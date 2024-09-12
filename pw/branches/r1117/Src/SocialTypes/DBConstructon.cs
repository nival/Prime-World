//#include "..\Types\Render.cs"
//#include "..\Types\RenderResources.cs"
//#include "..\PF_Types\SocialClient\DBSocialResources.cs"
//#include "..\PF_Types\DBConsumable.cs"

using System;
using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBStats;
using PF_GameLogic.DBConsumable;
using PF_Types.SocialClient;
using Foundation.DBSystem;
using PF_GameLogic.DBTalent;

namespace SocialTypes.DBTypes
{
  public enum ConstructionTab
  {
    Services,
    Pocket,
    Production,
    Houseroom,
    Decor,
    ForHeroes
  }

  public enum SpecialBathCycles
  {
    ToNextSessionInBorderlands,
    ToNextSessionInPvp,
    ToMaxLevel,
    ToMaxLevelForGold
  }

  [Flags]
  public enum DiscountType
  {
      None = 0,
      Gold = 1,
      Time = 2,
      Price = 4,
  }

	public enum TavernResourceType
	{
		None,
		Resource1,
		Resource2,
		Resource3,
    Perl,
    Silver,
		Gold,
    Shard,
	}

  public enum ConstructionProductionType
  {
    None,
    Resource1,
    Resource2,
    Resource3,
    Silver,
    Perl,
    Talents,
    Duck,
    RedPerl,
    Gold,
    Experience,
    Population,
    Shard,
  }

  public class GoldTable
  {
    [Description( "Процент вермени, с которого начинается данная цена" )]
    public int timePercent;
    [Description( "Процент от базовой цены, чтобы докупить цикл если он уже отработал [timePercent] процентов времени" )]
    public int goldPercent;
  }

  public class GoldPriceCycleTable : DBResource
  {
    public List<GoldTable> goldtable;
  }

  public class TimeBlock : DBResource
  {
    [Description( "Время цикла в секундах" )]
    public int time;
    [Description( "Базовая цена покупки цикла ( = цена за покупку полного цикла )" )]
    public int gold;
  }

  public class ConstructionLevel
  {
    [Description( "Цена за постройку/апгрейд" )]
    public ResourcesTable price;
    [Description( "Сколько Fame дается за постройку/апгрейд" )]
    public int fame;
  }

  public class BuildedConstruction
  {
    [Description( "ID строения" )]
    public string persistentId;
    public BuildedConstructionPosition position;
  }

  public class BuildedConstructionPosition
  {
    [Description( "Позиция x" )]
    public int x;
    [Description( "Позиция y" )]
    public int y;
    [Description( "Кратный 90 градусам угол(от 0 до 270) поворота здания" )]
    public int pitch;
  }

  public class ConstructionTabDesc
  {
    public TextRef Name = new TextRef();
    public string IconPath;
    public TextRef Tooltip = new TextRef();
    public int Order;
  }

  public class SectionsSet : DBResource
  {
    public List<IntVec2> Sections;
  }

  public class LimitsOfBuilding : DBResource
  {
    [Description( "Максимальное количество зданий этого типа на территории замка." )]
    public int MaxNumberOfBuilding;

    [Description("Текст лимитной группы, например: <br><center>Построено зданий в Замке: {0} из {1}")]
    public TextRef LimitText = new TextRef();

    [Description("Учитывать здания в кармане")]
    public bool CountPocket = false;
  }

  public class Constructon : DBResource
  {
    [Description( "ID строения" )]
    public string persistentId = null;
    public bool Destroyable = false;
    public bool Movable = false;

    [Description( "Путь до иконки относительно UnityClient/Assets/Resources. Как правило начинается с UI/Textures/Constructions/A/" )]
    public string IconPathA;
    [Description( "Путь до иконки относительно UnityClient/Assets/Resources. Как правило начинается с UI/Textures/Constructions/B/" )]
    public string IconPathB;


    [Description( "Отступ от 0-й клетки до центра 3D модели. В случае '0 0 0' модель будет выровнена по центру." )]
    public Vec3 OffsetA;

    [Description( "Отступ от 0-й клетки до центра 3D модели. В случае '0 0 0' модель будет выровнена по центру." )]
    public Vec3 OffsetB;

    [Description( "Меняет ли здание внешний вид при повылении грейда. Вне зависимости от значения доступно только при наличии 3D ассетов." )]
    public bool SupportVisualGradesChanging = false;
    
    [Description("Список уровней на которых здание меняет визуальное отображение(3D модель). Если уровни не заданы, модели будут равномерно распределены по уровням здания. Первую модель(1-й уровень) можно не задавать.")]
    public List<int> VisualChangingLevels;

    [Description( "Путь до папки с моделями грейдов или до модели здания относительно UnityClient/Assets/Resources для фракции Доктов. Как правило, начинается с Prefabs/Constructions/A/" )]
    public string ModelsPathA;

    [Description( "Путь до папки с моделями грейдов или до модели здания относительно UnityClient/Assets/Resources для фракции Адорнийцев. Как правило, начинается с Prefabs/Constructions/B/" )]
    public string ModelsPathB;

    [Description( "Путь до объекта, который создается после строительства домика(например эффект) относительно UnityClient/Assets/Resources для фракции Доктов. Как правило, начинается с Prefabs/" )]
    public string PostBuildingObjectPathA;

    [Description( "Путь до объекта, который создается после строительства домика(например эффект) относительно UnityClient/Assets/Resources для фракции Адорнийцев. Как правило, начинается с Prefabs/" )]
    public string PostBuildingObjectPathB;

    public TextRef CaptionA = new TextRef();
    public TextRef CaptionB = new TextRef();

    public TextRef Description = new TextRef();
    public TextRef Tooltip = new TextRef();
    public TextRef UpgradeTooltip = new TextRef();

    public int SectionsSize = SocialConstants.DEFAULT_SECTIONS_SIZE;

    public DBPtr<SectionsSet> SectionsLockedForBuilding;
    public DBPtr<SectionsSet> SectionsLockedForDecorations;

    [Description( "Уровни апгрейда" )]
    public List<ConstructionLevel> Levels;
    [Description( "Сколько процентов от цены здания дается при продаже" )]
    public float SellPricePercent = 0.5f;

    [Description( "Лимиты на количество построенных зданий" )]
    public List<DBPtr<LimitsOfBuilding>> GroupBuildingLimits;

    public ConstructionTab ConstructionTab;

    [Description("Lord's level required for buying buildings")]
    public int LevelRequired;

    [Description("Тип производимого ресурса (None, если иконка не должна отображаться)")]
    public ConstructionProductionType ProductionIconType;
  }

  public class BathLevel
  {
    [Description( "Уровень для которого указаны параметры" )]
    public int currentLevel;
    [Description( "Сколько героев влезают в баню одновременно" )]
    public int heroesCount;
    [Description( "Коэффициент ускорения пассивного восстановления энергии героя" )]
    public float passiveEnergyRecoveryBoost;
    [Description( "Скидка на цену восстановления героя в бане" )]
    public float recoveryPriceDiscount;
  }

  public class Bath : Constructon
  {
    [Description( "Уровни бани" )]
    public List<BathLevel> BathLevels;
    [Description( "Циклы бани" )]
    public List<BathCycleType> BathCycles;
    [Description( "Стоимость ускорения восстановления единицы энергии" )]
    public float GoldBoostPrice;
  }

  public class TavernExpCoeffToHeroLevel
  {
      public int currentLevel;
      public float coefficient;
  }

	public class Tavern : Constructon
	{
		public List<TavernLevel> tavernLevels;
		public List<TavernLevelQuest> tavernLevelQuests;

        [Description("Дефолтовый квест партуль")]
		public DBPtr<TavernQuest> patrollQuest;

        [Description("Диапазон выбора квестов для ролла")]
		public int questRollRange;

        [Description("Таблица для коэффициентов расчета выдачи опыта в зависимости от уровня героя")]
        public List<TavernExpCoeffToHeroLevel> tavernExpCoeffToHeroLevels;
	}

	public class TavernLevel 
	{
		[Description("Уровень для которого указаны параметры")]
		public int currentLevel;
		[Description("Сколько героев влезают в таверну одновременно")]
		public int heroesCount;
        [Description("Коэффициент для наград (опыта/ресурса)")]
	    public float rewardCoefficient;
	}
	
	public class TavernLevelQuest
	{
		[Description("Список квестов доступных на конкретном уровне")]
		public List<DBPtr<TavernQuest>> tavernQuests;
	}

	[UseTypeName("TAVERNQUEST")]
	public class TavernQuest : DBResource
	{
		[Description("Заголовок квеста")]
		public TextRef title;

		[Description("Описание квеста")]
		public TextRef description;

		[Description("Награды, получаемые за выполнение квеста")]
		public TavernReward reward;

		[Description("Значение на сколько уменьшится энергии для героев, после выполнения квеста")]
		public int energyDecrease;

		[Description("Цена старта таверны")]
		public ResourcesTable priceToStart;

		[Description("Время выполнения квеста")]
		public DBPtr<TimeBlock> estimate;

		[Description("Тип необходимого стата")]
		public EStat statType;

		[Description("Кол-во необходимых статов для выполнения квеста")]
		public int questStatCount;
	}

	public  class TavernReward
	{
        [Description("Ссылка на ролл-таблицу, если награда - талант")]
        public DBPtr<DBRollTalentPercents> rollContainer;

        // УСТАРЕЛО! используй resource
        [Browsable( false )]
        [Description( "Если награда ресурс - тут указать его тип" )]
        public TavernResourceType resourceType = TavernResourceType.None;
        // УСТАРЕЛО! используй resource
        [Browsable( false )]
        [Description( "кол-во получаемого ресурса, в зависимости от уровня (УСТАРЕЛО! используй resource)" )]
        public int resourceRewardCount;

        [Description( "Ресурс" )]
        public ResourcesTable resource;

        [Description("Экспа получаемая за квест, зависит от уровня таверны")]
        public int experience;
	}

  public class Decoration : Constructon
  {
    [Description( "Расса, для которой отображается декорация." )]
    public PF_GameLogic.DBUnit.EHeroRaces fraction = PF_GameLogic.DBUnit.EHeroRaces.A | PF_GameLogic.DBUnit.EHeroRaces.B;
  }

  public class Expansion : Constructon
  {
    [Description( "Уровень на котором данное расширение можно построить" )]
    public int expansionLevel;
  }

  public class BathCycleType
  {
    [Description( "Время работы цикла" )]
    public float cycleDuration;
    [Description("Количество восстанавливаемой энергии")]
    public int restoringEnergy;
    [Description( "Специальные циклы восстановления энергии" )]
    public SpecialBathCycles specialCycle;

    [Description("заголовок цикла")]
    public TextRef cycleTitle;

  }

  public class CycleType
  {
    [Description( "Цена старта добычи ресурсов" )]
    public ResourcesTable priceToStart;
    [Description("Сколько ресурсов добудется. Доступен для namemap'а")]
    [NameMapValue]
    public ResourcesTable resourcesToProduce;
    [Description( "Сколько fame дадут за завершение цикла" )]
    public int fameToProduce = 0;
    [Description( "Время цикла" )]
    public DBPtr<TimeBlock> timeblock;
    [Description( "При true пользователь может менять количество ресурсов, которые он хочет произвести" )]
    public bool isCustom = false;
    [Description( "На что распространяется скидка в цикле - ускорение, время, цена запуска")]
    public DiscountType discountType = DiscountType.None;

		[Description("Кастомный тултип, для циклов")]
		public TextRef customTooltip = new TextRef();
  }

  public class ProductionLevel
  {
    [Description( "Уровень для которого указаны параметры" )]
    public int currentLevel;
    [Description( "Циклы" )]
    public List<CycleType> cycles;
    [Description( "Ресурсов производится в единицу времени" )]
    public ResourcesTable resourcesToProduce;
    [Description( "Вместимость домика" )]
    public ResourcesTable totalProduceCapacity;
    [Description( "Стоимость ускорения производства" )]
    public ResourcesTable boostPrice;
    [Description("Сколько fame дадут за полный цикл")]
    public float fameToProduce;
  }

  public class ProductionBuilding : Constructon
  {
    [Description( "Уровни добывающего здания" )]
    public List<ProductionLevel> ProductionLevels;
    [Description( "Есть ли возможность ускорить производство" )]
    public bool  hasCustomProductionBoost;
    [Description("Единица времени, за которое производится единица ресурса из resourcesToProduce")]
    public int productionTimePeriod;
    [Description("Минимальное время через которое можно собрать ресурс")]
    public int minimalCollectTime;
  }

  public class StorageLevel
  {
    [Description( "Уровень для которого указаны параметры" )]
    public int currentLevel;
    [Description( "На сколько увеличивается максимальный запас" )]
    public ResourcesTable additionalStorage;
  }

  public class StorageBuilding : Constructon
  {
    [Description( "Уровни склада" )]
    public List<StorageLevel> StorageLevels;
  }

  public class HouseLevel
  {
    [Description( "Уровень для которого указаны параметры" )]
    public int currentLevel;
    [Description( "На сколько увеличивается лимит population (НЕ инкриментально, а просто это значение для этого здания)" )]
    public int currentMaxPopulation;
    [Description( "Всегда только 1 цикл" )]
    public CycleType cycle;
    [Description("Ресурсов производится в единицу времени")]
    public ResourcesTable resourcesToProduce;
    [Description("Вместимость домика")]
    public ResourcesTable totalProduceCapacity;
    [Description("Стоимость ускорения производства")]
    public ResourcesTable boostPrice;
    [Description("Сколько fame дадут за полный цикл")]
    public float fameToProduce;
  }

  public class HouseBuilding : Constructon
  {
    [Description( "Уровни жилого здания" )]
    public List<HouseLevel> HouseLevels;
    [Description( "Есть ли возможность ускорить производство" )]
    public bool  hasCustomProductionBoost;
    [Description("Единица времени, за которое производится единица ресурса из resourcesToProduce")]
    public int productionTimePeriod;
    [Description("Минимальное время через которое можно собрать ресурс")]
    public int minimalCollectTime;
  }

  public class PineTreeBuilding : Constructon
  {
      [Description("Уровни ёлки")]
      public List<PineTreeLevel> PineTreeLevels;
  }

  public class PineTreeLevel
  {
      [Description("Уровень для которого указаны параметры")]
      public int currentLevel;
      [Description("Всегда только 1 цикл")]
      public CycleType cycle;
  }


  public class TransmutationLevel
  {
    [Description( "Уровень для которого указаны параметры" )]
    public int currentLevel;

    [Description("Количество талантов, которое крафтится за один цикл кузницы")]
    public int perlForBonuse;

    [Description("Цена добычи одного таланта")]
    public ResourcesTable priceToStart;

    [Description("Сколько fame дадут за завершение цикла")]
    public int fameToProducePerCrystal = 0;
  }

  public class TransmutationBuilding : Constructon
  {
    [Description("Необходимый уровень кузницы для оранжевых талантов, начинается с 1-чки. Те то что пользователь видит на экране")]
    public int requiredLeveForExclusiveTalents = 20;

    [Description("Уровень кузницы, требуемый для доступа к ЛЮБОЙ перековке талантов")]
    public int requiredLeveForReforging = 11;

    [Description("Уровень кузницы, требуемый для перековки ОРАНЖЕВЫХ талантов")]
    public int requiredLeveForReforgingExclusiveTalents = 20;

    [Description("Минимальное качество таланта для перековки")]
    public ETalentRarity requiredRarityForReforging = ETalentRarity.excellent;

    [Description( "Уровни кузницы талантов" )]
    public List<TransmutationLevel> TransmutationLevels;

    [Description("Время цикла в секундах")]
    public int time;
  }

  public class LibraryLevel
  {
    [Description( "Уровень для которого указаны параметры" )]
    public int currentLevel;
    [Description( "На сколько увеличивается максимальное кол-во талантов в библиотеке" )]
    public int additionalTalentSlots;
  }

  public class LibraryBuilding : Constructon
  {
    [Description( "Уровни библиотеки" )]
    public List<LibraryLevel> LibraryLevels;
  }

    public class FirstBuyCycle : CycleType
    {
        [Description("Процент выдачи одного из типа ресурса по окончанию цикла")]
        [EnumArray(typeof(EResourceType))]
        public List<int> percents;
    }

    public class FirstBuyLevel
    {
        [Description("Уровень для которого указаны параметры")]
        public int currentLevel;
        [Description("На сколько увеличивается максимальное кол-во талантов в библиотеке")]
        public int additionalTalentSlots;
        [Description("На сколько увеличивается максимальный запас склада")]
        public ResourcesTable additionalStorage;
        [Description("Ресурсы, дающиеся при покупке")]
        public ResourcesTable resources;
        [Description("Всегда только 1 цикл")]
        public FirstBuyCycle cycle;
    }

    public class FirstBuyBuilding : Constructon
    {
        [Description("Уровни FirstBuy")]
        public List<FirstBuyLevel> FirstBuyLevels;
        [Description("Пет, вызываемый в бою")]
        public DBPtr<Consumable> petItem;
    }

    public class HeroesBuildingLevel
    {
        [Description("Уровень для которого указаны параметры")]
        public int currentLevel;
        [Description("Прибавка стата на 36 уровне")]
        public float statBufValue;
        [Description("Скидка на покупку героев роли в %")]
        public float discount;
        [Description("Снижение требования к уровню замка для героев роли")]
        public int fameReqDecr;
    }

    public class HeroesBuilding : Constructon
    {
        [Description("Роль героя, для которого предназначены бонусы домика")]
        public HeroClassEnum heroClass;
        [Description("Статы, на которые распространяются бонусы")]
        [MinMaxSize(2,2)]
        public List<EStat> buffStats;
        [Description("Уровни HeroesBuilding")]
        public List<HeroesBuildingLevel> HeroesBuildingLevels;
    }

    public class GuildBuilding : Constructon
    {
        
    }

    public class GoldProductionBuilding : Constructon
    {
      [Description("Цикл домика (нужен всего 1 уровень, но название сохранено, чтобы с ним можно было работать так же, как с домиком для населения)")]
      public List<HouseLevel> HouseLevels;
    }

    public class RerollShopBuilding : Constructon
    {

    }
}
