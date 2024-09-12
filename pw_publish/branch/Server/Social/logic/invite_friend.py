#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.InviteFriendRequest import InviteFriendRequest

class Invite_friend( SubAction, InviteFriendRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "invite_friend"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.friendsdata.inviteFriend( self.I.SEX, self.acc, self.arguments.friend_uid )

    self.response["ok"] = 1
    self.fin()
