using UnityEngine;
using UnityEngine.Video;

namespace Flash
{
  // Миграция Unity 2018.4 -> 2019.4: замена removed-API MovieTexture.
  // Оборачивает VideoPlayer + RenderTexture и отдаёт RenderTexture как обычную Texture —
  // её рисует Loader через материал _FillTex ровно так же, как раньше рисовалась MovieTexture.
  // RenderTexture создаётся точного размера видео, поэтому legacy pow2-хак (Loader/MovieTexture) не нужен.
  // VideoClip берётся из .mp4 (H264) — он импортируется как VideoClip и на 2018.4, и на 2019.4,
  // поэтому путь единый (без #if). Источник паттерна: docs.unity3d.com VideoPlayer-MigratingFromMovieTexture.
  public class FlashVideoTexture
  {
    private static GameObject _host;

    private readonly GameObject _go;
    private readonly VideoPlayer _player;
    private readonly RenderTexture _rt;
    private System.Action _onReady;

    // RenderTexture, который рисует FlashUI (передаётся в ImageBox.InitProcedural / Loader.Texture).
    public Texture Texture { get { return _rt; } }
    public bool IsPlaying { get { return _player != null && _player.isPlaying; } }
    public double Duration { get { return _player != null ? _player.length : 0.0; } }

    public bool Loop
    {
      get { return _player != null && _player.isLooping; }
      set { if ( _player != null ) _player.isLooping = value; }
    }

    public FlashVideoTexture( VideoClip clip )
    {
      int w = clip != null && clip.width > 0 ? (int) clip.width : 4;
      int h = clip != null && clip.height > 0 ? (int) clip.height : 4;

      _rt = new RenderTexture( w, h, 0, RenderTextureFormat.ARGB32 );
      _rt.Create();

      _go = new GameObject( "FlashVideo" );
      _go.transform.SetParent( Host.transform, false );

      _player = _go.AddComponent<VideoPlayer>();
      _player.playOnAwake = false;
      _player.source = VideoSource.VideoClip;
      _player.clip = clip;
      _player.renderMode = VideoRenderMode.RenderTexture;
      _player.targetTexture = _rt;
      _player.audioOutputMode = VideoAudioOutputMode.None; // у видео-аватаров нет аудиодорожки (importAudio:0)
      _player.waitForFirstFrame = true;
      _player.errorReceived += HandleError;
    }

    private static void HandleError( VideoPlayer vp, string message )
    {
      Debug.LogError( "FlashVideoTexture [" + vp.gameObject.name + "]: " + message );
    }

    public void PlayWhenReady( System.Action onReady )
    {
      _onReady = onReady;
      _player.prepareCompleted += HandlePrepared;
      _player.Prepare();
    }

    private void HandlePrepared( VideoPlayer vp )
    {
      vp.prepareCompleted -= HandlePrepared;
      // Workaround (Unity 6 / Windows Media Foundation, одобрено Каримом 2026-07-03):
      // у свежесозданного VideoPlayer выводной пайплайн не подключается на первом проходе клипа
      // (time=0, frame=-1 при isPlaying=true вплоть до конца ролика) и оживает только на событии
      // лупа, которое пересобирает пайплайн. Поэтому стартуем с последнего кадра: луп срабатывает
      // в первые миллисекунды, и воспроизведение идёт сразу. Для зацикленных аватаров бесшовно.
      vp.frame = (long)vp.frameCount - 1;
      vp.Play();
      System.Action cb = _onReady;
      _onReady = null;
      cb();
    }

    public void Pause() { if ( _player != null ) _player.Pause(); }
    public void Stop()  { if ( _player != null ) _player.Stop(); }

    // Освобождение GPU-ресурсов: обязательно при снятии видео (вместо Resources.UnloadAsset для MovieTexture),
    // иначе RenderTexture'ы будут течь в видеопамяти.
    public void Release()
    {
      if ( _player != null )
        _player.Stop();

      if ( _rt != null )
      {
        _rt.Release();
        Object.Destroy( _rt );
      }

      if ( _go != null )
        Object.Destroy( _go );
    }

    private static GameObject Host
    {
      get
      {
        if ( _host == null )
        {
          _host = new GameObject( "__FlashVideoHost" );
          Object.DontDestroyOnLoad( _host );
        }
        return _host;
      }
    }
  }
}
