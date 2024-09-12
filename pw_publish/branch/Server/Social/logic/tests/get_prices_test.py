import sys
sys.path.append('../')
sys.path.append('../..')
from logic.get_prices import *
from binascii import crc32
from base.helpers import *
from enums import *

sys.path.append('thrift_pw/account_management/gen-py')
sys.path.append('../thrift_pw/account_management/gen-py')
sys.path.append('../../thrift_pw/account_management/gen-py')
from AccountManagementAPI.ttypes import PayServiceType

class get_prices_test:

  def get_prices_test( self, env ):
    modeldata = env.acc.model

    requests =  [ ( Get_prices, GetPricesRequest( modeldata, { "servicetype" : [PayServiceType.PremiumAccount] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList
    result = changeList.get(0)

    assert changeList.get(0)
    assert result.has_key("prices")
    assert result["prices"][0].has_key("price")
    assert result["prices"][0]["price"] > 0
    assert result["prices"][0].has_key("duration")
    assert result["prices"][0]["duration"] > 0
    assert result["prices"][1].has_key("price")
    assert result["prices"][1]["price"] > 0
    assert result["prices"][1].has_key("duration")
    assert result["prices"][1]["duration"] > 0

