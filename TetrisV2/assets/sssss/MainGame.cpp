/* MainGame.cpp

	MainGame class; responsible for all states during the main game

	Author: Georgi Dragandjikov

	$Id: MainGame.cpp,v 1.1.2.46 2015/11/13 12:16:59 anton.boykov Exp $


	Copyright (c) 2004-2007 EGT Ltd.
	All rights reserved

	More information at: http://www.egt-bg.com
 */

#include "MainGame.h"
#include "mm.h"
#include "ui_mgr/ButtonsUtil.h"
#include "gp_mgr/GPMgr.h"
#include "money_counting/MoneyCounting.h"
#include "game_state_mgr/GameStateMgr.h"
#include <device_mgr/ButtonDefs.h>
#include <project_definitions/hat_api/HatApi.h>
#include "status_line/StatusLine.h"
#include "game_draw_mgr/GameDrawManager.h"
#include <storage_mgr/StorageManagerApi.h>
#include "GameDefinitions.h"
#include <game_mgr/RGBManager.h>
#include <egt_lib/debug/egt_debug.h>
#include <egt_lib/utils/FormatFunc.h>
#include <jpm_mgr/JPMMgr.h>
#include "panel/PanelObject.h"
#include "p3_info/P3Info.h"
#include "ml_mgr/MLMgr.h"
#include <GlobalError.h>
#include "game_gamble/Gamble.h"
#include <aft_mgr/AFTMgr.h>
#include <limits>
#include "option_bet_control/GameOptionSchema.h"
#include "option_bet_control/OptionAndBetControlAdapter.h"
#include <ReelsDemo/Demo.h>
#include <ReelsDemo/DemoReelsArea.h>
#include "action_bridge/ActionBridgeMgr.h"
#include <screen_object/VideoControlMgr.h>
#include "IJurisdiction.h"
#include "Analyzer.h"
#include "MainGameDefs.h"
#include "panel/DenominationControl.h"
#include <h2_mgr/H2Mgr.h>
#include <game_mgr/GameMgr.h>
#include <jp_bonus_game/BonusGame.h>
#include <oled/KeyboardScenarioController.h>
#include <RestrictionComponents/GameReels/GameVariantsComponent.h>
#include <RestrictionComponents/GameConfiguration/StaticsComponent.h>
#include "game_settings/CommonGameSettings.h"
#include "ReelsDemo/SpecialDemo.h"
#include "../common/topper_mgr_game/TopperMgrGame.h"
#include <Components/RestrictionComponents/KeyboardCfg/VirtualKeyboardCfgComponent.h>
using namespace std;
using namespace RestrictionComponents;

static const char* unNVRAMHitsIDs[]=
{
        "NVRAM_GCP_3THREE_TEN",
        "NVRAM_GCP_4FOUR_TEN",
        "NVRAM_GCP_5FIVE_TEN",

        "NVRAM_GCP_3THREE_JACK",
        "NVRAM_GCP_4FOUR_JACK",
        "NVRAM_GCP_5FIVE_JACK",

        "NVRAM_GCP_3THREE_QUEEN",
        "NVRAM_GCP_4FOUR_QUEEN",
        "NVRAM_GCP_5FIVE_QUEEN",

        "NVRAM_GCP_3THREE_KING",
        "NVRAM_GCP_4FOUR_KING",
        "NVRAM_GCP_5FIVE_KING",

        "NVRAM_GCP_3THREE_ACE",
        "NVRAM_GCP_4FOUR_ACE",
        "NVRAM_GCP_5FIVE_ACE",

        "NVRAM_GCP_3THREE_FIREWORKS",
        "NVRAM_GCP_4FOUR_FIREWORKS",
        "NVRAM_GCP_5FIVE_FIREWORKS",

        "NVRAM_GCP_3THREE_PAPIRUS",
        "NVRAM_GCP_4FOUR_PAPIRUS",
        "NVRAM_GCP_5FIVE_PAPIRUS",

        "NVRAM_GCP_3THREE_LANTERN",
        "NVRAM_GCP_4FOUR_LANTERN",
        "NVRAM_GCP_5FIVE_LANTERN",

        "NVRAM_GCP_3THREE_WOMAN",
        "NVRAM_GCP_4FOUR_WOMAN",
        "NVRAM_GCP_5FIVE_WOMAN",

        "NVRAM_GCP_3THREE_MAN",
        "NVRAM_GCP_4FOUR_MAN",
        "NVRAM_GCP_5FIVE_MAN",

        "NVRAM_GCP_3THREE_SCATTER",
        "NVRAM_GCP_4FOUR_SCATTER",
        "NVRAM_GCP_5FIVE_SCATTER"
};

static void GetSlidingWindow( GameVariantsComponent::GameType gameType,
                              unsigned char nVariant,
                              unsigned int nReel,
                              unsigned int nMiddleIndex,
                              unsigned char* ucResult);

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

// tmp; test results ///////////////////////////////
const int nTestResultsCount = 20;
int gnTestResults[ALL_FIGURES_PER_REEL*nTestResultsCount][REELS_COUNT] = {

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },


		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		{ 7, 3, 3, 5, 3 },
		{ 1, 9, 4, 9, 5 },
		{ 0, 2, 9, 0, 4 },
		{ 9, 4, 5, 4, 9 },
		{ 2, 6, 0, 1, 0 },

		// BWD ///////////////////////////////////////////////

        // Fireworks
		{ 1,  9,  4,  7,  5  },
		{ 2,  1,  4,  2,  1  },
		{ 5,  5,  5,  0,  0  },
        { 0,  4,  2,  1,  3  },
		{ 3,  3,  7,  4,  2  },

        // Papirus
		{ 2,  3,  4,  0,  5  },
        { 3,  2,  8,  0,  1  },
		{ 6,  6,  6,  3,  3  },
        { 0,  2,  4,  2,  3  },
		{ 3,  1,  5,  6,  0  },

        // Lantern
		{ 1,  0,  2,  2,  1  },
		{ 2,  5,  0,  0,  0  },
		{ 7,  7,  7,  1,  5  },
		{ 4,  3,  6,  5,  2  },
		{ 0,  1,  9,  8, 10  },

        // Woman
		{ 4,  1,  1,  2,  9  },
		{ 7,  4,  0,  6,  4  },
		{ 8,  8,  8,  0,  0  },
        { 1,  9,  5,  1,  5  },
		{ 3,  3,  3,  5,  0  },

        // Man
		{ 0,  2,  2,  0,  4  },
		{ 5,  3,  6,  3,  0  },
		{ 9,  9,  9,  1,  1  },
		{ 6,  1,  4,  2,  8  },
		{ 3,  4,  1,  4,  3  },

		// Wild
		{ 2,  0,  1,  7,  7  },
		{ 7,  4,  5,  2,  3  },
		{ 0, 10, 10, 10,  0  },
		{ 1,  2,  1,  8,  5  },
		{ 3,  1, 10,  1, 12  },

		// Scatter
		{ 4,  4,  4,  7,  5  },
		{ 0,  3,  7,  0,  6  },
		{11, 11, 11,  1,  1  },
		{ 0,  2,  9,  8,  3  },
		{ 5,  5,  5,  5,  2  },

		// Big Win
		{ 4,  4,  4,  7,  5  },
		{ 9,  9,  9,  9,  9  },
		{ 9,  9,  9,  9,  9  },
		{ 9,  9,  9,  9,  9  },
		{ 5,  5,  5,  5,  2  },
};

////////////////////////////////////////////////////
///HISTORY PARSER
////////////////////////////////////////////////////
namespace {

    struct Params {
        int gameId = 0;
        Currency betMultiplier{ 0 };
        int waysBet{ 0_dollars };
        PricePerCredit pricePerCredit{ 0_dollars };
        bool hasFreeGames{ false };
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
     Currency crBetPerLine = 1;
     Currency crBets[GAME_LINES_COUNT];
     for( int i = 0; i < GAME_LINES_COUNT; i++ ){
         if( i < GAME_LINES_COUNT ){
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

        Analyzer analyzer;
        int gameActiveReels = REELS_COUNT;

        analyzer.Init(mainGameFigues,
        			  crBets,
                      gameActiveReels,
                      params.waysBet,
                      false,
                      false,
                      1,
                      1,
                      params.hasFreeGames,
                      FIGURES_NUM );

        auto gameId = params.gameId;
        AnalyzerResults analResults( FIGURES_NUM*2, VISIBLE_FIGURES_PER_REEL, REELS_COUNT,
                                    gameId,
                                    GetGameRestrictionMgrGetter() );
        analyzer.GetResults( &analResults );
        
        auto waysResult = result.mutable_waysresult();
        if( params.hasFreeGames ) {
            waysResult->mutable_multiplier()->set_value( multiplier );
        }

        // standard reels
        auto resultReels = waysResult->mutable_visiblereels();
        for( int i = 0; i < REELS_COUNT; ++i ) {
            auto reel = resultReels->add_reels();
            for( int j = 0; j < VISIBLE_FIGURES_PER_REEL; ++j ) {
                auto figure = reel->add_figures();
                figure->add_id(analResults.nFigures[j][i]);
            }
        }

        // standard lines 
        for( int i = 0; i < analResults.GetWinFiguresCount(); ++i ) {
            auto combination = waysResult->add_line();
            for( int j = 0; j < analResults.GetFiguresDataAt(i).nCount; ++j ) {
                auto figureWin = combination->mutable_figurewin();
                auto figure = figureWin->add_figures();
                figure->add_id( analResults.GetFiguresDataAt(i).eFigure );
            }

            combination->mutable_linetype()->set_value( "way" );
            combination->mutable_winamount()->set_value( analResults.GetFiguresDataAt(i).currWin );
            combination->add_linemultiplier()->set_value( analResults.GetFiguresDataAt(i).nMultiply );
        }
        if( analResults.GetFiguresWin() > 0 ) {
            auto waysWin = waysResult->mutable_lineswin();
            waysWin->set_value(analResults.GetFiguresWin());
        }

        if( analResults.GetScatterWin() > 0 ) {
            auto bonus = waysResult->mutable_bonus();
            auto scatter = bonus->add_bonuses();
            auto bonus_name = scatter->mutable_name();
            bonus_name->set_value( "scatter" );
            auto award = scatter->mutable_award();
            auto winAmount = award->mutable_winamount();
            winAmount->set_value( analResults.GetScatterWin().ToCents() );
            unsigned nScatterCount = 0;
            
            for( unsigned char i = 0; i < REELS_COUNT; ++i ) {
                if( analResults.nScattersPos[i] != (-1) )
                    nScatterCount++;
            }
            
            for( unsigned char i = 0; i < nScatterCount; ++i ) {
                auto figureWin = scatter->mutable_figurewin();
                auto figure  = figureWin->add_figures();
                figure -> add_id( static_cast<int>( ef12_scatter ) );
            }
            
            if( gameData.has_bonus() ) {
                const auto& bonusData = gameData.bonus();
                if( bonusData.has_freegames() ) {
                    auto freeGames = award->mutable_freegames();
                    freeGames->set_value(bonusData.freegames().value());
                }
            }
        }

        if(analResults.bBonus1)
        {
            auto bonus = waysResult->mutable_bonus();
            auto bonus1 = bonus->add_bonuses();
            auto bonus_name = bonus1->mutable_name();
            bonus_name->set_value("bonus1");
        }

        if(analResults.bBonus2)
        {
            auto bonus = waysResult->mutable_bonus();
            auto bonus2 = bonus->add_bonuses();
            auto bonus_name = bonus2->mutable_name();
            bonus_name->set_value("bonus2");
        }

}


    analyzer::MatchResult GetAnalyzerResults( const history::Entry &entry, int gameId ) {
        
        Params params;
        params.gameId = gameId;
        
        const auto& entryInfo = entry.entryinfo();
        if( entryInfo.has_invoice() ) {
            const auto& invoice = entryInfo.invoice();
            if( invoice.has_pricepercredit() ) {
                params.pricePerCredit = PricePerCredit( Currency::FromCents( invoice.pricepercredit().value() ) );
            }
        }
        
        analyzer::MatchResult match;
        auto& matchInfo = *match.mutable_matchinfo();
        
        auto& id = *matchInfo.mutable_gameid();
        id.set_value(gameId);
        
        auto& name = *matchInfo.mutable_gamename();
        name.set_value("Great China");
        
        auto& timestamp = *matchInfo.mutable_timestamp();
        timestamp = entryInfo.timestamp();
        
        auto& gameVariant = *matchInfo.mutable_gamevariant();
        gameVariant = entryInfo.gamevariant();
        
        auto& invoice = *matchInfo.mutable_invoice();
        invoice = entryInfo.invoice();
        
        auto& waysInfo = *matchInfo.mutable_waysinfo();
        waysInfo = entryInfo.waysinfo();
        
        auto& totalBetField = *matchInfo.mutable_totalbet();
        auto totalBetValue = waysInfo.multiplier().value() * waysInfo.waysbet().value()*params.pricePerCredit.cents;
        totalBetField.set_value(totalBetValue);
        params.waysBet = waysInfo.waysbet().value();
        params.betMultiplier = params.pricePerCredit.cents * waysInfo.multiplier().value();
        
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
        
        for( const auto& gameData : freeGameTurns ) {
            auto freeGameResults = match.add_results();
            params.hasFreeGames = true;
            ParseGameData( *freeGameResults, gameData, params );
        }
        
        return match;
    }
}
MainGame::MainGame()
	 	: m_ucState()
	 	, m_ucLogFigResults()
	 	, m_ucDumpReelIndexes_1()
	 	, m_ucDumpReelIndexes_2()
	 	, m_bFirstTime(false)
	 	, m_ucReelsFastStop()
        , m_unCurrPotStateValue(0)
        , m_unPotStateValue(0)
	 	, m_bUserAutoMode(false)
	 	, m_bIsAutoModeOff(false)
	 	, m_bUserAutoModeON(false)
	 	, m_bTestAutoMode(false)
	 	, m_bWinGame(false)
	 	, m_bFG(false)
	 	, m_bJpWon(false)
	 	, m_bThereNeedBonusAfterScatter(false)
	 	, m_nFGOriginalCount()
	 	, m_nFGTotalCount()
	 	, m_nFGCount()
	 	, m_nFGMult()
	 	, m_cSpecialSymbol()
	 	, m_bFGFastStoped(false)
	 	, m_efResultsToShowAfterFG()
	 	, m_efResultsToShowInFG()
	 	, m_bNeedToRecordBonusWin(false)
	 	, m_bBetButtonsPlay(false)
	 	, m_bLastGameIsFree(false)
	 	, m_bLastDraw(false)
	 	, m_nLastDrawCount()
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
        , m_AnalyzerResults(FIGURES_NUM*2, VISIBLE_FIGURES_PER_REEL, REELS_COUNT, m_nGameID, GetGameRestrictionMgrGetter())
	 	, m_ucVariant()
	 	, m_ucVariantLatestResults()
	 	, m_nJPLine()
	 	, m_bChinaJackpotConditions(false)
	 	, m_nChinaJackpotWin(false)
	 	, m_bPendingMystery(false)
	 	, m_nPendingJPBet(false)
	 	, m_bPendingBetSet(false)
{

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

void MainGame::LoadResources(){

    // creat signal
    if ( !m_gameSentinel ){
        m_gameSentinel = std::make_shared<egt::Bindable>();
        auto& binder = PluginFunctions();
        binder.ConnectSlot("Plugins_TopperToGameMsg", m_gameSentinel, [this]( const egt::UniMsg& msg ){  ConnectToTopper( msg ); } );
    }
}

void MainGame::InitlaizeTopper(){

    // loading topper animation
    egt::UniMsg msg;
    msg.name =  "additional_animation_scenario";
    msg.description = "Initialize";
    msg.AddValue( "GameID" , GetMainGameID() );
    msg.AddValue( "PotFrame" , GetPotCurrentFrame() );
    msg.AddValue( "PotAnim" , false );

    constexpr unsigned MAX_POT_FRAME = 4; 
    std::array< std::string , MAX_POT_FRAME > PicturePotID;
    PicturePotID.fill( "STATIC_POT_" );
    unsigned pot_id( 0 );
    for ( std::string& single_pot_id : PicturePotID ){
        single_pot_id.append( std::to_string(  pot_id++ ) );
    }

    int nStaticPot = GetPotCurrentFrame();
    msg.AddValue( "PotFrame" , nStaticPot );

    msg.AddValue( "PotResources" , PicturePotID  );
    PluginFunctions().DispatchSignal("Plugin_AdditionaAnimation" , msg  );
}

void MainGame::ConnectToTopper( const egt::UniMsg& msg ){

    if ( msg.name == "additional_animation_scenario" ){
        if ( msg.description == "AnimationFinished" ){
            unsigned anim_id = AnimationLength;

            if ( msg.HasValue( "AnimType" ) ){
                msg.GetValue( "AnimType" , anim_id );
                if ( anim_id == SmallCoinAnimation || anim_id == Default ){
                	m_reelsArea.m_dFlyCoinAnim.SetVisible(false);
                }
            }
        }
        else if ( msg.description == "InitWithMsg" ){
            InitlaizeTopper();
        }
    }
}

void MainGame::UnloadResources(){

    // delete signal
    m_gameSentinel.reset();

    // deinitlaize topper
    egt::UniMsg msg;
    msg.name =  "additional_animation_scenario";
    msg.description = "Deinitialize";
    PluginFunctions().DispatchSignal("Plugin_AdditionaAnimation" , msg);
};

MainGame::~MainGame()
{
}

bool MainGame::Init()
{
    auto& adaptor = egt::GetAdaptor();
    adaptor.getAnalyzerResults = [this]( const history::Entry& entry )
    {
        return GetAnalyzerResults( entry, GetMainGameID() );
    };

    if ( false == InitHitIDs() ) {
        eCDebug(LOG_CATEGORY_GAMES) << __FILE__ << ":" << __LINE__ << " InitHitIDs() FAIL "<< "\n";
        return false;
    }

	m_bPendingBetSet = false;
	m_bLastDraw = false;
	m_nLastDrawCount = 0;
	m_bChinaJackpotConditions = false;
	m_nChinaJackpotWin = 0;
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
	m_bThereNeedBonusAfterScatter = false;
	m_crProgressiveWin = 0;

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

	m_cSpecialSymbol = FIGURES_NUM;

	m_bFirstTime = true;

	m_ucState = MG_STATE_BETTING;

	m_bLastGameIsFree = false;

	if(!m_reelsArea.Init()) {
        eCDebug(LOG_CATEGORY_GAMES) << "[ GREAT CHINA ] - m_reelsArea::Init() FAIL  "<< "\n" ;
		return false;
	}

	if(!m_FGSeals.Init()) {
        eCDebug(LOG_CATEGORY_GAMES) << "[ GREAT CHINA ] - m_FGSeals::Init() FAIL  "<< "\n" ;
		return false;
	}

	if(!m_WinSplash.Init()) {
        eCDebug(LOG_CATEGORY_GAMES) << "[ GREAT CHINA ] - m_WinSplash::Init() FAIL  "<< "\n" ;
		return false;
	}

	if(!m_ExtraGame.Init() ) {
	eCDebug(LOG_CATEGORY_GAMES) << "[ GREAT CHINA ] - m_StartFGSplash::Init() FAIL  "<< "\n" ;
		return false;
	}

    if(!m_StartFGSplash.Init())
    {
    eCDebug(LOG_CATEGORY_GAMES) << "[ GREAT CHINA ] - m_ExtraGame::Init() FAIL  "<< "\n" ;
        return false;
    }

	if(!m_BigWinDemo.Init() ) {
        eCDebug(LOG_CATEGORY_GAMES) << "[ GREAT CHINA ] - m_BigWinDemo::Init() FAIL  "<< "\n" ;
		return false;
	}

	m_nWinSplashCount = 0;
	m_ucBWDCombination = 255;
	m_nJPLine = (-1);
	m_ucVariant = 0;
	m_ucVariantLatestResults = 0;

	const char* nvram_parameter = gGPMgr.GetHybridParameter(eNvramGameVariant);
	if( !GetParameter(nvram_parameter, (void*)&m_ucVariant, sizeof( m_ucVariant ) ) ){
		eCDebug( LOG_CATEGORY_GAMES ) << "Get NVRAM_SL_GAME_VARIANT failed!\n";
		SetGeneralError(910002);
    }
	m_bUserAutoMode = false;
	m_bAutoInSound = false;
	m_bUserAutoModeON = false;
	m_bTestAutoMode = false;
	m_bIsAutoModeOff = false;

	m_bWinGame = false;

	m_bTimerLittleCounting = false;


	for( int i = 0; i < REELS_COUNT; i++ ){
		m_ucDumpReelIndexes_1[i] = 0;
		m_ucDumpReelIndexes_2[i] = 0;
	}

	m_sndGamble = gGameRM.GetSound( "MG_BUTTON_DOUBLE" );
	m_sndCashOut = gGameRM.GetSound( "MG_BUTTON_CASHOUT" );

	m_sndUserAutoModeIn = gGameRM.GetSound( "USER_AUTO_MODE_IN" );
	m_sndUserAutoModeOut = gGameRM.GetSound( "USER_AUTO_MODE_OUT" );

    if(!gGameRM.GetRegister().RegisterPicture("JPA_KNOBS_BACKGROUND", FIRST_VIEW_GROUP) ||
       !gGameRM.GetRegister().RegisterPicture("GCP_BONUS_HIT_1", FIRST_VIEW_GROUP) ||
       !gGameRM.GetRegister().RegisterPicture("GCP_BONUS_HIT_2", FIRST_VIEW_GROUP) ||
       !gGameRM.GetRegister().RegisterPicture("GCP_BONUS_HIT_3", FIRST_VIEW_GROUP) ||
       !gGameRM.GetRegister().RegisterPicture("GCP_BONUS_HIT_4", FIRST_VIEW_GROUP) )
    {
        return false;
    }


	gVBMgr.StartTimer( this, MG_TIMER_REELING_DRAW, 0, MG_PERIOD_REELING_DRAW );

	gGameStateMgr.RegisterClient( egscMGObject, this );
	gRecordMgr.AddClient( this );
	gGPMgr.AddClient( this );

	// Enable/Disable BigWinDemo //////////////////////////////
	m_BigWinDemo.SetToEnable( gGPMgr.GameSettings_Get().uchBigWinDemo ? true:false );
    
    m_AnalyzerResults.SetGameRestrictionMgr(GetGameRestrictionMgrGetter());
    m_AnalyzerResults.SetGameID( m_nGameID );
    
	StartLastDraw();

	return true;
}

void MainGame::DeInit()
{
	m_ExtraGame.Deinit();
}

bool MainGame::StateChanging( bool bStackDirection, EGameStateDef gsdOldState, EGameStateDef gsdNewState )
{
	return true;
}

bool MainGame::StateChanged( bool bStackDirection, EGameStateDef gsdOldState, EGameStateDef gsdNewState )
{
 	if( (gsdOldState == egsdMGBonusWin || gsdOldState == egsdFGBonusWin ) &&
            ( gsdNewState == egsdMGBetting || gsdNewState == egsdMGBettingPlus || gsdNewState == egsdFGBetting ) )
    {
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

	if( ( gsdNewState == egsdMGBonusWin && gsdOldState == egsdBonus_1 ) ){
		m_ucState = MG_STATE_WINSPLASH;
		m_bWinGame = true;
	}
	else if( (gsdNewState == egsdMGBetting || gsdNewState == egsdMGBettingPlus ) && gsdOldState == egsdBonus_1 ){

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
    else if( gsdNewState == egsdMGBonusWin && gsdOldState == egsdFGBetting )
    {
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
	else if( gsdNewState == egsdFGBetting && (gsdOldState == egsdMGBonusWin || gsdOldState == egsdBonus_1) ){

		if( m_nFGCount > 0 ){
			StartAutoFG( true , (gsdOldState == egsdBonus_1 ) );
		}

		SetBettingButtons();
		gMoneyCounting.SetSilentMode(false);
		m_bTestAutoMode = false;
	}
	else if( gsdNewState == egsdFGReeling && gsdOldState == egsdFGBetting ) {
	}
	else if( gsdNewState == egsdFGBetting && gsdOldState == egsdFGReeling ) {
		if( m_nFGCount > 0 ){
			StartAutoFG( m_bFGFastStoped );
		}
		SetBettingButtons();
	}
	else if( gsdNewState == egsdFGBonusWin && gsdOldState == egsdFGReeling ) {
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
				m_reelsArea.m_ActionMgr.m_CoinAnim.Stop( true );//BUG 20019 #28
			}
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
	if( m_bFirstTime ){

		m_bFirstTime = false;

		if( m_ucState == MG_STATE_REELING ) {
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

    gpBasicDraw->DrawPicture( 0, 0, 0, gGameRM.GetPicture( "JPA_KNOBS_BACKGROUND" ) );

    if ( gBonusGame.DrawReelsUnderBonus() ){
        m_reelsArea.Draw();
    }

    // draw splash
    gBonusGame.DrawCoins();

	if( m_ucState == MG_STATE_WINSPLASH ){
		m_WinSplash.Draw();
	}

	if((!m_bFG ) && ( m_ucState != MG_STATE_WINSPLASH) && ( m_ucState == MG_STATE_BETTING || m_ucState == MG_STATE_BIGWINDEMO)){
		m_BigWinDemo.Draw( m_ucState == MG_STATE_BIGWINDEMO  );
	}

    m_StartFGSplash.OnDraw();

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

	if( IsButtonForFastCollect(inputData) ) {
		m_reelsArea.m_ActionMgr.m_AnimMgr.SetSkipScatterAnim(m_reelsArea.m_ucRAStatus,
				m_reelsArea.m_ActionMgr.m_bThereIsUndoneScatter, m_bFG);
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

		if( inputData.uiButtons & BUTTON_STARTSTOP && inputData.uiPressed == BUTTON_STARTSTOP ){
			if( gMoneyCounting.GetLeftAmount() != 0 ){
				gMoneyCounting.SetFastMode();
				m_bFGFastStoped = true;
				SetDisabledButtons();
			}
			else{
				if( m_reelsArea.GetRAStatus() == RA_STATUS_REELING_CAN_STOP ||
					m_reelsArea.GetRAStatus() == RA_STATUS_REELING_CAN_NOT_STOP )
				{
					m_reelsArea.StartButton();
				}
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
	if( m_bUserAutoModeON ) {
		if( inputData.uiButtons == BUTTON_AUTO && inputData.uiPressed == BUTTON_AUTO ){
			m_bUserAutoModeON = false;
			m_bUserAutoMode = false;
			m_bAutoInSound = false;
			return;
		}
	}
	/////////////////////////////////////////////////////////////////

	// IMPORTANT: must be the first object to receive buttons and touch

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
	if( inputData.touchData1.bPressed || inputData.touchData1.bPressedNow ){
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
		if( !ProcessLinesButton( gBetLinesControlAdapter.GetLinesAccordingToOption(optValues.at(0)) )) return;
	}
	if( inputData.uiButtons == BUTTON_L2 && inputData.uiPressed == BUTTON_L2 ){
		if( !ProcessLinesButton( gBetLinesControlAdapter.GetLinesAccordingToOption(optValues.at(1)) )) return;
	}
	if( inputData.uiButtons == BUTTON_L3 && inputData.uiPressed == BUTTON_L3 ){
		if( !ProcessLinesButton( gBetLinesControlAdapter.GetLinesAccordingToOption(optValues.at(2)) )) return;
	}
	if( inputData.uiButtons == BUTTON_L4 && inputData.uiPressed == BUTTON_L4 ){
		if( !ProcessLinesButton( gBetLinesControlAdapter.GetLinesAccordingToOption(optValues.at(3)) )) return;
	}
	if( inputData.uiButtons == BUTTON_L5 && inputData.uiPressed == BUTTON_L5 ){
		if( !ProcessLinesButton( gBetLinesControlAdapter.GetLinesAccordingToOption(optValues.at(4)) )) return;
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
        
         if (  m_WinSplash.IsRetrigShown() ){
             m_WinSplash.Interrupt();
             return;
         }

		// second edition start fg splash ///////////////////

		if ( m_StartFGSplash.IsShown() ){

			m_StartFGSplash.Hide();
			if( !m_bFG ){
				gRecordMgr.RecordData();
			}

            SetDisabledButtons();
            m_WinSplash.StartIntro();
            PluginFunctions().DispatchSignal(signal_names::OnFGStart);
            gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
            gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
			gGPMgr.SetDemoMode();

			SetDisabledButtons();

			return;
		}
		if(m_ucButtonsState == MG_BUTTONS_STATE_DISABLED)
		{
			return;
		}

		//////////////////////////////////////////////////////
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

		}
	}

	if( inputData.uiButtons == BUTTON_TAKEWIN && inputData.uiPressed == BUTTON_TAKEWIN ){

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

	if( m_bFG )
	{
		SetDisabledButtons();

		if( m_nFGCount == 0 && gGameStateMgr.GetCurrentState() != egsdFGBonusWin )
		{
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
	m_crProgressiveWin = 0;
	int i = 0, j = 0;

	EFigure efResults[REELS_COUNT][ALL_FIGURES_PER_REEL];
	int nConfTmp[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
	for( i = 0; i < REELS_COUNT; i++ ){
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){
			efResults[i][j] = (EFigure)gnTestResults[ucCombination*ALL_FIGURES_PER_REEL+j][i];
			if( !m_bFG ){
				m_efResultsToShowAfterFG[i][j] = efResults[i][j];
			}
			else
			{
				m_efResultsToShowInFG[i][j] = efResults[i][j];
			}

			if( j > 0 && j < VISIBLE_FIGURES_PER_REEL+1 ){
				nConfTmp[j-1][i] = gnTestResults[ucCombination*ALL_FIGURES_PER_REEL+j][i];
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
	int nLinesCount = GAME_LINES_COUNT;
	Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
	for( i = 0; i < GAME_LINES_COUNT; i++ ){
		if( i < nLinesCount ){
			crBets[i] = crBetPerLine;
		}
		else{
			crBets[i] = 0;
		}
	}

	analyzer.Init( nConfTmp, crBets,
			gGPMgr.ActiveReels_Get(),
			gGPMgr.MultiwayBet_Get(),
			HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
			HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
			gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
			gGPMgr.BetPerLine_Get(), m_bFG, (EFigure) m_cSpecialSymbol );

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
	m_crProgressiveWin = 0;
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

	eCDebug(LOG_CATEGORY_GAMES) << "RESULTS:\t"
								<< nResults[0][1] << "\t"
								<< nResults[1][1] << "\t"
								<< nResults[2][1] << "\t"
								<< nResults[3][1] << "\t"
								<< nResults[4][1] << "\n\t\t\t\t\t"
								<< nResults[0][2] << "\t"
								<< nResults[1][2] << "\t"
								<< nResults[2][2] << "\t"
								<< nResults[3][2] << "\t"
								<< nResults[4][2] << "\n\t\t\t\t\t"
								<< nResults[0][3] << "\t"
								<< nResults[1][3] << "\t"
								<< nResults[2][3] << "\t"
								<< nResults[3][3] << "\t"
								<< nResults[4][3] << "\n";

	EFigure efResults[REELS_COUNT][ALL_FIGURES_PER_REEL];
	int nConfTmp[VISIBLE_FIGURES_PER_REEL][REELS_COUNT];
	for( i = 0; i < REELS_COUNT; i++ ){// reels
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ ){ // raws
			efResults[i][j] = (EFigure)nResults[i][j];
			if( !m_bFG )
			{
				m_efResultsToShowAfterFG[i][j] = efResults[i][j];
			}
			else
			{
				m_efResultsToShowInFG[i][j] = efResults[i][j];
			}

			if( j > 0 && j < VISIBLE_FIGURES_PER_REEL+1 ){
                    nConfTmp[j-1][i] = nResults[i][j];
			}
		}
	}

    SetPotStateValue(efResults);

	// last 50 result values //////////////////////////////////////
	for( i = 0; i < REELS_COUNT; i++ ){
		for ( j = 0; j < VISIBLE_FIGURES_PER_REEL; j++ )
			m_ucLogFigResults[j][i] = nConfTmp[j][i];
	}
	///////////////////////////////////////////////////////////

	Analyzer analyzer;
	Currency crBets[GAME_LINES_COUNT];
	int nLinesCount = GAME_LINES_COUNT;
	Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
	for( i = 0; i < GAME_LINES_COUNT; i++ ){
		if( i < nLinesCount ){
			crBets[i] = crBetPerLine;
		}
		else{
			crBets[i] = 0;
		}
	}

	analyzer.Init( 	nConfTmp, crBets,
			gGPMgr.ActiveReels_Get(),
			gGPMgr.MultiwayBet_Get(),
			HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
			HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
			gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
			gGPMgr.BetPerLine_Get(), m_bFG/*nCurrMult*/,  (EFigure) m_cSpecialSymbol );

	analyzer.GetResults( &m_AnalyzerResults );
#ifdef EGT_CREDIT_OBSERVER //define when EGT_DEBUG=1
    if (debCreditObserver::getInstance().isAcive())
    {
        Currency m_crWinFromLines_c = 0;

        for(int i = 0; i < m_AnalyzerResults.GetWinFiguresCount(); i++ ){
            m_crWinFromLines_c += m_AnalyzerResults.GetFiguresDataAt(i).currWin;
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
            return GetAnalyzerResults(entry, GetMainGameID());
        };
    }
#endif

	if(nID == MG_TIMER_PROGRESSIVE_RECOVER) {

		uint32_t ui32Level = 0;
		GameToHatData( GAME_TO_HAT_JP_GAME_READY, (const void*)&ui32Level, sizeof(ui32Level) );

	}

	else if( nID == MG_TIMER_REELING_DRAW ){

		if( m_reelsArea.ReadyForScatter() )
		{
//			 3x "ef13_scatter" hits
			if( !m_bFG && !m_bTestAutoMode )
			{
                gTopperMgrGame.ShowReelsInstantly(); //BUG 35222
                m_StartFGSplash.Show();
                PluginFunctions().DispatchSignal(signal_names::ShowFreeSpinPageRequest);

				RGBManager::eAction eActionRGB = RGBManager::eFreeGames;
				GameToHatData( GAME_TO_HAT_RGB_ACTION, (const void*)&eActionRGB, sizeof(eActionRGB) );
				if ( m_bUserAutoMode )
				{
					m_bUserAutoMode = false;
					m_bAutoInSound = false;
					m_bUserAutoModeON = false;
				}
				gKeyboardScenarioController->RequestFunctionUpdate();
				m_ucState = MG_STATE_WINSPLASH;
			}
			else
			{
				if( !m_bFG )
				{
					gRecordMgr.RecordData();
				}

				m_ucState = MG_STATE_WINSPLASH;

				if ( m_bFG )
				{
					m_WinSplash.StartRetrigger();

					SndInfo *pSndInfo= gGameRM.GetSound("COLLECT");
					if (gpBasicSound->IsPlaying(pSndInfo))
					{
						gpBasicSound->StopSound(pSndInfo);
					}
					if(m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted() )
					{
						m_reelsArea.m_ActionMgr.StopCoinAnim();
					}

					gGPMgr.SetDemoMode();

                    gKeyboardScenarioController->RequestFunctionUpdate();
				}
				else
				{
					// service auto games
					//m_WinSplash.StartFSIntro();
					m_WinSplash.StartIntro();
				}
				gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH );
				gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
			}
		}
        ////// Start Bonus Game  /////
        else if( m_reelsArea.ReadyForBonus1() ){
                gBonusGame.StartBonusGame();

                m_unPotStateValue = 0;
                m_unCurrPotStateValue = 0;
        }

		if( m_reelsArea.m_ActionMgr.NeedToSetFastCollect() ) {
			if(gMoneyCounting.GetLeftAmount() != 0)
			{
				gMoneyCounting.SetSilentMode();
				gMoneyCounting.SetFastMode();
			}
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
				m_ucState = MG_STATE_WINDEMO;
				if( m_reelsArea.m_ActionMgr.m_bScatter_Exist ){
					//if( m_bUserDemoMode )
					//	m_bUserAutoModeON = true;
					// about the two scatter situation m_bUserDemoMode = false;
					//Bug 4608 - new scenario for end of splashes.
					if (gMoneyCounting.GetLeftAmount() == 0 &&	(m_reelsArea.m_ActionMgr.m_bThereIsUndoneScatter )){
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
				else if( m_reelsArea.m_ActionMgr.m_bBonus1_Exist )
				{
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
            if(m_reelsArea.CoinAnimCanStart()){
                    m_reelsArea.m_ActionMgr.m_CoinAnim.SetCurrency(gMoneyCounting.GetLeftAmount());
            }

            if( m_reelsArea.GetScatterStarted() ){
                m_ucState = MG_STATE_SCATTERGAME;
            }
			else if( gMoneyCounting.GetLeftAmount() == 0 ){
				m_reelsArea.m_ActionMgr.m_CoinAnim.SetCurrency(gMoneyCounting.GetLeftAmount());

				if( SwitchInJPState() ){
					return;
				}

				// check for user auto mode /////////////////
				if( (m_bUserAutoMode || m_bTestAutoMode) && !m_bJpWon && !m_reelsArea.m_ActionMgr.m_bBonus1_Exist && !m_bFG){
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

				if( m_bFG )
				{
					if ( !m_reelsArea.m_ActionMgr.m_bScatter_Exist ){
						SwitchInFGBetting();
					}
				}
				else{
					// change state (Betting or BettingPlus) /////////////////
					if( IsDoubleUpOK() ){

						// request to BettingPlus
						m_ucState = MG_STATE_BETTING_PLUS;
						gGameStateMgr.RequestState( egsdMGBettingPlus );
					}
					else{

						if( m_reelsArea.m_ActionMgr.m_bBonus1_Exist )
						{
							m_ucState = MG_STATE_BONUSGAME;
							gGameStateMgr.RequestState(egsdBonus_1);
                            if ( m_bUserAutoMode )
                            {
                                m_bUserAutoMode = false;
                                m_bAutoInSound = false;
                                m_bUserAutoModeON = false;
                            }
                            gKeyboardScenarioController->RequestFunctionUpdate();
						}
						else
						{
							// back to Betting
							m_ucState = MG_STATE_BETTING;
							gGameStateMgr.BackToPreviousState();
							gGPMgr.SetGameMode();
						}
					}
					//////////////////////////////////////////////////////////
				}
				SetBettingButtons();
			}
			if( !m_reelsArea.m_ActionMgr.m_bThereIsUndoneScatter &&
					!m_reelsArea.m_ActionMgr.m_bThereIsUndoneBonus1 ){

					if( SwitchInJPState() ){
						return;
					}
			}
			break;

		case MG_STATE_WINSPLASH:
			if( m_nFGCount > 0 && gGameStateMgr.GetCurrentState() == egsdMGBonusWin )
			{
				m_reelsArea.BonusFinished();

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
        // WinSplash finished
		if( !m_WinSplash.IsShown() ){
			RGBManager::eAction eActionRGB = RGBManager::eDefault;
            GameToHatData( GAME_TO_HAT_RGB_ACTION, (const void*)&eActionRGB, sizeof(eActionRGB) );

			gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH );
			SetBettingButtons();
			m_nWinSplashCount = 0;

			if( m_WinSplash.GetState() == eOutro ){
                m_WinSplash.ResetState();

				if (RAAM_ACTIONTYPE_NO_ACTION == m_reelsArea.m_ActionMgr.m_ucActionType) {
					m_reelsArea.m_ActionMgr.m_AnimMgr.Start(false);
				}

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
			else if ( m_WinSplash.GetState() == eIntro || m_WinSplash.GetState() == eRetrigger ){
                m_WinSplash.ResetState();

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

        gVBMgr.StopTimer( this, MG_TIMER_FG_COUNTING );
		if( gGameStateMgr.GetCurrentState() != egsdFGBetting ){
			return;
		}

		SetBettingButtons();

		if ( m_WinSplash.GetState() == eRetrigger )
			StartAutoFG( true, false );
		else
			StartAutoFG( false, true );
	}

	else if( nID == MG_TIMER_START_FS_OUTRO ){

		gVBMgr.StopTimer( this, MG_TIMER_START_FS_OUTRO );

		m_reelsArea.BonusFinished();

		m_bThereNeedBonusAfterScatter = false;

		Currency crBonusWin = gGPMgr.Win_Get();
		m_crFGWin = crBonusWin;

		if ( m_crFGWin == 0 )
		{
			m_bWinGame = false;
		}
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
			m_WinSplash.StartTotal(m_crFGWin);
			if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() )
			{
				gP3Info.ShowDefaultScreen(true, true);
			}
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
	else if (nID == MG_TIMER_BACK_FROM_BONUS_GAME)
	{
		if ( gVBMgr.StopTimer( this, MG_TIMER_BACK_FROM_BONUS_GAME ) ){

#ifdef EGT_CREDIT_OBSERVER //define when EGT_DEBUG=1
            if (debCreditObserver::getInstance().isAcive())
            {
                debCreditObserver::getInstance().setCurrentWon( gGPMgr.MultiwayBet_Get() );
            }
#endif

            m_ucState = m_bFG ? MG_STATE_WINDEMO : MG_STATE_BETTING;

            if(!m_reelsArea.m_ActionMgr.ThereIsUndoneFeature())
            {
                // enable drawing bonus status
                m_reelsArea.m_ActionMgr.m_bBonusStatusEnable = true;

                m_reelsArea.m_ActionMgr.StartAction(false);
                m_reelsArea.BonusFinished();
                m_reelsArea.m_ActionMgr.m_bBonus1_Exist = false;
                // change state (Betting or BettingPlus) /////////////////
                if(	IsDoubleUpOK() && !m_bFG)
                {
                    m_ucState = MG_STATE_BETTING_PLUS;
                    gGameStateMgr.RequestState( egsdMGBettingPlus );
                }
                else{
                    if(	!IsDoubleUpOK() ) {
                        gGPMgr.SetDemoMode();
                        gGPMgr.Credit_AddWin( gGPMgr.Win_Get());
                    }

                    if ( gGameStateMgr.GetPreviousState() == egsdFGReeling ){
                        gGameStateMgr.RequestState( egsdFGBonusWin );
                    }
                    else
                    {
                        gGameStateMgr.BackToPreviousState();
                    }
                }
                // service auto mode after bonus game
                if (gGPMgr.GameSettings_Get().ui16AutoGames)
                {
                	m_bTestAutoMode = true;
                    gKeyboardScenarioController->RequestFunctionUpdate();
					StartTakeWinCounting();
                }
                // user auto mode
                if( IsUserAutoModeON() && !m_bFG ){
                    m_bUserAutoMode = true;
                    gKeyboardScenarioController->RequestFunctionUpdate();
					StartTakeWinCounting();
                }
            }
        }
	}
}

void MainGame::SwitchInFGBetting()
{
    if( m_reelsArea.m_ActionMgr.m_bBonus1_Exist ){

       m_ucState = MG_STATE_BONUSGAME;
       gGameStateMgr.RequestState(egsdBonus_1);
       gKeyboardScenarioController->RequestFunctionUpdate();

       return;
   }

	if( (gGameStateMgr.GetCurrentState() == egsdMGBonusWin || gGameStateMgr.GetCurrentState() == egsdFGBonusWin ) && m_nFGCount > 0 )
	{
		m_ucState = MG_STATE_BETTING;
		if ( gGameStateMgr.GetCurrentState() == egsdMGBonusWin ){
			gGameStateMgr.RequestState( egsdFGBetting );
        }
		else if ( gGameStateMgr.GetCurrentState() == egsdFGBonusWin ){
			gGameStateMgr.BackToPreviousState();
        }

		return;
	}

    if(m_AnalyzerResults.IsMoneyOverCapLimit(gGPMgr.Win_Get()))
    {
        m_nFGCount = 0;
    }

	if( m_nFGCount == 0 )
	{

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
            int nMultiwayBet = gGPMgr.MultiwayBet_Get();
            Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
            Currency crTotalBet = crBetPerLine * nMultiwayBet;
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
			int nLinesCount = GAME_LINES_COUNT;
				Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
				for( i = 0; i < GAME_LINES_COUNT; i++ ){
					if( i < nLinesCount ){
						crBets[i] = crBetPerLine;
					}
					else{
						crBets[i] = 0;
					}
				}

				analyzer.Init( nConfTmp, crBets,
							   gGPMgr.ActiveReels_Get(),
							   gGPMgr.MultiwayBet_Get(),
							   !HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
							   !HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || !HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
							   gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
							   gGPMgr.BetPerLine_Get(), m_bFG/*nCurrMult*/,  (EFigure) m_cSpecialSymbol );

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
				int nMultiwayBet = gGPMgr.MultiwayBet_Get();
					Currency crBetPerLine = gGPMgr.GameSettings_Get().cPointValue * gGPMgr.BetPerLine_Get();
				Currency crTotalBet = crBetPerLine * nMultiwayBet;


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
            if ( !m_reelsArea.m_dFlyCoinAnim.IsVisible() ){
                // it's a stop
                m_bFGFastStoped = true;
            }
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

    if ( true == m_StartFGSplash.IsShown() )
	{
		if ( true == m_StartFGSplash.IsInSplashArea( usX, usY ) )
		{

            m_bIsAutoModeOff = false; //BUG:23548

 			m_StartFGSplash.Hide();
            if( !m_bFG ){
				gRecordMgr.RecordData();
			}

            SetDisabledButtons();
            m_WinSplash.StartIntro();
            PluginFunctions().DispatchSignal(signal_names::OnFGStart);
            gVBMgr.StopTimer( this, MG_TIMER_WINSPLASH);
            gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );

			gGPMgr.SetDemoMode();

			SetDisabledButtons();

			return;
		}

	}

    if ((usX > MG_START_FG_RETRIG_SPLASH_X)&&(usX < MG_START_FG_RETRIG_SPLASH_X + MG_START_FG_RETRIG_SPLASH_W)
		&&(usY > MG_START_FG_RETRIG_SPLASH_Y) && (usY < MG_START_FG_RETRIG_SPLASH_Y + MG_START_FG_RETRIG_SPLASH_H))
	{
		if (  m_WinSplash.IsRetrigShown() ){
			m_WinSplash.Interrupt();
			return;
		}
	}

	if( m_ucState == MG_STATE_REELING ){
		m_reelsArea.StopReel( (int)usX, (int)usY );

	}
	else if( (egsdMGBetting == gGameStateMgr.GetCurrentState() ||
			  egsdMGBettingPlus == gGameStateMgr.GetCurrentState() ||
			  egsdFGBetting == gGameStateMgr.GetCurrentState() ) &&
			  m_ucState != MG_STATE_BIGWINDEMO && m_ucState != MG_STATE_CREDIT_COUNTING && m_ucState != MG_STATE_BETTING_PLUS) {

		if(( m_BigWinDemo.Touch( usX, usY, true ) == BWD_CHOICE_SWITCH_TO_BWD )&&( m_BigWinDemo.IsEnabled() )) {
			FromBettingPlusToBetting();
			m_ucState = MG_STATE_BIGWINDEMO;
			gGPMgr.SetBigWinDemoFlag( true );
			m_reelsArea.m_ActionMgr.StopAction();
			SetDisabledButtons();
			gKeyboardScenarioController->RequestFunctionUpdate();
		}

	}
	else if( m_ucState == MG_STATE_BIGWINDEMO ){

		m_ucState = MG_STATE_BETTING;
		unsigned char ucBWDState =  m_BigWinDemo.Touch( usX, usY );
		if( (ucBWDState <1) || (ucBWDState > BWD_ROWS * BWD_PAGES) ){
			m_ucState = MG_STATE_BIGWINDEMO;
		}
		else{
			m_ucBWDCombination = BWD_BASE + ucBWDState;
			DoStartButton();

		}
	}

}

void MainGame::GetRealResult( int nReel, unsigned char* ucResult )
{
    auto gameVariantsPtr = GameVariantsComponent::SafeGet(gGameRestrictionMgr);
    auto gameType = GameVariantsComponent::GameType::MainGame;

    if( m_bFG )
    {
        gameType = GameVariantsComponent::GameType::FreeGame;
    }

    // investigate reel lenght ///////////////////
    unsigned int nReelLen = gameVariantsPtr->GetReelSize(gameType, m_ucVariant, nReel);
    unsigned int unMiddleIndex = 0;

#ifdef USE_EGT_DEMO
    if (Demo::IsActive())
    {
           unMiddleIndex = Demo::GetRealResult(nReel);
#ifdef EGT_DEBUG
    Assert(unMiddleIndex < nReelLen);
#endif

    if (nReel == REELS_COUNT - 1)
        Demo::SetActive(false);
    }
    else
        GenerateSequence(0, 1, &unMiddleIndex, nReelLen);
#else
    GenerateSequence(0, 1, &unMiddleIndex, nReelLen);
#endif

    // preparing dump value ////////////////////////////////////
    m_ucDumpReelIndexes_1[nReel] = m_ucDumpReelIndexes_2[nReel];
    m_ucDumpReelIndexes_2[nReel] = (unsigned char)unMiddleIndex;
    ////////////////////////////////////////////////////////////

    GetSlidingWindow(gameType, m_ucVariant, nReel, unMiddleIndex, ucResult);
}

void MainGame::GetRealResult( int nReel, unsigned char* ucResult, unsigned char ucInitialIndex, bool bThereIsDoubt )
{
    unsigned char ucVariant = m_ucVariantLatestResults;

	if ( std::numeric_limits<unsigned char>::max() == ucVariant )
	{
		unsigned char firstDenomOffset = 0;

		while(! gDenominationControl.IsActive(firstDenomOffset) )
				firstDenomOffset++;
		const char*  nvramId = GetHybridParameterId(eNvramGameVariant, firstDenomOffset);
		if( !GetParameter(nvramId, (void*)&ucVariant, sizeof( ucVariant ) ) ){
			eCDebug( LOG_CATEGORY_GAMES ) << "Get NVRAM_GCP_GAME_VARIANT failed!\n";
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
		if( m_bFG && !((m_nFGOriginalCount == m_nFGCount) && (m_nFGOriginalCount == m_nFGTotalCount)) ){
			bMustBeFG = true;
		}
		else{
			bMustBeFG = false;
		}
	}

    auto gameType = GameVariantsComponent::GameType::MainGame;
    if( bMustBeFG )
    {
        gameType = GameVariantsComponent::GameType::FreeGame;
        eCDebug(LOG_CATEGORY_GAMES) << "going fg with indexes";
    }
    else
    {
        eCDebug(LOG_CATEGORY_GAMES) << "going non-fg with indexes";
    }

    GetSlidingWindow(gameType, ucVariant, nReel, ucInitialIndex, ucResult);
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
	sDump->chExtraWild = (char)m_cSpecialSymbol;
	sDump->ucVariantLatestResults = m_ucVariantLatestResults;

    sDump->unPotStateValue = m_unPotStateValue;
    sDump->unCurrPotStateValue = m_unCurrPotStateValue;

#if WSPLASHTYPE == WST_COVER_FULL
	if (!m_bFG)
#else
	if (m_bFG)
#endif // WSPLASHTYPE == WST_COVER_FULL
	{
		// fg mother figures ////////////////
		for(int i = 0; i < REELS_COUNT; i++ ){
			for(int j = 0; j < ALL_FIGURES_PER_REEL; j++ )
			{
				sDump->chResultsToShowAfterFG[i][j] = (unsigned char)m_efResultsToShowAfterFG[i][j];
			}
		}
	}

	// save last FG - need it for initial results in next triggered FG
	if(m_nFGCount == 0 && m_bFG)
	{
		for( int i=0; i<REELS_COUNT; i++)
		{
			for( int j=0; j<ALL_FIGURES_PER_REEL; j++)
			{
				sDump->chResultsToShowInFG[i][j] = (unsigned char)m_efResultsToShowInFG[i][j];
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

	eCDebug( LOG_CATEGORY_GAMES ) << "DUMP: pDump->ucMainGameState = " << (int)sDump->ucMainGameState;

 /** Record this point for recover after Progressive and Hand Splash*/
    if(gRecordMgr.GetCurrTrIdentificator() == eGTrIdProgressiveFinish )
	{
        sDump->b_ProgressiveSplashGap = true;
    }
	////////////////////////////

	// if it's matter of free games //////////////////
	if( ( m_bFG && bGlobalNotification &&(gGameStateMgr.GetCurrentState() == egsdFGReeling ||
					      (gGameStateMgr.GetCurrentState() == egsdFGBetting &&
	 ( (m_nFGOriginalCount == m_nFGCount) && (m_nFGOriginalCount == m_nFGTotalCount) ) )
			))) {

		//skip the rest of this function if this is a transition to/from a jp state
		if( (gRecordMgr.GetCurrTrIdentificator() == eGTrIdProgressiveStart) || (gRecordMgr.GetCurrTrIdentificator() == eGTrIdProgressiveFinish) ) {
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

        //retrigger logic
        int nScatterCount = 0;
        for(int i = 0; i < REELS_COUNT; i++ ){
            if( m_AnalyzerResults.nScattersPos[i] != (-1) ){
                nScatterCount++;
            }
        }
        if(nScatterCount >= 3)
        {
            auto bonusData = turn->mutable_bonus();
            auto freeGames = bonusData->mutable_freegames();
            freeGames->set_value(m_nFGOriginalCount);
        }

		if( gGameStateMgr.GetCurrentState() == egsdFGReeling ) {
            GetGameHistory()->addToLastEntry(std::move(entry));
		}


		// reel indexes /////////////////////////////////
		for( int i = 0; i < REELS_COUNT; i++ ){
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

        if( gGameStateMgr.GetCurrentState() == egsdFGReeling ){
            sDump->b_ProgressiveSplashGap = false;
        }
		return;
	}
	else if( m_bNeedToRecordBonusWin )
	{

			// total fg win id
			unsigned char uchLimitExceeded = 0;
			if(sDump->uchLimitExceeded){
				uchLimitExceeded = 1;
			}

			int game_id = HatApplication::GetInstance().m_GameMgr->GetGameID(true);
			uint64_t u64Win = 0;
			HatApplication::GetInstance().m_StorageMgr->GetParameter("NVRAM_JPM_FGRH_SPLASH_PAID", &u64Win, sizeof(u64Win), game_id);

			Currency crProgressive = 0;
			crProgressive.m_n64Data = u64Win;

			m_crPureFGWin = m_crFGWin - m_crFGMotherWin;
			m_crPureFGWin -= crProgressive;
			sDump->crPureFGWin = m_crPureFGWin;

            /** Record Special symbol hit statistics for bonus page */
			unsigned char uchDenomIndex = gGPMgr.GameSettings_Get().uchBaseDenomOffset;

	        history::Entry entry;
        	auto freegames = entry.mutable_freegames();
    	    freegames->mutable_limitexceeded()->set_value(uchLimitExceeded);
	        GetGameHistory()->addToLastEntry(std::move(entry));

			/** Total win value from free games */
			GameStatUnit_t gstatBonus(m_crPureFGWin, 1);
			updateGameStatUnits(trID,"NVRAM_GCP_BONUS_FREE_SPINS",uchDenomIndex,gstatBonus);

			/** Total free spins from free games */
			GameStatUnit_t gstatTotalFS(0,  m_nFGTotalCount);
			updateGameStatUnits(trID,"NVRAM_GCP_TOTAL_FREE_SPINS",uchDenomIndex,gstatTotalFS);

			sDump->bFGMode = m_bFG;
			sDump->usFGOriginalCount = (unsigned short)m_nFGOriginalCount;
			sDump->usFGCount = (unsigned short)m_nFGCount;
			sDump->usFGTotalCount = (unsigned short)m_nFGTotalCount;
			//initial project
			sDump->chFGMult = m_nFGMult;  // 1/* BUG 10396 (char)m_nFGMult*/;
			sDump->crFGWin = m_crFGWin;

			m_bNeedToRecordBonusWin = false;
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

	////////////////////////////////////////////////////////////////////////////////
	// follow the last 50 games and hit statistics recordings //////////////////////
	////////////////////////////////////////////////////////////////////////////////

	if( gGameStateMgr.GetCurrentState() != egsdMGReeling ){
		return;
	}

	sDump->b_ProgressiveSplashGap = false;

	// set game variant to be shown in the event log
    NewGameStartData startData;
    startData.trId = trID;
	auto gameVariantsPtr = GameVariantsComponent::SafeGet( gGameRestrictionMgr );
	size_t allRtpMainGame =  gameVariantsPtr->GetAllVariantsCount(GameVariantsComponent::GameType::MainGame);

    history::Entry entry;
	if ( m_ucVariant < allRtpMainGame )
	{
		unsigned short game_variant = gameVariantsPtr->GetFixedPointRtp(GameVariantsComponent::GameType::MainGame ,m_ucVariant);
        startData.gameVariant = game_variant;
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
		(gGPMgr.BetPerLine_Get() ==  gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine))
	{
        auto& jackpotData = *mainGameInfo.add_jackpot();
        jackpotData.mutable_hasjpconditions()->set_value(true);
	}

    auto entryInfo = entry.mutable_entryinfo();
    auto waysInfo = entryInfo->mutable_waysinfo();
    
    // ways per line
    waysInfo->mutable_multiplier()->set_value(gGPMgr.BetPerLine_Get());

    // multiway bet
    waysInfo->mutable_waysbet()->set_value(gGPMgr.MultiwayBet_Get());    

    // figures
    auto visibleReels = mainGameInfo.mutable_visiblereels();
    for( int j = 0; j < REELS_COUNT; j++ ) {
        auto newReel = visibleReels->add_reels();
        for( int i = 0; i < VISIBLE_FIGURES_PER_REEL; i++ ) {
            auto figure = newReel->add_figures();
            figure->add_id(m_ucLogFigResults[i][j]);
        }
    }

	// denomination
    auto invoice = entryInfo->mutable_invoice();
    invoice->mutable_pricepercredit()->set_value(gGPMgr.GameSettings_Get().cPointValue.ToCents());
    GameToHatData( GAME_TO_HAT_START_NEW_GAME_MARK, (const void*)&startData, MAIN_GAME_TRDATAID_LEN);
	RecordRegularHits( trID );
    GetGameHistory()->addToLastEntry(std::move(entry));
}

void MainGame::Recover(SDump *pDump)
{
	m_ucState = pDump->ucMainGameState;
	m_bLastGameIsFree = pDump->bLastGameIsFree;
	// Win JP flag
	m_bJpWon = pDump->bJPWin;

    m_unPotStateValue = pDump->unPotStateValue;
    m_unCurrPotStateValue = pDump->unCurrPotStateValue;
    m_reelsArea.m_dFlyCoinAnim.Send(true);

	eCDebug( LOG_CATEGORY_GAMES ) << "Recover: pDump->ucMainGameState = " << (int)pDump->ucMainGameState;


	eCDebug( LOG_CATEGORY_GAMES ) << "Recover positions 1:   "
									<< (int)pDump->ucReelsPositions_1[0] << "\t"
									<< (int)pDump->ucReelsPositions_1[1] << "\t"
									<< (int)pDump->ucReelsPositions_1[2] << "\t"
									<< (int)pDump->ucReelsPositions_1[3] << "\t"
									<< (int)pDump->ucReelsPositions_1[4];
	eCDebug( LOG_CATEGORY_GAMES ) << "Recover positions 2:   "
									<< (int)pDump->ucReelsPositions_2[0] << "\t"
									<< (int)pDump->ucReelsPositions_2[1] << "\t"
									<< (int)pDump->ucReelsPositions_2[2] << "\t"
									<< (int)pDump->ucReelsPositions_2[3] << "\t"
									<< (int)pDump->ucReelsPositions_2[4] << "\n";

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
	m_cSpecialSymbol = pDump->chExtraWild;

	// fg mother figures ////////////////
	for( i = 0; i < REELS_COUNT; i++ )
	{
		for( j = 0; j < ALL_FIGURES_PER_REEL; j++ )
		{
			m_efResultsToShowAfterFG[i][j] = (EFigure)pDump->chResultsToShowAfterFG[i][j];
			m_efResultsToShowInFG[i][j] = (EFigure)pDump->chResultsToShowInFG[i][j];
		}
	}

	m_FGSeals.AddFG( m_nFGCount );
	m_FGSeals.SetMult( m_nFGMult );

	EFigure efAnalResults[REELS_COUNT][ALL_FIGURES_PER_REEL];

	for( i = 0; i < REELS_COUNT; i++ ){
		unsigned char ucResults[ALL_FIGURES_PER_REEL];
		if( ( m_ucState == MG_STATE_REELING || m_ucState == MG_STATE_WINDEMO ) &&
				(gGameStateMgr.GetCurrentState() != egsdJPMProgressive) ){

            // lock recover starting animation until reeling reels
            gBonusGame.RecoverLock();

			if(m_bFG){
				GetRealResult( i, ucResults, pDump->ucReelsPositions_1[i], true );
			}
			else{
				GetRealResult( i, ucResults, pDump->ucReelsPositions_1[i], false );
			}
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
	Currency crBets[GAME_LINES_COUNT];
	int nLinesCount = GAME_LINES_COUNT;
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
    if(m_bFG)
    {
        nCurrMult = m_nFGMult;
        gStatusLine.SetFreeSpinsFeature( nCurrMult );
    }

	analyzer.Init( 	nConfTmp, crBets,
					gGPMgr.ActiveReels_Get(),
					gGPMgr.MultiwayBet_Get(),
					HatApplication::GetInstance().m_JPMMgr->IsLocalProgressiveEnabled(),
					HatApplication::GetInstance().m_JPMMgr->IsNonSASProgressiveEnabled() || HatApplication::GetInstance().m_JPMMgr->IsSASProgressiveEnabled(),
					gGPMgr.GameSettings_Get().sBetsPerLine.nMaxBetPerLine,
					gGPMgr.BetPerLine_Get(), m_bFG/*nCurrMult*/,  (EFigure) m_cSpecialSymbol );

	analyzer.GetResults( &m_AnalyzerResults );

	// in case of hat's jp state ///////////////////
	if(gGameStateMgr.GetCurrentState() == egsdJPMProgressive) {

		if ( ((m_ucState != MG_STATE_BETTING_PLUS)&&(m_ucState != MG_STATE_BETTING) ) ||
		   (m_AnalyzerResults.GetWinFiguresCount() == 1 && m_AnalyzerResults.GetFiguresDataAt(0).currWin == 0 ) || m_bFG )
		{
				m_reelsArea.SetResults( efAnalResults, m_AnalyzerResults, true );
				m_reelsArea.BonusFinished();
				m_reelsArea.m_ActionMgr.StartAction();
				SetDisabledButtons();

		   }
	}
	if( m_ucState == MG_STATE_WINDEMO ||
			m_ucState == MG_STATE_SCATTERGAME ||
			m_ucState == MG_STATE_BONUSGAME ||
			m_ucState == MG_STATE_WINSPLASH )
		m_reelsArea.m_ucRAStatus = RA_STATUS_STOPPED_BUSY;

	m_reelsArea.m_ActionMgr.SetActiveReels( pDump->uchActiveReels, false );

	if( gGameStateMgr.GetCurrentState() == egsdMGBettingPlus ||
			gGameStateMgr.GetCurrentState() == egsdInfo ||
			gGameStateMgr.GetCurrentState() == egsdGamble )
		m_bWinGame = true;

	if( (m_bFG) && (gGameStateMgr.GetCurrentState() == egsdMGBonusWin) )
	{
		if( gGPMgr.GameSettings_Get().ui16AutoGames )
			m_bTestAutoMode = true;
		m_ucState = MG_STATE_WINSPLASH;
		gVBMgr.StopTimer(this, MG_TIMER_WINSPLASH);
		gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
		m_WinSplash.StartTotal(m_crFGWin);
		m_bLastGameIsFree = true;
		return;
	}

	if((m_nFGCount == 0) && (gGameStateMgr.GetCurrentState() == egsdFGBetting) )
	{
		bool bProgressiveFocus = false;
		GameToHatData( GAME_TO_HAT_JP_PROGRESSIVE_FOCUS, (const void*)&bProgressiveFocus, sizeof(bProgressiveFocus) );
		SwitchInFGBetting();

	}
	if( (m_nFGCount == 0) && (gGameStateMgr.GetCurrentState() == egsdFGNormalWin) )
	{
		// this flag is set in FS_OUTRO timer
		m_bLastGameIsFree = true;
		SwitchInFGBetting();
		return;
	}
	if( !m_bFG && gGameStateMgr.GetCurrentState() == egsdMGBonusWin &&
			(m_ucState == MG_STATE_WINSPLASH || m_ucState == MG_STATE_SCATTERGAME) )
	{
		m_WinSplash.StartIntro();
		m_ucState = MG_STATE_WINSPLASH;
		gVBMgr.StartTimer( this, MG_TIMER_WINSPLASH, MG_PERIOD_WINSPLASH );
		gGPMgr.SetDemoMode();
	}

	if(m_nFGCount > 0 )
	{
		if( gGameStateMgr.GetCurrentState() == egsdFGBetting )
		{
			//??auto start
			gVBMgr.StopTimer( this, MG_TIMER_FG_AUTOSTART );
			StartAutoFG();
			SetBettingButtons();
		}
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
		m_reelsArea.BonusFinished();//put to stop readyforbonus1 after recover
		if (bStartWinDemo)
		{
			m_reelsArea.m_ActionMgr.StartAction( false );
		}
	}

	if (( gGameStateMgr.GetCurrentState() == egsdMGScatterGame ) )
	{
		m_reelsArea.SetResults( efAnalResults, m_AnalyzerResults, true );
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
{
//	const int cnScatterDataLen = 6;
//	unsigned char ucScatterData[cnScatterDataLen+MG_TRDATAID_LEN];
//	unsigned char ucCurrPos = 0;
//
//	// first 4 bytes for the transaction id
//	ucCurrPos = AddVratkaData_un( ucScatterData, ucCurrPos, trID );
//
//	// scatter id
//	if( m_bFG ){
//		ucCurrPos = AddVratkaData_uc( ucScatterData, ucCurrPos, GREAT_CHINA_PREMIER_SCATTER_ID_FG );
//	}
//	else{
//		ucCurrPos = AddVratkaData_uc( ucScatterData, ucCurrPos, GREAT_CHINA_PREMIER_SCATTER_ID );
//	}
//
//	// multipliers
//
//	for(int i = 0;  i < REELS_COUNT; i++ ){
//		ucCurrPos = AddVratkaData_uc( ucScatterData, ucCurrPos, pucMultipliers[i] );
//	}
//
//	// choice
//	ucCurrPos = AddVratkaData_uc( ucScatterData, ucCurrPos, ucChoice );
//
//
//	GameToHatData( GAME_TO_HAT_ADD_DATA_TO_LAST_GAME, (const void*)ucScatterData, cnScatterDataLen );
//
//
// 	if( m_bFG ){
// 		return; // without hits
// 	}
//
//	//////////////////////////////////////////////////////////////////////////////////////////
//	// set scatter hits //////////////////////////////////////////////////////////////////////
// 	unsigned char ucScatterCount = 0;
// 	for( int i = 0; i < 5; i++ ){
// 		if( pucMultipliers[i] > 0 ){
// 			ucScatterCount++;
// 		}
// 	}
/*
	unsigned char uchDenomIndex = gGPMgr.GameSettings_Get().uchBaseDenomOffset;
	// counts //////////////////////////

	unsigned int unCountsID = unNVRAMHitsIDs[GetHitIDIndex( ef13_scatter, ucScatterCount )];
	unsigned int unLastCountsValue = 0;
	GetArrayParameter( unCountsID, (void*)&unLastCountsValue, uchDenomIndex, sizeof( unLastCountsValue ) );
	unsigned int unNewCountsValue = unLastCountsValue + 1;
	AddTransactionArrayData( trID, unCountsID, (const void*)&unNewCountsValue, uchDenomIndex, sizeof( unNewCountsValue ), 1 );

	////////////////////////////////////

	// wins //////////////////////////////////
	unsigned int unWinsID = unNVRAMHitWinsIDs[GetHitIDIndex( ef13_scatter, ucScatterCount )];
	Currency crLastWinsValue = 0;
	GetArrayParameter( unWinsID, (void*)&crLastWinsValue, uchDenomIndex, sizeof( crLastWinsValue ) );
	Currency crTotalBet = gGPMgr.GameSettings_Get().cPointValue;
	crTotalBet *= gGPMgr.TotalBet_Get();
	crTotalBet *= m_nFGMult;//SCATTER_POSSIBLE_MULTIPLIERS[pucMultipliers[ucChoice]];
	Currency crNewWinsValue = crLastWinsValue + crTotalBet;
	AddTransactionArrayData( trID, unWinsID, (const void*)&crNewWinsValue, uchDenomIndex, sizeof( crNewWinsValue ), 1 );
	//////////////////////////////////////////

*/
}

void MainGame::RecordRegularHits( TransactionId trID )
{
	int i = 0;
	unsigned char uchDenomIndex = gGPMgr.GameSettings_Get().uchBaseDenomOffset;
	for( ; i < m_AnalyzerResults.GetWinFiguresCount(); i++ ){

		/* winFiguresData[i].nMultiply ->  1 multiplier = 1 hit  - record each one hit separately */
		for ( int j = 0; j < m_AnalyzerResults.GetFiguresDataAt(i).nMultiply; j++)
		{
			// Gameplay: game stat units update -> wins, hits //////////////////////////
            const char* unCountsID = unNVRAMHitsIDs[GetHitIDIndex( (EFigure)m_AnalyzerResults.GetFiguresDataAt(i).eFigure,
            m_AnalyzerResults.GetFiguresDataAt(i).nCount )];

			int nMultiplier = m_AnalyzerResults.GetFiguresDataAt(i).nMultiply;

            GameStatUnit_t gstat(m_AnalyzerResults.GetFiguresDataAt(i).currWin / nMultiplier, 1);
			updateGameStatUnits(trID, unCountsID, uchDenomIndex, gstat );
			//////////////////////////////////////////
		}
	}

	// scatters //////////////////////////////////////////////////////
	int nScatterCount = 0;
	for( i = 0; i < 5; i++ ){
		if( m_AnalyzerResults.nScattersPos[i] != (-1) ){
			nScatterCount++;
		}
	}
	if( nScatterCount > 2 ){
		// Gameplay: game stat units update -> wins, hits scatter //////////////////////////
		const char* unCountsID = unNVRAMHitsIDs[GetHitIDIndex( ef12_scatter, nScatterCount )];

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
		eCDebug( LOG_CATEGORY_GAMES ) << "Get NVRAM_LRP_GAME_VARIANT failed!\n";
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
	if(gGPMgr.GetHatCurrState() == esdGameSelect)
	{
		m_reelsArea.StopFlyCoinAnim();
	}

    if(gGPMgr.GetHatPrevState() == esdGameSelect)
    {
        m_reelsArea.m_dFlyCoinAnim.Send(true);
    }

  	if(gGPMgr.GetHatCurrState() == esdJPUniversalInternal) {
		gVBMgr.StopTimer(this, MG_TIMER_PROGRESSIVE_RECOVER);
	}

	if (gGPMgr.GetHatCurrState() == esdBusyGame ) {

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

    if( (gGPMgr.GetHatCurrState() == esdReadyGame || gGPMgr.GetHatCurrState() == esdBonus) &&
            gGPMgr.GetHatPrevState() == esdBackToNoJP ){
		gVBMgr.StartTimer(this, MG_TIMER_BACK_FROM_BONUS_GAME, MG_PERIOD_BACK_FROM_BONUS_GAME );
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

		if (m_reelsArea.m_ActionMgr.m_CoinAnim.IsStarted()){
			m_reelsArea.m_ActionMgr.m_CoinAnim.Pause();
		}

        /*
		if(gGameStateMgr.GetCurrentState() == egsdBonus_1){

			gBonusGame.BonusSoundControl(eStop);
		}
        */

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

    /*
	if ( (gGPMgr.GetHatPrevState() == esdNonFatalError || gGPMgr.GetHatPrevState() == esdWarning) && gGameStateMgr.GetCurrentState() == egsdBonus_1 )
	{
		gBonusGame.BonusSoundControl(eStart);
	}
    */

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

    /** Send StateChange event for Vaapi Animation pause and resume */
    m_reelsArea.m_ActionMgr.m_CoinAnim.HatStateChange() ;
	return 0;
}

void MainGame::SetFG( int nFGCount, int nFGMult )
{
	if( nFGCount > 0 )
	{
		m_bFG = true;
        gStatusLine.SetFreeSpinsFeature( nFGMult );
		SetBettingButtons();
		m_crFGMotherWin = (m_crFGMotherWin != 0)? m_crFGMotherWin : gGPMgr.Win_Get();
		m_reelsArea.m_ActionMgr.StopAction();
        PluginFunctions().DispatchSignal(signal_names::OnFGStart);
	}
	else {
		m_bFG = false;
		m_nFGCount = 0;
		m_nFGTotalCount = 0;
        gStatusLine.DisableFreeGame();
		m_reelsArea.SetOnlyFiguresResults(m_efResultsToShowAfterFG);
		m_reelsArea.m_ActionMgr.m_bThereIsUndoneBonus1 = false;
		m_reelsArea.m_ActionMgr.m_bThereIsUndoneScatter = false;
        m_reelsArea.m_ActionMgr.StartAction( false );

        if(	!IsDoubleUpOK() ){
            gGPMgr.SetDemoMode();
            gGPMgr.Credit_AddWin(gGPMgr.Win_Get());
        }

		m_cSpecialSymbol = FIGURES_NUM;
        PluginFunctions().DispatchSignal(signal_names::OnFGExit);
        gKeyboardScenarioController->RequestFunctionUpdate();
	}
	m_nFGOriginalCount = nFGCount;
	m_nFGMult = nFGMult;
}

void MainGame::SetPotStateValue( EFigure eFigRes[REELS_COUNT][ALL_FIGURES_PER_REEL] )
{

    m_unCurrPotStateValue = 0;

    	for (int j = 1; j < ALL_FIGURES_PER_REEL-1 ; ++j)
    	{
    		for (int i = 0; i < REELS_COUNT ; ++i)
    		{

    			if ( eFigRes[i][j] == ef11_wild)
    			{
       				m_unCurrPotStateValue = PotValuePerBet[gGPMgr.GetCurrentMultiplierIndex()];
    				j = ALL_FIGURES_PER_REEL;
    				i = REELS_COUNT;
    			}
    		}
    	}

    m_unPotStateValue += m_unCurrPotStateValue;
}

int MainGame::GetPotCurrentFrame()
{
    for( auto i = 0; i < VISIBLE_FIGURES_PER_REEL; ++i )
    {
       if( m_unPotStateValue < PotFrameTarget[i] )
       {
           return  i ;
       }
    }

   return VISIBLE_FIGURES_PER_REEL;
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
// 		OnTick(MG_TIMER_CREDIT_COUNTING,1);
		gVBMgr.StartTimer( this, MG_TIMER_CREDIT_COUNTING, 1);
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

	if(m_reelsArea.m_ActionMgr.m_bBonus1_Exist)
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

void MainGame::ReportHit( Currency BonusWin )
{
    m_cBonusWin = BonusWin;
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

void MainGame::SetLine( int nLinesToSet )
{
	m_reelsArea.m_ActionMgr.StopAction();

	gGPMgr.LinesCount_Set((int)(nLinesToSet));

	m_reelsArea.m_ActionMgr.SetActiveReels(gGPMgr.ActiveReels_Get());

	gBetLinesControlAdapter.GetSndObj().PlayOptionSound();
	SetBettingButtons();
	gRecordMgr.RecordData();
	if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() )
	{
		gP3Info.ShowDefaultScreen();
	}

	CleanDemoReelsArea();

}

bool MainGame::ProcessLinesButton( int nReelsCountCount )
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

		m_reelsArea.m_ActionMgr.StopAction();
		gGPMgr.LinesCount_Set(nReelsCountCount);
		m_reelsArea.m_ActionMgr.SetActiveReels( nReelsCountCount );

		int nLineIdx = 0;
		for (unsigned i = 0; i < GameOptionSchema::LINE_BUTTONS; ++i )
		{
		      if(nReelsCountCount == GameOptionSchema::cucMultiwayBets.at(gMainGame.GetMainGameID()).at(i).at(0))
		      {
		    	  nLineIdx = i;
		      }
		}
        gBetLinesControlAdapter.NextScreenLineSelection ( nLineIdx );

		SetBettingButtons();
		gRecordMgr.RecordData();
		if( !HatApplication::GetInstance().m_VideoControlMgr->IsMonoMode() )
		{
			gP3Info.ShowDefaultScreen();
		}
		//////////////////////////////
	}
	else if( gMoneyCounting.GetLeftAmount() != 0 ){

		m_bFGFastStoped = true;
		gMoneyCounting.SetFastMode();
		SetDisabledButtons();
	}

	CleanDemoReelsArea();

	return true;
}

bool MainGame::ProcessBetButton(int nBet, int nSoundIdx)
{
	if( m_ucState == MG_STATE_BETTING || m_ucState == MG_STATE_BETTING_PLUS ){

		FromBettingPlusToBetting();

		if( SwitchInJPState()  ) {
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

void MainGame::CleanDemoReelsArea() {
#ifdef USE_EGT_DEMO
	ReelsDemoHistory::ClearHistoryVector();
    Demo::Clean();
    Demo::Preinit();

	DemoReelsArea::SetNReels(REELS_COUNT);
	DemoReelsArea::SetAllVariantCoords(REELS_COUNT, ALL_FIGURES_PER_REEL);
	ResetDemoReelsArea();
#endif
}

void MainGame::ResetDemoReelsArea()
{
#ifdef USE_EGT_DEMO
	
    vector<SPicDef*> spicdefs_vec;
    char buff[255];
    for(unsigned char i = 0; i < FIGURES_NUM; i++){
  	  sprintf(buff, "REEL_EF_%d",(i + 1));
  	  spicdefs_vec.push_back(gGameRM.GetPicture(buff));
    }
    Demo::SetReelFigures(spicdefs_vec);

    GameVariantsComponent::GameType eGameType = GameVariantsComponent::GameType::MainGame;
    auto gameVariantsPtr = GameVariantsComponent::SafeGet(gGameRestrictionMgr);

    if ( m_bFG)
    {
        eGameType = GameVariantsComponent::GameType::FreeGame;
    }

    for (unsigned int reelIndex = 0; reelIndex < REELS_COUNT; reelIndex++)
    {

    auto vecReel = gameVariantsPtr->GetWholeReel(eGameType,
                             m_ucVariant,
                                         reelIndex);

                for (int nReelVariantFigure : vecReel)
        {
#ifdef EGT_DEBUG
        Assert(nReelVariantFigure <= static_cast<int>(spicdefs_vec.size()));
#endif
        SPicDef *pic;
        pic = spicdefs_vec[nReelVariantFigure];

        DemoReelsArea::InsertReelFigure(reelIndex, nReelVariantFigure);
        DemoReelsArea::InsertIdFigure(nReelVariantFigure, pic);
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

bool MainGame::IsButtonForFastCollect( const InputData &inputData )
{
	if(inputData.uiButtons != 0)
	{
		/* Finds the count of trealing zeros in the button mask */
		int button = __builtin_ctz(inputData.uiButtons);
		/**/
		if( button >= BTN_L1 && button <= BTN_B5 )
		{
			return true;
		}
		else if( button == BTN_STARTSTOP || button == BTN_TAKEWIN )
		{
			return true;
		}
		else if( !gGPMgr.GameSettings_Get().bGlobalDoubleUp &&
				( button == BTN_GAMBLE_SELBET || button == BTN_GAMBLE_SELLINE ) )
		{
			return true;
		}
		else if( !gGPMgr.GameSettings_Get().uchPlayerAutoMode && button == BTN_AUTO )
		{
			return true;
		}
	}

    return false;
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

void MainGame::ReturnFromBonusGame()
{
    gVBMgr.StartTimer( this , MG_TIMER_BACK_FROM_BONUS_GAME , 0 , 15 );
}

void MainGame::SetMainGameID(int gameId){
		m_nGameID = gameId;
}

int MainGame::GetMainGameID() const {
		return m_nGameID;
}

void MainGame::ResetDemoModeProperties(){

	HideAttraction();
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
    auto gameVariantsPtr =
            GameVariantsComponent::SafeGet( gGameRestrictionMgr );

    auto slidingWindow = gameVariantsPtr->CopyReelSlidingWindow( gameType, nVariant, nReel, nMiddleIndex);

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

void MainGame::SetSpecialFigDemo()
{
   SpecialDemo::Instance().Init(DemoBodyType::eGreatChinaDemoBody, "FIG_BONUS_LEVEL_");
}

bool MainGame::NeedToShowReelsInMirrorScreen()
{
        return m_ucState == MG_STATE_WINSPLASH || IsStartFGSplashShown();
}

//---------------------------------------------------------------------------------
