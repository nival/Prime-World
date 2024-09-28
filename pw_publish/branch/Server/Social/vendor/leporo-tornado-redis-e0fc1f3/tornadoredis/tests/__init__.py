import unittest

from server_commands import ServerCommandsTestCase
from pubsub import PubSubTestCase
from pipeline import PipelineTestCase
from scripting import ScriptingTestCase
from reconnect import DisconnectTestCase  # ReconnectTestCase


def all_tests():
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(ServerCommandsTestCase,
                                     PubSubTestCase,
                                     PipelineTestCase,
                                     ScriptingTestCase,
                                     DisconnectTestCase,
                                     # ReconnectTestCase,
                                     ))
    return suite
