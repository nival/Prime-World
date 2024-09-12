// Automatically generated file, don't change it manually!
using System;
using System.Collections.Generic;
using System.ComponentModel;

using libdb;
using libdb.DB;
using libdb.IO;
using libdb.UndoRedo;
using libdb.Diagnostics;
using libdb.Animated;

namespace DBTypes
{
[Custom("Social")]
public enum BasicResourceType
{
	None = 0,
	Gold = 1,
	Silver = 2,
	Crystal = 3,
	RedCrystal = 4,
	Resource1 = 5,
	Resource2 = 6,
	Resource3 = 7,
	Population = 8,
	ClanWarPoints = 9,
	PlayerWarPoints = 10,
	Shard = 11,
};

public enum EAchievementType
{
	FirstBlood = 0,
	DoubleKill = 1,
	MassKill = 2,
	Duel = 3,
	Chase = 4,
	Avenge = 5,
	Dominate = 6,
	Vendetta = 7,
	CeremonialKill = 8,
	KillingSpree = 9,
	DoubleAssist = 10,
	MassAssist = 11,
	Saviour = 12,
	MasterControl = 13,
	AssistingSpree = 14,
	BorderGuard = 15,
	FirstAssault = 16,
	DemolishingSpree = 17,
	TowerDeny = 18,
	ClearWay = 19,
	BaseStrike = 20,
	Vandalism = 21,
	WarLord = 22,
	CleanUpCreeps = 23,
	DragonSlayer = 24,
	KittySlayer = 25,
	Legend = 26,
	ForestHunter = 27,
	Ascension = 28,
	SliverRite = 29,
	GoldRite = 30,
	FirstMinigameComplete = 31,
	SessionDuration = 32,
	BossSlayer = 33,
	InvalidAchivement = 34,
};

public enum EAdventureTooltipStretchMode
{
	None = 0,
	Dynamic = 1,
	Static = 2,
};

public enum EAnnouncementType
{
	PlayerKilled = 0,
	Achievment = 1,
	TowerDestroyed = 2,
	SpawnSuperCreeps = 3,
	PlayerLeft = 4,
	PlayerReconnected = 5,
	QuestRecieved = 6,
	QuestComplete = 7,
	EggAnnouncement = 8,
	SuperSiegeSpawned = 9,
	CustomAnnouncement = 10,
};

public enum EBossSlayerAchievMode
{
	OnlyForKiller = 0,
	ForKillerAndAssister = 1,
	ForAllTeammates = 2,
};

[Custom("Social")]
public enum EChatChannel
{
	Global = 0,
	MyTeam = 1,
	BothTeams = 2,
	System = 3,
	Achievments = 4,
	Private = 5,
	Tambur = 6,
	Guild = 7,
	LookingForGroupe = 8,
	Administration = 9,
	SmartChat = 10,
};

[Custom("Social")]
public enum EClanWarsResourceType
{
	ClanRating = 0,
	PlayerRating = 1,
};

[Custom("Social")]
public enum EDerivativeStat
{
	LifeRegenTotal = 0,
	EnergyRegenTotal = 1,
	DamageMin = 2,
	DamageMax = 3,
	DexterityDamageMult = 4,
	MoveSpeedMpS = 5,
	CritChance = 6,
	AttacksPerSecond = 7,
	BodyDefence = 8,
	SpiritDefence = 9,
	PenetrationFromAttackSpeed = 10,
	PenetrationFromDexterity = 11,
	PenetrationTotal = 12,
};

public enum EErrorMessageType
{
	NotEnoughPrimeToBuy = 0,
	NotEnoughManaForAbility = 1,
	AbilityOnCooldown = 2,
	WrongTarget = 3,
	InvulnerableTarget = 4,
	FlagpoleProtectedByTower = 5,
	FlagpoleProtectedByNext = 6,
	FlagpoleTooFar = 7,
	FlagpoleCurrentlyRising = 8,
	MinigameBusy = 9,
	MinigameProtectedByTowers = 10,
	WaitingForTarget = 11,
	OutOfInventory = 12,
	MinigameNotReady = 13,
	MinigameDisabled = 14,
	NotEnoughLifeForAbility = 15,
	PingRestricted = 16,
	SmartChatRestricted = 17,
	ReplayEnded = 18,
};

[Custom("DBServer")]
public enum EFaction
{
	Neutral = 0,
	Freeze = 1,
	Burn = 2,
};

[Flags]
public enum EFactionFlags
{
	FactionFreeze = 1,
	FactionBurn = 2,
	Neutral = 4,
	Self = 8,
	Opposite = 16,
};

public enum EFlyOffAlign
{
	Left = 0,
	Center = 1,
	Right = 2,
};

public enum EFormatType
{
	Integer = 0,
	OneDigit = 1,
	TwoDigits = 2,
	Percent = 3,
	OneDigitPercent = 4,
};

public enum EHeroTitle
{
	BestKiller = 0,
	BestAssister = 1,
	TopCreepKills = 2,
	TopTowerKills = 3,
	LeastDeaths = 4,
	TopNafta = 5,
	Painter_mg2 = 6,
	Dedicated_mg2 = 7,
	Merciless = 8,
	Wanderer = 9,
	Teleporter = 10,
	Stay_at_home = 11,
	TopConsumableUser = 12,
	LeastConsumableUser = 13,
	Ascetic = 14,
	TopKillStreaker = 15,
	Shinigami = 16,
	Adventurer = 17,
	TopTowerDenier = 18,
	TopNeutralKiller = 19,
	TopCeremonialKiller = 20,
	TopOneHeroKiller = 21,
	Avenger = 22,
	LastHitToMainBuilding = 23,
	TopIdleTime = 24,
	Huntsman = 25,
	DragonSlayer = 26,
	Legend = 27,
	Kamikaze = 28,
	Novice = 29,
	BossSlayer = 30,
};

public enum EMessage
{
	SIMPLE_MESSAGE = 0,
	LINEAR_FEAT_MESSAGE = 1,
	ONLY_FOR_PRIESTESS_MESSAGE = 2,
};

public enum EMinimapIcons
{
	Default = 0,
	MainBuildingA = 1,
	MainBuildingB = 2,
	ShopA = 3,
	ShopB = 4,
	ShopN = 5,
	QuarterA = 6,
	QuarterB = 7,
	TowerA = 8,
	TowerB = 9,
	NeutralsWeak = 10,
	NeutralsStrong = 11,
	NeutralsBoss = 12,
	Minigame = 13,
	FountainA = 14,
	FountainB = 15,
	Flagpole = 16,
	AltarA = 17,
	AltarB = 18,
	Egg = 19,
	AlchemistCircle = 20,
	Glyph = 21,
	BridgePassable = 22,
	BridgeImpassable = 23,
	PushButton = 24,
	None = 25,
};

public enum EPathMarker
{
	Green = 0,
	Red = 1,
};

public enum EPlayerID
{
	None = 0,
	Player_1 = 1,
	Player_2 = 2,
	Player_3 = 3,
	Player_4 = 4,
	Player_5 = 5,
	Player_6 = 6,
	Player_7 = 7,
	Player_8 = 8,
	Player_9 = 9,
	Player_10 = 10,
};

public enum ERecipients
{
	EVENT_PARTICIPANTS = 0,
	EVENT_MAKER_TEAM = 1,
	EVENT_MAKER_OPPOSITE_TEAM = 2,
	ALL_PLAYERS = 3,
	ALL_PLAYERS_WITHOUT_PRIESTESS = 4,
	PLAYER_ONLY = 5,
	USE_FROM_PARENT = 6,
};

[Custom("Social")]
public enum EResourceType
{
	Silver = 0,
	Crystal = 1,
	Resource1 = 2,
	Resource2 = 3,
	Resource3 = 4,
	RedCrystal = 5,
	Shard = 6,
};

public enum ERoute
{
	Top = 0,
	Center = 1,
	Bottom = 2,
	Tree = 3,
	Unassigned = 4,
};

public enum EScoreType
{
	HeroKillCount = 0,
	DeathCount = 1,
	AssistCount = 2,
	Score = 3,
	TotalNafta = 4,
	AchievmentCount = 5,
	TowersDestroyed = 6,
	TowersDenied = 7,
	FlagsRaised = 8,
	FlagsDestroyed = 9,
	MinigameLevelsWon = 10,
	CreepsKilled = 11,
	NeutralCreepsCount = 12,
	TimeInDeath = 13,
	HeleadAmount = 14,
	SexHelp = 15,
	DamageDealed = 16,
	DamageRecieved = 17,
	DanageHeroDealed = 18,
	DanageHeroRecieved = 19,
	MeterialDamageDealed = 20,
	MeterialDamageRecieved = 21,
	EnergyDamageDealed = 22,
	EnergyDamageRecieved = 23,
};

public enum ESign
{
	NONE = 0,
	SEND_MESSAGE_TO_CHAT = 1,
	SEND_MESSAGE_TO_STATUS_LINE = 2,
	PLAY_SOUND = 3,
	FLYOFF_TEXT = 4,
	ANNOUNCEMENT = 5,
};

[Custom("DBServer", "Social")]
public enum EStat
{
	Life = 0,
	Energy = 1,
	Range = 2,
	MoveSpeed = 3,
	AttackSpeed = 4,
	CriticalChance = 5,
	CriticalMultiplier = 6,
	LifeDrain = 7,
	EnergyDrain = 8,
	Evasion = 9,
	LifeRegeneration = 10,
	LifeRegenerationAbsolute = 11,
	EnergyRegeneration = 12,
	EnergyRegenerationAbsolute = 13,
	VisibilityRange = 14,
	Strength = 15,
	Intellect = 16,
	Dexterity = 17,
	BaseAttack = 18,
	Stamina = 19,
	Will = 20,
	VirtualStat = 21,
	CritChanceBonus = 22,
	EnergyDamageDecrease = 23,
	MaterialDamageDecrease = 24,
	MissChance = 25,
	Level = 26,
	NaftaForKill = 27,
	NaftaForAssist = 28,
	NaftaSpecForKill = 29,
	TeamNaftaForKill = 30,
	TeamNaftaForPresence = 31,
};

public enum EStatOwner
{
	None = 0,
	Creature = 1,
	EnemyCreature = 2,
	EnemyHero = 3,
	Hero = 4,
	Player = 5,
};

public enum ETerrainType
{
	Plains = 0,
	Swamp = 1,
	Desert = 2,
	Rock = 3,
	Water = 4,
	Road = 5,
};

public enum EVisualStyle
{
	Always = 0,
	Changed = 1,
	DontShow = 2,
};

[Custom("Social")]
public enum GuildShopCategoryType
{
	ClanBufs = 0,
	PlayerBufs = 1,
	SkinsAndFlags = 2,
	ProductionBonus = 3,
	Talents = 4,
};

[Custom("Social")]
public enum PhraseTerminateEvent
{
	PressKey = 0,
	Time = 1,
	TimeAndKey = 2,
};

[Custom("Social")]
public enum PortretOrientation
{
	Left = 0,
	Right = 1,
};

public class AbuseSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AbuseSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _cooldownTime;
	private UndoRedo<int> _maxUsagesPerPeriod;
	private UndoRedo<float> _period;
	private UndoRedo<int> _maxUsagesPerRestrictedPeriod;
	private UndoRedo<float> _restrictedPeriod;
	private UndoRedo<bool> _refreshRestrictedPeriod;

	[Description( "Длительность ограничения (кулдаун) (сек)" )]
	public float cooldownTime { get { return _cooldownTime.Get(); } set { _cooldownTime.Set( value ); } }

	[Description( "Разрешённое кол-во действий за промежуток времени в обычном режиме" )]
	public int maxUsagesPerPeriod { get { return _maxUsagesPerPeriod.Get(); } set { _maxUsagesPerPeriod.Set( value ); } }

	[Description( "Промежуток в обычном режиме(сек)" )]
	public float period { get { return _period.Get(); } set { _period.Set( value ); } }

	[Description( "Разрешённое кол-во действий за промежуток времени в режиме ограничения" )]
	public int maxUsagesPerRestrictedPeriod { get { return _maxUsagesPerRestrictedPeriod.Get(); } set { _maxUsagesPerRestrictedPeriod.Set( value ); } }

	[Description( "Промежуток в режиме ограничения (сек)" )]
	public float restrictedPeriod { get { return _restrictedPeriod.Get(); } set { _restrictedPeriod.Set( value ); } }

	[Description( "Обновлять таймер режима ограничения" )]
	public bool refreshRestrictedPeriod { get { return _refreshRestrictedPeriod.Get(); } set { _refreshRestrictedPeriod.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_cooldownTime = new UndoRedo<float>( owner, 15.0f );
		_maxUsagesPerPeriod = new UndoRedo<int>( owner, 6 );
		_period = new UndoRedo<float>( owner, 3.0f );
		_maxUsagesPerRestrictedPeriod = new UndoRedo<int>( owner, 1 );
		_restrictedPeriod = new UndoRedo<float>( owner, 3.0f );
		_refreshRestrictedPeriod = new UndoRedo<bool>( owner, true );
		_cooldownTime.Changed += FireChangedEvent;
		_maxUsagesPerPeriod.Changed += FireChangedEvent;
		_period.Changed += FireChangedEvent;
		_maxUsagesPerRestrictedPeriod.Changed += FireChangedEvent;
		_restrictedPeriod.Changed += FireChangedEvent;
		_refreshRestrictedPeriod.Changed += FireChangedEvent;
	}

	public AbuseSettings()
	{
		Initialize( GetOwner() );
	}

	public AbuseSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AbuseSettings( DBResource owner, AbuseSettings source )
		: this(owner, source, true){}

	protected AbuseSettings( DBResource owner, AbuseSettings source, bool fireEvent )
	{
		_cooldownTime = new UndoRedo<float>( owner, source.cooldownTime );
		_maxUsagesPerPeriod = new UndoRedo<int>( owner, source.maxUsagesPerPeriod );
		_period = new UndoRedo<float>( owner, source.period );
		_maxUsagesPerRestrictedPeriod = new UndoRedo<int>( owner, source.maxUsagesPerRestrictedPeriod );
		_restrictedPeriod = new UndoRedo<float>( owner, source.restrictedPeriod );
		_refreshRestrictedPeriod = new UndoRedo<bool>( owner, source.refreshRestrictedPeriod );
		_cooldownTime.Changed += FireChangedEvent;
		_maxUsagesPerPeriod.Changed += FireChangedEvent;
		_period.Changed += FireChangedEvent;
		_maxUsagesPerRestrictedPeriod.Changed += FireChangedEvent;
		_restrictedPeriod.Changed += FireChangedEvent;
		_refreshRestrictedPeriod.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AbuseSettings source = _source as AbuseSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AbuseSettings" );
		cooldownTime = source.cooldownTime;
		maxUsagesPerPeriod = source.maxUsagesPerPeriod;
		period = source.period;
		maxUsagesPerRestrictedPeriod = source.maxUsagesPerRestrictedPeriod;
		restrictedPeriod = source.restrictedPeriod;
		refreshRestrictedPeriod = source.refreshRestrictedPeriod;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AbuseSettings newParent = _newParent as AbuseSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_cooldownTime.SetParent( newParent == null ? null : newParent._cooldownTime );
		_maxUsagesPerPeriod.SetParent( newParent == null ? null : newParent._maxUsagesPerPeriod );
		_period.SetParent( newParent == null ? null : newParent._period );
		_maxUsagesPerRestrictedPeriod.SetParent( newParent == null ? null : newParent._maxUsagesPerRestrictedPeriod );
		_restrictedPeriod.SetParent( newParent == null ? null : newParent._restrictedPeriod );
		_refreshRestrictedPeriod.SetParent( newParent == null ? null : newParent._refreshRestrictedPeriod );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_cooldownTime.Reset();
		_maxUsagesPerPeriod.Reset();
		_period.Reset();
		_maxUsagesPerRestrictedPeriod.Reset();
		_restrictedPeriod.Reset();
		_refreshRestrictedPeriod.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_cooldownTime.IsDerivedFromParent()
			&& _maxUsagesPerPeriod.IsDerivedFromParent()
			&& _period.IsDerivedFromParent()
			&& _maxUsagesPerRestrictedPeriod.IsDerivedFromParent()
			&& _restrictedPeriod.IsDerivedFromParent()
			&& _refreshRestrictedPeriod.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "cooldownTime" )
			_cooldownTime.Reset();
		else if ( fieldName == "maxUsagesPerPeriod" )
			_maxUsagesPerPeriod.Reset();
		else if ( fieldName == "period" )
			_period.Reset();
		else if ( fieldName == "maxUsagesPerRestrictedPeriod" )
			_maxUsagesPerRestrictedPeriod.Reset();
		else if ( fieldName == "restrictedPeriod" )
			_restrictedPeriod.Reset();
		else if ( fieldName == "refreshRestrictedPeriod" )
			_refreshRestrictedPeriod.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "cooldownTime" )
			return _cooldownTime.IsDerivedFromParent();
		if ( fieldName == "maxUsagesPerPeriod" )
			return _maxUsagesPerPeriod.IsDerivedFromParent();
		if ( fieldName == "period" )
			return _period.IsDerivedFromParent();
		if ( fieldName == "maxUsagesPerRestrictedPeriod" )
			return _maxUsagesPerRestrictedPeriod.IsDerivedFromParent();
		if ( fieldName == "restrictedPeriod" )
			return _restrictedPeriod.IsDerivedFromParent();
		if ( fieldName == "refreshRestrictedPeriod" )
			return _refreshRestrictedPeriod.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class AchievBossSlayerData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AchievBossSlayerData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Creature> _boss;
	private TextRef _name;
	private UndoRedo<int> _perAchievementScore;
	private UndoRedo<int> _limit;
	private TextRef _tooltip;
	private UndoRedoDBPtr<Texture> _image;
	private UndoRedoDBPtr<UIEvent> _evUI;
	private UndoRedo<EBossSlayerAchievMode> _mode;

	public DBPtr<Creature> boss { get { return _boss.Get(); } set { _boss.Set( value ); } }

	[Description( "Achievement name" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Description( "Amount of score per one achievement" )]
	public int perAchievementScore { get { return _perAchievementScore.Get(); } set { _perAchievementScore.Set( value ); } }

	[Description( "Maximum achievement scores" )]
	public int limit { get { return _limit.Get(); } set { _limit.Set( value ); } }

	[Description( "Tooltip text for final statistics" )]
	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Description( "Icon image" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	[Description( "UI Event" )]
	public DBPtr<UIEvent> evUI { get { return _evUI.Get(); } set { _evUI.Set( value ); } }

	public EBossSlayerAchievMode mode { get { return _mode.Get(); } set { _mode.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_boss = new UndoRedoDBPtr<Creature>( owner );
		_name = new TextRef( owner, new TextRef() );
		_perAchievementScore = new UndoRedo<int>( owner, 0 );
		_limit = new UndoRedo<int>( owner, 0 );
		_tooltip = new TextRef( owner, new TextRef() );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_evUI = new UndoRedoDBPtr<UIEvent>( owner );
		_mode = new UndoRedo<EBossSlayerAchievMode>( owner, EBossSlayerAchievMode.OnlyForKiller );
		_boss.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_perAchievementScore.Changed += FireChangedEvent;
		_limit.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_evUI.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
	}

	public AchievBossSlayerData()
	{
		Initialize( GetOwner() );
	}

	public AchievBossSlayerData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AchievBossSlayerData( DBResource owner, AchievBossSlayerData source )
		: this(owner, source, true){}

	protected AchievBossSlayerData( DBResource owner, AchievBossSlayerData source, bool fireEvent )
	{
		_boss = new UndoRedoDBPtr<Creature>( owner, source.boss );
		_name = new TextRef( owner, source.name );
		_perAchievementScore = new UndoRedo<int>( owner, source.perAchievementScore );
		_limit = new UndoRedo<int>( owner, source.limit );
		_tooltip = new TextRef( owner, source.tooltip );
		_image = new UndoRedoDBPtr<Texture>( owner, source.image );
		_evUI = new UndoRedoDBPtr<UIEvent>( owner, source.evUI );
		_mode = new UndoRedo<EBossSlayerAchievMode>( owner, source.mode );
		_boss.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_perAchievementScore.Changed += FireChangedEvent;
		_limit.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_evUI.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AchievBossSlayerData source = _source as AchievBossSlayerData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievBossSlayerData" );
		boss = source.boss;
		name = source.name;
		perAchievementScore = source.perAchievementScore;
		limit = source.limit;
		tooltip = source.tooltip;
		image = source.image;
		evUI = source.evUI;
		mode = source.mode;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AchievBossSlayerData newParent = _newParent as AchievBossSlayerData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_boss.SetParent( newParent == null ? null : newParent._boss );
		_name.SetParent( newParent == null ? null : newParent._name );
		_perAchievementScore.SetParent( newParent == null ? null : newParent._perAchievementScore );
		_limit.SetParent( newParent == null ? null : newParent._limit );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_image.SetParent( newParent == null ? null : newParent._image );
		_evUI.SetParent( newParent == null ? null : newParent._evUI );
		_mode.SetParent( newParent == null ? null : newParent._mode );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_boss.Reset();
		_name.Reset();
		_perAchievementScore.Reset();
		_limit.Reset();
		_tooltip.Reset();
		_image.Reset();
		_evUI.Reset();
		_mode.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_boss.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _perAchievementScore.IsDerivedFromParent()
			&& _limit.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _evUI.IsDerivedFromParent()
			&& _mode.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "boss" )
			_boss.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "perAchievementScore" )
			_perAchievementScore.Reset();
		else if ( fieldName == "limit" )
			_limit.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "evUI" )
			_evUI.Reset();
		else if ( fieldName == "mode" )
			_mode.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "boss" )
			return _boss.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "perAchievementScore" )
			return _perAchievementScore.IsDerivedFromParent();
		if ( fieldName == "limit" )
			return _limit.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "evUI" )
			return _evUI.IsDerivedFromParent();
		if ( fieldName == "mode" )
			return _mode.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class AnnouncementDescription : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnnouncementDescription __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _textMessage;
	private UndoRedo<float> _lifeTime;

	public TextRef textMessage { get { return _textMessage; } set { _textMessage.Assign( value ); } }

	public float lifeTime { get { return _lifeTime.Get(); } set { _lifeTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_textMessage = new TextRef( owner, new TextRef() );
		_lifeTime = new UndoRedo<float>( owner, 3.0f );
		_textMessage.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
	}

	public AnnouncementDescription()
	{
		Initialize( GetOwner() );
	}

	public AnnouncementDescription( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnnouncementDescription( DBResource owner, AnnouncementDescription source )
		: this(owner, source, true){}

	protected AnnouncementDescription( DBResource owner, AnnouncementDescription source, bool fireEvent )
	{
		_textMessage = new TextRef( owner, source.textMessage );
		_lifeTime = new UndoRedo<float>( owner, source.lifeTime );
		_textMessage.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnnouncementDescription source = _source as AnnouncementDescription;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnnouncementDescription" );
		textMessage = source.textMessage;
		lifeTime = source.lifeTime;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnnouncementDescription newParent = _newParent as AnnouncementDescription;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_textMessage.SetParent( newParent == null ? null : newParent._textMessage );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_textMessage.Reset();
		_lifeTime.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_textMessage.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "textMessage" )
			_textMessage.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "textMessage" )
			return _textMessage.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class AttackType : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AttackType __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _statName;
	private TextRef _phisicalAttackName;
	private TextRef _energyAttackName;
	private TextRef _pureAttackName;

	public TextRef statName { get { return _statName; } set { _statName.Assign( value ); } }

	public TextRef phisicalAttackName { get { return _phisicalAttackName; } set { _phisicalAttackName.Assign( value ); } }

	public TextRef energyAttackName { get { return _energyAttackName; } set { _energyAttackName.Assign( value ); } }

	public TextRef pureAttackName { get { return _pureAttackName; } set { _pureAttackName.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_statName = new TextRef( owner, new TextRef() );
		_phisicalAttackName = new TextRef( owner, new TextRef() );
		_energyAttackName = new TextRef( owner, new TextRef() );
		_pureAttackName = new TextRef( owner, new TextRef() );
		_statName.Changed += FireChangedEvent;
		_phisicalAttackName.Changed += FireChangedEvent;
		_energyAttackName.Changed += FireChangedEvent;
		_pureAttackName.Changed += FireChangedEvent;
	}

	public AttackType()
	{
		Initialize( GetOwner() );
	}

	public AttackType( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AttackType( DBResource owner, AttackType source )
		: this(owner, source, true){}

	protected AttackType( DBResource owner, AttackType source, bool fireEvent )
	{
		_statName = new TextRef( owner, source.statName );
		_phisicalAttackName = new TextRef( owner, source.phisicalAttackName );
		_energyAttackName = new TextRef( owner, source.energyAttackName );
		_pureAttackName = new TextRef( owner, source.pureAttackName );
		_statName.Changed += FireChangedEvent;
		_phisicalAttackName.Changed += FireChangedEvent;
		_energyAttackName.Changed += FireChangedEvent;
		_pureAttackName.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AttackType source = _source as AttackType;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AttackType" );
		statName = source.statName;
		phisicalAttackName = source.phisicalAttackName;
		energyAttackName = source.energyAttackName;
		pureAttackName = source.pureAttackName;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AttackType newParent = _newParent as AttackType;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_statName.SetParent( newParent == null ? null : newParent._statName );
		_phisicalAttackName.SetParent( newParent == null ? null : newParent._phisicalAttackName );
		_energyAttackName.SetParent( newParent == null ? null : newParent._energyAttackName );
		_pureAttackName.SetParent( newParent == null ? null : newParent._pureAttackName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_statName.Reset();
		_phisicalAttackName.Reset();
		_energyAttackName.Reset();
		_pureAttackName.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_statName.IsDerivedFromParent()
			&& _phisicalAttackName.IsDerivedFromParent()
			&& _energyAttackName.IsDerivedFromParent()
			&& _pureAttackName.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "statName" )
			_statName.Reset();
		else if ( fieldName == "phisicalAttackName" )
			_phisicalAttackName.Reset();
		else if ( fieldName == "energyAttackName" )
			_energyAttackName.Reset();
		else if ( fieldName == "pureAttackName" )
			_pureAttackName.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "statName" )
			return _statName.IsDerivedFromParent();
		if ( fieldName == "phisicalAttackName" )
			return _phisicalAttackName.IsDerivedFromParent();
		if ( fieldName == "energyAttackName" )
			return _energyAttackName.IsDerivedFromParent();
		if ( fieldName == "pureAttackName" )
			return _pureAttackName.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class BattleStartAnnouncementParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BattleStartAnnouncementParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Texture> _imageBurn;
	private UndoRedoDBPtr<Texture> _imageFreeze;
	private TextRef _announcementText;
	private DBFMODEventDesc _battleStartSound;

	[Description( "image for elfs" )]
	public DBPtr<Texture> imageBurn { get { return _imageBurn.Get(); } set { _imageBurn.Set( value ); } }

	[Description( "image for humans" )]
	public DBPtr<Texture> imageFreeze { get { return _imageFreeze.Get(); } set { _imageFreeze.Set( value ); } }

	[Description( "announcement text" )]
	public TextRef announcementText { get { return _announcementText; } set { _announcementText.Assign( value ); } }

	[Description( "Sound on battle start (soldiers first spawn)" )]
	public DBFMODEventDesc battleStartSound { get { return _battleStartSound; } set { _battleStartSound.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_imageBurn = new UndoRedoDBPtr<Texture>( owner );
		_imageFreeze = new UndoRedoDBPtr<Texture>( owner );
		_announcementText = new TextRef( owner, new TextRef() );
		_battleStartSound = new DBFMODEventDesc( owner );
		_imageBurn.Changed += FireChangedEvent;
		_imageFreeze.Changed += FireChangedEvent;
		_announcementText.Changed += FireChangedEvent;
		_battleStartSound.Changed += FireChangedEvent;
	}

	public BattleStartAnnouncementParams()
	{
		Initialize( GetOwner() );
	}

	public BattleStartAnnouncementParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BattleStartAnnouncementParams( DBResource owner, BattleStartAnnouncementParams source )
		: this(owner, source, true){}

	protected BattleStartAnnouncementParams( DBResource owner, BattleStartAnnouncementParams source, bool fireEvent )
	{
		_imageBurn = new UndoRedoDBPtr<Texture>( owner, source.imageBurn );
		_imageFreeze = new UndoRedoDBPtr<Texture>( owner, source.imageFreeze );
		_announcementText = new TextRef( owner, source.announcementText );
		_battleStartSound = new DBFMODEventDesc( owner, source.battleStartSound );
		_imageBurn.Changed += FireChangedEvent;
		_imageFreeze.Changed += FireChangedEvent;
		_announcementText.Changed += FireChangedEvent;
		_battleStartSound.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BattleStartAnnouncementParams source = _source as BattleStartAnnouncementParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BattleStartAnnouncementParams" );
		imageBurn = source.imageBurn;
		imageFreeze = source.imageFreeze;
		announcementText = source.announcementText;
		battleStartSound = source.battleStartSound;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BattleStartAnnouncementParams newParent = _newParent as BattleStartAnnouncementParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_imageBurn.SetParent( newParent == null ? null : newParent._imageBurn );
		_imageFreeze.SetParent( newParent == null ? null : newParent._imageFreeze );
		_announcementText.SetParent( newParent == null ? null : newParent._announcementText );
		_battleStartSound.SetParent( newParent == null ? null : newParent._battleStartSound );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_imageBurn.Reset();
		_imageFreeze.Reset();
		_announcementText.Reset();
		_battleStartSound.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_imageBurn.IsDerivedFromParent()
			&& _imageFreeze.IsDerivedFromParent()
			&& _announcementText.IsDerivedFromParent()
			&& _battleStartSound.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "imageBurn" )
			_imageBurn.Reset();
		else if ( fieldName == "imageFreeze" )
			_imageFreeze.Reset();
		else if ( fieldName == "announcementText" )
			_announcementText.Reset();
		else if ( fieldName == "battleStartSound" )
			_battleStartSound.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "imageBurn" )
			return _imageBurn.IsDerivedFromParent();
		if ( fieldName == "imageFreeze" )
			return _imageFreeze.IsDerivedFromParent();
		if ( fieldName == "announcementText" )
			return _announcementText.IsDerivedFromParent();
		if ( fieldName == "battleStartSound" )
			return _battleStartSound.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("bindKey")]
public class HotkeyBind : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HotkeyBind __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _name;
	private UndoRedo<string> _bindKey;
	private UndoRedo<string> _dependentBindKey;
	private UndoRedo<float> _bindFactor;
	private UndoRedo<bool> _isHelperKey;
	private TextRef _tooltip;
	private UndoRedoDBPtr<BindCategory> _category;

	[Description( "Название бинда. показывается в настройках" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Description( "ключ бинда. Например cmd_attack" )]
	public string bindKey { get { return _bindKey.Get(); } set { _bindKey.Set( value ); } }

	[Description( "ключ зависимого бинда бинда. Будет записываться вместе с оновным. Например cmd_attack" )]
	public string dependentBindKey { get { return _dependentBindKey.Get(); } set { _dependentBindKey.Set( value ); } }

	[Description( "фактор бинда. например bind camera_forward +1.0 'W' и bind camera_forward -1.0 'DOWN'" )]
	public float bindFactor { get { return _bindFactor.Get(); } set { _bindFactor.Set( value ); } }

	[Description( "Вспомогательный ли это бинд. Нужен чтобы уметь вводить просто ALT для селфкаста. Подразумевает только 1 клавишу (но любую)" )]
	public bool isHelperKey { get { return _isHelperKey.Get(); } set { _isHelperKey.Set( value ); } }

	[Description( "Тултип бинда" )]
	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Description( "категория бинда" )]
	public DBPtr<BindCategory> category { get { return _category.Get(); } set { _category.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new TextRef( owner, new TextRef() );
		_bindKey = new UndoRedo<string>( owner, string.Empty );
		_dependentBindKey = new UndoRedo<string>( owner, string.Empty );
		_bindFactor = new UndoRedo<float>( owner, 0.0f );
		_isHelperKey = new UndoRedo<bool>( owner, false );
		_tooltip = new TextRef( owner, new TextRef() );
		_category = new UndoRedoDBPtr<BindCategory>( owner );
		_name.Changed += FireChangedEvent;
		_bindKey.Changed += FireChangedEvent;
		_dependentBindKey.Changed += FireChangedEvent;
		_bindFactor.Changed += FireChangedEvent;
		_isHelperKey.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_category.Changed += FireChangedEvent;
	}

	public HotkeyBind()
	{
		Initialize( GetOwner() );
	}

	public HotkeyBind( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HotkeyBind( DBResource owner, HotkeyBind source )
		: this(owner, source, true){}

	protected HotkeyBind( DBResource owner, HotkeyBind source, bool fireEvent )
	{
		_name = new TextRef( owner, source.name );
		_bindKey = new UndoRedo<string>( owner, source.bindKey );
		_dependentBindKey = new UndoRedo<string>( owner, source.dependentBindKey );
		_bindFactor = new UndoRedo<float>( owner, source.bindFactor );
		_isHelperKey = new UndoRedo<bool>( owner, source.isHelperKey );
		_tooltip = new TextRef( owner, source.tooltip );
		_category = new UndoRedoDBPtr<BindCategory>( owner, source.category );
		_name.Changed += FireChangedEvent;
		_bindKey.Changed += FireChangedEvent;
		_dependentBindKey.Changed += FireChangedEvent;
		_bindFactor.Changed += FireChangedEvent;
		_isHelperKey.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_category.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HotkeyBind source = _source as HotkeyBind;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HotkeyBind" );
		name = source.name;
		bindKey = source.bindKey;
		dependentBindKey = source.dependentBindKey;
		bindFactor = source.bindFactor;
		isHelperKey = source.isHelperKey;
		tooltip = source.tooltip;
		category = source.category;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HotkeyBind newParent = _newParent as HotkeyBind;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_bindKey.SetParent( newParent == null ? null : newParent._bindKey );
		_dependentBindKey.SetParent( newParent == null ? null : newParent._dependentBindKey );
		_bindFactor.SetParent( newParent == null ? null : newParent._bindFactor );
		_isHelperKey.SetParent( newParent == null ? null : newParent._isHelperKey );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_category.SetParent( newParent == null ? null : newParent._category );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_bindKey.Reset();
		_dependentBindKey.Reset();
		_bindFactor.Reset();
		_isHelperKey.Reset();
		_tooltip.Reset();
		_category.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _bindKey.IsDerivedFromParent()
			&& _dependentBindKey.IsDerivedFromParent()
			&& _bindFactor.IsDerivedFromParent()
			&& _isHelperKey.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _category.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "bindKey" )
			_bindKey.Reset();
		else if ( fieldName == "dependentBindKey" )
			_dependentBindKey.Reset();
		else if ( fieldName == "bindFactor" )
			_bindFactor.Reset();
		else if ( fieldName == "isHelperKey" )
			_isHelperKey.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "category" )
			_category.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "bindKey" )
			return _bindKey.IsDerivedFromParent();
		if ( fieldName == "dependentBindKey" )
			return _dependentBindKey.IsDerivedFromParent();
		if ( fieldName == "bindFactor" )
			return _bindFactor.IsDerivedFromParent();
		if ( fieldName == "isHelperKey" )
			return _isHelperKey.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "category" )
			return _category.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("name")]
public class CountryFlag : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CountryFlag __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _id;
	private UndoRedoDBPtr<Texture> _icon;
	private TextRef _name;
	private UndoRedo<string> _countryCode;
	private TextRef _tooltip;

	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	[Description( "Иконка" )]
	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Description( "Название флага" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Custom("DBServer", "Social")]
	[Description( "Аббревиатура страны (2 буквы)" )]
	public string countryCode { get { return _countryCode.Get(); } set { _countryCode.Set( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_id = new UndoRedo<string>( owner, string.Empty );
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_name = new TextRef( owner, new TextRef() );
		_countryCode = new UndoRedo<string>( owner, string.Empty );
		_tooltip = new TextRef( owner, new TextRef() );
		_id.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_countryCode.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
	}

	public CountryFlag()
	{
		Initialize( GetOwner() );
	}

	public CountryFlag( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CountryFlag( DBResource owner, CountryFlag source )
		: this(owner, source, true){}

	protected CountryFlag( DBResource owner, CountryFlag source, bool fireEvent )
	{
		_id = new UndoRedo<string>( owner, source.id );
		_icon = new UndoRedoDBPtr<Texture>( owner, source.icon );
		_name = new TextRef( owner, source.name );
		_countryCode = new UndoRedo<string>( owner, source.countryCode );
		_tooltip = new TextRef( owner, source.tooltip );
		_id.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_countryCode.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CountryFlag source = _source as CountryFlag;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CountryFlag" );
		id = source.id;
		icon = source.icon;
		name = source.name;
		countryCode = source.countryCode;
		tooltip = source.tooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CountryFlag newParent = _newParent as CountryFlag;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_id.SetParent( newParent == null ? null : newParent._id );
		_icon.SetParent( newParent == null ? null : newParent._icon );
		_name.SetParent( newParent == null ? null : newParent._name );
		_countryCode.SetParent( newParent == null ? null : newParent._countryCode );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_id.Reset();
		_icon.Reset();
		_name.Reset();
		_countryCode.Reset();
		_tooltip.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _icon.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _countryCode.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "countryCode" )
			_countryCode.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "countryCode" )
			return _countryCode.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class CharStatTooltips : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CharStatTooltips __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<TextRef> _baseStatTooltips;
	private UndoRedoAssignableList<TextRef> _derivativeStatTooltips;
	private UndoRedoAssignableList<TextRef> _heroesBuildingStatTooltips;

	[Category( "Tooltips for base stats (used in CharStat window)" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<TextRef> baseStatTooltips { get { return _baseStatTooltips; } set { _baseStatTooltips.Assign( value ); } }

	[Category( "Tooltips for derivative stats (used in CharStat window)" )]
	[EnumArray(typeof(EDerivativeStat))]
	public libdb.IChangeableList<TextRef> derivativeStatTooltips { get { return _derivativeStatTooltips; } set { _derivativeStatTooltips.Assign( value ); } }

	[Category( "Tooltips for base stats (used in HeroesBuilding window)" )]
	[EnumArray(typeof(EStat))]
	[NoCode]
	public libdb.IChangeableList<TextRef> heroesBuildingStatTooltips { get { return _heroesBuildingStatTooltips; } set { _heroesBuildingStatTooltips.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_baseStatTooltips = new UndoRedoAssignableList<TextRef>( owner, typeof( EStat ) );
		_derivativeStatTooltips = new UndoRedoAssignableList<TextRef>( owner, typeof( EDerivativeStat ) );
		_heroesBuildingStatTooltips = new UndoRedoAssignableList<TextRef>( owner, typeof( EStat ) );
		_baseStatTooltips.Changed += FireChangedEvent;
		_derivativeStatTooltips.Changed += FireChangedEvent;
		_heroesBuildingStatTooltips.Changed += FireChangedEvent;
	}

	public CharStatTooltips()
	{
		Initialize( GetOwner() );
	}

	public CharStatTooltips( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CharStatTooltips( DBResource owner, CharStatTooltips source )
		: this(owner, source, true){}

	protected CharStatTooltips( DBResource owner, CharStatTooltips source, bool fireEvent )
	{
		_baseStatTooltips = new UndoRedoAssignableList<TextRef>( owner, typeof( EStat ) );
		_baseStatTooltips.Assign( source.baseStatTooltips );
		_derivativeStatTooltips = new UndoRedoAssignableList<TextRef>( owner, typeof( EDerivativeStat ) );
		_derivativeStatTooltips.Assign( source.derivativeStatTooltips );
		_heroesBuildingStatTooltips = new UndoRedoAssignableList<TextRef>( owner, typeof( EStat ) );
		_heroesBuildingStatTooltips.Assign( source.heroesBuildingStatTooltips );
		_baseStatTooltips.Changed += FireChangedEvent;
		_derivativeStatTooltips.Changed += FireChangedEvent;
		_heroesBuildingStatTooltips.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CharStatTooltips source = _source as CharStatTooltips;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CharStatTooltips" );
		baseStatTooltips = source.baseStatTooltips;
		derivativeStatTooltips = source.derivativeStatTooltips;
		heroesBuildingStatTooltips = source.heroesBuildingStatTooltips;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CharStatTooltips newParent = _newParent as CharStatTooltips;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_baseStatTooltips.SetParent( newParent == null ? null : newParent._baseStatTooltips );
		_derivativeStatTooltips.SetParent( newParent == null ? null : newParent._derivativeStatTooltips );
		_heroesBuildingStatTooltips.SetParent( newParent == null ? null : newParent._heroesBuildingStatTooltips );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_baseStatTooltips.Reset();
		_derivativeStatTooltips.Reset();
		_heroesBuildingStatTooltips.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_baseStatTooltips.IsDerivedFromParent()
			&& _derivativeStatTooltips.IsDerivedFromParent()
			&& _heroesBuildingStatTooltips.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "baseStatTooltips" )
			_baseStatTooltips.Reset();
		else if ( fieldName == "derivativeStatTooltips" )
			_derivativeStatTooltips.Reset();
		else if ( fieldName == "heroesBuildingStatTooltips" )
			_heroesBuildingStatTooltips.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "baseStatTooltips" )
			return _baseStatTooltips.IsDerivedFromParent();
		if ( fieldName == "derivativeStatTooltips" )
			return _derivativeStatTooltips.IsDerivedFromParent();
		if ( fieldName == "heroesBuildingStatTooltips" )
			return _heroesBuildingStatTooltips.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ChatChannelDescription : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ChatChannelDescription __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _channelName;
	private Color _channelColor;
	private TextRef _castleChannelName;
	private Color _castleChannelColor;
	private UndoRedo<bool> _showChannelName;
	private UndoRedo<bool> _showPlayerName;
	private UndoRedo<string> _chatChannelIconA;
	private UndoRedo<string> _chatChannelIconB;
	private UndoRedo<bool> _showBlinkOnMessage;
	private UndoRedoAssignableList<TextRef> _shortcuts;
	private UndoRedo<bool> _clearMessagesOnLeave;
	private UndoRedo<bool> _spamInGlobalChannel;
	private UndoRedo<bool> _cooldownOnSpam;

	public TextRef channelName { get { return _channelName; } set { _channelName.Assign( value ); } }

	public Color channelColor { get { return _channelColor; } set { _channelColor.Assign( value ); } }

	public TextRef castleChannelName { get { return _castleChannelName; } set { _castleChannelName.Assign( value ); } }

	public Color castleChannelColor { get { return _castleChannelColor; } set { _castleChannelColor.Assign( value ); } }

	public bool showChannelName { get { return _showChannelName.Get(); } set { _showChannelName.Set( value ); } }

	public bool showPlayerName { get { return _showPlayerName.Get(); } set { _showPlayerName.Set( value ); } }

	[Description( "иконка для таба канала фракции А, если пустая, то таб не появится" )]
	public string chatChannelIconA { get { return _chatChannelIconA.Get(); } set { _chatChannelIconA.Set( value ); } }

	[Description( "иконка для таба канала фракции B, если пустая, то таб не появится" )]
	public string chatChannelIconB { get { return _chatChannelIconB.Get(); } set { _chatChannelIconB.Set( value ); } }

	[Description( "Если false, то приходящее сообщение не будет вызывать мигание таба" )]
	public bool showBlinkOnMessage { get { return _showBlinkOnMessage.Get(); } set { _showBlinkOnMessage.Set( value ); } }

	[Description( "shortcuts for channel" )]
	public libdb.IChangeableList<TextRef> shortcuts { get { return _shortcuts; } set { _shortcuts.Assign( value ); } }

	[Description( "Флаг для чистки сообщений, если мы выходим из канала" )]
	public bool clearMessagesOnLeave { get { return _clearMessagesOnLeave.Get(); } set { _clearMessagesOnLeave.Set( value ); } }

	[Description( "Флаг для спама этого канала в глобал" )]
	public bool spamInGlobalChannel { get { return _spamInGlobalChannel.Get(); } set { _spamInGlobalChannel.Set( value ); } }

	[Description( "Флаг для появления кулдауна на спам в этот канал" )]
	public bool cooldownOnSpam { get { return _cooldownOnSpam.Get(); } set { _cooldownOnSpam.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_channelName = new TextRef( owner, new TextRef() );
		_channelColor = new Color( owner );
		_castleChannelName = new TextRef( owner, new TextRef() );
		_castleChannelColor = new Color( owner );
		_showChannelName = new UndoRedo<bool>( owner, false );
		_showPlayerName = new UndoRedo<bool>( owner, false );
		_chatChannelIconA = new UndoRedo<string>( owner, string.Empty );
		_chatChannelIconB = new UndoRedo<string>( owner, string.Empty );
		_showBlinkOnMessage = new UndoRedo<bool>( owner, true );
		_shortcuts = new UndoRedoAssignableList<TextRef>( owner );
		_clearMessagesOnLeave = new UndoRedo<bool>( owner, true );
		_spamInGlobalChannel = new UndoRedo<bool>( owner, true );
		_cooldownOnSpam = new UndoRedo<bool>( owner, false );
		_channelName.Changed += FireChangedEvent;
		_channelColor.Changed += FireChangedEvent;
		_castleChannelName.Changed += FireChangedEvent;
		_castleChannelColor.Changed += FireChangedEvent;
		_showChannelName.Changed += FireChangedEvent;
		_showPlayerName.Changed += FireChangedEvent;
		_chatChannelIconA.Changed += FireChangedEvent;
		_chatChannelIconB.Changed += FireChangedEvent;
		_showBlinkOnMessage.Changed += FireChangedEvent;
		_shortcuts.Changed += FireChangedEvent;
		_clearMessagesOnLeave.Changed += FireChangedEvent;
		_spamInGlobalChannel.Changed += FireChangedEvent;
		_cooldownOnSpam.Changed += FireChangedEvent;
	}

	public ChatChannelDescription()
	{
		Initialize( GetOwner() );
	}

	public ChatChannelDescription( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ChatChannelDescription( DBResource owner, ChatChannelDescription source )
		: this(owner, source, true){}

	protected ChatChannelDescription( DBResource owner, ChatChannelDescription source, bool fireEvent )
	{
		_channelName = new TextRef( owner, source.channelName );
		_channelColor = new Color( owner, source.channelColor );
		_castleChannelName = new TextRef( owner, source.castleChannelName );
		_castleChannelColor = new Color( owner, source.castleChannelColor );
		_showChannelName = new UndoRedo<bool>( owner, source.showChannelName );
		_showPlayerName = new UndoRedo<bool>( owner, source.showPlayerName );
		_chatChannelIconA = new UndoRedo<string>( owner, source.chatChannelIconA );
		_chatChannelIconB = new UndoRedo<string>( owner, source.chatChannelIconB );
		_showBlinkOnMessage = new UndoRedo<bool>( owner, source.showBlinkOnMessage );
		_shortcuts = new UndoRedoAssignableList<TextRef>( owner );
		_shortcuts.Assign( source.shortcuts );
		_clearMessagesOnLeave = new UndoRedo<bool>( owner, source.clearMessagesOnLeave );
		_spamInGlobalChannel = new UndoRedo<bool>( owner, source.spamInGlobalChannel );
		_cooldownOnSpam = new UndoRedo<bool>( owner, source.cooldownOnSpam );
		_channelName.Changed += FireChangedEvent;
		_channelColor.Changed += FireChangedEvent;
		_castleChannelName.Changed += FireChangedEvent;
		_castleChannelColor.Changed += FireChangedEvent;
		_showChannelName.Changed += FireChangedEvent;
		_showPlayerName.Changed += FireChangedEvent;
		_chatChannelIconA.Changed += FireChangedEvent;
		_chatChannelIconB.Changed += FireChangedEvent;
		_showBlinkOnMessage.Changed += FireChangedEvent;
		_shortcuts.Changed += FireChangedEvent;
		_clearMessagesOnLeave.Changed += FireChangedEvent;
		_spamInGlobalChannel.Changed += FireChangedEvent;
		_cooldownOnSpam.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ChatChannelDescription source = _source as ChatChannelDescription;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChatChannelDescription" );
		channelName = source.channelName;
		channelColor = source.channelColor;
		castleChannelName = source.castleChannelName;
		castleChannelColor = source.castleChannelColor;
		showChannelName = source.showChannelName;
		showPlayerName = source.showPlayerName;
		chatChannelIconA = source.chatChannelIconA;
		chatChannelIconB = source.chatChannelIconB;
		showBlinkOnMessage = source.showBlinkOnMessage;
		shortcuts = source.shortcuts;
		clearMessagesOnLeave = source.clearMessagesOnLeave;
		spamInGlobalChannel = source.spamInGlobalChannel;
		cooldownOnSpam = source.cooldownOnSpam;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ChatChannelDescription newParent = _newParent as ChatChannelDescription;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_channelName.SetParent( newParent == null ? null : newParent._channelName );
		_channelColor.SetParent( newParent == null ? null : newParent._channelColor );
		_castleChannelName.SetParent( newParent == null ? null : newParent._castleChannelName );
		_castleChannelColor.SetParent( newParent == null ? null : newParent._castleChannelColor );
		_showChannelName.SetParent( newParent == null ? null : newParent._showChannelName );
		_showPlayerName.SetParent( newParent == null ? null : newParent._showPlayerName );
		_chatChannelIconA.SetParent( newParent == null ? null : newParent._chatChannelIconA );
		_chatChannelIconB.SetParent( newParent == null ? null : newParent._chatChannelIconB );
		_showBlinkOnMessage.SetParent( newParent == null ? null : newParent._showBlinkOnMessage );
		_shortcuts.SetParent( newParent == null ? null : newParent._shortcuts );
		_clearMessagesOnLeave.SetParent( newParent == null ? null : newParent._clearMessagesOnLeave );
		_spamInGlobalChannel.SetParent( newParent == null ? null : newParent._spamInGlobalChannel );
		_cooldownOnSpam.SetParent( newParent == null ? null : newParent._cooldownOnSpam );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_channelName.Reset();
		_channelColor.Reset();
		_castleChannelName.Reset();
		_castleChannelColor.Reset();
		_showChannelName.Reset();
		_showPlayerName.Reset();
		_chatChannelIconA.Reset();
		_chatChannelIconB.Reset();
		_showBlinkOnMessage.Reset();
		_shortcuts.Reset();
		_clearMessagesOnLeave.Reset();
		_spamInGlobalChannel.Reset();
		_cooldownOnSpam.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_channelName.IsDerivedFromParent()
			&& _channelColor.IsDerivedFromParent()
			&& _castleChannelName.IsDerivedFromParent()
			&& _castleChannelColor.IsDerivedFromParent()
			&& _showChannelName.IsDerivedFromParent()
			&& _showPlayerName.IsDerivedFromParent()
			&& _chatChannelIconA.IsDerivedFromParent()
			&& _chatChannelIconB.IsDerivedFromParent()
			&& _showBlinkOnMessage.IsDerivedFromParent()
			&& _shortcuts.IsDerivedFromParent()
			&& _clearMessagesOnLeave.IsDerivedFromParent()
			&& _spamInGlobalChannel.IsDerivedFromParent()
			&& _cooldownOnSpam.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "channelName" )
			_channelName.Reset();
		else if ( fieldName == "channelColor" )
			_channelColor.Reset();
		else if ( fieldName == "castleChannelName" )
			_castleChannelName.Reset();
		else if ( fieldName == "castleChannelColor" )
			_castleChannelColor.Reset();
		else if ( fieldName == "showChannelName" )
			_showChannelName.Reset();
		else if ( fieldName == "showPlayerName" )
			_showPlayerName.Reset();
		else if ( fieldName == "chatChannelIconA" )
			_chatChannelIconA.Reset();
		else if ( fieldName == "chatChannelIconB" )
			_chatChannelIconB.Reset();
		else if ( fieldName == "showBlinkOnMessage" )
			_showBlinkOnMessage.Reset();
		else if ( fieldName == "shortcuts" )
			_shortcuts.Reset();
		else if ( fieldName == "clearMessagesOnLeave" )
			_clearMessagesOnLeave.Reset();
		else if ( fieldName == "spamInGlobalChannel" )
			_spamInGlobalChannel.Reset();
		else if ( fieldName == "cooldownOnSpam" )
			_cooldownOnSpam.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "channelName" )
			return _channelName.IsDerivedFromParent();
		if ( fieldName == "channelColor" )
			return _channelColor.IsDerivedFromParent();
		if ( fieldName == "castleChannelName" )
			return _castleChannelName.IsDerivedFromParent();
		if ( fieldName == "castleChannelColor" )
			return _castleChannelColor.IsDerivedFromParent();
		if ( fieldName == "showChannelName" )
			return _showChannelName.IsDerivedFromParent();
		if ( fieldName == "showPlayerName" )
			return _showPlayerName.IsDerivedFromParent();
		if ( fieldName == "chatChannelIconA" )
			return _chatChannelIconA.IsDerivedFromParent();
		if ( fieldName == "chatChannelIconB" )
			return _chatChannelIconB.IsDerivedFromParent();
		if ( fieldName == "showBlinkOnMessage" )
			return _showBlinkOnMessage.IsDerivedFromParent();
		if ( fieldName == "shortcuts" )
			return _shortcuts.IsDerivedFromParent();
		if ( fieldName == "clearMessagesOnLeave" )
			return _clearMessagesOnLeave.IsDerivedFromParent();
		if ( fieldName == "spamInGlobalChannel" )
			return _spamInGlobalChannel.IsDerivedFromParent();
		if ( fieldName == "cooldownOnSpam" )
			return _cooldownOnSpam.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class CombatStatuses : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CombatStatuses __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _replaySpeed;
	private TextRef _replayPause;

	public TextRef replaySpeed { get { return _replaySpeed; } set { _replaySpeed.Assign( value ); } }

	public TextRef replayPause { get { return _replayPause; } set { _replayPause.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_replaySpeed = new TextRef( owner, new TextRef() );
		_replayPause = new TextRef( owner, new TextRef() );
		_replaySpeed.Changed += FireChangedEvent;
		_replayPause.Changed += FireChangedEvent;
	}

	public CombatStatuses()
	{
		Initialize( GetOwner() );
	}

	public CombatStatuses( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CombatStatuses( DBResource owner, CombatStatuses source )
		: this(owner, source, true){}

	protected CombatStatuses( DBResource owner, CombatStatuses source, bool fireEvent )
	{
		_replaySpeed = new TextRef( owner, source.replaySpeed );
		_replayPause = new TextRef( owner, source.replayPause );
		_replaySpeed.Changed += FireChangedEvent;
		_replayPause.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CombatStatuses source = _source as CombatStatuses;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CombatStatuses" );
		replaySpeed = source.replaySpeed;
		replayPause = source.replayPause;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CombatStatuses newParent = _newParent as CombatStatuses;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_replaySpeed.SetParent( newParent == null ? null : newParent._replaySpeed );
		_replayPause.SetParent( newParent == null ? null : newParent._replayPause );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_replaySpeed.Reset();
		_replayPause.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_replaySpeed.IsDerivedFromParent()
			&& _replayPause.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "replaySpeed" )
			_replaySpeed.Reset();
		else if ( fieldName == "replayPause" )
			_replayPause.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "replaySpeed" )
			return _replaySpeed.IsDerivedFromParent();
		if ( fieldName == "replayPause" )
			return _replayPause.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[Description( "флаги для ботов" )]
public class BotDefaultFlags : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BotDefaultFlags __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private CountryFlag _adornianDefaultFlag;
	private CountryFlag _doctDefaultFlag;

	public CountryFlag adornianDefaultFlag { get { return _adornianDefaultFlag; } set { _adornianDefaultFlag.Assign( value ); } }

	public CountryFlag doctDefaultFlag { get { return _doctDefaultFlag; } set { _doctDefaultFlag.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_adornianDefaultFlag = new CountryFlag( owner );
		_doctDefaultFlag = new CountryFlag( owner );
		_adornianDefaultFlag.Changed += FireChangedEvent;
		_doctDefaultFlag.Changed += FireChangedEvent;
	}

	public BotDefaultFlags()
	{
		Initialize( GetOwner() );
	}

	public BotDefaultFlags( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BotDefaultFlags( DBResource owner, BotDefaultFlags source )
		: this(owner, source, true){}

	protected BotDefaultFlags( DBResource owner, BotDefaultFlags source, bool fireEvent )
	{
		_adornianDefaultFlag = new CountryFlag( owner, source.adornianDefaultFlag );
		_doctDefaultFlag = new CountryFlag( owner, source.doctDefaultFlag );
		_adornianDefaultFlag.Changed += FireChangedEvent;
		_doctDefaultFlag.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BotDefaultFlags source = _source as BotDefaultFlags;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BotDefaultFlags" );
		adornianDefaultFlag = source.adornianDefaultFlag;
		doctDefaultFlag = source.doctDefaultFlag;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BotDefaultFlags newParent = _newParent as BotDefaultFlags;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_adornianDefaultFlag.SetParent( newParent == null ? null : newParent._adornianDefaultFlag );
		_doctDefaultFlag.SetParent( newParent == null ? null : newParent._doctDefaultFlag );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_adornianDefaultFlag.Reset();
		_doctDefaultFlag.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_adornianDefaultFlag.IsDerivedFromParent()
			&& _doctDefaultFlag.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "adornianDefaultFlag" )
			_adornianDefaultFlag.Reset();
		else if ( fieldName == "doctDefaultFlag" )
			_doctDefaultFlag.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "adornianDefaultFlag" )
			return _adornianDefaultFlag.IsDerivedFromParent();
		if ( fieldName == "doctDefaultFlag" )
			return _doctDefaultFlag.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
public class DamageBloodMaskParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DamageBloodMaskParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private AnimatedFloat _alphaCurve;
	private UndoRedo<float> _lowHealthAlpha;
	private UndoRedo<float> _nearDeathAlpha;
	private UndoRedo<float> _lowHealthLevel;
	private UndoRedo<float> _nearDeathLevel;
	private UndoRedo<float> _lowHealthSaturation;
	private UndoRedo<float> _nearDeathSaturation;
	private UndoRedo<float> _afterDeathSaturation;
	private UndoRedo<float> _afterLoseSaturation;
	private UndoRedo<float> _saturationChangeSpeed;
	private UndoRedo<float> _saturationChangeSpeedAfterLose;

	[Description( "alpha curve of blood mask right after hit" )]
	public AnimatedFloat alphaCurve { get { return _alphaCurve; } set { _alphaCurve.Assign( value ); } }

	[Description( "alpha level of image when health is low" )]
	public float lowHealthAlpha { get { return _lowHealthAlpha.Get(); } set { _lowHealthAlpha.Set( value ); } }

	[Description( "alpha level of image when hero is near death" )]
	public float nearDeathAlpha { get { return _nearDeathAlpha.Get(); } set { _nearDeathAlpha.Set( value ); } }

	[Description( "level of health when hero's health is low" )]
	public float lowHealthLevel { get { return _lowHealthLevel.Get(); } set { _lowHealthLevel.Set( value ); } }

	[Description( "level of health when hero is near death" )]
	public float nearDeathLevel { get { return _nearDeathLevel.Get(); } set { _nearDeathLevel.Set( value ); } }

	[Description( "Color saturation on lowHealthLevel [0..1]" )]
	public float lowHealthSaturation { get { return _lowHealthSaturation.Get(); } set { _lowHealthSaturation.Set( value ); } }

	[Description( "Color saturation on nearDeathLevel [0..1]" )]
	public float nearDeathSaturation { get { return _nearDeathSaturation.Get(); } set { _nearDeathSaturation.Set( value ); } }

	[Description( "Color saturation on death [0..1]" )]
	public float afterDeathSaturation { get { return _afterDeathSaturation.Get(); } set { _afterDeathSaturation.Set( value ); } }

	[Description( "Color saturation on lose [0..1]" )]
	public float afterLoseSaturation { get { return _afterLoseSaturation.Get(); } set { _afterLoseSaturation.Set( value ); } }

	[Description( "Speed of saturation changing in game process (values / sec)" )]
	public float saturationChangeSpeed { get { return _saturationChangeSpeed.Get(); } set { _saturationChangeSpeed.Set( value ); } }

	[Description( "Speed of saturation changing after loose (values / sec)" )]
	public float saturationChangeSpeedAfterLose { get { return _saturationChangeSpeedAfterLose.Get(); } set { _saturationChangeSpeedAfterLose.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_alphaCurve = new AnimatedFloat( owner, 0.0f );
		_lowHealthAlpha = new UndoRedo<float>( owner, 0.2f );
		_nearDeathAlpha = new UndoRedo<float>( owner, 0.4f );
		_lowHealthLevel = new UndoRedo<float>( owner, 0.33f );
		_nearDeathLevel = new UndoRedo<float>( owner, 0.16f );
		_lowHealthSaturation = new UndoRedo<float>( owner, 0.5f );
		_nearDeathSaturation = new UndoRedo<float>( owner, 0.2f );
		_afterDeathSaturation = new UndoRedo<float>( owner, 0.0f );
		_afterLoseSaturation = new UndoRedo<float>( owner, 0.3f );
		_saturationChangeSpeed = new UndoRedo<float>( owner, 0.3333333f );
		_saturationChangeSpeedAfterLose = new UndoRedo<float>( owner, 0.1111111f );
		_alphaCurve.Changed += FireChangedEvent;
		_lowHealthAlpha.Changed += FireChangedEvent;
		_nearDeathAlpha.Changed += FireChangedEvent;
		_lowHealthLevel.Changed += FireChangedEvent;
		_nearDeathLevel.Changed += FireChangedEvent;
		_lowHealthSaturation.Changed += FireChangedEvent;
		_nearDeathSaturation.Changed += FireChangedEvent;
		_afterDeathSaturation.Changed += FireChangedEvent;
		_afterLoseSaturation.Changed += FireChangedEvent;
		_saturationChangeSpeed.Changed += FireChangedEvent;
		_saturationChangeSpeedAfterLose.Changed += FireChangedEvent;
	}

	public DamageBloodMaskParams()
	{
		Initialize( GetOwner() );
	}

	public DamageBloodMaskParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DamageBloodMaskParams( DBResource owner, DamageBloodMaskParams source )
		: this(owner, source, true){}

	protected DamageBloodMaskParams( DBResource owner, DamageBloodMaskParams source, bool fireEvent )
	{
		_alphaCurve = new AnimatedFloat( owner, source.alphaCurve );
		_lowHealthAlpha = new UndoRedo<float>( owner, source.lowHealthAlpha );
		_nearDeathAlpha = new UndoRedo<float>( owner, source.nearDeathAlpha );
		_lowHealthLevel = new UndoRedo<float>( owner, source.lowHealthLevel );
		_nearDeathLevel = new UndoRedo<float>( owner, source.nearDeathLevel );
		_lowHealthSaturation = new UndoRedo<float>( owner, source.lowHealthSaturation );
		_nearDeathSaturation = new UndoRedo<float>( owner, source.nearDeathSaturation );
		_afterDeathSaturation = new UndoRedo<float>( owner, source.afterDeathSaturation );
		_afterLoseSaturation = new UndoRedo<float>( owner, source.afterLoseSaturation );
		_saturationChangeSpeed = new UndoRedo<float>( owner, source.saturationChangeSpeed );
		_saturationChangeSpeedAfterLose = new UndoRedo<float>( owner, source.saturationChangeSpeedAfterLose );
		_alphaCurve.Changed += FireChangedEvent;
		_lowHealthAlpha.Changed += FireChangedEvent;
		_nearDeathAlpha.Changed += FireChangedEvent;
		_lowHealthLevel.Changed += FireChangedEvent;
		_nearDeathLevel.Changed += FireChangedEvent;
		_lowHealthSaturation.Changed += FireChangedEvent;
		_nearDeathSaturation.Changed += FireChangedEvent;
		_afterDeathSaturation.Changed += FireChangedEvent;
		_afterLoseSaturation.Changed += FireChangedEvent;
		_saturationChangeSpeed.Changed += FireChangedEvent;
		_saturationChangeSpeedAfterLose.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DamageBloodMaskParams source = _source as DamageBloodMaskParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DamageBloodMaskParams" );
		alphaCurve = source.alphaCurve;
		lowHealthAlpha = source.lowHealthAlpha;
		nearDeathAlpha = source.nearDeathAlpha;
		lowHealthLevel = source.lowHealthLevel;
		nearDeathLevel = source.nearDeathLevel;
		lowHealthSaturation = source.lowHealthSaturation;
		nearDeathSaturation = source.nearDeathSaturation;
		afterDeathSaturation = source.afterDeathSaturation;
		afterLoseSaturation = source.afterLoseSaturation;
		saturationChangeSpeed = source.saturationChangeSpeed;
		saturationChangeSpeedAfterLose = source.saturationChangeSpeedAfterLose;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DamageBloodMaskParams newParent = _newParent as DamageBloodMaskParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_alphaCurve.SetParent( newParent == null ? null : newParent._alphaCurve );
		_lowHealthAlpha.SetParent( newParent == null ? null : newParent._lowHealthAlpha );
		_nearDeathAlpha.SetParent( newParent == null ? null : newParent._nearDeathAlpha );
		_lowHealthLevel.SetParent( newParent == null ? null : newParent._lowHealthLevel );
		_nearDeathLevel.SetParent( newParent == null ? null : newParent._nearDeathLevel );
		_lowHealthSaturation.SetParent( newParent == null ? null : newParent._lowHealthSaturation );
		_nearDeathSaturation.SetParent( newParent == null ? null : newParent._nearDeathSaturation );
		_afterDeathSaturation.SetParent( newParent == null ? null : newParent._afterDeathSaturation );
		_afterLoseSaturation.SetParent( newParent == null ? null : newParent._afterLoseSaturation );
		_saturationChangeSpeed.SetParent( newParent == null ? null : newParent._saturationChangeSpeed );
		_saturationChangeSpeedAfterLose.SetParent( newParent == null ? null : newParent._saturationChangeSpeedAfterLose );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_alphaCurve.Reset();
		_lowHealthAlpha.Reset();
		_nearDeathAlpha.Reset();
		_lowHealthLevel.Reset();
		_nearDeathLevel.Reset();
		_lowHealthSaturation.Reset();
		_nearDeathSaturation.Reset();
		_afterDeathSaturation.Reset();
		_afterLoseSaturation.Reset();
		_saturationChangeSpeed.Reset();
		_saturationChangeSpeedAfterLose.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_alphaCurve.IsDerivedFromParent()
			&& _lowHealthAlpha.IsDerivedFromParent()
			&& _nearDeathAlpha.IsDerivedFromParent()
			&& _lowHealthLevel.IsDerivedFromParent()
			&& _nearDeathLevel.IsDerivedFromParent()
			&& _lowHealthSaturation.IsDerivedFromParent()
			&& _nearDeathSaturation.IsDerivedFromParent()
			&& _afterDeathSaturation.IsDerivedFromParent()
			&& _afterLoseSaturation.IsDerivedFromParent()
			&& _saturationChangeSpeed.IsDerivedFromParent()
			&& _saturationChangeSpeedAfterLose.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "alphaCurve" )
			_alphaCurve.Reset();
		else if ( fieldName == "lowHealthAlpha" )
			_lowHealthAlpha.Reset();
		else if ( fieldName == "nearDeathAlpha" )
			_nearDeathAlpha.Reset();
		else if ( fieldName == "lowHealthLevel" )
			_lowHealthLevel.Reset();
		else if ( fieldName == "nearDeathLevel" )
			_nearDeathLevel.Reset();
		else if ( fieldName == "lowHealthSaturation" )
			_lowHealthSaturation.Reset();
		else if ( fieldName == "nearDeathSaturation" )
			_nearDeathSaturation.Reset();
		else if ( fieldName == "afterDeathSaturation" )
			_afterDeathSaturation.Reset();
		else if ( fieldName == "afterLoseSaturation" )
			_afterLoseSaturation.Reset();
		else if ( fieldName == "saturationChangeSpeed" )
			_saturationChangeSpeed.Reset();
		else if ( fieldName == "saturationChangeSpeedAfterLose" )
			_saturationChangeSpeedAfterLose.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "alphaCurve" )
			return _alphaCurve.IsDerivedFromParent();
		if ( fieldName == "lowHealthAlpha" )
			return _lowHealthAlpha.IsDerivedFromParent();
		if ( fieldName == "nearDeathAlpha" )
			return _nearDeathAlpha.IsDerivedFromParent();
		if ( fieldName == "lowHealthLevel" )
			return _lowHealthLevel.IsDerivedFromParent();
		if ( fieldName == "nearDeathLevel" )
			return _nearDeathLevel.IsDerivedFromParent();
		if ( fieldName == "lowHealthSaturation" )
			return _lowHealthSaturation.IsDerivedFromParent();
		if ( fieldName == "nearDeathSaturation" )
			return _nearDeathSaturation.IsDerivedFromParent();
		if ( fieldName == "afterDeathSaturation" )
			return _afterDeathSaturation.IsDerivedFromParent();
		if ( fieldName == "afterLoseSaturation" )
			return _afterLoseSaturation.IsDerivedFromParent();
		if ( fieldName == "saturationChangeSpeed" )
			return _saturationChangeSpeed.IsDerivedFromParent();
		if ( fieldName == "saturationChangeSpeedAfterLose" )
			return _saturationChangeSpeedAfterLose.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class DampSmoothing : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DampSmoothing __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _dampTimeObserv;
	private UndoRedo<float> _dampTimeMove;
	private UndoRedo<float> _anchorShiftObserv;
	private UndoRedo<float> _projCorretionShiftObservMaxZoom;
	private UndoRedo<float> _projCorretionShiftObservMinZoom;
	private UndoRedo<float> _firstJumpTime;
	private UndoRedo<float> _zoomFactorMove;
	private UndoRedo<float> _zoomFactorObserv;
	private UndoRedo<float> _maxSpeed;
	private UndoRedo<float> _timeToMaxSpeed;

	[Description( "Время лага пружины в режиме наблюдения за героем. Характеризует максимальное расстояние от текущей позиции до целевой: <Максимальное расстояние> = <Текущая скорость> * <Время лага>" )]
	public float dampTimeObserv { get { return _dampTimeObserv.Get(); } set { _dampTimeObserv.Set( value ); } }

	[Description( "Время лага пружины в режиме свободного перемещения" )]
	public float dampTimeMove { get { return _dampTimeMove.Get(); } set { _dampTimeMove.Set( value ); } }

	[Description( "Длина вектора на который смещается точка привязки камеры в режиме наблюдения за героем. Вектор направлен в сторону взгляда героя и служит для того чтобы с одной стороны камера не слишком отставала при движении, а с другой стоны,для того чтобы можно было увидеть больше в направлении взгляда героя, где обычно происходит самое интересное" )]
	public float anchorShiftObserv { get { return _anchorShiftObserv.Get(); } set { _anchorShiftObserv.Set( value ); } }

	[Description( "Длина вектора при максимальном зуме на который смещается точка привязки камеры в режиме наблюдения за героем. Вектор направлен в ту же сторону, что и камера и служит для того чтобы в центре экрана находилось тело героя, а не его ботинки" )]
	public float projCorretionShiftObservMaxZoom { get { return _projCorretionShiftObservMaxZoom.Get(); } set { _projCorretionShiftObservMaxZoom.Set( value ); } }

	[Description( "Длина вектора при минимальном зуме на который смещается точка привязки камеры в режиме наблюдения за героем. Вектор направлен в ту же сторону, что и камера и служит для того чтобы в центре экрана находилось тело героя, а не его ботинки" )]
	public float projCorretionShiftObservMinZoom { get { return _projCorretionShiftObservMinZoom.Get(); } set { _projCorretionShiftObservMinZoom.Set( value ); } }

	[Description( "Время первого прыжка камеры в режиме свободного перемещения. Такой прыжок нужен для того, чтобы повысить отзывчивость камеры, которая без такого смещения ощутимо сопротивляется движению" )]
	public float firstJumpTime { get { return _firstJumpTime.Get(); } set { _firstJumpTime.Set( value ); } }

	[Description( "Коэффициент зависимости смещения камеры от текущего зума в режиме свободного перемещения. Без такой зависимости при приближении к земле камеру невозможно подвинуть к конкретному предмету. При значении 1 зависимость отсутствует, далее при уменьшении коэффициента зависимость увеличивается. Поведение камеры при зуме по-умолчанию не зависит от данного коэффициента" )]
	public float zoomFactorMove { get { return _zoomFactorMove.Get(); } set { _zoomFactorMove.Set( value ); } }

	[Description( "Коэффициент зависимости смещения камеры от текущего зума в режиме наблюдения за героем. Данная зависимость  управляет dampTimeObserv и anchorShiftObserv" )]
	public float zoomFactorObserv { get { return _zoomFactorObserv.Get(); } set { _zoomFactorObserv.Set( value ); } }

	[Description( "Максимальная скорость камеры" )]
	public float maxSpeed { get { return _maxSpeed.Get(); } set { _maxSpeed.Set( value ); } }

	[Description( "Время за которое достигается максимальная скорость движения камеры в режиме свободного перемещения при непрерывном нажатии кнопки" )]
	public float timeToMaxSpeed { get { return _timeToMaxSpeed.Get(); } set { _timeToMaxSpeed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_dampTimeObserv = new UndoRedo<float>( owner, 0.4f );
		_dampTimeMove = new UndoRedo<float>( owner, 0.2f );
		_anchorShiftObserv = new UndoRedo<float>( owner, 2.5f );
		_projCorretionShiftObservMaxZoom = new UndoRedo<float>( owner, 2.2f );
		_projCorretionShiftObservMinZoom = new UndoRedo<float>( owner, 0.0f );
		_firstJumpTime = new UndoRedo<float>( owner, 0.2f );
		_zoomFactorMove = new UndoRedo<float>( owner, 0.1f );
		_zoomFactorObserv = new UndoRedo<float>( owner, 0.7f );
		_maxSpeed = new UndoRedo<float>( owner, 60.0f );
		_timeToMaxSpeed = new UndoRedo<float>( owner, 3.0f );
		_dampTimeObserv.Changed += FireChangedEvent;
		_dampTimeMove.Changed += FireChangedEvent;
		_anchorShiftObserv.Changed += FireChangedEvent;
		_projCorretionShiftObservMaxZoom.Changed += FireChangedEvent;
		_projCorretionShiftObservMinZoom.Changed += FireChangedEvent;
		_firstJumpTime.Changed += FireChangedEvent;
		_zoomFactorMove.Changed += FireChangedEvent;
		_zoomFactorObserv.Changed += FireChangedEvent;
		_maxSpeed.Changed += FireChangedEvent;
		_timeToMaxSpeed.Changed += FireChangedEvent;
	}

	public DampSmoothing()
	{
		Initialize( GetOwner() );
	}

	public DampSmoothing( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DampSmoothing( DBResource owner, DampSmoothing source )
		: this(owner, source, true){}

	protected DampSmoothing( DBResource owner, DampSmoothing source, bool fireEvent )
	{
		_dampTimeObserv = new UndoRedo<float>( owner, source.dampTimeObserv );
		_dampTimeMove = new UndoRedo<float>( owner, source.dampTimeMove );
		_anchorShiftObserv = new UndoRedo<float>( owner, source.anchorShiftObserv );
		_projCorretionShiftObservMaxZoom = new UndoRedo<float>( owner, source.projCorretionShiftObservMaxZoom );
		_projCorretionShiftObservMinZoom = new UndoRedo<float>( owner, source.projCorretionShiftObservMinZoom );
		_firstJumpTime = new UndoRedo<float>( owner, source.firstJumpTime );
		_zoomFactorMove = new UndoRedo<float>( owner, source.zoomFactorMove );
		_zoomFactorObserv = new UndoRedo<float>( owner, source.zoomFactorObserv );
		_maxSpeed = new UndoRedo<float>( owner, source.maxSpeed );
		_timeToMaxSpeed = new UndoRedo<float>( owner, source.timeToMaxSpeed );
		_dampTimeObserv.Changed += FireChangedEvent;
		_dampTimeMove.Changed += FireChangedEvent;
		_anchorShiftObserv.Changed += FireChangedEvent;
		_projCorretionShiftObservMaxZoom.Changed += FireChangedEvent;
		_projCorretionShiftObservMinZoom.Changed += FireChangedEvent;
		_firstJumpTime.Changed += FireChangedEvent;
		_zoomFactorMove.Changed += FireChangedEvent;
		_zoomFactorObserv.Changed += FireChangedEvent;
		_maxSpeed.Changed += FireChangedEvent;
		_timeToMaxSpeed.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DampSmoothing source = _source as DampSmoothing;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DampSmoothing" );
		dampTimeObserv = source.dampTimeObserv;
		dampTimeMove = source.dampTimeMove;
		anchorShiftObserv = source.anchorShiftObserv;
		projCorretionShiftObservMaxZoom = source.projCorretionShiftObservMaxZoom;
		projCorretionShiftObservMinZoom = source.projCorretionShiftObservMinZoom;
		firstJumpTime = source.firstJumpTime;
		zoomFactorMove = source.zoomFactorMove;
		zoomFactorObserv = source.zoomFactorObserv;
		maxSpeed = source.maxSpeed;
		timeToMaxSpeed = source.timeToMaxSpeed;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DampSmoothing newParent = _newParent as DampSmoothing;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_dampTimeObserv.SetParent( newParent == null ? null : newParent._dampTimeObserv );
		_dampTimeMove.SetParent( newParent == null ? null : newParent._dampTimeMove );
		_anchorShiftObserv.SetParent( newParent == null ? null : newParent._anchorShiftObserv );
		_projCorretionShiftObservMaxZoom.SetParent( newParent == null ? null : newParent._projCorretionShiftObservMaxZoom );
		_projCorretionShiftObservMinZoom.SetParent( newParent == null ? null : newParent._projCorretionShiftObservMinZoom );
		_firstJumpTime.SetParent( newParent == null ? null : newParent._firstJumpTime );
		_zoomFactorMove.SetParent( newParent == null ? null : newParent._zoomFactorMove );
		_zoomFactorObserv.SetParent( newParent == null ? null : newParent._zoomFactorObserv );
		_maxSpeed.SetParent( newParent == null ? null : newParent._maxSpeed );
		_timeToMaxSpeed.SetParent( newParent == null ? null : newParent._timeToMaxSpeed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_dampTimeObserv.Reset();
		_dampTimeMove.Reset();
		_anchorShiftObserv.Reset();
		_projCorretionShiftObservMaxZoom.Reset();
		_projCorretionShiftObservMinZoom.Reset();
		_firstJumpTime.Reset();
		_zoomFactorMove.Reset();
		_zoomFactorObserv.Reset();
		_maxSpeed.Reset();
		_timeToMaxSpeed.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_dampTimeObserv.IsDerivedFromParent()
			&& _dampTimeMove.IsDerivedFromParent()
			&& _anchorShiftObserv.IsDerivedFromParent()
			&& _projCorretionShiftObservMaxZoom.IsDerivedFromParent()
			&& _projCorretionShiftObservMinZoom.IsDerivedFromParent()
			&& _firstJumpTime.IsDerivedFromParent()
			&& _zoomFactorMove.IsDerivedFromParent()
			&& _zoomFactorObserv.IsDerivedFromParent()
			&& _maxSpeed.IsDerivedFromParent()
			&& _timeToMaxSpeed.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "dampTimeObserv" )
			_dampTimeObserv.Reset();
		else if ( fieldName == "dampTimeMove" )
			_dampTimeMove.Reset();
		else if ( fieldName == "anchorShiftObserv" )
			_anchorShiftObserv.Reset();
		else if ( fieldName == "projCorretionShiftObservMaxZoom" )
			_projCorretionShiftObservMaxZoom.Reset();
		else if ( fieldName == "projCorretionShiftObservMinZoom" )
			_projCorretionShiftObservMinZoom.Reset();
		else if ( fieldName == "firstJumpTime" )
			_firstJumpTime.Reset();
		else if ( fieldName == "zoomFactorMove" )
			_zoomFactorMove.Reset();
		else if ( fieldName == "zoomFactorObserv" )
			_zoomFactorObserv.Reset();
		else if ( fieldName == "maxSpeed" )
			_maxSpeed.Reset();
		else if ( fieldName == "timeToMaxSpeed" )
			_timeToMaxSpeed.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "dampTimeObserv" )
			return _dampTimeObserv.IsDerivedFromParent();
		if ( fieldName == "dampTimeMove" )
			return _dampTimeMove.IsDerivedFromParent();
		if ( fieldName == "anchorShiftObserv" )
			return _anchorShiftObserv.IsDerivedFromParent();
		if ( fieldName == "projCorretionShiftObservMaxZoom" )
			return _projCorretionShiftObservMaxZoom.IsDerivedFromParent();
		if ( fieldName == "projCorretionShiftObservMinZoom" )
			return _projCorretionShiftObservMinZoom.IsDerivedFromParent();
		if ( fieldName == "firstJumpTime" )
			return _firstJumpTime.IsDerivedFromParent();
		if ( fieldName == "zoomFactorMove" )
			return _zoomFactorMove.IsDerivedFromParent();
		if ( fieldName == "zoomFactorObserv" )
			return _zoomFactorObserv.IsDerivedFromParent();
		if ( fieldName == "maxSpeed" )
			return _maxSpeed.IsDerivedFromParent();
		if ( fieldName == "timeToMaxSpeed" )
			return _timeToMaxSpeed.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class DialogsSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DialogsSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _defaultPhraseDuration;
	private UndoRedo<float> _defaultSilenceDuration;
	private UndoRedo<float> _FadeInOutPercentage;

	public float defaultPhraseDuration { get { return _defaultPhraseDuration.Get(); } set { _defaultPhraseDuration.Set( value ); } }

	[Description( "Длительность тишины после фразы" )]
	public float defaultSilenceDuration { get { return _defaultSilenceDuration.Get(); } set { _defaultSilenceDuration.Set( value ); } }

	public float FadeInOutPercentage { get { return _FadeInOutPercentage.Get(); } set { _FadeInOutPercentage.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_defaultPhraseDuration = new UndoRedo<float>( owner, 30.0f );
		_defaultSilenceDuration = new UndoRedo<float>( owner, 0.0f );
		_FadeInOutPercentage = new UndoRedo<float>( owner, 0.4f );
		_defaultPhraseDuration.Changed += FireChangedEvent;
		_defaultSilenceDuration.Changed += FireChangedEvent;
		_FadeInOutPercentage.Changed += FireChangedEvent;
	}

	public DialogsSettings()
	{
		Initialize( GetOwner() );
	}

	public DialogsSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DialogsSettings( DBResource owner, DialogsSettings source )
		: this(owner, source, true){}

	protected DialogsSettings( DBResource owner, DialogsSettings source, bool fireEvent )
	{
		_defaultPhraseDuration = new UndoRedo<float>( owner, source.defaultPhraseDuration );
		_defaultSilenceDuration = new UndoRedo<float>( owner, source.defaultSilenceDuration );
		_FadeInOutPercentage = new UndoRedo<float>( owner, source.FadeInOutPercentage );
		_defaultPhraseDuration.Changed += FireChangedEvent;
		_defaultSilenceDuration.Changed += FireChangedEvent;
		_FadeInOutPercentage.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DialogsSettings source = _source as DialogsSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DialogsSettings" );
		defaultPhraseDuration = source.defaultPhraseDuration;
		defaultSilenceDuration = source.defaultSilenceDuration;
		FadeInOutPercentage = source.FadeInOutPercentage;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DialogsSettings newParent = _newParent as DialogsSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_defaultPhraseDuration.SetParent( newParent == null ? null : newParent._defaultPhraseDuration );
		_defaultSilenceDuration.SetParent( newParent == null ? null : newParent._defaultSilenceDuration );
		_FadeInOutPercentage.SetParent( newParent == null ? null : newParent._FadeInOutPercentage );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_defaultPhraseDuration.Reset();
		_defaultSilenceDuration.Reset();
		_FadeInOutPercentage.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_defaultPhraseDuration.IsDerivedFromParent()
			&& _defaultSilenceDuration.IsDerivedFromParent()
			&& _FadeInOutPercentage.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "defaultPhraseDuration" )
			_defaultPhraseDuration.Reset();
		else if ( fieldName == "defaultSilenceDuration" )
			_defaultSilenceDuration.Reset();
		else if ( fieldName == "FadeInOutPercentage" )
			_FadeInOutPercentage.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "defaultPhraseDuration" )
			return _defaultPhraseDuration.IsDerivedFromParent();
		if ( fieldName == "defaultSilenceDuration" )
			return _defaultSilenceDuration.IsDerivedFromParent();
		if ( fieldName == "FadeInOutPercentage" )
			return _FadeInOutPercentage.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class RestrictedScoring : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RestrictedScoring __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _score;
	private UndoRedo<int> _maxScore;

	public int score { get { return _score.Get(); } set { _score.Set( value ); } }

	public int maxScore { get { return _maxScore.Get(); } set { _maxScore.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_score = new UndoRedo<int>( owner, 0 );
		_maxScore = new UndoRedo<int>( owner, 0 );
		_score.Changed += FireChangedEvent;
		_maxScore.Changed += FireChangedEvent;
	}

	public RestrictedScoring()
	{
		Initialize( GetOwner() );
	}

	public RestrictedScoring( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RestrictedScoring( DBResource owner, RestrictedScoring source )
		: this(owner, source, true){}

	protected RestrictedScoring( DBResource owner, RestrictedScoring source, bool fireEvent )
	{
		_score = new UndoRedo<int>( owner, source.score );
		_maxScore = new UndoRedo<int>( owner, source.maxScore );
		_score.Changed += FireChangedEvent;
		_maxScore.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RestrictedScoring source = _source as RestrictedScoring;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RestrictedScoring" );
		score = source.score;
		maxScore = source.maxScore;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RestrictedScoring newParent = _newParent as RestrictedScoring;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_score.SetParent( newParent == null ? null : newParent._score );
		_maxScore.SetParent( newParent == null ? null : newParent._maxScore );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_score.Reset();
		_maxScore.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_score.IsDerivedFromParent()
			&& _maxScore.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "score" )
			_score.Reset();
		else if ( fieldName == "maxScore" )
			_maxScore.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "score" )
			return _score.IsDerivedFromParent();
		if ( fieldName == "maxScore" )
			return _maxScore.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class ErrorMessageDescription : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ErrorMessageDescription __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _textMessage;
	private UndoRedo<bool> _shouldPlaySound;
	private UndoRedo<float> _lifeTime;

	public TextRef textMessage { get { return _textMessage; } set { _textMessage.Assign( value ); } }

	public bool shouldPlaySound { get { return _shouldPlaySound.Get(); } set { _shouldPlaySound.Set( value ); } }

	public float lifeTime { get { return _lifeTime.Get(); } set { _lifeTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_textMessage = new TextRef( owner, new TextRef() );
		_shouldPlaySound = new UndoRedo<bool>( owner, false );
		_lifeTime = new UndoRedo<float>( owner, 1.0f );
		_textMessage.Changed += FireChangedEvent;
		_shouldPlaySound.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
	}

	public ErrorMessageDescription()
	{
		Initialize( GetOwner() );
	}

	public ErrorMessageDescription( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ErrorMessageDescription( DBResource owner, ErrorMessageDescription source )
		: this(owner, source, true){}

	protected ErrorMessageDescription( DBResource owner, ErrorMessageDescription source, bool fireEvent )
	{
		_textMessage = new TextRef( owner, source.textMessage );
		_shouldPlaySound = new UndoRedo<bool>( owner, source.shouldPlaySound );
		_lifeTime = new UndoRedo<float>( owner, source.lifeTime );
		_textMessage.Changed += FireChangedEvent;
		_shouldPlaySound.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ErrorMessageDescription source = _source as ErrorMessageDescription;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ErrorMessageDescription" );
		textMessage = source.textMessage;
		shouldPlaySound = source.shouldPlaySound;
		lifeTime = source.lifeTime;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ErrorMessageDescription newParent = _newParent as ErrorMessageDescription;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_textMessage.SetParent( newParent == null ? null : newParent._textMessage );
		_shouldPlaySound.SetParent( newParent == null ? null : newParent._shouldPlaySound );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_textMessage.Reset();
		_shouldPlaySound.Reset();
		_lifeTime.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_textMessage.IsDerivedFromParent()
			&& _shouldPlaySound.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "textMessage" )
			_textMessage.Reset();
		else if ( fieldName == "shouldPlaySound" )
			_shouldPlaySound.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "textMessage" )
			return _textMessage.IsDerivedFromParent();
		if ( fieldName == "shouldPlaySound" )
			return _shouldPlaySound.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x0B6C5300)]
public class FlyOffText : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FlyOffText __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _lifeTime;
	private Vec2 _offset;
	private Vec2 _velocity;
	private Vec2 _acceleration;
	private UndoRedo<float> _startOpacity;
	private UndoRedo<float> _endOpacity;
	private UndoRedo<EFlyOffAlign> _align;
	private UndoRedo<string> _layout;

	[Description( "Fly-off text life time" )]
	public float lifeTime { get { return _lifeTime.Get(); } set { _lifeTime.Set( value ); } }

	[Description( "Offset" )]
	public Vec2 offset { get { return _offset; } set { _offset.Assign( value ); } }

	[Description( "Velocity" )]
	public Vec2 velocity { get { return _velocity; } set { _velocity.Assign( value ); } }

	[Description( "Acceleration" )]
	public Vec2 acceleration { get { return _acceleration; } set { _acceleration.Assign( value ); } }

	[Description( "Initial opacity" )]
	[FloatMinMax(0, 1)]
	public float startOpacity { get { return _startOpacity.Get(); } set { _startOpacity.Set( value ); } }

	[Description( "Target opacity at lifeTime" )]
	[FloatMinMax(0, 1)]
	public float endOpacity { get { return _endOpacity.Get(); } set { _endOpacity.Set( value ); } }

	[Description( "Flyoff alignment" )]
	public EFlyOffAlign align { get { return _align.Get(); } set { _align.Set( value ); } }

	[Description( "Fly-off text layout name" )]
	public string layout { get { return _layout.Get(); } set { _layout.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_lifeTime = new UndoRedo<float>( owner, 0.0f );
		_offset = new Vec2( owner );
		_velocity = new Vec2( owner );
		_acceleration = new Vec2( owner );
		_startOpacity = new UndoRedo<float>( owner, 0.0f );
		_endOpacity = new UndoRedo<float>( owner, 0.0f );
		_align = new UndoRedo<EFlyOffAlign>( owner, EFlyOffAlign.Left );
		_layout = new UndoRedo<string>( owner, string.Empty );
		_lifeTime.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_velocity.Changed += FireChangedEvent;
		_acceleration.Changed += FireChangedEvent;
		_startOpacity.Changed += FireChangedEvent;
		_endOpacity.Changed += FireChangedEvent;
		_align.Changed += FireChangedEvent;
		_layout.Changed += FireChangedEvent;
	}

	public FlyOffText()
	{
		Initialize( GetOwner() );
	}

	public FlyOffText( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FlyOffText( DBResource owner, FlyOffText source )
		: this(owner, source, true){}

	protected FlyOffText( DBResource owner, FlyOffText source, bool fireEvent )
	{
		_lifeTime = new UndoRedo<float>( owner, source.lifeTime );
		_offset = new Vec2( owner, source.offset );
		_velocity = new Vec2( owner, source.velocity );
		_acceleration = new Vec2( owner, source.acceleration );
		_startOpacity = new UndoRedo<float>( owner, source.startOpacity );
		_endOpacity = new UndoRedo<float>( owner, source.endOpacity );
		_align = new UndoRedo<EFlyOffAlign>( owner, source.align );
		_layout = new UndoRedo<string>( owner, source.layout );
		_lifeTime.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_velocity.Changed += FireChangedEvent;
		_acceleration.Changed += FireChangedEvent;
		_startOpacity.Changed += FireChangedEvent;
		_endOpacity.Changed += FireChangedEvent;
		_align.Changed += FireChangedEvent;
		_layout.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FlyOffText source = _source as FlyOffText;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FlyOffText" );
		lifeTime = source.lifeTime;
		offset = source.offset;
		velocity = source.velocity;
		acceleration = source.acceleration;
		startOpacity = source.startOpacity;
		endOpacity = source.endOpacity;
		align = source.align;
		layout = source.layout;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FlyOffText newParent = _newParent as FlyOffText;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_velocity.SetParent( newParent == null ? null : newParent._velocity );
		_acceleration.SetParent( newParent == null ? null : newParent._acceleration );
		_startOpacity.SetParent( newParent == null ? null : newParent._startOpacity );
		_endOpacity.SetParent( newParent == null ? null : newParent._endOpacity );
		_align.SetParent( newParent == null ? null : newParent._align );
		_layout.SetParent( newParent == null ? null : newParent._layout );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_lifeTime.Reset();
		_offset.Reset();
		_velocity.Reset();
		_acceleration.Reset();
		_startOpacity.Reset();
		_endOpacity.Reset();
		_align.Reset();
		_layout.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_lifeTime.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _velocity.IsDerivedFromParent()
			&& _acceleration.IsDerivedFromParent()
			&& _startOpacity.IsDerivedFromParent()
			&& _endOpacity.IsDerivedFromParent()
			&& _align.IsDerivedFromParent()
			&& _layout.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "velocity" )
			_velocity.Reset();
		else if ( fieldName == "acceleration" )
			_acceleration.Reset();
		else if ( fieldName == "startOpacity" )
			_startOpacity.Reset();
		else if ( fieldName == "endOpacity" )
			_endOpacity.Reset();
		else if ( fieldName == "align" )
			_align.Reset();
		else if ( fieldName == "layout" )
			_layout.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "velocity" )
			return _velocity.IsDerivedFromParent();
		if ( fieldName == "acceleration" )
			return _acceleration.IsDerivedFromParent();
		if ( fieldName == "startOpacity" )
			return _startOpacity.IsDerivedFromParent();
		if ( fieldName == "endOpacity" )
			return _endOpacity.IsDerivedFromParent();
		if ( fieldName == "align" )
			return _align.IsDerivedFromParent();
		if ( fieldName == "layout" )
			return _layout.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ForceColor : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ForceColor __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _force;
	private Color _color;
	private UndoRedoDBPtr<UIFontStyle> _style;

	public int force { get { return _force.Get(); } set { _force.Set( value ); } }

	public Color color { get { return _color; } set { _color.Assign( value ); } }

	public DBPtr<UIFontStyle> style { get { return _style.Get(); } set { _style.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_force = new UndoRedo<int>( owner, 0 );
		_color = new Color( owner );
		_style = new UndoRedoDBPtr<UIFontStyle>( owner );
		_force.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_style.Changed += FireChangedEvent;
	}

	public ForceColor()
	{
		Initialize( GetOwner() );
	}

	public ForceColor( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ForceColor( DBResource owner, ForceColor source )
		: this(owner, source, true){}

	protected ForceColor( DBResource owner, ForceColor source, bool fireEvent )
	{
		_force = new UndoRedo<int>( owner, source.force );
		_color = new Color( owner, source.color );
		_style = new UndoRedoDBPtr<UIFontStyle>( owner, source.style );
		_force.Changed += FireChangedEvent;
		_color.Changed += FireChangedEvent;
		_style.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ForceColor source = _source as ForceColor;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ForceColor" );
		force = source.force;
		color = source.color;
		style = source.style;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ForceColor newParent = _newParent as ForceColor;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_force.SetParent( newParent == null ? null : newParent._force );
		_color.SetParent( newParent == null ? null : newParent._color );
		_style.SetParent( newParent == null ? null : newParent._style );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_force.Reset();
		_color.Reset();
		_style.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_force.IsDerivedFromParent()
			&& _color.IsDerivedFromParent()
			&& _style.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "force" )
			_force.Reset();
		else if ( fieldName == "color" )
			_color.Reset();
		else if ( fieldName == "style" )
			_style.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "force" )
			return _force.IsDerivedFromParent();
		if ( fieldName == "color" )
			return _color.IsDerivedFromParent();
		if ( fieldName == "style" )
			return _style.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ForceToColorTable : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ForceToColorTable __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<ForceColor> _forceColors;

	public libdb.IChangeableList<ForceColor> forceColors { get { return _forceColors; } set { _forceColors.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_forceColors = new UndoRedoAssignableList<ForceColor>( owner );
		_forceColors.Changed += FireChangedEvent;
	}

	public ForceToColorTable()
	{
		Initialize( GetOwner() );
	}

	public ForceToColorTable( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ForceToColorTable( DBResource owner, ForceToColorTable source )
		: this(owner, source, true){}

	protected ForceToColorTable( DBResource owner, ForceToColorTable source, bool fireEvent )
	{
		_forceColors = new UndoRedoAssignableList<ForceColor>( owner );
		_forceColors.Assign( source.forceColors );
		_forceColors.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ForceToColorTable source = _source as ForceToColorTable;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ForceToColorTable" );
		forceColors = source.forceColors;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ForceToColorTable newParent = _newParent as ForceToColorTable;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_forceColors.SetParent( newParent == null ? null : newParent._forceColors );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_forceColors.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_forceColors.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "forceColors" )
			_forceColors.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "forceColors" )
			return _forceColors.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class GameUIData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GameUIData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _gamePauseMessage;
	private TextRef _gameResumeMessage;

	public TextRef gamePauseMessage { get { return _gamePauseMessage; } set { _gamePauseMessage.Assign( value ); } }

	public TextRef gameResumeMessage { get { return _gameResumeMessage; } set { _gameResumeMessage.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_gamePauseMessage = new TextRef( owner, new TextRef() );
		_gameResumeMessage = new TextRef( owner, new TextRef() );
		_gamePauseMessage.Changed += FireChangedEvent;
		_gameResumeMessage.Changed += FireChangedEvent;
	}

	public GameUIData()
	{
		Initialize( GetOwner() );
	}

	public GameUIData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GameUIData( DBResource owner, GameUIData source )
		: this(owner, source, true){}

	protected GameUIData( DBResource owner, GameUIData source, bool fireEvent )
	{
		_gamePauseMessage = new TextRef( owner, source.gamePauseMessage );
		_gameResumeMessage = new TextRef( owner, source.gameResumeMessage );
		_gamePauseMessage.Changed += FireChangedEvent;
		_gameResumeMessage.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GameUIData source = _source as GameUIData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GameUIData" );
		gamePauseMessage = source.gamePauseMessage;
		gameResumeMessage = source.gameResumeMessage;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GameUIData newParent = _newParent as GameUIData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_gamePauseMessage.SetParent( newParent == null ? null : newParent._gamePauseMessage );
		_gameResumeMessage.SetParent( newParent == null ? null : newParent._gameResumeMessage );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_gamePauseMessage.Reset();
		_gameResumeMessage.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_gamePauseMessage.IsDerivedFromParent()
			&& _gameResumeMessage.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "gamePauseMessage" )
			_gamePauseMessage.Reset();
		else if ( fieldName == "gameResumeMessage" )
			_gameResumeMessage.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "gamePauseMessage" )
			return _gamePauseMessage.IsDerivedFromParent();
		if ( fieldName == "gameResumeMessage" )
			return _gameResumeMessage.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("name")]
public class GuildShopTab : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GuildShopTab __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<GuildShopCategoryType> _category;
	private TextRef _name;
	private TextRef _tooltip;

	public GuildShopCategoryType category { get { return _category.Get(); } set { _category.Set( value ); } }

	[Description( "Название категории" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_category = new UndoRedo<GuildShopCategoryType>( owner, GuildShopCategoryType.ClanBufs );
		_name = new TextRef( owner, new TextRef() );
		_tooltip = new TextRef( owner, new TextRef() );
		_category.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
	}

	public GuildShopTab()
	{
		Initialize( GetOwner() );
	}

	public GuildShopTab( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GuildShopTab( DBResource owner, GuildShopTab source )
		: this(owner, source, true){}

	protected GuildShopTab( DBResource owner, GuildShopTab source, bool fireEvent )
	{
		_category = new UndoRedo<GuildShopCategoryType>( owner, source.category );
		_name = new TextRef( owner, source.name );
		_tooltip = new TextRef( owner, source.tooltip );
		_category.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GuildShopTab source = _source as GuildShopTab;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildShopTab" );
		category = source.category;
		name = source.name;
		tooltip = source.tooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GuildShopTab newParent = _newParent as GuildShopTab;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_category.SetParent( newParent == null ? null : newParent._category );
		_name.SetParent( newParent == null ? null : newParent._name );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_category.Reset();
		_name.Reset();
		_tooltip.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_category.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "category" )
			_category.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "category" )
			return _category.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class HeroTitle : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HeroTitle __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _maleName;
	private TextRef _femaleName;
	private TextRef _tooltip;
	private UndoRedoDBPtr<Texture> _image;
	private UndoRedo<float> _score;

	public TextRef maleName { get { return _maleName; } set { _maleName.Assign( value ); } }

	public TextRef femaleName { get { return _femaleName; } set { _femaleName.Assign( value ); } }

	[Description( "Tooltip for final statistics" )]
	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Description( "Icon image" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	public float score { get { return _score.Get(); } set { _score.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_maleName = new TextRef( owner, new TextRef() );
		_femaleName = new TextRef( owner, new TextRef() );
		_tooltip = new TextRef( owner, new TextRef() );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_score = new UndoRedo<float>( owner, 0.0f );
		_maleName.Changed += FireChangedEvent;
		_femaleName.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_score.Changed += FireChangedEvent;
	}

	public HeroTitle()
	{
		Initialize( GetOwner() );
	}

	public HeroTitle( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HeroTitle( DBResource owner, HeroTitle source )
		: this(owner, source, true){}

	protected HeroTitle( DBResource owner, HeroTitle source, bool fireEvent )
	{
		_maleName = new TextRef( owner, source.maleName );
		_femaleName = new TextRef( owner, source.femaleName );
		_tooltip = new TextRef( owner, source.tooltip );
		_image = new UndoRedoDBPtr<Texture>( owner, source.image );
		_score = new UndoRedo<float>( owner, source.score );
		_maleName.Changed += FireChangedEvent;
		_femaleName.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_score.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HeroTitle source = _source as HeroTitle;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroTitle" );
		maleName = source.maleName;
		femaleName = source.femaleName;
		tooltip = source.tooltip;
		image = source.image;
		score = source.score;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HeroTitle newParent = _newParent as HeroTitle;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_maleName.SetParent( newParent == null ? null : newParent._maleName );
		_femaleName.SetParent( newParent == null ? null : newParent._femaleName );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_image.SetParent( newParent == null ? null : newParent._image );
		_score.SetParent( newParent == null ? null : newParent._score );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_maleName.Reset();
		_femaleName.Reset();
		_tooltip.Reset();
		_image.Reset();
		_score.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_maleName.IsDerivedFromParent()
			&& _femaleName.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _score.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "maleName" )
			_maleName.Reset();
		else if ( fieldName == "femaleName" )
			_femaleName.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "score" )
			_score.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "maleName" )
			return _maleName.IsDerivedFromParent();
		if ( fieldName == "femaleName" )
			return _femaleName.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "score" )
			return _score.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("id")]
public class Hint : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Hint __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _id;
	private TextRef _text;

	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_id = new UndoRedo<string>( owner, string.Empty );
		_text = new TextRef( owner, new TextRef() );
		_id.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
	}

	public Hint()
	{
		Initialize( GetOwner() );
	}

	public Hint( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Hint( DBResource owner, Hint source )
		: this(owner, source, true){}

	protected Hint( DBResource owner, Hint source, bool fireEvent )
	{
		_id = new UndoRedo<string>( owner, source.id );
		_text = new TextRef( owner, source.text );
		_id.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Hint source = _source as Hint;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Hint" );
		id = source.id;
		text = source.text;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Hint newParent = _newParent as Hint;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_id.SetParent( newParent == null ? null : newParent._id );
		_text.SetParent( newParent == null ? null : newParent._text );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_id.Reset();
		_text.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _text.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "text" )
			_text.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("id")]
public class HintImage : Hint, libdb.ICompositeDBValue, libdb.IChangeable
{

	private HintImage __parent = null;

	private UndoRedoDBPtr<Texture> _image;

	[Description( "Картинка диалога" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_image = new UndoRedoDBPtr<Texture>( owner );
		_image.Changed += FireChangedEvent;
	}

	public HintImage()
	{
		Initialize( GetOwner() );
	}

	public HintImage( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public HintImage( DBResource owner, HintImage source ): base(owner, source, false)
	{
		_image = new UndoRedoDBPtr<Texture>( owner, source.image );
		_image.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		HintImage source = _source as HintImage;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HintImage" );

		base.Assign( source );

		image = source.image;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		HintImage newParent = _newParent as HintImage;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_image.SetParent( newParent == null ? null : newParent._image );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_image.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_image.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "image" )
			_image.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class Binds : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Binds __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<HotkeyBind> _bindList;

	[Description( "список видимых биндов для пользователя" )]
	public libdb.IChangeableList<HotkeyBind> bindList { get { return _bindList; } set { _bindList.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_bindList = new UndoRedoAssignableList<HotkeyBind>( owner );
		_bindList.Changed += FireChangedEvent;
	}

	public Binds()
	{
		Initialize( GetOwner() );
	}

	public Binds( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Binds( DBResource owner, Binds source )
		: this(owner, source, true){}

	protected Binds( DBResource owner, Binds source, bool fireEvent )
	{
		_bindList = new UndoRedoAssignableList<HotkeyBind>( owner );
		_bindList.Assign( source.bindList );
		_bindList.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Binds source = _source as Binds;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Binds" );
		bindList = source.bindList;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Binds newParent = _newParent as Binds;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_bindList.SetParent( newParent == null ? null : newParent._bindList );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_bindList.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_bindList.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "bindList" )
			_bindList.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "bindList" )
			return _bindList.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class IgnoreListParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private IgnoreListParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _outOfIgnorePlace;

	[Description( "out of ignore place" )]
	public TextRef outOfIgnorePlace { get { return _outOfIgnorePlace; } set { _outOfIgnorePlace.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_outOfIgnorePlace = new TextRef( owner, new TextRef() );
		_outOfIgnorePlace.Changed += FireChangedEvent;
	}

	public IgnoreListParams()
	{
		Initialize( GetOwner() );
	}

	public IgnoreListParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public IgnoreListParams( DBResource owner, IgnoreListParams source )
		: this(owner, source, true){}

	protected IgnoreListParams( DBResource owner, IgnoreListParams source, bool fireEvent )
	{
		_outOfIgnorePlace = new TextRef( owner, source.outOfIgnorePlace );
		_outOfIgnorePlace.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		IgnoreListParams source = _source as IgnoreListParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for IgnoreListParams" );
		outOfIgnorePlace = source.outOfIgnorePlace;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		IgnoreListParams newParent = _newParent as IgnoreListParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_outOfIgnorePlace.SetParent( newParent == null ? null : newParent._outOfIgnorePlace );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_outOfIgnorePlace.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_outOfIgnorePlace.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "outOfIgnorePlace" )
			_outOfIgnorePlace.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "outOfIgnorePlace" )
			return _outOfIgnorePlace.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class ImpulsiveBuffsParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ImpulsiveBuffsParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _minLifeTime;
	private UndoRedo<float> _maxLifeTime;
	private UndoRedo<float> _normalBlendTime;
	private UndoRedo<float> _fastBlendTime;
	private UndoRedo<float> _cancelDelay;

	public float minLifeTime { get { return _minLifeTime.Get(); } set { _minLifeTime.Set( value ); } }

	public float maxLifeTime { get { return _maxLifeTime.Get(); } set { _maxLifeTime.Set( value ); } }

	public float normalBlendTime { get { return _normalBlendTime.Get(); } set { _normalBlendTime.Set( value ); } }

	public float fastBlendTime { get { return _fastBlendTime.Get(); } set { _fastBlendTime.Set( value ); } }

	public float cancelDelay { get { return _cancelDelay.Get(); } set { _cancelDelay.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_minLifeTime = new UndoRedo<float>( owner, 0.0f );
		_maxLifeTime = new UndoRedo<float>( owner, 0.0f );
		_normalBlendTime = new UndoRedo<float>( owner, 0.0f );
		_fastBlendTime = new UndoRedo<float>( owner, 0.0f );
		_cancelDelay = new UndoRedo<float>( owner, 0.0f );
		_minLifeTime.Changed += FireChangedEvent;
		_maxLifeTime.Changed += FireChangedEvent;
		_normalBlendTime.Changed += FireChangedEvent;
		_fastBlendTime.Changed += FireChangedEvent;
		_cancelDelay.Changed += FireChangedEvent;
	}

	public ImpulsiveBuffsParams()
	{
		Initialize( GetOwner() );
	}

	public ImpulsiveBuffsParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ImpulsiveBuffsParams( DBResource owner, ImpulsiveBuffsParams source )
		: this(owner, source, true){}

	protected ImpulsiveBuffsParams( DBResource owner, ImpulsiveBuffsParams source, bool fireEvent )
	{
		_minLifeTime = new UndoRedo<float>( owner, source.minLifeTime );
		_maxLifeTime = new UndoRedo<float>( owner, source.maxLifeTime );
		_normalBlendTime = new UndoRedo<float>( owner, source.normalBlendTime );
		_fastBlendTime = new UndoRedo<float>( owner, source.fastBlendTime );
		_cancelDelay = new UndoRedo<float>( owner, source.cancelDelay );
		_minLifeTime.Changed += FireChangedEvent;
		_maxLifeTime.Changed += FireChangedEvent;
		_normalBlendTime.Changed += FireChangedEvent;
		_fastBlendTime.Changed += FireChangedEvent;
		_cancelDelay.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ImpulsiveBuffsParams source = _source as ImpulsiveBuffsParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ImpulsiveBuffsParams" );
		minLifeTime = source.minLifeTime;
		maxLifeTime = source.maxLifeTime;
		normalBlendTime = source.normalBlendTime;
		fastBlendTime = source.fastBlendTime;
		cancelDelay = source.cancelDelay;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ImpulsiveBuffsParams newParent = _newParent as ImpulsiveBuffsParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minLifeTime.SetParent( newParent == null ? null : newParent._minLifeTime );
		_maxLifeTime.SetParent( newParent == null ? null : newParent._maxLifeTime );
		_normalBlendTime.SetParent( newParent == null ? null : newParent._normalBlendTime );
		_fastBlendTime.SetParent( newParent == null ? null : newParent._fastBlendTime );
		_cancelDelay.SetParent( newParent == null ? null : newParent._cancelDelay );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minLifeTime.Reset();
		_maxLifeTime.Reset();
		_normalBlendTime.Reset();
		_fastBlendTime.Reset();
		_cancelDelay.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minLifeTime.IsDerivedFromParent()
			&& _maxLifeTime.IsDerivedFromParent()
			&& _normalBlendTime.IsDerivedFromParent()
			&& _fastBlendTime.IsDerivedFromParent()
			&& _cancelDelay.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minLifeTime" )
			_minLifeTime.Reset();
		else if ( fieldName == "maxLifeTime" )
			_maxLifeTime.Reset();
		else if ( fieldName == "normalBlendTime" )
			_normalBlendTime.Reset();
		else if ( fieldName == "fastBlendTime" )
			_fastBlendTime.Reset();
		else if ( fieldName == "cancelDelay" )
			_cancelDelay.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minLifeTime" )
			return _minLifeTime.IsDerivedFromParent();
		if ( fieldName == "maxLifeTime" )
			return _maxLifeTime.IsDerivedFromParent();
		if ( fieldName == "normalBlendTime" )
			return _normalBlendTime.IsDerivedFromParent();
		if ( fieldName == "fastBlendTime" )
			return _fastBlendTime.IsDerivedFromParent();
		if ( fieldName == "cancelDelay" )
			return _cancelDelay.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class Locale : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Locale __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _locale;
	private TextRef _tooltip;
	private UndoRedoDBPtr<Texture> _localeImage;

	public string locale { get { return _locale.Get(); } set { _locale.Set( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	public DBPtr<Texture> localeImage { get { return _localeImage.Get(); } set { _localeImage.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_locale = new UndoRedo<string>( owner, string.Empty );
		_tooltip = new TextRef( owner, new TextRef() );
		_localeImage = new UndoRedoDBPtr<Texture>( owner );
		_locale.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_localeImage.Changed += FireChangedEvent;
	}

	public Locale()
	{
		Initialize( GetOwner() );
	}

	public Locale( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Locale( DBResource owner, Locale source )
		: this(owner, source, true){}

	protected Locale( DBResource owner, Locale source, bool fireEvent )
	{
		_locale = new UndoRedo<string>( owner, source.locale );
		_tooltip = new TextRef( owner, source.tooltip );
		_localeImage = new UndoRedoDBPtr<Texture>( owner, source.localeImage );
		_locale.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_localeImage.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Locale source = _source as Locale;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Locale" );
		locale = source.locale;
		tooltip = source.tooltip;
		localeImage = source.localeImage;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Locale newParent = _newParent as Locale;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_locale.SetParent( newParent == null ? null : newParent._locale );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_localeImage.SetParent( newParent == null ? null : newParent._localeImage );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_locale.Reset();
		_tooltip.Reset();
		_localeImage.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_locale.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _localeImage.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "locale" )
			_locale.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "localeImage" )
			_localeImage.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "locale" )
			return _locale.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "localeImage" )
			return _localeImage.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class MapModeCustomDescriptions : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MapModeCustomDescriptions __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<AdvMapModeDescription> _maneuvers;
	private UndoRedoDBPtr<AdvMapModeDescription> _guardBattle;
	private UndoRedoDBPtr<AdvMapModeDescription> _guildBattle;
	private UndoRedoDBPtr<AdvMapModeDescription> _customBattle;

	public DBPtr<AdvMapModeDescription> maneuvers { get { return _maneuvers.Get(); } set { _maneuvers.Set( value ); } }

	public DBPtr<AdvMapModeDescription> guardBattle { get { return _guardBattle.Get(); } set { _guardBattle.Set( value ); } }

	public DBPtr<AdvMapModeDescription> guildBattle { get { return _guildBattle.Get(); } set { _guildBattle.Set( value ); } }

	[Description( "описание иконки договорных боев" )]
	public DBPtr<AdvMapModeDescription> customBattle { get { return _customBattle.Get(); } set { _customBattle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_maneuvers = new UndoRedoDBPtr<AdvMapModeDescription>( owner );
		_guardBattle = new UndoRedoDBPtr<AdvMapModeDescription>( owner );
		_guildBattle = new UndoRedoDBPtr<AdvMapModeDescription>( owner );
		_customBattle = new UndoRedoDBPtr<AdvMapModeDescription>( owner );
		_maneuvers.Changed += FireChangedEvent;
		_guardBattle.Changed += FireChangedEvent;
		_guildBattle.Changed += FireChangedEvent;
		_customBattle.Changed += FireChangedEvent;
	}

	public MapModeCustomDescriptions()
	{
		Initialize( GetOwner() );
	}

	public MapModeCustomDescriptions( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MapModeCustomDescriptions( DBResource owner, MapModeCustomDescriptions source )
		: this(owner, source, true){}

	protected MapModeCustomDescriptions( DBResource owner, MapModeCustomDescriptions source, bool fireEvent )
	{
		_maneuvers = new UndoRedoDBPtr<AdvMapModeDescription>( owner, source.maneuvers );
		_guardBattle = new UndoRedoDBPtr<AdvMapModeDescription>( owner, source.guardBattle );
		_guildBattle = new UndoRedoDBPtr<AdvMapModeDescription>( owner, source.guildBattle );
		_customBattle = new UndoRedoDBPtr<AdvMapModeDescription>( owner, source.customBattle );
		_maneuvers.Changed += FireChangedEvent;
		_guardBattle.Changed += FireChangedEvent;
		_guildBattle.Changed += FireChangedEvent;
		_customBattle.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MapModeCustomDescriptions source = _source as MapModeCustomDescriptions;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MapModeCustomDescriptions" );
		maneuvers = source.maneuvers;
		guardBattle = source.guardBattle;
		guildBattle = source.guildBattle;
		customBattle = source.customBattle;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MapModeCustomDescriptions newParent = _newParent as MapModeCustomDescriptions;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_maneuvers.SetParent( newParent == null ? null : newParent._maneuvers );
		_guardBattle.SetParent( newParent == null ? null : newParent._guardBattle );
		_guildBattle.SetParent( newParent == null ? null : newParent._guildBattle );
		_customBattle.SetParent( newParent == null ? null : newParent._customBattle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_maneuvers.Reset();
		_guardBattle.Reset();
		_guildBattle.Reset();
		_customBattle.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_maneuvers.IsDerivedFromParent()
			&& _guardBattle.IsDerivedFromParent()
			&& _guildBattle.IsDerivedFromParent()
			&& _customBattle.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "maneuvers" )
			_maneuvers.Reset();
		else if ( fieldName == "guardBattle" )
			_guardBattle.Reset();
		else if ( fieldName == "guildBattle" )
			_guildBattle.Reset();
		else if ( fieldName == "customBattle" )
			_customBattle.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "maneuvers" )
			return _maneuvers.IsDerivedFromParent();
		if ( fieldName == "guardBattle" )
			return _guardBattle.IsDerivedFromParent();
		if ( fieldName == "guildBattle" )
			return _guildBattle.IsDerivedFromParent();
		if ( fieldName == "customBattle" )
			return _customBattle.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class MarkerSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MarkerSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _duration;
	private UndoRedo<float> _otherMarkersCheckRange;

	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	public float otherMarkersCheckRange { get { return _otherMarkersCheckRange.Get(); } set { _otherMarkersCheckRange.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_duration = new UndoRedo<float>( owner, 10.0f );
		_otherMarkersCheckRange = new UndoRedo<float>( owner, 100.0f );
		_duration.Changed += FireChangedEvent;
		_otherMarkersCheckRange.Changed += FireChangedEvent;
	}

	public MarkerSettings()
	{
		Initialize( GetOwner() );
	}

	public MarkerSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MarkerSettings( DBResource owner, MarkerSettings source )
		: this(owner, source, true){}

	protected MarkerSettings( DBResource owner, MarkerSettings source, bool fireEvent )
	{
		_duration = new UndoRedo<float>( owner, source.duration );
		_otherMarkersCheckRange = new UndoRedo<float>( owner, source.otherMarkersCheckRange );
		_duration.Changed += FireChangedEvent;
		_otherMarkersCheckRange.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MarkerSettings source = _source as MarkerSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MarkerSettings" );
		duration = source.duration;
		otherMarkersCheckRange = source.otherMarkersCheckRange;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MarkerSettings newParent = _newParent as MarkerSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_duration.SetParent( newParent == null ? null : newParent._duration );
		_otherMarkersCheckRange.SetParent( newParent == null ? null : newParent._otherMarkersCheckRange );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_duration.Reset();
		_otherMarkersCheckRange.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_duration.IsDerivedFromParent()
			&& _otherMarkersCheckRange.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "otherMarkersCheckRange" )
			_otherMarkersCheckRange.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "otherMarkersCheckRange" )
			return _otherMarkersCheckRange.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class PathMarkerColor : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PathMarkerColor __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private HDRColor _mul;
	private HDRColor _add;

	public HDRColor mul { get { return _mul; } set { _mul.Assign( value ); } }

	public HDRColor add { get { return _add; } set { _add.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		HDRColor __mul = new HDRColor(); // Construct default object for mul
		__mul.R = 1.0f;
		__mul.G = 1.0f;
		__mul.B = 1.0f;
		_mul = new HDRColor( owner, __mul );
		HDRColor __add = new HDRColor(); // Construct default object for add
		__add.R = 1.0f;
		__add.G = 1.0f;
		__add.B = 1.0f;
		_add = new HDRColor( owner, __add );
		_mul.Changed += FireChangedEvent;
		_add.Changed += FireChangedEvent;
	}

	public PathMarkerColor()
	{
		Initialize( GetOwner() );
	}

	public PathMarkerColor( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PathMarkerColor( DBResource owner, PathMarkerColor source )
		: this(owner, source, true){}

	protected PathMarkerColor( DBResource owner, PathMarkerColor source, bool fireEvent )
	{
		_mul = new HDRColor( owner, source.mul );
		_add = new HDRColor( owner, source.add );
		_mul.Changed += FireChangedEvent;
		_add.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PathMarkerColor source = _source as PathMarkerColor;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PathMarkerColor" );
		mul = source.mul;
		add = source.add;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PathMarkerColor newParent = _newParent as PathMarkerColor;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_mul.SetParent( newParent == null ? null : newParent._mul );
		_add.SetParent( newParent == null ? null : newParent._add );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_mul.Reset();
		_add.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_mul.IsDerivedFromParent()
			&& _add.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "mul" )
			_mul.Reset();
		else if ( fieldName == "add" )
			_add.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "mul" )
			return _mul.IsDerivedFromParent();
		if ( fieldName == "add" )
			return _add.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("caption")]
public class Phrase : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Phrase __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Actor> _actorMale;
	private UndoRedoDBPtr<Actor> _actorFemale;
	private TextRef _textMale;
	private TextRef _textFemale;
	private Color _colorTextMale;
	private Color _colorTextFemale;
	private DBFMODEventDesc _soundMale;
	private DBFMODEventDesc _soundFemale;
	private UndoRedo<string> _socialSoundMale;
	private UndoRedo<string> _socialSoundFemale;
	private UndoRedo<float> _duration;
	private UndoRedo<string> _scriptName;
	private UndoRedo<PhraseTerminateEvent> _terminate;
	private UndoRedo<PortretOrientation> _orientation;
	private UndoRedo<string> _caption;
	private UndoRedoAssignableList<HintImage> _hintImages;

	[Description( "Говорящий" )]
	public DBPtr<Actor> actorMale { get { return _actorMale.Get(); } set { _actorMale.Set( value ); } }

	[Description( "Говорящий" )]
	public DBPtr<Actor> actorFemale { get { return _actorFemale.Get(); } set { _actorFemale.Set( value ); } }

	[Description( "Текст реплики" )]
	public TextRef textMale { get { return _textMale; } set { _textMale.Assign( value ); } }

	[Description( "Текст реплики" )]
	public TextRef textFemale { get { return _textFemale; } set { _textFemale.Assign( value ); } }

	[Description( "Цвет текста textMale" )]
	public Color colorTextMale { get { return _colorTextMale; } set { _colorTextMale.Assign( value ); } }

	[Description( "Цвет текста textFemale" )]
	public Color colorTextFemale { get { return _colorTextFemale; } set { _colorTextFemale.Assign( value ); } }

	[Description( "Звук реплики." )]
	public DBFMODEventDesc soundMale { get { return _soundMale; } set { _soundMale.Assign( value ); } }

	[Description( "Звук реплики." )]
	public DBFMODEventDesc soundFemale { get { return _soundFemale; } set { _soundFemale.Assign( value ); } }

	[Description( "Звук реплики. Указывается как путь относительно Resources/Sound без расширения" )]
	public string socialSoundMale { get { return _socialSoundMale.Get(); } set { _socialSoundMale.Set( value ); } }

	[Description( "Звук реплики Указывается как путь относительно Resources/Sound без расширения" )]
	public string socialSoundFemale { get { return _socialSoundFemale.Get(); } set { _socialSoundFemale.Set( value ); } }

	[Description( "Время реплики. Работает только для terminate = Time или TimeAndKey. Если -1 - совпадает с длительностью звука" )]
	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	[Description( "Символьное имя для ссылок из скриптов (сессия). В замке поле не используется" )]
	public string scriptName { get { return _scriptName.Get(); } set { _scriptName.Set( value ); } }

	[Description( "Событие по которому можно закончить реплику" )]
	public PhraseTerminateEvent terminate { get { return _terminate.Get(); } set { _terminate.Set( value ); } }

	[Description( "Ориентация портрета в реплике, используется в замке" )]
	public PortretOrientation orientation { get { return _orientation.Get(); } set { _orientation.Set( value ); } }

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	[Description( "Коллекция картинок для отображения в диалоговом окне" )]
	public libdb.IChangeableList<HintImage> hintImages { get { return _hintImages; } set { _hintImages.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_actorMale = new UndoRedoDBPtr<Actor>( owner );
		_actorFemale = new UndoRedoDBPtr<Actor>( owner );
		_textMale = new TextRef( owner, new TextRef() );
		_textFemale = new TextRef( owner, new TextRef() );
		Color __colorTextMale = new Color(); // Construct default object for colorTextMale
		__colorTextMale.R = 249;
		__colorTextMale.G = 216;
		__colorTextMale.B = 122;
		_colorTextMale = new Color( owner, __colorTextMale );
		Color __colorTextFemale = new Color(); // Construct default object for colorTextFemale
		__colorTextFemale.R = 249;
		__colorTextFemale.G = 216;
		__colorTextFemale.B = 122;
		_colorTextFemale = new Color( owner, __colorTextFemale );
		_soundMale = new DBFMODEventDesc( owner );
		_soundFemale = new DBFMODEventDesc( owner );
		_socialSoundMale = new UndoRedo<string>( owner, string.Empty );
		_socialSoundFemale = new UndoRedo<string>( owner, string.Empty );
		_duration = new UndoRedo<float>( owner, -1.0f );
		_scriptName = new UndoRedo<string>( owner, string.Empty );
		_terminate = new UndoRedo<PhraseTerminateEvent>( owner, PhraseTerminateEvent.Time );
		_orientation = new UndoRedo<PortretOrientation>( owner, PortretOrientation.Left );
		_caption = new UndoRedo<string>( owner, string.Empty );
		_hintImages = new UndoRedoAssignableList<HintImage>( owner );
		_actorMale.Changed += FireChangedEvent;
		_actorFemale.Changed += FireChangedEvent;
		_textMale.Changed += FireChangedEvent;
		_textFemale.Changed += FireChangedEvent;
		_colorTextMale.Changed += FireChangedEvent;
		_colorTextFemale.Changed += FireChangedEvent;
		_soundMale.Changed += FireChangedEvent;
		_soundFemale.Changed += FireChangedEvent;
		_socialSoundMale.Changed += FireChangedEvent;
		_socialSoundFemale.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_scriptName.Changed += FireChangedEvent;
		_terminate.Changed += FireChangedEvent;
		_orientation.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_hintImages.Changed += FireChangedEvent;
	}

	public Phrase()
	{
		Initialize( GetOwner() );
	}

	public Phrase( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Phrase( DBResource owner, Phrase source )
		: this(owner, source, true){}

	protected Phrase( DBResource owner, Phrase source, bool fireEvent )
	{
		_actorMale = new UndoRedoDBPtr<Actor>( owner, source.actorMale );
		_actorFemale = new UndoRedoDBPtr<Actor>( owner, source.actorFemale );
		_textMale = new TextRef( owner, source.textMale );
		_textFemale = new TextRef( owner, source.textFemale );
		_colorTextMale = new Color( owner, source.colorTextMale );
		_colorTextFemale = new Color( owner, source.colorTextFemale );
		_soundMale = new DBFMODEventDesc( owner, source.soundMale );
		_soundFemale = new DBFMODEventDesc( owner, source.soundFemale );
		_socialSoundMale = new UndoRedo<string>( owner, source.socialSoundMale );
		_socialSoundFemale = new UndoRedo<string>( owner, source.socialSoundFemale );
		_duration = new UndoRedo<float>( owner, source.duration );
		_scriptName = new UndoRedo<string>( owner, source.scriptName );
		_terminate = new UndoRedo<PhraseTerminateEvent>( owner, source.terminate );
		_orientation = new UndoRedo<PortretOrientation>( owner, source.orientation );
		_caption = new UndoRedo<string>( owner, source.caption );
		_hintImages = new UndoRedoAssignableList<HintImage>( owner );
		_hintImages.Assign( source.hintImages );
		_actorMale.Changed += FireChangedEvent;
		_actorFemale.Changed += FireChangedEvent;
		_textMale.Changed += FireChangedEvent;
		_textFemale.Changed += FireChangedEvent;
		_colorTextMale.Changed += FireChangedEvent;
		_colorTextFemale.Changed += FireChangedEvent;
		_soundMale.Changed += FireChangedEvent;
		_soundFemale.Changed += FireChangedEvent;
		_socialSoundMale.Changed += FireChangedEvent;
		_socialSoundFemale.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_scriptName.Changed += FireChangedEvent;
		_terminate.Changed += FireChangedEvent;
		_orientation.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_hintImages.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Phrase source = _source as Phrase;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Phrase" );
		actorMale = source.actorMale;
		actorFemale = source.actorFemale;
		textMale = source.textMale;
		textFemale = source.textFemale;
		colorTextMale = source.colorTextMale;
		colorTextFemale = source.colorTextFemale;
		soundMale = source.soundMale;
		soundFemale = source.soundFemale;
		socialSoundMale = source.socialSoundMale;
		socialSoundFemale = source.socialSoundFemale;
		duration = source.duration;
		scriptName = source.scriptName;
		terminate = source.terminate;
		orientation = source.orientation;
		caption = source.caption;
		hintImages = source.hintImages;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Phrase newParent = _newParent as Phrase;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_actorMale.SetParent( newParent == null ? null : newParent._actorMale );
		_actorFemale.SetParent( newParent == null ? null : newParent._actorFemale );
		_textMale.SetParent( newParent == null ? null : newParent._textMale );
		_textFemale.SetParent( newParent == null ? null : newParent._textFemale );
		_colorTextMale.SetParent( newParent == null ? null : newParent._colorTextMale );
		_colorTextFemale.SetParent( newParent == null ? null : newParent._colorTextFemale );
		_soundMale.SetParent( newParent == null ? null : newParent._soundMale );
		_soundFemale.SetParent( newParent == null ? null : newParent._soundFemale );
		_socialSoundMale.SetParent( newParent == null ? null : newParent._socialSoundMale );
		_socialSoundFemale.SetParent( newParent == null ? null : newParent._socialSoundFemale );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_scriptName.SetParent( newParent == null ? null : newParent._scriptName );
		_terminate.SetParent( newParent == null ? null : newParent._terminate );
		_orientation.SetParent( newParent == null ? null : newParent._orientation );
		_caption.SetParent( newParent == null ? null : newParent._caption );
		_hintImages.SetParent( newParent == null ? null : newParent._hintImages );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_actorMale.Reset();
		_actorFemale.Reset();
		_textMale.Reset();
		_textFemale.Reset();
		_colorTextMale.Reset();
		_colorTextFemale.Reset();
		_soundMale.Reset();
		_soundFemale.Reset();
		_socialSoundMale.Reset();
		_socialSoundFemale.Reset();
		_duration.Reset();
		_scriptName.Reset();
		_terminate.Reset();
		_orientation.Reset();
		_caption.Reset();
		_hintImages.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_actorMale.IsDerivedFromParent()
			&& _actorFemale.IsDerivedFromParent()
			&& _textMale.IsDerivedFromParent()
			&& _textFemale.IsDerivedFromParent()
			&& _colorTextMale.IsDerivedFromParent()
			&& _colorTextFemale.IsDerivedFromParent()
			&& _soundMale.IsDerivedFromParent()
			&& _soundFemale.IsDerivedFromParent()
			&& _socialSoundMale.IsDerivedFromParent()
			&& _socialSoundFemale.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _scriptName.IsDerivedFromParent()
			&& _terminate.IsDerivedFromParent()
			&& _orientation.IsDerivedFromParent()
			&& _caption.IsDerivedFromParent()
			&& _hintImages.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "actorMale" )
			_actorMale.Reset();
		else if ( fieldName == "actorFemale" )
			_actorFemale.Reset();
		else if ( fieldName == "textMale" )
			_textMale.Reset();
		else if ( fieldName == "textFemale" )
			_textFemale.Reset();
		else if ( fieldName == "colorTextMale" )
			_colorTextMale.Reset();
		else if ( fieldName == "colorTextFemale" )
			_colorTextFemale.Reset();
		else if ( fieldName == "soundMale" )
			_soundMale.Reset();
		else if ( fieldName == "soundFemale" )
			_soundFemale.Reset();
		else if ( fieldName == "socialSoundMale" )
			_socialSoundMale.Reset();
		else if ( fieldName == "socialSoundFemale" )
			_socialSoundFemale.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "scriptName" )
			_scriptName.Reset();
		else if ( fieldName == "terminate" )
			_terminate.Reset();
		else if ( fieldName == "orientation" )
			_orientation.Reset();
		else if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "hintImages" )
			_hintImages.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "actorMale" )
			return _actorMale.IsDerivedFromParent();
		if ( fieldName == "actorFemale" )
			return _actorFemale.IsDerivedFromParent();
		if ( fieldName == "textMale" )
			return _textMale.IsDerivedFromParent();
		if ( fieldName == "textFemale" )
			return _textFemale.IsDerivedFromParent();
		if ( fieldName == "colorTextMale" )
			return _colorTextMale.IsDerivedFromParent();
		if ( fieldName == "colorTextFemale" )
			return _colorTextFemale.IsDerivedFromParent();
		if ( fieldName == "soundMale" )
			return _soundMale.IsDerivedFromParent();
		if ( fieldName == "soundFemale" )
			return _soundFemale.IsDerivedFromParent();
		if ( fieldName == "socialSoundMale" )
			return _socialSoundMale.IsDerivedFromParent();
		if ( fieldName == "socialSoundFemale" )
			return _socialSoundFemale.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "scriptName" )
			return _scriptName.IsDerivedFromParent();
		if ( fieldName == "terminate" )
			return _terminate.IsDerivedFromParent();
		if ( fieldName == "orientation" )
			return _orientation.IsDerivedFromParent();
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "hintImages" )
			return _hintImages.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class PingAbuseSettings : AbuseSettings, libdb.ICompositeDBValue, libdb.IChangeable
{

	private PingAbuseSettings __parent = null;


	private void Initialize( DBResource owner )
	{
	}

	public PingAbuseSettings()
	{
		Initialize( GetOwner() );
	}

	public PingAbuseSettings( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public PingAbuseSettings( DBResource owner, PingAbuseSettings source ): base(owner, source, false)
	{
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		PingAbuseSettings source = _source as PingAbuseSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PingAbuseSettings" );

		base.Assign( source );

		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		PingAbuseSettings newParent = _newParent as PingAbuseSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class PremiumVisualInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PremiumVisualInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _premiumTooltipAddition;

	[Description( "дописка к тултипу таланта полученному благодаря премиуму" )]
	public TextRef premiumTooltipAddition { get { return _premiumTooltipAddition; } set { _premiumTooltipAddition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_premiumTooltipAddition = new TextRef( owner, new TextRef() );
		_premiumTooltipAddition.Changed += FireChangedEvent;
	}

	public PremiumVisualInfo()
	{
		Initialize( GetOwner() );
	}

	public PremiumVisualInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PremiumVisualInfo( DBResource owner, PremiumVisualInfo source )
		: this(owner, source, true){}

	protected PremiumVisualInfo( DBResource owner, PremiumVisualInfo source, bool fireEvent )
	{
		_premiumTooltipAddition = new TextRef( owner, source.premiumTooltipAddition );
		_premiumTooltipAddition.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PremiumVisualInfo source = _source as PremiumVisualInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PremiumVisualInfo" );
		premiumTooltipAddition = source.premiumTooltipAddition;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PremiumVisualInfo newParent = _newParent as PremiumVisualInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_premiumTooltipAddition.SetParent( newParent == null ? null : newParent._premiumTooltipAddition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_premiumTooltipAddition.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_premiumTooltipAddition.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "premiumTooltipAddition" )
			_premiumTooltipAddition.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "premiumTooltipAddition" )
			return _premiumTooltipAddition.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class PWSoundEvents : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PWSoundEvents __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private DBFMODEventDesc _selection;
	private DBFMODEventDesc _targetCancelled;
	private DBFMODEventDesc _targetSelected;
	private DBFMODEventDesc _minimapSignal;
	private DBFMODEventDesc _chatMarker;

	[Description( "Unit selection sound" )]
	public DBFMODEventDesc selection { get { return _selection; } set { _selection.Assign( value ); } }

	[Description( "Target select cancelation sound" )]
	public DBFMODEventDesc targetCancelled { get { return _targetCancelled; } set { _targetCancelled.Assign( value ); } }

	[Description( "Target selection sound" )]
	public DBFMODEventDesc targetSelected { get { return _targetSelected; } set { _targetSelected.Assign( value ); } }

	[Description( "Minimap signal sound" )]
	public DBFMODEventDesc minimapSignal { get { return _minimapSignal; } set { _minimapSignal.Assign( value ); } }

	[Description( "Chat marker sound" )]
	public DBFMODEventDesc chatMarker { get { return _chatMarker; } set { _chatMarker.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_selection = new DBFMODEventDesc( owner );
		_targetCancelled = new DBFMODEventDesc( owner );
		_targetSelected = new DBFMODEventDesc( owner );
		_minimapSignal = new DBFMODEventDesc( owner );
		_chatMarker = new DBFMODEventDesc( owner );
		_selection.Changed += FireChangedEvent;
		_targetCancelled.Changed += FireChangedEvent;
		_targetSelected.Changed += FireChangedEvent;
		_minimapSignal.Changed += FireChangedEvent;
		_chatMarker.Changed += FireChangedEvent;
	}

	public PWSoundEvents()
	{
		Initialize( GetOwner() );
	}

	public PWSoundEvents( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PWSoundEvents( DBResource owner, PWSoundEvents source )
		: this(owner, source, true){}

	protected PWSoundEvents( DBResource owner, PWSoundEvents source, bool fireEvent )
	{
		_selection = new DBFMODEventDesc( owner, source.selection );
		_targetCancelled = new DBFMODEventDesc( owner, source.targetCancelled );
		_targetSelected = new DBFMODEventDesc( owner, source.targetSelected );
		_minimapSignal = new DBFMODEventDesc( owner, source.minimapSignal );
		_chatMarker = new DBFMODEventDesc( owner, source.chatMarker );
		_selection.Changed += FireChangedEvent;
		_targetCancelled.Changed += FireChangedEvent;
		_targetSelected.Changed += FireChangedEvent;
		_minimapSignal.Changed += FireChangedEvent;
		_chatMarker.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PWSoundEvents source = _source as PWSoundEvents;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PWSoundEvents" );
		selection = source.selection;
		targetCancelled = source.targetCancelled;
		targetSelected = source.targetSelected;
		minimapSignal = source.minimapSignal;
		chatMarker = source.chatMarker;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PWSoundEvents newParent = _newParent as PWSoundEvents;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_selection.SetParent( newParent == null ? null : newParent._selection );
		_targetCancelled.SetParent( newParent == null ? null : newParent._targetCancelled );
		_targetSelected.SetParent( newParent == null ? null : newParent._targetSelected );
		_minimapSignal.SetParent( newParent == null ? null : newParent._minimapSignal );
		_chatMarker.SetParent( newParent == null ? null : newParent._chatMarker );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_selection.Reset();
		_targetCancelled.Reset();
		_targetSelected.Reset();
		_minimapSignal.Reset();
		_chatMarker.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_selection.IsDerivedFromParent()
			&& _targetCancelled.IsDerivedFromParent()
			&& _targetSelected.IsDerivedFromParent()
			&& _minimapSignal.IsDerivedFromParent()
			&& _chatMarker.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "selection" )
			_selection.Reset();
		else if ( fieldName == "targetCancelled" )
			_targetCancelled.Reset();
		else if ( fieldName == "targetSelected" )
			_targetSelected.Reset();
		else if ( fieldName == "minimapSignal" )
			_minimapSignal.Reset();
		else if ( fieldName == "chatMarker" )
			_chatMarker.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "selection" )
			return _selection.IsDerivedFromParent();
		if ( fieldName == "targetCancelled" )
			return _targetCancelled.IsDerivedFromParent();
		if ( fieldName == "targetSelected" )
			return _targetSelected.IsDerivedFromParent();
		if ( fieldName == "minimapSignal" )
			return _minimapSignal.IsDerivedFromParent();
		if ( fieldName == "chatMarker" )
			return _chatMarker.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ReportType : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ReportType __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _name;
	private UndoRedo<int> _id;

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public int id { get { return _id.Get(); } set { _id.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new TextRef( owner, new TextRef() );
		_id = new UndoRedo<int>( owner, 0 );
		_name.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
	}

	public ReportType()
	{
		Initialize( GetOwner() );
	}

	public ReportType( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ReportType( DBResource owner, ReportType source )
		: this(owner, source, true){}

	protected ReportType( DBResource owner, ReportType source, bool fireEvent )
	{
		_name = new TextRef( owner, source.name );
		_id = new UndoRedo<int>( owner, source.id );
		_name.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ReportType source = _source as ReportType;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ReportType" );
		name = source.name;
		id = source.id;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ReportType newParent = _newParent as ReportType;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_id.SetParent( newParent == null ? null : newParent._id );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_id.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _id.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "id" )
			_id.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class ResourceDescription : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ResourceDescription __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _resourceTooltipFreeze;
	private TextRef _resourceTooltipBurn;
	private UndoRedoDBPtr<Texture> _imageFreeze;
	private UndoRedoDBPtr<Texture> _imageBurn;

	[Description( "tooltip for resource. NOTE: should not contain value tags Dohkt" )]
	public TextRef resourceTooltipFreeze { get { return _resourceTooltipFreeze; } set { _resourceTooltipFreeze.Assign( value ); } }

	[Description( "tooltip for resource. NOTE: should not contain value tags Adornians" )]
	public TextRef resourceTooltipBurn { get { return _resourceTooltipBurn; } set { _resourceTooltipBurn.Assign( value ); } }

	[Description( "image for resource Dohkt" )]
	public DBPtr<Texture> imageFreeze { get { return _imageFreeze.Get(); } set { _imageFreeze.Set( value ); } }

	[Description( "image for resource Adornians" )]
	public DBPtr<Texture> imageBurn { get { return _imageBurn.Get(); } set { _imageBurn.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_resourceTooltipFreeze = new TextRef( owner, new TextRef() );
		_resourceTooltipBurn = new TextRef( owner, new TextRef() );
		_imageFreeze = new UndoRedoDBPtr<Texture>( owner );
		_imageBurn = new UndoRedoDBPtr<Texture>( owner );
		_resourceTooltipFreeze.Changed += FireChangedEvent;
		_resourceTooltipBurn.Changed += FireChangedEvent;
		_imageFreeze.Changed += FireChangedEvent;
		_imageBurn.Changed += FireChangedEvent;
	}

	public ResourceDescription()
	{
		Initialize( GetOwner() );
	}

	public ResourceDescription( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ResourceDescription( DBResource owner, ResourceDescription source )
		: this(owner, source, true){}

	protected ResourceDescription( DBResource owner, ResourceDescription source, bool fireEvent )
	{
		_resourceTooltipFreeze = new TextRef( owner, source.resourceTooltipFreeze );
		_resourceTooltipBurn = new TextRef( owner, source.resourceTooltipBurn );
		_imageFreeze = new UndoRedoDBPtr<Texture>( owner, source.imageFreeze );
		_imageBurn = new UndoRedoDBPtr<Texture>( owner, source.imageBurn );
		_resourceTooltipFreeze.Changed += FireChangedEvent;
		_resourceTooltipBurn.Changed += FireChangedEvent;
		_imageFreeze.Changed += FireChangedEvent;
		_imageBurn.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ResourceDescription source = _source as ResourceDescription;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResourceDescription" );
		resourceTooltipFreeze = source.resourceTooltipFreeze;
		resourceTooltipBurn = source.resourceTooltipBurn;
		imageFreeze = source.imageFreeze;
		imageBurn = source.imageBurn;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ResourceDescription newParent = _newParent as ResourceDescription;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_resourceTooltipFreeze.SetParent( newParent == null ? null : newParent._resourceTooltipFreeze );
		_resourceTooltipBurn.SetParent( newParent == null ? null : newParent._resourceTooltipBurn );
		_imageFreeze.SetParent( newParent == null ? null : newParent._imageFreeze );
		_imageBurn.SetParent( newParent == null ? null : newParent._imageBurn );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_resourceTooltipFreeze.Reset();
		_resourceTooltipBurn.Reset();
		_imageFreeze.Reset();
		_imageBurn.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_resourceTooltipFreeze.IsDerivedFromParent()
			&& _resourceTooltipBurn.IsDerivedFromParent()
			&& _imageFreeze.IsDerivedFromParent()
			&& _imageBurn.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "resourceTooltipFreeze" )
			_resourceTooltipFreeze.Reset();
		else if ( fieldName == "resourceTooltipBurn" )
			_resourceTooltipBurn.Reset();
		else if ( fieldName == "imageFreeze" )
			_imageFreeze.Reset();
		else if ( fieldName == "imageBurn" )
			_imageBurn.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "resourceTooltipFreeze" )
			return _resourceTooltipFreeze.IsDerivedFromParent();
		if ( fieldName == "resourceTooltipBurn" )
			return _resourceTooltipBurn.IsDerivedFromParent();
		if ( fieldName == "imageFreeze" )
			return _imageFreeze.IsDerivedFromParent();
		if ( fieldName == "imageBurn" )
			return _imageBurn.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class DiscreteScoring : RestrictedScoring, libdb.ICompositeDBValue, libdb.IChangeable
{

	private DiscreteScoring __parent = null;

	private UndoRedo<int> _count;

	public int count { get { return _count.Get(); } set { _count.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_count = new UndoRedo<int>( owner, 0 );
		_count.Changed += FireChangedEvent;
	}

	public DiscreteScoring()
	{
		Initialize( GetOwner() );
	}

	public DiscreteScoring( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public DiscreteScoring( DBResource owner, DiscreteScoring source ): base(owner, source, false)
	{
		_count = new UndoRedo<int>( owner, source.count );
		_count.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		DiscreteScoring source = _source as DiscreteScoring;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DiscreteScoring" );

		base.Assign( source );

		count = source.count;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		DiscreteScoring newParent = _newParent as DiscreteScoring;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_count.SetParent( newParent == null ? null : newParent._count );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_count.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_count.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "count" )
			_count.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "count" )
			return _count.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class ScoreDescription : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ScoreDescription __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _name;
	private UndoRedoDBPtr<Texture> _icon;
	private UndoRedo<int> _outputPriority;

	[Description( "score name" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Description( "score icon" )]
	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Description( "output priority" )]
	public int outputPriority { get { return _outputPriority.Get(); } set { _outputPriority.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new TextRef( owner, new TextRef() );
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_outputPriority = new UndoRedo<int>( owner, 0 );
		_name.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_outputPriority.Changed += FireChangedEvent;
	}

	public ScoreDescription()
	{
		Initialize( GetOwner() );
	}

	public ScoreDescription( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ScoreDescription( DBResource owner, ScoreDescription source )
		: this(owner, source, true){}

	protected ScoreDescription( DBResource owner, ScoreDescription source, bool fireEvent )
	{
		_name = new TextRef( owner, source.name );
		_icon = new UndoRedoDBPtr<Texture>( owner, source.icon );
		_outputPriority = new UndoRedo<int>( owner, source.outputPriority );
		_name.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_outputPriority.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ScoreDescription source = _source as ScoreDescription;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScoreDescription" );
		name = source.name;
		icon = source.icon;
		outputPriority = source.outputPriority;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ScoreDescription newParent = _newParent as ScoreDescription;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_icon.SetParent( newParent == null ? null : newParent._icon );
		_outputPriority.SetParent( newParent == null ? null : newParent._outputPriority );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_icon.Reset();
		_outputPriority.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _icon.IsDerivedFromParent()
			&& _outputPriority.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "outputPriority" )
			_outputPriority.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "outputPriority" )
			return _outputPriority.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("id")]
public class SessionQuest : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SessionQuest __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _id;
	private TextRef _text;
	private UndoRedo<int> _counter;
	private UndoRedo<bool> _primary;

	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	public int counter { get { return _counter.Get(); } set { _counter.Set( value ); } }

	public bool primary { get { return _primary.Get(); } set { _primary.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_id = new UndoRedo<string>( owner, string.Empty );
		_text = new TextRef( owner, new TextRef() );
		_counter = new UndoRedo<int>( owner, 0 );
		_primary = new UndoRedo<bool>( owner, false );
		_id.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
		_counter.Changed += FireChangedEvent;
		_primary.Changed += FireChangedEvent;
	}

	public SessionQuest()
	{
		Initialize( GetOwner() );
	}

	public SessionQuest( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SessionQuest( DBResource owner, SessionQuest source )
		: this(owner, source, true){}

	protected SessionQuest( DBResource owner, SessionQuest source, bool fireEvent )
	{
		_id = new UndoRedo<string>( owner, source.id );
		_text = new TextRef( owner, source.text );
		_counter = new UndoRedo<int>( owner, source.counter );
		_primary = new UndoRedo<bool>( owner, source.primary );
		_id.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
		_counter.Changed += FireChangedEvent;
		_primary.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SessionQuest source = _source as SessionQuest;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionQuest" );
		id = source.id;
		text = source.text;
		counter = source.counter;
		primary = source.primary;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SessionQuest newParent = _newParent as SessionQuest;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_id.SetParent( newParent == null ? null : newParent._id );
		_text.SetParent( newParent == null ? null : newParent._text );
		_counter.SetParent( newParent == null ? null : newParent._counter );
		_primary.SetParent( newParent == null ? null : newParent._primary );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_id.Reset();
		_text.Reset();
		_counter.Reset();
		_primary.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _text.IsDerivedFromParent()
			&& _counter.IsDerivedFromParent()
			&& _primary.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "text" )
			_text.Reset();
		else if ( fieldName == "counter" )
			_counter.Reset();
		else if ( fieldName == "primary" )
			_primary.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		if ( fieldName == "counter" )
			return _counter.IsDerivedFromParent();
		if ( fieldName == "primary" )
			return _primary.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class SmartChatAbuseSettings : AbuseSettings, libdb.ICompositeDBValue, libdb.IChangeable
{

	private SmartChatAbuseSettings __parent = null;


	private void Initialize( DBResource owner )
	{
	}

	public SmartChatAbuseSettings()
	{
		Initialize( GetOwner() );
	}

	public SmartChatAbuseSettings( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public SmartChatAbuseSettings( DBResource owner, SmartChatAbuseSettings source ): base(owner, source, false)
	{
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		SmartChatAbuseSettings source = _source as SmartChatAbuseSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SmartChatAbuseSettings" );

		base.Assign( source );

		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		SmartChatAbuseSettings newParent = _newParent as SmartChatAbuseSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("stat")]
public class StatBudget : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StatBudget __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EStat> _stat;
	private UndoRedo<float> _budget;
	private UndoRedo<bool> _upgradesWithForce;

	public EStat stat { get { return _stat.Get(); } set { _stat.Set( value ); } }

	public float budget { get { return _budget.Get(); } set { _budget.Set( value ); } }

	[Description( "Растёт ли стат от мощи" )]
	public bool upgradesWithForce { get { return _upgradesWithForce.Get(); } set { _upgradesWithForce.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_stat = new UndoRedo<EStat>( owner, EStat.Life );
		_budget = new UndoRedo<float>( owner, 0.0f );
		_upgradesWithForce = new UndoRedo<bool>( owner, false );
		_stat.Changed += FireChangedEvent;
		_budget.Changed += FireChangedEvent;
		_upgradesWithForce.Changed += FireChangedEvent;
	}

	public StatBudget()
	{
		Initialize( GetOwner() );
	}

	public StatBudget( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StatBudget( DBResource owner, StatBudget source )
		: this(owner, source, true){}

	protected StatBudget( DBResource owner, StatBudget source, bool fireEvent )
	{
		_stat = new UndoRedo<EStat>( owner, source.stat );
		_budget = new UndoRedo<float>( owner, source.budget );
		_upgradesWithForce = new UndoRedo<bool>( owner, source.upgradesWithForce );
		_stat.Changed += FireChangedEvent;
		_budget.Changed += FireChangedEvent;
		_upgradesWithForce.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StatBudget source = _source as StatBudget;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatBudget" );
		stat = source.stat;
		budget = source.budget;
		upgradesWithForce = source.upgradesWithForce;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StatBudget newParent = _newParent as StatBudget;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_stat.SetParent( newParent == null ? null : newParent._stat );
		_budget.SetParent( newParent == null ? null : newParent._budget );
		_upgradesWithForce.SetParent( newParent == null ? null : newParent._upgradesWithForce );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_stat.Reset();
		_budget.Reset();
		_upgradesWithForce.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_stat.IsDerivedFromParent()
			&& _budget.IsDerivedFromParent()
			&& _upgradesWithForce.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "stat" )
			_stat.Reset();
		else if ( fieldName == "budget" )
			_budget.Reset();
		else if ( fieldName == "upgradesWithForce" )
			_upgradesWithForce.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "stat" )
			return _stat.IsDerivedFromParent();
		if ( fieldName == "budget" )
			return _budget.IsDerivedFromParent();
		if ( fieldName == "upgradesWithForce" )
			return _upgradesWithForce.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class StatEnhancer : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StatEnhancer __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EStat> _statId;
	private UndoRedo<float> _statAddModifier;
	private UndoRedo<float> _statMullModifier;
	private UndoRedo<float> _incrementAddModifier;
	private UndoRedo<float> _incrementMullModifier;

	public EStat statId { get { return _statId.Get(); } set { _statId.Set( value ); } }

	public float statAddModifier { get { return _statAddModifier.Get(); } set { _statAddModifier.Set( value ); } }

	public float statMullModifier { get { return _statMullModifier.Get(); } set { _statMullModifier.Set( value ); } }

	public float incrementAddModifier { get { return _incrementAddModifier.Get(); } set { _incrementAddModifier.Set( value ); } }

	public float incrementMullModifier { get { return _incrementMullModifier.Get(); } set { _incrementMullModifier.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_statId = new UndoRedo<EStat>( owner, EStat.Life );
		_statAddModifier = new UndoRedo<float>( owner, 0.0f );
		_statMullModifier = new UndoRedo<float>( owner, 1.0f );
		_incrementAddModifier = new UndoRedo<float>( owner, 0.0f );
		_incrementMullModifier = new UndoRedo<float>( owner, 1.0f );
		_statId.Changed += FireChangedEvent;
		_statAddModifier.Changed += FireChangedEvent;
		_statMullModifier.Changed += FireChangedEvent;
		_incrementAddModifier.Changed += FireChangedEvent;
		_incrementMullModifier.Changed += FireChangedEvent;
	}

	public StatEnhancer()
	{
		Initialize( GetOwner() );
	}

	public StatEnhancer( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StatEnhancer( DBResource owner, StatEnhancer source )
		: this(owner, source, true){}

	protected StatEnhancer( DBResource owner, StatEnhancer source, bool fireEvent )
	{
		_statId = new UndoRedo<EStat>( owner, source.statId );
		_statAddModifier = new UndoRedo<float>( owner, source.statAddModifier );
		_statMullModifier = new UndoRedo<float>( owner, source.statMullModifier );
		_incrementAddModifier = new UndoRedo<float>( owner, source.incrementAddModifier );
		_incrementMullModifier = new UndoRedo<float>( owner, source.incrementMullModifier );
		_statId.Changed += FireChangedEvent;
		_statAddModifier.Changed += FireChangedEvent;
		_statMullModifier.Changed += FireChangedEvent;
		_incrementAddModifier.Changed += FireChangedEvent;
		_incrementMullModifier.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StatEnhancer source = _source as StatEnhancer;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatEnhancer" );
		statId = source.statId;
		statAddModifier = source.statAddModifier;
		statMullModifier = source.statMullModifier;
		incrementAddModifier = source.incrementAddModifier;
		incrementMullModifier = source.incrementMullModifier;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StatEnhancer newParent = _newParent as StatEnhancer;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_statId.SetParent( newParent == null ? null : newParent._statId );
		_statAddModifier.SetParent( newParent == null ? null : newParent._statAddModifier );
		_statMullModifier.SetParent( newParent == null ? null : newParent._statMullModifier );
		_incrementAddModifier.SetParent( newParent == null ? null : newParent._incrementAddModifier );
		_incrementMullModifier.SetParent( newParent == null ? null : newParent._incrementMullModifier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_statId.Reset();
		_statAddModifier.Reset();
		_statMullModifier.Reset();
		_incrementAddModifier.Reset();
		_incrementMullModifier.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_statId.IsDerivedFromParent()
			&& _statAddModifier.IsDerivedFromParent()
			&& _statMullModifier.IsDerivedFromParent()
			&& _incrementAddModifier.IsDerivedFromParent()
			&& _incrementMullModifier.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "statId" )
			_statId.Reset();
		else if ( fieldName == "statAddModifier" )
			_statAddModifier.Reset();
		else if ( fieldName == "statMullModifier" )
			_statMullModifier.Reset();
		else if ( fieldName == "incrementAddModifier" )
			_incrementAddModifier.Reset();
		else if ( fieldName == "incrementMullModifier" )
			_incrementMullModifier.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "statId" )
			return _statId.IsDerivedFromParent();
		if ( fieldName == "statAddModifier" )
			return _statAddModifier.IsDerivedFromParent();
		if ( fieldName == "statMullModifier" )
			return _statMullModifier.IsDerivedFromParent();
		if ( fieldName == "incrementAddModifier" )
			return _incrementAddModifier.IsDerivedFromParent();
		if ( fieldName == "incrementMullModifier" )
			return _incrementMullModifier.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class StatParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StatParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _name;
	private UndoRedo<EVisualStyle> _visualStyle;
	private UndoRedo<EFormatType> _format;
	private UndoRedo<float> _defValue;

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public EVisualStyle visualStyle { get { return _visualStyle.Get(); } set { _visualStyle.Set( value ); } }

	public EFormatType format { get { return _format.Get(); } set { _format.Set( value ); } }

	public float defValue { get { return _defValue.Get(); } set { _defValue.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_name = new TextRef( owner, new TextRef() );
		_visualStyle = new UndoRedo<EVisualStyle>( owner, EVisualStyle.Always );
		_format = new UndoRedo<EFormatType>( owner, EFormatType.Integer );
		_defValue = new UndoRedo<float>( owner, 0.0f );
		_name.Changed += FireChangedEvent;
		_visualStyle.Changed += FireChangedEvent;
		_format.Changed += FireChangedEvent;
		_defValue.Changed += FireChangedEvent;
	}

	public StatParams()
	{
		Initialize( GetOwner() );
	}

	public StatParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StatParams( DBResource owner, StatParams source )
		: this(owner, source, true){}

	protected StatParams( DBResource owner, StatParams source, bool fireEvent )
	{
		_name = new TextRef( owner, source.name );
		_visualStyle = new UndoRedo<EVisualStyle>( owner, source.visualStyle );
		_format = new UndoRedo<EFormatType>( owner, source.format );
		_defValue = new UndoRedo<float>( owner, source.defValue );
		_name.Changed += FireChangedEvent;
		_visualStyle.Changed += FireChangedEvent;
		_format.Changed += FireChangedEvent;
		_defValue.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StatParams source = _source as StatParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatParams" );
		name = source.name;
		visualStyle = source.visualStyle;
		format = source.format;
		defValue = source.defValue;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StatParams newParent = _newParent as StatParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_name.SetParent( newParent == null ? null : newParent._name );
		_visualStyle.SetParent( newParent == null ? null : newParent._visualStyle );
		_format.SetParent( newParent == null ? null : newParent._format );
		_defValue.SetParent( newParent == null ? null : newParent._defValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_name.Reset();
		_visualStyle.Reset();
		_format.Reset();
		_defValue.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _visualStyle.IsDerivedFromParent()
			&& _format.IsDerivedFromParent()
			&& _defValue.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "visualStyle" )
			_visualStyle.Reset();
		else if ( fieldName == "format" )
			_format.Reset();
		else if ( fieldName == "defValue" )
			_defValue.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "visualStyle" )
			return _visualStyle.IsDerivedFromParent();
		if ( fieldName == "format" )
			return _format.IsDerivedFromParent();
		if ( fieldName == "defValue" )
			return _defValue.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class StatUpgrade : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StatUpgrade __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _level;
	private UndoRedo<float> _increment;

	public int level { get { return _level.Get(); } set { _level.Set( value ); } }

	public float increment { get { return _increment.Get(); } set { _increment.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_level = new UndoRedo<int>( owner, 0 );
		_increment = new UndoRedo<float>( owner, 0.0f );
		_level.Changed += FireChangedEvent;
		_increment.Changed += FireChangedEvent;
	}

	public StatUpgrade()
	{
		Initialize( GetOwner() );
	}

	public StatUpgrade( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StatUpgrade( DBResource owner, StatUpgrade source )
		: this(owner, source, true){}

	protected StatUpgrade( DBResource owner, StatUpgrade source, bool fireEvent )
	{
		_level = new UndoRedo<int>( owner, source.level );
		_increment = new UndoRedo<float>( owner, source.increment );
		_level.Changed += FireChangedEvent;
		_increment.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StatUpgrade source = _source as StatUpgrade;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatUpgrade" );
		level = source.level;
		increment = source.increment;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StatUpgrade newParent = _newParent as StatUpgrade;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_level.SetParent( newParent == null ? null : newParent._level );
		_increment.SetParent( newParent == null ? null : newParent._increment );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_level.Reset();
		_increment.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_level.IsDerivedFromParent()
			&& _increment.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "level" )
			_level.Reset();
		else if ( fieldName == "increment" )
			_increment.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "level" )
			return _level.IsDerivedFromParent();
		if ( fieldName == "increment" )
			return _increment.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class StringTextRefPair : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StringTextRefPair __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _key;
	private TextRef _text;

	public string key { get { return _key.Get(); } set { _key.Set( value ); } }

	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_key = new UndoRedo<string>( owner, string.Empty );
		_text = new TextRef( owner, new TextRef() );
		_key.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
	}

	public StringTextRefPair()
	{
		Initialize( GetOwner() );
	}

	public StringTextRefPair( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StringTextRefPair( DBResource owner, StringTextRefPair source )
		: this(owner, source, true){}

	protected StringTextRefPair( DBResource owner, StringTextRefPair source, bool fireEvent )
	{
		_key = new UndoRedo<string>( owner, source.key );
		_text = new TextRef( owner, source.text );
		_key.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StringTextRefPair source = _source as StringTextRefPair;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StringTextRefPair" );
		key = source.key;
		text = source.text;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StringTextRefPair newParent = _newParent as StringTextRefPair;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_key.SetParent( newParent == null ? null : newParent._key );
		_text.SetParent( newParent == null ? null : newParent._text );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_key.Reset();
		_text.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_key.IsDerivedFromParent()
			&& _text.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "key" )
			_key.Reset();
		else if ( fieldName == "text" )
			_text.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "key" )
			return _key.IsDerivedFromParent();
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class TeamInfTooltipSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TeamInfTooltipSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _heroTooltip;

	public TextRef heroTooltip { get { return _heroTooltip; } set { _heroTooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_heroTooltip = new TextRef( owner, new TextRef() );
		_heroTooltip.Changed += FireChangedEvent;
	}

	public TeamInfTooltipSettings()
	{
		Initialize( GetOwner() );
	}

	public TeamInfTooltipSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TeamInfTooltipSettings( DBResource owner, TeamInfTooltipSettings source )
		: this(owner, source, true){}

	protected TeamInfTooltipSettings( DBResource owner, TeamInfTooltipSettings source, bool fireEvent )
	{
		_heroTooltip = new TextRef( owner, source.heroTooltip );
		_heroTooltip.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TeamInfTooltipSettings source = _source as TeamInfTooltipSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TeamInfTooltipSettings" );
		heroTooltip = source.heroTooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TeamInfTooltipSettings newParent = _newParent as TeamInfTooltipSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_heroTooltip.SetParent( newParent == null ? null : newParent._heroTooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_heroTooltip.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_heroTooltip.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "heroTooltip" )
			_heroTooltip.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "heroTooltip" )
			return _heroTooltip.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class TipOfTheDay : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TipOfTheDay __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _tipText;

	public TextRef tipText { get { return _tipText; } set { _tipText.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_tipText = new TextRef( owner, new TextRef() );
		_tipText.Changed += FireChangedEvent;
	}

	public TipOfTheDay()
	{
		Initialize( GetOwner() );
	}

	public TipOfTheDay( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TipOfTheDay( DBResource owner, TipOfTheDay source )
		: this(owner, source, true){}

	protected TipOfTheDay( DBResource owner, TipOfTheDay source, bool fireEvent )
	{
		_tipText = new TextRef( owner, source.tipText );
		_tipText.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TipOfTheDay source = _source as TipOfTheDay;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TipOfTheDay" );
		tipText = source.tipText;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TipOfTheDay newParent = _newParent as TipOfTheDay;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_tipText.SetParent( newParent == null ? null : newParent._tipText );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_tipText.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_tipText.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "tipText" )
			_tipText.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "tipText" )
			return _tipText.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class UnitOvertipSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UnitOvertipSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<AdventureTooltipSettings> _ally;
	private UndoRedoDBPtr<AdventureTooltipSettings> _enemy;
	private UndoRedoDBPtr<AdventureTooltipSettings> _neutral;
	private UndoRedoDBPtr<AdventureTooltipSettings> _invulnerableAlly;
	private UndoRedoDBPtr<AdventureTooltipSettings> _invulnerableEnemy;
	private UndoRedoDBPtr<AdventureTooltipSettings> _localHero;
	private UndoRedoDBPtr<AdventureTooltipSettings> _localHeroSlave;
	private UndoRedoDBPtr<AdventureTooltipSettings> _invulnerableLocalHero;
	private UndoRedoDBPtr<AdventureTooltipSettings> _invulnerableLocalHeroSlave;

	[Description( "Overtip settings for ally units; The default ones" )]
	public DBPtr<AdventureTooltipSettings> ally { get { return _ally.Get(); } set { _ally.Set( value ); } }

	[Description( "Overtip settings for enemy units; If not set, then 'ally' settings will be used" )]
	public DBPtr<AdventureTooltipSettings> enemy { get { return _enemy.Get(); } set { _enemy.Set( value ); } }

	[Description( "Overtip settings for neutral units; If not set, then 'ally' settings will be used" )]
	public DBPtr<AdventureTooltipSettings> neutral { get { return _neutral.Get(); } set { _neutral.Set( value ); } }

	[Description( "Overtip settings for invulnerable ally units; If not set, then 'ally' settings will be used" )]
	public DBPtr<AdventureTooltipSettings> invulnerableAlly { get { return _invulnerableAlly.Get(); } set { _invulnerableAlly.Set( value ); } }

	[Description( "Overtip settings for invulnerable enemy units; If not set, then 'enemy' settings will be used" )]
	public DBPtr<AdventureTooltipSettings> invulnerableEnemy { get { return _invulnerableEnemy.Get(); } set { _invulnerableEnemy.Set( value ); } }

	public DBPtr<AdventureTooltipSettings> localHero { get { return _localHero.Get(); } set { _localHero.Set( value ); } }

	public DBPtr<AdventureTooltipSettings> localHeroSlave { get { return _localHeroSlave.Get(); } set { _localHeroSlave.Set( value ); } }

	public DBPtr<AdventureTooltipSettings> invulnerableLocalHero { get { return _invulnerableLocalHero.Get(); } set { _invulnerableLocalHero.Set( value ); } }

	public DBPtr<AdventureTooltipSettings> invulnerableLocalHeroSlave { get { return _invulnerableLocalHeroSlave.Get(); } set { _invulnerableLocalHeroSlave.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_ally = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_enemy = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_neutral = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_invulnerableAlly = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_invulnerableEnemy = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_localHero = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_localHeroSlave = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_invulnerableLocalHero = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_invulnerableLocalHeroSlave = new UndoRedoDBPtr<AdventureTooltipSettings>( owner );
		_ally.Changed += FireChangedEvent;
		_enemy.Changed += FireChangedEvent;
		_neutral.Changed += FireChangedEvent;
		_invulnerableAlly.Changed += FireChangedEvent;
		_invulnerableEnemy.Changed += FireChangedEvent;
		_localHero.Changed += FireChangedEvent;
		_localHeroSlave.Changed += FireChangedEvent;
		_invulnerableLocalHero.Changed += FireChangedEvent;
		_invulnerableLocalHeroSlave.Changed += FireChangedEvent;
	}

	public UnitOvertipSettings()
	{
		Initialize( GetOwner() );
	}

	public UnitOvertipSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UnitOvertipSettings( DBResource owner, UnitOvertipSettings source )
		: this(owner, source, true){}

	protected UnitOvertipSettings( DBResource owner, UnitOvertipSettings source, bool fireEvent )
	{
		_ally = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.ally );
		_enemy = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.enemy );
		_neutral = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.neutral );
		_invulnerableAlly = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.invulnerableAlly );
		_invulnerableEnemy = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.invulnerableEnemy );
		_localHero = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.localHero );
		_localHeroSlave = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.localHeroSlave );
		_invulnerableLocalHero = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.invulnerableLocalHero );
		_invulnerableLocalHeroSlave = new UndoRedoDBPtr<AdventureTooltipSettings>( owner, source.invulnerableLocalHeroSlave );
		_ally.Changed += FireChangedEvent;
		_enemy.Changed += FireChangedEvent;
		_neutral.Changed += FireChangedEvent;
		_invulnerableAlly.Changed += FireChangedEvent;
		_invulnerableEnemy.Changed += FireChangedEvent;
		_localHero.Changed += FireChangedEvent;
		_localHeroSlave.Changed += FireChangedEvent;
		_invulnerableLocalHero.Changed += FireChangedEvent;
		_invulnerableLocalHeroSlave.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UnitOvertipSettings source = _source as UnitOvertipSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitOvertipSettings" );
		ally = source.ally;
		enemy = source.enemy;
		neutral = source.neutral;
		invulnerableAlly = source.invulnerableAlly;
		invulnerableEnemy = source.invulnerableEnemy;
		localHero = source.localHero;
		localHeroSlave = source.localHeroSlave;
		invulnerableLocalHero = source.invulnerableLocalHero;
		invulnerableLocalHeroSlave = source.invulnerableLocalHeroSlave;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UnitOvertipSettings newParent = _newParent as UnitOvertipSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_ally.SetParent( newParent == null ? null : newParent._ally );
		_enemy.SetParent( newParent == null ? null : newParent._enemy );
		_neutral.SetParent( newParent == null ? null : newParent._neutral );
		_invulnerableAlly.SetParent( newParent == null ? null : newParent._invulnerableAlly );
		_invulnerableEnemy.SetParent( newParent == null ? null : newParent._invulnerableEnemy );
		_localHero.SetParent( newParent == null ? null : newParent._localHero );
		_localHeroSlave.SetParent( newParent == null ? null : newParent._localHeroSlave );
		_invulnerableLocalHero.SetParent( newParent == null ? null : newParent._invulnerableLocalHero );
		_invulnerableLocalHeroSlave.SetParent( newParent == null ? null : newParent._invulnerableLocalHeroSlave );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_ally.Reset();
		_enemy.Reset();
		_neutral.Reset();
		_invulnerableAlly.Reset();
		_invulnerableEnemy.Reset();
		_localHero.Reset();
		_localHeroSlave.Reset();
		_invulnerableLocalHero.Reset();
		_invulnerableLocalHeroSlave.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_ally.IsDerivedFromParent()
			&& _enemy.IsDerivedFromParent()
			&& _neutral.IsDerivedFromParent()
			&& _invulnerableAlly.IsDerivedFromParent()
			&& _invulnerableEnemy.IsDerivedFromParent()
			&& _localHero.IsDerivedFromParent()
			&& _localHeroSlave.IsDerivedFromParent()
			&& _invulnerableLocalHero.IsDerivedFromParent()
			&& _invulnerableLocalHeroSlave.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "ally" )
			_ally.Reset();
		else if ( fieldName == "enemy" )
			_enemy.Reset();
		else if ( fieldName == "neutral" )
			_neutral.Reset();
		else if ( fieldName == "invulnerableAlly" )
			_invulnerableAlly.Reset();
		else if ( fieldName == "invulnerableEnemy" )
			_invulnerableEnemy.Reset();
		else if ( fieldName == "localHero" )
			_localHero.Reset();
		else if ( fieldName == "localHeroSlave" )
			_localHeroSlave.Reset();
		else if ( fieldName == "invulnerableLocalHero" )
			_invulnerableLocalHero.Reset();
		else if ( fieldName == "invulnerableLocalHeroSlave" )
			_invulnerableLocalHeroSlave.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "ally" )
			return _ally.IsDerivedFromParent();
		if ( fieldName == "enemy" )
			return _enemy.IsDerivedFromParent();
		if ( fieldName == "neutral" )
			return _neutral.IsDerivedFromParent();
		if ( fieldName == "invulnerableAlly" )
			return _invulnerableAlly.IsDerivedFromParent();
		if ( fieldName == "invulnerableEnemy" )
			return _invulnerableEnemy.IsDerivedFromParent();
		if ( fieldName == "localHero" )
			return _localHero.IsDerivedFromParent();
		if ( fieldName == "localHeroSlave" )
			return _localHeroSlave.IsDerivedFromParent();
		if ( fieldName == "invulnerableLocalHero" )
			return _invulnerableLocalHero.IsDerivedFromParent();
		if ( fieldName == "invulnerableLocalHeroSlave" )
			return _invulnerableLocalHeroSlave.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[DBVersion(1)]
[IndexField("statId")]
public class UnitStat : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private UnitStat __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private ExecutableFloatString _value;
	private ExecutableFloatString _increment;
	private UndoRedo<EStat> _statId;
	private UndoRedoAssignableList<StatUpgrade> _levelUpgrades;
	private UndoRedo<float> _calcValue;
	private UndoRedo<float> _calcIncrement;

	[Description( "Stat base value" )]
	public ExecutableFloatString value { get { return _value; } set { _value.Assign( value ); } }

	[Description( "Stat increment per level" )]
	public ExecutableFloatString increment { get { return _increment; } set { _increment.Assign( value ); } }

	[Description( "Stat Id" )]
	public EStat statId { get { return _statId.Get(); } set { _statId.Set( value ); } }

	[Description( "Special way to specify non-linear increment. Field increment ignored when this field is used" )]
	public libdb.IChangeableList<StatUpgrade> levelUpgrades { get { return _levelUpgrades; } set { _levelUpgrades.Assign( value ); } }

	[Browsable( false )]
	[NoCode]
	public float calcValue { get { return _calcValue.Get(); } set { _calcValue.Set( value ); } }

	[Browsable( false )]
	[NoCode]
	public float calcIncrement { get { return _calcIncrement.Get(); } set { _calcIncrement.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		ExecutableFloatString __value = new ExecutableFloatString(); // Construct default object for value
		__value.sString = "0.0f";
		_value = new ExecutableFloatString( owner, __value );
		ExecutableFloatString __increment = new ExecutableFloatString(); // Construct default object for increment
		__increment.sString = "0.0f";
		_increment = new ExecutableFloatString( owner, __increment );
		_statId = new UndoRedo<EStat>( owner, EStat.Life );
		_levelUpgrades = new UndoRedoAssignableList<StatUpgrade>( owner );
		_calcValue = new UndoRedo<float>( owner, 0.0f );
		_calcIncrement = new UndoRedo<float>( owner, 0.0f );
		_value.Changed += FireChangedEvent;
		_increment.Changed += FireChangedEvent;
		_statId.Changed += FireChangedEvent;
		_levelUpgrades.Changed += FireChangedEvent;
		_calcValue.Changed += FireChangedEvent;
		_calcIncrement.Changed += FireChangedEvent;
	}

	public UnitStat()
	{
		Initialize( GetOwner() );
	}

	public UnitStat( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public UnitStat( DBResource owner, UnitStat source )
		: this(owner, source, true){}

	protected UnitStat( DBResource owner, UnitStat source, bool fireEvent )
	{
		_value = new ExecutableFloatString( owner, source.value );
		_increment = new ExecutableFloatString( owner, source.increment );
		_statId = new UndoRedo<EStat>( owner, source.statId );
		_levelUpgrades = new UndoRedoAssignableList<StatUpgrade>( owner );
		_levelUpgrades.Assign( source.levelUpgrades );
		_calcValue = new UndoRedo<float>( owner, source.calcValue );
		_calcIncrement = new UndoRedo<float>( owner, source.calcIncrement );
		_value.Changed += FireChangedEvent;
		_increment.Changed += FireChangedEvent;
		_statId.Changed += FireChangedEvent;
		_levelUpgrades.Changed += FireChangedEvent;
		_calcValue.Changed += FireChangedEvent;
		_calcIncrement.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		UnitStat source = _source as UnitStat;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitStat" );
		value = source.value;
		increment = source.increment;
		statId = source.statId;
		levelUpgrades = source.levelUpgrades;
		calcValue = source.calcValue;
		calcIncrement = source.calcIncrement;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		UnitStat newParent = _newParent as UnitStat;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_value.SetParent( newParent == null ? null : newParent._value );
		_increment.SetParent( newParent == null ? null : newParent._increment );
		_statId.SetParent( newParent == null ? null : newParent._statId );
		_levelUpgrades.SetParent( newParent == null ? null : newParent._levelUpgrades );
		_calcValue.SetParent( newParent == null ? null : newParent._calcValue );
		_calcIncrement.SetParent( newParent == null ? null : newParent._calcIncrement );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_value.Reset();
		_increment.Reset();
		_statId.Reset();
		_levelUpgrades.Reset();
		_calcValue.Reset();
		_calcIncrement.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_value.IsDerivedFromParent()
			&& _increment.IsDerivedFromParent()
			&& _statId.IsDerivedFromParent()
			&& _levelUpgrades.IsDerivedFromParent()
			&& _calcValue.IsDerivedFromParent()
			&& _calcIncrement.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "value" )
			_value.Reset();
		else if ( fieldName == "increment" )
			_increment.Reset();
		else if ( fieldName == "statId" )
			_statId.Reset();
		else if ( fieldName == "levelUpgrades" )
			_levelUpgrades.Reset();
		else if ( fieldName == "calcValue" )
			_calcValue.Reset();
		else if ( fieldName == "calcIncrement" )
			_calcIncrement.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
		if ( fieldName == "increment" )
			return _increment.IsDerivedFromParent();
		if ( fieldName == "statId" )
			return _statId.IsDerivedFromParent();
		if ( fieldName == "levelUpgrades" )
			return _levelUpgrades.IsDerivedFromParent();
		if ( fieldName == "calcValue" )
			return _calcValue.IsDerivedFromParent();
		if ( fieldName == "calcIncrement" )
			return _calcIncrement.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

public class VictoryDefeatImages : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private VictoryDefeatImages __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Texture> _DefeatBurn;
	private UndoRedoDBPtr<Texture> _DefeatFreeze;
	private UndoRedoDBPtr<Texture> _VictoryBurn;
	private UndoRedoDBPtr<Texture> _VictoryFreeze;

	[Description( "Defeat: image for elfs " )]
	public DBPtr<Texture> DefeatBurn { get { return _DefeatBurn.Get(); } set { _DefeatBurn.Set( value ); } }

	[Description( "Defeat: image for humans" )]
	public DBPtr<Texture> DefeatFreeze { get { return _DefeatFreeze.Get(); } set { _DefeatFreeze.Set( value ); } }

	[Description( "Victory: image for elfs" )]
	public DBPtr<Texture> VictoryBurn { get { return _VictoryBurn.Get(); } set { _VictoryBurn.Set( value ); } }

	[Description( "Victory: image for humans" )]
	public DBPtr<Texture> VictoryFreeze { get { return _VictoryFreeze.Get(); } set { _VictoryFreeze.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_DefeatBurn = new UndoRedoDBPtr<Texture>( owner );
		_DefeatFreeze = new UndoRedoDBPtr<Texture>( owner );
		_VictoryBurn = new UndoRedoDBPtr<Texture>( owner );
		_VictoryFreeze = new UndoRedoDBPtr<Texture>( owner );
		_DefeatBurn.Changed += FireChangedEvent;
		_DefeatFreeze.Changed += FireChangedEvent;
		_VictoryBurn.Changed += FireChangedEvent;
		_VictoryFreeze.Changed += FireChangedEvent;
	}

	public VictoryDefeatImages()
	{
		Initialize( GetOwner() );
	}

	public VictoryDefeatImages( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public VictoryDefeatImages( DBResource owner, VictoryDefeatImages source )
		: this(owner, source, true){}

	protected VictoryDefeatImages( DBResource owner, VictoryDefeatImages source, bool fireEvent )
	{
		_DefeatBurn = new UndoRedoDBPtr<Texture>( owner, source.DefeatBurn );
		_DefeatFreeze = new UndoRedoDBPtr<Texture>( owner, source.DefeatFreeze );
		_VictoryBurn = new UndoRedoDBPtr<Texture>( owner, source.VictoryBurn );
		_VictoryFreeze = new UndoRedoDBPtr<Texture>( owner, source.VictoryFreeze );
		_DefeatBurn.Changed += FireChangedEvent;
		_DefeatFreeze.Changed += FireChangedEvent;
		_VictoryBurn.Changed += FireChangedEvent;
		_VictoryFreeze.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		VictoryDefeatImages source = _source as VictoryDefeatImages;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for VictoryDefeatImages" );
		DefeatBurn = source.DefeatBurn;
		DefeatFreeze = source.DefeatFreeze;
		VictoryBurn = source.VictoryBurn;
		VictoryFreeze = source.VictoryFreeze;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		VictoryDefeatImages newParent = _newParent as VictoryDefeatImages;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_DefeatBurn.SetParent( newParent == null ? null : newParent._DefeatBurn );
		_DefeatFreeze.SetParent( newParent == null ? null : newParent._DefeatFreeze );
		_VictoryBurn.SetParent( newParent == null ? null : newParent._VictoryBurn );
		_VictoryFreeze.SetParent( newParent == null ? null : newParent._VictoryFreeze );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_DefeatBurn.Reset();
		_DefeatFreeze.Reset();
		_VictoryBurn.Reset();
		_VictoryFreeze.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_DefeatBurn.IsDerivedFromParent()
			&& _DefeatFreeze.IsDerivedFromParent()
			&& _VictoryBurn.IsDerivedFromParent()
			&& _VictoryFreeze.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "DefeatBurn" )
			_DefeatBurn.Reset();
		else if ( fieldName == "DefeatFreeze" )
			_DefeatFreeze.Reset();
		else if ( fieldName == "VictoryBurn" )
			_VictoryBurn.Reset();
		else if ( fieldName == "VictoryFreeze" )
			_VictoryFreeze.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "DefeatBurn" )
			return _DefeatBurn.IsDerivedFromParent();
		if ( fieldName == "DefeatFreeze" )
			return _DefeatFreeze.IsDerivedFromParent();
		if ( fieldName == "VictoryBurn" )
			return _VictoryBurn.IsDerivedFromParent();
		if ( fieldName == "VictoryFreeze" )
			return _VictoryFreeze.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Create", "NWorld::PFAchievBase", "NWorld::PFWorld* world")]
[NonTerminal]
[TypeId(0x4D72CBC2)]
[UseTypeName("ACHIEV")]
public class AchievBase : DBResource
{
	private UndoRedoDBPtr<AchievBase> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EAchievementType> _achievType;
	private TextRef _name;
	private UndoRedo<int> _perAchievementScore;
	private UndoRedo<int> _limit;
	private UndoRedo<float> _multiplier;
	private TextRef _tooltip;
	private UndoRedo<int> _priority;
	private UndoRedoDBPtr<Texture> _image;
	private UndoRedoDBPtr<UIEvent> _evUI;
	private UndoRedo<float> _naftaAward;

	public EAchievementType achievType { get { return _achievType.Get(); } set { _achievType.Set( value ); } }

	[Description( "Achievement name" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Description( "Amount of score per one achievement" )]
	public int perAchievementScore { get { return _perAchievementScore.Get(); } set { _perAchievementScore.Set( value ); } }

	[Description( "Maximum achievement scores" )]
	public int limit { get { return _limit.Get(); } set { _limit.Set( value ); } }

	[Description( "Score multiplier (for linear achievements)" )]
	public float multiplier { get { return _multiplier.Get(); } set { _multiplier.Set( value ); } }

	[Description( "Tooltip text for final statistics" )]
	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	[Description( "Priority for final stat order" )]
	public int priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	[Description( "Icon image" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	[Description( "UI Event" )]
	public DBPtr<UIEvent> evUI { get { return _evUI.Get(); } set { _evUI.Set( value ); } }

	[Description( "Сколько прайма дадут за этот подвиг" )]
	public float naftaAward { get { return _naftaAward.Get(); } set { _naftaAward.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievBase>(owner);
		_achievType = new UndoRedo<EAchievementType>( owner, EAchievementType.InvalidAchivement );
		_name = new TextRef( owner, new TextRef() );
		_perAchievementScore = new UndoRedo<int>( owner, 0 );
		_limit = new UndoRedo<int>( owner, 0 );
		_multiplier = new UndoRedo<float>( owner, 1.0f );
		_tooltip = new TextRef( owner, new TextRef() );
		_priority = new UndoRedo<int>( owner, 0 );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_evUI = new UndoRedoDBPtr<UIEvent>( owner );
		_naftaAward = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_achievType.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_perAchievementScore.Changed += FireChangedEvent;
		_limit.Changed += FireChangedEvent;
		_multiplier.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_evUI.Changed += FireChangedEvent;
		_naftaAward.Changed += FireChangedEvent;
	}

	public AchievBase()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievBase" );
		achievType = source.achievType;
		name = source.name;
		perAchievementScore = source.perAchievementScore;
		limit = source.limit;
		multiplier = source.multiplier;
		tooltip = source.tooltip;
		priority = source.priority;
		image = source.image;
		evUI = source.evUI;
		naftaAward = source.naftaAward;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievBase source = _source as AchievBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievBase newParent = rawParent == null ? null : rawParent.Get<AchievBase>();
		if ( newParent == null && _newParent is AchievBase )
			newParent = _newParent as AchievBase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_achievType.SetParent( newParent == null ? null : newParent._achievType );
		_name.SetParent( newParent == null ? null : newParent._name );
		_perAchievementScore.SetParent( newParent == null ? null : newParent._perAchievementScore );
		_limit.SetParent( newParent == null ? null : newParent._limit );
		_multiplier.SetParent( newParent == null ? null : newParent._multiplier );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		_image.SetParent( newParent == null ? null : newParent._image );
		_evUI.SetParent( newParent == null ? null : newParent._evUI );
		_naftaAward.SetParent( newParent == null ? null : newParent._naftaAward );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_achievType.Reset();
		_name.Reset();
		_perAchievementScore.Reset();
		_limit.Reset();
		_multiplier.Reset();
		_tooltip.Reset();
		_priority.Reset();
		_image.Reset();
		_evUI.Reset();
		_naftaAward.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_achievType.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _perAchievementScore.IsDerivedFromParent()
			&& _limit.IsDerivedFromParent()
			&& _multiplier.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _priority.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _evUI.IsDerivedFromParent()
			&& _naftaAward.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "achievType" )
			_achievType.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "perAchievementScore" )
			_perAchievementScore.Reset();
		else if ( fieldName == "limit" )
			_limit.Reset();
		else if ( fieldName == "multiplier" )
			_multiplier.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "priority" )
			_priority.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "evUI" )
			_evUI.Reset();
		else if ( fieldName == "naftaAward" )
			_naftaAward.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "achievType" )
			return _achievType.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "perAchievementScore" )
			return _perAchievementScore.IsDerivedFromParent();
		if ( fieldName == "limit" )
			return _limit.IsDerivedFromParent();
		if ( fieldName == "multiplier" )
			return _multiplier.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "priority" )
			return _priority.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "evUI" )
			return _evUI.IsDerivedFromParent();
		if ( fieldName == "naftaAward" )
			return _naftaAward.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievRuler", "PFAchievement.h")]
[NonTerminal]
[TypeId(0x4D732480)]
[UseTypeName("ACHIEV")]
public class AchievRuler : AchievBase
{
	private UndoRedoDBPtr<AchievRuler> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievRuler> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _start;
	private UndoRedo<int> _step;
	private UndoRedo<bool> _breakOnDeath;

	[Description( "Start ruler value" )]
	public int start { get { return _start.Get(); } set { _start.Set( value ); } }

	[Description( "Ruler step" )]
	public int step { get { return _step.Get(); } set { _step.Set( value ); } }

	[Description( "Reset values on hero death?" )]
	public bool breakOnDeath { get { return _breakOnDeath.Get(); } set { _breakOnDeath.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievRuler>(owner);
		_start = new UndoRedo<int>( owner, 2 );
		_step = new UndoRedo<int>( owner, 1 );
		_breakOnDeath = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_start.Changed += FireChangedEvent;
		_step.Changed += FireChangedEvent;
		_breakOnDeath.Changed += FireChangedEvent;
	}

	public AchievRuler()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievRuler source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievRuler" );
		start = source.start;
		step = source.step;
		breakOnDeath = source.breakOnDeath;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievRuler source = _source as AchievRuler;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievRuler" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievRuler newParent = rawParent == null ? null : rawParent.Get<AchievRuler>();
		if ( newParent == null && _newParent is AchievRuler )
			newParent = _newParent as AchievRuler;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_start.SetParent( newParent == null ? null : newParent._start );
		_step.SetParent( newParent == null ? null : newParent._step );
		_breakOnDeath.SetParent( newParent == null ? null : newParent._breakOnDeath );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_start.Reset();
		_step.Reset();
		_breakOnDeath.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_start.IsDerivedFromParent()
			&& _step.IsDerivedFromParent()
			&& _breakOnDeath.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "start" )
			_start.Reset();
		else if ( fieldName == "step" )
			_step.Reset();
		else if ( fieldName == "breakOnDeath" )
			_breakOnDeath.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "start" )
			return _start.IsDerivedFromParent();
		if ( fieldName == "step" )
			return _step.IsDerivedFromParent();
		if ( fieldName == "breakOnDeath" )
			return _breakOnDeath.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievAvenge", "PFAchievement.h")]
[TypeId(0x4D732B43)]
[UseTypeName("ACHIEV")]
public class AchievAvenge : AchievBase
{
	private UndoRedoDBPtr<AchievAvenge> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievAvenge> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _timeLimit;
	private UndoRedo<float> _distanceLimit;

	public int timeLimit { get { return _timeLimit.Get(); } set { _timeLimit.Set( value ); } }

	public float distanceLimit { get { return _distanceLimit.Get(); } set { _distanceLimit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievAvenge>(owner);
		_timeLimit = new UndoRedo<int>( owner, 15 );
		_distanceLimit = new UndoRedo<float>( owner, 50.0f );
		___parent.Changed += FireChangedEvent;
		_timeLimit.Changed += FireChangedEvent;
		_distanceLimit.Changed += FireChangedEvent;
	}

	public AchievAvenge()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievAvenge source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievAvenge" );
		timeLimit = source.timeLimit;
		distanceLimit = source.distanceLimit;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievAvenge source = _source as AchievAvenge;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievAvenge" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievAvenge newParent = rawParent == null ? null : rawParent.Get<AchievAvenge>();
		if ( newParent == null && _newParent is AchievAvenge )
			newParent = _newParent as AchievAvenge;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_timeLimit.SetParent( newParent == null ? null : newParent._timeLimit );
		_distanceLimit.SetParent( newParent == null ? null : newParent._distanceLimit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_timeLimit.Reset();
		_distanceLimit.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_timeLimit.IsDerivedFromParent()
			&& _distanceLimit.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "timeLimit" )
			_timeLimit.Reset();
		else if ( fieldName == "distanceLimit" )
			_distanceLimit.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "timeLimit" )
			return _timeLimit.IsDerivedFromParent();
		if ( fieldName == "distanceLimit" )
			return _distanceLimit.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievStreak", "PFAchievement.h")]
[NonTerminal]
[TypeId(0x4D739B00)]
[UseTypeName("ACHIEV")]
public class AchievStreak : AchievBase
{
	private UndoRedoDBPtr<AchievStreak> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievStreak> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _start;

	[Description( "Start streak value" )]
	public int start { get { return _start.Get(); } set { _start.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievStreak>(owner);
		_start = new UndoRedo<int>( owner, 3 );
		___parent.Changed += FireChangedEvent;
		_start.Changed += FireChangedEvent;
	}

	public AchievStreak()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievStreak source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievStreak" );
		start = source.start;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievStreak source = _source as AchievStreak;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievStreak" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievStreak newParent = rawParent == null ? null : rawParent.Get<AchievStreak>();
		if ( newParent == null && _newParent is AchievStreak )
			newParent = _newParent as AchievStreak;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_start.SetParent( newParent == null ? null : newParent._start );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_start.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_start.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "start" )
			_start.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "start" )
			return _start.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievBaseStrike", "PFAchievement.h")]
[TypeId(0x4D732281)]
[UseTypeName("ACHIEV")]
public class AchievBaseStrike : AchievBase
{
	private UndoRedoDBPtr<AchievBaseStrike> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievBaseStrike> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minBarracks;

	public int minBarracks { get { return _minBarracks.Get(); } set { _minBarracks.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievBaseStrike>(owner);
		_minBarracks = new UndoRedo<int>( owner, 2 );
		___parent.Changed += FireChangedEvent;
		_minBarracks.Changed += FireChangedEvent;
	}

	public AchievBaseStrike()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievBaseStrike source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievBaseStrike" );
		minBarracks = source.minBarracks;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievBaseStrike source = _source as AchievBaseStrike;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievBaseStrike" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievBaseStrike newParent = rawParent == null ? null : rawParent.Get<AchievBaseStrike>();
		if ( newParent == null && _newParent is AchievBaseStrike )
			newParent = _newParent as AchievBaseStrike;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minBarracks.SetParent( newParent == null ? null : newParent._minBarracks );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minBarracks.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minBarracks.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minBarracks" )
			_minBarracks.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minBarracks" )
			return _minBarracks.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievBorderGuard", "PFAchievement.h")]
[TypeId(0x4D732B4B)]
[UseTypeName("ACHIEV")]
public class AchievBorderGuard : AchievBase
{
	private UndoRedoDBPtr<AchievBorderGuard> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievBorderGuard> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _byTowerLifePercent;
	private UndoRedo<int> _timePeriod;

	public int byTowerLifePercent { get { return _byTowerLifePercent.Get(); } set { _byTowerLifePercent.Set( value ); } }

	public int timePeriod { get { return _timePeriod.Get(); } set { _timePeriod.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievBorderGuard>(owner);
		_byTowerLifePercent = new UndoRedo<int>( owner, 50 );
		_timePeriod = new UndoRedo<int>( owner, 30 );
		___parent.Changed += FireChangedEvent;
		_byTowerLifePercent.Changed += FireChangedEvent;
		_timePeriod.Changed += FireChangedEvent;
	}

	public AchievBorderGuard()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievBorderGuard source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievBorderGuard" );
		byTowerLifePercent = source.byTowerLifePercent;
		timePeriod = source.timePeriod;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievBorderGuard source = _source as AchievBorderGuard;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievBorderGuard" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievBorderGuard newParent = rawParent == null ? null : rawParent.Get<AchievBorderGuard>();
		if ( newParent == null && _newParent is AchievBorderGuard )
			newParent = _newParent as AchievBorderGuard;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_byTowerLifePercent.SetParent( newParent == null ? null : newParent._byTowerLifePercent );
		_timePeriod.SetParent( newParent == null ? null : newParent._timePeriod );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_byTowerLifePercent.Reset();
		_timePeriod.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_byTowerLifePercent.IsDerivedFromParent()
			&& _timePeriod.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "byTowerLifePercent" )
			_byTowerLifePercent.Reset();
		else if ( fieldName == "timePeriod" )
			_timePeriod.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "byTowerLifePercent" )
			return _byTowerLifePercent.IsDerivedFromParent();
		if ( fieldName == "timePeriod" )
			return _timePeriod.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievBossSlayer", "PFAchievement.h")]
[TypeId(0xB19BF480)]
[UseTypeName("ACHIEV")]
public class AchievBossSlayer : AchievBase
{
	private UndoRedoDBPtr<AchievBossSlayer> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievBossSlayer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<AchievBossSlayerData> _creatures;

	[Description( "Юниты за убийство которых дается ачивка" )]
	public libdb.IChangeableList<AchievBossSlayerData> creatures { get { return _creatures; } set { _creatures.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievBossSlayer>(owner);
		_creatures = new UndoRedoAssignableList<AchievBossSlayerData>( owner );
		___parent.Changed += FireChangedEvent;
		_creatures.Changed += FireChangedEvent;
	}

	public AchievBossSlayer()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievBossSlayer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievBossSlayer" );
		creatures = source.creatures;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievBossSlayer source = _source as AchievBossSlayer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievBossSlayer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievBossSlayer newParent = rawParent == null ? null : rawParent.Get<AchievBossSlayer>();
		if ( newParent == null && _newParent is AchievBossSlayer )
			newParent = _newParent as AchievBossSlayer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_creatures.SetParent( newParent == null ? null : newParent._creatures );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_creatures.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_creatures.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "creatures" )
			_creatures.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "creatures" )
			return _creatures.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievCeremonialKill", "PFAchievement.h")]
[TypeId(0x4D732280)]
[UseTypeName("ACHIEV")]
public class AchievCeremonialKill : AchievBase
{
	private UndoRedoDBPtr<AchievCeremonialKill> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievCeremonialKill> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievCeremonialKill>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievCeremonialKill()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievCeremonialKill source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievCeremonialKill" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievCeremonialKill source = _source as AchievCeremonialKill;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievCeremonialKill" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievCeremonialKill newParent = rawParent == null ? null : rawParent.Get<AchievCeremonialKill>();
		if ( newParent == null && _newParent is AchievCeremonialKill )
			newParent = _newParent as AchievCeremonialKill;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievChase", "PFAchievement.h")]
[TypeId(0x4D732B42)]
[UseTypeName("ACHIEV")]
public class AchievChase : AchievBase
{
	private UndoRedoDBPtr<AchievChase> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievChase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _distanceMult;
	private UndoRedo<int> _timeLimit;

	public float distanceMult { get { return _distanceMult.Get(); } set { _distanceMult.Set( value ); } }

	[Description( "Chase duration" )]
	public int timeLimit { get { return _timeLimit.Get(); } set { _timeLimit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievChase>(owner);
		_distanceMult = new UndoRedo<float>( owner, 0.25f );
		_timeLimit = new UndoRedo<int>( owner, 30 );
		___parent.Changed += FireChangedEvent;
		_distanceMult.Changed += FireChangedEvent;
		_timeLimit.Changed += FireChangedEvent;
	}

	public AchievChase()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievChase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievChase" );
		distanceMult = source.distanceMult;
		timeLimit = source.timeLimit;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievChase source = _source as AchievChase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievChase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievChase newParent = rawParent == null ? null : rawParent.Get<AchievChase>();
		if ( newParent == null && _newParent is AchievChase )
			newParent = _newParent as AchievChase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_distanceMult.SetParent( newParent == null ? null : newParent._distanceMult );
		_timeLimit.SetParent( newParent == null ? null : newParent._timeLimit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_distanceMult.Reset();
		_timeLimit.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_distanceMult.IsDerivedFromParent()
			&& _timeLimit.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "distanceMult" )
			_distanceMult.Reset();
		else if ( fieldName == "timeLimit" )
			_timeLimit.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "distanceMult" )
			return _distanceMult.IsDerivedFromParent();
		if ( fieldName == "timeLimit" )
			return _timeLimit.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievCleanUpCreeps", "PFAchievement.h")]
[TypeId(0x4D732B4F)]
[UseTypeName("ACHIEV")]
public class AchievCleanUpCreeps : AchievBase
{
	private UndoRedoDBPtr<AchievCleanUpCreeps> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievCleanUpCreeps> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minCreepsKilled;
	private UndoRedo<int> _timePeriod;

	public int minCreepsKilled { get { return _minCreepsKilled.Get(); } set { _minCreepsKilled.Set( value ); } }

	public int timePeriod { get { return _timePeriod.Get(); } set { _timePeriod.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievCleanUpCreeps>(owner);
		_minCreepsKilled = new UndoRedo<int>( owner, 30 );
		_timePeriod = new UndoRedo<int>( owner, 5 );
		___parent.Changed += FireChangedEvent;
		_minCreepsKilled.Changed += FireChangedEvent;
		_timePeriod.Changed += FireChangedEvent;
	}

	public AchievCleanUpCreeps()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievCleanUpCreeps source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievCleanUpCreeps" );
		minCreepsKilled = source.minCreepsKilled;
		timePeriod = source.timePeriod;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievCleanUpCreeps source = _source as AchievCleanUpCreeps;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievCleanUpCreeps" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievCleanUpCreeps newParent = rawParent == null ? null : rawParent.Get<AchievCleanUpCreeps>();
		if ( newParent == null && _newParent is AchievCleanUpCreeps )
			newParent = _newParent as AchievCleanUpCreeps;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minCreepsKilled.SetParent( newParent == null ? null : newParent._minCreepsKilled );
		_timePeriod.SetParent( newParent == null ? null : newParent._timePeriod );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minCreepsKilled.Reset();
		_timePeriod.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minCreepsKilled.IsDerivedFromParent()
			&& _timePeriod.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minCreepsKilled" )
			_minCreepsKilled.Reset();
		else if ( fieldName == "timePeriod" )
			_timePeriod.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minCreepsKilled" )
			return _minCreepsKilled.IsDerivedFromParent();
		if ( fieldName == "timePeriod" )
			return _timePeriod.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievClearWay", "PFAchievement.h")]
[TypeId(0x4D72CBC4)]
[UseTypeName("ACHIEV")]
public class AchievClearWay : AchievBase
{
	private UndoRedoDBPtr<AchievClearWay> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievClearWay> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minClearWayTowers;

	public int minClearWayTowers { get { return _minClearWayTowers.Get(); } set { _minClearWayTowers.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievClearWay>(owner);
		_minClearWayTowers = new UndoRedo<int>( owner, 3 );
		___parent.Changed += FireChangedEvent;
		_minClearWayTowers.Changed += FireChangedEvent;
	}

	public AchievClearWay()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievClearWay source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievClearWay" );
		minClearWayTowers = source.minClearWayTowers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievClearWay source = _source as AchievClearWay;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievClearWay" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievClearWay newParent = rawParent == null ? null : rawParent.Get<AchievClearWay>();
		if ( newParent == null && _newParent is AchievClearWay )
			newParent = _newParent as AchievClearWay;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minClearWayTowers.SetParent( newParent == null ? null : newParent._minClearWayTowers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minClearWayTowers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minClearWayTowers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minClearWayTowers" )
			_minClearWayTowers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minClearWayTowers" )
			return _minClearWayTowers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievCraftWoman", "PFAchievement.h")]
[TypeId(0x4D738C03)]
[UseTypeName("ACHIEV")]
public class AchievCraftWoman : AchievBase
{
	private UndoRedoDBPtr<AchievCraftWoman> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievCraftWoman> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _heartsCnt;

	public float heartsCnt { get { return _heartsCnt.Get(); } set { _heartsCnt.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievCraftWoman>(owner);
		_heartsCnt = new UndoRedo<float>( owner, 5.0f );
		___parent.Changed += FireChangedEvent;
		_heartsCnt.Changed += FireChangedEvent;
	}

	public AchievCraftWoman()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievCraftWoman source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievCraftWoman" );
		heartsCnt = source.heartsCnt;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievCraftWoman source = _source as AchievCraftWoman;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievCraftWoman" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievCraftWoman newParent = rawParent == null ? null : rawParent.Get<AchievCraftWoman>();
		if ( newParent == null && _newParent is AchievCraftWoman )
			newParent = _newParent as AchievCraftWoman;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heartsCnt.SetParent( newParent == null ? null : newParent._heartsCnt );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heartsCnt.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heartsCnt.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heartsCnt" )
			_heartsCnt.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heartsCnt" )
			return _heartsCnt.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievDemolishingSpree", "PFAchievement.h")]
[TypeId(0x4D732B4D)]
[UseTypeName("ACHIEV")]
public class AchievDemolishingSpree : AchievRuler
{
	private UndoRedoDBPtr<AchievDemolishingSpree> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievDemolishingSpree> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievDemolishingSpree>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievDemolishingSpree()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievDemolishingSpree source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievDemolishingSpree" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievDemolishingSpree source = _source as AchievDemolishingSpree;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievDemolishingSpree" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievDemolishingSpree newParent = rawParent == null ? null : rawParent.Get<AchievDemolishingSpree>();
		if ( newParent == null && _newParent is AchievDemolishingSpree )
			newParent = _newParent as AchievDemolishingSpree;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievDominate", "PFAchievement.h")]
[TypeId(0x4D732B45)]
[UseTypeName("ACHIEV")]
public class AchievDominate : AchievBase
{
	private UndoRedoDBPtr<AchievDominate> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievDominate> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minKillsForDominate;

	[Description( "This value must be equal to start value Dominate-ruller" )]
	public int minKillsForDominate { get { return _minKillsForDominate.Get(); } set { _minKillsForDominate.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievDominate>(owner);
		_minKillsForDominate = new UndoRedo<int>( owner, 3 );
		___parent.Changed += FireChangedEvent;
		_minKillsForDominate.Changed += FireChangedEvent;
	}

	public AchievDominate()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievDominate source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievDominate" );
		minKillsForDominate = source.minKillsForDominate;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievDominate source = _source as AchievDominate;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievDominate" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievDominate newParent = rawParent == null ? null : rawParent.Get<AchievDominate>();
		if ( newParent == null && _newParent is AchievDominate )
			newParent = _newParent as AchievDominate;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minKillsForDominate.SetParent( newParent == null ? null : newParent._minKillsForDominate );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minKillsForDominate.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minKillsForDominate.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minKillsForDominate" )
			_minKillsForDominate.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minKillsForDominate" )
			return _minKillsForDominate.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievDoubleAssist", "PFAchievement.h")]
[TypeId(0x4D732B47)]
[UseTypeName("ACHIEV")]
public class AchievDoubleAssist : AchievBase
{
	private UndoRedoDBPtr<AchievDoubleAssist> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievDoubleAssist> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _timeLimit;

	public int timeLimit { get { return _timeLimit.Get(); } set { _timeLimit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievDoubleAssist>(owner);
		_timeLimit = new UndoRedo<int>( owner, 8 );
		___parent.Changed += FireChangedEvent;
		_timeLimit.Changed += FireChangedEvent;
	}

	public AchievDoubleAssist()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievDoubleAssist source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievDoubleAssist" );
		timeLimit = source.timeLimit;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievDoubleAssist source = _source as AchievDoubleAssist;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievDoubleAssist" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievDoubleAssist newParent = rawParent == null ? null : rawParent.Get<AchievDoubleAssist>();
		if ( newParent == null && _newParent is AchievDoubleAssist )
			newParent = _newParent as AchievDoubleAssist;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_timeLimit.SetParent( newParent == null ? null : newParent._timeLimit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_timeLimit.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_timeLimit.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "timeLimit" )
			_timeLimit.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "timeLimit" )
			return _timeLimit.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievDoubleKill", "PFAchievement.h")]
[TypeId(0x4D732B00)]
[UseTypeName("ACHIEV")]
public class AchievDoubleKill : AchievBase
{
	private UndoRedoDBPtr<AchievDoubleKill> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievDoubleKill> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _timeLimit;

	public int timeLimit { get { return _timeLimit.Get(); } set { _timeLimit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievDoubleKill>(owner);
		_timeLimit = new UndoRedo<int>( owner, 8 );
		___parent.Changed += FireChangedEvent;
		_timeLimit.Changed += FireChangedEvent;
	}

	public AchievDoubleKill()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievDoubleKill source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievDoubleKill" );
		timeLimit = source.timeLimit;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievDoubleKill source = _source as AchievDoubleKill;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievDoubleKill" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievDoubleKill newParent = rawParent == null ? null : rawParent.Get<AchievDoubleKill>();
		if ( newParent == null && _newParent is AchievDoubleKill )
			newParent = _newParent as AchievDoubleKill;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_timeLimit.SetParent( newParent == null ? null : newParent._timeLimit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_timeLimit.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_timeLimit.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "timeLimit" )
			_timeLimit.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "timeLimit" )
			return _timeLimit.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievDragonSlayer", "PFAchievement.h")]
[TypeId(0x4D732B50)]
[UseTypeName("ACHIEV")]
public class AchievDragonSlayer : AchievBase
{
	private UndoRedoDBPtr<AchievDragonSlayer> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievDragonSlayer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Creature>> _dragons;

	[Description( "Драконы. Подвиг даётся за любого из них" )]
	public libdb.IChangeableList<DBPtr<Creature>> dragons { get { return _dragons; } set { _dragons.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievDragonSlayer>(owner);
		_dragons = new UndoRedoAssignableList<DBPtr<Creature>>( owner );
		___parent.Changed += FireChangedEvent;
		_dragons.Changed += FireChangedEvent;
	}

	public AchievDragonSlayer()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievDragonSlayer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievDragonSlayer" );
		dragons = source.dragons;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievDragonSlayer source = _source as AchievDragonSlayer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievDragonSlayer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievDragonSlayer newParent = rawParent == null ? null : rawParent.Get<AchievDragonSlayer>();
		if ( newParent == null && _newParent is AchievDragonSlayer )
			newParent = _newParent as AchievDragonSlayer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_dragons.SetParent( newParent == null ? null : newParent._dragons );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_dragons.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_dragons.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "dragons" )
			_dragons.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "dragons" )
			return _dragons.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievDuel", "PFAchievement.h")]
[TypeId(0x4D732B41)]
[UseTypeName("ACHIEV")]
public class AchievDuel : AchievBase
{
	private UndoRedoDBPtr<AchievDuel> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievDuel> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _maxRestLifePercent;
	private UndoRedo<int> _minLifePercent;
	private UndoRedo<int> _timeLimit;

	[Description( "For achievement killer must have life less than this percent" )]
	public int maxRestLifePercent { get { return _maxRestLifePercent.Get(); } set { _maxRestLifePercent.Set( value ); } }

	[Description( "or during duel killer's life was below this percent" )]
	public int minLifePercent { get { return _minLifePercent.Get(); } set { _minLifePercent.Set( value ); } }

	[Description( "Duel duration" )]
	public int timeLimit { get { return _timeLimit.Get(); } set { _timeLimit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievDuel>(owner);
		_maxRestLifePercent = new UndoRedo<int>( owner, 10 );
		_minLifePercent = new UndoRedo<int>( owner, 5 );
		_timeLimit = new UndoRedo<int>( owner, 30 );
		___parent.Changed += FireChangedEvent;
		_maxRestLifePercent.Changed += FireChangedEvent;
		_minLifePercent.Changed += FireChangedEvent;
		_timeLimit.Changed += FireChangedEvent;
	}

	public AchievDuel()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievDuel source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievDuel" );
		maxRestLifePercent = source.maxRestLifePercent;
		minLifePercent = source.minLifePercent;
		timeLimit = source.timeLimit;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievDuel source = _source as AchievDuel;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievDuel" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievDuel newParent = rawParent == null ? null : rawParent.Get<AchievDuel>();
		if ( newParent == null && _newParent is AchievDuel )
			newParent = _newParent as AchievDuel;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_maxRestLifePercent.SetParent( newParent == null ? null : newParent._maxRestLifePercent );
		_minLifePercent.SetParent( newParent == null ? null : newParent._minLifePercent );
		_timeLimit.SetParent( newParent == null ? null : newParent._timeLimit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_maxRestLifePercent.Reset();
		_minLifePercent.Reset();
		_timeLimit.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_maxRestLifePercent.IsDerivedFromParent()
			&& _minLifePercent.IsDerivedFromParent()
			&& _timeLimit.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "maxRestLifePercent" )
			_maxRestLifePercent.Reset();
		else if ( fieldName == "minLifePercent" )
			_minLifePercent.Reset();
		else if ( fieldName == "timeLimit" )
			_timeLimit.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "maxRestLifePercent" )
			return _maxRestLifePercent.IsDerivedFromParent();
		if ( fieldName == "minLifePercent" )
			return _minLifePercent.IsDerivedFromParent();
		if ( fieldName == "timeLimit" )
			return _timeLimit.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievFirstAssault", "PFAchievement.h")]
[TypeId(0x4D732B4C)]
[UseTypeName("ACHIEV")]
public class AchievFirstAssault : AchievBase
{
	private UndoRedoDBPtr<AchievFirstAssault> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievFirstAssault> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievFirstAssault>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievFirstAssault()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievFirstAssault source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievFirstAssault" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievFirstAssault source = _source as AchievFirstAssault;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievFirstAssault" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievFirstAssault newParent = rawParent == null ? null : rawParent.Get<AchievFirstAssault>();
		if ( newParent == null && _newParent is AchievFirstAssault )
			newParent = _newParent as AchievFirstAssault;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievFirstBlood", "PFAchievement.h")]
[TypeId(0x4D72CBC3)]
[UseTypeName("ACHIEV")]
public class AchievFirstBlood : AchievBase
{
	private UndoRedoDBPtr<AchievFirstBlood> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievFirstBlood> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievFirstBlood>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievFirstBlood()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievFirstBlood source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievFirstBlood" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievFirstBlood source = _source as AchievFirstBlood;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievFirstBlood" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievFirstBlood newParent = rawParent == null ? null : rawParent.Get<AchievFirstBlood>();
		if ( newParent == null && _newParent is AchievFirstBlood )
			newParent = _newParent as AchievFirstBlood;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievFirstMinigameComplete", "PFAchievement.h")]
[TypeId(0x4D738C04)]
[UseTypeName("ACHIEV")]
public class AchievFirstMinigameComplete : AchievBase
{
	private UndoRedoDBPtr<AchievFirstMinigameComplete> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievFirstMinigameComplete> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievFirstMinigameComplete>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievFirstMinigameComplete()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievFirstMinigameComplete source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievFirstMinigameComplete" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievFirstMinigameComplete source = _source as AchievFirstMinigameComplete;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievFirstMinigameComplete" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievFirstMinigameComplete newParent = rawParent == null ? null : rawParent.Get<AchievFirstMinigameComplete>();
		if ( newParent == null && _newParent is AchievFirstMinigameComplete )
			newParent = _newParent as AchievFirstMinigameComplete;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievForestHunter", "PFAchievement.h")]
[TypeId(0x4D732B52)]
[UseTypeName("ACHIEV")]
public class AchievForestHunter : AchievRuler
{
	private UndoRedoDBPtr<AchievForestHunter> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievForestHunter> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievForestHunter>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievForestHunter()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievForestHunter source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievForestHunter" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievForestHunter source = _source as AchievForestHunter;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievForestHunter" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievForestHunter newParent = rawParent == null ? null : rawParent.Get<AchievForestHunter>();
		if ( newParent == null && _newParent is AchievForestHunter )
			newParent = _newParent as AchievForestHunter;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievGoldRite", "PFAchievement.h")]
[TypeId(0x4D738C02)]
[UseTypeName("ACHIEV")]
public class AchievGoldRite : AchievStreak
{
	private UndoRedoDBPtr<AchievGoldRite> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievGoldRite> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievGoldRite>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievGoldRite()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievGoldRite source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievGoldRite" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievGoldRite source = _source as AchievGoldRite;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievGoldRite" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievGoldRite newParent = rawParent == null ? null : rawParent.Get<AchievGoldRite>();
		if ( newParent == null && _newParent is AchievGoldRite )
			newParent = _newParent as AchievGoldRite;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievKillingSpree", "PFAchievement.h")]
[TypeId(0x4D732A80)]
[UseTypeName("ACHIEV")]
public class AchievKillingSpree : AchievRuler
{
	private UndoRedoDBPtr<AchievKillingSpree> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievKillingSpree> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievKillingSpree>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievKillingSpree()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievKillingSpree source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievKillingSpree" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievKillingSpree source = _source as AchievKillingSpree;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievKillingSpree" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievKillingSpree newParent = rawParent == null ? null : rawParent.Get<AchievKillingSpree>();
		if ( newParent == null && _newParent is AchievKillingSpree )
			newParent = _newParent as AchievKillingSpree;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievKittySlayer", "PFAchievement.h")]
[TypeId(0x37B1DC00)]
[UseTypeName("ACHIEV")]
public class AchievKittySlayer : AchievBase
{
	private UndoRedoDBPtr<AchievKittySlayer> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievKittySlayer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Creature>> _kitties;

	[Description( "Киски. Подвиг даётся за любого из них" )]
	public libdb.IChangeableList<DBPtr<Creature>> kitties { get { return _kitties; } set { _kitties.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievKittySlayer>(owner);
		_kitties = new UndoRedoAssignableList<DBPtr<Creature>>( owner );
		___parent.Changed += FireChangedEvent;
		_kitties.Changed += FireChangedEvent;
	}

	public AchievKittySlayer()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievKittySlayer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievKittySlayer" );
		kitties = source.kitties;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievKittySlayer source = _source as AchievKittySlayer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievKittySlayer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievKittySlayer newParent = rawParent == null ? null : rawParent.Get<AchievKittySlayer>();
		if ( newParent == null && _newParent is AchievKittySlayer )
			newParent = _newParent as AchievKittySlayer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_kitties.SetParent( newParent == null ? null : newParent._kitties );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_kitties.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_kitties.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "kitties" )
			_kitties.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "kitties" )
			return _kitties.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievLegend", "PFAchievement.h")]
[TypeId(0x4D732B51)]
[UseTypeName("ACHIEV")]
public class AchievLegend : AchievBase
{
	private UndoRedoDBPtr<AchievLegend> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievLegend> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Creature>> _creatures;

	[Description( "NeutralBosses. Подвиг даётся за любого из них" )]
	public libdb.IChangeableList<DBPtr<Creature>> creatures { get { return _creatures; } set { _creatures.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievLegend>(owner);
		_creatures = new UndoRedoAssignableList<DBPtr<Creature>>( owner );
		___parent.Changed += FireChangedEvent;
		_creatures.Changed += FireChangedEvent;
	}

	public AchievLegend()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievLegend source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievLegend" );
		creatures = source.creatures;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievLegend source = _source as AchievLegend;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievLegend" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievLegend newParent = rawParent == null ? null : rawParent.Get<AchievLegend>();
		if ( newParent == null && _newParent is AchievLegend )
			newParent = _newParent as AchievLegend;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_creatures.SetParent( newParent == null ? null : newParent._creatures );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_creatures.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_creatures.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "creatures" )
			_creatures.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "creatures" )
			return _creatures.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievMassAssist", "PFAchievement.h")]
[TypeId(0x4D732B48)]
[UseTypeName("ACHIEV")]
public class AchievMassAssist : AchievBase
{
	private UndoRedoDBPtr<AchievMassAssist> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievMassAssist> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _timeLimit;
	private UndoRedo<int> _cnt;

	public int timeLimit { get { return _timeLimit.Get(); } set { _timeLimit.Set( value ); } }

	public int cnt { get { return _cnt.Get(); } set { _cnt.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievMassAssist>(owner);
		_timeLimit = new UndoRedo<int>( owner, 8 );
		_cnt = new UndoRedo<int>( owner, 4 );
		___parent.Changed += FireChangedEvent;
		_timeLimit.Changed += FireChangedEvent;
		_cnt.Changed += FireChangedEvent;
	}

	public AchievMassAssist()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievMassAssist source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievMassAssist" );
		timeLimit = source.timeLimit;
		cnt = source.cnt;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievMassAssist source = _source as AchievMassAssist;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievMassAssist" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievMassAssist newParent = rawParent == null ? null : rawParent.Get<AchievMassAssist>();
		if ( newParent == null && _newParent is AchievMassAssist )
			newParent = _newParent as AchievMassAssist;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_timeLimit.SetParent( newParent == null ? null : newParent._timeLimit );
		_cnt.SetParent( newParent == null ? null : newParent._cnt );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_timeLimit.Reset();
		_cnt.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_timeLimit.IsDerivedFromParent()
			&& _cnt.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "timeLimit" )
			_timeLimit.Reset();
		else if ( fieldName == "cnt" )
			_cnt.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "timeLimit" )
			return _timeLimit.IsDerivedFromParent();
		if ( fieldName == "cnt" )
			return _cnt.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievMassKill", "PFAchievement.h")]
[TypeId(0x4D732B40)]
[UseTypeName("ACHIEV")]
public class AchievMassKill : AchievBase
{
	private UndoRedoDBPtr<AchievMassKill> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievMassKill> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _timeLimit;
	private UndoRedo<int> _cnt;

	public int timeLimit { get { return _timeLimit.Get(); } set { _timeLimit.Set( value ); } }

	public int cnt { get { return _cnt.Get(); } set { _cnt.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievMassKill>(owner);
		_timeLimit = new UndoRedo<int>( owner, 8 );
		_cnt = new UndoRedo<int>( owner, 4 );
		___parent.Changed += FireChangedEvent;
		_timeLimit.Changed += FireChangedEvent;
		_cnt.Changed += FireChangedEvent;
	}

	public AchievMassKill()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievMassKill source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievMassKill" );
		timeLimit = source.timeLimit;
		cnt = source.cnt;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievMassKill source = _source as AchievMassKill;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievMassKill" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievMassKill newParent = rawParent == null ? null : rawParent.Get<AchievMassKill>();
		if ( newParent == null && _newParent is AchievMassKill )
			newParent = _newParent as AchievMassKill;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_timeLimit.SetParent( newParent == null ? null : newParent._timeLimit );
		_cnt.SetParent( newParent == null ? null : newParent._cnt );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_timeLimit.Reset();
		_cnt.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_timeLimit.IsDerivedFromParent()
			&& _cnt.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "timeLimit" )
			_timeLimit.Reset();
		else if ( fieldName == "cnt" )
			_cnt.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "timeLimit" )
			return _timeLimit.IsDerivedFromParent();
		if ( fieldName == "cnt" )
			return _cnt.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievMasterControl", "PFAchievement.h")]
[TypeId(0x4D732B4A)]
[UseTypeName("ACHIEV")]
public class AchievMasterControl : AchievRuler
{
	private UndoRedoDBPtr<AchievMasterControl> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievMasterControl> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievMasterControl>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievMasterControl()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievMasterControl source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievMasterControl" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievMasterControl source = _source as AchievMasterControl;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievMasterControl" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievMasterControl newParent = rawParent == null ? null : rawParent.Get<AchievMasterControl>();
		if ( newParent == null && _newParent is AchievMasterControl )
			newParent = _newParent as AchievMasterControl;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievNecklaceOfGlory", "PFAchievement.h")]
[TypeId(0x4D738C01)]
[UseTypeName("ACHIEV")]
public class AchievNecklaceOfGlory : AchievStreak
{
	private UndoRedoDBPtr<AchievNecklaceOfGlory> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievNecklaceOfGlory> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievNecklaceOfGlory>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievNecklaceOfGlory()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievNecklaceOfGlory source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievNecklaceOfGlory" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievNecklaceOfGlory source = _source as AchievNecklaceOfGlory;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievNecklaceOfGlory" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievNecklaceOfGlory newParent = rawParent == null ? null : rawParent.Get<AchievNecklaceOfGlory>();
		if ( newParent == null && _newParent is AchievNecklaceOfGlory )
			newParent = _newParent as AchievNecklaceOfGlory;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievAssistingSpree", "PFAchievement.h")]
[TypeId(0x4D732B4A)]
[UseTypeName("ACHIEV")]
public class AchievAssistingSpree : AchievRuler
{
	private UndoRedoDBPtr<AchievAssistingSpree> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievAssistingSpree> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievAssistingSpree>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievAssistingSpree()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievAssistingSpree source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievAssistingSpree" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievAssistingSpree source = _source as AchievAssistingSpree;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievAssistingSpree" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievAssistingSpree newParent = rawParent == null ? null : rawParent.Get<AchievAssistingSpree>();
		if ( newParent == null && _newParent is AchievAssistingSpree )
			newParent = _newParent as AchievAssistingSpree;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Create", "NWorld::PFAchievSaviour", "PFAchievement.h")]
[TypeId(0x4D732B49)]
[UseTypeName("ACHIEV")]
public class AchievSaviour : AchievBase
{
	private UndoRedoDBPtr<AchievSaviour> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievSaviour> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minLifePercent;
	private UndoRedo<int> _damageDealedPeriod;
	private UndoRedoDBPtr<ApplicatorsList> _applicatorTypes;
	private UndoRedoDBPtr<ApplicatorsList> _exactApplicators;
	private UndoRedo<int> _cooldownPeriod;
	private UndoRedo<float> _timeToLive;
	private UndoRedo<float> _timeToNoDamage;

	public int minLifePercent { get { return _minLifePercent.Get(); } set { _minLifePercent.Set( value ); } }

	public int damageDealedPeriod { get { return _damageDealedPeriod.Get(); } set { _damageDealedPeriod.Set( value ); } }

	public DBPtr<ApplicatorsList> applicatorTypes { get { return _applicatorTypes.Get(); } set { _applicatorTypes.Set( value ); } }

	public DBPtr<ApplicatorsList> exactApplicators { get { return _exactApplicators.Get(); } set { _exactApplicators.Set( value ); } }

	public int cooldownPeriod { get { return _cooldownPeriod.Get(); } set { _cooldownPeriod.Set( value ); } }

	[Description( "Количество секунд, сколько должен прожить герой, после использования на нем спасательной абилки" )]
	public float timeToLive { get { return _timeToLive.Get(); } set { _timeToLive.Set( value ); } }

	[Description( "Количество секунд, сколько герой должен не получать дамаг по истечении времени timeToLive-timeToNoDamage" )]
	public float timeToNoDamage { get { return _timeToNoDamage.Get(); } set { _timeToNoDamage.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievSaviour>(owner);
		_minLifePercent = new UndoRedo<int>( owner, 50 );
		_damageDealedPeriod = new UndoRedo<int>( owner, 5 );
		_applicatorTypes = new UndoRedoDBPtr<ApplicatorsList>( owner );
		_exactApplicators = new UndoRedoDBPtr<ApplicatorsList>( owner );
		_cooldownPeriod = new UndoRedo<int>( owner, 60 );
		_timeToLive = new UndoRedo<float>( owner, 5.0f );
		_timeToNoDamage = new UndoRedo<float>( owner, 2.0f );
		___parent.Changed += FireChangedEvent;
		_minLifePercent.Changed += FireChangedEvent;
		_damageDealedPeriod.Changed += FireChangedEvent;
		_applicatorTypes.Changed += FireChangedEvent;
		_exactApplicators.Changed += FireChangedEvent;
		_cooldownPeriod.Changed += FireChangedEvent;
		_timeToLive.Changed += FireChangedEvent;
		_timeToNoDamage.Changed += FireChangedEvent;
	}

	public AchievSaviour()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievSaviour source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievSaviour" );
		minLifePercent = source.minLifePercent;
		damageDealedPeriod = source.damageDealedPeriod;
		applicatorTypes = source.applicatorTypes;
		exactApplicators = source.exactApplicators;
		cooldownPeriod = source.cooldownPeriod;
		timeToLive = source.timeToLive;
		timeToNoDamage = source.timeToNoDamage;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievSaviour source = _source as AchievSaviour;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievSaviour" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievSaviour newParent = rawParent == null ? null : rawParent.Get<AchievSaviour>();
		if ( newParent == null && _newParent is AchievSaviour )
			newParent = _newParent as AchievSaviour;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minLifePercent.SetParent( newParent == null ? null : newParent._minLifePercent );
		_damageDealedPeriod.SetParent( newParent == null ? null : newParent._damageDealedPeriod );
		_applicatorTypes.SetParent( newParent == null ? null : newParent._applicatorTypes );
		_exactApplicators.SetParent( newParent == null ? null : newParent._exactApplicators );
		_cooldownPeriod.SetParent( newParent == null ? null : newParent._cooldownPeriod );
		_timeToLive.SetParent( newParent == null ? null : newParent._timeToLive );
		_timeToNoDamage.SetParent( newParent == null ? null : newParent._timeToNoDamage );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minLifePercent.Reset();
		_damageDealedPeriod.Reset();
		_applicatorTypes.Reset();
		_exactApplicators.Reset();
		_cooldownPeriod.Reset();
		_timeToLive.Reset();
		_timeToNoDamage.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minLifePercent.IsDerivedFromParent()
			&& _damageDealedPeriod.IsDerivedFromParent()
			&& _applicatorTypes.IsDerivedFromParent()
			&& _exactApplicators.IsDerivedFromParent()
			&& _cooldownPeriod.IsDerivedFromParent()
			&& _timeToLive.IsDerivedFromParent()
			&& _timeToNoDamage.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minLifePercent" )
			_minLifePercent.Reset();
		else if ( fieldName == "damageDealedPeriod" )
			_damageDealedPeriod.Reset();
		else if ( fieldName == "applicatorTypes" )
			_applicatorTypes.Reset();
		else if ( fieldName == "exactApplicators" )
			_exactApplicators.Reset();
		else if ( fieldName == "cooldownPeriod" )
			_cooldownPeriod.Reset();
		else if ( fieldName == "timeToLive" )
			_timeToLive.Reset();
		else if ( fieldName == "timeToNoDamage" )
			_timeToNoDamage.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minLifePercent" )
			return _minLifePercent.IsDerivedFromParent();
		if ( fieldName == "damageDealedPeriod" )
			return _damageDealedPeriod.IsDerivedFromParent();
		if ( fieldName == "applicatorTypes" )
			return _applicatorTypes.IsDerivedFromParent();
		if ( fieldName == "exactApplicators" )
			return _exactApplicators.IsDerivedFromParent();
		if ( fieldName == "cooldownPeriod" )
			return _cooldownPeriod.IsDerivedFromParent();
		if ( fieldName == "timeToLive" )
			return _timeToLive.IsDerivedFromParent();
		if ( fieldName == "timeToNoDamage" )
			return _timeToNoDamage.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievSessionDuration", "PFAchievement.h")]
[TypeId(0xE79BD3C0)]
[UseTypeName("ACHIEV")]
public class AchievSessionDuration : AchievBase
{
	private UndoRedoDBPtr<AchievSessionDuration> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievSessionDuration> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _minTime;
	private UndoRedo<float> _maxTime;
	private UndoRedo<bool> _winners;
	private UndoRedo<bool> _loosers;

	[Description( "Минимальная длительность сессии для подвига (минуты)" )]
	public float minTime { get { return _minTime.Get(); } set { _minTime.Set( value ); } }

	[Description( "Максимальная длительность сессии для подвига (минуты)" )]
	public float maxTime { get { return _maxTime.Get(); } set { _maxTime.Set( value ); } }

	[Description( "Подвиг только для победивших" )]
	public bool winners { get { return _winners.Get(); } set { _winners.Set( value ); } }

	[Description( "Подвиг только для проигравших" )]
	public bool loosers { get { return _loosers.Get(); } set { _loosers.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievSessionDuration>(owner);
		_minTime = new UndoRedo<float>( owner, 0.0f );
		_maxTime = new UndoRedo<float>( owner, 0.0f );
		_winners = new UndoRedo<bool>( owner, true );
		_loosers = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_minTime.Changed += FireChangedEvent;
		_maxTime.Changed += FireChangedEvent;
		_winners.Changed += FireChangedEvent;
		_loosers.Changed += FireChangedEvent;
	}

	public AchievSessionDuration()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievSessionDuration source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievSessionDuration" );
		minTime = source.minTime;
		maxTime = source.maxTime;
		winners = source.winners;
		loosers = source.loosers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievSessionDuration source = _source as AchievSessionDuration;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievSessionDuration" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievSessionDuration newParent = rawParent == null ? null : rawParent.Get<AchievSessionDuration>();
		if ( newParent == null && _newParent is AchievSessionDuration )
			newParent = _newParent as AchievSessionDuration;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minTime.SetParent( newParent == null ? null : newParent._minTime );
		_maxTime.SetParent( newParent == null ? null : newParent._maxTime );
		_winners.SetParent( newParent == null ? null : newParent._winners );
		_loosers.SetParent( newParent == null ? null : newParent._loosers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minTime.Reset();
		_maxTime.Reset();
		_winners.Reset();
		_loosers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minTime.IsDerivedFromParent()
			&& _maxTime.IsDerivedFromParent()
			&& _winners.IsDerivedFromParent()
			&& _loosers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minTime" )
			_minTime.Reset();
		else if ( fieldName == "maxTime" )
			_maxTime.Reset();
		else if ( fieldName == "winners" )
			_winners.Reset();
		else if ( fieldName == "loosers" )
			_loosers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minTime" )
			return _minTime.IsDerivedFromParent();
		if ( fieldName == "maxTime" )
			return _maxTime.IsDerivedFromParent();
		if ( fieldName == "winners" )
			return _winners.IsDerivedFromParent();
		if ( fieldName == "loosers" )
			return _loosers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievAscension", "PFAchievement.h")]
[TypeId(0x4D738C00)]
[UseTypeName("ACHIEV")]
public class AchievAscension : AchievStreak
{
	private UndoRedoDBPtr<AchievAscension> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievAscension> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievAscension>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievAscension()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievAscension source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievAscension" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievAscension source = _source as AchievAscension;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievAscension" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievAscension newParent = rawParent == null ? null : rawParent.Get<AchievAscension>();
		if ( newParent == null && _newParent is AchievAscension )
			newParent = _newParent as AchievAscension;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievTowerDeny", "PFAchievement.h")]
[TypeId(0x4D731440)]
[UseTypeName("ACHIEV")]
public class AchievTowerDeny : AchievBase
{
	private UndoRedoDBPtr<AchievTowerDeny> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievTowerDeny> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievTowerDeny>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievTowerDeny()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievTowerDeny source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievTowerDeny" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievTowerDeny source = _source as AchievTowerDeny;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievTowerDeny" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievTowerDeny newParent = rawParent == null ? null : rawParent.Get<AchievTowerDeny>();
		if ( newParent == null && _newParent is AchievTowerDeny )
			newParent = _newParent as AchievTowerDeny;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievVandalism", "PFAchievement.h")]
[TypeId(0x4D732B4E)]
[UseTypeName("ACHIEV")]
public class AchievVandalism : AchievRuler
{
	private UndoRedoDBPtr<AchievVandalism> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievVandalism> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievVandalism>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievVandalism()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievVandalism source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievVandalism" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievVandalism source = _source as AchievVandalism;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievVandalism" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievVandalism newParent = rawParent == null ? null : rawParent.Get<AchievVandalism>();
		if ( newParent == null && _newParent is AchievVandalism )
			newParent = _newParent as AchievVandalism;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievVendetta", "PFAchievement.h")]
[TypeId(0x4D732B46)]
[UseTypeName("ACHIEV")]
public class AchievVendetta : AchievBase
{
	private UndoRedoDBPtr<AchievVendetta> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievVendetta> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _minKillsForDominate;

	[Description( "This value must be equal to start value Dominate-ruller" )]
	public int minKillsForDominate { get { return _minKillsForDominate.Get(); } set { _minKillsForDominate.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievVendetta>(owner);
		_minKillsForDominate = new UndoRedo<int>( owner, 3 );
		___parent.Changed += FireChangedEvent;
		_minKillsForDominate.Changed += FireChangedEvent;
	}

	public AchievVendetta()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievVendetta source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievVendetta" );
		minKillsForDominate = source.minKillsForDominate;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievVendetta source = _source as AchievVendetta;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievVendetta" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievVendetta newParent = rawParent == null ? null : rawParent.Get<AchievVendetta>();
		if ( newParent == null && _newParent is AchievVendetta )
			newParent = _newParent as AchievVendetta;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minKillsForDominate.SetParent( newParent == null ? null : newParent._minKillsForDominate );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minKillsForDominate.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minKillsForDominate.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minKillsForDominate" )
			_minKillsForDominate.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minKillsForDominate" )
			return _minKillsForDominate.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAchievWarLord", "PFAchievement.h")]
[TypeId(0x4D7324C0)]
[UseTypeName("ACHIEV")]
public class AchievWarLord : AchievRuler
{
	private UndoRedoDBPtr<AchievWarLord> ___parent;
	[HideInOutliner]
	public new DBPtr<AchievWarLord> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AchievWarLord>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public AchievWarLord()
	{
		Initialize( this );
	}
	private void AssignSelf( AchievWarLord source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AchievWarLord" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AchievWarLord source = _source as AchievWarLord;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AchievWarLord" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AchievWarLord newParent = rawParent == null ? null : rawParent.Get<AchievWarLord>();
		if ( newParent == null && _newParent is AchievWarLord )
			newParent = _newParent as AchievWarLord;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class Actor : DBResource
{
	private UndoRedoDBPtr<Actor> ___parent;
	[HideInOutliner]
	public new DBPtr<Actor> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _name;
	private UndoRedoDBPtr<Texture> _icon;
	private UndoRedo<string> _description;

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Description( "Описание персонажа для локализаторов" )]
	[NoCode]
	public string description { get { return _description.Get(); } set { _description.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Actor>(owner);
		_name = new TextRef( owner, new TextRef() );
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_description = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
	}

	public Actor()
	{
		Initialize( this );
	}
	private void AssignSelf( Actor source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Actor" );
		name = source.name;
		icon = source.icon;
		description = source.description;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Actor source = _source as Actor;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Actor" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Actor newParent = rawParent == null ? null : rawParent.Get<Actor>();
		if ( newParent == null && _newParent is Actor )
			newParent = _newParent as Actor;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		_icon.SetParent( newParent == null ? null : newParent._icon );
		_description.SetParent( newParent == null ? null : newParent._description );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		_icon.Reset();
		_description.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _icon.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("CAMS")]
public class AdventureCameraSettings : DBResource
{
	private UndoRedoDBPtr<AdventureCameraSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<AdventureCameraSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _name;
	private UndoRedo<float> _movementSpeed;
	private UndoRedo<float> _vertAngleBottom;
	private UndoRedo<float> _vertLengthBottom;
	private UndoRedo<float> _vertAngleTop;
	private UndoRedo<float> _vertLengthTop;
	private UndoRedo<float> _vertTime;
	private UndoRedo<float> _horCenterAngle;
	private UndoRedo<float> _horAngle;
	private UndoRedo<float> _horTime;
	private UndoRedo<float> _limitRadiusHor;
	private UndoRedo<float> _limitRadiusVert;
	private UndoRedo<float> _fov;
	private UndoRedo<float> _fovCorrectionAngle;
	private UndoRedo<float> _smoothRadius;
	private UndoRedo<int> _smoothDiscrete;
	private UndoRedo<float> _smoothDensity;
	private UndoRedo<float> _pitchRMax;
	private UndoRedo<float> _pitchRConst;
	private UndoRedo<int> _pitchDiscrete;
	private UndoRedo<float> _minCameraHeight;
	private Vec2 _centerOffset;
	private UndoRedo<float> _zoomSpeed;
	private UndoRedo<float> _maxZoomFactor;
	private UndoRedo<float> _lockMultRadiusHor;
	private UndoRedo<float> _lockMultRadiusVert;
	private Vec2 _lockCenterOffset;
	private DampSmoothing _dampSmoothing;

	[Description( "Camera id to be used in console commands" )]
	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	[Description( "Camera movement speed" )]
	public float movementSpeed { get { return _movementSpeed.Get(); } set { _movementSpeed.Set( value ); } }

	[Description( "Angle (0..90) from land plane in bottom-position" )]
	public float vertAngleBottom { get { return _vertAngleBottom.Get(); } set { _vertAngleBottom.Set( value ); } }

	[Description( "Length of rod in bottom-position" )]
	public float vertLengthBottom { get { return _vertLengthBottom.Get(); } set { _vertLengthBottom.Set( value ); } }

	[Description( "Angle (0..90) from land plane in top-position" )]
	public float vertAngleTop { get { return _vertAngleTop.Get(); } set { _vertAngleTop.Set( value ); } }

	[Description( "Length of rod in top-position" )]
	public float vertLengthTop { get { return _vertLengthTop.Get(); } set { _vertLengthTop.Set( value ); } }

	[Description( "Time of vertical deviation from top to bottom" )]
	public float vertTime { get { return _vertTime.Get(); } set { _vertTime.Set( value ); } }

	[Description( "Default horizontal angle (yaw)" )]
	public float horCenterAngle { get { return _horCenterAngle.Get(); } set { _horCenterAngle.Set( value ); } }

	[Description( "Max horizontal deviation (0..90)" )]
	public float horAngle { get { return _horAngle.Get(); } set { _horAngle.Set( value ); } }

	[Description( "Time of max horizontal deviation" )]
	public float horTime { get { return _horTime.Get(); } set { _horTime.Set( value ); } }

	[Description( "Limit ellipse horizontal radius" )]
	public float limitRadiusHor { get { return _limitRadiusHor.Get(); } set { _limitRadiusHor.Set( value ); } }

	[Description( "Limit ellipse vertical radius" )]
	public float limitRadiusVert { get { return _limitRadiusVert.Get(); } set { _limitRadiusVert.Set( value ); } }

	[Description( "Static camera fov" )]
	public float fov { get { return _fov.Get(); } set { _fov.Set( value ); } }

	[Description( "FOV correction angle for non-standard aspects" )]
	public float fovCorrectionAngle { get { return _fovCorrectionAngle.Get(); } set { _fovCorrectionAngle.Set( value ); } }

	[Description( "Radius of height filtration (on meters)" )]
	public float smoothRadius { get { return _smoothRadius.Get(); } set { _smoothRadius.Set( value ); } }

	[Description( "Smooth area discretization (0 - use only center point)" )]
	public int smoothDiscrete { get { return _smoothDiscrete.Get(); } set { _smoothDiscrete.Set( value ); } }

	[Description( "Influence of neighboring points (sigma). Bigger than 0" )]
	public float smoothDensity { get { return _smoothDensity.Get(); } set { _smoothDensity.Set( value ); } }

	[Description( "Radius of landscape collision check (on meters)" )]
	public float pitchRMax { get { return _pitchRMax.Get(); } set { _pitchRMax.Set( value ); } }

	[Description( "Radius of const values of landscape collision check ( <= pitchRMax)" )]
	public float pitchRConst { get { return _pitchRConst.Get(); } set { _pitchRConst.Set( value ); } }

	[Description( "Landscape collision area discretization (0 - use only center point)" )]
	public int pitchDiscrete { get { return _pitchDiscrete.Get(); } set { _pitchDiscrete.Set( value ); } }

	[Description( "Minimal height of camera in bottom (on meters)" )]
	public float minCameraHeight { get { return _minCameraHeight.Get(); } set { _minCameraHeight.Set( value ); } }

	[Description( "Center offset of camera" )]
	public Vec2 centerOffset { get { return _centerOffset; } set { _centerOffset.Assign( value ); } }

	[Description( "Camera zoom speed scale" )]
	public float zoomSpeed { get { return _zoomSpeed.Get(); } set { _zoomSpeed.Set( value ); } }

	[Description( "Maximum zoom factor value; Use values greater than 1.0 to extend over normal camera settings" )]
	public float maxZoomFactor { get { return _maxZoomFactor.Get(); } set { _maxZoomFactor.Set( value ); } }

	[Category( "Map lock overrides" )]
	[Description( "Multiplier for locking outside tiles by camera's limitRadiusHor" )]
	public float lockMultRadiusHor { get { return _lockMultRadiusHor.Get(); } set { _lockMultRadiusHor.Set( value ); } }

	[Category( "Map lock overrides" )]
	[Description( "Multiplier for locking outside tiles by camera's limitRadiusVert" )]
	public float lockMultRadiusVert { get { return _lockMultRadiusVert.Get(); } set { _lockMultRadiusVert.Set( value ); } }

	[Category( "Map lock overrides" )]
	[Description( "Locking outside tiles center offset from camera's centerOffset" )]
	public Vec2 lockCenterOffset { get { return _lockCenterOffset; } set { _lockCenterOffset.Assign( value ); } }

	[Description( "New camera movement algorithm based on damping oscillation" )]
	public DampSmoothing dampSmoothing { get { return _dampSmoothing; } set { _dampSmoothing.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdventureCameraSettings>(owner);
		_name = new UndoRedo<string>( owner, string.Empty );
		_movementSpeed = new UndoRedo<float>( owner, 3.0f );
		_vertAngleBottom = new UndoRedo<float>( owner, 0.0f );
		_vertLengthBottom = new UndoRedo<float>( owner, 0.0f );
		_vertAngleTop = new UndoRedo<float>( owner, 0.0f );
		_vertLengthTop = new UndoRedo<float>( owner, 0.0f );
		_vertTime = new UndoRedo<float>( owner, 0.0f );
		_horCenterAngle = new UndoRedo<float>( owner, 0.0f );
		_horAngle = new UndoRedo<float>( owner, 0.0f );
		_horTime = new UndoRedo<float>( owner, 0.0f );
		_limitRadiusHor = new UndoRedo<float>( owner, 200.0f );
		_limitRadiusVert = new UndoRedo<float>( owner, 200.0f );
		_fov = new UndoRedo<float>( owner, 70.0f );
		_fovCorrectionAngle = new UndoRedo<float>( owner, 66.0f );
		_smoothRadius = new UndoRedo<float>( owner, 3.0f );
		_smoothDiscrete = new UndoRedo<int>( owner, 3 );
		_smoothDensity = new UndoRedo<float>( owner, 2.0f );
		_pitchRMax = new UndoRedo<float>( owner, 3.0f );
		_pitchRConst = new UndoRedo<float>( owner, 1.0f );
		_pitchDiscrete = new UndoRedo<int>( owner, 3 );
		_minCameraHeight = new UndoRedo<float>( owner, 1.0f );
		_centerOffset = new Vec2( owner );
		_zoomSpeed = new UndoRedo<float>( owner, 1.0f );
		_maxZoomFactor = new UndoRedo<float>( owner, 1.0f );
		_lockMultRadiusHor = new UndoRedo<float>( owner, 1.0f );
		_lockMultRadiusVert = new UndoRedo<float>( owner, 1.0f );
		_lockCenterOffset = new Vec2( owner );
		_dampSmoothing = new DampSmoothing( owner );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_movementSpeed.Changed += FireChangedEvent;
		_vertAngleBottom.Changed += FireChangedEvent;
		_vertLengthBottom.Changed += FireChangedEvent;
		_vertAngleTop.Changed += FireChangedEvent;
		_vertLengthTop.Changed += FireChangedEvent;
		_vertTime.Changed += FireChangedEvent;
		_horCenterAngle.Changed += FireChangedEvent;
		_horAngle.Changed += FireChangedEvent;
		_horTime.Changed += FireChangedEvent;
		_limitRadiusHor.Changed += FireChangedEvent;
		_limitRadiusVert.Changed += FireChangedEvent;
		_fov.Changed += FireChangedEvent;
		_fovCorrectionAngle.Changed += FireChangedEvent;
		_smoothRadius.Changed += FireChangedEvent;
		_smoothDiscrete.Changed += FireChangedEvent;
		_smoothDensity.Changed += FireChangedEvent;
		_pitchRMax.Changed += FireChangedEvent;
		_pitchRConst.Changed += FireChangedEvent;
		_pitchDiscrete.Changed += FireChangedEvent;
		_minCameraHeight.Changed += FireChangedEvent;
		_centerOffset.Changed += FireChangedEvent;
		_zoomSpeed.Changed += FireChangedEvent;
		_maxZoomFactor.Changed += FireChangedEvent;
		_lockMultRadiusHor.Changed += FireChangedEvent;
		_lockMultRadiusVert.Changed += FireChangedEvent;
		_lockCenterOffset.Changed += FireChangedEvent;
		_dampSmoothing.Changed += FireChangedEvent;
	}

	public AdventureCameraSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( AdventureCameraSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdventureCameraSettings" );
		name = source.name;
		movementSpeed = source.movementSpeed;
		vertAngleBottom = source.vertAngleBottom;
		vertLengthBottom = source.vertLengthBottom;
		vertAngleTop = source.vertAngleTop;
		vertLengthTop = source.vertLengthTop;
		vertTime = source.vertTime;
		horCenterAngle = source.horCenterAngle;
		horAngle = source.horAngle;
		horTime = source.horTime;
		limitRadiusHor = source.limitRadiusHor;
		limitRadiusVert = source.limitRadiusVert;
		fov = source.fov;
		fovCorrectionAngle = source.fovCorrectionAngle;
		smoothRadius = source.smoothRadius;
		smoothDiscrete = source.smoothDiscrete;
		smoothDensity = source.smoothDensity;
		pitchRMax = source.pitchRMax;
		pitchRConst = source.pitchRConst;
		pitchDiscrete = source.pitchDiscrete;
		minCameraHeight = source.minCameraHeight;
		centerOffset = source.centerOffset;
		zoomSpeed = source.zoomSpeed;
		maxZoomFactor = source.maxZoomFactor;
		lockMultRadiusHor = source.lockMultRadiusHor;
		lockMultRadiusVert = source.lockMultRadiusVert;
		lockCenterOffset = source.lockCenterOffset;
		dampSmoothing = source.dampSmoothing;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdventureCameraSettings source = _source as AdventureCameraSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdventureCameraSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdventureCameraSettings newParent = rawParent == null ? null : rawParent.Get<AdventureCameraSettings>();
		if ( newParent == null && _newParent is AdventureCameraSettings )
			newParent = _newParent as AdventureCameraSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		_movementSpeed.SetParent( newParent == null ? null : newParent._movementSpeed );
		_vertAngleBottom.SetParent( newParent == null ? null : newParent._vertAngleBottom );
		_vertLengthBottom.SetParent( newParent == null ? null : newParent._vertLengthBottom );
		_vertAngleTop.SetParent( newParent == null ? null : newParent._vertAngleTop );
		_vertLengthTop.SetParent( newParent == null ? null : newParent._vertLengthTop );
		_vertTime.SetParent( newParent == null ? null : newParent._vertTime );
		_horCenterAngle.SetParent( newParent == null ? null : newParent._horCenterAngle );
		_horAngle.SetParent( newParent == null ? null : newParent._horAngle );
		_horTime.SetParent( newParent == null ? null : newParent._horTime );
		_limitRadiusHor.SetParent( newParent == null ? null : newParent._limitRadiusHor );
		_limitRadiusVert.SetParent( newParent == null ? null : newParent._limitRadiusVert );
		_fov.SetParent( newParent == null ? null : newParent._fov );
		_fovCorrectionAngle.SetParent( newParent == null ? null : newParent._fovCorrectionAngle );
		_smoothRadius.SetParent( newParent == null ? null : newParent._smoothRadius );
		_smoothDiscrete.SetParent( newParent == null ? null : newParent._smoothDiscrete );
		_smoothDensity.SetParent( newParent == null ? null : newParent._smoothDensity );
		_pitchRMax.SetParent( newParent == null ? null : newParent._pitchRMax );
		_pitchRConst.SetParent( newParent == null ? null : newParent._pitchRConst );
		_pitchDiscrete.SetParent( newParent == null ? null : newParent._pitchDiscrete );
		_minCameraHeight.SetParent( newParent == null ? null : newParent._minCameraHeight );
		_centerOffset.SetParent( newParent == null ? null : newParent._centerOffset );
		_zoomSpeed.SetParent( newParent == null ? null : newParent._zoomSpeed );
		_maxZoomFactor.SetParent( newParent == null ? null : newParent._maxZoomFactor );
		_lockMultRadiusHor.SetParent( newParent == null ? null : newParent._lockMultRadiusHor );
		_lockMultRadiusVert.SetParent( newParent == null ? null : newParent._lockMultRadiusVert );
		_lockCenterOffset.SetParent( newParent == null ? null : newParent._lockCenterOffset );
		_dampSmoothing.SetParent( newParent == null ? null : newParent._dampSmoothing );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		_movementSpeed.Reset();
		_vertAngleBottom.Reset();
		_vertLengthBottom.Reset();
		_vertAngleTop.Reset();
		_vertLengthTop.Reset();
		_vertTime.Reset();
		_horCenterAngle.Reset();
		_horAngle.Reset();
		_horTime.Reset();
		_limitRadiusHor.Reset();
		_limitRadiusVert.Reset();
		_fov.Reset();
		_fovCorrectionAngle.Reset();
		_smoothRadius.Reset();
		_smoothDiscrete.Reset();
		_smoothDensity.Reset();
		_pitchRMax.Reset();
		_pitchRConst.Reset();
		_pitchDiscrete.Reset();
		_minCameraHeight.Reset();
		_centerOffset.Reset();
		_zoomSpeed.Reset();
		_maxZoomFactor.Reset();
		_lockMultRadiusHor.Reset();
		_lockMultRadiusVert.Reset();
		_lockCenterOffset.Reset();
		_dampSmoothing.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _movementSpeed.IsDerivedFromParent()
			&& _vertAngleBottom.IsDerivedFromParent()
			&& _vertLengthBottom.IsDerivedFromParent()
			&& _vertAngleTop.IsDerivedFromParent()
			&& _vertLengthTop.IsDerivedFromParent()
			&& _vertTime.IsDerivedFromParent()
			&& _horCenterAngle.IsDerivedFromParent()
			&& _horAngle.IsDerivedFromParent()
			&& _horTime.IsDerivedFromParent()
			&& _limitRadiusHor.IsDerivedFromParent()
			&& _limitRadiusVert.IsDerivedFromParent()
			&& _fov.IsDerivedFromParent()
			&& _fovCorrectionAngle.IsDerivedFromParent()
			&& _smoothRadius.IsDerivedFromParent()
			&& _smoothDiscrete.IsDerivedFromParent()
			&& _smoothDensity.IsDerivedFromParent()
			&& _pitchRMax.IsDerivedFromParent()
			&& _pitchRConst.IsDerivedFromParent()
			&& _pitchDiscrete.IsDerivedFromParent()
			&& _minCameraHeight.IsDerivedFromParent()
			&& _centerOffset.IsDerivedFromParent()
			&& _zoomSpeed.IsDerivedFromParent()
			&& _maxZoomFactor.IsDerivedFromParent()
			&& _lockMultRadiusHor.IsDerivedFromParent()
			&& _lockMultRadiusVert.IsDerivedFromParent()
			&& _lockCenterOffset.IsDerivedFromParent()
			&& _dampSmoothing.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "movementSpeed" )
			_movementSpeed.Reset();
		else if ( fieldName == "vertAngleBottom" )
			_vertAngleBottom.Reset();
		else if ( fieldName == "vertLengthBottom" )
			_vertLengthBottom.Reset();
		else if ( fieldName == "vertAngleTop" )
			_vertAngleTop.Reset();
		else if ( fieldName == "vertLengthTop" )
			_vertLengthTop.Reset();
		else if ( fieldName == "vertTime" )
			_vertTime.Reset();
		else if ( fieldName == "horCenterAngle" )
			_horCenterAngle.Reset();
		else if ( fieldName == "horAngle" )
			_horAngle.Reset();
		else if ( fieldName == "horTime" )
			_horTime.Reset();
		else if ( fieldName == "limitRadiusHor" )
			_limitRadiusHor.Reset();
		else if ( fieldName == "limitRadiusVert" )
			_limitRadiusVert.Reset();
		else if ( fieldName == "fov" )
			_fov.Reset();
		else if ( fieldName == "fovCorrectionAngle" )
			_fovCorrectionAngle.Reset();
		else if ( fieldName == "smoothRadius" )
			_smoothRadius.Reset();
		else if ( fieldName == "smoothDiscrete" )
			_smoothDiscrete.Reset();
		else if ( fieldName == "smoothDensity" )
			_smoothDensity.Reset();
		else if ( fieldName == "pitchRMax" )
			_pitchRMax.Reset();
		else if ( fieldName == "pitchRConst" )
			_pitchRConst.Reset();
		else if ( fieldName == "pitchDiscrete" )
			_pitchDiscrete.Reset();
		else if ( fieldName == "minCameraHeight" )
			_minCameraHeight.Reset();
		else if ( fieldName == "centerOffset" )
			_centerOffset.Reset();
		else if ( fieldName == "zoomSpeed" )
			_zoomSpeed.Reset();
		else if ( fieldName == "maxZoomFactor" )
			_maxZoomFactor.Reset();
		else if ( fieldName == "lockMultRadiusHor" )
			_lockMultRadiusHor.Reset();
		else if ( fieldName == "lockMultRadiusVert" )
			_lockMultRadiusVert.Reset();
		else if ( fieldName == "lockCenterOffset" )
			_lockCenterOffset.Reset();
		else if ( fieldName == "dampSmoothing" )
			_dampSmoothing.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "movementSpeed" )
			return _movementSpeed.IsDerivedFromParent();
		if ( fieldName == "vertAngleBottom" )
			return _vertAngleBottom.IsDerivedFromParent();
		if ( fieldName == "vertLengthBottom" )
			return _vertLengthBottom.IsDerivedFromParent();
		if ( fieldName == "vertAngleTop" )
			return _vertAngleTop.IsDerivedFromParent();
		if ( fieldName == "vertLengthTop" )
			return _vertLengthTop.IsDerivedFromParent();
		if ( fieldName == "vertTime" )
			return _vertTime.IsDerivedFromParent();
		if ( fieldName == "horCenterAngle" )
			return _horCenterAngle.IsDerivedFromParent();
		if ( fieldName == "horAngle" )
			return _horAngle.IsDerivedFromParent();
		if ( fieldName == "horTime" )
			return _horTime.IsDerivedFromParent();
		if ( fieldName == "limitRadiusHor" )
			return _limitRadiusHor.IsDerivedFromParent();
		if ( fieldName == "limitRadiusVert" )
			return _limitRadiusVert.IsDerivedFromParent();
		if ( fieldName == "fov" )
			return _fov.IsDerivedFromParent();
		if ( fieldName == "fovCorrectionAngle" )
			return _fovCorrectionAngle.IsDerivedFromParent();
		if ( fieldName == "smoothRadius" )
			return _smoothRadius.IsDerivedFromParent();
		if ( fieldName == "smoothDiscrete" )
			return _smoothDiscrete.IsDerivedFromParent();
		if ( fieldName == "smoothDensity" )
			return _smoothDensity.IsDerivedFromParent();
		if ( fieldName == "pitchRMax" )
			return _pitchRMax.IsDerivedFromParent();
		if ( fieldName == "pitchRConst" )
			return _pitchRConst.IsDerivedFromParent();
		if ( fieldName == "pitchDiscrete" )
			return _pitchDiscrete.IsDerivedFromParent();
		if ( fieldName == "minCameraHeight" )
			return _minCameraHeight.IsDerivedFromParent();
		if ( fieldName == "centerOffset" )
			return _centerOffset.IsDerivedFromParent();
		if ( fieldName == "zoomSpeed" )
			return _zoomSpeed.IsDerivedFromParent();
		if ( fieldName == "maxZoomFactor" )
			return _maxZoomFactor.IsDerivedFromParent();
		if ( fieldName == "lockMultRadiusHor" )
			return _lockMultRadiusHor.IsDerivedFromParent();
		if ( fieldName == "lockMultRadiusVert" )
			return _lockMultRadiusVert.IsDerivedFromParent();
		if ( fieldName == "lockCenterOffset" )
			return _lockCenterOffset.IsDerivedFromParent();
		if ( fieldName == "dampSmoothing" )
			return _dampSmoothing.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(9395)]
[UseTypeName("UITP")]
public class AdventureTooltipParams : DBResource
{
	private UndoRedoDBPtr<AdventureTooltipParams> ___parent;
	[HideInOutliner]
	public new DBPtr<AdventureTooltipParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<UnitOvertipSettings> _units;
	private TextRef _locatorName;

	[Description( "Per unit type tooltip settings" )]
	[EnumArray(typeof(EUnitType))]
	public libdb.IChangeableList<UnitOvertipSettings> units { get { return _units; } set { _units.Assign( value ); } }

	public TextRef locatorName { get { return _locatorName; } set { _locatorName.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdventureTooltipParams>(owner);
		_units = new UndoRedoAssignableList<UnitOvertipSettings>( owner, typeof( EUnitType ) );
		_locatorName = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_units.Changed += FireChangedEvent;
		_locatorName.Changed += FireChangedEvent;
	}

	public AdventureTooltipParams()
	{
		Initialize( this );
	}
	private void AssignSelf( AdventureTooltipParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdventureTooltipParams" );
		units = source.units;
		locatorName = source.locatorName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdventureTooltipParams source = _source as AdventureTooltipParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdventureTooltipParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdventureTooltipParams newParent = rawParent == null ? null : rawParent.Get<AdventureTooltipParams>();
		if ( newParent == null && _newParent is AdventureTooltipParams )
			newParent = _newParent as AdventureTooltipParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_units.SetParent( newParent == null ? null : newParent._units );
		_locatorName.SetParent( newParent == null ? null : newParent._locatorName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_units.Reset();
		_locatorName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_units.IsDerivedFromParent()
			&& _locatorName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "units" )
			_units.Reset();
		else if ( fieldName == "locatorName" )
			_locatorName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "units" )
			return _units.IsDerivedFromParent();
		if ( fieldName == "locatorName" )
			return _locatorName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class AdventureTooltipSettings : DBResource
{
	private UndoRedoDBPtr<AdventureTooltipSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<AdventureTooltipSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _showDesc;
	private UndoRedo<EAdventureTooltipStretchMode> _stretch;
	private UndoRedo<string> _uiState;
	private UndoRedo<string> _uiStateShort;
	private TextRef _text;

	[Description( "Show text description in tooltip" )]
	public bool showDesc { get { return _showDesc.Get(); } set { _showDesc.Set( value ); } }

	[Description( "Stretch tooltip bars to fit unit AABB" )]
	public EAdventureTooltipStretchMode stretch { get { return _stretch.Get(); } set { _stretch.Set( value ); } }

	[Description( "State of the tooltip layout" )]
	public string uiState { get { return _uiState.Get(); } set { _uiState.Set( value ); } }

	[Description( "State of the tooltip layout in short mode; May be empty" )]
	public string uiStateShort { get { return _uiStateShort.Get(); } set { _uiStateShort.Set( value ); } }

	[Description( "Tooltip text" )]
	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdventureTooltipSettings>(owner);
		_showDesc = new UndoRedo<bool>( owner, true );
		_stretch = new UndoRedo<EAdventureTooltipStretchMode>( owner, EAdventureTooltipStretchMode.None );
		_uiState = new UndoRedo<string>( owner, "tooltip_layout" );
		_uiStateShort = new UndoRedo<string>( owner, string.Empty );
		_text = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_showDesc.Changed += FireChangedEvent;
		_stretch.Changed += FireChangedEvent;
		_uiState.Changed += FireChangedEvent;
		_uiStateShort.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
	}

	public AdventureTooltipSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( AdventureTooltipSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdventureTooltipSettings" );
		showDesc = source.showDesc;
		stretch = source.stretch;
		uiState = source.uiState;
		uiStateShort = source.uiStateShort;
		text = source.text;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdventureTooltipSettings source = _source as AdventureTooltipSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdventureTooltipSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdventureTooltipSettings newParent = rawParent == null ? null : rawParent.Get<AdventureTooltipSettings>();
		if ( newParent == null && _newParent is AdventureTooltipSettings )
			newParent = _newParent as AdventureTooltipSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_showDesc.SetParent( newParent == null ? null : newParent._showDesc );
		_stretch.SetParent( newParent == null ? null : newParent._stretch );
		_uiState.SetParent( newParent == null ? null : newParent._uiState );
		_uiStateShort.SetParent( newParent == null ? null : newParent._uiStateShort );
		_text.SetParent( newParent == null ? null : newParent._text );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_showDesc.Reset();
		_stretch.Reset();
		_uiState.Reset();
		_uiStateShort.Reset();
		_text.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_showDesc.IsDerivedFromParent()
			&& _stretch.IsDerivedFromParent()
			&& _uiState.IsDerivedFromParent()
			&& _uiStateShort.IsDerivedFromParent()
			&& _text.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "showDesc" )
			_showDesc.Reset();
		else if ( fieldName == "stretch" )
			_stretch.Reset();
		else if ( fieldName == "uiState" )
			_uiState.Reset();
		else if ( fieldName == "uiStateShort" )
			_uiStateShort.Reset();
		else if ( fieldName == "text" )
			_text.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "showDesc" )
			return _showDesc.IsDerivedFromParent();
		if ( fieldName == "stretch" )
			return _stretch.IsDerivedFromParent();
		if ( fieldName == "uiState" )
			return _uiState.IsDerivedFromParent();
		if ( fieldName == "uiStateShort" )
			return _uiStateShort.IsDerivedFromParent();
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[UseTypeName("MAPMODDESC")]
public class AdvMapModeDescription : DBResource
{
	private UndoRedoDBPtr<AdvMapModeDescription> ___parent;
	[HideInOutliner]
	public new DBPtr<AdvMapModeDescription> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Texture> _icon;
	private TextRef _tooltip;

	[Description( "иконка модификатора" )]
	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Description( "Тултип модификатора" )]
	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AdvMapModeDescription>(owner);
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_tooltip = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
	}

	public AdvMapModeDescription()
	{
		Initialize( this );
	}
	private void AssignSelf( AdvMapModeDescription source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AdvMapModeDescription" );
		icon = source.icon;
		tooltip = source.tooltip;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AdvMapModeDescription source = _source as AdvMapModeDescription;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AdvMapModeDescription" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AdvMapModeDescription newParent = rawParent == null ? null : rawParent.Get<AdvMapModeDescription>();
		if ( newParent == null && _newParent is AdvMapModeDescription )
			newParent = _newParent as AdvMapModeDescription;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_icon.SetParent( newParent == null ? null : newParent._icon );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_icon.Reset();
		_tooltip.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_icon.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[UseTypeName("BINDCATEGORY")]
public class BindCategory : DBResource
{
	private UndoRedoDBPtr<BindCategory> ___parent;
	[HideInOutliner]
	public new DBPtr<BindCategory> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _index;
	private TextRef _name;

	[Description( "Индекс категории. Обозначает порядок в окне настроек" )]
	public int index { get { return _index.Get(); } set { _index.Set( value ); } }

	[Description( "Название категории" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BindCategory>(owner);
		_index = new UndoRedo<int>( owner, 0 );
		_name = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_index.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
	}

	public BindCategory()
	{
		Initialize( this );
	}
	private void AssignSelf( BindCategory source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BindCategory" );
		index = source.index;
		name = source.name;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BindCategory source = _source as BindCategory;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BindCategory" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BindCategory newParent = rawParent == null ? null : rawParent.Get<BindCategory>();
		if ( newParent == null && _newParent is BindCategory )
			newParent = _newParent as BindCategory;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_index.SetParent( newParent == null ? null : newParent._index );
		_name.SetParent( newParent == null ? null : newParent._name );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_index.Reset();
		_name.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_index.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "index" )
			_index.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "index" )
			return _index.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("name")]
public class CustomFlag : DBResource
{
	private UndoRedoDBPtr<CustomFlag> ___parent;
	[HideInOutliner]
	public new DBPtr<CustomFlag> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _id;
	private UndoRedoDBPtr<Texture> _icon;
	private UndoRedoDBPtr<Texture> _bigIcon;
	private TextRef _name;
	private TextRef _tooltip;
	private UndoRedo<int> _Price;

	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	[Description( "Иконка" )]
	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	[Description( "Большая иконка (85*85) (в SeasonReardWnd)" )]
	public DBPtr<Texture> bigIcon { get { return _bigIcon.Get(); } set { _bigIcon.Set( value ); } }

	[Description( "Название флага" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public TextRef tooltip { get { return _tooltip; } set { _tooltip.Assign( value ); } }

	public int Price { get { return _Price.Get(); } set { _Price.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CustomFlag>(owner);
		_id = new UndoRedo<string>( owner, string.Empty );
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_bigIcon = new UndoRedoDBPtr<Texture>( owner );
		_name = new TextRef( owner, new TextRef() );
		_tooltip = new TextRef( owner, new TextRef() );
		_Price = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_bigIcon.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_tooltip.Changed += FireChangedEvent;
		_Price.Changed += FireChangedEvent;
	}

	public CustomFlag()
	{
		Initialize( this );
	}
	private void AssignSelf( CustomFlag source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CustomFlag" );
		id = source.id;
		icon = source.icon;
		bigIcon = source.bigIcon;
		name = source.name;
		tooltip = source.tooltip;
		Price = source.Price;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CustomFlag source = _source as CustomFlag;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CustomFlag" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CustomFlag newParent = rawParent == null ? null : rawParent.Get<CustomFlag>();
		if ( newParent == null && _newParent is CustomFlag )
			newParent = _newParent as CustomFlag;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_id.SetParent( newParent == null ? null : newParent._id );
		_icon.SetParent( newParent == null ? null : newParent._icon );
		_bigIcon.SetParent( newParent == null ? null : newParent._bigIcon );
		_name.SetParent( newParent == null ? null : newParent._name );
		_tooltip.SetParent( newParent == null ? null : newParent._tooltip );
		_Price.SetParent( newParent == null ? null : newParent._Price );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_id.Reset();
		_icon.Reset();
		_bigIcon.Reset();
		_name.Reset();
		_tooltip.Reset();
		_Price.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_id.IsDerivedFromParent()
			&& _icon.IsDerivedFromParent()
			&& _bigIcon.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _tooltip.IsDerivedFromParent()
			&& _Price.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "bigIcon" )
			_bigIcon.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "tooltip" )
			_tooltip.Reset();
		else if ( fieldName == "Price" )
			_Price.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "bigIcon" )
			return _bigIcon.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "tooltip" )
			return _tooltip.IsDerivedFromParent();
		if ( fieldName == "Price" )
			return _Price.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(7)]
[UseTypeName("MMAP")]
public class DBMinimap : DBResource
{
	private UndoRedoDBPtr<DBMinimap> ___parent;
	[HideInOutliner]
	public new DBPtr<DBMinimap> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _normalOpacity;
	private UndoRedo<float> _minigameOpacity;
	private UndoRedo<float> _transitionVelocity;
	private UndoRedo<float> _signalLifeTime;
	private Color _signalDefaultColor;
	private Color _enemyColor;
	private Color _allyColor;
	private Color _neutralColor;
	private UndoRedoDBPtr<Texture> _enemyHeroFrame;
	private UndoRedoDBPtr<Texture> _allyHeroFrame;
	private UndoRedoDBPtr<Texture> _localHeroFrame;
	private UndoRedoAssignableList<DBPtr<Texture>> _icons;
	private Color _targetZoneColor;
	private UndoRedo<int> _targetZoneLineThickness;

	[Category( "Fade" )]
	[Description( "Normal opacity" )]
	[FloatMinMax(0, 1)]
	public float normalOpacity { get { return _normalOpacity.Get(); } set { _normalOpacity.Set( value ); } }

	[Category( "Fade" )]
	[Description( "Minigame opacity" )]
	[FloatMinMax(0, 1)]
	public float minigameOpacity { get { return _minigameOpacity.Get(); } set { _minigameOpacity.Set( value ); } }

	[Category( "Fade" )]
	[Description( "Transition time" )]
	[FloatMin(0)]
	public float transitionVelocity { get { return _transitionVelocity.Get(); } set { _transitionVelocity.Set( value ); } }

	[Description( "Время жизни сигнала (пинга), в секундах" )]
	[FloatMinMax(1, 600)]
	public float signalLifeTime { get { return _signalLifeTime.Get(); } set { _signalLifeTime.Set( value ); } }

	[Description( "Цвет сигнала (пинга) по умолчанию" )]
	public Color signalDefaultColor { get { return _signalDefaultColor; } set { _signalDefaultColor.Assign( value ); } }

	[Description( "Color for enemy unit without icon" )]
	public Color enemyColor { get { return _enemyColor; } set { _enemyColor.Assign( value ); } }

	[Description( "Color for ally unit without icon" )]
	public Color allyColor { get { return _allyColor; } set { _allyColor.Assign( value ); } }

	[Description( "Color for neutral unit without icon" )]
	public Color neutralColor { get { return _neutralColor; } set { _neutralColor.Assign( value ); } }

	[Description( "Enemy hero frame" )]
	public DBPtr<Texture> enemyHeroFrame { get { return _enemyHeroFrame.Get(); } set { _enemyHeroFrame.Set( value ); } }

	[Description( "Ally hero frame" )]
	public DBPtr<Texture> allyHeroFrame { get { return _allyHeroFrame.Get(); } set { _allyHeroFrame.Set( value ); } }

	[Description( "Local hero frame" )]
	public DBPtr<Texture> localHeroFrame { get { return _localHeroFrame.Get(); } set { _localHeroFrame.Set( value ); } }

	[Description( "List of standard minimap icons" )]
	[EnumArray(typeof(EMinimapIcons))]
	public libdb.IChangeableList<DBPtr<Texture>> icons { get { return _icons; } set { _icons.Assign( value ); } }

	[Description( "Target zone line color" )]
	public Color targetZoneColor { get { return _targetZoneColor; } set { _targetZoneColor.Assign( value ); } }

	[Description( "Target zone line thickness" )]
	public int targetZoneLineThickness { get { return _targetZoneLineThickness.Get(); } set { _targetZoneLineThickness.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBMinimap>(owner);
		_normalOpacity = new UndoRedo<float>( owner, 1.0f );
		_minigameOpacity = new UndoRedo<float>( owner, 0.2f );
		_transitionVelocity = new UndoRedo<float>( owner, 1.0f );
		_signalLifeTime = new UndoRedo<float>( owner, 5.0f );
		Color __signalDefaultColor = new Color(); // Construct default object for signalDefaultColor
		__signalDefaultColor.R = 255;
		__signalDefaultColor.G = 252;
		__signalDefaultColor.B = 194;
		_signalDefaultColor = new Color( owner, __signalDefaultColor );
		_enemyColor = new Color( owner );
		_allyColor = new Color( owner );
		_neutralColor = new Color( owner );
		_enemyHeroFrame = new UndoRedoDBPtr<Texture>( owner );
		_allyHeroFrame = new UndoRedoDBPtr<Texture>( owner );
		_localHeroFrame = new UndoRedoDBPtr<Texture>( owner );
		_icons = new UndoRedoAssignableList<DBPtr<Texture>>( owner, typeof( EMinimapIcons ) );
		Color __targetZoneColor = new Color(); // Construct default object for targetZoneColor
		__targetZoneColor.R = 255;
		__targetZoneColor.G = 255;
		__targetZoneColor.B = 255;
		_targetZoneColor = new Color( owner, __targetZoneColor );
		_targetZoneLineThickness = new UndoRedo<int>( owner, 2 );
		___parent.Changed += FireChangedEvent;
		_normalOpacity.Changed += FireChangedEvent;
		_minigameOpacity.Changed += FireChangedEvent;
		_transitionVelocity.Changed += FireChangedEvent;
		_signalLifeTime.Changed += FireChangedEvent;
		_signalDefaultColor.Changed += FireChangedEvent;
		_enemyColor.Changed += FireChangedEvent;
		_allyColor.Changed += FireChangedEvent;
		_neutralColor.Changed += FireChangedEvent;
		_enemyHeroFrame.Changed += FireChangedEvent;
		_allyHeroFrame.Changed += FireChangedEvent;
		_localHeroFrame.Changed += FireChangedEvent;
		_icons.Changed += FireChangedEvent;
		_targetZoneColor.Changed += FireChangedEvent;
		_targetZoneLineThickness.Changed += FireChangedEvent;
	}

	public DBMinimap()
	{
		Initialize( this );
	}
	private void AssignSelf( DBMinimap source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBMinimap" );
		normalOpacity = source.normalOpacity;
		minigameOpacity = source.minigameOpacity;
		transitionVelocity = source.transitionVelocity;
		signalLifeTime = source.signalLifeTime;
		signalDefaultColor = source.signalDefaultColor;
		enemyColor = source.enemyColor;
		allyColor = source.allyColor;
		neutralColor = source.neutralColor;
		enemyHeroFrame = source.enemyHeroFrame;
		allyHeroFrame = source.allyHeroFrame;
		localHeroFrame = source.localHeroFrame;
		icons = source.icons;
		targetZoneColor = source.targetZoneColor;
		targetZoneLineThickness = source.targetZoneLineThickness;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBMinimap source = _source as DBMinimap;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBMinimap" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBMinimap newParent = rawParent == null ? null : rawParent.Get<DBMinimap>();
		if ( newParent == null && _newParent is DBMinimap )
			newParent = _newParent as DBMinimap;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_normalOpacity.SetParent( newParent == null ? null : newParent._normalOpacity );
		_minigameOpacity.SetParent( newParent == null ? null : newParent._minigameOpacity );
		_transitionVelocity.SetParent( newParent == null ? null : newParent._transitionVelocity );
		_signalLifeTime.SetParent( newParent == null ? null : newParent._signalLifeTime );
		_signalDefaultColor.SetParent( newParent == null ? null : newParent._signalDefaultColor );
		_enemyColor.SetParent( newParent == null ? null : newParent._enemyColor );
		_allyColor.SetParent( newParent == null ? null : newParent._allyColor );
		_neutralColor.SetParent( newParent == null ? null : newParent._neutralColor );
		_enemyHeroFrame.SetParent( newParent == null ? null : newParent._enemyHeroFrame );
		_allyHeroFrame.SetParent( newParent == null ? null : newParent._allyHeroFrame );
		_localHeroFrame.SetParent( newParent == null ? null : newParent._localHeroFrame );
		_icons.SetParent( newParent == null ? null : newParent._icons );
		_targetZoneColor.SetParent( newParent == null ? null : newParent._targetZoneColor );
		_targetZoneLineThickness.SetParent( newParent == null ? null : newParent._targetZoneLineThickness );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_normalOpacity.Reset();
		_minigameOpacity.Reset();
		_transitionVelocity.Reset();
		_signalLifeTime.Reset();
		_signalDefaultColor.Reset();
		_enemyColor.Reset();
		_allyColor.Reset();
		_neutralColor.Reset();
		_enemyHeroFrame.Reset();
		_allyHeroFrame.Reset();
		_localHeroFrame.Reset();
		_icons.Reset();
		_targetZoneColor.Reset();
		_targetZoneLineThickness.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_normalOpacity.IsDerivedFromParent()
			&& _minigameOpacity.IsDerivedFromParent()
			&& _transitionVelocity.IsDerivedFromParent()
			&& _signalLifeTime.IsDerivedFromParent()
			&& _signalDefaultColor.IsDerivedFromParent()
			&& _enemyColor.IsDerivedFromParent()
			&& _allyColor.IsDerivedFromParent()
			&& _neutralColor.IsDerivedFromParent()
			&& _enemyHeroFrame.IsDerivedFromParent()
			&& _allyHeroFrame.IsDerivedFromParent()
			&& _localHeroFrame.IsDerivedFromParent()
			&& _icons.IsDerivedFromParent()
			&& _targetZoneColor.IsDerivedFromParent()
			&& _targetZoneLineThickness.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "normalOpacity" )
			_normalOpacity.Reset();
		else if ( fieldName == "minigameOpacity" )
			_minigameOpacity.Reset();
		else if ( fieldName == "transitionVelocity" )
			_transitionVelocity.Reset();
		else if ( fieldName == "signalLifeTime" )
			_signalLifeTime.Reset();
		else if ( fieldName == "signalDefaultColor" )
			_signalDefaultColor.Reset();
		else if ( fieldName == "enemyColor" )
			_enemyColor.Reset();
		else if ( fieldName == "allyColor" )
			_allyColor.Reset();
		else if ( fieldName == "neutralColor" )
			_neutralColor.Reset();
		else if ( fieldName == "enemyHeroFrame" )
			_enemyHeroFrame.Reset();
		else if ( fieldName == "allyHeroFrame" )
			_allyHeroFrame.Reset();
		else if ( fieldName == "localHeroFrame" )
			_localHeroFrame.Reset();
		else if ( fieldName == "icons" )
			_icons.Reset();
		else if ( fieldName == "targetZoneColor" )
			_targetZoneColor.Reset();
		else if ( fieldName == "targetZoneLineThickness" )
			_targetZoneLineThickness.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "normalOpacity" )
			return _normalOpacity.IsDerivedFromParent();
		if ( fieldName == "minigameOpacity" )
			return _minigameOpacity.IsDerivedFromParent();
		if ( fieldName == "transitionVelocity" )
			return _transitionVelocity.IsDerivedFromParent();
		if ( fieldName == "signalLifeTime" )
			return _signalLifeTime.IsDerivedFromParent();
		if ( fieldName == "signalDefaultColor" )
			return _signalDefaultColor.IsDerivedFromParent();
		if ( fieldName == "enemyColor" )
			return _enemyColor.IsDerivedFromParent();
		if ( fieldName == "allyColor" )
			return _allyColor.IsDerivedFromParent();
		if ( fieldName == "neutralColor" )
			return _neutralColor.IsDerivedFromParent();
		if ( fieldName == "enemyHeroFrame" )
			return _enemyHeroFrame.IsDerivedFromParent();
		if ( fieldName == "allyHeroFrame" )
			return _allyHeroFrame.IsDerivedFromParent();
		if ( fieldName == "localHeroFrame" )
			return _localHeroFrame.IsDerivedFromParent();
		if ( fieldName == "icons" )
			return _icons.IsDerivedFromParent();
		if ( fieldName == "targetZoneColor" )
			return _targetZoneColor.IsDerivedFromParent();
		if ( fieldName == "targetZoneLineThickness" )
			return _targetZoneLineThickness.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("StatisticData")]
public class DBStatisticData : DBResource
{
	private UndoRedoDBPtr<DBStatisticData> ___parent;
	[HideInOutliner]
	public new DBPtr<DBStatisticData> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _winnersTeamStr;
	private TextRef _losersTeamStr;
	private TextRef _levelFormatStr;
	private TextRef _favoritesFeatsStr;
	private TextRef _timeUnderBlessingStr;
	private TextRef _totalHeartsStr;
	private TextRef _heartsFromMenAndMinigamesStr;
	private TextRef _goldAndSilverFromMinigameStr;
	private TextRef _killingAssistantsStr;

	public TextRef winnersTeamStr { get { return _winnersTeamStr; } set { _winnersTeamStr.Assign( value ); } }

	public TextRef losersTeamStr { get { return _losersTeamStr; } set { _losersTeamStr.Assign( value ); } }

	public TextRef levelFormatStr { get { return _levelFormatStr; } set { _levelFormatStr.Assign( value ); } }

	public TextRef favoritesFeatsStr { get { return _favoritesFeatsStr; } set { _favoritesFeatsStr.Assign( value ); } }

	public TextRef timeUnderBlessingStr { get { return _timeUnderBlessingStr; } set { _timeUnderBlessingStr.Assign( value ); } }

	public TextRef totalHeartsStr { get { return _totalHeartsStr; } set { _totalHeartsStr.Assign( value ); } }

	public TextRef heartsFromMenAndMinigamesStr { get { return _heartsFromMenAndMinigamesStr; } set { _heartsFromMenAndMinigamesStr.Assign( value ); } }

	public TextRef goldAndSilverFromMinigameStr { get { return _goldAndSilverFromMinigameStr; } set { _goldAndSilverFromMinigameStr.Assign( value ); } }

	public TextRef killingAssistantsStr { get { return _killingAssistantsStr; } set { _killingAssistantsStr.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBStatisticData>(owner);
		_winnersTeamStr = new TextRef( owner, new TextRef() );
		_losersTeamStr = new TextRef( owner, new TextRef() );
		_levelFormatStr = new TextRef( owner, new TextRef() );
		_favoritesFeatsStr = new TextRef( owner, new TextRef() );
		_timeUnderBlessingStr = new TextRef( owner, new TextRef() );
		_totalHeartsStr = new TextRef( owner, new TextRef() );
		_heartsFromMenAndMinigamesStr = new TextRef( owner, new TextRef() );
		_goldAndSilverFromMinigameStr = new TextRef( owner, new TextRef() );
		_killingAssistantsStr = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_winnersTeamStr.Changed += FireChangedEvent;
		_losersTeamStr.Changed += FireChangedEvent;
		_levelFormatStr.Changed += FireChangedEvent;
		_favoritesFeatsStr.Changed += FireChangedEvent;
		_timeUnderBlessingStr.Changed += FireChangedEvent;
		_totalHeartsStr.Changed += FireChangedEvent;
		_heartsFromMenAndMinigamesStr.Changed += FireChangedEvent;
		_goldAndSilverFromMinigameStr.Changed += FireChangedEvent;
		_killingAssistantsStr.Changed += FireChangedEvent;
	}

	public DBStatisticData()
	{
		Initialize( this );
	}
	private void AssignSelf( DBStatisticData source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBStatisticData" );
		winnersTeamStr = source.winnersTeamStr;
		losersTeamStr = source.losersTeamStr;
		levelFormatStr = source.levelFormatStr;
		favoritesFeatsStr = source.favoritesFeatsStr;
		timeUnderBlessingStr = source.timeUnderBlessingStr;
		totalHeartsStr = source.totalHeartsStr;
		heartsFromMenAndMinigamesStr = source.heartsFromMenAndMinigamesStr;
		goldAndSilverFromMinigameStr = source.goldAndSilverFromMinigameStr;
		killingAssistantsStr = source.killingAssistantsStr;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBStatisticData source = _source as DBStatisticData;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBStatisticData" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBStatisticData newParent = rawParent == null ? null : rawParent.Get<DBStatisticData>();
		if ( newParent == null && _newParent is DBStatisticData )
			newParent = _newParent as DBStatisticData;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_winnersTeamStr.SetParent( newParent == null ? null : newParent._winnersTeamStr );
		_losersTeamStr.SetParent( newParent == null ? null : newParent._losersTeamStr );
		_levelFormatStr.SetParent( newParent == null ? null : newParent._levelFormatStr );
		_favoritesFeatsStr.SetParent( newParent == null ? null : newParent._favoritesFeatsStr );
		_timeUnderBlessingStr.SetParent( newParent == null ? null : newParent._timeUnderBlessingStr );
		_totalHeartsStr.SetParent( newParent == null ? null : newParent._totalHeartsStr );
		_heartsFromMenAndMinigamesStr.SetParent( newParent == null ? null : newParent._heartsFromMenAndMinigamesStr );
		_goldAndSilverFromMinigameStr.SetParent( newParent == null ? null : newParent._goldAndSilverFromMinigameStr );
		_killingAssistantsStr.SetParent( newParent == null ? null : newParent._killingAssistantsStr );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_winnersTeamStr.Reset();
		_losersTeamStr.Reset();
		_levelFormatStr.Reset();
		_favoritesFeatsStr.Reset();
		_timeUnderBlessingStr.Reset();
		_totalHeartsStr.Reset();
		_heartsFromMenAndMinigamesStr.Reset();
		_goldAndSilverFromMinigameStr.Reset();
		_killingAssistantsStr.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_winnersTeamStr.IsDerivedFromParent()
			&& _losersTeamStr.IsDerivedFromParent()
			&& _levelFormatStr.IsDerivedFromParent()
			&& _favoritesFeatsStr.IsDerivedFromParent()
			&& _timeUnderBlessingStr.IsDerivedFromParent()
			&& _totalHeartsStr.IsDerivedFromParent()
			&& _heartsFromMenAndMinigamesStr.IsDerivedFromParent()
			&& _goldAndSilverFromMinigameStr.IsDerivedFromParent()
			&& _killingAssistantsStr.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "winnersTeamStr" )
			_winnersTeamStr.Reset();
		else if ( fieldName == "losersTeamStr" )
			_losersTeamStr.Reset();
		else if ( fieldName == "levelFormatStr" )
			_levelFormatStr.Reset();
		else if ( fieldName == "favoritesFeatsStr" )
			_favoritesFeatsStr.Reset();
		else if ( fieldName == "timeUnderBlessingStr" )
			_timeUnderBlessingStr.Reset();
		else if ( fieldName == "totalHeartsStr" )
			_totalHeartsStr.Reset();
		else if ( fieldName == "heartsFromMenAndMinigamesStr" )
			_heartsFromMenAndMinigamesStr.Reset();
		else if ( fieldName == "goldAndSilverFromMinigameStr" )
			_goldAndSilverFromMinigameStr.Reset();
		else if ( fieldName == "killingAssistantsStr" )
			_killingAssistantsStr.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "winnersTeamStr" )
			return _winnersTeamStr.IsDerivedFromParent();
		if ( fieldName == "losersTeamStr" )
			return _losersTeamStr.IsDerivedFromParent();
		if ( fieldName == "levelFormatStr" )
			return _levelFormatStr.IsDerivedFromParent();
		if ( fieldName == "favoritesFeatsStr" )
			return _favoritesFeatsStr.IsDerivedFromParent();
		if ( fieldName == "timeUnderBlessingStr" )
			return _timeUnderBlessingStr.IsDerivedFromParent();
		if ( fieldName == "totalHeartsStr" )
			return _totalHeartsStr.IsDerivedFromParent();
		if ( fieldName == "heartsFromMenAndMinigamesStr" )
			return _heartsFromMenAndMinigamesStr.IsDerivedFromParent();
		if ( fieldName == "goldAndSilverFromMinigameStr" )
			return _goldAndSilverFromMinigameStr.IsDerivedFromParent();
		if ( fieldName == "killingAssistantsStr" )
			return _killingAssistantsStr.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("TTIP")]
public class DBTooltip : DBResource
{
	private UndoRedoDBPtr<DBTooltip> ___parent;
	[HideInOutliner]
	public new DBPtr<DBTooltip> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _friendStyle;
	private TextRef _enemyStyle;
	private TextRef _heroInfo;
	private TextRef _unitInfo;

	public TextRef friendStyle { get { return _friendStyle; } set { _friendStyle.Assign( value ); } }

	public TextRef enemyStyle { get { return _enemyStyle; } set { _enemyStyle.Assign( value ); } }

	public TextRef heroInfo { get { return _heroInfo; } set { _heroInfo.Assign( value ); } }

	public TextRef unitInfo { get { return _unitInfo; } set { _unitInfo.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBTooltip>(owner);
		_friendStyle = new TextRef( owner, new TextRef() );
		_enemyStyle = new TextRef( owner, new TextRef() );
		_heroInfo = new TextRef( owner, new TextRef() );
		_unitInfo = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_friendStyle.Changed += FireChangedEvent;
		_enemyStyle.Changed += FireChangedEvent;
		_heroInfo.Changed += FireChangedEvent;
		_unitInfo.Changed += FireChangedEvent;
	}

	public DBTooltip()
	{
		Initialize( this );
	}
	private void AssignSelf( DBTooltip source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBTooltip" );
		friendStyle = source.friendStyle;
		enemyStyle = source.enemyStyle;
		heroInfo = source.heroInfo;
		unitInfo = source.unitInfo;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBTooltip source = _source as DBTooltip;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBTooltip" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBTooltip newParent = rawParent == null ? null : rawParent.Get<DBTooltip>();
		if ( newParent == null && _newParent is DBTooltip )
			newParent = _newParent as DBTooltip;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_friendStyle.SetParent( newParent == null ? null : newParent._friendStyle );
		_enemyStyle.SetParent( newParent == null ? null : newParent._enemyStyle );
		_heroInfo.SetParent( newParent == null ? null : newParent._heroInfo );
		_unitInfo.SetParent( newParent == null ? null : newParent._unitInfo );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_friendStyle.Reset();
		_enemyStyle.Reset();
		_heroInfo.Reset();
		_unitInfo.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_friendStyle.IsDerivedFromParent()
			&& _enemyStyle.IsDerivedFromParent()
			&& _heroInfo.IsDerivedFromParent()
			&& _unitInfo.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "friendStyle" )
			_friendStyle.Reset();
		else if ( fieldName == "enemyStyle" )
			_enemyStyle.Reset();
		else if ( fieldName == "heroInfo" )
			_heroInfo.Reset();
		else if ( fieldName == "unitInfo" )
			_unitInfo.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "friendStyle" )
			return _friendStyle.IsDerivedFromParent();
		if ( fieldName == "enemyStyle" )
			return _enemyStyle.IsDerivedFromParent();
		if ( fieldName == "heroInfo" )
			return _heroInfo.IsDerivedFromParent();
		if ( fieldName == "unitInfo" )
			return _unitInfo.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(12)]
[UseTypeName("UIDT")]
public class DBUIData : DBResource
{
	private UndoRedoDBPtr<DBUIData> ___parent;
	[HideInOutliner]
	public new DBPtr<DBUIData> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<StatParams> _elements;
	private CombatStatuses _combatStatuses;
	private PWSoundEvents _soundEvents;
	private AttackType _attackType;
	private ImpulsiveBuffsParams _impulsiveBuffsParams;
	private HDRColor _colorPreselect;
	private HDRColor _outlineAllyColor;
	private HDRColor _outlineHostileColor;
	private HDRColor _outlineSelfColor;
	private UndoRedo<float> _outlineThickness;
	private GameUIData _gameUIData;
	private UndoRedoAssignableList<PathMarkerColor> _pathMarkerColor;
	private UndoRedoAssignableList<TextRef> _rarityValue;
	private DamageBloodMaskParams _bloodMaskParams;
	private UndoRedoAssignableList<ErrorMessageDescription> _errorMessageDescriptions;
	private CharStatTooltips _charStatTooltips;
	private UndoRedoDBPtr<DBMinimap> _minimap;
	private UndoRedo<float> _tooltipDownScaleLimit;
	private BattleStartAnnouncementParams _battleStartAnnouncementParams;
	private UndoRedo<float> _mouseScrollingFieldSize;
	private UndoRedoAssignableList<ChatChannelDescription> _chatChannelDescriptions;
	private HDRColor _adminMessageColor;
	private UndoRedoAssignableList<ResourceDescription> _resourcesDescriptions;
	private UndoRedoAssignableList<ResourceDescription> _clanWarsResourcesDescriptions;
	private VictoryDefeatImages _victoryDefeatImages;
	private IgnoreListParams _ignoreListParams;
	private MarkerSettings _markerSettings;
	private ForceToColorTable _forceColors;
	private DialogsSettings _dialogsSettings;
	private PingAbuseSettings _pingAbuseSettings;
	private HDRColor _blockSaturationColor;
	private MapModeCustomDescriptions _mapModeCustomDescriptions;
	private UndoRedoAssignableList<StringTextRefPair> _loadingScreenStatuses;
	private PremiumVisualInfo _premiumVisualInfo;
	private UndoRedoAssignableList<Locale> _locales;
	private UndoRedoAssignableList<TipOfTheDay> _tips;
	private UndoRedoAssignableList<ReportType> _reportTypes;
	private Binds _binds;
	private UndoRedoAssignableList<CountryFlag> _countryFlags;
	private BotDefaultFlags _botFlags;
	private UndoRedoAssignableList<DBPtr<CustomFlag>> _customFlags;
	private UndoRedoAssignableList<DBPtr<CustomFlag>> _adminFlags;
	private UndoRedoAssignableList<GuildShopTab> _guildShopTabs;
	private UndoRedoDBPtr<SmartChatConfiguration> _smartChat;
	private SmartChatAbuseSettings _smartChatAbuseSettings;
	private UndoRedo<int> _RecentPlayers;
	private UndoRedoDBPtr<CurrencyDescriptionList> _currencies;

	[Category( "Unit info params" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<StatParams> elements { get { return _elements; } set { _elements.Assign( value ); } }

	[Category( "Unit info params" )]
	[Description( "Combat screen status texts" )]
	public CombatStatuses combatStatuses { get { return _combatStatuses; } set { _combatStatuses.Assign( value ); } }

	[Description( "Session UI sound events" )]
	public PWSoundEvents soundEvents { get { return _soundEvents; } set { _soundEvents.Assign( value ); } }

	public AttackType attackType { get { return _attackType; } set { _attackType.Assign( value ); } }

	[Category( "Impulsive buffs" )]
	public ImpulsiveBuffsParams impulsiveBuffsParams { get { return _impulsiveBuffsParams; } set { _impulsiveBuffsParams.Assign( value ); } }

	[Category( "Preselection" )]
	[Description( "Color multiplier for preselection" )]
	public HDRColor colorPreselect { get { return _colorPreselect; } set { _colorPreselect.Assign( value ); } }

	[Category( "Preselection" )]
	[Description( "Color for selection outline (allies)" )]
	public HDRColor outlineAllyColor { get { return _outlineAllyColor; } set { _outlineAllyColor.Assign( value ); } }

	[Category( "Preselection" )]
	[Description( "Color for selection outline (hostiles)" )]
	public HDRColor outlineHostileColor { get { return _outlineHostileColor; } set { _outlineHostileColor.Assign( value ); } }

	[Category( "Preselection" )]
	[Description( "Color for selection outline (neutrals)" )]
	public HDRColor outlineSelfColor { get { return _outlineSelfColor; } set { _outlineSelfColor.Assign( value ); } }

	[Category( "Preselection" )]
	[Description( "Selection outline thickness, in meters" )]
	public float outlineThickness { get { return _outlineThickness.Get(); } set { _outlineThickness.Set( value ); } }

	[Category( "Data for adventure screen: pause messages." )]
	public GameUIData gameUIData { get { return _gameUIData; } set { _gameUIData.Assign( value ); } }

	[Category( "Path markers" )]
	[EnumArray(typeof(EPathMarker))]
	public libdb.IChangeableList<PathMarkerColor> pathMarkerColor { get { return _pathMarkerColor; } set { _pathMarkerColor.Assign( value ); } }

	[Category( "Talents text fields" )]
	[EnumArray(typeof(ETalentRarity))]
	public libdb.IChangeableList<TextRef> rarityValue { get { return _rarityValue; } set { _rarityValue.Assign( value ); } }

	[Description( "params for blood mask logic when hero is damaged" )]
	public DamageBloodMaskParams bloodMaskParams { get { return _bloodMaskParams; } set { _bloodMaskParams.Assign( value ); } }

	[Description( "Error messages descriptions" )]
	[EnumArray(typeof(EErrorMessageType))]
	public libdb.IChangeableList<ErrorMessageDescription> errorMessageDescriptions { get { return _errorMessageDescriptions; } set { _errorMessageDescriptions.Assign( value ); } }

	[Custom("Social")]
	[Description( "Tooltips for char stat" )]
	public CharStatTooltips charStatTooltips { get { return _charStatTooltips; } set { _charStatTooltips.Assign( value ); } }

	[Description( "Minimap settings" )]
	public DBPtr<DBMinimap> minimap { get { return _minimap.Get(); } set { _minimap.Set( value ); } }

	[Description( "Minimal value of tooltip down scale factor" )]
	public float tooltipDownScaleLimit { get { return _tooltipDownScaleLimit.Get(); } set { _tooltipDownScaleLimit.Set( value ); } }

	[Description( "params for battle start delay announcement" )]
	public BattleStartAnnouncementParams battleStartAnnouncementParams { get { return _battleStartAnnouncementParams; } set { _battleStartAnnouncementParams.Assign( value ); } }

	[Description( "Size of scrolling fields in pixels relative standard ui resolution" )]
	public float mouseScrollingFieldSize { get { return _mouseScrollingFieldSize.Get(); } set { _mouseScrollingFieldSize.Set( value ); } }

	[Custom("Social")]
	[Description( "Visual description for chat channels" )]
	[EnumArray(typeof(EChatChannel))]
	public libdb.IChangeableList<ChatChannelDescription> chatChannelDescriptions { get { return _chatChannelDescriptions; } set { _chatChannelDescriptions.Assign( value ); } }

	[Category( "Preselection" )]
	[Custom("Social")]
	[Description( "Color for administrator messages in Lobby chat " )]
	public HDRColor adminMessageColor { get { return _adminMessageColor; } set { _adminMessageColor.Assign( value ); } }

	[Description( "resources visual description" )]
	[EnumArray(typeof(EResourceType))]
	public libdb.IChangeableList<ResourceDescription> resourcesDescriptions { get { return _resourcesDescriptions; } set { _resourcesDescriptions.Assign( value ); } }

	[Description( "ClanWars resources visual description" )]
	[EnumArray(typeof(EClanWarsResourceType))]
	public libdb.IChangeableList<ResourceDescription> clanWarsResourcesDescriptions { get { return _clanWarsResourcesDescriptions; } set { _clanWarsResourcesDescriptions.Assign( value ); } }

	public VictoryDefeatImages victoryDefeatImages { get { return _victoryDefeatImages; } set { _victoryDefeatImages.Assign( value ); } }

	[Description( "text recources for ignore list" )]
	public IgnoreListParams ignoreListParams { get { return _ignoreListParams; } set { _ignoreListParams.Assign( value ); } }

	public MarkerSettings markerSettings { get { return _markerSettings; } set { _markerSettings.Assign( value ); } }

	[Custom("Social")]
	[Description( "Цветовая дифференциация мощи героев" )]
	public ForceToColorTable forceColors { get { return _forceColors; } set { _forceColors.Assign( value ); } }

	public DialogsSettings dialogsSettings { get { return _dialogsSettings; } set { _dialogsSettings.Assign( value ); } }

	[Description( "Настройки ограничений на пинг" )]
	public PingAbuseSettings pingAbuseSettings { get { return _pingAbuseSettings; } set { _pingAbuseSettings.Assign( value ); } }

	[Description( "Цвет для затемнения экрана при блокировании UI" )]
	public HDRColor blockSaturationColor { get { return _blockSaturationColor; } set { _blockSaturationColor.Assign( value ); } }

	[Description( "описание кастомных модификаторов. Гвардейцы/Маневры итд" )]
	public MapModeCustomDescriptions mapModeCustomDescriptions { get { return _mapModeCustomDescriptions; } set { _mapModeCustomDescriptions.Assign( value ); } }

	[Description( "список статусов загрузки" )]
	public libdb.IChangeableList<StringTextRefPair> loadingScreenStatuses { get { return _loadingScreenStatuses; } set { _loadingScreenStatuses.Assign( value ); } }

	[Description( "информация по отображению премиума" )]
	public PremiumVisualInfo premiumVisualInfo { get { return _premiumVisualInfo; } set { _premiumVisualInfo.Assign( value ); } }

	[Description( "список локалей для игроков" )]
	public libdb.IChangeableList<Locale> locales { get { return _locales; } set { _locales.Assign( value ); } }

	public libdb.IChangeableList<TipOfTheDay> tips { get { return _tips; } set { _tips.Assign( value ); } }

	[Custom("Social")]
	[Description( "список типов жалоб" )]
	public libdb.IChangeableList<ReportType> reportTypes { get { return _reportTypes; } set { _reportTypes.Assign( value ); } }

	[Custom("Social")]
	[Description( "визуальное описание биндов для настроек" )]
	public Binds binds { get { return _binds; } set { _binds.Assign( value ); } }

	[Custom("Social")]
	[Description( "список флагов стран" )]
	public libdb.IChangeableList<CountryFlag> countryFlags { get { return _countryFlags; } set { _countryFlags.Assign( value ); } }

	[Custom("Social")]
	[Description( "флаги для ботов" )]
	public BotDefaultFlags botFlags { get { return _botFlags; } set { _botFlags.Assign( value ); } }

	[Custom("Social")]
	[Description( "список платных флагов" )]
	public libdb.IChangeableList<DBPtr<CustomFlag>> customFlags { get { return _customFlags; } set { _customFlags.Assign( value ); } }

	[Custom("Social")]
	[Description( "список флагов админов" )]
	public libdb.IChangeableList<DBPtr<CustomFlag>> adminFlags { get { return _adminFlags; } set { _adminFlags.Assign( value ); } }

	[Custom("Social")]
	[Description( "Вкладки гильдийского магазина" )]
	public libdb.IChangeableList<GuildShopTab> guildShopTabs { get { return _guildShopTabs; } set { _guildShopTabs.Assign( value ); } }

	[Description( "Смарт-чат" )]
	public DBPtr<SmartChatConfiguration> smartChat { get { return _smartChat.Get(); } set { _smartChat.Set( value ); } }

	[Description( "Настройки анти-спама для смарт-чата" )]
	public SmartChatAbuseSettings smartChatAbuseSettings { get { return _smartChatAbuseSettings; } set { _smartChatAbuseSettings.Assign( value ); } }

	[Description( "Количество союзников, с которыми игрок играл в предыдущем бою, отображаемых в панели 'Недавние игроки' " )]
	public int RecentPlayers { get { return _RecentPlayers.Get(); } set { _RecentPlayers.Set( value ); } }

	[Description( "Описание кастомной валюты" )]
	public DBPtr<CurrencyDescriptionList> currencies { get { return _currencies.Get(); } set { _currencies.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBUIData>(owner);
		_elements = new UndoRedoAssignableList<StatParams>( owner, typeof( EStat ) );
		_combatStatuses = new CombatStatuses( owner );
		_soundEvents = new PWSoundEvents( owner );
		_attackType = new AttackType( owner );
		_impulsiveBuffsParams = new ImpulsiveBuffsParams( owner );
		HDRColor __colorPreselect = new HDRColor(); // Construct default object for colorPreselect
		__colorPreselect.R = 1.2f;
		__colorPreselect.G = 1.2f;
		__colorPreselect.B = 1.2f;
		_colorPreselect = new HDRColor( owner, __colorPreselect );
		HDRColor __outlineAllyColor = new HDRColor(); // Construct default object for outlineAllyColor
		__outlineAllyColor.R = 1.0f;
		__outlineAllyColor.G = 1.0f;
		_outlineAllyColor = new HDRColor( owner, __outlineAllyColor );
		HDRColor __outlineHostileColor = new HDRColor(); // Construct default object for outlineHostileColor
		__outlineHostileColor.R = 1.0f;
		_outlineHostileColor = new HDRColor( owner, __outlineHostileColor );
		HDRColor __outlineSelfColor = new HDRColor(); // Construct default object for outlineSelfColor
		__outlineSelfColor.R = 1.0f;
		_outlineSelfColor = new HDRColor( owner, __outlineSelfColor );
		_outlineThickness = new UndoRedo<float>( owner, 0.1f );
		_gameUIData = new GameUIData( owner );
		_pathMarkerColor = new UndoRedoAssignableList<PathMarkerColor>( owner, typeof( EPathMarker ) );
		_rarityValue = new UndoRedoAssignableList<TextRef>( owner, typeof( ETalentRarity ) );
		_bloodMaskParams = new DamageBloodMaskParams( owner );
		_errorMessageDescriptions = new UndoRedoAssignableList<ErrorMessageDescription>( owner, typeof( EErrorMessageType ) );
		_charStatTooltips = new CharStatTooltips( owner );
		_minimap = new UndoRedoDBPtr<DBMinimap>( owner );
		_tooltipDownScaleLimit = new UndoRedo<float>( owner, 0.5f );
		_battleStartAnnouncementParams = new BattleStartAnnouncementParams( owner );
		_mouseScrollingFieldSize = new UndoRedo<float>( owner, 20.0f );
		_chatChannelDescriptions = new UndoRedoAssignableList<ChatChannelDescription>( owner, typeof( EChatChannel ) );
		HDRColor __adminMessageColor = new HDRColor(); // Construct default object for adminMessageColor
		__adminMessageColor.R = 1.0f;
		_adminMessageColor = new HDRColor( owner, __adminMessageColor );
		_resourcesDescriptions = new UndoRedoAssignableList<ResourceDescription>( owner, typeof( EResourceType ) );
		_clanWarsResourcesDescriptions = new UndoRedoAssignableList<ResourceDescription>( owner, typeof( EClanWarsResourceType ) );
		_victoryDefeatImages = new VictoryDefeatImages( owner );
		_ignoreListParams = new IgnoreListParams( owner );
		_markerSettings = new MarkerSettings( owner );
		_forceColors = new ForceToColorTable( owner );
		_dialogsSettings = new DialogsSettings( owner );
		_pingAbuseSettings = new PingAbuseSettings( owner );
		HDRColor __blockSaturationColor = new HDRColor(); // Construct default object for blockSaturationColor
		__blockSaturationColor.R = 1.0f;
		__blockSaturationColor.G = 1.0f;
		__blockSaturationColor.B = 1.0f;
		_blockSaturationColor = new HDRColor( owner, __blockSaturationColor );
		_mapModeCustomDescriptions = new MapModeCustomDescriptions( owner );
		_loadingScreenStatuses = new UndoRedoAssignableList<StringTextRefPair>( owner );
		_premiumVisualInfo = new PremiumVisualInfo( owner );
		_locales = new UndoRedoAssignableList<Locale>( owner );
		_tips = new UndoRedoAssignableList<TipOfTheDay>( owner );
		_reportTypes = new UndoRedoAssignableList<ReportType>( owner );
		_binds = new Binds( owner );
		_countryFlags = new UndoRedoAssignableList<CountryFlag>( owner );
		_botFlags = new BotDefaultFlags( owner );
		_customFlags = new UndoRedoAssignableList<DBPtr<CustomFlag>>( owner );
		_adminFlags = new UndoRedoAssignableList<DBPtr<CustomFlag>>( owner );
		_guildShopTabs = new UndoRedoAssignableList<GuildShopTab>( owner );
		_smartChat = new UndoRedoDBPtr<SmartChatConfiguration>( owner );
		_smartChatAbuseSettings = new SmartChatAbuseSettings( owner );
		_RecentPlayers = new UndoRedo<int>( owner, 20 );
		_currencies = new UndoRedoDBPtr<CurrencyDescriptionList>( owner );
		___parent.Changed += FireChangedEvent;
		_elements.Changed += FireChangedEvent;
		_combatStatuses.Changed += FireChangedEvent;
		_soundEvents.Changed += FireChangedEvent;
		_attackType.Changed += FireChangedEvent;
		_impulsiveBuffsParams.Changed += FireChangedEvent;
		_colorPreselect.Changed += FireChangedEvent;
		_outlineAllyColor.Changed += FireChangedEvent;
		_outlineHostileColor.Changed += FireChangedEvent;
		_outlineSelfColor.Changed += FireChangedEvent;
		_outlineThickness.Changed += FireChangedEvent;
		_gameUIData.Changed += FireChangedEvent;
		_pathMarkerColor.Changed += FireChangedEvent;
		_rarityValue.Changed += FireChangedEvent;
		_bloodMaskParams.Changed += FireChangedEvent;
		_errorMessageDescriptions.Changed += FireChangedEvent;
		_charStatTooltips.Changed += FireChangedEvent;
		_minimap.Changed += FireChangedEvent;
		_tooltipDownScaleLimit.Changed += FireChangedEvent;
		_battleStartAnnouncementParams.Changed += FireChangedEvent;
		_mouseScrollingFieldSize.Changed += FireChangedEvent;
		_chatChannelDescriptions.Changed += FireChangedEvent;
		_adminMessageColor.Changed += FireChangedEvent;
		_resourcesDescriptions.Changed += FireChangedEvent;
		_clanWarsResourcesDescriptions.Changed += FireChangedEvent;
		_victoryDefeatImages.Changed += FireChangedEvent;
		_ignoreListParams.Changed += FireChangedEvent;
		_markerSettings.Changed += FireChangedEvent;
		_forceColors.Changed += FireChangedEvent;
		_dialogsSettings.Changed += FireChangedEvent;
		_pingAbuseSettings.Changed += FireChangedEvent;
		_blockSaturationColor.Changed += FireChangedEvent;
		_mapModeCustomDescriptions.Changed += FireChangedEvent;
		_loadingScreenStatuses.Changed += FireChangedEvent;
		_premiumVisualInfo.Changed += FireChangedEvent;
		_locales.Changed += FireChangedEvent;
		_tips.Changed += FireChangedEvent;
		_reportTypes.Changed += FireChangedEvent;
		_binds.Changed += FireChangedEvent;
		_countryFlags.Changed += FireChangedEvent;
		_botFlags.Changed += FireChangedEvent;
		_customFlags.Changed += FireChangedEvent;
		_adminFlags.Changed += FireChangedEvent;
		_guildShopTabs.Changed += FireChangedEvent;
		_smartChat.Changed += FireChangedEvent;
		_smartChatAbuseSettings.Changed += FireChangedEvent;
		_RecentPlayers.Changed += FireChangedEvent;
		_currencies.Changed += FireChangedEvent;
	}

	public DBUIData()
	{
		Initialize( this );
	}
	private void AssignSelf( DBUIData source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBUIData" );
		elements = source.elements;
		combatStatuses = source.combatStatuses;
		soundEvents = source.soundEvents;
		attackType = source.attackType;
		impulsiveBuffsParams = source.impulsiveBuffsParams;
		colorPreselect = source.colorPreselect;
		outlineAllyColor = source.outlineAllyColor;
		outlineHostileColor = source.outlineHostileColor;
		outlineSelfColor = source.outlineSelfColor;
		outlineThickness = source.outlineThickness;
		gameUIData = source.gameUIData;
		pathMarkerColor = source.pathMarkerColor;
		rarityValue = source.rarityValue;
		bloodMaskParams = source.bloodMaskParams;
		errorMessageDescriptions = source.errorMessageDescriptions;
		charStatTooltips = source.charStatTooltips;
		minimap = source.minimap;
		tooltipDownScaleLimit = source.tooltipDownScaleLimit;
		battleStartAnnouncementParams = source.battleStartAnnouncementParams;
		mouseScrollingFieldSize = source.mouseScrollingFieldSize;
		chatChannelDescriptions = source.chatChannelDescriptions;
		adminMessageColor = source.adminMessageColor;
		resourcesDescriptions = source.resourcesDescriptions;
		clanWarsResourcesDescriptions = source.clanWarsResourcesDescriptions;
		victoryDefeatImages = source.victoryDefeatImages;
		ignoreListParams = source.ignoreListParams;
		markerSettings = source.markerSettings;
		forceColors = source.forceColors;
		dialogsSettings = source.dialogsSettings;
		pingAbuseSettings = source.pingAbuseSettings;
		blockSaturationColor = source.blockSaturationColor;
		mapModeCustomDescriptions = source.mapModeCustomDescriptions;
		loadingScreenStatuses = source.loadingScreenStatuses;
		premiumVisualInfo = source.premiumVisualInfo;
		locales = source.locales;
		tips = source.tips;
		reportTypes = source.reportTypes;
		binds = source.binds;
		countryFlags = source.countryFlags;
		botFlags = source.botFlags;
		customFlags = source.customFlags;
		adminFlags = source.adminFlags;
		guildShopTabs = source.guildShopTabs;
		smartChat = source.smartChat;
		smartChatAbuseSettings = source.smartChatAbuseSettings;
		RecentPlayers = source.RecentPlayers;
		currencies = source.currencies;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBUIData source = _source as DBUIData;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBUIData" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBUIData newParent = rawParent == null ? null : rawParent.Get<DBUIData>();
		if ( newParent == null && _newParent is DBUIData )
			newParent = _newParent as DBUIData;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_elements.SetParent( newParent == null ? null : newParent._elements );
		_combatStatuses.SetParent( newParent == null ? null : newParent._combatStatuses );
		_soundEvents.SetParent( newParent == null ? null : newParent._soundEvents );
		_attackType.SetParent( newParent == null ? null : newParent._attackType );
		_impulsiveBuffsParams.SetParent( newParent == null ? null : newParent._impulsiveBuffsParams );
		_colorPreselect.SetParent( newParent == null ? null : newParent._colorPreselect );
		_outlineAllyColor.SetParent( newParent == null ? null : newParent._outlineAllyColor );
		_outlineHostileColor.SetParent( newParent == null ? null : newParent._outlineHostileColor );
		_outlineSelfColor.SetParent( newParent == null ? null : newParent._outlineSelfColor );
		_outlineThickness.SetParent( newParent == null ? null : newParent._outlineThickness );
		_gameUIData.SetParent( newParent == null ? null : newParent._gameUIData );
		_pathMarkerColor.SetParent( newParent == null ? null : newParent._pathMarkerColor );
		_rarityValue.SetParent( newParent == null ? null : newParent._rarityValue );
		_bloodMaskParams.SetParent( newParent == null ? null : newParent._bloodMaskParams );
		_errorMessageDescriptions.SetParent( newParent == null ? null : newParent._errorMessageDescriptions );
		_charStatTooltips.SetParent( newParent == null ? null : newParent._charStatTooltips );
		_minimap.SetParent( newParent == null ? null : newParent._minimap );
		_tooltipDownScaleLimit.SetParent( newParent == null ? null : newParent._tooltipDownScaleLimit );
		_battleStartAnnouncementParams.SetParent( newParent == null ? null : newParent._battleStartAnnouncementParams );
		_mouseScrollingFieldSize.SetParent( newParent == null ? null : newParent._mouseScrollingFieldSize );
		_chatChannelDescriptions.SetParent( newParent == null ? null : newParent._chatChannelDescriptions );
		_adminMessageColor.SetParent( newParent == null ? null : newParent._adminMessageColor );
		_resourcesDescriptions.SetParent( newParent == null ? null : newParent._resourcesDescriptions );
		_clanWarsResourcesDescriptions.SetParent( newParent == null ? null : newParent._clanWarsResourcesDescriptions );
		_victoryDefeatImages.SetParent( newParent == null ? null : newParent._victoryDefeatImages );
		_ignoreListParams.SetParent( newParent == null ? null : newParent._ignoreListParams );
		_markerSettings.SetParent( newParent == null ? null : newParent._markerSettings );
		_forceColors.SetParent( newParent == null ? null : newParent._forceColors );
		_dialogsSettings.SetParent( newParent == null ? null : newParent._dialogsSettings );
		_pingAbuseSettings.SetParent( newParent == null ? null : newParent._pingAbuseSettings );
		_blockSaturationColor.SetParent( newParent == null ? null : newParent._blockSaturationColor );
		_mapModeCustomDescriptions.SetParent( newParent == null ? null : newParent._mapModeCustomDescriptions );
		_loadingScreenStatuses.SetParent( newParent == null ? null : newParent._loadingScreenStatuses );
		_premiumVisualInfo.SetParent( newParent == null ? null : newParent._premiumVisualInfo );
		_locales.SetParent( newParent == null ? null : newParent._locales );
		_tips.SetParent( newParent == null ? null : newParent._tips );
		_reportTypes.SetParent( newParent == null ? null : newParent._reportTypes );
		_binds.SetParent( newParent == null ? null : newParent._binds );
		_countryFlags.SetParent( newParent == null ? null : newParent._countryFlags );
		_botFlags.SetParent( newParent == null ? null : newParent._botFlags );
		_customFlags.SetParent( newParent == null ? null : newParent._customFlags );
		_adminFlags.SetParent( newParent == null ? null : newParent._adminFlags );
		_guildShopTabs.SetParent( newParent == null ? null : newParent._guildShopTabs );
		_smartChat.SetParent( newParent == null ? null : newParent._smartChat );
		_smartChatAbuseSettings.SetParent( newParent == null ? null : newParent._smartChatAbuseSettings );
		_RecentPlayers.SetParent( newParent == null ? null : newParent._RecentPlayers );
		_currencies.SetParent( newParent == null ? null : newParent._currencies );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_elements.Reset();
		_combatStatuses.Reset();
		_soundEvents.Reset();
		_attackType.Reset();
		_impulsiveBuffsParams.Reset();
		_colorPreselect.Reset();
		_outlineAllyColor.Reset();
		_outlineHostileColor.Reset();
		_outlineSelfColor.Reset();
		_outlineThickness.Reset();
		_gameUIData.Reset();
		_pathMarkerColor.Reset();
		_rarityValue.Reset();
		_bloodMaskParams.Reset();
		_errorMessageDescriptions.Reset();
		_charStatTooltips.Reset();
		_minimap.Reset();
		_tooltipDownScaleLimit.Reset();
		_battleStartAnnouncementParams.Reset();
		_mouseScrollingFieldSize.Reset();
		_chatChannelDescriptions.Reset();
		_adminMessageColor.Reset();
		_resourcesDescriptions.Reset();
		_clanWarsResourcesDescriptions.Reset();
		_victoryDefeatImages.Reset();
		_ignoreListParams.Reset();
		_markerSettings.Reset();
		_forceColors.Reset();
		_dialogsSettings.Reset();
		_pingAbuseSettings.Reset();
		_blockSaturationColor.Reset();
		_mapModeCustomDescriptions.Reset();
		_loadingScreenStatuses.Reset();
		_premiumVisualInfo.Reset();
		_locales.Reset();
		_tips.Reset();
		_reportTypes.Reset();
		_binds.Reset();
		_countryFlags.Reset();
		_botFlags.Reset();
		_customFlags.Reset();
		_adminFlags.Reset();
		_guildShopTabs.Reset();
		_smartChat.Reset();
		_smartChatAbuseSettings.Reset();
		_RecentPlayers.Reset();
		_currencies.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_elements.IsDerivedFromParent()
			&& _combatStatuses.IsDerivedFromParent()
			&& _soundEvents.IsDerivedFromParent()
			&& _attackType.IsDerivedFromParent()
			&& _impulsiveBuffsParams.IsDerivedFromParent()
			&& _colorPreselect.IsDerivedFromParent()
			&& _outlineAllyColor.IsDerivedFromParent()
			&& _outlineHostileColor.IsDerivedFromParent()
			&& _outlineSelfColor.IsDerivedFromParent()
			&& _outlineThickness.IsDerivedFromParent()
			&& _gameUIData.IsDerivedFromParent()
			&& _pathMarkerColor.IsDerivedFromParent()
			&& _rarityValue.IsDerivedFromParent()
			&& _bloodMaskParams.IsDerivedFromParent()
			&& _errorMessageDescriptions.IsDerivedFromParent()
			&& _charStatTooltips.IsDerivedFromParent()
			&& _minimap.IsDerivedFromParent()
			&& _tooltipDownScaleLimit.IsDerivedFromParent()
			&& _battleStartAnnouncementParams.IsDerivedFromParent()
			&& _mouseScrollingFieldSize.IsDerivedFromParent()
			&& _chatChannelDescriptions.IsDerivedFromParent()
			&& _adminMessageColor.IsDerivedFromParent()
			&& _resourcesDescriptions.IsDerivedFromParent()
			&& _clanWarsResourcesDescriptions.IsDerivedFromParent()
			&& _victoryDefeatImages.IsDerivedFromParent()
			&& _ignoreListParams.IsDerivedFromParent()
			&& _markerSettings.IsDerivedFromParent()
			&& _forceColors.IsDerivedFromParent()
			&& _dialogsSettings.IsDerivedFromParent()
			&& _pingAbuseSettings.IsDerivedFromParent()
			&& _blockSaturationColor.IsDerivedFromParent()
			&& _mapModeCustomDescriptions.IsDerivedFromParent()
			&& _loadingScreenStatuses.IsDerivedFromParent()
			&& _premiumVisualInfo.IsDerivedFromParent()
			&& _locales.IsDerivedFromParent()
			&& _tips.IsDerivedFromParent()
			&& _reportTypes.IsDerivedFromParent()
			&& _binds.IsDerivedFromParent()
			&& _countryFlags.IsDerivedFromParent()
			&& _botFlags.IsDerivedFromParent()
			&& _customFlags.IsDerivedFromParent()
			&& _adminFlags.IsDerivedFromParent()
			&& _guildShopTabs.IsDerivedFromParent()
			&& _smartChat.IsDerivedFromParent()
			&& _smartChatAbuseSettings.IsDerivedFromParent()
			&& _RecentPlayers.IsDerivedFromParent()
			&& _currencies.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "elements" )
			_elements.Reset();
		else if ( fieldName == "combatStatuses" )
			_combatStatuses.Reset();
		else if ( fieldName == "soundEvents" )
			_soundEvents.Reset();
		else if ( fieldName == "attackType" )
			_attackType.Reset();
		else if ( fieldName == "impulsiveBuffsParams" )
			_impulsiveBuffsParams.Reset();
		else if ( fieldName == "colorPreselect" )
			_colorPreselect.Reset();
		else if ( fieldName == "outlineAllyColor" )
			_outlineAllyColor.Reset();
		else if ( fieldName == "outlineHostileColor" )
			_outlineHostileColor.Reset();
		else if ( fieldName == "outlineSelfColor" )
			_outlineSelfColor.Reset();
		else if ( fieldName == "outlineThickness" )
			_outlineThickness.Reset();
		else if ( fieldName == "gameUIData" )
			_gameUIData.Reset();
		else if ( fieldName == "pathMarkerColor" )
			_pathMarkerColor.Reset();
		else if ( fieldName == "rarityValue" )
			_rarityValue.Reset();
		else if ( fieldName == "bloodMaskParams" )
			_bloodMaskParams.Reset();
		else if ( fieldName == "errorMessageDescriptions" )
			_errorMessageDescriptions.Reset();
		else if ( fieldName == "charStatTooltips" )
			_charStatTooltips.Reset();
		else if ( fieldName == "minimap" )
			_minimap.Reset();
		else if ( fieldName == "tooltipDownScaleLimit" )
			_tooltipDownScaleLimit.Reset();
		else if ( fieldName == "battleStartAnnouncementParams" )
			_battleStartAnnouncementParams.Reset();
		else if ( fieldName == "mouseScrollingFieldSize" )
			_mouseScrollingFieldSize.Reset();
		else if ( fieldName == "chatChannelDescriptions" )
			_chatChannelDescriptions.Reset();
		else if ( fieldName == "adminMessageColor" )
			_adminMessageColor.Reset();
		else if ( fieldName == "resourcesDescriptions" )
			_resourcesDescriptions.Reset();
		else if ( fieldName == "clanWarsResourcesDescriptions" )
			_clanWarsResourcesDescriptions.Reset();
		else if ( fieldName == "victoryDefeatImages" )
			_victoryDefeatImages.Reset();
		else if ( fieldName == "ignoreListParams" )
			_ignoreListParams.Reset();
		else if ( fieldName == "markerSettings" )
			_markerSettings.Reset();
		else if ( fieldName == "forceColors" )
			_forceColors.Reset();
		else if ( fieldName == "dialogsSettings" )
			_dialogsSettings.Reset();
		else if ( fieldName == "pingAbuseSettings" )
			_pingAbuseSettings.Reset();
		else if ( fieldName == "blockSaturationColor" )
			_blockSaturationColor.Reset();
		else if ( fieldName == "mapModeCustomDescriptions" )
			_mapModeCustomDescriptions.Reset();
		else if ( fieldName == "loadingScreenStatuses" )
			_loadingScreenStatuses.Reset();
		else if ( fieldName == "premiumVisualInfo" )
			_premiumVisualInfo.Reset();
		else if ( fieldName == "locales" )
			_locales.Reset();
		else if ( fieldName == "tips" )
			_tips.Reset();
		else if ( fieldName == "reportTypes" )
			_reportTypes.Reset();
		else if ( fieldName == "binds" )
			_binds.Reset();
		else if ( fieldName == "countryFlags" )
			_countryFlags.Reset();
		else if ( fieldName == "botFlags" )
			_botFlags.Reset();
		else if ( fieldName == "customFlags" )
			_customFlags.Reset();
		else if ( fieldName == "adminFlags" )
			_adminFlags.Reset();
		else if ( fieldName == "guildShopTabs" )
			_guildShopTabs.Reset();
		else if ( fieldName == "smartChat" )
			_smartChat.Reset();
		else if ( fieldName == "smartChatAbuseSettings" )
			_smartChatAbuseSettings.Reset();
		else if ( fieldName == "RecentPlayers" )
			_RecentPlayers.Reset();
		else if ( fieldName == "currencies" )
			_currencies.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "elements" )
			return _elements.IsDerivedFromParent();
		if ( fieldName == "combatStatuses" )
			return _combatStatuses.IsDerivedFromParent();
		if ( fieldName == "soundEvents" )
			return _soundEvents.IsDerivedFromParent();
		if ( fieldName == "attackType" )
			return _attackType.IsDerivedFromParent();
		if ( fieldName == "impulsiveBuffsParams" )
			return _impulsiveBuffsParams.IsDerivedFromParent();
		if ( fieldName == "colorPreselect" )
			return _colorPreselect.IsDerivedFromParent();
		if ( fieldName == "outlineAllyColor" )
			return _outlineAllyColor.IsDerivedFromParent();
		if ( fieldName == "outlineHostileColor" )
			return _outlineHostileColor.IsDerivedFromParent();
		if ( fieldName == "outlineSelfColor" )
			return _outlineSelfColor.IsDerivedFromParent();
		if ( fieldName == "outlineThickness" )
			return _outlineThickness.IsDerivedFromParent();
		if ( fieldName == "gameUIData" )
			return _gameUIData.IsDerivedFromParent();
		if ( fieldName == "pathMarkerColor" )
			return _pathMarkerColor.IsDerivedFromParent();
		if ( fieldName == "rarityValue" )
			return _rarityValue.IsDerivedFromParent();
		if ( fieldName == "bloodMaskParams" )
			return _bloodMaskParams.IsDerivedFromParent();
		if ( fieldName == "errorMessageDescriptions" )
			return _errorMessageDescriptions.IsDerivedFromParent();
		if ( fieldName == "charStatTooltips" )
			return _charStatTooltips.IsDerivedFromParent();
		if ( fieldName == "minimap" )
			return _minimap.IsDerivedFromParent();
		if ( fieldName == "tooltipDownScaleLimit" )
			return _tooltipDownScaleLimit.IsDerivedFromParent();
		if ( fieldName == "battleStartAnnouncementParams" )
			return _battleStartAnnouncementParams.IsDerivedFromParent();
		if ( fieldName == "mouseScrollingFieldSize" )
			return _mouseScrollingFieldSize.IsDerivedFromParent();
		if ( fieldName == "chatChannelDescriptions" )
			return _chatChannelDescriptions.IsDerivedFromParent();
		if ( fieldName == "adminMessageColor" )
			return _adminMessageColor.IsDerivedFromParent();
		if ( fieldName == "resourcesDescriptions" )
			return _resourcesDescriptions.IsDerivedFromParent();
		if ( fieldName == "clanWarsResourcesDescriptions" )
			return _clanWarsResourcesDescriptions.IsDerivedFromParent();
		if ( fieldName == "victoryDefeatImages" )
			return _victoryDefeatImages.IsDerivedFromParent();
		if ( fieldName == "ignoreListParams" )
			return _ignoreListParams.IsDerivedFromParent();
		if ( fieldName == "markerSettings" )
			return _markerSettings.IsDerivedFromParent();
		if ( fieldName == "forceColors" )
			return _forceColors.IsDerivedFromParent();
		if ( fieldName == "dialogsSettings" )
			return _dialogsSettings.IsDerivedFromParent();
		if ( fieldName == "pingAbuseSettings" )
			return _pingAbuseSettings.IsDerivedFromParent();
		if ( fieldName == "blockSaturationColor" )
			return _blockSaturationColor.IsDerivedFromParent();
		if ( fieldName == "mapModeCustomDescriptions" )
			return _mapModeCustomDescriptions.IsDerivedFromParent();
		if ( fieldName == "loadingScreenStatuses" )
			return _loadingScreenStatuses.IsDerivedFromParent();
		if ( fieldName == "premiumVisualInfo" )
			return _premiumVisualInfo.IsDerivedFromParent();
		if ( fieldName == "locales" )
			return _locales.IsDerivedFromParent();
		if ( fieldName == "tips" )
			return _tips.IsDerivedFromParent();
		if ( fieldName == "reportTypes" )
			return _reportTypes.IsDerivedFromParent();
		if ( fieldName == "binds" )
			return _binds.IsDerivedFromParent();
		if ( fieldName == "countryFlags" )
			return _countryFlags.IsDerivedFromParent();
		if ( fieldName == "botFlags" )
			return _botFlags.IsDerivedFromParent();
		if ( fieldName == "customFlags" )
			return _customFlags.IsDerivedFromParent();
		if ( fieldName == "adminFlags" )
			return _adminFlags.IsDerivedFromParent();
		if ( fieldName == "guildShopTabs" )
			return _guildShopTabs.IsDerivedFromParent();
		if ( fieldName == "smartChat" )
			return _smartChat.IsDerivedFromParent();
		if ( fieldName == "smartChatAbuseSettings" )
			return _smartChatAbuseSettings.IsDerivedFromParent();
		if ( fieldName == "RecentPlayers" )
			return _RecentPlayers.IsDerivedFromParent();
		if ( fieldName == "currencies" )
			return _currencies.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[UseTypeName("DSTCN")]
public class DerivativeStatsContainer : DBResource
{
	private UndoRedoDBPtr<DerivativeStatsContainer> ___parent;
	[HideInOutliner]
	public new DBPtr<DerivativeStatsContainer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<ExecutableFloatString> _derivativeStats;

	[EnumArray(typeof(EDerivativeStat))]
	public libdb.IChangeableList<ExecutableFloatString> derivativeStats { get { return _derivativeStats; } set { _derivativeStats.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DerivativeStatsContainer>(owner);
		_derivativeStats = new UndoRedoAssignableList<ExecutableFloatString>( owner, typeof( EDerivativeStat ) );
		___parent.Changed += FireChangedEvent;
		_derivativeStats.Changed += FireChangedEvent;
	}

	public DerivativeStatsContainer()
	{
		Initialize( this );
	}
	private void AssignSelf( DerivativeStatsContainer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DerivativeStatsContainer" );
		derivativeStats = source.derivativeStats;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DerivativeStatsContainer source = _source as DerivativeStatsContainer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DerivativeStatsContainer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DerivativeStatsContainer newParent = rawParent == null ? null : rawParent.Get<DerivativeStatsContainer>();
		if ( newParent == null && _newParent is DerivativeStatsContainer )
			newParent = _newParent as DerivativeStatsContainer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_derivativeStats.SetParent( newParent == null ? null : newParent._derivativeStats );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_derivativeStats.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_derivativeStats.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "derivativeStats" )
			_derivativeStats.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "derivativeStats" )
			return _derivativeStats.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[IndexField("caption")]
public class Dialog : DBResource
{
	private UndoRedoDBPtr<Dialog> ___parent;
	[HideInOutliner]
	public new DBPtr<Dialog> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _caption;
	private UndoRedo<string> _id;
	private TextRef _title;
	private UndoRedoAssignableList<Phrase> _phrasesA;
	private UndoRedoAssignableList<Phrase> _phrasesB;

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	[Description( "Символьное имя для ссылок из скриптов (сессия). В замке поле не используется" )]
	public string id { get { return _id.Get(); } set { _id.Set( value ); } }

	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	public libdb.IChangeableList<Phrase> phrasesA { get { return _phrasesA; } set { _phrasesA.Assign( value ); } }

	public libdb.IChangeableList<Phrase> phrasesB { get { return _phrasesB; } set { _phrasesB.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Dialog>(owner);
		_caption = new UndoRedo<string>( owner, string.Empty );
		_id = new UndoRedo<string>( owner, string.Empty );
		_title = new TextRef( owner, new TextRef() );
		_phrasesA = new UndoRedoAssignableList<Phrase>( owner );
		_phrasesB = new UndoRedoAssignableList<Phrase>( owner );
		___parent.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_id.Changed += FireChangedEvent;
		_title.Changed += FireChangedEvent;
		_phrasesA.Changed += FireChangedEvent;
		_phrasesB.Changed += FireChangedEvent;
	}

	public Dialog()
	{
		Initialize( this );
	}
	private void AssignSelf( Dialog source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Dialog" );
		caption = source.caption;
		id = source.id;
		title = source.title;
		phrasesA = source.phrasesA;
		phrasesB = source.phrasesB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Dialog source = _source as Dialog;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Dialog" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Dialog newParent = rawParent == null ? null : rawParent.Get<Dialog>();
		if ( newParent == null && _newParent is Dialog )
			newParent = _newParent as Dialog;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_caption.SetParent( newParent == null ? null : newParent._caption );
		_id.SetParent( newParent == null ? null : newParent._id );
		_title.SetParent( newParent == null ? null : newParent._title );
		_phrasesA.SetParent( newParent == null ? null : newParent._phrasesA );
		_phrasesB.SetParent( newParent == null ? null : newParent._phrasesB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_caption.Reset();
		_id.Reset();
		_title.Reset();
		_phrasesA.Reset();
		_phrasesB.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& _id.IsDerivedFromParent()
			&& _title.IsDerivedFromParent()
			&& _phrasesA.IsDerivedFromParent()
			&& _phrasesB.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "id" )
			_id.Reset();
		else if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "phrasesA" )
			_phrasesA.Reset();
		else if ( fieldName == "phrasesB" )
			_phrasesB.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "id" )
			return _id.IsDerivedFromParent();
		if ( fieldName == "title" )
			return _title.IsDerivedFromParent();
		if ( fieldName == "phrasesA" )
			return _phrasesA.IsDerivedFromParent();
		if ( fieldName == "phrasesB" )
			return _phrasesB.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("DIALOGS")]
public class DialogsCollection : DBResource
{
	private UndoRedoDBPtr<DialogsCollection> ___parent;
	[HideInOutliner]
	public new DBPtr<DialogsCollection> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Dialog>> _dialogs;

	public libdb.IChangeableList<DBPtr<Dialog>> dialogs { get { return _dialogs; } set { _dialogs.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DialogsCollection>(owner);
		_dialogs = new UndoRedoAssignableList<DBPtr<Dialog>>( owner );
		___parent.Changed += FireChangedEvent;
		_dialogs.Changed += FireChangedEvent;
	}

	public DialogsCollection()
	{
		Initialize( this );
	}
	private void AssignSelf( DialogsCollection source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DialogsCollection" );
		dialogs = source.dialogs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DialogsCollection source = _source as DialogsCollection;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DialogsCollection" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DialogsCollection newParent = rawParent == null ? null : rawParent.Get<DialogsCollection>();
		if ( newParent == null && _newParent is DialogsCollection )
			newParent = _newParent as DialogsCollection;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_dialogs.SetParent( newParent == null ? null : newParent._dialogs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_dialogs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_dialogs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "dialogs" )
			_dialogs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "dialogs" )
			return _dialogs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class FactionScoringTable : DBResource
{
	private UndoRedoDBPtr<FactionScoringTable> ___parent;
	[HideInOutliner]
	public new DBPtr<FactionScoringTable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _loose;
	private UndoRedo<int> _win;
	private UndoRedo<float> _towerDestroyedBase;
	private UndoRedo<float> _towerDestroyedLevelMul;
	private UndoRedo<int> _bossKill;
	private UndoRedo<int> _topKills;
	private UndoRedo<int> _topAssists;
	private UndoRedo<int> _maxBossKillScore;

	public int loose { get { return _loose.Get(); } set { _loose.Set( value ); } }

	public int win { get { return _win.Get(); } set { _win.Set( value ); } }

	[Description( "Base score for tower destruction" )]
	public float towerDestroyedBase { get { return _towerDestroyedBase.Get(); } set { _towerDestroyedBase.Set( value ); } }

	[Description( "Tower level multiplier for scoring" )]
	public float towerDestroyedLevelMul { get { return _towerDestroyedLevelMul.Get(); } set { _towerDestroyedLevelMul.Set( value ); } }

	public int bossKill { get { return _bossKill.Get(); } set { _bossKill.Set( value ); } }

	public int topKills { get { return _topKills.Get(); } set { _topKills.Set( value ); } }

	public int topAssists { get { return _topAssists.Get(); } set { _topAssists.Set( value ); } }

	public int maxBossKillScore { get { return _maxBossKillScore.Get(); } set { _maxBossKillScore.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FactionScoringTable>(owner);
		_loose = new UndoRedo<int>( owner, 10 );
		_win = new UndoRedo<int>( owner, 30 );
		_towerDestroyedBase = new UndoRedo<float>( owner, 1.0f );
		_towerDestroyedLevelMul = new UndoRedo<float>( owner, 1.0f );
		_bossKill = new UndoRedo<int>( owner, 1 );
		_topKills = new UndoRedo<int>( owner, 5 );
		_topAssists = new UndoRedo<int>( owner, 5 );
		_maxBossKillScore = new UndoRedo<int>( owner, 5 );
		___parent.Changed += FireChangedEvent;
		_loose.Changed += FireChangedEvent;
		_win.Changed += FireChangedEvent;
		_towerDestroyedBase.Changed += FireChangedEvent;
		_towerDestroyedLevelMul.Changed += FireChangedEvent;
		_bossKill.Changed += FireChangedEvent;
		_topKills.Changed += FireChangedEvent;
		_topAssists.Changed += FireChangedEvent;
		_maxBossKillScore.Changed += FireChangedEvent;
	}

	public FactionScoringTable()
	{
		Initialize( this );
	}
	private void AssignSelf( FactionScoringTable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FactionScoringTable" );
		loose = source.loose;
		win = source.win;
		towerDestroyedBase = source.towerDestroyedBase;
		towerDestroyedLevelMul = source.towerDestroyedLevelMul;
		bossKill = source.bossKill;
		topKills = source.topKills;
		topAssists = source.topAssists;
		maxBossKillScore = source.maxBossKillScore;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FactionScoringTable source = _source as FactionScoringTable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FactionScoringTable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FactionScoringTable newParent = rawParent == null ? null : rawParent.Get<FactionScoringTable>();
		if ( newParent == null && _newParent is FactionScoringTable )
			newParent = _newParent as FactionScoringTable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_loose.SetParent( newParent == null ? null : newParent._loose );
		_win.SetParent( newParent == null ? null : newParent._win );
		_towerDestroyedBase.SetParent( newParent == null ? null : newParent._towerDestroyedBase );
		_towerDestroyedLevelMul.SetParent( newParent == null ? null : newParent._towerDestroyedLevelMul );
		_bossKill.SetParent( newParent == null ? null : newParent._bossKill );
		_topKills.SetParent( newParent == null ? null : newParent._topKills );
		_topAssists.SetParent( newParent == null ? null : newParent._topAssists );
		_maxBossKillScore.SetParent( newParent == null ? null : newParent._maxBossKillScore );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_loose.Reset();
		_win.Reset();
		_towerDestroyedBase.Reset();
		_towerDestroyedLevelMul.Reset();
		_bossKill.Reset();
		_topKills.Reset();
		_topAssists.Reset();
		_maxBossKillScore.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_loose.IsDerivedFromParent()
			&& _win.IsDerivedFromParent()
			&& _towerDestroyedBase.IsDerivedFromParent()
			&& _towerDestroyedLevelMul.IsDerivedFromParent()
			&& _bossKill.IsDerivedFromParent()
			&& _topKills.IsDerivedFromParent()
			&& _topAssists.IsDerivedFromParent()
			&& _maxBossKillScore.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "loose" )
			_loose.Reset();
		else if ( fieldName == "win" )
			_win.Reset();
		else if ( fieldName == "towerDestroyedBase" )
			_towerDestroyedBase.Reset();
		else if ( fieldName == "towerDestroyedLevelMul" )
			_towerDestroyedLevelMul.Reset();
		else if ( fieldName == "bossKill" )
			_bossKill.Reset();
		else if ( fieldName == "topKills" )
			_topKills.Reset();
		else if ( fieldName == "topAssists" )
			_topAssists.Reset();
		else if ( fieldName == "maxBossKillScore" )
			_maxBossKillScore.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "loose" )
			return _loose.IsDerivedFromParent();
		if ( fieldName == "win" )
			return _win.IsDerivedFromParent();
		if ( fieldName == "towerDestroyedBase" )
			return _towerDestroyedBase.IsDerivedFromParent();
		if ( fieldName == "towerDestroyedLevelMul" )
			return _towerDestroyedLevelMul.IsDerivedFromParent();
		if ( fieldName == "bossKill" )
			return _bossKill.IsDerivedFromParent();
		if ( fieldName == "topKills" )
			return _topKills.IsDerivedFromParent();
		if ( fieldName == "topAssists" )
			return _topAssists.IsDerivedFromParent();
		if ( fieldName == "maxBossKillScore" )
			return _maxBossKillScore.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Create", "NWorld::PFWorld")]
[NonTerminal]
[TypeId(0x8D7C7280)]
[UseTypeName("FAKE")]
public class FakeObj : DBResource
{
	private UndoRedoDBPtr<FakeObj> ___parent;
	[HideInOutliner]
	public new DBPtr<FakeObj> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FakeObj>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public FakeObj()
	{
		Initialize( this );
	}
	private void AssignSelf( FakeObj source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FakeObj" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FakeObj source = _source as FakeObj;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FakeObj" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FakeObj newParent = rawParent == null ? null : rawParent.Get<FakeObj>();
		if ( newParent == null && _newParent is FakeObj )
			newParent = _newParent as FakeObj;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class HeroScoringTable : DBResource
{
	private UndoRedoDBPtr<HeroScoringTable> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroScoringTable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _heroOfTheDay;
	private UndoRedo<int> _towerKill;
	private RestrictedScoring _heroKill;
	private RestrictedScoring _bossKill;
	private RestrictedScoring _goldMedals;
	private RestrictedScoring _silverMedals;
	private RestrictedScoring _buildingDestroy;
	private DiscreteScoring _flagRaise;
	private DiscreteScoring _flagDrop;

	public int heroOfTheDay { get { return _heroOfTheDay.Get(); } set { _heroOfTheDay.Set( value ); } }

	public int towerKill { get { return _towerKill.Get(); } set { _towerKill.Set( value ); } }

	public RestrictedScoring heroKill { get { return _heroKill; } set { _heroKill.Assign( value ); } }

	public RestrictedScoring bossKill { get { return _bossKill; } set { _bossKill.Assign( value ); } }

	public RestrictedScoring goldMedals { get { return _goldMedals; } set { _goldMedals.Assign( value ); } }

	public RestrictedScoring silverMedals { get { return _silverMedals; } set { _silverMedals.Assign( value ); } }

	public RestrictedScoring buildingDestroy { get { return _buildingDestroy; } set { _buildingDestroy.Assign( value ); } }

	public DiscreteScoring flagRaise { get { return _flagRaise; } set { _flagRaise.Assign( value ); } }

	public DiscreteScoring flagDrop { get { return _flagDrop; } set { _flagDrop.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroScoringTable>(owner);
		_heroOfTheDay = new UndoRedo<int>( owner, 5 );
		_towerKill = new UndoRedo<int>( owner, 2 );
		_heroKill = new RestrictedScoring( owner );
		_bossKill = new RestrictedScoring( owner );
		_goldMedals = new RestrictedScoring( owner );
		_silverMedals = new RestrictedScoring( owner );
		_buildingDestroy = new RestrictedScoring( owner );
		_flagRaise = new DiscreteScoring( owner );
		_flagDrop = new DiscreteScoring( owner );
		___parent.Changed += FireChangedEvent;
		_heroOfTheDay.Changed += FireChangedEvent;
		_towerKill.Changed += FireChangedEvent;
		_heroKill.Changed += FireChangedEvent;
		_bossKill.Changed += FireChangedEvent;
		_goldMedals.Changed += FireChangedEvent;
		_silverMedals.Changed += FireChangedEvent;
		_buildingDestroy.Changed += FireChangedEvent;
		_flagRaise.Changed += FireChangedEvent;
		_flagDrop.Changed += FireChangedEvent;
	}

	public HeroScoringTable()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroScoringTable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroScoringTable" );
		heroOfTheDay = source.heroOfTheDay;
		towerKill = source.towerKill;
		heroKill = source.heroKill;
		bossKill = source.bossKill;
		goldMedals = source.goldMedals;
		silverMedals = source.silverMedals;
		buildingDestroy = source.buildingDestroy;
		flagRaise = source.flagRaise;
		flagDrop = source.flagDrop;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroScoringTable source = _source as HeroScoringTable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroScoringTable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroScoringTable newParent = rawParent == null ? null : rawParent.Get<HeroScoringTable>();
		if ( newParent == null && _newParent is HeroScoringTable )
			newParent = _newParent as HeroScoringTable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_heroOfTheDay.SetParent( newParent == null ? null : newParent._heroOfTheDay );
		_towerKill.SetParent( newParent == null ? null : newParent._towerKill );
		_heroKill.SetParent( newParent == null ? null : newParent._heroKill );
		_bossKill.SetParent( newParent == null ? null : newParent._bossKill );
		_goldMedals.SetParent( newParent == null ? null : newParent._goldMedals );
		_silverMedals.SetParent( newParent == null ? null : newParent._silverMedals );
		_buildingDestroy.SetParent( newParent == null ? null : newParent._buildingDestroy );
		_flagRaise.SetParent( newParent == null ? null : newParent._flagRaise );
		_flagDrop.SetParent( newParent == null ? null : newParent._flagDrop );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_heroOfTheDay.Reset();
		_towerKill.Reset();
		_heroKill.Reset();
		_bossKill.Reset();
		_goldMedals.Reset();
		_silverMedals.Reset();
		_buildingDestroy.Reset();
		_flagRaise.Reset();
		_flagDrop.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_heroOfTheDay.IsDerivedFromParent()
			&& _towerKill.IsDerivedFromParent()
			&& _heroKill.IsDerivedFromParent()
			&& _bossKill.IsDerivedFromParent()
			&& _goldMedals.IsDerivedFromParent()
			&& _silverMedals.IsDerivedFromParent()
			&& _buildingDestroy.IsDerivedFromParent()
			&& _flagRaise.IsDerivedFromParent()
			&& _flagDrop.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "heroOfTheDay" )
			_heroOfTheDay.Reset();
		else if ( fieldName == "towerKill" )
			_towerKill.Reset();
		else if ( fieldName == "heroKill" )
			_heroKill.Reset();
		else if ( fieldName == "bossKill" )
			_bossKill.Reset();
		else if ( fieldName == "goldMedals" )
			_goldMedals.Reset();
		else if ( fieldName == "silverMedals" )
			_silverMedals.Reset();
		else if ( fieldName == "buildingDestroy" )
			_buildingDestroy.Reset();
		else if ( fieldName == "flagRaise" )
			_flagRaise.Reset();
		else if ( fieldName == "flagDrop" )
			_flagDrop.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "heroOfTheDay" )
			return _heroOfTheDay.IsDerivedFromParent();
		if ( fieldName == "towerKill" )
			return _towerKill.IsDerivedFromParent();
		if ( fieldName == "heroKill" )
			return _heroKill.IsDerivedFromParent();
		if ( fieldName == "bossKill" )
			return _bossKill.IsDerivedFromParent();
		if ( fieldName == "goldMedals" )
			return _goldMedals.IsDerivedFromParent();
		if ( fieldName == "silverMedals" )
			return _silverMedals.IsDerivedFromParent();
		if ( fieldName == "buildingDestroy" )
			return _buildingDestroy.IsDerivedFromParent();
		if ( fieldName == "flagRaise" )
			return _flagRaise.IsDerivedFromParent();
		if ( fieldName == "flagDrop" )
			return _flagDrop.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("HINTS")]
public class HintsCollection : DBResource
{
	private UndoRedoDBPtr<HintsCollection> ___parent;
	[HideInOutliner]
	public new DBPtr<HintsCollection> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<Hint> _hints;

	public libdb.IChangeableList<Hint> hints { get { return _hints; } set { _hints.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HintsCollection>(owner);
		_hints = new UndoRedoAssignableList<Hint>( owner );
		___parent.Changed += FireChangedEvent;
		_hints.Changed += FireChangedEvent;
	}

	public HintsCollection()
	{
		Initialize( this );
	}
	private void AssignSelf( HintsCollection source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HintsCollection" );
		hints = source.hints;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HintsCollection source = _source as HintsCollection;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HintsCollection" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HintsCollection newParent = rawParent == null ? null : rawParent.Get<HintsCollection>();
		if ( newParent == null && _newParent is HintsCollection )
			newParent = _newParent as HintsCollection;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_hints.SetParent( newParent == null ? null : newParent._hints );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_hints.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_hints.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "hints" )
			_hints.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "hints" )
			return _hints.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("MMAPIMG")]
public class MinimapImages : DBResource
{
	private UndoRedoDBPtr<MinimapImages> ___parent;
	[HideInOutliner]
	public new DBPtr<MinimapImages> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TextureBase> _firstMap;
	private UndoRedoDBPtr<TextureBase> _secondMap;
	private UndoRedoDBPtr<TextureBase> _neutralMap;
	private Vec2 _centerOffset;
	private UndoRedo<float> _scaleFactor;

	[Description( "First (A) faction minimap image" )]
	public DBPtr<TextureBase> firstMap { get { return _firstMap.Get(); } set { _firstMap.Set( value ); } }

	[Description( "Second (B) faction minimap image" )]
	public DBPtr<TextureBase> secondMap { get { return _secondMap.Get(); } set { _secondMap.Set( value ); } }

	[Description( "Neutral minimap image" )]
	public DBPtr<TextureBase> neutralMap { get { return _neutralMap.Get(); } set { _neutralMap.Set( value ); } }

	[Description( "Center offset of the minimap (in meters)" )]
	public Vec2 centerOffset { get { return _centerOffset; } set { _centerOffset.Assign( value ); } }

	[Description( "Scale factor of the minimap (1.0 = no scale)" )]
	public float scaleFactor { get { return _scaleFactor.Get(); } set { _scaleFactor.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MinimapImages>(owner);
		_firstMap = new UndoRedoDBPtr<TextureBase>( owner );
		_secondMap = new UndoRedoDBPtr<TextureBase>( owner );
		_neutralMap = new UndoRedoDBPtr<TextureBase>( owner );
		_centerOffset = new Vec2( owner );
		_scaleFactor = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_firstMap.Changed += FireChangedEvent;
		_secondMap.Changed += FireChangedEvent;
		_neutralMap.Changed += FireChangedEvent;
		_centerOffset.Changed += FireChangedEvent;
		_scaleFactor.Changed += FireChangedEvent;
	}

	public MinimapImages()
	{
		Initialize( this );
	}
	private void AssignSelf( MinimapImages source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MinimapImages" );
		firstMap = source.firstMap;
		secondMap = source.secondMap;
		neutralMap = source.neutralMap;
		centerOffset = source.centerOffset;
		scaleFactor = source.scaleFactor;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MinimapImages source = _source as MinimapImages;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MinimapImages" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MinimapImages newParent = rawParent == null ? null : rawParent.Get<MinimapImages>();
		if ( newParent == null && _newParent is MinimapImages )
			newParent = _newParent as MinimapImages;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_firstMap.SetParent( newParent == null ? null : newParent._firstMap );
		_secondMap.SetParent( newParent == null ? null : newParent._secondMap );
		_neutralMap.SetParent( newParent == null ? null : newParent._neutralMap );
		_centerOffset.SetParent( newParent == null ? null : newParent._centerOffset );
		_scaleFactor.SetParent( newParent == null ? null : newParent._scaleFactor );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_firstMap.Reset();
		_secondMap.Reset();
		_neutralMap.Reset();
		_centerOffset.Reset();
		_scaleFactor.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_firstMap.IsDerivedFromParent()
			&& _secondMap.IsDerivedFromParent()
			&& _neutralMap.IsDerivedFromParent()
			&& _centerOffset.IsDerivedFromParent()
			&& _scaleFactor.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "firstMap" )
			_firstMap.Reset();
		else if ( fieldName == "secondMap" )
			_secondMap.Reset();
		else if ( fieldName == "neutralMap" )
			_neutralMap.Reset();
		else if ( fieldName == "centerOffset" )
			_centerOffset.Reset();
		else if ( fieldName == "scaleFactor" )
			_scaleFactor.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "firstMap" )
			return _firstMap.IsDerivedFromParent();
		if ( fieldName == "secondMap" )
			return _secondMap.IsDerivedFromParent();
		if ( fieldName == "neutralMap" )
			return _neutralMap.IsDerivedFromParent();
		if ( fieldName == "centerOffset" )
			return _centerOffset.IsDerivedFromParent();
		if ( fieldName == "scaleFactor" )
			return _scaleFactor.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("TRTI")]
public class PFTerrainTypeInfo : TerrainTypeInfo
{
	private UndoRedoDBPtr<PFTerrainTypeInfo> ___parent;
	[HideInOutliner]
	public new DBPtr<PFTerrainTypeInfo> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ETerrainType> _eType;

	public ETerrainType eType { get { return _eType.Get(); } set { _eType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PFTerrainTypeInfo>(owner);
		_eType = new UndoRedo<ETerrainType>( owner, ETerrainType.Plains );
		___parent.Changed += FireChangedEvent;
		_eType.Changed += FireChangedEvent;
	}

	public PFTerrainTypeInfo()
	{
		Initialize( this );
	}
	private void AssignSelf( PFTerrainTypeInfo source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PFTerrainTypeInfo" );
		eType = source.eType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PFTerrainTypeInfo source = _source as PFTerrainTypeInfo;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PFTerrainTypeInfo" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PFTerrainTypeInfo newParent = rawParent == null ? null : rawParent.Get<PFTerrainTypeInfo>();
		if ( newParent == null && _newParent is PFTerrainTypeInfo )
			newParent = _newParent as PFTerrainTypeInfo;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_eType.SetParent( newParent == null ? null : newParent._eType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_eType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_eType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "eType" )
			_eType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "eType" )
			return _eType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class PFUIGameLogicRoot : DBResource
{
	private UndoRedoDBPtr<PFUIGameLogicRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<PFUIGameLogicRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<DBStatisticData> _statisticData;

	public DBPtr<DBStatisticData> statisticData { get { return _statisticData.Get(); } set { _statisticData.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PFUIGameLogicRoot>(owner);
		_statisticData = new UndoRedoDBPtr<DBStatisticData>( owner );
		___parent.Changed += FireChangedEvent;
		_statisticData.Changed += FireChangedEvent;
	}

	public PFUIGameLogicRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( PFUIGameLogicRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PFUIGameLogicRoot" );
		statisticData = source.statisticData;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PFUIGameLogicRoot source = _source as PFUIGameLogicRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PFUIGameLogicRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PFUIGameLogicRoot newParent = rawParent == null ? null : rawParent.Get<PFUIGameLogicRoot>();
		if ( newParent == null && _newParent is PFUIGameLogicRoot )
			newParent = _newParent as PFUIGameLogicRoot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_statisticData.SetParent( newParent == null ? null : newParent._statisticData );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_statisticData.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_statisticData.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "statisticData" )
			_statisticData.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "statisticData" )
			return _statisticData.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xA06693C0)]
[UseTypeName("SCTB")]
public class ScoringTable : DBResource
{
	private UndoRedoDBPtr<ScoringTable> ___parent;
	[HideInOutliner]
	public new DBPtr<ScoringTable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<FactionScoringTable> _faction;
	private UndoRedoDBPtr<HeroScoringTable> _hero;
	private UndoRedoAssignableList<DBPtr<AchievBase>> _achievementsList;
	private UndoRedoAssignableList<HeroTitle> _heroTitles;
	private UndoRedoAssignableList<ScoreDescription> _scoreDescriptions;
	private UndoRedoAssignableList<DBPtr<Ability>> _teleporterAbilities;

	public DBPtr<FactionScoringTable> faction { get { return _faction.Get(); } set { _faction.Set( value ); } }

	public DBPtr<HeroScoringTable> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	[Description( "All game achievements" )]
	public libdb.IChangeableList<DBPtr<AchievBase>> achievementsList { get { return _achievementsList; } set { _achievementsList.Assign( value ); } }

	[Description( "Hero titles" )]
	[EnumArray(typeof(EHeroTitle))]
	public libdb.IChangeableList<HeroTitle> heroTitles { get { return _heroTitles; } set { _heroTitles.Assign( value ); } }

	[Description( "List score descriptions" )]
	[EnumArray(typeof(EScoreType))]
	public libdb.IChangeableList<ScoreDescription> scoreDescriptions { get { return _scoreDescriptions; } set { _scoreDescriptions.Assign( value ); } }

	[Description( "Abilities whose teleports are counted by Teleporter title" )]
	public libdb.IChangeableList<DBPtr<Ability>> teleporterAbilities { get { return _teleporterAbilities; } set { _teleporterAbilities.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ScoringTable>(owner);
		_faction = new UndoRedoDBPtr<FactionScoringTable>( owner );
		_hero = new UndoRedoDBPtr<HeroScoringTable>( owner );
		_achievementsList = new UndoRedoAssignableList<DBPtr<AchievBase>>( owner );
		_heroTitles = new UndoRedoAssignableList<HeroTitle>( owner, typeof( EHeroTitle ) );
		_scoreDescriptions = new UndoRedoAssignableList<ScoreDescription>( owner, typeof( EScoreType ) );
		_teleporterAbilities = new UndoRedoAssignableList<DBPtr<Ability>>( owner );
		___parent.Changed += FireChangedEvent;
		_faction.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
		_achievementsList.Changed += FireChangedEvent;
		_heroTitles.Changed += FireChangedEvent;
		_scoreDescriptions.Changed += FireChangedEvent;
		_teleporterAbilities.Changed += FireChangedEvent;
	}

	public ScoringTable()
	{
		Initialize( this );
	}
	private void AssignSelf( ScoringTable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ScoringTable" );
		faction = source.faction;
		hero = source.hero;
		achievementsList = source.achievementsList;
		heroTitles = source.heroTitles;
		scoreDescriptions = source.scoreDescriptions;
		teleporterAbilities = source.teleporterAbilities;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ScoringTable source = _source as ScoringTable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScoringTable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ScoringTable newParent = rawParent == null ? null : rawParent.Get<ScoringTable>();
		if ( newParent == null && _newParent is ScoringTable )
			newParent = _newParent as ScoringTable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_faction.SetParent( newParent == null ? null : newParent._faction );
		_hero.SetParent( newParent == null ? null : newParent._hero );
		_achievementsList.SetParent( newParent == null ? null : newParent._achievementsList );
		_heroTitles.SetParent( newParent == null ? null : newParent._heroTitles );
		_scoreDescriptions.SetParent( newParent == null ? null : newParent._scoreDescriptions );
		_teleporterAbilities.SetParent( newParent == null ? null : newParent._teleporterAbilities );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_faction.Reset();
		_hero.Reset();
		_achievementsList.Reset();
		_heroTitles.Reset();
		_scoreDescriptions.Reset();
		_teleporterAbilities.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_faction.IsDerivedFromParent()
			&& _hero.IsDerivedFromParent()
			&& _achievementsList.IsDerivedFromParent()
			&& _heroTitles.IsDerivedFromParent()
			&& _scoreDescriptions.IsDerivedFromParent()
			&& _teleporterAbilities.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "faction" )
			_faction.Reset();
		else if ( fieldName == "hero" )
			_hero.Reset();
		else if ( fieldName == "achievementsList" )
			_achievementsList.Reset();
		else if ( fieldName == "heroTitles" )
			_heroTitles.Reset();
		else if ( fieldName == "scoreDescriptions" )
			_scoreDescriptions.Reset();
		else if ( fieldName == "teleporterAbilities" )
			_teleporterAbilities.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "faction" )
			return _faction.IsDerivedFromParent();
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		if ( fieldName == "achievementsList" )
			return _achievementsList.IsDerivedFromParent();
		if ( fieldName == "heroTitles" )
			return _heroTitles.IsDerivedFromParent();
		if ( fieldName == "scoreDescriptions" )
			return _scoreDescriptions.IsDerivedFromParent();
		if ( fieldName == "teleporterAbilities" )
			return _teleporterAbilities.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("QUESTS")]
public class SessionQuestsCollection : DBResource
{
	private UndoRedoDBPtr<SessionQuestsCollection> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionQuestsCollection> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<SessionQuest> _quests;

	public libdb.IChangeableList<SessionQuest> quests { get { return _quests; } set { _quests.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionQuestsCollection>(owner);
		_quests = new UndoRedoAssignableList<SessionQuest>( owner );
		___parent.Changed += FireChangedEvent;
		_quests.Changed += FireChangedEvent;
	}

	public SessionQuestsCollection()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionQuestsCollection source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionQuestsCollection" );
		quests = source.quests;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionQuestsCollection source = _source as SessionQuestsCollection;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionQuestsCollection" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionQuestsCollection newParent = rawParent == null ? null : rawParent.Get<SessionQuestsCollection>();
		if ( newParent == null && _newParent is SessionQuestsCollection )
			newParent = _newParent as SessionQuestsCollection;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_quests.SetParent( newParent == null ? null : newParent._quests );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_quests.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_quests.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "quests" )
			_quests.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "quests" )
			return _quests.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[UseTypeName("STBUD")]
public class StatsBudgetContainer : DBResource
{
	private UndoRedoDBPtr<StatsBudgetContainer> ___parent;
	[HideInOutliner]
	public new DBPtr<StatsBudgetContainer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<StatBudget> _stats;

	public libdb.IChangeableList<StatBudget> stats { get { return _stats; } set { _stats.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StatsBudgetContainer>(owner);
		_stats = new UndoRedoAssignableList<StatBudget>( owner );
		___parent.Changed += FireChangedEvent;
		_stats.Changed += FireChangedEvent;
	}

	public StatsBudgetContainer()
	{
		Initialize( this );
	}
	private void AssignSelf( StatsBudgetContainer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StatsBudgetContainer" );
		stats = source.stats;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StatsBudgetContainer source = _source as StatsBudgetContainer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatsBudgetContainer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StatsBudgetContainer newParent = rawParent == null ? null : rawParent.Get<StatsBudgetContainer>();
		if ( newParent == null && _newParent is StatsBudgetContainer )
			newParent = _newParent as StatsBudgetContainer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_stats.SetParent( newParent == null ? null : newParent._stats );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_stats.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_stats.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "stats" )
			_stats.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "stats" )
			return _stats.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[TypeId(0x0F626440)]
[UseTypeName("STCN")]
public class StatsContainer : DBResource
{
	private UndoRedoDBPtr<StatsContainer> ___parent;
	[HideInOutliner]
	public new DBPtr<StatsContainer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<UnitStat> _stats;

	public libdb.IChangeableList<UnitStat> stats { get { return _stats; } set { _stats.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StatsContainer>(owner);
		_stats = new UndoRedoAssignableList<UnitStat>( owner );
		___parent.Changed += FireChangedEvent;
		_stats.Changed += FireChangedEvent;
	}

	public StatsContainer()
	{
		Initialize( this );
	}
	private void AssignSelf( StatsContainer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StatsContainer" );
		stats = source.stats;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StatsContainer source = _source as StatsContainer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatsContainer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StatsContainer newParent = rawParent == null ? null : rawParent.Get<StatsContainer>();
		if ( newParent == null && _newParent is StatsContainer )
			newParent = _newParent as StatsContainer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_stats.SetParent( newParent == null ? null : newParent._stats );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_stats.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_stats.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "stats" )
			_stats.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "stats" )
			return _stats.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class StatsEnhancersContainer : DBResource
{
	private UndoRedoDBPtr<StatsEnhancersContainer> ___parent;
	[HideInOutliner]
	public new DBPtr<StatsEnhancersContainer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<StatEnhancer> _statsEnhancers;

	public libdb.IChangeableList<StatEnhancer> statsEnhancers { get { return _statsEnhancers; } set { _statsEnhancers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StatsEnhancersContainer>(owner);
		_statsEnhancers = new UndoRedoAssignableList<StatEnhancer>( owner );
		___parent.Changed += FireChangedEvent;
		_statsEnhancers.Changed += FireChangedEvent;
	}

	public StatsEnhancersContainer()
	{
		Initialize( this );
	}
	private void AssignSelf( StatsEnhancersContainer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StatsEnhancersContainer" );
		statsEnhancers = source.statsEnhancers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StatsEnhancersContainer source = _source as StatsEnhancersContainer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatsEnhancersContainer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StatsEnhancersContainer newParent = rawParent == null ? null : rawParent.Get<StatsEnhancersContainer>();
		if ( newParent == null && _newParent is StatsEnhancersContainer )
			newParent = _newParent as StatsEnhancersContainer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_statsEnhancers.SetParent( newParent == null ? null : newParent._statsEnhancers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_statsEnhancers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_statsEnhancers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "statsEnhancers" )
			_statsEnhancers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "statsEnhancers" )
			return _statsEnhancers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("EventId")]
[TypeId(0x4D7262C0)]
[UseTypeName("UIEV")]
public class UIEvent : DBResource
{
	private UndoRedoDBPtr<UIEvent> ___parent;
	[HideInOutliner]
	public new DBPtr<UIEvent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ERecipients> _signRecipients;
	private UndoRedoAssignableList<DBPtr<UISign>> _UISigns;

	[Description( "Specify the recipients of all reaction/sign." )]
	public ERecipients signRecipients { get { return _signRecipients.Get(); } set { _signRecipients.Set( value ); } }

	public libdb.IChangeableList<DBPtr<UISign>> UISigns { get { return _UISigns; } set { _UISigns.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIEvent>(owner);
		_signRecipients = new UndoRedo<ERecipients>( owner, ERecipients.ALL_PLAYERS );
		_UISigns = new UndoRedoAssignableList<DBPtr<UISign>>( owner );
		___parent.Changed += FireChangedEvent;
		_signRecipients.Changed += FireChangedEvent;
		_UISigns.Changed += FireChangedEvent;
	}

	public UIEvent()
	{
		Initialize( this );
	}
	private void AssignSelf( UIEvent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIEvent" );
		signRecipients = source.signRecipients;
		UISigns = source.UISigns;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIEvent source = _source as UIEvent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIEvent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIEvent newParent = rawParent == null ? null : rawParent.Get<UIEvent>();
		if ( newParent == null && _newParent is UIEvent )
			newParent = _newParent as UIEvent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_signRecipients.SetParent( newParent == null ? null : newParent._signRecipients );
		_UISigns.SetParent( newParent == null ? null : newParent._UISigns );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_signRecipients.Reset();
		_UISigns.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_signRecipients.IsDerivedFromParent()
			&& _UISigns.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "signRecipients" )
			_signRecipients.Reset();
		else if ( fieldName == "UISigns" )
			_UISigns.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "signRecipients" )
			return _signRecipients.IsDerivedFromParent();
		if ( fieldName == "UISigns" )
			return _UISigns.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(4)]
[TypeId(0x4D729C41)]
[UseTypeName("UIEVCOLL")]
public class UIEventsCustom : DBResource
{
	private UndoRedoDBPtr<UIEventsCustom> ___parent;
	[HideInOutliner]
	public new DBPtr<UIEventsCustom> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<UIEvent> _evMiss;
	private UndoRedoDBPtr<UIEvent> _evGetNafta;
	private UndoRedoDBPtr<UIEvent> _evHeroKill;
	private UndoRedoDBPtr<UIEvent> _evHeroKillByAI;
	private UndoRedoDBPtr<UIEvent> _evHeroKillByNeutralAI;
	private UndoRedoDBPtr<UIEvent> _evTowerDestroy;
	private UndoRedoDBPtr<UIEvent> _evTowerDestroyByAI;
	private UndoRedoDBPtr<UIEvent> _evTowerDestroyByNeutralAI;
	private UndoRedoDBPtr<UIEvent> _evItemTransfer;
	private UndoRedoDBPtr<UIEvent> _evItemGain;
	private UndoRedoDBPtr<UIEvent> _evHeroCheat;
	private UndoRedoDBPtr<UIEvent> _evHeroReconnected;
	private UndoRedoDBPtr<UIEvent> _evHeroDisconnected;
	private UndoRedoDBPtr<UIEvent> _evHeroDisconnectedAFK;
	private UndoRedoDBPtr<UIEvent> _evHeroFriendDisconnected;
	private UndoRedoDBPtr<UIEvent> _evHeroFriendDisconnectedAFK;
	private UndoRedoDBPtr<UIEvent> _evHeroLeft;
	private UndoRedoDBPtr<UIEvent> _evHeroFriendLeft;
	private UndoRedoDBPtr<UIEvent> _evHeroFriendReconnected;
	private UndoRedoDBPtr<UIEvent> _evHeroAFK;
	private UndoRedoDBPtr<UIEvent> _evHeroAFKEnded;
	private UndoRedoDBPtr<UIEvent> _evBarrackDestroyed;
	private UndoRedoDBPtr<UIEvent> _evFriendBarrackDestroyed;
	private UndoRedoDBPtr<UIEvent> _evVictory;
	private UndoRedoDBPtr<UIEvent> _evDefeat;
	private UndoRedoDBPtr<UIEvent> _evSpectatorJoin;
	private UndoRedoDBPtr<UIEvent> _evAdminMuted;
	private UndoRedoDBPtr<UIEvent> _evStartAiForPlayer;
	private UndoRedoDBPtr<UIEvent> _evLeaverMuted;
	private UndoRedoDBPtr<UIEvent> _evLeaverPartyMuted;
	private UndoRedoDBPtr<UIEvent> _evAdminMutedNotify;

	[Description( "Miss UI Event" )]
	public DBPtr<UIEvent> evMiss { get { return _evMiss.Get(); } set { _evMiss.Set( value ); } }

	[Description( "Get nafta UI Event" )]
	public DBPtr<UIEvent> evGetNafta { get { return _evGetNafta.Get(); } set { _evGetNafta.Set( value ); } }

	[Description( "Hero kill" )]
	public DBPtr<UIEvent> evHeroKill { get { return _evHeroKill.Get(); } set { _evHeroKill.Set( value ); } }

	[Description( "Hero kill by AI" )]
	public DBPtr<UIEvent> evHeroKillByAI { get { return _evHeroKillByAI.Get(); } set { _evHeroKillByAI.Set( value ); } }

	[Description( "Hero kill by Neutral AI" )]
	public DBPtr<UIEvent> evHeroKillByNeutralAI { get { return _evHeroKillByNeutralAI.Get(); } set { _evHeroKillByNeutralAI.Set( value ); } }

	[Description( "Tower destroy" )]
	public DBPtr<UIEvent> evTowerDestroy { get { return _evTowerDestroy.Get(); } set { _evTowerDestroy.Set( value ); } }

	[Description( "Tower destroy by AI" )]
	public DBPtr<UIEvent> evTowerDestroyByAI { get { return _evTowerDestroyByAI.Get(); } set { _evTowerDestroyByAI.Set( value ); } }

	[Description( "Tower destroy by Neutral AI" )]
	public DBPtr<UIEvent> evTowerDestroyByNeutralAI { get { return _evTowerDestroyByNeutralAI.Get(); } set { _evTowerDestroyByNeutralAI.Set( value ); } }

	[Description( "Item transfer (Reward from Easel minigame)" )]
	public DBPtr<UIEvent> evItemTransfer { get { return _evItemTransfer.Get(); } set { _evItemTransfer.Set( value ); } }

	[Description( "Item transfer to self (Reward from Easel minigame)" )]
	public DBPtr<UIEvent> evItemGain { get { return _evItemGain.Get(); } set { _evItemGain.Set( value ); } }

	[Description( "Hero cheat" )]
	public DBPtr<UIEvent> evHeroCheat { get { return _evHeroCheat.Get(); } set { _evHeroCheat.Set( value ); } }

	[Description( "Hero enemy reconnected" )]
	public DBPtr<UIEvent> evHeroReconnected { get { return _evHeroReconnected.Get(); } set { _evHeroReconnected.Set( value ); } }

	[Description( "Hero enemy disconnected" )]
	public DBPtr<UIEvent> evHeroDisconnected { get { return _evHeroDisconnected.Get(); } set { _evHeroDisconnected.Set( value ); } }

	[Description( "Hero enemy disconnected due to long AFK time" )]
	public DBPtr<UIEvent> evHeroDisconnectedAFK { get { return _evHeroDisconnectedAFK.Get(); } set { _evHeroDisconnectedAFK.Set( value ); } }

	[Description( "Hero friend disconnected" )]
	public DBPtr<UIEvent> evHeroFriendDisconnected { get { return _evHeroFriendDisconnected.Get(); } set { _evHeroFriendDisconnected.Set( value ); } }

	[Description( "Hero friend disconnected due to long AFK time" )]
	public DBPtr<UIEvent> evHeroFriendDisconnectedAFK { get { return _evHeroFriendDisconnectedAFK.Get(); } set { _evHeroFriendDisconnectedAFK.Set( value ); } }

	[Description( "Hero enemy left" )]
	public DBPtr<UIEvent> evHeroLeft { get { return _evHeroLeft.Get(); } set { _evHeroLeft.Set( value ); } }

	[Description( "Hero friend left" )]
	public DBPtr<UIEvent> evHeroFriendLeft { get { return _evHeroFriendLeft.Get(); } set { _evHeroFriendLeft.Set( value ); } }

	[Description( "Hero friend reconnected" )]
	public DBPtr<UIEvent> evHeroFriendReconnected { get { return _evHeroFriendReconnected.Get(); } set { _evHeroFriendReconnected.Set( value ); } }

	[Description( "Hero afk" )]
	public DBPtr<UIEvent> evHeroAFK { get { return _evHeroAFK.Get(); } set { _evHeroAFK.Set( value ); } }

	[Description( "Hero afk ended" )]
	public DBPtr<UIEvent> evHeroAFKEnded { get { return _evHeroAFKEnded.Get(); } set { _evHeroAFKEnded.Set( value ); } }

	[Description( "Enemy's Barrack destroyed" )]
	public DBPtr<UIEvent> evBarrackDestroyed { get { return _evBarrackDestroyed.Get(); } set { _evBarrackDestroyed.Set( value ); } }

	[Description( "Friend's Barrack destroyed" )]
	public DBPtr<UIEvent> evFriendBarrackDestroyed { get { return _evFriendBarrackDestroyed.Get(); } set { _evFriendBarrackDestroyed.Set( value ); } }

	[Description( "Victory" )]
	public DBPtr<UIEvent> evVictory { get { return _evVictory.Get(); } set { _evVictory.Set( value ); } }

	[Description( "Defeat" )]
	public DBPtr<UIEvent> evDefeat { get { return _evDefeat.Get(); } set { _evDefeat.Set( value ); } }

	[Description( "Spectator join to battle" )]
	public DBPtr<UIEvent> evSpectatorJoin { get { return _evSpectatorJoin.Get(); } set { _evSpectatorJoin.Set( value ); } }

	[Description( "Player admin muted" )]
	public DBPtr<UIEvent> evAdminMuted { get { return _evAdminMuted.Get(); } set { _evAdminMuted.Set( value ); } }

	[Description( "Start AI for disconnected player" )]
	public DBPtr<UIEvent> evStartAiForPlayer { get { return _evStartAiForPlayer.Get(); } set { _evStartAiForPlayer.Set( value ); } }

	[Description( "Нельзя писать в чат сессии, т.к. игрок - дезертир" )]
	public DBPtr<UIEvent> evLeaverMuted { get { return _evLeaverMuted.Get(); } set { _evLeaverMuted.Set( value ); } }

	[Description( "Нельзя писать в чат сессии, т.к. игрок состоит в группе с дезертиром" )]
	public DBPtr<UIEvent> evLeaverPartyMuted { get { return _evLeaverPartyMuted.Get(); } set { _evLeaverPartyMuted.Set( value ); } }

	[Description( "Игрок не может писать в чат - уведомление для всех на экране загрузки" )]
	public DBPtr<UIEvent> evAdminMutedNotify { get { return _evAdminMutedNotify.Get(); } set { _evAdminMutedNotify.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIEventsCustom>(owner);
		_evMiss = new UndoRedoDBPtr<UIEvent>( owner );
		_evGetNafta = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroKill = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroKillByAI = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroKillByNeutralAI = new UndoRedoDBPtr<UIEvent>( owner );
		_evTowerDestroy = new UndoRedoDBPtr<UIEvent>( owner );
		_evTowerDestroyByAI = new UndoRedoDBPtr<UIEvent>( owner );
		_evTowerDestroyByNeutralAI = new UndoRedoDBPtr<UIEvent>( owner );
		_evItemTransfer = new UndoRedoDBPtr<UIEvent>( owner );
		_evItemGain = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroCheat = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroReconnected = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroDisconnected = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroDisconnectedAFK = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroFriendDisconnected = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroFriendDisconnectedAFK = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroLeft = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroFriendLeft = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroFriendReconnected = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroAFK = new UndoRedoDBPtr<UIEvent>( owner );
		_evHeroAFKEnded = new UndoRedoDBPtr<UIEvent>( owner );
		_evBarrackDestroyed = new UndoRedoDBPtr<UIEvent>( owner );
		_evFriendBarrackDestroyed = new UndoRedoDBPtr<UIEvent>( owner );
		_evVictory = new UndoRedoDBPtr<UIEvent>( owner );
		_evDefeat = new UndoRedoDBPtr<UIEvent>( owner );
		_evSpectatorJoin = new UndoRedoDBPtr<UIEvent>( owner );
		_evAdminMuted = new UndoRedoDBPtr<UIEvent>( owner );
		_evStartAiForPlayer = new UndoRedoDBPtr<UIEvent>( owner );
		_evLeaverMuted = new UndoRedoDBPtr<UIEvent>( owner );
		_evLeaverPartyMuted = new UndoRedoDBPtr<UIEvent>( owner );
		_evAdminMutedNotify = new UndoRedoDBPtr<UIEvent>( owner );
		___parent.Changed += FireChangedEvent;
		_evMiss.Changed += FireChangedEvent;
		_evGetNafta.Changed += FireChangedEvent;
		_evHeroKill.Changed += FireChangedEvent;
		_evHeroKillByAI.Changed += FireChangedEvent;
		_evHeroKillByNeutralAI.Changed += FireChangedEvent;
		_evTowerDestroy.Changed += FireChangedEvent;
		_evTowerDestroyByAI.Changed += FireChangedEvent;
		_evTowerDestroyByNeutralAI.Changed += FireChangedEvent;
		_evItemTransfer.Changed += FireChangedEvent;
		_evItemGain.Changed += FireChangedEvent;
		_evHeroCheat.Changed += FireChangedEvent;
		_evHeroReconnected.Changed += FireChangedEvent;
		_evHeroDisconnected.Changed += FireChangedEvent;
		_evHeroDisconnectedAFK.Changed += FireChangedEvent;
		_evHeroFriendDisconnected.Changed += FireChangedEvent;
		_evHeroFriendDisconnectedAFK.Changed += FireChangedEvent;
		_evHeroLeft.Changed += FireChangedEvent;
		_evHeroFriendLeft.Changed += FireChangedEvent;
		_evHeroFriendReconnected.Changed += FireChangedEvent;
		_evHeroAFK.Changed += FireChangedEvent;
		_evHeroAFKEnded.Changed += FireChangedEvent;
		_evBarrackDestroyed.Changed += FireChangedEvent;
		_evFriendBarrackDestroyed.Changed += FireChangedEvent;
		_evVictory.Changed += FireChangedEvent;
		_evDefeat.Changed += FireChangedEvent;
		_evSpectatorJoin.Changed += FireChangedEvent;
		_evAdminMuted.Changed += FireChangedEvent;
		_evStartAiForPlayer.Changed += FireChangedEvent;
		_evLeaverMuted.Changed += FireChangedEvent;
		_evLeaverPartyMuted.Changed += FireChangedEvent;
		_evAdminMutedNotify.Changed += FireChangedEvent;
	}

	public UIEventsCustom()
	{
		Initialize( this );
	}
	private void AssignSelf( UIEventsCustom source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIEventsCustom" );
		evMiss = source.evMiss;
		evGetNafta = source.evGetNafta;
		evHeroKill = source.evHeroKill;
		evHeroKillByAI = source.evHeroKillByAI;
		evHeroKillByNeutralAI = source.evHeroKillByNeutralAI;
		evTowerDestroy = source.evTowerDestroy;
		evTowerDestroyByAI = source.evTowerDestroyByAI;
		evTowerDestroyByNeutralAI = source.evTowerDestroyByNeutralAI;
		evItemTransfer = source.evItemTransfer;
		evItemGain = source.evItemGain;
		evHeroCheat = source.evHeroCheat;
		evHeroReconnected = source.evHeroReconnected;
		evHeroDisconnected = source.evHeroDisconnected;
		evHeroDisconnectedAFK = source.evHeroDisconnectedAFK;
		evHeroFriendDisconnected = source.evHeroFriendDisconnected;
		evHeroFriendDisconnectedAFK = source.evHeroFriendDisconnectedAFK;
		evHeroLeft = source.evHeroLeft;
		evHeroFriendLeft = source.evHeroFriendLeft;
		evHeroFriendReconnected = source.evHeroFriendReconnected;
		evHeroAFK = source.evHeroAFK;
		evHeroAFKEnded = source.evHeroAFKEnded;
		evBarrackDestroyed = source.evBarrackDestroyed;
		evFriendBarrackDestroyed = source.evFriendBarrackDestroyed;
		evVictory = source.evVictory;
		evDefeat = source.evDefeat;
		evSpectatorJoin = source.evSpectatorJoin;
		evAdminMuted = source.evAdminMuted;
		evStartAiForPlayer = source.evStartAiForPlayer;
		evLeaverMuted = source.evLeaverMuted;
		evLeaverPartyMuted = source.evLeaverPartyMuted;
		evAdminMutedNotify = source.evAdminMutedNotify;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIEventsCustom source = _source as UIEventsCustom;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIEventsCustom" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIEventsCustom newParent = rawParent == null ? null : rawParent.Get<UIEventsCustom>();
		if ( newParent == null && _newParent is UIEventsCustom )
			newParent = _newParent as UIEventsCustom;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_evMiss.SetParent( newParent == null ? null : newParent._evMiss );
		_evGetNafta.SetParent( newParent == null ? null : newParent._evGetNafta );
		_evHeroKill.SetParent( newParent == null ? null : newParent._evHeroKill );
		_evHeroKillByAI.SetParent( newParent == null ? null : newParent._evHeroKillByAI );
		_evHeroKillByNeutralAI.SetParent( newParent == null ? null : newParent._evHeroKillByNeutralAI );
		_evTowerDestroy.SetParent( newParent == null ? null : newParent._evTowerDestroy );
		_evTowerDestroyByAI.SetParent( newParent == null ? null : newParent._evTowerDestroyByAI );
		_evTowerDestroyByNeutralAI.SetParent( newParent == null ? null : newParent._evTowerDestroyByNeutralAI );
		_evItemTransfer.SetParent( newParent == null ? null : newParent._evItemTransfer );
		_evItemGain.SetParent( newParent == null ? null : newParent._evItemGain );
		_evHeroCheat.SetParent( newParent == null ? null : newParent._evHeroCheat );
		_evHeroReconnected.SetParent( newParent == null ? null : newParent._evHeroReconnected );
		_evHeroDisconnected.SetParent( newParent == null ? null : newParent._evHeroDisconnected );
		_evHeroDisconnectedAFK.SetParent( newParent == null ? null : newParent._evHeroDisconnectedAFK );
		_evHeroFriendDisconnected.SetParent( newParent == null ? null : newParent._evHeroFriendDisconnected );
		_evHeroFriendDisconnectedAFK.SetParent( newParent == null ? null : newParent._evHeroFriendDisconnectedAFK );
		_evHeroLeft.SetParent( newParent == null ? null : newParent._evHeroLeft );
		_evHeroFriendLeft.SetParent( newParent == null ? null : newParent._evHeroFriendLeft );
		_evHeroFriendReconnected.SetParent( newParent == null ? null : newParent._evHeroFriendReconnected );
		_evHeroAFK.SetParent( newParent == null ? null : newParent._evHeroAFK );
		_evHeroAFKEnded.SetParent( newParent == null ? null : newParent._evHeroAFKEnded );
		_evBarrackDestroyed.SetParent( newParent == null ? null : newParent._evBarrackDestroyed );
		_evFriendBarrackDestroyed.SetParent( newParent == null ? null : newParent._evFriendBarrackDestroyed );
		_evVictory.SetParent( newParent == null ? null : newParent._evVictory );
		_evDefeat.SetParent( newParent == null ? null : newParent._evDefeat );
		_evSpectatorJoin.SetParent( newParent == null ? null : newParent._evSpectatorJoin );
		_evAdminMuted.SetParent( newParent == null ? null : newParent._evAdminMuted );
		_evStartAiForPlayer.SetParent( newParent == null ? null : newParent._evStartAiForPlayer );
		_evLeaverMuted.SetParent( newParent == null ? null : newParent._evLeaverMuted );
		_evLeaverPartyMuted.SetParent( newParent == null ? null : newParent._evLeaverPartyMuted );
		_evAdminMutedNotify.SetParent( newParent == null ? null : newParent._evAdminMutedNotify );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_evMiss.Reset();
		_evGetNafta.Reset();
		_evHeroKill.Reset();
		_evHeroKillByAI.Reset();
		_evHeroKillByNeutralAI.Reset();
		_evTowerDestroy.Reset();
		_evTowerDestroyByAI.Reset();
		_evTowerDestroyByNeutralAI.Reset();
		_evItemTransfer.Reset();
		_evItemGain.Reset();
		_evHeroCheat.Reset();
		_evHeroReconnected.Reset();
		_evHeroDisconnected.Reset();
		_evHeroDisconnectedAFK.Reset();
		_evHeroFriendDisconnected.Reset();
		_evHeroFriendDisconnectedAFK.Reset();
		_evHeroLeft.Reset();
		_evHeroFriendLeft.Reset();
		_evHeroFriendReconnected.Reset();
		_evHeroAFK.Reset();
		_evHeroAFKEnded.Reset();
		_evBarrackDestroyed.Reset();
		_evFriendBarrackDestroyed.Reset();
		_evVictory.Reset();
		_evDefeat.Reset();
		_evSpectatorJoin.Reset();
		_evAdminMuted.Reset();
		_evStartAiForPlayer.Reset();
		_evLeaverMuted.Reset();
		_evLeaverPartyMuted.Reset();
		_evAdminMutedNotify.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_evMiss.IsDerivedFromParent()
			&& _evGetNafta.IsDerivedFromParent()
			&& _evHeroKill.IsDerivedFromParent()
			&& _evHeroKillByAI.IsDerivedFromParent()
			&& _evHeroKillByNeutralAI.IsDerivedFromParent()
			&& _evTowerDestroy.IsDerivedFromParent()
			&& _evTowerDestroyByAI.IsDerivedFromParent()
			&& _evTowerDestroyByNeutralAI.IsDerivedFromParent()
			&& _evItemTransfer.IsDerivedFromParent()
			&& _evItemGain.IsDerivedFromParent()
			&& _evHeroCheat.IsDerivedFromParent()
			&& _evHeroReconnected.IsDerivedFromParent()
			&& _evHeroDisconnected.IsDerivedFromParent()
			&& _evHeroDisconnectedAFK.IsDerivedFromParent()
			&& _evHeroFriendDisconnected.IsDerivedFromParent()
			&& _evHeroFriendDisconnectedAFK.IsDerivedFromParent()
			&& _evHeroLeft.IsDerivedFromParent()
			&& _evHeroFriendLeft.IsDerivedFromParent()
			&& _evHeroFriendReconnected.IsDerivedFromParent()
			&& _evHeroAFK.IsDerivedFromParent()
			&& _evHeroAFKEnded.IsDerivedFromParent()
			&& _evBarrackDestroyed.IsDerivedFromParent()
			&& _evFriendBarrackDestroyed.IsDerivedFromParent()
			&& _evVictory.IsDerivedFromParent()
			&& _evDefeat.IsDerivedFromParent()
			&& _evSpectatorJoin.IsDerivedFromParent()
			&& _evAdminMuted.IsDerivedFromParent()
			&& _evStartAiForPlayer.IsDerivedFromParent()
			&& _evLeaverMuted.IsDerivedFromParent()
			&& _evLeaverPartyMuted.IsDerivedFromParent()
			&& _evAdminMutedNotify.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "evMiss" )
			_evMiss.Reset();
		else if ( fieldName == "evGetNafta" )
			_evGetNafta.Reset();
		else if ( fieldName == "evHeroKill" )
			_evHeroKill.Reset();
		else if ( fieldName == "evHeroKillByAI" )
			_evHeroKillByAI.Reset();
		else if ( fieldName == "evHeroKillByNeutralAI" )
			_evHeroKillByNeutralAI.Reset();
		else if ( fieldName == "evTowerDestroy" )
			_evTowerDestroy.Reset();
		else if ( fieldName == "evTowerDestroyByAI" )
			_evTowerDestroyByAI.Reset();
		else if ( fieldName == "evTowerDestroyByNeutralAI" )
			_evTowerDestroyByNeutralAI.Reset();
		else if ( fieldName == "evItemTransfer" )
			_evItemTransfer.Reset();
		else if ( fieldName == "evItemGain" )
			_evItemGain.Reset();
		else if ( fieldName == "evHeroCheat" )
			_evHeroCheat.Reset();
		else if ( fieldName == "evHeroReconnected" )
			_evHeroReconnected.Reset();
		else if ( fieldName == "evHeroDisconnected" )
			_evHeroDisconnected.Reset();
		else if ( fieldName == "evHeroDisconnectedAFK" )
			_evHeroDisconnectedAFK.Reset();
		else if ( fieldName == "evHeroFriendDisconnected" )
			_evHeroFriendDisconnected.Reset();
		else if ( fieldName == "evHeroFriendDisconnectedAFK" )
			_evHeroFriendDisconnectedAFK.Reset();
		else if ( fieldName == "evHeroLeft" )
			_evHeroLeft.Reset();
		else if ( fieldName == "evHeroFriendLeft" )
			_evHeroFriendLeft.Reset();
		else if ( fieldName == "evHeroFriendReconnected" )
			_evHeroFriendReconnected.Reset();
		else if ( fieldName == "evHeroAFK" )
			_evHeroAFK.Reset();
		else if ( fieldName == "evHeroAFKEnded" )
			_evHeroAFKEnded.Reset();
		else if ( fieldName == "evBarrackDestroyed" )
			_evBarrackDestroyed.Reset();
		else if ( fieldName == "evFriendBarrackDestroyed" )
			_evFriendBarrackDestroyed.Reset();
		else if ( fieldName == "evVictory" )
			_evVictory.Reset();
		else if ( fieldName == "evDefeat" )
			_evDefeat.Reset();
		else if ( fieldName == "evSpectatorJoin" )
			_evSpectatorJoin.Reset();
		else if ( fieldName == "evAdminMuted" )
			_evAdminMuted.Reset();
		else if ( fieldName == "evStartAiForPlayer" )
			_evStartAiForPlayer.Reset();
		else if ( fieldName == "evLeaverMuted" )
			_evLeaverMuted.Reset();
		else if ( fieldName == "evLeaverPartyMuted" )
			_evLeaverPartyMuted.Reset();
		else if ( fieldName == "evAdminMutedNotify" )
			_evAdminMutedNotify.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "evMiss" )
			return _evMiss.IsDerivedFromParent();
		if ( fieldName == "evGetNafta" )
			return _evGetNafta.IsDerivedFromParent();
		if ( fieldName == "evHeroKill" )
			return _evHeroKill.IsDerivedFromParent();
		if ( fieldName == "evHeroKillByAI" )
			return _evHeroKillByAI.IsDerivedFromParent();
		if ( fieldName == "evHeroKillByNeutralAI" )
			return _evHeroKillByNeutralAI.IsDerivedFromParent();
		if ( fieldName == "evTowerDestroy" )
			return _evTowerDestroy.IsDerivedFromParent();
		if ( fieldName == "evTowerDestroyByAI" )
			return _evTowerDestroyByAI.IsDerivedFromParent();
		if ( fieldName == "evTowerDestroyByNeutralAI" )
			return _evTowerDestroyByNeutralAI.IsDerivedFromParent();
		if ( fieldName == "evItemTransfer" )
			return _evItemTransfer.IsDerivedFromParent();
		if ( fieldName == "evItemGain" )
			return _evItemGain.IsDerivedFromParent();
		if ( fieldName == "evHeroCheat" )
			return _evHeroCheat.IsDerivedFromParent();
		if ( fieldName == "evHeroReconnected" )
			return _evHeroReconnected.IsDerivedFromParent();
		if ( fieldName == "evHeroDisconnected" )
			return _evHeroDisconnected.IsDerivedFromParent();
		if ( fieldName == "evHeroDisconnectedAFK" )
			return _evHeroDisconnectedAFK.IsDerivedFromParent();
		if ( fieldName == "evHeroFriendDisconnected" )
			return _evHeroFriendDisconnected.IsDerivedFromParent();
		if ( fieldName == "evHeroFriendDisconnectedAFK" )
			return _evHeroFriendDisconnectedAFK.IsDerivedFromParent();
		if ( fieldName == "evHeroLeft" )
			return _evHeroLeft.IsDerivedFromParent();
		if ( fieldName == "evHeroFriendLeft" )
			return _evHeroFriendLeft.IsDerivedFromParent();
		if ( fieldName == "evHeroFriendReconnected" )
			return _evHeroFriendReconnected.IsDerivedFromParent();
		if ( fieldName == "evHeroAFK" )
			return _evHeroAFK.IsDerivedFromParent();
		if ( fieldName == "evHeroAFKEnded" )
			return _evHeroAFKEnded.IsDerivedFromParent();
		if ( fieldName == "evBarrackDestroyed" )
			return _evBarrackDestroyed.IsDerivedFromParent();
		if ( fieldName == "evFriendBarrackDestroyed" )
			return _evFriendBarrackDestroyed.IsDerivedFromParent();
		if ( fieldName == "evVictory" )
			return _evVictory.IsDerivedFromParent();
		if ( fieldName == "evDefeat" )
			return _evDefeat.IsDerivedFromParent();
		if ( fieldName == "evSpectatorJoin" )
			return _evSpectatorJoin.IsDerivedFromParent();
		if ( fieldName == "evAdminMuted" )
			return _evAdminMuted.IsDerivedFromParent();
		if ( fieldName == "evStartAiForPlayer" )
			return _evStartAiForPlayer.IsDerivedFromParent();
		if ( fieldName == "evLeaverMuted" )
			return _evLeaverMuted.IsDerivedFromParent();
		if ( fieldName == "evLeaverPartyMuted" )
			return _evLeaverPartyMuted.IsDerivedFromParent();
		if ( fieldName == "evAdminMutedNotify" )
			return _evAdminMutedNotify.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Create", "NGameX::PFUISign")]
[NonTerminal]
[TypeId(0xF6264430)]
public class UISign : DBResource
{
	private UndoRedoDBPtr<UISign> ___parent;
	[HideInOutliner]
	public new DBPtr<UISign> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ERecipients> _signRecipients;

	[Description( "Specify the recipients of this event reaction/sign. All messages (sounds) will be sent to the specified recipients only!!!" )]
	public ERecipients signRecipients { get { return _signRecipients.Get(); } set { _signRecipients.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UISign>(owner);
		_signRecipients = new UndoRedo<ERecipients>( owner, ERecipients.USE_FROM_PARENT );
		___parent.Changed += FireChangedEvent;
		_signRecipients.Changed += FireChangedEvent;
	}

	public UISign()
	{
		Initialize( this );
	}
	private void AssignSelf( UISign source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UISign" );
		signRecipients = source.signRecipients;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UISign source = _source as UISign;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UISign" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UISign newParent = rawParent == null ? null : rawParent.Get<UISign>();
		if ( newParent == null && _newParent is UISign )
			newParent = _newParent as UISign;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_signRecipients.SetParent( newParent == null ? null : newParent._signRecipients );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_signRecipients.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_signRecipients.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "signRecipients" )
			_signRecipients.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "signRecipients" )
			return _signRecipients.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NGameX::PFUISignAnnouncement", "PFUIEvent.h")]
public class UISignAnnouncement : UISign
{
	private UndoRedoDBPtr<UISignAnnouncement> ___parent;
	[HideInOutliner]
	public new DBPtr<UISignAnnouncement> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EAnnouncementType> _announcementType;
	private TextRef _txt;
	private UndoRedoDBPtr<Texture> _imageBurn;
	private UndoRedoDBPtr<Texture> _imageFreeze;
	private UndoRedo<int> _priority;
	private UndoRedo<float> _lifeTime;
	private DBFMODEventDesc _announcementSound;
	private UndoRedo<float> _announcementSoundCooldown;
	private UndoRedo<bool> _UseInTutorial;

	[Description( "Announcement type" )]
	public EAnnouncementType announcementType { get { return _announcementType.Get(); } set { _announcementType.Set( value ); } }

	[Description( "Announcement text" )]
	public TextRef txt { get { return _txt; } set { _txt.Assign( value ); } }

	[Description( "image for elfs" )]
	public DBPtr<Texture> imageBurn { get { return _imageBurn.Get(); } set { _imageBurn.Set( value ); } }

	[Description( "image for humans" )]
	public DBPtr<Texture> imageFreeze { get { return _imageFreeze.Get(); } set { _imageFreeze.Set( value ); } }

	[Description( "greater is more important" )]
	public int priority { get { return _priority.Get(); } set { _priority.Set( value ); } }

	[Description( "life time for announcement" )]
	public float lifeTime { get { return _lifeTime.Get(); } set { _lifeTime.Set( value ); } }

	[Description( "Announcement Sound like DoubleKill etc" )]
	public DBFMODEventDesc announcementSound { get { return _announcementSound; } set { _announcementSound.Assign( value ); } }

	[Description( "Cooldown (seconds) for announcement sound" )]
	public float announcementSoundCooldown { get { return _announcementSoundCooldown.Get(); } set { _announcementSoundCooldown.Set( value ); } }

	[Description( "Whether to use or not in the tutorial" )]
	public bool UseInTutorial { get { return _UseInTutorial.Get(); } set { _UseInTutorial.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UISignAnnouncement>(owner);
		_announcementType = new UndoRedo<EAnnouncementType>( owner, EAnnouncementType.PlayerKilled );
		_txt = new TextRef( owner, new TextRef() );
		_imageBurn = new UndoRedoDBPtr<Texture>( owner );
		_imageFreeze = new UndoRedoDBPtr<Texture>( owner );
		_priority = new UndoRedo<int>( owner, 0 );
		_lifeTime = new UndoRedo<float>( owner, 3.0f );
		_announcementSound = new DBFMODEventDesc( owner );
		_announcementSoundCooldown = new UndoRedo<float>( owner, 0.0f );
		_UseInTutorial = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_announcementType.Changed += FireChangedEvent;
		_txt.Changed += FireChangedEvent;
		_imageBurn.Changed += FireChangedEvent;
		_imageFreeze.Changed += FireChangedEvent;
		_priority.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		_announcementSound.Changed += FireChangedEvent;
		_announcementSoundCooldown.Changed += FireChangedEvent;
		_UseInTutorial.Changed += FireChangedEvent;
	}

	public UISignAnnouncement()
	{
		Initialize( this );
	}
	private void AssignSelf( UISignAnnouncement source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UISignAnnouncement" );
		announcementType = source.announcementType;
		txt = source.txt;
		imageBurn = source.imageBurn;
		imageFreeze = source.imageFreeze;
		priority = source.priority;
		lifeTime = source.lifeTime;
		announcementSound = source.announcementSound;
		announcementSoundCooldown = source.announcementSoundCooldown;
		UseInTutorial = source.UseInTutorial;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UISignAnnouncement source = _source as UISignAnnouncement;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UISignAnnouncement" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UISignAnnouncement newParent = rawParent == null ? null : rawParent.Get<UISignAnnouncement>();
		if ( newParent == null && _newParent is UISignAnnouncement )
			newParent = _newParent as UISignAnnouncement;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_announcementType.SetParent( newParent == null ? null : newParent._announcementType );
		_txt.SetParent( newParent == null ? null : newParent._txt );
		_imageBurn.SetParent( newParent == null ? null : newParent._imageBurn );
		_imageFreeze.SetParent( newParent == null ? null : newParent._imageFreeze );
		_priority.SetParent( newParent == null ? null : newParent._priority );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_announcementSound.SetParent( newParent == null ? null : newParent._announcementSound );
		_announcementSoundCooldown.SetParent( newParent == null ? null : newParent._announcementSoundCooldown );
		_UseInTutorial.SetParent( newParent == null ? null : newParent._UseInTutorial );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_announcementType.Reset();
		_txt.Reset();
		_imageBurn.Reset();
		_imageFreeze.Reset();
		_priority.Reset();
		_lifeTime.Reset();
		_announcementSound.Reset();
		_announcementSoundCooldown.Reset();
		_UseInTutorial.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_announcementType.IsDerivedFromParent()
			&& _txt.IsDerivedFromParent()
			&& _imageBurn.IsDerivedFromParent()
			&& _imageFreeze.IsDerivedFromParent()
			&& _priority.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			&& _announcementSound.IsDerivedFromParent()
			&& _announcementSoundCooldown.IsDerivedFromParent()
			&& _UseInTutorial.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "announcementType" )
			_announcementType.Reset();
		else if ( fieldName == "txt" )
			_txt.Reset();
		else if ( fieldName == "imageBurn" )
			_imageBurn.Reset();
		else if ( fieldName == "imageFreeze" )
			_imageFreeze.Reset();
		else if ( fieldName == "priority" )
			_priority.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "announcementSound" )
			_announcementSound.Reset();
		else if ( fieldName == "announcementSoundCooldown" )
			_announcementSoundCooldown.Reset();
		else if ( fieldName == "UseInTutorial" )
			_UseInTutorial.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "announcementType" )
			return _announcementType.IsDerivedFromParent();
		if ( fieldName == "txt" )
			return _txt.IsDerivedFromParent();
		if ( fieldName == "imageBurn" )
			return _imageBurn.IsDerivedFromParent();
		if ( fieldName == "imageFreeze" )
			return _imageFreeze.IsDerivedFromParent();
		if ( fieldName == "priority" )
			return _priority.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "announcementSound" )
			return _announcementSound.IsDerivedFromParent();
		if ( fieldName == "announcementSoundCooldown" )
			return _announcementSoundCooldown.IsDerivedFromParent();
		if ( fieldName == "UseInTutorial" )
			return _UseInTutorial.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NGameX::PFUISignFlyOffText", "PFUIEvent.h")]
[TypeId(0xF6264434)]
public class UISignFlyOffText : UISign
{
	private UndoRedoDBPtr<UISignFlyOffText> ___parent;
	[HideInOutliner]
	public new DBPtr<UISignFlyOffText> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private FlyOffText _text;

	[Description( "Fly-off text" )]
	public FlyOffText text { get { return _text; } set { _text.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UISignFlyOffText>(owner);
		_text = new FlyOffText( owner );
		___parent.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
	}

	public UISignFlyOffText()
	{
		Initialize( this );
	}
	private void AssignSelf( UISignFlyOffText source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UISignFlyOffText" );
		text = source.text;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UISignFlyOffText source = _source as UISignFlyOffText;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UISignFlyOffText" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UISignFlyOffText newParent = rawParent == null ? null : rawParent.Get<UISignFlyOffText>();
		if ( newParent == null && _newParent is UISignFlyOffText )
			newParent = _newParent as UISignFlyOffText;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_text.SetParent( newParent == null ? null : newParent._text );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_text.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_text.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "text" )
			_text.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NGameX::PFUISignMessageToChat", "PFUIEvent.h")]
[TypeId(0xF6264431)]
public class UISignMessageToChat : UISign
{
	private UndoRedoDBPtr<UISignMessageToChat> ___parent;
	[HideInOutliner]
	public new DBPtr<UISignMessageToChat> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TextRef> _messages;
	private UndoRedo<EChatChannel> _channel;

	[Description( "Sign message. This message will be send to any UI output." )]
	[EnumArray(typeof(EMessage))]
	public libdb.IChangeableList<TextRef> messages { get { return _messages; } set { _messages.Assign( value ); } }

	public EChatChannel channel { get { return _channel.Get(); } set { _channel.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UISignMessageToChat>(owner);
		_messages = new UndoRedoAssignableList<TextRef>( owner, typeof( EMessage ) );
		_channel = new UndoRedo<EChatChannel>( owner, EChatChannel.Achievments );
		___parent.Changed += FireChangedEvent;
		_messages.Changed += FireChangedEvent;
		_channel.Changed += FireChangedEvent;
	}

	public UISignMessageToChat()
	{
		Initialize( this );
	}
	private void AssignSelf( UISignMessageToChat source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UISignMessageToChat" );
		messages = source.messages;
		channel = source.channel;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UISignMessageToChat source = _source as UISignMessageToChat;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UISignMessageToChat" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UISignMessageToChat newParent = rawParent == null ? null : rawParent.Get<UISignMessageToChat>();
		if ( newParent == null && _newParent is UISignMessageToChat )
			newParent = _newParent as UISignMessageToChat;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_messages.SetParent( newParent == null ? null : newParent._messages );
		_channel.SetParent( newParent == null ? null : newParent._channel );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_messages.Reset();
		_channel.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_messages.IsDerivedFromParent()
			&& _channel.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "messages" )
			_messages.Reset();
		else if ( fieldName == "channel" )
			_channel.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "messages" )
			return _messages.IsDerivedFromParent();
		if ( fieldName == "channel" )
			return _channel.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NGameX::PFUISignMessageToStatusLine", "PFUIEvent.h")]
[TypeId(0xF6264433)]
public class UISignMessageToStatusLine : UISign
{
	private UndoRedoDBPtr<UISignMessageToStatusLine> ___parent;
	[HideInOutliner]
	public new DBPtr<UISignMessageToStatusLine> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TextRef> _messages;

	[Description( "Sign message. This message will be send to any UI output." )]
	[EnumArray(typeof(EMessage))]
	public libdb.IChangeableList<TextRef> messages { get { return _messages; } set { _messages.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UISignMessageToStatusLine>(owner);
		_messages = new UndoRedoAssignableList<TextRef>( owner, typeof( EMessage ) );
		___parent.Changed += FireChangedEvent;
		_messages.Changed += FireChangedEvent;
	}

	public UISignMessageToStatusLine()
	{
		Initialize( this );
	}
	private void AssignSelf( UISignMessageToStatusLine source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UISignMessageToStatusLine" );
		messages = source.messages;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UISignMessageToStatusLine source = _source as UISignMessageToStatusLine;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UISignMessageToStatusLine" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UISignMessageToStatusLine newParent = rawParent == null ? null : rawParent.Get<UISignMessageToStatusLine>();
		if ( newParent == null && _newParent is UISignMessageToStatusLine )
			newParent = _newParent as UISignMessageToStatusLine;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_messages.SetParent( newParent == null ? null : newParent._messages );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_messages.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_messages.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "messages" )
			_messages.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "messages" )
			return _messages.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NGameX::PFUISignPlaySound", "PFUIEvent.h")]
[TypeId(0xF6264432)]
public class UISignPlaySound : UISign
{
	private UndoRedoDBPtr<UISignPlaySound> ___parent;
	[HideInOutliner]
	public new DBPtr<UISignPlaySound> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private DBFMODEventDesc _soundDesc;

	[Description( "Sign sound. This sound will be played when event happened." )]
	public DBFMODEventDesc soundDesc { get { return _soundDesc; } set { _soundDesc.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UISignPlaySound>(owner);
		_soundDesc = new DBFMODEventDesc( owner );
		___parent.Changed += FireChangedEvent;
		_soundDesc.Changed += FireChangedEvent;
	}

	public UISignPlaySound()
	{
		Initialize( this );
	}
	private void AssignSelf( UISignPlaySound source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UISignPlaySound" );
		soundDesc = source.soundDesc;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UISignPlaySound source = _source as UISignPlaySound;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UISignPlaySound" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UISignPlaySound newParent = rawParent == null ? null : rawParent.Get<UISignPlaySound>();
		if ( newParent == null && _newParent is UISignPlaySound )
			newParent = _newParent as UISignPlaySound;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_soundDesc.SetParent( newParent == null ? null : newParent._soundDesc );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_soundDesc.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_soundDesc.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "soundDesc" )
			_soundDesc.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "soundDesc" )
			return _soundDesc.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("UITI")]
public class UITeamInfoParams : DBResource
{
	private UndoRedoDBPtr<UITeamInfoParams> ___parent;
	[HideInOutliner]
	public new DBPtr<UITeamInfoParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TeamInfTooltipSettings _tooltipSettings;

	[Category( "Team info tooltip" )]
	public TeamInfTooltipSettings tooltipSettings { get { return _tooltipSettings; } set { _tooltipSettings.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UITeamInfoParams>(owner);
		_tooltipSettings = new TeamInfTooltipSettings( owner );
		___parent.Changed += FireChangedEvent;
		_tooltipSettings.Changed += FireChangedEvent;
	}

	public UITeamInfoParams()
	{
		Initialize( this );
	}
	private void AssignSelf( UITeamInfoParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UITeamInfoParams" );
		tooltipSettings = source.tooltipSettings;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UITeamInfoParams source = _source as UITeamInfoParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UITeamInfoParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UITeamInfoParams newParent = rawParent == null ? null : rawParent.Get<UITeamInfoParams>();
		if ( newParent == null && _newParent is UITeamInfoParams )
			newParent = _newParent as UITeamInfoParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tooltipSettings.SetParent( newParent == null ? null : newParent._tooltipSettings );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tooltipSettings.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tooltipSettings.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tooltipSettings" )
			_tooltipSettings.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tooltipSettings" )
			return _tooltipSettings.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("CAMS")]
public class WebTowerCameraSettings : DBResource
{
	private UndoRedoDBPtr<WebTowerCameraSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<WebTowerCameraSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _linearSpeed;
	private UndoRedo<float> _initialPitch;
	private UndoRedo<float> _yawSpeed;
	private UndoRedo<float> _heightOffset;
	private UndoRedo<float> _minRod;
	private UndoRedo<float> _maxRod;

	[Description( "Linear speed" )]
	public float linearSpeed { get { return _linearSpeed.Get(); } set { _linearSpeed.Set( value ); } }

	[Description( "Initial pitch" )]
	public float initialPitch { get { return _initialPitch.Get(); } set { _initialPitch.Set( value ); } }

	[Description( "Yaw speed" )]
	public float yawSpeed { get { return _yawSpeed.Get(); } set { _yawSpeed.Set( value ); } }

	[Description( "Height offset" )]
	public float heightOffset { get { return _heightOffset.Get(); } set { _heightOffset.Set( value ); } }

	[Description( "Min rod" )]
	public float minRod { get { return _minRod.Get(); } set { _minRod.Set( value ); } }

	[Description( "Max rod" )]
	public float maxRod { get { return _maxRod.Get(); } set { _maxRod.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WebTowerCameraSettings>(owner);
		_linearSpeed = new UndoRedo<float>( owner, 4.0f );
		_initialPitch = new UndoRedo<float>( owner, -0.4f );
		_yawSpeed = new UndoRedo<float>( owner, 1.0f );
		_heightOffset = new UndoRedo<float>( owner, 0.0f );
		_minRod = new UndoRedo<float>( owner, 1.0f );
		_maxRod = new UndoRedo<float>( owner, 15.0f );
		___parent.Changed += FireChangedEvent;
		_linearSpeed.Changed += FireChangedEvent;
		_initialPitch.Changed += FireChangedEvent;
		_yawSpeed.Changed += FireChangedEvent;
		_heightOffset.Changed += FireChangedEvent;
		_minRod.Changed += FireChangedEvent;
		_maxRod.Changed += FireChangedEvent;
	}

	public WebTowerCameraSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( WebTowerCameraSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WebTowerCameraSettings" );
		linearSpeed = source.linearSpeed;
		initialPitch = source.initialPitch;
		yawSpeed = source.yawSpeed;
		heightOffset = source.heightOffset;
		minRod = source.minRod;
		maxRod = source.maxRod;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WebTowerCameraSettings source = _source as WebTowerCameraSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WebTowerCameraSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WebTowerCameraSettings newParent = rawParent == null ? null : rawParent.Get<WebTowerCameraSettings>();
		if ( newParent == null && _newParent is WebTowerCameraSettings )
			newParent = _newParent as WebTowerCameraSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_linearSpeed.SetParent( newParent == null ? null : newParent._linearSpeed );
		_initialPitch.SetParent( newParent == null ? null : newParent._initialPitch );
		_yawSpeed.SetParent( newParent == null ? null : newParent._yawSpeed );
		_heightOffset.SetParent( newParent == null ? null : newParent._heightOffset );
		_minRod.SetParent( newParent == null ? null : newParent._minRod );
		_maxRod.SetParent( newParent == null ? null : newParent._maxRod );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_linearSpeed.Reset();
		_initialPitch.Reset();
		_yawSpeed.Reset();
		_heightOffset.Reset();
		_minRod.Reset();
		_maxRod.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_linearSpeed.IsDerivedFromParent()
			&& _initialPitch.IsDerivedFromParent()
			&& _yawSpeed.IsDerivedFromParent()
			&& _heightOffset.IsDerivedFromParent()
			&& _minRod.IsDerivedFromParent()
			&& _maxRod.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "linearSpeed" )
			_linearSpeed.Reset();
		else if ( fieldName == "initialPitch" )
			_initialPitch.Reset();
		else if ( fieldName == "yawSpeed" )
			_yawSpeed.Reset();
		else if ( fieldName == "heightOffset" )
			_heightOffset.Reset();
		else if ( fieldName == "minRod" )
			_minRod.Reset();
		else if ( fieldName == "maxRod" )
			_maxRod.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "linearSpeed" )
			return _linearSpeed.IsDerivedFromParent();
		if ( fieldName == "initialPitch" )
			return _initialPitch.IsDerivedFromParent();
		if ( fieldName == "yawSpeed" )
			return _yawSpeed.IsDerivedFromParent();
		if ( fieldName == "heightOffset" )
			return _heightOffset.IsDerivedFromParent();
		if ( fieldName == "minRod" )
			return _minRod.IsDerivedFromParent();
		if ( fieldName == "maxRod" )
			return _maxRod.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
