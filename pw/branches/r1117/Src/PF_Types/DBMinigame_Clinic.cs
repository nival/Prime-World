//#include "../Types/UI.cs"

using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using PF_GameLogic.DBStats;
using Render.DBRender;
using Scene.DBScene;
using Scene.DBSceneBase;
using Sound.DBSound;
using UI.DBUI;

namespace PF_Minigames.DBClinic
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum ECreepWish
  {
    None,
    
    Sleep,
    Wash,
    Eat,
    Play,
    Carpet,
    Any,
    Exit
  }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum ECreepState
  {
    Working,
    Sleeping,
    NeedWash,
  }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum EBonusType
	{
		Broom,
		ComfortablePillow,
		Booklet,
		ComfortableTable,
		Bell,
		Footpaths,
		Whip,
		VelvetGloves,
		AdvencedEntrace,
		Candy,
		Talisman,
		ToyBox,
		SpeedBoots,
		ComfortableCarpet,
		SuperCleaner,
		BootCovers,
		BestClinic,	
		Star
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public enum EPlaceType
	{
		None,
		Table,
		Bad,
		Washtab,
		GamePlace,
		CreepPlace,
		Entrance
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class BonusDesc
	{
    public TextRef description = new TextRef();
    public TextRef name = new TextRef();
		public Vec3 position = new Vec3(0, 1.1F, 0.2F); 

		public float cooldown = 0;
		public float duration = 20;

		public int accessibility = -1;
		public int cost = 100;
		public int useCost = 10;

		public float value = 1.0F;

		public DBPtr<DBSceneObject> sceneObject;

    public DBPtr<UIObjectOvertips> overtip;

    public DBPtr<BaseUIMaterial> iconMaterial;

		public BonusDesc() {}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class LevelDesc
	{
		public int expToOpen = 0;
		public float levelFinishBonus = 100;
		public float creepTraindedBonus = 100;

    public int levelFinishMoney = 100;
    public int creepMedalMoney = 5;
    
    public float duration = 3;

		public TextRef name = new TextRef();
		public TextRef description = new TextRef();

		public int numberOfMelee = 1;
		public int numberOfRange = 1;
		public int numberOfSiege = 1;

    public bool casualWishGeneration = false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class TrainingBonuses
	{
    [FieldCategory("Creeps")]
    [Description("Stats modifications (bar > 50%)")]
    [EnumArray(typeof(EStat))]
    public List<float> statLifeBar50 = new List<float>();

    [FieldCategory("Creeps")]
    [Description("Stats modifications (bar > 59%)")]
    [EnumArray(typeof(EStat))]
    public List<float> statLifeBar59 = new List<float>();

    [FieldCategory("Creeps")]
    [Description("Stats modifications (bar > 69%)")]
    [EnumArray(typeof(EStat))]
    public List<float> statLifeBar69 = new List<float>();

    [FieldCategory("Creeps")]
    [Description("Stats modifications (bar > 79%)")]
    [EnumArray(typeof(EStat))]
    public List<float> statLifeBar79 = new List<float>();

    [FieldCategory("Creeps")]
    [Description("Stats modifications (bar > 89%)")]
    [EnumArray(typeof(EStat))]
    public List<float> statLifeBar89 = new List<float>();

    [FieldCategory("Creeps")]
    [Description("Stats modifications (bar == 100%)")]
    [EnumArray(typeof(EStat))]
    public List<float> statLifeBar100 = new List<float>();
  }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class PlaceDesc
	{
		public EPlaceType placeType = EPlaceType.Bad;
		public Vec3 position = new Vec3(0, 0, 0);

    [Description("Scene object for clear place (50% < soil)")]
    public DBPtr<DBSceneObject> sceneObject;
    [Description("Scene object for dirty place (50% < soil < 100%)")]
    public DBPtr<DBSceneObject> sceneObjectDirty50;

    public DBPtr<UIObjectOvertips> overtip;

		public int accessibility = -1;
		public int cost = 250;

    public TextRef name = new TextRef();
    public TextRef description = new TextRef();

    public DBPtr<BaseUIMaterial> iconMaterial;
  }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class DecorationDesc
	{
		public Vec3 position = new Vec3(0, 0, 0);
		public DBPtr<DBSceneObject> sceneObject;
	}

	//////////////////////////////////////////////////////////////////d/////////////////////////////////////////////////////////////
	public class CreepPlaceDesc
	{
		public Vec3 position;			
	}
	//////////////////////////////////////////////////////////////////d/////////////////////////////////////////////////////////////
	public class IntOffsets
	{
		public int pxBefore = 0;
		public int pxAfter = 0;
		
		public IntOffsets() {}

		public IntOffsets( int _pxBefore,  int _pxAfter )
		{
			pxBefore = _pxBefore;
			pxAfter = _pxAfter;
		}
	}
	//////////////////////////////////////////////////////////////////d/////////////////////////////////////////////////////////////
  [DBVersion(1)]
	public class MinigameUIStylesDesc
	{
    [EnumArray(typeof(ECreepWish))]
    public List<DBPtr<BaseUIMaterial>> creepWishMaterials;

    [EnumArray(typeof(ECreepState))]
    public List<DBPtr<BaseUIMaterial>> creepStateMaterials;

    [MinMaxSize(5, 5)]
    public List<DBPtr<BaseUIMaterial>> creepFriendshipMaterials;

    [FieldCategory( "ResultsScreen" )]
		public float creepsAppearPause = 0;
		public float creepAppearTime = 0;
    public float creepMedalAppearTime = 0;
		public float medalAppearPause = 0;
		public float medalAppearTime = 0;
    public float naftaAnimationSpeed = 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class CreepsDesc
	{
		public DBPtr<DBSceneObject> sceneObjectMelee;
		public DBPtr<DBSceneObject> sceneObjectRange;
		public DBPtr<DBSceneObject> sceneObjectSiege;

    public DBPtr<BaseUIMaterial> imageMeleeMaterial; 
    
    public DBPtr<BaseUIMaterial> imageRangeMaterial; 

    public DBPtr<BaseUIMaterial> imageSiegeMaterial; 

    public DBPtr<UIObjectOvertips> overtip;
    public float goldMedalValue = 0.75f;
    public float silverMedalValue = 0.5f;

		public List<CreepPlaceDesc> creepPlaces = new List<CreepPlaceDesc>();
  }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class PlayerDesc
	{
		public Vec3 startPosition;
		public float velocity = 2;
    public float scaleFactor = 1.0f;
    public DBPtr<Render.DBRenderResources.AnimGraphCreator> animationGraph;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class CreepBehaviourDesc
	{
		[Description("Pause before friend searching")]
		public float timeBeforeSearchFriend = 0F;

		[Description("Bonus for friendship")]
		public float friendshipBonus = 0.02F;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class NeighbourhoodDesc
	{
		public int first;
		public int second;
	}

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class Preselection
  {
    [Description("Color multiplier for item in shop")]
    public HDRColor colorNotBought = new HDRColor(0.5F, 1.0F, 0.5F, 1.0F);
    [Description("Color multiplier for item in shop (unavailable)")]
    public HDRColor colorNotBoughtUnavailable = new HDRColor(0.5F, 0.5F, 0.5F, 1.0F);
    [Description("Color multiplier for item in shop preselection")]
    public HDRColor colorNotBoughtPreselect = new HDRColor(0.5F, 2.0F, 0.5F, 1.0F);
    [Description("Color multiplier for preselection in game")]
    public HDRColor colorPreselect = new HDRColor(1.2F, 1.2F, 1.2F, 1.0F);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EClinicSounds
  {
    StartLevel,
    LevelWinWithMedal,
    LevelWinWithoutMedal,

    CreepWishMelee,
    CreepWishRanged,
    CreepWishSiege,

    CreepWishDesiredMelee,
    CreepWishDesiredRanged,
    CreepWishDesiredSiege,

    CreepBecomeLazy,
    CreepLooseWish,

    UseTable,
    UseWashtab,
    UseBad,
    UsePlayground,

    CreepFriendship,
    CreepBar25,
    CreepBar50,

    CreepWakeup,
    PlaceBecomeDirty,
    Buy
  }

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public class DBMinigame_Clinic : DBResource
	{
    public TextRef title;

    public ViewCamera cameraOptions;
    
    [FieldCategory("Sound")]
    [EnumArray(typeof(EClinicSounds))]
    public List<DBPtr<Sound2D>> sounds = new List<DBPtr<Sound2D>>();

    [FieldCategory("Sound")]
    [EnumArray(typeof(EBonusType))]
    public List<DBPtr<Sound2D>> bonusSounds = new List<DBPtr<Sound2D>>();

    [FieldCategory("Preselection")]
		public Preselection preselection;

    [FieldCategory("Player")]
		public PlayerDesc player;

    [EnumArray(typeof(EBonusType))]
    public List<BonusDesc> bonuses = new List<BonusDesc>();

		[FieldCategory("Game field")]
		public List<PlaceDesc> places = new List<PlaceDesc>();
    [FieldCategory("Game field")]
    [Description("Effect for dirty place (soil == 100%)")]
    public DBPtr<DBSceneObject> sceneObjectDirty100;


		[FieldCategory("Game field")]
		public List<NeighbourhoodDesc> neighbourhood = new List<NeighbourhoodDesc>();

		[FieldCategory("Game field")]
		public List<LevelDesc> levels = new List<LevelDesc>();

		[FieldCategory("Game field")]
		public List<DecorationDesc> decorations = new List<DecorationDesc>();

		[FieldCategory("Creeps")]
		public CreepsDesc creepsDesc;

		[FieldCategory("Creeps")]
		public CreepBehaviourDesc creepBehaviourDesc;

		[FieldCategory("Creeps")]
		public TrainingBonuses trainingBonuses;

		[FieldCategory("Options")]
		public float soilPersentMelee = 15;
		[FieldCategory("Options")]
		public float soilPersentRange = 15;
		[FieldCategory("Options")]
		public float soilPersentSiege = 35;

		[FieldCategory("Options")]
		public int clickBonusClickCount = 10;

		[FieldCategory("Options")]
		public float clickBonusValue = 0.02F;

		[FieldCategory("Options")]
		[Description("Hearts bonus for the level completion")]
		public float heartsBonus = 0.5F;

		[FieldCategory("Options")]
		[Description("Min. time between creeps apears at entrance")]
		public float minTimeBetweenCreeps = 2.0F;

		[FieldCategory("Options")]
		[Description("Max. time between creeps apears at entrance")]
		public float maxTimeBetweenCreeps = 5.0F;

		[FieldCategory("Creep state options")]
		[Description("Min. time of think phase")]
		public float minThinkTime = 3.0F;

		[FieldCategory("Creep state options")]
		[Description("Max. time of the 'Think' phase")]
		public float maxThinkTime = 5.0F;

		[FieldCategory("Creep state options")]
		[Description("Duration of the 'Wait' phase")]
		public float waitTime = 30.0F;

		[FieldCategory("Creep state options")]
		[Description("Time until a creep fall asleep")]
		public float fallAsleepTime = 3.0F;

		[FieldCategory("Creep state options")]
		[Description("Time until a creep wakes up")]
		public float wakeupTime = 3.0F;

		[FieldCategory("Creep state options")]
		[Description("Time of the 'Work' phase")]
		public float workTime = 5.0F;

		[FieldCategory("Creep state options")]
		[Description("Default work bonus (will be added)")]
		public float workBonus = 0.1F;

		[FieldCategory("Creep state options")]
		[Description("Default fail bonus (will be subtracted)")]
		public float failBonus = 0.1F;

		[FieldCategory("Level 1 features")]
		[Description("Bar value at start")]
		public float level1_BarValue = 40.0F;

		[FieldCategory("Level 3 features")]
		[Description("Min. time of think phase")]
		public float level3_phase1Min = 8.0F;

		[FieldCategory("Level 3 features")]
		[Description("Max. time of think phase")]
		public float level3_phase1Max = 12.0F;

		[FieldCategory("Level 4 features")]
		[Description("Wish 'Wash' probability (times)")]
		public float level4_washProbTimes = 2.0F;

		[FieldCategory("Level 5 features")]
		[Description("Time until a creep fall asleep")]
		public float level5_fallAsleepTime = 2.0F;

		[FieldCategory("Level 6 features")]
		[Description("Soil percent at start")]
		public float level6_soilAtStart = 90.0F;

		[FieldCategory("Level 8 features")]
		[Description("'Work' time reduction (times)")]
		public float level8_timeReduction = 2.0F;

		[FieldCategory("Level 8 features")]
		[Description("Bonus in percent")]
		public float level8_bonusReduction = 50.0F;

		[FieldCategory("Level 9 features")]
		[Description("Wish 'Wash' probability")]
		public float level9_washProb = 80.0F;

		[FieldCategory("Level 10 features")]
		[Description("Wish 'Play' probability (times)")]
		public float level10_playProbTimes = 2.0F;

		[FieldCategory("Level 11 features")]
		[Description("Soil in percent")]
		public float level11_soilIncrease = 200.0F;

		[FieldCategory("Level 12 features")]
		[Description("Soil in percent")]
		public float level12_soilIncrease = 150.0F;

		[FieldCategory("Level 12 features")]
		[Description("Bonus in percent")]
		public float level12_bonusReduction = 70.0F;

		[FieldCategory("Level 12 features")]
		[Description("Wait time decrease (times)")]
		public float level12_waitDecrease = 2.0F;

		[FieldCategory("Minigame UI Styles")]
		[Description("Minigame UI Styles")]
		public MinigameUIStylesDesc uiStyles;
  }
}
