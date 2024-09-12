import functools ,itertools
from binascii import crc32   # zlib version is not cross-platform

class GiveRerollShopHouseQuest:
    def convertModelData( self, env, acc, md, dict ):
        darkenCompleted = False
        shopQuestCompleted = False
        hasDarkenTutorial = False
        config = env.I.Config.getConfig( acc.userlocale )
        for questId in itertools.chain(md.CompletedQuests, md.ActiveQuests):
            quest = md.getQuestByID(questId)
            staticQuest = acc.SD.getStaticQuest(quest)
            if staticQuest:
                if staticQuest['persistentId'] == "d13_qA" or staticQuest['persistentId'] == "d13_qB":
                    darkenCompleted = True
                if staticQuest['persistentId'] == "m41_qA" or staticQuest['persistentId'] == "m41_qB":
                    shopQuestCompleted = True


        for questId in md.CompletedQuests:
            quest = md.getQuestByID(questId)
            staticQuest = acc.SD.getStaticQuest(quest)
            if staticQuest:
                if staticQuest['persistentId'] == "d10_qA" or staticQuest['persistentId'] == "d10_qB":
                    hasDarkenTutorial = True

        for questId in md.PendingQuests:
            if questId == crc32("m41_qB") or questId == crc32("m41_qA"):
                shopQuestCompleted = True

        if (darkenCompleted or not hasDarkenTutorial) and not shopQuestCompleted:
            staticQuest = acc.SD.getStaticQuestByFraction(acc, 'm41')
            if staticQuest:
                quest = md.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, acc )
        return md, acc.db

