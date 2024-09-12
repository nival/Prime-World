# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, re

from subaction import SubAction, action_timing
from base.helpers import *
from tornado.options import options

from geo_cfg import GEO_LOCATIONS

## ---------------------------------------------------------------
## ---------------------------------------------------------------

class SetGeoLocationAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "set_geolocation"
    
    ## клиент присылает правильно сгенерированную "цифровую подпись" (key), и заодно может получить в ответ persistent данные юзера (если уже загрузились)
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        possible_geo_locations = GEO_LOCATIONS[:]
        possible_geo_locations.append("RESET") # допускаем сброс геолокации
        if self.checkPossibleParam("geolocation", possible_geo_locations):
            loaded = toint(self.acc.loaded)
            self.response["loaded"] = loaded
            if loaded:
                if self.geolocation != "RESET":
                    self.acc.db.geolocation = self.geolocation 
                else:
                    self.acc.db.geolocation = ""
                
                self.acc.geolocation = self.acc.db.geolocation or self.acc.geolocation or DEFAULT_GEO_LOCATION
                info( "new acc.db.geolocation: %r, acc.geolocation: %r (uid=%d)" % (self.acc.db.geolocation, self.acc.geolocation, self.acc.uid) )
                            
                self.response["geolocation"] = self.acc.geolocation
                self.response["db"] = self.acc.db
                self.response["ok"] = 1
            else:
                self.response["error"] = "persistent data not loaded, please wait"
            
        self.fin()

