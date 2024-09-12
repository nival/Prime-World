import sys
sys.path.append('../')
from logic.decline_friend import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class decline_friend_test:

  def decline_friend_test( self, env ):
    modeldata = env.acc.model
    friend = modeldata.newSimpleFriend( )[0]
    friend.person_uid = 100504
    friend.nickName = "aya"
    friend.photoUrl = "http://gyazo.nivalnetwork.com/db/2191c4c92fdc03151d45d255d089ca28.png"   
    modeldata.Friends.IncomingInvites.add(friend.id) 

    assert len(modeldata.Friends.IncomingInvites) > 0
    size = len(modeldata.Friends.IncomingInvites)

    friend = modeldata.getSimpleFriendByID(modeldata.Friends.IncomingInvites.keys()[0])

    requests =  [ ( Decline_friend, DeclineFriendRequest( modeldata, { "friend_id" : ["" + str(friend.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert size - 1 == len(modeldata.Friends.IncomingInvites)

