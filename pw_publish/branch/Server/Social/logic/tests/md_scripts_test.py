# -*- coding: utf-8 -*-
import sys, math
import time
sys.path.append('../')
from binascii import crc32
sys.path.append('../..')
from enums import *

sys.path.append('../../modeldata/Scripts')
from AddIsRegularMMAllowedFlag import *
from ReplaceTutorialQuestsAndAwards import *
from ShowCorrectGoldHouseActionState import *
from ReplaceTutorialQuests2_0 import *
from ResetBuyHeroEventNewState import *
from SetLastRankedGameTime import *
from DelevelTransmutation import DelevelTransmutation, getBuildingPrice, getProductionCost
from RemoveExtraProductionHouses import *
from AddRerollShopProbabilities import *
from ChangeRerollShopProbabilities import *
from GiveBackTalentsForClassRefinement import *
from RecountGreenTalents import *
from ModifyTradeEventProgression import *
from FixCrusaderClassTalents import *
from MM import ESex
from GiveSomeTalents import *
from RemoveDuplicatedClassTalents import *
from ClearExtraTalents import *
addModPath("../thrift_pw/account_management/gen-py")
from AccountManagementAPI.ttypes import ConfigEventType
from RemoveCustomCurrenciesForFirstTradeEvent import *

class md_scripts_test:

    def Delevel_transmutation_building_test(self, env):
        modeldata = env.acc.model
        persistentId = crc32("Talent_Production")

        # Основная кузница, она и должна остаться, её уровень надо скинуть до 1 и вернуть все ресы за строительство
        construction1_uid = modeldata.addNewConstruction()
        construction1 = modeldata.getConstructionByID( construction1_uid )
        construction1.PersistentId = persistentId
        construction1.Level = 15
        modeldata.Buildings.add(construction1_uid)
        price1 = getBuildingPrice(construction1.Level, 1) # здание будет понижено в уровне до 0
        warn("Up level to %s prise: %r", construction1.Level, price1)

        # Проверим, что за кузницу, которая завершила производство, выдадут ресурсы
        construction2_uid = modeldata.addNewConstruction()
        construction2 = modeldata.getConstructionByID( construction2_uid )
        construction2.PersistentId = persistentId
        construction2.Level = 5
        construction2.ProductionLevel = construction2.Level
        construction2.ProductionState = ProductionState.Finished
        construction2.ProductionCustomValue = 1
        modeldata.Buildings.add(construction2_uid)
        price2 = getBuildingPrice(construction2.Level)
        cyclePrice2 = getProductionCost( env.acc, construction2.Level, None, construction2.ProductionCustomValue )

        # Проверим, что кузница из хранилища тоже правильно обработается
        construction3_uid = modeldata.addNewConstruction()
        construction3 = modeldata.getConstructionByID( construction3_uid )
        construction3.PersistentId = persistentId
        construction3.Level = 5
        modeldata.Pocket.add(construction3_uid)
        price3 = getBuildingPrice(construction3.Level)

        # Проверим, что за кузницу, которая работает, выдадут ресурсы
        construction4_uid = modeldata.addNewConstruction()
        construction4 = modeldata.getConstructionByID( construction4_uid )
        construction4.PersistentId = persistentId
        construction4.Level = 10
        construction4.ProductionLevel = construction4.Level
        construction4.ProductionState = ProductionState.Busy
        construction4.ProductionCustomValue = 2
        modeldata.Buildings.add(construction4_uid)
        price4 = getBuildingPrice(construction4.Level)
        cyclePrice4 = getProductionCost(env.acc, construction4.Level, None, construction4.ProductionCustomValue)

        resource1_old = modeldata.Resources.Resource1
        resource2_old = modeldata.Resources.Resource2
        resource3_old = modeldata.Resources.Resource3
        population = modeldata.Resources.Population
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        assert len(modeldata.Buildings) == 3
        assert len(modeldata.Pocket) == 1

        script = DelevelTransmutation()
        md = script.convertModelData(env, env.acc, env.acc.model, None)

        assert len(modeldata.Buildings) == 1
        assert len(modeldata.Pocket) == 0

        construction = modeldata.getConstructionByID(construction1_uid)
        assert construction != None
        assert construction.Level == 0
        assert modeldata.Resources.Resource1 == resource1_old + price1.Resource1 + price2.Resource1 + price3.Resource1 + price4.Resource1
        assert modeldata.Resources.Resource2 == resource2_old + price1.Resource2 + price2.Resource2 + price3.Resource2 + price4.Resource2
        assert modeldata.Resources.Resource3 == resource3_old + price1.Resource3 + price2.Resource3 + price3.Resource3 + price4.Resource3
        assert modeldata.Resources.Population == population + price1.Population + price2.Population + price3.Population + price4.Population
        assert modeldata.Resources.Silver == silver + cyclePrice4.Silver + cyclePrice2.Silver
        assert modeldata.Resources.Perl == perl + cyclePrice4.Perl + cyclePrice2.Perl


    def AddIsRegularMMAllowedFlag_test( self, env ):

        assert env.acc.db.isRegularMMAllowed == None

        script = AddIsRegularMMAllowedFlag()
        md = script.convertModelData( env, env.acc, env.acc.model, env.I )

        assert env.acc.db.isRegularMMAllowed == True

    def ReplaceTutorialQuestsAndAwardds_test( self, env ):
        modeldata = env.acc.model
        config = env.I.Config.getConfig( env.acc.userlocale )

        staticQuest = env.acc.SD.getStaticQuestById( crc32("c24_qA") )
        quest = modeldata.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, env.acc )
        modeldata.CompletedQuests.add(quest)

        quest_id = modeldata.addNewQuest()
        quest = modeldata.getQuestByID( quest_id )
        quest.state = QuestState.New
        quest.dialogPage = 0
        quest.persistentId = crc32("s31_qA")
        quest.isVisible = True
        modeldata.ActiveQuests.add(quest)

        assert len(modeldata.CompletedQuests) == 2

        staticQuest = env.acc.SD.getStaticQuestById( crc32("c21_qA") )
        quest = modeldata.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, env.acc )
        quest.state = QuestState.InProgress
        modeldata.ActiveQuests.add(quest)

        script = ReplaceTutorialQuestsAndAwards()
        md = script.convertModelData( env, env.acc, env.acc.model, env.I )

        c21Found = False
        n11Found = False
        for questId in modeldata.ActiveQuests:
            quest = modeldata.getQuestByID(questId)
            if quest.persistentId == crc32("c21_qA"):
                assert quest.state == QuestState.New
                c21Found = True
            if quest.persistentId == crc32("n11_qA"):
                n11Found = True

        assert c21Found == True
        assert n11Found == True


    def ShowCorrectGoldHouseActionState_test_all_heroes_already_bought(self, env):
        modeldata = env.acc.model
        config = env.I.Config.getConfig( env.acc.userlocale )

        for static_hero_id in env.acc.SD.data['Heroes']:
            static_hero = env.acc.SD.data['Heroes'][static_hero_id]
            if env.acc.sex == ESex.FEMALE:
                price = env.acc.SD.copyPrice(static_hero['lobbyData']['CostFemale'])
            else:
                price = env.acc.SD.copyPrice(static_hero['lobbyData']['CostMale'])
            if price.Silver <= config.BUY_HERO_MAX_ORIGINAL_PRICE:
                hero = env.add_hero(modeldata, static_hero['persistentId'])

        script = ShowCorrectGoldHouseActionState()

        md = script.convertModelData( env, env.acc, env.acc.model, None )

        assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowBuyHouseEvent


    def ShowCorrectGoldHouseActionState_test_buy_hero_complete(self, env):
        modeldata = env.acc.model
        config = env.I.Config.getConfig( env.acc.userlocale )

        constructions = len(modeldata.ConstructionsKeeper)
        modeldata.MarketingEventsInfo.IsBuyHeroComplete = True
        script = ShowCorrectGoldHouseActionState()

        md = script.convertModelData( env, env.acc, env.acc.model, None )

        assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowPlaceHouseEvent
        assert len(modeldata.ConstructionsKeeper) == constructions + 1


    def ShowCorrectGoldHouseActionState_test_buy_hero_is_not_complete(self, env):
        modeldata = env.acc.model
        config = env.I.Config.getConfig( env.acc.userlocale )

        constructions = len(modeldata.ConstructionsKeeper)
        modeldata.MarketingEventsInfo.IsBuyHeroComplete = False
        script = ShowCorrectGoldHouseActionState()

        md = script.convertModelData( env, env.acc, env.acc.model, None )

        assert modeldata.MarketingEventsInfo.GoldHouseActionState == GoldHouseActionState.ShowBuyHeroEvent
        assert len(modeldata.ConstructionsKeeper) == constructions


    def ReplaceTutorialQuests2_0_test(self, env):
        modeldata = env.acc.model
        config = env.I.Config.getConfig( env.acc.userlocale )

        staticQuest = env.acc.SD.getStaticQuestById( crc32("n11_qA") )
        quest = modeldata.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, env.acc )
        modeldata.CompletedQuests.add(quest)
        modeldata.ActiveQuests.remove(quest)

        staticQuest = env.acc.SD.getStaticQuestById( crc32("c24_qA") )
        quest = modeldata.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, env.acc )
        modeldata.CompletedQuests.add(quest)
        modeldata.ActiveQuests.remove(quest)

        staticQuest = env.acc.SD.getStaticQuestById( crc32("c21_qA") )
        quest = modeldata.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, env.acc )
        modeldata.ActiveQuests.add(quest)

        modeldata.LordInfo.MapsByType[MapType.PVE].Enabled = False
        modeldata.LordInfo.MapsByType[MapType.PVE].MapId = "Some_map_id"

        assert len(modeldata.CompletedQuests) == 3
        assert len(modeldata.ActiveQuests) == 2

        script = ReplaceTutorialQuests2_0()
        md = script.convertModelData( env, env.acc, env.acc.model, env.I )

        assert len(modeldata.CompletedQuests) == 0
        assert len(modeldata.ActiveQuests) == 5
        assert modeldata.LordInfo.MapsByType[MapType.PVE].Enabled == True
        assert modeldata.LordInfo.MapsByType[MapType.PVE].MapId == env.acc.SD.data['DefaultMaps']['Item'][MapType.PVE]['group']['dbid']


    def ResetBuyHeroEventNewState(self, env):
        modeldata = env.acc.model
        config = env.I.Config.getConfig( env.acc.userlocale )
        dbId = "/UI/Content/MarketingEvents/BuyHero"
        if dbId not in modeldata.MarketingEventsInfo.ViewedEvents:
            modeldata.MarketingEventsInfo.ViewedEvents.append(dbId)

        assert dbId in modeldata.MarketingEventsInfo.ViewedEvents

        script = ResetBuyHeroEventNewState()

        md = script.convertModelData( env, env.acc, env.acc.model, env.I )

        assert dbId not in modeldata.MarketingEventsInfo.ViewedEvents

    def SetLastRankedGameTime_test(self, env):
        modeldata = env.acc.model
        heroId = modeldata.addNewHero()
        hero = modeldata.getHeroByID(heroId)
        hero.lastPlayed = int(time.time())
        hero.PersistentId = crc32("witcher")
        modeldata.Heroes.add(hero)
        modeldata.LordInfo.LastRankedGameTime = 0

        assert hero.lastPlayed > modeldata.LordInfo.LastRankedGameTime

        script = SetLastRankedGameTime()

        md = script.convertModelData( env, env.acc, env.acc.model, env.I )

        assert modeldata.LordInfo.LastRankedGameTime == hero.lastPlayed

    def RemoveExtraProductionHousesTest(self, env):
        modeldata = env.acc.model
        config = env.I.Config.getConfig( env.acc.userlocale )

        persistentId = crc32("House_4")
        strId = "House_4"
        script = RemoveExtraProductionHouses()
        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(persistentId)

        # Основная кристалльня, она и должна остаться, её уровень надо скинуть до 1 и вернуть все ресы за строительство
        construction1_uid = modeldata.addNewConstruction()
        construction1 = modeldata.getConstructionByID(construction1_uid)
        construction1.PersistentId = persistentId
        construction1.Level = 15
        modeldata.Buildings.add(construction1_uid)
        price1 = script.getBuildingPrice(strId, construction1.Level, 1) # здание будет понижено в уровне до 0
        warn("Up level to %s price: %r", construction1.Level, price1)

        # Проверим, что за кристалльню, которая завершила производство, выдадут ресурсы
        construction2_uid = modeldata.addNewConstruction()
        construction2 = modeldata.getConstructionByID( construction2_uid )
        construction2.PersistentId = persistentId
        construction2.Level = 5
        construction2.ProductionLevel = construction2.Level
        construction2.ProductionState = ProductionState.Finished
        construction2.ProductionCustomValue = 8
        construction2.cycle = 0
        modeldata.Buildings.add(construction2_uid)
        price2 = script.getBuildingPrice(strId, construction2.Level)
        #cyclePrice2 = script.getProductionCost(env.acc, construction2, staticConstruction, construction2.ProductionCustomValue)

        # Проверим, что кузница из хранилища тоже правильно обработается
        construction3_uid = modeldata.addNewConstruction()
        construction3 = modeldata.getConstructionByID( construction3_uid )
        construction3.PersistentId = persistentId
        construction3.Level = 5
        modeldata.Pocket.add(construction3_uid)
        price3 = script.getBuildingPrice(strId, construction3.Level)

        # Проверим, что за кузницу, которая работает, выдадут ресурсы
        construction4_uid = modeldata.addNewConstruction()
        construction4 = modeldata.getConstructionByID( construction4_uid )
        construction4.PersistentId = persistentId
        construction4.Level = 10
        construction4.ProductionLevel = construction4.Level
        construction4.ProductionState = ProductionState.Busy
        construction4.ProductionCustomValue = 8
        construction2.cycle = 3
        modeldata.Buildings.add(construction4_uid)
        price4 = script.getBuildingPrice(strId, construction4.Level)
        #cyclePrice4 = script.getProductionCost(env.acc, construction4, staticConstruction, construction4.ProductionCustomValue)

        resource1_old = modeldata.Resources.Resource1
        resource2_old = modeldata.Resources.Resource2
        resource3_old = modeldata.Resources.Resource3
        population = modeldata.Resources.Population
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        assert len(modeldata.Buildings) == 3
        assert len(modeldata.Pocket) == 1

        md = script.convertModelData(env, env.acc, env.acc.model, env.I)

        assert len(modeldata.Buildings) == 1
        assert len(modeldata.Pocket) == 0

        construction = modeldata.getConstructionByID(construction1_uid)
        assert construction != None
        assert construction.Level > 15
        assert modeldata.Resources.Resource1 > resource1_old
        assert modeldata.Resources.Resource2 == resource2_old
        assert modeldata.Resources.Resource3 > resource3_old
        assert modeldata.Resources.Population == population
        assert modeldata.Resources.Silver > silver
        assert modeldata.Resources.Perl == perl

    def AddCastleRoll_test( self, env ):

        script = AddRerollShopProbabilities()
        md = script.convertModelData( env, env.acc, env.acc.model, env.I )

        assert len(env.acc.db.castle_roll) == 3

    def GiveBackTalentsForClassRefinement_test(self, env):
        modeldata = env.acc.model
        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID( heroId )
            break

        fullTalent = None
        mediumTalent = None
        smallTalent = None
        oneStarTalent = None
        for talId in hero.TalentSets[0].Talents.keys():
            talentId = hero.TalentSets[0].Talents.get(talId)
            talent = modeldata.getTalentByID(talentId)
            staticTalent = env.acc.SD.getStaticTalent(talent)
            if staticTalent and staticTalent['rarity'] == "Class":
                if fullTalent is None:
                    fullTalent = talent
                elif mediumTalent is None:
                    mediumTalent = talent
                elif oneStarTalent is None:
                    oneStarTalent = talent
                elif smallTalent is None:
                    smallTalent = talent
                else:
                    break
        fullTalent.Points = 1668
        mediumTalent.Points = 556
        oneStarTalent.Points = 111
        smallTalent.Points = 50
        talentsBefore = len(modeldata.UserInventory)

        script = GiveBackTalentsForClassRefinement()
        md = script.convertModelData( env, env.acc, env.acc.model, env.I )
        return
        assert fullTalent.Points == 111
        assert mediumTalent.Points == 37
        assert oneStarTalent.Points == 7
        assert smallTalent.Points == 3
        assert talentsBefore == len(modeldata.UserInventory) - int(math.ceil((1668 + 556 + 111 + 50)/110.0))

    def ChangeCastleRoll_test( self, env ):

        script = ChangeRerollShopProbabilities()
        md = script.convertModelData( env, env.acc, env.acc.model, env.I )

        assert len(env.acc.db.castle_roll) == 3

    def RecountGreenTalents_test(self, env):
        modeldata = env.acc.model
        persistentId = crc32("G058")

        fullTalent_uid = modeldata.addNewTalent()
        fullTalent = modeldata.getTalentByID( fullTalent_uid )
        fullTalent.PersistentId = persistentId
        fullTalent.Points = 445
        modeldata.UserInventory.add(fullTalent_uid)

        mediumTalent_uid = modeldata.addNewTalent()
        mediumTalent = modeldata.getTalentByID( mediumTalent_uid )
        mediumTalent.PersistentId = persistentId
        mediumTalent.Points = 100
        modeldata.UserInventory.add(mediumTalent_uid)

        smallTalent_uid = modeldata.addNewTalent()
        smallTalent = modeldata.getTalentByID( smallTalent_uid )
        smallTalent.PersistentId = persistentId
        smallTalent.Points = 15
        modeldata.UserInventory.add(smallTalent_uid)

        oneStarTalent_uid = modeldata.addNewTalent()
        oneStarTalent = modeldata.getTalentByID( oneStarTalent_uid )
        oneStarTalent.PersistentId = persistentId
        oneStarTalent.Points = 30
        modeldata.UserInventory.add(oneStarTalent_uid)

        script = RecountGreenTalents()
        md = script.convertModelData( env, env.acc, env.acc.model, env.I )

        assert fullTalent.Points == 778
        assert mediumTalent.Points > 156 and mediumTalent.Points < 200
        assert oneStarTalent.Points == 52
        assert smallTalent.Points == 26

    def modify_trade_event_progression_test(self, env):
        model_data = env.acc.model

        progr, _ = model_data.newTradeEventProgression()
        progr.PersistentId = 9
        model_data.TradeEvents.add(9, progr)

        script = ModifyTradeEventProgression()

        md = script.convertModelData(env, env.acc, env.acc.model, env.I)

        assert 9 not in model_data.TradeEvents
        assert 1 in model_data.TradeEvents
        afterProgr = model_data.TradeEvents[1]
        env.printAssert(afterProgr.PersistentId, 1)

    def fix_crusader_class_talents_test(self, env):
        model_data = env.acc.model

        env.acc.db.fraction = 'B'
        model_data.hireHero(crc32('crusader_B'), 0, env.I.WS, env.acc, env.I)
        hero, heroId = model_data.findHeroByCrc32(crc32("crusader_B"))

        assert hero

        script = FixCrusaderClassTalents()
        md = script.convertModelData(env, env.acc, env.acc.model, env.I)

        for _, ts in hero.TalentSets.iteritems():
            env.printAssert(ts.TalentSetCrc, -1)

    def clear_extratalents_talents_test(self, env):
        # todo: где ассерты?
        model_data = env.acc.model

        for i in range(50000):
            talent = model_data.addTalent(crc32('G662'))
            talentPointsToLevel = env.acc.SD.getTalentPointsToLevel(env.acc.SD.getStaticTalent(talent))
            talent.Points = talentPointsToLevel[random.randint(2, 6) - 2]

        beforeTalentCount = 0
        for _, talent in model_data.UserInventory.iteritems():
            if env.acc.SD.getStaticTalent(talent)['persistentId'] == 'G662':
                beforeTalentCount += 1

        script = ClearExtraTalents()
        md = script.convertModelData(env, env.acc, env.acc.model, env.I)

        afterTalentCount = 0
        for _, talent in model_data.UserInventory.iteritems():
            if env.acc.SD.getStaticTalent(talent)['persistentId'] == 'G662':
                afterTalentCount += 1

        env.printAssert(afterTalentCount, 0)

    def checkFixGiveSomeTalents(self, env):
        fix = GiveSomeTalents()

        # 0 - запуск в холостую (на новом профайле)
        _befor = len(env.acc.model.UserInventory)
        fix.convertModelData(None, env.acc, env.acc.model, None)
        assert len(env.acc.model.UserInventory) == _befor

        hero = next(h for h in env.acc.model.Heroes.values() if h.PersistentId == crc32('firefox'))
        classTalent = next(t for t in env.acc.model.UserInventory.values() if t.PersistentId == crc32('Firefox_A1'))
        orangeTalent = next(t for t in env.acc.model.UserInventory.values() if t.PersistentId == crc32('G435'))

        # 1 - удаляем классовый, проверяем, что фикс восстанавливает
        env.acc.model.UserInventory.remove(classTalent)
        fix.convertModelData(None, env.acc, env.acc.model, None)
        assert len(env.acc.model.UserInventory) == _befor

        # 2 - удаляем рыжий, проверяем, что фикс восстанавливает
        env.acc.model.UserInventory.remove(orangeTalent)
        fix.convertModelData(None, env.acc, env.acc.model, None)
        assert len(env.acc.model.UserInventory) == _befor

    def checkRemoveDuplicatedClassTalents(self, env):
        fix = RemoveDuplicatedClassTalents()

        hero = next(h for h in env.acc.model.Heroes.values() if h.PersistentId == crc32('firefox'))
        tId = hero.TalentSets[0].Talents.get(1)
        talent = env.acc.model.getTalentByID(tId)

        # 0 - прогоняем на валидном герое - проверяем, что фикс ничего не ломает
        _befor = len(env.acc.model.UserInventory)
        fix.convertModelData(env, env.acc, env.acc.model, None)
        assert len(env.acc.model.UserInventory) == _befor

        # 1 - дубликат в инвентаре
        createdTalent = env.add_talent(env.acc.model, "Firefox_A1")
        env.acc.model.UserInventory.add(createdTalent)
        fix.convertModelData(env, env.acc, env.acc.model, None)
        assert len(env.acc.model.UserInventory) == _befor
        assert createdTalent.id not in env.acc.model.UserInventory
        assert talent.id in env.acc.model.UserInventory

        # 2 - дубликат в инвентаре (лучше, чем в талантсете)
        createdTalent = env.add_talent(env.acc.model, "Firefox_A1")
        env.acc.model.UserInventory.add(createdTalent)
        createdTalent.Points = 100500
        fix.convertModelData(env, env.acc, env.acc.model, None)
        assert len(env.acc.model.UserInventory) == _befor
        assert createdTalent.id in env.acc.model.UserInventory
        assert talent.id not in env.acc.model.UserInventory

    def check_cc_from_first_trade_event_1(self, env):
        modeldata = env.acc.model

        if 'finishedEvents' not in env.I.WS.operatorEvents:
            env.I.WS.operatorEvents['finishedEvents'] = {}

        modeldata.Resources.Currencies[RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[0]] = 123
        modeldata.Resources.Currencies[RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[1]] = 123
        modeldata.Resources.Currencies[RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[5]] = 123

        script = RemoveCustomCurrenciesForFirstTradeEvent()
        md = script.convertModelData(env, env.acc, env.acc.model, env.I)

        assert RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[0] not in modeldata.Resources.Currencies
        assert RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[1] not in modeldata.Resources.Currencies
        assert RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[5] not in modeldata.Resources.Currencies

    def check_cc_from_first_trade_event_2(self, env):
        modeldata = env.acc.model

        local = modeldata.getUserLocale(env.acc)
        event_data = dict(startTime=0, endTime=1,
                               persistentId=100500,
                               enabled=True, type=ConfigEventType.TradeEvent,
                               newValue=dict(local=local, guid=RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_GUID),
                               defaultValue={}, description='')
        if 'finishedEvents' not in env.I.WS.operatorEvents:
            env.I.WS.operatorEvents['finishedEvents'] = {}
        env.I.WS.operatorEvents['finishedEvents'][event_data['persistentId']] = event_data

        event_progr, _ = modeldata.newTradeEventProgression()
        event_progr.PersistentId = event_data['newValue']['guid']
        modeldata.TradeEvents.add(event_data['newValue']['guid'], event_progr)

        modeldata.Resources.Currencies[RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[0]] = 123
        modeldata.Resources.Currencies[RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[1]] = 123
        modeldata.Resources.Currencies[RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[5]] = 123

        script = RemoveCustomCurrenciesForFirstTradeEvent()
        md = script.convertModelData(env, env.acc, env.acc.model, env.I)

        assert RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[0] in modeldata.Resources.Currencies
        assert RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[1] in modeldata.Resources.Currencies
        assert RemoveCustomCurrenciesForFirstTradeEvent.FIRST_TRADE_EVENT_CURRENCIES[5] in modeldata.Resources.Currencies

        del env.I.WS.operatorEvents['finishedEvents'][event_data['persistentId']]
        modeldata.TradeEvents.remove(event_data['newValue']['guid'])
