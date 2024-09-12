import sys

sys.path.append('../')
from logic.hire_hero import *
from logic.building_place import *
from binascii import crc32

sys.path.append('../..')
from enums import *


class hire_hero_test:
    def hire_hero_test(self, env):
        modeldata = env.acc.model

        heroCount = len(modeldata.Heroes)
        persistentId = "zealot"

        fame = 80000
        silver = 1000000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32(persistentId)]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.HeroesKeeper) == heroCount + 1
        assert len(modeldata.Heroes) == heroCount + 1
        static_hero = env.acc.SD.getStaticHeroByClassId(crc32(persistentId))
        cost = static_hero['lobbyData']['CostMale']
        fameInc = static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][0]
        assert silver - modeldata.Resources.Silver == cost['Silver']
        assert modeldata.LordInfo.Fame - fame == fameInc

    def hire_hero_wrong_fraction_test(self, env):
        # No more wrong fractions
        return
        env.acc.db.fraction = 'B'
        modeldata = env.acc.model

        heroesCount = len(modeldata.Heroes)
        persistentId = "alchemist"

        fame = 8000000
        silver = 8000000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32(persistentId)]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.HeroesKeeper) == heroesCount
        assert len(modeldata.Heroes) == heroesCount

    def hire_hero_wrong_fraction2_test(self, env):
        # No more wrong fractions
        return
        env.acc.db.fraction = 'A'
        modeldata = env.acc.model

        heroesCount = len(modeldata.Heroes)
        persistentId = "artist"

        fame = 8000000
        silver = 8000000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32(persistentId)]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.HeroesKeeper) == heroesCount
        assert len(modeldata.Heroes) == heroesCount

    def hire_hired_hero_test(self, env):
        modeldata = env.acc.model

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.Hired == True:
                hero = hero
                break

        heroesCount = len(modeldata.HeroesKeeper)

        fame = 80000
        silver = 5000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [
            (Hire_hero, HireHeroRequest(modeldata, {"PersistentId": ["" + str(hero.PersistentId) + ""]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.Heroes) == heroesCount
        assert len(modeldata.HeroesKeeper) == heroesCount

    def hire_hero_rating_test_1(self, env):
        modeldata = env.acc.model

        assert len(modeldata.HeroesKeeper) == 5
        assert len(modeldata.Heroes) == 5

        fame = 80000
        silver = 5000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("rockman")]}, False))]
        changeList = env.execActions(requests)

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.PersistentId == crc32("rockman"):
                found = hero

        assert found
        assert found.Rating == env.I.Config.getConfig(env.acc.userlocale).HERO_START_RATING

    def hire_hero_rating_test_2(self, env):
        modeldata = env.acc.model

        assert len(modeldata.HeroesKeeper) == 5
        assert len(modeldata.Heroes) == 5

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.Hired:
                hero.Rating = 100500
                break

        fame = 80000
        silver = 5000000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("frogenglut")]}, False))]
        changeList = env.execActions(requests)

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.PersistentId == crc32("frogenglut"):
                found = hero

        assert found
        assert found.Rating == env.I.Config.getConfig(env.acc.userlocale).HERO_CUP_RATING

    def hire_hero_firstbuy_test(self, env):
        modeldata = env.acc.model
        buildCount = len(modeldata.Buildings)
        modeldata.LordInfo.Fame = 100000
        modeldata.Resources = env.generate_resources(2000000)

        construction_id = modeldata.addNewConstruction()
        construction = modeldata.getConstructionByID(construction_id)
        construction.PersistentId = crc32("FirstBuy_Cat")
        construction.Position.X = 22
        construction.Position.Y = 35
        construction.Position.Pitch = 0
        modeldata.Buildings.add(construction_id)

        assert len(modeldata.Pocket) == 0
        assert len(modeldata.Buildings) == buildCount + 1

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("frogenglut")]}, False))]
        changeList = env.execActions(requests)

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.PersistentId == crc32("frogenglut"):
                found = hero
        assert found.Experience == env.acc.SD.data['FirstBuyHeroExpBonus']
        assert found.FirstBuyApplied == True

    def hire_hero_firstbuy_test2(self, env):
        modeldata = env.acc.model
        buildCount = len(modeldata.Buildings)

        construction_id = modeldata.addNewConstruction()
        construction = modeldata.getConstructionByID(construction_id)
        construction.PersistentId = crc32("FirstBuy_Cat")
        X = 22
        Y = 35
        Pitch = 0
        modeldata.Pocket.add(construction_id)

        modeldata.LordInfo.Fame = 100000
        modeldata.Resources = env.generate_resources(2000000)

        assert len(modeldata.Pocket) == 1
        assert len(modeldata.Buildings) == buildCount

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("frogenglut")]}, False))]
        changeList = env.execActions(requests)

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.PersistentId == crc32("frogenglut"):
                found = hero
        assert found.Experience == env.acc.SD.data['FirstBuyHeroExpBonus']
        assert found.FirstBuyApplied == True

    def hire_hero_firstbuy_test3(self, env):
        modeldata = env.acc.model
        buildCount = len(modeldata.Buildings)

        modeldata.LordInfo.LevelOfExpansion = 1
        modeldata.Resources = env.generate_resources(2000)
        assert len(modeldata.Buildings) == buildCount

        heroCount = len(modeldata.Heroes)

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.FirstBuyApplied != True:
                hero.FirstBuyApplied = True
                heroWithoutBonus = hero
                break

        plan_id = crc32("FirstBuy_Cat");
        x = 100500
        y = 100500
        pitch = 0

        modeldata.LordInfo.Fame = 100000

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("rockman")]}, False)), (
        Building_place, BuildingPlaceRequest(modeldata,
                                             {"PersistentId": ["" + str(plan_id) + ""], "x": ["" + str(x) + ""],
                                              "y": ["" + str(y) + ""], "pitch": ["" + str(pitch) + ""]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.Pocket) == 0
        assert len(modeldata.Buildings) == buildCount + 1
        assert len(modeldata.HeroesKeeper) == heroCount + 1
        assert len(modeldata.Heroes) == heroCount + 1

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.PersistentId == crc32("rockman"):
                found = hero
        assert found
        assert found.Experience == env.acc.SD.data['FirstBuyHeroExpBonus']
        assert found.FirstBuyApplied == True
        assert heroWithoutBonus.Experience == 0

    def hire_hero_heroesbuilding_test(self, env):
        modeldata = env.acc.model
        buildCount = len(modeldata.Buildings)

        modeldata.LordInfo.Fame = 100000
        modeldata.Resources = env.generate_resources(1000000)

        construction_id = modeldata.addNewConstruction()
        construction = modeldata.getConstructionByID(construction_id)
        construction.PersistentId = crc32("BuffHouse_2")
        construction.Position.X = 22
        construction.Position.Y = 35
        construction.Position.Pitch = 0
        modeldata.Buildings.add(construction_id)

        assert len(modeldata.Pocket) == 0
        assert len(modeldata.Buildings) == buildCount + 1

        hero_class_id = "rockman"
        oldSilver = modeldata.Resources.Silver
        staticHero = env.acc.SD.getStaticHeroByClassId(crc32(hero_class_id))

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32(hero_class_id)]}, False))]
        changeList = env.execActions(requests)

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.PersistentId == crc32(hero_class_id):
                found = hero
        assert found

        staticBuilding = env.acc.SD.getStaticConstruction(construction)
        discount = env.acc.SD.getFloatInterpolated(staticBuilding['HeroesBuildingLevels'], construction.Level, None,
                                                   "discount", 0)
        must_be_payed = oldSilver - (staticHero['lobbyData']['CostMale']['Silver'] - env.acc.SD.roundFloatToInt(
            staticHero['lobbyData']['CostMale']['Silver'] * discount / 100.0))
        assert must_be_payed == modeldata.Resources.Silver

    def hire_hero_version_test(self, env):
        modeldata = env.acc.model
        hero_class_id = "mage"
        staticHero = env.acc.SD.getStaticHeroByClassId(crc32(hero_class_id))
        version = 10
        staticHero['lobbyData']['Version'] = version

        modeldata.LordInfo.Fame = 100000
        modeldata.Resources = env.generate_resources(2000000)

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32(hero_class_id)]}, False))]
        changeList = env.execActions(requests)

        assert staticHero['lobbyData']['Version'] == version

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.PersistentId == crc32(hero_class_id):
                found = hero

        assert found
        assert found.Version == version

    def hire_hero_with_guild_bonus_points_test(self, env):
        modeldata = env.acc.model

        heroCount = len(modeldata.Heroes)
        persistentId = "rockman"

        fame = 80000
        silver = 5000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        guildPoints = 5
        construction = env.add_construction(modeldata, "Guild")
        construction.Level = 1
        tmpGuildLevel = env.acc.SD.data['GuildLevels']['levels']['Item'][1].copy()

        env.acc.SD.data['GuildLevels']['levels']['Item'][1]['Bonuses'] = {
            'Item': [{'MasterPoints': guildPoints, 'classType': 'GuildStatsBonus'}]}

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32(persistentId)]}, False))]
        changeList = env.execActions(requests)

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            if hero.PersistentId == crc32(persistentId):
                found = hero

        assert found
        assert found.TalentSets[0].GuildStats.StatPoints == guildPoints

        env.acc.SD.data['GuildLevels']['levels']['Item'][1] = tmpGuildLevel.copy()

    def hire_hero_for_prince_test(self, env):
        modeldata = env.acc.model

        heroCount = len(modeldata.Heroes)
        persistentId = "naga"

        fame = 80000
        silver = 35000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32(persistentId)]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.HeroesKeeper) == heroCount + 1
        assert len(modeldata.Heroes) == heroCount + 1
        static_hero = env.acc.SD.getStaticHeroByClassId(crc32(persistentId))
        cost = static_hero['lobbyData']['CostMale']
        fameInc = static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][0]
        assert silver - modeldata.Resources.Silver == cost['Silver']
        assert modeldata.LordInfo.Fame - fame == fameInc


    def hire_hero_cheat_test(self, env):
        modeldata = env.acc.model

        heroCount = len(modeldata.Heroes)
        persistentId = "prince"
        fame = 80000
        silver = 5000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver
        modeldata.Resources.Gold =0

        static_hero = env.acc.SD.getStaticHeroByClassId(crc32(persistentId))
        cost = static_hero['lobbyData']['CostMale']
        oldSilverCost = cost['Silver']
        cost['Silver'] = 0
        #oldGoldCost = cost['Gold']
        #cost['Gold'] = 10
        obj = {
            "_id" : 5,
            "customData" : {
                "heroes" : [
                    {
                        "silverPrice" : 0,
                        "persistentId" : "prince",
                        "goldPrice" : 10
                    }
                ]
            },
            "description" : "Prince",
            "enabled" : True,
            "endTime" : time.time() + 10000000,
            "startTime" : time.time() - 100000,
            "type" : 6
        }


        try:
            event = {"endTime": obj["endTime"], "persistentId": obj["_id"],
                     "startTime": obj["startTime"],
                     "enabled": obj["enabled"], "type": obj["type"],
                     "newValue": obj["customData"], "defaultValue": {}}
            if event["enabled"] and event["startTime"] < int(time.time()) < event["endTime"]:
                info("Loading event %r", event)
                changes, self.needUpdateSeeds = env.I.Config.applyEvent(env.I.SD, event)
        except Exception:
            catch()

        time.sleep(1.0)

        #modeldata.Resources.Gold = cost['Gold']
        #env.acc.getConfig().EventToolsChangeFields.HERO_SILVER_PRICES[static_hero['persistentId']] =0

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32(persistentId)]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.HeroesKeeper) == heroCount
        assert len(modeldata.Heroes) == heroCount
