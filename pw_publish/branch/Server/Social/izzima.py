# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, base64, hashlib 
import urllib2, functools

sys.path.append('tornado')

import tornado.ioloop
import tornado.options
from tornado.options import define, options

from base.helpers import *

import base.calculate_crc as calculate_crc
from base.helpers import *

sys.path.append('cfg')
import cfg

WS_MAX_ZZIMA_THREADS = 40

def AsyncZZ():
    return tornado.ioloop.IOLoop.instance().zz

# заглушка, на случай когда "не особо нужен callback"
def main_zzima_callback( reply ):
    info( "- main_zzima_callback: reply %s" % str(reply) )
    pass

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------
class IZZima:
    """ Виртуальный интерфейс для общения с zzima (он же и dummy-заглушка).
        повторяет интерфейс реального общения приложения с thread pool (через очередь запросов), 
        поэтому параметры и return могут быть странного вида.
        Поведение: по умолчанию якобы "фейлим" все запросы.
    """
    def __init__(self, HTTP=None, service_name='pw', payment_system='CBT', **kwargs):
        self.HTTP = HTTP
        self.service_name = service_name
        self.payment_system = payment_system
    
    def authorize(self, zzima_login, zzima_md5, callback=main_zzima_callback, params=None): 
        """ авторизовать юзера;
            ответ: будет вызван callback( reply = { "r":{ 'code':<INT>, 'userId':<INT> } } )
        """
        callback( {"r": {'code':-1, 'userId':-1}, "p":params} )

    def getBalance(self, zzima_login, callback=main_zzima_callback, params=None):
        """ определение баланса юзера;
            ответ: будет вызван callback( reply = { "r":{ 'code':<INT>, 'amount':<INT> } } )
        """
        callback( {"r": {'code':-1, 'amount':0}, "p":params} )


    def getBalanceEx(self, zzima_login, callback=main_zzima_callback, params=None):
        """ определение структуры баланса юзера;
            ответ: будет вызван callback( reply = { "r":{ 'code':<INT>, 'balance': { <payment_system> : <INT> } } } )
        """
        callback( {"r": {'code':-1, 'dbalance':{} }, "p":params} )

    def reserveAmount( self, zzima_login, amount, reason, callback=main_zzima_callback, params=None ):
        """ резервирование на счету;
            ответ: будет вызван callback( reply = { "r":{ 'code':<INT> } } )
        """
        callback( {"r": {'code':-1}, "p":params} )


    def confirmWriteOff( self, zzima_login, reserveId, callback=main_zzima_callback, params=None ):
        """ подтверждение резерва и окончательное списывание со счета;
            ответ: будет вызван callback( reply = { "r":{ 'code':<INT> } } )
        """
        callback( {"r": {'code':-1}, "p":params} )

        
    def writeOff(self, zzima_login, amount, reason, callback=main_zzima_callback, params=None):
        """ списание со счета;
            ответ: будет вызван callback( reply = { "r":{ 'code':<INT> } } )
        """
        callback( {"r": {'code':-1}, "p":params} )
        
    def replenish(self, zzima_login, amount, reason, callback=main_zzima_callback, params=None, payment_system=None):
        """ начисление на счет;
            ответ: будет вызван callback( reply = { "r":{ 'code':<INT>, 'amount':<INT> } } )
        """
        callback( {"r": {'code':-1, 'amount':0}, "p":params} )
        
    def createUser(self, zzima_login, email, password_md5, callback=main_zzima_callback, params=None):
        """ создание нового пользователя;
            ответ: будет вызван callback( reply = { "r":{ 'code':<INT>, 'userId':<INT>} } )
        """
        callback( {"r": {'code':-1, 'userId':-1}, "p":params} )
        
    #~ def getInfo(self, zzima_uid, get_extended_info=0, get_pic=0, callback=main_zzima_callback):
        #~ """ получить данные юзера;
            #~ ответ: будет вызван callback с данными, соответствующими ошибке "нет такого юзера"
        #~ """ 
        #~ reply = {
            #~ "response": {
                #~ "error": {
                    #~ "code": 200, 
                    #~ "message": "Not found user"
                #~ }, 
                #~ "request": {
                    #~ "game_user": str(zzima_uid), 
                    #~ "method": "users.getInfo,%s,0,0" % str(zzima_uid), 
                #~ }, 
                #~ "result": 0
            #~ } 
        #~ }
        #~ json_response = json_dumps(reply)
        #~ http_response = ClassDict( error=0, body=json_response )
        #~ callback( http_response )
        
    # ----------------------------------------------------------------------------------------------------------
    def destroy(self):
        pass

    def fadeout(self, syncWait=0 ):
        pass
        
    def isDone(self):
        return True
        
        
##---------------------------------------------------------------------------------------------
## Интерфейс для общения с реальным ZZima billing через async thread-pool.
class AsyncZZima(IZZima):
    
    def authorize(self, zzima_login, zzima_md5, callback=main_zzima_callback, params=None): 
        """ авторизовать юзера """
        args = {
            'fromServiceName' : self.service_name, 
            'userName' : zzima_login,
            'userPassword' : zzima_md5, # MD5: присылать теперь надо zz_auth = hashlib.md5( zzima_pwd ).hexdigest(), а сюда передается уже base64( md5( pwd ))
            ## 'userPassword' : base64.b64encode( hashlib.md5( zzima_md5 ).digest() ) ## пароль у нас в открытом виде (сначала, значит, делаем md5( pwd )
        }
        args['crc'] = calculate_crc.forAuthorizeUser(args)
        AsyncZZ().addQuery( "AuthorizeUser", args, callback, params )

    def subscribe(self, zzima_login, callback=main_zzima_callback, params=None):
        """ определение баланса юзера """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'serviceName' : self.service_name,
        }
        args['crc'] = calculate_crc.forSubscribeService(args)
        AsyncZZ().addQuery( "SubscribeService", args, callback, params )
        
    def getBalance(self, zzima_login, callback=main_zzima_callback, params=None):
        """ определение баланса юзера """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login
        }
        args['crc'] = calculate_crc.forGetUserBalance(args)
        AsyncZZ().addQuery( "GetUserBalance", args, callback, params )

    def getBalanceEx(self, zzima_login, callback=main_zzima_callback, params=None):
        """ определение баланса юзера """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login
        }
        args['crc'] = calculate_crc.forGetUserBalance(args)
        AsyncZZ().addQuery( "GetUserBalanceEx", args, callback, params )

    def reserveAmount( self, zzima_login, amount, reason, callback=main_zzima_callback, params=None ):
        """ резервация на счету """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'amount' : amount,
            'reason' : reason
        }
        args['crc'] = calculate_crc.forReserveAmount(args)
        AsyncZZ().addQuery( "ReserveAmount", args, callback, params )


    def confirmWriteOff( self, zzima_login, reserveId, callback=main_zzima_callback, params=None ):
        """ подтверждение резервации на счету """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'reserveId' : reserveId,
        }
        args['crc'] = calculate_crc.forConfirmWriteOff(args)
        AsyncZZ().addQuery( "ConfirmWriteOff", args, callback, params )
    
        
    def writeOff(self, zzima_login, amount, reason, callback=main_zzima_callback, params=None):
        """ списание со счета """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'amount' : amount,
            'account' : None,
            'reason' : reason
        }
        args['crc'] = calculate_crc.forAccountWriteOff(args)
        AsyncZZ().addQuery( "AccountWriteOff", args, callback, params )
        
    #~ <s:element minOccurs="0" maxOccurs="1" name="userName" type="s:string"/>
    #~ <s:element minOccurs="1" maxOccurs="1" name="amount" type="s:decimal"/>
    #~ <s:element minOccurs="0" maxOccurs="1" name="account" type="s:string"/>
    #~ <s:element minOccurs="0" maxOccurs="1" name="reason" type="s:string"/>
    #~ <s:element minOccurs="0" maxOccurs="1" name="paymentSystem" type="s:string"/>
    def replenish(self, zzima_login, amount, reason, callback=main_zzima_callback, params=None, payment_system=None):
        """ начисление на счет """
        _payment_system = payment_system or self.payment_system
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'amount' : amount,
            'account' : None,
            'paymentSystem': _payment_system,
            'reason' : reason
        }
        args['crc'] = calculate_crc.forAccountReplenish(args)
        AsyncZZ().addQuery( "AccountReplenish", args, callback, params )
        
    #~ <s:element minOccurs="0" maxOccurs="1" name="srcUserName" type="s:string"/>
    #~ <s:element minOccurs="0" maxOccurs="1" name="srcAccount" type="s:string"/>
    #~ <s:element minOccurs="0" maxOccurs="1" name="dstUserName" type="s:string"/>
    #~ <s:element minOccurs="0" maxOccurs="1" name="dstAccount" type="s:string"/>
    #~ <s:element minOccurs="1" maxOccurs="1" name="amount" type="s:decimal"/>
    #~ <s:element minOccurs="0" maxOccurs="1" name="reason" type="s:string"/>
    def transfer(self, src_zzima_login, dest_zzima_login, amount, reason, callback=main_zzima_callback, params=None):
        """ начисление на счет """
        args = {
            'fromServiceName' : self.service_name,
            'srcUserName' : src_zzima_login,
            'srcAccount' : None,
            'dstUserName' : dest_zzima_login,
            'dstAccount' : None,
            'amount' : amount,
            'reason' : reason
        }
        args['crc'] = calculate_crc.forMoneyTransfer(args)
        AsyncZZ().addQuery( "MoneyTransefer", args, callback, params )

        
    def createUser(self, zzima_login, email, password_md5, callback=main_zzima_callback, params=None):
        """ создание нового пользователя """
        args = {
            'fromServiceName' : self.service_name,
            'userEmail' : email,
            'userName' : zzima_login,
            'userPassword' : password_md5, # сюда передается уже base64( md5( pwd ))
            'userReferal' : None
        }
        args['crc'] = calculate_crc.forRegisterUser(args)
        AsyncZZ().addQuery( "RegisterUser", args, callback, params )
        
    #~ def getInfo(self, zzima_uid, get_extended_info=0, get_pic=0, callback=main_zzima_callback):
        #~ """ получить данные юзера по zz_uid """
        #~ if self.HTTP:
            #~ if cfg.ZZIMA_API_URL:
                #~ body, headers = zzima_api.getInfoParams( cfg.ZZIMA_API_KEY, cfg.ZZIMA_API_SECRET, zzima_uid, get_extended_info, get_pic ) # без дополнительной инфы и картинок
                #~ t0 = time.time()
                #~ zzima_api.invokeTornado( self.HTTP, cfg.ZZIMA_API_URL, body, headers, callback )
            #~ else:
                #~ callback( ClassDict( error=403, body=None ) ) # нет валидного URL
        #~ else:
            #~ callback( ClassDict( error=404, body=None ) ) # нет протокола

    # ----------------------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------------------
    
    def destroy(self):
        AsyncZZ().destroy()
        
    def fadeout(self, syncWait=0 ):
        """ постепенно прикрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool). 
            при syncWait==1 не возвращаем управление, пока полностью не закроемся; syncWait==0 ставит флаг и сразу возвращается (async) """
        AsyncZZ().fadeout( syncWait )

    def isDone(self):
        zz = AsyncZZ()
        if ( not zz.threadsDone() ) or len(zz.replies): # остались бегающие threads или неразобранные ответы
            return False
        return True



##---------------------------------------------------------------------------------------------
## Интерфейс для общения с реальным ZZima billing через обычные http-запросы (с подстановкой параметров в готовые XML-шаблоны).
class HttpZZima(IZZima):
    def __init__(self, HTTP=None, service_name='pw', payment_system='CBT', billing_url=""):
        IZZima.__init__(self, HTTP, service_name, payment_system)
        self.billing_url = billing_url
        self.shutdown = 0
        self.pending_count = 0
        
    HEADERS = { 
        'SOAPAction': u'"http://zzima.com/%s"', 
        'Soapaction': u'"http://zzima.com/%s"',
        'Content-Type': 'text/xml; charset=utf-8', 
        'Content-type': 'text/xml; charset=utf-8', 
    }
    
    # Ад и содомия
    BODIES = {
        'GetUserBalanceEx': '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:$method><ns0:req><ns0:crc>$crc</ns0:crc><ns0:fromServiceName>$fromServiceName</ns0:fromServiceName><ns0:userName>$userName</ns0:userName></ns0:req></ns0:$method></ns1:Body></SOAP-ENV:Envelope>',
        'GetUserBalance':   '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:$method><ns0:req><ns0:crc>$crc</ns0:crc><ns0:fromServiceName>$fromServiceName</ns0:fromServiceName><ns0:userName>$userName</ns0:userName></ns0:req></ns0:$method></ns1:Body></SOAP-ENV:Envelope>',
        'AccountReplenish': '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:AccountReplenish><ns0:req><ns0:crc>$crc</ns0:crc><ns0:fromServiceName>$fromServiceName</ns0:fromServiceName><ns0:userName>$userName</ns0:userName><ns0:amount>$amount</ns0:amount><ns0:reason>$reason</ns0:reason><ns0:paymentSystem>$paymentSystem</ns0:paymentSystem></ns0:req></ns0:AccountReplenish></ns1:Body></SOAP-ENV:Envelope>',
        'MoneyTransefer':   '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:MoneyTransefer><ns0:req><ns0:crc>$crc</ns0:crc><ns0:fromServiceName>$fromServiceName</ns0:fromServiceName><ns0:srcUserName>$srcUserName</ns0:srcUserName><ns0:dstUserName>$dstUserName</ns0:dstUserName><ns0:amount>$amount</ns0:amount><ns0:reason>$reason</ns0:reason></ns0:req></ns0:MoneyTransefer></ns1:Body></SOAP-ENV:Envelope>',
        'SubscribeService': '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:SubscribeService><ns0:req><ns0:crc>$crc</ns0:crc><ns0:fromServiceName>$fromServiceName</ns0:fromServiceName><ns0:userName>$userName</ns0:userName><ns0:serviceName>$serviceName</ns0:serviceName></ns0:req></ns0:SubscribeService></ns1:Body></SOAP-ENV:Envelope>',
        'AccountWriteOff':  '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:AccountWriteOff><ns0:req><ns0:crc>$crc</ns0:crc><ns0:fromServiceName>$fromServiceName</ns0:fromServiceName><ns0:userName>$userName</ns0:userName><ns0:amount>$amount</ns0:amount><ns0:reason>$reason</ns0:reason></ns0:req></ns0:AccountWriteOff></ns1:Body></SOAP-ENV:Envelope>',
        'ReserveAmount':    '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:ReserveAmount><ns0:req><ns0:crc>$crc</ns0:crc><ns0:fromServiceName>$fromServiceName</ns0:fromServiceName><ns0:userName>$userName</ns0:userName><ns0:amount>$amount</ns0:amount><ns0:reason>$reason</ns0:reason></ns0:req></ns0:ReserveAmount></ns1:Body></SOAP-ENV:Envelope>',
        'ConfirmWriteOff':  '<?xml version="1.0" encoding="UTF-8"?><SOAP-ENV:Envelope xmlns:ns0="http://zzima.com/" xmlns:ns1="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/"><SOAP-ENV:Header/><ns1:Body><ns0:ConfirmWriteOff><ns0:req><ns0:crc>$crc</ns0:crc><ns0:fromServiceName>$fromServiceName</ns0:fromServiceName><ns0:userName>$userName</ns0:userName><ns0:reserveId>$reserveId</ns0:reserveId></ns0:req></ns0:ConfirmWriteOff></ns1:Body></SOAP-ENV:Envelope>',
    }

    # ----------------------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------------------

    @staticmethod
    def _cutTag(tag, response):
        cut = None
        open_tag = "<%s>" % tag
        close_tag = "</%s>" % tag
        pos1 = response.find(open_tag)
        pos2 = response.find(close_tag)
        if pos1 >= 0 and pos2 >= pos1:
            return response[ pos1+len(open_tag) : pos2 ], pos2+len(close_tag)
        return cut, -1
    
    @staticmethod
    def cutTag(tag, response):
        tag, pos = HttpZZima._cutTag(tag, response)
        return tag

    @staticmethod
    def parseBalanceArrayTag(response):
        tag, pos = HttpZZima._cutTag('detailedBalance', response)
        if tag is not None:
            data = {}
            while tag:
                item, pos = HttpZZima._cutTag('OperationWriteOff', tag) 
                if pos >= 0: 
                    tag = tag[pos:]
                else:
                    break
                ps = HttpZZima.cutTag('paymentSystemId', item)
                amount = HttpZZima.cutTag('amount', item)
                if ps is not None:
                    data[ps] = tofloat(amount)
            return data
        return None
        
    def fillTemplate(self, method, args):
        headers = self.HEADERS.copy()
        headers['SOAPAction'] = headers['SOAPAction'] % method
        headers['Soapaction'] = headers['Soapaction'] % method

        body = self.BODIES.get( method, "" )
        body = body.replace( "$method", method )
        for name, value in args.iteritems():
            ## info("replacing arg %r:%r" % (name, value))
            body = body.replace( "$%s" % name, str(value) )
            
        ## info("url: %r" % self.billing_url)
        ## info("headers: %r" % headers)
        ## info("body: %r" % body)
        
        return headers, body

    def fetchTemplate(self, method, args, callback):
        if not self.shutdown:
            headers, body = self.fillTemplate( method, args )            
            request = tornado.httpclient.HTTPRequest( url=self.billing_url, method="POST", body=body, headers=headers )
            
            self.pending_count += 1 
            info("ZZ.pending_count=%s" % self.pending_count)
            _callback = functools.partial( self.onBillingReply, method=method, callback=callback )
            try:
                self.HTTP.fetch( request, _callback )
            except:
                catch()
                self.fail( callback )
        else:
            self.fail( callback )
            
    # ----------------------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------------------
    
    def getBalance(self, zzima_login, callback=main_zzima_callback, params=None):
        """ определение баланса юзера """
        args = ClassDict( {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login
        } )
        args['crc'] = calculate_crc.forGetUserBalance(args)
        method = 'GetUserBalance'
        self.fetchTemplate( method, args, callback )

    def getBalanceEx(self, zzima_login, callback=main_zzima_callback, params=None):
        """ определение баланса юзера """
        args = ClassDict( {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login
        } )
        args['crc'] = calculate_crc.forGetUserBalance(args)
        method = 'GetUserBalanceEx'
        self.fetchTemplate( method, args, callback )
        
    def replenish(self, zzima_login, amount, reason, callback=main_zzima_callback, params=None, payment_system=None):
        """ начисление на счет """
        _payment_system = payment_system or self.payment_system
        args = ClassDict( {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'amount' : amount,
            'account' : None,
            'paymentSystem': _payment_system, # берем либо указанную ps либо из настроек
            'reason' : reason
        } )
        args['crc'] = calculate_crc.forAccountReplenish(args)
        method = 'AccountReplenish'
        self.fetchTemplate(method, args, callback)
        
    def subscribe(self, zzima_login, callback=main_zzima_callback, params=None):
        """ подписка юзера на сервис """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'serviceName' : self.service_name,
        }
        args['crc'] = calculate_crc.forSubscribeService(args)
        method = 'SubscribeService'
        self.fetchTemplate(method, args, callback)

        
    def reserveAmount( self, zzima_login, amount, reason, callback=main_zzima_callback, params=None ):
        """ резервация на счету """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'amount' : amount,
            'reason' : reason
        }
        args['crc'] = calculate_crc.forReserveAmount(args)
        method = 'ReserveAmount'
        self.fetchTemplate(method, args, callback)


    def confirmWriteOff( self, zzima_login, reserveId, callback=main_zzima_callback, params=None ):
        """ подтверждение резервации на счету """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'reserveId' : reserveId,
        }
        args['crc'] = calculate_crc.forConfirmWriteOff(args)
        method = 'ConfirmWriteOff'
        self.fetchTemplate(method, args, callback)


    def writeOff(self, zzima_login, amount, reason, callback=main_zzima_callback, params=None):
        """ списание со счета """
        args = {
            'fromServiceName' : self.service_name,
            'userName' : zzima_login,
            'amount' : amount,
            'account' : None,
            'reason' : reason
        }
        args['crc'] = calculate_crc.forAccountWriteOff(args)
        method = 'AccountWriteOff'
        self.fetchTemplate(method, args, callback)
        
    def transfer(self, src_zzima_login, dest_zzima_login, amount, reason, callback=main_zzima_callback, params=None):
        """ перевод со счета на счет """
        args = {
            'fromServiceName' : self.service_name,
            'srcUserName' : src_zzima_login,
            'srcAccount' : None,
            'dstUserName' : dest_zzima_login,
            'dstAccount' : None,
            'amount' : amount,
            'reason' : reason
        }
        args['crc'] = calculate_crc.forMoneyTransfer(args)
        method = 'MoneyTransefer'
        self.fetchTemplate(method, args, callback)
        
    # ----------------------------------------------------------------------------------------------------------
    def authorize(self, zzima_login, zzima_md5, callback=main_zzima_callback, params=None): 
        raise Exception("zzima.authorize: method not supported by HttpZZima")

    def createUser(self, zzima_login, email, password_md5, callback=main_zzima_callback, params=None):
        raise Exception("zzima.createUser: method not supported by HttpZZima")
    # ----------------------------------------------------------------------------------------------------------
    
    def onBillingReply(self, http_reply, method="", callback=None):
        self.pending_count -= 1 

        ## info( "onBillingReply(%s) ZZ.pending_count=%s, http_reply: %r" % (method, self.pending_count, http_reply) )
        info( "onBillingReply(%s) ZZ.pending_count=%s" % (method, self.pending_count) )
        if http_reply and (not http_reply.error):           
            reply = http_reply.body
            
            result_dict = {}
            res_string = self.cutTag("%sResult" % method, reply) or ""
                          
            code = toint( self.cutTag("code", res_string))
            message = self.cutTag("message", res_string)
            error = toint( self.cutTag("error", res_string))
            amount = tofloat( self.cutTag("amount", res_string))
            reserveId = toint( self.cutTag("reserveId", res_string))
            dbalance = self.parseBalanceArrayTag(res_string)
            
            result_dict = dict( code=code, message=message, error=error, amount=amount, reserveId=reserveId )
            if dbalance is not None:
                result_dict['dbalance'] = dbalance
            info( "onBillingReply(%s) result_dict: %r" % (method, result_dict) )
            
            if callback:
                callback( {"r": result_dict} )
        else:
            info( "bad onBillingReply(%s) http_reply: %r" % (method, http_reply) )
            self.fail( callback )
        
    def fail(self, callback):
        if callback:
            callback( {"r": {'code':-1, 'userId':-1}} )
    
    # ----------------------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------------------
    
    def fadeout(self, syncWait=0 ):
        self.shutdown = 1
        if syncWait > 0:
            while (not self.isDone()) and (syncWait > 0):
                time.sleep(0.01)
                syncWait -= 0.01

    def isDone(self):
        if self.pending_count:
            return False
        return True
