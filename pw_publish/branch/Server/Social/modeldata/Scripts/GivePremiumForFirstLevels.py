# -*- coding: utf-8 -*-
from base.helpers import *

class GivePremiumForFirstLevels:
    def convertModelData(self, env, acc, md, dict):
        accLevel = acc.SD.getFameLevel(md.LordInfo.Fame)
        if accLevel > 4 and accLevel < 20:
            md.addPremiumAccount(604800, acc)
        return md, acc.db