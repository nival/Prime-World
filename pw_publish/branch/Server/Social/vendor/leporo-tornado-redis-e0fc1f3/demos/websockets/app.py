# Demo application for brukva
# In order to use:
#  1. $ python app.py
#  2. Open in your browser that supports websockets: http://localhost:8888/
#     You should see text that says "Connected..."
#  3. $ curl http://localhost:8888/msg -d 'message=Hello!'
#     You should see 'Hello!' in your browser

import tornado.httpserver
import tornado.web
import tornado.websocket
import tornado.ioloop
import tornado.gen

import tornadoredis


c = tornadoredis.Client()
c.connect()


class MainHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("template.html", title="Websocket test")


class NewMessage(tornado.web.RequestHandler):
    def post(self):
        message = self.get_argument('message')
        c.publish('test_channel', message)
        self.set_header('Content-Type', 'text/plain')
        self.write('sent: %s' % (message,))


class MessagesCatcher(tornado.websocket.WebSocketHandler):
    def __init__(self, *args, **kwargs):
        super(MessagesCatcher, self).__init__(*args, **kwargs)
        self.listen()
    
    @tornado.gen.engine
    def listen(self):
        self.client = tornadoredis.Client()
        self.client.connect()
        yield tornado.gen.Task(self.client.subscribe, 'test_channel')
        self.client.listen(self.on_message)

    def on_message(self, msg):
        if msg.kind == 'message':
            self.write_message(str(msg.body))

    def close(self):
        print 'closed'
        self.client.unsubscribe('test_channel')
        self.client.disconnect()


application = tornado.web.Application([
    (r'/', MainHandler),
    (r'/msg', NewMessage),
    (r'/track', MessagesCatcher),
])

if __name__ == '__main__':
    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
