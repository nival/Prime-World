import sys
sys.path.append('../')
from logic.remove_friend_from_favorites import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class remove_friend_from_favorites_test:
  def remove_friend_from_favorites_test( self, env ):   
    modeldata = env.acc.model
    friendsdata = env.acc.friendsdata
    modeldata.Friends.Favorites.append(1)
    favoritesCount = len( modeldata.Friends.Favorites )

    requests =  [ ( Remove_friend_from_favorites, RemoveFriendFromFavoritesRequest( modeldata, { "friend_uid" : ["1"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.Friends.Favorites ) == favoritesCount - 1