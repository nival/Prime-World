import sys
sys.path.append('../')
sys.path.append('../..')
sys.path.append('../logic')
sys.path.append('../../base')
from logic.change_flag import *
from logic.buy_custom_flag import *
from base.helpers import *
from enums import *

class change_flag_test:

    def buy_custom_flag_and_change_flag_test( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Gold = 100500
        customFlag = env.acc.SD.getCustomFlagById("rak")

        assert modeldata.FlagInfo.FlagType == FlagType.Default

        requests = [(Buy_custom_flag, BuyCustomFlagRequest(modeldata, {"flagId": ["rak"], "master_auid": [0], "guardParty": [False]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.FlagInfo.FlagType == FlagType.Special

        requests = [(Change_flag, ChangeFlagRequest(modeldata, {"flagId": ["default_flag"], "flagType": [0], "master_auid": [0], "guardParty": [False]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.FlagInfo.FlagType == FlagType.Default
        assert modeldata.FlagInfo.PersistentId == "default_flag"

    def change_flag_to_country_flag_test(self, env):
        modeldata = env.acc.model

        assert modeldata.FlagInfo.FlagType == FlagType.Default


        requests = [(Change_flag, ChangeFlagRequest(modeldata, {"flagId": ["belgium"], "flagType": [2], "master_auid": [0], "guardParty": [False]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.FlagInfo.FlagType == FlagType.Country
        assert modeldata.FlagInfo.PersistentId == "belgium"