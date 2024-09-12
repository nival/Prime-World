# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys, os
import hashlib
import urllib2
import random
import logging

from x_client_base import *

os.chdir('..')
sys.path.append('.')

from base.helpers import *

import CC
import EC
import MM


# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------

RESPONSE_TAG = 'Packet: '

def parseClientLog( filename, model_change_tag=None ):
    acc = accNew()
    
    f = open(filename, "rt")
    info("file=%s" % f)
    for line in f:
        if line:
            pos = line.find(RESPONSE_TAG)
            if pos >= 0:
                str_response = line[(pos+len(RESPONSE_TAG)):]
                #info("response found: %s" % str_response)
                response = json_loads(str_response).get("response", {})
                #info("response json: %s" % pretty(response))
                if model_change_tag:
                    model_changes = response.get(model_change_tag)
                    if model_changes:
                        info("response[%s] json: %s" % (model_change_tag, pretty(model_changes)))
                        resultModel = accApplyModelChangesTag( acc, response, model_change_tag )
                        info("result model: %s" % pretty( resultModel.generateJsonDict() ))
                else:   
                    info("response json: %s" % pretty(response))
                    accApplyModelChangesAll( acc, response )
    
# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------
DEFAULT_LOG_LEVEL = logging.INFO

filename = "C:/Work/BUGLO/_LogParser/PW-shipping-0.12.43.21080-FullLog.log"
logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )

parseClientLog( filename, model_change_tag="TamburData" )
