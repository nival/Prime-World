import sys
sys.path.append('../')
from logic.remove_friend import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class remove_friend_test:

  def remove_friend_test( self, env ):
    env.acc.db.guildAuid = 0
    requests =  [ ( Remove_friend, RemoveFriendRequest( env.acc.model, { "friend_uid" : ["100500"] }, False ) ) ]
    changeList = env.execActions( requests )