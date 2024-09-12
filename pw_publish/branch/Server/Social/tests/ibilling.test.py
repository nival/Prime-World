# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network
import sys, os, time, logging, json

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )

from ext_main.login import LoginAction
from ext_main.auth import AuthAction
from ext_pw import *

## --------- for sync tests --------------
from base.helpers import *
from ifactory import IfaceFactory
import cfg, time, coord_cfg
import unittest

import ibilling 
import utils
import izzima

DEFAULT_LOG_LEVEL = logging.INFO

def logLevel( level=DEFAULT_LOG_LEVEL ):
    logger = logging.getLogger()
    logger.setLevel( level )

class ZZimaTest(unittest.TestCase):

    def test_ParseBalanceArray(self):
        zz = izzima.HttpZZima()  
        response = '''<?xml version="1.0" encoding="utf-8"?><soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema"><soap:Body><GetUserBalanceExResponse xmlns="http://zzima.com/"><GetUserBalanceExResult><code>0</code><detailedBalance><OperationWriteOff><paymentSystemId>1</paymentSystemId><amount>3533.00</amount></OperationWriteOff><OperationWriteOff><paymentSystemId>102</paymentSystemId><amount>270.00</amount></OperationWriteOff></detailedBalance></GetUserBalanceExResult></GetUserBalanceExResponse></soap:Body></soap:Envelope>'''     
        data = zz.parseBalanceArrayTag(response)
        self.assertEquals(3533, data['1'])
        self.assertEquals(270, data['102']) 

class DummyBillingTest( unittest.TestCase ):
    
    def setUp(self):
        self.I = ClassDict()
        self.I.BILL = IfaceFactory.makeBillingInterface( "dummy", self.I )
        self.auid = 1
        
    def _onBillingResponse(self, response):
        self.response = response
        info( "_onBillingResponse: %s" % response )

    def testGetBalanceEx(self):
        logLevel()
        self.response = None
        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )

        self.response = None
        self.I.BILL.getBalanceEx( self.auid, callback=self._onBillingResponse )
        self.assert_( self.response.get("dbalance")[None] == 1000.0 )
        
    def testWriteoffs(self):
        logLevel()
        self.response = None
        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )
        
        self.response = None
        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )
        
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 1000.0 )

        self.response = None
        self.I.BILL.writeoff( self.auid, 1.0, "buy_mouse", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 999.0 )
        
        self.response = None
        self.I.BILL.writeoff( self.auid, -1.0, "buy_bad", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") != ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 999.0 )
        
        self.response = None
        self.I.BILL.writeoff( self.auid, 0.0, "buy_bad", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") != ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 999.0 )
        
        self.response = None
        self.I.BILL.writeoff( self.auid, "123", 12325625, callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") != ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 999.0 )

        # check
        status, balance = self.I.BILL.getStatusBalance( self.auid )
        self.assert_( status == ibilling.BILLING_OK )
        self.assert_( balance == 999.0 )

        self.response = None
        self.I.BILL.writeoff( self.auid, 1000.0, "buy_elephant", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") != ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 999.0 )
        
        self.response = None
        self.I.BILL.writeoff( self.auid, 999.0, "buy_horse", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 0.0 )
        
        # повторный init (должен пройти нормально)
        self.response = None
        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 0.0 )
        
        self.response = None
        self.I.BILL.replenish( self.auid, 5.0, "replenish_5", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 5.0 )
        
        # kill
        self.I.BILL.releaseBilling( self.auid )
        # check
        status, balance = self.I.BILL.getStatusBalance( self.auid )
        self.assert_( status != ibilling.BILLING_OK )
        self.assert_( balance == 0.0 )
        
        logLevel() 
        
    def testReplenish(self):
        logLevel()
        
        self.response = None
        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )
        
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 1000.0 )

        self.response = None
        self.I.BILL.replenish( self.auid, 5.0, "replenish_5", callback=self._onBillingResponse, payment_system='STEAM' )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 1005.0 )
        self.assert_( self.response.get("payment_system") == 'STEAM' )
        
        # kill
        self.I.BILL.releaseBilling( self.auid )
        # check
        status, balance = self.I.BILL.getStatusBalance( self.auid )
        self.assert_( status != ibilling.BILLING_OK )
        self.assert_( balance == 0.0 )
        
        logLevel() 


    def testReserveConfirm( self ):
        logLevel()
        
        self.response = None
        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )
        
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 1000.0 )

        self.response = None
        self.I.BILL.reserveAmount( self.auid, 5.0, "reserve_5", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 995.0 )
        self.assert_( self.response.get("reserveId") == 1 )
        
        self.response = None
        self.I.BILL.confirmWriteOff( self.auid, 1, callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 995.0 )
        self.assert_( self.response.get("reserveId") == 1 )

        # kill
        self.I.BILL.releaseBilling( self.auid )
        # check
        status, balance = self.I.BILL.getStatusBalance( self.auid )
        self.assert_( status != ibilling.BILLING_OK )
        self.assert_( balance == 0.0 )
        
        logLevel() 


    def testReserveConfirm2( self ):
        logLevel()
        
        self.response = None
        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )
        
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 1000.0 )

        self.response = None
        self.I.BILL.reserveAmount( self.auid, 5.0, "reserve_5", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 995.0 )
        self.assert_( self.response.get("reserveId") == 1 )

        time.sleep( 6 )        

        self.response = None
        self.I.BILL.confirmWriteOff( self.auid, 1, callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_UNKNOWN )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 1000.0 )
        self.assert_( self.response.get("reserveId") == 1 )

        # kill
        self.I.BILL.releaseBilling( self.auid )
        # check
        status, balance = self.I.BILL.getStatusBalance( self.auid )
        self.assert_( status != ibilling.BILLING_OK )
        self.assert_( balance == 0.0 )
        
        logLevel() 


class MockAggregator:

    def getBillingStatus(self, auid, callback):
        data = {
            'get_billing_status' : 1,
        }
        callback(data)

class MockBilling:

    def __init__(self):
        self.get_balance = {}
        self.do_replenish = {}
        self.balance = {}
        self.reserveId = 1
    
    def getBalance(self, login, callback):
        assert login not in self.get_balance, (login, self.get_balance)
        self.get_balance[login] = callback

    def pushBalance(self, login, count, ps=None):
        callback = self.get_balance.get(login, None)
        if callback:
            del self.get_balance[login]
            self.balance[ps] = self.balance.get(ps, 0)+count
            data = {
                'r' : {  
                    'code' : 0,
                    'amount': count,   
                    'error' : 0,
                    'message' : None,
                }
            }
            callback(data)

    def replenish(self, login, amount, reason, callback, payment_system):
        assert login not in self.do_replenish
        self.do_replenish[login] = callback
        self.balance[payment_system] = self.balance.get(payment_system, 0)+amount

    def pushReplenish(self, login, error_code=0):
        callback = self.do_replenish.get(login, None)
        if callback:
            del self.do_replenish[login]
            data = {
                'r' : {  
                    'code' : error_code,
                    'error' : error_code,
                    'message' : None,
                }
            }
            callback(data)

    def writeOff(self, login, amount, reason, callback):
        data = {
            'r' : {  
                'code' : 0,
                'error' : 0,
                'message' : None,
            }
        }
        callback(data)

    def getBalanceEx(self, login, callback):
        data = {
            'r' : {  
                'code' : 0,
                'error' : 0,
                'message' : None,
                'dbalance' : self.balance,
            }
        }
        callback(data)

    def reserveAmount( self, zzima_login, amount, reason, callback):
        data = {
            'r' : {  
                'code' : 0,
                'error' : 0,
                'message' : None,
                'reserveId' : self.reserveId,
            }
        }
        self.reserveId += 1
        callback(data)

    def confirmWriteOff( self, zzima_login, reserveId, callback):
        data = {
            'r' : {  
                'code' : 0,
                'error' : 0,
                'message' : None,
            }
        }
        callback(data)

class MockWS:

    def __init__(self):
        self.guid = 1231231231231
        self.accs = {}
        self.wsShutdown = False
    
    def nextInt64GUID(self, target):
        r = self.guid
        self.guid += 1
        return r    

    def getUserAccByAuid(self, _auid):
        class Db:       
            pass
        class Account:
            def __init__(self):
                self.db = Db()
        auid = int(_auid)
        if auid not in self.accs:
            acc = Account()
            self.accs[auid] = acc
        return self.accs[auid]
        
class SteamPaymentsTest( unittest.TestCase ):
    
    def test_Simple(self):
        self.I = ClassDict()
        self.HTTP = utils.DummyHttp()
        payments = ibilling.RealPayments(self.HTTP, 'http://localhost:7868/Steam/Pay', 'PaymentSecretSalt', 'STEAM')
        class Callback:

            def onResult(self, data):
                self.data = data

        callback = Callback()
        payments.replenish(555, 100, 10, "x3", 123, callback=callback.onResult)

        goodUrl = 'http://localhost:7868/Steam/Pay?auid=555&ps=STEAM&ramount=10&txnid=123&sign=1c464fbe3ee2a879cf71a9436a93c6b6&currency=x3&amount=100'
        self.assertEquals(True, goodUrl in self.HTTP.requests)
        result = {
            'result' : 0,
            'txnid' : 123,
            'amount' : 100,
            'logid' : 777,
            'auid' : 555,
        }
        self.HTTP.push( goodUrl, json.dumps(result) )
        data = callback.data
        self.assertEquals(0, data['result'])
        self.assertEquals(123, data['txnid'])
        self.assertEquals(100, data['amount'])
        self.assertEquals(777, data['logid'])
        self.assertEquals(555, data['auid'])

    def test_Timeout(self):
        self.I = ClassDict()
        self.HTTP = utils.DummyHttp()
        payments = ibilling.RealPayments(self.HTTP, 'http://localhost:7868/Steam/Pay', 'PaymentSecretSalt', 'STEAM')
        class Callback:

            def onResult(self, data):
                self.data = data

        callback = Callback()
        payments.replenish(555, 100, 10, "x3", 123, callback=callback.onResult)

        goodUrl = 'http://localhost:7868/Steam/Pay?auid=555&ps=STEAM&ramount=10&txnid=123&sign=1c464fbe3ee2a879cf71a9436a93c6b6&currency=x3&amount=100'
        self.assertEquals(True, goodUrl in self.HTTP.requests)
        self.HTTP.push( goodUrl, None )
        data = callback.data
        self.assertEquals(ibilling.PAYMENTS_FETCH_ERROR, data['result'])
    
    def test_BadJson(self):
        self.I = ClassDict()
        self.HTTP = utils.DummyHttp()
        payments = ibilling.RealPayments(self.HTTP, 'http://localhost:7868/Steam/Pay', 'PaymentSecretSalt', 'STEAM')
        class Callback:

            def onResult(self, data):
                self.data = data

        callback = Callback()
        payments.replenish(555, 100, 10, "x3", 123, callback=callback.onResult)

        goodUrl = 'http://localhost:7868/Steam/Pay?auid=555&ps=STEAM&ramount=10&txnid=123&sign=1c464fbe3ee2a879cf71a9436a93c6b6&currency=x3&amount=100'
        self.assertEquals(True, goodUrl in self.HTTP.requests)
        self.HTTP.push( goodUrl, 'bad bad json')
        data = callback.data
        self.assertEquals(ibilling.PAYMENTS_FETCH_ERROR, data['result'])

class ZZimaBillingTest( unittest.TestCase ):
    
    def setUp(self):
        self.I = ClassDict()
        self.I.AGG = MockAggregator()
        self.I.ZZ = MockBilling()
        self.I.WS = MockWS()
        self.I.BILL = IfaceFactory.makeBillingInterface( "zzima", self.I )
        self.auid = 555

    def OnInit(self, result):
        pass

    def OnReplenish(self, result):
        pass

    def OnBalanceEx(self, result):
        self.balance_ex = result

    def test_GetBalanceEx(self):
        logLevel()
        self.I.BILL.initBilling(self.auid, self.OnInit)
        self.I.ZZ.pushBalance(str(self.auid), 70, 'merge')
        self.I.BILL.replenish(self.auid, 20, 'because', self.OnReplenish, payment_system='real')
        self.I.BILL.getBalanceEx(self.auid, self.OnBalanceEx)
        self.assertEquals(20, self.balance_ex['dbalance']['real'])
        self.assertEquals(70, self.balance_ex['dbalance']['merge'])

    def test_DoubleInit(self):
        logLevel()
        self.I.BILL.initBilling(self.auid, self.OnInit)
        self.I.BILL.initBilling(self.auid, self.OnInit)

    def test_Replenish(self):
        self.I.BILL.initBilling(self.auid, self.OnInit)
        self.I.ZZ.pushBalance(str(self.auid), 70)
        self.I.BILL.replenish(self.auid, 10, 'because', self.OnReplenish)
        self.I.ZZ.pushReplenish(str(self.auid))
        self.I.ZZ.pushBalance(str(self.auid), 80)

        self.I.BILL.getStatusBalance( self.auid, force_balance_check=True )

    def test_ReplenishFailed(self):
        self.I.BILL.initBilling(self.auid, self.OnInit)
        self.I.ZZ.pushBalance(str(self.auid), 70)

        self.I.BILL.replenish(self.auid, 10, 'because', self.OnReplenish)
        self.I.ZZ.pushReplenish(str(self.auid), -1006)
        self.I.BILL.replenish(self.auid, 10, 'because', self.OnReplenish)
        self.I.ZZ.pushReplenish(str(self.auid), -1006)

        self.I.BILL.replenish(self.auid, 10, 'because', self.OnReplenish)
        self.I.ZZ.pushReplenish(str(self.auid))
        self.I.ZZ.pushBalance(str(self.auid), 80)

        self.I.BILL.getStatusBalance( self.auid, force_balance_check=True )

    def _onBillingResponse(self, response):
        self.response = response
        info( "_onBillingResponse: %s" % response )

    def testReserveConfirm( self ):
        cfg.BILLING_RESERVE_ENABLED = True

        self.I.BILL.initBilling( self.auid, callback=self._onBillingResponse )
        self.I.ZZ.pushBalance(str(self.auid), 80)
        
        self.response = None
        self.I.BILL.reserveAmount( self.auid, 5.0, "reserve_5", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 75.0 )
        self.assert_( self.response.get("reserveId") == 1 )

        self.I.ZZ.pushBalance(str(self.auid), 75)
        
        self.response = None
        self.I.BILL.confirmWriteOff( self.auid, 1, callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 75.0 )
        self.assert_( self.response.get("reserveId") == 1 )

        self.I.ZZ.pushBalance(str(self.auid), 75)

        self.response = None
        self.I.BILL.reserveAmount( self.auid, 5.0, "reserve_5", callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 70.0 )
        self.assert_( self.response.get("reserveId") == 2 )

        self.I.ZZ.pushBalance(str(self.auid), 70)
        
        self.response = None
        self.I.BILL.confirmWriteOff( self.auid, 2, callback=self._onBillingResponse )
        self.assert_( self.response and isinstance(self.response, dict) )
        self.assert_( self.response.get("code") == ibilling.ERROR_CODE_OK )
        self.assert_( self.response.get("auid") == self.auid )
        self.assert_( self.response.get("balance") == 70.0 )
        self.assert_( self.response.get("reserveId") == 2 )
        
##----------------------------------------------------------------
##----------------------------------------------------------------

def main():
    ## print "DEFAULT_LOG_LEVEL: %s" % DEFAULT_LOG_LEVEL
    log_level = logging.CRITICAL
    if '--verbose' in sys.argv:
        log_level = DEFAULT_LOG_LEVEL

    logging.basicConfig( level=log_level, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
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
