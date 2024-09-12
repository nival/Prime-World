import sys
sys.path.append('../')
from binascii import crc32
import time
sys.path.append('../..')
from enums import *

class quest_exec_condition_test( ):
  def quest_exec_condition8_test( self, env ):
    modeldata = env.acc.model
    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes
		Buildings = modeldata.Buildings
		Lord = modeldata.Lord
		return Lord.Resources.Resource1"""
    modeldata.Resources.Resource1 = 100
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 100

    modeldata.Resources.Resource1 = 666
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 666


  def quest_exec_condition7_test( self, env ):
    modeldata = env.acc.model		
    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes
		Buildings = modeldata.Buildings
		Lord = modeldata.Lord
		for building in Buildings:
			if building.ClassType=="HouseBuilding":
				return 1
		return 0"""
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0

    construction = env.add_construction(modeldata, "House_4")

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 1


  def quest_exec_condition6_test( self, env ):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Tavern")

    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes
		Buildings = modeldata.Buildings
		Lord = modeldata.Lord
		for building in Buildings:
			if building.PersistentId=="Tavern" and building.ProductionState==ProductionState.Busy:
				return 1
		return 0"""
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0

    construction.ProductionState = ProductionState.Busy

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 1


  def quest_exec_condition5_test( self, env ):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Tavern")

    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes
		Buildings = modeldata.Buildings
		Lord = modeldata.Lord
		for building in Buildings:
			if building.PersistentId=="Tavern":
				return 1
		return 0"""
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 1

    modeldata.Buildings.remove( construction.id)

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0


  def quest_exec_condition4_test( self, env ):
    modeldata = env.acc.model
    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes
		Buildings = modeldata.Buildings
		Lord = modeldata.Lord
		if Lord.LevelOfExpansion>0:
			return 1
		return 0"""
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0

    modeldata.LordInfo.LevelOfExpansion = 2

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 1


  def quest_exec_condition3_test( self, env ):
    modeldata = env.acc.model
    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes
		Buildings = modeldata.Buildings
		Lord = modeldata.Lord
		for hero in Heroes:
			for talent in hero.TalentSets[0].Talents:
				if not talent.IsDefaultForHero(hero.PersistentId):
					return 1
		return 0"""
    for heroId in modeldata.Heroes:
      hero = modeldata.getHeroByID( heroId )
      break

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0

    mdTalent = modeldata.getTalentByID(hero.TalentSets[0].Talents.get( 13 ))
    mdTalent.defaultForHero = None
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 1


  def quest_exec_condition2_test( self, env ):
    modeldata = env.acc.model
    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes
		Buildings = modeldata.Buildings
		Lord = modeldata.Lord
		for hero in Heroes:
			if hero.TalentSets[0].Stats.Agility>0 or hero.TalentSets[0].Stats.Cunning>0 or hero.TalentSets[0].Stats.Fortitude>0 or hero.TalentSets[0].Stats.Health>0 or hero.TalentSets[0].Stats.Intellect>0 or hero.TalentSets[0].Stats.Mana>0 or hero.TalentSets[0].Stats.Strength>0 or hero.TalentSets[0].Stats.Will>0:
				return 1
		return 0"""
    for heroId in modeldata.Heroes:
      hero = modeldata.getHeroByID( heroId )
      break

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0

    hero.TalentSets[0].Stats.Agility = 2

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 1

  def quest_exec_condition1_test( self, env ):
    modeldata = env.acc.model
    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes;
		Buildings = modeldata.Buildings;
		Lord = modeldata.Lord;
		for hero in Heroes:
			for talent in hero.TalentSets[0].Talents:
				if talent.PersistentId=="G185" and not talent.IsDefaultForHero(hero.PersistentId):
					return 1
		return 0"""
    for heroId in modeldata.Heroes:
      hero = modeldata.getHeroByID( heroId )
      for key in hero.TalentSets[0].Talents.keys():
        hero.TalentSets[0].Talents.remove( key )

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0

    talent = env.add_talent(modeldata, "G185")

    hero.TalentSets[0].Talents.add( 33, talent.id )

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 1

    talent.defaultForHero = hero
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0


  def quest_exec_condition_count_test( self, env ):
    modeldata = env.acc.model
    
    construction = env.add_construction(modeldata, "Tavern")

    conditionFunc = """def Condition( modeldata, **kwargs ):
		Heroes = modeldata.Heroes
		Buildings = modeldata.Buildings
		Lord = modeldata.Lord
		for building in Buildings:
			if building.PersistentId=="Tavern" and building.ProductionState==ProductionState.Busy:
				return 1
		return 0"""
    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 0

    construction.ProductionState = ProductionState.Busy

    result = modeldata.execQuestCondition( conditionFunc, 1, env.acc.SD, env.acc.getConfig() )
    assert result == 1
