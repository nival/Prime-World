using System;
using libdb.DB;
using System.Xml.Serialization;
using System.Collections.Generic;
using libdb.UndoRedo;
using System.ComponentModel;
using libdb.Diagnostics;
namespace libdb.Animated
{
	public enum AnimatedType
	{
		None,
		Clamp,
		Wrap,
	}

	public interface IAnimatedAlgorithm<T>
	{
		T GetValue( T a, T b, float t );
	}

  public abstract class AnimatedTracks<T, TAlgorithm> : IDBSerializable, IChangeable, ICompositeDBValue 
    where TAlgorithm : IAnimatedAlgorithm<T>
  {
    #region Nested Types

    public class AnimatedTracksSerializeAttributes
		{
			public bool Animated = false;
		
			public AnimatedTracksSerializeAttributes() { }
			public AnimatedTracksSerializeAttributes( bool animated ) 
      { 
        this.Animated = animated; 
      }
		}

		public class AnimatedTracksSerializeObject
		{
			public class KeyValueObject
			{
				public float Key = 0.0f;
				public object Value = null;

				public KeyValueObject() { }
				public KeyValueObject( float key, object value ) 
        { 
          this.Key = key; 
          this.Value = value; 
        }
			}

			public AnimatedType Type = AnimatedType.None;
			public UndoRedoList<UndoRedoList<AnimatedTrack<T>.SerializaedKeyValue>> Tracks = new UndoRedoList<UndoRedoList<AnimatedTrack<T>.SerializaedKeyValue>>( null );
			public UndoRedoList<KeyValueObject> Values = new UndoRedoList<KeyValueObject>( null );
		}
   
    private class TrackCallback : AnimatedTrack<T>.ITrackCallback
    {
      private readonly AnimatedTracks<T, TAlgorithm> owner = null;
      private readonly int trackNumber;

      public TrackCallback( AnimatedTracks<T, TAlgorithm> owner, int trackNumber )
      {
        this.owner = owner; 
        this.trackNumber = trackNumber;
      }

      public void BeforeChanged() 
      { 
        owner.OnBeforeTrackChanged(); 
      }

      public void Changed() 
      { 
        owner.OnTrackChanged(); 
      }

      public AnimatedTrack<T> GetParentTrack()
      {
        if ( owner.isDerivedFromParent && owner.parent != null )
          return owner.parent[trackNumber];
        return null;
      }
    }

    #endregion

    private static readonly TAlgorithm algorithm = default( TAlgorithm );

  	private readonly DBResource owner = null;

		protected AnimatedTracks( DBResource _owner, int _tracksCount )
		{
			owner = _owner;

			tracks = new AnimatedTrack<T>[_tracksCount];
			for ( int i = 0; i < _tracksCount; ++i )
			{
				tracks[i] = new AnimatedTrack<T>( owner, default( T ), new TrackCallback( this, i ) );
			}
		}


		public virtual DBResource GetOwner() { return owner; }

    public event EventHandler Changed;

    protected void FireChangedEvent( object sender, EventArgs e )
    {
      if ( Changed != null ) 
        Changed( sender, e );
    }

		private readonly AnimatedTrack<T>[] tracks = null;

		protected virtual void OnChanged() 
    {
      isDerivedFromParent = false;
      FireChangedEvent( this, EventArgs.Empty );
    }

		private void OnTrackChanged()
		{
				OnChanged();
		}

    [Browsable( false )]
		public AnimatedType Type
		{
			get 
      {
        if( isDerivedFromParent && parent != null )
          return parent.Type;

        foreach( AnimatedTrack<T> track in tracks )
        {
          if( track.Length > 0.0f )
            return AnimatedType.Clamp;
        }

        return AnimatedType.None;
	    }
		}

		[XmlIgnoreAttribute]
    [Browsable( false )]
		public AnimatedTrack<T> this[int index] { get{ return tracks[index]; } }
		public IAnimatedTrack GetObjectTrack( int index ) { return tracks[index]; }

		[XmlIgnoreAttribute]
    [Browsable( false )]
		public int TracksCount 
    { 
      get
      {
        if ( isDerivedFromParent && parent != null )
          return parent.TracksCount;
        return tracks.Length;
      }
    }

		private T GetTrackValue( float time, AnimatedTrack<T> track )
		{
      if ( isDerivedFromParent && parent != null )
        return parent.GetTrackValue( time, track );

      float t = track.GetTime( time );

			int index = track.FindKey( t );
			float key = track.GetKey( index );
			T value = track.GetValue( index );
			if ( key == t || index + 1 == track.KeysCount )
				return value;

			float key2 = track.GetKey( index + 1 );
			T value2 = track.GetValue( index + 1 );

			return algorithm.GetValue( value, value2, ( t - key ) / ( key2 - key ) );
		}

		public T GetTrackValue( float time, int trackIndex )
		{
			return GetTrackValue( time, this[trackIndex] );
		}

		public object GetObjectTrackValue( float time, int trackIndex )
		{
			return GetTrackValue( time, trackIndex );
		}

		[XmlIgnoreAttribute]
    [Browsable( false )]
		public virtual Type ValueType { get { return typeof( T ); } }
		
		[XmlIgnoreAttribute]
    [Browsable( false )]
		public Type TrackValueType { get { return typeof( T ); } }

    public bool IsEqual( AnimatedTracks<T, TAlgorithm> source )
    {
      if ( ReferenceEquals( source, this ) )
        return true;
      if ( TracksCount != source.TracksCount )
        return false;

      //if ( type != source.type )
      //  return false;

      for ( int i = 0; i < tracks.Length; ++i )
        if ( !tracks[i].IsEqual( source.tracks[i] ) )
          return false;

      return true;
    }

    private List<int[]> BuildIndices()
    {
      List<int[]> indices = new List<int[]>();
      int[] currentIndices = new int[TracksCount];
      int[] tempIndices = new int[TracksCount];

      indices.Add( tempIndices );

      bool allTrackFinished = false;
      
      while ( !allTrackFinished )
      {
        allTrackFinished = true;
        
        float minTime = float.MaxValue;

        for ( int i = 0; i < TracksCount; ++i )
        {
          if ( tracks[i].KeysCount == currentIndices[i] + 1 )
            continue;

          if ( tracks[i].GetKey( currentIndices[i] + 1 ) < minTime )
          {
            minTime = tracks[i].GetKey( currentIndices[i] + 1 );
            allTrackFinished = false;
          }
        }

        if ( allTrackFinished )
          break;

        tempIndices = new int[TracksCount];

        for ( int i = 0; i < TracksCount; ++i )
        {
          if ( ( currentIndices[i] < tracks[i].KeysCount - 1 ) && 
               ( tracks[i].GetKey( currentIndices[i] + 1 ) == minTime) )
          {
            currentIndices[i] = currentIndices[i] + 1;
            tempIndices[i] = currentIndices[i];
          }
          else
          {
            tempIndices[i] = -1;
          }
        }

        indices.Add( tempIndices );
      }

      return indices;
    }

    protected abstract object GetObjectForSerialization( float time, int[] indices );

		public void Serialize( FieldPath path, out object nestedObject, out object attributes )
		{
      if( Type == AnimatedType.None )
      {
        IAnimated animated = this as IAnimated;
        nestedObject = animated.GetObjectValue( 0.0f );
        attributes = null;
      }
      else
			{
				AnimatedTracksSerializeObject serializeObject = new AnimatedTracksSerializeObject();
				serializeObject.Type = Type;
				foreach ( AnimatedTrack<T> track in tracks )
          serializeObject.Tracks.Add( track.Serialize() as UndoRedoList<AnimatedTrack<T>.SerializaedKeyValue> );

        List<int[]> indices = BuildIndices();
        
        foreach ( int[] currentIndices in indices )
				{
          float time = float.MinValue;
          for( int i = 0; i < TracksCount; ++i )
          {
            if ( currentIndices[i] == -1 )
              continue;

            time = tracks[i].GetKey( currentIndices[i] );
            break;
          }

          serializeObject.Values.Add( new AnimatedTracksSerializeObject.KeyValueObject( time, GetObjectForSerialization( time, currentIndices ) ) );
				}

				attributes = new AnimatedTracksSerializeAttributes( true );
				nestedObject = serializeObject;
			}
    }

		public Type GetAttributesType()
		{
			return typeof( AnimatedTracksSerializeAttributes );
		}

		public bool DeserializeAttributes( object attributes, out Type nestedObjectType )
		{
			IAnimated animated = this as IAnimated;
			AnimatedTracksSerializeAttributes attr = attributes as AnimatedTracksSerializeAttributes;
			if ( attr == null || !attr.Animated )
				nestedObjectType = animated.ValueType;
			else
				nestedObjectType = typeof( AnimatedTracksSerializeObject );

			return true;
		}

		public bool DeserializeNestedObject( object attributes, object nestedObject )
		{
			AnimatedTracksSerializeAttributes attr = attributes as AnimatedTracksSerializeAttributes;
			if ( attr == null || !attr.Animated )
			{
        isDerivedFromParent = false;
        //Type = AnimatedType.None;
				IAnimated animated = this as IAnimated;
				animated.Clear( nestedObject );
			}
			else
			{
				AnimatedTracksSerializeObject nestedAnimated = nestedObject as AnimatedTracksSerializeObject;
				if ( nestedAnimated == null )
					return false;

        isDerivedFromParent = false;
				//type = nestedAnimated.Type;
				int tracksCount = Math.Min( nestedAnimated.Tracks.Count, TracksCount );
				for ( int trackIndex = 0; trackIndex < tracksCount; ++trackIndex )
					tracks[trackIndex].Deserialize( nestedAnimated.Tracks[trackIndex] );
			}

			return true;
		}

    #region IBasicDBValue Members

    private AnimatedTracks<T, TAlgorithm> parent = null;
    private bool isDerivedFromParent = true;
    public virtual void Reset()
    {
      isDerivedFromParent = true;
    }

    public virtual bool IsDerivedFromParent()
    {
      return isDerivedFromParent;
    }

    public virtual void SetParent( object _parent )
    {
      AnimatedTracks<T, TAlgorithm> parent = _parent as AnimatedTracks<T, TAlgorithm>;
      if ( parent == null && this.parent != null )
        Assign( this.parent );
      this.parent = parent;
    }

    public virtual void Assign( object _source )
    {
      AnimatedTracks<T, TAlgorithm> source = _source as AnimatedTracks<T, TAlgorithm>;
      if ( null == source )
        return;

      if ( TracksCount != source.TracksCount || ReferenceEquals( source, this ) )
        return;

      //type = source.type;
      for ( int i = 0; i < tracks.Length; ++i )
        tracks[i].Assign( source.tracks[i] );
    }

    private void OnBeforeTrackChanged()
    {
      if ( isDerivedFromParent && parent != null )
      {
        isDerivedFromParent = false;
        Assign( parent );
      }
    }

    public virtual void ResetField( string fieldName ) 
    { 
      Log.AlwaysAssert( "Should not be called" ); 
    }

    public virtual bool IsFieldDerivedFromParent( string fieldName ) 
    { 
      Log.AlwaysAssert( "Should not be called" ); 
      return false; 
    }

    public virtual bool HasParent()
    {
      Log.AlwaysAssert( "Should not be called" );
      return false;
    }

    #endregion
  }

}