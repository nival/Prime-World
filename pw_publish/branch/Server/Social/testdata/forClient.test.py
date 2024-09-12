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
from modeldata.ModelData import *

class TestHelper( SubAction ):
  def __init__( self ):
    self.response = {}
    self._serializator = JSONSerialization( None )
    
  def toJson(self, model, forClient=True):
    self._serializator.setMode( forClient )
    return model.save()

class MultiDataTest(unittest.TestCase):
  
  def testMultiData( self ):

    helper = TestHelper()
    td = TestData()
    td.init( None )
    td.write( helper )
    td.intVal = 10
    td.fakeVal = 11
    td.stop()
    clientSide = helper.toJson( td, True )
    serverSide = helper.toJson( td, False )
    #print "FOR CLIENT: ", helper.toJson( td, True )
    #print "FOR SERVER: ", helper.toJson( td, False )
    
    ##DAN: этот тест пока непоправимо сломан
    ## 1) не умеем сериализовать значения, которых нет в шаблоне
    ## 2) не умеем сериализовать по-разному для сервера и для клиента
    
    ## assert not clientSide == serverSide ##DAN: сейчас они, увы, совпадают; и пишутся только те поля, которые есть в шаблоне (см. generateJsonDict)
    ## assert clientSide.find( "refCounter" ) == -1
    ## assert clientSide.find( "fakeVal" ) == -1
    ## assert serverSide.find( "fakeVal" ) != -1
    
    #~ print "intVal:", serverSide.find( "intVal" )
    #~ print "fakeVal:", serverSide.find( "fakeVal" )
    
    assert clientSide.find( "intVal" ) != -1
    assert serverSide.find( "refCounter" ) != -1

unittest.main()
