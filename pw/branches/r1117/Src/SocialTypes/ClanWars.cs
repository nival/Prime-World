using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBStats;
using SocialTypes.DBTypes;
using PF_GameLogic.DBServer;
using Render.DBRenderResources;

namespace SocialTypes.ClanWars
{
    public class NPCVillage : NPCCastle
    {
        [Description("Ежедневный доход с этого клана")]
        public int everyDayProfit;
    }
    public class NPCSuzerain : NPCCastle
    {
        [Description("Ежедневный доход с этого клана")]
        public int defaultSiegePoints;
    }


    public class NPCCastle
    {
        [Description("Название клана")]
        public TextRef clanName = new TextRef();

        [Description("Название клана")]
        public TextRef clanShortName = new TextRef();

        [Description("Рейтинг клана")]

        public int clanRating;

    }

    public class GuildWarEventAwardItem
    {
      [Description("лутбокс")]
      public DBPtr<Lootbox> lootbox;
      [Description("количество лутбоксов")]
      public int count;
    }

    public class GuildWarEventAward
    {
      [Description( "максимальное место клана в топе (включительно)" )]
      public int maxPlace;
      [Description( "сколько самых активных игроков награждаем" )]
      public int members;
      [Description( "награда" )]
      public GuildWarEventAwardItem award;
    }

    public class GuildWarEventData
    {
        [Description("Размер пула")]
        public long pointsCap = 1000000;

        [Description("Длительность ивента (в днях)")]
        public int duration = 7;

        [Description("Награды выдаваемы по завершению евента. Задавать в порядке возрастания по месту.")]
        public List<GuildWarEventAward> awards;
    }

    public class ClanWarsData 
    {
        [Description("NPC деревня")]
        public NPCVillage npcVillage;
        
        [Description("NPC сюзерена")]
        public NPCSuzerain npcSuzerain;

        [Description("Количество деревень")]
        public int countOfNPCVillage;

        [Description("Процент очков, который получает сюзерен со своих вассалов")]
        public float guildVassalsTributeCoef = 0.15f;

        [Description("Рейтинг, открывающий доступ в магазин древних")]
        public int shopAncientRating;

        [Description("Когда клан А нападает на клан Б, второй получает в копилку на защиту сразу +X% очков")]
        public float defencePointsPercent = 0.05f;

        [Description("Кол-во лучших по клановому рейтингу игроков влияющих на рейтинг клана")]
        public int numPlayersFromTopInClanRating = 20;

        [Description("Настройки кланового ивента")]
        public GuildWarEventData guildWarEventData;
    }

  public class GuildRecruitment
  {
    [Description("Максимальнеое кол-во заявок от одного пользователя")]
    public int maxUserGuildRequests;

    [Description("Размер текста для прошения в гильдию")]
    public int maxUserGuildRequestSize;

    [Description("Размер сообщения гильдии, которое отображается игрокам при поиске гильдии")]
    public int maxGuildRecruitTextSize;

    [Description("Время жизни заявки (в секундах)")]
    public int guildRequestLifetime;

    [Description("Языки клиентов, они же языки гильдий")]
    public List<string> locales;
  }
}
