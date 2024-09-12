#pragma once

namespace StatisticService
{

//
//
// !!! AHTUNG AHTUNG !!! 
// —труктура десериализируетс€ в ToolsServer (C Sharp)
// Ћюбые изменени€ полей согласовать с разработчиками ToolServer:
//
//

// —труктура в которой передаЄм разного рода очки полученные в сессии и счЄтчики. «десь может быть например прогресс квестов.
// ≈сли вдруг доп.счЄтчиков станет больше 1, то имеет смысл заводить контейнер с соответстви€ми string-int или enum-int

struct SessionPlayerScoring
{
  ZDATA
    //количество набранных очков GetScore()
    int score; // ќбычные generic сессионные очки
    //специальные очки дл€ испытаний GetSpecialPoints()
    int specialPoints; // »спользуетс€ дл€ режима "»спытани€"
    //уровень геро€ к концу сессии по нафте GetNaftaLevel()
    int finalLevel;
    //количество убийств вражеских героев GetTotalNumHeroKills
    int kills;
    //количество смертей GetNumDeaths()
    int deaths;
    //количество поддержек GetTotalNumHeroAssists()
    int assists;
    //количество убийств вражеских солдат GetCreepsKilled()
    int enemyCreepsKilled;
    //количество убийств нейтральных монстров GetNeutralCreepsKilled()
    int neutralCreepsKilled;
    //количество разрушенных башен GetTotalNumTowersKilled
    int totalNumTowersKilled;
    //количество отказанных башен GetTotalNumTowersAssisted
    int totalNumTowersAssisted;
    //количество подн€тых флагов GetFlagsRaised
    int flagsRaised;
    //количество уничтоженных флагов GetFlagsDestroyed
    int flagsDestroyed;
    //?количество выигранных уровней мини игры GetTotalMedalsCount (Failed = 1, Done, Silver, Gold)
    int totalMedalsCountFailed;
    int totalMedalsCountDone;
    int totalMedalsCountSilver;
    int totalMedalsCountGold;
    //количество времени (в секундах), проведенного в смерти GetTimeInDeath
    float timeInDeath;
    //количество нанесенного урона
    float damageDealedMagic;
    float damageDealedMaterial;
    float damageDealedPure;
    //общее количество нанесенного урона
    float damageDealedTotal;
    //количество полученного урона
    float damageReceivedMagic;
    float damageReceivedMaterial;
    float damageReceivedPure;
    //общее количество полученного урона
    float damageReceivedTotal;
    //?количество раз, когда был оказана помощь геро€м противоположного пола с помощью Gender-талантов GetSexHelp
    int sexHelp;
    //количество вылеченного за сессию своего «доровь€ GetHealedAmount
    float healedAmount;
    //количество разрушенных арсеналов GetTotalNumQuartersDestroyed
    int totalNumQuartersDestroyed;

    //additional fields
    // GetNumBossKillsAssist();
    int numBossKillsAssist;
	// GetNumCatKillAssist();
    int numCatKillAssist;
	// GetNumDragonKillAssist();
    int numDragonKillAssist;
    // GetNumKillsTotal();
    int numKillsTotal;
    // GetMoney();
    float money;
    // GetCurrentKillSpree();
    int currentKillSpree;
    // GetCurrentDeathSpree();
    int currentDeathSpree;
    // GetSaviourTime();
    float saviourTime;
    // GetTimeInIdle();
    float timeInIdle;
    // GetKilledByNeutrals();
    int killedByNeutrals;
    // GetUsedPotions();
    int usedPotions;
    // GetTimeAtHome();
    float timeAtHome;
    // GetTeleportsByAbility();
    int teleportsByAbility;
    // GetGlyphsPickuped();
    int glyphsPickuped;
    // GetAchievScore();
    int achievScore;
    // GetDamageReceivedFromHeroes(Magic/Material/Pure);
    float damageReceivedFromHeroesMagic;
    float damageReceivedFromHeroesMaterial;
    float damageReceivedFromHeroesPure;
    float damageReceivedFromHeroesTotal;
    // GetDamageDealedToHeroes(Magic/Material/Pure);
    float damageDealedToHeroesMagic;
    float damageDealedToHeroesMaterial;
    float damageDealedToHeroesPure;
    float damageDealedToHeroesTotal;
    // GetGrandScore();
    int grandScore;

    int timeElapsed;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&score); f.Add(3,&specialPoints); f.Add(4,&finalLevel); f.Add(5,&kills); f.Add(6,&deaths); f.Add(7,&assists); f.Add(8,&enemyCreepsKilled); f.Add(9,&neutralCreepsKilled); f.Add(10,&totalNumTowersKilled); f.Add(11,&totalNumTowersAssisted); f.Add(12,&flagsRaised); f.Add(13,&flagsDestroyed); f.Add(14,&totalMedalsCountFailed); f.Add(15,&totalMedalsCountDone); f.Add(16,&totalMedalsCountSilver); f.Add(17,&totalMedalsCountGold); f.Add(18,&timeInDeath); f.Add(19,&damageDealedMagic); f.Add(20,&damageDealedMaterial); f.Add(21,&damageDealedPure); f.Add(22,&damageDealedTotal); f.Add(23,&damageReceivedMagic); f.Add(24,&damageReceivedMaterial); f.Add(25,&damageReceivedPure); f.Add(26,&damageReceivedTotal); f.Add(27,&sexHelp); f.Add(28,&healedAmount); f.Add(29,&totalNumQuartersDestroyed); f.Add(30,&numBossKillsAssist); f.Add(31,&numCatKillAssist); f.Add(32,&numDragonKillAssist); f.Add(33,&numKillsTotal); f.Add(34,&money); f.Add(35,&currentKillSpree); f.Add(36,&currentDeathSpree); f.Add(37,&saviourTime); f.Add(38,&timeInIdle); f.Add(39,&killedByNeutrals); f.Add(40,&usedPotions); f.Add(41,&timeAtHome); f.Add(42,&teleportsByAbility); f.Add(43,&glyphsPickuped); f.Add(44,&achievScore); f.Add(45,&damageReceivedFromHeroesMagic); f.Add(46,&damageReceivedFromHeroesMaterial); f.Add(47,&damageReceivedFromHeroesPure); f.Add(48,&damageReceivedFromHeroesTotal); f.Add(49,&damageDealedToHeroesMagic); f.Add(50,&damageDealedToHeroesMaterial); f.Add(51,&damageDealedToHeroesPure); f.Add(52,&damageDealedToHeroesTotal); f.Add(53,&grandScore); f.Add(54,&timeElapsed); return 0; }

  SessionPlayerScoring() : score( 0 ), specialPoints( 0 ), finalLevel( 0 ), kills( 0 ), deaths( 0 ), assists( 0 ), enemyCreepsKilled( 0 ), neutralCreepsKilled( 0 ), totalNumTowersKilled( 0 ), totalNumTowersAssisted( 0 ), flagsRaised( 0 ), flagsDestroyed( 0 ), totalMedalsCountFailed( 0 ), totalMedalsCountDone( 0 ), totalMedalsCountSilver( 0 ), totalMedalsCountGold( 0 ), timeInDeath( 0.0f ), damageDealedMagic( 0.0f ), damageDealedMaterial( 0.0f ), damageDealedPure( 0.0f ), damageDealedTotal( 0.0f ), damageReceivedMagic( 0.0f ), damageReceivedMaterial( 0.0f ), damageReceivedPure( 0.0f ), damageReceivedTotal( 0.0f ), sexHelp( 0 ), healedAmount( 0.0f ), totalNumQuartersDestroyed( 0 ), numBossKillsAssist( 0 ), numCatKillAssist( 0 ), numDragonKillAssist( 0 ), numKillsTotal( 0 ), money( 0.0f ), currentKillSpree( 0 ), currentDeathSpree( 0 ), saviourTime( 0.0f ), timeInIdle( 0.0f ), killedByNeutrals( 0 ), usedPotions( 0 ), timeAtHome( 0.0f ), teleportsByAbility( 0 ), glyphsPickuped( 0 ), achievScore( 0 ), damageReceivedFromHeroesMagic( 0.0f ), damageReceivedFromHeroesMaterial( 0.0f ), damageReceivedFromHeroesPure( 0.0f ), damageReceivedFromHeroesTotal( 0.0f ), damageDealedToHeroesMagic( 0.0f ), damageDealedToHeroesMaterial( 0.0f ), damageDealedToHeroesPure( 0.0f ), damageDealedToHeroesTotal( 0.0f ), grandScore( 0 ), timeElapsed( 0 ) {}

  bool operator == ( const SessionPlayerScoring & other ) const
  {
    return
        ( score == other.score ) &&
        ( specialPoints == other.specialPoints ) &&
        ( finalLevel == other.finalLevel ) &&
        ( kills == other.kills ) &&
        ( deaths == other.deaths ) &&
        ( assists == other.assists ) &&
        ( enemyCreepsKilled == other.enemyCreepsKilled ) &&
        ( neutralCreepsKilled == other.neutralCreepsKilled ) &&
        ( totalNumTowersKilled == other.totalNumTowersKilled ) &&
        ( totalNumTowersAssisted == other.totalNumTowersAssisted ) &&
        ( flagsRaised == other.flagsRaised ) &&
        ( flagsDestroyed == other.flagsDestroyed ) &&
        ( totalMedalsCountFailed == other.totalMedalsCountFailed ) &&
        ( totalMedalsCountDone == other.totalMedalsCountDone ) &&
        ( totalMedalsCountSilver == other.totalMedalsCountSilver ) &&
        ( totalMedalsCountGold == other.totalMedalsCountGold ) &&
        ( timeInDeath == other.timeInDeath ) &&
        ( damageDealedMagic == other.damageDealedMagic ) &&
        ( damageDealedMaterial == other.damageDealedMaterial ) &&
        ( damageDealedPure == other.damageDealedPure ) &&
        ( damageDealedTotal == other.damageDealedTotal ) &&
        ( damageReceivedMagic == other.damageReceivedMagic ) &&
        ( damageReceivedMaterial == other.damageReceivedMaterial ) &&
        ( damageReceivedPure == other.damageReceivedPure ) &&
        ( damageReceivedTotal == other.damageReceivedTotal ) &&
        ( sexHelp == other.sexHelp ) &&
        ( healedAmount == other.healedAmount ) &&
        ( totalNumQuartersDestroyed == other.totalNumQuartersDestroyed ) &&
        ( numBossKillsAssist == other.numBossKillsAssist ) &&
		( numCatKillAssist == other.numCatKillAssist ) &&
		( numDragonKillAssist == other.numDragonKillAssist ) &&
        ( numKillsTotal == other.numKillsTotal ) &&
        ( money == other.money ) &&
        ( currentKillSpree == other.currentKillSpree ) &&
        ( currentDeathSpree == other.currentDeathSpree ) &&
        ( saviourTime == other.saviourTime ) &&
        ( timeInIdle == other.timeInIdle ) &&
        ( killedByNeutrals == other.killedByNeutrals ) &&
        ( usedPotions == other.usedPotions ) &&
        ( timeAtHome == other.timeAtHome ) &&
        ( teleportsByAbility == other.teleportsByAbility ) &&
        ( glyphsPickuped == other.glyphsPickuped ) &&
        ( achievScore == other.achievScore ) &&
        ( damageReceivedFromHeroesMagic == other.damageReceivedFromHeroesMagic ) &&
        ( damageReceivedFromHeroesMaterial == other.damageReceivedFromHeroesMaterial ) &&
        ( damageReceivedFromHeroesPure == other.damageReceivedFromHeroesPure ) &&
        ( damageReceivedFromHeroesTotal == other.damageReceivedFromHeroesTotal ) &&
        ( damageDealedToHeroesMagic == other.damageDealedToHeroesMagic ) &&
        ( damageDealedToHeroesMaterial == other.damageDealedToHeroesMaterial ) &&
        ( damageDealedToHeroesPure == other.damageDealedToHeroesPure ) &&
        ( damageDealedToHeroesTotal == other.damageDealedToHeroesTotal ) &&
        ( grandScore == other.grandScore ) &&
        ( timeElapsed == other.timeElapsed );
  }
};

}