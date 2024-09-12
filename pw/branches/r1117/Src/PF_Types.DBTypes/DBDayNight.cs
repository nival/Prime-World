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
public enum EDayNightState
{
	Day = 0,
	Night = 1,
};

public class DayNightSettings : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private DayNightSettings __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<EDayNightState> _initialState;
	private UndoRedo<float> _initialStateFraction;
	private UndoRedo<float> _transitionDuration;
	private UndoRedo<float> _transitionThreshold;
	private UndoRedo<float> _dayDuration;
	private UndoRedo<float> _nightDuration;
	private UndoRedo<float> _twilightDuration;
	private UndoRedo<float> _twilightFraction;
	private UndoRedo<float> _nightSpecularReduction;
	private UndoRedo<bool> _hideDayNightWidget;

	[Description( "Начальное состояние после загрузки карты" )]
	public EDayNightState initialState { get { return _initialState.Get(); } set { _initialState.Set( value ); } }

	[Description( "Относительное смещение начального состояния. Пример: 0.3 - 30% дня (ночи) уже прошло на момент старта." )]
	[FloatMinMax(0, 1)]
	public float initialStateFraction { get { return _initialStateFraction.Get(); } set { _initialStateFraction.Set( value ); } }

	[Description( "Длительность визуального эффекта перехода из дня в ночь и наоборот, в секундах" )]
	[FloatMin(0)]
	public float transitionDuration { get { return _transitionDuration.Get(); } set { _transitionDuration.Set( value ); } }

	[Description( "Относительная граница, при переходе через которую меняется визуальное состояние MSO" )]
	[FloatMinMax(0, 1)]
	public float transitionThreshold { get { return _transitionThreshold.Get(); } set { _transitionThreshold.Set( value ); } }

	[Description( "Длительность дня, в секундах" )]
	[FloatMin(5)]
	public float dayDuration { get { return _dayDuration.Get(); } set { _dayDuration.Set( value ); } }

	[Description( "Длительность ночи, в секундах" )]
	[FloatMin(5)]
	public float nightDuration { get { return _nightDuration.Get(); } set { _nightDuration.Set( value ); } }

	[Browsable( false )]
	[FloatMin(0)]
	[HideInOutliner]
	public float twilightDuration { get { return _twilightDuration.Get(); } set { _twilightDuration.Set( value ); } }

	[Browsable( false )]
	[FloatMinMax(0, 1)]
	[HideInOutliner]
	public float twilightFraction { get { return _twilightFraction.Get(); } set { _twilightFraction.Set( value ); } }

	[Description( "Коэффициент уменьшения specular-компоненты динамического освещения ночью" )]
	[FloatMinMax(0, 1)]
	public float nightSpecularReduction { get { return _nightSpecularReduction.Get(); } set { _nightSpecularReduction.Set( value ); } }

	[Description( "Прячет виджет времени суток" )]
	public bool hideDayNightWidget { get { return _hideDayNightWidget.Get(); } set { _hideDayNightWidget.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_initialState = new UndoRedo<EDayNightState>( owner, EDayNightState.Day );
		_initialStateFraction = new UndoRedo<float>( owner, 0.0f );
		_transitionDuration = new UndoRedo<float>( owner, 0.5f );
		_transitionThreshold = new UndoRedo<float>( owner, 0.75f );
		_dayDuration = new UndoRedo<float>( owner, 600.0f );
		_nightDuration = new UndoRedo<float>( owner, 600.0f );
		_twilightDuration = new UndoRedo<float>( owner, 60.0f );
		_twilightFraction = new UndoRedo<float>( owner, 0.5f );
		_nightSpecularReduction = new UndoRedo<float>( owner, 0.4f );
		_hideDayNightWidget = new UndoRedo<bool>( owner, false );
		_initialState.Changed += FireChangedEvent;
		_initialStateFraction.Changed += FireChangedEvent;
		_transitionDuration.Changed += FireChangedEvent;
		_transitionThreshold.Changed += FireChangedEvent;
		_dayDuration.Changed += FireChangedEvent;
		_nightDuration.Changed += FireChangedEvent;
		_twilightDuration.Changed += FireChangedEvent;
		_twilightFraction.Changed += FireChangedEvent;
		_nightSpecularReduction.Changed += FireChangedEvent;
		_hideDayNightWidget.Changed += FireChangedEvent;
	}

	public DayNightSettings()
	{
		Initialize( GetOwner() );
	}

	public DayNightSettings( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public DayNightSettings( DBResource owner, DayNightSettings source )
		: this(owner, source, true){}

	protected DayNightSettings( DBResource owner, DayNightSettings source, bool fireEvent )
	{
		_initialState = new UndoRedo<EDayNightState>( owner, source.initialState );
		_initialStateFraction = new UndoRedo<float>( owner, source.initialStateFraction );
		_transitionDuration = new UndoRedo<float>( owner, source.transitionDuration );
		_transitionThreshold = new UndoRedo<float>( owner, source.transitionThreshold );
		_dayDuration = new UndoRedo<float>( owner, source.dayDuration );
		_nightDuration = new UndoRedo<float>( owner, source.nightDuration );
		_twilightDuration = new UndoRedo<float>( owner, source.twilightDuration );
		_twilightFraction = new UndoRedo<float>( owner, source.twilightFraction );
		_nightSpecularReduction = new UndoRedo<float>( owner, source.nightSpecularReduction );
		_hideDayNightWidget = new UndoRedo<bool>( owner, source.hideDayNightWidget );
		_initialState.Changed += FireChangedEvent;
		_initialStateFraction.Changed += FireChangedEvent;
		_transitionDuration.Changed += FireChangedEvent;
		_transitionThreshold.Changed += FireChangedEvent;
		_dayDuration.Changed += FireChangedEvent;
		_nightDuration.Changed += FireChangedEvent;
		_twilightDuration.Changed += FireChangedEvent;
		_twilightFraction.Changed += FireChangedEvent;
		_nightSpecularReduction.Changed += FireChangedEvent;
		_hideDayNightWidget.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		DayNightSettings source = _source as DayNightSettings;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for DayNightSettings" );
		initialState = source.initialState;
		initialStateFraction = source.initialStateFraction;
		transitionDuration = source.transitionDuration;
		transitionThreshold = source.transitionThreshold;
		dayDuration = source.dayDuration;
		nightDuration = source.nightDuration;
		twilightDuration = source.twilightDuration;
		twilightFraction = source.twilightFraction;
		nightSpecularReduction = source.nightSpecularReduction;
		hideDayNightWidget = source.hideDayNightWidget;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DayNightSettings newParent = _newParent as DayNightSettings;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_initialState.SetParent( newParent == null ? null : newParent._initialState );
		_initialStateFraction.SetParent( newParent == null ? null : newParent._initialStateFraction );
		_transitionDuration.SetParent( newParent == null ? null : newParent._transitionDuration );
		_transitionThreshold.SetParent( newParent == null ? null : newParent._transitionThreshold );
		_dayDuration.SetParent( newParent == null ? null : newParent._dayDuration );
		_nightDuration.SetParent( newParent == null ? null : newParent._nightDuration );
		_twilightDuration.SetParent( newParent == null ? null : newParent._twilightDuration );
		_twilightFraction.SetParent( newParent == null ? null : newParent._twilightFraction );
		_nightSpecularReduction.SetParent( newParent == null ? null : newParent._nightSpecularReduction );
		_hideDayNightWidget.SetParent( newParent == null ? null : newParent._hideDayNightWidget );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_initialState.Reset();
		_initialStateFraction.Reset();
		_transitionDuration.Reset();
		_transitionThreshold.Reset();
		_dayDuration.Reset();
		_nightDuration.Reset();
		_twilightDuration.Reset();
		_twilightFraction.Reset();
		_nightSpecularReduction.Reset();
		_hideDayNightWidget.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_initialState.IsDerivedFromParent()
			&& _initialStateFraction.IsDerivedFromParent()
			&& _transitionDuration.IsDerivedFromParent()
			&& _transitionThreshold.IsDerivedFromParent()
			&& _dayDuration.IsDerivedFromParent()
			&& _nightDuration.IsDerivedFromParent()
			&& _twilightDuration.IsDerivedFromParent()
			&& _twilightFraction.IsDerivedFromParent()
			&& _nightSpecularReduction.IsDerivedFromParent()
			&& _hideDayNightWidget.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "initialState" )
			_initialState.Reset();
		else if ( fieldName == "initialStateFraction" )
			_initialStateFraction.Reset();
		else if ( fieldName == "transitionDuration" )
			_transitionDuration.Reset();
		else if ( fieldName == "transitionThreshold" )
			_transitionThreshold.Reset();
		else if ( fieldName == "dayDuration" )
			_dayDuration.Reset();
		else if ( fieldName == "nightDuration" )
			_nightDuration.Reset();
		else if ( fieldName == "twilightDuration" )
			_twilightDuration.Reset();
		else if ( fieldName == "twilightFraction" )
			_twilightFraction.Reset();
		else if ( fieldName == "nightSpecularReduction" )
			_nightSpecularReduction.Reset();
		else if ( fieldName == "hideDayNightWidget" )
			_hideDayNightWidget.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "initialState" )
			return _initialState.IsDerivedFromParent();
		if ( fieldName == "initialStateFraction" )
			return _initialStateFraction.IsDerivedFromParent();
		if ( fieldName == "transitionDuration" )
			return _transitionDuration.IsDerivedFromParent();
		if ( fieldName == "transitionThreshold" )
			return _transitionThreshold.IsDerivedFromParent();
		if ( fieldName == "dayDuration" )
			return _dayDuration.IsDerivedFromParent();
		if ( fieldName == "nightDuration" )
			return _nightDuration.IsDerivedFromParent();
		if ( fieldName == "twilightDuration" )
			return _twilightDuration.IsDerivedFromParent();
		if ( fieldName == "twilightFraction" )
			return _twilightFraction.IsDerivedFromParent();
		if ( fieldName == "nightSpecularReduction" )
			return _nightSpecularReduction.IsDerivedFromParent();
		if ( fieldName == "hideDayNightWidget" )
			return _hideDayNightWidget.IsDerivedFromParent();
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
