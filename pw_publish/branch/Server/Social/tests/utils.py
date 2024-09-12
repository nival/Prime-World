import urllib2
from logging import info

class Response:

    def __init__(self, body, error=None):
        self.body = body
        self.error = error

class RealHttp:

    def __init__(self):
        self.requests = {}

    def fetch(self, request, callback):
        if type(request) == str:
            url = request
            data = None
            headers = {}
        else:
            url = request.url
            data = request.body
            headers = request.headers
        info('url: %r' % url)
        if headers:
            info('headers: %r' % headers)
        if data:
            info('body: %r' % data)
        urlRequest = urllib2.Request( url, data, headers )
        try:
            response = urllib2.urlopen( urlRequest, None, timeout=20.0 )
            headers = response.info()
            responseData = response.read()
            info('response: %r' % responseData)
            callback(Response(responseData))
            return 
        except urllib2.URLError, e:
            print 'Error:',str(e)
            callback(Response(None, e))

class DummyHttp:

    def __init__(self):
        self.requests = {}

    def fetch(self, request, callback):
        if type(request) == str:
            body = None
            url = request
        else:
            body = request.body
            url = request.url
        self.requests[url] = (body, callback)

    def push(self, url, result, error=None):
        data, callback = self.requests[url]
        class Response:
            def __init__(self, body, error):
                self.body = body
                self.error = error
        del self.requests[url] 
        callback(Response(result, error))

    def clear(self):
        self.requests.clear()
