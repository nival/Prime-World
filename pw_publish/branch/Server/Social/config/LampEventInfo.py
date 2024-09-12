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


from LampEventInfo_base import *

class LampEventInfo(RefCounted, Identified, ChangeHandler, BaseObject, LampEventInfo_base):
  _changeFields = {
    "BonusGold":1,
    "Duration":1,
    "Transactions":1,
  } 

  def __init__( self, modeldata, id=None, path=None ):
    ChangeHandler.__init__( self, path, modeldata )
    RefCounted.__init__( self )
    Identified.__init__( self, id )
    _dict = self.__dict__
    _dict["_modeldata"] = modeldata
    _dict["BonusGold"] = 2000
    _dict["Duration"] = 86400
    _dict["Transactions"] = 1
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
    json_dict = LampEventInfo_base.generateBaseDict(self)
    json_dict['id'] = self.id
    json_dict['path'] = self.path
    json_dict['refCounter'] = self.refCounter
    _dict = self.__dict__
    json_dict["BonusGold"]=_dict.get("BonusGold")
    json_dict["Duration"]=_dict.get("Duration")
    json_dict["Transactions"]=_dict.get("Transactions")
    return { "LampEventInfo": json_dict }

if not hasattr( LampEventInfo_base, "generateBaseDict" ):
  LampEventInfo_base.generateBaseDict = generateEmptyDict
