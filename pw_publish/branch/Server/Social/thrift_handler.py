# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import httplib

import tornado.options
import tornado.web
from tornado.options import define, options


from handlers import JsonHandler
##from iwebserver import IServerStatistic, IWebServer

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol


class AsyncThriftException( Exception ):
    pass

class ThriftHandler( JsonHandler ):
    """ main http request mapper (раскидываем запросы по handler methods, в зависимости от "/subaddr" и "action=") """
    ##_SERVICES = { 'serverinfo': ServerInfoHandler )
    
    def __init__( self, application, request, SERVICES={}, **kwargs):
        JsonHandler.__init__( self, application, request, **kwargs )
        self._SERVICES = SERVICES

    ##-------------------------------------------------------------------------------------
    
    def get(self):
        raise tornado.web.HTTPError(400)
    
    @tornado.web.asynchronous
    def post(self):
        params = self.request.arguments
        info( "Post Params: " + str(params) )
        
        self.service = self.getParam("service", "")
        if self.service in self._SERVICES:
            self.set_header("Content-Type", "application/thrift")
            self.set_header("charset", "UTF-8")


            b = str(self.request.body)
            info( "post body: %s\n ...\n %s", b[:128], b[-128:])
            
            if self.request.body:
                HandlerClass = self._SERVICES[ self.service ]
                if HandlerClass: 
                    ProcessorClass = HandlerClass.getProcessorClass()
                    if ProcessorClass:
                        handler = HandlerClass( self ) # отдаем хэндлеру указатель на себя, пусть сам ищет чего ему надо (self.request = запрос, self.I = словарь интерфейсов..)
                        self.processor = ProcessorClass( handler )  
                        
                        # !!! NB: в этом сценарии создаем отдельный processor на каждый вызов, так что обращения к "памяти" процессора, типа client.getStruct(1) не пройдут
                        
                        self.ifactory = TBinaryProtocol.TBinaryProtocolAcceleratedFactory()
                        self.otrans = TTransport.TMemoryBuffer()
                        self.oprot = self.ifactory.getProtocol( self.otrans )
                        
                        self.process()
                        ##debug( "otrans: %s" % str(self.otrans) )
                        ##debug( "oprot: %s" % str(self.oprot) )
                        return 
                    
                    else:
                        raise tornado.web.HTTPError(400)
                else:
                    raise tornado.web.HTTPError(400)
            else:
                raise tornado.web.HTTPError(400)
                
        #FAIL:
        raise tornado.web.HTTPError(403)

    # -------------------------------------------------------------------------------------------------------
    # возвращаем !=0 когда требуется асинхронная обработка (подождите, не надо сразу заворачивать ответ)
    def process(self):
        # входной протокол придется инициализировать заново (т.к. если нас вызывают повторно и асинхронно -- получается, что один раз мы уже считали все аргументы)
        info("thrift.process")
        self.itrans = TTransport.TMemoryBuffer( self.request.body )
        self.iprot = self.ifactory.getProtocol( self.itrans )
        try:
            self.processor.process( self.iprot, self.oprot )
            self.fin()
        except AsyncThriftException, e:
            info( "AsyncThriftException: %s" % str(e) )
            return True # ждем, пока handler не выполнит свою асинхронную магию и не вызовет наш process() еще раз
        except Exception:
            error( "thrift process exception" )
            catch()
            return self.finish()

    # ------------------------------------------------------------------------
    def fin(self):
        self.response = self.otrans.getvalue()
        self.write(self.response)
        self.finish()
        
    def on_connection_close(self): # PF-93560 - override JsonHandler.on_connection_close since here there is no self.actionHandler
        info("on_connection_close: %s %s (t=%s)", self.request.method, self.request.uri, self.request.request_time())
