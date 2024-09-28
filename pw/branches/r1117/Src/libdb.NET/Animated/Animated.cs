using libdb.DB;
using System.Collections.Generic;
using System;
using System.ComponentModel;

namespace libdb.Animated
{
	public interface IAnimated
	{
    [Browsable( false )]
    AnimatedType Type { get; }

		object GetObjectValue( float time );
		object GetObjectTrackValue( float time, int trackIndex );

		void Clear( object value );

    [Browsable( false )]
    int TracksCount { get; }
		IAnimatedTrack GetObjectTrack( int index );

    [Browsable( false )]
    Type ValueType { get; }
    [Browsable( false )]
    Type TrackValueType { get; }
	}

	public interface IAnimated<T, TField> : IAnimated
	{
		T GetValue( float time );
		TField GetTrackValue( float time, int trackIndex );
	}

	public class AnimatedDiscrete<T> : AnimatedTracks<T, AnimatedDiscrete<T>.Algorithm>, IAnimated, IAnimated<T, T>
	{
		public struct Algorithm : IAnimatedAlgorithm<T>
		{
			public T GetValue( T a, T b, float t ) { return a; }
		}

		//for codegen only
		public AnimatedDiscrete() : base( null, 1 ){}

		//for codegen only
		public AnimatedDiscrete( T value )
			: base( null, 1 )
		{
			this[0].SetKey( 0, 0.0f );
			this[0].SetValue( 0, value );
		}

		public AnimatedDiscrete( DBResource owner ) : base( owner, 1 ) { }

		public AnimatedDiscrete( DBResource owner, T value )
			: base( owner, 1 ) 
		{ 
			this[0].SetKey( 0, 0.0f ); 
			this[0].SetValue( 0, value ); 
		}

    protected override object GetObjectForSerialization( float time, int[] indices ) 
		{ 
			return this[0].GetValue( indices[0] ); 
		}

    public T GetValue( float time ) { return GetTrackValue( time, 0 ); }
		public object GetObjectValue( float time ) { return GetValue( time ); }
		public void Clear( object value ) { this[0].Clear(); this[0].SetObjectValue( 0, value ); }
	}

	public struct IntAlgorithm : IAnimatedAlgorithm<int>
	{
		public int GetValue( int a, int b, float t ) { return a + (int)( ( b - a ) * t ); }
	}

	public struct FloatAlgorithm : IAnimatedAlgorithm<float>
	{
		public float GetValue( float a, float b, float t ) { return a + ( (float)( b - a ) * t ); }
	}

	public class AnimatedLinear<T, TAlgorithm> : AnimatedTracks<T, TAlgorithm>, IAnimated, IAnimated<T, T>
		where TAlgorithm : IAnimatedAlgorithm<T>
	{
		//for codegen only
		public AnimatedLinear() : base( null, 1 ) { }
		//for codegen only
		public AnimatedLinear( T value ) : base( null, 1 ) { this[0].SetKey( 0, 0.0f ); this[0].SetValue( 0, value ); }

		public AnimatedLinear( DBResource owner ) : base( owner, 1 ) { }
		public AnimatedLinear( DBResource owner, T value ): base( owner, 1 )
		{
			this[0].SetKey( 0, 0.0f ); 
			this[0].SetValue( 0, value );
		}

    protected override object GetObjectForSerialization( float time, int[] indices ) { return this[0].GetValue( indices[0] ); }

    public T GetValue( float time ) { return GetTrackValue( time, 0 ); }
		public object GetObjectValue( float time ) { return GetValue( time ); }
		public void Clear( object value ) { this[0].Clear(); this[0].SetObjectValue( 0, value ); }
	}

	public interface IComplexConverter<T, TField>
	{
    T ConvertTo( TField[] tracks );
    void ConvertFrom<TAlgorithm>( int index, T value, AnimatedTracks<TField, TAlgorithm> tracks ) where TAlgorithm : IAnimatedAlgorithm<TField>;
		int TrackCount { get; }
	}

	public struct DummyComplexConverter<T, TField> : IComplexConverter<T, TField>
	{
    public T ConvertTo( TField[] tracks ) { return default( T ); }
    public void ConvertFrom<TAlgorithm>( int index, T value, AnimatedTracks<TField, TAlgorithm> tracks ) where TAlgorithm : IAnimatedAlgorithm<TField> { }
		public int TrackCount { get { return 0; } }
	}

	public sealed class AnimatedComplexConverterAttribute : DBAttribute
	{
    private readonly bool createConverter = true;
		private readonly string[] args = null;

    public AnimatedComplexConverterAttribute( params string[] args ) { this.args = args; }
    public AnimatedComplexConverterAttribute( bool createConverter, params string[] args ) { this.createConverter = createConverter; this.args = args; }

    public bool CreateConverter { get { return createConverter; } }
		public string[] Args { get { return args; } }

		public override string ConstructorParameters
		{
			get
			{
				List<string> quotedArgs = new List<string>();
        if ( !CreateConverter )
          quotedArgs.Add( "false" );
				foreach ( string arg in args )
					quotedArgs.Add( "\"" + arg + "\"" );
				
				return string.Join( ", ", quotedArgs.ToArray() );
			}
		}
	}

	public class AnimatedComplex<T, TField, TAlgorithm, TConverter> : AnimatedTracks<TField, TAlgorithm>, IAnimated, IAnimated<T, TField>
		where TAlgorithm : IAnimatedAlgorithm<TField>
		where TConverter : IComplexConverter<T, TField>, new()
	{
		private static readonly TConverter converter = new TConverter();

		public AnimatedComplex() : base( null, converter.TrackCount ) { }

		public AnimatedComplex( T value ) : base( null, converter.TrackCount ) 
		{ 
			converter.ConvertFrom( 0, value, this ); 
		}

		public AnimatedComplex( params TField[] values )
			: base( null, values.Length )
		{
			for ( int i = 0; i < values.Length; ++i )
			{
				this[i].Clear();
				this[i].SetValue( 0, values[i] );
			}
		}

		public AnimatedComplex( DBResource owner ) : base( owner, converter.TrackCount ) { }

		public AnimatedComplex( DBResource owner, T value )
			: base( owner, converter.TrackCount )
		{
			converter.ConvertFrom( 0, value, this );
		}

		public AnimatedComplex( DBResource owner, params TField[] values )
			: base( owner, values.Length )
		{
			for ( int i = 0; i < values.Length; ++i )
			{
				this[i].Clear();
				this[i].SetValue( 0, values[i] );
			}
		}

    protected override object GetObjectForSerialization( float time, int[] indices )
    {
      TField[] tracks = new TField[TracksCount];
      for ( int i = 0; i < TracksCount; ++i )
      {
        if ( indices[i] == -1 )
          tracks[i] = GetTrackValue( time, i );
        else
          tracks[i] = this[i].GetValue( indices[i] );
      }

      return converter.ConvertTo( tracks );
    }

		public T GetValue( float time )
    {
      TField[] tracks = new TField[TracksCount];
      for ( int i = 0; i < TracksCount; ++i )
        tracks[i] = GetTrackValue( time, i );
        
      return converter.ConvertTo( tracks );
    }

		public object GetObjectValue( float time )
    {
      return GetValue( time );
    }

		public void Clear( object value )
    {
      converter.ConvertFrom( 0, (T)value, this );
    }

    [Browsable( false )]
    public override Type ValueType { get { return typeof( T ); } }
	}
}