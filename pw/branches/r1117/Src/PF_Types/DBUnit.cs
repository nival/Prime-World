//#include "../Types/Terrain.cs"
//#include "../Types/Scene2.cs"
//#include "Effect.cs"
//#include "DBMinimap.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBGameLogic;
using PF_GameLogic.DBStats;
using Render.DBRenderResources;
using Scene.DBScene;
using Scene.DBSceneBase;
using Terrain.DBTerrain;
using Foundation.DBSystem;
using Render.DBRender;

namespace PF_GameLogic.DBUnit
{

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum EUnitCategory
  {
    Invalid,
    Heroes,
    Creeps,
    Buildings
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("UTCT")]
  public class UnitCategories : DBResource
  {
    [EnumArray(typeof(EUnitType))]
    public List<EUnitCategory> elements = new List<EUnitCategory>();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class UnitCategoryParams
  {
    public int selectionPriority;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [UseTypeName("UCP")]
  public class UnitCategoriesParams : DBResource
  {
    [EnumArray(typeof(EUnitCategory))]
    public List<UnitCategoryParams> elements = new List<UnitCategoryParams>();
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF641B40)]
  [UseTypeName("SSO")]
  public class SingleStateObject : GameObject
  {
    public DBPtr<DBSceneObject> sceneObject;
  }

  public class TransactionEffects
  {
    public DBPtr<EffectBase> effectIn;
    public DBPtr<EffectBase> effectOut;
  }

	[TypeId( 0x8D81AB80 )]
	[UseTypeName( "TREF" )]
	[DBVersion( 1 )]
	public class MSOTransactions : DBResource
	{
		public TransactionEffects effectN;
		public TransactionEffects effectA;
		public TransactionEffects effectB;
	}

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2B832BC0)]
  [UseTypeName("CRITTER")]
  public class Critter : SingleStateObject
  {
    [Description("На сколько можем отбегать от ''базы''")]
    public float moveRadius = 0.0f;

    [Description("На каком расстоянии замечаем героев")]
    public float alarmRadius = 0.0f;

    [Description("Через сколько секунд после ухода героя возвращаемся")]
    public float calmDownTime = 0.0f;

    [Description("Скорость перемещения")]
    public float moveSpeed = 0.0f;

    [Description( "Виден ли этот Critter под варфогом. Если в true, то он виден, но при этом фризится" )]
    public bool isVisibleUnderWarfog = false;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xF64B3C0)]
  [UseTypeName("MSO")]
  [DBVersion(2)]
  public class MultiStateObject : GameObject
  {
    [EnumArray(typeof(ENatureType))]
    public List<DBPtr<DBSceneObject>> sceneObjects = new List<DBPtr<DBSceneObject>>();

    [EnumArray(typeof(ENatureType))]
    public List<DBPtr<DBSceneObject>> nightSceneObjects = new List<DBPtr<DBSceneObject>>();

    [Description( "MSO transactions" )]
    public DBPtr<MSOTransactions> effects;

    [Description("MSO night transactions")]
    public DBPtr<MSOTransactions> nightEffects;

    [Description("Непрозрачный для игрока. Если этот флаг выставлен в true, то герой не может видеть объекты за этим объектом.")]
    public bool opaque = false;

    [Description("Fade offset in time")]
    public float fadeInOffset = 0.0f;

    [Description( "Время падения дерева. Должно совпадать с длиной трека drop." )]
    public float dropTime = 1.0f;

    [Description("Виден ли этот Object под варфогом. Если в true, то он виден.")]
    public bool isVisibleUnderWarfog = false;

    [Description("Явно разделяет дневное и ночное состояния. Если false, то при отсутствии дневных или ночных SceneObject'ов вместо них будут использоваться, соответственно, ночные или дневные.")]
    public bool distinct = false;
  }

  public enum EDamageType
  {
    Material = EApplicatorDamageType.Material,
    Energy = EApplicatorDamageType.Energy,
  }

  //////////////////////////////////////////////////////////////////////////
  public enum ESelectionAoeVisualType
  {
    Primary = 0,
    Secondary = 1,
  }

  [TypeId( 0xB1A4F2C1 )]
  [UseTypeName( "VISAOE" )]
  [DBVersion( 1 )]
  public class AoeVisual : DBResource
  {
    [FieldCategory( "UI" )]
    [Description( "Aoe radius in meters." )]
    public ExecutableFloatString size = new ExecutableFloatString( "0.0f" );

    [FieldCategory( "UI" )]
    [Description( "Enables/disables radius." )]
    public ExecutableBoolString enabled = new ExecutableBoolString( "true" );

    [FieldCategory( "UI" )]
    [Description( "Aoe zone material." )]
    public DBPtr<AOEMaterial> material;
  }

  [TypeId(0xE7A8B300)]
  [UseTypeName("IACT")]
  public class Interaction : DBResource
  {
    [Description( "Ability that will be used by hero on interaction" )]
    public DBPtr<Ability> externalAbility;

    [Description("Фракции которые могут юзать этот юнит")]
    public EFactionFlags allowedFactions = EFactionFlags.Self;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E678C00)]
  [UseTypeName("UNIT")]
  [DBVersion(2)]
  public class Unit : SingleStateObject
  {
    [FieldCategory("Stats")]
    [Custom( "Social" )]
    public DBPtr<StatsContainer> stats;

    [FieldCategory("Targeting")]
    public DBPtr<UnitTargetingParameters> targetingParams;
    
    [FieldCategory("Base attack")]
    [Description("Basic attack ability of the unit")]
    public DBPtr<BaseAttack> attackAbility;

    [FieldCategory("Description")]
    [Description("Basic human readable name for a unit")]
    public TextRef description = new TextRef();

    [Description("Common UI avatar picture for first faction")]
    public DBPtr<Render.DBRenderResources.Texture> image;

    [Description("Unit health bar width in UI pixels")]
    public int overtipBarsWidth = 0;

    [Description("Vertical offset from middle of unit's AABB top face to health bar center")]
    public float overtipVerticalOffset = 0.0f;

    [Description("Type of attack, native to the unit")]
    [Custom( "Social" )]
    public EDamageType nativeAttack = EDamageType.Material;

    [Description("Type of defense, native to the unit")]
    public EDamageType nativeDefence = EDamageType.Material;

    [Description("Unit visual parameters of death")]
    public DBPtr<UnitDeathParameters> deathParameters;

    [Description("Абилки кричи")]
    [EnumArray(typeof(EAbility))]
    public List<DBPtr<Ability>> abilities = new List<DBPtr<Ability>>();

		[Description( "Object size in meters" )]
		public float size = 2;
		[Description( "Object size for pathfinding in meters, specify -1 for use value from size" )]
		public float sizeDynamic = -1;

    [Description("Насколько выравнивать по нормали (0 — никак, 1 — полностью)")]
    public float normalLevelling = 0.0f;

    [Description("Custom minimap icon")]
    public EMinimapIcons minimapIcon = EMinimapIcons.Default;

    [Description( "Visual parameters of the area of effect" )]
    [EnumArray( typeof( ESelectionAoeVisualType ) )]
    public List<DBPtr<AoeVisual>> selectionAoe = new List<DBPtr<AoeVisual>>();

    [Description( "Качество поиска пути. Для героев ставить 10, для остальных 1" )] 
    public int pathFindingSteps = 1;

    [Description( "Interaction params" )]
    public DBPtr<Interaction> interaction;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x9E722340)]
  [UseTypeName("UNIT")]
  [DBVersion(2)]
  [Custom( "Social" )]
  public class Creature : Unit
  {
    public HDRColor recolor = new HDRColor( 0.0f, 0.0f, 0.0f, 0.0f );

  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId( 0xB199C400 )]
  [UseTypeName( "CREEPSKIN" )]
  [DBVersion( 1 )]
  [IndexField( "persistentId" )]
  public class CreepSkin : DBResource
  {
    [Description( "Hero Skin ID" )]
    [Custom( "Social" )]
    public string heroPersistentId  = "";

    [Description( "Human readable skin name" )]
    [Custom( "Social" )]
    public TextRef description = new TextRef();

    [Description( "Hero UI avatar picture" )]
    [Custom( "Social" )]
    public DBPtr<Render.DBRenderResources.Texture> image;

    [Description( "Scene object" )]
    public DBPtr<DBSceneObject> sceneObject;

    [Description( "Death parameters" )]
    public DBPtr<UnitDeathParameters> deathParameters;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  [TypeId( 0xB199C440 )]
  [UseTypeName( "SUMMONED" )]
  [DBVersion( 1 )]
  public class Summoned : Creature
  {
    [Description( "List of available skins" )]
    public List<DBPtr<CreepSkin>> creepSkins;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x8E547B04)]
  [UseTypeName("SMPL")]
  public class SimpleObject : SingleStateObject
  {
    [FieldCategory("Destructible")]
    public int health = -1;

    [Description("Непрозрачный для игрока. Если этот флаг выставлен в true, то герой не может видеть объекты за этим объектом.")]
    public bool opaque = false;

    [Description("Виден ли этот Object под варфогом. Если в true, то он виден")]
    public bool isVisibleUnderWarfog = false;
  }

  public enum BooleanLockMode
  {
    Lock = 0,
    UnLock = 1,
  }

  [TypeId(0xE7879C40)]
  [UseTypeName("OBST")]
  public class AdvMapObstacle : GameObject
  {
    [Description("Непрозрачный для игрока. Если этот флаг выставлен в true, то герой не может видеть объекты за этим объектом.")]
    public bool opaque = false;

    [Description("Lock/Unlock области")]
    public BooleanLockMode LockMode = BooleanLockMode.Lock;
  }

  [TypeId(0xEF91A282)]
  [UseTypeName("WFUB")]
  public class WarFogUnblock : GameObject
  {
      [Description("Объект открывает warfog в данном радиусе")]
      public int radius = 0;

      [Description("Объект открывает туман войны только для указаной фракции")]
      [HideEnumValues( "Self", "Opposite" )]
      public EFactionFlags faction = EFactionFlags.FactionBurn | EFactionFlags.FactionFreeze;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0x2C616C00)]
  [UseTypeName("TREE")]
  [DBVersion(1)]
  public class TreeObject : MultiStateObject
  {
    [EnumArray(typeof(ENatureType))]
    public List<DBPtr<DBSceneObject>> stubsSceneObjects = new List<DBPtr<DBSceneObject>>();

    [EnumArray(typeof(ENatureType))]
    public List<DBPtr<DBSceneObject>> nightStubsSceneObjects = new List<DBPtr<DBSceneObject>>();

    public bool wonderfulTree = false;
  }
  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [TypeId(0xB768C41)]
  [UseTypeName("FLAG")]
  public class Flagpole : Unit
  {
    [Description("Выбор башен, которые дают неуязвимость флагу")]
    public DBPtr<TargetSelector> ownerTowers;

    [Description("Эффект")]
    [EnumArray(typeof(ETeamID))]
    public List<DBPtr<EffectBase>> effect = new List<DBPtr<EffectBase>>();

    [Description("Иконки для разных фракций")]
    [EnumArray(typeof(ETeamID))]
    public List<DBPtr<Texture>> factionImages = new List<DBPtr<Texture>>();

    [Description("Описание для разных фракций")]
    [EnumArray(typeof(ETeamID))]
    public List<TextRef> factionDescriptions = new List<TextRef>();
  }
  [TypeId( 0x9A9BA381 )]
  [UseTypeName( "FLAG" )]
  public class ScriptedFlagpole : Flagpole
  {

  }

  [Flags]
  public enum MapForceStatModifierApplication
  {
    None = 0,
    Base = (1 << 0),
    LevelUp = (1 << 1),
    All = (Base | LevelUp),
  }
}


