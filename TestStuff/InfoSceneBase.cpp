#include "InfoSceneBase.h"
#include <actions/ActionsInclude.h>
#include <egt_itc/thread_pool.h>
#include <egt_lib/Imm_interfaces.h>
#include <egt_lib/resource_mgr/ResourceMgr.h>
#include <vaapi_player_x11/player.h>

#include <slave_legacy/slave_rss_mgr.h>
#include <slave_legacy/slave_screen_obj.h>
#include <slave_core/slave_render.h>
#include <slave_core/slave_rss.h>

#include <egt_rss_impl/rss_image_impl/ImageImpl.h>
#include <egt_rss_impl/rss_text_impl/TextImpl.h>
#include <egt_rss_impl/rss_font_impl/FontImpl.h>
#include <common/project_definitions/definitions.h>


using namespace egt;
namespace
{
    struct PictureOrderByZ
    {
        bool operator()(const InfoResourceModel& first,
                        const InfoResourceModel& second)
        {
            return first.z < second.z;
        }
    };
}


void InfoSceneBase::InitWithMsg( const UniMsg &msg )
{
    if( msg.HasValue("config_view") )
    {
        auto& resources = GetContext().Get<egt::slave::legacy::RssMgrInterface>().getResources();
        ELanguage eLanguage = eLanguageNumber;
        msg.GetValue("current_language_idx", eLanguage);

        if ( eLanguage != eLanguageNumber &&
            resources.GetCurrentLanguage() != eLanguage )
        {
            resources.LanguageChanged(resources.GetCurrentLanguage(), eLanguage);
        }

        egt::UniMsg configMsg;
        msg.GetValue("config_view", configMsg);

        configMsg.GetValue("info_values", m_infoValues);
        configMsg.GetValue("info_resources", m_resModels);
        calculateValueScales();

        std::vector<InfoVideoModel> videoModelList;
        configMsg.GetValue("video_values", videoModelList);
        if(false == videoModelList.empty())
        {
            AssertMsg(m_videoPlayers.size() <= videoModelList.size(),
            "VideoPlayer size is less than requested videos to play! Please change the size of VideoPlayer(InfoSceneBase.h)");

            if(configMsg.HasValue("refresh_video"))
            {
                refreshVideo(videoModelList);
            }
            if(configMsg.HasValue("reinit_scene"))
            {
                reinitVideo(videoModelList);
            }
        }

        if(configMsg.HasValue("refresh_crossfade"))
        {
            refreshCrossFade(configMsg);
        }
        if(configMsg.HasValue("reinit_scene"))
        {
            reinitCrossFade(configMsg);
        }
        auto rend = GetContextPtr()->Get<slave::RendererPtr>();
        m_fbo = rend->create_texture(rend->get_width(), rend->get_height(),
                                     video_ctrl::pix_type::rgb, video_ctrl::texture::format_type::streaming);
    }
}

void InfoSceneBase::Init()
{
    auto winPtr = GetContext().Get<slave::WindowPtr>();
    auto pool = GetContext().Get<std::shared_ptr<itc::thread_pool>>();
    vaapi::player::init(*winPtr, pool);
}

void InfoSceneBase::Deinit()
{
    for (auto&  e : m_videoPlayers)
    {
        auto& splashPlayer = e.first;
        splashPlayer.UnloadMovie();
    }
    vaapi::player::shutdown();
}

void InfoSceneBase::Show()
{
    m_readyToDraw = false;
}

void InfoSceneBase::Hide()
{
    auto& drawer = *GetContext().Get<slave::legacy::IBasicDrawPtr>();
    drawer.SetColor(255, 255, 255, 255);
}

///////////////////////////////////////////////////////////////////////////
void InfoSceneBase::Draw()
{
    auto rend = GetContextPtr()->Get<slave::RendererPtr>();
    if ( m_updateFBO )
    {
        rend->push_fbo(m_fbo);
        if(false == m_crossFadeAnimation.empty())
        {
            drawCrossFade();
        }
        else
        {
            drawPictures(m_resModels);
        }

        drawValues();
        rend->pop_fbo();

    }

    const auto& src_rect = m_fbo->get_rect();
    video_ctrl::rect dest_rect {GetPos().x,GetPos().y, rend->get_width()/*+GetPos().x*/, rend->get_height()/*+GetPos().y*/};
    rend->get_list().add_image(m_fbo, src_rect, dest_rect);
    drawVideos();

    m_AdditionalAnim.Draw( GetPos() );
}

///////////////////////////////////////////////////////////////////////////
const std::vector<InfoResourceModel> &InfoSceneBase::GetResModels() const
{
    return m_resModels;
}

InfoSceneBase::VideoList& InfoSceneBase::GetVideoModels()
{
    return m_videoPlayers;
}

void InfoSceneBase::initVideo(SplashPlayer &player, const InfoVideoModel &videoModel)
{
    auto interfaceType = videoModel.loop ? SplashPlayer::Loop : SplashPlayer::Once;

    if(videoModel.path.empty())
    {
        eCDebug(LOG_CATEGORY_SLAVE) << "InfoSceneBase::Init - header_animation is empty";
        return;
    }

    if( false == player.Init( interfaceType,
                              videoModel.fps,
                              videoModel.path ) )
    {
        eCDebug(LOG_CATEGORY_SLAVE) << "InfoSceneBase vaapi::player failed to init:"
                                    << " movie: " << videoModel.path;
        return;
    }

    player.UnloadMovie();
    if (false == player.LoadMovie(GetContext()) )
    {
        eCDebug(LOG_CATEGORY_SLAVE) << "InfoSceneBase vaapi::player failed to load";
        return;
    }

    player.Start();
}

void InfoSceneBase::reinitVideo(const std::vector<InfoVideoModel>& videoModelList)
{
    for(auto& p : m_videoPlayers)
    {
        p.first.UnloadMovie();
    }

    for(size_t i = 0; i < videoModelList.size(); i++)
    {
        m_videoPlayers[i].second = videoModelList[i];
        initVideo(m_videoPlayers[i].first, videoModelList[i]);
    }
}

void InfoSceneBase::refreshVideo(const std::vector<InfoVideoModel>& videoModelList)
{
    for(size_t i = 0; i < m_videoPlayers.size(); i++)
    {
        auto& videoPlayer = m_videoPlayers[i].first;
        auto& videoModel = m_videoPlayers[i].second;

        auto iter = std::find(videoModelList.begin(), videoModelList.end(), videoModel);
        if(iter != videoModelList.end())
        {
            continue;
        }

        videoPlayer.UnloadMovie();
        videoModel = videoModelList[i];
        initVideo(videoPlayer, videoModelList[i]);
    }
}

void InfoSceneBase::refreshCrossFade(const UniMsg &configMsg)
{
    std::vector<InfoCrossFadeModel> crossFadeList;
    configMsg.GetValue("cross_fade_values", crossFadeList);
    AssertMsg(m_crossFadeAnimation.size() == crossFadeList.size(), "Can not refresh crossfade animation with differnet size");

    for(size_t i = 0; i < crossFadeList.size(); i++)
    {
        const auto& crossFade = crossFadeList[i];
        auto iter = std::find_if(m_crossFadeAnimation.begin(), m_crossFadeAnimation.end(), [&crossFade](const auto& crossFadeAnimation)
        {
                return crossFadeAnimation.IsSameModel(crossFade);
        });

        if(iter != m_crossFadeAnimation.end())
        {
            continue;
        }

        m_crossFadeAnimation[i].Init(crossFade);
        m_crossFadeAnimation[i].StartAnim();
    }
}

void InfoSceneBase::reinitCrossFade(const UniMsg &configMsg)
{
    m_crossFadeAnimation.clear();

    std::vector<InfoCrossFadeModel> crossFadeList;
    configMsg.GetValue("cross_fade_values", crossFadeList);

    for(const auto& crossFadeModel : crossFadeList)
    {
        CrossFadeAnimation animation([& flag = m_updateFBO](){ flag = true;} );
        animation.Init(crossFadeModel);
        m_crossFadeAnimation.push_back(animation);
    }

    for(auto& animation : m_crossFadeAnimation)
    {
        animation.StartAnim();
    }
}

void InfoSceneBase::drawPictures(const std::vector<InfoResourceModel> &resModels)
{
    m_readyToDraw = true;

    for ( const auto& resModel : resModels )
    {
        if (false == drawPicture(resModel))
        {
            m_readyToDraw = false;
            break;
        }
    }
    if ( m_readyToDraw )
    {
        m_updateFBO = false;
    }
}

bool InfoSceneBase::drawPicture(const InfoResourceModel &resModel)
{
    auto& resources = GetContext().Get<slave::legacy::RssMgrInterface>().getResources();
    auto picture = resources.GetPicture(resModel.resourceId.c_str());

    if (nullptr == picture)
    {
        m_readyToDraw = false;
        return false;
    }

    auto& drawer = *GetContext().Get<slave::legacy::IBasicDrawPtr>();    
    auto alpha = uint8_t(resModel.alpha * 255);
    drawer.SetColor(255, 255, 255, alpha);
    drawer.DrawPicture(resModel.xPos, resModel.yPos, 0, picture);
    return true;
}

void InfoSceneBase::drawValues()
{
    if( false == m_readyToDraw)
    {
        return;
    }

    auto drawer = GetContext().Get<slave::legacy::IBasicDrawPtr>();
    auto& resources = GetContext().Get<slave::legacy::RssMgrInterface>().getResources();
    
    for( const auto& infoValue : m_infoValues )
    {
        drawer->SetColor(infoValue.color.r, infoValue.color.g, infoValue.color.b, infoValue.color.a);
        auto font = resources.GetFont(infoValue.fontName.c_str());
        drawer->SetFont(font);

        drawer->DrawText(infoValue.xPos,
                         infoValue.yPos,
                         0,
                         infoValue.formatterResult,
                         infoValue.scale,
                         infoValue.alignment);
    }
}

void InfoSceneBase::drawVideos()
{
//    for (auto& p : m_videoPlayers)
//    {
        static int currPos = 1;
        static bool drawRepeatedMovie = true;
        
        std::pair<SplashPlayer, InfoVideoModel>* p = nullptr;
         if(drawRepeatedMovie) {
            p = &m_videoPlayers.at(0);
        }
        else {
            p = &m_videoPlayers.at(currPos);
        }
        
        auto& videoPlayer = p->first;
        const auto& videoModel = p->second;
        if(!videoPlayer.IsActive()) {
            videoPlayer.Start();
        }
        videoPlayer.Draw(videoModel.pos.first + GetPos().x, videoModel.pos.second + GetPos().y);
        if(drawRepeatedMovie && m_videoPlayers.at(0).first.IsLastFrame()) {
            m_videoPlayers.at(0).first.Stop();
            drawRepeatedMovie = false;
        }
        else if(!drawRepeatedMovie && m_videoPlayers.at(currPos).first.IsLastFrame()) {
            m_videoPlayers.at(currPos).first.Stop();
            currPos++;
            if(currPos == m_videoPlayers.size()) {
                currPos = 1;
            }
            drawRepeatedMovie = true;
        }
//    }
}

void InfoSceneBase::drawCrossFade()
{
    auto pictures = m_resModels;
    for(const auto& animation : m_crossFadeAnimation)
    {
        pictures.push_back(animation.GetFrontResource());
        pictures.push_back(animation.GetBackResource());
    }

    std::sort(pictures.begin(), pictures.end(), PictureOrderByZ{});
    drawPictures(pictures);
}

void InfoSceneBase::stopVideos()
{
    for(size_t i = 0; i < m_videoPlayers.size(); i++)
    {
        m_videoPlayers[i].first.Stop();
    }
}

///////////////////////////////////////////////////////////////////////////
void InfoSceneBase::calculateValueScales()
{
    std::map<int, std::vector<InfoValueModel>> infoValuePerGroup;
    for( const auto& infoValue : m_infoValues )
    {
        infoValuePerGroup[infoValue.groupId].push_back(infoValue);
    }

    auto& resources = GetContext().Get<slave::legacy::RssMgrInterface>().getResources();
    auto& drawer = *GetContext().Get<slave::legacy::IBasicDrawPtr>();

    for(auto& p : infoValuePerGroup)
    {
        float groupScale = 1.0f;
        for(const auto& infoValue : p.second)
        {
            const auto font = resources.GetFont(infoValue.fontName.c_str());
            if((nullptr == font) || (infoValue.scaleBoxWidth == 0))
            {
                continue;
            }

            SPicDimensions box; box.nWidth = infoValue.scaleBoxWidth;
            float scale = drawer.FitText( infoValue.formatterResult.Value.c_str(), 0,
                                          &box, const_cast<FontInfo*>(font) );

            groupScale = std::min(groupScale, scale);
        }
        for(auto& infoValue : m_infoValues)
        {
            if(infoValue.groupId == p.first)
            {
                infoValue.scale = groupScale;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void InfoSceneBase::ReceiveMsg( const UniMsg& msg )
{
    if((msg.name == "select_view") && msg.description == GetName())
    {
        InitWithMsg( msg );
    }
    else if( msg.name == "change_active_game" )
    {
        if(  msg.HasValue("stop_h2_videos") )
            stopVideos();

        m_AdditionalAnim.Deinitialize();
    }
    else if ( msg.name == "additional_animation_scenario")
    {
        m_AdditionalAnim.SendMsg( msg , GetContext() , GetName() , GetType() );
    }
}

void InfoSceneBase::Update(DeltaTime dt)
{
    for(auto& animation : m_crossFadeAnimation)
    {
        animation.Update(dt);
    }
    m_AdditionalAnim.Update();
}


int64_t InfoSceneBase::EvalSelectView(const UniMsg& msg, const std::string& pageName, const std::string& pageType)
{
    std::string requestedPageName;
    std::string requestedPageType;

    msg.GetValue("page_name", requestedPageName);
    msg.GetValue("page_type", requestedPageType);


    if (msg.name == "select_view" &&
        pageName == requestedPageName &&
        pageType == requestedPageType)
    {
        m_updateFBO = true;
        return 10;
    }

    return -1;
}
