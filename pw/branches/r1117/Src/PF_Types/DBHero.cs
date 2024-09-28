//#include "SocialClient/DBSocialHeroes.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using PF_GameLogic.DBServer;
using libdb.DB;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBGameLogic;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBTalent;
using Render.DBRender;
using Render.DBRenderResources;
using Scene.DBScene;
using Scene.DBSceneBase;
using Sound.DBSound;
using PF_Types.SocialClient;
using Foundation.DBSystem;

namespace PF_GameLogic.DBUnit
{
  [TypeId( 0x2C5B3C81 )]
  [UseTypeName( "HPLH" )]
  public class HeroPlaceHolder : GameObject
  {
    public ETeamID teamId = ETeamID.A;
  }

  public enum EAskRecipient
  {
    Self,
    Target,
    Allies,
    Enemies,
    All,
  }

  public class AskSettings
  {
    [Description( "Defines minimum time interval, which is allowed between two ask plays. (seconds)" )]
    public float minInterval = 3.0f;

    [Description( "Defines allowed recipients for 3d asks." )]
    public EAskRecipient ask3dRecipient = EAskRecipient.Enemies;
  }

  public class AskSounds
  {
    [EnumArray( typeof( EAskSounds ) )]
    public List<DBPtr<DBSoundSceneComponent>> sounds = new List<DBPtr<DBSoundSceneComponent>>();

    [EnumArray( typeof( EAskSounds ) )]
    public List<DBPtr<DBSoundSceneComponent>> sounds3d = new List<DBPtr<DBSoundSceneComponent>>();

    [EnumArray( typeof( EAskSounds ) )]
    public List<AskSettings> settings = new List<AskSettings>();
  }


  [UseTypeName( "ASKS" )]
  public class AskSoundsRef : DBResource
  {
    public AskSounds asks;
  }


  public class LevelDiffModifier
  {
    public int difference = 0;
    public float modifier = 0;
  }

  [UseTypeName( "KLEM" )]
  public class KillExperienceModifier : DBResource
  {
    public float otherDifferenceLessCoeff = 10;
    public float otherDifferenceGreaterCoeff = 150;
    public List<LevelDiffModifier> levelModifiers = new List<LevelDiffModifier>();
  }

  [UseTypeName( "HLVL" )]
  [DBVersion(1)]
  public class HeroesLevelUps : DBResource
  {
    public List<int> developmentPoints = new List<int>();
    public DBPtr<KillExperienceModifier> killExperienceModifiers;
  }

  [Flags]
  [Custom( "Social" )]
  public enum EHeroRaces
  {
    Zero = 0,
    A = ( 1 << 0 ),
    B = ( 1 << 1 ),
  }


  [Custom("DBServer")]
  [NoCode]
  public enum MMakingHeroClassEnum
  {
    None,
    Protector,
    Vanguard,
    Executioner,
    Fighter,
    Support,
    Jungler
  }


  [DBVersion( 4 )]
  public class SummonedUnits 
  {
    [Description( "Summon for first faction" )]
    public DBPtr<Summoned> unitA;
    [Description( "Summon for second faction" )]
    public DBPtr<Summoned> unitB;
  }

  public class HeroResource : DBResource
  {
    public string formulaNameValue;
    public string formulaNameMaximum;
    public string formulaNameRegeneration;

    public DBPtr<BaseUIMaterial> overtipManaProgressMaterial;

    public Color uiManaBarColor = new Color(0xFF, 0x00, 0xFF, 0xFF);

    [Custom("Social")]
    public TextRef name = new TextRef();

    [Custom("Social")]
    public TextRef tooltip = new TextRef();

    [Custom("Social")]
    public float castleValueMaximum;
  }

  [DBVersion( 5 )]
  public class BaseHero : Creature
  {
    [EnumArray( typeof( ETeamID ) )]
    [Description( "Scene objects by team ID" )]
    public List<DBPtr<DBSceneObject>> heroSceneObjects = new List<DBPtr<DBSceneObject>>();

    [Custom( "DBServer", "Social" )]
    public EGender gender = EGender.Male;

    [FieldCategory( "Asks" )]
    [EnumArray( typeof( ETeamID ) )]
    [Description( "Hero acknowledgment sounds by team ID" )]
    public List<AskSounds> askLists = new List<AskSounds>();

    [FieldCategory("Asks")]
    [EnumArray(typeof(ETeamID))]
    [Description("Hero acknowledgment sounds by team ID (second hero state)")]
    public List<AskSounds> askListsSecondState = new List<AskSounds>();

    [Description("Human readable hero name for first faction")]
    [Custom( "Social" )]
    public TextRef heroNameA = new TextRef();

    [Description( "Human readable hero name for second faction" )]
    [Custom( "Social" )]
    public TextRef heroNameB = new TextRef();

    [Description( "Hero UI avatar picture for first faction" )]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> heroImageA;

    [Description( "Hero UI avatar picture for second faction" )]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> heroImageB;

    [Description( "Global Hero ID" )]
    [Custom( "Social" )]
    public string persistentId = "";

    [Description( "ID for antagonist" )]
    [Custom( "Social" )]
    public string antagonistId = "";

    [Description( "IDs of antagonists for matchmaking" )]
    [Custom( "DBServer" )]
    public List<string> mmakingAntagonists = new List<string>();


    [Custom("Social")]
    [Description( "Hero minimap icon for first faction" )]
    public DBPtr<Texture> minimapIconA;

    [Custom("Social")]
    [Description( "Hero minimap icon for second faction" )]
    public DBPtr<Texture> minimapIconB;

    [Description( "Enabled hero races" )]
    [Custom( "DBServer", "Social" )]
    public EHeroRaces heroRace = EHeroRaces.A | EHeroRaces.B;

    [Description( "Recommended stats" )]
    [Custom( "Social" )]
    public List<EStat> recommendedStats;

    [Description( "List of available skins" )]
    [Custom("DBServer", "Social")]
    public List<DBPtr<HeroSkin>> heroSkins;

    [Description( "Units available to summon" )]
    public List<SummonedUnits> summonedUnits = new List<SummonedUnits>();

    [NoCode, Custom( "Social" ), Browsable( false )]
    public float totalStatsBudget;

    [Custom("Social")]
    public DBPtr<HeroResource> uniqueResource;
  }


  [DBVersion( 2 )]
  [TypeId( 0xB1988440 )]
  [UseTypeName( "HEROSKIN" )]
  [IndexField( "persistentId" )]
  public class HeroSkin : DBResource
  {
    [Custom( "DBServer", "Social" )]
    public bool legal = false;

    [Description( "Global Hero Skin ID" )]
    [Custom("DBServer", "Social")]
    public string persistentId = "";

    [Custom("DBServer", "DBServer", "Social")]
    public EGender gender = EGender.Male;

    [Description( "Human readable skin name" )]
    [Custom( "Social" )]
    public TextRef heroName = new TextRef();

    [Description( "Hero UI avatar picture for first faction" )]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> heroImageA;

    [Description( "Hero UI avatar picture for second faction" )]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> heroImageB;

    [Description( "Hero UI big avatar picture for first faction" )]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> heroRenderA;

    [Description( "Hero UI big avatar picture for second faction" )]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> heroRenderB;

    [Description( "Allowed hero races for skin" )]
    [Custom( "DBServer", "Social" )]
    public EHeroRaces heroRace = EHeroRaces.A | EHeroRaces.B;

    [Description( "Scene object" )]
    public DBPtr<DBSceneObject> sceneObject;
    
    [NoCode]
    [Custom("Social")]
    [Description( "Path to sound, played on hero click in castle. Relative path from Resources/Sound/, without file extension." )]
    public string lobbyAskSound;
  
    // sound list
    [FieldCategory( "Asks" )]
    [Description( "Hero acknowledgment sounds for this skin" )]
    public DBPtr<AskSoundsRef> askList;

    [FieldCategory("Asks")]
    [Description("Hero acknowledgment sounds for this skin (second hero state)")]
    public DBPtr<AskSoundsRef> askListSecondState;

    [Description( "Death parameters" )]
    public DBPtr<UnitDeathParameters> deathParameters;

    [Description( "Cost of skin in gold" )]
    [Custom( "Social" )]
    public int cost = 500;

    [Description( "Disable all acknowledgment sounds" )]
    [Custom( "Social" )]
    public bool mute = false;

    [Custom( "DBServer", "Social" )]
    [Description( "Allowed for bots" )]
    public bool botRoll = false;

    [Description("ID for antagonist")]
    [Custom("Social")]
    public string antagonistSkinId = "";
  }

  public enum EBotRollMode
  {
    Enabled,
    Disabled,
    DisabledAsEnemy
  }

  [TypeId( 0x2C5B3C40 )]
  [UseTypeName( "HROB" )]
  [IndexField( "id" )]
  public class Hero : BaseHero
  {
    [Custom( "DBServer", "Social" )]
    public string id;

    [Custom( "DBServer", "Social" )]
    public bool legal = true;

    [Custom( "DBServer" )]
    public EBotRollMode botRollMode = EBotRollMode.Enabled;

    [Description( "Таблица эффективности героя в по каждому классу, для матчмекинга" )]
    [Custom( "DBServer", "Social" )]
    [EnumArray(typeof(MMakingHeroClassEnum))]
    public List<float> classEfficiency = new List<float>();

    public bool canMount = false;
    public float askBlessCooldown = 0.0f;
    [Custom( "Social" )]
    public List<DBPtr<TalentsSet>> defaultTalentsSets = new List<DBPtr<TalentsSet>>();
	
    [NoCode, Custom("Social")]
    public DBPtr<TalentsSet> mightyTalentSet;
    
    [NoCode, Description( "For social client" )]
    [Custom( "Social" )]
    public LobbyHeroData lobbyData;
  }

  
}
