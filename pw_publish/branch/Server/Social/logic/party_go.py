#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from enums import *
from logic.requests.PartyGoRequest import PartyGoRequest
import cfg
from geo_cfg import DEFAULT_GEO_LOCATION

class Party_go( Party_action, PartyGoRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_go"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      info("Party_go(auid=%s): failed param check" % self.acc.auid)
      return

    if self.I.WS.maintenanceMode != MAINTENANCE_NORMAL:
        ec, em = getMaintenanceInfo(self.I.WS.maintenanceMode)
        self.errorResponse( ec, em, { 'tm' : self.I.WS.maintenanceTime} )
        return

    #if self.acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER and self.acc.model.TournamentInfo.TournamentTicket.State != TicketState.InTournament:
    #  self.errorResponse( EC.TOURNAMENT_CANNOT_MM_GAME_LOST_OR_SPECTATOR, "Cannot MM because lost or spectator" )
    #  return

    isPvpSession = 0
    if not getattr(self.acc.model, "game_type", None):
      self.acc.model.game_type = self.acc.model.LordInfo.LastStartedMap.MapId
    map = self.acc.SD.getObjectByDbid( self.acc.model.game_type )
    try:
      if map and (map['mapType'] in ["CTE", "PvP"]):
        isPvpSession = 1
    except:
      pass

    if self.acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER and self.acc.model.TournamentInfo.isSecondGame() and isPvpSession:
      self.errorResponse( EC.TOURNAMENT_CANNOT_PLAY_SECOND_GAME, "Cannot play second game" )
      return

    #if self.acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER and self.acc.model.TournamentInfo.TournamentState != TournamentState.InProgress:
    #  self.errorResponse( EC.TOURNAMENT_NOT_STARTED, "Cannot play tournament not started" )
    #  return
    
    # для party.go требуются флажок guard_only; берутся они из ModelData лидера партии
    # всем участникам группы надо для ММ ппрописать локаль и геолокацию лидера
    # для играющих через Massive (филиппинцев) необходимо проставить специальную локаль - PF-85549
    msv_hack = self.acc.snid == 'msv' or self.acc.original_snid == 'msv' or self.acc.fsn == 'msv'
    self.addArguments(
        only_guard = toint(self.acc.model.LordInfo.GuardInfo.OnlyGuard), # насильно преобразуем к 0/1
        locale =  cfg.MATCHMAKER_MSV_LOCALE if msv_hack else (self.acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE),
        geolocation = cfg.MATCHMAKER_MSV_GEOLOCATION if msv_hack else (self.acc.geolocation or DEFAULT_GEO_LOCATION),
    )
    return Party_action.onStart(self)
