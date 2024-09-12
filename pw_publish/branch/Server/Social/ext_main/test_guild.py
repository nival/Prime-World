#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, time, logging

sys.path.append( os.path.abspath('..') )
from subaction import SubAction, action_timing

sys.path.append( os.path.abspath('../base') )
from helpers import *
from tornado.options import options
import cfg
import coord_cfg
import pymongo

class TestGuildAction( SubAction ):
  action = "test_guild"
    
  def onStart(self):
    self.acc = ClassDict()
    self.acc.db = ClassDict()
    self.acc.db.guildAuid = 11
    self.acc.db.fraction = 'B'
    self.acc.auid = 12
    self.acc.db.auid = 12
    self.acc.snid = 'fb'
    self.acc.snuid = 13
    self.acc.uid = 14
    self.textFullName = 'nivalTest11'
    self.textShortName = 'nvT11'
    bestHero = 15
    bestHeroRating = 16
    self.I.GS.createGuild( self.acc, self.acc.snid, self.acc.snuid, self.acc.uid, options.server_id, self.acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE, 
                             self.textFullName, self.textShortName, bestHero, bestHeroRating, self.onCreateGuild )

  def onCreateGuild( self, response ):
    if response and response["ok"] == 1:
      for options_dict in coord_cfg.COORDINATOR_MONGO_CONFIG:
        opt = ClassDict( options_dict )
        connection = pymongo.Connection( opt.mongo_addr, opt.mongo_port )
        mongo_db = getattr( connection, opt.mongo_base, None )
        if mongo_db:
          coll = getattr( mongo_db, "guilds" )
          func = getattr( coll, "find" )
          reply = func( { "key" : { "$exists" : True } } )
          for obj in reply:
            guildAuid = tolong( str( obj.get( "key", None ) )[3:] )
            if guildAuid == 11:
              self.response["ok"] = 1
              break
    self.I.GS.destroyGuild( self.acc, self.onDestroyGuild )
    self.fin()


  def onDestroyGuild( self, response ):
    pass
