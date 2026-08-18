using System;
using System.Collections.Generic;
using NivalCLI;
using Unity.Components.SoundsManager.Core;
using Unity.Components.SoundsManager.Effects;
using UnityEngine;
using System.Collections;

namespace Unity.Components.SoundsManager.Chains
{
  /// <summary>
  /// Using for playing sounds in chain
  /// </summary>
  public sealed class SoundsChain : MonoBehaviour
  {
    private List<AudioClip> _clips;
    private ICrossMode _switcher;
    private IPlaylistModes _playlist;
    private float _crossLength;
    private float _lastStoppedTime = 0;
    private float _pauseLength = 0;
    private bool _fromRandomPosition = false;
    private bool _loop = false;
    private AudioSource _activeSource;
    private AudioSource _previousSource;
    private List<AudioSource> _audioSources = new List<AudioSource>();

    public static SoundsChain Create( List<AudioClip> clips, ICrossMode switcher, IPlaylistModes playlist, float crossLength, float pauseLength, bool startWithRandomPosition, bool loop )
    {
      SoundsChain res = Sound.BaseGameObject.AddComponent<SoundsChain>();

      if ( clips == null || clips.Count == 0 )
      {
        CLI.Warning( "Cants start SoundsChain with empty clips list. Chech audio resources." );
        return null;
      }
      res.Initialize( clips, switcher, playlist, crossLength, pauseLength, startWithRandomPosition, loop );
      return res;
    }

    public void Initialize( List<AudioClip> clips, ICrossMode switcher, IPlaylistModes playlist, float crossLength, float pauseLength, bool startWithRandomPosition, bool loop )
    {
      _playlist = playlist;
      _clips = clips;
      _switcher = switcher;
      _crossLength = crossLength;
      _fromRandomPosition = startWithRandomPosition;
      _loop = loop;
      _pauseLength = pauseLength;
    }

    private AudioSource LaunchAudioSource( AudioClip clip )
    {
      if ( clip == null )
      {
        CLI.Warning( "Trying to play null audio clip in SoundsChain" );
        return null;
      }
      AudioSource res = Sound.CreateAudioSource( SourceType.Music );
      ClipPlayMode mode = ClipPlayMode.None;
      if ( _fromRandomPosition )
        mode |= ClipPlayMode.FromRandomPoint;

      Processor.PlaySound( res, clip, mode );
      return res;
    }

    public void Destroy()
    {
      Clear();
    }

    public void Launch()
    {
      Launch( 0f );
    }

    public void Launch( float fadeInLength )
    {
      Launch( fadeInLength, 0f );
    }

    public void Launch( float fadeInLength, float startTime )
    {
      _playlist.Reset();
      AudioClip clip = _playlist.GetNextTrack( _clips );
      if ( clip == null )
      {
        Clear();
        CLI.Warning( "Failed to start sounds chain, because playlist mode return null fro first clip. Check that clips list is not empty" );
        return;
      }
      _activeSource = Sound.CreateAudioSource( SourceType.Music );

      if ( fadeInLength != 0 )
        Fade.Create( _activeSource, FadeType.In, fadeInLength, false );
      _audioSources.Add( _activeSource );
      Processor.PlaySound( _activeSource, clip );
      if ( clip.length > startTime )
        _activeSource.time = startTime;
    }

    private void Update()
    {
      if ( _activeSource == null )
        return;
      //      if (Input.GetKeyDown (KeyCode.W))
      //      {
      //        CLI.Debug ("Time {0}", _activeSource.time);
      //        CLI.Debug ("Clip {0}", _activeSource.clip.length);
      //      });
      if ( _activeSource.time >= _activeSource.clip.length && _lastStoppedTime == 0 )
        _lastStoppedTime = Time.realtimeSinceStartup;

      if ( _activeSource.time >= _activeSource.clip.length - _crossLength && _lastStoppedTime == 0
        //||
        //Immediately changing clips case.
        //_activeSource.time == 0 && _crossLength == 0
        //For Update thread sleep case.
          || _activeSource.time == 0 && _loop && !_activeSource.isPlaying && _lastStoppedTime == 0
        //Pause case
          || _lastStoppedTime != 0 && Time.realtimeSinceStartup > _lastStoppedTime + _pauseLength )
      {
        Switch();
      }
    }

    public void Switch()
    {
      AudioClip c = _playlist.GetNextTrack( _clips );
      if ( c == null && _loop )
      {
        _playlist.Reset();
        c = _playlist.GetNextTrack( _clips );
      }

      if ( c == null )
      {
        Debug.Log( "SoundChain completely ended. Use Loop parameter for auto repeating." );
        Clear();
        return;
      }
      AudioSource n = LaunchAudioSource( c );

      _switcher.Change( _activeSource, n, _crossLength );
      _previousSource = _activeSource;
      _activeSource = n;
      _lastStoppedTime = 0f;
      _audioSources.Add( _activeSource );
      if ( _activeSource == null )
        Clear();
    }

    private void Clear()
    {
      Sound.RegisterUnusedAudioSource( _previousSource );
      Sound.RegisterUnusedAudioSource( _activeSource );
      Destroy( this );
    }
  }
}
