using UnityEngine;

namespace Unity.Components.SoundsManager.Core
{
  static internal class Processor
  {
    public static void PlaySound( AudioSource source, AudioClip clip, ClipPlayMode mode )
    {
      if ( ( mode & ClipPlayMode.Loop ) == ClipPlayMode.Loop )
        source.loop = true;
      else
        source.loop = false;

      source.clip = clip;

      if ( ( mode & ClipPlayMode.FromRandomPoint ) == ClipPlayMode.FromRandomPoint )
      {
        System.Random r = new System.Random();
        source.time = (float)( ( clip.length / 2 ) * r.NextDouble() );
      }

      source.Play();
    }

    public static void PlaySound( AudioSource source, AudioClip clip )
    {
      source.clip = clip;
      source.loop = false;
      source.Play();
    }
  }
}
