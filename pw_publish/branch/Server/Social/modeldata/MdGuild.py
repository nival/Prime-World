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


from MdGuild_base import *

class MdGuild(RefCounted, Identified, ChangeHandler, BaseObject, MdGuild_base):
  _changeFields = {
    "Experience":1,
  } 

  def __init__( self, modeldata, id=None, path=None ):
    ChangeHandler.__init__( self, path, modeldata )
    RefCounted.__init__( self )
    Identified.__init__( self, id )
    _dict = self.__dict__
    _dict["_modeldata"] = modeldata
    _dict["Experience"] = -1
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
    json_dict = MdGuild_base.generateBaseDict(self)
    json_dict['id'] = self.id
    json_dict['path'] = self.path
    json_dict['refCounter'] = self.refCounter
    _dict = self.__dict__
    json_dict["Experience"]=_dict.get("Experience")
    return { "MdGuild": json_dict }

if not hasattr( MdGuild_base, "generateBaseDict" ):
  MdGuild_base.generateBaseDict = generateEmptyDict
