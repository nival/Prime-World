# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ForceLimits
import Friend
import FriendError
import FriendMMInfo
import PartyMember
import RatingLimits

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from PartyDataCustom import PartyDataCustom

class PartyData(ChangeHandler, PartyDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "afterBattleLockEndTime":1,
        "foes_ready":1,
        "InMatchmaking":1,
        "madeAfterBattle":1,
        "mapID":1,
        "owner":1,
        "party_uid":1,
        "withBots":1,
    } 


    def __init__(self):
        PartyDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["ErrorKeeper"] = Keeper(self)
        self.__dict__["PartyMemberKeeper"] = Keeper(self)
        self.__dict__["PersonKeeper"] = Keeper(self)
        self.__dict__["afterBattleLockEndTime"] = 0
        self.__dict__["errors"] = Set(self)
        self.__dict__["foes_ready"] = 0
        self.__dict__["ForceLimits"] = ForceLimits.ForceLimits(self)
        self.__dict__["InMatchmaking"] = False
        self.__dict__["madeAfterBattle"] = False
        self.__dict__["mapID"] = ""
        self.__dict__["members"] = Set(self)
        self.__dict__["owner"] = Ref(self)
        self.__dict__["party_uid"] = 0
        self.__dict__["RatingLimits"] = RatingLimits.RatingLimits(self)
        self.__dict__["withBots"] = False


    def init(self, changeWriter):
        self.write(changeWriter)
        self.ErrorKeeper.init(u"ErrorKeeper", self, "FriendError")
        self.PartyMemberKeeper.init(u"PartyMemberKeeper", self, "PartyMember")
        self.PersonKeeper.init(u"PersonKeeper", self, "Friend")
        self.errors.init(self.ErrorKeeper, u"errors", self)
        self.ForceLimits.setPath(u"ForceLimits")
        self.members.init(self.PartyMemberKeeper, u"members", self)
        self.owner.init(self.PartyMemberKeeper, u"/", self, "owner")
        self.RatingLimits.setPath(u"RatingLimits")


    @staticmethod
    def initJsonTypes(TCustomPartyData): # конечный класс CustomPartyData будет передавать снаружи, из datamanager
        if "PartyData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomPartyData,
            ForceLimits.ForceLimits,
            Friend.Friend,
            FriendError.FriendError,
            FriendMMInfo.FriendMMInfo,
            PartyMember.PartyMember,
            RatingLimits.RatingLimits,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "PartyData" : TCustomPartyData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "ForceLimits" : ForceLimits.ForceLimits
            , "Friend" : Friend.Friend
            , "FriendError" : FriendError.FriendError
            , "FriendMMInfo" : FriendMMInfo.FriendMMInfo
            , "PartyMember" : PartyMember.PartyMember
            , "RatingLimits" : RatingLimits.RatingLimits
            })  
        else:
            err("PartyData.initJsonTypes called twice! The second call is:\n%s", errStack())

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
    def addNewPartyMember(self):
        uid = self.nextGUID()
        var = PartyMember.PartyMember(self, uid, "PartyMemberKeeper/"+str(uid))
        var.init_add()
        self.PartyMemberKeeper.add(uid, var)
        return uid


    def getPartyMemberByID(self, id):
        return self.PartyMemberKeeper.get(id)


    def newPartyMember(self):
        _id = self.addNewPartyMember()
        _data = self.getPartyMemberByID(_id)
        return _data, _id
    def addNewFriend(self):
        uid = self.nextGUID()
        var = Friend.Friend(self, uid, "PersonKeeper/"+str(uid))
        var.init_add()
        self.PersonKeeper.add(uid, var)
        return uid


    def getFriendByID(self, id):
        return self.PersonKeeper.get(id)


    def newFriend(self):
        _id = self.addNewFriend()
        _data = self.getFriendByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.errors.deleteByID(id)
        self.ForceLimits.deleteByID(id)
        self.members.deleteByID(id)
        self.owner.deleteByID(id)
        self.RatingLimits.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.ErrorKeeper.deleteByID(id)
        self.PartyMemberKeeper.deleteByID(id)
        self.PersonKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        FriendError = self.getFriendErrorByID(id)
        if FriendError:
            obj = FriendError
        PartyMember = self.getPartyMemberByID(id)
        if PartyMember:
            obj = PartyMember
        Friend = self.getFriendByID(id)
        if Friend:
            obj = Friend
        return obj


    def __setattr__(self, name, val):
        if name == "owner":
            self.__dict__["owner"].set(val)
            return    
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = PartyDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            afterBattleLockEndTime=self.__dict__["afterBattleLockEndTime"],
            ErrorKeeper=self.__dict__["ErrorKeeper"].generateJsonDict(),
            errors=self.__dict__["errors"].getJsonDict(),
            foes_ready=self.__dict__["foes_ready"],
            ForceLimits = self.__dict__["ForceLimits"].generateJsonDict(),
            InMatchmaking=self.__dict__["InMatchmaking"],
            madeAfterBattle=self.__dict__["madeAfterBattle"],
            mapID=self.__dict__["mapID"],
            members=self.__dict__["members"].getJsonDict(),
            owner=self.__dict__["owner"].getJsonDict(),
            party_uid=self.__dict__["party_uid"],
            PartyMemberKeeper=self.__dict__["PartyMemberKeeper"].generateJsonDict(),
            PersonKeeper=self.__dict__["PersonKeeper"].generateJsonDict(),
            RatingLimits = self.__dict__["RatingLimits"].generateJsonDict(),
            withBots=self.__dict__["withBots"],
        )
        return { "PartyData": _dct }
    

    def serializeToFile(self, file):
        pass
        file.write("self.afterBattleLockEndTime = " + repr(self.afterBattleLockEndTime) + "\n")
        file.write("self.foes_ready = " + repr(self.foes_ready) + "\n")
        self.ForceLimits.serializeToFile(file, "ForceLimits")
        file.write("self.InMatchmaking = " + repr(self.InMatchmaking) + "\n")
        file.write("self.madeAfterBattle = " + repr(self.madeAfterBattle) + "\n")
        file.write("self.mapID = " + repr(self.mapID) + "\n")
        file.write("self.party_uid = " + repr(self.party_uid) + "\n")
        self.RatingLimits.serializeToFile(file, "RatingLimits")
        file.write("self.withBots = " + repr(self.withBots) + "\n")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
PartyData.initJsonTypes(PartyData)
