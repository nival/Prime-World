# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json

os.chdir('..')
sys.path.append( os.path.abspath('.') )

## --------- for sync tests --------------
from base.helpers import *
from handlers import resetGlobals, users, SOCAGG_VERSION # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
import imemcache, isql, ihttp, idata

import cfg, coord_cfg # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора
## --------- for Async (real MC/SQL/HTTP) test --------------
import thread, tornado.ioloop # для тестов, требующих асинхронной обработки
from tornado.options import options, define
from iwebserver import IWebServer

# ---------------------------------
from binascii import crc32   # zlib version is not cross-platform
# ---------------------------------
import unittest
import iaggregator

from base_loop_test import *

""" Базовый класс для тестов, требующих асинхронной обработки, с участием настоящих async-thread-pool & IOLoop. """
class AggregatorTest( BaseLoopTest ):

    #----------------------------------------------------------------
    # локальная заглушка (test case)
    
    def onSocialAggregatorCallback(self, reply):
        ##info( "onSocialAggregatorCallback: reply %r" % reply )
        self.reply = json_loads( reply.body ) #.get("response")
        info( "onSocialAggregatorCallback reply: " + str(self.reply) )

    def testISocialAggregator(self):
        ##logLevel( logging.INFO )
        info( "---------- testISocialAggregator ----------" )
        
        SA = iaggregator.ISocialAggregator( SOCAGG_VERSION )
        SA.login( "uid12345", "token12345", "fb", callback=self.onSocialAggregatorCallback)
        self.assert_( self.reply.get("error") == 0 )
        
        SA.getInfo( "12345", "fb", 1, callback=self.onSocialAggregatorCallback )
        self.assert_( self.reply.get("error") == 0 )
        self.assert_( self.reply["get_info"]["fb"] )
        self.assert_( self.reply["get_info"]["fb"].get("email") )
        
        
    #--------------------------------------------------------------------------------------------
    # HTTP MockSocialAggregator test case 
    # !!! ЛОКАЛЬНО ДОЛЖЕН БЫТЬ ЗАПУЩЕН mock_aggregator.py! (или настоящий social aggregator)
    
    def onHttpSocialAggregatorCallback(self, reply):
        ##info( "onHttpSocialAggregatorCallback: http reply %r" % reply )
        self.reply = json_loads( reply.body ) #.get("response")
        info( "onHttpSocialAggregatorCallback reply: " + str(self.reply) )
        
    def testHttpSocialAggregator(self):
        ##logLevel( logging.INFO )
        info( "---------- testHttpSocialAggregator ----------" )
        
        SA = iaggregator.IRealSocialAggregator( cfg.SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, \
            HTTP=tornado.httpclient.AsyncHTTPClient( max_clients=2 )  )
        
        self.reply = None
        SA.login( "uid12345", "token12345", "fb", callback=self.onHttpSocialAggregatorCallback)
        self.waitAsyncReply( self, 0.5 )
        self.assert_( self.reply.get("error") == 0 )
            
        self.reply = None
        SA.getInfo( "12345", "fb", 1, callback=self.onHttpSocialAggregatorCallback )
        self.waitAsyncReply( self, 0.5 )
        self.assert_( self.reply.get("error") == 0 )
        self.assert_( self.reply["get_info"]["fb"] )
        self.assert_( self.reply["get_info"]["fb"].get("email") )
        
        self.reply = None
        SA.getInfo( "12345", "fb", 0, callback=self.onHttpSocialAggregatorCallback )
        self.waitAsyncReply( self, 0.5 )
        self.assert_( self.reply.get("error") == 0 )
        self.assert_( self.reply["get_info"]["fb"] )
        self.assert_( self.reply["get_info"]["fb"].get("email") == None)

##----------------------------------------------------------------
##----------------------------------------------------------------
    
def main():
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    logLevel(DEFAULT_LOG_LEVEL)
    
    err( "-- START tests.." )
    
    ITERATIONS = 1
    for i in range(ITERATIONS):
        try:
            unittest.main()
        except SystemExit:
            if str( exc() ) == "True":
                break
        except:
            catch()
            
    info( "-- Finish tests (x %d)." % ITERATIONS )
    

if __name__ == "__main__":
    main()
