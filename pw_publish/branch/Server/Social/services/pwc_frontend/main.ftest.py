import sys

sys.path.append('../common/py')
import System.logs

import time
import urllib
import threading
from logging import debug, info

class Config:
    connection_timeout = 10
    timeout = 0.1
    use_poll = False
    ssl_path = '../../tests/ssl_ca'
    async = False
    handshake_threads_count = 16
    minimal_handshake_thread_livetime = 10.0
    handshake_check_period = 1.0

def callback(response):
    if response and not response.error:
        print response.body, response.tm
    else:
        print 'request error !!!', response.tm

class Callback:
    def __init__(self):
        self.isCalled = False

    def __call__(self, response):
        if response and not response.error:
            print response.body, response.tm
        else:       
            print 'request error !!!', response.tm
        self.isCalled = True

import main
import Network.HttpClient

def _main():
    c = Network.HttpClient.AsyncHttpsClient(Config)
    args = dict(
        action='pwc_register',
        email='e_e_i8@mail.ru',
        pwd=main.md5('sunset'),
        gender=2,
        birthdate=int(time.time()),
    )

    args['sign'] = main.Sign(args, 'sunset')
    pwc_url = 'https://pw.nivalnetwork.com:888/pwc'
    url = pwc_url + "?" + urllib.urlencode(args)
    #url = 'http://pw.nivalnetwork.com:88/'

    class Params:

        def __init__(self, rps=1):
            self.Set(rps)

        def Set(self, rps):
            self.rps = rps
            self.request_delta = 1.0/rps

    params = Params()

    def VariableLoad(params, timeFromStart):
        if timeFromStart > 300.0:
            return False
        if timeFromStart > 10.0:
            params.Set(10)
        if timeFromStart > 30.0:
            params.Set(20)
        if timeFromStart > 40.0:
            params.Set(1)
        if timeFromStart > 60.0:
            params.Set(40)
        if timeFromStart > 80.0:
            params.Set(10)
        return True

    def HighLoad(params, timeFromStart):
        if timeFromStart > 300.0:
            return False
        params.Set(40)
        return True

    func = None#VariableLoad
    stime = 0
    ttime = time.time()
    try:
        while True:
            timeFromStart = time.time()-ttime
            if func:
                if not func(params, timeFromStart):
                    break
                
            ctime = time.time()
            if ctime-stime >= params.request_delta:
                c.fetch(url, callback)                                                                          
                stime = ctime
            time.sleep(params.request_delta/2)
    except KeyboardInterrupt, details:
        print details
    del c

def LoadTestPWC():
    _main()
    while threading.active_count() > 1:
        time.sleep(0.1)

import urllib, urllib2

def TestSimplePWCF():
    request = 'http://localhost:10004/oauth'

    args = []
    data = None

    request += '?'+urllib.urlencode(args)
    if not data:
        debug(request)
    else:
        debug(request+' (post_data_size=%d)' % len(data))

    urlRequest = urllib2.Request( request, data )
    response = urllib2.urlopen( urlRequest, None, timeout=10.0 )
    headers = response.info()
    responseData = response.read()
    print responseData

def TestRegister():
    c = Network.HttpClient.AsyncHttpsClient(Config)
    args = dict(
        action='pwc_register',
        email='test13@mail.ru',
        pwd=main.md5('sunset'),
        gender=2,
        birthdate=int(time.time()),
    )
#    args['sign'] = main.Sign(args, 'sunset')
    pwc_url = 'https://pw.nivalnetwork.com:8881/pwc'
    url = pwc_url + "?" + urllib.urlencode(args)
    debug(url)
    callback = Callback()
    c.fetch(url, callback)                                                                          
    while not callback.isCalled:
        time.sleep(0.25)

def TestJsonRegistration():
    request = 'http://localhost:10004/jsonp_register'

    args = {
        'reg_email__': 'd39200@playpw.com',
        'reg_passwd__' : '25d55ad283aa400af464c76d713c07ad',
        'sex' : 1,
        'birth_date' : 318200400,
        'locale' : 'tr',
#        'muid' : 'bzv',
        'callback':'jQuery191049254400620454275_1372314975194&_=1372314975195',
    }   

    request += '?'+urllib.urlencode(args)
    print request
    debug(request)

    urlRequest = urllib2.Request( request )
    response = urllib2.urlopen( urlRequest, None, timeout=10.0 )
    headers = response.info()
    responseData = response.read()
    print responseData

if __name__ == '__main__':
    System.logs.setup('ftest.log', 'debug')
   # TestSimplePWCF()    
#    TestRegister()
    TestJsonRegistration()