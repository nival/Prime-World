using System;
using System.Collections;
using Unity.Components.SoundsManager.Effects;
using UnityEngine;

namespace Unity.Components.SoundsManager.Tools
{
  /// <summary>
  /// Using for auto dstory oneShot playing audio sources
  /// </summary>
  public sealed class AudioSourceCleaner : MonoBehaviour, IAudioSourceController
  {
    private const float FADE_LENGTH = 0.25f;
    private Action _responseCallback;
    private AudioSource _audioSource;
    private bool _autoDeleteGameObject = false;

    public static IAudioSourceController Create( AudioSource audioSource, Action responseCallback, float startPause )
    {
      AudioSourceCleaner clnr = audioSource.gameObject.AddComponent<AudioSourceCleaner>();
      clnr.SetAudioSource( audioSource, false, responseCallback, startPause );
      return clnr;
    }

    public static IAudioSourceController Create( AudioSource audioSource, Action responseCallback )
    {
      AudioSourceCleaner clnr = audioSource.gameObject.AddComponent<AudioSourceCleaner>();
      clnr.SetAudioSource( audioSource, false, responseCallback, 0 );
      return clnr;
    }

    public void SetAudioSource( AudioSource audioSource, bool autoDeleteGameObject, Action responseCallback, float startPause )
    {
      IsActive = true;
      _autoDeleteGameObject = autoDeleteGameObject;
      _audioSource = audioSource;
      _responseCallback = responseCallback;
      StartCoroutine( StartPlaying( startPause ) );
    }

    private IEnumerator StartPlaying( float pause )
    {
      if ( pause != 0 )
        yield return new WaitForSeconds( pause );
      if ( !_audioSource.isPlaying )
        _audioSource.Play();
      Invoke( "Clear", _audioSource.clip.length + 0.1f );
    }

    private void FadeComplete( Fade fade )
    {
      fade.OnFadeComplete -= FadeComplete;
      if ( !IsActive )
        return;
      _audioSource.Stop();
      Clear();
    }

    private void Clear()
    {
      if ( this.enabled )
      {
        int samplesLeft = _audioSource.timeSamples == 0 ? 0 : _audioSource.clip.samples - _audioSource.timeSamples;
        if ( _audioSource.isPlaying || samplesLeft > 0 )
        {
          Invoke( "Clear", ( (float)samplesLeft / _audioSource.clip.frequency ) + 0.1f );
          return;
        }
        IsActive = false;
        if ( AudioSourceCleared != null )
          AudioSourceCleared( this );
        if ( _responseCallback != null )
          _responseCallback();
        if ( _autoDeleteGameObject )
          Destroy( gameObject );
        else
        {
          Sound.RegisterUnusedAudioSource( _audioSource );
          Destroy( this );
        }
      }
    }

    #region Implementation of IAudioSourceController

    public event Action<IAudioSourceController> AudioSourceCleared;

    public bool IsActive { get; private set; }

    public void Stop()
    {
      Stop( false, FADE_LENGTH );
    }

    public void Stop( bool callCallback, float fadeLength )
    {
      if ( !IsActive )
        return;
      CancelInvoke( "Clear" );
      if ( !callCallback )
        _responseCallback = null;
      var fade = Fade.Create( _audioSource, FadeType.Out, fadeLength, false );
      fade.OnFadeComplete += FadeComplete;
    }

    public void Pause()
    {
      if ( !IsActive )
        return;
      if ( _audioSource.isPlaying )
        _audioSource.Pause();
    }

    public void UnPause()
    {
      if ( !IsActive )
        return;
      if ( !_audioSource.isPlaying && _audioSource.timeSamples != 0 )
        _audioSource.Play();
    }

    public void FadeIn( float fadeLength )
    {
      if ( !IsActive )
        return;
      Fade.Create( _audioSource, FadeType.In, fadeLength, false );
    }

    public void FadeOut( float fadeLength )
    {
      if ( !IsActive )
        return;
      Fade.Create( _audioSource, FadeType.Out, fadeLength, false );
    }

    public void FadeIn( float fadeLength, float fadeTo )
    {
      if ( !IsActive )
        return;
      Fade.Create( _audioSource, FadeType.In, fadeLength, fadeTo, false );
    }

    public void FadeOut( float fadeLength, float fadeTo )
    {
      if ( !IsActive )
        return;
      Fade.Create( _audioSource, FadeType.Out, fadeLength, fadeTo, false );
    }

    #endregion
  }
}
