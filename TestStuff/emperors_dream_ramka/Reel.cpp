/* Reel.cpp

	Reel class implementation

	Author: Georgi Dragandjikov
	$Id: Reel.cpp,v 1.1.2.1.8.1.2.1 2014/09/18 13:16:43 aboikov Exp $

	Copyright (c) 2002-2007 EGT Ltd.
	All rights reserved

	More information at: http://www.egt-bg.com
*/

#include "Reel.h"
#include "mm.h"
#include <iostream>
#include "main_game/MainGame.h"

#ifdef EGT_DEBUG
#include <egt_lib/utils/StaticAssert.h>

#endif

#ifdef EGT_REEL_TIMERS
#include "tests/debTimer.h"
#endif

#include <algorithm>
#include "oled/KeyboardScenarioController.h"
#include <game_settings/CommonGameSettings.h>
#include <RestrictionComponents/GameReels/GameVariantsComponent.h>
/* modules */
#include <game_modules/reels_geometry/ReelsLoader.h>
// gpBasicSound
#include <egt_lib/resource_mgr/ResourceMgr.h>

static const short WILD_OFFSET = 2;

Reel::Reel() :
	m_ptrCurrFigInfo(nullptr) ,
	m_ptrBonusFrame(nullptr),
	m_bLeader(false),
	m_bStartingOnFirstFreeGame(false),
    m_bDrawFrame{false},
	m_ucReelLabel(0),
	m_ucPicLineNum(0),
	m_viFakeReels(0),
	m_viFakeReelsFG(0),
	m_efPicLine(0),
	m_ucReelStatus(REEL_STATUS_STOPPED),
	m_scIntroSteps{0},
	m_ucIntroStepsCount(0),
	m_scEpiSteps{0},
	m_ucEpiStepsCount(0),
	m_ssCurPos(0),
	m_usCurIntroPos(0),
	m_usCurEpiPos(0),
	m_nResultsPositions{0},
	m_orgPos_x(0),
	m_orgPos_y(0),
	m_bPreliminaryStop(false),
	m_SpecSoundStr{0},
	m_pSpecSnd(nullptr),
	m_pStopSnd(nullptr),
	m_bSoundDone(true),
	pdPattern(nullptr),
	m_bAccelerationSoundPlayed(false),
	m_usReelMovPiece(0),
	m_usReelPicAllHeight(0),
	m_usReelPicInHeight(0),
	m_usReelPicInWidth(0),
	m_usReelPicFrameWidth(0),
    m_nExtraWildFig{-1}
{
}

Reel::~Reel()
{
}

bool Reel::Init( unsigned char ucReelLabel )
{
	if ( ucReelLabel >= REELS_COUNT ){
		eCDebug( LOG_CATEGORY_GAMES )
		    <<"[Emperors Dream] Reel::Init fail Incorrect Reel id :" << ucReelLabel;
		return false;
	}
	m_bLeader = false;

	m_ucReelLabel = ucReelLabel;

	m_ucPicLineNum = 0;

	m_ucReelStatus = REEL_STATUS_STOPPED;//REEL_STATUS_INTRO;//REEL_STATUS_STOPPED;

	ReelsLoader* m_ReelsLoader = ReelsLoader::GetReelsLoader();
	if(!m_ReelsLoader)
	{
		eCDebug(LOG_CATEGORY_GAMES)
		    << "[ Emperors Dream ] - Reel::Init ReelsLoader FAIL";
		return false;
	}

	m_ssCurPos = 0;
	m_usCurIntroPos = 0;
	m_usCurEpiPos = 0;

	m_ucIntroStepsCount = 0;
	m_ucEpiStepsCount = 0;

	m_bPreliminaryStop = false;
    
	m_orgPos_x = m_ReelsLoader->GetReelX(m_ucReelLabel);
	m_orgPos_y = m_ReelsLoader->GetReelY();

	m_usReelMovPiece = m_ReelsLoader->GetReelMovePiece();
	m_usReelPicAllHeight = m_ReelsLoader->GetReelAllHeight();
	m_usReelPicInHeight = m_ReelsLoader->GetReelHeight();
	m_usReelPicInWidth = m_ReelsLoader->GetReelWidth();
	m_usReelPicFrameWidth = m_ReelsLoader->GetReelFrameWidth();

	//Get fake reel array
	auto gameType = RestrictionComponents::GameVariantsComponent::GameType::MGFakeReel;
	auto gameVariantsPtr = RestrictionComponents::GameVariantsComponent::SafeGet(gGameRestrictionMgr);
	// normal game
	m_viFakeReels = gameVariantsPtr->GetWholeReel( gameType, 0/*m_ucVariant*/, m_ucReelLabel );
	m_efPicLine.resize( m_viFakeReels.size() );

	gameType = RestrictionComponents::GameVariantsComponent::GameType::FGFakeReel;
	m_viFakeReelsFG = gameVariantsPtr->GetWholeReel( gameType, 0/*m_ucVariant*/, m_ucReelLabel );
	if( m_viFakeReelsFG.size() > m_efPicLine.size())
	{
	m_efPicLine.resize( m_viFakeReelsFG.size() );
	}
	m_bSoundDone = true;
	m_bAccelerationSoundPlayed = false;
	InitPicLine();

	return RegisterResource();
}

void Reel::InitPicLine()
{
	m_ucPicLineNum = 0;
	if( false == gMainGame.m_bFG )
	{
		for ( unsigned i = 0; i < m_viFakeReels.size(); ++i )
		{
			m_efPicLine.at(i) = static_cast<EFigure>(m_viFakeReels.at(i));
		}
		m_ucPicLineNum = m_viFakeReels.size();
	}
	else
	{
		for ( unsigned i = 0; i < m_viFakeReelsFG.size(); ++i )
		{
			m_efPicLine.at(i) = static_cast<EFigure>(m_viFakeReelsFG.at(i));
		}
		m_ucPicLineNum = m_viFakeReelsFG.size();
	}
}

void Reel::RestorePicLine()
{
	for ( int i = 0; i < m_ucPicLineNum; ++i )
	{
		if ( ( m_nResultsPositions + ALL_FIGURES_PER_REEL ) == std::find( m_nResultsPositions, m_nResultsPositions + ALL_FIGURES_PER_REEL,  i ) )
		{
			m_efPicLine.at( i )= ( !gMainGame.m_bFG ? static_cast<EFigure>(m_viFakeReels.at(i)) : static_cast<EFigure>( m_viFakeReelsFG.at(i)) ) ;
		}
	}
}

bool Reel::Start()
{
	if( m_ucReelStatus != REEL_STATUS_STOPPED ){
		return false;
	}

#ifdef EGT_REEL_TIMERS

	/* Start the Timer that shows stop time for each reel */
	debTimer::getGlobalTimer().start(m_ucReelLabel);

#endif
    
	m_ucReelStatus = REEL_STATUS_INTRO;

	m_bPreliminaryStop = false;

	m_bSoundDone = false;
	m_bAccelerationSoundPlayed = false;

	RestorePicLine();

	return true;
}

bool Reel::Stop()
{
	if( m_ucReelStatus == REEL_STATUS_STOPPED ||
		m_ucReelStatus == REEL_STATUS_EPILOG ||
		m_ucReelStatus == REEL_STATUS_STOPPING ){
		return false;
	}
    
	if( gpBasicSound->IsPlaying( gGameRM.GetSound( "REEL_ACCELERATE" )) )
		gpBasicSound->StopSound( gGameRM.GetSound( "REEL_ACCELERATE" ) );
    
	m_ucReelStatus = REEL_STATUS_STOPPING;
	InsertResults();

	m_usCurIntroPos = 0;

	gKeyboardScenarioController->RequestFunctionUpdate();

	return true;
}

unsigned char Reel::GetReelingStatus()
{
	return m_ucReelStatus;
}

void Reel::NextStep()
{
	if( m_ucReelStatus == REEL_STATUS_INTRO ) {

		m_ssCurPos -= m_scIntroSteps[m_usCurIntroPos++];

		if( m_usCurIntroPos == m_ucIntroStepsCount ){
			m_ucReelStatus = REEL_STATUS_STARTING;
			m_usCurIntroPos = 0;
		}
	}
	else if( m_ucReelStatus == REEL_STATUS_EPILOG ) {
        m_bDrawFrame = gMainGame.m_bFG ? true : false;
		if( m_nLeadEpiPos == 0 && m_usCurEpiPos == 0 ){
			m_bLeader = true;
		}

		m_ssCurPos -= m_scEpiSteps[m_usCurEpiPos++];

		if( m_bLeader ) {
			m_nLeadEpiPos++;
		}

		if( m_scEpiSteps[m_usCurEpiPos] >= 0 && !m_bSoundDone ) {
			// stop sound ///////////////
			if( m_SpecSoundStr[0] != '\0' && m_SpecSoundStr[0] != '\t' ){
				m_pSpecSnd = gGameRM.GetSound( m_SpecSoundStr );
				gpBasicSound->StartSound( m_pSpecSnd );
			}
			else if( m_SpecSoundStr[0] != '\t' ){ // '\t' means there is no sound at all
				gpBasicSound->StartSound(m_pStopSnd);
			}

			/////////////////////////////
			m_bSoundDone = true;
		}

		if( m_usCurEpiPos >= m_ucEpiStepsCount ) {
			m_ucReelStatus = REEL_STATUS_STOPPED;

			m_usCurEpiPos = 0;
			m_nLeadEpiPos = 0;
			m_bLeader = false;

			#ifdef EGT_REEL_TIMERS

				/* Stop the reeling timer */
				debTimer::getGlobalTimer().stop(m_ucReelLabel + 1);

			#endif
			//gMainGame.ReelStopped(m_ucReelLabel);
		}
	}
	else if( m_ucReelStatus != REEL_STATUS_STOPPED ){

        
		m_ssCurPos -= m_usReelMovPiece;

		if( m_ssCurPos >= (m_ucPicLineNum*m_usReelPicAllHeight) ){
			m_ssCurPos -= (m_ucPicLineNum*m_usReelPicAllHeight);
		}

		if( m_ssCurPos < 0 ) {
			m_ssCurPos += (m_ucPicLineNum*m_usReelPicAllHeight);
		}

		if( m_ucReelStatus == REEL_STATUS_STOPPING ) {
            m_bDrawFrame = gMainGame.m_bFG ? true : false;
			signed short ssDownBorder= m_nResultsPositions[1]*m_usReelPicAllHeight;

			if( (ssDownBorder-m_ssCurPos) <= m_usReelMovPiece &&
				(ssDownBorder-m_ssCurPos) >= (-m_usReelMovPiece)){

				m_ssCurPos = ssDownBorder;
				m_ucReelStatus = REEL_STATUS_EPILOG;
				m_usCurEpiPos = 0;
				//gMainGame.ReelStopped(m_ucReelLabel);
			}
		}

		if( m_ucReelStatus == REEL_STATUS_STARTING ) {
            
			signed short ssDownBorder;

			ssDownBorder= m_nResultsPositions[0] * m_usReelPicAllHeight;
            ssDownBorder -= (m_usReelPicAllHeight*VISIBLE_FIGURES_PER_REEL);

			if( ssDownBorder < 0 ){
				ssDownBorder += (m_ucPicLineNum*m_usReelPicAllHeight);
			}
			else if (ssDownBorder >= m_ucPicLineNum*m_usReelPicAllHeight){
				ssDownBorder-= m_ucPicLineNum*m_usReelPicAllHeight;
			}

			if( (ssDownBorder-m_ssCurPos) <= m_usReelMovPiece && (ssDownBorder-m_ssCurPos) >= (-m_usReelMovPiece) ){
				m_ucReelStatus = REEL_STATUS_REELING;
                m_bDrawFrame = gMainGame.m_bFG ? true : false;
				RemoveResults();
				if( m_bPreliminaryStop ){
					m_bPreliminaryStop = false;
					Stop();
				}
			}
		}
	}

	if( m_ssCurPos >= (m_ucPicLineNum*m_usReelPicAllHeight) ){
		m_ssCurPos -= (m_ucPicLineNum*m_usReelPicAllHeight);
	}

	if( m_ssCurPos < 0 ){
		m_ssCurPos += (m_ucPicLineNum*m_usReelPicAllHeight);
	}
}

void Reel::AddIntroStep( signed char scNewStep )
{
	m_scIntroSteps[m_ucIntroStepsCount++] = scNewStep;
}

void Reel::AddEpilogStep( signed char scNewStep )
{
	m_scEpiSteps[m_ucEpiStepsCount++] = scNewStep;
}

void Reel::SetResults( EFigure efResults[ALL_FIGURES_PER_REEL], bool bImmediate )
{
	for ( int sqrId = 0 ; sqrId < ALL_FIGURES_PER_REEL ; ++sqrId )
	{
		m_efResults[sqrId] = efResults[sqrId];
	}

    if( (gMainGame.m_bFG) && (gMainGame.m_nExtraWild != FIGURES_NUM)){
        EFigure efExtraWild = static_cast<EFigure>(gMainGame.m_nExtraWild);
        m_nExtraWildFig = static_cast<int>(efExtraWild);
		for(unsigned j = 0; j < ALL_FIGURES_PER_REEL; ++j) {
            if(m_efResults[j] == efExtraWild){
                m_efResults[j] = static_cast<EFigure>(REEL_EXTENDING_SYMBOL_OFFSET_VALUE + (int)(m_efResults[j]));
            }
        }
    }

	memcpy(m_efResultsOriginal, m_efResults, ALL_FIGURES_PER_REEL * sizeof(EFigure));
	if( bImmediate ){
		InsertResults( true );
	}
}

void Reel::SetDrawFrame(const bool& bDraw) {
    m_bDrawFrame = bDraw;
}

void Reel::SetExtendedSymbol(int pos, EFigure fig){

	if((pos <= ALL_FIGURES_PER_REEL - 1) && (fig < FIGURES_NUM)){
        m_efResults[pos] = static_cast<EFigure>(REEL_EXTENDING_SYMBOL_OFFSET_VALUE + (int)(fig));
    }

    for ( int sqr = 0 ; sqr < ALL_FIGURES_PER_REEL ; ++sqr )
    {
        m_efPicLine.at( m_nResultsPositions[sqr] ) = m_efResults[sqr];
    }
}

void Reel::ResetExtendedSymbols() {

	memcpy(m_efResults, m_efResultsOriginal, ALL_FIGURES_PER_REEL * sizeof(EFigure));
	for ( int sqr = 0 ; sqr < ALL_FIGURES_PER_REEL ; ++sqr )
	{
		m_efPicLine.at( m_nResultsPositions[sqr] ) = m_efResults[sqr];
	}
    if(!gMainGame.m_bFG) {
        m_nExtraWildFig = -1;
    }
}

void Reel::InsertResults( bool bBeginning )
{
	int nOffsets[ALL_FIGURES_PER_REEL];
	int offset_value = ( bBeginning ? 1 : ALL_FIGURES_PER_REEL ) ;

	for ( int& value : nOffsets )
	{
		value = offset_value;
		--offset_value;
	}

	for (unsigned short i = 0; i < ALL_FIGURES_PER_REEL; i++) {
		m_nResultsPositions[i] = m_ssCurPos / m_usReelPicInHeight - nOffsets[i];
		if (m_nResultsPositions[i] < 0) {
			m_nResultsPositions[i] += m_ucPicLineNum;
		}
		if (m_nResultsPositions[i] >= m_ucPicLineNum) {
			m_nResultsPositions[i] -= m_ucPicLineNum;
		}
	}

	for (unsigned short i = 0; i < ALL_FIGURES_PER_REEL; i++) {
		m_efPicLine.at(m_nResultsPositions[i]) = m_efResults[i];
	}

	if (!bBeginning) {
		m_ssCurPos = GetBottomPicPos(m_nResultsPositions[ALL_FIGURES_PER_REEL - 1]);
	}
}

void Reel::RemoveResults()
{
	for ( int pos = 0; pos < ALL_FIGURES_PER_REEL; pos++ )
	{
		if ( false == gMainGame.m_bFG )
		{
			m_efPicLine.at( m_nResultsPositions[pos] ) = static_cast<EFigure>( m_viFakeReels.at( m_nResultsPositions[pos] ) );
		}
		else
		{
			m_efPicLine.at( m_nResultsPositions[pos] ) = static_cast<EFigure>( m_viFakeReelsFG.at( m_nResultsPositions[pos] ) );
		}
	}
}

void Reel::ReplaceSymbol(EFigure figToReplace, EFigure figToReplaceWith)
{
	for (int i=0; i< m_ucPicLineNum; i++){
		if (m_efPicLine.at(i) == figToReplace)
			m_efPicLine.at(i) = figToReplaceWith;
	}
}

void Reel::SetSpecialSound( const char* pSpecSound )
{
	sprintf( m_SpecSoundStr, "%s", pSpecSound );
}

signed short Reel::GetBottomPicPos( int nPicPos )
{
	return ( nPicPos == m_ucPicLineNum - 1 ) ? 0 : ( nPicPos + 1 )*m_usReelPicAllHeight;
}

void Reel::DrawBlackPattern(int nX, int nY, int nW, int nH)
{
	if(gMainGame.m_ucState == MG_STATE_WINDEMO_EXTENDED){
		gpBasicDraw->SetColor(255, 255, 255, REEL_DARKENED_SYMBOL_COLOR);
		gpBasicDraw->Enable(GL_BLEND);
		gpBasicDraw->DrawPattern(nX, nY, 0, nW, nH, pdPattern);
		gpBasicDraw->Disable(GL_BLEND);
		gpBasicDraw->SetColor(255, 255, 255, 255);
	}
}

/* New Drawing Reel function made for normal and largest figures | Drawing by center coordinate |*/
void Reel::Draw( LevelType eType )
{
	/*  ##                                Draw Reel                                 ##*/
	int pos = m_ssCurPos/m_usReelPicAllHeight;
	int nPixelsFromCurrent = m_ssCurPos - (pos*m_usReelPicAllHeight);

	for( int squareIt = 0; squareIt <= VISIBLE_FIGURES_PER_REEL; ++squareIt )
	{
		/*get current square resource to draw */
		if( ( squareIt < VISIBLE_FIGURES_PER_REEL || nPixelsFromCurrent != 0 )   )
		{
			// getting current figure on square
			EFigure figureId = m_efPicLine.at( pos );

			/*Get figure information  to drawing */
			m_ptrCurrFigInfo = GetFigureInfo( figureId );

			if ( !SquareIsDrawing( figureId , squareIt ) )
			{
				/*current type to draw */
				if ( m_ptrCurrFigInfo && m_ptrCurrFigInfo->m_type == eType )
				{
					SPicDimensions dmnPic = m_ptrCurrFigInfo->m_ptrPicture->GetPicDimensions();

					int nPicY = m_orgPos_y + ( squareIt * m_usReelPicAllHeight) - nPixelsFromCurrent - m_ptrCurrFigInfo->m_correctionY ;
					int nPicX = m_orgPos_x - m_ptrCurrFigInfo->m_correctionX;

					/* draw */
					CalculateReelPictureDimensions( m_ptrCurrFigInfo->m_ptrPicture , m_ptrCurrFigInfo->m_correctionY  , nPicY , dmnPic);

					gpBasicDraw->Enable( GL_BLEND );

					gpBasicDraw->DrawScaledPicture( nPicX, nPicY, 0, m_ptrCurrFigInfo->m_ptrPicture , &dmnPic );
					if ( gMainGame.m_bFG && m_bDrawFrame && m_nExtraWildFig != FIGURES_NUM && (m_nExtraWildFig == figureId || 
                            (m_nExtraWildFig + REEL_EXTENDING_SYMBOL_OFFSET_VALUE) == figureId) 
					     && m_ptrBonusFrame != nullptr)
					{
						gpBasicDraw->DrawScaledPicture( nPicX, nPicY, 0, m_ptrBonusFrame , &dmnPic );
					}

					/*draw black patter in free game for normal figure */
					if ( gMainGame.m_bFG && static_cast<int>(figureId) < REEL_EXTENDING_SYMBOL_OFFSET_VALUE && figureId != ef10_scatter){
						DrawBlackPattern( nPicX, nPicY, dmnPic.nWidth, dmnPic.nHeight);
					}
					else if (figureId == ef10_scatter)
					{
						DrawBlackPattern( m_orgPos_x , m_orgPos_y + ( squareIt * m_usReelPicAllHeight) ,
						                  dmnPic.nWidth - (m_usReelPicInWidth / 2) + WILD_OFFSET, dmnPic.nHeight  - (m_usReelPicInHeight/2) + WILD_OFFSET);
					}
                    
					gpBasicDraw->Disable( GL_BLEND );
				} 
			}
		}

		/*advance next square position */
		++pos;

		if(pos >= m_ucPicLineNum)
		{
			pos = 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////
    #ifdef EGT_REEL_TIMERS
	    /* Draw the reeling time */
	    debTimer::getGlobalTimer().draw(m_orgPos_x,  m_orgPos_y - debTimer::getGlobalTimer().getFontHeight(), m_ucReelLabel + 1);
    #endif
}

/*return resource to drawing */
Reel::FigureInfo* Reel::GetFigureInfo( EFigure eFigureID )
{
	/*Offset of figure */
	bool is_extended_figure = false ;
	if (  gMainGame.m_bFG && static_cast<int>(eFigureID) >= REEL_EXTENDING_SYMBOL_OFFSET_VALUE   )
	{
		is_extended_figure = true ;
		eFigureID = static_cast<EFigure> ( eFigureID - REEL_EXTENDING_SYMBOL_OFFSET_VALUE );
		// second part after first spin starting then check status of reel and he become reelinig then start to drawing expanding simbol
		if ( m_bStartingOnFirstFreeGame )
		{
			if ( m_ucReelStatus != REEL_STATUS_STOPPED )
			{
				if( m_ucReelStatus > REEL_STATUS_STARTING )
				{
					m_bStartingOnFirstFreeGame = false;
				}
			}

			is_extended_figure = false;
		}
	}

	/* is there a logic for free game can write here */
	std::string strTextureID = GetFullTextureID( eFigureID , is_extended_figure  );

	/*free games texture string id  */
	MapFigInfo::iterator it = m_mapFigInfo.find( strTextureID );
	if ( it == m_mapFigInfo.end() )
	{
		eCDebug( LOG_CATEGORY_GAMES )
		    << "Reel::Draw It can not find : " <<  strTextureID << " in m_mapFigInfo map : " ;

		return nullptr;
	}

	return &(it->second)  ;
}

/*calculate position of figure in reel */
void Reel::CalculateReelPictureDimensions(  SPicDef* sPicDef
                                            , int correctionY
                                            , int &nPicPositionY
                                            , SPicDimensions& sPicDimensions ) const
{
	/*coordinate*/
	int nTopCoor = m_orgPos_y;
	int nBottomCoor = nTopCoor + (VISIBLE_FIGURES_PER_REEL *  m_usReelPicAllHeight );

	/*resource have a different size from square label*/
	bool bigPicAfterEpilog = ( ( m_ucReelStatus >= REEL_STATUS_EPILOG ) && ( sPicDimensions.nHeight > m_usReelPicAllHeight ) );

	/*in figure with bigger then standard we resize reel top and bottom position */
	if(bigPicAfterEpilog)
	{
		nTopCoor -= correctionY;
		nBottomCoor += correctionY;
	}

	/*crop top of figure in first visible position on reel */
	if(nPicPositionY < nTopCoor)
	{
		sPicDimensions.fTop += ( sPicDef->GetPicDimensions().fHeight* ( (float) (nTopCoor - nPicPositionY)/sPicDimensions.nHeight ) + DIM_CORRECTION ) ;
		sPicDimensions.nHeight = (nPicPositionY + sPicDimensions.nHeight) - nTopCoor;

		if(bigPicAfterEpilog)
		{
			sPicDimensions.nHeight = 0;
		}

		nPicPositionY = nTopCoor ;
	}

	/*crop bottom of figure in last visible position on reel  */
	else if(nPicPositionY + sPicDimensions.nHeight > nBottomCoor)
	{
		sPicDimensions.nHeight = nBottomCoor - nPicPositionY;
	}

	sPicDimensions.fHeight = ( sPicDef->GetPicDimensions().fHeight*( (float)sPicDimensions.nHeight / sPicDef->GetPicDimensions().nHeight ) + DIM_CORRECTION ) ;
}

/*Register all possible figure resource  */
bool Reel::RegisterResource()
{
	if ( ! (  pdPattern = gGameRM.GetPicture( "DU_BLACK_PATTERN" ) ) )
	{
		eCDebug( LOG_CATEGORY_GAMES )
		    <<"[ Emperors Dream ] Reel::RegisterResource() fail DU_BLACK_PATTERN resource missing";
		return false ;
	}

	if ( ! (  m_ptrBonusFrame = gGameRM.GetPicture( "BONUS_FRAME" ) ) )
	{
		eCDebug( LOG_CATEGORY_GAMES )
		    <<"[ Emperors Dream ] Reel::RegisterResource() fail BONUS_FRAME resource missing";
		return false ;
	}

	/*for all possible figure in game */
	for (int figIt = 0 ; figIt < ( FIGURES_NUM ) ; figIt++ )
	{
		// for normal games
		if  ( false == AddReelFig( static_cast<EFigure>( figIt ) ) )
		{
		eCDebug(LOG_CATEGORY_GAMES)
		        << "[Emperors Dream] Reel::RegisterResource fail it can not register figure id " << figIt ;
		    return false  ;
		}

		// for free games
		if ( figIt != static_cast<EFigure>( ef10_scatter ) )
		{
			if ( !AddReelFig( static_cast<EFigure>( figIt ) , true ) )
			{
				return false;
			}
		}
	}

	if ( !( m_pStopSnd = gGameRM.GetSound( "STOP_SND_1" ) ) ){
		eCDebug( LOG_CATEGORY_GAMES )
            << "[Emperors Dream] Reel::Register sound fail STOP_SND_1";
		return false;
	}

	/* all is fine */
	return true ;
}

/* insert into map information for current figure
 like if have any correction pointer to resource or type of figure */
bool Reel::AddReelFig( EFigure eFigureId , bool bIsFreeGame /*false*/)
{
	/*get current texture id for figure */
	std::string strTextureID = GetFullTextureID(eFigureId , bIsFreeGame ) ;

	/* register */
	if( false == gGameRM.GetRegister().RegisterPicture( strTextureID.c_str() , FIRST_VIEW_GROUP ) )
	{
		/*in free game can have single figure texture id for current figure id */
		if ( bIsFreeGame ) { return true ;  }

		/*it cannot find TEXTRUE ID for current figure then return false */
		eCDebug( LOG_CATEGORY_GAMES )
		    << " [Reel.cpp] it can not find TEXTURE_ID : " << strTextureID ;
		return false;
	}

	/*get picture def pointer of texture */
	SPicDef* resource =  gGameRM.GetPicture( strTextureID.c_str() ) ;
	/*get current offset if have any  */
	int correctionX = (resource->GetPicDimensions().nWidth - m_usReelPicInWidth) / 2;
	/*add correction if need to move resource up or down in reel */
	int correctionY = (resource->GetPicDimensions().nHeight - m_usReelPicInHeight) / 2;

	/*get current figure type to draw
	 type of figure can be change from MainGameDefs.h !!! */
	FigureInfo CurrentFigureInfo ( resource , correctionX , correctionY , FIGURES_LEVEL[eFigureId] );

	/*insert into map Figure information  */
	m_mapFigInfo.insert ( MapFigInfo::value_type( strTextureID , CurrentFigureInfo ) );

	return true ;
}

/*return string of Texture ID like string */
std::string Reel::GetFullTextureID( EFigure eFigureId , bool bIsFreeGame /*false */ )
{
	/*encapsulate picture id */
	std::string strTextureID ( "REEL_" ) ;

	/* suffix */
	strTextureID.append("EF_") ;
	char buffer[4]; /* max value can be 999 ! */
	sprintf( buffer, "%d", static_cast<int>(eFigureId + 1) );
	strTextureID.append( buffer ) ;

	/*return string of texture id */
	return strTextureID;
}

/*get current square id drawing from ReelAnimation {O} if is true : do not draw from here  */
bool Reel::SquareIsDrawing( EFigure FigureId , int nSquareId ) const
{
	if ( FigureId >= FIGURES_NUM || nSquareId >= VISIBLE_FIGURES_PER_REEL ) { return false; }

	bool bSquareIsDrawing = ( gMainGame.m_reelsArea.m_ActionMgr.m_AnimMgr.IsDrawingSquare( FigureId , m_ucReelLabel * VISIBLE_FIGURES_PER_REEL + nSquareId ) );
	return  ( bSquareIsDrawing && REEL_STATUS_STOPPED == m_ucReelStatus );
}

