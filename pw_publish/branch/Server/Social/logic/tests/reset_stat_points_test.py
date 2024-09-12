import sys
sys.path.append('../')
from logic.reset_stat_points import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class reset_stat_points_test:
  def reset_stat_points_test( self, env ):
    modeldata = env.acc.model

    modeldata.Resources.Perl = Perl = 100
    pricePerl = env.acc.SD.getStatsResetPriceCoef().Perl

    hero = env.add_hero(modeldata, 'mowgly')
    statPoints = hero.TalentSets[0].Stats.StatPoints = 0
    hero.Experience = 1050
    intellect = hero.TalentSets[0].Stats.Intellect = 5


    heroLvl = env.acc.SD.getHeroExpLevel(hero.Experience)

    Health = hero.TalentSets[0].Stats.Health
    points = hero.TalentSets[0].Stats.StatPoints
    addValue = 5

    requests =  [ ( Reset_stat_points, ResetStatPointsRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "afterContext": ["false"], "talent_set_id": ["0"]  }, False ) ) ]
    changeList = env.execActions( requests )

    assert statPoints < intellect
    assert hero.TalentSets[0].Stats.Intellect == 0
    assert Perl == modeldata.Resources.Perl + env.acc.SD.roundFloatToInt((heroLvl + 1) * pricePerl)
    
  def reset_guild_stat_points_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Perl = Perl = 100
    
    guildPoints = 5

    construction = env.add_construction(modeldata, "Guild")
    construction.Level = 1
    tmpGuildLevel = env.acc.SD.data['GuildLevels']['levels']['Item'][1].copy()
    
    env.acc.SD.data['GuildLevels']['levels']['Item'][1]['Bonuses'] = { 'Item' : [ { 'MasterPoints' : guildPoints, 'classType' : 'GuildStatsBonus' } ] }

    hero = env.add_hero(modeldata, 'mowgly')
    statPoints = hero.TalentSets[0].GuildStats.StatPoints = 2
    intellect = hero.TalentSets[0].GuildStats.Intellect = 3

    points = hero.TalentSets[0].Stats.StatPoints

    requests =  [ ( Reset_stat_points, ResetStatPointsRequest( modeldata, { "hero_id" : ["" + str(hero.id) + ""], "afterContext": ["false"], "talent_set_id": ["0"]  }, False ) ) ]
    changeList = env.execActions( requests )

    assert hero.TalentSets[0].GuildStats.Intellect == 0
    assert hero.TalentSets[0].GuildStats.StatPoints == guildPoints
    env.acc.SD.data['GuildLevels']['levels']['Item'][1] = tmpGuildLevel.copy()