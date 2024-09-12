//#include "RenderResources.cs"
//#include "Sound.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using Render.DBRender;
using Render.DBRenderResources;

namespace Scene.DBSceneBase
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class LightInstance
	{
		public DBPtr<OmniLight> light;
		public Vec3 position;
		public Quat rotation;
		[Description( "Scale coefficient" )]
		public float scale = 1.0f;
		[Description( "Playback speed coefficient" )]
		public float speed = 1.0f;
		[Description( "(sec.) pause before playback start" )]
		public float offset = 0.0f;
		[Description( "(sec.) cycle length (0 = no repeat)" )]
		public float cycleLength = 0.0f;
		[Description( "Number of playback cycles (0 = infinite)" )]
		public int cycleCount = 1;
		[Description( "Model's joint name to bind to (empty = do not bind)" )]
		public string jointName = String.Empty;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class AnimFaceFXKey
	{
		public float startTime = 0.0f;
		public int animation = 0;
		public int cycleCount = 0;
		public string facefxname = string.Empty;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class ModelInstance
	{
		public DBPtr<Skeleton> model;
		[Description("Animation & FaceFX keys")]
		public List<AnimFaceFXKey> anims = new List<AnimFaceFXKey>();
		[Description("Skins")]
		public List<int> skins = new List<int>();
		[Description("Transform matrix")]
		public Matrix trasform;
		[Description( "Playback speed coefficient" )]
		public float speed = 1.0f;
		[Description( "(sec.) pause before playback start" )]
		public float offset = 0.0f;
		[Description( "(sec.) cycle length (0 = animation length)" )]
		public float cycleLength = 0.0f;
		[Description( "Number of playback cycles (0 = infinite)" )]
		public int cycleCount = 0;
		[Description("(sec.) duration (0 = use cycleLength)")]
		public float duration = 0.0f;

		[Description("(sec.) FadeIn")]
		public float fadein = 0.0f;
		[Description("(sec.) FadeOut")]
		public float fadeout = 0.0f;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class StaticModelInstance
	{
		public DBPtr<StaticMesh> model;
		[Description("Transform matrix")]
		public Matrix trasform;
		[Description("(sec.) pause before playback start")]
		public float offset = 0.0f;
		[Description("(sec.) duration (0 = infinity)")]
		public float duration = 0.0f;

		[Description("(sec.) FadeIn")]
		public float fadein = 0.0f;
		[Description("(sec.) FadeOut")]
		public float fadeout = 0.0f;
	};
	public class SyncInfo
	{
		[FileRef( "*.mid" )]
		public string midiFile = string.Empty;
		public bool tempoSync = false;
		public bool toneSync = false;
		[Description( "(sec.) pause before synced object" )]
		public float offset = 0.0f;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class SoundSRC : DBResource
	{
		[FileRef( "*.wav;*.mp3;*.ogg;*.flac" )]
		public string soundFile = string.Empty;
		public SyncInfo syncInfo;
	}

	public class SoundTrack 
	{
		public DBPtr<SoundSRC> sound;
		public float volume = 1.0f;
		public float volumeRandomization = 0.0f;
		[Description( "A priority which the Sound will be played. 0 - most important, 256 - least important" )]
		public int priority = 0;
	}

	public class SoundEffect  :SoundTrack
	{
		public float pitch = 0.0f;
		public float pitchRandomization = 0.0f;
	}

	public class SoundSet : DBResource
	{
		public List<SoundEffect> sounds = new List<SoundEffect>();
		[Description( "A priority which the Sound will be heared. 0 - most Important, 256 - least Imortant" )]
		public int priority = 0;
	}
	public class SoundObject
	{
		public DBPtr<SoundSet> soundSet;
		//Позиция на карте (или в пресете) и прочее

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class SoundInstance
	{
		[FileRef("*.wav;*.mp3;*.ogg;*.flac")]
		public string soundFile = string.Empty;
		[Description("(sec.) pause before playback start")]
		public float offset = 0.0f;
		[Description("Number of playback cycles (0 = infinite)")]
		public int cycleCount = 0;
		[Description("Sound volume")]
		public float volume = 1.0f;
		[Description("true = 3d sound, false = 2d sound")]
		public bool is3DSound = true;
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class EffectInstance
	{
//		public ParticleInstance particle = new ParticleInstance();
		public ModelInstance model = new ModelInstance();
		public LightInstance light = new LightInstance();
		public StaticModelInstance staticmodel = new StaticModelInstance();
		public SoundInstance sound = new SoundInstance();
		public Sound.DBSound.FMODEventInstance fmodEvent = new Sound.DBSound.FMODEventInstance();
		[Description("Visual Object's joint name to bind to (empty = do not bind)")]
		public string jointName = String.Empty;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	[UseTypeName("CHEF")]
	public class ChildEffect : DBResource
	{
		public DBPtr<ChildEffect> tranformedchild;
		public DBPtr<Effect> childeffect;
		public Matrix transform;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	[UseTypeName("LNDT")]
	public class LandTemp : DBResource
	{
		public float speed = 0.1f;
		public int randomSeed = 50;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	[UseTypeName( "EFCT" )]
	public class Effect : DBResource
	{
		public DBPtr<LandTemp> landtemp;
		public DBPtr<ChildEffect> tranformedchild;
		public DBPtr<Effect> child;
		public List<EffectInstance> effects = new List<EffectInstance>();
		[Description( "Randomize effect start phase?" )]
		public bool randomizePhase = false;
		[Description("Randomize effect speed?")]
		public bool randomizeSpeed = false;
	};

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	[UseTypeName( "COLL" )]
	public class CollisionGeometry : DBResource
	{
		[SrcFile( "Maya files", "*.mb" )]
		[DstFileArg( 0 )]
		public string srcFileName = string.Empty;

		[NoCode]
		[DstFile( "mayaColl" )]
		public string mayaFileName = string.Empty;

		[DstFile( "coll" )]
		public string fileName = string.Empty;

		[NoCode]
		[DstFileArg( 1 )]
		public string selection = string.Empty;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public class ViewCamera
	{
		public string name;
		public Vec3 anchor;
		public float yaw = 0;
		public float pitch = 0;
		public float roll = 0;
		public int rod = 10;
		public int fov = 30;
		public string environment = string.Empty;
	}

	public class ObjectLockMask
	{
		public float tileSize = 0.5f;
    public List<IntPoint> mask = new List<IntPoint>();
	}

	[TypeId(0x9E5573C6)]
	[UseTypeName("GMOB")]
  [DBVersion(1)]
	public class GameObject : DBResource
	{
		[Description("Relative 2D object bounds to lock map")]
		public FloatRect collision;
		[Description("Precise mask to lock map")]
		public ObjectLockMask lockMask;
		[Description("Threshold for object scale-dependent lock")]
		public float minLockScale = 0;
    [Description( "Allow rounding of object map lock" )]
		public bool rounded = false;
		public bool heightObject = false;
	}
  
  [NoCode]
  [TypeId(0x4964EAC0)]
  [UseTypeName("PTLT")]
  public class PointLightGameObject : DBResource
  {
  }

  [NoCode]
  [TypeId( 0xE7920C00 )]
  [UseTypeName( "SCAR" )]
  public class ScriptAreaGameObject : GameObject
  {
  }

  [TypeId( 0xE7920C10 )]
  [UseTypeName( "SPTH" )]
  public class ScriptPath : GameObject
  {
    public List<Vec2> path = new List<Vec2>();
  }

  [Flags]
  public enum ELocatorAttachFlags
  {
    None = 0,
    UseJointScale = 1,
    UseJointRotation = 1 << 1,
    UseJointPosition = 1 << 2,
    CancelNormalLevelling = 1 << 3,
  }

  [IndexField("name")]
  public class Locator
  {
    public string name = string.Empty;
    public Placement2 offset2;
    public ELocatorAttachFlags flags = ELocatorAttachFlags.UseJointScale | ELocatorAttachFlags.UseJointRotation | ELocatorAttachFlags.UseJointPosition;
    [JointNamesSelector]
    public string jointName = string.Empty;
  }

  //////////////////////////////////////////////////////////////////////////////////////////

  public class RoadControlPoint : FlatSplineControlPointDesc
  {
    [Description("Прозрачность материала дороги в этой точке (от 0 до 1)")]
    public float opacity = 1.0f;
  }

  [DBVersion(1)]
  public class RoadProperties
  {
    [Description("Базовая ширина дороги в метрах, относительно которой действуют настройки ширины в контрольных точках, и указываются некоторые другие параметры.")]
    public float width = 2.0f;

    [Description("Значение от 0 до 1, задающая ширину бордюра в процентах от половины *базовой* ширины дороги (не текущей, а width).")]
    public float border = 0.2f;

    [Description("Значение от 0 до 1, задающая ширину затухания по краям полотна дороги в процентах от половины *базовой* ширины дороги (не текущей, а width).")]
    public float falloff = 0.1f;

    [Description("Общая прозрачность дороги (от 0 до 1), умножается на прозрачность в отдельных точках.")]
    public float opacity = 1.0f;

    [Description("Значение тайлинга текстуры полотна поперек направления дороги, т.е. сколько раз текстура укладывается по ширине (*базовой* или текущей, в зависимости от fit).")]
    public float tileU = 1.0f;

    [Description("Значение тайлинга текстуры полотна вдоль направления дороги, в том же масштабе, что и  tileU.")]
    public float tileV = 1.0f;

    [Description("Значение тайлинга текстуры бордюра вдоль направления дороги.")]
    public float tileVBorder = 1.0f;

    [Description("Флаг, определяющий, должен ли маппинг текстуры растягиваться с изменением ширины дороги (true) или должен быть равномерным, задаваясь для базовой ширины (false).")]
    public bool fit = false;

    [Description("Флаг, определяющий, нужно ли флипнуть текстуру поперек дороги.")]
    public bool flip = false;

    [Description("Приоритет рендера, большее число означает, что дорога будет рендериться раньше других. По умолчанию 0.")]
    public float priority = 0.0f;

    [Description("Материал дороги для нейтральной земли")]
    public DBPtr<RoadMaterial> materialN;

    [Description("Материал дороги для земли фракции A")]
    public DBPtr<RoadMaterial> materialA;

    [Description("Материал дороги для земли фракции B")]
    public DBPtr<RoadMaterial> materialB;
  }

  [TypeId(0xCB726281)]
  [UseTypeName("ROAD")]
  public class Road : GameObject
  {
    [ReadOnly(true)]
    public List<RoadControlPoint> points = new List<RoadControlPoint>();
    public RoadProperties properties = new RoadProperties();

    [Description("Сбейканные данные для ускорения загрузки игры")]
    [DstFile("road")]
    public string bakedFileName;
  }
}
