#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AcceptFriendRequest import AcceptFriendRequest

class Accept_friend( SubAction, AcceptFriendRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "accept_friend"

  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.friend = self.arguments.friend

    self.model = self.acc.model

    if self.friend.id in self.model.Friends.IncomingInvites:
      self.I.PS.addFriend(self.acc.auid, self.friend.person_uid, self.onAdd)      
      return None      
    else:
      self.errorResponse( "No friend invitation from selected person" )
      return


  @model_callback
  @action_timing
  def onAdd( self, response ):
    #проверить ответ
    self.model.Friends.IncomingInvites.remove(self.friend.id)
    self.acc.db.CountOfAllFriends +=  1
    self.response["ok"] = 1
    self.fin()