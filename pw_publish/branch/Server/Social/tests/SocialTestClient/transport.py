import urllib2, urllib
import ujson
import threading

import logging
from logging import debug, info
MAX_LOG_DATA_LENGTH = 2048

import sys, traceback, time, collections
import gzip, cStringIO

def printException(exceptionInfoList):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    strList = traceback.format_exception(exceptionType, exceptionValue, exceptionTraceback)
    strOutput = "catch:"
    for s in strList:   
        strOutput += s
    return strOutput 

def catch():
    print printException(sys.exc_info())

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
def convertAddress(address):
    index0 = address.rfind('.')
    index1 = address.rfind('/')
    if index1 < index0:
        return address + '/'
    return address

class _AsyncHTTPChannel(threading.Thread):

    def __init__(self, address, send_timeout=10.0):
        super(_AsyncHTTPChannel, self).__init__()
        self.address = address
        self.lock = threading.Lock()
        self.requests = collections.deque()
        self.__serving = False
        self.connected = False
        self.send_timeout = send_timeout
    
    def send(self, requestId, request, data, callback):
        self.lock.acquire()
        self.requests.append( (requestId, request, data, callback) )
        self.lock.release()
        
    def _send(self, requestId, request, data, callback):
        debug( "request sent (channel=%s id=%d)" % ( str(self), requestId ))
        responseData = None
        try:
            address = convertAddress(self.address)+request
            urlRequest = urllib2.Request( address, data, headers={"Accept-Encoding":"gzip"} )
            response = urllib2.urlopen( urlRequest, None, timeout=self.send_timeout )
            headers = response.info()
            responseData = response.read()
            
            ##debug( "response(%d) headers: %s" % (requestId, str(headers)) )
            if str(headers).find("Content-Encoding: gzip") >= 0:
                info( "response(%d) GZIP response data(size=%d)" % (requestId, len(responseData)) )
                _gzip_value = cStringIO.StringIO( responseData )
                _gzip_file = gzip.GzipFile(mode="rb", fileobj=_gzip_value)
                responseData = _gzip_file.read()
            
            self.connected = True
        except: #except urllib2.URLError, details:
            catch()
            self.connected = False
        debug( "request recieve (channel=%s id=%d)" % ( str(self), requestId ))
        callback(requestId, responseData)
        
    def run(self):
        self.__serving = True
        counter = 0
        while self.__serving:
            self.lock.acquire()
            try:
                if len(self.requests) > 0:
                    requestId, request, data, callback = self.requests.popleft()
                    self._send(requestId, request, data, callback)
            except:
                catch()
            self.lock.release()
            time.sleep(0.005)
            
            #~ counter += 1
            #~ if (counter % 1000) == 0:
                #~ info( "thread %s alive" % str(self) )
                
                    
    def shutdown(self):
        self.__serving = False                    
        
    def isConnected(self):
        return self.status        

# ----------------------------------------------------------------------
# ----------------------------------------------------------------------

class AsyncHTTPChannel(object):

    def __init__(self, address, verbose=0, threadCount=1, send_timeout=10.0):
        self.address = address
        self.threads = []
        for i in range(threadCount):
            self.threads.append(_AsyncHTTPChannel(address, send_timeout=send_timeout))
        self.lock = threading.Lock()
        self.requestId = 0
        self.verbose = verbose
        self.requests = {}
        self.started = False
    
    def send(self, request, data, callback, responseCallback):
        self.lock.acquire()
        requestId = self.requestId
        self.requestId += 1
        if self.verbose > 0:
            if not data:
                info('request(%d):%s/%s' % (requestId, self.address, request))
            else:    
                info('request(%d):%s/%s %r'  % (requestId, self.address, request, data))
        self.requests[requestId] = (callback, responseCallback)
        self.lock.release()
        self.threads[requestId % len(self.threads)].send(requestId, request, data, self.OnResponse)
        return requestId
        
    def OnResponse(self, requestId, data):
        self.lock.acquire()
        callback, responseCallback = self.requests[requestId]
        del self.requests[requestId]
        
        if self.verbose >= 1:
            str_data = str(data)
            if len(str_data) <= MAX_LOG_DATA_LENGTH:
                info('response(%d): %s %s' % (requestId, self.address, str(data)))
            else:
                info( "response(%d) %s START: %s'\n...\n%s" % (requestId, self.address, str_data[:MAX_LOG_DATA_LENGTH/2], str_data[-MAX_LOG_DATA_LENGTH/2:] ) )

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

    def send(self, data, __request, callback, page=None):
        _request = urllib.urlencode(__request)
        if page:
            request = page 
        else:
            request = ''
        if _request:
            request += '?'+_request

        self.outBandwidth += len(request)
        if data:
            self.outBandwidth += len(data)
        return self.channel.send(request, data, callback, self.OnResponse)

    def OnResponse(self, requestId, data, callback):
        if data:
            self.inBandwidth += len(data)
            result = ujson.decode(data)
            callback(requestId, result)    
        else:
            callback(requestId, None)    

if __name__ == '__main__':
    assert 'http://127.0.0.1:88/' == convertAddress('http://127.0.0.1:88')
    assert 'http://127.0.0.1:88/chat0' == convertAddress('http://127.0.0.1:88/chat0')