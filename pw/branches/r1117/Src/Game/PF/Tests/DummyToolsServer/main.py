import tornado.ioloop
import tornado.web
import sys
import time

sys.path.append('gen-py')

delay = 3

class DummyHandler(tornado.web.RequestHandler):

    def __init__(self, *args, **kwargs):
        self.processor = kwargs.pop('processor', None)
        self.types = kwargs.pop('types', None)
        super(DummyHandler, self).__init__(*args, **kwargs)

    def get(self):
        self.write("Use Thrift, Luke!")

    def post(self):
        itrans = self.types.TTransport.TMemoryBuffer(self.request.body)
        otrans = self.types.TTransport.TMemoryBuffer()
        ifactory = self.types.TBinaryProtocol.TBinaryProtocolFactory()
        iprot = ifactory.getProtocol(itrans)
        oprot = ifactory.getProtocol(otrans)
        self.processor.process(iprot, oprot)
        self.response = otrans.getvalue()
        self.write(self.response)
        self.finish()

import Account
import Cluster
import Monitor

if __name__ == "__main__":
    
    application = tornado.web.Application([
        (r"/Account", DummyHandler, Account.GetParams()),
        (r"/Cluster", DummyHandler, Cluster.GetParams()),
        (r"/Monitoring", DummyHandler, Monitor.GetParams()),
    ])

    try:
        port_param = [a for a in sys.argv if a.startswith("--port")][0]
        port = int(port_param.split("=")[1])
    except IndexError:
        port = 8888
    
    try:
        delay_param = [a for a in sys.argv if a.startswith("--delay")][0]
        delay = int(delay_param.split("=")[1])
    except IndexError:
        delay = 3

    print 'Starting on port %d' % port
    application.listen(port)
    tornado.ioloop.IOLoop.instance().start()
