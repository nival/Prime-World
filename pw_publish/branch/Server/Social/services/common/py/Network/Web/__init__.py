import time
import json 

class Request:

    def __init__(self, request, method=None, pretty=0, useMethod=True):
        self.request = request
        self.method = method
        self.pretty = pretty
        self.startTime = time.time()
        self.useMethod = useMethod
        self.request.set_header("Content-Type", "text/plain") 
        self.request.set_header("charset", "UTF-8")
        if not method:
            self.useMethod = False
    
    def Fail(self, ec, em=''):
        reply = {
            'ec' : ec,
        }
        if em:
            reply['em'] = em
        if self.pretty:
            text = json.dumps(reply, indent=4)      
        else:
            text = json.dumps(reply)      
        self.request.write(text)
        self.request.finish()

    def Finish(self, result=None):        
        ec = 0
        em = ''
        mresult = {}

        if result != None:
            if type(result) in [dict, list]:
                mresult = result
            elif type(result) == int:
                ec = result
            elif type(result) == tuple:
                if len(result) == 2:
                    ec = result[0]
                    if type(result[1]) == dict:
                        mresult = result[1]
                    else:
                        em = result[1]
                elif len(result) == 3:
                    ec = result[0]
                    em = result[1]
                    mresult = result[2]

        reply = {
            'tm' : int((time.time()-self.startTime)*1000)
        }
        if len(mresult) > 0:
            if self.useMethod:
                reply[self.method] = mresult
                target = reply[self.method]
            else:
                reply.update(mresult)
                target = reply
            if em:
                target['em'] = em
            target['ec'] = ec
        else:
            reply['ec'] = ec
        if self.pretty:
            text = json.dumps(reply, indent=4)      
        else:
            text = json.dumps(reply)      
        self.request.write(text)
        self.request.finish()

class Updater:

    def __init__(self, who, instance, timeout):
        self.who = who
        self.instance = instance
        self.timeout = timeout
        self.__call__()

    def SetTimeout(self, timeout):
        self.timeout = timeout
    def Reset(self):
        self.instance.add_timeout(time.time(), self)

    def __call__(self):
        self.who.Update()
        self.instance.add_timeout(time.time()+self.timeout, self)
