using System.Collections.Generic;
using System.ComponentModel;
using Scene.DBScene;
using Scene.DBSceneBase;
using libdb.DB;
using PF_Core.DBEffect;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBConsumable;
using PF_GameLogic.DBMinigamesTypes;
using Foundation.DBSystem;
using PF_GameLogic.DBAbility;

namespace PF_GameLogic.DBUnit
{
  [TypeId(0xF67ACC0)]
  [UseTypeName("SBLD")]
  [DBVersion(0)]
  public class Building : Unit
  {
    public EFaction faction = EFaction.Neutral;
    [FieldCategory("Chains")]
    public ERoute routeID = ERoute.Unassigned;
    public int routeLevel = 0;
    public DBPtr<DBSceneObject> ruinSceneObject;
    public float showRuinDelay = 0;
    [Description("Locator used for ruin placement")]
    public string ruinLocator = "Crash";
    public DBPtr<EffectBase> onDamageFragEffect;
    public DBPtr<BasicEffectStandalone> onDestructionEffect;
    public bool isDecoration = false;
    public Vec2 minimapIconOffset = new Vec2( 0.0f, 0.0f );
    [Description( "Периодичность левел-апа здания в секундах (0=никогда)" )]
    public float levelUpInterval = 0.0f;
    [Description("Апдейтить вижуал здания под туманом")]
    public bool updateUnderWarfog = false;
  }

  [NonTerminal]
  public class BattleBuilding : Building
  {
    [FloatMinMax(0, 360)]
    [Description("Tower turret initial and idle rotation (angles)")]
    public float baseRotation = 0.0f;
  }

  [TypeId(0x2C5BE300)]
  [UseTypeName("TOWR")]
  [DBVersion(2)]
  public class Tower : BattleBuilding
  {
  }

  [TypeId(0x2C6C1340)]
  [UseTypeName("TOWR")]
  public class ControllableTower : Tower
  {
  }

  [TypeId(0x2C5BE301)]
  [UseTypeName("QRTR")]
  public class Quarter : Building
  {
  }
  
  [TypeId(0x2C5BE302)]
  [UseTypeName("MBLD")]
  [DBVersion(2)]
  public class MainBuilding : Building
  {
    public int   aoeUnitsCount            = 10;
    public ESpellTarget aoeUnitsTypes     = ESpellTarget.All;
    public EFactionFlags aoeUnitsFactions = EFactionFlags.Opposite | EFactionFlags.Neutral;
    public float aoeRadius                = 20.0f;  
    public float minAOEDelay              = 10.0f;
    public float maxAOEDelay              = 20.0f;

    public DBPtr<PF_GameLogic.DBAbility.Ability>    aoeAttack;    
  }

  [TypeId(0xF61A400)]
  [UseTypeName("FNTN")]
  public class Fountain : Building
  {
  }

  [TypeId(0xF61AC41)]
  [UseTypeName("SHOP")]
  public class Shop : Building
  {
    public DBPtr<ConsumablesShop> shop;
  }

  [TypeId(0x9D62D2C1)]
  [UseTypeName("MINI")]
  public class MinigamePlace : Building
  {
    public DBPtr<MinigamePlaceParams> placeParams;
    public string minigameId;
    public Vec2 artifactsSpawnPosition;
    public DBPtr<BasicEffectAttached> onIdleEffect;
  }

  [TypeId(0xE78B3C80)]
  [UseTypeName("USBL")]
  public class UsableBuilding : Building
  {
  }

}