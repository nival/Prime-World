using System.Collections.Generic;
using UnityEngine;

namespace Unity.Components.SoundsManager.Chains
{
  public class NameOrderedNotRepeat : IPlaylistModes
  {
    private int _lastIndex = -1;

    public AudioClip GetNextTrack( List<AudioClip> clips )
    {
      if ( clips != null )
      {
        _lastIndex++;
        if ( clips.Count > _lastIndex )
          return clips[_lastIndex];
      }
      return null;
    }

    public void Reset()
    {
      _lastIndex = -1;
    }
  }
}
