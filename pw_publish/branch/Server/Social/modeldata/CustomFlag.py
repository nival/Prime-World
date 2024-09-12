# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from CustomFlag_base import *

class CustomFlag(RefCounted, Identified, ChangeHandler, BaseObject, CustomFlag_base):
  _changeFields = {
    "FlagName":1,
    "Icon":1,
    "Price":1,
    "Tooltip":1,
  } 

  def __init__( self, modeldata, id=None, path=None ):
    ChangeHandler.__init__( self, path, modeldata )
    RefCounted.__init__( self )
    Identified.__init__( self, id )
    _dict = self.__dict__
    _dict["_modeldata"] = modeldata
    _dict["FlagName"] = ""
    _dict["Icon"] = ""
    _dict["Price"] = 0
    _dict["Tooltip"] = ""
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
    if name not in self.__dict__ or  val != self.__dict__[name]:
      ChangeHandler.__setattr__( self, name, val )
    
    
  def generateJsonDict( self ):
    json_dict = CustomFlag_base.generateBaseDict(self)
    json_dict['id'] = self.id
    json_dict['path'] = self.path
    json_dict['refCounter'] = self.refCounter
    _dict = self.__dict__
    json_dict["FlagName"]=_dict.get("FlagName")
    json_dict["Icon"]=_dict.get("Icon")
    json_dict["Price"]=_dict.get("Price")
    json_dict["Tooltip"]=_dict.get("Tooltip")
    return { "CustomFlag": json_dict }

if not hasattr( CustomFlag_base, "generateBaseDict" ):
  CustomFlag_base.generateBaseDict = generateEmptyDict
