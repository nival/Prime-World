import sys
sys.path.append('../')
from logic.stop_building_production import *
from logic.start_building_production import *
from logic.building_upgrade import *
from base.helpers import *
from enums import *
import EC

class stop_building_production_test:

  def stop_idle_building_production_test( self, env ):
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")
    heroes = env.add_heroes_to_construction(modeldata, construction, 2)

    requests = [ ( Stop_building_production , StopBuildingProductionRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert construction.ProductionState == ProductionState.Idle
    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE
    

