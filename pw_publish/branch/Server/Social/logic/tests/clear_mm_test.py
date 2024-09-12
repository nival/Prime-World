import sys
sys.path.append('../')
from logic.clear_mm import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class clear_mm_test:

  def clear_mm_test( self, env ):
    env.acc.data.mm = {"koto":"pes"}
    
    requests = [ ( Clear_mm, ClearMmRequest( env.acc.model, { }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert env.acc.data.mm == None