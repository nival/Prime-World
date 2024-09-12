/*
#about Завести героя и классовые таланты для героя с указанным именем и прописать ему дефалтовые значения
#ref PF_Types.DBTypes.dll
#ref PF_EditorC.exe
*/

using System.Collections;
using System.Collections.Generic;
using DBTypes;
using libdb.DB;
using libdb.IO;
using libdb.Diagnostics;
using EditorLib;
using System.Text;
using System.Globalization;
using System.Runtime.InteropServices;

public class GenerateNewHero
{
  [DllImport("FormulaBuilder.dll", CallingConvention = CallingConvention.StdCall)]
  public static extern int BuildFormula(string cpFormula, [MarshalAs(UnmanagedType.LPStr)] StringBuilder buf, int nMaxCount, string cpReturnType);

  private void PutTalentIntoSet(DBPtr<Talent> talent, TalentsSet talentsSet, int level, int slot, bool isTakenOnStart)
  {
    List<TalentsLevel> levels = new List<TalentsLevel>(talentsSet.levels);
    List<TalentSlot>   slots  = new List<TalentSlot>(levels[level].talents);

    slots[slot].talent = talent;
  }

  private void PutTalentIntoSet(DBPtr<Talent> talent, TalentsSet talentsSet, int level, int slot)
  {
    PutTalentIntoSet(talent, talentsSet, level, slot, false);
  }

  public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
  {
    //////////////////////////////////////////////////////////////////////////
    // Parameters ////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    bool isParamsCorrect = (parameters.Length == 3) || (parameters.Length == 4);
    isParamsCorrect &= (parameters[1] == "m") || (parameters[1] == "f");
    isParamsCorrect &= (parameters[2] == "m") || (parameters[2] == "r");

    string defaultTalents = "A0A1A1uA2A2uA3A3uA4A4u";

    if (!isParamsCorrect)
    {
      Log.TraceError("Usage: PF_EditorC.exe run ../Tools/Scripts/GenerateNewHero.cs <HeroName> <Gender> <Attack> [<Talents>]");
      Log.TraceError("--HeroName: Hero Name (C.O.)");
      Log.TraceError("--Gender: m|f (male/female)");
      Log.TraceError("--Attack: m|r (melee/ranged)");
      Log.TraceError("--Talents: String with Talents IDs. Example (and default): " + defaultTalents);
      yield return true;
    }

    string heroName = parameters[0];

    bool isMale  = parameters[1] == "m";
    bool isMelee = parameters[2] == "m";
    string templateHeroName = isMale ? (isMelee ? "Ratcatcher" : "Mage") : (isMelee ? "Unicorn" : "Healer");

    Hero templateHero = DataBase.Get<Hero>(DBID.FromFileName(string.Format("/Heroes/{0}/_.HROB", templateHeroName), false)).Get();

    string talents = (parameters.Length == 4) ? parameters[3] : defaultTalents;
    if (!talents.StartsWith("A"))
    {
      Log.TraceError("Every Talent ID should start with 'A'!");
      yield return true;
    }
    List<string> talentNames = new List<string>(talents.Replace("A", " A").Substring(1).Split(' '));
    if (talentNames.Count != 9)
    {
      Log.TraceError("There should be 9 Talent ID's!");
      yield return true;
    }

    DataBase.UndoRedoManager.Start("Create new hero");

    //////////////////////////////////////////////////////////////////////////
    // New Hero from template ////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    string oldHeroNameA = templateHero.heroNameA.ToString();
    string oldHeroNameB = templateHero.heroNameB.ToString();
    string oldHeroDescriptionA = templateHero.lobbyData.heroDescriptionA.ToString();
    string oldHeroDescriptionB = templateHero.lobbyData.heroDescriptionB.ToString();

    Hero hero = new Hero();
    DBID newDbid = DBID.GenerateUnique(string.Format("/Heroes/{0}/", heroName), "_", hero.GetType());
    DataBase.Copy(newDbid, DBID.FromDBID(templateHero.DBId, false));

    DBPtr<Hero> dbHero = DataBase.Get<Hero>(DBID.FromDBID(newDbid, false));
    hero = dbHero.Get();

    hero.askLists[0] = null;
    hero.askLists[1] = null;

    hero.heroNameA = new TextRef();
    hero.heroNameB = new TextRef();
    hero.lobbyData.heroDescriptionA = new TextRef();
    hero.lobbyData.heroDescriptionB = new TextRef();
    hero.heroNameA.FromString(heroName);
    hero.heroNameB.FromString(heroName);
    hero.gender = isMale ? EGender.Male : EGender.Female; ;

    hero.persistentId = heroName.ToLower();

    hero.attackAbility.Get().constants = null;

    templateHero.heroNameA = new TextRef();
    templateHero.heroNameB = new TextRef();
    templateHero.lobbyData.heroDescriptionA = new TextRef();
    templateHero.lobbyData.heroDescriptionB = new TextRef();
    templateHero.heroNameA.FromString(oldHeroNameA);
    templateHero.heroNameB.FromString(oldHeroNameB);
    templateHero.lobbyData.heroDescriptionA.FromString(oldHeroDescriptionA);
    templateHero.lobbyData.heroDescriptionB.FromString(oldHeroDescriptionB);

    //////////////////////////////////////////////////////////////////////////
    // Hero in DB ////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    HeroParams heroParams = new HeroParams();

    heroParams.id = heroName.ToLower();
    heroParams.hero = dbHero;
    heroParams.legal = false;
    heroParams.matchmakingSex = hero.gender;

    HeroesDB heroesDB = DataBase.Get<HeroesDB>(DBID.FromFileName(string.Format("/Heroes/_.HRDB"), false));
    heroesDB.heroes.Add(heroParams);

    //////////////////////////////////////////////////////////////////////////
    // Talents ///////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    Log.TraceMessage("Start");

    string defaultTTText = "$(TThead)\n$(TTbottom)";

    DBID defaultImageDBID = DBID.FromFileName("/UI/Styles/Icons/Artifacts/testitem.ITEX.xdb", false);
    DBPtr<Texture> defaultImage = DataBase.Get<Texture>(defaultImageDBID);

    TalentsSet talentsSet = DataBase.Get<TalentsSet>(DBID.FromFileName(string.Format("/Items/Talents/defaultSet.TALENTSET"), false)).Get();
    DBPtr<TalentsSet> dbTalentsSet = DataBase.Create(DBID.FromFileName(string.Format("/Items/Talents/{0}.TALENTSET", heroName), false), talentsSet);
    talentsSet = dbTalentsSet.Get();
    
    // Generate talents and put it into talentsSet
    int askId = 0;
    int curLevel = 1;
    int curSlot = 4;

    DBPtr<Talent> dbGenderTalent = isMale ? DataBase.Get<Talent>( DBID.FromFileName( "/Items/Talents/Gender/_M_1_Rejuvenation.TALENT", false ) )
      : DataBase.Get<Talent>( DBID.FromFileName( "/Items/Talents/Gender/_F_1_Bubble.TALENT", false ) );

    PutTalentIntoSet( dbGenderTalent, talentsSet, 0, 4 );

    foreach (string talentName in talentNames)
    {
      string name = string.Format("{0}_{1}", heroName, talentName);

      Talent talent = new Talent();
      talent.persistentId = name;
      talent.caption = name;
      talent.name.FromString(name);
      talent.description = new TextRef(talent);
      talent.description.FromString(defaultTTText);
      talent.image = defaultImage;

      DBPtr<Talent> dbTalent = DataBase.Create(DBID.FromFileName(string.Format("/Items/Talents/Class/{0}/Ability_{1}.TALENT", heroName, talentName), false), talent);

      switch (talentName)
      {
        case "A0":
          PutTalentIntoSet(dbTalent, talentsSet, 0, 5, true);
          break;
        case "A1":
          PutTalentIntoSet(dbTalent, talentsSet, 0, 0);
          break;
        case "A2":
          PutTalentIntoSet(dbTalent, talentsSet, 0, 1);
          break;
        case "A3":
          PutTalentIntoSet(dbTalent, talentsSet, 0, 2);
          break;
        case "A4":
          PutTalentIntoSet(dbTalent, talentsSet, 0, 3);
          break;
        case "A1u":
          PutTalentIntoSet(dbTalent, talentsSet, 1, 0);
          break;
        case "A2u":
          PutTalentIntoSet(dbTalent, talentsSet, 1, 1);
          break;
        case "A3u":
          PutTalentIntoSet(dbTalent, talentsSet, 1, 2);
          break;
        case "A4u":
          PutTalentIntoSet(dbTalent, talentsSet, 1, 3);
          break;
        default:
          PutTalentIntoSet(dbTalent, talentsSet, curLevel, curSlot);
          curSlot++;
          if ( curSlot > 5 )
          {
            curSlot = 0;
            curLevel++;
          }
          break;
      }
      
      if ((talentName != "A0") && !talentName.Contains("u"))
      {
        askId++;
        talent.askId = askId;
      }
    }

    foreach (string talentName in talentNames)
    {
      if (talentName.Contains("u"))
      {
        Talent talent = DataBase.Get<Talent>(DBID.FromFileName(string.Format("/Items/Talents/Class/{0}/Ability_{1}.TALENT", heroName, talentName), false));

        string prerequisiteName = talentName.Substring(0, talentName.IndexOf("u"));

        if (talentNames.Contains(prerequisiteName))
        {
          DBPtr<Talent> dbPrerequisite = DataBase.Get<Talent>(DBID.FromFileName(string.Format("/Items/Talents/Class/{0}/Ability_{1}.TALENT", heroName, prerequisiteName), false));
          talent.prerequisiteTalents.Add(dbPrerequisite);
        }
        else
        {
          Log.TraceError("Talents string {0} contains upgrade {1}, but don't contains talent {2}!", talents, talentName, prerequisiteName);
          yield return true;
        }
      }
    }

    hero.defaultTalentsSets = new List<DBPtr<TalentsSet>>() { dbTalentsSet };

    //////////////////////////////////////////////////////////////////////////
    // Stats /////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    List<EStat> statIdTable = new List<EStat>(12);
    statIdTable.Add(EStat.Life);
    statIdTable.Add(EStat.Energy);
    statIdTable.Add(EStat.Strength);
    statIdTable.Add(EStat.Intellect);
    statIdTable.Add(EStat.Dexterity);
    statIdTable.Add(EStat.AttackSpeed);
    statIdTable.Add(EStat.Stamina);
    statIdTable.Add(EStat.Will);
    statIdTable.Add(EStat.LifeRegenerationAbsolute);
    statIdTable.Add(EStat.EnergyRegenerationAbsolute);
    statIdTable.Add(EStat.MoveSpeed);
    statIdTable.Add(EStat.Range);

    // Stat values
    List<float> statValueTable = new List<float>(12);
    statValueTable.Add(600);
    statValueTable.Add(600);
    statValueTable.Add(50);
    statValueTable.Add(50);
    statValueTable.Add(50);
    statValueTable.Add(50);
    statValueTable.Add(50);
    statValueTable.Add(50);
    statValueTable.Add(0);
    statValueTable.Add(0);
    statValueTable.Add(50);
    statValueTable.Add(4);

    // Stat increments
    List<float> statIncTable = new List<float>(12);
    statIncTable.Add(25);
    statIncTable.Add(25);
    statIncTable.Add(1);
    statIncTable.Add(1);
    statIncTable.Add(1);
    statIncTable.Add(1);
    statIncTable.Add(1);
    statIncTable.Add(1);
    statIncTable.Add(0);
    statIncTable.Add(0);
    statIncTable.Add(0);
    statIncTable.Add(0);

    DBPtr<StatsContainer> dbStatsContainer = DataBase.Create<StatsContainer>(DBID.FromDBID(hero.DBId, true), new StatsContainer());
    hero.stats = dbStatsContainer;

    // Generate and fill hero stats
    StatsContainer statsContainer = dbStatsContainer.Get();
    for (int i = 0; i < 12; i++)
    {
      UnitStat stat = new UnitStat(statsContainer);
      statsContainer.stats.Add(stat);

      stat.statId = statIdTable[i];
      stat.value = new ExecutableFloatString(statsContainer);
      stat.value.sString = statValueTable[i].ToString("F0", CultureInfo.InvariantCulture);

      int nSize = 4096 * 2;
      StringBuilder sb = new StringBuilder(nSize);

      while (0 == BuildFormula(stat.value.sString, sb, sb.Capacity, stat.value.returnType))
      {
        nSize *= 2;
        sb = new StringBuilder(nSize);
      }
      stat.value.compiledString = sb.ToString();

      stat.increment = new ExecutableFloatString(statsContainer);
      stat.increment.sString = statIncTable[i].ToString("F0", CultureInfo.InvariantCulture);

      nSize = 4096 * 2;
      sb = new StringBuilder(nSize);

      while (0 == BuildFormula(stat.increment.sString, sb, sb.Capacity, stat.increment.returnType))
      {
        nSize *= 2;
        sb = new StringBuilder(nSize);
      }
      stat.increment.compiledString = sb.ToString();
    }

    DataBase.UndoRedoManager.Commit();
    DataBase.Store();

    Log.TraceMessage("Done");

    yield return true;
  }
}