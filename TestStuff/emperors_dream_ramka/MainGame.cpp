/* MainGame.cpp

	MainGame class; responsible for all states during the main game

	Author: Georgi Dragandjikov
	$Id: MainGame.cpp,v 1.1.2.7.2.3.2.5.2.15 2015/06/18 14:07:57 mustafa.bialkov Exp $

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
#include "../../hat/game_mgr/RGBManager.h"
#include "GameDefinitions.h"
#include <egt_lib/debug/egt_debug.h>
#include <egt_lib/utils/FormatFunc.h>
#include "panel/PanelObject.h"
#include "p3_info/P3Info.h"
#include "ml_mgr/MLMgr.h"
#include "GlobalError.h"
#include "game_gamble/Gamble.h"
#include "aft_mgr/AFTMgr.h"
#include <limits>
#include "option_bet_control/GameOptionSchema.h"
#include "option_bet_control/OptionAndBetControlAdapter.h"
#include "jpm_mgr/JPMMgr.h"
#include "action_bridge/ActionBridgeMgr.h"
#include "screen_object/VideoControlMgr.h"

#include "panel/DenominationControl.h"
#include "RestrictionComponents/GameReels/GameVariantsComponent.h"
#include "game_settings/CommonGameSettings.h"
#include <Components/RestrictionComponents/KeyboardCfg/VirtualKeyboardCfgComponent.h>
#include <Components/RestrictionComponents/GameConfiguration/BigWinDemoComponent.h> // Big win demo
#include "game_modules/big_win_demo/CommonBigWinDemo.h"

#include "HatPlugins.h"

using namespace std;
using namespace RestrictionComponents;

#ifdef USE_EGT_DEMO
#include "tests/combinations_demo/CombinationsDemo.h"
#include "tests/combinations_demo/ExpWildDemo.h"
#include "tests/combinations_demo/DemoMgr.h"
using namespace egt_tests;
#endif

static const char* unNVRAMHitsIDs[]=
{
    "NVRAM_ED_3THREE_TEN",
    "NVRAM_ED_4FOUR_TEN",
    "NVRAM_ED_5FIVE_TEN",

    "NVRAM_ED_3THREE_JACK",
    "NVRAM_ED_4FOUR_JACK",
    "NVRAM_ED_5FIVE_JACK",

    "NVRAM_ED_3THREE_QUEEN",
    "NVRAM_ED_4FOUR_QUEEN",
    "NVRAM_ED_5FIVE_QUEEN",

    "NVRAM_ED_3THREE_KING",
    "NVRAM_ED_4FOUR_KING",
    "NVRAM_ED_5FIVE_KING",

    "NVRAM_ED_3THREE_ACE",
    "NVRAM_ED_4FOUR_ACE",
    "NVRAM_ED_5FIVE_ACE",

    "NVRAM_ED_2TWO_LANTERN",
    "NVRAM_ED_3THREE_LANTERN",
    "NVRAM_ED_4FOUR_LANTERN",
    "NVRAM_ED_5FIVE_LANTERN",

    "NVRAM_ED_2TWO_DRAGON",
    "NVRAM_ED_3THREE_DRAGON",
    "NVRAM_ED_4FOUR_DRAGON",
    "NVRAM_ED_5FIVE_DRAGON",

    "NVRAM_ED_2TWO_WOMAN",
    "NVRAM_ED_3THREE_WOMAN",
    "NVRAM_ED_4FOUR_WOMAN",
    "NVRAM_ED_5FIVE_WOMAN",

    "NVRAM_ED_2TWO_MAN",
    "NVRAM_ED_3THREE_MAN",
    "NVRAM_ED_4FOUR_MAN",
    "NVRAM_ED_5FIVE_MAN",

    "NVRAM_ED_3THREE_SCATTER",
    "NVRAM_ED_4FOUR_SCATTER",
    "NVRAM_ED_5FIVE_SCATTER"
};

static void GetSlidingWindow( GameVariantsComponent::GameType gameType,
							  unsigned char nVariant,
							  unsigned int nReel,
							  unsigned int nMiddleIndex,
							  unsigned char* ucResult );

// Mihail 24.06.2009
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
	int specialFigure = 0;
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
	Currency crBets[GAME_LINES_COUNT];
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

	// in free games you substitute the extra wild symbol
	// of the original reels with the analogical resource from sf_rss.xml
	auto linesResult = result.mutable_linesresult();
	int extraWild = params.extraWild;
	if(gameData.has_specialsymbol())
	{
		const auto& specialSymbol = gameData.specialsymbol();
		extraWild = specialSymbol.value();
		linesResult->mutable_jockerid()->add_id(extraWild );
		// showing frame above special symbol
		linesResult->mutable_jockerid()->add_id(PLAYHISTORY_EXPANDING_FRAME );
	}
	Analyzer analyzer;
	analyzer.Init(mainGameFigues,
	              crBets,
	              hasConditions,
	              false,
	              int(crMaxBetPerLine),
	              int(crBetPerLine),
	              multiplier,
	              EFigure(extraWild));

	auto gameId = params.gameId;
	AnalyzerResults analResults(gameId, GetGameRestrictionMgrGetter(), GAME_LINES_COUNT, REELS_COUNT);
	analyzer.GetResults(&analResults);

	if(params.hasFreeGames)
	{
		linesResult->mutable_multiplier()->set_value(multiplier);
	}

	if(params.hasFreeGames)
	{
		int replaced_result[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
		memcpy(replaced_result,analResults.nFigures,sizeof(analResults.nFigures));

		if(analResults.GetWinExtendedLinesCount() > 0)
		{
			for (int i = 0; i < REELS_COUNT; i++)
                {
                    if (analResults.GetWinExtendedLinesData().nExtendedSymbolPos[i] != (-1)){
                        for ( int sqr = 0 ; sqr < VISIBLE_FIGURES_PER_REEL ; ++sqr ){
                            replaced_result[sqr][i] = analResults.GetWinExtendedLinesData().nExtendedSymbolPos[i];
                        }
                    }
                }

			auto specialReels = linesResult->mutable_jockers();
			for(int i = 0; i < REELS_COUNT; ++i)
			{
				auto reel = specialReels->add_reels();
				for(int j = 0; j < VISIBLE_FIGURES_PER_REEL; ++j)
				{
					auto figure = reel->add_figures();
					figure->add_id(replaced_result[j][i]);
					if (replaced_result[j][i] == extraWild)
					{
						// showing frame above special symbol
						figure->add_id(PLAYHISTORY_EXPANDING_FRAME);
					}
				}
			}
		}
	}

	auto resultReels = linesResult->mutable_visiblereels();
	for(int i = 0; i < REELS_COUNT; ++i)
	{
		auto reel = resultReels->add_reels();
		for(int j = 0; j < VISIBLE_FIGURES_PER_REEL; ++j)
		{
			auto figure = reel->add_figures();
			figure->add_id(analResults.nFigures[j][i]);
			// showing frame above special symbol
			if (analResults.nFigures[j][i] == extraWild)
			{
				figure->add_id(PLAYHISTORY_EXPANDING_FRAME);
			}
		}
	}

	Currency totalLinesWin = 0_dollars;
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
		totalLinesWin += analResults.GetLineDataAt(i).currWin;
		if(analResults.nJPLine == analResults.GetLineDataAt(i).nLine)
		{
			line->mutable_jpwin()->set_value(hasConditions);
		}
	}

	for(int i = 0; i< analResults.GetWinExtendedLinesCount();++i)
	{
		auto line = linesResult->add_line();
		line->mutable_linenumber()->set_value(std::to_string(i + 1));
		line->mutable_linetype()->set_value("expanding");
		for(int j = 0; j < analResults.GetWinExtendedLinesData().nCount; ++j)
		{
			auto figureWin = line->mutable_figurewin();
			auto figure = figureWin->add_figures();
			figure->add_id(analResults.GetWinExtendedLinesData().eFigure);
			if (analResults.GetWinExtendedLinesData().eFigure == extraWild)
			{
				// showing frame above special symbol
				figure->add_id(PLAYHISTORY_EXPANDING_FRAME);
			}
		}

		line->mutable_winamount()->set_value(analResults.GetWinExtendedLinesData().currWin);
	}

	 if(analResults.GetWinExtendedLinesCount() > 0){
            totalLinesWin += analResults.GetExtendedLinesWin();
        }

	if(totalLinesWin > 0)
	{
		auto linesWin = linesResult->mutable_lineswin();
		linesWin->set_value(totalLinesWin.ToCents());
	}


	if(analResults.GetScatterWin() > 0)
	{
		auto bonus = linesResult->mutable_bonus();
		auto scatter = bonus->add_bonuses();
		auto bonus_name = scatter->mutable_name();
		bonus_name->set_value("scatter");
		auto award = scatter->mutable_award();
		auto winAmount = award->mutable_winamount();
		winAmount->set_value(analResults.GetScatterWin().ToCents());
		unsigned nScatterCount = 0;
		for(unsigned i = 0; i < REELS_COUNT; i++ )
		{
			if( analResults.nScattersPos[i] != (-1) )
				nScatterCount++;
		}
		for(unsigned i=0 ;i < nScatterCount;++i)
		{
			auto figureWin = scatter->mutable_figurewin();
			auto figure  = figureWin->add_figures();
			figure -> add_id(ef10_scatter);
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
#ifdef EGT_CREDIT_OBSERVER //define when EGT_DEBUG=1
    if (debCreditObserver::getInstance().isAcivePlayHistoryTotalCreditObserver())
    {
        debCreditObserver::getInstance().SetPlayHistoryPartialWin(totalLinesWin.m_n64Data + analResults.GetScatterWin().m_n64Data);
    }
#endif
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
    name.set_value("Emperor's Dream");

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
	 	, m_ucLogFigResults()
	 	, m_ucDumpReelIndexes_1()
	 	, m_ucDumpReelIndexes_2()
	 	, m_bFirstTime(true)
	 	, m_ucReelsFastStop()
	 	, m_bRecordCoin()
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
	 	, m_sndGamble(nullptr)
	 	, m_sndCashOut(nullptr)
	 	, m_sndUserAutoModeIn(nullptr)
	 	, m_sndUserAutoModeOut(nullptr)
	 	, m_bAutoInSound(false)
	 	, m_ucBWDCombination()
        , m_AnalyzerResults( m_nGameID, GetGameRestrictionMgrGetter(), GAME_LINES_COUNT, REELS_COUNT )
	 	, m_ucVariant()
	 	, m_ucVariantLatestResults()
	 	, m_nJPLine()
	 	, bCheckToStartWinSplash(false)
	 	, m_bReeling_after_auto()
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

  m_bReeling_after_auto = false;//vk bug 9627
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
	m_bRecordCoin = false;

	m_ucState = MG_STATE_BETTING;

	m_bLastGameIsFree = false;

	if(!m_reelsArea.Init()) {
        eCDebug( LOG_CATEGORY_GAMES )<<"[ EMPERORS_DREAM ] MainGame::Init fail m_reelsArea " ;
		return false;
	}

	if(!m_FGSeals.Init()) {
        eCDebug( LOG_CATEGORY_GAMES )<< "[EMPERORS_DREAM] MainGame::Init m_FGSeals fail "; 
		return false;
	}

	if(!m_WinSplash.Init()) {
        eCDebug( LOG_CATEGORY_GAMES )<< "[EMPERORS_DREAM] MainGame::Init fail m_WinSplash ";
		return false;
	}

	if(!m_ExtraGame.Init() ) {
		eCDebug(LOG_CATEGORY_GAMES) << "[ EMPERORS_DREAM ] - m_ExtraGame::Init() FAIL  ";
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

	m_bUserAutoMode = false;
	m_bAutoInSound = false;
	m_bUserAutoModeON = false;
	m_bTestAutoMode = false;
	m_bIsAutoModeOff = false;
	m_bWinGame = false;

	m_bTimerLittleCounting = false;
	bCheckToStartWinSplash = false;

	for( int i = 0; i < REELS_COUNT; i++ ){
		m_ucDumpReelIndexes_1[i] = 0;
		m_ucDumpReelIndexes_2[i] = 0;
	}

	if ( ! ( m_sndGamble = gGameRM.GetSound( "MG_BUTTON_DOUBLE" ) ) ){
        eCDebug( LOG_CATEGORY_GAMES )
            << "[EMPERORS_DREAM] : MainGame::Init fail MG_BUTTON_DOUBLE : line :" << __LINE__;
        return false;
    }

	if ( !( m_sndCashOut = gGameRM.GetSound( "MG_BUTTON_CASHOUT" ) ) ){
        eCDebug( LOG_CATEGORY_GAMES )
            << "[EMPERORS_DREAM] : MainGame::Init fail MG_BUTTON_CASHOUT : line :" << __LINE__;
        return false;
    }

	if (! ( m_sndUserAutoModeIn = gGameRM.GetSound( "USER_AUTO_MODE_IN" ) ) ){
        eCDebug( LOG_CATEGORY_GAMES )
            << "[EMPERORS_DREAM] : MainGame::Init fail USER_AUTO_MODE_IN : line :" << __LINE__;
        return false;
    }
	if (! (m_sndUserAutoModeOut = gGameRM.GetSound( "USER_AUTO_MODE_OUT" ) ) ){
        eCDebug( LOG_CATEGORY_GAMES )
            << "[EMPERORS_DREAM] : MainGame::Init fail USER_AUTO_MODE_OUT : line :" << __LINE__;
        return false;
    }

    if(!gGameRM.GetRegister().RegisterPicture("JPA_KNOBS_BACKGROUND", FIRST_VIEW_GROUP))
	{
		eCDebug(LOG_CATEGORY_GAMES) << "[ EMPERORS_DREAM ] - JPA_KNOBS_BACKGROUND FAIL  ";
		return false;
	}

	gVBMgr.StartTimer( this, MG_TIMER_REELING_DRAW, 0, MG_PERIOD_REELING_DRAW );

	gGameStateMgr.RegisterClient( egscMGObject, this );
	gRecordMgr.AddClient( this );
	gGPMgr.AddClient( this );

	///////////////////////////////////////////////////////////

	StartLastDraw();

#ifdef USE_EGT_DEMO
    HatApplication::GetInstance().m_DemoManager->AddDemoHandler ([this](){
         InitTestDemo();
    });
#endif
	
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

/*load stream's*/
void MainGame::LoadResources()
{

}

/*unload stream's*/
void MainGame::UnloadResources()
{

}

bool MainGame::StateChanging( bool bStackDirection, EGameStateDef gsdOldState, EGameStateDef gsdNewState )
{

	return true;
}

bool MainGame::StateChanged( bool bStackDirection, EGameStateDef gsdOldState, EGameStateDef gsdNewState )
{
	if(gsdOldState == egsdMGBonusWin && gsdNewState == egsdFGBetting) {
		m_bRecordCoin = true;
	}

	if( (gsdOldState == egsdMGBonusWin || gsdOldState == egsdFGBonusWin ) &&
		( gsdNewState == egsdMGBetting || gsdNewState == egsdMGBettingPlus || gsdNewState == egsdFGBetting ) ){
		m_reelsArea.SetScatterStarted( false );
	}

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

	else if ( ( gsdNewState == egsdFGBonusWin && gsdOldState == egsdBonus_1 ) ||
			  ( gsdNewState == egsdFGBonusWin && gsdOldState == egsdBonus_2 ) ){


		m_ucState = MG_STATE_WINSPLASH;
        m_WinSplash.SetMode(WSPLASH_MODE_FG_RETRIGGER_WIN);
		gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
		gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, 1 );

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
		m_reelsArea.m_ActionMgr.StopAction();

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
			if( gGPMgr.GameSettings_Get().ui16AutoGames ){
			m_bTestAutoMode = true;
			}
	}
	else if( gsdNewState == egsdFGBonusWin && gsdOldState == egsdBonus_1 ){


	}
	else if( gsdNewState == egsdBonus_1 && gsdOldState == egsdFGBonusWin ){
		m_reelsArea.SetScatterStarted( false );
	}
	else if( gsdNewState == egsdFGBonusWin && gsdOldState == egsdFGScatterGame ){
	}
	else if( gsdNewState == egsdFGScatterGame && gsdOldState == egsdFGBonusWin ){
	}
	else if( gsdNewState == egsdFGBetting && gsdOldState == egsdFGBonusWin ){
		m_bTestAutoMode = false;
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
          m_bReeling_after_auto = false;//vk bug 9627
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
			m_reelsArea.m_ActionMgr.HideLines();
		}
	}

	if ( gsdNewState == egsdBusy && gsdOldState == egsdMGBetting)
	{
		m_bUserAutoMode = false;
		m_bUserAutoModeON = false;
		m_bAutoInSound = false;
		SetDisabledButtons();
	}

	if ( gsdNewState == egsdLangSelect && gsdOldState == egsdMGBetting)
	{
		m_bUserAutoMode = false;
		m_bUserAutoModeON = false;
		m_bAutoInSound = false;
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

			m_bUserAutoMode = false;
			m_bAutoInSound = false;
			m_bUserAutoModeON = false;
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

			m_bUserAutoMode = false;
			m_bAutoInSound = false;
			m_bUserAutoModeON = false;

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

			m_bUserAutoMode = false;
			m_bAutoInSound = false;
			m_bUserAutoModeON = false;


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
	if( m_bFirstTime )
	{

		m_bFirstTime = false;

		if( m_ucState == MG_STATE_REELING ){
			DoStartButton( true );
		}
		else if( m_ucState == MG_STATE_SCATTERGAME )
		{
			if( gGameStateMgr.GetCurrentState() != egsdJPMProgressive)
				m_reelsArea.SetScatterStarted( true );
			else
				m_ucState = MG_STATE_WINDEMO;
		}

	}

	gpBasicDraw->SetColor( 255, 255, 255, 255 );
    gpBasicDraw->DrawPicture( 0, 0, 0, gGameRM.GetPicture( "JPA_KNOBS_BACKGROUND" ) );

	m_reelsArea.Draw();

	if( m_ucState == MG_STATE_WINSPLASH  ) {
		m_WinSplash.Draw();
	}

	if((!m_bFG ) && ( m_ucState != MG_STATE_WINSPLASH) && ( m_ucState == MG_STATE_BETTING || m_ucState == MG_STATE_BIGWINDEMO)){
		CommonBigWinDemo::get().Draw( m_ucState == MG_STATE_BIGWINDEMO  );
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

    if(m_ucState == MG_STATE_WINSPLASH )
	{
		m_WinSplash.OnButton( inputData );
	}


	if( inputData.uiPressed && m_bTestAutoMode ){
		m_bTestAutoMode = false;
		return;
	}

	if( inputData.uiButtons == BUTTON_STARTSTOP){
		m_bIsAutoModeOff = false;
	}

	// user demo mode ///////////////////////////////////////////////
	if( m_bUserAutoMode ){
		if( inputData.uiButtons == BUTTON_AUTO && inputData.uiPressed == BUTTON_AUTO ){
			gpBasicSound->StopSound( m_sndUserAutoModeIn );
			gpBasicSound->StartSound( m_sndUserAutoModeOut );
			m_bUserAutoMode = false;
			m_bAutoInSound = false;

			if(m_ucState == MG_STATE_REELING){
				m_bIsAutoModeOff = true;
			}
		}
		if( inputData.uiButtons & BUTTON_STARTSTOP && inputData.uiPressed == BUTTON_STARTSTOP ){
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
// 			    DoStartButton(); //vk bug 19111
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
	if( m_bUserAutoModeON ){
		if( inputData.uiButtons == BUTTON_AUTO && inputData.uiPressed == BUTTON_AUTO ){
			m_bUserAutoModeON = false;
			m_bUserAutoMode = false;
			m_bAutoInSound = false;
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
		if( inputData.uiButtons || inputData.uiPressed )
		{
			return;
		} else
		{
			OnTouch( inputData.touchData1.bPressed, inputData.touchData1.x, inputData.touchData1.y );
			return;
		}
	}
		// end								*****************************
	//////////////////////////////////////////////////////////////////////////////////////////////////

	const std::vector<int> optValues = gBetLinesControlAdapter.GetOptionVals(); //vk
	if( inputData.uiButtons == BUTTON_L1 && inputData.uiPressed == BUTTON_L1 ){
	  if( !ProcessLinesButton( optValues.at(0) )) return;
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
			FromBettingPlusToBetting();
			if( SwitchInJPState() ){
				return;
			}
			m_reelsArea.m_ActionMgr.StopAction();
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


	if( inputData.uiButtons == BUTTON_STARTSTOP && inputData.uiPressed == BUTTON_STARTSTOP ){
		// button start/stop
		if (  egsdFGBonusWin == gGameStateMgr.GetCurrentState() && !m_reelsArea.m_ActionMgr.m_bMustStopScatter ){
			m_reelsArea.m_ActionMgr.m_bMustStopScatter = true;
			m_reelsArea.m_ActionMgr.m_AnimMgr.StopSounds();
			return;
		}

		if (  m_WinSplash.IsRetrigShown() ){
				m_WinSplash.Interrupt();
				return;
		}

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

		if( gMoneyCounting.GetLeftAmount() != 0 ) {
			gMoneyCounting.SetFastMode();
			SetDisabledButtons();
		}
		else
		{
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
                if (keyboardCfg->IsAvailable()){
                    if ( egsdMGBetting == gGameStateMgr.GetCurrentState() ){
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
                          if (IsReeling()) m_bReeling_after_auto = true; //vk, bug 9627
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
	if( m_bUserAutoModeON || m_bTestAutoMode){
		SetDisabledButtons();
		return;
	}

	m_ucButtonsState = MG_BUTTONS_STATE_REELING;
}

void MainGame::SetWaitingReelsButtons()
{
	m_ucButtonsState = MG_BUTTONS_STATE_WAIT_REELS;
}

void MainGame::SetWinDemoButtons() {

	if( m_reelsArea.m_ActionMgr.m_bExtendedWinExists) {

		//CHANGED BEHAVIOUR - Radoslav Donov
		if(m_ucState != MG_STATE_WINDEMO_EXTENDED){

			if( m_ucButtonsState != MG_BUTTONS_STATE_DISABLED ){
				SetDisabledButtons();
			}
		}
		else {

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
	}

	else if( m_reelsArea.m_ActionMgr.m_bScatter_Exist ){

		//Bug 4608 - new scenario for end of splashes.
		//if (gMoneyCounting.GetLeftAmount() == 0){
		if( m_ucButtonsState != MG_BUTTONS_STATE_DISABLED ){
			SetDisabledButtons();
		}

		gKeyboardScenarioController->RequestFunctionUpdate();
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
		else {
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

    auto results = GetGameComp_BigWinDemo()->GetCombination( ucCombination, CommonBigWinDemo::get().GetCurrentPage() );
    
	EFigure efResults[REELS_COUNT][ALL_FIGURES_PER_REEL];
	int nConfTmp[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
	for( i = 0; i < REELS_COUNT; i++ ){
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){
			efResults[i][j] = static_cast<EFigure>(results.at(j).at(i));
			if( !m_bFG ){
				m_efResultsToShowAfterFG[i][j] = efResults[i][j];
			}
			if( j > 0 && j < VISIBLE_FIGURES_PER_REEL+1 ){
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
	Currency crBets[GAME_LINES_COUNT];
	int nLinesCount = gGPMgr.LinesCount_Get();
	Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
	for( i = 0; i < GAME_LINES_COUNT; i++ ){
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

	eCDebug(LOG_CATEGORY_GAMES) << "RESULTS: " << nResults[0][1] << " " << nResults[1][1] << " " << nResults[2][1] << " " << nResults[3][1] << " " << nResults[4][1] << "\n"
								<<"\t\t\t\t   "<< nResults[0][2] << " " << nResults[1][2] << " " << nResults[2][2] << " " << nResults[3][2] << " " << nResults[4][2] << "\n"
								<<"\t\t\t\t   "<< nResults[0][3] << " " << nResults[1][3] << " " << nResults[2][3] << " " << nResults[3][3] << " " << nResults[4][3] << "\n";

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
	Currency crBets[GAME_LINES_COUNT];
	int nLinesCount = gGPMgr.LinesCount_Get();
	Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
	for( i = 0; i < GAME_LINES_COUNT; i++ ){
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
        Currency m_crWinFromLines_c = 0;

        for(int i = 0; i < m_AnalyzerResults.GetWinLinesCount(); i++ ){
            m_crWinFromLines_c += m_AnalyzerResults.GetLineDataAt(i).currWin;
        }
        if(m_bFG && m_nExtraWild != FIGURES_NUM) {
            for( i = 0; i < m_AnalyzerResults.GetWinExtendedLinesCount(); i++ ) {
                m_crWinFromLines_c += m_AnalyzerResults.GetWinExtendedLinesData().currWin;
            }
        }
        // scatter win ////////////////////////////////////
        m_crWinFromLines_c += m_AnalyzerResults.GetScatterWin();
        debCreditObserver::getInstance().setCurrentWon(m_crWinFromLines_c.ToCents());
        debCreditObserver::getInstance().setCurrGameRespinOrFg(m_bFG);
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

	if(nID == MG_TIMER_PROGRESSIVE_RECOVER)
	{
		uint32_t ui32Level = 0;
		GameToHatData( GAME_TO_HAT_JP_GAME_READY, (const void*)&ui32Level, sizeof(ui32Level) );
	}
	else if( nID == MG_TIMER_REELING_DRAW )
	{

		//start win splash from recover after jp splash
		if(bCheckToStartWinSplash) {
			//bCheckToStartWinSplash = false;
			m_ucState = MG_STATE_WINSPLASH;
            m_WinSplash.SetFGBonusWin( 1, EMPERORS_DREAM_NUMBER_OF_FREE_GAMES ,m_nExtraWild != FIGURES_NUM ? true : false);
			gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
			gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
			gGPMgr.SetDemoMode();
			SetDisabledButtons();
		}
		////////////////////////////////////////////////////////


		if( m_reelsArea.m_ActionMgr.NeedToSetFastCollect() ) {
			if(gMoneyCounting.GetLeftAmount() != 0)
			{
				gMoneyCounting.SetSilentMode();
				gMoneyCounting.SetFastMode();
			}
		}

		if(  (m_reelsArea.ReadyForScatter() )  && (!bCheckToStartWinSplash)){

			// FreeGames disabled
			// second edition start fg splash ///////////////////////////

			if( /*!m_bFG && */!m_bTestAutoMode ){

				if(!m_bFG){
					StartBonusSplash();
					RGBManager::eAction eActionRGB = RGBManager::eFreeGames;
					GameToHatData( GAME_TO_HAT_RGB_ACTION, (const void*)&eActionRGB, sizeof(eActionRGB) );

				}
				else{
					StartRetriggerSplash();
				}
			}
			else{

				if(!m_bFG){
					gRecordMgr.RecordData();
				}

				if(m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted() )
				{
					m_reelsArea.m_ActionMgr.StopCoinAnim();
				}

				m_ucState = MG_STATE_WINSPLASH;
                m_WinSplash.SetFGBonusWin( 1, EMPERORS_DREAM_NUMBER_OF_FREE_GAMES );
				gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
				gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
				gGPMgr.SetDemoMode();

				//Bug 6903
				if ( gGameStateMgr.GetCurrentState() ==	egsdJPMProgressive ){
					gMoneyCounting.SetFastMode(true);
				}
				else{
					gMoneyCounting.SetFastMode(false);
				}
				//End Bug 6903

				SetDisabledButtons();
			}
		}

		bCheckToStartWinSplash = false;

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
				m_ucState = MG_STATE_WINDEMO;
				if( m_reelsArea.m_ActionMgr.m_bScatter_Exist ){
					//if( m_bUserDemoMode )
					//	m_bUserAutoModeON = true;
					// about the two scatter situation m_bUserDemoMode = false;

					//Bug 4608 - new scenario for end of splashes.
					if (gMoneyCounting.GetLeftAmount() == 0 && m_reelsArea.m_ActionMgr.m_bThereIsUndoneScatter){
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


			//	SetWinDemoButtons();
			}
			else if( m_reelsArea.GetRAStatus() == RA_STATUS_REELING_CAN_NOT_STOP ){
				if( m_ucButtonsState != MG_BUTTONS_STATE_WAIT_REELS )
					SetWaitingReelsButtons();
			}

			break;
		case MG_STATE_WINDEMO:
				if(m_reelsArea.CoinAnimCanStart()){
					m_reelsArea.m_ActionMgr.m_CoinAnim.SetCurrency(gMoneyCounting.GetLeftAmount());
				}
			if( ( m_reelsArea.m_ActionMgr.m_bExtendedWinExists) ) {

				//CHANGED BEHAVIOUR - Radoslav Donov
				if( /*( gMoneyCounting.GetLeftAmount() == 0 ) && */ (m_reelsArea.m_ActionMgr.NeedToShowExtendedWin()) ) {

					if(gMoneyCounting.GetLeftAmount() != 0 ) {
						gMoneyCounting.SetFastMode();
						SetDisabledButtons();
					}

					m_ucState = MG_STATE_WINDEMO_EXTENDED;
					m_reelsArea.StartExtendedLinesDemo();
					SetWinDemoButtons();
				}
				return;
			}


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
				m_reelsArea.m_ActionMgr.m_CoinAnim.SetCurrency(gMoneyCounting.GetLeftAmount());

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

		case MG_STATE_WINDEMO_EXTENDED:
			if(m_reelsArea.CoinAnimCanStart()){
					m_reelsArea.m_ActionMgr.m_CoinAnim.SetCurrency(gMoneyCounting.GetLeftAmount());
			}

			//CHANGED BEHAVIOUR - Radoslav Donov
			if( (gMoneyCounting.GetLeftAmount() == 0 ) && (!m_reelsArea.m_ActionMgr.IsShowingExtendedWin()) ) {

				m_reelsArea.StopExtendedLinesDemo();
				m_ucState = MG_STATE_WINDEMO;
				SetWinDemoButtons();
			}

			break;

		case MG_STATE_SCATTERGAME:
			if( !m_reelsArea.GetScatterStarted() ){
				m_ucState = MG_STATE_WINSPLASH;
				gMoneyCounting.SetSilentMode(false);

				gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
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
		default:
			break;
		}
		///////////////////////////////////////////////////////

		Refresh();

	}
	else if( nID == MG_TIMER_WINSPLASH ){

		if(times == 1 && m_WinSplash.GetMode() == WSPLASH_MODE_FG_BONUS_WIN)
		{
			RGBManager::eAction eActionRGB = RGBManager::eFreeGames;
			GameToHatData( GAME_TO_HAT_RGB_ACTION, (const void*)&eActionRGB, sizeof(eActionRGB) );
		}

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
					m_WinSplash.GetMode() == WSPLASH_MODE_FG_RETRIGGER_WIN ||
					m_WinSplash.GetMode() == WSPLASH_MODE_FAST_RETRIGGER ){

				if(m_WinSplash.GetMode() == WSPLASH_MODE_FG_BONUS_WIN)
					{
						  RGBManager::eAction eActionRGB = RGBManager::eDefault;
						  GameToHatData( GAME_TO_HAT_RGB_ACTION, (const void*)&eActionRGB, sizeof(eActionRGB) );
					}



				m_nFGCount += m_nFGOriginalCount;
				m_nFGTotalCount += m_nFGOriginalCount;

				m_FGSeals.AddFG( m_nFGOriginalCount, true );
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

				if(( m_nFGCount == 0 ) && (m_WinSplash.GetMode() != WSPLASH_MODE_FG_RETRIGGER_WIN || m_WinSplash.GetMode() != WSPLASH_MODE_FAST_RETRIGGER )){
					SwitchInFGBetting();
				}

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
		StartAutoFG( true, false );

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
			gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
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

				SetBettingButtons();


				m_bTestAutoMode = true;
				if( !SwitchInJPState() ){
					DoStartButton();
				}
			}
		}
	}

	else if ( nID == MG_TIMER_CREDIT_COUNTING )
	{
		if( gMoneyCounting.GetLeftAmount() == 0 )
		{
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

		gVBMgr.StopTimer( this, MG_TIMER_START_FS_OUTRO );
		gVBMgr.StartTimer( this, MG_TIMER_START_FS_OUTRO, MG_PERIOD_START_FS_OUTRO );
		SetDisabledButtons();
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
			if(gBetLinesControlAdapter.GetState() != AOptionAndBetControlAdapter::eRegular){ //vk
			  m_bUserAutoMode = false;
			  m_bUserAutoModeON = false;
			  m_bAutoInSound = false;
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
				Currency crBets[GAME_LINES_COUNT];
				int nLinesCount = gGPMgr.LinesCount_Get();
				Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
				for( i = 0; i < GAME_LINES_COUNT; i++ ){
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

			if( !bRecover )
			{

				if( m_bFG )
				{

					if( m_nJPLine != (-1) )
					{
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
				else
				{

					gGPMgr.SetGameMode();
					int nLinesCount = gGPMgr.LinesCount_Get();
					Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
					Currency crTotalBet = crBetPerLine * nLinesCount;
					gGPMgr.Credit_DeductBet( crTotalBet );

					if( m_nJPLine != (-1) )
					{
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
					else
					{
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

    if (m_WinSplash.IsFastSplashInTouchZone(usX,usY))
	{
		if (  m_WinSplash.IsRetrigShown() ){
			m_WinSplash.Interrupt();
			return;
		}
	}

	if( m_bIsAutoModeOff == true && m_ucState == MG_STATE_REELING ){
		return;
	}
	else if( m_ucState == MG_STATE_REELING ){

		m_reelsArea.StopReel( (int)usX, (int)usY );

	}
	else if( (egsdMGBetting == gGameStateMgr.GetCurrentState() ||
			  egsdMGBettingPlus == gGameStateMgr.GetCurrentState() ||
			  egsdFGBetting == gGameStateMgr.GetCurrentState() ) &&
			 m_ucState != MG_STATE_BIGWINDEMO && m_ucState != MG_STATE_CREDIT_COUNTING && m_ucState != MG_STATE_BETTING_PLUS) {

		if ( egsdMGBetting == gGameStateMgr.GetCurrentState() && esdReadyGame == gGPMgr.GetHatCurrState() )
		{
			int nLinesToSet = 0;
			if (m_reelsArea.m_ActionMgr.m_KnobMgr.Touch((int) usX, (int) usY, nLinesToSet))
			{
				if (gBetLinesControlAdapter.IsLineSelectable(nLinesToSet))
				{
					SetLine(nLinesToSet);
				}
			}
		}

		if(( CommonBigWinDemo::get().Touch( usX, usY, true ) == BWD_CHOICE_SWITCH_TO_BWD )&&( CommonBigWinDemo::get().IsEnabled() )) {
			FromBettingPlusToBetting();
			m_ucState = MG_STATE_BIGWINDEMO;
			gGPMgr.SetBigWinDemoFlag( true );
			m_reelsArea.m_ActionMgr.StopAction();
			SetDisabledButtons();
		}

	}
	else if( m_ucState == MG_STATE_BIGWINDEMO ){

		m_ucState = MG_STATE_BETTING;
		unsigned char ucBWDState =  CommonBigWinDemo::get().Touch( usX, usY );
		if( (ucBWDState <1) || (ucBWDState > CommonBigWinDemo::get().GetBWDRows() * CommonBigWinDemo::get().GetBWDPages()) ){
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
	
	GameVariantsComponent::GameType gameType = GameVariantsComponent::GameType::MainGame;
	if( m_bFG )
	{
		gameType = GameVariantsComponent::GameType::FreeGame;
	}	//else is is by default = MainGame
	
	unsigned int nReelLen = gameVariantsPtr->GetReelSize( gameType, m_ucVariant, nReel );
	//////////////////////////////////////////////
	
	unsigned int unMiddleIndex = 0;
	
#ifdef USE_EGT_DEMO
    if(CombinationsDemo::Instance().IsActive() && CombinationsDemo::Instance().IsDemoDataOK(REELS_COUNT, gameType )){
        unMiddleIndex = CombinationsDemo::Instance().GetRealResult(nReel);
#ifdef EGT_DEBUG
        Assert(unMiddleIndex < nReelLen);
#endif
        if (nReel == REELS_COUNT-1)
            CombinationsDemo::Instance().SetInactive();
    }
    else
        GenerateSequence( 0, 1, &unMiddleIndex, nReelLen );
#else
    GenerateSequence( 0, 1, &unMiddleIndex, nReelLen );
#endif
	
	// preparing dump value ////////////////////////////////////
	m_ucDumpReelIndexes_1[nReel] = m_ucDumpReelIndexes_2[nReel];
	m_ucDumpReelIndexes_2[nReel] = (unsigned char)unMiddleIndex;
	////////////////////////////////////////////////////////////
	
	GetSlidingWindow( gameType, m_ucVariant, nReel, unMiddleIndex, ucResult);
}

void MainGame::GetRealResult( int nReel, unsigned char* ucResult, unsigned char ucInitialIndex, bool bThereIsDoubt )
{
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

	bool bMustBeFG = false;
	if(	bThereIsDoubt ){
		// in case of first free game, get non fg reels
		if( (m_nFGOriginalCount == (m_nFGCount+1)) &&
				(m_nFGOriginalCount == m_nFGTotalCount) ){
			bMustBeFG = false;
		}
		else{
			bMustBeFG = true;
		}
		// in case of normal games and last game wasn't free - get non fg reels
		if( !m_bFG && !m_bLastGameIsFree ){
			bMustBeFG = false;
		}
	}
	else{
		if( m_bFG &&
				!((m_nFGOriginalCount == m_nFGCount) &&
						(m_nFGOriginalCount == m_nFGTotalCount)) ){
			bMustBeFG = true;
		}
		else{
			bMustBeFG = false;
		}
	}
	
	GameVariantsComponent::GameType gameType = GameVariantsComponent::GameType::MainGame;
	if( bMustBeFG )
	{
		gameType = GameVariantsComponent::GameType::FreeGame;
		eCDebug(LOG_CATEGORY_GAMES) << "going fg with indexes";
	}	//else is is by default = MainGame
	else
	{
		eCDebug(LOG_CATEGORY_GAMES) << "going non-fg with indexes";
	}
	
	GetSlidingWindow( gameType, ucVariant, nReel, ucInitialIndex, ucResult);
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
    

	// Win JP flag
	sDump->bJPWin = m_bJpWon;


	if (MG_STATE_REELING == m_ucState)
	{
		sDump->uchLastGameBetPerLine = gGPMgr.BetPerLine_Get();
		sDump->uchLastGameLinesCount = gGPMgr.LinesCount_Get();
	}

	if( bGlobalNotification ){
		sDump->bFGMode = m_bFG;
	}
    
eCDebug (LOG_CATEGORY_GAMES) << "\nDUMP: pDump->ucMainGameState = " << (int)sDump->ucMainGameState << "\n";
	
 /** Record this point for recover after Progressive and Hand Splash*/
    if(gRecordMgr.GetCurrTrIdentificator() == eGTrIdProgressiveFinish )
	{
        sDump->b_ProgressiveSplashGap = true;
    }

	////////////////////////////
	if(m_bRecordCoin) {
			unsigned char ucRecordCoin[6];
			GameToHatData( GAME_TO_HAT_ADD_DATA_TO_LAST_GAME, (const void*)ucRecordCoin, 2 );
			m_bRecordCoin = false;
	}
	// if it's matter of free games //////////////////
	if(m_bFG &&
			bGlobalNotification &&
			(gGameStateMgr.GetCurrentState() == egsdFGReeling  ||
					(gGameStateMgr.GetCurrentState() == egsdFGBetting &&
							( (m_nFGOriginalCount == m_nFGCount) && (m_nFGOriginalCount == m_nFGTotalCount) ) )
			)){

		//skip the rest of this function if this is a transition to/from a jp state
		if( (gRecordMgr.GetCurrTrIdentificator() == eGTrIdProgressiveStart) ||
				(gRecordMgr.GetCurrTrIdentificator() == eGTrIdProgressiveFinish) ){
			return;
		}

		history::Entry entry;
		auto freegames = entry.mutable_freegames();
		auto turn = freegames->add_turns();
		if ( HatApplication::GetInstance().m_JPMMgr->IsAnyProgressiveEnabled() && (gGPMgr.BetPerLine_Get() == gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine) )
		{
			auto jackpotData = turn->add_jackpot();
			jackpotData->mutable_hasjpconditions()->set_value(true);
		}
		auto visibleReels = turn->mutable_visiblereels();
		auto multipliers = turn->mutable_multipliers();
		auto winmultiplier = multipliers->mutable_winmultiplier();
		winmultiplier->set_value(GetFGMult());
		for( int i = 0; i < REELS_COUNT; i++ )
		{
			auto newReel = visibleReels->add_reels();

			for( int j = 0; j < VISIBLE_FIGURES_PER_REEL; j++ )
			{
				auto figure = newReel->add_figures();
				figure->add_id(m_ucLogFigResults[j][i]);
			}
		}
		auto specialSymbol = turn->mutable_specialsymbol();
		specialSymbol->set_value(m_nExtraWild);

		//retrigger logic
		int nScatterCount = 0;
		for(int i = 0; i < REELS_COUNT; i++ ){
			if( m_AnalyzerResults.nScattersPos[i] != (-1) ){
				nScatterCount++;
			}
		}
		if(nScatterCount > 2)
		{
			auto bonusData = turn->mutable_bonus();
			auto freeGames = bonusData->mutable_freegames();
			freeGames->set_value(m_nFGOriginalCount);
		}

		if( gGameStateMgr.GetCurrentState() == egsdFGReeling ){
			GetGameHistory()->addToLastEntry(std::move(entry));
		}

		// reel indexes /////////////////////////////////
		int i = 0;
		for( ; i < REELS_COUNT; i++ ){
			sDump->ucReelsPositions_1[i] = m_ucDumpReelIndexes_1[i];
			sDump->ucReelsPositions_2[i] = m_ucDumpReelIndexes_2[i];
		}

		sDump->bFGMode = m_bFG;
		sDump->usFGOriginalCount = (unsigned short)m_nFGOriginalCount;
		sDump->usFGCount = (unsigned short)m_nFGCount;
		sDump->usFGTotalCount = (unsigned short)m_nFGTotalCount;
		sDump->chFGMult = (char)m_nFGMult;
		sDump->crFGWin = m_crFGWin;

		if(m_reelsArea.m_ActionMgr.m_bWinLimitExceeded){
			sDump->uchLimitExceeded = 1;
		}

		return;
	}
	else if( m_bNeedToRecordBonusWin ){

		const size_t DATA_LEN = 10;
		unsigned char ucVratkaData[MAIN_GAME_TRDATAID_LEN+DATA_LEN];

		// total fg win id
		unsigned char uchLimitExceeded = 0;
		if(sDump->uchLimitExceeded){
			uchLimitExceeded = 1;
		}

		history::Entry entry;
		auto freegames = entry.mutable_freegames();
		freegames->mutable_limitexceeded()->set_value(uchLimitExceeded);
		GetGameHistory()->addToLastEntry(std::move(entry));

		m_crPureFGWin = m_crFGWin - m_crFGMotherWin;
		sDump->crPureFGWin = m_crPureFGWin;

		GameToHatData( GAME_TO_HAT_ADD_DATA_TO_LAST_GAME, (const void*)ucVratkaData, DATA_LEN );

		unsigned char uchDenomIndex = gGPMgr.GameSettings_Get().uchBaseDenomOffset;

		GameStatUnit_t gstatBonus(m_crPureFGWin, 1);
        updateGameStatUnits(trID,"NVRAM_ED_BONUS_FREE_SPINS",uchDenomIndex,gstatBonus);

		GameStatUnit_t gstatTotalFS(0, m_nFGTotalCount);
        updateGameStatUnits(trID,"NVRAM_ED_TOTAL_FREE_SPINS",uchDenomIndex,gstatTotalFS);

		sDump->bFGMode = m_bFG;
		sDump->usFGOriginalCount = (unsigned short)m_nFGOriginalCount;
		sDump->usFGCount = (unsigned short)m_nFGCount;
		sDump->usFGTotalCount = (unsigned short)m_nFGTotalCount;
		sDump->chFGMult = (char)m_nFGMult;
		sDump->crFGWin = m_crFGWin;

		m_bNeedToRecordBonusWin = false;
	}
	//////////////////////////////////////////////////


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
	/////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////
	// follow the last 50 games and hit statistics recordings //////////////////////
	////////////////////////////////////////////////////////////////////////////////

	if( gGameStateMgr.GetCurrentState() != egsdMGReeling ){
		return;
	}

	sDump->b_ProgressiveSplashGap = false;

	NewGameStartData startData;
	startData.trId = trID;

	//
	// set game variant to be shown in the event log

	auto gameVariantsPtr = GameVariantsComponent::SafeGet( gGameRestrictionMgr );
	size_t allRtpMainGame =  gameVariantsPtr->GetAllVariantsCount(GameVariantsComponent::GameType::MainGame);
//	size_t allowedRtpMainGame =  gameVariantsPtr->GetAllowedVariantsCount(); We need all game variants not only allowed
	history::Entry entry;
	if ( m_ucVariant < allRtpMainGame )
	{
		unsigned short game_variant = gameVariantsPtr->GetFixedPointRtp(GameVariantsComponent::GameType::MainGame ,m_ucVariant);
		startData.gameVariant = game_variant;
		// history
		auto entryInfo = entry.mutable_entryinfo();
		entryInfo->mutable_gamevariant()->set_value(game_variant);
	}
	else
	{
		eCDebug( LOG_CATEGORY_GAMES ) << "\n\n [MainGame::FillDumpLogStatistics] WARNING! invalid game variant index \n\n\n";
		unsigned short game_variant = gameVariantsPtr->GetFixedPointRtp(GameVariantsComponent::GameType::MainGame ,0);
		startData.gameVariant = game_variant;
		SetGeneralError(500279);
		return;
	}

	// variant/type
	// check for JP Conditions
	auto& mainGameInfo = *entry.mutable_maingame();

	if ( HatApplication::GetInstance().m_JPMMgr->IsAnyProgressiveEnabled() &&
	     (gGPMgr.BetPerLine_Get() == gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine))
	{
		auto& jackpotData = *mainGameInfo.add_jackpot();
		jackpotData.mutable_hasjpconditions()->set_value(true);
	}

	auto entryInfo = entry.mutable_entryinfo();
	auto linesInfo = entryInfo->mutable_linesinfo();

	// bet per line
	linesInfo->mutable_betperline()->set_value(gGPMgr.BetPerLine_Get());

	//max bet per line
	linesInfo->mutable_maxbetperline()->set_value(gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine);

	// lines
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
	auto invoice = entryInfo->mutable_invoice();
	invoice->mutable_pricepercredit()->set_value(gGPMgr.GameSettings_Get().cPointValue.ToCents());

	GameToHatData( GAME_TO_HAT_START_NEW_GAME_MARK, (const void*)&startData, MAIN_GAME_TRDATAID_LEN);

    RecordRegularHits( trID );

	//gMysteryView.OnStartGame();

	GetGameHistory()->addToLastEntry(std::move(entry));
}

void MainGame::Recover(SDump *pDump)
{
	m_ucState = pDump->ucMainGameState;
	m_bLastGameIsFree = pDump->bLastGameIsFree;
    m_nExtraWild = pDump->chExtraWild;

	// Win JP flag
	m_bJpWon = pDump->bJPWin;

	eCDebug( LOG_CATEGORY_GAMES) << "Recover: pDump->ucMainGameState = " << (int)pDump->ucMainGameState << "\n";


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
    
	m_reelsArea.Preinit((EFigure)m_nExtraWild);

    //Bug 43546 and 43485
    if(m_nExtraWild != FIGURES_NUM && m_bFG)
    {
        std::vector<int> winCoeffs( gucWins[m_nExtraWild], gucWins[m_nExtraWild] + REELS_COUNT );
        PluginFunctions().DispatchSignal(signal_names::special_symbol_bonus::SelectedSymbol, int(m_nExtraWild), winCoeffs);
    }
    /////////////////////

	// fg mother figures ////////////////
	for( i = 0; i < REELS_COUNT; i++ ){
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){
			m_efResultsToShowAfterFG[i][j] = (EFigure)pDump->chResultsToShowAfterFG[i][j];
		}
	}
	m_FGSeals.AddFG( m_nFGCount );
	m_FGSeals.SetTotalSpins(m_nFGTotalCount);
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
        if(IsFirstFreeGameCorr()) {
            m_reelsArea.m_reels[i].SetDrawFrame(false);
        }
        else if(m_bFG) {
            m_reelsArea.m_reels[i].SetDrawFrame(true);
        }
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
	Currency crBets[GAME_LINES_COUNT];
	int nLinesCount = gGPMgr.LinesCount_Get();
	Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
	for( i = 0; i < GAME_LINES_COUNT; i++ ){
		if( i < nLinesCount ){
			crBets[i] = crBetPerLine;
		}
		else{
			crBets[i] = 0;
		}
	}

	int nCurrMult = 1;
	if (m_bFG){
		gStatusLine.SetFreeSpinsFeature(m_nFGMult);
		nCurrMult = m_nFGMult;
	}

	analyzer.Init( 	nConfTmp, crBets,
			HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
			HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
			gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
			gGPMgr.BetPerLine_Get(), nCurrMult,  (EFigure) m_nExtraWild );

	analyzer.GetResults( &m_AnalyzerResults );

	if(gGameStateMgr.GetCurrentState() == egsdJPMProgressive)
	{
		if ( ((m_ucState != MG_STATE_BETTING_PLUS)&&(m_ucState != MG_STATE_BETTING) ) ||
		   (m_AnalyzerResults.GetWinLinesCount() == 1 && m_AnalyzerResults.GetLineDataAt(0).currWin == 0 ) || m_bFG )
		{
			m_reelsArea.SetResults( efAnalResults, m_AnalyzerResults, true );
			m_reelsArea.m_ActionMgr.StartAction(false);
			SetDisabledButtons();
		}
	}

	if( m_ucState == MG_STATE_WINDEMO ||
			m_ucState == MG_STATE_WINDEMO_EXTENDED ||
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
		gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
		gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
		m_WinSplash.SetBonusWinAfterFG( m_crFGWin );
		m_bLastGameIsFree = true;
        for(auto&& reel : m_reelsArea.m_reels) {
            reel.SetDrawFrame(true);
        }
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
		if(m_ucState == MG_STATE_WINSPLASH) {

            m_WinSplash.SetFGBonusWin( 1, EMPERORS_DREAM_NUMBER_OF_FREE_GAMES, m_nExtraWild != FIGURES_NUM ? true : false);
			gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
			gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
			gGPMgr.SetDemoMode();
		}
		else{
			bCheckToStartWinSplash = true;
		}
        
        for( i = 0; i < REELS_COUNT; i++) {
            m_reelsArea.m_reels[i].SetDrawFrame(false);
        }
        
	}
	if( (gGameStateMgr.GetCurrentState() == egsdFGBetting)&& ( m_nFGCount > 0 ))
	{
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
			gGameStateMgr.GetCurrentState() == egsdBusy  )
			&& (MG_STATE_WINSPLASH != m_ucState) && (m_bLastGameIsFree) ) {

		m_reelsArea.SetOnlyFiguresResults( m_efResultsToShowAfterFG );
		if (bStartWinDemo)
		{
			m_reelsArea.m_ActionMgr.StartAction( false );
		}
	}

	if ( gGameStateMgr.GetCurrentState() == egsdBusy )
	{
		m_bUserAutoMode = false;
		m_bUserAutoModeON = false;
		m_bAutoInSound = false;
		SetDisabledButtons();
	}
}

void MainGame::SetScatterLogData( TransactionId trID, unsigned char* pucMultipliers, unsigned char ucChoice )
{}

void MainGame::RecordRegularHits( TransactionId trID )
{
	int i = 0;
	unsigned char uchDenomIndex = gGPMgr.GameSettings_Get().uchBaseDenomOffset;
	for( ; i < m_AnalyzerResults.GetWinLinesCount(); i++ ){

		// counts //////////////////////////

		const char* unCountsID = unNVRAMHitsIDs[GetHitIDIndex( (EFigure)m_AnalyzerResults.GetLineDataAt(i).eFigure,
		        m_AnalyzerResults.GetLineDataAt(i).nCount )];

		//////////////////////////////////////////
		GameStatUnit_t gstat(m_AnalyzerResults.GetLineDataAt(i).currWin, 1);
        updateGameStatUnits(trID, unCountsID, uchDenomIndex, gstat );

	}

	// scatters //////////////////////////////////////////////////////
	int nScatterCount = 0;
	for( i = 0; i < REELS_COUNT; i++ ){
		if( m_AnalyzerResults.nScattersPos[i] != (-1) ){
			nScatterCount++;
		}
	}
	if( nScatterCount > 2 ){
		// counts //////////////////////////
		const char* unCountsID = unNVRAMHitsIDs[GetHitIDIndex( ef10_scatter, nScatterCount )];

		GameStatUnit_t gstat(m_AnalyzerResults.GetScatterWin(), 1);
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
			m_bUserAutoModeON = false;
			m_bUserAutoMode = false;
			m_bAutoInSound = false;
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
	}

	if( (gGPMgr.GetHatCurrState() == esdReadyGame || gGPMgr.GetHatCurrState() == esdReadyGamePlus ||
				gGPMgr.GetHatCurrState() == esdBusyGame) &&	(gGPMgr.GetHatPrevState() == esdCongratulation ) )
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
        if (m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted())
        {
            m_reelsArea.m_ActionMgr.m_CoinAnim.Pause();
        }

		if ( gGPMgr.GetHatCurrState() == esdWarning )
		{
			if( m_bUserAutoMode || m_bUserAutoModeON ){
				m_bUserAutoModeON = false;
				m_bUserAutoMode = false;
				m_bAutoInSound = false;

				m_ucButtonsState = MG_BUTTONS_STATE_BETTING;
			}
		}

		unsigned char ucLastButtonsState = m_ucButtonsState;
		SetDisabledButtons();
		//In this case m_ucButtonState stores the buttons state before the error appears
		m_ucButtonsState = ucLastButtonsState;
	}

    if ( gGPMgr.GetHatPrevState() == esdNonFatalError || gGPMgr.GetHatPrevState() == esdWarning)
    {
        if (m_reelsArea.CoinAnimCanStart() && gMoneyCounting.GetLeftAmount() != 0)
        {
            m_reelsArea.m_ActionMgr.m_CoinAnim.Continue();
        }
    }

	if( (gGPMgr.GetHatCurrState() == esdNonFatalError) && (gGPMgr.GetHatPrevState() == esdJPGameGap) )
	{

		m_bUserAutoModeON = false;
		m_bUserAutoMode = false;
		m_bAutoInSound = false;

		if(gActionBridgeMgr.GetBridgeType() == ActionBridge::eTPlayNextGame)
			gActionBridgeMgr.GetBridge()->OnDestroy();
	}

	//BUG 19238
	if(gGPMgr.GetHatCurrState() == esdNonFatalError && (gGPMgr.GetHatPrevState() == esdReadyGame || gGPMgr.GetHatPrevState() == esdReadyGamePlus ))
	{
		m_bUserAutoModeON = false;
		m_bUserAutoMode = false;
		m_bAutoInSound = false;
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
	return 0;
}

void MainGame::SetFG( int nFGCount, int nFGMult, int nExtraWild )
{
	if( nFGCount > 0 ){
		m_bFG = true;
		/** Moved in status line */
		gStatusLine.SetFreeSpinsFeature();
		SetBettingButtons();
		m_crFGMotherWin = (m_crFGMotherWin != 0)? m_crFGMotherWin : gGPMgr.Win_Get();

		m_nExtraWild = nExtraWild;
        m_reelsArea.Preinit((EFigure)nExtraWild);
		m_reelsArea.m_ActionMgr.m_AnimMgr.m_bStartOnlyScatterSound = false;
		m_reelsArea.m_ActionMgr.StopAction();
	}
	else{
		m_bFG = false;
		m_nFGCount = 0;
		m_nFGTotalCount = 0;
		m_reelsArea.SetOnlyFiguresResults( m_efResultsToShowAfterFG );
		m_reelsArea.m_ActionMgr.StartAction( false );
		m_nExtraWild = FIGURES_NUM;
		gStatusLine.DisableFreeGame();
        for(auto&& reel : m_reelsArea.m_reels) {
            reel.SetDrawFrame(false);
        }
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

	if(!IsTherePendingJP()) {
		gActionBridgeMgr.SwitchToBridge(ActionBridge::eTPlayNextGame);
	}

}

void MainGame::StartCreditCounting()
{
	Currency crWin = gGPMgr.Win_Get();

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


void MainGame::StartRetriggerSplash(){

	m_ucState = MG_STATE_WINSPLASH;

    m_WinSplash.SetFGBonusWin( 1, EMPERORS_DREAM_NUMBER_OF_FREE_GAMES );

	gMoneyCounting.SetSilentMode(false);
	gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
	gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
}

void MainGame::StartBonusSplash()
{
	SetDisabledButtons();
	// start

	if ( m_bUserAutoMode || m_bUserAutoModeON)
	{
		m_bUserAutoMode = false;
		m_bAutoInSound = false;
		m_bUserAutoModeON = false;
	}

	if( !m_bFG ){
		gRecordMgr.RecordData();
		//gGameStateMgr.RequestState( egsdBonus_1 );
	}

	m_ucState = MG_STATE_WINSPLASH;
    m_WinSplash.SetFGBonusWin( 1, EMPERORS_DREAM_NUMBER_OF_FREE_GAMES );
	gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
	gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
	gGPMgr.SetDemoMode();
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
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_MG_READ_FAILED); // 1000402
		return;
	}
	if (crExtraGameWin > 0)
	{
		crExtraGameWin -= crWinAmount;

		if (!AddTransactionData(trID, "NVRAM_EXTRA_GAME_MG", &crExtraGameWin, sizeof(crExtraGameWin)))
		{
			SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_MG_WRITE_FAILED); // 1000403
			return;
		}

		return;
	}

	if(!GetParameter("NVRAM_EXTRA_GAME_EXTERNAL", (void*)&crExtraGameWin, sizeof(crExtraGameWin)))
	{
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_EXTERNAL_READ_FAILED); // 1000404
		return;
	}
	if (crExtraGameWin > 0)
	{
		crExtraGameWin -= crWinAmount;

		if (!AddTransactionData(trID, "NVRAM_EXTRA_GAME_EXTERNAL", &crExtraGameWin, sizeof(crExtraGameWin)))
		{
			SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_EXTERNAL_WRITE_FAILED); // 1000405
			return;
		}

		return;
	}

	if(!GetParameter("NVRAM_EXTRA_GAME_JP", (void*)&crExtraGameWin, sizeof(crExtraGameWin)))
	{
		SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_JP_READ_FAILED); // 1000406
		return;
	}
	if (crExtraGameWin > 0)
	{
		crExtraGameWin -= crWinAmount;

		if (!AddTransactionData(trID, "NVRAM_EXTRA_GAME_JP", &crExtraGameWin, sizeof(crExtraGameWin)))
		{
			SetGeneralError(ERROR_MG_NVRAM_EXTRA_GAME_JP_WRITE_FAILED); // 1000407
			return;
		}

		return;
	}

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

void MainGame::SetLine( int nLinesToSet )
{
	m_reelsArea.m_ActionMgr.StopAction();

	gGPMgr.LinesCount_Set((int)(nLinesToSet));

	m_reelsArea.m_ActionMgr.SetBetLines(nLinesToSet);

	gBetLinesControlAdapter.GetSndObj().PlayOptionSound();

	SetBettingButtons();
	gRecordMgr.RecordData();
	if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() )
	{
		if ( true == m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted() )//BUG 20504 #20 finish coin anim before info request
		{
			m_reelsArea.m_ActionMgr.StopCoinAnim(true);
		}

		gP3Info.ShowDefaultScreen();
	}
}

bool MainGame::ProcessLinesButton(int nLinesCount)
{
	if( gBetLinesControlAdapter.FixedLines() )
		return false;

	if( m_ucState == MG_STATE_BETTING || m_ucState == MG_STATE_BETTING_PLUS ){

		FromBettingPlusToBetting();
		if( SwitchInJPState()  ) {
			return false;
		}

		if( (gGPMgr.GetHatCurrState() != esdReadyGame) && (gGPMgr.GetHatCurrState() != esdJPGameGap) ) {
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
	}
	else if( gMoneyCounting.GetLeftAmount() != 0 ){

		m_bFGFastStoped = true;
		gMoneyCounting.SetFastMode();
		SetDisabledButtons();
	}

	return true;
}

bool MainGame::ProcessBetButton(int nBet, int nSoundIdx)
{
	if( m_ucState == MG_STATE_BETTING || m_ucState == MG_STATE_BETTING_PLUS ){

		FromBettingPlusToBetting();

		//TODO if there is a switch to gap here, the current code will not work

		if( SwitchInJPState() ){
			return false;
		}

		if( (gGPMgr.GetHatCurrState() != esdReadyGame) && (gGPMgr.GetHatCurrState() != esdJPGameGap) ) {
			return false;
		}

		if (m_bBetButtonsPlay)
			gBetLinesControlAdapter.GetSndObj().MuteBetSound();

		SetBet(nBet, nSoundIdx);

		if (m_bBetButtonsPlay)
		{
			if(gGameStateMgr.GetCurrentState() == egsdMGBetting)
				DoStartButton();
			else
				gActionBridgeMgr.SwitchToBridge(ActionBridge::eTPlayNextGame);
		}
	}
	else if( gMoneyCounting.GetLeftAmount() != 0 )
	{
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

bool MainGame::GetAutoModeOff(){
	return 	m_bIsAutoModeOff;
}

#ifdef USE_EGT_DEMO
void MainGame::InitTestDemo(){

    if(HatApplication::GetInstance().m_DemoManager->GetCurrentDemoType() == eDemoType::eReelsDemo){

        vector<SPicDef*> spicdefs_vec;
        char buff[255];
        for(unsigned char i = 0; i < FIGURES_NUM; i++){
            sprintf(buff, "REEL_EF_%d",i+1);
            spicdefs_vec.push_back(gGameRM.GetPicture(buff));
        }

        GameVariantsComponent::GameType eGameType = GameVariantsComponent::GameType::MainGame;
        if ( m_bFG )
        {
            eGameType = GameVariantsComponent::GameType::FreeGame;
        }
        CombinationsDemo::Instance().FillDemoData(spicdefs_vec, REELS_COUNT, eGameType);
        CombinationsDemo::Instance().m_DemoLineSelector.SetNLines(gGPMgr.LinesCount_Get());
        for( int line = 0; line < gGPMgr.LinesCount_Get(); line++ ){
            for( unsigned int reelNo = 0; reelNo < REELS_COUNT; reelNo++ ){
                CombinationsDemo::Instance().m_DemoLineSelector.InsertLineValue(line , gucWinLines[line][reelNo]);
            }
        }
    }
    else if(HatApplication::GetInstance().m_DemoManager->GetCurrentDemoType() == eDemoType::eExpWildDemo)
    {
        int nNumberOfBonusFigs = 9;
        ExpWildDemo::Instance().SetExpWildDemo(nNumberOfBonusFigs, 0, "REEL_EF_");
    }

}
#endif

void MainGame::OnJPMProgressiveReady()
{
	gVBMgr.StopTimer(this, MG_TIMER_PROGRESSIVE_RECOVER);
}

bool MainGame::IsFirstFreeGame(){

	bool bRes=false;
    
	if ( (m_nFGOriginalCount == (m_nFGCount)) &&
					(m_nFGOriginalCount == m_nFGTotalCount) && m_bFG ){
		bRes = true;
	}
	return bRes;
}

bool MainGame::IsFirstFreeGameCorr() {
    if(m_bFG && ((m_nFGOriginalCount - m_nFGCount) == m_nFGOriginalCount || m_nFGOriginalCount == m_nFGCount)) {
        return true;
    }
    if(m_nFGOriginalCount - m_nFGCount == 1) {
        if(m_ucState == MG_STATE_BETTING && m_bFG) {
            return false;
        } 
        else {
            return true;
        }
    }   
    return false;
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

bool MainGame::IsInFreeGame()
{
	if( m_nExtraWild == FIGURES_NUM )  {
		return false;
	}

	if(!gMainGame.m_bFG) {
		return false;
	}

	if(IsFirstFreeGame()){
		return true;
	}
	return true;
}

void MainGame::TakeWin(){
  if( gMoneyCounting.GetLeftAmount() != 0 ) {
    gMoneyCounting.SetFastMode();
    SetDisabledButtons();
  }
  else if (egsdMGBettingPlus == gGameStateMgr.GetCurrentState())
	{
		if(gGPMgr.AnyLimitExceeded() )
		{
			gpBasicSound->StartSound(gGameRM.GetSound("TAKE_WIN_BUTTON"));
			FromBettingPlusToBetting();
			SwitchInJPState();
		}
		else
		{
			StartCreditCounting();
		}
	}
}

void MainGame::SetMainGameID(int gameId){
        m_nGameID = gameId;
}

int MainGame::GetMainGameID() const {
        return m_nGameID;
}

/** the global MainGame object */
MainGame gMainGame;

//================================ Helper functions =========================================

void GetSlidingWindow( GameVariantsComponent::GameType gameType,
					   unsigned char nVariant,
					   unsigned int nReel,
					   unsigned int nMiddleIndex,
					   unsigned char* ucResult )
{
	auto gameVariantsPtr = GameVariantsComponent::SafeGet( gGameRestrictionMgr );
	
	auto slidingWindow = gameVariantsPtr->CopyReelSlidingWindow( gameType, nVariant, nReel, nMiddleIndex );


#ifdef EGT_DEBUG
    if( *(ucResult + (slidingWindow.size() - 1)) == '\0' )//check if ucResult is pointing to array big enough to take slidinWindow values
    {
        eCDebug( LOG_CATEGORY_GAMES ) << "Slinging window result out of range\n";
    }
#endif
	for ( auto figID : slidingWindow)
	{
		*ucResult = (unsigned char) figID;
		ucResult++;
	}
}

bool MainGame::NeedToShowReelsInMirrorScreen()
{
    return m_ucState == MG_STATE_WINSPLASH || IsStartFGSplashShown();
}

//---------------------------------------------------------------------------------

