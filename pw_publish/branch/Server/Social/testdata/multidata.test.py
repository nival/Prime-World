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
    return model.save()

class MultiDataTest(unittest.TestCase):
  
  def testMultiData( self ):

    helper = TestHelper()
    td = TestData()
    td.init( None )
    td.write( helper )
    td.stop()

    md = ModelData()
    md.init( None )
    md.initAllTimesCounters()
    md.write( helper )
    md.stop()

    td_dict = helper.toJson( td )
    md_dict = helper.toJson( md )
    assert not td_dict == "{}"
    assert not md_dict == "{}"

unittest.main()
