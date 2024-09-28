import sys
sys.path.append('../')
from logic.give_stat_points import *
sys.path.append('../..')

class give_stat_points_test:
  def give_stat_points_test( self, env ):
    modeldata = env.acc.model

    hero = env.add_hero(modeldata, 'mowgly')

    statPoints = hero.TalentSets[0].Stats.StatPoints
    addValue = 10

    requests =  [ ( Give_stat_points, GiveStatPointsRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( hero.TalentSets[0].Stats.StatPoints == statPoints + addValue )