# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2010
#
# async sql queries for Tornado

from base.helpers import *
import threading
import tornado.ioloop

from base.safelock import *

# ----------------------------------
from cluster_base import IClusterFunctorThreadPool, asyncThreadFunc

from modeldata.ModelData import ModelData
from modeldata.datamanager import PwNewModelManager
from modeldata.validator import Validator
from pwaccount import UserAccount



# хэндлер "тяжелых операций с modeldata": умеем асинхронно создавать новую ModelData, или грузить ее из json-сохранения 
class SerialModelFactory:
    
    def __init__(self, options):
        self.I = options.I
        self.server_version = options.server_version
        
    #-----------------------------------------------------------------------------------------------------------------------------------------------
    # наша задача - не трогая исходный пользовательский аккаунт, создать его пустую копию, в которой будут созданы свежие acc.model и acc.data.index
    def newSerial(self, fraction, sex, guest, db, auid, old_md, Config, SD, userlocale, country_code, isReset):
        acc = UserAccount( data=ClassDict(), db=db, auid=auid, Config=Config, SD=SD, userlocale=userlocale, country_code=country_code )
        info( "serial model new: fraction=%s, sex=%s" % (fraction, sex) )
        self.I.MD.newModel( acc, self.I, self.server_version, random_heroes=-1, fraction=fraction, sex=sex, guest=guest, db=db, old_md = old_md, isReset=isReset)
        return acc

    #------------------------------------------------------------------------------------------------
    def loadSerial(self, uid, model_string, fraction, sex, db, sn_count, Config, SD, userlocale, country_code):
        ##info( "serial model load: uid=%s, fraction=%s, sex=%s, model_string=%s..." % (uid, fraction, sex, str(model_string)[:256]) )        
        acc = UserAccount( uid=uid, db=db, data=ClassDict(), sn_count=sn_count, Config=Config, SD=SD, userlocale=userlocale, country_code=country_code )
        
        if model_string:
            t0 = time.time() # ----------------------            
            self.I.MD.loadModel(acc, model_string, self.I, self.server_version, fraction=fraction, sex=sex)            
            t1 = time.time() # ----------------------
            info( "persistent user[%d] loadModel time: %.3f" % (acc.uid, t1-t0) )            
        else:
            self.I.MD.emptyModel(acc, self.I, self.server_version)

        return acc

                
##------------------------------------------------------------------------------------------------
class AsyncSerialModelManager( IClusterFunctorThreadPool ):
    """ Thread pool и очереди запросов/ответов для общения с memcache. 
        Метод вызова запросов стандартный, наследуем от FunctorThreadPool: query["f"] содержит имя функции, query["a"] -- аргументы (tuple).
    """
    CNAME = "smodel"
    
    # ----------- OVERRIDE --------------
    def newConnection(self, threadNum, threadID, options):
        conn_name = "smodel%s" % threadNum
        info( "AsyncSerialModel thread %d {%d} start: %5.3f, name %s" % (threadNum, threadID, time.time(), conn_name) )

        smodel = SerialModelFactory( self.options )
        smodel.threadID = threadID
        return smodel, conn_name
        
    ## ----------------------------------------------------------------------------------------
    def __init__(self, iDict, server_version, num_connections=8):
        self.options = ClassDict( I=iDict, server_version=unicode(server_version), load_conversion_xml=True )
        IClusterFunctorThreadPool.__init__(self, num_connections, syncWait=15.0)
        self.startThreads()

        
