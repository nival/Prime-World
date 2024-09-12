# -*- coding: utf-8 -*-

from helpers import *
import httplib, warnings, urllib2
import tornado.httpclient
from tornado.httpclient import HTTPRequest, HTTPResponse, HTTPError, AsyncHTTPClient

__all__ = ['httpLibRequest','httpClientRequest','httpUrllibRequest']

# если получится, вернем словарик response[]
def httpLibRequest( addr="127.0.0.1", server="", params="", log_id=0, log=logging.debug, client=None ):
    ret = {}
    
    strAddr = str(addr)
    strReq = "/" + str(server)
    
    if len(params):
        strReq += "?" + str(params) 
                    
    ##log( "[%d]" % log_id + strAddr + strReq )
    
    conn = None
    try:
        conn = httplib.HTTPConnection(strAddr, timeout=30)
        hdr = { "Connection": "close" }
        try:
            conn.request("GET", strReq, headers=hdr)
        except socket.error, msg:
            logging.error("socket " + str(msg))
            return ret
        
        #t0 = time.time()
        res = conn.getresponse()
        #t1 = time.time()
        #info("[%d] t%0.3f http status: " % (log_id, t1-t0) + str(res.status) + " " + str(res.reason))
        
        data1 = res.read()
        #log("[%d] http data: " % log_id + str(data1))
        
        try:
            if res.status == 200:
                json_res = json_loads(data1)
                ret = json_res["response"]
        except:
            catch()
        
    except:
        catch()
    
    try:
        if conn:
            try:
                if conn.sock:
                    conn.sock.close()
            except:
                catch()

            conn.close()
    except:
        catch()

    return ret


## tornado BLOCKING httpclient
def httpClientRequest(addr="127.0.0.1", server="", params="", client=None, log_id=0, log=logging.debug):
    ret = {}
    
    strReq = http_prefix( "%s/%s" % (addr, server) )
    
    if len(params):
        strReq += "?" + str(params) 
        
    #log( "[%d]" % log_id + strReq )
    
    http_client = client or tornado.httpclient.HTTPClient()
    try:
        response = http_client.fetch( strReq )
        if response:
            res = jsonResult( response )
            ret = res["response"]
    except HTTPError, e:
        pass
    except:
        exc()
        
    return ret

    
def httpUrllibRequest(addr="127.0.0.1", server="", params="", client=None, log_id=0, log=logging.debug):
    ret = {}
    
    strReq = http_prefix( "%s/%s" % (addr, server) )
    
    if len(params):
        strReq += "?" + str(params) 
        
    ## print "URLLIB2:", strReq
    
    ret = {}
    try:
        response = urllib2.urlopen( strReq )
        html = response.read()
        ret = json_loads( html )
    except:
        exc()
        
    return ret

