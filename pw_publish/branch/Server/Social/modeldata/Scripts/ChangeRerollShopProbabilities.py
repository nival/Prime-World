# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32
from RerollHelper import *
import CC

class ChangeRerollShopProbabilities:
    def convertModelData( self, env, acc, md, dict ):
        acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {},
                              CC.REROLL_DAILY_WEIGHTS: {}}
        rerollHelper = RerollHelper(acc.SD)
        rerollHelper.resetProbabilities(acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES], acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                        acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES], 0, acc.getConfig())
        md.rerollShopItems(acc)

        return md, acc.db