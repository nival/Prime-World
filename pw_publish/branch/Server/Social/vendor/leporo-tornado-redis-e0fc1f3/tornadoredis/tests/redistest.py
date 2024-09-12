#!/usr/bin/env python
import time

from tornado.testing import AsyncTestCase

import tornadoredis


def get_callable(obj):
    return hasattr(obj, '__call__')


def async_test_ex(timeout=5):
    def _inner(func):
        def _runner(self, *args, **kwargs):
            try:
                func(self, *args, **kwargs)
            except:
                self.stop()
                raise
            return self.wait(timeout=timeout)
        return _runner
    return _inner


def async_test(func):
    _inner = async_test_ex()
    return _inner(func)


class RedisTestCase(AsyncTestCase):
    test_db = 9
    test_port = 6379

    def setUp(self):
        super(RedisTestCase, self).setUp()
        self.client = self._new_client()
        self.client.flushdb()

    def tearDown(self):
        try:
            self.client.connection.disconnect()
            del self.client
        except AttributeError:
            pass
        super(RedisTestCase, self).tearDown()

    def _new_client(self):
        client = tornadoredis.Client(io_loop=self.io_loop, port=self.test_port)
        # client.connection.connect()
        client.select(self.test_db)
        return client

    def delayed(self, timeout, cb):
        self.io_loop.add_timeout(time.time() + timeout, cb)


class ClientTestCase(RedisTestCase):
    def test_new_client(self):
        # Test non=wrapped calls to clien's functions
        self.client
