#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
sys.path.append('../')
from logic.all import Buy_cycle, Start_building_production, Building_upgrade
from logic.requests.all import BuyCycleRequest, StartBuildingProductionRequest, BuildingUpgradeRequest
from binascii import crc32
import time
import EC
sys.path.append('../..')
from enums import *

class buy_cycle_test( ):
  def buy_cycle_no_production_state_test( self, env ):
    # No more cycles for production
    return
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Production_Resource1")	

    silver = modeldata.Resources.Silver = 1000

    requests = [ ( Buy_cycle , BuyCycleRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert changeList.get(0).get("ec") == EC.DEBUG_MESSAGE
    assert changeList.get(0).get("error") == 'Building is not in production state'

  #def buy_cycle_transmutation_test( self, env ): убрал, так как мы теперь не можем покупать циклы в трансмутации.
  #  modeldata = env.acc.model
  #
  #  construction = env.add_construction(modeldata, "Talent_Production")
  #  construction.cycle = 0
  #  construction.ProductionState = ProductionState.Busy
  #  construction.StartProductionTime = int(time.time()) - 5
  #  construction.EndProductionTime = construction.StartProductionTime + 30
  #  construction.ProductionCustomValue = 1
  #
  #  gold = modeldata.Resources.Gold = 1000
  #
  #  requests = [ ( Buy_cycle , BuyCycleRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
  #  changeList = env.execActions( requests )
  #
  #  cost = gold - modeldata.Resources.Gold
  #  assert construction.ProductionState == ProductionState.Finished
  #  #assert construction.EndProductionTime <= int(time.time())
  #  assert cost > 1
  #  assert len(construction.CraftedTalents) == 1


  def buy_cycle_production_test( self, env ):
    # No more cycles for production
    return
    modeldata = env.acc.model
    cycleLength = 10000
    cycleDone = 0.1
    
    goldPercent = 1
    for item in env.acc.SD.data['GoldPriceCycleTable']['goldtable']['Item']:
      if (1 - cycleDone) * 100 <= item['timePercent']:
        goldPercent = item['goldPercent'] / 100.0
        
    assert goldPercent == 1

    construction = env.add_construction(modeldata, "Production_Resource1")
    construction.cycle = 0
    construction.Level = 0
    construction.ProductionState = ProductionState.Busy
    construction.StartProductionTime = int(time.time()) - (cycleLength * cycleDone)
    construction.EndProductionTime = construction.StartProductionTime + cycleLength

    gold = modeldata.Resources.Gold = 1000

    requests = [ ( Buy_cycle , BuyCycleRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstruction( construction )
    prLevelFirst, prLevelSecond = env.acc.SD.getInterpolLevels( staticConstruction['ProductionLevels'], construction.Level )
    maxGold = prLevelFirst['cycles']['Item'][construction.cycle]['timeblock']['gold']
    
    cost1 = env.acc.SD.roundGold( maxGold * goldPercent )
    cost2 = gold - modeldata.Resources.Gold
    assert construction.ProductionState == ProductionState.Finished
    assert cost1 == cost2
  
  def buy_cycle_production_goldtable_test( self, env ):
    # No more cycles for production
    return
    modeldata = env.acc.model
    cycleLength = 10000
    cycleDone = 0.6
    
    goldPercent = 1
    for item in env.acc.SD.data['GoldPriceCycleTable']['goldtable']['Item']:
      if (1 - cycleDone) * 100 <= item['timePercent']:
        goldPercent = item['goldPercent'] / 100.0
    
    #sorry for hardcode )=
    assert goldPercent  == 0.34

    construction = env.add_construction(modeldata, "Production_Resource1")
    construction.cycle = 0
    construction.Level = 0
    construction.ProductionState = ProductionState.Busy
    construction.StartProductionTime = int(time.time()) - (cycleLength * cycleDone)
    construction.EndProductionTime = construction.StartProductionTime + cycleLength

    gold = modeldata.Resources.Gold = 1000

    requests = [ ( Buy_cycle , BuyCycleRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstruction( construction )
    prLevelFirst, prLevelSecond = env.acc.SD.getInterpolLevels( staticConstruction['ProductionLevels'], construction.Level )
    maxGold = prLevelFirst['cycles']['Item'][construction.cycle]['timeblock']['gold']
    
    cost1 = env.acc.SD.roundGold( maxGold * goldPercent )
    cost2 = gold - modeldata.Resources.Gold
    assert construction.ProductionState == ProductionState.Finished
    assert cost1 == cost2
    
  def buy_cycle_production_goldtable_test( self, env ):
    # No more cycles for production
    return
    modeldata = env.acc.model
    cycleLength = 10000
    cycleDone = 0.99
    
    goldPercent = 1
    for item in env.acc.SD.data['GoldPriceCycleTable']['goldtable']['Item']:
      if (1 - cycleDone) * 100 <= item['timePercent']:
        goldPercent = item['goldPercent'] / 100.0
    
    #sorry for hardcode )=    
    assert goldPercent == 0.25

    construction = env.add_construction(modeldata, "Production_Resource1", 29)
    construction.cycle = 3
    construction.ProductionState = ProductionState.Busy
    construction.StartProductionTime = int(time.time()) - (cycleLength * cycleDone)
    construction.EndProductionTime = construction.StartProductionTime + cycleLength

    gold = modeldata.Resources.Gold = 1000

    requests = [ ( Buy_cycle , BuyCycleRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstruction( construction )
    prLevelFirst, prLevelSecond = env.acc.SD.getInterpolLevels( staticConstruction['ProductionLevels'], construction.Level )
    maxGold = prLevelFirst['cycles']['Item'][construction.cycle]['timeblock']['gold']
    
    cost1 = env.acc.SD.roundGold( maxGold * goldPercent )
    cost2 = gold - modeldata.Resources.Gold
    assert construction.ProductionState == ProductionState.Finished
    assert cost1 == cost2
    
  def buy_cycle_production_goldtable_test2( self, env ):
    # No more cycles for production
    return
    modeldata = env.acc.model
    cycleLength = 10000
    cycleDone = 0.51
    
    goldPercent = 1
    for item in env.acc.SD.data['GoldPriceCycleTable']['goldtable']['Item']:
      if (1 - cycleDone) * 100 <= item['timePercent']:
        goldPercent = item['goldPercent'] / 100.0
    
    #sorry for hardcode )=    
    assert goldPercent == 0.5

    construction = env.add_construction(modeldata, "Production_Resource1", 29)
    construction.cycle = 3
    construction.ProductionState = ProductionState.Busy
    construction.StartProductionTime = int(time.time()) - (cycleLength * cycleDone)
    construction.EndProductionTime = construction.StartProductionTime + cycleLength

    gold = modeldata.Resources.Gold = 1000

    requests = [ ( Buy_cycle , BuyCycleRequest( modeldata, { "construction_id" : ["" + str(construction.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    staticConstruction = env.acc.SD.getStaticConstruction( construction )
    prLevelFirst, prLevelSecond = env.acc.SD.getInterpolLevels( staticConstruction['ProductionLevels'], construction.Level )
    maxGold = prLevelFirst['cycles']['Item'][construction.cycle]['timeblock']['gold']
    
    cost1 = env.acc.SD.roundGold( maxGold * goldPercent )
    cost2 = gold - modeldata.Resources.Gold
    assert construction.ProductionState == ProductionState.Finished
    assert cost1 == cost2