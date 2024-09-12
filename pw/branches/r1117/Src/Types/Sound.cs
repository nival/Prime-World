//#include "RenderResources.cs"

using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Render.DBRenderResources;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Все классы называются с префикса Sound
namespace Sound.DBSound
{
	public enum SoundCameraType
	{
		TopDown,
		Perspective,
	}
	public class SoundCamera
	{
		public SoundCameraType type = SoundCameraType.Perspective;
		public float multiplier = 1.0f;
	}

  // obsolete, have to be changed to DBFMODEventInstance
  public class Sound2D : DBResource
  {
      [FileRef("*.wav;*.mp3;*.ogg")]
      public string soundFile = string.Empty;
      [Description("(sec.) pause before playback start")]
      public float offset = 0.0f;
      [Description("Number of playback cycles (0 = infinite)")]
      public int cycleCount = 1;
      [Description("Sound volume")]
      public float volume = 1.0f;
  }

  // for music purpose only
  public class SoundStream : DBResource
  {
      [FileRef("*.wav;*.mp3;*.ogg")]
      public string soundFile = string.Empty;
      [Description("Number of playback cycles (0 = infinite)")]
      public int cycleCount = 0;
      [Description("Sound volume")]
      public float volume = 1.0f;
  }

  public enum EAskSounds
  {
    MOVE,
    ABILITY_1,
    ABILITY_2,
    ABILITY_3,
    ABILITY_ULT,
    ATTACK,
    DEATH,
    REVIVE,
    KILL,
    IDLE,
    RAISEFLAG,
    KILLCHAMPION,
    MINIGAMEWIN,
    MINIGAMEFAIL,
  }

  [DBVersion(0)]
  public class SoundAmbienceMap
  {
    [Description("Текстурная карта с областями, обозначающими различные звуки окружения в данной местности (см. документацию).")]
    public DBPtr<Texture> texture;

    [Description("Радиус осреднения текстурной карты для определения пропорций звуков окружения, в метрах вокруг слушателя (камеры).")]
    public float radius = 30.0f;

    [Description("Направленность ушей слушателя, т.е. зависимость сдвига осреднения от направления взгляда, в долях от радиуса. Ноль = нет направленности.")]
    public float directivity = 0.5f;
  }

  [DBVersion(4)]
  public class SoundEnvironment : DBResource
	{
    [Description( "Sound language" )]
    public TextRef language = new TextRef();
		public SoundCamera soundCamera;                                                                            

		public List<string> fevFiles;
		public List<string> banks;
  }

  public class DBFMODEventDesc
  {
    [Description("Project name")]
    public string projectName = string.Empty;
    [Description("Group name")]
    public string groupName = string.Empty;
    [Description("Event name")]
    public string eventName = string.Empty;
  }

  public class FMODEventInstance
	{
		public FMODGroupInstance fmodGroup;
		public string name = string.Empty;
	}
	public class FMODGroupInstance
	{
		public DBPtr<FMODEventProject> project;
		public string fmodGroup = string.Empty;
	}

	public class FMODEventProject : DBResource
	{
		public string name = string.Empty;
		public List<FMODEventGroup> groups = new List<FMODEventGroup>();
	}

	public class FMODEvent
	{
		public string name = string.Empty;
	}
	public class FMODEventGroup
	{
		public string name = string.Empty;
		public List<FMODEventGroup> groups = new List<FMODEventGroup>();
		public List<FMODEvent> events = new List<FMODEvent>();
	}

  public class SoundSceneGroupDesc
  {
    public string categoryName;
    public float pitch = 0.0f;
    public AnimatedFloat volume;
  }

  public class MusicDesc
  {
    public string cueName;
  }

  public class SoundSceneDesc
  {
    public List<SoundSceneGroupDesc> soundSceneGroups;
    public MusicDesc cue;
  }
}
