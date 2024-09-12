import sys
sys.path.append('../')
from logic.change_pa_end import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class change_pa_end_test:

  def change_pa_end_test( self, env ):
    modeldata = env.acc.model
    
    modeldata.LordInfo.PremiumAccountEnd = 0

    requests =  [ ( Change_pa_end, ChangePAEndRequest( modeldata, { "secs" : [100500] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert modeldata.LordInfo.PremiumAccountEnd == 100500