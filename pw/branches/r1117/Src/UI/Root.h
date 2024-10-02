#pragma once
#include "System\StarForce\StarForce.h"


namespace NDb
{
	struct UIRoot;
	struct UIBaseLayout;
	struct UIContentResource;
}


namespace UI
{


class User;


STARFORCE_EXPORT void Initialize( const NDb::UIRoot *pRoot );
void ApplyNewParams( unsigned long width, unsigned long height, bool isFullScreen, bool isBorderless );

void Release();


void NewFrame( DWORD time );
void PresentFrame( DWORD time, bool active );


DWORD GetSyncTime();


User * GetUser();


const NDb::UIBaseLayout *GetScreenLayout( const string & screenId );


void SetCursor( const string & cursorId );
void FreezeCursor( bool freeze );


const NDb::UIContentResource *GetContentResource( const string & groupId, const string & contentId );


const string & GetConstant( const string & constId );
const int GetIntConstant( const string & constId );
const float GetFloatConstant( const string & constId );
const bool GetBoolConstant( const string & constId );

_interface ICustomSubstitutes
{
  virtual const wstring * GetSubstitute( const wstring & name ) = 0;
};

void SubstituteText( wstring & result, const wchar_t * source, ICustomSubstitutes * customSubsts = 0 );

const NDb::UIRoot *GetUIRoot();
void SetUIRoot( const NDb::UIRoot *pRoot );

} //namespace UI
