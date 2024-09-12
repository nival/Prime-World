# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform
from enums.MapType import *
from StatisticCore.ttypes import TalentChangeOperation

# см. PF-83657
class ReplaceTutorialQuestsAndAwards:
  def convertModelData( self, env, acc, md, dict ):
    self.giveTalentsForOldCompletedQuests(env, acc, md)
    hasS31 = False
    hasS41 = False
    hasN11 = False
    config = env.I.Config.getConfig( acc.userlocale )
    # посмотрим, у кого есть нужные квесты
    for questId in md.ActiveQuests:
      quest = md.getQuestByID(questId)
      staticQuest = acc.SD.getStaticQuest(quest)
      if staticQuest:
        if staticQuest['persistentId'] == "s41_qA" or staticQuest['persistentId'] == "s41_qB":
          hasS41 = True
        if staticQuest['persistentId'] == "n11_qA" or staticQuest['persistentId'] == "n11_qB":
          hasN11 = True
        if staticQuest['persistentId'] == "c21_qA" or staticQuest['persistentId'] == "c21_qB":
          quest.resetQuest(md, acc.SD)
      else:
        if quest.persistentId == crc32("s31_qA") or quest.persistentId == crc32("s31_qB"):
          hasS31 = True
    # Воздадим каждому по заслугам
    if hasS31:
      staticQuest = acc.SD.getStaticQuestByFraction(acc, 's31')
      md.removeQuest(staticQuest)
      if not hasN11:
        staticQuest = acc.SD.getStaticQuestByFraction(acc, 'n11')
        if staticQuest:
          quest = md.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, acc )
      if not hasS41:
        staticQuest = acc.SD.getStaticQuestByFraction(acc, 's41')
        if staticQuest:
          quest = md.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, acc )

    # Поменяем карты тем, кто ещё не прошёл какие-то из старых квестов
    hasPVE1 = False
    for questId in md.QuestsKeeper:
      quest = md.getQuestByID(questId)
      staticQuest = acc.SD.getStaticQuest(quest)
      if staticQuest:
        if staticQuest['persistentId'] == "pve11_qA" or staticQuest['persistentId'] == "pve11_qB":
          hasPVE1 = True
    if not hasPVE1:
      mapInfo = md.LordInfo.MapsByType.get(MapType.PVE)
      md.updateMap(MapType.PVE, mapInfo.MapId, mapInfo.Enabled, mapInfo.StartTime, mapInfo.EndTime, False)

    completedS11 = False
    completedS21 = False
    for questId in md.CompletedQuests:
      quest = md.getQuestByID(questId)
      staticQuest = acc.SD.getStaticQuest(quest)
      if staticQuest:
        if staticQuest['persistentId'] == "s11_qA" or staticQuest['persistentId'] == "s11_qB":
          completedS11 = True
        if staticQuest['persistentId'] == "s21_qA" or staticQuest['persistentId'] == "s21_qB":
          completedS21 = True
    # Если нет даже первого квеста, выдаём карту туториал1
    if not completedS11:
      mapId = acc.SD.getDefaultMapByType(MapType.Tutorial)
      mapInfo = md.LordInfo.MapsByType.get(MapType.Tutorial)
      md.updateMap(MapType.Tutorial, mapId, mapInfo.Enabled, mapInfo.StartTime, mapInfo.EndTime, mapInfo.Visible)
    # Если готов только s11, выдаём карту туториал2
    elif completedS11 and not completedS21:
      mapInfo = md.LordInfo.MapsByType.get(MapType.Tutorial)
      md.updateMap(MapType.Tutorial, "/Maps/Tutorial/_2.ADMPDSCR", mapInfo.Enabled, mapInfo.StartTime, mapInfo.EndTime, mapInfo.Visible)
    # Если туториальные карты пройдены, убираем туториальный слот
    else:
      mapInfo = md.LordInfo.MapsByType.get(MapType.Tutorial)
      md.updateMap(MapType.Tutorial, "", mapInfo.Enabled, mapInfo.StartTime, mapInfo.EndTime, False)
    return md, acc.db

  def giveTalentsForOldCompletedQuests(self, env, acc, md):
    hasC25 = False
    hasS42 = False
    for questId in md.CompletedQuests:
      quest = md.getQuestByID(questId)
      staticQuest = acc.SD.getStaticQuest(quest)
      if staticQuest:
        if staticQuest['persistentId'] == "s42_qA" or staticQuest['persistentId'] == "s42_qB":
          hasS42 = True
        if staticQuest['persistentId'] == "c25_qA" or staticQuest['persistentId'] == "c25_qB":
          hasC25 = True
    talents = []
    if hasS42:
      talents.append('G231')
    if hasC25:
      talents.append('G247')
    if talents:
      md.addTalentsForFree("Quests s42, c25", talents, acc, env.I.STATS, TalentChangeOperation.GetFromQuest)