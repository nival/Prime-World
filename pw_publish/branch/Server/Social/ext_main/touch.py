# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging

sys.path.append( os.path.abspath('..') )
from subaction import SubAction, action_timing

sys.path.append( os.path.abspath('../base') )
from helpers import *

## ---------------------------------------------------------------
## ---------------------------------------------------------------

class TouchAction( SubAction ):
    """ совсем ничего не делаем, только поддерживаем сессию юзера на сервере """
    action = "touch"
    
    @action_timing
    def onStart(self):
        """ стартовый метод для обработки action """
        info( "touch (uid=%d)" % self.acc.uid )
        self.response["ok"] = 1
        self.fin()

