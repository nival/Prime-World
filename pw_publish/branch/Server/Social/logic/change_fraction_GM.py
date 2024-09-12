#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from change_fraction import *
import tornado.options
from tornado.options import define, options
import cfg


class Change_fraction_GM( Change_fraction, ChangeFractionRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "change_fraction_gm"
  debug = True

  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if self.acc.db.guildAuid:
      self.I.GS.subscribe( self.acc, self.acc.snid, self.acc.snuid, self.acc.uid, options.server_id, self.acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE, self.onGuildDataCallback )
    else:
      self.onGuildDataCallback( None )


  def onGuildDataCallback( self, response ):
    if self.acc.db.fraction != self.arguments.fraction and self.acc.db.fraction != 'N':
      self.changeFraction()
      self.response["ok"] = 1 # success 

    self.fin()