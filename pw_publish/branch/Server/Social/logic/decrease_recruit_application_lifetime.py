# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.DecreaseRecruitApplicationLifetimeRequest import *
import CC

class Decrease_recruit_application_lifetime( SubAction, DecreaseRecruitApplicationLifetimeRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "decrease_recruit_application_lifetime"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        lifetime = self.acc.SD.data['GuildRecruitment']['guildRequestLifetime']
        seconds = self.arguments.days*60*60*24
        for applicationId, application in self.acc.model.GuildApplications.items():
            created = application.ExpireTime - lifetime - seconds
            self.I.DATA.update(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                                {"pers_auid": self.acc.auid, "guild_auid": application.GuildAuid}, {"created": created},
                                self.onRecruitsInfoUpdated, params=None)
            self.I.GS.updateRecruitApplication(self.acc.auid, application.GuildAuid, created)
            application.ExpireTime -= seconds
            if application.ExpireTime < int(time.time()):
                self.acc.model.GuildApplications.remove(application)

        self.response["ok"] = 1
        self.fin()

    def onRecruitsInfoUpdated(self, response):
        info(response)
