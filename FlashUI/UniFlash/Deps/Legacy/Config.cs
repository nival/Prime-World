using CastleTypes;
using NivalCLI;

namespace Lobby.Configs
{
#pragma warning disable 649
  public static class Config
  {
    private const string _socialConfigFileName = "config.cfg";
    public static string SocialConfigFileName
    {
      get { return _socialConfigFileName; }
    }

    private const string _sessionConfigFileName = "user.cfg";
    public static string SessionConfigFileName
    {
      get { return _sessionConfigFileName; }
    }

    [Config( "data_files", Scope.User )]
    private static string _dataFiles = "session.assets,sound.assets,loc.assets";
    public static string DataFiles
    {
      get { return _dataFiles; }
    }

    [Config( "pfx_enable", Scope.User )]
    private static bool _pfxenable = false;
    public static bool PFXEnable
    {
      get { return _pfxenable; }
    }

    [Config( "profiler_level", Scope.User )]
    private static int _profilerLevel = 0;
    public static int ProfilerLevel
    {
      get { return _profilerLevel; }
    }

    [Config("gc_period", Scope.User)]
    private static int _gcPeriod = 30;
    public static int GcPeriod
    {
      get { return _gcPeriod; }
    }

    [Config("gc_32_threshold", Scope.User)]
    private static long _gc32Threshold = 1100L * 1024 * 1024;
    public static long Gc32Threshold
    {
      get { return _gc32Threshold; }
    }

    [Config("gc_64_threshold", Scope.User)]
    private static long _gc64Threshold = 2049L * 1024 * 1024;
    public static long Gc64Threshold
    {
      get { return _gc64Threshold; }
    }

    [Config("video_postfix", Scope.User)]
    private static string _videoPostfix = "_m";
    public static string VideoPostfix
    {
      get { return _videoPostfix; }
    }

    [Config("animated_avatar_small_postfix", Scope.User)]
    private static string _animatedAvatarSmallPostfix = "_m78";
    public static string AnimatedAvatarSmallPostfix
    {
      get { return _animatedAvatarSmallPostfix; }
    }

    [Config("animated_avatar_medium_postfix", Scope.User)]
    private static string _animatedAvatarMediumPostfix = "_m89";
    public static string AnimatedAvatarMediumPostfix
    {
      get { return _animatedAvatarMediumPostfix; }
    }

    [Config("animated_avatar_big_postfix", Scope.User)]
    private static string _animatedAvatarBigPostfix = "_m112";
    public static string AnimatedAvatarBigPostfix
    {
      get { return _animatedAvatarBigPostfix; }
    }

    [Config( "sdofile", Scope.User )]
    private static string _sdofile = @"logic_overrides.py";
    public static string SdoFile
    {
      get { return _sdofile; }
    }


    [Config( "log_talent_roll_stats", Scope.User )]
    private static bool _logTalentsRoll = false;
    public static bool LogTalentsRoll
    {
      get { return _logTalentsRoll; }
    }

    [Config( "binary_profiler", Scope.User )]
    private static bool _binaryProfiler;
    public static bool BinaryProfiler
    {
      get { return _binaryProfiler; }
    }

    [Config( "offline_mode", Scope.User )]
    private static bool _offlineMode = false;
    public static bool OfflineMode
    {
      get { return _offlineMode; }
    }

    [Config( "offline_friends_count", Scope.User )]
    private static int _offlineFriendsCount = 8;
    public static int OfflineFriendsCount
    {
      get { return _offlineFriendsCount; }
    }

    [Config( "offline_no_fame", Scope.User )]
    private static bool _offlineNoFame = false;
    public static bool OfflineNoFame
    {
      get { return _offlineNoFame; }
    }

    [Config( "offline_friends_image_root", Scope.User )]
    private static string _offlineFriendsImageRoot = string.Empty;
    public static string OfflineFriendsImageRoot
    {
      get { return _offlineFriendsImageRoot; }
    }

    [Config( "pvp_map", Scope.User )]
    private static string _pvpMap = string.Empty;
    public static string PvpMap
    {
      get { return _pvpMap; }
    }

    [Config( "safe_wait_frame_before_session", Scope.User )]
    private static bool _waitForEndOfFrameBeforeSessionOSX = false;
    public static bool WaitForEndOfFrameBeforeSessionOSX
    {
      get { return _waitForEndOfFrameBeforeSessionOSX; }
    }

    [Config( "safe_pause_before_session", Scope.User )]
    private static float _pauseBeforeSessionOSX = 3f;
    public static float PauseBeforeSessionOSX
    {
      get { return _pauseBeforeSessionOSX; }
    }

    [Config( "login_queue_ui_update_interval", Scope.User )]
    private static int _loginQueueUIUpdateInterval = 1;
    public static int LoginQueueUIUpdateInterval
    {
      get { return _loginQueueUIUpdateInterval; }
    }

    [Config( "login_queue_poll_timeout", Scope.User )]
    private static float _loginQueuePollTimeOut = 5f;
    public static float LoginQueuePollTimeOut
    {
      get { return _loginQueuePollTimeOut; }
    }

    [Config( "emulate_queue_timer", Scope.User )]
    private static bool _emulateQueueTimer = false;
    public static bool EmulateQueueTimer
    {
      get { return _emulateQueueTimer; }
    }

    [Config( "update_secret_after_queue", Scope.User )]
    private static bool _updateSecretAfterQueue = true;
    public static bool UpdateSecretAfterQueue
    {
      get { return _updateSecretAfterQueue; }
    }

    [Config( "use_login_queue", Scope.User )]
    private static bool _useLoginQueue = false;
    public static bool UseLoginQueue
    {
      get { return _useLoginQueue; }
    }

    [Config( "queue_server", Scope.User )]
    private static string _queueServer = "login0";
    public static string QueueServer
    {
      get { return _queueServer; }
    }

    [Config( "matchmaiking_valid_check_timeout", Scope.User )]
    private static double _matchmaikingValidCheckTimeout = 10.0;
    public static double MatchmaikingValidCheckTimeout
    {
      get { return _matchmaikingValidCheckTimeout; }
    }

    [Config( "show_console", Scope.User )]
    private static bool _showConsole = false;
    public static bool ShowConsole
    {
      get { return _showConsole; }
    }

    [Config( "show_asserts_messages", Scope.User )]
    private static bool _showAssertsMessageBoxes = false;
    public static bool ShowAssertsMessageBoxes
    {
      get { return _showAssertsMessageBoxes; }
    }

    [Config( "pretty_json", Scope.User )]
    private static bool _prettyJson = false;
    public static bool PrettyJson
    {
      get { return _prettyJson; }
    }

    [Config( "show_grid", Scope.User )]
    private static bool _showGrid = false;
    public static bool ShowGrid
    {
      get { return _showGrid; }
    }

    [Config( "show_watermark", Scope.User )]
    private static bool _showWatermark = false;
    public static bool ShowWatermark
    {
      get { return _showWatermark; }
    }

    [Config( "show_ui", Scope.User )]
    private static bool _showUI = true;
    public static bool ShowUI
    {
      get { return _showUI; }
    }

    [Config( "show_visual_grades", Scope.User )]
    private static bool _showVisualGrades = true;
    public static bool ShowVisualGrades
    {
      get { return _showVisualGrades; }
    }

    [Config( "casual_control_style", Scope.User )]
    private static bool _casualControlStyle = true;
    public static bool CasualControlStyle
    {
      get { return _casualControlStyle; }
      set { _casualControlStyle = value; }
    }

    [Config("receive_regular_chat_messages", Scope.User)]
    private static bool _receiveRegularChatMessages = true;
    public static bool ReceiveRegularChatMessages
    {
      get { return _receiveRegularChatMessages; }
      set { _receiveRegularChatMessages = value; }
    }

    [Config("session_chat_off", Scope.User)]
    private static bool _sessionChatOff = false;
    public static bool SessionChatOff
    {
      get { return _sessionChatOff; }
      set { _sessionChatOff = value; }
    }

    [Config( "use_badwords_filter", Scope.User )]
    private static bool _useBadwordsFilter = true;
    public static bool UseBadWordsFilter
    {
      get { return _useBadwordsFilter; }
      set { _useBadwordsFilter = value; }
    }


    [Config( "network_delay_time", Scope.User )]
    private static int _networkDelayTime = 5;
    public static int NetworkDelayTimeout
    {
      get { return _networkDelayTime; }
    }

    [Config( "matchmaiking_session_reconnect_timeout", Scope.User )]
    private static int _matchmaikingSessionReconnectTimeout = 30;
    public static int MatchmaikingSessionReconnectTimeout
    {
      get { return _matchmaikingSessionReconnectTimeout; }
    }

    [Config( "party_join_timeout", Scope.User )]
    private static int _partyJoinTimeout = 30;
    public static int PartyJoinTimeout
    {
      get { return _partyJoinTimeout; }
    }

    [Config( "min_width", Scope.User )]
    private static int _minScreenWidth = 1024;
    public static int MinScreenWidth
    {
      get { return _minScreenWidth; }
    }

    [Config( "min_height", Scope.User )]
    private static int _minScreenHeight = 768;
    public static int MinScreenHeight
    {
      get { return _minScreenHeight; }
    }

    [Config( "min_win_width", Scope.User )]
    private static int _minWinScreenWidth = 1020;
    public static int MinWinScreenWidth
    {
      get { return _minWinScreenWidth; }
    }

    [Config( "min_win_height", Scope.User )]
    private static int _minWinScreenHeight = 760;
    public static int MinWinScreenHeight
    {
      get { return _minWinScreenHeight; }
    }

    [Config( "osx_window_height_offset", Scope.User )]
    private static int _OSXWindowHeightOffset = 100;
    public static int OSXWindowHeightOffset
    {
      get { return _OSXWindowHeightOffset; }
    }

    [Config( "video_tutorial_url", Scope.User )]
    private static string _videoTutorialUrl;
    public static string VideoTutorialUrl
    {
      get { return _videoTutorialUrl; }
    }

    [Config( "hqscreenshot_ext", Scope.User )]
    private static string _hqscreenshotExt = "png";
    public static string HQScreenshotExt
    {
      get { return _hqscreenshotExt; }
    }

    [Config( "screenshot_ext", Scope.User )]
    private static string _screenshotExt = "jpg";
    public static string ScreenshotExt
    {
      get { return _screenshotExt; }
    }

    [Config( "predefiend_fraction", Scope.User )]
    private static PlayerFraction _predefiendFraction = PlayerFraction.N;
    public static PlayerFraction PredefiendFraction
    {
      get { return _predefiendFraction; }
    }

    [Config( "default_nick_name", Scope.User )]
    private static string _defaultNickName;
    public static string DefaultNickName
    {
      get { return _defaultNickName; }
    }

    [Config( "castle_log_level", Scope.User )]
    private static NivalCLI.Log.Level _castleLogLevel = NivalCLI.Log.Level.Information | NivalCLI.Log.Level.Warning | NivalCLI.Log.Level.Error;
    public static NivalCLI.Log.Level CastleLogLevel
    {
      get { return _castleLogLevel; }
    }

    [Config( "freeze_scene", Scope.User )]
    private static bool _freezeScene = true;
    public static bool FreezeScene
    {
      get { return _freezeScene; }
    }

    [Config( "non_clickable_widget", Scope.User )]
    private static bool _nonClickableWidget = true;
    public static bool NonClickableWidget
    {
      get { return _nonClickableWidget; }
    }

    [Config( "www_timeout", Scope.User )]
    private static int _wwwTimeout = 30;
    public static int WwwTimeout
    {
      get { return _wwwTimeout; }
    }

    [Config( "block_steam_in_editor", Scope.User )]
    private static bool _blockSteamInEditor = true;
    public static bool BlockSteamInEditor
    {
      get { return _blockSteamInEditor; }
    }

    [Config( "steam_window_timeout", Scope.User )]
    private static int _steamWindowTimeout = 120;
    public static int SteamWindowTimeout
    {
      get { return _steamWindowTimeout; }
    }

    [Config( "steam_trans_timeout", Scope.User )]
    private static int _steamTransTimeout = 30;
    public static int SteamTransTimeout
    {
      get { return _steamTransTimeout; }
    }

    [Config( "aeria_trans_timeout", Scope.User )]
    private static int _aeriaTransTimeout = 30;
    public static int AeriaTransTimeout
    {
      get { return _aeriaTransTimeout; }
    }

    [Config( "emulate_aeria", Scope.User )]
    private static bool _emulateAeria = false;
    public static bool EmulateAeria
    {
      get { return _emulateAeria; }
    }

    [Config("gamigo_trans_timeout", Scope.User)]
    private static int _gamigoTransTimeout = 30;
    public static int GamigoTransTimeout
    {
      get { return _gamigoTransTimeout; }
    }

    [Config("emulate_gamigo", Scope.User)]
    private static bool _emulateGamigo = false;
    public static bool EmulateGamigo
    {
      get { return _emulateGamigo; }
    }

    [Config("arcgames_trans_timeout", Scope.User)]
    private static int _arcGamesTransTimeout = 30;
    public static int ArcGamesTransTimeout
    {
      get { return _arcGamesTransTimeout; }
    }

    [Config("emulate_arc_games", Scope.User)]
    private static bool _emulateArcGames = false;
    public static bool EmulateArcGames
    {
      get { return _emulateArcGames; }
    }

    [Config("zzima_trans_timeout", Scope.User)]
    private static int _zZimaTransTimeout = 30;
    public static int ZZimaTransTimeout
    {
      get { return _zZimaTransTimeout; }
    }

    [Config("emulate_zzima", Scope.User)]
    private static bool _emulateZZima = false;
    public static bool EmulateZZima
    {
      get { return _emulateZZima; }
    }

    [Config( "store_logs_days_count", Scope.User )]
    private static int _storeLogsDaysCount = 30;
    public static int StoreLogsDaysCount
    {
      get { return _storeLogsDaysCount; }
    }

    [Config( "screen_border_camera_scroll", Scope.User )]
    private static bool _screenBorderCameraScroll = true;
    public static bool ScreenBorderCameraScroll
    {
      get { return _screenBorderCameraScroll; }
    }

    [Config( "load_ui", Scope.User )]
    private static bool _loadUI = true;
    public static bool LoadUI
    {
      get { return _loadUI; }
    }

    [Config( "castle_data_daemon_max_message_size", Scope.User )]
    private static uint _castleDataDaemonMaxMessageSize = 256 * 1024;
    public static uint CastleDataDaemonMaxMessageSize
    {
      get { return _castleDataDaemonMaxMessageSize; }
    }

    [Config( "castle_data_daemon_max_messages_per_second", Scope.User )]
    private static uint _castleDataDaemonMaxMessagesPerSecond = 4;
    public static uint CastleDataDaemonMaxMessagesPerSecond
    {
      get { return _castleDataDaemonMaxMessagesPerSecond; }
    }

    [Config( "castle_data_daemon_stop_timeout", Scope.User )]
    private static float _castleDataDaemonStopTimeout= 2f;
    public static float CastleDataDaemonStopTimeout
    {
      get { return _castleDataDaemonStopTimeout; }
    }

    [Config( "castle_data_daemon_stop_timer_frequency", Scope.User )]
    private static float _castleDataDaemonStopTimerFrequency= 0.2f;
    public static float CastleDataDaemonStopTimerFrequency
    {
      get { return _castleDataDaemonStopTimerFrequency; }
    }

    [Config( "ignore_fatal_errors", Scope.User )]
    private static bool _ignoreFatalErrors = false;
    public static bool IgnoreFatalErrors
    {
      get { return _ignoreFatalErrors; }
    }

    #region Login

    [Config( "login_address", Scope.User )]
    private static string _gameServerHost = "NOT SET!";
    public static string GameServerHost
    {
      get { return _gameServerHost; }
    }

    [Config( "guest_autologin", Scope.User )]
    private static bool _guestAutologin = false;
    public static bool GuestAutologin
    {
      get { return _guestAutologin; }
    }

    [Config( "use_test_login", Scope.User )]
    private static bool _useTestLogin = false;
    public static bool UseTestLogin
    {
      get { return _useTestLogin; }
    }

    [Config( "guest_gender", Scope.User )]
    private static EGender _guestGender = EGender.Male;
    public static EGender GuestGender
    {
      get { return _guestGender; }
    }

    #endregion

    #region Social authorization

    [Config( "sn_id", Scope.User )]
    private static string _snId;
    public static string SnId
    {
      get { return _snId; }
    }

    [Config( "sn_uid", Scope.User )]
    private static string _snUid;
    public static string SnUid
    {
      get { return _snUid; }
    }

    [Config( "server_name", Scope.User )]
    private static string _serverName;
    public static string ServerName
    {
      get { return _serverName; }
    }

    [Config( "sn_token", Scope.User )]
    private static string _snToken;
    public static string SnToken
    {
      get { return _snToken; }
    }

    #endregion

    [Config( "banned_hosts", Scope.User )]
    private static string _bannedHosts = string.Empty;
    public static string BannedHosts
    {
      get { return _bannedHosts; }
    }

    [Config( "responce_time", Scope.User )]
    private static int _responceTime;
    public static int ResponceTime
    {
      get { return _responceTime; }
    }

    [Config( "disable_pvx_transition", Scope.User )]
    private static bool _disablePvxTransition = UnityEngine.Application.isEditor;
    public static bool DisablePvxTransition
    {
      get { return _disablePvxTransition; }
    }

    [Config( "disable_tutor_pvx_transition", Scope.User )]
    private static bool _disableTutorPvxTransition = false;
    public static bool DisableTutorPvxTransition
    {
      get { return _disableTutorPvxTransition; }
    }

    [Config( "hide_Start_Screen_Timeout", Scope.User )]
    private static int _hideStartScreenTimeout = 60;
    public static int HideStartScreenTimeout
    {
      get { return _hideStartScreenTimeout; }
    }

    [Config("web_im_website_url", Scope.User)]
    private static string _webIMUrl = string.Empty;
    public static string WebImUrl
    {
      get { return _webIMUrl; }
    }

    [Config("cursor_mode", Scope.User)]
    private static int _cursor_mode = 2;
    public static int cursor_mode
    {
      get 
      {
        return _cursor_mode;
      }
    }

    [Config("force_castle_exit_on_pvx", Scope.User)]
    private static bool _force_castle_exit_on_pvx = false;
    public static bool force_castle_exit_on_pvx
    {
      get { return _force_castle_exit_on_pvx; }
      set { _force_castle_exit_on_pvx = value; }
    }

    [Config("full_requests_log", Scope.User)]
    private static bool _full_requests_log = false;
    public static bool full_requests_log
    {
      get { return _full_requests_log; }
      set { _full_requests_log = value; }
    }
    
  }
}
