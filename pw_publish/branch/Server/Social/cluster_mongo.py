# -*- coding: utf8 -*-
#
# (C) Dan Vorobiev 2010
#
# async sql queries for Tornado

from base.helpers import *
import threading
import tornado.stack_context
from base.safelock import *

# ----------------------------------
import pymongo
from cluster_base import crc_hash, IClusterFunctorThreadPool, asyncThreadFunc

DEFAULT_MONGO_NETWORK_TIMEOUT = 10.0

## ----------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------

class AsyncMongoManager( IClusterFunctorThreadPool ):
    """ Thread pool и очереди запросов/ответов для общения с NO-sql database.
        По сравнению с дефолтным IClusterFunctorThreadPool у нас добавляется имя collection ("таблицы") в query["c"]
    """
    CNAME = "mongo"
    
    ## ----------------------------------------------------------------------------------------
    def __init__(self, options, num_connections=8, database_id=0, syncWait=2.0, instrument=None):
        IClusterFunctorThreadPool.__init__(self, num_connections, syncWait, instrument)

        self.options = options
        self.database_id = database_id

        self.startThreads()
        
        
    # ----------- OVERRIDE -----------
    def newConnection(self, threadNum, threadID, options):
        info( "Async Mongo thread %s.%d {%d} start: %5.3f (host %s:%d)" % (options.mongo_base, threadNum, threadID, time.time(), options.mongo_addr, options.mongo_port) )
        mongo_connection = pymongo.Connection(options.mongo_addr, options.mongo_port, network_timeout=options.get("network_timeout",DEFAULT_MONGO_NETWORK_TIMEOUT) )
        db = getattr(mongo_connection, options.mongo_base, None)
        db.threadID = threadID # connection в терминах cluster_base -- это будет db
        return db, options.mongo_base
    
    
    ## ----------- OVERRIDE (IClusterThreadPool) --------------
    def runQuery(self, query, connection):
        coll_name = query["c"]
        func_name = query["f"]
        args = query.get("a", tuple())
        kwargs = query.get("kw", {})
        kwargs.setdefault("new", True)
       # kwargs.update(query.get("p", {}))
            
        # если что-нибудь пофейлится, exception traceback все равно приземлится в query["e"]
        func = getattr(getattr(connection, coll_name), func_name)

        #info( "mongo runQuery [thread %s]: query %s" % ( connection.threadID, str(query)[:200] ) )

        # new: возвращать всегда уже модифицированный объект (в процессе update или find_and_modify)
        reply = func(*args, **kwargs)
        
        #info( "mongo reply [thread %s]: reply %s" % ( connection.threadID, str(reply)[:200] ) )
        return reply
        
        
    ## ---------------------------------------
    ## добавляем в очередь новый запрос
    def addQuery(self, coll_name, func_name, args_tuple, callback=None, params=None, opname="ANY", kw=None):
        if callback:
            callback = tornado.stack_context.wrap(callback)
        query = {"f":func_name, "c":coll_name, "a":args_tuple, "cb":callback, "tq":time.time(), "p":params, "n":opname}
        if kw:
            query['kw'] = kw
        
        #info( "mongo addQuery 1: query %s" % ( str(query)[:200] ) )
        
        self.conditionQueries.acquire()
        
        self.queries.append( query )
        
        self.conditionQueries.notify() # извещаем (будим) первого попавшегося consumer
        self.conditionQueries.release()
        
        #info( "mongo addQuery 2 query %s" % ( str(query)[:512] ) )
    
