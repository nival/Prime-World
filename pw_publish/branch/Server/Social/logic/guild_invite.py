#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from ext_pw.sexchange import FindNickAuidAction
from logic.requests.GuildInviteRequest import GuildInviteRequest

class Guild_invite( SubAction, GuildInviteRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "guild_invite"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    if not self.acc.db.guildAuid:
      self.errorResponse( EC.NOT_IN_GUILD,  "You're not in guild" )
      return

    self.I.GS.inviteToGuild( self.acc, self.onInviteGuild )    

    
  @model_callback
  @action_timing
  def onInviteGuild( self, response ):
    if response:
      isOk = response.get("ok") or 0
      msg = response.get("error") or ""
      self.guildName = response.get("guildName") or ""
      if isOk:
        if self.arguments.friend_uid:
          self.addInvite( self.arguments.friend_uid )
        else:
          action = FindNickAuidAction( acc=self.acc, I=self.I, nick=self.arguments.friend_name, fin_callback=self.onSearchFriend )
          return action.onStart()
      else:
        err("Can not invite: %r" % msg )
        self.response["ok"] = 1
        self.fin()


  @model_callback
  @action_timing
  def onSearchFriend( self, response ):
    if response:
      info( "onSearchFriend: %r" % response )
      friend_auid = response.get("auid", 0)
      if friend_auid:
        self.addInvite( friend_auid )
      else:   
        self.errorResponse( EC.FRIEND_NOT_FOUND, "Friend not found", { "friend_name" : self.arguments.friend_name })
        return


  def addInvite( self, friend_auid ):
    if friend_auid != self.acc.auid:
      ourInfo = [{"type":"invite_guild", "person_uid":self.acc.auid, "nickName":self.acc.nick, "photoUrl":self.acc.db.photoUrl, 
                  "guildAuid":self.acc.db.guildAuid, "guildName":self.guildName}]
      self.I.SEX.sendMail( "pw", friend_auid, ourInfo, from_auid=self.acc.auid, from_sid=self.acc.sex_sid, from_server=self.acc.sex_server )
    else:
      warn("friend_auid(%s) == self.acc.auid(%s)" % (friend_auid, self.acc.auid))
      
    self.response["ok"] = 1
    self.fin()
