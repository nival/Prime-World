import sys
sys.path.append('../')
sys.path.append('../..')
sys.path.append('../logic')
sys.path.append('../../base')
from logic.buy_custom_flag import *
from base.helpers import *
from enums import *

class buy_custom_flag_test:

    def buy_custom_flag_test( self, env ):
        modeldata = env.acc.model
        customFlag = env.acc.getConfig().getCustomFlagById("rak")

        modeldata.Resources.Gold = 100500
        oldGold = 100500

        requests = [(Buy_custom_flag, BuyCustomFlagRequest(modeldata, {"flagId": ["rak"], "master_auid": [0], "guardParty"
                                                                                                                         "": [False]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.FlagInfo.FlagType == FlagType.Special
        assert len(modeldata.Flags) == 1
        assert modeldata.Resources.Gold == oldGold - customFlag.Price
