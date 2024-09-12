# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32
skinPersistentId = crc32("prince_S4")

class RemovePrinceSkin:
    def convertModelData(self, env, acc, md, dict):
        # найдём принца и выпилим
        for skinId, skin in md.SkinsKeeper.items():
            if skin.PersistentId == skinPersistentId:
                for heroId, hero in md.Heroes.iteritems():
                    if skinId in hero.HeroSkins.Skins:
                        hero.HeroSkins.Skins.remove(skin)
                        hero.HeroSkins.CurrentSkin = 0
                env.I.BILL.replenish(acc.db.auid, 1, "GoldFor_prince_S4", None)
                md.SkinsKeeper.remove(skin)
                break
        return md, acc.db