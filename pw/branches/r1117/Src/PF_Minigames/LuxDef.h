#pragma once

//////////////////////////////////////////////////////////////////////////
//
// common data structures for luxor game part
//
//////////////////////////////////////////////////////////////////////////

namespace PF_Minigames
{

// common logic error codes (basic scheme)	
const int LUX_OK              = 0;
const int LUX_ERROR           = LUX_OK+1;
const int LUX_NOT_IMPLEMENTED = LUX_OK+2;
const int LUX_NOT_INIT        = LUX_OK+3;
const int LUX_ALREADY_INIT    = LUX_OK+4;
const int LUX_NO_ITEM         = LUX_OK+5;
const int LUX_ALREADY_RUN     = LUX_OK+6;
const int LUX_LENGHT_TOO_BIG  = LUX_OK+7;
const int LUX_WRONG_COORD     = LUX_OK+8;
const int LUX_ERROR_MOVING    = LUX_OK+9;
const int LUX_ERROR_STOPPED   = LUX_OK+10;
const int LUX_LENGHT_LESS_ZERO  = LUX_OK+12;

//////////////////////////////////////////////////////////////////////////
//
// common input structures, used in logic for internal processing
//
//////////////////////////////////////////////////////////////////////////
struct SEaselMouseInput
{
	int xCoord;
	int yCoord;

	bool leftBtnClicked;
	bool rightBtnClicked;

  SEaselMouseInput() : xCoord( 0 ), yCoord( 0 ), leftBtnClicked( false ), rightBtnClicked( false ) {}
};

} //namespace PF_Minigames
