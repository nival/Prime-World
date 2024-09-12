# -*- coding: utf-8 -*-
#automatically generated file. do not modify it!!!

#!/usr/bin/env python
import sys, os
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

realpath = os.path.dirname( __file__ )
modeldatapath = os.path.join(realpath, "../modeldata")
sys.path.append(modeldatapath)
sharedtypespath = os.path.join(realpath, "../modeldata/SharedTypes")
sys.path.append(sharedtypespath)


from Person_base import *

class Person(RefCounted, Identified, ChangeHandler, BaseObject, Person_base):
  _changeFields = {
    "fame":1,
    "fraction":1,
    "gender":1,
    "InMatchmaking":1,
    "lastLoginTime":1,
    "nickName":1,
    "online":1,
    "person_uid":1,
    "photoUrl":1,
    "Status":1,
  } 

  def __init__( self, modeldata, id=None, path=None ):
    ChangeHandler.__init__( self, path, modeldata )
    RefCounted.__init__( self )
    Identified.__init__( self, id )
    _dict = self.__dict__
    _dict["_modeldata"] = modeldata
    _dict["fame"] = 0
    _dict["fraction"] = 2
    _dict["gender"] = 0
    _dict["InMatchmaking"] = False
    _dict["lastLoginTime"] = 0
    _dict["nickName"] = ""
    _dict["online"] = False
    _dict["person_uid"] = 0
    _dict["photoUrl"] = ""
    _dict["Status"] = 0
    _dict["isDeleting"] = False

  # вызывается во всех случаях кроме model.addNewName() -- например, в keeper.init() после загрузки
  def init( self ):
    pass
  
  # вызывается после model.addNewName()
  def init_add( self ):
    pass
    
  def setPath( self, path ):
    ChangeHandler.init( self, path, self._modeldata )
  
  def deleteByID( self, id ):
    if not self.isDeleting:
      self.isDeleting = True
      self.isDeleting = False

  def __setattr__( self, name, val ):
    ChangeHandler.__setattr__( self, name, val )
    
  def generateJsonDict( self ):
    json_dict = Person_base.generateBaseDict(self)
    json_dict['id'] = self.id
    json_dict['path'] = self.path
    json_dict['refCounter'] = self.refCounter
    _dict = self.__dict__
    json_dict["fame"]=_dict.get("fame")
    json_dict["fraction"]=_dict.get("fraction")
    json_dict["gender"]=_dict.get("gender")
    json_dict["InMatchmaking"]=_dict.get("InMatchmaking")
    json_dict["lastLoginTime"]=_dict.get("lastLoginTime")
    json_dict["nickName"]=_dict.get("nickName")
    json_dict["online"]=_dict.get("online")
    json_dict["person_uid"]=_dict.get("person_uid")
    json_dict["photoUrl"]=_dict.get("photoUrl")
    json_dict["Status"]=_dict.get("Status")
    return { "Person": json_dict }

if not hasattr( Person_base, "generateBaseDict" ):
  Person_base.generateBaseDict = generateEmptyDict
