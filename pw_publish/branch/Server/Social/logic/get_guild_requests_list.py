# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GetGuildRequestsListRequest import *
from guild.GuildWarsData import GuildWarsData
from enums import RatingPositionChange
from itertools import repeat
from base.sql import GuildListQuery

GuildListQuery.setSortCriteria(GuildsListSortCriteria)


class Get_guild_requests_list(SubAction, GetGuildRequestsListRequest, GuildListQuery):
    """action, который будет обрабатывать данный класс"""
    action = "get_guild_requests_list"

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

        self.response["callback"] = ["get_guild_requests_list"]
        self.I.DATA.find_one("guilds", "guilds", {"key": ("gs_"+str(self.acc.db.guildAuid))}, self.onDataResponse, params=None)

    def onDataResponse(self, response):
        self.acc.GuildWarsData = GuildWarsData()
        self.acc.GuildWarsData.init(None)

        if response and "r" in response:
            requests = response["r"].get("requests") or None
            if requests and "SuzerainInvites" in requests:
                if requests["SuzerainInvites"]:
                    info("Get_guild_requests_list: %r" % requests["SuzerainInvites"])
                    query, args = self.createSQLQuery(requests["SuzerainInvites"].keys())
                    debug("Get_guild_requests_list query: %s, args: %r" % (query, args))
                    self.I.EXPORT.performQuery(query, args, self.onInfoFromSQL)
                    return
        else:
            err("Bad response from Mongo database")
        changes = [MakeModelChangeString("init_guild_wars_data", "/", "init", self.acc.GuildWarsData.generateJsonDict())]
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
                self.acc.GuildWarsData.VassalApplications.add(gi)

        changes = [MakeModelChangeString("init_guild_wars_data", "/", "init", self.acc.GuildWarsData.generateJsonDict())]
        self.response["GuildWarsData"] = changes
        self.response["ok"] = 1
        self.fin()

