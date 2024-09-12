import socket

from tornado import gen
from tornado.netutil import TCPServer

from tornado.testing import AsyncTestCase

import tornadoredis
from tornadoredis.exceptions import ConnectionError


class DisconnectingRedisServer(TCPServer):
    @gen.engine
    def handle_stream(self, stream, address):
        n_args = yield gen.Task(stream.read_until, '\r\n')
        while n_args and n_args[0] == '*':
            yield gen.Task(stream.read_until, '\r\n')
            command = yield gen.Task(stream.read_until, '\r\n')
            arg_num = int(n_args.strip()[1:]) - 1
            if arg_num > 0:
                for __ in xrange(0, arg_num):
                    # read the $N line
                    yield gen.Task(stream.read_until, '\r\n')
                    # read the argument line
                    yield gen.Task(stream.read_until, '\r\n')
            stream.write('+OK\r\n')
            if command.strip() == 'DISCONNECT':
                try:
                    stream.socket.shutdown(socket.SHUT_RDWR)
                    stream.close()
                except socket.error:
                    pass
                break
            n_args = yield gen.Task(stream.read_until, '\r\n')


# RedisTestCase
class DisconnectTestCase(AsyncTestCase):
    test_db = 9
    test_port = 6380

    def setUp(self):
        #self._server_io_loop = IOLoop()
        # self._server_io_loop
        super(DisconnectTestCase, self).setUp()
        self._server = DisconnectingRedisServer(io_loop=self.io_loop)
        self._server.listen(self.test_port)
        self.client = self._new_client()
        self.client.flushdb()

    def _new_client(self):
        client = tornadoredis.Client(io_loop=self.io_loop, port=self.test_port)
        client.connection.connect()
        client.select(self.test_db)
        return client

    def tearDown(self):
        try:
            self.client.connection.disconnect()
            del self.client
        except AttributeError:
            pass
        self._server.stop()
        super(DisconnectTestCase, self).tearDown()

    def test_disconnect(self):
        def _disconnect_and_send_a_command():
            self.client.execute_command('DISCONNECT', callback=self.stop)
            self.wait()
            self.client.set('foo', 'bar', callback=self.stop)
            self.wait()
        self.assertRaises(ConnectionError, _disconnect_and_send_a_command)

    def test_bpop(self):
        def _disconnect_and_send_a_command():
            self.client.execute_command('DISCONNECT', callback=self.stop)
            self.wait()
            self.client.blpop('foo', callback=self.stop)
            self.wait()
        self.assertRaises(ConnectionError, _disconnect_and_send_a_command)


#class ReconnectTestCase(RedisTestCase):
#    @async_test
#    @gen.engine
#    def test_redis_timeout(self):
#        res = yield gen.Task(self.client.setex, 'foo', 1, 'bar')
#        self.assertEqual(res, True)
#
#        @gen.engine
#        def _get_delayed():
#            res = yield gen.Task(self.client.get, 'foo')
#            self.assertFalse(res)
#            self.stop()
#        self.delayed(2, _get_delayed)
#
#    @async_test
#    @gen.engine
#    def test_redis_timeout_with_pipe(self):
#        res = yield gen.Task(self.client.set, 'foo', 'bar')
#        self.assertEqual(res, True)
#        pipe = self.client.pipeline(transactional=True)
#        pipe.get('foo')
#        res = yield gen.Task(pipe.execute)
#        self.assertEqual(res, ['bar'])
#        self.stop()
