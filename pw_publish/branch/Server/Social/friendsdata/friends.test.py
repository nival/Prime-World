#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import unittest

sys.path.append('..')
sys.path.append('../cfg')
from FriendsData import *
import modeldata.jsonserialize

class MainTest(unittest.TestCase):
    def testMain( self ):
        changeWriter = None # DummyRequestWriter()
        changeWriterOff = None # DummyRequestWriter( "NONE: TURNED OFF " )

        fd = FriendsData( )
        fd.init( changeWriter )
        fd.testVal = 3

        #---------------------------------------------------
        # временно отключаем генерацию model change 
        # (например, для добавления служебного поля, или для добавления целого большого объекта, который обновим руками, через сериализацию)
        fd.write( changeWriterOff )

        del fd.testVal

        # включаем обратно генерацию model change 
        fd.write( changeWriter )

        fd.testVal = 5

        data = fd.save()
        #print "raw:", data
    
        result = FriendsData()
        result.load( data )
        result.init( changeWriter )
        result.testVal = 11

        data2 = result.save()
        #print data2

unittest.main()
