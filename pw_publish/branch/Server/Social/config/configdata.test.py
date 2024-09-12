#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os
sys.path.append(os.path.abspath('..'))
sys.path.append(os.path.abspath('../cfg'))
from base.helpers import *

import unittest

from ConfigData import *

class StringStream:
  def __init__( self ):
    self.stringdata = ""

  def write( self, str ):
    self.stringdata += str

  def __eq__( self, other ):
    return self.stringdata == other.stringdata

  def getString( self ):
    return self.stringdata


class MainTest(unittest.TestCase):
  def testMain( self ):
    config = ConfigData( )
    config.init( None )
    config.create()
    strstream = StringStream()
    config.serializeToFile( strstream )

    config = ConfigData( )
    config.init( None )
    config.createFromString( strstream.getString() )
    newstream = StringStream()
    config.serializeToFile( newstream )

    assert strstream == newstream

if __name__ == "__main__":
    unittest.main()
else:
    print "ERROR: %s shouldn't be imported!" % __file__
