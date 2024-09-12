import urllib2, urllib
import json
import threading
import cStringIO
import gzip

from logging import debug, error

class Caller:

    class Callback:

        def __init__(self, name, callback):
            self.name = name 
            self.callback = callback

        def __call__(self, **args):
            return self.callback(self.name, args)

    class List:

        def __init__(self, data):
            self.__data = data

        def __str__(self):
            return str(self.__data)

        def __len__(self):
            return len(self.__data)

        def __contains__(self, item):
            return item in self.__data

        def __getitem__(self, index):
            result = self.__data[index]
            if type(result) == dict:
                return Caller.Dict(result)
            if type(result) == list:
                return Caller.List(result)
            return result

    class Dict:

        def __init__(self, data):
            self.__data = data

        def __str__(self):
            return str(self.__data)

        def __nonzero__(self):
            return len(self.__data) > 0
                
        def __contains__(self, item):
            return item in self.__data

        def get(self, key, default=None):
            result = self.__data.get(key, default)
            if result != default:
                return self.__get(result)
            return result

        def __get(self, result):
            if type(result) == dict:
                return Caller.Dict(result)
            if type(result) == list:
                return Caller.List(result)
            return result
            
        def __getattr__(self, name):
            result = self.__data.get(name, None)
            if result != None:
                return self.__get(result)
            raise AttributeError(name)

    def __init__(self, url, action='action', **args):
        self.__url = url
        self.__args = args
        self.__page = None
        self.__action = action

    def _call(self, name, args):
        args[self.__action] = name
        args.update(self.__args)
        request = self.__url+'/'
        if self.__page:
            request += self.__page
        request += '?'+urllib.urlencode(args)
        debug(request)
        urlRequest = urllib2.Request( request, None, headers={"Accept-Encoding":"gzip"} )

        try:
            response = urllib2.urlopen( urlRequest, None, timeout=10.0 )
            headers = response.info()
            responseData = response.read()
            if str(headers).find("Content-Encoding: gzip") >= 0:
                _gzip_value = cStringIO.StringIO( responseData )
                _gzip_file = gzip.GzipFile(mode="rb", fileobj=_gzip_value)
                responseData = _gzip_file.read()

            data = json.loads(responseData)
            debug(json.dumps(data, indent=4))
            return Caller.Dict(data)
        except urllib2.URLError, e:
            error(str(e))
            return Caller.Dict({})        

    def SetPage(self, page):
        self.__page = page

    def SetDefault(self, **args):
        self.__args.update(args)

    def __getattr__(self, name):
        return Caller.Callback(name, self._call)

    def __nonzero__(self):
        return True

class AutoIncrement:

    def __init__(self):
        self.value = 0
    
    def __str__(self):
        result = str(self.value)
        self.value += 1
        return result

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient    
from thrift.protocol import TBinaryProtocol

class ThriftCaller:

    class Callback:

        def __init__(self, name, callback):
            self.name = name 
            self.callback = callback

        def __call__(self, *args, **kargs):
            return self.callback(self.name, args, kargs)

    def __init__(self, url, clientClass):
        transport = THttpClient.THttpClient(url)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = clientClass.Client(protocol)

        self.transport = transport
        self.client = client

    def _call(self, name, args, kargs):
        func = eval("self.client."+name)
        result = None
        logging.debug("%s%s" % (name, args))
        try:
            self.transport.open()
            result = func(*args)
            self.transport.close()
            logging.debug(result)
        except Thrift.TException, tx:
            logging.error(str(tx.message))
        return result    
                        
    def __getattr__(self, name):
        return ThriftCaller.Callback(name, self._call)

if __name__ == '__main__':
    import unittest

    class Test_Caller(unittest.TestCase):

        def test_List(self):
            t  = Caller.List([{'auto' : 1},{'auto' : 2}, {'auto' : 3}])
            self.assertEquals(3, len(t))
            for index, i in enumerate(t):
                self.assertEquals(True, 'auto' in i)
                self.assertEquals(index+1, i.auto)

        def test_Dict(self):
            t  = Caller.Dict({'response' : {'pending_events' : 1}})
            self.assertEquals(1, t.response.pending_events)
            self.assertEquals(None, t.response.get('NotExistingValue'))
    unittest.main()

