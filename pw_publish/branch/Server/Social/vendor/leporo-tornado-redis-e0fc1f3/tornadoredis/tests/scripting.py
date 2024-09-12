import hashlib
import logging
from tornado import gen

from redistest import RedisTestCase, async_test


class ScriptingTestCase(RedisTestCase):

    @async_test
    @gen.engine
    def test_eval(self):
        script = 'return 2'
        script_digest = hashlib.sha1(script).hexdigest()

        results = yield gen.Task(self.client.eval, script)
        self.assertEqual(2, results)

        # test evalsha
        results = yield gen.Task(self.client.evalsha, script_digest)
        self.assertEqual(2, results)

        self.stop()
