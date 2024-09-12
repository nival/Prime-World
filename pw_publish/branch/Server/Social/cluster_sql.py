# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2010
#
# async sql queries for Tornado

from base.helpers import *
import threading
import torndb # sql query result as iterator
import tornado.stack_context

from base.safelock import *

# ----------------------------------
from cluster_base import crc_hash, IClusterThreadPool, asyncThreadFunc

# ----------------------------------------------------------------------------------------
# тупо исполняем одиночный запрос, синхронно (должен быть SELECT с рядами полей в ответе, т.к. исполняем db.query)
def syncSqlQuery(sqlQuery, options, *params):
    db = torndb.Connection(options.sql_host, options.sql_base, options.sql_user, options.sql_pass)
    reply = None
    if db:
        try:
            reply = db.query( sqlQuery, *params )
        except Exception:
            printException( sys.exc_info() )
            
    return reply


# ----------------------------------------------------------------------------------------
# тупо исполняем одиночный запрос, синхронно (должен быть UPDATE/DELETE с одним (числовым) ответом, без рядов полей, т.к. исполняем db.execute)
def syncSqlCommand(sqlCommand, options, *params):
    db = torndb.Connection(options.sql_host, options.sql_base, options.sql_user, options.sql_pass)
    reply = None
    if db:
        try:
            reply = db.execute( sqlCommand, *params )
        except Exception:
            catch()
    return reply

class SyncSqlManager():

  def __init__(self, options):
      self.options = options
      self.db = None

  def openConnection(self):
      self.db = torndb.Connection(self.options.sql_host, self.options.sql_base, self.options.sql_user, self.options.sql_pass)
  # ----------------------------------------------------------------------------------------
  # тупо исполняем одиночный запрос к уже открытому соединению, синхронно (должен быть SELECT с рядами полей в ответе, т.к. исполняем db.query)
  def syncSqlQuery(self, sqlQuery, *params):
      reply = None
      if self.db:
          try:
              reply = self.db.query( sqlQuery, *params )
          except Exception:
              #print printException( sys.exc_info() )
              catch()
      return reply


  # ----------------------------------------------------------------------------------------
  # тупо исполняем одиночный запрос к уже открытому соединению, синхронно (должен быть UPDATE/DELETE с одним (числовым) ответом, без рядов полей, т.к. исполняем db.execute)
  def syncSqlCommand(self, sqlCommand, *params):
      reply = None
      if self.db:
          try:
              reply = self.db.execute( sqlCommand, *params )
          except Exception:
              catch()
              #print printException( sys.exc_info() )
      return reply
## ----------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------

class AsyncSqlManager( IClusterThreadPool ):
    """ thread pool и очереди запросов/ответов для общения с sql database """
    CNAME = "sql"
    
    # ----------- IClusterThreadPool overridables -----------
    def runQuery(self, query, connection):
        args = query.get('a', None) or ()
        if query.has_key("s"):
            reply = connection.query(query["s"], *args)
        elif query.has_key("x"):
            reply = connection.execute(query["x"], *args)
        elif query.has_key("xm"):
            reply = connection.executemany(query["xm"], args)

        return reply 
        
    def newConnection(self, threadNum, threadID, options):
        info( "Async SQL thread %s.%d {%d} start: %5.3f (host %s)" % (options.sql_base, threadNum, threadID, time.time(), options.sql_host) )
        db = torndb.Connection(options.sql_host, options.sql_base, options.sql_user, options.sql_pass)
        db.execute( "SET NAMES UTF8" )
        return db, options.sql_base
    
    def closeConnection(self, connection):
        if connection:
            connection.close()

    ## ----------------------------------------------------------------------------------------
    def __init__(self, options, num_connections=8, database_id=0, syncWait=2.0, instrument=None):
        IClusterThreadPool.__init__(self, num_connections, syncWait, instrument)

        self.options = options
        self.sql_base = options.sql_base
        self.database_id = database_id

        self.lazyQueries = []
        self.lockLazyQueries = JustLock( warn ) ## SafeLock(log)

        self.startThreads()
            
    #~ def __del__(self):
        #~ info( "~AsyncSqlManager " + str(self) )
        
        
    ## -------------------------------------------------------------------------------------
    ## добавляем в очередь новый срочный запрос
    ## D.L.: Невполне понятно, для чего (вероятно, для логирования) тут params,
    ## но для проброса параемтров в query()/execute() запроса пришлось дополнительно сделать args
    def addQuery(self, sql, callback=None, params=None, args=None, opname="ANY"):
        self.conditionQueries.acquire()
        
        if callback:
            callback = tornado.stack_context.wrap(callback)
        query = {"i":self.database_id, "s":sql, "cb":callback, "tq":time.time(), "p":params, "n":opname, "a":args}
        self.queries.append(query)
        
        self.conditionQueries.notify()
        self.conditionQueries.release()
        
        ##log( "addQuery(%s): %s, ts %5.3f" % (self.sql_base, str(query), time.time()) )
        
        
    ## добавляем в очередь новый ОТЛОЖЕННЫЙ запрос
    def lazyQuery(self, sql, callback=None, params=None, args=None, opname="ANY"):
        self.lockLazyQueries.acquireSafe()
        
        if callback:
            callback = tornado.stack_context.wrap(callback)
        query = {"i":self.database_id, "s":sql, "cb":callback, "tq":time.time(), "p":params, "n":opname, "a":args}
        self.lazyQueries.append( query )
        
        self.lockLazyQueries.releaseSafe()
        # разбудим какую-нибудь из основных ниток
        self.wakeOne()
        
        ##log( "lazyQuery(%s): %s" % (self.sql_base, str(query)) )
        
        
    ## добавляем в очередь новый срочный запрос
    def addExec(self, sql, callback=None, params=None, args=None, opname="ANY"):
        self.conditionQueries.acquire()
        
        if callback:
            callback = tornado.stack_context.wrap(callback)
        query = {"i":self.database_id, "x":sql, "cb":callback, "tq":time.time(), "p":params, "n":opname, "a":args}
        self.queries.append( query )
        
        self.conditionQueries.notify()
        self.conditionQueries.release()
        
        ##log( "addExec(%s): %s, ts %5.3f" % (self.sql_base, str(query), time.time()) )

    ## добавляем в очередь новый срочный запрос
    def addExecMany(self, sql, callback=None, params=None, args=None, opname="ANY"):
        self.conditionQueries.acquire()

        if callback:
            callback = tornado.stack_context.wrap(callback)
        query = {"i":self.database_id, "xm":sql, "cb":callback, "tq":time.time(), "p":params, "n":opname, "a":args}
        self.queries.append( query )

        self.conditionQueries.notify()
        self.conditionQueries.release()

        ##log( "addExec(%s): %s, ts %5.3f" % (self.sql_base, str(query), time.time()) )

        
    ## добавляем в очередь новый ОТЛОЖЕННЫЙ запрос
    def lazyExec(self, sql, callback=None, params=None, args=None, opname="ANY"):
        self.lockLazyQueries.acquireSafe()
        
        if callback:
            callback = tornado.stack_context.wrap(callback)
        query = {"i":self.database_id, "x":sql, "cb":callback, "tq":time.time(), "p":params, "n":opname, "a":args}
        self.lazyQueries.append( query )
        
        self.lockLazyQueries.releaseSafe()
        # разбудим какую-нибудь из основных ниток
        self.wakeOne()
        
        ##log( "lazyExec(%s): %s" % (self.sql_base, str(query)) )
        
        
    ## забираем очередной запрос (FIFO)
    def popQuery(self):
        query = None
        self.conditionQueries.acquire()
        
        if (not len(self.queries)) and (not len(self.lazyQueries)):
            self.conditionQueries.wait()
        
        if len(self.queries):
            query = self.queries.pop(0)
            
        self.conditionQueries.release()
        
        if query:
            return query
        else:
            # нет срочных запросов; проверим lazy очередь
            return self.popLazyQuery()
            
            
    ## есть еще запросы в очередях?
    def peekQueries(self):
        return len(self.queries) or len(self.lazyQueries)
            
    
    ## забираем очередной запрос (FIFO) из "ленивой" очереди
    def popLazyQuery(self):
        query = None
        self.lockLazyQueries.acquireSafe()
        
        if len(self.lazyQueries):
            query = self.lazyQueries.pop(0)
            
        self.lockLazyQueries.releaseSafe()
        return query
        


    
