// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBGameLogic.h"
#include "../PF_GameLogic/DBStats.h"
#include "../PF_GameLogic/DBUnit.h"
#include "../PF_GameLogic/DBHeroesList.h"
#include "../PF_GameLogic/DBImpulsiveBuffs.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../PF_GameLogic/DbMapList.h"
#include "../PF_GameLogic/DBGuild.h"
#include "../PF_GameLogic/DBVisualRoots.h"
#include "../PF_GameLogic/DBServer.h"
#include "../PF_GameLogic/DBSessionMessages.h"
#include "DBSessionRoots.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( SessionLogicRoot );
REGISTER_DBRESOURCE( SessionRoot );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionLogicRoot::SessionLogicRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionLogicRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &aiLogic );
	saver.Add( 3, &scoringTable );
	saver.Add( 4, &unitLogicParameters );
	saver.Add( 5, &glyphsDB );
	saver.Add( 6, &heroes );
	saver.Add( 7, &heroesLevelups );
	saver.Add( 8, &impulsiveBuffs );
	saver.Add( 9, &defaultFormulas );
	saver.Add( 10, &mapList );
	saver.Add( 11, &guildBuffsCollection );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionLogicRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionLogicRoot* parentPtr = (SessionLogicRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionLogicRoot::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "aiLogic", &aiLogic );
	saver.Add( "scoringTable", &scoringTable );
	saver.Add( "unitLogicParameters", &unitLogicParameters );
	saver.Add( "glyphsDB", &glyphsDB );
	saver.Add( "heroes", &heroes );
	saver.Add( "heroesLevelups", &heroesLevelups );
	saver.Add( "impulsiveBuffs", &impulsiveBuffs );
	saver.Add( "defaultFormulas", &defaultFormulas );
	saver.Add( "mapList", &mapList );
	saver.Add( "guildBuffsCollection", &guildBuffsCollection );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionLogicRoot::Assign( const SessionLogicRoot& _sessionLogicRoot )
{
	aiLogic = _sessionLogicRoot.aiLogic;
	scoringTable = _sessionLogicRoot.scoringTable;
	unitLogicParameters = _sessionLogicRoot.unitLogicParameters;
	glyphsDB = _sessionLogicRoot.glyphsDB;
	heroes = _sessionLogicRoot.heroes;
	heroesLevelups = _sessionLogicRoot.heroesLevelups;
	impulsiveBuffs = _sessionLogicRoot.impulsiveBuffs;
	defaultFormulas = _sessionLogicRoot.defaultFormulas;
	mapList = _sessionLogicRoot.mapList;
	guildBuffsCollection = _sessionLogicRoot.guildBuffsCollection;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SessionRoot::SessionRoot()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ptr< SessionRoot > SessionRoot::instance;
void SessionRoot::InitRoot( const DBID& dbid ) { InitRoot( Get<SessionRoot>( dbid ) ); }
void SessionRoot::InitRoot( const SessionRoot* _instance ) { instance = _instance; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const Ptr< SessionRoot >& SessionRoot::GetRoot()
{
	NI_ASSERT( IsValid( instance ), "Root for type \"SessionRoot\" not initialized" );
	return instance;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionRoot::operator&( IBinSaver &saver )
{
	saver.Add( 2, &uiRoot );
	saver.Add( 3, &logicRoot );
	saver.Add( 4, &visualRoot );
	saver.Add( 5, &audioRoot );
	saver.Add( 6, &rollSettings );
	saver.Add( 7, &sessionMessages );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SessionRoot::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			SessionRoot* parentPtr = (SessionRoot*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionRoot::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "uiRoot", &uiRoot );
	saver.Add( "logicRoot", &logicRoot );
	saver.Add( "visualRoot", &visualRoot );
	saver.Add( "audioRoot", &audioRoot );
	saver.Add( "rollSettings", &rollSettings );
	saver.Add( "sessionMessages", &sessionMessages );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SessionRoot::Assign( const SessionRoot& _sessionRoot )
{
	uiRoot = _sessionRoot.uiRoot;
	logicRoot = _sessionRoot.logicRoot;
	visualRoot = _sessionRoot.visualRoot;
	audioRoot = _sessionRoot.audioRoot;
	rollSettings = _sessionRoot.rollSettings;
	sessionMessages = _sessionRoot.sessionMessages;
}
}; // namespace NDb
