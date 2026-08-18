using System.Collections.Generic;
using UnityEngine;

namespace Unity.Components.SoundsManager.Chains
{
  public class RandomNotRepeat : IPlaylistModes
  {
    private List<int> _usedIndexes = new List<int>();
    //Using for after reset playing
    private int _lastIndex = -1;
    /// <summary>
    /// Returns random not played yet clip from list.
    /// </summary>
    /// <param name="clips">
    /// A <see cref="List<AudioClip>"/>
    /// </param>
    /// <returns>
    /// A <see cref="AudioClip"/> null if all tracks was rolled
    /// </returns>
    public AudioClip GetNextTrack( List<AudioClip> clips )
    {
      if ( _usedIndexes.Count == clips.Count )
        return null;
      System.Random r = new System.Random();
      int index = r.Next( 0, clips.Count );

      while ( _usedIndexes.Contains( index ) || ( _lastIndex == index && clips.Count > 1 ) )
        index = r.Next( 0, clips.Count );

      _usedIndexes.Add( index );
      _lastIndex = index;
      return clips[index];
    }

    public void Reset()
    {
      _usedIndexes.Clear();
    }


  }
}
