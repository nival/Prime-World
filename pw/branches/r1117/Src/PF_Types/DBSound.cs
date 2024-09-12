using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Sound.DBSound;

namespace PF_GameLogic.DBSound
{

  public enum SoundScene
  {
    SessionA,
    SessionB,
    Minigame_02,
    Loading,
    Dead,
    Battle,
    Win,
    Defeat,
    TutorialA,
    TutorialB,
    TowerDeath,
  }

  public enum SoundAmbientGroup
  {
    BaseA,
    BaseB,
    ForestN,
    ForestA,
    ForestB,
    Water,
    Road,
  }

  public class SoundAmbientDesc
  {
    public string paramName = "";
    public HDRColor color = new HDRColor(0.0f, 0.0f, 0.0f, 0.0f);
    public string reverbPresetName = "Ambient";
  }

  [DBVersion(1)]
  public class TimerSounds
  {
    [Description("Start timer sound")]
    public DBFMODEventDesc startTimerSound;

    [Description("Start event for A")]
    public DBFMODEventDesc startEventA;

    [Description("Start event for B")]
    public DBFMODEventDesc startEventB;

    [Description("Dead timer sound")]
    public DBFMODEventDesc deadTimerSound;

    [Description("Dead reverb preset name")]
    public string deadReverbName;

    public float timeToRestorePitch = 5.0f;
    public float timeToTickOnStart = 10.0f;
  }

  [DbRoot]
  public class SoundRoot : DBResource
  {
    [EnumArray(typeof(SoundScene))]
    public List<SoundSceneDesc> sceneScenes;

    public TimerSounds timerSounds;

    [Description("Heartbeat sound")]
    public DBFMODEventDesc heartbeat;

    [Description("Heartbeat sound for female")]
    public DBFMODEventDesc heartbeatFemale;

    [Description("Heartbeat sound - life parameter name")]
    public string heartbeatParamName = "";

    [Description("Ambient sound")]
    public DBFMODEventDesc ambient;

    [EnumArray(typeof(SoundAmbientGroup))]
    public List<SoundAmbientDesc> ambienceGroups;

    [Description("Звук воспроизводится в экране настроек после изменения положения ползунка громкости")]
    public DBFMODEventDesc preferencesVolumeHasChanged;

    [Description( "Звук убийства крипа героем ( lastHit )" )]
    public DBFMODEventDesc lastHit;

    [Description("Timer for playing ask idle")]
    public float timerHeroAskIdle = 15.0f;


    [Description( "Время, после которого опять может начать играть сцена разрушения башни" )]
    public float timeToTowerDeath = 60.0f;
  }
}