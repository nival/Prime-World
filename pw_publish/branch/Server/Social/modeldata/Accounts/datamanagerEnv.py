# -*- coding: utf-8 -*-
#!/usr/bin/env python

import sys, os, time, logging

sys.path.append('../..')
sys.path.append('..')
sys.path.append('../../base')
sys.path.append('../../cfg')
from modeldata.ModelData import *

from base.helpers import *
from handlers import *
from modeldata.datamanager import *
#from modeldata.persistent_data import *
from config.MultiConfig import *
from modeldata.persistent_data import PersistentDataManager, createStandalonePersistentInterface

from pwaccount import *
import coord_cfg

class DataManagerEnv:
    def __init__( self ):
        options_xdb_path = "../../xdb"
        cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
        cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
        cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR
        cfg.TOURNAMENT_SPECTATOR_AUIDS = coord_cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS
        cfg.TOURNAMENT_APPLY_RESULTS = coord_cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS
        self.I = ClassDict()
        self.I.coord_res = {}
        self.I.coord_res["deploy_name"] = "RU"
        createStandalonePersistentInterface(self.I, options_xdb_path, os.path.dirname("../"))
         
        self.acc = UserAccount( uid = 1, Config=self.I.Config, SD=self.I.SD, userlocale="" )
        self.acc.db = ClassDict()
        self.acc.data = ClassDict()
        self.acc.auid = 1
        self.acc.db.auid = 1

        self.acc.geo_info = {'region_name': '66', 'city': 'Saint Petersburg', 'longitude': 30.264199999999988,
                             'country_code3': 'RUS', 'latitude': 59.89439999999999, 'postal_code': None,
                             'country_code': 'RU', 'country_name': 'Russian Federation'}

        self.I.BILL.initBilling( self.acc.auid )
        
    def convertModelData( self, filename ):
        file = open( filename, "rb" )
        data_json = file.read()
        file.close()
        self.__loadPersistent( self.acc, data_json )
        
    def __loadPersistent( self, acc, data_json ):
        try:
            self.I.PDM.loadAccountData( acc, data_json )
        except:
            catch()

