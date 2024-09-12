# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *

import tornado.ioloop
import tornado.options
from tornado.options import define, options

from iwebserver import *
from cluster_serial import SerialModelFactory

def AsyncSModel():
    return tornado.ioloop.IOLoop.instance().smodel

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------
class IAsyncSerialModel:
    """ Реальный интерфейс для общения с async thread pool, создающим и грузящим ModelData
    """
    def __init__(self, iDict, server_version):
        pass
        
    def newSerialModel(self, auid, fraction, sex, guest, db, old_md, Config, SD, userlocale, country_code,isReset, callback):
        """  """
        AsyncSModel().addQuery( "newSerial", (fraction, sex, guest, db, auid, old_md, Config, SD, userlocale, country_code, isReset), callback )
        
    def loadSerialModel(self, uid, model_string, fraction, sex, db, sn_count, Config, SD, userlocale, country_code, callback):
        """  """
        AsyncSModel().addQuery( "loadSerial", (uid, model_string, fraction, sex, db, sn_count, Config, SD, userlocale, country_code), callback, params=uid )

    def destroy(self):
        AsyncSModel().destroy()

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------
class ISyncSerialModel:
    """ Полностью синхронный интерфейс, вызывает методы new/load напрямую, без всякого thread pool (и сразу вызывает callback)
    """
    def __init__(self, iDict, server_version, load_conversion_xml=True):
        options = ClassDict( I=iDict, server_version=server_version, load_conversion_xml=load_conversion_xml )
        self.serial = SerialModelFactory( options )
        
    def newSerialModel(self, auid, fraction, sex, guest, db, old_md, Config, SD, userlocale, country_code, isReset, callback):
        """  """
        new_acc = self.serial.newSerial(fraction, sex, guest, db, auid, old_md, Config, SD, userlocale, country_code, isReset)
        reply = { "r":new_acc }
        callback( reply )
        
    def loadSerialModel(self, uid, model_string, fraction, sex, db, sn_count, Config, SD, userlocale, country_code, callback):
        """  """
        new_acc = self.serial.loadSerial(uid, model_string, fraction, sex, db, sn_count, Config, SD, userlocale, country_code)
        reply = { "r":new_acc, "p":uid }
        callback( reply )

    def destroy(self):
        pass
        
