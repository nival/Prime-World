#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json
import unittest

os.chdir('..')
sys.path.append( os.path.abspath('.') )

#~ DEFAULT_LOG_LEVEL = logging.INFO
DEFAULT_LOG_LEVEL = logging.WARNING
#~ DEFAULT_LOG_LEVEL = logging.ERROR

## --------- for sync tests --------------
from base.helpers import *
import modeldata.jsonserialize
from modeldata.changes import PendingChangeWriter, GroupPendingChangeWriter, MakeModelChangeString
from modeldata.change_applicator import ModelChangeApplicator
from subaction import SubAction
##from modeldata.datamanager import PwNewModelManager

from friendsdata.FriendsData import FriendsData

class MainTest(unittest.TestCase):
    def setUp( self ):
        self.md = FriendsData()
        self.md.init( None )
        
        # налаживаем запись pending changes
        self.acc = ClassDict()
        self.acc.pending_changes = []
        self.acc.pending = GroupPendingChangeWriter( self.acc )
        
        # начинаем "под запись"
        self.md.write( self.acc.pending )
        
        self.friend, self.friend_id = self.md.newFriend()
        
        # поля разных типов
        self.friend.online = True
        self.friend.nickName = "nick1"
        self.friend.gender = 2
        
        # пакуем pending changes в response
        self.response = ClassDict()
        SubAction.wrapPendingMessages( self.acc, -1, self.response )
        
    # ------------------------------------------------------------
    # 1) делаем полный экспорт (init)
    def testInit( self ):
        init_model_changes = [ MakeModelChangeString( "comment", "path", "init", self.md.generateJsonDict() ) ]
        acc1 = ClassDict()
        ModelChangeApplicator.apply( acc1, "friendsdata", FriendsData, init_model_changes )
        
        md1 = acc1.friendsdata
        self.assert_( md1 )
        self.assert_( md1.FriendsKeeper and len(md1.FriendsKeeper) == 1)
        friend1 = md1.FriendsKeeper.get( self.friend_id )
        self.assert_( friend1 )
        self.assert_( friend1.online == True )
        self.assert_( friend1.nickName == "nick1" )
        self.assert_( friend1.gender == 2 )


    # ------------------------------------------------------------
    # 2) применяем накопленные model changes
    def testModelChanges( self ):
        acc2 = ClassDict()
        acc2.friendsdata = FriendsData()
        acc2.friendsdata.init( None )
        info("acc.pending_changes: %s" % self.acc.pending_changes)
        info("response.FriendsData model changes: %s" % self.response.FriendsData)
        ModelChangeApplicator.apply( acc2, "friendsdata", FriendsData, self.response.FriendsData )
        
        md1 = acc2.friendsdata
        self.assert_( md1 )
        self.assert_( md1.FriendsKeeper and (len(md1.FriendsKeeper) == 1) )
        friend1 = md1.FriendsKeeper.get( self.friend_id )
        self.assert_( friend1 )
        self.assert_( friend1.online == True )
        self.assert_( friend1.nickName == "nick1" )
        self.assert_( friend1.gender == 2 )
        
    
    # ------------------------------------------------------------
    # (применяем накопленные model changes)
    def testDelete( self ):
        acc2 = ClassDict()
        acc2.friendsdata = FriendsData()
        acc2.friendsdata.init( None )
        info("acc.pending_changes: %s" % self.acc.pending_changes)
        info("response.FriendsData model changes: %s" % self.response.FriendsData)
        ModelChangeApplicator.apply( acc2, "friendsdata", FriendsData, self.response.FriendsData )

        acc2 = ClassDict()
        acc2.friendsdata = FriendsData()
        acc2.friendsdata.init( None )
        info("acc.pending_changes: %s" % self.acc.pending_changes)
        info("response.FriendsData model changes: %s" % self.response.FriendsData)
        ModelChangeApplicator.apply( acc2, "friendsdata", FriendsData, self.response.FriendsData )
        
        md1 = acc2.friendsdata
        self.assert_( md1 )
        self.assert_( md1.FriendsKeeper and len(md1.FriendsKeeper) == 1)
        friend1 = md1.FriendsKeeper.get( self.friend_id )
        self.assert_( friend1 )
        self.assert_( friend1.online == True )
        self.assert_( friend1.nickName == "nick1" )
        self.assert_( friend1.gender == 2 )

        # ----------------------------------------------
        self.acc.pending_changes = []
        self.md.deleteByID( self.friend_id )
        # пакуем pending changes в response
        self.response = ClassDict()
        SubAction.wrapPendingMessages( self.acc, -1, self.response )
        # ----------------------------------------------

        info("(del) acc.pending_changes: %s" % self.acc.pending_changes)
        info("(del) response.FriendsData model changes: %s" % self.response.FriendsData)
        ModelChangeApplicator.apply( acc2, "friendsdata", FriendsData, self.response.FriendsData )
        
        self.assert_( md1 )
        ##info("(del) len(md1.FriendsKeeper): %s" % len(md1.FriendsKeeper))
        self.assert_( len(md1.FriendsKeeper) == 0 )
        friend1 = md1.FriendsKeeper.get( self.friend_id )
        self.assert_( friend1 is None )
        

def main():
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    info( "Starting tests..." )
    
    ITERATIONS = 1
    for i in range(ITERATIONS):
        try:
            unittest.main()
        except SystemExit:
            if str( exc() ) == "True":
                sys.exit(1)
        except:
            catch()
            
        #time.sleep(0.01)

    info( "-- Finish tests (x %d)." % ITERATIONS )
    

if __name__ == "__main__":
    main()
