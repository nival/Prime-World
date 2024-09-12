#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, time
from subaction import *
from datetime import date
import MM
import chat_utils
import pwconst
import isteam
import EC
import iaeria
import iarcgames
import izzimacom
import enums
from logic.requests.KeepaliveRequest import KeepaliveRequest

##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------
class Keepalive( SubAction, KeepaliveRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "keepalive"
  ## раз в N минут клиент напоминает, что жив
  """стартовый метод для обработки action"""
  # декоратор model_callback должен автоматически направлять model changes от нашего ModelData в self.response["model"] нашего хэндлера (SubAction)
  @action_timing
  @model_callback
  @parse
  def onStart(self):
    debug("Keepalive.onStart auid=%s, ka=%s", self.acc.auid, self.acc.ka)
    # Если запрашивают друзей, то возможно нет ModelData и даем только друзей
    if self.arguments.onlyFriends:
      self.sendPendingEvents()
      self.response["ok"] = 1
      self.fin()
      return

    counter = self.arguments.counter or 0

    self.log()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateGuildWarEvent == 0:
      self.updateGuildWarEvent()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateFirstDayWin == 0:
      self.updateFirstDayWin()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateBuildingsProduction == 0:
      self.updateBuildingsProduction()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateGold == 0:
      self.updateGold()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateFameToPersonServer == 0:
      self.updateFameToPersonServer()

    if counter % pwconst.KEEPALIVE_TIMINGS.updatePartyInfo == 0:
      self.updatePartyInfo()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateGoldLamp == 0:
      self.updateGoldLamp()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateDodgesStatus == 0:
      self.updateDodgesStatus()

    if counter % pwconst.KEEPALIVE_TIMINGS.sendPendingMessages == 0:
      self.sendPendingMessages()

    if counter % pwconst.KEEPALIVE_TIMINGS.sendPendingEvents == 0:
      self.sendPendingEvents() #### WORKAROUND АП8: keepalive возвращает и все "long-polling евенты", ждущие action=ping

    if counter % pwconst.KEEPALIVE_TIMINGS.updateGuildBonuses == 0:
      self.updateGuildBonuses()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateDynQuests == 0:
      #self.I.WS.checkDynamicQuests(self.acc)
      self.updateDynamicQuests()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateEventMap == 0:
      self.updateEventMap()

    if counter % pwconst.KEEPALIVE_TIMINGS.updateRerollShop == 0:
      self.updateRerollShop()

    self.response["ok"] = 1

    if self.acc.auid:
        self.I.WS.refreshLoginToken( self.acc.auid )
        self.I.WS.updateKeepaliveState( self.acc, online=True, now=time.time() )

    try:
        l = self.acc.login.lower()
        if l in repeated_requests["auth"]:
            repeated_requests["auth"].pop(l)
    except:
        pass

    debug("keepalive before fin response %r", self.response)
    self.fin()

  @separate_timing
  def updateDynamicQuests(self):
    try:
      self.I.WS.checkDynamicQuests(self.acc)
    except:
      catch()

  @separate_timing
  @model_callback
  def updateBuildingsProduction( self ):
    try:
      rid = 0
      if self.arguments.rid:
        rid = self.arguments.rid
      for buildingId in self.acc.model.Buildings:
        building = self.acc.model.getConstructionByID( buildingId )
        if building and building.EndProductionTime != 0 and building.EndProductionTime < int(round(time.time())) and building.ProductionState == ProductionState.Busy:
          building.ProductionState = ProductionState.Finished
      self.acc.model.validateTavern(self.acc.SD, self.acc.getConfig(), int(rid))
    except:
      catch()


  @separate_timing
  @model_callback
  def updateFirstDayWin( self ):
    self.acc.model.resetComplaints( self.acc )
    self.acc.model.updateFirstDayWin()

  @separate_timing
  @model_callback
  def updateGold( self ):
    try:
      self.acc.model.updateBalanceInfo(self.acc, self.I.BILL)

      #TODO: реализовать общий механизма для обновления оплат из соц. сетей
      #      пока разнес по методам
      if self.acc.db.steamOrders:
        self.updateSteamGold()

      elif self.acc.db.aeriaOrders:
        self.updateAeriaGold()

      elif self.acc.db.arcgamesOrders:
        self.updateArcgamesGold()

      elif self.acc.db.zzimacomOrders:
        self.updateZZimacomGold()


      # Выдаём золото за победу на турнире
      if (self.acc.model.TournamentInfo.TournamentTicket.UserAuid == self.acc.db.auid and self.acc.model.TournamentInfo.TournamentTicket.TicketPriseState == TicketPriseState.HasNoPrise
          and not self.acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER):
        if self.acc.model.TournamentInfo.TournamentTicket.State == TicketState.TournamentLost:
          if self.acc.model.TournamentInfo.TournamentTicket.Wins != 0:
            self.I.BILL.replenish( self.acc.db.auid, self.acc.getConfig().TournamentSettings.GOLDEN_PRISE_AMOUNT*2**(self.acc.model.TournamentInfo.TournamentTicket.Wins - 1), "Tournament win bonius", self.onGivePrise )
            self.acc.model.TournamentInfo.TournamentTicket.TicketPriseState == TicketPriseState.PriseInProgress
    except:
      catch()
      return 1

    return 1

  def updateSteamGold(self):
    for txnid, steamInfo in self.acc.db.steamOrders.items():
      curTime = int( round( time.time() ) )
      # Чистим неподтвержденные ордеры ( 3 мин таймаут )
      if steamInfo["orderStatus"] >= isteam.STEAM_ORDER_STATUS_CONFIRM and (curTime - steamInfo["orderTime"]) > isteam.STEAM_REPLENISH_TIMEOUT:
        err("Steam order %s timed out (%s sec) with status %s", txnid, isteam.STEAM_REPLENISH_TIMEOUT, steamInfo["orderStatus"])
        if self.acc.steam:
            self.acc.steam.cancelTransaction(txnid, steamInfo["orderCode"])
        del self.acc.db.steamOrders[txnid]
      # Чистим зависшие ордеры ( 2 часа таймаут )
      elif (curTime - steamInfo["orderTime"]) > isteam.STEAM_ORDER_TIMEOUT:
        err("Steam order %s timed out (%s sec) with status %s", txnid, isteam.STEAM_ORDER_TIMEOUT, steamInfo["orderStatus"])
        if self.acc.steam:
            self.acc.steam.cancelTransaction(txnid, steamInfo["orderCode"])
        del self.acc.db.steamOrders[txnid]

  def updateAeriaGold(self):
    for transId in self.acc.db.aeriaOrders.keys():
      order = self.acc.db.aeriaOrders[transId]
      if order["status"] == iaeria.AERIA_LG_START_TRANSACTION:
        if order["try"] < iaeria.AERIA_LG_TRANSACTION_FASTTRY and (int( time.time() ) - order["time"]) > iaeria.AERIA_LG_TRANSACTION_TIMEOUT:
          warn( "Aeria fast retry start transaction %r %r" % (transId,order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["aeria_info"]
          self.acc.aeria.startTransaction( transId, itemId, description, price, callback )
        elif order["try"] < iaeria.AERIA_LG_TRANSACTION_FASTTRY+iaeria.AERIA_LG_TRANSACTION_MAXTRYS and \
             (int( time.time() ) - order["time"]) > iaeria.AERIA_LG_TRANSACTION_LONGTIMEOUT:
          warn( "Aeria slow retry start transaction %r %r" % (transId,order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["aeria_info"]
          self.acc.aeria.startTransaction( transId, itemId, description, price, callback )
        elif order["try"] >= iaeria.AERIA_LG_TRANSACTION_FASTTRY+iaeria.AERIA_LG_TRANSACTION_MAXTRYS:
          err( "Aeria stop retry start transaction %r %r" % (transId, order) )
          self.acc.db.aeriaOrders.pop( transId, None )

      elif order["status"] == iaeria.AERIA_LG_REPLENISH:
        if order["try"] < iaeria.AERIA_LG_REPLENISH_FASTTRY and (int( time.time() ) - order["time"]) > iaeria.AERIA_LG_REPLENISH_TIMEOUT:
          warn( "Aeria fast retry replenish %r %r" % (transId,order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["aeria_info"]
          callback = functools.partial( self.acc.model.onAeriaReplenish, txnid=transId, acc=self.acc )
          self.I.AERIA_PS.replenish( self.acc.db.auid, int(gold), int(price), "AE", transId, callback )
        elif order["try"] < iaeria.AERIA_LG_REPLENISH_FASTTRY+iaeria.AERIA_LG_REPLENISH_MAXTRYS and \
             (int( time.time() ) - order["time"]) > iaeria.AERIA_LG_REPLENISH_LONGTIMEOUT:
          warn( "Aeria slow retry replenish %r %r" % (transId,order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["aeria_info"]
          callback = functools.partial( self.acc.model.onAeriaReplenish, txnid=transId, acc=self.acc )
          self.I.AERIA_PS.replenish( self.acc.db.auid, int(gold), int(price), "AE", transId, callback )
        elif order["try"] >= iaeria.AERIA_LG_TRANSACTION_FASTTRY+iaeria.AERIA_LG_TRANSACTION_MAXTRYS:
          err( "Aeria stop retry replenish %r %r" % (transId,order) )
          self.acc.db.aeriaOrders.pop( transId, None )

  def updateArcgamesGold(self):
    for transId in self.acc.db.arcgamesOrders.keys():
      order = self.acc.db.arcgamesOrders[transId]
      if order["status"] == iarcgames.ARCGAMES_LG_START_TRANSACTION:
        if order["try"] < iarcgames.ARCGAMES_LG_TRANSACTION_FASTTRY and (int( time.time() ) - order["time"]) > iarcgames.ARCGAMES_LG_TRANSACTION_TIMEOUT:
          warn( "Arcgames fast retry start transaction %r %r" % (transId, order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["arcgames_info"]
          self.acc.arcgames.startTransaction( transId, itemId, description, price, callback )
        elif order["try"] < iarcgames.ARCGAMES_LG_TRANSACTION_FASTTRY+iarcgames.ARCGAMES_LG_TRANSACTION_MAXTRYS and \
             (int( time.time() ) - order["time"]) > iarcgames.ARCGAMES_LG_TRANSACTION_LONGTIMEOUT:
          warn( "ArcGames slow retry start transaction %r %r" % (transId,order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["arcgames_info"]
          self.acc.arcgames.startTransaction( transId, itemId, description, price, callback )
        elif order["try"] >= iarcgames.ARCGAMES_LG_TRANSACTION_FASTTRY + iarcgames.ARCGAMES_LG_TRANSACTION_MAXTRYS:
          err( "Arcgames stop retry start transaction %r %r" % (transId, order) )
          self.acc.db.arcgamesOrders.pop( transId, None )

      elif order["status"] == iarcgames.ARCGAMES_LG_REPLENISH:
        if order["try"] < iarcgames.ARCGAMES_LG_REPLENISH_FASTTRY and (int( time.time() ) - order["time"]) > iarcgames.ARCGAMES_LG_REPLENISH_TIMEOUT:
          warn( "Arcgames fast retry replenish %r %r" % (transId, order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["arcgames_info"]
          callback = functools.partial( self.acc.model.onArcGamesReplenish, txnid=transId, acc=self.acc )
          self.I.ARCGAMES_PS.replenish( self.acc.db.auid, int(gold), int(price), "ARC", transId, callback )
        elif order["try"] < iarcgames.ARCGAMES_LG_REPLENISH_FASTTRY + iarcgames.ARCGAMES_LG_REPLENISH_MAXTRYS and \
             (int( time.time() ) - order["time"]) > iarcgames.ARCGAMES_LG_REPLENISH_LONGTIMEOUT:
          warn( "Arcgames slow retry replenish %r %r" % (transId, order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["arcgames_info"]
          callback = functools.partial( self.acc.model.onArcGamesReplenish, txnid=transId, acc=self.acc )
          self.I.ARCGAMES_PS.replenish( self.acc.db.auid, int(gold), int(price), "ARC", transId, callback )
        elif order["try"] >= iarcgames.ARCGAMES_LG_TRANSACTION_FASTTRY + iarcgames.ARCGAMES_LG_TRANSACTION_MAXTRYS:
          err( "ArcGames stop retry replenish %r %r" % (transId, order) )
          self.acc.db.arcgamesOrders.pop( transId, None )

  def updateZZimacomGold(self):
    for transId in self.acc.db.zzimacomOrders.keys():
      order = self.acc.db.zzimacomOrders[transId]
      if order["status"] == izzimacom.ZZIMA_LG_START_TRANSACTION:
        if order["try"] < izzimacom.ZZIMA_LG_TRANSACTION_FASTTRY and (int( time.time() ) - order["time"]) > izzimacom.ZZIMA_LG_TRANSACTION_TIMEOUT:
          warn( "ZZima fast retry start transaction %r %r" % (transId, order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["zzimacom_info"]
          self.acc.zzimacom.startTransaction( transId, itemId, description, price, callback )
        elif order["try"] < izzimacom.ZZIMA_LG_TRANSACTION_FASTTRY + izzimacom.ZZIMA_LG_TRANSACTION_MAXTRYS and \
             (int( time.time() ) - order["time"]) > izzimacom.ZZIMA_LG_TRANSACTION_LONGTIMEOUT:
          warn( "ZZima slow retry start transaction %r %r" % (transId,order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["zzimacom_info"]
          self.acc.zzimacom.startTransaction( transId, itemId, description, price, callback )
        elif order["try"] >= izzimacom.ZZIMA_LG_TRANSACTION_FASTTRY + izzimacom.ZZIMA_LG_TRANSACTION_MAXTRYS:
          err( "ZZima stop retry start transaction %r %r" % (transId, order) )
          self.acc.db.zzimacomOrders.pop( transId, None )

      elif order["status"] == izzimacom.ZZIMA_LG_REPLENISH:
        if order["try"] < izzimacom.ZZIMA_LG_REPLENISH_FASTTRY and (int( time.time() ) - order["time"]) > izzimacom.ZZIMA_LG_REPLENISH_TIMEOUT:
          warn( "ZZima fast retry replenish %r %r" % (transId, order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["zzimacom_info"]
          callback = functools.partial( self.acc.model.onZZimacomReplenish, txnid=transId, acc=self.acc )
          self.I.ZZIMA_PS.replenish( self.acc.db.auid, int(gold), int(price), "ZZIMA", transId, callback )
        elif order["try"] < izzimacom.ZZIMA_LG_REPLENISH_FASTTRY + izzimacom.ZZIMA_LG_REPLENISH_MAXTRYS and \
             (int( time.time() ) - order["time"]) > izzimacom.ZZIMA_LG_REPLENISH_LONGTIMEOUT:
          warn( "ZZima slow retry replenish %r %r" % (transId, order) )
          order["try"] += 1
          order["time"] = int( time.time() )
          itemId, description, price, gold, callback = order["zzimacom_info"]
          callback = functools.partial( self.acc.model.onZZimacomReplenish, txnid=transId, acc=self.acc )
          self.I.ZZIMA_PS.replenish( self.acc.db.auid, int(gold), int(price), "ZZIMA", transId, callback )
        elif order["try"] >= izzimacom.ZZIMA_LG_TRANSACTION_FASTTRY + izzimacom.ZZIMA_LG_TRANSACTION_MAXTRYS:
          err( "ArcGames stop retry replenish %r %r" % (transId, order) )
          self.acc.db.arcgamesOrders.pop( transId, None )

  @separate_timing
  def updateEventMap( self ):
    try:
      self.acc.model.calcEventInfo( self.I.Config.eventMaps, self.acc )
      self.acc.model.calcBanEventInfo(self.acc, self.I.Config.eventMapsForBan, self.I.Config.eventMaps )
      self.acc.model.calcEventSkin( self.I.MD.eventSkins, self.acc )
    except:
      catch()


  @separate_timing
  def updateFameToPersonServer( self ):
    try:
      if ( time.time() - self.acc.model.LordInfo.lastFameUpdateTime_ ) > MM.FAME_PERIOD:
        self.I.WS.updateGameDataToPersonServer( self.acc )
        self.acc.model.LordInfo.lastFameUpdateTime_ = time.time()
    except:
      catch()


  @separate_timing
  def updatePartyInfo( self ):
    try:
      if self.acc.partydata:
        for member_id, member in self.acc.partydata.members.iteritems():
          if member.banEndTime != 0 and member.banEndTime < int(round(time.time())):
            self.I.WS.updatePartyDodge( self.acc )
    except:
      catch()

  @separate_timing
  def updateGoldLamp( self ):
    now = time.time()
    if self.acc.model.MarketingEventsInfo.LampEventInfo.EndTime < now and self.acc.model.MarketingEventsInfo.LampEventInfo.dbId != "":
      self.I.STATS.addRuneExpire( self.acc.auid, self.acc.model.getGoldLampType( self.acc.SD ), \
        self.acc.model.MarketingEventsInfo.LampEventInfo.TransactionsLeft, self.acc.model.MarketingEventsInfo.LampEventInfo.BonusLeft )
      self.acc.model.MarketingEventsInfo.LampEventInfo.dbId = ""

  @separate_timing
  def updateDodgesStatus( self ):
    self.acc.model.updateDodgesStatus( self.acc )

  def onGivePrise(self, response):
    info( "onGivePrise %r", response )
    if response and response.get("code", ibilling.ERROR_CODE_UNKNOWN) == ibilling.ERROR_CODE_OK:
      self.acc.model.TournamentInfo.TournamentTicket.TicketPriseState = TicketPriseState.HasPrise
    else:
      self.acc.model.TournamentInfo.TournamentTicket.TicketPriseState = TicketPriseState.HasNoPrise

  @separate_timing
  @model_callback
  def updateGuildBonuses(self):
    # Если клановые войны не включены, баффы не трогаем
    if not self.acc.getConfig().GUILD_WARS_ENABLED:
      return

    needUpdate = False
    for bonusId in self.acc.model.GuildBufs.keys():
      bonus = self.acc.model.getGuildBufByID(bonusId)
      if bonus.DurationType in [GuildBufDurationType.TimeBased, GuildBufDurationType.Mixed] and bonus.ExpireTime <= int(time.time()):
        self.acc.model.GuildBufs.remove(bonusId)
        needUpdate = True

    if needUpdate:
      self.acc.model.deactivateAllWeakerBonuses(self.acc.SD)

  @separate_timing
  @model_callback
  def updateRerollShop( self ):
    self.acc.model.validateRerollShop(self.acc)

  @separate_timing
  @model_callback
  def updateGuildWarEvent(self):
    try:
      self.I.WS.updateGuildWarEvent(self.acc)
      self.response['GuildWarEventData'] = self.I.WS.getGuildWarEventDataChanges()
    except:
      catch()

