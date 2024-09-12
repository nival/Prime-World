from base.helpers import *
sys.path.append('../')
from logic.add_to_pocket import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class add_to_pocket_test:

  def add_to_pocket_test( self, env ):
    modeldata = env.acc.model
    buildCount = len(modeldata.Pocket)
    I = env.I

    plan_id = crc32("FirstBuy_Cat")
    level = 0

    requests = [ ( Add_to_pocket, AddToPocketRequest( modeldata, { "PersistentId" : ["" + str(plan_id) + ""], "level" : ["" + str(level) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstructionByPersistentId( plan_id )

    for buildingId in modeldata.Pocket:
      building = modeldata.getConstructionByID( buildingId )
      if building:
        if building.Level == level and building.PersistentId == plan_id:
          building = building
        else:
          building = None

    assert building != None
    assert len( modeldata.Pocket ) == buildCount + 1