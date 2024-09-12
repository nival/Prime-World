# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import AgregatorType
import KeeperType
import ResourceTable
import SimpleObject

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from TestDataCustom import TestDataCustom

class TestData(ChangeHandler, TestDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "boolVal":1,
        "doubleVal":1,
        "enumVal":1,
        "floatVal":1,
        "heroesNames":1,
        "intVal":1,
        "longVal":1,
        "refVal":1,
        "removedDefaultTalents":1,
        "simpleObjects":1,
        "stringToIntDict":1,
        "stringVal":1,
    } 


    def __init__(self):
        TestDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["KeeperVal"] = Keeper(self)
        self.__dict__["agrVal"] = AgregatorType.AgregatorType(self)
        self.__dict__["boolVal"] = False
        self.__dict__["collectionVal"] = Collection(self)
        self.__dict__["doubleVal"] = 0.0
        self.__dict__["enumVal"] = 0
        self.__dict__["floatVal"] = 0.0
        self.__dict__["heroesNames"] = SimpleList(self)
        self.__dict__["intVal"] = 0
        self.__dict__["longVal"] = 0
        self.__dict__["refVal"] = Ref(self)
        self.__dict__["removedDefaultTalents"] = SimpleList(self)
        self.__dict__["resources"] = ResourceTable.ResourceTable(self)
        self.__dict__["setVal"] = Set(self)
        self.__dict__["simpleObjects"] = SimpleList(self)
        self.__dict__["stringToIntDict"] = SimpleDict(self)
        self.__dict__["stringVal"] = ""


    def init(self, changeWriter):
        self.write(changeWriter)
        self.KeeperVal.init(u"KeeperVal", self, "KeeperType")
        self.agrVal.setPath(u"agrVal")
        self.collectionVal.init(self.KeeperVal, u"collectionVal", self)
        self.heroesNames.init(u"heroesNames", self)
        self.refVal.init(self.KeeperVal, u"/", self, "refVal")
        self.removedDefaultTalents.init(u"removedDefaultTalents", self)
        self.resources.setPath(u"resources")
        self.setVal.init(self.KeeperVal, u"setVal", self)
        self.simpleObjects.init(u"simpleObjects", self)
        self.stringToIntDict.init(u"stringToIntDict", self)


    @staticmethod
    def initJsonTypes(TCustomTestData): # конечный класс CustomTestData будет передавать снаружи, из datamanager
        if "TestData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomTestData,
            AgregatorType.AgregatorType,
            KeeperType.KeeperType,
            ResourceTable.ResourceTable,
            SimpleObject.SimpleObject,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "TestData" : TCustomTestData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "AgregatorType" : AgregatorType.AgregatorType
            , "KeeperType" : KeeperType.KeeperType
            , "ResourceTable" : ResourceTable.ResourceTable
            , "SimpleObject" : SimpleObject.SimpleObject
            })  
        else:
            err("TestData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewKeeperType(self):
        uid = self.nextGUID()
        var = KeeperType.KeeperType(self, uid, "KeeperVal/"+str(uid))
        var.init_add()
        self.KeeperVal.add(uid, var)
        return uid


    def getKeeperTypeByID(self, id):
        return self.KeeperVal.get(id)


    def newKeeperType(self):
        _id = self.addNewKeeperType()
        _data = self.getKeeperTypeByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.agrVal.deleteByID(id)
        self.collectionVal.deleteByID(id)
        self.heroesNames.deleteByID(id)
        self.refVal.deleteByID(id)
        self.removedDefaultTalents.deleteByID(id)
        self.resources.deleteByID(id)
        self.setVal.deleteByID(id)
        self.simpleObjects.deleteByID(id)
        self.stringToIntDict.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.KeeperVal.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        KeeperType = self.getKeeperTypeByID(id)
        if KeeperType:
            obj = KeeperType
        return obj


    def __setattr__(self, name, val):
        if name == "refVal":
            self.__dict__["refVal"].set(val)
            return    
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = TestDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            agrVal = self.__dict__["agrVal"].generateJsonDict(),
            boolVal=self.__dict__["boolVal"],
            collectionVal=self.__dict__["collectionVal"].getJsonDict(),
            doubleVal=self.__dict__["doubleVal"],
            enumVal=self.__dict__["enumVal"],
            floatVal=self.__dict__["floatVal"],
            heroesNames=self.__dict__["heroesNames"].getJsonDict(),
            intVal=self.__dict__["intVal"],
            KeeperVal=self.__dict__["KeeperVal"].generateJsonDict(),
            longVal=self.__dict__["longVal"],
            refVal=self.__dict__["refVal"].getJsonDict(),
            removedDefaultTalents=self.__dict__["removedDefaultTalents"].getJsonDict(),
            resources = self.__dict__["resources"].generateJsonDict(),
            setVal=self.__dict__["setVal"].getJsonDict(),
            simpleObjects=self.__dict__["simpleObjects"].getJsonDict(),
            stringToIntDict=self.__dict__["stringToIntDict"].getJsonDict(),
            stringVal=self.__dict__["stringVal"],
        )
        return { "TestData": _dct }
    

    def serializeToFile(self, file):
        pass
        self.agrVal.serializeToFile(file, "agrVal")
        file.write("self.boolVal = " + repr(self.boolVal) + "\n")
        file.write("self.doubleVal = " + repr(self.doubleVal) + "\n")
        file.write("self.enumVal = " + repr(self.enumVal) + "\n")
        file.write("self.floatVal = " + repr(self.floatVal) + "\n")
        self.heroesNames.serializeToFile(file, "heroesNames")
        file.write("self.intVal = " + repr(self.intVal) + "\n")
        file.write("self.longVal = " + repr(self.longVal) + "\n")
        self.removedDefaultTalents.serializeToFile(file, "removedDefaultTalents")
        self.resources.serializeToFile(file, "resources")
        self.simpleObjects.serializeToFile(file, "simpleObjects")
        self.stringToIntDict.serializeToFile(file, "stringToIntDict")
        file.write("self.stringVal = " + repr(self.stringVal) + "\n")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
TestData.initJsonTypes(TestData)
