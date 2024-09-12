import functools ,itertools
from binascii import crc32   # zlib version is not cross-platform

class GiveQuestsForRerollShop:
    def convertModelData( self, env, acc, md, dict ):
        shopQuestCompleted = False
        config = env.I.Config.getConfig( acc.userlocale )
        for questId in md.CompletedQuests:
            quest = md.getQuestByID(questId)
            staticQuest = acc.SD.getStaticQuest(quest)
            if staticQuest:
                if staticQuest['persistentId'] == "m41_qA" or staticQuest['persistentId'] == "m41_qB":
                    shopQuestCompleted = True

        if shopQuestCompleted:
            staticQuest = acc.SD.getStaticQuestByFraction(acc, 'm42')
            if staticQuest:
                quest = md.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, acc )
        return md, acc.db
