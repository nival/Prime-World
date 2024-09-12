namespace StatisticService.RPC
{
  /// <summary>
  /// Тип события игровой сессии.
  /// </summary>
  public enum SessionEventType
  {
    /// <summary>
    /// Активация таланта.
    /// </summary>
    TalentUsed = 0,

    /// <summary>
    /// Открытие таланта.
    /// </summary>
    TalentUnlocked = 1,

    /// <summary>
    /// Спонтанная покупка.
    /// </summary>
    ImpulsiveBuffUsed = 2,
    
    /// <summary>
    /// Результаты временного среза.
    /// </summary>
    TimeSlice = 4,

    /// <summary>
    /// использовал буст (какой буст).
    /// </summary>
    MG2BoostUsage = 5,

    /// <summary>
    /// запуск миниигры.
    /// </summary>
    MG2Started = 6,

    /// <summary>
    /// проигрыш уровня или прерывание мг2.Если можно различать - различать
    /// </summary>
    MG2LevelFailed = 7,

    /// <summary>
    /// Игрок поменял шарики на платформе (важен сам факт)
    /// </summary>
    MG2BallsChanged = 8,

    /// <summary>
    /// использовал zzgold
    /// </summary>
    MG2ZZBoostUsed = 9,

    /// <summary>
    /// успешная раскраска
    /// </summary>
    MG2LevelWon = 10,

    /// <summary>
    /// начата раскраска
    /// </summary>
    MG2LevelStarted = 11,

    /// <summary>
    /// Убийство.
    /// </summary>
    Kill = 12,

    /// <summary>
    /// Смерть.
    /// </summary>
    Death = 13,

    /// <summary>
    /// Ассист.
    /// </summary>
    Assist = 14,

    /// <summary>
    /// Повышение уровня.
    /// </summary>
    LevelUp = 17,

    /// <summary>
    /// Итем куплен.
    /// </summary>
    ConsumableBought = 18,

    /// <summary>
    /// Итем использован.
    /// </summary>
    ConsumableUsed = 19,

    /// <summary>
    /// Достижение.
    /// </summary>
    Achievement = 20,

    /// <summary>
    /// Возрождение.
    /// </summary>
    Ressurection = 21,

    /// <summary>
    /// Здание уничтожено.
    /// </summary>
    BuildingDestroyed = 22,

    /// <summary>
    /// Флаг поднят.
    /// </summary>
    FlagRaised = 23,

    /// <summary>
    /// Флаг опущен.
    /// </summary>
    FlagDropped = 24,

    /// <summary>
    /// выход из мг2
    /// </summary>
    MG2Exit = 25,

    /// <summary>
    /// Включаемый талант выключен.
    /// </summary>
    TalentSwitchedOff = 26,

    /// <summary>
    /// Получение нафты от убитого героя.
    /// </summary>
    NaftaIncomeFromHero = 27,

    /// <summary>
    /// Получение нафты от убитого существа.
    /// </summary>
    NaftaIncomeFromCreature = 28,

    /// <summary>
    /// Получение нафты от уничтоженного здания.
    /// </summary>
    NaftaIncomeFromBuilding = 29,

    /// <summary>
    /// Получение нафты от использования таланта.
    /// </summary>
    NaftaIncomeFromTalent = 30,

    /// <summary>
    /// Предложение случайной покупки.
    /// </summary>
    ImpulsiveBuffSuggested = 31,

    /// <summary>
    /// Использование чита.
    /// </summary>
    CheatUsed = 32,

    /// <summary>
    /// Получение нафты от импульсного бафа.
    /// </summary>
    NaftaIncomeFromImpulsiveBuff = 33,

    /// <summary>
    /// Получение нафты от миниигры.
    /// </summary>
    NaftaIncomeFromMinigame = 34,

    /// <summary>
    /// Предложение ZZ буста в миниигре.
    /// </summary>
    MG2ZZBoostSuggested = 35,

    /// <summary>
    /// Добавление игрока в игнор
    /// </summary>
    IgnoreAdd = 36,

    /// <summary>
    /// Удаление игрока из игнора
    /// </summary>
    IgnoreRemove = 37,

    /// <summary>
    /// Последний юнит спавнера убит (спавнер убит)
    /// </summary>
    SpawnerDead = 38,

    /// <summary>
    /// Поднятие моста
    /// </summary>
    ToggleOnBridge = 39,

    /// <summary>
    /// Чаннелинг на алтаре
    /// </summary>
    AltarChanneling = 40,

    /// <summary>
    /// Получение нафты за подвиг
    /// </summary>
    NaftaIncomeFromAchievement = 41,

    /// <summary>
    /// Script events
    /// </summary>
    ScriptEvent = 42
  }
}
