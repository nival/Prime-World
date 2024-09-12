import sys
sys.path.append('../')
sys.path.append('../..')
from logic.srv_debug import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class srv_debug_test:

    def srv_debug_test( self, env ):
        model_data = env.acc.model
        requests = [(Srv_debug, SrvDebugRequest(model_data, {'command': ['ping']}, False))]
        env.execActions(requests)
