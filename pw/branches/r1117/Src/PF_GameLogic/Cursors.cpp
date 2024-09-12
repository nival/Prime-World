#include "stdafx.h"

#include "./Cursors.h"
#include "../Client/Cursor.h"

#include "DBUIRoot.h"

namespace NGameX
{
	static NDb::Ptr<NDb::H6UIRoot> pUIRoot;
	static const NDb::DBID DBID_H6UIROOT( "UI/H6UIRoot.xdb" );

	const NDb::H6UIRoot *GetH6UIRoot()
	{
		if ( !pUIRoot )
		{
			pUIRoot = NDb::Get<NDb::H6UIRoot>( DBID_H6UIROOT );
			NI_VERIFY( pUIRoot, "Panic! Cannot load UI Root !!!", pUIRoot = new NDb::H6UIRoot() );
		}
		return pUIRoot;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool g_cursorsInit = false;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void InitCursors()
	{
		//if ( g_cursorsInit )
		//	return;
		//g_cursorsInit = true;

		//NI_VERIFY( GetH6UIRoot(), "No UI root found!", return );

		//for ( int i = 0; i < GetH6UIRoot()->cursors.size(); ++i )
		//{
		//	const string & cursorName = GetH6UIRoot()->cursors[i].name;

		//	if ( cursorName.empty() )
		//		continue;

		//	const NDb::UICursor *pCursor = GetH6UIRoot()->cursors[i].cursor;
		//	const NDb::UICursor *pCursorOverlay = GetH6UIRoot()->cursors[i].cursorOverlay;
		//	const CTPoint<int> cursorOverlayOffset = GetH6UIRoot()->cursors[i].cursorOverlayOffset;

		//	NCursor::Image cursor;
		//	NCursor::Image overlay;

		//	if ( !cursor.Load( pCursor ) )
		//		continue;
		//	if ( overlay.Load( pCursorOverlay ) )
		//		cursor.Blit( cursorOverlayOffset.x, cursorOverlayOffset.y, overlay, 0,0 );

		//	if ( cursorName == "default" )
		//		NCursor::SetDefault( &cursor );

		//	NCursors::Register( cursorName, &cursor );
		//}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetCursor( const string & cursorName, bool force )
	{
		NCursors::Select( cursorName, force ? 1 : 0 );
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void FreezeCursor( bool freeze )
	{
		NCursor::Freeze( freeze );
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	static string checkName;
	void MakeAdventureCursorName( string *pName, const string & prefix, bool danger, int days )
	{
		if ( !pName )
			return;

		for ( int j = 0; j < 2; ++j )
		{
			*pName = prefix;
			if ( (j==0) == danger )
				*pName += "_danger";

			days = Clamp( days, 0, 9 );
			for ( int i = days; i >= 0; --i )
			{
				checkName = NStr::StrFmt("%s_%d", pName->c_str(),i+1);
				if ( NCursors::IsRegistered( checkName ) )
				{
					*pName = checkName;
					return;
				}
			}

			if ( NCursors::IsRegistered( *pName ) )
				return;
		}

		*pName = prefix;
	}
}