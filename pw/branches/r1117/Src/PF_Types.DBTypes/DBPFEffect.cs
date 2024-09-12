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
public enum EAuraType
{
	Ally = 0,
	Enemy = 1,
};

public enum EEffectSwitchLogic
{
	FactionVisibility = 0,
	SenderFaction = 1,
};

public enum EMinimapEffects
{
	EggCarrier = 0,
	MarkerAlly = 1,
	MarkerHostile = 2,
	Chat = 3,
};

public enum ESceneObjectVisibilityMode
{
	AsObject = 0,
	AsBuilding = 1,
};

public enum EUnitSceneObjectModifyMode
{
	Append = 0,
	ReplaceStatic = 1,
	ReplaceAnimated = 2,
};

[FactoryImpl("Retrieve", "NGameX::PFAuraEffect", "PFAuraEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0x9E71DC80)]
[UseTypeName("EFFT")]
public class AuraEffect : EffectBase
{
	private UndoRedoDBPtr<AuraEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<AuraEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EAuraType> _type;

	[Description( "Тип ауры: дружественная или враждебная" )]
	public EAuraType type { get { return _type.Get(); } set { _type.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<AuraEffect>(owner);
		_type = new UndoRedo<EAuraType>( owner, EAuraType.Enemy );
		___parent.Changed += FireChangedEvent;
		_type.Changed += FireChangedEvent;
	}

	public AuraEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( AuraEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for AuraEffect" );
		type = source.type;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		AuraEffect source = _source as AuraEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AuraEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		AuraEffect newParent = rawParent == null ? null : rawParent.Get<AuraEffect>();
		if ( newParent == null && _newParent is AuraEffect )
			newParent = _newParent as AuraEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_type.SetParent( newParent == null ? null : newParent._type );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_type.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_type.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "type" )
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

[FactoryImpl("Retrieve", "NGameX::PFEffectSwitcher", "PFEffectSwitcher.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0x9E71EC00)]
[UseTypeName("EFFT")]
public class EffectSwitcher : EffectBase
{
	private UndoRedoDBPtr<EffectSwitcher> ___parent;
	[HideInOutliner]
	public new DBPtr<EffectSwitcher> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EEffectSwitchLogic> _logic;
	private UndoRedoDBPtr<EffectBase> _effectOnVisible;
	private UndoRedoDBPtr<EffectBase> _effectOnInvisible;
	private UndoRedo<bool> _isVisibleUnderWarfog;

	[Description( "Логика переключения между эффектами" )]
	public EEffectSwitchLogic logic { get { return _logic.Get(); } set { _logic.Set( value ); } }

	[Description( "FactionVisibility: Эффект для случая, когда фрацкия смотрящего равна фракции юнита, на которого наложен EffectSwitcher" )]
	public DBPtr<EffectBase> effectOnVisible { get { return _effectOnVisible.Get(); } set { _effectOnVisible.Set( value ); } }

	[Description( "FactionVisibility: Эффект для случая, когда фрацкия смотрящего отличается от фракции юнита, на которого наложен EffectSwitcher" )]
	public DBPtr<EffectBase> effectOnInvisible { get { return _effectOnInvisible.Get(); } set { _effectOnInvisible.Set( value ); } }

	public bool isVisibleUnderWarfog { get { return _isVisibleUnderWarfog.Get(); } set { _isVisibleUnderWarfog.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<EffectSwitcher>(owner);
		_logic = new UndoRedo<EEffectSwitchLogic>( owner, EEffectSwitchLogic.FactionVisibility );
		_effectOnVisible = new UndoRedoDBPtr<EffectBase>( owner );
		_effectOnInvisible = new UndoRedoDBPtr<EffectBase>( owner );
		_isVisibleUnderWarfog = new UndoRedo<bool>( owner, false );
		___parent.Changed += FireChangedEvent;
		_logic.Changed += FireChangedEvent;
		_effectOnVisible.Changed += FireChangedEvent;
		_effectOnInvisible.Changed += FireChangedEvent;
		_isVisibleUnderWarfog.Changed += FireChangedEvent;
	}

	public EffectSwitcher()
	{
		Initialize( this );
	}
	private void AssignSelf( EffectSwitcher source )
	{
		DataBase.UndoRedoManager.Start( "Assign for EffectSwitcher" );
		logic = source.logic;
		effectOnVisible = source.effectOnVisible;
		effectOnInvisible = source.effectOnInvisible;
		isVisibleUnderWarfog = source.isVisibleUnderWarfog;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		EffectSwitcher source = _source as EffectSwitcher;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for EffectSwitcher" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		EffectSwitcher newParent = rawParent == null ? null : rawParent.Get<EffectSwitcher>();
		if ( newParent == null && _newParent is EffectSwitcher )
			newParent = _newParent as EffectSwitcher;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_logic.SetParent( newParent == null ? null : newParent._logic );
		_effectOnVisible.SetParent( newParent == null ? null : newParent._effectOnVisible );
		_effectOnInvisible.SetParent( newParent == null ? null : newParent._effectOnInvisible );
		_isVisibleUnderWarfog.SetParent( newParent == null ? null : newParent._isVisibleUnderWarfog );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_logic.Reset();
		_effectOnVisible.Reset();
		_effectOnInvisible.Reset();
		_isVisibleUnderWarfog.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_logic.IsDerivedFromParent()
			&& _effectOnVisible.IsDerivedFromParent()
			&& _effectOnInvisible.IsDerivedFromParent()
			&& _isVisibleUnderWarfog.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "logic" )
			_logic.Reset();
		else if ( fieldName == "effectOnVisible" )
			_effectOnVisible.Reset();
		else if ( fieldName == "effectOnInvisible" )
			_effectOnInvisible.Reset();
		else if ( fieldName == "isVisibleUnderWarfog" )
			_isVisibleUnderWarfog.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "logic" )
			return _logic.IsDerivedFromParent();
		if ( fieldName == "effectOnVisible" )
			return _effectOnVisible.IsDerivedFromParent();
		if ( fieldName == "effectOnInvisible" )
			return _effectOnInvisible.IsDerivedFromParent();
		if ( fieldName == "isVisibleUnderWarfog" )
			return _isVisibleUnderWarfog.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Retrieve", "NGameX::InvisibilityEffect", "PFInvisibilityEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0x0B732380)]
[UseTypeName("EFFT")]
public class InvisibilityEffect : ScaleColorEffect
{
	private UndoRedoDBPtr<InvisibilityEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<InvisibilityEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }


	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<InvisibilityEffect>(owner);
		___parent.Changed += FireChangedEvent;
	}

	public InvisibilityEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( InvisibilityEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for InvisibilityEffect" );
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		InvisibilityEffect source = _source as InvisibilityEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for InvisibilityEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		InvisibilityEffect newParent = rawParent == null ? null : rawParent.Get<InvisibilityEffect>();
		if ( newParent == null && _newParent is InvisibilityEffect )
			newParent = _newParent as InvisibilityEffect;
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

[FactoryImpl("Retrieve", "NGameX::PFMinimapEffect", "PFMinimapEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xE78B94C0)]
[UseTypeName("EFFT")]
public class MinimapEffect : EffectBase
{
	private UndoRedoDBPtr<MinimapEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<MinimapEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EMinimapEffects> _effect;

	public EMinimapEffects effect { get { return _effect.Get(); } set { _effect.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<MinimapEffect>(owner);
		_effect = new UndoRedo<EMinimapEffects>( owner, EMinimapEffects.EggCarrier );
		___parent.Changed += FireChangedEvent;
		_effect.Changed += FireChangedEvent;
	}

	public MinimapEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( MinimapEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for MinimapEffect" );
		effect = source.effect;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		MinimapEffect source = _source as MinimapEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for MinimapEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		MinimapEffect newParent = rawParent == null ? null : rawParent.Get<MinimapEffect>();
		if ( newParent == null && _newParent is MinimapEffect )
			newParent = _newParent as MinimapEffect;
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

[FactoryImpl("Retrieve", "NGameX::PFPlayAnimEffect", "PFPlayAnimEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0x9E67B282)]
[UseTypeName("EFFT")]
public class PlayAnimationEffect : EffectBase
{
	private UndoRedoDBPtr<PlayAnimationEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<PlayAnimationEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<string> _animGraphNode;
	private UndoRedo<float> _markerReachTime;
	private UndoRedo<string> _marker;
	private UndoRedo<bool> _goToOtherNodeOnStop;
	private UndoRedo<string> _returnAnimGraphNode;

	[Description( "Name of animation graph node to play" )]
	public string animGraphNode { get { return _animGraphNode.Get(); } set { _animGraphNode.Set( value ); } }

	[Description( "Time of reaching specified marker" )]
	public float markerReachTime { get { return _markerReachTime.Get(); } set { _markerReachTime.Set( value ); } }

	[Description( "Marker name" )]
	public string marker { get { return _marker.Get(); } set { _marker.Set( value ); } }

	[Description( "Should animation return to some node when effect is dropped" )]
	public bool goToOtherNodeOnStop { get { return _goToOtherNodeOnStop.Get(); } set { _goToOtherNodeOnStop.Set( value ); } }

	[Description( "Return anim graph node name" )]
	public string returnAnimGraphNode { get { return _returnAnimGraphNode.Get(); } set { _returnAnimGraphNode.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PlayAnimationEffect>(owner);
		_animGraphNode = new UndoRedo<string>( owner, string.Empty );
		_markerReachTime = new UndoRedo<float>( owner, 0.0f );
		_marker = new UndoRedo<string>( owner, string.Empty );
		_goToOtherNodeOnStop = new UndoRedo<bool>( owner, false );
		_returnAnimGraphNode = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_animGraphNode.Changed += FireChangedEvent;
		_markerReachTime.Changed += FireChangedEvent;
		_marker.Changed += FireChangedEvent;
		_goToOtherNodeOnStop.Changed += FireChangedEvent;
		_returnAnimGraphNode.Changed += FireChangedEvent;
	}

	public PlayAnimationEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( PlayAnimationEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PlayAnimationEffect" );
		animGraphNode = source.animGraphNode;
		markerReachTime = source.markerReachTime;
		marker = source.marker;
		goToOtherNodeOnStop = source.goToOtherNodeOnStop;
		returnAnimGraphNode = source.returnAnimGraphNode;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PlayAnimationEffect source = _source as PlayAnimationEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PlayAnimationEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PlayAnimationEffect newParent = rawParent == null ? null : rawParent.Get<PlayAnimationEffect>();
		if ( newParent == null && _newParent is PlayAnimationEffect )
			newParent = _newParent as PlayAnimationEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_animGraphNode.SetParent( newParent == null ? null : newParent._animGraphNode );
		_markerReachTime.SetParent( newParent == null ? null : newParent._markerReachTime );
		_marker.SetParent( newParent == null ? null : newParent._marker );
		_goToOtherNodeOnStop.SetParent( newParent == null ? null : newParent._goToOtherNodeOnStop );
		_returnAnimGraphNode.SetParent( newParent == null ? null : newParent._returnAnimGraphNode );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_animGraphNode.Reset();
		_markerReachTime.Reset();
		_marker.Reset();
		_goToOtherNodeOnStop.Reset();
		_returnAnimGraphNode.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_animGraphNode.IsDerivedFromParent()
			&& _markerReachTime.IsDerivedFromParent()
			&& _marker.IsDerivedFromParent()
			&& _goToOtherNodeOnStop.IsDerivedFromParent()
			&& _returnAnimGraphNode.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "animGraphNode" )
			_animGraphNode.Reset();
		else if ( fieldName == "markerReachTime" )
			_markerReachTime.Reset();
		else if ( fieldName == "marker" )
			_marker.Reset();
		else if ( fieldName == "goToOtherNodeOnStop" )
			_goToOtherNodeOnStop.Reset();
		else if ( fieldName == "returnAnimGraphNode" )
			_returnAnimGraphNode.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "animGraphNode" )
			return _animGraphNode.IsDerivedFromParent();
		if ( fieldName == "markerReachTime" )
			return _markerReachTime.IsDerivedFromParent();
		if ( fieldName == "marker" )
			return _marker.IsDerivedFromParent();
		if ( fieldName == "goToOtherNodeOnStop" )
			return _goToOtherNodeOnStop.IsDerivedFromParent();
		if ( fieldName == "returnAnimGraphNode" )
			return _returnAnimGraphNode.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[FactoryImpl("Retrieve", "NGameX::PriestessSignEffect", "PFPriestessSignEffect.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0xA06CEC00)]
[UseTypeName("EFFT")]
public class PriestessSignEffect : BasicEffectStandalone
{
	private UndoRedoDBPtr<PriestessSignEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<PriestessSignEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<BasicEffectStandalone> _soulEffect;
	private UndoRedo<string> _destinationLocator;
	private UndoRedo<float> _flyInDelay;
	private UndoRedoDBPtr<AnimatedPlacementResource> _flyInPath;
	private UndoRedo<string> _flyInAnim;
	private UndoRedo<string> _flyOutAnim;

	[Description( "Effect of dead hero soul appearing" )]
	public DBPtr<BasicEffectStandalone> soulEffect { get { return _soulEffect.Get(); } set { _soulEffect.Set( value ); } }

	[Description( "Name of locator for soul sphere destination" )]
	public string destinationLocator { get { return _destinationLocator.Get(); } set { _destinationLocator.Set( value ); } }

	[Description( "Time delay from soul effect start to fly-in start" )]
	public float flyInDelay { get { return _flyInDelay.Get(); } set { _flyInDelay.Set( value ); } }

	[Description( "Trajectory of priestess flying in on dead hero body, curve from (0, 1, 1) to (0, 0, 0)" )]
	public DBPtr<AnimatedPlacementResource> flyInPath { get { return _flyInPath.Get(); } set { _flyInPath.Set( value ); } }

	[Description( "Name of animation of priestess flying in on dead hero body (only pose change, no real translation)" )]
	public string flyInAnim { get { return _flyInAnim.Get(); } set { _flyInAnim.Set( value ); } }

	[Description( "Name of animation of priestess flying out with dead hero soul" )]
	public string flyOutAnim { get { return _flyOutAnim.Get(); } set { _flyOutAnim.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<PriestessSignEffect>(owner);
		_soulEffect = new UndoRedoDBPtr<BasicEffectStandalone>( owner );
		_destinationLocator = new UndoRedo<string>( owner, string.Empty );
		_flyInDelay = new UndoRedo<float>( owner, 0.0f );
		_flyInPath = new UndoRedoDBPtr<AnimatedPlacementResource>( owner );
		_flyInAnim = new UndoRedo<string>( owner, string.Empty );
		_flyOutAnim = new UndoRedo<string>( owner, string.Empty );
		___parent.Changed += FireChangedEvent;
		_soulEffect.Changed += FireChangedEvent;
		_destinationLocator.Changed += FireChangedEvent;
		_flyInDelay.Changed += FireChangedEvent;
		_flyInPath.Changed += FireChangedEvent;
		_flyInAnim.Changed += FireChangedEvent;
		_flyOutAnim.Changed += FireChangedEvent;
	}

	public PriestessSignEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( PriestessSignEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for PriestessSignEffect" );
		soulEffect = source.soulEffect;
		destinationLocator = source.destinationLocator;
		flyInDelay = source.flyInDelay;
		flyInPath = source.flyInPath;
		flyInAnim = source.flyInAnim;
		flyOutAnim = source.flyOutAnim;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		PriestessSignEffect source = _source as PriestessSignEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for PriestessSignEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		PriestessSignEffect newParent = rawParent == null ? null : rawParent.Get<PriestessSignEffect>();
		if ( newParent == null && _newParent is PriestessSignEffect )
			newParent = _newParent as PriestessSignEffect;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_soulEffect.SetParent( newParent == null ? null : newParent._soulEffect );
		_destinationLocator.SetParent( newParent == null ? null : newParent._destinationLocator );
		_flyInDelay.SetParent( newParent == null ? null : newParent._flyInDelay );
		_flyInPath.SetParent( newParent == null ? null : newParent._flyInPath );
		_flyInAnim.SetParent( newParent == null ? null : newParent._flyInAnim );
		_flyOutAnim.SetParent( newParent == null ? null : newParent._flyOutAnim );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_soulEffect.Reset();
		_destinationLocator.Reset();
		_flyInDelay.Reset();
		_flyInPath.Reset();
		_flyInAnim.Reset();
		_flyOutAnim.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_soulEffect.IsDerivedFromParent()
			&& _destinationLocator.IsDerivedFromParent()
			&& _flyInDelay.IsDerivedFromParent()
			&& _flyInPath.IsDerivedFromParent()
			&& _flyInAnim.IsDerivedFromParent()
			&& _flyOutAnim.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "soulEffect" )
			_soulEffect.Reset();
		else if ( fieldName == "destinationLocator" )
			_destinationLocator.Reset();
		else if ( fieldName == "flyInDelay" )
			_flyInDelay.Reset();
		else if ( fieldName == "flyInPath" )
			_flyInPath.Reset();
		else if ( fieldName == "flyInAnim" )
			_flyInAnim.Reset();
		else if ( fieldName == "flyOutAnim" )
			_flyOutAnim.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "soulEffect" )
			return _soulEffect.IsDerivedFromParent();
		if ( fieldName == "destinationLocator" )
			return _destinationLocator.IsDerivedFromParent();
		if ( fieldName == "flyInDelay" )
			return _flyInDelay.IsDerivedFromParent();
		if ( fieldName == "flyInPath" )
			return _flyInPath.IsDerivedFromParent();
		if ( fieldName == "flyInAnim" )
			return _flyInAnim.IsDerivedFromParent();
		if ( fieldName == "flyOutAnim" )
			return _flyOutAnim.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(0)]
[FactoryImpl("Retrieve", "NGameX::PFEffectRandom", "PFEffectRandom.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0x0B753AC0)]
[UseTypeName("EFFT")]
public class RandomEffect : EffectBase
{
	private UndoRedoDBPtr<RandomEffect> ___parent;
	[HideInOutliner]
	public new DBPtr<RandomEffect> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoAssignableList<DBPtr<EffectBase>> _effects;

	[Description( "Список эффектов для случайного выбора" )]
	public libdb.IChangeableList<DBPtr<EffectBase>> effects { get { return _effects; } set { _effects.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<RandomEffect>(owner);
		_effects = new UndoRedoAssignableList<DBPtr<EffectBase>>( owner );
		___parent.Changed += FireChangedEvent;
		_effects.Changed += FireChangedEvent;
	}

	public RandomEffect()
	{
		Initialize( this );
	}
	private void AssignSelf( RandomEffect source )
	{
		DataBase.UndoRedoManager.Start( "Assign for RandomEffect" );
		effects = source.effects;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		RandomEffect source = _source as RandomEffect;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for RandomEffect" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		RandomEffect newParent = rawParent == null ? null : rawParent.Get<RandomEffect>();
		if ( newParent == null && _newParent is RandomEffect )
			newParent = _newParent as RandomEffect;
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

[FactoryImpl("Retrieve", "NGameX::PFUnitSceneObjectModify", "PFUnitSceneObjectModify.h", CreateFunction = "PF_Core::CreateEffectFromPool<>")]
[TypeId(0x9E720B00)]
[UseTypeName("EFFT")]
public class UnitSceneObjectModify : EffectBase
{
	private UndoRedoDBPtr<UnitSceneObjectModify> ___parent;
	[HideInOutliner]
	public new DBPtr<UnitSceneObjectModify> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<EUnitSceneObjectModifyMode> _mode;
	private UndoRedo<ESceneObjectVisibilityMode> _visibilityMode;
	private UndoRedoAssignableList<DBPtr<DBSceneObject>> _sceneObjects;

	[Description( "Механизм влияния на оригинальный Scene Object" )]
	public EUnitSceneObjectModifyMode mode { get { return _mode.Get(); } set { _mode.Set( value ); } }

	[Description( "Модель видимости под туманов войны. AsObject - под туманом войны объект не видим, AsBuilding - виден" )]
	public ESceneObjectVisibilityMode visibilityMode { get { return _visibilityMode.Get(); } set { _visibilityMode.Set( value ); } }

	[Description( "Scene Object" )]
	[EnumArray(typeof(ENatureType))]
	public libdb.IChangeableList<DBPtr<DBSceneObject>> sceneObjects { get { return _sceneObjects; } set { _sceneObjects.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<UnitSceneObjectModify>(owner);
		_mode = new UndoRedo<EUnitSceneObjectModifyMode>( owner, EUnitSceneObjectModifyMode.Append );
		_visibilityMode = new UndoRedo<ESceneObjectVisibilityMode>( owner, ESceneObjectVisibilityMode.AsObject );
		_sceneObjects = new UndoRedoAssignableList<DBPtr<DBSceneObject>>( owner, typeof( ENatureType ) );
		___parent.Changed += FireChangedEvent;
		_mode.Changed += FireChangedEvent;
		_visibilityMode.Changed += FireChangedEvent;
		_sceneObjects.Changed += FireChangedEvent;
	}

	public UnitSceneObjectModify()
	{
		Initialize( this );
	}
	private void AssignSelf( UnitSceneObjectModify source )
	{
		DataBase.UndoRedoManager.Start( "Assign for UnitSceneObjectModify" );
		mode = source.mode;
		visibilityMode = source.visibilityMode;
		sceneObjects = source.sceneObjects;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		UnitSceneObjectModify source = _source as UnitSceneObjectModify;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for UnitSceneObjectModify" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		UnitSceneObjectModify newParent = rawParent == null ? null : rawParent.Get<UnitSceneObjectModify>();
		if ( newParent == null && _newParent is UnitSceneObjectModify )
			newParent = _newParent as UnitSceneObjectModify;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_mode.SetParent( newParent == null ? null : newParent._mode );
		_visibilityMode.SetParent( newParent == null ? null : newParent._visibilityMode );
		_sceneObjects.SetParent( newParent == null ? null : newParent._sceneObjects );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_mode.Reset();
		_visibilityMode.Reset();
		_sceneObjects.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_mode.IsDerivedFromParent()
			&& _visibilityMode.IsDerivedFromParent()
			&& _sceneObjects.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "mode" )
			_mode.Reset();
		else if ( fieldName == "visibilityMode" )
			_visibilityMode.Reset();
		else if ( fieldName == "sceneObjects" )
			_sceneObjects.Reset();
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
		if ( fieldName == "visibilityMode" )
			return _visibilityMode.IsDerivedFromParent();
		if ( fieldName == "sceneObjects" )
			return _sceneObjects.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes
