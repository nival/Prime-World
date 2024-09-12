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
public enum EEffectAlignment
{
	None = 0,
	Ground = 1,
};

public enum EEffectAttachType
{
	General = 0,
	Above = 1,
	Ground = 2,
	Body = 3,
	Death = 4,
	Head = 5,
};

public enum EEffectDeathType
{
	Manual = 0,
	Anim = 1,
	Time = 2,
};

public enum EEffectEvent
{
	Attack = 0,
	Death = 1,
	Stop = 2,
};

public enum EEffectGenPolicy
{
	Start = 0,
	Death = 1,
	Regular = 2,
};

[Flags]
public enum EEffectGroupFlags
{
	None = 0,
	IgnoreColorModification = 1048576,
	IgnoreInvisibility = 2097152,
};

public enum EEffects
{
	Empty = 0,
	LevelUp = 1,
	ClickOnTerrain = 2,
	OnDamageFragTeamA = 3,
	OnDamageFragTeamB = 4,
	OnBuildingDestructTeamA = 5,
	OnBuildingDestructTeamB = 6,
	ControlledHeroAura = 7,
	SelectionAuraSelf = 8,
	SelectionAuraAlly = 9,
	SelectionAuraHostile = 10,
	PreSelectionAuraSelf = 11,
	PreSelectionAuraAlly = 12,
	PreSelectionAuraHostile = 13,
	SelectionPickSelf = 14,
	SelectionPickAlly = 15,
	SelectionPickHostile = 16,
	SelectionBuildingPickSelf = 17,
	SelectionBuildingPickAlly = 18,
	SelectionBuildingPickHostile = 19,
	MarkerAlly = 20,
	MarkerHostile = 21,
	MarkerChat = 22,
	DefaultEffect = 23,
	GlowEffectA = 24,
	GlowEffectB = 25,
	RotateAnimationEffect = 26,
	MinigameScrollGiven = 27,
	TowerAttackEffectAlly = 28,
	TowerAttackEffectEnemy = 29,
};

public enum EEffectSelectionPolicy
{
	Random = 0,
	Sequential = 1,
};

public enum EnableSCEffectMode
{
	ComponentId = 0,
	EventName = 1,
};

public class EffectEventAction : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EffectEventAction __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _animation;
	private UndoRedo<string> _marker;

	[Description( "Animation to play" )]
	public string animation { get { return _animation.Get(); } set { _animation.Set( value ); } }

	[Description( "Marker to synchronize with event" )]
	public string marker { get { return _marker.Get(); } set { _marker.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_animation = new UndoRedo<string>( owner, string.Empty );
		_marker = new UndoRedo<string>( owner, string.Empty );
		_animation.Changed += FireChangedEvent;
		_marker.Changed += FireChangedEvent;
	}

	public EffectEventAction()
	{
		Initialize( GetOwner() );
	}

	public EffectEventAction( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EffectEventAction( DBResource owner, EffectEventAction source )
		: this(owner, source, true){}

	protected EffectEventAction( DBResource owner, EffectEventAction source, bool fireEvent )
	{
		_animation = new UndoRedo<string>( owner, source.animation );
		_marker = new UndoRedo<string>( owner, source.marker );
		_animation.Changed += FireChangedEvent;
		_marker.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EffectEventAction source = _source as EffectEventAction;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectEventAction" );
		animation = source.animation;
		marker = source.marker;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EffectEventAction newParent = _newParent as EffectEventAction;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_animation.SetParent( newParent == null ? null : newParent._animation );
		_marker.SetParent( newParent == null ? null : newParent._marker );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_animation.Reset();
		_marker.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_animation.IsDerivedFromParent()
			&& _marker.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "animation" )
			_animation.Reset();
		else if ( fieldName == "marker" )
			_marker.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "animation" )
			return _animation.IsDerivedFromParent();
		if ( fieldName == "marker" )
			return _marker.IsDerivedFromParent();
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
public class SpringParamDynamics : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private SpringParamDynamics __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _speed;
	private UndoRedo<float> _maxValue;

	[Description( "Множитель скорости изменения параметра" )]
	public float speed { get { return _speed.Get(); } set { _speed.Set( value ); } }

	[Description( "Максимальное отставание (-1 значит не ограничено)" )]
	public float maxValue { get { return _maxValue.Get(); } set { _maxValue.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_speed = new UndoRedo<float>( owner, 1.0f );
		_maxValue = new UndoRedo<float>( owner, -1.0f );
		_speed.Changed += FireChangedEvent;
		_maxValue.Changed += FireChangedEvent;
	}

	public SpringParamDynamics()
	{
		Initialize( GetOwner() );
	}

	public SpringParamDynamics( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public SpringParamDynamics( DBResource owner, SpringParamDynamics source )
		: this(owner, source, true){}

	protected SpringParamDynamics( DBResource owner, SpringParamDynamics source, bool fireEvent )
	{
		_speed = new UndoRedo<float>( owner, source.speed );
		_maxValue = new UndoRedo<float>( owner, source.maxValue );
		_speed.Changed += FireChangedEvent;
		_maxValue.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		SpringParamDynamics source = _source as SpringParamDynamics;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpringParamDynamics" );
		speed = source.speed;
		maxValue = source.maxValue;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		SpringParamDynamics newParent = _newParent as SpringParamDynamics;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_speed.SetParent( newParent == null ? null : newParent._speed );
		_maxValue.SetParent( newParent == null ? null : newParent._maxValue );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_speed.Reset();
		_maxValue.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_speed.IsDerivedFromParent()
			&& _maxValue.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "speed" )
			_speed.Reset();
		else if ( fieldName == "maxValue" )
			_maxValue.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "speed" )
			return _speed.IsDerivedFromParent();
		if ( fieldName == "maxValue" )
			return _maxValue.IsDerivedFromParent();
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

public class TraceInfo : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private TraceInfo __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<string> _nodeName;
	private UndoRedo<string> _locatorName;
	private UndoRedoDBPtr<Trace> _traces;

	[Description( "Animation node name (traces will be generated when in this node)" )]
	public string nodeName { get { return _nodeName.Get(); } set { _nodeName.Set( value ); } }

	[Description( "Locator name (traces will be generated at this locator's position)" )]
	public string locatorName { get { return _locatorName.Get(); } set { _locatorName.Set( value ); } }

	public DBPtr<Trace> traces { get { return _traces.Get(); } set { _traces.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_nodeName = new UndoRedo<string>( owner, string.Empty );
		_locatorName = new UndoRedo<string>( owner, string.Empty );
		_traces = new UndoRedoDBPtr<Trace>( owner );
		_nodeName.Changed += FireChangedEvent;
		_locatorName.Changed += FireChangedEvent;
		_traces.Changed += FireChangedEvent;
	}

	public TraceInfo()
	{
		Initialize( GetOwner() );
	}

	public TraceInfo( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public TraceInfo( DBResource owner, TraceInfo source )
		: this(owner, source, true){}

	protected TraceInfo( DBResource owner, TraceInfo source, bool fireEvent )
	{
		_nodeName = new UndoRedo<string>( owner, source.nodeName );
		_locatorName = new UndoRedo<string>( owner, source.locatorName );
		_traces = new UndoRedoDBPtr<Trace>( owner, source.traces );
		_nodeName.Changed += FireChangedEvent;
		_locatorName.Changed += FireChangedEvent;
		_traces.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		TraceInfo source = _source as TraceInfo;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TraceInfo" );
		nodeName = source.nodeName;
		locatorName = source.locatorName;
		traces = source.traces;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		TraceInfo newParent = _newParent as TraceInfo;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_nodeName.SetParent( newParent == null ? null : newParent._nodeName );
		_locatorName.SetParent( newParent == null ? null : newParent._locatorName );
		_traces.SetParent( newParent == null ? null : newParent._traces );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_nodeName.Reset();
		_locatorName.Reset();
		_traces.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_nodeName.IsDerivedFromParent()
			&& _locatorName.IsDerivedFromParent()
			&& _traces.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "nodeName" )
			_nodeName.Reset();
		else if ( fieldName == "locatorName" )
			_locatorName.Reset();
		else if ( fieldName == "traces" )
			_traces.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "nodeName" )
			return _nodeName.IsDerivedFromParent();
		if ( fieldName == "locatorName" )
			return _locatorName.IsDerivedFromParent();
		if ( fieldName == "traces" )
			return _traces.IsDerivedFromParent();
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

[FactoryBase("Retrieve", "PF_Core::BasicEffect", "PF_Core::ObjectsPool &pool", ReturnType = "CObj<PF_Core::BasicEffect>", Define = "!VISUAL_CUTTED")]
[HasStates]
[TypeId(0xA06253C0)]
[UseTypeName("EFFT")]
public class EffectBase : DBResource
{
	private UndoRedoDBPtr<EffectBase> ___parent;
	[HideInOutliner]
	public new DBPtr<EffectBase> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EEffectDeathType> _deathType;
	private UndoRedo<float> _lifeTime;
	private UndoRedoDBPtr<ConditionFormula> _enableCondition;

	public EEffectDeathType deathType { get { return _deathType.Get(); } set { _deathType.Set( value ); } }

	public float lifeTime { get { return _lifeTime.Get(); } set { _lifeTime.Set( value ); } }

	[Description( "Формула для активации эффекта; true = активировать; Если поле не задано, то считается что условие выполняется." )]
	public DBPtr<ConditionFormula> enableCondition { get { return _enableCondition.Get(); } set { _enableCondition.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EffectBase>(owner);
		_deathType = new UndoRedo<EEffectDeathType>( owner, EEffectDeathType.Manual );
		_lifeTime = new UndoRedo<float>( owner, 0.0f );
		_enableCondition = new UndoRedoDBPtr<ConditionFormula>( owner );
		___parent.Changed += FireChangedEvent;
		_deathType.Changed += FireChangedEvent;
		_lifeTime.Changed += FireChangedEvent;
		_enableCondition.Changed += FireChangedEvent;
	}

	public EffectBase()
	{
		Initialize( this );
	}
	private void AssignSelf( EffectBase source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EffectBase" );
		deathType = source.deathType;
		lifeTime = source.lifeTime;
		enableCondition = source.enableCondition;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EffectBase source = _source as EffectBase;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectBase" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EffectBase newParent = rawParent == null ? null : rawParent.Get<EffectBase>();
		if ( newParent == null && _newParent is EffectBase )
			newParent = _newParent as EffectBase;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_deathType.SetParent( newParent == null ? null : newParent._deathType );
		_lifeTime.SetParent( newParent == null ? null : newParent._lifeTime );
		_enableCondition.SetParent( newParent == null ? null : newParent._enableCondition );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_deathType.Reset();
		_lifeTime.Reset();
		_enableCondition.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_deathType.IsDerivedFromParent()
			&& _lifeTime.IsDerivedFromParent()
			&& _enableCondition.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "deathType" )
			_deathType.Reset();
		else if ( fieldName == "lifeTime" )
			_lifeTime.Reset();
		else if ( fieldName == "enableCondition" )
			_enableCondition.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "deathType" )
			return _deathType.IsDerivedFromParent();
		if ( fieldName == "lifeTime" )
			return _lifeTime.IsDerivedFromParent();
		if ( fieldName == "enableCondition" )
			return _enableCondition.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0xA06253C1)]
[UseTypeName("EFFT")]
public class BasicEffect : EffectBase
{
	private UndoRedoDBPtr<BasicEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<BasicEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<DBSceneComponent> _component;
	private UndoRedo<float> _fadeIn;
	private UndoRedo<float> _fadeOut;

	public DBPtr<DBSceneComponent> component { get { return _component.Get(); } set { _component.Set( value ); } }

	public float fadeIn { get { return _fadeIn.Get(); } set { _fadeIn.Set( value ); } }

	public float fadeOut { get { return _fadeOut.Get(); } set { _fadeOut.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BasicEffect>(owner);
		_component = new UndoRedoDBPtr<DBSceneComponent>( owner );
		_fadeIn = new UndoRedo<float>( owner, 0.0f );
		_fadeOut = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_component.Changed += FireChangedEvent;
		_fadeIn.Changed += FireChangedEvent;
		_fadeOut.Changed += FireChangedEvent;
	}

	public BasicEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( BasicEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BasicEffect" );
		component = source.component;
		fadeIn = source.fadeIn;
		fadeOut = source.fadeOut;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BasicEffect source = _source as BasicEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BasicEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BasicEffect newParent = rawParent == null ? null : rawParent.Get<BasicEffect>();
		if ( newParent == null && _newParent is BasicEffect )
			newParent = _newParent as BasicEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_component.SetParent( newParent == null ? null : newParent._component );
		_fadeIn.SetParent( newParent == null ? null : newParent._fadeIn );
		_fadeOut.SetParent( newParent == null ? null : newParent._fadeOut );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_component.Reset();
		_fadeIn.Reset();
		_fadeOut.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_component.IsDerivedFromParent()
			&& _fadeIn.IsDerivedFromParent()
			&& _fadeOut.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "component" )
			_component.Reset();
		else if ( fieldName == "fadeIn" )
			_fadeIn.Reset();
		else if ( fieldName == "fadeOut" )
			_fadeOut.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "component" )
			return _component.IsDerivedFromParent();
		if ( fieldName == "fadeIn" )
			return _fadeIn.IsDerivedFromParent();
		if ( fieldName == "fadeOut" )
			return _fadeOut.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Retrieve", "PF_Core::BasicEffectStandalone", "EffectsPool.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xA06253C2)]
[UseTypeName("EFFT")]
public class BasicEffectStandalone : BasicEffect
{
	private UndoRedoDBPtr<BasicEffectStandalone> ___parent;
	[HideInOutliner]
	public new DBPtr<BasicEffectStandalone> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<bool> _visibilityLimited;
	private UndoRedo<float> _visibleTime;
	private UndoRedo<bool> _isVisibleUnderWarfog;
	private UndoRedo<string> _parentType;
	private UndoRedo<EStandAloneEffectFlags> _parentFlags;

	[Description( "If true effective visibility is limited by visibleTime, otherwise it's limited only by visibility itself." )]
	public bool visibilityLimited { get { return _visibilityLimited.Get(); } set { _visibilityLimited.Set( value ); } }

	public float visibleTime { get { return _visibleTime.Get(); } set { _visibleTime.Set( value ); } }

	public bool isVisibleUnderWarfog { get { return _isVisibleUnderWarfog.Get(); } set { _isVisibleUnderWarfog.Set( value ); } }

	[DefaultValues(typeof( EEffectAttachType ))]
	public string parentType { get { return _parentType.Get(); } set { _parentType.Set( value ); } }

	public EStandAloneEffectFlags parentFlags { get { return _parentFlags.Get(); } set { _parentFlags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BasicEffectStandalone>(owner);
		_visibilityLimited = new UndoRedo<bool>( owner, false );
		_visibleTime = new UndoRedo<float>( owner, 0.0f );
		_isVisibleUnderWarfog = new UndoRedo<bool>( owner, false );
		_parentType = new UndoRedo<string>( owner, "General" );
		_parentFlags = new UndoRedo<EStandAloneEffectFlags>( owner, EStandAloneEffectFlags.None );
		___parent.Changed += FireChangedEvent;
		_visibilityLimited.Changed += FireChangedEvent;
		_visibleTime.Changed += FireChangedEvent;
		_isVisibleUnderWarfog.Changed += FireChangedEvent;
		_parentType.Changed += FireChangedEvent;
		_parentFlags.Changed += FireChangedEvent;
	}

	public BasicEffectStandalone()
	{
		Initialize( this );
	}
	private void AssignSelf( BasicEffectStandalone source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BasicEffectStandalone" );
		visibilityLimited = source.visibilityLimited;
		visibleTime = source.visibleTime;
		isVisibleUnderWarfog = source.isVisibleUnderWarfog;
		parentType = source.parentType;
		parentFlags = source.parentFlags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BasicEffectStandalone source = _source as BasicEffectStandalone;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BasicEffectStandalone" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BasicEffectStandalone newParent = rawParent == null ? null : rawParent.Get<BasicEffectStandalone>();
		if ( newParent == null && _newParent is BasicEffectStandalone )
			newParent = _newParent as BasicEffectStandalone;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_visibilityLimited.SetParent( newParent == null ? null : newParent._visibilityLimited );
		_visibleTime.SetParent( newParent == null ? null : newParent._visibleTime );
		_isVisibleUnderWarfog.SetParent( newParent == null ? null : newParent._isVisibleUnderWarfog );
		_parentType.SetParent( newParent == null ? null : newParent._parentType );
		_parentFlags.SetParent( newParent == null ? null : newParent._parentFlags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_visibilityLimited.Reset();
		_visibleTime.Reset();
		_isVisibleUnderWarfog.Reset();
		_parentType.Reset();
		_parentFlags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_visibilityLimited.IsDerivedFromParent()
			&& _visibleTime.IsDerivedFromParent()
			&& _isVisibleUnderWarfog.IsDerivedFromParent()
			&& _parentType.IsDerivedFromParent()
			&& _parentFlags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "visibilityLimited" )
			_visibilityLimited.Reset();
		else if ( fieldName == "visibleTime" )
			_visibleTime.Reset();
		else if ( fieldName == "isVisibleUnderWarfog" )
			_isVisibleUnderWarfog.Reset();
		else if ( fieldName == "parentType" )
			_parentType.Reset();
		else if ( fieldName == "parentFlags" )
			_parentFlags.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "visibilityLimited" )
			return _visibilityLimited.IsDerivedFromParent();
		if ( fieldName == "visibleTime" )
			return _visibleTime.IsDerivedFromParent();
		if ( fieldName == "isVisibleUnderWarfog" )
			return _isVisibleUnderWarfog.IsDerivedFromParent();
		if ( fieldName == "parentType" )
			return _parentType.IsDerivedFromParent();
		if ( fieldName == "parentFlags" )
			return _parentFlags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "PF_Core::CameraShakeSceneComponent", "CameraShakeSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0xA0698AC0)]
[UseTypeName("CSSC")]
public class CameraShakeSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<CameraShakeSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<CameraShakeSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<AnimatedPlacementResource> _displacement;
	private UndoRedo<float> _range;

	[Description( "Animated camera displacement" )]
	public DBPtr<AnimatedPlacementResource> displacement { get { return _displacement.Get(); } set { _displacement.Set( value ); } }

	[Description( "Maximum distance between camera anchor and component for shake to be visible" )]
	public float range { get { return _range.Get(); } set { _range.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CameraShakeSceneComponent>(owner);
		_displacement = new UndoRedoDBPtr<AnimatedPlacementResource>( owner );
		_range = new UndoRedo<float>( owner, 10.0f );
		___parent.Changed += FireChangedEvent;
		_displacement.Changed += FireChangedEvent;
		_range.Changed += FireChangedEvent;
	}

	public CameraShakeSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( CameraShakeSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CameraShakeSceneComponent" );
		displacement = source.displacement;
		range = source.range;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CameraShakeSceneComponent source = _source as CameraShakeSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CameraShakeSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CameraShakeSceneComponent newParent = rawParent == null ? null : rawParent.Get<CameraShakeSceneComponent>();
		if ( newParent == null && _newParent is CameraShakeSceneComponent )
			newParent = _newParent as CameraShakeSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_displacement.SetParent( newParent == null ? null : newParent._displacement );
		_range.SetParent( newParent == null ? null : newParent._range );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_displacement.Reset();
		_range.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_displacement.IsDerivedFromParent()
			&& _range.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "displacement" )
			_displacement.Reset();
		else if ( fieldName == "range" )
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
		if ( fieldName == "displacement" )
			return _displacement.IsDerivedFromParent();
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

[DBVersion(1)]
[FactoryImpl("Retrieve", "PF_Core::ChangeMaterialEffect", "ChangeMaterialEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0x9DAA1380)]
[UseTypeName("EFFT")]
public class ChangeMaterialEffect : EffectBase
{
	private UndoRedoDBPtr<ChangeMaterialEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<ChangeMaterialEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _fadeInTime;
	private UndoRedo<float> _fadeOutTime;
	private UndoRedoAssignableList<DBPtr<Material>> _materials;

	public float fadeInTime { get { return _fadeInTime.Get(); } set { _fadeInTime.Set( value ); } }

	public float fadeOutTime { get { return _fadeOutTime.Get(); } set { _fadeOutTime.Set( value ); } }

	public libdb.IChangeableList<DBPtr<Material>> materials { get { return _materials; } set { _materials.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ChangeMaterialEffect>(owner);
		_fadeInTime = new UndoRedo<float>( owner, 1.0f );
		_fadeOutTime = new UndoRedo<float>( owner, 1.0f );
		_materials = new UndoRedoAssignableList<DBPtr<Material>>( owner );
		___parent.Changed += FireChangedEvent;
		_fadeInTime.Changed += FireChangedEvent;
		_fadeOutTime.Changed += FireChangedEvent;
		_materials.Changed += FireChangedEvent;
	}

	public ChangeMaterialEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( ChangeMaterialEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ChangeMaterialEffect" );
		fadeInTime = source.fadeInTime;
		fadeOutTime = source.fadeOutTime;
		materials = source.materials;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ChangeMaterialEffect source = _source as ChangeMaterialEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ChangeMaterialEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ChangeMaterialEffect newParent = rawParent == null ? null : rawParent.Get<ChangeMaterialEffect>();
		if ( newParent == null && _newParent is ChangeMaterialEffect )
			newParent = _newParent as ChangeMaterialEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fadeInTime.SetParent( newParent == null ? null : newParent._fadeInTime );
		_fadeOutTime.SetParent( newParent == null ? null : newParent._fadeOutTime );
		_materials.SetParent( newParent == null ? null : newParent._materials );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fadeInTime.Reset();
		_fadeOutTime.Reset();
		_materials.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fadeInTime.IsDerivedFromParent()
			&& _fadeOutTime.IsDerivedFromParent()
			&& _materials.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fadeInTime" )
			_fadeInTime.Reset();
		else if ( fieldName == "fadeOutTime" )
			_fadeOutTime.Reset();
		else if ( fieldName == "materials" )
			_materials.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fadeInTime" )
			return _fadeInTime.IsDerivedFromParent();
		if ( fieldName == "fadeOutTime" )
			return _fadeOutTime.IsDerivedFromParent();
		if ( fieldName == "materials" )
			return _materials.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class PositionRandomizer : DBResource
{
	private UndoRedoDBPtr<PositionRandomizer> ___parent;
	[HideInOutliner]
	public new DBPtr<PositionRandomizer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PositionRandomizer>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public PositionRandomizer()
	{
		Initialize( this );
	}
	private void AssignSelf( PositionRandomizer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PositionRandomizer" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PositionRandomizer source = _source as PositionRandomizer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PositionRandomizer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PositionRandomizer newParent = rawParent == null ? null : rawParent.Get<PositionRandomizer>();
		if ( newParent == null && _newParent is PositionRandomizer )
			newParent = _newParent as PositionRandomizer;
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

[FactoryImpl("Retrieve", "PF_Core::BasicEffectAttached", "EffectsPool.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xA06253C3)]
[UseTypeName("EFFT")]
public class BasicEffectAttached : BasicEffect
{
	private UndoRedoDBPtr<BasicEffectAttached> ___parent;
	[HideInOutliner]
	public new DBPtr<BasicEffectAttached> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _attachType;
	private UndoRedo<EAttachFlags> _attachFlags;
	private UndoRedo<EEffectGroupFlags> _groupFlags;

	[DefaultValues(typeof( EEffectAttachType ))]
	public string attachType { get { return _attachType.Get(); } set { _attachType.Set( value ); } }

	public EAttachFlags attachFlags { get { return _attachFlags.Get(); } set { _attachFlags.Set( value ); } }

	public EEffectGroupFlags groupFlags { get { return _groupFlags.Get(); } set { _groupFlags.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<BasicEffectAttached>(owner);
		_attachType = new UndoRedo<string>( owner, "General" );
		_attachFlags = new UndoRedo<EAttachFlags>( owner, EAttachFlags.None );
		_groupFlags = new UndoRedo<EEffectGroupFlags>( owner, EEffectGroupFlags.None );
		___parent.Changed += FireChangedEvent;
		_attachType.Changed += FireChangedEvent;
		_attachFlags.Changed += FireChangedEvent;
		_groupFlags.Changed += FireChangedEvent;
	}

	public BasicEffectAttached()
	{
		Initialize( this );
	}
	private void AssignSelf( BasicEffectAttached source )
	{
		DataBase.UndoRedoManager.Start( "Assign for BasicEffectAttached" );
		attachType = source.attachType;
		attachFlags = source.attachFlags;
		groupFlags = source.groupFlags;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		BasicEffectAttached source = _source as BasicEffectAttached;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for BasicEffectAttached" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		BasicEffectAttached newParent = rawParent == null ? null : rawParent.Get<BasicEffectAttached>();
		if ( newParent == null && _newParent is BasicEffectAttached )
			newParent = _newParent as BasicEffectAttached;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_attachType.SetParent( newParent == null ? null : newParent._attachType );
		_attachFlags.SetParent( newParent == null ? null : newParent._attachFlags );
		_groupFlags.SetParent( newParent == null ? null : newParent._groupFlags );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_attachType.Reset();
		_attachFlags.Reset();
		_groupFlags.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_attachType.IsDerivedFromParent()
			&& _attachFlags.IsDerivedFromParent()
			&& _groupFlags.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "attachType" )
			_attachType.Reset();
		else if ( fieldName == "attachFlags" )
			_attachFlags.Reset();
		else if ( fieldName == "groupFlags" )
			_groupFlags.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "attachType" )
			return _attachType.IsDerivedFromParent();
		if ( fieldName == "attachFlags" )
			return _attachFlags.IsDerivedFromParent();
		if ( fieldName == "groupFlags" )
			return _groupFlags.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Retrieve", "PF_Core::ControlledStatusEffect", "EffectsPool.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xA06CEBC0)]
[UseTypeName("EFFT")]
public class ControlledStatusEffect : BasicEffectAttached
{
	private UndoRedoDBPtr<ControlledStatusEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<ControlledStatusEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<EffectEventAction> _eventActions;
	private UndoRedoDBPtr<BasicEffectStandalone> _onDeathEffect;

	[Description( "Actions for events" )]
	[EnumArray(typeof(EEffectEvent))]
	public libdb.IChangeableList<EffectEventAction> eventActions { get { return _eventActions; } set { _eventActions.Assign( value ); } }

	[Description( "Standalone afterlife extension (starts upon DEATH event, scene components inherited)" )]
	public DBPtr<BasicEffectStandalone> onDeathEffect { get { return _onDeathEffect.Get(); } set { _onDeathEffect.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ControlledStatusEffect>(owner);
		_eventActions = new UndoRedoAssignableList<EffectEventAction>( owner, typeof( EEffectEvent ) );
		_onDeathEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		___parent.Changed += FireChangedEvent;
		_eventActions.Changed += FireChangedEvent;
		_onDeathEffect.Changed += FireChangedEvent;
	}

	public ControlledStatusEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( ControlledStatusEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ControlledStatusEffect" );
		eventActions = source.eventActions;
		onDeathEffect = source.onDeathEffect;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ControlledStatusEffect source = _source as ControlledStatusEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ControlledStatusEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ControlledStatusEffect newParent = rawParent == null ? null : rawParent.Get<ControlledStatusEffect>();
		if ( newParent == null && _newParent is ControlledStatusEffect )
			newParent = _newParent as ControlledStatusEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_eventActions.SetParent( newParent == null ? null : newParent._eventActions );
		_onDeathEffect.SetParent( newParent == null ? null : newParent._onDeathEffect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_eventActions.Reset();
		_onDeathEffect.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_eventActions.IsDerivedFromParent()
			&& _onDeathEffect.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "eventActions" )
			_eventActions.Reset();
		else if ( fieldName == "onDeathEffect" )
			_onDeathEffect.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "eventActions" )
			return _eventActions.IsDerivedFromParent();
		if ( fieldName == "onDeathEffect" )
			return _onDeathEffect.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "PF_Core::EffectGenSceneComponent", "EffectGenSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0x9E6433C0)]
[UseTypeName("EGSC")]
public class EffectGenSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<EffectGenSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<EffectGenSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<EffectSelector> _effect;
	private UndoRedo<EEffectGenPolicy> _generationPolicy;
	private UndoRedo<float> _minPeriod;
	private UndoRedo<float> _maxPeriod;
	private UndoRedoDBPtr<PositionRandomizer> _posRandomizer;
	private UndoRedo<bool> _randomizeDirection;
	private UndoRedo<EEffectAlignment> _alignment;
	private UndoRedo<float> _offset;

	[Description( "Effect to be created" )]
	public DBPtr<EffectSelector> effect { get { return _effect.Get(); } set { _effect.Set( value ); } }

	[Category( "Generation" )]
	public EEffectGenPolicy generationPolicy { get { return _generationPolicy.Get(); } set { _generationPolicy.Set( value ); } }

	[Category( "Generation" )]
	public float minPeriod { get { return _minPeriod.Get(); } set { _minPeriod.Set( value ); } }

	[Category( "Generation" )]
	public float maxPeriod { get { return _maxPeriod.Get(); } set { _maxPeriod.Set( value ); } }

	[Category( "Randomization" )]
	public DBPtr<PositionRandomizer> posRandomizer { get { return _posRandomizer.Get(); } set { _posRandomizer.Set( value ); } }

	[Category( "Randomization" )]
	public bool randomizeDirection { get { return _randomizeDirection.Get(); } set { _randomizeDirection.Set( value ); } }

	public EEffectAlignment alignment { get { return _alignment.Get(); } set { _alignment.Set( value ); } }

	public float offset { get { return _offset.Get(); } set { _offset.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EffectGenSceneComponent>(owner);
		_effect = new UndoRedoDBPtr<EffectSelector>( owner );
		_generationPolicy = new UndoRedo<EEffectGenPolicy>( owner, EEffectGenPolicy.Start );
		_minPeriod = new UndoRedo<float>( owner, 1.0f );
		_maxPeriod = new UndoRedo<float>( owner, 1.0f );
		_posRandomizer = new UndoRedoDBPtr<PositionRandomizer>( owner );
		_randomizeDirection = new UndoRedo<bool>( owner, false );
		_alignment = new UndoRedo<EEffectAlignment>( owner, EEffectAlignment.None );
		_offset = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
		_generationPolicy.Changed += FireChangedEvent;
		_minPeriod.Changed += FireChangedEvent;
		_maxPeriod.Changed += FireChangedEvent;
		_posRandomizer.Changed += FireChangedEvent;
		_randomizeDirection.Changed += FireChangedEvent;
		_alignment.Changed += FireChangedEvent;
		_offset.Changed += FireChangedEvent;
	}

	public EffectGenSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( EffectGenSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EffectGenSceneComponent" );
		effect = source.effect;
		generationPolicy = source.generationPolicy;
		minPeriod = source.minPeriod;
		maxPeriod = source.maxPeriod;
		posRandomizer = source.posRandomizer;
		randomizeDirection = source.randomizeDirection;
		alignment = source.alignment;
		offset = source.offset;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EffectGenSceneComponent source = _source as EffectGenSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectGenSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EffectGenSceneComponent newParent = rawParent == null ? null : rawParent.Get<EffectGenSceneComponent>();
		if ( newParent == null && _newParent is EffectGenSceneComponent )
			newParent = _newParent as EffectGenSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_effect.SetParent( newParent == null ? null : newParent._effect );
		_generationPolicy.SetParent( newParent == null ? null : newParent._generationPolicy );
		_minPeriod.SetParent( newParent == null ? null : newParent._minPeriod );
		_maxPeriod.SetParent( newParent == null ? null : newParent._maxPeriod );
		_posRandomizer.SetParent( newParent == null ? null : newParent._posRandomizer );
		_randomizeDirection.SetParent( newParent == null ? null : newParent._randomizeDirection );
		_alignment.SetParent( newParent == null ? null : newParent._alignment );
		_offset.SetParent( newParent == null ? null : newParent._offset );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_effect.Reset();
		_generationPolicy.Reset();
		_minPeriod.Reset();
		_maxPeriod.Reset();
		_posRandomizer.Reset();
		_randomizeDirection.Reset();
		_alignment.Reset();
		_offset.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_effect.IsDerivedFromParent()
			&& _generationPolicy.IsDerivedFromParent()
			&& _minPeriod.IsDerivedFromParent()
			&& _maxPeriod.IsDerivedFromParent()
			&& _posRandomizer.IsDerivedFromParent()
			&& _randomizeDirection.IsDerivedFromParent()
			&& _alignment.IsDerivedFromParent()
			&& _offset.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "effect" )
			_effect.Reset();
		else if ( fieldName == "generationPolicy" )
			_generationPolicy.Reset();
		else if ( fieldName == "minPeriod" )
			_minPeriod.Reset();
		else if ( fieldName == "maxPeriod" )
			_maxPeriod.Reset();
		else if ( fieldName == "posRandomizer" )
			_posRandomizer.Reset();
		else if ( fieldName == "randomizeDirection" )
			_randomizeDirection.Reset();
		else if ( fieldName == "alignment" )
			_alignment.Reset();
		else if ( fieldName == "offset" )
			_offset.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "effect" )
			return _effect.IsDerivedFromParent();
		if ( fieldName == "generationPolicy" )
			return _generationPolicy.IsDerivedFromParent();
		if ( fieldName == "minPeriod" )
			return _minPeriod.IsDerivedFromParent();
		if ( fieldName == "maxPeriod" )
			return _maxPeriod.IsDerivedFromParent();
		if ( fieldName == "posRandomizer" )
			return _posRandomizer.IsDerivedFromParent();
		if ( fieldName == "randomizeDirection" )
			return _randomizeDirection.IsDerivedFromParent();
		if ( fieldName == "alignment" )
			return _alignment.IsDerivedFromParent();
		if ( fieldName == "offset" )
			return _offset.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[TypeId(0x2B823BC0)]
[UseTypeName("EFFT")]
public class EffectList : EffectBase
{
	private UndoRedoDBPtr<EffectList> ___parent;
	[HideInOutliner]
	public new DBPtr<EffectList> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<EffectBase>> _effects;

	public libdb.IChangeableList<DBPtr<EffectBase>> effects { get { return _effects; } set { _effects.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EffectList>(owner);
		_effects = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner );
		___parent.Changed += FireChangedEvent;
		_effects.Changed += FireChangedEvent;
	}

	public EffectList()
	{
		Initialize( this );
	}
	private void AssignSelf( EffectList source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EffectList" );
		effects = source.effects;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EffectList source = _source as EffectList;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectList" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EffectList newParent = rawParent == null ? null : rawParent.Get<EffectList>();
		if ( newParent == null && _newParent is EffectList )
			newParent = _newParent as EffectList;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_effects.SetParent( newParent == null ? null : newParent._effects );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_effects.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_effects.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "effects" )
			_effects.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "effects" )
			return _effects.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("ESEL")]
public class EffectSelector : DBResource
{
	private UndoRedoDBPtr<EffectSelector> ___parent;
	[HideInOutliner]
	public new DBPtr<EffectSelector> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<BasicEffectStandalone>> _effects;
	private UndoRedo<EEffectSelectionPolicy> _selectionPolicy;

	[Description( "Effects to select from" )]
	public libdb.IChangeableList<DBPtr<BasicEffectStandalone>> effects { get { return _effects; } set { _effects.Assign( value ); } }

	[Description( "Method to select effect" )]
	public EEffectSelectionPolicy selectionPolicy { get { return _selectionPolicy.Get(); } set { _selectionPolicy.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EffectSelector>(owner);
		_effects = new UndoRedoAssignableList<DBPtr<BasicEffectStandalone>>( owner );
		_selectionPolicy = new UndoRedo<EEffectSelectionPolicy>( owner, EEffectSelectionPolicy.Random );
		___parent.Changed += FireChangedEvent;
		_effects.Changed += FireChangedEvent;
		_selectionPolicy.Changed += FireChangedEvent;
	}

	public EffectSelector()
	{
		Initialize( this );
	}
	private void AssignSelf( EffectSelector source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EffectSelector" );
		effects = source.effects;
		selectionPolicy = source.selectionPolicy;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EffectSelector source = _source as EffectSelector;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectSelector" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EffectSelector newParent = rawParent == null ? null : rawParent.Get<EffectSelector>();
		if ( newParent == null && _newParent is EffectSelector )
			newParent = _newParent as EffectSelector;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_effects.SetParent( newParent == null ? null : newParent._effects );
		_selectionPolicy.SetParent( newParent == null ? null : newParent._selectionPolicy );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_effects.Reset();
		_selectionPolicy.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_effects.IsDerivedFromParent()
			&& _selectionPolicy.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "effects" )
			_effects.Reset();
		else if ( fieldName == "selectionPolicy" )
			_selectionPolicy.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "effects" )
			return _effects.IsDerivedFromParent();
		if ( fieldName == "selectionPolicy" )
			return _selectionPolicy.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(4)]
[UseTypeName("EFPL")]
public class EffectsPool : DBResource
{
	private UndoRedoDBPtr<EffectsPool> ___parent;
	[HideInOutliner]
	public new DBPtr<EffectsPool> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<EffectBase>> _effectsList;

	[EnumArray(typeof(EEffects))]
	public libdb.IChangeableList<DBPtr<EffectBase>> effectsList { get { return _effectsList; } set { _effectsList.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EffectsPool>(owner);
		_effectsList = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner, typeof( EEffects ) );
		___parent.Changed += FireChangedEvent;
		_effectsList.Changed += FireChangedEvent;
	}

	public EffectsPool()
	{
		Initialize( this );
	}
	private void AssignSelf( EffectsPool source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EffectsPool" );
		effectsList = source.effectsList;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EffectsPool source = _source as EffectsPool;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectsPool" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EffectsPool newParent = rawParent == null ? null : rawParent.Get<EffectsPool>();
		if ( newParent == null && _newParent is EffectsPool )
			newParent = _newParent as EffectsPool;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_effectsList.SetParent( newParent == null ? null : newParent._effectsList );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_effectsList.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_effectsList.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "effectsList" )
			_effectsList.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "effectsList" )
			return _effectsList.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Retrieve", "PF_Core::EnableSCEffect", "EnableSCEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xA0626B00)]
[UseTypeName("EFFT")]
public class EnableSCEffect : EffectBase
{
	private UndoRedoDBPtr<EnableSCEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<EnableSCEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _nameStart;
	private UndoRedo<string> _nameStop;
	private UndoRedo<EnableSCEffectMode> _mode;
	private UndoRedo<bool> _enable;

	[Description( "ComponentId or EventName used then effect start" )]
	public string nameStart { get { return _nameStart.Get(); } set { _nameStart.Set( value ); } }

	[Description( "ComponentId or EventName used then effect stop" )]
	public string nameStop { get { return _nameStop.Get(); } set { _nameStop.Set( value ); } }

	public EnableSCEffectMode mode { get { return _mode.Get(); } set { _mode.Set( value ); } }

	public bool enable { get { return _enable.Get(); } set { _enable.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EnableSCEffect>(owner);
		_nameStart = new UndoRedo<string>( owner, string.Empty );
		_nameStop = new UndoRedo<string>( owner, string.Empty );
		_mode = new UndoRedo<EnableSCEffectMode>( owner, EnableSCEffectMode.ComponentId );
		_enable = new UndoRedo<bool>( owner, true );
		___parent.Changed += FireChangedEvent;
		_nameStart.Changed += FireChangedEvent;
		_nameStop.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		_enable.Changed += FireChangedEvent;
	}

	public EnableSCEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( EnableSCEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EnableSCEffect" );
		nameStart = source.nameStart;
		nameStop = source.nameStop;
		mode = source.mode;
		enable = source.enable;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EnableSCEffect source = _source as EnableSCEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EnableSCEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EnableSCEffect newParent = rawParent == null ? null : rawParent.Get<EnableSCEffect>();
		if ( newParent == null && _newParent is EnableSCEffect )
			newParent = _newParent as EnableSCEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_nameStart.SetParent( newParent == null ? null : newParent._nameStart );
		_nameStop.SetParent( newParent == null ? null : newParent._nameStop );
		_mode.SetParent( newParent == null ? null : newParent._mode );
		_enable.SetParent( newParent == null ? null : newParent._enable );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_nameStart.Reset();
		_nameStop.Reset();
		_mode.Reset();
		_enable.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_nameStart.IsDerivedFromParent()
			&& _nameStop.IsDerivedFromParent()
			&& _mode.IsDerivedFromParent()
			&& _enable.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "nameStart" )
			_nameStart.Reset();
		else if ( fieldName == "nameStop" )
			_nameStop.Reset();
		else if ( fieldName == "mode" )
			_mode.Reset();
		else if ( fieldName == "enable" )
			_enable.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "nameStart" )
			return _nameStart.IsDerivedFromParent();
		if ( fieldName == "nameStop" )
			return _nameStop.IsDerivedFromParent();
		if ( fieldName == "mode" )
			return _mode.IsDerivedFromParent();
		if ( fieldName == "enable" )
			return _enable.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Retrieve", "PF_Core::GhostEffect", "GhostEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xA06B93C0)]
[UseTypeName("EFFT")]
public class GhostEffect : EffectBase
{
	private UndoRedoDBPtr<GhostEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<GhostEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<GhostEffect>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public GhostEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( GhostEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for GhostEffect" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		GhostEffect source = _source as GhostEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for GhostEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		GhostEffect newParent = rawParent == null ? null : rawParent.Get<GhostEffect>();
		if ( newParent == null && _newParent is GhostEffect )
			newParent = _newParent as GhostEffect;
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

[FactoryImpl("Retrieve", "PF_Core::LightningEffect", "LightningEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xA0629380)]
[UseTypeName("EFFT")]
public class LightningEffect : EffectBase
{
	private UndoRedoDBPtr<LightningEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<LightningEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<DBLightningSceneComponent> _component;
	private UndoRedo<bool> _controlledVisibility;

	[Description( "Associated scene component" )]
	public DBPtr<DBLightningSceneComponent> component { get { return _component.Get(); } set { _component.Set( value ); } }

	[Description( "Lightning is visible iff at least one object attached to is visible?" )]
	public bool controlledVisibility { get { return _controlledVisibility.Get(); } set { _controlledVisibility.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<LightningEffect>(owner);
		_component = new UndoRedoDBPtr<DBLightningSceneComponent>( owner );
		_controlledVisibility = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_component.Changed += FireChangedEvent;
		_controlledVisibility.Changed += FireChangedEvent;
	}

	public LightningEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( LightningEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for LightningEffect" );
		component = source.component;
		controlledVisibility = source.controlledVisibility;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		LightningEffect source = _source as LightningEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for LightningEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		LightningEffect newParent = rawParent == null ? null : rawParent.Get<LightningEffect>();
		if ( newParent == null && _newParent is LightningEffect )
			newParent = _newParent as LightningEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_component.SetParent( newParent == null ? null : newParent._component );
		_controlledVisibility.SetParent( newParent == null ? null : newParent._controlledVisibility );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_component.Reset();
		_controlledVisibility.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_component.IsDerivedFromParent()
			&& _controlledVisibility.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "component" )
			_component.Reset();
		else if ( fieldName == "controlledVisibility" )
			_controlledVisibility.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "component" )
			return _component.IsDerivedFromParent();
		if ( fieldName == "controlledVisibility" )
			return _controlledVisibility.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "PF_Core::ParticleSceneComponentWithEffect", "ParticleSceneComponentWithEffect.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0xA065DB40)]
[UseTypeName("PSCE")]
public class ParticleSceneComponentWithEffect : DBParticleSceneComponent
{
	private UndoRedoDBPtr<ParticleSceneComponentWithEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<ParticleSceneComponentWithEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BasicEffectStandalone> _effect;

	public DBPtr<BasicEffectStandalone> effect { get { return _effect.Get(); } set { _effect.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ParticleSceneComponentWithEffect>(owner);
		_effect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		___parent.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
	}

	public ParticleSceneComponentWithEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( ParticleSceneComponentWithEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ParticleSceneComponentWithEffect" );
		effect = source.effect;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ParticleSceneComponentWithEffect source = _source as ParticleSceneComponentWithEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ParticleSceneComponentWithEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ParticleSceneComponentWithEffect newParent = rawParent == null ? null : rawParent.Get<ParticleSceneComponentWithEffect>();
		if ( newParent == null && _newParent is ParticleSceneComponentWithEffect )
			newParent = _newParent as ParticleSceneComponentWithEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_effect.SetParent( newParent == null ? null : newParent._effect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_effect.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_effect.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "effect" )
			_effect.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "effect" )
			return _effect.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class CircleRandomizer : PositionRandomizer
{
	private UndoRedoDBPtr<CircleRandomizer> ___parent;
	[HideInOutliner]
	public new DBPtr<CircleRandomizer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _radius;

	public float radius { get { return _radius.Get(); } set { _radius.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<CircleRandomizer>(owner);
		_radius = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_radius.Changed += FireChangedEvent;
	}

	public CircleRandomizer()
	{
		Initialize( this );
	}
	private void AssignSelf( CircleRandomizer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for CircleRandomizer" );
		radius = source.radius;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		CircleRandomizer source = _source as CircleRandomizer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for CircleRandomizer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		CircleRandomizer newParent = rawParent == null ? null : rawParent.Get<CircleRandomizer>();
		if ( newParent == null && _newParent is CircleRandomizer )
			newParent = _newParent as CircleRandomizer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_radius.SetParent( newParent == null ? null : newParent._radius );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_radius.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_radius.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "radius" )
			_radius.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "radius" )
			return _radius.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[TypeId(0xA06C5B40)]
[UseTypeName("PFXP")]
public class PostFXParams : DBResource
{
	private UndoRedoDBPtr<PostFXParams> ___parent;
	[HideInOutliner]
	public new DBPtr<PostFXParams> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<FullScreenFXParams> _fullScreenFXParams;
	private UndoRedo<float> _mipMapLodBias;

	[EnumArray(typeof(ENatureType))]
	public libdb.IChangeableList<FullScreenFXParams> fullScreenFXParams { get { return _fullScreenFXParams; } set { _fullScreenFXParams.Assign( value ); } }

	public float mipMapLodBias { get { return _mipMapLodBias.Get(); } set { _mipMapLodBias.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PostFXParams>(owner);
		_fullScreenFXParams = new UndoRedoAssignableList<FullScreenFXParams>( owner, typeof( ENatureType ) );
		_mipMapLodBias = new UndoRedo<float>( owner, 0.0f );
		___parent.Changed += FireChangedEvent;
		_fullScreenFXParams.Changed += FireChangedEvent;
		_mipMapLodBias.Changed += FireChangedEvent;
	}

	public PostFXParams()
	{
		Initialize( this );
	}
	private void AssignSelf( PostFXParams source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PostFXParams" );
		fullScreenFXParams = source.fullScreenFXParams;
		mipMapLodBias = source.mipMapLodBias;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PostFXParams source = _source as PostFXParams;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PostFXParams" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PostFXParams newParent = rawParent == null ? null : rawParent.Get<PostFXParams>();
		if ( newParent == null && _newParent is PostFXParams )
			newParent = _newParent as PostFXParams;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_fullScreenFXParams.SetParent( newParent == null ? null : newParent._fullScreenFXParams );
		_mipMapLodBias.SetParent( newParent == null ? null : newParent._mipMapLodBias );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_fullScreenFXParams.Reset();
		_mipMapLodBias.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_fullScreenFXParams.IsDerivedFromParent()
			&& _mipMapLodBias.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "fullScreenFXParams" )
			_fullScreenFXParams.Reset();
		else if ( fieldName == "mipMapLodBias" )
			_mipMapLodBias.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "fullScreenFXParams" )
			return _fullScreenFXParams.IsDerivedFromParent();
		if ( fieldName == "mipMapLodBias" )
			return _mipMapLodBias.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

public class RectangleRandomizer : PositionRandomizer
{
	private UndoRedoDBPtr<RectangleRandomizer> ___parent;
	[HideInOutliner]
	public new DBPtr<RectangleRandomizer> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private Vec2 _min;
	private Vec2 _max;

	public Vec2 min { get { return _min; } set { _min.Assign( value ); } }

	public Vec2 max { get { return _max; } set { _max.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RectangleRandomizer>(owner);
		_min = new Vec2( owner );
		_max = new Vec2( owner );
		___parent.Changed += FireChangedEvent;
		_min.Changed += FireChangedEvent;
		_max.Changed += FireChangedEvent;
	}

	public RectangleRandomizer()
	{
		Initialize( this );
	}
	private void AssignSelf( RectangleRandomizer source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RectangleRandomizer" );
		min = source.min;
		max = source.max;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RectangleRandomizer source = _source as RectangleRandomizer;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RectangleRandomizer" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RectangleRandomizer newParent = rawParent == null ? null : rawParent.Get<RectangleRandomizer>();
		if ( newParent == null && _newParent is RectangleRandomizer )
			newParent = _newParent as RectangleRandomizer;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_min.SetParent( newParent == null ? null : newParent._min );
		_max.SetParent( newParent == null ? null : newParent._max );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_min.Reset();
		_max.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_min.IsDerivedFromParent()
			&& _max.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "min" )
			_min.Reset();
		else if ( fieldName == "max" )
			_max.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "min" )
			return _min.IsDerivedFromParent();
		if ( fieldName == "max" )
			return _max.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(3)]
[FactoryImpl("Retrieve", "PF_Core::ScaleColorEffect", "ScaleColorEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xA06253C4)]
[UseTypeName("EFFT")]
public class ScaleColorEffect : EffectBase
{
	private UndoRedoDBPtr<ScaleColorEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<ScaleColorEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _scale;
	private HDRColor _colorMul;
	private HDRColor _colorAdd;
	private UndoRedo<BlendMode> _blendMode;
	private AnimatedFloat _scaleIn;
	private AnimatedFloat _scaleOut;
	private UndoRedo<float> _fadeInTime;
	private UndoRedo<float> _fadeOutTime;
	private UndoRedo<bool> _fullRecolor;

	public float scale { get { return _scale.Get(); } set { _scale.Set( value ); } }

	public HDRColor colorMul { get { return _colorMul; } set { _colorMul.Assign( value ); } }

	public HDRColor colorAdd { get { return _colorAdd; } set { _colorAdd.Assign( value ); } }

	public BlendMode blendMode { get { return _blendMode.Get(); } set { _blendMode.Set( value ); } }

	public AnimatedFloat scaleIn { get { return _scaleIn; } set { _scaleIn.Assign( value ); } }

	public AnimatedFloat scaleOut { get { return _scaleOut; } set { _scaleOut.Assign( value ); } }

	public float fadeInTime { get { return _fadeInTime.Get(); } set { _fadeInTime.Set( value ); } }

	public float fadeOutTime { get { return _fadeOutTime.Get(); } set { _fadeOutTime.Set( value ); } }

	public bool fullRecolor { get { return _fullRecolor.Get(); } set { _fullRecolor.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<ScaleColorEffect>(owner);
		_scale = new UndoRedo<float>( owner, 1.0f );
		HDRColor __colorMul = new HDRColor(); // Construct default object for colorMul
		__colorMul.R = 1.0f;
		__colorMul.G = 1.0f;
		__colorMul.B = 1.0f;
		_colorMul = new HDRColor( owner, __colorMul );
		HDRColor __colorAdd = new HDRColor(); // Construct default object for colorAdd
		__colorAdd.A = 0.0f;
		_colorAdd = new HDRColor( owner, __colorAdd );
		_blendMode = new UndoRedo<BlendMode>( owner, BlendMode.LerpByAlpha );
		_scaleIn = new AnimatedFloat( owner, 1.0f );
		_scaleOut = new AnimatedFloat( owner, 1.0f );
		_fadeInTime = new UndoRedo<float>( owner, 1.0f );
		_fadeOutTime = new UndoRedo<float>( owner, 1.0f );
		_fullRecolor = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
		_colorMul.Changed += FireChangedEvent;
		_colorAdd.Changed += FireChangedEvent;
		_blendMode.Changed += FireChangedEvent;
		_scaleIn.Changed += FireChangedEvent;
		_scaleOut.Changed += FireChangedEvent;
		_fadeInTime.Changed += FireChangedEvent;
		_fadeOutTime.Changed += FireChangedEvent;
		_fullRecolor.Changed += FireChangedEvent;
	}

	public ScaleColorEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( ScaleColorEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for ScaleColorEffect" );
		scale = source.scale;
		colorMul = source.colorMul;
		colorAdd = source.colorAdd;
		blendMode = source.blendMode;
		scaleIn = source.scaleIn;
		scaleOut = source.scaleOut;
		fadeInTime = source.fadeInTime;
		fadeOutTime = source.fadeOutTime;
		fullRecolor = source.fullRecolor;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		ScaleColorEffect source = _source as ScaleColorEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for ScaleColorEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		ScaleColorEffect newParent = rawParent == null ? null : rawParent.Get<ScaleColorEffect>();
		if ( newParent == null && _newParent is ScaleColorEffect )
			newParent = _newParent as ScaleColorEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_scale.SetParent( newParent == null ? null : newParent._scale );
		_colorMul.SetParent( newParent == null ? null : newParent._colorMul );
		_colorAdd.SetParent( newParent == null ? null : newParent._colorAdd );
		_blendMode.SetParent( newParent == null ? null : newParent._blendMode );
		_scaleIn.SetParent( newParent == null ? null : newParent._scaleIn );
		_scaleOut.SetParent( newParent == null ? null : newParent._scaleOut );
		_fadeInTime.SetParent( newParent == null ? null : newParent._fadeInTime );
		_fadeOutTime.SetParent( newParent == null ? null : newParent._fadeOutTime );
		_fullRecolor.SetParent( newParent == null ? null : newParent._fullRecolor );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_scale.Reset();
		_colorMul.Reset();
		_colorAdd.Reset();
		_blendMode.Reset();
		_scaleIn.Reset();
		_scaleOut.Reset();
		_fadeInTime.Reset();
		_fadeOutTime.Reset();
		_fullRecolor.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_scale.IsDerivedFromParent()
			&& _colorMul.IsDerivedFromParent()
			&& _colorAdd.IsDerivedFromParent()
			&& _blendMode.IsDerivedFromParent()
			&& _scaleIn.IsDerivedFromParent()
			&& _scaleOut.IsDerivedFromParent()
			&& _fadeInTime.IsDerivedFromParent()
			&& _fadeOutTime.IsDerivedFromParent()
			&& _fullRecolor.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "scale" )
			_scale.Reset();
		else if ( fieldName == "colorMul" )
			_colorMul.Reset();
		else if ( fieldName == "colorAdd" )
			_colorAdd.Reset();
		else if ( fieldName == "blendMode" )
			_blendMode.Reset();
		else if ( fieldName == "scaleIn" )
			_scaleIn.Reset();
		else if ( fieldName == "scaleOut" )
			_scaleOut.Reset();
		else if ( fieldName == "fadeInTime" )
			_fadeInTime.Reset();
		else if ( fieldName == "fadeOutTime" )
			_fadeOutTime.Reset();
		else if ( fieldName == "fullRecolor" )
			_fullRecolor.Reset();
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
		if ( fieldName == "colorMul" )
			return _colorMul.IsDerivedFromParent();
		if ( fieldName == "colorAdd" )
			return _colorAdd.IsDerivedFromParent();
		if ( fieldName == "blendMode" )
			return _blendMode.IsDerivedFromParent();
		if ( fieldName == "scaleIn" )
			return _scaleIn.IsDerivedFromParent();
		if ( fieldName == "scaleOut" )
			return _scaleOut.IsDerivedFromParent();
		if ( fieldName == "fadeInTime" )
			return _fadeInTime.IsDerivedFromParent();
		if ( fieldName == "fadeOutTime" )
			return _fadeOutTime.IsDerivedFromParent();
		if ( fieldName == "fullRecolor" )
			return _fullRecolor.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Create", "PF_Core::SpringSceneComponent", "SpringSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0xA071EBC0)]
[UseTypeName("SPSC")]
public class SpringSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<SpringSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<SpringSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private SpringParamDynamics _posDynamics;
	private SpringParamDynamics _rotDynamics;
	private SpringParamDynamics _scaleDynamics;

	[Description( "Параметры динамики позиции" )]
	public SpringParamDynamics posDynamics { get { return _posDynamics; } set { _posDynamics.Assign( value ); } }

	[Description( "Параметры динамики поворота" )]
	public SpringParamDynamics rotDynamics { get { return _rotDynamics; } set { _rotDynamics.Assign( value ); } }

	[Description( "Параметры динамики масштаба" )]
	public SpringParamDynamics scaleDynamics { get { return _scaleDynamics; } set { _scaleDynamics.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SpringSceneComponent>(owner);
		_posDynamics = new SpringParamDynamics( owner );
		_rotDynamics = new SpringParamDynamics( owner );
		_scaleDynamics = new SpringParamDynamics( owner );
		___parent.Changed += FireChangedEvent;
		_posDynamics.Changed += FireChangedEvent;
		_rotDynamics.Changed += FireChangedEvent;
		_scaleDynamics.Changed += FireChangedEvent;
	}

	public SpringSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( SpringSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SpringSceneComponent" );
		posDynamics = source.posDynamics;
		rotDynamics = source.rotDynamics;
		scaleDynamics = source.scaleDynamics;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SpringSceneComponent source = _source as SpringSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SpringSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SpringSceneComponent newParent = rawParent == null ? null : rawParent.Get<SpringSceneComponent>();
		if ( newParent == null && _newParent is SpringSceneComponent )
			newParent = _newParent as SpringSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_posDynamics.SetParent( newParent == null ? null : newParent._posDynamics );
		_rotDynamics.SetParent( newParent == null ? null : newParent._rotDynamics );
		_scaleDynamics.SetParent( newParent == null ? null : newParent._scaleDynamics );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_posDynamics.Reset();
		_rotDynamics.Reset();
		_scaleDynamics.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_posDynamics.IsDerivedFromParent()
			&& _rotDynamics.IsDerivedFromParent()
			&& _scaleDynamics.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "posDynamics" )
			_posDynamics.Reset();
		else if ( fieldName == "rotDynamics" )
			_rotDynamics.Reset();
		else if ( fieldName == "scaleDynamics" )
			_scaleDynamics.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "posDynamics" )
			return _posDynamics.IsDerivedFromParent();
		if ( fieldName == "rotDynamics" )
			return _rotDynamics.IsDerivedFromParent();
		if ( fieldName == "scaleDynamics" )
			return _scaleDynamics.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Load", "PF_Core::AnimatedTexture", "AnimatedTexture.h", CreateFunction = "PF_Core::LoadAnimatedTexture")]
[FactoryImpl("LoadInPool", "PF_Core::AnimatedTexture", "AnimatedTexture.h", CreateFunction = "PF_Core::LoadAnimatedTextureIntoPool")]
[UseTypeName("TXAN")]
public class TextureAnimated : Texture
{
	private UndoRedoDBPtr<TextureAnimated> ___parent;
	[HideInOutliner]
	public new DBPtr<TextureAnimated> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<int> _animCount;
	private UndoRedo<float> _animSpeed;

	public int animCount { get { return _animCount.Get(); } set { _animCount.Set( value ); } }

	public float animSpeed { get { return _animSpeed.Get(); } set { _animSpeed.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TextureAnimated>(owner);
		_animCount = new UndoRedo<int>( owner, 1 );
		_animSpeed = new UndoRedo<float>( owner, 10.0f );
		___parent.Changed += FireChangedEvent;
		_animCount.Changed += FireChangedEvent;
		_animSpeed.Changed += FireChangedEvent;
	}

	public TextureAnimated()
	{
		Initialize( this );
	}
	private void AssignSelf( TextureAnimated source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TextureAnimated" );
		animCount = source.animCount;
		animSpeed = source.animSpeed;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TextureAnimated source = _source as TextureAnimated;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TextureAnimated" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TextureAnimated newParent = rawParent == null ? null : rawParent.Get<TextureAnimated>();
		if ( newParent == null && _newParent is TextureAnimated )
			newParent = _newParent as TextureAnimated;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_animCount.SetParent( newParent == null ? null : newParent._animCount );
		_animSpeed.SetParent( newParent == null ? null : newParent._animSpeed );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_animCount.Reset();
		_animSpeed.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_animCount.IsDerivedFromParent()
			&& _animSpeed.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "animCount" )
			_animCount.Reset();
		else if ( fieldName == "animSpeed" )
			_animSpeed.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "animCount" )
			return _animCount.IsDerivedFromParent();
		if ( fieldName == "animSpeed" )
			return _animSpeed.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[FactoryImpl("Load", "PF_Core::RecolorableTexture", "RecolorableTexture.h", CreateFunction = "PF_Core::LoadRecolorableTexture")]
[FactoryImpl("LoadInPool", "PF_Core::RecolorableTexture", "RecolorableTexture.h", CreateFunction = "PF_Core::LoadRecolorableTextureInPool")]
[UseTypeName("TXRC")]
public class TextureRecolorable : TextureBase
{
	private UndoRedoDBPtr<TextureRecolorable> ___parent;
	[HideInOutliner]
	public new DBPtr<TextureRecolorable> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Texture> _main;
	private UndoRedoDBPtr<Texture> _mask;
	private HDRColor _baseRGB;

	public DBPtr<Texture> main { get { return _main.Get(); } set { _main.Set( value ); } }

	public DBPtr<Texture> mask { get { return _mask.Get(); } set { _mask.Set( value ); } }

	[Description( "Color that is applied by default (no recolor by default when A=0)" )]
	public HDRColor baseRGB { get { return _baseRGB; } set { _baseRGB.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TextureRecolorable>(owner);
		_main = new UndoRedoDBPtr<Texture>( owner );
		_mask = new UndoRedoDBPtr<Texture>( owner );
		HDRColor __baseRGB = new HDRColor(); // Construct default object for baseRGB
		__baseRGB.A = 0.0f;
		_baseRGB = new HDRColor( owner, __baseRGB );
		___parent.Changed += FireChangedEvent;
		_main.Changed += FireChangedEvent;
		_mask.Changed += FireChangedEvent;
		_baseRGB.Changed += FireChangedEvent;
	}

	public TextureRecolorable()
	{
		Initialize( this );
	}
	private void AssignSelf( TextureRecolorable source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TextureRecolorable" );
		main = source.main;
		mask = source.mask;
		baseRGB = source.baseRGB;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TextureRecolorable source = _source as TextureRecolorable;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TextureRecolorable" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TextureRecolorable newParent = rawParent == null ? null : rawParent.Get<TextureRecolorable>();
		if ( newParent == null && _newParent is TextureRecolorable )
			newParent = _newParent as TextureRecolorable;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_main.SetParent( newParent == null ? null : newParent._main );
		_mask.SetParent( newParent == null ? null : newParent._mask );
		_baseRGB.SetParent( newParent == null ? null : newParent._baseRGB );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_main.Reset();
		_mask.Reset();
		_baseRGB.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_main.IsDerivedFromParent()
			&& _mask.IsDerivedFromParent()
			&& _baseRGB.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "main" )
			_main.Reset();
		else if ( fieldName == "mask" )
			_mask.Reset();
		else if ( fieldName == "baseRGB" )
			_baseRGB.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "main" )
			return _main.IsDerivedFromParent();
		if ( fieldName == "mask" )
			return _mask.IsDerivedFromParent();
		if ( fieldName == "baseRGB" )
			return _baseRGB.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[UseTypeName("TRAC")]
public class Trace : DBResource
{
	private UndoRedoDBPtr<Trace> ___parent;
	[HideInOutliner]
	public new DBPtr<Trace> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<EffectSelector> _waterTrace;
	private UndoRedoAssignableList<DBPtr<EffectSelector>> _terrainTrace;

	public DBPtr<EffectSelector> waterTrace { get { return _waterTrace.Get(); } set { _waterTrace.Set( value ); } }

	[EnumArray(typeof(ENatureType))]
	public libdb.IChangeableList<DBPtr<EffectSelector>> terrainTrace { get { return _terrainTrace; } set { _terrainTrace.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<Trace>(owner);
		_waterTrace = new UndoRedoDBPtr<EffectSelector>( owner );
		_terrainTrace = new UndoRedoAssignableList<DBPtr<EffectSelector>>( owner, typeof( ENatureType ) );
		___parent.Changed += FireChangedEvent;
		_waterTrace.Changed += FireChangedEvent;
		_terrainTrace.Changed += FireChangedEvent;
	}

	public Trace()
	{
		Initialize( this );
	}
	private void AssignSelf( Trace source )
	{
		DataBase.UndoRedoManager.Start( "Assign for Trace" );
		waterTrace = source.waterTrace;
		terrainTrace = source.terrainTrace;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		Trace source = _source as Trace;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Trace" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		Trace newParent = rawParent == null ? null : rawParent.Get<Trace>();
		if ( newParent == null && _newParent is Trace )
			newParent = _newParent as Trace;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_waterTrace.SetParent( newParent == null ? null : newParent._waterTrace );
		_terrainTrace.SetParent( newParent == null ? null : newParent._terrainTrace );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_waterTrace.Reset();
		_terrainTrace.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_waterTrace.IsDerivedFromParent()
			&& _terrainTrace.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "waterTrace" )
			_waterTrace.Reset();
		else if ( fieldName == "terrainTrace" )
			_terrainTrace.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "waterTrace" )
			return _waterTrace.IsDerivedFromParent();
		if ( fieldName == "terrainTrace" )
			return _terrainTrace.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Create", "PF_Core::TraceGenSceneComponent", "TraceGenSceneComponent.h", CreateFunction = "NScene::CreateSceneComponent<>")]
[TypeId(0xA065B300)]
[UseTypeName("TGSC")]
public class TraceGenSceneComponent : DBSceneComponent
{
	private UndoRedoDBPtr<TraceGenSceneComponent> ___parent;
	[HideInOutliner]
	public new DBPtr<TraceGenSceneComponent> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<Trace> _defaultTraces;
	private UndoRedo<string> _defaultLocatorName;
	private UndoRedoAssignableList<TraceInfo> _traceByAnim;

	public DBPtr<Trace> defaultTraces { get { return _defaultTraces.Get(); } set { _defaultTraces.Set( value ); } }

	public string defaultLocatorName { get { return _defaultLocatorName.Get(); } set { _defaultLocatorName.Set( value ); } }

	public libdb.IChangeableList<TraceInfo> traceByAnim { get { return _traceByAnim; } set { _traceByAnim.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<TraceGenSceneComponent>(owner);
		_defaultTraces = new UndoRedoDBPtr<Trace>( owner );
		_defaultLocatorName = new UndoRedo<string>( owner, string.Empty );
		_traceByAnim = new UndoRedoAssignableList<TraceInfo>( owner );
		___parent.Changed += FireChangedEvent;
		_defaultTraces.Changed += FireChangedEvent;
		_defaultLocatorName.Changed += FireChangedEvent;
		_traceByAnim.Changed += FireChangedEvent;
	}

	public TraceGenSceneComponent()
	{
		Initialize( this );
	}
	private void AssignSelf( TraceGenSceneComponent source )
	{
		DataBase.UndoRedoManager.Start( "Assign for TraceGenSceneComponent" );
		defaultTraces = source.defaultTraces;
		defaultLocatorName = source.defaultLocatorName;
		traceByAnim = source.traceByAnim;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		TraceGenSceneComponent source = _source as TraceGenSceneComponent;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for TraceGenSceneComponent" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		TraceGenSceneComponent newParent = rawParent == null ? null : rawParent.Get<TraceGenSceneComponent>();
		if ( newParent == null && _newParent is TraceGenSceneComponent )
			newParent = _newParent as TraceGenSceneComponent;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_defaultTraces.SetParent( newParent == null ? null : newParent._defaultTraces );
		_defaultLocatorName.SetParent( newParent == null ? null : newParent._defaultLocatorName );
		_traceByAnim.SetParent( newParent == null ? null : newParent._traceByAnim );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_defaultTraces.Reset();
		_defaultLocatorName.Reset();
		_traceByAnim.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_defaultTraces.IsDerivedFromParent()
			&& _defaultLocatorName.IsDerivedFromParent()
			&& _traceByAnim.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "defaultTraces" )
			_defaultTraces.Reset();
		else if ( fieldName == "defaultLocatorName" )
			_defaultLocatorName.Reset();
		else if ( fieldName == "traceByAnim" )
			_traceByAnim.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "defaultTraces" )
			return _defaultTraces.IsDerivedFromParent();
		if ( fieldName == "defaultLocatorName" )
			return _defaultLocatorName.IsDerivedFromParent();
		if ( fieldName == "traceByAnim" )
			return _traceByAnim.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
