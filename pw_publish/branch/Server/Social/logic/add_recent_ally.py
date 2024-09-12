# -*- coding: utf-8 -*-
import sys
from subaction import *
from ext_pw.sexchange import FindNickAuidAction
from logic.requests.AddRecentAllyRequest import *

class Add_recent_ally(SubAction, AddRecentAllyRequest):
    """ Добавляем в список союзника (по нику) """
    action = "add_recent_ally"
    debug = True
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        action = FindNickAuidAction(acc=self.acc, I=self.I, nick=self.arguments.nickname, fin_callback=self.onSearchFriend)
        return action.onStart()


    @model_callback
    @action_timing
    def onSearchFriend( self, response ):
        if response:
            info( "onSearchFriend: %r" % response )
            friend_auid = response.get("auid", 0)
            if friend_auid:
                self.I.FRIENDS.addRecentAllies(self.acc.auid, str(friend_auid))
                self.response["ok"] = 1
                self.fin()
            else:
                self.errorResponse( EC.FRIEND_SERVER_CRASHED, "Friends data was corrupted" )
            return

        self.errorResponse( EC.FRIEND_NOT_FOUND, "Friend not found", { "friend_name" : self.arguments.friend_name })
        return