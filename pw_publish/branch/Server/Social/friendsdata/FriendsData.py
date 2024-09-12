# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import Friend
import FriendError
import FriendMMInfo

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from FriendsDataCustom import FriendsDataCustom

class FriendsData(ChangeHandler, FriendsDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "ignores":1,
    } 


    def __init__(self):
        FriendsDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["ErrorKeeper"] = Keeper(self)
        self.__dict__["FriendsKeeper"] = Keeper(self)
        self.__dict__["errors"] = Set(self)
        self.__dict__["ignores"] = SimpleList(self)
        self.__dict__["invites"] = Set(self)
        self.__dict__["myFriends"] = Set(self)
        self.__dict__["RecentAllies"] = Collection(self)


    def init(self, changeWriter):
        self.write(changeWriter)
        self.ErrorKeeper.init(u"ErrorKeeper", self, "FriendError")
        self.FriendsKeeper.init(u"FriendsKeeper", self, "Friend")
        self.errors.init(self.ErrorKeeper, u"errors", self)
        self.ignores.init(u"ignores", self)
        self.invites.init(self.FriendsKeeper, u"invites", self)
        self.myFriends.init(self.FriendsKeeper, u"myFriends", self)
        self.RecentAllies.init(self.FriendsKeeper, u"RecentAllies", self)


    @staticmethod
    def initJsonTypes(TCustomFriendsData): # конечный класс CustomFriendsData будет передавать снаружи, из datamanager
        if "FriendsData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomFriendsData,
            Friend.Friend,
            FriendError.FriendError,
            FriendMMInfo.FriendMMInfo,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "FriendsData" : TCustomFriendsData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "Friend" : Friend.Friend
            , "FriendError" : FriendError.FriendError
            , "FriendMMInfo" : FriendMMInfo.FriendMMInfo
            })  
        else:
            err("FriendsData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewFriendError(self):
        uid = self.nextGUID()
        var = FriendError.FriendError(self, uid, "ErrorKeeper/"+str(uid))
        var.init_add()
        self.ErrorKeeper.add(uid, var)
        return uid


    def getFriendErrorByID(self, id):
        return self.ErrorKeeper.get(id)


    def newFriendError(self):
        _id = self.addNewFriendError()
        _data = self.getFriendErrorByID(_id)
        return _data, _id
    def addNewFriend(self):
        uid = self.nextGUID()
        var = Friend.Friend(self, uid, "FriendsKeeper/"+str(uid))
        var.init_add()
        self.FriendsKeeper.add(uid, var)
        return uid


    def getFriendByID(self, id):
        return self.FriendsKeeper.get(id)


    def newFriend(self):
        _id = self.addNewFriend()
        _data = self.getFriendByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.errors.deleteByID(id)
        self.ignores.deleteByID(id)
        self.invites.deleteByID(id)
        self.myFriends.deleteByID(id)
        self.RecentAllies.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.ErrorKeeper.deleteByID(id)
        self.FriendsKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        FriendError = self.getFriendErrorByID(id)
        if FriendError:
            obj = FriendError
        Friend = self.getFriendByID(id)
        if Friend:
            obj = Friend
        return obj


    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = FriendsDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            ErrorKeeper=self.__dict__["ErrorKeeper"].generateJsonDict(),
            errors=self.__dict__["errors"].getJsonDict(),
            FriendsKeeper=self.__dict__["FriendsKeeper"].generateJsonDict(),
            ignores=self.__dict__["ignores"].getJsonDict(),
            invites=self.__dict__["invites"].getJsonDict(),
            myFriends=self.__dict__["myFriends"].getJsonDict(),
            RecentAllies=self.__dict__["RecentAllies"].getJsonDict(),
        )
        return { "FriendsData": _dct }
    

    def serializeToFile(self, file):
        pass
        self.ignores.serializeToFile(file, "ignores")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
FriendsData.initJsonTypes(FriendsData)
