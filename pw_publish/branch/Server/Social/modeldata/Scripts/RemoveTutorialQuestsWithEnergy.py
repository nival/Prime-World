# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform

# см. PF-101868
class RemoveTutorialQuestsWithEnergy:
    def convertModelData( self, env, acc, md, dict ):
        hasc12 = False
        hasc13 = False
        hash13 = False
        config = env.I.Config.getConfig(acc.userlocale)
        # посмотрим, у кого есть нужные квесты
        for questId in md.ActiveQuests:
            quest = md.getQuestByID(questId)
            if quest.persistentId == crc32("c12_qA") or quest.persistentId == crc32("c12_qB"):
                hasc12 = True
            if quest.persistentId == crc32("c13_qA") or quest.persistentId == crc32("c13_qB"):
                hasc13 = True
            if quest.persistentId == crc32("h13_qA") or quest.persistentId == crc32("h13_qB"):
                hash13 = True
        # Воздадим каждому по заслугам
        if hasc12 or hasc13:
            md.removeQuest(acc.SD.getStaticQuestOnlyNameByFraction(acc, "c13"))
            md.removeQuest(acc.SD.getStaticQuestOnlyNameByFraction(acc, "c12"))
            staticQuest = acc.SD.getStaticQuestByFraction(acc, 'c21')
            if staticQuest:
                quest = md.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS,
                                    config.ONE_TIME_QUESTS, True, env.I.STATS, acc)
        if hash13:
            md.removeQuest(acc.SD.getStaticQuestOnlyNameByFraction(acc, "h13"))
            staticQuest = acc.SD.getStaticQuestByFraction(acc, 'h14')
            if staticQuest:
                quest = md.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS,
                                    config.ONE_TIME_QUESTS, True, env.I.STATS, acc)

        return md, acc.db
