#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.DeclineFriendRequest import DeclineFriendRequest

class Decline_friend( SubAction, DeclineFriendRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "decline_friend"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    friend = self.arguments.friend
    model = self.acc.model
    
    if friend.id in model.Friends.IncomingInvites:      
      model.Friends.IncomingInvites.remove(friend.id)
    else:
      self.errorResponse( "No friend invitation from selected person" )
      return

    self.response["ok"] = 1 # success
    self.fin()