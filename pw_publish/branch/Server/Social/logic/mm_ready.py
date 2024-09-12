#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
import MM
from logic.requests.ReadyMatchMakingRequest import ReadyMatchMakingRequest

class Mm_ready( SubAction, ReadyMatchMakingRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "mm_ready"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    try:
      session = self.acc.data.mm
      if self.checkValidParam("mmid"):
        if session and session.mmid == self.mmid:
          if (session.progress == MM.STATUS_GUARDS_LOBBY):
            if not session.is_tambur_ready:
              self.hero_id = session.hero_id
              
              self.I.WS.doMatchmakingCmd( "ready", self.acc, self.mmid ) # убрали параметры героя из "ready"
              session.is_tambur_ready = 1 # второй раз для одной сессии "ready" уже не примем
              
              self.response["mm"] = session
              self.response["mmid"] = session.mmid
              self.response["ok"] = 1
                
            else:
              return self.fail("already checked ready state", EC.GUARDS_ALREADY_READY)
          else:
            return self.fail("wrong session progress, must be in GUARDS LOBBY", EC.READY_BAD_MATCHMAKING_STATE)
        else:
          return self.fail("bad or unfinished matchmaking session id", EC.MM_BAD_MMID)
    except:
      catch()
      return self.fail("exception: bad or unfinished matchmaking session id", EC.MM_BAD_MMID)

    self.fin()
    
    
