# -*- coding: utf-8 -*-

import base64, sys
from hashlib import md5

import cfg

SERVICE_PASSWORD = cfg.ZZIMA_SERVICE_PASSWORD
svcPassword = md5(SERVICE_PASSWORD).digest()

def normalize(params):
    new_params = {}
    for k, v in params.items():
        if not isinstance(v, str):
            if v is not None:
                v = str(v)
            else:
                v = ''
        new_params[k] = v
    return new_params

def forAuthorizeUser(params):
    params = normilize(params)
    return base64.b64encode( md5( params.get('fromServiceName','') + params.get('userName','') + svcPassword).digest() )
    
def forGetUserBalance(params):
    params = normalize(params)
    return base64.b64encode( md5( params.get('fromServiceName','') + params.get('userName','') + svcPassword).digest() )

def forRegisterUser(params):
    params = normalize(params)
    return base64.b64encode( md5( params.get('fromServiceName','') + svcPassword).digest() )

def forReserveAmount(params):
    params = normalize(params)
    params['amount'] = float(params['amount'])
    return base64.b64encode( md5( params.get('fromServiceName','') + params.get('userName','') +  '%.2f' % params.get('amount','') + \
                                  params.get('reason','') + svcPassword).digest() )

def forConfirmWriteOff(params):
    params = normalize(params)
    return base64.b64encode( md5( params.get('fromServiceName','') + params.get('userName','') + params.get('reserveId','') + svcPassword).digest() )

def forAccountWriteOff(params):
    params = normalize(params)
    params['amount'] = float(params['amount'])
    return base64.b64encode( md5( params.get('fromServiceName','') + params.get('userName','') +  '%.2f' % params.get('amount','') + \
     params.get('account','') +  params.get('reason','') + svcPassword).digest() )
     
def forAccountReplenish(params):
    params = normalize(params)
    params['amount'] = float(params['amount'])
    return base64.b64encode( md5( params.get('fromServiceName','') + params.get('userName','') +  '%.2f' % params.get('amount','') + \
     params.get('account','') + params.get('paymentSystem','') + params.get('reason','') + svcPassword).digest() )

def forMoneyTransfer(params):
    params = normalize(params)
    params['amount'] = float(params['amount'])
    return base64.b64encode( md5( params.get('fromServiceName','') + params.get('srcUserName','') + params.get('srcAccount','') + \
        params.get('dstUserName','') + params.get('dstAccount','') + '%.2f' % params.get('amount','') + params.get('reason','') + svcPassword).digest() )

def forSubscribeService(params):
    params = normalize(params)
    return base64.b64encode( md5( params.get('fromServiceName','') + params.get('userName','') + params.get('serviceName','') + svcPassword).digest() )
