namespace ControlCenter.Areas.GM.Models
{
  //Emuns from SS. If you change them - you must change them in SS too. I believe this will be fixed in NUM_TASK
  public enum ResourcesEnum
  {
    // ReSharper disable InconsistentNaming
    Resource1 = 0,
    Resource2,
    Resource3,
    Resource1_Rare,
    Resource2_Rare,
    Resource3_Rare,
    Perl,
    RedPerl,
    Silver,
    Gold,
    Population,
    DontUseThis,
    DontUseThis2,
    TalentsToPay,
    DontUseThis3,
    CustomCurrency
    // ReSharper restore InconsistentNaming
  }

  public enum DynamicQuestCollectingTypeEnum
  {
    // ReSharper disable InconsistentNaming
    score, // Обычные generic сессионные очки
    specialPoints, // Используется для режима "Испытания"
    finalLevel,    //уровень героя к концу сессии
    kills,    //количество убийств вражеских героев
    deaths,    //количество смертей
    assists,    //количество поддержек
    enemyCreepsKilled,    //количество убийств вражеских солдат
    neutralCreepsKilled,    //количество убийств нейтральных монстров
    totalNumTowersKilled,    //количество разрушенных башен 
    totalNumTowersAssisted,    //количество отказанных башен 
    flagsRaised,    //количество поднятых флагов
    flagsDestroyed,    //количество уничтоженных флагов
    //количество выигранных уровней мини игры (проваленных, сделанных, серебряный мастер, золотой мастер)
    totalMedalsCountFailed,
    totalMedalsCountDone,
    totalMedalsCountSilver,
    totalMedalsCountGold,

    timeInDeath,    //количество времени (в секундах), проведенного в смерти
    damageDealedMagic,    //количество нанесенного урона (магия)
    damageDealedMaterial,     //количество нанесенного урона (физический)
    damageDealedPure,    //количество нанесенного урона (чистый)
    damageDealedTotal,    //общее количество нанесенного урона
    damageReceivedMagic,    //количество полученного урона
    damageReceivedMaterial,
    damageReceivedPure,
    damageReceivedTotal,    //общее количество полученного урона
    healedAmount,    //количество вылеченного за сессию своего Здоровья
    totalNumQuartersDestroyed,    //количество разрушенных арсеналов

    numBossKillsAssist, // убито боссов (см. также: numCatKillAssist, numDragonKillAssist)
    numKillsTotal, // всего убийств
    money, // сколько прайма заработано
    currentKillSpree,
    currentDeathSpree,
    saviourTime,
    timeInIdle,
    killedByNeutrals,

    usedPotions, // зелий использовано
    teleportsByAbility, // телепортов использовано
    glyphsPickuped,
    achievScore, // очков за аччивки
    damageReceivedFromHeroesMagic,
    damageReceivedFromHeroesMaterial,
    damageReceivedFromHeroesPure,
    damageReceivedFromHeroesTotal,
    damageDealedToHeroesMagic,
    damageDealedToHeroesMaterial,
    damageDealedToHeroesPure,
    damageDealedToHeroesTotal,
    grandScore,
    timeElapsed,

    numCatKillAssist, // - засчитывает только убийства\ассисты босса кота Баюна
    numDragonKillAssist, // - засчитывает только убийства\ассисты босса Горыныча
    // ReSharper restore InconsistentNaming
  }

  public enum DynamicQuestCheckType
  {
    SessionResult = 0,    // Учитываем внутрисессионную статистику
    SessionInfo = 1,      // Просто победа в режиме определённым или любым героем
    Instant = 2,          // Сдать ресурсы
    ModelData = 3,        // Квесты, связанные с состоянием замка
  }

  public enum ModelDataConditionType
  {
    CastleLogin = 0,
    HeroLevel = 1,
    HeroLevelUp = 2,
    HeroRating = 3,
    HeroRatingUp = 4,
    HeroForce = 5,
    HeroForceUp = 6,
    BuildingLevel = 7,
    CollectResources = 8,
    ForgeTalent = 9,
    MakeReforges = 10,
    CollectCWPointsGuildFight = 11
  }

  public enum SessionCheckType
  {
    WinOnly = 0,
    WinAndLoss = 1,
    Loss =2,
  }

  public enum DynamicQuestAwardType
  {
    PremiumAcc = 0,
    Gold = 1,
    Resource1 = 2,
    Resource2 = 3,
    Resource3 = 4,
    Silver = 5,
    Perl = 6,
    RedPerl = 7,
    Talent = 8,
    RandomTalent = 9,
    Construction = 10,
    Experience = 11,
    Lamp = 12,
    CustomFlag = 13,
    Hero = 14,
    Skin = 15,
    FractionChange = 16,
    NicknameChange = 17,
    HeroExperience = 18,
    HeroStatsReset = 19,
    AllHeroStatsReset = 20,
    Quest = 21,
    RandomHero = 22,
    RandomSkin = 23,
    RandomTalentFromPool = 24,
    AlreadyCompletedQuest = 25,
    UpgradeHeroTalentsEvent = 26,
    DontUseThis = 27,
    DontUseThis2 = 28,
    Shard = 29,
    CustomCurrency = 30,
    Lootbox = 31
  }

  public enum DynamicQuestPreConditionType
  {
     Usual = 0,    // обычное предусловие
     Tournament = 1,    // Турнирное предусловие
  }

    public enum DynamicQuestAwardConditionType
    {
        AfterWin = 0,
        AfterMiss = 1, //будет отвечать за выдачу данной награды, если игрок пропустил квест
    }
}