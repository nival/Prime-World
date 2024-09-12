#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, time, os
import unittest

os.chdir('..')
sys.path.append( os.path.abspath('cfg') )
sys.path.append( os.path.abspath('.') )

from ext_main.login import LoginAction
from ext_main.auth import AuthAction
from ext_pw import *

import cfg, coord_cfg # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора

from base.helpers import *
from binascii import crc32 
from modeldata.ModelData import ModelData
from modeldata.MultiStaticData import MultiStaticData

import logging
logging.basicConfig( level=logging.INFO, format="[%(asctime)s %(levelname)8s] %(message)s" )

class StaticDataTest( unittest.TestCase ):

  SD = MultiStaticData( "./xdb/ExportedSocialData.xml", None ).getMainSD()

  def testSocialRootInDbids( self ):
    assert( "/Social.ROOT" in self.SD.dbid )
    
  def testLampEventRollSelect( self ):
    assert( self.SD.getGoldLampRollContainer( 3651 ) == "/Items/Coupon/GoldLamp_High.ROLLCONT" )
    assert( self.SD.getGoldLampRollContainer( 3650 ) == "/Items/Coupon/GoldLamp_High.ROLLCONT" )
    assert( self.SD.getGoldLampRollContainer( 3649 ) == "/Items/Coupon/GoldLamp_Mid.ROLLCONT" )
    assert( self.SD.getGoldLampRollContainer( 0 ) == "/Items/Coupon/GoldLamp_Low.ROLLCONT" )
    
  def testFillMarketingEventRollItem( self ):
    item = self.SD.dbid['/Items/Coupon/GoldLamp_20.ROLLITEM']
    assert( self.SD.getMarketingEventRollItem( crc32( 'GoldLampItem_20' ) ) == item )
    
  def testGetMarketingEventRollItemReturnsNull( self ):
    assert( self.SD.getMarketingEventRollItem( crc32( 'blah-blah-blah' ) ) == None )

  def testGetTurnamentSettings( self ):
    item = self.SD.getStaticMap( '/Maps/Multiplayer/CTE/PVP.ADMPDSCR')
    assert(item )

if __name__ == "__main__":
  unittest.main() 