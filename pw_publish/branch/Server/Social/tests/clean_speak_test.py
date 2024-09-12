# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys, os
import hashlib
import urllib2
import random
import logging
import re

os.chdir('..')
sys.path.append('.')

from base.helpers import *

# -------------------------------

#~ SERVER_ADDR = '127.0.0.1'
#~ SERVER_ADDR = 'pw.nivalnetwork.com'
SERVER_ADDR = '192.168.2.76'
#~ SERVER_ADDR = 'pw.zzima.com'

HTTP_PORT = 8001
SERVER_HTTP_ADDR = '%s:%d' % (SERVER_ADDR, HTTP_PORT)
HTTP_TIMEOUT = 20.0

## --------------------------------------------------------------------------------------------------------------------------

def post( text="", server="content/item.js?", **kwargs ):
    encoded_text = utf8convert(text)
    info( "text: %s" % unicode(encoded_text, "UTF8").encode("cp866") )
    params = {
        "contentItem.content": encoded_text,
        "contentItem.type":"text",
        "filter.operation":"replace",
        "filter.blacklist.enabled":"true",
    }

    url = "http://%s/%s" % (SERVER_HTTP_ADDR, server)
    headers = { "Content-Type": "application/x-www-form-urlencoded" }
    body = urllib.urlencode( params )

    info( "url: %s, \nheaders: %s, \nbody: %s\n" % (url, headers, body) )
    request = urllib2.Request(url, body, headers)

    reply = urllib2.urlopen( request, body, HTTP_TIMEOUT ).read()
    reply = reply.replace('1,00', '0,98')
    if reply:
        reply = re.sub( r'"quality": (\d),', r'"quality": \1.', reply )
    info( "reply: %s" % unicode(reply, "UTF8").encode("cp866") )
    
    parsed_reply = json_loads(reply)
    return parsed_reply

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

DEFAULT_LOG_LEVEL = logging.INFO
#~ DEFAULT_LOG_LEVEL = logging.WARNING
logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

post( text=u"Neutral politically correct text" )

post( text=u" Holy nigger motherfucking shit!" )

#~ post( text=u"Ах ты ж ебаный ты нахуй!" )
