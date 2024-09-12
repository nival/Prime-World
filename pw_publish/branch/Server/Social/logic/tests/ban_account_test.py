import sys
sys.path.append('../')
from logic.ban_account import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class ban_account_test:
  def ban_account_test( self, env ):
    modeldata = env.acc.model
    requests =  [ ( Ban_account, BanAccountRequest( modeldata, { "minutes" : ["10"], "reason" : ["Looser"], "autoBan" : ["0"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( env.acc.db.banned == True )
    assert( env.acc.db.autoban == False )
    assert( env.acc.db.banreason == "Looser" )
    assert( env.acc.db.bantime > 0)