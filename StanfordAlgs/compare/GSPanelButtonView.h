#ifndef GSPANELBUTTONVIEW_H
#define GSPANELBUTTONVIEW_H

#include <egt_lib/mm_interfaces.h>
#include <hat/HatApplication.h>
#include "../../device_mgr/InputEvent.h"
#include "BaseButton.h"
#include "PanelLanguageButton.h"
#include "GSPanelButton.h"
#include "../interfaces/ITouchZone.h"
#include "../interfaces/INotifyClient.h"
#include "../interfaces/IKeyboardEvent.h"
#include "../TouchDispatcher.h"

namespace HatGameSelect
{

class GSPanelButtonView: public HatITouchZone::ITouchZone, public INotifyClient, public IKeyboardEvent, public ITimerClient
{
    /** Timer id for Game Rating button */
    static const int TID_GAME_RATING = 1;

    /** Timer perion for Game Rating button*/
    static const int TP_GAME_RATING_PERION = 30000;


    /**  */
    enum EButtonsID {
        eLanguage = 0,
        eRating
    };



    /** Pointer to basic draw functions */
    IBasicDraw* m_pBasicDraw;

    /** Pointer to basic sound functions */
    IBasicSound* m_pBasicSound;

    /** Pointer to resource manager */
    ResourceMgr* m_pResourceMgr;

    /** Pointer to touch dispatcher */
    HatTouchDispatcher::TouchDispatcher* m_pTouchDispatcher;

    /** Rating button */
    GSPanelButton* m_pRatingButton;

    /** Picture for label Language Frame */
    SPicDef* m_spdLangFrame = nullptr;
    POINT    m_pFrame;
    /** Language button */
    PanelLanguageButton* m_pLanguageButton;

    /** Picture for rating button */
    string m_strRatingBtnPic;

    /** Picture for language button  */
    string m_strLangBtnPic;

    /** Picture for label choose game */
    SPicDef* m_spdLabelChooseGame;

    /** Panel rectangle with buttons */
    RECT m_ViewRect;

    /** Language heigh */
    int m_nPictureLanguageHeight;

    /** Language width */
    int m_nPictureLanguageWidth;

    /** Rating heigh */
    int m_nPictureRatingHeight;

    /** Rating width */
    int m_nPictureRatingWidth;

    /** Flag for disableInput */
    bool m_bDisableInput;
    
    /** Flag indicates is button pressed */
    bool m_bIsGameRatingPressed;
    
    /** Flag for start hide of language view */
    bool m_bStartHideLangugageView;

    /** Offset betwen denoination and language buttons */
    int m_cnOffsetXBetweenBtn;
    int m_cnOffsetYBetweenBtn;
    int m_nNumberOfPages;
    /** Set flag for show game rating */
    void SetShowGameRating ( bool bShowGameRating );
    
    /** Recalcualation button positions */
    void RecalculationButtonsPosition ( bool bShowGameRating );
    
    /** Released buttons */
    void ReleasedButtons();
    
    /** Restart timer game rating */
    void RestartTimerGameRating();

    void SetChooseGameLabelPos();
public:

    /** Constructor */
    GSPanelButtonView();

    /** Constructor */
    GSPanelButtonView ( int nResolutionWidth, int nResolutionHeight );

    /** Destructor */
    virtual ~GSPanelButtonView();

    /** Clear all parameters */
    void Clear();

    /** Initialize button with pictuers
    * @param pResourceMgr - pointer to resource manager
    * @param pBasicDraw - pointer to draw interface
    * @param pBasicSound - pointer to sound interface
    * @param RectView - rectangle with buttons
    * @return success
    */
    bool Init ( ResourceMgr* pResourceMgr,IBasicDraw* pBasicDraw,IBasicSound* pBasicSound, HatTouchDispatcher::TouchDispatcher* pTouchDispatcher, RECT RectView );

    /** DeInit */
    void DeInit();

    /** Draw */
    void Draw();

    /** Set Buttons Pictures
    * @param strLanguagePic - Language button picture
    * @param strRatingPic - Game Rating button picture
    * @return success
    */
    void SetBtnsPic ( string strLanguagePic, string strRatingPic );

    /** OnActive - overrides function: notify for arriving event
    * @param enable - "true" for eTouch and eMove, "false" eUnTouch
    */
    virtual void OnActive ( bool enable );

    /** OnTouch
    * @param inputData - all input data, touch and button data
    */
    virtual void OnTouch ( const InputEvent& inputData );

    /** SetFocus - check touch coordinates if is in range of current view
    * @param inputData - all input data, touch and button data
    */
    virtual bool TrySetFocus ( const InputEvent& inputData );

    /** OnLanguageChange - notification for changed language from HAT */
    virtual void OnLanguageChange ( int16_t eLanguage );

    /** INotify overrides */
    virtual void OnShowLanguageView ( int nMenuState );

    /** ITimerClient override */
    virtual void OnTick ( int nID, int times );

    /** INotifyClient override */
    virtual void OnChangeTab ( int nTab, bool bFadeEffect, bool bFromTabView );

    /** INotifyClient override */
    virtual void OnSettingsGameRating ( bool bShow );

    /** INotifyClient override */
    virtual void OnDisableInput ( bool bDisableInput );
    
    /** INotify overrides */
    virtual void OnStartSlide ( bool bStart, int32_t nDirection );

    /** INotifyClient override */
    virtual void OnStateChanged ( EStateDef sdOldState, EStateDef sdNewState );
    
    /** INotifyClient override */
    virtual void OnCreditChange ( int64_t newCredit );
    
    /** IKeyboardEvent override */
    virtual void OnKeyboardEvent ( const InputEvent::_SButtons& Buttons, const LogicalKeyboard& logKeyb );
    
    /** Notify client overrides */
    virtual void OnMaxPages( int nMaxPages, bool bAfterInit );
    
    /** CbButtonPressed - pressed current button */
    void CbButtonPressed ( BaseButton* btn );

};

}
#endif // GSPANELBUTTONVIEW_H
