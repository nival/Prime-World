# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GuildAddActiveBuffRequest import *
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator

class Guild_add_active_buff( SubAction, GuildAddActiveBuffRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "guild_add_active_buff"
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        staticBuff = self.acc.SD.getGuildShopItemById(crc32(self.arguments.persistentId))
        if not staticBuff:
            self.errorResponse(EC.BAD_PARAM, "Can't find buff with id %d", self.arguments.persistentId)
            return

        self.I.GS.addActiveBuff(self.acc, self.arguments.persistentId, self.onBuffAdded)

    @model_callback
    @action_timing
    def onBuffAdded(self, response):
        info("onBuffAdded response: %s" % self.I.MD.pretty(response))
        self.response["callback"] = ["guild_add_active_buff"]
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                GuildData_changes = response.get("GuildData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                    except Exception:
                        catch()
                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                if self.acc.pending_handler:
                    self.acc.pending_handler()

                self.sendPendingEvents()
        self.response["ok"] = 1
        self.fin()