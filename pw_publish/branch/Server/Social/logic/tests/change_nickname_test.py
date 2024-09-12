import sys
sys.path.append('../')
from logic.change_nickname import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class change_nickname_test:

  def change_nickname_test( self, env ):
    env.acc.db.nick = "nick"
    modeldata = env.acc.model
    modeldata.Resources.Gold = 0
    env.acc.db.nickChanged = 0

    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['Mr_Facker'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert env.acc.db.nick == 'Mr_Facker'
    assert (env.acc.db.nickChanged == 1)
    assert (modeldata.Resources.Gold == 0)

  def change_nick_test2( self, env ):
    env.acc.db.nick = "nick"
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.acc.getConfigValue("COST_NICK_CHANGE")
    freeChangesLimit = env.acc.getConfigValue("FREE_NICK_CHANGES")
    env.acc.db.nickChanged = freeChangesLimit

    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['Mr_Facker'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert env.acc.db.nick == 'Mr_Facker'
    assert (env.acc.db.nickChanged == freeChangesLimit + 1)
    assert (modeldata.Resources.Gold == 0)

  def change_nick_test3( self, env ):
    env.acc.db.nick = "nick"
    modeldata = env.acc.model
    modeldata.Resources.Gold = 0
    freeChangesLimit = env.acc.getConfigValue("FREE_NICK_CHANGES")
    env.acc.db.nickChanged = freeChangesLimit

    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['Mr_Facker'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( changeList.get("ModelData") == None )     
    assert env.acc.db.nick == 'nick'
    assert (env.acc.db.nickChanged == freeChangesLimit)
    assert (modeldata.Resources.Gold == 0)
    
  def change_same_nick_test( self, env ):
    env.acc.db.nick = "nick"
    modeldata = env.acc.model
    changePrice = env.acc.getConfigValue("COST_NICK_CHANGE")
    modeldata.Resources.Gold = changePrice
    freeChangesLimit = env.acc.getConfigValue("FREE_NICK_CHANGES")
    env.acc.db.nickChanged = freeChangesLimit

    requests = [ ( Change_nickname, ChangeNicknameRequest( modeldata, { "nickname" : ['nick'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( changeList.get("ModelData") == None )     
    assert env.acc.db.nick == 'nick'
    assert (env.acc.db.nickChanged == freeChangesLimit)
    assert (modeldata.Resources.Gold == changePrice)