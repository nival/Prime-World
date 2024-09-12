import sys
sys.path.append('../')
sys.path.append('../..')
from logic.set_lamp_last_roll import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class set_lamp_last_roll_test:

  def set_lamp_last_roll_test(self,env):
    modeldata = env.acc.model
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 1
    modeldata.MarketingEventsInfo.LampEventInfo.dbId = ""
    modeldata.Statistics.LastPaymentTime = time.time() - 60*60*24

    requests = [ ( Set_lamp_last_roll, SetLampLastDropTimeRequest( modeldata, { "secs" : ["" + str( 2*86400 ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "" )
    modeldata.Statistics.LastPaymentTime = time.time() - 6*86400
    requests = [ ( Set_lamp_last_roll, SetLampLastDropTimeRequest( modeldata, { "secs" : ["" + str( 4*86400 ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "/Items/Coupon/GoldLamp_Low.ROLLCONT" )