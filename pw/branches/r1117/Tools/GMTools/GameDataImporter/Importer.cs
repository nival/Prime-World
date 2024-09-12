using DAL.Entities;
using DAL.Repositories;

namespace GameDataImporter
{
  public class Importer
  {
    private readonly IDatabaseInteraction database;
    private readonly IGameDataInteraction gamedata;

    internal Importer(IDatabaseInteraction dbi, IGameDataInteraction gdi)
    {
      database = dbi;
      gamedata = gdi;
    }

    internal void Run()
    {
      database.Update(gamedata.GetCharacters(), new CharacterRepository());

      var abilitytypes = gamedata.GetAbilityTypes();
      database.Update(gamedata.GetAbilityTypes(), new AbilityTypeRepository());

      database.Update(gamedata.GetTalents(abilitytypes), new TalentRepository());
      //database.Update(gamedata.GetEntities(), new TalentUpgradeEntityRepository());

      database.Update(gamedata.GetImpulsiveBuffs(), new ImpulsiveBuffRepository());

      database.Update(gamedata.GetMGBoosts(), new MGBoostRepository());
      
      database.Update(gamedata.GetBuildings(), new BuildingRepository());

      database.Update(gamedata.GetUnitTypes(), new UnitTypeRepository());

      database.Update(gamedata.GetCreatures(), new CreatureRepository());

      database.Update(gamedata.GetAchievements(), new AchievementRepository());

      database.Update(gamedata.GetConsumables(), new ConsumableRepository());

      database.Update(gamedata.GetQuests(), new Repository<Quest>());

      database.Update(gamedata.GetUnionRunes(), new Repository<Rune>());

      database.Update(gamedata.GetCastleBuildings(), new Repository<CastleBuilding>());

      database.Update(gamedata.GetGuildBuffs(), new Repository<GuildBuff>());

      database.Update(gamedata.GetGuildShopItems(), new Repository<GuildShopItem>());
    }
  }
}