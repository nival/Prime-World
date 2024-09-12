# -*- coding: utf-8 -*-
import urllib, hashlib, sys, time

import logging
from logging import debug, info, warning

from context import *
import operator

sys.path.append('../../')
import party_const
from party_fsm import FIRST_HERO_CRC
from base.helpers import *

class PartyUserContext( UserContext ):
    
    CLIENT_PARTY_CMD_HANDLERS = {
        'invite':   'OnPartyInvite', 
        'invited':  'OnPartyInviteDelivered', 
        'error':    'OnPartyCmdError',
        
        # master/member events
        'join':         'OnUserJoined', 
        'remove_invite':'OnUserDeclined',
        'disband':      'OnUserDisbanded',
        'hero':         'OnUserChooseHero',
        'go':           'OnUserPartyGo',
        
        # invited/kicked client events
        'join_init': 'OnAcceptSuccess', 
        'invite_removed': 'OnDeclineSuccess',
        'disbanded': 'OnDisbandSuccess',
    }
    
    def __init__( self, proxy, tag, ping_wait=0, **kwargs ):
        UserContext.__init__( self, proxy, **kwargs )
        self.tag = tag
        self.auid = 0
        self.ping_wait = ping_wait
        self.invites_delivered = []
        self.invites_received = []
        self.choose_heroes_left = []
        
    # ------------------------------------------------
    def PartyInvite(self, invite_auid):
        args =  {
            'action' : 'party_invite',
            'invite_auid': invite_auid,
            # --------------------------
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.party_response = 0
        self.send(args, self.OnPartyResponse)

    def PartyAccept(self, master_auid):
        args =  {
            'action' : 'party_accept',
            'master_auid': master_auid,
            # --------------------------
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.party_response = 0
        self.send(args, self.OnPartyResponse)
        
    def PartyDecline(self, master_auid):
        args =  {
            'action' : 'party_decline',
            'master_auid': master_auid,
            # --------------------------
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.party_response = 0
        self.send(args, self.OnPartyResponse)

    def PartyDisband(self):
        args =  {
            'action' : 'party_disband',
            'master_auid': self.master_auid,
            # --------------------------
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.party_response = 0
        self.send(args, self.OnPartyResponse)
        
    def PartyKick(self, kick_auid):
        try:
            args =  {
                'action' : 'party_kick',
                'master_auid': self.master_auid,
                'kick_auid': kick_auid,
                # --------------------------
                'uid' : self.uid,
                'key' : self.key,
                'pretty' : 1,
            }
            self.party_response = 0
            self.send(args, self.OnPartyResponse)
        except:
            warning( traceback.format_exc() )
    
    def PartyHero(self, hero_id=0, hero_crc=0): # crc32('assassin'))
        args =  {
            'action' : 'party_hero',
            'master_auid': self.master_auid,
            'hero_id': hero_id,
            'hero_crc': hero_crc, 
            # --------------------------
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.party_response = 0
        self.send(args, self.OnPartyResponse)
        
    def PartyGo(self, game_type="pvp"):
        args =  {
            'action' : 'party_go',
            'master_auid': self.master_auid,
            'game_type': game_type,
            # --------------------------
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.party_response = 0
        self.send(args, self.OnPartyResponse)
        
    def OnPartyResponse(self, data):
        assert data['response']['ok']
        self.party_response = 1

    # ------------------------------------------------
    def PartyPing(self):
        args =  {
            'action' : 'ping',
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
            'wait' : 0,
        }
        self.party_response = 0
        self.send(args, self.OnPartyPing)

    def OnPartyPing(self, data):
        assert data['response']['ok']
        self.data = data
        pending_events = data['response'].get( "pending_events" )
        if pending_events:
            for event_dict in pending_events:
                if event_dict: 
                    party_event = event_dict.get('party')
                    if party_event:
                        cmd = party_event.get('cmd')
                        if cmd in self.CLIENT_PARTY_CMD_HANDLERS:
                            method = getattr(self, self.CLIENT_PARTY_CMD_HANDLERS[cmd], None)
                            assert method
                            method( ClassDict(party_event) )
                    
    # ------------------------------------------------
    # ------------------------------------------------
            
    def OnPartyInvite(self, party_event):
        info( party_event )
        
        auid = toint( party_event.get('master_auid') )
        if auid:
            info( '%s on INVITE RECEIVED: from %d' % (self.tag, auid) )
            self.invites_received.append( auid )
            
            
    def OnPartyInviteDelivered(self, party_event):
        info( party_event )
        
        assert operator.isNumberType( party_event.msg_id ) and party_event.msg_id
        assert party_event.cmd == "invited"
        assert operator.isNumberType( party_event.invite_auid ) and party_event.invite_auid
        assert operator.isNumberType( party_event.party_id ) and party_event.party_id 
        assert party_event.action == "server_party"
        assert party_event.message == "ok"
        
        auid = toint( party_event.get('invite_auid') )
        if auid:
            info( '%s on INVITE DELIVERED: %d' % (self.tag, auid) )
            self.invites_delivered.append( auid )
            
        self.party_id = toint(party_event.party_id) # пригласили юзера в нашу партию, значит мы мастер партии (возможно, временной)
            
    # ---------------------------------------------------------------------------
            
    def OnUserJoined(self, party_event):
        info( party_event )
        master_auid = party_event.master_auid
        if self.auid == master_auid:
            # это мы мастер 
            self.master_auid = master_auid
            join_auid = party_event.join_auid
            warning( '%s on USER JOINED: %d' % (self.tag, join_auid) )
            
            self.invite_replies_left.remove( join_auid )
            
    def OnUserDeclined(self, party_event):
        info( party_event )
        master_auid = party_event.master_auid
        if self.auid == master_auid:
            # это мы мастер 
            invite_auid = toint( party_event.invite_auid )
            info( '%s on USER DECLINED: %d' % (self.tag, invite_auid) )
            self.invite_replies_left.remove( invite_auid )
            
    def OnUserDisbanded(self, party_event):
        info( party_event )
        master_auid = party_event.master_auid
        info( '%s OnUserDisbanded: self.auid %s, master_auid %s' % (self.tag, self.auid, master_auid) )
        if self.auid == master_auid:
            # это мы мастер 
            disband_auid = toint( party_event.disband_auid )
            warning( '%s on USER DISBANDED: %d' % (self.tag, disband_auid) )
            self.disbands_left.remove( disband_auid )
            
    def OnUserChooseHero(self, party_event):
        info( party_event )
        event_auid = party_event.auid
        info( '%s OnUserChooseHero: self.auid %s, event auid %s' % (self.tag, self.auid, event_auid) )
        if event_auid in self.choose_heroes_left:
            warning( '%s on USER CHOOSE HERO: %d' % (self.tag, event_auid) )
            # юзер, извещения от которого мы ждем, выбрал героя
            self.choose_heroes_left.remove( event_auid )
            
    def OnUserPartyGo(self, party_event):
        info( party_event )
        warning( '%s on PARTY GO' % (self.tag) )
        self.party_go = 1
        
    # ---------------------------------------------------------------------------
                
    def OnAcceptSuccess(self, party_event):
        info( party_event )
        self.master_auid = party_event.master_auid
        warning( '%s on ACCEPT SUCCESS (JOINED): %d' % (self.tag, self.master_auid) )
        
        self.accepts_left.remove( self.master_auid )
        self.party_id = toint(party_event.party_id) # вступили в партию
        
    def OnDeclineSuccess(self, party_event):
        info( party_event )
        
        master_auid = toint( party_event.master_auid )
        info( '%s on DECLINE SUCCESS: %d' % (self.tag, master_auid) )
        self.declines_left.remove( master_auid )

    def OnDisbandSuccess(self, party_event):
        info( party_event )
        
        master_auid = toint( party_event.master_auid )
        warning( '%s on KICK SUCCESS: %d' % (self.tag, master_auid) )
        self.disbanded_ok = 1
        self.party_id = 0 # вышли из партии

        
    # ---------------------------------------------------------------------------
    
    def OnPartyCmdError(self, party_event):
        info( party_event )

        assert operator.isNumberType( party_event.msg_id ) and party_event.msg_id
        assert isinstance( party_event.failed_cmd, basestring )
        assert operator.isNumberType( party_event.party_id ) 
        assert party_event.action == "server_party"
        assert isinstance( party_event.message, basestring )
        
        failed_cmd = party_event.get('failed_cmd')
        if failed_cmd == 'invite':
            auid = toint( party_event.get('invite_auid') )
            info( '%s on INVITE FAILED: %d' % (self.tag, auid) )
        
    # ---------------------------------------------------------------------------
    # ---------------------------------------------------------------------------
    
    # OVERRIDE: party-контекст изначально не знает свой mmid, узнаёт его только после первого mm-пинга
    def OnPingMM(self, data):
        mmid = data['response']['mmid']
        if not self.mm.mmid:
            self.mm.mmid = mmid # party-контекст изначально не знает свой mmid, узнаёт его только после первого mm-пинга
            
        assert mmid == self.mm.mmid, 'mmid should be equal'
        self.mm.Ping( data['response']['mm'] )
        
        # прикучиваем полный session info, для последующего вдумчивого рассматривания в party_FSM-ках
        self.mm.lastPingResponse = data['response']['mm']
    
