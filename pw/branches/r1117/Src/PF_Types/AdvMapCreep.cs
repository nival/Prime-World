//#include "..\Types\Scene2.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using PF_GameLogic.DBStats;
using Scene.DBSceneBase;

namespace PF_GameLogic.DBUnit
{
  
  public enum ECreepType
  {
    FactionalNormal,
    FactionalSiege,
    FactionalChampion,
    NeutralMinion,
    NeutralNormal,
    NeutralChampion,
    NeutralBoss,
  }
  
  [Flags]
  public enum ESpawnType
  {
    Before = 1,
    After  = 2,
  }

  [TypeId(0x1E59D400)]
  [UseTypeName( "CREEP" )]
  [DBVersion(3)]
  public class AdvMapCreep : Creature
  {
    public ECreepType creepType = ECreepType.FactionalNormal;
  }

  [TypeId(0xF6693C0)]
  [UseTypeName("CSTM")]
  public class CreepSpawnTimer : DBResource
  {
    public int startDelay = 0;
    public int spawnDelay = 1;

    [Description("Defines when CREEP should spawn, BEFORE or AFTER destruction of the barracks on the line, or both.")]
    public ESpawnType spawnType = ESpawnType.Before | ESpawnType.After;
  }
  
  public class SpawnObject
  {
    public DBPtr<AdvMapCreep> creep;
    public Placement place;
    public DBPtr<CreepSpawnTimer> timer;
  }

  [DBVersion(1)]
  public class LevelUpInfo
  {
    public bool lifetimeLevelUp = false;
    public float interval = -1.0f;
    public int increment = -1;

    [Description("Defines per-spawn level up interval, i.e. after each N spawns creep will get aditional levels (0 = no per-spawn levelups).")]
    public int spawnLevelUpInterval = 0;

    [Description("Defines per-spawn level up increment, i.e. for each per-spawn level up creep will get N aditional levels (0 = no increment).")]
    public int spawnLevelUpIncrement = 0;
  }

  public class BaseCreepSpawner : GameObject
  {
    public LevelUpInfo levelUpInfo;

    [Description("Defines first spawn time offset from the battle start delay (can be negative)(seconds).")]
    public float firstSpawnTimeOffset = 0.0f;
  }

  [TypeId(0x2C5AB3C0)]
  [UseTypeName( "CSPN" )]
  public class AdvMapCreepSpawner : BaseCreepSpawner
  {
    public List<SpawnObject> creeps = new List<SpawnObject>();
    public List<Vec2> path = new List<Vec2>();
    public EFaction faction = EFaction.Neutral;
    public ERoute routeID = ERoute.Center;
    public bool mustRegisterInAIWorld = true;

    [Description("Defines whether to use Evade logic for creeps in this spawner.")]
    public bool useEvade = true;

    [Description("Evade logic parameters.")]
    public EvadeData evadeParams;

    [Description("Defines maximum distance, to which creeps are allowed to walk away from its initial position. -1 = no limit. May be overriden by creep's settings")]
    public float limitWalkDistance = -1.0f;
  }

  public class NeutralSpawnObject
  {
    public DBPtr<AdvMapCreep> creep;
    public Placement offset;
    public int waveDelayToAppear = 0;

    [Description("Defines whether to use spawner's maximum allowed walk distance setting.")]
    public bool useSpawnerWalkLimit = true;

    [Description("Defines maximum distance, to which creep is allowed to walk away from its initial position. -1 = no limit. Effective only when useSpawnerWalkLimit = false.")]
    public float limitWalkDistance = -1.0f;

    [Description( "Ignore level diff when awarding a killer (for the case of custom neutralKillExperienceModifier map settings)" )]
    public bool specialAwarding = false;
  }
  
  public class AdvMapNeutralCreepsGroup
  {
    public List<NeutralSpawnObject> creeps = new List<NeutralSpawnObject>();
  }

  public class EvadeData
  {
    [Description("Defines maximum time to wait for enemy after receiving damage, before entering Evade State. (seconds)")]
    public float waitForEvadeTime = 3.0f;

    [Description("Defines maximum time to wait for next enemy after previous is died, before entering Evade State. (seconds)")]
    public float waitForNextTargetTime = 3.0f;

    [Description("Defines maximum time the Evade State may be active. (seconds)")]
    public float evadeTimeout = 60.0f;

    [Description("Defines health restore per second amount as a percent of maximum health. (percents in range 0-1)")]
    public float restoreHealthPercent = 0.2f;
  }

  [TypeId(0xF6163C0)]
  [UseTypeName( "NCSPN" )]
  [DBVersion(1)]
  public class AdvMapNeutralCreepSpawner : BaseCreepSpawner
  {
    public List<AdvMapNeutralCreepsGroup> groups = new List<AdvMapNeutralCreepsGroup>();
    public int spawnDelay = 45;
    public int waveCount = 0;
    public int baseLevel = 0;
    public int naftaForGroupKill = 0;
    public EMinimapIcons minimapIcon = EMinimapIcons.Default;
    public bool showMinimapIcon = true;

    [Description("If defined, spawned neutrals will go by path instead of stay on spawn point")]
    public List<Vec2> path = new List<Vec2>();

    [Description("Defines maximum distance, to which creeps are allowed to walk away from its initial position. -1 = no limit. May be overriden by creep's settings")]
    public float limitWalkDistance = -1.0f;

    [Description("Defines whether to use Evade logic for creeps in this spawner.")]
    public bool useEvade = true;

    [Description("Evade logic parameters.")]
    public EvadeData evadeParams;

    [Description("Крипы спаунера агрессивные.")]
    public bool isAggressive = false;

    [Description("Способ применения модификатора статов от мощи карты")]
    public MapForceStatModifierApplication mapForceStatModifierApplication = MapForceStatModifierApplication.All;
  }
}