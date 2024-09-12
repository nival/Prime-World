# -*- coding: utf-8 -*-
from logic.requests.DbgQuestEventChooseRequest import *
from logic.quest_event_choose_base import *


class Dbg_quest_event_choose( Quest_event_choose_base, DbgQuestEventChooseRequest ):
    action = "dbg_quest_event_choose"
    debug = True

    def _do_roll(self):
        return self.arguments.win is True
