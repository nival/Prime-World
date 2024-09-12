import sys
sys.path.append('../')
from logic.finish_production import *
from logic.start_building_production import *
import time
sys.path.append('../..')
from enums import *

class finish_production_test:

  def finish_production_with_time_test( self, env ):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Production_Resource1")
    staticConstruction = env.acc.SD.getStaticConstruction(construction)
    now = int( round( time.time() ) )
    construction.StartProductionTime = construction.EndProductionTime = now
    construction.ProductionState = ProductionState.Finished

    requests = [(Finish_production, FinishProductionRequest(modeldata, {"seconds": [0]}, False))]
    changeList = env.execActions( requests )

    assert construction.StartProductionTime >= now - staticConstruction['productionTimePeriod'] - 5
    assert construction.ProductionState == ProductionState.Finished

    
  def finish_production_test( self, env ):
    # we now don't have cycles for production buildings
    return
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Production_Resource1")
    
    requests =  [ ( Start_building_production , StartBuildingProductionRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""], "cycle" : [str(0)], "aftercontext": ["false"] }, False ) ),
                  ( Finish_production , FinishProductionRequest( modeldata, {}, False ) ) ]
    changeList = env.execActions( requests )
    
    assert construction.ProductionState == ProductionState.Finished
