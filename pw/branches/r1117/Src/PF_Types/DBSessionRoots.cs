//#include "DBVisualRoots.cs"
//#include "DBAbility.cs"
//#include "DbHeroesList.cs"
//#include "DbStatistic.cs"
//#include "DBGameLogic.cs"
//#include "DBImpulsiveBuffs.cs"
//#include "DBGuild.cs"

using libdb.DB;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBGameLogic;
using PF_GameLogic.DBHeroesList;
using PF_GameLogic.DBImpulsiveBuffs;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBVisualRoots;
using PF_GameLogic.DbMapList;
using PF_GameLogic.DBServer;
using PF_GameLogic.DBGuild;
using PF_GameLogic.DBSessionMessages;

namespace PF_GameLogic.DBSessionRoots
{
  [UseTypeName("ROOT")]
  [Custom( "DBServer" )]
  public class SessionLogicRoot : DBResource
  {
    public DBPtr<AILogicParameters> aiLogic;
    public DBPtr<ScoringTable> scoringTable;
    public DBPtr<UnitsLogicParameters> unitLogicParameters;
    public DBPtr<GlyphsDB> glyphsDB;
    public DBPtr<HeroesDB> heroes;
    public DBPtr<HeroesLevelUps> heroesLevelups;
    public DBPtr<ImpulsiveBuffsContainer> impulsiveBuffs;
    public DBPtr<DefaultFormulas> defaultFormulas;
    public DBPtr<MapList> mapList;
    public DBPtr<GuildBuffsCollection> guildBuffsCollection;
  }

  [DbRoot]
  [UseTypeName("ROOT")]
  [Custom( "DBServer" )]
  public class SessionRoot : DBResource
  {
    public DBPtr<SessionUIRoot> uiRoot;
    public DBPtr<SessionLogicRoot> logicRoot;
    public DBPtr<SessionVisualRoot> visualRoot;
    public DBPtr<SessionAudioRoot> audioRoot;
    public DBPtr<RollSettings> rollSettings;
    public DBPtr<SessionMessages> sessionMessages;
  }
}