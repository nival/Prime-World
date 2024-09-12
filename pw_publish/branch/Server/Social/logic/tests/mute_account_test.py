import sys
sys.path.append('../')
from logic.mute_account import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class mute_account_test:
  def mute_account_test( self, env ):
    modeldata = env.acc.model
    requests =  [ ( Mute_account, MuteAccountRequest( modeldata, { "minutes" : ["10"], "reason" : ["Looser"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( env.acc.db.muted == 1 )
    assert( env.acc.db.mutereason == "Looser" )
    assert( env.acc.db.mutetime > 0)