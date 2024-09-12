import sys
sys.path.append('../')
from logic.increase_stat import *
from binascii import crc32
sys.path.append('../..')
from enums import *
import EC

class increase_stat_test:
  def increase_stat_test( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
    hero.changeExperience( 100500, env.acc.model, env.I.WS, env.acc, env.I )
    addValue = 1
    force = hero.TalentSets[0].Force

    Health = hero.TalentSets[0].Stats.Health
    points = hero.TalentSets[0].Stats.StatPoints

    requests =  [ ( Increase_stat, IncreaseStatRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "stat" : ["Health"], "value" : [addValue], "talent_set_id": ["0"]  }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Stats.StatPoints == points - addValue
    assert hero.TalentSets[0].Stats.Health - Health == addValue * env.acc.SD.getStatPointsMultiplyer( "Life" )
    assert hero.TalentSets[0].Force == force
    
  def increase_stat_many_test( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
    hero.changeExperience( 100500, env.acc.model, env.I.WS, env.acc, env.I )
    force = hero.TalentSets[0].Force

    Health = hero.TalentSets[0].Stats.Health
    points = hero.TalentSets[0].Stats.StatPoints
    addValue = 5

    requests =  [ ( Increase_stat, IncreaseStatRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "stat" : ["Health"], "value" : ["" + str(addValue) + ""], "talent_set_id": ["0"]  }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Stats.StatPoints == points - addValue
    assert hero.TalentSets[0].Stats.Health - Health == addValue * env.acc.SD.getStatPointsMultiplyer( "Life" )
    assert hero.TalentSets[0].Force == force
    
  def increase_wrong_stat_test( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
    hero.changeExperience( 100500, env.acc.model, env.I.WS, env.acc, env.I )
    addValue = 1
    force = hero.TalentSets[0].Force

    Health = hero.TalentSets[0].Stats.Health
    points = hero.TalentSets[0].Stats.StatPoints

    requests =  [ ( Increase_stat, IncreaseStatRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "stat" : ["iq"], "value" : [addValue], "talent_set_id": ["0"]  }, False ) ) ]
    changeList = env.execActions( requests )

    changeList[0]['ec'] = EC.DEBUG_MESSAGE
    
  def increase_guild_stat_test( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
    #hero.changeExperience( 100500, env.acc.model, env.I.WS, env.acc, env.I )
    addValue = 1
    force = hero.TalentSets[0].Force
    
    hero.TalentSets[0].GuildStats.StatPoints = 1

    Health = hero.TalentSets[0].GuildStats.Health
    points = hero.TalentSets[0].GuildStats.StatPoints

    requests =  [ ( Increase_stat, IncreaseStatRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "stat" : ["Health"], "value" : [addValue], "talent_set_id": ["0"]  }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].GuildStats.StatPoints == points - addValue
    assert hero.TalentSets[0].GuildStats.Health - Health == addValue * env.acc.SD.getStatPointsMultiplyer( "Life" )
    assert hero.TalentSets[0].Force == force
    
  def increase_guild_stat_many_test( self, env ):
    modeldata = env.acc.model

    hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
    #hero.changeExperience( 100500, env.acc.model, env.I.WS, env.acc, env.I )
    addValue = 1
    guildAddValue = 1
    
    hero.TalentSets[0].Stats.StatPoints = 1
    hero.TalentSets[0].GuildStats.StatPoints = 2

    requests =  [ ( Increase_stat, IncreaseStatRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "stat" : ["Health"], "value" : [addValue + guildAddValue], "talent_set_id": ["0"]  }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].Stats.StatPoints == 0
    assert hero.TalentSets[0].GuildStats.StatPoints == 1
    assert hero.TalentSets[0].Stats.Health == addValue * env.acc.SD.getStatPointsMultiplyer( "Life" )
    assert hero.TalentSets[0].GuildStats.Health == guildAddValue * env.acc.SD.getStatPointsMultiplyer( "Life" )