# -*- coding: utf-8 -*-
#!/usr/bin/env python

import sys, os, time, logging, unittest

sys.path.append('..')
sys.path.append('../base')
sys.path.append('../cfg')
from PartyData import *
import modeldata.jsonserialize
from base.helpers import * 

class MainTest(unittest.TestCase):

    def testMain( self ):
        changeWriter = None # DummyRequestWriter()
        changeWriterOff = None # DummyRequestWriter( "NONE: TURNED OFF " )
        pd = PartyData( )
        pd.init( changeWriter )
        partyId = pd.addNewPartyMember()
        party = pd.getPartyMemberByID( partyId )
        party.partyName = "My party"

        assert pd.owner.isValid() == False

        pd.owner = party
        assert pd.owner.isValid() == True
        assert pd.owner.partyName == "My party"
        assert pd.owner.refCounter == 1
        pd.members.add( pd.owner )
        assert pd.owner.refCounter == 2

        data = pd.save()
        #print "raw:", data
    
        result = PartyData()
        result.load( data )
        result.init( changeWriter )

        data2 = result.save()
        #print "dat:", data2
        assert data == data2
        pd.owner = None
        assert pd.owner.isValid() == False
        assert party.refCounter == 1

    def testDelete( self ):
        changeWriter = None # DummyRequestWriter()
        changeWriterOff = None # DummyRequestWriter( "NONE: TURNED OFF " )
        pd = PartyData( )
        pd.init( changeWriter )
        partyId = pd.addNewPartyMember()
        party = pd.getPartyMemberByID( partyId )
        party.partyName = "My party"
        pd.owner = party
        pd.members.add( pd.owner )
        
        partyId2 = pd.addNewPartyMember()
        party2 = pd.getPartyMemberByID( partyId2 )
        pd.members.add( party2 )

        personId = pd.addNewFriend()
        person = pd.getFriendByID( personId )

        partyMemberId = pd.addNewPartyMember()
        partyMember = pd.getPartyMemberByID( partyMemberId )
        partyMember.person = person
        
        pd.members.add( partyMember )

        # delete
        pd.deleteByID( party.id )
        assert party.refCounter == 0
 
        data = pd.save()
        #print "raw:", data
    
        result = PartyData()
        result.load( data )
        result.init( changeWriter )

        data2 = result.save()
        #print "dat:", data2
        assert data == data2

    def testDelete2( self ):
        changeWriter = None # DummyRequestWriter()
        changeWriterOff = None # DummyRequestWriter( "NONE: TURNED OFF " )
        pd = PartyData( )
        pd.init( changeWriter )
        partyId = pd.addNewPartyMember()
        party = pd.getPartyMemberByID( partyId )
        party.partyName = "My party"
        pd.owner = party
        pd.members.add( party )
        
        partyId2 = pd.addNewPartyMember()
        party2 = pd.getPartyMemberByID( partyId2 )
        pd.members.add( party2 )

        personId = pd.addNewFriend()
        person = pd.getFriendByID( personId )

        partyMemberId = pd.addNewPartyMember()
        partyMember = pd.getPartyMemberByID( partyMemberId )
        partyMember.person = person
        
        pd.members.add( partyMember )

        # delete
        pd.deleteByID( personId )
        assert person.refCounter == 0
 
        data = pd.save()
        #print "raw:", data
    
        result = PartyData()
        result.load( data )
        result.init( changeWriter )

        data2 = result.save()
        #print "dat:", data2
        assert data == data2

unittest.main()
