    /// Активация таланта.
    NAMED_ENUM(TalentUsed, 0),

    /// Открытие таланта.
    NAMED_ENUM(TalentUnlocked, 1),

    /// Спонтанная покупка.
    NAMED_ENUM(ImpulsiveBuffUsed, 2),

    /// Достижение максимального уровня.
    NAMED_ENUM(MaxLevelReached, 3), // obsolete

    /// Результаты временного среза.
    NAMED_ENUM(TimeSliceResults, 4),

    //использовал буст (какой буст). 
    NAMED_ENUM(MG2BoostUsage, 5),
    
    //запуск миниигры. 
    NAMED_ENUM(MG2Started, 6),
    
    //проигрыш уровня или прерывание мг2.Если можно различать - различать
    NAMED_ENUM(MG2LevelFailed, 7),

    //Игрок поменял шарики на платформе (важен сам факт)
    NAMED_ENUM(MG2BallsChanged, 8),
    
    //использовал zzgold 
    NAMED_ENUM(MG2ZZBoostUsed, 9), 

    //успешная раскраска
    NAMED_ENUM(MG2LevelWon, 10),
    
    //начата раскраска
    NAMED_ENUM(MG2LevelStarted, 11),

    //идентификатор убитого игрока
    NAMED_ENUM(HeroKill, 12),

    //id игрока, id существa
    NAMED_ENUM(HeroDeath, 13), //(если игрок убивается другим игроком, то в "id игрока" передается идентификатор игрока-киллера, "id существа" остается пустым, если же игрок убивается существом, то в "id" существа передается идентификатор существа-киллера, "id игрока" в таком случае остается пустым)
    
    //id игрока (которого убили)
    NAMED_ENUM(KillAssist, 14), 
    
    //уровень персонажа
    NAMED_ENUM(LevelUp, 17), 
    
    //итем, цена
    NAMED_ENUM(ConsumableBought, 18), 
      
    //итем
    NAMED_ENUM(ConsumableUsed, 19), 
    
    //подвиг
    NAMED_ENUM(Deed, 20), 

    //любой (обычный и из баффа)
    NAMED_ENUM(Ressurection, 21),

    //any building is destroyed
    NAMED_ENUM(BuildingDestroyed, 22),

    //события флага. кто поднял и в каком месте
    NAMED_ENUM(FlagPoleRaised, 23),

    //события флага. кто опустил и в каком месте
    NAMED_ENUM(FlagPoleDropped, 24),

    //выход из мг2
    NAMED_ENUM(MG2Exit, 25),

    //Включаемый талант выключен.
    NAMED_ENUM(TalentSwitchedOff, 26),

    //Получение нафты от убитого героя.
    NAMED_ENUM(NaftaIncomeFromHero, 27),

    //Получение нафты от убитого существа.
    NAMED_ENUM(NaftaIncomeFromCreature, 28),

    //Получение нафты от уничтоженного здания.
    NAMED_ENUM(NaftaIncomeFromBuilding, 29),

    //Получение нафты от использования таланта.
    NAMED_ENUM(NaftaIncomeFromTalent, 30),

    //Предложение случайной покупки
    NAMED_ENUM(ImpulsiveBuffSuggested, 31),

    //Использование чита
    NAMED_ENUM(CheatUsed, 32),

    //Получение нафты от импульсного бафа.
    NAMED_ENUM(NaftaIncomeFromImpulsiveBuff, 33),

    //Получение нафты от миниигры.
    NAMED_ENUM(NaftaIncomeFromMinigame, 34),

    //Предложение ZZ буста в миниигре
    NAMED_ENUM(MG2ZZBoostSuggested, 35),

    //Добавление игрока в игнор
    NAMED_ENUM(IgnoreAdd, 36),

    //Удаление игрока из игнора
    NAMED_ENUM(IgnoreRemove, 37),

    //Последний юнит спавнера убит (спавнер убит)
    NAMED_ENUM(SpawnerDead, 38),

    //Поднятие моста
    NAMED_ENUM(ToggleOnBridge, 39),

    // Чаннелинг на алтаре
    NAMED_ENUM(AltarChanneling, 40),

    //Получение нафты за подвиг.
    NAMED_ENUM(NaftaIncomeFromAchievement, 41),

    // Script events
    NAMED_ENUM(ScriptEvent, 42),
