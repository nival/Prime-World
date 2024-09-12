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
public class Rank : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Rank __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _rating;
	private TextRef _rankNameA;
	private TextRef _rankNameB;
	private TextRef _rankGroupNameA;
	private TextRef _rankGroupNameB;
	private TextRef _rankTooltipA;
	private TextRef _rankTooltipB;
	private UndoRedoDBPtr<Texture> _iconA;
	private UndoRedoDBPtr<Texture> _bigIconA;
	private UndoRedoDBPtr<Texture> _iconB;
	private UndoRedoDBPtr<Texture> _bigIconB;
	private UndoRedo<float> _recommendedForce;
	private UndoRedo<int> _rewardTalentsCountForUI;

	[Custom("DBServer")]
	[Description( "Звание соответствует рейтингу героя равному или большему указанного" )]
	public int rating { get { return _rating.Get(); } set { _rating.Set( value ); } }

	public TextRef rankNameA { get { return _rankNameA; } set { _rankNameA.Assign( value ); } }

	public TextRef rankNameB { get { return _rankNameB; } set { _rankNameB.Assign( value ); } }

	public TextRef rankGroupNameA { get { return _rankGroupNameA; } set { _rankGroupNameA.Assign( value ); } }

	public TextRef rankGroupNameB { get { return _rankGroupNameB; } set { _rankGroupNameB.Assign( value ); } }

	public TextRef rankTooltipA { get { return _rankTooltipA; } set { _rankTooltipA.Assign( value ); } }

	public TextRef rankTooltipB { get { return _rankTooltipB; } set { _rankTooltipB.Assign( value ); } }

	public DBPtr<Texture> iconA { get { return _iconA.Get(); } set { _iconA.Set( value ); } }

	[Description( "Большая иконка (64*64) (в SeasonRewardWnd и Current/Best Season Results)" )]
	public DBPtr<Texture> bigIconA { get { return _bigIconA.Get(); } set { _bigIconA.Set( value ); } }

	public DBPtr<Texture> iconB { get { return _iconB.Get(); } set { _iconB.Set( value ); } }

	[Description( "см описание bigIconA" )]
	public DBPtr<Texture> bigIconB { get { return _bigIconB.Get(); } set { _bigIconB.Set( value ); } }

	[Description( "рекомендованная моща для звания. Поле нужно для показа предупреждения. Например 140 (а не 1400)" )]
	public float recommendedForce { get { return _recommendedForce.Get(); } set { _recommendedForce.Set( value ); } }

	[Description( "максимально количество талантов за обычную сессию. используется ТОЛЬКО в UI" )]
	public int rewardTalentsCountForUI { get { return _rewardTalentsCountForUI.Get(); } set { _rewardTalentsCountForUI.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_rating = new UndoRedo<int>( owner, 0 );
		_rankNameA = new TextRef( owner, new TextRef() );
		_rankNameB = new TextRef( owner, new TextRef() );
		_rankGroupNameA = new TextRef( owner, new TextRef() );
		_rankGroupNameB = new TextRef( owner, new TextRef() );
		_rankTooltipA = new TextRef( owner, new TextRef() );
		_rankTooltipB = new TextRef( owner, new TextRef() );
		_iconA = new UndoRedoDBPtr<Texture>( owner );
		_bigIconA = new UndoRedoDBPtr<Texture>( owner );
		_iconB = new UndoRedoDBPtr<Texture>( owner );
		_bigIconB = new UndoRedoDBPtr<Texture>( owner );
		_recommendedForce = new UndoRedo<float>( owner, 0.0f );
		_rewardTalentsCountForUI = new UndoRedo<int>( owner, 0 );
		_rating.Changed += FireChangedEvent;
		_rankNameA.Changed += FireChangedEvent;
		_rankNameB.Changed += FireChangedEvent;
		_rankGroupNameA.Changed += FireChangedEvent;
		_rankGroupNameB.Changed += FireChangedEvent;
		_rankTooltipA.Changed += FireChangedEvent;
		_rankTooltipB.Changed += FireChangedEvent;
		_iconA.Changed += FireChangedEvent;
		_bigIconA.Changed += FireChangedEvent;
		_iconB.Changed += FireChangedEvent;
		_bigIconB.Changed += FireChangedEvent;
		_recommendedForce.Changed += FireChangedEvent;
		_rewardTalentsCountForUI.Changed += FireChangedEvent;
	}

	public Rank()
	{
		Initialize( GetOwner() );
	}

	public Rank( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Rank( DBResource owner, Rank source )
		: this(owner, source, true){}

	protected Rank( DBResource owner, Rank source, bool fireEvent )
	{
		_rating = new UndoRedo<int>( owner, source.rating );
		_rankNameA = new TextRef( owner, source.rankNameA );
		_rankNameB = new TextRef( owner, source.rankNameB );
		_rankGroupNameA = new TextRef( owner, source.rankGroupNameA );
		_rankGroupNameB = new TextRef( owner, source.rankGroupNameB );
		_rankTooltipA = new TextRef( owner, source.rankTooltipA );
		_rankTooltipB = new TextRef( owner, source.rankTooltipB );
		_iconA = new UndoRedoDBPtr<Texture>( owner, source.iconA );
		_bigIconA = new UndoRedoDBPtr<Texture>( owner, source.bigIconA );
		_iconB = new UndoRedoDBPtr<Texture>( owner, source.iconB );
		_bigIconB = new UndoRedoDBPtr<Texture>( owner, source.bigIconB );
		_recommendedForce = new UndoRedo<float>( owner, source.recommendedForce );
		_rewardTalentsCountForUI = new UndoRedo<int>( owner, source.rewardTalentsCountForUI );
		_rating.Changed += FireChangedEvent;
		_rankNameA.Changed += FireChangedEvent;
		_rankNameB.Changed += FireChangedEvent;
		_rankGroupNameA.Changed += FireChangedEvent;
		_rankGroupNameB.Changed += FireChangedEvent;
		_rankTooltipA.Changed += FireChangedEvent;
		_rankTooltipB.Changed += FireChangedEvent;
		_iconA.Changed += FireChangedEvent;
		_bigIconA.Changed += FireChangedEvent;
		_iconB.Changed += FireChangedEvent;
		_bigIconB.Changed += FireChangedEvent;
		_recommendedForce.Changed += FireChangedEvent;
		_rewardTalentsCountForUI.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Rank source = _source as Rank;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Rank" );
		rating = source.rating;
		rankNameA = source.rankNameA;
		rankNameB = source.rankNameB;
		rankGroupNameA = source.rankGroupNameA;
		rankGroupNameB = source.rankGroupNameB;
		rankTooltipA = source.rankTooltipA;
		rankTooltipB = source.rankTooltipB;
		iconA = source.iconA;
		bigIconA = source.bigIconA;
		iconB = source.iconB;
		bigIconB = source.bigIconB;
		recommendedForce = source.recommendedForce;
		rewardTalentsCountForUI = source.rewardTalentsCountForUI;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Rank newParent = _newParent as Rank;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_rating.SetParent( newParent == null ? null : newParent._rating );
		_rankNameA.SetParent( newParent == null ? null : newParent._rankNameA );
		_rankNameB.SetParent( newParent == null ? null : newParent._rankNameB );
		_rankGroupNameA.SetParent( newParent == null ? null : newParent._rankGroupNameA );
		_rankGroupNameB.SetParent( newParent == null ? null : newParent._rankGroupNameB );
		_rankTooltipA.SetParent( newParent == null ? null : newParent._rankTooltipA );
		_rankTooltipB.SetParent( newParent == null ? null : newParent._rankTooltipB );
		_iconA.SetParent( newParent == null ? null : newParent._iconA );
		_bigIconA.SetParent( newParent == null ? null : newParent._bigIconA );
		_iconB.SetParent( newParent == null ? null : newParent._iconB );
		_bigIconB.SetParent( newParent == null ? null : newParent._bigIconB );
		_recommendedForce.SetParent( newParent == null ? null : newParent._recommendedForce );
		_rewardTalentsCountForUI.SetParent( newParent == null ? null : newParent._rewardTalentsCountForUI );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_rating.Reset();
		_rankNameA.Reset();
		_rankNameB.Reset();
		_rankGroupNameA.Reset();
		_rankGroupNameB.Reset();
		_rankTooltipA.Reset();
		_rankTooltipB.Reset();
		_iconA.Reset();
		_bigIconA.Reset();
		_iconB.Reset();
		_bigIconB.Reset();
		_recommendedForce.Reset();
		_rewardTalentsCountForUI.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_rating.IsDerivedFromParent()
			&& _rankNameA.IsDerivedFromParent()
			&& _rankNameB.IsDerivedFromParent()
			&& _rankGroupNameA.IsDerivedFromParent()
			&& _rankGroupNameB.IsDerivedFromParent()
			&& _rankTooltipA.IsDerivedFromParent()
			&& _rankTooltipB.IsDerivedFromParent()
			&& _iconA.IsDerivedFromParent()
			&& _bigIconA.IsDerivedFromParent()
			&& _iconB.IsDerivedFromParent()
			&& _bigIconB.IsDerivedFromParent()
			&& _recommendedForce.IsDerivedFromParent()
			&& _rewardTalentsCountForUI.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "rating" )
			_rating.Reset();
		else if ( fieldName == "rankNameA" )
			_rankNameA.Reset();
		else if ( fieldName == "rankNameB" )
			_rankNameB.Reset();
		else if ( fieldName == "rankGroupNameA" )
			_rankGroupNameA.Reset();
		else if ( fieldName == "rankGroupNameB" )
			_rankGroupNameB.Reset();
		else if ( fieldName == "rankTooltipA" )
			_rankTooltipA.Reset();
		else if ( fieldName == "rankTooltipB" )
			_rankTooltipB.Reset();
		else if ( fieldName == "iconA" )
			_iconA.Reset();
		else if ( fieldName == "bigIconA" )
			_bigIconA.Reset();
		else if ( fieldName == "iconB" )
			_iconB.Reset();
		else if ( fieldName == "bigIconB" )
			_bigIconB.Reset();
		else if ( fieldName == "recommendedForce" )
			_recommendedForce.Reset();
		else if ( fieldName == "rewardTalentsCountForUI" )
			_rewardTalentsCountForUI.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "rating" )
			return _rating.IsDerivedFromParent();
		if ( fieldName == "rankNameA" )
			return _rankNameA.IsDerivedFromParent();
		if ( fieldName == "rankNameB" )
			return _rankNameB.IsDerivedFromParent();
		if ( fieldName == "rankGroupNameA" )
			return _rankGroupNameA.IsDerivedFromParent();
		if ( fieldName == "rankGroupNameB" )
			return _rankGroupNameB.IsDerivedFromParent();
		if ( fieldName == "rankTooltipA" )
			return _rankTooltipA.IsDerivedFromParent();
		if ( fieldName == "rankTooltipB" )
			return _rankTooltipB.IsDerivedFromParent();
		if ( fieldName == "iconA" )
			return _iconA.IsDerivedFromParent();
		if ( fieldName == "bigIconA" )
			return _bigIconA.IsDerivedFromParent();
		if ( fieldName == "iconB" )
			return _iconB.IsDerivedFromParent();
		if ( fieldName == "bigIconB" )
			return _bigIconB.IsDerivedFromParent();
		if ( fieldName == "recommendedForce" )
			return _recommendedForce.IsDerivedFromParent();
		if ( fieldName == "rewardTalentsCountForUI" )
			return _rewardTalentsCountForUI.IsDerivedFromParent();
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

[Custom("DBServer", "Social")]
[DBVersion(0)]
[UseTypeName("HRANKS")]
public class HeroRanks : DBResource
{
	private UndoRedoDBPtr<HeroRanks> ___parent;
	[HideInOutliner]
	public new DBPtr<HeroRanks> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _highLevelsMMRating;
	private UndoRedoAssignableList<Rank> _ranks;

	[Description( "Рейтинг, начиная с которого в тамбуре можно выбирать всех героев, которые выше по званию" )]
	public int highLevelsMMRating { get { return _highLevelsMMRating.Get(); } set { _highLevelsMMRating.Set( value ); } }

	[Description( "Список соответствий рейтинг-звание" )]
	public libdb.IChangeableList<Rank> ranks { get { return _ranks; } set { _ranks.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<HeroRanks>(owner);
		_highLevelsMMRating = new UndoRedo<int>( owner, 2000 );
		_ranks = new UndoRedoAssignableList<Rank>( owner );
		___parent.Changed += FireChangedEvent;
		_highLevelsMMRating.Changed += FireChangedEvent;
		_ranks.Changed += FireChangedEvent;
	}

	public HeroRanks()
	{
		Initialize( this );
	}
	private void AssignSelf( HeroRanks source )
	{
		DataBase.UndoRedoManager.Start( "Assign for HeroRanks" );
		highLevelsMMRating = source.highLevelsMMRating;
		ranks = source.ranks;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		HeroRanks source = _source as HeroRanks;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HeroRanks" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		HeroRanks newParent = rawParent == null ? null : rawParent.Get<HeroRanks>();
		if ( newParent == null && _newParent is HeroRanks )
			newParent = _newParent as HeroRanks;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_highLevelsMMRating.SetParent( newParent == null ? null : newParent._highLevelsMMRating );
		_ranks.SetParent( newParent == null ? null : newParent._ranks );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_highLevelsMMRating.Reset();
		_ranks.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_highLevelsMMRating.IsDerivedFromParent()
			&& _ranks.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "highLevelsMMRating" )
			_highLevelsMMRating.Reset();
		else if ( fieldName == "ranks" )
			_ranks.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "highLevelsMMRating" )
			return _highLevelsMMRating.IsDerivedFromParent();
		if ( fieldName == "ranks" )
			return _ranks.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
