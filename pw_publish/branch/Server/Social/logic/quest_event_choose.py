# -*- coding: utf-8 -*-
from logic.requests.QuestEventChooseRequest import *
from logic.quest_event_choose_base import *


class Quest_event_choose( Quest_event_choose_base, QuestEventChooseRequest ):
    action = "quest_event_choose"

    def _do_roll(self):
        ratio = self.quest_choice.WinRatioBase
        if self.acc.model.IsPremiumAccount():
            ratio = self.quest_choice.WinRatioGold
        drop = random.random()
        return drop <= ratio
