import sys
sys.path.append('../')
from logic.reset_counters import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class reset_counters_test:
  def reset_counters_test( self, env ):
    modeldata = env.acc.model
    modeldata.MarketingEventsInfo.IsBuyHeroComplete = True

    env.acc.db.fractionChanged = 10
    env.acc.db.nickChanged = 10
    requests =  [ ( Reset_counters, ResetCountersRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )

    assert env.acc.db.fractionChanged == 0
    assert env.acc.db.nickChanged == 0
    assert modeldata.MarketingEventsInfo.IsBuyHeroComplete == False
