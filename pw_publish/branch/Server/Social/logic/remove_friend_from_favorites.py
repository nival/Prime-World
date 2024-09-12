#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveFriendFromFavoritesRequest import RemoveFriendFromFavoritesRequest

class Remove_friend_from_favorites( SubAction, RemoveFriendFromFavoritesRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "remove_friend_from_favorites"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    friend_uid = self.arguments.friend_uid

    if self.acc.friendsdata.findPersonByUid( friend_uid ):
      self.acc.model.Friends.Favorites.remove(friend_uid)      
    else:
      self.errorResponse( "Friend is not found" )
      return
    
    self.response["ok"] = 1 # success
    self.fin()