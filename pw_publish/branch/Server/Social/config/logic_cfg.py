# -*- coding: utf-8 -*-
#!/usr/bin/env python


self.DONT_VALIDATE_STEAM_DLC = True
##----------------------------------------------------------------------------------------------------------------------
## блок настроек игровой логики
## soulbound
self.SOULBOUND_ENABLED = True
## debug
self.DEBUG_ENABLED = True
## UserInventory Limit
self.UILIMIT_ENABLED = True
##initial silver value when creating new account
self.INIT_SILVER = 325000
##initial fame value when creating new account
self.INIT_FAME = 40500
##init new account with all heroes available
self.GIVE_ALL_HEROES = False
##Количество дней отчетного периода, за которое мы расчитываем пользовательский рейтинг героя
self.PLAYER_RATING_PERIOD = 30
##Карта, для которой мы рассчитываем пользовательский рейтинг
self.MAPS_FOR_PLAYER_RATING.append("/Maps/Multiplayer/MOBA/_.ADMPDSCR")
##matchmaking rating = hero.Rating + K * hero.Force
self.K_FORCE_RATING = 6.0
##Сколько фракции можно сделать бесплатно
self.FREE_FRACTION_CHANGES = 10
##Сколько смен никаможно сделать бесплатно
self.FREE_NICK_CHANGES = 10
##Сколько стоит смена фракции
self.COST_FRACTION_CHANGE = 495
##Сколько стоит смена ника
self.COST_NICK_CHANGE = 295
##переопределение цены за золото для построек (только при покупке)
self.overrideData( "/Social/Constructions/Buildings/FirstBuy_Cat::Levels.Item.[0].price.Gold", "149" )
self.overrideData( "/Social/Constructions/Buildings/FirstBuy_Dog::Levels.Item.[0].price.Gold", "149" )
##Таланты за новые соцсети ( пока один для одноклассников G185 )
self.TALENTIDS_FOR_NEW_SN.append(1124223207)
self.TALENTIDS_FOR_NEW_SN.append(1049756815)
##! за 3-ю  и последующие соц.сети (fb+ok+vk и т.п.) бонусных талантов не даем

# ##Сколько стоит снятие soulbound'a с синего таланта
# self.COST_UNSOULBOUND_TALENT_BLUE = 0
# self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[3].Silver", "1" )
# ##Сколько стоит снятие soulbound'a с фиолетвого таланта
# self.COST_UNSOULBOUND_TALENT_VIOLET = 0
# self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[4].Silver", "1" )
# ##Сколько стоит снятие soulbound'a с оранжевого таланта
# self.COST_UNSOULBOUND_TALENT_ORANGE = 0
# self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[5].Perl", "9" )
# ##Сколько стоит снятие soulbound'a с красного таланта
# self.COST_UNSOULBOUND_TALENT_RED = 9

## Хаку и Даку нельзя брать в одну группу в замке.
self.blockHeroesPairForParty("crusader_A","crusader_B")


## Оверрайд цены запуска квеста на указанный талант
#self.overrideData("/Social/Quests/TalentQuests/_Settings::OverridenPricesMap.Item.[3].Resources.Shard", "111", OverrideType.Client) #клиент
#self.overrideData("/Social/Quests/TalentQuests/_Settings::OverridenPricesMap.G575.Shard", "111", OverrideType.Server) #сервер

## Оверрайд цены отвязки в зависимости от уровня заточки 0 - 1-5 звезд, 1 - 6 звезд и тд.
#self.overrideData( "/Social.ROOT::TalentsUnsoulboundPriceByLevel.Item.[0].price", "5", OverrideType.Both)


## Отключение альтернативных ультов
##self.DISABLED_DEFAULT_TALENSETS.append("/Items/Talents/Marine_Alternative.TALENTSET")
##self.DISABLED_DEFAULT_TALENSETS.append("/Items/Talents/Faceless_Alternative.TALENTSET")

## Цена серебра за золото
self.overrideData( "/Social.ROOT::resourcesToGoldPrice.Silver.resourceCount", "2000")

self.EventToolsChangeFields.HERO_SILVER_PRICES.add('pinkgirl', 0)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "pinkgirl", 3 ) #цены в золоте на конкретных героев, если стандартное переопределение не подходит (МУЖСКОЙ АКК)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "pinkgirl", 3 ) #цены в золоте на конкретных героев, если стандартное переопределение не подходит (ЖЕНСКИЙ АКК)

##Цены в золоте на конкретных героев, если стандартное переопределение не подходит
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "frogenglut", 0 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "frogenglut", 0 )

self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "rifleman", 299 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "rifleman", 299 )

self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "freeze", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "freeze", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add("angel", 499)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add("angel", 499)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "monster", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "monster", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "crusader_A", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "crusader_A", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "crusader_B", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "crusader_B", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "witch", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "witch", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "vampire", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "vampire", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "alchemist", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "alchemist", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "demonolog", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "demonolog", 499 )


#Время начала\окончания сезонов
self.overrideData( "/Social.ROOT::Seasons.Item.[0].stopTime", "1494806400" )
self.overrideData( "/Social.ROOT::Seasons.Item.[1].startTime", "1494806400" )
self.overrideData( "/Social.ROOT::Seasons.Item.[1].stopTime", "1501372800" )
self.overrideData( "/Social.ROOT::Seasons.Item.[2].startTime", "1501372800" )

#Сезонные скины
self.SEASON_SKINS.append("naga_S3")


self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add("witchdoctor", 399)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add("witchdoctor", 399)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "ghostlord", 324 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "ghostlord", 324 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "faceless", 249 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "faceless", 249 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add("bard", 199)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add("bard", 199)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add("witcher", 174)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add("witcher", 174)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add("fairy", 154)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add("fairy", 154)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "night", 134 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "night", 134 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add("manawyrm", 119)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add("manawyrm", 119)
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "inventor", 79 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "inventor", 79 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "artist", 79 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "artist", 79 )


self.EventToolsChangeFields.SKIN_GOLD_PRICES.add("healer_S2", 19)
self.EventToolsChangeFields.SKIN_GOLD_PRICES.add("unicorn_S3", 19)
self.EventToolsChangeFields.SKIN_GOLD_PRICES.add("mage_S2", 19)
self.EventToolsChangeFields.SKIN_GOLD_PRICES.add("hunter_S3", 19)
self.EventToolsChangeFields.SKIN_GOLD_PRICES.add("fluffy_S1", 19)
self.EventToolsChangeFields.SKIN_GOLD_PRICES.add("fairy_S2", 19)



## Цена на скины
self.EventToolsChangeFields.SKIN_GOLD_PRICES.add("witchdoctor_S2", 29)
self.EventToolsChangeFields.SKIN_GOLD_PRICES.add("fallenangel_S1", 29)

##self.INVALID_HEROES.append('fallenangel')

## Длительность буста дистиллятора в секундах
self.TOTAL_BOOST_TIME = 82800


##Платежный сервер
self.PAY_SERVER = "https://pay.playpw.com"
##Фракция, которая выбрана по умолчанию. "A" - Докты, "B" - Адорницы, "N" - не выбрана
self.DEFAULT_FRACTION = "B"
## отклонение от среднего Force для партий (+-); помним, что в UI force показывается умноженным на 10! т.е. 1600 force в UI это 160.0 в коде!
self.PARTY_FORCE_RANGE = 10.0
## отклонение от среднего рейтинга для партий (+-)
self.PARTY_RATING_RANGE = 100.0


#Гвардейцы - переопредение мощи, с которой герой считается гвардейцем - на текущий момент логика гвардов не используется, поэтому значение высокое, чтобы никто им никогда не стал
self.EPIC_HERO_FORCE = 10000.0


self.SHARING_WEBSITE_SALT = "http://share.qa.playpw.com/share.php"

## Премиум-аккаунт - Золотой век
##----------------------------------------------------------------------------------------------------------------------
##продолжительность действия премиум аккаунта (менять последнюю цифру)
self.PREMIUM_ACCOUNT_DURATION = (24*60*60) * 30
##цена премиум аккаунта
self.PREMIUM_ACCOUNT_PRICE = 299
##продолжительность действия премиум аккаунта2 (менять последнюю цифру)
self.PREMIUM_ACCOUNT_DURATION2 = (24*60*60) * 7
##цена премиум аккаунта2
self.PREMIUM_ACCOUNT_PRICE2 = 99
##продолжительность действия премиум аккаунта3 (менять последнюю цифру)
self.PREMIUM_ACCOUNT_DURATION3 = (24*60*60) * 3
##цена премиум аккаунта3
self.PREMIUM_ACCOUNT_PRICE3 = 49
##----------------------------------------------------------------------------------------------------------------------


## Блок про добавление новостей
##----------------------------------------------------------------------------------------------------------------------

self.addNews( "Зимние состязания", "Зимние состязания", "http://ru.playpw.com/images/promo/olimpic_icon.png", "http://ru.playpw.com/images/promo/olimpic_doct_rus.png", "На время Зимних состязаний в замке Вас ждут новые квесты, в награду за которые Вы получите уникальный талант - Медаль победителя! Также для Вас доступен новый образ - Чемпион! Приобрести данный скин Вы можете в окне информации о герое Молниеносный/Громовержец только до 23 февраля! Не упустите свой шанс, примите эстафету Зимнего огня!", "http://ru.playpw.com/images/promo/olimpic_adorn_rus.png" )
# Новости о бесплатном контенте за регистрацию через Aeria
# русский
self.addNews( "Подарок от Aeria Games", "Подарок от Aeria Games", "http://ru.playpw.com/images/pay/dlc_icon.png", "http://ru.playpw.com/images/pay/aeria-r.png", "Спасибо за регистрацию через сеть Aeria Games! Пожалуйста, примите небольшой подарок в качестве благодарности: 5000 всех видов ресурсов, 10 000 серебра и 5 кристаллов прайма.", "", "ae", 1, True  )

# английский
# self.addNews( "Aeria Games Bonus", "Aeria Games Bonus", "http://en.playpw.com/images/pay/dlc_icon.png", "http://en.playpw.com/images/pay/aeria-e.png", "Thank you for registering via Aeria Games network! Please take this small gift as a token of our gratitude: 5,000 of each type of resources, 10,000 Silver, and 5 Prime Crystals.", "", "ae", 1, True  )
##----------------------------------------------------------------------------------------------------------------------

## Блок акций
##----------------------------------------------------------------------------------------------------------------------
#Кол-во сообщений администрации
self.ADMIN_MESSAGES_TO_STORE = 10


# Акция покупки спец. героя
# продавать Путник
self.BuySpecialHeroEventInfo.HeroIdA = "rifleman"
self.BuySpecialHeroEventInfo.HeroIdB = "rifleman"
# стоимость покупки героя по этой акции в рублях
self.BuySpecialHeroEventInfo.Price = 299

##Цена акции "Купи героя" в золоте
self.BUY_HERO_PRICE = 9
##Максимальная цена в серебре для героя, участвующего в акции "Купи героя"
self.BUY_HERO_MAX_ORIGINAL_PRICE = 125000

##Включаем акции, чтобы выключить - закомментируйте
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/PremiumAcc" )
#self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyHero" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/FirstBuy" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuySpecialHero" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyGoldHero" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuySteamDLC" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuySteamGold" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyAeriaGold" )
##self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyArcGamesGold" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyZZimaGold" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/TournamentInProgressEvent" )
#self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyGoldenLodge" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuildGoldenLodge" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyFlag" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BeginnersPackEvent" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/UpgradeHeroTalentsEvent" )

self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_FEMALE.add( "vampire", 499 )
self.BuyGoldHeroInfo.REPLACE_GOLD_PRICES_MALE.add( "vampire", 499 )

##----------------------------------------------------------------------------------------------------------------------

#Рейтинги героев в замке

##----------------------------------------------------------------------------------------------------------------------
self.HERO_START_RATING = 1100    # Стартовый рейтинг свежекупленного героя
self.HERO_CUP_RATING = 1700     # Кап на рейтинг свежекупленного героя
self.HERO_DELTA_RATING = 0       # Разница между рейтингом самого высокорейтингового героя и рейтингом свежекупленного героя
self.HERO_COEFF_RATING = 0.55     # Коэффициент для высчитывания рейтинга свежекупленного героя между стартовым рейтингом и самым высокорейтинговым


##Рейтинг с которого доступен тамбур
self.TamburInfo.TamburStartRaiting = 1800
##----------------------------------------------------------------------------------------------------------------------

# Пинги
##----------------------------------------------------------------------------------------------------------------------
self.PingInfo.Frequency = 60*15 #как часто пинговать (раз в 15 минут)
self.PingInfo.TryCount = 5 #сколько попыток на один адрес
self.PingInfo.MaxTimeOut = 9000 #максимальное ожидание ответа в ms (оно же - пинг по умолчанию)
self.PingInfo.addresses.add("ru0","http://pw.nivalnetwork.com:88/ping")
self.PingInfo.addresses.add("ru1","http://pw.nivalnetwork.com:88/ping")
self.PingInfo.addresses.add("tr0","http://pw.nivalnetwork.com:88/ping")
##----------------------------------------------------------------------------------------------------------------------



# Волшебная лампа
#-------------------------------------------------------------------------------------------------------------------------------------
# Период когда лампа не выпадет ни при каких обстоятельствах (c последнего выпадания) должен иметь в себе ключи start и end
self.LampEventSettings.BlockLampPeriod.add("start",1)
self.LampEventSettings.BlockLampPeriod.add("end",3)
# Период гарантированного выпадения лампы (c последнего выпадания) должен иметь в себе ключи start и end
self.LampEventSettings.GuarantyLampPeriod.add("start",5)
self.LampEventSettings.GuarantyLampPeriod.add("end",6)
# Активная группа для которое может выпасть ламп, параметром отбора в группу является диапазон дат(в днях от последнего платежа
self.addLampActiveGroup(1,10)
# Количество доступных бонусных денег по одной лампе (в золоте), если этот параметр равен 0 - акция недоступна
self.LampEventSettings.BonusGold = 3000
# Длительность действия одной лампы (в секундах)
self.LampEventSettings.Duration = 500
#Количество доступных транзакций по одной лампе, если этот параметр равен 0 - акция недоступна
self.LampEventSettings.Transactions = 2
#Вероятность того, что ролл сервис вообще будет роллить лампу в случае первой победы (даже при благоприятных остальных условиях). От 0 до 100
self.LampEventSettings.FwodLampRollProbability = 100
# Счётчик кол-ва возможных первых побед в день
self.LampEventSettings.FWODLimit = 1
#Вероятность того, что ролл сервис вообще будет роллить лампу (даже при благоприятных остальных условиях). От 0 до 100
self.LampEventSettings.LampRollProbability = 100
#Максимальное кол-во дней от последнего платежа для статуса платящего игрока
self.LampEventSettings.MaxPaymentDaysForGoldStatus = 30
#----------------------------------------------------------------------------------------------------------------------------------------

# URL хранилища иконок гильдии и паттерн для составления имени файла - иконки гильдии.
# (i) Для загрузки иконок используется coord_cfg.GUILD_ICONS_UPLOAD_URL_PATTERN
self.GUILD_ICONS_URL_PATTERN = "http://pw-updates.nivalnetwork.com/guild_logo/{guild_id}_{changes_count}.png"
#Доступность вкладки банка гильдий
self.GuildBankSettings.IS_GUILD_BANK_ACTIVE = True


# Курсы валют Steam

self.BuySteamGoldEventInfo.CurrencyIndex.add( "USD", 1.0/30.0 )
self.BuySteamGoldEventInfo.CurrencyIndex.add( "GBP", 1.0/50.0 )
self.BuySteamGoldEventInfo.CurrencyIndex.add( "EUR", 1.0/40.0 )
self.BuySteamGoldEventInfo.CurrencyIndex.add( "RUB", 1.0 )
self.BuySteamGoldEventInfo.CurrencyIndex.add( "BRL", 1.0/15.0 )

# Настройка кнопок в акции покупки золота для разных игровых площадок
#--------------------------------------------------------------------------------

# Steam (6 штук)
self.addSteamItem(1, 10, 0, 1000, "UI/Textures/Steam/Items/Ru/10", "10 золота")
self.addSteamItem(2, 100, 0, 10000, "UI/Textures/Steam/Items/Ru/100", "100 золота")
self.addSteamItem(3, 300, 0, 30000, "UI/Textures/Steam/Items/Ru/300", "300 золота")
self.addSteamItem(4, 500, 0, 50000, "UI/Textures/Steam/Items/Ru/500", "500 золота")
self.addSteamItem(5, 1000, 0, 100000, "UI/Textures/Steam/Items/Ru/1000", "1000 золота")
self.addSteamItem(6, 3000, 0, 300000, "UI/Textures/Steam/Items/Ru/3000", "3000 золота")
self.BuySteamGoldEventInfo.Category = "золото"

# Aeria
self.addAeriaItem(1, 25, 0, 99, "UI/Textures/Aeria/01ap", "25 золота")
self.addAeriaItem(2, 125, 0, 499, "UI/Textures/Aeria/02ap", "125 золота")
self.addAeriaItem(3, 350, 0, 1299, "UI/Textures/Aeria/03ap", "350 золота")
self.addAeriaItem(4, 550, 0, 1999, "UI/Textures/Aeria/04ap", "550 золота")
self.addAeriaItem(5, 1000, 0, 3499, "UI/Textures/Aeria/05ap", "1000 золота")
self.addAeriaItem(6, 1500, 0, 4999, "UI/Textures/Aeria/06ap", "1500 золота")

# ArcGames
self.addArcGamesItem(1, 35, 0, 150, "UI/Textures/ArcGames/Items/RU/01zen_ru", "35 золота")
self.addArcGamesItem(2, 110, 0, 450, "UI/Textures/ArcGames/Items/RU/02zen_ru", "110 золота")
self.addArcGamesItem(3, 225, 0, 900, "UI/Textures/ArcGames/Items/RU/03zen_ru", "225 золота")
self.addArcGamesItem(4, 515, 0, 2000, "UI/Textures/ArcGames/Items/RU/04zen_ru", "515 золота")
self.addArcGamesItem(5, 810, 0, 3000, "UI/Textures/ArcGames/Items/RU/05zen_ru", "810 золота")
self.addArcGamesItem(6, 1460, 0, 5000, "UI/Textures/ArcGames/Items/RU/06zen_ru", "1460 золота")

## Включить использование оверлея арка для покупок
self.ARCGAMES_USE_OVERLAY = True


#ZZima
self.addZZimaItem(1, 10, 0, 10, "UI/Textures/Zzima/10zz", "10 золота")
self.addZZimaItem(2, 50, 0, 50, "UI/Textures/ZZima/50zz", "50 золота")
self.addZZimaItem(3, 100, 0, 100, "UI/Textures/ZZima/100zz", "100 золота")
self.addZZimaItem(4, 500, 0, 500, "UI/Textures/ZZima/500zz", "500 золота")
self.addZZimaItem(5, 1000, 0, 1000, "UI/Textures/ZZima/1000zz", "1000 золота")
self.addZZimaItem(6, 2000, 0, 2000, "UI/Textures/ZZima/2000zz", "2000 золота")
#---------------------------------------------------------------------------------

#Тип жалобы ( категория(int) и описание(string) )
self.ComplaintsSettings.COMPLAINTS_TYPES.add( 0, "Оскорбления" )
self.ComplaintsSettings.COMPLAINTS_TYPES.add( 1, "Неспортивное поведение" )
#self.ComplaintsSettings.COMPLAINTS_TYPES.add( 2, "Использование бота" )
#Максимальное количество жалоб от игрока в день
self.ComplaintsSettings.MAX_COMPLAINTS_PER_DAY = 5
# хранить и присылать с жалобой не более 200 сообщений чата замка
self.ComplaintsSettings.CHAT_MSG_HISTORY_SIZE = 200
# хранить и присылать с жалобой сообщения не старше 10 минут (600 секунд)
self.ComplaintsSettings.CHAT_MSG_HISTORY_TIME = 600

# Заполнение покупаемых флагов
#----------------------------------------------------------------------------------------------------------------
self.addCustomFlag("adornia",49)
self.addCustomFlag("bat",49)
self.addCustomFlag("bike",49)
self.addCustomFlag("CSKA",99)
self.addCustomFlag("dagger",49)
self.addCustomFlag("dokt",49)
self.addCustomFlag("fire_sword",49)
#self.addCustomFlag("flower",99)
self.addCustomFlag("kapitoshka",49)
self.addCustomFlag("kote",99)
self.addCustomFlag("krest",49)
self.addCustomFlag("lips",49)
self.addCustomFlag("morkov",99)
self.addCustomFlag("pautina",49)
self.addCustomFlag("pirat",99)
self.addCustomFlag("prime",49)
self.addCustomFlag("rak",99)
self.addCustomFlag("rock",99)
self.addCustomFlag("spartak",99)
self.addCustomFlag("spoon",49)
self.addCustomFlag("tikva",49)
self.addCustomFlag("troll",99)
self.addCustomFlag("USSR",99)
self.addCustomFlag("zenit",99)
self.addCustomFlag("zubi",49)

#self.addCustomFlag("smile",49)
#self.addCustomFlag("fun_smile",49)
#self.addCustomFlag("lightning",99)
#self.addCustomFlag("in_yan",49)
self.addCustomFlag("jedi",99)
self.addCustomFlag("crab",99)
self.addCustomFlag("dragon",49)
self.addCustomFlag("casino",49)
self.addCustomFlag("devil",99)
self.addCustomFlag("apple",49)
self.addCustomFlag("peace",49)
self.addCustomFlag("no lobster",99)
self.addCustomFlag("ball",49)
self.addCustomFlag("packman",99)
self.addCustomFlag("radiation",49)
self.addCustomFlag("hockey",49)
self.addCustomFlag("owl",99)
#self.addCustomFlag("hypnosis",49)
self.addCustomFlag("bebebe",19)
self.addCustomFlag("x-tree",0)
#-------------------------------------------------------------------------------------------------------------------

#платежный сервер для mail.ru
self.MAILRU_PAY_SERVER = "http://nival.com"

#-----------------------------------------------------------------------------------------------------------------------
#-------------------------------------------GAMIGO---------------------------------------------------------------
self.GAMIGO_PAY_SERVER = "http://gamigo.qa.nivalnetwork.com/game-server/get-shop-url"
self.GAMIGO_PAY_URL_SALT = "f84fff0134a3221a4b5ea0330cd3ca64"
#------------------------------------------------------------------------------------------------------------------------

self.DRAUGASLT_PAY_SERVER = "http://pay.playpw.com"
# self.DRAUGASLT_PAY_URL_SALT = ""
# self.DRAUGASLT_PAY_URL_PARAMS = ""

#Запретные ники
#self.ADMIN_NICKS.append(u"admin")
#self.ADMIN_NICKS.append(u"Administrator")
#self.ADMIN_NICKS.append(u"Администрация")

##Перековка талантов
# Включаем перековку
self.IS_REFORGE_ACTIVE = True

# стоимости цен для перековки # TODO
# Цена перековки фиола 1лвл (для сервера и замка)
self.overrideData("/Social.ROOT::ReforgeTalentPrices.magnificent.rerollPrices.Item.[0].priceWithoutSetFilter.Perl", "4")
self.overrideData("/Social.ROOT::ReforgeTalentPrices.magnificent.rerollPrices.Item.[0].priceWithSetFilter.Perl", "4")
self.overrideData("/Social.ROOT::ReforgeTalentPrices.Item.[1].rerollPrices.Item.[0].priceWithoutSetFilter.Perl", "4")
self.overrideData("/Social.ROOT::ReforgeTalentPrices.Item.[1].rerollPrices.Item.[0].priceWithSetFilter.Perl", "4")
# Цена улучшения фиола в оранж
#self.overrideData("/Social.ROOT::ReforgeTalentPrices.Item.[0].upgradePrice", "12")
# Цена перековки оранжа
#self.overrideData("/Social.ROOT::ReforgeTalentPrices.Item.[1].rerollPrice", "10")
# Цена перековки оранжа в красный
#self.overrideData("/Social.ROOT::ReforgeTalentPrices.Item.[1].upgradePrice", "10")
# Цена перековки красного в красный
#self.overrideData("/Social.ROOT::ReforgeTalentPrices.Item.[2].rerollPrice", "8")


self.addBeginnerPack(1, 199, "http://ru.playpw.com/images/100/bp/bp_01.png", "MagStrAspd", "<style:TT_talent_rar_small_3>Набор чемпиона: Сила и Проворство</style><br><br>Набор содержит 10 <style:TT_talent_rar_small_3>уникальных</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Сила и Проворство.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природная сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природное проворство<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Путь воина<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет силы<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет проворства<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Недюжинная сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Внезапная стремительность<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Неумолимая сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Проворство ирбиса<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Раскрытый потенциал</style>", ["G208" , "G275", "G182", "G260", "G279", "G281", "G284", "G286", "G129", "G187"])
self.addBeginnerPack(2, 199,  "http://ru.playpw.com/images/100/bp/bp_02.png", "MagStrDex", "<style:TT_talent_rar_small_3>Набор чемпиона: Сила и Хитрость</style><br><br>Набор содержит 10 <style:TT_talent_rar_small_3>уникальных</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Сила и Хитрость.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природная сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природная хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Путь воина<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет силы<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет хитрости<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Недюжинная сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Разрушительная хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Неумолимая сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Коварство кобры<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Раскрытый потенциал</style>", ["G208" , "G276", "G182", "G260", "G278", "G281", "G283", "G286", "G129", "G188"])
self.addBeginnerPack(3, 49,  "http://ru.playpw.com/images/100/bp/bp_05.png", "ExStrAspd", "<style:TT_talent_rar_small_2>Набор героя: Сила и Проворство</style><br><br>Набор содержит 2 <style:TT_talent_rar_small_3>уникальных</style> таланта и 8 <style:TT_talent_rar_small_2>редких</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Сила и Проворство.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природная сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природное проворство<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Отчаянная сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Редкая сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Редкое проворство<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Ненасытная ярость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Тренировка проворства<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Ловкость рук<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Свирепость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Проворство рыси</style>", ["G180" , "G069", "G061", "G085", "G153", "G145", "G191", "G238", "G129", "G187"])
self.addBeginnerPack(4, 49,  "http://ru.playpw.com/images/100/bp/bp_06.png", "ExStrDex", "<style:TT_talent_rar_small_2>Набор героя: Сила и Хитрость</style><br><br>Набор содержит 2 <style:TT_talent_rar_small_3>уникальных</style> таланта и 8 <style:TT_talent_rar_small_2>редких</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Сила и Хитрость.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природная сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природная хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Отчаянная сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Редкая сила<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Редкая хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Ненасытная ярость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Возрастающая хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Жажда разрушения<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Свирепость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Лисье коварство</style>", ["G179" , "G069", "G053", "G085", "G154", "G145", "G192", "G238", "G129", "G188"])
self.addBeginnerPack(5, 199,  "http://ru.playpw.com/images/100/bp/bp_03.png", "MagIntAspd", "<style:TT_talent_rar_small_3>Набор чемпиона: Разум и Проворство</style><br><br>Набор содержит 10 <style:TT_talent_rar_small_3>уникальных</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Разум и Проворство.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природный разум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природное проворство<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Путь мага<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет разума<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет проворства<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Недюжинный ум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Внезапная стремительность<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Благородный ум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Проворство ирбиса<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Раскрытый потенциал</style>", ["G207" , "G275", "G182", "G261", "G279", "G282", "G284", "G287", "G130", "G187"])
self.addBeginnerPack(6, 199,  "http://ru.playpw.com/images/100/bp/bp_04.png", "MagIntDex", "<style:TT_talent_rar_small_3>Набор чемпиона: Разум и Хитрость</style><br><br>Набор содержит 10 <style:TT_talent_rar_small_3>уникальных</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Разум и Хитрость.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природный разум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природная хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Путь мага<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет разума<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет хитрости<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Недюжинный ум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Разрушительная хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Благородный ум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Коварство кобры<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Раскрытый потенциал</style>", ["G207" , "G276", "G182", "G261", "G278", "G282", "G283", "G287", "G130", "G188"])
self.addBeginnerPack(7, 49,  "http://ru.playpw.com/images/100/bp/bp_07.png", "ExIntAspd", "<style:TT_talent_rar_small_2>Набор героя: Разум и Проворство</style><br><br>Набор содержит 2 <style:TT_talent_rar_small_3>уникальных</style> таланта и 8 <style:TT_talent_rar_small_2>редких</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Разум и Проворство.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природный разум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природное проворство<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Отчаянный разум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Редкий ум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Редкое проворство<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Тренировка разума<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Тренировка проворства<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Ловкость рук<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Величие разума<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Проворство рыси</style>", ["G180" , "G065", "G061", "G086", "G153", "G191", "G144", "G239", "G130", "G187"])
self.addBeginnerPack(8, 49,  "http://ru.playpw.com/images/100/bp/bp_08.png", "ExIntDex", "<style:TT_talent_rar_small_2>Набор героя: Разум и Хитрость</style><br><br>Набор содержит 2 <style:TT_talent_rar_small_3>уникальных</style> таланта и 8 <style:TT_talent_rar_small_2>редких</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Разум и Хитрость.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природный разум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природная хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Отчаянный разум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Редкий ум<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Редкая хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Тренировка разума<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Возрастающая хитрость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Жажда разрушения<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Величие разума<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Лисье коварство</style>", ["G179" , "G065", "G053", "G086", "G154", "G192", "G144", "G239", "G130", "G188"])
self.addBeginnerPack(9, 199,  "http://ru.playpw.com/images/100/bp/bp_09.png", "MagLifeWill", "<style:TT_talent_rar_small_3>Набор чемпиона: Здоровье и Воля</style><br><br>Набор содержит 10 <style:TT_talent_rar_small_3>уникальных</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Здоровье и Воля.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природное здоровье<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Тренировка тела<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет здоровья<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Противостояние магии<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Расторопность<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Отвага древних<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Воля к победе<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Легендарное здоровье<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Невозмутимость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Безупречная защита</style>", ["G235" , "G245", "G212", "G171", "G277", "G285", "G155", "G247", "G138", "G231"])
self.addBeginnerPack(10, 199,  "http://ru.playpw.com/images/100/bp/bp_10.png", "MagLifeStam", "<style:TT_talent_rar_small_3>Набор чемпиона: Здоровье и Стойкость</style><br><br>Набор содержит 10 <style:TT_talent_rar_small_3>уникальных</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Здоровье и Стойкость.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природное здоровье<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Тренировка тела<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Секрет здоровья<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Противостояние силе<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Расторопность<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Отвага древних<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Героическая стойкость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Легендарное здоровье<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Толстокожесть<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Безупречная защита</style>", ["G234" , "G245", "G212", "G170", "G277", "G285", "G156", "G247", "G138", "G231"])
self.addBeginnerPack(11, 49,  "http://ru.playpw.com/images/100/bp/bp_11.png", "ExLifeWill", "<style:TT_talent_rar_small_2>Набор героя: Здоровье и Воля</style><br><br>Набор содержит 2 <style:TT_talent_rar_small_3>уникальных</style> таланта и 8 <style:TT_talent_rar_small_2>редких</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Здоровье и Воля.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природное здоровье<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Невозмутимость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Выживание сильнейшего<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Надежность<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Росток жизни<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Отважное сердце<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Твердость суждений<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Укрепление веры<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Сердце дракона<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Выдержка</style>", ["G235" , "G072", "G269", "G200", "G078", "G093", "G090", "G009", "G087", "G231"])
self.addBeginnerPack(12, 49, "http://ru.playpw.com/images/100/bp/bp_12.png", "ExLifeStam", "<style:TT_talent_rar_small_2>Набор героя: Здоровье и Стойкость</style><br><br>Набор содержит 2 <style:TT_talent_rar_small_3>уникальных</style> таланта и 8 <style:TT_talent_rar_small_2>редких</style> талантов.<br>Он подойдет героям, которым рекомендованы характеристики Здоровье и Стойкость.<br><br>Таланты, которые входят в набор:<br><br><space:15 pixels=on>• <style:TT_talent_rar_small_3>Природное здоровье<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_3>Толстокожесть<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Выживание сильнейшего<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Выносливость<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Росток жизни<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Отважное сердце<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Твердость характера<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Стальная закалка<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Сердце дракона<br></style><space:15 pixels=on>• <style:TT_talent_rar_small_2>Устойчивость</style>", ["G234" , "G072", "G268", "G200", "G077", "G092", "G090", "G006", "G087", "G231"])

self.addGuildShopItems(["CS001", "CS002", "CS003", "CS004", "CS005", "CS006", "CS007", "CS008", "CS009", "CS010", "CS011", "CS012", "CS013", "CS014", "CS015", "CS016", "CS017", "CS018", "CS019", "CS020", "CS021", "CS022", "CS023", "CS024", "CS025", "CS026", "CS027", "CS028", "CS029", "CS030", "CS031", "CS032", "CS033", "CS034", "CS035", "CS036", "CS037", "CS038", "CS039", "CS040", "CS041", "CS042", "CS043", "CS044", "CS045", "CS046", "CS047", "CS048", "CS049", "CS050", "CS051", "CS052", "CS053", "CS054", "CS055", "CS056", "CS057", "CS058", "CS059", "CS060", "CS061", "CS062", "CS063", "CS064", "CS065", "CS066", "CS067", "CS068", "CS069", "CS070", "CS071", "CS072", "CS073", "CS074", "CS075", "CS076", "CS077", "CS078", "CS079", "CS080", "CS081", "CS082", "CS083", "CS084", "CS085", "CS086", "CS087", "CS088", "CS089"])

#self.overrideData("/Dialog/CastleTutorial/StartQuest::answers.Item.[0].actions.Item", "[]")


#PF-92484  Добавить рекомендованных вассалов в данные по карте
# X = MINIMAL_SIEGE_PARTICIPATION_PRICE + max(рейтингЗахватываемогоКлана*SIEGES_START_MULT_COEFF - SIEGES_START_ADD_COEFF; 0)
self.SiegeSettings.SIEGES_START_MULT_COEFF = 2.0
#Процент очков от реальной стоимости осады для вычисления стоимости захвата потенциальных вассалов с карты клана и бывших вассалов
self.SiegeSettings.SIEGE_DISCOUNT = 0.2

#self.SiegeSettings.TIMEOUT_FOR_EX_VASSAL_CAPTURE = 240
#self.SiegeSettings.TIMEOUT_FOR_CAPTURE_AFTER_LOSS = 120
#self.SiegeSettings.SIEGE_DURATION = 60

# Квесты запускаемы при скипе туториала
self.SKIPPED_TUTORIAL_QUESTS.add('A', 'ts11_qA')
self.SKIPPED_TUTORIAL_QUESTS.add('B', 'ts11_qB')

self.WEB_IM_ENABLED = True

#Штраф за додж из тамбура
self.EPIC_HERO_RETIRED_CAP = 4800
self.EPIC_HERO_RETIRED_TIME_INC = 1


#Максимальное количество очков набранных в играх c ливом игрока, которое может быть набрано
#self.MAX_LEAVES_POINT = 18

#Количество очков, которое необходимо, чтобы оставалось для выхода из ливерской корзины
#self.MIN_LEAVES_POINT = 6

#Количество очков, которое добавляется после лива игрока
#self.ADD_LEAVE_POINT = 6

#Количество очков, которое отнимается после успешно сыгранной (без лива) ливером игры
#self.SUB_LEAVE_POINT = 3

#Количество очков набранных в играх c ливом игрока, чтобы стать ливером, а не обычным игроком
#self.LEAVES_POINT = 12

#Количество очков лива, которое добавляется когда игрок получил 2 репорта о неспортивном поведении от игроков своей команды и статус 'Зона риска'
self.POINTS_PER_BAD_BEHAIVIOR_REPORTS = 6

#Включение/Отключение учета очков лива за плохое поведение в игре
self.BEHAVIOUR_DETECTED_ENABLE = True

self.WEB_IM_WEBSITE_URL = "https://primearena.net/"

self.GUILD_MAX_VASSAL_SIZE = 5

#Время, в течение которого клан не может отбить вассала
self.SiegeSettings.TIMEOUT_FOR_EX_VASSAL_CAPTURE = 7 * 24 * 60 * 60;
#Время, в течение которого клан не может захватывать клан, проигранный в недавней осаде
self.SiegeSettings.TIMEOUT_FOR_CAPTURE_AFTER_LOSS = 1 * 24 * 60 * 60;

#Список турнирных карт
self.TournamentSettings.TOURNAMENT_MAP_LIST.append("/Maps/Multiplayer/MOBA/Mod5/_.ADMPDSCR")
self.TournamentSettings.TOURNAMENT_MAP_LIST.append("/Maps/Multiplayer/MOBA/Mod7/_.ADMPDSCR")
self.TournamentSettings.TOURNAMENT_MAP_LIST.append("/Maps/Multiplayer/MOBA/Mod8/_.ADMPDSCR")

#Кол-во сообщений администрации
self.ADMIN_MESSAGES_TO_STORE = 10

#С какого уровня можно вешать красные таланты
self.REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS = 15
#С какого уровня можно вешать оранжевые таланты
self.REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS = 0


self.overrideData( "/UI/Content/MarketingEvents/PremiumAcc::imageA", "http://ru.playpw.com/images/hardcode/pw_ga_ingame_new.png" )
self.overrideData( "/UI/Content/MarketingEvents/PremiumAcc::imageB", "http://ru.playpw.com/images/hardcode/pw_ga_ingame_new.png" )

#Стоимость заточки классовых талантов
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[0].levelToPoints.Item.[0]", "7" )
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[0].levelToPoints.Item.[1]", "22" )
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[0].levelToPoints.Item.[2]", "52" )
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[0].levelToPoints.Item.[3]", "111" )

#Баннер ярмарки
self.EventToolsChangeFields.RerollShopBanner.BANNER_URL = "http://ru.playpw.com/images/2016/pw_market_banner4.png"

#Размер одной страницы с друзьями(по умолчанию размер страницы 15).
self.FRIENDS_PAGE_SIZE = 30

#Продолжительность мьюта системой автомьюта в секундах
self.AUTOMUTE_DURATION = 24 * 60;

#Количество попыток неправильного ввода необходимых для включения капчи
self.BruteForceDefenderSettings.FAILED_COUNT_FOR_CAPTCHA = 5;

##Во сколько раз уменьшается цена в серебре, чтобы получить цену в золоте (от этого значение еще -1)
self.BuyGoldHeroInfo.DISCOUNT_COEFFICIENT = 2500

##лимит на добавление поинтов guild wars за раз
self.GWPOINTSTOADDLIMIT = 20

# фиксы перехода из сессии в замок на клиенте (https://devjira.nivalnetwork.com/browse/PF-97057)
# коректная блокировка Unity на время боя # по умолчанию True
#self.SESSION_TO_CASTLE_FIX_1 = False
# вырубаем сеть и Flash на время боя # по умолчанию True
#self.SESSION_TO_CASTLE_FIX_2 = False
