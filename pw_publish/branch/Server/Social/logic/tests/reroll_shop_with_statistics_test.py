# -*- coding: utf-8 -*-
import sys
import math
import pymongo
sys.path.append('../')
sys.path.append('../..')
from logic.reroll_shop_with_statistics import *
import coord_cfg
from binascii import crc32
from base.helpers import *
from enums import *
import EC
from cluster_base import crc_hash


# needed in reroll shop manual testing, will started from - Reroll_shop_with_statistics
# maybe test locally, but remember - logic "Reroll_shop_with_statistics" depends on this
class reroll_shop_with_statistics_test:

    def reroll_shop_with_statistics_test( self, env ):

        modeldata = env.acc.model
        env.acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {}, CC.REROLL_DAILY_WEIGHTS: {}}

        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            modeldata.RerollShopInfo.ShopItems.remove(item)

        assert len(modeldata.RerollShopInfo.ShopItems) == 0
        sumWeight = 0
        weights = env.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS]
        probs = env.acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES]
        rollList = env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES]
        probabilitiesList = {}
        for persistentId, staticGroup in env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.iteritems():
            newWeight = env.acc.getConfig().getRollWeightByRollTimes(staticGroup.LevelToWeights, 0)
            weights[str(persistentId)] = newWeight
            sumWeight += newWeight

        for persistentId in weights:
            probabilitiesList[persistentId] = float(weights[persistentId])/sumWeight*100
            groupProbability = probabilitiesList[persistentId]
            if persistentId in probs:
                groupProbability += probs[persistentId]
            if groupProbability > 0:
                rollList[persistentId] = random.randint(math.floor(groupProbability), math.ceil(groupProbability))
                probs[persistentId] = groupProbability - rollList[persistentId]
            else:
                rollList[persistentId] = 0
                probs[persistentId] = groupProbability

        requests = [(Reroll_shop_with_statistics, RerollShopWithStatisticsRequest(modeldata,
                                                                                  {"totalRerolls": ["" + str(0) + ""],
                                                                                   "dumpConfig": ["False"]}, False))]
        changeList = env.execActions(requests)

        expectedSlotsCount = env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS + env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS

        assert len(modeldata.RerollShopInfo.ShopItems) == expectedSlotsCount

    def reroll_shop_with_statistics_subprocess_test( self, env ):

        debug("I'm in!")

        settingsFile = open("Rerolls.txt", "r")
        rerolls = int(settingsFile.readline())
        # rerolls = 5

        index = (crc_hash("events") % len(coord_cfg.COORDINATOR_MONGO_CONFIG)) if len(coord_cfg.COORDINATOR_MONGO_CONFIG) else 0
        opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[index])
        mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)
        if mongo_db:
            cursor = mongo_db.events.find()
            for obj in cursor:
                try:
                    event = {"endTime": obj["endTime"], "persistentId": obj["_id"],
                             "startTime": obj["startTime"],
                             "enabled": obj["enabled"], "type": obj["type"],
                             "newValue": obj["customData"], "defaultValue": {}}
                    #env.I.Config.setEventDefalutValue(env.I.SD, event)
                    #changes, self.needUpdateSeeds = env.I.Config.applyEvent(env.I.SD, event)
                    #changes = env.I.Config.revertEvent(env.I.SD, event)

                    if event["enabled"] and event["startTime"] < int(time.time()) < event["endTime"]:
                        info("Loading event %r", event)
                        changes, self.needUpdateSeeds = env.I.Config.applyEvent(env.I.SD, event)
                except Exception:
                    catch()

        modeldata = env.acc.model
        env.acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {}, CC.REROLL_DAILY_WEIGHTS: {}}

        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            modeldata.RerollShopInfo.ShopItems.remove(item)

        assert len(modeldata.RerollShopInfo.ShopItems) == 0
        sumWeight = 0
        weights = env.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS]
        probs = env.acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES]
        rollList = env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES]
        probabilitiesList = {}
        for persistentId, staticGroup in env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.iteritems():
            newWeight = env.acc.getConfig().getRollWeightByRollTimes(staticGroup.LevelToWeights, 0)
            weights[str(persistentId)] = newWeight
            sumWeight += newWeight

        for persistentId in weights:
            probabilitiesList[persistentId] = float(weights[persistentId])/sumWeight*100
            groupProbability = probabilitiesList[persistentId]
            if persistentId in probs:
                groupProbability += probs[persistentId]
            if groupProbability > 0:
                rollList[persistentId] = random.randint(math.floor(groupProbability), math.ceil(groupProbability))
                probs[persistentId] = groupProbability - rollList[persistentId]
            else:
                rollList[persistentId] = 0
                probs[persistentId] = groupProbability
        requests = [(Reroll_shop_with_statistics, RerollShopWithStatisticsRequest(modeldata,
                                                                                  {"totalRerolls": ["" + str(rerolls) + ""],
                                                                                   "dumpConfig": ["False"]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.RerollShopInfo.ShopItems) == env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS + env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS



