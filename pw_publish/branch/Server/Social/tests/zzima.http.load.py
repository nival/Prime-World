# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, random, json, hashlib, urllib, httplib, thread, logging

import gc
gc.disable()

os.chdir("..")
sys.path.append('.')

from base.helpers import * 

import tornado.options
from tornado.options import define,options
import tornado.ioloop
from tornado.httpclient import HTTPRequest, AsyncHTTPClient

import Queue, urllib2

#define("server", default="127.0.0.1:88", help="connect to given ip:port")
define("num_queries", default=100, help="number or queries", type=int)
define("num_threads", default=10, help="http client count", type=int)
define("num_http_connections", default=2, help="number or concurrent http connections", type=int)
define("scenario", default="urllib2", help="test scenario: tornado|urllib2")

XML_URL = "http://b210.nivalnetwork.com:8082/API/PL/ZZServiceWeb.asmx"
XML_HEADERS = {'SOAPAction': u'"http://zzima.com/GetUserBalance"', 'Content-Type': 'text/xml; charset=utf-8'}

clientQueriesDone = 0

def handle_reply( response ):
    global clientQueriesDone
    info( "[%d] response: %s" % (clientQueriesDone, response) )
    info( "[%d] body: %s" % (clientQueriesDone, response.body) )
    
    clientQueriesDone += 1
    if clientQueriesDone >= options.num_queries:
        tornado.ioloop.IOLoop.instance().stop()
        
        
def urllibThreadFunc( thread_num, queue ):
    info( "[%d] urllib thread started: %.3f" % (thread_num, time.time()) )
    rcount = 0
    while 1:
        try:
            body = queue.get_nowait()
            request = urllib2.Request( XML_URL, body, headers=XML_HEADERS )
            
            try:
                info( "[%d] %.3f request (%d): %s" % (thread_num, time.time(), rcount, request))
                t0 = time.time()
                reply = urllib2.urlopen( request ).read()
                t1 = time.time()
                info( "[%d] %.3f reply(%d): %s, \nrequest time %.3f" % (thread_num, t1, rcount, reply, t1-t0 ))
            except:
                catch()
            
            queue.task_done()
            rcount += 1
            
        except:
            info( "[%d] %.3f queue.get failed, urllib thread exiting.. (%d tasks done)" % (thread_num, time.time(), rcount) )
            return
    
##--------------------------------------------------------------------------------
## старт 
def main():
    tornado.options.parse_command_line()

    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        opts = options.as_dict().keys()
        opts.sort()
        for opt in opts:
            print( "--%s = %r" % (str(opt), options[opt]));
    else:
        opts = options.keys()
        opts.sort()
        for opt in opts:
            print( "--%s = %r" % (str(opt), options[opt].value()));
        
    print "Test client start: scenario %r, %d threads x %d conns x %d queries" % (options.scenario, options.num_threads, options.num_http_connections, options.num_queries)
    
    logging.basicConfig( filename=options.log_file_prefix, level=logging.WARNING, format='[%(asctime)s %(levelname)8s] %(message)s' )
    log( 'This message should go to the log file' )
    
    global httpAsyncClient
    httpAsyncClient = tornado.httpclient.AsyncHTTPClient( max_clients=options.num_threads ) 
    handlers = []

    XML_GETBALANCE_BODY = '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:GetUserBalance><ns0:req><ns0:crc>uEgReokHWB3k4owIccUZfA==</ns0:crc><ns0:fromServiceName>pwtst</ns0:fromServiceName><ns0:userName>%s</ns0:userName></ns0:req></ns0:GetUserBalance></ns1:Body></SOAP-ENV:Envelope>'
    
    t0 = time.time()
    
    if options.scenario == "tornado":
        for i in range(0, options.num_queries):
            request = HTTPRequest( 
                url = XML_URL,
                method = "POST",
                headers = XML_HEADERS,
                user_name = "ruopr_%d" % i,
                body = XML_GETBALANCE_BODY % user_name
            )
            
            #~ # БОЕВОЙ
            #~ request = HTTPRequest( "http://b208.nivalnetwork.com:8080/API/PL/ZZServiceWeb.asmx?WSDL", 
                #~ method = "POST",
                #~ headers = {'SOAPAction': u'"http://zzima.com/GetUserBalance"', 'Content-Type': 'text/xml; charset=utf-8'}, 
                #~ body = '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:GetUserBalance><ns0:req><ns0:crc>++P5ZGAfbw8XouPY5KZpFQ==</ns0:crc><ns0:fromServiceName>pw</ns0:fromServiceName><ns0:userName>ruopr_37343</ns0:userName></ns0:req></ns0:GetUserBalance></ns1:Body></SOAP-ENV:Envelope>'
            #~ )
            
            httpAsyncClient.fetch( request, handle_reply)
    
        info("ASYNC ioloop start")
        tornado.ioloop.IOLoop.instance().start()
        
    elif options.scenario == "urllib2":
        queries = Queue.Queue()
        for i in range(0, options.num_queries):
            user_name = "ruopr_%d" % i
            body = XML_GETBALANCE_BODY % user_name
            queries.put( body )
            
        clientQueriesDone = queries.qsize()
        info("queries in queue: %d" % queries.qsize())
            
        for i in range(0, options.num_threads):
            thread.start_new_thread(urllibThreadFunc, (i+1, queries)) # требует кортеж аргументов (tuple) для передачи в thread-func
            
        queries.join()
        
    #~ while clientThreadsDone < options.num_threads:
        #~ pass
        
    t1 = time.time()
    print "%d queries done: %0.3f sec." % (clientQueriesDone, t1-t0)


if __name__ == "__main__":
    main()
