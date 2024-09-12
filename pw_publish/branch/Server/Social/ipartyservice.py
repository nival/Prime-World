# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, urllib

sys.path.append('base')
from helpers import *

import collections
import functools

import CC
import EC
import MM
import ihttp


##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IPartyService:
    """ Болванка для интерфейса """
    def __init__(self, addresses=None, HTTP=None):
        pass
        
    def updateGameData(self, *args, **kwargs):
        pass
        
    def updatePersonStatus(self, *args, **kwargs):
        pass

    def unsubscribe(self, *args, **kwargs):
        pass
        
    def sendPartyCmd(self, *args, **kwargs):
        pass
        
    def partyInvite(self, *args, **kwargs):
        pass

    def updateTalentSetInfo(self, *args, **kwargs):
        pass


##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IHttpPartyService( IPartyService ):
    """  """
    def __init__(self, addresses=[""], HTTP=None, request_limit=1000):
        self.addresses = addresses
        self.address_count = len(addresses) or 1
        self.HTTP = ihttp.ILimitedAsyncHttpFetcher( HTTP, request_limit )
        
    def getPeer(self, party_id):
        if self.address_count:
            if party_id == "afterparty_register":
                return self.addresses[0]
            else:
                return self.addresses[party_id % self.address_count ]
            
    def onFetch(self, response, peer_addr="", args={}, callback=None):
        info("IHttpPartyService response (peer_addr=%s, args=%s):\n%s" % (peer_addr, args, str(response)[:128]))
        if callback:
            callback(response)
            
    def do(self, party_id, args, callback):
        peer_addr = self.getPeer( party_id )
        _callback = functools.partial( self.onFetch, peer_addr=peer_addr, args=args, callback=callback )
        self.fetch( peer_addr, args, _callback )
        
    # единственная точка, реально вызывающая HTTP.fetch (OVERRIDE point для фейк-интерфейсов)
    def fetch(self, peer_addr, args, callback):
        self.HTTP.fetch( peer_addr, args, callback )
        
    def updateWsAcc(self, auid, uid, server):
        args = dict( action="pts_update_ws_acc", auid=auid, uid=uid, server=server )
        # оповещаем всех 
        for peer_addr in self.addresses:
            self.fetch( peer_addr, args, None ) # тут нам никогда не нужен callback
            
    # ----------------------------------------------------------------------------------
    def updateGameData(self, auid, party_id, friends_model_changes, callback=None, **kwargs):
        args = dict( action="pts_update_game_data", auid=auid, party_id=party_id, friends_model_changes=friends_model_changes, **kwargs )
        self.do( party_id, args, callback )
        
    def updatePersonStatus(self, auid, party_id, person_status, callback=None):
        args = dict( action="pts_update_person_status", auid=auid, party_id=party_id, person_status=person_status )
        self.do( party_id, args, callback )

    def unsubscribe(self, auid, party_id, callback=None):
        args = dict( action="pts_unsubscribe", auid=auid, party_id=party_id )
        self.do( party_id, args, callback )

    # ----------------------------------------------------------------------------------
    def sendPartyCmd(self, auid, server, command, callback, **kwargs):
        if command == "party_hero" and kwargs.get("mm_progress", 0) == MM.STATUS_GUARDS_LOBBY:
            # специальный случай: в гвардейском тамбуре нужно отправлять вместо tmb_party_hero на "тамбурный" сервер, и мапить по game_id
            args = dict( action="pts_tambur_hero", auid=auid, server=server, **kwargs )
            game_id = toint( args.get("game_id", 0) )
            if game_id:
                self.do( game_id, args, callback )
            else:
                err("no game_id in tambur party_hero args (%s)" % args)
                if callback:
                    callback( {} )
        elif command in ["party_disband", "party_kick", "party_dodge", "party_go", "party_hero", "party_map",
                         "party_flag", "party_inventory_is_full"]:
            args = dict( action="pts_"+command, auid=auid, server=server, **kwargs )
            party_id = toint( args.get("party_id", 0) )
            if party_id:
                self.do( party_id, args, callback )
            else:
                err("no party_id in IHttpPartyService.sendPartyCmd(%s)" % args)
                if callback:
                    callback( {} )
        else:
            err("bad party cmd for party server (%s)" % command)
            if callback:
                callback( dict(ec=EC.FRIENDS_BAD_PARTY_CMD, error="bad party cmd for party server: %s" % command) )
                
    # ----------------------------------------------------------------------------------
    def partyInvite(self, party_id, auid, invite_auid, json_master_person="{}", json_invited_person="{}", as_enemy=0,
                    game_type="", with_bots=0, flagType=0, flagPersistentId="default_flag", isMMAllowed=True,
                    isInventoryFull=False, isLeaver=False, tournamentDynQuestId=-1,dependedTournamentQuests = "-1", callback=None, banEndTime = 0):
        args = dict(action="pts_party_invite", auid=auid, invite_auid=invite_auid, party_id=party_id,
            json_master_person=json_master_person, json_invited_person=json_invited_person, as_enemy=as_enemy,
            game_type=game_type, with_bots=with_bots, flagType=flagType, flagPersistentId=flagPersistentId,
            isMMAllowed=isMMAllowed, isInventoryFull=isInventoryFull, isLeaver=isLeaver, banEndTime=banEndTime, tournamentDynQuestId=tournamentDynQuestId,dependedTournamentQuests=dependedTournamentQuests)
        self.do(party_id, args, callback)
        
    def partyAccept(self, party_id, auid, banEndTime, flagType, flagPersistentId, isMMAllowed, isInventoryFull, isLeaver, tournamentDynQuestId, dependedTournamentQuests, callback=None):
        args = dict(action="pts_party_accept", auid=auid, party_id=party_id, banEndTime=banEndTime, flagType=flagType,
                    flagPersistentId=flagPersistentId, isMMAllowed=isMMAllowed, isInventoryFull=isInventoryFull, isLeaver=isLeaver,
                    tournamentDynQuestId=tournamentDynQuestId, dependedTournamentQuests=dependedTournamentQuests)
        self.do(party_id, args, callback)
        
    def partyDecline(self, party_id, auid, callback=None):
        args = dict( action="pts_party_decline", auid=auid, party_id=party_id )
        self.do( party_id, args, callback )        
        
    def partyRelogin(self, party_id, auid, callback=None):
        args = dict( action="pts_party_relogin", auid=auid, party_id=party_id )
        self.do( party_id, args, callback )        

    def updateProgress(self, party_id, auid, progress, person_status, party_ec, callback=None):
        args = dict( action="pts_party_progress", auid=auid, party_id=party_id, progress=progress, person_status=person_status, party_ec=party_ec )
        self.do( party_id, args, callback )

    def choosePartyAgain(self, party_id, auid, session_id, allies_keys, agreed, callback, **kwargs):
        args = dict(action="pts_afterparty_process", auid=auid, session_id=session_id, party_id=party_id,
                    allies_keys=allies_keys, agreed=agreed, **kwargs)
        # Шардим по session_id, потому что он одинаковый у всей afterparty
        self.do(session_id, args, callback)

    def addPersonToAfterparty(self, party_id, auid, session_id, allies_keys, agreed, callback, **kwargs):
        args = dict(action="pts_afterparty_process_member", auid=auid, session_id=session_id, party_id=party_id,
                    allies_keys=allies_keys, agreed=agreed, **kwargs)
        self.do(party_id, args, callback)

    def addPartyToAfterparty(self, party_id, auid, session_id, allies_keys, agreed, callback, **kwargs):
        args = dict(action="pts_afterparty_process_party", auid=auid, session_id=session_id, party_id=party_id,
                    allies_keys=allies_keys, agreed=agreed, **kwargs)
        self.do(party_id, args, callback)

    def removeAfterpartyId(self, session_id, party_id):
        args = dict(action="pts_afterparty_remove_id", session_id=session_id, party_id=party_id)
        self.do("afterparty_register", args, None)

    def getPartyData(self, party_id, callback, remove_party=False ):
        args = dict(action="pts_party_get_data", party_id=party_id, remove_party=remove_party)
        self.do(party_id, args, callback)

    # ----------------------------------------------------------------------------------
    def sendTamburCmd(self, auid, command, callback=None, **kwargs):
        if command in ["tambur_delete", "tambur_ready"]:
            args = dict( action="pts_"+command, auid=auid, **kwargs )
            game_id = toint( args.get("game_id", 0) )
            if game_id:
                self.do( game_id, args, callback )
            else:
                err("no game_id in IHttpPartyService.sendTamburCmd(%s)" % args)
                if callback:
                    callback( {} )
        else:
            err("bad tambur cmd for party server (%s)" % command)
            if callback:
                callback( dict(ec=EC.FRIENDS_BAD_PARTY_CMD, error="bad tambur cmd for party server: %s" % command) )
        
    def tamburAddPerson(self, game_id, auid, callback=None, **kwargs):
        args = dict( action="pts_tambur_add_person", game_id=game_id, auid=auid, **kwargs )
        self.do( game_id, args, callback )

    def getAfterpartyId(self, auid, session_id, allies_keys, oparty_id, callback, **kwargs):
        args = dict( action="pts_get_afterparty_id", session_id=session_id, auid=auid, allies_keys=allies_keys, old_party_id=oparty_id, **kwargs )
        self.do( "afterparty_register", args, callback )

    def updatePartyLeaverInfo(self, auid, party_id, isLeaver,  callback, **kwargs):
        args = dict(action="pts_party_update_leaver_info", auid=auid, party_id=party_id, isLeaver=isLeaver, **kwargs)
        self.do(party_id, args, callback)

    def updatePartyTournamentInfo(self, auid, party_id, tournamentDynQuestId, dependedTournamentQuests,  callback, **kwargs):
        args = dict(action="pts_party_update_tournament_info", auid=auid, party_id=party_id, tournamentDynQuestId=tournamentDynQuestId, dependedTournamentQuest=dependedTournamentQuests, **kwargs)
        self.do(party_id, args, callback)

    def updatePartyTalentSetInfo(self, auid, party_id, activeTalentSet, callback, **kwargs):
        args = dict(action="pts_party_update_talentset_info", auid=auid, party_id=party_id, activeTalentSet=activeTalentSet, **kwargs)
        self.do(party_id, args, callback)


##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IFakePartyService( IHttpPartyService ):
    """ вместо HTTP у нас функция, которую мы тупо вызываем """
    def __init__(self, addresses=[""], HTTP=None):
        self.addresses = addresses
        self.address_count = len(addresses) or 1
        assert isinstance( HTTP, collections.Callable )
        self.HTTP = HTTP
        
    def fetch(self, peer_addr, args_dict, callback):
        response = self.HTTP( args_dict )
        if callback:
            callback( response )
