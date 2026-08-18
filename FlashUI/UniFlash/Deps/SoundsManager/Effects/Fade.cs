using System;
using UnityEngine;

namespace Unity.Components.SoundsManager.Effects
{
  /// <summary>
  /// Using for fade audio source at clip playing
  /// </summary>
  public sealed class Fade : MonoBehaviour
  {
    public event Action<Fade> OnFadeComplete;
    private AudioSource _audioSource;
    private FadeType _type;
    private float _length;
    private float _delta;
    private float _fadeTo;
    private bool _removeAudioSourceAtClear = false;

    private bool _cleared;

    public static Fade Create( AudioSource audioSource, FadeType type, float fadeLength, bool clear )
    {
      return Create( audioSource, type, fadeLength, type == FadeType.In ? Sound.MusicVolume : 0, clear );
    }

    public static Fade Create( AudioSource audioSource, FadeType type, float fadeLength, float fadeTo, bool clear )
    {
      var fades = audioSource.gameObject.GetComponents<Fade>();
      if ( fades != null )
      {
        foreach ( var oldFade in fades )
        {
          if ( !oldFade._cleared && oldFade._audioSource == audioSource )
          {
            oldFade.Clear();
            break;
          }
        }
      }
      Fade fade = audioSource.gameObject.AddComponent<Fade>();
      fade.Initialize( audioSource, type, fadeLength, fadeTo, clear );
      return fade;
    }

    public void Initialize( AudioSource audioSource, FadeType type, float fadeLength, float fadeTo, bool clear )
    {
      _audioSource = audioSource;
      _removeAudioSourceAtClear = clear;
      _type = type;
      _length = fadeLength;
      _fadeTo = fadeTo;
      if ( _length == 0 )
      {
        Clear();
        return;
      }
      if ( _type == FadeType.In )
      {
        _delta = ( _fadeTo - _audioSource.volume ) / _length;
      }

      if ( _type == FadeType.Out )
      {
        _delta = ( _audioSource.volume - _fadeTo ) / _length;
      }

      if ( _delta < 0 )
        Clear();
    }

    private void Update()
    {
      if ( _cleared )
        return;

      if ( _audioSource == null )
      {
        Clear();
        return;
      }
      if ( !_audioSource.isPlaying )
      {
        Clear();
        return;
      }

      if ( _type == FadeType.In )
      {
        _audioSource.volume = Mathf.MoveTowards( _audioSource.volume, _fadeTo, Time.smoothDeltaTime * _delta );
        if ( _audioSource.volume == _fadeTo )
        {
          Clear();
        }
      }

      if ( _type == FadeType.Out )
      {
        _audioSource.volume = Mathf.MoveTowards( _audioSource.volume, _fadeTo, Time.smoothDeltaTime * _delta );
        if ( _audioSource.volume == _fadeTo )
        {
          Clear();
        }
      }
    }

    private void Clear()
    {
      _cleared = true;
      if ( OnFadeComplete != null )
        OnFadeComplete( this );
      if ( _removeAudioSourceAtClear )
        Sound.RegisterUnusedAudioSource( _audioSource );
      Destroy( this );
    }
  }
}
