# -*- coding: utf-8 -*-
#!/usr/bin/env python
import sys
sys.path.append('../')
from logic.check_nickname import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class check_nickname_test:
  
  def free_nick_must_pass_checking_test( self, env ):
    env.acc.db.nick = 'nick'
    # use 'used_nick' to emulate already registred nickname
    modeldata = env.acc.model
    requests = [ ( Check_nickname, CheckNicknameRequest( modeldata, { "nickname" : ['not_used_nick'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 1
    assert env.acc.db.nick == 'nick'

  def cyrillic_nick_must_pass_checking_test( self, env ):
    env.acc.db.nick = 'nick'
    # use 'used_nick' to emulate already registred nickname
    modeldata = env.acc.model
    requests = [ ( Check_nickname, CheckNicknameRequest( modeldata, { "nickname" : ['кирилический ник'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 1
    assert env.acc.db.nick == 'nick'


  def existing_nick_must_fail_checking_test( self, env ):
    env.acc.db.nick = 'nick'
    modeldata = env.acc.model
    requests = [ ( Check_nickname, CheckNicknameRequest( modeldata, { "nickname" : ['used_nick'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 0
    assert env.acc.db.nick == 'nick'