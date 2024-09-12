# -*- coding: utf-8 -*-
#
__author__ = 'danil.lavrentyuk'
from base.helpers import *
from functools import partial
import CC
from subaction import model_callback

__all__ = ['GuildApplicationsLoader']

class GuildApplicationsLoader(object):
    """Used for multi-inheritance with SubAction's subclass.
    Uses it's self.I and self.acc, uses model_callback decorator.
    Privides method to load guild applications during action processing."""

    def callWithGuildApplications(self, callback):
        if self.acc.model.LordInfo.UpdateGuildApplications:
            self.I.DATA.find(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                 {"pers_auid": self.acc.auid, "created": {"$gt": int(time.time()) - self.acc.SD.data['GuildRecruitment']['guildRequestLifetime']}},
                 partial(self.onActualApplicationsFound, callback=callback), params=None)
        elif callback:
            callback()

    @model_callback
    def onActualApplicationsFound(self, reply, callback):
        if "r" in reply:
            lifetime = self.acc.SD.data['GuildRecruitment']['guildRequestLifetime']
            for application in reply["r"]:
                try:
                    self.acc.model.fillGuildApplication(application, lifetime)
                except Exception:
                    catch()
        self.acc.model.LordInfo.UpdateGuildApplications = False
        if callback:
            callback()
