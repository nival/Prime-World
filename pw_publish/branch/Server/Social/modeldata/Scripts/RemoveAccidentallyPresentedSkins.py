# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32

PATH = os.path.dirname(os.path.abspath(__file__))

skinsToRemove = {crc32("warlord_S3"), crc32("archeress_S6")}

OPERATOR_AUIDS =[]
try:
    with open(os.path.join(PATH, "RemoveAccidentallyPresentedSkins.auids")) as f:
        OPERATOR_AUIDS = {toint(x.strip()) for x in f}
except Exception:
    catch()


class RemoveAccidentallyPresentedSkins:
    def convertModelData(self, env, acc, md, dict):
        # работаем только с халявщиками
        if acc.db.auid not in OPERATOR_AUIDS:
            return md, acc.db

        # найдём халявно полученные скины и выпилим
        for skinId, skin in md.SkinsKeeper.items():
            if skin.PersistentId in skinsToRemove:
                debug("RemoveAccidentallyPresentedSkins: removing skin %s", skin.PersistentId)
                for heroId, hero in md.Heroes.iteritems():
                    if skinId in hero.HeroSkins.Skins:
                        debug("RemoveAccidentallyPresentedSkins: skin %s removed from hero %s",
                              skin.PersistentId, hero.PersistentId)
                        hero.HeroSkins.Skins.remove(skin)
                        if skinId == hero.HeroSkins.CurrentSkin:
                            hero.HeroSkins.CurrentSkin = 0
                        break
                md.SkinsKeeper.remove(skin)
                debug("RemoveAccidentallyPresentedSkins: skin %s removed", skin.PersistentId)

        return md, acc.db