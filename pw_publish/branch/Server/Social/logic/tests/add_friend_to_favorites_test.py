import sys
sys.path.append('../')
from logic.add_friend_to_favorites import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class add_friend_to_favorites_test:
  def add_friend_to_favorites_test( self, env ):   
    modeldata = env.acc.model
    friendsdata = env.acc.friendsdata
    assert len( modeldata.Friends.Favorites ) == 0

    requests =  [ ( Add_friend_to_favorites, AddFriendToFavoritesRequest( modeldata, { "friend_uid" : ["1"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.Friends.Favorites ) == 1

  def add_friend_to_favorites_twice_test( self, env ):   
    modeldata = env.acc.model
    friendsdata = env.acc.friendsdata
    assert len( modeldata.Friends.Favorites ) == 0

    requests =  [ ( Add_friend_to_favorites, AddFriendToFavoritesRequest( modeldata, { "friend_uid" : ["1"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.Friends.Favorites ) == 1

    requests =  [ ( Add_friend_to_favorites, AddFriendToFavoritesRequest( modeldata, { "friend_uid" : ["1"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.Friends.Favorites ) == 1

  def add_friend_to_favorites_limit_test( self, env ):   
    modeldata = env.acc.model
    friendsdata = env.acc.friendsdata
    count = 32
    for i in xrange(1, count + 1):
      uid =  friendsdata.addNewFriend()
      modeldata.Friends.Favorites.append(uid)
    assert len( modeldata.Friends.Favorites ) == count

    requests =  [ ( Add_friend_to_favorites, AddFriendToFavoritesRequest( modeldata, { "friend_uid" : ["1"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.Friends.Favorites ) == count