#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct AILogicParameters;
struct DefaultFormulas;
struct GlyphsDB;
struct GuildBuffsCollection;
struct HeroesDB;
struct HeroesLevelUps;
struct ImpulsiveBuffsContainer;
struct MapList;
struct RollSettings;
struct ScoringTable;
struct SessionAudioRoot;
struct SessionLogicRoot;
struct SessionMessages;
struct SessionUIRoot;
struct SessionVisualRoot;
struct UnitsLogicParameters;

struct SessionLogicRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionLogicRoot );
public:
	Ptr< AILogicParameters > aiLogic;
	Ptr< ScoringTable > scoringTable;
	Ptr< UnitsLogicParameters > unitLogicParameters;
	Ptr< GlyphsDB > glyphsDB;
	Ptr< HeroesDB > heroes;
	Ptr< HeroesLevelUps > heroesLevelups;
	Ptr< ImpulsiveBuffsContainer > impulsiveBuffs;
	Ptr< DefaultFormulas > defaultFormulas;
	Ptr< MapList > mapList;
	Ptr< GuildBuffsCollection > guildBuffsCollection;

	SessionLogicRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionLogicRoot& operator = ( const SessionLogicRoot &_sessionLogicRoot ) { Assign( _sessionLogicRoot ); return *this; }
	SessionLogicRoot( const SessionLogicRoot &_sessionLogicRoot ) { Assign( _sessionLogicRoot ); }
	virtual void Assign( const SessionLogicRoot &_sessionLogicRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionLogicRoot * pOther = dynamic_cast< const SessionLogicRoot * > ( _pResource );
		if ( pOther ) SessionLogicRoot::Assign( *pOther );
	}
};

struct SessionRoot : public DbResource
{
	DBRESOURCE_METHODS( SessionRoot );
private:
	static Ptr< SessionRoot > instance;
	static bool instanceInitialized;
public:
	Ptr< SessionUIRoot > uiRoot;
	Ptr< SessionLogicRoot > logicRoot;
	Ptr< SessionVisualRoot > visualRoot;
	Ptr< SessionAudioRoot > audioRoot;
	Ptr< RollSettings > rollSettings;
	Ptr< SessionMessages > sessionMessages;

	SessionRoot();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	SessionRoot& operator = ( const SessionRoot &_sessionRoot ) { Assign( _sessionRoot ); return *this; }
	SessionRoot( const SessionRoot &_sessionRoot ) { Assign( _sessionRoot ); }
	virtual void Assign( const SessionRoot &_sessionRoot );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const SessionRoot * pOther = dynamic_cast< const SessionRoot * > ( _pResource );
		if ( pOther ) SessionRoot::Assign( *pOther );
	}
	static void InitRoot( const DBID& dbid );
	static void InitRoot( const SessionRoot* instance );
	static const Ptr< SessionRoot >& GetRoot();
};

}; // namespace NDb
