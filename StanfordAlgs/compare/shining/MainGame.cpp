
/* MainGame.cpp

	MainGame class; responsible for all states during the main game

	Author: Georgi Dragandjikov
	$Id: MainGame.cpp,v 1.1.2.5.2.12 2015/06/18 14:07:52 mustafa.bialkov Exp $

	Copyright (c) 2004-2007 EGT Ltd.
	All rights reserved

	More information at: http://www.egt-bg.com
 */

#include "MainGame.h"
#include "oled/KeyboardScenarioController.h"
#include "mm.h"
#include "ui_mgr/ButtonsUtil.h"
#include "gp_mgr/GPMgr.h"
#include "money_counting/MoneyCounting.h"
#include "game_state_mgr/GameStateMgr.h"
#include "device_mgr/ButtonDefs.h"
#include <project_definitions/hat_api/HatApi.h>
#include "status_line/StatusLine.h"
#include "game_draw_mgr/GameDrawManager.h"
#include "storage_mgr/StorageManagerApi.h"
#include "GameDefinitions.h"
#include <egt_lib/debug/egt_debug.h>
#include <egt_lib/utils/FormatFunc.h>
#include "jpm_mgr/JPMMgr.h"
#include "panel/PanelObject.h"
#include "p3_info/P3Info.h"
#include "busy_counting/BusyCounting.h"
#include "ml_mgr/MLMgr.h"
#include "GlobalError.h"
#include "game_gamble/Gamble.h"
#include "aft_mgr/AFTMgr.h"
#include <limits>
#include "option_bet_control/GameOptionSchema.h"
#include "option_bet_control/OptionAndBetControlAdapter.h"
#include "RestrictionComponents/GameReels/GameVariantsComponent.h"
#include "game_settings/CommonGameSettings.h"
#include "action_bridge/ActionBridgeMgr.h"
#include "screen_object/VideoControlMgr.h"
#include "ReelsDemo/Demo.h"
#include "ReelsDemo/DemoReelsArea.h"
//#include "IJurisdiction.h"
#include "../../hat/game_mgr/GameMgr.h"
#include "panel/DenominationControl.h"
#include <Components/RestrictionComponents/KeyboardCfg/VirtualKeyboardCfgComponent.h>
#include <Components/RestrictionComponents/GameConfiguration/BigWinDemoComponent.h>

using namespace std;
using namespace RestrictionComponents;

static const char* unNVRAMHitsIDs[]=
{
		"NVRAM_SCP_3THREE_CHERRY",
		"NVRAM_SCP_4FOUR_CHERRY",
		"NVRAM_SCP_5FIVE_CHERRY",

		"NVRAM_SCP_3THREE_LEMON",
		"NVRAM_SCP_4FOUR_LEMON",
		"NVRAM_SCP_5FIVE_LEMON",

		"NVRAM_SCP_3THREE_ORANGE",
		"NVRAM_SCP_4FOUR_ORANGE",
		"NVRAM_SCP_5FIVE_ORANGE",

		"NVRAM_SCP_3THREE_PLUM",
		"NVRAM_SCP_4FOUR_PLUM",
		"NVRAM_SCP_5FIVE_PLUM",

		"NVRAM_SCP_3THREE_BELL",
		"NVRAM_SCP_4FOUR_BELL",
		"NVRAM_SCP_5FIVE_BELL",

		"NVRAM_SCP_3THREE_GRAPES",
		"NVRAM_SCP_4FOUR_GRAPES",
		"NVRAM_SCP_5FIVE_GRAPES",

		"NVRAM_SCP_3THREE_WATERMELON",
		"NVRAM_SCP_4FOUR_WATERMELON",
		"NVRAM_SCP_5FIVE_WATERMELON",

		"NVRAM_SCP_2TWO_SEVEN",
		"NVRAM_SCP_3THREE_SEVEN",
		"NVRAM_SCP_4FOUR_SEVEN",
		"NVRAM_SCP_5FIVE_SEVEN",

		"NVRAM_SCP_3THREE_STAR",

		"NVRAM_SCP_3THREE_DOLLAR",
		"NVRAM_SCP_4FOUR_DOLLAR",
		"NVRAM_SCP_5FIVE_DOLLAR"
};

static void GetSlidingWindow( GameVariantsComponent::GameType gameType,
							  unsigned char nVariant,
							  unsigned int nReel,
							  unsigned int nMiddleIndex,
							  unsigned char* ucResult );

unsigned int MainGame::GetHitIDIndex( EFigure eFig, unsigned char ucFigCount )
{
    unsigned short usIndex = ( ( eFig * REELS_COUNT ) + ucFigCount - 1 );//from matrix to one dimention array
    if ( usIndex >= m_ausHitIDIndx.size() )
    {
        eCDebug(LOG_CATEGORY_GAMES) << __FILE__ << ":" << __LINE__ << " GetHitIDIndex failed! eFig:" << eFig << " ucFigCount:" << (int)ucFigCount;
        return 255;
    }

    return m_ausHitIDIndx.at( usIndex );
}

////////////////////////////////////////////////////
///HISTORY PARSER
////////////////////////////////////////////////////
namespace
{

struct Params
{
    int gameId = 0;
    int extraWild = 0;
    Credits betPerLine{0};
    Credits maxBetPerLine{0};
    PricePerCredit pricePerCredit{0_dollars};
    int32_t linesCount = 0;
    bool hasFreeGames{false};
};

void ParseGameData(analyzer::TurnResult& result, const history::TurnResults& gameData, Params params)
{

        int multiplier = 1;
        if(gameData.has_multipliers())
        {
            const auto& multipliers = gameData.multipliers();
            if(multipliers.has_winmultiplier())
            {
                multiplier = multipliers.winmultiplier().value();
            }
        }

        bool hasConditions = false;
        const auto& jpSize = gameData.jackpot_size();
       const auto& jackpots = gameData.jackpot();
     for(int i = 0; i < jpSize ; ++i )
        {
            const auto jackpot = jackpots.Get(i);

            if(jackpot.has_hasjpconditions())
            {
                hasConditions = jackpot.hasjpconditions().value();
            }

        }

        auto linesCount = params.linesCount;
        auto betPerLine = params.betPerLine;
        auto maxBetPerLine = params.maxBetPerLine;
        auto pricePerCredit = params.pricePerCredit;
        Currency crBets[MGDEFS_BET_LINES_COUNT];
        Currency crMaxBetPerLine = pricePerCredit * maxBetPerLine;
        Currency crBetPerLine = pricePerCredit * betPerLine;
        for( int i = 0; i < linesCount; i++ ){
            if( i < linesCount ){
                crBets[i] = crBetPerLine;
            }
            else{
                crBets[i] = 0;
            }
        }

        const auto& visibleReels = gameData.visiblereels();
        const auto& reels = visibleReels.reels();
        const auto reelsSize = visibleReels.reels_size();
        int mainGameFigues[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
        for(int i = 0; i < reelsSize; ++i)
        {
            const auto& reel = reels.Get(i);
            const auto& figures = reel.figures();
            const auto figuresSize = reel.figures_size();
            for(int j = 0; j < figuresSize; ++j)
            {
                const auto& figure = figures.Get(j);

                mainGameFigues[j][i] = figure.id(0);
            }
        }

        int extraWild = params.extraWild;
        Analyzer analyzer;
        analyzer.Init(mainGameFigues,
                      crBets,
                      hasConditions,
                      false,
                      int(crMaxBetPerLine),
                      int(crBetPerLine),
                      multiplier,
                      EFigure(extraWild) );

        auto gameId = params.gameId;
        AnalyzerResults analResults(gameId, GetGameRestrictionMgrGetter(), MGDEFS_BET_LINES_COUNT, REELS_COUNT);
        analyzer.GetResults(&analResults);


        auto linesResult = result.mutable_linesresult();
        if(params.hasFreeGames)
        {
            linesResult->mutable_multiplier()->set_value(multiplier);
        }
        auto resultReels = linesResult->mutable_visiblereels();
        for(int i = 0; i < REELS_COUNT; ++i)
        {
            auto reel = resultReels->add_reels();

            for(int j = 0; j < VISIBLE_FIGURES_PER_REEL; ++j)
            {
                auto figure = reel->add_figures();
                figure->add_id(analResults.nFigures[j][i]);
            }
        }

        for(int i = 0; i < analResults.GetWinLinesCount(); ++i)
        {
            auto line = linesResult->add_line();
            line->mutable_linenumber()->set_value(std::to_string(analResults.GetLineDataAt(i).nLine + 1));
            for(int j = 0; j < analResults.GetLineDataAt(i).nCount; ++j)
            {
                auto figureWin = line->mutable_figurewin();
                auto figure = figureWin->add_figures();
                figure->add_id(analResults.GetLineDataAt(i).eFigure);
            }
            line->mutable_winamount()->set_value(analResults.GetLineDataAt(i).currWin);
            if(analResults.nJPLine == analResults.GetLineDataAt(i).nLine)
            {
                line->mutable_jpwin()->set_value(hasConditions);
            }
        }

        if(analResults.GetLinesWin() > 0)
        {
            auto linesWin = linesResult->mutable_lineswin();
            linesWin->set_value(analResults.GetLinesWin());
        }

        if(analResults.GetScatterWin() > 0)
        {
            auto bonus = linesResult->mutable_bonus();
            auto scatter = bonus->add_bonuses();
            auto bonus_name = scatter->mutable_name();
            bonus_name->set_value("scatter");
            auto award = scatter->mutable_award();
            auto winAmount = award->mutable_winamount();
            if(analResults.crScatter1Win > 0)
            {
                winAmount->set_value(analResults.crScatter1Win.ToCents());
            }
            else if(analResults.crScatter2Win > 0)
            {
                winAmount->set_value(analResults.crScatter2Win.ToCents());
            }
            unsigned nScatter1Count = 0;
            unsigned nScatter2Count = 0;
            for(unsigned i = 0; i < REELS_COUNT; i++ )
            {
                if( analResults.nScatters1Pos[i] != (-1) )
                    nScatter1Count++;
                if( analResults.nScatters2Pos[i] != (-1) )
                    nScatter2Count++;
            }
            if(nScatter1Count > 2)
            {
                for(unsigned i=0 ;i < nScatter1Count;++i)
                {
                    auto figureWin = scatter->mutable_figurewin();
                    auto figure  = figureWin->add_figures();
                    figure -> add_id(ef10_star);
                }
            }
            if(nScatter2Count > 2)
            {
                for(unsigned i=0 ;i < nScatter2Count;++i)
                {
                    auto figureWin = scatter->mutable_figurewin();
                    auto figure  = figureWin->add_figures();
                    figure -> add_id(ef11_dollar);
                }
            }
            if(gameData.has_bonus())
            {
                const auto& bonusData = gameData.bonus();
                if(bonusData.has_freegames())
                {
                   auto freeGames = award->mutable_freegames();
                   freeGames->set_value(bonusData.freegames().value());
                }
            }

        }
        if( analResults.bSpecial )
        {
            auto specialReels = linesResult->mutable_jockers();
            for( int i = 0; i < REELS_COUNT; ++i )
            {
                auto reel = specialReels->add_reels();
                bool bSpecialReel = false;
                for( int j = 0; j < VISIBLE_FIGURES_PER_REEL; ++j )
                {
                    auto figure = reel->add_figures();
                    figure->add_id(analResults.nFigures[j][i]);
                    if (analResults.sJokers[i].nPos[j] != -1)
                    {
                        bSpecialReel = true;
                    }
                }
                if(bSpecialReel)
                {
                    reel->clear_figures();
                    for(int g = 0; g < VISIBLE_FIGURES_PER_REEL; ++g)
                    {
                        auto figure = reel->add_figures();
                        figure->add_id(static_cast<EFigure>(ef9_crown));
                    }
                }
            }
        }

        if(analResults.bBonus1)
        {
            auto bonus = linesResult->mutable_bonus();
            auto bonus1 = bonus->add_bonuses();
            auto bonus_name = bonus1->mutable_name();
            bonus_name->set_value("bonus1");
        }

        if(analResults.bBonus2)
        {
            auto bonus = linesResult->mutable_bonus();
            auto bonus2 = bonus->add_bonuses();
            auto bonus_name = bonus2->mutable_name();
            bonus_name->set_value("bonus2");
        }

}


analyzer::MatchResult GetAnalyzerResults(const history::Entry &entry, int gameId, int extraWild)
{

    Params params;
    params.gameId = gameId;
    params.extraWild = extraWild;

    const auto& entryInfo = entry.entryinfo();
    if(entryInfo.has_invoice())
    {
        const auto& invoice = entryInfo.invoice();
        if(invoice.has_pricepercredit())
        {
            params.pricePerCredit = PricePerCredit(Currency::FromCents(invoice.pricepercredit().value()));
        }
    }

    if(entryInfo.has_linesinfo())
    {
        const auto& linesInfo = entryInfo.linesinfo();

        if(linesInfo.has_betperline())
        {
            params.betPerLine = Credits(linesInfo.betperline().value());
        }
        if(linesInfo.has_maxbetperline())
        {
            params.maxBetPerLine = Credits(linesInfo.maxbetperline().value());
        }
        if(linesInfo.has_linescount())
        {
            params.linesCount = linesInfo.linescount().value();
        }
    }

    analyzer::MatchResult match;
    auto& matchInfo = *match.mutable_matchinfo();

    auto& id = *matchInfo.mutable_gameid();
    id.set_value(gameId);

    auto& name = *matchInfo.mutable_gamename();
    name.set_value("Shining Crown");

    auto& timestamp = *matchInfo.mutable_timestamp();
    timestamp = entryInfo.timestamp();

    auto& gameVariant = *matchInfo.mutable_gamevariant();
    gameVariant = entryInfo.gamevariant();

    auto& invoice = *matchInfo.mutable_invoice();
    invoice = entryInfo.invoice();

    auto& linesInfo = *matchInfo.mutable_linesinfo();
    linesInfo.mutable_linescount()->set_value(entryInfo.linesinfo().linescount().value());
    linesInfo.mutable_maxlinescount()->set_value(entryInfo.linesinfo().maxlinescount().value());
    linesInfo.mutable_betperline()->set_value(entryInfo.linesinfo().betperline().value());
    linesInfo.mutable_maxbetperline()->set_value(entryInfo.linesinfo().maxbetperline().value());

    auto& totalBetField = *matchInfo.mutable_totalbet();
    auto totalBetValue = params.pricePerCredit.cents*params.linesCount * params.betPerLine.GetValue();
    totalBetField.set_value(totalBetValue);

    auto& gameStartMeters = *match.mutable_gamestartmeters();
    gameStartMeters = entry.gamestartmeters();
    auto& gameStartCreditField = *gameStartMeters.mutable_totalcredit();
    auto gameStartCreditValue = gameStartCreditField.value();
    gameStartCreditValue += totalBetValue;
    gameStartCreditField.set_value(gameStartCreditValue);

    auto& gameEndMeters = *match.mutable_gameendmeters();
    gameEndMeters = entry.gameendmeters();

    auto mainGameResults = match.add_results();
    const auto& mainGameTurn = entry.maingame();
    ParseGameData(*mainGameResults, mainGameTurn, params);

    const auto& freeGames = entry.freegames();
    const auto& freeGameTurns = freeGames.turns();
    for(const auto& gameData : freeGameTurns)
    {
        auto freeGameResults = match.add_results();
        params.hasFreeGames = true;
        ParseGameData(*freeGameResults, gameData, params);
    }

    return match;
}
}
////////////////////////////////////////////////////

MainGame::MainGame()
	 	: m_ucState()
        , m_ausHitIDIndx()
	 	, m_ucLogFigResults()
	 	, m_ucDumpReelIndexes_1()
	 	, m_ucDumpReelIndexes_2()
	 	, m_bFirstTime(true)
	 	, m_ucReelsFastStop()
	 	, m_bUserAutoMode(false)
	 	, m_bIsAutoModeOff(false)
	 	, m_bUserAutoModeON(false)
	 	, m_bTestAutoMode(false)
	 	, m_bWinGame(false)
	 	, m_bFG(false)
	 	, m_bJpWon(false)
	 	, m_nExtraWild()
	 	, m_nFGOriginalCount()
	 	, m_nFGTotalCount()
	 	, m_nFGCount()
	 	, m_nFGMult()
	 	, m_bFGFastStoped(false)
	 	, m_bNeedToRecordBonusWin(false)
	 	, m_bBetButtonsPlay(false)
	 	, m_bLastGameIsFree(false)
	 	, m_bLastDraw(false)
	 	, m_nLastDrawCount(false)
	 	, m_nWinSplashCount()
	 	, m_bTimerLittleCounting(false)
	 	, m_nGameID()
	 	, m_ucButtonsState()
	 	, m_sndBettingPlus(nullptr)
	 	, m_sndGamble(nullptr)
	 	, m_sndInfo(nullptr)
	 	, m_sndCashOut(nullptr)
	 	, m_sndUserAutoModeIn(nullptr)
	 	, m_sndUserAutoModeOut(nullptr)
	 	, m_bAutoInSound(false)
	 	, m_ucBWDCombination()
        , m_AnalyzerResults( m_nGameID, GetGameRestrictionMgrGetter(), MGDEFS_BET_LINES_COUNT, REELS_COUNT )
        , m_ucVariant()
	 	, m_ucVariantLatestResults()
	 	, m_nJPLine()
{
}

MainGame::~MainGame()
{
}

bool MainGame::Init()
{
    auto& adaptor = egt::GetAdaptor();
    adaptor.getAnalyzerResults = [this](const history::Entry& entry)
    {
        return GetAnalyzerResults(entry, GetMainGameID(), m_nExtraWild);
    };

    if ( false == InitHitIDs() ) {
        eCDebug(LOG_CATEGORY_GAMES) << __FILE__ << ":" << __LINE__ << " InitHitIDs() FAIL "<< "\n";
        return false;
    }

	m_bLastDraw = false;
	m_nLastDrawCount = 0;

	m_bFG = false;
	m_nFGCount = 0;
	m_nFGOriginalCount = 0;
	m_nFGTotalCount = 0;
	m_nFGMult = 1;
	m_crFGMotherWin = 0;
	m_crFGWin = 0;
	m_crPureFGWin = 0;
	m_bFGFastStoped = false;
	m_bNeedToRecordBonusWin = false;
	m_crExtraGameWin = 0;

    m_AnalyzerResults.SetGameRestrictionMgr( GetGameRestrictionMgrGetter() ); // during MainGame::MainGame()
    m_AnalyzerResults.SetGameID( m_nGameID );

	if(!GetParameter("NVRAM_REELS_FAST_STOP", (void*)&m_ucReelsFastStop, sizeof(m_ucReelsFastStop)))
	{
		eCDebug( LOG_CATEGORY_GAMES ) << "Get NVRAM_REELS_FAST_STOP failed!\n";
		SetGeneralError(1300052);
	}

	unsigned char ucBetButtonsPlay;
	if(!GetParameter("NVRAM_BET_BUTTONS_NOT_PLAY", (void*)&ucBetButtonsPlay, sizeof(ucBetButtonsPlay)))
	{
		eCDebug( LOG_CATEGORY_GAMES ) << "Get NVRAM_BET_BUTTONS_NOT_PLAY failed!\n";
		SetGeneralError(1500001);
	}
	if (ucBetButtonsPlay == 0) m_bBetButtonsPlay = true;
	else m_bBetButtonsPlay = false;

	m_nExtraWild = FIGURES_NUM;

	m_bFirstTime = true;

	m_ucState = MG_STATE_BETTING;

	m_bLastGameIsFree = false;

	if(!m_reelsArea.Init()) {
	    eCDebug(LOG_CATEGORY_GAMES) << "[ SHINING CROWN ] - m_reelsArea::Init() FAIL  "<< "\n" ;
		return false;
	}

	if(!m_FGSeals.Init()) {
	    eCDebug(LOG_CATEGORY_GAMES) << "[ SHINING CROWN ] - m_FGSeals::Init() FAIL  "<< "\n" ;
		return false;
	}

	if(!m_WinSplash.Init()) {
	    eCDebug(LOG_CATEGORY_GAMES) << "[ SHINING CROWN ] - m_WinSplash::Init() FAIL  "<< "\n" ;
		return false;
	}

	if(!m_ExtraGame.Init() ) {
	    eCDebug(LOG_CATEGORY_GAMES) << "[ SHINING CROWN ] - m_ExtraGame::Init() FAIL  "<< "\n" ;
		return false;
	}

	if(!m_BigWinDemo.Init() ) {
	    eCDebug(LOG_CATEGORY_GAMES) << "[ SHINING CROWN ] - m_BigWinDemo::Init() FAIL  "<< "\n" ;
		return false;
	}

	m_nWinSplashCount = 0;


	m_ucBWDCombination = 255;

	m_nJPLine = (-1);

	m_ucVariant = 0;
	m_ucVariantLatestResults = 0;


	const char* nvram_parameter = gGPMgr.GetHybridParameter(eNvramGameVariant);
	if( !GetParameter(nvram_parameter, (void*)&m_ucVariant, sizeof( m_ucVariant ) ) ){
		eCDebug( LOG_CATEGORY_GAMES ) << "Get NVRAM_DRP_GAME_VARIANT failed!\n";
		SetGeneralError(910002);
	}

	ResetAutoMode();
    m_bTestAutoMode = false;
	m_bIsAutoModeOff = false;
	m_bWinGame = false;

	m_bTimerLittleCounting = false;

	int i = 0;
	for( ; i < REELS_COUNT; i++ ){
		m_ucDumpReelIndexes_1[i] = 0;
		m_ucDumpReelIndexes_2[i] = 0;
	}

	m_sndBettingPlus = gGameRM.GetSound( "MG_BETTING_PLUS_SOUND" );
	m_sndGamble = gGameRM.GetSound( "MG_BUTTON_DOUBLE" );
	m_sndInfo = gGameRM.GetSound( "MG_BUTTON_INFO" );
	m_sndCashOut = gGameRM.GetSound( "MG_BUTTON_CASHOUT" );

	m_sndUserAutoModeIn = gGameRM.GetSound( "USER_AUTO_MODE_IN" );
	m_sndUserAutoModeOut = gGameRM.GetSound( "USER_AUTO_MODE_OUT" );


//	if(gGPMgr.GetCurrentSeriesType() == eCollection){
		if(!gGameRM.GetRegister().RegisterPicture("JPA_KNOBS_BACKGROUND_US", FIRST_VIEW_GROUP)) {
			return false;
		}
//	}else{
//		if(!gGameRM.GetRegister().RegisterPicture("JPA_KNOBS_BACKGROUND", FIRST_VIEW_GROUP)) {
//			return false;
//		}
//	}

	gVBMgr.StartTimer( this, MG_TIMER_REELING_DRAW, 0, MG_PERIOD_REELING_DRAW );

	gGameStateMgr.RegisterClient( egscMGObject, this );
	gRecordMgr.AddClient( this );
	gGPMgr.AddClient( this );

	// Enable/Disable BigWinDemo //////////////////////////////
	m_BigWinDemo.SetToEnable( gGPMgr.GameSettings_Get().uchBigWinDemo ? true:false );
	///////////////////////////////////////////////////////////

	StartLastDraw();
	return true;
}

bool MainGame::InitHitIDs()
{
    m_ausHitIDIndx.fill( std::numeric_limits<unsigned char>::max() );
    unsigned short curHitIndex = 0;
    unsigned short arrayPos = 0;
    for ( auto &fig : gucWins )
    {
        for ( auto &winVal : fig )
        {
            if ( 0 != winVal )
            {
                m_ausHitIDIndx.at( arrayPos ) = curHitIndex;
                ++curHitIndex;
            }
            ++arrayPos;
        }
    }

    if ( curHitIndex != ( sizeof(unNVRAMHitsIDs) / sizeof(*unNVRAMHitsIDs) ) )
    {
        eCDebug(LOG_CATEGORY_GAMES) << __FILE__ << ":" << __LINE__ << " gucWins != unNVRAMHitsIDs curHitIndex=" << curHitIndex << " NVRAM:" << ( sizeof(unNVRAMHitsIDs) / sizeof(*unNVRAMHitsIDs) );
        return false;
    }

    return true;
}

void MainGame::DeInit()
{
	m_ExtraGame.Deinit();
}

void MainGame::LoadResources()
{

}

void MainGame::UnloadResources()
{

}

bool MainGame::StateChanging( bool bStackDirection, EGameStateDef gsdOldState, EGameStateDef gsdNewState )
{

	return true;
}

bool MainGame::StateChanged( bool bStackDirection, EGameStateDef gsdOldState, EGameStateDef gsdNewState )
{
	if( (gsdOldState == egsdMGBonusWin || gsdOldState == egsdFGBonusWin ) &&
			( gsdNewState == egsdMGBetting || gsdNewState == egsdMGBettingPlus || gsdNewState == egsdFGBetting ) ){
		m_reelsArea.SetScatterStarted( false );
	}

	if (bStackDirection == true && gsdNewState == egsdMGBettingPlus)
		gpBasicSound->StartSound( m_sndBettingPlus, true );

	if( (gsdNewState == egsdMGNormalWin) ||(gsdNewState == egsdMGBonusWin) ){
		m_bWinGame = true;
	}

	if( gsdNewState == egsdMGReeling || gsdNewState == egsdFGReeling ){//BUG 20238 #4
		if ( m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted() == true )//fast stop coin anim if pre interupted before wait time
		{
			m_reelsArea.m_ActionMgr.StopCoinAnim(true);
		}
	}

    if( gsdNewState == egsdGamble && gsdOldState == egsdMGBettingPlus )
    {
        m_reelsArea.m_ActionMgr.StopCoinAnim(true);
    }

	if( ( gsdNewState == egsdMGBonusWin && gsdOldState == egsdBonus_1 ) ||
			( gsdNewState == egsdMGBonusWin && gsdOldState == egsdBonus_2 ) ){

		m_ucState = MG_STATE_WINSPLASH;

		m_bWinGame = true;
	}
	else if( (gsdNewState == egsdMGBetting || gsdNewState == egsdMGBettingPlus ) && gsdOldState == egsdMGBonusWin ){
		SetBettingButtons();
		if(gsdNewState == egsdMGBetting){
			gGPMgr.SetGameMode();
			gRecordMgr.EndGame( m_bWinGame, m_bWinGame );
		}
		m_crFGWin = 0;
		m_crFGMotherWin = 0;

	}

	else if( gsdNewState == egsdBonus_1 && gsdOldState == egsdMGBonusWin ){

		gStatusLine.ClearAllModes();

		m_bUserAutoMode = false;
		m_bAutoInSound = false;
		m_bUserAutoModeON = false;
		m_bTestAutoMode = false;
		m_reelsArea.SetScatterStarted( false );

	}

	// free games //////////////////////////////////////////////////////////////////
	else if( gsdNewState == egsdMGBonusWin && gsdOldState == egsdFGBetting ){
		m_reelsArea.m_ActionMgr.m_AnimMgr.StopSounds ();

		if(m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted() )
		{
			m_reelsArea.m_ActionMgr.StopCoinAnim();
		}

		gMoneyCounting.SetSilentMode(false);
		//m_reelsArea.m_ActionMgr.StopAction();

		gStatusLine.ClearAllModes();


		m_bNeedToRecordBonusWin = true;

		m_bWinGame = true;
		if( gGPMgr.GameSettings_Get().ui16AutoGames ){
			m_bTestAutoMode = true;
		}

	}
	else if( gsdNewState == egsdFGBetting && gsdOldState == egsdMGBonusWin ){
		if( m_nFGCount > 0 ){
			StartAutoFG();
		}
		SetBettingButtons();
		gMoneyCounting.SetSilentMode(false);
		m_bTestAutoMode = false;

	}
	else if( gsdNewState == egsdFGReeling && gsdOldState == egsdFGBetting ){
	}
	else if( gsdNewState == egsdFGBetting && gsdOldState == egsdFGReeling ){
		if( m_nFGCount > 0 ){
			StartAutoFG( m_bFGFastStoped );
		}
		SetBettingButtons();
	}
	else if( gsdNewState == egsdFGBonusWin && gsdOldState == egsdFGReeling ){
	}
	else if( gsdNewState == egsdFGBonusWin && gsdOldState == egsdBonus_1 ){
		m_ucState = MG_STATE_WINSPLASH;
		gMoneyCounting.SetSilentMode(false);
		m_nFGCount += m_nFGOriginalCount;

	}
	else if( gsdNewState == egsdBonus_1 && gsdOldState == egsdFGBonusWin ){
		m_reelsArea.SetScatterStarted( false );
	}
	else if( gsdNewState == egsdFGBonusWin && gsdOldState == egsdFGScatterGame ){
	}
	else if( gsdNewState == egsdFGScatterGame && gsdOldState == egsdFGBonusWin ){
	}
	else if( gsdNewState == egsdFGBetting && gsdOldState == egsdFGBonusWin ){
		if( m_nFGCount > 0 ){
			StartAutoFG();
		}
		SetBettingButtons();
	}
	else if( gsdNewState == egsdFGNormalWin && gsdOldState == egsdFGReeling ){
	}
	else if( gsdNewState == egsdInfo && gsdOldState == egsdFGBetting ){
		gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );
	}
	else if( gsdNewState == egsdFGBetting && gsdOldState == egsdInfo ){
		StartAutoFG();
		SetBettingButtons();
	}
	else if( gsdNewState == egsdFGBetting && gsdOldState == egsdFGNormalWin ){
		if( m_nFGCount > 0 ){
			StartAutoFG( m_bFGFastStoped );
		}
		SetBettingButtons();
	}
	////////////////////////////////////////////////////////////////////////////////

	else if( gsdNewState == egsdMGReeling && gsdOldState == egsdMGBettingPlus ){
		gGPMgr.SetGameMode();
		gGPMgr.SetBigWinDemoFlag( false );
		gRecordMgr.EndGame( m_bWinGame, m_bWinGame );
	}
	else if( gsdNewState == egsdMGBetting &&
			(gsdOldState == egsdMGBonusWin || gsdOldState == egsdMGNormalWin ) ){
		SetBettingButtons();
		gGPMgr.SetGameMode();
		gRecordMgr.EndGame( m_bWinGame, m_bWinGame );
	}
	else if( gsdNewState == egsdMGBetting && gsdOldState == egsdGamble ){
		m_ucState = MG_STATE_BETTING;
		SetBettingButtons();
		gGPMgr.SetGameMode();
		////////////////////////////////////////////
	}
	else if( gsdNewState == egsdMGBetting && gsdOldState == egsdMGBettingPlus ){
		m_ucState = MG_STATE_BETTING;
		SetBettingButtons();
		gGPMgr.SetGameMode();
		gRecordMgr.EndGame( m_bWinGame, m_bWinGame );
	}
	else if( gsdNewState == egsdMGBettingPlus ){
		SetBettingButtons();
	}
	else if( gsdNewState == egsdMGBetting && gsdOldState == egsdMGReeling ){
		m_ucState = MG_STATE_BETTING;
		SetBettingButtons();
		gRecordMgr.EndGame( m_bWinGame, m_bWinGame );
	}
	else if( gsdNewState == egsdMGBetting && gsdOldState == egsdExtraGame ){
		m_ucState = MG_STATE_BETTING;
		SetBettingButtons();
		m_crExtraGameWin = gGPMgr.Win_Get();
		if(m_crExtraGameWin > 0){
			gGPMgr.bExtraGamePaymentMode = true;
		}
		gRecordMgr.EndGame( m_bWinGame, m_bWinGame );
		if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() )
			gP3Info.StartLastDraw();
		gGPMgr.SetGameMode();
	}
	else if( gsdNewState == egsdMGBetting ){
		m_ucState = MG_STATE_BETTING;
		SetBettingButtons();
		gGPMgr.SetBigWinDemoFlag( false );
	}
	else if( gsdOldState == egsdMGScatterGame ){
		if( m_bUserAutoModeON ){
			m_bUserAutoMode = true;
			SetDisabledButtons();
			m_bUserAutoModeON = false;
		}
		if( gGPMgr.GameSettings_Get().ui16AutoGames )
			m_bTestAutoMode = true;
		m_bWinGame = true;
	}
	if( gsdOldState == egsdMGReeling ){
		m_bLastGameIsFree = false;
		gRecordMgr.GetDump()->uchLimitExceeded = 0;
	}
	//drop down big win demo flag
	if((gsdNewState == egsdMGBetting)||(gsdNewState == egsdMGBettingPlus)){
		gGPMgr.SetBigWinDemoFlag( false );
	}
	////////////////////////////////////////////////////

	// always hide bet-lines //////////////////////////////////
	if( gsdOldState != egsdMGReeling )  {

		if( ( (gsdOldState == egsdBusyGap) && (gsdNewState == egsdMGBetting) ) ||
		( (gsdNewState == egsdBusyGap) && (gsdOldState == egsdMGBetting) ) ) {

			//do not hide lines
		}
		else {
			m_reelsArea.m_ActionMgr.m_LinesMgr.HideLines();
		}
	}

	if ( gsdNewState == egsdBusy && gsdOldState == egsdMGBetting)
	{

	    ResetAutoMode();

		SetDisabledButtons();
	}

	if ( gsdNewState == egsdLangSelect && gsdOldState == egsdMGBetting)
	{
	    ResetAutoMode();
		SetDisabledButtons();
	}

	if ( gsdNewState == egsdGamble) {
        if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() ){

			//BUG 20206 #8 Recover default screen after big coin anim if timer hasn't finished
			if ( gVBMgr.StopTimer( &m_reelsArea.m_ActionMgr, 4 ) )//4 == TID_COIN_ANIM_DELAY_STOP
			{
				gP3Info.ShowDefaultScreen(false,true);
			}

			gP3Info.ShowScreen( eInfoDoubleUp );
		}
	}


//JPM CHANGES START ======== JPM CHANGES START //

	if ( (gsdNewState == egsdJPMProgressive) && bStackDirection ) //progressive start
	{

	    ResetAutoMode();
		m_bWinGame = true;

//		SetDisabledButtons();

		if( m_bFG ){
			gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );
		}

		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);

		if(gsdOldState == GSM_UNUSED_LEVEL) {

			gVBMgr.StopTimer(this, MG_TIMER_PROGRESSIVE_RECOVER);
			gVBMgr.StartTimer(this, MG_TIMER_PROGRESSIVE_RECOVER, 1);

		}
	}

	else if ( (gsdOldState == egsdJPMProgressive) && !bStackDirection ) //progressive end
	{

/*
		if( m_ucState == MG_STATE_SCATTERGAME || m_ucState == MG_STATE_BONUSGAME || gGameStateMgr.GetCurrentState() == egsdMGBonusWin ){
			SetDisabledButtons();
		}
		else{
			SetBettingButtons();
		}
*/

		if( m_bFG && m_nFGCount > 0 ) {
			StartAutoFG();
		}
		else if( m_bFG ){
			// return in MGBetting(Plus)
			SwitchInFGBetting();
		}
		m_nJPLine = (-1);

		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);
		gVBMgr.StartTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE, MG_PERIOD_START_SERVICE_AUTO_MODE );

	}

	else if ( (gsdNewState == egsdJPMExternal) && bStackDirection ) //mystery start
	{

		ResetAutoMode();

		//SetDisabledButtons();
		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);

	}

	else if ( (gsdOldState == egsdJPMExternal) && !bStackDirection ) //mystery end
	{

		//SetBettingButtons();
		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);
		gVBMgr.StartTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE, MG_PERIOD_START_SERVICE_AUTO_MODE );

	}

	else if ( (gsdNewState == egsdJPMBusy) && bStackDirection ) //netsplash start
	{

		if( m_bFG ){
			gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );
		}

		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);

		ResetAutoMode();


	}

 	else if ( (gsdOldState == egsdJPMBusy) && !bStackDirection ) //netsplash end
	{

		if( m_bFG && m_nFGCount > 0 ) {
			StartAutoFG();
		}
		else if( m_bFG ){
			// return in MGBetting(Plus)
			SwitchInFGBetting();
		}

		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);
		gVBMgr.StartTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE, MG_PERIOD_START_SERVICE_AUTO_MODE );

	}

	else if ( (gsdNewState == egsdBusyGap) && bStackDirection )
	{

		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);

		SetDisabledButtons();

	}
	else if(  (gsdOldState == egsdBusyGap) && !bStackDirection ) {

		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);
		gVBMgr.StartTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE, MG_PERIOD_START_SERVICE_AUTO_MODE );


		if(gActionBridgeMgr.GetBridgeType() == ActionBridge::eTNone) {

			SetBettingButtons();

		}

	}

//JPM CHANGES END =========== JPM CHANGES END //

	return true;
}

void MainGame::OnDraw( bool bParentRedrawn )
{
	if( m_bFirstTime ){

		m_bFirstTime = false;

		if( m_ucState == MG_STATE_REELING ){
			DoStartButton( true );
		}

		else if( m_ucState == MG_STATE_SCATTERGAME ) {

			if( gGameStateMgr.GetCurrentState() != egsdJPMProgressive) {
				m_reelsArea.SetScatterStarted( true );
			}
			else{
				m_ucState = MG_STATE_WINDEMO;
			}
		}

	}

	gpBasicDraw->SetColor( 255, 255, 255, 255 );

//	if(gGPMgr.GetCurrentSeriesType() == eCollection){
		gpBasicDraw->DrawPicture( 0, 0, 0, gGameRM.GetPicture( "JPA_KNOBS_BACKGROUND_US" ) );
//	}else{
//		gpBasicDraw->DrawPicture( 0, 0, 0, gGameRM.GetPicture( "JPA_KNOBS_BACKGROUND" ) );
//	}

	m_reelsArea.Draw();


	if( m_ucState == MG_STATE_WINSPLASH  ){
		//m_WinSplash.Draw();
	}

	if((!m_bFG ) && ( m_ucState != MG_STATE_WINSPLASH) && ( m_ucState == MG_STATE_BETTING || m_ucState == MG_STATE_BIGWINDEMO)){
		m_BigWinDemo.Draw( m_ucState == MG_STATE_BIGWINDEMO  );
	}


	if ( m_ucState == MG_STATE_EXTRAGAME )
	{
		m_ExtraGame.Draw();
	}

}

void MainGame::OnButton( const InputData &inputData )
{
	if( m_ucState == MG_STATE_EXTRAGAME )
	{

		m_ExtraGame.OnButton( inputData );

		return;
	}

	if( inputData.uiPressed && m_bTestAutoMode ){
		m_bTestAutoMode = false;
		return;
	}

	if( inputData.uiButtons == BUTTON_STARTSTOP){
		m_bIsAutoModeOff = false;
	}

	// user demo mode ///////////////////////////////////////////////
	if( m_bUserAutoMode ) {
		if( inputData.uiButtons == BUTTON_AUTO && inputData.uiPressed == BUTTON_AUTO ){
			gpBasicSound->StopSound( m_sndUserAutoModeIn );
			gpBasicSound->StartSound( m_sndUserAutoModeOut );
			m_bUserAutoMode = false;
			m_bAutoInSound = false;

			if(m_ucState == MG_STATE_REELING){
				m_bIsAutoModeOff = true;
			}
		}
		if( inputData.uiButtons == BUTTON_INFO && inputData.uiPressed == BUTTON_INFO ){
			if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() ){
			  //vk bug 18819
			  // gpBasicSound->StartSound( m_sndInfo );
			  // gP3Info.ShowNextScreen();
			}
		}
		if( inputData.uiButtons & BUTTON_STARTSTOP && inputData.uiPressed == BUTTON_STARTSTOP ){
			if(GetActionType() == RAAM_ACTIONTYPE_WILD_DEMO){/**Bug fix:20495*/
				return;
			}
			if( gMoneyCounting.GetLeftAmount() != 0 ){
				gMoneyCounting.SetFastMode();
				m_bFGFastStoped = true;
				SetDisabledButtons();
			}
			else{
				if( (m_reelsArea.GetRAStatus() == RA_STATUS_REELING_CAN_STOP )	||
				(m_reelsArea.GetRAStatus() == RA_STATUS_REELING_CAN_NOT_STOP) )
				{
				m_reelsArea.StartButton();
				}
// 				DoStartButton(); //vk bug 19111
			}
		}
		if( inputData.uiButtons == BUTTON_CASHOUT && inputData.uiPressed == BUTTON_CASHOUT ){ //vk bug 19111
			m_bUserAutoModeON = false;
			m_bUserAutoMode = false;
			gpBasicSound->StartSound( m_sndCashOut );
			if ( gGPMgr.Credit_Get() > 0 ){
				 m_reelsArea.m_ActionMgr.StopAction();
			}
			GameToHatData( GAME_TO_HAT_START_CASHOUT, NULL, 0 );
		}
		return;
	}
	if (m_bUserAutoModeON)
	{
		if (inputData.uiButtons == BUTTON_AUTO
				&& inputData.uiPressed == BUTTON_AUTO)
		{
		    ResetAutoMode();
			return;
		}
	}
	/////////////////////////////////////////////////////////////////

	// IMPORTANT: must be the first object to receive buttons and touch

	//	   m_AttractionDemo.OnButton(inputData);
	HideAttraction();

	// the only moment of muti-button functionallity /////////////////////////////////////////////
	if( m_reelsArea.GetRAStatus() == RA_STATUS_REELING_CAN_STOP &&
			!( inputData.uiButtons & BUTTON_INFO) ){

		if ( !m_ucReelsFastStop && !m_bFG ) return;

		if( inputData.uiButtons & BUTTON_STARTSTOP && inputData.uiPressed != BUTTON_STARTSTOP ){
			return;
		}

		if( inputData.uiPressed == BUTTON_STARTSTOP ){
			DoStartButton();
		}
		else{
			// Spain 2 jurisdiction
			//bug 20709
			if( inputData.uiPressed & BUTTON_B1 ||
			    inputData.uiPressed & BUTTON_B2 ||
			    inputData.uiPressed & BUTTON_B3 ||
			    inputData.uiPressed & BUTTON_B4 ||
			    inputData.uiPressed & BUTTON_B5 ){
			  m_reelsArea.StopAllReels();
			}
			}

		// added from Stancho			*****************************
		// begin
		OnTouch( inputData.touchData1.bPressed, inputData.touchData1.x, inputData.touchData1.y );
		// end							*****************************

		return;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////

	// added from Stancho				*****************************
	// begin
	if( inputData.touchData1.bPressed || inputData.touchData1.bPressedNow )
	{
		if( inputData.uiButtons || inputData.uiPressed ){
			return;
		} else {
			OnTouch( inputData.touchData1.bPressed, inputData.touchData1.x, inputData.touchData1.y );
			return;
		}
	}
	// end								*****************************
	//////////////////////////////////////////////////////////////////////////////////////////////////

	const std::vector<int> optValues = gBetLinesControlAdapter.GetOptionVals(); //vk

	if( inputData.uiButtons == BUTTON_L1 && inputData.uiPressed == BUTTON_L1 ){

		if( !ProcessLinesButton( optValues.at(0) ))return;
	}

	if( inputData.uiButtons == BUTTON_L2 && inputData.uiPressed == BUTTON_L2 ){

		if( !ProcessLinesButton( optValues.at(1) )) return;
	}

	if( inputData.uiButtons == BUTTON_L3 && inputData.uiPressed == BUTTON_L3 ){

		if( !ProcessLinesButton( optValues.at(2) )) return;
	}

	if( inputData.uiButtons == BUTTON_L4 && inputData.uiPressed == BUTTON_L4 ){

		if( !ProcessLinesButton( optValues.at(3) )) return;
	}

	if( inputData.uiButtons == BUTTON_L5 && inputData.uiPressed == BUTTON_L5 ){

		if( !ProcessLinesButton( optValues.at(4) )) return;
	}

	if( inputData.uiButtons == BUTTON_B1 && inputData.uiPressed == BUTTON_B1 ){

		if( !ProcessBetButton(gBetLinesControlAdapter.GetBetValue(0), 0) ) return;
	}

	if( inputData.uiButtons == BUTTON_B2 && inputData.uiPressed == BUTTON_B2 ){

		if( !ProcessBetButton(gBetLinesControlAdapter.GetBetValue(1), 1) ) return;
	}

	if( inputData.uiButtons == BUTTON_B3 && inputData.uiPressed == BUTTON_B3 ){

		if( !ProcessBetButton(gBetLinesControlAdapter.GetBetValue(2), 2) ) return;
	}

	if( inputData.uiButtons == BUTTON_B4 && inputData.uiPressed == BUTTON_B4 ){

		if( !ProcessBetButton(gBetLinesControlAdapter.GetBetValue(3), 3) ) return;
	}

	if( inputData.uiButtons == BUTTON_B5 && inputData.uiPressed == BUTTON_B5 ){

		if( !ProcessBetButton(gBetLinesControlAdapter.GetBetValue(4), 4) ) return;
	}

	if( (inputData.uiButtons == BUTTON_GAMBLE_SELBET && inputData.uiPressed == BUTTON_GAMBLE_SELBET) ){

		if( gMoneyCounting.GetLeftAmount() != 0 ) {

			gMoneyCounting.SetFastMode();
			SetDisabledButtons();
		}
		else if ( egsdMGBettingPlus == gGameStateMgr.GetCurrentState() )
		{
			gpBasicSound->StopAllSounds();
			gGameStateMgr.RequestState( egsdGamble );
			gpBasicSound->StartSound( m_sndGamble );
		}
		else if ( egsdMGBetting == gGameStateMgr.GetCurrentState() )
		{
			FromBettingPlusToBetting();
			if( SwitchInJPState() ){
				return;
			}
			m_reelsArea.m_ActionMgr.StopAction();
			gBetLinesControlAdapter.DoButtonSelBet();
		}
	}

	if (inputData.uiButtons == BUTTON_GAMBLE_SELLINE && inputData.uiPressed == BUTTON_GAMBLE_SELLINE)
	{
		if( gMoneyCounting.GetLeftAmount() != 0 ) {

			gMoneyCounting.SetFastMode();
			SetDisabledButtons();
		}
		else if ( egsdMGBettingPlus == gGameStateMgr.GetCurrentState() )
		{
			gpBasicSound->StopAllSounds();
			gGameStateMgr.RequestState( egsdGamble );
			gpBasicSound->StartSound( m_sndGamble );
		}
		else if ( egsdMGBetting == gGameStateMgr.GetCurrentState() )
		{
//			FromBettingPlusToBetting();
			if( SwitchInJPState() ){
				return;
			}
			m_reelsArea.m_ActionMgr.StopAction();

//			unsigned int nLinesToSet = gGPMgr.NextScreenLineSelection ();
//			SetLine( nLinesToSet );
			gBetLinesControlAdapter.DoButtonSelLine();

		}
	}

	if( inputData.uiButtons == BUTTON_CASHOUT && inputData.uiPressed == BUTTON_CASHOUT ){
		gpBasicSound->StartSound( m_sndCashOut );
		if ( gGPMgr.Credit_Get() > 0 ){
			m_reelsArea.m_ActionMgr.StopAction();
		}
		GameToHatData( GAME_TO_HAT_START_CASHOUT, NULL, 0 );
	}

	if( inputData.uiButtons == BUTTON_INFO && inputData.uiPressed == BUTTON_INFO ){
		//vk bug 18819
//		if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() )
//		{
//			gpBasicSound->StartSound( m_sndInfo );
//			gP3Info.ShowNextScreen();
//		}
		//vk bug 19150
//		if( m_bFG && m_nFGCount > 0 ){
//			StartAutoFG();
//		}
	}

	if( inputData.uiButtons == BUTTON_STARTSTOP && inputData.uiPressed == BUTTON_STARTSTOP ){
		// button start/stop

		//Sopotski
		if(m_ucButtonsState == MG_BUTTONS_STATE_DISABLED)
		{
			return;
		}

		if( gMoneyCounting.GetLeftAmount() != 0 ){
			gMoneyCounting.SetFastMode();
			m_bFGFastStoped = true;
			SetDisabledButtons();
		}
		else{
			if( m_ucState == MG_STATE_BETTING_PLUS ){
				//vk bug 19265
				if (gBetLinesControlAdapter.GetLastPlayedState() == AOptionAndBetControlAdapter::eLeftover){
					if ( gKeyboardScenarioController->GetButtonEKbFunction(BTN_STARTSTOP) == KbButton::eTakeWin )/**Bug fix: 20481*/
						TakeWin();
					else
						StartCreditCounting();
				}
				else StartTakeWinCounting();

			}
			else if( m_ucState == MG_STATE_BETTING ||
					m_ucState == MG_STATE_REELING ){
				if( !gGPMgr.GameSettings_Get().ui16AutoGames ){
					gGPMgr.SetStopAuto( true );
				}
				else{
					m_bTestAutoMode = true;
				}
				DoStartButton();
			}
			else if( gMoneyCounting.GetLeftAmount() == 0 && m_ucState == MG_STATE_WINSPLASH ){
				m_nWinSplashCount = MG_WINSPLASH_TIMES + 1;
			}
			else if( (m_ucState == MG_STATE_SCATTERGAME) && (m_ucButtonsState == MG_BUTTONS_STATE_WAIT_FAST)){
				SetDisabledButtons();
			}
		}
	}

	if( inputData.uiButtons == BUTTON_TAKEWIN && inputData.uiPressed == BUTTON_TAKEWIN ){
	  

	//vk
	if( gMoneyCounting.GetLeftAmount() != 0 ) {
		gMoneyCounting.SetFastMode();
		SetDisabledButtons();
	}
	else{
		//bug 19556
		// if ( m_ucState == MG_STATE_BETTING_PLUS ){
		//   StartTakeWinCounting();
		// }
		if ( gKeyboardScenarioController->GetButtonEKbFunction(BTN_TAKEWIN) == KbButton::ePlayMaxBet ){
		  if ( gBetLinesControlAdapter.MaxOptionAndBetPossible(true) && !m_bUserAutoMode ){
		if ( m_ucState == MG_STATE_BETTING ){
		  DoStartButton();
		}
		  }
		}
		else if ( gKeyboardScenarioController->GetButtonEKbFunction(BTN_TAKEWIN) == KbButton::eTakeWin ){ //bug 19556
		  TakeWin();
		}
        else if ( gKeyboardScenarioController->GetButtonEKbFunction(BTN_TAKEWIN) == KbButton::eSelectBet )
        {
            auto keyboardCfg = GetGameComp_VirtualKeyboardCfg();
            if (keyboardCfg->IsAvailable())
            {
                if ( egsdMGBetting == gGameStateMgr.GetCurrentState() )
                {
                    if( SwitchInJPState() ){
                        return;
                    }
                    m_reelsArea.m_ActionMgr.StopAction();
                    gBetLinesControlAdapter.DoButtonSelBet();
                }
            }
        }
  }
	}

	if( inputData.uiButtons == BUTTON_AUTO && inputData.uiPressed == BUTTON_AUTO ){
		// auto
		if( !gGPMgr.GameSettings_Get().uchPlayerAutoMode &&
				gGameStateMgr.GetCurrentState() != egsdGamble ){
			if( m_bUserAutoMode ){
				m_bUserAutoMode = false;
				m_bAutoInSound = false;
				gpBasicSound->StopSound( m_sndUserAutoModeIn );
				gpBasicSound->StartSound( m_sndUserAutoModeOut );
			}
			else{
				if( gGameStateMgr.GetCurrentState() == egsdMGBetting ){
					m_bUserAutoMode = true;
					m_bAutoInSound = true;
					DoStartButton();
				}
				// Vega Vision behaviour /////////////
				else if( gGameStateMgr.GetCurrentState() == egsdMGBettingPlus ){
				//vk necessary when exiting leftover with a win
				  if (gKeyboardScenarioController->GetButtonEKbFunction(BTN_AUTO) != KbButton::eTakeWin){
					m_bUserAutoMode = true;
					m_bAutoInSound = true;
				  }
				  StartTakeWinCounting();
				}
				else if( gMoneyCounting.GetLeftAmount() != 0 ) {
					gMoneyCounting.SetFastMode();
					SetDisabledButtons();
					return;
				}
				//////////////////////////////////////
			}
		}

	}
}

void MainGame::SetBettingButtons()
{
	if (gGPMgr.GetHatCurrState() != esdReadyGame &&gGPMgr.GetHatCurrState() != esdReadyGamePlus &&
			gGPMgr.GetHatCurrState() != esdBusyGame && gGPMgr.GetHatCurrState() != esdBonus &&
			gGPMgr.GetHatCurrState() != esdBonusBusy && gGPMgr.GetHatCurrState() != esdGameLangSelect ){
		return;
	}

	if(gGameStateMgr.GetCurrentState() == egsdLangSelect || gGameStateMgr.GetCurrentState() == egsdGamble) {
		return;
	}

	if( m_ucState == MG_STATE_BIGWINDEMO || m_ucState == MG_STATE_EXTRAGAME ||
			m_ucState == MG_STATE_BONUSGAME || m_ucState == MG_STATE_SCATTERGAME ||
			m_ucState == MG_STATE_CREDIT_COUNTING){
		return;
	}
	if( m_bUserAutoMode || m_bTestAutoMode || m_bUserAutoModeON ){
		SetDisabledButtons();
		return;
	}

	if( m_bFG ){
		SetDisabledButtons();

		if( m_nFGCount == 0 && gGameStateMgr.GetCurrentState() != egsdBonus_1 ){
			return;
		}

		m_ucButtonsState = MG_BUTTONS_STATE_BETTING;

		return;
	}

	m_ucButtonsState = MG_BUTTONS_STATE_BETTING;
}

void MainGame::SetReelingButtons()
{

	if( m_bUserAutoModeON || m_bTestAutoMode ){
		SetDisabledButtons();
		return;
	}

	m_ucButtonsState = MG_BUTTONS_STATE_REELING;
}

void MainGame::SetWaitingReelsButtons()
{
	m_ucButtonsState = MG_BUTTONS_STATE_WAIT_REELS;
}

void MainGame::SetWaitForFastCollctButtons()
{
	m_ucButtonsState = MG_BUTTONS_STATE_WAIT_FAST;
}

void MainGame::SetDisabledButtons()
{

	m_ucButtonsState = MG_BUTTONS_STATE_DISABLED;
}

void MainGame::SetNewGameResults( unsigned char ucCombination )
{
	int i = 0, j = 0;

	EFigure efResults[REELS_COUNT][ALL_FIGURES_PER_REEL];
	int nConfTmp[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
    auto results = GetGameComp_BigWinDemo()->GetCombination(ucCombination, m_BigWinDemo.GetCurrentPage());

    for (size_t i = 0; i < REELS_COUNT; ++i)
    {
        for(size_t j = 0; j < ALL_FIGURES_PER_REEL; ++j)
        {
            efResults[i][j] = static_cast<EFigure>(results.at(j).at(i));
            if(m_bFG == false)
            {
                m_efResultsToShowAfterFG[i][j] = efResults[i][j];
            }

            if( j > 0 && j < VISIBLE_FIGURES_PER_REEL+1 )
            {
                nConfTmp[j-1][i] = results.at(j).at(i);
            }
        }
    }

	// last 50 result values //////////////////////////////////////
	for( i = 0; i < REELS_COUNT; i++ ){
		for ( j = 0; j < VISIBLE_FIGURES_PER_REEL; j++ )
			m_ucLogFigResults[j][i] = nConfTmp[j][i];
	}
	///////////////////////////////////////////////////////////////

	Analyzer analyzer;
	Currency crBets[MGDEFS_BET_LINES_COUNT];
	int nLinesCount = gGPMgr.LinesCount_Get();
	Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
	for( i = 0; i < MGDEFS_BET_LINES_COUNT; i++ ){
		if( i < nLinesCount ){
			crBets[i] = crBetPerLine;
		}
		else{
			crBets[i] = 0;
		}
	}
	int nCurrMult = 1;
	if (m_bFG){
		nCurrMult = m_nFGMult;
	}

	analyzer.Init( nConfTmp, crBets,
			HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
			HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
			gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
			gGPMgr.BetPerLine_Get(), nCurrMult, (EFigure) m_nExtraWild );

	analyzer.GetResults( &m_AnalyzerResults );
	m_reelsArea.SetResults( efResults, m_AnalyzerResults );

	// if not in free games set JpWon always to false
	if ( !m_bFG )
		m_bJpWon = false;

	// jackpot ////////////////////////////////////////////////////////////
	m_nJPLine = (-1);
	if (m_AnalyzerResults.bJPWon){
		m_nJPLine = m_AnalyzerResults.nJPLine;
		m_bJpWon = true;
	}
	///////////////////////////////////////////////////////////////////////

}


void MainGame::SetNewGameResults()
{
	if( m_ucBWDCombination != 255 ){
		SetNewGameResults( m_ucBWDCombination );
		m_ucBWDCombination = 255;
		return;
	}

	m_ucVariantLatestResults = m_ucVariant;
	int i = 0, j = 0;
	int nResults[REELS_COUNT][ALL_FIGURES_PER_REEL];
	for( ; i < REELS_COUNT; i++ ){

		unsigned char ucResults[ALL_FIGURES_PER_REEL];
		GetRealResult( i, ucResults );
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){
			nResults[i][j] = ucResults[j];
		}

	}

	eCDebug(LOG_CATEGORY_GAMES) << "RESULTS: " << nResults[0][1] << "\t" << nResults[1][1] << "\t" << nResults[2][1] << "\t" << nResults[3][1] << "\t" << nResults[4][1] << "\n"
								<<"\t\t\t\t   "<< nResults[0][2] << "\t" << nResults[1][2] << "\t" << nResults[2][2] << "\t" << nResults[3][2] << "\t" << nResults[4][2] << "\n"
								<<"\t\t\t\t   "<< nResults[0][3] << "\t" << nResults[1][3] << "\t" << nResults[2][3] << "\t" << nResults[3][3] << "\t" << nResults[4][3] << "\n";

	EFigure efResults[REELS_COUNT][ALL_FIGURES_PER_REEL];
	int nConfTmp[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
	for( i = 0; i < REELS_COUNT; i++ ){// reels
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){ // raws
			efResults[i][j] = (EFigure)nResults[i][j];
			if( !m_bFG ){
				m_efResultsToShowAfterFG[i][j] = efResults[i][j];
			}
			if( j > 0 && j < VISIBLE_FIGURES_PER_REEL+1 ){
				nConfTmp[j-1][i] = nResults[i][j];
			}
		}
	}

	// last 50 result values //////////////////////////////////////
	for( i = 0; i < REELS_COUNT; i++ ){
		for ( j = 0; j < VISIBLE_FIGURES_PER_REEL; j++ )
			m_ucLogFigResults[j][i] = nConfTmp[j][i];
	}
	///////////////////////////////////////////////////////////

	Analyzer analyzer;
	Currency crBets[MGDEFS_BET_LINES_COUNT];
	int nLinesCount = gGPMgr.LinesCount_Get();
	Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
	for( i = 0; i < MGDEFS_BET_LINES_COUNT; i++ ){
		if( i < nLinesCount ){
			crBets[i] = crBetPerLine;
		}
		else{
			crBets[i] = 0;
		}
	}

	int nCurrMult = 1;
	if (m_bFG){
		nCurrMult = m_nFGMult;
	}

	analyzer.Init( 	nConfTmp, crBets,
			HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
			HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
			gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
			gGPMgr.BetPerLine_Get(), nCurrMult,  (EFigure) m_nExtraWild );

	analyzer.GetResults( &m_AnalyzerResults );
#ifdef EGT_CREDIT_OBSERVER //define when EGT_DEBUG=1
    if (debCreditObserver::getInstance().isAcive())
    {
        debCreditObserver::getInstance().setCurrentWon(m_AnalyzerResults.GetMainGameWin().m_n64Data);
        if (debCreditObserver::getInstance().getShoHideSplash())
        {
            m_reelsArea.m_ActionMgr.StopAction();
            m_bUserAutoMode = false;
        }
    }
#endif
	m_reelsArea.SetResults( efResults, m_AnalyzerResults );

	// jackpot ////////////////////////////////////////////////////////////
	m_nJPLine = (-1);
	gRecordMgr.GetDump()->ucWonPJP = 0;

	// if not in free games set JpWon always to false
	if ( !m_bFG )
		m_bJpWon = false;

	if( m_AnalyzerResults.bJPWon ){
		m_nJPLine = m_AnalyzerResults.nJPLine;
		gRecordMgr.GetDump()->ucWonPJP = 1;
		m_bJpWon = true;
	}
	///////////////////////////////////////////////////////////////////////

}


void MainGame::OnJPMProgressiveReady() {

	gVBMgr.StopTimer(this, MG_TIMER_PROGRESSIVE_RECOVER);

}


void MainGame::OnTick( int nID, int times )
{
	if( m_bFirstTime ){
		return;
	}
#ifdef EGT_CREDIT_OBSERVER //define when EGT_DEBUG=1
    if (debCreditObserver::getInstance().getAnalyzerResults == nullptr && debCreditObserver::getInstance().isAcivePlayHistoryTotalCreditObserver())
    {
        debCreditObserver::getInstance().getAnalyzerResults = [this](const history::Entry& entry)
        {
            return GetAnalyzerResults(entry, GetMainGameID(), m_nExtraWild);
        };
    }
#endif

	if(nID == MG_TIMER_PROGRESSIVE_RECOVER) {

		uint32_t ui32Level = 0;
		GameToHatData( GAME_TO_HAT_JP_GAME_READY, (const void*)&ui32Level, sizeof(ui32Level) );

	}

	else if( nID == MG_TIMER_REELING_DRAW ){


		if( m_reelsArea.ReadyForBonus1() ){
			m_ucState = MG_STATE_BONUSGAME;
			//m_ucState = MG_STATE_BETTING;
			//gGameStateMgr.BackToPreviousState();
			gGameStateMgr.RequestState( egsdBonus_1 );
		}

		if( m_reelsArea.ReadyForBonus2() ){
			//m_ucState = MG_STATE_BONUSGAME;
			m_ucState = MG_STATE_BETTING;
			gGameStateMgr.BackToPreviousState();
			//gGameStateMgr.RequestState( egsdBonus_2 );
		}

		if( m_reelsArea.ReadyForScatter() ){

			// second edition start fg splash ///////////////////////////
			if( !m_bFG && !m_bTestAutoMode ){

				if ( m_bUserAutoMode )
				{
					m_bUserAutoMode = false;
					m_bAutoInSound = false;
					m_bUserAutoModeON = false;
				}

				// start splash
				//m_WinSplash.StartFSIntro();

				m_ucState = MG_STATE_WINSPLASH;
				//gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
			}
			else {
				if( !m_bFG ){
					gRecordMgr.RecordData();
				}

				m_ucState = MG_STATE_WINSPLASH;
				//m_WinSplash.SetFGScatterWin( 15, 3 );
				if ( m_bFG )
				{
					//m_WinSplash.StartFSRetrigger();

					if(m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted() )
					{
						m_reelsArea.m_ActionMgr.StopCoinAnim();
					}

					gGPMgr.SetDemoMode();
				}
				else
				{
					// service auto games
					//m_WinSplash.StartFSIntro();
				}
				gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
			}
			//////////////////////////////////////////////////////////////
		}

		// examine the reels area state ///////////////////////
		switch( m_ucState ){
		case MG_STATE_BETTING:
			break;
		case MG_STATE_BETTING_PLUS:
			break;
		case MG_STATE_REELING:
			if( m_reelsArea.GetRAStatus() == RA_STATUS_STOPPED_READY ){
				if( m_ucState != MG_STATE_BETTING_PLUS ){
					m_ucState = MG_STATE_BETTING;

					// check for user auto mode /////////////////
					if( m_bUserAutoMode ){
						StartTakeWinCounting();
					}
					else if( m_bTestAutoMode ){
						FromBettingPlusToBetting();
						if( !SwitchInJPState() ){
							DoStartButton();
						}
					}
					else{
						SetBettingButtons();
					}
					/////////////////////////////////////////////

				}
			}
			else if( m_reelsArea.GetRAStatus() == RA_STATUS_STOPPED_BUSY ){
				m_bWinGame = true;

				if (m_reelsArea.m_ActionMgr.m_ucActionType == RAAM_ACTIONTYPE_WILD_DEMO) {
					m_ucState = MG_STATE_WILD_SHOW_DEMO;
				}

				else {
					m_ucState = MG_STATE_WINDEMO;
				}
				if( m_reelsArea.m_ActionMgr.m_bScatter_Exist ){
					//if( m_bUserDemoMode )
					//	m_bUserAutoModeON = true;
					// about the two scatter situation m_bUserDemoMode = false;
					if (gMoneyCounting.GetLeftAmount() == 0){
						if( m_ucButtonsState != MG_BUTTONS_STATE_DISABLED ){
							SetDisabledButtons();
						}
					}
					else{
						if( m_ucButtonsState != MG_BUTTONS_STATE_WAIT_FAST ){
							SetWaitForFastCollctButtons();
						}
					}
				}
				else if( m_reelsArea.m_ActionMgr.m_bBonus1_Exist ||
						m_reelsArea.m_ActionMgr.m_bBonus2_Exist ){
					if( m_bUserAutoMode ){
						m_bUserAutoModeON = true;
					}
					m_bUserAutoMode = false;
					m_bAutoInSound = false;
					if( gMoneyCounting.GetLeftAmount() == 0 ){
						if( m_ucButtonsState != MG_BUTTONS_STATE_DISABLED ){
							SetDisabledButtons();
						}
					}
					else{
						if( m_ucButtonsState != MG_BUTTONS_STATE_WAIT_FAST ){
							SetWaitForFastCollctButtons();
						}
					}
				}
				else{
					if( m_ucButtonsState != MG_BUTTONS_STATE_WAIT_FAST ){
						SetWaitForFastCollctButtons();
					}
				}
		}
			else if( m_reelsArea.GetRAStatus() == RA_STATUS_REELING_CAN_NOT_STOP ){
				if( m_ucButtonsState != MG_BUTTONS_STATE_WAIT_REELS )
					SetWaitingReelsButtons();
			}
			break;

		case MG_STATE_WINDEMO:
//			if(gGPMgr.GetCurrentSeriesType() == eCollection){
				if(m_reelsArea.CoinAnimCanStart()){
					m_reelsArea.m_ActionMgr.m_CoinAnim.SetCurrency(gMoneyCounting.GetLeftAmount());
				}
//			}
			if( m_reelsArea.m_ActionMgr.m_bBonus1_Exist ||
					m_reelsArea.m_ActionMgr.m_bBonus2_Exist ){
				if( m_ucButtonsState != MG_BUTTONS_STATE_DISABLED ){
					SetDisabledButtons();
				}
			}


			if( m_reelsArea.GetScatterStarted() ){
				m_ucState = MG_STATE_SCATTERGAME;
			}
			else if( m_reelsArea.m_ActionMgr.m_bBonus1_Exist ){
				m_ucState = MG_STATE_BONUSGAME;
			}
			else if( m_reelsArea.m_ActionMgr.m_bBonus2_Exist ){
				m_ucState = MG_STATE_BONUSGAME;
			}
			else if( gMoneyCounting.GetLeftAmount() == 0 ){

				// if(gGPMgr.GetCurrentSeriesType() == eCollection){
					m_reelsArea.m_ActionMgr.m_CoinAnim.SetCurrency(gMoneyCounting.GetLeftAmount());
//				}
				if( SwitchInJPState() ){
					return;
				}

				// check for user auto mode /////////////////
				if( (m_bUserAutoMode || m_bTestAutoMode) && !m_bJpWon ){
					m_ucState = MG_STATE_BETTING_PLUS;
					gGameStateMgr.RequestState( egsdMGBettingPlus );

					if( m_bUserAutoMode ){
						StartTakeWinCounting();
					}
					else if( m_bTestAutoMode ){
						FromBettingPlusToBetting();
						if( !SwitchInJPState() ){
							DoStartButton();
						}
					}

					return;
				}
				else{
					SetBettingButtons();
				}
				/////////////////////////////////////////////

				if( m_bFG ){
					SwitchInFGBetting();
				}
				else{
					// change state (Betting or BettingPlus) /////////////////
					if( IsDoubleUpOK() ){

						// request to BettingPlus
						m_ucState = MG_STATE_BETTING_PLUS;
						gGameStateMgr.RequestState( egsdMGBettingPlus );
					}
					else{
						// back to Betting
						m_ucState = MG_STATE_BETTING;
						gGameStateMgr.BackToPreviousState();
						gGPMgr.SetGameMode();
					}
					//////////////////////////////////////////////////////////
				}
				SetBettingButtons();

			}

			if( !m_reelsArea.m_ActionMgr.m_bThereIsUndoneScatter &&
					!m_reelsArea.m_ActionMgr.m_bThereIsUndoneBonus1 &&
					!m_reelsArea.m_ActionMgr.m_bThereIsUndoneBonus2 ){
				if( m_bFG && (m_nFGCount == 0) ){
					// after start of the last free game
				}
				else{
					if( SwitchInJPState() ){
						return;
					}
				}
			}
			break;

		case MG_STATE_SCATTERGAME:
			if( !m_reelsArea.GetScatterStarted() ){
				m_ucState = MG_STATE_WINSPLASH;
				gMoneyCounting.SetSilentMode(false);

				//m_WinSplash.SetScatterWin( gGPMgr.Get_SplashBonusTimesTotalBet() );

				gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
				gGPMgr.SetDemoMode();
				gMoneyCounting.StartCounting( gGPMgr.Get_SplashBonusLastWin(),
						gGPMgr.GameSettings_Get().cPointValue );
				gMoneyCounting.StartCollectSound();
				SetWaitForFastCollctButtons();

				// change state ///////////////////////////////////
				gGameStateMgr.BackToPreviousState();
				///////////////////////////////////////////////////

			}
			break;

		case MG_STATE_BONUSGAME:
			break;

		case MG_STATE_WINSPLASH:

			if( m_nFGCount > 0 && gGameStateMgr.GetCurrentState() == egsdMGBonusWin ){
				m_reelsArea.BonusFinished();
				//not used
				//m_JPArea.Stop();
				//m_FGJPArea.Start();
				m_bFG = true;

				SwitchInFGBetting();
			}

			break;

		case MG_STATE_EXTRAGAME:
			if ( m_bWinGame && 0 == gMoneyCounting.GetLeftAmount() )
			{
				// We've won in extra game and counting has finished
				m_ExtraGame.Stop();

			}
			break;
		case MG_STATE_WILD_SHOW_DEMO:
			if (m_reelsArea.m_ActionMgr.m_AnimMgr.IsWildShowingFinished()) {
				m_ucState = MG_STATE_WINDEMO;
			}
			break;

		default:
			break;
		}
		///////////////////////////////////////////////////////

		Refresh();

	}
	else if( nID == MG_TIMER_WINSPLASH ){

		if( !m_WinSplash.IsShown() ){

			gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH );
			SetBettingButtons();
			m_nWinSplashCount = 0;
			if( m_WinSplash.GetMode() == WSPLASH_MODE_SCATTER_WIN ){

				if( !m_bFG ){
					if(	IsDoubleUpOK() ){
						m_ucState = MG_STATE_BETTING_PLUS;
					}
					else{
						m_ucState = MG_STATE_BETTING;
					}
				}
				else{
					m_ucState = MG_STATE_BETTING;
				}

				//gRecordMgr.GetDump()->uchScatterState = SG_SCENARIO_BEGINNING;

				m_reelsArea.ScatterFinished();

				SwitchInJPState();

			}
			else if( m_WinSplash.GetMode() == WSPLASH_MODE_BONUS_WIN ){
				m_reelsArea.BonusFinished();
				m_reelsArea.m_ActionMgr.m_AnimMgr.Start(false);

				// change state (Betting or BettingPlus) /////////////////
				if(	IsDoubleUpOK() && (m_crFGWin > 0 || m_crFGMotherWin > 0) ){
					m_ucState = MG_STATE_BETTING_PLUS;
					gGameStateMgr.RequestState( egsdMGBettingPlus );
				}
				else{
					m_ucState = MG_STATE_BETTING;
					gGameStateMgr.BackToPreviousState();
				}
				//////////////////////////////////////////////////////////

				SwitchInJPState();

			}
			else if( m_WinSplash.GetMode() == WSPLASH_MODE_FG_BONUS_WIN ||
					m_WinSplash.GetMode() == WSPLASH_MODE_FG_RETRIGGER_WIN ){

				m_nFGCount += m_nFGOriginalCount;
				m_nFGTotalCount += m_nFGOriginalCount;

				m_FGSeals.AddFG( m_nFGOriginalCount, false );
				gVBMgr.StopTimer( this, MG_TIMER_FG_COUNTING );
				gVBMgr.StartTimer( this, MG_TIMER_FG_COUNTING, MG_PERIOD_FG_COUNTING );

				gMoneyCounting.SetSilentMode( false );
				m_bUserAutoMode = false;
				m_bAutoInSound = false;

				m_reelsArea.BonusFinished();
				SwitchInFGBetting();

				SetDisabledButtons();

			}
			else if( m_WinSplash.GetMode() == WSPLASH_MODE_FG_SCATTER_WIN ){

				if( m_nFGCount == 0 ){
					m_bLastGameIsFree = true;
				}

				m_ucState = MG_STATE_BETTING;
				m_reelsArea.ScatterFinished();

			}

			if( (m_bUserAutoMode || m_bTestAutoMode) && !m_bFG ){
				if( m_bUserAutoMode ){
					StartTakeWinCounting();
				}
				else if( m_bTestAutoMode ){
					FromBettingPlusToBetting();
					if( !SwitchInJPState() ){
						DoStartButton();
					}
				}
				return;
			}

		}

	}

	else if( nID == MG_TIMER_FG_AUTOSTART ){


		gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );

		if( m_nFGCount > 0 ){
			DoStartButton();
		}

	}

	else if( nID == MG_TIMER_FG_COUNTING ){

		if( gGameStateMgr.GetCurrentState() != egsdFGBetting ){
			gVBMgr.StopTimer( this, MG_TIMER_FG_COUNTING );
			return;
		}

		gVBMgr.StopTimer( this, MG_TIMER_FG_COUNTING );
		SetBettingButtons();

		StartAutoFG( false, true );

	}

	else if( nID == MG_TIMER_START_FS_OUTRO ){

		gVBMgr.StopTimer( this, MG_TIMER_START_FS_OUTRO );

		Currency crBonusWin = gGPMgr.Win_Get();
		m_crFGWin = crBonusWin;


		// Vega Vision //////////////////////
		if( SwitchInJPState() ){
			return;
		}
		/////////////////////////////////////



		// if the outro splash is started after clearing the error splash, skip returning to previous state
		// if the outro spalsh is starting after recovering in FGBetting state - skip returning to previous state
		if ( (gGPMgr.GetHatPrevState() != esdSASBlockScreen &&
			  gGPMgr.GetHatPrevState() != esdNoSasPjpInfo &&
			  gGPMgr.GetHatPrevState() != esdNoCbjsPjpInfo ) &&
			 gGameStateMgr.GetCurrentState() != egsdFGBetting )
		{
			gGameStateMgr.BackToPreviousState();
		}


		// if there is an error condition after switching the states, do nothing
		if ( gGPMgr.GetHatCurrState() != esdSASBlockScreen &&
             gGPMgr.GetHatCurrState() != esdNoSasPjpInfo &&
			 gGPMgr.GetHatCurrState() != esdNoCbjsPjpInfo )
		{
			gGameStateMgr.BackToPreviousState();
			m_bLastGameIsFree = true;

			m_ucState = MG_STATE_WINSPLASH;
			gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
			m_WinSplash.SetBonusWinAfterFG( crBonusWin );
		}

	}
	else if( nID == MG_TIMER_START_SERVICE_AUTO_MODE )
	{
		gVBMgr.StopTimer(this, nID);

		if( IsNetOK() ){
			if( gGPMgr.GameSettings_Get().ui16AutoGames ){

				// change state (Betting or BettingPlus) /////////////////
				if( gGameStateMgr.GetCurrentState() == egsdMGNormalWin ){
					if(	IsDoubleUpOK() ){

						m_ucState = MG_STATE_BETTING_PLUS;

						// request to BettingPlus
						gGameStateMgr.RequestState( egsdMGBettingPlus );

					}
					else{
						m_ucState = MG_STATE_BETTING;
						// back to Betting
						gGameStateMgr.BackToPreviousState();
						gGPMgr.SetGameMode();
					}
					//////////////////////////////////////////////////////////
				}
				SetBettingButtons ();


				m_bTestAutoMode = true;
				if( !SwitchInJPState() ){
					DoStartButton();
				}
			}
		}
	}
	else if ( nID == MG_TIMER_CREDIT_COUNTING ){

		if( gMoneyCounting.GetLeftAmount() == 0 ){
			FromBettingPlusToBetting( true );
			gVBMgr.StopTimer( this, nID );
			m_bTimerLittleCounting = false;
		}
	}
}

void MainGame::SwitchInFGBetting()
{
	if( gGameStateMgr.GetCurrentState() == egsdMGBonusWin && m_nFGCount > 0 ){
		// exiting from bonus and entering the free games

		m_ucState = MG_STATE_BETTING;
		gGameStateMgr.RequestState( egsdFGBetting );

		return;
	}

	if( m_nFGCount == 0 ) {


		bool bProgressiveFocus = false;
		GameToHatData( GAME_TO_HAT_JP_PROGRESSIVE_FOCUS, (const void*)&bProgressiveFocus, sizeof(bProgressiveFocus) );

		// must return to MGBonusWin
		m_ucState = MG_STATE_BETTING;
		/*		if( SwitchInJPState() ){
			m_reelsArea.m_ActionMgr.StartAction();
		}
		else{*/
		gVBMgr.StopTimer( this, MG_TIMER_START_FS_OUTRO );
		gVBMgr.StartTimer( this, MG_TIMER_START_FS_OUTRO, MG_PERIOD_START_FS_OUTRO );
		SetDisabledButtons();
		// this flag is moved in FS_OUTRO timer
		//m_bLastGameIsFree = true;
		//		}

		return;
	}

	m_ucState = MG_STATE_BETTING;

	// change state ///////////////////////////////////
	gGameStateMgr.BackToPreviousState();
	///////////////////////////////////////////////////

	// check for user auto mode /////////////////
	if( m_bTestAutoMode ){
		if( !SwitchInJPState() ){
			DoStartButton();
		}
	}
	else{
		SetBettingButtons();
	}
	/////////////////////////////////////////////
}

void MainGame::SetStateAfterReeling()
{
	if( m_reelsArea.GetRAStatus() == RA_STATUS_STOPPED_READY ){

		if( m_bFG ){
			SwitchInFGBetting();
			if( SwitchInJPState() ){
				m_reelsArea.m_ActionMgr.StartAction();
			}
			return;
		}

		if ( 0 != GetExtraGameWin() )
		{
			// stop user auto mode (if on)
			m_bUserAutoMode = false;
			m_bUserAutoModeON = false;
			m_bAutoInSound = false;

			m_ucState = MG_STATE_EXTRAGAME;
			m_ExtraGame.Start();

			return;
		}

		m_ucState = MG_STATE_BETTING;

		// change state ///////////////////////////////////
		gGameStateMgr.BackToPreviousState();
		///////////////////////////////////////////////////

		if( SwitchInJPState() ){
			m_reelsArea.m_ActionMgr.StartAction();
			return;
		}

		// check for user auto mode /////////////////
		if( m_bUserAutoMode ){
			StartTakeWinCounting();
		      if (gBetLinesControlAdapter.GetState()
				      != AOptionAndBetControlAdapter::eRegular)
		      { //vk
		          ResetAutoMode();
			}
		}
		else if( m_bTestAutoMode ){
			if( !SwitchInJPState() ){
				DoStartButton();
			}
		}
		else{
			SetBettingButtons();
		}
		/////////////////////////////////////////////

	}
}

void MainGame::DoStartButton( bool bRecover )
{
	if(m_ucState == MG_STATE_REELING || gBetLinesControlAdapter.AllowPlay()){ //vk, || order matters
	// this request to turn The Hat to BusyGame (or BonusBusy) is with lowest priority,
	// so we check the Hat state is it appropriate
	if( m_reelsArea.GetRAStatus() == RA_STATUS_STOPPED_READY ){
		if( gGPMgr.GetHatCurrState() != esdReadyGame &&
				gGPMgr.GetHatCurrState() != esdBusyGame &&
				gGPMgr.GetHatCurrState() != esdBonus &&
				gGPMgr.GetHatCurrState() != esdBonusBusy ){
			return;
		}
	}
	///////////////////////////////////////////////////////////////////

	StartLastDraw();

	if( m_reelsArea.GetRAStatus() == RA_STATUS_STOPPED_READY && !m_bFG ){
		// about to start reeling
		int nLinesCount = gGPMgr.LinesCount_Get();
		Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
		Currency crTotalBet = crBetPerLine * nLinesCount;
		if( !bRecover ){
			if( crTotalBet > gGPMgr.Credit_Get() || !IsNetOK() ){
				// there's not enought credit for this bet
				m_bUserAutoMode = false;
				m_bAutoInSound = false;
				m_bTestAutoMode = false;
				SetBettingButtons();
				return;
			}
		}
	}

	if( m_reelsArea.StartButton() ){
		// it's a start

		m_bFGFastStoped = false;

		if( m_bAutoInSound ){
			gpBasicSound->StartSound( m_sndUserAutoModeIn );
			m_bAutoInSound = false;
		}

		if( m_bTestAutoMode &&
				gGPMgr.GameSettings_Get().ui16AutoGames && !m_bFG ){
			gGPMgr.DecrementAutoGames();
			if( gGPMgr.GameSettings_Get().ui16AutoGames == 0 ){
				m_bTestAutoMode = false;
			}
		}

		if( !m_bFG )
		{
			gGPMgr.Win_Reset();
		}

		if( !bRecover ){
			SetNewGameResults();
		}
		else{
			int nConfTmp[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
			int j = 0;
			int i = 0;
			EFigure efResults[REELS_COUNT][ALL_FIGURES_PER_REEL];
			for( i = 0; i < REELS_COUNT; i++ ){
				unsigned char ucResults[ALL_FIGURES_PER_REEL];
				GetRealResult( i, ucResults, gRecordMgr.GetDump()->ucReelsPositions_2[i] );
				for ( j = 0; j < ALL_FIGURES_PER_REEL; j++ )
					efResults[i][j] = (EFigure)ucResults[j];
			}

			for( i = 0; i < REELS_COUNT; i++ ){
				for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){
					if( j > 0 && j < VISIBLE_FIGURES_PER_REEL+1 ){
						nConfTmp[j-1][i] = efResults[i][j];
					}
				}
			}

			Analyzer analyzer;
			Currency crBets[MGDEFS_BET_LINES_COUNT];
			int nLinesCount = gGPMgr.LinesCount_Get();
			Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
			for( i = 0; i < MGDEFS_BET_LINES_COUNT; i++ ){
				if( i < nLinesCount ){
					crBets[i] = crBetPerLine;
				}
				else{
					crBets[i] = 0;
				}
			}

			int nCurrMult = 1;
			if (m_bFG){
				nCurrMult = m_nFGMult;
			}

			analyzer.Init( nConfTmp, crBets,
					HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
					HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
					gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
					gGPMgr.BetPerLine_Get(), nCurrMult,  (EFigure) m_nExtraWild );

			analyzer.GetResults( &m_AnalyzerResults );
			m_reelsArea.SetResults( efResults, m_AnalyzerResults, false, bRecover );

			if (m_AnalyzerResults.bJPWon){
				m_nJPLine = m_AnalyzerResults.nJPLine;
				gRecordMgr.GetDump()->ucWonPJP = 1;//bobby
			}

		}

		if( !bRecover ){

			if( m_bFG ){

				if( m_nJPLine != (-1) ){
					uint32_t ui32Level = 0;
					GameToHatData( GAME_TO_HAT_JP_HIT, (const void*)&ui32Level, sizeof(ui32Level) );
				}

				m_ucState = MG_STATE_REELING;

				m_nFGCount--;
				m_FGSeals.ReduceFG();

				gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );

				// change state ///////////////////////////////////
				gGameStateMgr.RequestState( egsdFGReeling );
			}
			else{

				gGPMgr.SetGameMode();
				int nLinesCount = gGPMgr.LinesCount_Get();
				Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
				Currency crTotalBet = crBetPerLine * nLinesCount;
				gGPMgr.Credit_DeductBet( crTotalBet );

				if( m_nJPLine != (-1) ){
					uint32_t ui32Level = 0;
					GameToHatData( GAME_TO_HAT_JP_HIT, (const void*)&ui32Level, sizeof(ui32Level) );
				}

				gGPMgr.Win_Reset();

				m_ucState = MG_STATE_REELING;

				// change state ///////////////////////////////////
				if( gGameStateMgr.GetCurrentState() == egsdMGBettingPlus ){
					// VEGA VISION behaviour ////////////////
					FromBettingPlusToBetting();
					//gGameStateMgr.BackToPreviousState();
					gGameStateMgr.RequestState( egsdMGReeling );
					/////////////////////////////////////////
				}
				else{
					gGameStateMgr.RequestState( egsdMGReeling );
				}

			}

		}
		///////////////////////////////////////////////////

		SetReelingButtons();
		gStatusLine.ClearAllModes();

		gGameDrawMgr.RefreshAll();

		if( gGPMgr.GameSettings_Get().ui16AutoGames ){
			if( !m_bFG ){
				m_bTestAutoMode = true;
			}
			else{
				m_bTestAutoMode = false;
			}
		}
		else{
			m_bTestAutoMode = false;
		}
	}
	else{
		// it's a stop
		m_bFGFastStoped = true;
	}

	if ((m_AnalyzerResults.bJPWon) && (!m_bFG)) {
		m_bWinGame = true;
	}
	else{
		m_bWinGame = false;
	}
  }
}

void MainGame::OnTouch( bool bTouch, unsigned short usX, unsigned short usY )
{
	if( !bTouch ){
		return;
	}

	if( m_bIsAutoModeOff == true && m_ucState == MG_STATE_REELING ){
		return;
	}

	if( m_ucState == MG_STATE_SCATTERGAME ){

	}
	else if( m_ucState == MG_STATE_REELING ){

		m_reelsArea.StopReel( (int)usX, (int)usY );

	}
	else if( (egsdMGBetting == gGameStateMgr.GetCurrentState() ||
			  egsdMGBettingPlus == gGameStateMgr.GetCurrentState() ||
			  egsdFGBetting == gGameStateMgr.GetCurrentState() ) &&
			  m_ucState != MG_STATE_BIGWINDEMO && m_ucState != MG_STATE_CREDIT_COUNTING && m_ucState != MG_STATE_BETTING_PLUS) {

		if ( egsdMGBetting == gGameStateMgr.GetCurrentState() && esdReadyGame == gGPMgr.GetHatCurrState() )
			m_reelsArea.m_ActionMgr.m_KnobsMgr.Touch( usX, usY );
		if(( m_BigWinDemo.Touch( usX, usY, true ) == BWD_CHOICE_SWITCH_TO_BWD )&&( m_BigWinDemo.IsEnabled() )) {
			FromBettingPlusToBetting();
			m_ucState = MG_STATE_BIGWINDEMO;
			gGPMgr.SetBigWinDemoFlag( true );
			m_reelsArea.m_ActionMgr.StopAction();
			SetDisabledButtons();
		}

	}
	else if( m_ucState == MG_STATE_BIGWINDEMO ){

		m_ucState = MG_STATE_BETTING;
		unsigned char ucBWDState =  m_BigWinDemo.Touch( usX, usY );
		if( (ucBWDState <1) || (ucBWDState > m_BigWinDemo.GetBWDRows() * m_BigWinDemo.GetBWDPages()) ){
			m_ucState = MG_STATE_BIGWINDEMO;
		}
		else{
            m_ucBWDCombination = ucBWDState;
			DoStartButton();
		}
	}

}

void MainGame::GetRealResult( int nReel, unsigned char* ucResult )
{
	auto gameVariantsPtr = GameVariantsComponent::SafeGet( gGameRestrictionMgr );
	auto gameType =GameVariantsComponent::GameType::MainGame;
	
	unsigned int nReelLen = gameVariantsPtr->GetReelSize( gameType, m_ucVariant, nReel );
	
    unsigned int unMiddleIndex = 0;
#ifdef USE_EGT_DEMO
	if (Demo::IsActive())
	{
		unMiddleIndex = Demo::GetRealResult(nReel);
		Assert(unMiddleIndex < nReelLen);
		
		if (nReel == REELS_COUNT-1)
			Demo::SetActive(false);
	}
    else
        GenerateSequence( 0, 1, &unMiddleIndex, nReelLen );
#else
        GenerateSequence( 0, 1, &unMiddleIndex, nReelLen );
#endif
	
	// preparing dump value ////////////////////////////////////
	m_ucDumpReelIndexes_1[nReel] = m_ucDumpReelIndexes_2[nReel];
	m_ucDumpReelIndexes_2[nReel] = (unsigned short)unMiddleIndex;
	////////////////////////////////////////////////////////////
	
	GetSlidingWindow( gameType, m_ucVariant, nReel, unMiddleIndex, ucResult);
}

void MainGame::GetRealResult( int nReel, unsigned char* ucResult, unsigned char ucInitialIndex, bool bThereIsDoubt )
{
	auto gameType = GameVariantsComponent::GameType::MainGame;
	
	unsigned char ucVariant = m_ucVariantLatestResults;
	if ( std::numeric_limits<unsigned char>::max() == ucVariant )
	{
		unsigned char firstDenomOffset = 0;


		while(! gDenominationControl.IsActive(firstDenomOffset) )
			firstDenomOffset++;


		const char* nvramId = GetHybridParameterId(eNvramGameVariant, firstDenomOffset);
		if( !GetParameter(nvramId, (void*)&ucVariant, sizeof( ucVariant ) ) ){
			eCDebug( LOG_CATEGORY_GAMES ) << "Get NVRAM_GA_GAME_VARIANT failed!\n";
			SetGeneralError(910002);
		}
	}


	// normal games
	eCDebug(LOG_CATEGORY_GAMES) << "going non-fg with indexes\n";

	GetSlidingWindow(gameType, ucVariant, nReel, ucInitialIndex, ucResult);			
}

void MainGame::StopJPArea()
{
	m_reelsArea.StopPillars();
	//not used
	//m_JPArea.Stop();
	//m_FGJPArea.Stop();
}

void MainGame::StartJPArea()
{
	//m_reelsArea.StartPillars();
	//if( m_bFG )
	//	m_FGJPArea.Start();
	//else
	// 	m_JPArea.Start();
}


void MainGame::FillDumpLogStatistics( TransactionId trID, SDump *sDump, bool bGlobalNotification )
{
	// game state //////////////
	sDump->ucMainGameState = m_ucState;
	sDump->bLastGameIsFree = m_bLastGameIsFree;
	sDump->crFGMotherWin = m_crFGMotherWin;
	sDump->usFGCount = (unsigned short)m_nFGCount;
	sDump->usFGOriginalCount = (unsigned short)m_nFGOriginalCount;
	sDump->usFGTotalCount = (unsigned short)m_nFGTotalCount;
	sDump->chExtraWild = (char)m_nExtraWild;
	sDump->ucVariantLatestResults = m_ucVariantLatestResults;

#if WSPLASHTYPE == WST_COVER_FULL
	if (!m_bFG)
#else
	if (m_bFG)
#endif // WSPLASHTYPE == WST_COVER_FULL
	{
		// fg mother figures ////////////////
		for(int i = 0; i < REELS_COUNT; i++ ){
			for(int j = 0; j < ALL_FIGURES_PER_REEL; j++ ){
				sDump->chResultsToShowAfterFG[i][j] = (char)m_efResultsToShowAfterFG[i][j];
			}
		}
	}

	// Win JP flag
	sDump->bJPWin = m_bJpWon;


	if (MG_STATE_REELING == m_ucState)
	{
		sDump->uchLastGameBetPerLine = gGPMgr.BetPerLine_Get();
		sDump->uchLastGameLinesCount = gGPMgr.LinesCount_Get();
	}

	if( bGlobalNotification ) {
		sDump->bFGMode = m_bFG;
	}

	eCDebug(LOG_CATEGORY_GAMES) << "DUMP: pDump->ucMainGameState = " << (int)sDump->ucMainGameState << "\n";

	
 /** Record this point for recover after Progressive and Hand Splash*/
    if(gRecordMgr.GetCurrTrIdentificator() == eGTrIdProgressiveFinish )
	{
        sDump->b_ProgressiveSplashGap = true;
    }


	if( !bGlobalNotification || m_bFG ){
		return;
	}

	/////////////////////////////////////////////////////////////
	// dump /////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	// reel indexes /////////////////////////////////
	int i = 0;
	for( ; i < REELS_COUNT; i++ ){
		sDump->ucReelsPositions_1[i] = m_ucDumpReelIndexes_1[i];
		sDump->ucReelsPositions_2[i] = m_ucDumpReelIndexes_2[i];
	}
	/////////////////////////////////////////////////


	/////////////////////////////////////

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	// follow the last 50 games and hit statistics recordings //////////////////////
	////////////////////////////////////////////////////////////////////////////////


	if( gGameStateMgr.GetCurrentState() != egsdMGReeling ){
		return;
	}

	sDump->b_ProgressiveSplashGap = false;

	const unsigned char MG_GAME_VARIANT_LEN= 2;

	unsigned char ucTrDataID[MG_TRDATAID_LEN + MG_GAME_VARIANT_LEN];
	AddVratkaData_un( ucTrDataID, 0, trID );

	//
	// set game variant to be shown in the event log
	auto gameVariantsPtr = GameVariantsComponent::SafeGet( gGameRestrictionMgr );
	size_t allRtpMainGame =  gameVariantsPtr->GetAllVariantsCount(GameVariantsComponent::GameType::MainGame);
//	size_t allowedRtpMainGame =  gameVariantsPtr->GetAllowedVariantsCount(); We need all game variants not only allowed
	history::Entry entry;
	
	if ( m_ucVariant < allRtpMainGame )
	{
		unsigned short game_variant = gameVariantsPtr->GetFixedPointRtp(GameVariantsComponent::GameType::MainGame ,m_ucVariant);
		memcpy(&(ucTrDataID[MG_TRDATAID_LEN]), &game_variant, sizeof(short)); // copy short to array
        auto entryInfo = entry.mutable_entryinfo();
        entryInfo->mutable_gamevariant()->set_value(game_variant);
	}
	else
	{
		eCDebug( LOG_CATEGORY_GAMES ) << "\n\n [MainGame::FillDumpLogStatistics] WARNING! invalid game variant index \n\n\n";
		unsigned short game_variant = gameVariantsPtr->GetFixedPointRtp(GameVariantsComponent::GameType::MainGame ,0);
		memcpy(&(ucTrDataID[MG_TRDATAID_LEN]), &game_variant, sizeof(short)); // copy short to array
		SetGeneralError(500279);
		return;
	}

	unsigned char ucVratkaData[MG_TRDATAID_LEN+MG_VRATKA_DATA_LEN];
	unsigned char ucCurrPos = 0;

	// first 4 bytes for the transaction id
	ucCurrPos = AddVratkaData_un( ucVratkaData, ucCurrPos, trID );

	// game id
	ucCurrPos = AddVratkaData_uc( ucVratkaData, ucCurrPos, MAIN_GAME_ID);

	// date
    auto now = time( NULL );
    ucCurrPos = AddVratkaData_un( ucVratkaData, ucCurrPos, now);

	// variant/type
	// check for JP Conditions
	unsigned char ucVariant= m_ucVariant;

    auto& mainGameInfo = *entry.mutable_maingame();
	if ( HatApplication::GetInstance().m_JPMMgr->IsAnyProgressiveEnabled() &&
			(gGPMgr.BetPerLine_Get() == gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine)){

		ucVariant|= 1 << 5; // use the sixt bit as an indicator for JP Conditions
        auto& jackpotData = *mainGameInfo.add_jackpot();
        jackpotData.mutable_hasjpconditions()->set_value(true);

	}


	ucCurrPos = AddVratkaData_uc( ucVratkaData, ucCurrPos, ucVariant );
    auto entryInfo = entry.mutable_entryinfo();
    auto linesInfo = entryInfo->mutable_linesinfo();


	// bet per line
	ucCurrPos = AddVratkaData_us( ucVratkaData, ucCurrPos, (unsigned short)gGPMgr.BetPerLine_Get() );
    linesInfo->mutable_betperline()->set_value(gGPMgr.BetPerLine_Get());

    //max bet per line
    linesInfo->mutable_maxbetperline()->set_value(gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine);

	// lines
	ucCurrPos = AddVratkaData_uc( ucVratkaData, ucCurrPos, (unsigned char)gGPMgr.LinesCount_Get() );
    linesInfo->mutable_linescount()->set_value(gGPMgr.LinesCount_Get());

	// figures
    auto visibleReels = mainGameInfo.mutable_visiblereels();
    for( int j = 0; j < REELS_COUNT; j++ ){
        auto newReel = visibleReels->add_reels();
        for( int i = 0; i < VISIBLE_FIGURES_PER_REEL; i++ ){
            auto figure = newReel->add_figures();
            figure->add_id(m_ucLogFigResults[i][j]);
        }
    }

	// denomination
    ucCurrPos = AddVratkaData_ud( ucVratkaData, ucCurrPos, gGPMgr.GameSettings_Get().cPointValue.ToCents() );
    auto invoice = entryInfo->mutable_invoice();
    invoice->mutable_pricepercredit()->set_value(gGPMgr.GameSettings_Get().cPointValue.ToCents());

	GameToHatData( GAME_TO_HAT_START_NEW_GAME_MARK, (const void*)ucTrDataID, MG_TRDATAID_LEN + MG_GAME_VARIANT_LEN);
	GameToHatData( GAME_TO_HAT_ADD_DATA_TO_LAST_GAME, (const void*)ucVratkaData, MG_VRATKA_DATA_LEN );
	//GameToHatData( GAME_TO_HAT_END_GAME, (const void*)ucTrDataID, MG_TRDATAID_LEN );



	RecordRegularHits( trID );

    GetGameHistory()->addToLastEntry(std::move(entry));
	//gMysteryView.OnStartGame();
}

void MainGame::Recover(SDump *pDump)
{
	m_ucState = pDump->ucMainGameState;
	m_bLastGameIsFree = pDump->bLastGameIsFree;
	m_nExtraWild = pDump->chExtraWild;

	// Win JP flag
	m_bJpWon = pDump->bJPWin;

	eCDebug(LOG_CATEGORY_GAMES) << "Recover: pDump->ucMainGameState = " << (int)pDump->ucMainGameState << "\n";


	eCDebug( LOG_CATEGORY_GAMES) << "Recover positions 1: " << (int)pDump->ucReelsPositions_1[0] << " " <<  (int)pDump->ucReelsPositions_1[1] << " " <<
															   (int)pDump->ucReelsPositions_1[2] << " " <<  (int)pDump->ucReelsPositions_1[3] << " " <<
															   (int)pDump->ucReelsPositions_1[4] << "\n";

	eCDebug( LOG_CATEGORY_GAMES) << "Recover positions 2: " << (int)pDump->ucReelsPositions_2[0] << " " <<  (int)pDump->ucReelsPositions_2[1] << " " <<
															   (int)pDump->ucReelsPositions_2[2] << " " <<  (int)pDump->ucReelsPositions_2[3] << " " <<
															   (int)pDump->ucReelsPositions_2[4] << "\n";

	// reel indexes /////////////////////////////////
	int i = 0;
	int j = 0;
	for( ; i < REELS_COUNT; i++ ){
		m_ucDumpReelIndexes_1[i] = pDump->ucReelsPositions_1[i];
		m_ucDumpReelIndexes_2[i] = pDump->ucReelsPositions_2[i];
	}
	/////////////////////////////////////////////////

	m_ucVariantLatestResults = pDump->ucVariantLatestResults;

	// free games attributes /////////////////////
	m_bFG = pDump->bFGMode;
	m_nFGOriginalCount = (int)pDump->usFGOriginalCount;
	m_nFGCount = (int)pDump->usFGCount;
	m_nFGTotalCount = (int)pDump->usFGTotalCount;
	m_nFGMult = (int)pDump->chFGMult;
	m_crFGMotherWin = pDump->crFGMotherWin;
	m_crFGWin = pDump->crFGWin;
	m_crPureFGWin = pDump->crPureFGWin;
	// fg mother figures ////////////////
	for( i = 0; i < REELS_COUNT; i++ ){
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){
			m_efResultsToShowAfterFG[i][j] = (EFigure)pDump->chResultsToShowAfterFG[i][j];
		}
	}
	m_FGSeals.AddFG( m_nFGCount );
	m_FGSeals.SetMult( m_nFGMult );


	EFigure efAnalResults[REELS_COUNT][ALL_FIGURES_PER_REEL];

	for( i = 0; i < REELS_COUNT; i++ ){
		unsigned char ucResults[ALL_FIGURES_PER_REEL];
		if( ( m_ucState == MG_STATE_REELING || m_ucState == MG_STATE_WINDEMO ) &&
            (gGameStateMgr.GetCurrentState() != egsdJPMProgressive) && !pDump->b_ProgressiveSplashGap ){
			GetRealResult( i, ucResults, pDump->ucReelsPositions_1[i], true );
		}
		else{
			GetRealResult( i, ucResults, pDump->ucReelsPositions_2[i] );
		}
		EFigure eResults[ALL_FIGURES_PER_REEL];

		for ( j = 0; j < ALL_FIGURES_PER_REEL; j++ )
			eResults[j] = (EFigure)ucResults[j];

		m_reelsArea.m_reels[i].SetResults( eResults, true );

		for ( j = 0; j < ALL_FIGURES_PER_REEL; j++ )
			efAnalResults[i][j] = (EFigure)ucResults[j];
	}


	int nConfTmp[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
	for( i = 0; i < REELS_COUNT; i++ ){// reels
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){ // raws
			//efResults[i][j] = (EFigure)nResults[i][j];
			if( j > 0 && j < VISIBLE_FIGURES_PER_REEL+1 ){
				nConfTmp[j-1][i] = efAnalResults[i][j];
			}
		}
	}

	Analyzer analyzer;
	Currency crBets[MGDEFS_BET_LINES_COUNT];
	int nLinesCount = gGPMgr.LinesCount_Get();
	Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
	for( i = 0; i < MGDEFS_BET_LINES_COUNT; i++ ){
		if( i < nLinesCount ){
			crBets[i] = crBetPerLine;
		}
		else{
			crBets[i] = 0;
		}
	}

	int nCurrMult = 1;
	if (m_bFG){
		nCurrMult = m_nFGMult;
		//m_JPArea.Stop();
		//m_FGJPArea.Start();
	}

	analyzer.Init( 	nConfTmp, crBets,
			HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
			HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
			gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
			gGPMgr.BetPerLine_Get(), nCurrMult,  (EFigure) m_nExtraWild );

	analyzer.GetResults( &m_AnalyzerResults );

	// in case of hat's jp state ///////////////////
	if(gGameStateMgr.GetCurrentState() == egsdJPMProgressive) {

		if ( ((m_ucState != MG_STATE_BETTING_PLUS)&&(m_ucState != MG_STATE_BETTING) ) ||
		   ( m_AnalyzerResults.GetWinLinesCount() == 1 && m_AnalyzerResults.GetLineDataAt(0).currWin == 0 ) ||
		   m_bFG ) {

				m_reelsArea.SetResults( efAnalResults, m_AnalyzerResults, true );
				m_reelsArea.m_ActionMgr.StartAction();
				SetDisabledButtons();

		   }
	}


	if( m_ucState == MG_STATE_WINDEMO ||
			m_ucState == MG_STATE_SCATTERGAME ||
			m_ucState == MG_STATE_BONUSGAME ||
			m_ucState == MG_STATE_WINSPLASH )
		m_reelsArea.m_ucRAStatus = RA_STATUS_STOPPED_BUSY;

	m_reelsArea.m_ActionMgr.SetBetLines( pDump->uchLinesCount, false );

	if( gGameStateMgr.GetCurrentState() == egsdMGBettingPlus ||
			gGameStateMgr.GetCurrentState() == egsdInfo ||
			gGameStateMgr.GetCurrentState() == egsdGamble )
		m_bWinGame = true;

	if( (m_bFG) && (gGameStateMgr.GetCurrentState() == egsdMGBonusWin))
	{
		if( gGPMgr.GameSettings_Get().ui16AutoGames )
			m_bTestAutoMode = true;
		m_ucState = MG_STATE_WINSPLASH;
		gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
		//m_WinSplash.SetBonusWinAfterFG( m_crFGWin );
		m_bLastGameIsFree = true;

		//m_FGJPArea.Stop();
		//m_JPArea.Start();
	}
	if((m_nFGCount == 0) && (gGameStateMgr.GetCurrentState() == egsdFGBetting) )
	{

		bool bProgressiveFocus = false;
		GameToHatData( GAME_TO_HAT_JP_PROGRESSIVE_FOCUS, (const void*)&bProgressiveFocus, sizeof(bProgressiveFocus) );

		SwitchInFGBetting();
	}
	if( (m_nFGCount == 0) &&
			(gGameStateMgr.GetCurrentState() == egsdFGNormalWin) ){
		// this flag is set in FS_OUTRO timer
		//m_bLastGameIsFree = true;
		SwitchInFGBetting();
		return;
	}
	if( !m_bFG && gGameStateMgr.GetCurrentState() == egsdMGBonusWin )
	{
		m_ucState = MG_STATE_WINSPLASH;

		//m_WinSplash.StartFSIntro();
		//m_WinSplash.SetFGScatterWin( 15, 3 );
		gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
		gGPMgr.SetDemoMode();
	}
	if( (gGameStateMgr.GetCurrentState() == egsdFGBetting)&& ( m_nFGCount > 0 )){
		//??auto start
		gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );

		StartAutoFG();

		SetBettingButtons();
	}

	bool bStartWinDemo = true;

	// don't start win demo, if lines/bet changed or win is 0
	if ( pDump->uchLastGameBetPerLine != pDump->uchBetPerLine ||
			pDump->uchLastGameLinesCount != pDump->uchLinesCount ||
			0 == gGPMgr.Win_Get() )
	{
		bStartWinDemo = false;
	}

	if( ((gGameStateMgr.GetCurrentState() == egsdMGBetting) ||
	     (gGameStateMgr.GetCurrentState() == egsdGamble) ||
	     (gGameStateMgr.GetCurrentState() == egsdMGBettingPlus)) &&
	     (!m_bLastGameIsFree) )
	{
		m_reelsArea.SetResults( efAnalResults, m_AnalyzerResults, true );
		if (bStartWinDemo)
		{
			m_reelsArea.m_ActionMgr.StartAction( false );
		}
		m_reelsArea.SetScatterStarted( false );
	}
	if(( gGameStateMgr.GetCurrentState() == egsdMGBetting||
			gGameStateMgr.GetCurrentState() == egsdMGBettingPlus ||
			gGameStateMgr.GetCurrentState() == egsdMGBonusWin || //when showing fs outro splash and there are animations
			gGameStateMgr.GetCurrentState() == egsdInfo ||
			gGameStateMgr.GetCurrentState() == egsdGamble ||
			gGameStateMgr.GetCurrentState() == egsdLangSelect ||
			gGameStateMgr.GetCurrentState() == egsdJPMExternal ||
			gGameStateMgr.GetCurrentState() == egsdJPMBusy ||
			 gGameStateMgr.GetCurrentState() == egsdBusy  ) && (m_bLastGameIsFree)){
		m_reelsArea.SetOnlyFiguresResults( m_efResultsToShowAfterFG );
		if (bStartWinDemo)
		{
			m_reelsArea.m_ActionMgr.StartAction( false );
		}
	}

	if ( gGameStateMgr.GetCurrentState() == egsdBusy )
	{
	    ResetAutoMode();
		SetDisabledButtons();
	}
}

void MainGame::SetScatterLogData( TransactionId trID, unsigned char* pucMultipliers, unsigned char ucChoice )
{
	const int cnScatterDataLen = 7;
	unsigned char ucScatterData[cnScatterDataLen+MG_TRDATAID_LEN];
	unsigned char ucCurrPos = 0;

	// first 4 bytes for the transaction id
	ucCurrPos = AddVratkaData_un( ucScatterData, ucCurrPos, trID );

	// scatter id
	if( m_bFG ){
		ucCurrPos = AddVratkaData_uc( ucScatterData, ucCurrPos, SCATTER_ID_FG );
	}
	else{
		ucCurrPos = AddVratkaData_uc( ucScatterData, ucCurrPos, SCATTER_ID );
	}

	// multipliers

	for(int i = 0;  i < REELS_COUNT; i++ ){
		ucCurrPos = AddVratkaData_uc( ucScatterData, ucCurrPos, pucMultipliers[i] );
	}

	// choice
	ucCurrPos = AddVratkaData_uc( ucScatterData, ucCurrPos, ucChoice );


	GameToHatData( GAME_TO_HAT_ADD_DATA_TO_LAST_GAME, (const void*)ucScatterData, cnScatterDataLen );

	if( m_bFG ){
		return; // without hits
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	// set scatter hits //////////////////////////////////////////////////////////////////////
	unsigned char ucScatterCount = 0;
	for( int i = 0; i < REELS_COUNT; i++ ){
		if( pucMultipliers[i] > 0 ){
			ucScatterCount++;
		}
	}
/*
	unsigned char uchDenomIndex = gGPMgr.GameSettings_Get().uchBaseDenomOffset;
	// counts //////////////////////////
	//unsigned int unCountsID = unNVRAMHitsIDs[GetHitIDIndex( ef11_scatter, ucScatterCount )];
	unsigned int unCountsID = unNVRAMHitsIDs[GetHitIDIndex( ef10_star, ucScatterCount )];
	unsigned int unLastCountsValue = 0;
	GetArrayParameter( unCountsID, (void*)&unLastCountsValue, uchDenomIndex, sizeof( unLastCountsValue ) );
	unsigned int unNewCountsValue = unLastCountsValue + 1;
	AddTransactionArrayData( trID, unCountsID, (const void*)&unNewCountsValue, uchDenomIndex, sizeof( unNewCountsValue ), 1 );
	////////////////////////////////////

	// wins //////////////////////////////////
	//unsigned int unWinsID = unNVRAMHitWinsIDs[GetHitIDIndex( ef11_scatter, ucScatterCount )];
	unsigned int unWinsID = unNVRAMHitWinsIDs[GetHitIDIndex( ef10_star, ucScatterCount )];
	Currency crLastWinsValue = 0;
	GetArrayParameter( unWinsID, (void*)&crLastWinsValue, uchDenomIndex, sizeof( crLastWinsValue ) );
	Currency crTotalBet = gGPMgr.GameSettings_Get().cPointValue;
	crTotalBet *= gGPMgr.TotalBet_Get();
	//crTotalBet *= SCATTER_POSSIBLE_MULTIPLIERS[pucMultipliers[ucChoice]];
	crTotalBet *= pucMultipliers[ucChoice];
	Currency crNewWinsValue = crLastWinsValue + crTotalBet;
	AddTransactionArrayData( trID, unWinsID, (const void*)&crNewWinsValue, uchDenomIndex, sizeof( crNewWinsValue ), 1 );
	//////////////////////////////////////////
*/
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

}

void MainGame::RecordRegularHits( TransactionId trID )
{
	int i = 0;
	unsigned char uchDenomIndex = gGPMgr.GameSettings_Get().uchBaseDenomOffset;
	for( ; i < m_AnalyzerResults.GetWinLinesCount(); i++ ){

		// counts and wins//////////////////////////
        const char* unCountsID = unNVRAMHitsIDs[GetHitIDIndex( (EFigure)m_AnalyzerResults.GetLineDataAt(i).eFigure,
                m_AnalyzerResults.GetLineDataAt(i).nCount )];
        GameStatUnit_t gstat(m_AnalyzerResults.GetLineDataAt(i).currWin, 1);
        updateGameStatUnits(trID,unCountsID,uchDenomIndex,gstat);

		//////////////////////////////////////////
	}

	// scatters //////////////////////////////////////////////////////
	int nStarScatterCount = 0;
	int nDollarScatterCount = 0;

	for( i = 0; i < 5; i++ ){

		if( m_AnalyzerResults.nScatters1Pos[i] != (-1) ){
			nStarScatterCount++;
		}

		if( m_AnalyzerResults.nScatters2Pos[i] != (-1) ){
			nDollarScatterCount++;
		}
	}

	if( nStarScatterCount == 3 ){

		const char* unCountsID = unNVRAMHitsIDs[GetHitIDIndex( ef10_star, nStarScatterCount )];
		GameStatUnit_t gstat(m_AnalyzerResults.crScatter1Win, 1);
		updateGameStatUnits(trID, unCountsID, uchDenomIndex, gstat );

	}

	//////////////////////////////////////////////////////////////////

	if( nDollarScatterCount > 2 ){

		const char* unCountsID = unNVRAMHitsIDs[GetHitIDIndex( ef11_dollar, nDollarScatterCount )];
		GameStatUnit_t gstat(m_AnalyzerResults.crScatter2Win, 1);
		updateGameStatUnits(trID, unCountsID, uchDenomIndex, gstat );
	}
	//////////////////////////////////////////////////////////////////
}

void MainGame::updateGameStatUnits( TransactionId trID, const char *unCountsID, uint8_t uchDenomIndex, const GameStatUnit_t& gstat)
{
    GameStatUnit_t gameStat;
    GetArrayParameter( unCountsID, (void*)&gameStat, uchDenomIndex, sizeof( GameStatUnit_t ) );
    gameStat += gstat;
    AddTransactionArrayData( trID, unCountsID, (const void*)&gameStat, uchDenomIndex, sizeof( GameStatUnit_t ), 1 );
}

unsigned char MainGame::AddVratkaData_uc( unsigned char* pucData, unsigned char ucPos, unsigned char ucData )
{
	pucData[ucPos++] = ucData;
	return ucPos;
}

unsigned char MainGame::AddVratkaData_us( unsigned char* pucData, unsigned char ucPos, unsigned short usData )
{
	pucData[ucPos++] = GET_LO_1( usData );
	pucData[ucPos++] = GET_HI_1( usData );
	return ucPos;
}

unsigned char MainGame::AddVratkaData_un( unsigned char* pucData, unsigned char ucPos, unsigned int unData )
{
	pucData[ucPos++] = GET_LO_1( GET_LO_2( unData ) );
	pucData[ucPos++] = GET_HI_1( GET_LO_2( unData ) );
	pucData[ucPos++] = GET_LO_1( GET_HI_2( unData ) );
	pucData[ucPos++] = GET_HI_1( GET_HI_2( unData ) );
	return ucPos;
}

unsigned char MainGame::AddVratkaData_ud( unsigned char* pucData, unsigned char ucPos, int64_t udData )
{
	pucData[ucPos++] = GET_LO_1( GET_LO_2( GET_LO_4( udData ) ) );
	pucData[ucPos++] = GET_HI_1( GET_LO_2( GET_LO_4( udData ) ) );
	pucData[ucPos++] = GET_LO_1( GET_HI_2( GET_LO_4( udData ) ) );
	pucData[ucPos++] = GET_HI_1( GET_HI_2( GET_LO_4( udData ) ) );
	pucData[ucPos++] = GET_LO_1( GET_LO_2( GET_HI_4( udData ) ) );
	pucData[ucPos++] = GET_HI_1( GET_LO_2( GET_HI_4( udData ) ) );
	pucData[ucPos++] = GET_LO_1( GET_HI_2( GET_HI_4( udData ) ) );
	pucData[ucPos++] = GET_HI_1( GET_HI_2( GET_HI_4( udData ) ) );
	return ucPos;
}

void MainGame::FromBettingPlusToBetting( bool bTakeWin )
{
	if( SwitchInJPState() ){
		return;
	}

	if( gGameStateMgr.GetCurrentState() == egsdMGBettingPlus ) {

		if( !bTakeWin && gGPMgr.Win_Get() != 0 ){
			Currency crWin = gGPMgr.Win_Get();
			gGPMgr.Win_Reset();
			gMoneyCounting.StartCounting( crWin, gGPMgr.GameSettings_Get().cPointValue, true );
			gMoneyCounting.SetFastMode();
		}

		gGPMgr.SetGameMode();
		gGPMgr.SetFromBettingPlusToBetting();
		gGameStateMgr.RequestToPreviousState();

		//vk bug 19111 19350
		if (gBetLinesControlAdapter.IsCreditBelowTotBet()){
		  m_bUserAutoModeON = false;
		  m_bUserAutoMode = false;
		}

		SetBettingButtons();
	}
}

Currency MainGame::GetGambleLimit()
{
	return gGPMgr.DoubleUpLimit_Get();
}

bool MainGame::SwitchInJPState()
{

	//already in JP state
	if( gGameStateMgr.CheckForState(egsdJPMProgressive) ) {

		//uint32_t ui32Level = 0;
		//GameToHatData( GAME_TO_HAT_JP_GAME_READY, (const void*)&ui32Level, sizeof(ui32Level) );
		return true;
	}


	if( m_ucState == MG_STATE_REELING ||
			m_ucState == MG_STATE_WINSPLASH ||
			gGPMgr.GetHatCurrState() == esdMultidenomination ) {

			return false;
	}


	// conditions to switch in jp state (in the HAT) //////////
	if( gMoneyCounting.GetLeftAmount() == 0 && m_nJPLine != (-1) ) {

		uint32_t ui32Level = 0;
		GameToHatData( GAME_TO_HAT_JP_GAME_READY, (const void*)&ui32Level, sizeof(ui32Level) );

		if( gGameStateMgr.GetCurrentState() == egsdJPMProgressive ) {
			return true;
		}

	}

	return false;
}


bool MainGame::IsNetOK()
{
	bool bNetOk = true;

	// sas condition /////////////////////////////////////////
	if( gGPMgr.BlockWithoutSAS_Get() ||
			gGPMgr.SASBlocked_Get() || gGPMgr.SASNoPJPInfo_Get() )
	{
		bNetOk = false;
	}
	//////////////////////////////////////////////////////////
	return bNetOk;
}


int MainGame::OnGameSettingsChange()
{
	const char* nvram_parameter = gGPMgr.GetHybridParameter(eNvramGameVariant);
	if( !GetParameter(nvram_parameter, (void*)&m_ucVariant, sizeof( m_ucVariant ) ) ){
		eCDebug( LOG_CATEGORY_GAMES ) << "Get NVRAM_DRP_GAME_VARIANT failed!\n";
		SetGeneralError(910002);
	}

	// stop auto if disabled but still running
	if ( gGPMgr.GameSettings_Get().uchPlayerAutoMode != 0 ) {
		if( m_bUserAutoMode || m_bUserAutoModeON ){
		    ResetAutoMode();
		}
	}

	return 0;
}

int MainGame::OnHatStateChanged()
{

	if(gGPMgr.GetHatCurrState() == esdJPUniversalInternal) {
		gVBMgr.StopTimer(this, MG_TIMER_PROGRESSIVE_RECOVER);
	}

	if (gGPMgr.GetHatCurrState() == esdBusyGame )
	{
		bool bProgressiveFocus = true;
		GameToHatData( GAME_TO_HAT_JP_PROGRESSIVE_FOCUS, (const void*)&bProgressiveFocus, sizeof(bProgressiveFocus) );
	}

	if( gGPMgr.GetHatCurrState() == esdMultidenomination ||
		gGPMgr.GetHatCurrState() == esdSASBlockScreen ||
		gGPMgr.GetHatCurrState() == esdNoSasPjpInfo ||
		gGPMgr.GetHatCurrState() == esdNoCbjsPjpInfo ){
		SetDisabledButtons();
	}

	//
	// we assume that hat can go into BlockScreenState only from ready game
	if (gGPMgr.GetHatPrevState() == esdSASBlockScreen || gGPMgr.GetHatPrevState() == esdNoSasPjpInfo ||
			gGPMgr.GetHatPrevState() == esdNoCbjsPjpInfo )
	{
		//
		// check to go into JP state. Only MJP can be won during esdSASBlockScreen
		if (SwitchInJPState()){
			return 0;
		}
	}

	if( ( gGPMgr.GetHatCurrState() == esdSASBlockScreen || gGPMgr.GetHatCurrState() == esdNoSasPjpInfo ||
			gGPMgr.GetHatCurrState() == esdNoCbjsPjpInfo ) &&
			m_nFGCount == 0 &&
			gGameStateMgr.GetCurrentState() == egsdFGBetting )
	{
		gVBMgr.StopTimer( this, MG_TIMER_START_FS_OUTRO );
	}
	else if( ( gGPMgr.GetHatPrevState() == esdSASBlockScreen || gGPMgr.GetHatPrevState() == esdNoSasPjpInfo ||
			gGPMgr.GetHatPrevState() == esdNoCbjsPjpInfo ) &&
			m_nFGCount == 0 &&
			gGameStateMgr.GetCurrentState() == egsdFGBetting )
	{
		gVBMgr.StartTimer( this, MG_TIMER_START_FS_OUTRO, MG_PERIOD_START_FS_OUTRO );
		SetDisabledButtons();
		// this flag is set in FS_OUTRO timer
		//m_bLastGameIsFree = true;
	}

	if( (gGPMgr.GetHatCurrState() == esdReadyGame || gGPMgr.GetHatCurrState() == esdReadyGamePlus ||
			gGPMgr.GetHatCurrState() == esdBusyGame) &&
			(gGPMgr.GetHatPrevState() == esdCongratulation ) )
	{
		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);
		gVBMgr.StartTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE, MG_PERIOD_START_SERVICE_AUTO_MODE ); // tick as soon as possible
	}
	else if( gGPMgr.GetHatCurrState() == esdReadyGame &&
			( gGPMgr.GetHatPrevState() == esdSASBlockScreen || gGPMgr.GetHatPrevState() == esdNoSasPjpInfo	||
					gGPMgr.GetHatPrevState() == esdNoCbjsPjpInfo) )
	{
		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);
		gVBMgr.StartTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE, MG_PERIOD_START_SERVICE_AUTO_MODE );
	}
	else if( gGPMgr.GetHatPrevState() == esdInitUp &&
			( gGPMgr.GetHatCurrState() == esdReadyGame || gGPMgr.GetHatCurrState() == esdReadyGamePlus ) )
	{
		gVBMgr.StopTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE);
		gVBMgr.StartTimer(this, MG_TIMER_START_SERVICE_AUTO_MODE, MG_PERIOD_START_SERVICE_AUTO_MODE );
	}
	else if(gGPMgr.GetHatCurrState() == esdReadyGame && gGPMgr.GetHatPrevState() == esdGameInfo){
		SetBettingButtons();
	}


	if( m_bFG ){
		if( gGPMgr.GetHatCurrState() != esdBonus &&
				gGPMgr.GetHatCurrState() != esdBonusBusy ){
			gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );
		}
	}

	if( gGPMgr.GetHatCurrState() == esdBonus &&
			gGPMgr.GetHatPrevState() != esdBonusBusy ){
		// Must complete all free games without stopping on disconnect
		if( m_bFG && m_nFGCount > 0/* && IsNetOK()*/ ){
			StartAutoFG();
		}
	}

	if( gGPMgr.GetHatPrevState() != esdNonFatalError ||
			gGPMgr.GetHatPrevState() != esdWarning ){
		StartLastDraw();
	}

	if( gGPMgr.GetHatPrevState() == esdCashOut &&
			gGPMgr.GetHatCurrState() != esdHandpay &&
			gGPMgr.GetHatCurrState() != esdPayingWithHopper ){
		SetBettingButtons();
	}

	if ( gGPMgr.GetHatCurrState() == esdNonFatalError || gGPMgr.GetHatCurrState() == esdWarning )
	{
		if ( gGPMgr.GetHatCurrState() == esdWarning )
		{
			if( m_bUserAutoMode || m_bUserAutoModeON ){
			    ResetAutoMode();

				m_ucButtonsState = MG_BUTTONS_STATE_BETTING;
			}
		}

		unsigned char ucLastButtonsState = m_ucButtonsState;
		SetDisabledButtons();
		//In this case m_ucButtonState stores the buttons state before the error appears
		m_ucButtonsState = ucLastButtonsState;
	}

	if( (gGPMgr.GetHatCurrState() == esdNonFatalError) && (gGPMgr.GetHatPrevState() == esdJPGameGap) ) {

		m_bUserAutoModeON = false;
		m_bUserAutoMode = false;
		m_bAutoInSound = false;

		if(gActionBridgeMgr.GetBridgeType() == ActionBridge::eTPlayNextGame) {
			gActionBridgeMgr.GetBridge()->OnDestroy();
		}
	}

	//BUG 19238
	if(gGPMgr.GetHatCurrState() == esdNonFatalError && (gGPMgr.GetHatPrevState() == esdReadyGame || gGPMgr.GetHatPrevState() == esdReadyGamePlus ))
	{
		ResetAutoMode();
	}

    if( (gGPMgr.GetHatCurrState() == esdWaitToConfirmCashout ||
                gGPMgr.GetHatCurrState() == esdHandpay) && !gGPMgr.AnyLimitExceeded())
        {
            m_reelsArea.m_ActionMgr.StopAction();
        }
        if( gGPMgr.GetHatCurrState() == esdMultidenomination )
        {
            m_reelsArea.m_ActionMgr.StopAction();
        }
        /** Send StateChange event for Vaapi Animation pause and resume */
        m_reelsArea.m_ActionMgr.m_CoinAnim.HatStateChange() ;

	return 0;
}

void MainGame::SetFG( int nFGCount, int nFGMult, int nExtraWild )
{
	if( nFGCount > 0 ){
		m_bFG = true;
		m_FGSeals.Reset();
		m_FGSeals.SetMult( nFGMult );
		SetBettingButtons();
		m_crFGMotherWin = (m_crFGMotherWin != 0)? m_crFGMotherWin : gGPMgr.Win_Get();

		// commented for the VEGA VISION fg scenario /////////
		//gGPMgr.Win_Reset();
		//////////////////////////////////////////////////////

		m_reelsArea.m_ActionMgr.StopAction();
		// There isn't extra wild figure in this game
		m_nExtraWild = FIGURES_NUM;
	}
	else{
		m_bFG = false;
		//m_FGJPArea.Stop();
		//m_JPArea.Start();
		m_nFGCount = 0;
		m_nFGTotalCount = 0;
		m_reelsArea.SetOnlyFiguresResults( m_efResultsToShowAfterFG );
		m_reelsArea.m_ActionMgr.StartAction( false );
		m_nExtraWild = FIGURES_NUM;
	}

	//m_nFGCount = nFGCount;
	m_nFGOriginalCount = nFGCount;
	//m_nFGTotalCount = nFGCount;
	m_nFGMult = nFGMult;
}


void MainGame::StartAutoFG( bool bLongPeriod, bool bStartImidiately )
{
	if( gGameStateMgr.GetCurrentState() != egsdFGBetting &&
			gGameStateMgr.GetCurrentState() != egsdFGBettingPlus ){
		return;
	}

	gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );

	if( m_bTestAutoMode ){
		return;
	}

	if( gGPMgr.GetHatCurrState() == esdBonus ||
			gGPMgr.GetHatCurrState() == esdBonusBusy ||
			gGPMgr.GetHatCurrState() == esdBusyGame ){

		int nPeriod = MG_PERIOD_FG_AUTOSTART_2;
		if( bLongPeriod ){
			nPeriod = MG_PERIOD_FG_AUTOSTART_1;
		}
		if ( bStartImidiately )
			gVBMgr.StartTimer( this, MG_TIMER_FG_AUTOSTART, 1 );
		else
			gVBMgr.StartTimer( this, MG_TIMER_FG_AUTOSTART, nPeriod );

	}
}

void MainGame::StartLastDraw()
{
	m_nLastDrawCount = 0;
	m_bLastDraw = true;

	if ( m_ucState == MG_STATE_EXTRAGAME )
	{
		m_ExtraGame.StartLastDraw();
	}
}

void MainGame::ProcessLastDraw()
{
	if( m_bLastDraw ){
		if( ++m_nLastDrawCount > 2 ){
			m_bLastDraw = false;
		}
	}
}

void MainGame::StartTakeWinCounting()
{
	if( gGameStateMgr.GetCurrentState() == egsdJPMProgressive ) {
		return;
	}

	if( SwitchInJPState() ){
		return;
	}

	Currency crWin = gGPMgr.Win_Get();

	// in case of user auto mode ////////////
	if( crWin == 0 ){
		if( !SwitchInJPState() ) {
			gActionBridgeMgr.SwitchToBridge(ActionBridge::eTPlayNextGame);
			//DoStartButton();
		}

		// not used
		//gPanelObject.ShowGameOver();
		return;
	}
	/////////////////////////////////////////

	// not used
	//gPanelObject.m_bGameOverInscription = true;
	gGPMgr.Win_Reset();
	gMoneyCounting.StartCounting( crWin, gGPMgr.GameSettings_Get().cPointValue, true );
	gMoneyCounting.SetFastMode( /*true*/ );
	SetDisabledButtons();

	FromBettingPlusToBetting( true );

	gpBasicSound->StartSound( gGameRM.GetSound( "TAKE_WIN" ) );

	if(!IsTherePendingJP()) {
		gActionBridgeMgr.SwitchToBridge(ActionBridge::eTPlayNextGame);
	}

}

void MainGame::StartCreditCounting()
{
	Currency crWin = gGPMgr.Win_Get();

	// not used
	//gPanelObject.m_bGameOverInscription = true;
	gGPMgr.Win_Reset();
	gMoneyCounting.StartCounting( crWin, gGPMgr.GameSettings_Get().cPointValue, true );
	gMoneyCounting.SetFastMode( true );
	SetDisabledButtons();
	gpBasicSound->StartSound( gGameRM.GetSound( "TAKE_WIN_BUTTON" ) );

	m_ucState = MG_STATE_CREDIT_COUNTING;

	gVBMgr.StopTimer( this, MG_TIMER_CREDIT_COUNTING);
	if(!IsTherePendingJP()){
		gVBMgr.StartTimer( this, MG_TIMER_CREDIT_COUNTING, MG_PERIOD_CREDIT_COUNTING );
		m_bTimerLittleCounting = true;
	}
	else{
		gVBMgr.StartTimer( this, MG_TIMER_CREDIT_COUNTING, 1 );
	}
}

bool MainGame::IsDoubleUpOK(Currency crCheckedAmount)
{
	Currency crWin = gGPMgr.Win_Get();

	if (crCheckedAmount != 0)
		crWin = crCheckedAmount;

	if( gGPMgr.GameSettings_Get().bGlobalDoubleUp ){
		// forbbiden from sf
		return false;
	}

	// cannot double up a zero win
	if( crWin == 0 ){
		return false;
	}

	// check for exceeded double up limit
	Currency crGambleLimit = GetGambleLimit();
	if ( crWin * 2 > crGambleLimit ){
		return false;
	}

	// check for exceeded win limit
	Currency crGameWinLimit = gGPMgr.GameWinLimit_Get() / 2;
	if ( crWin > crGameWinLimit && crGameWinLimit != 0 )
		return false;

	// cannot double up jackpot win
	if ( m_bJpWon )
		return false;

	return true;
}

int MainGame::OnCreditChange()
{
	if( gGPMgr.GetHatPrevState() == esdPayingWithHopper ||
			gGPMgr.GetHatPrevState() == esdHandpay )
	{
		SetBettingButtons();
	}

	return 0;
}

bool MainGame::IsTherePendingJP()
{
	if( m_nJPLine != (-1) ){
		// progressive jp
		return true;
	}

	return false;
}


int MainGame::GetJpLine()
{
	return m_AnalyzerResults.bJPWon ? m_AnalyzerResults.nJPLine : -1;
}


Currency MainGame::GetExtraGameWin(	EExtraGameWinType* pWinType )
{
	Currency crExtraGameWin = GetExtraGameAmount( pWinType );

	return std::min( gGPMgr.GameWinLimit_Get(), crExtraGameWin );
}

Currency MainGame::GetExtraGameAmount( EExtraGameWinType* pWinType )
{
	Currency crExtraGameWin;

	if ( NULL != pWinType )
		*pWinType = eEGInvalid;

	if(!GetParameter("NVRAM_EXTRA_GAME_MG", (void*)&crExtraGameWin, sizeof(crExtraGameWin))){
		eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - Get NVRAM_EXTRA_GAME_MG failed!\n";
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_MG_READ_FAILED); // 1000402
		return 0;
	}
	if (crExtraGameWin > 0)
	{
		if ( NULL != pWinType )
			*pWinType = eEGGame;

		return crExtraGameWin;
	}

	if(!GetParameter("NVRAM_EXTRA_GAME_EXTERNAL", (void*)&crExtraGameWin, sizeof(crExtraGameWin))){
		eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - Get NVRAM_EXTRA_GAME_EXTERNAL failed!\n";
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_EXTERNAL_READ_FAILED); // 1000404
		return 0;
	}
	if (crExtraGameWin > 0)
	{
		if ( NULL != pWinType )
			*pWinType = eEGExternal;

		return crExtraGameWin;
	}

	if(!GetParameter("NVRAM_EXTRA_GAME_JP", (void*)&crExtraGameWin, sizeof(crExtraGameWin))){
		eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - Get NVRAM_EXTRA_GAME_JP failed!\n";
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_JP_READ_FAILED); // 1000406
		return 0;
	}
	if (crExtraGameWin > 0)
	{
		if ( NULL != pWinType )
			*pWinType = eEGProgressive;

		return crExtraGameWin;
	}

	return 0;
}


void MainGame::SubtractExtraGameWin( TransactionId trID )
{
	Currency crExtraGameWin;
	Currency crWinAmount = GetExtraGameWin();

	if(!GetParameter("NVRAM_EXTRA_GAME_MG", (void*)&crExtraGameWin, sizeof(crExtraGameWin)))
	{
		eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - Get NVRAM_EXTRA_GAME_MG failed!\n";
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_MG_READ_FAILED); // 1000402
		return;
	}
	if (crExtraGameWin > 0)
	{
		crExtraGameWin -= crWinAmount;

		if (!AddTransactionData(trID, "NVRAM_EXTRA_GAME_MG", &crExtraGameWin, sizeof(crExtraGameWin)))
		{
			eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - AddTransactionData() failed - NVRAM_EXTRA_GAME_MG\n";
			SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_MG_WRITE_FAILED); // 1000403
			return;
		}

		return;
	}

	if(!GetParameter("NVRAM_EXTRA_GAME_EXTERNAL", (void*)&crExtraGameWin, sizeof(crExtraGameWin)))
	{
		eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - Get NVRAM_EXTRA_GAME_EXTERNAL failed!\n";
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_EXTERNAL_READ_FAILED); // 1000404
		return;
	}
	if (crExtraGameWin > 0)
	{
		crExtraGameWin -= crWinAmount;

		if (!AddTransactionData(trID, "NVRAM_EXTRA_GAME_EXTERNAL", &crExtraGameWin, sizeof(crExtraGameWin)))
		{
			eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - AddTransactionData() failed - NVRAM_EXTRA_GAME_EXTERNAL\n";
			SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_EXTERNAL_WRITE_FAILED); // 1000405
			return;
		}

		return;
	}

	if(!GetParameter("NVRAM_EXTRA_GAME_JP", (void*)&crExtraGameWin, sizeof(crExtraGameWin)))
	{
		eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - Get NVRAM_EXTRA_GAME_JP failed!\n";
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_JP_READ_FAILED); // 1000406
		return;
	}
	if (crExtraGameWin > 0)
	{
		crExtraGameWin -= crWinAmount;

		if (!AddTransactionData(trID, "NVRAM_EXTRA_GAME_JP", &crExtraGameWin, sizeof(crExtraGameWin)))
		{
			eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::GetExtraGameWin() - AddTransactionData() failed - NVRAM_EXTRA_GAME_JP\n";
			SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_JP_WRITE_FAILED); // 1000407
			return;
		}

		return;
	}

	eCDebug( LOG_CATEGORY_GAMES ) << "MainGame::SubtractExtraGameWin() - called when all accumulators are empty\n";
	SetGeneralError(ERROR_MG_EXTRA_GAME_CANT_SUBTRACT_WIN); // 1000408
}


void MainGame::GiveExtraGameAward()
{
	EExtraGameWinType type;
	Currency crWin = GetExtraGameWin( &type );

	switch( type )
	{
	case eEGGame:
		gGPMgr.m_crCurrentPaytableAndProgressiveWin = crWin;
		break;

	case eEGExternal:
		gGPMgr.m_crExternalWin = crWin;
		break;

	case eEGProgressive:
		gGPMgr.m_crCurrentPaytableAndProgressiveWin = crWin;
		gGPMgr.m_crAllProgressiveWins = crWin;
		gGPMgr.m_crProgressiveWin = crWin;
		break;

	default:
		break;
	}

	gGPMgr.SetDemoMode();

	bool bAddToCredit = true;
	if(gGPMgr.AnyLimitExceeded()){
		bAddToCredit = false;
	}

	gMoneyCounting.StartCounting( crWin, gGPMgr.GameSettings_Get().cPointValue, bAddToCredit );
	gMoneyCounting.StartCollectSound();


	m_bWinGame = true;
}

void MainGame::ReelStopped(unsigned char nReel) const
{
	if (!m_bFG)
	{
		struct ReelStoppedInfo
		{
			unsigned char ucReelNumber;
			unsigned char ucIndex;
		} sReelInfo;

		sReelInfo.ucReelNumber = nReel;
		sReelInfo.ucIndex = m_ucDumpReelIndexes_2[nReel-1];

		SetError(REEL_N_STOPPED, NULL, 0, 0, 0, &sReelInfo, sizeof(sReelInfo) );
	}
}

int MainGame::GetLineSndIdx()
{
	int nCurrentLines = gGPMgr.LinesCount_Get();

	  const std::vector<int> optValues = gBetLinesControlAdapter.GetOptionVals(); //vk

	  if ( optValues.at(4) == nCurrentLines )
		return 4/*eLineBtn5*/;
	  else if ( optValues.at(3) == nCurrentLines )
		return 3/*eLineBtn4*/;
	  else if ( optValues.at(2) == nCurrentLines )
		return 2/*eLineBtn3*/;
	  else if ( optValues.at(1) == nCurrentLines )
		return 1/*eLineBtn2*/;
	  else if ( optValues.at(0) == nCurrentLines )
		return 0/*eLineBtn1*/;

	  return -1;
}

void MainGame::SetLine( int nLinesToSet )
{
	m_reelsArea.m_ActionMgr.StopAction();

	gGPMgr.LinesCount_Set((int)(nLinesToSet));

	m_reelsArea.m_ActionMgr.SetBetLines(nLinesToSet);

	gBetLinesControlAdapter.GetSndObj().PlayOptionSound();

	SetBettingButtons();
	gRecordMgr.RecordData();
	if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() ){

		if ( true == m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted() )//BUG 20504 #20 finish coin anim before info request
		{
			m_reelsArea.m_ActionMgr.StopCoinAnim(true);
		}

		gP3Info.ShowDefaultScreen();
	}
}

bool MainGame::ProcessLinesButton(int nLinesCount)
{
	/** 20 LINES ONLY */


	if( gBetLinesControlAdapter.FixedLines() )
		return false;

/*	if( m_ucState == MG_STATE_BETTING || m_ucState == MG_STATE_BETTING_PLUS ){

		FromBettingPlusToBetting();
		if( SwitchInJPState() || gGPMgr.GetHatCurrState() != esdReadyGame ){
			return false;
		}

		if(nLinesCount == -1){
		  eCDebug( LOG_CATEGORY_GAMES ) << "Lines button error!";
		  SetGeneralError(1500090);
		}

		m_reelsArea.m_ActionMgr.StopAction();
		m_reelsArea.m_ActionMgr.SetBetLines( nLinesCount );
		gGPMgr.LinesCount_Set( nLinesCount );

		gBetLinesControlAdapter.GetSndObj().PlayOptionSound();

		SetBettingButtons();
		gRecordMgr.RecordData();
		// initial project ///////////
		if(!gCB2Info.IsShowingJPScreen())
			gCB2Info.ShowScreen( eInfoMainGame );
			//////////////////////////////
		}
	else if( gMoneyCounting.GetLeftAmount() != 0 ){

		m_bFGFastStoped = true;
		gMoneyCounting.SetFastMode();
		SetDisabledButtons();
	}

	return true;
*/

	return true;
}

bool MainGame::ProcessBetButton(int nBet, int nSoundIdx)
{
	if( m_ucState == MG_STATE_BETTING || m_ucState == MG_STATE_BETTING_PLUS ){

		FromBettingPlusToBetting();

		//TODO if there is a switch to gap here, the current code will not work


		if( SwitchInJPState()  ){
			return false;
		}


		if( (gGPMgr.GetHatCurrState() != esdReadyGame) && (gGPMgr.GetHatCurrState() != esdJPGameGap) ) {
			return false;
		}

		if (m_bBetButtonsPlay)
			gBetLinesControlAdapter.GetSndObj().MuteBetSound();

		SetBet(nBet, nSoundIdx);

		if (m_bBetButtonsPlay) {

			if(gGameStateMgr.GetCurrentState() == egsdMGBetting) {
				DoStartButton();
			}
			else {
				gActionBridgeMgr.SwitchToBridge(ActionBridge::eTPlayNextGame);
			}

		}
	}
	else if( gMoneyCounting.GetLeftAmount() != 0 ){

		m_bFGFastStoped = true;
		gMoneyCounting.SetFastMode();
		SetDisabledButtons();
	}

	return true;
}

void MainGame::SetBet(int nBet, int nSoundIdx/*=0*/, bool bEventTriggerGame/*= true */) {

	gBetLinesControlAdapter.GetSndObj().PlayBetSound();
	m_reelsArea.m_ActionMgr.StopNoBettingAction();
	gGPMgr.BetPerLine_Set(nBet);
	gBetLinesControlAdapter.DisableResetOnBetKey();
	SetBettingButtons();
	gRecordMgr.RecordData();
	if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() )
	{
		if ( true == m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted() )//BUG 20504 #20 finish coin anim before info request
		{
			m_reelsArea.m_ActionMgr.StopCoinAnim(true);
		}

		if ( !bEventTriggerGame ){
		  gP3Info.ShowDefaultScreen();
		}
		else if ( !m_bBetButtonsPlay){
		  gP3Info.ShowDefaultScreen();
		}
	}
}

bool MainGame::GetAutoModeState(){
	return 	m_bIsAutoModeOff;
}

void MainGame::ResetDemoReelsArea() {
#ifdef USE_EGT_DEMO

    vector<SPicDef*> spicdefs_vec;
    char buff[255];
    for(unsigned char i = 0; i < FIGURES_NUM; i++){
  	  sprintf(buff, "PICTURE_%d",i);
 		  spicdefs_vec.push_back(gGameRM.GetPicture(buff));
    }

    Demo::SetReelFigures(spicdefs_vec);
    
    GameVariantsComponent::GameType eGameType = GameVariantsComponent::GameType::MainGame;
    auto gameVariantsPtr = GameVariantsComponent::SafeGet(gGameRestrictionMgr);

    for( unsigned int reelIndex = 0; reelIndex < REELS_COUNT; reelIndex++ )
    {
        auto vecReel = gameVariantsPtr->GetWholeReel( eGameType, m_ucVariant, reelIndex );
    
        for (int nReelVariantFigure : vecReel)
        {
#ifdef EGT_DEBUG
            Assert(nReelVariantFigure < static_cast<int>(spicdefs_vec.size()));
#endif        
            SPicDef *pic = spicdefs_vec[nReelVariantFigure];
            DemoReelsArea::InsertReelFigure(reelIndex, nReelVariantFigure);
            DemoReelsArea::InsertIdFigure(nReelVariantFigure, pic);
        }
    }
    
    //setup line selection in reels demo
    DemoReelsArea::SetGameTotalLines(gGPMgr.LinesCount_Get());
    DemoReelsArea::SetNLines(gGPMgr.LinesCount_Get());

    for( int line = 0; line < gGPMgr.LinesCount_Get(); line++ ){
     for( unsigned int reelNo = 0; reelNo < REELS_COUNT; reelNo++ ){

		DemoReelsArea::InsertLines(line , gucWinLines[line][reelNo]);
     }
    }
#endif
}

bool MainGame::IsFirstFreeGame(){

	bool bRes=false;

	if ( (m_nFGOriginalCount == (m_nFGCount)) &&
					(m_nFGOriginalCount == m_nFGTotalCount) && m_bFG ){
		bRes = true;
	}
	return bRes;
}

void MainGame::ResetAutoMode() {

	m_bUserAutoMode = false;
	m_bUserAutoModeON = false;
	m_bAutoInSound = false;
}

void MainGame::HideAttraction()
{
	gP3Info.HideAttraction();
}

void MainGame::TakeWin(){
  if( gMoneyCounting.GetLeftAmount() != 0 ) {
    gMoneyCounting.SetFastMode();
    SetDisabledButtons();
  }
  else if ( egsdMGBettingPlus == gGameStateMgr.GetCurrentState() )
	{
		if(gGPMgr.AnyLimitExceeded() )
		{
			gpBasicSound->StartSound( gGameRM.GetSound( "TAKE_WIN_BUTTON" ) );
			FromBettingPlusToBetting();
			SwitchInJPState();
		}
		else
		{
			StartCreditCounting();
		}
	}
}
//================================ Helper functions =========================================

void GetSlidingWindow( GameVariantsComponent::GameType gameType,
					   unsigned char nVariant,
					   unsigned int nReel,
					   unsigned int nMiddleIndex,
					   unsigned char* ucResult )
{
	auto gameVariantsPtr = GameVariantsComponent::SafeGet( gGameRestrictionMgr );
	
	auto slidingWindow = gameVariantsPtr->CopyReelSlidingWindow( gameType, nVariant, nReel, nMiddleIndex );
	
	for ( auto figID : slidingWindow)
	{
		*ucResult = (unsigned char) figID;
		ucResult++;
	}
}

//---------------------------------------------------------------------------------

void MainGame::ShowInfoScreenIfNotMono( int eScreen, bool bSlide /*= true*/ ){
	if( false == HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() )
	{
		gP3Info.ShowScreen( eScreen, bSlide ); // show main info
	}
}

void MainGame::SetMainGameID(int gameId){
        m_nGameID = gameId;
}

int MainGame::GetMainGameID() const {
        return m_nGameID;
}

bool MainGame::HideReels()
{
        return gMainGame.m_ucState == MG_STATE_WINSPLASH || gMainGame.IsStartFGSplashShown();
}


/** the global MainGame object */
MainGame gMainGame;
