# -*- coding: utf-8 -*-
#!/usr/bin/env python
import sys, time, json

sys.path.append('..')
sys.path.append('../base')
from modeldata.jsonserialize import JSONSerialization
from helpers import *
from modeldata.baseclasses import *

class TestDataCustom( BaseObject ):
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
            
  def write( self, changeWriter ):
    self._modelChangeWriter = changeWriter
    self._writeChanges = (changeWriter is not None)
    
  def stop( self ):
    self._modelChangeWriter = None
    self._writeChanges = False

  # эмулируем доступ к элементу как у словаря, чтобы работал поиск по абсолютным путям
  def get( self, key ):
    return self.__dict__.get(key) 

  # дополнительные (server-side) сериализуемые поля
  def generateBaseDict(self):
    return dict(
      next_uid_ = self.next_uid_
    )
