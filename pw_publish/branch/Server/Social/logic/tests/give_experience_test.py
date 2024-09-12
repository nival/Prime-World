import sys
sys.path.append('../')
from logic.give_experience import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *

class give_experience_test:
  def give_experience_test( self, env ):
    modeldata = env.acc.model

    hero = env.add_hero(modeldata, 'mowgly')

    experience = hero.Experience
    addValue = 1

    requests = [ ( Give_experience, GiveExperienceRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( hero.Experience == experience + addValue )

  def give_experience_with_1_lvlup_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.Fame = fame = 0

    hero = env.add_hero(modeldata, 'mowgly')
    statpoints = hero.TalentSets[0].Stats.StatPoints
    
    experience = hero.Experience
    addValue = 300

    requests = [ ( Give_experience, GiveExperienceRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( hero.Experience == experience + addValue )
    assert fame < modeldata.LordInfo.Fame 
    assert statpoints < hero.TalentSets[0].Stats.StatPoints

  def give_max_experience_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.Fame = fame = 0

    hero = env.add_hero(modeldata, 'mowgly')
    statpoints = hero.TalentSets[0].Stats.StatPoints

    experience = hero.Experience
    addValue = 1000000

    requests = [ ( Give_experience, GiveExperienceRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( hero.Experience == env.acc.SD.getMaxHeroExp()-1 )
    assert( fame < modeldata.LordInfo.Fame )
    assert statpoints < hero.TalentSets[0].Stats.StatPoints

  def give_experience_with_many_lvlup_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.Fame = fame = 0

    hero = env.add_hero(modeldata, 'mowgly')
    statpoints = hero.TalentSets[0].Stats.StatPoints

    experience = hero.Experience
    addValue = 1001

    requests = [ ( Give_experience, GiveExperienceRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.Experience == experience + addValue 
    assert fame < modeldata.LordInfo.Fame 
    assert statpoints < hero.TalentSets[0].Stats.StatPoints