# -*- coding: utf-8 -*-
#!/usr/bin/env python

import sys, os, time, logging, unittest

sys.path.append('..')
sys.path.append('../base')
sys.path.append('../cfg')
from TestData import *
import modeldata.jsonserialize
from base.helpers import * 
from subaction import *

class TestHelper( SubAction ):
  def __init__( self ):
    self.response = {}
    self._serializator = JSONSerialization( None )
    
  def clearResponse( self ):
    self.response = {}

  def toJson(self, save_data, forClient=False):
    self._serializator.setMode( forClient )
    if isinstance( save_data, dict ):
      for key in save_data:
        if isinstance( save_data[key], ResponseObject ):
          save_data[key] = save_data[key].makeDict()
    return json_dumps( save_data )

  def saveLoadTest( self, root ):
    data = root.save()

    result = TestData()
    result.load( data )
    result.init( None )

    data2 = result.save()
    assert data == data2

class SimpleListTest(unittest.TestCase):
  
  def testSimpleList( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    root.write( helper )
    root.heroesNames.append("Abra")
    root.stop()
    assert root.heroesNames[0] == "Abra"
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["heroesNames","push","Abra"]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    assert root.heroesNames[0] == "Abra"
    root.heroesNames[0] = "Trax"
    root.stop()
    assert root.heroesNames[0] == "Trax"
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["heroesNames","upd",{"0":"Trax"}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    assert root.heroesNames[0] == "Trax"
    root.heroesNames.append( "Abra" )
    assert root.heroesNames.pop() == "Abra"
    root.stop()
    assert len(root.heroesNames) == 1
    assert root.heroesNames[0] == "Trax"
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["heroesNames","push","Abra"],["heroesNames","del","Abra"]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    assert root.heroesNames[0] == "Trax"
    root.heroesNames.append( "Abra" )
    del root.heroesNames[0]
    root.stop()
    assert len(root.heroesNames) == 1
    assert root.heroesNames[0] == "Abra"
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["heroesNames","push","Abra"],["heroesNames","del","Trax"]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    

unittest.main()
