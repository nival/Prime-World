using System;
using Flash.Utils; // WWWErrorEventArgs (контракт события OnError) живёт здесь
using UnityEngine;
using UnityEngine.Video;

namespace Flash
{
  // Миграция Unity 2018.4 -> 2019.4: MovieTexture (+WWW.GetMovieTexture) -> VideoPlayer.url.
  // VideoPlayer сам качает и проигрывает видео по URL (без WWW/MovieLoader), рендерит в RenderTexture,
  // который рисует базовый Loader через _FillTex. Источник: docs.unity3d.com VideoPlayer-MigratingFromMovieTexture.
  // ВНИМАНИЕ: VideoPlayer на Windows не играет Theora (.ogv/.ogg) по URL — для рабочего стрима видео
  // должно отдаваться как mp4 (H264)/webm (VP8).
  public class MediaPlayer : Loader
  {
    private Vector2 _positionCache;
    private string _video;

    private VideoPlayer _player;
    private RenderTexture _rt;
    private bool _prepared;
    private bool _requestPlay;
    private bool _waitingForFinish;

    public new bool IsPlaying
    {
      get { return _player != null && _player.isPlaying; }
    }

    private bool _fullScreenMode;
    public bool FullScreenMode
    {
      get { return _fullScreenMode; }
      set
      {
        if ( _fullScreenMode == value )
          return;

        if ( value )
        {
          GoToFullScreen();
          UniFlashPlayer.ResolutionChanged += OnResolutionChanged;
        }
        else
        {
          EscapeFromFullScreen();
          UniFlashPlayer.ResolutionChanged -= OnResolutionChanged;
        }
      }
    }
    private bool _fullScreenRequest;

    public float Duration
    {
      get { return _player != null ? (float) _player.length : 0f; }
    }

    public event MediaPlayerEventHandler Started;  //начало проигрывания видеоряда
    public event MediaPlayerEventHandler Paused;   //пользователь запаузил видео
    public event MediaPlayerEventHandler Stopped;  //пользователь нажал стоп
    public event MediaPlayerEventHandler Finished;
    public event MediaPlayerEventHandler EnterFullScreen;
    public event MediaPlayerEventHandler ExitFullScreen;
    public event EventHandler<WWWErrorEventArgs> OnError;

    public void Seed( string video )
    {
      if ( _video == video )
        return;

      _video = video;
      EnsurePlayer();
      _prepared = false;
      _player.source = VideoSource.Url;
      _player.url = video;
      _player.Prepare();
    }

    private void EnsurePlayer()
    {
      if ( _player != null )
        return;

      // Один VideoPlayer на инстанс MediaPlayer (инстанс — один на окно, живёт всё время приложения).
      GameObject go = new GameObject( "MediaPlayerVideo" );
      UnityEngine.Object.DontDestroyOnLoad( go );

      _player = go.AddComponent<VideoPlayer>();
      _player.playOnAwake = false;
      _player.isLooping = false;
      _player.renderMode = VideoRenderMode.RenderTexture;
      _player.audioOutputMode = VideoAudioOutputMode.AudioSource;
      _player.SetTargetAudioSource( 0, UniFlashPlayer.AudioSource );
      _player.prepareCompleted += OnPrepared;
      _player.errorReceived += OnVideoError;
      _player.loopPointReached += OnLoopPoint;
    }

    private void OnPrepared( VideoPlayer vp )
    {
      int w = (int) vp.width;
      int h = (int) vp.height;
      if ( w <= 0 ) w = 4;
      if ( h <= 0 ) h = 4;

      if ( _rt == null || _rt.width != w || _rt.height != h )
      {
        if ( _rt != null )
        {
          _rt.Release();
          UnityEngine.Object.Destroy( _rt );
        }
        _rt = new RenderTexture( w, h, 0, RenderTextureFormat.ARGB32 );
        _rt.Create();
        _player.targetTexture = _rt;
      }

      Load( _rt, _video ); // отдать RenderTexture в FlashUI (как раньше отдавали MovieTexture)
      _prepared = true;

      if ( _fullScreenRequest )
        GoToFullScreen();

      if ( _requestPlay )
        PlayMovie();
    }

    private void OnVideoError( VideoPlayer vp, string message )
    {
      if ( OnError != null )
        OnError( this, new WWWErrorEventArgs( message ) );
    }

    private void OnLoopPoint( VideoPlayer vp )
    {
      // isLooping == false -> событие = конец ролика
      if ( _waitingForFinish )
      {
        _waitingForFinish = false;
        if ( Finished != null )
          Finished( this, _video );
      }
    }

    public void PlayMovie()
    {
      if ( !_prepared || _player == null )
      {
        _requestPlay = true;
        return;
      }
      _requestPlay = false;
      _waitingForFinish = true;

      _player.Play();
      if ( Started != null )
        Started( this, _video );
    }

    public void PauseMovie()
    {
      _requestPlay = false;

      if ( _player == null )
        return;

      _waitingForFinish = false;

      _player.Pause();
      if ( Paused != null )
        Paused( this, _video );
    }

    public void StopMovie()
    {
      _requestPlay = false;

      if ( _player == null )
        return;

      _waitingForFinish = false;

      _player.Stop();
      if ( Stopped != null )
        Stopped( this, _video );
    }

    public override void PreRender()
    {
      if ( FullScreenMode )
        GL.Clear( false, true, Color.clear );

      base.PreRender();

      if ( FullScreenMode )
        _banDoRender = true;
    }

    private void GoToFullScreen()
    {
      if ( Texture == null )
      {
        _fullScreenRequest = true;
        return;
      }

      if ( !FullScreenMode )
      {
        _positionCache.x = X;
        _positionCache.y = Y;
      }

      if ( Texture.width >= Texture.height )
      {
        Width = UniFlashPlayer.Width;
        Height = Texture.height * ( Width / Texture.width );
        Position = Parent.GlobalToLocal( new Vector2( 0, UniFlashPlayer.Height / 2.0F - Height / 2 ) );
      }
      else
      {
        Height = UniFlashPlayer.Height;
        Width = Texture.width * ( Height / Texture.height );
        Position = Parent.GlobalToLocal( new Vector2( UniFlashPlayer.Width / 2.0F - Width / 2, 0 ) );
      }

      _fullScreenRequest = false;
      _fullScreenMode = true;

      if ( EnterFullScreen != null )
        EnterFullScreen( this, _video );
    }

    private void EscapeFromFullScreen()
    {
      Width = Texture.width;
      Height = Texture.height;
      X = _positionCache.x;
      Y = _positionCache.y;

      _fullScreenMode = false;

      if ( ExitFullScreen != null )
        ExitFullScreen( this, _video );
    }

    void OnResolutionChanged( object sender, ResolutionEventArgs e )
    {
      GoToFullScreen();
    }
  }

  public delegate void MediaPlayerEventHandler( MediaPlayer sender, string video );
}
