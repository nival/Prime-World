# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32

class ChangeTutorialQuests:
  def convertModelData( self, acc, SD, config, stats ):
    info("ChangeTutorialQuestsEvent: auid=%r" % acc.db.auid)
    md = acc.model
    questsToAdd = []
    questsToRemove = []
    if acc.country_code == 'US':
      # Если квесты ещё не меняли, давайте это сделаем.
      if acc.model.LordInfo.TurtorialVersion == 0:
        acc.model.LordInfo.TurtorialVersion = 1
        for questId in md.ActiveQuests:
          quest = md.getQuestByID(questId)
          staticQuest = SD.getStaticQuest(quest)
          if staticQuest:
            if staticQuest['persistentId'] in config.ALTERNATIVE_QUESTS:
              alternativeQuestsSet = json.loads(config.ALTERNATIVE_QUESTS[staticQuest['persistentId']])
              for questId in alternativeQuestsSet:
                questsToAdd.append(questId)
              questsToRemove.append(staticQuest['persistentId'])

        # Убираем квесты, которые нашли у игроков
        for questId in questsToRemove:
          staticQuest = SD.getStaticQuestById(crc32(questId))
          md.removeQuest(staticQuest)

        # Выдаём альтернативные квесты
        for questId in questsToAdd:
          staticQuest = SD.getStaticQuestById(crc32(questId))
          quest = md.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, stats, acc )

    return acc.model
