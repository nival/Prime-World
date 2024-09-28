# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, random, json, hashlib, urllib, httplib, thread, logging

########################
import asyncore, socket
import urllib2


sys.path.append('base')
from helpers import * 
from http_dumb import *

sys.path.append('tornado')
import tornado.options
from tornado.options import define,options

import tornado.ioloop

define("server", default="127.0.0.1:88", help="connect to given ip:port")
define("num_threads", default=10, help="http client thread count", type=int)
define("num_queries", default=2, help="number or query pairs", type=int)
define("scenario", default="keepalive", help="test scenario: random|keepalive|async|asyncore")
#define("scenario", default="async", help="test scenario: random|keepalive|async")
#define("scenario", default="asyncore", help="test scenario: random|keepalive|async")

def randomUserId():
    return random.randint(1,5)

httpClientRequest = httpLibRequest #httpUrllibRequest

def    doClientRequest( http_client, addr=options.server, server=None, action="login", uid=0, uid2=0, threadId=0 ):
    ret = {}
    
    if not uid:
        uid = randomUserId()
    
    if action == "login":
        user = "user%d" % uid
        pwd = "pwd%d" % uid
        auth = hashlib.md5(pwd).hexdigest()
        if server == None:
            server = pickRandom( ["one", "two", "BAD", "", "", "", "", "", ""] ) # с шансом 2/3 будет правильный запрос к балансеру
        
        strReq = "action=%s&user=%s&auth=%s" % (action, urllib.quote(user), urllib.quote(auth)) 
        
    elif action == "keepalive":
        key = 12345
        if server == None:
            server = pickRandom( ["one", "two", "one", "two", "BAD", ""] ) # с шансом 2/3 будет запрос к одному из WS
        
        strReq = "action=%s&uid=%d&key=%d" % (action, uid, key) 
                    
    elif action == "give":
        key = 12345
        if server == None:
            server = pickRandom( ["one", "two", "one", "two", "BAD", ""] ) # с шансом 2/3 будет запрос к одному из WS
            
        if not uid2:
            uid2 = randomUserId()
        user2 = "user%d" % uid2
        
        strReq = "action=%s&uid=%d&key=%d&user2=%s" % (action, uid, key, user2) 
        
    #str_message = urllib.quote( send_message.encode('utf-8', 'replace') ) #.encode('cp1251', 'replace') )
    #log( "[%d]" % threadId + strAddr + "/" + server + "?" + strReq )
    
    ret = httpClientRequest( addr=addr, server=server, params=strReq, client=http_client )
    
    return ret
    

clientThreadsDone = 0

##--------------------------------------------------------------------------------
## нагрузка: посылаем случайные запросы (login/keepalive) на случайный сервер 
def randomThreadFunc( threadId, maxQueryCount ):
    t0 = time.time()
    
    for i in range(0,maxQueryCount):
        user_id = randomUserId()
        
        ret = httpClientRequest( uid=user_id, threadId=threadId )
        if ret and ret.has_key("uid"):
            user_id = ret["uid"]
        
        httpClientRequest( action="keepalive", uid=user_id, threadId=threadId )
        
        time.sleep(0.001)
    
    t1 = time.time()
    
    fin = "-- thread #%d FINISHED: %d queries, %0.4f sec" % (threadId, maxQueryCount*2, t1-t0)
    log( fin )
    print fin
    
    global clientThreadsDone
    clientThreadsDone += 1


#DEBUG
#doClientRequest = doHttpLibRequest


##--------------------------------------------------------------------------------
## эмуляция "нормального клиента": логинимся, периодически шлем keepalive, подолгу спим
def keepaliveThreadFunc( threadId, maxQueryCount, sleepTime ):
    httpClient = tornado.httpclient.HTTPClient()
    queryCount = 0
    totalTime = 0.0
    while queryCount < maxQueryCount:
        user_id = randomUserId()
        t0 = time.time()
        ret = doClientRequest( httpClient, addr=options.server, action="login", server="", uid=user_id, threadId=threadId )
        t1 = time.time()
        totalTime += t1-t0;
        
        info( "[%d] t%0.3f-" % (threadId, t1-t0) + str(ret) )
        queryCount += 1
        
        if ret and ret.get("ok"):
            # login ok
            user_id = ret.get("uid")
            server_name = ret.get("server")
            
            while queryCount < maxQueryCount:
                time.sleep(sleepTime) # долго спим

                t0 = time.time()
                #ret = doClientRequest( httpClient, action="keepalive", server=server_name, uid=user_id, threadId=threadId )
                ret = doClientRequest( httpClient, addr=options.server, action="give", server=server_name, uid=user_id, threadId=threadId )
                t1 = time.time()
                totalTime += t1-t0;
                
                info( "[%d] t%0.3f-" % (threadId, t1-t0) + str(ret) )
                queryCount += 1
                
    fin = "-- thread #%d FINISHED: %d queries, total req time: %0.3f" % (threadId, queryCount, totalTime)
    warn( fin )
    print fin
    
    global clientThreadsDone
    clientThreadsDone += 1

    
##--------------------------------------------------------------------------------

def startRandomThreads( num_threads=1 ):
    for i in range(0,num_threads):
        # запускаем N thread'ов с коннектами
        thread.start_new_thread(randomThreadFunc, (i+1, options.num_queries)) # требует кортеж аргументов (tuple) для передачи в thread-func

def startKeepaliveThreads( num_threads=1 ):
    for i in range(0,num_threads):
        # запускаем N thread'ов с коннектами
        thread.start_new_thread(keepaliveThreadFunc, (i+1, options.num_queries, 1)) # требует кортеж аргументов (tuple) для передачи в thread-func
        time.sleep(0.001)
        
##--------------------------------------------------------------------------------
httpAsyncClient = None
asyncReplyCount = 0

# пока просто один глобальный хэндлер (проверял, что вариант self.callback в принципе работает с libCURL)
class AsyncHandler:
    def __init__(self, id):
        self.id = id
        self.t0 = time.time()
        
    def handle_login(self, response):
        if response.error:
            print "Error:", response.error
        else:
            self.t1 = time.time()
            info( "handle_login[%d] t%0.3f: %s" % ( self.id, self.t1-self.t0, response.body ) )
            
            res = json_loads(response.body)
            ret = res["response"]
            if ret: # and ret.get("ok"):
                uid = ret.get("uid", 0)
                server = ret.get("server", "")
                    
                httpAsyncClient.fetch( options.server + "/%s?action=keepalive&uid=%d&key=12345" % (server, uid), self.handle_ka)
            else:
                asyncReplyCount += 1 # этот логин не прошел
            
    def handle_ka(self, response):
        if response.error:
            print "Error:", response.error
        else:
            self.t2 = time.time()
            info( "handle_ka[%d] t%0.3f, total req time: %0.3f: %s\n" % ( self.id, self.t2-self.t1, self.t2-self.t0, response.body ) )
            
            global asyncReplyCount
            asyncReplyCount += 1
            if asyncReplyCount >= options.num_threads:
                tornado.ioloop.IOLoop.instance().stop()


class AsyncSocketClient(asyncore.dispatcher):

    def __init__(self, id, strhost, path):
        asyncore.dispatcher.__init__(self)
        self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
        
        self.t0 = time.time()
        self.id = id
        self.can_close = 0
        
        host, port = strhost.split(":")
        self.connect( (host, int(port)) )
        self.buffer = 'GET %s HTTP/1.0\r\n\r\n' % path

    def handle_connect(self):
        pass

    def handle_close(self):
        self.close()

    def handle_read(self):
        self.t1 = time.time()
        text = self.recv(8192)
        if text and len(text):
            # header от body отделяется пустой строкой
            empty_string = "\r\n\r\n"
            pos = text.find(empty_string)
            if pos > 0:
                body = text[ pos+len(empty_string): ]
            else:
                body = "???"
            info( "handle_read[%d] t%0.3f: len %d\n" % ( self.id, self.t1-self.t0, len(text) ) + body )
            
            ret = {}
            try:
                ret = json_loads( body )["response"]
            except:
                exc()
                
            self.handle_response(ret)
                
    def handle_response(self, dict):
        pass

    def writable(self):
        return (len(self.buffer) > 0)

    def handle_write(self):
        sent = self.send(self.buffer)
        self.buffer = self.buffer[sent:]

class AsyncoreHandler(AsyncSocketClient):
    def handle_response(self, res):
        if res and res.get("ok"):
            info( "handle_response[%d]: %s" % ( self.id, str(res) ) )
            
            #~ if res.get("uid"):
                #~ info("repost")
                #~ uid = res.get("uid", 0)
                #~ server = res.get("server", "")
                    
                #~ path = options.server + "/%s?action=keepalive&uid=%d&key=12345" % (server, uid)
                #~ self.buffer = 'GET %s HTTP/1.0\r\n\r\n' % path

    #~ def handle_close(self):
        #~ warn("handle_close")
        #~ if self.can_close:
            #~ self.close()

##--------------------------------------------------------------------------------
## старт 
def main():
    tornado.options.parse_command_line()

    #~ opts = options.keys()
    #~ opts.sort()
    #~ for opt in opts:
        #~ print( "--%s = %s" % ( str(opt), str(options[opt].value()) ));
        
    print "Test client start: scenario %r, %d threads x %d query pairs" % (options.scenario, options.num_threads, options.num_queries)
    
    logging.basicConfig( filename=options.log_file_prefix, level=logging.DEBUG, format='[%(asctime)s %(levelname)8s] %(message)s' )
    log( 'This message should go to the log file' )
    
    global httpAsyncClient
    httpAsyncClient = tornado.httpclient.AsyncHTTPClient( max_clients=options.num_threads ) #, max_simultaneous_connections= )
    handlers = []

    t0 = time.time()
    
    if options.scenario == "async":
        for i in range(0, options.num_threads):
            uid = randomUserId()
            user = "user%d" % uid
            pwd = "pwd%d" % uid
            auth = hashlib.md5(pwd).hexdigest()
            asyncHandler = AsyncHandler(i)
            handlers.append( asyncHandler )    
            httpAsyncClient.fetch( options.server + "/?action=login&user=%s&auth=%s" % (user, auth), asyncHandler.handle_login)

        info("ASYNC ioloop start")
        tornado.ioloop.IOLoop.instance().start()
        
        return
        
    elif options.scenario == "asyncore":
        for i in range(0, options.num_threads):
            uid = randomUserId()
            user = "user%d" % uid
            pwd = "pwd%d" % uid
            auth = hashlib.md5(pwd).hexdigest()
            
            c = AsyncoreHandler( i, options.server, "/?action=login&user=%s&auth=%s" % (user, auth) )
        
        info("ASYNCORE loop start")
        asyncore.loop()
        
        return
        
    if options.scenario == "keepalive":
        startKeepaliveThreads( options.num_threads ) 
    else:
        startRandomThreads( options.num_threads ) 
    
    while clientThreadsDone < options.num_threads:
        pass
        
    t1 = time.time()
    print "%d threads done: %0.3f sec." % (clientThreadsDone, t1-t0)



if __name__ == "__main__":
    main()
