# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveOutOfDateRecruitApplicationsRequest import *

class Remove_out_of_date_recruit_applications( SubAction, RemoveOutOfDateRecruitApplicationsRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "remove_out_of_date_recruit_applications"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.I.WS.removeOutOfDateRecruitApplications()

        self.response["ok"] = 1
        self.fin()