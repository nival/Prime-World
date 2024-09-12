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

class SerializationTest(unittest.TestCase):
  
  def testIntSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.intVal = 1
    root.stop()
    assert root.intVal == 1
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"intVal":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.intVal = -1
    assert root.intVal == -1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"intVal":-1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.intVal = -0
    root.stop()
    assert root.intVal == 0
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"intVal":0}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testFloatSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.floatVal = 1.0
    root.stop()
    assert root.floatVal == 1.0
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"floatVal":1.0}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.floatVal = 0.0
    root.stop()
    assert root.floatVal == 0.0
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"floatVal":0.0}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.floatVal = -1.0
    root.stop()
    assert root.floatVal == -1.0
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"floatVal":-1.0}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testBoolSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.boolVal = True
    root.stop()
    assert root.boolVal == True
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"boolVal":true}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.boolVal = False
    root.stop()
    assert root.boolVal == False
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"boolVal":false}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testEnumSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.enumVal = 0
    root.stop()
    assert root.enumVal == 0
    assert helper.toJson( helper.response ) == '{}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.enumVal = 1
    root.stop()
    assert root.enumVal == 1
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"enumVal":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
  def testAgrValIntSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.agrVal.intVal = 1
    root.stop()
    assert root.agrVal.intVal == 1
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"intVal":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.intVal = -1
    assert root.agrVal.intVal == -1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"intVal":-1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.intVal = -0
    root.stop()
    assert root.agrVal.intVal == 0
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"intVal":0}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testAgrValFloatSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.agrVal.floatVal = 1.0
    root.stop()
    assert root.agrVal.floatVal == 1.0
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"floatVal":1.0}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.agrVal.floatVal = 0.0
    root.stop()
    assert root.agrVal.floatVal == 0.0
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"floatVal":0.0}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.floatVal = -1.0
    root.stop()
    assert root.agrVal.floatVal == -1.0
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"floatVal":-1.0}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testAgrValBoolSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.agrVal.boolVal = True
    root.stop()
    assert root.agrVal.boolVal == True
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"boolVal":true}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.agrVal.boolVal = False
    root.stop()
    assert root.agrVal.boolVal == False
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"boolVal":false}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testAgrValEnumSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.agrVal.enumVal = 0
    root.stop()
    assert root.agrVal.enumVal == 0
    assert helper.toJson( helper.response ) == '{}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.agrVal.enumVal = 1
    root.stop()
    assert root.agrVal.enumVal == 1
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"enumVal":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()


  def testSetSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.setVal.add( keeperTypeID )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["setVal","add",{"1":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.setVal.remove( keeperTypeID )
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["setVal","del",1],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.setVal.add( keeperType )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["setVal","add",{"1":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.setVal.remove( keeperType )
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["setVal","del",1],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()


  def testCollectionSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.collectionVal.add( 3, keeperTypeID )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["collectionVal","add",{"3":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.collectionVal.remove( 3 )
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["collectionVal","del",3],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.collectionVal.add( 12, keeperType )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["collectionVal","add",{"12":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.collectionVal.remove( 12 )
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["collectionVal","del",12],["KeeperVal","del",1]]}]}'

    helper.saveLoadTest( root )
    helper.clearResponse()
    
  def testAgrValSetSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.agrVal.setVal.add( keeperTypeID )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["agrVal\/setVal","add",{"1":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.agrVal.setVal.remove( keeperTypeID )
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal\/setVal","del",1],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.setVal.add( keeperType )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["agrVal\/setVal","add",{"1":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.setVal.remove( keeperType )
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal\/setVal","del",1],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
  def testArgValCollectionSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.agrVal.collectionVal.add( 3, keeperTypeID )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["agrVal\/collectionVal","add",{"3":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.agrVal.collectionVal.remove( 3 )
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal\/collectionVal","del",3],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.collectionVal.add( 12, keeperType )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["agrVal\/collectionVal","add",{"12":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.collectionVal.remove( 12 )
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal\/collectionVal","del",12],["KeeperVal","del",1]]}]}'

    helper.saveLoadTest( root )
    helper.clearResponse()

  def testRefSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.refVal = keeperTypeID
    assert root.refVal == keeperType
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["\/","upd",{"refVal":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.refVal = None
    assert root.refVal == IGuidGenerator.InvalidUID
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"refVal":0}],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.refVal = keeperType
    assert root.refVal == keeperType
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["\/","upd",{"refVal":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.refVal = None
    assert root.refVal == IGuidGenerator.InvalidUID
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["\/","upd",{"refVal":0}],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
  def testAgrRefSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.agrVal.agrRefVal = keeperTypeID
    assert root.agrVal.agrRefVal == keeperType
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["agrVal","upd",{"agrRefVal":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.agrVal.agrRefVal = None
    assert root.agrVal.agrRefVal == IGuidGenerator.InvalidUID
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"agrRefVal":0}],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.agrRefVal = keeperType
    assert root.agrVal.agrRefVal == keeperType
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["agrVal","upd",{"agrRefVal":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.agrVal.agrRefVal = None
    assert root.agrVal.agrRefVal == IGuidGenerator.InvalidUID
    assert keeperType.refCounter == 0
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"agrRefVal":0}],["KeeperVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testAgregatorSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root.agrVal.intVal = 3
    root.agrVal.floatVal = 1.4
    root.agrVal.boolVal = True
    root.stop()
    assert root.agrVal.intVal == 3
    assert root.agrVal.floatVal == 1.4
    assert root.agrVal.boolVal == True
    assert (helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"boolVal":true,"floatVal":1.3999999999999999,"intVal":3}]]}]}') or (helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"boolVal":true,"floatVal":1.4,"intVal":3}]]}]}')
    helper.saveLoadTest( root )
    helper.clearResponse()
    
    root.write( helper )
    root.agrVal.intVal = 2
    root.agrVal.floatVal = 4.5
    root.agrVal.boolVal = False
    root.stop()
    assert root.agrVal.intVal == 2
    assert root.agrVal.floatVal == 4.5
    assert root.agrVal.boolVal == False
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["agrVal","upd",{"boolVal":false,"floatVal":4.5,"intVal":2}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testRefSetCollectionSerialization( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.refVal = keeperTypeID
    assert keeperType.refCounter == 1
    root.setVal.add( root.refVal )
    assert keeperType.refCounter == 2
    root.collectionVal.add( 13, root.refVal )
    assert keeperType.refCounter == 3
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["\/","upd",{"refVal":1}],["setVal","add",{"1":1}],["collectionVal","add",{"13":1}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.setVal.remove( root.refVal )
    assert keeperType.refCounter == 2
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["setVal","del",1]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

    root.write( helper )
    root.collectionVal.remove( root.refVal )
    assert keeperType.refCounter == 1
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["collectionVal","del",13]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()
    
  def testOnlyServerNonSaveVars( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    root._testVarNonSave = 3
    root.stop()
    data = root.save()
    assert data.find( "_testVarNonSave" ) == -1
    assert helper.response == {}
    helper.saveLoadTest( root )
    helper.clearResponse()

  ##DAN: этот тест пока непоправимо сломан
  ## 1) не умеем сериализовать значения, которых нет в шаблоне
  ## 2) не умеем сериализовать по-разному для сервера и для клиента
  #~ def testOnlyServerSaveVars( self ):
    #~ helper = TestHelper()
    #~ root = TestData()
    #~ root.init( None )
    #~ helper.saveLoadTest( root )
    #~ root.write( helper )
    #~ root.testVarSave_ = 3
    #~ root.stop()
    #~ data = root.save()
    #~ assert data.find( "testVarSave_" ) != -1
    #~ assert helper.response == {}
    #~ helper.saveLoadTest( root )
    #~ helper.clearResponse()

  def testKeeperAgrRefIntChange( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.refVal = keeperTypeID
    assert keeperType.refCounter == 1
    root.refVal.keeperAgrVal.intVal = 34
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1}}],["\/","upd",{"refVal":1}],["KeeperVal\/1\/keeperAgrVal","upd",{"intVal":34}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()

  def testKeeperAgrRefRefChange( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    helper.saveLoadTest( root )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    keeperTypeID2 = root.addNewKeeperType()
    keeperType2 = root.getKeeperTypeByID( keeperTypeID2 )
    assert keeperType.refCounter == 0
    root.refVal = keeperTypeID
    assert keeperType.refCounter == 1
    root.refVal.keeperAgrVal.agrRefVal = keeperType2
    root.stop()
    assert helper.toJson( helper.response ) == '{"TestData":[{"auto":[["KeeperVal","add",{"1":{"id":1},"2":{"id":2}}],["\/","upd",{"refVal":1}],["KeeperVal\/1\/keeperAgrVal","upd",{"agrRefVal":2}]]}]}'
    helper.saveLoadTest( root )
    helper.clearResponse()


unittest.main()
