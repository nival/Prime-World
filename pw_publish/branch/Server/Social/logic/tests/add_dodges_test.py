import sys
sys.path.append('../')
sys.path.append('../..')
from logic.add_dodges import *
from binascii import crc32
from base.helpers import *
from enums import *

class add_dodges_test:

  def add_dodges_test( self, env ):
    modeldata = env.acc.model
    assert modeldata.LordInfo.GuardInfo.Dodges == 0
    requests =  [ ( Add_dodges, AddDodgesRequest( modeldata, { "dodges" : ["3"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.GuardInfo.Dodges == 3
    assert modeldata.LordInfo.GuardInfo.RetiredTime > 0
