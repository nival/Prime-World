#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import cfg
from subaction import *
from logic.requests.UpdateDLCRequest import UpdateDLCRequest

class Dlc_update( SubAction, UpdateDLCRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "dlc_update"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.dlcIdx = self.arguments.dlcIdx

    if self.dlcIdx not in cfg.DLCs_INFO:
      self.errorResponse( EC.STEAM_DLC_IS_NOT_EXIST,  "dlc with id=%r not found" % self.dlcIdx)
      return

    if self.dlcIdx not in self.acc.db.dlcs:
      if self.acc.steam and not self.acc.getConfig().DONT_VALIDATE_STEAM_DLC:
        self.acc.steam.checkOwnershipInfo( self.dlcIdx, self.onSteamResponse )
      elif self.acc.getConfig().DONT_VALIDATE_STEAM_DLC:
        warn( "Cheat apply dlc with id=%r for auid=%r" % (self.dlcIdx, self.acc.auid) )
        self.onSteamResponse( True )
    else:
      self.errorResponse( EC.STEAM_DLC_IS_ALREADY_APPLIED,  "dlc with id=%r already applied (%r) for auid=%r" % (self.dlcIdx, self.acc.db.dlcs, self.acc.auid))
      return

    self.response["ok"] = 1
    self.fin()


  def onSteamResponse( self, response ):
    success = False
    if response:
      success = self.I.WS.tryApplyDLCs( [self.dlcIdx], self.acc, self.I )
    
    if not success:
      self.errorResponse( EC.STEAM_DLC_APPLY_ERROR, "DLC %r apply error" % self.dlcIdx)
