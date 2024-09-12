# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.WithdrawRecruitApplicationRequest import *
#import CC
from base.exceptions import *

class Withdraw_recruit_application( SubAction, WithdrawRecruitApplicationRequest ):
    """Отзыв игроком заявки на вступление в клан."""
    action = "withdraw_recruit_application"

    @model_callback
    @parse
    def onStart(self):
        acc = self.acc
        guildAuid = self.arguments.guildAuid
        info("Withdraw_recruit_application: auid=%s, guildAuid=%s", acc.db.auid, guildAuid)
        if not self.checkParams():
            return

        if acc.db.guildAuid:
            self.errorResponse(EC.RECRUIT_IN_GUILD, "You're in a guild already.")
            return

        try:
            acc.model.removeGuildApplication(guildAuid)
            self.I.WS.removePlayerGuildApplications(acc, [guildAuid])
            self.response["ok"] = 1
            self.I.GS.rmRecruitNotification(self.acc.db.auid, self.arguments.guildAuid)
            self.fin()
        except RecruitAppliationDeclinedError:
            warn("Withdraw_recruit_application auid = %s (guildAuid=%s): application already declined!", acc.db.auid, guildAuid)
            self.errorResponse(EC.RECRUIT_DECLINED, "Declined application can't be withdrawn")
        except NoRecruitApplicationError:
            warn("Withdraw_recruit_application auid = %s (guildAuid=%s): application not found!", acc.db.auid, guildAuid)
            self.errorResponse(EC.RECRUIT_NO_RECRUIT, "Recruit application not found")

        # просто заодно проверим, не протухло ли что
        self.I.WS.checkPlayerGuildApplications(acc)

