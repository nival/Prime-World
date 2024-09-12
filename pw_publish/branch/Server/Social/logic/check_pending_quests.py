#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.CheckPendingQuestsRequest import CheckPendingQuestsRequest

class Check_pending_quests( SubAction, CheckPendingQuestsRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "check_pending_quests"

  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    pendings = self.acc.model.PendingQuests.keys()[:]
    for questID in pendings:
      quest = self.acc.SD.getStaticQuestById( questID )
      if quest:
        config = self.acc.getConfig()
        self.acc.model.addQuest( quest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, self.I.STATS, self.acc )

    self.response["ok"] = 1
    self.fin()