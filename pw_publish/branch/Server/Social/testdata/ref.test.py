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
    
  def toJson(self, save_data, forClient=True):
    return json_dumps( save_data )

class RefTest(unittest.TestCase):
  
  def testRefEqual( self ):
    helper = TestHelper()
    root = TestData()
    root.init( None )
    root.write( helper )
    keeperTypeID = root.addNewKeeperType()
    keeperType = root.getKeeperTypeByID( keeperTypeID )
    assert keeperType.refCounter == 0
    root.refVal = keeperTypeID
    root.stop()
    assert root.refVal == keeperType
    assert root.refVal == keeperTypeID
    assert not root.refVal == 34
    assert keeperType.refCounter == 1

unittest.main()
