# -*- coding: utf-8 -*-
#!/usr/bin/env python

import sys, urllib2
from base.helpers import *
import cfg
from enums import *
import datetime
import TournamentTicket
from tornado.httpclient import HTTPRequest
import functools

class TournamentInfo_base:
  def serializeToFile( self, file, name ):
    pass


  def sendTournamentTicket( self, acc, http ):
    self.acc = acc
    # синхронизуем билет только из SST PF-79526
    if not cfg.TOURNAMENT_SERVER:
      return

    try:
      ticketInfo = json_dumps( [{"type":"ticket_info", "auid":acc.db.auid, "State":self.TournamentTicket.State,
                              "TicketId":self.TournamentTicket.TicketId, "LastGameTime":self.TournamentTicket.LastGameTime,
                              "Wins":self.TournamentTicket.Wins, "Losses":self.TournamentTicket.Losses,
                              "UserAuid":self.TournamentTicket.UserAuid, "TicketBoughtType":self.TournamentTicket.TicketBoughtType,
                              "GameDurations":self.TournamentTicket.GameDurations.list, "SessionInfo":self.TournamentTicket.SessionInfo.list}] )
      SENDER = "%s:%s" % ("em", 0)
      self.post( http, "send_nl", project="pw", recipient=acc.db.auid, sender=SENDER, body=ticketInfo, server=cfg.TOURNAMENT_XSERVER_ADDR, callback=self.onSync )
    except:
      catch()
      err( "FAILED sendTournamentTicket" )


  def post( self, http, method, body="", server='se', callback=None, **kwargs ):
    params = dict( **kwargs )
    params["method"] = method
    req = makeSignedRequest( params )

    url = "%s/%s?%s" % (server, 'se', req)

    headers = { "Accept-Encoding": "text/plain" }
    request = HTTPRequest( url=url, method="POST", headers=headers, body=body, connect_timeout=20.0, request_timeout=20.0 )

    try:
      http.fetch( request, callback )
    except:
      catch()
      callback( None )


  def onSync( self, response ):
    info( "onSync %r", response )
    if response and (not response.error) and len(response.body) > 0:
      result = jsonResult( response )
      if result.get("response", None) and result["response"].get("ok", None):
        self.acc.model.write( self.acc.pending )
        self.acc.pending.setPrefix( "ticket:" )
        self.acc.model.setComment( "auto" )
        self.TournamentTicket.IsSynchronized = True


  @staticmethod
  def getGoldAndMaxGameDuration(tournamentTicket, config):
    if tournamentTicket.Wins != 0:
      gold = config.TournamentSettings.GOLDEN_PRISE_AMOUNT*2**(tournamentTicket.Wins - 1)
    else:
      gold = 0
    reply = dict(gold=gold, maxGameDuration = max(tournamentTicket.GameDurations or (0.0,)))
    return reply


  def createTicket( self, auid, boughtType ):
    self.TournamentTicket.UserAuid = auid
    self.TournamentTicket.TicketId = "Tournament1"
    self.TournamentTicket.State = TicketState.InTournament
    # TODO: заменить на верное время из конфигов!!!
    self.TournamentTicket.LastGameTime = 1
    self.TournamentTicket.TicketBoughtType = boughtType


  def isSecondGame( self ):
    curTime = datetime.datetime.now()
    lastTime = datetime.datetime.fromtimestamp( float(self.TournamentTicket.LastGameTime) )
    if curTime.day == lastTime.day and curTime.month == lastTime.month and curTime.year == lastTime.year:
      return True
    return False


  def clearTicket( self, modeldata ):
    self.TournamentTicket.State = 0
    self.TournamentTicket.TicketId = ""
    self.TournamentTicket.LastGameTime = 0
    self.TournamentTicket.Wins = 0
    self.TournamentTicket.Losses = 0
    self.TournamentTicket.UserAuid = 0
    self.TournamentTicket.TicketPriseState = 0
    self.TournamentTicket.TicketBoughtType = 0
    self.TournamentTicket.MissedGames = 0
    self.TournamentTicket.IsSynchronized = True
    for id in xrange( 0, len(self.TournamentTicket.GameDurations) ):
        self.TournamentTicket.GameDurations.pop()
    for id in xrange( 0, len(self.TournamentTicket.SessionInfo) ):
        self.TournamentTicket.SessionInfo.pop()
    
