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
[NoCode]
[RenameType("Animated<float, NDb::AnimatedAlgorithms::Linear>")]
public class AnimatedFloat : AnimatedLinear<float, FloatAlgorithm>, libdb.IBasicDBValue, libdb.IChangeable
{

	public AnimatedFloat( DBResource owner ) : base( owner )
	{
	}

	public AnimatedFloat( DBResource owner, float value )
		: base( owner )
	{
		Clear( value );
		Reset();
	}

	public AnimatedFloat( DBResource owner, AnimatedFloat source )
		: this(owner, source, true){}

	private AnimatedFloat( DBResource owner, AnimatedFloat source, bool fireEvent ) : base (owner)
	{
		base.Assign( source );
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		AnimatedFloat source = _source as AnimatedFloat;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedFloat" );
		base.Assign( source );
		DataBase.UndoRedoManager.Commit();
	}

}

[AnimatedComplexConverter("R", "G", "B", "A")]
[NoCode]
[RenameType("Animated<Render::HDRColor, NDb::AnimatedAlgorithms::Linear>")]
public class AnimatedHDRColor : AnimatedComplex<HDRColor, float, FloatAlgorithm, AnimatedHDRColor.Converter>, libdb.IBasicDBValue, libdb.IChangeable
{
	public struct Converter : IComplexConverter<HDRColor, float>
	{
		public HDRColor ConvertTo( float[] tracks )
		{
			HDRColor result = new HDRColor();
			result.R = tracks[0];
			result.G = tracks[1];
			result.B = tracks[2];
			result.A = tracks[3];
			return result;
		}
		public void ConvertFrom<TAlgorithm>( int index, HDRColor value, AnimatedTracks<float, TAlgorithm> tracks ) where TAlgorithm : IAnimatedAlgorithm<float>
		{
			tracks[0].SetValue( index, value.R );
			tracks[1].SetValue( index, value.G );
			tracks[2].SetValue( index, value.B );
			tracks[3].SetValue( index, value.A );
		}
		public int TrackCount { get { return 4; } }
	}


	public AnimatedHDRColor( DBResource owner ) : base( owner )
	{
	}

	public AnimatedHDRColor( DBResource owner, float R, float G, float B, float A )
		: base( owner )
	{
		this[0].Clear();
		this[0].SetValue( 0, R );
		this[1].Clear();
		this[1].SetValue( 0, G );
		this[2].Clear();
		this[2].SetValue( 0, B );
		this[3].Clear();
		this[3].SetValue( 0, A );
		Reset();
	}

	public AnimatedHDRColor( DBResource owner, AnimatedHDRColor source )
		: this(owner, source, true){}

	private AnimatedHDRColor( DBResource owner, AnimatedHDRColor source, bool fireEvent ) : base (owner)
	{
		base.Assign( source );
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		AnimatedHDRColor source = _source as AnimatedHDRColor;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedHDRColor" );
		base.Assign( source );
		DataBase.UndoRedoManager.Commit();
	}

}

[NoCode]
[RenameType("Animated<int, NDb::AnimatedAlgorithms::Linear>")]
public class AnimatedInt : AnimatedLinear<int, IntAlgorithm>, libdb.IBasicDBValue, libdb.IChangeable
{

	public AnimatedInt( DBResource owner ) : base( owner )
	{
	}

	public AnimatedInt( DBResource owner, int value )
		: base( owner )
	{
		Clear( value );
		Reset();
	}

	public AnimatedInt( DBResource owner, AnimatedInt source )
		: this(owner, source, true){}

	private AnimatedInt( DBResource owner, AnimatedInt source, bool fireEvent ) : base (owner)
	{
		base.Assign( source );
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		AnimatedInt source = _source as AnimatedInt;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedInt" );
		base.Assign( source );
		DataBase.UndoRedoManager.Commit();
	}

}

[AnimatedComplexConverter(false, "RotateX", "RotateY", "RotateZ")]
[NoCode]
[RenameType("Animated<CQuat, NDb::AnimatedAlgorithms::Linear>")]
public partial class AnimatedQuat : AnimatedComplex<Quat, float, FloatAlgorithm, AnimatedQuat.Converter>, libdb.IBasicDBValue, libdb.IChangeable
{

	public AnimatedQuat( DBResource owner ) : base( owner )
	{
	}

	public AnimatedQuat( DBResource owner, float RotateX, float RotateY, float RotateZ )
		: base( owner )
	{
		this[0].Clear();
		this[0].SetValue( 0, RotateX );
		this[1].Clear();
		this[1].SetValue( 0, RotateY );
		this[2].Clear();
		this[2].SetValue( 0, RotateZ );
		Reset();
	}

	public AnimatedQuat( DBResource owner, AnimatedQuat source )
		: this(owner, source, true){}

	private AnimatedQuat( DBResource owner, AnimatedQuat source, bool fireEvent ) : base (owner)
	{
		base.Assign( source );
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		AnimatedQuat source = _source as AnimatedQuat;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedQuat" );
		base.Assign( source );
		DataBase.UndoRedoManager.Commit();
	}

}

[AnimatedComplexConverter("x", "y", "z")]
[NoCode]
[RenameType("Animated<CVec3, NDb::AnimatedAlgorithms::Linear>")]
public class AnimatedScale : AnimatedComplex<Scale, float, FloatAlgorithm, AnimatedScale.Converter>, libdb.IBasicDBValue, libdb.IChangeable
{
	public struct Converter : IComplexConverter<Scale, float>
	{
		public Scale ConvertTo( float[] tracks )
		{
			Scale result = new Scale();
			result.x = tracks[0];
			result.y = tracks[1];
			result.z = tracks[2];
			return result;
		}
		public void ConvertFrom<TAlgorithm>( int index, Scale value, AnimatedTracks<float, TAlgorithm> tracks ) where TAlgorithm : IAnimatedAlgorithm<float>
		{
			tracks[0].SetValue( index, value.x );
			tracks[1].SetValue( index, value.y );
			tracks[2].SetValue( index, value.z );
		}
		public int TrackCount { get { return 3; } }
	}


	public AnimatedScale( DBResource owner ) : base( owner )
	{
	}

	public AnimatedScale( DBResource owner, float x, float y, float z )
		: base( owner )
	{
		this[0].Clear();
		this[0].SetValue( 0, x );
		this[1].Clear();
		this[1].SetValue( 0, y );
		this[2].Clear();
		this[2].SetValue( 0, z );
		Reset();
	}

	public AnimatedScale( DBResource owner, AnimatedScale source )
		: this(owner, source, true){}

	private AnimatedScale( DBResource owner, AnimatedScale source, bool fireEvent ) : base (owner)
	{
		base.Assign( source );
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		AnimatedScale source = _source as AnimatedScale;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedScale" );
		base.Assign( source );
		DataBase.UndoRedoManager.Commit();
	}

}

[NoCode]
[RenameType("Animated<string, NDb::AnimatedAlgorithms::Discrete>")]
public class AnimatedString : AnimatedDiscrete<string>, libdb.IBasicDBValue, libdb.IChangeable
{

	public AnimatedString( DBResource owner ) : base( owner )
	{
	}

	public AnimatedString( DBResource owner, string value )
		: base( owner )
	{
		Clear( value );
		Reset();
	}

	public AnimatedString( DBResource owner, AnimatedString source )
		: this(owner, source, true){}

	private AnimatedString( DBResource owner, AnimatedString source, bool fireEvent ) : base (owner)
	{
		base.Assign( source );
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		AnimatedString source = _source as AnimatedString;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedString" );
		base.Assign( source );
		DataBase.UndoRedoManager.Commit();
	}

}

[AnimatedComplexConverter("x", "y")]
[NoCode]
[RenameType("Animated<CVec2, NDb::AnimatedAlgorithms::Linear>")]
public class AnimatedVec2 : AnimatedComplex<Vec2, float, FloatAlgorithm, AnimatedVec2.Converter>, libdb.IBasicDBValue, libdb.IChangeable
{
	public struct Converter : IComplexConverter<Vec2, float>
	{
		public Vec2 ConvertTo( float[] tracks )
		{
			Vec2 result = new Vec2();
			result.x = tracks[0];
			result.y = tracks[1];
			return result;
		}
		public void ConvertFrom<TAlgorithm>( int index, Vec2 value, AnimatedTracks<float, TAlgorithm> tracks ) where TAlgorithm : IAnimatedAlgorithm<float>
		{
			tracks[0].SetValue( index, value.x );
			tracks[1].SetValue( index, value.y );
		}
		public int TrackCount { get { return 2; } }
	}


	public AnimatedVec2( DBResource owner ) : base( owner )
	{
	}

	public AnimatedVec2( DBResource owner, float x, float y )
		: base( owner )
	{
		this[0].Clear();
		this[0].SetValue( 0, x );
		this[1].Clear();
		this[1].SetValue( 0, y );
		Reset();
	}

	public AnimatedVec2( DBResource owner, AnimatedVec2 source )
		: this(owner, source, true){}

	private AnimatedVec2( DBResource owner, AnimatedVec2 source, bool fireEvent ) : base (owner)
	{
		base.Assign( source );
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		AnimatedVec2 source = _source as AnimatedVec2;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedVec2" );
		base.Assign( source );
		DataBase.UndoRedoManager.Commit();
	}

}

[AnimatedComplexConverter("x", "y", "z")]
[NoCode]
[RenameType("Animated<CVec3, NDb::AnimatedAlgorithms::Linear>")]
public class AnimatedVec3 : AnimatedComplex<Vec3, float, FloatAlgorithm, AnimatedVec3.Converter>, libdb.IBasicDBValue, libdb.IChangeable
{
	public struct Converter : IComplexConverter<Vec3, float>
	{
		public Vec3 ConvertTo( float[] tracks )
		{
			Vec3 result = new Vec3();
			result.x = tracks[0];
			result.y = tracks[1];
			result.z = tracks[2];
			return result;
		}
		public void ConvertFrom<TAlgorithm>( int index, Vec3 value, AnimatedTracks<float, TAlgorithm> tracks ) where TAlgorithm : IAnimatedAlgorithm<float>
		{
			tracks[0].SetValue( index, value.x );
			tracks[1].SetValue( index, value.y );
			tracks[2].SetValue( index, value.z );
		}
		public int TrackCount { get { return 3; } }
	}


	public AnimatedVec3( DBResource owner ) : base( owner )
	{
	}

	public AnimatedVec3( DBResource owner, float x, float y, float z )
		: base( owner )
	{
		this[0].Clear();
		this[0].SetValue( 0, x );
		this[1].Clear();
		this[1].SetValue( 0, y );
		this[2].Clear();
		this[2].SetValue( 0, z );
		Reset();
	}

	public AnimatedVec3( DBResource owner, AnimatedVec3 source )
		: this(owner, source, true){}

	private AnimatedVec3( DBResource owner, AnimatedVec3 source, bool fireEvent ) : base (owner)
	{
		base.Assign( source );
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public override void Assign( object _source )
	{
		AnimatedVec3 source = _source as AnimatedVec3;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for AnimatedVec3" );
		base.Assign( source );
		DataBase.UndoRedoManager.Commit();
	}

}

[Custom("Social")]
[NoCode]
[RenameType("Render::Color")]
public class Color : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Color __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _R;
	private UndoRedo<int> _G;
	private UndoRedo<int> _B;
	private UndoRedo<int> _A;

	public int R { get { return _R.Get(); } set { _R.Set( value ); } }

	public int G { get { return _G.Get(); } set { _G.Set( value ); } }

	public int B { get { return _B.Get(); } set { _B.Set( value ); } }

	public int A { get { return _A.Get(); } set { _A.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_R = new UndoRedo<int>( owner, 0 );
		_G = new UndoRedo<int>( owner, 0 );
		_B = new UndoRedo<int>( owner, 0 );
		_A = new UndoRedo<int>( owner, 255 );
		_R.Changed += FireChangedEvent;
		_G.Changed += FireChangedEvent;
		_B.Changed += FireChangedEvent;
		_A.Changed += FireChangedEvent;
	}

	public Color()
	{
		Initialize( GetOwner() );
	}

	public Color( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Color( DBResource owner, Color source )
		: this(owner, source, true){}

	protected Color( DBResource owner, Color source, bool fireEvent )
	{
		_R = new UndoRedo<int>( owner, source.R );
		_G = new UndoRedo<int>( owner, source.G );
		_B = new UndoRedo<int>( owner, source.B );
		_A = new UndoRedo<int>( owner, source.A );
		_R.Changed += FireChangedEvent;
		_G.Changed += FireChangedEvent;
		_B.Changed += FireChangedEvent;
		_A.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Color source = _source as Color;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Color" );
		R = source.R;
		G = source.G;
		B = source.B;
		A = source.A;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Color newParent = _newParent as Color;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_R.SetParent( newParent == null ? null : newParent._R );
		_G.SetParent( newParent == null ? null : newParent._G );
		_B.SetParent( newParent == null ? null : newParent._B );
		_A.SetParent( newParent == null ? null : newParent._A );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_R.Reset();
		_G.Reset();
		_B.Reset();
		_A.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_R.IsDerivedFromParent()
			&& _G.IsDerivedFromParent()
			&& _B.IsDerivedFromParent()
			&& _A.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "R" )
			_R.Reset();
		else if ( fieldName == "G" )
			_G.Reset();
		else if ( fieldName == "B" )
			_B.Reset();
		else if ( fieldName == "A" )
			_A.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "R" )
			return _R.IsDerivedFromParent();
		if ( fieldName == "G" )
			return _G.IsDerivedFromParent();
		if ( fieldName == "B" )
			return _B.IsDerivedFromParent();
		if ( fieldName == "A" )
			return _A.IsDerivedFromParent();
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

[NoCode]
[RenameType("CTPoint<float>")]
public class FloatPoint : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FloatPoint __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _x;
	private UndoRedo<int> _y;

	public int x { get { return _x.Get(); } set { _x.Set( value ); } }

	public int y { get { return _y.Get(); } set { _y.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<int>( owner, 0 );
		_y = new UndoRedo<int>( owner, 0 );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
	}

	public FloatPoint()
	{
		Initialize( GetOwner() );
	}

	public FloatPoint( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FloatPoint( DBResource owner, FloatPoint source )
		: this(owner, source, true){}

	protected FloatPoint( DBResource owner, FloatPoint source, bool fireEvent )
	{
		_x = new UndoRedo<int>( owner, source.x );
		_y = new UndoRedo<int>( owner, source.y );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FloatPoint source = _source as FloatPoint;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FloatPoint" );
		x = source.x;
		y = source.y;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FloatPoint newParent = _newParent as FloatPoint;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x" )
			return _x.IsDerivedFromParent();
		if ( fieldName == "y" )
			return _y.IsDerivedFromParent();
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

[NoCode]
[RenameType("CTRect<float>")]
public class FloatRect : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private FloatRect __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _x1;
	private UndoRedo<float> _y1;
	private UndoRedo<float> _x2;
	private UndoRedo<float> _y2;

	public float x1 { get { return _x1.Get(); } set { _x1.Set( value ); } }

	public float y1 { get { return _y1.Get(); } set { _y1.Set( value ); } }

	public float x2 { get { return _x2.Get(); } set { _x2.Set( value ); } }

	public float y2 { get { return _y2.Get(); } set { _y2.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x1 = new UndoRedo<float>( owner, 0.0f );
		_y1 = new UndoRedo<float>( owner, 0.0f );
		_x2 = new UndoRedo<float>( owner, 0.0f );
		_y2 = new UndoRedo<float>( owner, 0.0f );
		_x1.Changed += FireChangedEvent;
		_y1.Changed += FireChangedEvent;
		_x2.Changed += FireChangedEvent;
		_y2.Changed += FireChangedEvent;
	}

	public FloatRect()
	{
		Initialize( GetOwner() );
	}

	public FloatRect( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public FloatRect( DBResource owner, FloatRect source )
		: this(owner, source, true){}

	protected FloatRect( DBResource owner, FloatRect source, bool fireEvent )
	{
		_x1 = new UndoRedo<float>( owner, source.x1 );
		_y1 = new UndoRedo<float>( owner, source.y1 );
		_x2 = new UndoRedo<float>( owner, source.x2 );
		_y2 = new UndoRedo<float>( owner, source.y2 );
		_x1.Changed += FireChangedEvent;
		_y1.Changed += FireChangedEvent;
		_x2.Changed += FireChangedEvent;
		_y2.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		FloatRect source = _source as FloatRect;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for FloatRect" );
		x1 = source.x1;
		y1 = source.y1;
		x2 = source.x2;
		y2 = source.y2;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		FloatRect newParent = _newParent as FloatRect;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x1.SetParent( newParent == null ? null : newParent._x1 );
		_y1.SetParent( newParent == null ? null : newParent._y1 );
		_x2.SetParent( newParent == null ? null : newParent._x2 );
		_y2.SetParent( newParent == null ? null : newParent._y2 );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x1.Reset();
		_y1.Reset();
		_x2.Reset();
		_y2.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x1.IsDerivedFromParent()
			&& _y1.IsDerivedFromParent()
			&& _x2.IsDerivedFromParent()
			&& _y2.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x1" )
			_x1.Reset();
		else if ( fieldName == "y1" )
			_y1.Reset();
		else if ( fieldName == "x2" )
			_x2.Reset();
		else if ( fieldName == "y2" )
			_y2.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x1" )
			return _x1.IsDerivedFromParent();
		if ( fieldName == "y1" )
			return _y1.IsDerivedFromParent();
		if ( fieldName == "x2" )
			return _x2.IsDerivedFromParent();
		if ( fieldName == "y2" )
			return _y2.IsDerivedFromParent();
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
[RenameType("Render::HDRColor")]
public class HDRColor : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private HDRColor __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _R;
	private UndoRedo<float> _G;
	private UndoRedo<float> _B;
	private UndoRedo<float> _A;

	public float R { get { return _R.Get(); } set { _R.Set( value ); } }

	public float G { get { return _G.Get(); } set { _G.Set( value ); } }

	public float B { get { return _B.Get(); } set { _B.Set( value ); } }

	public float A { get { return _A.Get(); } set { _A.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_R = new UndoRedo<float>( owner, 0.0f );
		_G = new UndoRedo<float>( owner, 0.0f );
		_B = new UndoRedo<float>( owner, 0.0f );
		_A = new UndoRedo<float>( owner, 1.0f );
		_R.Changed += FireChangedEvent;
		_G.Changed += FireChangedEvent;
		_B.Changed += FireChangedEvent;
		_A.Changed += FireChangedEvent;
	}

	public HDRColor()
	{
		Initialize( GetOwner() );
	}

	public HDRColor( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public HDRColor( DBResource owner, HDRColor source )
		: this(owner, source, true){}

	protected HDRColor( DBResource owner, HDRColor source, bool fireEvent )
	{
		_R = new UndoRedo<float>( owner, source.R );
		_G = new UndoRedo<float>( owner, source.G );
		_B = new UndoRedo<float>( owner, source.B );
		_A = new UndoRedo<float>( owner, source.A );
		_R.Changed += FireChangedEvent;
		_G.Changed += FireChangedEvent;
		_B.Changed += FireChangedEvent;
		_A.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		HDRColor source = _source as HDRColor;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for HDRColor" );
		R = source.R;
		G = source.G;
		B = source.B;
		A = source.A;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		HDRColor newParent = _newParent as HDRColor;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_R.SetParent( newParent == null ? null : newParent._R );
		_G.SetParent( newParent == null ? null : newParent._G );
		_B.SetParent( newParent == null ? null : newParent._B );
		_A.SetParent( newParent == null ? null : newParent._A );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_R.Reset();
		_G.Reset();
		_B.Reset();
		_A.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_R.IsDerivedFromParent()
			&& _G.IsDerivedFromParent()
			&& _B.IsDerivedFromParent()
			&& _A.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "R" )
			_R.Reset();
		else if ( fieldName == "G" )
			_G.Reset();
		else if ( fieldName == "B" )
			_B.Reset();
		else if ( fieldName == "A" )
			_A.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "R" )
			return _R.IsDerivedFromParent();
		if ( fieldName == "G" )
			return _G.IsDerivedFromParent();
		if ( fieldName == "B" )
			return _B.IsDerivedFromParent();
		if ( fieldName == "A" )
			return _A.IsDerivedFromParent();
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

[NoCode]
[RenameType("CTPoint<int>")]
public class IntPoint : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private IntPoint __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _x;
	private UndoRedo<int> _y;

	public int x { get { return _x.Get(); } set { _x.Set( value ); } }

	public int y { get { return _y.Get(); } set { _y.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<int>( owner, 0 );
		_y = new UndoRedo<int>( owner, 0 );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
	}

	public IntPoint()
	{
		Initialize( GetOwner() );
	}

	public IntPoint( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public IntPoint( DBResource owner, IntPoint source )
		: this(owner, source, true){}

	protected IntPoint( DBResource owner, IntPoint source, bool fireEvent )
	{
		_x = new UndoRedo<int>( owner, source.x );
		_y = new UndoRedo<int>( owner, source.y );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		IntPoint source = _source as IntPoint;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for IntPoint" );
		x = source.x;
		y = source.y;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		IntPoint newParent = _newParent as IntPoint;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x" )
			return _x.IsDerivedFromParent();
		if ( fieldName == "y" )
			return _y.IsDerivedFromParent();
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

[NoCode]
[RenameType("CTRect<int>")]
public class IntRect : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private IntRect __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<int> _x1;
	private UndoRedo<int> _y1;
	private UndoRedo<int> _x2;
	private UndoRedo<int> _y2;

	public int x1 { get { return _x1.Get(); } set { _x1.Set( value ); } }

	public int y1 { get { return _y1.Get(); } set { _y1.Set( value ); } }

	public int x2 { get { return _x2.Get(); } set { _x2.Set( value ); } }

	public int y2 { get { return _y2.Get(); } set { _y2.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x1 = new UndoRedo<int>( owner, 0 );
		_y1 = new UndoRedo<int>( owner, 0 );
		_x2 = new UndoRedo<int>( owner, 0 );
		_y2 = new UndoRedo<int>( owner, 0 );
		_x1.Changed += FireChangedEvent;
		_y1.Changed += FireChangedEvent;
		_x2.Changed += FireChangedEvent;
		_y2.Changed += FireChangedEvent;
	}

	public IntRect()
	{
		Initialize( GetOwner() );
	}

	public IntRect( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public IntRect( DBResource owner, IntRect source )
		: this(owner, source, true){}

	protected IntRect( DBResource owner, IntRect source, bool fireEvent )
	{
		_x1 = new UndoRedo<int>( owner, source.x1 );
		_y1 = new UndoRedo<int>( owner, source.y1 );
		_x2 = new UndoRedo<int>( owner, source.x2 );
		_y2 = new UndoRedo<int>( owner, source.y2 );
		_x1.Changed += FireChangedEvent;
		_y1.Changed += FireChangedEvent;
		_x2.Changed += FireChangedEvent;
		_y2.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		IntRect source = _source as IntRect;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for IntRect" );
		x1 = source.x1;
		y1 = source.y1;
		x2 = source.x2;
		y2 = source.y2;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		IntRect newParent = _newParent as IntRect;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x1.SetParent( newParent == null ? null : newParent._x1 );
		_y1.SetParent( newParent == null ? null : newParent._y1 );
		_x2.SetParent( newParent == null ? null : newParent._x2 );
		_y2.SetParent( newParent == null ? null : newParent._y2 );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x1.Reset();
		_y1.Reset();
		_x2.Reset();
		_y2.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x1.IsDerivedFromParent()
			&& _y1.IsDerivedFromParent()
			&& _x2.IsDerivedFromParent()
			&& _y2.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x1" )
			_x1.Reset();
		else if ( fieldName == "y1" )
			_y1.Reset();
		else if ( fieldName == "x2" )
			_x2.Reset();
		else if ( fieldName == "y2" )
			_y2.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x1" )
			return _x1.IsDerivedFromParent();
		if ( fieldName == "y1" )
			return _y1.IsDerivedFromParent();
		if ( fieldName == "x2" )
			return _x2.IsDerivedFromParent();
		if ( fieldName == "y2" )
			return _y2.IsDerivedFromParent();
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

[NoCode]
[RenameType("Matrix43")]
public class Matrix : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Matrix __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _x1;
	private UndoRedo<float> _y1;
	private UndoRedo<float> _z1;
	private UndoRedo<float> _w1;
	private UndoRedo<float> _x2;
	private UndoRedo<float> _y2;
	private UndoRedo<float> _z2;
	private UndoRedo<float> _w2;
	private UndoRedo<float> _x3;
	private UndoRedo<float> _y3;
	private UndoRedo<float> _z3;
	private UndoRedo<float> _w3;

	public float x1 { get { return _x1.Get(); } set { _x1.Set( value ); } }

	public float y1 { get { return _y1.Get(); } set { _y1.Set( value ); } }

	public float z1 { get { return _z1.Get(); } set { _z1.Set( value ); } }

	public float w1 { get { return _w1.Get(); } set { _w1.Set( value ); } }

	public float x2 { get { return _x2.Get(); } set { _x2.Set( value ); } }

	public float y2 { get { return _y2.Get(); } set { _y2.Set( value ); } }

	public float z2 { get { return _z2.Get(); } set { _z2.Set( value ); } }

	public float w2 { get { return _w2.Get(); } set { _w2.Set( value ); } }

	public float x3 { get { return _x3.Get(); } set { _x3.Set( value ); } }

	public float y3 { get { return _y3.Get(); } set { _y3.Set( value ); } }

	public float z3 { get { return _z3.Get(); } set { _z3.Set( value ); } }

	public float w3 { get { return _w3.Get(); } set { _w3.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x1 = new UndoRedo<float>( owner, 1.0f );
		_y1 = new UndoRedo<float>( owner, 0.0f );
		_z1 = new UndoRedo<float>( owner, 0.0f );
		_w1 = new UndoRedo<float>( owner, 0.0f );
		_x2 = new UndoRedo<float>( owner, 0.0f );
		_y2 = new UndoRedo<float>( owner, 1.0f );
		_z2 = new UndoRedo<float>( owner, 0.0f );
		_w2 = new UndoRedo<float>( owner, 0.0f );
		_x3 = new UndoRedo<float>( owner, 0.0f );
		_y3 = new UndoRedo<float>( owner, 0.0f );
		_z3 = new UndoRedo<float>( owner, 1.0f );
		_w3 = new UndoRedo<float>( owner, 0.0f );
		_x1.Changed += FireChangedEvent;
		_y1.Changed += FireChangedEvent;
		_z1.Changed += FireChangedEvent;
		_w1.Changed += FireChangedEvent;
		_x2.Changed += FireChangedEvent;
		_y2.Changed += FireChangedEvent;
		_z2.Changed += FireChangedEvent;
		_w2.Changed += FireChangedEvent;
		_x3.Changed += FireChangedEvent;
		_y3.Changed += FireChangedEvent;
		_z3.Changed += FireChangedEvent;
		_w3.Changed += FireChangedEvent;
	}

	public Matrix()
	{
		Initialize( GetOwner() );
	}

	public Matrix( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Matrix( DBResource owner, Matrix source )
		: this(owner, source, true){}

	protected Matrix( DBResource owner, Matrix source, bool fireEvent )
	{
		_x1 = new UndoRedo<float>( owner, source.x1 );
		_y1 = new UndoRedo<float>( owner, source.y1 );
		_z1 = new UndoRedo<float>( owner, source.z1 );
		_w1 = new UndoRedo<float>( owner, source.w1 );
		_x2 = new UndoRedo<float>( owner, source.x2 );
		_y2 = new UndoRedo<float>( owner, source.y2 );
		_z2 = new UndoRedo<float>( owner, source.z2 );
		_w2 = new UndoRedo<float>( owner, source.w2 );
		_x3 = new UndoRedo<float>( owner, source.x3 );
		_y3 = new UndoRedo<float>( owner, source.y3 );
		_z3 = new UndoRedo<float>( owner, source.z3 );
		_w3 = new UndoRedo<float>( owner, source.w3 );
		_x1.Changed += FireChangedEvent;
		_y1.Changed += FireChangedEvent;
		_z1.Changed += FireChangedEvent;
		_w1.Changed += FireChangedEvent;
		_x2.Changed += FireChangedEvent;
		_y2.Changed += FireChangedEvent;
		_z2.Changed += FireChangedEvent;
		_w2.Changed += FireChangedEvent;
		_x3.Changed += FireChangedEvent;
		_y3.Changed += FireChangedEvent;
		_z3.Changed += FireChangedEvent;
		_w3.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Matrix source = _source as Matrix;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Matrix" );
		x1 = source.x1;
		y1 = source.y1;
		z1 = source.z1;
		w1 = source.w1;
		x2 = source.x2;
		y2 = source.y2;
		z2 = source.z2;
		w2 = source.w2;
		x3 = source.x3;
		y3 = source.y3;
		z3 = source.z3;
		w3 = source.w3;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Matrix newParent = _newParent as Matrix;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x1.SetParent( newParent == null ? null : newParent._x1 );
		_y1.SetParent( newParent == null ? null : newParent._y1 );
		_z1.SetParent( newParent == null ? null : newParent._z1 );
		_w1.SetParent( newParent == null ? null : newParent._w1 );
		_x2.SetParent( newParent == null ? null : newParent._x2 );
		_y2.SetParent( newParent == null ? null : newParent._y2 );
		_z2.SetParent( newParent == null ? null : newParent._z2 );
		_w2.SetParent( newParent == null ? null : newParent._w2 );
		_x3.SetParent( newParent == null ? null : newParent._x3 );
		_y3.SetParent( newParent == null ? null : newParent._y3 );
		_z3.SetParent( newParent == null ? null : newParent._z3 );
		_w3.SetParent( newParent == null ? null : newParent._w3 );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x1.Reset();
		_y1.Reset();
		_z1.Reset();
		_w1.Reset();
		_x2.Reset();
		_y2.Reset();
		_z2.Reset();
		_w2.Reset();
		_x3.Reset();
		_y3.Reset();
		_z3.Reset();
		_w3.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x1.IsDerivedFromParent()
			&& _y1.IsDerivedFromParent()
			&& _z1.IsDerivedFromParent()
			&& _w1.IsDerivedFromParent()
			&& _x2.IsDerivedFromParent()
			&& _y2.IsDerivedFromParent()
			&& _z2.IsDerivedFromParent()
			&& _w2.IsDerivedFromParent()
			&& _x3.IsDerivedFromParent()
			&& _y3.IsDerivedFromParent()
			&& _z3.IsDerivedFromParent()
			&& _w3.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x1" )
			_x1.Reset();
		else if ( fieldName == "y1" )
			_y1.Reset();
		else if ( fieldName == "z1" )
			_z1.Reset();
		else if ( fieldName == "w1" )
			_w1.Reset();
		else if ( fieldName == "x2" )
			_x2.Reset();
		else if ( fieldName == "y2" )
			_y2.Reset();
		else if ( fieldName == "z2" )
			_z2.Reset();
		else if ( fieldName == "w2" )
			_w2.Reset();
		else if ( fieldName == "x3" )
			_x3.Reset();
		else if ( fieldName == "y3" )
			_y3.Reset();
		else if ( fieldName == "z3" )
			_z3.Reset();
		else if ( fieldName == "w3" )
			_w3.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x1" )
			return _x1.IsDerivedFromParent();
		if ( fieldName == "y1" )
			return _y1.IsDerivedFromParent();
		if ( fieldName == "z1" )
			return _z1.IsDerivedFromParent();
		if ( fieldName == "w1" )
			return _w1.IsDerivedFromParent();
		if ( fieldName == "x2" )
			return _x2.IsDerivedFromParent();
		if ( fieldName == "y2" )
			return _y2.IsDerivedFromParent();
		if ( fieldName == "z2" )
			return _z2.IsDerivedFromParent();
		if ( fieldName == "w2" )
			return _w2.IsDerivedFromParent();
		if ( fieldName == "x3" )
			return _x3.IsDerivedFromParent();
		if ( fieldName == "y3" )
			return _y3.IsDerivedFromParent();
		if ( fieldName == "z3" )
			return _z3.IsDerivedFromParent();
		if ( fieldName == "w3" )
			return _w3.IsDerivedFromParent();
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

[NoCode]
[RenameType("CQuat")]
public class Quat : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Quat __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _x;
	private UndoRedo<float> _y;
	private UndoRedo<float> _z;
	private UndoRedo<float> _w;

	public float x { get { return _x.Get(); } set { _x.Set( value ); } }

	public float y { get { return _y.Get(); } set { _y.Set( value ); } }

	public float z { get { return _z.Get(); } set { _z.Set( value ); } }

	public float w { get { return _w.Get(); } set { _w.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<float>( owner, 0.0f );
		_y = new UndoRedo<float>( owner, 0.0f );
		_z = new UndoRedo<float>( owner, 0.0f );
		_w = new UndoRedo<float>( owner, 1.0f );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		_z.Changed += FireChangedEvent;
		_w.Changed += FireChangedEvent;
	}

	public Quat()
	{
		Initialize( GetOwner() );
	}

	public Quat( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Quat( DBResource owner, Quat source )
		: this(owner, source, true){}

	protected Quat( DBResource owner, Quat source, bool fireEvent )
	{
		_x = new UndoRedo<float>( owner, source.x );
		_y = new UndoRedo<float>( owner, source.y );
		_z = new UndoRedo<float>( owner, source.z );
		_w = new UndoRedo<float>( owner, source.w );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		_z.Changed += FireChangedEvent;
		_w.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Quat source = _source as Quat;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Quat" );
		x = source.x;
		y = source.y;
		z = source.z;
		w = source.w;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Quat newParent = _newParent as Quat;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		_z.SetParent( newParent == null ? null : newParent._z );
		_w.SetParent( newParent == null ? null : newParent._w );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
		_z.Reset();
		_w.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			&& _z.IsDerivedFromParent()
			&& _w.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else if ( fieldName == "z" )
			_z.Reset();
		else if ( fieldName == "w" )
			_w.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x" )
			return _x.IsDerivedFromParent();
		if ( fieldName == "y" )
			return _y.IsDerivedFromParent();
		if ( fieldName == "z" )
			return _z.IsDerivedFromParent();
		if ( fieldName == "w" )
			return _w.IsDerivedFromParent();
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

[NoCode]
[RenameType("CPlacement")]
public class Placement2 : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Placement2 __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _translateX;
	private UndoRedo<float> _translateY;
	private UndoRedo<float> _translateZ;
	private UndoRedo<float> _rotationX;
	private UndoRedo<float> _rotationY;
	private UndoRedo<float> _rotationZ;
	private UndoRedo<float> _scaleX;
	private UndoRedo<float> _scaleY;
	private UndoRedo<float> _scaleZ;

	public float translateX { get { return _translateX.Get(); } set { _translateX.Set( value ); } }

	public float translateY { get { return _translateY.Get(); } set { _translateY.Set( value ); } }

	public float translateZ { get { return _translateZ.Get(); } set { _translateZ.Set( value ); } }

	public float rotationX { get { return _rotationX.Get(); } set { _rotationX.Set( value ); } }

	public float rotationY { get { return _rotationY.Get(); } set { _rotationY.Set( value ); } }

	public float rotationZ { get { return _rotationZ.Get(); } set { _rotationZ.Set( value ); } }

	public float scaleX { get { return _scaleX.Get(); } set { _scaleX.Set( value ); } }

	public float scaleY { get { return _scaleY.Get(); } set { _scaleY.Set( value ); } }

	public float scaleZ { get { return _scaleZ.Get(); } set { _scaleZ.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_translateX = new UndoRedo<float>( owner, 0.0f );
		_translateY = new UndoRedo<float>( owner, 0.0f );
		_translateZ = new UndoRedo<float>( owner, 0.0f );
		_rotationX = new UndoRedo<float>( owner, 0.0f );
		_rotationY = new UndoRedo<float>( owner, 0.0f );
		_rotationZ = new UndoRedo<float>( owner, 0.0f );
		_scaleX = new UndoRedo<float>( owner, 1.0f );
		_scaleY = new UndoRedo<float>( owner, 1.0f );
		_scaleZ = new UndoRedo<float>( owner, 1.0f );
		_translateX.Changed += FireChangedEvent;
		_translateY.Changed += FireChangedEvent;
		_translateZ.Changed += FireChangedEvent;
		_rotationX.Changed += FireChangedEvent;
		_rotationY.Changed += FireChangedEvent;
		_rotationZ.Changed += FireChangedEvent;
		_scaleX.Changed += FireChangedEvent;
		_scaleY.Changed += FireChangedEvent;
		_scaleZ.Changed += FireChangedEvent;
	}

	public Placement2()
	{
		Initialize( GetOwner() );
	}

	public Placement2( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Placement2( DBResource owner, Placement2 source )
		: this(owner, source, true){}

	protected Placement2( DBResource owner, Placement2 source, bool fireEvent )
	{
		_translateX = new UndoRedo<float>( owner, source.translateX );
		_translateY = new UndoRedo<float>( owner, source.translateY );
		_translateZ = new UndoRedo<float>( owner, source.translateZ );
		_rotationX = new UndoRedo<float>( owner, source.rotationX );
		_rotationY = new UndoRedo<float>( owner, source.rotationY );
		_rotationZ = new UndoRedo<float>( owner, source.rotationZ );
		_scaleX = new UndoRedo<float>( owner, source.scaleX );
		_scaleY = new UndoRedo<float>( owner, source.scaleY );
		_scaleZ = new UndoRedo<float>( owner, source.scaleZ );
		_translateX.Changed += FireChangedEvent;
		_translateY.Changed += FireChangedEvent;
		_translateZ.Changed += FireChangedEvent;
		_rotationX.Changed += FireChangedEvent;
		_rotationY.Changed += FireChangedEvent;
		_rotationZ.Changed += FireChangedEvent;
		_scaleX.Changed += FireChangedEvent;
		_scaleY.Changed += FireChangedEvent;
		_scaleZ.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Placement2 source = _source as Placement2;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Placement2" );
		translateX = source.translateX;
		translateY = source.translateY;
		translateZ = source.translateZ;
		rotationX = source.rotationX;
		rotationY = source.rotationY;
		rotationZ = source.rotationZ;
		scaleX = source.scaleX;
		scaleY = source.scaleY;
		scaleZ = source.scaleZ;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Placement2 newParent = _newParent as Placement2;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_translateX.SetParent( newParent == null ? null : newParent._translateX );
		_translateY.SetParent( newParent == null ? null : newParent._translateY );
		_translateZ.SetParent( newParent == null ? null : newParent._translateZ );
		_rotationX.SetParent( newParent == null ? null : newParent._rotationX );
		_rotationY.SetParent( newParent == null ? null : newParent._rotationY );
		_rotationZ.SetParent( newParent == null ? null : newParent._rotationZ );
		_scaleX.SetParent( newParent == null ? null : newParent._scaleX );
		_scaleY.SetParent( newParent == null ? null : newParent._scaleY );
		_scaleZ.SetParent( newParent == null ? null : newParent._scaleZ );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_translateX.Reset();
		_translateY.Reset();
		_translateZ.Reset();
		_rotationX.Reset();
		_rotationY.Reset();
		_rotationZ.Reset();
		_scaleX.Reset();
		_scaleY.Reset();
		_scaleZ.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_translateX.IsDerivedFromParent()
			&& _translateY.IsDerivedFromParent()
			&& _translateZ.IsDerivedFromParent()
			&& _rotationX.IsDerivedFromParent()
			&& _rotationY.IsDerivedFromParent()
			&& _rotationZ.IsDerivedFromParent()
			&& _scaleX.IsDerivedFromParent()
			&& _scaleY.IsDerivedFromParent()
			&& _scaleZ.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "translateX" )
			_translateX.Reset();
		else if ( fieldName == "translateY" )
			_translateY.Reset();
		else if ( fieldName == "translateZ" )
			_translateZ.Reset();
		else if ( fieldName == "rotationX" )
			_rotationX.Reset();
		else if ( fieldName == "rotationY" )
			_rotationY.Reset();
		else if ( fieldName == "rotationZ" )
			_rotationZ.Reset();
		else if ( fieldName == "scaleX" )
			_scaleX.Reset();
		else if ( fieldName == "scaleY" )
			_scaleY.Reset();
		else if ( fieldName == "scaleZ" )
			_scaleZ.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "translateX" )
			return _translateX.IsDerivedFromParent();
		if ( fieldName == "translateY" )
			return _translateY.IsDerivedFromParent();
		if ( fieldName == "translateZ" )
			return _translateZ.IsDerivedFromParent();
		if ( fieldName == "rotationX" )
			return _rotationX.IsDerivedFromParent();
		if ( fieldName == "rotationY" )
			return _rotationY.IsDerivedFromParent();
		if ( fieldName == "rotationZ" )
			return _rotationZ.IsDerivedFromParent();
		if ( fieldName == "scaleX" )
			return _scaleX.IsDerivedFromParent();
		if ( fieldName == "scaleY" )
			return _scaleY.IsDerivedFromParent();
		if ( fieldName == "scaleZ" )
			return _scaleZ.IsDerivedFromParent();
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

[NoCode]
[RenameType("CVec3")]
public class Scale : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Scale __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _x;
	private UndoRedo<float> _y;
	private UndoRedo<float> _z;

	public float x { get { return _x.Get(); } set { _x.Set( value ); } }

	public float y { get { return _y.Get(); } set { _y.Set( value ); } }

	public float z { get { return _z.Get(); } set { _z.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<float>( owner, 1.0f );
		_y = new UndoRedo<float>( owner, 1.0f );
		_z = new UndoRedo<float>( owner, 1.0f );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		_z.Changed += FireChangedEvent;
	}

	public Scale()
	{
		Initialize( GetOwner() );
	}

	public Scale( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Scale( DBResource owner, Scale source )
		: this(owner, source, true){}

	protected Scale( DBResource owner, Scale source, bool fireEvent )
	{
		_x = new UndoRedo<float>( owner, source.x );
		_y = new UndoRedo<float>( owner, source.y );
		_z = new UndoRedo<float>( owner, source.z );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		_z.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Scale source = _source as Scale;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Scale" );
		x = source.x;
		y = source.y;
		z = source.z;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Scale newParent = _newParent as Scale;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		_z.SetParent( newParent == null ? null : newParent._z );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
		_z.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			&& _z.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else if ( fieldName == "z" )
			_z.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x" )
			return _x.IsDerivedFromParent();
		if ( fieldName == "y" )
			return _y.IsDerivedFromParent();
		if ( fieldName == "z" )
			return _z.IsDerivedFromParent();
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
[RenameType("CVec3")]
public class Vec3 : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Vec3 __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _x;
	private UndoRedo<float> _y;
	private UndoRedo<float> _z;

	public float x { get { return _x.Get(); } set { _x.Set( value ); } }

	public float y { get { return _y.Get(); } set { _y.Set( value ); } }

	public float z { get { return _z.Get(); } set { _z.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<float>( owner, 0.0f );
		_y = new UndoRedo<float>( owner, 0.0f );
		_z = new UndoRedo<float>( owner, 0.0f );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		_z.Changed += FireChangedEvent;
	}

	public Vec3()
	{
		Initialize( GetOwner() );
	}

	public Vec3( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Vec3( DBResource owner, Vec3 source )
		: this(owner, source, true){}

	protected Vec3( DBResource owner, Vec3 source, bool fireEvent )
	{
		_x = new UndoRedo<float>( owner, source.x );
		_y = new UndoRedo<float>( owner, source.y );
		_z = new UndoRedo<float>( owner, source.z );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		_z.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Vec3 source = _source as Vec3;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Vec3" );
		x = source.x;
		y = source.y;
		z = source.z;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Vec3 newParent = _newParent as Vec3;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		_z.SetParent( newParent == null ? null : newParent._z );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
		_z.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			&& _z.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else if ( fieldName == "z" )
			_z.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x" )
			return _x.IsDerivedFromParent();
		if ( fieldName == "y" )
			return _y.IsDerivedFromParent();
		if ( fieldName == "z" )
			return _z.IsDerivedFromParent();
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
[RenameType("CVec2")]
public class Vec2 : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Vec2 __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<float> _x;
	private UndoRedo<float> _y;

	public float x { get { return _x.Get(); } set { _x.Set( value ); } }

	public float y { get { return _y.Get(); } set { _y.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		_x = new UndoRedo<float>( owner, 0.0f );
		_y = new UndoRedo<float>( owner, 0.0f );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
	}

	public Vec2()
	{
		Initialize( GetOwner() );
	}

	public Vec2( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Vec2( DBResource owner, Vec2 source )
		: this(owner, source, true){}

	protected Vec2( DBResource owner, Vec2 source, bool fireEvent )
	{
		_x = new UndoRedo<float>( owner, source.x );
		_y = new UndoRedo<float>( owner, source.y );
		_x.Changed += FireChangedEvent;
		_y.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Vec2 source = _source as Vec2;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Vec2" );
		x = source.x;
		y = source.y;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Vec2 newParent = _newParent as Vec2;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_x.SetParent( newParent == null ? null : newParent._x );
		_y.SetParent( newParent == null ? null : newParent._y );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_x.Reset();
		_y.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_x.IsDerivedFromParent()
			&& _y.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "x" )
			_x.Reset();
		else if ( fieldName == "y" )
			_y.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "x" )
			return _x.IsDerivedFromParent();
		if ( fieldName == "y" )
			return _y.IsDerivedFromParent();
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

[NoCode]
[RenameType("CPlacement")]
public class Placement : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private Placement __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private Vec3 _location;
	private Quat _rotation;
	private Scale _scale;

	public Vec3 location { get { return _location; } set { _location.Assign( value ); } }

	public Quat rotation { get { return _rotation; } set { _rotation.Assign( value ); } }

	public Scale scale { get { return _scale; } set { _scale.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_location = new Vec3( owner );
		_rotation = new Quat( owner );
		_scale = new Scale( owner );
		_location.Changed += FireChangedEvent;
		_rotation.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
	}

	public Placement()
	{
		Initialize( GetOwner() );
	}

	public Placement( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public Placement( DBResource owner, Placement source )
		: this(owner, source, true){}

	protected Placement( DBResource owner, Placement source, bool fireEvent )
	{
		_location = new Vec3( owner, source.location );
		_rotation = new Quat( owner, source.rotation );
		_scale = new Scale( owner, source.scale );
		_location.Changed += FireChangedEvent;
		_rotation.Changed += FireChangedEvent;
		_scale.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		Placement source = _source as Placement;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for Placement" );
		location = source.location;
		rotation = source.rotation;
		scale = source.scale;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		Placement newParent = _newParent as Placement;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_location.SetParent( newParent == null ? null : newParent._location );
		_rotation.SetParent( newParent == null ? null : newParent._rotation );
		_scale.SetParent( newParent == null ? null : newParent._scale );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_location.Reset();
		_rotation.Reset();
		_scale.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_location.IsDerivedFromParent()
			&& _rotation.IsDerivedFromParent()
			&& _scale.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "location" )
			_location.Reset();
		else if ( fieldName == "rotation" )
			_rotation.Reset();
		else if ( fieldName == "scale" )
			_scale.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "location" )
			return _location.IsDerivedFromParent();
		if ( fieldName == "rotation" )
			return _rotation.IsDerivedFromParent();
		if ( fieldName == "scale" )
			return _scale.IsDerivedFromParent();
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
