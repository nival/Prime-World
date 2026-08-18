using System;

namespace Unity.Components.SoundsManager.Tools
{
  public interface IAudioSourceController
  {
    event Action<IAudioSourceController> AudioSourceCleared;
    bool IsActive { get; }
    void Stop();
    void Stop( bool callCallback, float fadeLength );
    void Pause();
    void UnPause();
    void FadeIn( float fadeLength );
    void FadeOut( float fadeLength );
    void FadeIn( float fadeLength, float fadeTo );
    void FadeOut( float fadeLength, float fadeTo );
  } 
}
