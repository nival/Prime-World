#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import urllib2
import ujson
import json
import zlib
import gzip
import cStringIO
import gc

gc.disable()

import logging
DEFAULT_LOG_LEVEL = logging.INFO
logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

os.chdir('..')
_addPath('.')

from base.helpers import *

#~ @profile
def createStandalonePersistentInterface( iDict, xdb_path, modeldata_path ):
    """ для случаев, когда у нас нет рабочего кластера и особо некого оповещать, делаем dummy self.I, адекватно реагирующий на вызовы из PersistentDataManager """
    from config.MultiConfig import MultiConfig
    iDict.Config = MultiConfig()
    
    from modeldata.MultiStaticData import MultiStaticData
    iDict.SD = iDict.SD or MultiStaticData( xdb_path + "/ExportedSocialData.xml", iDict.Config.getMainConfig() ).getMainSD()
    iDict.Config.getMainConfig.fillStaticDataDependendValues(iDict.SD)
    
    from modeldata.datamanager import PwNewModelManager
    iDict.MD = PwNewModelManager( ifaceDict=iDict, load_events=False )
    
    from iserialmodel import ISyncSerialModel
    from handlers import PWSOC_VERSION
    iDict.SMODEL = ISyncSerialModel( iDict, PWSOC_VERSION )
    
    from iwebserver import IWebServer
    iDict.WS = IWebServer()
    
    from modeldata.persistent_data import PersistentDataManager
    iDict.PDM = PersistentDataManager( iDict )
    
    from ifactory import IfaceFactory
    iDict.STATS = IfaceFactory.makeIStatsInterface( "none", "", iDict ) # пустая болванка
    iDict.BILL = IfaceFactory.makeBillingInterface( "dummy", iDict )

def loadFromFile( filename ):
    if os.path.isfile( filename ):
      file = open( filename, "rb" )
      result = file.read()
      return result
  
@profile
def main( iter_count=1 ):
    import base.helpers
    _addPath("cfg")
    import coord_cfg
    
    from modeldata.ModelData import ModelData
    from friendsdata.FriendsData import FriendsData
    from party.PartyData import PartyData
    
    options_xdb_path = "xdb"
    modeldata_path = os.path.realpath("modeldata")
    info("modeldata_path: %s" % modeldata_path)
    I = ClassDict()
    createStandalonePersistentInterface(I, options_xdb_path, modeldata_path)
        
    acc = ClassDict( uid=1, guest=1, pending_events=[] )
    acc.sex = 0 #male
    acc.loaded = 1
    acc.db = ClassDict()
    acc.data = ClassDict()
    acc.db.fraction = "A"
    acc.db.nick = "TestNick"
    #acc.friendsdata = generateFakeFriends()
    acc.db.nickChanged = 0
    acc.db.fractionChanged = 0
    acc.db.Gold = 100
    acc.auid = 1
    acc.snid = "fb"
    acc.snuid = "100001"
    
    FAKE_PWSOC_SERVER_VERSION = "1.2.3"
    
    #gc.collect()
    #time.sleep(5)
    
    #~ for i in xrange( iter_count ):
        #~ I.MD.newModel( acc, I, FAKE_PWSOC_SERVER_VERSION, random_heroes=-1, random_items=-1, fraction=acc.db.fraction, db=acc.db)
        
        #~ # сохраним свежесозданные данные, и загрузим обратно (так мы убедимся, что после сериализации ModelData по-прежнему проходит все тесты)
        #~ save_data_unicode = I.PDM.saveData( acc, zip=True )
        #~ I.PDM.loadAccountData( acc, save_data_unicode )

    #~ json_data = loadFromFile( "tests/userdata.json" )
    #~ I.PDM.loadAccountData( acc, json_data )
    
    latin1_data = loadFromFile( "tests/userdata.zlib" )
    unicode_data = latin1_data.decode( 'latin1' )
    info("latin1_data len: %s, unicode_data len: %s" % (len(latin1_data), len(unicode_data)))
    I.PDM.loadAccountData( acc, unicode_data )
    
    # --- вернемся обратно из ".." --------------------   
    os.chdir('tests')
    
# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------

main( 1 )