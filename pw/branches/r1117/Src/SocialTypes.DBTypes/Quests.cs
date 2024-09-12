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
public enum CastleResources
{
	Resource1 = 0,
	Resource2 = 1,
	Resource3 = 2,
	Resource1_Rare = 3,
	Resource2_Rare = 4,
	Resource3_Rare = 5,
	Perl = 6,
	RedPerl = 7,
	Silver = 8,
	Gold = 9,
	Population = 10,
	CWPoints_Clan = 11,
	CWPoints_Player = 12,
	TalentsToPay = 13,
	Shard = 14,
	Custom = 15,
};

public enum DBDynamicQuestCheckType
{
	SessionResult = 0,
	SessionInfo = 1,
	Instant = 2,
	ModelData = 3,
};

public enum DBModelDataConditionType
{
	CastleLogin = 0,
	HeroLevel = 1,
	HeroLevelUp = 2,
	HeroRating = 3,
	HeroRatingUp = 4,
	HeroForce = 5,
	HeroForceUp = 6,
	BuildingLevel = 7,
	CollectResources = 8,
	ForgeTalent = 9,
	MakeReforges = 10,
	CollectCWPointsGuildFight = 11,
};

public enum DBSessionCheckType
{
	WinOnly = 0,
	WinAndLoss = 1,
	Loss = 2,
};

public enum DynamicQuestAwardConditionType
{
	AfterWin = 0,
	AfterMiss = 1,
};

public enum DynamicQuestAwardType
{
	PremiumAcc = 0,
	Gold = 1,
	Resource1 = 2,
	Resource2 = 3,
	Resource3 = 4,
	Silver = 5,
	Perl = 6,
	RedPerl = 7,
	Talent = 8,
	RandomTalent = 9,
	Construction = 10,
	Experience = 11,
	Lamp = 12,
	CustomFlag = 13,
	Hero = 14,
	Skin = 15,
	FractionChange = 16,
	NicknameChange = 17,
	HeroExperience = 18,
	HeroStatsReset = 19,
	AllHeroStatsReset = 20,
	Quest = 21,
	RandomHero = 22,
	RandomSkin = 23,
	RandomTalentFromPool = 24,
	AlreadyCompletedQuest = 25,
	UpgradeHeroTalentsEvent = 26,
	GuildLogoChange = 27,
	GuildExperience = 28,
	Shard = 29,
	CustomCurrency = 30,
};

[Flags]
public enum ECastleLibraryFilter
{
	None = 0,
	Ordinary = 1,
	Good = 2,
	Excellent = 4,
	Magnificent = 8,
	Exclusive = 16,
	Outstanding = 32,
	All = 63,
};

public enum EnergyChangeType
{
	Increment = 0,
	Override = 1,
	AsTopValue = 2,
	AsBottomValue = 3,
};

public enum FinsihSessionResult
{
	DontCare = 0,
	Win = 1,
	Lose = 2,
};

[Flags]
public enum GenderFractionFilter
{
	All = 0,
	Male = 1,
	Female = 2,
	A = 4,
	B = 8,
};

public enum HightlightItemType
{
	UnsoulboundButton = 0,
	SellTalentButton = 1,
	PlayGameButton = 2,
	UpgradeButton = 3,
};

public enum MapType
{
	Tutorial = 0,
	CTF = 1,
	PVP = 2,
	PVE = 3,
};

public enum MatchType
{
	pvp = 0,
	pve = 1,
	train = 2,
	pvp1x1 = 3,
	pvp2x2 = 4,
	pvb = 5,
	ctf = 6,
};

public enum OpenWindowConditionType
{
	Academy = 0,
	CastleMain = 1,
};

public enum PanelType
{
	Construction = 0,
	Friends = 1,
	Heroes = 2,
};

public enum SendRequestName
{
	accept_friend = 0,
	accept_quest = 1,
	add_all_talents = 2,
	add_dodges = 3,
	add_friend = 4,
	add_friend_to_favorites = 5,
	add_ignore = 6,
	add_quest = 7,
	add_statistic = 8,
	add_talent = 9,
	add_to_pocket = 10,
	boost_buildingproduction = 11,
	building_move = 12,
	building_place = 13,
	building_remove = 14,
	building_upgrade = 15,
	buy_cycle = 16,
	buy_hero = 17,
	buy_hero_gold = 18,
	buy_premium_account = 19,
	buy_premium_account_GM = 20,
	buy_special_hero = 21,
	change_fraction = 22,
	change_last_login = 23,
	change_map = 24,
	change_nickname = 25,
	change_pa_end = 26,
	check_pending_quests = 27,
	check_talent = 28,
	clear_item_soulbound = 29,
	clear_soulbound = 30,
	collect_production_results = 31,
	collect_talent = 32,
	complete_quest = 33,
	decline_friend = 34,
	decrease_energy = 35,
	expansion = 36,
	finish_production = 37,
	force_complete_objective = 38,
	get_prices = 39,
	give_experience = 40,
	give_fame = 41,
	give_rating = 42,
	give_resource = 43,
	give_stat_points = 44,
	hire_hero = 45,
	increase_building_lvl = 46,
	increase_stat = 47,
	invite_friend = 48,
	item_move_inv2ts = 49,
	item_move_ts2inv = 50,
	item_move_ts2ts = 51,
	item_remove_new_status = 52,
	item_set_actbar_idx = 53,
	keepalive = 54,
	mark_event_viewed = 55,
	merge_talents = 56,
	mm_accept = 57,
	mm_add = 58,
	mm_cancel = 59,
	mm_leave = 60,
	move_from_pocket = 61,
	move_perl_into_building = 62,
	move_to_pocket = 63,
	notify_session_ended = 64,
	only_guard = 65,
	party_accept = 66,
	party_decline = 67,
	party_disband = 68,
	party_go = 69,
	party_hero = 70,
	party_invite = 71,
	party_kick = 72,
	place_friend_to_building = 73,
	place_hero_to_building = 74,
	remove_friend = 75,
	remove_friend_from_building = 76,
	remove_friend_from_favorites = 77,
	remove_hero_from_building = 78,
	remove_ignore = 79,
	remove_perl_from_building = 80,
	remove_talents = 81,
	reset_counters = 82,
	reset_new_talents = 83,
	reset_stat_points = 84,
	return_friend = 85,
	search_friend = 86,
	set_guard = 87,
	set_new_status = 88,
	skip_objective = 89,
	start_building_production = 90,
	stop_building_production = 91,
	try_complete_objective = 92,
	upgrade_talent = 93,
};

public enum SendRequestPhase
{
	ClientAccepted = 0,
	ServerAccepted = 1,
};

public enum StatisticEventType
{
	SESSION_FINISH = 0,
	SESSION_RESOURCE = 1,
	SESSION_TALENT = 2,
	BATH_START = 3,
	BATH_FINISH = 4,
	PRODUCTION_START = 5,
	PRODUCTION_FINISH = 6,
	TALENT_START = 7,
	TALENT_FINISH = 8,
	TALENT_UNSOULBOUND = 9,
	TALENT_SOULBOUND = 10,
	TALENT_UPGRADE = 11,
	TALENTS_REMOVE = 12,
	FREE_SKIP = 13,
	DAILY_COMPLETE = 14,
	PRODUCTION_SKIP = 15,
	HERO_LEVEL = 16,
	HERO_RATING = 17,
	HERO_FORCE = 18,
	BUILDING_LEVEL = 19,
	TALENT_REFORGE = 20,
	GUILD_SESSION_FINISH = 21,
	BUILDING_BOOST = 22,
	RED_PERL_BUY = 23,
	TALENT_REFORGE_UPGRADE = 24,
};

public enum TutorialState
{
	NotStarted = 0,
	BattleQuestAdded = 1,
	SessionMMStarted = 2,
	SessionMMAccepted = 3,
	SessionStarted = 4,
	ClientReturnedFromSession = 5,
	RewardsReceived = 6,
	Completed = 7,
	Skipped = 9,
};

[Custom("Social")]
public class DBDynamicAward : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBDynamicAward __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<DynamicQuestAwardType> _AwardType;
	private UndoRedo<string> _TextData;
	private UndoRedo<int> _Value;
	private UndoRedo<int> _PersistentId;
	private UndoRedo<DynamicQuestAwardConditionType> _AwardConditionType;

	public DynamicQuestAwardType AwardType { get { return _AwardType.Get(); } set { _AwardType.Set( value ); } }

	public string TextData { get { return _TextData.Get(); } set { _TextData.Set( value ); } }

	public int Value { get { return _Value.Get(); } set { _Value.Set( value ); } }

	public int PersistentId { get { return _PersistentId.Get(); } set { _PersistentId.Set( value ); } }

	public DynamicQuestAwardConditionType AwardConditionType { get { return _AwardConditionType.Get(); } set { _AwardConditionType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_AwardType = new UndoRedo<DynamicQuestAwardType>( owner, DynamicQuestAwardType.PremiumAcc );
		_TextData = new UndoRedo<string>( owner, string.Empty );
		_Value = new UndoRedo<int>( owner, 0 );
		_PersistentId = new UndoRedo<int>( owner, 0 );
		_AwardConditionType = new UndoRedo<DynamicQuestAwardConditionType>( owner, DynamicQuestAwardConditionType.AfterWin );
		_AwardType.Changed += FireChangedEvent;
		_TextData.Changed += FireChangedEvent;
		_Value.Changed += FireChangedEvent;
		_PersistentId.Changed += FireChangedEvent;
		_AwardConditionType.Changed += FireChangedEvent;
	}

	public DBDynamicAward()
	{
		Initialize( GetOwner() );
	}

	public DBDynamicAward( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBDynamicAward( DBResource owner, DBDynamicAward source )
		: this(owner, source, true){}

	protected DBDynamicAward( DBResource owner, DBDynamicAward source, bool fireEvent )
	{
		_AwardType = new UndoRedo<DynamicQuestAwardType>( owner, source.AwardType );
		_TextData = new UndoRedo<string>( owner, source.TextData );
		_Value = new UndoRedo<int>( owner, source.Value );
		_PersistentId = new UndoRedo<int>( owner, source.PersistentId );
		_AwardConditionType = new UndoRedo<DynamicQuestAwardConditionType>( owner, source.AwardConditionType );
		_AwardType.Changed += FireChangedEvent;
		_TextData.Changed += FireChangedEvent;
		_Value.Changed += FireChangedEvent;
		_PersistentId.Changed += FireChangedEvent;
		_AwardConditionType.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBDynamicAward source = _source as DBDynamicAward;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBDynamicAward" );
		AwardType = source.AwardType;
		TextData = source.TextData;
		Value = source.Value;
		PersistentId = source.PersistentId;
		AwardConditionType = source.AwardConditionType;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBDynamicAward newParent = _newParent as DBDynamicAward;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_AwardType.SetParent( newParent == null ? null : newParent._AwardType );
		_TextData.SetParent( newParent == null ? null : newParent._TextData );
		_Value.SetParent( newParent == null ? null : newParent._Value );
		_PersistentId.SetParent( newParent == null ? null : newParent._PersistentId );
		_AwardConditionType.SetParent( newParent == null ? null : newParent._AwardConditionType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_AwardType.Reset();
		_TextData.Reset();
		_Value.Reset();
		_PersistentId.Reset();
		_AwardConditionType.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_AwardType.IsDerivedFromParent()
			&& _TextData.IsDerivedFromParent()
			&& _Value.IsDerivedFromParent()
			&& _PersistentId.IsDerivedFromParent()
			&& _AwardConditionType.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "AwardType" )
			_AwardType.Reset();
		else if ( fieldName == "TextData" )
			_TextData.Reset();
		else if ( fieldName == "Value" )
			_Value.Reset();
		else if ( fieldName == "PersistentId" )
			_PersistentId.Reset();
		else if ( fieldName == "AwardConditionType" )
			_AwardConditionType.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "AwardType" )
			return _AwardType.IsDerivedFromParent();
		if ( fieldName == "TextData" )
			return _TextData.IsDerivedFromParent();
		if ( fieldName == "Value" )
			return _Value.IsDerivedFromParent();
		if ( fieldName == "PersistentId" )
			return _PersistentId.IsDerivedFromParent();
		if ( fieldName == "AwardConditionType" )
			return _AwardConditionType.IsDerivedFromParent();
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
public class DBInstantCondition : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBInstantCondition __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<CastleResources> _ResourceType;
	private UndoRedo<string> _CustomCurrencyId;
	private UndoRedo<string> _TotalValue;

	public CastleResources ResourceType { get { return _ResourceType.Get(); } set { _ResourceType.Set( value ); } }

	public string CustomCurrencyId { get { return _CustomCurrencyId.Get(); } set { _CustomCurrencyId.Set( value ); } }

	public string TotalValue { get { return _TotalValue.Get(); } set { _TotalValue.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_ResourceType = new UndoRedo<CastleResources>( owner, CastleResources.Resource1 );
		_CustomCurrencyId = new UndoRedo<string>( owner, string.Empty );
		_TotalValue = new UndoRedo<string>( owner, string.Empty );
		_ResourceType.Changed += FireChangedEvent;
		_CustomCurrencyId.Changed += FireChangedEvent;
		_TotalValue.Changed += FireChangedEvent;
	}

	public DBInstantCondition()
	{
		Initialize( GetOwner() );
	}

	public DBInstantCondition( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBInstantCondition( DBResource owner, DBInstantCondition source )
		: this(owner, source, true){}

	protected DBInstantCondition( DBResource owner, DBInstantCondition source, bool fireEvent )
	{
		_ResourceType = new UndoRedo<CastleResources>( owner, source.ResourceType );
		_CustomCurrencyId = new UndoRedo<string>( owner, source.CustomCurrencyId );
		_TotalValue = new UndoRedo<string>( owner, source.TotalValue );
		_ResourceType.Changed += FireChangedEvent;
		_CustomCurrencyId.Changed += FireChangedEvent;
		_TotalValue.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBInstantCondition source = _source as DBInstantCondition;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBInstantCondition" );
		ResourceType = source.ResourceType;
		CustomCurrencyId = source.CustomCurrencyId;
		TotalValue = source.TotalValue;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBInstantCondition newParent = _newParent as DBInstantCondition;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_ResourceType.SetParent( newParent == null ? null : newParent._ResourceType );
		_CustomCurrencyId.SetParent( newParent == null ? null : newParent._CustomCurrencyId );
		_TotalValue.SetParent( newParent == null ? null : newParent._TotalValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_ResourceType.Reset();
		_CustomCurrencyId.Reset();
		_TotalValue.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_ResourceType.IsDerivedFromParent()
			&& _CustomCurrencyId.IsDerivedFromParent()
			&& _TotalValue.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "ResourceType" )
			_ResourceType.Reset();
		else if ( fieldName == "CustomCurrencyId" )
			_CustomCurrencyId.Reset();
		else if ( fieldName == "TotalValue" )
			_TotalValue.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "ResourceType" )
			return _ResourceType.IsDerivedFromParent();
		if ( fieldName == "CustomCurrencyId" )
			return _CustomCurrencyId.IsDerivedFromParent();
		if ( fieldName == "TotalValue" )
			return _TotalValue.IsDerivedFromParent();
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
public class DBMDCondition : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBMDCondition __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<DBModelDataConditionType> _TypeToCollect;
	private UndoRedoList<string> _PersistentIds;
	private UndoRedo<int> _TotalValue;
	private UndoRedo<Int64> _LastEventId;

	public DBModelDataConditionType TypeToCollect { get { return _TypeToCollect.Get(); } set { _TypeToCollect.Set( value ); } }

	public libdb.IChangeableList<string> PersistentIds { get { return _PersistentIds; } set { _PersistentIds.Assign( value ); } }

	public int TotalValue { get { return _TotalValue.Get(); } set { _TotalValue.Set( value ); } }

	public Int64 LastEventId { get { return _LastEventId.Get(); } set { _LastEventId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_TypeToCollect = new UndoRedo<DBModelDataConditionType>( owner, DBModelDataConditionType.CastleLogin );
		_PersistentIds = new UndoRedoList<string>( owner );
		_TotalValue = new UndoRedo<int>( owner, 0 );
		_LastEventId = new UndoRedo<Int64>( owner, 0 );
		_TypeToCollect.Changed += FireChangedEvent;
		_PersistentIds.Changed += FireChangedEvent;
		_TotalValue.Changed += FireChangedEvent;
		_LastEventId.Changed += FireChangedEvent;
	}

	public DBMDCondition()
	{
		Initialize( GetOwner() );
	}

	public DBMDCondition( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBMDCondition( DBResource owner, DBMDCondition source )
		: this(owner, source, true){}

	protected DBMDCondition( DBResource owner, DBMDCondition source, bool fireEvent )
	{
		_TypeToCollect = new UndoRedo<DBModelDataConditionType>( owner, source.TypeToCollect );
		_PersistentIds = new UndoRedoList<string>( owner );
		_PersistentIds.Assign( source.PersistentIds );
		_TotalValue = new UndoRedo<int>( owner, source.TotalValue );
		_LastEventId = new UndoRedo<Int64>( owner, source.LastEventId );
		_TypeToCollect.Changed += FireChangedEvent;
		_PersistentIds.Changed += FireChangedEvent;
		_TotalValue.Changed += FireChangedEvent;
		_LastEventId.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBMDCondition source = _source as DBMDCondition;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBMDCondition" );
		TypeToCollect = source.TypeToCollect;
		PersistentIds = source.PersistentIds;
		TotalValue = source.TotalValue;
		LastEventId = source.LastEventId;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBMDCondition newParent = _newParent as DBMDCondition;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_TypeToCollect.SetParent( newParent == null ? null : newParent._TypeToCollect );
		_PersistentIds.SetParent( newParent == null ? null : newParent._PersistentIds );
		_TotalValue.SetParent( newParent == null ? null : newParent._TotalValue );
		_LastEventId.SetParent( newParent == null ? null : newParent._LastEventId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_TypeToCollect.Reset();
		_PersistentIds.Reset();
		_TotalValue.Reset();
		_LastEventId.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_TypeToCollect.IsDerivedFromParent()
			&& _PersistentIds.IsDerivedFromParent()
			&& _TotalValue.IsDerivedFromParent()
			&& _LastEventId.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "TypeToCollect" )
			_TypeToCollect.Reset();
		else if ( fieldName == "PersistentIds" )
			_PersistentIds.Reset();
		else if ( fieldName == "TotalValue" )
			_TotalValue.Reset();
		else if ( fieldName == "LastEventId" )
			_LastEventId.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "TypeToCollect" )
			return _TypeToCollect.IsDerivedFromParent();
		if ( fieldName == "PersistentIds" )
			return _PersistentIds.IsDerivedFromParent();
		if ( fieldName == "TotalValue" )
			return _TotalValue.IsDerivedFromParent();
		if ( fieldName == "LastEventId" )
			return _LastEventId.IsDerivedFromParent();
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
public class DBSessionCondition : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBSessionCondition __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<int> _PickedHeroes;
	private UndoRedoList<string> _GameTypes;
	private UndoRedo<string> _CollectingType;
	private UndoRedo<int> _TotalValue;
	private UndoRedo<int> _IncrementPerBattle;
	private UndoRedo<DBSessionCheckType> _SessionCheckType;
	private UndoRedo<bool> _IsGuildGame;
	private UndoRedo<int> _PlayerPartySize;
	private UndoRedo<bool> _IsPlayerPartySizeStrongCond;
	private UndoRedo<int> _EnemyPartySize;
	private UndoRedo<bool> _IsEnemyPartySizeStrongCond;

	public libdb.IChangeableList<int> PickedHeroes { get { return _PickedHeroes; } set { _PickedHeroes.Assign( value ); } }

	public libdb.IChangeableList<string> GameTypes { get { return _GameTypes; } set { _GameTypes.Assign( value ); } }

	public string CollectingType { get { return _CollectingType.Get(); } set { _CollectingType.Set( value ); } }

	public int TotalValue { get { return _TotalValue.Get(); } set { _TotalValue.Set( value ); } }

	public int IncrementPerBattle { get { return _IncrementPerBattle.Get(); } set { _IncrementPerBattle.Set( value ); } }

	public DBSessionCheckType SessionCheckType { get { return _SessionCheckType.Get(); } set { _SessionCheckType.Set( value ); } }

	public bool IsGuildGame { get { return _IsGuildGame.Get(); } set { _IsGuildGame.Set( value ); } }

	public int PlayerPartySize { get { return _PlayerPartySize.Get(); } set { _PlayerPartySize.Set( value ); } }

	public bool IsPlayerPartySizeStrongCond { get { return _IsPlayerPartySizeStrongCond.Get(); } set { _IsPlayerPartySizeStrongCond.Set( value ); } }

	public int EnemyPartySize { get { return _EnemyPartySize.Get(); } set { _EnemyPartySize.Set( value ); } }

	public bool IsEnemyPartySizeStrongCond { get { return _IsEnemyPartySizeStrongCond.Get(); } set { _IsEnemyPartySizeStrongCond.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_PickedHeroes = new UndoRedoList<int>( owner );
		_GameTypes = new UndoRedoList<string>( owner );
		_CollectingType = new UndoRedo<string>( owner, string.Empty );
		_TotalValue = new UndoRedo<int>( owner, 0 );
		_IncrementPerBattle = new UndoRedo<int>( owner, 0 );
		_SessionCheckType = new UndoRedo<DBSessionCheckType>( owner, DBSessionCheckType.WinOnly );
		_IsGuildGame = new UndoRedo<bool>( owner, false );
		_PlayerPartySize = new UndoRedo<int>( owner, 1 );
		_IsPlayerPartySizeStrongCond = new UndoRedo<bool>( owner, false );
		_EnemyPartySize = new UndoRedo<int>( owner, 1 );
		_IsEnemyPartySizeStrongCond = new UndoRedo<bool>( owner, false );
		_PickedHeroes.Changed += FireChangedEvent;
		_GameTypes.Changed += FireChangedEvent;
		_CollectingType.Changed += FireChangedEvent;
		_TotalValue.Changed += FireChangedEvent;
		_IncrementPerBattle.Changed += FireChangedEvent;
		_SessionCheckType.Changed += FireChangedEvent;
		_IsGuildGame.Changed += FireChangedEvent;
		_PlayerPartySize.Changed += FireChangedEvent;
		_IsPlayerPartySizeStrongCond.Changed += FireChangedEvent;
		_EnemyPartySize.Changed += FireChangedEvent;
		_IsEnemyPartySizeStrongCond.Changed += FireChangedEvent;
	}

	public DBSessionCondition()
	{
		Initialize( GetOwner() );
	}

	public DBSessionCondition( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBSessionCondition( DBResource owner, DBSessionCondition source )
		: this(owner, source, true){}

	protected DBSessionCondition( DBResource owner, DBSessionCondition source, bool fireEvent )
	{
		_PickedHeroes = new UndoRedoList<int>( owner );
		_PickedHeroes.Assign( source.PickedHeroes );
		_GameTypes = new UndoRedoList<string>( owner );
		_GameTypes.Assign( source.GameTypes );
		_CollectingType = new UndoRedo<string>( owner, source.CollectingType );
		_TotalValue = new UndoRedo<int>( owner, source.TotalValue );
		_IncrementPerBattle = new UndoRedo<int>( owner, source.IncrementPerBattle );
		_SessionCheckType = new UndoRedo<DBSessionCheckType>( owner, source.SessionCheckType );
		_IsGuildGame = new UndoRedo<bool>( owner, source.IsGuildGame );
		_PlayerPartySize = new UndoRedo<int>( owner, source.PlayerPartySize );
		_IsPlayerPartySizeStrongCond = new UndoRedo<bool>( owner, source.IsPlayerPartySizeStrongCond );
		_EnemyPartySize = new UndoRedo<int>( owner, source.EnemyPartySize );
		_IsEnemyPartySizeStrongCond = new UndoRedo<bool>( owner, source.IsEnemyPartySizeStrongCond );
		_PickedHeroes.Changed += FireChangedEvent;
		_GameTypes.Changed += FireChangedEvent;
		_CollectingType.Changed += FireChangedEvent;
		_TotalValue.Changed += FireChangedEvent;
		_IncrementPerBattle.Changed += FireChangedEvent;
		_SessionCheckType.Changed += FireChangedEvent;
		_IsGuildGame.Changed += FireChangedEvent;
		_PlayerPartySize.Changed += FireChangedEvent;
		_IsPlayerPartySizeStrongCond.Changed += FireChangedEvent;
		_EnemyPartySize.Changed += FireChangedEvent;
		_IsEnemyPartySizeStrongCond.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBSessionCondition source = _source as DBSessionCondition;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBSessionCondition" );
		PickedHeroes = source.PickedHeroes;
		GameTypes = source.GameTypes;
		CollectingType = source.CollectingType;
		TotalValue = source.TotalValue;
		IncrementPerBattle = source.IncrementPerBattle;
		SessionCheckType = source.SessionCheckType;
		IsGuildGame = source.IsGuildGame;
		PlayerPartySize = source.PlayerPartySize;
		IsPlayerPartySizeStrongCond = source.IsPlayerPartySizeStrongCond;
		EnemyPartySize = source.EnemyPartySize;
		IsEnemyPartySizeStrongCond = source.IsEnemyPartySizeStrongCond;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBSessionCondition newParent = _newParent as DBSessionCondition;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_PickedHeroes.SetParent( newParent == null ? null : newParent._PickedHeroes );
		_GameTypes.SetParent( newParent == null ? null : newParent._GameTypes );
		_CollectingType.SetParent( newParent == null ? null : newParent._CollectingType );
		_TotalValue.SetParent( newParent == null ? null : newParent._TotalValue );
		_IncrementPerBattle.SetParent( newParent == null ? null : newParent._IncrementPerBattle );
		_SessionCheckType.SetParent( newParent == null ? null : newParent._SessionCheckType );
		_IsGuildGame.SetParent( newParent == null ? null : newParent._IsGuildGame );
		_PlayerPartySize.SetParent( newParent == null ? null : newParent._PlayerPartySize );
		_IsPlayerPartySizeStrongCond.SetParent( newParent == null ? null : newParent._IsPlayerPartySizeStrongCond );
		_EnemyPartySize.SetParent( newParent == null ? null : newParent._EnemyPartySize );
		_IsEnemyPartySizeStrongCond.SetParent( newParent == null ? null : newParent._IsEnemyPartySizeStrongCond );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_PickedHeroes.Reset();
		_GameTypes.Reset();
		_CollectingType.Reset();
		_TotalValue.Reset();
		_IncrementPerBattle.Reset();
		_SessionCheckType.Reset();
		_IsGuildGame.Reset();
		_PlayerPartySize.Reset();
		_IsPlayerPartySizeStrongCond.Reset();
		_EnemyPartySize.Reset();
		_IsEnemyPartySizeStrongCond.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_PickedHeroes.IsDerivedFromParent()
			&& _GameTypes.IsDerivedFromParent()
			&& _CollectingType.IsDerivedFromParent()
			&& _TotalValue.IsDerivedFromParent()
			&& _IncrementPerBattle.IsDerivedFromParent()
			&& _SessionCheckType.IsDerivedFromParent()
			&& _IsGuildGame.IsDerivedFromParent()
			&& _PlayerPartySize.IsDerivedFromParent()
			&& _IsPlayerPartySizeStrongCond.IsDerivedFromParent()
			&& _EnemyPartySize.IsDerivedFromParent()
			&& _IsEnemyPartySizeStrongCond.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "PickedHeroes" )
			_PickedHeroes.Reset();
		else if ( fieldName == "GameTypes" )
			_GameTypes.Reset();
		else if ( fieldName == "CollectingType" )
			_CollectingType.Reset();
		else if ( fieldName == "TotalValue" )
			_TotalValue.Reset();
		else if ( fieldName == "IncrementPerBattle" )
			_IncrementPerBattle.Reset();
		else if ( fieldName == "SessionCheckType" )
			_SessionCheckType.Reset();
		else if ( fieldName == "IsGuildGame" )
			_IsGuildGame.Reset();
		else if ( fieldName == "PlayerPartySize" )
			_PlayerPartySize.Reset();
		else if ( fieldName == "IsPlayerPartySizeStrongCond" )
			_IsPlayerPartySizeStrongCond.Reset();
		else if ( fieldName == "EnemyPartySize" )
			_EnemyPartySize.Reset();
		else if ( fieldName == "IsEnemyPartySizeStrongCond" )
			_IsEnemyPartySizeStrongCond.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "PickedHeroes" )
			return _PickedHeroes.IsDerivedFromParent();
		if ( fieldName == "GameTypes" )
			return _GameTypes.IsDerivedFromParent();
		if ( fieldName == "CollectingType" )
			return _CollectingType.IsDerivedFromParent();
		if ( fieldName == "TotalValue" )
			return _TotalValue.IsDerivedFromParent();
		if ( fieldName == "IncrementPerBattle" )
			return _IncrementPerBattle.IsDerivedFromParent();
		if ( fieldName == "SessionCheckType" )
			return _SessionCheckType.IsDerivedFromParent();
		if ( fieldName == "IsGuildGame" )
			return _IsGuildGame.IsDerivedFromParent();
		if ( fieldName == "PlayerPartySize" )
			return _PlayerPartySize.IsDerivedFromParent();
		if ( fieldName == "IsPlayerPartySizeStrongCond" )
			return _IsPlayerPartySizeStrongCond.IsDerivedFromParent();
		if ( fieldName == "EnemyPartySize" )
			return _EnemyPartySize.IsDerivedFromParent();
		if ( fieldName == "IsEnemyPartySizeStrongCond" )
			return _IsEnemyPartySizeStrongCond.IsDerivedFromParent();
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

[Description( "Нужно выбрать определённый condition в зависимости от QuestCheckType" )]
[IndexField("QuestCheckType")]
[Custom("Social")]
public class DBDynamicObjective : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DBDynamicObjective __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<DBDynamicQuestCheckType> _QuestCheckType;
	private UndoRedo<bool> _ShowProgress;
	private TextRef _Description;
	private TextRef _ButtonDescription;
	private DBSessionCondition _SessionCondition;
	private DBInstantCondition _InstantCondition;
	private DBMDCondition _ModelDataCondition;

	public DBDynamicQuestCheckType QuestCheckType { get { return _QuestCheckType.Get(); } set { _QuestCheckType.Set( value ); } }

	public bool ShowProgress { get { return _ShowProgress.Get(); } set { _ShowProgress.Set( value ); } }

	public TextRef Description { get { return _Description; } set { _Description.Assign( value ); } }

	public TextRef ButtonDescription { get { return _ButtonDescription; } set { _ButtonDescription.Assign( value ); } }

	public DBSessionCondition SessionCondition { get { return _SessionCondition; } set { _SessionCondition.Assign( value ); } }

	public DBInstantCondition InstantCondition { get { return _InstantCondition; } set { _InstantCondition.Assign( value ); } }

	public DBMDCondition ModelDataCondition { get { return _ModelDataCondition; } set { _ModelDataCondition.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_QuestCheckType = new UndoRedo<DBDynamicQuestCheckType>( owner, DBDynamicQuestCheckType.SessionResult );
		_ShowProgress = new UndoRedo<bool>( owner, false );
		_Description = new TextRef( owner, new TextRef() );
		_ButtonDescription = new TextRef( owner, new TextRef() );
		_SessionCondition = new DBSessionCondition( owner );
		_InstantCondition = new DBInstantCondition( owner );
		_ModelDataCondition = new DBMDCondition( owner );
		_QuestCheckType.Changed += FireChangedEvent;
		_ShowProgress.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
		_ButtonDescription.Changed += FireChangedEvent;
		_SessionCondition.Changed += FireChangedEvent;
		_InstantCondition.Changed += FireChangedEvent;
		_ModelDataCondition.Changed += FireChangedEvent;
	}

	public DBDynamicObjective()
	{
		Initialize( GetOwner() );
	}

	public DBDynamicObjective( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DBDynamicObjective( DBResource owner, DBDynamicObjective source )
		: this(owner, source, true){}

	protected DBDynamicObjective( DBResource owner, DBDynamicObjective source, bool fireEvent )
	{
		_QuestCheckType = new UndoRedo<DBDynamicQuestCheckType>( owner, source.QuestCheckType );
		_ShowProgress = new UndoRedo<bool>( owner, source.ShowProgress );
		_Description = new TextRef( owner, source.Description );
		_ButtonDescription = new TextRef( owner, source.ButtonDescription );
		_SessionCondition = new DBSessionCondition( owner, source.SessionCondition );
		_InstantCondition = new DBInstantCondition( owner, source.InstantCondition );
		_ModelDataCondition = new DBMDCondition( owner, source.ModelDataCondition );
		_QuestCheckType.Changed += FireChangedEvent;
		_ShowProgress.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
		_ButtonDescription.Changed += FireChangedEvent;
		_SessionCondition.Changed += FireChangedEvent;
		_InstantCondition.Changed += FireChangedEvent;
		_ModelDataCondition.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DBDynamicObjective source = _source as DBDynamicObjective;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBDynamicObjective" );
		QuestCheckType = source.QuestCheckType;
		ShowProgress = source.ShowProgress;
		Description = source.Description;
		ButtonDescription = source.ButtonDescription;
		SessionCondition = source.SessionCondition;
		InstantCondition = source.InstantCondition;
		ModelDataCondition = source.ModelDataCondition;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBDynamicObjective newParent = _newParent as DBDynamicObjective;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_QuestCheckType.SetParent( newParent == null ? null : newParent._QuestCheckType );
		_ShowProgress.SetParent( newParent == null ? null : newParent._ShowProgress );
		_Description.SetParent( newParent == null ? null : newParent._Description );
		_ButtonDescription.SetParent( newParent == null ? null : newParent._ButtonDescription );
		_SessionCondition.SetParent( newParent == null ? null : newParent._SessionCondition );
		_InstantCondition.SetParent( newParent == null ? null : newParent._InstantCondition );
		_ModelDataCondition.SetParent( newParent == null ? null : newParent._ModelDataCondition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_QuestCheckType.Reset();
		_ShowProgress.Reset();
		_Description.Reset();
		_ButtonDescription.Reset();
		_SessionCondition.Reset();
		_InstantCondition.Reset();
		_ModelDataCondition.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_QuestCheckType.IsDerivedFromParent()
			&& _ShowProgress.IsDerivedFromParent()
			&& _Description.IsDerivedFromParent()
			&& _ButtonDescription.IsDerivedFromParent()
			&& _SessionCondition.IsDerivedFromParent()
			&& _InstantCondition.IsDerivedFromParent()
			&& _ModelDataCondition.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "QuestCheckType" )
			_QuestCheckType.Reset();
		else if ( fieldName == "ShowProgress" )
			_ShowProgress.Reset();
		else if ( fieldName == "Description" )
			_Description.Reset();
		else if ( fieldName == "ButtonDescription" )
			_ButtonDescription.Reset();
		else if ( fieldName == "SessionCondition" )
			_SessionCondition.Reset();
		else if ( fieldName == "InstantCondition" )
			_InstantCondition.Reset();
		else if ( fieldName == "ModelDataCondition" )
			_ModelDataCondition.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "QuestCheckType" )
			return _QuestCheckType.IsDerivedFromParent();
		if ( fieldName == "ShowProgress" )
			return _ShowProgress.IsDerivedFromParent();
		if ( fieldName == "Description" )
			return _Description.IsDerivedFromParent();
		if ( fieldName == "ButtonDescription" )
			return _ButtonDescription.IsDerivedFromParent();
		if ( fieldName == "SessionCondition" )
			return _SessionCondition.IsDerivedFromParent();
		if ( fieldName == "InstantCondition" )
			return _InstantCondition.IsDerivedFromParent();
		if ( fieldName == "ModelDataCondition" )
			return _ModelDataCondition.IsDerivedFromParent();
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

[IndexField("Difficulty")]
[Custom("Social")]
public class DQuestForTalentsGroup : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DQuestForTalentsGroup __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _Difficulty;
	private UndoRedoAssignableList<DBPtr<DQuestForTalent>> _Quests;

	[Description( "Сложность" )]
	public int Difficulty { get { return _Difficulty.Get(); } set { _Difficulty.Set( value ); } }

	[Description( "Сами квесты" )]
	public libdb.IChangeableList<DBPtr<DQuestForTalent>> Quests { get { return _Quests; } set { _Quests.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_Difficulty = new UndoRedo<int>( owner, 0 );
		_Quests = new UndoRedoAssignableList<DBPtr<DQuestForTalent>>( owner );
		_Difficulty.Changed += FireChangedEvent;
		_Quests.Changed += FireChangedEvent;
	}

	public DQuestForTalentsGroup()
	{
		Initialize( GetOwner() );
	}

	public DQuestForTalentsGroup( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DQuestForTalentsGroup( DBResource owner, DQuestForTalentsGroup source )
		: this(owner, source, true){}

	protected DQuestForTalentsGroup( DBResource owner, DQuestForTalentsGroup source, bool fireEvent )
	{
		_Difficulty = new UndoRedo<int>( owner, source.Difficulty );
		_Quests = new UndoRedoAssignableList<DBPtr<DQuestForTalent>>( owner );
		_Quests.Assign( source.Quests );
		_Difficulty.Changed += FireChangedEvent;
		_Quests.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DQuestForTalentsGroup source = _source as DQuestForTalentsGroup;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DQuestForTalentsGroup" );
		Difficulty = source.Difficulty;
		Quests = source.Quests;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DQuestForTalentsGroup newParent = _newParent as DQuestForTalentsGroup;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Difficulty.SetParent( newParent == null ? null : newParent._Difficulty );
		_Quests.SetParent( newParent == null ? null : newParent._Quests );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Difficulty.Reset();
		_Quests.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Difficulty.IsDerivedFromParent()
			&& _Quests.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Difficulty" )
			_Difficulty.Reset();
		else if ( fieldName == "Quests" )
			_Quests.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Difficulty" )
			return _Difficulty.IsDerivedFromParent();
		if ( fieldName == "Quests" )
			return _Quests.IsDerivedFromParent();
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

[IndexField("ETalentRarity")]
[Custom("Social")]
public class DynamicQuestForTalentsDifficulty : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DynamicQuestForTalentsDifficulty __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<ETalentRarity> _ETalentRarity;
	private UndoRedo<int> _Difficulty;

	[Description( "Рарность для этой сложности" )]
	public ETalentRarity ETalentRarity { get { return _ETalentRarity.Get(); } set { _ETalentRarity.Set( value ); } }

	[Description( "Сложность" )]
	public int Difficulty { get { return _Difficulty.Get(); } set { _Difficulty.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_ETalentRarity = new UndoRedo<ETalentRarity>( owner, ETalentRarity.Class );
		_Difficulty = new UndoRedo<int>( owner, 0 );
		_ETalentRarity.Changed += FireChangedEvent;
		_Difficulty.Changed += FireChangedEvent;
	}

	public DynamicQuestForTalentsDifficulty()
	{
		Initialize( GetOwner() );
	}

	public DynamicQuestForTalentsDifficulty( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DynamicQuestForTalentsDifficulty( DBResource owner, DynamicQuestForTalentsDifficulty source )
		: this(owner, source, true){}

	protected DynamicQuestForTalentsDifficulty( DBResource owner, DynamicQuestForTalentsDifficulty source, bool fireEvent )
	{
		_ETalentRarity = new UndoRedo<ETalentRarity>( owner, source.ETalentRarity );
		_Difficulty = new UndoRedo<int>( owner, source.Difficulty );
		_ETalentRarity.Changed += FireChangedEvent;
		_Difficulty.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DynamicQuestForTalentsDifficulty source = _source as DynamicQuestForTalentsDifficulty;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DynamicQuestForTalentsDifficulty" );
		ETalentRarity = source.ETalentRarity;
		Difficulty = source.Difficulty;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DynamicQuestForTalentsDifficulty newParent = _newParent as DynamicQuestForTalentsDifficulty;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_ETalentRarity.SetParent( newParent == null ? null : newParent._ETalentRarity );
		_Difficulty.SetParent( newParent == null ? null : newParent._Difficulty );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_ETalentRarity.Reset();
		_Difficulty.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_ETalentRarity.IsDerivedFromParent()
			&& _Difficulty.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "ETalentRarity" )
			_ETalentRarity.Reset();
		else if ( fieldName == "Difficulty" )
			_Difficulty.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "ETalentRarity" )
			return _ETalentRarity.IsDerivedFromParent();
		if ( fieldName == "Difficulty" )
			return _Difficulty.IsDerivedFromParent();
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

[IndexField("Talent")]
[Custom("Social")]
public class DynamicQuestForTalentsOverridenDifficulty : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DynamicQuestForTalentsOverridenDifficulty __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Talent> _Talent;
	private UndoRedo<int> _Difficulty;

	[Description( "Талант" )]
	public DBPtr<Talent> Talent { get { return _Talent.Get(); } set { _Talent.Set( value ); } }

	[Description( "Сложность" )]
	public int Difficulty { get { return _Difficulty.Get(); } set { _Difficulty.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_Talent = new UndoRedoDBPtr<Talent>( owner );
		_Difficulty = new UndoRedo<int>( owner, 0 );
		_Talent.Changed += FireChangedEvent;
		_Difficulty.Changed += FireChangedEvent;
	}

	public DynamicQuestForTalentsOverridenDifficulty()
	{
		Initialize( GetOwner() );
	}

	public DynamicQuestForTalentsOverridenDifficulty( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DynamicQuestForTalentsOverridenDifficulty( DBResource owner, DynamicQuestForTalentsOverridenDifficulty source )
		: this(owner, source, true){}

	protected DynamicQuestForTalentsOverridenDifficulty( DBResource owner, DynamicQuestForTalentsOverridenDifficulty source, bool fireEvent )
	{
		_Talent = new UndoRedoDBPtr<Talent>( owner, source.Talent );
		_Difficulty = new UndoRedo<int>( owner, source.Difficulty );
		_Talent.Changed += FireChangedEvent;
		_Difficulty.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DynamicQuestForTalentsOverridenDifficulty source = _source as DynamicQuestForTalentsOverridenDifficulty;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DynamicQuestForTalentsOverridenDifficulty" );
		Talent = source.Talent;
		Difficulty = source.Difficulty;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DynamicQuestForTalentsOverridenDifficulty newParent = _newParent as DynamicQuestForTalentsOverridenDifficulty;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Talent.SetParent( newParent == null ? null : newParent._Talent );
		_Difficulty.SetParent( newParent == null ? null : newParent._Difficulty );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Talent.Reset();
		_Difficulty.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Talent.IsDerivedFromParent()
			&& _Difficulty.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Talent" )
			_Talent.Reset();
		else if ( fieldName == "Difficulty" )
			_Difficulty.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Talent" )
			return _Talent.IsDerivedFromParent();
		if ( fieldName == "Difficulty" )
			return _Difficulty.IsDerivedFromParent();
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

[IndexField("Talent")]
[Custom("Social")]
public class DynamicQuestForTalentsOverridenPrice : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DynamicQuestForTalentsOverridenPrice __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Talent> _Talent;
	private ResourcesTable _Resources;

	[Description( "Талант" )]
	public DBPtr<Talent> Talent { get { return _Talent.Get(); } set { _Talent.Set( value ); } }

	[Description( "Цена в ресурсах" )]
	public ResourcesTable Resources { get { return _Resources; } set { _Resources.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_Talent = new UndoRedoDBPtr<Talent>( owner );
		_Resources = new ResourcesTable( owner );
		_Talent.Changed += FireChangedEvent;
		_Resources.Changed += FireChangedEvent;
	}

	public DynamicQuestForTalentsOverridenPrice()
	{
		Initialize( GetOwner() );
	}

	public DynamicQuestForTalentsOverridenPrice( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DynamicQuestForTalentsOverridenPrice( DBResource owner, DynamicQuestForTalentsOverridenPrice source )
		: this(owner, source, true){}

	protected DynamicQuestForTalentsOverridenPrice( DBResource owner, DynamicQuestForTalentsOverridenPrice source, bool fireEvent )
	{
		_Talent = new UndoRedoDBPtr<Talent>( owner, source.Talent );
		_Resources = new ResourcesTable( owner, source.Resources );
		_Talent.Changed += FireChangedEvent;
		_Resources.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DynamicQuestForTalentsOverridenPrice source = _source as DynamicQuestForTalentsOverridenPrice;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DynamicQuestForTalentsOverridenPrice" );
		Talent = source.Talent;
		Resources = source.Resources;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DynamicQuestForTalentsOverridenPrice newParent = _newParent as DynamicQuestForTalentsOverridenPrice;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_Talent.SetParent( newParent == null ? null : newParent._Talent );
		_Resources.SetParent( newParent == null ? null : newParent._Resources );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_Talent.Reset();
		_Resources.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_Talent.IsDerivedFromParent()
			&& _Resources.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "Talent" )
			_Talent.Reset();
		else if ( fieldName == "Resources" )
			_Resources.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "Talent" )
			return _Talent.IsDerivedFromParent();
		if ( fieldName == "Resources" )
			return _Resources.IsDerivedFromParent();
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

[IndexField("ETalentRarity")]
[Custom("Social")]
public class DynamicQuestForTalentsPrice : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DynamicQuestForTalentsPrice __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<ETalentRarity> _ETalentRarity;
	private ResourcesTable _Resources;

	[Description( "Рарность для этой стоимости" )]
	public ETalentRarity ETalentRarity { get { return _ETalentRarity.Get(); } set { _ETalentRarity.Set( value ); } }

	[Description( "Цена в ресурсах" )]
	public ResourcesTable Resources { get { return _Resources; } set { _Resources.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_ETalentRarity = new UndoRedo<ETalentRarity>( owner, ETalentRarity.Class );
		_Resources = new ResourcesTable( owner );
		_ETalentRarity.Changed += FireChangedEvent;
		_Resources.Changed += FireChangedEvent;
	}

	public DynamicQuestForTalentsPrice()
	{
		Initialize( GetOwner() );
	}

	public DynamicQuestForTalentsPrice( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DynamicQuestForTalentsPrice( DBResource owner, DynamicQuestForTalentsPrice source )
		: this(owner, source, true){}

	protected DynamicQuestForTalentsPrice( DBResource owner, DynamicQuestForTalentsPrice source, bool fireEvent )
	{
		_ETalentRarity = new UndoRedo<ETalentRarity>( owner, source.ETalentRarity );
		_Resources = new ResourcesTable( owner, source.Resources );
		_ETalentRarity.Changed += FireChangedEvent;
		_Resources.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DynamicQuestForTalentsPrice source = _source as DynamicQuestForTalentsPrice;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DynamicQuestForTalentsPrice" );
		ETalentRarity = source.ETalentRarity;
		Resources = source.Resources;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DynamicQuestForTalentsPrice newParent = _newParent as DynamicQuestForTalentsPrice;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_ETalentRarity.SetParent( newParent == null ? null : newParent._ETalentRarity );
		_Resources.SetParent( newParent == null ? null : newParent._Resources );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_ETalentRarity.Reset();
		_Resources.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_ETalentRarity.IsDerivedFromParent()
			&& _Resources.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "ETalentRarity" )
			_ETalentRarity.Reset();
		else if ( fieldName == "Resources" )
			_Resources.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "ETalentRarity" )
			return _ETalentRarity.IsDerivedFromParent();
		if ( fieldName == "Resources" )
			return _Resources.IsDerivedFromParent();
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
public class DynamicQuestLampAward : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DynamicQuestLampAward __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _DbId;
	private UndoRedo<int> _Bonus;
	private UndoRedo<int> _Transactions;
	private UndoRedo<int> _Duration;

	public string DbId { get { return _DbId.Get(); } set { _DbId.Set( value ); } }

	public int Bonus { get { return _Bonus.Get(); } set { _Bonus.Set( value ); } }

	public int Transactions { get { return _Transactions.Get(); } set { _Transactions.Set( value ); } }

	public int Duration { get { return _Duration.Get(); } set { _Duration.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_DbId = new UndoRedo<string>( owner, string.Empty );
		_Bonus = new UndoRedo<int>( owner, 0 );
		_Transactions = new UndoRedo<int>( owner, 0 );
		_Duration = new UndoRedo<int>( owner, 0 );
		_DbId.Changed += FireChangedEvent;
		_Bonus.Changed += FireChangedEvent;
		_Transactions.Changed += FireChangedEvent;
		_Duration.Changed += FireChangedEvent;
	}

	public DynamicQuestLampAward()
	{
		Initialize( GetOwner() );
	}

	public DynamicQuestLampAward( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DynamicQuestLampAward( DBResource owner, DynamicQuestLampAward source )
		: this(owner, source, true){}

	protected DynamicQuestLampAward( DBResource owner, DynamicQuestLampAward source, bool fireEvent )
	{
		_DbId = new UndoRedo<string>( owner, source.DbId );
		_Bonus = new UndoRedo<int>( owner, source.Bonus );
		_Transactions = new UndoRedo<int>( owner, source.Transactions );
		_Duration = new UndoRedo<int>( owner, source.Duration );
		_DbId.Changed += FireChangedEvent;
		_Bonus.Changed += FireChangedEvent;
		_Transactions.Changed += FireChangedEvent;
		_Duration.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DynamicQuestLampAward source = _source as DynamicQuestLampAward;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DynamicQuestLampAward" );
		DbId = source.DbId;
		Bonus = source.Bonus;
		Transactions = source.Transactions;
		Duration = source.Duration;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DynamicQuestLampAward newParent = _newParent as DynamicQuestLampAward;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_DbId.SetParent( newParent == null ? null : newParent._DbId );
		_Bonus.SetParent( newParent == null ? null : newParent._Bonus );
		_Transactions.SetParent( newParent == null ? null : newParent._Transactions );
		_Duration.SetParent( newParent == null ? null : newParent._Duration );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_DbId.Reset();
		_Bonus.Reset();
		_Transactions.Reset();
		_Duration.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_DbId.IsDerivedFromParent()
			&& _Bonus.IsDerivedFromParent()
			&& _Transactions.IsDerivedFromParent()
			&& _Duration.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "DbId" )
			_DbId.Reset();
		else if ( fieldName == "Bonus" )
			_Bonus.Reset();
		else if ( fieldName == "Transactions" )
			_Transactions.Reset();
		else if ( fieldName == "Duration" )
			_Duration.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "DbId" )
			return _DbId.IsDerivedFromParent();
		if ( fieldName == "Bonus" )
			return _Bonus.IsDerivedFromParent();
		if ( fieldName == "Transactions" )
			return _Transactions.IsDerivedFromParent();
		if ( fieldName == "Duration" )
			return _Duration.IsDerivedFromParent();
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
public class DynamicQuestUpgradeHeroTalentsAward : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DynamicQuestUpgradeHeroTalentsAward __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _usesLeft;

	public int usesLeft { get { return _usesLeft.Get(); } set { _usesLeft.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_usesLeft = new UndoRedo<int>( owner, 0 );
		_usesLeft.Changed += FireChangedEvent;
	}

	public DynamicQuestUpgradeHeroTalentsAward()
	{
		Initialize( GetOwner() );
	}

	public DynamicQuestUpgradeHeroTalentsAward( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DynamicQuestUpgradeHeroTalentsAward( DBResource owner, DynamicQuestUpgradeHeroTalentsAward source )
		: this(owner, source, true){}

	protected DynamicQuestUpgradeHeroTalentsAward( DBResource owner, DynamicQuestUpgradeHeroTalentsAward source, bool fireEvent )
	{
		_usesLeft = new UndoRedo<int>( owner, source.usesLeft );
		_usesLeft.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DynamicQuestUpgradeHeroTalentsAward source = _source as DynamicQuestUpgradeHeroTalentsAward;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DynamicQuestUpgradeHeroTalentsAward" );
		usesLeft = source.usesLeft;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DynamicQuestUpgradeHeroTalentsAward newParent = _newParent as DynamicQuestUpgradeHeroTalentsAward;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_usesLeft.SetParent( newParent == null ? null : newParent._usesLeft );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_usesLeft.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_usesLeft.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "usesLeft" )
			_usesLeft.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "usesLeft" )
			return _usesLeft.IsDerivedFromParent();
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
public class Objective : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Objective __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<QuestCondition> _condition;
	private UndoRedo<bool> _incremental;
	private UndoRedo<bool> _showProgress;
	private UndoRedo<int> _value;
	private UndoRedo<int> _timeOutInMinutes;
	private UndoRedoDBPtr<ModelDataCondition> _autoCompleteCondition;
	private UndoRedo<bool> _showInUI;
	private TextRef _Text;
	private UndoRedoAssignableList<DBPtr<QuestAction>> _skip;
	private ResourcesTable _skipPrice;
	private UndoRedoDBPtr<RepeatableCondition> _repeatableCondition;
	private TextRef _InstantText;
	private UndoRedoAssignableList<DBPtr<ClientQuestAction>> _instant;
	private UndoRedoAssignableList<DBPtr<QuestAction>> _completeActions;
	private UndoRedo<int> _errorCode;

	public DBPtr<QuestCondition> condition { get { return _condition.Get(); } set { _condition.Set( value ); } }

	[Description( "Накапливать ли value в процессе проверки условия. Те если стоит True, то при повторном вычислении условия value увеличится, пока не достигнет значения в objective" )]
	public bool incremental { get { return _incremental.Get(); } set { _incremental.Set( value ); } }

	[Description( "показывать ли прогресс выполнения обжектива. Пример: 1/13" )]
	public bool showProgress { get { return _showProgress.Get(); } set { _showProgress.Set( value ); } }

	public int value { get { return _value.Get(); } set { _value.Set( value ); } }

	[Description( "Таймаут в минутах на изменение Value обжектива (актуально для накопительных условий)" )]
	public int timeOutInMinutes { get { return _timeOutInMinutes.Get(); } set { _timeOutInMinutes.Set( value ); } }

	public DBPtr<ModelDataCondition> autoCompleteCondition { get { return _autoCompleteCondition.Get(); } set { _autoCompleteCondition.Set( value ); } }

	public bool showInUI { get { return _showInUI.Get(); } set { _showInUI.Set( value ); } }

	[Description( "текст обжектива" )]
	public TextRef Text { get { return _Text; } set { _Text.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<QuestAction>> skip { get { return _skip; } set { _skip.Assign( value ); } }

	[Description( "Стоимость пропуска обжектива. 0, если обжектив нельзя пропустить" )]
	public ResourcesTable skipPrice { get { return _skipPrice; } set { _skipPrice.Assign( value ); } }

	[Description( "Повторяемое действие пока квест активен" )]
	public DBPtr<RepeatableCondition> repeatableCondition { get { return _repeatableCondition.Get(); } set { _repeatableCondition.Set( value ); } }

	[Description( "текст на кнопке быстроклика" )]
	public TextRef InstantText { get { return _InstantText; } set { _InstantText.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<ClientQuestAction>> instant { get { return _instant; } set { _instant.Assign( value ); } }

	[Description( "Дейсвтия, которые выполнятся при выполнении данного обжектива" )]
	public libdb.IChangeableList<DBPtr<QuestAction>> completeActions { get { return _completeActions; } set { _completeActions.Assign( value ); } }

	[Description( "Если мы послали try_complete_objective, а он не закомплитился, то вернем эту ошибку" )]
	public int errorCode { get { return _errorCode.Get(); } set { _errorCode.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_condition = new UndoRedoDBPtr<QuestCondition>( owner );
		_incremental = new UndoRedo<bool>( owner, false );
		_showProgress = new UndoRedo<bool>( owner, true );
		_value = new UndoRedo<int>( owner, 1 );
		_timeOutInMinutes = new UndoRedo<int>( owner, 0 );
		_autoCompleteCondition = new UndoRedoDBPtr<ModelDataCondition>( owner );
		_showInUI = new UndoRedo<bool>( owner, true );
		_Text = new TextRef( owner, new TextRef() );
		_skip = new UndoRedoAssignableList<DBPtr<QuestAction>>( owner );
		_skipPrice = new ResourcesTable( owner );
		_repeatableCondition = new UndoRedoDBPtr<RepeatableCondition>( owner );
		_InstantText = new TextRef( owner, new TextRef() );
		_instant = new UndoRedoAssignableList<DBPtr<ClientQuestAction>>( owner );
		_completeActions = new UndoRedoAssignableList<DBPtr<QuestAction>>( owner );
		_errorCode = new UndoRedo<int>( owner, 0 );
		_condition.Changed += FireChangedEvent;
		_incremental.Changed += FireChangedEvent;
		_showProgress.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		_timeOutInMinutes.Changed += FireChangedEvent;
		_autoCompleteCondition.Changed += FireChangedEvent;
		_showInUI.Changed += FireChangedEvent;
		_Text.Changed += FireChangedEvent;
		_skip.Changed += FireChangedEvent;
		_skipPrice.Changed += FireChangedEvent;
		_repeatableCondition.Changed += FireChangedEvent;
		_InstantText.Changed += FireChangedEvent;
		_instant.Changed += FireChangedEvent;
		_completeActions.Changed += FireChangedEvent;
		_errorCode.Changed += FireChangedEvent;
	}

	public Objective()
	{
		Initialize( GetOwner() );
	}

	public Objective( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Objective( DBResource owner, Objective source )
		: this(owner, source, true){}

	protected Objective( DBResource owner, Objective source, bool fireEvent )
	{
		_condition = new UndoRedoDBPtr<QuestCondition>( owner, source.condition );
		_incremental = new UndoRedo<bool>( owner, source.incremental );
		_showProgress = new UndoRedo<bool>( owner, source.showProgress );
		_value = new UndoRedo<int>( owner, source.value );
		_timeOutInMinutes = new UndoRedo<int>( owner, source.timeOutInMinutes );
		_autoCompleteCondition = new UndoRedoDBPtr<ModelDataCondition>( owner, source.autoCompleteCondition );
		_showInUI = new UndoRedo<bool>( owner, source.showInUI );
		_Text = new TextRef( owner, source.Text );
		_skip = new UndoRedoAssignableList<DBPtr<QuestAction>>( owner );
		_skip.Assign( source.skip );
		_skipPrice = new ResourcesTable( owner, source.skipPrice );
		_repeatableCondition = new UndoRedoDBPtr<RepeatableCondition>( owner, source.repeatableCondition );
		_InstantText = new TextRef( owner, source.InstantText );
		_instant = new UndoRedoAssignableList<DBPtr<ClientQuestAction>>( owner );
		_instant.Assign( source.instant );
		_completeActions = new UndoRedoAssignableList<DBPtr<QuestAction>>( owner );
		_completeActions.Assign( source.completeActions );
		_errorCode = new UndoRedo<int>( owner, source.errorCode );
		_condition.Changed += FireChangedEvent;
		_incremental.Changed += FireChangedEvent;
		_showProgress.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		_timeOutInMinutes.Changed += FireChangedEvent;
		_autoCompleteCondition.Changed += FireChangedEvent;
		_showInUI.Changed += FireChangedEvent;
		_Text.Changed += FireChangedEvent;
		_skip.Changed += FireChangedEvent;
		_skipPrice.Changed += FireChangedEvent;
		_repeatableCondition.Changed += FireChangedEvent;
		_InstantText.Changed += FireChangedEvent;
		_instant.Changed += FireChangedEvent;
		_completeActions.Changed += FireChangedEvent;
		_errorCode.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Objective source = _source as Objective;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Objective" );
		condition = source.condition;
		incremental = source.incremental;
		showProgress = source.showProgress;
		value = source.value;
		timeOutInMinutes = source.timeOutInMinutes;
		autoCompleteCondition = source.autoCompleteCondition;
		showInUI = source.showInUI;
		Text = source.Text;
		skip = source.skip;
		skipPrice = source.skipPrice;
		repeatableCondition = source.repeatableCondition;
		InstantText = source.InstantText;
		instant = source.instant;
		completeActions = source.completeActions;
		errorCode = source.errorCode;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Objective newParent = _newParent as Objective;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_condition.SetParent( newParent == null ? null : newParent._condition );
		_incremental.SetParent( newParent == null ? null : newParent._incremental );
		_showProgress.SetParent( newParent == null ? null : newParent._showProgress );
		_value.SetParent( newParent == null ? null : newParent._value );
		_timeOutInMinutes.SetParent( newParent == null ? null : newParent._timeOutInMinutes );
		_autoCompleteCondition.SetParent( newParent == null ? null : newParent._autoCompleteCondition );
		_showInUI.SetParent( newParent == null ? null : newParent._showInUI );
		_Text.SetParent( newParent == null ? null : newParent._Text );
		_skip.SetParent( newParent == null ? null : newParent._skip );
		_skipPrice.SetParent( newParent == null ? null : newParent._skipPrice );
		_repeatableCondition.SetParent( newParent == null ? null : newParent._repeatableCondition );
		_InstantText.SetParent( newParent == null ? null : newParent._InstantText );
		_instant.SetParent( newParent == null ? null : newParent._instant );
		_completeActions.SetParent( newParent == null ? null : newParent._completeActions );
		_errorCode.SetParent( newParent == null ? null : newParent._errorCode );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_condition.Reset();
		_incremental.Reset();
		_showProgress.Reset();
		_value.Reset();
		_timeOutInMinutes.Reset();
		_autoCompleteCondition.Reset();
		_showInUI.Reset();
		_Text.Reset();
		_skip.Reset();
		_skipPrice.Reset();
		_repeatableCondition.Reset();
		_InstantText.Reset();
		_instant.Reset();
		_completeActions.Reset();
		_errorCode.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_condition.IsDerivedFromParent()
			&& _incremental.IsDerivedFromParent()
			&& _showProgress.IsDerivedFromParent()
			&& _value.IsDerivedFromParent()
			&& _timeOutInMinutes.IsDerivedFromParent()
			&& _autoCompleteCondition.IsDerivedFromParent()
			&& _showInUI.IsDerivedFromParent()
			&& _Text.IsDerivedFromParent()
			&& _skip.IsDerivedFromParent()
			&& _skipPrice.IsDerivedFromParent()
			&& _repeatableCondition.IsDerivedFromParent()
			&& _InstantText.IsDerivedFromParent()
			&& _instant.IsDerivedFromParent()
			&& _completeActions.IsDerivedFromParent()
			&& _errorCode.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "condition" )
			_condition.Reset();
		else if ( fieldName == "incremental" )
			_incremental.Reset();
		else if ( fieldName == "showProgress" )
			_showProgress.Reset();
		else if ( fieldName == "value" )
			_value.Reset();
		else if ( fieldName == "timeOutInMinutes" )
			_timeOutInMinutes.Reset();
		else if ( fieldName == "autoCompleteCondition" )
			_autoCompleteCondition.Reset();
		else if ( fieldName == "showInUI" )
			_showInUI.Reset();
		else if ( fieldName == "Text" )
			_Text.Reset();
		else if ( fieldName == "skip" )
			_skip.Reset();
		else if ( fieldName == "skipPrice" )
			_skipPrice.Reset();
		else if ( fieldName == "repeatableCondition" )
			_repeatableCondition.Reset();
		else if ( fieldName == "InstantText" )
			_InstantText.Reset();
		else if ( fieldName == "instant" )
			_instant.Reset();
		else if ( fieldName == "completeActions" )
			_completeActions.Reset();
		else if ( fieldName == "errorCode" )
			_errorCode.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "condition" )
			return _condition.IsDerivedFromParent();
		if ( fieldName == "incremental" )
			return _incremental.IsDerivedFromParent();
		if ( fieldName == "showProgress" )
			return _showProgress.IsDerivedFromParent();
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
		if ( fieldName == "timeOutInMinutes" )
			return _timeOutInMinutes.IsDerivedFromParent();
		if ( fieldName == "autoCompleteCondition" )
			return _autoCompleteCondition.IsDerivedFromParent();
		if ( fieldName == "showInUI" )
			return _showInUI.IsDerivedFromParent();
		if ( fieldName == "Text" )
			return _Text.IsDerivedFromParent();
		if ( fieldName == "skip" )
			return _skip.IsDerivedFromParent();
		if ( fieldName == "skipPrice" )
			return _skipPrice.IsDerivedFromParent();
		if ( fieldName == "repeatableCondition" )
			return _repeatableCondition.IsDerivedFromParent();
		if ( fieldName == "InstantText" )
			return _InstantText.IsDerivedFromParent();
		if ( fieldName == "instant" )
			return _instant.IsDerivedFromParent();
		if ( fieldName == "completeActions" )
			return _completeActions.IsDerivedFromParent();
		if ( fieldName == "errorCode" )
			return _errorCode.IsDerivedFromParent();
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
public class Reward : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Reward __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _caption;
	private UndoRedoAssignableList<DBPtr<QuestAction>> _actions;

	[Description( "Текст кнопки с данным выбором" )]
	public TextRef caption { get { return _caption; } set { _caption.Assign( value ); } }

	[Description( "Список действий по этому выбору" )]
	public libdb.IChangeableList<DBPtr<QuestAction>> actions { get { return _actions; } set { _actions.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_caption = new TextRef( owner, new TextRef() );
		_actions = new UndoRedoAssignableList<DBPtr<QuestAction>>( owner );
		_caption.Changed += FireChangedEvent;
		_actions.Changed += FireChangedEvent;
	}

	public Reward()
	{
		Initialize( GetOwner() );
	}

	public Reward( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Reward( DBResource owner, Reward source )
		: this(owner, source, true){}

	protected Reward( DBResource owner, Reward source, bool fireEvent )
	{
		_caption = new TextRef( owner, source.caption );
		_actions = new UndoRedoAssignableList<DBPtr<QuestAction>>( owner );
		_actions.Assign( source.actions );
		_caption.Changed += FireChangedEvent;
		_actions.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Reward source = _source as Reward;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Reward" );
		caption = source.caption;
		actions = source.actions;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Reward newParent = _newParent as Reward;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_caption.SetParent( newParent == null ? null : newParent._caption );
		_actions.SetParent( newParent == null ? null : newParent._actions );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_caption.Reset();
		_actions.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& _actions.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "actions" )
			_actions.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "actions" )
			return _actions.IsDerivedFromParent();
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
public class RewardConstruction : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private RewardConstruction __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _level;
	private UndoRedoDBPtr<Constructon> _construction;

	[Description( "Уровень здания" )]
	public int level { get { return _level.Get(); } set { _level.Set( value ); } }

	[Description( "Здание в награду" )]
	public DBPtr<Constructon> construction { get { return _construction.Get(); } set { _construction.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_level = new UndoRedo<int>( owner, 0 );
		_construction = new UndoRedoDBPtr<Constructon>( owner );
		_level.Changed += FireChangedEvent;
		_construction.Changed += FireChangedEvent;
	}

	public RewardConstruction()
	{
		Initialize( GetOwner() );
	}

	public RewardConstruction( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public RewardConstruction( DBResource owner, RewardConstruction source )
		: this(owner, source, true){}

	protected RewardConstruction( DBResource owner, RewardConstruction source, bool fireEvent )
	{
		_level = new UndoRedo<int>( owner, source.level );
		_construction = new UndoRedoDBPtr<Constructon>( owner, source.construction );
		_level.Changed += FireChangedEvent;
		_construction.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		RewardConstruction source = _source as RewardConstruction;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RewardConstruction" );
		level = source.level;
		construction = source.construction;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		RewardConstruction newParent = _newParent as RewardConstruction;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_level.SetParent( newParent == null ? null : newParent._level );
		_construction.SetParent( newParent == null ? null : newParent._construction );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_level.Reset();
		_construction.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_level.IsDerivedFromParent()
			&& _construction.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "level" )
			_level.Reset();
		else if ( fieldName == "construction" )
			_construction.Reset();
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
		if ( fieldName == "construction" )
			return _construction.IsDerivedFromParent();
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
public class StatisticEventConditionItem : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private StatisticEventConditionItem __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<StatisticEventType> _eventType;
	private UndoRedo<string> _description;

	public StatisticEventType eventType { get { return _eventType.Get(); } set { _eventType.Set( value ); } }

	[Description( "Regex уточняющий действие" )]
	public string description { get { return _description.Get(); } set { _description.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_eventType = new UndoRedo<StatisticEventType>( owner, StatisticEventType.PRODUCTION_FINISH );
		_description = new UndoRedo<string>( owner, string.Empty );
		_eventType.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
	}

	public StatisticEventConditionItem()
	{
		Initialize( GetOwner() );
	}

	public StatisticEventConditionItem( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public StatisticEventConditionItem( DBResource owner, StatisticEventConditionItem source )
		: this(owner, source, true){}

	protected StatisticEventConditionItem( DBResource owner, StatisticEventConditionItem source, bool fireEvent )
	{
		_eventType = new UndoRedo<StatisticEventType>( owner, source.eventType );
		_description = new UndoRedo<string>( owner, source.description );
		_eventType.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		StatisticEventConditionItem source = _source as StatisticEventConditionItem;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatisticEventConditionItem" );
		eventType = source.eventType;
		description = source.description;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		StatisticEventConditionItem newParent = _newParent as StatisticEventConditionItem;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_eventType.SetParent( newParent == null ? null : newParent._eventType );
		_description.SetParent( newParent == null ? null : newParent._description );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_eventType.Reset();
		_description.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_eventType.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "eventType" )
			_eventType.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "eventType" )
			return _eventType.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
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

[IndexField("talent")]
[Custom("Social")]
public class TalentItem : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentItem __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Talent> _talent;

	public DBPtr<Talent> talent { get { return _talent.Get(); } set { _talent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_talent = new UndoRedoDBPtr<Talent>( owner );
		_talent.Changed += FireChangedEvent;
	}

	public TalentItem()
	{
		Initialize( GetOwner() );
	}

	public TalentItem( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentItem( DBResource owner, TalentItem source )
		: this(owner, source, true){}

	protected TalentItem( DBResource owner, TalentItem source, bool fireEvent )
	{
		_talent = new UndoRedoDBPtr<Talent>( owner, source.talent );
		_talent.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentItem source = _source as TalentItem;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentItem" );
		talent = source.talent;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentItem newParent = _newParent as TalentItem;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_talent.SetParent( newParent == null ? null : newParent._talent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_talent.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_talent.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "talent" )
			_talent.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "talent" )
			return _talent.IsDerivedFromParent();
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

[IndexField("title")]
[Custom("Social")]
public class TalentsRow : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentsRow __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _title;
	private UndoRedoAssignableList<TalentItem> _items;

	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	public libdb.IChangeableList<TalentItem> items { get { return _items; } set { _items.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_title = new TextRef( owner, new TextRef() );
		_items = new UndoRedoAssignableList<TalentItem>( owner );
		_title.Changed += FireChangedEvent;
		_items.Changed += FireChangedEvent;
	}

	public TalentsRow()
	{
		Initialize( GetOwner() );
	}

	public TalentsRow( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentsRow( DBResource owner, TalentsRow source )
		: this(owner, source, true){}

	protected TalentsRow( DBResource owner, TalentsRow source, bool fireEvent )
	{
		_title = new TextRef( owner, source.title );
		_items = new UndoRedoAssignableList<TalentItem>( owner );
		_items.Assign( source.items );
		_title.Changed += FireChangedEvent;
		_items.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentsRow source = _source as TalentsRow;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentsRow" );
		title = source.title;
		items = source.items;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentsRow newParent = _newParent as TalentsRow;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_title.SetParent( newParent == null ? null : newParent._title );
		_items.SetParent( newParent == null ? null : newParent._items );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_title.Reset();
		_items.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_title.IsDerivedFromParent()
			&& _items.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "items" )
			_items.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "title" )
			return _title.IsDerivedFromParent();
		if ( fieldName == "items" )
			return _items.IsDerivedFromParent();
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

[IndexField("title")]
[Custom("Social")]
public class TalentsColumn : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TalentsColumn __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _title;
	private UndoRedoDBPtr<Texture> _icon;
	private UndoRedo<bool> _isEventColumn;
	private UndoRedo<int> _rowsPerLine;
	private UndoRedoAssignableList<TalentsRow> _rows;

	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	public DBPtr<Texture> icon { get { return _icon.Get(); } set { _icon.Set( value ); } }

	public bool isEventColumn { get { return _isEventColumn.Get(); } set { _isEventColumn.Set( value ); } }

	public int rowsPerLine { get { return _rowsPerLine.Get(); } set { _rowsPerLine.Set( value ); } }

	public libdb.IChangeableList<TalentsRow> rows { get { return _rows; } set { _rows.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_title = new TextRef( owner, new TextRef() );
		_icon = new UndoRedoDBPtr<Texture>( owner );
		_isEventColumn = new UndoRedo<bool>( owner, false );
		_rowsPerLine = new UndoRedo<int>( owner, 0 );
		_rows = new UndoRedoAssignableList<TalentsRow>( owner );
		_title.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_isEventColumn.Changed += FireChangedEvent;
		_rowsPerLine.Changed += FireChangedEvent;
		_rows.Changed += FireChangedEvent;
	}

	public TalentsColumn()
	{
		Initialize( GetOwner() );
	}

	public TalentsColumn( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TalentsColumn( DBResource owner, TalentsColumn source )
		: this(owner, source, true){}

	protected TalentsColumn( DBResource owner, TalentsColumn source, bool fireEvent )
	{
		_title = new TextRef( owner, source.title );
		_icon = new UndoRedoDBPtr<Texture>( owner, source.icon );
		_isEventColumn = new UndoRedo<bool>( owner, source.isEventColumn );
		_rowsPerLine = new UndoRedo<int>( owner, source.rowsPerLine );
		_rows = new UndoRedoAssignableList<TalentsRow>( owner );
		_rows.Assign( source.rows );
		_title.Changed += FireChangedEvent;
		_icon.Changed += FireChangedEvent;
		_isEventColumn.Changed += FireChangedEvent;
		_rowsPerLine.Changed += FireChangedEvent;
		_rows.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TalentsColumn source = _source as TalentsColumn;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentsColumn" );
		title = source.title;
		icon = source.icon;
		isEventColumn = source.isEventColumn;
		rowsPerLine = source.rowsPerLine;
		rows = source.rows;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TalentsColumn newParent = _newParent as TalentsColumn;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_title.SetParent( newParent == null ? null : newParent._title );
		_icon.SetParent( newParent == null ? null : newParent._icon );
		_isEventColumn.SetParent( newParent == null ? null : newParent._isEventColumn );
		_rowsPerLine.SetParent( newParent == null ? null : newParent._rowsPerLine );
		_rows.SetParent( newParent == null ? null : newParent._rows );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_title.Reset();
		_icon.Reset();
		_isEventColumn.Reset();
		_rowsPerLine.Reset();
		_rows.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_title.IsDerivedFromParent()
			&& _icon.IsDerivedFromParent()
			&& _isEventColumn.IsDerivedFromParent()
			&& _rowsPerLine.IsDerivedFromParent()
			&& _rows.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "icon" )
			_icon.Reset();
		else if ( fieldName == "isEventColumn" )
			_isEventColumn.Reset();
		else if ( fieldName == "rowsPerLine" )
			_rowsPerLine.Reset();
		else if ( fieldName == "rows" )
			_rows.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "title" )
			return _title.IsDerivedFromParent();
		if ( fieldName == "icon" )
			return _icon.IsDerivedFromParent();
		if ( fieldName == "isEventColumn" )
			return _isEventColumn.IsDerivedFromParent();
		if ( fieldName == "rowsPerLine" )
			return _rowsPerLine.IsDerivedFromParent();
		if ( fieldName == "rows" )
			return _rows.IsDerivedFromParent();
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

[IndexField("title")]
[Custom("Social")]
public class TaletnsGrouping : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TaletnsGrouping __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _title;
	private UndoRedoAssignableList<TalentsColumn> _columns;

	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	public libdb.IChangeableList<TalentsColumn> columns { get { return _columns; } set { _columns.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_title = new TextRef( owner, new TextRef() );
		_columns = new UndoRedoAssignableList<TalentsColumn>( owner );
		_title.Changed += FireChangedEvent;
		_columns.Changed += FireChangedEvent;
	}

	public TaletnsGrouping()
	{
		Initialize( GetOwner() );
	}

	public TaletnsGrouping( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TaletnsGrouping( DBResource owner, TaletnsGrouping source )
		: this(owner, source, true){}

	protected TaletnsGrouping( DBResource owner, TaletnsGrouping source, bool fireEvent )
	{
		_title = new TextRef( owner, source.title );
		_columns = new UndoRedoAssignableList<TalentsColumn>( owner );
		_columns.Assign( source.columns );
		_title.Changed += FireChangedEvent;
		_columns.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TaletnsGrouping source = _source as TaletnsGrouping;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TaletnsGrouping" );
		title = source.title;
		columns = source.columns;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TaletnsGrouping newParent = _newParent as TaletnsGrouping;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_title.SetParent( newParent == null ? null : newParent._title );
		_columns.SetParent( newParent == null ? null : newParent._columns );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_title.Reset();
		_columns.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_title.IsDerivedFromParent()
			&& _columns.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "columns" )
			_columns.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "title" )
			return _title.IsDerivedFromParent();
		if ( fieldName == "columns" )
			return _columns.IsDerivedFromParent();
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

[IndexField("caption")]
[NonTerminal]
[Custom("Social")]
public class DialogBase : DBResource
{
	private UndoRedoDBPtr<DialogBase> ___parent;
	[HideInOutliner]
	public new DBPtr<DialogBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _caption;

	[NoCode]
	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DialogBase>(owner);
		_caption = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
	}

	public DialogBase()
	{
		Initialize( this );
	}
	private void AssignSelf( DialogBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DialogBase" );
		caption = source.caption;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DialogBase source = _source as DialogBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DialogBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DialogBase newParent = rawParent == null ? null : rawParent.Get<DialogBase>();
		if ( newParent == null && _newParent is DialogBase )
			newParent = _newParent as DialogBase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_caption.SetParent( newParent == null ? null : newParent._caption );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_caption.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
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
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class CastleDialog : DialogBase
{
	private UndoRedoDBPtr<CastleDialog> ___parent;
	[HideInOutliner]
	public new DBPtr<CastleDialog> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<Phrase> _phrasesA;
	private UndoRedoAssignableList<Phrase> _phrasesB;
	private TextRef _locationNameA;
	private TextRef _locationNameB;
	private UndoRedoDBPtr<Texture> _locationImageA;
	private UndoRedoDBPtr<Texture> _locationImageB;

	public libdb.IChangeableList<Phrase> phrasesA { get { return _phrasesA; } set { _phrasesA.Assign( value ); } }

	public libdb.IChangeableList<Phrase> phrasesB { get { return _phrasesB; } set { _phrasesB.Assign( value ); } }

	public TextRef locationNameA { get { return _locationNameA; } set { _locationNameA.Assign( value ); } }

	public TextRef locationNameB { get { return _locationNameB; } set { _locationNameB.Assign( value ); } }

	[Description( "location image for Docts quest" )]
	public DBPtr<Texture> locationImageA { get { return _locationImageA.Get(); } set { _locationImageA.Set( value ); } }

	[Description( "location image for Adornians quest" )]
	public DBPtr<Texture> locationImageB { get { return _locationImageB.Get(); } set { _locationImageB.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CastleDialog>(owner);
		_phrasesA = new UndoRedoAssignableList<Phrase>( owner );
		_phrasesB = new UndoRedoAssignableList<Phrase>( owner );
		_locationNameA = new TextRef( owner, new TextRef() );
		_locationNameB = new TextRef( owner, new TextRef() );
		_locationImageA = new UndoRedoDBPtr<Texture>( owner );
		_locationImageB = new UndoRedoDBPtr<Texture>( owner );
		___parent.Changed += FireChangedEvent;
		_phrasesA.Changed += FireChangedEvent;
		_phrasesB.Changed += FireChangedEvent;
		_locationNameA.Changed += FireChangedEvent;
		_locationNameB.Changed += FireChangedEvent;
		_locationImageA.Changed += FireChangedEvent;
		_locationImageB.Changed += FireChangedEvent;
	}

	public CastleDialog()
	{
		Initialize( this );
	}
	private void AssignSelf( CastleDialog source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CastleDialog" );
		phrasesA = source.phrasesA;
		phrasesB = source.phrasesB;
		locationNameA = source.locationNameA;
		locationNameB = source.locationNameB;
		locationImageA = source.locationImageA;
		locationImageB = source.locationImageB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CastleDialog source = _source as CastleDialog;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CastleDialog" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CastleDialog newParent = rawParent == null ? null : rawParent.Get<CastleDialog>();
		if ( newParent == null && _newParent is CastleDialog )
			newParent = _newParent as CastleDialog;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_phrasesA.SetParent( newParent == null ? null : newParent._phrasesA );
		_phrasesB.SetParent( newParent == null ? null : newParent._phrasesB );
		_locationNameA.SetParent( newParent == null ? null : newParent._locationNameA );
		_locationNameB.SetParent( newParent == null ? null : newParent._locationNameB );
		_locationImageA.SetParent( newParent == null ? null : newParent._locationImageA );
		_locationImageB.SetParent( newParent == null ? null : newParent._locationImageB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_phrasesA.Reset();
		_phrasesB.Reset();
		_locationNameA.Reset();
		_locationNameB.Reset();
		_locationImageA.Reset();
		_locationImageB.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_phrasesA.IsDerivedFromParent()
			&& _phrasesB.IsDerivedFromParent()
			&& _locationNameA.IsDerivedFromParent()
			&& _locationNameB.IsDerivedFromParent()
			&& _locationImageA.IsDerivedFromParent()
			&& _locationImageB.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "phrasesA" )
			_phrasesA.Reset();
		else if ( fieldName == "phrasesB" )
			_phrasesB.Reset();
		else if ( fieldName == "locationNameA" )
			_locationNameA.Reset();
		else if ( fieldName == "locationNameB" )
			_locationNameB.Reset();
		else if ( fieldName == "locationImageA" )
			_locationImageA.Reset();
		else if ( fieldName == "locationImageB" )
			_locationImageB.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "phrasesA" )
			return _phrasesA.IsDerivedFromParent();
		if ( fieldName == "phrasesB" )
			return _phrasesB.IsDerivedFromParent();
		if ( fieldName == "locationNameA" )
			return _locationNameA.IsDerivedFromParent();
		if ( fieldName == "locationNameB" )
			return _locationNameB.IsDerivedFromParent();
		if ( fieldName == "locationImageA" )
			return _locationImageA.IsDerivedFromParent();
		if ( fieldName == "locationImageB" )
			return _locationImageB.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[NonTerminal]
[Custom("Social")]
public class QuestAction : DBResource
{
	private UndoRedoDBPtr<QuestAction> ___parent;
	[HideInOutliner]
	public new DBPtr<QuestAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<GenderFractionFilter> _genderFractionFilter;

	[Description( "При выборе All - действие выполняется для всех без исключений, выбор какой-то одной из фракций или только одного из полов - означает ограничения выполнения действия только для игрока с данным полом/фракцией. Если выбрано оба пола или обе фракции - значит по этим характеристикам нет ограничений, равнозначно не выбору этих значений вовсе." )]
	public GenderFractionFilter genderFractionFilter { get { return _genderFractionFilter.Get(); } set { _genderFractionFilter.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<QuestAction>(owner);
		_genderFractionFilter = new UndoRedo<GenderFractionFilter>( owner, GenderFractionFilter.All );
		___parent.Changed += FireChangedEvent;
		_genderFractionFilter.Changed += FireChangedEvent;
	}

	public QuestAction()
	{
		Initialize( this );
	}
	private void AssignSelf( QuestAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for QuestAction" );
		genderFractionFilter = source.genderFractionFilter;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		QuestAction source = _source as QuestAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for QuestAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		QuestAction newParent = rawParent == null ? null : rawParent.Get<QuestAction>();
		if ( newParent == null && _newParent is QuestAction )
			newParent = _newParent as QuestAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_genderFractionFilter.SetParent( newParent == null ? null : newParent._genderFractionFilter );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_genderFractionFilter.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_genderFractionFilter.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "genderFractionFilter" )
			_genderFractionFilter.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "genderFractionFilter" )
			return _genderFractionFilter.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ChangeGroupMapAction : QuestAction
{
	private UndoRedoDBPtr<ChangeGroupMapAction> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeGroupMapAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<DBAdvMapDescGroup> _group;
	private UndoRedo<MapType> _type;
	private UndoRedo<bool> _isVisible;

	[Description( "Группа карт, которую проставить" )]
	public DBPtr<DBAdvMapDescGroup> group { get { return _group.Get(); } set { _group.Set( value ); } }

	[Description( "Тип режима (обучение, пвп, пве, эвент)" )]
	public MapType type { get { return _type.Get(); } set { _type.Set( value ); } }

	[Description( "Видна ли эта карта в отдельном слоте" )]
	public bool isVisible { get { return _isVisible.Get(); } set { _isVisible.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeGroupMapAction>(owner);
		_group = new UndoRedoDBPtr<DBAdvMapDescGroup>( owner );
		_type = new UndoRedo<MapType>( owner, MapType.Tutorial );
		_isVisible = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_group.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_isVisible.Changed += FireChangedEvent;
	}

	public ChangeGroupMapAction()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeGroupMapAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeGroupMapAction" );
		group = source.group;
		type = source.type;
		isVisible = source.isVisible;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeGroupMapAction source = _source as ChangeGroupMapAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeGroupMapAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeGroupMapAction newParent = rawParent == null ? null : rawParent.Get<ChangeGroupMapAction>();
		if ( newParent == null && _newParent is ChangeGroupMapAction )
			newParent = _newParent as ChangeGroupMapAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_group.SetParent( newParent == null ? null : newParent._group );
		_type.SetParent( newParent == null ? null : newParent._type );
		_isVisible.SetParent( newParent == null ? null : newParent._isVisible );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_group.Reset();
		_type.Reset();
		_isVisible.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_group.IsDerivedFromParent()
			&& _type.IsDerivedFromParent()
			&& _isVisible.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "group" )
			_group.Reset();
		else if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "isVisible" )
			_isVisible.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "group" )
			return _group.IsDerivedFromParent();
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "isVisible" )
			return _isVisible.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ChangeHeroEnergyAction : QuestAction
{
	private UndoRedoDBPtr<ChangeHeroEnergyAction> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeHeroEnergyAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Hero> _hero;
	private UndoRedo<int> _energy;
	private UndoRedo<EnergyChangeType> _changeType;

	[Description( "Герой, которому изменяют энергию" )]
	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	[Description( "Энергии добавить/удалить при отрицательном значении" )]
	public int energy { get { return _energy.Get(); } set { _energy.Set( value ); } }

	[Description( "Increment - добавить/вычесть указанное значение, Override - переопределить, AsTopValue - выставить порог сверху(уменьшить, если больше), AsBottomValue - сделать порог снизу (увеличить, если меньше)" )]
	public EnergyChangeType changeType { get { return _changeType.Get(); } set { _changeType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeHeroEnergyAction>(owner);
		_hero = new UndoRedoDBPtr<Hero>( owner );
		_energy = new UndoRedo<int>( owner, 0 );
		_changeType = new UndoRedo<EnergyChangeType>( owner, EnergyChangeType.Increment );
		___parent.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
		_energy.Changed += FireChangedEvent;
		_changeType.Changed += FireChangedEvent;
	}

	public ChangeHeroEnergyAction()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeHeroEnergyAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeHeroEnergyAction" );
		hero = source.hero;
		energy = source.energy;
		changeType = source.changeType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeHeroEnergyAction source = _source as ChangeHeroEnergyAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeHeroEnergyAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeHeroEnergyAction newParent = rawParent == null ? null : rawParent.Get<ChangeHeroEnergyAction>();
		if ( newParent == null && _newParent is ChangeHeroEnergyAction )
			newParent = _newParent as ChangeHeroEnergyAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_hero.SetParent( newParent == null ? null : newParent._hero );
		_energy.SetParent( newParent == null ? null : newParent._energy );
		_changeType.SetParent( newParent == null ? null : newParent._changeType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_hero.Reset();
		_energy.Reset();
		_changeType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_hero.IsDerivedFromParent()
			&& _energy.IsDerivedFromParent()
			&& _changeType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "hero" )
			_hero.Reset();
		else if ( fieldName == "energy" )
			_energy.Reset();
		else if ( fieldName == "changeType" )
			_changeType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		if ( fieldName == "energy" )
			return _energy.IsDerivedFromParent();
		if ( fieldName == "changeType" )
			return _changeType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ChangeMapAction : QuestAction
{
	private UndoRedoDBPtr<ChangeMapAction> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeMapAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<AdvMapDescription> _map;
	private UndoRedo<MapType> _type;
	private UndoRedo<bool> _isVisible;

	[Description( "Карта, которую проставить" )]
	public DBPtr<AdvMapDescription> map { get { return _map.Get(); } set { _map.Set( value ); } }

	[Description( "Тип режима (обучение, пвп, пве, эвент)" )]
	public MapType type { get { return _type.Get(); } set { _type.Set( value ); } }

	[Description( "Видна ли эта карта в отдельном слоте" )]
	public bool isVisible { get { return _isVisible.Get(); } set { _isVisible.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeMapAction>(owner);
		_map = new UndoRedoDBPtr<AdvMapDescription>( owner );
		_type = new UndoRedo<MapType>( owner, MapType.Tutorial );
		_isVisible = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_map.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
		_isVisible.Changed += FireChangedEvent;
	}

	public ChangeMapAction()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeMapAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeMapAction" );
		map = source.map;
		type = source.type;
		isVisible = source.isVisible;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeMapAction source = _source as ChangeMapAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeMapAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeMapAction newParent = rawParent == null ? null : rawParent.Get<ChangeMapAction>();
		if ( newParent == null && _newParent is ChangeMapAction )
			newParent = _newParent as ChangeMapAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_map.SetParent( newParent == null ? null : newParent._map );
		_type.SetParent( newParent == null ? null : newParent._type );
		_isVisible.SetParent( newParent == null ? null : newParent._isVisible );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_map.Reset();
		_type.Reset();
		_isVisible.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_map.IsDerivedFromParent()
			&& _type.IsDerivedFromParent()
			&& _isVisible.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "map" )
			_map.Reset();
		else if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "isVisible" )
			_isVisible.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "map" )
			return _map.IsDerivedFromParent();
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "isVisible" )
			return _isVisible.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ChangeTutorialStateAction : QuestAction
{
	private UndoRedoDBPtr<ChangeTutorialStateAction> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeTutorialStateAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<TutorialState> _state;

	[Description( "Состояние туториала" )]
	public TutorialState state { get { return _state.Get(); } set { _state.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeTutorialStateAction>(owner);
		_state = new UndoRedo<TutorialState>( owner, TutorialState.NotStarted );
		___parent.Changed += FireChangedEvent;
		_state.Changed += FireChangedEvent;
	}

	public ChangeTutorialStateAction()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeTutorialStateAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeTutorialStateAction" );
		state = source.state;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeTutorialStateAction source = _source as ChangeTutorialStateAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeTutorialStateAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeTutorialStateAction newParent = rawParent == null ? null : rawParent.Get<ChangeTutorialStateAction>();
		if ( newParent == null && _newParent is ChangeTutorialStateAction )
			newParent = _newParent as ChangeTutorialStateAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_state.SetParent( newParent == null ? null : newParent._state );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_state.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_state.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "state" )
			_state.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "state" )
			return _state.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[NonTerminal]
[Custom("Social")]
public class ClientQuestAction : QuestAction
{
	private UndoRedoDBPtr<ClientQuestAction> ___parent;
	[HideInOutliner]
	public new DBPtr<ClientQuestAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ClientQuestAction>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public ClientQuestAction()
	{
		Initialize( this );
	}
	private void AssignSelf( ClientQuestAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ClientQuestAction" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ClientQuestAction source = _source as ClientQuestAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ClientQuestAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ClientQuestAction newParent = rawParent == null ? null : rawParent.Get<ClientQuestAction>();
		if ( newParent == null && _newParent is ClientQuestAction )
			newParent = _newParent as ClientQuestAction;
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
public class CloseAllWindowAction : ClientQuestAction
{
	private UndoRedoDBPtr<CloseAllWindowAction> ___parent;
	[HideInOutliner]
	public new DBPtr<CloseAllWindowAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CloseAllWindowAction>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public CloseAllWindowAction()
	{
		Initialize( this );
	}
	private void AssignSelf( CloseAllWindowAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CloseAllWindowAction" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CloseAllWindowAction source = _source as CloseAllWindowAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CloseAllWindowAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CloseAllWindowAction newParent = rawParent == null ? null : rawParent.Get<CloseAllWindowAction>();
		if ( newParent == null && _newParent is CloseAllWindowAction )
			newParent = _newParent as CloseAllWindowAction;
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

[NonTerminal]
[Custom("Social")]
public class QuestCondition : DBResource
{
	private UndoRedoDBPtr<QuestCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<QuestCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<QuestCondition>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public QuestCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( QuestCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for QuestCondition" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		QuestCondition source = _source as QuestCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for QuestCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		QuestCondition newParent = rawParent == null ? null : rawParent.Get<QuestCondition>();
		if ( newParent == null && _newParent is QuestCondition )
			newParent = _newParent as QuestCondition;
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
public class CloseDarkenTutorialAction : ClientQuestAction
{
	private UndoRedoDBPtr<CloseDarkenTutorialAction> ___parent;
	[HideInOutliner]
	public new DBPtr<CloseDarkenTutorialAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CloseDarkenTutorialAction>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public CloseDarkenTutorialAction()
	{
		Initialize( this );
	}
	private void AssignSelf( CloseDarkenTutorialAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CloseDarkenTutorialAction" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CloseDarkenTutorialAction source = _source as CloseDarkenTutorialAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CloseDarkenTutorialAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CloseDarkenTutorialAction newParent = rawParent == null ? null : rawParent.Get<CloseDarkenTutorialAction>();
		if ( newParent == null && _newParent is CloseDarkenTutorialAction )
			newParent = _newParent as CloseDarkenTutorialAction;
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
public class CompleteObjectiveAction : ClientQuestAction
{
	private UndoRedoDBPtr<CompleteObjectiveAction> ___parent;
	[HideInOutliner]
	public new DBPtr<CompleteObjectiveAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CompleteObjectiveAction>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public CompleteObjectiveAction()
	{
		Initialize( this );
	}
	private void AssignSelf( CompleteObjectiveAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CompleteObjectiveAction" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CompleteObjectiveAction source = _source as CompleteObjectiveAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CompleteObjectiveAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CompleteObjectiveAction newParent = rawParent == null ? null : rawParent.Get<CompleteObjectiveAction>();
		if ( newParent == null && _newParent is CompleteObjectiveAction )
			newParent = _newParent as CompleteObjectiveAction;
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

[IndexField("sctiptName")]
[Custom("Social")]
public class Caption : DialogBase
{
	private UndoRedoDBPtr<Caption> ___parent;
	[HideInOutliner]
	public new DBPtr<Caption> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _sctiptName;
	private UndoRedo<float> _duration;
	private UndoRedo<PhraseTerminateEvent> _terminate;

	public string sctiptName { get { return _sctiptName.Get(); } set { _sctiptName.Set( value ); } }

	[Description( "Время реплики. Работает только для terminate = Time или TimeAndKey. Если -1 - совпадает с длительностью скрипта" )]
	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	[Description( "Событие по которому можно закончить реплику" )]
	public PhraseTerminateEvent terminate { get { return _terminate.Get(); } set { _terminate.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Caption>(owner);
		_sctiptName = new UndoRedo<string>( owner, string.Empty );
		_duration = new UndoRedo<float>( owner, -1.0f );
		_terminate = new UndoRedo<PhraseTerminateEvent>( owner, PhraseTerminateEvent.TimeAndKey );
		___parent.Changed += FireChangedEvent;
		_sctiptName.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_terminate.Changed += FireChangedEvent;
	}

	public Caption()
	{
		Initialize( this );
	}
	private void AssignSelf( Caption source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Caption" );
		sctiptName = source.sctiptName;
		duration = source.duration;
		terminate = source.terminate;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Caption source = _source as Caption;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Caption" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Caption newParent = rawParent == null ? null : rawParent.Get<Caption>();
		if ( newParent == null && _newParent is Caption )
			newParent = _newParent as Caption;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_sctiptName.SetParent( newParent == null ? null : newParent._sctiptName );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_terminate.SetParent( newParent == null ? null : newParent._terminate );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_sctiptName.Reset();
		_duration.Reset();
		_terminate.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_sctiptName.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _terminate.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "sctiptName" )
			_sctiptName.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "terminate" )
			_terminate.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "sctiptName" )
			return _sctiptName.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "terminate" )
			return _terminate.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("Title")]
[Custom("Social")]
public class DQuestForTalent : DBResource
{
	private UndoRedoDBPtr<DQuestForTalent> ___parent;
	[HideInOutliner]
	public new DBPtr<DQuestForTalent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _Title;
	private TextRef _Description;
	private UndoRedo<int> _Duration;
	private TextRef _NPCPortret;
	private UndoRedoAssignableList<DBDynamicObjective> _DynamicObjectives;
	private UndoRedoAssignableList<DBDynamicAward> _DynamicAwards;

	[Description( "Заголовок квеста" )]
	public TextRef Title { get { return _Title; } set { _Title.Assign( value ); } }

	[Description( "Что надо сделать" )]
	public TextRef Description { get { return _Description; } set { _Description.Assign( value ); } }

	[Description( "Длительность квеста (в секундах), стартует в тот момент, как добавили его" )]
	public int Duration { get { return _Duration.Get(); } set { _Duration.Set( value ); } }

	[Description( "Ccылка на картинку" )]
	public TextRef NPCPortret { get { return _NPCPortret; } set { _NPCPortret.Assign( value ); } }

	[Description( "Логика нужных действий" )]
	public libdb.IChangeableList<DBDynamicObjective> DynamicObjectives { get { return _DynamicObjectives; } set { _DynamicObjectives.Assign( value ); } }

	[Description( "Награды" )]
	public libdb.IChangeableList<DBDynamicAward> DynamicAwards { get { return _DynamicAwards; } set { _DynamicAwards.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DQuestForTalent>(owner);
		_Title = new TextRef( owner, new TextRef() );
		_Description = new TextRef( owner, new TextRef() );
		_Duration = new UndoRedo<int>( owner, 0 );
		_NPCPortret = new TextRef( owner, new TextRef() );
		_DynamicObjectives = new UndoRedoAssignableList<DBDynamicObjective>( owner );
		_DynamicAwards = new UndoRedoAssignableList<DBDynamicAward>( owner );
		___parent.Changed += FireChangedEvent;
		_Title.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
		_Duration.Changed += FireChangedEvent;
		_NPCPortret.Changed += FireChangedEvent;
		_DynamicObjectives.Changed += FireChangedEvent;
		_DynamicAwards.Changed += FireChangedEvent;
	}

	public DQuestForTalent()
	{
		Initialize( this );
	}
	private void AssignSelf( DQuestForTalent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DQuestForTalent" );
		Title = source.Title;
		Description = source.Description;
		Duration = source.Duration;
		NPCPortret = source.NPCPortret;
		DynamicObjectives = source.DynamicObjectives;
		DynamicAwards = source.DynamicAwards;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DQuestForTalent source = _source as DQuestForTalent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DQuestForTalent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DQuestForTalent newParent = rawParent == null ? null : rawParent.Get<DQuestForTalent>();
		if ( newParent == null && _newParent is DQuestForTalent )
			newParent = _newParent as DQuestForTalent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_Title.SetParent( newParent == null ? null : newParent._Title );
		_Description.SetParent( newParent == null ? null : newParent._Description );
		_Duration.SetParent( newParent == null ? null : newParent._Duration );
		_NPCPortret.SetParent( newParent == null ? null : newParent._NPCPortret );
		_DynamicObjectives.SetParent( newParent == null ? null : newParent._DynamicObjectives );
		_DynamicAwards.SetParent( newParent == null ? null : newParent._DynamicAwards );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_Title.Reset();
		_Description.Reset();
		_Duration.Reset();
		_NPCPortret.Reset();
		_DynamicObjectives.Reset();
		_DynamicAwards.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_Title.IsDerivedFromParent()
			&& _Description.IsDerivedFromParent()
			&& _Duration.IsDerivedFromParent()
			&& _NPCPortret.IsDerivedFromParent()
			&& _DynamicObjectives.IsDerivedFromParent()
			&& _DynamicAwards.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "Title" )
			_Title.Reset();
		else if ( fieldName == "Description" )
			_Description.Reset();
		else if ( fieldName == "Duration" )
			_Duration.Reset();
		else if ( fieldName == "NPCPortret" )
			_NPCPortret.Reset();
		else if ( fieldName == "DynamicObjectives" )
			_DynamicObjectives.Reset();
		else if ( fieldName == "DynamicAwards" )
			_DynamicAwards.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "Title" )
			return _Title.IsDerivedFromParent();
		if ( fieldName == "Description" )
			return _Description.IsDerivedFromParent();
		if ( fieldName == "Duration" )
			return _Duration.IsDerivedFromParent();
		if ( fieldName == "NPCPortret" )
			return _NPCPortret.IsDerivedFromParent();
		if ( fieldName == "DynamicObjectives" )
			return _DynamicObjectives.IsDerivedFromParent();
		if ( fieldName == "DynamicAwards" )
			return _DynamicAwards.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class DynamicQuestForTalents : DBResource
{
	private UndoRedoDBPtr<DynamicQuestForTalents> ___parent;
	[HideInOutliner]
	public new DBPtr<DynamicQuestForTalents> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<Talent>> _ForbadeTalents;
	private UndoRedoAssignableList<DynamicQuestForTalentsPrice> _PricesMap;
	private UndoRedoAssignableList<DynamicQuestForTalentsOverridenPrice> _OverridenPricesMap;
	private UndoRedoAssignableList<DynamicQuestForTalentsDifficulty> _DifficultiesMap;
	private UndoRedoAssignableList<DynamicQuestForTalentsOverridenDifficulty> _OverridenDifficultiesMap;
	private UndoRedoAssignableList<DQuestForTalentsGroup> _QuestsGroups;

	[Description( "Таланты, для которых не выдем квесты" )]
	public libdb.IChangeableList<DBPtr<Talent>> ForbadeTalents { get { return _ForbadeTalents; } set { _ForbadeTalents.Assign( value ); } }

	[Description( "Цены для рарностей" )]
	public libdb.IChangeableList<DynamicQuestForTalentsPrice> PricesMap { get { return _PricesMap; } set { _PricesMap.Assign( value ); } }

	[Description( "Перегрузка цен для талантов" )]
	public libdb.IChangeableList<DynamicQuestForTalentsOverridenPrice> OverridenPricesMap { get { return _OverridenPricesMap; } set { _OverridenPricesMap.Assign( value ); } }

	[Description( "Сложности для рарностей" )]
	public libdb.IChangeableList<DynamicQuestForTalentsDifficulty> DifficultiesMap { get { return _DifficultiesMap; } set { _DifficultiesMap.Assign( value ); } }

	[Description( "Перегрузка сложностей для талантов" )]
	public libdb.IChangeableList<DynamicQuestForTalentsOverridenDifficulty> OverridenDifficultiesMap { get { return _OverridenDifficultiesMap; } set { _OverridenDifficultiesMap.Assign( value ); } }

	[Description( "Группы квестов" )]
	public libdb.IChangeableList<DQuestForTalentsGroup> QuestsGroups { get { return _QuestsGroups; } set { _QuestsGroups.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DynamicQuestForTalents>(owner);
		_ForbadeTalents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_PricesMap = new UndoRedoAssignableList<DynamicQuestForTalentsPrice>( owner );
		_OverridenPricesMap = new UndoRedoAssignableList<DynamicQuestForTalentsOverridenPrice>( owner );
		_DifficultiesMap = new UndoRedoAssignableList<DynamicQuestForTalentsDifficulty>( owner );
		_OverridenDifficultiesMap = new UndoRedoAssignableList<DynamicQuestForTalentsOverridenDifficulty>( owner );
		_QuestsGroups = new UndoRedoAssignableList<DQuestForTalentsGroup>( owner );
		___parent.Changed += FireChangedEvent;
		_ForbadeTalents.Changed += FireChangedEvent;
		_PricesMap.Changed += FireChangedEvent;
		_OverridenPricesMap.Changed += FireChangedEvent;
		_DifficultiesMap.Changed += FireChangedEvent;
		_OverridenDifficultiesMap.Changed += FireChangedEvent;
		_QuestsGroups.Changed += FireChangedEvent;
	}

	public DynamicQuestForTalents()
	{
		Initialize( this );
	}
	private void AssignSelf( DynamicQuestForTalents source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DynamicQuestForTalents" );
		ForbadeTalents = source.ForbadeTalents;
		PricesMap = source.PricesMap;
		OverridenPricesMap = source.OverridenPricesMap;
		DifficultiesMap = source.DifficultiesMap;
		OverridenDifficultiesMap = source.OverridenDifficultiesMap;
		QuestsGroups = source.QuestsGroups;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DynamicQuestForTalents source = _source as DynamicQuestForTalents;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DynamicQuestForTalents" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DynamicQuestForTalents newParent = rawParent == null ? null : rawParent.Get<DynamicQuestForTalents>();
		if ( newParent == null && _newParent is DynamicQuestForTalents )
			newParent = _newParent as DynamicQuestForTalents;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_ForbadeTalents.SetParent( newParent == null ? null : newParent._ForbadeTalents );
		_PricesMap.SetParent( newParent == null ? null : newParent._PricesMap );
		_OverridenPricesMap.SetParent( newParent == null ? null : newParent._OverridenPricesMap );
		_DifficultiesMap.SetParent( newParent == null ? null : newParent._DifficultiesMap );
		_OverridenDifficultiesMap.SetParent( newParent == null ? null : newParent._OverridenDifficultiesMap );
		_QuestsGroups.SetParent( newParent == null ? null : newParent._QuestsGroups );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_ForbadeTalents.Reset();
		_PricesMap.Reset();
		_OverridenPricesMap.Reset();
		_DifficultiesMap.Reset();
		_OverridenDifficultiesMap.Reset();
		_QuestsGroups.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_ForbadeTalents.IsDerivedFromParent()
			&& _PricesMap.IsDerivedFromParent()
			&& _OverridenPricesMap.IsDerivedFromParent()
			&& _DifficultiesMap.IsDerivedFromParent()
			&& _OverridenDifficultiesMap.IsDerivedFromParent()
			&& _QuestsGroups.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "ForbadeTalents" )
			_ForbadeTalents.Reset();
		else if ( fieldName == "PricesMap" )
			_PricesMap.Reset();
		else if ( fieldName == "OverridenPricesMap" )
			_OverridenPricesMap.Reset();
		else if ( fieldName == "DifficultiesMap" )
			_DifficultiesMap.Reset();
		else if ( fieldName == "OverridenDifficultiesMap" )
			_OverridenDifficultiesMap.Reset();
		else if ( fieldName == "QuestsGroups" )
			_QuestsGroups.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "ForbadeTalents" )
			return _ForbadeTalents.IsDerivedFromParent();
		if ( fieldName == "PricesMap" )
			return _PricesMap.IsDerivedFromParent();
		if ( fieldName == "OverridenPricesMap" )
			return _OverridenPricesMap.IsDerivedFromParent();
		if ( fieldName == "DifficultiesMap" )
			return _DifficultiesMap.IsDerivedFromParent();
		if ( fieldName == "OverridenDifficultiesMap" )
			return _OverridenDifficultiesMap.IsDerivedFromParent();
		if ( fieldName == "QuestsGroups" )
			return _QuestsGroups.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class FinishSessionCondition : QuestCondition
{
	private UndoRedoDBPtr<FinishSessionCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<FinishSessionCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<FinsihSessionResult> _result;
	private UndoRedoAssignableList<DBPtr<AdvMapDescription>> _maps;

	[Description( "Результат по возвращению" )]
	public FinsihSessionResult result { get { return _result.Get(); } set { _result.Set( value ); } }

	[Description( "Список карт, любую из которых надо завершить. Пустой список - любая карта" )]
	public libdb.IChangeableList<DBPtr<AdvMapDescription>> maps { get { return _maps; } set { _maps.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<FinishSessionCondition>(owner);
		_result = new UndoRedo<FinsihSessionResult>( owner, FinsihSessionResult.DontCare );
		_maps = new UndoRedoAssignableList<DBPtr<AdvMapDescription>>( owner );
		___parent.Changed += FireChangedEvent;
		_result.Changed += FireChangedEvent;
		_maps.Changed += FireChangedEvent;
	}

	public FinishSessionCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( FinishSessionCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for FinishSessionCondition" );
		result = source.result;
		maps = source.maps;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		FinishSessionCondition source = _source as FinishSessionCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FinishSessionCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		FinishSessionCondition newParent = rawParent == null ? null : rawParent.Get<FinishSessionCondition>();
		if ( newParent == null && _newParent is FinishSessionCondition )
			newParent = _newParent as FinishSessionCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_result.SetParent( newParent == null ? null : newParent._result );
		_maps.SetParent( newParent == null ? null : newParent._maps );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_result.Reset();
		_maps.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_result.IsDerivedFromParent()
			&& _maps.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "result" )
			_result.Reset();
		else if ( fieldName == "maps" )
			_maps.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "result" )
			return _result.IsDerivedFromParent();
		if ( fieldName == "maps" )
			return _maps.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GiveFreeSkipsAction : QuestAction
{
	private UndoRedoDBPtr<GiveFreeSkipsAction> ___parent;
	[HideInOutliner]
	public new DBPtr<GiveFreeSkipsAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _skipsCount;
	private UndoRedo<string> _buildingName;

	[Description( "Количество бесплатных скипов" )]
	public int skipsCount { get { return _skipsCount.Get(); } set { _skipsCount.Set( value ); } }

	[Description( "PersistentID здания, для которого действуют скипы" )]
	public string buildingName { get { return _buildingName.Get(); } set { _buildingName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GiveFreeSkipsAction>(owner);
		_skipsCount = new UndoRedo<int>( owner, 0 );
		_buildingName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_skipsCount.Changed += FireChangedEvent;
		_buildingName.Changed += FireChangedEvent;
	}

	public GiveFreeSkipsAction()
	{
		Initialize( this );
	}
	private void AssignSelf( GiveFreeSkipsAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GiveFreeSkipsAction" );
		skipsCount = source.skipsCount;
		buildingName = source.buildingName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GiveFreeSkipsAction source = _source as GiveFreeSkipsAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GiveFreeSkipsAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GiveFreeSkipsAction newParent = rawParent == null ? null : rawParent.Get<GiveFreeSkipsAction>();
		if ( newParent == null && _newParent is GiveFreeSkipsAction )
			newParent = _newParent as GiveFreeSkipsAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_skipsCount.SetParent( newParent == null ? null : newParent._skipsCount );
		_buildingName.SetParent( newParent == null ? null : newParent._buildingName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_skipsCount.Reset();
		_buildingName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_skipsCount.IsDerivedFromParent()
			&& _buildingName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "skipsCount" )
			_skipsCount.Reset();
		else if ( fieldName == "buildingName" )
			_buildingName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "skipsCount" )
			return _skipsCount.IsDerivedFromParent();
		if ( fieldName == "buildingName" )
			return _buildingName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GiveGoldenLampAction : QuestAction
{
	private UndoRedoDBPtr<GiveGoldenLampAction> ___parent;
	[HideInOutliner]
	public new DBPtr<GiveGoldenLampAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<GoldLampEvent> _lampEventInfo;
	private UndoRedo<int> _duration;
	private UndoRedo<int> _bonus;
	private UndoRedo<int> _unsoulbounds;

	[Description( "Ссылка на тип руны" )]
	public DBPtr<GoldLampEvent> lampEventInfo { get { return _lampEventInfo.Get(); } set { _lampEventInfo.Set( value ); } }

	[Description( "Длительность" )]
	public int duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	[Description( "Максимальный бонус золота" )]
	public int bonus { get { return _bonus.Get(); } set { _bonus.Set( value ); } }

	[Description( "Кол-во отвязок" )]
	public int unsoulbounds { get { return _unsoulbounds.Get(); } set { _unsoulbounds.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GiveGoldenLampAction>(owner);
		_lampEventInfo = new UndoRedoDBPtr<GoldLampEvent>( owner );
		_duration = new UndoRedo<int>( owner, 0 );
		_bonus = new UndoRedo<int>( owner, 0 );
		_unsoulbounds = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_lampEventInfo.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_bonus.Changed += FireChangedEvent;
		_unsoulbounds.Changed += FireChangedEvent;
	}

	public GiveGoldenLampAction()
	{
		Initialize( this );
	}
	private void AssignSelf( GiveGoldenLampAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GiveGoldenLampAction" );
		lampEventInfo = source.lampEventInfo;
		duration = source.duration;
		bonus = source.bonus;
		unsoulbounds = source.unsoulbounds;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GiveGoldenLampAction source = _source as GiveGoldenLampAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GiveGoldenLampAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GiveGoldenLampAction newParent = rawParent == null ? null : rawParent.Get<GiveGoldenLampAction>();
		if ( newParent == null && _newParent is GiveGoldenLampAction )
			newParent = _newParent as GiveGoldenLampAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_lampEventInfo.SetParent( newParent == null ? null : newParent._lampEventInfo );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_bonus.SetParent( newParent == null ? null : newParent._bonus );
		_unsoulbounds.SetParent( newParent == null ? null : newParent._unsoulbounds );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_lampEventInfo.Reset();
		_duration.Reset();
		_bonus.Reset();
		_unsoulbounds.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_lampEventInfo.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _bonus.IsDerivedFromParent()
			&& _unsoulbounds.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "lampEventInfo" )
			_lampEventInfo.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "bonus" )
			_bonus.Reset();
		else if ( fieldName == "unsoulbounds" )
			_unsoulbounds.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "lampEventInfo" )
			return _lampEventInfo.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "bonus" )
			return _bonus.IsDerivedFromParent();
		if ( fieldName == "unsoulbounds" )
			return _unsoulbounds.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GiveHeroExpAction : QuestAction
{
	private UndoRedoDBPtr<GiveHeroExpAction> ___parent;
	[HideInOutliner]
	public new DBPtr<GiveHeroExpAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Hero> _hero;
	private UndoRedo<int> _exp;

	[Description( "Герой, которому выдают опыт" )]
	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	[Description( "Количество опыта для героя" )]
	public int exp { get { return _exp.Get(); } set { _exp.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GiveHeroExpAction>(owner);
		_hero = new UndoRedoDBPtr<Hero>( owner );
		_exp = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
		_exp.Changed += FireChangedEvent;
	}

	public GiveHeroExpAction()
	{
		Initialize( this );
	}
	private void AssignSelf( GiveHeroExpAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GiveHeroExpAction" );
		hero = source.hero;
		exp = source.exp;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GiveHeroExpAction source = _source as GiveHeroExpAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GiveHeroExpAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GiveHeroExpAction newParent = rawParent == null ? null : rawParent.Get<GiveHeroExpAction>();
		if ( newParent == null && _newParent is GiveHeroExpAction )
			newParent = _newParent as GiveHeroExpAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_hero.SetParent( newParent == null ? null : newParent._hero );
		_exp.SetParent( newParent == null ? null : newParent._exp );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_hero.Reset();
		_exp.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_hero.IsDerivedFromParent()
			&& _exp.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "hero" )
			_hero.Reset();
		else if ( fieldName == "exp" )
			_exp.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		if ( fieldName == "exp" )
			return _exp.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GiveRewardAction : QuestAction
{
	private UndoRedoDBPtr<GiveRewardAction> ___parent;
	[HideInOutliner]
	public new DBPtr<GiveRewardAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private ResourcesTable _resources;
	private UndoRedo<int> _fame;
	private UndoRedoAssignableList<DBPtr<Hero>> _heroes;
	private UndoRedoAssignableList<DBPtr<Hero>> _heroesForRandomPick;
	private UndoRedoAssignableList<DBPtr<Talent>> _talents;
	private UndoRedoDBPtr<Hero> _defaultTalentsSoulboundMale;
	private UndoRedoDBPtr<Hero> _defaultTalentsSoulboundFemale;
	private UndoRedoAssignableList<RewardConstruction> _constructions;
	private UndoRedo<int> _daysForPremiumAcc;

	public ResourcesTable resources { get { return _resources; } set { _resources.Assign( value ); } }

	public int fame { get { return _fame.Get(); } set { _fame.Set( value ); } }

	[Description( "Список героев, которые гарантированно выдадутся игроку в качестве награды" )]
	public libdb.IChangeableList<DBPtr<Hero>> heroes { get { return _heroes; } set { _heroes.Assign( value ); } }

	[Description( "Список героев, один из которых выберется случайным образом для выдачи в награду" )]
	public libdb.IChangeableList<DBPtr<Hero>> heroesForRandomPick { get { return _heroesForRandomPick; } set { _heroesForRandomPick.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<Talent>> talents { get { return _talents; } set { _talents.Assign( value ); } }

	[Description( "Для игроков-мальчиков (или по умолчанию): Если этот Action выдает таланты и у игрока есть герой, указанный в этом поле, то выдаваемые таланты будут привязаны к нему." )]
	public DBPtr<Hero> defaultTalentsSoulboundMale { get { return _defaultTalentsSoulboundMale.Get(); } set { _defaultTalentsSoulboundMale.Set( value ); } }

	[Description( "Для игроков-девочек: Если этот Action выдает таланты и у игрока есть герой, указанный в этом поле, то выдаваемые таланты будут привязаны к нему." )]
	public DBPtr<Hero> defaultTalentsSoulboundFemale { get { return _defaultTalentsSoulboundFemale.Get(); } set { _defaultTalentsSoulboundFemale.Set( value ); } }

	public libdb.IChangeableList<RewardConstruction> constructions { get { return _constructions; } set { _constructions.Assign( value ); } }

	public int daysForPremiumAcc { get { return _daysForPremiumAcc.Get(); } set { _daysForPremiumAcc.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GiveRewardAction>(owner);
		_resources = new ResourcesTable( owner );
		_fame = new UndoRedo<int>( owner, 0 );
		_heroes = new UndoRedoAssignableList<DBPtr<Hero>>( owner );
		_heroesForRandomPick = new UndoRedoAssignableList<DBPtr<Hero>>( owner );
		_talents = new UndoRedoAssignableList<DBPtr<Talent>>( owner );
		_defaultTalentsSoulboundMale = new UndoRedoDBPtr<Hero>( owner );
		_defaultTalentsSoulboundFemale = new UndoRedoDBPtr<Hero>( owner );
		_constructions = new UndoRedoAssignableList<RewardConstruction>( owner );
		_daysForPremiumAcc = new UndoRedo<int>( owner, 0 );
		___parent.Changed += FireChangedEvent;
		_resources.Changed += FireChangedEvent;
		_fame.Changed += FireChangedEvent;
		_heroes.Changed += FireChangedEvent;
		_heroesForRandomPick.Changed += FireChangedEvent;
		_talents.Changed += FireChangedEvent;
		_defaultTalentsSoulboundMale.Changed += FireChangedEvent;
		_defaultTalentsSoulboundFemale.Changed += FireChangedEvent;
		_constructions.Changed += FireChangedEvent;
		_daysForPremiumAcc.Changed += FireChangedEvent;
	}

	public GiveRewardAction()
	{
		Initialize( this );
	}
	private void AssignSelf( GiveRewardAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GiveRewardAction" );
		resources = source.resources;
		fame = source.fame;
		heroes = source.heroes;
		heroesForRandomPick = source.heroesForRandomPick;
		talents = source.talents;
		defaultTalentsSoulboundMale = source.defaultTalentsSoulboundMale;
		defaultTalentsSoulboundFemale = source.defaultTalentsSoulboundFemale;
		constructions = source.constructions;
		daysForPremiumAcc = source.daysForPremiumAcc;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GiveRewardAction source = _source as GiveRewardAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GiveRewardAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GiveRewardAction newParent = rawParent == null ? null : rawParent.Get<GiveRewardAction>();
		if ( newParent == null && _newParent is GiveRewardAction )
			newParent = _newParent as GiveRewardAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_resources.SetParent( newParent == null ? null : newParent._resources );
		_fame.SetParent( newParent == null ? null : newParent._fame );
		_heroes.SetParent( newParent == null ? null : newParent._heroes );
		_heroesForRandomPick.SetParent( newParent == null ? null : newParent._heroesForRandomPick );
		_talents.SetParent( newParent == null ? null : newParent._talents );
		_defaultTalentsSoulboundMale.SetParent( newParent == null ? null : newParent._defaultTalentsSoulboundMale );
		_defaultTalentsSoulboundFemale.SetParent( newParent == null ? null : newParent._defaultTalentsSoulboundFemale );
		_constructions.SetParent( newParent == null ? null : newParent._constructions );
		_daysForPremiumAcc.SetParent( newParent == null ? null : newParent._daysForPremiumAcc );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_resources.Reset();
		_fame.Reset();
		_heroes.Reset();
		_heroesForRandomPick.Reset();
		_talents.Reset();
		_defaultTalentsSoulboundMale.Reset();
		_defaultTalentsSoulboundFemale.Reset();
		_constructions.Reset();
		_daysForPremiumAcc.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_resources.IsDerivedFromParent()
			&& _fame.IsDerivedFromParent()
			&& _heroes.IsDerivedFromParent()
			&& _heroesForRandomPick.IsDerivedFromParent()
			&& _talents.IsDerivedFromParent()
			&& _defaultTalentsSoulboundMale.IsDerivedFromParent()
			&& _defaultTalentsSoulboundFemale.IsDerivedFromParent()
			&& _constructions.IsDerivedFromParent()
			&& _daysForPremiumAcc.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "resources" )
			_resources.Reset();
		else if ( fieldName == "fame" )
			_fame.Reset();
		else if ( fieldName == "heroes" )
			_heroes.Reset();
		else if ( fieldName == "heroesForRandomPick" )
			_heroesForRandomPick.Reset();
		else if ( fieldName == "talents" )
			_talents.Reset();
		else if ( fieldName == "defaultTalentsSoulboundMale" )
			_defaultTalentsSoulboundMale.Reset();
		else if ( fieldName == "defaultTalentsSoulboundFemale" )
			_defaultTalentsSoulboundFemale.Reset();
		else if ( fieldName == "constructions" )
			_constructions.Reset();
		else if ( fieldName == "daysForPremiumAcc" )
			_daysForPremiumAcc.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "resources" )
			return _resources.IsDerivedFromParent();
		if ( fieldName == "fame" )
			return _fame.IsDerivedFromParent();
		if ( fieldName == "heroes" )
			return _heroes.IsDerivedFromParent();
		if ( fieldName == "heroesForRandomPick" )
			return _heroesForRandomPick.IsDerivedFromParent();
		if ( fieldName == "talents" )
			return _talents.IsDerivedFromParent();
		if ( fieldName == "defaultTalentsSoulboundMale" )
			return _defaultTalentsSoulboundMale.IsDerivedFromParent();
		if ( fieldName == "defaultTalentsSoulboundFemale" )
			return _defaultTalentsSoulboundFemale.IsDerivedFromParent();
		if ( fieldName == "constructions" )
			return _constructions.IsDerivedFromParent();
		if ( fieldName == "daysForPremiumAcc" )
			return _daysForPremiumAcc.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class GiveUpgradeHeroTalentsEventAction : QuestAction
{
	private UndoRedoDBPtr<GiveUpgradeHeroTalentsEventAction> ___parent;
	[HideInOutliner]
	public new DBPtr<GiveUpgradeHeroTalentsEventAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _count;

	[Description( "Кол-во рун чемпиона которое надо выдать в награду" )]
	public int count { get { return _count.Get(); } set { _count.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GiveUpgradeHeroTalentsEventAction>(owner);
		_count = new UndoRedo<int>( owner, 1 );
		___parent.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
	}

	public GiveUpgradeHeroTalentsEventAction()
	{
		Initialize( this );
	}
	private void AssignSelf( GiveUpgradeHeroTalentsEventAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GiveUpgradeHeroTalentsEventAction" );
		count = source.count;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GiveUpgradeHeroTalentsEventAction source = _source as GiveUpgradeHeroTalentsEventAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GiveUpgradeHeroTalentsEventAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GiveUpgradeHeroTalentsEventAction newParent = rawParent == null ? null : rawParent.Get<GiveUpgradeHeroTalentsEventAction>();
		if ( newParent == null && _newParent is GiveUpgradeHeroTalentsEventAction )
			newParent = _newParent as GiveUpgradeHeroTalentsEventAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

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
		if ( __parent == null || __parent.Get() == null )
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
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
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

[NonTerminal]
[Custom("Social")]
public class HighlightAction : ClientQuestAction
{
	private UndoRedoDBPtr<HighlightAction> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightAction>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public HighlightAction()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightAction" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightAction source = _source as HighlightAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightAction newParent = rawParent == null ? null : rawParent.Get<HighlightAction>();
		if ( newParent == null && _newParent is HighlightAction )
			newParent = _newParent as HighlightAction;
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
public class HighlightAndOpenBathSlot : HighlightAction
{
	private UndoRedoDBPtr<HighlightAndOpenBathSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightAndOpenBathSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightAndOpenBathSlot>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public HighlightAndOpenBathSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightAndOpenBathSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenBathSlot" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightAndOpenBathSlot source = _source as HighlightAndOpenBathSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenBathSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightAndOpenBathSlot newParent = rawParent == null ? null : rawParent.Get<HighlightAndOpenBathSlot>();
		if ( newParent == null && _newParent is HighlightAndOpenBathSlot )
			newParent = _newParent as HighlightAndOpenBathSlot;
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
public class HighlightAndOpenBoostButton : HighlightAction
{
	private UndoRedoDBPtr<HighlightAndOpenBoostButton> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightAndOpenBoostButton> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _windowName;

	public string windowName { get { return _windowName.Get(); } set { _windowName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightAndOpenBoostButton>(owner);
		_windowName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_windowName.Changed += FireChangedEvent;
	}

	public HighlightAndOpenBoostButton()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightAndOpenBoostButton source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenBoostButton" );
		windowName = source.windowName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightAndOpenBoostButton source = _source as HighlightAndOpenBoostButton;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenBoostButton" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightAndOpenBoostButton newParent = rawParent == null ? null : rawParent.Get<HighlightAndOpenBoostButton>();
		if ( newParent == null && _newParent is HighlightAndOpenBoostButton )
			newParent = _newParent as HighlightAndOpenBoostButton;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_windowName.SetParent( newParent == null ? null : newParent._windowName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_windowName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_windowName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "windowName" )
			_windowName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "windowName" )
			return _windowName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HighlightAndOpenBuildingUpgradeAction : HighlightAction
{
	private UndoRedoDBPtr<HighlightAndOpenBuildingUpgradeAction> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightAndOpenBuildingUpgradeAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _windowName;

	public string windowName { get { return _windowName.Get(); } set { _windowName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightAndOpenBuildingUpgradeAction>(owner);
		_windowName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_windowName.Changed += FireChangedEvent;
	}

	public HighlightAndOpenBuildingUpgradeAction()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightAndOpenBuildingUpgradeAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenBuildingUpgradeAction" );
		windowName = source.windowName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightAndOpenBuildingUpgradeAction source = _source as HighlightAndOpenBuildingUpgradeAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenBuildingUpgradeAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightAndOpenBuildingUpgradeAction newParent = rawParent == null ? null : rawParent.Get<HighlightAndOpenBuildingUpgradeAction>();
		if ( newParent == null && _newParent is HighlightAndOpenBuildingUpgradeAction )
			newParent = _newParent as HighlightAndOpenBuildingUpgradeAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_windowName.SetParent( newParent == null ? null : newParent._windowName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_windowName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_windowName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "windowName" )
			_windowName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "windowName" )
			return _windowName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HighlightAndOpenFriendSlot : HighlightAction
{
	private UndoRedoDBPtr<HighlightAndOpenFriendSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightAndOpenFriendSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _windowName;

	public string windowName { get { return _windowName.Get(); } set { _windowName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightAndOpenFriendSlot>(owner);
		_windowName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_windowName.Changed += FireChangedEvent;
	}

	public HighlightAndOpenFriendSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightAndOpenFriendSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenFriendSlot" );
		windowName = source.windowName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightAndOpenFriendSlot source = _source as HighlightAndOpenFriendSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenFriendSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightAndOpenFriendSlot newParent = rawParent == null ? null : rawParent.Get<HighlightAndOpenFriendSlot>();
		if ( newParent == null && _newParent is HighlightAndOpenFriendSlot )
			newParent = _newParent as HighlightAndOpenFriendSlot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_windowName.SetParent( newParent == null ? null : newParent._windowName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_windowName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_windowName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "windowName" )
			_windowName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "windowName" )
			return _windowName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HighlightAndOpenTransmutationSlot : HighlightAction
{
	private UndoRedoDBPtr<HighlightAndOpenTransmutationSlot> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightAndOpenTransmutationSlot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightAndOpenTransmutationSlot>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public HighlightAndOpenTransmutationSlot()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightAndOpenTransmutationSlot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenTransmutationSlot" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightAndOpenTransmutationSlot source = _source as HighlightAndOpenTransmutationSlot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightAndOpenTransmutationSlot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightAndOpenTransmutationSlot newParent = rawParent == null ? null : rawParent.Get<HighlightAndOpenTransmutationSlot>();
		if ( newParent == null && _newParent is HighlightAndOpenTransmutationSlot )
			newParent = _newParent as HighlightAndOpenTransmutationSlot;
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
public class HighlightContructionAction : HighlightAction
{
	private UndoRedoDBPtr<HighlightContructionAction> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightContructionAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Constructon> _construction;

	public DBPtr<Constructon> construction { get { return _construction.Get(); } set { _construction.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightContructionAction>(owner);
		_construction = new UndoRedoDBPtr<Constructon>( owner );
		___parent.Changed += FireChangedEvent;
		_construction.Changed += FireChangedEvent;
	}

	public HighlightContructionAction()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightContructionAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightContructionAction" );
		construction = source.construction;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightContructionAction source = _source as HighlightContructionAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightContructionAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightContructionAction newParent = rawParent == null ? null : rawParent.Get<HighlightContructionAction>();
		if ( newParent == null && _newParent is HighlightContructionAction )
			newParent = _newParent as HighlightContructionAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_construction.SetParent( newParent == null ? null : newParent._construction );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_construction.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_construction.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "construction" )
			_construction.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "construction" )
			return _construction.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HighlightContructionInPocketAction : HighlightAction
{
	private UndoRedoDBPtr<HighlightContructionInPocketAction> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightContructionInPocketAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Constructon> _construction;

	public DBPtr<Constructon> construction { get { return _construction.Get(); } set { _construction.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightContructionInPocketAction>(owner);
		_construction = new UndoRedoDBPtr<Constructon>( owner );
		___parent.Changed += FireChangedEvent;
		_construction.Changed += FireChangedEvent;
	}

	public HighlightContructionInPocketAction()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightContructionInPocketAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightContructionInPocketAction" );
		construction = source.construction;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightContructionInPocketAction source = _source as HighlightContructionInPocketAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightContructionInPocketAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightContructionInPocketAction newParent = rawParent == null ? null : rawParent.Get<HighlightContructionInPocketAction>();
		if ( newParent == null && _newParent is HighlightContructionInPocketAction )
			newParent = _newParent as HighlightContructionInPocketAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_construction.SetParent( newParent == null ? null : newParent._construction );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_construction.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_construction.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "construction" )
			_construction.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "construction" )
			return _construction.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HighlightHeroAction : HighlightAction
{
	private UndoRedoDBPtr<HighlightHeroAction> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightHeroAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Hero> _hero;

	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightHeroAction>(owner);
		_hero = new UndoRedoDBPtr<Hero>( owner );
		___parent.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
	}

	public HighlightHeroAction()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightHeroAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightHeroAction" );
		hero = source.hero;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightHeroAction source = _source as HighlightHeroAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightHeroAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightHeroAction newParent = rawParent == null ? null : rawParent.Get<HighlightHeroAction>();
		if ( newParent == null && _newParent is HighlightHeroAction )
			newParent = _newParent as HighlightHeroAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_hero.SetParent( newParent == null ? null : newParent._hero );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_hero.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_hero.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "hero" )
			_hero.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HighlightItemAction : HighlightAction
{
	private UndoRedoDBPtr<HighlightItemAction> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightItemAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<HightlightItemType> _itemToHighlight;

	public HightlightItemType itemToHighlight { get { return _itemToHighlight.Get(); } set { _itemToHighlight.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightItemAction>(owner);
		_itemToHighlight = new UndoRedo<HightlightItemType>( owner, HightlightItemType.UnsoulboundButton );
		___parent.Changed += FireChangedEvent;
		_itemToHighlight.Changed += FireChangedEvent;
	}

	public HighlightItemAction()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightItemAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightItemAction" );
		itemToHighlight = source.itemToHighlight;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightItemAction source = _source as HighlightItemAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightItemAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightItemAction newParent = rawParent == null ? null : rawParent.Get<HighlightItemAction>();
		if ( newParent == null && _newParent is HighlightItemAction )
			newParent = _newParent as HighlightItemAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_itemToHighlight.SetParent( newParent == null ? null : newParent._itemToHighlight );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_itemToHighlight.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_itemToHighlight.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "itemToHighlight" )
			_itemToHighlight.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "itemToHighlight" )
			return _itemToHighlight.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HighlightMapTypeAction : HighlightAction
{
	private UndoRedoDBPtr<HighlightMapTypeAction> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightMapTypeAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<MapType> _mapType;

	public MapType mapType { get { return _mapType.Get(); } set { _mapType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightMapTypeAction>(owner);
		_mapType = new UndoRedo<MapType>( owner, MapType.Tutorial );
		___parent.Changed += FireChangedEvent;
		_mapType.Changed += FireChangedEvent;
	}

	public HighlightMapTypeAction()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightMapTypeAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightMapTypeAction" );
		mapType = source.mapType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightMapTypeAction source = _source as HighlightMapTypeAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightMapTypeAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightMapTypeAction newParent = rawParent == null ? null : rawParent.Get<HighlightMapTypeAction>();
		if ( newParent == null && _newParent is HighlightMapTypeAction )
			newParent = _newParent as HighlightMapTypeAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_mapType.SetParent( newParent == null ? null : newParent._mapType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_mapType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_mapType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "mapType" )
			_mapType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "mapType" )
			return _mapType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class HighlightTalentAction : HighlightAction
{
	private UndoRedoDBPtr<HighlightTalentAction> ___parent;
	[HideInOutliner]
	public new DBPtr<HighlightTalentAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Talent> _talent;

	public DBPtr<Talent> talent { get { return _talent.Get(); } set { _talent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HighlightTalentAction>(owner);
		_talent = new UndoRedoDBPtr<Talent>( owner );
		___parent.Changed += FireChangedEvent;
		_talent.Changed += FireChangedEvent;
	}

	public HighlightTalentAction()
	{
		Initialize( this );
	}
	private void AssignSelf( HighlightTalentAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HighlightTalentAction" );
		talent = source.talent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HighlightTalentAction source = _source as HighlightTalentAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HighlightTalentAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HighlightTalentAction newParent = rawParent == null ? null : rawParent.Get<HighlightTalentAction>();
		if ( newParent == null && _newParent is HighlightTalentAction )
			newParent = _newParent as HighlightTalentAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_talent.SetParent( newParent == null ? null : newParent._talent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_talent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_talent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "talent" )
			_talent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "talent" )
			return _talent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ModelDataCondition : QuestCondition
{
	private UndoRedoDBPtr<ModelDataCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<ModelDataCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _code;
	private UndoRedoAssignableList<DBPtr<QuestCondition>> _triggers;

	[Multiline]
	public string code { get { return _code.Get(); } set { _code.Set( value ); } }

	[Description( "Условия, по выполнению любого из которых происходит проверка кода" )]
	public libdb.IChangeableList<DBPtr<QuestCondition>> triggers { get { return _triggers; } set { _triggers.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ModelDataCondition>(owner);
		_code = new UndoRedo<string>( owner, string.Empty );
		_triggers = new UndoRedoAssignableList<DBPtr<QuestCondition>>( owner );
		___parent.Changed += FireChangedEvent;
		_code.Changed += FireChangedEvent;
		_triggers.Changed += FireChangedEvent;
	}

	public ModelDataCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( ModelDataCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ModelDataCondition" );
		code = source.code;
		triggers = source.triggers;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ModelDataCondition source = _source as ModelDataCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ModelDataCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ModelDataCondition newParent = rawParent == null ? null : rawParent.Get<ModelDataCondition>();
		if ( newParent == null && _newParent is ModelDataCondition )
			newParent = _newParent as ModelDataCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_code.SetParent( newParent == null ? null : newParent._code );
		_triggers.SetParent( newParent == null ? null : newParent._triggers );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_code.Reset();
		_triggers.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_code.IsDerivedFromParent()
			&& _triggers.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "code" )
			_code.Reset();
		else if ( fieldName == "triggers" )
			_triggers.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "code" )
			return _code.IsDerivedFromParent();
		if ( fieldName == "triggers" )
			return _triggers.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class MoveTalentFromHeroToLibraryAction : QuestAction
{
	private UndoRedoDBPtr<MoveTalentFromHeroToLibraryAction> ___parent;
	[HideInOutliner]
	public new DBPtr<MoveTalentFromHeroToLibraryAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Hero> _hero;
	private UndoRedo<int> _slot;
	private UndoRedoDBPtr<Talent> _talent;

	[Description( "У какого героя искать талант" )]
	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	[Description( "Номер слота, из которого нужно вынуть талант (1-36)" )]
	public int slot { get { return _slot.Get(); } set { _slot.Set( value ); } }

	[Description( "Какой талант попытаться выложить, если не задан слот" )]
	public DBPtr<Talent> talent { get { return _talent.Get(); } set { _talent.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MoveTalentFromHeroToLibraryAction>(owner);
		_hero = new UndoRedoDBPtr<Hero>( owner );
		_slot = new UndoRedo<int>( owner, 0 );
		_talent = new UndoRedoDBPtr<Talent>( owner );
		___parent.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
		_slot.Changed += FireChangedEvent;
		_talent.Changed += FireChangedEvent;
	}

	public MoveTalentFromHeroToLibraryAction()
	{
		Initialize( this );
	}
	private void AssignSelf( MoveTalentFromHeroToLibraryAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MoveTalentFromHeroToLibraryAction" );
		hero = source.hero;
		slot = source.slot;
		talent = source.talent;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MoveTalentFromHeroToLibraryAction source = _source as MoveTalentFromHeroToLibraryAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MoveTalentFromHeroToLibraryAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MoveTalentFromHeroToLibraryAction newParent = rawParent == null ? null : rawParent.Get<MoveTalentFromHeroToLibraryAction>();
		if ( newParent == null && _newParent is MoveTalentFromHeroToLibraryAction )
			newParent = _newParent as MoveTalentFromHeroToLibraryAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_hero.SetParent( newParent == null ? null : newParent._hero );
		_slot.SetParent( newParent == null ? null : newParent._slot );
		_talent.SetParent( newParent == null ? null : newParent._talent );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_hero.Reset();
		_slot.Reset();
		_talent.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_hero.IsDerivedFromParent()
			&& _slot.IsDerivedFromParent()
			&& _talent.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "hero" )
			_hero.Reset();
		else if ( fieldName == "slot" )
			_slot.Reset();
		else if ( fieldName == "talent" )
			_talent.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		if ( fieldName == "slot" )
			return _slot.IsDerivedFromParent();
		if ( fieldName == "talent" )
			return _talent.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class NextQuestAction : QuestAction
{
	private UndoRedoDBPtr<NextQuestAction> ___parent;
	[HideInOutliner]
	public new DBPtr<NextQuestAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Quest> _quest;

	[Description( "Следующий квест" )]
	public DBPtr<Quest> quest { get { return _quest.Get(); } set { _quest.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<NextQuestAction>(owner);
		_quest = new UndoRedoDBPtr<Quest>( owner );
		___parent.Changed += FireChangedEvent;
		_quest.Changed += FireChangedEvent;
	}

	public NextQuestAction()
	{
		Initialize( this );
	}
	private void AssignSelf( NextQuestAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for NextQuestAction" );
		quest = source.quest;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		NextQuestAction source = _source as NextQuestAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NextQuestAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		NextQuestAction newParent = rawParent == null ? null : rawParent.Get<NextQuestAction>();
		if ( newParent == null && _newParent is NextQuestAction )
			newParent = _newParent as NextQuestAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_quest.SetParent( newParent == null ? null : newParent._quest );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_quest.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_quest.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "quest" )
			_quest.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "quest" )
			return _quest.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class OpenDarkenTutorialAction : ClientQuestAction
{
	private UndoRedoDBPtr<OpenDarkenTutorialAction> ___parent;
	[HideInOutliner]
	public new DBPtr<OpenDarkenTutorialAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _movieName;
	private UndoRedo<string> _baseWindowName;
	private UndoRedoAssignableList<TextRef> _advices;
	private UndoRedo<bool> _declineDragFromTalentSet;

	public string movieName { get { return _movieName.Get(); } set { _movieName.Set( value ); } }

	public string baseWindowName { get { return _baseWindowName.Get(); } set { _baseWindowName.Set( value ); } }

	public libdb.IChangeableList<TextRef> advices { get { return _advices; } set { _advices.Assign( value ); } }

	public bool declineDragFromTalentSet { get { return _declineDragFromTalentSet.Get(); } set { _declineDragFromTalentSet.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OpenDarkenTutorialAction>(owner);
		_movieName = new UndoRedo<string>( owner, string.Empty );
		_baseWindowName = new UndoRedo<string>( owner, string.Empty );
		_advices = new UndoRedoAssignableList<TextRef>( owner );
		_declineDragFromTalentSet = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_movieName.Changed += FireChangedEvent;
		_baseWindowName.Changed += FireChangedEvent;
		_advices.Changed += FireChangedEvent;
		_declineDragFromTalentSet.Changed += FireChangedEvent;
	}

	public OpenDarkenTutorialAction()
	{
		Initialize( this );
	}
	private void AssignSelf( OpenDarkenTutorialAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OpenDarkenTutorialAction" );
		movieName = source.movieName;
		baseWindowName = source.baseWindowName;
		advices = source.advices;
		declineDragFromTalentSet = source.declineDragFromTalentSet;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OpenDarkenTutorialAction source = _source as OpenDarkenTutorialAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OpenDarkenTutorialAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OpenDarkenTutorialAction newParent = rawParent == null ? null : rawParent.Get<OpenDarkenTutorialAction>();
		if ( newParent == null && _newParent is OpenDarkenTutorialAction )
			newParent = _newParent as OpenDarkenTutorialAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_movieName.SetParent( newParent == null ? null : newParent._movieName );
		_baseWindowName.SetParent( newParent == null ? null : newParent._baseWindowName );
		_advices.SetParent( newParent == null ? null : newParent._advices );
		_declineDragFromTalentSet.SetParent( newParent == null ? null : newParent._declineDragFromTalentSet );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_movieName.Reset();
		_baseWindowName.Reset();
		_advices.Reset();
		_declineDragFromTalentSet.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_movieName.IsDerivedFromParent()
			&& _baseWindowName.IsDerivedFromParent()
			&& _advices.IsDerivedFromParent()
			&& _declineDragFromTalentSet.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "movieName" )
			_movieName.Reset();
		else if ( fieldName == "baseWindowName" )
			_baseWindowName.Reset();
		else if ( fieldName == "advices" )
			_advices.Reset();
		else if ( fieldName == "declineDragFromTalentSet" )
			_declineDragFromTalentSet.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "movieName" )
			return _movieName.IsDerivedFromParent();
		if ( fieldName == "baseWindowName" )
			return _baseWindowName.IsDerivedFromParent();
		if ( fieldName == "advices" )
			return _advices.IsDerivedFromParent();
		if ( fieldName == "declineDragFromTalentSet" )
			return _declineDragFromTalentSet.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class OpenDecreaseRatingDialogWindowAction : ClientQuestAction
{
	private UndoRedoDBPtr<OpenDecreaseRatingDialogWindowAction> ___parent;
	[HideInOutliner]
	public new DBPtr<OpenDecreaseRatingDialogWindowAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _message;

	public TextRef message { get { return _message; } set { _message.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OpenDecreaseRatingDialogWindowAction>(owner);
		_message = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_message.Changed += FireChangedEvent;
	}

	public OpenDecreaseRatingDialogWindowAction()
	{
		Initialize( this );
	}
	private void AssignSelf( OpenDecreaseRatingDialogWindowAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OpenDecreaseRatingDialogWindowAction" );
		message = source.message;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OpenDecreaseRatingDialogWindowAction source = _source as OpenDecreaseRatingDialogWindowAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OpenDecreaseRatingDialogWindowAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OpenDecreaseRatingDialogWindowAction newParent = rawParent == null ? null : rawParent.Get<OpenDecreaseRatingDialogWindowAction>();
		if ( newParent == null && _newParent is OpenDecreaseRatingDialogWindowAction )
			newParent = _newParent as OpenDecreaseRatingDialogWindowAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_message.SetParent( newParent == null ? null : newParent._message );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_message.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_message.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "message" )
			_message.Reset();
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
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class OpenPanelAction : ClientQuestAction
{
	private UndoRedoDBPtr<OpenPanelAction> ___parent;
	[HideInOutliner]
	public new DBPtr<OpenPanelAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<PanelType> _panelType;

	public PanelType panelType { get { return _panelType.Get(); } set { _panelType.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OpenPanelAction>(owner);
		_panelType = new UndoRedo<PanelType>( owner, PanelType.Construction );
		___parent.Changed += FireChangedEvent;
		_panelType.Changed += FireChangedEvent;
	}

	public OpenPanelAction()
	{
		Initialize( this );
	}
	private void AssignSelf( OpenPanelAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OpenPanelAction" );
		panelType = source.panelType;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OpenPanelAction source = _source as OpenPanelAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OpenPanelAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OpenPanelAction newParent = rawParent == null ? null : rawParent.Get<OpenPanelAction>();
		if ( newParent == null && _newParent is OpenPanelAction )
			newParent = _newParent as OpenPanelAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_panelType.SetParent( newParent == null ? null : newParent._panelType );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_panelType.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_panelType.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "panelType" )
			_panelType.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "panelType" )
			return _panelType.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class OpenUrlAction : ClientQuestAction
{
	private UndoRedoDBPtr<OpenUrlAction> ___parent;
	[HideInOutliner]
	public new DBPtr<OpenUrlAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _url;

	[Description( "Полный адрес, по которому будет совершен переход в браузере" )]
	public TextRef url { get { return _url; } set { _url.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OpenUrlAction>(owner);
		_url = new TextRef( owner, new TextRef() );
		___parent.Changed += FireChangedEvent;
		_url.Changed += FireChangedEvent;
	}

	public OpenUrlAction()
	{
		Initialize( this );
	}
	private void AssignSelf( OpenUrlAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OpenUrlAction" );
		url = source.url;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OpenUrlAction source = _source as OpenUrlAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OpenUrlAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OpenUrlAction newParent = rawParent == null ? null : rawParent.Get<OpenUrlAction>();
		if ( newParent == null && _newParent is OpenUrlAction )
			newParent = _newParent as OpenUrlAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_url.SetParent( newParent == null ? null : newParent._url );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_url.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_url.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "url" )
			_url.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "url" )
			return _url.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class OpenWindowAction : ClientQuestAction
{
	private UndoRedoDBPtr<OpenWindowAction> ___parent;
	[HideInOutliner]
	public new DBPtr<OpenWindowAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _windowName;

	public string windowName { get { return _windowName.Get(); } set { _windowName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OpenWindowAction>(owner);
		_windowName = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_windowName.Changed += FireChangedEvent;
	}

	public OpenWindowAction()
	{
		Initialize( this );
	}
	private void AssignSelf( OpenWindowAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OpenWindowAction" );
		windowName = source.windowName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OpenWindowAction source = _source as OpenWindowAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OpenWindowAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OpenWindowAction newParent = rawParent == null ? null : rawParent.Get<OpenWindowAction>();
		if ( newParent == null && _newParent is OpenWindowAction )
			newParent = _newParent as OpenWindowAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_windowName.SetParent( newParent == null ? null : newParent._windowName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_windowName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_windowName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "windowName" )
			_windowName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "windowName" )
			return _windowName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class OpenWindowCondition : QuestCondition
{
	private UndoRedoDBPtr<OpenWindowCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<OpenWindowCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<OpenWindowConditionType> _windowName;

	public OpenWindowConditionType windowName { get { return _windowName.Get(); } set { _windowName.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<OpenWindowCondition>(owner);
		_windowName = new UndoRedo<OpenWindowConditionType>( owner, OpenWindowConditionType.Academy );
		___parent.Changed += FireChangedEvent;
		_windowName.Changed += FireChangedEvent;
	}

	public OpenWindowCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( OpenWindowCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for OpenWindowCondition" );
		windowName = source.windowName;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		OpenWindowCondition source = _source as OpenWindowCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for OpenWindowCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		OpenWindowCondition newParent = rawParent == null ? null : rawParent.Get<OpenWindowCondition>();
		if ( newParent == null && _newParent is OpenWindowCondition )
			newParent = _newParent as OpenWindowCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_windowName.SetParent( newParent == null ? null : newParent._windowName );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_windowName.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_windowName.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "windowName" )
			_windowName.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "windowName" )
			return _windowName.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[IndexField("id")]
[Custom("Social")]
public class Quest : DBResource
{
	private UndoRedoDBPtr<Quest> ___parent;
	[HideInOutliner]
	public new DBPtr<Quest> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _persistentId;
	private TextRef _Title;
	private UndoRedo<bool> _oneTime;
	private TextRef _Description;
	private UndoRedoAssignableList<DBPtr<DialogBase>> _initialDialog;
	private UndoRedoAssignableList<DBPtr<DialogBase>> _finalDialog;
	private UndoRedoAssignableList<Objective> _objectives;
	private UndoRedoAssignableList<DBPtr<QuestAction>> _rewards;
	private UndoRedoAssignableList<Reward> _answers;
	private UndoRedo<bool> _participateInQuestLine;
	private UndoRedo<bool> _autoOpen;
	private UndoRedoAssignableList<DBPtr<Quest>> _prerequisiteQuests;
	private UndoRedo<int> _lordLevelRequirement;
	private UndoRedo<bool> _autoOpenReward;
	private UndoRedo<bool> _isVisible;
	private UndoRedo<string> _alternativeQuestId;

	public string persistentId { get { return _persistentId.Get(); } set { _persistentId.Set( value ); } }

	[Description( "заголовок квеста" )]
	public TextRef Title { get { return _Title; } set { _Title.Assign( value ); } }

	[Description( "квест может быть выдан только один раз" )]
	public bool oneTime { get { return _oneTime.Get(); } set { _oneTime.Set( value ); } }

	[Description( "что надо сделать" )]
	public TextRef Description { get { return _Description; } set { _Description.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<DialogBase>> initialDialog { get { return _initialDialog; } set { _initialDialog.Assign( value ); } }

	public libdb.IChangeableList<DBPtr<DialogBase>> finalDialog { get { return _finalDialog; } set { _finalDialog.Assign( value ); } }

	public libdb.IChangeableList<Objective> objectives { get { return _objectives; } set { _objectives.Assign( value ); } }

	[Description( "Список наград, которые выдаются всегда" )]
	public libdb.IChangeableList<DBPtr<QuestAction>> rewards { get { return _rewards; } set { _rewards.Assign( value ); } }

	[Description( "Варианты ответов на финальный диалог со списком действий" )]
	public libdb.IChangeableList<Reward> answers { get { return _answers; } set { _answers.Assign( value ); } }

	[Description( "влияет ли квест на изменение отображения линейки (пример 1 из 2)" )]
	public bool participateInQuestLine { get { return _participateInQuestLine.Get(); } set { _participateInQuestLine.Set( value ); } }

	[Description( "окно квеста сразу открывается при его появлении" )]
	public bool autoOpen { get { return _autoOpen.Get(); } set { _autoOpen.Set( value ); } }

	[Description( "Какие квесты нужно закомплитить что бы получить доступ к этому квесту" )]
	public libdb.IChangeableList<DBPtr<Quest>> prerequisiteQuests { get { return _prerequisiteQuests; } set { _prerequisiteQuests.Assign( value ); } }

	[Description( "Необходимый уровень замка (минимальный) для выдачи квеста" )]
	public int lordLevelRequirement { get { return _lordLevelRequirement.Get(); } set { _lordLevelRequirement.Set( value ); } }

	[Description( "флаг автоматического открытия окна квестовых наград" )]
	public bool autoOpenReward { get { return _autoOpenReward.Get(); } set { _autoOpenReward.Set( value ); } }

	[Description( "Показывается ли в интерфейсе" )]
	public bool isVisible { get { return _isVisible.Get(); } set { _isVisible.Set( value ); } }

	[Description( "persistentId квеста, на который меняется текущий квест, при смене фракции. Если менять не надо - оставить пустым." )]
	public string alternativeQuestId { get { return _alternativeQuestId.Get(); } set { _alternativeQuestId.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Quest>(owner);
		_persistentId = new UndoRedo<string>( owner, string.Empty );
		_Title = new TextRef( owner, new TextRef() );
		_oneTime = new UndoRedo<bool>( owner, true );
		_Description = new TextRef( owner, new TextRef() );
		_initialDialog = new UndoRedoAssignableList<DBPtr<DialogBase>>( owner );
		_finalDialog = new UndoRedoAssignableList<DBPtr<DialogBase>>( owner );
		_objectives = new UndoRedoAssignableList<Objective>( owner );
		_rewards = new UndoRedoAssignableList<DBPtr<QuestAction>>( owner );
		_answers = new UndoRedoAssignableList<Reward>( owner );
		_participateInQuestLine = new UndoRedo<bool>( owner, true );
		_autoOpen = new UndoRedo<bool>( owner, false );
		_prerequisiteQuests = new UndoRedoAssignableList<DBPtr<Quest>>( owner );
		_lordLevelRequirement = new UndoRedo<int>( owner, 1 );
		_autoOpenReward = new UndoRedo<bool>( owner, false );
		_isVisible = new UndoRedo<bool>( owner, true );
		_alternativeQuestId = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_persistentId.Changed += FireChangedEvent;
		_Title.Changed += FireChangedEvent;
		_oneTime.Changed += FireChangedEvent;
		_Description.Changed += FireChangedEvent;
		_initialDialog.Changed += FireChangedEvent;
		_finalDialog.Changed += FireChangedEvent;
		_objectives.Changed += FireChangedEvent;
		_rewards.Changed += FireChangedEvent;
		_answers.Changed += FireChangedEvent;
		_participateInQuestLine.Changed += FireChangedEvent;
		_autoOpen.Changed += FireChangedEvent;
		_prerequisiteQuests.Changed += FireChangedEvent;
		_lordLevelRequirement.Changed += FireChangedEvent;
		_autoOpenReward.Changed += FireChangedEvent;
		_isVisible.Changed += FireChangedEvent;
		_alternativeQuestId.Changed += FireChangedEvent;
	}

	public Quest()
	{
		Initialize( this );
	}
	private void AssignSelf( Quest source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Quest" );
		persistentId = source.persistentId;
		Title = source.Title;
		oneTime = source.oneTime;
		Description = source.Description;
		initialDialog = source.initialDialog;
		finalDialog = source.finalDialog;
		objectives = source.objectives;
		rewards = source.rewards;
		answers = source.answers;
		participateInQuestLine = source.participateInQuestLine;
		autoOpen = source.autoOpen;
		prerequisiteQuests = source.prerequisiteQuests;
		lordLevelRequirement = source.lordLevelRequirement;
		autoOpenReward = source.autoOpenReward;
		isVisible = source.isVisible;
		alternativeQuestId = source.alternativeQuestId;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Quest source = _source as Quest;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Quest" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Quest newParent = rawParent == null ? null : rawParent.Get<Quest>();
		if ( newParent == null && _newParent is Quest )
			newParent = _newParent as Quest;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_persistentId.SetParent( newParent == null ? null : newParent._persistentId );
		_Title.SetParent( newParent == null ? null : newParent._Title );
		_oneTime.SetParent( newParent == null ? null : newParent._oneTime );
		_Description.SetParent( newParent == null ? null : newParent._Description );
		_initialDialog.SetParent( newParent == null ? null : newParent._initialDialog );
		_finalDialog.SetParent( newParent == null ? null : newParent._finalDialog );
		_objectives.SetParent( newParent == null ? null : newParent._objectives );
		_rewards.SetParent( newParent == null ? null : newParent._rewards );
		_answers.SetParent( newParent == null ? null : newParent._answers );
		_participateInQuestLine.SetParent( newParent == null ? null : newParent._participateInQuestLine );
		_autoOpen.SetParent( newParent == null ? null : newParent._autoOpen );
		_prerequisiteQuests.SetParent( newParent == null ? null : newParent._prerequisiteQuests );
		_lordLevelRequirement.SetParent( newParent == null ? null : newParent._lordLevelRequirement );
		_autoOpenReward.SetParent( newParent == null ? null : newParent._autoOpenReward );
		_isVisible.SetParent( newParent == null ? null : newParent._isVisible );
		_alternativeQuestId.SetParent( newParent == null ? null : newParent._alternativeQuestId );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_persistentId.Reset();
		_Title.Reset();
		_oneTime.Reset();
		_Description.Reset();
		_initialDialog.Reset();
		_finalDialog.Reset();
		_objectives.Reset();
		_rewards.Reset();
		_answers.Reset();
		_participateInQuestLine.Reset();
		_autoOpen.Reset();
		_prerequisiteQuests.Reset();
		_lordLevelRequirement.Reset();
		_autoOpenReward.Reset();
		_isVisible.Reset();
		_alternativeQuestId.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_persistentId.IsDerivedFromParent()
			&& _Title.IsDerivedFromParent()
			&& _oneTime.IsDerivedFromParent()
			&& _Description.IsDerivedFromParent()
			&& _initialDialog.IsDerivedFromParent()
			&& _finalDialog.IsDerivedFromParent()
			&& _objectives.IsDerivedFromParent()
			&& _rewards.IsDerivedFromParent()
			&& _answers.IsDerivedFromParent()
			&& _participateInQuestLine.IsDerivedFromParent()
			&& _autoOpen.IsDerivedFromParent()
			&& _prerequisiteQuests.IsDerivedFromParent()
			&& _lordLevelRequirement.IsDerivedFromParent()
			&& _autoOpenReward.IsDerivedFromParent()
			&& _isVisible.IsDerivedFromParent()
			&& _alternativeQuestId.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "persistentId" )
			_persistentId.Reset();
		else if ( fieldName == "Title" )
			_Title.Reset();
		else if ( fieldName == "oneTime" )
			_oneTime.Reset();
		else if ( fieldName == "Description" )
			_Description.Reset();
		else if ( fieldName == "initialDialog" )
			_initialDialog.Reset();
		else if ( fieldName == "finalDialog" )
			_finalDialog.Reset();
		else if ( fieldName == "objectives" )
			_objectives.Reset();
		else if ( fieldName == "rewards" )
			_rewards.Reset();
		else if ( fieldName == "answers" )
			_answers.Reset();
		else if ( fieldName == "participateInQuestLine" )
			_participateInQuestLine.Reset();
		else if ( fieldName == "autoOpen" )
			_autoOpen.Reset();
		else if ( fieldName == "prerequisiteQuests" )
			_prerequisiteQuests.Reset();
		else if ( fieldName == "lordLevelRequirement" )
			_lordLevelRequirement.Reset();
		else if ( fieldName == "autoOpenReward" )
			_autoOpenReward.Reset();
		else if ( fieldName == "isVisible" )
			_isVisible.Reset();
		else if ( fieldName == "alternativeQuestId" )
			_alternativeQuestId.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "persistentId" )
			return _persistentId.IsDerivedFromParent();
		if ( fieldName == "Title" )
			return _Title.IsDerivedFromParent();
		if ( fieldName == "oneTime" )
			return _oneTime.IsDerivedFromParent();
		if ( fieldName == "Description" )
			return _Description.IsDerivedFromParent();
		if ( fieldName == "initialDialog" )
			return _initialDialog.IsDerivedFromParent();
		if ( fieldName == "finalDialog" )
			return _finalDialog.IsDerivedFromParent();
		if ( fieldName == "objectives" )
			return _objectives.IsDerivedFromParent();
		if ( fieldName == "rewards" )
			return _rewards.IsDerivedFromParent();
		if ( fieldName == "answers" )
			return _answers.IsDerivedFromParent();
		if ( fieldName == "participateInQuestLine" )
			return _participateInQuestLine.IsDerivedFromParent();
		if ( fieldName == "autoOpen" )
			return _autoOpen.IsDerivedFromParent();
		if ( fieldName == "prerequisiteQuests" )
			return _prerequisiteQuests.IsDerivedFromParent();
		if ( fieldName == "lordLevelRequirement" )
			return _lordLevelRequirement.IsDerivedFromParent();
		if ( fieldName == "autoOpenReward" )
			return _autoOpenReward.IsDerivedFromParent();
		if ( fieldName == "isVisible" )
			return _isVisible.IsDerivedFromParent();
		if ( fieldName == "alternativeQuestId" )
			return _alternativeQuestId.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ChangeConfirmationUnsoulboundModeAction : ClientQuestAction
{
	private UndoRedoDBPtr<ChangeConfirmationUnsoulboundModeAction> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeConfirmationUnsoulboundModeAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _UnsoulboundConfirmationRequired;

	[Description( "True - запрашивать у пользователя подтверждение при отвязке таланты(как обычно). False - отвязывать талант без подтверждения." )]
	public bool UnsoulboundConfirmationRequired { get { return _UnsoulboundConfirmationRequired.Get(); } set { _UnsoulboundConfirmationRequired.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeConfirmationUnsoulboundModeAction>(owner);
		_UnsoulboundConfirmationRequired = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_UnsoulboundConfirmationRequired.Changed += FireChangedEvent;
	}

	public ChangeConfirmationUnsoulboundModeAction()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeConfirmationUnsoulboundModeAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeConfirmationUnsoulboundModeAction" );
		UnsoulboundConfirmationRequired = source.UnsoulboundConfirmationRequired;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeConfirmationUnsoulboundModeAction source = _source as ChangeConfirmationUnsoulboundModeAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeConfirmationUnsoulboundModeAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeConfirmationUnsoulboundModeAction newParent = rawParent == null ? null : rawParent.Get<ChangeConfirmationUnsoulboundModeAction>();
		if ( newParent == null && _newParent is ChangeConfirmationUnsoulboundModeAction )
			newParent = _newParent as ChangeConfirmationUnsoulboundModeAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_UnsoulboundConfirmationRequired.SetParent( newParent == null ? null : newParent._UnsoulboundConfirmationRequired );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_UnsoulboundConfirmationRequired.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_UnsoulboundConfirmationRequired.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "UnsoulboundConfirmationRequired" )
			_UnsoulboundConfirmationRequired.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "UnsoulboundConfirmationRequired" )
			return _UnsoulboundConfirmationRequired.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class CloseAllWindowCondition : QuestCondition
{
	private UndoRedoDBPtr<CloseAllWindowCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<CloseAllWindowCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CloseAllWindowCondition>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public CloseAllWindowCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( CloseAllWindowCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CloseAllWindowCondition" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CloseAllWindowCondition source = _source as CloseAllWindowCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CloseAllWindowCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CloseAllWindowCondition newParent = rawParent == null ? null : rawParent.Get<CloseAllWindowCondition>();
		if ( newParent == null && _newParent is CloseAllWindowCondition )
			newParent = _newParent as CloseAllWindowCondition;
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

[IndexField("caption")]
[Custom("Social")]
public class QuestLine : DBResource
{
	private UndoRedoDBPtr<QuestLine> ___parent;
	[HideInOutliner]
	public new DBPtr<QuestLine> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _caption;
	private TextRef _LineName;
	private UndoRedoDBPtr<Actor> _actor;
	private UndoRedoAssignableList<DBPtr<Quest>> _quests;

	public string caption { get { return _caption.Get(); } set { _caption.Set( value ); } }

	[Description( "имя линейки" )]
	public TextRef LineName { get { return _LineName; } set { _LineName.Assign( value ); } }

	[Description( "Говорящий" )]
	public DBPtr<Actor> actor { get { return _actor.Get(); } set { _actor.Set( value ); } }

	public libdb.IChangeableList<DBPtr<Quest>> quests { get { return _quests; } set { _quests.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<QuestLine>(owner);
		_caption = new UndoRedo<string>( owner, string.Empty );
		_LineName = new TextRef( owner, new TextRef() );
		_actor = new UndoRedoDBPtr<Actor>( owner );
		_quests = new UndoRedoAssignableList<DBPtr<Quest>>( owner );
		___parent.Changed += FireChangedEvent;
		_caption.Changed += FireChangedEvent;
		_LineName.Changed += FireChangedEvent;
		_actor.Changed += FireChangedEvent;
		_quests.Changed += FireChangedEvent;
	}

	public QuestLine()
	{
		Initialize( this );
	}
	private void AssignSelf( QuestLine source )
	{
		DataBase.UndoRedoManager.Start( "Assign for QuestLine" );
		caption = source.caption;
		LineName = source.LineName;
		actor = source.actor;
		quests = source.quests;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		QuestLine source = _source as QuestLine;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for QuestLine" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		QuestLine newParent = rawParent == null ? null : rawParent.Get<QuestLine>();
		if ( newParent == null && _newParent is QuestLine )
			newParent = _newParent as QuestLine;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_caption.SetParent( newParent == null ? null : newParent._caption );
		_LineName.SetParent( newParent == null ? null : newParent._LineName );
		_actor.SetParent( newParent == null ? null : newParent._actor );
		_quests.SetParent( newParent == null ? null : newParent._quests );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_caption.Reset();
		_LineName.Reset();
		_actor.Reset();
		_quests.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_caption.IsDerivedFromParent()
			&& _LineName.IsDerivedFromParent()
			&& _actor.IsDerivedFromParent()
			&& _quests.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "caption" )
			_caption.Reset();
		else if ( fieldName == "LineName" )
			_LineName.Reset();
		else if ( fieldName == "actor" )
			_actor.Reset();
		else if ( fieldName == "quests" )
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
		if ( fieldName == "caption" )
			return _caption.IsDerivedFromParent();
		if ( fieldName == "LineName" )
			return _LineName.IsDerivedFromParent();
		if ( fieldName == "actor" )
			return _actor.IsDerivedFromParent();
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
public class RemoveQuestAction : QuestAction
{
	private UndoRedoDBPtr<RemoveQuestAction> ___parent;
	[HideInOutliner]
	public new DBPtr<RemoveQuestAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Quest> _quest;

	[Description( "Удаляемый (отменяемый) квест" )]
	public DBPtr<Quest> quest { get { return _quest.Get(); } set { _quest.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RemoveQuestAction>(owner);
		_quest = new UndoRedoDBPtr<Quest>( owner );
		___parent.Changed += FireChangedEvent;
		_quest.Changed += FireChangedEvent;
	}

	public RemoveQuestAction()
	{
		Initialize( this );
	}
	private void AssignSelf( RemoveQuestAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RemoveQuestAction" );
		quest = source.quest;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RemoveQuestAction source = _source as RemoveQuestAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RemoveQuestAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RemoveQuestAction newParent = rawParent == null ? null : rawParent.Get<RemoveQuestAction>();
		if ( newParent == null && _newParent is RemoveQuestAction )
			newParent = _newParent as RemoveQuestAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_quest.SetParent( newParent == null ? null : newParent._quest );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_quest.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_quest.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "quest" )
			_quest.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "quest" )
			return _quest.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class RemoveTalentsIsNewStateAction : QuestAction
{
	private UndoRedoDBPtr<RemoveTalentsIsNewStateAction> ___parent;
	[HideInOutliner]
	public new DBPtr<RemoveTalentsIsNewStateAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RemoveTalentsIsNewStateAction>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public RemoveTalentsIsNewStateAction()
	{
		Initialize( this );
	}
	private void AssignSelf( RemoveTalentsIsNewStateAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RemoveTalentsIsNewStateAction" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RemoveTalentsIsNewStateAction source = _source as RemoveTalentsIsNewStateAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RemoveTalentsIsNewStateAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RemoveTalentsIsNewStateAction newParent = rawParent == null ? null : rawParent.Get<RemoveTalentsIsNewStateAction>();
		if ( newParent == null && _newParent is RemoveTalentsIsNewStateAction )
			newParent = _newParent as RemoveTalentsIsNewStateAction;
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
public class RepeatableCondition : QuestCondition
{
	private UndoRedoDBPtr<RepeatableCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<RepeatableCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<QuestCondition> _trigger;
	private UndoRedoAssignableList<DBPtr<ClientQuestAction>> _actions;

	[Description( "Условие, по которому вызываются действия пока квест активен" )]
	public DBPtr<QuestCondition> trigger { get { return _trigger.Get(); } set { _trigger.Set( value ); } }

	[Description( "Набор действий, выполняемый после срабатывания триггера" )]
	public libdb.IChangeableList<DBPtr<ClientQuestAction>> actions { get { return _actions; } set { _actions.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RepeatableCondition>(owner);
		_trigger = new UndoRedoDBPtr<QuestCondition>( owner );
		_actions = new UndoRedoAssignableList<DBPtr<ClientQuestAction>>( owner );
		___parent.Changed += FireChangedEvent;
		_trigger.Changed += FireChangedEvent;
		_actions.Changed += FireChangedEvent;
	}

	public RepeatableCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( RepeatableCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RepeatableCondition" );
		trigger = source.trigger;
		actions = source.actions;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RepeatableCondition source = _source as RepeatableCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RepeatableCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RepeatableCondition newParent = rawParent == null ? null : rawParent.Get<RepeatableCondition>();
		if ( newParent == null && _newParent is RepeatableCondition )
			newParent = _newParent as RepeatableCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_trigger.SetParent( newParent == null ? null : newParent._trigger );
		_actions.SetParent( newParent == null ? null : newParent._actions );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_trigger.Reset();
		_actions.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_trigger.IsDerivedFromParent()
			&& _actions.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "trigger" )
			_trigger.Reset();
		else if ( fieldName == "actions" )
			_actions.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "trigger" )
			return _trigger.IsDerivedFromParent();
		if ( fieldName == "actions" )
			return _actions.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ResetTalentsLibraryFiltersAction : ClientQuestAction
{
	private UndoRedoDBPtr<ResetTalentsLibraryFiltersAction> ___parent;
	[HideInOutliner]
	public new DBPtr<ResetTalentsLibraryFiltersAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<ECastleLibraryFilter> _ActiveFilters;

	[Description( "Все фильтры в библиотеке(по герою и т.д.) будут сброшены. Затем будут установлены фильтры по 'цветам' талантов согласно заданному значению." )]
	public ECastleLibraryFilter ActiveFilters { get { return _ActiveFilters.Get(); } set { _ActiveFilters.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ResetTalentsLibraryFiltersAction>(owner);
		_ActiveFilters = new UndoRedo<ECastleLibraryFilter>( owner, ECastleLibraryFilter.All );
		___parent.Changed += FireChangedEvent;
		_ActiveFilters.Changed += FireChangedEvent;
	}

	public ResetTalentsLibraryFiltersAction()
	{
		Initialize( this );
	}
	private void AssignSelf( ResetTalentsLibraryFiltersAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ResetTalentsLibraryFiltersAction" );
		ActiveFilters = source.ActiveFilters;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ResetTalentsLibraryFiltersAction source = _source as ResetTalentsLibraryFiltersAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ResetTalentsLibraryFiltersAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ResetTalentsLibraryFiltersAction newParent = rawParent == null ? null : rawParent.Get<ResetTalentsLibraryFiltersAction>();
		if ( newParent == null && _newParent is ResetTalentsLibraryFiltersAction )
			newParent = _newParent as ResetTalentsLibraryFiltersAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_ActiveFilters.SetParent( newParent == null ? null : newParent._ActiveFilters );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_ActiveFilters.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_ActiveFilters.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "ActiveFilters" )
			_ActiveFilters.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "ActiveFilters" )
			return _ActiveFilters.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class SelectHeroAction : ClientQuestAction
{
	private UndoRedoDBPtr<SelectHeroAction> ___parent;
	[HideInOutliner]
	public new DBPtr<SelectHeroAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Hero> _hero;

	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SelectHeroAction>(owner);
		_hero = new UndoRedoDBPtr<Hero>( owner );
		___parent.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
	}

	public SelectHeroAction()
	{
		Initialize( this );
	}
	private void AssignSelf( SelectHeroAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SelectHeroAction" );
		hero = source.hero;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SelectHeroAction source = _source as SelectHeroAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SelectHeroAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SelectHeroAction newParent = rawParent == null ? null : rawParent.Get<SelectHeroAction>();
		if ( newParent == null && _newParent is SelectHeroAction )
			newParent = _newParent as SelectHeroAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_hero.SetParent( newParent == null ? null : newParent._hero );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_hero.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_hero.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "hero" )
			_hero.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class SelectMapTypeAction : ClientQuestAction
{
	private UndoRedoDBPtr<SelectMapTypeAction> ___parent;
	[HideInOutliner]
	public new DBPtr<SelectMapTypeAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<MapType> _mapType;
	private UndoRedo<bool> _playWithBots;

	public MapType mapType { get { return _mapType.Get(); } set { _mapType.Set( value ); } }

	public bool playWithBots { get { return _playWithBots.Get(); } set { _playWithBots.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SelectMapTypeAction>(owner);
		_mapType = new UndoRedo<MapType>( owner, MapType.Tutorial );
		_playWithBots = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_mapType.Changed += FireChangedEvent;
		_playWithBots.Changed += FireChangedEvent;
	}

	public SelectMapTypeAction()
	{
		Initialize( this );
	}
	private void AssignSelf( SelectMapTypeAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SelectMapTypeAction" );
		mapType = source.mapType;
		playWithBots = source.playWithBots;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SelectMapTypeAction source = _source as SelectMapTypeAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SelectMapTypeAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SelectMapTypeAction newParent = rawParent == null ? null : rawParent.Get<SelectMapTypeAction>();
		if ( newParent == null && _newParent is SelectMapTypeAction )
			newParent = _newParent as SelectMapTypeAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_mapType.SetParent( newParent == null ? null : newParent._mapType );
		_playWithBots.SetParent( newParent == null ? null : newParent._playWithBots );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_mapType.Reset();
		_playWithBots.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_mapType.IsDerivedFromParent()
			&& _playWithBots.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "mapType" )
			_mapType.Reset();
		else if ( fieldName == "playWithBots" )
			_playWithBots.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "mapType" )
			return _mapType.IsDerivedFromParent();
		if ( fieldName == "playWithBots" )
			return _playWithBots.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class SendRequestCondition : QuestCondition
{
	private UndoRedoDBPtr<SendRequestCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<SendRequestCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<SendRequestName> _name;
	private UndoRedo<SendRequestPhase> _phase;

	[Description( "Имя запроса" )]
	public SendRequestName name { get { return _name.Get(); } set { _name.Set( value ); } }

	[Description( "Фаза исполнения запроса" )]
	public SendRequestPhase phase { get { return _phase.Get(); } set { _phase.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SendRequestCondition>(owner);
		_name = new UndoRedo<SendRequestName>( owner, SendRequestName.expansion );
		_phase = new UndoRedo<SendRequestPhase>( owner, SendRequestPhase.ClientAccepted );
		___parent.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_phase.Changed += FireChangedEvent;
	}

	public SendRequestCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( SendRequestCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SendRequestCondition" );
		name = source.name;
		phase = source.phase;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SendRequestCondition source = _source as SendRequestCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SendRequestCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SendRequestCondition newParent = rawParent == null ? null : rawParent.Get<SendRequestCondition>();
		if ( newParent == null && _newParent is SendRequestCondition )
			newParent = _newParent as SendRequestCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_name.SetParent( newParent == null ? null : newParent._name );
		_phase.SetParent( newParent == null ? null : newParent._phase );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_name.Reset();
		_phase.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_name.IsDerivedFromParent()
			&& _phase.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "phase" )
			_phase.Reset();
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
		if ( fieldName == "phase" )
			return _phase.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class SetLastRankedGameTimeAction : QuestAction
{
	private UndoRedoDBPtr<SetLastRankedGameTimeAction> ___parent;
	[HideInOutliner]
	public new DBPtr<SetLastRankedGameTimeAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SetLastRankedGameTimeAction>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public SetLastRankedGameTimeAction()
	{
		Initialize( this );
	}
	private void AssignSelf( SetLastRankedGameTimeAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SetLastRankedGameTimeAction" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SetLastRankedGameTimeAction source = _source as SetLastRankedGameTimeAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SetLastRankedGameTimeAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SetLastRankedGameTimeAction newParent = rawParent == null ? null : rawParent.Get<SetLastRankedGameTimeAction>();
		if ( newParent == null && _newParent is SetLastRankedGameTimeAction )
			newParent = _newParent as SetLastRankedGameTimeAction;
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
public class StartSessionAction : ClientQuestAction
{
	private UndoRedoDBPtr<StartSessionAction> ___parent;
	[HideInOutliner]
	public new DBPtr<StartSessionAction> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<AdvMapDescription> _map;
	private UndoRedoDBPtr<Hero> _hero;

	[Description( "Карта, которую стартовать" )]
	public DBPtr<AdvMapDescription> map { get { return _map.Get(); } set { _map.Set( value ); } }

	[Description( "Герой, с которым идти в бой" )]
	public DBPtr<Hero> hero { get { return _hero.Get(); } set { _hero.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StartSessionAction>(owner);
		_map = new UndoRedoDBPtr<AdvMapDescription>( owner );
		_hero = new UndoRedoDBPtr<Hero>( owner );
		___parent.Changed += FireChangedEvent;
		_map.Changed += FireChangedEvent;
		_hero.Changed += FireChangedEvent;
	}

	public StartSessionAction()
	{
		Initialize( this );
	}
	private void AssignSelf( StartSessionAction source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StartSessionAction" );
		map = source.map;
		hero = source.hero;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StartSessionAction source = _source as StartSessionAction;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StartSessionAction" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StartSessionAction newParent = rawParent == null ? null : rawParent.Get<StartSessionAction>();
		if ( newParent == null && _newParent is StartSessionAction )
			newParent = _newParent as StartSessionAction;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_map.SetParent( newParent == null ? null : newParent._map );
		_hero.SetParent( newParent == null ? null : newParent._hero );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_map.Reset();
		_hero.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_map.IsDerivedFromParent()
			&& _hero.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "map" )
			_map.Reset();
		else if ( fieldName == "hero" )
			_hero.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "map" )
			return _map.IsDerivedFromParent();
		if ( fieldName == "hero" )
			return _hero.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class StatisticEventCondition : QuestCondition
{
	private UndoRedoDBPtr<StatisticEventCondition> ___parent;
	[HideInOutliner]
	public new DBPtr<StatisticEventCondition> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<StatisticEventConditionItem> _events;
	private UndoRedo<bool> _countOnly;

	[Description( "Список эвентов, каждый из которых может привести к комплиту условия" )]
	public libdb.IChangeableList<StatisticEventConditionItem> events { get { return _events; } set { _events.Assign( value ); } }

	[Description( "Если true condition возвращает 1, иначе - value из эвента" )]
	public bool countOnly { get { return _countOnly.Get(); } set { _countOnly.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<StatisticEventCondition>(owner);
		_events = new UndoRedoAssignableList<StatisticEventConditionItem>( owner );
		_countOnly = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_events.Changed += FireChangedEvent;
		_countOnly.Changed += FireChangedEvent;
	}

	public StatisticEventCondition()
	{
		Initialize( this );
	}
	private void AssignSelf( StatisticEventCondition source )
	{
		DataBase.UndoRedoManager.Start( "Assign for StatisticEventCondition" );
		events = source.events;
		countOnly = source.countOnly;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		StatisticEventCondition source = _source as StatisticEventCondition;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for StatisticEventCondition" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		StatisticEventCondition newParent = rawParent == null ? null : rawParent.Get<StatisticEventCondition>();
		if ( newParent == null && _newParent is StatisticEventCondition )
			newParent = _newParent as StatisticEventCondition;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_events.SetParent( newParent == null ? null : newParent._events );
		_countOnly.SetParent( newParent == null ? null : newParent._countOnly );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_events.Reset();
		_countOnly.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_events.IsDerivedFromParent()
			&& _countOnly.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "events" )
			_events.Reset();
		else if ( fieldName == "countOnly" )
			_countOnly.Reset();
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
		if ( fieldName == "countOnly" )
			return _countOnly.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class TalentsCollectionSettings : DBResource
{
	private UndoRedoDBPtr<TalentsCollectionSettings> ___parent;
	[HideInOutliner]
	public new DBPtr<TalentsCollectionSettings> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<TaletnsGrouping> _grouping;

	public libdb.IChangeableList<TaletnsGrouping> grouping { get { return _grouping; } set { _grouping.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TalentsCollectionSettings>(owner);
		_grouping = new UndoRedoAssignableList<TaletnsGrouping>( owner );
		___parent.Changed += FireChangedEvent;
		_grouping.Changed += FireChangedEvent;
	}

	public TalentsCollectionSettings()
	{
		Initialize( this );
	}
	private void AssignSelf( TalentsCollectionSettings source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TalentsCollectionSettings" );
		grouping = source.grouping;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TalentsCollectionSettings source = _source as TalentsCollectionSettings;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TalentsCollectionSettings" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TalentsCollectionSettings newParent = rawParent == null ? null : rawParent.Get<TalentsCollectionSettings>();
		if ( newParent == null && _newParent is TalentsCollectionSettings )
			newParent = _newParent as TalentsCollectionSettings;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_grouping.SetParent( newParent == null ? null : newParent._grouping );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_grouping.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_grouping.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "grouping" )
			_grouping.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "grouping" )
			return _grouping.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
