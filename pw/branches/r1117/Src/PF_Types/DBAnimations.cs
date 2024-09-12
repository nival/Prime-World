using System.Collections.Generic;
using libdb.DB;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_GameLogic.DBAnimations
{

  public enum EEmotion
  {
    Happy,
    Sad,
    Hello,
  }

  public enum EEmotePermission
  {
    PlayNone,
    PlayUpper,
    PlayLower,
    PlayBoth
  }

  public class EmotePlayNodeParams
  {
    [EnumArray(typeof(EEmotion))]
    public List<EEmotePermission> permissions = new List<EEmotePermission>();
  }

  [UseTypeName("EMO")]
  public class EmoteSettings : DBResource
  {
    [EnumArray(typeof(EAnimStates))]
    public List<EmotePlayNodeParams> nodes = new List<EmotePlayNodeParams>();
  }
  
  public enum EAnimStates
  {
    Invalid,

    Idle,
    Stun,

    Move,
    BlockedMove,

    Attack,

    Ability1,
    Ability2,
    Ability3,
    Ability4,

    Death,
    Resurrect,
    Summon,
    Unsummon,

    Hello,
    Happy,
    Sad,

    Minigaming,

    Special1,
    Special2,
    Special3,
    Special4,

    Hide,
  }

  public enum EAnimStatePlayMode
  {
    PlayNormal,
    PlayUpper,
    PlayBoth 
  }

  public class AnimStateData
  {
    public string commonNode   = "";
    public string upperNode    = "";
    public EAnimStatePlayMode playMode = EAnimStatePlayMode.PlayBoth;
    public string commonMarker = "";
    public string upperMarker  = "";
  }

  public class AnimStateDataNew
  {
    public EAnimStates animState;
    public string node   = "";
    public string marker = "";
  }

  [IndexField("caption")]
  public class AnimStateChanger
  {
    public AnimStateDataNew oldAnimation;
    public AnimStateDataNew newAnimation;

    [NoCode]
    public string caption = string.Empty;
  }

  [UseTypeName("ANS")]
  public class AnimSet : DBResource
  {
    [EnumArray(typeof(EAnimStates))]
    public List<AnimStateData> states = new List<AnimStateData>();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
