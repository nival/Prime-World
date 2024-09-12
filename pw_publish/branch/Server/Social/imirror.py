# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *

import tornado.ioloop
import tornado.options
from tornado.options import define, options

##---------------------------------------------------------------------------------------------
from cluster_base import crc_hash

def AsyncMIRROR(key):
    return tornado.ioloop.IOLoop.instance().mirror

MirrorDataType = ClassDict(
    NONE = 0,
    MODEL_DATA = 1, # user data record from mongo
    GUILD_DATA = 2, # mongo guild data
)

MirrorRequestStatus = ClassDict(
    NEW = 0,
    PULLED = 1,
    PROCESSING = 2,
    DONE = 3
)
CheckMirrorRequestStatus = ClassDict(
    CHECK = 0,
    DONE = 1
)


##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

# NB: пока что реализуем и IData здесь же (простым наследованием)
class IMirrorQueue:
    """ очередь запросов на зеркалирование данных
    """
    # ------------- техническое  -------------------
    def __init__(self, *args, **kwargs):
        pass
        
    def destroy(self):
        """ грубо закрываем лавочку (прибиваем thread pool, очередь запросов и т.п.) """
        pass

    def fadeout(self, syncWait=0 ):
        """ постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool) """
        pass
        
    def isDone(self):
        """ прикрыта ли лавочка? """ 
        return True # пустышку можно прибивать в любой момент
        
    # ------------- REQUEST QUEUE API -------------------
    def addRequest(self, data_type, data_id, callback=None): 
        """ добавляем новый запрос в очередь """
        pass
        
    def getRequests(self, data_type, service_count, request_type, count_limit, my_handler_id, callback=None):
        """ вытаскиваем пачку запросов из очереди """
        pass
        
    def getOldRequests(self, timestamp, callback=None):
        """ достаем запросы старше чем timestamp """
        pass
        
    def markRequests(self, request_id_list, status, callback):
        """ помечаем запросы как выполняемые (или выполненные) """
        pass

    def deleteRequests(self, request_id_list, callback=None):
        """ удаляем выполненные запросы """
        pass

    def countRequests(self , callback):
        """ добавляем новый запрос в очередь """
        pass
        
        
##---------------------------------------------------------------------------------------------
## Интерфейс для общения с реальной sql-базой через async thread-pool.
# NB: пока что реализуем и IData здесь же, просто через отдельную таблицу tbl_brick в MySQL БД
class AsyncSqlMirrorQueue(IMirrorQueue):
    def __init__(self):
        self.loop = tornado.ioloop.IOLoop.instance()
        
    def destroy(self):
        self.loop.mirror.destroy()

    def fadeout(self, syncWait=0 ):
        self.loop.mirror.fadeout( syncWait )
            
    def isDone(self):
        """ прикрыта ли лавочка? """ 
        if ( not self.loop.mirror.threadsDone() ) or len(self.loop.mirror.replies): # остались бегающие threads или неразобранные ответы
            return False
        return True
    
    # ------------------ API -------------------------

    def addRequest(self, data_type, data_id, callback=None): 
        """ добавляем новый запрос в очередь """
        ts = toint(time.time())
        sql = "INSERT INTO tbl_queue (`data_type`,`data_id`,`timestamp`) VALUES (%d,%d,%d) ON DUPLICATE KEY UPDATE `timestamp`=%d" \
            % (data_type, data_id, ts, ts)
        info("addRequest query: %r", sql)
        self.loop.mirror.addExec(sql, callback, opname="addRequest")

    def getRequests(self, data_type, service_count, request_type, count_limit, my_handler_id, callback=None):
        """ вытаскиваем пачку запросов из очереди """
        sql = "CALL sp_get_requests(%d,%d,%d,%d,%d)" % (data_type, request_type,  service_count, count_limit, my_handler_id)
        info("getRequests query: %r", sql)
        self.loop.mirror.addQuery(sql, callback, opname="getRequests")
                
    def markRequests(self, request_id_list, status, callback=None):
        """ помечаем запросы как выполняемые (или выполненные) """
        sql = "UPDATE tbl_queue SET _status=%d, timestamp=%d WHERE id IN (%s)" % (status, toint(time.time()), strList(request_id_list))
        info("markRequests query: %r", sql)
        self.loop.mirror.addExec(sql, callback, opname="markRequests")
        
    def deleteRequests(self, request_id_list, callback=None):
        """ удаляем выполненные запросы """
        sql = "DELETE FROM tbl_queue WHERE id IN (%s)" % strList(request_id_list)
        info("deleteRequests query: %r", sql)
        self.loop.mirror.addExec(sql, callback, opname="deleteRequests")
        
    def getOldRequests(self, timestamp, callback=None):
        """ достаем запросы старше чем timestamp """
        sql = "SELECT * FROM tbl_queue WHERE timestamp < %d" % toint(timestamp)
        info("getOldRequests query: %r", sql)
        self.loop.mirror.addQuery(sql, callback, opname="getOldRequests")

    def countRequests(self, data_type, callback=None):
        if data_type == 'pers':
            data_type = str(1)
        if data_type == 'guilds':
            data_type = str(2)
        """ считаем количество запросов с определенным флагом """
        #sql = "SELECT data_type, count(*) FROM pw_mirror.tbl_queue t GROUP BY data_type"
        sql = "SELECT data_type , count(*) as amount FROM tbl_queue t WHERE data_type='%s'"% data_type
        info("get requests counter : %r", sql)
        self.loop.mirror.addQuery(sql, callback, opname="countRequests")

    def checkRequestStatus(self, mirror_service_count, mirror_request_type, adata_type, callback=None):
        sql = "UPDATE tbl_queue SET _status={0} WHERE _status={1} AND data_type = {2} AND MOD(id, {3}) = {4}".format(
                MirrorRequestStatus.NEW,
                MirrorRequestStatus.PROCESSING,
                adata_type,
                mirror_service_count,
                mirror_request_type
        )
        info("checkRequestStatus query: %r", sql)
        self.loop.mirror.addExec(sql, callback, opname="checkRequestStatus")