# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.DbgQuestEventClearRequest import *

class Dbg_quest_event_clear( SubAction, DbgQuestEventClearRequest ):
    action = "dbg_quest_event_clear"
    debug = True
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        event_id = self.arguments.questEventId
        events = self.acc.getConfigValue("QuestEvents")
        if event_id not in events:
            self.errorResponse("Can't find QuestEvent with id %d" % event_id)
            return

        quest_event = events[event_id]

        if quest_event.Guid not in self.acc.model.QuestEvents:
            self.errorResponse("No progression record for QuestEvent with guid %d" % quest_event.Guid)
            return

        event_progression = self.acc.model.QuestEvents[quest_event.Guid]

        while len(event_progression.Choices) > 0:
            event_progression.Choices.pop()

        self.response["ok"] = 1
        self.fin()
