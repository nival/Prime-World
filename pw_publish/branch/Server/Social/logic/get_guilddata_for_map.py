# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GetGuildDataForMapRequest import *
import CC
import EC

class Get_guilddata_for_map(SubAction, GetGuildDataForMapRequest):
    """action, который будет обрабатывать данный класс"""
    action = "get_guilddata_for_map"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC
        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD, "You're not in guild")
            return

        if self.acc.db.guildAuid == self.getIntParam('guildAuid'):
            self.errorResponse(EC.DEBUG_MESSAGE, "It is your guild")
            return

        if self.getIntParam('guildAuid') in (CC.NPC_SUZERAIN_AUID, CC.NPC_VASSAL_AUID):
            self.errorResponse( EC.DEBUG_MESSAGE, "You can not see map for NPC")
            return

        self.I.GS.getGuilDataFordMap(self.acc, self.getIntParam('guildAuid'), self.onGetGuildDataForMap)


    def onGetGuildDataForMap(self, response):
        info( "Guild_get_map.onGetGuildDataForMap response: %r" % response )
        if response:
            self.response["GuildMapData"] = response.get("GuildMapData", "{}")
            self.response["ok"] = 1
        else:
            self.response["ec"] = EC.ACTION_HANDLER_EXCEPTION
            self.response["error"] = "Bad response from guild service"
            err(self.response["error"])
            self.response["ok"] = 0
        self.fin()

