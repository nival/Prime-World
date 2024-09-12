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
public enum EAnimSetID
{
	Creep = 0,
	Hero = 1,
	Priestess = 2,
	SittingPriestess = 3,
	Critter = 4,
};

public enum EAuraEffectType
{
	Ally = 0,
	Enemy = 1,
	Mixed = 2,
};

public enum EFemaleMaleAssistEffectSate
{
	HeroToMiddle = 0,
	MiddleToHero = 1,
	SingleAtMidle = 2,
	StartFlash = 3,
	Destroy = 4,
};

public enum EWinLose
{
	Win = 0,
	Lose = 1,
};

public class AnimSets : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AnimSets __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedoAssignableList<DBPtr<AnimSet>> _sets;

	[EnumArray(typeof(EAnimSetID))]
	public libdb.IChangeableList<DBPtr<AnimSet>> sets { get { return _sets; } set { _sets.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_sets = new UndoRedoAssignableList<DBPtr<AnimSet>>( owner, typeof( EAnimSetID ) );
		_sets.Changed += FireChangedEvent;
	}

	public AnimSets()
	{
		Initialize( GetOwner() );
	}

	public AnimSets( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AnimSets( DBResource owner, AnimSets source )
		: this(owner, source, true){}

	protected AnimSets( DBResource owner, AnimSets source, bool fireEvent )
	{
		_sets = new UndoRedoAssignableList<DBPtr<AnimSet>>( owner, typeof( EAnimSetID ) );
		_sets.Assign( source.sets );
		_sets.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AnimSets source = _source as AnimSets;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimSets" );
		sets = source.sets;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AnimSets newParent = _newParent as AnimSets;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_sets.SetParent( newParent == null ? null : newParent._sets );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_sets.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_sets.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "sets" )
			_sets.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "sets" )
			return _sets.IsDerivedFromParent();
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

public class AuraEffects : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private AuraEffects __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _minimalEffectIntencity;
	private UndoRedo<int> _maximalAuraCount;
	private UndoRedoAssignableList<DBPtr<BasicEffectAttached>> _auraEffects;

	[Description( "Минимальная интенсивность ауры" )]
	public float minimalEffectIntencity { get { return _minimalEffectIntencity.Get(); } set { _minimalEffectIntencity.Set( value ); } }

	[Description( "Количество аур, на котором достигается интенсивность 1" )]
	public int maximalAuraCount { get { return _maximalAuraCount.Get(); } set { _maximalAuraCount.Set( value ); } }

	[Description( "Эффекты для трех различных типов аур" )]
	[EnumArray(typeof(EAuraEffectType))]
	public libdb.IChangeableList<DBPtr<BasicEffectAttached>> auraEffects { get { return _auraEffects; } set { _auraEffects.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_minimalEffectIntencity = new UndoRedo<float>( owner, 0.5f );
		_maximalAuraCount = new UndoRedo<int>( owner, 3 );
		_auraEffects = new UndoRedoAssignableList<DBPtr<BasicEffectAttached>>( owner, typeof( EAuraEffectType ) );
		_minimalEffectIntencity.Changed += FireChangedEvent;
		_maximalAuraCount.Changed += FireChangedEvent;
		_auraEffects.Changed += FireChangedEvent;
	}

	public AuraEffects()
	{
		Initialize( GetOwner() );
	}

	public AuraEffects( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public AuraEffects( DBResource owner, AuraEffects source )
		: this(owner, source, true){}

	protected AuraEffects( DBResource owner, AuraEffects source, bool fireEvent )
	{
		_minimalEffectIntencity = new UndoRedo<float>( owner, source.minimalEffectIntencity );
		_maximalAuraCount = new UndoRedo<int>( owner, source.maximalAuraCount );
		_auraEffects = new UndoRedoAssignableList<DBPtr<BasicEffectAttached>>( owner, typeof( EAuraEffectType ) );
		_auraEffects.Assign( source.auraEffects );
		_minimalEffectIntencity.Changed += FireChangedEvent;
		_maximalAuraCount.Changed += FireChangedEvent;
		_auraEffects.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		AuraEffects source = _source as AuraEffects;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AuraEffects" );
		minimalEffectIntencity = source.minimalEffectIntencity;
		maximalAuraCount = source.maximalAuraCount;
		auraEffects = source.auraEffects;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		AuraEffects newParent = _newParent as AuraEffects;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minimalEffectIntencity.SetParent( newParent == null ? null : newParent._minimalEffectIntencity );
		_maximalAuraCount.SetParent( newParent == null ? null : newParent._maximalAuraCount );
		_auraEffects.SetParent( newParent == null ? null : newParent._auraEffects );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minimalEffectIntencity.Reset();
		_maximalAuraCount.Reset();
		_auraEffects.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minimalEffectIntencity.IsDerivedFromParent()
			&& _maximalAuraCount.IsDerivedFromParent()
			&& _auraEffects.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minimalEffectIntencity" )
			_minimalEffectIntencity.Reset();
		else if ( fieldName == "maximalAuraCount" )
			_maximalAuraCount.Reset();
		else if ( fieldName == "auraEffects" )
			_auraEffects.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minimalEffectIntencity" )
			return _minimalEffectIntencity.IsDerivedFromParent();
		if ( fieldName == "maximalAuraCount" )
			return _maximalAuraCount.IsDerivedFromParent();
		if ( fieldName == "auraEffects" )
			return _auraEffects.IsDerivedFromParent();
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

public class EffectWithDelay : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private EffectWithDelay __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _deltaTime;
	private UndoRedoDBPtr<EffectBase> _effect;

	[Description( "Задержка перед запуском" )]
	public float deltaTime { get { return _deltaTime.Get(); } set { _deltaTime.Set( value ); } }

	[Description( "Описание эффекта" )]
	public DBPtr<EffectBase> effect { get { return _effect.Get(); } set { _effect.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_deltaTime = new UndoRedo<float>( owner, 0.0f );
		_effect = new UndoRedoDBPtr<EffectBase>( owner );
		_deltaTime.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
	}

	public EffectWithDelay()
	{
		Initialize( GetOwner() );
	}

	public EffectWithDelay( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public EffectWithDelay( DBResource owner, EffectWithDelay source )
		: this(owner, source, true){}

	protected EffectWithDelay( DBResource owner, EffectWithDelay source, bool fireEvent )
	{
		_deltaTime = new UndoRedo<float>( owner, source.deltaTime );
		_effect = new UndoRedoDBPtr<EffectBase>( owner, source.effect );
		_deltaTime.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		EffectWithDelay source = _source as EffectWithDelay;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectWithDelay" );
		deltaTime = source.deltaTime;
		effect = source.effect;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		EffectWithDelay newParent = _newParent as EffectWithDelay;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_deltaTime.SetParent( newParent == null ? null : newParent._deltaTime );
		_effect.SetParent( newParent == null ? null : newParent._effect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_deltaTime.Reset();
		_effect.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_deltaTime.IsDerivedFromParent()
			&& _effect.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "deltaTime" )
			_deltaTime.Reset();
		else if ( fieldName == "effect" )
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
		if ( fieldName == "deltaTime" )
			return _deltaTime.IsDerivedFromParent();
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

public class FemaleMaleAssistEffect : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FemaleMaleAssistEffect __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _minDistanceBetweenHeroes;
	private UndoRedo<float> _middlePosHeight;
	private UndoRedoAssignableList<EffectWithDelay> _effectsWithDelay;

	[Description( "Минимальная дистанция между героями для срабатывании эффекта" )]
	public float minDistanceBetweenHeroes { get { return _minDistanceBetweenHeroes.Get(); } set { _minDistanceBetweenHeroes.Set( value ); } }

	[Description( "Высота, относительно террейна, на которую будет смещён центр эффекта" )]
	public float middlePosHeight { get { return _middlePosHeight.Get(); } set { _middlePosHeight.Set( value ); } }

	[Description( "Воспроизводимые эффекты и относительная задержка перед из стартом" )]
	[EnumArray(typeof(EFemaleMaleAssistEffectSate))]
	public libdb.IChangeableList<EffectWithDelay> effectsWithDelay { get { return _effectsWithDelay; } set { _effectsWithDelay.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_minDistanceBetweenHeroes = new UndoRedo<float>( owner, 23.0f );
		_middlePosHeight = new UndoRedo<float>( owner, 4.0f );
		_effectsWithDelay = new UndoRedoAssignableList<EffectWithDelay>( owner, typeof( EFemaleMaleAssistEffectSate ) );
		_minDistanceBetweenHeroes.Changed += FireChangedEvent;
		_middlePosHeight.Changed += FireChangedEvent;
		_effectsWithDelay.Changed += FireChangedEvent;
	}

	public FemaleMaleAssistEffect()
	{
		Initialize( GetOwner() );
	}

	public FemaleMaleAssistEffect( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FemaleMaleAssistEffect( DBResource owner, FemaleMaleAssistEffect source )
		: this(owner, source, true){}

	protected FemaleMaleAssistEffect( DBResource owner, FemaleMaleAssistEffect source, bool fireEvent )
	{
		_minDistanceBetweenHeroes = new UndoRedo<float>( owner, source.minDistanceBetweenHeroes );
		_middlePosHeight = new UndoRedo<float>( owner, source.middlePosHeight );
		_effectsWithDelay = new UndoRedoAssignableList<EffectWithDelay>( owner, typeof( EFemaleMaleAssistEffectSate ) );
		_effectsWithDelay.Assign( source.effectsWithDelay );
		_minDistanceBetweenHeroes.Changed += FireChangedEvent;
		_middlePosHeight.Changed += FireChangedEvent;
		_effectsWithDelay.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FemaleMaleAssistEffect source = _source as FemaleMaleAssistEffect;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FemaleMaleAssistEffect" );
		minDistanceBetweenHeroes = source.minDistanceBetweenHeroes;
		middlePosHeight = source.middlePosHeight;
		effectsWithDelay = source.effectsWithDelay;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FemaleMaleAssistEffect newParent = _newParent as FemaleMaleAssistEffect;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_minDistanceBetweenHeroes.SetParent( newParent == null ? null : newParent._minDistanceBetweenHeroes );
		_middlePosHeight.SetParent( newParent == null ? null : newParent._middlePosHeight );
		_effectsWithDelay.SetParent( newParent == null ? null : newParent._effectsWithDelay );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_minDistanceBetweenHeroes.Reset();
		_middlePosHeight.Reset();
		_effectsWithDelay.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_minDistanceBetweenHeroes.IsDerivedFromParent()
			&& _middlePosHeight.IsDerivedFromParent()
			&& _effectsWithDelay.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "minDistanceBetweenHeroes" )
			_minDistanceBetweenHeroes.Reset();
		else if ( fieldName == "middlePosHeight" )
			_middlePosHeight.Reset();
		else if ( fieldName == "effectsWithDelay" )
			_effectsWithDelay.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "minDistanceBetweenHeroes" )
			return _minDistanceBetweenHeroes.IsDerivedFromParent();
		if ( fieldName == "middlePosHeight" )
			return _middlePosHeight.IsDerivedFromParent();
		if ( fieldName == "effectsWithDelay" )
			return _effectsWithDelay.IsDerivedFromParent();
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

public class WinLoseEffect : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private WinLoseEffect __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _cameraMovementTime;
	private ViewCamera _cameraPos;
	private UndoRedo<float> _effectDelay;
	private UndoRedoDBPtr<BasicEffectStandalone> _effect;

	[Description( "Время движения камеры к зданию (сек)" )]
	public float cameraMovementTime { get { return _cameraMovementTime.Get(); } set { _cameraMovementTime.Set( value ); } }

	[Description( "Позиция камеры относительно здания. Можно использовать поле anchor для горизонтального смещения" )]
	public ViewCamera cameraPos { get { return _cameraPos; } set { _cameraPos.Assign( value ); } }

	[Description( "Задержка перед стартом эффекта (сек)" )]
	public float effectDelay { get { return _effectDelay.Get(); } set { _effectDelay.Set( value ); } }

	[Description( "Сам эффект" )]
	public DBPtr<BasicEffectStandalone> effect { get { return _effect.Get(); } set { _effect.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_cameraMovementTime = new UndoRedo<float>( owner, 3.0f );
		_cameraPos = new ViewCamera( owner );
		_effectDelay = new UndoRedo<float>( owner, 3.0f );
		_effect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_cameraMovementTime.Changed += FireChangedEvent;
		_cameraPos.Changed += FireChangedEvent;
		_effectDelay.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
	}

	public WinLoseEffect()
	{
		Initialize( GetOwner() );
	}

	public WinLoseEffect( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public WinLoseEffect( DBResource owner, WinLoseEffect source )
		: this(owner, source, true){}

	protected WinLoseEffect( DBResource owner, WinLoseEffect source, bool fireEvent )
	{
		_cameraMovementTime = new UndoRedo<float>( owner, source.cameraMovementTime );
		_cameraPos = new ViewCamera( owner, source.cameraPos );
		_effectDelay = new UndoRedo<float>( owner, source.effectDelay );
		_effect = new UndoRedoDBPtr<BasicEffectStandalone>( owner, source.effect );
		_cameraMovementTime.Changed += FireChangedEvent;
		_cameraPos.Changed += FireChangedEvent;
		_effectDelay.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		WinLoseEffect source = _source as WinLoseEffect;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for WinLoseEffect" );
		cameraMovementTime = source.cameraMovementTime;
		cameraPos = source.cameraPos;
		effectDelay = source.effectDelay;
		effect = source.effect;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		WinLoseEffect newParent = _newParent as WinLoseEffect;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_cameraMovementTime.SetParent( newParent == null ? null : newParent._cameraMovementTime );
		_cameraPos.SetParent( newParent == null ? null : newParent._cameraPos );
		_effectDelay.SetParent( newParent == null ? null : newParent._effectDelay );
		_effect.SetParent( newParent == null ? null : newParent._effect );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_cameraMovementTime.Reset();
		_cameraPos.Reset();
		_effectDelay.Reset();
		_effect.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_cameraMovementTime.IsDerivedFromParent()
			&& _cameraPos.IsDerivedFromParent()
			&& _effectDelay.IsDerivedFromParent()
			&& _effect.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "cameraMovementTime" )
			_cameraMovementTime.Reset();
		else if ( fieldName == "cameraPos" )
			_cameraPos.Reset();
		else if ( fieldName == "effectDelay" )
			_effectDelay.Reset();
		else if ( fieldName == "effect" )
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
		if ( fieldName == "cameraMovementTime" )
			return _cameraMovementTime.IsDerivedFromParent();
		if ( fieldName == "cameraPos" )
			return _cameraPos.IsDerivedFromParent();
		if ( fieldName == "effectDelay" )
			return _effectDelay.IsDerivedFromParent();
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

[UseTypeName("ROOT")]
public class SessionAudioRoot : DBResource
{
	private UndoRedoDBPtr<SessionAudioRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionAudioRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionAudioRoot>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public SessionAudioRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionAudioRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionAudioRoot" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionAudioRoot source = _source as SessionAudioRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionAudioRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionAudioRoot newParent = rawParent == null ? null : rawParent.Get<SessionAudioRoot>();
		if ( newParent == null && _newParent is SessionAudioRoot )
			newParent = _newParent as SessionAudioRoot;
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

[UseTypeName("ROOT")]
public class SessionUIRoot : DBResource
{
	private UndoRedoDBPtr<SessionUIRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionUIRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<UnitCategories> _unitCategories;
	private UndoRedoDBPtr<UnitCategoriesParams> _unitCategoriesParams;

	public DBPtr<UnitCategories> unitCategories { get { return _unitCategories.Get(); } set { _unitCategories.Set( value ); } }

	public DBPtr<UnitCategoriesParams> unitCategoriesParams { get { return _unitCategoriesParams.Get(); } set { _unitCategoriesParams.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionUIRoot>(owner);
		_unitCategories = new UndoRedoDBPtr<UnitCategories>( owner );
		_unitCategoriesParams = new UndoRedoDBPtr<UnitCategoriesParams>( owner );
		___parent.Changed += FireChangedEvent;
		_unitCategories.Changed += FireChangedEvent;
		_unitCategoriesParams.Changed += FireChangedEvent;
	}

	public SessionUIRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionUIRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionUIRoot" );
		unitCategories = source.unitCategories;
		unitCategoriesParams = source.unitCategoriesParams;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionUIRoot source = _source as SessionUIRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionUIRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionUIRoot newParent = rawParent == null ? null : rawParent.Get<SessionUIRoot>();
		if ( newParent == null && _newParent is SessionUIRoot )
			newParent = _newParent as SessionUIRoot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_unitCategories.SetParent( newParent == null ? null : newParent._unitCategories );
		_unitCategoriesParams.SetParent( newParent == null ? null : newParent._unitCategoriesParams );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_unitCategories.Reset();
		_unitCategoriesParams.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_unitCategories.IsDerivedFromParent()
			&& _unitCategoriesParams.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "unitCategories" )
			_unitCategories.Reset();
		else if ( fieldName == "unitCategoriesParams" )
			_unitCategoriesParams.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "unitCategories" )
			return _unitCategories.IsDerivedFromParent();
		if ( fieldName == "unitCategoriesParams" )
			return _unitCategoriesParams.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
[UseTypeName("ROOT")]
public class SessionVisualRoot : DBResource
{
	private UndoRedoDBPtr<SessionVisualRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionVisualRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<EmoteSettings> _emoteSettings;
	private UndoRedoDBPtr<TeamsColoringScheme> _teamColoringScheme;
	private UndoRedoDBPtr<EffectsPool> _effects;
	private UndoRedoAssignableList<DBPtr<BasicEffectAttached>> _selfAuraEffects;
	private AnimSets _animSets;
	private AuraEffects _auraEffects;
	private UndoRedoDBPtr<UIEventsCustom> _uiEvents;
	private UndoRedoAssignableList<DBPtr<AdventureCameraSettings>> _cameras;
	private UndoRedoAssignableList<WinLoseEffect> _winLoseEffects;
	private FemaleMaleAssistEffect _femaleMaleAssistEffect;
	private UndoRedo<float> _wallTargetZoneWidth;

	public DBPtr<EmoteSettings> emoteSettings { get { return _emoteSettings.Get(); } set { _emoteSettings.Set( value ); } }

	public DBPtr<TeamsColoringScheme> teamColoringScheme { get { return _teamColoringScheme.Get(); } set { _teamColoringScheme.Set( value ); } }

	public DBPtr<EffectsPool> effects { get { return _effects.Get(); } set { _effects.Set( value ); } }

	[EnumArray(typeof(EAuraEffectType))]
	public libdb.IChangeableList<DBPtr<BasicEffectAttached>> selfAuraEffects { get { return _selfAuraEffects; } set { _selfAuraEffects.Assign( value ); } }

	public AnimSets animSets { get { return _animSets; } set { _animSets.Assign( value ); } }

	public AuraEffects auraEffects { get { return _auraEffects; } set { _auraEffects.Assign( value ); } }

	public DBPtr<UIEventsCustom> uiEvents { get { return _uiEvents.Get(); } set { _uiEvents.Set( value ); } }

	public libdb.IChangeableList<DBPtr<AdventureCameraSettings>> cameras { get { return _cameras; } set { _cameras.Assign( value ); } }

	[Description( "Эффекты и перемещения камеры после победы/поражения" )]
	[EnumArray(typeof(EWinLose))]
	public libdb.IChangeableList<WinLoseEffect> winLoseEffects { get { return _winLoseEffects; } set { _winLoseEffects.Assign( value ); } }

	[Description( "Эффект при совместных гетеросексуальных убийствах и разрушениях" )]
	public FemaleMaleAssistEffect femaleMaleAssistEffect { get { return _femaleMaleAssistEffect; } set { _femaleMaleAssistEffect.Assign( value ); } }

	[Description( "Ширина таргетзоны типа Стена" )]
	public float wallTargetZoneWidth { get { return _wallTargetZoneWidth.Get(); } set { _wallTargetZoneWidth.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionVisualRoot>(owner);
		_emoteSettings = new UndoRedoDBPtr<EmoteSettings>( owner );
		_teamColoringScheme = new UndoRedoDBPtr<TeamsColoringScheme>( owner );
		_effects = new UndoRedoDBPtr<EffectsPool>( owner );
		_selfAuraEffects = new UndoRedoAssignableList<DBPtr<BasicEffectAttached>>( owner, typeof( EAuraEffectType ) );
		_animSets = new AnimSets( owner );
		_auraEffects = new AuraEffects( owner );
		_uiEvents = new UndoRedoDBPtr<UIEventsCustom>( owner );
		_cameras = new UndoRedoAssignableList<DBPtr<AdventureCameraSettings>>( owner );
		_winLoseEffects = new UndoRedoAssignableList<WinLoseEffect>( owner, typeof( EWinLose ) );
		_femaleMaleAssistEffect = new FemaleMaleAssistEffect( owner );
		_wallTargetZoneWidth = new UndoRedo<float>( owner, 1.0f );
		___parent.Changed += FireChangedEvent;
		_emoteSettings.Changed += FireChangedEvent;
		_teamColoringScheme.Changed += FireChangedEvent;
		_effects.Changed += FireChangedEvent;
		_selfAuraEffects.Changed += FireChangedEvent;
		_animSets.Changed += FireChangedEvent;
		_auraEffects.Changed += FireChangedEvent;
		_uiEvents.Changed += FireChangedEvent;
		_cameras.Changed += FireChangedEvent;
		_winLoseEffects.Changed += FireChangedEvent;
		_femaleMaleAssistEffect.Changed += FireChangedEvent;
		_wallTargetZoneWidth.Changed += FireChangedEvent;
	}

	public SessionVisualRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionVisualRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionVisualRoot" );
		emoteSettings = source.emoteSettings;
		teamColoringScheme = source.teamColoringScheme;
		effects = source.effects;
		selfAuraEffects = source.selfAuraEffects;
		animSets = source.animSets;
		auraEffects = source.auraEffects;
		uiEvents = source.uiEvents;
		cameras = source.cameras;
		winLoseEffects = source.winLoseEffects;
		femaleMaleAssistEffect = source.femaleMaleAssistEffect;
		wallTargetZoneWidth = source.wallTargetZoneWidth;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionVisualRoot source = _source as SessionVisualRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionVisualRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionVisualRoot newParent = rawParent == null ? null : rawParent.Get<SessionVisualRoot>();
		if ( newParent == null && _newParent is SessionVisualRoot )
			newParent = _newParent as SessionVisualRoot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_emoteSettings.SetParent( newParent == null ? null : newParent._emoteSettings );
		_teamColoringScheme.SetParent( newParent == null ? null : newParent._teamColoringScheme );
		_effects.SetParent( newParent == null ? null : newParent._effects );
		_selfAuraEffects.SetParent( newParent == null ? null : newParent._selfAuraEffects );
		_animSets.SetParent( newParent == null ? null : newParent._animSets );
		_auraEffects.SetParent( newParent == null ? null : newParent._auraEffects );
		_uiEvents.SetParent( newParent == null ? null : newParent._uiEvents );
		_cameras.SetParent( newParent == null ? null : newParent._cameras );
		_winLoseEffects.SetParent( newParent == null ? null : newParent._winLoseEffects );
		_femaleMaleAssistEffect.SetParent( newParent == null ? null : newParent._femaleMaleAssistEffect );
		_wallTargetZoneWidth.SetParent( newParent == null ? null : newParent._wallTargetZoneWidth );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_emoteSettings.Reset();
		_teamColoringScheme.Reset();
		_effects.Reset();
		_selfAuraEffects.Reset();
		_animSets.Reset();
		_auraEffects.Reset();
		_uiEvents.Reset();
		_cameras.Reset();
		_winLoseEffects.Reset();
		_femaleMaleAssistEffect.Reset();
		_wallTargetZoneWidth.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_emoteSettings.IsDerivedFromParent()
			&& _teamColoringScheme.IsDerivedFromParent()
			&& _effects.IsDerivedFromParent()
			&& _selfAuraEffects.IsDerivedFromParent()
			&& _animSets.IsDerivedFromParent()
			&& _auraEffects.IsDerivedFromParent()
			&& _uiEvents.IsDerivedFromParent()
			&& _cameras.IsDerivedFromParent()
			&& _winLoseEffects.IsDerivedFromParent()
			&& _femaleMaleAssistEffect.IsDerivedFromParent()
			&& _wallTargetZoneWidth.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "emoteSettings" )
			_emoteSettings.Reset();
		else if ( fieldName == "teamColoringScheme" )
			_teamColoringScheme.Reset();
		else if ( fieldName == "effects" )
			_effects.Reset();
		else if ( fieldName == "selfAuraEffects" )
			_selfAuraEffects.Reset();
		else if ( fieldName == "animSets" )
			_animSets.Reset();
		else if ( fieldName == "auraEffects" )
			_auraEffects.Reset();
		else if ( fieldName == "uiEvents" )
			_uiEvents.Reset();
		else if ( fieldName == "cameras" )
			_cameras.Reset();
		else if ( fieldName == "winLoseEffects" )
			_winLoseEffects.Reset();
		else if ( fieldName == "femaleMaleAssistEffect" )
			_femaleMaleAssistEffect.Reset();
		else if ( fieldName == "wallTargetZoneWidth" )
			_wallTargetZoneWidth.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "emoteSettings" )
			return _emoteSettings.IsDerivedFromParent();
		if ( fieldName == "teamColoringScheme" )
			return _teamColoringScheme.IsDerivedFromParent();
		if ( fieldName == "effects" )
			return _effects.IsDerivedFromParent();
		if ( fieldName == "selfAuraEffects" )
			return _selfAuraEffects.IsDerivedFromParent();
		if ( fieldName == "animSets" )
			return _animSets.IsDerivedFromParent();
		if ( fieldName == "auraEffects" )
			return _auraEffects.IsDerivedFromParent();
		if ( fieldName == "uiEvents" )
			return _uiEvents.IsDerivedFromParent();
		if ( fieldName == "cameras" )
			return _cameras.IsDerivedFromParent();
		if ( fieldName == "winLoseEffects" )
			return _winLoseEffects.IsDerivedFromParent();
		if ( fieldName == "femaleMaleAssistEffect" )
			return _femaleMaleAssistEffect.IsDerivedFromParent();
		if ( fieldName == "wallTargetZoneWidth" )
			return _wallTargetZoneWidth.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
