import sys
sys.path.append('../')
sys.path.append('../..')
from logic.boost_buildingproduction import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class boost_buildingproduction_test:

    def boost_buildingproduction_test( self, env ):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Crystal")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600 * 46

        modeldata.Resources.Resource1 = 50000
        modeldata.Resources.Resource2 = 50000
        modeldata.Resources.Resource3 = 50000
        Perl = modeldata.Resources.Perl = 0

        requests = [(Boost_buildingproduction,
                     BoostBuildingProductionRequest(modeldata,
                                                    {
                                                        "construction_id": [""+str(construction.id)+""],
                                                        "afterContext": ["false"],
                                                        "client_time": ["" + str(modeldata.FatClientServerTime) + ""]
                                                    }, False))]
        changeList = env.execActions(requests)
