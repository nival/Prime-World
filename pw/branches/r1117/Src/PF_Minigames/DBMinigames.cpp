// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "../PF_GameLogic/DBAbility.h"
#include "DBMinigames.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( DBMinigamesCommon );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// includes for factories
#include "MinigamesMain.h"

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Bidon::Bidon()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Bidon::operator&( IBinSaver &saver )
{
	saver.Add( 2, &ability );
	saver.Add( 3, &commonNode );
	saver.Add( 4, &upperNode );
	saver.Add( 5, &commonMarker );
	saver.Add( 6, &upperMarker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Bidon::operator&( IXmlSaver &saver )
{
	saver.Add( "ability", &ability );
	saver.Add( "commonNode", &commonNode );
	saver.Add( "upperNode", &upperNode );
	saver.Add( "commonMarker", &commonMarker );
	saver.Add( "upperMarker", &upperMarker );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DBMinigamesCommon::DBMinigamesCommon() :
		smoothCamera( false )
{
	sessionBidonAbilities.resize( 5 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBMinigamesCommon::operator&( IBinSaver &saver )
{
	saver.Add( 1, (MinigamesBasic*)this );
	saver.Add( 2, &cameraOptions );
	saver.Add( 3, &smoothCamera );
	saver.Add( 4, &namePoolMelee );
	saver.Add( 5, &namePoolRange );
	saver.Add( 6, &namePoolSiege );
	saver.Add( 7, &sessionBidonAbilities );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DBMinigamesCommon::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			DBMinigamesCommon* parentPtr = (DBMinigamesCommon*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBMinigamesCommon::SerializeSelf( IXmlSaver &saver )
{
	MinigamesBasic::SerializeSelf( saver );
	saver.Add( "cameraOptions", &cameraOptions );
	saver.Add( "smoothCamera", &smoothCamera );
	saver.Add( "namePoolMelee", &namePoolMelee );
	saver.Add( "namePoolRange", &namePoolRange );
	saver.Add( "namePoolSiege", &namePoolSiege );
	sessionBidonAbilities.resize( 5 );
	saver.Add( "sessionBidonAbilities", &sessionBidonAbilities );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DBMinigamesCommon::Assign( const DBMinigamesCommon& _dBMinigamesCommon )
{
	cameraOptions.name = _dBMinigamesCommon.cameraOptions.name;
	cameraOptions.anchor = _dBMinigamesCommon.cameraOptions.anchor;
	cameraOptions.yaw = _dBMinigamesCommon.cameraOptions.yaw;
	cameraOptions.pitch = _dBMinigamesCommon.cameraOptions.pitch;
	cameraOptions.roll = _dBMinigamesCommon.cameraOptions.roll;
	cameraOptions.rod = _dBMinigamesCommon.cameraOptions.rod;
	cameraOptions.fov = _dBMinigamesCommon.cameraOptions.fov;
	cameraOptions.environment = _dBMinigamesCommon.cameraOptions.environment;
	smoothCamera = _dBMinigamesCommon.smoothCamera;
	namePoolMelee = _dBMinigamesCommon.namePoolMelee;
	namePoolRange = _dBMinigamesCommon.namePoolRange;
	namePoolSiege = _dBMinigamesCommon.namePoolSiege;
	sessionBidonAbilities = _dBMinigamesCommon.sessionBidonAbilities;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PF_Minigames::IMinigamesMain* DBMinigamesCommon::Construct() const
{
	return new PF_Minigames::MinigamesMain( *this );
}
}; // namespace NDb
