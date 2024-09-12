# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2010
#
# async sql queries for Tornado

from base.helpers import *
import threading
import tornado
import tornado.stack_context
from pymongo.errors import AutoReconnect

from binascii import crc32   # zlib version is not cross-platform
def crc_hash(key):
    return((((crc32(key) & 0xffffffff) >> 16) & 0x7fff) or 1)

from base.safelock import *

PERFORM_SCHEDULE_TIMEOUT = 20.0 # если долго не было запросов на perform, надо бы обеспокоиться
AUTORECONNECT_COUNT = 5 # максимальное количество попыток рекконекта

## --------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------

class IClusterThreadPool( object ):
    """ Базовый интерфейс для async thread pool """
    CNAME = "ICTP"

    # ----------- OVERRIDE --------------
    def runQuery(self, query, connection):
        pass
        
    # ----------- OVERRIDE --------------
    def newConnection(self, threadNum, threadID, options):
        info( "IClusterConnection thread #%d {%d} start: %5.3f" % (threadNum, threadID, time.time()) )
        return None, "conn_name"
        
    # ----------- OVERRIDE --------------
    def closeConnection(self, connection):
        pass
        
    # ----------- OVERRIDE --------------
    # не пора ли свернуть работу?
    def checkFadeout(self, connection, options):
        if not self.peekQueries():
            # если очередь пустая: по флагу fadeoutThreads=1 мягко завершаем работу: доразбираем очередь запросов и выходим
            return getattr(self, "fadeoutThreads", 0)
        return 0
        
    ## ----------------------------------------------------------------------------------------
    def __init__(self, num_connections=8, syncWait=16.0, instrument=None):
        log( "!" + str(self)) 
        self.conditionQueries = threading.Condition()
        self.lockReplies = JustLock( warn ) ## SafeLock(log)
        self.performScheduled = 0
        self.queries = []
        self.replies = []
        self.stopThreads = 0
        self.fadeoutThreads = 0 # флаг для worker threads, чтобы "сваливали по мере завершения разбора запросов"
        self.lockThreadCount = thread.allocate_lock()
        self.threadCount = 0
        
        self.num_connections = num_connections
        self.syncWait = syncWait
        self.instrument = instrument
        
        ##! после конструктора обычно сразу вызывается startThreads()
    
    ## ----------------------------------------------------------------------------------------
    def startThreads(self):
        for i in xrange(self.num_connections):
            # запускаем N thread'ов с коннектами
            paramTuple = i+1, self.popQuery, self.addReply, self.options, self # thread хочет кортеж на входе
            thread.start_new_thread(asyncThreadFunc, paramTuple) 
            
        if self.syncWait:
            t0 = time.time()
            # ждем, пока все worker threads побегут
            while not self.threadsStarted(self.num_connections): 
                time.sleep(0.001)
                if time.time() - t0 > self.syncWait:
                    err( "fail starting %s thread pool: time elapsed %.3f, syncWait=%.3f" % (self.CNAME, time.time() - t0, self.syncWait) )
                    raise Exception("fail starting %s thread pool" % self.CNAME)

    ## ----------------------------------------------------------------------------------------
    #~ def __del__(self):
        #~ log( "~" + str(self) )
    
    ## ----------------------------------------------------------------------------------------
    ## останавливаем thread pool, удаляем очереди
    def destroy(self, syncWait=1.0):
        info( "destroying " + str(self) )
        
        self.stopThreads = 1 # говорим worker threads, чтобы сваливали
        self.wakeAll() # будим все нитки, чтобы увидели stopThreads и свалили
        
        # ждем, пока все worker threads свалят
        t0 = time.time()
        while not self.threadsDone(): 
            time.sleep(0.001)        
            self.wakeAll() # будим все нитки
            if time.time() - t0 > syncWait:
                raise

        # чиcтим очереди запросов/ответов
        self.conditionQueries.acquire()
        self.queries[:] = []
        self.conditionQueries.release()
        
        self.lockReplies.acquireSafe()
        self.replies[:] = []
        self.lockReplies.releaseSafe()
        
        info( "done " + str(self))
        
    ## ----------------------------------------------------------------------------------------
    ## мягкое завершение работы: ждем, пока потоки доразберут текущую очередь запросов
    def fadeout(self, syncWait=0 ):
        warn( "fadeout " + str(self) )
        self.fadeoutThreads = 1 # говорим worker threads, чтобы сваливали по мере завершения разбора запросов
        self.wakeAll()
        
        if syncWait:
            t0 = time.time()
            # ждем, пока все worker threads свалят
            while not self.threadsDone(): 
                #~ log( "%s syncWait self.threadCount=%d" % (self.sql_base, self.threadCount) )
                time.sleep(0.001)
                self.wakeAll()
                if time.time() - t0 > syncWait:
                    err( "fadeout too long (%s), syncWait=%s timeout" % (self, syncWait) )
                    return
            
            # ждем, пока ioloop заберет все ответы
            while self.replies:
                #~ log( "%s syncWait len(self.replies)=%d" % (self.sql_base, len(self.replies)) )
                time.sleep(0.001)
                self.wakeAll()
                self.forceCallback()
                if time.time() - t0 > syncWait:
                    err( "fadeout too long (%s), syncWait=%s timeout" % (self, syncWait) )
                    return
                
            info( "fadeout done " + str(self) )
        
    ## ----------------------------------------------------------------------------------------
    ## разбудить какую-нибудь (одну) рабочую нитку
    def wakeOne(self):
        # разбудим какую-нибудь из основных ниток
        self.conditionQueries.acquire()
        self.conditionQueries.notify()
        self.conditionQueries.release()
        
    ## ----------------------------------
    ## разбудить все нитки
    def wakeAll(self):
        self.conditionQueries.acquire()
        self.conditionQueries.notifyAll()
        self.conditionQueries.release()
        
    ## ---------------------------------------
    ## подсчет кол-ва запущенных threads
    def addThread(self, threadID):
        self.lockThreadCount.acquire()
        self.threadCount += 1
        self.lockThreadCount.release()
        
    def releaseThread(self, threadID):
        self.lockThreadCount.acquire()
        self.threadCount -= 1
        self.lockThreadCount.release()
        
    def threadsDone(self):
        return self.threadCount <= 0

    def threadsStarted(self, num_threads):
        return self.threadCount == num_threads

        
    ## ---------------------------------------
    ## добавляем в очередь новый ответ
    def addReply(self, replyDict):
        self.lockReplies.acquireSafe()
        
        self.replies.append( replyDict )
        
        now = time.time()
        # если еще не сказали IOLoop "обработать ответы", или если как-то слишком давно говорили, надо сказать
        bAddCallback = (self.performScheduled == 0) or (now - self.performScheduled > PERFORM_SCHEDULE_TIMEOUT) 
        self.performScheduled = now
        
        if bAddCallback:
            # просим IOLoop проснуться и обработать ответ(ы)
            self.forceCallback()
                        
        self.lockReplies.releaseSafe()

        reply_count = len(self.replies)
        if reply_count > 1000:
            t0 = replyDict["ts"] - replyDict["tq"]
            t1 = replyDict["tr"] - replyDict["ts"]
            info( "%s addReply: query time %0.4f (timer lag %0.4f, now %0.4f), bAddCallback:%d, reply queue size: %s", self.CNAME, t1, t0, time.time(), bAddCallback, reply_count)
    
    ## ---------------------------------------
    def forceCallback(self):
        # просим IOLoop проснуться и обработать ответ(ы)
        loop = tornado.ioloop.IOLoop.instance()
        loop.add_callback( self.perform )
    
    #~ ## ---------------------------------------
    #~ ## забираем очередной ответ (LIFO) поштучно (в целом, плохая идея из-за лока на каждой операции)
    #~ def popReply(self):
        #~ reply = None
        #~ self.lockReplies.acquireSafe()
        
        #~ if len(self.replies):
            #~ reply = self.replies.pop()
            
        #~ self.lockReplies.releaseSafe()
        #~ return reply
        

    ## ---------------------------------------
    ## забираем все накопившиеся ответы списком
    def popAllReplies(self):
        self.lockReplies.acquireSafe()
        
        replies = self.replies[:]
        clear( self.replies )
        self.performScheduled = 0 # забрали ответы, можно вешать новые perform-callbacks
        
        self.lockReplies.releaseSafe()
        return replies
        

    ## ---------------------------------------
    ## периодически исполняем callback-и для всех новых ответов:
    ## ! В ОБЩЕМ IOLoop сервера (синхронно)
    def perform(self):
        replies = self.popAllReplies() # забираем сразу весь список ответов
        
        t0 = time.time()
        reply_count = len(replies)
        
        for reply in replies:
            if reply:
                try:
                    if self.instrument:
                        # попробуем достать тип запроса, и запротоколировать время исполнения запроса
                        query_name = reply.get("n", "ANY")
                        loop = tornado.ioloop.IOLoop.instance()
                        
                        t_add = reply.get("tq", 0.0)
                        t_start = reply.get("ts", 0.0)
                        t_reply = reply.get("tr", 0.0)
                        
                        wait_tag = self.CNAME + ".wait"

                        if getattr(loop, "ws", None): 
                            #TODO: Отстой, невозможно отдельно пользоваться интерфейсом к монго
                            loop.ws.instrumentAction( wait_tag, t_start-t_add) 
                            action_tag = self.CNAME + "." + query_name
                            loop.ws.instrumentAction( action_tag, t_reply-t_start)
                    
                    callback = reply.get("cb")
                    if callback:
                        callback( reply )
                except:
                    catch()
                        
        t1 = time.time()
        queries_count = len(self.queries)
        if (t1-t0 > 0.001) or (reply_count > 10) or (queries_count > 1000):
            info( "perform %s: %.3f (%d reply callbacks done), pending queries_count=%s" % (self.CNAME, t1-t0, reply_count, queries_count) )
        

    ## ---------------------------------------
    ## есть еще запросы в очереди?
    def peekQueries(self):
        return len(self.queries)



## --------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------

class IClusterFunctorThreadPool( IClusterThreadPool ):
    """ Реализует простой режим вызова запросов: с указанием имени функции в query["f"] и списка аргументов (tuple) в query["a"] """
    CNAME = "ICFTP"
    
    ## ----------- OVERRIDE (IClusterThreadPool) --------------
    def runQuery(self, query, connection):
        func_name = query["f"]
        func = getattr(connection, func_name);
        args = tuple()
        if query.has_key("a"):
            args = query["a"]
        reply = func( *args )
        return reply
        
        
    ## ---------------------------------------
    ## добавляем в очередь новый запрос
    def addQuery(self, func_name, args_tuple, callback=None, params=None):
        self.conditionQueries.acquire()
        
        if callback:
            callback = tornado.stack_context.wrap(callback)
        query = { "f":func_name, "a":args_tuple, "cb":callback, "tq":time.time(), "p":params }
        self.queries.append( query )
        
        self.conditionQueries.notify() # извещаем (будим) первого попавшегося consumer
        self.conditionQueries.release()
        
        ## log( "%s addQuery: %s, ts %5.3f" % ( self.CNAME, str(query), time.time() ))
        
        
    ## ---------------------------------------
    ## забираем очередной запрос (FIFO)
    def popQuery(self):
        query = None
        self.conditionQueries.acquire()
        
        if not self.queries:
            self.conditionQueries.wait()
        
        if self.queries:
            query = self.queries.pop(0)
            
        self.conditionQueries.release()
        return query

    ## --------------------------------------
    ## Запрос создан мы его просто хотим еще раз добавить
    def reAddQuery(self, query):
        self.conditionQueries.acquire()
        self.queries.append( query )

        self.conditionQueries.notify() # извещаем (будим) первого попавшегося consumer
        self.conditionQueries.release()


## --------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------
def packExceptions(query,owner, conn_name, threadNum):
    warn("async query %s.%s.%d exception. Query: %s", owner.CNAME, conn_name, threadNum, query)
    exc_info = sys.exc_info()
    query["e"] = printException( exc_info )
    query["ex"] = printExceptionOnly( exc_info )
    catch()

def asyncThreadFunc(threadNum, getQuery, postReply, options, owner):
    threadID = thread.get_ident()
    connection, conn_name = None, "?"
    try:
        connection, conn_name = owner.newConnection(threadNum, threadID, options)
        owner.addThread( threadID )
        autoReconnect = False
        arCount = 0

        while connection and (not getattr(owner, "stopThreads", None)):
            if not autoReconnect:
                query = getQuery()

            if query:
                ts = time.time()
                ##info( "async query %s.%s.%d start: %5.3f, query: %s..." % (owner.CNAME, conn_name, threadNum, ts, str(query)[:1024]) )
                
                try:
                    reply = owner.runQuery(query, connection)
                    autoReconnect = False
                    arCount = 0

                except AutoReconnect:
                    reply = None
                    if arCount <= AUTORECONNECT_COUNT:
                        debug("Autoreconnect error reached. Trying to resend data by timeout: async query %s.%s.%d exception. Count of try %s Query: %s", owner.CNAME, conn_name, threadNum, arCount, query)
                        arCount += 1
                        time.sleep(0.1) #подождем чуть чуть
                        autoReconnect = True
                        continue
                    else:
                        debug("Autoreconnect max count of errors reached! ", query)
                        autoReconnect = False
                        arCount = 0
                        ## реконнекты не помогли попробуем добавить запрос в очередь еще раз
                        ## может потом получится его выполнить
                        #owner.reAddQuery(query)
                        packExceptions(query, owner, conn_name, threadNum)

                except Exception:
                    reply = None
                    autoReconnect = False
                    arCount = 0
                    packExceptions(query, owner, conn_name, threadNum)


                tr = time.time()
                if 'x' in query and isinstance(reply, (int, long)): #PF-96975
                    query["r"] = [reply]
                else:
                    query["r"] = reply
                query["ts"] = ts
                query["tr"] = tr

                ##info( "async query %s.%s.%d done: %5.3f, query: %s..." % ( owner.CNAME, conn_name, threadNum, tr, str(query)[:1024] ) )
                
                postReply(query)
                
            try:
                if owner.checkFadeout(connection, options):
                    break
            except Exception:
                warn( "async thread %s.%s.%d check fadeout exception" % (owner.CNAME, conn_name, threadNum) )
                catch()
                
    except:
        bad_warn( "async thread %s.%s.%d exception (FATAL)" % (owner.CNAME, conn_name, threadNum) )
        catch()
                
    info("Async %s thread %d exiting" % (owner.CNAME, threadID) )
    owner.closeConnection( connection )
    owner.releaseThread( threadID )



