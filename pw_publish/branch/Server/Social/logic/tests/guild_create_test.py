#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
sys.path.append('../')
sys.path.append('../..')
from logic.guild_create import *
from base.helpers import *
import EC

class guild_create_test:

    def guild_create_test(self, env):
        modeldata = env.acc.model
        env.acc.db.guildAuid = 0
        fullname = "test"
        shortname = "tst"
        modeldata.Resources.Silver = silver = 1000000

        requests = [(Guild_create, GuildCreateRequest(modeldata, {"fullname": [fullname], "shortname": [shortname]}, False))]
        changeList = env.execActions( requests )

        price = int(env.I.Config.getConfig(env.acc.userlocale).GUILD_CREATE_PRICE_SILVER)
        assert silver - modeldata.Resources.Silver == price


    def guild_create_rus_name_test( self, env ):
        modeldata = env.acc.model
        env.acc.db.guildAuid = 0
        fullname = "свиномат_свиномату_свиномат"
        shortname = "ссс"
        modeldata.Resources.Silver = silver = 1000000

        requests =  [ ( Guild_create, GuildCreateRequest( modeldata, { "fullname" : [fullname], "shortname" : [shortname] }, False ) ) ]
        changeList = env.execActions( requests )

        price = int(env.I.Config.getConfig( env.acc.userlocale ).GUILD_CREATE_PRICE_SILVER)
        assert silver - modeldata.Resources.Silver == price


    def guild_create_no_silver_test( self, env ):
        modeldata = env.acc.model
        env.acc.db.guildAuid = 0
        fullname = "AlKashi"
        shortname = "AKI"
        modeldata.Resources.Silver = silver = 0

        requests =  [ ( Guild_create, GuildCreateRequest( modeldata, { "fullname" : [fullname], "shortname" : [shortname] }, False ) ) ]
        changeList = env.execActions( requests )

        assert changeList[0].get("ec") == EC.NOT_ENOUGH_RESOURCES
