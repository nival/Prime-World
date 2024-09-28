import sys
sys.path.append('../')
sys.path.append('../..')
from logic.give_muid_dlc import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class give_muid_dlc_test:

  def give_muid_dlc_test( self, env ):
    modeldata = env.acc.modeldata
    requests =  [ ( Give_muid_dlc, GiveMuidDLCRequest( modeldata, { "muid" : "testmuid" }, False ) ) ]
    changeList = env.execActions( requests )
    pass