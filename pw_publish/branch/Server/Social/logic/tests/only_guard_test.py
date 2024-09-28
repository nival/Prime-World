import sys
sys.path.append('../')
sys.path.append('../..')
from logic.only_guard import *
from binascii import crc32
from base.helpers import *
from enums import *

class only_guard_test:

  def only_guard_test( self, env ):
    modeldata = env.acc.model
    requests =  [ ( Only_guard, OnlyGuardRequest( modeldata, { "only_guard" : ["True"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.GuardInfo.OnlyGuard == True
