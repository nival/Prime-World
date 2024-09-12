import urllib2, urllib
import json
import threading

import logging
from logging import debug, info, error
MAX_LOG_DATA_LENGTH = 1024

import sys, traceback, time, collections
import gzip, cStringIO

def printException(exceptionInfoList):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    strList = traceback.format_exception(exceptionType, exceptionValue, exceptionTraceback)
    return ''.join(strList)

def catch():
    error(printException(sys.exc_info()))

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------

class _AsyncHTTPChannel(threading.Thread):

    def __init__(self, address, verbose):
        super(_AsyncHTTPChannel, self).__init__()
        self.address = address
        self.verbose = verbose
        self.lock = threading.Lock()
        self.requests = collections.deque()
        self.__serving = False
        self.connected = False
    
    def send(self, requestId, request, data, callback):
        if self.verbose > 1:
            debug( "channel[%s] send(%d)" % ( str(self), requestId ))
        self.lock.acquire()
        self.requests.append( (requestId, request, data, callback) )
        self.lock.release()
        
    def _send(self, requestId, request, data, callback):
        if self.verbose > 1:
            debug( "channel[%s] _send(%d)" % ( str(self), requestId ))
        responseData = None
        try:
            urlRequest = urllib2.Request( self.address+"/"+request, data )
            urlRequest.add_header("Content-Type", "text/plain")
            urlRequest.add_header("Accept-Encoding", "gzip")
            response = urllib2.urlopen( urlRequest )        
            headers = response.info()
            responseData = response.read()
            
            if self.verbose > 2:
                debug( "response(%d) headers: %s" % (requestId, str(headers)) )
            if str(headers).find("Content-Encoding: gzip") >= 0:
                if self.verbose > 2:
                    debug( "response(%d) GZIP response data: %s" % (requestId, str(responseData)) )
                _gzip_value = cStringIO.StringIO( responseData )
                _gzip_file = gzip.GzipFile(mode="rb", fileobj=_gzip_value)
                responseData = _gzip_file.read()
            
            self.connected = True
        except: #except urllib2.URLError, details:
            catch()
            self.connected = False
        callback(requestId, responseData)
        
    def run(self):
        self.__serving = True
        while self.__serving:
            self.lock.acquire()
            try:
                if len(self.requests) > 0:
                    requestId, request, data, callback = self.requests.popleft()
                    self._send(requestId, request, data, callback)
            except:
                catch()
            self.lock.release()
            time.sleep(0.001)
                
                    
    def shutdown(self):
        self.__serving = False                    
        
    def isConnected(self):
        return self.status        

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------

class AsyncHTTPChannel(object):

    def __init__(self, address, verbose=0, threadCount=1):
        self.threads = []
        for i in range(threadCount):
            self.threads.append(_AsyncHTTPChannel(address, verbose))
        self.lock = threading.Lock()
        self.requestId = 0
        self.verbose = verbose
        self.requests = {}
        self.started = False

    def __del__(self):
        self.shutdown()
    
    def send(self, request, data, callback, responseCallback):
        self.lock.acquire()
        requestId = self.requestId
        self.requestId += 1
        if self.verbose > 0:
            if not data:
                debug('request(%d):%s' % (requestId, request))
            else:
                debug('request(%d):%s %r' % (requestId, request, data))
        self.requests[requestId] = (callback, responseCallback)
        self.lock.release()
        self.threads[requestId % len(self.threads)].send(requestId, request, data, self.OnResponse)
        return requestId
        
    def OnResponse(self, requestId, data):
        self.lock.acquire()
        callback, responseCallback = self.requests[requestId]
        del self.requests[requestId]
        
        if self.verbose > 0:
            str_data = str(data)
            if len(str_data) <= MAX_LOG_DATA_LENGTH:
                debug('response(%d): %s' % (requestId, str(data)))
            else:
                debug( "response(%d) START: %s'\n...\n%s" % (requestId, str_data[:MAX_LOG_DATA_LENGTH/2], str_data[-MAX_LOG_DATA_LENGTH/2:] ) )

        self.lock.release()
        if data:
            responseCallback(requestId, data, callback)
        else:
            responseCallback(requestId, None, callback)

    def shutdown(self):
        for thread in self.threads:
            thread.shutdown()

    def start(self):
        if not self.started:
            self.started = True             
            for thread in self.threads:
                thread.start()
        
    def isConnected(self):
        for thread in self.threads:
            if thread.isConnected():
                return True
        return False

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------

class JsonChannel:

    def __init__(self, channel):
        self.channel = channel
        self.outBandwidth = 0
        self.inBandwidth = 0

    def start(self):
        self.channel.start()

    def shutdown(self):
        self.channel.shutdown()

    def send(self, data, _request, callback, page=None):
        if page:
            request = page+"?"+_request 
        else:
            request = "?"+_request 
        self.outBandwidth += len(request)
        if data:
            self.outBandwidth += len(data)
        return self.channel.send(request, data, callback, self.OnResponse)

    def OnResponse(self, requestId, data, callback):
        if data:
            self.inBandwidth += len(data)
            result = json.loads(data)
            callback(requestId, result)    
        else:
            callback(requestId, None)    
