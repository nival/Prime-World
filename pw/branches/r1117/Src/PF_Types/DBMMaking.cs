using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBUnit;


namespace PF_GameLogic.DBServer
{
    [Custom("DBServer")]
    [NoCode]
    public enum ESweepStage
    {
        LowerLimit,
        UpperLimit,
        WidenedLimits
    }


  [Custom("DBServer")]
  [DBVersion(1)]
  public class EstimFunctionWeights
  {
    [Description("Вес компоненты про количество девочек в команде")]
    public float ladiesNumber = 1.0f;

    [Description("Вес компоненты про соотношение количества гендерных пар между командами")]
    public float genderPairs = 1.0f;

    [Description("Вес компоненты про количество одинаковых героев")]
    public float heroes = 1.0f;

    [Description("Вес компоненты про разброс рейтинга в команде, только для PVP")]
    public float ratingSpan = 1.0f;

    [Description("Вес компоненты про разброс рейтинга после сортировки игроков по рейтингу")]
    public float ratingPatternDelta = 1.0f;

    [Description("Вес компоненты про разброс среднего рейтинга двух команд")]
    public float ratingTeamAvgDelta = 1.0f;

    [Description("Вес компоненты про разброс форса в команде, только для PVE")]
    public float forceSpan = 1.0f;

    [Description("Вес компоненты про разницу ролей команд, разница между двумя командами")]
    public float heroClassesDifference = 1.0f;

    [Description("Вес компоненты про оптимальность классов героев, срднее между двумя командами")]
    public float heroClassesOptimum = 1.0f;
  }


  [Custom("DBServer")]
  [DBVersion(1)]
  public class MMakingScale
  {
    [Description("Нижняя граница шкалы")]
    public int low = 100;

    [Description("Верхняя граница шкалы")]
    public int high = 1000;

    [Description("Шаг приращения")]
    public int step = 20;

    [Description("Начальная допустимая разница параметра при формировании выборки; Задается кусочно линнейной интерполяцией")]
    public List<LerpDataItem> diffLow = new List<LerpDataItem>();

    [Description("Максимальная допустимая разница параметра при формировании выборки; Задается кусочно линнейной интерполяцией")]
    public List<LerpDataItem> diffHigh = new List<LerpDataItem>();
  }


  [Custom("DBServer")]
  [IndexField("heroClass")]
  [DBVersion(1)]
  public class MMakingHeroClass
  {
    public float minEfficiency = 1.0f;
    public float maxEfficiency = 1.0f;
  }



  [UseTypeName("MAPMMAKING")]
  [Custom("DBServer")]
  [DBVersion(6)]
  public class MapMMakingSettings : DBResource
  {
    [Description("Включает заглушечный ММ")]
    [Custom("Social")]
    public bool mock = false;

    [Description("Включает турнирный режим ММ")]
    [Custom("Social")]
    public bool isTournamentMap = false;

    [Description("Веса компонент оценочной функции")]
    public EstimFunctionWeights estimFunctionWeights = new EstimFunctionWeights();

    [Description("Кратность повторения точек для обычных игроков")]
    public int normalBasePointsRepeatFactor = 5;

    [Description("Кратность повторения точек в нубятнике")]
    public int noobBasePointsRepeatFactor = 40;

    [Description("Время ожидания игрока, за которое допустимая разница рейтинга/форса вырастает до макс. значения")]
    public float ratingDiffGrowTime = 180.0f;

    [Description("Ограничение размера выборки, на которой будет производится полный перебор; Отдельно для каждой фракции")]
    public int fullSweepSubsetLimit = 15;

    [Description("Ограничение размера выборки, на которой будет производится полный перебор; Для PVE режимов")]
    public int fullSweepSubsetLimitPve = 15;

    [Description("Оценочная функция игры будет снижена, если среднее время ожидания игроков находится в этом интервале")]
    public int estimFunDecreaseTimeBegin = 180;

    [Description("Оценочная функция игры будет снижена, если среднее время ожидания игроков находится в этом интервале")]
    public int estimFunDecreaseTimeEnd = 300;

    [Description("Коэффициент понижения оценочной функции в зависимости от времени ожидания")]
    public float estimFunDecreaseFactor = 0.5f;

    [Description("Коэффициент понижения оценочной функции в зависимости от времени ожидания; В режиме маневров")]
    public float estimFunManoeuvresDecreaseFactor = 0.5f;

    [Description("Предельное количество одинаковых героев в предварительной выборке, по которой проводится полный перебор")]
    public int identicalHeroesSampleLimit = 1;

    [Description("Предельное количество одинаковых героев в предварительной выборке, по которой проводится полный перебор; Гвардейский режим")]
    public int identicalGuardHeroesSampleLimit = 1;

    [Description("Предельное количество одинаковых героев в предварительной выборке, по которой проводится полный перебор; Нубские игры")]
    public int identicalNoobHeroesSampleLimit = 2;

    [Description("Минимальное время ожидания. Если в игре присутствуют люди с меньшим временем, то значение ОФ будет дополнительно увеличено в lowWaitTimeFactor раз")]
    public int lowWaitTimeThreshold = 30;

    [Description("Во сколько раз будет увеличена ОФ, если в игре присутствуют люди с временем, меньшим lowWaitTimeThreshold")]
    public float lowWaitTimeFactor = 2.0f;

    [Description("Минимальное число людей в очереди ММ для начала маневров, за одну сторону(устарело и не будет использоваться)")]
    public int manoeuvresMinPopulation = 25;

    [Description("Максимальное число людей в очереди ММ для начала маневров, за другую сторону(устарело и не будет использоваться)")]
    public int manoeuvresMaxPopulation = 10;

    [Description("Минимальное число людей в очереди ММ для начала гвардейских маневров, за одну сторону (устарело и не будет использоваться)")]
    public int guardManoeuvresMinPopulation = 10;

    [Description("Максимальное число людей в очереди ММ для начала гвардейских маневров, за другую сторону (устарело и не будет использоваться)")]
    public int guardManoeuvresMaxPopulation = 10;

    [Description("Минимальное время ожидания для участия запроса в маневрах (устарело и не будет использоваться)")]
    public float manoeuvresWaitThreshold = 180.0f;

    [Description("Ограничение размера выборки, на которой будет производится полный перебор в режиме маневров (устарело и не будет использоваться)")]
    public int manoeuvresFullSweepSubset = 15; //15 - 380k combinations; 20 - 23M combinations

    [Description("Идеальное количество девочек-ботов в тренировке")]
    public int trainingFemaleBotsCount = 1;

    [Description("Идеальное количество девочек с точки зрения ММ")]
    public int necessaryLadiesCount = 1;

    [Description("Компенсирующая набавка к рейтингу для игроков, участвующих в ММ группой")]
    public List<float> partySkillCompensation = new List<float>();

    [Description("Настройки механизма коррекции lose streaks")]
    public MMakingLoseStreakCorrection loseStreakCorrection = new MMakingLoseStreakCorrection();

    [Description("Порог рейтинга, начиная с которого ММ будет придерживать игроков для 'задротов'")]
    public int highRatingThreshold = 1800;

    [Description("Порог рейтинга, начиная с которого игрок считается 'задротом', и для него начинают придерживать более низкорейтинговых")]
    public int proRatingThreshold = 2000;

    [Description("Максимальный рейтинг обычных игроков для участия в нубской игре")]
    public int noobGamesMaxNormalRating = 1500;

    [Description("Время, которое будут продолжать придеживать высокорейтинговых игроков, после ухода последнего 'задрота'")]
    public int highRatingCooldown = 60;

    [Description("Время ожидания игроков-нубов, через которое их могут смешать с normal-игроками")]
    public float noobsTimeout = 45.0f;

    [Description("Минимальный процент содержания нубов в нубской игре, за каждую сторону")]
    public int minimalNoobsPercentage = 60;

    [Description("Разница между рейтингами full-party, при минимальном времени ожидания")]
    public int fullPartyGameRatingDiffMin = 30;

    [Description("Разница между рейтингами full-party, при максимальном времени ожидания")]
    public int fullPartyGameRatingDiffMax = 200;

    [Description("Настройки системы ограничения времени ожидания (tm)")]
    public int waitTimeSoftLimit = 240;

    [Description("Настройки системы ограничения времени ожидания (tm)")]
    public int waitTimeHardLimit = 600;

    [Description("Настройка времени сбора команды, состоящей только из матерых ливеров(tm)")]
    public int teamLeaversTimeTrashold = 600;

    [Description("Настройка времени подбора команды противников, состоящей только из матерых ливеров(tm)")]
    public int gameLeaversTimeTrashold = 300;

    [Description("Настройки учета качества связи с разными pvx-кластерами")]
    public MMakingLocationPingSettings locationPingSettings = new MMakingLocationPingSettings();

    [Description("Вероятность попадания нуба или гвардейца в соответствующую игру в зависимости от времени ожидания")]
    public MMakingWaitVsProbability waitVsProbability = new MMakingWaitVsProbability();

    [Description("Список званий для использования в ММ")]
    public List<MMakingRank> ranks = new List<MMakingRank>();

    [Description("Таблица допустимых разлетов")]
    [EnumArray(typeof(ESweepStage))]
    public List<RecessionData> recessionTableForForceMM = new List<RecessionData>();

    [Description("Таблица добавок к допустимым разлётам за каждые 60 сек ожидания сверх границы")]
    public List<float> recessionPremiumTable = new List<float>();

    [Description("Таблица допустимых разлетов при сборе фулок")]
    public RecessionFullPartyTableForForceMM recessionFullPartyTableForForceMM = new RecessionFullPartyTableForForceMM();
    
    [Description("Граница времени ожидания, начиная с которой работают добавки к допустимым разлётам")]
    public float recessionPremiumTimeThreshold = 0.0f;
      
    [Description("Набор таблиц допустимых разлётов по playerRating для первого/второго/третьего просевов")]
    public RecessionTableForPlayerRatingMM recessionTableForPlayerRatingMM = new RecessionTableForPlayerRatingMM();
      
   [Description("Максимальная разница количеств игроков в командах на промежуточных шагах алгоритма")]
    public int playerDiff = 5;

    [Description("Штраф к времени ожидания за разницу в званиях")]
    public float rankDifferenceTimePenalty = 180.0f;

    [Description("Время расширения допустимых границ классов героев на еденицу, сек")]
    public float heroClassLimitsAttenuationTime = 120.0f;

    [Description("Включает режим ММ по званиям")]
    [Custom("Social")]
    public bool useRanking = false;

    [Description("Таблица оптимальной эффективности классов в команде (из пяти человек)")]
    [EnumArray(typeof(MMakingHeroClassEnum))]
    public List<MMakingHeroClass> optimalClasses = new List<MMakingHeroClass>();

    [Description("Таблица барьера времени ожидания в зависимости от количества доноров в команде, от 0 до 4; Только для ММ по званиям")]
    public List<float> delayPerDonorLocalePlayer = new List<float>();
    
     
    [Description("Размер команды, при которой она официально считается фуллкой")]
    [Custom("Social")]
    public int fullPartySize = 5;

    [Description("Порог времени ожидания, начиная с которого full-party может сматчмейкаться с рандомами")]
    public float fullPartyVsRandomTimeThreshold = 30.0f;

    [Description("Время ожидания, через которое игрок может попасть в игру с разным языком")]
    public int localeWaitTimeThreshold = 45;

    [Description("Параметры расстановки опорных точек рейтинга")]
    public MMakingScale ratingScale = new MMakingScale();

    [Description("Параметры расстановки опорных точек форса")]
    public MMakingScale forceScale = new MMakingScale();

    [Description("Время подбора команды только за свою сторону")]
    public float TeamSideTimeTreshold = 120.0f;
  }



  [Custom("DBServer")]
  public class MMakingWaitVsProbability
  {
    [Description("Время начала линейного участка, сек")]
    public float startingWaitTime = 15.0f;

    [Description("Время окончания линейного участка, сек")]
    public float endingWaitTime = 180.0f;

    [Description("Вероятность (вес) в начале линейного участка. Веса нормируются по всем участникам выборки")]
    public int startingProbabilityWeight = 100;

    [Description("Вероятность (вес) в конце линейного участка. Веса нормируются по всем участникам выборки")]
    public int endingProbabilityWeight = 300;
  }


  [Custom("DBServer")]
  public class MMakingLoseStreakCorrection
  {
    [Description("Минимальное количество проигрышей подряд, с которого начинает работать механизм коррекции")]
    public int minStreak = 2;

    [Description("Штраф форса за каждое последующее поражение")]
    public float forcePenalty = 5.0f;

    [Description("Штраф рейтинга за каждое последующее поражение")]
    public float ratingPenalty = 100.0f;

    //True rocket-scince here
    //Descriptions is useless
    //See full documentation
    public int firstCaseThreshold = 2;
    public float firstCasePenalty = 0.25f;

    public int secondCaseThreshold = 3;
    public float secondCasePenalty = 0.5f;

    public int thirdCaseThreshold = 5;
    public float thirdCasePenalty = 1.0f;
  }


  [Custom("DBServer")]
  public class MMakingLocationPingSettings
  {
    [Description("Все пинги ниже этого порога будут считаться хорошими")]
    public int nicePingThreshold = 40;

    [Description("Минимальный масштаб относительной шкалы пингов")]
    public float pingScaleMinFactor = 2.0f;

    [Description("Добавка к времени ожидания для худших пингов")]
    public int worstPingWaitTimePenalty = 180;

    [Description("Планка для выбора лучшего пинга из доступных")]
    public float goodEnoughPingFactor = 0.2f;

    [Description("Порог рейтинга, после которого не работают ограничения про пинги и локали")]
    public int ratingThreshold = 1800;
  }


  [Custom("DBServer")]
  public class LerpDataItem
  {
    [Description("Независимая переменная")]
    public float x;

    [Description("Зависимая переменная")]
    public float y;
  }


  [Custom("DBServer")]
  public class MMakingRank
  {
    [Description("Минимальный рейтинг")]
    public float lowRating;

    [Description("Объединено ли данное звание со следующим")]
    public bool mergeWithNextRank;

    [Description("Дизайнер, будь внимателен, думай головой и смотри на mergeWithNextRank тоже!")]
    public int mergeRanksCount = 0;

    [Description("Имя для отображения в логах")]
    public string debugName;

    [Description("Надо ли использовать проверку на мощь на данном звании")]
    public bool useForceMM;
    
    [Description("Надо ли использовать проверку на пользовательский рейтинг на данном звании")]
    public bool usePlayerRatingMM;

  }

  [Custom("DBServer")]
  public class RecessionData
  {
      [Description("Таблица разлетов прохода,нумерацию начинаем с нуля, но считаем что 0 это 1, 1 это 2 и т.д. ")]
      public List<float> recessionTable = new List<float>();
      [Description("Использовать добавку за время ожидания")]
      public bool isWaitingTimePremium = true;
  }

  [Custom("DBServer")]
  public class RecessionFullPartyTableForForceMM
   {
       [Description("Таблица допустимых разлетов")]
       public List<float> recessionTable = new List<float>();

       [Description("Таблица добавок к допустимым разлётам за каждые 60 сек ожидания сверх границы")]
       public List<float> recessionPremium = new List<float>();
   }

  [Custom("DBServer")]
  public class RecessionTableForPlayerRatingMM 
  {
      [EnumArray(typeof(ESweepStage))]
      public List<RecessionData> recessionTable = new List<RecessionData>();

      [Description("Значение отвечающие за максимальную разницу по playerRating между игроками внутри команды")]
      public float recessionSideDiff = 0.0f;

      [Description("Добавка 50 к допустимым разлётам за каждые 60 сек ожидания сверх границы recessionPremiumTimeThreshold (учитывается линейно, а не кусочно-постоянно)")]
      public List<float> recessionPremiumTable = new List<float>();

      [Description("Граница времени ожидания, начиная с которой работают добавки к допустимым разлётам для подбора команд по пользовательскому рейтингу")]
      public float recessionPremiumTimeThreshold = 0.0f;
      
      
      [Description("В ходе ММ кандидат с playerRating выше этого значения будет приравнен к этому значению. Пример: кандидат с playerRating 2400 в рамках ММ будет расцениваться как кандидат с playerRating 2000.")]
      public int recessionMaxPlayerRating = 2000;
      [Description("Граница времени ожидания, начиная с которой работают добавки к допустимым разлётам для подбора команд по пользовательскому рейтингу")]
      public int recessionMinPlayerRating = 1200;

  }

}
