import sys
sys.path.append('../')
sys.path.append('../..')
from logic.add_fake_friends import *
from binascii import crc32
from base.helpers import *
from enums import *

class add_fake_friends_test:

  def add_fake_friends_test( self, env ):
    modeldata = env.acc.model

    assert len(modeldata.FriendsKeeper) == 0

    requests =  [ ( Add_fake_friends, AddFakeFriendsRequest( modeldata, { }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.FriendsKeeper) > 0