# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network
import sys, os, time, logging, json
import urllib2

os.chdir('..')
sys.path.append( os.path.abspath('.') )

## --------- for sync tests --------------
from base.helpers import *
from ifactory import IfaceFactory
import cfg
import unittest

import ibilling 

DEFAULT_LOG_LEVEL = logging.DEBUG

def logLevel( level=DEFAULT_LOG_LEVEL ):
    logger = logging.getLogger()
    logger.setLevel( level )

import utils
class IBillingTest( unittest.TestCase ):
    
    def setUp(self):
        cfg.AGG_BILLING_PREFIX = 'redjack_trunk_'
        billingUrl = 'http://b210.nivalnetwork.com:8082/API/PL/ZZServiceWeb.asmx?WSDL'
        aggregatorUrl = 'http://ec2-46-137-34-36.eu-west-1.compute.amazonaws.com'
        self.I = ClassDict()
        self.http = utils.RealHttp()
        self.I.ZZ = IfaceFactory.makeZZimaInterface('http', billingUrl, self.http, 'pwtst')
        #self.I.AGG = IfaceFactory.makeSocAggInterface( "dummy", 'http://B373.nivalnetwork.com:9090/', '0.3.93', self.http )
        self.I.AGG = IfaceFactory.makeSocAggInterface( "http", aggregatorUrl, '0.3.93', self.http )
        self.I.BILL = IfaceFactory.makeBillingInterface( "zzima", self.I )
        self.auid = 2
        
    def _onBillingResponse(self, response):
        self.response = response
        info( "_onBillingResponse: %s" % response )
        
    def testGetBalance(self):
        logLevel()
        
        self.response = None
        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )
        
        
##----------------------------------------------------------------
##----------------------------------------------------------------

def main():
    ## print "DEFAULT_LOG_LEVEL: %s" % DEFAULT_LOG_LEVEL
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    info( "-- START tests.." )
    
    ITERATIONS = 1
    for i in range(ITERATIONS):
        try:
            unittest.main()
        except SystemExit:
            if str( exc() ) == "True":
                sys.exit(1)
        except:
            catch()
            sys.exit(1)
            
    info( "-- Finish tests (x %d)." % ITERATIONS )
    

if __name__ == "__main__":
    main()
