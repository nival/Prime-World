# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Social Aggregator Login

import sys, os, time, logging, base64

from handlers import * 
from subaction import SubAction, action_timing

import EC

class LauncherPingAction( SubAction ):
    
    @action_timing
    def onStart(self):
        self.response['ok'] = 1
        self.fin()
