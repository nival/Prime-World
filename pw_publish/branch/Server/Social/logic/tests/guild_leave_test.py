#!/usr/bin/env python
# -*- coding: utf-8 -*-


import sys
sys.path.append('../')
sys.path.append('../..')
from logic.guild_leave import *
from logic.guild_create import *
from binascii import crc32
from base.helpers import *
from enums import *

class guild_leave_test:

  def guild_leave_test( self, env ):
    modeldata = env.acc.model
    env.acc.db.guildAuid = 0
    fullname = "boobs"
    shortname = "O_O"
    modeldata.Resources.Silver = silver = 1000000

    requests =  [ ( Guild_create, GuildCreateRequest( modeldata, { "fullname" : [fullname], "shortname" : [shortname] }, False ) ) ]
    changeList = env.execActions( requests )
    
    price = int(env.I.Config.getConfig( env.acc.userlocale ).GUILD_CREATE_PRICE_SILVER)
    assert silver - modeldata.Resources.Silver == price  


    requests =  [ ( Guild_leave, GuildLeaveRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert env.acc.db.guildAuid == 0
    
  def guild_leave_with_stat_bonus_test( self, env ):
    modeldata = env.acc.model
    fullname = "boobs"
    shortname = "O_O"
    modeldata.Resources.Silver = silver = 1000000

    env.acc.db.guildAuid = 'ржитсярожьовесовситсячечевитсячечевица'
    
    hero = env.add_hero(modeldata, 'mowgly')
    hero.TalentSets[0].GuildStats.StatPoints = 50
    hero.TalentSets[0].GuildStats.Health = 100

    requests =  [ ( Guild_leave, GuildLeaveRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert env.acc.db.guildAuid == 0
    assert hero.TalentSets[0].GuildStats.StatPoints == 0
    assert hero.TalentSets[0].GuildStats.Health == 0
