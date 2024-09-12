# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32
import CC

class AddRerollShopProbabilities:
    def convertModelData( self, env, acc, md, dict ):
        acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {},
                              CC.REROLL_DAILY_WEIGHTS: {}}
        weights = acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS]
        probs = acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES]
        for persistentId, staticGroup in acc.getConfig().EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.iteritems():
            newWeight = acc.getConfig().getRollWeightByRollTimes(staticGroup.LevelToWeights, 0)
            weights[str(persistentId)] = newWeight
            probs[str(persistentId)] = newWeight*100
        md.rerollShopItems(acc)

        return md, acc.db