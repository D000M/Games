#include "RespinMgr.h"
#include "../../GameDefinitions.h"
#include "oled/KeyboardScenarioController.h"
#include <game_modules/reels_geometry/ReelsLoader.h>
#include "main_game/MainGame.h"

constexpr int EXTENDED_FIG_X = 150;
constexpr int EXTENDED_FIG_Y = 135;

RespinMgr::RespinMgr() :
    m_nFramePosX(0),
    m_nFramePosY(0),
    m_nTextPosX(0),
    m_nTextPosY(0),
    m_nReel1X(0),
    m_nReel5X(0),
    m_nReelY(0),
    m_spStaticResource{nullptr},
    m_pdExtendedFig{nullptr},
    m_nExtendedAlpha{0},
	m_usPositions_x(),
	m_usPositions_y(),
    m_bIsFinished(true),
	m_bDrawStaticFig(true),
	m_usStaticFigures(),
    m_bDrawBigWild{false},
    m_bDrawBothWilds{false}
{

}

RespinMgr::~RespinMgr()
{

}

bool RespinMgr::Init()
{    
	for (int i = 0; i < SQRS_MAX_NUM; ++i) {
        m_usPositions_x[i] = ReelsLoader::GetReelsLoader()->GetReelX(i / VISIBLE_FIGURES_PER_REEL);
        m_usPositions_y[i] = ReelsLoader::GetReelsLoader()->GetReelY() + ((i % VISIBLE_FIGURES_PER_REEL) * ReelsLoader::GetReelsLoader()->GetReelAllHeight()) + ReelsLoader::GetReelsLoader()->GetReelFrameWidth();
    }

	for( int i = 0; i < REELS_COUNT; i++ )
	{
		for(int j = 0; j < VISIBLE_FIGURES_PER_REEL; j++ )
		{
			m_usStaticFigures[j][i] = FIGURES_NUM;
		}
	}

    /*Debug mode */
    if ( ! ( m_spStaticResource = gGameRM.GetPicture( std::string( "REEL_EF_" + std::to_string( static_cast<int>( ef7_wild + 1 ) ) ).c_str() ) ) )
    {
        return false;
    }
    
    double frame_rate = (22.2222) ;
    
    m_nReel1X = ReelsLoader::GetReelsLoader()->GetReelX(0) + ReelsLoader::GetReelsLoader()->GetReelWidth()/2 - 10;
    m_nReel5X = ReelsLoader::GetReelsLoader()->GetReelX(4) + ReelsLoader::GetReelsLoader()->GetReelWidth()/2 - 10;
    m_nReelY = ReelsLoader::GetReelsLoader()->GetReelY() + 420;
    if (!m_wildAppear.Init(ReelPlayer::Loop, frame_rate, "file://../data/ps_fhd_joker_burst_10/p/reels/reel_animations/WildAppear-rgba.mov" ))
    {
        eCDebug(LOG_CATEGORY_GAMES) << "[ 10 Joker Burst ] - RespinMgr::Init FAIL : m_wildAppear" ;
        return false ;
    }
    if (!m_BigWildAnim.Init(ReelPlayer::Loop, frame_rate, "file://../data/ps_fhd_joker_burst_10/p/reels/reel_animations/big_wild-rgba.mov" ))
    {
        eCDebug(LOG_CATEGORY_GAMES) << "[ 10 Joker Burst ] - RespinMgr::Init FAIL : m_BigWild" ;
        return false ;
    }
    m_nFramePosX = ReelsLoader::GetReelsLoader()->GetReelX(2) + ReelsLoader::GetReelsLoader()->GetReelWidth()/2;
    m_nFramePosY = ReelsLoader::GetReelsLoader()->GetReelY() + 420;
    if (!m_FramePlayer.Init(ReelPlayer::Loop, frame_rate, "file://../data/ps_fhd_joker_burst_10/p/reels/reel_animations/respin_frame-rgba.mov" ))
    {
        eCDebug(LOG_CATEGORY_GAMES) << "[ 10 Joker Burst ] - RespinMgr::Init FAIL : m_FramePlayer" ;
        return false ;
    }



    if (!m_wildSmallApper.Init(ReelPlayer::Loop, frame_rate, "file://../data/ps_fhd_joker_burst_10/p/reels/reel_animations/WildAppearSmall-rgba.mov" ))
    {
        eCDebug(LOG_CATEGORY_GAMES) << "[ 10 Joker Burst ] - RespinMgr::Init FAIL : m_wildSmallAppear" ;
        return false ;
    }


    m_nTextPosX = gpBasicDraw->SCREEN_WIDTH()/2;
    m_nTextPosY = gpBasicDraw->SCREEN_HEIGHT()/3 - 150;
    if (!m_TextPlayer.Init(ReelPlayer::OnceFinished, frame_rate, "file://../data/ps_fhd_joker_burst_10/p/reels/reel_animations/respin_text-rgba.mov" ))
    {
        eCDebug(LOG_CATEGORY_GAMES) << "[ 10 Joker Burst ] - RespinMgr::Init FAIL : m_TextPlayer" ;
        return false ;
    }

    if (!m_ReversedSmallWild.Init(ReelPlayer::OnceFinished, frame_rate, "file://../data/ps_fhd_joker_burst_10/p/reels/reel_animations/wild_small_reverse-rgba.mov" ))
    {
        eCDebug(LOG_CATEGORY_GAMES) << "[ 10 Joker Burst ] - RespinMgr::Init FAIL : m_ReversedSmallWild" ;
        return false ;
    }
    if (!m_ReversedBigWild.Init(ReelPlayer::OnceFinished, frame_rate, "file://../data/ps_fhd_joker_burst_10/p/reels/reel_animations/wild_big_reverse-rgba.mov" ))
    {
        eCDebug(LOG_CATEGORY_GAMES) << "[ 10 Joker Burst ] - RespinMgr::Init FAIL : m_ReversedBigWild" ;
        return false ;
    }
    m_ReversedBigWild.InitFrameCallBack([&](uint64_t frame) {
        if(frame >= 4) {
            if(m_nExtendedAlpha >= 210) {
                m_nExtendedAlpha = 255;
                return;
            }
            m_nExtendedAlpha += 55;
        }
    });
    m_wildAppear.InitFrameCallBack([&](uint64_t frame){
        if( m_wildAppear.GetCycles() == 0 ){
            if( m_wildAppear.GetCurrentFrame() == 42){
                gVBMgr.StopTimer(this, RFA_TIMER_FRAME_APPEAR);
                gVBMgr.StartTimer( this, RFA_TIMER_FRAME_APPEAR, 0 ,RFA_TIMER_MAIN_PERIOD );
                StartRespinTextAnim();
            }
            if(m_wildAppear.GetCurrentFrame() == 1) {
                if( !gpBasicSound->IsPlaying( gGameRM.GetSound( "WILD_APPEAR" )) ) {
                    gpBasicSound->StartSound( gGameRM.GetSound( "WILD_APPEAR" ) );
                }
            }
        }
    });
    auto EndOfRespinLabel = [&](){
        Stop();
        m_wildAppear.Stop();
        m_wildSmallApper.Stop();
        if( gpBasicSound->IsPlaying( gGameRM.GetSound( "RESPIN_TEXT_APPEAR" )) ) {
            gpBasicSound->StopSound( gGameRM.GetSound( "RESPIN_TEXT_APPEAR" ) );
        }
        if( gpBasicSound->IsPlaying( gGameRM.GetSound( "WILD_APPEAR" )) ) {
            gpBasicSound->StopSound( gGameRM.GetSound( "WILD_APPEAR" ) );
        }
    };
    m_TextPlayer.InitEndCallBack(EndOfRespinLabel);
    
	return RegisterResources();
}

void RespinMgr::Start(bool bWithSound)
{
    m_unCycleText = 0;
	m_bDrawStaticFig = false;
	m_bIsFinished = false;
    m_bDrawBothWilds = false;
}

void RespinMgr::Stop()
{
    m_unCycleText = 0;
	m_bIsFinished = true;
    m_bDrawStaticFig = true;
    m_bDrawBothWilds = false;
    m_bDrawBigWild = false;
    m_wildAppear.Stop();
    m_wildSmallApper.Stop();
    m_TextPlayer.Stop();
    StopReversedAnim();
    InsertWilds();
}

void RespinMgr::Draw()
{
    m_wildAppear.Draw(m_nReel1X, m_nReelY);
    m_wildAppear.Draw(m_nReel5X, m_nReelY);

    for(int i = 1; i < REELS_COUNT - 1; i++) {
        if(gMainGame.m_reelsArea.m_reels[i].GetScatterPos()) {
            m_wildSmallApper.Draw(ReelsLoader::GetReelsLoader()->GetReelX(i) + ReelsLoader::GetReelsLoader()->GetReelWidth() / 2, 
                (ReelsLoader::GetReelsLoader()->GetReelY() + (ReelsLoader::GetReelsLoader()->GetReelHeight() / 2) + (ReelsLoader::GetReelsLoader()->GetReelHeight() * (gMainGame.m_reelsArea.m_reels[i].GetScatterPos() - 1))));
        }
    }
    
    DrawTextOnly();
}

void RespinMgr::DrawOnlyFrame() {
    m_FramePlayer.Draw( m_nFramePosX , m_nReelY );
}
void RespinMgr::DrawTextOnly() {
    m_TextPlayer.Draw(m_nTextPosX, m_nTextPosY);
}

void RespinMgr::DrawBigWildAnim(const bool& bReversed) {
    
    if(!m_bDrawBigWild) {
        return;
    }
    if(bReversed) {
        
        m_ReversedBigWild.Draw(m_nReel1X, m_nReelY);
        m_ReversedBigWild.Draw(m_nReel5X, m_nReelY);      
        for(int reel = 1; reel < REELS_COUNT - 1; reel++) {
            
            if(gMainGame.m_reelsArea.m_reels[reel].GetWildPos()) {
                m_ReversedSmallWild.Draw(ReelsLoader::GetReelsLoader()->GetReelX(reel) + ReelsLoader::GetReelsLoader()->GetReelWidth() / 2, 
                    (ReelsLoader::GetReelsLoader()->GetReelY() + (ReelsLoader::GetReelsLoader()->GetReelHeight() / 2) + (ReelsLoader::GetReelsLoader()->GetReelHeight() * (gMainGame.m_reelsArea.m_reels[reel].GetWildPos() - 1))));
            }
            
            for(int pos = 0; pos < VISIBLE_FIGURES_PER_REEL; pos++) {
                if(StaticWildPos(pos, reel)) {
                    
                    m_ReversedSmallWild.Draw(ReelsLoader::GetReelsLoader()->GetReelX(reel) + ReelsLoader::GetReelsLoader()->GetReelWidth() / 2, 
                        (ReelsLoader::GetReelsLoader()->GetReelY() + (ReelsLoader::GetReelsLoader()->GetReelHeight() / 2) + (ReelsLoader::GetReelsLoader()->GetReelHeight() * pos)));                
                } 
            }
        }
    }
    else {
        m_BigWildAnim.Draw(m_nReel1X, m_nReelY);
        if(m_bDrawBothWilds) {
            m_BigWildAnim.Draw(m_nReel5X, m_nReelY);
        }
    }
}
void RespinMgr::OnTick(int nID, int times)
{
    if( nID == RFA_TIMER_WILD_APPEAR )
    {
        gVBMgr.StopTimer(this, nID);
        m_wildSmallApper.Start();
        m_wildAppear.Start();
        /*start*/
    }
    else if(nID == RFA_TIMER_FRAME_ONLY) {
        gVBMgr.StopTimer(this, nID);
        m_FramePlayer.Start(m_FramePlayer.GetTotalFrames() / 2);
    }
    else if(nID == RFA_TIMER_BIG_WILD) {
        gVBMgr.StopTimer(this, nID);
        m_BigWildAnim.Start();
    }
    else if(nID == RFA_TIMER_FRAME_APPEAR) {
        gVBMgr.StopTimer(this, nID);
        m_FramePlayer.Start();
    }
    else if(nID == RFA_TIMER_TEXT) { 
        gVBMgr.StopTimer(this, nID);
        m_TextPlayer.Start();
        gKeyboardScenarioController->RequestFunctionUpdate();
    }
    else if(nID == RFA_TIMER_REVERSE) {
        gVBMgr.StopTimer(this, nID);
        m_ReversedBigWild.Start();
        m_ReversedSmallWild.Start();
    }
}

bool RespinMgr::RegisterResources()
{

    return true;
}

void RespinMgr::Reset()
{
	m_bIsFinished = false;
    m_bDrawStaticFig = false;
}
bool RespinMgr::IsStaticSquare(uint8_t aSqaureID ){

    if( aSqaureID < SQRS_MAX_NUM ){
        bool ReelAnimationIsActive = (gMainGame.m_reelsArea.m_ActionMgr.m_AnimMgr.IsActiveWildAnimation(aSqaureID));
        if( ReelAnimationIsActive ){
            return false;
        }
    }
    return m_usStaticFigures[(aSqaureID % VISIBLE_FIGURES_PER_REEL)][(aSqaureID / VISIBLE_FIGURES_PER_REEL)] != FIGURES_NUM;
}

void RespinMgr::DrawStaticFigures()
{
    /*avoid static drawing figure until big wild animation is drawn*/
    if( m_wildAppear.IsActive() || IsReversedAnimActive()) {
        return;
    }
    for ( uint8_t sqrId {3} ; sqrId < SQRS_MAX_NUM - 3 ; ++sqrId  ){

        if ( IsStaticSquare(sqrId)){
            gpBasicDraw->SetColor( 255, 255, 255, 255 );
            gpBasicDraw->DrawPicture( m_usPositions_x[sqrId] - 75,m_usPositions_y[sqrId] - 90 , 0 , m_spStaticResource );
        }
    }  
}
void RespinMgr::SetStaticFigures(const short unsigned int usStaticFigures[VISIBLE_FIGURES_PER_REEL][REELS_COUNT])
{
	memcpy( m_usStaticFigures, usStaticFigures, SQRS_MAX_NUM*sizeof(unsigned short));
}

void RespinMgr::StartFrameAnimationOnly()
{
    m_bIsFinished = false;
    m_bDrawStaticFig = false;
    gVBMgr.StartTimer( this, RFA_TIMER_WILD_APPEAR, 0 ,RFA_TIMER_MAIN_PERIOD );
}
void RespinMgr::StartBigWildAnimation() {
    m_nExtendedAlpha = 0;
    if(m_BigWildAnim.IsActive()) {
        m_BigWildAnim.Stop();
    }
    gVBMgr.StopTimer(this, RFA_TIMER_BIG_WILD);
    gVBMgr.StartTimer( this, RFA_TIMER_BIG_WILD, 0 ,RFA_TIMER_MAIN_PERIOD );
}
void RespinMgr::StopFrameAnimation()
{
    m_FramePlayer.Stop();
    m_wildAppear.Stop();
}

bool RespinMgr::IsActiveBigWildAnimation(uint8_t aSqrID)
{
    if( m_wildAppear.IsActive() ){
        uint8_t reelId = aSqrID / VISIBLE_FIGURES_PER_REEL;
        if( reelId == 0 || reelId == 4  ){
            return true;
        }

    }
    return false;
}

bool RespinMgr::IsActiveScatterSquare(uint8_t aSqrID) {

    // validate parameter
    if ( aSqrID >= SQRS_MAX_NUM ) { return false ; }

    if( m_wildSmallApper.IsActive() ){
        uint8_t reelId = aSqrID / VISIBLE_FIGURES_PER_REEL; //reel
        uint8_t figPos = aSqrID % VISIBLE_FIGURES_PER_REEL;
        if(gMainGame.m_reelsArea.m_reels[reelId].GetScatterPos() - 1 == figPos) {
            return true;
        }
    }
    
    return false;
}

void RespinMgr::InsertWilds() {
    
    EFigure wilds[ALL_FIGURES_PER_REEL];
    for(auto&& elem : wilds) {
        elem = ef7_wild;
    }

    gMainGame.m_reelsArea.m_reels[0].SetResults(wilds, true);
    gMainGame.m_reelsArea.m_reels[4].SetResults(wilds, true);
    for(int i = 1; i < REELS_COUNT - 1; i++) {
        if(gMainGame.m_reelsArea.m_reels[i].GetScatterPos()) {
            gMainGame.m_reelsArea.m_reels[i].ReplaceScatter(gMainGame.m_reelsArea.m_reels[i].GetScatterPos());
        }
    }
}

void RespinMgr::ResumeFrameAnimation() {
    gVBMgr.StartTimer( this, RFA_TIMER_FRAME_ONLY, 0 ,RFA_TIMER_MAIN_PERIOD );
}

bool RespinMgr::StaticWildPos(int pos, int reel) {
    return m_usStaticFigures[pos][reel] != FIGURES_NUM;
}

bool RespinMgr::GetDrawBigWild() const {
    return m_bDrawBigWild;
}
bool RespinMgr::GetDrawBothWilds() const {
    return m_bDrawBothWilds;
}
void RespinMgr::SetDrawBigAnim(const bool& bDraw, const bool& bBothWilds) {
    m_bDrawBigWild = bDraw;
    m_bDrawBothWilds = bBothWilds;
}

bool RespinMgr::IsRespinTextActive(){
    return m_TextPlayer.IsActive();
}
bool RespinMgr::IsReversedAnimActive() {
    return (m_ReversedBigWild.IsActive() || m_ReversedSmallWild.IsActive());
}
void RespinMgr::StopReversedAnim() {
    m_ReversedBigWild.Stop();
    m_ReversedSmallWild.Stop();
}
void RespinMgr::StartReversedAnim() {
    m_bDrawBigWild = true;
    m_nExtendedAlpha = 0;
    if(gMainGame.GetSpecialFigure() != FIGURES_NUM) {
        SetExtendedFig();
    }
    gVBMgr.StopTimer(this, RFA_TIMER_REVERSE);
    gVBMgr.StartTimer( this, RFA_TIMER_REVERSE, 0 ,RFA_TIMER_MAIN_PERIOD );
}
void RespinMgr::StartRespinTextAnim() {
    m_unCycleText = 0;
    m_bIsFinished = false;
    gpBasicSound->StopAllSounds();
    if( !gpBasicSound->IsPlaying( gGameRM.GetSound( "RESPIN_TEXT_APPEAR" )) ) {
        gpBasicSound->StartSound( gGameRM.GetSound( "RESPIN_TEXT_APPEAR" ) );
    }
    gVBMgr.StopTimer(this, RFA_TIMER_TEXT);
    gVBMgr.StartTimer( this, RFA_TIMER_TEXT, 0 ,RFA_TIMER_MAIN_PERIOD );
}
void RespinMgr::SetExtendedFig() {
    if(gMainGame.GetSpecialFigure() != FIGURES_NUM) {
        m_pdExtendedFig = gGameRM.GetPicture(std::string("REEL_EF_" + std::to_string(static_cast<int>( gMainGame.GetSpecialFigure() + 1 ))).c_str());
    }
    else {
        m_pdExtendedFig = nullptr;
    }
}

void RespinMgr::ExtendedFigAppear() {
    gpBasicDraw->SetColor( 255, 255, 255, m_nExtendedAlpha );
    for(int pos = 0; pos < VISIBLE_FIGURES_PER_REEL; pos++) {
        gpBasicDraw->DrawPicture( (ReelsLoader::GetReelsLoader()->GetReelX(0) + ReelsLoader::GetReelsLoader()->GetReelWidth() / 2) - EXTENDED_FIG_X,
            (ReelsLoader::GetReelsLoader()->GetReelY() + (ReelsLoader::GetReelsLoader()->GetReelHeight() / 2) + (ReelsLoader::GetReelsLoader()->GetReelHeight() * pos)) - EXTENDED_FIG_Y , 0 , m_pdExtendedFig );

        gpBasicDraw->DrawPicture( (ReelsLoader::GetReelsLoader()->GetReelX(4) + ReelsLoader::GetReelsLoader()->GetReelWidth() / 2) - EXTENDED_FIG_X,
            (ReelsLoader::GetReelsLoader()->GetReelY() + (ReelsLoader::GetReelsLoader()->GetReelHeight() / 2) + (ReelsLoader::GetReelsLoader()->GetReelHeight() * pos)) - EXTENDED_FIG_Y , 0 , m_pdExtendedFig );
    }
    for(int reel = 1; reel < REELS_COUNT - 1; reel++) {

        if(gMainGame.m_reelsArea.m_reels[reel].GetWildPos()) {
            gpBasicDraw->DrawPicture( (ReelsLoader::GetReelsLoader()->GetReelX(reel) + ReelsLoader::GetReelsLoader()->GetReelWidth() / 2) - EXTENDED_FIG_X,
                    (ReelsLoader::GetReelsLoader()->GetReelY() + (ReelsLoader::GetReelsLoader()->GetReelHeight() / 2) + (ReelsLoader::GetReelsLoader()->GetReelHeight() * (gMainGame.m_reelsArea.m_reels[reel].GetWildPos() - 1))) - EXTENDED_FIG_Y , 0 , m_pdExtendedFig );
        }

        for(int pos = 0; pos < VISIBLE_FIGURES_PER_REEL; pos++) {
            if(StaticWildPos(pos, reel)) {
                gpBasicDraw->DrawPicture( (ReelsLoader::GetReelsLoader()->GetReelX(reel) + ReelsLoader::GetReelsLoader()->GetReelWidth() / 2) - EXTENDED_FIG_X
                    ,(ReelsLoader::GetReelsLoader()->GetReelY() + (ReelsLoader::GetReelsLoader()->GetReelHeight() / 2) + (ReelsLoader::GetReelsLoader()->GetReelHeight() * pos)) - EXTENDED_FIG_Y, 0 , m_pdExtendedFig );

            } 
        }
    }
}
