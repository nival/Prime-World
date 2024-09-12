#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddFriendToFavoritesRequest import AddFriendToFavoritesRequest

class Add_friend_to_favorites( SubAction, AddFriendToFavoritesRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_friend_to_favorites"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    friend_uid = self.arguments.friend_uid
    friend = self.acc.friendsdata.findPersonByUid( friend_uid )
    if friend != None:
      if self.acc.getConfigValue("FAVORITE_FRIENDS_LIMIT") > len(self.acc.model.Friends.Favorites):
        if not friend.person_uid in self.acc.model.Friends.Favorites:
          self.acc.model.Friends.Favorites.append(friend.person_uid)
          self.response["ok"] = 1
        else:
          self.errorResponse( "Friend is already in favorites")
          return
      else:
        self.errorResponse( EC.FAVORITE_FRIENDS_LIMIT, "FAVORITE_FRIENDS_LIMIT", {'limit':self.acc.getConfigValue("FAVORITE_FRIENDS_LIMIT")} )
        return
    else:
      self.errorResponse( "Friend is not found")
      return
    
    self.fin()