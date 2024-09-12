# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GetGuildsListRequest import *
from guild.GuildWarsData import GuildWarsData
from modeldata.change_applicator import ModelChangeApplicator
from base.sql import GuildListQuery

GuildListQuery.setSortCriteria(GuildsListSortCriteria)

class Get_guilds_list(SubAction, GetGuildsListRequest, GuildListQuery):
    """action, который будет обрабатывать данный класс"""
    action = "get_guilds_list"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.acc.GuildWarsData = GuildWarsData()
        self.acc.GuildWarsData.init(None)

        query, args = self.createSQLQuery()
        debug("Get_guilds_list query: %s, args: %r", query, args)
        self.I.EXPORT.performQuery(query, args, self.onInfoFromSQL)

    def onInfoFromSQL(self, reply):
        r = reply["r"]
        if r and len(r):
            for guildInfo in r:
                gi, giId = self.acc.GuildWarsData.newGuildsListEntity()
                gi.ShortInfo, _id = self.acc.GuildWarsData.newGuildShortInfo()
                GuildWarsData.FillGuildShortInfoFromSQL(gi, guildInfo)
                self.acc.GuildWarsData.AllGuilds.add(gi)

        changes = [MakeModelChangeString("init_guild_wars_data", "/", "init", self.acc.GuildWarsData.generateJsonDict())]
        self.response["callback"] = ["get_guilds_list"]
        self.response["GuildWarsData"] = changes
        self.response["ok"] = 1
        self.fin()

