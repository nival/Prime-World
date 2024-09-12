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
public enum EBonusType
{
	Broom = 0,
	ComfortablePillow = 1,
	Booklet = 2,
	ComfortableTable = 3,
	Bell = 4,
	Footpaths = 5,
	Whip = 6,
	VelvetGloves = 7,
	AdvencedEntrace = 8,
	Candy = 9,
	Talisman = 10,
	ToyBox = 11,
	SpeedBoots = 12,
	ComfortableCarpet = 13,
	SuperCleaner = 14,
	BootCovers = 15,
	BestClinic = 16,
	Star = 17,
};

public enum EClinicSounds
{
	StartLevel = 0,
	LevelWinWithMedal = 1,
	LevelWinWithoutMedal = 2,
	CreepWishMelee = 3,
	CreepWishRanged = 4,
	CreepWishSiege = 5,
	CreepWishDesiredMelee = 6,
	CreepWishDesiredRanged = 7,
	CreepWishDesiredSiege = 8,
	CreepBecomeLazy = 9,
	CreepLooseWish = 10,
	UseTable = 11,
	UseWashtab = 12,
	UseBad = 13,
	UsePlayground = 14,
	CreepFriendship = 15,
	CreepBar25 = 16,
	CreepBar50 = 17,
	CreepWakeup = 18,
	PlaceBecomeDirty = 19,
	Buy = 20,
};

public enum ECreepState
{
	Working = 0,
	Sleeping = 1,
	NeedWash = 2,
};

public enum ECreepWish
{
	None = 0,
	Sleep = 1,
	Wash = 2,
	Eat = 3,
	Play = 4,
	Carpet = 5,
	Any = 6,
	Exit = 7,
};

public enum EPlaceType
{
	None = 0,
	Table = 1,
	Bad = 2,
	Washtab = 3,
	GamePlace = 4,
	CreepPlace = 5,
	Entrance = 6,
};

public class BonusDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private BonusDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private TextRef _description;
	private TextRef _name;
	private Vec3 _position;
	private UndoRedo<float> _cooldown;
	private UndoRedo<float> _duration;
	private UndoRedo<int> _accessibility;
	private UndoRedo<int> _cost;
	private UndoRedo<int> _useCost;
	private UndoRedo<float> _value;
	private UndoRedoDBPtr<DBSceneObject> _sceneObject;
	private UndoRedoDBPtr<UIObjectOvertips> _overtip;
	private UndoRedoDBPtr<BaseUIMaterial> _iconMaterial;

	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public Vec3 position { get { return _position; } set { _position.Assign( value ); } }

	public float cooldown { get { return _cooldown.Get(); } set { _cooldown.Set( value ); } }

	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	public int accessibility { get { return _accessibility.Get(); } set { _accessibility.Set( value ); } }

	public int cost { get { return _cost.Get(); } set { _cost.Set( value ); } }

	public int useCost { get { return _useCost.Get(); } set { _useCost.Set( value ); } }

	public float value { get { return _value.Get(); } set { _value.Set( value ); } }

	public DBPtr<DBSceneObject> sceneObject { get { return _sceneObject.Get(); } set { _sceneObject.Set( value ); } }

	public DBPtr<UIObjectOvertips> overtip { get { return _overtip.Get(); } set { _overtip.Set( value ); } }

	public DBPtr<BaseUIMaterial> iconMaterial { get { return _iconMaterial.Get(); } set { _iconMaterial.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_description = new TextRef( owner, new TextRef() );
		_name = new TextRef( owner, new TextRef() );
		Vec3 __position = new Vec3(); // Construct default object for position
		__position.y = 1.1f;
		__position.z = 0.2f;
		_position = new Vec3( owner, __position );
		_cooldown = new UndoRedo<float>( owner, 0.0f );
		_duration = new UndoRedo<float>( owner, 20.0f );
		_accessibility = new UndoRedo<int>( owner, -1 );
		_cost = new UndoRedo<int>( owner, 100 );
		_useCost = new UndoRedo<int>( owner, 10 );
		_value = new UndoRedo<float>( owner, 1.0f );
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		_overtip = new UndoRedoDBPtr<UIObjectOvertips>( owner );
		_iconMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_description.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_accessibility.Changed += FireChangedEvent;
		_cost.Changed += FireChangedEvent;
		_useCost.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
		_overtip.Changed += FireChangedEvent;
		_iconMaterial.Changed += FireChangedEvent;
	}

	public BonusDesc()
	{
		Initialize( GetOwner() );
	}

	public BonusDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public BonusDesc( DBResource owner, BonusDesc source )
		: this(owner, source, true){}

	protected BonusDesc( DBResource owner, BonusDesc source, bool fireEvent )
	{
		_description = new TextRef( owner, source.description );
		_name = new TextRef( owner, source.name );
		_position = new Vec3( owner, source.position );
		_cooldown = new UndoRedo<float>( owner, source.cooldown );
		_duration = new UndoRedo<float>( owner, source.duration );
		_accessibility = new UndoRedo<int>( owner, source.accessibility );
		_cost = new UndoRedo<int>( owner, source.cost );
		_useCost = new UndoRedo<int>( owner, source.useCost );
		_value = new UndoRedo<float>( owner, source.value );
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner, source.sceneObject );
		_overtip = new UndoRedoDBPtr<UIObjectOvertips>( owner, source.overtip );
		_iconMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner, source.iconMaterial );
		_description.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_cooldown.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_accessibility.Changed += FireChangedEvent;
		_cost.Changed += FireChangedEvent;
		_useCost.Changed += FireChangedEvent;
		_value.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
		_overtip.Changed += FireChangedEvent;
		_iconMaterial.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		BonusDesc source = _source as BonusDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BonusDesc" );
		description = source.description;
		name = source.name;
		position = source.position;
		cooldown = source.cooldown;
		duration = source.duration;
		accessibility = source.accessibility;
		cost = source.cost;
		useCost = source.useCost;
		value = source.value;
		sceneObject = source.sceneObject;
		overtip = source.overtip;
		iconMaterial = source.iconMaterial;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		BonusDesc newParent = _newParent as BonusDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_description.SetParent( newParent == null ? null : newParent._description );
		_name.SetParent( newParent == null ? null : newParent._name );
		_position.SetParent( newParent == null ? null : newParent._position );
		_cooldown.SetParent( newParent == null ? null : newParent._cooldown );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_accessibility.SetParent( newParent == null ? null : newParent._accessibility );
		_cost.SetParent( newParent == null ? null : newParent._cost );
		_useCost.SetParent( newParent == null ? null : newParent._useCost );
		_value.SetParent( newParent == null ? null : newParent._value );
		_sceneObject.SetParent( newParent == null ? null : newParent._sceneObject );
		_overtip.SetParent( newParent == null ? null : newParent._overtip );
		_iconMaterial.SetParent( newParent == null ? null : newParent._iconMaterial );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_description.Reset();
		_name.Reset();
		_position.Reset();
		_cooldown.Reset();
		_duration.Reset();
		_accessibility.Reset();
		_cost.Reset();
		_useCost.Reset();
		_value.Reset();
		_sceneObject.Reset();
		_overtip.Reset();
		_iconMaterial.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_description.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _position.IsDerivedFromParent()
			&& _cooldown.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _accessibility.IsDerivedFromParent()
			&& _cost.IsDerivedFromParent()
			&& _useCost.IsDerivedFromParent()
			&& _value.IsDerivedFromParent()
			&& _sceneObject.IsDerivedFromParent()
			&& _overtip.IsDerivedFromParent()
			&& _iconMaterial.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "position" )
			_position.Reset();
		else if ( fieldName == "cooldown" )
			_cooldown.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "accessibility" )
			_accessibility.Reset();
		else if ( fieldName == "cost" )
			_cost.Reset();
		else if ( fieldName == "useCost" )
			_useCost.Reset();
		else if ( fieldName == "value" )
			_value.Reset();
		else if ( fieldName == "sceneObject" )
			_sceneObject.Reset();
		else if ( fieldName == "overtip" )
			_overtip.Reset();
		else if ( fieldName == "iconMaterial" )
			_iconMaterial.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
		if ( fieldName == "cooldown" )
			return _cooldown.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "accessibility" )
			return _accessibility.IsDerivedFromParent();
		if ( fieldName == "cost" )
			return _cost.IsDerivedFromParent();
		if ( fieldName == "useCost" )
			return _useCost.IsDerivedFromParent();
		if ( fieldName == "value" )
			return _value.IsDerivedFromParent();
		if ( fieldName == "sceneObject" )
			return _sceneObject.IsDerivedFromParent();
		if ( fieldName == "overtip" )
			return _overtip.IsDerivedFromParent();
		if ( fieldName == "iconMaterial" )
			return _iconMaterial.IsDerivedFromParent();
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

public class CreepBehaviourDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CreepBehaviourDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _timeBeforeSearchFriend;
	private UndoRedo<float> _friendshipBonus;

	[Description( "Pause before friend searching" )]
	public float timeBeforeSearchFriend { get { return _timeBeforeSearchFriend.Get(); } set { _timeBeforeSearchFriend.Set( value ); } }

	[Description( "Bonus for friendship" )]
	public float friendshipBonus { get { return _friendshipBonus.Get(); } set { _friendshipBonus.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_timeBeforeSearchFriend = new UndoRedo<float>( owner, 0.0f );
		_friendshipBonus = new UndoRedo<float>( owner, 0.02f );
		_timeBeforeSearchFriend.Changed += FireChangedEvent;
		_friendshipBonus.Changed += FireChangedEvent;
	}

	public CreepBehaviourDesc()
	{
		Initialize( GetOwner() );
	}

	public CreepBehaviourDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CreepBehaviourDesc( DBResource owner, CreepBehaviourDesc source )
		: this(owner, source, true){}

	protected CreepBehaviourDesc( DBResource owner, CreepBehaviourDesc source, bool fireEvent )
	{
		_timeBeforeSearchFriend = new UndoRedo<float>( owner, source.timeBeforeSearchFriend );
		_friendshipBonus = new UndoRedo<float>( owner, source.friendshipBonus );
		_timeBeforeSearchFriend.Changed += FireChangedEvent;
		_friendshipBonus.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CreepBehaviourDesc source = _source as CreepBehaviourDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepBehaviourDesc" );
		timeBeforeSearchFriend = source.timeBeforeSearchFriend;
		friendshipBonus = source.friendshipBonus;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CreepBehaviourDesc newParent = _newParent as CreepBehaviourDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_timeBeforeSearchFriend.SetParent( newParent == null ? null : newParent._timeBeforeSearchFriend );
		_friendshipBonus.SetParent( newParent == null ? null : newParent._friendshipBonus );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_timeBeforeSearchFriend.Reset();
		_friendshipBonus.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_timeBeforeSearchFriend.IsDerivedFromParent()
			&& _friendshipBonus.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "timeBeforeSearchFriend" )
			_timeBeforeSearchFriend.Reset();
		else if ( fieldName == "friendshipBonus" )
			_friendshipBonus.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "timeBeforeSearchFriend" )
			return _timeBeforeSearchFriend.IsDerivedFromParent();
		if ( fieldName == "friendshipBonus" )
			return _friendshipBonus.IsDerivedFromParent();
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

public class CreepPlaceDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CreepPlaceDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec3 _position;

	public Vec3 position { get { return _position; } set { _position.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_position = new Vec3( owner );
		_position.Changed += FireChangedEvent;
	}

	public CreepPlaceDesc()
	{
		Initialize( GetOwner() );
	}

	public CreepPlaceDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CreepPlaceDesc( DBResource owner, CreepPlaceDesc source )
		: this(owner, source, true){}

	protected CreepPlaceDesc( DBResource owner, CreepPlaceDesc source, bool fireEvent )
	{
		_position = new Vec3( owner, source.position );
		_position.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CreepPlaceDesc source = _source as CreepPlaceDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepPlaceDesc" );
		position = source.position;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CreepPlaceDesc newParent = _newParent as CreepPlaceDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_position.SetParent( newParent == null ? null : newParent._position );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_position.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_position.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "position" )
			_position.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
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

public class CreepsDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private CreepsDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoDBPtr<DBSceneObject> _sceneObjectMelee;
	private UndoRedoDBPtr<DBSceneObject> _sceneObjectRange;
	private UndoRedoDBPtr<DBSceneObject> _sceneObjectSiege;
	private UndoRedoDBPtr<BaseUIMaterial> _imageMeleeMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _imageRangeMaterial;
	private UndoRedoDBPtr<BaseUIMaterial> _imageSiegeMaterial;
	private UndoRedoDBPtr<UIObjectOvertips> _overtip;
	private UndoRedo<float> _goldMedalValue;
	private UndoRedo<float> _silverMedalValue;
	private UndoRedoAssignableList<CreepPlaceDesc> _creepPlaces;

	public DBPtr<DBSceneObject> sceneObjectMelee { get { return _sceneObjectMelee.Get(); } set { _sceneObjectMelee.Set( value ); } }

	public DBPtr<DBSceneObject> sceneObjectRange { get { return _sceneObjectRange.Get(); } set { _sceneObjectRange.Set( value ); } }

	public DBPtr<DBSceneObject> sceneObjectSiege { get { return _sceneObjectSiege.Get(); } set { _sceneObjectSiege.Set( value ); } }

	public DBPtr<BaseUIMaterial> imageMeleeMaterial { get { return _imageMeleeMaterial.Get(); } set { _imageMeleeMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> imageRangeMaterial { get { return _imageRangeMaterial.Get(); } set { _imageRangeMaterial.Set( value ); } }

	public DBPtr<BaseUIMaterial> imageSiegeMaterial { get { return _imageSiegeMaterial.Get(); } set { _imageSiegeMaterial.Set( value ); } }

	public DBPtr<UIObjectOvertips> overtip { get { return _overtip.Get(); } set { _overtip.Set( value ); } }

	public float goldMedalValue { get { return _goldMedalValue.Get(); } set { _goldMedalValue.Set( value ); } }

	public float silverMedalValue { get { return _silverMedalValue.Get(); } set { _silverMedalValue.Set( value ); } }

	public libdb.IChangeableList<CreepPlaceDesc> creepPlaces { get { return _creepPlaces; } set { _creepPlaces.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_sceneObjectMelee = new UndoRedoDBPtr<DBSceneObject>( owner );
		_sceneObjectRange = new UndoRedoDBPtr<DBSceneObject>( owner );
		_sceneObjectSiege = new UndoRedoDBPtr<DBSceneObject>( owner );
		_imageMeleeMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_imageRangeMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_imageSiegeMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_overtip = new UndoRedoDBPtr<UIObjectOvertips>( owner );
		_goldMedalValue = new UndoRedo<float>( owner, 0.75f );
		_silverMedalValue = new UndoRedo<float>( owner, 0.5f );
		_creepPlaces = new UndoRedoAssignableList<CreepPlaceDesc>( owner );
		_sceneObjectMelee.Changed += FireChangedEvent;
		_sceneObjectRange.Changed += FireChangedEvent;
		_sceneObjectSiege.Changed += FireChangedEvent;
		_imageMeleeMaterial.Changed += FireChangedEvent;
		_imageRangeMaterial.Changed += FireChangedEvent;
		_imageSiegeMaterial.Changed += FireChangedEvent;
		_overtip.Changed += FireChangedEvent;
		_goldMedalValue.Changed += FireChangedEvent;
		_silverMedalValue.Changed += FireChangedEvent;
		_creepPlaces.Changed += FireChangedEvent;
	}

	public CreepsDesc()
	{
		Initialize( GetOwner() );
	}

	public CreepsDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public CreepsDesc( DBResource owner, CreepsDesc source )
		: this(owner, source, true){}

	protected CreepsDesc( DBResource owner, CreepsDesc source, bool fireEvent )
	{
		_sceneObjectMelee = new UndoRedoDBPtr<DBSceneObject>( owner, source.sceneObjectMelee );
		_sceneObjectRange = new UndoRedoDBPtr<DBSceneObject>( owner, source.sceneObjectRange );
		_sceneObjectSiege = new UndoRedoDBPtr<DBSceneObject>( owner, source.sceneObjectSiege );
		_imageMeleeMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner, source.imageMeleeMaterial );
		_imageRangeMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner, source.imageRangeMaterial );
		_imageSiegeMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner, source.imageSiegeMaterial );
		_overtip = new UndoRedoDBPtr<UIObjectOvertips>( owner, source.overtip );
		_goldMedalValue = new UndoRedo<float>( owner, source.goldMedalValue );
		_silverMedalValue = new UndoRedo<float>( owner, source.silverMedalValue );
		_creepPlaces = new UndoRedoAssignableList<CreepPlaceDesc>( owner );
		_creepPlaces.Assign( source.creepPlaces );
		_sceneObjectMelee.Changed += FireChangedEvent;
		_sceneObjectRange.Changed += FireChangedEvent;
		_sceneObjectSiege.Changed += FireChangedEvent;
		_imageMeleeMaterial.Changed += FireChangedEvent;
		_imageRangeMaterial.Changed += FireChangedEvent;
		_imageSiegeMaterial.Changed += FireChangedEvent;
		_overtip.Changed += FireChangedEvent;
		_goldMedalValue.Changed += FireChangedEvent;
		_silverMedalValue.Changed += FireChangedEvent;
		_creepPlaces.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		CreepsDesc source = _source as CreepsDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CreepsDesc" );
		sceneObjectMelee = source.sceneObjectMelee;
		sceneObjectRange = source.sceneObjectRange;
		sceneObjectSiege = source.sceneObjectSiege;
		imageMeleeMaterial = source.imageMeleeMaterial;
		imageRangeMaterial = source.imageRangeMaterial;
		imageSiegeMaterial = source.imageSiegeMaterial;
		overtip = source.overtip;
		goldMedalValue = source.goldMedalValue;
		silverMedalValue = source.silverMedalValue;
		creepPlaces = source.creepPlaces;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		CreepsDesc newParent = _newParent as CreepsDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_sceneObjectMelee.SetParent( newParent == null ? null : newParent._sceneObjectMelee );
		_sceneObjectRange.SetParent( newParent == null ? null : newParent._sceneObjectRange );
		_sceneObjectSiege.SetParent( newParent == null ? null : newParent._sceneObjectSiege );
		_imageMeleeMaterial.SetParent( newParent == null ? null : newParent._imageMeleeMaterial );
		_imageRangeMaterial.SetParent( newParent == null ? null : newParent._imageRangeMaterial );
		_imageSiegeMaterial.SetParent( newParent == null ? null : newParent._imageSiegeMaterial );
		_overtip.SetParent( newParent == null ? null : newParent._overtip );
		_goldMedalValue.SetParent( newParent == null ? null : newParent._goldMedalValue );
		_silverMedalValue.SetParent( newParent == null ? null : newParent._silverMedalValue );
		_creepPlaces.SetParent( newParent == null ? null : newParent._creepPlaces );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_sceneObjectMelee.Reset();
		_sceneObjectRange.Reset();
		_sceneObjectSiege.Reset();
		_imageMeleeMaterial.Reset();
		_imageRangeMaterial.Reset();
		_imageSiegeMaterial.Reset();
		_overtip.Reset();
		_goldMedalValue.Reset();
		_silverMedalValue.Reset();
		_creepPlaces.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_sceneObjectMelee.IsDerivedFromParent()
			&& _sceneObjectRange.IsDerivedFromParent()
			&& _sceneObjectSiege.IsDerivedFromParent()
			&& _imageMeleeMaterial.IsDerivedFromParent()
			&& _imageRangeMaterial.IsDerivedFromParent()
			&& _imageSiegeMaterial.IsDerivedFromParent()
			&& _overtip.IsDerivedFromParent()
			&& _goldMedalValue.IsDerivedFromParent()
			&& _silverMedalValue.IsDerivedFromParent()
			&& _creepPlaces.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "sceneObjectMelee" )
			_sceneObjectMelee.Reset();
		else if ( fieldName == "sceneObjectRange" )
			_sceneObjectRange.Reset();
		else if ( fieldName == "sceneObjectSiege" )
			_sceneObjectSiege.Reset();
		else if ( fieldName == "imageMeleeMaterial" )
			_imageMeleeMaterial.Reset();
		else if ( fieldName == "imageRangeMaterial" )
			_imageRangeMaterial.Reset();
		else if ( fieldName == "imageSiegeMaterial" )
			_imageSiegeMaterial.Reset();
		else if ( fieldName == "overtip" )
			_overtip.Reset();
		else if ( fieldName == "goldMedalValue" )
			_goldMedalValue.Reset();
		else if ( fieldName == "silverMedalValue" )
			_silverMedalValue.Reset();
		else if ( fieldName == "creepPlaces" )
			_creepPlaces.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "sceneObjectMelee" )
			return _sceneObjectMelee.IsDerivedFromParent();
		if ( fieldName == "sceneObjectRange" )
			return _sceneObjectRange.IsDerivedFromParent();
		if ( fieldName == "sceneObjectSiege" )
			return _sceneObjectSiege.IsDerivedFromParent();
		if ( fieldName == "imageMeleeMaterial" )
			return _imageMeleeMaterial.IsDerivedFromParent();
		if ( fieldName == "imageRangeMaterial" )
			return _imageRangeMaterial.IsDerivedFromParent();
		if ( fieldName == "imageSiegeMaterial" )
			return _imageSiegeMaterial.IsDerivedFromParent();
		if ( fieldName == "overtip" )
			return _overtip.IsDerivedFromParent();
		if ( fieldName == "goldMedalValue" )
			return _goldMedalValue.IsDerivedFromParent();
		if ( fieldName == "silverMedalValue" )
			return _silverMedalValue.IsDerivedFromParent();
		if ( fieldName == "creepPlaces" )
			return _creepPlaces.IsDerivedFromParent();
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

public class DecorationDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DecorationDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec3 _position;
	private UndoRedoDBPtr<DBSceneObject> _sceneObject;

	public Vec3 position { get { return _position; } set { _position.Assign( value ); } }

	public DBPtr<DBSceneObject> sceneObject { get { return _sceneObject.Get(); } set { _sceneObject.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_position = new Vec3( owner );
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		_position.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
	}

	public DecorationDesc()
	{
		Initialize( GetOwner() );
	}

	public DecorationDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DecorationDesc( DBResource owner, DecorationDesc source )
		: this(owner, source, true){}

	protected DecorationDesc( DBResource owner, DecorationDesc source, bool fireEvent )
	{
		_position = new Vec3( owner, source.position );
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner, source.sceneObject );
		_position.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DecorationDesc source = _source as DecorationDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DecorationDesc" );
		position = source.position;
		sceneObject = source.sceneObject;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DecorationDesc newParent = _newParent as DecorationDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_position.SetParent( newParent == null ? null : newParent._position );
		_sceneObject.SetParent( newParent == null ? null : newParent._sceneObject );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_position.Reset();
		_sceneObject.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_position.IsDerivedFromParent()
			&& _sceneObject.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "position" )
			_position.Reset();
		else if ( fieldName == "sceneObject" )
			_sceneObject.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
		if ( fieldName == "sceneObject" )
			return _sceneObject.IsDerivedFromParent();
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

public class IntOffsets : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private IntOffsets __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _pxBefore;
	private UndoRedo<int> _pxAfter;

	public int pxBefore { get { return _pxBefore.Get(); } set { _pxBefore.Set( value ); } }

	public int pxAfter { get { return _pxAfter.Get(); } set { _pxAfter.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_pxBefore = new UndoRedo<int>( owner, 0 );
		_pxAfter = new UndoRedo<int>( owner, 0 );
		_pxBefore.Changed += FireChangedEvent;
		_pxAfter.Changed += FireChangedEvent;
	}

	public IntOffsets()
	{
		Initialize( GetOwner() );
	}

	public IntOffsets( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public IntOffsets( DBResource owner, IntOffsets source )
		: this(owner, source, true){}

	protected IntOffsets( DBResource owner, IntOffsets source, bool fireEvent )
	{
		_pxBefore = new UndoRedo<int>( owner, source.pxBefore );
		_pxAfter = new UndoRedo<int>( owner, source.pxAfter );
		_pxBefore.Changed += FireChangedEvent;
		_pxAfter.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		IntOffsets source = _source as IntOffsets;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for IntOffsets" );
		pxBefore = source.pxBefore;
		pxAfter = source.pxAfter;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		IntOffsets newParent = _newParent as IntOffsets;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_pxBefore.SetParent( newParent == null ? null : newParent._pxBefore );
		_pxAfter.SetParent( newParent == null ? null : newParent._pxAfter );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_pxBefore.Reset();
		_pxAfter.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_pxBefore.IsDerivedFromParent()
			&& _pxAfter.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "pxBefore" )
			_pxBefore.Reset();
		else if ( fieldName == "pxAfter" )
			_pxAfter.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "pxBefore" )
			return _pxBefore.IsDerivedFromParent();
		if ( fieldName == "pxAfter" )
			return _pxAfter.IsDerivedFromParent();
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

public class LevelDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private LevelDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _expToOpen;
	private UndoRedo<float> _levelFinishBonus;
	private UndoRedo<float> _creepTraindedBonus;
	private UndoRedo<int> _levelFinishMoney;
	private UndoRedo<int> _creepMedalMoney;
	private UndoRedo<float> _duration;
	private TextRef _name;
	private TextRef _description;
	private UndoRedo<int> _numberOfMelee;
	private UndoRedo<int> _numberOfRange;
	private UndoRedo<int> _numberOfSiege;
	private UndoRedo<bool> _casualWishGeneration;

	public int expToOpen { get { return _expToOpen.Get(); } set { _expToOpen.Set( value ); } }

	public float levelFinishBonus { get { return _levelFinishBonus.Get(); } set { _levelFinishBonus.Set( value ); } }

	public float creepTraindedBonus { get { return _creepTraindedBonus.Get(); } set { _creepTraindedBonus.Set( value ); } }

	public int levelFinishMoney { get { return _levelFinishMoney.Get(); } set { _levelFinishMoney.Set( value ); } }

	public int creepMedalMoney { get { return _creepMedalMoney.Get(); } set { _creepMedalMoney.Set( value ); } }

	public float duration { get { return _duration.Get(); } set { _duration.Set( value ); } }

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	public int numberOfMelee { get { return _numberOfMelee.Get(); } set { _numberOfMelee.Set( value ); } }

	public int numberOfRange { get { return _numberOfRange.Get(); } set { _numberOfRange.Set( value ); } }

	public int numberOfSiege { get { return _numberOfSiege.Get(); } set { _numberOfSiege.Set( value ); } }

	public bool casualWishGeneration { get { return _casualWishGeneration.Get(); } set { _casualWishGeneration.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_expToOpen = new UndoRedo<int>( owner, 0 );
		_levelFinishBonus = new UndoRedo<float>( owner, 100.0f );
		_creepTraindedBonus = new UndoRedo<float>( owner, 100.0f );
		_levelFinishMoney = new UndoRedo<int>( owner, 100 );
		_creepMedalMoney = new UndoRedo<int>( owner, 5 );
		_duration = new UndoRedo<float>( owner, 3.0f );
		_name = new TextRef( owner, new TextRef() );
		_description = new TextRef( owner, new TextRef() );
		_numberOfMelee = new UndoRedo<int>( owner, 1 );
		_numberOfRange = new UndoRedo<int>( owner, 1 );
		_numberOfSiege = new UndoRedo<int>( owner, 1 );
		_casualWishGeneration = new UndoRedo<bool>( owner, false );
		_expToOpen.Changed += FireChangedEvent;
		_levelFinishBonus.Changed += FireChangedEvent;
		_creepTraindedBonus.Changed += FireChangedEvent;
		_levelFinishMoney.Changed += FireChangedEvent;
		_creepMedalMoney.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_numberOfMelee.Changed += FireChangedEvent;
		_numberOfRange.Changed += FireChangedEvent;
		_numberOfSiege.Changed += FireChangedEvent;
		_casualWishGeneration.Changed += FireChangedEvent;
	}

	public LevelDesc()
	{
		Initialize( GetOwner() );
	}

	public LevelDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public LevelDesc( DBResource owner, LevelDesc source )
		: this(owner, source, true){}

	protected LevelDesc( DBResource owner, LevelDesc source, bool fireEvent )
	{
		_expToOpen = new UndoRedo<int>( owner, source.expToOpen );
		_levelFinishBonus = new UndoRedo<float>( owner, source.levelFinishBonus );
		_creepTraindedBonus = new UndoRedo<float>( owner, source.creepTraindedBonus );
		_levelFinishMoney = new UndoRedo<int>( owner, source.levelFinishMoney );
		_creepMedalMoney = new UndoRedo<int>( owner, source.creepMedalMoney );
		_duration = new UndoRedo<float>( owner, source.duration );
		_name = new TextRef( owner, source.name );
		_description = new TextRef( owner, source.description );
		_numberOfMelee = new UndoRedo<int>( owner, source.numberOfMelee );
		_numberOfRange = new UndoRedo<int>( owner, source.numberOfRange );
		_numberOfSiege = new UndoRedo<int>( owner, source.numberOfSiege );
		_casualWishGeneration = new UndoRedo<bool>( owner, source.casualWishGeneration );
		_expToOpen.Changed += FireChangedEvent;
		_levelFinishBonus.Changed += FireChangedEvent;
		_creepTraindedBonus.Changed += FireChangedEvent;
		_levelFinishMoney.Changed += FireChangedEvent;
		_creepMedalMoney.Changed += FireChangedEvent;
		_duration.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_numberOfMelee.Changed += FireChangedEvent;
		_numberOfRange.Changed += FireChangedEvent;
		_numberOfSiege.Changed += FireChangedEvent;
		_casualWishGeneration.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		LevelDesc source = _source as LevelDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LevelDesc" );
		expToOpen = source.expToOpen;
		levelFinishBonus = source.levelFinishBonus;
		creepTraindedBonus = source.creepTraindedBonus;
		levelFinishMoney = source.levelFinishMoney;
		creepMedalMoney = source.creepMedalMoney;
		duration = source.duration;
		name = source.name;
		description = source.description;
		numberOfMelee = source.numberOfMelee;
		numberOfRange = source.numberOfRange;
		numberOfSiege = source.numberOfSiege;
		casualWishGeneration = source.casualWishGeneration;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		LevelDesc newParent = _newParent as LevelDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_expToOpen.SetParent( newParent == null ? null : newParent._expToOpen );
		_levelFinishBonus.SetParent( newParent == null ? null : newParent._levelFinishBonus );
		_creepTraindedBonus.SetParent( newParent == null ? null : newParent._creepTraindedBonus );
		_levelFinishMoney.SetParent( newParent == null ? null : newParent._levelFinishMoney );
		_creepMedalMoney.SetParent( newParent == null ? null : newParent._creepMedalMoney );
		_duration.SetParent( newParent == null ? null : newParent._duration );
		_name.SetParent( newParent == null ? null : newParent._name );
		_description.SetParent( newParent == null ? null : newParent._description );
		_numberOfMelee.SetParent( newParent == null ? null : newParent._numberOfMelee );
		_numberOfRange.SetParent( newParent == null ? null : newParent._numberOfRange );
		_numberOfSiege.SetParent( newParent == null ? null : newParent._numberOfSiege );
		_casualWishGeneration.SetParent( newParent == null ? null : newParent._casualWishGeneration );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_expToOpen.Reset();
		_levelFinishBonus.Reset();
		_creepTraindedBonus.Reset();
		_levelFinishMoney.Reset();
		_creepMedalMoney.Reset();
		_duration.Reset();
		_name.Reset();
		_description.Reset();
		_numberOfMelee.Reset();
		_numberOfRange.Reset();
		_numberOfSiege.Reset();
		_casualWishGeneration.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_expToOpen.IsDerivedFromParent()
			&& _levelFinishBonus.IsDerivedFromParent()
			&& _creepTraindedBonus.IsDerivedFromParent()
			&& _levelFinishMoney.IsDerivedFromParent()
			&& _creepMedalMoney.IsDerivedFromParent()
			&& _duration.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _numberOfMelee.IsDerivedFromParent()
			&& _numberOfRange.IsDerivedFromParent()
			&& _numberOfSiege.IsDerivedFromParent()
			&& _casualWishGeneration.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "expToOpen" )
			_expToOpen.Reset();
		else if ( fieldName == "levelFinishBonus" )
			_levelFinishBonus.Reset();
		else if ( fieldName == "creepTraindedBonus" )
			_creepTraindedBonus.Reset();
		else if ( fieldName == "levelFinishMoney" )
			_levelFinishMoney.Reset();
		else if ( fieldName == "creepMedalMoney" )
			_creepMedalMoney.Reset();
		else if ( fieldName == "duration" )
			_duration.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "numberOfMelee" )
			_numberOfMelee.Reset();
		else if ( fieldName == "numberOfRange" )
			_numberOfRange.Reset();
		else if ( fieldName == "numberOfSiege" )
			_numberOfSiege.Reset();
		else if ( fieldName == "casualWishGeneration" )
			_casualWishGeneration.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "expToOpen" )
			return _expToOpen.IsDerivedFromParent();
		if ( fieldName == "levelFinishBonus" )
			return _levelFinishBonus.IsDerivedFromParent();
		if ( fieldName == "creepTraindedBonus" )
			return _creepTraindedBonus.IsDerivedFromParent();
		if ( fieldName == "levelFinishMoney" )
			return _levelFinishMoney.IsDerivedFromParent();
		if ( fieldName == "creepMedalMoney" )
			return _creepMedalMoney.IsDerivedFromParent();
		if ( fieldName == "duration" )
			return _duration.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "numberOfMelee" )
			return _numberOfMelee.IsDerivedFromParent();
		if ( fieldName == "numberOfRange" )
			return _numberOfRange.IsDerivedFromParent();
		if ( fieldName == "numberOfSiege" )
			return _numberOfSiege.IsDerivedFromParent();
		if ( fieldName == "casualWishGeneration" )
			return _casualWishGeneration.IsDerivedFromParent();
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
public class MinigameUIStylesDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private MinigameUIStylesDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<BaseUIMaterial>> _creepWishMaterials;
	private UndoRedoAssignableList<DBPtr<BaseUIMaterial>> _creepStateMaterials;
	private UndoRedoAssignableList<DBPtr<BaseUIMaterial>> _creepFriendshipMaterials;
	private UndoRedo<float> _creepsAppearPause;
	private UndoRedo<float> _creepAppearTime;
	private UndoRedo<float> _creepMedalAppearTime;
	private UndoRedo<float> _medalAppearPause;
	private UndoRedo<float> _medalAppearTime;
	private UndoRedo<float> _naftaAnimationSpeed;

	[EnumArray(typeof(ECreepWish))]
	public libdb.IChangeableList<DBPtr<BaseUIMaterial>> creepWishMaterials { get { return _creepWishMaterials; } set { _creepWishMaterials.Assign( value ); } }

	[EnumArray(typeof(ECreepState))]
	public libdb.IChangeableList<DBPtr<BaseUIMaterial>> creepStateMaterials { get { return _creepStateMaterials; } set { _creepStateMaterials.Assign( value ); } }

	[MinMaxSize(5, 5)]
	public libdb.IChangeableList<DBPtr<BaseUIMaterial>> creepFriendshipMaterials { get { return _creepFriendshipMaterials; } set { _creepFriendshipMaterials.Assign( value ); } }

	[Category( "ResultsScreen" )]
	public float creepsAppearPause { get { return _creepsAppearPause.Get(); } set { _creepsAppearPause.Set( value ); } }

	public float creepAppearTime { get { return _creepAppearTime.Get(); } set { _creepAppearTime.Set( value ); } }

	public float creepMedalAppearTime { get { return _creepMedalAppearTime.Get(); } set { _creepMedalAppearTime.Set( value ); } }

	public float medalAppearPause { get { return _medalAppearPause.Get(); } set { _medalAppearPause.Set( value ); } }

	public float medalAppearTime { get { return _medalAppearTime.Get(); } set { _medalAppearTime.Set( value ); } }

	public float naftaAnimationSpeed { get { return _naftaAnimationSpeed.Get(); } set { _naftaAnimationSpeed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_creepWishMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, typeof( ECreepWish ) );
		_creepStateMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, typeof( ECreepState ) );
		_creepFriendshipMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, 5, 5 );
		_creepsAppearPause = new UndoRedo<float>( owner, 0.0f );
		_creepAppearTime = new UndoRedo<float>( owner, 0.0f );
		_creepMedalAppearTime = new UndoRedo<float>( owner, 0.0f );
		_medalAppearPause = new UndoRedo<float>( owner, 0.0f );
		_medalAppearTime = new UndoRedo<float>( owner, 0.0f );
		_naftaAnimationSpeed = new UndoRedo<float>( owner, 0.0f );
		_creepWishMaterials.Changed += FireChangedEvent;
		_creepStateMaterials.Changed += FireChangedEvent;
		_creepFriendshipMaterials.Changed += FireChangedEvent;
		_creepsAppearPause.Changed += FireChangedEvent;
		_creepAppearTime.Changed += FireChangedEvent;
		_creepMedalAppearTime.Changed += FireChangedEvent;
		_medalAppearPause.Changed += FireChangedEvent;
		_medalAppearTime.Changed += FireChangedEvent;
		_naftaAnimationSpeed.Changed += FireChangedEvent;
	}

	public MinigameUIStylesDesc()
	{
		Initialize( GetOwner() );
	}

	public MinigameUIStylesDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public MinigameUIStylesDesc( DBResource owner, MinigameUIStylesDesc source )
		: this(owner, source, true){}

	protected MinigameUIStylesDesc( DBResource owner, MinigameUIStylesDesc source, bool fireEvent )
	{
		_creepWishMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, typeof( ECreepWish ) );
		_creepWishMaterials.Assign( source.creepWishMaterials );
		_creepStateMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, typeof( ECreepState ) );
		_creepStateMaterials.Assign( source.creepStateMaterials );
		_creepFriendshipMaterials = new UndoRedoAssignableList<DBPtr<BaseUIMaterial>>( owner, 5, 5 );
		_creepFriendshipMaterials.Assign( source.creepFriendshipMaterials );
		_creepsAppearPause = new UndoRedo<float>( owner, source.creepsAppearPause );
		_creepAppearTime = new UndoRedo<float>( owner, source.creepAppearTime );
		_creepMedalAppearTime = new UndoRedo<float>( owner, source.creepMedalAppearTime );
		_medalAppearPause = new UndoRedo<float>( owner, source.medalAppearPause );
		_medalAppearTime = new UndoRedo<float>( owner, source.medalAppearTime );
		_naftaAnimationSpeed = new UndoRedo<float>( owner, source.naftaAnimationSpeed );
		_creepWishMaterials.Changed += FireChangedEvent;
		_creepStateMaterials.Changed += FireChangedEvent;
		_creepFriendshipMaterials.Changed += FireChangedEvent;
		_creepsAppearPause.Changed += FireChangedEvent;
		_creepAppearTime.Changed += FireChangedEvent;
		_creepMedalAppearTime.Changed += FireChangedEvent;
		_medalAppearPause.Changed += FireChangedEvent;
		_medalAppearTime.Changed += FireChangedEvent;
		_naftaAnimationSpeed.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		MinigameUIStylesDesc source = _source as MinigameUIStylesDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MinigameUIStylesDesc" );
		creepWishMaterials = source.creepWishMaterials;
		creepStateMaterials = source.creepStateMaterials;
		creepFriendshipMaterials = source.creepFriendshipMaterials;
		creepsAppearPause = source.creepsAppearPause;
		creepAppearTime = source.creepAppearTime;
		creepMedalAppearTime = source.creepMedalAppearTime;
		medalAppearPause = source.medalAppearPause;
		medalAppearTime = source.medalAppearTime;
		naftaAnimationSpeed = source.naftaAnimationSpeed;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		MinigameUIStylesDesc newParent = _newParent as MinigameUIStylesDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_creepWishMaterials.SetParent( newParent == null ? null : newParent._creepWishMaterials );
		_creepStateMaterials.SetParent( newParent == null ? null : newParent._creepStateMaterials );
		_creepFriendshipMaterials.SetParent( newParent == null ? null : newParent._creepFriendshipMaterials );
		_creepsAppearPause.SetParent( newParent == null ? null : newParent._creepsAppearPause );
		_creepAppearTime.SetParent( newParent == null ? null : newParent._creepAppearTime );
		_creepMedalAppearTime.SetParent( newParent == null ? null : newParent._creepMedalAppearTime );
		_medalAppearPause.SetParent( newParent == null ? null : newParent._medalAppearPause );
		_medalAppearTime.SetParent( newParent == null ? null : newParent._medalAppearTime );
		_naftaAnimationSpeed.SetParent( newParent == null ? null : newParent._naftaAnimationSpeed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_creepWishMaterials.Reset();
		_creepStateMaterials.Reset();
		_creepFriendshipMaterials.Reset();
		_creepsAppearPause.Reset();
		_creepAppearTime.Reset();
		_creepMedalAppearTime.Reset();
		_medalAppearPause.Reset();
		_medalAppearTime.Reset();
		_naftaAnimationSpeed.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_creepWishMaterials.IsDerivedFromParent()
			&& _creepStateMaterials.IsDerivedFromParent()
			&& _creepFriendshipMaterials.IsDerivedFromParent()
			&& _creepsAppearPause.IsDerivedFromParent()
			&& _creepAppearTime.IsDerivedFromParent()
			&& _creepMedalAppearTime.IsDerivedFromParent()
			&& _medalAppearPause.IsDerivedFromParent()
			&& _medalAppearTime.IsDerivedFromParent()
			&& _naftaAnimationSpeed.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "creepWishMaterials" )
			_creepWishMaterials.Reset();
		else if ( fieldName == "creepStateMaterials" )
			_creepStateMaterials.Reset();
		else if ( fieldName == "creepFriendshipMaterials" )
			_creepFriendshipMaterials.Reset();
		else if ( fieldName == "creepsAppearPause" )
			_creepsAppearPause.Reset();
		else if ( fieldName == "creepAppearTime" )
			_creepAppearTime.Reset();
		else if ( fieldName == "creepMedalAppearTime" )
			_creepMedalAppearTime.Reset();
		else if ( fieldName == "medalAppearPause" )
			_medalAppearPause.Reset();
		else if ( fieldName == "medalAppearTime" )
			_medalAppearTime.Reset();
		else if ( fieldName == "naftaAnimationSpeed" )
			_naftaAnimationSpeed.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "creepWishMaterials" )
			return _creepWishMaterials.IsDerivedFromParent();
		if ( fieldName == "creepStateMaterials" )
			return _creepStateMaterials.IsDerivedFromParent();
		if ( fieldName == "creepFriendshipMaterials" )
			return _creepFriendshipMaterials.IsDerivedFromParent();
		if ( fieldName == "creepsAppearPause" )
			return _creepsAppearPause.IsDerivedFromParent();
		if ( fieldName == "creepAppearTime" )
			return _creepAppearTime.IsDerivedFromParent();
		if ( fieldName == "creepMedalAppearTime" )
			return _creepMedalAppearTime.IsDerivedFromParent();
		if ( fieldName == "medalAppearPause" )
			return _medalAppearPause.IsDerivedFromParent();
		if ( fieldName == "medalAppearTime" )
			return _medalAppearTime.IsDerivedFromParent();
		if ( fieldName == "naftaAnimationSpeed" )
			return _naftaAnimationSpeed.IsDerivedFromParent();
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

public class NeighbourhoodDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private NeighbourhoodDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _first;
	private UndoRedo<int> _second;

	public int first { get { return _first.Get(); } set { _first.Set( value ); } }

	public int second { get { return _second.Get(); } set { _second.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_first = new UndoRedo<int>( owner, 0 );
		_second = new UndoRedo<int>( owner, 0 );
		_first.Changed += FireChangedEvent;
		_second.Changed += FireChangedEvent;
	}

	public NeighbourhoodDesc()
	{
		Initialize( GetOwner() );
	}

	public NeighbourhoodDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public NeighbourhoodDesc( DBResource owner, NeighbourhoodDesc source )
		: this(owner, source, true){}

	protected NeighbourhoodDesc( DBResource owner, NeighbourhoodDesc source, bool fireEvent )
	{
		_first = new UndoRedo<int>( owner, source.first );
		_second = new UndoRedo<int>( owner, source.second );
		_first.Changed += FireChangedEvent;
		_second.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		NeighbourhoodDesc source = _source as NeighbourhoodDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for NeighbourhoodDesc" );
		first = source.first;
		second = source.second;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		NeighbourhoodDesc newParent = _newParent as NeighbourhoodDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_first.SetParent( newParent == null ? null : newParent._first );
		_second.SetParent( newParent == null ? null : newParent._second );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_first.Reset();
		_second.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_first.IsDerivedFromParent()
			&& _second.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "first" )
			_first.Reset();
		else if ( fieldName == "second" )
			_second.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "first" )
			return _first.IsDerivedFromParent();
		if ( fieldName == "second" )
			return _second.IsDerivedFromParent();
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

public class PlaceDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PlaceDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EPlaceType> _placeType;
	private Vec3 _position;
	private UndoRedoDBPtr<DBSceneObject> _sceneObject;
	private UndoRedoDBPtr<DBSceneObject> _sceneObjectDirty50;
	private UndoRedoDBPtr<UIObjectOvertips> _overtip;
	private UndoRedo<int> _accessibility;
	private UndoRedo<int> _cost;
	private TextRef _name;
	private TextRef _description;
	private UndoRedoDBPtr<BaseUIMaterial> _iconMaterial;

	public EPlaceType placeType { get { return _placeType.Get(); } set { _placeType.Set( value ); } }

	public Vec3 position { get { return _position; } set { _position.Assign( value ); } }

	[Description( "Scene object for clear place (50% < soil)" )]
	public DBPtr<DBSceneObject> sceneObject { get { return _sceneObject.Get(); } set { _sceneObject.Set( value ); } }

	[Description( "Scene object for dirty place (50% < soil < 100%)" )]
	public DBPtr<DBSceneObject> sceneObjectDirty50 { get { return _sceneObjectDirty50.Get(); } set { _sceneObjectDirty50.Set( value ); } }

	public DBPtr<UIObjectOvertips> overtip { get { return _overtip.Get(); } set { _overtip.Set( value ); } }

	public int accessibility { get { return _accessibility.Get(); } set { _accessibility.Set( value ); } }

	public int cost { get { return _cost.Get(); } set { _cost.Set( value ); } }

	public TextRef name { get { return _name; } set { _name.Assign( value ); } }

	public TextRef description { get { return _description; } set { _description.Assign( value ); } }

	public DBPtr<BaseUIMaterial> iconMaterial { get { return _iconMaterial.Get(); } set { _iconMaterial.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_placeType = new UndoRedo<EPlaceType>( owner, EPlaceType.Bad );
		_position = new Vec3( owner );
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner );
		_sceneObjectDirty50 = new UndoRedoDBPtr<DBSceneObject>( owner );
		_overtip = new UndoRedoDBPtr<UIObjectOvertips>( owner );
		_accessibility = new UndoRedo<int>( owner, -1 );
		_cost = new UndoRedo<int>( owner, 250 );
		_name = new TextRef( owner, new TextRef() );
		_description = new TextRef( owner, new TextRef() );
		_iconMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner );
		_placeType.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
		_sceneObjectDirty50.Changed += FireChangedEvent;
		_overtip.Changed += FireChangedEvent;
		_accessibility.Changed += FireChangedEvent;
		_cost.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_iconMaterial.Changed += FireChangedEvent;
	}

	public PlaceDesc()
	{
		Initialize( GetOwner() );
	}

	public PlaceDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PlaceDesc( DBResource owner, PlaceDesc source )
		: this(owner, source, true){}

	protected PlaceDesc( DBResource owner, PlaceDesc source, bool fireEvent )
	{
		_placeType = new UndoRedo<EPlaceType>( owner, source.placeType );
		_position = new Vec3( owner, source.position );
		_sceneObject = new UndoRedoDBPtr<DBSceneObject>( owner, source.sceneObject );
		_sceneObjectDirty50 = new UndoRedoDBPtr<DBSceneObject>( owner, source.sceneObjectDirty50 );
		_overtip = new UndoRedoDBPtr<UIObjectOvertips>( owner, source.overtip );
		_accessibility = new UndoRedo<int>( owner, source.accessibility );
		_cost = new UndoRedo<int>( owner, source.cost );
		_name = new TextRef( owner, source.name );
		_description = new TextRef( owner, source.description );
		_iconMaterial = new UndoRedoDBPtr<BaseUIMaterial>( owner, source.iconMaterial );
		_placeType.Changed += FireChangedEvent;
		_position.Changed += FireChangedEvent;
		_sceneObject.Changed += FireChangedEvent;
		_sceneObjectDirty50.Changed += FireChangedEvent;
		_overtip.Changed += FireChangedEvent;
		_accessibility.Changed += FireChangedEvent;
		_cost.Changed += FireChangedEvent;
		_name.Changed += FireChangedEvent;
		_description.Changed += FireChangedEvent;
		_iconMaterial.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PlaceDesc source = _source as PlaceDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PlaceDesc" );
		placeType = source.placeType;
		position = source.position;
		sceneObject = source.sceneObject;
		sceneObjectDirty50 = source.sceneObjectDirty50;
		overtip = source.overtip;
		accessibility = source.accessibility;
		cost = source.cost;
		name = source.name;
		description = source.description;
		iconMaterial = source.iconMaterial;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PlaceDesc newParent = _newParent as PlaceDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_placeType.SetParent( newParent == null ? null : newParent._placeType );
		_position.SetParent( newParent == null ? null : newParent._position );
		_sceneObject.SetParent( newParent == null ? null : newParent._sceneObject );
		_sceneObjectDirty50.SetParent( newParent == null ? null : newParent._sceneObjectDirty50 );
		_overtip.SetParent( newParent == null ? null : newParent._overtip );
		_accessibility.SetParent( newParent == null ? null : newParent._accessibility );
		_cost.SetParent( newParent == null ? null : newParent._cost );
		_name.SetParent( newParent == null ? null : newParent._name );
		_description.SetParent( newParent == null ? null : newParent._description );
		_iconMaterial.SetParent( newParent == null ? null : newParent._iconMaterial );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_placeType.Reset();
		_position.Reset();
		_sceneObject.Reset();
		_sceneObjectDirty50.Reset();
		_overtip.Reset();
		_accessibility.Reset();
		_cost.Reset();
		_name.Reset();
		_description.Reset();
		_iconMaterial.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_placeType.IsDerivedFromParent()
			&& _position.IsDerivedFromParent()
			&& _sceneObject.IsDerivedFromParent()
			&& _sceneObjectDirty50.IsDerivedFromParent()
			&& _overtip.IsDerivedFromParent()
			&& _accessibility.IsDerivedFromParent()
			&& _cost.IsDerivedFromParent()
			&& _name.IsDerivedFromParent()
			&& _description.IsDerivedFromParent()
			&& _iconMaterial.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "placeType" )
			_placeType.Reset();
		else if ( fieldName == "position" )
			_position.Reset();
		else if ( fieldName == "sceneObject" )
			_sceneObject.Reset();
		else if ( fieldName == "sceneObjectDirty50" )
			_sceneObjectDirty50.Reset();
		else if ( fieldName == "overtip" )
			_overtip.Reset();
		else if ( fieldName == "accessibility" )
			_accessibility.Reset();
		else if ( fieldName == "cost" )
			_cost.Reset();
		else if ( fieldName == "name" )
			_name.Reset();
		else if ( fieldName == "description" )
			_description.Reset();
		else if ( fieldName == "iconMaterial" )
			_iconMaterial.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "placeType" )
			return _placeType.IsDerivedFromParent();
		if ( fieldName == "position" )
			return _position.IsDerivedFromParent();
		if ( fieldName == "sceneObject" )
			return _sceneObject.IsDerivedFromParent();
		if ( fieldName == "sceneObjectDirty50" )
			return _sceneObjectDirty50.IsDerivedFromParent();
		if ( fieldName == "overtip" )
			return _overtip.IsDerivedFromParent();
		if ( fieldName == "accessibility" )
			return _accessibility.IsDerivedFromParent();
		if ( fieldName == "cost" )
			return _cost.IsDerivedFromParent();
		if ( fieldName == "name" )
			return _name.IsDerivedFromParent();
		if ( fieldName == "description" )
			return _description.IsDerivedFromParent();
		if ( fieldName == "iconMaterial" )
			return _iconMaterial.IsDerivedFromParent();
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

public class PlayerDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private PlayerDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec3 _startPosition;
	private UndoRedo<float> _velocity;
	private UndoRedo<float> _scaleFactor;
	private UndoRedoDBPtr<AnimGraphCreator> _animationGraph;

	public Vec3 startPosition { get { return _startPosition; } set { _startPosition.Assign( value ); } }

	public float velocity { get { return _velocity.Get(); } set { _velocity.Set( value ); } }

	public float scaleFactor { get { return _scaleFactor.Get(); } set { _scaleFactor.Set( value ); } }

	public DBPtr<AnimGraphCreator> animationGraph { get { return _animationGraph.Get(); } set { _animationGraph.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_startPosition = new Vec3( owner );
		_velocity = new UndoRedo<float>( owner, 2.0f );
		_scaleFactor = new UndoRedo<float>( owner, 1.0f );
		_animationGraph = new UndoRedoDBPtr<AnimGraphCreator>( owner );
		_startPosition.Changed += FireChangedEvent;
		_velocity.Changed += FireChangedEvent;
		_scaleFactor.Changed += FireChangedEvent;
		_animationGraph.Changed += FireChangedEvent;
	}

	public PlayerDesc()
	{
		Initialize( GetOwner() );
	}

	public PlayerDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public PlayerDesc( DBResource owner, PlayerDesc source )
		: this(owner, source, true){}

	protected PlayerDesc( DBResource owner, PlayerDesc source, bool fireEvent )
	{
		_startPosition = new Vec3( owner, source.startPosition );
		_velocity = new UndoRedo<float>( owner, source.velocity );
		_scaleFactor = new UndoRedo<float>( owner, source.scaleFactor );
		_animationGraph = new UndoRedoDBPtr<AnimGraphCreator>( owner, source.animationGraph );
		_startPosition.Changed += FireChangedEvent;
		_velocity.Changed += FireChangedEvent;
		_scaleFactor.Changed += FireChangedEvent;
		_animationGraph.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		PlayerDesc source = _source as PlayerDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PlayerDesc" );
		startPosition = source.startPosition;
		velocity = source.velocity;
		scaleFactor = source.scaleFactor;
		animationGraph = source.animationGraph;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		PlayerDesc newParent = _newParent as PlayerDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_startPosition.SetParent( newParent == null ? null : newParent._startPosition );
		_velocity.SetParent( newParent == null ? null : newParent._velocity );
		_scaleFactor.SetParent( newParent == null ? null : newParent._scaleFactor );
		_animationGraph.SetParent( newParent == null ? null : newParent._animationGraph );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_startPosition.Reset();
		_velocity.Reset();
		_scaleFactor.Reset();
		_animationGraph.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_startPosition.IsDerivedFromParent()
			&& _velocity.IsDerivedFromParent()
			&& _scaleFactor.IsDerivedFromParent()
			&& _animationGraph.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "startPosition" )
			_startPosition.Reset();
		else if ( fieldName == "velocity" )
			_velocity.Reset();
		else if ( fieldName == "scaleFactor" )
			_scaleFactor.Reset();
		else if ( fieldName == "animationGraph" )
			_animationGraph.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "startPosition" )
			return _startPosition.IsDerivedFromParent();
		if ( fieldName == "velocity" )
			return _velocity.IsDerivedFromParent();
		if ( fieldName == "scaleFactor" )
			return _scaleFactor.IsDerivedFromParent();
		if ( fieldName == "animationGraph" )
			return _animationGraph.IsDerivedFromParent();
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

public class Preselection : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Preselection __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private HDRColor _colorNotBought;
	private HDRColor _colorNotBoughtUnavailable;
	private HDRColor _colorNotBoughtPreselect;
	private HDRColor _colorPreselect;

	[Description( "Color multiplier for item in shop" )]
	public HDRColor colorNotBought { get { return _colorNotBought; } set { _colorNotBought.Assign( value ); } }

	[Description( "Color multiplier for item in shop (unavailable)" )]
	public HDRColor colorNotBoughtUnavailable { get { return _colorNotBoughtUnavailable; } set { _colorNotBoughtUnavailable.Assign( value ); } }

	[Description( "Color multiplier for item in shop preselection" )]
	public HDRColor colorNotBoughtPreselect { get { return _colorNotBoughtPreselect; } set { _colorNotBoughtPreselect.Assign( value ); } }

	[Description( "Color multiplier for preselection in game" )]
	public HDRColor colorPreselect { get { return _colorPreselect; } set { _colorPreselect.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		HDRColor __colorNotBought = new HDRColor(); // Construct default object for colorNotBought
		__colorNotBought.R = 0.5f;
		__colorNotBought.G = 1.0f;
		__colorNotBought.B = 0.5f;
		_colorNotBought = new HDRColor( owner, __colorNotBought );
		HDRColor __colorNotBoughtUnavailable = new HDRColor(); // Construct default object for colorNotBoughtUnavailable
		__colorNotBoughtUnavailable.R = 0.5f;
		__colorNotBoughtUnavailable.G = 0.5f;
		__colorNotBoughtUnavailable.B = 0.5f;
		_colorNotBoughtUnavailable = new HDRColor( owner, __colorNotBoughtUnavailable );
		HDRColor __colorNotBoughtPreselect = new HDRColor(); // Construct default object for colorNotBoughtPreselect
		__colorNotBoughtPreselect.R = 0.5f;
		__colorNotBoughtPreselect.G = 2.0f;
		__colorNotBoughtPreselect.B = 0.5f;
		_colorNotBoughtPreselect = new HDRColor( owner, __colorNotBoughtPreselect );
		HDRColor __colorPreselect = new HDRColor(); // Construct default object for colorPreselect
		__colorPreselect.R = 1.2f;
		__colorPreselect.G = 1.2f;
		__colorPreselect.B = 1.2f;
		_colorPreselect = new HDRColor( owner, __colorPreselect );
		_colorNotBought.Changed += FireChangedEvent;
		_colorNotBoughtUnavailable.Changed += FireChangedEvent;
		_colorNotBoughtPreselect.Changed += FireChangedEvent;
		_colorPreselect.Changed += FireChangedEvent;
	}

	public Preselection()
	{
		Initialize( GetOwner() );
	}

	public Preselection( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Preselection( DBResource owner, Preselection source )
		: this(owner, source, true){}

	protected Preselection( DBResource owner, Preselection source, bool fireEvent )
	{
		_colorNotBought = new HDRColor( owner, source.colorNotBought );
		_colorNotBoughtUnavailable = new HDRColor( owner, source.colorNotBoughtUnavailable );
		_colorNotBoughtPreselect = new HDRColor( owner, source.colorNotBoughtPreselect );
		_colorPreselect = new HDRColor( owner, source.colorPreselect );
		_colorNotBought.Changed += FireChangedEvent;
		_colorNotBoughtUnavailable.Changed += FireChangedEvent;
		_colorNotBoughtPreselect.Changed += FireChangedEvent;
		_colorPreselect.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Preselection source = _source as Preselection;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Preselection" );
		colorNotBought = source.colorNotBought;
		colorNotBoughtUnavailable = source.colorNotBoughtUnavailable;
		colorNotBoughtPreselect = source.colorNotBoughtPreselect;
		colorPreselect = source.colorPreselect;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Preselection newParent = _newParent as Preselection;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_colorNotBought.SetParent( newParent == null ? null : newParent._colorNotBought );
		_colorNotBoughtUnavailable.SetParent( newParent == null ? null : newParent._colorNotBoughtUnavailable );
		_colorNotBoughtPreselect.SetParent( newParent == null ? null : newParent._colorNotBoughtPreselect );
		_colorPreselect.SetParent( newParent == null ? null : newParent._colorPreselect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_colorNotBought.Reset();
		_colorNotBoughtUnavailable.Reset();
		_colorNotBoughtPreselect.Reset();
		_colorPreselect.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_colorNotBought.IsDerivedFromParent()
			&& _colorNotBoughtUnavailable.IsDerivedFromParent()
			&& _colorNotBoughtPreselect.IsDerivedFromParent()
			&& _colorPreselect.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "colorNotBought" )
			_colorNotBought.Reset();
		else if ( fieldName == "colorNotBoughtUnavailable" )
			_colorNotBoughtUnavailable.Reset();
		else if ( fieldName == "colorNotBoughtPreselect" )
			_colorNotBoughtPreselect.Reset();
		else if ( fieldName == "colorPreselect" )
			_colorPreselect.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "colorNotBought" )
			return _colorNotBought.IsDerivedFromParent();
		if ( fieldName == "colorNotBoughtUnavailable" )
			return _colorNotBoughtUnavailable.IsDerivedFromParent();
		if ( fieldName == "colorNotBoughtPreselect" )
			return _colorNotBoughtPreselect.IsDerivedFromParent();
		if ( fieldName == "colorPreselect" )
			return _colorPreselect.IsDerivedFromParent();
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

public class TrainingBonuses : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TrainingBonuses __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoList<float> _statLifeBar50;
	private UndoRedoList<float> _statLifeBar59;
	private UndoRedoList<float> _statLifeBar69;
	private UndoRedoList<float> _statLifeBar79;
	private UndoRedoList<float> _statLifeBar89;
	private UndoRedoList<float> _statLifeBar100;

	[Category( "Creeps" )]
	[Description( "Stats modifications (bar > 50%)" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<float> statLifeBar50 { get { return _statLifeBar50; } set { _statLifeBar50.Assign( value ); } }

	[Category( "Creeps" )]
	[Description( "Stats modifications (bar > 59%)" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<float> statLifeBar59 { get { return _statLifeBar59; } set { _statLifeBar59.Assign( value ); } }

	[Category( "Creeps" )]
	[Description( "Stats modifications (bar > 69%)" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<float> statLifeBar69 { get { return _statLifeBar69; } set { _statLifeBar69.Assign( value ); } }

	[Category( "Creeps" )]
	[Description( "Stats modifications (bar > 79%)" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<float> statLifeBar79 { get { return _statLifeBar79; } set { _statLifeBar79.Assign( value ); } }

	[Category( "Creeps" )]
	[Description( "Stats modifications (bar > 89%)" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<float> statLifeBar89 { get { return _statLifeBar89; } set { _statLifeBar89.Assign( value ); } }

	[Category( "Creeps" )]
	[Description( "Stats modifications (bar == 100%)" )]
	[EnumArray(typeof(EStat))]
	public libdb.IChangeableList<float> statLifeBar100 { get { return _statLifeBar100; } set { _statLifeBar100.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_statLifeBar50 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar59 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar69 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar79 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar89 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar100 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar50.Changed += FireChangedEvent;
		_statLifeBar59.Changed += FireChangedEvent;
		_statLifeBar69.Changed += FireChangedEvent;
		_statLifeBar79.Changed += FireChangedEvent;
		_statLifeBar89.Changed += FireChangedEvent;
		_statLifeBar100.Changed += FireChangedEvent;
	}

	public TrainingBonuses()
	{
		Initialize( GetOwner() );
	}

	public TrainingBonuses( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TrainingBonuses( DBResource owner, TrainingBonuses source )
		: this(owner, source, true){}

	protected TrainingBonuses( DBResource owner, TrainingBonuses source, bool fireEvent )
	{
		_statLifeBar50 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar50.Assign( source.statLifeBar50 );
		_statLifeBar59 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar59.Assign( source.statLifeBar59 );
		_statLifeBar69 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar69.Assign( source.statLifeBar69 );
		_statLifeBar79 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar79.Assign( source.statLifeBar79 );
		_statLifeBar89 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar89.Assign( source.statLifeBar89 );
		_statLifeBar100 = new UndoRedoList<float>( owner, typeof( EStat ) );
		_statLifeBar100.Assign( source.statLifeBar100 );
		_statLifeBar50.Changed += FireChangedEvent;
		_statLifeBar59.Changed += FireChangedEvent;
		_statLifeBar69.Changed += FireChangedEvent;
		_statLifeBar79.Changed += FireChangedEvent;
		_statLifeBar89.Changed += FireChangedEvent;
		_statLifeBar100.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TrainingBonuses source = _source as TrainingBonuses;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TrainingBonuses" );
		statLifeBar50 = source.statLifeBar50;
		statLifeBar59 = source.statLifeBar59;
		statLifeBar69 = source.statLifeBar69;
		statLifeBar79 = source.statLifeBar79;
		statLifeBar89 = source.statLifeBar89;
		statLifeBar100 = source.statLifeBar100;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TrainingBonuses newParent = _newParent as TrainingBonuses;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_statLifeBar50.SetParent( newParent == null ? null : newParent._statLifeBar50 );
		_statLifeBar59.SetParent( newParent == null ? null : newParent._statLifeBar59 );
		_statLifeBar69.SetParent( newParent == null ? null : newParent._statLifeBar69 );
		_statLifeBar79.SetParent( newParent == null ? null : newParent._statLifeBar79 );
		_statLifeBar89.SetParent( newParent == null ? null : newParent._statLifeBar89 );
		_statLifeBar100.SetParent( newParent == null ? null : newParent._statLifeBar100 );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_statLifeBar50.Reset();
		_statLifeBar59.Reset();
		_statLifeBar69.Reset();
		_statLifeBar79.Reset();
		_statLifeBar89.Reset();
		_statLifeBar100.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_statLifeBar50.IsDerivedFromParent()
			&& _statLifeBar59.IsDerivedFromParent()
			&& _statLifeBar69.IsDerivedFromParent()
			&& _statLifeBar79.IsDerivedFromParent()
			&& _statLifeBar89.IsDerivedFromParent()
			&& _statLifeBar100.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "statLifeBar50" )
			_statLifeBar50.Reset();
		else if ( fieldName == "statLifeBar59" )
			_statLifeBar59.Reset();
		else if ( fieldName == "statLifeBar69" )
			_statLifeBar69.Reset();
		else if ( fieldName == "statLifeBar79" )
			_statLifeBar79.Reset();
		else if ( fieldName == "statLifeBar89" )
			_statLifeBar89.Reset();
		else if ( fieldName == "statLifeBar100" )
			_statLifeBar100.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "statLifeBar50" )
			return _statLifeBar50.IsDerivedFromParent();
		if ( fieldName == "statLifeBar59" )
			return _statLifeBar59.IsDerivedFromParent();
		if ( fieldName == "statLifeBar69" )
			return _statLifeBar69.IsDerivedFromParent();
		if ( fieldName == "statLifeBar79" )
			return _statLifeBar79.IsDerivedFromParent();
		if ( fieldName == "statLifeBar89" )
			return _statLifeBar89.IsDerivedFromParent();
		if ( fieldName == "statLifeBar100" )
			return _statLifeBar100.IsDerivedFromParent();
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

public class DBMinigame_Clinic : DBResource
{
	private UndoRedoDBPtr<DBMinigame_Clinic> ___parent;
	[HideInOutliner]
	public new DBPtr<DBMinigame_Clinic> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private TextRef _title;
	private ViewCamera _cameraOptions;
	private UndoRedoAssignableList<DBPtr<Sound2D>> _sounds;
	private UndoRedoAssignableList<DBPtr<Sound2D>> _bonusSounds;
	private Preselection _preselection;
	private PlayerDesc _player;
	private UndoRedoAssignableList<BonusDesc> _bonuses;
	private UndoRedoAssignableList<PlaceDesc> _places;
	private UndoRedoDBPtr<DBSceneObject> _sceneObjectDirty100;
	private UndoRedoAssignableList<NeighbourhoodDesc> _neighbourhood;
	private UndoRedoAssignableList<LevelDesc> _levels;
	private UndoRedoAssignableList<DecorationDesc> _decorations;
	private CreepsDesc _creepsDesc;
	private CreepBehaviourDesc _creepBehaviourDesc;
	private TrainingBonuses _trainingBonuses;
	private UndoRedo<float> _soilPersentMelee;
	private UndoRedo<float> _soilPersentRange;
	private UndoRedo<float> _soilPersentSiege;
	private UndoRedo<int> _clickBonusClickCount;
	private UndoRedo<float> _clickBonusValue;
	private UndoRedo<float> _heartsBonus;
	private UndoRedo<float> _minTimeBetweenCreeps;
	private UndoRedo<float> _maxTimeBetweenCreeps;
	private UndoRedo<float> _minThinkTime;
	private UndoRedo<float> _maxThinkTime;
	private UndoRedo<float> _waitTime;
	private UndoRedo<float> _fallAsleepTime;
	private UndoRedo<float> _wakeupTime;
	private UndoRedo<float> _workTime;
	private UndoRedo<float> _workBonus;
	private UndoRedo<float> _failBonus;
	private UndoRedo<float> _level1_BarValue;
	private UndoRedo<float> _level3_phase1Min;
	private UndoRedo<float> _level3_phase1Max;
	private UndoRedo<float> _level4_washProbTimes;
	private UndoRedo<float> _level5_fallAsleepTime;
	private UndoRedo<float> _level6_soilAtStart;
	private UndoRedo<float> _level8_timeReduction;
	private UndoRedo<float> _level8_bonusReduction;
	private UndoRedo<float> _level9_washProb;
	private UndoRedo<float> _level10_playProbTimes;
	private UndoRedo<float> _level11_soilIncrease;
	private UndoRedo<float> _level12_soilIncrease;
	private UndoRedo<float> _level12_bonusReduction;
	private UndoRedo<float> _level12_waitDecrease;
	private MinigameUIStylesDesc _uiStyles;

	public TextRef title { get { return _title; } set { _title.Assign( value ); } }

	public ViewCamera cameraOptions { get { return _cameraOptions; } set { _cameraOptions.Assign( value ); } }

	[Category( "Sound" )]
	[EnumArray(typeof(EClinicSounds))]
	public libdb.IChangeableList<DBPtr<Sound2D>> sounds { get { return _sounds; } set { _sounds.Assign( value ); } }

	[Category( "Sound" )]
	[EnumArray(typeof(EBonusType))]
	public libdb.IChangeableList<DBPtr<Sound2D>> bonusSounds { get { return _bonusSounds; } set { _bonusSounds.Assign( value ); } }

	[Category( "Preselection" )]
	public Preselection preselection { get { return _preselection; } set { _preselection.Assign( value ); } }

	[Category( "Player" )]
	public PlayerDesc player { get { return _player; } set { _player.Assign( value ); } }

	[EnumArray(typeof(EBonusType))]
	public libdb.IChangeableList<BonusDesc> bonuses { get { return _bonuses; } set { _bonuses.Assign( value ); } }

	[Category( "Game field" )]
	public libdb.IChangeableList<PlaceDesc> places { get { return _places; } set { _places.Assign( value ); } }

	[Category( "Game field" )]
	[Description( "Effect for dirty place (soil == 100%)" )]
	public DBPtr<DBSceneObject> sceneObjectDirty100 { get { return _sceneObjectDirty100.Get(); } set { _sceneObjectDirty100.Set( value ); } }

	[Category( "Game field" )]
	public libdb.IChangeableList<NeighbourhoodDesc> neighbourhood { get { return _neighbourhood; } set { _neighbourhood.Assign( value ); } }

	[Category( "Game field" )]
	public libdb.IChangeableList<LevelDesc> levels { get { return _levels; } set { _levels.Assign( value ); } }

	[Category( "Game field" )]
	public libdb.IChangeableList<DecorationDesc> decorations { get { return _decorations; } set { _decorations.Assign( value ); } }

	[Category( "Creeps" )]
	public CreepsDesc creepsDesc { get { return _creepsDesc; } set { _creepsDesc.Assign( value ); } }

	[Category( "Creeps" )]
	public CreepBehaviourDesc creepBehaviourDesc { get { return _creepBehaviourDesc; } set { _creepBehaviourDesc.Assign( value ); } }

	[Category( "Creeps" )]
	public TrainingBonuses trainingBonuses { get { return _trainingBonuses; } set { _trainingBonuses.Assign( value ); } }

	[Category( "Options" )]
	public float soilPersentMelee { get { return _soilPersentMelee.Get(); } set { _soilPersentMelee.Set( value ); } }

	[Category( "Options" )]
	public float soilPersentRange { get { return _soilPersentRange.Get(); } set { _soilPersentRange.Set( value ); } }

	[Category( "Options" )]
	public float soilPersentSiege { get { return _soilPersentSiege.Get(); } set { _soilPersentSiege.Set( value ); } }

	[Category( "Options" )]
	public int clickBonusClickCount { get { return _clickBonusClickCount.Get(); } set { _clickBonusClickCount.Set( value ); } }

	[Category( "Options" )]
	public float clickBonusValue { get { return _clickBonusValue.Get(); } set { _clickBonusValue.Set( value ); } }

	[Category( "Options" )]
	[Description( "Hearts bonus for the level completion" )]
	public float heartsBonus { get { return _heartsBonus.Get(); } set { _heartsBonus.Set( value ); } }

	[Category( "Options" )]
	[Description( "Min. time between creeps apears at entrance" )]
	public float minTimeBetweenCreeps { get { return _minTimeBetweenCreeps.Get(); } set { _minTimeBetweenCreeps.Set( value ); } }

	[Category( "Options" )]
	[Description( "Max. time between creeps apears at entrance" )]
	public float maxTimeBetweenCreeps { get { return _maxTimeBetweenCreeps.Get(); } set { _maxTimeBetweenCreeps.Set( value ); } }

	[Category( "Creep state options" )]
	[Description( "Min. time of think phase" )]
	public float minThinkTime { get { return _minThinkTime.Get(); } set { _minThinkTime.Set( value ); } }

	[Category( "Creep state options" )]
	[Description( "Max. time of the 'Think' phase" )]
	public float maxThinkTime { get { return _maxThinkTime.Get(); } set { _maxThinkTime.Set( value ); } }

	[Category( "Creep state options" )]
	[Description( "Duration of the 'Wait' phase" )]
	public float waitTime { get { return _waitTime.Get(); } set { _waitTime.Set( value ); } }

	[Category( "Creep state options" )]
	[Description( "Time until a creep fall asleep" )]
	public float fallAsleepTime { get { return _fallAsleepTime.Get(); } set { _fallAsleepTime.Set( value ); } }

	[Category( "Creep state options" )]
	[Description( "Time until a creep wakes up" )]
	public float wakeupTime { get { return _wakeupTime.Get(); } set { _wakeupTime.Set( value ); } }

	[Category( "Creep state options" )]
	[Description( "Time of the 'Work' phase" )]
	public float workTime { get { return _workTime.Get(); } set { _workTime.Set( value ); } }

	[Category( "Creep state options" )]
	[Description( "Default work bonus (will be added)" )]
	public float workBonus { get { return _workBonus.Get(); } set { _workBonus.Set( value ); } }

	[Category( "Creep state options" )]
	[Description( "Default fail bonus (will be subtracted)" )]
	public float failBonus { get { return _failBonus.Get(); } set { _failBonus.Set( value ); } }

	[Category( "Level 1 features" )]
	[Description( "Bar value at start" )]
	public float level1_BarValue { get { return _level1_BarValue.Get(); } set { _level1_BarValue.Set( value ); } }

	[Category( "Level 3 features" )]
	[Description( "Min. time of think phase" )]
	public float level3_phase1Min { get { return _level3_phase1Min.Get(); } set { _level3_phase1Min.Set( value ); } }

	[Category( "Level 3 features" )]
	[Description( "Max. time of think phase" )]
	public float level3_phase1Max { get { return _level3_phase1Max.Get(); } set { _level3_phase1Max.Set( value ); } }

	[Category( "Level 4 features" )]
	[Description( "Wish 'Wash' probability (times)" )]
	public float level4_washProbTimes { get { return _level4_washProbTimes.Get(); } set { _level4_washProbTimes.Set( value ); } }

	[Category( "Level 5 features" )]
	[Description( "Time until a creep fall asleep" )]
	public float level5_fallAsleepTime { get { return _level5_fallAsleepTime.Get(); } set { _level5_fallAsleepTime.Set( value ); } }

	[Category( "Level 6 features" )]
	[Description( "Soil percent at start" )]
	public float level6_soilAtStart { get { return _level6_soilAtStart.Get(); } set { _level6_soilAtStart.Set( value ); } }

	[Category( "Level 8 features" )]
	[Description( "'Work' time reduction (times)" )]
	public float level8_timeReduction { get { return _level8_timeReduction.Get(); } set { _level8_timeReduction.Set( value ); } }

	[Category( "Level 8 features" )]
	[Description( "Bonus in percent" )]
	public float level8_bonusReduction { get { return _level8_bonusReduction.Get(); } set { _level8_bonusReduction.Set( value ); } }

	[Category( "Level 9 features" )]
	[Description( "Wish 'Wash' probability" )]
	public float level9_washProb { get { return _level9_washProb.Get(); } set { _level9_washProb.Set( value ); } }

	[Category( "Level 10 features" )]
	[Description( "Wish 'Play' probability (times)" )]
	public float level10_playProbTimes { get { return _level10_playProbTimes.Get(); } set { _level10_playProbTimes.Set( value ); } }

	[Category( "Level 11 features" )]
	[Description( "Soil in percent" )]
	public float level11_soilIncrease { get { return _level11_soilIncrease.Get(); } set { _level11_soilIncrease.Set( value ); } }

	[Category( "Level 12 features" )]
	[Description( "Soil in percent" )]
	public float level12_soilIncrease { get { return _level12_soilIncrease.Get(); } set { _level12_soilIncrease.Set( value ); } }

	[Category( "Level 12 features" )]
	[Description( "Bonus in percent" )]
	public float level12_bonusReduction { get { return _level12_bonusReduction.Get(); } set { _level12_bonusReduction.Set( value ); } }

	[Category( "Level 12 features" )]
	[Description( "Wait time decrease (times)" )]
	public float level12_waitDecrease { get { return _level12_waitDecrease.Get(); } set { _level12_waitDecrease.Set( value ); } }

	[Category( "Minigame UI Styles" )]
	[Description( "Minigame UI Styles" )]
	public MinigameUIStylesDesc uiStyles { get { return _uiStyles; } set { _uiStyles.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<DBMinigame_Clinic>(owner);
		_title = new TextRef( owner, new TextRef() );
		_cameraOptions = new ViewCamera( owner );
		_sounds = new UndoRedoAssignableList<DBPtr<Sound2D>>( owner, typeof( EClinicSounds ) );
		_bonusSounds = new UndoRedoAssignableList<DBPtr<Sound2D>>( owner, typeof( EBonusType ) );
		_preselection = new Preselection( owner );
		_player = new PlayerDesc( owner );
		_bonuses = new UndoRedoAssignableList<BonusDesc>( owner, typeof( EBonusType ) );
		_places = new UndoRedoAssignableList<PlaceDesc>( owner );
		_sceneObjectDirty100 = new UndoRedoDBPtr<DBSceneObject>( owner );
		_neighbourhood = new UndoRedoAssignableList<NeighbourhoodDesc>( owner );
		_levels = new UndoRedoAssignableList<LevelDesc>( owner );
		_decorations = new UndoRedoAssignableList<DecorationDesc>( owner );
		_creepsDesc = new CreepsDesc( owner );
		_creepBehaviourDesc = new CreepBehaviourDesc( owner );
		_trainingBonuses = new TrainingBonuses( owner );
		_soilPersentMelee = new UndoRedo<float>( owner, 15.0f );
		_soilPersentRange = new UndoRedo<float>( owner, 15.0f );
		_soilPersentSiege = new UndoRedo<float>( owner, 35.0f );
		_clickBonusClickCount = new UndoRedo<int>( owner, 10 );
		_clickBonusValue = new UndoRedo<float>( owner, 0.02f );
		_heartsBonus = new UndoRedo<float>( owner, 0.5f );
		_minTimeBetweenCreeps = new UndoRedo<float>( owner, 2.0f );
		_maxTimeBetweenCreeps = new UndoRedo<float>( owner, 5.0f );
		_minThinkTime = new UndoRedo<float>( owner, 3.0f );
		_maxThinkTime = new UndoRedo<float>( owner, 5.0f );
		_waitTime = new UndoRedo<float>( owner, 30.0f );
		_fallAsleepTime = new UndoRedo<float>( owner, 3.0f );
		_wakeupTime = new UndoRedo<float>( owner, 3.0f );
		_workTime = new UndoRedo<float>( owner, 5.0f );
		_workBonus = new UndoRedo<float>( owner, 0.1f );
		_failBonus = new UndoRedo<float>( owner, 0.1f );
		_level1_BarValue = new UndoRedo<float>( owner, 40.0f );
		_level3_phase1Min = new UndoRedo<float>( owner, 8.0f );
		_level3_phase1Max = new UndoRedo<float>( owner, 12.0f );
		_level4_washProbTimes = new UndoRedo<float>( owner, 2.0f );
		_level5_fallAsleepTime = new UndoRedo<float>( owner, 2.0f );
		_level6_soilAtStart = new UndoRedo<float>( owner, 90.0f );
		_level8_timeReduction = new UndoRedo<float>( owner, 2.0f );
		_level8_bonusReduction = new UndoRedo<float>( owner, 50.0f );
		_level9_washProb = new UndoRedo<float>( owner, 80.0f );
		_level10_playProbTimes = new UndoRedo<float>( owner, 2.0f );
		_level11_soilIncrease = new UndoRedo<float>( owner, 200.0f );
		_level12_soilIncrease = new UndoRedo<float>( owner, 150.0f );
		_level12_bonusReduction = new UndoRedo<float>( owner, 70.0f );
		_level12_waitDecrease = new UndoRedo<float>( owner, 2.0f );
		_uiStyles = new MinigameUIStylesDesc( owner );
		___parent.Changed += FireChangedEvent;
		_title.Changed += FireChangedEvent;
		_cameraOptions.Changed += FireChangedEvent;
		_sounds.Changed += FireChangedEvent;
		_bonusSounds.Changed += FireChangedEvent;
		_preselection.Changed += FireChangedEvent;
		_player.Changed += FireChangedEvent;
		_bonuses.Changed += FireChangedEvent;
		_places.Changed += FireChangedEvent;
		_sceneObjectDirty100.Changed += FireChangedEvent;
		_neighbourhood.Changed += FireChangedEvent;
		_levels.Changed += FireChangedEvent;
		_decorations.Changed += FireChangedEvent;
		_creepsDesc.Changed += FireChangedEvent;
		_creepBehaviourDesc.Changed += FireChangedEvent;
		_trainingBonuses.Changed += FireChangedEvent;
		_soilPersentMelee.Changed += FireChangedEvent;
		_soilPersentRange.Changed += FireChangedEvent;
		_soilPersentSiege.Changed += FireChangedEvent;
		_clickBonusClickCount.Changed += FireChangedEvent;
		_clickBonusValue.Changed += FireChangedEvent;
		_heartsBonus.Changed += FireChangedEvent;
		_minTimeBetweenCreeps.Changed += FireChangedEvent;
		_maxTimeBetweenCreeps.Changed += FireChangedEvent;
		_minThinkTime.Changed += FireChangedEvent;
		_maxThinkTime.Changed += FireChangedEvent;
		_waitTime.Changed += FireChangedEvent;
		_fallAsleepTime.Changed += FireChangedEvent;
		_wakeupTime.Changed += FireChangedEvent;
		_workTime.Changed += FireChangedEvent;
		_workBonus.Changed += FireChangedEvent;
		_failBonus.Changed += FireChangedEvent;
		_level1_BarValue.Changed += FireChangedEvent;
		_level3_phase1Min.Changed += FireChangedEvent;
		_level3_phase1Max.Changed += FireChangedEvent;
		_level4_washProbTimes.Changed += FireChangedEvent;
		_level5_fallAsleepTime.Changed += FireChangedEvent;
		_level6_soilAtStart.Changed += FireChangedEvent;
		_level8_timeReduction.Changed += FireChangedEvent;
		_level8_bonusReduction.Changed += FireChangedEvent;
		_level9_washProb.Changed += FireChangedEvent;
		_level10_playProbTimes.Changed += FireChangedEvent;
		_level11_soilIncrease.Changed += FireChangedEvent;
		_level12_soilIncrease.Changed += FireChangedEvent;
		_level12_bonusReduction.Changed += FireChangedEvent;
		_level12_waitDecrease.Changed += FireChangedEvent;
		_uiStyles.Changed += FireChangedEvent;
	}

	public DBMinigame_Clinic()
	{
		Initialize( this );
	}
	private void AssignSelf( DBMinigame_Clinic source )
	{
		DataBase.UndoRedoManager.Start( "Assign for DBMinigame_Clinic" );
		title = source.title;
		cameraOptions = source.cameraOptions;
		sounds = source.sounds;
		bonusSounds = source.bonusSounds;
		preselection = source.preselection;
		player = source.player;
		bonuses = source.bonuses;
		places = source.places;
		sceneObjectDirty100 = source.sceneObjectDirty100;
		neighbourhood = source.neighbourhood;
		levels = source.levels;
		decorations = source.decorations;
		creepsDesc = source.creepsDesc;
		creepBehaviourDesc = source.creepBehaviourDesc;
		trainingBonuses = source.trainingBonuses;
		soilPersentMelee = source.soilPersentMelee;
		soilPersentRange = source.soilPersentRange;
		soilPersentSiege = source.soilPersentSiege;
		clickBonusClickCount = source.clickBonusClickCount;
		clickBonusValue = source.clickBonusValue;
		heartsBonus = source.heartsBonus;
		minTimeBetweenCreeps = source.minTimeBetweenCreeps;
		maxTimeBetweenCreeps = source.maxTimeBetweenCreeps;
		minThinkTime = source.minThinkTime;
		maxThinkTime = source.maxThinkTime;
		waitTime = source.waitTime;
		fallAsleepTime = source.fallAsleepTime;
		wakeupTime = source.wakeupTime;
		workTime = source.workTime;
		workBonus = source.workBonus;
		failBonus = source.failBonus;
		level1_BarValue = source.level1_BarValue;
		level3_phase1Min = source.level3_phase1Min;
		level3_phase1Max = source.level3_phase1Max;
		level4_washProbTimes = source.level4_washProbTimes;
		level5_fallAsleepTime = source.level5_fallAsleepTime;
		level6_soilAtStart = source.level6_soilAtStart;
		level8_timeReduction = source.level8_timeReduction;
		level8_bonusReduction = source.level8_bonusReduction;
		level9_washProb = source.level9_washProb;
		level10_playProbTimes = source.level10_playProbTimes;
		level11_soilIncrease = source.level11_soilIncrease;
		level12_soilIncrease = source.level12_soilIncrease;
		level12_bonusReduction = source.level12_bonusReduction;
		level12_waitDecrease = source.level12_waitDecrease;
		uiStyles = source.uiStyles;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		DBMinigame_Clinic source = _source as DBMinigame_Clinic;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DBMinigame_Clinic" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		DBMinigame_Clinic newParent = rawParent == null ? null : rawParent.Get<DBMinigame_Clinic>();
		if ( newParent == null && _newParent is DBMinigame_Clinic )
			newParent = _newParent as DBMinigame_Clinic;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_title.SetParent( newParent == null ? null : newParent._title );
		_cameraOptions.SetParent( newParent == null ? null : newParent._cameraOptions );
		_sounds.SetParent( newParent == null ? null : newParent._sounds );
		_bonusSounds.SetParent( newParent == null ? null : newParent._bonusSounds );
		_preselection.SetParent( newParent == null ? null : newParent._preselection );
		_player.SetParent( newParent == null ? null : newParent._player );
		_bonuses.SetParent( newParent == null ? null : newParent._bonuses );
		_places.SetParent( newParent == null ? null : newParent._places );
		_sceneObjectDirty100.SetParent( newParent == null ? null : newParent._sceneObjectDirty100 );
		_neighbourhood.SetParent( newParent == null ? null : newParent._neighbourhood );
		_levels.SetParent( newParent == null ? null : newParent._levels );
		_decorations.SetParent( newParent == null ? null : newParent._decorations );
		_creepsDesc.SetParent( newParent == null ? null : newParent._creepsDesc );
		_creepBehaviourDesc.SetParent( newParent == null ? null : newParent._creepBehaviourDesc );
		_trainingBonuses.SetParent( newParent == null ? null : newParent._trainingBonuses );
		_soilPersentMelee.SetParent( newParent == null ? null : newParent._soilPersentMelee );
		_soilPersentRange.SetParent( newParent == null ? null : newParent._soilPersentRange );
		_soilPersentSiege.SetParent( newParent == null ? null : newParent._soilPersentSiege );
		_clickBonusClickCount.SetParent( newParent == null ? null : newParent._clickBonusClickCount );
		_clickBonusValue.SetParent( newParent == null ? null : newParent._clickBonusValue );
		_heartsBonus.SetParent( newParent == null ? null : newParent._heartsBonus );
		_minTimeBetweenCreeps.SetParent( newParent == null ? null : newParent._minTimeBetweenCreeps );
		_maxTimeBetweenCreeps.SetParent( newParent == null ? null : newParent._maxTimeBetweenCreeps );
		_minThinkTime.SetParent( newParent == null ? null : newParent._minThinkTime );
		_maxThinkTime.SetParent( newParent == null ? null : newParent._maxThinkTime );
		_waitTime.SetParent( newParent == null ? null : newParent._waitTime );
		_fallAsleepTime.SetParent( newParent == null ? null : newParent._fallAsleepTime );
		_wakeupTime.SetParent( newParent == null ? null : newParent._wakeupTime );
		_workTime.SetParent( newParent == null ? null : newParent._workTime );
		_workBonus.SetParent( newParent == null ? null : newParent._workBonus );
		_failBonus.SetParent( newParent == null ? null : newParent._failBonus );
		_level1_BarValue.SetParent( newParent == null ? null : newParent._level1_BarValue );
		_level3_phase1Min.SetParent( newParent == null ? null : newParent._level3_phase1Min );
		_level3_phase1Max.SetParent( newParent == null ? null : newParent._level3_phase1Max );
		_level4_washProbTimes.SetParent( newParent == null ? null : newParent._level4_washProbTimes );
		_level5_fallAsleepTime.SetParent( newParent == null ? null : newParent._level5_fallAsleepTime );
		_level6_soilAtStart.SetParent( newParent == null ? null : newParent._level6_soilAtStart );
		_level8_timeReduction.SetParent( newParent == null ? null : newParent._level8_timeReduction );
		_level8_bonusReduction.SetParent( newParent == null ? null : newParent._level8_bonusReduction );
		_level9_washProb.SetParent( newParent == null ? null : newParent._level9_washProb );
		_level10_playProbTimes.SetParent( newParent == null ? null : newParent._level10_playProbTimes );
		_level11_soilIncrease.SetParent( newParent == null ? null : newParent._level11_soilIncrease );
		_level12_soilIncrease.SetParent( newParent == null ? null : newParent._level12_soilIncrease );
		_level12_bonusReduction.SetParent( newParent == null ? null : newParent._level12_bonusReduction );
		_level12_waitDecrease.SetParent( newParent == null ? null : newParent._level12_waitDecrease );
		_uiStyles.SetParent( newParent == null ? null : newParent._uiStyles );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_title.Reset();
		_cameraOptions.Reset();
		_sounds.Reset();
		_bonusSounds.Reset();
		_preselection.Reset();
		_player.Reset();
		_bonuses.Reset();
		_places.Reset();
		_sceneObjectDirty100.Reset();
		_neighbourhood.Reset();
		_levels.Reset();
		_decorations.Reset();
		_creepsDesc.Reset();
		_creepBehaviourDesc.Reset();
		_trainingBonuses.Reset();
		_soilPersentMelee.Reset();
		_soilPersentRange.Reset();
		_soilPersentSiege.Reset();
		_clickBonusClickCount.Reset();
		_clickBonusValue.Reset();
		_heartsBonus.Reset();
		_minTimeBetweenCreeps.Reset();
		_maxTimeBetweenCreeps.Reset();
		_minThinkTime.Reset();
		_maxThinkTime.Reset();
		_waitTime.Reset();
		_fallAsleepTime.Reset();
		_wakeupTime.Reset();
		_workTime.Reset();
		_workBonus.Reset();
		_failBonus.Reset();
		_level1_BarValue.Reset();
		_level3_phase1Min.Reset();
		_level3_phase1Max.Reset();
		_level4_washProbTimes.Reset();
		_level5_fallAsleepTime.Reset();
		_level6_soilAtStart.Reset();
		_level8_timeReduction.Reset();
		_level8_bonusReduction.Reset();
		_level9_washProb.Reset();
		_level10_playProbTimes.Reset();
		_level11_soilIncrease.Reset();
		_level12_soilIncrease.Reset();
		_level12_bonusReduction.Reset();
		_level12_waitDecrease.Reset();
		_uiStyles.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_title.IsDerivedFromParent()
			&& _cameraOptions.IsDerivedFromParent()
			&& _sounds.IsDerivedFromParent()
			&& _bonusSounds.IsDerivedFromParent()
			&& _preselection.IsDerivedFromParent()
			&& _player.IsDerivedFromParent()
			&& _bonuses.IsDerivedFromParent()
			&& _places.IsDerivedFromParent()
			&& _sceneObjectDirty100.IsDerivedFromParent()
			&& _neighbourhood.IsDerivedFromParent()
			&& _levels.IsDerivedFromParent()
			&& _decorations.IsDerivedFromParent()
			&& _creepsDesc.IsDerivedFromParent()
			&& _creepBehaviourDesc.IsDerivedFromParent()
			&& _trainingBonuses.IsDerivedFromParent()
			&& _soilPersentMelee.IsDerivedFromParent()
			&& _soilPersentRange.IsDerivedFromParent()
			&& _soilPersentSiege.IsDerivedFromParent()
			&& _clickBonusClickCount.IsDerivedFromParent()
			&& _clickBonusValue.IsDerivedFromParent()
			&& _heartsBonus.IsDerivedFromParent()
			&& _minTimeBetweenCreeps.IsDerivedFromParent()
			&& _maxTimeBetweenCreeps.IsDerivedFromParent()
			&& _minThinkTime.IsDerivedFromParent()
			&& _maxThinkTime.IsDerivedFromParent()
			&& _waitTime.IsDerivedFromParent()
			&& _fallAsleepTime.IsDerivedFromParent()
			&& _wakeupTime.IsDerivedFromParent()
			&& _workTime.IsDerivedFromParent()
			&& _workBonus.IsDerivedFromParent()
			&& _failBonus.IsDerivedFromParent()
			&& _level1_BarValue.IsDerivedFromParent()
			&& _level3_phase1Min.IsDerivedFromParent()
			&& _level3_phase1Max.IsDerivedFromParent()
			&& _level4_washProbTimes.IsDerivedFromParent()
			&& _level5_fallAsleepTime.IsDerivedFromParent()
			&& _level6_soilAtStart.IsDerivedFromParent()
			&& _level8_timeReduction.IsDerivedFromParent()
			&& _level8_bonusReduction.IsDerivedFromParent()
			&& _level9_washProb.IsDerivedFromParent()
			&& _level10_playProbTimes.IsDerivedFromParent()
			&& _level11_soilIncrease.IsDerivedFromParent()
			&& _level12_soilIncrease.IsDerivedFromParent()
			&& _level12_bonusReduction.IsDerivedFromParent()
			&& _level12_waitDecrease.IsDerivedFromParent()
			&& _uiStyles.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "title" )
			_title.Reset();
		else if ( fieldName == "cameraOptions" )
			_cameraOptions.Reset();
		else if ( fieldName == "sounds" )
			_sounds.Reset();
		else if ( fieldName == "bonusSounds" )
			_bonusSounds.Reset();
		else if ( fieldName == "preselection" )
			_preselection.Reset();
		else if ( fieldName == "player" )
			_player.Reset();
		else if ( fieldName == "bonuses" )
			_bonuses.Reset();
		else if ( fieldName == "places" )
			_places.Reset();
		else if ( fieldName == "sceneObjectDirty100" )
			_sceneObjectDirty100.Reset();
		else if ( fieldName == "neighbourhood" )
			_neighbourhood.Reset();
		else if ( fieldName == "levels" )
			_levels.Reset();
		else if ( fieldName == "decorations" )
			_decorations.Reset();
		else if ( fieldName == "creepsDesc" )
			_creepsDesc.Reset();
		else if ( fieldName == "creepBehaviourDesc" )
			_creepBehaviourDesc.Reset();
		else if ( fieldName == "trainingBonuses" )
			_trainingBonuses.Reset();
		else if ( fieldName == "soilPersentMelee" )
			_soilPersentMelee.Reset();
		else if ( fieldName == "soilPersentRange" )
			_soilPersentRange.Reset();
		else if ( fieldName == "soilPersentSiege" )
			_soilPersentSiege.Reset();
		else if ( fieldName == "clickBonusClickCount" )
			_clickBonusClickCount.Reset();
		else if ( fieldName == "clickBonusValue" )
			_clickBonusValue.Reset();
		else if ( fieldName == "heartsBonus" )
			_heartsBonus.Reset();
		else if ( fieldName == "minTimeBetweenCreeps" )
			_minTimeBetweenCreeps.Reset();
		else if ( fieldName == "maxTimeBetweenCreeps" )
			_maxTimeBetweenCreeps.Reset();
		else if ( fieldName == "minThinkTime" )
			_minThinkTime.Reset();
		else if ( fieldName == "maxThinkTime" )
			_maxThinkTime.Reset();
		else if ( fieldName == "waitTime" )
			_waitTime.Reset();
		else if ( fieldName == "fallAsleepTime" )
			_fallAsleepTime.Reset();
		else if ( fieldName == "wakeupTime" )
			_wakeupTime.Reset();
		else if ( fieldName == "workTime" )
			_workTime.Reset();
		else if ( fieldName == "workBonus" )
			_workBonus.Reset();
		else if ( fieldName == "failBonus" )
			_failBonus.Reset();
		else if ( fieldName == "level1_BarValue" )
			_level1_BarValue.Reset();
		else if ( fieldName == "level3_phase1Min" )
			_level3_phase1Min.Reset();
		else if ( fieldName == "level3_phase1Max" )
			_level3_phase1Max.Reset();
		else if ( fieldName == "level4_washProbTimes" )
			_level4_washProbTimes.Reset();
		else if ( fieldName == "level5_fallAsleepTime" )
			_level5_fallAsleepTime.Reset();
		else if ( fieldName == "level6_soilAtStart" )
			_level6_soilAtStart.Reset();
		else if ( fieldName == "level8_timeReduction" )
			_level8_timeReduction.Reset();
		else if ( fieldName == "level8_bonusReduction" )
			_level8_bonusReduction.Reset();
		else if ( fieldName == "level9_washProb" )
			_level9_washProb.Reset();
		else if ( fieldName == "level10_playProbTimes" )
			_level10_playProbTimes.Reset();
		else if ( fieldName == "level11_soilIncrease" )
			_level11_soilIncrease.Reset();
		else if ( fieldName == "level12_soilIncrease" )
			_level12_soilIncrease.Reset();
		else if ( fieldName == "level12_bonusReduction" )
			_level12_bonusReduction.Reset();
		else if ( fieldName == "level12_waitDecrease" )
			_level12_waitDecrease.Reset();
		else if ( fieldName == "uiStyles" )
			_uiStyles.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "title" )
			return _title.IsDerivedFromParent();
		if ( fieldName == "cameraOptions" )
			return _cameraOptions.IsDerivedFromParent();
		if ( fieldName == "sounds" )
			return _sounds.IsDerivedFromParent();
		if ( fieldName == "bonusSounds" )
			return _bonusSounds.IsDerivedFromParent();
		if ( fieldName == "preselection" )
			return _preselection.IsDerivedFromParent();
		if ( fieldName == "player" )
			return _player.IsDerivedFromParent();
		if ( fieldName == "bonuses" )
			return _bonuses.IsDerivedFromParent();
		if ( fieldName == "places" )
			return _places.IsDerivedFromParent();
		if ( fieldName == "sceneObjectDirty100" )
			return _sceneObjectDirty100.IsDerivedFromParent();
		if ( fieldName == "neighbourhood" )
			return _neighbourhood.IsDerivedFromParent();
		if ( fieldName == "levels" )
			return _levels.IsDerivedFromParent();
		if ( fieldName == "decorations" )
			return _decorations.IsDerivedFromParent();
		if ( fieldName == "creepsDesc" )
			return _creepsDesc.IsDerivedFromParent();
		if ( fieldName == "creepBehaviourDesc" )
			return _creepBehaviourDesc.IsDerivedFromParent();
		if ( fieldName == "trainingBonuses" )
			return _trainingBonuses.IsDerivedFromParent();
		if ( fieldName == "soilPersentMelee" )
			return _soilPersentMelee.IsDerivedFromParent();
		if ( fieldName == "soilPersentRange" )
			return _soilPersentRange.IsDerivedFromParent();
		if ( fieldName == "soilPersentSiege" )
			return _soilPersentSiege.IsDerivedFromParent();
		if ( fieldName == "clickBonusClickCount" )
			return _clickBonusClickCount.IsDerivedFromParent();
		if ( fieldName == "clickBonusValue" )
			return _clickBonusValue.IsDerivedFromParent();
		if ( fieldName == "heartsBonus" )
			return _heartsBonus.IsDerivedFromParent();
		if ( fieldName == "minTimeBetweenCreeps" )
			return _minTimeBetweenCreeps.IsDerivedFromParent();
		if ( fieldName == "maxTimeBetweenCreeps" )
			return _maxTimeBetweenCreeps.IsDerivedFromParent();
		if ( fieldName == "minThinkTime" )
			return _minThinkTime.IsDerivedFromParent();
		if ( fieldName == "maxThinkTime" )
			return _maxThinkTime.IsDerivedFromParent();
		if ( fieldName == "waitTime" )
			return _waitTime.IsDerivedFromParent();
		if ( fieldName == "fallAsleepTime" )
			return _fallAsleepTime.IsDerivedFromParent();
		if ( fieldName == "wakeupTime" )
			return _wakeupTime.IsDerivedFromParent();
		if ( fieldName == "workTime" )
			return _workTime.IsDerivedFromParent();
		if ( fieldName == "workBonus" )
			return _workBonus.IsDerivedFromParent();
		if ( fieldName == "failBonus" )
			return _failBonus.IsDerivedFromParent();
		if ( fieldName == "level1_BarValue" )
			return _level1_BarValue.IsDerivedFromParent();
		if ( fieldName == "level3_phase1Min" )
			return _level3_phase1Min.IsDerivedFromParent();
		if ( fieldName == "level3_phase1Max" )
			return _level3_phase1Max.IsDerivedFromParent();
		if ( fieldName == "level4_washProbTimes" )
			return _level4_washProbTimes.IsDerivedFromParent();
		if ( fieldName == "level5_fallAsleepTime" )
			return _level5_fallAsleepTime.IsDerivedFromParent();
		if ( fieldName == "level6_soilAtStart" )
			return _level6_soilAtStart.IsDerivedFromParent();
		if ( fieldName == "level8_timeReduction" )
			return _level8_timeReduction.IsDerivedFromParent();
		if ( fieldName == "level8_bonusReduction" )
			return _level8_bonusReduction.IsDerivedFromParent();
		if ( fieldName == "level9_washProb" )
			return _level9_washProb.IsDerivedFromParent();
		if ( fieldName == "level10_playProbTimes" )
			return _level10_playProbTimes.IsDerivedFromParent();
		if ( fieldName == "level11_soilIncrease" )
			return _level11_soilIncrease.IsDerivedFromParent();
		if ( fieldName == "level12_soilIncrease" )
			return _level12_soilIncrease.IsDerivedFromParent();
		if ( fieldName == "level12_bonusReduction" )
			return _level12_bonusReduction.IsDerivedFromParent();
		if ( fieldName == "level12_waitDecrease" )
			return _level12_waitDecrease.IsDerivedFromParent();
		if ( fieldName == "uiStyles" )
			return _uiStyles.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
