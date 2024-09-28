# -*- coding: utf-8 -*-
#automatically generated file. do not modify it!!!

#!/usr/bin/env python
import sys
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *

from PartyMember import *

from Party_base import *

class Party(RefCounted, Identified, ChangeHandler, BaseObject, Party_base):
  _changeFields = {
    "owner":1,
    "party_uid":1,
  } 

  def __init__( self, modeldata, id=None, path=None ):
    RefCounted.__init__( self )
    Identified.__init__( self, id )
    ChangeHandler.__init__( self, path, modeldata )
    self.__dict__["_modeldata"] = modeldata
    self.__dict__["members"] = Set( modeldata )
    self.__dict__["owner"] = Ref( modeldata )
    self.__dict__["party_uid"] = 0

  def init( self ):
    ChangeHandler.__init__( self, self.path, self._modeldata )
    self.members.init( self._modeldata.PartyMemberKeeper, self.path + u"/members", self._modeldata )
    self.owner.init( self._modeldata.PartyMemberKeeper, self.path + u"/owner", self._modeldata )
  
  def setPath( self, path ):
    ChangeHandler.__init__( self, path, self._modeldata )
  
  def deleteByID( self, id ):
    self.members.deleteByID( id )
    self.owner.deleteByID( id )
    pass

  def __setattr__( self, name, val ):
    if name == "owner":
      self.__dict__["owner"].set( val )
      return
    ChangeHandler.__setattr__( self, name, val )