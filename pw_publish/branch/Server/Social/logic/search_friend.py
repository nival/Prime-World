#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SearchFriendRequest import SearchFriendRequest

class Search_friend( SubAction, SearchFriendRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "search_friend"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    name = self.arguments.friend_name
    
    self.response["ok"] = 1
    self.fin()