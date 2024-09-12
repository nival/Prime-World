# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32
from RerollHelper import *
import CC

class ResetRerollShop:
    def convertModelData( self, env, acc, md, dict ):
        rerollHelper = RerollHelper(acc.SD)
        try:
            rerollHelper.resetProbabilities(acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES], acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                            0, acc.getConfig())
        except Exception:
            pass
        md.rerollShopItems(acc)

        return md, acc.db