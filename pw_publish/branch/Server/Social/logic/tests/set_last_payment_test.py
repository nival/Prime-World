import sys,time
sys.path.append('../')
sys.path.append('../..')
from logic.set_last_payment import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class set_last_payment_test:

  def get_lamp_bonus_1d_test( self, env ):
    modeldata = env.acc.model
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 1
    modeldata.MarketingEventsInfo.LampEventInfo.dbId = ""

    requests = [ ( Set_last_payment, SetLastPaymentRequest( modeldata, { "secs" : ["" + str( 4*60*60*24 ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "/Items/Coupon/GoldLamp_Low.ROLLCONT" )

  def get_lamp_bonus_10y_test( self, env ):
    modeldata = env.acc.model
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 1
    modeldata.MarketingEventsInfo.LampEventInfo.dbId = ""
    env.acc.getConfig().LampEventSettings.FwodLampRollProbability = 100
    modeldata.Statistics.LastLampDropTime = time.time() - 365*86400
    env.acc.getConfig().addLampActiveGroup(1, -1)

    requests = [ ( Set_last_payment, SetLastPaymentRequest( modeldata, { "secs" : ["" + str( 3650*60*60*24 ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "/Items/Coupon/GoldLamp_High.ROLLCONT" )

  def first_win_lamp_test(self,env):
    modeldata = env.acc.model
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 1
    modeldata.MarketingEventsInfo.LampEventInfo.dbId = ""
    env.acc.getConfig().LampEventSettings.FwodLampRollProbability = 0

    requests = [ ( Set_last_payment, SetLastPaymentRequest( modeldata, { "secs" : ["" + str( 60*60*24 ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), True ) == "" )

    modeldata.LordInfo.TodayWinMaps.add( "dsfsdf","asddsf" )
    modeldata.LordInfo.TodayWinMaps.add( "dsdf","sds" )
    modeldata.LordInfo.TodayWinMaps.add( "ds4fsdf","sdfsdf" )
    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), True ) == "" )

  def check_block_lamp_test(self,env):
    modeldata = env.acc.model
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 1
    modeldata.MarketingEventsInfo.LampEventInfo.dbId = ""

    requests = [ ( Set_last_payment, SetLastPaymentRequest( modeldata, { "secs" : ["" + str( 60*60*24 ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    modeldata.Statistics.LastLampDropTime = time.time() - 2*86400

    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "" )
    modeldata.Statistics.LastPaymentTime = time.time() - 5*86400
    modeldata.Statistics.LastLampDropTime = time.time() - 4*86400
    
    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "/Items/Coupon/GoldLamp_Low.ROLLCONT" )

  def check_active_group_test(self,env):
    modeldata = env.acc.model
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 1
    modeldata.MarketingEventsInfo.LampEventInfo.dbId = ""

    requests = [ ( Set_last_payment, SetLastPaymentRequest( modeldata, { "secs" : ["" + str( 4*60*60*24 ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "/Items/Coupon/GoldLamp_Low.ROLLCONT" )

    modeldata.Statistics.LastPaymentTime = time.time() - 15*86400

    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "" )

  def guaranty_period_test(self,env):
    modeldata = env.acc.model
    modeldata.MarketingEventsInfo.LampEventInfo.AllowedLamps = 1
    modeldata.MarketingEventsInfo.LampEventInfo.dbId = ""

    requests = [ ( Set_last_payment, SetLastPaymentRequest( modeldata, { "secs" : ["" + str( 4*60*60*24 ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), False ) == "/Items/Coupon/GoldLamp_Low.ROLLCONT" )

    env.acc.getConfig().LampEventSettings.FwodLampRollProbability = 0
    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), True ) == "" )

    modeldata.Statistics.LastLampDropTime = time.time() - 6*86400
    assert( modeldata.getGoldLampRollContainer( env.acc.SD, env.acc.getConfig(), True ) == "/Items/Coupon/GoldLamp_Low.ROLLCONT" )

