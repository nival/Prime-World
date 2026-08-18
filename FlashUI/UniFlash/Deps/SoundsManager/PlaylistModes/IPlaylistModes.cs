using System.Collections.Generic;
using UnityEngine;

namespace Unity.Components.SoundsManager.Chains
{
  public interface IPlaylistModes
  {
    AudioClip GetNextTrack (List<AudioClip> clips);
    void Reset ();
  }
}
