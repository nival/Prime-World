# -*- coding: utf-8 -*-

#
# (C) Dan Vorobiev 2010
#
# async sql queries for Tornado

from base.helpers import *
import threading
import tornado.ioloop
import socket

from base.safelock import *

addRelPath("libs/memcache")
import memcache

from binascii import crc32   # zlib version is not cross-platform

# ----------------------------------
from cluster_base import IClusterFunctorThreadPool, asyncThreadFunc

# вокруг клиента придется сделать небольшую обертку, чтобы поддержать cas-операции
#  в текущей реализации gets складывает полученный cas_id внутри конкретного инстанса memcache.Client 
# (в этом случае другой инстанс mc.Client, работающий из другого thread-а, выполняя cas, разумеется, промахнется)
# -> нужно 
#    либо 1) возвращать cas_id из метода gets, 
#       либо 2) буферизовать две операции (gets + cas) в одну, исполняемую одним и тем же клиентом атомарно
class CasClient(memcache.Client):
    #------------------------------------------------------------------------------------------------
    def gets(self, key):
        '''Retrieves a key + cas_id from the memcache. Used in conjunction with 'cas'.

        @return: value, cas_id or None, None.
        '''
        #--- дальше делаем то же что в методе _get, только с другим возвратом
        self.check_key(key)
        server, key = self._get_server(key)
        if not server:
            return None, None #

        self._statlog("gets")

        try:
            server.send_cmd("%s %s" % ("gets", key))
            rkey = flags = rlen = cas_id = None
            rkey, flags, rlen, cas_id, = self._expect_cas_value(server)

            if not rkey:
                log("fail _expect_cas_value")
                return None, None #
            value = self._recv_value(server, flags, rlen)
            server.expect("END")
        except (memcache._Error, socket.error), msg:
            if isinstance(msg, tuple): msg = msg[1]
            server.mark_dead(msg)
            log("fail try")
            return None, None
        return value, cas_id

    #------------------------------------------------------------------------------------------------
    def cas(self, key, val, cas_id, time=0, min_compress_len=0):
        '''Sets a key to a given value in the memcache IF IT HASN'T BEEN
        ALTERED since last fetched (i.e. still equal to <cas_id>). (See L{gets}).
        '''
        #--- дальше делаем то же самое, что в методе _set, только cas_id подсовываем из параметров вызова, а не из self.cas_ids[]
        self.check_key(key)
        server, key = self._get_server(key)
        if not server:
            return 0

        self._statlog("cas")

        store_info = self._val_to_store_info(val, min_compress_len)
        if not store_info: return(0)

        fullcmd = "%s %s %d %d %d %d\r\n%s" % (
                "cas", key, store_info[0], time, store_info[1],
                cas_id, store_info[2])

        try:
            server.send_cmd(fullcmd)
            return(server.expect("STORED") == "STORED")
        except socket.error, msg:
            if isinstance(msg, tuple): msg = msg[1]
            server.mark_dead(msg)
        return 0

                
##------------------------------------------------------------------------------------------------
class AsyncMemcacheManager( IClusterFunctorThreadPool ):
    """ Thread pool и очереди запросов/ответов для общения с memcache. 
        Метод вызова запросов стандартный, наследуем от FunctorThreadPool: query["f"] содержит имя функции, query["a"] -- аргументы (tuple).
    """
    CNAME = "mc"
    
    # ----------- OVERRIDE --------------
    def newConnection(self, threadNum, threadID, options):
        prev_crc = options.server_crc32[0]
        info( "AsyncMemcache thread %d {%d} start: %5.3f (servers %s, crc %s)" % (threadNum, threadID, time.time(), str(options.server_list), str(prev_crc)) )

        mc = CasClient(options.server_list, debug=0)
        mc.prev_crc = prev_crc
        mc.threadID = threadID
        return mc, "mc"
        
    # ----------- OVERRIDE --------------
    def checkFadeout(self, connection, options):
        # список серверов может динамически меняться
        if connection.prev_crc != options.server_crc32[0]:
            connection.prev_crc = options.server_crc32[0]
            connection.disconnect_all()
            connection.set_servers( options.server_list )

            warn( "{%d} mc server list reset (%s)" % (connection.threadID, str(options.server_list)) )
            print( "{%d} server list (%s)" % (connection.threadID, str(options.server_list)) )
        
        # никогда не возвращаем True, у нас не бывает fadeout
        
    ## ----------------------------------------------------------------------------------------
    def __init__(self, server_list, server_crc32, num_connections=8, syncWait=1.0):
        IClusterFunctorThreadPool.__init__(self, num_connections, syncWait)

        self.server_list = server_list
        self.options = ClassDict( server_list=server_list, server_crc32=server_crc32 )
        
        self.startThreads()

        
