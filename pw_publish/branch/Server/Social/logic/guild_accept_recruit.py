# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GuildAcceptRecruitRequest import *
from base.service_lock import ServiceLock
from ext_main.get_full_user_account import GetFullUserAccountAction
import CC
from modeldata.change_applicator import ModelChangeApplicator
import cfg
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from base.service_lock import ServiceLock
from ext_main.accept_recruit import AcceptRecruitAction
from handlers import *

class Guild_accept_recruit(SubAction, GuildAcceptRecruitRequest):
    """
    action, который будет обрабатывать данный класс

    Схема работы:
    1. Проверяем находится ли ауид в процессе принятия в гильдию
    2. Если 1 ок, устанавливаем состояние принятия в гильдию
    3. Если 2 ок, то отправляем запрос ws ке на которой загружен юзвер, чтобы там иницировать принятие в гильдию
    """
    action = "guild_accept_recruit"


    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC
        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD, "You are non in guild. ")
            return

        if not self.arguments.auid:
            self.errorResponse(EC.BAD_PARAM, "Bad auid !")
            return

        # 1. Проверяем находится ли ауид в процессе принятия в гильдию
        self.lock = ServiceLock(self.I.DATA, 'recruit_' + str(self.arguments.auid), self.onSemaphoreReady)

    def onSemaphoreReady(self):
        # 2. Если 1 ок, устанавливаем состояние принятия в гильдию
        self.lock.tryAcquire(self.onLockAcquired)


    def onLockAcquired(self, OK):
        debug("Guild_accept_recruit.onLockAcquired %r", OK)
        if OK:
            self.I.GS.acceptRecruit( self.acc.auid, self.acc.db.guildAuid, self.arguments.auid, self.onResultAccept)
        else:
            # видимо наше место уже занято
            self.errorResponse(EC.RECRUIT_NO_RECRUIT, "This recruit was accepted by another guild!")


    def onResultAccept(self, response):
        debug("Guild_accept_recruit.onResultAccept %r", response)
        if response:
            isOk = response.get("ok") or 0
            self.msg = response.get("error") or ""
            self.guildName = response.get("guildName") or ""
            if isOk:
                acc =self.I.WS.getUserAccByAuid(self.arguments.auid)
                if not acc:
                    args = ClassDict(target_auid=[self.arguments.auid], is_ws=[True])
                    action = GetFullUserAccountAction(args, self.onSendMail, I=self.I)
                    action.onStart()
                else:
                    ar = ClassDict(guildAuid=[self.acc.db.guildAuid], auid=[self.arguments.auid])
                    act = AcceptRecruitAction(ar, self.onGetFullUserAccountAction, I=self.I)
                    act.onStart()
            else:
                self.lock.removeVar()
                self.errorResponse(response.get("ec"), response.get("error") or "")
        else:
            self.lock.removeVar()
            self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Internal Server Error")

    def onSendMail(self, response):
        debug("Guild_accept_recruit.onSendMail %r", response)
        if response:
            ws = response.get("ws_name", "")
            if ws:
                args = dict(action="accept_recruit",
                            auid=self.arguments.auid,
                            guildAuid=self.acc.db.guildAuid)
                debug("Guild_accept_recruit.onSendMail peers %r", self.I.WS.peers)
                ws_addr = self.I.WS.getPeerServerByName(ws)["addr"]
                self.I.WSX.fetch(ws_addr, args, self.onGetFullUserAccountAction, subrequest=ws)
                return
            else:
                self.lock.removeVar()
                self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Internal Server Error")
        else:
            self.lock.removeVar()
            self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Internal Server Error")

    def onGetFullUserAccountAction(self, response):
        debug("Guild_accept_recruit.onGetFullUserAccountAction %r", response)
        if response:
            isOk = response.get("ok") or 0
            msg = response.get("error") or ""
            ec = response.get("ec") or 0
            if isOk:
                self.response['ok'] = isOk
                self.fin()
            else:
                self.lock.removeVar()
                self.errorResponse(ec, msg)
        else:
            self.lock.removeVar()
            self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Internal Server Error")



