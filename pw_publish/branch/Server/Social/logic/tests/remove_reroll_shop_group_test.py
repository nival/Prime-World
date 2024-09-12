import sys
sys.path.append('../')
sys.path.append('../..')
from logic.remove_reroll_shop_group import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class remove_reroll_shop_group_test:

    def remove_reroll_shop_group_test( self, env ):
        modeldata = env.acc.model
        totalSum = 0

        weights = env.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS]
        probs = env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES]
        for persistentId, staticGroup in env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.iteritems():
            newWeight = env.acc.getConfig().getRollWeightByRollTimes(staticGroup.LevelToWeights, 0)
            weights[persistentId] = newWeight
            probs[persistentId] = newWeight*100
            totalSum += newWeight * 100
        oldMdSum = 0
        for key, probability in env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES].iteritems():
            oldMdSum += probability
        assert oldMdSum != totalSum

        requests = [(Remove_reroll_shop_group, RemoveRerollShopGroupRequest(modeldata, {"persistentId": ["" + str(crc32("group_A")) + ""]}, False))]
        changeList = env.execActions(requests)

        mdSum = 0
        for key, probability in env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES].iteritems():
            mdSum += probability
        env.printAssert(mdSum, oldMdSum)