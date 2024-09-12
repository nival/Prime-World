#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBGameLogic.h"
#include "../Scene/DBSceneBase.h"

struct IXmlSaver;
// forward declarations for factories
namespace PF_Minigames
{
	class IMinigamesMain;
}; //namespace PF_Minigames

namespace NDb
{
struct Ability;

struct Bidon
{
public:
	Ptr< Ability > ability;
	string commonNode;
	string upperNode;
	string commonMarker;
	string upperMarker;

	Bidon();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct DBMinigamesCommon : public MinigamesBasic
{
	DBRESOURCE_METHODS( DBMinigamesCommon );
public:
	ViewCamera cameraOptions;
	bool smoothCamera;
	CTextRef namePoolMelee;
	CTextRef namePoolRange;
	CTextRef namePoolSiege;
	vector< Bidon > sessionBidonAbilities;

	DBMinigamesCommon();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DBMinigamesCommon& operator = ( const DBMinigamesCommon &_dBMinigamesCommon ) { Assign( _dBMinigamesCommon ); return *this; }
	DBMinigamesCommon( const DBMinigamesCommon &_dBMinigamesCommon ) { Assign( _dBMinigamesCommon ); }
	virtual void Assign( const DBMinigamesCommon &_dBMinigamesCommon );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DBMinigamesCommon * pOther = dynamic_cast< const DBMinigamesCommon * > ( _pResource );
		if ( pOther ) DBMinigamesCommon::Assign( *pOther );
	}

	virtual PF_Minigames::IMinigamesMain* Construct() const;
};

}; // namespace NDb
