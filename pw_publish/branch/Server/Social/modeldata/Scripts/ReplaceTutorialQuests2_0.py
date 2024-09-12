# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform
from enums.TutorialState import *

# см. PF-87203
class ReplaceTutorialQuests2_0:
  def convertModelData(self, env, acc, md, dict):
    config = env.I.Config.getConfig(acc.userlocale)

    # Перезапишем все старые карты у игроков, теперь можно всё :)
    md.createDefaultMaps(acc.SD, True)
    md.LordInfo.TutorialState = TutorialState.Skipped

    # Очищаем ActiveQuests, CompletedQuests и PendingQuests
    for questId in md.ActiveQuests.keys():
      md.ActiveQuests.remove(questId)
    for questId in md.CompletedQuests.keys():
      md.CompletedQuests.remove(questId)
    while len(md.PendingQuests):
      md.PendingQuests.pop(0)

    # Выдаём весь остальной набор квестов
    staticQuest = acc.SD.getStaticQuestByFraction(acc, 'n11')
    if staticQuest:
      quest = md.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS,
                          True, env.I.STATS, acc)
    staticQuest = acc.SD.getStaticQuestByFraction(acc, 'c11')
    if staticQuest:
      quest = md.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS,
                          True, env.I.STATS, acc)
    staticQuest = acc.SD.getStaticQuestByFraction(acc, 'pve11')
    if staticQuest:
      quest = md.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS,
                          True, env.I.STATS, acc)
    staticQuest = acc.SD.getStaticQuestByFraction(acc, 's11')
    if staticQuest:
      quest = md.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS,
                          True, env.I.STATS, acc)
    staticQuest = acc.SD.getStaticQuestByFraction(acc, 'hidden1')
    if staticQuest:
      quest = md.addQuest(staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS,
                          True, env.I.STATS, acc)
    return md, acc.db