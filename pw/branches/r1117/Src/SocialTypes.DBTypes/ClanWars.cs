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
public class GuildWarEventAwardItem : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GuildWarEventAwardItem __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<Lootbox> _lootbox;
	private UndoRedo<int> _count;

	[Description( "???????" )]
	public DBPtr<Lootbox> lootbox { get { return _lootbox.Get(); } set { _lootbox.Set( value ); } }

	[Description( "?????????? ?????????" )]
	public int count { get { return _count.Get(); } set { _count.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_lootbox = new UndoRedoDBPtr<Lootbox>( owner );
		_count = new UndoRedo<int>( owner, 0 );
		_lootbox.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
	}

	public GuildWarEventAwardItem()
	{
		Initialize( GetOwner() );
	}

	public GuildWarEventAwardItem( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GuildWarEventAwardItem( DBResource owner, GuildWarEventAwardItem source )
		: this(owner, source, true){}

	protected GuildWarEventAwardItem( DBResource owner, GuildWarEventAwardItem source, bool fireEvent )
	{
		_lootbox = new UndoRedoDBPtr<Lootbox>( owner, source.lootbox );
		_count = new UndoRedo<int>( owner, source.count );
		_lootbox.Changed += FireChangedEvent;
		_count.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GuildWarEventAwardItem source = _source as GuildWarEventAwardItem;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildWarEventAwardItem" );
		lootbox = source.lootbox;
		count = source.count;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GuildWarEventAwardItem newParent = _newParent as GuildWarEventAwardItem;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_lootbox.SetParent( newParent == null ? null : newParent._lootbox );
		_count.SetParent( newParent == null ? null : newParent._count );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_lootbox.Reset();
		_count.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_lootbox.IsDerivedFromParent()
			&& _count.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "lootbox" )
			_lootbox.Reset();
		else if ( fieldName == "count" )
			_count.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "lootbox" )
			return _lootbox.IsDerivedFromParent();
		if ( fieldName == "count" )
			return _count.IsDerivedFromParent();
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
public class GuildRecruitment : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GuildRecruitment __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _maxUserGuildRequests;
	private UndoRedo<int> _maxUserGuildRequestSize;
	private UndoRedo<int> _maxGuildRecruitTextSize;
	private UndoRedo<int> _guildRequestLifetime;
	private UndoRedoList<string> _locales;

	[Description( "????????????? ???-?? ?????? ?? ?????? ????????????" )]
	public int maxUserGuildRequests { get { return _maxUserGuildRequests.Get(); } set { _maxUserGuildRequests.Set( value ); } }

	[Description( "?????? ?????? ??? ???????? ? ???????" )]
	public int maxUserGuildRequestSize { get { return _maxUserGuildRequestSize.Get(); } set { _maxUserGuildRequestSize.Set( value ); } }

	[Description( "?????? ????????? ???????, ??????? ???????????? ??????? ??? ?????? ???????" )]
	public int maxGuildRecruitTextSize { get { return _maxGuildRecruitTextSize.Get(); } set { _maxGuildRecruitTextSize.Set( value ); } }

	[Description( "????? ????? ?????? (? ????????)" )]
	public int guildRequestLifetime { get { return _guildRequestLifetime.Get(); } set { _guildRequestLifetime.Set( value ); } }

	[Description( "????? ????????, ??? ?? ????? ???????" )]
	public libdb.IChangeableList<string> locales { get { return _locales; } set { _locales.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_maxUserGuildRequests = new UndoRedo<int>( owner, 0 );
		_maxUserGuildRequestSize = new UndoRedo<int>( owner, 0 );
		_maxGuildRecruitTextSize = new UndoRedo<int>( owner, 0 );
		_guildRequestLifetime = new UndoRedo<int>( owner, 0 );
		_locales = new UndoRedoList<string>( owner );
		_maxUserGuildRequests.Changed += FireChangedEvent;
		_maxUserGuildRequestSize.Changed += FireChangedEvent;
		_maxGuildRecruitTextSize.Changed += FireChangedEvent;
		_guildRequestLifetime.Changed += FireChangedEvent;
		_locales.Changed += FireChangedEvent;
	}

	public GuildRecruitment()
	{
		Initialize( GetOwner() );
	}

	public GuildRecruitment( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GuildRecruitment( DBResource owner, GuildRecruitment source )
		: this(owner, source, true){}

	protected GuildRecruitment( DBResource owner, GuildRecruitment source, bool fireEvent )
	{
		_maxUserGuildRequests = new UndoRedo<int>( owner, source.maxUserGuildRequests );
		_maxUserGuildRequestSize = new UndoRedo<int>( owner, source.maxUserGuildRequestSize );
		_maxGuildRecruitTextSize = new UndoRedo<int>( owner, source.maxGuildRecruitTextSize );
		_guildRequestLifetime = new UndoRedo<int>( owner, source.guildRequestLifetime );
		_locales = new UndoRedoList<string>( owner );
		_locales.Assign( source.locales );
		_maxUserGuildRequests.Changed += FireChangedEvent;
		_maxUserGuildRequestSize.Changed += FireChangedEvent;
		_maxGuildRecruitTextSize.Changed += FireChangedEvent;
		_guildRequestLifetime.Changed += FireChangedEvent;
		_locales.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GuildRecruitment source = _source as GuildRecruitment;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildRecruitment" );
		maxUserGuildRequests = source.maxUserGuildRequests;
		maxUserGuildRequestSize = source.maxUserGuildRequestSize;
		maxGuildRecruitTextSize = source.maxGuildRecruitTextSize;
		guildRequestLifetime = source.guildRequestLifetime;
		locales = source.locales;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GuildRecruitment newParent = _newParent as GuildRecruitment;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_maxUserGuildRequests.SetParent( newParent == null ? null : newParent._maxUserGuildRequests );
		_maxUserGuildRequestSize.SetParent( newParent == null ? null : newParent._maxUserGuildRequestSize );
		_maxGuildRecruitTextSize.SetParent( newParent == null ? null : newParent._maxGuildRecruitTextSize );
		_guildRequestLifetime.SetParent( newParent == null ? null : newParent._guildRequestLifetime );
		_locales.SetParent( newParent == null ? null : newParent._locales );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_maxUserGuildRequests.Reset();
		_maxUserGuildRequestSize.Reset();
		_maxGuildRecruitTextSize.Reset();
		_guildRequestLifetime.Reset();
		_locales.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_maxUserGuildRequests.IsDerivedFromParent()
			&& _maxUserGuildRequestSize.IsDerivedFromParent()
			&& _maxGuildRecruitTextSize.IsDerivedFromParent()
			&& _guildRequestLifetime.IsDerivedFromParent()
			&& _locales.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "maxUserGuildRequests" )
			_maxUserGuildRequests.Reset();
		else if ( fieldName == "maxUserGuildRequestSize" )
			_maxUserGuildRequestSize.Reset();
		else if ( fieldName == "maxGuildRecruitTextSize" )
			_maxGuildRecruitTextSize.Reset();
		else if ( fieldName == "guildRequestLifetime" )
			_guildRequestLifetime.Reset();
		else if ( fieldName == "locales" )
			_locales.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "maxUserGuildRequests" )
			return _maxUserGuildRequests.IsDerivedFromParent();
		if ( fieldName == "maxUserGuildRequestSize" )
			return _maxUserGuildRequestSize.IsDerivedFromParent();
		if ( fieldName == "maxGuildRecruitTextSize" )
			return _maxGuildRecruitTextSize.IsDerivedFromParent();
		if ( fieldName == "guildRequestLifetime" )
			return _guildRequestLifetime.IsDerivedFromParent();
		if ( fieldName == "locales" )
			return _locales.IsDerivedFromParent();
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
public class GuildWarEventAward : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GuildWarEventAward __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _maxPlace;
	private UndoRedo<int> _members;
	private GuildWarEventAwardItem _award;

	[Description( "???????????? ????? ????? ? ???? (????????????)" )]
	public int maxPlace { get { return _maxPlace.Get(); } set { _maxPlace.Set( value ); } }

	[Description( "??????? ????? ???????? ??????? ??????????" )]
	public int members { get { return _members.Get(); } set { _members.Set( value ); } }

	[Description( "???????" )]
	public GuildWarEventAwardItem award { get { return _award; } set { _award.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_maxPlace = new UndoRedo<int>( owner, 0 );
		_members = new UndoRedo<int>( owner, 0 );
		_award = new GuildWarEventAwardItem( owner );
		_maxPlace.Changed += FireChangedEvent;
		_members.Changed += FireChangedEvent;
		_award.Changed += FireChangedEvent;
	}

	public GuildWarEventAward()
	{
		Initialize( GetOwner() );
	}

	public GuildWarEventAward( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GuildWarEventAward( DBResource owner, GuildWarEventAward source )
		: this(owner, source, true){}

	protected GuildWarEventAward( DBResource owner, GuildWarEventAward source, bool fireEvent )
	{
		_maxPlace = new UndoRedo<int>( owner, source.maxPlace );
		_members = new UndoRedo<int>( owner, source.members );
		_award = new GuildWarEventAwardItem( owner, source.award );
		_maxPlace.Changed += FireChangedEvent;
		_members.Changed += FireChangedEvent;
		_award.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GuildWarEventAward source = _source as GuildWarEventAward;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildWarEventAward" );
		maxPlace = source.maxPlace;
		members = source.members;
		award = source.award;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GuildWarEventAward newParent = _newParent as GuildWarEventAward;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_maxPlace.SetParent( newParent == null ? null : newParent._maxPlace );
		_members.SetParent( newParent == null ? null : newParent._members );
		_award.SetParent( newParent == null ? null : newParent._award );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_maxPlace.Reset();
		_members.Reset();
		_award.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_maxPlace.IsDerivedFromParent()
			&& _members.IsDerivedFromParent()
			&& _award.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "maxPlace" )
			_maxPlace.Reset();
		else if ( fieldName == "members" )
			_members.Reset();
		else if ( fieldName == "award" )
			_award.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "maxPlace" )
			return _maxPlace.IsDerivedFromParent();
		if ( fieldName == "members" )
			return _members.IsDerivedFromParent();
		if ( fieldName == "award" )
			return _award.IsDerivedFromParent();
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
public class GuildWarEventData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private GuildWarEventData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<Int64> _pointsCap;
	private UndoRedo<int> _duration;
	private UndoRedoAssignableList<GuildWarEventAward> _awards;

	[Description( "?????? ????" )]
	public Int64 pointsCap { get { return _pointsCap.Get(); } set { _pointsCap.Set( value ); } }

	[Description( "???????????? ?????? (? ????)" )]
	public int duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	[Description( "??????? ????????? ?? ?????????? ??????. ???????? ? ??????? ??????????? ?? ?????." )]
	public libdb.IChangeableList<GuildWarEventAward> awards { get { return _awards; } set { _awards.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_pointsCap = new UndoRedo<Int64>( owner, 1000000 );
		_duration = new UndoRedo<int>( owner, 7 );
		_awards = new UndoRedoAssignableList<GuildWarEventAward>( owner );
		_pointsCap.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_awards.Changed += FireChangedEvent;
	}

	public GuildWarEventData()
	{
		Initialize( GetOwner() );
	}

	public GuildWarEventData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public GuildWarEventData( DBResource owner, GuildWarEventData source )
		: this(owner, source, true){}

	protected GuildWarEventData( DBResource owner, GuildWarEventData source, bool fireEvent )
	{
		_pointsCap = new UndoRedo<Int64>( owner, source.pointsCap );
		_duration = new UndoRedo<int>( owner, source.duration );
		_awards = new UndoRedoAssignableList<GuildWarEventAward>( owner );
		_awards.Assign( source.awards );
		_pointsCap.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_awards.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		GuildWarEventData source = _source as GuildWarEventData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GuildWarEventData" );
		pointsCap = source.pointsCap;
		duration = source.duration;
		awards = source.awards;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		GuildWarEventData newParent = _newParent as GuildWarEventData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_pointsCap.SetParent( newParent == null ? null : newParent._pointsCap );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_awards.SetParent( newParent == null ? null : newParent._awards );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_pointsCap.Reset();
		_duration.Reset();
		_awards.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_pointsCap.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _awards.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "pointsCap" )
			_pointsCap.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "awards" )
			_awards.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "pointsCap" )
			return _pointsCap.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "awards" )
			return _awards.IsDerivedFromParent();
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
public class NPCCastle : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private NPCCastle __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _clanName;
	private TextRef _clanShortName;
	private UndoRedo<int> _clanRating;

	[Description( "???????? ?????" )]
	public TextRef clanName { get { return _clanName; } set { _clanName.Assign( value ); } }

	[Description( "???????? ?????" )]
	public TextRef clanShortName { get { return _clanShortName; } set { _clanShortName.Assign( value ); } }

	[Description( "??????? ?????" )]
	public int clanRating { get { return _clanRating.Get(); } set { _clanRating.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_clanName = new TextRef( owner, new TextRef() );
		_clanShortName = new TextRef( owner, new TextRef() );
		_clanRating = new UndoRedo<int>( owner, 0 );
		_clanName.Changed += FireChangedEvent;
		_clanShortName.Changed += FireChangedEvent;
		_clanRating.Changed += FireChangedEvent;
	}

	public NPCCastle()
	{
		Initialize( GetOwner() );
	}

	public NPCCastle( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public NPCCastle( DBResource owner, NPCCastle source )
		: this(owner, source, true){}

	protected NPCCastle( DBResource owner, NPCCastle source, bool fireEvent )
	{
		_clanName = new TextRef( owner, source.clanName );
		_clanShortName = new TextRef( owner, source.clanShortName );
		_clanRating = new UndoRedo<int>( owner, source.clanRating );
		_clanName.Changed += FireChangedEvent;
		_clanShortName.Changed += FireChangedEvent;
		_clanRating.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		NPCCastle source = _source as NPCCastle;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NPCCastle" );
		clanName = source.clanName;
		clanShortName = source.clanShortName;
		clanRating = source.clanRating;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		NPCCastle newParent = _newParent as NPCCastle;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_clanName.SetParent( newParent == null ? null : newParent._clanName );
		_clanShortName.SetParent( newParent == null ? null : newParent._clanShortName );
		_clanRating.SetParent( newParent == null ? null : newParent._clanRating );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_clanName.Reset();
		_clanShortName.Reset();
		_clanRating.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_clanName.IsDerivedFromParent()
			&& _clanShortName.IsDerivedFromParent()
			&& _clanRating.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "clanName" )
			_clanName.Reset();
		else if ( fieldName == "clanShortName" )
			_clanShortName.Reset();
		else if ( fieldName == "clanRating" )
			_clanRating.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "clanName" )
			return _clanName.IsDerivedFromParent();
		if ( fieldName == "clanShortName" )
			return _clanShortName.IsDerivedFromParent();
		if ( fieldName == "clanRating" )
			return _clanRating.IsDerivedFromParent();
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
public class NPCSuzerain : NPCCastle, libdb.ICompositeDBValue, libdb.IChangeable
{

	private NPCSuzerain __parent = null;

	private UndoRedo<int> _defaultSiegePoints;

	[Description( "?????????? ????? ? ????? ?????" )]
	public int defaultSiegePoints { get { return _defaultSiegePoints.Get(); } set { _defaultSiegePoints.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_defaultSiegePoints = new UndoRedo<int>( owner, 0 );
		_defaultSiegePoints.Changed += FireChangedEvent;
	}

	public NPCSuzerain()
	{
		Initialize( GetOwner() );
	}

	public NPCSuzerain( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public NPCSuzerain( DBResource owner, NPCSuzerain source ): base(owner, source, false)
	{
		_defaultSiegePoints = new UndoRedo<int>( owner, source.defaultSiegePoints );
		_defaultSiegePoints.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		NPCSuzerain source = _source as NPCSuzerain;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NPCSuzerain" );

		base.Assign( source );

		defaultSiegePoints = source.defaultSiegePoints;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		NPCSuzerain newParent = _newParent as NPCSuzerain;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_defaultSiegePoints.SetParent( newParent == null ? null : newParent._defaultSiegePoints );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_defaultSiegePoints.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_defaultSiegePoints.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "defaultSiegePoints" )
			_defaultSiegePoints.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "defaultSiegePoints" )
			return _defaultSiegePoints.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class NPCVillage : NPCCastle, libdb.ICompositeDBValue, libdb.IChangeable
{

	private NPCVillage __parent = null;

	private UndoRedo<int> _everyDayProfit;

	[Description( "?????????? ????? ? ????? ?????" )]
	public int everyDayProfit { get { return _everyDayProfit.Get(); } set { _everyDayProfit.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_everyDayProfit = new UndoRedo<int>( owner, 0 );
		_everyDayProfit.Changed += FireChangedEvent;
	}

	public NPCVillage()
	{
		Initialize( GetOwner() );
	}

	public NPCVillage( DBResource owner ) : base( owner )
	{
		Initialize( GetOwner() );
	}

	public NPCVillage( DBResource owner, NPCVillage source ): base(owner, source, false)
	{
		_everyDayProfit = new UndoRedo<int>( owner, source.everyDayProfit );
		_everyDayProfit.Changed += FireChangedEvent;
		FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		NPCVillage source = _source as NPCVillage;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NPCVillage" );

		base.Assign( source );

		everyDayProfit = source.everyDayProfit;
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		base.SetParent(_newParent);

		NPCVillage newParent = _newParent as NPCVillage;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_everyDayProfit.SetParent( newParent == null ? null : newParent._everyDayProfit );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_everyDayProfit.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_everyDayProfit.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "everyDayProfit" )
			_everyDayProfit.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "everyDayProfit" )
			return _everyDayProfit.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("Social")]
public class ClanWarsData : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private ClanWarsData __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private NPCVillage _npcVillage;
	private NPCSuzerain _npcSuzerain;
	private UndoRedo<int> _countOfNPCVillage;
	private UndoRedo<float> _guildVassalsTributeCoef;
	private UndoRedo<int> _shopAncientRating;
	private UndoRedo<float> _defencePointsPercent;
	private UndoRedo<int> _numPlayersFromTopInClanRating;
	private GuildWarEventData _guildWarEventData;

	[Description( "NPC ???????" )]
	public NPCVillage npcVillage { get { return _npcVillage; } set { _npcVillage.Assign( value ); } }

	[Description( "NPC ????????" )]
	public NPCSuzerain npcSuzerain { get { return _npcSuzerain; } set { _npcSuzerain.Assign( value ); } }

	[Description( "?????????? ????????" )]
	public int countOfNPCVillage { get { return _countOfNPCVillage.Get(); } set { _countOfNPCVillage.Set( value ); } }

	[Description( "??????? ?????, ??????? ???????? ??????? ?? ????? ????????" )]
	public float guildVassalsTributeCoef { get { return _guildVassalsTributeCoef.Get(); } set { _guildVassalsTributeCoef.Set( value ); } }

	[Description( "???????, ??????????? ?????? ? ??????? ???????" )]
	public int shopAncientRating { get { return _shopAncientRating.Get(); } set { _shopAncientRating.Set( value ); } }

	[Description( "????? ???? ? ???????? ?? ???? ?, ?????? ???????? ? ??????? ?? ?????? ????? +X% ?????" )]
	public float defencePointsPercent { get { return _defencePointsPercent.Get(); } set { _defencePointsPercent.Set( value ); } }

	[Description( "???-?? ?????? ?? ????????? ???????? ??????? ???????? ?? ??????? ?????" )]
	public int numPlayersFromTopInClanRating { get { return _numPlayersFromTopInClanRating.Get(); } set { _numPlayersFromTopInClanRating.Set( value ); } }

	[Description( "????????? ????????? ??????" )]
	public GuildWarEventData guildWarEventData { get { return _guildWarEventData; } set { _guildWarEventData.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_npcVillage = new NPCVillage( owner );
		_npcSuzerain = new NPCSuzerain( owner );
		_countOfNPCVillage = new UndoRedo<int>( owner, 0 );
		_guildVassalsTributeCoef = new UndoRedo<float>( owner, 0.15f );
		_shopAncientRating = new UndoRedo<int>( owner, 0 );
		_defencePointsPercent = new UndoRedo<float>( owner, 0.05f );
		_numPlayersFromTopInClanRating = new UndoRedo<int>( owner, 20 );
		_guildWarEventData = new GuildWarEventData( owner );
		_npcVillage.Changed += FireChangedEvent;
		_npcSuzerain.Changed += FireChangedEvent;
		_countOfNPCVillage.Changed += FireChangedEvent;
		_guildVassalsTributeCoef.Changed += FireChangedEvent;
		_shopAncientRating.Changed += FireChangedEvent;
		_defencePointsPercent.Changed += FireChangedEvent;
		_numPlayersFromTopInClanRating.Changed += FireChangedEvent;
		_guildWarEventData.Changed += FireChangedEvent;
	}

	public ClanWarsData()
	{
		Initialize( GetOwner() );
	}

	public ClanWarsData( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public ClanWarsData( DBResource owner, ClanWarsData source )
		: this(owner, source, true){}

	protected ClanWarsData( DBResource owner, ClanWarsData source, bool fireEvent )
	{
		_npcVillage = new NPCVillage( owner, source.npcVillage );
		_npcSuzerain = new NPCSuzerain( owner, source.npcSuzerain );
		_countOfNPCVillage = new UndoRedo<int>( owner, source.countOfNPCVillage );
		_guildVassalsTributeCoef = new UndoRedo<float>( owner, source.guildVassalsTributeCoef );
		_shopAncientRating = new UndoRedo<int>( owner, source.shopAncientRating );
		_defencePointsPercent = new UndoRedo<float>( owner, source.defencePointsPercent );
		_numPlayersFromTopInClanRating = new UndoRedo<int>( owner, source.numPlayersFromTopInClanRating );
		_guildWarEventData = new GuildWarEventData( owner, source.guildWarEventData );
		_npcVillage.Changed += FireChangedEvent;
		_npcSuzerain.Changed += FireChangedEvent;
		_countOfNPCVillage.Changed += FireChangedEvent;
		_guildVassalsTributeCoef.Changed += FireChangedEvent;
		_shopAncientRating.Changed += FireChangedEvent;
		_defencePointsPercent.Changed += FireChangedEvent;
		_numPlayersFromTopInClanRating.Changed += FireChangedEvent;
		_guildWarEventData.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		ClanWarsData source = _source as ClanWarsData;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ClanWarsData" );
		npcVillage = source.npcVillage;
		npcSuzerain = source.npcSuzerain;
		countOfNPCVillage = source.countOfNPCVillage;
		guildVassalsTributeCoef = source.guildVassalsTributeCoef;
		shopAncientRating = source.shopAncientRating;
		defencePointsPercent = source.defencePointsPercent;
		numPlayersFromTopInClanRating = source.numPlayersFromTopInClanRating;
		guildWarEventData = source.guildWarEventData;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		ClanWarsData newParent = _newParent as ClanWarsData;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_npcVillage.SetParent( newParent == null ? null : newParent._npcVillage );
		_npcSuzerain.SetParent( newParent == null ? null : newParent._npcSuzerain );
		_countOfNPCVillage.SetParent( newParent == null ? null : newParent._countOfNPCVillage );
		_guildVassalsTributeCoef.SetParent( newParent == null ? null : newParent._guildVassalsTributeCoef );
		_shopAncientRating.SetParent( newParent == null ? null : newParent._shopAncientRating );
		_defencePointsPercent.SetParent( newParent == null ? null : newParent._defencePointsPercent );
		_numPlayersFromTopInClanRating.SetParent( newParent == null ? null : newParent._numPlayersFromTopInClanRating );
		_guildWarEventData.SetParent( newParent == null ? null : newParent._guildWarEventData );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_npcVillage.Reset();
		_npcSuzerain.Reset();
		_countOfNPCVillage.Reset();
		_guildVassalsTributeCoef.Reset();
		_shopAncientRating.Reset();
		_defencePointsPercent.Reset();
		_numPlayersFromTopInClanRating.Reset();
		_guildWarEventData.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_npcVillage.IsDerivedFromParent()
			&& _npcSuzerain.IsDerivedFromParent()
			&& _countOfNPCVillage.IsDerivedFromParent()
			&& _guildVassalsTributeCoef.IsDerivedFromParent()
			&& _shopAncientRating.IsDerivedFromParent()
			&& _defencePointsPercent.IsDerivedFromParent()
			&& _numPlayersFromTopInClanRating.IsDerivedFromParent()
			&& _guildWarEventData.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "npcVillage" )
			_npcVillage.Reset();
		else if ( fieldName == "npcSuzerain" )
			_npcSuzerain.Reset();
		else if ( fieldName == "countOfNPCVillage" )
			_countOfNPCVillage.Reset();
		else if ( fieldName == "guildVassalsTributeCoef" )
			_guildVassalsTributeCoef.Reset();
		else if ( fieldName == "shopAncientRating" )
			_shopAncientRating.Reset();
		else if ( fieldName == "defencePointsPercent" )
			_defencePointsPercent.Reset();
		else if ( fieldName == "numPlayersFromTopInClanRating" )
			_numPlayersFromTopInClanRating.Reset();
		else if ( fieldName == "guildWarEventData" )
			_guildWarEventData.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "npcVillage" )
			return _npcVillage.IsDerivedFromParent();
		if ( fieldName == "npcSuzerain" )
			return _npcSuzerain.IsDerivedFromParent();
		if ( fieldName == "countOfNPCVillage" )
			return _countOfNPCVillage.IsDerivedFromParent();
		if ( fieldName == "guildVassalsTributeCoef" )
			return _guildVassalsTributeCoef.IsDerivedFromParent();
		if ( fieldName == "shopAncientRating" )
			return _shopAncientRating.IsDerivedFromParent();
		if ( fieldName == "defencePointsPercent" )
			return _defencePointsPercent.IsDerivedFromParent();
		if ( fieldName == "numPlayersFromTopInClanRating" )
			return _numPlayersFromTopInClanRating.IsDerivedFromParent();
		if ( fieldName == "guildWarEventData" )
			return _guildWarEventData.IsDerivedFromParent();
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

}; // namespace DBTypes
