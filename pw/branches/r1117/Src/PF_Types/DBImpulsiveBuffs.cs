using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBGameLogic;


namespace PF_GameLogic.DBImpulsiveBuffs
{
  public enum ImpulsiveEventType 
  {
    HeroEvent,
    TowerEvent
  }

  [NonTerminal]
  //[FactoryBase("Create", "NWorld::ImpulsiveEvent", Define = "!SERVER_DB")]
  [FactoryBase( "Create", "NWorld::ImpulsiveEvent", "class NWorld::ImpulsiveBuffsManager* _buffsManager", Define = "!SERVER_DB" )]
  [IndexField("caption")]
  public class ImpulsiveEvent : DBResource
  {
    [NoCode]
    public string caption = string.Empty;
    public bool suggestTarget = false;
    public ImpulsiveEventType eventType = ImpulsiveEventType.HeroEvent;
  }

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  public enum ImpulseBuffClass
  {
    Class_BuffTower,
    Class_BuffHero,
  }

  public class AccessInfo
  {
    [Description("Уровень доступности импульса (0, 1, ... )")]
    public int level = 0;

    [Description("Сколько очков добавится герою при взятии этого импульса")]
    public int points = 1;
  }

  [IndexField("caption")]
  [DBVersion(1)]
  public class ImpulsiveBuff
  {
    public DBPtr<Ability> buff;
    public List<DBPtr<ImpulsiveEvent>> events = new List<DBPtr<ImpulsiveEvent>>();

    [Description("Информация про доступность импульса")]
    public AccessInfo accessInfo = new AccessInfo();

    public string caption = "";
    public bool canBeOfferedToDead = false;
    
    [Description("Force buff message display time. If 0 - used default time is used")]
    public float offerTime = 0.0f;

    [Description("Cooldown of that impulse to be activated")]
    public float cooldown = 10.0f;

    [Description("Cooldowns are shared through the same groups")]
    public string cooldownGroup = "A";

    [FloatMinMax(0.0f, 1.0f)]
    [Description("Priority")]
    public float priority = 0.3f;

    [Description("Specifies buff target class")]
    public ImpulseBuffClass buffClass = ImpulseBuffClass.Class_BuffHero;

    [Description("If true - creates new state, cancels current states, etc; if false - just uses external ability")]
    public bool isSimple = true;

    [Description( "Describes if this impulse can be bought only once per team" )]
    public bool oncePerTeam = false;
  }

  public class UnitCountingWeights
  {
    public string setName = "";

    [EnumArray(typeof(EUnitType))]
    public List<int> weights = new List<int>();
  }

  public class AccessCost
  {
    [Description("Количество очков, необходимое для получения импульств этого уровня.")]
    public int impulsesPoints = 0;

    [Description("Импульсы из скольки последних игр (включая текущую) учитываем. 0 — без ограничений.")]
    public int gamesLimit = 0;
  }

  [TypeId(0xF664BC0)]
  [DBVersion(2)]
  [UseTypeName("IBCN")]
  public class ImpulsiveBuffsContainer : DBResource
  {
    [Description("all services cost")]
    public DBPtr<PF_GameLogic.DBGameLogic.BuyServicesContainer> servicesCosts;

    [Description("Heroes & Tower impulsive buffs")]
    [EnumArray(typeof(PF_GameLogic.DBGameLogic.ImpulseBuffs))]
    public List<ImpulsiveBuff> buffs = new List<ImpulsiveBuff>();
    public List<AccessCost> accessLevelsCosts = new List<AccessCost>();

    public float globalCooldown = 0.0f;
    public float buffUseEventLifeTime = 15.0f;
    public float priestessEventsLifeTime = 15.0f;

    public List<UnitCountingWeights> unitCountingParams = new List<UnitCountingWeights>();
  }

}
