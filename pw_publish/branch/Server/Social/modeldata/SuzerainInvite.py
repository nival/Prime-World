# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

import sys, os
from base.helpers import addRelPath
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


from SuzerainInvite_base import *

class SuzerainInvite(RefCounted, Identified, ChangeHandler, BaseObject, SuzerainInvite_base):
  _changeFields = {
    "guildAuid":1,
    "guildFullName":1,
    "guildShortName":1,
    "timeToAutoDecline":1,
  } 

  def __init__( self, modeldata, id=None, path=None ):
    ChangeHandler.__init__( self, path, modeldata )
    RefCounted.__init__( self )
    Identified.__init__( self, id )
    _dict = self.__dict__
    _dict["_modeldata"] = modeldata
    _dict["guildAuid"] = 0
    _dict["guildFullName"] = ""
    _dict["guildShortName"] = ""
    _dict["timeToAutoDecline"] = 0
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
    json_dict = SuzerainInvite_base.generateBaseDict(self)
    json_dict['id'] = self.id
    json_dict['path'] = self.path
    json_dict['refCounter'] = self.refCounter
    _dict = self.__dict__
    json_dict["guildAuid"]=_dict.get("guildAuid")
    json_dict["guildFullName"]=_dict.get("guildFullName")
    json_dict["guildShortName"]=_dict.get("guildShortName")
    json_dict["timeToAutoDecline"]=_dict.get("timeToAutoDecline")
    return { "SuzerainInvite": json_dict }

if not hasattr( SuzerainInvite_base, "generateBaseDict" ):
  SuzerainInvite_base.generateBaseDict = generateEmptyDict
