#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Mock Social Aggregator web-server
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import functools
import time


import tornado.options
from tornado.options import define, options

addModPath('cfg')
# import cfg
import coord_cfg
import cfg

from config.MultiConfig import *

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

from handlers import * # JsonHandler, IfaceFactory
from subaction import SubAction, action_timing, separate_timing
from subaction import ResponseObject

from party_const import *
import MM
import CC
from MM import FriendStatus, GameType2FriendStatus
from binascii import crc32
## ---------------------------------------------------------------------------------------------

from modeldata.changes import PendingChangeWriter, GroupPendingChangeWriter, MakeModelChangeString

from party.PartyData import PartyData
from party.PartyMember import PartyMember
from party.Person import Person
from party.Party import Party

from modeldata.datamanager import PwNewModelManager # от него, вообще-то, нужен только .toJson
from modeldata.MultiStaticData import MultiStaticData

from friend_service import preview_pending_response, PersonServerSubAction, BasePersonService, FakePartyData, UpdateWsAccAction
import ifriendservice
import ipartyservice

## ---------------------------------------------------------------------------------------------

def getGroupChatName(group_id):
    return 'group_%s' % group_id
    
def getTamburChatName(group_id):
    return 'tambur_%s' % group_id

## ---------------------------------------------------------------------------------------------
class PartyContext:
    """ Контекст партии, общий для всех ее членов. Здесь же живет и ее PartyData, model changes от которой опять же рассылаются всем членам партии. """
    def __init__(self, master_auid, party_id, game_type, with_bots, flag_type, flag_id, isMMAllowed, isInventoryFull, isLeaver, banEndTime, tournamentDynQuestId, dependedTournamentQuests,
                 WS, master_person_dict, agreed=True, old_session_id=0):
        self.party_id = party_id
        self.members = [master_auid]
        self.old_session_id = old_session_id
        self.leavers = []
        self.kick_members = []
        self.pending_invites = {} # auid -> invite timestamp
        self.I = ClassDict(WS=WS)

        # ------- PartyData -----------------------------------------------------------------
        self.I.WS.resetPendingChanges(self) # заводим self.pending и self.pending_changes
        pd = PartyData()
        self.PartyData = pd
        self.PartyData.init(None) # вот теперь начинаем писать pending changes
        
        _master_person, _master_person_id = pd.newFriend() ## _master_person, _master_person_id = pd.newFixedIdFriend(master_auid) 
        _master_person.person_uid = master_auid
        self.I.WS.updatePersonFromDict(_master_person, master_person_dict)

        _master, _master_id = pd.newPartyMember()
        _master.person = _master_person
        _master.flagType = flag_type
        _master.flagPersistentId = flag_id
        _master.isMMAllowed = isMMAllowed
        _master.isPending = False
        _master.isInventoryFull = isInventoryFull
        _master.isLeaver = isLeaver
        _master.banEndTime = banEndTime
        _master.tournamentDynQuestId = tournamentDynQuestId
        _master.dependedTournamentQuests = dependedTournamentQuests
        _master.agreed = bool(agreed)

        info('new party _master dict: %s,\n_master_person dict: %s',_master.generateJsonDict(), _master_person.generateJsonDict())

        pd.owner = _master
        pd.members.add(_master)
        pd.party_uid = party_id
        pd.mapID = game_type
        pd.withBots = bool(with_bots)
        
        self.is_fixed_match = 0

        self.PartyData.init(self.pending) # вот теперь начинаем писать pending changes
        
    def isMaster(self, auid):
        return auid and (self.members[0] == auid)

    def getMaster(self):
        if self.members:
            return self.members[0]
        return 0

    # пока в группе есть только мастер, она считается временной; ее мастера можно приглашать в другие партии
    def isTemp(self):
        return len(self.members) <= 1
        
    def isEmpty(self):
        return len(self.members) <= 0
        
    def isFull(self, is_fixed_match_party=0):
        return len(self.members) >= MAX_PARTY_MEMBERS * (is_fixed_match_party+1) # для fixed_match_party=1 удваиваем лимит
    
    def isFullWithInvites(self, is_fixed_match_party=0):
        return len(self.members) + len(self.pending_invites) >= MAX_PARTY_MEMBERS * (is_fixed_match_party+1) # для fixed_match_party=1 удваиваем лимит
        
    # -----------------------------------------------------------------
    def addInvite(self, auid, invited_person_dict, as_enemy=0):
        if auid not in self.pending_invites:
            self.pending_invites[auid] = time.time()
        
            # ------- PartyData -----------------------------------------------------------------
            # добавляем нового приглашенного (isPending) member-а в свою партию
            pd = self.PartyData

            _person, _person_id = pd.newFriend() ## _person, _person_id = pd.newFixedIdFriend(auid) 
            _person.person_uid = auid
            self.I.WS.updatePersonFromDict(_person, invited_person_dict)

            _member, _member_id = pd.newPartyMember()
            _member.person = _person
            _member.isPending = True
            _member.isEnemy = bool(as_enemy)
            
            if as_enemy:
                self.is_fixed_match = 1
        
            pd.members.add(_member)

            ## info('add invite pending_changes: %s' % preview_pending_response(self, self.party_id))

    def checkDataForStats(self,auid):

        if auid in self.kick_members:
            self.kick_members.remove(auid)

        if auid in self.leavers:
            self.leavers.remove(auid)

    # -----------------------------------------------------------------
    def addPendingMember(self, auid):
        pd = self.PartyData
        if auid in self.members:
            return
        self.members.append(auid)
        self.checkDataForStats(auid)

        _person, _person_id = pd.newFriend() ## _person, _person_id = pd.newFixedIdFriend(auid)
        _person.person_uid = auid

        _member, _member_id = pd.newPartyMember()
        _member.person = _person
        _member.isPending = True
        _member.agreed = False
        _member.isEnemy = False

        pd.members.add(_member)
            
    # -----------------------------------------------------------------
    def acceptInvite(self, auid):
        if auid in self.pending_invites:
            # вписать юзера в партию
            self.pending_invites.pop(auid)            
            self.members.append(auid)            
            self.checkDataForStats(auid)

            # ------- PartyData -----------------------------------------------------------------
            # всего лишь меняем у приглашенного статус isPending
            _member = self.PartyData.findMemberByUid(auid)
            if _member:
                _member.isPending = False
                _member.agreed = True
                
            ## info('acceptInvite invite pending_changes: %s' % preview_pending_response(self, self.party_id))

    # -----------------------------------------------------------------
    def removePerson(self, auid):
        person = self.PartyData.findPersonByUid(auid)
        member = self.PartyData.findMemberByUid(auid)
        if member:
            self.PartyData.deleteByID(member.id)
        if person:
            self.PartyData.deleteByID(person.id)
            
        self.updateFixedMatchStatus()
        
        ## info('removePerson invite pending_changes: %s' % preview_pending_response(self, self.party_id))
        
    # -----------------------------------------------------------------
    def updateFixedMatchStatus(self):
        self.is_fixed_match = 0
        for id,member in self.PartyData.members.iteritems():
            if member and member.isEnemy:
                self.is_fixed_match = 1
                return

    # -----------------------------------------------------------------
    def getSimilarHeroesList(self, hero_crc):
        same_heroes_auids = []
        if hero_crc:
            for member_id, member in self.PartyData.members.iteritems():
                if member.heroClassId == hero_crc:
                    same_heroes_auids.append(member.person.person_uid)
                    
            if len(same_heroes_auids) > 1:
                warn("too many similar heroes! same_heroes_auids: %s, hero_crc=%s" % (same_heroes_auids, hero_crc))
            else:
                same_heroes_auids=[] # 2 одинаковых героя в партии -- разрешаем
            
        return same_heroes_auids

    def checkForbiddenPartyHeroes(self, auid, members, partyData, hero_src, config):
        forbiddenPartyHeroes = config.FORBIDDEN_FOR_PARTY_HERO_PAIRS
        for forbiddenHero in forbiddenPartyHeroes:
            debug("checkForbiddenPartyHeroes forbidden pair %r", forbiddenHero)
            sameheroes = {True: [auid], False: [auid]}
            hero1, hero2 = forbiddenHero.split(";")
            test = crc32(hero1), crc32(hero2)
            if hero_src in test:
                for _, member in partyData.members.iteritems():
                    if member.person.person_uid!=auid and member.heroClassId in test:
                        sameheroes[member.isEnemy].append(member.person.person_uid)

            debug("checkForbiddenPartyHeroes checkSimilarHeroes sameheroes: %r", sameheroes)
            if len(sameheroes[True]) > 1:
                return sameheroes[True]
            elif len(sameheroes[False]) > 1:
                return sameheroes[False]
    # -----------------------------------------------------------------
    def checkSimilarHeroes(self, config):
        same_heroes_auids = {}

        forbiddenPartyHeroes = config.FORBIDDEN_FOR_PARTY_HERO_PAIRS
        for forbiddenHero in forbiddenPartyHeroes:
            debug("forbidden pair %r", forbiddenHero)
            sameheroes = {True:[], False:[]}
            hero1, hero2 = forbiddenHero.split(";")
            hero1ClassId = crc32(hero1)
            hero2ClassId = crc32(hero2)

            for member_id, member in self.PartyData.members.iteritems():
                if member.heroClassId in (hero1ClassId, hero2ClassId):
                    sameheroes[member.isEnemy].append(member.person.person_uid)

            debug("checkSimilarHeroes sameheroes: %r", sameheroes)
            if len(sameheroes[True]) > 1:
                return sameheroes[True]
            elif len(sameheroes[False]) > 1:
                return sameheroes[False]

        for member_id, member in self.PartyData.members.iteritems():
            hero_crc_key = "enemy:%s,hero_crc:%s" % (member.isEnemy, member.heroClassId)
            if not same_heroes_auids.get(hero_crc_key):
                same_heroes_auids[hero_crc_key] = []
            same_heroes_auids[hero_crc_key].append(member.person.person_uid)

        for hero_crc_key, auid_list in same_heroes_auids.iteritems():
            if auid_list and len(auid_list) > 1:
                warn("too many similar heroes! auid_list: %s, key %s" % (auid_list, hero_crc_key))
                return auid_list

    # -----------------------------------------------------------------
    def checkPartyValueRange(self, valueName, VALUE_RANGE):
        bad_values = {} # сюда будем складывать плохие пары "auid:value", которые слишком отличаются от среднего значения по партии
        if len(self.PartyData.members):
            # сначала собираем значения в словарь вида auid:value
            hero_values = {}
            for member_id, member in self.PartyData.members.iteritems():
                auid = member.person.person_uid
                hero_values[ auid ] = getattr(member, valueName)
            
            # потом забираем значения в список, находим среднее/мин/макс
            hero_value_list = hero_values.values()
            avgValue = sum(hero_value_list) / len(hero_value_list)
            for auid, value in hero_values.iteritems():
                info("checkPartyValueRange: %s=%s for auid %s (avg %s, range %s..%s)" % (valueName, value, auid, avgValue, avgValue-VALUE_RANGE, avgValue+VALUE_RANGE))
                if (value < avgValue - VALUE_RANGE) or (value > avgValue + VALUE_RANGE):
                    bad_values[ auid ] = value

        # в итоге возвращаем список "плохих пар auid:value"; если он непустой -- должен быть варнинг
        info("checkPartyValueRange(%s): bad values %s" % (valueName, bad_values))
        return bad_values
        
    def getFixedMatchSides(self):
        party_auids = []
        enemy_auids = []
        for member_id, member in self.PartyData.members.iteritems():
            member_auid = member.person.person_uid
            if member.isEnemy:
                enemy_auids.append(member_auid)
            else:
                party_auids.append(member_auid)
        return party_auids, enemy_auids
        
    def getFixedMatchSide(self, isEnemy):
        side_auids = []
        for member_id, member in self.PartyData.members.iteritems():
            member_auid = member.person.person_uid
            if member.isEnemy == isEnemy and member.agreed:
                side_auids.append(member_auid)
        return side_auids
        
    FILTER_PARTY_MEMBER_FIELDS = ["banEndTime", "hero_id", "heroClassId", "heroForce", "heroLevel", "heroRating", "isValidTS", "skin_persistent_id", "IsAnimatedAvatar"]
    def filterPartyMembers(self, json_dict, isEnemy):
        if self.is_fixed_match:
            self._filterPartyMembers(json_dict, isEnemy)
        return json_dict
            
    def _filterPartyMembers(self, json_dict, isEnemy):
        for k, v in json_dict.iteritems():
            if k == "PartyMember":
                enemy = v.get("isEnemy", False)
                if enemy != isEnemy:
                    for field in self.FILTER_PARTY_MEMBER_FIELDS:
                        v.pop(field)
            elif isinstance(v, dict):
                self._filterPartyMembers(v, isEnemy) # рекурсивно по всем словарям

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------
                        
class TamburContext(PartyContext):
    """ Контекст 'гвардейского тамбура', общий для всех его членов. Сюда пихаем всех, кто попадает в тамбур, вне зависимости, в party они или соло. 
        Здесь живет копия PartyData, model changes от которой рассылаются всем членам тамбура под тагом 'TamburData'. """
    def __init__(self, tambur_id, WS):
        self.party_id = tambur_id
        self.members = []
        self.ts = time.time()
        self.I = ClassDict(WS=WS)
        self.is_fixed_match = 0
        
        # ------- PartyData -----------------------------------------------------------------
        self.I.WS.resetPendingChanges(self) # заводим self.pending и self.pending_changes
        pd = PartyData()
        self.PartyData = pd
        self.PartyData.init(None) # на этапе создания не пишем pending changes
        
        pd.party_uid = tambur_id
        
        self.PartyData.init(self.pending) # вот теперь начинаем писать pending changes
        ## info('new tambur pending_changes: %s' % preview_pending_response(self, self.party_id))

    # -----------------------------------------------------------------
    def addMember(self, auid, person_dict, realPartyUid):
        if auid not in self.members:
            self.members.append(auid)


            # ------- PartyData -----------------------------------------------------------------
            # добавляем нового приглашенного (isPending) member-а в свою партию
            pd = self.PartyData

            _person, _person_id = pd.newFriend() 
            _person.person_uid = auid
            self.I.WS.updatePersonFromDict(_person, person_dict)

            _member, _member_id = pd.newPartyMember()
            _member.person = _person
            _member.agreed = True
            _member.isPending = False
            _member.realPartyUid = realPartyUid

            pd.members.add(_member)
            if len(self.members) == 1: 
                pd.owner = _member # первого, кто добавляется в тамбур, делаем фиктивным owner-ом (чтобы клиент был счастлив)

            info('add tambur member changes: %s', preview_pending_response(self, self.party_id))
            
            
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class PartyUpdateGameDataAction(PersonServerSubAction):
    """ нам нужно только отфорвардить изменения person_info всем членам партии игрока """
    action = "pts_update_game_data"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("PartyUpdateGameDataAction")
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("party_id"):
                friends_model_changes = self.getParam("friends_model_changes", "")
                
                party = self.I.WS.parties.get(self.party_id)
                if party:
                    if friends_model_changes:
                        # грязный хак: поскольку (FriendsData)Friend и (PartyData)Person у нас совпадают до буквы, 
                        #   просто текстуально заменяем путь "FriendsKeeper/<auid>" -> "PersonKeeper/<person_id>" 
                        person = party.PartyData.findPersonByUid(self.auid)
                        if person:
                            friend_path = "FriendsKeeper\/%s" % self.auid
                            party_model_changes = friends_model_changes.replace(friend_path, person.path)
                            self.I.WS.sendPartyBroadcast(party, "change", to_auids=party.members, change_auid=self.auid,
                                                         json_PartyData=party_model_changes)
                    
                    # кроме того, нужно применить и разослать изменения hero data 
                    member = party.PartyData.findMemberByUid(self.auid)
                    if member:
                        self.hero_id = self.getIntParam("hero_id", 0)
                        self.hero_lvl = self.getIntParam("hero_lvl", 0)
                        self.hero_force = self.getFloatParam("hero_force", 0.0)
                        self.hero_rating = self.getFloatParam("hero_rating", 0.0)
                        
                        if member.hero_id == self.hero_id:
                            member.heroLevel = self.hero_lvl
                            member.heroForce = self.hero_force
                            member.heroRating = self.hero_rating
                            party_model_changes = self.I.WS.pickPendingPartyChanges(party) 
                            if party_model_changes:
                                to_auids = party.getFixedMatchSide(member.isEnemy) # рассылаем только своей стороне партии (не врагам в "договорняке"!)
                                self.I.WS.sendPartyBroadcast(party, "hero", auid=self.auid, to_auids=to_auids,
                                                             json_PartyData=party_model_changes)
        self.fin()

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class PartyUpdatePersonStatusAction(PersonServerSubAction):
    """ нам нужно только отфорвардить изменения person_info всем членам партии игрока """
    action = "pts_update_person_status"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("PartyUpdatePersonStatusAction")
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("party_id"):
                person_status = self.getIntParam("person_status", 0)
                
                party = self.I.WS.parties.get(self.party_id)
                if party:
                    person = party.PartyData.findPersonByUid(self.auid)
                    if person:
                        person.Status = person_status
                        member = party.PartyData.findMemberByUid(self.auid)
                        if member:
                            member.person.Status = person_status
                        # апдейтим всей партии результат изменения:
                        party_model_changes = self.I.WS.pickPendingPartyChanges(party) 
                        self.I.WS.sendPartyBroadcast(party, "friend_status", to_auids=party.members, auid=self.auid,
                                                     friend_status=person_status, json_PartyData=party_model_changes)
                    
        self.fin()

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class PartyUnsubscribeAction(PersonServerSubAction):
    """ нам нужно только отфорвардить изменения person_info всем членам партии игрока """
    action = "pts_unsubscribe"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("PartyUnsubscribeAction")
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("party_id"):
                party = self.I.WS.parties.get(self.party_id)
                if party:
                    # насильно выкидываем offline юзеров из партии
                    self.I.WS.removePartyMember(party, self.auid, message="offline")
                    
        self.fin()

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class PartyServiceInviteAction(PersonServerSubAction):
    action = 'pts_party_invite'
    """ """
    def onStart(self):
        if self.checkValidIntParam("auid"):
            self.setUserUid()
            if (self.checkValidIntParam("invite_auid") and self.checkValidIntParam("party_id") and self.checkValidParam("json_master_person")
                and self.checkValidParam("json_invited_person") and self.checkValidParam("game_type")):
                    self.master_person_dict = json_loads(self.json_master_person)
                    self.invited_person_dict = json_loads(self.json_invited_person)
                    self.as_enemy = self.getIntParam("as_enemy", 0)
                    self.with_bots = self.getIntParam("with_bots", 0)
                    self.flagType = self.getIntParam("flagType")
                    self.flagPersistentId = self.getParam("flagPersistentId")
                    self.isMMAllowed = self.getBoolParam("isMMAllowed", True)
                    self.isInventoryFull = self.getBoolParam("isInventoryFull", False)
                    self.isLeaver = self.getBoolParam("isLeaver", False)
                    self.banEndTime = self.getIntParam("banEndTime", 0)
                    self.tournamentDynQuestId = self.getIntParam("tournamentDynQuestId",-1)
                    self.dependedTournamentQuests = self.getParam("dependedTournamentQuests", "-1")

                    # смотрим, может ли приглашать
                    party = self.I.WS.parties.get(self.party_id)
                    if not party:
                        # у мастера нету партии; надо создать новый PartyContext
                        party = PartyContext(self.auid, self.party_id, self.game_type, self.with_bots, self.flagType,
                                              self.flagPersistentId, self.isMMAllowed, self.isInventoryFull, self.isLeaver, self.banEndTime,
                                             self.tournamentDynQuestId, self.dependedTournamentQuests,  self.I.WS, self.master_person_dict)
                        self.I.WS.parties[ self.party_id ] = party
                        self.I.CHAT.addUserGroup(self.auid, getGroupChatName(self.party_id), self.I.WS.onChatGroupRegister)

                        # для только что созданной партии надо выслать мастеру полный "init" новой PartyData
                        self.party = party
                        party_model_init = self.I.WS.WriteModelChangeString("create_party", "/", "init", party.PartyData.generateJsonDict())
                        self.I.WS.sendServerPartyCmd(self.auid, "create_init", "created new party during invite", party_id=self.party_id, \
                            master_auid=self.auid, json_PartyData=party_model_init) # перекладываем из response в pending events

                    if self.as_enemy: # пока есть хотя бы один инвайт "как противника", считаем партию "договорной"
                        party.is_fixed_match = 1

                    self.party = party
                    self.party_id = party.party_id

                    if party.isMaster(self.auid):
                        # ок, мы хозяин партии, имеем право приглашать
                        if not party.isFullWithInvites(party.is_fixed_match):
                            self.party_id = party.party_id

                            # добавляем в party context и общий PartyData приглашенного pending member
                            party.addInvite(self.invite_auid, self.invited_person_dict, self.as_enemy)

                            # заворачиваем для партии PartyData changes
                            party_model_changes = self.I.WS.pickPendingPartyChanges(party)
                            self.I.WS.sendPartyBroadcast(party, "invited", message="ok", invite_auid=self.invite_auid, \
                                json_PartyData=party_model_changes, to_auids=party.members, as_enemy=self.as_enemy)

                            self.response["ok"] = 1 # ок, приняли к исполнению

                        else:
                            self.response["error"] = "party is full with invites (members: %s, pending: %s, max count=%d)" \
                                % (party.members, party.pending_invites.keys(), MAX_PARTY_MEMBERS)
                            self.replyInviteError("invite", PARTY_ERROR.PARTY_FULL)
                    else:
                        self.response["error"] = "party member (not master) cannot invite (members: %s)" % str(party.members)
                        self.replyInviteError("invite", PARTY_ERROR.PARTY_MEMBER_CANT_INVITE)
                                            
        self.fin()

##---------------------------------------------------------------------------------------------------

class PartyServiceActionBase(PersonServerSubAction):
    """ все команды, подразумевающие наличие партии, идут через этот общий базовый класс """
    def onStart(self):        
        if self.checkValidIntParam("auid"):
            self.setUserUid()
            if self.checkValidIntParam("party_id"):
                self.party = self.I.WS.parties.get(self.party_id)
                info("%s: auid=%s, party_id=%s, party=%s" % (self.action, self.auid, self.party_id, self.party))
                if self.party:
                    self.master_auid = self.party.getMaster()
                    #----------
                    # main handler:
                    if self.cmdStart(): # если основной хэндлер что-то вернет, не будем вызывать self.fin
                        return
                    
                else:
                    self.response["error"] = "unknown party_id: %d" % self.party_id
                    self.replyPartyError("decline", PARTY_ERROR.BAD_PARTY)
                       
        self.fin()

    # --------------------------------------------------------------------------------
    # helper
    def checkPartyMaster(self):
        if self.party:
            if self.party.isMaster(self.auid):
                return True                
            else:
                self.response["error"] = "not a party master: auid %d, party_id %d, members: %s" % (self.auid, self.party_id, strList(self.party.members))
                self.replyPartyError(self.action, PARTY_ERROR.NOT_A_PARTY_MASTER, self.auid)
        else:
            self.response["error"] = "no such party: master_auid %s, party_id %s" % (self.master_auid, self.party_id)
            self.replyPartyError(self.action, PARTY_ERROR.BAD_PARTY, self.auid)
            
    # --------------------------------------------------------------------------------
    # helper: проверяем, нет ли у нас членов партии с mm_progress != 0, при необходимости перещелкиваем party.InMatchmaking
    def checkPartyMMProgress(self, party_progress={}, party_timestamps={}):
        if not party_progress:
            for member_id,member in self.party.PartyData.PartyMemberKeeper.iteritems():
                if member.person.InMatchmaking: # нет ли отличного от 0 прогресса mm-сессии
                    party_progress[ member.person.person_uid ] = 1
        
        isPartyHasProgress = bool(party_progress)
        if self.party.PartyData.InMatchmaking != isPartyHasProgress:
            # у кого-то из партии появился ненулевой progress state - пометим партию как "в поиске", чтобы не могли стартовать новый поиск
            warn("switching checkPartyMMProgress(party_id=%s) to %s" % (self.party.party_id, isPartyHasProgress))
            self.party.PartyData.InMatchmaking = isPartyHasProgress

    # --------------------------------------------------------------------------------
    # helper: проверяем, нет ли у нас героев с переполненной библиотекой
    def checkForPlayersLibrary(self):
        for member_id, member in self.party.PartyData.PartyMemberKeeper.iteritems():
            if member.isInventoryFull:
                return False
        return True

##---------------------------------------------------------------------------------------------------

class AfterpartyActionBase(SubAction):
    """ сюда выносим базовые для Afterparty helper-методы """

    def createInitChanges(self, party):
        party.PartyData.eraseAllErrors()
        party_dict = party.filterPartyMembers(party.PartyData.generateJsonDict(), False)
        self.writeStringToResponse("initPartyData", "join_new_party", "/", "init", party_dict)
        temp = self.response.pop("initPartyData")
        if isinstance(temp, ResponseObject):
            temp = temp.makeDict()
        return self.I.MD.toJson(temp)

    def fillAfterparty(self, afterparty):
        debug("pre fillAfterparty afterparty %r", afterparty)
        debug("pre fillAfterparty afterparty.PartyData %r", afterparty.PartyData.generateJsonDict())
        debug("pre fillAfterparty self.allies_keys %r",  self.allies_keys)

        afterparty.PartyData.madeAfterBattle = True
        afterparty.PartyData.afterBattleLockEndTime = self.lock_end_time
        afterparty.afterparty_session_id = self.session_id
        afterparty.max_party_size = 1
        # Заводим "пустых" союзников
        if self.allies_keys and not isinstance(self.allies_keys, int ):
            allies = self.allies_keys.split(",")
            for auid in allies:
                a = auid.strip('"')
                # Проверим, что этих ребят точно нет в пати
                member = afterparty.PartyData.findMemberByUid(int(a))
                person = afterparty.PartyData.findPersonByUid(int(a))
                if not member and not person:
                    afterparty.addPendingMember(int(a))
                    self.I.FRIENDS.getFriendInfo(a, self.onMemberInfoFromFriends)

        elif self.allies_keys and isinstance(self.allies_keys, int):
            # Проверим, что этих ребят точно нет в пати
            member = afterparty.PartyData.findMemberByUid(int(self.allies_keys))
            person = afterparty.PartyData.findPersonByUid(int(self.allies_keys))
            if not member and not person:
                afterparty.addPendingMember(int(self.allies_keys))
                self.I.FRIENDS.getFriendInfo(self.allies_keys, self.onMemberInfoFromFriends)


        debug("post fillAfterparty afterparty %r", afterparty)
        debug("post fillAfterparty afterparty.PartyData %r", afterparty.PartyData.generateJsonDict())



    def onMemberInfoFromFriends(self, response):
        if response and response.get("ok") and response.get("person_dict"):
            afterparty = self.I.WS.parties.get(self.party_id)
            if afterparty:
                person_dict = json_loads(response.get("person_dict"))
                member = afterparty.PartyData.findMemberByUid(person_dict.get("person_uid"))
                person = afterparty.PartyData.findPersonByUid(person_dict.get("person_uid"))
                if member and person:
                    self.I.WS.resetPendingChanges(afterparty)
                    self.I.WS.updatePersonFromDict(person, person_dict)
                    party_model_changes = self.I.WS.pickPendingPartyChanges(afterparty)
                    self.I.WS.sendPartyBroadcast(afterparty, "person_info", json_PartyData=party_model_changes)

    def removeMember(self, afterparty, auid):

        debug("pre removeMember afterparty.members %r", afterparty.members)
        debug("pre removeMember afterparty.PartyData %r", afterparty.PartyData.generateJsonDict())
        master = afterparty.getMaster()
        if master and auid == master:
            # если из партии выходит мастер, нужно сменить owner на следующего member
            if len(afterparty.members) > 1:
                _next_master = afterparty.PartyData.findMemberByUid(afterparty.members[1])
                afterparty.PartyData.owner = _next_master

        afterparty.removePerson(auid)
        if auid in afterparty.members:
            afterparty.members.remove(auid)

        debug("post removeMember afterparty.members %r", afterparty.members)
        debug("post removeMember afterparty.PartyData %r",  afterparty.PartyData.generateJsonDict())


class PartyServiceMapAction(PartyServiceActionBase):
    action = 'pts_party_map'
    """ """
    @separate_timing
    def cmdStart(self):
        if self.checkPartyMaster():
            self.checkPartyMMProgress({}, {})
            if not self.party.PartyData.InMatchmaking:      
                self.game_type = self.getParam("game_type", "")
                self.with_bots = self.getIntParam("with_bots", -1)
                
                pd = self.party.PartyData
                if self.game_type:
                    pd.mapID = self.game_type
                if self.with_bots != -1:
                    pd.withBots = bool(self.with_bots)                

                party_model_changes = self.I.WS.pickPendingPartyChanges(self.party) 
                                                
                kwargs = dict(
                    game_type = self.game_type, 
                    with_bots = self.with_bots , 
                    json_PartyData = party_model_changes
                )
                
                # рассылаем всей партии команду map:
                self.I.WS.sendPartyBroadcast(self.party, "map", **kwargs)
                
                self.response["ok"] = 1
            else:
                self.response["error"] = "cant change map while in matchmaking: party_id %d" \
                        % (self.party_id)
                self.replyPartyError("go", PARTY_ERROR.CANT_CNANGE_MAP_MM, 0)                
        
##---------------------------------------------------------------------------------------------------

class PartyServiceFlagAction(PartyServiceActionBase):
    action = 'pts_party_flag'
    """ """
    @separate_timing
    def cmdStart(self):
        self.checkPartyMMProgress({}, {})
        if not self.party.PartyData.InMatchmaking:
            if self.getIntParam("person_id"):
                self.flagType = self.getIntParam("flag_type", 0)
                self.flagPersistentId = self.getParam("flag_persistent_id", self.I.SD.getDefaultFlagName())
                self.person = self.getIntParam("person_id")

                pd = self.party.PartyData
                person = pd.findPersonByUid(self.person)
                if person:
                    member = pd.findMemberByUid(self.person)
                    if member:
                        member.flagType = self.flagType
                        member.flagPersistentId = self.flagPersistentId


                party_model_changes = self.I.WS.pickPendingPartyChanges(self.party)

                kwargs = dict(json_PartyData=party_model_changes)

                # рассылаем всей партии команду flag:
                self.I.WS.sendPartyBroadcast(self.party, "flag", **kwargs)

                self.response["ok"] = 1
            else:
                self.response["error"] = "no party member selected to change flag: party_id %d" \
                    % (self.party_id,)
        else:
            self.response["error"] = "cant change flag while in matchmaking: party_id %d" \
                    % (self.party_id)
            self.replyPartyError("go", PARTY_ERROR.CANT_CNANGE_MAP_MM, 0)

##---------------------------------------------------------------------------------------------------

class PartyServiceInventoryIsFullAction(PartyServiceActionBase):
    action = 'pts_party_inventory_is_full'
    """ """
    @separate_timing
    def cmdStart(self):
        self.checkPartyMMProgress({}, {})
        info("PartyServiceInventoryIsFullAction onStart")
        if not self.party.PartyData.InMatchmaking:
            if self.getIntParam("person_id"):
                self.isFull = self.getBoolParam("isFull", False)
                self.person = self.getIntParam("person_id")

                pd = self.party.PartyData
                person = pd.findPersonByUid(self.person)
                if person:
                    member = pd.findMemberByUid(self.person)
                    if member:
                        member.isInventoryFull = self.isFull

                party_model_changes = self.I.WS.pickPendingPartyChanges(self.party)

                kwargs = dict(json_PartyData=party_model_changes)
                # рассылаем всей партии команду is_inventory_full:
                self.I.WS.sendPartyBroadcast(self.party, "is_inventory_full", **kwargs)

                self.response["ok"] = 1
            else:
                self.response["error"] = "no party member selected to change isInventoryFull flag: party_id %d" \
                    % (self.party_id,)
        else:
            self.response["error"] = "cant change isInventoryFull flag while in matchmaking: party_id %d" \
                    % (self.party_id)
            self.replyPartyError("go", PARTY_ERROR.CANT_CNANGE_MAP_MM, 0)

##---------------------------------------------------------------------------------------------------

class PartyServiceAcceptAction(PartyServiceActionBase):
    action = 'pts_party_accept'
    """ """
    def cmdStart(self):        
        self.banEndTime = self.getIntParam("banEndTime")
        self.flagType = self.getIntParam("flagType") or 0
        self.flagPersistentId = self.getParam("flagPersistentId") or self.I.SD.getDefaultFlagName()
        self.isMMAllowed = self.getBoolParam("isMMAllowed", True)
        self.isInventoryFull = self.getBoolParam("isInventoryFull", False)
        self.isLeaver = self.getBoolParam("isLeaver", False)
        self.tournamentDynQuestId= self.getIntParam("tournamentDynQuestId", -1)
        self.dependedTournamentQuests = self.getParam("dependedTournamentQuests", "-1")
        if self.auid in self.party.pending_invites:
            if not self.party.isFull(self.party.is_fixed_match):
                # запоминаем список предыдущих членов партии (свежеприсоединившемуся уйдет отдельный join_init)
                join_notification_list = self.party.members[:] 

                # ---- наконец, принимаем invite ----
                self.party.acceptInvite(self.auid) 

                # проставляем banEndTime
                _member = self.party.PartyData.findMemberByUid(self.auid)
                if _member:
                    _member.banEndTime = self.banEndTime
                    _member.flagType = self.flagType
                    _member.flagPersistentId = self.flagPersistentId
                    _member.isMMAllowed = self.isMMAllowed
                    _member.person.InMatchmaking = False
                    _member.isInventoryFull = self.isInventoryFull
                    _member.isLeaver = self.isLeaver
                    _member.tournamentDynQuestId=self.tournamentDynQuestId
                    _member.dependedTournamentQuests =self.dependedTournamentQuests
                
                # отправить всем членам партии КРОМЕ только что вступившего -- сообщение "join" про нового member
                party_model_changes = self.I.WS.pickPendingPartyChanges(self.party)
                self.I.WS.sendPartyBroadcast(self.party, "join", to_auids=join_notification_list, master_auid=self.master_auid, \
                    join_auid=self.auid, members=strList(self.party.members), json_PartyData=party_model_changes) 
                    
                # а вот только что вступившему в партию надо 
                # 1) зачистить PartyData от ошибок (вообще механизма очистки от ошибок я не нашел, поэтому чистим здесь)
                self.party.PartyData.eraseAllErrors()

                # 2) выслать полный init-пакет PartyData
                party_dict = self.party.filterPartyMembers(self.party.PartyData.generateJsonDict(), _member.isEnemy)
                self.writeStringToResponse("initPartyData", "join_new_party", "/", "init", party_dict) 
                temp = self.response.pop("initPartyData")
                if isinstance(temp, ResponseObject):
                    temp = temp.makeDict()
                party_model_init = self.I.MD.toJson(temp)

                ## info("self.party: %s, party_id: %d, self.party.PartyData: %s, members: %s" \
                ##    % (self.party, self.party.party_id, self.party.PartyData, self.party.PartyData.members.keys()))
                    
                ## info("toJson: %s, model_init: %s" % (self.I.MD.toJson(self.party.PartyData), party_model_init))
                        
                self.replyPartyCmd("join_init", "joined new party", join_auid=self.auid, master_auid=self.master_auid, \
                    json_PartyData=party_model_init) # перекладываем из response в pending events
                
                self.I.CHAT.addUserGroup(self.auid, getGroupChatName(self.party_id), self.I.WS.onChatGroupRegister)
                self.response["ok"] = 1 # ок, done
        
            else:
                self.response["error"] = "party is full: party_id %d, members: %s" % (self.auid, self.party_id, str(self.party.members))
                self.replyPartyError("accept", PARTY_ERROR.PARTY_FULL, self.master_auid)
        else:
            self.response["error"] = "no invite for auid %d: party_id %d, pending_invites: %s" \
                % (self.auid, self.party_id, str(self.party.pending_invites))
            self.replyPartyError("accept", PARTY_ERROR.NO_PENDING_INVITE, self.master_auid)
                
##---------------------------------------------------------------------------------------------------

class PartyServiceDeclineAction(PartyServiceActionBase):
    action = 'pts_party_decline'
    """ """
    def cmdStart(self):        
        if self.auid in self.party.pending_invites:
            # ---- отклоняем invite ----
            self.I.WS.removePartyMember(self.party, self.auid, "user decline")
            self.response["ok"] = 1 # ок, done
        else:
            self.response["error"] = "no invite for auid %d: party_id %d, pending_invites: %s" \
                % (self.auid, self.party_id, str(self.party.pending_invites))
            self.replyPartyError("decline", PARTY_ERROR.NO_PENDING_INVITE, self.master_auid)

##---------------------------------------------------------------------------------------------------

class PartyServiceDisbandAction(PartyServiceActionBase):
    action = 'pts_party_disband'
    """ """
    def cmdStart(self):        
        if self.auid in self.party.members:
            # если команда автоматическая (например, в результате mm_leave из идущей сессии) может быть указана причина
            reason = self.getParam("reason", "user disband")
                
            self.I.WS.removePartyMember(self.party, self.auid, message=reason)
            if self.auid not in self.party.leavers:
                self.party.leavers.append(self.auid)

            self.response["ok"] = 1 # ок, done
        else:
            self.response["error"] = "not a party member: auid %d, party_id %d, members: %s" % (self.auid, self.party_id, strList(self.party.members))
            self.replyPartyError("disband", PARTY_ERROR.NOT_A_PARTY_MEMBER, self.auid)
        
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class PartyServiceKickAction(PartyServiceActionBase):
    action = 'pts_party_kick'
    """ """
    def cmdStart(self):        
        if self.checkPartyMaster():
            if self.checkValidIntParam("kick_auid"):
                if self.kick_auid in self.party.members:
                    if self.auid != self.kick_auid:
                        self.I.WS.removePartyMember(self.party, self.kick_auid, message="kicked")
                        if self.kick_auid not in self.party.kick_members:
                            self.party.kick_members.append(self.kick_auid)
                        self.response["ok"] = 1 # ок, done
                        
                    else:
                        self.response["error"] = "cant kick oneself: auid %d, kick_auid %d" % (self.auid, self.kick_auid)
                        self.replyPartyError("kick", PARTY_ERROR.CANT_KICK_SELF, self.auid)
                        
                elif self.kick_auid in self.party.pending_invites:
                    self.I.WS.removePartyMember(self.party, self.kick_auid, message="kicked")
                    if self.kick_auid not in self.party.kick_members:
                        self.party.kick_members.append(self.kick_auid)
                    self.response["ok"] = 1 # ок, done
                        
                else:
                    self.response["error"] = "not a party member or invite: kick_auid %d, party_id %d, members: %s, invites: %s" \
                        % (self.kick_auid, self.party_id, strList(self.party.members), strList(self.party.pending_invites.keys()))
                    self.replyPartyError("kick", PARTY_ERROR.NOT_A_PARTY_MEMBER_OR_INVITE, self.kick_auid)

##---------------------------------------------------------------------------------------------------

class PartyServiceDodgeAction(PartyServiceActionBase):
    action = 'pts_party_dodge'
    """ """
    def cmdStart(self):        
        # Проставляем banEndTime
        self.banEndTime = self.getIntParam("banEndTime", 0)
        _member = self.party.PartyData.findMemberByUid(self.auid)
        if _member:
            _member.banEndTime = self.banEndTime
            # апдейтим всей партии результат изменения:
            party_model_changes = self.I.WS.pickPendingPartyChanges(self.party) 
            self.I.WS.sendPartyBroadcast(self.party, "dodge", to_auids=self.party.members, json_PartyData=party_model_changes)
            self.response["ok"] = 1
        else:
            self.response["error"] = "not a party member: auid=%s, party_id=%s, members: %s" \
                % (self.auid, self.party_id, strList(self.party.members))
            self.replyPartyError("kick", PARTY_ERROR.NOT_A_PARTY_MEMBER_OR_INVITE, self.auid)

##---------------------------------------------------------------------------------------------------
class PartyServiceGoAction(PartyServiceActionBase):
    action = 'pts_party_go'
    """ """
    # --------------------------------------------------------------------------------
    # helper: проверяем, нет ли у нас текущих инвайтов
    def checkForActiveInvites(self):
        for member_id,member in self.party.PartyData.PartyMemberKeeper.iteritems():
            if member.isPending:
                return member.person.person_uid
        return None

    # --------------------------------------------------------------------------------
    # helper: проверяем, нет ли у нас героев с невалидным талант-сетом
    def checkForHeroesTS(self):
        for member_id,member in self.party.PartyData.PartyMemberKeeper.iteritems():
            if not member.isValidTS:
                return False
        return True
    
    # --------------------------------------------------------------------------------
    # helper: проверяем, нет ли у нас героев с невалидным значение мощи   
    def checkForHeroesForce(self, force_for_map):
        for member_id,member in self.party.PartyData.PartyMemberKeeper.iteritems():
            if not (member.heroForce >= force_for_map):
                return False
        return True        

    # --------------------------------------------------------------------------------
    # helper: проверяем, нет ли у нас забаненых игроков
    def checkForBan(self):
        for member_id,member in self.party.PartyData.PartyMemberKeeper.iteritems():
            if member.banEndTime > time.time():
                return False
        return True

    # --------------------------------------------------------------------------------
    # helper: проверяем, нет ли у нас игроков с турнирными аккаунтами
    def checkForDiasllowedMM(self, is_fixed_match, with_bots):
        if is_fixed_match or with_bots:
            return True
        for member_id,member in self.party.PartyData.PartyMemberKeeper.iteritems():
            if not member.isMMAllowed:
                return False
        return True

    # --------------------------------------------------------------------------------
    @separate_timing
    def cmdStart(self):         
        info("PartyServiceGoAction: from auid %s" % self.auid)
        if self.checkPartyMaster():
            # проверим, что 1) матчмейкинг сейчас не идет 2) у всех party members выбраны герои для pvp
            party_progress = {}
            party_timestamps = {}
            chosen_heroes = {}
            not_chosen_hero_member_auid = 0
            mm_progress_member_auid = 0
            mm_timestamp_member_auid = 0
            now = time.time()
            
            self.game_type = self.party.PartyData.mapID
            self.with_bots = self.party.PartyData.withBots
            self.rdy2manoeuvre = toint(self.getParam("rdy2manoeuvre", 0))
            self.only_guard = toint(self.getParam("only_guard", 0))
            locale = self.getParam("locale", "")
            geolocation = self.getParam("geolocation", "")
            
            is_fixed_match = self.party.is_fixed_match
            force_for_map = 0.0
            max_team_size = 0  
            can_use_enemies = False
            staticMap = self.I.SD.getStaticMap(self.game_type)
            self.talentset_id = toint(self.getParam("talentset_id", 0))
            if staticMap:
                if self.with_bots and (not is_fixed_match):
                    if not staticMap['mapWithBots']['dbid']:
                        self.response["error"] = "bots are not allowed for game_type=%s" % self.game_type
                        self.replyPartyError("go", PARTY_ERROR.BOTS_FORBIDDEN)
                        return  
                    staticMap = staticMap['mapWithBots']
                max_team_size = int(staticMap.get('teamSize', 0))
                can_use_enemies = (staticMap.get('PartyMode', "") == "AlliesAndEnemies")
                if staticMap['mapSettings'] and 'requiredHeroforce' in staticMap['mapSettings']:
                    force_for_map = float(staticMap['mapSettings']['requiredHeroforce'])

                
            else:
                err("staticMap not found for game_type=%s" % self.game_type)
                
            active_invite_uid = self.checkForActiveInvites()
            if active_invite_uid:
                self.response["error"] = "not all party members ready for pvp: party_id %d, members: %s, has active invites" \
                    % (self.party_id, strList(self.party.members))
                self.replyPartyError("go", PARTY_ERROR.NOT_READY_FOR_PVP, active_invite_uid)
                return     
            
            if not self.checkForBan():
                self.response["error"] = "player is retired"
                self.replyPartyError("go", PARTY_ERROR.USER_IS_RETIRED)
                return

            if not self.checkForDiasllowedMM(is_fixed_match, self.with_bots):
                self.response["error"] = "player with disallowed MM state is in a party"
                self.replyPartyError("go", PARTY_ERROR.TOURNAMENT_ACCOUNT_IN_PARTY)
                return

            for member_id, member in self.party.PartyData.PartyMemberKeeper.iteritems():
                auid = member.person.person_uid
                if member.person.InMatchmaking: # нет ли отличного от 0 прогресса mm-сессии
                    party_progress[ auid ] = 1
                    mm_progress_member_auid = auid # запомним любого юзера, который еще в матчмейкинге (чтобы вернуть в ошибке)
                elif (member.person.Status != FriendStatus.INCASTLE):
                    party_progress[ auid ] = MM.STATUS_NOT_IN_CASTLE
                    mm_progress_member_auid = auid # запомним любого юзера, который отсутствует в замке (чтобы вернуть в ошибке)

                hero_id = member.hero_id
                hero_crc = member.heroClassId
                if hero_id:
                    chosen_heroes[ auid ] = ClassDict(hero_id=hero_id, hero_crc=hero_crc) # должен быть выбран герой
                else:
                    not_chosen_hero_member_auid = auid # запомним любого юзера с не выбранным героем (чтобы вернуть в ошибке)
                        
            self.checkPartyMMProgress(party_progress, party_timestamps) # при необходимости перещелкиваем party.InMatchmaking
            
            if not party_progress:
                if len(chosen_heroes) == len(self.party.members):
                    if not self.checkForHeroesTS():
                        self.response["error"] = "some heroes has bad talent set"
                        self.replyPartyError("go", PARTY_ERROR.HAS_BAD_TS)
                        return          
                    if not self.checkForHeroesForce(force_for_map):
                        self.response["error"] = "some heroes has not enough force for map"
                        self.replyPartyError("go", PARTY_ERROR.NOT_ENOUGH_FORCE)
                        return

                    party_auids, enemy_auids = self.party.getFixedMatchSides()
                    if (is_fixed_match and (max_team_size == 0 or (max_team_size >= len(party_auids) and max_team_size >= len(enemy_auids)))) \
                    or ((not is_fixed_match) and (max_team_size == 0 or max_team_size >= len(self.party.members))):
                        same_heroes_auids = self.party.checkSimilarHeroes(self.I.Config.getMainConfig())
                        if not same_heroes_auids:                           
                            if (is_fixed_match and can_use_enemies) \
                            or ((not is_fixed_match) and (len(enemy_auids) == 0)):
                                # всё, заворачиваем
                                self.party.PartyData.InMatchmaking = True
                                
                                if (not is_fixed_match) and can_use_enemies:
                                    # добавить предупреждения о разбросе в званиях героев в пати
                                    master_auid = self.party.getMaster()
                                    master_member = self.party.PartyData.findMemberByUid(master_auid)
                                    ratings = []
                                    if master_member:
                                        for member_id, member in self.party.PartyData.members.iteritems():
                                            if member:
                                                ratings.append(member.heroRating)
                                        minRank, maxRank = self.I.SD.findMinMaxRanks(ratings)
                                        if self.game_type not in self.I.Config.getMainConfig().TournamentSettings.TOURNAMENT_MAP_LIST and (maxRank - minRank) >= 3:
                                            self.addPartyError(self.party.PartyData, EC.PARTY_BAD_RATING_RANGE, "bad rating range", self.auid)

                                        if not self.checkForPlayersLibrary():
                                            self.addPartyError(self.party.PartyData,
                                                               EC.NON_FULL_AWARD_FOR_SOME_PARTY_MEMBERS,
                                                               "one of party members has full library", self.auid)

                                        if max(ratings) >= MM.MAX_NO_MANOEUVRE_RATING:
                                            info("max party rating=%s >= MAX_NO_MANOEUVRE_RATING=%s, forcing rdy2manoeuvre flag=1 for master_auid=%s" \
                                                % (max(ratings), MM.MAX_NO_MANOEUVRE_RATING, master_auid))
                                            self.rdy2manoeuvre = 1
                                
                                party_model_changes = self.I.WS.pickPendingPartyChanges(self.party) 
                                
                                kwargs = dict(
                                    game_type = self.game_type,
                                    with_bots = int(self.with_bots),
                                    json_heroes = json_dumps(chosen_heroes),
                                    rdy2manoeuvre = self.rdy2manoeuvre, 
                                    only_guard = self.only_guard,
                                    json_PartyData = party_model_changes,
                                    is_fixed_match = is_fixed_match,
                                    party_auids = party_auids,
                                    enemy_auids = enemy_auids,
                                    locale = locale,
                                    geolocation = geolocation,
                                )


                                # рассылаем всей партии команду party_go:
                                self.I.WS.sendPartyBroadcast(self.party, "go", to_auids=self.party.members, **kwargs)
                                debug("session_id for afterparty statistics=%r",self.party.old_session_id)
                                # отошлем статистику
                                if self.party.old_session_id:
                                    membs = []
                                    for x in self.party.members:
                                        membs.append(dict(auid=x, sessionPersistentId=self.party.old_session_id, kicked=False, leaved=False))

                                    for x in self.party.leavers:
                                        membs.append(dict(auid=x, sessionPersistentId=self.party.old_session_id, kicked=False, leaved=True))

                                    for x in self.party.kick_members:
                                        membs.append(dict(auid=x, sessionPersistentId=self.party.old_session_id, kicked=True, leaved=False))

                                    info("send afterparty statistics=%r", membs )
                                    self.I.STATS.addAfterParty(True, membs)

                                # удаляем все pending invites (заодно там разошлются необх. извещения)
                                self.I.WS.removePendingInvites(self.party, "party matchmaking started")
                                
                                self.response["ok"] = 1
                            
                            else:
                                self.response["error"] = "bad party sides: party_auids=%s, enemy_auids=%s, is_fixed_match=%s" \
                                    % (party_auids, enemy_auids, is_fixed_match)
                                self.replyPartyError("go", PARTY_ERROR.BAD_FIXED_MATCH_SIDES, 0)
                        else:
                            self.response["error"] = "too many similar heroes: party_id %d, members: %s, same heroes auids: %s" \
                                % (self.party_id, strList(self.party.members), same_heroes_auids)
                            self.replyPartyError("go", PARTY_ERROR.SIMILAR_HEROES, same_heroes_auids[-1], same_heroes_auids=same_heroes_auids)
                    else:
                        self.response["error"] = "wrong number of players (%d) disallowed by map (max_team_size=%d and is_fixed_match=%s and can_use_enemies=%s)" \
                           % (len(self.party.members), max_team_size, is_fixed_match, can_use_enemies)
                        self.replyPartyError("go", PARTY_ERROR.TOO_BIG_PARTY, team_size = len(self.party.members), max_team_size = max_team_size)
                else:
                    self.response["error"] = "not all party members chosen heroes for pvp: party_id %d, members: %s, heroes: %s" \
                        % (self.party_id, strList(self.party.members), json_dumps(chosen_heroes))
                    self.replyPartyError("go", PARTY_ERROR.NO_CHOSEN_HEROES, not_chosen_hero_member_auid)
            else:
                self.response["error"] = "not all party members ready for pvp: party_id %d, members: %s, party_progress: %s" \
                    % (self.party_id, strList(self.party.members), json_dumps(party_progress))
                self.replyPartyError("go", PARTY_ERROR.NOT_READY_FOR_PVP, mm_progress_member_auid)
                
##---------------------------------------------------------------------------------------------------
        
class PartyServiceHeroAction(PartyServiceActionBase):
    action = 'pts_party_hero'
    """ """
    # ----------------------------------------
    def updatePartyMemberHero(self, party, json_tag):
        member = party.PartyData.findMemberByUid(self.auid)
        if member:
            if self.hero_id and self.hero_id != -1:
                member.isHeroChosen = True
            else:
                member.isHeroChosen = False
            if party.is_fixed_match:
                party_model_changes = self.I.WS.pickPendingPartyChanges(party) 
                # апдейтим всей партии (включая "врагов") результат изменения:
                args = dict(auid=self.auid)
                args[json_tag] = party_model_changes
                self.I.WS.sendPartyBroadcast(party, "hero", to_auids=party.members, **args)
            
            member.heroClassId = self.hero_crc
            member.heroLevel = self.hero_level
            member.heroForce = self.hero_force
            member.heroRating = self.hero_rating
            member.hero_id = self.hero_id
            member.isValidTS = self.hero_isValidTS
            member.skin_persistent_id = self.hero_skin_id
            member.ActiveTalentSet = self.hero_talentset_id
            member.IsAnimatedAvatar = bool( self.IsAnimatedAvatar)
            member.LeagueIndex = self.LeagueIndex
                
            party_model_changes = self.I.WS.pickPendingPartyChanges(party)

            # апдейтим своей стороне партии (тамбура) результат изменения:
            args = dict(auid=self.auid, hero_id=self.hero_id, hero_crc=self.hero_crc, hero_level=self.hero_level, hero_force=self.hero_force, hero_rating=self.hero_rating)
            args[json_tag] = party_model_changes
            to_auids = party.getFixedMatchSide(member.isEnemy)
            self.I.WS.sendPartyBroadcast(party, "hero", to_auids=to_auids, **args)

    # ----------------------------------------
    def updatePreviousHero(self, party, json_tag):
        if party:
            member = party.PartyData.findMemberByUid(self.auid)
            if member:
                # Таким странным кодом мы генерируем изменения на героя на самого себя, чтобы отослать клиенту и он бы вернул нашего героя обратно
                member.heroClassId = member.heroClassId
                member.heroLevel = member.heroLevel
                member.heroForce = member.heroForce
                member.heroRating = member.heroRating
                member.hero_id = member.hero_id
                member.isValidTS = member.isValidTS
                member.skin_persistent_id = member.skin_persistent_id
                member.ActiveTalentSet = member.ActiveTalentSet
                member.IsAnimatedAvatar = bool( self.IsAnimatedAvatar)
                member.LeagueIndex = self.LeagueIndex
                    
                party_model_changes = self.I.WS.pickPendingPartyChanges(party)

                # апдейтим своей стороне партии(тамбура) результат изменения:
                args = dict(auid=self.auid, hero_id=member.hero_id, hero_crc=member.heroClassId, hero_level=member.heroLevel, \
                    hero_force=member.heroForce, hero_rating=member.heroRating, )
                args[json_tag] = party_model_changes
                to_auids = party.getFixedMatchSide(member.isEnemy)
                self.I.WS.sendPartyBroadcast(party, "hero", to_auids=to_auids, **args)
        
    # ----------------------------------------
    # helper
    def getHeroParams(self):
        self.mm_progress = self.getIntParam("mm_progress", 0)
        self.hero_id = toint(self.getParam("hero_id"))
        self.hero_crc = toint(self.getParam("hero_crc"))
        self.hero_level = toint(self.getParam("hero_level"))
        self.hero_force = tofloat(self.getParam("hero_force"))
        self.hero_rating = tofloat(self.getParam("hero_rating"))
        self.hero_status = toint(self.getParam("hero_status"))
        self.hero_isValidTS = str2bool(self.getParam("hero_isValidTS"))
        self.hero_skin_id = toint(self.getParam("hero_skin_id"))
        self.hero_talentset_id = toint(self.getParam("talentset_id"))
        self.server = self.getParam("server", "")
        self.IsAnimatedAvatar = toint( self.getParam("IsAnimatedAvatar", 1))
        self.LeagueIndex = toint( self.getParam("LeagueIndex", 0))
                        
    # ----------------------------------------
    @separate_timing
    def cmdStart(self):
        self.getHeroParams()
        force_update = self.getParam("force_update", "")
        
        if force_update == "hero":
            self.updatePartyMemberHero(self.party, "json_PartyData")
        elif force_update == "prev":
            self.updatePreviousHero(self.party, "json_PartyData")
        else:
            # force_change: насильно сменить героя, не обращая внимания на прогресс матчмейкинга (например, когда после тамбура нужно вернуть исходного героя в поиск)
            force_change = self.getIntParam("force_change", 0)
            
            isPartyHasProgress = False
            if not force_change:
                party_progress = {}
                for member_id,member in self.party.PartyData.PartyMemberKeeper.iteritems():
                    auid = member.person.person_uid
                    if member.person.InMatchmaking: # нет ли отличного от 0 прогресса mm-сессии
                        party_progress[ auid ] = 1            
                isPartyHasProgress = bool(party_progress)
            
            if (force_change) or (not isPartyHasProgress):
                # меняем выбранного героя:
                self.updatePartyMemberHero(self.party, "json_PartyData")
            else:
                info("PartyServiceHeroAction: auid=%s, party_id=%s -- return previous hero, because of party_progress: %s" % (self.auid, self.party_id, party_progress))
                # партия в матчмейкинге; НЕ меняем выбранного героя (наоборот, рассылаем model changes с предыдущим выбранным героем)
                self.updatePreviousHero(self.party, "json_PartyData")
        
        self.response["ok"] = 1
            

##---------------------------------------------------------------------------------------------------
class PartyServiceProgressAction(PartyServiceActionBase):
    action = 'pts_party_progress'
    """ """
    def cmdStart(self):
        self.progress = self.getIntParam("progress", 0)
        self.person_status = self.getIntParam("person_status", 0)
        self.ec = self.getIntParam("party_ec", 0)
        
        person = self.party.PartyData.findPersonByUid(self.auid)
        if person:
            person.Status = self.person_status
            person.InMatchmaking = (self.progress != 0)
            if person.InMatchmaking:
                person.mmInfo.mmStartTime = int(time.time())
            
        member = self.party.PartyData.findMemberByUid(self.auid)
        if member:
            member.person.Status = self.person_status
            member.person.InMatchmaking = (self.progress != 0)
            if member.person.InMatchmaking:
                member.person.mmStartTime = int(time.time())
            
        if self.ec:
            # если mm_add одного из клиентов вернул ошибку, нужно разослать соответствующий PartyError
            self.addPartyError(self.party.PartyData, self.ec, "party_progress error", self.auid)
            self.checkPartyMMProgress() 
            # ну и выпилить всю партию из mm
            self.party.PartyData.InMatchmaking = False
            self.I.WS.sendPartyBroadcast(self.party, "stop", to_auids=self.party.members,
                                         message="party_progress_ec:%s" % self.ec, failed_auid=self.auid)
            
        else:
            self.checkPartyMMProgress()
        
        # апдейтим всей партии результат изменения:
        party_model_changes = self.I.WS.pickPendingPartyChanges(self.party) # при необходимости перещелкиваем party.InMatchmaking
        self.I.WS.sendPartyBroadcast(self.party, "progress", to_auids=self.party.members, auid=self.auid,
                                     progress=self.progress, json_PartyData=party_model_changes)
        self.response["ok"] = 1

##---------------------------------------------------------------------------------------------------
class PartyServiceReloginAction(PartyServiceActionBase):
    action = 'pts_party_relogin'
    """ """
    def cmdStart(self): 
        member = self.party.PartyData.findMemberByUid(self.auid)
        if member:
            party_dict = self.party.filterPartyMembers(self.party.PartyData.generateJsonDict(), member.isEnemy)
            party_model_init = [ MakeModelChangeString("init_party", "/", "init", party_dict) ]
            self.I.WS.sendPartyBroadcast(self.party, "party_relogin", to_auids=[self.auid], json_PartyData=party_model_init)
            
            # и повторно добавимся в парти-чат 
            self.I.CHAT.addUserGroup(self.auid, getGroupChatName(self.party_id), self.I.WS.onChatGroupRegister)

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class TamburServiceActionBase(PersonServerSubAction):
    # ----------------------------------------
    # WS прислал форвард команды клиента
    @action_timing
    def onStart(self):
        self.msg_id = self.nextMsgID() # на всякий случай сразу перещелкиваем на следующий msg_id (вдруг пофейлим какую-нибудь проверку параметров)
        if self.checkValidIntParam("auid"):
            ws_acc = self.I.WS.ws_accs.get(self.auid)
            if ws_acc:
                self.uid = ws_acc.uid
                self.response["uid"] = self.uid # продублируем в ответ, чтобы WS, если получит авто-отлуп, разобрался, к какому юзеру-команде-партии он относится
                
                if self.checkValidParam("game_id"):
                    if self.checkValidParam("allies_key"):
                        self.tambur_id = self.I.WS.getTamburId(self.game_id, self.allies_key)
                        self.tambur = self.I.WS.tamburs.get(self.tambur_id)
                        self.party_id = 0 # иначе replyPartyCmd и replyPartyError будут печалиться
            
                        if self.cmdStart(): # если child handler вернет что-то -- значит, потребовалась асинхронная обработка
                            return
            else:
                self.response["error"] = "unknown src auid: %s" % self.auid
        # fail:
        self.fin()

##---------------------------------------------------------------------------------------------------

class TamburAddAction(TamburServiceActionBase): 
    action = 'pts_tambur_add_person'
    """ """
    def cmdStart(self):
        if self.checkValidParam("json_person"):
            if self.checkValidIntParam("allies_count"):
                self.person_dict = json_loads(self.json_person)
                
                info('TamburAddAction: game_id %s, allies_key %s, existing tambur_id %s (auid %s)',self.game_id, self.allies_key, self.tambur_id, self.auid)
                if self.tambur:
                    if not self.tambur.party_id:
                        self.response["ok"] = 0
                        return None
                    if not self.I.WS.checkTamburSide(self.game_id, self.tambur_id):
                        warn("A player's tambur is not in tambur_sides. Auid %s, tambur_id %s, game_id %s, allies_key %s", self.auid, self.tambur_id, self.game_id, self.allies_key)
                        self.response["ok"] = 0
                        return None
                else:
                    self.tambur, self.tambur_id = self.I.WS.addTambur(self.game_id, self.allies_key)
                    
                join_notification_list = self.tambur.members[:] # разослать только предыдущим членам тамбура (свежеприсоединившемуся уйдет отдельный join_init)

                # добавляем к существующему тамбуру

                realPartyUid = toint(self.getParam("real_party_uid"))
                self.tambur.addMember(self.auid, self.person_dict, realPartyUid)
                self.response["tambur_id"] = self.tambur_id
                
                self.I.CHAT.addUserGroup(self.auid, getTamburChatName(self.tambur_id), self.I.WS.onChatGroupRegister)
                
                hero_id = toint(self.getParam("hero_id"))
                hero_crc = toint(self.getParam("hero_crc"))
                hero_level = toint(self.getParam("hero_level"))
                hero_force = tofloat(self.getParam("hero_force"))
                hero_rating = tofloat(self.getParam("hero_rating"))
                hero_status = toint(self.getParam("hero_status"))
                hero_skin_id = toint(self.getParam("hero_skin_id"))
                flag_type = toint(self.getParam("flag_type"))
                flag_persistent_id = self.getParam("flag_persistent_id")
                IsAnimatedAvatar = toint( self.getParam("IsAnimatedAvatar", 1))
                LeagueIndex = toint( self.getParam("LeagueIndex", 0))


                game_type = self.getParam("game_type")
                staticMap = self.I.SD.getStaticMap(game_type)
                useRanking = False
                
                can_use_enemies = False
                if staticMap:
                    can_use_enemies = (staticMap.get('PartyMode', "") == "AlliesAndEnemies")
                    mmS = staticMap.get("matchmakingSettings", None)
                    if mmS:
                        useRanking = mmS.get("useRanking", False)
                
                info("onTamburAdd (auid %s) hero_status=%s", self.auid, hero_status)
                
                member = self.tambur.PartyData.findMemberByUid(self.auid)
                if member:
                    member.hero_id = hero_id
                    member.heroClassId = hero_crc
                    member.heroLevel = hero_level
                    member.heroForce = hero_force
                    member.heroRating = hero_rating
                    member.isValidTS = True
                    member.skin_persistent_id = hero_skin_id
                    member.realPartyUid = realPartyUid
                    member.flagType = flag_type
                    member.flagPersistentId = flag_persistent_id
                    member.IsAnimatedAvatar = bool(IsAnimatedAvatar)
                    member.LeagueIndex = LeagueIndex
                else:
                    warn('NO TAMBUR MEMBER for auid %s' % self.auid)
                
                info('PS tambur members now: %s' % self.tambur.members)

                # Тамбур собрался, выставляем лимиты рейтинга
                self.tambur.allies_count = self.allies_count
                resultMaxForce = staticMap["mapSettings"].get('maxRequiredHeroForce', 0)
                resultMinForce = staticMap["mapSettings"].get('minRequiredHeroForce', 0)

                self.tambur.PartyData.ForceLimits.MaxForce = resultMaxForce
                self.tambur.PartyData.ForceLimits.MinForce = resultMinForce
                if len(self.tambur.members) == self.allies_count:
                    if can_use_enemies:
                        # теперь достанем тамбур для другой стороны игры (наши противники); если и там уже все собрались, установим общие границы рейтингов
                        other_tambur = self.I.WS.getOtherTambur(self.game_id, self.tambur_id)
                        if other_tambur:
                            other_tambur.PartyData.ForceLimits.MaxForce = resultMaxForce
                            other_tambur.PartyData.ForceLimits.MinForce = resultMinForce
                            if len(other_tambur.members) == other_tambur.allies_count:
                                # check tambur type for this map
                                if not useRanking:
                                    # old tambur (no ranking)
                                    maxRating = 0.0
                                    for mem_id, mem in self.tambur.PartyData.PartyMemberKeeper.iteritems():
                                        if mem.heroRating > maxRating:
                                            maxRating = mem.heroRating
                                    for mem_id, mem in other_tambur.PartyData.PartyMemberKeeper.iteritems():
                                        if mem.heroRating > maxRating:
                                            maxRating = mem.heroRating
                                        
                                    resultMaxRating = self.I.SD.getMaxRating(maxRating)
                                    #TODO:LOFIK: gatMainConfig -> getConfig(locale)
                                    resultMinRating = self.I.SD.getMinRating(maxRating, self.I.Config.getMainConfig().SHIFT_MIN_RANK)
                                    self.tambur.PartyData.RatingLimits.MaxRating = resultMaxRating
                                    self.tambur.PartyData.RatingLimits.MinRating = resultMinRating
                                
                                    other_tambur.PartyData.RatingLimits.MaxRating = resultMaxRating
                                    other_tambur.PartyData.RatingLimits.MinRating = resultMinRating

                                else:
                                    # new tambur (with ranking)
                                    maxRatingInAllTamburs = 0.0
                                    maxRatingInAllyTambur = 0.0
                                    maxRatingInEnemyTambur = 0.0
                                    for mem_id, mem in self.tambur.PartyData.PartyMemberKeeper.iteritems():
                                        if mem.heroRating > maxRatingInAllyTambur:
                                            maxRatingInAllyTambur = mem.heroRating
                                        if mem.heroRating > maxRatingInAllTamburs:
                                            maxRatingInAllTamburs = mem.heroRating
                                    for mem_id, mem in other_tambur.PartyData.PartyMemberKeeper.iteritems():
                                        if mem.heroRating > maxRatingInEnemyTambur:
                                            maxRatingInEnemyTambur = mem.heroRating
                                        if mem.heroRating > maxRatingInAllTamburs:
                                            maxRatingInAllTamburs = mem.heroRating
                                
                                    # https://confluence.nivalnetwork.com/display/dot/Borderlands+Matchmaking
                                    if maxRatingInAllTamburs < self.I.SD.data['AIGameLogic']['heroRanks']['highLevelsMMRating']:
                                        self.tambur.PartyData.RatingLimits.MaxRating = self.I.SD.getMaxRating(maxRatingInAllTamburs)
                                        self.tambur.PartyData.RatingLimits.MinRating = self.I.SD.getMinRating(maxRatingInAllyTambur, 2)
                                        other_tambur.PartyData.RatingLimits.MaxRating = self.I.SD.getMaxRating(maxRatingInAllTamburs)
                                        other_tambur.PartyData.RatingLimits.MinRating = self.I.SD.getMinRating(maxRatingInEnemyTambur, 2)
                                    else:
                                        self.tambur.PartyData.RatingLimits.MaxRating = self.I.SD.getCapMaxRating()
                                        self.tambur.PartyData.RatingLimits.MinRating = 1900
                                        other_tambur.PartyData.RatingLimits.MaxRating = self.I.SD.getCapMaxRating()
                                        other_tambur.PartyData.RatingLimits.MinRating = 1900

                                # придется отдельно разослать изменения MaxRating/MinRating для "чужого" тамбура
                                other_model_changes = self.I.WS.pickPendingPartyChanges(other_tambur)
                                self.I.WS.sendPartyBroadcast(other_tambur, "rating_limits", to_auids=other_tambur.members,
                                                             json_TamburData=other_model_changes)
                                
                                info("tambur rating limits SET for tambur_id=%s, game_id=%s: maxRating=%s, minRating=%s", self.tambur_id, self.game_id, self.tambur.PartyData.RatingLimits.MaxRating,
                                                                          self.tambur.PartyData.RatingLimits.MinRating)
                            else:
                                info("tambur rating limits: not all tambur members gathered for tambur_id=%s, game_id=%s: len(members)=%s, allies_count=%s",
                                    self.tambur_id, self.game_id, len(other_tambur.members), other_tambur.allies_count)
                        else:
                            info("tambur rating limits: no other tambur for tambur_id=%s, game_id=%s", self.tambur_id, self.game_id)
                    else:
                        self.tambur.PartyData.RatingLimits.MaxRating = 999999
                        self.tambur.PartyData.RatingLimits.MinRating = 1                        
                        self.tambur.PartyData.ForceLimits.MaxForce = 999999
                        self.tambur.PartyData.ForceLimits.MinForce = 1
                else:
                    info("tambur rating limits: not all tambur members gathered for tambur_id=%s, game_id=%s: len(members)=%s, allies_count=%s" , self.tambur_id, self.game_id, len(self.tambur.members), self.allies_count)
                    
                # отправить всем членам тамбура КРОМЕ только что вступившего -- сообщение "join" про нового member
                party_model_changes = self.I.WS.pickPendingPartyChanges(self.tambur)
                if join_notification_list:
                    self.I.WS.sendPartyBroadcast(self.tambur, "join", to_auids=join_notification_list, \
                        join_auid=self.auid, tambur_id=self.tambur_id,
                        members=strList(self.tambur.members), json_TamburData=party_model_changes) 
                        
                # а вот только что вступившему в тамбур надо:

                # 1) зачистить PartyData от ошибок (вообще механизма очистки от ошибок я не нашел, поэтому чистим здесь)
                self.tambur.PartyData.eraseAllErrors()

                # 2) полностью зачистить старую TamburData, выслать полный "init" новой PartyData 
                self.writeStringToResponse("initTamburData", "join_new_tambur", "/", "init", self.tambur.PartyData.generateJsonDict()) 
                temp = self.response.pop("initTamburData")
                if isinstance(temp, ResponseObject):
                    temp = temp.makeDict()
                tambur_model_init = self.I.MD.toJson(temp)

                ## info("self.tambur: %s, tambur_id: %d, self.tambur.PartyData: %s, PartyData.members: %s" \
                    ## % (self.tambur, self.tambur.party_id, self.tambur.PartyData, self.tambur.PartyData.members.keys()))
                    
                ## info("toJson: %s, model_init: %s" \
                        ## % (self.I.MD.toJson(self.tambur.PartyData), tambur_model_init))
                    
                self.replyPartyCmd("join_init_tambur", "joined new tambur", join_auid=self.auid, tambur_id=self.tambur_id, json_TamburData=tambur_model_init)
                    
                self.response["ok"] = 1
    
##---------------------------------------------------------------------------------------------------

class TamburDeleteAction(TamburServiceActionBase): 
    action = 'pts_tambur_delete'
    """ """
    def cmdStart(self):
        info('TamburDeleteAction: game_id %s, allies_key %s, existing tambur_id %s (auid %s)' % (self.game_id, self.allies_key, self.tambur_id, self.auid))
        if self.tambur and self.tambur.PartyData.party_uid:
            self.I.WS.deleteTambur(self.tambur)
            self.response["ok"] = 1
        
##---------------------------------------------------------------------------------------------------

class TamburReadyAction(TamburServiceActionBase): 
    action = 'pts_tambur_ready'
    """ """
    def cmdStart(self):
        info('TamburReadyAction: game_id %s, allies_key %s, existing tambur_id %s (auid %s)' % (self.game_id, self.allies_key, self.tambur_id, self.auid))
        if self.tambur:
            self.foes_ready = self.getIntParam("foes_ready", 0)
            self.member_ready = self.getIntParam("ready", 0)
            pd = self.tambur.PartyData
            member = pd.findMemberByUid(self.auid)
            if member:
                if member.isValidTS:
                    do_update = False
                    if (pd.foes_ready != self.foes_ready):
                        pd.foes_ready = self.foes_ready
                        do_update = True
                    if self.member_ready and (not member.isTamburReady):
                        member.isTamburReady = True
                        do_update = True

                    if do_update:
                        # рассылаем изменения всем членам тамбура:
                        party_model_changes = self.I.WS.pickPendingPartyChanges(self.tambur)
                        self.I.WS.sendPartyBroadcast(self.tambur, "tambur_ready", to_auids=self.tambur.members,
                                                     ready_auid=self.auid, json_TamburData=party_model_changes)
                    else:
                        info("tambur %s: values already set (member auid=%s is ready, foes_ready=%s)" % (self.tambur_id, self.auid, self.foes_ready))

                    self.response["ok"] = 1
                else:
                    warn("tambur %s wrong talentset for person with auid=%s" % (self.tambur_id, self.auid))
            else:
                warn("tambur %s failed to find person with auid=%s" % (self.tambur_id, self.auid))

##---------------------------------------------------------------------------------------------------

class TamburHeroAction(TamburServiceActionBase, PartyServiceHeroAction):
    action = 'pts_tambur_hero'
    """ """
    def cmdStart(self):
        info("TamburHeroAction: auid=%s, tambur=%s", self.auid, self.tambur)
        self.getHeroParams()
        args = self.getFlatParams(except_list=["action", "auid", "server", "game_id", "allies_key", "mm_progress"])
        party_id = self.getIntParam("party_id", 0)

        # 1) проверим, что мы еще не нажали ready
        member = self.tambur.PartyData.findMemberByUid(self.auid)
        if member.isTamburReady and member.heroClassId != self.hero_crc:
            # FAIL: уже нажали ready
            self.response["error"] = "already sent mm_ready for tambur member auid=%s" % (self.auid)
            return self.replyPartyError("hero", PARTY_ERROR.ALREADY_MM_READY, self.auid)
            
        # 2) проверим, что у других юзеров нет такого героя
        other_members = self.tambur.members[:]
        other_members.remove(self.auid)
        for auid in other_members:
            other = self.tambur.PartyData.findMemberByUid(auid)
            if other and (other.heroClassId == self.hero_crc) :
                self.updatePreviousHero(self.tambur, "json_TamburData")
                if party_id:
                    self.I.PARTY.sendPartyCmd(self.auid, self.server, "party_hero", None, force_update="prev", **args)
                warn("TamburHeroAction: similar heroes, auid=%s has hero_crc=%s", other.person.person_uid, other.heroClassId )
                return 
        # и что герой не запрещен для игры героев в тамбуре
        sameheroes = self.tambur.checkForbiddenPartyHeroes(self.auid, other_members, self.tambur.PartyData, self.hero_crc, self.I.Config.getMainConfig())
        if sameheroes:
            self.updatePreviousHero(self.tambur, "json_TamburData")
            if party_id:
                self.I.PARTY.sendPartyCmd(self.auid, self.server, "party_hero", None, force_update="prev", **args)
            warn("TamburHeroAction: forbidden heroes pair, auids %r", sameheroes)
            return

        # 3) Проверим, что герой - гвардейский и правильного ранка:
        limits = self.tambur.PartyData.RatingLimits
        info("TamburHeroAction:  self.hero_status=%s, self.hero_rating=%s, tambur.MinRating=%s, tambur.MaxRating=%s", self.hero_status, self.hero_rating, limits.MinRating, limits.MaxRating)
        if (limits.MinRating == 0 and limits.MaxRating == 0) or limits.MinRating > self.hero_rating or limits.MaxRating < self.hero_rating:
            # Если можем - возвращаем старого
            self.updatePreviousHero(self.tambur, "json_TamburData")
            if party_id:
                self.I.PARTY.sendPartyCmd(self.auid, self.server, "party_hero", None, force_update="prev", **args)
            warn("TamburHeroAction: bad rating limit")
            return

        # 4) Проверим, что герой подходит по мощи:
        forces = self.tambur.PartyData.ForceLimits
        info("TamburHeroAction:  self.hero_status=%s, self.hero_force=%s, tambur.MinForce=%s, tambur.MaxForce=%s", self.hero_status, self.hero_force, forces.MinForce, forces.MaxForce)
        if (forces.MinForce != 0 and forces.MaxForce !=0) and not( forces.MinForce <= self.hero_force <= forces.MaxForce ):
            # Если можем - возвращаем старого
            self.updatePreviousHero(self.tambur, "json_TamburData")
            if party_id:
                self.I.PARTY.sendPartyCmd(self.auid, self.server, "party_hero", None, force_update="prev", **args)
            warn("TamburHeroAction: bad force limit")
            return

        # ок, меняем героя
        self.updatePartyMemberHero(self.tambur, "json_TamburData")
        if party_id:
            self.I.PARTY.sendPartyCmd(self.auid, self.server, "party_hero", None, force_update="hero", **args)

        self.response["ok"] = 1

##---------------------------------------------------------------------------------------------------

class AfterpartyProcessMemberAction(AfterpartyActionBase):
    action = 'pts_afterparty_process_member'
    intParams = ("auid", "session_id", "agreed", "party_id", "lock_end_time", "with_bots", "flagType")

    """ Обрабатываем поступившую заявку: заполняем инфо, если игрок хочет играть в той же пати
        или ставим флаг "не согласен" """
    def onStart(self):
        info("AfterpartyProcessMemberAction.onStart %r", self.arguments)
        if self.checkIntParams():
            self.getActionParams()
            afterparty = self.I.WS.parties.get(self.party_id)
            if not afterparty:
                # нету партии; надо создать новый PartyContext
                afterparty = PartyContext(self.auid, self.party_id,
                                          self.game_type,
                                          self.with_bots,
                                          self.flagType,
                                          self.flagPersistentId,
                                          self.isMMAllowed,
                                          self.isInventoryFull,
                                          self.isLeaver,
                                          0,
                                          self.tournamentDynQuestId,
                                          self.dependedTournamentQuests,
                                          self.I.WS,
                                          self.person_dict,
                                          self.agreed,
                                          old_session_id=self.session_id)
                self.I.WS.parties[self.party_id] = afterparty
                #self.I.WS.resetPendingChanges(afterparty)
                self.fillAfterparty(afterparty)

                # Если человек согласился, то выдаём ему обновления пати-даты.
                if self.agreed:
                    self.I.CHAT.addUserGroup(self.auid, getGroupChatName(self.party_id), self.I.WS.onChatGroupRegister)
                    # для только что созданной партии надо выслать мастеру полный "init" новой PartyData
                    party_model_init = self.I.WS.WriteModelChangeString("create_party", "/", "init", afterparty.PartyData.generateJsonDict())
                    self.I.WS.sendServerPartyCmd(self.auid, "create_init", "created same party after battle",
                                                 party_id=self.party_id, master_auid=afterparty.members[0],
                                                 json_PartyData=party_model_init)  # перекладываем из response в pending events
                else:
                    self.removeMember(afterparty, self.auid)
                    # надо очистить pending_events

            else:
                if self.agreed:
                    member = afterparty.PartyData.findMemberByUid(self.auid)
                    person = afterparty.PartyData.findPersonByUid(self.auid)
                    if member and person:
                        self.I.WS.updatePersonFromDict(person, self.person_dict)
                        member.agreed = True
                        member.isPending = False
                        member.flagType = self.flagType
                        member.flagPersistentId = self.flagPersistentId
                        member.isMMAllowed = self.isMMAllowed
                        member.person.InMatchmaking = False
                        member.isInventoryFull = self.isInventoryFull
                        member.isLeaver = self.isLeaver
                        member.tournamentDynQuestId=self.tournamentDynQuestId
                        member.dependedTournamentQuests = self.dependedTournamentQuests
                    else:
                        # Кажется, кто-то левый прислал нам запрос
                        warn("AfterpartyProcessMemberAction: Person with auid %d was not found in PartyData for party_id %d",
                             self.auid, afterparty.party_id)
                        self.response["ok"] = 1  # сделаем вид, что не заметили
                        self.fin()
                        return

                    self.I.CHAT.addUserGroup(self.auid, getGroupChatName(self.party_id), self.I.WS.onChatGroupRegister)
                    party_model_init = self.createInitChanges(afterparty)
                    self.I.WS.sendPartyBroadcast(afterparty, "create_init", message="joined same party after battle",
                                                 to_auids=[self.auid],
                                                 master_auid=afterparty.members[0], join_auid=self.auid,
                                                 members=strList(afterparty.members), json_PartyData=party_model_init)
                else:
                    self.removeMember(afterparty, self.auid)

                # отправим всем членам партии сообщение про нового member
                join_notification_list = [member.person.person_uid for _id, member in afterparty.PartyData.members.iteritems()
                                          if member.agreed and member.person.person_uid != self.auid]
                party_model_changes = self.I.WS.pickPendingPartyChanges(afterparty)
                self.I.WS.sendPartyBroadcast(afterparty, "change", message="afterparty member status changed",
                                             to_auids=join_notification_list, join_auid=self.auid,
                                             master_auid=afterparty.members[0] if afterparty.members else self.auid,
                                             members=strList(afterparty.members), json_PartyData=party_model_changes)
            self.response["ok"] = 1  # ок, приняли к исполнению
        self.fin()

    def getActionParams(self):
        self.game_type = self.getParam("game_type", "")
        self.flagPersistentId = self.getParam("flagPersistentId")
        self.isMMAllowed = self.getBoolParam("isMMAllowed", True)
        self.isInventoryFull = self.getBoolParam("isInventoryFull", False)
        self.allies_keys = self.getParam("allies_keys") #self.getJsonParam("allies_keys")

        self.person_dict = self.getJsonParam("person_dict")
        self.isLeaver = self.getBoolParam("isLeaver", False)
        self.tournamentDynQuestId=self.getIntParam("tournamentDynQuestId",-1)
        self.dependedTournamentQuests = self.getParam("dependedTournamentQuests", "-1")


class AfterpartyProcessPartyAction(AfterpartyActionBase):
    action = 'pts_afterparty_process_party'
    intParams = ("auid", "session_id", "agreed", "party_id", "lock_end_time", "with_bots", "flagType", "old_party_id")

    """ Обрабатываем поступившую заявку: заполняем инфо, если игрок хочет играть в той же пати
        или ставим флаг "не согласен" """
    def onStart(self):
        info("AfterpartyProcessPartyAction.onStart %r", self.arguments)
        if self.checkIntParams():
            self.getActionParams()
            self.old_party = self.getParam("old_party")
            afterparty = self.I.WS.parties.get(self.party_id)
            if not afterparty:
                # Если вдруг нету партии, надо создать новый PartyContext
                afterparty = PartyContext(self.auid,
                                          self.party_id,
                                          self.game_type,
                                          self.with_bots,
                                          self.flagType,
                                          self.flagPersistentId,
                                          self.isMMAllowed,
                                          self.isInventoryFull,
                                          self.isLeaver,
                                          0,
                                          self.tournamentDynQuestId,
                                          self.dependedTournamentQuests,
                                          self.I.WS,
                                          self.person_dict,
                                          self.agreed,
                                          old_session_id=self.session_id)
                self.I.WS.parties[self.party_id] = afterparty
                self.fillAfterparty(afterparty)
                # Получим данные по другой пати и либо уберём, либо добавим новых участников (зависит от agreed)
                return self.I.PARTY.getPartyData(self.old_party_id, self.onPartyDataFound, remove_party=self.agreed)
            else:
                # Если на афтерпати согласился лидер какой-то предыдущей пати, будем собирать новую в её контексте
                if self.old_party_id == self.party_id:
                    debug("AfterpartyProcessPartyAction: creating party from old party")
                    # пометим своих ребят как согласившихся и сбросим героев
                    for _id, member in afterparty.PartyData.members.items():
                        member.agreed = True
                        member.isPending = False
                        member.hero_id = 0
                        member.heroClassId = 0
                        member.heroForce = 0.0
                        member.heroLevel = 0
                        member.heroRating = 0.0
                        member.isHeroChosen = False
                    afterparty.old_session_id = self.session_id
                    self.fillAfterparty(afterparty)
                # Другой пати-лидер уже сделал свою пати основной
                else:
                    debug("AfterpartyProcessPartyAction: searching for joining party's data")
                    return self.I.PARTY.getPartyData(self.old_party_id, self.onPartyDataFound, remove_party=self.agreed)

                # отправим всем членам партии сообщение про нового member
                party_model_changes = self.I.WS.pickPendingPartyChanges(afterparty)
                self.I.WS.sendPartyBroadcast(afterparty, "change", master_auid=afterparty.members[0],
                                             members=strList(afterparty.members), json_PartyData=party_model_changes)
            self.response["ok"] = 1  # ок, приняли к исполнению
        self.fin()

    def onPartyDataFound(self, response):
        debug("AfterpartyProcessPartyAction.onPartyDataFound response %r", response)
        afterparty = self.I.WS.parties.get(self.party_id)
        if afterparty:
            invited_auids = []
            if response and response.get("ok") and response.get("party_dict"):
                oldPartyDataDict = json_loads(response["party_dict"])
                oldPartyData = PartyData()
                oldPartyData.load(oldPartyDataDict)
                oldPartyData.init(None)
                if self.agreed:
                    debug("AfterpartyProcessPartyAction: joining old party to afterparty")
                    party_size = len(oldPartyData.members)
                    for _id, oldMember in oldPartyData.members.iteritems():
                        member = afterparty.PartyData.findMemberByUid(oldMember.person.person_uid)
                        person = afterparty.PartyData.findPersonByUid(oldMember.person.person_uid)
                        if member and person:
                            member.agreed = True
                            member.isPending = False
                            member.copyMember(oldMember)
                            self.I.WS.updatePersonFromDict(person, oldMember.person.generateJsonDict().get("Friend", {}))
                            self.I.CHAT.addUserGroup(oldMember.person.person_uid, getGroupChatName(self.party_id),
                                                     self.I.WS.onChatGroupRegister)
                            self.I.FRIENDS.sendPartyCmd(oldMember.person.person_uid, None, "party_set_id", None,
                                                        party_id=self.party_id)
                    # Не пора ли сменить лидера?
                    if afterparty.max_party_size < party_size:
                        if len(afterparty.members) > 1:
                            debug("AfterpartyProcessPartyAction, changing party owner")
                            debug("AfterpartyProcessPartyAction members before: %r", afterparty.members)
                            _next_master = afterparty.PartyData.findMemberByUid(self.auid)
                            afterparty.PartyData.owner = _next_master
                            afterparty.members.remove(self.auid)
                            afterparty.members.append(afterparty.members[0])
                            afterparty.members[0] = self.auid
                            afterparty.max_party_size = len(afterparty.members)
                            debug("AfterpartyProcessPartyAction members after: %r", afterparty.members)
                    # Надо разослать изменения вновь прибывшим
                    invited_auids = [oldMember.person.person_uid for _id, oldMember in oldPartyData.members.iteritems()]
                    party_model_init = self.I.WS.WriteModelChangeString("create_party", "/", "init", afterparty.PartyData.generateJsonDict())
                    self.I.WS.sendPartyBroadcast(afterparty, "create_init", to_auids=invited_auids,
                                                 master_auid=afterparty.members[0],
                                                 members=strList(afterparty.members), json_PartyData=party_model_init)

                else:
                    for _id, oldMember in oldPartyData.members.iteritems():
                        self.removeMember(afterparty, oldMember.person.person_uid)

            # Что-то накрылось, уберём из пати хотя бы лидера
            else:
                self.removeMember(afterparty, self.auid)

            if afterparty.members:
                join_notification_list = [member.person.person_uid for _id, member in afterparty.PartyData.members.iteritems()
                                          if member.agreed and member.person.person_uid not in invited_auids]
                party_model_changes = self.I.WS.pickPendingPartyChanges(afterparty)
                self.I.WS.sendPartyBroadcast(afterparty, "change", to_auids=join_notification_list,
                                             master_auid=afterparty.members[0], members=strList(afterparty.members),
                                             json_PartyData=party_model_changes)
            else:
                info("Party %d is empty", self.party_id)
        else:
            warn("Party %d was disbanded", self.party_id)
        self.response["ok"] = 1  # ок, приняли к исполнению
        self.fin()

    def getActionParams(self):
        self.game_type = self.getParam("game_type", "")
        self.flagPersistentId = self.getParam("flagPersistentId")
        self.isMMAllowed = self.getBoolParam("isMMAllowed", True)
        self.isInventoryFull = self.getBoolParam("isInventoryFull", False)
        self.allies_keys = self.getParam("allies_keys") #self.getJsonParam("allies_keys")
        self.person_dict = self.getJsonParam("person_dict")
        self.isLeaver = self.getBoolParam("isLeaver", False)
        self.tournamentDynQuestId=self.getIntParam("tournamentDynQuestId",-1)
        self.dependedTournamentQuests = self.getParam("dependedTournamentQuests", "-1")


class PartyGetDataAction(PersonServerSubAction):
    action = 'pts_party_get_data'

    def onStart(self):
        self.party_id = self.getIntParam("party_id")
        party = self.I.WS.parties.get(self.party_id)
        if party:
            self.response["party_dict"] = json_dumps(party.PartyData.generateJsonDict())
            if self.getBoolParam("remove_party"):
                # удаление партии будет апдейтить в model changes как сброс uid-а в 0
                party.PartyData.party_uid = 0
                # удаляем участников из чатов и т.д.
                for _id, member in party.PartyData.members.iteritems():
                    self.I.CHAT.removeUserGroup(member.person.person_uid, getGroupChatName(self.party_id), self.I.WS.onChatGroupUnregister)
                    self.I.FRIENDS.removePartyId(member.person.person_uid, self.party_id, member.person.person_uid)

                self.I.WS.parties.pop(self.party_id)
            self.response["ok"] = 1
        self.fin()



##---------------------------------------------------------------------------------------------------

class AfterpartyProcessAction(PersonServerSubAction):
    action = 'pts_afterparty_process'
    intParams = ("auid", "session_id", "party_id", "agreed", "with_bots", "flagType", "lock_end_time", "is_leader",
                 "old_party_id")
    """ Перенаправляет на PartyService, для которого актуален новый party_id """
    def onStart(self):
        info('AfterpartyProcessAction.onStart %r', self.arguments)
        if self.checkIntParams():
            self.allies_keys = self.getParam("allies_keys")
            self.isLeaver = self.getBoolParam("isLeaver", False)
            self.tournamentDynQuestId=self.getIntParam("tournamentDynQuestId",-1)
            self.dependedTournamentQuests = self.getParam("dependedTournamentQuests", "-1")
            self.old_party = self.getParam("old_party")
            if self.is_leader:
                return self.I.PARTY.addPartyToAfterparty(self.party_id, self.auid, self.session_id,
                                      self.allies_keys,
                                      self.agreed, self.onNewMemberProcessed,
                                      person_dict=self.getParam("person_dict"),
                                      game_type=self.getParam("game_type"),
                                      with_bots=self.with_bots,
                                      flagType=self.flagType,
                                      flagPersistentId=self.getParam("flagPersistentId"),
                                      isMMAllowed=self.getBoolParam("isMMAllowed"),
                                      is_leader=self.is_leader,
                                      isInventoryFull=self.getBoolParam("isInventoryFull"),
                                      lock_end_time=self.lock_end_time,
                                      old_party_id=self.old_party_id,
                                      isLeaver=self.isLeaver,
                                      tournamentDynQuestId=self.tournamentDynQuestId,
                                      dependedTournamentQuests=self.dependedTournamentQuests,
                                      old_party=self.old_party)
            else:
                return self.I.PARTY.addPersonToAfterparty(self.party_id, self.auid, self.session_id,
                                                      self.allies_keys,
                                                      self.agreed, self.onNewMemberProcessed,
                                                      person_dict=self.getParam("person_dict"),
                                                      game_type=self.getParam("game_type"),
                                                      with_bots=self.with_bots,
                                                      flagType=self.flagType,
                                                      flagPersistentId=self.getParam("flagPersistentId"),
                                                      isMMAllowed=self.getBoolParam("isMMAllowed"),
                                                      is_leader=self.is_leader,
                                                      isInventoryFull=self.getBoolParam("isInventoryFull"),
                                                      lock_end_time=self.lock_end_time,
                                                      isLeaver=self.isLeaver,
                                                      tournamentDynQuestId=self.tournamentDynQuestId,
                                                      dependedTournamentQuests=self.dependedTournamentQuests,
                                                      old_party_id=self.old_party_id,
                                                      old_party=self.old_party)
        self.fin()


    def onNewMemberProcessed(self, response):
        if response and response.get("ok"):
            self.response["ok"] = 1
            self.response["party_id"] = self.party_id
        else:
            warn("Failed to add member %d to afterparty with session_id %d", self.auid, self.session_id)
        self.fin()

class PartyRemoveAfterpartyIdAction(PersonServerSubAction):
    action = 'pts_afterparty_remove_id'
    intParams = ("session_id", "party_id")
    """ Затираем id, так как afterparty либо развалилась, либо стала полноценной party """

    def onStart(self):
        info('PartyRemoveAfterpartyIdAction.onStart %r', self.arguments)
        if self.checkIntParams():
            parties = self.I.WS.afterparties.get(self.session_id)
            if parties:
                for party in parties[:]:
                    if self.party_id == party["party_id"]:
                        parties.remove(party)
                if not parties:
                    self.I.WS.afterparties.pop(self.session_id)
        self.response["ok"] = 1
        self.fin()

class GetAfterpartyIdAction(PersonServerSubAction):
    action = 'pts_get_afterparty_id'
    intParams = ('auid', 'session_id', 'old_party_id')

    """ Выдаем id для afterparty и заносим информацию о ней"""
    def onStart(self):
        info('GetAfterpartyIdAction.onStart %r', self.arguments)
        if self.checkIntParams():
            self.allies_keys = self.getParam("allies_keys")
            self.party_id = None
            new_parties = self.I.WS.afterparties.get(self.session_id)
            debug("GetAfterpartyIdAction.onStart self.I.WS.afterparties %r", self.I.WS.afterparties)
            debug("GetAfterpartyIdAction.onStart new_parties %r", new_parties)

            # На одну сессию может появитсья 2 афтерпати, надо найти свою
            if new_parties:
                for party in new_parties:
                    # ищем первую подходящую партию. где есть наш ауид.
                    if self.auid in party["allies"]:
                        self.party_id = party["party_id"]
                        break


            # Никто из союзников ещё не создал новую пати, так будем же первыми!
            if not self.party_id:
                if not self.old_party_id:
                    self.party_id = self.I.WS.nextInt64GUID("party")
                else:
                    self.party_id = self.old_party_id
                party_dict = {"party_id": self.party_id, "allies": []}
                allies = json_loads(self.allies_keys).split(",")
                for auid in allies:
                    party_dict["allies"].append(int(auid))
                if not new_parties:
                    self.I.WS.afterparties[self.session_id] = [party_dict]
                else:
                    self.I.WS.afterparties[self.session_id].append(party_dict)

            debug("GetAfterpartyIdAction.onStart self.I.WS.afterparties %r", self.I.WS.afterparties)
            debug("GetAfterpartyIdAction.onStart  self.party_id %r",  self.party_id)

            self.response["ok"] = 1
            self.response["party_id"] = self.party_id
            self.fin()
            return
        else:
            self.errorResponse(EC.BAD_PARAM, "Bad param for pts_get_afterparty_id action")
            return

class PartyUpdateLeaverInfoAction(PersonServerSubAction):
    action = 'pts_party_update_leaver_info'
    intParams = ('auid','party_id', )

    """ Выдаем id для afterparty и заносим информацию о ней"""
    def onStart(self):
        info('PartyUpdateLeaverInfoAction.onStart %r', self.arguments)
        if self.checkIntParams():
            self.isLeaver = self.getBoolParam("isLeaver", False)
            party = self.I.WS.parties.get(self.party_id)
            if party:
                member = party.PartyData.findMemberByUid(self.auid)
                if member:
                    member.isLeaver = self.isLeaver
                    party_model_changes = self.I.WS.pickPendingPartyChanges(party)

                    args = dict(auid=self.auid)
                    args["json_PartyData"] = party_model_changes
                    debug("PartyUpdateLeaverInfoAction.onStart json_PartyData: %r", party_model_changes)
                    self.I.WS.sendPartyBroadcast(party, "change", to_auids=party.members, change_auid=self.auid,
                                                 master_auid=party.members[0], members=strList(party.members),
                                        json_PartyData=party_model_changes)
                else:
                    self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Party's member is not found")
                    return
            else:
                self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Party is not found")
                return

        self.response['ok'] = 1
        self.fin()
        return

class PartyUpdateTournamentInfoAction(PersonServerSubAction):
    action = 'pts_party_update_tournament_info'
    intParams = ('auid','party_id', )

    """ Выдаем id для afterparty и заносим информацию о ней"""
    def onStart(self):
        info('PartyUpdateTournamentInfoAction.onStart %r', self.arguments)
        if self.checkIntParams():
            self.tournamentDynQuestId=self.getIntParam("tournamentDynQuestId", -1)
            self.dependedTournamentQuest=self.getParam("dependedTournamentQuests","-1")

            party = self.I.WS.parties.get(self.party_id)
            if party:
                member = party.PartyData.findMemberByUid(self.auid)
                if member:
                    member.tournamentDynQuestId = self.tournamentDynQuestId
                    member.dependedTournamentQuest = self.dependedTournamentQuest

                    party_model_changes = self.I.WS.pickPendingPartyChanges(party)

                    args = dict(auid=self.auid)
                    args["json_PartyData"] = party_model_changes
                    debug("PartyUpdateTournamentInfoAction.onStart json_PartyData: %r", party_model_changes)
                    self.I.WS.sendPartyBroadcast(party, "change", to_auids=party.members, change_auid=self.auid,
                                                 master_auid=party.members[0], members=strList(party.members),
                                        json_PartyData=party_model_changes)
                else:
                    self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Party's member is not found")
                    return
            else:
                self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Party is not found")
                return

        self.response['ok'] = 1
        self.fin()
        return

class PartyUpdateTalentSetInfoAction(PersonServerSubAction):
    action = 'pts_party_update_talentset_info'
    intParams = ('auid','party_id', )

    """ Выдаем поменялся талансет у героя заносим ифно об этом"""
    def onStart(self):
        info('PartyUpdateTalentSetInfoAction.onStart %r', self.arguments)
        if self.checkIntParams():
            self.activeTalentSet = self.getIntParam("activeTalentSet")

            party = self.I.WS.parties.get(self.party_id)
            if party:
                member = party.PartyData.findMemberByUid(self.auid)
                if member:
                    member.ActiveTalentSet = self.activeTalentSet

                    party_model_changes = self.I.WS.pickPendingPartyChanges(party)

                    args = dict(auid=self.auid)
                    args["json_PartyData"] = party_model_changes
                    debug("PartyUpdateTalentSetInfoAction.onStart json_PartyData: %r", party_model_changes)
                    self.I.WS.sendPartyBroadcast(party, "change", to_auids=party.members, change_auid=self.auid,
                                                 master_auid=party.members[0], members=strList(party.members),
                                        json_PartyData=party_model_changes)
                else:
                    self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Party's member is not found")
                    return
            else:
                self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Party is not found")
                return

        self.response['ok'] = 1
        self.fin()
        return


##---------------------------------------------------------------------------------------------------

class PartyServiceHandler(JsonHandler):
    """ обрабатываем только внутренние запросы от рабочих серверов """
    
    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
        # --- служебное ----
        'check_alive': 'onCheckWebServerAlive', # base JsonHandler: умеем отвечать, что мы живы
        'get_stat':  'onGetStat',
        'reload_multi_config': 'onReloadMultiConfigWithMainSD', # base JsonHandler: умеем перегружать logic_cfg+StaticData со всеми внутренностями
        'peer': PeerServerStatusAction, # base JsonHandler: апдейтим статус peer WS-ок
        'clear_addr_info': 'onClearAddrInfoCache', # base JsonHandler: умеем чистить кэш addrinfo (чтобы заново резолвить адреса после перестройки DNS)        
        # --- friend_server forwards -----
        'pts_update_game_data': PartyUpdateGameDataAction,
        'pts_update_person_status': PartyUpdatePersonStatusAction,
        'pts_unsubscribe': PartyUnsubscribeAction,
        'pts_update_ws_acc': UpdateWsAccAction,
        # --- party commands (from FS) ---
        'pts_party_invite': PartyServiceInviteAction,
        'pts_party_accept': PartyServiceAcceptAction,
        'pts_party_decline': PartyServiceDeclineAction,
        'pts_party_disband': PartyServiceDisbandAction,
        'pts_party_kick': PartyServiceKickAction,
        'pts_party_dodge': PartyServiceDodgeAction,
        'pts_party_go': PartyServiceGoAction,
        'pts_party_hero': PartyServiceHeroAction,
        'pts_party_progress': PartyServiceProgressAction,
        'pts_party_relogin': PartyServiceReloginAction,
        'pts_party_map': PartyServiceMapAction,
        'pts_party_flag': PartyServiceFlagAction,
        'pts_party_inventory_is_full': PartyServiceInventoryIsFullAction,
        'pts_party_get_data': PartyGetDataAction,
        'pts_party_update_leaver_info': PartyUpdateLeaverInfoAction,
        'pts_party_update_tournament_info': PartyUpdateTournamentInfoAction,
        'pts_party_update_talentset_info': PartyUpdateTalentSetInfoAction,
        # --- afterparty commands ---
        'pts_afterparty_process': AfterpartyProcessAction,
        'pts_afterparty_process_member': AfterpartyProcessMemberAction,
        'pts_afterparty_process_party': AfterpartyProcessPartyAction,
        'pts_afterparty_remove_id': PartyRemoveAfterpartyIdAction,
        'pts_get_afterparty_id':GetAfterpartyIdAction,
        # --- tambur commands ---
        'pts_tambur_add_person': TamburAddAction,
        'pts_tambur_delete': TamburDeleteAction,
        'pts_tambur_ready': TamburReadyAction,
        'pts_tambur_hero': TamburHeroAction, # в случае, когда героя меняют в тамбуре, другая логика обработки (лимиты по рейтингу), а партию извещаем о факте изменения

    }

    def onGetStat(self):
        self.response["ok"] = 1
        self.response["usersCount"] = len(self.I.WS.users)
        self.response["afterpartiesCount"] = len(self.I.WS.afterparties)
        self.response["tambursCount"] = len(self.I.WS.tamburs)
        self.response["fail_requests"] = self.I.WS.fail_requests
        self.fin()

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class PartyService(BasePersonService, ICSVActionTimingWriter, ITornadoServer, FakePartyData):
    """ Добываем из социального аггрегатора пользовательские данные (ник, фото и т.п.) и предоставляем их рабочим серверам """
    server_type_name = "pts"
    
    _aggregatorProperties = { 
        "nick": utf8convert,
        "fame": int,
        "fraction": int,
    }
        
    TAMBUR_DELETE_PERIOD = 60.0 

    def __init__(self, **kwargs):
        super(PartyService, self).__init__(**kwargs)
        FakePartyData.__init__(self)
        
        self.users = {} # здесь будем хранить записи юзеров (со списками френдов) [auid] -> user info
        self.logins = {} # здесь будем хранить соответствие login ["<snid>#<snuid>"] -> auid 
        self.peers = {} # [server_id] -> peer server info
        self.ws_accs = {} # [auid] -> {server, uid}
        
        self.parties = {} # [auid] -> PartyContext
        self.afterparties = {} # [session_id] -> [auid]
        self.tamburs = {} # [tambur_id] -> TamburContext
        self.tambur_ids = {} # [gameid+список auid игроков] -> tambur_id
        self.tambur_sides = {} # [gameid] -> [tambur_id, tambur_id..] для всех сторон, участвующих в игре (в норме там ровно 2 штуки tambur_id, для двух сторон игры)
        self.fail_requests = ClassDict()
        
    # -----------------------------------------------
    def tick(self):
        SEC = toint(time.time())
        # отрабатываем таймауты на invit-ах (возможно, прибивая весь PartyContext, если invite последний)
        self.refreshPartyContexts()
        # отрабатываем таймауты на тамбурах (мы их не удаляем сразу, чтобы не было проблем с цепочкой асинхронных запросов вида tambur_add - tambur_delete - tambur_add - tambur_delete...)
        self.refreshTamburContexts()
        
        if SEC % 60 == 0:
            self.updateInstrumentedActions()

        if self.I.STATS:
            ts0 = time.clock()
            try:
                self.I.STATS.Send()
            except:
                catch()
        info("STATS.Send time: %.3f" % (time.clock()-ts0))

    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers(r"(.*)", [ 
            (r"/x", PartyServiceHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I)),
        ])
        
        # готовы слушать; рапортуем координатору (и получаем в ответ список WS peers)
        self.getPeersFromCoordinator()
            
        
    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # проверяем, не слушает ли на нашем порту кто-то еще (защита от повторного запуска координатора)
        self_addr = "127.0.0.1:"+str(options.port)
        res = httpClientRequest(addr=self_addr, server="x", params="action=check_alive&name=_party_server_")
        if res and res.get("ok") != None:
            fatal("DUPLICATE PARTY SERVER: already listening on " + self_addr + "\n(reply was %s)" % str(res))
            return True # обламываемся, уже запущена копия веб-сервера на этом порту
            
        print("check startup environment: ok, port free (" + self_addr + ")")
        
        
    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = PERSON_SERVER_ID
            options.server_name = PERSON_SERVER_NAME
            options.server_class = "party"
        else:
            options["server_id"].set(PERSON_SERVER_ID)
            options["server_name"].set(PERSON_SERVER_NAME)
            options["server_class"].set("party")

    # -----------------------------------------------
    # OVERRIDE
    def onGetPeerServer(self, peer, peer_name, peer_id, status):
        if status == PEER_DELETED:
            return
        if peer["on"] and peer_id:
            self.peers[ toint(peer_id) ] = peer
            
    # -----------------------------------------------
    @staticmethod
    def initInterfaces(classOf=None):
        # --- для начала надо связаться с координатором и получить от него актуальные кластерные настройки для cfg
        classOf.getCoordinatorConfig(classOf)
        
        iDict = ClassDict()

        # http-клиент, потенциально -- для запросов к facebook и zzima api
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient(max_clients=cfg.HTTP_CURL_WORKERS) 
        iDict.WS = IWebServer() # чисто для генерации GUID-ов

        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager() 
        info("MD interface: " + str(iDict.MD))
        
        iDict.Config = MultiConfig()

        iDict.MSD = MultiStaticData("xdb/ExportedSocialData.xml", iDict.Config.getMainConfig(), loadLocales=False)
        iDict.SD = iDict.MSD.getMainSD()
        iDict.AGG = IfaceFactory.makeSocAggInterface(options.soc_agg, \
            cfg.SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, HTTP=iDict.HTTP)
                
        request_limit = getattr(cfg, "HTTP_REQUEST_LIMIT", 1000)
        info("using http request_limit=%s" % request_limit)
        
        iDict.WSX = IfaceFactory.makeIPeerWebServerInterface(options.wsx, HTTP=iDict.HTTP, request_limit=request_limit)
        iDict.CHAT = IfaceFactory.makeIChatServerInterface(options.chat, cfg.CHAT_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit)
        
        iDict.FRIENDS = ifriendservice.IHttpFriendService(addresses=cfg.FRIEND_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit)
        iDict.PARTY = ipartyservice.IHttpPartyService(addresses=cfg.PARTY_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit)

        iDict.STATS = IfaceFactory.makeIStatsInterface(options.stats, coord_cfg.COORDINATOR_STATS_AGENT_URL, iDict, cfg.STATS_RESEND_POOL_LIMIT)
        info( "Statistics interface: " + str(iDict.STATS) )


        return iDict


    def resetPendingChanges(self, party):
        party.pending_changes = []
        party.pending = GroupPendingChangeWriter(party)
        
        
    # ---------------------------------------------------------------------------------------------
    def getTamburKey(self, game_id, allies_key):
        return "%s:%s" % (game_id, allies_key)
        
    def getTamburId(self, game_id, allies_key):
        tambur_key = self.getTamburKey(game_id, allies_key)
        return self.tambur_ids.get(tambur_key)

    def addTambur(self, game_id, allies_key):
        tambur_key = self.getTamburKey(game_id, allies_key)
        tambur_id = self.I.WS.nextInt64GUID('tambur')
        tambur = TamburContext(tambur_id, self)
        tambur.game_id = game_id
        self.I.WS.tambur_ids[ tambur_key ] = tambur_id
        self.I.WS.tamburs[ tambur_id ] = tambur
        self.addTamburSide(game_id, tambur_id)
        return tambur, tambur_id
        
    def deleteTambur(self, tambur):
        if tambur:
            # после зачистки party_id тамбур должен автоматически удалиться через TAMBUR_DELETE_PERIOD секунд
            tambur_id = tambur.party_id
            if tambur_id:
                for auid in tambur.members:
                    self.I.CHAT.removeUserGroup(auid, getTamburChatName(tambur_id), self.I.WS.onChatGroupUnregister)

                tambur.party_id = 0 
                tambur.ts = time.time()
                
                tambur.PartyData.party_uid = 0 # торжественно зачищаем party_id
                # и рассылаем всем посетителям тамбура извещение о его смерти:
                fake_tambur_model_change = self.I.WS.WriteModelChangeString("deleted", "/", "init", {"PartyData":{ "party_uid":0 }})
                self.I.WS.sendPartyBroadcast(tambur, "deleted", to_auids=tambur.members,
                                             json_TamburData=fake_tambur_model_change, tambur_id=tambur_id)
                
                self.I.FRIENDS.removeTamburId(tambur_id, auids=tambur.members)
                
            self.tambur_sides.pop(tambur.game_id, None)

    def addTamburSide(self, game_id, tambur_id):
        tambur_list = self.tambur_sides.setdefault(game_id, [])
        if tambur_id not in tambur_list:
            tambur_list.append(tambur_id)

    # helper, возвращаем ДРУГОЙ зареганный тамбур для данной игры (имеющий тот же game_id, но ДРУГОЙ tambur_id)
    def getOtherTambur(self, game_id, tambur_id):
        tambur_list = self.tambur_sides.get(game_id)
        if tambur_list:
            for other_tambur_id in tambur_list:
                if other_tambur_id != tambur_id:
                    other_tambur = self.tamburs.get(other_tambur_id)
                    info("getOtherTambur: game_id %s, tambur_id %s, other_tambur_id %s, other_tambur %s" % (game_id, tambur_id, other_tambur_id, other_tambur))
                    return other_tambur
            info("getOtherTambur: game_id %s, tambur_id %s -- no other tambur found in tambur_list" % (game_id, tambur_id))
        else:
            info("getOtherTambur: game_id %s, tambur_id %s -- empty tambur_list" % (game_id, tambur_id))


    def checkTamburSide(self, game_id, tambur_id):
        'Used for debug purpose to check if a tambur exists in the self.tambur_sides.'
        tambur_list = self.tambur_sides.get(game_id)
        return (tambur_list is not None) and (tambur_id in tambur_list)

    # ---------------------------------------------------------------------------------------------
    # выпиливаем все outstanding invites
    def removePendingInvites(self, party, reason="unknown reason"):
        if party:
            for invite_auid in party.pending_invites.keys():
                if invite_auid:
                    self.removePartyMember(party, invite_auid, reason)

    # ---------------------------------------------------------------------------------------------
    def fixIsEnemyState(self, newMaster, party):
        if newMaster.isEnemy:
            for member_id, member in party.members.iteritems():
                member.isEnemy = not member.isEnemy

    # ---------------------------------------------------------------------------------------------
    def removePartyMember(self, party, acc_auid, message):
        if party and acc_auid:
            master_auid = party.getMaster()
            info("removePartyMember: party members=%s, auid=%s" % (party.members, acc_auid))
            if acc_auid in party.members and acc_auid not in party.pending_invites:

                # всем членам партии (включая удаляемого) надо будет остановить матчмейкинг
                notify_members = party.members[:]
                if party.isTemp():
                    # это последний постоянный member; придется выпилить и все outstanding invites (мастер наприглашал, а сам слился)
                    self.removePendingInvites(party, "party expire")

                # PartyData:
                _next_master = None
                if(acc_auid == party.getMaster()):
                    # если из партии выходит мастер, нужно сменить owner на следующего member
                    if len(party.members) > 1:
                        _next_master = party.PartyData.findMemberByUid(party.members[1])
                        self.fixIsEnemyState(_next_master, party.PartyData)
                        
                # убираем юзера из партии
                party.members.remove(acc_auid)
                #! если в партии не осталось больше members, или если остался только 1 и больше нет инвайтов -- партия удалится на следующем тике PS
                
                party.removePerson(acc_auid)
                if _next_master:
                    party.PartyData.owner = _next_master
 
                master_auid = party.getMaster()
                    
                # отправляем всем членам партии извещение, что member удален (и если сменился мастер, то факт этой смены)
                party_model_changes = self.I.WS.pickPendingPartyChanges(party) 
                self.sendPartyBroadcast(party, "disband", to_auids=party.members, disband_auid=acc_auid,
                                        master_auid=master_auid, message=message, json_PartyData=party_model_changes)
                    
                # выкинутого юзера нужно известить, что у него больше нет партии
                fake_party_model_change = self.I.WS.WriteModelChangeString("disbanded", "/", "init", {"PartyData":{ "party_uid":0 }})
                self.I.WS.sendPartyBroadcast(party, "disbanded", to_auids=[acc_auid], master_auid=master_auid, \
                    message=message, disband_auid=acc_auid, json_PartyData=fake_party_model_change)
                        
                # при удалении party member, если партия находится в матчмейкинге, она должна немедленно выпилиться оттуда
                if party.PartyData.InMatchmaking:
                    self.I.WS.sendPartyBroadcast(party, "stop", to_auids=notify_members, master_auid=master_auid, \
                        message="on member disband: "+message, disband_auid=acc_auid)

                self.I.CHAT.removeUserGroup(acc_auid, getGroupChatName(party.party_id), self.I.WS.onChatGroupUnregister)
                                
            elif acc_auid in party.pending_invites:
                party.pending_invites.pop(acc_auid)

                # PartyData:
                party.removePerson(acc_auid)
                # отправляем всем членам партии извещение, что инвайт удален 
                party_model_changes = self.I.WS.pickPendingPartyChanges(party) 
                self.sendPartyBroadcast(party, "remove_invite", to_auids=party.members, invite_auid=acc_auid,
                                        message=message, json_PartyData=party_model_changes)
                    
                # приглашенного юзера нужно известить, что у него больше нет инвайта
                self.I.FRIENDS.removePartyInvite(acc_auid, party.party_id, master_auid, reason=message)
                        
                #! если в партии не осталось больше members, или если остался только 1 и больше нет инвайтов -- партия удалится на следующем тике PS

            # ----------------------------------------------
            # извещаем FriendService, что у нас больше нет партии
            self.I.FRIENDS.removePartyId(acc_auid, party.party_id, master_auid)
                
        else:
            warn("BAD removePartyMember: party %s, acc_auid %s" % (party, acc_auid))
                
                    
    # ---------------------------------------------------------------------------------------------
    # отрабатываем таймауты на invit-ах (возможно, прибивая весь PartyContext, если invite последний)
    def refreshPartyContexts(self):
        now = time.time()
        for party_id in self.parties.keys():
            party = self.parties[party_id]
            master_auid = party.getMaster()
            if party and (party.pending_invites or (party.isTemp() and not party.PartyData.madeAfterBattle)):
                # партия временная (только мастер) или у нее есть неотвеченные инвайты
                for invite_auid in party.pending_invites.keys():
                    ts = party.pending_invites[invite_auid]
                    if ts + PARTY_INVITE_TIMEOUT < now:
                        info("expiring invite_auid %d for party_id %d (master_auid %d): ts %5.3f, now %5.3f", invite_auid, party_id, master_auid, ts, now)
                        
                        # PartyData:
                        self.removePartyMember(party, invite_auid, "invite timeout")
            elif party.PartyData.madeAfterBattle:
                debug("pre refreshPartyContexts %r", party.PartyData.generateJsonDict())
                # время ожидания игроков ещё не завершилось
                if party.PartyData.afterBattleLockEndTime >= int(time.time()):
                    canFinalize = True
                    # Проверим, не пора ли финализировать пати досрочно (все, кто хотел, уже присоединились или отказались)
                    for _id, member in party.PartyData.members.iteritems():
                        # Если мы ещё кого-то ждём, пропускаем эту пати
                        if not member.agreed:
                            canFinalize = False
                            break
                    if not canFinalize:
                        continue
                # время вышло, пора финализировать пати
                else:
                    # выкинуть не принявших
                    for _id, member in party.PartyData.members.items():
                        if member.agreed:
                            self.I.PARTY.updatePersonStatus(member.person.person_uid, party.PartyData.party_uid, FriendStatus.INCASTLE )
                        else:
                            party.members.remove(member.person.person_uid)
                            party.removePerson(member.person.person_uid)
                    master_auid = party.getMaster()

                party.PartyData.madeAfterBattle = False
                party.PartyData.afterBattleLockEndTime = 0

                debug("refreshPartyContexts to_auids %r", party.members)
                if party.members:
                    party_model_changes = self.I.WS.pickPendingPartyChanges(party)
                    self.sendPartyBroadcast(party, "change", message="afterparty was finalized",
                                            to_auids=party.members,
                                            master_auid=master_auid, members=strList(party.members),
                                            json_PartyData=party_model_changes)

                debug("refreshPartyContexts afterparty_session_id %r", party.afterparty_session_id)
                if party.afterparty_session_id:
                    self.I.PARTY.removeAfterpartyId(party.afterparty_session_id, party_id)

                debug("post refreshPartyContexts %r", party.PartyData.generateJsonDict())

            # если удалили все инвайты, и остался один мастер -- нафиг такую партию
            if party.isEmpty() or (party.isTemp() and (not party.pending_invites)):
                # если время ожидания игроков ещё не завершилось,
                if party.PartyData.madeAfterBattle:
                    continue
                info("expiring party_id %d (master_auid %d)" % (party_id, master_auid))

                # извещаем мастера, что партия всё
                if master_auid:
                    # удаление партии будет апдейтить в model changes как сброс uid-а в 0
                    party.PartyData.party_uid = 0
                    party_model_changes = self.I.WS.WriteModelChangeString("expire", "/", "init", {"PartyData": {"party_uid": 0}})

                    self.sendServerPartyError(master_auid, "expire", "party expired: all invites timed out", json_PartyData=party_model_changes, party_id=party_id)

                    self.I.CHAT.removeUserGroup(master_auid, getGroupChatName(party_id), self.I.WS.onChatGroupUnregister)
                    self.I.FRIENDS.removePartyId(master_auid, party_id, master_auid)

                self.parties.pop(party_id)
                            
    def refreshTamburContexts(self):
        now = time.time()
        for tambur_key in self.tambur_ids.keys():
            tambur_id = self.tambur_ids.get(tambur_key)
            tambur = self.tamburs.get(tambur_id)
            if not tambur.party_id:
                if tambur.ts + self.TAMBUR_DELETE_PERIOD <= now:
                    info('deleting tambur_id %s (members %s)' % (tambur_id, tambur.members))
                    self.tambur_ids.pop(tambur_key)
                    self.tamburs.pop(tambur_id)

        
    # ---------------------------------------------------------------------------------------------
    def sendServerPartyError(self, auid, failed_cmd, message, party_id=0, **kwargs):
        self.sendServerPartyCmd(auid, "error", message, failed_cmd=failed_cmd, party_id=party_id, **kwargs)
                
    def sendServerPartyCmd(self, auid, cmd, message, party_id=0, **kwargs):
        ws_acc = self.ws_accs.get(auid)
        if ws_acc and ws_acc.server:
            peer = self.peers.get(ws_acc.server)
            if peer:
                kwargs["message"] = message
                post_body = json_dumps(kwargs)
                Callback = functools.partial(self.checkFailCallback, peer.get("name", ""))
                self.I.WSX.post(
                    peer["addr"], 
                    dict(
                        action='server_party',
                        cmd=cmd,
                        to_uids=str(ws_acc.uid),
                        party_id=party_id,
                        msg_id=self.nextMsgID(),
                 ), 
                    post_body,
                    Callback
             )
                
    # ---------------------------------------------------------------------------------------------
    def sendPartyBroadcast(self, party, cmd, to_auids=[], **kwargs):
        # предварительный вид http-строки (без списка адресатов to_uids=<uid,uid,..>:
        #command = "/x?action=server_party&cmd=%s&party_id=%s&msg_id=%d" % (cmd, party.party_id, self.nextMsgID()) + makeParamString(kwargs)
        if not to_auids:
            to_auids = [member.person.person_uid for _id, member in party.PartyData.members.iteritems() if member.agreed]
        
        # отсортируем список членов группы по peer-серверам, на которых они находятся (каждому peer-серверу можно отослать одно http-сообщение, со списком to_uids)
        #  заодно достаем родные кластерные uid вместо вражеских auid
        server_uid_groups = {}
        for auid in to_auids:    
            ws_acc = self.ws_accs.get(auid)
            if ws_acc and ws_acc.server:
                group = server_uid_groups.get(ws_acc.server) or []
                group.append(ws_acc.uid)
                server_uid_groups[ ws_acc.server ] = group
            
        if server_uid_groups:
            post_body = json_dumps(kwargs)
            
            for server_id, uid_list in server_uid_groups.iteritems():
                peer = self.peers.get(server_id)
                if peer:
                    ##to_uids_string = "&to_uids=%s" % strList(uid_list)
                    Callback = functools.partial(self.checkFailCallback, peer.get("name", ""))
                    self.I.WSX.post(
                        peer["addr"], 
                        dict(
                            action='server_party',
                            cmd=cmd,
                            to_uids=strList(uid_list),
                            party_id=party.party_id,
                            msg_id=self.nextMsgID(),
                     ), 
                        post_body,
                        Callback
                 )
        else:
            info("empty server_uid_groups for sendPartyBroadcast: party_id %d" % party.party_id)

    def checkFailCallback(self, sname, data_reply):
        if not data_reply:
            self.fail_requests[sname] = self.fail_requests.get(sname, 0) + 1
            warn("checkFailCallback fail_requests stats %r", self.fail_requests)
        else:
            if not self.fail_requests.get(sname, 0):
                self.fail_requests[sname] = 0

    # ---------------------------------------------------------------------------------------------
    def onDummyHttpCallback(self, http_reply):
        pass
        
    def onDummyAggCallback(self, result_dict):
        info("onDummyAggCallback: result %s" % result_dict)
        
    def onDummyResponseCallback(self, response):
        info("PS onDummyResponseCallback: response %r" % response)
    
    # ---------------------------------------------------------------------------------------------
    def setPersonAUID(self, auid):
        self._personAUID = auid
        
    def getPersonAUID(self):
        return self._personAUID
       
    # ---------------------------------------------------------------------------------------------
    # CHAT callbacks
    # ---------------------------------------------------------------------------------------------
    def onChatRegister(self, response):
        ##response = self.parseResponse(http_reply)
        if response and response.get('ok'):
            ##info("onChatRegister response: %s" % pretty(response))
            pass

    def onChatUnregister(self, response):
        if response and response.get('ok'):
            ##info("onChatUnregister response: %s" % pretty(response))
            pass

    def onChatGroupRegister(self, response):
        if response and response.get('ok'):
            ##info("onChatGroupRegister response: %s" % pretty(response))
            pass

    def onChatGroupUnregister(self, response):
        if response and response.get('ok'):
            ##info("onChatGroupUnregister response: %s" % pretty(response))
            pass
        
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

def main():
    ITornadoServer.main(PartyService)

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8716
    else:
        options["port"].set(8716)
    main()
