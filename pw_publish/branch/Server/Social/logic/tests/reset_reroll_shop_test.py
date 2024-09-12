import sys
sys.path.append('../')
sys.path.append('../..')
from logic.reset_reroll_shop import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class reset_reroll_shop_test:

    def reset_reroll_shop_test( self, env ):
        modeldata = env.acc.model
        totalSum = 0
        for persistentId, staticGroup in env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.iteritems():
            newWeight = env.acc.getConfig().getRollWeightByRollTimes(staticGroup.LevelToWeights, 0)
            totalSum += newWeight

        oldMdSum = 0
        for key, probability in env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES].iteritems():
            oldMdSum += probability
        assert oldMdSum != totalSum

        requests = [(Reset_reroll_shop, ResetRerollShopRequest(modeldata, {}, False))]
        changeList = env.execActions(requests)

        mdSum = 0
        for key, probability in env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES].iteritems():
            mdSum += probability
        assert mdSum in range(100 - len(env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES]),
                              100 + len(env.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES]))