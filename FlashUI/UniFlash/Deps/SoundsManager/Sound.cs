using System;
using System.Collections.Generic;
using NivalCLI;
using Unity.Components.SoundsManager.Chains;
using Unity.Components.SoundsManager.Core;
using Unity.Components.SoundsManager.Effects;
using Unity.Components.SoundsManager.Tools;
using UnityEngine;
using Object = UnityEngine.Object;
using Resources = ResourcesManager.Resources;

namespace Unity.Components.SoundsManager
{
  /// <summary>
  /// Controls sounds of UI.
  /// </summary>
  public static class Sound
  {
    #region Public constants
    public const float ASK_SWITCHING_FADE_LENGTH = 0.2f;
    public const float MUSIC_FADE_LENGTH = 2f;
    public const float TAMBUR_MUSIC_FADE_K = 0f;
    public const float GOLDEN_AGE_MUSIC_SILENT_PERIOD = 6f;
    #endregion

    #region Sounds (Constant names setted in UI SoundsList prefab by Audio Designer)
    public const string NoSound = "";
    public const string LevelUp = "LevelUp";
    public const string ConstructionLevelUp = "ConstructionLevelUp";
    public const string Click = "Click";
    public const string Gong = "Gong";
    public const string UiOpenSmall = "UiOpenSmall";
    public const string UiClose = "UiClose";
    public const string MMFound = "MMFound";
    public const string UiOpenBig = "UiOpenBig";
    public const string ResourcesGathering = "ResourcesGathering";
    public const string ButtonCancelSmall = "ButtonCancelSmall";
    public const string Tambur = "Tambur";
    public const string GoldenAge = "GoldenAge";
    public const string GoldenAgeStart = "GoldenAgeStart";
    public const string CameraFlight = "CameraFlight";
    public const string GoldCoins = "GoldCoins";
    public const string PrivateMessage = "PrivateMessage";
    public const string GroupInvite = "GroupInvite";

    // Reroll Shop sounds
    public const string RerollShopReroll = "RerollShopReroll";
    public const string RerollShopOver = "RerollShopOver";
    public const string RerollShopOverEpic = "RerollShopOverEpic";
    public const string RerollShopBuy = "RerollShopBuy";
    public const string RerollShopBuyEpic = "RerollShopBuyEpic";

    #region Resources
    public const string Resource1Collected = "Resource1Collected";
    public const string Resource2Collected = "Resource2Collected";
    public const string Resource3Collected = "Resource3Collected";

    public const string CrystalCollected = "CrystalCollected";
    public const string SilverCollected = "SilverCollected";
    public const string GoldCollected = "GoldCollected";
    public const string PopulationCollected = "PopulationCollected";
    #endregion

    #region Quests
    public const string MissionComplete = "MissionComplete";
    public const string QuestRewardAchieved = "QuestRewardAchieved";
    public const string QuestActorChecked = "QuestActorChecked";
    #endregion

    #region Constructions
    public const string BuildingEffectA = "BuildingEffectA";
    public const string BuildingEffectB = "BuildingEffectB";
    public const string DestructionEffectA = "DestructionEffectA";
    public const string DestructionEffectB = "DestructionEffectB";
    public const string VisualUpgradeEffect = "VisualUpgradeEffect";
    #endregion

    #region Effects
    public const string ExpansionEffect = "ExpansionEffect";
    #endregion
    #endregion

    #region Chains (Paths begins from UISoundsListPrefabPath)
    public const string Credits = "Credits";
    public const string MainTheme = "MainTheme";
    public const string FactionSelectionAmbientSounds = "FactionSelectionAbmientSounds";
    #endregion

    private const string SoundsBaseGameObjectName = "_runtime_2DSoundsBase";
    private const string AmbientMapSoundsTag = "AmbientSounds";
    private const string UISoundsListPrefabPath = "Prefabs/Sound/UISoundsList";
    private const string SoundConfigPrefabPath = "Prefabs/Sound/SoundConfig";


    private static float _musicVolume = 1f;
    private static float _musicVolumeCached = 1f;
    private static float _musicVolumeFadeCached = 1f;
    private static int _musicFadesCount = 0;

    private const float FADE_LENGTH = 1.5f;
    private const float FADE_TO_COEFF = 0.4f;

    public static float MusicVolume
    {
      get { return _musicVolume; }
      set
      {
        if ( _musicVolume != value )
        {
          _musicVolumeCached = _musicVolume;
          _musicVolume = Mathf.Clamp01( value );
          _musicVolumeFadeCached = _musicVolume;
          SetMusicVolume( _musicVolume );
        }
      }
    }

    private static float _voiceVolume = 1f;
    private static float _voiceVolumeCached = 1f;
    public static float VoiceVolume
    {
      get { return _voiceVolume; }
      set
      {
        if ( _voiceVolume != value )
        {
          _voiceVolumeCached = _voiceVolume;
          _voiceVolume = Mathf.Clamp01( value );
          SetVoiceVolume( _voiceVolume );
        }
      }
    }

    private static float _uiVolume = 1f;
    private static float _uiVolumeCached = 1f;
    public static float UIVolume
    {
      get { return _uiVolume; }
      set
      {
        if ( _uiVolume != value )
        {
          _uiVolumeCached = _uiVolume;
          _uiVolume = Mathf.Clamp01( value );
          SetUIVolume( _uiVolume );
        }
      }
    }

    private static SoundConfig _config;
    public static SoundConfig Config
    {
      get
      {
        if ( _config == null )
        {
          GameObject prefab = Resources.Load( SoundConfigPrefabPath ) as GameObject;
          if ( prefab != null )
          {
            _config = prefab.GetComponent<SoundConfig>();
          }
          else
            CLI.Warning( "SoundConfig prefab not found at '{0}'", UISoundsListPrefabPath );

          if ( _config == null )
          {
            CLI.Warning( "SoundConfig component not found on prefab at '{0}'. Using default paramters.", SoundConfigPrefabPath );
            GameObject go = new GameObject( "_SoundConfig" );
            _config = go.AddComponent<SoundConfig>();
          }
        }
        return _config;
      }
    }

    private static List<AudioSource> _uiSources = new List<AudioSource>();
    private static List<AudioSource> _musicSources = new List<AudioSource>();
    private static List<AudioSource> _musicAFSources = new List<AudioSource>();
    private static List<AudioSource> _voiceSources = new List<AudioSource>();
    private static List<AudioSource> _fadedMusicSources = new List<AudioSource>();

    /// <summary>
    /// Pools for unused AudioSources
    /// 2D sources stored and reused from _unusedAudioSources
    /// </summary>
    private static List<AudioSource> _unusedAudioSources = new List<AudioSource>();
    /// <summary>
    /// 3D sources and gameObjects stored and reused from _unused3DAudioSources
    /// </summary>
    private static List<AudioSource> _unused3DAudioSources = new List<AudioSource>();

    private static string _audioClipsResourcesRoot = "Sound/";
    public static string AudioClipsResourcesRoot
    {
      get { return _audioClipsResourcesRoot; }
      set { _audioClipsResourcesRoot = value; }
    }

    private static GameObject _2dChannelsBase;
    public static GameObject BaseGameObject
    {
      get
      {
        if ( _2dChannelsBase == null )
        {
          _2dChannelsBase = FindOrCreateGameObject( SoundsBaseGameObjectName );
        }
        return _2dChannelsBase;
      }
    }

    /// <summary>
    /// Using for SoundsList prefab data access
    /// </summary>
    private static Dictionary<string,AudioClip> _uiSoundsList;
    public static Dictionary<string, AudioClip> UISoundsList
    {
      get
      {
        if ( _uiSoundsList == null )
        {
          _uiSoundsList = new Dictionary<string, AudioClip>();
          //Loading UiSundsList prefab
          GameObject uiSoundsListGO = Resources.Load( UISoundsListPrefabPath ) as GameObject;
          if ( uiSoundsListGO != null )
          {
            SoundsList uiSoundsList = uiSoundsListGO.GetComponent<SoundsList>();
            if ( uiSoundsList != null )
              _uiSoundsList = uiSoundsList.GetItems();
            else
              CLI.DataAssert( "SoundsList not found on UISoundList prefab at '{0}'", UISoundsListPrefabPath );
          }
          else
            CLI.DataAssert( "SoundsList prefab not found at '{0}'", UISoundsListPrefabPath );
        }
        return _uiSoundsList;
      }
    }

    private static GameObject FindOrCreateGameObject( string name )
    {
      GameObject result;
      result = GameObject.Find( name );
      if ( result != null )
      {
        CLI.Debug( "Sounds base succesfully found on stage" );
        return result;
      }

      result = new GameObject( name );
      //_2dChannelsBase.AddComponent<SafeObjectDestroyer>();
      //Object.DontDestroyOnLoad( _2dChannelsBase );
      CLI.Debug( "Sound component succesfully created" );
      return result;
    }

    #region Ambient Enviroment sounds
    private static Dictionary<AudioSource, float> _ambientMapSounds;
    public static Dictionary<AudioSource, float> CollectAndSetAmbientMapSounds()
    {
      Dictionary<AudioSource, float> result = new Dictionary<AudioSource, float>();
      GameObject[] gos = GameObject.FindGameObjectsWithTag( AmbientMapSoundsTag );
      foreach ( GameObject go in gos )
      {
        AudioSource[] sources = go.GetComponentsInChildren<AudioSource>();
        foreach ( AudioSource source in sources )
        {
          result.Add( source, source.volume );
        }
      }
      return result;
    }

    public static void PlayAmbientMapSounds()
    {
      if ( _ambientMapSounds == null )
        _ambientMapSounds = CollectAndSetAmbientMapSounds();

      foreach ( var pair in _ambientMapSounds )
      {
        pair.Key.volume = pair.Value * _uiVolume;
        if ( pair.Key != null )
          pair.Key.Play();
      }
    }

    #endregion

    #region Volume
    private static void SetMusicVolume( float volume )
    {
      foreach ( AudioSource s in _musicSources )
        if ( s != null && s.isPlaying && !_fadedMusicSources.Contains( s ) )
          s.volume = volume;

      foreach ( AudioSource s in _musicAFSources )
        if ( s != null && s.isPlaying )
          s.volume = volume;
    }
    private static void SetUIVolume( float volume )
    {
      foreach ( AudioSource s in _uiSources )
        if ( s != null && s.isPlaying )
          s.volume = volume;

      if ( _ambientMapSounds != null )
        foreach ( var pair in _ambientMapSounds )
        {
          if ( pair.Key != null && pair.Key.isPlaying )
            pair.Key.volume = pair.Value * volume; //Mathf.MoveTowards( 0, pair.Value, volume );
        }
    }
    private static void SetVoiceVolume( float volume )
    {
      foreach ( AudioSource s in _voiceSources )
        if ( s != null && s.isPlaying )
          s.volume = volume;
    }


    public static void MuteAll()
    {
      MusicVolume = 0f;
      UIVolume = 0f;
      VoiceVolume = 0f;
    }
    public static void UnmuteAll()
    {
      if ( _musicVolume == 0f )
        MusicVolume = _musicVolumeCached;
      if ( _uiVolume == 0f )
        UIVolume = _uiVolumeCached;
      if ( _voiceVolume == 0f )
        VoiceVolume = _voiceVolumeCached;
    }

    public static void Mute( SourceType channelType )
    {
      if ( channelType == SourceType.Music || channelType == SourceType.MusicAvoidingFade )
      {
        MusicVolume = 0f;
      }
      else if ( channelType == SourceType.UI )
      {
        UIVolume = 0f;
      }
      else if ( channelType == SourceType.Voice )
      {
        VoiceVolume = 0f;
      }

    }
    public static void UnMute( SourceType channelType )
    {
      if ( channelType == SourceType.Music || channelType == SourceType.MusicAvoidingFade )
      {
        if ( _musicVolume == 0f )
          MusicVolume = _musicVolumeCached;
      }
      else if ( channelType == SourceType.UI )
      {
        if ( _uiVolume == 0f )
          UIVolume = _uiVolumeCached;
      }
      else if ( channelType == SourceType.Voice )
      {
        if ( _voiceVolume == 0f )
          VoiceVolume = _voiceVolumeCached;
      }
    }

    public static void FadeInMusicVolume( float fadeLength )
    {
      _musicFadesCount--;
      if ( _musicFadesCount != 0 )
        return;
      //CLI.Warning( "!!!In from {0} to {1}", _musicVolume, _musicVolumeFadeCached );
      _musicVolume = _musicVolumeFadeCached;
      foreach ( AudioSource s in _musicSources )
        if ( s != null && s.isPlaying )
        {
          Fade.Create( s, FadeType.In, fadeLength, false );
          if ( _fadedMusicSources.Contains( s ) )
            _fadedMusicSources.Remove( s );
        }
    }
    public static void FadeOutMusicVolume( float fadeLength )
    {
      FadeOutMusicVolume( fadeLength, FADE_TO_COEFF );
    }

    public static void FadeOutMusicVolume( float fadeLength, float fadeK )
    {
      _musicFadesCount++;
      if ( _musicFadesCount > 1 )
        return;
      _musicVolumeFadeCached = _musicVolume;
      _musicVolume *= fadeK;
      for ( int i =0; i < _musicSources.Count; i++ )
      {
        AudioSource s = _musicSources[i];
        if ( s != null && s.isPlaying )
        {
          Fade.Create( s, FadeType.Out, fadeLength, _musicVolume, false );
          if ( !_fadedMusicSources.Contains( s ) )
            _fadedMusicSources.Add( s );
        }
      }
      //CLI.Warning( "!!!Out from {0} to {1}", _musicVolumeFadeCached, _musicVolume );
      //foreach ( AudioSource s in _musicSources )

    }
    #endregion

    #region Pause
    public static void PauseMusic()
    {
      foreach ( AudioSource s in _musicSources )
        if ( s != null && s.isPlaying )
          s.Pause();

      foreach ( AudioSource s in _musicAFSources )
        if ( s != null && s.isPlaying )
          s.Pause();
    }
    public static void UnPauseMusic()
    {
      foreach ( AudioSource s in _musicSources )
        if ( s != null && !s.isPlaying && s.timeSamples != 0 )
          s.Play();

      foreach ( AudioSource s in _musicAFSources )
        if ( s != null && !s.isPlaying && s.timeSamples != 0 )
          s.Play();
    }

    public static void PauseUI()
    {
      foreach ( AudioSource s in _uiSources )
        if ( s != null && s.isPlaying )
          s.Pause();

      if ( _ambientMapSounds != null )
        foreach ( var pair in _ambientMapSounds )
        {
          if ( pair.Key != null && pair.Key.isPlaying )
            pair.Key.Pause();
        }
    }
    public static void UnPauseUI()
    {
      foreach ( AudioSource s in _uiSources )
        if ( s != null && !s.isPlaying && s.timeSamples != 0 )
          s.Play();

      if ( _ambientMapSounds != null )
        foreach ( var pair in _ambientMapSounds )
        {
          if ( pair.Key != null && !pair.Key.isPlaying && pair.Key.timeSamples != 0 )
            pair.Key.Play();
        }
    }

    #endregion

    private static void ShowDebugInfo( AudioSource audioSource, bool full )
    {
      Debug.Log( "time sec " + audioSource.time );
      Debug.Log( "time samples " + audioSource.timeSamples );
      Debug.Log( "time samples sec " + (float)audioSource.timeSamples / audioSource.clip.frequency );
      if ( !full )
        return;
      Debug.Log( "Length sec " + audioSource.clip.length );
      Debug.Log( "Length samples " + audioSource.clip.samples );
      Debug.Log( "Length samples sec " + (float)audioSource.clip.samples / audioSource.clip.frequency );
    }

    /// <summary>
    /// Plays audio clip at specified channel
    /// </summary>
    /// <param name="clip">Clip</param>
    /// <param name="responseCallback">Clip play ended callback</param>
    /// <param name="startDelay">Delay on start in seconds</param>
    /// <param name="sourceType">Playing channel</param>
    /// <returns></returns>
    public static IAudioSourceController PlaySoundAtChannel( AudioClip clip, Action responseCallback,
float startDelay, SourceType sourceType )
    {
      if ( clip == null )
      {
        CLI.DataAssert( "Attempt to play null AudioClip." );
        return null;
      }
      AudioSource s = CreateAudioSource( sourceType );

      s.clip = clip;
      s.loop = false;
      if ( startDelay == 0 )
        s.Play();

      return AudioSourceCleaner.Create( s, responseCallback, startDelay );
    }
    /// <summary>
    /// Attempts to load audioclip from UIConfig or from Resources. 
    /// If not found null will be returned.
    /// </summary>
    /// <param name="clipName">Clipname or path from Resources/Sound/</param>
    /// <returns></returns>
    private static AudioClip TryToLoadAudioClip( string clipName )
    {
      //CLI.Debug( "Playing UI sound: {0}", clipName );
      if ( string.IsNullOrEmpty( clipName ) )
      {
        CLI.Debug( "Trying to play audio clip with empty name." );
        return null;
      }
      AudioClip clip;
      if ( !UISoundsList.TryGetValue( clipName, out clip ) )
      {
        clip = Resources.Load( _audioClipsResourcesRoot + clipName ) as AudioClip;
        if ( clip == null )
        {
          CLI.DataAssert( "Can't play sound {0}. File not found in UISoundsList and in Resources or has invalid format.", _audioClipsResourcesRoot + clipName );
          return null;
        }
      }
      return clip;
    }

    /// <summary>
    /// Reports about unused audio source. Source will be cleared, reseted and using again in next call.
    /// There are 2 pools: for 3D gameObjects+AudioSource component and for 2D AudioSource components
    /// </summary>
    /// <param name="source"></param>
    internal static void RegisterUnusedAudioSource( AudioSource source )
    {
      if ( source == null )
        return;

      if ( _musicSources.Contains( source ) )
        _musicSources.Remove( source );
      if ( _uiSources.Contains( source ) )
        _uiSources.Remove( source );
      if ( _voiceSources.Contains( source ) )
        _voiceSources.Remove( source );
      if ( _musicAFSources.Contains( source ) )
        _musicAFSources.Remove( source );
      if ( _fadedMusicSources.Contains( source ) )
        _fadedMusicSources.Remove( source );

      if ( source.isPlaying )
        source.Stop();

      source.clip = null;
      source.enabled = false;
      if ( source.gameObject == BaseGameObject && !_unusedAudioSources.Contains( source ) )
        _unusedAudioSources.Add( source );
      else if ( source.gameObject != BaseGameObject && !_unused3DAudioSources.Contains( source ) )
      {
        source.gameObject.SetActive(false);
        _unused3DAudioSources.Add( source );
      }
    }

    /// <summary>
    /// Trying to get AudioSource from unused pools. 
    /// If found source will be enabled and ready to work.
    /// </summary>
    /// <param name="is3D">Is AudioSource compnent attached to separated GameObject. Often using for 3D sounds.</param>
    /// <param name="source">Result</param>
    /// <returns>Is source found</returns>
    private static bool GetFromUnused( bool is3D, out AudioSource source )
    {
      List<AudioSource> pool;
      if ( is3D )
        pool = _unused3DAudioSources;
      else
        pool = _unusedAudioSources;

      if ( pool != null && pool.Count != 0 && pool[0] != null )
      {
        source = pool[0];
        source.enabled = true;
        source.gameObject.SetActive(true);
        pool.Remove( source );
        return true;
      }
      source = null;
      return false;
    }

    public static AudioSource CreateAudioSource( SourceType type )
    {
      AudioSource result;
      if ( !GetFromUnused( false, out result ) )
        result = BaseGameObject.AddComponent<AudioSource>();

      result.enabled = true;
      result.playOnAwake = false;
      TuneVolumeAndAddToChannelsList( result, type );
      return result;
    }

    public static AudioSource Create3DAudioSourceAtPoint( SourceType type, Vector3 position )
    {
      GameObject resultBase;
      AudioSource result;
      if ( !GetFromUnused( true, out result ) )
      {
        resultBase = new GameObject( "_runtime_3DSoundBaseObject" );
        result = resultBase.gameObject.AddComponent<AudioSource>();
      }
      resultBase = result.gameObject;

      //TODO: position is not used?
      //resultBase.transform.position = position;
      result.enabled = true;
      resultBase.SetActive(true);
      result.rolloffMode = AudioRolloffMode.Linear;

      result.playOnAwake = false;
      TuneVolumeAndAddToChannelsList( result, type );

      return result;
    }

    /// <summary>
    /// Link AudioSource with associated channel and sets actual volume
    /// </summary>
    /// <param name="source"></param>
    /// <param name="type"></param>
    private static void TuneVolumeAndAddToChannelsList( AudioSource source, SourceType type )
    {
      if ( type == SourceType.Music )
      {
        source.volume = _musicVolume;
        _musicSources.Add( source );
      }
      else if ( type == SourceType.UI )
      {
        source.volume = _uiVolume;
        _uiSources.Add( source );
      }
      else if ( type == SourceType.Voice )
      {
        source.volume = _voiceVolume;
        _voiceSources.Add( source );
      }
      else if ( type == SourceType.MusicAvoidingFade )
      {
        source.volume = _musicVolumeFadeCached;
        _musicAFSources.Add( source );
      }
      else
      {
        CLI.Warning( @"Trying to call TuneVolumeAndAddToChannelsList with unknown SourceType. 
        Please, check that for recently added SourceType sounds list and volume parameter defined." );
      }
    }

    private static void OnAudioSourceCleared( IAudioSourceController source )
    {
      if ( source != null )
        source.AudioSourceCleared -= OnAudioSourceCleared;
      FadeInMusicVolume( FADE_LENGTH );
    }


    #region Play UI 2D from SoundsList or form Resources
    public static IAudioSourceController PlayUI( string clipName )
    {
      return PlayUI( clipName, null, 0f );
    }

    public static IAudioSourceController PlayUI( string clipName, float startDelay )
    {
      return PlayUI( clipName, null, startDelay );
    }

    public static IAudioSourceController PlayUI( string clipName, Action responseCallback )
    {
      return PlayUI( clipName, responseCallback, 0f );
    }

    public static IAudioSourceController PlayUI( string clipName, Action responseCallback, float startDelay )
    {
      AudioClip clip = TryToLoadAudioClip( clipName );
      if ( clip == null )
        return null;
      return PlayUI( clip, responseCallback, startDelay );
    }
    #endregion

    #region Play UI 2D by resource
    public static IAudioSourceController PlayUI( AudioClip clip )
    {
      return PlayUI( clip, null, 0 );
    }

    public static IAudioSourceController PlayMusic( string clipName )
    {
      AudioClip clip = TryToLoadAudioClip( clipName );
      if ( clip == null )
        return null;
      return PlaySoundAtChannel( clip, null, 0, SourceType.Music );
    }

    public static IAudioSourceController PlayUI( AudioClip clip, Action responseCallback, float startDelay )
    {
      return PlaySoundAtChannel( clip, responseCallback, startDelay, SourceType.UI );
    }
    #endregion

    #region Play 3D UI from SoundsList
    public static IAudioSourceController Play3DUISound( string clipName, Vector3 position )
    {
      return Play3DUISound( clipName, position, null );
    }

    public static IAudioSourceController Play3DUISound( string clipName, Vector3 position, Action responseCallback )
    {
      if ( string.IsNullOrEmpty( clipName ) )
      {
        CLI.Debug( "Trying to play audio clip with empty name." );
        return null;
      }
      AudioClip clip;
      if ( !UISoundsList.TryGetValue( clipName, out clip ) )
      {
        CLI.DataAssert( "Can't play 3D UI sound {0}. Key not presented in UI SoundsList.", clipName );
        return null;
      }
      AudioSource s = Create3DAudioSourceAtPoint( SourceType.UI, position );
      Processor.PlaySound( s, clip );
      return AudioSourceCleaner.Create( s, responseCallback );
    }
    #endregion

    #region Music
    /// <summary>
    /// Plays music channel audio clip which will be ignore fade volume changes.
    /// </summary>
    /// <param name="clipName">ClipName form UIConfig or relative path to clip from Resources/Sound</param>
    /// <returns></returns>
    public static IAudioSourceController PlayMusicAvoidingFade( string clipName )
    {
      AudioClip clip = TryToLoadAudioClip( clipName );
      if ( clip == null )
        return null;


      return PlaySoundAtChannel( clip, null, 0f, SourceType.MusicAvoidingFade );
    }
    #endregion

    #region Voice
    public static IAudioSourceController PlayVoice( string clipName )
    {
      return PlayVoice( clipName, null );
    }

    public static IAudioSourceController PlayVoice( string clipName, Action responseCallback )
    {
      AudioClip clip = Resources.Load( _audioClipsResourcesRoot + clipName ) as AudioClip;
      if ( clip == null )
      {
        CLI.DataAssert( "Can't play sound {0}. File not found or invalid format.", _audioClipsResourcesRoot + clipName );
        return null;
      }
      /// if resources.assets.resS file was missed
      if ( clip.length == 0 )
        return null;

      FadeOutMusicVolume( FADE_LENGTH );
      IAudioSourceController auc = PlaySoundAtChannel( clip, responseCallback, 0f, SourceType.Voice );
      auc.AudioSourceCleared += OnAudioSourceCleared;

      return auc;
    }
    #endregion

    #region Chains (number of clips playing consistently with some switching rules)
    public static SoundsChain PlayChain( string clipFolderName, float crossLength, float pauseLength )
    {
      string path = _audioClipsResourcesRoot + clipFolderName;
      if ( string.IsNullOrEmpty( clipFolderName ) )
        path = _audioClipsResourcesRoot.TrimEnd( '/', '\\' ) + clipFolderName;

      Object[] loaded = Resources.LoadAll( path );
      List<AudioClip> clips = new List<AudioClip>();
      foreach ( Object obj in loaded )
      {
        if ( ( obj as AudioClip ) != null )
          clips.Add( obj as AudioClip );
      }

      if ( clips == null || clips.Count == 0 )
      {
        CLI.DataAssert( "Clips for chain playing not found. Check directory for existing files and right AudioClip format", path );
        return null;
      }

      SoundsChain s = SoundsChain.Create( clips, new CrossFade(), new NameOrderedNotRepeat(), crossLength, pauseLength, false, true );
      s.Launch();
      return s;
    }

    public static SoundsChain PlayChain( List<string> clipNames, float crossLength, float pauseLength, bool loop, float startFade, float startTime )
    {
      List<AudioClip> clips = new List<AudioClip>();
      foreach ( string clipName in clipNames )
      {
        AudioClip c = TryToLoadAudioClip( clipName );
        if ( c != null )
          clips.Add( c );
      }

      if ( clips.Count == 0 )
      {
        return null;
      }
      SoundsChain s = SoundsChain.Create( clips, new CrossFade(), new RandomNotRepeat(), crossLength, pauseLength, false, loop );
      s.Launch( startFade, startTime );
      return s;
    }

    public static SoundsChain PlayChain( List<string> clipNames, float crossLength, float pauseLength, bool loop, float startFade )
    {
      return PlayChain( clipNames, crossLength, pauseLength, loop, startFade, 0f );
    }

    public static SoundsChain PlayChain( List<string> clipNames, float crossLength, float pauseLength, bool loop )
    {
      return PlayChain( clipNames, crossLength, pauseLength, loop, 0f, 0f );
    }
    #endregion

  }
}