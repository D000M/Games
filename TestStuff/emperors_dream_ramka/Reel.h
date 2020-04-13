/* Reel.h

	Reel class implementation

	Author: Georgi Dragandjikov
	$Id: Reel.h,v 1.1.2.1 2012/05/11 11:12:47 mbyalkov Exp $

	Copyright (c) 2002-2007 EGT Ltd.
	All rights reserved

	More information at: http://www.egt-bg.com
*/

#ifndef _REEL_H
#define _REEL_H

#include <egt_lib/resource_mgr/ResourceMgr.h>
#include "main_game/MainGameDefs.h"


/** implementation of a single reel */
class Reel{

	static const short  REEL_DARKENED_SYMBOL_COLOR         = 160 ;

	/*  ######## Structure for Figure information ################*/
	struct FigureInfo
	{
		SPicDef* m_ptrPicture  ;
		int  m_correctionX ;
		int  m_correctionY ;
		LevelType m_type ;
		FigureInfo( SPicDef* ptrPic = nullptr , int correctX = 0 , int correctY = 0 , LevelType type = LevelType::efLowLevel )
		    : m_ptrPicture( ptrPic )
		    , m_correctionX( correctX )
		    , m_correctionY( correctY )
		    , m_type( type )
		    {}
	};

	/* map encapsulate for all figure's information for type or etc */
	typedef std::map< std::string, FigureInfo > MapFigInfo ;
	MapFigInfo  m_mapFigInfo;
	/*pointer for current map value */
	FigureInfo* m_ptrCurrFigInfo;
	/*##############################################################*/

	SPicDef* m_ptrBonusFrame;

    int m_nLeadEpiPos = 0;

	/** leading stop flag */
	bool			m_bLeader;
	bool            m_bStartingOnFirstFreeGame;
    bool            m_bDrawFrame;
	/** label - it's the sequence number */
	unsigned char	m_ucReelLabel;

	/** real reeling pictures number */
	unsigned char	m_ucPicLineNum;

	/** MG full fake reel pictures IDs*/
	std::vector<int> m_viFakeReels;
	/** FG full fake reel pictures IDs*/
	std::vector<int> m_viFakeReelsFG;
	/** real reeling pictures IDs */
	std::vector<EFigure>		m_efPicLine;

	/** one from the above 6 reel status values */
	unsigned char	m_ucReelStatus;

	// intro properties ///////////////////
	/** introduction steps */
	signed char		m_scIntroSteps[REEL_MAX_INTRO_STEPS];
	/** introduction steps number */
	unsigned char	m_ucIntroStepsCount;
	///////////////////////////////////////

	// epilog properties ///////////////////
	/** epilog steps */
	signed char		m_scEpiSteps[REEL_MAX_EPILOG_STEPS];
	/** epilog steps number */
	unsigned char	m_ucEpiStepsCount;
	////////////////////////////////////////

	// current reeling positions ////////////////////////////
	/** position  in pixels on the fake reel line */
	signed short	m_ssCurPos;
	/** current intro frame */
	unsigned short	m_usCurIntroPos;
	/** current epilog frame */
	unsigned short	m_usCurEpiPos;
	/////////////////////////////////////////////////////////

	// results /////////////////////////
	/** current results */
	EFigure			m_efResults[ALL_FIGURES_PER_REEL];
	/** replaced real results while extedning figures in free games*/
	EFigure			m_efResultsOriginal[ALL_FIGURES_PER_REEL];
	/** current results positions */
	int				m_nResultsPositions[ALL_FIGURES_PER_REEL];
	////////////////////////////////////

	// the upper-left origin of the reel according to its label ////////////////
	/** x origin of the reel */
	int				m_orgPos_x;
	/** y origin of the reel */
	int				m_orgPos_y;
	////////////////////////////////////////////////////////////////////////////

	// preliminary stop flag /////////////////
	/** preliminary stop flag */
	bool			m_bPreliminaryStop;
	//////////////////////////////////////////

	// special stop sound //////////////////////////
	/** special stop sound id (if any) */
	char			m_SpecSoundStr[20];
	/** special stop sound resource (if any) */
	SndInfo* 		m_pSpecSnd;
	/** special stop sound resource (if any) */
	SndInfo* 		m_pStopSnd;
	/** sound is over flag */
	bool			m_bSoundDone;
	////////////////////////////////////////////////

	SPicDef* pdPattern;

	/** Acceleration sound was played for this reel */
	bool			m_bAccelerationSoundPlayed;

	/** ReelsArea parameters */
	unsigned short m_usReelMovPiece;
	unsigned short m_usReelPicAllHeight;
	unsigned short m_usReelPicInHeight;
	unsigned short m_usReelPicInWidth;
	unsigned short m_usReelPicFrameWidth;
    int m_nExtraWildFig;
public:
	Reel();
	virtual ~Reel();

	bool Init( unsigned char ucReelLabel );

	// action interface ////////////////////////////////
	/** action interface */
	bool Start();
	/** action interface */
	bool Stop();
	/** action interface */
	unsigned char GetReelingStatus();
	/** action interface */
	void NextStep();
	////////////////////////////////////////////////////

	void SetAccelerationSoundPlayed() { m_bAccelerationSoundPlayed = true; }
	bool GetAccelerationSoundPlayed() { return m_bAccelerationSoundPlayed; }

	// introduction & epilog interface ////////////////////////////////
	/** introduction & epilog interface */
	void AddIntroStep( signed char scNewStep );
	/** introduction & epilog interface */
	void AddEpilogStep( signed char scNewStep );
	///////////////////////////////////////////////////////////////////

	void SetSpecialSound( const char* pSpecSound );

	inline bool GetSoundDone() {return m_bSoundDone;}

	// results interface //////////////////////////////
	/** results interface */
	void SetResults( EFigure efResults[ALL_FIGURES_PER_REEL], bool bImmediate = false );

	/** temporary change of figure in exteded mode*/
	void SetExtendedSymbol(int pos, EFigure fig);

	/** restoring original symbols*/
	void ResetExtendedSymbols();

	void ReplaceSymbol(EFigure figToReplace, EFigure figReplaceWith);

	void DisableExpandFigures() { m_bStartingOnFirstFreeGame = true; }
    void SetDrawFrame(const bool& bDraw);
protected:
	/** results interface */
	void InitPicLine();
	/** results interface */
	void RestorePicLine();
	/** results interface */
	void InsertResults( bool bBeginning = false );
	/** results interface */
	void RemoveResults();
	
	///////////////////////////////////////////////////

public:
	/** draw reel in by type  */
	void Draw( LevelType type );

	void DrawBlackPattern(int nX, int nY, int nW, int nH);

private:
	signed short GetBottomPicPos( int nPicPos );

	/*###################################### Functions to Draw figures into center by type ########################################*/
	/*insert all figure information by Id */
	bool AddReelFig( EFigure eFigureId , bool bIsFreeGame = false);
	/*return string of texture ID */
	std::string GetFullTextureID( EFigure eFigureId , bool bIsFreeGame  = false  );
	/*register all resource for current reel */
	bool RegisterResource() ;
	/*return pointer of mat witch encapsulate figure information like resource pointer or offset if have any and type  */
	FigureInfo* GetFigureInfo( EFigure eFigureID );
	/*calculate position and dimensions of figure  */
	void CalculateReelPictureDimensions(SPicDef* sPicDef, int correctionY , int &nPicPositionY, SPicDimensions& sPicDimensions) const;
	/*if return true stop drawing square*/
	bool SquareIsDrawing( EFigure FigureId , int nSquareId ) const ;
	/*############################################################################################################################*/

};

#endif // _REEL_H
