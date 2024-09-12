# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GetExVassalsListRequest import *
from guild.GuildWarsData import GuildWarsData
import CC

class Get_ex_vassals_list( SubAction, GetExVassalsListRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "get_ex_vassals_list"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if not self.acc.db.guildAuid:
            self.errorResponse( EC.NOT_IN_GUILD,  "You're not in guild" )
            return

        self.acc.GuildWarsData = GuildWarsData()
        self.acc.GuildWarsData.init(None)

        if self.acc.guilddata.ExVassals:
            keys = [toint(x) for x in self.acc.guilddata.ExVassals.keys() if x != CC.NPC_VASSAL_AUID] # затычка на случай  PF-93123
            self.I.EXPORT.getExtendedGuildsInfo(keys, self.onInfoFromSQL)
        else:
            changes = [MakeModelChangeString("GWD_changes_on_exVassal_request_NoExVassals", "/", "init", self.acc.GuildWarsData.generateJsonDict())]
            #self.acc.pending_events.append({"GuildWarsData": {"GuildWarsData": changes}})
            self.response["callback"] = ["get_ex_vassals_list"]
            self.response["GuildWarsData"] = changes
            self.response["ok"] = 1
            self.fin()


    def onInfoFromSQL(self, reply):
        r = reply["r"]
        if r and len(r):
            for guildInfo in r:
                gi, giId = self.acc.GuildWarsData.newGuildsListEntity()
                gi.ShortInfo, _id = self.acc.GuildWarsData.newGuildShortInfo()
                GuildWarsData.FillGuildShortInfoFromSQL(gi, guildInfo)
                self.acc.GuildWarsData.ExVassals.add(gi)

        changes = [MakeModelChangeString("GWD_changes_on_exVassal_request_from_sql", "/", "init", self.acc.GuildWarsData.generateJsonDict())]
        #self.acc.pending_events.append({"GuildWarsData": {"GuildWarsData": changes}})
        self.response["callback"] = ["get_ex_vassals_list"]
        self.response["GuildWarsData"] = changes
        self.response["ok"] = 1
        self.fin()
