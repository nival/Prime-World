
using System.Collections.Generic;
using PF_Types.SocialClient;
using PF_GameLogic.DBTalent;
using SocialTypes.Quests;
using libdb.DB;
using System.ComponentModel;
using Foundation.DBSystem;

namespace SocialTypes.DBTypes
{
  public class FameLevelRes
  {
    [Description( "Уровень для которого указаны параметры" )]
    public int currentLevel;
    [Description( "Количество ресурсов, выдаваемых игроку за новый уровень лорда" )]
    public ResourcesTable resourcesPerLevel;
    [Description("Количество часов премимум аккаунта, выдаваемых за новый уровень лорда")]
    public int PremiumAccountHours = 0;
  }

  public class LevelToResources
  {
   [Description("Таблица ресурсов, выдаваемых игроку за новый уровень лорда")]
    public List<FameLevelRes> resourcesPerLevel;
  }

   public class HonorLevelTable
  {
    [Description("Уровни чести")]
    public List<HonorLevel> rewardPerLevel;   
  }

   public class HonorLevel
   {
       [Description("Кол-во очков чести для перехода на следующий уровень")]
       public float points;
       [Description("Табличка процентов на ролл талантов в награду")]
       public DBPtr<DBRollTalentPercents> rollTalentsReward;
   }

  public class DBLevelToFame : DBResource
  {
    public List<int> Levels;
  }

  public class DBRollTalentPercents : DBResource
  {
    [EnumArray(typeof(ETalentRarity))]
    public List<int> percents;
  }

  public class DBStatpointsToLevel : DBResource
  {
    public List<int> StatPoints;
  }

  public class MDInitParams : DBResource
  {
    [Description( "Начальные ресурсы" )]
    public ResourcesTable resourceTable;
    [Description( "Начальный fame" )]
    public int fame;
  }

  public class ResourceAndInventoryLimits : DBResource
  {
    [Description( "Начальные лимиты" )]
    public ResourcesTable resourceLimits;
    [Description( "Начальные лимит библиотеки" )]
    public int inventoryLimits;
  }

  public enum PlayerGender
  {
    Unknown = 0,
    Male = 1,
    Female = 2,
    Other = 3,
  }

  public enum PlayerFraction
  {
    A = 0,
    B = 1,
    N = 2,
    //TODO <zulman> : after generation bug with NotSetted. Dont remove.
    NotSetted = 3,
  }

  public class RatingLossToInactivityDays
  {
    [Description("Рейтинг, который потеряет герой, если он не участвовал в боях ratingToLoose дней")]
    public int ratingToLoose;
    [Description("Кол-во дней с последней битвы, после которых игрок потеряет ratingToLoose рейтинга")]
    public int minDaysFromLastBattle;
  }

  public class RatingDecreaseByTime : DBResource
  {
    [Description("Рейтинга с которого начинаем что-то терять при неактивности")]
    public int minRatingToLoose;
    [Description("Квест, который выдаётся за потерю рейтинга")]
    public DBPtr<Quest> ratingUpdateQuest;
    [Description("Список соответствий потеря рейтинга-дни без боёв")]
    public List<RatingLossToInactivityDays> ratings;
  }
}
