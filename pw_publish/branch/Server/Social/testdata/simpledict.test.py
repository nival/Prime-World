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

class SimpleDictTest(unittest.TestCase):
  
  def testSimpleDict( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    root.write( helper )
    root.stringToIntDict.add( "Lofik", 10 )
    root.stop()
    assert root.stringToIntDict["Lofik"] == 10
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["stringToIntDict","add",{"Lofik":10}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    assert root.stringToIntDict["Lofik"] == 10
    root.stringToIntDict["Lofik"] = 12
    root.stop()
    assert root.stringToIntDict["Lofik"] == 12
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["stringToIntDict","upd",{"Lofik":12}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    assert root.stringToIntDict["Lofik"] == 12
    root.stringToIntDict.add( "Movsya", 7 )
    root.stringToIntDict.remove( "Movsya" )
    root.stop()
    assert len(root.stringToIntDict) == 1
    assert root.stringToIntDict["Lofik"] == 12
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["stringToIntDict","add",{"Movsya":7}],["stringToIntDict","del","Movsya"]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    assert root.stringToIntDict["Lofik"] == 12
    root.stringToIntDict.add( "Aya", 5 )
    del root.stringToIntDict["Aya"]
    root.stop()
    assert len(root.stringToIntDict) == 1
    assert root.stringToIntDict["Lofik"] == 12
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["stringToIntDict","add",{"Aya":5}],["stringToIntDict","del","Aya"]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    

unittest.main()
