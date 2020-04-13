#include "GSPanelButtonView.h"

#include "../NotifyMgr.h"
#include "GSDemoMgr.h"
#include "GSLanguageView.h"
#include "../HatFacade.h"
#include <egt_lib/utils/Utils.h>
#include "HatRestrictions.h"
#include <RestrictionComponents/GameConfiguration/GameSelectComponent.h>

namespace HatGameSelect
{

GSPanelButtonView::GSPanelButtonView() 
                  : m_pRatingButton ( nullptr ),
                    m_pLanguageButton ( nullptr )
{
    Clear();
}

GSPanelButtonView::GSPanelButtonView ( int , int  )
                  : m_pRatingButton ( nullptr ),
                    m_pLanguageButton ( nullptr )
{
    Clear();
}

GSPanelButtonView::~GSPanelButtonView()
{
    DeInit();
}

void GSPanelButtonView::Clear()
{
    m_pResourceMgr = NULL;
    m_pBasicDraw = NULL;
    m_pBasicSound = NULL;
    m_pTouchDispatcher = NULL;
	m_spdLabelChooseGame = NULL;
    m_spdLangFrame = NULL;
    m_pFrame = {0,0};

    m_strRatingBtnPic.assign ( "n/a" );
    m_strLangBtnPic.assign ( "n/a" );

    m_ViewRect.bottom = 0;
    m_ViewRect.left = 0;
    m_ViewRect.right = 0;
    m_ViewRect.top = 0;

    m_nPictureLanguageHeight = 0;
    m_nPictureLanguageWidth = 0;
    m_nPictureRatingHeight = 0;
    m_nPictureRatingWidth = 0;
    m_nNumberOfPages = 0;
    m_cnOffsetXBetweenBtn = 0;
    m_cnOffsetYBetweenBtn = 0;

    m_bDisableInput = false;
    m_bIsGameRatingPressed = false;
    m_bStartHideLangugageView = false;

}


bool GSPanelButtonView::Init ( ResourceMgr* pResourceMgr, IBasicDraw* pBasicDraw, IBasicSound* pBasicSound, HatTouchDispatcher::TouchDispatcher* pTouchDispatcher, RECT RectView )
{

    m_pResourceMgr = pResourceMgr;
    m_pBasicDraw = pBasicDraw;
    m_pBasicSound = pBasicSound;
    m_pTouchDispatcher = pTouchDispatcher;

    if ( m_pResourceMgr == NULL || m_pBasicDraw == NULL || m_pBasicSound == NULL || m_pTouchDispatcher == NULL )
    {
        eCDebug ( LOG_CATEGORY_HAT ) << "ERROR NULL pointer: pResourceMgr = " << pResourceMgr << " pBasicDraw = " << pBasicDraw << ", pBasicSound = " << pBasicSound << ", pTouchDispatcher = " << pTouchDispatcher;
        return false;
    }

    HatITouchZone::ITouchZone::AddClient ( this );
    HatNotifyMgr::NotifyMgr::Instance().AddClient ( this );
    IKeyboardEvent::AddClient ( this );

    m_ViewRect = RectView;

    m_bDisableInput = false;
    m_bIsGameRatingPressed = false;
    m_bStartHideLangugageView = false;

    m_pLanguageButton = new PanelLanguageButton();
    m_pRatingButton = new GSPanelButton();

    auto cfg = GetHatComp_GameSelect(GAME_SELECT_ID);
    if( cfg->Has_DenomLangSpace() )
    {
    	auto DenomLangOffset_ = cfg->Get_DenomLangSpace();
    	m_cnOffsetXBetweenBtn = DenomLangOffset_.first;
    	m_cnOffsetYBetweenBtn = DenomLangOffset_.second;
    }

    if ( m_strLangBtnPic.compare ( "n/a" ) == 0 || m_strRatingBtnPic.compare ( "n/a" ) == 0 )
    {
        eCDebug ( LOG_CATEGORY_HAT ) << "ERROR unset resource!";
        return false;
    }


    m_nPictureLanguageHeight = ( m_ViewRect.GetRectHeight() - m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nHeight ) /2;
    m_nPictureLanguageWidth = ( ( m_ViewRect.GetRectWidth() +   m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nWidth ) -  m_pResourceMgr->GetMlPicture ( m_strRatingBtnPic.c_str() )->GetPicDimensions().nWidth ) /2;

    if ( ! m_pLanguageButton->Init ( m_pResourceMgr, m_pBasicDraw, m_pBasicSound, POINT ( ( m_ViewRect.left + m_nPictureLanguageWidth ), ( m_ViewRect.top + m_nPictureLanguageHeight ) ),
                                     m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nWidth,m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nHeight, eLanguage ) )
    {
        eCDebug ( LOG_CATEGORY_HAT ) << "ERROR Can`t init  m_pLanguageButton.Init";
        return false;
    }

    m_pLanguageButton->SetDrawEmptyButton(false);

    m_nPictureRatingHeight = ( m_ViewRect.GetRectHeight() - m_pResourceMgr->GetMlPicture ( m_strRatingBtnPic.c_str() )->GetPicDimensions().nHeight ) /2;
    m_nPictureRatingWidth = ( m_ViewRect.GetRectWidth() - ( m_pResourceMgr->GetMlPicture ( m_strRatingBtnPic.c_str() )->GetPicDimensions().nWidth +  m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nWidth ) ) /2;

    if ( ! m_pRatingButton->Init ( m_pResourceMgr, m_pBasicDraw, m_pBasicSound, POINT ( (( m_ViewRect.left + m_nPictureRatingWidth )- m_cnOffsetXBetweenBtn ), ( m_ViewRect.top + m_nPictureRatingHeight ) - m_cnOffsetYBetweenBtn ),
                                   m_pResourceMgr->GetMlPicture ( m_strRatingBtnPic.c_str() )->GetPicDimensions().nWidth, m_pResourceMgr->GetMlPicture ( m_strRatingBtnPic.c_str() )->GetPicDimensions().nHeight , eRating ) )
    {
        eCDebug ( LOG_CATEGORY_HAT ) << "ERROR Can`t init  m_pRatingButton.Init";
        return false;
    }
    m_pRatingButton->SetDrawEmptyButton(false);
    
    m_pRatingButton->SetTextMl ( m_strRatingBtnPic, m_strRatingBtnPic + "_ON" );
    m_pLanguageButton->SetTextMl ( m_strLangBtnPic, m_strLangBtnPic + "_ON" );
    m_pRatingButton->SetScaleML ( false );
    m_pLanguageButton->SetScaleML ( false );

    auto onClickUp = [this] ( BaseButton* btn )
    {
        this->CbButtonPressed ( btn );
    };

    m_pLanguageButton->SignalClickDown = onClickUp;
    m_pRatingButton->SignalClickDown = onClickUp;

    m_spdLabelChooseGame = m_pResourceMgr->GetMlPicture ( "LABEL_CHOOSE_GAME" );
    m_spdLangFrame = m_pResourceMgr->GetPicture("FRAME_GENERAL");
    if ( m_spdLabelChooseGame == NULL )
    {
        eCDebug ( LOG_CATEGORY_HAT ) << "ERROR! NULL pointer m_spdLabelChooseGame!";
        return false;
    }

    return true;
}

void GSPanelButtonView::DeInit()
{
    delete m_pRatingButton;
    delete m_pLanguageButton;

    m_pRatingButton = NULL;
    m_spdLangFrame = NULL;
    m_pLanguageButton = NULL;
    m_spdLabelChooseGame = NULL;
    m_pResourceMgr = NULL;
    m_pBasicDraw = NULL;
    m_pBasicSound = NULL;
    m_pTouchDispatcher = NULL;

    Clear();
}

void GSPanelButtonView::Draw()
{

    m_pRatingButton->Draw();
    m_pBasicDraw->Enable ( GL_BLEND );
    if( m_spdLangFrame != nullptr)
    {
        m_pBasicDraw->DrawPicture(m_pFrame.x, m_pFrame.y, 0, m_spdLangFrame);
    }
    m_pLanguageButton->Draw();

    m_pBasicDraw->Enable ( GL_BLEND );
    m_pBasicDraw->DrawMlPicture ( m_spdLabelChooseGame );
    m_pBasicDraw->Disable ( GL_BLEND );
}

void GSPanelButtonView::SetShowGameRating ( bool bShowGameRating )
{
    if ( bShowGameRating )
    {
        m_pRatingButton->Disable ( false );
    }
    else
    {
        m_pRatingButton->Hide();
    }
    RecalculationButtonsPosition ( bShowGameRating );
}

void GSPanelButtonView::RecalculationButtonsPosition ( bool bShowGameRating )
{
    if ( ! bShowGameRating )
    {
        m_nPictureLanguageHeight = ( m_ViewRect.GetRectHeight() - m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nHeight )  /2;
        m_nPictureLanguageWidth = ( m_ViewRect.GetRectWidth() - m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nWidth ) /2;
        m_pFrame = POINT ( ( m_ViewRect.left + m_nPictureLanguageWidth ), ( m_ViewRect.top + m_nPictureLanguageHeight ) );
        m_pLanguageButton->SetButtonPosition ( POINT ( ( m_ViewRect.left + m_nPictureLanguageWidth ), ( m_ViewRect.top + m_nPictureLanguageHeight ) ) );
    }
    else
    {
        m_nPictureLanguageHeight = ( m_ViewRect.GetRectHeight() - m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nHeight ) /2;
        m_nPictureLanguageWidth = ( ( m_ViewRect.GetRectWidth() +  m_pResourceMgr->GetMlPicture ( m_strLangBtnPic.c_str() )->GetPicDimensions().nWidth ) - m_pResourceMgr->GetMlPicture ( m_strRatingBtnPic.c_str() )->GetPicDimensions().nWidth ) /2;
        m_pFrame =  POINT ( ( m_cnOffsetXBetweenBtn +( m_ViewRect.left + m_nPictureLanguageWidth )),m_cnOffsetYBetweenBtn + ( m_ViewRect.top + m_nPictureLanguageHeight ) );
        m_pLanguageButton->SetButtonPosition ( POINT ( ( m_cnOffsetXBetweenBtn +( m_ViewRect.left + m_nPictureLanguageWidth )),m_cnOffsetYBetweenBtn + ( m_ViewRect.top + m_nPictureLanguageHeight ) ) );
    }
}

void GSPanelButtonView::ReleasedButtons()
{
    m_pRatingButton->Released();
    m_pLanguageButton->Released();
}

void GSPanelButtonView::RestartTimerGameRating()
{
    if ( HatApplication::GetInstance().m_TimerMgr->CheckIfTimerOn ( this, TID_GAME_RATING ) )
    {
        HatApplication::GetInstance().m_TimerMgr->StopTimer ( this, TID_GAME_RATING );
        HatApplication::GetInstance().m_TimerMgr->StartTimer ( this, TID_GAME_RATING, TP_GAME_RATING_PERION );
    }
}

void GSPanelButtonView::CbButtonPressed ( BaseButton* btn )
{
    switch ( btn->GetButtonId() )
    {
    case eLanguage:
        HatNotifyMgr::NotifyMgr::Instance().SendBtnLanguagePressed();
        break;
    case eRating:
        m_bIsGameRatingPressed = ! m_bIsGameRatingPressed;
        HatNotifyMgr::NotifyMgr::Instance().SendBtnGameRatingPressed(m_bIsGameRatingPressed);
        m_pBasicSound->StartSound ( m_pResourceMgr->GetSound ( "GSGAME_RATING" ) );
        HatApplication::GetInstance().m_TimerMgr->StopTimer ( this, TID_GAME_RATING );
        if ( m_bIsGameRatingPressed )
        {
            HatApplication::GetInstance().m_TimerMgr->StartTimer ( this, TID_GAME_RATING, TP_GAME_RATING_PERION );
        }

        break;
    default:
        break;
    }
}

void GSPanelButtonView::SetBtnsPic ( string strLanguagePic, string strRatingPic )
{
    m_strLangBtnPic = strLanguagePic;
    m_strRatingBtnPic = strRatingPic;
}

void GSPanelButtonView::OnActive ( bool enable )
{
  if ( enable == false)
  {
    m_pLanguageButton->Released();
    m_pRatingButton->Released();
  }
}

void GSPanelButtonView::OnTouch ( const InputEvent& inputData )
{
    if ( m_bDisableInput == true )
    {
        return;
    }

    if( m_bStartHideLangugageView == true )
    {
        return;
    }
    
    m_pRatingButton->Touch ( inputData );
    m_pLanguageButton->OnTouch ( inputData );
}

bool GSPanelButtonView::TrySetFocus ( const InputEvent& inputData )
{
    this->RestartTimerGameRating();
    return Utils::Instance().IsPointInPolygon ( POINT ( inputData.Touch1()->x(), inputData.Touch1()->y() ), Utils::Instance().convex_hull ( m_ViewRect.vPolygon ) );
}

void GSPanelButtonView::OnLanguageChange ( int16_t eLanguage )
{
    SPicDef* spdLabelChooseGame = m_pResourceMgr->GetMlPicture ( "LABEL_CHOOSE_GAME" );
    if ( spdLabelChooseGame == NULL )
    {
        eCDebug ( LOG_CATEGORY_HAT ) << "ERROR! NULL pointer m_spdLabelChooseGame!";
        return;
    }
    
    m_spdLabelChooseGame = spdLabelChooseGame;
    SetChooseGameLabelPos();
    
}

void GSPanelButtonView::OnTick ( int nID, int times )
{
    if ( nID == TID_GAME_RATING )
    {
        HatApplication::GetInstance().m_TimerMgr->StopTimer ( this, TID_GAME_RATING );
        m_bIsGameRatingPressed = false;

        HatNotifyMgr::NotifyMgr::Instance().SendBtnGameRatingPressed(m_bIsGameRatingPressed);
    }
}

void GSPanelButtonView::OnChangeTab ( int nTab, bool bFadeEffect, bool bFromTabView )
{
    if ( nTab != HatFacade::eAllGameRated )
    {
        HatApplication::GetInstance().m_TimerMgr->StopTimer ( this, TID_GAME_RATING );
        m_bIsGameRatingPressed = false;
    }
}

void GSPanelButtonView::OnSettingsGameRating ( bool bShow )
{
    SetShowGameRating ( bShow );
}

void GSPanelButtonView::OnShowLanguageView ( int nMenuState )
{
    if ( nMenuState == GSLanguageView::eStartShow )
    {
        m_pTouchDispatcher->SetFocus ( m_pLanguageButton );
        m_pLanguageButton->SetState ( eSelfRemove );
    }

    if ( ( nMenuState == GSLanguageView::eStartHide ) || ( nMenuState == GSLanguageView::eHide ) )
    {
        m_bStartHideLangugageView = bool ( nMenuState == GSLanguageView::eStartHide );
        m_pTouchDispatcher->RemoveFocus ( m_pLanguageButton );
        m_pLanguageButton->SetState ( eAutoRemove );
	
	ReleasedButtons();

    }
}

void GSPanelButtonView::OnDisableInput ( bool bDisableInput )
{
    m_bDisableInput = bDisableInput;
}

void GSPanelButtonView::OnStartSlide ( bool bStart, int32_t nDirection )
{
    m_bDisableInput = bStart;
    
    m_pLanguageButton->Released();
    m_pRatingButton->Released();
}

void GSPanelButtonView::OnStateChanged ( EStateDef sdOldState, EStateDef sdNewState )
{
    /** @TODO REFACTOR !!! */
    if ( HatApplication::GetInstance().m_TimerMgr->CheckIfTimerOn ( this, TID_GAME_RATING ) )
    {
        HatApplication::GetInstance().m_TimerMgr->StopTimer ( this, TID_GAME_RATING );
        m_bIsGameRatingPressed = false;

        HatNotifyMgr::NotifyMgr::Instance().SendBtnGameRatingPressed(m_bIsGameRatingPressed);
    }

    if ( sdNewState != esdGameSelect )
    {
        ReleasedButtons();
    }
}

void GSPanelButtonView::OnCreditChange(int64_t newCredit)
{
    this->RestartTimerGameRating();
}

void GSPanelButtonView::OnKeyboardEvent(const InputEvent::_SButtons& Buttons, const LogicalKeyboard& logKeyb)
{
    unsigned int uiButtons= ~Buttons.GetButtonState();
    if(uiButtons == 0)
    {
      return;
    }
  
    this->RestartTimerGameRating();
    }

void GSPanelButtonView::OnMaxPages(int nMaxPages, bool bAfterInit) {
    m_nNumberOfPages = nMaxPages;
    SetChooseGameLabelPos();
}

void GSPanelButtonView::SetChooseGameLabelPos() {
    if(m_nNumberOfPages > 1) {
        m_spdLabelChooseGame->m_DC.y = 911;
    }
    else {
        m_spdLabelChooseGame->m_DC.y = 982;
    }
}


}
