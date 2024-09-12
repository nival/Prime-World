#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddFakeFriendsRequest import AddFakeFriendsRequest

class Add_fake_friends( SubAction, AddFakeFriendsRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_fake_friends"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    modeldata = self.acc.model
    lof = modeldata.newSimpleFriend( )[0]
    movsic = modeldata.newSimpleFriend( )[0]
    ogorodov = modeldata.newSimpleFriend( )[0]
    zulman = modeldata.newSimpleFriend( )[0]
    aya = modeldata.newSimpleFriend( )[0]
    
    lof.person_uid = 100500
    lof.nickName = "Lofic"
    lof.photoUrl = "http://gyazo.nivalnetwork.com/db/2191c4c92fdc03151d45d255d089ca28.png"
    
    movsic.person_uid = 100501
    movsic.nickName = "movsic"
    movsic.photoUrl = "http://gyazo.nivalnetwork.com/db/2191c4c92fdc03151d45d255d089ca28.png"
    
    ogorodov.person_uid = 100502
    ogorodov.nickName = "ogorodov"
    ogorodov.photoUrl = "http://gyazo.nivalnetwork.com/db/2191c4c92fdc03151d45d255d089ca28.png"
    
    zulman.person_uid = 100503
    zulman.nickName = "zulman"
    zulman.photoUrl = "http://gyazo.nivalnetwork.com/db/2191c4c92fdc03151d45d255d089ca28.png"
    
    aya.person_uid = 100504
    aya.nickName = "aya"
    aya.photoUrl = "http://gyazo.nivalnetwork.com/db/2191c4c92fdc03151d45d255d089ca28.png"
    
    modeldata.Friends.IncomingInvites.add(lof.id)
    modeldata.Friends.IncomingInvites.add(movsic.id)
    modeldata.Friends.IncomingInvites.add(ogorodov.id)
    modeldata.Friends.IncomingInvites.add(zulman.id)
    modeldata.Friends.IncomingInvites.add(aya.id)

    self.response["ok"] = 1
    self.fin()