#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from ext_pw.sexchange import FindNickAuidAction
from logic.requests.AddFriendRequest import AddFriendRequest

class Add_friend( SubAction, AddFriendRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_friend"
  
  @model_callback
  @parse
  @action_timing
  def onStart( self ):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    action = FindNickAuidAction( acc=self.acc, I=self.I, nick=self.arguments.friend_name, fin_callback=self.onSearchFriend )
    return action.onStart()
    

  @model_callback
  @action_timing
  def onSearchFriend( self, response ):
    if response:
      info( "onSearchFriend: %r" % response )
      friend_auid = response.get("auid", 0)
      if friend_auid:
        if self.acc.friendsdata:
          self.acc.friendsdata.inviteFriend( self.I.SEX, self.acc, friend_auid )
          self.response["ok"] = 1
          self.fin()
        else:
          self.errorResponse( EC.FRIEND_SERVER_CRASHED, "Friends data was corrupted" )
        return
        
    self.errorResponse( EC.FRIEND_NOT_FOUND, "Friend not found", { "friend_name" : self.arguments.friend_name })
    return
