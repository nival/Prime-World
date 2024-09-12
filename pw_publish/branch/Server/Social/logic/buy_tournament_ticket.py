#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, urllib
from subaction import *
from tornado.httpclient import HTTPRequest
import cfg, base64
import ibilling
from logic.requests.BuyTournamentTicketRequest import BuyTournamentTicketRequest

class Buy_tournament_ticket( SubAction, BuyTournamentTicketRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_tournament_ticket"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if self.acc.db.auid in cfg.TOURNAMENT_SPECTATOR_AUIDS:
      self.errorResponse( EC.TOURNAMENT_SPECTATOR_CANNOT_BUY_TICKET, "Spectator can not buy ticket" )
      return

    if not self.acc.model.canBuyTicket( self.acc ):
      self.errorResponse( "Action is over" )
      return

    if self.acc.model.TournamentInfo.TournamentTicket.UserAuid != 0:
      self.errorResponse( "User already has a tournament ticket" )
      return

    if self.acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER:
      self.errorResponse( "Can't buy tickets on tournament server" )
      return

    self.price = None
    if self.arguments.paymentType == TicketPaymentType.Gold:
      self.boughtType = TicketBoughtType.BoughtForGold
      self.price = self.acc.model.createResourcesTable( Gold = int(self.I.Config.getMainConfig().TournamentSettings.GOLDEN_TICKET_PRICE ))
    if self.arguments.paymentType == TicketPaymentType.Silver:
      self.boughtType = TicketBoughtType.BoughtForSilver
      self.price = self.acc.model.createResourcesTable( Silver = int(self.I.Config.getMainConfig().TournamentSettings.SILVER_TICKET_PRICE ))

    if not self.price:
      self.errorResponse( "Paying method was not provided" )
      return

    if self.getIntParam( "force_free", 0 ) == 1:
      self.boughtType = TicketBoughtType.GivenByGM
      self.onBuy( { "code" : ibilling.ERROR_CODE_OK } )
      return

    self.needGold = int( self.price.Gold )
    reason = "PW!TournamentTicket:" + str( self.arguments.paymentType )
    self.buy( self.price, self.onBuy, self.onBuyFunc, reason )


  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.acc.model.TournamentInfo.createTicket( self.acc.db.auid, self.boughtType )
      if "tournament0_ticket_dlc" not in self.acc.db.dlcs:
        self.I.WS.tryApplyDLCs( ["tournament0_ticket_dlc"], self.acc, self.I )

      #send message to tournament social server
      args = dict( action="create_account", auid=self.acc.db.auid, snid=self.acc.snid, snuid=self.acc.snuid, nickname=self.acc.getNickname(), 
                                            fraction=self.acc.db.fraction, boughtType=self.boughtType )
      req = HTTPRequest( url=cfg.TOURNAMENT_SERVER_ADDR + '/?' + urllib.urlencode(args), method="GET", connect_timeout=20.0, request_timeout=20.0 )
      self.I.HTTP.fetch( req, self.onRegister )
    else:
      self.onBuyError( response, self.needGold )
      return


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )


  @action_timing
  def onRegister( self, response ):
    info( "onRegister: %r", response )
    if response and (not response.error) and len(response.body) > 0:
      result = jsonResult( response )
      if result.get("response", None) and result["response"].get("ok", None):
        info( "Ticket buy OK" )
        self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.BuyTournamentTicket, "", self.price, self.acc.model.Resources ) 
        self.response["ok"] = 1 # success
        self.fin()
        return

    # ошибка
    self.acc.model.TournamentInfo.clearTicket( self.acc.model )
    if self.boughtType == TicketBoughtType.BoughtForGold and int(self.price.Gold) != 0:
      self.I.BILL.replenish( self.acc.db.auid, int(self.price.Gold), "For fail buy ticket", None )
    elif self.boughtType == TicketBoughtType.BoughtForSilver:
      self.acc.model.sell( self.price, self.acc )

    self.errorResponse( EC.TOURNAMENT_BUY_FAIL, "Fail buy ticket" )
