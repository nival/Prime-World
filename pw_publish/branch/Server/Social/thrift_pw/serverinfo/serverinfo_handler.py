# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging

sys.path.append( os.path.abspath('thrift_pw/serverinfo/gen-py') )
from serverinfo import ServerInfo
from serverinfo.ttypes import *

class ServerInfoHandler( ServerInfo.Iface ):

    def __init__(self, thrift_handler):
        self.log = {}
        self.ISS = thrift_handler.I.WS

    @staticmethod
    def getProcessorClass():
        return ServerInfo.Processor
    
    # ---- ServerInfo.Iface ----
    def getServers(self):
        res_servers = []
        for name,data in self.ISS.getServers().items():
            s = Server()
            s.name = name
            s.addr = data.get("addr", "")
            s.on = data.get("on", 0)
            s.rdy = data.get("rdy", 0)
            s.ka = data.get("ka", 0)
            res_servers.append(s)
        return res_servers

