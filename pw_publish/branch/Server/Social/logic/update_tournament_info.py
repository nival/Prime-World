#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from enums import *
from logic.requests.UpdateTournamentInfoRequest import UpdateTournamentInfoRequest
import cfg

class Update_tournament_info( SubAction, UpdateTournamentInfoRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "update_tournament_info"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    # синхронизуем билет только из SST PF-79526
    if not cfg.TOURNAMENT_SERVER:
      return

    if self.arguments.type == "del":
      self.acc.model.TournamentInfo.TournamentTicket.State = TicketState.NotActivated
      self.acc.model.TournamentInfo.TournamentTicket.TicketId = ""
      self.acc.model.TournamentInfo.TournamentTicket.LastGameTime = 0
      self.acc.model.TournamentInfo.TournamentTicket.Wins = 0
      self.acc.model.TournamentInfo.TournamentTicket.Losses = 0
      self.acc.model.TournamentInfo.TournamentTicket.UserAuid = 0
      self.acc.model.TournamentInfo.TournamentTicket.TicketPriseState = TicketPriseState.HasNoPrise
      for id in xrange( 0, len(self.acc.model.TournamentInfo.TournamentTicket.GameDurations) ):
        self.acc.model.TournamentInfo.TournamentTicket.GameDurations.pop()
    elif self.arguments.type == "lost":
      self.acc.model.TournamentInfo.TournamentTicket.State = TicketState.TournamentLost
      self.acc.model.TournamentInfo.TournamentTicket.Losses += 1
      self.acc.model.TournamentInfo.TournamentTicket.LastGameTime = int( time.time() )
      self.acc.model.TournamentInfo.TournamentTicket.GameDurations.append( 100 )
    elif self.arguments.type == "win":
      self.acc.model.TournamentInfo.TournamentTicket.Wins += 1
      self.acc.model.TournamentInfo.TournamentTicket.LastGameTime = int( time.time() )
      self.acc.model.TournamentInfo.TournamentTicket.GameDurations.append( 100 )
    elif self.arguments.type == "defeat":
      self.acc.model.TournamentInfo.TournamentTicket.Losses += 1
      self.acc.model.TournamentInfo.TournamentTicket.LastGameTime = int( time.time() )
      self.acc.model.TournamentInfo.TournamentTicket.GameDurations.append( 100 )
    elif self.arguments.type == "time":
      self.acc.model.TournamentInfo.TournamentTicket.LastGameTime = self.arguments.time
    elif self.arguments.type == "timeDodge":
      self.acc.model.TournamentInfo.TournamentTicket.Losses += 1
      self.acc.model.TournamentInfo.TournamentTicket.LastGameTime = self.arguments.time
      self.acc.model.TournamentInfo.TournamentTicket.State = TicketState.TournamentLost
    elif self.arguments.type == "prise":
      self.acc.model.TournamentInfo.TournamentTicket.TicketPriseState = TicketPriseState.HasNoPrise
      self.acc.model.TournamentInfo.TournamentTicket.State = TicketState.TournamentLost
      self.acc.model.TournamentInfo.TournamentTicket.Losses = 1

    self.acc.model.TournamentInfo.TournamentTicket.IsSynchronized = False
    self.acc.model.TournamentInfo.sendTournamentTicket( self.acc, self.I.HTTP )

    self.response["ok"] = 1 # success
    self.fin()
