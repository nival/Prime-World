import sys
sys.path.append('../')
from logic.expansion import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class expansion_test:
  def expansion_test( self, env ):
    modeldata = env.acc.model
    assert modeldata.LordInfo.LevelOfExpansion == 0

    requests =  [ ( Expansion, ExpansionRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.LevelOfExpansion == 1