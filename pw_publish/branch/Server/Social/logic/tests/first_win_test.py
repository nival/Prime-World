# -*- coding: utf-8 -*-
#!/usr/bin/env python
import sys
sys.path.append('../')
sys.path.append('../../')
from logic.keepalive import *
from binascii import crc32
import time
import datetime
from Events.event import *
from Events.EventMap import *
from modeldata.validator import Validator
import EC
sys.path.append('../..')
from enums import *
import EC


class first_win_test:

  def set_first_win_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.GuardInfo.NumberOfWins =  env.acc.getConfig().NEWBIE_WINS

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

    map = {}
    map['FWODGroup'] = "pvp"
    modeldata.setFirstWinIfNeed( map, env.acc.getConfig() )

    assert len( modeldata.LordInfo.TodayWinMaps ) == 1
    assert "pvp" in modeldata.LordInfo.TodayWinMaps
    assert modeldata.LordInfo.TodayWinMaps["pvp"] > int(round(time.time()))-10


  def set_first_win_fail_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.GuardInfo.NumberOfWins =  env.acc.getConfig().NEWBIE_WINS

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

    modeldata.setFirstWinIfNeed( None, env.acc.getConfig() )

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0


  def set_first_win_fail2_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.GuardInfo.NumberOfWins =  env.acc.getConfig().NEWBIE_WINS

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

    map = ClassDict()
    modeldata.setFirstWinIfNeed( map, env.acc.getConfig() )

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0


  def set_first_win_fail3_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.GuardInfo.NumberOfWins =  env.acc.getConfig().NEWBIE_WINS

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

    map = {}
    map['FWODGroup'] = ""
    modeldata.setFirstWinIfNeed( map, env.acc.getConfig() )

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0


  def is_first_play_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.GuardInfo.NumberOfWins =  env.acc.getConfig().NEWBIE_WINS

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

    map = {}
    map['FWODGroup'] = "pvp"
    modeldata.setFirstWinIfNeed( map, env.acc.getConfig())

    assert len( modeldata.LordInfo.TodayWinMaps ) == 1
    assert "pvp" in modeldata.LordInfo.TodayWinMaps
    assert modeldata.LordInfo.TodayWinMaps["pvp"] > int(round(time.time()))-10

    map2 = {}
    map2['FWODGroup'] = "pvp"
    assert not modeldata.isFirstPlay( map2, env.acc.getConfig() )


  def is_first_play_newbie_test( self, env ):
    modeldata = env.acc.model

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

    map = {}
    map['FWODGroup'] = "pvp"
    modeldata.setFirstWinIfNeed( map, env.acc.getConfig() )

    assert len( modeldata.LordInfo.TodayWinMaps ) == 1


  def is_first_play_test2( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.GuardInfo.NumberOfWins =  env.acc.getConfig().NEWBIE_WINS

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

    map = {}
    map['FWODGroup'] = "pvp"
    modeldata.setFirstWinIfNeed( map, env.acc.getConfig() )

    assert len( modeldata.LordInfo.TodayWinMaps ) == 1
    assert "pvp" in modeldata.LordInfo.TodayWinMaps
    assert modeldata.LordInfo.TodayWinMaps["pvp"] > int(round(time.time()))-10

    map2 = {}
    map2['FWODGroup'] = "train"
    assert modeldata.isFirstPlay( map2, env.acc.getConfig() )


  def keepalive_first_win_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.GuardInfo.NumberOfWins =  env.acc.getConfig().NEWBIE_WINS

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

    map = {}
    map['FWODGroup'] = "pvp"
    modeldata.setFirstWinIfNeed( map, env.acc.getConfig() )

    assert len( modeldata.LordInfo.TodayWinMaps ) == 1
    assert "pvp" in modeldata.LordInfo.TodayWinMaps
    assert modeldata.LordInfo.TodayWinMaps["pvp"] > int(round(time.time()))-10

    f = Keepalive( KeepaliveRequest( modeldata, { "counter" : [0] } ), env.callback, request=env )
    f.onStart()

    assert len( modeldata.LordInfo.TodayWinMaps ) == 1
    assert "pvp" in modeldata.LordInfo.TodayWinMaps
    assert modeldata.LordInfo.TodayWinMaps["pvp"] > int(round(time.time()))-10

    modeldata.LordInfo.TodayWinMaps["pvp"] = int(round(time.time()))-100000
    f = Keepalive( KeepaliveRequest( modeldata, { "counter" : [0] } ), env.callback, request=env )
    f.onStart()

    assert len( modeldata.LordInfo.TodayWinMaps ) == 0

