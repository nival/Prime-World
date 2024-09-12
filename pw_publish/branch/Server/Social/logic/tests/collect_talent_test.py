import sys
sys.path.append('../')
from logic.collect_talent import *
from logic.craft_talents import *
from logic.start_building_production import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class collect_talent_test:
  def collect_talent_test( self, env ):
    pass

  def start_crystal_production_collect_start_test( self, env ):
    modeldata = env.acc.model
    cycle = 0
    customValue = 4

    construction = env.add_construction(modeldata, "Talent_Production")
    staticConstr = env.acc.SD.getStaticConstruction( construction )
    talentsForCycle = env.acc.getConfig().EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL
    perlsCost =  customValue / talentsForCycle

    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)

    assert modeldata.Resources.Perl == 2000
    
    requests = [ ( Craft_talents , CraftTalentsRequest(modeldata, {"construction_id": ["" + str(construction.id) + ""],
                                                                   "customValue": [customValue],
                                                                   "afterContext": ["false"]}, False))]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Perl == 2000 - perlsCost

    requests = [ ( Craft_talents , CraftTalentsRequest(modeldata, {"construction_id": ["" + str(construction.id) + ""],
                                                                   "customValue": [customValue],
                                                                   "afterContext": ["false"]}, False))]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Perl == 2000 - 2 * perlsCost

