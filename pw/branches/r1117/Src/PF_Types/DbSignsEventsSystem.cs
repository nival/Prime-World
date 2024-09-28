//#include "../Types/Sound.cs"

using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Sound.DBSound;

namespace PF_GameLogic.DBStats
{
  //==========================================================================================================================================
  public enum EMessage
  {
    [Description("Sign message. This message will be send to almost all players.")]
    SIMPLE_MESSAGE,

    [Description("This is the second message for linear feat. When the hero is continuing the feat.")]
    LINEAR_FEAT_MESSAGE,

    [Description("Sign message. This message is only for Priestess who blessed the hero for the feat. Will be processed for signParticipants = ALL_PLAYERS_WITHOUT_PRIESTESS type only.")]
    ONLY_FOR_PRIESTESS_MESSAGE
  }

  //==========================================================================================================================================
  public enum ERecipients
  {
    [Description("This message is only for participants of current event.")]
    EVENT_PARTICIPANTS,

    [Description("This message is only for the team of player who made the current event.")]
    EVENT_MAKER_TEAM,

    [Description("This message is only for the opposite team of player who made the current event.")]
    EVENT_MAKER_OPPOSITE_TEAM,

    [Description("This message is for all players.")]
    ALL_PLAYERS,

    [Description("This message is for all players except the priestess who has blessed the hero for this feat/event.")]
    ALL_PLAYERS_WITHOUT_PRIESTESS,

    [Description("This message only for player")]
    PLAYER_ONLY,

    [Description("Take recipients from UIEvent (only for UISign)")]
    USE_FROM_PARENT,
  }

  //==========================================================================================================================================
  //possible signs for event in the adventure screen
  public enum ESign
  {
    NONE,
    SEND_MESSAGE_TO_CHAT,
    SEND_MESSAGE_TO_STATUS_LINE,
    PLAY_SOUND,
    FLYOFF_TEXT,
    ANNOUNCEMENT,
    //....to be continue
  }

  public enum EFlyOffAlign
  {
      Left,
      Center,
      Right,
  }

  public enum EAnnouncementType
  {
    PlayerKilled,
    Achievment,
    TowerDestroyed,
    SpawnSuperCreeps,
    PlayerLeft,
    PlayerReconnected,
    QuestRecieved,
    QuestComplete,
    EggAnnouncement,
    SuperSiegeSpawned,
    CustomAnnouncement,
  }

  //==========================================================================================================================================
  [TypeId(0xB6C5300)]
  public class FlyOffText
  {
    [Description("Fly-off text life time")]
    public float lifeTime = 0.0f;

    [Description("Offset")]
    public Vec2 offset = new Vec2();

    [Description("Velocity")]
    public Vec2 velocity = new Vec2();

    [Description("Acceleration")]
    public Vec2 acceleration = new Vec2();

    [Description("Initial opacity")]
    [FloatMinMax(0.0f, 1.0f)]
    public float startOpacity = 0.0f;

    [Description("Target opacity at lifeTime")]
    [FloatMinMax(0.0f, 1.0f)]
    public float endOpacity = 0.0f;

    [Description("Flyoff alignment")]
    public EFlyOffAlign align = EFlyOffAlign.Left;

    [Description("Fly-off text layout name")]
    public string layout;
  }

  [NonTerminal]
  [TypeId(0xF6264430)]
  [FactoryBase("Create", "NGameX::PFUISign")]
  public class UISign : DBResource
  {
    [Description("Specify the recipients of this event reaction/sign. All messages (sounds) will be sent to the specified recipients only!!!")]
    public ERecipients signRecipients = ERecipients.USE_FROM_PARENT;
  }

  //==========================================================================================================================================
  [TypeId(0xF6264431)]
  [FactoryImpl("Create", "NGameX::PFUISignMessageToChat", "PFUIEvent.h")]
  public class UISignMessageToChat : UISign
  {
    [Description("Sign message. This message will be send to any UI output.")]
    [EnumArray(typeof(EMessage))]
    public List<TextRef> messages = new List<TextRef>();
    public EChatChannel channel = EChatChannel.Achievments;
  }

  //==========================================================================================================================================
  [TypeId(0xF6264432)]
  [FactoryImpl("Create", "NGameX::PFUISignPlaySound", "PFUIEvent.h")]
  public class UISignPlaySound : UISign
  {
    [Description("Sign sound. This sound will be played when event happened.")]
    public DBFMODEventDesc soundDesc;
  }

  //==========================================================================================================================================
  [TypeId(0xF6264433)]
  [FactoryImpl("Create", "NGameX::PFUISignMessageToStatusLine", "PFUIEvent.h")]
  public class UISignMessageToStatusLine : UISign
  {
    [Description("Sign message. This message will be send to any UI output.")]
    [EnumArray(typeof(EMessage))]
    public List<TextRef> messages = new List<TextRef>();
  }

  //==========================================================================================================================================
  [TypeId(0xF6264434)]
  [FactoryImpl("Create", "NGameX::PFUISignFlyOffText", "PFUIEvent.h")]
  public class UISignFlyOffText : UISign
  {
    [Description("Fly-off text")]
    public FlyOffText text;
  }

  [FactoryImpl("Create", "NGameX::PFUISignAnnouncement", "PFUIEvent.h")]
  public class UISignAnnouncement: UISign
  {
    [Description("Announcement type")]
    public EAnnouncementType announcementType;

    [Description("Announcement text")]
    public TextRef txt;

    [Description("image for elfs")]
    public DBPtr<Render.DBRenderResources.Texture> imageBurn;
    
    [Description("image for humans")]
    public DBPtr<Render.DBRenderResources.Texture> imageFreeze;

    [Description("greater is more important")]
    public int priority = 0;

    [Description("life time for announcement")]
    public float lifeTime = 3;

    [Description( "Announcement Sound like DoubleKill etc" )]
    public DBFMODEventDesc announcementSound;

    [Description("Cooldown (seconds) for announcement sound")]
    public float announcementSoundCooldown = 0.0f;

    [Description("Whether to use or not in the tutorial")]
    public bool UseInTutorial = true;
  }

  //==========================================================================================================================================
  [TypeId(0x4D7262C0)]
  [UseTypeName("UIEV")]
  [IndexField("EventId")]
  public class UIEvent : DBResource
  {
    [Description("Specify the recipients of all reaction/sign.")]
    public ERecipients signRecipients = ERecipients.ALL_PLAYERS;

    //list of signs for this event    
    public List<DBPtr<UISign>> UISigns = new List<DBPtr<UISign>>();
  }

  //==========================================================================================================================================
  [TypeId(0x4D729C41)]
  [UseTypeName("UIEVCOLL")]
  [DBVersion(4)]
  public class UIEventsCustom : DBResource
  {
    [Description("Miss UI Event")]
    public DBPtr<UIEvent> evMiss;

    [Description("Get nafta UI Event")]
    public DBPtr<UIEvent> evGetNafta;

    [Description("Hero kill")]
    public DBPtr<UIEvent> evHeroKill;

    [Description("Hero kill by AI")]
    public DBPtr<UIEvent> evHeroKillByAI;

    [Description("Hero kill by Neutral AI")]
    public DBPtr<UIEvent> evHeroKillByNeutralAI;

    [Description("Tower destroy")]
    public DBPtr<UIEvent> evTowerDestroy;

    [Description("Tower destroy by AI")]
    public DBPtr<UIEvent> evTowerDestroyByAI;

    [Description( "Tower destroy by Neutral AI" )]
    public DBPtr<UIEvent> evTowerDestroyByNeutralAI;

    [Description("Item transfer (Reward from Easel minigame)")]
    public DBPtr<UIEvent> evItemTransfer;

    [Description("Item transfer to self (Reward from Easel minigame)")]
    public DBPtr<UIEvent> evItemGain;

    [Description("Hero cheat")]
    public DBPtr<UIEvent> evHeroCheat;

    //TODO make this events
    [Description("Hero enemy reconnected")]
    public DBPtr<UIEvent> evHeroReconnected;

    [Description("Hero enemy disconnected")]
    public DBPtr<UIEvent> evHeroDisconnected;

    [Description("Hero enemy disconnected due to long AFK time")]
    public DBPtr<UIEvent> evHeroDisconnectedAFK;

    [Description("Hero friend disconnected")]
    public DBPtr<UIEvent> evHeroFriendDisconnected;

    [Description("Hero friend disconnected due to long AFK time")]
    public DBPtr<UIEvent> evHeroFriendDisconnectedAFK;

    [Description("Hero enemy left")]
    public DBPtr<UIEvent> evHeroLeft;

    [Description("Hero friend left")]
    public DBPtr<UIEvent> evHeroFriendLeft;

    [Description("Hero friend reconnected")]
    public DBPtr<UIEvent> evHeroFriendReconnected;

    [Description("Hero afk")]
    public DBPtr<UIEvent> evHeroAFK;

    [Description("Hero afk ended")]
    public DBPtr<UIEvent> evHeroAFKEnded;

    [Description("Enemy's Barrack destroyed")]
    public DBPtr<UIEvent> evBarrackDestroyed;

    [Description("Friend's Barrack destroyed")]
    public DBPtr<UIEvent> evFriendBarrackDestroyed;

    [Description("Victory")]
    public DBPtr<UIEvent> evVictory;

    [Description("Defeat")]
    public DBPtr<UIEvent> evDefeat;

    [Description( "Spectator join to battle" )]
    public DBPtr<UIEvent> evSpectatorJoin;

    [Description("Player admin muted")]
    public DBPtr<UIEvent> evAdminMuted;

    [Description("Start AI for disconnected player")]
    public DBPtr<UIEvent> evStartAiForPlayer;

    [Description("Нельзя писать в чат сессии, т.к. игрок - дезертир")]
    public DBPtr<UIEvent> evLeaverMuted;

    [Description("Нельзя писать в чат сессии, т.к. игрок состоит в группе с дезертиром")]
    public DBPtr<UIEvent> evLeaverPartyMuted;

    [Description("Игрок не может писать в чат - уведомление для всех на экране загрузки")]
    public DBPtr<UIEvent> evAdminMutedNotify;
  }
}
