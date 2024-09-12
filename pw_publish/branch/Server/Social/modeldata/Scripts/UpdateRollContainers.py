# -*- coding: utf-8 -*-
from base.helpers import *

class UpdateRollContainers:
    """ Заполним новые типы ролл-контейнера, так как для премиума теперь отдельная корзина """
    def convertModelData( self, env, acc, md, dict ):
        if "LordInfo" in dict["ModelData"] and \
                "TransmutationRandomSeed" in dict["ModelData"]["LordInfo"]["LordInfo"] and \
                "TransmutationTalentsProduced" in dict["ModelData"]["LordInfo"]["LordInfo"]:
            debug("Updating seeds from old values")
            if md.IsPremiumAccount():
                md.LordInfo.PremiumForgeRoll.TransmutationRandomSeed = dict["ModelData"]["LordInfo"]["LordInfo"]["TransmutationRandomSeed"]
                md.LordInfo.PremiumForgeRoll.TransmutationTalentsProduced = dict["ModelData"]["LordInfo"]["LordInfo"]["TransmutationTalentsProduced"]
                md.setTransmutationRandomSeed(env.I.Config.GoodSeeds)
            else:
                md.LordInfo.OrdinaryForgeRoll.TransmutationRandomSeed = dict["ModelData"]["LordInfo"]["LordInfo"]["TransmutationRandomSeed"]
                md.LordInfo.OrdinaryForgeRoll.TransmutationTalentsProduced = dict["ModelData"]["LordInfo"]["LordInfo"]["TransmutationTalentsProduced"]
                md.setPremiumTransmutationRandomSeed(env.I.Config.PremiumGoodSeeds)
        return md, acc.db