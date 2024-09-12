using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using libdb.DB;
using PF_GameLogic.DBTalent;
using PF_GameLogic.DBUnit;
using PF_GameLogic.DBAdvMap;
using PF_Types.SocialClient;
using SocialTypes.DBTypes;

namespace SocialTypes.Quests
{
  public class ChangeMapAction : QuestAction
  {
      [Description("Карта, которую проставить")]
      public DBPtr<AdvMapDescription> map;
      [Description("Тип режима (обучение, пвп, пве, эвент)")]
      public MapType type = MapType.Tutorial;
      [Description("Видна ли эта карта в отдельном слоте")]
      public bool isVisible = true;
  }

  public class ChangeGroupMapAction : QuestAction
  {
      [Description("Группа карт, которую проставить")]
      public DBPtr<DBAdvMapDescGroup> group;
      [Description("Тип режима (обучение, пвп, пве, эвент)")]
      public MapType type = MapType.Tutorial;
      [Description("Видна ли эта карта в отдельном слоте")]
      public bool isVisible = true;
  }

  public class OpenWindowAction : ClientQuestAction
  {
      public string windowName = string.Empty;
  }

  public class CloseAllWindowAction : ClientQuestAction
  {

  }

  public class OpenDarkenTutorialAction : ClientQuestAction
  {
      public string movieName = string.Empty;
      public string baseWindowName = string.Empty;
      public List<TextRef> advices;
      public bool declineDragFromTalentSet = false;
  }

  public class CloseDarkenTutorialAction : ClientQuestAction
  {
  }

  public enum PanelType
  {
    Construction,
    Friends,
    Heroes
  }

  public class OpenPanelAction : ClientQuestAction
  {
    public PanelType panelType = PanelType.Construction;
  }

  public enum MatchType
  {
    pvp = 0,
    pve,
    train,
    pvp1x1,
    pvp2x2,
    pvb,
    ctf
  }

  public class StartSessionAction : ClientQuestAction
  {
    [Description( "Карта, которую стартовать" )]
    public DBPtr<AdvMapDescription> map;
    [Description( "Герой, с которым идти в бой" )]
    public DBPtr<Hero> hero;
  }


  public class SelectMapTypeAction : ClientQuestAction
  {
    public MapType mapType = MapType.Tutorial;
    public bool playWithBots = false;
  }

  public class NextQuestAction : QuestAction
  {
    [Description( "Следующий квест" )]
    public DBPtr<Quest> quest;
  }

  public class RemoveQuestAction : QuestAction
  {
      [Description("Удаляемый (отменяемый) квест")]
      public DBPtr<Quest> quest;
  }

  public class GiveHeroExpAction : QuestAction
  {
    [Description( "Герой, которому выдают опыт" )]
    public DBPtr<Hero> hero;

    [Description( "Количество опыта для героя" )]
    public int exp;
  }

    public class GiveFreeSkipsAction : QuestAction
    {
        [Description("Количество бесплатных скипов")]
        public int skipsCount;
        [Description("PersistentID здания, для которого действуют скипы")]
        public string buildingName = string.Empty;
    }

    public enum EnergyChangeType
    {
        Increment = 0,
        Override,
        AsTopValue,
        AsBottomValue
    }

    public class ChangeHeroEnergyAction : QuestAction
    {
        [Description("Герой, которому изменяют энергию")]
        public DBPtr<Hero> hero;
        [Description("Энергии добавить/удалить при отрицательном значении")]
        public int energy = 0;
        [Description("Increment - добавить/вычесть указанное значение, Override - переопределить, AsTopValue - выставить порог сверху(уменьшить, если больше), AsBottomValue - сделать порог снизу (увеличить, если меньше)")]
        public EnergyChangeType changeType = EnergyChangeType.Increment;
    }

    public class GiveRewardAction : QuestAction
    {
        public ResourcesTable resources;
        public int fame = 0;
        [Description("Список героев, которые гарантированно выдадутся игроку в качестве награды")]
        public List<DBPtr<Hero>> heroes;
        [Description("Список героев, один из которых выберется случайным образом для выдачи в награду")]
        public List<DBPtr<Hero>> heroesForRandomPick;
        public List<DBPtr<Talent>> talents;
        [Description( "Для игроков-мальчиков (или по умолчанию): Если этот Action выдает таланты и у игрока есть герой, указанный в этом поле, то выдаваемые таланты будут привязаны к нему." )]
        public DBPtr<Hero> defaultTalentsSoulboundMale;
        [Description( "Для игроков-девочек: Если этот Action выдает таланты и у игрока есть герой, указанный в этом поле, то выдаваемые таланты будут привязаны к нему." )]
        public DBPtr<Hero> defaultTalentsSoulboundFemale;
        public List<RewardConstruction> constructions;
        public int daysForPremiumAcc = 0;
    }

    public class RewardConstruction
    {
        [Description("Уровень здания")]
        public int level;
        [Description("Здание в награду")]
        public DBPtr<Constructon> construction;
    }

    public class SelectHeroAction : ClientQuestAction
    {
      public DBPtr<Hero> hero;
    }

    public class CompleteObjectiveAction : ClientQuestAction
    {
    }

    public class OpenUrlAction : ClientQuestAction
    {
      [Description( "Полный адрес, по которому будет совершен переход в браузере" )]
      public TextRef url;
    }

    public class RemoveTalentsIsNewStateAction : QuestAction
    {

    }

    [Flags]
    public enum ECastleLibraryFilter
    {
      None = 0,
      Ordinary = 1 << 0,
      Good = 1 << 1,
      Excellent = 1 << 2,
      Magnificent = 1 << 3,
      Exclusive = 1 << 4,
      Outstanding = 1 << 5,
      All = Ordinary | Good | Excellent | Magnificent | Exclusive | Outstanding,
    }

    public class ResetTalentsLibraryFiltersAction : ClientQuestAction
    {
      [Description( "Все фильтры в библиотеке(по герою и т.д.) будут сброшены. Затем будут установлены фильтры по 'цветам' талантов согласно заданному значению." )]
      public ECastleLibraryFilter ActiveFilters = ECastleLibraryFilter.All;
    }

    public class ChangeConfirmationUnsoulboundModeAction : ClientQuestAction
    {
      [Description("True - запрашивать у пользователя подтверждение при отвязке таланты(как обычно). False - отвязывать талант без подтверждения.")] 
      public bool UnsoulboundConfirmationRequired = true;
    }

    public class MoveTalentFromHeroToLibraryAction : QuestAction
    {
      [Description( "У какого героя искать талант" )] 
      public DBPtr<Hero> hero;

      [Description("Номер слота, из которого нужно вынуть талант (1-36)")]
      public int slot;

      [Description( "Какой талант попытаться выложить, если не задан слот" )]
      public DBPtr<Talent> talent;
    }

    public enum TutorialState
    {
      NotStarted = 0,
      BattleQuestAdded = 1,
      SessionMMStarted = 2,
      SessionMMAccepted = 3,
      SessionStarted = 4,
      ClientReturnedFromSession = 5,
      RewardsReceived = 6,
      Completed = 7,
      Skipped = 9
    }

    public class ChangeTutorialStateAction : QuestAction
    {
      [Description("Состояние туториала")]
      public TutorialState state = TutorialState.NotStarted;
    }

    public class OpenDecreaseRatingDialogWindowAction : ClientQuestAction
    {
      public TextRef message;
    }

    public class GiveGoldenLampAction : QuestAction
    {
      [Description("Ссылка на тип руны")]
      public DBPtr<GoldLampEvent> lampEventInfo;
      [Description("Длительность")]
      public int duration = 0;
      [Description("Максимальный бонус золота")]
      public int bonus = 0;
      [Description("Кол-во отвязок")]
      public int unsoulbounds = 0;
    }

    public class SetLastRankedGameTimeAction : QuestAction
    {

    }

    public class GiveUpgradeHeroTalentsEventAction : QuestAction
    {
      [Description("Кол-во рун чемпиона которое надо выдать в награду")]
      public int count = 1;
    }
}
