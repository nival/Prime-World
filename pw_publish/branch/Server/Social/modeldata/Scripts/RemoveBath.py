# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32
from StaticData import StaticData

class RemoveBath:
    oldLevels = None

    def __init__(self):
        if not self.oldLevels:
            with open(os.path.join(os.path.dirname(os.path.realpath(__file__)),
                                   "OldProductionPricesAndCycles/bathPrices.json"), "r") as f:
                self.__class__.oldLevels = json_loads(f.read())

    def convertModelData( self, env, acc, md, dict ):
        bath = None
        for constructionId, construction in md.ConstructionsKeeper.iteritems():
            if construction.PersistentId == crc32("Bathhouse"):
                bath = construction
                break
        if bath:
            for hid, hero in bath.HeroesInBuilding.items():
                if hero:
                    bath.removeHeroFromBuilding( hero, acc, env.I )

            price = self.getBuildingPrice(bath.Level)
            md.Buildings.remove(bath)
            md.Pocket.remove(bath)
            md.sell(price, None, False)
        return md, acc.db


    def getBuildingPrice(self, level):
        price = StaticData.emptyPrice()
        for item in self.oldLevels[0:level+1]:
            price.Resource1 += item['Resource1']
            price.Resource2 += item['Resource2']
            price.Resource3 += item['Resource3']
            price.Silver += item['Silver']
            price.Population += item['Population']
        return price