using System;
using System.Collections.Generic;
using libdb.Animated;
using libdb.Diagnostics;

namespace EditorPlugins.Editors.Animated
{
	public sealed class CombinedAnimated
	{
		private class AnimatedInfo
		{
			public readonly IAnimated animated = null;
			public readonly int trackIndex = 0;

			public AnimatedInfo( IAnimated animated, int trackIndex ) 
      { 
        this.animated = animated; 
        this.trackIndex = trackIndex; 
      }
		}

		private readonly List<AnimatedInfo> collection = new List<AnimatedInfo>();

		public CombinedAnimated( IEnumerable<IAnimated> _collection )
		{
			foreach( IAnimated animated in _collection )
			{
				for ( int i = 0; i < animated.TracksCount; ++i )
				{
					collection.Add( new AnimatedInfo( animated, i ) );

					IAnimatedTrack animatedTrack = animated.GetObjectTrack(i);

					for(int keyIndex = 0; keyIndex < animatedTrack.KeysCount; ++keyIndex)
					{
						if(animatedTrack.GetKey(keyIndex) < 0)
						{
							Log.TraceWarning( "Invalid key found for {0}. Please reexport resource with Big Red Button.", animated.GetType().Name );
						}							
					}
					
				}
			}
		}

		private IAnimated GetAnimated( int trackIndex, out int localTrackIndex )
		{
			if ( trackIndex < 0 || trackIndex >= collection.Count )
			{
				localTrackIndex = -1;
				return null;
			}

			AnimatedInfo info = collection[trackIndex];
			localTrackIndex = info.trackIndex;
			return info.animated;
		}

		private IAnimated GetAnimated( int trackIndex )
		{
			int localTrackIndex = 0;
			return GetAnimated( trackIndex, out localTrackIndex );
		}

		private void ForEach( Action<IAnimated> action )
		{
			IAnimated prevAnimated = null;
      foreach ( AnimatedInfo animInfo in collection )
			{
				if ( prevAnimated != animInfo.animated )
          action( animInfo.animated );
        prevAnimated = animInfo.animated;
			}
		}

		private delegate T AnimatedAction<T>( IAnimated animated, int trackIndex );

		private T DoForAnimated<T>( int trackIndex, AnimatedAction<T> action )
		{
			int localTrackIndex = 0;
			IAnimated animated = GetAnimated( trackIndex, out localTrackIndex );
			return action( animated, localTrackIndex );
		}

    public AnimatedType Type
    {
      get { return collection.Count > 0 ? GetAnimated( 0 ).Type : AnimatedType.None; }
    }

    public float GetTotalLength()
		{
      float len = 0.0f;

      foreach(var a in collection)
      {
        IAnimatedTrack track = a.animated.GetObjectTrack( a.trackIndex );       
        
        if( track.Length > len )
          len = track.Length;
      }

      return len;
		}

		public object GetObjectTrackValue( float time, int trackIndex )
		{
			return DoForAnimated( trackIndex, ( animated, localTrackIndex ) => animated.GetObjectTrackValue( time, localTrackIndex ) );
		}

		public void Clear( object value )
		{
			ForEach( animated => animated.Clear( value ) );
		}

		public int TracksCount
		{
			get { return collection.Count; }
		}

		public IAnimatedTrack GetObjectTrack( int index )
		{
      if ( index < 0 || index >= collection.Count )
        return null;

      return DoForAnimated( index, ( animated, localTrackIndex ) => animated.GetObjectTrack( localTrackIndex ) );
		}

		public Type TrackValueType
		{
			get 
      { 
        return collection.Count > 0 ? GetAnimated( 0 ).TrackValueType : null; 
      }
		}

	}
}
