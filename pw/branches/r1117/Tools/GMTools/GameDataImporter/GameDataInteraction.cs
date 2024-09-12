using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Text;
using DAL.Entities;
using DBTypes;
using EditorLib.IO;
using libdb.DB;
using log4net;
using Building = DAL.Entities.Building;
using Consumable=DAL.Entities.Consumable;
using Creature = DAL.Entities.Creature;
using GuildBuff = DAL.Entities.GuildBuff;
using GuildShopItem = DAL.Entities.GuildShopItem;
using ImpulsiveBuff = DAL.Entities.ImpulsiveBuff;
using Quest = DAL.Entities.Quest;
using Talent = DAL.Entities.Talent;

namespace GameDataImporter
{
  public interface IGameDataInteraction : IDisposable
  {
    IEnumerable<Character> GetCharacters();
    IEnumerable<AbilityType> GetAbilityTypes();
    IEnumerable<Talent> GetTalents(IEnumerable<AbilityType> abilitytypes);
    IEnumerable<ImpulsiveBuff> GetImpulsiveBuffs();
    IEnumerable<MGBoost> GetMGBoosts();
    IEnumerable<Building> GetBuildings();
    IEnumerable<Creature> GetCreatures();
    IEnumerable<UnitType> GetUnitTypes();
    IEnumerable<Achievement> GetAchievements();
    IEnumerable<Consumable> GetConsumables();
    IEnumerable<Quest> GetQuests();
    IEnumerable<Rune> GetUnionRunes();
    IEnumerable<CastleBuilding> GetCastleBuildings();
    IEnumerable<GuildBuff> GetGuildBuffs();
    IEnumerable<GuildShopItem> GetGuildShopItems();
  }
  
  public class GameDataInteraction : IGameDataInteraction
  {
    private static ILog _log = LogManager.GetLogger(typeof (GameDataInteraction));

    public GameDataInteraction()
    {
      var sw = Stopwatch.StartNew();
      EditorApplication.Editor.Initialize(null);
      _log.InfoFormat("Editor init in {0} ms", sw.ElapsedMilliseconds);
    }

    public IEnumerable<Character> GetCharacters()
    {
      var heroesDBPtr = DataBase.Get<HeroesDB>(DBID.FromString("/Heroes/_.HRDB"));
      return heroesDBPtr.Get().heroes
          .Select(hptr =>
          {
            Hero hero = hptr.Get();
            return new Character
            {
              Id = Crc32(hero.id),
              Name = hero.id,
              DBID = hero.DBId.ToString(),
              Gender = (int)hero.gender
           };
        });
    }

    public IEnumerable<AbilityType> GetAbilityTypes()
    {
      var abilitytypes = new List<AbilityType>();
      foreach (EAbilityType a in Enum.GetValues(typeof(EAbilityType)))
      {
        abilitytypes.Add(new AbilityType { Id = (int)a, Name = a.ToString() });
      }
      return abilitytypes;
    }

    public IEnumerable<Talent> GetTalents(IEnumerable<AbilityType> abilitytypes)
    {
      var talents = new List<Talent>();

      var heroesDBPtr = DataBase.Get<HeroesDB>(DBID.FromString("/Heroes/_.HRDB"));
      var heroes = heroesDBPtr.Get().heroes.Select(hparam => hparam.Get());
      foreach (var hero in heroes)
      {
        // Добавление автоатаки героя в справочник талантов.
        var autoAttack = hero.attackAbility.Get();
        int id = Crc32(autoAttack.DBId.NameFormatted);
        if (!talents.Exists(t => t.Id == id))
          talents.Add(new Talent
                        {
                          Id = id,
                          Name = String.Format("Автоатака: {0} ({1})", hero.heroNameA, hero.heroNameB),
                          DBID = autoAttack.DBId.NameFormatted,
                          Description = autoAttack.name.ToString(),
                          Cooldown = 0f,
                          AbilityType = abilitytypes.Single(at => at.Id == (int)autoAttack.type),
                          Rarity = TalentRarity.Class
                        });
      }

      List<DBID> dbids;
      ObjectsSelector.CollectObjects(EditorApplication.Editor, "/Items/Talents", typeof (DBTypes.Talent), true, false, out dbids);

      foreach (var dbtalent in dbids.Select(dbid => DataBase.Get<DBTypes.Talent>(dbid).Get()))
      {
        float cooldown;
        if (!float.TryParse(dbtalent.cooldownTime.sString.TrimEnd('f'), NumberStyles.Float, NumberFormatInfo.InvariantInfo, out cooldown))
          cooldown = 0;

        if (String.IsNullOrEmpty(dbtalent.persistentId))
        {
          _log.Warn("Empty talentId in the talent " + dbtalent.DBId);
          continue;
        }

        talents.Add(new Talent
                      {
                        Id = Crc32(dbtalent.persistentId),
                        TalentId = dbtalent.persistentId,
                        Name = dbtalent.name.ToString(),
                        DBID = dbtalent.DBId.ToString(),
                        Cooldown = cooldown,
                        Description = dbtalent.description.ToString(),
                        Tour = dbtalent.minLevel + 1, // в игровой базе уровни считаются с 0, а нам нужно с 1
                        Rarity = (TalentRarity)dbtalent.rarity,
                        Budget = dbtalent.budget,
                        AbilityType = new AbilityType {Id = (int) dbtalent.type, Name = dbtalent.type.ToString()}
                      });
      }

      // собираем энтити и засовываем их в список талантов, т.к. статистика прихода и трат энтитей будет писаться в лог талантов
      dbids.Clear();
      ObjectsSelector.CollectObjects(EditorApplication.Editor, "/Social/TalentUpgrade", typeof(DBTypes.TalentUpgradeEntity), true, false, out dbids);

      foreach (var upgradeEntity in dbids.Select(dbid => DataBase.Get<DBTypes.TalentUpgradeEntity>(dbid).Get()))
      {
        if (String.IsNullOrEmpty(upgradeEntity.persistentId))
        {
          _log.Warn("Empty persistentId in the talentUpgradeEntity " + upgradeEntity.DBId);
          continue;
        }

        talents.Add(new Talent
        {
          Id = Crc32(upgradeEntity.persistentId),
          TalentId = upgradeEntity.persistentId,
          Name = upgradeEntity.persistentId,
          DBID = upgradeEntity.DBId.ToString(),
          Cooldown = 0,
          Description = upgradeEntity.description.ToString(),
          Tour = upgradeEntity.talentLevelLimit + 1, // в игровой базе уровни считаются с 0, а нам нужно с 1
          Rarity = (TalentRarity)upgradeEntity.type,
          Budget = upgradeEntity.probability,
          AbilityType = new AbilityType { Id = (int)upgradeEntity.type, Name = upgradeEntity.type.ToString() }
        });
      }

      return talents;
    }

    public IEnumerable<ImpulsiveBuff> GetImpulsiveBuffs()
    {
      var buffsPtr = DataBase.Get<ImpulsiveBuffsContainer>(DBID.FromString("/Impulses/_.IBCN"));

      return buffsPtr.Get().buffs
        .Select(b => b.buff.Get())
        .Select(b => new ImpulsiveBuff
                       {
                         Id = b.DBId.GetHashCode(),
                         Name = b.name.ToString(),
                         DBID = b.DBId.ToString()
                       });
    }

    public IEnumerable<MGBoost> GetMGBoosts()
    {
      var boosts = new List<MGBoost>();
      foreach (EBoostType b in Enum.GetValues(typeof(EBoostType)))
      {
        boosts.Add(new MGBoost {Id = (int) b, Name = b.ToString()});
      }
      return boosts;
    }

    public IEnumerable<Building> GetBuildings()
    {
      var buildings = new List<Building>();
      List<DBID> dbids;
      var sw = Stopwatch.StartNew();
      ObjectsSelector.CollectObjects(EditorApplication.Editor, "/Maps", typeof(AdvMap), true, false, out dbids);
      _log.InfoFormat("Collect objects in {0} ms", sw.ElapsedMilliseconds);
      sw.Reset();
      sw.Start();
      foreach(var dbid in dbids)
      {
        var mapobjects = DataBase.Get<AdvMap>(dbid).Get().objects;
        foreach(AdvMapObject mapobj in mapobjects)
        {
          DBTypes.GameObject go = mapobj.gameObject.Get();
          if (go is DBTypes.Building)
          {
            int id = go.DBId.GetHashCode();
            if (!buildings.Exists(b => b.Id == id))
              buildings.Add(new Building
                              {
                                Id = id,
                                Name = go.DBId.ToString(),
                                Description = ((DBTypes.Building) go).description.ToString()
                              });
          }
        }
      }
      _log.InfoFormat("Select game objects from dbids in {0} ms", sw.ElapsedMilliseconds);
      return buildings;
    }

    public IEnumerable<Creature> GetCreatures()
    {
      var creatures = new List<Creature>();
      List<DBID> dbids = new List<DBID>(), dbids_part;
      var sw = Stopwatch.StartNew();
      foreach (var path in new[] { "/Creeps", "/Summons", "/Pets" })
      {
        ObjectsSelector.CollectObjects(EditorApplication.Editor, path, typeof(DBTypes.Creature), true, true, out dbids_part);
        dbids.AddRange(dbids_part);
      }
      _log.InfoFormat("Collect objects in {0} ms", sw.ElapsedMilliseconds);
      sw.Reset();
      sw.Start();
      foreach (var dbid in dbids)
      {
        var creep = DataBase.Get<DBTypes.Creature>(dbid).Get();
        creatures.Add(new Creature
        {
          Id = creep.DBId.GetHashCode(),
          Name = creep.DBId.ToString()
        });
      }

      // В список существ добавляются еще и герои (потому что, например ghostlord умеет суммонить убиенных героев)
      creatures.AddRange(GetCharacters().Select(c => new Creature {Id = c.Id, Name = c.Name}));

      _log.InfoFormat("Select game objects from dbids in {0} ms", sw.ElapsedMilliseconds);
      return creatures;
    }

    public IEnumerable<UnitType> GetUnitTypes()
    {
      var unittypes = new List<UnitType>();
      foreach (EUnitType u in Enum.GetValues(typeof(EUnitType)))
      {
        unittypes.Add(new UnitType { Id = (int)u, Name = u.ToString() });
      }
      return unittypes;
    }

    public IEnumerable<Achievement> GetAchievements()
    {
      var result = new List<Achievement>();
      
      List<DBID> dbids;
      ObjectsSelector.CollectObjects(EditorApplication.Editor, "/GameLogic/Statistic", typeof(AchievBase), true, true, out dbids);

      foreach(var dbid in dbids)
      {
        var achievement = DataBase.Get<AchievBase>(dbid).Get();
        result.Add(new Achievement
                     {
                       Id = achievement.DBId.GetHashCode(),
                       DBID = achievement.DBId.ToString(),
                       Name = achievement.name.ToString()
                     });
      }

      var maplist = DataBase.Get<MapList>(DBID.FromString("/Maps/_.MAPLST")).Get();
      foreach (var map in maplist.maps.Select(m => m.Get()))
      {
        if (map.scoringTable.IsValid && map.scoringTable.Get().achievementsList != null)
        {
          foreach (var achievement in map.scoringTable.Get().achievementsList.Select(a => a.Get()))
          {
            if (achievement != null && !result.Exists(r => r.Id == achievement.DBId.GetHashCode()))
            {
              result.Add(new Achievement
                           {
                             Id = achievement.DBId.GetHashCode(),
                             DBID = achievement.DBId.NameFormatted,
                             Name = String.Format("{0} ({1})", achievement.name, map.title)
                           });
            }
          }
        }
      }

      return result;
    }

    public IEnumerable<Consumable> GetConsumables()
    {
      var result = new List<Consumable>();

      var consumable_ptrs = new List<DBPtr<DBTypes.Consumable>>();
      // Итемы из обычного магазина
      consumable_ptrs.AddRange(DataBase.Get<ConsumablesShop>(DBID.FromString("/Buildings/DefaultStats/Basic.CNSH")).Get().items);
      // Итемы из секретного магазина
      consumable_ptrs.AddRange(DataBase.Get<ConsumablesShop>(DBID.FromString("/Buildings/DefaultStats/Secret.CNSH")).Get().items);
      // Итемы из миниигры
      consumable_ptrs.AddRange(DataBase.Get<DBEaselData>(DBID.FromString("/MiniGames/Minigame02/GameLogic/EaselMinigameData.xdb")).Get().artifacts.artifact);
      
      // Петы из папки Consumables
      List<DBID> item_dbids;
      ObjectsSelector.CollectObjects(EditorApplication.Editor, "/Items/Consumables", typeof(DBTypes.Consumable), true, true, out item_dbids);
      item_dbids.Where(dbid => dbid.Name.Contains("Pet_")).ToList()
        .ForEach(dbid => consumable_ptrs.Add(DataBase.Get<DBTypes.Consumable>(dbid)));

      foreach (var consumable in consumable_ptrs.Select(ptr => ptr.Get()))
      {
        if (!result.Exists(c => c.DBID == consumable.DBId.ToString()))
        {
          result.Add(new Consumable
                       {
                         Id = consumable.DBId.GetHashCode(),
                         DBID = consumable.DBId.ToString(),
                         Name = consumable.name.ToString(),
                         NaftaCost = consumable.naftaCost
                       });
        }
      }

      return result;
    }

    public IEnumerable<Quest> GetQuests()
    {
      var questsDBPtrs = DataBase.Get<SocialRoot>(DBID.FromString("/Social.ROOT")).Get()
        .Quests.Select(q => q.Get()) // get quest lines
        .SelectMany(q => q.quests);  // get quests

      var result = questsDBPtrs.Select(q => q.Get()).Distinct()
        .Select(dbquest => new Quest
                             {
                               Id = Crc32(dbquest.persistentId),
                               QuestId = dbquest.persistentId,
                               Name = dbquest.Title.GetText()
                             }).ToList();
      var ratingDecreaseQuest =
        DataBase.Get<SocialRoot>( DBID.FromString( "/Social.ROOT" ) ).Get().RatingDecreaseByTime.Get().ratingUpdateQuest
          .Get();
      result.Add( new Quest
                  {
                    Id = Crc32( ratingDecreaseQuest.persistentId ),
                    QuestId = ratingDecreaseQuest.persistentId,
                    Name = ratingDecreaseQuest.Title.GetText()
                  });
      return result;
    }

    public IEnumerable<Rune> GetUnionRunes()
    {
        return GetGoldRunes().Concat(GetUpgHeroTalRunes());
    }

    private List<Rune> GetGoldRunes()
    {
      List<DBID> dbids;
      ObjectsSelector.CollectObjects(EditorApplication.Editor, "/UI/Content/MarketingEvents", typeof(GoldLampEvent), true, true, out dbids);
      return dbids
        .Select(dbid => DataBase.Get<GoldLampEvent>(dbid).Get<GoldLampEvent>())
        .Select(item => new Rune
                          {
                            Id = Crc32(item.DBId.NameFormatted),
                            Name = item.DBId.NameFormatted,
                            Percent = item.bonusPersent
                          }).ToList();
    }

    private List<Rune> GetUpgHeroTalRunes()
    {
        List<DBID> dbids;
        ObjectsSelector.CollectObjects(EditorApplication.Editor, "/UI/Content/MarketingEvents", typeof(UpgradeHeroTalentsEvent), true, true, out dbids);
        return dbids
          .Select(dbid => DataBase.Get<UpgradeHeroTalentsEvent>(dbid).Get<UpgradeHeroTalentsEvent>())
          .Select(item => new Rune
                          {
                              Id = Crc32(item.DBId.NameFormatted),
                              Name = item.DBId.NameFormatted,
                              Percent = 300
                          }).ToList();
    }

    public IEnumerable<CastleBuilding> GetCastleBuildings()
    {
      List<DBID> dbids;
      ObjectsSelector.CollectObjects(EditorApplication.Editor, "/Social/Constructions", typeof(Constructon), true, true, out dbids);
      return dbids
        .Select(dbid => DataBase.Get<Constructon>(dbid).Get<Constructon>())
        .Select(item => new CastleBuilding
                          {
                            Id = Crc32(item.persistentId),
                            Name = item.persistentId,
                            Description = String.Format("{0}/{1}", item.CaptionA, item.CaptionB),
                            MaxLevel = item.Levels.Count()
                          });

    }


    public IEnumerable<GuildBuff> GetGuildBuffs()
    {
      var items = DataBase.Get<SocialRoot>(DBID.FromString("/Social.ROOT")).Get()
                          .GuildBuffsCollection.Get().buffs.Select(iptr => iptr.Get());
      return items.Select(item => new GuildBuff
                                    {
                                      Id = Crc32(item.persistentId),
                                      Name = item.persistentId,
                                      DBID = item.DBId.ToString()
                                    })
                                    .Distinct(); // Подпорка на случай, если дизайнеры заведут одинаковые итемы
    }


    public IEnumerable<GuildShopItem> GetGuildShopItems()
    {
      var items = DataBase.Get<SocialRoot>(DBID.FromString("/Social.ROOT")).Get()
                          .GuildShopItems.Select(iptr => iptr.Get());
      return items.Select(item => new GuildShopItem
                                    {
                                      Id = Crc32(item.persistentId),
                                      Name = item.persistentId,
                                      DBID = item.DBId.ToString(),
                                      Description = item.description.GetText()
                                    });
    }


    private int Crc32(string value)
    {
      return (int) Crc32ChecksumGenerator.GenerateChecksum(Encoding.ASCII.GetBytes(value));
    }


    protected void Dispose(bool disposing)
    {
      var sw = Stopwatch.StartNew();
      EditorApplication.Editor.Terminate();
      _log.InfoFormat("Terminate Editor in {0} ms", sw.ElapsedMilliseconds);
    }

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }

    ~GameDataInteraction()
    {
      Dispose(false);
    }
  }
}