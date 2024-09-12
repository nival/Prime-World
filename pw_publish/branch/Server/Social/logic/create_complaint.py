#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
import base64
from logic.requests.CreateComplaintRequest import CreateComplaintRequest
from ext_main.get_full_user_account import GetFullUserAccountAction

_DUMMY = object() # just to make it unique

# Откуда пришла жалоба
SOURCE_CASTLE  = 0
SOURCE_SESSION = 1

class Create_complaint(SubAction, CreateComplaintRequest):
    """action, который будет обрабатывать данный класс"""
    action = "create_complaint"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # Не нашёлся лог чата - ну и ладно.
        self.chatLog = self.getParam('post_data', "").replace(' ','+') #уберем на всякий случай пробелы
        debug("chat log %s", self.chatLog)
        if self.chatLog != "" and not self.chatLog.startswith('type='): # PF-95830 - castle client sends unencoded data
            self.chatLog = base64.urlsafe_b64decode(self.chatLog + "=" * ((4 - len(self.chatLog) % 4) % 4)) # PF-94654 // добавим возможно пропущенные паддинги

        if self.arguments.source is not None and self.arguments.source == SOURCE_CASTLE and self.acc.model.LordInfo.ComplaintsLeft <= 0:
            self.errorResponse(EC.TOO_MANY_COMPLAINTS, "Too many complaints today", { "ComplaintsLeft" : self.acc.model.LordInfo.ComplaintsLeft })
            return

        if self.arguments.source is not None and self.arguments.source == SOURCE_SESSION and self.acc.model.LordInfo.ComplaintsSessionLeft <= 0:
            self.errorResponse(EC.TOO_MANY_COMPLAINTS, "Too many session' complaints", { "ComplaintsSessionLeft" : self.acc.model.LordInfo.ComplaintsSessionLeft })
            return

        txt = self.arguments.text.replace(' ','+')
        self.msg = base64.urlsafe_b64decode(txt + "=" * ((4 - len(txt) % 4) % 4) ) #и тут тоже уберем пробелы и добавим возможно пропущенные паддинги

        args = ClassDict( target_auid=[self.arguments.toauid] )
        action = GetFullUserAccountAction(args, self.onTargetAccInfoFound, I=self.I, acc=self.acc, uid=self.acc.uid)
        action.onStart()

    @model_callback
    def onTargetAccInfoFound(self, response):
        args = self.arguments
        userlocale = self.acc.userlocale
        muid = self.acc.muid or self.acc.db.muid
        ruid = self.acc.ruid or self.acc.db.ruid
        if response:
            #info( "onTargetAccInfoFound response: %s" % self.I.MD.pretty(response) )
            isOk = response.get("ok") or 0
            if isOk:
                info("onTargetAccInfoFound: Ok")
                target_acc_db = ClassDict(response.get("db"))
                if target_acc_db:
                    userlocale = target_acc_db.locale
                    muid = target_acc_db.muid
                    ruid = target_acc_db.ruid
            else:
                if response.get("error"):
                    warn("onTargetAccInfoFound error: %r", response.get("error"))
        else:
            warn("onTargetAccInfoFound error: empty response")

        info("Create complaint from auid %r to auid %r category %r with text %r sessionid %r source %r timestamp %r "
             "kills %r deaths %r assists %r points %r prime %r leave %r distance %r afks %r log %r locale %r muid %r, ruid %r",
             self.acc.db.auid, args.toauid, args.category, self.msg, args.sessionid, args.source,
             int(time.time()), args.kills, args.deaths, args.assists, args.points, args.prime,
             args.leave, args.distance, args.afks, self.chatLog, userlocale, muid, ruid)

        self.I.STATS.addUserClaim(args.category, self.acc.db.auid, args.toauid, self.msg, self.chatLog,
                                  args.source, userlocale, muid or "", session_id=args.sessionid, deaths=args.deaths,
                                  kills=args.kills, assists=args.assists, points=args.points,
                                  prime=args.prime, leave=args.leave, distance=args.distance, afks=args.afks)

        if args.source == SOURCE_SESSION:
            # Forget ally who we have complainted on
            self.acc.model.LordInfo.ComplaintsSessionLeft -= 1
            self.I.FRIENDS.removeRecentAlly(self.acc.db.auid, args.toauid, None)

        else:
            self.acc.model.LordInfo.ComplaintsLeft -= 1

        self.response["ok"] = 1
        self.fin()
