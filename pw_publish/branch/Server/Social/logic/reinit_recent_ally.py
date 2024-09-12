# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from friendsdata.FriendsData import FriendsData
from logic.requests.ReinitRecentAllyRequest import *
from base.exceptions import  ModelChangeApplicatorError

class Reinit_recent_ally( SubAction, ReinitRecentAllyRequest ):
    """ Обновить информацию о недавних союзниках """
    action = "reinit_recent_ally"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        self.I.FRIENDS.updateRecentAllies(self.acc.auid, self.onAllyInfoUpdated)

    def onAllyInfoUpdated(self, response):
        if response and response.get("ok"):
            FriendsData_changes = response.get("FriendsData") or []
            if FriendsData_changes:
                try:
                    debug("PersonServerFriendsCmdAction: self.acc.isSendedFriends= %r", self.acc.isSendedFriends)
                    for fname in ("BufferFriendsData", "friendsdata"):
                        if getattr(self.acc, fname ):
                            try:
                                ModelChangeApplicator.apply( self.acc, fname , FriendsData, FriendsData_changes )
                            except ModelChangeApplicatorError as exc:
                                debug("Bad update for %r  error: %r",fname, exc.message)

                except Exception:
                    catch()

            if not self.acc.isSendedFriends:
                self.acc.pending_events.append({"FriendsData": {"FriendsData": FriendsData_changes}})
                if self.acc.pending_handler:
                    self.acc.pending_handler()
                self.sendPendingEvents()
            else:
                info("Reinit_recent_ally.onAllyInfoUpdated self.acc.isSendedFriends=%r", self.acc.isSendedFriends)
        self.response["ok"] = 1
        self.fin()