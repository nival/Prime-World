# -*- coding: utf-8 -*-
from base.helpers import *

from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *

class FriendsDataCustom( BaseObject ):
    def __init__(self):
        self.__dict__["_modelChangeWriter"] = None
        self.__dict__["_writeChanges"] = False

    def save( self, save_data=None ):
        self._serializator.setMode( False ) # For server side
        save_data = save_data or self.generateJsonDict()
        return json_dumps( save_data )

    def load( self, data ):
        if isinstance(data, basestring):
            data = json_loads( data )
        self._serializator.fromDict( data )

    # IChangeWriter
    def modelChange( self, path, op, val ):
        if self._modelChangeWriter:
            self._modelChangeWriter.writeStringToResponse( self.__class__.__name__, "auto", path, op, val )

    # включаем авто-запись изменений в нашей ModelData (в указанный changeWriter)
    def write( self, changeWriter ):
        self._modelChangeWriter = changeWriter
        self._writeChanges = (changeWriter is not None)

    # отключаем авто-запись изменений в нашей ModelData
    def stop( self ):
        self._modelChangeWriter = None
        self._writeChanges = False

    # эмулируем доступ к элементу как у словаря, чтобы работал поиск по абсолютным путям
    def get( self, key ):
        return self.__dict__.get(key)

    # находим по auid == Person.person_uid == Friend.person_uid
    def findPersonByUid(self, person_uid):
        for friend_id,friend in self.FriendsKeeper.iteritems():
            if friend.person_uid == person_uid:
                return friend


    # Выдаем всех online-друзей
    def getOnlineFriendUids( self ):
        friendUids = []
        for friendId in self.FriendsKeeper:
            friend = self.getFriendByID( friendId )
            if friend and friend.online:
                friendUids.append( friend.person_uid )
        return friendUids


    def inviteFriend( self, socialExchange, acc, friend_auid ):
        if friend_auid != acc.auid:
            guildshortname = ""
            you = self.findPersonByUid(acc.auid)
            if you:
                guildshortname = you.guildshortname
            ourInfo = [{"type":"invite_friend", "person_uid":acc.auid, "nickName":acc.nick, "photoUrl":acc.db.photoUrl, "guildshortname":guildshortname}]
            socialExchange.sendMail( "pw", friend_auid, ourInfo, from_auid=acc.auid, from_sid=acc.sex_sid, from_server=acc.sex_server )
        else:
            warn("friend_auid(%s) == acc.auid(%s)" % (friend_auid, acc.auid))

    def hasRecentAlly(self, auid):
        for timestamp, friend in self.RecentAllies.iteritems():
            if friend.person_uid == auid:
                return True
        return False

    def removeRecentAlly(self, auid):
        found = None
        for timestamp, friend in self.RecentAllies.iteritems():
            if friend.person_uid == auid:
                found = timestamp
                break
        if found is None:
            return False
        else:
            self.RecentAllies.remove(found)
            return True

    def hasFriend(self, auid):
        for friendId, friend in self.myFriends.iteritems():
            if friend.person_uid == auid:
                return True
        return False

    # дополнительные (server-side) сериализуемые поля
    def generateBaseDict(self):
        return dict(
            next_uid_=self.next_uid_
        )

    def hasFriendOnPage(self, acc, changes):
        friends = sorted(self.myFriends.keys())[acc.model.PagesInfo.CurrBeginOfFriendsPage: acc.model.PagesInfo.CurrBeginOfFriendsPage + acc.getConfig().FRIENDS_PAGE_SIZE]
        auid = changes.get("friend_auid")
        #friend = self.findPersonByUid(auid)
        if auid and auid in friends:
            return True
        return False

    def fillFriend(self, storeFriend, friend):
        friend.person_uid = storeFriend.person_uid
        friend.nickName = storeFriend.nickName
        friend.gender = storeFriend.gender
        friend.fraction = storeFriend.fraction
        friend.photoUrl = storeFriend.photoUrl
        friend.fame = storeFriend.fame
        friend.online = storeFriend.online
        friend.InMatchmaking = storeFriend.InMatchmaking
        friend.mmInfo = storeFriend.mmInfo
        friend.Status = storeFriend.Status
        friend.lastLoginTime = storeFriend.lastLoginTime
        friend.lastLogoutTime = storeFriend.lastLogoutTime
        friend.friendRelation = storeFriend.friendRelation
        friend.guildshortname = storeFriend.guildshortname
        friend.IsMuted = bool(storeFriend.IsMuted)
