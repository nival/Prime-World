# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32
import CC

class RemoveOldRerollGroups:
    def convertModelData( self, env, acc, md, dict ):
        if not acc.db.get("castle_roll", None):
            acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {},
                              CC.REROLL_DAILY_WEIGHTS: {}}
        for groupId in acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES].keys():
            if groupId not in acc.getConfig().EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS:
                del acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES][groupId]
        for groupId in acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES].keys():
            if groupId not in acc.getConfig().EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS:
                del acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES][groupId]
        for groupId in acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS].keys():
            if groupId not in acc.getConfig().EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS:
                del acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS][groupId]

        return md, acc.db