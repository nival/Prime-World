#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveFriendRequest import RemoveFriendRequest


class Remove_friend(SubAction, RemoveFriendRequest):
    """action, который будет обрабатывать данный класс"""
    action = "remove_friend"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.friend_uid = self.arguments.friend_uid
        if self.acc.db.guildAuid:
            self.I.GS.isGuildMember(self.acc, self.friend_uid, self.acc.db.guildAuid, self.OnFriendChecked)
            return

        self.I.PS.deleteFriend(self.acc.auid, self.friend_uid, self.onRemoveFriend)
        return None

    @action_timing
    def OnFriendChecked(self, response):
        debug("OnFriendChecked response: %s", response)
        code = response["is_member"]
        if code == True:
            self.errorResponse(EC.FRIEND_IS_IN_YOUR_GUILD, "GuildMembers are not allowed to be deleted from friends")
        else:
            self.I.PS.deleteFriend(self.acc.auid, self.friend_uid, self.onRemoveFriend)

    @model_callback
    @action_timing
    def onRemoveFriend(self, response):
        if response:
            if self.acc.friendsdata.findPersonByUid(self.friend_uid):
                if self.friend_uid in self.acc.model.Friends.Favorites:
                    self.acc.model.Friends.Favorites.remove(self.friend_uid)
        c = self.acc.db.CountOfAllFriends - 1
        self.acc.db.CountOfAllFriends = c if c >= 0 else 0
        # проверить ответ
        self.response["ok"] = 1
        self.fin()
