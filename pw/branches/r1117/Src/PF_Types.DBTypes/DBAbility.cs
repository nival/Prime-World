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
public enum EAbility
{
	ID_Stats = 0,
	ID_1 = 1,
	ID_2 = 2,
	ID_3 = 3,
	ID_4 = 4,
};

public enum EAbilityAOEVisual
{
	None = 0,
	Disk = 1,
	Cone = 2,
	Corridor = 3,
	CorridorMax = 4,
	UnattachedSector = 5,
	Wall = 6,
	AttachedSector = 7,
};

public enum EAbilityCostMode
{
	Energy = 0,
	Life = 1,
	Any = 2,
	Custom = 3,
};

[Flags]
public enum EAbilityFlags
{
	FocusOnTarget = 1,
	Momentary = 2,
	ApplyToDead = 4,
	MirroredByClone = 8,
	StayInvisible = 16,
	ChannelingCreate = 32,
	CanUseOutOfRange = 64,
	DontOpenWarFog = 128,
	InstaCast = 256,
	Moving = 512,
	UseAttackTarget = 1024,
	WaitForChanneling = 2048,
	FocusInstantly = 4096,
	MinimapTargetMustBeAlternative = 8192,
	SpendLifeInsteadEnergy = 16384,
	SelfCasting = 32768,
	ForceDoNotStopUnit = 65536,
};

[Flags]
public enum EAbilityIdFlags
{
	Specific = 0,
	BaseAttack = 1,
	Ability1 = 4,
	Ability2 = 8,
	Ability3 = 16,
	Ability4 = 32,
	Consumables = 64,
	Talents = 128,
	Portal = 2048,
	All = 2301,
};

public enum EAbilityModMode
{
	naftacost = 0,
	manacost = 1,
	cooldown = 2,
	scale = 3,
	duration = 4,
	state = 5,
};

public enum EAbilityType
{
	Simple = 0,
	Active = 1,
	MultiActive = 2,
	Passive = 3,
	Autocastable = 4,
	Switchable = 5,
	Channelling = 6,
};

public enum EAbilityTypeId
{
	BaseAttack = 0,
	Ability0 = 1,
	Ability1 = 2,
	Ability2 = 3,
	Ability3 = 4,
	Ability4 = 5,
	Consumable = 6,
	Talent = 7,
	TalentFromList = 8,
	ImpulsiveBuff = 9,
	Special = 10,
	Portal = 11,
};

[Flags]
public enum EAbilityUpgradeMode
{
	None = 0,
	DontUseOriginal = 1,
	UseAbilityMana = 2,
	UseAbilityCooldown = 4,
	UseGlyph = 8,
	ChangeIcon = 16,
	ApplyOncePerCast = 32,
	ApplyOncePerCastPerTarget = 64,
};

public enum EApplicatorAppliedMode
{
	Default = 0,
	Cancel = 1,
	SetNewLifetime = 2,
};

public enum EApplicatorApplyTarget
{
	ApplicatorTarget = 0,
	AbilityOwner = 1,
	PrevApplicatorTarget = 2,
	PrevApplicatorReceiver = 3,
	Hier1UpApplicatorTarget = 4,
	Hier2UpApplicatorTarget = 5,
	Hier3UpApplicatorTarget = 6,
	AbilityTarget = 7,
	ApplicatorSelectedTarget = 8,
	CastPosition = 9,
	CastMasterPosition = 10,
};

public enum EApplicatorDamageType
{
	Material = 0,
	Energy = 1,
	Mana = 2,
	Pure = 3,
	Native = 4,
};

public enum EApplyEffectOrientation
{
	Default = 0,
	Random = 1,
	Motion = 2,
	LogicalDirection = 3,
};

public enum EAttackersType
{
	Targeters = 0,
	DamageDealers = 1,
};

public enum EAttackTargetEvadeAction
{
	AttackAgain = 0,
	StopAsComplete = 1,
	StopAsFailed = 2,
};

public enum EAuraVisualType
{
	None = 0,
	Ally = 1,
	Enemy = 2,
};

public enum EBaseUnitEvent
{
	Move = 0,
	CastMagic = 1,
	UseConsumable = 2,
	UseTalent = 3,
	Attack = 4,
	ForbidMove = 5,
	ForbidAttack = 6,
	ForbidCast = 7,
	ForcedMove = 8,
	DispatchApplied = 9,
	DispatchEvaded = 10,
	Damage = 11,
	Isolate = 12,
	ApplicatorStep = 13,
	ApplicatorApplied = 14,
	Death = 15,
	AssignTarget = 16,
	LastHit = 17,
	ForbidAutoAttack = 18,
	Pickup = 19,
	Resurrect = 20,
	AbilityStart = 21,
	ChannelingCanceled = 22,
	CancelInvisibility = 23,
	Unsummon = 24,
	ConsumableObtained = 25,
	UsePortal = 26,
	WantMoveTo = 27,
	OutgoingDamage = 28,
	DispatchMissed = 29,
	HeroKillOrAssist = 30,
	MinigameStarted = 31,
	MinigameExit = 32,
	MinigameLevelStarted = 33,
	MinigameLevelWon = 34,
	MinigameLevelFailed = 35,
};

[Flags]
public enum EBaseUnitEventFlags
{
	Zero = 0,
	Move = 1,
	CastMagic = 2,
	UseConsumable = 4,
	UseTalent = 8,
	Attack = 16,
	ForbidMove = 32,
	ForbidAttack = 64,
	ForbidCast = 128,
	ForcedMove = 256,
	DispatchApplied = 512,
	DispatchEvaded = 1024,
	Damage = 2048,
	Isolate = 4096,
	ApplicatorStep = 8192,
	ApplicatorApplied = 16384,
	Death = 32768,
	AssignTarget = 65536,
	LastHit = 131072,
	ForbidAutoAttack = 262144,
	Pickup = 524288,
	Resurrect = 1048576,
	AbilityStart = 2097152,
	ChannelingCanceled = 4194304,
	CancelInvisibility = 8388608,
	Unsummon = 16777216,
	UsePortal = 67108864,
	DispatchMissed = 536870912,
	HeroKillOrAssist = 1073741824,
};

[Flags]
public enum EBehaviourChangeFlags
{
	Zero = 0,
	DummyBehaviour = 1,
	ChangeFaction = 2,
	PrimarySummon = 4,
	ChangePermanently = 8,
	ChangeType2Summon = 16,
	DisableBehaviour = 32,
};

public enum EBetweenUnitsMode
{
	AllPairs = 0,
	Chain = 1,
};

[Flags]
public enum EBounceFlags
{
	BounceNextTargetOnLoss = 1,
	RenewTargetOnStart = 2,
	StartFromOwner = 4,
};

[Flags]
public enum EBuffBehavior
{
	Zero = 0,
	StopOnDisable = 1,
	RemoveChildren = 2,
	DontShowInBar = 4,
	DontStopOnDeath = 8,
	EnabledOnSenderDeath = 16,
	DontRemoveEffect = 32,
	ApplyToDead = 64,
	DontStopOnSenderDeath = 128,
};

public enum EChannelingType
{
	Streaming = 0,
	Creation = 1,
};

[Flags]
public enum ECloneFlags
{
	None = 0,
	GhostMove = 1,
	DoLevelUp = 2,
	MirrorOwnerSpells = 4,
	UseAbilityAI = 8,
	PlaySummonEffect = 16,
	MakeSlave = 32,
	CopyStats = 64,
	DummyBehaviour = 128,
	InitTalents = 256,
};

[Flags]
public enum EConsumableOriginFlags
{
	Shop = 2,
	Minigame = 4,
	Pickupable = 8,
	Applicator = 16,
	Script = 32,
};

[NoCode]
public enum ECustomApplyType
{
	None = 0,
	Maximize = 1,
	Minimize = 2,
};

[Flags]
public enum EDamageFilter
{
	Zero = 0,
	Melee = 1,
	Ranged = 2,
	Material = 4,
	Energy = 8,
	Pure = 16,
	All = 31,
};

[Flags]
public enum EDamageMode
{
	Zero = 0,
	ApplyLifeDrains = 1,
	ApplyEnergyDrains = 2,
	DontAttackBack = 4,
	CouldBeCritical = 8,
};

[Flags]
public enum EDelegateDamageFlags
{
	AllowDrains = 1,
};

public enum EDispatchAiming
{
	Straight = 0,
	Homing = 1,
	Pursue = 2,
};

[Flags]
public enum EDispatchFlags
{
	Upgradable = 1,
	Evadable = 2,
	Aggressive = 4,
};

public enum EDispatchFlyMode
{
	Parabolic = 0,
	Linear = 1,
	FixedHeight = 2,
};

public enum EDispatchType
{
	Immediate = 0,
	Linear = 1,
	ByTime = 2,
};

public enum EDispellPriority
{
	NonDispellable = -1,
	Low = 0,
	Medium = 1,
	High = 2,
};

[Flags]
public enum EFXFlags
{
	ApplyFXToAux = 1,
};

[Flags]
public enum EGhostMoveMode
{
	IgnoreDynamic = 1,
	IgnoreBuildings = 2,
	IgnoreStatic = 4,
};

public enum EHealTarget
{
	Health = 0,
	Energy = 1,
};

public enum EKickAwayBehaviour
{
	KickFromSender = 0,
	KickFromHier1UpTarget = 1,
	KickFromHier1UpTargetMoveDirection = 2,
};

public enum EKillMode
{
	None = 0,
	DontShowDeath = 1,
	InstantRemove = 2,
	Unsummon = 3,
};

public enum EParentNotification
{
	NA = -1,
	Start = 0,
	Stop = 1,
	Done = 2,
	Cancel = 3,
};

[Flags]
public enum EParentNotificationFlags
{
	Zero = 0,
	Start = 1,
	Stop = 2,
	Done = 4,
	Cancel = 8,
};

public enum EPointTargetSelectorMode
{
	ToOwner = 0,
	ToTarget = 1,
	RangeFromOwner = 2,
	RangeFromTarget = 3,
	Interpolation = 4,
	OffsetFromOwner = 5,
	RangeFromTargetToRequester = 6,
	OffsetFromTarget = 7,
	RandomPoint = 8,
	RandomDirection = 9,
	RangeFromTargetToAbility = 10,
};

public enum EScaleCalculationMode
{
	ScaleIsCount = 0,
	ScaleIsTime = 1,
	ScaleIsVPar = 2,
};

public enum ESortingOrder
{
	Increasing = 0,
	Decreasing = 1,
};

[Flags]
public enum ESpellTarget
{
	HeroMale = 1,
	HeroFemale = 2,
	Summon = 4,
	Creep = 8,
	SiegeCreep = 16,
	NeutralCreep = 32,
	Tower = 64,
	MainBuilding = 256,
	Building = 128,
	Shop = 512,
	Tree = 1024,
	Pickupable = 4096,
	MinigamePlaces = 8192,
	DeadBodies = 16384,
	DummyUnit = 65536,
	Flagpole = 131072,
	NeutralChampion = 262144,
	NeutralBoss = 524288,
	FactionChampion = 1048576,
	AllNeutrals = 786464,
	All = 2040319,
	AllWoBuildings = 1900607,
	Flying = 4194304,
	LineOfSight = 2097152,
	VulnerableTargetsOnly = 8388608,
	Land = 16777216,
	Neutral = 33554432,
	AffectMounted = 67108864,
	VisibleTargetsOnly = 134217728,
	Ally = 268435456,
	Enemy = 536870912,
	Self = 1073741824,
	AllEnemies = 538911231,
};

public enum EStackingRule
{
	Unstackable = 0,
	PartiallyStackable = 1,
	FullyStackable = 2,
};

public enum EStatConstraint
{
	None = 0,
	UpperLimit = 1,
	LowerLimit = 2,
};

[Flags]
public enum EStatusFlags
{
	None = 0,
	UpdateLifetime = 1,
	IsDebuff = 2,
	StopSameConflicted = 4,
	AlwaysMerge = 8,
	ShowSingle = 16,
	StopAllConflicted = 32,
	IsBuff = 64,
};

public enum EStopBehaviour
{
	StopByTime = 0,
	StopByChild = 1,
	StopByAllChilds = 2,
};

[Flags]
public enum ESummonFlags
{
	None = 0,
	Essential = 1,
	AlphaSummon = 2,
	NoHealthPriority = 4,
	CopyLevelAndStats = 8,
	TurnByMasterDirection = 16,
	NoSummonAnimation = 32,
	UseGlowEffect = 64,
	NoCollision = 128,
	LikeHero = 256,
};

[Flags]
public enum ETargetSelectorFlags
{
	Zero = 0,
	IgnoreOriginalTarget = 1,
	DeadAllowed = 2,
};

public enum ETargetSelectorMode
{
	Normal = 0,
	CaptureTargets = 1,
	SendOnce = 2,
};

public enum ETargetSelectorPoint
{
	AbilityOwner = 0,
	CurrentPosition = 1,
	PreviousPosition = 2,
	OwnerDirection = 3,
};

public enum ETeamID
{
	A = 0,
	B = 1,
};

public enum EThrowType
{
	Throw = 0,
	Jump = 1,
	Flip = 2,
};

[Flags]
public enum ETraceMode
{
	Dynamic = 1,
	Static = 2,
	Building = 4,
};

[Flags]
public enum ETriggerAbilitiesAbilitiesFlags
{
	None = 0,
	BaseAttack = 1,
	Ability0 = 2,
	Ability1 = 4,
	Ability2 = 8,
	Ability3 = 16,
	Ability4 = 32,
	Consumable = 64,
	Talent = 128,
	Special = 1024,
	All = 1279,
	OnlyClassTalent = 134217856,
	FromList = 268435456,
	FromAlly = 536870912,
	FromEnemy = 1073741824,
};

[Flags]
public enum ETriggerEventCheckSender
{
	None = 0,
	MatchTarget = 1,
	ObjectFilter = 2,
};

[Flags]
public enum ETriggerEventFlags
{
	None = 0,
	OnlyFirstFromAbility = 1,
	OncePerStep = 2,
};

public enum EUnitCreationPlace
{
	DirectToTarget = 0,
	AtTarget = 1,
	AtCreator = 2,
};

[Flags]
public enum EUnitFlag
{
	ForbidMove = 1,
	ForbidSelectTarget = 2,
	ForbidAttack = 4,
	Forbid_Ability1 = 8,
	Forbid_Ability2 = 16,
	Forbid_Ability3 = 32,
	Forbid_Ability4 = 64,
	ForbidTakeDamage = 128,
	ForbidAutotargetMe = 256,
	ForbidUseConsumables = 512,
	ForbidUseTalents = 1024,
	Isolated = 2047,
	Invisible = 2048,
	CanSeeInvisible = 4096,
	Stun = 8192,
	ForbidLifeRestore = 16384,
	ForbidEnergyRestore = 32768,
	IgnoreInvisible = 65536,
	ForbidMoveSpecial = 131072,
	ForbidDeath = 262144,
	ForbidInteract = 524288,
	Flying = 1048576,
	ForbidAutoAttack = 2097152,
	ForbidPick = 4194304,
	ForbidPlayerControl = 8388608,
	CanTurnWhileForbidMove = 16777216,
	Freeze = 33554432,
	IgnorePush = 67108864,
	ForbidInvisibility = 134217728,
	InMinigame = 268435456,
	LiveAfterDeath = 536870912,
	ForbidRewards = 1073741824,
};

public enum EUnitFlagType
{
	ForbidMove = 0,
	ForbidSelectTarget = 1,
	ForbidAttack = 2,
	Forbid_Ability1 = 3,
	Forbid_Ability2 = 4,
	Forbid_Ability3 = 5,
	Forbid_Ability4 = 6,
	ForbidTakeDamage = 7,
	ForbidAutotargetMe = 8,
	ForbidUseConsumables = 9,
	ForbidUseTalents = 10,
	Invisible = 11,
	CanSeeInvisible = 12,
	Stun = 13,
	ForbidLifeRestore = 14,
	ForbidEnergyRestore = 15,
	IgnoreInvisible = 16,
	ForbidMoveSpecial = 17,
	ForbidDeath = 18,
	ForbidInteract = 19,
	Flying = 20,
	ForbidAutoAttack = 21,
	ForbidPick = 22,
	ForbidPlayerControl = 23,
	CanTurnWhileForbidMove = 24,
	Freeze = 25,
	IgnorePush = 26,
	ForbidInvisibility = 27,
	InMinigame = 28,
	LiveAfterDeath = 29,
	ForbidRewards = 30,
};

public enum EUnitRelation
{
	Master = 0,
	Target = 1,
	AlphaSummon = 2,
	Mount = 3,
};

[Custom("Social")]
public enum EUnitType
{
	Invalid = -1,
	HeroMale = 0,
	HeroFemale = 1,
	Summon = 2,
	Creep = 3,
	SiegeCreep = 4,
	NeutralCreep = 5,
	Tower = 6,
	Building = 7,
	MainBuilding = 8,
	Shop = 9,
	Tree = 10,
	Pet = 11,
	Pickupable = 12,
	MinigamePlace = 13,
	DeadBody = 14,
	SimpleObject = 15,
	DummyUnit = 16,
	Flagpole = 17,
	NeutralChampion = 18,
	NeutralBoss = 19,
	FactionChampion = 20,
};

[Flags]
public enum EUpdateDurationFlags
{
	None = 0,
	CheckByFormulaName = 1,
	SetDuration = 2,
};

public enum EUseMode
{
	ListAsRule = 0,
	ListAsException = 1,
};

[Flags]
public enum EWaitForSpellBehaviour
{
	Zero = 0,
	StopWhenSpellFinished = 1,
	UpdateParentTarget = 2,
	DontApplyEffectOnFirstTarget = 4,
};

public enum SummonPlaceMode
{
	ByApplicator = 0,
	ByTargetSelector = 1,
	ByBehaviour = 2,
};

public enum SummonSource
{
	ByApplicator = 0,
	TargetClone = 1,
};

public enum SummonType
{
	Primary = 0,
	Secondary = 1,
	Pet = 2,
	Clone = 3,
};

[Flags]
public enum SummonTypeFlags
{
	Primary = 1,
	Secondary = 2,
	Pet = 4,
	Clone = 8,
};

public enum TargetToLandMode
{
	First = 0,
	Nearest = 1,
	Center = 2,
	CenterTarget = 3,
};

[Flags]
public enum UnitDieKillersFlags
{
	KilledByMe = 1,
	KilledByAllies = 2,
	KilledByEnemy = 4,
	KilledByMySummons = 8,
	KilledByAll = 7,
};

[Custom("Social")]
[DBVersion(21)]
[NoCode]
[NonTerminal]
public abstract class BaseExecutableString : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BaseExecutableString __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _sString;
	private UndoRedo<string> _compiledString;

	public string sString { get { return _sString.Get(); } set { _sString.Set( value ); } }

	[ReadOnly( true )]
	public string compiledString { get { return _compiledString.Get(); } set { _compiledString.Set( value ); } }

	[Abstract]
	[ReadOnly( true )]
	public abstract string returnType { get; set; }

	private void Initialize( DBResource owner )
	{
		_sString = new UndoRedo<string>( owner, "0" );
		_compiledString = new UndoRedo<string>( owner, string.Empty );
		_sString.Changed += FireChangedEvent;
		_compiledString.Changed += FireChangedEvent;
	}

	public BaseExecutableString()
	{
		Initialize( GetOwner() );
	}

	public BaseExecutableString( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BaseExecutableString( DBResource owner, BaseExecutableString source )
		: this(owner, source, true){}

	protected BaseExecutableString( DBResource owner, BaseExecutableString source, bool fireEvent )
	{
		_sString = new UndoRedo<string>( owner, source.sString );
		_compiledString = new UndoRedo<string>( owner, source.compiledString );
		_sString.Changed += FireChangedEvent;
		_compiledString.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BaseExecutableString source = _source as BaseExecutableString;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BaseExecutableString" );
		sString = source.sString;
		compiledString = source.compiledString;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BaseExecutableString newParent = _newParent as BaseExecutableString;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_sString.SetParent( newParent == null ? null : newParent._sString );
		_compiledString.SetParent( newParent == null ? null : newParent._compiledString );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_sString.Reset();
		_compiledString.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_sString.IsDerivedFromParent()
			&& _compiledString.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "sString" )
			_sString.Reset();
		else if ( fieldName == "compiledString" )
			_compiledString.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "sString" )
			return _sString.IsDerivedFromParent();
		if ( fieldName == "compiledString" )
			return _compiledString.IsDerivedFromParent();
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
[IndexField("applicator")]
public class ApplicatorToProxy : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ApplicatorToProxy __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<BaseApplicator> _applicator;
	private UndoRedoList<string> _variableNames;

	[Description( "Applicator to execute" )]
	public DBPtr<BaseApplicator> applicator { get { return _applicator.Get(); } set { _applicator.Set( value ); } }

	[Description( "Names of variables which values should be retrieved and stored" )]
	public libdb.IChangeableList<string> variableNames { get { return _variableNames; } set { _variableNames.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_applicator = new UndoRedoDBPtr<BaseApplicator>( owner );
		_variableNames = new UndoRedoList<string>( owner );
		_applicator.Changed += FireChangedEvent;
		_variableNames.Changed += FireChangedEvent;
	}

	public ApplicatorToProxy()
	{
		Initialize( GetOwner() );
	}

	public ApplicatorToProxy( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ApplicatorToProxy( DBResource owner, ApplicatorToProxy source )
		: this(owner, source, true){}

	protected ApplicatorToProxy( DBResource owner, ApplicatorToProxy source, bool fireEvent )
	{
		_applicator = new UndoRedoDBPtr<BaseApplicator>( owner, source.applicator );
		_variableNames = new UndoRedoList<string>( owner );
		_variableNames.Assign( source.variableNames );
		_applicator.Changed += FireChangedEvent;
		_variableNames.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ApplicatorToProxy source = _source as ApplicatorToProxy;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ApplicatorToProxy" );
		applicator = source.applicator;
		variableNames = source.variableNames;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ApplicatorToProxy newParent = _newParent as ApplicatorToProxy;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_applicator.SetParent( newParent == null ? null : newParent._applicator );
		_variableNames.SetParent( newParent == null ? null : newParent._variableNames );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_applicator.Reset();
		_variableNames.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_applicator.IsDerivedFromParent()
			&& _variableNames.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "applicator" )
			_applicator.Reset();
		else if ( fieldName == "variableNames" )
			_variableNames.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "applicator" )
			return _applicator.IsDerivedFromParent();
		if ( fieldName == "variableNames" )
			return _variableNames.IsDerivedFromParent();
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
[NoCode]
public class ExecutableBoolString : BaseExecutableString, libdb.ICompositeDBValue, libdb.IChangeable
{

	private ExecutableBoolString __parent = null;

	private UndoRedo<string> _returnType;

	public override string returnType { get { return _returnType.Get(); } set { _returnType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_returnType = new UndoRedo<string>( owner, "bool" );
		_returnType.Changed += FireChangedEvent;
	}

	public ExecutableBoolString()
	{
		Initialize( GetOwner() );
	}

	public ExecutableBoolString( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public ExecutableBoolString( DBResource owner, ExecutableBoolString source ): base(owner, source, false)
	{
		_returnType = new UndoRedo<string>( owner, source.returnType );
		_returnType.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		ExecutableBoolString source = _source as ExecutableBoolString;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ExecutableBoolString" );

		base.Assign( source );

		returnType = source.returnType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		ExecutableBoolString newParent = _newParent as ExecutableBoolString;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_returnType.SetParent( newParent == null ? null : newParent._returnType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_returnType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_returnType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "returnType" )
			_returnType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "returnType" )
			return _returnType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[NoCode]
public class ExecutableBooleanString : BaseExecutableString, libdb.ICompositeDBValue, libdb.IChangeable
{

	private ExecutableBooleanString __parent = null;

	private UndoRedo<string> _returnType;

	public override string returnType { get { return _returnType.Get(); } set { _returnType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_returnType = new UndoRedo<string>( owner, "boolean" );
		_returnType.Changed += FireChangedEvent;
	}

	public ExecutableBooleanString()
	{
		Initialize( GetOwner() );
	}

	public ExecutableBooleanString( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public ExecutableBooleanString( DBResource owner, ExecutableBooleanString source ): base(owner, source, false)
	{
		_returnType = new UndoRedo<string>( owner, source.returnType );
		_returnType.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		ExecutableBooleanString source = _source as ExecutableBooleanString;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ExecutableBooleanString" );

		base.Assign( source );

		returnType = source.returnType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		ExecutableBooleanString newParent = _newParent as ExecutableBooleanString;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_returnType.SetParent( newParent == null ? null : newParent._returnType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_returnType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_returnType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "returnType" )
			_returnType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "returnType" )
			return _returnType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[NoCode]
public class ExecutableFloatString : BaseExecutableString, libdb.ICompositeDBValue, libdb.IChangeable
{

	private ExecutableFloatString __parent = null;

	private UndoRedo<string> _returnType;

	public override string returnType { get { return _returnType.Get(); } set { _returnType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_returnType = new UndoRedo<string>( owner, "float" );
		_returnType.Changed += FireChangedEvent;
	}

	public ExecutableFloatString()
	{
		Initialize( GetOwner() );
	}

	public ExecutableFloatString( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public ExecutableFloatString( DBResource owner, ExecutableFloatString source ): base(owner, source, false)
	{
		_returnType = new UndoRedo<string>( owner, source.returnType );
		_returnType.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		ExecutableFloatString source = _source as ExecutableFloatString;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ExecutableFloatString" );

		base.Assign( source );

		returnType = source.returnType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		ExecutableFloatString newParent = _newParent as ExecutableFloatString;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_returnType.SetParent( newParent == null ? null : newParent._returnType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_returnType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_returnType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "returnType" )
			_returnType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "returnType" )
			return _returnType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("applicator")]
public class ApplicatorToExecute : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ApplicatorToExecute __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<BaseApplicator> _applicator;
	private ExecutableFloatString _delay;
	private ExecutableBoolString _continueCondition;
	private ExecutableBoolString _stopCondition;
	private UndoRedo<EParentNotificationFlags> _continueEvents;
	private UndoRedo<EParentNotificationFlags> _stopEvents;

	public DBPtr<BaseApplicator> applicator { get { return _applicator.Get(); } set { _applicator.Set( value ); } }

	[Description( "Через сколько секунд переключимся на следующий аппликатор в списке. -1 — механизм не задействован" )]
	public ExecutableFloatString delay { get { return _delay; } set { _delay.Assign( value ); } }

	[Description( "Дополнительное условие переключения на следующий аппликатор в списке" )]
	public ExecutableBoolString continueCondition { get { return _continueCondition; } set { _continueCondition.Assign( value ); } }

	[Description( "Дополнительное условие останова программы" )]
	public ExecutableBoolString stopCondition { get { return _stopCondition; } set { _stopCondition.Assign( value ); } }

	public EParentNotificationFlags continueEvents { get { return _continueEvents.Get(); } set { _continueEvents.Set( value ); } }

	public EParentNotificationFlags stopEvents { get { return _stopEvents.Get(); } set { _stopEvents.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_applicator = new UndoRedoDBPtr<BaseApplicator>( owner );
		ExecutableFloatString __delay = new ExecutableFloatString(); // Construct default object for delay
		__delay.sString = "-1.0";
		_delay = new ExecutableFloatString( owner, __delay );
		_continueCondition = new ExecutableBoolString( owner );
		_stopCondition = new ExecutableBoolString( owner );
		_continueEvents = new UndoRedo<EParentNotificationFlags>( owner, EParentNotificationFlags.Stop );
		_stopEvents = new UndoRedo<EParentNotificationFlags>( owner, EParentNotificationFlags.Zero );
		_applicator.Changed += FireChangedEvent;
		_delay.Changed += FireChangedEvent;
		_continueCondition.Changed += FireChangedEvent;
		_stopCondition.Changed += FireChangedEvent;
		_continueEvents.Changed += FireChangedEvent;
		_stopEvents.Changed += FireChangedEvent;
	}

	public ApplicatorToExecute()
	{
		Initialize( GetOwner() );
	}

	public ApplicatorToExecute( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ApplicatorToExecute( DBResource owner, ApplicatorToExecute source )
		: this(owner, source, true){}

	protected ApplicatorToExecute( DBResource owner, ApplicatorToExecute source, bool fireEvent )
	{
		_applicator = new UndoRedoDBPtr<BaseApplicator>( owner, source.applicator );
		_delay = new ExecutableFloatString( owner, source.delay );
		_continueCondition = new ExecutableBoolString( owner, source.continueCondition );
		_stopCondition = new ExecutableBoolString( owner, source.stopCondition );
		_continueEvents = new UndoRedo<EParentNotificationFlags>( owner, source.continueEvents );
		_stopEvents = new UndoRedo<EParentNotificationFlags>( owner, source.stopEvents );
		_applicator.Changed += FireChangedEvent;
		_delay.Changed += FireChangedEvent;
		_continueCondition.Changed += FireChangedEvent;
		_stopCondition.Changed += FireChangedEvent;
		_continueEvents.Changed += FireChangedEvent;
		_stopEvents.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ApplicatorToExecute source = _source as ApplicatorToExecute;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ApplicatorToExecute" );
		applicator = source.applicator;
		delay = source.delay;
		continueCondition = source.continueCondition;
		stopCondition = source.stopCondition;
		continueEvents = source.continueEvents;
		stopEvents = source.stopEvents;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ApplicatorToExecute newParent = _newParent as ApplicatorToExecute;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_applicator.SetParent( newParent == null ? null : newParent._applicator );
		_delay.SetParent( newParent == null ? null : newParent._delay );
		_continueCondition.SetParent( newParent == null ? null : newParent._continueCondition );
		_stopCondition.SetParent( newParent == null ? null : newParent._stopCondition );
		_continueEvents.SetParent( newParent == null ? null : newParent._continueEvents );
		_stopEvents.SetParent( newParent == null ? null : newParent._stopEvents );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_applicator.Reset();
		_delay.Reset();
		_continueCondition.Reset();
		_stopCondition.Reset();
		_continueEvents.Reset();
		_stopEvents.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_applicator.IsDerivedFromParent()
			&& _delay.IsDerivedFromParent()
			&& _continueCondition.IsDerivedFromParent()
			&& _stopCondition.IsDerivedFromParent()
			&& _continueEvents.IsDerivedFromParent()
			&& _stopEvents.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "applicator" )
			_applicator.Reset();
		else if ( fieldName == "delay" )
			_delay.Reset();
		else if ( fieldName == "continueCondition" )
			_continueCondition.Reset();
		else if ( fieldName == "stopCondition" )
			_stopCondition.Reset();
		else if ( fieldName == "continueEvents" )
			_continueEvents.Reset();
		else if ( fieldName == "stopEvents" )
			_stopEvents.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "applicator" )
			return _applicator.IsDerivedFromParent();
		if ( fieldName == "delay" )
			return _delay.IsDerivedFromParent();
		if ( fieldName == "continueCondition" )
			return _continueCondition.IsDerivedFromParent();
		if ( fieldName == "stopCondition" )
			return _stopCondition.IsDerivedFromParent();
		if ( fieldName == "continueEvents" )
			return _continueEvents.IsDerivedFromParent();
		if ( fieldName == "stopEvents" )
			return _stopEvents.IsDerivedFromParent();
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
[NoCode]
public class ExecutableIntString : BaseExecutableString, libdb.ICompositeDBValue, libdb.IChangeable
{

	private ExecutableIntString __parent = null;

	private UndoRedo<string> _returnType;

	public override string returnType { get { return _returnType.Get(); } set { _returnType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_returnType = new UndoRedo<string>( owner, "int" );
		_returnType.Changed += FireChangedEvent;
	}

	public ExecutableIntString()
	{
		Initialize( GetOwner() );
	}

	public ExecutableIntString( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public ExecutableIntString( DBResource owner, ExecutableIntString source ): base(owner, source, false)
	{
		_returnType = new UndoRedo<string>( owner, source.returnType );
		_returnType.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		ExecutableIntString source = _source as ExecutableIntString;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ExecutableIntString" );

		base.Assign( source );

		returnType = source.returnType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		ExecutableIntString newParent = _newParent as ExecutableIntString;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_returnType.SetParent( newParent == null ? null : newParent._returnType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_returnType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_returnType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "returnType" )
			_returnType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "returnType" )
			return _returnType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class LightningLink : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LightningLink __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<LightningEffect>> _effect;

	[Description( "Lightning effect for visualization." )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<LightningEffect>> effect { get { return _effect; } set { _effect.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_effect = new UndoRedoAssignableList<DBPtr<LightningEffect>>( owner, typeof( ETeamID ) );
		_effect.Changed += FireChangedEvent;
	}

	public LightningLink()
	{
		Initialize( GetOwner() );
	}

	public LightningLink( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LightningLink( DBResource owner, LightningLink source )
		: this(owner, source, true){}

	protected LightningLink( DBResource owner, LightningLink source, bool fireEvent )
	{
		_effect = new UndoRedoAssignableList<DBPtr<LightningEffect>>( owner, typeof( ETeamID ) );
		_effect.Assign( source.effect );
		_effect.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LightningLink source = _source as LightningLink;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LightningLink" );
		effect = source.effect;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LightningLink newParent = _newParent as LightningLink;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_effect.SetParent( newParent == null ? null : newParent._effect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_effect.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_effect.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "effect" )
			_effect.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "effect" )
			return _effect.IsDerivedFromParent();
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
public class Modifier : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Modifier __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EStat> _stat;
	private UndoRedo<string> _variable;
	private ExecutableFloatString _addValue;
	private ExecutableFloatString _multValue;
	private UndoRedo<bool> _topModifier;

	[Description( "Stat to be modified" )]
	public EStat stat { get { return _stat.Get(); } set { _stat.Set( value ); } }

	[Description( "Value to be modified" )]
	public string variable { get { return _variable.Get(); } set { _variable.Set( value ); } }

	[Description( "Value to be added to stat [Formula update: every step]" )]
	public ExecutableFloatString addValue { get { return _addValue; } set { _addValue.Assign( value ); } }

	[Description( "Value to be multiplied on stat [Formula update: every step]" )]
	public ExecutableFloatString multValue { get { return _multValue; } set { _multValue.Assign( value ); } }

	[Description( "This modifier is applied to top" )]
	public bool topModifier { get { return _topModifier.Get(); } set { _topModifier.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_stat = new UndoRedo<EStat>( owner, EStat.Life );
		_variable = new UndoRedo<string>( owner, string.Empty );
		ExecutableFloatString __addValue = new ExecutableFloatString(); // Construct default object for addValue
		__addValue.sString = "0.0f";
		_addValue = new ExecutableFloatString( owner, __addValue );
		ExecutableFloatString __multValue = new ExecutableFloatString(); // Construct default object for multValue
		__multValue.sString = "1.0f";
		_multValue = new ExecutableFloatString( owner, __multValue );
		_topModifier = new UndoRedo<bool>( owner, false );
		_stat.Changed += FireChangedEvent;
		_variable.Changed += FireChangedEvent;
		_addValue.Changed += FireChangedEvent;
		_multValue.Changed += FireChangedEvent;
		_topModifier.Changed += FireChangedEvent;
	}

	public Modifier()
	{
		Initialize( GetOwner() );
	}

	public Modifier( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Modifier( DBResource owner, Modifier source )
		: this(owner, source, true){}

	protected Modifier( DBResource owner, Modifier source, bool fireEvent )
	{
		_stat = new UndoRedo<EStat>( owner, source.stat );
		_variable = new UndoRedo<string>( owner, source.variable );
		_addValue = new ExecutableFloatString( owner, source.addValue );
		_multValue = new ExecutableFloatString( owner, source.multValue );
		_topModifier = new UndoRedo<bool>( owner, source.topModifier );
		_stat.Changed += FireChangedEvent;
		_variable.Changed += FireChangedEvent;
		_addValue.Changed += FireChangedEvent;
		_multValue.Changed += FireChangedEvent;
		_topModifier.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Modifier source = _source as Modifier;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Modifier" );
		stat = source.stat;
		variable = source.variable;
		addValue = source.addValue;
		multValue = source.multValue;
		topModifier = source.topModifier;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Modifier newParent = _newParent as Modifier;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_stat.SetParent( newParent == null ? null : newParent._stat );
		_variable.SetParent( newParent == null ? null : newParent._variable );
		_addValue.SetParent( newParent == null ? null : newParent._addValue );
		_multValue.SetParent( newParent == null ? null : newParent._multValue );
		_topModifier.SetParent( newParent == null ? null : newParent._topModifier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_stat.Reset();
		_variable.Reset();
		_addValue.Reset();
		_multValue.Reset();
		_topModifier.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_stat.IsDerivedFromParent()
			&& _variable.IsDerivedFromParent()
			&& _addValue.IsDerivedFromParent()
			&& _multValue.IsDerivedFromParent()
			&& _topModifier.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "stat" )
			_stat.Reset();
		else if ( fieldName == "variable" )
			_variable.Reset();
		else if ( fieldName == "addValue" )
			_addValue.Reset();
		else if ( fieldName == "multValue" )
			_multValue.Reset();
		else if ( fieldName == "topModifier" )
			_topModifier.Reset();
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
		if ( fieldName == "variable" )
			return _variable.IsDerivedFromParent();
		if ( fieldName == "addValue" )
			return _addValue.IsDerivedFromParent();
		if ( fieldName == "multValue" )
			return _multValue.IsDerivedFromParent();
		if ( fieldName == "topModifier" )
			return _topModifier.IsDerivedFromParent();
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

public class SpawnStats : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SpawnStats __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private ExecutableFloatString _life;
	private ExecutableFloatString _energy;

	public ExecutableFloatString life { get { return _life; } set { _life.Assign( value ); } }

	public ExecutableFloatString energy { get { return _energy; } set { _energy.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		ExecutableFloatString __life = new ExecutableFloatString(); // Construct default object for life
		__life.sString = "-1.0";
		_life = new ExecutableFloatString( owner, __life );
		ExecutableFloatString __energy = new ExecutableFloatString(); // Construct default object for energy
		__energy.sString = "-1.0";
		_energy = new ExecutableFloatString( owner, __energy );
		_life.Changed += FireChangedEvent;
		_energy.Changed += FireChangedEvent;
	}

	public SpawnStats()
	{
		Initialize( GetOwner() );
	}

	public SpawnStats( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SpawnStats( DBResource owner, SpawnStats source )
		: this(owner, source, true){}

	protected SpawnStats( DBResource owner, SpawnStats source, bool fireEvent )
	{
		_life = new ExecutableFloatString( owner, source.life );
		_energy = new ExecutableFloatString( owner, source.energy );
		_life.Changed += FireChangedEvent;
		_energy.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SpawnStats source = _source as SpawnStats;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpawnStats" );
		life = source.life;
		energy = source.energy;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SpawnStats newParent = _newParent as SpawnStats;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_life.SetParent( newParent == null ? null : newParent._life );
		_energy.SetParent( newParent == null ? null : newParent._energy );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_life.Reset();
		_energy.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_life.IsDerivedFromParent()
			&& _energy.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "life" )
			_life.Reset();
		else if ( fieldName == "energy" )
			_energy.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "life" )
			return _life.IsDerivedFromParent();
		if ( fieldName == "energy" )
			return _energy.IsDerivedFromParent();
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

public class SummonBehaviourCommonParams : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SummonBehaviourCommonParams __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<UnitTargetingParameters> _targetingParams;
	private ExecutableFloatString _lashRange;
	private UndoRedo<float> _responseRange;
	private UndoRedo<float> _responseTime;

	[Description( "Override targeting params" )]
	public DBPtr<UnitTargetingParameters> targetingParams { get { return _targetingParams.Get(); } set { _targetingParams.Set( value ); } }

	[Category( "Ranges" )]
	[Description( "Радиус в пределах которого саммон будет стараться находится в обычном состоянии." )]
	public ExecutableFloatString lashRange { get { return _lashRange; } set { _lashRange.Assign( value ); } }

	[Category( "Ranges" )]
	[Description( "Радиус за пределами которого команда move воспринимается саммоном как приказ к немедленному движению и игнорированию всех целей" )]
	public float responseRange { get { return _responseRange.Get(); } set { _responseRange.Set( value ); } }

	[Description( "Время в течении которого саммон бежит в указанную точку игнорируя цели." )]
	public float responseTime { get { return _responseTime.Get(); } set { _responseTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_targetingParams = new UndoRedoDBPtr<UnitTargetingParameters>( owner );
		ExecutableFloatString __lashRange = new ExecutableFloatString(); // Construct default object for lashRange
		__lashRange.sString = "0.0";
		_lashRange = new ExecutableFloatString( owner, __lashRange );
		_responseRange = new UndoRedo<float>( owner, 0.0f );
		_responseTime = new UndoRedo<float>( owner, 0.0f );
		_targetingParams.Changed += FireChangedEvent;
		_lashRange.Changed += FireChangedEvent;
		_responseRange.Changed += FireChangedEvent;
		_responseTime.Changed += FireChangedEvent;
	}

	public SummonBehaviourCommonParams()
	{
		Initialize( GetOwner() );
	}

	public SummonBehaviourCommonParams( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SummonBehaviourCommonParams( DBResource owner, SummonBehaviourCommonParams source )
		: this(owner, source, true){}

	protected SummonBehaviourCommonParams( DBResource owner, SummonBehaviourCommonParams source, bool fireEvent )
	{
		_targetingParams = new UndoRedoDBPtr<UnitTargetingParameters>( owner, source.targetingParams );
		_lashRange = new ExecutableFloatString( owner, source.lashRange );
		_responseRange = new UndoRedo<float>( owner, source.responseRange );
		_responseTime = new UndoRedo<float>( owner, source.responseTime );
		_targetingParams.Changed += FireChangedEvent;
		_lashRange.Changed += FireChangedEvent;
		_responseRange.Changed += FireChangedEvent;
		_responseTime.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SummonBehaviourCommonParams source = _source as SummonBehaviourCommonParams;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SummonBehaviourCommonParams" );
		targetingParams = source.targetingParams;
		lashRange = source.lashRange;
		responseRange = source.responseRange;
		responseTime = source.responseTime;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SummonBehaviourCommonParams newParent = _newParent as SummonBehaviourCommonParams;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_targetingParams.SetParent( newParent == null ? null : newParent._targetingParams );
		_lashRange.SetParent( newParent == null ? null : newParent._lashRange );
		_responseRange.SetParent( newParent == null ? null : newParent._responseRange );
		_responseTime.SetParent( newParent == null ? null : newParent._responseTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_targetingParams.Reset();
		_lashRange.Reset();
		_responseRange.Reset();
		_responseTime.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_targetingParams.IsDerivedFromParent()
			&& _lashRange.IsDerivedFromParent()
			&& _responseRange.IsDerivedFromParent()
			&& _responseTime.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "targetingParams" )
			_targetingParams.Reset();
		else if ( fieldName == "lashRange" )
			_lashRange.Reset();
		else if ( fieldName == "responseRange" )
			_responseRange.Reset();
		else if ( fieldName == "responseTime" )
			_responseTime.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "targetingParams" )
			return _targetingParams.IsDerivedFromParent();
		if ( fieldName == "lashRange" )
			return _lashRange.IsDerivedFromParent();
		if ( fieldName == "responseRange" )
			return _responseRange.IsDerivedFromParent();
		if ( fieldName == "responseTime" )
			return _responseTime.IsDerivedFromParent();
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

public class TriggerAbilitiesFilter : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TriggerAbilitiesFilter __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<ETriggerAbilitiesAbilitiesFlags> _flags;
	private UndoRedo<bool> _onlySingleTarget;
	private UndoRedo<EAbilityCostMode> _abilityCostMode;
	private UndoRedoAssignableList<DBPtr<Ability>> _abilitiesList;
	private UndoRedo<bool> _exceptThis;
	private ExecutableBoolString _abilityCondition;

	public ETriggerAbilitiesAbilitiesFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	public bool onlySingleTarget { get { return _onlySingleTarget.Get(); } set { _onlySingleTarget.Set( value ); } }

	[Description( "Реагировать на абилки с указанным режимом стоимости. Для автоатаки не проверяется." )]
	public EAbilityCostMode abilityCostMode { get { return _abilityCostMode.Get(); } set { _abilityCostMode.Set( value ); } }

	public libdb.IChangeableList<DBPtr<Ability>> abilitiesList { get { return _abilitiesList; } set { _abilitiesList.Assign( value ); } }

	public bool exceptThis { get { return _exceptThis.Get(); } set { _exceptThis.Set( value ); } }

	[Description( "Условие (pMisc=фильтруемая абилка) " )]
	public ExecutableBoolString abilityCondition { get { return _abilityCondition; } set { _abilityCondition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_flags = new UndoRedo<ETriggerAbilitiesAbilitiesFlags>( owner, ETriggerAbilitiesAbilitiesFlags.FromEnemy | ETriggerAbilitiesAbilitiesFlags.FromAlly | ETriggerAbilitiesAbilitiesFlags.All );
		_onlySingleTarget = new UndoRedo<bool>( owner, false );
		_abilityCostMode = new UndoRedo<EAbilityCostMode>( owner, EAbilityCostMode.Energy );
		_abilitiesList = new UndoRedoAssignableList<DBPtr<Ability>>( owner );
		_exceptThis = new UndoRedo<bool>( owner, false );
		ExecutableBoolString __abilityCondition = new ExecutableBoolString(); // Construct default object for abilityCondition
		__abilityCondition.sString = "true";
		_abilityCondition = new ExecutableBoolString( owner, __abilityCondition );
		_flags.Changed += FireChangedEvent;
		_onlySingleTarget.Changed += FireChangedEvent;
		_abilityCostMode.Changed += FireChangedEvent;
		_abilitiesList.Changed += FireChangedEvent;
		_exceptThis.Changed += FireChangedEvent;
		_abilityCondition.Changed += FireChangedEvent;
	}

	public TriggerAbilitiesFilter()
	{
		Initialize( GetOwner() );
	}

	public TriggerAbilitiesFilter( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TriggerAbilitiesFilter( DBResource owner, TriggerAbilitiesFilter source )
		: this(owner, source, true){}

	protected TriggerAbilitiesFilter( DBResource owner, TriggerAbilitiesFilter source, bool fireEvent )
	{
		_flags = new UndoRedo<ETriggerAbilitiesAbilitiesFlags>( owner, source.flags );
		_onlySingleTarget = new UndoRedo<bool>( owner, source.onlySingleTarget );
		_abilityCostMode = new UndoRedo<EAbilityCostMode>( owner, source.abilityCostMode );
		_abilitiesList = new UndoRedoAssignableList<DBPtr<Ability>>( owner );
		_abilitiesList.Assign( source.abilitiesList );
		_exceptThis = new UndoRedo<bool>( owner, source.exceptThis );
		_abilityCondition = new ExecutableBoolString( owner, source.abilityCondition );
		_flags.Changed += FireChangedEvent;
		_onlySingleTarget.Changed += FireChangedEvent;
		_abilityCostMode.Changed += FireChangedEvent;
		_abilitiesList.Changed += FireChangedEvent;
		_exceptThis.Changed += FireChangedEvent;
		_abilityCondition.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TriggerAbilitiesFilter source = _source as TriggerAbilitiesFilter;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TriggerAbilitiesFilter" );
		flags = source.flags;
		onlySingleTarget = source.onlySingleTarget;
		abilityCostMode = source.abilityCostMode;
		abilitiesList = source.abilitiesList;
		exceptThis = source.exceptThis;
		abilityCondition = source.abilityCondition;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TriggerAbilitiesFilter newParent = _newParent as TriggerAbilitiesFilter;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_flags.SetParent( newParent == null ? null : newParent._flags );
		_onlySingleTarget.SetParent( newParent == null ? null : newParent._onlySingleTarget );
		_abilityCostMode.SetParent( newParent == null ? null : newParent._abilityCostMode );
		_abilitiesList.SetParent( newParent == null ? null : newParent._abilitiesList );
		_exceptThis.SetParent( newParent == null ? null : newParent._exceptThis );
		_abilityCondition.SetParent( newParent == null ? null : newParent._abilityCondition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_flags.Reset();
		_onlySingleTarget.Reset();
		_abilityCostMode.Reset();
		_abilitiesList.Reset();
		_exceptThis.Reset();
		_abilityCondition.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_flags.IsDerivedFromParent()
			&& _onlySingleTarget.IsDerivedFromParent()
			&& _abilityCostMode.IsDerivedFromParent()
			&& _abilitiesList.IsDerivedFromParent()
			&& _exceptThis.IsDerivedFromParent()
			&& _abilityCondition.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "onlySingleTarget" )
			_onlySingleTarget.Reset();
		else if ( fieldName == "abilityCostMode" )
			_abilityCostMode.Reset();
		else if ( fieldName == "abilitiesList" )
			_abilitiesList.Reset();
		else if ( fieldName == "exceptThis" )
			_exceptThis.Reset();
		else if ( fieldName == "abilityCondition" )
			_abilityCondition.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "onlySingleTarget" )
			return _onlySingleTarget.IsDerivedFromParent();
		if ( fieldName == "abilityCostMode" )
			return _abilityCostMode.IsDerivedFromParent();
		if ( fieldName == "abilitiesList" )
			return _abilitiesList.IsDerivedFromParent();
		if ( fieldName == "exceptThis" )
			return _exceptThis.IsDerivedFromParent();
		if ( fieldName == "abilityCondition" )
			return _abilityCondition.IsDerivedFromParent();
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
[TypeId(0x2C5C0B00)]
[UseTypeName("SPLL")]
public class Spell : DBResource
{
	private UndoRedoDBPtr<Spell> ___parent;
	[HideInOutliner]
	public new DBPtr<Spell> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Dispatch> _dispatch;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicators;

	[Category( "Dispatch" )]
	public DBPtr<Dispatch> dispatch { get { return _dispatch.Get(); } set { _dispatch.Set( value ); } }

	[Category( "Applicators" )]
	[Description( "List of applicators that will be applied to the target of the spell. Exceptions: applicators with applyMode = Passive & OnSender" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Spell>(owner);
		_dispatch = new UndoRedoDBPtr<Dispatch>( owner );
		_applicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		___parent.Changed += FireChangedEvent;
		_dispatch.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
	}

	public Spell()
	{
		Initialize( this );
	}
	private void AssignSelf( Spell source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Spell" );
		dispatch = source.dispatch;
		applicators = source.applicators;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Spell source = _source as Spell;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Spell" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Spell newParent = rawParent == null ? null : rawParent.Get<Spell>();
		if ( newParent == null && _newParent is Spell )
			newParent = _newParent as Spell;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_dispatch.SetParent( newParent == null ? null : newParent._dispatch );
		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_dispatch.Reset();
		_applicators.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_dispatch.IsDerivedFromParent()
			&& _applicators.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "dispatch" )
			_dispatch.Reset();
		else if ( fieldName == "applicators" )
			_applicators.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "dispatch" )
			return _dispatch.IsDerivedFromParent();
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryBase("Create", "NWorld::PFBaseApplicator", "NWorld::PFApplCreatePars const &cp")]
[IndexField("caption")]
[NonTerminal]
[TypeId(0x9E5C0B00)]
[UseTypeName("APLR")]
public class BaseApplicator : DBResource
{
	private UndoRedoDBPtr<BaseApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<BaseApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableBoolString _enabled;
	private UndoRedo<EApplicatorApplyTarget> _applyTarget;
	private UndoRedo<string> _formulaName;
	private UndoRedo<string> _caption;
	private UndoRedo<int> _LoggingEvent;
	private UndoRedo<string> _providerName;

	[Custom("Social")]
	[Description( "Enables/disables applicator. [Formula update: every step]" )]
	public ExecutableBoolString enabled { get { return _enabled; } set { _enabled.Assign( value ); } }

	[Description( "Specifies the target for applying the applicator. Basically it is the target of the applicator, but you can select different target" )]
	public EApplicatorApplyTarget applyTarget { get { return _applyTarget.Get(); } set { _applyTarget.Set( value ); } }

	[Description( "Name of applicator to access from formulas" )]
	public string formulaName { get { return _formulaName.Get(); } set { _formulaName.Set( value ); } }

	[Custom("Social")]
	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	[Description( "Number of logging event" )]
	public int LoggingEvent { get { return _LoggingEvent.Get(); } set { _LoggingEvent.Set( value ); } }

	[Description( "PersistentId of a talent providing this applicator" )]
	public string providerName { get { return _providerName.Get(); } set { _providerName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BaseApplicator>(owner);
		ExecutableBoolString __enabled = new ExecutableBoolString(); // Construct default object for enabled
		__enabled.sString = "true";
		_enabled = new ExecutableBoolString( owner, __enabled );
		_applyTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_formulaName = new UndoRedo<string>( owner, string.Empty );
		_caption = new UndoRedo<string>( owner, string.Empty );
		_LoggingEvent = new UndoRedo<int>( owner, -1 );
		_providerName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_enabled.Changed += FireChangedEvent;
		_applyTarget.Changed += FireChangedEvent;
		_formulaName.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_LoggingEvent.Changed += FireChangedEvent;
		_providerName.Changed += FireChangedEvent;
	}

	public BaseApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( BaseApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BaseApplicator" );
		enabled = source.enabled;
		applyTarget = source.applyTarget;
		formulaName = source.formulaName;
		caption = source.caption;
		LoggingEvent = source.LoggingEvent;
		providerName = source.providerName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BaseApplicator source = _source as BaseApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BaseApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BaseApplicator newParent = rawParent == null ? null : rawParent.Get<BaseApplicator>();
		if ( newParent == null && _newParent is BaseApplicator )
			newParent = _newParent as BaseApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_enabled.SetParent( newParent == null ? null : newParent._enabled );
		_applyTarget.SetParent( newParent == null ? null : newParent._applyTarget );
		_formulaName.SetParent( newParent == null ? null : newParent._formulaName );
		_caption.SetParent( newParent == null ? null : newParent._caption );
		_LoggingEvent.SetParent( newParent == null ? null : newParent._LoggingEvent );
		_providerName.SetParent( newParent == null ? null : newParent._providerName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_enabled.Reset();
		_applyTarget.Reset();
		_formulaName.Reset();
		_caption.Reset();
		_LoggingEvent.Reset();
		_providerName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_enabled.IsDerivedFromParent()
			&& _applyTarget.IsDerivedFromParent()
			&& _formulaName.IsDerivedFromParent()
			&& _caption.IsDerivedFromParent()
			&& _LoggingEvent.IsDerivedFromParent()
			&& _providerName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "enabled" )
			_enabled.Reset();
		else if ( fieldName == "applyTarget" )
			_applyTarget.Reset();
		else if ( fieldName == "formulaName" )
			_formulaName.Reset();
		else if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "LoggingEvent" )
			_LoggingEvent.Reset();
		else if ( fieldName == "providerName" )
			_providerName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "enabled" )
			return _enabled.IsDerivedFromParent();
		if ( fieldName == "applyTarget" )
			return _applyTarget.IsDerivedFromParent();
		if ( fieldName == "formulaName" )
			return _formulaName.IsDerivedFromParent();
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "LoggingEvent" )
			return _LoggingEvent.IsDerivedFromParent();
		if ( fieldName == "providerName" )
			return _providerName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[NonTerminal]
[TypeId(0x9E5C0B02)]
[UseTypeName("APLR")]
public class BuffApplicator : BaseApplicator
{
	private UndoRedoDBPtr<BuffApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<BuffApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EBuffBehavior> _behaviorFlags;
	private ExecutableFloatString _lifeTime;
	private UndoRedoAssignableList<DBPtr<EffectBase>> _effect;
	private ExecutableBoolString _startCondition;

	[Description( "StopOnDisable - buff will be dropped when become disabled (in normal state it could be enabled again)" )]
	public EBuffBehavior behaviorFlags { get { return _behaviorFlags.Get(); } set { _behaviorFlags.Set( value ); } }

	[Description( "Life time of buff (in seconds); specify -1 as infinity" )]
	public ExecutableFloatString lifeTime { get { return _lifeTime; } set { _lifeTime.Assign( value ); } }

	[Description( "Visual effect of buff" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<EffectBase>> effect { get { return _effect; } set { _effect.Assign( value ); } }

	[Description( "Проверка на запуск аппликатора (не путать с enabled!)" )]
	public ExecutableBoolString startCondition { get { return _startCondition; } set { _startCondition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BuffApplicator>(owner);
		_behaviorFlags = new UndoRedo<EBuffBehavior>( owner, EBuffBehavior.Zero );
		ExecutableFloatString __lifeTime = new ExecutableFloatString(); // Construct default object for lifeTime
		__lifeTime.sString = "-1.0";
		_lifeTime = new ExecutableFloatString( owner, __lifeTime );
		_effect = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner, typeof( ETeamID ) );
		ExecutableBoolString __startCondition = new ExecutableBoolString(); // Construct default object for startCondition
		__startCondition.sString = "true";
		_startCondition = new ExecutableBoolString( owner, __startCondition );
		___parent.Changed += FireChangedEvent;
		_behaviorFlags.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
		_startCondition.Changed += FireChangedEvent;
	}

	public BuffApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( BuffApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BuffApplicator" );
		behaviorFlags = source.behaviorFlags;
		lifeTime = source.lifeTime;
		effect = source.effect;
		startCondition = source.startCondition;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BuffApplicator source = _source as BuffApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BuffApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BuffApplicator newParent = rawParent == null ? null : rawParent.Get<BuffApplicator>();
		if ( newParent == null && _newParent is BuffApplicator )
			newParent = _newParent as BuffApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_behaviorFlags.SetParent( newParent == null ? null : newParent._behaviorFlags );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_effect.SetParent( newParent == null ? null : newParent._effect );
		_startCondition.SetParent( newParent == null ? null : newParent._startCondition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_behaviorFlags.Reset();
		_lifeTime.Reset();
		_effect.Reset();
		_startCondition.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_behaviorFlags.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			&& _effect.IsDerivedFromParent()
			&& _startCondition.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "behaviorFlags" )
			_behaviorFlags.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "effect" )
			_effect.Reset();
		else if ( fieldName == "startCondition" )
			_startCondition.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "behaviorFlags" )
			return _behaviorFlags.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "effect" )
			return _effect.IsDerivedFromParent();
		if ( fieldName == "startCondition" )
			return _startCondition.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[FactoryImpl("Create", "NWorld::PFApplAbilityUpgrade", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F6C0C40)]
[UseTypeName("APLR")]
public class AbilityUpgradeApplicator : BuffApplicator
{
	private UndoRedoDBPtr<AbilityUpgradeApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AbilityUpgradeApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EAbilityUpgradeMode> _flags;
	private UndoRedo<EAbilityTypeId> _targetAbility;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicators;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _persistentApplicators;
	private ExecutableIntString _applyCount;
	private UndoRedoAssignableList<DBPtr<Ability>> _talents;
	private UndoRedo<EUseMode> _useListAs;

	[Category( "Ability Modification" )]
	[Description( "Extended upgrade properties" )]
	public EAbilityUpgradeMode flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Ability to upgrade (use only with BaseAttack or Ability1 - Ability4)" )]
	public EAbilityTypeId targetAbility { get { return _targetAbility.Get(); } set { _targetAbility.Set( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Applicators to attach" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Persistent applicators to attach" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> persistentApplicators { get { return _persistentApplicators; } set { _persistentApplicators.Assign( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Upgrades counter (0 if infinite)" )]
	public ExecutableIntString applyCount { get { return _applyCount; } set { _applyCount.Assign( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Список улучшаемых талантов" )]
	public libdb.IChangeableList<DBPtr<Ability>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Режим работы со списком" )]
	public EUseMode useListAs { get { return _useListAs.Get(); } set { _useListAs.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AbilityUpgradeApplicator>(owner);
		_flags = new UndoRedo<EAbilityUpgradeMode>( owner, EAbilityUpgradeMode.None );
		_targetAbility = new UndoRedo<EAbilityTypeId>( owner, EAbilityTypeId.BaseAttack );
		_applicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		_persistentApplicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		_applyCount = new ExecutableIntString( owner );
		_talents = new UndoRedoAssignableList<DBPtr<Ability>>( owner );
		_useListAs = new UndoRedo<EUseMode>( owner, EUseMode.ListAsRule );
		___parent.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_targetAbility.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
		_persistentApplicators.Changed += FireChangedEvent;
		_applyCount.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
		_useListAs.Changed += FireChangedEvent;
	}

	public AbilityUpgradeApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AbilityUpgradeApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AbilityUpgradeApplicator" );
		flags = source.flags;
		targetAbility = source.targetAbility;
		applicators = source.applicators;
		persistentApplicators = source.persistentApplicators;
		applyCount = source.applyCount;
		talents = source.talents;
		useListAs = source.useListAs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AbilityUpgradeApplicator source = _source as AbilityUpgradeApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AbilityUpgradeApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AbilityUpgradeApplicator newParent = rawParent == null ? null : rawParent.Get<AbilityUpgradeApplicator>();
		if ( newParent == null && _newParent is AbilityUpgradeApplicator )
			newParent = _newParent as AbilityUpgradeApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_flags.SetParent( newParent == null ? null : newParent._flags );
		_targetAbility.SetParent( newParent == null ? null : newParent._targetAbility );
		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		_persistentApplicators.SetParent( newParent == null ? null : newParent._persistentApplicators );
		_applyCount.SetParent( newParent == null ? null : newParent._applyCount );
		_talents.SetParent( newParent == null ? null : newParent._talents );
		_useListAs.SetParent( newParent == null ? null : newParent._useListAs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_flags.Reset();
		_targetAbility.Reset();
		_applicators.Reset();
		_persistentApplicators.Reset();
		_applyCount.Reset();
		_talents.Reset();
		_useListAs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_flags.IsDerivedFromParent()
			&& _targetAbility.IsDerivedFromParent()
			&& _applicators.IsDerivedFromParent()
			&& _persistentApplicators.IsDerivedFromParent()
			&& _applyCount.IsDerivedFromParent()
			&& _talents.IsDerivedFromParent()
			&& _useListAs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "targetAbility" )
			_targetAbility.Reset();
		else if ( fieldName == "applicators" )
			_applicators.Reset();
		else if ( fieldName == "persistentApplicators" )
			_persistentApplicators.Reset();
		else if ( fieldName == "applyCount" )
			_applyCount.Reset();
		else if ( fieldName == "talents" )
			_talents.Reset();
		else if ( fieldName == "useListAs" )
			_useListAs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "targetAbility" )
			return _targetAbility.IsDerivedFromParent();
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		if ( fieldName == "persistentApplicators" )
			return _persistentApplicators.IsDerivedFromParent();
		if ( fieldName == "applyCount" )
			return _applyCount.IsDerivedFromParent();
		if ( fieldName == "talents" )
			return _talents.IsDerivedFromParent();
		if ( fieldName == "useListAs" )
			return _useListAs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Create", "NWorld::PFApplTechAbilityUpgrade", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x15DC6040)]
[UseTypeName("APLR")]
public class AbilityUpgradeTechApplicator : BaseApplicator
{
	private UndoRedoDBPtr<AbilityUpgradeTechApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AbilityUpgradeTechApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _abilityObjectId;
	private UndoRedo<int> _abilityLastUseStep;

	[HideInOutliner]
	public int abilityObjectId { get { return _abilityObjectId.Get(); } set { _abilityObjectId.Set( value ); } }

	[HideInOutliner]
	public int abilityLastUseStep { get { return _abilityLastUseStep.Get(); } set { _abilityLastUseStep.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AbilityUpgradeTechApplicator>(owner);
		_abilityObjectId = new UndoRedo<int>( owner, 0 );
		_abilityLastUseStep = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_abilityObjectId.Changed += FireChangedEvent;
		_abilityLastUseStep.Changed += FireChangedEvent;
	}

	public AbilityUpgradeTechApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AbilityUpgradeTechApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AbilityUpgradeTechApplicator" );
		abilityObjectId = source.abilityObjectId;
		abilityLastUseStep = source.abilityLastUseStep;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AbilityUpgradeTechApplicator source = _source as AbilityUpgradeTechApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AbilityUpgradeTechApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AbilityUpgradeTechApplicator newParent = rawParent == null ? null : rawParent.Get<AbilityUpgradeTechApplicator>();
		if ( newParent == null && _newParent is AbilityUpgradeTechApplicator )
			newParent = _newParent as AbilityUpgradeTechApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_abilityObjectId.SetParent( newParent == null ? null : newParent._abilityObjectId );
		_abilityLastUseStep.SetParent( newParent == null ? null : newParent._abilityLastUseStep );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_abilityObjectId.Reset();
		_abilityLastUseStep.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_abilityObjectId.IsDerivedFromParent()
			&& _abilityLastUseStep.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "abilityObjectId" )
			_abilityObjectId.Reset();
		else if ( fieldName == "abilityLastUseStep" )
			_abilityLastUseStep.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "abilityObjectId" )
			return _abilityObjectId.IsDerivedFromParent();
		if ( fieldName == "abilityLastUseStep" )
			return _abilityLastUseStep.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAbsorbShieldApplicator", "PFTriggerApplicator.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2B82CC00)]
[UseTypeName("APLR")]
public class AbsorbShieldApplicator : BuffApplicator
{
	private UndoRedoDBPtr<AbsorbShieldApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AbsorbShieldApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _damageToAbsorb;

	public ExecutableFloatString damageToAbsorb { get { return _damageToAbsorb; } set { _damageToAbsorb.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AbsorbShieldApplicator>(owner);
		ExecutableFloatString __damageToAbsorb = new ExecutableFloatString(); // Construct default object for damageToAbsorb
		__damageToAbsorb.sString = "0.0f";
		_damageToAbsorb = new ExecutableFloatString( owner, __damageToAbsorb );
		___parent.Changed += FireChangedEvent;
		_damageToAbsorb.Changed += FireChangedEvent;
	}

	public AbsorbShieldApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AbsorbShieldApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AbsorbShieldApplicator" );
		damageToAbsorb = source.damageToAbsorb;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AbsorbShieldApplicator source = _source as AbsorbShieldApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AbsorbShieldApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AbsorbShieldApplicator newParent = rawParent == null ? null : rawParent.Get<AbsorbShieldApplicator>();
		if ( newParent == null && _newParent is AbsorbShieldApplicator )
			newParent = _newParent as AbsorbShieldApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_damageToAbsorb.SetParent( newParent == null ? null : newParent._damageToAbsorb );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_damageToAbsorb.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_damageToAbsorb.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "damageToAbsorb" )
			_damageToAbsorb.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "damageToAbsorb" )
			return _damageToAbsorb.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplAddApplicatorDuration", "PFApplBuff.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2B82CC80)]
[UseTypeName("APLR")]
public class AddApplicatorDuration : BaseApplicator
{
	private UndoRedoDBPtr<AddApplicatorDuration> ___parent;
	[HideInOutliner]
	public new DBPtr<AddApplicatorDuration> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _durationToAdd;
	private UndoRedoAssignableList<DBPtr<BuffApplicator>> _applicators;
	private UndoRedo<EUpdateDurationFlags> _flags;
	private UndoRedo<string> _nameToCheck;

	public ExecutableFloatString durationToAdd { get { return _durationToAdd; } set { _durationToAdd.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<BuffApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	public EUpdateDurationFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	public string nameToCheck { get { return _nameToCheck.Get(); } set { _nameToCheck.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AddApplicatorDuration>(owner);
		ExecutableFloatString __durationToAdd = new ExecutableFloatString(); // Construct default object for durationToAdd
		__durationToAdd.sString = "-1.0";
		_durationToAdd = new ExecutableFloatString( owner, __durationToAdd );
		_applicators = new UndoRedoAssignableList<DBPtr<BuffApplicator>>( owner );
		_flags = new UndoRedo<EUpdateDurationFlags>( owner, EUpdateDurationFlags.None );
		_nameToCheck = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_durationToAdd.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_nameToCheck.Changed += FireChangedEvent;
	}

	public AddApplicatorDuration()
	{
		Initialize( this );
	}
	private void AssignSelf( AddApplicatorDuration source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AddApplicatorDuration" );
		durationToAdd = source.durationToAdd;
		applicators = source.applicators;
		flags = source.flags;
		nameToCheck = source.nameToCheck;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AddApplicatorDuration source = _source as AddApplicatorDuration;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AddApplicatorDuration" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AddApplicatorDuration newParent = rawParent == null ? null : rawParent.Get<AddApplicatorDuration>();
		if ( newParent == null && _newParent is AddApplicatorDuration )
			newParent = _newParent as AddApplicatorDuration;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_durationToAdd.SetParent( newParent == null ? null : newParent._durationToAdd );
		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_nameToCheck.SetParent( newParent == null ? null : newParent._nameToCheck );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_durationToAdd.Reset();
		_applicators.Reset();
		_flags.Reset();
		_nameToCheck.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_durationToAdd.IsDerivedFromParent()
			&& _applicators.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _nameToCheck.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "durationToAdd" )
			_durationToAdd.Reset();
		else if ( fieldName == "applicators" )
			_applicators.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "nameToCheck" )
			_nameToCheck.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "durationToAdd" )
			return _durationToAdd.IsDerivedFromParent();
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "nameToCheck" )
			return _nameToCheck.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAddNaftaApplicator", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE7764C40)]
[UseTypeName("APLR")]
public class AddNaftaApplicator : BaseApplicator
{
	private UndoRedoDBPtr<AddNaftaApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AddNaftaApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _nafta;
	private UndoRedo<bool> _isFromImpulseBuff;

	[Description( "Nafta to be added to the target unit (negative to remove)" )]
	public ExecutableFloatString nafta { get { return _nafta; } set { _nafta.Assign( value ); } }

	[Description( "Designates whether the source is impulse buff or not" )]
	public bool isFromImpulseBuff { get { return _isFromImpulseBuff.Get(); } set { _isFromImpulseBuff.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AddNaftaApplicator>(owner);
		ExecutableFloatString __nafta = new ExecutableFloatString(); // Construct default object for nafta
		__nafta.sString = "1.0f";
		_nafta = new ExecutableFloatString( owner, __nafta );
		_isFromImpulseBuff = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_nafta.Changed += FireChangedEvent;
		_isFromImpulseBuff.Changed += FireChangedEvent;
	}

	public AddNaftaApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AddNaftaApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AddNaftaApplicator" );
		nafta = source.nafta;
		isFromImpulseBuff = source.isFromImpulseBuff;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AddNaftaApplicator source = _source as AddNaftaApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AddNaftaApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AddNaftaApplicator newParent = rawParent == null ? null : rawParent.Get<AddNaftaApplicator>();
		if ( newParent == null && _newParent is AddNaftaApplicator )
			newParent = _newParent as AddNaftaApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_nafta.SetParent( newParent == null ? null : newParent._nafta );
		_isFromImpulseBuff.SetParent( newParent == null ? null : newParent._isFromImpulseBuff );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_nafta.Reset();
		_isFromImpulseBuff.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_nafta.IsDerivedFromParent()
			&& _isFromImpulseBuff.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "nafta" )
			_nafta.Reset();
		else if ( fieldName == "isFromImpulseBuff" )
			_isFromImpulseBuff.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "nafta" )
			return _nafta.IsDerivedFromParent();
		if ( fieldName == "isFromImpulseBuff" )
			return _isFromImpulseBuff.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("ACTV")]
public class AlternativeActivity : DBResource
{
	private UndoRedoDBPtr<AlternativeActivity> ___parent;
	[HideInOutliner]
	public new DBPtr<AlternativeActivity> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _useRange;
	private UndoRedo<EAbilityFlags> _flags;

	public ExecutableFloatString useRange { get { return _useRange; } set { _useRange.Assign( value ); } }

	public EAbilityFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AlternativeActivity>(owner);
		ExecutableFloatString __useRange = new ExecutableFloatString(); // Construct default object for useRange
		__useRange.sString = "0.0f";
		_useRange = new ExecutableFloatString( owner, __useRange );
		_flags = new UndoRedo<EAbilityFlags>( owner, (EAbilityFlags)0 );
		___parent.Changed += FireChangedEvent;
		_useRange.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
	}

	public AlternativeActivity()
	{
		Initialize( this );
	}
	private void AssignSelf( AlternativeActivity source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AlternativeActivity" );
		useRange = source.useRange;
		flags = source.flags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AlternativeActivity source = _source as AlternativeActivity;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AlternativeActivity" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AlternativeActivity newParent = rawParent == null ? null : rawParent.Get<AlternativeActivity>();
		if ( newParent == null && _newParent is AlternativeActivity )
			newParent = _newParent as AlternativeActivity;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_useRange.SetParent( newParent == null ? null : newParent._useRange );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_useRange.Reset();
		_flags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_useRange.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "useRange" )
			_useRange.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "useRange" )
			return _useRange.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("ALTT")]
public class AlternativeTarget : DBResource
{
	private UndoRedoDBPtr<AlternativeTarget> ___parent;
	[HideInOutliner]
	public new DBPtr<AlternativeTarget> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;
	private UndoRedo<int> _index;
	private UndoRedo<bool> _updateTarget;
	private UndoRedo<bool> _fromMinimap;
	private UndoRedoDBPtr<AlternativeActivity> _alternativeActivity;

	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Alternative target index. Applicators can access it via GetAlternativeTargetIndex()" )]
	public int index { get { return _index.Get(); } set { _index.Set( value ); } }

	[Description( "Update ability target with alternative one if found" )]
	public bool updateTarget { get { return _updateTarget.Get(); } set { _updateTarget.Set( value ); } }

	[Description( "Search such targets only if requested from minimap" )]
	public bool fromMinimap { get { return _fromMinimap.Get(); } set { _fromMinimap.Set( value ); } }

	[Description( "Activity that will be used if alternative target found" )]
	public DBPtr<AlternativeActivity> alternativeActivity { get { return _alternativeActivity.Get(); } set { _alternativeActivity.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AlternativeTarget>(owner);
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_index = new UndoRedo<int>( owner, 0 );
		_updateTarget = new UndoRedo<bool>( owner, true );
		_fromMinimap = new UndoRedo<bool>( owner, false );
		_alternativeActivity = new UndoRedoDBPtr<AlternativeActivity>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_index.Changed += FireChangedEvent;
		_updateTarget.Changed += FireChangedEvent;
		_fromMinimap.Changed += FireChangedEvent;
		_alternativeActivity.Changed += FireChangedEvent;
	}

	public AlternativeTarget()
	{
		Initialize( this );
	}
	private void AssignSelf( AlternativeTarget source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AlternativeTarget" );
		targetSelector = source.targetSelector;
		index = source.index;
		updateTarget = source.updateTarget;
		fromMinimap = source.fromMinimap;
		alternativeActivity = source.alternativeActivity;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AlternativeTarget source = _source as AlternativeTarget;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AlternativeTarget" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AlternativeTarget newParent = rawParent == null ? null : rawParent.Get<AlternativeTarget>();
		if ( newParent == null && _newParent is AlternativeTarget )
			newParent = _newParent as AlternativeTarget;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_index.SetParent( newParent == null ? null : newParent._index );
		_updateTarget.SetParent( newParent == null ? null : newParent._updateTarget );
		_fromMinimap.SetParent( newParent == null ? null : newParent._fromMinimap );
		_alternativeActivity.SetParent( newParent == null ? null : newParent._alternativeActivity );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_index.Reset();
		_updateTarget.Reset();
		_fromMinimap.Reset();
		_alternativeActivity.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _index.IsDerivedFromParent()
			&& _updateTarget.IsDerivedFromParent()
			&& _fromMinimap.IsDerivedFromParent()
			&& _alternativeActivity.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "index" )
			_index.Reset();
		else if ( fieldName == "updateTarget" )
			_updateTarget.Reset();
		else if ( fieldName == "fromMinimap" )
			_fromMinimap.Reset();
		else if ( fieldName == "alternativeActivity" )
			_alternativeActivity.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "index" )
			return _index.IsDerivedFromParent();
		if ( fieldName == "updateTarget" )
			return _updateTarget.IsDerivedFromParent();
		if ( fieldName == "fromMinimap" )
			return _fromMinimap.IsDerivedFromParent();
		if ( fieldName == "alternativeActivity" )
			return _alternativeActivity.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFBaseApplicator", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE794DC40)]
[UseTypeName("ADBIC")]
public class ApplicatorNameOverrider : BaseApplicator
{
	private UndoRedoDBPtr<ApplicatorNameOverrider> ___parent;
	[HideInOutliner]
	public new DBPtr<ApplicatorNameOverrider> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseApplicator> _applicator;

	public DBPtr<BaseApplicator> applicator { get { return _applicator.Get(); } set { _applicator.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ApplicatorNameOverrider>(owner);
		_applicator = new UndoRedoDBPtr<BaseApplicator>( owner );
		___parent.Changed += FireChangedEvent;
		_applicator.Changed += FireChangedEvent;
	}

	public ApplicatorNameOverrider()
	{
		Initialize( this );
	}
	private void AssignSelf( ApplicatorNameOverrider source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ApplicatorNameOverrider" );
		applicator = source.applicator;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ApplicatorNameOverrider source = _source as ApplicatorNameOverrider;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ApplicatorNameOverrider" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ApplicatorNameOverrider newParent = rawParent == null ? null : rawParent.Get<ApplicatorNameOverrider>();
		if ( newParent == null && _newParent is ApplicatorNameOverrider )
			newParent = _newParent as ApplicatorNameOverrider;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_applicator.SetParent( newParent == null ? null : newParent._applicator );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_applicator.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_applicator.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "applicator" )
			_applicator.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "applicator" )
			return _applicator.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Create", "NWorld::PFTargetSelector", "NWorld::PFWorld* world")]
[TypeId(0x9E676B40)]
[UseTypeName("TGSL")]
public class TargetSelector : DBResource
{
	private UndoRedoDBPtr<TargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<TargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TargetSelector>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public TargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( TargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TargetSelector" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TargetSelector source = _source as TargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TargetSelector newParent = rawParent == null ? null : rawParent.Get<TargetSelector>();
		if ( newParent == null && _newParent is TargetSelector )
			newParent = _newParent as TargetSelector;
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

[TypeId(0x0F724340)]
[UseTypeName("APLS")]
public class ApplicatorsList : DBResource
{
	private UndoRedoDBPtr<ApplicatorsList> ___parent;
	[HideInOutliner]
	public new DBPtr<ApplicatorsList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicators;
	private UndoRedoAssignableList<DBPtr<ApplicatorsList>> _applicatorLists;

	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<ApplicatorsList>> applicatorLists { get { return _applicatorLists; } set { _applicatorLists.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ApplicatorsList>(owner);
		_applicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		_applicatorLists = new UndoRedoAssignableList<DBPtr<ApplicatorsList>>( owner );
		___parent.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
		_applicatorLists.Changed += FireChangedEvent;
	}

	public ApplicatorsList()
	{
		Initialize( this );
	}
	private void AssignSelf( ApplicatorsList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ApplicatorsList" );
		applicators = source.applicators;
		applicatorLists = source.applicatorLists;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ApplicatorsList source = _source as ApplicatorsList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ApplicatorsList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ApplicatorsList newParent = rawParent == null ? null : rawParent.Get<ApplicatorsList>();
		if ( newParent == null && _newParent is ApplicatorsList )
			newParent = _newParent as ApplicatorsList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		_applicatorLists.SetParent( newParent == null ? null : newParent._applicatorLists );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_applicators.Reset();
		_applicatorLists.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_applicators.IsDerivedFromParent()
			&& _applicatorLists.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "applicators" )
			_applicators.Reset();
		else if ( fieldName == "applicatorLists" )
			_applicatorLists.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		if ( fieldName == "applicatorLists" )
			return _applicatorLists.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9E6C82C0)]
[UseTypeName("TGSL")]
public class MultipleTargetSelector : TargetSelector
{
	private UndoRedoDBPtr<MultipleTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<MultipleTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ETargetSelectorMode> _mode;
	private UndoRedo<ETargetSelectorFlags> _flags;

	[Description( "Selector working mode" )]
	public ETargetSelectorMode mode { get { return _mode.Get(); } set { _mode.Set( value ); } }

	[Description( "Target selector flags" )]
	public ETargetSelectorFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MultipleTargetSelector>(owner);
		_mode = new UndoRedo<ETargetSelectorMode>( owner, ETargetSelectorMode.Normal );
		_flags = new UndoRedo<ETargetSelectorFlags>( owner, ETargetSelectorFlags.Zero );
		___parent.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
	}

	public MultipleTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( MultipleTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MultipleTargetSelector" );
		mode = source.mode;
		flags = source.flags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MultipleTargetSelector source = _source as MultipleTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MultipleTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MultipleTargetSelector newParent = rawParent == null ? null : rawParent.Get<MultipleTargetSelector>();
		if ( newParent == null && _newParent is MultipleTargetSelector )
			newParent = _newParent as MultipleTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_mode.SetParent( newParent == null ? null : newParent._mode );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_mode.Reset();
		_flags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_mode.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "mode" )
			_mode.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "mode" )
			return _mode.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9E7192C0)]
[UseTypeName("TGSL")]
public class MultipleTargetSelectorFiltered : MultipleTargetSelector
{
	private UndoRedoDBPtr<MultipleTargetSelectorFiltered> ___parent;
	[HideInOutliner]
	public new DBPtr<MultipleTargetSelectorFiltered> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ESpellTarget> _targetFilter;

	[Description( "Flags that specify targets of this spell. Specify 0 if you want to apply this spell on sender." )]
	public ESpellTarget targetFilter { get { return _targetFilter.Get(); } set { _targetFilter.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MultipleTargetSelectorFiltered>(owner);
		_targetFilter = new UndoRedo<ESpellTarget>( owner, ESpellTarget.AllEnemies | ESpellTarget.VisibleTargetsOnly );
		___parent.Changed += FireChangedEvent;
		_targetFilter.Changed += FireChangedEvent;
	}

	public MultipleTargetSelectorFiltered()
	{
		Initialize( this );
	}
	private void AssignSelf( MultipleTargetSelectorFiltered source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MultipleTargetSelectorFiltered" );
		targetFilter = source.targetFilter;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MultipleTargetSelectorFiltered source = _source as MultipleTargetSelectorFiltered;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MultipleTargetSelectorFiltered" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MultipleTargetSelectorFiltered newParent = rawParent == null ? null : rawParent.Get<MultipleTargetSelectorFiltered>();
		if ( newParent == null && _newParent is MultipleTargetSelectorFiltered )
			newParent = _newParent as MultipleTargetSelectorFiltered;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetFilter.SetParent( newParent == null ? null : newParent._targetFilter );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetFilter.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetFilter.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetFilter" )
			_targetFilter.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetFilter" )
			return _targetFilter.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplAttackTarget", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E678B02)]
[UseTypeName("APLR")]
public class AttackTargetApplicator : BuffApplicator
{
	private UndoRedoDBPtr<AttackTargetApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AttackTargetApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _attackTarget;
	private UndoRedo<int> _attackCount;
	private UndoRedo<EAttackTargetEvadeAction> _evadeAction;
	private UndoRedo<bool> _ignoreVisibility;

	[Description( "Target to attack" )]
	public EApplicatorApplyTarget attackTarget { get { return _attackTarget.Get(); } set { _attackTarget.Set( value ); } }

	[Description( "Number attacks" )]
	public int attackCount { get { return _attackCount.Get(); } set { _attackCount.Set( value ); } }

	[Description( "What to do when attack is evaded" )]
	public EAttackTargetEvadeAction evadeAction { get { return _evadeAction.Get(); } set { _evadeAction.Set( value ); } }

	[Description( "Allow attack invisible (concealed by warfog too) targets" )]
	public bool ignoreVisibility { get { return _ignoreVisibility.Get(); } set { _ignoreVisibility.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AttackTargetApplicator>(owner);
		_attackTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_attackCount = new UndoRedo<int>( owner, -1 );
		_evadeAction = new UndoRedo<EAttackTargetEvadeAction>( owner, EAttackTargetEvadeAction.StopAsFailed );
		_ignoreVisibility = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_attackTarget.Changed += FireChangedEvent;
		_attackCount.Changed += FireChangedEvent;
		_evadeAction.Changed += FireChangedEvent;
		_ignoreVisibility.Changed += FireChangedEvent;
	}

	public AttackTargetApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AttackTargetApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AttackTargetApplicator" );
		attackTarget = source.attackTarget;
		attackCount = source.attackCount;
		evadeAction = source.evadeAction;
		ignoreVisibility = source.ignoreVisibility;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AttackTargetApplicator source = _source as AttackTargetApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AttackTargetApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AttackTargetApplicator newParent = rawParent == null ? null : rawParent.Get<AttackTargetApplicator>();
		if ( newParent == null && _newParent is AttackTargetApplicator )
			newParent = _newParent as AttackTargetApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_attackTarget.SetParent( newParent == null ? null : newParent._attackTarget );
		_attackCount.SetParent( newParent == null ? null : newParent._attackCount );
		_evadeAction.SetParent( newParent == null ? null : newParent._evadeAction );
		_ignoreVisibility.SetParent( newParent == null ? null : newParent._ignoreVisibility );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_attackTarget.Reset();
		_attackCount.Reset();
		_evadeAction.Reset();
		_ignoreVisibility.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_attackTarget.IsDerivedFromParent()
			&& _attackCount.IsDerivedFromParent()
			&& _evadeAction.IsDerivedFromParent()
			&& _ignoreVisibility.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "attackTarget" )
			_attackTarget.Reset();
		else if ( fieldName == "attackCount" )
			_attackCount.Reset();
		else if ( fieldName == "evadeAction" )
			_evadeAction.Reset();
		else if ( fieldName == "ignoreVisibility" )
			_ignoreVisibility.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "attackTarget" )
			return _attackTarget.IsDerivedFromParent();
		if ( fieldName == "attackCount" )
			return _attackCount.IsDerivedFromParent();
		if ( fieldName == "evadeAction" )
			return _evadeAction.IsDerivedFromParent();
		if ( fieldName == "ignoreVisibility" )
			return _ignoreVisibility.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplAttract", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F61F480)]
[UseTypeName("APLR")]
public class AttractApplicator : BaseApplicator
{
	private UndoRedoDBPtr<AttractApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AttractApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _distance;

	[Category( "Attract" )]
	public float distance { get { return _distance.Get(); } set { _distance.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AttractApplicator>(owner);
		_distance = new UndoRedo<float>( owner, 10.0f );
		___parent.Changed += FireChangedEvent;
		_distance.Changed += FireChangedEvent;
	}

	public AttractApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AttractApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AttractApplicator" );
		distance = source.distance;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AttractApplicator source = _source as AttractApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AttractApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AttractApplicator newParent = rawParent == null ? null : rawParent.Get<AttractApplicator>();
		if ( newParent == null && _newParent is AttractApplicator )
			newParent = _newParent as AttractApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_distance.SetParent( newParent == null ? null : newParent._distance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_distance.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_distance.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "distance" )
			_distance.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "distance" )
			return _distance.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFApplAura", "PFApplAura.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B04)]
[UseTypeName("APLR")]
public class AuraApplicator : BuffApplicator
{
	private UndoRedoDBPtr<AuraApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AuraApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;
	private ExecutableFloatString _range;
	private UndoRedo<ESpellTarget> _targets;
	private UndoRedo<EAuraVisualType> _type;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicators;

	[Description( "Targets selector" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Category( "Aura" )]
	[Description( "Affecting range (in meters)" )]
	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	[Category( "Aura" )]
	[Description( "Flags to specify targets of the aura. The same as targetType field in Spell" )]
	public ESpellTarget targets { get { return _targets.Get(); } set { _targets.Set( value ); } }

	[Category( "Aura" )]
	[Description( "Тип ауры: дружественная или враждебная. Используется для визуального эффекта на кастующего." )]
	public EAuraVisualType type { get { return _type.Get(); } set { _type.Set( value ); } }

	[Category( "Applicators" )]
	[Description( "List of aura applicators" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AuraApplicator>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		_targets = new UndoRedo<ESpellTarget>( owner, ESpellTarget.VulnerableTargetsOnly | ESpellTarget.All );
		_type = new UndoRedo<EAuraVisualType>( owner, EAuraVisualType.None );
		_applicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_targets.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
	}

	public AuraApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AuraApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AuraApplicator" );
		targetSelector = source.targetSelector;
		range = source.range;
		targets = source.targets;
		type = source.type;
		applicators = source.applicators;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AuraApplicator source = _source as AuraApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AuraApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AuraApplicator newParent = rawParent == null ? null : rawParent.Get<AuraApplicator>();
		if ( newParent == null && _newParent is AuraApplicator )
			newParent = _newParent as AuraApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_range.SetParent( newParent == null ? null : newParent._range );
		_targets.SetParent( newParent == null ? null : newParent._targets );
		_type.SetParent( newParent == null ? null : newParent._type );
		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_range.Reset();
		_targets.Reset();
		_type.Reset();
		_applicators.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& _targets.IsDerivedFromParent()
			&& _type.IsDerivedFromParent()
			&& _applicators.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "targets" )
			_targets.Reset();
		else if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "applicators" )
			_applicators.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "targets" )
			return _targets.IsDerivedFromParent();
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplAbilityEnd", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0B75FB81)]
[UseTypeName("APLR")]
public class AbilityEndApplicator : BaseApplicator
{
	private UndoRedoDBPtr<AbilityEndApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AbilityEndApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _cancelApplicators;

	[Description( "Cancel ability applicators applied to sender" )]
	public bool cancelApplicators { get { return _cancelApplicators.Get(); } set { _cancelApplicators.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AbilityEndApplicator>(owner);
		_cancelApplicators = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_cancelApplicators.Changed += FireChangedEvent;
	}

	public AbilityEndApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AbilityEndApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AbilityEndApplicator" );
		cancelApplicators = source.cancelApplicators;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AbilityEndApplicator source = _source as AbilityEndApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AbilityEndApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AbilityEndApplicator newParent = rawParent == null ? null : rawParent.Get<AbilityEndApplicator>();
		if ( newParent == null && _newParent is AbilityEndApplicator )
			newParent = _newParent as AbilityEndApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_cancelApplicators.SetParent( newParent == null ? null : newParent._cancelApplicators );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_cancelApplicators.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_cancelApplicators.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "cancelApplicators" )
			_cancelApplicators.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "cancelApplicators" )
			return _cancelApplicators.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(7)]
[IndexField("caption")]
[TypeId(0x2C5C0B01)]
[UseTypeName("ABLT")]
public class Ability : Spell
{
	private UndoRedoDBPtr<Ability> ___parent;
	[HideInOutliner]
	public new DBPtr<Ability> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _caption;
	private TextRef _name;
	private TextRef _description;
	private TextRef _compiledDescriptionA;
	private TextRef _compiledDescriptionB;
	private TextRef _shortDescription;
	private TextRef _commonDescription;
	private UndoRedoAssignableList<DBPtr<CastLimitation>> _castLimitations;
	private UndoRedoDBPtr<Texture> _image;
	private UndoRedoDBPtr<Texture> _imageSecondState;
	private UndoRedo<EAbilityAOEVisual> _aoeType;
	private ExecutableFloatString _aoeSize;
	private UndoRedoDBPtr<AOEMaterial> _aoeMaterial;
	private UndoRedo<float> _aoeHeight;
	private UndoRedoDBPtr<AOEMaterial> _useRangeMaterial;
	private UndoRedo<ETraceMode> _aoePassabilityCheckMode;
	private UndoRedo<bool> _aoeDisplayOnMinimap;
	private UndoRedo<EAbilityType> _type;
	private ExecutableFloatString _cooldownTime;
	private ExecutableFloatString _cooldownTimeSecondState;
	private ExecutableFloatString _manaCost;
	private UndoRedo<bool> _activeCustomTrigger;
	private ExecutableFloatString _useRange;
	private UndoRedo<float> _minUseRangeCorrection;
	private ExecutableFloatString _castAllowRange;
	private ExecutableBoolString _allowChase;
	private UndoRedoDBPtr<UnitConstantsContainer> _constants;
	private UndoRedoAssignableList<DBPtr<ConditionFormula>> _conditionFormulas;
	private UndoRedo<bool> _isUnitFreeAfterCast;
	private UndoRedo<EAbilityFlags> _flags;
	private UndoRedo<ESpellTarget> _targetType;
	private UndoRedo<bool> _requireLineOfSight;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _passiveApplicators;
	private UndoRedoDBPtr<SingleTargetSelector> _autoTargetSelector;
	private UndoRedoDBPtr<MicroAI> _microAI;
	private UndoRedo<string> _node;
	private UndoRedo<string> _marker;
	private UndoRedo<float> _warFogRemoveTime;
	private UndoRedo<float> _warFogRemoveRadius;
	private UndoRedoAssignableList<DBPtr<AlternativeTarget>> _alternativeTargets;

	[Category( "Description" )]
	[Custom("Social")]
	[Description( "Caption of ability" )]
	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	[Category( "Description" )]
	[Custom("Social")]
	[Description( "Name of ability/artifact/glyph" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Category( "Description" )]
	[Custom("Social")]
	[Description( "Description of ability/artifact/glyph" )]
	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	[Browsable( false )]
	[Category( "Description" )]
	[Custom("Social")]
	[Description( "Description of ability/artifact/glyph" )]
	public TextRef compiledDescriptionA { get { return _compiledDescriptionA; } set { _compiledDescriptionA.Assign( value ); } }

	[Browsable( false )]
	[Category( "Description" )]
	[Custom("Social")]
	[Description( "Description of ability/artifact/glyph" )]
	public TextRef compiledDescriptionB { get { return _compiledDescriptionB; } set { _compiledDescriptionB.Assign( value ); } }

	[Category( "Description" )]
	[Description( "Short description of ability/artifact/glyph" )]
	public TextRef shortDescription { get { return _shortDescription; } set { _shortDescription.Assign( value ); } }

	[Description( "Common description part that can be substituted as $(commonDescription)" )]
	public TextRef commonDescription { get { return _commonDescription; } set { _commonDescription.Assign( value ); } }

	[Category( "Description" )]
	[Description( "List of possible cast limitations" )]
	public libdb.IChangeableList<DBPtr<CastLimitation>> castLimitations { get { return _castLimitations; } set { _castLimitations.Assign( value ); } }

	[Category( "UI" )]
	[Custom("Social")]
	[Description( "UI texture that will be shown in action bar (and status bar)" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	[Category( "UI" )]
	[Description( "UI texture that will be shown in action bar (and status bar) when ability is switched off." )]
	public DBPtr<Texture> imageSecondState { get { return _imageSecondState.Get(); } set { _imageSecondState.Set( value ); } }

	[Category( "UI" )]
	[Description( "Target zone visual shape." )]
	public EAbilityAOEVisual aoeType { get { return _aoeType.Get(); } set { _aoeType.Set( value ); } }

	[Category( "UI" )]
	[Description( "Target zone size, interpreted differently. For DISK - radius in meters. For CONE - half of the angle in degrees. For CORRIDOR - the width in meters." )]
	public ExecutableFloatString aoeSize { get { return _aoeSize; } set { _aoeSize.Assign( value ); } }

	[Category( "UI" )]
	[Description( "Target zone material." )]
	public DBPtr<AOEMaterial> aoeMaterial { get { return _aoeMaterial.Get(); } set { _aoeMaterial.Set( value ); } }

	[Category( "UI" )]
	[Description( "Target zone height." )]
	public float aoeHeight { get { return _aoeHeight.Get(); } set { _aoeHeight.Set( value ); } }

	[Category( "UI" )]
	[Description( "Target zone range material" )]
	public DBPtr<AOEMaterial> useRangeMaterial { get { return _useRangeMaterial.Get(); } set { _useRangeMaterial.Set( value ); } }

	[Category( "UI" )]
	[Description( "Target zone passability check mode for corridor AOE. 0 (zero) means no check." )]
	public ETraceMode aoePassabilityCheckMode { get { return _aoePassabilityCheckMode.Get(); } set { _aoePassabilityCheckMode.Set( value ); } }

	[Category( "UI" )]
	[Description( "Отображать ли радиус действия на мини-карте" )]
	public bool aoeDisplayOnMinimap { get { return _aoeDisplayOnMinimap.Get(); } set { _aoeDisplayOnMinimap.Set( value ); } }

	[Category( "Logic" )]
	[Custom("Social")]
	[Description( "Type of ability. Don't use Autocastable." )]
	public EAbilityType type { get { return _type.Get(); } set { _type.Set( value ); } }

	[Category( "Logic" )]
	[Custom("Social")]
	[Description( "Cooldown time of ability. You can use only mXXX in formulas (or r(x,y,z,w) function). [Formula update: once]" )]
	public ExecutableFloatString cooldownTime { get { return _cooldownTime; } set { _cooldownTime.Assign( value ); } }

	[Category( "Logic" )]
	[Description( "Cooldown time of ability for a second state. You can use only mXXX in formulas (or r(x,y,z,w) function). [Formula update: once]" )]
	public ExecutableFloatString cooldownTimeSecondState { get { return _cooldownTimeSecondState; } set { _cooldownTimeSecondState.Assign( value ); } }

	[Category( "Logic" )]
	[Custom("Social")]
	[Description( "Mana cost of ability. You can use only mXXX in formulas (or r(x,y,z,w) function). [Formula update: once]" )]
	public ExecutableFloatString manaCost { get { return _manaCost; } set { _manaCost.Assign( value ); } }

	[Category( "Logic" )]
	[Description( "for TriggerAbilitiesFilter" )]
	public bool activeCustomTrigger { get { return _activeCustomTrigger.Get(); } set { _activeCustomTrigger.Set( value ); } }

	[Category( "Logic" )]
	[Description( "Using range of ability (in meters)" )]
	public ExecutableFloatString useRange { get { return _useRange; } set { _useRange.Assign( value ); } }

	[Category( "Logic" )]
	[Description( "min range to witch ability range is stretched when its less than minUseRangeCorrection(in meters)" )]
	public float minUseRangeCorrection { get { return _minUseRangeCorrection.Get(); } set { _minUseRangeCorrection.Set( value ); } }

	[Description( "Расстояние до цели на котором абилка сработает (случай ченнелинга). Если <= 0, то будет считаться по умолчанию (см. настройку channelingAbilityRangeMultiplier)" )]
	public ExecutableFloatString castAllowRange { get { return _castAllowRange; } set { _castAllowRange.Assign( value ); } }

	[Description( "Allow or disallow chasing ability's target (currently attack ability only)" )]
	public ExecutableBoolString allowChase { get { return _allowChase; } set { _allowChase.Assign( value ); } }

	[Category( "Logic" )]
	[Custom("Social")]
	public DBPtr<UnitConstantsContainer> constants { get { return _constants.Get(); } set { _constants.Set( value ); } }

	[Category( "Logic" )]
	[Custom("Social")]
	public libdb.IChangeableList<DBPtr<ConditionFormula>> conditionFormulas { get { return _conditionFormulas; } set { _conditionFormulas.Assign( value ); } }

	[Category( "Logic" )]
	[Description( "If true then unit can do anything after workTime, if false then after program(applicators) end" )]
	public bool isUnitFreeAfterCast { get { return _isUnitFreeAfterCast.Get(); } set { _isUnitFreeAfterCast.Set( value ); } }

	[Category( "Logic" )]
	[Custom("Social")]
	public EAbilityFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[Category( "Targets" )]
	[Custom("Social")]
	[Description( "Flags that specify targets of this spell. Specify 0 if you want to apply this spell on sender." )]
	public ESpellTarget targetType { get { return _targetType.Get(); } set { _targetType.Set( value ); } }

	[Category( "Targets" )]
	[Description( "Describes if direct line of side is needed to target unit" )]
	public bool requireLineOfSight { get { return _requireLineOfSight.Get(); } set { _requireLineOfSight.Set( value ); } }

	[Category( "Applicators" )]
	[Custom("Social")]
	[Description( "List of applicators that will be applied to the owner of the spell then attach it to owner." )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> passiveApplicators { get { return _passiveApplicators; } set { _passiveApplicators.Assign( value ); } }

	[Category( "Targets" )]
	[Description( "Target selector использующийся для выбора дефолтовой цели" )]
	public DBPtr<SingleTargetSelector> autoTargetSelector { get { return _autoTargetSelector.Get(); } set { _autoTargetSelector.Set( value ); } }

	[Category( "Targets" )]
	[Description( "Микро ИИ данной абилки. Используется в крипах или в ИИ-героях" )]
	public DBPtr<MicroAI> microAI { get { return _microAI.Get(); } set { _microAI.Set( value ); } }

	[Category( "Animations" )]
	public string node { get { return _node.Get(); } set { _node.Set( value ); } }

	[Category( "Animations" )]
	public string marker { get { return _marker.Get(); } set { _marker.Set( value ); } }

	[Category( "WarFog" )]
	[Description( "Defines time for removing WarFog around attacker after dispatch delivery to target (seconds)." )]
	public float warFogRemoveTime { get { return _warFogRemoveTime.Get(); } set { _warFogRemoveTime.Set( value ); } }

	[Category( "WarFog" )]
	[Description( "Defines radius for removing WarFog around attacker after dispatch delivery to target (meters)." )]
	public float warFogRemoveRadius { get { return _warFogRemoveRadius.Get(); } set { _warFogRemoveRadius.Set( value ); } }

	public libdb.IChangeableList<DBPtr<AlternativeTarget>> alternativeTargets { get { return _alternativeTargets; } set { _alternativeTargets.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Ability>(owner);
		_caption = new UndoRedo<string>( owner, string.Empty );
		_name = new TextRef( owner, new TextRef() );
		_description = new TextRef( owner, new TextRef() );
		_compiledDescriptionA = new TextRef( owner, new TextRef() );
		_compiledDescriptionB = new TextRef( owner, new TextRef() );
		_shortDescription = new TextRef( owner, new TextRef() );
		_commonDescription = new TextRef( owner, new TextRef() );
		_castLimitations = new UndoRedoAssignableList<DBPtr<CastLimitation>>( owner );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_imageSecondState = new UndoRedoDBPtr<Texture>( owner );
		_aoeType = new UndoRedo<EAbilityAOEVisual>( owner, EAbilityAOEVisual.None );
		ExecutableFloatString __aoeSize = new ExecutableFloatString(); // Construct default object for aoeSize
		__aoeSize.sString = "0.0f";
		_aoeSize = new ExecutableFloatString( owner, __aoeSize );
		_aoeMaterial = new UndoRedoDBPtr<AOEMaterial>( owner );
		_aoeHeight = new UndoRedo<float>( owner, 0.0f );
		_useRangeMaterial = new UndoRedoDBPtr<AOEMaterial>( owner );
		_aoePassabilityCheckMode = new UndoRedo<ETraceMode>( owner, (ETraceMode)0 );
		_aoeDisplayOnMinimap = new UndoRedo<bool>( owner, false );
		_type = new UndoRedo<EAbilityType>( owner, EAbilityType.Passive );
		ExecutableFloatString __cooldownTime = new ExecutableFloatString(); // Construct default object for cooldownTime
		__cooldownTime.sString = "0.0f";
		_cooldownTime = new ExecutableFloatString( owner, __cooldownTime );
		ExecutableFloatString __cooldownTimeSecondState = new ExecutableFloatString(); // Construct default object for cooldownTimeSecondState
		__cooldownTimeSecondState.sString = "0.0f";
		_cooldownTimeSecondState = new ExecutableFloatString( owner, __cooldownTimeSecondState );
		ExecutableFloatString __manaCost = new ExecutableFloatString(); // Construct default object for manaCost
		__manaCost.sString = "0.0f";
		_manaCost = new ExecutableFloatString( owner, __manaCost );
		_activeCustomTrigger = new UndoRedo<bool>( owner, true );
		ExecutableFloatString __useRange = new ExecutableFloatString(); // Construct default object for useRange
		__useRange.sString = "0.0f";
		_useRange = new ExecutableFloatString( owner, __useRange );
		_minUseRangeCorrection = new UndoRedo<float>( owner, 0.0f );
		ExecutableFloatString __castAllowRange = new ExecutableFloatString(); // Construct default object for castAllowRange
		__castAllowRange.sString = "0.0f";
		_castAllowRange = new ExecutableFloatString( owner, __castAllowRange );
		ExecutableBoolString __allowChase = new ExecutableBoolString(); // Construct default object for allowChase
		__allowChase.sString = "true";
		_allowChase = new ExecutableBoolString( owner, __allowChase );
		_constants = new UndoRedoDBPtr<UnitConstantsContainer>( owner );
		_conditionFormulas = new UndoRedoAssignableList<DBPtr<ConditionFormula>>( owner );
		_isUnitFreeAfterCast = new UndoRedo<bool>( owner, true );
		_flags = new UndoRedo<EAbilityFlags>( owner, EAbilityFlags.FocusOnTarget );
		_targetType = new UndoRedo<ESpellTarget>( owner, ESpellTarget.VisibleTargetsOnly | ESpellTarget.All );
		_requireLineOfSight = new UndoRedo<bool>( owner, true );
		_passiveApplicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		_autoTargetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_microAI = new UndoRedoDBPtr<MicroAI>( owner );
		_node = new UndoRedo<string>( owner, string.Empty );
		_marker = new UndoRedo<string>( owner, string.Empty );
		_warFogRemoveTime = new UndoRedo<float>( owner, 0.0f );
		_warFogRemoveRadius = new UndoRedo<float>( owner, 0.0f );
		_alternativeTargets = new UndoRedoAssignableList<DBPtr<AlternativeTarget>>( owner );
		___parent.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_compiledDescriptionA.Changed += FireChangedEvent;
		_compiledDescriptionB.Changed += FireChangedEvent;
		_shortDescription.Changed += FireChangedEvent;
		_commonDescription.Changed += FireChangedEvent;
		_castLimitations.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_imageSecondState.Changed += FireChangedEvent;
		_aoeType.Changed += FireChangedEvent;
		_aoeSize.Changed += FireChangedEvent;
		_aoeMaterial.Changed += FireChangedEvent;
		_aoeHeight.Changed += FireChangedEvent;
		_useRangeMaterial.Changed += FireChangedEvent;
		_aoePassabilityCheckMode.Changed += FireChangedEvent;
		_aoeDisplayOnMinimap.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_cooldownTime.Changed += FireChangedEvent;
		_cooldownTimeSecondState.Changed += FireChangedEvent;
		_manaCost.Changed += FireChangedEvent;
		_activeCustomTrigger.Changed += FireChangedEvent;
		_useRange.Changed += FireChangedEvent;
		_minUseRangeCorrection.Changed += FireChangedEvent;
		_castAllowRange.Changed += FireChangedEvent;
		_allowChase.Changed += FireChangedEvent;
		_constants.Changed += FireChangedEvent;
		_conditionFormulas.Changed += FireChangedEvent;
		_isUnitFreeAfterCast.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_targetType.Changed += FireChangedEvent;
		_requireLineOfSight.Changed += FireChangedEvent;
		_passiveApplicators.Changed += FireChangedEvent;
		_autoTargetSelector.Changed += FireChangedEvent;
		_microAI.Changed += FireChangedEvent;
		_node.Changed += FireChangedEvent;
		_marker.Changed += FireChangedEvent;
		_warFogRemoveTime.Changed += FireChangedEvent;
		_warFogRemoveRadius.Changed += FireChangedEvent;
		_alternativeTargets.Changed += FireChangedEvent;
	}

	public Ability()
	{
		Initialize( this );
	}
	private void AssignSelf( Ability source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Ability" );
		caption = source.caption;
		name = source.name;
		description = source.description;
		compiledDescriptionA = source.compiledDescriptionA;
		compiledDescriptionB = source.compiledDescriptionB;
		shortDescription = source.shortDescription;
		commonDescription = source.commonDescription;
		castLimitations = source.castLimitations;
		image = source.image;
		imageSecondState = source.imageSecondState;
		aoeType = source.aoeType;
		aoeSize = source.aoeSize;
		aoeMaterial = source.aoeMaterial;
		aoeHeight = source.aoeHeight;
		useRangeMaterial = source.useRangeMaterial;
		aoePassabilityCheckMode = source.aoePassabilityCheckMode;
		aoeDisplayOnMinimap = source.aoeDisplayOnMinimap;
		type = source.type;
		cooldownTime = source.cooldownTime;
		cooldownTimeSecondState = source.cooldownTimeSecondState;
		manaCost = source.manaCost;
		activeCustomTrigger = source.activeCustomTrigger;
		useRange = source.useRange;
		minUseRangeCorrection = source.minUseRangeCorrection;
		castAllowRange = source.castAllowRange;
		allowChase = source.allowChase;
		constants = source.constants;
		conditionFormulas = source.conditionFormulas;
		isUnitFreeAfterCast = source.isUnitFreeAfterCast;
		flags = source.flags;
		targetType = source.targetType;
		requireLineOfSight = source.requireLineOfSight;
		passiveApplicators = source.passiveApplicators;
		autoTargetSelector = source.autoTargetSelector;
		microAI = source.microAI;
		node = source.node;
		marker = source.marker;
		warFogRemoveTime = source.warFogRemoveTime;
		warFogRemoveRadius = source.warFogRemoveRadius;
		alternativeTargets = source.alternativeTargets;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Ability source = _source as Ability;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Ability" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Ability newParent = rawParent == null ? null : rawParent.Get<Ability>();
		if ( newParent == null && _newParent is Ability )
			newParent = _newParent as Ability;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_caption.SetParent( newParent == null ? null : newParent._caption );
		_name.SetParent( newParent == null ? null : newParent._name );
		_description.SetParent( newParent == null ? null : newParent._description );
		_compiledDescriptionA.SetParent( newParent == null ? null : newParent._compiledDescriptionA );
		_compiledDescriptionB.SetParent( newParent == null ? null : newParent._compiledDescriptionB );
		_shortDescription.SetParent( newParent == null ? null : newParent._shortDescription );
		_commonDescription.SetParent( newParent == null ? null : newParent._commonDescription );
		_castLimitations.SetParent( newParent == null ? null : newParent._castLimitations );
		_image.SetParent( newParent == null ? null : newParent._image );
		_imageSecondState.SetParent( newParent == null ? null : newParent._imageSecondState );
		_aoeType.SetParent( newParent == null ? null : newParent._aoeType );
		_aoeSize.SetParent( newParent == null ? null : newParent._aoeSize );
		_aoeMaterial.SetParent( newParent == null ? null : newParent._aoeMaterial );
		_aoeHeight.SetParent( newParent == null ? null : newParent._aoeHeight );
		_useRangeMaterial.SetParent( newParent == null ? null : newParent._useRangeMaterial );
		_aoePassabilityCheckMode.SetParent( newParent == null ? null : newParent._aoePassabilityCheckMode );
		_aoeDisplayOnMinimap.SetParent( newParent == null ? null : newParent._aoeDisplayOnMinimap );
		_type.SetParent( newParent == null ? null : newParent._type );
		_cooldownTime.SetParent( newParent == null ? null : newParent._cooldownTime );
		_cooldownTimeSecondState.SetParent( newParent == null ? null : newParent._cooldownTimeSecondState );
		_manaCost.SetParent( newParent == null ? null : newParent._manaCost );
		_activeCustomTrigger.SetParent( newParent == null ? null : newParent._activeCustomTrigger );
		_useRange.SetParent( newParent == null ? null : newParent._useRange );
		_minUseRangeCorrection.SetParent( newParent == null ? null : newParent._minUseRangeCorrection );
		_castAllowRange.SetParent( newParent == null ? null : newParent._castAllowRange );
		_allowChase.SetParent( newParent == null ? null : newParent._allowChase );
		_constants.SetParent( newParent == null ? null : newParent._constants );
		_conditionFormulas.SetParent( newParent == null ? null : newParent._conditionFormulas );
		_isUnitFreeAfterCast.SetParent( newParent == null ? null : newParent._isUnitFreeAfterCast );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_targetType.SetParent( newParent == null ? null : newParent._targetType );
		_requireLineOfSight.SetParent( newParent == null ? null : newParent._requireLineOfSight );
		_passiveApplicators.SetParent( newParent == null ? null : newParent._passiveApplicators );
		_autoTargetSelector.SetParent( newParent == null ? null : newParent._autoTargetSelector );
		_microAI.SetParent( newParent == null ? null : newParent._microAI );
		_node.SetParent( newParent == null ? null : newParent._node );
		_marker.SetParent( newParent == null ? null : newParent._marker );
		_warFogRemoveTime.SetParent( newParent == null ? null : newParent._warFogRemoveTime );
		_warFogRemoveRadius.SetParent( newParent == null ? null : newParent._warFogRemoveRadius );
		_alternativeTargets.SetParent( newParent == null ? null : newParent._alternativeTargets );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_caption.Reset();
		_name.Reset();
		_description.Reset();
		_compiledDescriptionA.Reset();
		_compiledDescriptionB.Reset();
		_shortDescription.Reset();
		_commonDescription.Reset();
		_castLimitations.Reset();
		_image.Reset();
		_imageSecondState.Reset();
		_aoeType.Reset();
		_aoeSize.Reset();
		_aoeMaterial.Reset();
		_aoeHeight.Reset();
		_useRangeMaterial.Reset();
		_aoePassabilityCheckMode.Reset();
		_aoeDisplayOnMinimap.Reset();
		_type.Reset();
		_cooldownTime.Reset();
		_cooldownTimeSecondState.Reset();
		_manaCost.Reset();
		_activeCustomTrigger.Reset();
		_useRange.Reset();
		_minUseRangeCorrection.Reset();
		_castAllowRange.Reset();
		_allowChase.Reset();
		_constants.Reset();
		_conditionFormulas.Reset();
		_isUnitFreeAfterCast.Reset();
		_flags.Reset();
		_targetType.Reset();
		_requireLineOfSight.Reset();
		_passiveApplicators.Reset();
		_autoTargetSelector.Reset();
		_microAI.Reset();
		_node.Reset();
		_marker.Reset();
		_warFogRemoveTime.Reset();
		_warFogRemoveRadius.Reset();
		_alternativeTargets.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _compiledDescriptionA.IsDerivedFromParent()
			&& _compiledDescriptionB.IsDerivedFromParent()
			&& _shortDescription.IsDerivedFromParent()
			&& _commonDescription.IsDerivedFromParent()
			&& _castLimitations.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _imageSecondState.IsDerivedFromParent()
			&& _aoeType.IsDerivedFromParent()
			&& _aoeSize.IsDerivedFromParent()
			&& _aoeMaterial.IsDerivedFromParent()
			&& _aoeHeight.IsDerivedFromParent()
			&& _useRangeMaterial.IsDerivedFromParent()
			&& _aoePassabilityCheckMode.IsDerivedFromParent()
			&& _aoeDisplayOnMinimap.IsDerivedFromParent()
			&& _type.IsDerivedFromParent()
			&& _cooldownTime.IsDerivedFromParent()
			&& _cooldownTimeSecondState.IsDerivedFromParent()
			&& _manaCost.IsDerivedFromParent()
			&& _activeCustomTrigger.IsDerivedFromParent()
			&& _useRange.IsDerivedFromParent()
			&& _minUseRangeCorrection.IsDerivedFromParent()
			&& _castAllowRange.IsDerivedFromParent()
			&& _allowChase.IsDerivedFromParent()
			&& _constants.IsDerivedFromParent()
			&& _conditionFormulas.IsDerivedFromParent()
			&& _isUnitFreeAfterCast.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _targetType.IsDerivedFromParent()
			&& _requireLineOfSight.IsDerivedFromParent()
			&& _passiveApplicators.IsDerivedFromParent()
			&& _autoTargetSelector.IsDerivedFromParent()
			&& _microAI.IsDerivedFromParent()
			&& _node.IsDerivedFromParent()
			&& _marker.IsDerivedFromParent()
			&& _warFogRemoveTime.IsDerivedFromParent()
			&& _warFogRemoveRadius.IsDerivedFromParent()
			&& _alternativeTargets.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "compiledDescriptionA" )
			_compiledDescriptionA.Reset();
		else if ( fieldName == "compiledDescriptionB" )
			_compiledDescriptionB.Reset();
		else if ( fieldName == "shortDescription" )
			_shortDescription.Reset();
		else if ( fieldName == "commonDescription" )
			_commonDescription.Reset();
		else if ( fieldName == "castLimitations" )
			_castLimitations.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "imageSecondState" )
			_imageSecondState.Reset();
		else if ( fieldName == "aoeType" )
			_aoeType.Reset();
		else if ( fieldName == "aoeSize" )
			_aoeSize.Reset();
		else if ( fieldName == "aoeMaterial" )
			_aoeMaterial.Reset();
		else if ( fieldName == "aoeHeight" )
			_aoeHeight.Reset();
		else if ( fieldName == "useRangeMaterial" )
			_useRangeMaterial.Reset();
		else if ( fieldName == "aoePassabilityCheckMode" )
			_aoePassabilityCheckMode.Reset();
		else if ( fieldName == "aoeDisplayOnMinimap" )
			_aoeDisplayOnMinimap.Reset();
		else if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "cooldownTime" )
			_cooldownTime.Reset();
		else if ( fieldName == "cooldownTimeSecondState" )
			_cooldownTimeSecondState.Reset();
		else if ( fieldName == "manaCost" )
			_manaCost.Reset();
		else if ( fieldName == "activeCustomTrigger" )
			_activeCustomTrigger.Reset();
		else if ( fieldName == "useRange" )
			_useRange.Reset();
		else if ( fieldName == "minUseRangeCorrection" )
			_minUseRangeCorrection.Reset();
		else if ( fieldName == "castAllowRange" )
			_castAllowRange.Reset();
		else if ( fieldName == "allowChase" )
			_allowChase.Reset();
		else if ( fieldName == "constants" )
			_constants.Reset();
		else if ( fieldName == "conditionFormulas" )
			_conditionFormulas.Reset();
		else if ( fieldName == "isUnitFreeAfterCast" )
			_isUnitFreeAfterCast.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "targetType" )
			_targetType.Reset();
		else if ( fieldName == "requireLineOfSight" )
			_requireLineOfSight.Reset();
		else if ( fieldName == "passiveApplicators" )
			_passiveApplicators.Reset();
		else if ( fieldName == "autoTargetSelector" )
			_autoTargetSelector.Reset();
		else if ( fieldName == "microAI" )
			_microAI.Reset();
		else if ( fieldName == "node" )
			_node.Reset();
		else if ( fieldName == "marker" )
			_marker.Reset();
		else if ( fieldName == "warFogRemoveTime" )
			_warFogRemoveTime.Reset();
		else if ( fieldName == "warFogRemoveRadius" )
			_warFogRemoveRadius.Reset();
		else if ( fieldName == "alternativeTargets" )
			_alternativeTargets.Reset();
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
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "compiledDescriptionA" )
			return _compiledDescriptionA.IsDerivedFromParent();
		if ( fieldName == "compiledDescriptionB" )
			return _compiledDescriptionB.IsDerivedFromParent();
		if ( fieldName == "shortDescription" )
			return _shortDescription.IsDerivedFromParent();
		if ( fieldName == "commonDescription" )
			return _commonDescription.IsDerivedFromParent();
		if ( fieldName == "castLimitations" )
			return _castLimitations.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "imageSecondState" )
			return _imageSecondState.IsDerivedFromParent();
		if ( fieldName == "aoeType" )
			return _aoeType.IsDerivedFromParent();
		if ( fieldName == "aoeSize" )
			return _aoeSize.IsDerivedFromParent();
		if ( fieldName == "aoeMaterial" )
			return _aoeMaterial.IsDerivedFromParent();
		if ( fieldName == "aoeHeight" )
			return _aoeHeight.IsDerivedFromParent();
		if ( fieldName == "useRangeMaterial" )
			return _useRangeMaterial.IsDerivedFromParent();
		if ( fieldName == "aoePassabilityCheckMode" )
			return _aoePassabilityCheckMode.IsDerivedFromParent();
		if ( fieldName == "aoeDisplayOnMinimap" )
			return _aoeDisplayOnMinimap.IsDerivedFromParent();
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "cooldownTime" )
			return _cooldownTime.IsDerivedFromParent();
		if ( fieldName == "cooldownTimeSecondState" )
			return _cooldownTimeSecondState.IsDerivedFromParent();
		if ( fieldName == "manaCost" )
			return _manaCost.IsDerivedFromParent();
		if ( fieldName == "activeCustomTrigger" )
			return _activeCustomTrigger.IsDerivedFromParent();
		if ( fieldName == "useRange" )
			return _useRange.IsDerivedFromParent();
		if ( fieldName == "minUseRangeCorrection" )
			return _minUseRangeCorrection.IsDerivedFromParent();
		if ( fieldName == "castAllowRange" )
			return _castAllowRange.IsDerivedFromParent();
		if ( fieldName == "allowChase" )
			return _allowChase.IsDerivedFromParent();
		if ( fieldName == "constants" )
			return _constants.IsDerivedFromParent();
		if ( fieldName == "conditionFormulas" )
			return _conditionFormulas.IsDerivedFromParent();
		if ( fieldName == "isUnitFreeAfterCast" )
			return _isUnitFreeAfterCast.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "targetType" )
			return _targetType.IsDerivedFromParent();
		if ( fieldName == "requireLineOfSight" )
			return _requireLineOfSight.IsDerivedFromParent();
		if ( fieldName == "passiveApplicators" )
			return _passiveApplicators.IsDerivedFromParent();
		if ( fieldName == "autoTargetSelector" )
			return _autoTargetSelector.IsDerivedFromParent();
		if ( fieldName == "microAI" )
			return _microAI.IsDerivedFromParent();
		if ( fieldName == "node" )
			return _node.IsDerivedFromParent();
		if ( fieldName == "marker" )
			return _marker.IsDerivedFromParent();
		if ( fieldName == "warFogRemoveTime" )
			return _warFogRemoveTime.IsDerivedFromParent();
		if ( fieldName == "warFogRemoveRadius" )
			return _warFogRemoveRadius.IsDerivedFromParent();
		if ( fieldName == "alternativeTargets" )
			return _alternativeTargets.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Create", "NWorld::PFMicroAI", "NWorld::PFMicroAICreateParams const &cp")]
[UseTypeName("MCAI")]
public class MicroAI : DBResource
{
	private UndoRedoDBPtr<MicroAI> ___parent;
	[HideInOutliner]
	public new DBPtr<MicroAI> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MicroAI>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public MicroAI()
	{
		Initialize( this );
	}
	private void AssignSelf( MicroAI source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MicroAI" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MicroAI source = _source as MicroAI;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MicroAI" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MicroAI newParent = rawParent == null ? null : rawParent.Get<MicroAI>();
		if ( newParent == null && _newParent is MicroAI )
			newParent = _newParent as MicroAI;
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

[FactoryImpl("Create", "NWorld::PFBetweenUnitsTargetSelector", "PFTargetSelector.h")]
[TypeId(0x9A9CE3C0)]
[UseTypeName("TGSL")]
public class BetweenUnitsTargetSelector : MultipleTargetSelector
{
	private UndoRedoDBPtr<BetweenUnitsTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<BetweenUnitsTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;
	private ExecutableIntString _maxTargets;
	private UndoRedo<EBetweenUnitsMode> _pairMode;
	private ExecutableFloatString _minDistBetweenTargets;

	[Description( "Селектор, между целями которых будут возвращаемые точки" )]
	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Максимальное число возвращаемых позиций (0=неограничено)" )]
	public ExecutableIntString maxTargets { get { return _maxTargets; } set { _maxTargets.Assign( value ); } }

	[Description( "Брать N*(N-1) пересечений (AllPairs) или N-1 (Chain) ?" )]
	public EBetweenUnitsMode pairMode { get { return _pairMode.Get(); } set { _pairMode.Set( value ); } }

	[Description( "Если пара целей ближе - не возвращать точку между ними" )]
	public ExecutableFloatString minDistBetweenTargets { get { return _minDistBetweenTargets; } set { _minDistBetweenTargets.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BetweenUnitsTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		_maxTargets = new ExecutableIntString( owner );
		_pairMode = new UndoRedo<EBetweenUnitsMode>( owner, EBetweenUnitsMode.AllPairs );
		ExecutableFloatString __minDistBetweenTargets = new ExecutableFloatString(); // Construct default object for minDistBetweenTargets
		__minDistBetweenTargets.sString = "0.f";
		_minDistBetweenTargets = new ExecutableFloatString( owner, __minDistBetweenTargets );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_maxTargets.Changed += FireChangedEvent;
		_pairMode.Changed += FireChangedEvent;
		_minDistBetweenTargets.Changed += FireChangedEvent;
	}

	public BetweenUnitsTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( BetweenUnitsTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BetweenUnitsTargetSelector" );
		targetSelector = source.targetSelector;
		maxTargets = source.maxTargets;
		pairMode = source.pairMode;
		minDistBetweenTargets = source.minDistBetweenTargets;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BetweenUnitsTargetSelector source = _source as BetweenUnitsTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BetweenUnitsTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BetweenUnitsTargetSelector newParent = rawParent == null ? null : rawParent.Get<BetweenUnitsTargetSelector>();
		if ( newParent == null && _newParent is BetweenUnitsTargetSelector )
			newParent = _newParent as BetweenUnitsTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_maxTargets.SetParent( newParent == null ? null : newParent._maxTargets );
		_pairMode.SetParent( newParent == null ? null : newParent._pairMode );
		_minDistBetweenTargets.SetParent( newParent == null ? null : newParent._minDistBetweenTargets );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_maxTargets.Reset();
		_pairMode.Reset();
		_minDistBetweenTargets.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _maxTargets.IsDerivedFromParent()
			&& _pairMode.IsDerivedFromParent()
			&& _minDistBetweenTargets.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "maxTargets" )
			_maxTargets.Reset();
		else if ( fieldName == "pairMode" )
			_pairMode.Reset();
		else if ( fieldName == "minDistBetweenTargets" )
			_minDistBetweenTargets.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "maxTargets" )
			return _maxTargets.IsDerivedFromParent();
		if ( fieldName == "pairMode" )
			return _pairMode.IsDerivedFromParent();
		if ( fieldName == "minDistBetweenTargets" )
			return _minDistBetweenTargets.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Create", "NWorld::PFApplBounce", "PFApplBounce.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE7792380)]
[UseTypeName("APLR")]
public class BounceApplicator : BuffApplicator
{
	private UndoRedoDBPtr<BounceApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<BounceApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SingleTargetSelector> _target;
	private UndoRedoDBPtr<Spell> _spell;
	private ExecutableIntString _targetsNumber;
	private ExecutableFloatString _bounceDelay;
	private UndoRedo<EApplicatorApplyTarget> _startTarget;
	private UndoRedo<EBounceFlags> _flags;
	private UndoRedoAssignableList<DBPtr<EffectBase>> _cancelEffect;

	[Description( "Target to select for next bounce" )]
	public DBPtr<SingleTargetSelector> target { get { return _target.Get(); } set { _target.Set( value ); } }

	[Description( "Spell to send" )]
	public DBPtr<Spell> spell { get { return _spell.Get(); } set { _spell.Set( value ); } }

	[Description( "Number of targets to bounce between. Less or equal 0 means no limits" )]
	public ExecutableIntString targetsNumber { get { return _targetsNumber; } set { _targetsNumber.Assign( value ); } }

	[Description( "Delay before next bounce" )]
	public ExecutableFloatString bounceDelay { get { return _bounceDelay; } set { _bounceDelay.Assign( value ); } }

	[Description( "Target from which bouncing starts" )]
	public EApplicatorApplyTarget startTarget { get { return _startTarget.Get(); } set { _startTarget.Set( value ); } }

	[Description( "Flags specific for Bounce applicator" )]
	public EBounceFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<EffectBase>> cancelEffect { get { return _cancelEffect; } set { _cancelEffect.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BounceApplicator>(owner);
		_target = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_spell = new UndoRedoDBPtr<Spell>( owner );
		ExecutableIntString __targetsNumber = new ExecutableIntString(); // Construct default object for targetsNumber
		__targetsNumber.sString = "1";
		_targetsNumber = new ExecutableIntString( owner, __targetsNumber );
		ExecutableFloatString __bounceDelay = new ExecutableFloatString(); // Construct default object for bounceDelay
		__bounceDelay.sString = "0.0";
		_bounceDelay = new ExecutableFloatString( owner, __bounceDelay );
		_startTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_flags = new UndoRedo<EBounceFlags>( owner, (EBounceFlags)0 );
		_cancelEffect = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner, typeof( ETeamID ) );
		___parent.Changed += FireChangedEvent;
		_target.Changed += FireChangedEvent;
		_spell.Changed += FireChangedEvent;
		_targetsNumber.Changed += FireChangedEvent;
		_bounceDelay.Changed += FireChangedEvent;
		_startTarget.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_cancelEffect.Changed += FireChangedEvent;
	}

	public BounceApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( BounceApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BounceApplicator" );
		target = source.target;
		spell = source.spell;
		targetsNumber = source.targetsNumber;
		bounceDelay = source.bounceDelay;
		startTarget = source.startTarget;
		flags = source.flags;
		cancelEffect = source.cancelEffect;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BounceApplicator source = _source as BounceApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BounceApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BounceApplicator newParent = rawParent == null ? null : rawParent.Get<BounceApplicator>();
		if ( newParent == null && _newParent is BounceApplicator )
			newParent = _newParent as BounceApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_target.SetParent( newParent == null ? null : newParent._target );
		_spell.SetParent( newParent == null ? null : newParent._spell );
		_targetsNumber.SetParent( newParent == null ? null : newParent._targetsNumber );
		_bounceDelay.SetParent( newParent == null ? null : newParent._bounceDelay );
		_startTarget.SetParent( newParent == null ? null : newParent._startTarget );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_cancelEffect.SetParent( newParent == null ? null : newParent._cancelEffect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_target.Reset();
		_spell.Reset();
		_targetsNumber.Reset();
		_bounceDelay.Reset();
		_startTarget.Reset();
		_flags.Reset();
		_cancelEffect.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_target.IsDerivedFromParent()
			&& _spell.IsDerivedFromParent()
			&& _targetsNumber.IsDerivedFromParent()
			&& _bounceDelay.IsDerivedFromParent()
			&& _startTarget.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _cancelEffect.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "target" )
			_target.Reset();
		else if ( fieldName == "spell" )
			_spell.Reset();
		else if ( fieldName == "targetsNumber" )
			_targetsNumber.Reset();
		else if ( fieldName == "bounceDelay" )
			_bounceDelay.Reset();
		else if ( fieldName == "startTarget" )
			_startTarget.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "cancelEffect" )
			_cancelEffect.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "target" )
			return _target.IsDerivedFromParent();
		if ( fieldName == "spell" )
			return _spell.IsDerivedFromParent();
		if ( fieldName == "targetsNumber" )
			return _targetsNumber.IsDerivedFromParent();
		if ( fieldName == "bounceDelay" )
			return _bounceDelay.IsDerivedFromParent();
		if ( fieldName == "startTarget" )
			return _startTarget.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "cancelEffect" )
			return _cancelEffect.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFApplAbilityMod", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F6BCC40)]
[UseTypeName("APLR")]
public class AbilityModApplicator : BuffApplicator
{
	private UndoRedoDBPtr<AbilityModApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<AbilityModApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _addValue;
	private ExecutableFloatString _multValue;
	private UndoRedo<EAbilityIdFlags> _targetAbilities;
	private UndoRedo<EAbilityModMode> _mode;
	private UndoRedoDBPtr<Ability> _specificAbility;
	private UndoRedoAssignableList<DBPtr<Ability>> _talents;
	private UndoRedo<EUseMode> _useListAs;

	[Category( "Ability Modification" )]
	[Description( "Value to be added to stat [Formula update: every step]" )]
	public ExecutableFloatString addValue { get { return _addValue; } set { _addValue.Assign( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Value to be multiplied on stat [Formula update: every step]" )]
	public ExecutableFloatString multValue { get { return _multValue; } set { _multValue.Assign( value ); } }

	[Category( "Ability Modification" )]
	public EAbilityIdFlags targetAbilities { get { return _targetAbilities.Get(); } set { _targetAbilities.Set( value ); } }

	[Category( "Ability Modification" )]
	public EAbilityModMode mode { get { return _mode.Get(); } set { _mode.Set( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Ability to modify (used only if targetAbilities == Specific)" )]
	public DBPtr<Ability> specificAbility { get { return _specificAbility.Get(); } set { _specificAbility.Set( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Список улучшаемых талантов/предметов" )]
	public libdb.IChangeableList<DBPtr<Ability>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	[Category( "Ability Modification" )]
	[Description( "Режим работы со списком" )]
	public EUseMode useListAs { get { return _useListAs.Get(); } set { _useListAs.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AbilityModApplicator>(owner);
		ExecutableFloatString __addValue = new ExecutableFloatString(); // Construct default object for addValue
		__addValue.sString = "0.0f";
		_addValue = new ExecutableFloatString( owner, __addValue );
		ExecutableFloatString __multValue = new ExecutableFloatString(); // Construct default object for multValue
		__multValue.sString = "1.0f";
		_multValue = new ExecutableFloatString( owner, __multValue );
		_targetAbilities = new UndoRedo<EAbilityIdFlags>( owner, EAbilityIdFlags.All );
		_mode = new UndoRedo<EAbilityModMode>( owner, EAbilityModMode.naftacost );
		_specificAbility = new UndoRedoDBPtr<Ability>( owner );
		_talents = new UndoRedoAssignableList<DBPtr<Ability>>( owner );
		_useListAs = new UndoRedo<EUseMode>( owner, EUseMode.ListAsException );
		___parent.Changed += FireChangedEvent;
		_addValue.Changed += FireChangedEvent;
		_multValue.Changed += FireChangedEvent;
		_targetAbilities.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		_specificAbility.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
		_useListAs.Changed += FireChangedEvent;
	}

	public AbilityModApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( AbilityModApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AbilityModApplicator" );
		addValue = source.addValue;
		multValue = source.multValue;
		targetAbilities = source.targetAbilities;
		mode = source.mode;
		specificAbility = source.specificAbility;
		talents = source.talents;
		useListAs = source.useListAs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AbilityModApplicator source = _source as AbilityModApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AbilityModApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AbilityModApplicator newParent = rawParent == null ? null : rawParent.Get<AbilityModApplicator>();
		if ( newParent == null && _newParent is AbilityModApplicator )
			newParent = _newParent as AbilityModApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_addValue.SetParent( newParent == null ? null : newParent._addValue );
		_multValue.SetParent( newParent == null ? null : newParent._multValue );
		_targetAbilities.SetParent( newParent == null ? null : newParent._targetAbilities );
		_mode.SetParent( newParent == null ? null : newParent._mode );
		_specificAbility.SetParent( newParent == null ? null : newParent._specificAbility );
		_talents.SetParent( newParent == null ? null : newParent._talents );
		_useListAs.SetParent( newParent == null ? null : newParent._useListAs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_addValue.Reset();
		_multValue.Reset();
		_targetAbilities.Reset();
		_mode.Reset();
		_specificAbility.Reset();
		_talents.Reset();
		_useListAs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_addValue.IsDerivedFromParent()
			&& _multValue.IsDerivedFromParent()
			&& _targetAbilities.IsDerivedFromParent()
			&& _mode.IsDerivedFromParent()
			&& _specificAbility.IsDerivedFromParent()
			&& _talents.IsDerivedFromParent()
			&& _useListAs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "addValue" )
			_addValue.Reset();
		else if ( fieldName == "multValue" )
			_multValue.Reset();
		else if ( fieldName == "targetAbilities" )
			_targetAbilities.Reset();
		else if ( fieldName == "mode" )
			_mode.Reset();
		else if ( fieldName == "specificAbility" )
			_specificAbility.Reset();
		else if ( fieldName == "talents" )
			_talents.Reset();
		else if ( fieldName == "useListAs" )
			_useListAs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "addValue" )
			return _addValue.IsDerivedFromParent();
		if ( fieldName == "multValue" )
			return _multValue.IsDerivedFromParent();
		if ( fieldName == "targetAbilities" )
			return _targetAbilities.IsDerivedFromParent();
		if ( fieldName == "mode" )
			return _mode.IsDerivedFromParent();
		if ( fieldName == "specificAbility" )
			return _specificAbility.IsDerivedFromParent();
		if ( fieldName == "talents" )
			return _talents.IsDerivedFromParent();
		if ( fieldName == "useListAs" )
			return _useListAs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFCapsuleTargetSelector", "PFTargetSelector.h")]
[TypeId(0x9E6CBAC0)]
[UseTypeName("TGSL")]
public class CapsuleTargetSelector : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<CapsuleTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<CapsuleTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ETargetSelectorPoint> _segmentBegin;
	private UndoRedo<ETargetSelectorPoint> _segmentEnd;
	private UndoRedoDBPtr<SingleTargetSelector> _segmentEndTargetSelector;
	private ExecutableFloatString _range;
	private ExecutableFloatString _rangeFromOwner;
	private UndoRedo<bool> _cutoffFirstSegment;
	private UndoRedo<float> _segmentDirectionOffset;

	[Description( "Begin of segment defining direction" )]
	public ETargetSelectorPoint segmentBegin { get { return _segmentBegin.Get(); } set { _segmentBegin.Set( value ); } }

	[Description( "End of segment defining direction" )]
	public ETargetSelectorPoint segmentEnd { get { return _segmentEnd.Get(); } set { _segmentEnd.Set( value ); } }

	[Description( "If defined, overrides segmentEnd" )]
	public DBPtr<SingleTargetSelector> segmentEndTargetSelector { get { return _segmentEndTargetSelector.Get(); } set { _segmentEndTargetSelector.Set( value ); } }

	[Description( "Range of selection" )]
	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	[Description( "Range from ability owner. Set to 0 if not required." )]
	public ExecutableFloatString rangeFromOwner { get { return _rangeFromOwner; } set { _rangeFromOwner.Assign( value ); } }

	[Description( "Cutoff beginning of the first segment" )]
	public bool cutoffFirstSegment { get { return _cutoffFirstSegment.Get(); } set { _cutoffFirstSegment.Set( value ); } }

	[Description( "Дополнительный поворот выбранного направления капсулы, в градусах" )]
	public float segmentDirectionOffset { get { return _segmentDirectionOffset.Get(); } set { _segmentDirectionOffset.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CapsuleTargetSelector>(owner);
		_segmentBegin = new UndoRedo<ETargetSelectorPoint>( owner, ETargetSelectorPoint.AbilityOwner );
		_segmentEnd = new UndoRedo<ETargetSelectorPoint>( owner, ETargetSelectorPoint.CurrentPosition );
		_segmentEndTargetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		ExecutableFloatString __rangeFromOwner = new ExecutableFloatString(); // Construct default object for rangeFromOwner
		__rangeFromOwner.sString = "0.0f";
		_rangeFromOwner = new ExecutableFloatString( owner, __rangeFromOwner );
		_cutoffFirstSegment = new UndoRedo<bool>( owner, false );
		_segmentDirectionOffset = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_segmentBegin.Changed += FireChangedEvent;
		_segmentEnd.Changed += FireChangedEvent;
		_segmentEndTargetSelector.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_rangeFromOwner.Changed += FireChangedEvent;
		_cutoffFirstSegment.Changed += FireChangedEvent;
		_segmentDirectionOffset.Changed += FireChangedEvent;
	}

	public CapsuleTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( CapsuleTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CapsuleTargetSelector" );
		segmentBegin = source.segmentBegin;
		segmentEnd = source.segmentEnd;
		segmentEndTargetSelector = source.segmentEndTargetSelector;
		range = source.range;
		rangeFromOwner = source.rangeFromOwner;
		cutoffFirstSegment = source.cutoffFirstSegment;
		segmentDirectionOffset = source.segmentDirectionOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CapsuleTargetSelector source = _source as CapsuleTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CapsuleTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CapsuleTargetSelector newParent = rawParent == null ? null : rawParent.Get<CapsuleTargetSelector>();
		if ( newParent == null && _newParent is CapsuleTargetSelector )
			newParent = _newParent as CapsuleTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_segmentBegin.SetParent( newParent == null ? null : newParent._segmentBegin );
		_segmentEnd.SetParent( newParent == null ? null : newParent._segmentEnd );
		_segmentEndTargetSelector.SetParent( newParent == null ? null : newParent._segmentEndTargetSelector );
		_range.SetParent( newParent == null ? null : newParent._range );
		_rangeFromOwner.SetParent( newParent == null ? null : newParent._rangeFromOwner );
		_cutoffFirstSegment.SetParent( newParent == null ? null : newParent._cutoffFirstSegment );
		_segmentDirectionOffset.SetParent( newParent == null ? null : newParent._segmentDirectionOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_segmentBegin.Reset();
		_segmentEnd.Reset();
		_segmentEndTargetSelector.Reset();
		_range.Reset();
		_rangeFromOwner.Reset();
		_cutoffFirstSegment.Reset();
		_segmentDirectionOffset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_segmentBegin.IsDerivedFromParent()
			&& _segmentEnd.IsDerivedFromParent()
			&& _segmentEndTargetSelector.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& _rangeFromOwner.IsDerivedFromParent()
			&& _cutoffFirstSegment.IsDerivedFromParent()
			&& _segmentDirectionOffset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "segmentBegin" )
			_segmentBegin.Reset();
		else if ( fieldName == "segmentEnd" )
			_segmentEnd.Reset();
		else if ( fieldName == "segmentEndTargetSelector" )
			_segmentEndTargetSelector.Reset();
		else if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "rangeFromOwner" )
			_rangeFromOwner.Reset();
		else if ( fieldName == "cutoffFirstSegment" )
			_cutoffFirstSegment.Reset();
		else if ( fieldName == "segmentDirectionOffset" )
			_segmentDirectionOffset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "segmentBegin" )
			return _segmentBegin.IsDerivedFromParent();
		if ( fieldName == "segmentEnd" )
			return _segmentEnd.IsDerivedFromParent();
		if ( fieldName == "segmentEndTargetSelector" )
			return _segmentEndTargetSelector.IsDerivedFromParent();
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "rangeFromOwner" )
			return _rangeFromOwner.IsDerivedFromParent();
		if ( fieldName == "cutoffFirstSegment" )
			return _cutoffFirstSegment.IsDerivedFromParent();
		if ( fieldName == "segmentDirectionOffset" )
			return _segmentDirectionOffset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Check", "NWorld::PFAbilityData", "NWorld::CastLimitationsCheckParams const &cp", ReturnType = "const NWorld::PFAbilityData*")]
[UseTypeName("ABCL")]
public class CastLimitation : DBResource
{
	private UndoRedoDBPtr<CastLimitation> ___parent;
	[HideInOutliner]
	public new DBPtr<CastLimitation> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<UIEvent> _uiEvent;

	[Description( "Error description UI event" )]
	public DBPtr<UIEvent> uiEvent { get { return _uiEvent.Get(); } set { _uiEvent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CastLimitation>(owner);
		_uiEvent = new UndoRedoDBPtr<UIEvent>( owner );
		___parent.Changed += FireChangedEvent;
		_uiEvent.Changed += FireChangedEvent;
	}

	public CastLimitation()
	{
		Initialize( this );
	}
	private void AssignSelf( CastLimitation source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CastLimitation" );
		uiEvent = source.uiEvent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CastLimitation source = _source as CastLimitation;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CastLimitation" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CastLimitation newParent = rawParent == null ? null : rawParent.Get<CastLimitation>();
		if ( newParent == null && _newParent is CastLimitation )
			newParent = _newParent as CastLimitation;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_uiEvent.SetParent( newParent == null ? null : newParent._uiEvent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_uiEvent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_uiEvent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "uiEvent" )
			_uiEvent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "uiEvent" )
			return _uiEvent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[FactoryImpl("Create", "NWorld::PFApplChainLightning", "PFApplChainLightning.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B0D)]
[UseTypeName("APLR")]
public class ChainLightningApplicator : BaseApplicator
{
	private UndoRedoDBPtr<ChainLightningApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ChainLightningApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableIntString _numJumps;
	private UndoRedoDBPtr<Spell> _spell;
	private UndoRedo<float> _onJumpSpellScale;
	private UndoRedo<float> _betweenJumpsTimeInterval;
	private ExecutableFloatString _range;
	private UndoRedo<ESpellTarget> _targetFilter;
	private ExecutableIntString _effectIndex;
	private UndoRedoAssignableList<DBPtr<EffectBase>> _effects;
	private ExecutableBoolString _jumpOnEvade;

	[Category( "ChainLightning" )]
	public ExecutableIntString numJumps { get { return _numJumps; } set { _numJumps.Assign( value ); } }

	public DBPtr<Spell> spell { get { return _spell.Get(); } set { _spell.Set( value ); } }

	public float onJumpSpellScale { get { return _onJumpSpellScale.Get(); } set { _onJumpSpellScale.Set( value ); } }

	public float betweenJumpsTimeInterval { get { return _betweenJumpsTimeInterval.Get(); } set { _betweenJumpsTimeInterval.Set( value ); } }

	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	[Description( "Flags that specify targets of this spell." )]
	public ESpellTarget targetFilter { get { return _targetFilter.Get(); } set { _targetFilter.Set( value ); } }

	[Description( "Индекс эффекта из списка" )]
	public ExecutableIntString effectIndex { get { return _effectIndex; } set { _effectIndex.Assign( value ); } }

	[Description( "Списов эффектов (LightningEffect или EffectList с молниями)" )]
	public libdb.IChangeableList<DBPtr<EffectBase>> effects { get { return _effects; } set { _effects.Assign( value ); } }

	[Description( "Перескакивать на новую цель, если текущая уклонилась" )]
	public ExecutableBoolString jumpOnEvade { get { return _jumpOnEvade; } set { _jumpOnEvade.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChainLightningApplicator>(owner);
		ExecutableIntString __numJumps = new ExecutableIntString(); // Construct default object for numJumps
		__numJumps.sString = "1";
		_numJumps = new ExecutableIntString( owner, __numJumps );
		_spell = new UndoRedoDBPtr<Spell>( owner );
		_onJumpSpellScale = new UndoRedo<float>( owner, 1.0f );
		_betweenJumpsTimeInterval = new UndoRedo<float>( owner, 0.0f );
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0";
		_range = new ExecutableFloatString( owner, __range );
		_targetFilter = new UndoRedo<ESpellTarget>( owner, ESpellTarget.AllEnemies | ESpellTarget.VisibleTargetsOnly );
		_effectIndex = new ExecutableIntString( owner );
		_effects = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner );
		ExecutableBoolString __jumpOnEvade = new ExecutableBoolString(); // Construct default object for jumpOnEvade
		__jumpOnEvade.sString = "true";
		_jumpOnEvade = new ExecutableBoolString( owner, __jumpOnEvade );
		___parent.Changed += FireChangedEvent;
		_numJumps.Changed += FireChangedEvent;
		_spell.Changed += FireChangedEvent;
		_onJumpSpellScale.Changed += FireChangedEvent;
		_betweenJumpsTimeInterval.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_targetFilter.Changed += FireChangedEvent;
		_effectIndex.Changed += FireChangedEvent;
		_effects.Changed += FireChangedEvent;
		_jumpOnEvade.Changed += FireChangedEvent;
	}

	public ChainLightningApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ChainLightningApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChainLightningApplicator" );
		numJumps = source.numJumps;
		spell = source.spell;
		onJumpSpellScale = source.onJumpSpellScale;
		betweenJumpsTimeInterval = source.betweenJumpsTimeInterval;
		range = source.range;
		targetFilter = source.targetFilter;
		effectIndex = source.effectIndex;
		effects = source.effects;
		jumpOnEvade = source.jumpOnEvade;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChainLightningApplicator source = _source as ChainLightningApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChainLightningApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChainLightningApplicator newParent = rawParent == null ? null : rawParent.Get<ChainLightningApplicator>();
		if ( newParent == null && _newParent is ChainLightningApplicator )
			newParent = _newParent as ChainLightningApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_numJumps.SetParent( newParent == null ? null : newParent._numJumps );
		_spell.SetParent( newParent == null ? null : newParent._spell );
		_onJumpSpellScale.SetParent( newParent == null ? null : newParent._onJumpSpellScale );
		_betweenJumpsTimeInterval.SetParent( newParent == null ? null : newParent._betweenJumpsTimeInterval );
		_range.SetParent( newParent == null ? null : newParent._range );
		_targetFilter.SetParent( newParent == null ? null : newParent._targetFilter );
		_effectIndex.SetParent( newParent == null ? null : newParent._effectIndex );
		_effects.SetParent( newParent == null ? null : newParent._effects );
		_jumpOnEvade.SetParent( newParent == null ? null : newParent._jumpOnEvade );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_numJumps.Reset();
		_spell.Reset();
		_onJumpSpellScale.Reset();
		_betweenJumpsTimeInterval.Reset();
		_range.Reset();
		_targetFilter.Reset();
		_effectIndex.Reset();
		_effects.Reset();
		_jumpOnEvade.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_numJumps.IsDerivedFromParent()
			&& _spell.IsDerivedFromParent()
			&& _onJumpSpellScale.IsDerivedFromParent()
			&& _betweenJumpsTimeInterval.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& _targetFilter.IsDerivedFromParent()
			&& _effectIndex.IsDerivedFromParent()
			&& _effects.IsDerivedFromParent()
			&& _jumpOnEvade.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "numJumps" )
			_numJumps.Reset();
		else if ( fieldName == "spell" )
			_spell.Reset();
		else if ( fieldName == "onJumpSpellScale" )
			_onJumpSpellScale.Reset();
		else if ( fieldName == "betweenJumpsTimeInterval" )
			_betweenJumpsTimeInterval.Reset();
		else if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "targetFilter" )
			_targetFilter.Reset();
		else if ( fieldName == "effectIndex" )
			_effectIndex.Reset();
		else if ( fieldName == "effects" )
			_effects.Reset();
		else if ( fieldName == "jumpOnEvade" )
			_jumpOnEvade.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "numJumps" )
			return _numJumps.IsDerivedFromParent();
		if ( fieldName == "spell" )
			return _spell.IsDerivedFromParent();
		if ( fieldName == "onJumpSpellScale" )
			return _onJumpSpellScale.IsDerivedFromParent();
		if ( fieldName == "betweenJumpsTimeInterval" )
			return _betweenJumpsTimeInterval.IsDerivedFromParent();
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "targetFilter" )
			return _targetFilter.IsDerivedFromParent();
		if ( fieldName == "effectIndex" )
			return _effectIndex.IsDerivedFromParent();
		if ( fieldName == "effects" )
			return _effects.IsDerivedFromParent();
		if ( fieldName == "jumpOnEvade" )
			return _jumpOnEvade.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplChangeAnimation", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2C68AC01)]
[UseTypeName("APLR")]
public class ChangeAnimationApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ChangeAnimationApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeAnimationApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EAnimStates> _animState;
	private UndoRedo<string> _animation;
	private UndoRedo<string> _marker;
	private UndoRedo<bool> _upper;
	private UndoRedo<bool> _affectAllSets;

	public EAnimStates animState { get { return _animState.Get(); } set { _animState.Set( value ); } }

	public string animation { get { return _animation.Get(); } set { _animation.Set( value ); } }

	public string marker { get { return _marker.Get(); } set { _marker.Set( value ); } }

	public bool upper { get { return _upper.Get(); } set { _upper.Set( value ); } }

	public bool affectAllSets { get { return _affectAllSets.Get(); } set { _affectAllSets.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeAnimationApplicator>(owner);
		_animState = new UndoRedo<EAnimStates>( owner, EAnimStates.Invalid );
		_animation = new UndoRedo<string>( owner, string.Empty );
		_marker = new UndoRedo<string>( owner, string.Empty );
		_upper = new UndoRedo<bool>( owner, false );
		_affectAllSets = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_animState.Changed += FireChangedEvent;
		_animation.Changed += FireChangedEvent;
		_marker.Changed += FireChangedEvent;
		_upper.Changed += FireChangedEvent;
		_affectAllSets.Changed += FireChangedEvent;
	}

	public ChangeAnimationApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeAnimationApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeAnimationApplicator" );
		animState = source.animState;
		animation = source.animation;
		marker = source.marker;
		upper = source.upper;
		affectAllSets = source.affectAllSets;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeAnimationApplicator source = _source as ChangeAnimationApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeAnimationApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeAnimationApplicator newParent = rawParent == null ? null : rawParent.Get<ChangeAnimationApplicator>();
		if ( newParent == null && _newParent is ChangeAnimationApplicator )
			newParent = _newParent as ChangeAnimationApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_animState.SetParent( newParent == null ? null : newParent._animState );
		_animation.SetParent( newParent == null ? null : newParent._animation );
		_marker.SetParent( newParent == null ? null : newParent._marker );
		_upper.SetParent( newParent == null ? null : newParent._upper );
		_affectAllSets.SetParent( newParent == null ? null : newParent._affectAllSets );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_animState.Reset();
		_animation.Reset();
		_marker.Reset();
		_upper.Reset();
		_affectAllSets.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_animState.IsDerivedFromParent()
			&& _animation.IsDerivedFromParent()
			&& _marker.IsDerivedFromParent()
			&& _upper.IsDerivedFromParent()
			&& _affectAllSets.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "animState" )
			_animState.Reset();
		else if ( fieldName == "animation" )
			_animation.Reset();
		else if ( fieldName == "marker" )
			_marker.Reset();
		else if ( fieldName == "upper" )
			_upper.Reset();
		else if ( fieldName == "affectAllSets" )
			_affectAllSets.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "animState" )
			return _animState.IsDerivedFromParent();
		if ( fieldName == "animation" )
			return _animation.IsDerivedFromParent();
		if ( fieldName == "marker" )
			return _marker.IsDerivedFromParent();
		if ( fieldName == "upper" )
			return _upper.IsDerivedFromParent();
		if ( fieldName == "affectAllSets" )
			return _affectAllSets.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplChangeAnimSet", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2C68AC00)]
[UseTypeName("APLR")]
public class ChangeAnimSetApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ChangeAnimSetApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeAnimSetApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<AnimSet> _animSet;

	public DBPtr<AnimSet> animSet { get { return _animSet.Get(); } set { _animSet.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeAnimSetApplicator>(owner);
		_animSet = new UndoRedoDBPtr<AnimSet>( owner );
		___parent.Changed += FireChangedEvent;
		_animSet.Changed += FireChangedEvent;
	}

	public ChangeAnimSetApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeAnimSetApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeAnimSetApplicator" );
		animSet = source.animSet;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeAnimSetApplicator source = _source as ChangeAnimSetApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeAnimSetApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeAnimSetApplicator newParent = rawParent == null ? null : rawParent.Get<ChangeAnimSetApplicator>();
		if ( newParent == null && _newParent is ChangeAnimSetApplicator )
			newParent = _newParent as ChangeAnimSetApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_animSet.SetParent( newParent == null ? null : newParent._animSet );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_animSet.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_animSet.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "animSet" )
			_animSet.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "animSet" )
			return _animSet.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplChangeBaseAttack", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E678AC0)]
[UseTypeName("APLR")]
public class ChangeBaseAttackApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ChangeBaseAttackApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeBaseAttackApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseAttack> _attackAbility;
	private UndoRedo<bool> _applyPassivePart;

	[Description( "This attack ability replaces attack ability of the unit" )]
	public DBPtr<BaseAttack> attackAbility { get { return _attackAbility.Get(); } set { _attackAbility.Set( value ); } }

	public bool applyPassivePart { get { return _applyPassivePart.Get(); } set { _applyPassivePart.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeBaseAttackApplicator>(owner);
		_attackAbility = new UndoRedoDBPtr<BaseAttack>( owner );
		_applyPassivePart = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_attackAbility.Changed += FireChangedEvent;
		_applyPassivePart.Changed += FireChangedEvent;
	}

	public ChangeBaseAttackApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeBaseAttackApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeBaseAttackApplicator" );
		attackAbility = source.attackAbility;
		applyPassivePart = source.applyPassivePart;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeBaseAttackApplicator source = _source as ChangeBaseAttackApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeBaseAttackApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeBaseAttackApplicator newParent = rawParent == null ? null : rawParent.Get<ChangeBaseAttackApplicator>();
		if ( newParent == null && _newParent is ChangeBaseAttackApplicator )
			newParent = _newParent as ChangeBaseAttackApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_attackAbility.SetParent( newParent == null ? null : newParent._attackAbility );
		_applyPassivePart.SetParent( newParent == null ? null : newParent._applyPassivePart );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_attackAbility.Reset();
		_applyPassivePart.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_attackAbility.IsDerivedFromParent()
			&& _applyPassivePart.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "attackAbility" )
			_attackAbility.Reset();
		else if ( fieldName == "applyPassivePart" )
			_applyPassivePart.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "attackAbility" )
			return _attackAbility.IsDerivedFromParent();
		if ( fieldName == "applyPassivePart" )
			return _applyPassivePart.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplChangeHeroState", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x22CC6D80)]
[UseTypeName("APLR")]
public class ChangeHeroStateApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ChangeHeroStateApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeHeroStateApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeHeroStateApplicator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public ChangeHeroStateApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeHeroStateApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeHeroStateApplicator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeHeroStateApplicator source = _source as ChangeHeroStateApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeHeroStateApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeHeroStateApplicator newParent = rawParent == null ? null : rawParent.Get<ChangeHeroStateApplicator>();
		if ( newParent == null && _newParent is ChangeHeroStateApplicator )
			newParent = _newParent as ChangeHeroStateApplicator;
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

[FactoryImpl("Create", "NWorld::PFApplChangeState", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE7958BC0)]
[UseTypeName("APLR")]
public class ChangeStateApplicator : BaseApplicator
{
	private UndoRedoDBPtr<ChangeStateApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeStateApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _newStateName;

	public string newStateName { get { return _newStateName.Get(); } set { _newStateName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeStateApplicator>(owner);
		_newStateName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_newStateName.Changed += FireChangedEvent;
	}

	public ChangeStateApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeStateApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeStateApplicator" );
		newStateName = source.newStateName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeStateApplicator source = _source as ChangeStateApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeStateApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeStateApplicator newParent = rawParent == null ? null : rawParent.Get<ChangeStateApplicator>();
		if ( newParent == null && _newParent is ChangeStateApplicator )
			newParent = _newParent as ChangeStateApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_newStateName.SetParent( newParent == null ? null : newParent._newStateName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_newStateName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_newStateName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "newStateName" )
			_newStateName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "newStateName" )
			return _newStateName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFApplChannelling", "PFApplChannelling.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E67B280)]
[UseTypeName("APLR")]
public class ChannellingApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ChannellingApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ChannellingApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;
	private UndoRedo<EChannelingType> _channelingType;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicatorsOnSelf;
	private UndoRedoDBPtr<Spell> _startSpell;
	private UndoRedoDBPtr<Spell> _periodicalSpell;
	private UndoRedoDBPtr<Spell> _stopSpell;
	private UndoRedoDBPtr<Spell> _cancelSpell;
	private UndoRedo<float> _period;
	private UndoRedo<EBaseUnitEventFlags> _interruptEvents;
	private UndoRedo<bool> _cancelOnInterrupt;
	private UndoRedo<bool> _removeStartSpellEffectOnInterrupt;
	private ExecutableFloatString _scaleWhenInterrupted;
	private UndoRedo<bool> _cancelOnDisable;

	[Description( "Targets selector" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Type of channeling. In case of Creation don't forget to setup DontTakeMana flag for Ability" )]
	public EChannelingType channelingType { get { return _channelingType.Get(); } set { _channelingType.Set( value ); } }

	[Description( "List of applicators that will be applied to caster of channelling" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicatorsOnSelf { get { return _applicatorsOnSelf; } set { _applicatorsOnSelf.Assign( value ); } }

	[Description( "Spell that will be cast on the targets of applicator at start" )]
	public DBPtr<Spell> startSpell { get { return _startSpell.Get(); } set { _startSpell.Set( value ); } }

	[Description( "Spell that will be cast on the targets of applicator every 'period' of time" )]
	public DBPtr<Spell> periodicalSpell { get { return _periodicalSpell.Get(); } set { _periodicalSpell.Set( value ); } }

	[Description( "Spell that will be cast on the targets of applicator at stop" )]
	public DBPtr<Spell> stopSpell { get { return _stopSpell.Get(); } set { _stopSpell.Set( value ); } }

	[Description( "Spell that will be cast on the targets of applicator on cancel" )]
	public DBPtr<Spell> cancelSpell { get { return _cancelSpell.Get(); } set { _cancelSpell.Set( value ); } }

	[Description( "Period of time (in sec)" )]
	public float period { get { return _period.Get(); } set { _period.Set( value ); } }

	[Description( "Flags that specify channelling interruption events" )]
	public EBaseUnitEventFlags interruptEvents { get { return _interruptEvents.Get(); } set { _interruptEvents.Set( value ); } }

	[Description( "When 'true' channelling will be cancelled when interrupted and cancelSpell will be applied instead of stopSpell" )]
	public bool cancelOnInterrupt { get { return _cancelOnInterrupt.Get(); } set { _cancelOnInterrupt.Set( value ); } }

	[Description( "On interrupt all start spell effects will be removed" )]
	public bool removeStartSpellEffectOnInterrupt { get { return _removeStartSpellEffectOnInterrupt.Get(); } set { _removeStartSpellEffectOnInterrupt.Set( value ); } }

	[Description( "When channelling is interrupted it's scale will be calculated using this formula" )]
	public ExecutableFloatString scaleWhenInterrupted { get { return _scaleWhenInterrupted; } set { _scaleWhenInterrupted.Assign( value ); } }

	[Description( "Should cancelSpell will be applied on disable instead of stopSpell?" )]
	public bool cancelOnDisable { get { return _cancelOnDisable.Get(); } set { _cancelOnDisable.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChannellingApplicator>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		_channelingType = new UndoRedo<EChannelingType>( owner, EChannelingType.Streaming );
		_applicatorsOnSelf = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		_startSpell = new UndoRedoDBPtr<Spell>( owner );
		_periodicalSpell = new UndoRedoDBPtr<Spell>( owner );
		_stopSpell = new UndoRedoDBPtr<Spell>( owner );
		_cancelSpell = new UndoRedoDBPtr<Spell>( owner );
		_period = new UndoRedo<float>( owner, 0.0f );
		_interruptEvents = new UndoRedo<EBaseUnitEventFlags>( owner, EBaseUnitEventFlags.Zero );
		_cancelOnInterrupt = new UndoRedo<bool>( owner, false );
		_removeStartSpellEffectOnInterrupt = new UndoRedo<bool>( owner, false );
		ExecutableFloatString __scaleWhenInterrupted = new ExecutableFloatString(); // Construct default object for scaleWhenInterrupted
		__scaleWhenInterrupted.sString = "1.0f";
		_scaleWhenInterrupted = new ExecutableFloatString( owner, __scaleWhenInterrupted );
		_cancelOnDisable = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_channelingType.Changed += FireChangedEvent;
		_applicatorsOnSelf.Changed += FireChangedEvent;
		_startSpell.Changed += FireChangedEvent;
		_periodicalSpell.Changed += FireChangedEvent;
		_stopSpell.Changed += FireChangedEvent;
		_cancelSpell.Changed += FireChangedEvent;
		_period.Changed += FireChangedEvent;
		_interruptEvents.Changed += FireChangedEvent;
		_cancelOnInterrupt.Changed += FireChangedEvent;
		_removeStartSpellEffectOnInterrupt.Changed += FireChangedEvent;
		_scaleWhenInterrupted.Changed += FireChangedEvent;
		_cancelOnDisable.Changed += FireChangedEvent;
	}

	public ChannellingApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ChannellingApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChannellingApplicator" );
		targetSelector = source.targetSelector;
		channelingType = source.channelingType;
		applicatorsOnSelf = source.applicatorsOnSelf;
		startSpell = source.startSpell;
		periodicalSpell = source.periodicalSpell;
		stopSpell = source.stopSpell;
		cancelSpell = source.cancelSpell;
		period = source.period;
		interruptEvents = source.interruptEvents;
		cancelOnInterrupt = source.cancelOnInterrupt;
		removeStartSpellEffectOnInterrupt = source.removeStartSpellEffectOnInterrupt;
		scaleWhenInterrupted = source.scaleWhenInterrupted;
		cancelOnDisable = source.cancelOnDisable;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChannellingApplicator source = _source as ChannellingApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChannellingApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChannellingApplicator newParent = rawParent == null ? null : rawParent.Get<ChannellingApplicator>();
		if ( newParent == null && _newParent is ChannellingApplicator )
			newParent = _newParent as ChannellingApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_channelingType.SetParent( newParent == null ? null : newParent._channelingType );
		_applicatorsOnSelf.SetParent( newParent == null ? null : newParent._applicatorsOnSelf );
		_startSpell.SetParent( newParent == null ? null : newParent._startSpell );
		_periodicalSpell.SetParent( newParent == null ? null : newParent._periodicalSpell );
		_stopSpell.SetParent( newParent == null ? null : newParent._stopSpell );
		_cancelSpell.SetParent( newParent == null ? null : newParent._cancelSpell );
		_period.SetParent( newParent == null ? null : newParent._period );
		_interruptEvents.SetParent( newParent == null ? null : newParent._interruptEvents );
		_cancelOnInterrupt.SetParent( newParent == null ? null : newParent._cancelOnInterrupt );
		_removeStartSpellEffectOnInterrupt.SetParent( newParent == null ? null : newParent._removeStartSpellEffectOnInterrupt );
		_scaleWhenInterrupted.SetParent( newParent == null ? null : newParent._scaleWhenInterrupted );
		_cancelOnDisable.SetParent( newParent == null ? null : newParent._cancelOnDisable );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_channelingType.Reset();
		_applicatorsOnSelf.Reset();
		_startSpell.Reset();
		_periodicalSpell.Reset();
		_stopSpell.Reset();
		_cancelSpell.Reset();
		_period.Reset();
		_interruptEvents.Reset();
		_cancelOnInterrupt.Reset();
		_removeStartSpellEffectOnInterrupt.Reset();
		_scaleWhenInterrupted.Reset();
		_cancelOnDisable.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _channelingType.IsDerivedFromParent()
			&& _applicatorsOnSelf.IsDerivedFromParent()
			&& _startSpell.IsDerivedFromParent()
			&& _periodicalSpell.IsDerivedFromParent()
			&& _stopSpell.IsDerivedFromParent()
			&& _cancelSpell.IsDerivedFromParent()
			&& _period.IsDerivedFromParent()
			&& _interruptEvents.IsDerivedFromParent()
			&& _cancelOnInterrupt.IsDerivedFromParent()
			&& _removeStartSpellEffectOnInterrupt.IsDerivedFromParent()
			&& _scaleWhenInterrupted.IsDerivedFromParent()
			&& _cancelOnDisable.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "channelingType" )
			_channelingType.Reset();
		else if ( fieldName == "applicatorsOnSelf" )
			_applicatorsOnSelf.Reset();
		else if ( fieldName == "startSpell" )
			_startSpell.Reset();
		else if ( fieldName == "periodicalSpell" )
			_periodicalSpell.Reset();
		else if ( fieldName == "stopSpell" )
			_stopSpell.Reset();
		else if ( fieldName == "cancelSpell" )
			_cancelSpell.Reset();
		else if ( fieldName == "period" )
			_period.Reset();
		else if ( fieldName == "interruptEvents" )
			_interruptEvents.Reset();
		else if ( fieldName == "cancelOnInterrupt" )
			_cancelOnInterrupt.Reset();
		else if ( fieldName == "removeStartSpellEffectOnInterrupt" )
			_removeStartSpellEffectOnInterrupt.Reset();
		else if ( fieldName == "scaleWhenInterrupted" )
			_scaleWhenInterrupted.Reset();
		else if ( fieldName == "cancelOnDisable" )
			_cancelOnDisable.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "channelingType" )
			return _channelingType.IsDerivedFromParent();
		if ( fieldName == "applicatorsOnSelf" )
			return _applicatorsOnSelf.IsDerivedFromParent();
		if ( fieldName == "startSpell" )
			return _startSpell.IsDerivedFromParent();
		if ( fieldName == "periodicalSpell" )
			return _periodicalSpell.IsDerivedFromParent();
		if ( fieldName == "stopSpell" )
			return _stopSpell.IsDerivedFromParent();
		if ( fieldName == "cancelSpell" )
			return _cancelSpell.IsDerivedFromParent();
		if ( fieldName == "period" )
			return _period.IsDerivedFromParent();
		if ( fieldName == "interruptEvents" )
			return _interruptEvents.IsDerivedFromParent();
		if ( fieldName == "cancelOnInterrupt" )
			return _cancelOnInterrupt.IsDerivedFromParent();
		if ( fieldName == "removeStartSpellEffectOnInterrupt" )
			return _removeStartSpellEffectOnInterrupt.IsDerivedFromParent();
		if ( fieldName == "scaleWhenInterrupted" )
			return _scaleWhenInterrupted.IsDerivedFromParent();
		if ( fieldName == "cancelOnDisable" )
			return _cancelOnDisable.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFCheckConditionTargetSelector", "PFAITargetSelectors.h")]
[TypeId(0x9A9C5C42)]
[UseTypeName("TGSL")]
public class CheckConditionTargetSelector : MultipleTargetSelector
{
	private UndoRedoDBPtr<CheckConditionTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<CheckConditionTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;
	private ExecutableBoolString _condition;
	private ExecutableIntString _minTargetsNumber;

	[Description( "Селектор, чьи цели выдаем, если условие выполнено" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Какие цели отбирать для проверки" )]
	public ExecutableBoolString condition { get { return _condition; } set { _condition.Assign( value ); } }

	[Description( "Если отобрано меньше целей - не выбирать ни одной" )]
	public ExecutableIntString minTargetsNumber { get { return _minTargetsNumber; } set { _minTargetsNumber.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CheckConditionTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		ExecutableBoolString __condition = new ExecutableBoolString(); // Construct default object for condition
		__condition.sString = "true";
		_condition = new ExecutableBoolString( owner, __condition );
		_minTargetsNumber = new ExecutableIntString( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_condition.Changed += FireChangedEvent;
		_minTargetsNumber.Changed += FireChangedEvent;
	}

	public CheckConditionTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( CheckConditionTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CheckConditionTargetSelector" );
		targetSelector = source.targetSelector;
		condition = source.condition;
		minTargetsNumber = source.minTargetsNumber;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CheckConditionTargetSelector source = _source as CheckConditionTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CheckConditionTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CheckConditionTargetSelector newParent = rawParent == null ? null : rawParent.Get<CheckConditionTargetSelector>();
		if ( newParent == null && _newParent is CheckConditionTargetSelector )
			newParent = _newParent as CheckConditionTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_condition.SetParent( newParent == null ? null : newParent._condition );
		_minTargetsNumber.SetParent( newParent == null ? null : newParent._minTargetsNumber );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_condition.Reset();
		_minTargetsNumber.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _condition.IsDerivedFromParent()
			&& _minTargetsNumber.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "condition" )
			_condition.Reset();
		else if ( fieldName == "minTargetsNumber" )
			_minTargetsNumber.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
		if ( fieldName == "minTargetsNumber" )
			return _minTargetsNumber.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Create", "NWorld::PFApplCloneHero", "PFApplSummon.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E724380)]
[UseTypeName("APLR")]
public class CloneHeroApplicator : BaseApplicator
{
	private UndoRedoDBPtr<CloneHeroApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<CloneHeroApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicators;
	private ExecutableFloatString _lifeTime;
	private ExecutableFloatString _followRange;
	private UndoRedo<ECloneFlags> _flags;
	private UndoRedoDBPtr<UnitTargetingParameters> _targetingParams;
	private ExecutableIntString _maxCount;
	private UndoRedo<string> _summonGroupName;
	private SpawnStats _spawnStats;
	private ExecutableFloatString _takeModDmg;
	private UndoRedo<ESpellTarget> _takeTypeUnit;

	[Description( "Список аппликаторов, который ляжет на копию" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	[Description( "Life time of buff (in seconds); specify -1 as infinity" )]
	public ExecutableFloatString lifeTime { get { return _lifeTime; } set { _lifeTime.Assign( value ); } }

	[Description( "Максимальное расстояние, на котором клон следует за хозяином; <= 0 - не переопределять" )]
	public ExecutableFloatString followRange { get { return _followRange; } set { _followRange.Assign( value ); } }

	[Description( "Дополнительнае настройки" )]
	public ECloneFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[Description( "(вариант MakeSlave) Целеуказание клона" )]
	public DBPtr<UnitTargetingParameters> targetingParams { get { return _targetingParams.Get(); } set { _targetingParams.Set( value ); } }

	[Description( "(вариант MakeSlave) Максимум склонированных героев; -1 - предел не меняется" )]
	public ExecutableIntString maxCount { get { return _maxCount; } set { _maxCount.Assign( value ); } }

	[Description( "Имя группы суммонов к которой приписать" )]
	public string summonGroupName { get { return _summonGroupName.Get(); } set { _summonGroupName.Set( value ); } }

	[Description( "Life and energy at spawn time" )]
	public SpawnStats spawnStats { get { return _spawnStats; } set { _spawnStats.Assign( value ); } }

	[Description( "Additional damage's multiplier" )]
	public ExecutableFloatString takeModDmg { get { return _takeModDmg; } set { _takeModDmg.Assign( value ); } }

	[Description( "Flags to specify targets of the takeModDmg" )]
	public ESpellTarget takeTypeUnit { get { return _takeTypeUnit.Get(); } set { _takeTypeUnit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CloneHeroApplicator>(owner);
		_applicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		ExecutableFloatString __lifeTime = new ExecutableFloatString(); // Construct default object for lifeTime
		__lifeTime.sString = "-1.0";
		_lifeTime = new ExecutableFloatString( owner, __lifeTime );
		ExecutableFloatString __followRange = new ExecutableFloatString(); // Construct default object for followRange
		__followRange.sString = "-1.0";
		_followRange = new ExecutableFloatString( owner, __followRange );
		_flags = new UndoRedo<ECloneFlags>( owner, ECloneFlags.PlaySummonEffect | ECloneFlags.DoLevelUp | ECloneFlags.GhostMove );
		_targetingParams = new UndoRedoDBPtr<UnitTargetingParameters>( owner );
		ExecutableIntString __maxCount = new ExecutableIntString(); // Construct default object for maxCount
		__maxCount.sString = "1";
		_maxCount = new ExecutableIntString( owner, __maxCount );
		_summonGroupName = new UndoRedo<string>( owner, string.Empty );
		SpawnStats __spawnStats = new SpawnStats(); // Construct default object for spawnStats
		__spawnStats.life.sString = "-1.0";
		__spawnStats.energy.sString = "-1.0";
		_spawnStats = new SpawnStats( owner, __spawnStats );
		ExecutableFloatString __takeModDmg = new ExecutableFloatString(); // Construct default object for takeModDmg
		__takeModDmg.sString = "1.0f";
		_takeModDmg = new ExecutableFloatString( owner, __takeModDmg );
		_takeTypeUnit = new UndoRedo<ESpellTarget>( owner, ESpellTarget.VulnerableTargetsOnly | ESpellTarget.All );
		___parent.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		_followRange.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_targetingParams.Changed += FireChangedEvent;
		_maxCount.Changed += FireChangedEvent;
		_summonGroupName.Changed += FireChangedEvent;
		_spawnStats.Changed += FireChangedEvent;
		_takeModDmg.Changed += FireChangedEvent;
		_takeTypeUnit.Changed += FireChangedEvent;
	}

	public CloneHeroApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( CloneHeroApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CloneHeroApplicator" );
		applicators = source.applicators;
		lifeTime = source.lifeTime;
		followRange = source.followRange;
		flags = source.flags;
		targetingParams = source.targetingParams;
		maxCount = source.maxCount;
		summonGroupName = source.summonGroupName;
		spawnStats = source.spawnStats;
		takeModDmg = source.takeModDmg;
		takeTypeUnit = source.takeTypeUnit;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CloneHeroApplicator source = _source as CloneHeroApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CloneHeroApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CloneHeroApplicator newParent = rawParent == null ? null : rawParent.Get<CloneHeroApplicator>();
		if ( newParent == null && _newParent is CloneHeroApplicator )
			newParent = _newParent as CloneHeroApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_followRange.SetParent( newParent == null ? null : newParent._followRange );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_targetingParams.SetParent( newParent == null ? null : newParent._targetingParams );
		_maxCount.SetParent( newParent == null ? null : newParent._maxCount );
		_summonGroupName.SetParent( newParent == null ? null : newParent._summonGroupName );
		_spawnStats.SetParent( newParent == null ? null : newParent._spawnStats );
		_takeModDmg.SetParent( newParent == null ? null : newParent._takeModDmg );
		_takeTypeUnit.SetParent( newParent == null ? null : newParent._takeTypeUnit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_applicators.Reset();
		_lifeTime.Reset();
		_followRange.Reset();
		_flags.Reset();
		_targetingParams.Reset();
		_maxCount.Reset();
		_summonGroupName.Reset();
		_spawnStats.Reset();
		_takeModDmg.Reset();
		_takeTypeUnit.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_applicators.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			&& _followRange.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _targetingParams.IsDerivedFromParent()
			&& _maxCount.IsDerivedFromParent()
			&& _summonGroupName.IsDerivedFromParent()
			&& _spawnStats.IsDerivedFromParent()
			&& _takeModDmg.IsDerivedFromParent()
			&& _takeTypeUnit.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "applicators" )
			_applicators.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "followRange" )
			_followRange.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "targetingParams" )
			_targetingParams.Reset();
		else if ( fieldName == "maxCount" )
			_maxCount.Reset();
		else if ( fieldName == "summonGroupName" )
			_summonGroupName.Reset();
		else if ( fieldName == "spawnStats" )
			_spawnStats.Reset();
		else if ( fieldName == "takeModDmg" )
			_takeModDmg.Reset();
		else if ( fieldName == "takeTypeUnit" )
			_takeTypeUnit.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "followRange" )
			return _followRange.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "targetingParams" )
			return _targetingParams.IsDerivedFromParent();
		if ( fieldName == "maxCount" )
			return _maxCount.IsDerivedFromParent();
		if ( fieldName == "summonGroupName" )
			return _summonGroupName.IsDerivedFromParent();
		if ( fieldName == "spawnStats" )
			return _spawnStats.IsDerivedFromParent();
		if ( fieldName == "takeModDmg" )
			return _takeModDmg.IsDerivedFromParent();
		if ( fieldName == "takeTypeUnit" )
			return _takeTypeUnit.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x9E6C82C1)]
[UseTypeName("TGSL")]
public class SingleTargetSelector : TargetSelector
{
	private UndoRedoDBPtr<SingleTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<SingleTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SingleTargetSelector>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public SingleTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( SingleTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SingleTargetSelector" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SingleTargetSelector source = _source as SingleTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SingleTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SingleTargetSelector newParent = rawParent == null ? null : rawParent.Get<SingleTargetSelector>();
		if ( newParent == null && _newParent is SingleTargetSelector )
			newParent = _newParent as SingleTargetSelector;
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

[FactoryImpl("Check", "NWorld::PFAbilityData", "PFCastLimitations.h", CreateFunction = "NWorld::CheckConditionLimitation")]
[TypeId(0x9E71CB81)]
[UseTypeName("ABCL")]
public class ConditionCastLimitation : CastLimitation
{
	private UndoRedoDBPtr<ConditionCastLimitation> ___parent;
	[HideInOutliner]
	public new DBPtr<ConditionCastLimitation> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableBoolString _condition;

	[Description( "Condition to check validity of cast" )]
	public ExecutableBoolString condition { get { return _condition; } set { _condition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ConditionCastLimitation>(owner);
		ExecutableBoolString __condition = new ExecutableBoolString(); // Construct default object for condition
		__condition.sString = "true";
		_condition = new ExecutableBoolString( owner, __condition );
		___parent.Changed += FireChangedEvent;
		_condition.Changed += FireChangedEvent;
	}

	public ConditionCastLimitation()
	{
		Initialize( this );
	}
	private void AssignSelf( ConditionCastLimitation source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ConditionCastLimitation" );
		condition = source.condition;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ConditionCastLimitation source = _source as ConditionCastLimitation;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConditionCastLimitation" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ConditionCastLimitation newParent = rawParent == null ? null : rawParent.Get<ConditionCastLimitation>();
		if ( newParent == null && _newParent is ConditionCastLimitation )
			newParent = _newParent as ConditionCastLimitation;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_condition.SetParent( newParent == null ? null : newParent._condition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_condition.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_condition.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "condition" )
			_condition.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
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
public class ConditionFormula : DBResource
{
	private UndoRedoDBPtr<ConditionFormula> ___parent;
	[HideInOutliner]
	public new DBPtr<ConditionFormula> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _name;
	private ExecutableBoolString _condition;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public ExecutableBoolString condition { get { return _condition; } set { _condition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ConditionFormula>(owner);
		_name = new UndoRedo<string>( owner, string.Empty );
		ExecutableBoolString __condition = new ExecutableBoolString(); // Construct default object for condition
		__condition.sString = "true";
		_condition = new ExecutableBoolString( owner, __condition );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_condition.Changed += FireChangedEvent;
	}

	public ConditionFormula()
	{
		Initialize( this );
	}
	private void AssignSelf( ConditionFormula source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ConditionFormula" );
		name = source.name;
		condition = source.condition;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ConditionFormula source = _source as ConditionFormula;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConditionFormula" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ConditionFormula newParent = rawParent == null ? null : rawParent.Get<ConditionFormula>();
		if ( newParent == null && _newParent is ConditionFormula )
			newParent = _newParent as ConditionFormula;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		_condition.SetParent( newParent == null ? null : newParent._condition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		_condition.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _condition.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "condition" )
			_condition.Reset();
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
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFConditionTargetSelector", "PFTargetSelector.h")]
[TypeId(0x2B7BB4C0)]
[UseTypeName("TGSL")]
public class ConditionTargetSelector : MultipleTargetSelector
{
	private UndoRedoDBPtr<ConditionTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<ConditionTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;
	private ExecutableBoolString _condition;

	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Selection condition" )]
	public ExecutableBoolString condition { get { return _condition; } set { _condition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ConditionTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		ExecutableBoolString __condition = new ExecutableBoolString(); // Construct default object for condition
		__condition.sString = "true";
		_condition = new ExecutableBoolString( owner, __condition );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_condition.Changed += FireChangedEvent;
	}

	public ConditionTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( ConditionTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ConditionTargetSelector" );
		targetSelector = source.targetSelector;
		condition = source.condition;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ConditionTargetSelector source = _source as ConditionTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConditionTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ConditionTargetSelector newParent = rawParent == null ? null : rawParent.Get<ConditionTargetSelector>();
		if ( newParent == null && _newParent is ConditionTargetSelector )
			newParent = _newParent as ConditionTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_condition.SetParent( newParent == null ? null : newParent._condition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_condition.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _condition.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "condition" )
			_condition.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFConvertTargetToLand", "PFTargetSelector.h")]
[TypeId(0x9E71EBC1)]
[UseTypeName("TGSL")]
public class ConvertTargetToLand : SingleTargetSelector
{
	private UndoRedoDBPtr<ConvertTargetToLand> ___parent;
	[HideInOutliner]
	public new DBPtr<ConvertTargetToLand> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<TargetToLandMode> _aggregateMode;
	private UndoRedoDBPtr<TargetSelector> _targetSelector;

	[Description( "Метод преобразования нескольких целей в позицию на земле" )]
	public TargetToLandMode aggregateMode { get { return _aggregateMode.Get(); } set { _aggregateMode.Set( value ); } }

	[Description( "Target selector to select from" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ConvertTargetToLand>(owner);
		_aggregateMode = new UndoRedo<TargetToLandMode>( owner, TargetToLandMode.First );
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_aggregateMode.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public ConvertTargetToLand()
	{
		Initialize( this );
	}
	private void AssignSelf( ConvertTargetToLand source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ConvertTargetToLand" );
		aggregateMode = source.aggregateMode;
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ConvertTargetToLand source = _source as ConvertTargetToLand;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ConvertTargetToLand" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ConvertTargetToLand newParent = rawParent == null ? null : rawParent.Get<ConvertTargetToLand>();
		if ( newParent == null && _newParent is ConvertTargetToLand )
			newParent = _newParent as ConvertTargetToLand;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_aggregateMode.SetParent( newParent == null ? null : newParent._aggregateMode );
		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_aggregateMode.Reset();
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_aggregateMode.IsDerivedFromParent()
			&& _targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "aggregateMode" )
			_aggregateMode.Reset();
		else if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "aggregateMode" )
			return _aggregateMode.IsDerivedFromParent();
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFCountingTargetSelector", "PFTargetSelector.h")]
[TypeId(0xE776A5C0)]
[UseTypeName("TGSL")]
public class CountingTargetSelector : MultipleTargetSelector
{
	private UndoRedoDBPtr<CountingTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<CountingTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;
	private ExecutableIntString _targetsNumber;
	private UndoRedo<bool> _heroesFirst;
	private UndoRedo<bool> _enableSorting;
	private ExecutableFloatString _sortingValue;
	private UndoRedo<ESortingOrder> _order;

	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Число целей" )]
	public ExecutableIntString targetsNumber { get { return _targetsNumber; } set { _targetsNumber.Assign( value ); } }

	[Description( "Выдавать героев в первую очередь" )]
	public bool heroesFirst { get { return _heroesFirst.Get(); } set { _heroesFirst.Set( value ); } }

	[Description( "Сортировать результаты по значению" )]
	public bool enableSorting { get { return _enableSorting.Get(); } set { _enableSorting.Set( value ); } }

	[Description( "Контрольное значение сортировки" )]
	public ExecutableFloatString sortingValue { get { return _sortingValue; } set { _sortingValue.Assign( value ); } }

	[Description( "Порядок сортировки" )]
	public ESortingOrder order { get { return _order.Get(); } set { _order.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CountingTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		ExecutableIntString __targetsNumber = new ExecutableIntString(); // Construct default object for targetsNumber
		__targetsNumber.sString = "1";
		_targetsNumber = new ExecutableIntString( owner, __targetsNumber );
		_heroesFirst = new UndoRedo<bool>( owner, false );
		_enableSorting = new UndoRedo<bool>( owner, false );
		ExecutableFloatString __sortingValue = new ExecutableFloatString(); // Construct default object for sortingValue
		__sortingValue.sString = "1";
		_sortingValue = new ExecutableFloatString( owner, __sortingValue );
		_order = new UndoRedo<ESortingOrder>( owner, ESortingOrder.Decreasing );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_targetsNumber.Changed += FireChangedEvent;
		_heroesFirst.Changed += FireChangedEvent;
		_enableSorting.Changed += FireChangedEvent;
		_sortingValue.Changed += FireChangedEvent;
		_order.Changed += FireChangedEvent;
	}

	public CountingTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( CountingTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CountingTargetSelector" );
		targetSelector = source.targetSelector;
		targetsNumber = source.targetsNumber;
		heroesFirst = source.heroesFirst;
		enableSorting = source.enableSorting;
		sortingValue = source.sortingValue;
		order = source.order;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CountingTargetSelector source = _source as CountingTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CountingTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CountingTargetSelector newParent = rawParent == null ? null : rawParent.Get<CountingTargetSelector>();
		if ( newParent == null && _newParent is CountingTargetSelector )
			newParent = _newParent as CountingTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_targetsNumber.SetParent( newParent == null ? null : newParent._targetsNumber );
		_heroesFirst.SetParent( newParent == null ? null : newParent._heroesFirst );
		_enableSorting.SetParent( newParent == null ? null : newParent._enableSorting );
		_sortingValue.SetParent( newParent == null ? null : newParent._sortingValue );
		_order.SetParent( newParent == null ? null : newParent._order );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_targetsNumber.Reset();
		_heroesFirst.Reset();
		_enableSorting.Reset();
		_sortingValue.Reset();
		_order.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _targetsNumber.IsDerivedFromParent()
			&& _heroesFirst.IsDerivedFromParent()
			&& _enableSorting.IsDerivedFromParent()
			&& _sortingValue.IsDerivedFromParent()
			&& _order.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "targetsNumber" )
			_targetsNumber.Reset();
		else if ( fieldName == "heroesFirst" )
			_heroesFirst.Reset();
		else if ( fieldName == "enableSorting" )
			_enableSorting.Reset();
		else if ( fieldName == "sortingValue" )
			_sortingValue.Reset();
		else if ( fieldName == "order" )
			_order.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "targetsNumber" )
			return _targetsNumber.IsDerivedFromParent();
		if ( fieldName == "heroesFirst" )
			return _heroesFirst.IsDerivedFromParent();
		if ( fieldName == "enableSorting" )
			return _enableSorting.IsDerivedFromParent();
		if ( fieldName == "sortingValue" )
			return _sortingValue.IsDerivedFromParent();
		if ( fieldName == "order" )
			return _order.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplCreateGlyph", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE77AF500)]
[UseTypeName("APLR")]
public class CreateGlyphApplicator : BaseApplicator
{
	private UndoRedoDBPtr<CreateGlyphApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<CreateGlyphApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Glyph> _glyph;
	private UndoRedo<float> _distance;
	private UndoRedo<float> _angle;
	private UndoRedo<float> _radius;
	private UndoRedo<bool> _angleIsRelative;
	private Vec2 _absolutePosition;
	private UndoRedo<string> _scriptName;

	[Description( "Glyph to create" )]
	public DBPtr<Glyph> glyph { get { return _glyph.Get(); } set { _glyph.Set( value ); } }

	[Description( "Distance from parent's position" )]
	public float distance { get { return _distance.Get(); } set { _distance.Set( value ); } }

	[Description( "Angle from parent's direction or from [1,0] direction on map (ccw,deg)" )]
	public float angle { get { return _angle.Get(); } set { _angle.Set( value ); } }

	[Description( "Radius for free place searching" )]
	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	[Description( "Angle is relative to the parent's direction" )]
	public bool angleIsRelative { get { return _angleIsRelative.Get(); } set { _angleIsRelative.Set( value ); } }

	[Description( "Absolute position instead distance, angle and radius parameters" )]
	public Vec2 absolutePosition { get { return _absolutePosition; } set { _absolutePosition.Assign( value ); } }

	[Description( "Script name to assign" )]
	public string scriptName { get { return _scriptName.Get(); } set { _scriptName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CreateGlyphApplicator>(owner);
		_glyph = new UndoRedoDBPtr<Glyph>( owner );
		_distance = new UndoRedo<float>( owner, -1.0f );
		_angle = new UndoRedo<float>( owner, -1.0f );
		_radius = new UndoRedo<float>( owner, -1.0f );
		_angleIsRelative = new UndoRedo<bool>( owner, false );
		_absolutePosition = new Vec2( owner );
		_scriptName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_glyph.Changed += FireChangedEvent;
		_distance.Changed += FireChangedEvent;
		_angle.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_angleIsRelative.Changed += FireChangedEvent;
		_absolutePosition.Changed += FireChangedEvent;
		_scriptName.Changed += FireChangedEvent;
	}

	public CreateGlyphApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( CreateGlyphApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CreateGlyphApplicator" );
		glyph = source.glyph;
		distance = source.distance;
		angle = source.angle;
		radius = source.radius;
		angleIsRelative = source.angleIsRelative;
		absolutePosition = source.absolutePosition;
		scriptName = source.scriptName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CreateGlyphApplicator source = _source as CreateGlyphApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreateGlyphApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CreateGlyphApplicator newParent = rawParent == null ? null : rawParent.Get<CreateGlyphApplicator>();
		if ( newParent == null && _newParent is CreateGlyphApplicator )
			newParent = _newParent as CreateGlyphApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_glyph.SetParent( newParent == null ? null : newParent._glyph );
		_distance.SetParent( newParent == null ? null : newParent._distance );
		_angle.SetParent( newParent == null ? null : newParent._angle );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		_angleIsRelative.SetParent( newParent == null ? null : newParent._angleIsRelative );
		_absolutePosition.SetParent( newParent == null ? null : newParent._absolutePosition );
		_scriptName.SetParent( newParent == null ? null : newParent._scriptName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_glyph.Reset();
		_distance.Reset();
		_angle.Reset();
		_radius.Reset();
		_angleIsRelative.Reset();
		_absolutePosition.Reset();
		_scriptName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_glyph.IsDerivedFromParent()
			&& _distance.IsDerivedFromParent()
			&& _angle.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			&& _angleIsRelative.IsDerivedFromParent()
			&& _absolutePosition.IsDerivedFromParent()
			&& _scriptName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "glyph" )
			_glyph.Reset();
		else if ( fieldName == "distance" )
			_distance.Reset();
		else if ( fieldName == "angle" )
			_angle.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else if ( fieldName == "angleIsRelative" )
			_angleIsRelative.Reset();
		else if ( fieldName == "absolutePosition" )
			_absolutePosition.Reset();
		else if ( fieldName == "scriptName" )
			_scriptName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "glyph" )
			return _glyph.IsDerivedFromParent();
		if ( fieldName == "distance" )
			return _distance.IsDerivedFromParent();
		if ( fieldName == "angle" )
			return _angle.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		if ( fieldName == "angleIsRelative" )
			return _angleIsRelative.IsDerivedFromParent();
		if ( fieldName == "absolutePosition" )
			return _absolutePosition.IsDerivedFromParent();
		if ( fieldName == "scriptName" )
			return _scriptName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(4)]
[FactoryImpl("Create", "NWorld::PFApplCreepBehaviourChange", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E677A81)]
[UseTypeName("APLR")]
public class CreepBehaviourChangeApplicator : BuffApplicator
{
	private UndoRedoDBPtr<CreepBehaviourChangeApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<CreepBehaviourChangeApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EBehaviourChangeFlags> _behaviourChangeFlags;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicators;
	private UndoRedo<string> _summonGroupName;
	private UndoRedoDBPtr<SummonBehaviourBase> _behaviour;

	[Description( "Flags" )]
	public EBehaviourChangeFlags behaviourChangeFlags { get { return _behaviourChangeFlags.Get(); } set { _behaviourChangeFlags.Set( value ); } }

	[Description( "List of applicators that will be applied to changed unit" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	[Description( "Имя группы суммонов к которой приписать" )]
	public string summonGroupName { get { return _summonGroupName.Get(); } set { _summonGroupName.Set( value ); } }

	[Description( "Summoned unit behaviour" )]
	public DBPtr<SummonBehaviourBase> behaviour { get { return _behaviour.Get(); } set { _behaviour.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CreepBehaviourChangeApplicator>(owner);
		_behaviourChangeFlags = new UndoRedo<EBehaviourChangeFlags>( owner, EBehaviourChangeFlags.ChangeFaction );
		_applicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		_summonGroupName = new UndoRedo<string>( owner, string.Empty );
		_behaviour = new UndoRedoDBPtr<SummonBehaviourBase>( owner );
		___parent.Changed += FireChangedEvent;
		_behaviourChangeFlags.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
		_summonGroupName.Changed += FireChangedEvent;
		_behaviour.Changed += FireChangedEvent;
	}

	public CreepBehaviourChangeApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( CreepBehaviourChangeApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CreepBehaviourChangeApplicator" );
		behaviourChangeFlags = source.behaviourChangeFlags;
		applicators = source.applicators;
		summonGroupName = source.summonGroupName;
		behaviour = source.behaviour;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CreepBehaviourChangeApplicator source = _source as CreepBehaviourChangeApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepBehaviourChangeApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CreepBehaviourChangeApplicator newParent = rawParent == null ? null : rawParent.Get<CreepBehaviourChangeApplicator>();
		if ( newParent == null && _newParent is CreepBehaviourChangeApplicator )
			newParent = _newParent as CreepBehaviourChangeApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_behaviourChangeFlags.SetParent( newParent == null ? null : newParent._behaviourChangeFlags );
		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		_summonGroupName.SetParent( newParent == null ? null : newParent._summonGroupName );
		_behaviour.SetParent( newParent == null ? null : newParent._behaviour );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_behaviourChangeFlags.Reset();
		_applicators.Reset();
		_summonGroupName.Reset();
		_behaviour.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_behaviourChangeFlags.IsDerivedFromParent()
			&& _applicators.IsDerivedFromParent()
			&& _summonGroupName.IsDerivedFromParent()
			&& _behaviour.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "behaviourChangeFlags" )
			_behaviourChangeFlags.Reset();
		else if ( fieldName == "applicators" )
			_applicators.Reset();
		else if ( fieldName == "summonGroupName" )
			_summonGroupName.Reset();
		else if ( fieldName == "behaviour" )
			_behaviour.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "behaviourChangeFlags" )
			return _behaviourChangeFlags.IsDerivedFromParent();
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		if ( fieldName == "summonGroupName" )
			return _summonGroupName.IsDerivedFromParent();
		if ( fieldName == "behaviour" )
			return _behaviour.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplDamage", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B01)]
[UseTypeName("APLR")]
public class DamageApplicator : BaseApplicator
{
	private UndoRedoDBPtr<DamageApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<DamageApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _damage;
	private UndoRedo<EApplicatorDamageType> _damageType;
	private UndoRedo<EDamageMode> _damageMode;
	private UndoRedo<bool> _cancelInvisibility;
	private UndoRedoDBPtr<UIEvent> _uiEvent;
	private UndoRedo<float> _timeLimiter;

	[Description( "Damage to be dealt to target [Formula update: once]" )]
	public ExecutableFloatString damage { get { return _damage; } set { _damage.Assign( value ); } }

	[Description( "Damage type. Material/Energy - damage, Mana - mana-burn" )]
	public EApplicatorDamageType damageType { get { return _damageType.Get(); } set { _damageType.Set( value ); } }

	[Description( "ApplyDrains - apply life & energy drain, DontAttackBack - target willn't attack back if idle" )]
	public EDamageMode damageMode { get { return _damageMode.Get(); } set { _damageMode.Set( value ); } }

	[Description( "Cancel owner's invisibility" )]
	public bool cancelInvisibility { get { return _cancelInvisibility.Get(); } set { _cancelInvisibility.Set( value ); } }

	[Description( "UI Event" )]
	public DBPtr<UIEvent> uiEvent { get { return _uiEvent.Get(); } set { _uiEvent.Set( value ); } }

	[Description( "Limiter time for applicator [if -1.0 then don't check it]" )]
	public float timeLimiter { get { return _timeLimiter.Get(); } set { _timeLimiter.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DamageApplicator>(owner);
		ExecutableFloatString __damage = new ExecutableFloatString(); // Construct default object for damage
		__damage.sString = "0.0";
		_damage = new ExecutableFloatString( owner, __damage );
		_damageType = new UndoRedo<EApplicatorDamageType>( owner, EApplicatorDamageType.Material );
		_damageMode = new UndoRedo<EDamageMode>( owner, EDamageMode.Zero );
		_cancelInvisibility = new UndoRedo<bool>( owner, false );
		_uiEvent = new UndoRedoDBPtr<UIEvent>( owner );
		_timeLimiter = new UndoRedo<float>( owner, -1.0f );
		___parent.Changed += FireChangedEvent;
		_damage.Changed += FireChangedEvent;
		_damageType.Changed += FireChangedEvent;
		_damageMode.Changed += FireChangedEvent;
		_cancelInvisibility.Changed += FireChangedEvent;
		_uiEvent.Changed += FireChangedEvent;
		_timeLimiter.Changed += FireChangedEvent;
	}

	public DamageApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( DamageApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DamageApplicator" );
		damage = source.damage;
		damageType = source.damageType;
		damageMode = source.damageMode;
		cancelInvisibility = source.cancelInvisibility;
		uiEvent = source.uiEvent;
		timeLimiter = source.timeLimiter;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DamageApplicator source = _source as DamageApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DamageApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DamageApplicator newParent = rawParent == null ? null : rawParent.Get<DamageApplicator>();
		if ( newParent == null && _newParent is DamageApplicator )
			newParent = _newParent as DamageApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_damage.SetParent( newParent == null ? null : newParent._damage );
		_damageType.SetParent( newParent == null ? null : newParent._damageType );
		_damageMode.SetParent( newParent == null ? null : newParent._damageMode );
		_cancelInvisibility.SetParent( newParent == null ? null : newParent._cancelInvisibility );
		_uiEvent.SetParent( newParent == null ? null : newParent._uiEvent );
		_timeLimiter.SetParent( newParent == null ? null : newParent._timeLimiter );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_damage.Reset();
		_damageType.Reset();
		_damageMode.Reset();
		_cancelInvisibility.Reset();
		_uiEvent.Reset();
		_timeLimiter.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_damage.IsDerivedFromParent()
			&& _damageType.IsDerivedFromParent()
			&& _damageMode.IsDerivedFromParent()
			&& _cancelInvisibility.IsDerivedFromParent()
			&& _uiEvent.IsDerivedFromParent()
			&& _timeLimiter.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "damage" )
			_damage.Reset();
		else if ( fieldName == "damageType" )
			_damageType.Reset();
		else if ( fieldName == "damageMode" )
			_damageMode.Reset();
		else if ( fieldName == "cancelInvisibility" )
			_cancelInvisibility.Reset();
		else if ( fieldName == "uiEvent" )
			_uiEvent.Reset();
		else if ( fieldName == "timeLimiter" )
			_timeLimiter.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "damage" )
			return _damage.IsDerivedFromParent();
		if ( fieldName == "damageType" )
			return _damageType.IsDerivedFromParent();
		if ( fieldName == "damageMode" )
			return _damageMode.IsDerivedFromParent();
		if ( fieldName == "cancelInvisibility" )
			return _cancelInvisibility.IsDerivedFromParent();
		if ( fieldName == "uiEvent" )
			return _uiEvent.IsDerivedFromParent();
		if ( fieldName == "timeLimiter" )
			return _timeLimiter.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplDamageReflect", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B0A)]
[UseTypeName("APLR")]
public class DamageReflectApplicator : BuffApplicator
{
	private UndoRedoDBPtr<DamageReflectApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<DamageReflectApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _amountInPersent;

	[Category( "Damage reflection" )]
	public float amountInPersent { get { return _amountInPersent.Get(); } set { _amountInPersent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DamageReflectApplicator>(owner);
		_amountInPersent = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_amountInPersent.Changed += FireChangedEvent;
	}

	public DamageReflectApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( DamageReflectApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DamageReflectApplicator" );
		amountInPersent = source.amountInPersent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DamageReflectApplicator source = _source as DamageReflectApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DamageReflectApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DamageReflectApplicator newParent = rawParent == null ? null : rawParent.Get<DamageReflectApplicator>();
		if ( newParent == null && _newParent is DamageReflectApplicator )
			newParent = _newParent as DamageReflectApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_amountInPersent.SetParent( newParent == null ? null : newParent._amountInPersent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_amountInPersent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_amountInPersent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "amountInPersent" )
			_amountInPersent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "amountInPersent" )
			return _amountInPersent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFDamagingLinksTargetSelector", "PFAITargetSelectors.h")]
[TypeId(0x9A9C5CD0)]
[UseTypeName("TGSL")]
public class DamagingLinksTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<DamagingLinksTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<DamagingLinksTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _linkEndsSelector;
	private UndoRedoDBPtr<MultipleTargetSelector> _linkTargetsSelector;
	private ExecutableFloatString _moveRange;
	private ExecutableFloatString _minRangeFromLinkEnds;
	private ExecutableFloatString _maxRangeFromLinkEnds;

	[Description( "Селектор объектов, связанных с нами линками" )]
	public DBPtr<MultipleTargetSelector> linkEndsSelector { get { return _linkEndsSelector.Get(); } set { _linkEndsSelector.Set( value ); } }

	[Description( "Селектор, по которому линки бьют врагов" )]
	public DBPtr<MultipleTargetSelector> linkTargetsSelector { get { return _linkTargetsSelector.Get(); } set { _linkTargetsSelector.Set( value ); } }

	[Description( "Радиус от нас, на котором ищем цель" )]
	public ExecutableFloatString moveRange { get { return _moveRange; } set { _moveRange.Assign( value ); } }

	[Description( "Не приближаемся к концам линков ближе заданного" )]
	public ExecutableFloatString minRangeFromLinkEnds { get { return _minRangeFromLinkEnds; } set { _minRangeFromLinkEnds.Assign( value ); } }

	[Description( "Не отдаляемся от концов линков дальше заданного" )]
	public ExecutableFloatString maxRangeFromLinkEnds { get { return _maxRangeFromLinkEnds; } set { _maxRangeFromLinkEnds.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DamagingLinksTargetSelector>(owner);
		_linkEndsSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		_linkTargetsSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		ExecutableFloatString __moveRange = new ExecutableFloatString(); // Construct default object for moveRange
		__moveRange.sString = "0.0f";
		_moveRange = new ExecutableFloatString( owner, __moveRange );
		ExecutableFloatString __minRangeFromLinkEnds = new ExecutableFloatString(); // Construct default object for minRangeFromLinkEnds
		__minRangeFromLinkEnds.sString = "0.0f";
		_minRangeFromLinkEnds = new ExecutableFloatString( owner, __minRangeFromLinkEnds );
		ExecutableFloatString __maxRangeFromLinkEnds = new ExecutableFloatString(); // Construct default object for maxRangeFromLinkEnds
		__maxRangeFromLinkEnds.sString = "0.0f";
		_maxRangeFromLinkEnds = new ExecutableFloatString( owner, __maxRangeFromLinkEnds );
		___parent.Changed += FireChangedEvent;
		_linkEndsSelector.Changed += FireChangedEvent;
		_linkTargetsSelector.Changed += FireChangedEvent;
		_moveRange.Changed += FireChangedEvent;
		_minRangeFromLinkEnds.Changed += FireChangedEvent;
		_maxRangeFromLinkEnds.Changed += FireChangedEvent;
	}

	public DamagingLinksTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( DamagingLinksTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DamagingLinksTargetSelector" );
		linkEndsSelector = source.linkEndsSelector;
		linkTargetsSelector = source.linkTargetsSelector;
		moveRange = source.moveRange;
		minRangeFromLinkEnds = source.minRangeFromLinkEnds;
		maxRangeFromLinkEnds = source.maxRangeFromLinkEnds;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DamagingLinksTargetSelector source = _source as DamagingLinksTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DamagingLinksTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DamagingLinksTargetSelector newParent = rawParent == null ? null : rawParent.Get<DamagingLinksTargetSelector>();
		if ( newParent == null && _newParent is DamagingLinksTargetSelector )
			newParent = _newParent as DamagingLinksTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_linkEndsSelector.SetParent( newParent == null ? null : newParent._linkEndsSelector );
		_linkTargetsSelector.SetParent( newParent == null ? null : newParent._linkTargetsSelector );
		_moveRange.SetParent( newParent == null ? null : newParent._moveRange );
		_minRangeFromLinkEnds.SetParent( newParent == null ? null : newParent._minRangeFromLinkEnds );
		_maxRangeFromLinkEnds.SetParent( newParent == null ? null : newParent._maxRangeFromLinkEnds );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_linkEndsSelector.Reset();
		_linkTargetsSelector.Reset();
		_moveRange.Reset();
		_minRangeFromLinkEnds.Reset();
		_maxRangeFromLinkEnds.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_linkEndsSelector.IsDerivedFromParent()
			&& _linkTargetsSelector.IsDerivedFromParent()
			&& _moveRange.IsDerivedFromParent()
			&& _minRangeFromLinkEnds.IsDerivedFromParent()
			&& _maxRangeFromLinkEnds.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "linkEndsSelector" )
			_linkEndsSelector.Reset();
		else if ( fieldName == "linkTargetsSelector" )
			_linkTargetsSelector.Reset();
		else if ( fieldName == "moveRange" )
			_moveRange.Reset();
		else if ( fieldName == "minRangeFromLinkEnds" )
			_minRangeFromLinkEnds.Reset();
		else if ( fieldName == "maxRangeFromLinkEnds" )
			_maxRangeFromLinkEnds.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "linkEndsSelector" )
			return _linkEndsSelector.IsDerivedFromParent();
		if ( fieldName == "linkTargetsSelector" )
			return _linkTargetsSelector.IsDerivedFromParent();
		if ( fieldName == "moveRange" )
			return _moveRange.IsDerivedFromParent();
		if ( fieldName == "minRangeFromLinkEnds" )
			return _minRangeFromLinkEnds.IsDerivedFromParent();
		if ( fieldName == "maxRangeFromLinkEnds" )
			return _maxRangeFromLinkEnds.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplDayNightTransition", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x15CBF300)]
[UseTypeName("APLR")]
public class DayNightTransitionApplicator : BaseApplicator
{
	private UndoRedoDBPtr<DayNightTransitionApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<DayNightTransitionApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EDayNightState> _desiredState;
	private UndoRedo<float> _desiredStateFraction;

	public EDayNightState desiredState { get { return _desiredState.Get(); } set { _desiredState.Set( value ); } }

	[FloatMinMax(0, 1)]
	public float desiredStateFraction { get { return _desiredStateFraction.Get(); } set { _desiredStateFraction.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DayNightTransitionApplicator>(owner);
		_desiredState = new UndoRedo<EDayNightState>( owner, EDayNightState.Night );
		_desiredStateFraction = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_desiredState.Changed += FireChangedEvent;
		_desiredStateFraction.Changed += FireChangedEvent;
	}

	public DayNightTransitionApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( DayNightTransitionApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DayNightTransitionApplicator" );
		desiredState = source.desiredState;
		desiredStateFraction = source.desiredStateFraction;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DayNightTransitionApplicator source = _source as DayNightTransitionApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DayNightTransitionApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DayNightTransitionApplicator newParent = rawParent == null ? null : rawParent.Get<DayNightTransitionApplicator>();
		if ( newParent == null && _newParent is DayNightTransitionApplicator )
			newParent = _newParent as DayNightTransitionApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_desiredState.SetParent( newParent == null ? null : newParent._desiredState );
		_desiredStateFraction.SetParent( newParent == null ? null : newParent._desiredStateFraction );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_desiredState.Reset();
		_desiredStateFraction.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_desiredState.IsDerivedFromParent()
			&& _desiredStateFraction.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "desiredState" )
			_desiredState.Reset();
		else if ( fieldName == "desiredStateFraction" )
			_desiredStateFraction.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "desiredState" )
			return _desiredState.IsDerivedFromParent();
		if ( fieldName == "desiredStateFraction" )
			return _desiredStateFraction.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplDealedDamageConverter", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B0C)]
[UseTypeName("APLR")]
public class DealedDamageConverterApplicator : BaseApplicator
{
	private UndoRedoDBPtr<DealedDamageConverterApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<DealedDamageConverterApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _scale;
	private UndoRedo<float> _deltaTime;
	private UndoRedo<EHealTarget> _type;

	[Category( "DealedDamageConverter" )]
	[Description( "Dealed damage will be multiplied on this value" )]
	public float scale { get { return _scale.Get(); } set { _scale.Set( value ); } }

	[Description( "Applicators that dealed damage will be gathered within this time frame" )]
	public float deltaTime { get { return _deltaTime.Get(); } set { _deltaTime.Set( value ); } }

	[Description( "Type of healing: life or energy" )]
	public EHealTarget type { get { return _type.Get(); } set { _type.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DealedDamageConverterApplicator>(owner);
		_scale = new UndoRedo<float>( owner, 1.0f );
		_deltaTime = new UndoRedo<float>( owner, 3.0f );
		_type = new UndoRedo<EHealTarget>( owner, EHealTarget.Health );
		___parent.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
		_deltaTime.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
	}

	public DealedDamageConverterApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( DealedDamageConverterApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DealedDamageConverterApplicator" );
		scale = source.scale;
		deltaTime = source.deltaTime;
		type = source.type;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DealedDamageConverterApplicator source = _source as DealedDamageConverterApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DealedDamageConverterApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DealedDamageConverterApplicator newParent = rawParent == null ? null : rawParent.Get<DealedDamageConverterApplicator>();
		if ( newParent == null && _newParent is DealedDamageConverterApplicator )
			newParent = _newParent as DealedDamageConverterApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_scale.SetParent( newParent == null ? null : newParent._scale );
		_deltaTime.SetParent( newParent == null ? null : newParent._deltaTime );
		_type.SetParent( newParent == null ? null : newParent._type );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_scale.Reset();
		_deltaTime.Reset();
		_type.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_scale.IsDerivedFromParent()
			&& _deltaTime.IsDerivedFromParent()
			&& _type.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "scale" )
			_scale.Reset();
		else if ( fieldName == "deltaTime" )
			_deltaTime.Reset();
		else if ( fieldName == "type" )
			_type.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "scale" )
			return _scale.IsDerivedFromParent();
		if ( fieldName == "deltaTime" )
			return _deltaTime.IsDerivedFromParent();
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x0F664BC9)]
[UseTypeName("DFSC")]
public class DefaultFormulas : DBResource
{
	private UndoRedoDBPtr<DefaultFormulas> ___parent;
	[HideInOutliner]
	public new DBPtr<DefaultFormulas> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<ExecutableFloatString> _floatFormulas;
	private UndoRedoAssignableList<ExecutableBoolString> _boolFormulas;
	private UndoRedoAssignableList<ExecutableIntString> _intFormulas;

	public libdb.IChangeableList<ExecutableFloatString> floatFormulas { get { return _floatFormulas; } set { _floatFormulas.Assign( value ); } }

	public libdb.IChangeableList<ExecutableBoolString> boolFormulas { get { return _boolFormulas; } set { _boolFormulas.Assign( value ); } }

	public libdb.IChangeableList<ExecutableIntString> intFormulas { get { return _intFormulas; } set { _intFormulas.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DefaultFormulas>(owner);
		_floatFormulas = new UndoRedoAssignableList<ExecutableFloatString>( owner );
		_boolFormulas = new UndoRedoAssignableList<ExecutableBoolString>( owner );
		_intFormulas = new UndoRedoAssignableList<ExecutableIntString>( owner );
		___parent.Changed += FireChangedEvent;
		_floatFormulas.Changed += FireChangedEvent;
		_boolFormulas.Changed += FireChangedEvent;
		_intFormulas.Changed += FireChangedEvent;
	}

	public DefaultFormulas()
	{
		Initialize( this );
	}
	private void AssignSelf( DefaultFormulas source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DefaultFormulas" );
		floatFormulas = source.floatFormulas;
		boolFormulas = source.boolFormulas;
		intFormulas = source.intFormulas;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DefaultFormulas source = _source as DefaultFormulas;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DefaultFormulas" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DefaultFormulas newParent = rawParent == null ? null : rawParent.Get<DefaultFormulas>();
		if ( newParent == null && _newParent is DefaultFormulas )
			newParent = _newParent as DefaultFormulas;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_floatFormulas.SetParent( newParent == null ? null : newParent._floatFormulas );
		_boolFormulas.SetParent( newParent == null ? null : newParent._boolFormulas );
		_intFormulas.SetParent( newParent == null ? null : newParent._intFormulas );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_floatFormulas.Reset();
		_boolFormulas.Reset();
		_intFormulas.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_floatFormulas.IsDerivedFromParent()
			&& _boolFormulas.IsDerivedFromParent()
			&& _intFormulas.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "floatFormulas" )
			_floatFormulas.Reset();
		else if ( fieldName == "boolFormulas" )
			_boolFormulas.Reset();
		else if ( fieldName == "intFormulas" )
			_intFormulas.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "floatFormulas" )
			return _floatFormulas.IsDerivedFromParent();
		if ( fieldName == "boolFormulas" )
			return _boolFormulas.IsDerivedFromParent();
		if ( fieldName == "intFormulas" )
			return _intFormulas.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFDelayTargetSelector", "PFAITargetSelectors.h")]
[TypeId(0x9A9C5C41)]
[UseTypeName("TGSL")]
public class DelayTargetSelector : MultipleTargetSelector
{
	private UndoRedoDBPtr<DelayTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<DelayTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;
	private ExecutableFloatString _delay;

	[Description( "Селектор, чьи цели выдаем после задержки" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Время, в течении которого цель должна быть во вложенном селекторе, чтобы быть отданным этим селектором" )]
	public ExecutableFloatString delay { get { return _delay; } set { _delay.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DelayTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		ExecutableFloatString __delay = new ExecutableFloatString(); // Construct default object for delay
		__delay.sString = "0.0f";
		_delay = new ExecutableFloatString( owner, __delay );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_delay.Changed += FireChangedEvent;
	}

	public DelayTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( DelayTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DelayTargetSelector" );
		targetSelector = source.targetSelector;
		delay = source.delay;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DelayTargetSelector source = _source as DelayTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DelayTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DelayTargetSelector newParent = rawParent == null ? null : rawParent.Get<DelayTargetSelector>();
		if ( newParent == null && _newParent is DelayTargetSelector )
			newParent = _newParent as DelayTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_delay.SetParent( newParent == null ? null : newParent._delay );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_delay.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _delay.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "delay" )
			_delay.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "delay" )
			return _delay.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplDelegateDamage", "PFApplDelegateDamage.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE7873440)]
[UseTypeName("APLR")]
public class DelegateDamageApplicator : BuffApplicator
{
	private UndoRedoDBPtr<DelegateDamageApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<DelegateDamageApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _damageToDelegate;
	private ExecutableFloatString _damageToApply;
	private ExecutableFloatString _totalDamage;
	private UndoRedo<EDelegateDamageFlags> _flags;
	private UndoRedo<bool> _infiniteTotalDamage;
	private UndoRedo<bool> _ignoreDefences;
	private UndoRedo<bool> _forceDontAttackBack;
	private UndoRedoDBPtr<TargetSelector> _delegateTargets;
	private ExecutableBoolString _stopCondition;

	[Description( "Damage to delegate; use 'appl.vDamage' to access incoming damage" )]
	public ExecutableFloatString damageToDelegate { get { return _damageToDelegate; } set { _damageToDelegate.Assign( value ); } }

	[Description( "Damage to apply on receiver; use 'appl.vDamage' to access incoming damage" )]
	public ExecutableFloatString damageToApply { get { return _damageToApply; } set { _damageToApply.Assign( value ); } }

	[Description( "Total damage that can be delegated" )]
	public ExecutableFloatString totalDamage { get { return _totalDamage; } set { _totalDamage.Assign( value ); } }

	public EDelegateDamageFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[Description( "Total damage is infinite (ignores totalDamage formula)" )]
	public bool infiniteTotalDamage { get { return _infiniteTotalDamage.Get(); } set { _infiniteTotalDamage.Set( value ); } }

	[Description( "Delegated damage ignores defence" )]
	public bool ignoreDefences { get { return _ignoreDefences.Get(); } set { _ignoreDefences.Set( value ); } }

	[Description( "Delegated damage won't trigger aggro whether DontAttackBack flag is set for original damage or not" )]
	public bool forceDontAttackBack { get { return _forceDontAttackBack.Get(); } set { _forceDontAttackBack.Set( value ); } }

	[Description( "Targets to delegate damage to" )]
	public DBPtr<TargetSelector> delegateTargets { get { return _delegateTargets.Get(); } set { _delegateTargets.Set( value ); } }

	[Description( "Condition to stop after damage processing" )]
	public ExecutableBoolString stopCondition { get { return _stopCondition; } set { _stopCondition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DelegateDamageApplicator>(owner);
		ExecutableFloatString __damageToDelegate = new ExecutableFloatString(); // Construct default object for damageToDelegate
		__damageToDelegate.sString = "0.0f";
		_damageToDelegate = new ExecutableFloatString( owner, __damageToDelegate );
		ExecutableFloatString __damageToApply = new ExecutableFloatString(); // Construct default object for damageToApply
		__damageToApply.sString = "0.0f";
		_damageToApply = new ExecutableFloatString( owner, __damageToApply );
		ExecutableFloatString __totalDamage = new ExecutableFloatString(); // Construct default object for totalDamage
		__totalDamage.sString = "0.0f";
		_totalDamage = new ExecutableFloatString( owner, __totalDamage );
		_flags = new UndoRedo<EDelegateDamageFlags>( owner, (EDelegateDamageFlags)0 );
		_infiniteTotalDamage = new UndoRedo<bool>( owner, false );
		_ignoreDefences = new UndoRedo<bool>( owner, false );
		_forceDontAttackBack = new UndoRedo<bool>( owner, false );
		_delegateTargets = new UndoRedoDBPtr<TargetSelector>( owner );
		_stopCondition = new ExecutableBoolString( owner );
		___parent.Changed += FireChangedEvent;
		_damageToDelegate.Changed += FireChangedEvent;
		_damageToApply.Changed += FireChangedEvent;
		_totalDamage.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_infiniteTotalDamage.Changed += FireChangedEvent;
		_ignoreDefences.Changed += FireChangedEvent;
		_forceDontAttackBack.Changed += FireChangedEvent;
		_delegateTargets.Changed += FireChangedEvent;
		_stopCondition.Changed += FireChangedEvent;
	}

	public DelegateDamageApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( DelegateDamageApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DelegateDamageApplicator" );
		damageToDelegate = source.damageToDelegate;
		damageToApply = source.damageToApply;
		totalDamage = source.totalDamage;
		flags = source.flags;
		infiniteTotalDamage = source.infiniteTotalDamage;
		ignoreDefences = source.ignoreDefences;
		forceDontAttackBack = source.forceDontAttackBack;
		delegateTargets = source.delegateTargets;
		stopCondition = source.stopCondition;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DelegateDamageApplicator source = _source as DelegateDamageApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DelegateDamageApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DelegateDamageApplicator newParent = rawParent == null ? null : rawParent.Get<DelegateDamageApplicator>();
		if ( newParent == null && _newParent is DelegateDamageApplicator )
			newParent = _newParent as DelegateDamageApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_damageToDelegate.SetParent( newParent == null ? null : newParent._damageToDelegate );
		_damageToApply.SetParent( newParent == null ? null : newParent._damageToApply );
		_totalDamage.SetParent( newParent == null ? null : newParent._totalDamage );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_infiniteTotalDamage.SetParent( newParent == null ? null : newParent._infiniteTotalDamage );
		_ignoreDefences.SetParent( newParent == null ? null : newParent._ignoreDefences );
		_forceDontAttackBack.SetParent( newParent == null ? null : newParent._forceDontAttackBack );
		_delegateTargets.SetParent( newParent == null ? null : newParent._delegateTargets );
		_stopCondition.SetParent( newParent == null ? null : newParent._stopCondition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_damageToDelegate.Reset();
		_damageToApply.Reset();
		_totalDamage.Reset();
		_flags.Reset();
		_infiniteTotalDamage.Reset();
		_ignoreDefences.Reset();
		_forceDontAttackBack.Reset();
		_delegateTargets.Reset();
		_stopCondition.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_damageToDelegate.IsDerivedFromParent()
			&& _damageToApply.IsDerivedFromParent()
			&& _totalDamage.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _infiniteTotalDamage.IsDerivedFromParent()
			&& _ignoreDefences.IsDerivedFromParent()
			&& _forceDontAttackBack.IsDerivedFromParent()
			&& _delegateTargets.IsDerivedFromParent()
			&& _stopCondition.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "damageToDelegate" )
			_damageToDelegate.Reset();
		else if ( fieldName == "damageToApply" )
			_damageToApply.Reset();
		else if ( fieldName == "totalDamage" )
			_totalDamage.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "infiniteTotalDamage" )
			_infiniteTotalDamage.Reset();
		else if ( fieldName == "ignoreDefences" )
			_ignoreDefences.Reset();
		else if ( fieldName == "forceDontAttackBack" )
			_forceDontAttackBack.Reset();
		else if ( fieldName == "delegateTargets" )
			_delegateTargets.Reset();
		else if ( fieldName == "stopCondition" )
			_stopCondition.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "damageToDelegate" )
			return _damageToDelegate.IsDerivedFromParent();
		if ( fieldName == "damageToApply" )
			return _damageToApply.IsDerivedFromParent();
		if ( fieldName == "totalDamage" )
			return _totalDamage.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "infiniteTotalDamage" )
			return _infiniteTotalDamage.IsDerivedFromParent();
		if ( fieldName == "ignoreDefences" )
			return _ignoreDefences.IsDerivedFromParent();
		if ( fieldName == "forceDontAttackBack" )
			return _forceDontAttackBack.IsDerivedFromParent();
		if ( fieldName == "delegateTargets" )
			return _delegateTargets.IsDerivedFromParent();
		if ( fieldName == "stopCondition" )
			return _stopCondition.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Create", "NWorld::PFDispatch", "NWorld::PFDispatchCreateParams const &cp")]
[NonTerminal]
[TypeId(0xA0678C00)]
[UseTypeName("DSCH")]
public class Dispatch : DBResource
{
	private UndoRedoDBPtr<Dispatch> ___parent;
	[HideInOutliner]
	public new DBPtr<Dispatch> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<EffectBase>> _dispatchEffect;
	private UndoRedoAssignableList<DBPtr<EffectBase>> _applyEffect;
	private UndoRedo<EApplyEffectOrientation> _applyEffectOrientation;
	private UndoRedo<int> _applyEffectRandomAnglePoints;
	private UndoRedo<bool> _dieAfterApply;
	private UndoRedo<bool> _alwaysApply;
	private UndoRedo<bool> _applyEffectIgnoreVisibility;
	private UndoRedo<EDispatchFlags> _flags;

	[Description( "Effect that will be played in the position of dispatch (used by Linear and ByTime types)" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<EffectBase>> dispatchEffect { get { return _dispatchEffect; } set { _dispatchEffect.Assign( value ); } }

	[Description( "Effect that will be played on the target of the dispatch" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<EffectBase>> applyEffect { get { return _applyEffect; } set { _applyEffect.Assign( value ); } }

	public EApplyEffectOrientation applyEffectOrientation { get { return _applyEffectOrientation.Get(); } set { _applyEffectOrientation.Set( value ); } }

	[Description( "Number of points for discreet randomization of apply effect orientation (0 = continuos random)" )]
	public int applyEffectRandomAnglePoints { get { return _applyEffectRandomAnglePoints.Get(); } set { _applyEffectRandomAnglePoints.Set( value ); } }

	[Description( "If false dispatch will remain after apply. Someone else should kill it eventually." )]
	public bool dieAfterApply { get { return _dieAfterApply.Get(); } set { _dieAfterApply.Set( value ); } }

	[Description( "Skip CanApplyDispatch check" )]
	public bool alwaysApply { get { return _alwaysApply.Get(); } set { _alwaysApply.Set( value ); } }

	[Description( "Ignore target visibility dispatch check for applyEffect. False is default" )]
	public bool applyEffectIgnoreVisibility { get { return _applyEffectIgnoreVisibility.Get(); } set { _applyEffectIgnoreVisibility.Set( value ); } }

	[Description( "Dispatch flags" )]
	public EDispatchFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Dispatch>(owner);
		_dispatchEffect = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner, typeof( ETeamID ) );
		_applyEffect = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner, typeof( ETeamID ) );
		_applyEffectOrientation = new UndoRedo<EApplyEffectOrientation>( owner, EApplyEffectOrientation.Default );
		_applyEffectRandomAnglePoints = new UndoRedo<int>( owner, 0 );
		_dieAfterApply = new UndoRedo<bool>( owner, true );
		_alwaysApply = new UndoRedo<bool>( owner, false );
		_applyEffectIgnoreVisibility = new UndoRedo<bool>( owner, false );
		_flags = new UndoRedo<EDispatchFlags>( owner, (EDispatchFlags)0 );
		___parent.Changed += FireChangedEvent;
		_dispatchEffect.Changed += FireChangedEvent;
		_applyEffect.Changed += FireChangedEvent;
		_applyEffectOrientation.Changed += FireChangedEvent;
		_applyEffectRandomAnglePoints.Changed += FireChangedEvent;
		_dieAfterApply.Changed += FireChangedEvent;
		_alwaysApply.Changed += FireChangedEvent;
		_applyEffectIgnoreVisibility.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
	}

	public Dispatch()
	{
		Initialize( this );
	}
	private void AssignSelf( Dispatch source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Dispatch" );
		dispatchEffect = source.dispatchEffect;
		applyEffect = source.applyEffect;
		applyEffectOrientation = source.applyEffectOrientation;
		applyEffectRandomAnglePoints = source.applyEffectRandomAnglePoints;
		dieAfterApply = source.dieAfterApply;
		alwaysApply = source.alwaysApply;
		applyEffectIgnoreVisibility = source.applyEffectIgnoreVisibility;
		flags = source.flags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Dispatch source = _source as Dispatch;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Dispatch" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Dispatch newParent = rawParent == null ? null : rawParent.Get<Dispatch>();
		if ( newParent == null && _newParent is Dispatch )
			newParent = _newParent as Dispatch;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_dispatchEffect.SetParent( newParent == null ? null : newParent._dispatchEffect );
		_applyEffect.SetParent( newParent == null ? null : newParent._applyEffect );
		_applyEffectOrientation.SetParent( newParent == null ? null : newParent._applyEffectOrientation );
		_applyEffectRandomAnglePoints.SetParent( newParent == null ? null : newParent._applyEffectRandomAnglePoints );
		_dieAfterApply.SetParent( newParent == null ? null : newParent._dieAfterApply );
		_alwaysApply.SetParent( newParent == null ? null : newParent._alwaysApply );
		_applyEffectIgnoreVisibility.SetParent( newParent == null ? null : newParent._applyEffectIgnoreVisibility );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_dispatchEffect.Reset();
		_applyEffect.Reset();
		_applyEffectOrientation.Reset();
		_applyEffectRandomAnglePoints.Reset();
		_dieAfterApply.Reset();
		_alwaysApply.Reset();
		_applyEffectIgnoreVisibility.Reset();
		_flags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_dispatchEffect.IsDerivedFromParent()
			&& _applyEffect.IsDerivedFromParent()
			&& _applyEffectOrientation.IsDerivedFromParent()
			&& _applyEffectRandomAnglePoints.IsDerivedFromParent()
			&& _dieAfterApply.IsDerivedFromParent()
			&& _alwaysApply.IsDerivedFromParent()
			&& _applyEffectIgnoreVisibility.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "dispatchEffect" )
			_dispatchEffect.Reset();
		else if ( fieldName == "applyEffect" )
			_applyEffect.Reset();
		else if ( fieldName == "applyEffectOrientation" )
			_applyEffectOrientation.Reset();
		else if ( fieldName == "applyEffectRandomAnglePoints" )
			_applyEffectRandomAnglePoints.Reset();
		else if ( fieldName == "dieAfterApply" )
			_dieAfterApply.Reset();
		else if ( fieldName == "alwaysApply" )
			_alwaysApply.Reset();
		else if ( fieldName == "applyEffectIgnoreVisibility" )
			_applyEffectIgnoreVisibility.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "dispatchEffect" )
			return _dispatchEffect.IsDerivedFromParent();
		if ( fieldName == "applyEffect" )
			return _applyEffect.IsDerivedFromParent();
		if ( fieldName == "applyEffectOrientation" )
			return _applyEffectOrientation.IsDerivedFromParent();
		if ( fieldName == "applyEffectRandomAnglePoints" )
			return _applyEffectRandomAnglePoints.IsDerivedFromParent();
		if ( fieldName == "dieAfterApply" )
			return _dieAfterApply.IsDerivedFromParent();
		if ( fieldName == "alwaysApply" )
			return _alwaysApply.IsDerivedFromParent();
		if ( fieldName == "applyEffectIgnoreVisibility" )
			return _applyEffectIgnoreVisibility.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFDispatchContinuous", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
[TypeId(0xA067A400)]
[UseTypeName("DSCH")]
public class DispatchContinuous : Dispatch
{
	private UndoRedoDBPtr<DispatchContinuous> ___parent;
	[HideInOutliner]
	public new DBPtr<DispatchContinuous> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _persistentApplicators;

	[Description( "List of persistent applicators that will live along with the dispatch itself" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> persistentApplicators { get { return _persistentApplicators; } set { _persistentApplicators.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispatchContinuous>(owner);
		_persistentApplicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		___parent.Changed += FireChangedEvent;
		_persistentApplicators.Changed += FireChangedEvent;
	}

	public DispatchContinuous()
	{
		Initialize( this );
	}
	private void AssignSelf( DispatchContinuous source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispatchContinuous" );
		persistentApplicators = source.persistentApplicators;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispatchContinuous source = _source as DispatchContinuous;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispatchContinuous" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispatchContinuous newParent = rawParent == null ? null : rawParent.Get<DispatchContinuous>();
		if ( newParent == null && _newParent is DispatchContinuous )
			newParent = _newParent as DispatchContinuous;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentApplicators.SetParent( newParent == null ? null : newParent._persistentApplicators );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentApplicators.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentApplicators.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentApplicators" )
			_persistentApplicators.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "persistentApplicators" )
			return _persistentApplicators.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFDispatchByTime", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
[TypeId(0xA0678C02)]
[UseTypeName("DSCH")]
public class DispatchByTime : DispatchContinuous
{
	private UndoRedoDBPtr<DispatchByTime> ___parent;
	[HideInOutliner]
	public new DBPtr<DispatchByTime> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _lifeTime;
	private UndoRedo<bool> _cancelOnSenderDeath;

	[Description( "Life time of dispatch (in seconds). If negative dispatch dies upon all persistent applicators death." )]
	public ExecutableFloatString lifeTime { get { return _lifeTime; } set { _lifeTime.Assign( value ); } }

	[Description( "Cancel dispatch on sender's death" )]
	public bool cancelOnSenderDeath { get { return _cancelOnSenderDeath.Get(); } set { _cancelOnSenderDeath.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispatchByTime>(owner);
		ExecutableFloatString __lifeTime = new ExecutableFloatString(); // Construct default object for lifeTime
		__lifeTime.sString = "0.0f";
		_lifeTime = new ExecutableFloatString( owner, __lifeTime );
		_cancelOnSenderDeath = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		_cancelOnSenderDeath.Changed += FireChangedEvent;
	}

	public DispatchByTime()
	{
		Initialize( this );
	}
	private void AssignSelf( DispatchByTime source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispatchByTime" );
		lifeTime = source.lifeTime;
		cancelOnSenderDeath = source.cancelOnSenderDeath;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispatchByTime source = _source as DispatchByTime;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispatchByTime" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispatchByTime newParent = rawParent == null ? null : rawParent.Get<DispatchByTime>();
		if ( newParent == null && _newParent is DispatchByTime )
			newParent = _newParent as DispatchByTime;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_cancelOnSenderDeath.SetParent( newParent == null ? null : newParent._cancelOnSenderDeath );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_lifeTime.Reset();
		_cancelOnSenderDeath.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_lifeTime.IsDerivedFromParent()
			&& _cancelOnSenderDeath.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "cancelOnSenderDeath" )
			_cancelOnSenderDeath.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "cancelOnSenderDeath" )
			return _cancelOnSenderDeath.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Create", "NWorld::PFDispatchCursor", "PFDispatchCursor.h", CreateFunction = "NWorld::FCreateDispatch<>")]
[TypeId(0x8D85DC80)]
[UseTypeName("DSCH")]
public class DispatchCursor : DispatchContinuous
{
	private UndoRedoDBPtr<DispatchCursor> ___parent;
	[HideInOutliner]
	public new DBPtr<DispatchCursor> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _speed;
	private ExecutableFloatString _maxSpeed;
	private UndoRedo<string> _fromLocator;
	private UndoRedo<float> _height;
	private ExecutableFloatString _lifeTime;
	private UndoRedo<int> _cursorUpdateFrequency;
	private UndoRedo<float> _linkRange;
	private UndoRedoDBPtr<LightningEffect> _linkEffect;
	private UndoRedoDBPtr<AOEMaterial> _maxRangeMaterial;
	private UndoRedo<float> _size;

	[Description( "Speed of bullet (in meters/second)." )]
	public ExecutableFloatString speed { get { return _speed; } set { _speed.Assign( value ); } }

	[Description( "Max speed of bullet (in meters/second)." )]
	public ExecutableFloatString maxSpeed { get { return _maxSpeed; } set { _maxSpeed.Assign( value ); } }

	[Description( "Name of locator (on owner object) dispatch will depart from. If empty, AABB center will be used." )]
	public string fromLocator { get { return _fromLocator.Get(); } set { _fromLocator.Set( value ); } }

	[Description( "Высота над террейном" )]
	public float height { get { return _height.Get(); } set { _height.Set( value ); } }

	[Description( "Время жизни" )]
	public ExecutableFloatString lifeTime { get { return _lifeTime; } set { _lifeTime.Assign( value ); } }

	[Description( "Частота обновления положения курсора в step'ах (1-каждый step, 2-каждый второй step и тд)" )]
	public int cursorUpdateFrequency { get { return _cursorUpdateFrequency.Get(); } set { _cursorUpdateFrequency.Set( value ); } }

	[Description( "Расстояние на которое диспатч может удалиться от посылающего" )]
	public float linkRange { get { return _linkRange.Get(); } set { _linkRange.Set( value ); } }

	[Description( "Эффект-молния который появится между диспатчем и посылающим, когда диспатч удалится на расстояние linkRange" )]
	public DBPtr<LightningEffect> linkEffect { get { return _linkEffect.Get(); } set { _linkEffect.Set( value ); } }

	[Description( "AOE-материал для отображения макс. радиуса полёта" )]
	public DBPtr<AOEMaterial> maxRangeMaterial { get { return _maxRangeMaterial.Get(); } set { _maxRangeMaterial.Set( value ); } }

	[Description( "Размер диспатча для отображения maxRangeMaterial" )]
	public float size { get { return _size.Get(); } set { _size.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispatchCursor>(owner);
		ExecutableFloatString __speed = new ExecutableFloatString(); // Construct default object for speed
		__speed.sString = "0.0f";
		_speed = new ExecutableFloatString( owner, __speed );
		ExecutableFloatString __maxSpeed = new ExecutableFloatString(); // Construct default object for maxSpeed
		__maxSpeed.sString = "0.0f";
		_maxSpeed = new ExecutableFloatString( owner, __maxSpeed );
		_fromLocator = new UndoRedo<string>( owner, "Attack" );
		_height = new UndoRedo<float>( owner, 0.0f );
		ExecutableFloatString __lifeTime = new ExecutableFloatString(); // Construct default object for lifeTime
		__lifeTime.sString = "10.0f";
		_lifeTime = new ExecutableFloatString( owner, __lifeTime );
		_cursorUpdateFrequency = new UndoRedo<int>( owner, 5 );
		_linkRange = new UndoRedo<float>( owner, 0.0f );
		_linkEffect = new UndoRedoDBPtr<LightningEffect>( owner );
		_maxRangeMaterial = new UndoRedoDBPtr<AOEMaterial>( owner );
		_size = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_maxSpeed.Changed += FireChangedEvent;
		_fromLocator.Changed += FireChangedEvent;
		_height.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		_cursorUpdateFrequency.Changed += FireChangedEvent;
		_linkRange.Changed += FireChangedEvent;
		_linkEffect.Changed += FireChangedEvent;
		_maxRangeMaterial.Changed += FireChangedEvent;
		_size.Changed += FireChangedEvent;
	}

	public DispatchCursor()
	{
		Initialize( this );
	}
	private void AssignSelf( DispatchCursor source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispatchCursor" );
		speed = source.speed;
		maxSpeed = source.maxSpeed;
		fromLocator = source.fromLocator;
		height = source.height;
		lifeTime = source.lifeTime;
		cursorUpdateFrequency = source.cursorUpdateFrequency;
		linkRange = source.linkRange;
		linkEffect = source.linkEffect;
		maxRangeMaterial = source.maxRangeMaterial;
		size = source.size;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispatchCursor source = _source as DispatchCursor;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispatchCursor" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispatchCursor newParent = rawParent == null ? null : rawParent.Get<DispatchCursor>();
		if ( newParent == null && _newParent is DispatchCursor )
			newParent = _newParent as DispatchCursor;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_speed.SetParent( newParent == null ? null : newParent._speed );
		_maxSpeed.SetParent( newParent == null ? null : newParent._maxSpeed );
		_fromLocator.SetParent( newParent == null ? null : newParent._fromLocator );
		_height.SetParent( newParent == null ? null : newParent._height );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_cursorUpdateFrequency.SetParent( newParent == null ? null : newParent._cursorUpdateFrequency );
		_linkRange.SetParent( newParent == null ? null : newParent._linkRange );
		_linkEffect.SetParent( newParent == null ? null : newParent._linkEffect );
		_maxRangeMaterial.SetParent( newParent == null ? null : newParent._maxRangeMaterial );
		_size.SetParent( newParent == null ? null : newParent._size );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_speed.Reset();
		_maxSpeed.Reset();
		_fromLocator.Reset();
		_height.Reset();
		_lifeTime.Reset();
		_cursorUpdateFrequency.Reset();
		_linkRange.Reset();
		_linkEffect.Reset();
		_maxRangeMaterial.Reset();
		_size.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_speed.IsDerivedFromParent()
			&& _maxSpeed.IsDerivedFromParent()
			&& _fromLocator.IsDerivedFromParent()
			&& _height.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			&& _cursorUpdateFrequency.IsDerivedFromParent()
			&& _linkRange.IsDerivedFromParent()
			&& _linkEffect.IsDerivedFromParent()
			&& _maxRangeMaterial.IsDerivedFromParent()
			&& _size.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "maxSpeed" )
			_maxSpeed.Reset();
		else if ( fieldName == "fromLocator" )
			_fromLocator.Reset();
		else if ( fieldName == "height" )
			_height.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "cursorUpdateFrequency" )
			_cursorUpdateFrequency.Reset();
		else if ( fieldName == "linkRange" )
			_linkRange.Reset();
		else if ( fieldName == "linkEffect" )
			_linkEffect.Reset();
		else if ( fieldName == "maxRangeMaterial" )
			_maxRangeMaterial.Reset();
		else if ( fieldName == "size" )
			_size.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "maxSpeed" )
			return _maxSpeed.IsDerivedFromParent();
		if ( fieldName == "fromLocator" )
			return _fromLocator.IsDerivedFromParent();
		if ( fieldName == "height" )
			return _height.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "cursorUpdateFrequency" )
			return _cursorUpdateFrequency.IsDerivedFromParent();
		if ( fieldName == "linkRange" )
			return _linkRange.IsDerivedFromParent();
		if ( fieldName == "linkEffect" )
			return _linkEffect.IsDerivedFromParent();
		if ( fieldName == "maxRangeMaterial" )
			return _maxRangeMaterial.IsDerivedFromParent();
		if ( fieldName == "size" )
			return _size.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFDispatchImmediate", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
[TypeId(0xA0678C01)]
[UseTypeName("DSCH")]
public class DispatchImmediate : Dispatch
{
	private UndoRedoDBPtr<DispatchImmediate> ___parent;
	[HideInOutliner]
	public new DBPtr<DispatchImmediate> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _instantApply;

	[Description( "Apply dispatch instantly. Use with caution!" )]
	public bool instantApply { get { return _instantApply.Get(); } set { _instantApply.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispatchImmediate>(owner);
		_instantApply = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_instantApply.Changed += FireChangedEvent;
	}

	public DispatchImmediate()
	{
		Initialize( this );
	}
	private void AssignSelf( DispatchImmediate source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispatchImmediate" );
		instantApply = source.instantApply;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispatchImmediate source = _source as DispatchImmediate;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispatchImmediate" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispatchImmediate newParent = rawParent == null ? null : rawParent.Get<DispatchImmediate>();
		if ( newParent == null && _newParent is DispatchImmediate )
			newParent = _newParent as DispatchImmediate;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_instantApply.SetParent( newParent == null ? null : newParent._instantApply );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_instantApply.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_instantApply.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "instantApply" )
			_instantApply.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "instantApply" )
			return _instantApply.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Create", "NWorld::PFDispatchUniformLinearMove", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
[TypeId(0xA0678C03)]
[UseTypeName("DSCH")]
public class DispatchLinear : DispatchContinuous
{
	private UndoRedoDBPtr<DispatchLinear> ___parent;
	[HideInOutliner]
	public new DBPtr<DispatchLinear> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EDispatchAiming> _aiming;
	private UndoRedo<float> _maxDeviation;
	private UndoRedo<float> _speed;
	private UndoRedo<bool> _locatorOrient;
	private UndoRedo<string> _fromLocator;
	private UndoRedo<string> _toLocator;
	private UndoRedo<float> _height;
	private UndoRedo<EDispatchFlyMode> _flyMode;
	private UndoRedo<float> _maxDistance;
	private UndoRedo<float> _minRise;
	private UndoRedo<float> _maxRise;
	private UndoRedo<bool> _killEffect;
	private UndoRedo<float> _suspendTime;

	[Description( "Affects chances to lose target if it moves during flight" )]
	public EDispatchAiming aiming { get { return _aiming.Get(); } set { _aiming.Set( value ); } }

	[Description( "Maximum deviation angle from straight line of fire in degrees (if aiming = Straight)" )]
	public float maxDeviation { get { return _maxDeviation.Get(); } set { _maxDeviation.Set( value ); } }

	[Description( "Speed of bullet (in meters/second)." )]
	public float speed { get { return _speed.Get(); } set { _speed.Set( value ); } }

	[Description( "Dispatch effect will use from-locator orientation (otherwise it will use position only)." )]
	public bool locatorOrient { get { return _locatorOrient.Get(); } set { _locatorOrient.Set( value ); } }

	[Description( "Name of locator (on owner object) dispatch will depart from. If empty, AABB center will be used." )]
	public string fromLocator { get { return _fromLocator.Get(); } set { _fromLocator.Set( value ); } }

	[Description( "Name of locator (on target object) dispatch will arrive to. If empty, AABB center will be used." )]
	public string toLocator { get { return _toLocator.Get(); } set { _toLocator.Set( value ); } }

	[Description( "Высота над toLocator или террейном" )]
	public float height { get { return _height.Get(); } set { _height.Set( value ); } }

	[Description( "Trajectory calculation method dispatch starts flying with (may be changed according to environment conditions)." )]
	[HideEnumValues("FixedHeight")]
	public EDispatchFlyMode flyMode { get { return _flyMode.Get(); } set { _flyMode.Set( value ); } }

	[Description( "Maximum distance dispatch can travel (negative for unlimited motion)." )]
	public float maxDistance { get { return _maxDistance.Get(); } set { _maxDistance.Set( value ); } }

	[Description( "Trajectory height on minimal distance." )]
	public float minRise { get { return _minRise.Get(); } set { _minRise.Set( value ); } }

	[Description( "Trajectory height on maximal distance." )]
	public float maxRise { get { return _maxRise.Get(); } set { _maxRise.Set( value ); } }

	[Description( "Kill dispatch effect upon arrival. If false someone else is responsible for this." )]
	public bool killEffect { get { return _killEffect.Get(); } set { _killEffect.Set( value ); } }

	[Description( "Time to suspend dispatch before sending it fly" )]
	public float suspendTime { get { return _suspendTime.Get(); } set { _suspendTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispatchLinear>(owner);
		_aiming = new UndoRedo<EDispatchAiming>( owner, EDispatchAiming.Straight );
		_maxDeviation = new UndoRedo<float>( owner, 180.0f );
		_speed = new UndoRedo<float>( owner, 0.0f );
		_locatorOrient = new UndoRedo<bool>( owner, true );
		_fromLocator = new UndoRedo<string>( owner, "Attack" );
		_toLocator = new UndoRedo<string>( owner, "Body" );
		_height = new UndoRedo<float>( owner, 0.0f );
		_flyMode = new UndoRedo<EDispatchFlyMode>( owner, EDispatchFlyMode.Parabolic );
		_maxDistance = new UndoRedo<float>( owner, -1.0f );
		_minRise = new UndoRedo<float>( owner, 0.0f );
		_maxRise = new UndoRedo<float>( owner, 0.0f );
		_killEffect = new UndoRedo<bool>( owner, true );
		_suspendTime = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_aiming.Changed += FireChangedEvent;
		_maxDeviation.Changed += FireChangedEvent;
		_speed.Changed += FireChangedEvent;
		_locatorOrient.Changed += FireChangedEvent;
		_fromLocator.Changed += FireChangedEvent;
		_toLocator.Changed += FireChangedEvent;
		_height.Changed += FireChangedEvent;
		_flyMode.Changed += FireChangedEvent;
		_maxDistance.Changed += FireChangedEvent;
		_minRise.Changed += FireChangedEvent;
		_maxRise.Changed += FireChangedEvent;
		_killEffect.Changed += FireChangedEvent;
		_suspendTime.Changed += FireChangedEvent;
	}

	public DispatchLinear()
	{
		Initialize( this );
	}
	private void AssignSelf( DispatchLinear source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispatchLinear" );
		aiming = source.aiming;
		maxDeviation = source.maxDeviation;
		speed = source.speed;
		locatorOrient = source.locatorOrient;
		fromLocator = source.fromLocator;
		toLocator = source.toLocator;
		height = source.height;
		flyMode = source.flyMode;
		maxDistance = source.maxDistance;
		minRise = source.minRise;
		maxRise = source.maxRise;
		killEffect = source.killEffect;
		suspendTime = source.suspendTime;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispatchLinear source = _source as DispatchLinear;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispatchLinear" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispatchLinear newParent = rawParent == null ? null : rawParent.Get<DispatchLinear>();
		if ( newParent == null && _newParent is DispatchLinear )
			newParent = _newParent as DispatchLinear;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_aiming.SetParent( newParent == null ? null : newParent._aiming );
		_maxDeviation.SetParent( newParent == null ? null : newParent._maxDeviation );
		_speed.SetParent( newParent == null ? null : newParent._speed );
		_locatorOrient.SetParent( newParent == null ? null : newParent._locatorOrient );
		_fromLocator.SetParent( newParent == null ? null : newParent._fromLocator );
		_toLocator.SetParent( newParent == null ? null : newParent._toLocator );
		_height.SetParent( newParent == null ? null : newParent._height );
		_flyMode.SetParent( newParent == null ? null : newParent._flyMode );
		_maxDistance.SetParent( newParent == null ? null : newParent._maxDistance );
		_minRise.SetParent( newParent == null ? null : newParent._minRise );
		_maxRise.SetParent( newParent == null ? null : newParent._maxRise );
		_killEffect.SetParent( newParent == null ? null : newParent._killEffect );
		_suspendTime.SetParent( newParent == null ? null : newParent._suspendTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_aiming.Reset();
		_maxDeviation.Reset();
		_speed.Reset();
		_locatorOrient.Reset();
		_fromLocator.Reset();
		_toLocator.Reset();
		_height.Reset();
		_flyMode.Reset();
		_maxDistance.Reset();
		_minRise.Reset();
		_maxRise.Reset();
		_killEffect.Reset();
		_suspendTime.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_aiming.IsDerivedFromParent()
			&& _maxDeviation.IsDerivedFromParent()
			&& _speed.IsDerivedFromParent()
			&& _locatorOrient.IsDerivedFromParent()
			&& _fromLocator.IsDerivedFromParent()
			&& _toLocator.IsDerivedFromParent()
			&& _height.IsDerivedFromParent()
			&& _flyMode.IsDerivedFromParent()
			&& _maxDistance.IsDerivedFromParent()
			&& _minRise.IsDerivedFromParent()
			&& _maxRise.IsDerivedFromParent()
			&& _killEffect.IsDerivedFromParent()
			&& _suspendTime.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "aiming" )
			_aiming.Reset();
		else if ( fieldName == "maxDeviation" )
			_maxDeviation.Reset();
		else if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "locatorOrient" )
			_locatorOrient.Reset();
		else if ( fieldName == "fromLocator" )
			_fromLocator.Reset();
		else if ( fieldName == "toLocator" )
			_toLocator.Reset();
		else if ( fieldName == "height" )
			_height.Reset();
		else if ( fieldName == "flyMode" )
			_flyMode.Reset();
		else if ( fieldName == "maxDistance" )
			_maxDistance.Reset();
		else if ( fieldName == "minRise" )
			_minRise.Reset();
		else if ( fieldName == "maxRise" )
			_maxRise.Reset();
		else if ( fieldName == "killEffect" )
			_killEffect.Reset();
		else if ( fieldName == "suspendTime" )
			_suspendTime.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "aiming" )
			return _aiming.IsDerivedFromParent();
		if ( fieldName == "maxDeviation" )
			return _maxDeviation.IsDerivedFromParent();
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "locatorOrient" )
			return _locatorOrient.IsDerivedFromParent();
		if ( fieldName == "fromLocator" )
			return _fromLocator.IsDerivedFromParent();
		if ( fieldName == "toLocator" )
			return _toLocator.IsDerivedFromParent();
		if ( fieldName == "height" )
			return _height.IsDerivedFromParent();
		if ( fieldName == "flyMode" )
			return _flyMode.IsDerivedFromParent();
		if ( fieldName == "maxDistance" )
			return _maxDistance.IsDerivedFromParent();
		if ( fieldName == "minRise" )
			return _minRise.IsDerivedFromParent();
		if ( fieldName == "maxRise" )
			return _maxRise.IsDerivedFromParent();
		if ( fieldName == "killEffect" )
			return _killEffect.IsDerivedFromParent();
		if ( fieldName == "suspendTime" )
			return _suspendTime.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFDispatchWithLink", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
[TypeId(0xA067BBC0)]
[UseTypeName("DSCH")]
public class DispatchLinearWithLink : DispatchLinear
{
	private UndoRedoDBPtr<DispatchLinearWithLink> ___parent;
	[HideInOutliner]
	public new DBPtr<DispatchLinearWithLink> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<LightningLink> _links;

	public libdb.IChangeableList<LightningLink> links { get { return _links; } set { _links.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispatchLinearWithLink>(owner);
		_links = new UndoRedoAssignableList<LightningLink>( owner );
		___parent.Changed += FireChangedEvent;
		_links.Changed += FireChangedEvent;
	}

	public DispatchLinearWithLink()
	{
		Initialize( this );
	}
	private void AssignSelf( DispatchLinearWithLink source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispatchLinearWithLink" );
		links = source.links;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispatchLinearWithLink source = _source as DispatchLinearWithLink;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispatchLinearWithLink" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispatchLinearWithLink newParent = rawParent == null ? null : rawParent.Get<DispatchLinearWithLink>();
		if ( newParent == null && _newParent is DispatchLinearWithLink )
			newParent = _newParent as DispatchLinearWithLink;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_links.SetParent( newParent == null ? null : newParent._links );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_links.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_links.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "links" )
			_links.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "links" )
			return _links.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFDispatchRockmanMace", "PFDispatchStrike1.h", CreateFunction = "NWorld::FCreateDispatch<>")]
[TypeId(0xA073CA80)]
[UseTypeName("DSCH")]
public class DispatchRockmanMace : DispatchLinearWithLink
{
	private UndoRedoDBPtr<DispatchRockmanMace> ___parent;
	[HideInOutliner]
	public new DBPtr<DispatchRockmanMace> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _minDistance;

	[Description( "Minimal distance to send dispatch" )]
	public float minDistance { get { return _minDistance.Get(); } set { _minDistance.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispatchRockmanMace>(owner);
		_minDistance = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_minDistance.Changed += FireChangedEvent;
	}

	public DispatchRockmanMace()
	{
		Initialize( this );
	}
	private void AssignSelf( DispatchRockmanMace source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispatchRockmanMace" );
		minDistance = source.minDistance;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispatchRockmanMace source = _source as DispatchRockmanMace;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispatchRockmanMace" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispatchRockmanMace newParent = rawParent == null ? null : rawParent.Get<DispatchRockmanMace>();
		if ( newParent == null && _newParent is DispatchRockmanMace )
			newParent = _newParent as DispatchRockmanMace;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_minDistance.SetParent( newParent == null ? null : newParent._minDistance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_minDistance.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_minDistance.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "minDistance" )
			_minDistance.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "minDistance" )
			return _minDistance.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplDispell", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E67DB00)]
[UseTypeName("APLR")]
public class DispellApplicator : BaseApplicator
{
	private UndoRedoDBPtr<DispellApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<DispellApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableIntString _maxEffectsToDispell;
	private UndoRedoDBPtr<TargetSelector> _targets;

	[Description( "Maximal amount of effects to be dispelled at once" )]
	public ExecutableIntString maxEffectsToDispell { get { return _maxEffectsToDispell; } set { _maxEffectsToDispell.Assign( value ); } }

	[Description( "Цели по которым диспеллить (опционально)" )]
	public DBPtr<TargetSelector> targets { get { return _targets.Get(); } set { _targets.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispellApplicator>(owner);
		ExecutableIntString __maxEffectsToDispell = new ExecutableIntString(); // Construct default object for maxEffectsToDispell
		__maxEffectsToDispell.sString = "1";
		_maxEffectsToDispell = new ExecutableIntString( owner, __maxEffectsToDispell );
		_targets = new UndoRedoDBPtr<TargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_maxEffectsToDispell.Changed += FireChangedEvent;
		_targets.Changed += FireChangedEvent;
	}

	public DispellApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( DispellApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispellApplicator" );
		maxEffectsToDispell = source.maxEffectsToDispell;
		targets = source.targets;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispellApplicator source = _source as DispellApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispellApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispellApplicator newParent = rawParent == null ? null : rawParent.Get<DispellApplicator>();
		if ( newParent == null && _newParent is DispellApplicator )
			newParent = _newParent as DispellApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_maxEffectsToDispell.SetParent( newParent == null ? null : newParent._maxEffectsToDispell );
		_targets.SetParent( newParent == null ? null : newParent._targets );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_maxEffectsToDispell.Reset();
		_targets.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_maxEffectsToDispell.IsDerivedFromParent()
			&& _targets.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "maxEffectsToDispell" )
			_maxEffectsToDispell.Reset();
		else if ( fieldName == "targets" )
			_targets.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "maxEffectsToDispell" )
			return _maxEffectsToDispell.IsDerivedFromParent();
		if ( fieldName == "targets" )
			return _targets.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Check", "NWorld::PFAbilityData", "PFCastLimitations.h", CreateFunction = "NWorld::CheckDispellLimitation")]
[TypeId(0x9E71CB82)]
[UseTypeName("ABCL")]
public class DispellCastLimitation : CastLimitation
{
	private UndoRedoDBPtr<DispellCastLimitation> ___parent;
	[HideInOutliner]
	public new DBPtr<DispellCastLimitation> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DispellCastLimitation>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public DispellCastLimitation()
	{
		Initialize( this );
	}
	private void AssignSelf( DispellCastLimitation source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DispellCastLimitation" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DispellCastLimitation source = _source as DispellCastLimitation;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DispellCastLimitation" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DispellCastLimitation newParent = rawParent == null ? null : rawParent.Get<DispellCastLimitation>();
		if ( newParent == null && _newParent is DispellCastLimitation )
			newParent = _newParent as DispellCastLimitation;
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

[FactoryImpl("Create", "NWorld::PFApplDropTree", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F622B41)]
[UseTypeName("APLR")]
public class DropTreeApplicator : BaseApplicator
{
	private UndoRedoDBPtr<DropTreeApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<DropTreeApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DropTreeApplicator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public DropTreeApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( DropTreeApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DropTreeApplicator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DropTreeApplicator source = _source as DropTreeApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DropTreeApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DropTreeApplicator newParent = rawParent == null ? null : rawParent.Get<DropTreeApplicator>();
		if ( newParent == null && _newParent is DropTreeApplicator )
			newParent = _newParent as DropTreeApplicator;
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

[FactoryBase("Create", "NWorld::PFEventProcessorBase", "NWorld::PFWorld* world")]
[IndexField("caption")]
[NonTerminal]
public class EventProcessorBase : DBResource
{
	private UndoRedoDBPtr<EventProcessorBase> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _applyTarget;
	private UndoRedoDBPtr<Spell> _spell;

	public EApplicatorApplyTarget applyTarget { get { return _applyTarget.Get(); } set { _applyTarget.Set( value ); } }

	public DBPtr<Spell> spell { get { return _spell.Get(); } set { _spell.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorBase>(owner);
		_applyTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_spell = new UndoRedoDBPtr<Spell>( owner );
		___parent.Changed += FireChangedEvent;
		_applyTarget.Changed += FireChangedEvent;
		_spell.Changed += FireChangedEvent;
	}

	public EventProcessorBase()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorBase" );
		applyTarget = source.applyTarget;
		spell = source.spell;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorBase source = _source as EventProcessorBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorBase newParent = rawParent == null ? null : rawParent.Get<EventProcessorBase>();
		if ( newParent == null && _newParent is EventProcessorBase )
			newParent = _newParent as EventProcessorBase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_applyTarget.SetParent( newParent == null ? null : newParent._applyTarget );
		_spell.SetParent( newParent == null ? null : newParent._spell );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_applyTarget.Reset();
		_spell.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_applyTarget.IsDerivedFromParent()
			&& _spell.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "applyTarget" )
			_applyTarget.Reset();
		else if ( fieldName == "spell" )
			_spell.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "applyTarget" )
			return _applyTarget.IsDerivedFromParent();
		if ( fieldName == "spell" )
			return _spell.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorApplicatorApplied", "PFTriggerApplicator.h")]
[TypeId(0x0F72C2C1)]
[UseTypeName("EVNT")]
public class EventProcessorApplicatorApplied : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorApplicatorApplied> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorApplicatorApplied> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ETriggerAbilitiesAbilitiesFlags> _filter;
	private UndoRedoDBPtr<ApplicatorsList> _applicatorTypesList;
	private UndoRedoDBPtr<ApplicatorsList> _applicatorsList;
	private UndoRedo<EApplicatorAppliedMode> _mode;
	private ExecutableFloatString _newLifetime;
	private UndoRedo<EApplicatorApplyTarget> _senderMatchTarget;
	private UndoRedo<ETriggerEventCheckSender> _checkSender;

	public ETriggerAbilitiesAbilitiesFlags filter { get { return _filter.Get(); } set { _filter.Set( value ); } }

	[Description( "Типы аппликаторов для сравнения" )]
	public DBPtr<ApplicatorsList> applicatorTypesList { get { return _applicatorTypesList.Get(); } set { _applicatorTypesList.Set( value ); } }

	[Description( "Конкретные аппликаторы для сравнения" )]
	public DBPtr<ApplicatorsList> applicatorsList { get { return _applicatorsList.Get(); } set { _applicatorsList.Set( value ); } }

	public EApplicatorAppliedMode mode { get { return _mode.Get(); } set { _mode.Set( value ); } }

	[Description( "Новая длительность накладываемого аппликатора. Оргинальную можно получить через appl.vLifetime" )]
	public ExecutableFloatString newLifetime { get { return _newLifetime; } set { _newLifetime.Assign( value ); } }

	[Description( "Сравнить посылающего с целью аппликатора" )]
	public EApplicatorApplyTarget senderMatchTarget { get { return _senderMatchTarget.Get(); } set { _senderMatchTarget.Set( value ); } }

	[Description( "Дополнительные проверки посылающего событие" )]
	public ETriggerEventCheckSender checkSender { get { return _checkSender.Get(); } set { _checkSender.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorApplicatorApplied>(owner);
		_filter = new UndoRedo<ETriggerAbilitiesAbilitiesFlags>( owner, ETriggerAbilitiesAbilitiesFlags.None );
		_applicatorTypesList = new UndoRedoDBPtr<ApplicatorsList>( owner );
		_applicatorsList = new UndoRedoDBPtr<ApplicatorsList>( owner );
		_mode = new UndoRedo<EApplicatorAppliedMode>( owner, EApplicatorAppliedMode.Default );
		ExecutableFloatString __newLifetime = new ExecutableFloatString(); // Construct default object for newLifetime
		__newLifetime.sString = "-1.0";
		_newLifetime = new ExecutableFloatString( owner, __newLifetime );
		_senderMatchTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_checkSender = new UndoRedo<ETriggerEventCheckSender>( owner, ETriggerEventCheckSender.None );
		___parent.Changed += FireChangedEvent;
		_filter.Changed += FireChangedEvent;
		_applicatorTypesList.Changed += FireChangedEvent;
		_applicatorsList.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		_newLifetime.Changed += FireChangedEvent;
		_senderMatchTarget.Changed += FireChangedEvent;
		_checkSender.Changed += FireChangedEvent;
	}

	public EventProcessorApplicatorApplied()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorApplicatorApplied source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorApplicatorApplied" );
		filter = source.filter;
		applicatorTypesList = source.applicatorTypesList;
		applicatorsList = source.applicatorsList;
		mode = source.mode;
		newLifetime = source.newLifetime;
		senderMatchTarget = source.senderMatchTarget;
		checkSender = source.checkSender;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorApplicatorApplied source = _source as EventProcessorApplicatorApplied;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorApplicatorApplied" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorApplicatorApplied newParent = rawParent == null ? null : rawParent.Get<EventProcessorApplicatorApplied>();
		if ( newParent == null && _newParent is EventProcessorApplicatorApplied )
			newParent = _newParent as EventProcessorApplicatorApplied;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_filter.SetParent( newParent == null ? null : newParent._filter );
		_applicatorTypesList.SetParent( newParent == null ? null : newParent._applicatorTypesList );
		_applicatorsList.SetParent( newParent == null ? null : newParent._applicatorsList );
		_mode.SetParent( newParent == null ? null : newParent._mode );
		_newLifetime.SetParent( newParent == null ? null : newParent._newLifetime );
		_senderMatchTarget.SetParent( newParent == null ? null : newParent._senderMatchTarget );
		_checkSender.SetParent( newParent == null ? null : newParent._checkSender );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_filter.Reset();
		_applicatorTypesList.Reset();
		_applicatorsList.Reset();
		_mode.Reset();
		_newLifetime.Reset();
		_senderMatchTarget.Reset();
		_checkSender.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_filter.IsDerivedFromParent()
			&& _applicatorTypesList.IsDerivedFromParent()
			&& _applicatorsList.IsDerivedFromParent()
			&& _mode.IsDerivedFromParent()
			&& _newLifetime.IsDerivedFromParent()
			&& _senderMatchTarget.IsDerivedFromParent()
			&& _checkSender.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "filter" )
			_filter.Reset();
		else if ( fieldName == "applicatorTypesList" )
			_applicatorTypesList.Reset();
		else if ( fieldName == "applicatorsList" )
			_applicatorsList.Reset();
		else if ( fieldName == "mode" )
			_mode.Reset();
		else if ( fieldName == "newLifetime" )
			_newLifetime.Reset();
		else if ( fieldName == "senderMatchTarget" )
			_senderMatchTarget.Reset();
		else if ( fieldName == "checkSender" )
			_checkSender.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "filter" )
			return _filter.IsDerivedFromParent();
		if ( fieldName == "applicatorTypesList" )
			return _applicatorTypesList.IsDerivedFromParent();
		if ( fieldName == "applicatorsList" )
			return _applicatorsList.IsDerivedFromParent();
		if ( fieldName == "mode" )
			return _mode.IsDerivedFromParent();
		if ( fieldName == "newLifetime" )
			return _newLifetime.IsDerivedFromParent();
		if ( fieldName == "senderMatchTarget" )
			return _senderMatchTarget.IsDerivedFromParent();
		if ( fieldName == "checkSender" )
			return _checkSender.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorAbilityManacostTransformer", "PFTriggerApplicator.h")]
[TypeId(0x0F729C41)]
[UseTypeName("EVNT")]
public class EventProcessorAbilityManacostTransformer : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorAbilityManacostTransformer> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorAbilityManacostTransformer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TriggerAbilitiesFilter _filter;

	public TriggerAbilitiesFilter filter { get { return _filter; } set { _filter.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorAbilityManacostTransformer>(owner);
		_filter = new TriggerAbilitiesFilter( owner );
		___parent.Changed += FireChangedEvent;
		_filter.Changed += FireChangedEvent;
	}

	public EventProcessorAbilityManacostTransformer()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorAbilityManacostTransformer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorAbilityManacostTransformer" );
		filter = source.filter;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorAbilityManacostTransformer source = _source as EventProcessorAbilityManacostTransformer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorAbilityManacostTransformer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorAbilityManacostTransformer newParent = rawParent == null ? null : rawParent.Get<EventProcessorAbilityManacostTransformer>();
		if ( newParent == null && _newParent is EventProcessorAbilityManacostTransformer )
			newParent = _newParent as EventProcessorAbilityManacostTransformer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_filter.SetParent( newParent == null ? null : newParent._filter );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_filter.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_filter.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "filter" )
			_filter.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "filter" )
			return _filter.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorCancelDispatch", "PFTriggerApplicator.h")]
[TypeId(0x0F728300)]
[UseTypeName("EVNT")]
public class EventProcessorCancelDispatch : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorCancelDispatch> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorCancelDispatch> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TriggerAbilitiesFilter _filter;
	private UndoRedo<EApplicatorApplyTarget> _senderMatchTarget;
	private UndoRedo<ETriggerEventCheckSender> _checkSender;

	public TriggerAbilitiesFilter filter { get { return _filter; } set { _filter.Assign( value ); } }

	[Description( "Сравнить посылающего диспатч с целью аппликатора" )]
	public EApplicatorApplyTarget senderMatchTarget { get { return _senderMatchTarget.Get(); } set { _senderMatchTarget.Set( value ); } }

	[Description( "Дополнительные проверки посылающего событие" )]
	public ETriggerEventCheckSender checkSender { get { return _checkSender.Get(); } set { _checkSender.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorCancelDispatch>(owner);
		_filter = new TriggerAbilitiesFilter( owner );
		_senderMatchTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_checkSender = new UndoRedo<ETriggerEventCheckSender>( owner, ETriggerEventCheckSender.None );
		___parent.Changed += FireChangedEvent;
		_filter.Changed += FireChangedEvent;
		_senderMatchTarget.Changed += FireChangedEvent;
		_checkSender.Changed += FireChangedEvent;
	}

	public EventProcessorCancelDispatch()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorCancelDispatch source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorCancelDispatch" );
		filter = source.filter;
		senderMatchTarget = source.senderMatchTarget;
		checkSender = source.checkSender;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorCancelDispatch source = _source as EventProcessorCancelDispatch;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorCancelDispatch" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorCancelDispatch newParent = rawParent == null ? null : rawParent.Get<EventProcessorCancelDispatch>();
		if ( newParent == null && _newParent is EventProcessorCancelDispatch )
			newParent = _newParent as EventProcessorCancelDispatch;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_filter.SetParent( newParent == null ? null : newParent._filter );
		_senderMatchTarget.SetParent( newParent == null ? null : newParent._senderMatchTarget );
		_checkSender.SetParent( newParent == null ? null : newParent._checkSender );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_filter.Reset();
		_senderMatchTarget.Reset();
		_checkSender.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_filter.IsDerivedFromParent()
			&& _senderMatchTarget.IsDerivedFromParent()
			&& _checkSender.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "filter" )
			_filter.Reset();
		else if ( fieldName == "senderMatchTarget" )
			_senderMatchTarget.Reset();
		else if ( fieldName == "checkSender" )
			_checkSender.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "filter" )
			return _filter.IsDerivedFromParent();
		if ( fieldName == "senderMatchTarget" )
			return _senderMatchTarget.IsDerivedFromParent();
		if ( fieldName == "checkSender" )
			return _checkSender.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorCondition", "PFTriggerApplicator.h")]
[TypeId(0x0F724340)]
[UseTypeName("EVNT")]
public class EventProcessorCondition : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EBaseUnitEventFlags> _events;
	private ExecutableBoolString _condition;
	private UndoRedo<bool> _onlyParent;

	public EBaseUnitEventFlags events { get { return _events.Get(); } set { _events.Set( value ); } }

	public ExecutableBoolString condition { get { return _condition; } set { _condition.Assign( value ); } }

	[Description( "true - триггириться только от абилки, в которой лежит, false - от всех, подходящих по условию" )]
	public bool onlyParent { get { return _onlyParent.Get(); } set { _onlyParent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorCondition>(owner);
		_events = new UndoRedo<EBaseUnitEventFlags>( owner, EBaseUnitEventFlags.Zero );
		_condition = new ExecutableBoolString( owner );
		_onlyParent = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
		_condition.Changed += FireChangedEvent;
		_onlyParent.Changed += FireChangedEvent;
	}

	public EventProcessorCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorCondition" );
		events = source.events;
		condition = source.condition;
		onlyParent = source.onlyParent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorCondition source = _source as EventProcessorCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorCondition newParent = rawParent == null ? null : rawParent.Get<EventProcessorCondition>();
		if ( newParent == null && _newParent is EventProcessorCondition )
			newParent = _newParent as EventProcessorCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_events.SetParent( newParent == null ? null : newParent._events );
		_condition.SetParent( newParent == null ? null : newParent._condition );
		_onlyParent.SetParent( newParent == null ? null : newParent._onlyParent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_events.Reset();
		_condition.Reset();
		_onlyParent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_events.IsDerivedFromParent()
			&& _condition.IsDerivedFromParent()
			&& _onlyParent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "events" )
			_events.Reset();
		else if ( fieldName == "condition" )
			_condition.Reset();
		else if ( fieldName == "onlyParent" )
			_onlyParent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "events" )
			return _events.IsDerivedFromParent();
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
		if ( fieldName == "onlyParent" )
			return _onlyParent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorDamageTransformer", "PFTriggerApplicator.h")]
[TypeId(0x0F729C40)]
[UseTypeName("EVNT")]
public class EventProcessorDamageTransformer : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorDamageTransformer> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorDamageTransformer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EDamageFilter> _damageTypeFilter;
	private TriggerAbilitiesFilter _abilityFilter;
	private ExecutableFloatString _add;
	private ExecutableFloatString _mul;
	private UndoRedo<EApplicatorApplyTarget> _senderMatchTarget;
	private UndoRedo<bool> _matchTargetInverted;
	private UndoRedo<bool> _treatDelegatedByDelegator;
	private UndoRedo<ESpellTarget> _objectFilter;
	private UndoRedo<ETriggerEventCheckSender> _checkSender;
	private UndoRedo<ETriggerEventFlags> _flags;

	public EDamageFilter damageTypeFilter { get { return _damageTypeFilter.Get(); } set { _damageTypeFilter.Set( value ); } }

	public TriggerAbilitiesFilter abilityFilter { get { return _abilityFilter; } set { _abilityFilter.Assign( value ); } }

	public ExecutableFloatString add { get { return _add; } set { _add.Assign( value ); } }

	public ExecutableFloatString mul { get { return _mul; } set { _mul.Assign( value ); } }

	[Description( "Сравнить посылающего событие с целью аппликатора" )]
	public EApplicatorApplyTarget senderMatchTarget { get { return _senderMatchTarget.Get(); } set { _senderMatchTarget.Set( value ); } }

	[Description( "Invert sender vs target comparison results" )]
	public bool matchTargetInverted { get { return _matchTargetInverted.Get(); } set { _matchTargetInverted.Set( value ); } }

	[Description( "Считать делегированный урон как от делегирующего" )]
	public bool treatDelegatedByDelegator { get { return _treatDelegatedByDelegator.Get(); } set { _treatDelegatedByDelegator.Set( value ); } }

	[Description( "Фильтр по типу объекта, посылающего событие" )]
	public ESpellTarget objectFilter { get { return _objectFilter.Get(); } set { _objectFilter.Set( value ); } }

	[Description( "Дополнительные проверки посылающего событие" )]
	public ETriggerEventCheckSender checkSender { get { return _checkSender.Get(); } set { _checkSender.Set( value ); } }

	[Description( "Доплнительные Флаги: OnlyFirstFromAbility - обработать только первый урон из посланных абилкой за степ" )]
	public ETriggerEventFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorDamageTransformer>(owner);
		_damageTypeFilter = new UndoRedo<EDamageFilter>( owner, EDamageFilter.All );
		_abilityFilter = new TriggerAbilitiesFilter( owner );
		ExecutableFloatString __add = new ExecutableFloatString(); // Construct default object for add
		__add.sString = "0.0f";
		_add = new ExecutableFloatString( owner, __add );
		ExecutableFloatString __mul = new ExecutableFloatString(); // Construct default object for mul
		__mul.sString = "1.0f";
		_mul = new ExecutableFloatString( owner, __mul );
		_senderMatchTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_matchTargetInverted = new UndoRedo<bool>( owner, false );
		_treatDelegatedByDelegator = new UndoRedo<bool>( owner, false );
		_objectFilter = new UndoRedo<ESpellTarget>( owner, ESpellTarget.All );
		_checkSender = new UndoRedo<ETriggerEventCheckSender>( owner, ETriggerEventCheckSender.None );
		_flags = new UndoRedo<ETriggerEventFlags>( owner, ETriggerEventFlags.None );
		___parent.Changed += FireChangedEvent;
		_damageTypeFilter.Changed += FireChangedEvent;
		_abilityFilter.Changed += FireChangedEvent;
		_add.Changed += FireChangedEvent;
		_mul.Changed += FireChangedEvent;
		_senderMatchTarget.Changed += FireChangedEvent;
		_matchTargetInverted.Changed += FireChangedEvent;
		_treatDelegatedByDelegator.Changed += FireChangedEvent;
		_objectFilter.Changed += FireChangedEvent;
		_checkSender.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
	}

	public EventProcessorDamageTransformer()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorDamageTransformer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorDamageTransformer" );
		damageTypeFilter = source.damageTypeFilter;
		abilityFilter = source.abilityFilter;
		add = source.add;
		mul = source.mul;
		senderMatchTarget = source.senderMatchTarget;
		matchTargetInverted = source.matchTargetInverted;
		treatDelegatedByDelegator = source.treatDelegatedByDelegator;
		objectFilter = source.objectFilter;
		checkSender = source.checkSender;
		flags = source.flags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorDamageTransformer source = _source as EventProcessorDamageTransformer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorDamageTransformer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorDamageTransformer newParent = rawParent == null ? null : rawParent.Get<EventProcessorDamageTransformer>();
		if ( newParent == null && _newParent is EventProcessorDamageTransformer )
			newParent = _newParent as EventProcessorDamageTransformer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_damageTypeFilter.SetParent( newParent == null ? null : newParent._damageTypeFilter );
		_abilityFilter.SetParent( newParent == null ? null : newParent._abilityFilter );
		_add.SetParent( newParent == null ? null : newParent._add );
		_mul.SetParent( newParent == null ? null : newParent._mul );
		_senderMatchTarget.SetParent( newParent == null ? null : newParent._senderMatchTarget );
		_matchTargetInverted.SetParent( newParent == null ? null : newParent._matchTargetInverted );
		_treatDelegatedByDelegator.SetParent( newParent == null ? null : newParent._treatDelegatedByDelegator );
		_objectFilter.SetParent( newParent == null ? null : newParent._objectFilter );
		_checkSender.SetParent( newParent == null ? null : newParent._checkSender );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_damageTypeFilter.Reset();
		_abilityFilter.Reset();
		_add.Reset();
		_mul.Reset();
		_senderMatchTarget.Reset();
		_matchTargetInverted.Reset();
		_treatDelegatedByDelegator.Reset();
		_objectFilter.Reset();
		_checkSender.Reset();
		_flags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_damageTypeFilter.IsDerivedFromParent()
			&& _abilityFilter.IsDerivedFromParent()
			&& _add.IsDerivedFromParent()
			&& _mul.IsDerivedFromParent()
			&& _senderMatchTarget.IsDerivedFromParent()
			&& _matchTargetInverted.IsDerivedFromParent()
			&& _treatDelegatedByDelegator.IsDerivedFromParent()
			&& _objectFilter.IsDerivedFromParent()
			&& _checkSender.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "damageTypeFilter" )
			_damageTypeFilter.Reset();
		else if ( fieldName == "abilityFilter" )
			_abilityFilter.Reset();
		else if ( fieldName == "add" )
			_add.Reset();
		else if ( fieldName == "mul" )
			_mul.Reset();
		else if ( fieldName == "senderMatchTarget" )
			_senderMatchTarget.Reset();
		else if ( fieldName == "matchTargetInverted" )
			_matchTargetInverted.Reset();
		else if ( fieldName == "treatDelegatedByDelegator" )
			_treatDelegatedByDelegator.Reset();
		else if ( fieldName == "objectFilter" )
			_objectFilter.Reset();
		else if ( fieldName == "checkSender" )
			_checkSender.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "damageTypeFilter" )
			return _damageTypeFilter.IsDerivedFromParent();
		if ( fieldName == "abilityFilter" )
			return _abilityFilter.IsDerivedFromParent();
		if ( fieldName == "add" )
			return _add.IsDerivedFromParent();
		if ( fieldName == "mul" )
			return _mul.IsDerivedFromParent();
		if ( fieldName == "senderMatchTarget" )
			return _senderMatchTarget.IsDerivedFromParent();
		if ( fieldName == "matchTargetInverted" )
			return _matchTargetInverted.IsDerivedFromParent();
		if ( fieldName == "treatDelegatedByDelegator" )
			return _treatDelegatedByDelegator.IsDerivedFromParent();
		if ( fieldName == "objectFilter" )
			return _objectFilter.IsDerivedFromParent();
		if ( fieldName == "checkSender" )
			return _checkSender.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorGroup", "PFTriggerApplicator.h")]
[TypeId(0x0F7563C0)]
[UseTypeName("EVNT")]
public class EventProcessorGroup : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorGroup> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorGroup> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<EventProcessorBase>> _processors;

	public libdb.IChangeableList<DBPtr<EventProcessorBase>> processors { get { return _processors; } set { _processors.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorGroup>(owner);
		_processors = new UndoRedoAssignableList<DBPtr<EventProcessorBase>>( owner );
		___parent.Changed += FireChangedEvent;
		_processors.Changed += FireChangedEvent;
	}

	public EventProcessorGroup()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorGroup source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorGroup" );
		processors = source.processors;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorGroup source = _source as EventProcessorGroup;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorGroup" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorGroup newParent = rawParent == null ? null : rawParent.Get<EventProcessorGroup>();
		if ( newParent == null && _newParent is EventProcessorGroup )
			newParent = _newParent as EventProcessorGroup;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_processors.SetParent( newParent == null ? null : newParent._processors );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_processors.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_processors.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "processors" )
			_processors.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "processors" )
			return _processors.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorIncomingDamage", "PFTriggerApplicator.h")]
[TypeId(0xE78A3CC0)]
[UseTypeName("EVNT")]
public class EventProcessorIncomingDamage : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorIncomingDamage> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorIncomingDamage> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<DelegateDamageApplicator> _damageDelegate;
	private UndoRedo<EApplicatorApplyTarget> _damageDelegateOwner;

	[Description( "Делегированный указанным аппликатором урон можно получить из отдельной переменной" )]
	public DBPtr<DelegateDamageApplicator> damageDelegate { get { return _damageDelegate.Get(); } set { _damageDelegate.Set( value ); } }

	[Description( "Кто делегирует урон" )]
	public EApplicatorApplyTarget damageDelegateOwner { get { return _damageDelegateOwner.Get(); } set { _damageDelegateOwner.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorIncomingDamage>(owner);
		_damageDelegate = new UndoRedoDBPtr<DelegateDamageApplicator>( owner );
		_damageDelegateOwner = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		___parent.Changed += FireChangedEvent;
		_damageDelegate.Changed += FireChangedEvent;
		_damageDelegateOwner.Changed += FireChangedEvent;
	}

	public EventProcessorIncomingDamage()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorIncomingDamage source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorIncomingDamage" );
		damageDelegate = source.damageDelegate;
		damageDelegateOwner = source.damageDelegateOwner;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorIncomingDamage source = _source as EventProcessorIncomingDamage;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorIncomingDamage" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorIncomingDamage newParent = rawParent == null ? null : rawParent.Get<EventProcessorIncomingDamage>();
		if ( newParent == null && _newParent is EventProcessorIncomingDamage )
			newParent = _newParent as EventProcessorIncomingDamage;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_damageDelegate.SetParent( newParent == null ? null : newParent._damageDelegate );
		_damageDelegateOwner.SetParent( newParent == null ? null : newParent._damageDelegateOwner );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_damageDelegate.Reset();
		_damageDelegateOwner.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_damageDelegate.IsDerivedFromParent()
			&& _damageDelegateOwner.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "damageDelegate" )
			_damageDelegate.Reset();
		else if ( fieldName == "damageDelegateOwner" )
			_damageDelegateOwner.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "damageDelegate" )
			return _damageDelegate.IsDerivedFromParent();
		if ( fieldName == "damageDelegateOwner" )
			return _damageDelegateOwner.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorLastHit", "PFTriggerApplicator.h")]
[TypeId(0xE7768540)]
[UseTypeName("EVNT")]
public class EventProcessorLastHit : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorLastHit> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorLastHit> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorLastHit>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public EventProcessorLastHit()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorLastHit source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorLastHit" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorLastHit source = _source as EventProcessorLastHit;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorLastHit" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorLastHit newParent = rawParent == null ? null : rawParent.Get<EventProcessorLastHit>();
		if ( newParent == null && _newParent is EventProcessorLastHit )
			newParent = _newParent as EventProcessorLastHit;
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

[FactoryImpl("Create", "NWorld::PFEventProcessorOnConsumableObtained", "PFTriggerApplicator.h")]
[TypeId(0xE79B9C01)]
[UseTypeName("EVNT")]
public class EventProcessorOnConsumableObtained : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorOnConsumableObtained> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorOnConsumableObtained> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Consumable> _consumable;
	private UndoRedo<EConsumableOriginFlags> _origin;

	[Description( "Консумабл на получение которого реагировать. Оставить пустым если надо реагировать на любой." )]
	public DBPtr<Consumable> consumable { get { return _consumable.Get(); } set { _consumable.Set( value ); } }

	[Description( "На какое происхождение консумабла реагировать" )]
	public EConsumableOriginFlags origin { get { return _origin.Get(); } set { _origin.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorOnConsumableObtained>(owner);
		_consumable = new UndoRedoDBPtr<Consumable>( owner );
		_origin = new UndoRedo<EConsumableOriginFlags>( owner, (EConsumableOriginFlags)0 );
		___parent.Changed += FireChangedEvent;
		_consumable.Changed += FireChangedEvent;
		_origin.Changed += FireChangedEvent;
	}

	public EventProcessorOnConsumableObtained()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorOnConsumableObtained source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOnConsumableObtained" );
		consumable = source.consumable;
		origin = source.origin;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorOnConsumableObtained source = _source as EventProcessorOnConsumableObtained;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOnConsumableObtained" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorOnConsumableObtained newParent = rawParent == null ? null : rawParent.Get<EventProcessorOnConsumableObtained>();
		if ( newParent == null && _newParent is EventProcessorOnConsumableObtained )
			newParent = _newParent as EventProcessorOnConsumableObtained;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_consumable.SetParent( newParent == null ? null : newParent._consumable );
		_origin.SetParent( newParent == null ? null : newParent._origin );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_consumable.Reset();
		_origin.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_consumable.IsDerivedFromParent()
			&& _origin.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "consumable" )
			_consumable.Reset();
		else if ( fieldName == "origin" )
			_origin.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "consumable" )
			return _consumable.IsDerivedFromParent();
		if ( fieldName == "origin" )
			return _origin.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorOnDeath", "PFTriggerApplicator.h")]
[TypeId(0x0F72CB40)]
[UseTypeName("EVNT")]
public class EventProcessorOnDeath : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorOnDeath> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorOnDeath> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _castSpellDelay;
	private UndoRedo<EApplicatorApplyTarget> _senderMatchTarget;
	private UndoRedo<ESpellTarget> _objectFilter;
	private UndoRedo<ETriggerEventCheckSender> _checkSender;

	[Description( "Delay after death before apply spell" )]
	public ExecutableFloatString castSpellDelay { get { return _castSpellDelay; } set { _castSpellDelay.Assign( value ); } }

	[Description( "Сравнить киллера с целью аппликатора" )]
	public EApplicatorApplyTarget senderMatchTarget { get { return _senderMatchTarget.Get(); } set { _senderMatchTarget.Set( value ); } }

	[Description( "Фильтр по типу объекта, посылающего событие" )]
	public ESpellTarget objectFilter { get { return _objectFilter.Get(); } set { _objectFilter.Set( value ); } }

	[Description( "Дополнительные проверки посылающего событие" )]
	public ETriggerEventCheckSender checkSender { get { return _checkSender.Get(); } set { _checkSender.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorOnDeath>(owner);
		ExecutableFloatString __castSpellDelay = new ExecutableFloatString(); // Construct default object for castSpellDelay
		__castSpellDelay.sString = "0.0f";
		_castSpellDelay = new ExecutableFloatString( owner, __castSpellDelay );
		_senderMatchTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_objectFilter = new UndoRedo<ESpellTarget>( owner, ESpellTarget.All );
		_checkSender = new UndoRedo<ETriggerEventCheckSender>( owner, ETriggerEventCheckSender.None );
		___parent.Changed += FireChangedEvent;
		_castSpellDelay.Changed += FireChangedEvent;
		_senderMatchTarget.Changed += FireChangedEvent;
		_objectFilter.Changed += FireChangedEvent;
		_checkSender.Changed += FireChangedEvent;
	}

	public EventProcessorOnDeath()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorOnDeath source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOnDeath" );
		castSpellDelay = source.castSpellDelay;
		senderMatchTarget = source.senderMatchTarget;
		objectFilter = source.objectFilter;
		checkSender = source.checkSender;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorOnDeath source = _source as EventProcessorOnDeath;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOnDeath" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorOnDeath newParent = rawParent == null ? null : rawParent.Get<EventProcessorOnDeath>();
		if ( newParent == null && _newParent is EventProcessorOnDeath )
			newParent = _newParent as EventProcessorOnDeath;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_castSpellDelay.SetParent( newParent == null ? null : newParent._castSpellDelay );
		_senderMatchTarget.SetParent( newParent == null ? null : newParent._senderMatchTarget );
		_objectFilter.SetParent( newParent == null ? null : newParent._objectFilter );
		_checkSender.SetParent( newParent == null ? null : newParent._checkSender );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_castSpellDelay.Reset();
		_senderMatchTarget.Reset();
		_objectFilter.Reset();
		_checkSender.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_castSpellDelay.IsDerivedFromParent()
			&& _senderMatchTarget.IsDerivedFromParent()
			&& _objectFilter.IsDerivedFromParent()
			&& _checkSender.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "castSpellDelay" )
			_castSpellDelay.Reset();
		else if ( fieldName == "senderMatchTarget" )
			_senderMatchTarget.Reset();
		else if ( fieldName == "objectFilter" )
			_objectFilter.Reset();
		else if ( fieldName == "checkSender" )
			_checkSender.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "castSpellDelay" )
			return _castSpellDelay.IsDerivedFromParent();
		if ( fieldName == "senderMatchTarget" )
			return _senderMatchTarget.IsDerivedFromParent();
		if ( fieldName == "objectFilter" )
			return _objectFilter.IsDerivedFromParent();
		if ( fieldName == "checkSender" )
			return _checkSender.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorOnTarget", "PFTriggerApplicator.h")]
[TypeId(0x0F72CB40)]
[UseTypeName("EVNT")]
public class EventProcessorOnTarget : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorOnTarget> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorOnTarget> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;
	private ExecutableFloatString _minTargets;

	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	public ExecutableFloatString minTargets { get { return _minTargets; } set { _minTargets.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorOnTarget>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		ExecutableFloatString __minTargets = new ExecutableFloatString(); // Construct default object for minTargets
		__minTargets.sString = "1.0f";
		_minTargets = new ExecutableFloatString( owner, __minTargets );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_minTargets.Changed += FireChangedEvent;
	}

	public EventProcessorOnTarget()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorOnTarget source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOnTarget" );
		targetSelector = source.targetSelector;
		minTargets = source.minTargets;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorOnTarget source = _source as EventProcessorOnTarget;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOnTarget" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorOnTarget newParent = rawParent == null ? null : rawParent.Get<EventProcessorOnTarget>();
		if ( newParent == null && _newParent is EventProcessorOnTarget )
			newParent = _newParent as EventProcessorOnTarget;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_minTargets.SetParent( newParent == null ? null : newParent._minTargets );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_minTargets.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _minTargets.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "minTargets" )
			_minTargets.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "minTargets" )
			return _minTargets.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorOnUseAbilityForceStrike", "PFTriggerApplicator.h")]
[TypeId(0x0F741400)]
[UseTypeName("EVNT")]
public class EventProcessorOnUseAbilityForceStrike : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorOnUseAbilityForceStrike> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorOnUseAbilityForceStrike> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TriggerAbilitiesFilter _filter;
	private UndoRedo<string> _applicatorName;

	[Description( "Abilities to process" )]
	public TriggerAbilitiesFilter filter { get { return _filter; } set { _filter.Assign( value ); } }

	[Description( "formulaName of SpellPeriodicallyVisual applicator to control (must be placed in the same dispatch!)" )]
	public string applicatorName { get { return _applicatorName.Get(); } set { _applicatorName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorOnUseAbilityForceStrike>(owner);
		_filter = new TriggerAbilitiesFilter( owner );
		_applicatorName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_filter.Changed += FireChangedEvent;
		_applicatorName.Changed += FireChangedEvent;
	}

	public EventProcessorOnUseAbilityForceStrike()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorOnUseAbilityForceStrike source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOnUseAbilityForceStrike" );
		filter = source.filter;
		applicatorName = source.applicatorName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorOnUseAbilityForceStrike source = _source as EventProcessorOnUseAbilityForceStrike;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOnUseAbilityForceStrike" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorOnUseAbilityForceStrike newParent = rawParent == null ? null : rawParent.Get<EventProcessorOnUseAbilityForceStrike>();
		if ( newParent == null && _newParent is EventProcessorOnUseAbilityForceStrike )
			newParent = _newParent as EventProcessorOnUseAbilityForceStrike;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_filter.SetParent( newParent == null ? null : newParent._filter );
		_applicatorName.SetParent( newParent == null ? null : newParent._applicatorName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_filter.Reset();
		_applicatorName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_filter.IsDerivedFromParent()
			&& _applicatorName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "filter" )
			_filter.Reset();
		else if ( fieldName == "applicatorName" )
			_applicatorName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "filter" )
			return _filter.IsDerivedFromParent();
		if ( fieldName == "applicatorName" )
			return _applicatorName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorOutgoingDamage", "PFTriggerApplicator.h")]
[TypeId(0xE7A69380)]
[UseTypeName("EVNT")]
public class EventProcessorOutgoingDamage : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorOutgoingDamage> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorOutgoingDamage> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EDamageFilter> _damageTypeFilter;
	private TriggerAbilitiesFilter _abilityFilter;
	private ExecutableFloatString _modifiedDamage;

	public EDamageFilter damageTypeFilter { get { return _damageTypeFilter.Get(); } set { _damageTypeFilter.Set( value ); } }

	public TriggerAbilitiesFilter abilityFilter { get { return _abilityFilter; } set { _abilityFilter.Assign( value ); } }

	[Description( "Выходной урон. Доступ к урону на входе через appl.vDamage" )]
	public ExecutableFloatString modifiedDamage { get { return _modifiedDamage; } set { _modifiedDamage.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorOutgoingDamage>(owner);
		_damageTypeFilter = new UndoRedo<EDamageFilter>( owner, EDamageFilter.All );
		_abilityFilter = new TriggerAbilitiesFilter( owner );
		ExecutableFloatString __modifiedDamage = new ExecutableFloatString(); // Construct default object for modifiedDamage
		__modifiedDamage.sString = "0.0f";
		_modifiedDamage = new ExecutableFloatString( owner, __modifiedDamage );
		___parent.Changed += FireChangedEvent;
		_damageTypeFilter.Changed += FireChangedEvent;
		_abilityFilter.Changed += FireChangedEvent;
		_modifiedDamage.Changed += FireChangedEvent;
	}

	public EventProcessorOutgoingDamage()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorOutgoingDamage source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOutgoingDamage" );
		damageTypeFilter = source.damageTypeFilter;
		abilityFilter = source.abilityFilter;
		modifiedDamage = source.modifiedDamage;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorOutgoingDamage source = _source as EventProcessorOutgoingDamage;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorOutgoingDamage" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorOutgoingDamage newParent = rawParent == null ? null : rawParent.Get<EventProcessorOutgoingDamage>();
		if ( newParent == null && _newParent is EventProcessorOutgoingDamage )
			newParent = _newParent as EventProcessorOutgoingDamage;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_damageTypeFilter.SetParent( newParent == null ? null : newParent._damageTypeFilter );
		_abilityFilter.SetParent( newParent == null ? null : newParent._abilityFilter );
		_modifiedDamage.SetParent( newParent == null ? null : newParent._modifiedDamage );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_damageTypeFilter.Reset();
		_abilityFilter.Reset();
		_modifiedDamage.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_damageTypeFilter.IsDerivedFromParent()
			&& _abilityFilter.IsDerivedFromParent()
			&& _modifiedDamage.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "damageTypeFilter" )
			_damageTypeFilter.Reset();
		else if ( fieldName == "abilityFilter" )
			_abilityFilter.Reset();
		else if ( fieldName == "modifiedDamage" )
			_modifiedDamage.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "damageTypeFilter" )
			return _damageTypeFilter.IsDerivedFromParent();
		if ( fieldName == "abilityFilter" )
			return _abilityFilter.IsDerivedFromParent();
		if ( fieldName == "modifiedDamage" )
			return _modifiedDamage.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorPickupGlyph", "PFTriggerApplicator.h")]
[TypeId(0x37A78C40)]
[UseTypeName("EVNT")]
public class EventProcessorPickupGlyph : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorPickupGlyph> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorPickupGlyph> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TriggerAbilitiesFilter _filter;

	public TriggerAbilitiesFilter filter { get { return _filter; } set { _filter.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorPickupGlyph>(owner);
		_filter = new TriggerAbilitiesFilter( owner );
		___parent.Changed += FireChangedEvent;
		_filter.Changed += FireChangedEvent;
	}

	public EventProcessorPickupGlyph()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorPickupGlyph source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorPickupGlyph" );
		filter = source.filter;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorPickupGlyph source = _source as EventProcessorPickupGlyph;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorPickupGlyph" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorPickupGlyph newParent = rawParent == null ? null : rawParent.Get<EventProcessorPickupGlyph>();
		if ( newParent == null && _newParent is EventProcessorPickupGlyph )
			newParent = _newParent as EventProcessorPickupGlyph;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_filter.SetParent( newParent == null ? null : newParent._filter );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_filter.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_filter.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "filter" )
			_filter.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "filter" )
			return _filter.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFEventProcessorUnitDieNearMe", "PFTriggerApplicator.h")]
[TypeId(0x0F72CB40)]
[UseTypeName("EVNT")]
public class EventProcessorUnitDieNearMe : EventProcessorBase
{
	private UndoRedoDBPtr<EventProcessorUnitDieNearMe> ___parent;
	[HideInOutliner]
	public new DBPtr<EventProcessorUnitDieNearMe> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _range;
	private UndoRedo<ESpellTarget> _targets;
	private UndoRedo<UnitDieKillersFlags> _killerFlags;
	private UndoRedo<EApplicatorApplyTarget> _senderMatchTarget;
	private UndoRedo<ETriggerEventCheckSender> _checkSender;

	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	public ESpellTarget targets { get { return _targets.Get(); } set { _targets.Set( value ); } }

	public UnitDieKillersFlags killerFlags { get { return _killerFlags.Get(); } set { _killerFlags.Set( value ); } }

	[Description( "Сравнить убитого с целью аппликатора" )]
	public EApplicatorApplyTarget senderMatchTarget { get { return _senderMatchTarget.Get(); } set { _senderMatchTarget.Set( value ); } }

	[Description( "Дополнительные проверки посылающего событие" )]
	public ETriggerEventCheckSender checkSender { get { return _checkSender.Get(); } set { _checkSender.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EventProcessorUnitDieNearMe>(owner);
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		_targets = new UndoRedo<ESpellTarget>( owner, ESpellTarget.AllEnemies | ESpellTarget.Ally );
		_killerFlags = new UndoRedo<UnitDieKillersFlags>( owner, UnitDieKillersFlags.KilledByAll );
		_senderMatchTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_checkSender = new UndoRedo<ETriggerEventCheckSender>( owner, ETriggerEventCheckSender.None );
		___parent.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_targets.Changed += FireChangedEvent;
		_killerFlags.Changed += FireChangedEvent;
		_senderMatchTarget.Changed += FireChangedEvent;
		_checkSender.Changed += FireChangedEvent;
	}

	public EventProcessorUnitDieNearMe()
	{
		Initialize( this );
	}
	private void AssignSelf( EventProcessorUnitDieNearMe source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorUnitDieNearMe" );
		range = source.range;
		targets = source.targets;
		killerFlags = source.killerFlags;
		senderMatchTarget = source.senderMatchTarget;
		checkSender = source.checkSender;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EventProcessorUnitDieNearMe source = _source as EventProcessorUnitDieNearMe;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EventProcessorUnitDieNearMe" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EventProcessorUnitDieNearMe newParent = rawParent == null ? null : rawParent.Get<EventProcessorUnitDieNearMe>();
		if ( newParent == null && _newParent is EventProcessorUnitDieNearMe )
			newParent = _newParent as EventProcessorUnitDieNearMe;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_range.SetParent( newParent == null ? null : newParent._range );
		_targets.SetParent( newParent == null ? null : newParent._targets );
		_killerFlags.SetParent( newParent == null ? null : newParent._killerFlags );
		_senderMatchTarget.SetParent( newParent == null ? null : newParent._senderMatchTarget );
		_checkSender.SetParent( newParent == null ? null : newParent._checkSender );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_range.Reset();
		_targets.Reset();
		_killerFlags.Reset();
		_senderMatchTarget.Reset();
		_checkSender.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_range.IsDerivedFromParent()
			&& _targets.IsDerivedFromParent()
			&& _killerFlags.IsDerivedFromParent()
			&& _senderMatchTarget.IsDerivedFromParent()
			&& _checkSender.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "targets" )
			_targets.Reset();
		else if ( fieldName == "killerFlags" )
			_killerFlags.Reset();
		else if ( fieldName == "senderMatchTarget" )
			_senderMatchTarget.Reset();
		else if ( fieldName == "checkSender" )
			_checkSender.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "targets" )
			return _targets.IsDerivedFromParent();
		if ( fieldName == "killerFlags" )
			return _killerFlags.IsDerivedFromParent();
		if ( fieldName == "senderMatchTarget" )
			return _senderMatchTarget.IsDerivedFromParent();
		if ( fieldName == "checkSender" )
			return _checkSender.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplEye", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F73BB40)]
[UseTypeName("APLR")]
public class EyeApplicator : BuffApplicator
{
	private UndoRedoDBPtr<EyeApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<EyeApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _visRange;
	private UndoRedo<EFactionFlags> _flags;
	private UndoRedo<EApplicatorApplyTarget> _eyeTarget;
	private UndoRedo<bool> _cancelObstacles;

	public ExecutableFloatString visRange { get { return _visRange; } set { _visRange.Assign( value ); } }

	[Description( "Какой фракции открыть туман" )]
	public EFactionFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[Description( "Target to open warfog at" )]
	public EApplicatorApplyTarget eyeTarget { get { return _eyeTarget.Get(); } set { _eyeTarget.Set( value ); } }

	[Description( "Cancel hiding beyond obstacles" )]
	public bool cancelObstacles { get { return _cancelObstacles.Get(); } set { _cancelObstacles.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EyeApplicator>(owner);
		ExecutableFloatString __visRange = new ExecutableFloatString(); // Construct default object for visRange
		__visRange.sString = "1.0f";
		_visRange = new ExecutableFloatString( owner, __visRange );
		_flags = new UndoRedo<EFactionFlags>( owner, EFactionFlags.Self );
		_eyeTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_cancelObstacles = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_visRange.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_eyeTarget.Changed += FireChangedEvent;
		_cancelObstacles.Changed += FireChangedEvent;
	}

	public EyeApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( EyeApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EyeApplicator" );
		visRange = source.visRange;
		flags = source.flags;
		eyeTarget = source.eyeTarget;
		cancelObstacles = source.cancelObstacles;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EyeApplicator source = _source as EyeApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EyeApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EyeApplicator newParent = rawParent == null ? null : rawParent.Get<EyeApplicator>();
		if ( newParent == null && _newParent is EyeApplicator )
			newParent = _newParent as EyeApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_visRange.SetParent( newParent == null ? null : newParent._visRange );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_eyeTarget.SetParent( newParent == null ? null : newParent._eyeTarget );
		_cancelObstacles.SetParent( newParent == null ? null : newParent._cancelObstacles );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_visRange.Reset();
		_flags.Reset();
		_eyeTarget.Reset();
		_cancelObstacles.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_visRange.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _eyeTarget.IsDerivedFromParent()
			&& _cancelObstacles.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "visRange" )
			_visRange.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "eyeTarget" )
			_eyeTarget.Reset();
		else if ( fieldName == "cancelObstacles" )
			_cancelObstacles.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "visRange" )
			return _visRange.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "eyeTarget" )
			return _eyeTarget.IsDerivedFromParent();
		if ( fieldName == "cancelObstacles" )
			return _cancelObstacles.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFFilterTargetSelector", "PFTargetSelector.h")]
[TypeId(0x0F738B02)]
[UseTypeName("TGSL")]
public class FilterTargetSelector : MultipleTargetSelector
{
	private UndoRedoDBPtr<FilterTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<FilterTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;
	private UndoRedoAssignableList<DBPtr<Unit>> _suitableUnits;

	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	public libdb.IChangeableList<DBPtr<Unit>> suitableUnits { get { return _suitableUnits; } set { _suitableUnits.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FilterTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		_suitableUnits = new UndoRedoAssignableList<DBPtr<Unit>>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_suitableUnits.Changed += FireChangedEvent;
	}

	public FilterTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( FilterTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FilterTargetSelector" );
		targetSelector = source.targetSelector;
		suitableUnits = source.suitableUnits;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FilterTargetSelector source = _source as FilterTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FilterTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FilterTargetSelector newParent = rawParent == null ? null : rawParent.Get<FilterTargetSelector>();
		if ( newParent == null && _newParent is FilterTargetSelector )
			newParent = _newParent as FilterTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_suitableUnits.SetParent( newParent == null ? null : newParent._suitableUnits );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_suitableUnits.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _suitableUnits.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "suitableUnits" )
			_suitableUnits.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "suitableUnits" )
			return _suitableUnits.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFFirstTargetSelector", "PFTargetSelector.h")]
[TypeId(0x0F738B00)]
[UseTypeName("TGSL")]
public class FirstTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<FirstTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<FirstTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;
	private UndoRedo<bool> _nearestTarget;

	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	public bool nearestTarget { get { return _nearestTarget.Get(); } set { _nearestTarget.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FirstTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		_nearestTarget = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_nearestTarget.Changed += FireChangedEvent;
	}

	public FirstTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( FirstTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FirstTargetSelector" );
		targetSelector = source.targetSelector;
		nearestTarget = source.nearestTarget;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FirstTargetSelector source = _source as FirstTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FirstTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FirstTargetSelector newParent = rawParent == null ? null : rawParent.Get<FirstTargetSelector>();
		if ( newParent == null && _newParent is FirstTargetSelector )
			newParent = _newParent as FirstTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_nearestTarget.SetParent( newParent == null ? null : newParent._nearestTarget );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_nearestTarget.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _nearestTarget.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "nearestTarget" )
			_nearestTarget.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "nearestTarget" )
			return _nearestTarget.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFFixToCenterTargetSelector", "PFTargetSelector.h")]
[TypeId(0xEF9752C0)]
[UseTypeName("TGSL")]
public class FixToCenterTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<FixToCenterTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<FixToCenterTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;
	private UndoRedo<string> _nameScriptArea;

	[Description( "Target selector to select from" )]
	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Name of script area that is used for definition parameters" )]
	public string nameScriptArea { get { return _nameScriptArea.Get(); } set { _nameScriptArea.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FixToCenterTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_nameScriptArea = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_nameScriptArea.Changed += FireChangedEvent;
	}

	public FixToCenterTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( FixToCenterTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FixToCenterTargetSelector" );
		targetSelector = source.targetSelector;
		nameScriptArea = source.nameScriptArea;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FixToCenterTargetSelector source = _source as FixToCenterTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FixToCenterTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FixToCenterTargetSelector newParent = rawParent == null ? null : rawParent.Get<FixToCenterTargetSelector>();
		if ( newParent == null && _newParent is FixToCenterTargetSelector )
			newParent = _newParent as FixToCenterTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_nameScriptArea.SetParent( newParent == null ? null : newParent._nameScriptArea );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_nameScriptArea.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _nameScriptArea.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "nameScriptArea" )
			_nameScriptArea.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "nameScriptArea" )
			return _nameScriptArea.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFApplFlags", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B06)]
[UseTypeName("APLR")]
public class FlagsApplicator : BuffApplicator
{
	private UndoRedoDBPtr<FlagsApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<FlagsApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EUnitFlag> _flag;
	private UndoRedoAssignableList<DBPtr<Ability>> _talents;
	private UndoRedoAssignableList<DBPtr<Ability>> _consumables;
	private UndoRedo<EUseMode> _useListAs;

	[Category( "Flags" )]
	[Description( "Specify different flags to be set" )]
	public EUnitFlag flag { get { return _flag.Get(); } set { _flag.Set( value ); } }

	[Description( "Talents to forbid" )]
	public libdb.IChangeableList<DBPtr<Ability>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	[Description( "Consumables to forbid" )]
	public libdb.IChangeableList<DBPtr<Ability>> consumables { get { return _consumables; } set { _consumables.Assign( value ); } }

	[Description( "Режим работы со списком (talents only)" )]
	public EUseMode useListAs { get { return _useListAs.Get(); } set { _useListAs.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FlagsApplicator>(owner);
		_flag = new UndoRedo<EUnitFlag>( owner, (EUnitFlag)0 );
		_talents = new UndoRedoAssignableList<DBPtr<Ability>>( owner );
		_consumables = new UndoRedoAssignableList<DBPtr<Ability>>( owner );
		_useListAs = new UndoRedo<EUseMode>( owner, EUseMode.ListAsRule );
		___parent.Changed += FireChangedEvent;
		_flag.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
		_consumables.Changed += FireChangedEvent;
		_useListAs.Changed += FireChangedEvent;
	}

	public FlagsApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( FlagsApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FlagsApplicator" );
		flag = source.flag;
		talents = source.talents;
		consumables = source.consumables;
		useListAs = source.useListAs;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FlagsApplicator source = _source as FlagsApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FlagsApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FlagsApplicator newParent = rawParent == null ? null : rawParent.Get<FlagsApplicator>();
		if ( newParent == null && _newParent is FlagsApplicator )
			newParent = _newParent as FlagsApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_flag.SetParent( newParent == null ? null : newParent._flag );
		_talents.SetParent( newParent == null ? null : newParent._talents );
		_consumables.SetParent( newParent == null ? null : newParent._consumables );
		_useListAs.SetParent( newParent == null ? null : newParent._useListAs );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_flag.Reset();
		_talents.Reset();
		_consumables.Reset();
		_useListAs.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_flag.IsDerivedFromParent()
			&& _talents.IsDerivedFromParent()
			&& _consumables.IsDerivedFromParent()
			&& _useListAs.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "flag" )
			_flag.Reset();
		else if ( fieldName == "talents" )
			_talents.Reset();
		else if ( fieldName == "consumables" )
			_consumables.Reset();
		else if ( fieldName == "useListAs" )
			_useListAs.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "flag" )
			return _flag.IsDerivedFromParent();
		if ( fieldName == "talents" )
			return _talents.IsDerivedFromParent();
		if ( fieldName == "consumables" )
			return _consumables.IsDerivedFromParent();
		if ( fieldName == "useListAs" )
			return _useListAs.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplFly", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2B789AC0)]
[UseTypeName("APLR")]
public class FlyApplicator : BuffApplicator
{
	private UndoRedoDBPtr<FlyApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<FlyApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _flightHeight;
	private UndoRedo<float> _startTime;
	private UndoRedo<float> _stopTime;
	private UndoRedo<float> _animatedStopTime;
	private UndoRedo<EGhostMoveMode> _collisionFlags;
	private UndoRedo<bool> _push;
	private UndoRedoDBPtr<Spell> _startSpell;
	private UndoRedoDBPtr<Spell> _stopSpell;
	private UndoRedoAssignableList<AnimStateChanger> _replaceAnimations;
	private UndoRedo<float> _radiusFixObstacle;

	[Description( "Высота полёта" )]
	public float flightHeight { get { return _flightHeight.Get(); } set { _flightHeight.Set( value ); } }

	[Description( "Время взлёта" )]
	public float startTime { get { return _startTime.Get(); } set { _startTime.Set( value ); } }

	[Description( "Время приземления" )]
	public float stopTime { get { return _stopTime.Get(); } set { _stopTime.Set( value ); } }

	[Description( "Длительность анимации приземления" )]
	public float animatedStopTime { get { return _animatedStopTime.Get(); } set { _animatedStopTime.Set( value ); } }

	[Description( "Объекты, через которые мы можем перелетать" )]
	public EGhostMoveMode collisionFlags { get { return _collisionFlags.Get(); } set { _collisionFlags.Set( value ); } }

	[Description( "Расталкивать ли юнитов при приземлении" )]
	public bool push { get { return _push.Get(); } set { _push.Set( value ); } }

	[Description( "Spell выполняемый до начала работы аппликатора" )]
	public DBPtr<Spell> startSpell { get { return _startSpell.Get(); } set { _startSpell.Set( value ); } }

	[Description( "Spell выполняемый после окончания работы аппликатора" )]
	public DBPtr<Spell> stopSpell { get { return _stopSpell.Get(); } set { _stopSpell.Set( value ); } }

	[Description( "Замены анимаций" )]
	public libdb.IChangeableList<AnimStateChanger> replaceAnimations { get { return _replaceAnimations; } set { _replaceAnimations.Assign( value ); } }

	[Description( "Радиус, в рамках которого будет исправляться позиция приземления после полёта" )]
	public float radiusFixObstacle { get { return _radiusFixObstacle.Get(); } set { _radiusFixObstacle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FlyApplicator>(owner);
		_flightHeight = new UndoRedo<float>( owner, 3.0f );
		_startTime = new UndoRedo<float>( owner, 1.0f );
		_stopTime = new UndoRedo<float>( owner, 1.0f );
		_animatedStopTime = new UndoRedo<float>( owner, 1.0f );
		_collisionFlags = new UndoRedo<EGhostMoveMode>( owner, EGhostMoveMode.IgnoreStatic | EGhostMoveMode.IgnoreBuildings | EGhostMoveMode.IgnoreDynamic );
		_push = new UndoRedo<bool>( owner, false );
		_startSpell = new UndoRedoDBPtr<Spell>( owner );
		_stopSpell = new UndoRedoDBPtr<Spell>( owner );
		_replaceAnimations = new UndoRedoAssignableList<AnimStateChanger>( owner );
		_radiusFixObstacle = new UndoRedo<float>( owner, 30.0f );
		___parent.Changed += FireChangedEvent;
		_flightHeight.Changed += FireChangedEvent;
		_startTime.Changed += FireChangedEvent;
		_stopTime.Changed += FireChangedEvent;
		_animatedStopTime.Changed += FireChangedEvent;
		_collisionFlags.Changed += FireChangedEvent;
		_push.Changed += FireChangedEvent;
		_startSpell.Changed += FireChangedEvent;
		_stopSpell.Changed += FireChangedEvent;
		_replaceAnimations.Changed += FireChangedEvent;
		_radiusFixObstacle.Changed += FireChangedEvent;
	}

	public FlyApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( FlyApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FlyApplicator" );
		flightHeight = source.flightHeight;
		startTime = source.startTime;
		stopTime = source.stopTime;
		animatedStopTime = source.animatedStopTime;
		collisionFlags = source.collisionFlags;
		push = source.push;
		startSpell = source.startSpell;
		stopSpell = source.stopSpell;
		replaceAnimations = source.replaceAnimations;
		radiusFixObstacle = source.radiusFixObstacle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FlyApplicator source = _source as FlyApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FlyApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FlyApplicator newParent = rawParent == null ? null : rawParent.Get<FlyApplicator>();
		if ( newParent == null && _newParent is FlyApplicator )
			newParent = _newParent as FlyApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_flightHeight.SetParent( newParent == null ? null : newParent._flightHeight );
		_startTime.SetParent( newParent == null ? null : newParent._startTime );
		_stopTime.SetParent( newParent == null ? null : newParent._stopTime );
		_animatedStopTime.SetParent( newParent == null ? null : newParent._animatedStopTime );
		_collisionFlags.SetParent( newParent == null ? null : newParent._collisionFlags );
		_push.SetParent( newParent == null ? null : newParent._push );
		_startSpell.SetParent( newParent == null ? null : newParent._startSpell );
		_stopSpell.SetParent( newParent == null ? null : newParent._stopSpell );
		_replaceAnimations.SetParent( newParent == null ? null : newParent._replaceAnimations );
		_radiusFixObstacle.SetParent( newParent == null ? null : newParent._radiusFixObstacle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_flightHeight.Reset();
		_startTime.Reset();
		_stopTime.Reset();
		_animatedStopTime.Reset();
		_collisionFlags.Reset();
		_push.Reset();
		_startSpell.Reset();
		_stopSpell.Reset();
		_replaceAnimations.Reset();
		_radiusFixObstacle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_flightHeight.IsDerivedFromParent()
			&& _startTime.IsDerivedFromParent()
			&& _stopTime.IsDerivedFromParent()
			&& _animatedStopTime.IsDerivedFromParent()
			&& _collisionFlags.IsDerivedFromParent()
			&& _push.IsDerivedFromParent()
			&& _startSpell.IsDerivedFromParent()
			&& _stopSpell.IsDerivedFromParent()
			&& _replaceAnimations.IsDerivedFromParent()
			&& _radiusFixObstacle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "flightHeight" )
			_flightHeight.Reset();
		else if ( fieldName == "startTime" )
			_startTime.Reset();
		else if ( fieldName == "stopTime" )
			_stopTime.Reset();
		else if ( fieldName == "animatedStopTime" )
			_animatedStopTime.Reset();
		else if ( fieldName == "collisionFlags" )
			_collisionFlags.Reset();
		else if ( fieldName == "push" )
			_push.Reset();
		else if ( fieldName == "startSpell" )
			_startSpell.Reset();
		else if ( fieldName == "stopSpell" )
			_stopSpell.Reset();
		else if ( fieldName == "replaceAnimations" )
			_replaceAnimations.Reset();
		else if ( fieldName == "radiusFixObstacle" )
			_radiusFixObstacle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "flightHeight" )
			return _flightHeight.IsDerivedFromParent();
		if ( fieldName == "startTime" )
			return _startTime.IsDerivedFromParent();
		if ( fieldName == "stopTime" )
			return _stopTime.IsDerivedFromParent();
		if ( fieldName == "animatedStopTime" )
			return _animatedStopTime.IsDerivedFromParent();
		if ( fieldName == "collisionFlags" )
			return _collisionFlags.IsDerivedFromParent();
		if ( fieldName == "push" )
			return _push.IsDerivedFromParent();
		if ( fieldName == "startSpell" )
			return _startSpell.IsDerivedFromParent();
		if ( fieldName == "stopSpell" )
			return _stopSpell.IsDerivedFromParent();
		if ( fieldName == "replaceAnimations" )
			return _replaceAnimations.IsDerivedFromParent();
		if ( fieldName == "radiusFixObstacle" )
			return _radiusFixObstacle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplForAllTargets", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0B76BC40)]
[UseTypeName("APLR")]
public class ForAllTargetsApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ForAllTargetsApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ForAllTargetsApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targets;
	private UndoRedoDBPtr<ProgramApplicator> _program;
	private UndoRedo<EParentNotificationFlags> _continueEvents;
	private UndoRedo<EParentNotificationFlags> _stopEvents;
	private UndoRedo<bool> _skipTargetIfInvalid;

	[Description( "Таргет селектор, для выбора целей" )]
	public DBPtr<MultipleTargetSelector> targets { get { return _targets.Get(); } set { _targets.Set( value ); } }

	[Description( "Программа, которая применяется к каждой цели" )]
	public DBPtr<ProgramApplicator> program { get { return _program.Get(); } set { _program.Set( value ); } }

	[Description( "Когда наложить программу на следующую цель" )]
	public EParentNotificationFlags continueEvents { get { return _continueEvents.Get(); } set { _continueEvents.Set( value ); } }

	[Description( "Когда прервать аппликатор" )]
	public EParentNotificationFlags stopEvents { get { return _stopEvents.Get(); } set { _stopEvents.Set( value ); } }

	[Description( "Если во время действия апликатора над многими целями следующая цель стала не валидной, то пропустить ее" )]
	public bool skipTargetIfInvalid { get { return _skipTargetIfInvalid.Get(); } set { _skipTargetIfInvalid.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ForAllTargetsApplicator>(owner);
		_targets = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		_program = new UndoRedoDBPtr<ProgramApplicator>( owner );
		_continueEvents = new UndoRedo<EParentNotificationFlags>( owner, EParentNotificationFlags.Zero );
		_stopEvents = new UndoRedo<EParentNotificationFlags>( owner, EParentNotificationFlags.Zero );
		_skipTargetIfInvalid = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_targets.Changed += FireChangedEvent;
		_program.Changed += FireChangedEvent;
		_continueEvents.Changed += FireChangedEvent;
		_stopEvents.Changed += FireChangedEvent;
		_skipTargetIfInvalid.Changed += FireChangedEvent;
	}

	public ForAllTargetsApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ForAllTargetsApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ForAllTargetsApplicator" );
		targets = source.targets;
		program = source.program;
		continueEvents = source.continueEvents;
		stopEvents = source.stopEvents;
		skipTargetIfInvalid = source.skipTargetIfInvalid;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ForAllTargetsApplicator source = _source as ForAllTargetsApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ForAllTargetsApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ForAllTargetsApplicator newParent = rawParent == null ? null : rawParent.Get<ForAllTargetsApplicator>();
		if ( newParent == null && _newParent is ForAllTargetsApplicator )
			newParent = _newParent as ForAllTargetsApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targets.SetParent( newParent == null ? null : newParent._targets );
		_program.SetParent( newParent == null ? null : newParent._program );
		_continueEvents.SetParent( newParent == null ? null : newParent._continueEvents );
		_stopEvents.SetParent( newParent == null ? null : newParent._stopEvents );
		_skipTargetIfInvalid.SetParent( newParent == null ? null : newParent._skipTargetIfInvalid );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targets.Reset();
		_program.Reset();
		_continueEvents.Reset();
		_stopEvents.Reset();
		_skipTargetIfInvalid.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targets.IsDerivedFromParent()
			&& _program.IsDerivedFromParent()
			&& _continueEvents.IsDerivedFromParent()
			&& _stopEvents.IsDerivedFromParent()
			&& _skipTargetIfInvalid.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targets" )
			_targets.Reset();
		else if ( fieldName == "program" )
			_program.Reset();
		else if ( fieldName == "continueEvents" )
			_continueEvents.Reset();
		else if ( fieldName == "stopEvents" )
			_stopEvents.Reset();
		else if ( fieldName == "skipTargetIfInvalid" )
			_skipTargetIfInvalid.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targets" )
			return _targets.IsDerivedFromParent();
		if ( fieldName == "program" )
			return _program.IsDerivedFromParent();
		if ( fieldName == "continueEvents" )
			return _continueEvents.IsDerivedFromParent();
		if ( fieldName == "stopEvents" )
			return _stopEvents.IsDerivedFromParent();
		if ( fieldName == "skipTargetIfInvalid" )
			return _skipTargetIfInvalid.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFFountainTargetSelector", "PFTargetSelector.h")]
[TypeId(0x0B720B42)]
[UseTypeName("TGSL")]
public class FountainTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<FountainTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<FountainTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FountainTargetSelector>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public FountainTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( FountainTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FountainTargetSelector" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FountainTargetSelector source = _source as FountainTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FountainTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FountainTargetSelector newParent = rawParent == null ? null : rawParent.Get<FountainTargetSelector>();
		if ( newParent == null && _newParent is FountainTargetSelector )
			newParent = _newParent as FountainTargetSelector;
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

[FactoryImpl("Create", "NWorld::PFApplFX", "PFApplFx.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE7A6C480)]
[UseTypeName("APLR")]
public class FXApplicator : BuffApplicator
{
	private UndoRedoDBPtr<FXApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<FXApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SingleTargetSelector> _auxillaryTarget;
	private UndoRedo<EFXFlags> _flags;

	[Description( "Дополнительная цель для эффекта. Например начало молнии." )]
	public DBPtr<SingleTargetSelector> auxillaryTarget { get { return _auxillaryTarget.Get(); } set { _auxillaryTarget.Set( value ); } }

	public EFXFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FXApplicator>(owner);
		_auxillaryTarget = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_flags = new UndoRedo<EFXFlags>( owner, (EFXFlags)0 );
		___parent.Changed += FireChangedEvent;
		_auxillaryTarget.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
	}

	public FXApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( FXApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FXApplicator" );
		auxillaryTarget = source.auxillaryTarget;
		flags = source.flags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FXApplicator source = _source as FXApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FXApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FXApplicator newParent = rawParent == null ? null : rawParent.Get<FXApplicator>();
		if ( newParent == null && _newParent is FXApplicator )
			newParent = _newParent as FXApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_auxillaryTarget.SetParent( newParent == null ? null : newParent._auxillaryTarget );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_auxillaryTarget.Reset();
		_flags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_auxillaryTarget.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "auxillaryTarget" )
			_auxillaryTarget.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "auxillaryTarget" )
			return _auxillaryTarget.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplGhostMove", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0B74F480)]
[UseTypeName("APLR")]
public class GhostMoveApplicator : BuffApplicator
{
	private UndoRedoDBPtr<GhostMoveApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<GhostMoveApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EGhostMoveMode> _collisionFlags;
	private UndoRedo<bool> _pushUnits;

	[Category( "Mode" )]
	[Description( "Dynamic - collide with moving units, Buildings - collide with buildings, Static - collide with static objects" )]
	public EGhostMoveMode collisionFlags { get { return _collisionFlags.Get(); } set { _collisionFlags.Set( value ); } }

	[Description( "When true, this applicator will free place for unit by pushing other units away - after stopping applicator." )]
	public bool pushUnits { get { return _pushUnits.Get(); } set { _pushUnits.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GhostMoveApplicator>(owner);
		_collisionFlags = new UndoRedo<EGhostMoveMode>( owner, (EGhostMoveMode)0 );
		_pushUnits = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_collisionFlags.Changed += FireChangedEvent;
		_pushUnits.Changed += FireChangedEvent;
	}

	public GhostMoveApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( GhostMoveApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GhostMoveApplicator" );
		collisionFlags = source.collisionFlags;
		pushUnits = source.pushUnits;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GhostMoveApplicator source = _source as GhostMoveApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GhostMoveApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GhostMoveApplicator newParent = rawParent == null ? null : rawParent.Get<GhostMoveApplicator>();
		if ( newParent == null && _newParent is GhostMoveApplicator )
			newParent = _newParent as GhostMoveApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_collisionFlags.SetParent( newParent == null ? null : newParent._collisionFlags );
		_pushUnits.SetParent( newParent == null ? null : newParent._pushUnits );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_collisionFlags.Reset();
		_pushUnits.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_collisionFlags.IsDerivedFromParent()
			&& _pushUnits.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "collisionFlags" )
			_collisionFlags.Reset();
		else if ( fieldName == "pushUnits" )
			_pushUnits.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "collisionFlags" )
			return _collisionFlags.IsDerivedFromParent();
		if ( fieldName == "pushUnits" )
			return _pushUnits.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplGiveConsumable", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE79B9C00)]
[UseTypeName("APLR")]
public class GiveConsumable : BaseApplicator
{
	private UndoRedoDBPtr<GiveConsumable> ___parent;
	[HideInOutliner]
	public new DBPtr<GiveConsumable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Consumable> _consumable;
	private ExecutableIntString _amount;

	public DBPtr<Consumable> consumable { get { return _consumable.Get(); } set { _consumable.Set( value ); } }

	public ExecutableIntString amount { get { return _amount; } set { _amount.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GiveConsumable>(owner);
		_consumable = new UndoRedoDBPtr<Consumable>( owner );
		ExecutableIntString __amount = new ExecutableIntString(); // Construct default object for amount
		__amount.sString = "1";
		_amount = new ExecutableIntString( owner, __amount );
		___parent.Changed += FireChangedEvent;
		_consumable.Changed += FireChangedEvent;
		_amount.Changed += FireChangedEvent;
	}

	public GiveConsumable()
	{
		Initialize( this );
	}
	private void AssignSelf( GiveConsumable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GiveConsumable" );
		consumable = source.consumable;
		amount = source.amount;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GiveConsumable source = _source as GiveConsumable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GiveConsumable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GiveConsumable newParent = rawParent == null ? null : rawParent.Get<GiveConsumable>();
		if ( newParent == null && _newParent is GiveConsumable )
			newParent = _newParent as GiveConsumable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_consumable.SetParent( newParent == null ? null : newParent._consumable );
		_amount.SetParent( newParent == null ? null : newParent._amount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_consumable.Reset();
		_amount.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_consumable.IsDerivedFromParent()
			&& _amount.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "consumable" )
			_consumable.Reset();
		else if ( fieldName == "amount" )
			_amount.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "consumable" )
			return _consumable.IsDerivedFromParent();
		if ( fieldName == "amount" )
			return _amount.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplHeal", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xA0617B80)]
[UseTypeName("APLR")]
public class HealApplicator : BaseApplicator
{
	private UndoRedoDBPtr<HealApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<HealApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _amount;
	private UndoRedo<EHealTarget> _healTarget;
	private UndoRedoDBPtr<UIEvent> _uiEvent;
	private UndoRedo<bool> _ignoreHealingMods;

	[Description( "Amount to be added" )]
	public ExecutableFloatString amount { get { return _amount; } set { _amount.Assign( value ); } }

	[Description( "Health - add amount to health; Energy - add amount to energy" )]
	public EHealTarget healTarget { get { return _healTarget.Get(); } set { _healTarget.Set( value ); } }

	[Description( "UI Event" )]
	public DBPtr<UIEvent> uiEvent { get { return _uiEvent.Get(); } set { _uiEvent.Set( value ); } }

	[Description( "Не применять модификаторы при хиле юнита, отличного от кастера" )]
	public bool ignoreHealingMods { get { return _ignoreHealingMods.Get(); } set { _ignoreHealingMods.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HealApplicator>(owner);
		ExecutableFloatString __amount = new ExecutableFloatString(); // Construct default object for amount
		__amount.sString = "0.0";
		_amount = new ExecutableFloatString( owner, __amount );
		_healTarget = new UndoRedo<EHealTarget>( owner, EHealTarget.Health );
		_uiEvent = new UndoRedoDBPtr<UIEvent>( owner );
		_ignoreHealingMods = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_amount.Changed += FireChangedEvent;
		_healTarget.Changed += FireChangedEvent;
		_uiEvent.Changed += FireChangedEvent;
		_ignoreHealingMods.Changed += FireChangedEvent;
	}

	public HealApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( HealApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HealApplicator" );
		amount = source.amount;
		healTarget = source.healTarget;
		uiEvent = source.uiEvent;
		ignoreHealingMods = source.ignoreHealingMods;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HealApplicator source = _source as HealApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HealApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HealApplicator newParent = rawParent == null ? null : rawParent.Get<HealApplicator>();
		if ( newParent == null && _newParent is HealApplicator )
			newParent = _newParent as HealApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_amount.SetParent( newParent == null ? null : newParent._amount );
		_healTarget.SetParent( newParent == null ? null : newParent._healTarget );
		_uiEvent.SetParent( newParent == null ? null : newParent._uiEvent );
		_ignoreHealingMods.SetParent( newParent == null ? null : newParent._ignoreHealingMods );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_amount.Reset();
		_healTarget.Reset();
		_uiEvent.Reset();
		_ignoreHealingMods.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_amount.IsDerivedFromParent()
			&& _healTarget.IsDerivedFromParent()
			&& _uiEvent.IsDerivedFromParent()
			&& _ignoreHealingMods.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "amount" )
			_amount.Reset();
		else if ( fieldName == "healTarget" )
			_healTarget.Reset();
		else if ( fieldName == "uiEvent" )
			_uiEvent.Reset();
		else if ( fieldName == "ignoreHealingMods" )
			_ignoreHealingMods.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "amount" )
			return _amount.IsDerivedFromParent();
		if ( fieldName == "healTarget" )
			return _healTarget.IsDerivedFromParent();
		if ( fieldName == "uiEvent" )
			return _uiEvent.IsDerivedFromParent();
		if ( fieldName == "ignoreHealingMods" )
			return _ignoreHealingMods.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFHeroEnumerator", "PFTargetSelector.h")]
[TypeId(0x9E67AB00)]
[UseTypeName("TGSL")]
public class HeroEnumerator : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<HeroEnumerator> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroEnumerator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroEnumerator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public HeroEnumerator()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroEnumerator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroEnumerator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroEnumerator source = _source as HeroEnumerator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroEnumerator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroEnumerator newParent = rawParent == null ? null : rawParent.Get<HeroEnumerator>();
		if ( newParent == null && _newParent is HeroEnumerator )
			newParent = _newParent as HeroEnumerator;
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

[FactoryImpl("Create", "NWorld::PFHighlanderA1TargetSelector", "PFHighlander.h")]
[TypeId(0x0B76C240)]
[UseTypeName("TGSL")]
public class HighlanderA1TargetSelector : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<HighlanderA1TargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlanderA1TargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _range;
	private ExecutableFloatString _targetCount;

	[Description( "Радиус для поиска целей" )]
	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	[Description( "Количество целей, которых должен атаковать горец. Может зависеть от ранга абилки." )]
	public ExecutableFloatString targetCount { get { return _targetCount; } set { _targetCount.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlanderA1TargetSelector>(owner);
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		ExecutableFloatString __targetCount = new ExecutableFloatString(); // Construct default object for targetCount
		__targetCount.sString = "1.0f";
		_targetCount = new ExecutableFloatString( owner, __targetCount );
		___parent.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_targetCount.Changed += FireChangedEvent;
	}

	public HighlanderA1TargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlanderA1TargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlanderA1TargetSelector" );
		range = source.range;
		targetCount = source.targetCount;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlanderA1TargetSelector source = _source as HighlanderA1TargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlanderA1TargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlanderA1TargetSelector newParent = rawParent == null ? null : rawParent.Get<HighlanderA1TargetSelector>();
		if ( newParent == null && _newParent is HighlanderA1TargetSelector )
			newParent = _newParent as HighlanderA1TargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_range.SetParent( newParent == null ? null : newParent._range );
		_targetCount.SetParent( newParent == null ? null : newParent._targetCount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_range.Reset();
		_targetCount.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_range.IsDerivedFromParent()
			&& _targetCount.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "targetCount" )
			_targetCount.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "targetCount" )
			return _targetCount.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplInvalidAbilityTarget", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x15C7A800)]
[UseTypeName("APLR")]
public class InvalidAbilityTargetApplicator : BuffApplicator
{
	private UndoRedoDBPtr<InvalidAbilityTargetApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<InvalidAbilityTargetApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<InvalidAbilityTargetApplicator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public InvalidAbilityTargetApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( InvalidAbilityTargetApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for InvalidAbilityTargetApplicator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		InvalidAbilityTargetApplicator source = _source as InvalidAbilityTargetApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for InvalidAbilityTargetApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		InvalidAbilityTargetApplicator newParent = rawParent == null ? null : rawParent.Get<InvalidAbilityTargetApplicator>();
		if ( newParent == null && _newParent is InvalidAbilityTargetApplicator )
			newParent = _newParent as InvalidAbilityTargetApplicator;
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

[FactoryImpl("Create", "NWorld::PFApplInvisibility", "PfApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0B724A40)]
[UseTypeName("APLR")]
public class InvisibilityApplicator : BuffApplicator
{
	private UndoRedoDBPtr<InvisibilityApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<InvisibilityApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _fadeIn;
	private UndoRedoDBPtr<Spell> _onBecomeInvisible;
	private UndoRedo<bool> _ignoreCancel;

	[Description( "Время ухода в невидимость" )]
	public ExecutableFloatString fadeIn { get { return _fadeIn; } set { _fadeIn.Assign( value ); } }

	[Description( "Заклинание, которое будет закастовано в момент, когда юнит становится невидимым." )]
	public DBPtr<Spell> onBecomeInvisible { get { return _onBecomeInvisible.Get(); } set { _onBecomeInvisible.Set( value ); } }

	[Description( "Игнорировать событие отмены невидимости" )]
	public bool ignoreCancel { get { return _ignoreCancel.Get(); } set { _ignoreCancel.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<InvisibilityApplicator>(owner);
		ExecutableFloatString __fadeIn = new ExecutableFloatString(); // Construct default object for fadeIn
		__fadeIn.sString = "0.0";
		_fadeIn = new ExecutableFloatString( owner, __fadeIn );
		_onBecomeInvisible = new UndoRedoDBPtr<Spell>( owner );
		_ignoreCancel = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_fadeIn.Changed += FireChangedEvent;
		_onBecomeInvisible.Changed += FireChangedEvent;
		_ignoreCancel.Changed += FireChangedEvent;
	}

	public InvisibilityApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( InvisibilityApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for InvisibilityApplicator" );
		fadeIn = source.fadeIn;
		onBecomeInvisible = source.onBecomeInvisible;
		ignoreCancel = source.ignoreCancel;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		InvisibilityApplicator source = _source as InvisibilityApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for InvisibilityApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		InvisibilityApplicator newParent = rawParent == null ? null : rawParent.Get<InvisibilityApplicator>();
		if ( newParent == null && _newParent is InvisibilityApplicator )
			newParent = _newParent as InvisibilityApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fadeIn.SetParent( newParent == null ? null : newParent._fadeIn );
		_onBecomeInvisible.SetParent( newParent == null ? null : newParent._onBecomeInvisible );
		_ignoreCancel.SetParent( newParent == null ? null : newParent._ignoreCancel );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fadeIn.Reset();
		_onBecomeInvisible.Reset();
		_ignoreCancel.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fadeIn.IsDerivedFromParent()
			&& _onBecomeInvisible.IsDerivedFromParent()
			&& _ignoreCancel.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fadeIn" )
			_fadeIn.Reset();
		else if ( fieldName == "onBecomeInvisible" )
			_onBecomeInvisible.Reset();
		else if ( fieldName == "ignoreCancel" )
			_ignoreCancel.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fadeIn" )
			return _fadeIn.IsDerivedFromParent();
		if ( fieldName == "onBecomeInvisible" )
			return _onBecomeInvisible.IsDerivedFromParent();
		if ( fieldName == "ignoreCancel" )
			return _ignoreCancel.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplKickAway", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B0B)]
[UseTypeName("APLR")]
public class KickAwayApplicator : BaseApplicator
{
	private UndoRedoDBPtr<KickAwayApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<KickAwayApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _distance;

	[Category( "KickAway" )]
	public float distance { get { return _distance.Get(); } set { _distance.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<KickAwayApplicator>(owner);
		_distance = new UndoRedo<float>( owner, 10.0f );
		___parent.Changed += FireChangedEvent;
		_distance.Changed += FireChangedEvent;
	}

	public KickAwayApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( KickAwayApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for KickAwayApplicator" );
		distance = source.distance;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		KickAwayApplicator source = _source as KickAwayApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for KickAwayApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		KickAwayApplicator newParent = rawParent == null ? null : rawParent.Get<KickAwayApplicator>();
		if ( newParent == null && _newParent is KickAwayApplicator )
			newParent = _newParent as KickAwayApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_distance.SetParent( newParent == null ? null : newParent._distance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_distance.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_distance.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "distance" )
			_distance.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "distance" )
			return _distance.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFApplKill", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E678B02)]
[UseTypeName("APLR")]
public class KillApplicator : BaseApplicator
{
	private UndoRedoDBPtr<KillApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<KillApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EKillMode> _flag;
	private UndoRedo<bool> _dontGiveRewards;

	[Description( "Kill flag: Don't show death animation, Instant remove on death" )]
	public EKillMode flag { get { return _flag.Get(); } set { _flag.Set( value ); } }

	[Description( "Do not reward killer" )]
	public bool dontGiveRewards { get { return _dontGiveRewards.Get(); } set { _dontGiveRewards.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<KillApplicator>(owner);
		_flag = new UndoRedo<EKillMode>( owner, EKillMode.None );
		_dontGiveRewards = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_flag.Changed += FireChangedEvent;
		_dontGiveRewards.Changed += FireChangedEvent;
	}

	public KillApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( KillApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for KillApplicator" );
		flag = source.flag;
		dontGiveRewards = source.dontGiveRewards;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		KillApplicator source = _source as KillApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for KillApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		KillApplicator newParent = rawParent == null ? null : rawParent.Get<KillApplicator>();
		if ( newParent == null && _newParent is KillApplicator )
			newParent = _newParent as KillApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_flag.SetParent( newParent == null ? null : newParent._flag );
		_dontGiveRewards.SetParent( newParent == null ? null : newParent._dontGiveRewards );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_flag.Reset();
		_dontGiveRewards.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_flag.IsDerivedFromParent()
			&& _dontGiveRewards.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "flag" )
			_flag.Reset();
		else if ( fieldName == "dontGiveRewards" )
			_dontGiveRewards.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "flag" )
			return _flag.IsDerivedFromParent();
		if ( fieldName == "dontGiveRewards" )
			return _dontGiveRewards.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFListOfTargetSelectors", "PFTargetSelector.h")]
[TypeId(0x0F738B01)]
[UseTypeName("TGSL")]
public class ListOfTargetSelectors : MultipleTargetSelector
{
	private UndoRedoDBPtr<ListOfTargetSelectors> ___parent;
	[HideInOutliner]
	public new DBPtr<ListOfTargetSelectors> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<TargetSelector>> _targetSelectors;

	public libdb.IChangeableList<DBPtr<TargetSelector>> targetSelectors { get { return _targetSelectors; } set { _targetSelectors.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ListOfTargetSelectors>(owner);
		_targetSelectors = new UndoRedoAssignableList<DBPtr<TargetSelector>>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelectors.Changed += FireChangedEvent;
	}

	public ListOfTargetSelectors()
	{
		Initialize( this );
	}
	private void AssignSelf( ListOfTargetSelectors source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ListOfTargetSelectors" );
		targetSelectors = source.targetSelectors;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ListOfTargetSelectors source = _source as ListOfTargetSelectors;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ListOfTargetSelectors" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ListOfTargetSelectors newParent = rawParent == null ? null : rawParent.Get<ListOfTargetSelectors>();
		if ( newParent == null && _newParent is ListOfTargetSelectors )
			newParent = _newParent as ListOfTargetSelectors;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelectors.SetParent( newParent == null ? null : newParent._targetSelectors );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelectors.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelectors.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelectors" )
			_targetSelectors.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelectors" )
			return _targetSelectors.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplLockTiles", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xA0757340)]
[UseTypeName("APLR")]
public class LockTilesApplicator : BuffApplicator
{
	private UndoRedoDBPtr<LockTilesApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<LockTilesApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ObjectLockMask _lockMask;
	private FloatRect _collision;
	private UndoRedo<bool> _pushCaster;

	[Description( "Mask to lock tile map" )]
	public ObjectLockMask lockMask { get { return _lockMask; } set { _lockMask.Assign( value ); } }

	[Description( "Relative 2D object bounds to lock map" )]
	public FloatRect collision { get { return _collision; } set { _collision.Assign( value ); } }

	[Description( "Push applicator sender out of locked tiles" )]
	public bool pushCaster { get { return _pushCaster.Get(); } set { _pushCaster.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LockTilesApplicator>(owner);
		_lockMask = new ObjectLockMask( owner );
		_collision = new FloatRect( owner );
		_pushCaster = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_lockMask.Changed += FireChangedEvent;
		_collision.Changed += FireChangedEvent;
		_pushCaster.Changed += FireChangedEvent;
	}

	public LockTilesApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( LockTilesApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LockTilesApplicator" );
		lockMask = source.lockMask;
		collision = source.collision;
		pushCaster = source.pushCaster;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LockTilesApplicator source = _source as LockTilesApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LockTilesApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LockTilesApplicator newParent = rawParent == null ? null : rawParent.Get<LockTilesApplicator>();
		if ( newParent == null && _newParent is LockTilesApplicator )
			newParent = _newParent as LockTilesApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_lockMask.SetParent( newParent == null ? null : newParent._lockMask );
		_collision.SetParent( newParent == null ? null : newParent._collision );
		_pushCaster.SetParent( newParent == null ? null : newParent._pushCaster );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_lockMask.Reset();
		_collision.Reset();
		_pushCaster.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_lockMask.IsDerivedFromParent()
			&& _collision.IsDerivedFromParent()
			&& _pushCaster.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "lockMask" )
			_lockMask.Reset();
		else if ( fieldName == "collision" )
			_collision.Reset();
		else if ( fieldName == "pushCaster" )
			_pushCaster.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "lockMask" )
			return _lockMask.IsDerivedFromParent();
		if ( fieldName == "collision" )
			return _collision.IsDerivedFromParent();
		if ( fieldName == "pushCaster" )
			return _pushCaster.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFMainBuildingTargetSelector", "PFTargetSelector.h")]
[TypeId(0x0B720B41)]
[UseTypeName("TGSL")]
public class MainBuildingTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<MainBuildingTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<MainBuildingTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MainBuildingTargetSelector>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public MainBuildingTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( MainBuildingTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MainBuildingTargetSelector" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MainBuildingTargetSelector source = _source as MainBuildingTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MainBuildingTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MainBuildingTargetSelector newParent = rawParent == null ? null : rawParent.Get<MainBuildingTargetSelector>();
		if ( newParent == null && _newParent is MainBuildingTargetSelector )
			newParent = _newParent as MainBuildingTargetSelector;
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

[FactoryImpl("Create", "NWorld::PFApplMarker", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE778BC81)]
[UseTypeName("APLR")]
public class MarkerApplicator : BuffApplicator
{
	private UndoRedoDBPtr<MarkerApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<MarkerApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _addValue;
	private ExecutableFloatString _multValue;

	[Description( "Прибавка к текущему значению" )]
	public ExecutableFloatString addValue { get { return _addValue; } set { _addValue.Assign( value ); } }

	[Description( "Множитель текущего значения" )]
	public ExecutableFloatString multValue { get { return _multValue; } set { _multValue.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MarkerApplicator>(owner);
		ExecutableFloatString __addValue = new ExecutableFloatString(); // Construct default object for addValue
		__addValue.sString = "1.0";
		_addValue = new ExecutableFloatString( owner, __addValue );
		ExecutableFloatString __multValue = new ExecutableFloatString(); // Construct default object for multValue
		__multValue.sString = "1.0";
		_multValue = new ExecutableFloatString( owner, __multValue );
		___parent.Changed += FireChangedEvent;
		_addValue.Changed += FireChangedEvent;
		_multValue.Changed += FireChangedEvent;
	}

	public MarkerApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( MarkerApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MarkerApplicator" );
		addValue = source.addValue;
		multValue = source.multValue;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MarkerApplicator source = _source as MarkerApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MarkerApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MarkerApplicator newParent = rawParent == null ? null : rawParent.Get<MarkerApplicator>();
		if ( newParent == null && _newParent is MarkerApplicator )
			newParent = _newParent as MarkerApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_addValue.SetParent( newParent == null ? null : newParent._addValue );
		_multValue.SetParent( newParent == null ? null : newParent._multValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_addValue.Reset();
		_multValue.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_addValue.IsDerivedFromParent()
			&& _multValue.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "addValue" )
			_addValue.Reset();
		else if ( fieldName == "multValue" )
			_multValue.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "addValue" )
			return _addValue.IsDerivedFromParent();
		if ( fieldName == "multValue" )
			return _multValue.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFMaximizingTargetSelector", "PFAITargetSelectors.h")]
[TypeId(0x9A9C5C40)]
[UseTypeName("TGSL")]
public class MaximizingTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<MaximizingTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<MaximizingTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;
	private ExecutableFloatString _range;
	private ExecutableFloatString _searchRange;
	private UndoRedo<ESpellTarget> _searchFilter;
	private ExecutableIntString _minTargetsNumber;

	[Description( "Селектор, у которого максимизируем количество целей (по CurrentPosition)" )]
	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Радиус, на котором ищем цель" )]
	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	[Description( "Поиск целей включится, только если в этом радиусе есть хотя бы одна цель c флагами из searchFilter" )]
	public ExecutableFloatString searchRange { get { return _searchRange; } set { _searchRange.Assign( value ); } }

	[Description( "Flags that specify targets of this spell. Specify 0 if you want to apply this spell on sender." )]
	public ESpellTarget searchFilter { get { return _searchFilter.Get(); } set { _searchFilter.Set( value ); } }

	[Description( "Если число целей меньше - не выбирать ни одной" )]
	public ExecutableIntString minTargetsNumber { get { return _minTargetsNumber; } set { _minTargetsNumber.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MaximizingTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		ExecutableFloatString __searchRange = new ExecutableFloatString(); // Construct default object for searchRange
		__searchRange.sString = "0.0f";
		_searchRange = new ExecutableFloatString( owner, __searchRange );
		_searchFilter = new UndoRedo<ESpellTarget>( owner, ESpellTarget.AllEnemies | ESpellTarget.VisibleTargetsOnly );
		_minTargetsNumber = new ExecutableIntString( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_searchRange.Changed += FireChangedEvent;
		_searchFilter.Changed += FireChangedEvent;
		_minTargetsNumber.Changed += FireChangedEvent;
	}

	public MaximizingTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( MaximizingTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MaximizingTargetSelector" );
		targetSelector = source.targetSelector;
		range = source.range;
		searchRange = source.searchRange;
		searchFilter = source.searchFilter;
		minTargetsNumber = source.minTargetsNumber;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MaximizingTargetSelector source = _source as MaximizingTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MaximizingTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MaximizingTargetSelector newParent = rawParent == null ? null : rawParent.Get<MaximizingTargetSelector>();
		if ( newParent == null && _newParent is MaximizingTargetSelector )
			newParent = _newParent as MaximizingTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_range.SetParent( newParent == null ? null : newParent._range );
		_searchRange.SetParent( newParent == null ? null : newParent._searchRange );
		_searchFilter.SetParent( newParent == null ? null : newParent._searchFilter );
		_minTargetsNumber.SetParent( newParent == null ? null : newParent._minTargetsNumber );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_range.Reset();
		_searchRange.Reset();
		_searchFilter.Reset();
		_minTargetsNumber.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& _searchRange.IsDerivedFromParent()
			&& _searchFilter.IsDerivedFromParent()
			&& _minTargetsNumber.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "searchRange" )
			_searchRange.Reset();
		else if ( fieldName == "searchFilter" )
			_searchFilter.Reset();
		else if ( fieldName == "minTargetsNumber" )
			_minTargetsNumber.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "searchRange" )
			return _searchRange.IsDerivedFromParent();
		if ( fieldName == "searchFilter" )
			return _searchFilter.IsDerivedFromParent();
		if ( fieldName == "minTargetsNumber" )
			return _minTargetsNumber.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFBasicMicroAI", "PFMicroAI.h", CreateFunction = "NWorld::CreateMicroAI<>")]
[UseTypeName("MCAI")]
public class BasicMicroAI : MicroAI
{
	private UndoRedoDBPtr<BasicMicroAI> ___parent;
	[HideInOutliner]
	public new DBPtr<BasicMicroAI> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableBoolString _condition;
	private UndoRedo<bool> _castWhenIdle;

	[Description( "Формула для активации абилки; true = активировать" )]
	public ExecutableBoolString condition { get { return _condition; } set { _condition.Assign( value ); } }

	[Description( "Кастовать только если юнит ничего не делает" )]
	public bool castWhenIdle { get { return _castWhenIdle.Get(); } set { _castWhenIdle.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BasicMicroAI>(owner);
		_condition = new ExecutableBoolString( owner );
		_castWhenIdle = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_condition.Changed += FireChangedEvent;
		_castWhenIdle.Changed += FireChangedEvent;
	}

	public BasicMicroAI()
	{
		Initialize( this );
	}
	private void AssignSelf( BasicMicroAI source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BasicMicroAI" );
		condition = source.condition;
		castWhenIdle = source.castWhenIdle;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BasicMicroAI source = _source as BasicMicroAI;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BasicMicroAI" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BasicMicroAI newParent = rawParent == null ? null : rawParent.Get<BasicMicroAI>();
		if ( newParent == null && _newParent is BasicMicroAI )
			newParent = _newParent as BasicMicroAI;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_condition.SetParent( newParent == null ? null : newParent._condition );
		_castWhenIdle.SetParent( newParent == null ? null : newParent._castWhenIdle );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_condition.Reset();
		_castWhenIdle.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_condition.IsDerivedFromParent()
			&& _castWhenIdle.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "condition" )
			_condition.Reset();
		else if ( fieldName == "castWhenIdle" )
			_castWhenIdle.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
		if ( fieldName == "castWhenIdle" )
			return _castWhenIdle.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Create", "NWorld::PFApplModifyTerrain", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0E676B42)]
[UseTypeName("APLR")]
public class ModifyTerrainApplicator : BaseApplicator
{
	private UndoRedoDBPtr<ModifyTerrainApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ModifyTerrainApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _durationTime;
	private ExecutableIntString _faction;
	private ExecutableFloatString _modifRadius;

	[Description( "Time of modification" )]
	public ExecutableFloatString durationTime { get { return _durationTime; } set { _durationTime.Assign( value ); } }

	[Description( "Faction" )]
	public ExecutableIntString faction { get { return _faction; } set { _faction.Assign( value ); } }

	[Description( "Modification radius" )]
	public ExecutableFloatString modifRadius { get { return _modifRadius; } set { _modifRadius.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ModifyTerrainApplicator>(owner);
		ExecutableFloatString __durationTime = new ExecutableFloatString(); // Construct default object for durationTime
		__durationTime.sString = "5.0f";
		_durationTime = new ExecutableFloatString( owner, __durationTime );
		_faction = new ExecutableIntString( owner );
		ExecutableFloatString __modifRadius = new ExecutableFloatString(); // Construct default object for modifRadius
		__modifRadius.sString = "1.0f";
		_modifRadius = new ExecutableFloatString( owner, __modifRadius );
		___parent.Changed += FireChangedEvent;
		_durationTime.Changed += FireChangedEvent;
		_faction.Changed += FireChangedEvent;
		_modifRadius.Changed += FireChangedEvent;
	}

	public ModifyTerrainApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ModifyTerrainApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ModifyTerrainApplicator" );
		durationTime = source.durationTime;
		faction = source.faction;
		modifRadius = source.modifRadius;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ModifyTerrainApplicator source = _source as ModifyTerrainApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ModifyTerrainApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ModifyTerrainApplicator newParent = rawParent == null ? null : rawParent.Get<ModifyTerrainApplicator>();
		if ( newParent == null && _newParent is ModifyTerrainApplicator )
			newParent = _newParent as ModifyTerrainApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_durationTime.SetParent( newParent == null ? null : newParent._durationTime );
		_faction.SetParent( newParent == null ? null : newParent._faction );
		_modifRadius.SetParent( newParent == null ? null : newParent._modifRadius );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_durationTime.Reset();
		_faction.Reset();
		_modifRadius.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_durationTime.IsDerivedFromParent()
			&& _faction.IsDerivedFromParent()
			&& _modifRadius.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "durationTime" )
			_durationTime.Reset();
		else if ( fieldName == "faction" )
			_faction.Reset();
		else if ( fieldName == "modifRadius" )
			_modifRadius.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "durationTime" )
			return _durationTime.IsDerivedFromParent();
		if ( fieldName == "faction" )
			return _faction.IsDerivedFromParent();
		if ( fieldName == "modifRadius" )
			return _modifRadius.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplMount", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE7777B80)]
[UseTypeName("APLR")]
public class MountApplicator : BuffApplicator
{
	private UndoRedoDBPtr<MountApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<MountApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _mountTarget;
	private UndoRedo<bool> _controlMount;

	[Description( "Target to mount to" )]
	public EApplicatorApplyTarget mountTarget { get { return _mountTarget.Get(); } set { _mountTarget.Set( value ); } }

	[Description( "Hero can issue commands to his mount" )]
	public bool controlMount { get { return _controlMount.Get(); } set { _controlMount.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MountApplicator>(owner);
		_mountTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_controlMount = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_mountTarget.Changed += FireChangedEvent;
		_controlMount.Changed += FireChangedEvent;
	}

	public MountApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( MountApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MountApplicator" );
		mountTarget = source.mountTarget;
		controlMount = source.controlMount;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MountApplicator source = _source as MountApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MountApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MountApplicator newParent = rawParent == null ? null : rawParent.Get<MountApplicator>();
		if ( newParent == null && _newParent is MountApplicator )
			newParent = _newParent as MountApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_mountTarget.SetParent( newParent == null ? null : newParent._mountTarget );
		_controlMount.SetParent( newParent == null ? null : newParent._controlMount );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_mountTarget.Reset();
		_controlMount.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_mountTarget.IsDerivedFromParent()
			&& _controlMount.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "mountTarget" )
			_mountTarget.Reset();
		else if ( fieldName == "controlMount" )
			_controlMount.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "mountTarget" )
			return _mountTarget.IsDerivedFromParent();
		if ( fieldName == "controlMount" )
			return _controlMount.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplMovementControl", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2C67DB40)]
[UseTypeName("APLR")]
public class MovementControlApplicator : BuffApplicator
{
	private UndoRedoDBPtr<MovementControlApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<MovementControlApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MovementControlApplicator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public MovementControlApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( MovementControlApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MovementControlApplicator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MovementControlApplicator source = _source as MovementControlApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MovementControlApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MovementControlApplicator newParent = rawParent == null ? null : rawParent.Get<MovementControlApplicator>();
		if ( newParent == null && _newParent is MovementControlApplicator )
			newParent = _newParent as MovementControlApplicator;
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

[FactoryImpl("Create", "NWorld::PFApplMoveTo", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0E676B80)]
[UseTypeName("APLR")]
public class MoveToApplicator : BuffApplicator
{
	private UndoRedoDBPtr<MoveToApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<MoveToApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _moveRange;
	private ExecutableFloatString _moveSpeed;
	private UndoRedo<EApplicatorApplyTarget> _moveTarget;
	private Vec2 _offset;
	private ExecutableBoolString _isMoveDirect;
	private UndoRedo<bool> _pushUnits;
	private UndoRedo<bool> _justRotate;
	private UndoRedo<bool> _isNotStackable;

	[Description( "Destination we going to move." )]
	public ExecutableFloatString moveRange { get { return _moveRange; } set { _moveRange.Assign( value ); } }

	[Description( "(isMoveDirect mode only!) Movement speed in MPs" )]
	public ExecutableFloatString moveSpeed { get { return _moveSpeed; } set { _moveSpeed.Assign( value ); } }

	[Description( "Movement target" )]
	public EApplicatorApplyTarget moveTarget { get { return _moveTarget.Get(); } set { _moveTarget.Set( value ); } }

	[Description( "Offset off target (negative_Y is pointing towards target)" )]
	public Vec2 offset { get { return _offset; } set { _offset.Assign( value ); } }

	[Description( "Should we move trough obstacles?" )]
	public ExecutableBoolString isMoveDirect { get { return _isMoveDirect; } set { _isMoveDirect.Assign( value ); } }

	[Description( "(isMoveDirect mode only!) should free place for unit by pushing other units avay?" )]
	public bool pushUnits { get { return _pushUnits.Get(); } set { _pushUnits.Set( value ); } }

	[Description( "Don't move, just rotate to target" )]
	public bool justRotate { get { return _justRotate.Get(); } set { _justRotate.Set( value ); } }

	[Description( "Not stackable MoveTo applicator" )]
	public bool isNotStackable { get { return _isNotStackable.Get(); } set { _isNotStackable.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MoveToApplicator>(owner);
		ExecutableFloatString __moveRange = new ExecutableFloatString(); // Construct default object for moveRange
		__moveRange.sString = "1.0f";
		_moveRange = new ExecutableFloatString( owner, __moveRange );
		ExecutableFloatString __moveSpeed = new ExecutableFloatString(); // Construct default object for moveSpeed
		__moveSpeed.sString = "0.0f";
		_moveSpeed = new ExecutableFloatString( owner, __moveSpeed );
		_moveTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_offset = new Vec2( owner );
		ExecutableBoolString __isMoveDirect = new ExecutableBoolString(); // Construct default object for isMoveDirect
		__isMoveDirect.sString = "true";
		_isMoveDirect = new ExecutableBoolString( owner, __isMoveDirect );
		_pushUnits = new UndoRedo<bool>( owner, false );
		_justRotate = new UndoRedo<bool>( owner, false );
		_isNotStackable = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_moveRange.Changed += FireChangedEvent;
		_moveSpeed.Changed += FireChangedEvent;
		_moveTarget.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_isMoveDirect.Changed += FireChangedEvent;
		_pushUnits.Changed += FireChangedEvent;
		_justRotate.Changed += FireChangedEvent;
		_isNotStackable.Changed += FireChangedEvent;
	}

	public MoveToApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( MoveToApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MoveToApplicator" );
		moveRange = source.moveRange;
		moveSpeed = source.moveSpeed;
		moveTarget = source.moveTarget;
		offset = source.offset;
		isMoveDirect = source.isMoveDirect;
		pushUnits = source.pushUnits;
		justRotate = source.justRotate;
		isNotStackable = source.isNotStackable;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MoveToApplicator source = _source as MoveToApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MoveToApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MoveToApplicator newParent = rawParent == null ? null : rawParent.Get<MoveToApplicator>();
		if ( newParent == null && _newParent is MoveToApplicator )
			newParent = _newParent as MoveToApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_moveRange.SetParent( newParent == null ? null : newParent._moveRange );
		_moveSpeed.SetParent( newParent == null ? null : newParent._moveSpeed );
		_moveTarget.SetParent( newParent == null ? null : newParent._moveTarget );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_isMoveDirect.SetParent( newParent == null ? null : newParent._isMoveDirect );
		_pushUnits.SetParent( newParent == null ? null : newParent._pushUnits );
		_justRotate.SetParent( newParent == null ? null : newParent._justRotate );
		_isNotStackable.SetParent( newParent == null ? null : newParent._isNotStackable );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_moveRange.Reset();
		_moveSpeed.Reset();
		_moveTarget.Reset();
		_offset.Reset();
		_isMoveDirect.Reset();
		_pushUnits.Reset();
		_justRotate.Reset();
		_isNotStackable.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_moveRange.IsDerivedFromParent()
			&& _moveSpeed.IsDerivedFromParent()
			&& _moveTarget.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _isMoveDirect.IsDerivedFromParent()
			&& _pushUnits.IsDerivedFromParent()
			&& _justRotate.IsDerivedFromParent()
			&& _isNotStackable.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "moveRange" )
			_moveRange.Reset();
		else if ( fieldName == "moveSpeed" )
			_moveSpeed.Reset();
		else if ( fieldName == "moveTarget" )
			_moveTarget.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "isMoveDirect" )
			_isMoveDirect.Reset();
		else if ( fieldName == "pushUnits" )
			_pushUnits.Reset();
		else if ( fieldName == "justRotate" )
			_justRotate.Reset();
		else if ( fieldName == "isNotStackable" )
			_isNotStackable.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "moveRange" )
			return _moveRange.IsDerivedFromParent();
		if ( fieldName == "moveSpeed" )
			return _moveSpeed.IsDerivedFromParent();
		if ( fieldName == "moveTarget" )
			return _moveTarget.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "isMoveDirect" )
			return _isMoveDirect.IsDerivedFromParent();
		if ( fieldName == "pushUnits" )
			return _pushUnits.IsDerivedFromParent();
		if ( fieldName == "justRotate" )
			return _justRotate.IsDerivedFromParent();
		if ( fieldName == "isNotStackable" )
			return _isNotStackable.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplicatorRecipientsTargetSelector", "PFTargetSelector.h")]
[TypeId(0xE7832C00)]
[UseTypeName("TGSL")]
public class ApplicatorRecipientsTargetSelector : MultipleTargetSelector
{
	private UndoRedoDBPtr<ApplicatorRecipientsTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<ApplicatorRecipientsTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BaseApplicator> _applicator;

	[Description( "Аппликатор, получателей которого надо собрать" )]
	public DBPtr<BaseApplicator> applicator { get { return _applicator.Get(); } set { _applicator.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ApplicatorRecipientsTargetSelector>(owner);
		_applicator = new UndoRedoDBPtr<BaseApplicator>( owner );
		___parent.Changed += FireChangedEvent;
		_applicator.Changed += FireChangedEvent;
	}

	public ApplicatorRecipientsTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( ApplicatorRecipientsTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ApplicatorRecipientsTargetSelector" );
		applicator = source.applicator;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ApplicatorRecipientsTargetSelector source = _source as ApplicatorRecipientsTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ApplicatorRecipientsTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ApplicatorRecipientsTargetSelector newParent = rawParent == null ? null : rawParent.Get<ApplicatorRecipientsTargetSelector>();
		if ( newParent == null && _newParent is ApplicatorRecipientsTargetSelector )
			newParent = _newParent as ApplicatorRecipientsTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_applicator.SetParent( newParent == null ? null : newParent._applicator );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_applicator.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_applicator.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "applicator" )
			_applicator.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "applicator" )
			return _applicator.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAreaTargetSelector", "PFTargetSelector.h")]
[TypeId(0x9E676B40)]
[UseTypeName("TGSL")]
public class AreaTargetSelector : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<AreaTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<AreaTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _range;
	private Vec2 _absolutePosition;
	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;

	[Description( "Range of selection" )]
	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	[Description( "Absolute position of area selection center point; set (0,0) to ignore this parameter" )]
	public Vec2 absolutePosition { get { return _absolutePosition; } set { _absolutePosition.Assign( value ); } }

	[Description( "Position from which AreaTargetSelector should search targets" )]
	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AreaTargetSelector>(owner);
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		_absolutePosition = new Vec2( owner );
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_absolutePosition.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public AreaTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( AreaTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AreaTargetSelector" );
		range = source.range;
		absolutePosition = source.absolutePosition;
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AreaTargetSelector source = _source as AreaTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AreaTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AreaTargetSelector newParent = rawParent == null ? null : rawParent.Get<AreaTargetSelector>();
		if ( newParent == null && _newParent is AreaTargetSelector )
			newParent = _newParent as AreaTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_range.SetParent( newParent == null ? null : newParent._range );
		_absolutePosition.SetParent( newParent == null ? null : newParent._absolutePosition );
		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_range.Reset();
		_absolutePosition.Reset();
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_range.IsDerivedFromParent()
			&& _absolutePosition.IsDerivedFromParent()
			&& _targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "absolutePosition" )
			_absolutePosition.Reset();
		else if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "absolutePosition" )
			return _absolutePosition.IsDerivedFromParent();
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFMultipleTargetSelectorMicroAI", "PFMicroAI.h", CreateFunction = "NWorld::CreateMicroAI<>")]
[UseTypeName("MCAI")]
public class MultipleTargetSelectorMicroAI : BasicMicroAI
{
	private UndoRedoDBPtr<MultipleTargetSelectorMicroAI> ___parent;
	[HideInOutliner]
	public new DBPtr<MultipleTargetSelectorMicroAI> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;
	private ExecutableBoolString _unitFilter;
	private UndoRedo<int> _minTargetCount;
	private UndoRedo<float> _minTargetWeight;

	[Description( "TargetSelector для поиска целей" )]
	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Дополнительное условие, на найденные цели" )]
	public ExecutableBoolString unitFilter { get { return _unitFilter; } set { _unitFilter.Assign( value ); } }

	[Description( "Минимальное количество целей для каста абилки. Установить 0 если надо кастовать только когда цели не найдены." )]
	[IntMin(0)]
	public int minTargetCount { get { return _minTargetCount.Get(); } set { _minTargetCount.Set( value ); } }

	[Description( "Минимальный вес каждой цели" )]
	public float minTargetWeight { get { return _minTargetWeight.Get(); } set { _minTargetWeight.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MultipleTargetSelectorMicroAI>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		ExecutableBoolString __unitFilter = new ExecutableBoolString(); // Construct default object for unitFilter
		__unitFilter.sString = "true";
		_unitFilter = new ExecutableBoolString( owner, __unitFilter );
		_minTargetCount = new UndoRedo<int>( owner, 1 );
		_minTargetWeight = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_unitFilter.Changed += FireChangedEvent;
		_minTargetCount.Changed += FireChangedEvent;
		_minTargetWeight.Changed += FireChangedEvent;
	}

	public MultipleTargetSelectorMicroAI()
	{
		Initialize( this );
	}
	private void AssignSelf( MultipleTargetSelectorMicroAI source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MultipleTargetSelectorMicroAI" );
		targetSelector = source.targetSelector;
		unitFilter = source.unitFilter;
		minTargetCount = source.minTargetCount;
		minTargetWeight = source.minTargetWeight;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MultipleTargetSelectorMicroAI source = _source as MultipleTargetSelectorMicroAI;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MultipleTargetSelectorMicroAI" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MultipleTargetSelectorMicroAI newParent = rawParent == null ? null : rawParent.Get<MultipleTargetSelectorMicroAI>();
		if ( newParent == null && _newParent is MultipleTargetSelectorMicroAI )
			newParent = _newParent as MultipleTargetSelectorMicroAI;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_unitFilter.SetParent( newParent == null ? null : newParent._unitFilter );
		_minTargetCount.SetParent( newParent == null ? null : newParent._minTargetCount );
		_minTargetWeight.SetParent( newParent == null ? null : newParent._minTargetWeight );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_unitFilter.Reset();
		_minTargetCount.Reset();
		_minTargetWeight.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _unitFilter.IsDerivedFromParent()
			&& _minTargetCount.IsDerivedFromParent()
			&& _minTargetWeight.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "unitFilter" )
			_unitFilter.Reset();
		else if ( fieldName == "minTargetCount" )
			_minTargetCount.Reset();
		else if ( fieldName == "minTargetWeight" )
			_minTargetWeight.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "unitFilter" )
			return _unitFilter.IsDerivedFromParent();
		if ( fieldName == "minTargetCount" )
			return _minTargetCount.IsDerivedFromParent();
		if ( fieldName == "minTargetWeight" )
			return _minTargetWeight.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplNaftaTransfer", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0E676B40)]
[UseTypeName("APLR")]
public class NaftaTransferApplicator : BaseApplicator
{
	private UndoRedoDBPtr<NaftaTransferApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<NaftaTransferApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _naftaTransferTarget;
	private ExecutableFloatString _amount;
	private ExecutableFloatString _multiplier;
	private ExecutableFloatString _addition;
	private UndoRedoDBPtr<UIEvent> _uiEvent;

	[Description( "Nafta is transfered from receiver of this applicator to this target" )]
	public EApplicatorApplyTarget naftaTransferTarget { get { return _naftaTransferTarget.Get(); } set { _naftaTransferTarget.Set( value ); } }

	[Description( "Amount of nafta to be taken from receiver" )]
	public ExecutableFloatString amount { get { return _amount; } set { _amount.Assign( value ); } }

	[Description( "Multiplier of nafta to be transfered" )]
	public ExecutableFloatString multiplier { get { return _multiplier; } set { _multiplier.Assign( value ); } }

	[Description( "Bonus nafta to be transfered" )]
	public ExecutableFloatString addition { get { return _addition; } set { _addition.Assign( value ); } }

	[Description( "UI Event" )]
	public DBPtr<UIEvent> uiEvent { get { return _uiEvent.Get(); } set { _uiEvent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<NaftaTransferApplicator>(owner);
		_naftaTransferTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.AbilityOwner );
		ExecutableFloatString __amount = new ExecutableFloatString(); // Construct default object for amount
		__amount.sString = "0.0f";
		_amount = new ExecutableFloatString( owner, __amount );
		ExecutableFloatString __multiplier = new ExecutableFloatString(); // Construct default object for multiplier
		__multiplier.sString = "1.0f";
		_multiplier = new ExecutableFloatString( owner, __multiplier );
		ExecutableFloatString __addition = new ExecutableFloatString(); // Construct default object for addition
		__addition.sString = "0.0f";
		_addition = new ExecutableFloatString( owner, __addition );
		_uiEvent = new UndoRedoDBPtr<UIEvent>( owner );
		___parent.Changed += FireChangedEvent;
		_naftaTransferTarget.Changed += FireChangedEvent;
		_amount.Changed += FireChangedEvent;
		_multiplier.Changed += FireChangedEvent;
		_addition.Changed += FireChangedEvent;
		_uiEvent.Changed += FireChangedEvent;
	}

	public NaftaTransferApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( NaftaTransferApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for NaftaTransferApplicator" );
		naftaTransferTarget = source.naftaTransferTarget;
		amount = source.amount;
		multiplier = source.multiplier;
		addition = source.addition;
		uiEvent = source.uiEvent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		NaftaTransferApplicator source = _source as NaftaTransferApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NaftaTransferApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		NaftaTransferApplicator newParent = rawParent == null ? null : rawParent.Get<NaftaTransferApplicator>();
		if ( newParent == null && _newParent is NaftaTransferApplicator )
			newParent = _newParent as NaftaTransferApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_naftaTransferTarget.SetParent( newParent == null ? null : newParent._naftaTransferTarget );
		_amount.SetParent( newParent == null ? null : newParent._amount );
		_multiplier.SetParent( newParent == null ? null : newParent._multiplier );
		_addition.SetParent( newParent == null ? null : newParent._addition );
		_uiEvent.SetParent( newParent == null ? null : newParent._uiEvent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_naftaTransferTarget.Reset();
		_amount.Reset();
		_multiplier.Reset();
		_addition.Reset();
		_uiEvent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_naftaTransferTarget.IsDerivedFromParent()
			&& _amount.IsDerivedFromParent()
			&& _multiplier.IsDerivedFromParent()
			&& _addition.IsDerivedFromParent()
			&& _uiEvent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "naftaTransferTarget" )
			_naftaTransferTarget.Reset();
		else if ( fieldName == "amount" )
			_amount.Reset();
		else if ( fieldName == "multiplier" )
			_multiplier.Reset();
		else if ( fieldName == "addition" )
			_addition.Reset();
		else if ( fieldName == "uiEvent" )
			_uiEvent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "naftaTransferTarget" )
			return _naftaTransferTarget.IsDerivedFromParent();
		if ( fieldName == "amount" )
			return _amount.IsDerivedFromParent();
		if ( fieldName == "multiplier" )
			return _multiplier.IsDerivedFromParent();
		if ( fieldName == "addition" )
			return _addition.IsDerivedFromParent();
		if ( fieldName == "uiEvent" )
			return _uiEvent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFNearestInAreaTargetSelector", "PFTargetSelector.h")]
[TypeId(0x9E67EC00)]
[UseTypeName("TGSL")]
public class NearestInAreaTargetSelector : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<NearestInAreaTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<NearestInAreaTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _range;

	[Description( "Range of selection" )]
	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<NearestInAreaTargetSelector>(owner);
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		___parent.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
	}

	public NearestInAreaTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( NearestInAreaTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for NearestInAreaTargetSelector" );
		range = source.range;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		NearestInAreaTargetSelector source = _source as NearestInAreaTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NearestInAreaTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		NearestInAreaTargetSelector newParent = rawParent == null ? null : rawParent.Get<NearestInAreaTargetSelector>();
		if ( newParent == null && _newParent is NearestInAreaTargetSelector )
			newParent = _newParent as NearestInAreaTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_range.SetParent( newParent == null ? null : newParent._range );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_range.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_range.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "range" )
			_range.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFNearestTargetSelector", "PFTargetSelector.h")]
[TypeId(0x9E6C8340)]
[UseTypeName("TGSL")]
public class NearestTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<NearestTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<NearestTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;

	[Description( "Target selector to select from" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<NearestTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public NearestTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( NearestTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for NearestTargetSelector" );
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		NearestTargetSelector source = _source as NearestTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NearestTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		NearestTargetSelector newParent = rawParent == null ? null : rawParent.Get<NearestTargetSelector>();
		if ( newParent == null && _newParent is NearestTargetSelector )
			newParent = _newParent as NearestTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFNotTargetOfSameAbilitySelector", "PFAITargetSelectors.h")]
[TypeId(0x9A9C6C40)]
[UseTypeName("TGSL")]
public class NotTargetOfSameAbilitySelector : MultipleTargetSelector
{
	private UndoRedoDBPtr<NotTargetOfSameAbilitySelector> ___parent;
	[HideInOutliner]
	public new DBPtr<NotTargetOfSameAbilitySelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;
	private UndoRedoDBPtr<TargetSelector> _abilityCastersSelector;
	private ExecutableFloatString _minDistBetweenTargets;

	[Description( "Селектор, чьи цели проверяем и выдаем" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Селектор, который ищет применяющих ту же абилку" )]
	public DBPtr<TargetSelector> abilityCastersSelector { get { return _abilityCastersSelector.Get(); } set { _abilityCastersSelector.Set( value ); } }

	[Description( "Если цель абилки - точка, задает разрешенное расстояние между целями" )]
	public ExecutableFloatString minDistBetweenTargets { get { return _minDistBetweenTargets; } set { _minDistBetweenTargets.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<NotTargetOfSameAbilitySelector>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		_abilityCastersSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		ExecutableFloatString __minDistBetweenTargets = new ExecutableFloatString(); // Construct default object for minDistBetweenTargets
		__minDistBetweenTargets.sString = "0.f";
		_minDistBetweenTargets = new ExecutableFloatString( owner, __minDistBetweenTargets );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_abilityCastersSelector.Changed += FireChangedEvent;
		_minDistBetweenTargets.Changed += FireChangedEvent;
	}

	public NotTargetOfSameAbilitySelector()
	{
		Initialize( this );
	}
	private void AssignSelf( NotTargetOfSameAbilitySelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for NotTargetOfSameAbilitySelector" );
		targetSelector = source.targetSelector;
		abilityCastersSelector = source.abilityCastersSelector;
		minDistBetweenTargets = source.minDistBetweenTargets;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		NotTargetOfSameAbilitySelector source = _source as NotTargetOfSameAbilitySelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NotTargetOfSameAbilitySelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		NotTargetOfSameAbilitySelector newParent = rawParent == null ? null : rawParent.Get<NotTargetOfSameAbilitySelector>();
		if ( newParent == null && _newParent is NotTargetOfSameAbilitySelector )
			newParent = _newParent as NotTargetOfSameAbilitySelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_abilityCastersSelector.SetParent( newParent == null ? null : newParent._abilityCastersSelector );
		_minDistBetweenTargets.SetParent( newParent == null ? null : newParent._minDistBetweenTargets );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_abilityCastersSelector.Reset();
		_minDistBetweenTargets.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _abilityCastersSelector.IsDerivedFromParent()
			&& _minDistBetweenTargets.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "abilityCastersSelector" )
			_abilityCastersSelector.Reset();
		else if ( fieldName == "minDistBetweenTargets" )
			_minDistBetweenTargets.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "abilityCastersSelector" )
			return _abilityCastersSelector.IsDerivedFromParent();
		if ( fieldName == "minDistBetweenTargets" )
			return _minDistBetweenTargets.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplOnDamage", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B07)]
[UseTypeName("APLR")]
public class OnDamageApplicator : BuffApplicator
{
	private UndoRedoDBPtr<OnDamageApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<OnDamageApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EDamageFilter> _filterFlags;
	private UndoRedoDBPtr<Spell> _spell;
	private UndoRedo<EApplicatorApplyTarget> _spellTarget;

	[Description( "Flags that allow control over type of damage that produces spell" )]
	public EDamageFilter filterFlags { get { return _filterFlags.Get(); } set { _filterFlags.Set( value ); } }

	[Category( "OnDamage" )]
	[Description( "A spell that will be cast on sender of incoming damage" )]
	public DBPtr<Spell> spell { get { return _spell.Get(); } set { _spell.Set( value ); } }

	[Category( "OnDamage" )]
	[Description( "A spell that will be cast on sender of incoming damage" )]
	public EApplicatorApplyTarget spellTarget { get { return _spellTarget.Get(); } set { _spellTarget.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OnDamageApplicator>(owner);
		_filterFlags = new UndoRedo<EDamageFilter>( owner, EDamageFilter.All );
		_spell = new UndoRedoDBPtr<Spell>( owner );
		_spellTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		___parent.Changed += FireChangedEvent;
		_filterFlags.Changed += FireChangedEvent;
		_spell.Changed += FireChangedEvent;
		_spellTarget.Changed += FireChangedEvent;
	}

	public OnDamageApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( OnDamageApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OnDamageApplicator" );
		filterFlags = source.filterFlags;
		spell = source.spell;
		spellTarget = source.spellTarget;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OnDamageApplicator source = _source as OnDamageApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OnDamageApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OnDamageApplicator newParent = rawParent == null ? null : rawParent.Get<OnDamageApplicator>();
		if ( newParent == null && _newParent is OnDamageApplicator )
			newParent = _newParent as OnDamageApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_filterFlags.SetParent( newParent == null ? null : newParent._filterFlags );
		_spell.SetParent( newParent == null ? null : newParent._spell );
		_spellTarget.SetParent( newParent == null ? null : newParent._spellTarget );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_filterFlags.Reset();
		_spell.Reset();
		_spellTarget.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_filterFlags.IsDerivedFromParent()
			&& _spell.IsDerivedFromParent()
			&& _spellTarget.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "filterFlags" )
			_filterFlags.Reset();
		else if ( fieldName == "spell" )
			_spell.Reset();
		else if ( fieldName == "spellTarget" )
			_spellTarget.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "filterFlags" )
			return _filterFlags.IsDerivedFromParent();
		if ( fieldName == "spell" )
			return _spell.IsDerivedFromParent();
		if ( fieldName == "spellTarget" )
			return _spellTarget.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[FactoryImpl("Create", "NWorld::PFApplPermanentStatMod", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E688C00)]
[UseTypeName("APLR")]
public class PermanentStatModApplicator : BaseApplicator
{
	private UndoRedoDBPtr<PermanentStatModApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<PermanentStatModApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ECustomApplyType> _customApplyType;
	private Modifier _modifier;

	[NoCode]
	public ECustomApplyType customApplyType { get { return _customApplyType.Get(); } set { _customApplyType.Set( value ); } }

	[Category( "StatModifier" )]
	public Modifier modifier { get { return _modifier; } set { _modifier.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PermanentStatModApplicator>(owner);
		_customApplyType = new UndoRedo<ECustomApplyType>( owner, ECustomApplyType.None );
		_modifier = new Modifier( owner );
		___parent.Changed += FireChangedEvent;
		_customApplyType.Changed += FireChangedEvent;
		_modifier.Changed += FireChangedEvent;
	}

	public PermanentStatModApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( PermanentStatModApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PermanentStatModApplicator" );
		customApplyType = source.customApplyType;
		modifier = source.modifier;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PermanentStatModApplicator source = _source as PermanentStatModApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PermanentStatModApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PermanentStatModApplicator newParent = rawParent == null ? null : rawParent.Get<PermanentStatModApplicator>();
		if ( newParent == null && _newParent is PermanentStatModApplicator )
			newParent = _newParent as PermanentStatModApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_customApplyType.SetParent( newParent == null ? null : newParent._customApplyType );
		_modifier.SetParent( newParent == null ? null : newParent._modifier );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_customApplyType.Reset();
		_modifier.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_customApplyType.IsDerivedFromParent()
			&& _modifier.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "customApplyType" )
			_customApplyType.Reset();
		else if ( fieldName == "modifier" )
			_modifier.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "customApplyType" )
			return _customApplyType.IsDerivedFromParent();
		if ( fieldName == "modifier" )
			return _modifier.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplPickupChanneling", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE7A4F3C0)]
[UseTypeName("APLR")]
public class PickupChannelingApplicator : ChannellingApplicator
{
	private UndoRedoDBPtr<PickupChannelingApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<PickupChannelingApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PickupChannelingApplicator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public PickupChannelingApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( PickupChannelingApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PickupChannelingApplicator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PickupChannelingApplicator source = _source as PickupChannelingApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PickupChannelingApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PickupChannelingApplicator newParent = rawParent == null ? null : rawParent.Get<PickupChannelingApplicator>();
		if ( newParent == null && _newParent is PickupChannelingApplicator )
			newParent = _newParent as PickupChannelingApplicator;
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

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFPointTargetSelector", "PFTargetSelector.h")]
[TypeId(0x1E728BC0)]
[UseTypeName("TGSL")]
public class PointTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<PointTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<PointTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;
	private UndoRedo<EPointTargetSelectorMode> _mode;
	private ExecutableFloatString _range;
	private Vec2 _offset;
	private UndoRedo<ETraceMode> _traceMode;
	private UndoRedo<bool> _checkMinRange;
	private UndoRedo<bool> _paralleledTarget;

	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	public EPointTargetSelectorMode mode { get { return _mode.Get(); } set { _mode.Set( value ); } }

	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	[Description( "Смещение относительно хозяина. ВАЖНО! Нормируется и умножается на range!" )]
	public Vec2 offset { get { return _offset; } set { _offset.Assign( value ); } }

	[Description( "Works only for mode = RangeFromOwner, OffsetFromOwner, OffsetFromTarget" )]
	public ETraceMode traceMode { get { return _traceMode.Get(); } set { _traceMode.Set( value ); } }

	[Description( "Check range with half sizes of owner and target" )]
	public bool checkMinRange { get { return _checkMinRange.Get(); } set { _checkMinRange.Set( value ); } }

	[Description( "Calculate new target as parallel to vector from owner to target which selected target from received unit position (only for RangeFromOwner)" )]
	public bool paralleledTarget { get { return _paralleledTarget.Get(); } set { _paralleledTarget.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PointTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_mode = new UndoRedo<EPointTargetSelectorMode>( owner, EPointTargetSelectorMode.ToOwner );
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		Vec2 __offset = new Vec2(); // Construct default object for offset
		__offset.y = 1.0f;
		_offset = new Vec2( owner, __offset );
		_traceMode = new UndoRedo<ETraceMode>( owner, (ETraceMode)0 );
		_checkMinRange = new UndoRedo<bool>( owner, true );
		_paralleledTarget = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
		_traceMode.Changed += FireChangedEvent;
		_checkMinRange.Changed += FireChangedEvent;
		_paralleledTarget.Changed += FireChangedEvent;
	}

	public PointTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( PointTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PointTargetSelector" );
		targetSelector = source.targetSelector;
		mode = source.mode;
		range = source.range;
		offset = source.offset;
		traceMode = source.traceMode;
		checkMinRange = source.checkMinRange;
		paralleledTarget = source.paralleledTarget;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PointTargetSelector source = _source as PointTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PointTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PointTargetSelector newParent = rawParent == null ? null : rawParent.Get<PointTargetSelector>();
		if ( newParent == null && _newParent is PointTargetSelector )
			newParent = _newParent as PointTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_mode.SetParent( newParent == null ? null : newParent._mode );
		_range.SetParent( newParent == null ? null : newParent._range );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		_traceMode.SetParent( newParent == null ? null : newParent._traceMode );
		_checkMinRange.SetParent( newParent == null ? null : newParent._checkMinRange );
		_paralleledTarget.SetParent( newParent == null ? null : newParent._paralleledTarget );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_mode.Reset();
		_range.Reset();
		_offset.Reset();
		_traceMode.Reset();
		_checkMinRange.Reset();
		_paralleledTarget.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _mode.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& _traceMode.IsDerivedFromParent()
			&& _checkMinRange.IsDerivedFromParent()
			&& _paralleledTarget.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "mode" )
			_mode.Reset();
		else if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else if ( fieldName == "traceMode" )
			_traceMode.Reset();
		else if ( fieldName == "checkMinRange" )
			_checkMinRange.Reset();
		else if ( fieldName == "paralleledTarget" )
			_paralleledTarget.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "mode" )
			return _mode.IsDerivedFromParent();
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		if ( fieldName == "traceMode" )
			return _traceMode.IsDerivedFromParent();
		if ( fieldName == "checkMinRange" )
			return _checkMinRange.IsDerivedFromParent();
		if ( fieldName == "paralleledTarget" )
			return _paralleledTarget.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Check", "NWorld::PFAbilityData", "PFCastLimitations.h", CreateFunction = "NWorld::CheckPositionLimitation")]
[TypeId(0x5BB4ABC0)]
[UseTypeName("ABCL")]
public class PositionCastLimitation : CastLimitation
{
	private UndoRedoDBPtr<PositionCastLimitation> ___parent;
	[HideInOutliner]
	public new DBPtr<PositionCastLimitation> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableBooleanString _condition;

	[Description( "Condition to check validity of cast" )]
	public ExecutableBooleanString condition { get { return _condition; } set { _condition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PositionCastLimitation>(owner);
		_condition = new ExecutableBooleanString( owner );
		___parent.Changed += FireChangedEvent;
		_condition.Changed += FireChangedEvent;
	}

	public PositionCastLimitation()
	{
		Initialize( this );
	}
	private void AssignSelf( PositionCastLimitation source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PositionCastLimitation" );
		condition = source.condition;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PositionCastLimitation source = _source as PositionCastLimitation;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PositionCastLimitation" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PositionCastLimitation newParent = rawParent == null ? null : rawParent.Get<PositionCastLimitation>();
		if ( newParent == null && _newParent is PositionCastLimitation )
			newParent = _newParent as PositionCastLimitation;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_condition.SetParent( newParent == null ? null : newParent._condition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_condition.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_condition.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "condition" )
			_condition.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplProgram", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E676A80)]
[UseTypeName("APLR")]
public class ProgramApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ProgramApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ProgramApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<ApplicatorToExecute> _applicators;

	[Description( "Applicators to be applied sequentially (one after another)" )]
	public libdb.IChangeableList<ApplicatorToExecute> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ProgramApplicator>(owner);
		_applicators = new UndoRedoAssignableList<ApplicatorToExecute>( owner );
		___parent.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
	}

	public ProgramApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ProgramApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ProgramApplicator" );
		applicators = source.applicators;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ProgramApplicator source = _source as ProgramApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ProgramApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ProgramApplicator newParent = rawParent == null ? null : rawParent.Get<ProgramApplicator>();
		if ( newParent == null && _newParent is ProgramApplicator )
			newParent = _newParent as ProgramApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_applicators.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_applicators.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "applicators" )
			_applicators.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplRaiseFlag", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0B76AA41)]
[UseTypeName("APLR")]
public class RaiseFlagApplicator : ChannellingApplicator
{
	private UndoRedoDBPtr<RaiseFlagApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<RaiseFlagApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RaiseFlagApplicator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public RaiseFlagApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( RaiseFlagApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RaiseFlagApplicator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RaiseFlagApplicator source = _source as RaiseFlagApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RaiseFlagApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RaiseFlagApplicator newParent = rawParent == null ? null : rawParent.Get<RaiseFlagApplicator>();
		if ( newParent == null && _newParent is RaiseFlagApplicator )
			newParent = _newParent as RaiseFlagApplicator;
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

[FactoryImpl("Create", "NWorld::PFApplRefreshCooldown", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E79AD18)]
[UseTypeName("APLR")]
public class RefreshCooldownApplicator : BaseApplicator
{
	private UndoRedoDBPtr<RefreshCooldownApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<RefreshCooldownApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EAbilityIdFlags> _flags;
	private UndoRedo<bool> _refreshThis;
	private ExecutableFloatString _reductionAmount;
	private UndoRedoAssignableList<DBPtr<Ability>> _talents;
	private UndoRedo<EUseMode> _useListAs;
	private UndoRedo<bool> _allowCdIncrease;
	private UndoRedo<bool> _reduceByPercent;

	[Description( "Задает способности героя, которым следует сбросить кулдаун" )]
	public EAbilityIdFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[Description( "Нужно ли сбрасывать кулдаун у данной способности" )]
	public bool refreshThis { get { return _refreshThis.Get(); } set { _refreshThis.Set( value ); } }

	[Description( "На сколько сбросить кулдаун, в секундах (если <= 0, то полностью). Процент (точнее сотые), если стоит флаг reductByPercent" )]
	public ExecutableFloatString reductionAmount { get { return _reductionAmount; } set { _reductionAmount.Assign( value ); } }

	[Description( "Список улучшаемых талантов" )]
	public libdb.IChangeableList<DBPtr<Ability>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	[Description( "Режим работы со списком" )]
	public EUseMode useListAs { get { return _useListAs.Get(); } set { _useListAs.Set( value ); } }

	[Description( "Разрешить увеличивать кулдаун (указывая отрицательный reductionAmount)" )]
	public bool allowCdIncrease { get { return _allowCdIncrease.Get(); } set { _allowCdIncrease.Set( value ); } }

	[Description( "Сбросить кулдаун на процент вместо секунд" )]
	public bool reduceByPercent { get { return _reduceByPercent.Get(); } set { _reduceByPercent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RefreshCooldownApplicator>(owner);
		_flags = new UndoRedo<EAbilityIdFlags>( owner, EAbilityIdFlags.All );
		_refreshThis = new UndoRedo<bool>( owner, false );
		ExecutableFloatString __reductionAmount = new ExecutableFloatString(); // Construct default object for reductionAmount
		__reductionAmount.sString = "-1.0f";
		_reductionAmount = new ExecutableFloatString( owner, __reductionAmount );
		_talents = new UndoRedoAssignableList<DBPtr<Ability>>( owner );
		_useListAs = new UndoRedo<EUseMode>( owner, EUseMode.ListAsRule );
		_allowCdIncrease = new UndoRedo<bool>( owner, false );
		_reduceByPercent = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_refreshThis.Changed += FireChangedEvent;
		_reductionAmount.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
		_useListAs.Changed += FireChangedEvent;
		_allowCdIncrease.Changed += FireChangedEvent;
		_reduceByPercent.Changed += FireChangedEvent;
	}

	public RefreshCooldownApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( RefreshCooldownApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RefreshCooldownApplicator" );
		flags = source.flags;
		refreshThis = source.refreshThis;
		reductionAmount = source.reductionAmount;
		talents = source.talents;
		useListAs = source.useListAs;
		allowCdIncrease = source.allowCdIncrease;
		reduceByPercent = source.reduceByPercent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RefreshCooldownApplicator source = _source as RefreshCooldownApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RefreshCooldownApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RefreshCooldownApplicator newParent = rawParent == null ? null : rawParent.Get<RefreshCooldownApplicator>();
		if ( newParent == null && _newParent is RefreshCooldownApplicator )
			newParent = _newParent as RefreshCooldownApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_flags.SetParent( newParent == null ? null : newParent._flags );
		_refreshThis.SetParent( newParent == null ? null : newParent._refreshThis );
		_reductionAmount.SetParent( newParent == null ? null : newParent._reductionAmount );
		_talents.SetParent( newParent == null ? null : newParent._talents );
		_useListAs.SetParent( newParent == null ? null : newParent._useListAs );
		_allowCdIncrease.SetParent( newParent == null ? null : newParent._allowCdIncrease );
		_reduceByPercent.SetParent( newParent == null ? null : newParent._reduceByPercent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_flags.Reset();
		_refreshThis.Reset();
		_reductionAmount.Reset();
		_talents.Reset();
		_useListAs.Reset();
		_allowCdIncrease.Reset();
		_reduceByPercent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_flags.IsDerivedFromParent()
			&& _refreshThis.IsDerivedFromParent()
			&& _reductionAmount.IsDerivedFromParent()
			&& _talents.IsDerivedFromParent()
			&& _useListAs.IsDerivedFromParent()
			&& _allowCdIncrease.IsDerivedFromParent()
			&& _reduceByPercent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "refreshThis" )
			_refreshThis.Reset();
		else if ( fieldName == "reductionAmount" )
			_reductionAmount.Reset();
		else if ( fieldName == "talents" )
			_talents.Reset();
		else if ( fieldName == "useListAs" )
			_useListAs.Reset();
		else if ( fieldName == "allowCdIncrease" )
			_allowCdIncrease.Reset();
		else if ( fieldName == "reduceByPercent" )
			_reduceByPercent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "refreshThis" )
			return _refreshThis.IsDerivedFromParent();
		if ( fieldName == "reductionAmount" )
			return _reductionAmount.IsDerivedFromParent();
		if ( fieldName == "talents" )
			return _talents.IsDerivedFromParent();
		if ( fieldName == "useListAs" )
			return _useListAs.IsDerivedFromParent();
		if ( fieldName == "allowCdIncrease" )
			return _allowCdIncrease.IsDerivedFromParent();
		if ( fieldName == "reduceByPercent" )
			return _reduceByPercent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFRelativeUnitTargetSelector", "PFTargetSelector.h")]
[TypeId(0x9E6C8400)]
[UseTypeName("TGSL")]
public class RelativeUnitTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<RelativeUnitTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<RelativeUnitTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EUnitRelation> _relation;

	public EUnitRelation relation { get { return _relation.Get(); } set { _relation.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RelativeUnitTargetSelector>(owner);
		_relation = new UndoRedo<EUnitRelation>( owner, EUnitRelation.Master );
		___parent.Changed += FireChangedEvent;
		_relation.Changed += FireChangedEvent;
	}

	public RelativeUnitTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( RelativeUnitTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RelativeUnitTargetSelector" );
		relation = source.relation;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RelativeUnitTargetSelector source = _source as RelativeUnitTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RelativeUnitTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RelativeUnitTargetSelector newParent = rawParent == null ? null : rawParent.Get<RelativeUnitTargetSelector>();
		if ( newParent == null && _newParent is RelativeUnitTargetSelector )
			newParent = _newParent as RelativeUnitTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_relation.SetParent( newParent == null ? null : newParent._relation );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_relation.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_relation.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "relation" )
			_relation.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "relation" )
			return _relation.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFResurrectApplicator", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2C6C8442)]
[UseTypeName("APLR")]
public class ResurrectApplicator : BaseApplicator
{
	private UndoRedoDBPtr<ResurrectApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ResurrectApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _healthPercent;
	private UndoRedo<float> _energyPercent;

	[FloatMinMax(0, 100)]
	public float healthPercent { get { return _healthPercent.Get(); } set { _healthPercent.Set( value ); } }

	[FloatMinMax(0, 100)]
	public float energyPercent { get { return _energyPercent.Get(); } set { _energyPercent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ResurrectApplicator>(owner);
		_healthPercent = new UndoRedo<float>( owner, 100.0f );
		_energyPercent = new UndoRedo<float>( owner, 100.0f );
		___parent.Changed += FireChangedEvent;
		_healthPercent.Changed += FireChangedEvent;
		_energyPercent.Changed += FireChangedEvent;
	}

	public ResurrectApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ResurrectApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ResurrectApplicator" );
		healthPercent = source.healthPercent;
		energyPercent = source.energyPercent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ResurrectApplicator source = _source as ResurrectApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResurrectApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ResurrectApplicator newParent = rawParent == null ? null : rawParent.Get<ResurrectApplicator>();
		if ( newParent == null && _newParent is ResurrectApplicator )
			newParent = _newParent as ResurrectApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_healthPercent.SetParent( newParent == null ? null : newParent._healthPercent );
		_energyPercent.SetParent( newParent == null ? null : newParent._energyPercent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_healthPercent.Reset();
		_energyPercent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_healthPercent.IsDerivedFromParent()
			&& _energyPercent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "healthPercent" )
			_healthPercent.Reset();
		else if ( fieldName == "energyPercent" )
			_energyPercent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "healthPercent" )
			return _healthPercent.IsDerivedFromParent();
		if ( fieldName == "energyPercent" )
			return _energyPercent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplScaleControl", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9A9CA341)]
[UseTypeName("APLR")]
public class ScaleControlApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ScaleControlApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ScaleControlApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _desiredScale;
	private ExecutableFloatString _changeSpeed;

	[Description( "Желаемый масштаб цели. Текущий масштаб будет подтягиваться к желаемому" )]
	public ExecutableFloatString desiredScale { get { return _desiredScale; } set { _desiredScale.Assign( value ); } }

	[Description( "Скорость изменения масштаба, % в секунду" )]
	public ExecutableFloatString changeSpeed { get { return _changeSpeed; } set { _changeSpeed.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ScaleControlApplicator>(owner);
		ExecutableFloatString __desiredScale = new ExecutableFloatString(); // Construct default object for desiredScale
		__desiredScale.sString = "1.0f";
		_desiredScale = new ExecutableFloatString( owner, __desiredScale );
		ExecutableFloatString __changeSpeed = new ExecutableFloatString(); // Construct default object for changeSpeed
		__changeSpeed.sString = "10.0f";
		_changeSpeed = new ExecutableFloatString( owner, __changeSpeed );
		___parent.Changed += FireChangedEvent;
		_desiredScale.Changed += FireChangedEvent;
		_changeSpeed.Changed += FireChangedEvent;
	}

	public ScaleControlApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ScaleControlApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ScaleControlApplicator" );
		desiredScale = source.desiredScale;
		changeSpeed = source.changeSpeed;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ScaleControlApplicator source = _source as ScaleControlApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScaleControlApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ScaleControlApplicator newParent = rawParent == null ? null : rawParent.Get<ScaleControlApplicator>();
		if ( newParent == null && _newParent is ScaleControlApplicator )
			newParent = _newParent as ScaleControlApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_desiredScale.SetParent( newParent == null ? null : newParent._desiredScale );
		_changeSpeed.SetParent( newParent == null ? null : newParent._changeSpeed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_desiredScale.Reset();
		_changeSpeed.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_desiredScale.IsDerivedFromParent()
			&& _changeSpeed.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "desiredScale" )
			_desiredScale.Reset();
		else if ( fieldName == "changeSpeed" )
			_changeSpeed.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "desiredScale" )
			return _desiredScale.IsDerivedFromParent();
		if ( fieldName == "changeSpeed" )
			return _changeSpeed.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplSceneObjectChange", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2B7B8C40)]
[UseTypeName("APLR")]
public class SceneObjectChangeApplicator : BuffApplicator
{
	private UndoRedoDBPtr<SceneObjectChangeApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SceneObjectChangeApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _sceneObjects;
	private ExecutableIntString _sceneObjectIndex;

	[Description( "List of scene objects" )]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> sceneObjects { get { return _sceneObjects; } set { _sceneObjects.Assign( value ); } }

	[Description( "Index to select scene object from the list" )]
	public ExecutableIntString sceneObjectIndex { get { return _sceneObjectIndex; } set { _sceneObjectIndex.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SceneObjectChangeApplicator>(owner);
		_sceneObjects = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner );
		_sceneObjectIndex = new ExecutableIntString( owner );
		___parent.Changed += FireChangedEvent;
		_sceneObjects.Changed += FireChangedEvent;
		_sceneObjectIndex.Changed += FireChangedEvent;
	}

	public SceneObjectChangeApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SceneObjectChangeApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SceneObjectChangeApplicator" );
		sceneObjects = source.sceneObjects;
		sceneObjectIndex = source.sceneObjectIndex;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SceneObjectChangeApplicator source = _source as SceneObjectChangeApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SceneObjectChangeApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SceneObjectChangeApplicator newParent = rawParent == null ? null : rawParent.Get<SceneObjectChangeApplicator>();
		if ( newParent == null && _newParent is SceneObjectChangeApplicator )
			newParent = _newParent as SceneObjectChangeApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_sceneObjects.SetParent( newParent == null ? null : newParent._sceneObjects );
		_sceneObjectIndex.SetParent( newParent == null ? null : newParent._sceneObjectIndex );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_sceneObjects.Reset();
		_sceneObjectIndex.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_sceneObjects.IsDerivedFromParent()
			&& _sceneObjectIndex.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "sceneObjects" )
			_sceneObjects.Reset();
		else if ( fieldName == "sceneObjectIndex" )
			_sceneObjectIndex.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "sceneObjects" )
			return _sceneObjects.IsDerivedFromParent();
		if ( fieldName == "sceneObjectIndex" )
			return _sceneObjectIndex.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFSectorTargetSelector", "PFTargetSelector.h")]
[TypeId(0x9E6C8A40)]
[UseTypeName("TGSL")]
public class SectorTargetSelector : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<SectorTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<SectorTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ETargetSelectorPoint> _segmentBegin;
	private UndoRedo<ETargetSelectorPoint> _segmentEnd;
	private ExecutableFloatString _range;
	private UndoRedo<float> _angle;
	private UndoRedo<bool> _centerIsSegmentEnd;
	private UndoRedo<float> _segmentDirectionOffset;

	[Description( "Begin of segment defining direction" )]
	public ETargetSelectorPoint segmentBegin { get { return _segmentBegin.Get(); } set { _segmentBegin.Set( value ); } }

	[Description( "End of segment defining direction" )]
	public ETargetSelectorPoint segmentEnd { get { return _segmentEnd.Get(); } set { _segmentEnd.Set( value ); } }

	[Description( "Range of selection" )]
	public ExecutableFloatString range { get { return _range; } set { _range.Assign( value ); } }

	[Description( "Range of selection" )]
	public float angle { get { return _angle.Get(); } set { _angle.Set( value ); } }

	[Description( "Account segmentEnd as sector's center" )]
	public bool centerIsSegmentEnd { get { return _centerIsSegmentEnd.Get(); } set { _centerIsSegmentEnd.Set( value ); } }

	[Description( "Дополнительный поворот выбранного направления сектора, в градусах" )]
	public float segmentDirectionOffset { get { return _segmentDirectionOffset.Get(); } set { _segmentDirectionOffset.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SectorTargetSelector>(owner);
		_segmentBegin = new UndoRedo<ETargetSelectorPoint>( owner, ETargetSelectorPoint.AbilityOwner );
		_segmentEnd = new UndoRedo<ETargetSelectorPoint>( owner, ETargetSelectorPoint.CurrentPosition );
		ExecutableFloatString __range = new ExecutableFloatString(); // Construct default object for range
		__range.sString = "0.0f";
		_range = new ExecutableFloatString( owner, __range );
		_angle = new UndoRedo<float>( owner, 90.0f );
		_centerIsSegmentEnd = new UndoRedo<bool>( owner, false );
		_segmentDirectionOffset = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_segmentBegin.Changed += FireChangedEvent;
		_segmentEnd.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
		_angle.Changed += FireChangedEvent;
		_centerIsSegmentEnd.Changed += FireChangedEvent;
		_segmentDirectionOffset.Changed += FireChangedEvent;
	}

	public SectorTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( SectorTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SectorTargetSelector" );
		segmentBegin = source.segmentBegin;
		segmentEnd = source.segmentEnd;
		range = source.range;
		angle = source.angle;
		centerIsSegmentEnd = source.centerIsSegmentEnd;
		segmentDirectionOffset = source.segmentDirectionOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SectorTargetSelector source = _source as SectorTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SectorTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SectorTargetSelector newParent = rawParent == null ? null : rawParent.Get<SectorTargetSelector>();
		if ( newParent == null && _newParent is SectorTargetSelector )
			newParent = _newParent as SectorTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_segmentBegin.SetParent( newParent == null ? null : newParent._segmentBegin );
		_segmentEnd.SetParent( newParent == null ? null : newParent._segmentEnd );
		_range.SetParent( newParent == null ? null : newParent._range );
		_angle.SetParent( newParent == null ? null : newParent._angle );
		_centerIsSegmentEnd.SetParent( newParent == null ? null : newParent._centerIsSegmentEnd );
		_segmentDirectionOffset.SetParent( newParent == null ? null : newParent._segmentDirectionOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_segmentBegin.Reset();
		_segmentEnd.Reset();
		_range.Reset();
		_angle.Reset();
		_centerIsSegmentEnd.Reset();
		_segmentDirectionOffset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_segmentBegin.IsDerivedFromParent()
			&& _segmentEnd.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& _angle.IsDerivedFromParent()
			&& _centerIsSegmentEnd.IsDerivedFromParent()
			&& _segmentDirectionOffset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "segmentBegin" )
			_segmentBegin.Reset();
		else if ( fieldName == "segmentEnd" )
			_segmentEnd.Reset();
		else if ( fieldName == "range" )
			_range.Reset();
		else if ( fieldName == "angle" )
			_angle.Reset();
		else if ( fieldName == "centerIsSegmentEnd" )
			_centerIsSegmentEnd.Reset();
		else if ( fieldName == "segmentDirectionOffset" )
			_segmentDirectionOffset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "segmentBegin" )
			return _segmentBegin.IsDerivedFromParent();
		if ( fieldName == "segmentEnd" )
			return _segmentEnd.IsDerivedFromParent();
		if ( fieldName == "range" )
			return _range.IsDerivedFromParent();
		if ( fieldName == "angle" )
			return _angle.IsDerivedFromParent();
		if ( fieldName == "centerIsSegmentEnd" )
			return _centerIsSegmentEnd.IsDerivedFromParent();
		if ( fieldName == "segmentDirectionOffset" )
			return _segmentDirectionOffset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFSelectApplicatorTarget", "PFTargetSelector.h")]
[TypeId(0xE77B1C80)]
[UseTypeName("TGSL")]
public class SelectApplicatorTarget : SingleTargetSelector
{
	private UndoRedoDBPtr<SelectApplicatorTarget> ___parent;
	[HideInOutliner]
	public new DBPtr<SelectApplicatorTarget> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _selectTarget;
	private UndoRedo<string> _applicatorName;
	private UndoRedo<int> _applicatorIndex;
	private UndoRedo<EApplicatorApplyTarget> _namedApplicatorTarget;

	[Description( "Выбрать цель аппликатора (аналогично полю applyTarget аппликатора)" )]
	public EApplicatorApplyTarget selectTarget { get { return _selectTarget.Get(); } set { _selectTarget.Set( value ); } }

	[Description( "Если не пусто: найти аппликатор у цели, заданной selectTarget и выбрать его цель namedApplicatorTarget" )]
	public string applicatorName { get { return _applicatorName.Get(); } set { _applicatorName.Set( value ); } }

	[Description( "Выбрать n-й по счету аппликатор с именем applicatorName (если applicatorName не пусто)" )]
	public int applicatorIndex { get { return _applicatorIndex.Get(); } set { _applicatorIndex.Set( value ); } }

	[Description( "Выбрать цель именованного аппликатора (если applicatorName не пусто)" )]
	public EApplicatorApplyTarget namedApplicatorTarget { get { return _namedApplicatorTarget.Get(); } set { _namedApplicatorTarget.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SelectApplicatorTarget>(owner);
		_selectTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_applicatorName = new UndoRedo<string>( owner, string.Empty );
		_applicatorIndex = new UndoRedo<int>( owner, 0 );
		_namedApplicatorTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		___parent.Changed += FireChangedEvent;
		_selectTarget.Changed += FireChangedEvent;
		_applicatorName.Changed += FireChangedEvent;
		_applicatorIndex.Changed += FireChangedEvent;
		_namedApplicatorTarget.Changed += FireChangedEvent;
	}

	public SelectApplicatorTarget()
	{
		Initialize( this );
	}
	private void AssignSelf( SelectApplicatorTarget source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SelectApplicatorTarget" );
		selectTarget = source.selectTarget;
		applicatorName = source.applicatorName;
		applicatorIndex = source.applicatorIndex;
		namedApplicatorTarget = source.namedApplicatorTarget;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SelectApplicatorTarget source = _source as SelectApplicatorTarget;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SelectApplicatorTarget" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SelectApplicatorTarget newParent = rawParent == null ? null : rawParent.Get<SelectApplicatorTarget>();
		if ( newParent == null && _newParent is SelectApplicatorTarget )
			newParent = _newParent as SelectApplicatorTarget;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_selectTarget.SetParent( newParent == null ? null : newParent._selectTarget );
		_applicatorName.SetParent( newParent == null ? null : newParent._applicatorName );
		_applicatorIndex.SetParent( newParent == null ? null : newParent._applicatorIndex );
		_namedApplicatorTarget.SetParent( newParent == null ? null : newParent._namedApplicatorTarget );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_selectTarget.Reset();
		_applicatorName.Reset();
		_applicatorIndex.Reset();
		_namedApplicatorTarget.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_selectTarget.IsDerivedFromParent()
			&& _applicatorName.IsDerivedFromParent()
			&& _applicatorIndex.IsDerivedFromParent()
			&& _namedApplicatorTarget.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "selectTarget" )
			_selectTarget.Reset();
		else if ( fieldName == "applicatorName" )
			_applicatorName.Reset();
		else if ( fieldName == "applicatorIndex" )
			_applicatorIndex.Reset();
		else if ( fieldName == "namedApplicatorTarget" )
			_namedApplicatorTarget.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "selectTarget" )
			return _selectTarget.IsDerivedFromParent();
		if ( fieldName == "applicatorName" )
			return _applicatorName.IsDerivedFromParent();
		if ( fieldName == "applicatorIndex" )
			return _applicatorIndex.IsDerivedFromParent();
		if ( fieldName == "namedApplicatorTarget" )
			return _namedApplicatorTarget.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplAdvancedSummonSetTarget", "PFAdvancedSummon.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x15D320C1)]
[UseTypeName("APLR")]
public class SetAdvancedSummonTargetApplicator : BaseApplicator
{
	private UndoRedoDBPtr<SetAdvancedSummonTargetApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SetAdvancedSummonTargetApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SetAdvancedSummonTargetApplicator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public SetAdvancedSummonTargetApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SetAdvancedSummonTargetApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SetAdvancedSummonTargetApplicator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SetAdvancedSummonTargetApplicator source = _source as SetAdvancedSummonTargetApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SetAdvancedSummonTargetApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SetAdvancedSummonTargetApplicator newParent = rawParent == null ? null : rawParent.Get<SetAdvancedSummonTargetApplicator>();
		if ( newParent == null && _newParent is SetAdvancedSummonTargetApplicator )
			newParent = _newParent as SetAdvancedSummonTargetApplicator;
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

[FactoryImpl("Create", "NWorld::PFApplSetTimescale", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x15CBF400)]
[UseTypeName("APLR")]
public class SetTimescaleApplicator : BaseApplicator
{
	private UndoRedoDBPtr<SetTimescaleApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SetTimescaleApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _desiredTimescale;

	public float desiredTimescale { get { return _desiredTimescale.Get(); } set { _desiredTimescale.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SetTimescaleApplicator>(owner);
		_desiredTimescale = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_desiredTimescale.Changed += FireChangedEvent;
	}

	public SetTimescaleApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SetTimescaleApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SetTimescaleApplicator" );
		desiredTimescale = source.desiredTimescale;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SetTimescaleApplicator source = _source as SetTimescaleApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SetTimescaleApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SetTimescaleApplicator newParent = rawParent == null ? null : rawParent.Get<SetTimescaleApplicator>();
		if ( newParent == null && _newParent is SetTimescaleApplicator )
			newParent = _newParent as SetTimescaleApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_desiredTimescale.SetParent( newParent == null ? null : newParent._desiredTimescale );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_desiredTimescale.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_desiredTimescale.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "desiredTimescale" )
			_desiredTimescale.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "desiredTimescale" )
			return _desiredTimescale.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplShift", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x1E726440)]
[UseTypeName("APLR")]
public class ShiftApplicator : BaseApplicator
{
	private UndoRedoDBPtr<ShiftApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ShiftApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _shiftTarget;
	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;

	[Description( "Target to shift to" )]
	public EApplicatorApplyTarget shiftTarget { get { return _shiftTarget.Get(); } set { _shiftTarget.Set( value ); } }

	[Description( "Targets selector" )]
	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ShiftApplicator>(owner);
		_shiftTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_shiftTarget.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public ShiftApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ShiftApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ShiftApplicator" );
		shiftTarget = source.shiftTarget;
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ShiftApplicator source = _source as ShiftApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ShiftApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ShiftApplicator newParent = rawParent == null ? null : rawParent.Get<ShiftApplicator>();
		if ( newParent == null && _newParent is ShiftApplicator )
			newParent = _newParent as ShiftApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_shiftTarget.SetParent( newParent == null ? null : newParent._shiftTarget );
		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_shiftTarget.Reset();
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_shiftTarget.IsDerivedFromParent()
			&& _targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "shiftTarget" )
			_shiftTarget.Reset();
		else if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "shiftTarget" )
			return _shiftTarget.IsDerivedFromParent();
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFShopTargetSelector", "PFTargetSelector.h")]
[TypeId(0x0F756BC0)]
[UseTypeName("TGSL")]
public class ShopTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<ShopTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<ShopTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _secret;

	public bool secret { get { return _secret.Get(); } set { _secret.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ShopTargetSelector>(owner);
		_secret = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_secret.Changed += FireChangedEvent;
	}

	public ShopTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( ShopTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ShopTargetSelector" );
		secret = source.secret;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ShopTargetSelector source = _source as ShopTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ShopTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ShopTargetSelector newParent = rawParent == null ? null : rawParent.Get<ShopTargetSelector>();
		if ( newParent == null && _newParent is ShopTargetSelector )
			newParent = _newParent as ShopTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_secret.SetParent( newParent == null ? null : newParent._secret );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_secret.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_secret.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "secret" )
			_secret.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "secret" )
			return _secret.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFComparingTargetSelector", "PFTargetSelector.h")]
[TypeId(0xE776B440)]
[UseTypeName("TGSL")]
public class ComparingTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<ComparingTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<ComparingTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;
	private ExecutableFloatString _referenceValue;
	private ExecutableFloatString _valueToCompare;

	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Опорное значение" )]
	public ExecutableFloatString referenceValue { get { return _referenceValue; } set { _referenceValue.Assign( value ); } }

	[Description( "Значение, которое будет сравниваться с опорным" )]
	public ExecutableFloatString valueToCompare { get { return _valueToCompare; } set { _valueToCompare.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ComparingTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		ExecutableFloatString __referenceValue = new ExecutableFloatString(); // Construct default object for referenceValue
		__referenceValue.sString = "0.0f";
		_referenceValue = new ExecutableFloatString( owner, __referenceValue );
		ExecutableFloatString __valueToCompare = new ExecutableFloatString(); // Construct default object for valueToCompare
		__valueToCompare.sString = "0.0f";
		_valueToCompare = new ExecutableFloatString( owner, __valueToCompare );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_referenceValue.Changed += FireChangedEvent;
		_valueToCompare.Changed += FireChangedEvent;
	}

	public ComparingTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( ComparingTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ComparingTargetSelector" );
		targetSelector = source.targetSelector;
		referenceValue = source.referenceValue;
		valueToCompare = source.valueToCompare;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ComparingTargetSelector source = _source as ComparingTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ComparingTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ComparingTargetSelector newParent = rawParent == null ? null : rawParent.Get<ComparingTargetSelector>();
		if ( newParent == null && _newParent is ComparingTargetSelector )
			newParent = _newParent as ComparingTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_referenceValue.SetParent( newParent == null ? null : newParent._referenceValue );
		_valueToCompare.SetParent( newParent == null ? null : newParent._valueToCompare );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_referenceValue.Reset();
		_valueToCompare.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _referenceValue.IsDerivedFromParent()
			&& _valueToCompare.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "referenceValue" )
			_referenceValue.Reset();
		else if ( fieldName == "valueToCompare" )
			_valueToCompare.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "referenceValue" )
			return _referenceValue.IsDerivedFromParent();
		if ( fieldName == "valueToCompare" )
			return _valueToCompare.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x2C5CCAC0)]
[UseTypeName("ATCK")]
public class BaseAttack : Ability
{
	private UndoRedoDBPtr<BaseAttack> ___parent;
	[HideInOutliner]
	public new DBPtr<BaseAttack> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _isMelee;

	[Description( "Считать автоатаку милишной" )]
	public bool isMelee { get { return _isMelee.Get(); } set { _isMelee.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BaseAttack>(owner);
		_isMelee = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_isMelee.Changed += FireChangedEvent;
	}

	public BaseAttack()
	{
		Initialize( this );
	}
	private void AssignSelf( BaseAttack source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BaseAttack" );
		isMelee = source.isMelee;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BaseAttack source = _source as BaseAttack;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BaseAttack" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BaseAttack newParent = rawParent == null ? null : rawParent.Get<BaseAttack>();
		if ( newParent == null && _newParent is BaseAttack )
			newParent = _newParent as BaseAttack;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_isMelee.SetParent( newParent == null ? null : newParent._isMelee );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_isMelee.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_isMelee.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "isMelee" )
			_isMelee.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "isMelee" )
			return _isMelee.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Create", "NWorld::PFApplSpell", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E677240)]
[UseTypeName("APLR")]
public class SpellApplicator : BaseApplicator
{
	private UndoRedoDBPtr<SpellApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SpellApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;
	private UndoRedo<EApplicatorApplyTarget> _spellTarget;
	private UndoRedoDBPtr<Spell> _spell;

	[Description( "Targets selector" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Target to spell (works only if no target selector used)" )]
	public EApplicatorApplyTarget spellTarget { get { return _spellTarget.Get(); } set { _spellTarget.Set( value ); } }

	[Description( "Spell that will be applied to the targets" )]
	public DBPtr<Spell> spell { get { return _spell.Get(); } set { _spell.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SpellApplicator>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		_spellTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_spell = new UndoRedoDBPtr<Spell>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_spellTarget.Changed += FireChangedEvent;
		_spell.Changed += FireChangedEvent;
	}

	public SpellApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SpellApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SpellApplicator" );
		targetSelector = source.targetSelector;
		spellTarget = source.spellTarget;
		spell = source.spell;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SpellApplicator source = _source as SpellApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpellApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SpellApplicator newParent = rawParent == null ? null : rawParent.Get<SpellApplicator>();
		if ( newParent == null && _newParent is SpellApplicator )
			newParent = _newParent as SpellApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_spellTarget.SetParent( newParent == null ? null : newParent._spellTarget );
		_spell.SetParent( newParent == null ? null : newParent._spell );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_spellTarget.Reset();
		_spell.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _spellTarget.IsDerivedFromParent()
			&& _spell.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "spellTarget" )
			_spellTarget.Reset();
		else if ( fieldName == "spell" )
			_spell.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "spellTarget" )
			return _spellTarget.IsDerivedFromParent();
		if ( fieldName == "spell" )
			return _spell.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplSpellPeriodically", "PFApplHelper.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B08)]
[UseTypeName("APLR")]
public class SpellPeriodicallyApplicator : BuffApplicator
{
	private UndoRedoDBPtr<SpellPeriodicallyApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SpellPeriodicallyApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _period;
	private ExecutableFloatString _startOffset;
	private UndoRedo<EScaleCalculationMode> _scaleMode;
	private UndoRedoDBPtr<TargetSelector> _targetSelector;
	private UndoRedoDBPtr<Spell> _spell;

	[Description( "Period of time (in sec)" )]
	public ExecutableFloatString period { get { return _period; } set { _period.Assign( value ); } }

	[Description( "Start offset before first strike (in sec)" )]
	public ExecutableFloatString startOffset { get { return _startOffset; } set { _startOffset.Assign( value ); } }

	[Description( "The mode of scale calculation" )]
	public EScaleCalculationMode scaleMode { get { return _scaleMode.Get(); } set { _scaleMode.Set( value ); } }

	[Description( "Targets selector" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Spell that will be cast on the target of applicator every 'period' of time" )]
	public DBPtr<Spell> spell { get { return _spell.Get(); } set { _spell.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SpellPeriodicallyApplicator>(owner);
		ExecutableFloatString __period = new ExecutableFloatString(); // Construct default object for period
		__period.sString = "0.0f";
		_period = new ExecutableFloatString( owner, __period );
		ExecutableFloatString __startOffset = new ExecutableFloatString(); // Construct default object for startOffset
		__startOffset.sString = "0.0f";
		_startOffset = new ExecutableFloatString( owner, __startOffset );
		_scaleMode = new UndoRedo<EScaleCalculationMode>( owner, EScaleCalculationMode.ScaleIsCount );
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		_spell = new UndoRedoDBPtr<Spell>( owner );
		___parent.Changed += FireChangedEvent;
		_period.Changed += FireChangedEvent;
		_startOffset.Changed += FireChangedEvent;
		_scaleMode.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_spell.Changed += FireChangedEvent;
	}

	public SpellPeriodicallyApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SpellPeriodicallyApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SpellPeriodicallyApplicator" );
		period = source.period;
		startOffset = source.startOffset;
		scaleMode = source.scaleMode;
		targetSelector = source.targetSelector;
		spell = source.spell;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SpellPeriodicallyApplicator source = _source as SpellPeriodicallyApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpellPeriodicallyApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SpellPeriodicallyApplicator newParent = rawParent == null ? null : rawParent.Get<SpellPeriodicallyApplicator>();
		if ( newParent == null && _newParent is SpellPeriodicallyApplicator )
			newParent = _newParent as SpellPeriodicallyApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_period.SetParent( newParent == null ? null : newParent._period );
		_startOffset.SetParent( newParent == null ? null : newParent._startOffset );
		_scaleMode.SetParent( newParent == null ? null : newParent._scaleMode );
		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_spell.SetParent( newParent == null ? null : newParent._spell );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_period.Reset();
		_startOffset.Reset();
		_scaleMode.Reset();
		_targetSelector.Reset();
		_spell.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_period.IsDerivedFromParent()
			&& _startOffset.IsDerivedFromParent()
			&& _scaleMode.IsDerivedFromParent()
			&& _targetSelector.IsDerivedFromParent()
			&& _spell.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "period" )
			_period.Reset();
		else if ( fieldName == "startOffset" )
			_startOffset.Reset();
		else if ( fieldName == "scaleMode" )
			_scaleMode.Reset();
		else if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "spell" )
			_spell.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "period" )
			return _period.IsDerivedFromParent();
		if ( fieldName == "startOffset" )
			return _startOffset.IsDerivedFromParent();
		if ( fieldName == "scaleMode" )
			return _scaleMode.IsDerivedFromParent();
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "spell" )
			return _spell.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplSpellPeriodicallyVisual", "PFApplHelper.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E6CF400)]
[UseTypeName("APLR")]
public class SpellPeriodicallyVisualApplicator : SpellPeriodicallyApplicator
{
	private UndoRedoDBPtr<SpellPeriodicallyVisualApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SpellPeriodicallyVisualApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _attackTimeOffset;

	[Description( "Period of time (in sec)" )]
	public ExecutableFloatString attackTimeOffset { get { return _attackTimeOffset; } set { _attackTimeOffset.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SpellPeriodicallyVisualApplicator>(owner);
		ExecutableFloatString __attackTimeOffset = new ExecutableFloatString(); // Construct default object for attackTimeOffset
		__attackTimeOffset.sString = "0.0f";
		_attackTimeOffset = new ExecutableFloatString( owner, __attackTimeOffset );
		___parent.Changed += FireChangedEvent;
		_attackTimeOffset.Changed += FireChangedEvent;
	}

	public SpellPeriodicallyVisualApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SpellPeriodicallyVisualApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SpellPeriodicallyVisualApplicator" );
		attackTimeOffset = source.attackTimeOffset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SpellPeriodicallyVisualApplicator source = _source as SpellPeriodicallyVisualApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpellPeriodicallyVisualApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SpellPeriodicallyVisualApplicator newParent = rawParent == null ? null : rawParent.Get<SpellPeriodicallyVisualApplicator>();
		if ( newParent == null && _newParent is SpellPeriodicallyVisualApplicator )
			newParent = _newParent as SpellPeriodicallyVisualApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_attackTimeOffset.SetParent( newParent == null ? null : newParent._attackTimeOffset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_attackTimeOffset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_attackTimeOffset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "attackTimeOffset" )
			_attackTimeOffset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "attackTimeOffset" )
			return _attackTimeOffset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplSpellProbability", "PFApplHelper.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0BFD)]
[UseTypeName("APLR")]
public class SpellProbabilityApplicator : BaseApplicator
{
	private UndoRedoDBPtr<SpellProbabilityApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SpellProbabilityApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _probability;
	private UndoRedoDBPtr<Spell> _spell;
	private UndoRedoDBPtr<Spell> _spellIfFailed;

	[Description( "Probability of a spell (within 0..100 interval)" )]
	public ExecutableFloatString probability { get { return _probability; } set { _probability.Assign( value ); } }

	[Description( "Spell that will be applied to the target in the case of passing probability check" )]
	public DBPtr<Spell> spell { get { return _spell.Get(); } set { _spell.Set( value ); } }

	[Description( "Spell that will be applied to the target in the case of failing probability check" )]
	public DBPtr<Spell> spellIfFailed { get { return _spellIfFailed.Get(); } set { _spellIfFailed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SpellProbabilityApplicator>(owner);
		ExecutableFloatString __probability = new ExecutableFloatString(); // Construct default object for probability
		__probability.sString = "100.0";
		_probability = new ExecutableFloatString( owner, __probability );
		_spell = new UndoRedoDBPtr<Spell>( owner );
		_spellIfFailed = new UndoRedoDBPtr<Spell>( owner );
		___parent.Changed += FireChangedEvent;
		_probability.Changed += FireChangedEvent;
		_spell.Changed += FireChangedEvent;
		_spellIfFailed.Changed += FireChangedEvent;
	}

	public SpellProbabilityApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SpellProbabilityApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SpellProbabilityApplicator" );
		probability = source.probability;
		spell = source.spell;
		spellIfFailed = source.spellIfFailed;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SpellProbabilityApplicator source = _source as SpellProbabilityApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpellProbabilityApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SpellProbabilityApplicator newParent = rawParent == null ? null : rawParent.Get<SpellProbabilityApplicator>();
		if ( newParent == null && _newParent is SpellProbabilityApplicator )
			newParent = _newParent as SpellProbabilityApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_probability.SetParent( newParent == null ? null : newParent._probability );
		_spell.SetParent( newParent == null ? null : newParent._spell );
		_spellIfFailed.SetParent( newParent == null ? null : newParent._spellIfFailed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_probability.Reset();
		_spell.Reset();
		_spellIfFailed.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_probability.IsDerivedFromParent()
			&& _spell.IsDerivedFromParent()
			&& _spellIfFailed.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "probability" )
			_probability.Reset();
		else if ( fieldName == "spell" )
			_spell.Reset();
		else if ( fieldName == "spellIfFailed" )
			_spellIfFailed.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "probability" )
			return _probability.IsDerivedFromParent();
		if ( fieldName == "spell" )
			return _spell.IsDerivedFromParent();
		if ( fieldName == "spellIfFailed" )
			return _spellIfFailed.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplSpellSwitch", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0E674B40)]
[UseTypeName("APLR")]
public class SpellSwitchApplicator : BaseApplicator
{
	private UndoRedoDBPtr<SpellSwitchApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SpellSwitchApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableIntString _activeSpellIndex;
	private UndoRedo<bool> _dontUseDispatches;
	private UndoRedoAssignableList<DBPtr<Spell>> _spells;

	[Description( "Index of default(active) spell" )]
	public ExecutableIntString activeSpellIndex { get { return _activeSpellIndex; } set { _activeSpellIndex.Assign( value ); } }

	[Description( "Don't use spell dispatches, apply instantly" )]
	public bool dontUseDispatches { get { return _dontUseDispatches.Get(); } set { _dontUseDispatches.Set( value ); } }

	[Description( "Spell list to select active spell from." )]
	public libdb.IChangeableList<DBPtr<Spell>> spells { get { return _spells; } set { _spells.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SpellSwitchApplicator>(owner);
		_activeSpellIndex = new ExecutableIntString( owner );
		_dontUseDispatches = new UndoRedo<bool>( owner, false );
		_spells = new UndoRedoAssignableList<DBPtr<Spell>>( owner );
		___parent.Changed += FireChangedEvent;
		_activeSpellIndex.Changed += FireChangedEvent;
		_dontUseDispatches.Changed += FireChangedEvent;
		_spells.Changed += FireChangedEvent;
	}

	public SpellSwitchApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SpellSwitchApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SpellSwitchApplicator" );
		activeSpellIndex = source.activeSpellIndex;
		dontUseDispatches = source.dontUseDispatches;
		spells = source.spells;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SpellSwitchApplicator source = _source as SpellSwitchApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpellSwitchApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SpellSwitchApplicator newParent = rawParent == null ? null : rawParent.Get<SpellSwitchApplicator>();
		if ( newParent == null && _newParent is SpellSwitchApplicator )
			newParent = _newParent as SpellSwitchApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_activeSpellIndex.SetParent( newParent == null ? null : newParent._activeSpellIndex );
		_dontUseDispatches.SetParent( newParent == null ? null : newParent._dontUseDispatches );
		_spells.SetParent( newParent == null ? null : newParent._spells );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_activeSpellIndex.Reset();
		_dontUseDispatches.Reset();
		_spells.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_activeSpellIndex.IsDerivedFromParent()
			&& _dontUseDispatches.IsDerivedFromParent()
			&& _spells.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "activeSpellIndex" )
			_activeSpellIndex.Reset();
		else if ( fieldName == "dontUseDispatches" )
			_dontUseDispatches.Reset();
		else if ( fieldName == "spells" )
			_spells.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "activeSpellIndex" )
			return _activeSpellIndex.IsDerivedFromParent();
		if ( fieldName == "dontUseDispatches" )
			return _dontUseDispatches.IsDerivedFromParent();
		if ( fieldName == "spells" )
			return _spells.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplStatMod", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B03)]
[UseTypeName("APLR")]
public class StatModApplicator : BuffApplicator
{
	private UndoRedoDBPtr<StatModApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<StatModApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Modifier _modifier;
	private UndoRedo<bool> _dontUpdate;
	private UndoRedo<string> _statModName;
	private UndoRedo<EStatConstraint> _constraint;

	[Category( "StatModifier" )]
	public Modifier modifier { get { return _modifier; } set { _modifier.Assign( value ); } }

	[Description( "Don't update modifier" )]
	public bool dontUpdate { get { return _dontUpdate.Get(); } set { _dontUpdate.Set( value ); } }

	[Description( "Name for resolving constants while merging statuses in UI, must be same as constant name used in modifier and tooltip" )]
	public string statModName { get { return _statModName.Get(); } set { _statModName.Set( value ); } }

	[Description( "Calculated value (baseValue * multValue + addValue) becomes a constraint" )]
	public EStatConstraint constraint { get { return _constraint.Get(); } set { _constraint.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StatModApplicator>(owner);
		_modifier = new Modifier( owner );
		_dontUpdate = new UndoRedo<bool>( owner, false );
		_statModName = new UndoRedo<string>( owner, string.Empty );
		_constraint = new UndoRedo<EStatConstraint>( owner, EStatConstraint.None );
		___parent.Changed += FireChangedEvent;
		_modifier.Changed += FireChangedEvent;
		_dontUpdate.Changed += FireChangedEvent;
		_statModName.Changed += FireChangedEvent;
		_constraint.Changed += FireChangedEvent;
	}

	public StatModApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( StatModApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StatModApplicator" );
		modifier = source.modifier;
		dontUpdate = source.dontUpdate;
		statModName = source.statModName;
		constraint = source.constraint;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StatModApplicator source = _source as StatModApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatModApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StatModApplicator newParent = rawParent == null ? null : rawParent.Get<StatModApplicator>();
		if ( newParent == null && _newParent is StatModApplicator )
			newParent = _newParent as StatModApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_modifier.SetParent( newParent == null ? null : newParent._modifier );
		_dontUpdate.SetParent( newParent == null ? null : newParent._dontUpdate );
		_statModName.SetParent( newParent == null ? null : newParent._statModName );
		_constraint.SetParent( newParent == null ? null : newParent._constraint );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_modifier.Reset();
		_dontUpdate.Reset();
		_statModName.Reset();
		_constraint.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_modifier.IsDerivedFromParent()
			&& _dontUpdate.IsDerivedFromParent()
			&& _statModName.IsDerivedFromParent()
			&& _constraint.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "modifier" )
			_modifier.Reset();
		else if ( fieldName == "dontUpdate" )
			_dontUpdate.Reset();
		else if ( fieldName == "statModName" )
			_statModName.Reset();
		else if ( fieldName == "constraint" )
			_constraint.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "modifier" )
			return _modifier.IsDerivedFromParent();
		if ( fieldName == "dontUpdate" )
			return _dontUpdate.IsDerivedFromParent();
		if ( fieldName == "statModName" )
			return _statModName.IsDerivedFromParent();
		if ( fieldName == "constraint" )
			return _constraint.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(2)]
[FactoryImpl("Create", "NWorld::PFApplStatus", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E688BC0)]
[UseTypeName("APLR")]
public class StatusApplicator : BuffApplicator
{
	private UndoRedoDBPtr<StatusApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<StatusApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _name;
	private TextRef _description;
	private UndoRedoDBPtr<Texture> _image;
	private UndoRedo<int> _stackCount;
	private UndoRedo<EStackingRule> _stackableAcrossUnits;
	private UndoRedo<int> _power;
	private UndoRedo<EDispellPriority> _dispellPriority;
	private UndoRedo<EStopBehaviour> _stopBehaviour;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicators;
	private UndoRedoDBPtr<ApplicatorsList> _unstackableWith;
	private ExecutableIntString _customCounter;
	private ExecutableFloatString _customProgress;
	private UndoRedo<int> _statusPosition;
	private UndoRedo<EStatusFlags> _flags;

	[Description( "Name of status" )]
	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	[Description( "Description of status" )]
	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	[Description( "UI texture that will be shown in status bar" )]
	public DBPtr<Texture> image { get { return _image.Get(); } set { _image.Set( value ); } }

	[Description( "Count of stacking of status with the same one" )]
	public int stackCount { get { return _stackCount.Get(); } set { _stackCount.Set( value ); } }

	[Description( "How status stacks with the same status from other unit" )]
	public EStackingRule stackableAcrossUnits { get { return _stackableAcrossUnits.Get(); } set { _stackableAcrossUnits.Set( value ); } }

	[Description( "When nonstackable statuses collide, status with highest power survives" )]
	public int power { get { return _power.Get(); } set { _power.Set( value ); } }

	[Description( "The higher dispell priority is, the earlier effect will be dispelled" )]
	public EDispellPriority dispellPriority { get { return _dispellPriority.Get(); } set { _dispellPriority.Set( value ); } }

	[Description( "Поведение статус-аппликатора. Остановиться по времени, остановиться, когда ребенок остановиться, остановиться после остановки всех детей." )]
	public EStopBehaviour stopBehaviour { get { return _stopBehaviour.Get(); } set { _stopBehaviour.Set( value ); } }

	[Description( "List of applicators that will be applied to changed unit" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	[Description( "List of unstackable applicators" )]
	public DBPtr<ApplicatorsList> unstackableWith { get { return _unstackableWith.Get(); } set { _unstackableWith.Set( value ); } }

	[Description( "Custom stack counter" )]
	public ExecutableIntString customCounter { get { return _customCounter; } set { _customCounter.Assign( value ); } }

	[Description( "Custom progress" )]
	public ExecutableFloatString customProgress { get { return _customProgress; } set { _customProgress.Assign( value ); } }

	[Description( "UI status icon position" )]
	public int statusPosition { get { return _statusPosition.Get(); } set { _statusPosition.Set( value ); } }

	public EStatusFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StatusApplicator>(owner);
		_name = new TextRef( owner, new TextRef() );
		_description = new TextRef( owner, new TextRef() );
		_image = new UndoRedoDBPtr<Texture>( owner );
		_stackCount = new UndoRedo<int>( owner, 0 );
		_stackableAcrossUnits = new UndoRedo<EStackingRule>( owner, EStackingRule.Unstackable );
		_power = new UndoRedo<int>( owner, 0 );
		_dispellPriority = new UndoRedo<EDispellPriority>( owner, EDispellPriority.Medium );
		_stopBehaviour = new UndoRedo<EStopBehaviour>( owner, EStopBehaviour.StopByTime );
		_applicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		_unstackableWith = new UndoRedoDBPtr<ApplicatorsList>( owner );
		_customCounter = new ExecutableIntString( owner );
		ExecutableFloatString __customProgress = new ExecutableFloatString(); // Construct default object for customProgress
		__customProgress.sString = "-1.0";
		_customProgress = new ExecutableFloatString( owner, __customProgress );
		_statusPosition = new UndoRedo<int>( owner, 0 );
		_flags = new UndoRedo<EStatusFlags>( owner, EStatusFlags.None );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_image.Changed += FireChangedEvent;
		_stackCount.Changed += FireChangedEvent;
		_stackableAcrossUnits.Changed += FireChangedEvent;
		_power.Changed += FireChangedEvent;
		_dispellPriority.Changed += FireChangedEvent;
		_stopBehaviour.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
		_unstackableWith.Changed += FireChangedEvent;
		_customCounter.Changed += FireChangedEvent;
		_customProgress.Changed += FireChangedEvent;
		_statusPosition.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
	}

	public StatusApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( StatusApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StatusApplicator" );
		name = source.name;
		description = source.description;
		image = source.image;
		stackCount = source.stackCount;
		stackableAcrossUnits = source.stackableAcrossUnits;
		power = source.power;
		dispellPriority = source.dispellPriority;
		stopBehaviour = source.stopBehaviour;
		applicators = source.applicators;
		unstackableWith = source.unstackableWith;
		customCounter = source.customCounter;
		customProgress = source.customProgress;
		statusPosition = source.statusPosition;
		flags = source.flags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StatusApplicator source = _source as StatusApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatusApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StatusApplicator newParent = rawParent == null ? null : rawParent.Get<StatusApplicator>();
		if ( newParent == null && _newParent is StatusApplicator )
			newParent = _newParent as StatusApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		_description.SetParent( newParent == null ? null : newParent._description );
		_image.SetParent( newParent == null ? null : newParent._image );
		_stackCount.SetParent( newParent == null ? null : newParent._stackCount );
		_stackableAcrossUnits.SetParent( newParent == null ? null : newParent._stackableAcrossUnits );
		_power.SetParent( newParent == null ? null : newParent._power );
		_dispellPriority.SetParent( newParent == null ? null : newParent._dispellPriority );
		_stopBehaviour.SetParent( newParent == null ? null : newParent._stopBehaviour );
		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		_unstackableWith.SetParent( newParent == null ? null : newParent._unstackableWith );
		_customCounter.SetParent( newParent == null ? null : newParent._customCounter );
		_customProgress.SetParent( newParent == null ? null : newParent._customProgress );
		_statusPosition.SetParent( newParent == null ? null : newParent._statusPosition );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		_description.Reset();
		_image.Reset();
		_stackCount.Reset();
		_stackableAcrossUnits.Reset();
		_power.Reset();
		_dispellPriority.Reset();
		_stopBehaviour.Reset();
		_applicators.Reset();
		_unstackableWith.Reset();
		_customCounter.Reset();
		_customProgress.Reset();
		_statusPosition.Reset();
		_flags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _image.IsDerivedFromParent()
			&& _stackCount.IsDerivedFromParent()
			&& _stackableAcrossUnits.IsDerivedFromParent()
			&& _power.IsDerivedFromParent()
			&& _dispellPriority.IsDerivedFromParent()
			&& _stopBehaviour.IsDerivedFromParent()
			&& _applicators.IsDerivedFromParent()
			&& _unstackableWith.IsDerivedFromParent()
			&& _customCounter.IsDerivedFromParent()
			&& _customProgress.IsDerivedFromParent()
			&& _statusPosition.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "image" )
			_image.Reset();
		else if ( fieldName == "stackCount" )
			_stackCount.Reset();
		else if ( fieldName == "stackableAcrossUnits" )
			_stackableAcrossUnits.Reset();
		else if ( fieldName == "power" )
			_power.Reset();
		else if ( fieldName == "dispellPriority" )
			_dispellPriority.Reset();
		else if ( fieldName == "stopBehaviour" )
			_stopBehaviour.Reset();
		else if ( fieldName == "applicators" )
			_applicators.Reset();
		else if ( fieldName == "unstackableWith" )
			_unstackableWith.Reset();
		else if ( fieldName == "customCounter" )
			_customCounter.Reset();
		else if ( fieldName == "customProgress" )
			_customProgress.Reset();
		else if ( fieldName == "statusPosition" )
			_statusPosition.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
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
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "image" )
			return _image.IsDerivedFromParent();
		if ( fieldName == "stackCount" )
			return _stackCount.IsDerivedFromParent();
		if ( fieldName == "stackableAcrossUnits" )
			return _stackableAcrossUnits.IsDerivedFromParent();
		if ( fieldName == "power" )
			return _power.IsDerivedFromParent();
		if ( fieldName == "dispellPriority" )
			return _dispellPriority.IsDerivedFromParent();
		if ( fieldName == "stopBehaviour" )
			return _stopBehaviour.IsDerivedFromParent();
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		if ( fieldName == "unstackableWith" )
			return _unstackableWith.IsDerivedFromParent();
		if ( fieldName == "customCounter" )
			return _customCounter.IsDerivedFromParent();
		if ( fieldName == "customProgress" )
			return _customProgress.IsDerivedFromParent();
		if ( fieldName == "statusPosition" )
			return _statusPosition.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(5)]
[FactoryImpl("Create", "NWorld::PFApplSummon", "PFApplSummon.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F730BC3)]
[UseTypeName("APLR")]
public class SummonApplicator : BaseApplicator
{
	private UndoRedoDBPtr<SummonApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<SummonApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<SummonSource> _summonSource;
	private UndoRedoAssignableList<DBPtr<Summoned>> _summonedUnits;
	private ExecutableIntString _summonedUnitIndex;
	private ExecutableIntString _summonedUnitsCount;
	private UndoRedoDBPtr<SummonBehaviourBase> _behaviour;
	private UndoRedoDBPtr<SingleTargetSelector> _placeSelector;
	private UndoRedo<SummonPlaceMode> _placeMode;
	private ExecutableFloatString _lifeTime;
	private UndoRedoAssignableList<DBPtr<BaseApplicator>> _applicators;
	private UndoRedo<ESummonFlags> _flags;
	private SpawnStats _spawnStats;
	private ExecutableFloatString _takeModDmg;
	private UndoRedo<ESpellTarget> _takeTypeUnit;
	private UndoRedo<bool> _openWarFog;
	private ExecutableFloatString _unsummonSortCriterion;
	private UndoRedo<string> _summonGroupName;

	[Description( "Какого крипа призываем — из списка или клона цели" )]
	public SummonSource summonSource { get { return _summonSource.Get(); } set { _summonSource.Set( value ); } }

	[Description( "[ByApplicator] Units array that will be created (one of them)" )]
	public libdb.IChangeableList<DBPtr<Summoned>> summonedUnits { get { return _summonedUnits; } set { _summonedUnits.Assign( value ); } }

	[Description( "[ByApplicator] Unit that will be created (index in array)" )]
	public ExecutableIntString summonedUnitIndex { get { return _summonedUnitIndex; } set { _summonedUnitIndex.Assign( value ); } }

	[Description( "How many units will be summoned" )]
	public ExecutableIntString summonedUnitsCount { get { return _summonedUnitsCount; } set { _summonedUnitsCount.Assign( value ); } }

	[Description( "Summoned unit behaviour" )]
	public DBPtr<SummonBehaviourBase> behaviour { get { return _behaviour.Get(); } set { _behaviour.Set( value ); } }

	[Description( "Summoned unit creation place" )]
	public DBPtr<SingleTargetSelector> placeSelector { get { return _placeSelector.Get(); } set { _placeSelector.Set( value ); } }

	[Description( "Summoned unit creation place source" )]
	public SummonPlaceMode placeMode { get { return _placeMode.Get(); } set { _placeMode.Set( value ); } }

	[Description( "Maximum life time of summoned unit" )]
	public ExecutableFloatString lifeTime { get { return _lifeTime; } set { _lifeTime.Assign( value ); } }

	[Description( "List of applicators that will be applied to summoned unit" )]
	public libdb.IChangeableList<DBPtr<BaseApplicator>> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	[Description( "Флаги (Является ли суммон 'важным', является ли альфа-суммоном)" )]
	public ESummonFlags flags { get { return _flags.Get(); } set { _flags.Set( value ); } }

	[Description( "Life and energy at spawn time" )]
	public SpawnStats spawnStats { get { return _spawnStats; } set { _spawnStats.Assign( value ); } }

	[Description( "Additional damage's multiplier" )]
	public ExecutableFloatString takeModDmg { get { return _takeModDmg; } set { _takeModDmg.Assign( value ); } }

	[Description( "Flags to specify targets of the takeModDmg" )]
	public ESpellTarget takeTypeUnit { get { return _takeTypeUnit.Get(); } set { _takeTypeUnit.Set( value ); } }

	[Description( "Открывать ли варфог вокруг этого юнита" )]
	public bool openWarFog { get { return _openWarFog.Get(); } set { _openWarFog.Set( value ); } }

	[Description( "Критерий по которому сортируются существующие суммоны для ансуммона лишних (с меньшими значениями). Если не используется, то оставить 0. Здесь: sender - тот кто суммонит, receiver - суммон из перебираемых" )]
	public ExecutableFloatString unsummonSortCriterion { get { return _unsummonSortCriterion; } set { _unsummonSortCriterion.Assign( value ); } }

	[Description( "Имя группы суммонов к которой приписать" )]
	public string summonGroupName { get { return _summonGroupName.Get(); } set { _summonGroupName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SummonApplicator>(owner);
		_summonSource = new UndoRedo<SummonSource>( owner, SummonSource.ByApplicator );
		_summonedUnits = new UndoRedoAssignableList<DBPtr<Summoned>>( owner );
		_summonedUnitIndex = new ExecutableIntString( owner );
		ExecutableIntString __summonedUnitsCount = new ExecutableIntString(); // Construct default object for summonedUnitsCount
		__summonedUnitsCount.sString = "1";
		_summonedUnitsCount = new ExecutableIntString( owner, __summonedUnitsCount );
		_behaviour = new UndoRedoDBPtr<SummonBehaviourBase>( owner );
		_placeSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_placeMode = new UndoRedo<SummonPlaceMode>( owner, SummonPlaceMode.ByBehaviour );
		ExecutableFloatString __lifeTime = new ExecutableFloatString(); // Construct default object for lifeTime
		__lifeTime.sString = "0.0f";
		_lifeTime = new ExecutableFloatString( owner, __lifeTime );
		_applicators = new UndoRedoAssignableList<DBPtr<BaseApplicator>>( owner );
		_flags = new UndoRedo<ESummonFlags>( owner, ESummonFlags.None );
		SpawnStats __spawnStats = new SpawnStats(); // Construct default object for spawnStats
		__spawnStats.life.sString = "-1.0";
		__spawnStats.energy.sString = "-1.0";
		_spawnStats = new SpawnStats( owner, __spawnStats );
		ExecutableFloatString __takeModDmg = new ExecutableFloatString(); // Construct default object for takeModDmg
		__takeModDmg.sString = "1.0f";
		_takeModDmg = new ExecutableFloatString( owner, __takeModDmg );
		_takeTypeUnit = new UndoRedo<ESpellTarget>( owner, ESpellTarget.VulnerableTargetsOnly | ESpellTarget.All );
		_openWarFog = new UndoRedo<bool>( owner, true );
		ExecutableFloatString __unsummonSortCriterion = new ExecutableFloatString(); // Construct default object for unsummonSortCriterion
		__unsummonSortCriterion.sString = "0.0f";
		_unsummonSortCriterion = new ExecutableFloatString( owner, __unsummonSortCriterion );
		_summonGroupName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_summonSource.Changed += FireChangedEvent;
		_summonedUnits.Changed += FireChangedEvent;
		_summonedUnitIndex.Changed += FireChangedEvent;
		_summonedUnitsCount.Changed += FireChangedEvent;
		_behaviour.Changed += FireChangedEvent;
		_placeSelector.Changed += FireChangedEvent;
		_placeMode.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
		_flags.Changed += FireChangedEvent;
		_spawnStats.Changed += FireChangedEvent;
		_takeModDmg.Changed += FireChangedEvent;
		_takeTypeUnit.Changed += FireChangedEvent;
		_openWarFog.Changed += FireChangedEvent;
		_unsummonSortCriterion.Changed += FireChangedEvent;
		_summonGroupName.Changed += FireChangedEvent;
	}

	public SummonApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( SummonApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SummonApplicator" );
		summonSource = source.summonSource;
		summonedUnits = source.summonedUnits;
		summonedUnitIndex = source.summonedUnitIndex;
		summonedUnitsCount = source.summonedUnitsCount;
		behaviour = source.behaviour;
		placeSelector = source.placeSelector;
		placeMode = source.placeMode;
		lifeTime = source.lifeTime;
		applicators = source.applicators;
		flags = source.flags;
		spawnStats = source.spawnStats;
		takeModDmg = source.takeModDmg;
		takeTypeUnit = source.takeTypeUnit;
		openWarFog = source.openWarFog;
		unsummonSortCriterion = source.unsummonSortCriterion;
		summonGroupName = source.summonGroupName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SummonApplicator source = _source as SummonApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SummonApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SummonApplicator newParent = rawParent == null ? null : rawParent.Get<SummonApplicator>();
		if ( newParent == null && _newParent is SummonApplicator )
			newParent = _newParent as SummonApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_summonSource.SetParent( newParent == null ? null : newParent._summonSource );
		_summonedUnits.SetParent( newParent == null ? null : newParent._summonedUnits );
		_summonedUnitIndex.SetParent( newParent == null ? null : newParent._summonedUnitIndex );
		_summonedUnitsCount.SetParent( newParent == null ? null : newParent._summonedUnitsCount );
		_behaviour.SetParent( newParent == null ? null : newParent._behaviour );
		_placeSelector.SetParent( newParent == null ? null : newParent._placeSelector );
		_placeMode.SetParent( newParent == null ? null : newParent._placeMode );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		_flags.SetParent( newParent == null ? null : newParent._flags );
		_spawnStats.SetParent( newParent == null ? null : newParent._spawnStats );
		_takeModDmg.SetParent( newParent == null ? null : newParent._takeModDmg );
		_takeTypeUnit.SetParent( newParent == null ? null : newParent._takeTypeUnit );
		_openWarFog.SetParent( newParent == null ? null : newParent._openWarFog );
		_unsummonSortCriterion.SetParent( newParent == null ? null : newParent._unsummonSortCriterion );
		_summonGroupName.SetParent( newParent == null ? null : newParent._summonGroupName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_summonSource.Reset();
		_summonedUnits.Reset();
		_summonedUnitIndex.Reset();
		_summonedUnitsCount.Reset();
		_behaviour.Reset();
		_placeSelector.Reset();
		_placeMode.Reset();
		_lifeTime.Reset();
		_applicators.Reset();
		_flags.Reset();
		_spawnStats.Reset();
		_takeModDmg.Reset();
		_takeTypeUnit.Reset();
		_openWarFog.Reset();
		_unsummonSortCriterion.Reset();
		_summonGroupName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_summonSource.IsDerivedFromParent()
			&& _summonedUnits.IsDerivedFromParent()
			&& _summonedUnitIndex.IsDerivedFromParent()
			&& _summonedUnitsCount.IsDerivedFromParent()
			&& _behaviour.IsDerivedFromParent()
			&& _placeSelector.IsDerivedFromParent()
			&& _placeMode.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			&& _applicators.IsDerivedFromParent()
			&& _flags.IsDerivedFromParent()
			&& _spawnStats.IsDerivedFromParent()
			&& _takeModDmg.IsDerivedFromParent()
			&& _takeTypeUnit.IsDerivedFromParent()
			&& _openWarFog.IsDerivedFromParent()
			&& _unsummonSortCriterion.IsDerivedFromParent()
			&& _summonGroupName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "summonSource" )
			_summonSource.Reset();
		else if ( fieldName == "summonedUnits" )
			_summonedUnits.Reset();
		else if ( fieldName == "summonedUnitIndex" )
			_summonedUnitIndex.Reset();
		else if ( fieldName == "summonedUnitsCount" )
			_summonedUnitsCount.Reset();
		else if ( fieldName == "behaviour" )
			_behaviour.Reset();
		else if ( fieldName == "placeSelector" )
			_placeSelector.Reset();
		else if ( fieldName == "placeMode" )
			_placeMode.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "applicators" )
			_applicators.Reset();
		else if ( fieldName == "flags" )
			_flags.Reset();
		else if ( fieldName == "spawnStats" )
			_spawnStats.Reset();
		else if ( fieldName == "takeModDmg" )
			_takeModDmg.Reset();
		else if ( fieldName == "takeTypeUnit" )
			_takeTypeUnit.Reset();
		else if ( fieldName == "openWarFog" )
			_openWarFog.Reset();
		else if ( fieldName == "unsummonSortCriterion" )
			_unsummonSortCriterion.Reset();
		else if ( fieldName == "summonGroupName" )
			_summonGroupName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "summonSource" )
			return _summonSource.IsDerivedFromParent();
		if ( fieldName == "summonedUnits" )
			return _summonedUnits.IsDerivedFromParent();
		if ( fieldName == "summonedUnitIndex" )
			return _summonedUnitIndex.IsDerivedFromParent();
		if ( fieldName == "summonedUnitsCount" )
			return _summonedUnitsCount.IsDerivedFromParent();
		if ( fieldName == "behaviour" )
			return _behaviour.IsDerivedFromParent();
		if ( fieldName == "placeSelector" )
			return _placeSelector.IsDerivedFromParent();
		if ( fieldName == "placeMode" )
			return _placeMode.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		if ( fieldName == "flags" )
			return _flags.IsDerivedFromParent();
		if ( fieldName == "spawnStats" )
			return _spawnStats.IsDerivedFromParent();
		if ( fieldName == "takeModDmg" )
			return _takeModDmg.IsDerivedFromParent();
		if ( fieldName == "takeTypeUnit" )
			return _takeTypeUnit.IsDerivedFromParent();
		if ( fieldName == "openWarFog" )
			return _openWarFog.IsDerivedFromParent();
		if ( fieldName == "unsummonSortCriterion" )
			return _unsummonSortCriterion.IsDerivedFromParent();
		if ( fieldName == "summonGroupName" )
			return _summonGroupName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryBase("Create", "NWorld::PFSummonBehaviourDataBase")]
[IndexField("comment")]
[NonTerminal]
[TypeId(0x0F730BC0)]
[UseTypeName("SBEH")]
public class SummonBehaviourBase : DBResource
{
	private UndoRedoDBPtr<SummonBehaviourBase> ___parent;
	[HideInOutliner]
	public new DBPtr<SummonBehaviourBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _comment;

	[NoCode]
	public string comment { get { return _comment.Get(); } set { _comment.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SummonBehaviourBase>(owner);
		_comment = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_comment.Changed += FireChangedEvent;
	}

	public SummonBehaviourBase()
	{
		Initialize( this );
	}
	private void AssignSelf( SummonBehaviourBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SummonBehaviourBase" );
		comment = source.comment;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SummonBehaviourBase source = _source as SummonBehaviourBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SummonBehaviourBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SummonBehaviourBase newParent = rawParent == null ? null : rawParent.Get<SummonBehaviourBase>();
		if ( newParent == null && _newParent is SummonBehaviourBase )
			newParent = _newParent as SummonBehaviourBase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_comment.SetParent( newParent == null ? null : newParent._comment );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_comment.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_comment.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "comment" )
			_comment.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "comment" )
			return _comment.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(3)]
[FactoryImpl("Create", "NWorld::PFSummonBehaviourDataCommon", "PFApplSummon.h")]
[TypeId(0x0F730BC1)]
public class SummonBehaviourCommon : SummonBehaviourBase
{
	private UndoRedoDBPtr<SummonBehaviourCommon> ___parent;
	[HideInOutliner]
	public new DBPtr<SummonBehaviourCommon> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<SummonType> _summonType;
	private ExecutableIntString _maxCount;
	private ExecutableIntString _maxThisCount;
	private UndoRedoDBPtr<UnitTargetingParameters> _targetingParams;
	private ExecutableFloatString _lashRange;
	private UndoRedo<float> _responseRange;
	private UndoRedo<float> _responseTime;

	[Description( "Group of summoned units to insert" )]
	public SummonType summonType { get { return _summonType.Get(); } set { _summonType.Set( value ); } }

	[Description( "Макс кол-во суммонов типа summonType" )]
	public ExecutableIntString maxCount { get { return _maxCount; } set { _maxCount.Assign( value ); } }

	[Description( "Макс кол-во суммонов типа указанного в аппликаторе. Должно быть не больше maxCount. Если 0, то не учитывать." )]
	public ExecutableIntString maxThisCount { get { return _maxThisCount; } set { _maxThisCount.Assign( value ); } }

	[Description( "Override targeting params" )]
	public DBPtr<UnitTargetingParameters> targetingParams { get { return _targetingParams.Get(); } set { _targetingParams.Set( value ); } }

	[Category( "Ranges" )]
	[Description( "Радиус в пределах которого саммон будет стараться находится в обычном состоянии." )]
	public ExecutableFloatString lashRange { get { return _lashRange; } set { _lashRange.Assign( value ); } }

	[Category( "Ranges" )]
	[Description( "Радиус за пределами которого команда move воспринимается саммоном как приказ к немедленному движению и игнорированию всех целей" )]
	public float responseRange { get { return _responseRange.Get(); } set { _responseRange.Set( value ); } }

	[Description( "Время в течении которого саммон бежит в указанную точку игнорируя цели." )]
	public float responseTime { get { return _responseTime.Get(); } set { _responseTime.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SummonBehaviourCommon>(owner);
		_summonType = new UndoRedo<SummonType>( owner, SummonType.Primary );
		ExecutableIntString __maxCount = new ExecutableIntString(); // Construct default object for maxCount
		__maxCount.sString = "1";
		_maxCount = new ExecutableIntString( owner, __maxCount );
		_maxThisCount = new ExecutableIntString( owner );
		_targetingParams = new UndoRedoDBPtr<UnitTargetingParameters>( owner );
		ExecutableFloatString __lashRange = new ExecutableFloatString(); // Construct default object for lashRange
		__lashRange.sString = "0.0";
		_lashRange = new ExecutableFloatString( owner, __lashRange );
		_responseRange = new UndoRedo<float>( owner, 0.0f );
		_responseTime = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_summonType.Changed += FireChangedEvent;
		_maxCount.Changed += FireChangedEvent;
		_maxThisCount.Changed += FireChangedEvent;
		_targetingParams.Changed += FireChangedEvent;
		_lashRange.Changed += FireChangedEvent;
		_responseRange.Changed += FireChangedEvent;
		_responseTime.Changed += FireChangedEvent;
	}

	public SummonBehaviourCommon()
	{
		Initialize( this );
	}
	private void AssignSelf( SummonBehaviourCommon source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SummonBehaviourCommon" );
		summonType = source.summonType;
		maxCount = source.maxCount;
		maxThisCount = source.maxThisCount;
		targetingParams = source.targetingParams;
		lashRange = source.lashRange;
		responseRange = source.responseRange;
		responseTime = source.responseTime;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SummonBehaviourCommon source = _source as SummonBehaviourCommon;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SummonBehaviourCommon" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SummonBehaviourCommon newParent = rawParent == null ? null : rawParent.Get<SummonBehaviourCommon>();
		if ( newParent == null && _newParent is SummonBehaviourCommon )
			newParent = _newParent as SummonBehaviourCommon;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_summonType.SetParent( newParent == null ? null : newParent._summonType );
		_maxCount.SetParent( newParent == null ? null : newParent._maxCount );
		_maxThisCount.SetParent( newParent == null ? null : newParent._maxThisCount );
		_targetingParams.SetParent( newParent == null ? null : newParent._targetingParams );
		_lashRange.SetParent( newParent == null ? null : newParent._lashRange );
		_responseRange.SetParent( newParent == null ? null : newParent._responseRange );
		_responseTime.SetParent( newParent == null ? null : newParent._responseTime );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_summonType.Reset();
		_maxCount.Reset();
		_maxThisCount.Reset();
		_targetingParams.Reset();
		_lashRange.Reset();
		_responseRange.Reset();
		_responseTime.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_summonType.IsDerivedFromParent()
			&& _maxCount.IsDerivedFromParent()
			&& _maxThisCount.IsDerivedFromParent()
			&& _targetingParams.IsDerivedFromParent()
			&& _lashRange.IsDerivedFromParent()
			&& _responseRange.IsDerivedFromParent()
			&& _responseTime.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "summonType" )
			_summonType.Reset();
		else if ( fieldName == "maxCount" )
			_maxCount.Reset();
		else if ( fieldName == "maxThisCount" )
			_maxThisCount.Reset();
		else if ( fieldName == "targetingParams" )
			_targetingParams.Reset();
		else if ( fieldName == "lashRange" )
			_lashRange.Reset();
		else if ( fieldName == "responseRange" )
			_responseRange.Reset();
		else if ( fieldName == "responseTime" )
			_responseTime.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "summonType" )
			return _summonType.IsDerivedFromParent();
		if ( fieldName == "maxCount" )
			return _maxCount.IsDerivedFromParent();
		if ( fieldName == "maxThisCount" )
			return _maxThisCount.IsDerivedFromParent();
		if ( fieldName == "targetingParams" )
			return _targetingParams.IsDerivedFromParent();
		if ( fieldName == "lashRange" )
			return _lashRange.IsDerivedFromParent();
		if ( fieldName == "responseRange" )
			return _responseRange.IsDerivedFromParent();
		if ( fieldName == "responseTime" )
			return _responseTime.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFSummonBehaviourDataAdvanced", "PFAdvancedSummon.h")]
[TypeId(0x15D32040)]
public class SummonBehaviourAdvanced : SummonBehaviourCommon
{
	private UndoRedoDBPtr<SummonBehaviourAdvanced> ___parent;
	[HideInOutliner]
	public new DBPtr<SummonBehaviourAdvanced> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SummonBehaviourCommonParams _guardBehaviourParams;
	private SummonBehaviourCommonParams _chaseBehaviourParams;

	[Description( "Параметры режима охраны" )]
	public SummonBehaviourCommonParams guardBehaviourParams { get { return _guardBehaviourParams; } set { _guardBehaviourParams.Assign( value ); } }

	[Description( "Параметры режима преследования" )]
	public SummonBehaviourCommonParams chaseBehaviourParams { get { return _chaseBehaviourParams; } set { _chaseBehaviourParams.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SummonBehaviourAdvanced>(owner);
		_guardBehaviourParams = new SummonBehaviourCommonParams( owner );
		_chaseBehaviourParams = new SummonBehaviourCommonParams( owner );
		___parent.Changed += FireChangedEvent;
		_guardBehaviourParams.Changed += FireChangedEvent;
		_chaseBehaviourParams.Changed += FireChangedEvent;
	}

	public SummonBehaviourAdvanced()
	{
		Initialize( this );
	}
	private void AssignSelf( SummonBehaviourAdvanced source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SummonBehaviourAdvanced" );
		guardBehaviourParams = source.guardBehaviourParams;
		chaseBehaviourParams = source.chaseBehaviourParams;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SummonBehaviourAdvanced source = _source as SummonBehaviourAdvanced;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SummonBehaviourAdvanced" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SummonBehaviourAdvanced newParent = rawParent == null ? null : rawParent.Get<SummonBehaviourAdvanced>();
		if ( newParent == null && _newParent is SummonBehaviourAdvanced )
			newParent = _newParent as SummonBehaviourAdvanced;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_guardBehaviourParams.SetParent( newParent == null ? null : newParent._guardBehaviourParams );
		_chaseBehaviourParams.SetParent( newParent == null ? null : newParent._chaseBehaviourParams );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_guardBehaviourParams.Reset();
		_chaseBehaviourParams.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_guardBehaviourParams.IsDerivedFromParent()
			&& _chaseBehaviourParams.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "guardBehaviourParams" )
			_guardBehaviourParams.Reset();
		else if ( fieldName == "chaseBehaviourParams" )
			_chaseBehaviourParams.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "guardBehaviourParams" )
			return _guardBehaviourParams.IsDerivedFromParent();
		if ( fieldName == "chaseBehaviourParams" )
			return _chaseBehaviourParams.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFSummonEnumerator", "PFTargetSelector.h")]
[TypeId(0x9E677280)]
[UseTypeName("TGSL")]
public class SummonEnumerator : MultipleTargetSelector
{
	private UndoRedoDBPtr<SummonEnumerator> ___parent;
	[HideInOutliner]
	public new DBPtr<SummonEnumerator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<SummonTypeFlags> _summonTypes;

	public SummonTypeFlags summonTypes { get { return _summonTypes.Get(); } set { _summonTypes.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SummonEnumerator>(owner);
		_summonTypes = new UndoRedo<SummonTypeFlags>( owner, SummonTypeFlags.Primary );
		___parent.Changed += FireChangedEvent;
		_summonTypes.Changed += FireChangedEvent;
	}

	public SummonEnumerator()
	{
		Initialize( this );
	}
	private void AssignSelf( SummonEnumerator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SummonEnumerator" );
		summonTypes = source.summonTypes;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SummonEnumerator source = _source as SummonEnumerator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SummonEnumerator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SummonEnumerator newParent = rawParent == null ? null : rawParent.Get<SummonEnumerator>();
		if ( newParent == null && _newParent is SummonEnumerator )
			newParent = _newParent as SummonEnumerator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_summonTypes.SetParent( newParent == null ? null : newParent._summonTypes );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_summonTypes.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_summonTypes.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "summonTypes" )
			_summonTypes.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "summonTypes" )
			return _summonTypes.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Check", "NWorld::PFAbilityData", "PFCastLimitations.h", CreateFunction = "NWorld::CheckTargetLimitation")]
[TypeId(0x9E71CB80)]
[UseTypeName("ABCL")]
public class TargetCastLimitation : CastLimitation
{
	private UndoRedoDBPtr<TargetCastLimitation> ___parent;
	[HideInOutliner]
	public new DBPtr<TargetCastLimitation> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;

	[Description( "Target selector to check target presence" )]
	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TargetCastLimitation>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public TargetCastLimitation()
	{
		Initialize( this );
	}
	private void AssignSelf( TargetCastLimitation source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TargetCastLimitation" );
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TargetCastLimitation source = _source as TargetCastLimitation;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TargetCastLimitation" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TargetCastLimitation newParent = rawParent == null ? null : rawParent.Get<TargetCastLimitation>();
		if ( newParent == null && _newParent is TargetCastLimitation )
			newParent = _newParent as TargetCastLimitation;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplTargetsCounter", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F739C40)]
[UseTypeName("APLR")]
public class TargetsCounterApplicator : BuffApplicator
{
	private UndoRedoDBPtr<TargetsCounterApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<TargetsCounterApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<TargetSelector> _targetSelector;

	public DBPtr<TargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TargetsCounterApplicator>(owner);
		_targetSelector = new UndoRedoDBPtr<TargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public TargetsCounterApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( TargetsCounterApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TargetsCounterApplicator" );
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TargetsCounterApplicator source = _source as TargetsCounterApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TargetsCounterApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TargetsCounterApplicator newParent = rawParent == null ? null : rawParent.Get<TargetsCounterApplicator>();
		if ( newParent == null && _newParent is TargetsCounterApplicator )
			newParent = _newParent as TargetsCounterApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFAttackersTargetSelector", "PFTargetSelector.h")]
[TypeId(0x9A9D43C0)]
[UseTypeName("TGSL")]
public class AttackersTargetSelector : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<AttackersTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<AttackersTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EAttackersType> _type;
	private ExecutableFloatString _damageDealTime;
	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;

	[Description( "Which criteria to use, 'who targeted me' or 'who damaged me in x seconds'" )]
	public EAttackersType type { get { return _type.Get(); } set { _type.Set( value ); } }

	[Description( "Time span to cvount dealed damage (when type = DamageDealers)" )]
	public ExecutableFloatString damageDealTime { get { return _damageDealTime; } set { _damageDealTime.Assign( value ); } }

	[Description( "Unit to get attackers from (using aplicator target if not specified)" )]
	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AttackersTargetSelector>(owner);
		_type = new UndoRedo<EAttackersType>( owner, EAttackersType.Targeters );
		ExecutableFloatString __damageDealTime = new ExecutableFloatString(); // Construct default object for damageDealTime
		__damageDealTime.sString = "0.0f";
		_damageDealTime = new ExecutableFloatString( owner, __damageDealTime );
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_damageDealTime.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public AttackersTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( AttackersTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AttackersTargetSelector" );
		type = source.type;
		damageDealTime = source.damageDealTime;
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AttackersTargetSelector source = _source as AttackersTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AttackersTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AttackersTargetSelector newParent = rawParent == null ? null : rawParent.Get<AttackersTargetSelector>();
		if ( newParent == null && _newParent is AttackersTargetSelector )
			newParent = _newParent as AttackersTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_type.SetParent( newParent == null ? null : newParent._type );
		_damageDealTime.SetParent( newParent == null ? null : newParent._damageDealTime );
		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_type.Reset();
		_damageDealTime.Reset();
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_type.IsDerivedFromParent()
			&& _damageDealTime.IsDerivedFromParent()
			&& _targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "damageDealTime" )
			_damageDealTime.Reset();
		else if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "damageDealTime" )
			return _damageDealTime.IsDerivedFromParent();
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFTargetSelectorMicroAI", "PFMicroAI.h", CreateFunction = "NWorld::CreateMicroAI<>")]
[UseTypeName("MCAI")]
public class TargetSelectorMicroAI : BasicMicroAI
{
	private UndoRedoDBPtr<TargetSelectorMicroAI> ___parent;
	[HideInOutliner]
	public new DBPtr<TargetSelectorMicroAI> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;

	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TargetSelectorMicroAI>(owner);
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public TargetSelectorMicroAI()
	{
		Initialize( this );
	}
	private void AssignSelf( TargetSelectorMicroAI source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TargetSelectorMicroAI" );
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TargetSelectorMicroAI source = _source as TargetSelectorMicroAI;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TargetSelectorMicroAI" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TargetSelectorMicroAI newParent = rawParent == null ? null : rawParent.Get<TargetSelectorMicroAI>();
		if ( newParent == null && _newParent is TargetSelectorMicroAI )
			newParent = _newParent as TargetSelectorMicroAI;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplTaunt", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E5C0B09)]
[UseTypeName("APLR")]
public class TauntApplicator : BuffApplicator
{
	private UndoRedoDBPtr<TauntApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<TauntApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _tauntTarget;
	private UndoRedo<bool> _strongTarget;

	[Description( "Target to taunt on" )]
	public EApplicatorApplyTarget tauntTarget { get { return _tauntTarget.Get(); } set { _tauntTarget.Set( value ); } }

	[Description( "Receiver's target can't be changed by autotargeting" )]
	public bool strongTarget { get { return _strongTarget.Get(); } set { _strongTarget.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TauntApplicator>(owner);
		_tauntTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_strongTarget = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_tauntTarget.Changed += FireChangedEvent;
		_strongTarget.Changed += FireChangedEvent;
	}

	public TauntApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( TauntApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TauntApplicator" );
		tauntTarget = source.tauntTarget;
		strongTarget = source.strongTarget;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TauntApplicator source = _source as TauntApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TauntApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TauntApplicator newParent = rawParent == null ? null : rawParent.Get<TauntApplicator>();
		if ( newParent == null && _newParent is TauntApplicator )
			newParent = _newParent as TauntApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_tauntTarget.SetParent( newParent == null ? null : newParent._tauntTarget );
		_strongTarget.SetParent( newParent == null ? null : newParent._strongTarget );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_tauntTarget.Reset();
		_strongTarget.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_tauntTarget.IsDerivedFromParent()
			&& _strongTarget.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "tauntTarget" )
			_tauntTarget.Reset();
		else if ( fieldName == "strongTarget" )
			_strongTarget.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "tauntTarget" )
			return _tauntTarget.IsDerivedFromParent();
		if ( fieldName == "strongTarget" )
			return _strongTarget.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplTeleport", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E67C380)]
[UseTypeName("APLR")]
public class TeleportApplicator : BaseApplicator
{
	private UndoRedoDBPtr<TeleportApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<TeleportApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _teleportTarget;
	private ExecutableFloatString _maxDistance;
	private UndoRedoDBPtr<EffectBase> _disappearEffect;
	private UndoRedoDBPtr<EffectBase> _appearEffect;
	private UndoRedo<bool> _pushUnits;
	private UndoRedo<bool> _notifyInboundDispatches;

	[Description( "Target to teleport to" )]
	public EApplicatorApplyTarget teleportTarget { get { return _teleportTarget.Get(); } set { _teleportTarget.Set( value ); } }

	[Description( "Maximal teleport distance (if 0 or less - teleport distance is not limited)" )]
	public ExecutableFloatString maxDistance { get { return _maxDistance; } set { _maxDistance.Assign( value ); } }

	[Description( "Effect of disappearing. Played on the place where teleporting unit was standing." )]
	public DBPtr<EffectBase> disappearEffect { get { return _disappearEffect.Get(); } set { _disappearEffect.Set( value ); } }

	[Description( "Effect of appearing. Played on the place where teleporting unit standing after teleport." )]
	public DBPtr<EffectBase> appearEffect { get { return _appearEffect.Get(); } set { _appearEffect.Set( value ); } }

	[Description( "When true, this applicator will free place for teleporting unit by pushing other units avay." )]
	public bool pushUnits { get { return _pushUnits.Get(); } set { _pushUnits.Set( value ); } }

	[Description( "Notify inbound dispatches" )]
	public bool notifyInboundDispatches { get { return _notifyInboundDispatches.Get(); } set { _notifyInboundDispatches.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TeleportApplicator>(owner);
		_teleportTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		ExecutableFloatString __maxDistance = new ExecutableFloatString(); // Construct default object for maxDistance
		__maxDistance.sString = "0.0f";
		_maxDistance = new ExecutableFloatString( owner, __maxDistance );
		_disappearEffect = new UndoRedoDBPtr<EffectBase>( owner );
		_appearEffect = new UndoRedoDBPtr<EffectBase>( owner );
		_pushUnits = new UndoRedo<bool>( owner, false );
		_notifyInboundDispatches = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_teleportTarget.Changed += FireChangedEvent;
		_maxDistance.Changed += FireChangedEvent;
		_disappearEffect.Changed += FireChangedEvent;
		_appearEffect.Changed += FireChangedEvent;
		_pushUnits.Changed += FireChangedEvent;
		_notifyInboundDispatches.Changed += FireChangedEvent;
	}

	public TeleportApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( TeleportApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TeleportApplicator" );
		teleportTarget = source.teleportTarget;
		maxDistance = source.maxDistance;
		disappearEffect = source.disappearEffect;
		appearEffect = source.appearEffect;
		pushUnits = source.pushUnits;
		notifyInboundDispatches = source.notifyInboundDispatches;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TeleportApplicator source = _source as TeleportApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TeleportApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TeleportApplicator newParent = rawParent == null ? null : rawParent.Get<TeleportApplicator>();
		if ( newParent == null && _newParent is TeleportApplicator )
			newParent = _newParent as TeleportApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_teleportTarget.SetParent( newParent == null ? null : newParent._teleportTarget );
		_maxDistance.SetParent( newParent == null ? null : newParent._maxDistance );
		_disappearEffect.SetParent( newParent == null ? null : newParent._disappearEffect );
		_appearEffect.SetParent( newParent == null ? null : newParent._appearEffect );
		_pushUnits.SetParent( newParent == null ? null : newParent._pushUnits );
		_notifyInboundDispatches.SetParent( newParent == null ? null : newParent._notifyInboundDispatches );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_teleportTarget.Reset();
		_maxDistance.Reset();
		_disappearEffect.Reset();
		_appearEffect.Reset();
		_pushUnits.Reset();
		_notifyInboundDispatches.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_teleportTarget.IsDerivedFromParent()
			&& _maxDistance.IsDerivedFromParent()
			&& _disappearEffect.IsDerivedFromParent()
			&& _appearEffect.IsDerivedFromParent()
			&& _pushUnits.IsDerivedFromParent()
			&& _notifyInboundDispatches.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "teleportTarget" )
			_teleportTarget.Reset();
		else if ( fieldName == "maxDistance" )
			_maxDistance.Reset();
		else if ( fieldName == "disappearEffect" )
			_disappearEffect.Reset();
		else if ( fieldName == "appearEffect" )
			_appearEffect.Reset();
		else if ( fieldName == "pushUnits" )
			_pushUnits.Reset();
		else if ( fieldName == "notifyInboundDispatches" )
			_notifyInboundDispatches.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "teleportTarget" )
			return _teleportTarget.IsDerivedFromParent();
		if ( fieldName == "maxDistance" )
			return _maxDistance.IsDerivedFromParent();
		if ( fieldName == "disappearEffect" )
			return _disappearEffect.IsDerivedFromParent();
		if ( fieldName == "appearEffect" )
			return _appearEffect.IsDerivedFromParent();
		if ( fieldName == "pushUnits" )
			return _pushUnits.IsDerivedFromParent();
		if ( fieldName == "notifyInboundDispatches" )
			return _notifyInboundDispatches.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(5)]
[FactoryImpl("Create", "NWorld::PFApplThrow", "PFApplMove.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x1E729C40)]
[UseTypeName("APLR")]
public class ThrowApplicator : BaseApplicator
{
	private UndoRedoDBPtr<ThrowApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ThrowApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EThrowType> _flightType;
	private UndoRedo<EGhostMoveMode> _collisionFlags;
	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;
	private UndoRedo<bool> _trackTargetUnit;
	private UndoRedoDBPtr<Spell> _startSpell;
	private UndoRedoDBPtr<Spell> _stopSpell;
	private ExecutableFloatString _moveSpeed;
	private ExecutableFloatString _flipTime;
	private UndoRedo<float> _maxHeight;
	private UndoRedo<float> _maxDistance;
	private AnimatedFloat _trajectory;
	private AnimatedFloat _angle;
	private UndoRedo<float> _takeOffTime;
	private UndoRedo<float> _landTime;
	private UndoRedo<bool> _surfaceSpeedFromAG;
	private UndoRedoAssignableList<DBPtr<EffectBase>> _flyEffect;
	private UndoRedo<EBuffBehavior> _behaviorFlags;
	private UndoRedo<bool> _lockRotation;
	private UndoRedoDBPtr<SingleTargetSelector> _firstTargetToHit;

	[Description( "Разновидность полёта" )]
	public EThrowType flightType { get { return _flightType.Get(); } set { _flightType.Set( value ); } }

	[Description( "Объекты, через которые мы можем перепрыгивать" )]
	public EGhostMoveMode collisionFlags { get { return _collisionFlags.Get(); } set { _collisionFlags.Set( value ); } }

	[Description( "Выбор цели полёта" )]
	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Режим самонаведения на движущийся юнит-цель" )]
	public bool trackTargetUnit { get { return _trackTargetUnit.Get(); } set { _trackTargetUnit.Set( value ); } }

	[Description( "Spell выполняемый до начала работы аппликатора" )]
	public DBPtr<Spell> startSpell { get { return _startSpell.Get(); } set { _startSpell.Set( value ); } }

	[Description( "Spell выполняемый после окончания работы аппликатора" )]
	public DBPtr<Spell> stopSpell { get { return _stopSpell.Get(); } set { _stopSpell.Set( value ); } }

	[Description( "Горизонтальная скорость полёта юнита (м/с)" )]
	public ExecutableFloatString moveSpeed { get { return _moveSpeed; } set { _moveSpeed.Assign( value ); } }

	[Description( "Время полёта юнита в случае Flip" )]
	public ExecutableFloatString flipTime { get { return _flipTime; } set { _flipTime.Assign( value ); } }

	[Description( "Максимальная высота полёта юнита" )]
	public float maxHeight { get { return _maxHeight.Get(); } set { _maxHeight.Set( value ); } }

	[Description( "Растояние на котором высота равняется maxHeight" )]
	public float maxDistance { get { return _maxDistance.Get(); } set { _maxDistance.Set( value ); } }

	[Description( "Форма траектории полёта юнита (нормируется по maxHeight)" )]
	public AnimatedFloat trajectory { get { return _trajectory; } set { _trajectory.Assign( value ); } }

	[Description( "Угол наклона на траектории полета (0 - для вычисления по касательной к траектории)" )]
	public AnimatedFloat angle { get { return _angle; } set { _angle.Assign( value ); } }

	[Description( "Время, через которое юнит начнёт перемещение после начала спела (случай Jump)" )]
	public float takeOffTime { get { return _takeOffTime.Get(); } set { _takeOffTime.Set( value ); } }

	[Description( "Время до приземления, когда пора проигрывать финальную анимацию (случай Jump)" )]
	public float landTime { get { return _landTime.Get(); } set { _landTime.Set( value ); } }

	[Description( "Согласовывать ли Surface Speed анимации с АГ (случай Jump)" )]
	public bool surfaceSpeedFromAG { get { return _surfaceSpeedFromAG.Get(); } set { _surfaceSpeedFromAG.Set( value ); } }

	[Description( "Эффект полёта юнита (зацикленная нода) (случай Jump)" )]
	[EnumArray(typeof(ETeamID))]
	public libdb.IChangeableList<DBPtr<EffectBase>> flyEffect { get { return _flyEffect; } set { _flyEffect.Assign( value ); } }

	[Description( "StopOnDisable - buff will be dropped when become disabled (in normal state it could be enabled again)" )]
	public EBuffBehavior behaviorFlags { get { return _behaviorFlags.Get(); } set { _behaviorFlags.Set( value ); } }

	[Description( "Запрещать ли поворот SceneObject'а получателя на время действия аппликатора" )]
	public bool lockRotation { get { return _lockRotation.Get(); } set { _lockRotation.Set( value ); } }

	[Description( "Выбор цели для экстренной остановки" )]
	public DBPtr<SingleTargetSelector> firstTargetToHit { get { return _firstTargetToHit.Get(); } set { _firstTargetToHit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ThrowApplicator>(owner);
		_flightType = new UndoRedo<EThrowType>( owner, EThrowType.Throw );
		_collisionFlags = new UndoRedo<EGhostMoveMode>( owner, EGhostMoveMode.IgnoreDynamic );
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_trackTargetUnit = new UndoRedo<bool>( owner, false );
		_startSpell = new UndoRedoDBPtr<Spell>( owner );
		_stopSpell = new UndoRedoDBPtr<Spell>( owner );
		ExecutableFloatString __moveSpeed = new ExecutableFloatString(); // Construct default object for moveSpeed
		__moveSpeed.sString = "1.0";
		_moveSpeed = new ExecutableFloatString( owner, __moveSpeed );
		ExecutableFloatString __flipTime = new ExecutableFloatString(); // Construct default object for flipTime
		__flipTime.sString = "1.0";
		_flipTime = new ExecutableFloatString( owner, __flipTime );
		_maxHeight = new UndoRedo<float>( owner, 0.0f );
		_maxDistance = new UndoRedo<float>( owner, 0.0f );
		_trajectory = new AnimatedFloat( owner, 1.0f );
		_angle = new AnimatedFloat( owner, 0.0f );
		_takeOffTime = new UndoRedo<float>( owner, 0.0f );
		_landTime = new UndoRedo<float>( owner, 0.0f );
		_surfaceSpeedFromAG = new UndoRedo<bool>( owner, true );
		_flyEffect = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner, typeof( ETeamID ) );
		_behaviorFlags = new UndoRedo<EBuffBehavior>( owner, EBuffBehavior.Zero );
		_lockRotation = new UndoRedo<bool>( owner, false );
		_firstTargetToHit = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_flightType.Changed += FireChangedEvent;
		_collisionFlags.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_trackTargetUnit.Changed += FireChangedEvent;
		_startSpell.Changed += FireChangedEvent;
		_stopSpell.Changed += FireChangedEvent;
		_moveSpeed.Changed += FireChangedEvent;
		_flipTime.Changed += FireChangedEvent;
		_maxHeight.Changed += FireChangedEvent;
		_maxDistance.Changed += FireChangedEvent;
		_trajectory.Changed += FireChangedEvent;
		_angle.Changed += FireChangedEvent;
		_takeOffTime.Changed += FireChangedEvent;
		_landTime.Changed += FireChangedEvent;
		_surfaceSpeedFromAG.Changed += FireChangedEvent;
		_flyEffect.Changed += FireChangedEvent;
		_behaviorFlags.Changed += FireChangedEvent;
		_lockRotation.Changed += FireChangedEvent;
		_firstTargetToHit.Changed += FireChangedEvent;
	}

	public ThrowApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ThrowApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ThrowApplicator" );
		flightType = source.flightType;
		collisionFlags = source.collisionFlags;
		targetSelector = source.targetSelector;
		trackTargetUnit = source.trackTargetUnit;
		startSpell = source.startSpell;
		stopSpell = source.stopSpell;
		moveSpeed = source.moveSpeed;
		flipTime = source.flipTime;
		maxHeight = source.maxHeight;
		maxDistance = source.maxDistance;
		trajectory = source.trajectory;
		angle = source.angle;
		takeOffTime = source.takeOffTime;
		landTime = source.landTime;
		surfaceSpeedFromAG = source.surfaceSpeedFromAG;
		flyEffect = source.flyEffect;
		behaviorFlags = source.behaviorFlags;
		lockRotation = source.lockRotation;
		firstTargetToHit = source.firstTargetToHit;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ThrowApplicator source = _source as ThrowApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ThrowApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ThrowApplicator newParent = rawParent == null ? null : rawParent.Get<ThrowApplicator>();
		if ( newParent == null && _newParent is ThrowApplicator )
			newParent = _newParent as ThrowApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_flightType.SetParent( newParent == null ? null : newParent._flightType );
		_collisionFlags.SetParent( newParent == null ? null : newParent._collisionFlags );
		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_trackTargetUnit.SetParent( newParent == null ? null : newParent._trackTargetUnit );
		_startSpell.SetParent( newParent == null ? null : newParent._startSpell );
		_stopSpell.SetParent( newParent == null ? null : newParent._stopSpell );
		_moveSpeed.SetParent( newParent == null ? null : newParent._moveSpeed );
		_flipTime.SetParent( newParent == null ? null : newParent._flipTime );
		_maxHeight.SetParent( newParent == null ? null : newParent._maxHeight );
		_maxDistance.SetParent( newParent == null ? null : newParent._maxDistance );
		_trajectory.SetParent( newParent == null ? null : newParent._trajectory );
		_angle.SetParent( newParent == null ? null : newParent._angle );
		_takeOffTime.SetParent( newParent == null ? null : newParent._takeOffTime );
		_landTime.SetParent( newParent == null ? null : newParent._landTime );
		_surfaceSpeedFromAG.SetParent( newParent == null ? null : newParent._surfaceSpeedFromAG );
		_flyEffect.SetParent( newParent == null ? null : newParent._flyEffect );
		_behaviorFlags.SetParent( newParent == null ? null : newParent._behaviorFlags );
		_lockRotation.SetParent( newParent == null ? null : newParent._lockRotation );
		_firstTargetToHit.SetParent( newParent == null ? null : newParent._firstTargetToHit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_flightType.Reset();
		_collisionFlags.Reset();
		_targetSelector.Reset();
		_trackTargetUnit.Reset();
		_startSpell.Reset();
		_stopSpell.Reset();
		_moveSpeed.Reset();
		_flipTime.Reset();
		_maxHeight.Reset();
		_maxDistance.Reset();
		_trajectory.Reset();
		_angle.Reset();
		_takeOffTime.Reset();
		_landTime.Reset();
		_surfaceSpeedFromAG.Reset();
		_flyEffect.Reset();
		_behaviorFlags.Reset();
		_lockRotation.Reset();
		_firstTargetToHit.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_flightType.IsDerivedFromParent()
			&& _collisionFlags.IsDerivedFromParent()
			&& _targetSelector.IsDerivedFromParent()
			&& _trackTargetUnit.IsDerivedFromParent()
			&& _startSpell.IsDerivedFromParent()
			&& _stopSpell.IsDerivedFromParent()
			&& _moveSpeed.IsDerivedFromParent()
			&& _flipTime.IsDerivedFromParent()
			&& _maxHeight.IsDerivedFromParent()
			&& _maxDistance.IsDerivedFromParent()
			&& _trajectory.IsDerivedFromParent()
			&& _angle.IsDerivedFromParent()
			&& _takeOffTime.IsDerivedFromParent()
			&& _landTime.IsDerivedFromParent()
			&& _surfaceSpeedFromAG.IsDerivedFromParent()
			&& _flyEffect.IsDerivedFromParent()
			&& _behaviorFlags.IsDerivedFromParent()
			&& _lockRotation.IsDerivedFromParent()
			&& _firstTargetToHit.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "flightType" )
			_flightType.Reset();
		else if ( fieldName == "collisionFlags" )
			_collisionFlags.Reset();
		else if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "trackTargetUnit" )
			_trackTargetUnit.Reset();
		else if ( fieldName == "startSpell" )
			_startSpell.Reset();
		else if ( fieldName == "stopSpell" )
			_stopSpell.Reset();
		else if ( fieldName == "moveSpeed" )
			_moveSpeed.Reset();
		else if ( fieldName == "flipTime" )
			_flipTime.Reset();
		else if ( fieldName == "maxHeight" )
			_maxHeight.Reset();
		else if ( fieldName == "maxDistance" )
			_maxDistance.Reset();
		else if ( fieldName == "trajectory" )
			_trajectory.Reset();
		else if ( fieldName == "angle" )
			_angle.Reset();
		else if ( fieldName == "takeOffTime" )
			_takeOffTime.Reset();
		else if ( fieldName == "landTime" )
			_landTime.Reset();
		else if ( fieldName == "surfaceSpeedFromAG" )
			_surfaceSpeedFromAG.Reset();
		else if ( fieldName == "flyEffect" )
			_flyEffect.Reset();
		else if ( fieldName == "behaviorFlags" )
			_behaviorFlags.Reset();
		else if ( fieldName == "lockRotation" )
			_lockRotation.Reset();
		else if ( fieldName == "firstTargetToHit" )
			_firstTargetToHit.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "flightType" )
			return _flightType.IsDerivedFromParent();
		if ( fieldName == "collisionFlags" )
			return _collisionFlags.IsDerivedFromParent();
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "trackTargetUnit" )
			return _trackTargetUnit.IsDerivedFromParent();
		if ( fieldName == "startSpell" )
			return _startSpell.IsDerivedFromParent();
		if ( fieldName == "stopSpell" )
			return _stopSpell.IsDerivedFromParent();
		if ( fieldName == "moveSpeed" )
			return _moveSpeed.IsDerivedFromParent();
		if ( fieldName == "flipTime" )
			return _flipTime.IsDerivedFromParent();
		if ( fieldName == "maxHeight" )
			return _maxHeight.IsDerivedFromParent();
		if ( fieldName == "maxDistance" )
			return _maxDistance.IsDerivedFromParent();
		if ( fieldName == "trajectory" )
			return _trajectory.IsDerivedFromParent();
		if ( fieldName == "angle" )
			return _angle.IsDerivedFromParent();
		if ( fieldName == "takeOffTime" )
			return _takeOffTime.IsDerivedFromParent();
		if ( fieldName == "landTime" )
			return _landTime.IsDerivedFromParent();
		if ( fieldName == "surfaceSpeedFromAG" )
			return _surfaceSpeedFromAG.IsDerivedFromParent();
		if ( fieldName == "flyEffect" )
			return _flyEffect.IsDerivedFromParent();
		if ( fieldName == "behaviorFlags" )
			return _behaviorFlags.IsDerivedFromParent();
		if ( fieldName == "lockRotation" )
			return _lockRotation.IsDerivedFromParent();
		if ( fieldName == "firstTargetToHit" )
			return _firstTargetToHit.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFTriggerApplicator", "PFTriggerApplicator.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F722380)]
[UseTypeName("APLR")]
public class TriggerApplicator : BuffApplicator
{
	private UndoRedoDBPtr<TriggerApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<TriggerApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableIntString _actionsCount;
	private UndoRedoDBPtr<EventProcessorBase> _processor;
	private UndoRedo<bool> _useAbilityCooldown;
	private UndoRedo<bool> _useAbilityOwnerMana;
	private UndoRedo<bool> _playAck;

	public ExecutableIntString actionsCount { get { return _actionsCount; } set { _actionsCount.Assign( value ); } }

	public DBPtr<EventProcessorBase> processor { get { return _processor.Get(); } set { _processor.Set( value ); } }

	public bool useAbilityCooldown { get { return _useAbilityCooldown.Get(); } set { _useAbilityCooldown.Set( value ); } }

	public bool useAbilityOwnerMana { get { return _useAbilityOwnerMana.Get(); } set { _useAbilityOwnerMana.Set( value ); } }

	[Description( "Проигрывать указанный в таланте аск героя при срабатывании." )]
	public bool playAck { get { return _playAck.Get(); } set { _playAck.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TriggerApplicator>(owner);
		_actionsCount = new ExecutableIntString( owner );
		_processor = new UndoRedoDBPtr<EventProcessorBase>( owner );
		_useAbilityCooldown = new UndoRedo<bool>( owner, false );
		_useAbilityOwnerMana = new UndoRedo<bool>( owner, false );
		_playAck = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_actionsCount.Changed += FireChangedEvent;
		_processor.Changed += FireChangedEvent;
		_useAbilityCooldown.Changed += FireChangedEvent;
		_useAbilityOwnerMana.Changed += FireChangedEvent;
		_playAck.Changed += FireChangedEvent;
	}

	public TriggerApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( TriggerApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TriggerApplicator" );
		actionsCount = source.actionsCount;
		processor = source.processor;
		useAbilityCooldown = source.useAbilityCooldown;
		useAbilityOwnerMana = source.useAbilityOwnerMana;
		playAck = source.playAck;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TriggerApplicator source = _source as TriggerApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TriggerApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TriggerApplicator newParent = rawParent == null ? null : rawParent.Get<TriggerApplicator>();
		if ( newParent == null && _newParent is TriggerApplicator )
			newParent = _newParent as TriggerApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_actionsCount.SetParent( newParent == null ? null : newParent._actionsCount );
		_processor.SetParent( newParent == null ? null : newParent._processor );
		_useAbilityCooldown.SetParent( newParent == null ? null : newParent._useAbilityCooldown );
		_useAbilityOwnerMana.SetParent( newParent == null ? null : newParent._useAbilityOwnerMana );
		_playAck.SetParent( newParent == null ? null : newParent._playAck );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_actionsCount.Reset();
		_processor.Reset();
		_useAbilityCooldown.Reset();
		_useAbilityOwnerMana.Reset();
		_playAck.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_actionsCount.IsDerivedFromParent()
			&& _processor.IsDerivedFromParent()
			&& _useAbilityCooldown.IsDerivedFromParent()
			&& _useAbilityOwnerMana.IsDerivedFromParent()
			&& _playAck.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "actionsCount" )
			_actionsCount.Reset();
		else if ( fieldName == "processor" )
			_processor.Reset();
		else if ( fieldName == "useAbilityCooldown" )
			_useAbilityCooldown.Reset();
		else if ( fieldName == "useAbilityOwnerMana" )
			_useAbilityOwnerMana.Reset();
		else if ( fieldName == "playAck" )
			_playAck.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "actionsCount" )
			return _actionsCount.IsDerivedFromParent();
		if ( fieldName == "processor" )
			return _processor.IsDerivedFromParent();
		if ( fieldName == "useAbilityCooldown" )
			return _useAbilityCooldown.IsDerivedFromParent();
		if ( fieldName == "useAbilityOwnerMana" )
			return _useAbilityOwnerMana.IsDerivedFromParent();
		if ( fieldName == "playAck" )
			return _playAck.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFUIMessageApplicator", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x2C6C83C2)]
[UseTypeName("APLR")]
public class UIMessageApplicator : BaseApplicator
{
	private UndoRedoDBPtr<UIMessageApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<UIMessageApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _message;
	private ExecutableFloatString _value;
	private UndoRedoDBPtr<UIEvent> _uiEvent;

	[Description( "Сообщение со значением. Включать значение value так: <value=value>." )]
	public TextRef message { get { return _message; } set { _message.Assign( value ); } }

	[Description( "Значение" )]
	public ExecutableFloatString value { get { return _value; } set { _value.Assign( value ); } }

	[Description( "UI событие" )]
	public DBPtr<UIEvent> uiEvent { get { return _uiEvent.Get(); } set { _uiEvent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UIMessageApplicator>(owner);
		_message = new TextRef( owner, new TextRef() );
		ExecutableFloatString __value = new ExecutableFloatString(); // Construct default object for value
		__value.sString = "-1.0";
		_value = new ExecutableFloatString( owner, __value );
		_uiEvent = new UndoRedoDBPtr<UIEvent>( owner );
		___parent.Changed += FireChangedEvent;
		_message.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		_uiEvent.Changed += FireChangedEvent;
	}

	public UIMessageApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( UIMessageApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UIMessageApplicator" );
		message = source.message;
		value = source.value;
		uiEvent = source.uiEvent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UIMessageApplicator source = _source as UIMessageApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UIMessageApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UIMessageApplicator newParent = rawParent == null ? null : rawParent.Get<UIMessageApplicator>();
		if ( newParent == null && _newParent is UIMessageApplicator )
			newParent = _newParent as UIMessageApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_message.SetParent( newParent == null ? null : newParent._message );
		_value.SetParent( newParent == null ? null : newParent._value );
		_uiEvent.SetParent( newParent == null ? null : newParent._uiEvent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_message.Reset();
		_value.Reset();
		_uiEvent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_message.IsDerivedFromParent()
			&& _value.IsDerivedFromParent()
			&& _uiEvent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "message" )
			_message.Reset();
		else if ( fieldName == "value" )
			_value.Reset();
		else if ( fieldName == "uiEvent" )
			_uiEvent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "message" )
			return _message.IsDerivedFromParent();
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
		if ( fieldName == "uiEvent" )
			return _uiEvent.IsDerivedFromParent();
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
public class UnitConstant : DBResource
{
	private UndoRedoDBPtr<UnitConstant> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitConstant> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _name;
	private ExecutableFloatString _var;

	public string name { get { return _name.Get(); } set { _name.Set( value ); } }

	public ExecutableFloatString var { get { return _var; } set { _var.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitConstant>(owner);
		_name = new UndoRedo<string>( owner, string.Empty );
		ExecutableFloatString __var = new ExecutableFloatString(); // Construct default object for var
		__var.sString = "0.0f";
		_var = new ExecutableFloatString( owner, __var );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_var.Changed += FireChangedEvent;
	}

	public UnitConstant()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitConstant source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitConstant" );
		name = source.name;
		var = source.var;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitConstant source = _source as UnitConstant;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitConstant" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitConstant newParent = rawParent == null ? null : rawParent.Get<UnitConstant>();
		if ( newParent == null && _newParent is UnitConstant )
			newParent = _newParent as UnitConstant;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		_var.SetParent( newParent == null ? null : newParent._var );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		_var.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _var.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "var" )
			_var.Reset();
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
		if ( fieldName == "var" )
			return _var.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
[TypeId(0x0F64AC40)]
[UseTypeName("UCCN")]
public class UnitConstantsContainer : DBResource
{
	private UndoRedoDBPtr<UnitConstantsContainer> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitConstantsContainer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<UnitConstant>> _vars;

	public libdb.IChangeableList<DBPtr<UnitConstant>> vars { get { return _vars; } set { _vars.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitConstantsContainer>(owner);
		_vars = new UndoRedoAssignableList<DBPtr<UnitConstant>>( owner );
		___parent.Changed += FireChangedEvent;
		_vars.Changed += FireChangedEvent;
	}

	public UnitConstantsContainer()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitConstantsContainer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitConstantsContainer" );
		vars = source.vars;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitConstantsContainer source = _source as UnitConstantsContainer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitConstantsContainer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitConstantsContainer newParent = rawParent == null ? null : rawParent.Get<UnitConstantsContainer>();
		if ( newParent == null && _newParent is UnitConstantsContainer )
			newParent = _newParent as UnitConstantsContainer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_vars.SetParent( newParent == null ? null : newParent._vars );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_vars.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_vars.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "vars" )
			_vars.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "vars" )
			return _vars.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFUnitEnumerator", "PFTargetSelector.h")]
[TypeId(0x9E677300)]
[UseTypeName("TGSL")]
public class UnitEnumerator : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<UnitEnumerator> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitEnumerator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitEnumerator>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public UnitEnumerator()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitEnumerator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitEnumerator" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitEnumerator source = _source as UnitEnumerator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitEnumerator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitEnumerator newParent = rawParent == null ? null : rawParent.Get<UnitEnumerator>();
		if ( newParent == null && _newParent is UnitEnumerator )
			newParent = _newParent as UnitEnumerator;
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

[FactoryImpl("Create", "NWorld::PFUnitPlaceCorrector", "PFTargetSelector.h")]
[TypeId(0x9E71DB80)]
[UseTypeName("TGSL")]
public class UnitPlaceCorrector : SingleTargetSelector
{
	private UndoRedoDBPtr<UnitPlaceCorrector> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitPlaceCorrector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SingleTargetSelector> _targetSelector;
	private UndoRedo<bool> _checkByRangeToRequester;
	private UndoRedo<bool> _nativeTerrainOnly;
	private UndoRedo<float> _radius;
	private UndoRedo<ETraceMode> _passabilityCheckMode;
	private UndoRedo<bool> _checkLineOfSight;

	[Description( "Target selector to select from" )]
	public DBPtr<SingleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	[Description( "Искать место не дальше radius от requester'а. Задайте false если вам это не интересно." )]
	public bool checkByRangeToRequester { get { return _checkByRangeToRequester.Get(); } set { _checkByRangeToRequester.Set( value ); } }

	[Description( "Искать место только на родном террейне" )]
	public bool nativeTerrainOnly { get { return _nativeTerrainOnly.Get(); } set { _nativeTerrainOnly.Set( value ); } }

	[Description( "Радиус, в котором искать место. Укажите 0, если он не превышает размеров юнита." )]
	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	[Description( "Типы проходимости для которых чекать свободно место. 0 - обычный режим." )]
	public ETraceMode passabilityCheckMode { get { return _passabilityCheckMode.Get(); } set { _passabilityCheckMode.Set( value ); } }

	[Description( "Чекать видимость или нет" )]
	public bool checkLineOfSight { get { return _checkLineOfSight.Get(); } set { _checkLineOfSight.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitPlaceCorrector>(owner);
		_targetSelector = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_checkByRangeToRequester = new UndoRedo<bool>( owner, false );
		_nativeTerrainOnly = new UndoRedo<bool>( owner, false );
		_radius = new UndoRedo<float>( owner, 0.0f );
		_passabilityCheckMode = new UndoRedo<ETraceMode>( owner, (ETraceMode)0 );
		_checkLineOfSight = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
		_checkByRangeToRequester.Changed += FireChangedEvent;
		_nativeTerrainOnly.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
		_passabilityCheckMode.Changed += FireChangedEvent;
		_checkLineOfSight.Changed += FireChangedEvent;
	}

	public UnitPlaceCorrector()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitPlaceCorrector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitPlaceCorrector" );
		targetSelector = source.targetSelector;
		checkByRangeToRequester = source.checkByRangeToRequester;
		nativeTerrainOnly = source.nativeTerrainOnly;
		radius = source.radius;
		passabilityCheckMode = source.passabilityCheckMode;
		checkLineOfSight = source.checkLineOfSight;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitPlaceCorrector source = _source as UnitPlaceCorrector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitPlaceCorrector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitPlaceCorrector newParent = rawParent == null ? null : rawParent.Get<UnitPlaceCorrector>();
		if ( newParent == null && _newParent is UnitPlaceCorrector )
			newParent = _newParent as UnitPlaceCorrector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		_checkByRangeToRequester.SetParent( newParent == null ? null : newParent._checkByRangeToRequester );
		_nativeTerrainOnly.SetParent( newParent == null ? null : newParent._nativeTerrainOnly );
		_radius.SetParent( newParent == null ? null : newParent._radius );
		_passabilityCheckMode.SetParent( newParent == null ? null : newParent._passabilityCheckMode );
		_checkLineOfSight.SetParent( newParent == null ? null : newParent._checkLineOfSight );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		_checkByRangeToRequester.Reset();
		_nativeTerrainOnly.Reset();
		_radius.Reset();
		_passabilityCheckMode.Reset();
		_checkLineOfSight.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& _checkByRangeToRequester.IsDerivedFromParent()
			&& _nativeTerrainOnly.IsDerivedFromParent()
			&& _radius.IsDerivedFromParent()
			&& _passabilityCheckMode.IsDerivedFromParent()
			&& _checkLineOfSight.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else if ( fieldName == "checkByRangeToRequester" )
			_checkByRangeToRequester.Reset();
		else if ( fieldName == "nativeTerrainOnly" )
			_nativeTerrainOnly.Reset();
		else if ( fieldName == "radius" )
			_radius.Reset();
		else if ( fieldName == "passabilityCheckMode" )
			_passabilityCheckMode.Reset();
		else if ( fieldName == "checkLineOfSight" )
			_checkLineOfSight.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		if ( fieldName == "checkByRangeToRequester" )
			return _checkByRangeToRequester.IsDerivedFromParent();
		if ( fieldName == "nativeTerrainOnly" )
			return _nativeTerrainOnly.IsDerivedFromParent();
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		if ( fieldName == "passabilityCheckMode" )
			return _passabilityCheckMode.IsDerivedFromParent();
		if ( fieldName == "checkLineOfSight" )
			return _checkLineOfSight.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFUnitShiftTarget", "PFTargetSelector.h")]
[TypeId(0x1E728BC0)]
[UseTypeName("TGSL")]
public class UnitShiftTarget : SingleTargetSelector
{
	private UndoRedoDBPtr<UnitShiftTarget> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitShiftTarget> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _distance;

	[Category( "Maximal shift distance" )]
	public ExecutableFloatString distance { get { return _distance; } set { _distance.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitShiftTarget>(owner);
		ExecutableFloatString __distance = new ExecutableFloatString(); // Construct default object for distance
		__distance.sString = "10.0f";
		_distance = new ExecutableFloatString( owner, __distance );
		___parent.Changed += FireChangedEvent;
		_distance.Changed += FireChangedEvent;
	}

	public UnitShiftTarget()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitShiftTarget source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitShiftTarget" );
		distance = source.distance;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitShiftTarget source = _source as UnitShiftTarget;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitShiftTarget" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitShiftTarget newParent = rawParent == null ? null : rawParent.Get<UnitShiftTarget>();
		if ( newParent == null && _newParent is UnitShiftTarget )
			newParent = _newParent as UnitShiftTarget;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_distance.SetParent( newParent == null ? null : newParent._distance );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_distance.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_distance.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "distance" )
			_distance.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "distance" )
			return _distance.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplValue", "PFApplMod.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x0F73BB40)]
[UseTypeName("APLR")]
public class ValueApplicator : BuffApplicator
{
	private UndoRedoDBPtr<ValueApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<ValueApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ExecutableFloatString _value;

	public ExecutableFloatString value { get { return _value; } set { _value.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ValueApplicator>(owner);
		ExecutableFloatString __value = new ExecutableFloatString(); // Construct default object for value
		__value.sString = "0.0f";
		_value = new ExecutableFloatString( owner, __value );
		___parent.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
	}

	public ValueApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( ValueApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ValueApplicator" );
		value = source.value;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ValueApplicator source = _source as ValueApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ValueApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ValueApplicator newParent = rawParent == null ? null : rawParent.Get<ValueApplicator>();
		if ( newParent == null && _newParent is ValueApplicator )
			newParent = _newParent as ValueApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_value.SetParent( newParent == null ? null : newParent._value );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_value.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_value.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "value" )
			_value.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplVariableProxy", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE778BC80)]
[UseTypeName("APLR")]
public class VariableProxyApplicator : BaseApplicator
{
	private UndoRedoDBPtr<VariableProxyApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<VariableProxyApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<ApplicatorToProxy> _applicators;

	[Description( "List of applicators to execute and retrieve variable value from" )]
	public libdb.IChangeableList<ApplicatorToProxy> applicators { get { return _applicators; } set { _applicators.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<VariableProxyApplicator>(owner);
		_applicators = new UndoRedoAssignableList<ApplicatorToProxy>( owner );
		___parent.Changed += FireChangedEvent;
		_applicators.Changed += FireChangedEvent;
	}

	public VariableProxyApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( VariableProxyApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for VariableProxyApplicator" );
		applicators = source.applicators;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		VariableProxyApplicator source = _source as VariableProxyApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for VariableProxyApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		VariableProxyApplicator newParent = rawParent == null ? null : rawParent.Get<VariableProxyApplicator>();
		if ( newParent == null && _newParent is VariableProxyApplicator )
			newParent = _newParent as VariableProxyApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_applicators.SetParent( newParent == null ? null : newParent._applicators );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_applicators.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_applicators.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "applicators" )
			_applicators.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "applicators" )
			return _applicators.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplVictory", "PFApplInstant.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0xE77B4C80)]
[UseTypeName("APLR")]
public class VictoryApplicator : BaseApplicator
{
	private UndoRedoDBPtr<VictoryApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<VictoryApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _destroyMainBuilding;
	private UndoRedo<bool> _oppositeFaction;

	[Description( "Destroy losers' main building" )]
	public bool destroyMainBuilding { get { return _destroyMainBuilding.Get(); } set { _destroyMainBuilding.Set( value ); } }

	[Description( "Wins a faction opposite to the applicator sender's faction" )]
	public bool oppositeFaction { get { return _oppositeFaction.Get(); } set { _oppositeFaction.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<VictoryApplicator>(owner);
		_destroyMainBuilding = new UndoRedo<bool>( owner, false );
		_oppositeFaction = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_destroyMainBuilding.Changed += FireChangedEvent;
		_oppositeFaction.Changed += FireChangedEvent;
	}

	public VictoryApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( VictoryApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for VictoryApplicator" );
		destroyMainBuilding = source.destroyMainBuilding;
		oppositeFaction = source.oppositeFaction;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		VictoryApplicator source = _source as VictoryApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for VictoryApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		VictoryApplicator newParent = rawParent == null ? null : rawParent.Get<VictoryApplicator>();
		if ( newParent == null && _newParent is VictoryApplicator )
			newParent = _newParent as VictoryApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_destroyMainBuilding.SetParent( newParent == null ? null : newParent._destroyMainBuilding );
		_oppositeFaction.SetParent( newParent == null ? null : newParent._oppositeFaction );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_destroyMainBuilding.Reset();
		_oppositeFaction.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_destroyMainBuilding.IsDerivedFromParent()
			&& _oppositeFaction.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "destroyMainBuilding" )
			_destroyMainBuilding.Reset();
		else if ( fieldName == "oppositeFaction" )
			_oppositeFaction.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "destroyMainBuilding" )
			return _destroyMainBuilding.IsDerivedFromParent();
		if ( fieldName == "oppositeFaction" )
			return _oppositeFaction.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplWaitForSpell", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E67ACC1)]
[UseTypeName("APLR")]
public class WaitForSpellApplicator : BuffApplicator
{
	private UndoRedoDBPtr<WaitForSpellApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<WaitForSpellApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EApplicatorApplyTarget> _spellTarget;
	private UndoRedoDBPtr<Spell> _spell;
	private UndoRedo<EWaitForSpellBehaviour> _behaviour;
	private UndoRedoDBPtr<SingleTargetSelector> _firstTargetToHit;
	private UndoRedoDBPtr<SingleTargetSelector> _dispatchSource;

	[Description( "Spell target" )]
	public EApplicatorApplyTarget spellTarget { get { return _spellTarget.Get(); } set { _spellTarget.Set( value ); } }

	[Description( "Spell to send" )]
	public DBPtr<Spell> spell { get { return _spell.Get(); } set { _spell.Set( value ); } }

	[Description( "Behaviour description" )]
	public EWaitForSpellBehaviour behaviour { get { return _behaviour.Get(); } set { _behaviour.Set( value ); } }

	[Description( "Dispatch will hit found target and stop" )]
	public DBPtr<SingleTargetSelector> firstTargetToHit { get { return _firstTargetToHit.Get(); } set { _firstTargetToHit.Set( value ); } }

	[Description( "Source of dispatch. Applytarget by default." )]
	public DBPtr<SingleTargetSelector> dispatchSource { get { return _dispatchSource.Get(); } set { _dispatchSource.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WaitForSpellApplicator>(owner);
		_spellTarget = new UndoRedo<EApplicatorApplyTarget>( owner, EApplicatorApplyTarget.ApplicatorTarget );
		_spell = new UndoRedoDBPtr<Spell>( owner );
		_behaviour = new UndoRedo<EWaitForSpellBehaviour>( owner, EWaitForSpellBehaviour.Zero );
		_firstTargetToHit = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_dispatchSource = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_spellTarget.Changed += FireChangedEvent;
		_spell.Changed += FireChangedEvent;
		_behaviour.Changed += FireChangedEvent;
		_firstTargetToHit.Changed += FireChangedEvent;
		_dispatchSource.Changed += FireChangedEvent;
	}

	public WaitForSpellApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( WaitForSpellApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WaitForSpellApplicator" );
		spellTarget = source.spellTarget;
		spell = source.spell;
		behaviour = source.behaviour;
		firstTargetToHit = source.firstTargetToHit;
		dispatchSource = source.dispatchSource;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WaitForSpellApplicator source = _source as WaitForSpellApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WaitForSpellApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WaitForSpellApplicator newParent = rawParent == null ? null : rawParent.Get<WaitForSpellApplicator>();
		if ( newParent == null && _newParent is WaitForSpellApplicator )
			newParent = _newParent as WaitForSpellApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_spellTarget.SetParent( newParent == null ? null : newParent._spellTarget );
		_spell.SetParent( newParent == null ? null : newParent._spell );
		_behaviour.SetParent( newParent == null ? null : newParent._behaviour );
		_firstTargetToHit.SetParent( newParent == null ? null : newParent._firstTargetToHit );
		_dispatchSource.SetParent( newParent == null ? null : newParent._dispatchSource );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_spellTarget.Reset();
		_spell.Reset();
		_behaviour.Reset();
		_firstTargetToHit.Reset();
		_dispatchSource.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_spellTarget.IsDerivedFromParent()
			&& _spell.IsDerivedFromParent()
			&& _behaviour.IsDerivedFromParent()
			&& _firstTargetToHit.IsDerivedFromParent()
			&& _dispatchSource.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "spellTarget" )
			_spellTarget.Reset();
		else if ( fieldName == "spell" )
			_spell.Reset();
		else if ( fieldName == "behaviour" )
			_behaviour.Reset();
		else if ( fieldName == "firstTargetToHit" )
			_firstTargetToHit.Reset();
		else if ( fieldName == "dispatchSource" )
			_dispatchSource.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "spellTarget" )
			return _spellTarget.IsDerivedFromParent();
		if ( fieldName == "spell" )
			return _spell.IsDerivedFromParent();
		if ( fieldName == "behaviour" )
			return _behaviour.IsDerivedFromParent();
		if ( fieldName == "firstTargetToHit" )
			return _firstTargetToHit.IsDerivedFromParent();
		if ( fieldName == "dispatchSource" )
			return _dispatchSource.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFWallTargetSelector", "PFTargetSelector.h")]
[TypeId(0xE79C9480)]
[UseTypeName("TGSL")]
public class WallTargetSelector : MultipleTargetSelectorFiltered
{
	private UndoRedoDBPtr<WallTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<WallTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SingleTargetSelector> _origin;
	private UndoRedoDBPtr<SingleTargetSelector> _direction;
	private ExecutableFloatString _length;
	private ExecutableFloatString _width;

	[Description( "Точка в которой находится центр стены" )]
	public DBPtr<SingleTargetSelector> origin { get { return _origin.Get(); } set { _origin.Set( value ); } }

	[Description( "Точка в которую смотрит стена (точнее перпендикуляр)" )]
	public DBPtr<SingleTargetSelector> direction { get { return _direction.Get(); } set { _direction.Set( value ); } }

	[Description( "Длина стены" )]
	public ExecutableFloatString length { get { return _length; } set { _length.Assign( value ); } }

	[Description( "Ширина стены" )]
	public ExecutableFloatString width { get { return _width; } set { _width.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WallTargetSelector>(owner);
		_origin = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		_direction = new UndoRedoDBPtr<SingleTargetSelector>( owner );
		ExecutableFloatString __length = new ExecutableFloatString(); // Construct default object for length
		__length.sString = "4.0f";
		_length = new ExecutableFloatString( owner, __length );
		ExecutableFloatString __width = new ExecutableFloatString(); // Construct default object for width
		__width.sString = "2.0f";
		_width = new ExecutableFloatString( owner, __width );
		___parent.Changed += FireChangedEvent;
		_origin.Changed += FireChangedEvent;
		_direction.Changed += FireChangedEvent;
		_length.Changed += FireChangedEvent;
		_width.Changed += FireChangedEvent;
	}

	public WallTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( WallTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WallTargetSelector" );
		origin = source.origin;
		direction = source.direction;
		length = source.length;
		width = source.width;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WallTargetSelector source = _source as WallTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WallTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WallTargetSelector newParent = rawParent == null ? null : rawParent.Get<WallTargetSelector>();
		if ( newParent == null && _newParent is WallTargetSelector )
			newParent = _newParent as WallTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_origin.SetParent( newParent == null ? null : newParent._origin );
		_direction.SetParent( newParent == null ? null : newParent._direction );
		_length.SetParent( newParent == null ? null : newParent._length );
		_width.SetParent( newParent == null ? null : newParent._width );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_origin.Reset();
		_direction.Reset();
		_length.Reset();
		_width.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_origin.IsDerivedFromParent()
			&& _direction.IsDerivedFromParent()
			&& _length.IsDerivedFromParent()
			&& _width.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "origin" )
			_origin.Reset();
		else if ( fieldName == "direction" )
			_direction.Reset();
		else if ( fieldName == "length" )
			_length.Reset();
		else if ( fieldName == "width" )
			_width.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "origin" )
			return _origin.IsDerivedFromParent();
		if ( fieldName == "direction" )
			return _direction.IsDerivedFromParent();
		if ( fieldName == "length" )
			return _length.IsDerivedFromParent();
		if ( fieldName == "width" )
			return _width.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFApplWatch", "PFApplSpecial.h", CreateFunction = "NWorld::CreateApplicator<>")]
[TypeId(0x9E678B04)]
[UseTypeName("APLR")]
public class WatchApplicator : BuffApplicator
{
	private UndoRedoDBPtr<WatchApplicator> ___parent;
	[HideInOutliner]
	public new DBPtr<WatchApplicator> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EParentNotification> _onSenderDispatchApply;
	private UndoRedo<EParentNotification> _onSenderDispatchEvade;
	private UndoRedo<EParentNotification> _onUnitDeath;
	private UndoRedo<EParentNotification> _onFinish;
	private UndoRedo<EParentNotification> _onSenderDispatchMiss;

	[Description( "Event will be send to the parent when dispatch from ability owner is applied to watched unit" )]
	public EParentNotification onSenderDispatchApply { get { return _onSenderDispatchApply.Get(); } set { _onSenderDispatchApply.Set( value ); } }

	[Description( "Event will be send to the parent when dispatch from ability owner is evaded by watched unit" )]
	public EParentNotification onSenderDispatchEvade { get { return _onSenderDispatchEvade.Get(); } set { _onSenderDispatchEvade.Set( value ); } }

	[Description( "Event will be send to parent on watched unit death" )]
	public EParentNotification onUnitDeath { get { return _onUnitDeath.Get(); } set { _onUnitDeath.Set( value ); } }

	[Description( "Event will be send to parent when this applicator finishes and watched unit is still alive" )]
	public EParentNotification onFinish { get { return _onFinish.Get(); } set { _onFinish.Set( value ); } }

	[Description( "Event will be send to the parent when dispatch from ability owner is missed by watched unit" )]
	public EParentNotification onSenderDispatchMiss { get { return _onSenderDispatchMiss.Get(); } set { _onSenderDispatchMiss.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WatchApplicator>(owner);
		_onSenderDispatchApply = new UndoRedo<EParentNotification>( owner, EParentNotification.NA );
		_onSenderDispatchEvade = new UndoRedo<EParentNotification>( owner, EParentNotification.NA );
		_onUnitDeath = new UndoRedo<EParentNotification>( owner, EParentNotification.NA );
		_onFinish = new UndoRedo<EParentNotification>( owner, EParentNotification.NA );
		_onSenderDispatchMiss = new UndoRedo<EParentNotification>( owner, EParentNotification.NA );
		___parent.Changed += FireChangedEvent;
		_onSenderDispatchApply.Changed += FireChangedEvent;
		_onSenderDispatchEvade.Changed += FireChangedEvent;
		_onUnitDeath.Changed += FireChangedEvent;
		_onFinish.Changed += FireChangedEvent;
		_onSenderDispatchMiss.Changed += FireChangedEvent;
	}

	public WatchApplicator()
	{
		Initialize( this );
	}
	private void AssignSelf( WatchApplicator source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WatchApplicator" );
		onSenderDispatchApply = source.onSenderDispatchApply;
		onSenderDispatchEvade = source.onSenderDispatchEvade;
		onUnitDeath = source.onUnitDeath;
		onFinish = source.onFinish;
		onSenderDispatchMiss = source.onSenderDispatchMiss;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WatchApplicator source = _source as WatchApplicator;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WatchApplicator" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WatchApplicator newParent = rawParent == null ? null : rawParent.Get<WatchApplicator>();
		if ( newParent == null && _newParent is WatchApplicator )
			newParent = _newParent as WatchApplicator;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_onSenderDispatchApply.SetParent( newParent == null ? null : newParent._onSenderDispatchApply );
		_onSenderDispatchEvade.SetParent( newParent == null ? null : newParent._onSenderDispatchEvade );
		_onUnitDeath.SetParent( newParent == null ? null : newParent._onUnitDeath );
		_onFinish.SetParent( newParent == null ? null : newParent._onFinish );
		_onSenderDispatchMiss.SetParent( newParent == null ? null : newParent._onSenderDispatchMiss );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_onSenderDispatchApply.Reset();
		_onSenderDispatchEvade.Reset();
		_onUnitDeath.Reset();
		_onFinish.Reset();
		_onSenderDispatchMiss.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_onSenderDispatchApply.IsDerivedFromParent()
			&& _onSenderDispatchEvade.IsDerivedFromParent()
			&& _onUnitDeath.IsDerivedFromParent()
			&& _onFinish.IsDerivedFromParent()
			&& _onSenderDispatchMiss.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "onSenderDispatchApply" )
			_onSenderDispatchApply.Reset();
		else if ( fieldName == "onSenderDispatchEvade" )
			_onSenderDispatchEvade.Reset();
		else if ( fieldName == "onUnitDeath" )
			_onUnitDeath.Reset();
		else if ( fieldName == "onFinish" )
			_onFinish.Reset();
		else if ( fieldName == "onSenderDispatchMiss" )
			_onSenderDispatchMiss.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "onSenderDispatchApply" )
			return _onSenderDispatchApply.IsDerivedFromParent();
		if ( fieldName == "onSenderDispatchEvade" )
			return _onSenderDispatchEvade.IsDerivedFromParent();
		if ( fieldName == "onUnitDeath" )
			return _onUnitDeath.IsDerivedFromParent();
		if ( fieldName == "onFinish" )
			return _onFinish.IsDerivedFromParent();
		if ( fieldName == "onSenderDispatchMiss" )
			return _onSenderDispatchMiss.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "NWorld::PFWeightTargetSelector", "PFTargetSelector.h")]
[TypeId(0x2282AB00)]
[UseTypeName("TGSL")]
public class WeightTargetSelector : SingleTargetSelector
{
	private UndoRedoDBPtr<WeightTargetSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<WeightTargetSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<MultipleTargetSelector> _targetSelector;

	public DBPtr<MultipleTargetSelector> targetSelector { get { return _targetSelector.Get(); } set { _targetSelector.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<WeightTargetSelector>(owner);
		_targetSelector = new UndoRedoDBPtr<MultipleTargetSelector>( owner );
		___parent.Changed += FireChangedEvent;
		_targetSelector.Changed += FireChangedEvent;
	}

	public WeightTargetSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( WeightTargetSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for WeightTargetSelector" );
		targetSelector = source.targetSelector;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		WeightTargetSelector source = _source as WeightTargetSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WeightTargetSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		WeightTargetSelector newParent = rawParent == null ? null : rawParent.Get<WeightTargetSelector>();
		if ( newParent == null && _newParent is WeightTargetSelector )
			newParent = _newParent as WeightTargetSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_targetSelector.SetParent( newParent == null ? null : newParent._targetSelector );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_targetSelector.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_targetSelector.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "targetSelector" )
			_targetSelector.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "targetSelector" )
			return _targetSelector.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
