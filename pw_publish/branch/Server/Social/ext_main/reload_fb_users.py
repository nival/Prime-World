# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging
from subaction import SubAction, action_timing
from helpers import *
import EC

## ---------------------------------------------------------------
## ---------------------------------------------------------------


class ReloadFbUsersAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "reload_fb_users"
    
    @action_timing
    def onStart(self):
        self.fail("OBSOLETE action", EC.BAD_PARAM)

