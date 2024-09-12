#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
sys.path.append('../')
sys.path.append('../..')
from logic.guild_create import *
from logic.guild_rename import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class guild_rename_test:

  def guild_rename_test( self, env ):
    modeldata = env.acc.model
    env.acc.db.guildAuid = 0
    fullname = "Парася"
    shortname = "Хрю"
    modeldata.Resources.Silver = silver = 1000000
    modeldata.Resources.Gold = gold = 1000

    requests =  [ ( Guild_create, GuildCreateRequest( modeldata, { "fullname" : [fullname], "shortname" : [shortname] }, False ) ) ]
    changeList = env.execActions( requests )
    
    price = int(env.I.Config.getConfig( env.acc.userlocale ).GUILD_CREATE_PRICE_SILVER)
    assert silver - modeldata.Resources.Silver == price 

    
    fullname = "Свиноматки"
    shortname = "Уи"
    
    requests =  [ ( Guild_rename, GuildRenameRequest( modeldata, { "fullname" : [fullname], "shortname" : [shortname] }, False ) ) ]
    changeList = env.execActions( requests )
    
    price = int(env.I.Config.getConfig( env.acc.userlocale ).GUILD_RENAME_PRICE_GOLD)
    assert gold - modeldata.Resources.Gold == price 

    
  def guild_rename_no_gold_test( self, env ):
    modeldata = env.acc.model
    env.acc.db.guildAuid = 0
    fullname = "Piggies"
    shortname = "yiii"
    modeldata.Resources.Silver = silver = 1000000
    modeldata.Resources.Gold = gold = 1

    requests =  [ ( Guild_create, GuildCreateRequest( modeldata, { "fullname" : [fullname], "shortname" : [shortname] }, False ) ) ]
    changeList = env.execActions( requests )
    
    guilddata = env.acc.GuildData
    price = int(env.I.Config.getConfig( env.acc.userlocale ).GUILD_CREATE_PRICE_SILVER)
    assert silver - modeldata.Resources.Silver == price 

    
    fullname = "Boars"
    shortname = "oink"
    
    requests =  [ ( Guild_rename, GuildRenameRequest( modeldata, { "fullname" : [fullname], "shortname" : [shortname] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert changeList[1].get('ec') == EC.NOT_ENOUGH_GOLD
    price = int(env.I.Config.getConfig( env.acc.userlocale ).GUILD_RENAME_PRICE_GOLD)
    assert gold == modeldata.Resources.Gold 
    
  def guild_rename_not_in_guild_test( self, env ):
    env.acc.db.guildAuid = 0
    modeldata = env.acc.model
    fullname = "Piggies"
    shortname = "yiii"
    modeldata.Resources.Silver = silver = 1000000
    modeldata.Resources.Gold = gold = 1

    requests =  [ ( Guild_rename, GuildRenameRequest( modeldata, { "fullname" : [fullname], "shortname" : [shortname] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert changeList[0].get('ec') == EC.NOT_IN_GUILD
           