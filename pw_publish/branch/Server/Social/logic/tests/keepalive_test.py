#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
sys.path.append('../')
from logic.keepalive import *
from binascii import crc32
from base.helpers import *
from enums import TicketState
from enums import TicketPriseState

import pwconst

class keepalive_test:

  def keepalive_test( self, env ):
    modeldata = env.acc.model
        
    requests = [ ( Keepalive, KeepaliveRequest( modeldata, { "counter" : [0] }, False ) ) ]
    changeList = env.execActions( requests )
    

  def keepalive_reset_gold_lamp_test( self, env ):
    md = env.acc.model
    md.MarketingEventsInfo.LampEventInfo.EndTime = time.time() + 100500
    md.MarketingEventsInfo.LampEventInfo.dbId = "qwerty"
    
    f = Keepalive( KeepaliveRequest( md, { "counter" : [0] } ), env.callback, request=env )
    f.onStart() 

    assert md.MarketingEventsInfo.LampEventInfo.dbId == "qwerty"
    
  def keepalive_reset_gold_lamp2_test( self, env ):
    md = env.acc.model
    md.MarketingEventsInfo.LampEventInfo.EndTime = time.time() -10
    md.MarketingEventsInfo.LampEventInfo.dbId = "qwerty"
    
    f = Keepalive( KeepaliveRequest( md, { "counter" : [0] } ), env.callback, request=env )
    f.onStart() 

    assert md.MarketingEventsInfo.LampEventInfo.dbId == ""

  def keepalive_give_gold_for_tournament_test( self, env ):
    md = env.acc.model
    config = env.I.Config.getConfig( env.acc.userlocale )

    md.TournamentInfo.TournamentTicket.UserAuid = env.acc.auid
    md.TournamentInfo.TournamentTicket.State = TicketState.TournamentLost
    md.TournamentInfo.TournamentTicket.Losses = 1
    md.TournamentInfo.TournamentTicket.Wins = 2
    md.TournamentInfo.TournamentTicket.TicketPriseState = TicketPriseState.HasNoPrise

    oldGold = md.Resources.Gold

    f = Keepalive( KeepaliveRequest( md, { "counter" : [0] } ), env.callback, request=env )
    f.onStart()

    assert md.TournamentInfo.TournamentTicket.TicketPriseState == TicketPriseState.HasPrise