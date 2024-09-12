# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2010
#
# async sql queries for Tornado

from base.helpers import *
import threading
import tornado.ioloop
import base64, binascii

from suds.client import Client

from base.safelock import *

from binascii import crc32   # zlib version is not cross-platform

# ----------------------------------
from cluster_base import IClusterFunctorThreadPool, asyncThreadFunc


##------------------------------------------------------------------------------------------------
class AsyncZZimaManager( IClusterFunctorThreadPool ):
    """ Thread pool и очереди запросов/ответов для общения с ZZima billing. 
        Метод вызова запросов стандартный, наследуем от FunctorThreadPool: query["f"] содержит имя функции, query["a"] -- аргументы (tuple).
    """
    CNAME = "zz"
    
    # ----------- IClusterThreadPool overridables -----------
    def newConnection(self, threadNum, threadID, options):
        info( "AsyncZZima thread %d {%d} start: %5.3f (wsdl %s)" % (threadNum, threadID, time.time(), str(options.wsdl)) )

        connection = Client(options.wsdl)
        connection.wsdl = options.wsdl
        connection.threadID = threadID
        connection.threadNum = threadNum
        return connection, "zz"
        
        
    ## ----------------------------------------------------------------------------------------
    def runQuery(self, query, connection):
        info( "ZZ runQuery [thread %d]: query %s, client %d" % ( connection.threadID, str(query), toint(connection.threadNum) ) )
        
        params = query["a"]
        methodName = query["f"]
        result = eval('connection.service.%s(params)' % methodName)
        
        info( "ZZ result: %s, query %s, client %d" % ( dict(result), str(query), toint(connection.threadNum) ) )
        
        return dict(result)

    ## ----------------------------------------------------------------------------------------
    def addReply(self, replyDict):
        tq = replyDict.get("tq", 0.0)
        ts = replyDict.get("ts", 0.0)
        tr = replyDict.get("tr", 0.0)
        info( "ZZ addReply: queries=%d, tWait=%.3f, tExec=%.3f" % (len(self.queries), ts-tq, tr-ts) )
        
        return super(AsyncZZimaManager, self).addReply( replyDict )
        
    ## ----------------------------------------------------------------------------------------
    def __init__(self, wsdl, num_connections=4, syncWait=8.0):
        IClusterFunctorThreadPool.__init__(self, num_connections, syncWait)

        self.wsdl = wsdl
        self.options = ClassDict( wsdl=wsdl )
        
        self.startThreads()

        
