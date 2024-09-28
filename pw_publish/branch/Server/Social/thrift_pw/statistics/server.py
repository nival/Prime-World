import sys
import datetime

sys.path.append('../..')
import tornado.ioloop
import tornado.web
import tornado.httpserver

sys.path.append('gen-py')
from StatisticCore import StatisticService
from StatisticCore.ttypes import *

class StatisticCoreHandler:
    def LoginUsers(self, logins):
        print "================= Logged In " + str(datetime.datetime.now()) + " ================="
        print logins

    def LogoutUsers(self, logins):
        print "================= Logged Out " + str(datetime.datetime.now()) + " ================="
        print logins

class DummyHandler(tornado.web.RequestHandler):
    def __init__(self, *args, **kwargs):
        self.statistic_core_handler = kwargs.pop('statistic_core_handler', None)
        super(DummyHandler, self).__init__(*args, **kwargs)

    def get(self):
        self.write("Use Thrift, Luke!")
    def post(self):
        processor = StatisticService.Processor(self.statistic_core_handler)
        itrans = TTransport.TMemoryBuffer(self.request.body)
        otrans = TTransport.TMemoryBuffer()
        ifactory = TBinaryProtocol.TBinaryProtocolFactory()
        iprot = ifactory.getProtocol(itrans)
        oprot = ifactory.getProtocol(otrans)
        processor.process(iprot, oprot)
        self.response = otrans.getvalue()
        self.write(self.response)
        self.finish()


if __name__ == "__main__":
    statistic_core_handler = StatisticCoreHandler()

    application = tornado.web.Application([
        (r"/", DummyHandler, {'statistic_core_handler': statistic_core_handler}),
    ])
    
    try:
        port_param = [a for a in sys.argv if a.startswith("--port")][0]
        port = int(port_param.split("=")[1])
    except IndexError:
        port = 8888
    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(port)
    tornado.ioloop.IOLoop.instance().start()
