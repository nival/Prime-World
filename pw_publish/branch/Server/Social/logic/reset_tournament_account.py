#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.ban_account import *
from ext_pw import SetFractionAction
from logic.requests.ResetTournamentAccountRequest import ResetTournamentAccountRequest

class Reset_tournament_account( SubAction, ResetTournamentAccountRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "reset_tournament_account"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if not self.I.Config.getMainConfig().TournamentSettings.IS_TOURNAMENT_SERVER:
      self.errorResponse("Can't reset tournament account on SS server, SST required")
      return

    #ACTION LOGIC
    #subParams = ClassDict( minutes=[1], reason=[u"Над Вашим аккаунтом проводятся технические работы, зайдите попозже"], autoBan=[1], rid=[1] )
    #accountAction = Ban_account( subParams, self.callbackBanUser, I=self.I, acc=self.acc, uid=self.acc.uid )
    #accountAction.onStart()
    self.acc.db.banned = True
    self.acc.db.autoban = True
    self.acc.db.bantime = int( round( time.time() ) ) +  60
    self.acc.db.banreason = u"Над Вашим аккаунтом проводятся технические работы, зайдите попозже"

    self.acc.ka = 0
    self.I.DATA.remove( "pers", "pers", {"key": self.acc.pers_key}, self.callbackClearSQLLogin, params=self.acc.uid )

  def callbackClearSQLLogin(self, response):
    info("Reset_tournament_account: clear mongo %r", response)
    self.I.SQL.removeLogin(self.acc.uid, self.acc.login, callback=self.callbackClearSQLNick)

  def callbackClearSQLNick(self, response):
    info("Reset_tournament_account: clear mongo %r", response)
    self.I.SQL.removeNicknameById(self.acc.uid, self.acc.login, callback=self.callbackFinal)

  def callbackFinal(self, response):
    self.acc.do_not_save_mongo = True
    self.response["ok"] = 1
    self.fin()
