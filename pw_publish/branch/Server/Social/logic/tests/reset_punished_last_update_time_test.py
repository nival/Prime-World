import sys
sys.path.append('../')
sys.path.append('../..')
from logic.reset_punished_last_update_time import *


class reset_punished_last_update_time_test:

    def reset_punished_last_update_time_test(self, env):
        modeldata = env.acc.model
        assert modeldata.LordInfo.PunishedNextUpdateTime == 0

        requests = [(Reset_punished_last_update_time, ResetPunishedNextUpdateTimeRequest(modeldata, {}, False))]
        changeList = env.execActions(requests)

        assert modeldata.LordInfo.PunishedNextUpdateTime > 0