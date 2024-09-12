# -*- coding: utf-8 -*-
import sys

from subaction import *
from logic.requests.GetLegendLeagueRequest import *
from modeldata.change_applicator import ModelChangeApplicator
from modeldata.LegendLeagueData import LegendLeagueData
from base.sql import LegendLeagueQuery

class Get_legend_league_list( SubAction, GetLegendLeagueRequest, LegendLeagueQuery ):
    """action, ������� ����� ������������ ������ �����"""
    action = "get_legend_league_list"
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        self.acc.LegendLeagueData = LegendLeagueData()
        self.acc.LegendLeagueData.init(None)

        query, args = self.createSQLQuery()
        self.I.EXPORT.performQuery(query, args, self.onInfoFromSQL)

    def onInfoFromSQL(self, reply):
        r = reply["r"]
        if r and len(r):
            for legendLeagueInfo in r:
                ll_info, giId = self.acc.LegendLeagueData.newLegendLeagueListEntity()
                LegendLeagueData.FillInfoInfoFromSQL(ll_info, legendLeagueInfo)
                self.acc.LegendLeagueData.AllLeaguesInfo.add(ll_info)

        changes = [MakeModelChangeString("init_legend_league_data", "/", "init", self.acc.LegendLeagueData.generateJsonDict())]

        debug("get_legend_league_list, league_data: %s", )

        self.response["callback"] = ["get_legend_league_list"]
        self.response["LegendLeagueData"] = changes
        self.response["ok"] = 1
        self.fin()