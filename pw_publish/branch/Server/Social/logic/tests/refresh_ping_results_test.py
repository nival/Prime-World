import sys
sys.path.append('../')
sys.path.append('../..')
from logic.refresh_ping_results import *
from binascii import crc32
from base.helpers import *
from enums import *

class refresh_ping_results_test:

  def refresh_ping_results_test( self, env ):
    modeldata = env.acc.model
    
    config = env.I.Config.getConfig( env.acc.userlocale )
    valid_locales = config.PingInfo.addresses.keys()
    l = len(valid_locales)
    locale1_key = valid_locales[random.randint(0, l - 1)]
    locale2_key = valid_locales[random.randint(0, l - 1)]


    assert modeldata.LordInfo.PingResults[locale1_key] == config.PingInfo.MaxTimeOut
    assert modeldata.LordInfo.PingResults[locale2_key] == config.PingInfo.MaxTimeOut
    
    requests = [ ( Refresh_ping_results, RefreshPingResultsRequest( modeldata, { "pingName" : [locale2_key], "pingTime" : [10]}, False ) ) ]
    changeList = env.execActions( requests )    
    
    assert modeldata.LordInfo.PingResults[locale2_key] == 10
    assert locale1_key == locale2_key or modeldata.LordInfo.PingResults[locale1_key] == config.PingInfo.MaxTimeOut