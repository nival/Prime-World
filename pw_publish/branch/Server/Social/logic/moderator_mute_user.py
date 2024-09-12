# -*- coding: utf-8 -*-
import sys
import base64
from subaction import *
from logic.requests.ModeratorMuteUserRequest import *
from ext_pw.sexchange import FindNickAuidAction

class Moderator_mute_user( SubAction, ModeratorMuteUserRequest ):
    """Выдаём юзеру молчанку, если достаточно прав на это"""
    action = "moderator_mute_user"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        if not self.acc.db.IsModerator:
            self.errorResponse(EC.ONLY_MODERATOR_CAN_OPERATE, "Only moderator can mute")
            return

        self.chatLog = self.getParam('post_data', "").replace(' ','+') #уберем на всякий случай пробелы
        action = FindNickAuidAction(acc=self.acc, I=self.I, nick=self.arguments.mutedPlayer,
                                    fin_callback=self.onSearchFriend )
        return action.onStart()


    @model_callback
    @action_timing
    def onSearchFriend( self, response ):
        if response:
            info("Moderator_mute_user.onSearchFriend: %r", response)
            player_auid = response.get("auid", 0)

            if player_auid:
                muteTime = 0
                if self.arguments.muteHours:
                    muteTime = int(time.time()) + self.arguments.muteHours * 60 * 60
                args = [{"type": "add_mute", "muteTime": muteTime}]
                self.I.SEX.sendMail("pw", player_auid, args, from_auid=self.acc.auid, from_sid=self.acc.sex_sid,
                                    from_server=self.acc.sex_server, callback=None)
                self.I.STATS.addModeratorMuteUser(player_auid, self.acc.db.nick,
                                                  self.arguments.muteHours * 60, self.chatLog)

                self.response["ok"] = 1
                self.fin()
                return

        self.errorResponse( EC.FRIEND_NOT_FOUND, "Player not found", { "player_name" : self.arguments.mutedPlayer })