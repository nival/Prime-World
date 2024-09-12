#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"
#include "../PF_GameLogic/DBAbility.h"
#include "../PF_GameLogic/DBDayNight.h"
#include "../PF_GameLogic/DBGameLogic.h"
#include "../PF_GameLogic/DBStats.h"
#include "../Render/DBRender.h"
#include "../Render/DBRenderResources.h"
#include "../Scene/DBSceneBase.h"
#include "../Sound/DBSound.h"

struct IXmlSaver;

namespace NDb
{
struct AdventureCameraSettings;
struct AdventureTooltipParams;
struct AdvMap;
struct AdvMapCreep;
struct AdvMapDescription;
struct AdvMapHeroesOverride;
struct AdvMapHeroesOverrideData;
struct AdvMapModeDescription;
struct AdvMapSettings;
struct BaseCreepSpawner;
struct BotsSettings;
struct CreepAnnounceList;
struct DBMinimap;
struct DialogsCollection;
struct DictionaryPreloadingResources;
struct FWODVisualInfo;
struct GameObject;
struct GameSvcSettings;
struct GlyphManagerParams;
struct GlyphsDB;
struct Hero;
struct HeroNaftaParams;
struct HeroRespawnParams;
struct HintsCollection;
struct KillExperienceModifier;
struct LightEnvironment;
struct MapMMakingSettings;
struct MinimapImages;
struct ModeRollSettings;
struct PostFXParams;
struct ScoringTable;
struct SessionQuestsCollection;
struct SoundEnvironment;
struct Talent;
struct Terrain;
struct Texture;
struct VotingForSurrenderPerMission;

enum EMapType
{
	MAPTYPE_NONE = 0,
	MAPTYPE_PVP = 1,
	MAPTYPE_CTE = 2,
	MAPTYPE_TRAINING = 3,
	MAPTYPE_TUTORIAL = 4,
	MAPTYPE_SERIES = 5,
	MAPTYPE_COOPERATIVE = 6,
};

const char *EnumToString( const EMapType value );
const EMapType StringToEnum_EMapType( const char* value );

template <>
struct KnownEnum< EMapType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const EMapType value ) { return EnumToString( value ); }
	static const EMapType ToEnum( const char* value ) { return StringToEnum_EMapType( value ); }
	static const EMapType ToEnum( const string& value ) { return StringToEnum_EMapType( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

enum PartyMode
{
	PARTYMODE_NOTALLOWED = 0,
	PARTYMODE_ONLYALLIES = 1,
	PARTYMODE_ALLIESANDENEMIES = 2,
};

const char *EnumToString( const PartyMode value );
const PartyMode StringToEnum_PartyMode( const char* value );

template <>
struct KnownEnum< PartyMode >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const PartyMode value ) { return EnumToString( value ); }
	static const PartyMode ToEnum( const char* value ) { return StringToEnum_PartyMode( value ); }
	static const PartyMode ToEnum( const string& value ) { return StringToEnum_PartyMode( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

struct AdvMapObject
{
public:
	Ptr< GameObject > gameObject;
	CPlacement offset;
	EPlayerID player;
	bool lockMap;
	string scriptName;
	string scriptGroupName;

	AdvMapObject();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AdvMapPlayerData
{
public:
	Ptr< Hero > hero;
	CTextRef nickname;

	AdvMapPlayerData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct CreepAnnounce
{
public:
	Ptr< BaseCreepSpawner > spawner;
	vector< Ptr< AdvMapCreep > > creeps;

	CreepAnnounce();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct LoadingBackgroundImages
{
public:
	Ptr< Texture > back;
	Ptr< Texture > logo;

	LoadingBackgroundImages();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct PrimeSettings
{
public:
	bool giveWorldPrimeToDead;
	float giveWorldPrimeRessurectDelay;
	int startPrimePerTeam;
	int giveWorldPrimeAmount;
	vector< float > multipliers;
	float naftaForKill;
	float naftaForAssist;
	float naftaSpecForKill;
	float teamNaftaForPresence;
	Ptr< KillExperienceModifier > neutralKillExperienceModifier;
	Ptr< HeroNaftaParams > heroNaftaParams;
	float awardSpecRange;
	float awardTeamRange;

	PrimeSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ResourceDesc
{
public:
	string key;
	Ptr< DbResource > resource;

	ResourceDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ScriptArea
{
public:
	string name;
	CVec2 position;
	float radius;
	ESpellTarget targetType;

	ScriptArea();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct ScriptPolygonAreaPolygon
{
public:
	string name;
	vector< int > indexes;

	ScriptPolygonAreaPolygon();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct StatisticBackgoundImages
{
public:
	Ptr< Texture > normal;
	Ptr< Texture > win;
	Ptr< Texture > loose;

	StatisticBackgoundImages();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct TriggerMarkerBinding
{
public:
	string TriggerPoint;
	vector< string > MarkerPoints;

	TriggerMarkerBinding();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct AdvMap : public DbResource
{
	DBRESOURCE_METHODS( AdvMap );
public:
	Ptr< AdventureCameraSettings > cameraSettings;
	Ptr< MinimapImages > minimapImages;
	vector< AdvMapObject > objects;
	Ptr< Terrain > terrain;
	Ptr< SoundEnvironment > soundEnvironment;
	Ptr< LightEnvironment > lightEnvironment;
	Ptr< LightEnvironment > nightLightEnvironment;
	BakedLighting bakedLighting;
	vector< PointLightInfo > pointLights;
	vector< ScriptArea > scriptAreas;
	string ObjectsLayerFileName;
	string waterMapFileName;
	SoundAmbienceMap ambienceMap;
	Ptr< AdvMapSettings > mapSettings;
	Ptr< PostFXParams > postEffect;
	DayNightSettings dayNightSettings;

	AdvMap();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMap& operator = ( const AdvMap &_advMap ) { Assign( _advMap ); return *this; }
	AdvMap( const AdvMap &_advMap ) { Assign( _advMap ); }
	virtual void Assign( const AdvMap &_advMap );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMap * pOther = dynamic_cast< const AdvMap * > ( _pResource );
		if ( pOther ) AdvMap::Assign( *pOther );
	}
};

struct AdvMapCameraSpline : public GameObject
{
	DBRESOURCE_METHODS( AdvMapCameraSpline );
public:
	enum { typeId = 0xEF924380 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AdvMapCameraSpline::typeId; }
	vector< Spline3DControlPointDesc > points;
	int hight;
	bool SmoothStart;
	float StartTime;
	bool SmoothEnd;
	float EndTime;

	AdvMapCameraSpline();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapCameraSpline& operator = ( const AdvMapCameraSpline &_advMapCameraSpline ) { Assign( _advMapCameraSpline ); return *this; }
	AdvMapCameraSpline( const AdvMapCameraSpline &_advMapCameraSpline ) { Assign( _advMapCameraSpline ); }
	virtual void Assign( const AdvMapCameraSpline &_advMapCameraSpline );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapCameraSpline * pOther = dynamic_cast< const AdvMapCameraSpline * > ( _pResource );
		if ( pOther ) AdvMapCameraSpline::Assign( *pOther );
	}
};

struct AdvMapDescription : public DbResource
{
	DBRESOURCE_METHODS( AdvMapDescription );
public:
	CTextRef title;
	LoadingBackgroundImages loadingBackgroundImages;
	StatisticBackgoundImages statisticBackgroundImages;
	Ptr< AdvMapModeDescription > modeVisualDescription;
	Ptr< Texture > image;
	EMapType mapType;
	Ptr< AdvMapDescription > mapWithBots;
	PartyMode PartyMode;
	bool acceptNeeded;
	CTextRef description;
	Ptr< AdvMap > map;
	Ptr< AdvMapHeroesOverride > heroesOverride;
	Ptr< MapMMakingSettings > matchmakingSettings;
	int teamSize;
	int minTeamSize;
	int maxUncompleteTeamSize;
	bool productionMode;
	Ptr< AdvMapSettings > mapSettings;
	Ptr< ModeRollSettings > rollSettings;
	Ptr< ModeRollSettings > guardRollSettings;
	Ptr< ScoringTable > scoringTable;
	float victoryPoint;
	string FWODGroup;
	Ptr< FWODVisualInfo > FirstWinVisualInfo;
	bool canUseSkins;
	bool botsUseSkins;
	int minimalGuildFightTeam;
	Ptr< GameSvcSettings > gameSvcSettings;
	int playSameTeamTimeOut;
	bool AvailableForLeavers;
	bool PlusPointForLeave;
	bool MinusPointsPerFullGame;

	AdvMapDescription();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapDescription& operator = ( const AdvMapDescription &_advMapDescription ) { Assign( _advMapDescription ); return *this; }
	AdvMapDescription( const AdvMapDescription &_advMapDescription ) { Assign( _advMapDescription ); }
	virtual void Assign( const AdvMapDescription &_advMapDescription );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapDescription * pOther = dynamic_cast< const AdvMapDescription * > ( _pResource );
		if ( pOther ) AdvMapDescription::Assign( *pOther );
	}
};

struct AdvMapHeroesOverride : public DbResource
{
	DBRESOURCE_METHODS( AdvMapHeroesOverride );
public:
	Ptr< AdvMapHeroesOverrideData > singlePlayerMale;
	Ptr< AdvMapHeroesOverrideData > singlePlayerFemale;
	bool shuffleHeroesInTeam;

	AdvMapHeroesOverride();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapHeroesOverride& operator = ( const AdvMapHeroesOverride &_advMapHeroesOverride ) { Assign( _advMapHeroesOverride ); return *this; }
	AdvMapHeroesOverride( const AdvMapHeroesOverride &_advMapHeroesOverride ) { Assign( _advMapHeroesOverride ); }
	virtual void Assign( const AdvMapHeroesOverride &_advMapHeroesOverride );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapHeroesOverride * pOther = dynamic_cast< const AdvMapHeroesOverride * > ( _pResource );
		if ( pOther ) AdvMapHeroesOverride::Assign( *pOther );
	}
};

struct AdvMapHeroesOverrideData : public DbResource
{
	DBRESOURCE_METHODS( AdvMapHeroesOverrideData );
public:
	AdvMapPlayerData ownHero;
	vector< AdvMapPlayerData > allies;
	vector< AdvMapPlayerData > enemies;

	AdvMapHeroesOverrideData();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapHeroesOverrideData& operator = ( const AdvMapHeroesOverrideData &_advMapHeroesOverrideData ) { Assign( _advMapHeroesOverrideData ); return *this; }
	AdvMapHeroesOverrideData( const AdvMapHeroesOverrideData &_advMapHeroesOverrideData ) { Assign( _advMapHeroesOverrideData ); }
	virtual void Assign( const AdvMapHeroesOverrideData &_advMapHeroesOverrideData );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapHeroesOverrideData * pOther = dynamic_cast< const AdvMapHeroesOverrideData * > ( _pResource );
		if ( pOther ) AdvMapHeroesOverrideData::Assign( *pOther );
	}
};

struct AdvMapSettings : public DbResource
{
	DBRESOURCE_METHODS( AdvMapSettings );
public:
	int battleStartDelay;
	int towersVulnerabilityDelay;
	BattleStartAnnouncementParams customBattleStartAnnouncement;
	bool useCustomBattleStartAnnouncement;
	bool showAllHeroes;
	float force;
	float minRequiredHeroForce;
	float maxRequiredHeroForce;
	bool fullPartyOnly;
	Ptr< DictionaryPreloadingResources > dictionary;
	PrimeSettings primeSettings;
	Ptr< DialogsCollection > dialogsCollection;
	Ptr< HintsCollection > hintsCollection;
	Ptr< SessionQuestsCollection > questsCollection;
	float trainingForceCoeff;
	string scriptFileName;
	Ptr< HeroRespawnParams > heroRespawnParams;
	vector< TriggerMarkerBinding > triggerMarkerBinding;
	Ptr< CreepAnnounceList > creepAnnounceList;
	Ptr< VotingForSurrenderPerMission > votingForSurrender;
	Ptr< AdventureTooltipParams > overrideTooltipParams;
	Ptr< DBMinimap > overrideMinimapParams;
	Ptr< Talent > overridePortalTalent;
	Ptr< GlyphManagerParams > overrideGlyphSettings;
	Ptr< BotsSettings > overrideBotsSettings;
	bool enableAnnouncements;
	bool enablePortalTalent;
	bool enableAllScriptFunctions;
	bool enableStatistics;
	int creepLevelCap;
	int emblemHeroNeeds;

	AdvMapSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapSettings& operator = ( const AdvMapSettings &_advMapSettings ) { Assign( _advMapSettings ); return *this; }
	AdvMapSettings( const AdvMapSettings &_advMapSettings ) { Assign( _advMapSettings ); }
	virtual void Assign( const AdvMapSettings &_advMapSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapSettings * pOther = dynamic_cast< const AdvMapSettings * > ( _pResource );
		if ( pOther ) AdvMapSettings::Assign( *pOther );
	}
};

struct AdvMapWaterZone : public GameObject
{
	DBRESOURCE_METHODS( AdvMapWaterZone );
public:
	enum { typeId = 0x146B6280 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)AdvMapWaterZone::typeId; }
	FlatSplineDesc area;

	AdvMapWaterZone();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	AdvMapWaterZone& operator = ( const AdvMapWaterZone &_advMapWaterZone ) { Assign( _advMapWaterZone ); return *this; }
	AdvMapWaterZone( const AdvMapWaterZone &_advMapWaterZone ) { Assign( _advMapWaterZone ); }
	virtual void Assign( const AdvMapWaterZone &_advMapWaterZone );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const AdvMapWaterZone * pOther = dynamic_cast< const AdvMapWaterZone * > ( _pResource );
		if ( pOther ) AdvMapWaterZone::Assign( *pOther );
	}
};

struct CreepAnnounceList : public DbResource
{
	DBRESOURCE_METHODS( CreepAnnounceList );
public:
	vector< CreepAnnounce > list;

	CreepAnnounceList();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	CreepAnnounceList& operator = ( const CreepAnnounceList &_creepAnnounceList ) { Assign( _creepAnnounceList ); return *this; }
	CreepAnnounceList( const CreepAnnounceList &_creepAnnounceList ) { Assign( _creepAnnounceList ); }
	virtual void Assign( const CreepAnnounceList &_creepAnnounceList );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const CreepAnnounceList * pOther = dynamic_cast< const CreepAnnounceList * > ( _pResource );
		if ( pOther ) CreepAnnounceList::Assign( *pOther );
	}
};

struct DbAdvMapCTESettings : public AdvMapSettings
{
	DBRESOURCE_METHODS( DbAdvMapCTESettings );
public:
	string altarName_A;
	string altarName_B;
	string dragonSpawnerName;
	string damageVariableName;
	vector< float > damageAnimationTable;

	DbAdvMapCTESettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DbAdvMapCTESettings& operator = ( const DbAdvMapCTESettings &_dbAdvMapCTESettings ) { Assign( _dbAdvMapCTESettings ); return *this; }
	DbAdvMapCTESettings( const DbAdvMapCTESettings &_dbAdvMapCTESettings ) { Assign( _dbAdvMapCTESettings ); }
	virtual void Assign( const DbAdvMapCTESettings &_dbAdvMapCTESettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DbAdvMapCTESettings * pOther = dynamic_cast< const DbAdvMapCTESettings * > ( _pResource );
		if ( pOther ) DbAdvMapCTESettings::Assign( *pOther );
	}
};

struct DictionaryPreloadingResources : public DbResource
{
	DBRESOURCE_METHODS( DictionaryPreloadingResources );
public:
	enum { typeId = 0xEF91FBC0 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)DictionaryPreloadingResources::typeId; }
	vector< ResourceDesc > resources;

	DictionaryPreloadingResources();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	DictionaryPreloadingResources& operator = ( const DictionaryPreloadingResources &_dictionaryPreloadingResources ) { Assign( _dictionaryPreloadingResources ); return *this; }
	DictionaryPreloadingResources( const DictionaryPreloadingResources &_dictionaryPreloadingResources ) { Assign( _dictionaryPreloadingResources ); }
	virtual void Assign( const DictionaryPreloadingResources &_dictionaryPreloadingResources );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const DictionaryPreloadingResources * pOther = dynamic_cast< const DictionaryPreloadingResources * > ( _pResource );
		if ( pOther ) DictionaryPreloadingResources::Assign( *pOther );
	}
};

struct FWODVisualInfo : public DbResource
{
	DBRESOURCE_METHODS( FWODVisualInfo );
public:
	Ptr< Texture > icon;
	Ptr< Texture > iconSmall;
	CTextRef tooltip;
	CTextRef sessionTooltip;

	FWODVisualInfo();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	FWODVisualInfo& operator = ( const FWODVisualInfo &_fWODVisualInfo ) { Assign( _fWODVisualInfo ); return *this; }
	FWODVisualInfo( const FWODVisualInfo &_fWODVisualInfo ) { Assign( _fWODVisualInfo ); }
	virtual void Assign( const FWODVisualInfo &_fWODVisualInfo );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const FWODVisualInfo * pOther = dynamic_cast< const FWODVisualInfo * > ( _pResource );
		if ( pOther ) FWODVisualInfo::Assign( *pOther );
	}
};

struct GameSvcSettings : public DbResource
{
	DBRESOURCE_METHODS( GameSvcSettings );
public:
	int afkMessageTimer;
	int afkDisconnectTimer;
	float timeScale;

	GameSvcSettings();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GameSvcSettings& operator = ( const GameSvcSettings &_gameSvcSettings ) { Assign( _gameSvcSettings ); return *this; }
	GameSvcSettings( const GameSvcSettings &_gameSvcSettings ) { Assign( _gameSvcSettings ); }
	virtual void Assign( const GameSvcSettings &_gameSvcSettings );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GameSvcSettings * pOther = dynamic_cast< const GameSvcSettings * > ( _pResource );
		if ( pOther ) GameSvcSettings::Assign( *pOther );
	}
};

struct GlyphManagerParams : public DbResource
{
	DBRESOURCE_METHODS( GlyphManagerParams );
public:
	GlyphSettings settings;
	Ptr< GlyphsDB > glyphs;

	GlyphManagerParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	GlyphManagerParams& operator = ( const GlyphManagerParams &_glyphManagerParams ) { Assign( _glyphManagerParams ); return *this; }
	GlyphManagerParams( const GlyphManagerParams &_glyphManagerParams ) { Assign( _glyphManagerParams ); }
	virtual void Assign( const GlyphManagerParams &_glyphManagerParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const GlyphManagerParams * pOther = dynamic_cast< const GlyphManagerParams * > ( _pResource );
		if ( pOther ) GlyphManagerParams::Assign( *pOther );
	}
};

struct HeroNaftaParams : public DbResource
{
	DBRESOURCE_METHODS( HeroNaftaParams );
public:
	ExecutableFloatString naftaForKill;
	ExecutableFloatString naftaForAssist;
	ExecutableFloatString naftaSpecForKill;
	ExecutableFloatString teamNaftaForPresence;

	HeroNaftaParams();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	HeroNaftaParams& operator = ( const HeroNaftaParams &_heroNaftaParams ) { Assign( _heroNaftaParams ); return *this; }
	HeroNaftaParams( const HeroNaftaParams &_heroNaftaParams ) { Assign( _heroNaftaParams ); }
	virtual void Assign( const HeroNaftaParams &_heroNaftaParams );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const HeroNaftaParams * pOther = dynamic_cast< const HeroNaftaParams * > ( _pResource );
		if ( pOther ) HeroNaftaParams::Assign( *pOther );
	}
};

struct ScriptPolygonArea : public GameObject
{
	DBRESOURCE_METHODS( ScriptPolygonArea );
public:
	enum { typeId = 0x9A9B7C40 };
	virtual const DWORD GetObjectTypeID() const { return (DWORD)ScriptPolygonArea::typeId; }
	vector< CVec2 > points;
	vector< ScriptPolygonAreaPolygon > polygons;

	ScriptPolygonArea();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	ScriptPolygonArea& operator = ( const ScriptPolygonArea &_scriptPolygonArea ) { Assign( _scriptPolygonArea ); return *this; }
	ScriptPolygonArea( const ScriptPolygonArea &_scriptPolygonArea ) { Assign( _scriptPolygonArea ); }
	virtual void Assign( const ScriptPolygonArea &_scriptPolygonArea );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const ScriptPolygonArea * pOther = dynamic_cast< const ScriptPolygonArea * > ( _pResource );
		if ( pOther ) ScriptPolygonArea::Assign( *pOther );
	}
};

}; // namespace NDb
