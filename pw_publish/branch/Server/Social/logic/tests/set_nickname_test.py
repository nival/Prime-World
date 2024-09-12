# -*- coding: utf-8 -*-
#!/usr/bin/env python
import sys
sys.path.append('../')
from logic.change_nickname import *
from base.helpers import *
sys.path.append('../..')
import EC

class set_nickname_test:
  
  def set_nickname_bad_length( self, env ):
    env.acc.db.nick = 'nick'
    # use 'used_nick' to emulate already registred nickname
    modeldata = env.acc.model
    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['very_very_very_very_very_very_long_nickname'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 0
    assert changeList[0]['ec'] == EC.NICK_BAD_PARAMS
    assert changeList[0]['error'] == "bad nickname length, should be in 3..32"

  def set_nickname_bad_special_symbols( self, env ):
    env.acc.db.nick = 'nick'
    # use 'used_nick' to emulate already registred nickname
    modeldata = env.acc.model
    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['bad  special'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 0
    assert changeList[0]['ec'] == EC.NICK_BAD_PARAMS
    assert changeList[0]['error'] == "two or more special symbols in a row or leading spaces"    
    
  def set_nickname_bad_character( self, env ):
    env.acc.db.nick = 'nick'
    # use 'used_nick' to emulate already registred nickname
    modeldata = env.acc.model
    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['русский english'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 0
    assert changeList[0]['ec'] == EC.NICK_BAD_PARAMS
    assert changeList[0]['error'] == "bad characters in nickname"        
    
  def set_nickname_bad_character2( self, env ):
    env.acc.db.nick = 'nick'
    # use 'used_nick' to emulate already registred nickname
    modeldata = env.acc.model
    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['ῷῷῷῷῷῷῷῷῷῷῷῷ'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 0
    assert changeList[0]['ec'] == EC.NICK_BAD_PARAMS
    assert changeList[0]['error'] == "bad characters in nickname"    
    
  def set_nickname_forbidden( self, env ):
    env.acc.db.nick = 'nick'
    # use 'used_nick' to emulate already registred nickname
    modeldata = env.acc.model
    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['admin'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 0
    assert changeList[0]['ec'] == EC.NICK_BAD_PARAMS
    assert changeList[0]['error'] == "nickname is forbidden"    
    
  def set_nickname_one_language( self, env ):
    env.acc.db.nick = 'nick'
    config = env.I.Config.getConfig( env.acc.userlocale )
    config.NICKNAME_REGEXES.append( u'^\s|[\s_\-]{2,}|\s$' )
    config.NICKNAME_REGEXES.append( u'[^abcçdefgğhıijklmnoöpqrsştuüwvxyzABCÇDEFGĞHIİJKLMNOÖPQRSŞTUÜWVXYZ0-9 _\-]' )
    # use 'used_nick' to emulate already registred nickname
    modeldata = env.acc.model
    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['русский'] }, False ) ) ]
    changeList = env.execActions( requests )
    assert changeList[0]['ok'] == 0
    assert changeList[0]['ec'] == EC.NICK_BAD_PARAMS
    assert changeList[0]['error'] == "bad characters in nickname"      
    
    
