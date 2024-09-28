# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetLeavesRequest import *

class Set_leaves( SubAction, SetLeavesRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "set_leaves"
    debug = True

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        self.acc.model.setLeaves(self.arguments.leaves, self.acc.getConfig())

        self.response["ok"] = 1
        self.fin()