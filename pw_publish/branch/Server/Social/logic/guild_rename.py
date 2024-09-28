# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.GuildRenameRequest import GuildRenameRequest

from ext_main.nickname import SetNicknameAction


class Guild_rename(SubAction, GuildRenameRequest):
    """action, который будет обрабатывать данный класс"""
    action = "guild_rename"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD, "You're not in guild")
            return

        ( r, self.textFullName, encoding ) = SetNicknameAction.checkNickname(self.arguments.fullname,
                                                self.acc.getConfigValue("NICKNAME_REGEXES").keys(),
                                                self.acc.getConfigValue("ADMIN_NICKS").keys())
        if r != SetNicknameAction.CHECK_OK:
            warn("Cannot rename guild for acc %r to %r" % ( self.acc.db.guildAuid, self.arguments.fullname ))
            self.response["callback"] = ["guild_rename"]
            self.errorResponse(EC.BAD_GUILD_FULL_NAME, self.textFullName)
            return

        ( r, self.textShortName, encoding ) = SetNicknameAction.checkNickname(self.arguments.shortname,
                                                self.acc.getConfigValue("NICKNAME_REGEXES").keys(),
                                                self.acc.getConfigValue("ADMIN_NICKS").keys(),
                                                2, 5)
        if r != SetNicknameAction.CHECK_OK:
            warn("Cannot rename guild for acc %r to %r" % ( self.acc.auid, self.arguments.shortname ))
            self.response["callback"] = ["guild_rename"]
            self.errorResponse(EC.BAD_GUILD_SHORT_NAME, self.textShortName)
            return

        self.textFullName = self.textFullName.encode('utf8')
        self.textShortName = self.textShortName.encode('utf8')
        self.I.GS.checkGuildName(self.acc, self.textFullName, self.textShortName, self.OnNameChecked)

    @action_timing
    def OnNameChecked(self, response):
        info("OnNameChecked response: %s" % self.I.MD.pretty(response))
        code = response["unique"]
        if code == True:
            gold = int(self.acc.getConfigValue("GUILD_RENAME_PRICE_GOLD"))
            self.price = self.acc.model.createResourcesTable(Gold=gold)
            self.needGold = int(gold)
            if self.price >= 0:
                reason = "PW!RENAME_GUILD:" + str(self.textFullName) + "[" + str(self.textShortName) + "]"
                self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
                return None
            else:
                self.response["callback"] = ["guild_rename"]
                self.errorResponse("Price is negative")
        else:
            self.response["callback"] = ["guild_rename"]
            if code == "Short":
                self.errorResponse(EC.GUILD_SHORTNAME_NOT_UNIQUE, "Guild shortname is not unique")
            elif code == "Full":
                self.errorResponse(EC.GUILD_FULLNAME_NOT_UNIQUE, "Guild fullname is not unique")

    @model_callback
    @action_timing
    def onRenameGuild(self, response):
        if response:
            info("onRenameGuild response: %s" % self.I.MD.pretty(response))
            GuildData_changes = response.get("GuildData") or []
            if GuildData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                except:
                    catch()
            self.acc.pending_events.append({"callback": {"callback": ["guild_rename"]}})
            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            self.I.STATS.addGuildRenamed(self.acc.auid, self.acc.db.guildAuid, self.acc.db.fraction,
                                         self.arguments.shortname,
                                         self.arguments.fullname, self.price, self.acc.model.Resources,
                                         len(self.acc.guilddata.Members))
            if self.acc.pending_handler:
                self.acc.pending_handler()

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            self.I.GS.renameGuild(self.acc, self.arguments.fullname, self.arguments.shortname, self.onRenameGuild)
            self.response["ok"] = 1
            self.fin()
        else:
            self.response["callback"] = ["guild_rename"]
            self.onBuyError(response, self.needGold)

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)
