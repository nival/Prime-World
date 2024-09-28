import sys
sys.path.append('../')
sys.path.append('../..')
from logic.craft_talents import *
from binascii import crc32
from base.helpers import *
from modeldata.StaticData import StaticData
import EC

class craft_talents_test:

  def craft_talents_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources = env.generate_resources(2000)

    construction = env.add_construction(modeldata, "Talent_Production")
    staticConstruction = env.acc.SD.getStaticConstruction( construction )
    inventoryCount = len(modeldata.UserInventory)

    requests =  [ ( Craft_talents , CraftTalentsRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""], "customValue": [str(1)], "afterContext": ["false"] }, False ) )]
    changeList = env.execActions( requests )

    assert len(modeldata.UserInventory) == inventoryCount + 1

  def craft_talent_1_test( self, env ):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Talent_Production")

    Resources = env.generate_resources(1000)
    modeldata.Resources = env.generate_resources(1000)

    requests = [ ( Craft_talents , CraftTalentsRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""], "customValue" : [1], "afterContext": ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstruction( construction )
    cost = env.get_paid_cost(Resources, modeldata.Resources)
    price = StaticData.getPriceInterpolated( staticConstruction['TransmutationLevels'], construction.ProductionLevel, None , "priceToStart", None )
    price.Perl = 1
    talentsForCycle = env.acc.getConfig().EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL
    coef = math.ceil(1*1.0/talentsForCycle)
    assert cost == env.acc.model.CalcPrice( price, coef, env.acc.SD ).Perl

  def craft_talent_2_test( self, env ):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Talent_Production")

    Resources = env.generate_resources(1000)
    modeldata.Resources = env.generate_resources(1000)

    requests = [ ( Craft_talents , CraftTalentsRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""], "customValue" : [2], "afterContext": ["false"] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstruction( construction )
    cost = env.get_paid_cost(Resources, modeldata.Resources)
    price = StaticData.getPriceInterpolated( staticConstruction['TransmutationLevels'], construction.ProductionLevel, None, "priceToStart", None )
    price.Perl = 1
    talentsForCycle = env.acc.getConfig().EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL
    coef = math.ceil(2*1.0/talentsForCycle)
    assert cost == env.acc.model.CalcPrice( price, coef, env.acc.SD ).Perl

  def craft_talent_90_test( self, env ):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Talent_Production")

    Resources = env.generate_resources(1000000)
    modeldata.Resources = env.generate_resources(1000000)

    requests = [ ( Craft_talents , CraftTalentsRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""], "customValue" : [90], "afterContext": ["false"] }, False ) ) ]
    changeList = env.execActions( requests )
    text = str(changeList)

    staticConstruction = env.acc.SD.getStaticConstruction( construction )
    cost = env.get_paid_cost(Resources, modeldata.Resources)
    price = StaticData.getPriceInterpolated( staticConstruction['TransmutationLevels'], construction.ProductionLevel, None, "priceToStart", None )
    price.Perl = 1
    talentsForCycle = env.acc.getConfig().EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL
    coef = math.ceil(90*1.0/talentsForCycle)
    assert cost == env.acc.model.CalcPrice( price, coef, env.acc.SD ).Perl

    assert text.count( "TransmutationRandomSeed" ) == 1

  # PF-72749
  def start_production_talent_neg_test( self, env ):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Talent_Production")

    Resources = env.generate_resources(1000)
    modeldata.Resources = env.generate_resources(1000)

    requests = [ ( Craft_talents , CraftTalentsRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""],  "customValue" : [-10], "afterContext": ["false"] }, False ) ) ]
    changeList = env.execActions( requests )
    assert( changeList[0].get("ec") == EC.DEBUG_MESSAGE )