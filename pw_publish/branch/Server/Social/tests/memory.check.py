#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import urllib2
import ujson
import json
import zlib
import gzip
import cStringIO
import gc

gc.disable()

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

os.chdir('..')
_addPath('.')

from base.helpers import *

_addPath("cfg")
import coord_cfg

ALWAYS_GC = 0

# gc.set_debug( gc.DEBUG_UNCOLLECTABLE  ) 

import logging
DEFAULT_LOG_LEVEL = logging.INFO
logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )

try:
    from wmi import WMI
    info("loading WMI..")
    _wmi = WMI('.')
except:
    warn("wmi not available on this system")
    _wmi = None

# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------

try:
    import resource
    def getMemoryUsed():
        return resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
except:
    warn("resource.getrusage not supported on this system")
    def getMemoryUsed():
        return 0 
        
def proc_memory_usage():
    """Memory usage of the current process in kilobytes."""
    status = None
    result = {'peak': 0, 'rss': 0}
    try:
        # This will only work on systems with a /proc file system
        # (like Linux).
        status = open('/proc/self/status')
        for line in status:
            parts = line.split()
            key = parts[0][2:-1].lower()
            if key in result:
                result[key] = int(parts[1])
    except:
        pass
    finally:
        if status is not None:
            status.close()
    return result
    

def memory_wmi():
    if _wmi:
        result = _wmi.query("SELECT WorkingSet FROM Win32_PerfRawData_PerfProc_Process WHERE IDProcess=%d" % os.getpid())
        info("memory_wmi result[0]: %s" % result[0])
        return int(result[0].WorkingSet)
    return 0

def checkMemory(tag, do_gc=ALWAYS_GC ):
    info( "--------------")
    if do_gc:
        info( "[%s] gc counts: %s" % (tag, str(gc.get_count())))
        gc_collected_count = gc.collect()
        info( "[%s] gc collected: %d, garbage size: %d" % (tag, gc_collected_count, len(gc.garbage)))
        info( "[%s] collected gc counts: %s" % (tag, str(gc.get_count())))
    info( "[%s] getrusage memory usage (unix): %r" % (tag, getMemoryUsed()))
    info( "[%s] /proc/ memory_usage (unix): %r" % (tag, proc_memory_usage())) 
    info( "[%s] wmi memory_usage (win): %r" % (tag, memory_wmi())) 
    info( "--------------")

#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------
#--------------------------------------------------------------------------------------

@profile
def test_xml():
    # -----------------
    checkMemory( "before XML" )

    # ----------------- check SD memory --------------------
    I.SD = MultiStaticData( "xdb/ExportedSocialData.xml", I.Config.getMainConfig() ).getMainSD

    # -----------------
    checkMemory( "created XML" )

    # -----------------
    info( "deleting StaticData.." )
    I.SD = None

    checkMemory( "deleted XML" )


@profile
def test_suds( client_count=10 ):
    
    # ----------------- check wsdl client memory --------------------
    from suds.client import Client 
    import base.calculate_crc as calculate_crc

    WSDL_URL = coord_cfg.COORDINATOR_ZZIMA_WSDL
    WSDL_SERVICE = coord_cfg.COORDINATOR_ZZIMA_SERVICE_NAME
    
    suds_clients = {}
    results = {}
    
    for i in xrange(client_count):
        suds_clients[i] = Client( WSDL_URL )

    # -----------------
    checkMemory( "created suds clients" )

    args = {
        'fromServiceName' : WSDL_SERVICE,
        'userName' : 'someusername'
    }
    args['crc'] = calculate_crc.forGetUserBalance(args)
    method = 'GetUserBalance'

    for i in xrange(client_count):
        info( "suds runQuery: method %r, params %r" % (method, args) )
        results[i] = eval('suds_clients[i].service.%s(args)' % method)
        info( "suds runQuery result: %r" % dict(results[i]) )

    # -----------------
    checkMemory( "run suds queries" )
    
    info( "deleting suds client.." )
    suds_clients = None
    results = None

    # -----------------
    checkMemory( "deleted suds" )

def cutTag(tag, response):
    cut = None
    open_tag = "<%s>" % tag
    close_tag = "</%s>" % tag
    pos1 = response.find(open_tag)
    pos2 = response.find(close_tag)
    if pos1 >= 0 and pos2 >= pos1:
        cut = response[ pos1+len(open_tag) : pos2 ]
    return cut

@profile
def test_http_billing( client_count=1 ):
    
    # ----------------- check wsdl client memory --------------------
    import base.calculate_crc as calculate_crc

    WSDL_URL = coord_cfg.COORDINATOR_ZZIMA_WSDL
    WSDL_SERVICE = coord_cfg.COORDINATOR_ZZIMA_SERVICE_NAME

    # -----------------
    args = ClassDict( {
        'fromServiceName' : WSDL_SERVICE,
        'userName' : 'someusername'
    } )
    args['crc'] = calculate_crc.forGetUserBalance(args)
    method = 'GetUserBalance'

    info( "urllib WSDL query: method %r, args %r" % (method, args) )
    
    HEADERS = { 
        'SOAPAction': u'"http://zzima.com/%s"' % method, 
        'Soapaction': u'"http://zzima.com/%s"' % method,
        'Content-Type': 'text/xml; charset=utf-8', 
        'Content-type': 'text/xml; charset=utf-8', 
    }
    
    BODY = '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:$METHOD><ns0:req><ns0:crc>$CRC</ns0:crc><ns0:fromServiceName>$FROM_SERVICE</ns0:fromServiceName><ns0:userName>$USER_NAME</ns0:userName></ns0:req></ns0:$METHOD></ns1:Body></SOAP-ENV:Envelope>'
    
    BODY = BODY.replace( "$METHOD", method )
    BODY = BODY.replace( "$FROM_SERVICE", args.fromServiceName )
    BODY = BODY.replace( "$USER_NAME", args.userName )
    BODY = BODY.replace( "$CRC", args.crc )
    
    info("url: %r" % WSDL_URL)
    info("headers: %r" % HEADERS)
    info("body: %r" % BODY)
    request = urllib2.Request(WSDL_URL, BODY, HEADERS)
    
    result_dicts = {}
    for i in xrange(client_count):
        result = urllib2.urlopen(request).read()
        
        info( "urllib runQuery result: %r" % (result) )
        
        res_string = cutTag("GetUserBalanceResult", result) or ""
                      
        code = toint( cutTag("code", res_string))
        message = cutTag("message", res_string)
        error = toint( cutTag("error", res_string))
        amount = tofloat( cutTag("amount", res_string))
        
        result_dicts[i] = dict( code=code, message=message, error=error, amount=amount )
        
        info( "urllib result dict: %r" % (result_dicts[i]) )
    
    #~ while 1:
      #~ pass
    # -----------------
    checkMemory( "done urllib query" )


@profile
def main():
    _addPath("base")
    
    import config.MultiConfig
    from modeldata.MultiStaticData import MultiStaticData
    I = ClassDict()
    I.Config = config.MultiConfig.MultiConfig()
    I.SD = MultiStaticData( "C:/sources/pw_lobby/SocialServer/xdb/ExportedSocialData.xml", I.Config.getMainConfig() ).getMainSD()
    I.Config.fillStaticDataDependendValues(I.SD)

    _addPath("libs")

    # ------------------------------------------------------------------------------------
    # ------------------------------------------------------------------------------------
    # ------------------------------------------------------------------------------------

    #test_xml()

    #test_suds( 10 )
    test_http_billing( 10 )

    #checkMemory( "done", do_gc=1 )

    #~ while 1:
      #~ pass

    #-----------------------        
    os.chdir('tests')
    


# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------

main()
