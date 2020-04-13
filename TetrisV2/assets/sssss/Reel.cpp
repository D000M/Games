/* Reel.cpp

	Reel class implementation

	Author: Georgi Dragandjikov
	$Id: Reel.cpp,v 1.1.2.4 2015/10/09 09:53:25 anton.boykov Exp $

	Copyright (c) 2002-2007 EGT Ltd.
	All rights reserved

	More information at: http://www.egt-bg.com
*/

#include "Reel.h"
#include "mm.h"
#include "main_game/MainGame.h"

#ifdef EGT_REEL_TIMERS
#include <tests/debTimer.h>
#endif

#include <algorithm>
#include "game_state_mgr/GameStateMgr.h"
#include <oled/KeyboardScenarioController.h>
#include <screen_object/VideoControlMgr.h>
#include <game_settings/CommonGameSettings.h>
#include <RestrictionComponents/GameReels/GameVariantsComponent.h>

using namespace std;

Reel::Reel() :
        m_mapFigInfo{},
        m_ptrCurrFigInfo(nullptr),
        m_bLeader(false),
    	m_usLeadEpiPos(0),
        m_ucReelLabel(0),
        m_viFakeReels(0),
        m_viFakeReelsFG(0),
        m_efPicLine(0),
        m_ucPicLineNum(0),
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
        m_bAccelerationSoundPlayed(false),
        m_usReelMovPiece(0),
        m_usReelPicAllHeight(0),
        m_usReelPicInHeight(0),
        m_usReelPicInWidth(0)
{
}

Reel::~Reel()
{
}

bool Reel::Init( unsigned char ucReelLabel )
{

	m_bLeader = false;

	m_ucReelLabel = ucReelLabel;

	m_ucReelStatus = REEL_STATUS_STOPPED;

	m_ssCurPos = 0;
	m_usCurIntroPos = 0;
	m_usCurEpiPos = 0;

	m_ucIntroStepsCount = 0;
	m_ucEpiStepsCount = 0;

	m_bPreliminaryStop = false;

	m_orgPos_x = gMainGame.m_reelsArea.m_ReelsLoader->GetReelX(m_ucReelLabel - 1);
	m_orgPos_y = gMainGame.m_reelsArea.m_ReelsLoader->GetReelY();

    m_usReelMovPiece = gMainGame.m_reelsArea.m_ReelsLoader->GetReelMovePiece();
	m_usReelPicAllHeight = gMainGame.m_reelsArea.m_ReelsLoader->GetReelAllHeight();
	m_usReelPicInHeight = gMainGame.m_reelsArea.m_ReelsLoader->GetReelHeight();
	m_usReelPicInWidth = gMainGame.m_reelsArea.m_ReelsLoader->GetReelWidth();

	m_bSoundDone = true;
	m_bAccelerationSoundPlayed = false;

    auto gameType = RestrictionComponents::GameVariantsComponent::GameType::MGFakeReel;
    auto gameVariantsPtr = RestrictionComponents::GameVariantsComponent::SafeGet(gGameRestrictionMgr);
    m_viFakeReels = gameVariantsPtr->GetWholeReel( gameType, 0/*m_ucVariant*/, ucReelLabel - 1);
    m_efPicLine.resize( m_viFakeReels.size() );

    gameType = RestrictionComponents::GameVariantsComponent::GameType::FGFakeReel;
    m_viFakeReelsFG = gameVariantsPtr->GetWholeReel( gameType, 0/*m_ucVariant*/, ucReelLabel - 1);
    if( m_viFakeReelsFG.size() > m_efPicLine.size())
    {
        m_efPicLine.resize( m_viFakeReelsFG.size() );
    }

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
            m_efPicLine.at(i) = static_cast<EFigure>( m_viFakeReels.at(i) );
        }
        m_ucPicLineNum = m_viFakeReels.size();
    }
        else
    {
        for ( unsigned i = 0; i < m_viFakeReelsFG.size(); ++i )
        {
            m_efPicLine.at(i) = static_cast<EFigure>( m_viFakeReelsFG.at(i) );
    }

        m_ucPicLineNum = m_viFakeReelsFG.size();
    }
}

void Reel::RestorePicLine()
{
	for ( int i = 0; i < m_ucPicLineNum; ++i )
	{
		if ( gMainGame.m_bFG && ( m_nResultsPositions + ALL_FIGURES_PER_REEL ) == std::find( m_nResultsPositions, m_nResultsPositions + ALL_FIGURES_PER_REEL,  i ) )
		{
			m_efPicLine.at(i) = static_cast<EFigure>( m_viFakeReelsFG.at(i) );
		}
		else if (  ( m_nResultsPositions + ALL_FIGURES_PER_REEL ) == std::find( m_nResultsPositions, m_nResultsPositions + ALL_FIGURES_PER_REEL,  i )  )
		{
			m_efPicLine.at(i) = static_cast<EFigure>( m_viFakeReels.at(i) );
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
	if( m_ucReelStatus == REEL_STATUS_INTRO ){

		m_ssCurPos -= m_scIntroSteps[m_usCurIntroPos++];

		if( m_usCurIntroPos == m_ucIntroStepsCount ){
			m_ucReelStatus = REEL_STATUS_STARTING;
			m_usCurIntroPos = 0;
		}
	}
	else if( m_ucReelStatus == REEL_STATUS_EPILOG ){

        if( m_usLeadEpiPos == 0 && m_usCurEpiPos == 0 ){
			m_bLeader = true;
		}

		m_ssCurPos -= m_scEpiSteps[m_usCurEpiPos++];

		if( m_bLeader ){
            m_usLeadEpiPos++;
		}

		if( m_scEpiSteps[m_usCurEpiPos] >= 0 && !m_bSoundDone ){
			// stop sound ///////////////
			if( m_SpecSoundStr[0] != '\0' && m_SpecSoundStr[0] != '\t' ){
				m_pSpecSnd = gGameRM.GetSound( m_SpecSoundStr );
				gpBasicSound->StartSound( m_pSpecSnd );
			}
			else if( m_SpecSoundStr[0] != '\t' ){ // '\t' means there is no sound at all
				gpBasicSound->StartSound( m_pStopSnd );
			}
			/////////////////////////////

			m_bSoundDone = true;
		}

		if( m_usCurEpiPos >= m_ucEpiStepsCount ){
			m_ucReelStatus = REEL_STATUS_STOPPED;
			m_usCurEpiPos = 0;
            m_usLeadEpiPos = 0;
			m_bLeader = false;

			#ifdef EGT_REEL_TIMERS

				/* Stop the reeling timer */
				debTimer::getGlobalTimer().stop(m_ucReelLabel);

			#endif
		}
	}
	else if( m_ucReelStatus != REEL_STATUS_STOPPED ){


		m_ssCurPos -= m_usReelMovPiece;

		if( m_ssCurPos >= (m_ucPicLineNum* m_usReelPicAllHeight) ){
			m_ssCurPos -= (m_ucPicLineNum* m_usReelPicAllHeight);
		}

		if( m_ssCurPos < 0 ){
			m_ssCurPos += (m_ucPicLineNum * m_usReelPicAllHeight);
		}

		if( m_ucReelStatus == REEL_STATUS_STOPPING ){

			signed short ssDownBorder= m_nResultsPositions[1]*m_usReelPicAllHeight;

			if( (ssDownBorder-m_ssCurPos) <= m_usReelMovPiece &&
				(ssDownBorder-m_ssCurPos) >= (-m_usReelMovPiece))
			{
				m_ssCurPos = ssDownBorder;
				m_ucReelStatus = REEL_STATUS_EPILOG;
				m_usCurEpiPos = 0;
			}
		}

		if( m_ucReelStatus == REEL_STATUS_STARTING ){

			signed short ssDownBorder;

			ssDownBorder= m_nResultsPositions[0] * m_usReelPicAllHeight;
			ssDownBorder -= (m_usReelPicAllHeight * VISIBLE_FIGURES_PER_REEL);

			if( ssDownBorder < 0 ){
				ssDownBorder += (m_ucPicLineNum* m_usReelPicAllHeight);
			}
			else if (ssDownBorder >= m_ucPicLineNum*m_usReelPicAllHeight){
				ssDownBorder-= m_ucPicLineNum*m_usReelPicAllHeight;
			}

			if( (ssDownBorder-m_ssCurPos) <= m_usReelMovPiece &&
				(ssDownBorder-m_ssCurPos) >= (-m_usReelMovPiece) )
			{
				m_ucReelStatus = REEL_STATUS_REELING;
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
	for( int i = 0; i < ALL_FIGURES_PER_REEL; i++ )
		m_efResults[i] = efResults[i];

	if( bImmediate ){
		InsertResults( true );
	}
}

void Reel::InsertResults( bool bBeginning )
{
	int nOffsets[ALL_FIGURES_PER_REEL];

    int offset_index = ( bBeginning ? 1 : ALL_FIGURES_PER_REEL );

    for ( int i = 0 ; i < ALL_FIGURES_PER_REEL ; ++i )
    {
        nOffsets[i] = offset_index;
        --offset_index ;
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


	for (unsigned short i = 0; i < ALL_FIGURES_PER_REEL; i++)
	{
        m_efPicLine.at(m_nResultsPositions[i]) = m_efResults[i];
	}

	if (!bBeginning)
	{
		m_ssCurPos = GetBottomPicPos(m_nResultsPositions[ALL_FIGURES_PER_REEL - 1]);
	}

}

void Reel::RemoveResults()
{
	for ( int pos = 0; pos < ALL_FIGURES_PER_REEL; pos++ )
	{
		if( gMainGame.m_bFG )
		{
			m_efPicLine.at(m_nResultsPositions[pos]) = static_cast<EFigure>( m_viFakeReelsFG.at(m_nResultsPositions[pos]) );
		}
		else{
			m_efPicLine.at(m_nResultsPositions[pos]) = static_cast<EFigure>( m_viFakeReels.at(m_nResultsPositions[pos]) );
		}

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


void Reel::SetCurrFakeBonusReels( int nFigNum )
{
	/*for (int i = 0 ; i < REELS_COUNT; i ++)
	{
			if ( m_efPicLine.at(i) != ef12_scatter && m_efPicLine.at(i) != ef11_wild) // we can have Scatter on 5th Reel in FG
			{
				m_efPicLine.at(i) = static_cast<EFigure>( nFigNum);
			}
	}*/
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
            DrawingInfo info;
            // getting current figure on square
            info.figureId = m_efPicLine.at( pos );
            // check to drawing figure from anather object 
            if ( !SquareIsDrawing( info.figureId  , squareIt )  )
            {
                /*Get figure information  to drawing */
                m_ptrCurrFigInfo = GetFigureInfo( info.figureId );
                /*current type to draw */
                if ( m_ptrCurrFigInfo && m_ptrCurrFigInfo->m_type == eType )
                {
                    info.pic_resource = m_ptrCurrFigInfo->m_ptrPicture;
                    info.pic_dim = m_ptrCurrFigInfo->m_ptrPicture->GetPicDimensions();
                    // position
                    info.pos.x = m_orgPos_x - m_ptrCurrFigInfo->m_correctionX;
                    info.pos.y = m_orgPos_y + ( squareIt * m_usReelPicAllHeight) - nPixelsFromCurrent - m_ptrCurrFigInfo->m_correctionY ;
                    // calculate dimention
                    CalculateReelPictureDimensions( m_ptrCurrFigInfo->m_ptrPicture , m_ptrCurrFigInfo->m_correctionY  , info.pos.y , info.pic_dim);
                    // save param to draw in preority
                    m_drawReel.push_back( info );
                }
            }
        }
        /*advance next square position */
        if(++pos >= m_ucPicLineNum)
        {
            pos = 0;
        }
    }

    if ( !m_drawReel.empty())
    {
        //sorted
        sort(m_drawReel.begin(), m_drawReel.end(), Greater);
        /* draw */
        gpBasicDraw->Enable( GL_BLEND );
        for ( const DrawingInfo& draw:m_drawReel)
        {
            gpBasicDraw->DrawScaledPicture( draw.pos.x, draw.pos.y, 0, draw.pic_resource, &draw.pic_dim);
        }
        gpBasicDraw->Disable( GL_BLEND );
    }
    // clear
    m_drawReel.clear();

    //////////////////////////////////////////////////////////////////////////////////
    #ifdef EGT_REEL_TIMERS
        /* Draw the reeling time */
        debTimer::getGlobalTimer().draw(m_orgPos_x,  m_orgPos_y - debTimer::getGlobalTimer().getFontHeight(), m_ucReelLabel);
    #endif
}

bool Reel::Greater( const DrawingInfo& lhs , const DrawingInfo& rhs ){
    return lhs.figureId < rhs.figureId;
}

/*return resource to drawing */
Reel::FigureInfo* Reel::GetFigureInfo( EFigure eFigureID )
{
    /* is there a logic for free game can write here */
    std::string strTextureID = GetFullTextureID( eFigureID );

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
        nBottomCoor += correctionY + 12;
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
    /*for all possible figure in game */
    for (int figIt = 0 ; figIt < ( FIGURES_NUM ) ; figIt++ )
    {
        if  ( false == AddReelFig( static_cast<EFigure>( figIt ) ) )
        {
            return false  ;
        }
    }

    m_pStopSnd = gGameRM.GetSound("STOP_SND_1");


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

    /*free game */
    if( bIsFreeGame )
    {
        strTextureID.append("FG_");
    }

    /* suffix */
    strTextureID.append("EF_") ;
    char buffer[4]; /* max value can be 999 ! */
    sprintf( buffer, "%d", static_cast<int>(eFigureId + 1) );
    strTextureID.append( buffer ) ;

    /*return string of texture id */
    return strTextureID;
}

/*get current square id drawing from ReelAnimation {O} if is true : do not draw from here  */
bool Reel::SquareIsDrawing( EFigure figureId , int nSquareId ) const
{
    // validate input parameter 
    if ( figureId >= FIGURES_NUM || nSquareId >= VISIBLE_FIGURES_PER_REEL )  { return false ; }

    unsigned squareId = ( (m_ucReelLabel - 1)* VISIBLE_FIGURES_PER_REEL + nSquareId );
    bool bSquareIsDrawing = ( gMainGame.m_reelsArea.m_ActionMgr.m_AnimMgr.IsDrawingSquare( figureId , squareId ) ) ;

    return  ( bSquareIsDrawing && REEL_STATUS_STOPPED == m_ucReelStatus );
}
