class MockRequest:

    def __init__(self):
        self.result = None
        self.isDone = False

    def Finish(self, result={'ec' : 0}):
        assert self.isDone == False
        self.result = result
        self.result['ec'] = 0
        self.isDone = True

    def Fail(self, ec, message=None):
        self.result = {
            'ec' : ec
        }
        if message:
            self.result['message'] = message
        self.isDone = True

    def Reset(self):
        self.result = None
        self.isDone = False

class MockHttpClient:

    def __init__(self):
        self.requests = []

    def fetch(self, request, callback, data=None, accept_json=True):
        assert False == accept_json
        class Request:

            def __init__(self, request, callback):
                self.request = request
                self.callback = callback
                self.body = None
                self.error = None
                assert callback

            def Set(self, body, error=None):
                self.body = body
                self.error = error

            def Execute(self):
                self.callback(self.body, self.error)

        self.requests.append( Request(request, callback))

    def Clear(self):
        self.requests = []

    def Execute(self):
        for request in self.requests:
            request.Execute()
        self.Clear()

class MockQueue:

    def __init__(self):
        self.requests = []
    
    def Push(self, url):
        self.requests.append(url)

    def Reset(self):
        self.requests = []

class Dict:

    def __init__(self, **args):
        for name, value in args.items():
            self.__dict__[name] = value

