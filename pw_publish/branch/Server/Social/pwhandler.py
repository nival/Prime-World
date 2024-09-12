# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, re, hashlib, urllib, httplib, logging

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)
_addPath('tornado')

import tornado.options

from tornado.options import define, options
from handlers import *
from ifactory import IfaceFactory
from whandler import WebJsonHandler
from binascii import crc32

import MM
import party_const
import ibilling
from enums import *

from ext_pw import MatchmakingAddAction
from ext_main.who import AddUserAction
from ext_main.l_merge import LauncherMergeInternalAction

from modeldata.change_applicator import ModelChangeApplicator
from friendsdata.FriendsData import FriendsData
from party.PartyData import PartyData
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from guild.RecruitsData import RecruitsData
from subaction import SubAction, ResponseObject, action_timing
from sublogin import AgentSubloginAction 

import chat_utils
from base.exceptions import  ModelChangeApplicatorError

## -------------------------------------------------------------------------------------------------------------------------------------
## -------------------------------------------------------------------------------------------------------------------------------------

class PersonServerFriendsCmdAction( SubAction ):
    """ отдельный SubAction, который обрабатывает server_friends-команды, полученные от PersonServer """
    action = "server_friends"


    #----------------------------------------------------------------------------------------------
    # PersonServer прислал friends-команду для передачи на клиент
    @action_timing
    def onStart(self):
        # если пришел post, нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
        try:
            self.unpackJsonBodyArguments()
        except:
            catch()
            return self.fin()
            
        if self.checkValidParam("cmd"):        
            to_uids = self.getParam("to_uids").split(",")
            info( "PersonServerFriendsCmdAction: cmd:%s, to_uids:%s", self.cmd, str(to_uids) )
            if to_uids and isinstance(to_uids, list) and len(to_uids):
                self.response["messages"] = []
                for uid in to_uids:
                    self.acc = users.get( toint(uid) )
                    if self.acc:
                        self.auid = self.acc.auid
                        param_dict = self.getFlatParams( except_list=['to_uids'] )
                        
                        for key, val in param_dict.iteritems():
                            if isinstance(val, basestring):
                                # int значения приведем к типу int
                                try:
                                    int_val = int(val)
                                    param_dict[key] = int_val
                                except:
                                    pass
                            
                        debug( "PersonServerFriendsCmdAction: param_dict %s", self.I.MD.pretty(param_dict) )
                        
                        recurse_unquote( param_dict )
                        recurse_unjson( param_dict )

                        #data_dict = self.I.WS.postFriendPendingEvent( self.acc, param_dict )
                        #if self.acc.isSendedFriends:
                            # отправляем только если чувак у нас на странице
                        self.I.WS.postPendingEvent( self.acc, {"friends": param_dict})
                        
                        changes_dict = param_dict.get("FriendsData")
                        if changes_dict:
                            try:
                                debug("PersonServerFriendsCmdAction: self.acc.isSendedFriends= %r", self.acc.isSendedFriends)
                                for fname in ("BufferFriendsData", "friendsdata"):
                                    if getattr(self.acc, fname ):
                                        try:
                                            ModelChangeApplicator.apply( self.acc, fname , FriendsData, changes_dict )
                                        except ModelChangeApplicatorError as exc:
                                            debug("Bad update for %r  error: %r",fname, exc.message)

                            except Exception:
                                info("Error in applying changes: %r", changes_dict)
                                catch()

                        
                    else:
                        self.response["messages"].append( "no acc for uid %r" % uid )

                self.response["ok"] = 1
            else:
                self.response["error"] = "bad uids list: %r" % (to_uids)
        
        self.fin()


## -------------------------------------------------------------------------------------------------------------------------------------
## -------------------------------------------------------------------------------------------------------------------------------------

class GuildResubscribeToChatCmdAction( SubAction ):
    action = "guild_resubscribe_to_chat"

    @action_timing
    def onStart(self):
        # если пришел post, нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
        param_dict = None
        uid = self.getIntParam("uid", 0)
        self.guildshortname = self.getParam("guildshortname")
        self.acc = users.get( uid )
        if self.acc:
            if self.acc.chat:
                self.I.CHAT.removeUser(self.acc.chat['host'], self.acc.auid, self.onRemoveFromChat)
                return 
            elif chat_utils.addToChat(self.I.CHAT, self.acc.db.fraction, self.acc, options.server_id, self.onAddToChat, guildshortname=self.guildshortname):
                return 
            
        else:
            err("GuildResubscribeToChatCmdAction: can not find acc by uid=%r" % uid )

        return self.fin()


    def onRemoveFromChat(self, response):
        info( "onRemoveFromChat: response %s" % str(response) )
        if chat_utils.addToChat(self.I.CHAT, self.acc.db.fraction, self.acc, options.server_id, self.onAddToChat, guildshortname=self.guildshortname):            
            return
        self.fin()
        
    def onDummyAddUserGroup(self, response, whom=''):
        info("onDummyAddUserGroup: from %r response %r" % (whom,response))

    def onAddToChat(self, response):
        if response and response.get("ok"):
            info( "onAddToChat: response %s" % str(response) )
            self.response['chat'] = { 'host' : self.acc.chat['host'], 'key' : self.acc.chat['key'] }
            
            callback1 = functools.partial( self.onDummyAddUserGroup, whom="global" )
            callback2 = functools.partial( self.onDummyAddUserGroup, whom="guild" )
            callback3 = functools.partial( self.onDummyAddUserGroup, whom="party" )
            
            self.I.CHAT.addUserGlobalGroups( self.acc.auid, callback1)
            if self.acc.db.guildAuid:
                self.I.CHAT.addUserGroup( self.acc.auid, self.I.WS.getGuildChatName(self.acc.db.guildAuid), callback2)
            if self.acc.party_id:
                self.I.CHAT.addUserGroup( self.acc.auid, self.I.WS.getGroupChatName(self.acc.party_id), callback3)
                                        
        else:
            warn( "onAddToChat: BAD response %s" % str(response) )
        self.fin()


class GuildDataCmdAction( SubAction ):
    action = "guild_data"
        
    @action_timing
    def onStart(self):
        # если пришел post, нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
        param_dict = None
        try:
            if self.request.request and self.request.request.body:
                unquoted_body = urllib.unquote( self.request.request.body )
                param_dict = json_loads( unquoted_body )
        except:
            catch()
            return self.fin()
        if param_dict:
            to_uids = self.getParam("to_uids").split(",")
            cmd = self.getParam("cmd")
            guild_auid =self.getIntParam("guild_auid", 0)
            if to_uids and isinstance(to_uids, list):
                for uid in to_uids:
                    self.acc = users.get( toint(uid) )
                    if self.acc and (self.acc.db.guildAuid == guild_auid or guild_auid == 0):
                        if cmd in ('destroy', 'admin_kick'):
                            if self.acc.db.guildAuid:
                                self.I.CHAT.removeUserGroup(self.acc.auid, self.I.WS.getGuildChatName(self.acc.db.guildAuid), self.I.WS.onDummyResponseCallback)
                                self.I.GS.unsubscribe( self.acc, options.server_id, self.I.WS.onDummyResponseCallback )
                            self.acc.db.guildAuid = 0
                            #и плюшки от гильдии конфискуем!
                            self.acc.model.write( self.acc.pending )
                            self.acc.pending.setPrefix( "resetGuild:" )
                            self.acc.model.setComment( "auto" )
                            self.acc.model.resetGuild( self.I, self.acc)

                        if param_dict:
                            try:
                                ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, param_dict ) 
                            except:
                                catch()
                        self.acc.pending_events.append( {"GuildData": { "GuildData": param_dict }} )
                        if self.acc.pending_handler:
                            self.acc.pending_handler()
                    else:
                        err("GuildDataCmdAction: can not find acc by uid=%r" % toint(uid) )
            else:
                err("GuildDataCmdAction: to_uids(%r) is bad" % to_uids )
        else:
            err("GuildDataCmdAction: params = None" )
        return self.fin()


class SiegeDataCmdAction(SubAction):
    action = "siege_data"

    @action_timing
    def onStart(self):
        # если пришел post, нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
        param_dict = None
        try:
            if self.request.request and self.request.request.body:
                unquoted_body = urllib.unquote( self.request.request.body )
                param_dict = json_loads( unquoted_body )
        except:
            catch()
            return self.fin()
        if param_dict:
            to_uids = self.getParam("to_uids").split(",")
            cmd = self.getParam("cmd")
            if to_uids and isinstance(to_uids, list) and len(to_uids):
                for uid in to_uids:
                    self.acc = users.get( toint(uid) )
                    if self.acc:
                        if param_dict:
                            try:
                                ModelChangeApplicator.apply( self.acc, "siegedata", SiegeData, param_dict )
                            except:
                                catch()
                        self.acc.pending_events.append( {"SiegeData": { "SiegeData": param_dict }} )
                        if self.acc.pending_handler:
                            self.acc.pending_handler()
                    else:
                        err("SiegeDataCmdAction: can not find acc by uid=%r" % toint(uid) )
            else:
                err("SiegeDataCmdAction: to_uids(%r) is bad" % to_uids )
        else:
            err("SiegeDataCmdAction: params = None" )
        return self.fin()


class PersonServerPartyCmdAction( SubAction ):
    """ отдельный SubAction, который обрабатывает server_party-команды, полученные от PersonServer """
    action = "server_party"
        
    #----------------------------------------------------------------------------------------------
    # PersonServer прислал party-команду для передачи на клиент
    @action_timing
    def onStart(self):
        # если пришел post, нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
        try:
            self.unpackJsonBodyArguments()
        except:
            catch()
            return self.fin()
        
        if not self.checkValidParam("cmd"):
            return self.fin()

        to_uids = self.getParam("to_uids").split(",")
        msg_id = self.getIntParam("msg_id", 0)
        info("onPersonServerPartyCmd: cmd=%s, msg_id=%s, to_uids=%s", self.cmd, msg_id, str(to_uids))
        if not (to_uids and isinstance(to_uids, list) and len(to_uids)):
            self.response["error"] = "bad uids list: %r" % (to_uids)
            return self.fin()

        self.response["messages"] = []
        for uid in to_uids:
            self.party_ok = 1 # если хотя бы один из членов партии пофейлит mm_add, вся попытка в целом будет неуспешной
            self.acc = users.get(toint(uid))
            if self.acc:
                self.auid = self.acc.auid
                param_dict = self.getFlatParams(except_list=['to_uids'])
                info("onPersonServerPartyCmd (uid=%s, auid=%s) param_dict:%s", uid, self.auid, param_dict)

                for key,val in param_dict.iteritems():
                    if isinstance(val, basestring):
                        # int значения приведем к типу int
                        try:
                            int_val = int(val)
                            param_dict[key] = int_val
                        except:
                            pass

                recurse_unquote(param_dict)
                recurse_unjson(param_dict)
                self.I.WS.postPendingEvent(self.acc, {"party":param_dict})

                changes_dict = param_dict.get("PartyData")
                debug("PersonServerPartyCmdAction: auid %d, cmd %r, party_changes %r", self.auid, self.cmd, changes_dict)
                if changes_dict:
                    try:
                        ModelChangeApplicator.apply(self.acc, "partydata", PartyData, changes_dict)
                    except:
                        catch()
                # We also need to check FriendsData, PF-91926
                friends_change_dict = param_dict.get("FriendsData")
                if friends_change_dict:
                    try:
                        ModelChangeApplicator.apply(self.acc, "friendsdata", FriendsData, friends_change_dict)
                    except:
                        catch()


                # отдельно обрабатываем party.go: нужно зафорсить mm_add от лица каждого из перечисленных юзеров
                if self.cmd == "go":
                    game_type = param_dict.get("game_type", "pvp")
                    with_bots = param_dict.get("with_bots", 0)
                    heroes = param_dict.get("heroes")
                    party_id = toint( param_dict.get("party_id") )
                    rdy2manoeuvre = toint( param_dict.get("rdy2manoeuvre") )
                    only_guard = toint( param_dict.get("only_guard") )
                    party_auids = param_dict.get("party_auids", [])
                    enemy_auids = param_dict.get("enemy_auids", [])
                    if heroes and isinstance(heroes, dict):
                        if self.auid in heroes:
                            hero_params = ClassDict( heroes[ self.auid ] )
                            hero = self.acc.model.getHeroByID( hero_params.hero_id )
                            if hero:
                                if hero.PersistentId == hero_params.hero_crc:
                                    # все ок, юзер есть, выбранный герой нашелся; можно делать mm_add

                                    info( "starting user (uid=%s) matchmaking with hero_id=%s, game_type=%s, rdy2manoeuvre=%s, with_bots=%s talentset_id %s on party.go", uid, hero_params.hero_id, game_type, rdy2manoeuvre, with_bots, hero.ActiveTalentSet )

                                    subParams = ClassDict(
                                        src_hero_id=[ hero_params.hero_id ],
                                        fraction=[ self.acc.db.fraction ],
                                        game_type=[ game_type ],
                                        with_bots=[ with_bots ],
                                        party_id=[ party_id ],
                                        party_auids=[ strList( party_auids ) ],
                                        enemy_auids=[ strList( enemy_auids ) ],
                                        rdy2manoeuvre=[ rdy2manoeuvre ],
                                        only_guard=[ only_guard ],
                                        locale = [ param_dict.get("locale", "") ],
                                        geolocation = [ param_dict.get("geolocation", "") ],
                                        talent_set_id = [hero.ActiveTalentSet]
                                    )
                                    mmAddAction = MatchmakingAddAction( subParams, self.onPartyGoMMAddCallback, I=self.I, acc=self.acc, uid=self.acc.uid )
                                    mmAddAction._party_go_ = 1 # признак того, что мы запускаемся через внутренний механизм party.go

                                    #! если просто включить self.acc.model.write( self.acc.pending ), @model_callback благополучно заоверрайдит это дело опять в SubAction.response
                                    mmAddAction.onStart() # ответ получаем в onPartyGoMMAddCallback; если кто-то из юзеров пофейлит mm_add, там поставят self.party_ok=0

                                    #! так что приходится выгребать уже готовые changes из response, и перекладывать в pending
                                    model_changes_generated = mmAddAction.response.get("ModelData")
                                    if model_changes_generated:
                                        if isinstance( model_changes_generated, ResponseObject ):
                                            model_changes_generated = model_changes_generated.makeDict()
                                        info( "generated mmAddAction model changes: %s" % model_changes_generated )
                                        for change in model_changes_generated:
                                            self.acc.pending_changes.append( {"ModelData": change} )

                                else:
                                    self.response["error"] = "bad hero_params.hero_id %r, for auid %s" % ( hero_params.hero_id, self.auid )
                                    self.party_ok = 0
                            else:
                                self.response["error"] = "bad hero_params.uid %r, for auid %s" % ( hero_params.uid, self.auid )
                                self.party_ok = 0
                        else:
                            self.response["error"] = "no auid in heroes (auid %s, heroes %r)" % ( self.auid, heroes )
                            self.party_ok = 0

                    else:
                        self.response["error"] = "bad heroes dict: %r" % (heroes)

                    if not self.party_ok:
                        # полностью или частично пофейлился старт матчмейкинга
                        return self.fin()

                elif self.cmd == "stop":
                    # по какой-то причине партия требует полностью остановить свой матчмейкинг (лучше если это сделаем мы сами, а не будем ждать, пока сессию выпилит матчмейкер)
                    # (обычно роллится при disband/kick/logout одного из членов партии; по дизайну в этом случае вся партия должна выпасть из матчмейкинга)
                    mm = self.acc.data.mm
                    if mm:
                        can_cancel = 1
                        session = mm
                        if session:
                            info( "trying to cancel user (uid=%s) mm session on party.stop (mmid %s, progress %s)" % (uid, session.mmid, session.progress) )
                            if session.progress in [MM.STATUS_WAITING_IN_LOBBY, MM.STATUS_WAITING_FOR_PARTY, MM.STATUS_IN_GAME, MM.STATUS_CLIENT_DROPPED, \
                            MM.STATUS_WAITING_GAME_FINISH, MM.STATUS_GAME_FINISHED]:
                                can_cancel = 0 # нельзя cancel-ить уже идущую сессию
                                info( "can't cancel (uid=%s) mm session on party.stop (mmid %s, progress %s)" % (uid, session.mmid, session.progress) )
                                break

                        if can_cancel:
                            self.acc.model.write( self.acc.pending )
                            self.I.WS.doMatchmakingCmd( "party_cancel", self.acc, MM.CANCEL_ALL )

                elif self.cmd == "create_init":
                    # создалась временная партия; заводим себе party_id
                    self.acc.party_id = toint( param_dict.get("party_id") )
                    info( "create_init: set party_id=%d (uid=%d)" % (self.acc.party_id, self.acc.uid) )

                elif self.cmd == "disbanded":
                    # по выходу из группы обнуляем party_id
                    self.acc.party_id = 0
                    info( "disbanded: set party_id=%d (uid=%d)" % (self.acc.party_id, self.acc.uid) )

                elif self.cmd == "error" and param_dict.get("failed_cmd","") == "expire":
                    # по удалению группы обнуляем party_id
                    self.acc.party_id = 0
                    info( "error/expire: set party_id=%d (uid=%d)" % (self.acc.party_id, self.acc.uid) )

                elif self.cmd == "hero":
                    # меняется выбранный герой; если речь о нашем юзере, и юзер в гвардейском тамбуре, то нужно известить матчмейкинг о смене героя
                    change_auid = toint(param_dict.get("auid", 0))
                    hero_id = toint(param_dict.get("hero_id", 0))
                    ts_id = toint(param_dict.get("talentset_id", None))
                    if self.acc.auid == change_auid:
                        # ага, это именно нас извещают
                        session = self.acc.data.mm
                        if session and (session.progress == MM.STATUS_GUARDS_LOBBY):
                            # на всякий случай проверим, что этот герой у нас точно есть PF-79342
                            try:
                                hero = self.acc.model.getHeroByID(hero_id)
                            except:
                                catch()
                            if not hero:
                                self.errorResponse(EC.HERO_NOT_FOUND, "Wrong hero_id came to PersonServerPartyCmdAction: hero_id=%r" % hero_id)
                                return
                            if not ts_id:
                                ts_id = hero.ActiveTalentSet
                            prev_msg_id = toint( session.hero_msg_id )
                            # оповещения о смене героя могут приходить с PS в перепутанном порядке; поэтому запоминаем msg_id от соотв. команды "change hero" у себя в mm session
                            if msg_id > prev_msg_id:
                                map = self.acc.SD.getObjectByDbid( session.game_type )
                                acceptParamsDict = self.I.WS.getHeroAcceptParameters( self.acc, hero_id, map, session.game_type, ts_id )
                                
                                if self.acc.partydata and self.acc.partydata.party_uid and self.acc.partydata.owner:
                                    if self.acc.partydata.owner.person.person_uid == self.acc.auid:
                                        acceptParamsDict["partyLeader"] = True

                                self.I.WS.doMatchmakingCmd( "change_hero", self.acc, session.mmid, acceptParamsDict )
                                self.I.WS.fillHeroMatchmakingValues( session, self.acc, hero_id, self.acc.getConfig(), ts_id )
                                session.hero_msg_id = msg_id
                                self.acc.model.write( self.acc.pending )
                                self.acc.model.validateHeroesInMatchmaking(self.acc)
                            else:
                                warn("previous change_hero msg_id=%s, new msg_id=%s, SKIPPING (probably an out-of-order message)" % (prev_msg_id, msg_id))

            else:
                self.response["messages"].append( "no acc for uid %r" % uid )

        self.response["ok"] = 1
        self.fin()

    
    @action_timing
    def onPartyGoMMAddCallback(self, mmadd_response):
        self.addResponseTiming(mmadd_response)
        if not mmadd_response.get("ok"):
            warn( "party mm_add failed: response %s" % mmadd_response )
            self.party_ok = 0
            self.response["error"] = mmadd_response.get("error", "onPartyGoMMAddCallback fail")
            ec = mmadd_response.get("ec", 0)
        
            # извещаем PersonServer, что юзер не смог начать матчмейкаться
            self.I.PS.sendPartyCmd(self.acc.auid, options.server_id, "party_progress", self.I.WS.onDummyResponseCallback, progress=0, reason="mm_add_fail", ec=ec )

class UpdateTopBuildAction(SubAction):
    action = "update_top_build"
    # -----------------------------------------
    # Обновляем топовые билды, хранящиеся на сервере (при старте кластера или ежедневно при апдейте)
    def onStart(self):
        info("UpdateTopBuildAction.onStart")
        # если пришел post, нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
        param_dict = None
        try:
            if self.request.request and self.request.request.body:
                unquoted_body = urllib.unquote( self.request.request.body )
                param_dict = json_loads(unquoted_body)
        except:
            catch()
            return self.fin()

        if param_dict:
            self.response['ok'] = self.I.WS.updateTopBuildFromJson(param_dict)
        self.fin()

class UpdateGuildWarEventAction(SubAction):
    action = "update_guild_war_event"
    # -----------------------------------------
    # Обновляем данные текущего клановго ивента, хранящиеся на сервере (при старте кластера или ежедневно при апдейте)
    def onStart(self):
        info("UpdateGuildWarEventAction.onStart")
        # если пришел post, нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
        param_dict = None
        try:
            if self.request.request and self.request.request.body:
                unquoted_body = urllib.unquote(self.request.request.body)
                param_dict = json_loads(unquoted_body)
        except:
            catch()
            return self.fin()

        if param_dict:
            self.response['ok'] = self.I.WS.updateGuildWarEventDataFromJson(param_dict)
        self.fin()

class RecruitsDataUpdateAction(SubAction):
    action = "recruits_data"
    # -----------------------------------------
    # Обновляем данные о рекрутах для клиента, присылаем только пакет изменений, без хранения локальной копии на WS
    def onStart(self):
        info("RecruitsDataUpdateAction.onStart")
        # если пришел post, нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
        param_dict = None
        try:
            if self.request.request and self.request.request.body:
                unquoted_body = urllib.unquote(self.request.request.body)
                param_dict = json_loads(unquoted_body)
        except:
            catch()
            return self.fin()

        if param_dict:
            to_uids = self.getParam("to_uids").split(",")
            if to_uids and isinstance(to_uids, list) and len(to_uids):
                for uid in to_uids:
                    self.acc = users.get( toint(uid) )
                    if self.acc:
                        self.acc.pending_events.append({"RecruitsData": {"RecruitsData": param_dict}})
                        if self.acc.pending_handler:
                            self.acc.pending_handler()
                    else:
                        err("RecruitsDataUpdateAction: can not find acc by uid=%r" % toint(uid))
            else:
                err("RecruitsDataUpdateAction: to_uids(%r) is bad" % to_uids)
        else:
            err("RecruitsDataUpdateAction: params = None")
        return self.fin()

class ChangeEventStateByIdAction(SubAction):
    action = "chane_event_state_by_id"

    def onStart(self):
        info("ChangeEventStateById.onStart")
        persistentId = self.getIntParam("persistentId", 0)
        enable = self.getBoolParam("enable")
        opEvents = self.I.WS.operatorEvents
        # Если ивент надо включить, вынимаем его из выключенных и переносим в pending
        if enable:
            if persistentId in opEvents["disabledEvents"]:
                opEvents["pendingEvents"][persistentId] = opEvents["disabledEvents"][persistentId]
                del opEvents["disabledEvents"][persistentId]
            else:
                warn("Event %d was not disabled!", persistentId)
        # Если ивент надо выключить, перенесём его в disabled и отправим в finished, чтобы сервер откатил его действие
        else:
            if persistentId in opEvents["pendingEvents"]:
                del opEvents["pendingEvents"][persistentId]
            elif persistentId in opEvents["activeEvents"]:
                # Ивент активен, надо его откатить
                opEvents["toRevert"][persistentId] = (False, opEvents["activeEvents"][persistentId])
                opEvents["disabledEvents"][persistentId] = opEvents["activeEvents"][persistentId]
                del opEvents["activeEvents"][persistentId]
            elif persistentId in opEvents["finishedEvents"]:
                del opEvents["finishedEvents"][persistentId]
        #debug("ChangeEventStateById.onStart disabledEvents=%r pendingEvents=%r activeEvents=%r finishedEvents=%r", opEvents["disabledEvents"],
        #     opEvents["pendingEvents"], opEvents["activeEvents"], opEvents["finishedEvents"])
        self.response['ok'] = 1
        self.fin()

class EventSubAction(SubAction):
    def __init__(self, arguments, fin_callback, request=None, **kwargs):
        SubAction.__init__(self, arguments, fin_callback, request)
        self.persistentId = self.getIntParam("persistentId")
        self.type = self.getIntParam("type", -1)
        self.endTime = self.getIntParam("endTime", 0)
        self.startTime = self.getIntParam("startTime", 0)
        self.description = self.getParam("description", "")
        self.enabled = self.getBoolParam("enabled")
        opEvents = self.I.WS.operatorEvents

        # Если событие выключено, используем disabled группу
        if not self.enabled:
            self.eventsGroup = opEvents["disabledEvents"]
        # Если событие ещё не активно или уже идёт, используем pending группу
        elif self.startTime > int(time.time()) or (self.startTime < int(time.time()) < self.endTime):
            self.eventsGroup = opEvents["pendingEvents"]
        # Если вдруг событие уже закончилось, то добавим в завершенные
        else:
            self.eventsGroup = opEvents["finishedEvents"]

        _id = self.persistentId
        if self.persistentId in opEvents["pendingEvents"]:
            del opEvents["pendingEvents"][_id]
        elif self.persistentId in opEvents["disabledEvents"]:
            del opEvents["disabledEvents"][_id]
        elif self.persistentId in opEvents["activeEvents"]:
            # Ивент активен, надо его откатить: положим в законченные
            opEvents["toRevert"][_id] = (False, opEvents["activeEvents"][_id])
            del opEvents["activeEvents"][_id]
        elif self.persistentId in opEvents["finishedEvents"]:
            del opEvents["finishedEvents"][_id]

class DeleteEventByIdAction(EventSubAction):
    action = "delete_event_by_id"

    def onStart(self):
        info("DeleteEventById.onStart")

        # Класс EventSubAction уже сам всё за нас удалил
        self.response['ok'] = 1
        self.fin()

class AddTalentPerPerlEventAction(EventSubAction):
    action = "add_talent_per_perl_event"
    # -----------------------------------------
    # Добавляем ивент на изменение кол-ва талантов, получаемых за 1 кристалл

    def onStart(self):
        info("AddTalentPerPerlEventAction.onStart")
        self.talents = self.getIntParam("talents")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                                                   "enabled": self.enabled, "defaultValue": 0,
                                                   "newValue": {"talents": self.talents}}
        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event
            debug("Event added: %r", self.eventsGroup[self.persistentId])

        self.response['ok'] = 1
        self.fin()

class AddNewsBannerAction(EventSubAction):
    action = "add_news_banner_event"
    # -----------------------------------------
    # Добавляет новостной баннер

    def onStart(self):
        info("AddNewsBannerAction.onStart")
        self.buttonText = self.getParam("buttonText")
        self.windowCaption = self.getParam("windowCaption")
        self.buttonUrl = self.getParam("buttonUrl")
        self.mainUrl = self.getParam("mainUrl")
        self.tooltip = self.getParam("tooltip")
        self.mainUrlB = self.getParam("mainUrlB")
        self.LoginNetworks = self.getParam("LoginNetworks")
        self.minLordLevel = self.getParam("minLordLevel")
        self.hideIfViewed = self.getParam("hideIfViewed")
        self.locale = self.getParam("locale")
        self.extensionJson = self.getParam("extensionJson")

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                                                   "enabled": self.enabled,
                                                   "newValue": {"buttonText": self.buttonText, "locale": self.locale,
                                                   "windowCaption": self.windowCaption, "buttonUrl": self.buttonUrl,
                                                   "mainUrl": self.mainUrl, "tooltip": self.tooltip,
                                                   "mainUrlB": self.mainUrlB, "LoginNetworks": self.LoginNetworks,
                                                   "minLordLevel": self.minLordLevel, "hideIfViewed": self.hideIfViewed,
                                                   "extensionJson": self.extensionJson}}

        self.response['ok'] = 1
        self.fin()

class AddCustomEventAcion(EventSubAction):
    action = "add_custom_event"
    # -----------------------------------------
    # Добавляем ивент из старых events.txt

    def onStart(self):
        info("AddCustomEventAcion.onStart")
        self.eventDescription = self.getParam("eventDescription")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"eventDescription": self.eventDescription}}
        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddSkinsPriceEventAction(EventSubAction):
    action = "add_skins_price_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddSkinsPriceEventAction.onStart")
        self.skins = self.getJsonParam("skins")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"skins": self.skins}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()


class AddHeroesPriceEventAction(EventSubAction):
    action = "add_heroes_price_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddHeroesPriceEventAction.onStart")
        self.heroes = self.getJsonParam("heroes")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"heroes": self.heroes}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddCustomMapEventAcion(EventSubAction):
    action = "add_custom_map_event"
    # -----------------------------------------
    # Добавляем ивент из старых events.txt

    def onStart(self):
        info("AddCustomMapEventAcion.onStart")
        self.startHour = self.getParam("startHour")
        self.endHour = self.getParam("endHour")
        self.day = self.getParam("day")
        self.mapType = self.getParam("mapType")
        self.mapDbid = self.getParam("mapDbid")
        self.mapEnabled = self.getBoolParam("mapEnabled")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"startHour": self.startHour, "endHour": self.endHour, "mapType": self.mapType,
                              "mapDbid": self.mapDbid, "day": self.day, "mapEnabled": self.mapEnabled}}
        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1


class AddTalentDropRarityAction(EventSubAction):
    action = "add_talent_drop_rar_event"
    # -----------------------------------------
    # Добавляем ивент из старых events.txt

    def onStart(self):
        info("AddTalentDropRarityAction.onStart")
        self.Class = self.getIntParam("Class")
        self.ordinary = self.getIntParam("ordinary")
        self.good = self.getIntParam("good")
        self.excellent = self.getIntParam("excellent")
        self.magnificent = self.getIntParam("magnificent")
        self.exclusive = self.getIntParam("exclusive")
        self.premium = self.getBoolParam("premium")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"Class": self.Class, "ordinary": self.ordinary, "good": self.good,
                              "excellent": self.excellent, "magnificent": self.magnificent, "exclusive": self.exclusive,
                              "premium": self.premium}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddReforgeTalentsPricesEvent(EventSubAction):
    action = "add_reforge_talents_prices_event"
    # -----------------------------------------
    # Добавляем ивент из старых events.txt

    def onStart(self):
        info("AddReforgeTalentsPricesEvent.onStart %r", self.arguments)
        self.listReforgeTalentPrices = self.getParam("listReforgeTalentPrices", None)
        if self.listReforgeTalentPrices and isinstance(self.listReforgeTalentPrices, basestring):
            self.listReforgeTalentPrices = self.getJsonParam("listReforgeTalentPrices", None)

        if not self.listReforgeTalentPrices:
            self.response["error"] = "bad listReforgeTalentPrices"
            self.response['ok'] = 0
            self.fin()
            return


        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"listReforgeTalentPrices": self.listReforgeTalentPrices}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event
            debug("Event added: %r", self.eventsGroup[self.persistentId])

        self.response['ok'] = 1
        self.fin()

class AddTechsAction(EventSubAction):
    action = "add_techs"
    # -----------------------------------------
    # Добавляем ивент из старых events.txt

    def onStart(self):
        info("AddTechsAction.onStart")
        self.techType = self.getParam("techType")
        self.compensation = self.getIntParam("compensation")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"techType": self.techType, "compensation": self.compensation}}
        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddRerollShopSlotsEventAction(EventSubAction):
    action = "add_reroll_shop_slots_event"
    # -----------------------------------------
    # Добавляем ивент на изменение кол-ва талантов, получаемых за 1 кристалл

    def onStart(self):
        info("AddRerollShopSlotsEventAction.onStart")
        self.usualSlots = self.getIntParam("usualSlots")
        self.premiumSlots = self.getIntParam("premiumSlots")
        self.maxActiveUsualSlots = self.getIntParam("maxActiveUsualSlots")
        self.maxActivePremiumSlots = self.getIntParam("maxActivePremiumSlots")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "defaultValue": {},
                 "newValue": {"usualSlots": self.usualSlots, "premiumSlots": self.premiumSlots,
                 "maxActiveUsualSlots": self.maxActiveUsualSlots, "maxActivePremiumSlots": self.maxActivePremiumSlots}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event
            debug("Event added: %r", self.eventsGroup[self.persistentId])

        self.response['ok'] = 1
        self.fin()

class AddRerollShopPriceEventAction(EventSubAction):
    action = "add_reroll_shop_price_event"
    # -----------------------------------------
    # Добавляем ивент на изменение кол-ва талантов, получаемых за 1 кристалл

    def onStart(self):
        info("AddRerollShopPriceEventAction.onStart")
        self.resource1 = self.getIntParam("resource1")
        self.resource2 = self.getIntParam("resource2")
        self.resource3 = self.getIntParam("resource3")
        self.silver = self.getIntParam("silver")
        self.gold = self.getIntParam("gold")
        self.perl = self.getIntParam("perl")
        self.redPerl = self.getIntParam("redPerl")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "defaultValue": {}, "newValue": {"resource1": self.resource1,
                 "resource2": self.resource2, "resource3": self.resource3, "silver": self.silver,
                 "gold": self.gold, "perl": self.perl, "redPerl": self.redPerl}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event
            debug("Event added: %r", self.eventsGroup[self.persistentId])

        self.response['ok'] = 1
        self.fin()

class AddRerollShopGroupsPriceEventAction(EventSubAction):
    action = "add_reroll_shop_groups_price_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddRerollShopGroupsPriceEventAction.onStart")
        self.groups = self.getJsonParam("groups")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"groups": self.groups}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddRerollShopGroupsProbabilityEventAction(EventSubAction):
    action = "add_reroll_shop_groups_probability_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddRerollShopGroupsProbabilityEventAction.onStart")
        self.groups = self.getJsonParam("groups")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"groups": self.groups}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddRerollShopGroupsCurrenciesEventAction(EventSubAction):
    action = "add_reroll_shop_groups_currencies_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddRerollShopGroupsCurrenciesEventAction.onStart")
        self.groups = self.getJsonParam("groups")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"groups": self.groups}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddRerollShopSlotsPriceEventAction(EventSubAction):
    action = "add_reroll_shop_slots_price_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddRerollShopSlotsPriceEventAction.onStart")
        self.slots = self.getJsonParam("slots")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"slots": self.slots}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddRerollShopSlotsAmountEventAction(EventSubAction):
    action = "add_reroll_shop_slots_amount_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddRerollShopSlotsAmountEventAction.onStart")
        self.slots = self.getJsonParam("slots")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"slots": self.slots}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddFirstBuyPriceEventAction(EventSubAction):
    action = "add_first_buy_price_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddSkinsPriceEventAction.onStart")
        self.firstBuys = self.getJsonParam("firstBuys")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"firstBuys": self.firstBuys}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddPremiumNotInactiveEventAction(EventSubAction):
    action = "add_premium_not_inactive_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddPremiumNotInactiveEventAction.onStart")
        self.isInactive = self.getBoolParam("isInactive")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": self.isInactive, "defaultValue": True}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()

class AddRerollShopGroupsSlotsEventAction(EventSubAction):
    action = "add_reroll_shop_groups_slots_event"
    # -----------------------------------------
    # Добавляем ивент на изменение цены скина в золоте

    def onStart(self):
        info("AddRerollShopGroupsSlotsEventAction.onStart")
        self.groups = self.getJsonParam("groups")

        event = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                 "enabled": self.enabled, "persistentId": self.persistentId,
                 "newValue": {"groups": self.groups}, "defaultValue": {}}

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = event

        self.response['ok'] = 1
        self.fin()


class AddRerollShopBannerAction(EventSubAction):
    action = "add_reroll_shop_banner_event"
    # -----------------------------------------
    # Добавляет новостной баннер

    def onStart(self):
        info("AddRerollShopBannerAction.onStart")
        self.mainUrl = self.getParam("mainUrl")
        self.locale = self.getParam("locale")

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                                                   "enabled": self.enabled, "defaultValue": {},
                                                   "newValue": {"locale": self.locale, "mainUrl": self.mainUrl}}

        self.response['ok'] = 1
        self.fin()

class AddRerollShopTooltipAction(EventSubAction):
    action = "add_reroll_shop_tooltip_event"
    # -----------------------------------------
    # Добавляет тултип для ярмарки

    def onStart(self):
        info("AddRerollShopTooltipAction.onStart")
        self.tooltip = self.getParam("tooltip")
        self.locale = self.getParam("locale")

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = {"startTime": self.startTime, "type": self.type, "endTime": self.endTime,
                                                   "enabled": self.enabled, "defaultValue": {},
                                                   "newValue": {"locale": self.locale, "tooltip": self.tooltip}}

        self.response['ok'] = 1
        self.fin()

class AddRollEventAction(EventSubAction):
    action = "add_roll_event"
    # -----------------------------------------
    # Добавляет событие с роллом

    def onStart(self):
        info("AddRollEventAction.onStart")
        self.locale = self.getParam("locale")
        self.customData = self.getParam("customData")

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] = {"persistentId": self.persistentId, "type": self.type,
                                                   "startTime": self.startTime, "endTime": self.endTime,
                                                   "description": self.description, "enabled": self.enabled,
                                                   "defaultValue": {}, "newValue": json_loads(self.customData)}
        self.response['ok'] = 1
        self.fin()

class AddQuestEventAction(EventSubAction):
    action = "add_quest_event"
    # -----------------------------------------
    # Добавляет событие с квестом

    def onStart(self):
        info("AddQuestEventAction.onStart")
        self.locale = self.getParam("locale")
        self.customData = self.getParam("customData")

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] =  {"persistentId": self.persistentId, "type": self.type,
                                                   "startTime": self.startTime, "endTime": self.endTime,
                                                   "description": self.description, "enabled": self.enabled,
                                                   "defaultValue": {}, "newValue": json_loads(self.customData)}
        self.response['ok'] = 1
        self.fin()

## --------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------
class AddTradeEventAction(EventSubAction):
    action = "add_trade_event"
    # -----------------------------------------

    def onStart(self):
        info("AddTradeEventAction.onStart")
        self.locale = self.getParam("locale")
        self.customData = self.getParam("customData")

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] =  {"persistentId": self.persistentId, "type": self.type,
                                                   "startTime": self.startTime, "endTime": self.endTime,
                                                   "description": self.description, "enabled": self.enabled,
                                                   "defaultValue": {}, "newValue": json_loads(self.customData)}
        self.response['ok'] = 1
        self.fin()

## --------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------
class AddSeasonEventAction(EventSubAction):
    action = "add_season_event"
    # -----------------------------------------

    def onStart(self):
        info("AddSeasonEventAction.onStart")
        self.locale = self.getParam("locale")
        self.customData = self.getParam("customData")

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] =  {"persistentId": self.persistentId, "type": self.type,
                                                   "startTime": self.startTime, "endTime": self.endTime,
                                                   "description": self.description, "enabled": self.enabled,
                                                   "defaultValue": {}, "newValue": json_loads(self.customData)}
        self.response['ok'] = 1
        self.fin()

## --------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------
class AddDonateEventAction(EventSubAction):
    action = "add_donate_event"
    # -----------------------------------------

    def onStart(self):
        info("AddDonateEventAction.onStart")
        #self.locale = self.getParam("locale")
        self.customData = self.getParam("customData")

        if self.eventsGroup is not None:
            self.eventsGroup[self.persistentId] =  {"persistentId": self.persistentId, "type": self.type,
                                                   "startTime": self.startTime, "endTime": self.endTime,
                                                   "description": self.description, "enabled": self.enabled,
                                                   "defaultValue": {}, "newValue": json_loads(self.customData)}
        self.response['ok'] = 1
        self.fin()
## --------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------


class PwJsonHandler( WebJsonHandler ):
    """ реальный обработчик команд PW-шного рабочего сервера (PwWorkServer) """
    
    internalActionMap = mergeDicts( WebJsonHandler.internalActionMap, {
        'sublogin_fsn': AgentSubloginAction,
        'server_party': PersonServerPartyCmdAction,
        'server_friends': PersonServerFriendsCmdAction,
        'ps_resubscribe': "onPersonServerSubscribeAll",
        'change_const': "onChangeConst",
        'calc_top_build':"onCalcTopBuild",
        'resend_top_build': "onResendTopBuild",
        'set_config': "onSetCoordConfigValues",  # динамически меняем одну из настроек конфига; по умолчанию апдейтится на все ws-ки
        'guild_data': GuildDataCmdAction,
        'siege_data': SiegeDataCmdAction,
        'recruits_data': RecruitsDataUpdateAction,
        'guild_resubscribe_to_chat' : GuildResubscribeToChatCmdAction,
        'reload_multi_config': 'onReloadMultiConfig',  # overrided from JsonHandler: умеем перегружать logic_cfg+StaticData со всеми внутренностями, а также logic_update_cfg
        'reload_locale_multi_config': 'onReloadLocaleMultiConfig',  # base JsonHandler: умеем перегружать logic_cfg+StaticData для конкретной локали
        'clear_addr_info': 'onClearAddrInfoCache',  # base JsonHandler: умеем чистить кэш addrinfo (чтобы заново резолвить адреса после перестройки DNS)
        'add_user': AddUserAction,
        'l_merge_internal': LauncherMergeInternalAction,
        'add_new_dynamic_quest': 'onAddNewDynamicQuest',  # добавляем новый динамический квест к StaticData соответствующей локали
        'remove_dynamic_quest': 'onRemoveDynamicQuest', # удаляем указанный динамический квест с сервера
        'clear_dynamic_quests': 'onClearAllDynamicQuests',  # очищаем текущие динамические квесты
        'edit_dynamic_quest': "onEditDynamicQuest",  # обновляем данные о квесте на сервере, в базе и у игроков
        'edit_auids_list': "onEditAuidsListForQuest", # обновляем список ауидов, которым доступен квест
        'add_new_dynamic_quest_pull': "onAddNewDynamicQuestPull",  # Добавляем на сервер новый пулл
        'edit_dynamic_quest_pull': "onAddNewDynamicQuestPull",
        'remove_dynamic_quest_pull': "onRemoveDynamicQuestPull",
        'add_quest_to_pull': "onAddDynamicQuestToPull",  # Добавляем на сервер новый пулл
        'remove_quest_from_pull': "onRemoveDynamicQuestFromPull",  # Добавляем на сервер новый пулл
        'update_top_build':   UpdateTopBuildAction,  # Обновляем данные о топовом билде (раз в сутки)
        'chane_event_state_by_id': ChangeEventStateByIdAction,
        'delete_event_by_id': DeleteEventByIdAction,
        'add_talent_per_perl_event': AddTalentPerPerlEventAction,  # Добавляем ивент на кол-во талантов за кристалл в кузнице
        'add_news_banner_event': AddNewsBannerAction,
        'add_custom_event': AddCustomEventAcion,
        'add_skins_price_event': AddSkinsPriceEventAction,
        'add_heroes_price_event': AddHeroesPriceEventAction,
        'add_custom_map_event': AddCustomMapEventAcion,
        'add_talent_drop_rar_event': AddTalentDropRarityAction,
        'add_techs': AddTechsAction,
        'add_reforge_talents_prices_event': AddReforgeTalentsPricesEvent,
        'add_reroll_shop_slots_event': AddRerollShopSlotsEventAction,
        'add_reroll_shop_price_event': AddRerollShopPriceEventAction,
        'add_reroll_shop_groups_price_event': AddRerollShopGroupsPriceEventAction,
        'add_reroll_shop_groups_probability_event': AddRerollShopGroupsProbabilityEventAction,
        'add_reroll_shop_groups_currencies_event': AddRerollShopGroupsCurrenciesEventAction,
        'add_reroll_shop_slots_price_event': AddRerollShopSlotsPriceEventAction,
        'add_reroll_shop_slots_amount_event': AddRerollShopSlotsAmountEventAction,
        'add_first_buy_price_event': AddFirstBuyPriceEventAction,
        'add_premium_not_inactive_event': AddPremiumNotInactiveEventAction,
        'add_reroll_shop_groups_slots_event': AddRerollShopGroupsSlotsEventAction,
        'add_reroll_shop_banner_event': AddRerollShopBannerAction,
        'add_reroll_shop_tooltip_event': AddRerollShopTooltipAction,
        'add_roll_event': AddRollEventAction,
        'add_quest_event': AddQuestEventAction,
        'add_trade_event': AddTradeEventAction,
        'add_season_event': AddSeasonEventAction,
        'add_donate_event': AddDonateEventAction,
        'update_guild_war_event': UpdateGuildWarEventAction,
        'send_gweventedit_to_stats': 'onSendGWEventEditToStats',
    })
    
    ## _Interfaces = mergeDicts( WebJsonHandler._Interfaces, dict( ZZ=None, AGG=None, MD=None ))
    
    MODULE_NAMES = ["MM", "party_const"]
            
    # ----------------------------------------------------------------------------------------------
    def __init__(self, application, request, **kwargs):
        ##info( "PwJsonHandler internalActionMap:" + str(self.internalActionMap) )
        ##info( "PwJsonHandler _Interfaces:" + str(self._Interfaces) )
        WebJsonHandler.__init__(self, application, request, **kwargs)

    ##----------------------------------------------------------------------------------------------------------------------
    # принимаем post аналогично get """
    def post(self):
        return self.get()
        
    ##----------------------------------------------------------------------------------------------------------------------
    def onSetCoordConfigValues(self):
        json_values = self.getParam("json_values")
        info("onSetCoordConfigValues: json %s" % (json_values))
        try:
            values = json_loads(json_values)
            info("onSetCoordConfigValues: parsed %s" % values)
            
            COORD_PREFIX = "COORDINATOR_"
            for name,value in values.iteritems():
                if name.find(COORD_PREFIX) == 0:
                    # отрезаем префикс (в локальном конфиге имена традиционно без префикса COORDINATOR_xxx)
                    local_name = name[ len(COORD_PREFIX): ]
                    if getattr(cfg, local_name, None) is not None:
                        info("setting config value %r=%r" % (local_name, value))
                        setattr(cfg, local_name, value)
                    else:
                        self.response["error"] = "no such name in local config (%r)" % local_name
                else:
                    self.response["error"] = "no coordinator prefix (%s) in name %r" % (COORD_PREFIX, name)
                    
            self.response["ok"] = 1
                
        except:
            catch()
            self.response["error"] = "can't parse json values"
            warn("onSetCoordConfigValues: can't parse json values")
            
        self.fin() # отправляем ответ
        
    ##----------------------------------------------------------------------------------------------------------------------
    
    def onChangeConst(self):
        """стартовый метод для обработки action"""
        info("onChangeConst")
        
        self.module_name = self.getParam("module", "MM")
        self.var_name = self.getParam("var", "GAME_TYPES")
        self.var_value = self.getJsonParam("value", None)
        
        if self.checkPossibleValue(self.module_name, self.MODULE_NAMES):
            global_dict = globals()
            info( "globals(): %s" % global_dict )
            self.module = global_dict.get( self.module_name )
            if self.module:
                self.var = getattr( self.module, self.var_name, None)
                if (self.var is not None) and (self.var_value is not None):
                    info( "before set: module %s, self.var (%s) = %s" % (self.module, self.var_name, self.var) )
                    
                    self.module.__dict__[ self.var_name ] = self.var_value
                                            
                    new_val = getattr(self.module, self.var_name, None)
                    info( "after set:  self.var (%s) = %s (type %s)" % (self.var_name, new_val, type(new_val)) )
            
                    self.response["var_set"] = self.module_name + "." + self.var_name
                    self.response["value_set"] = new_val
                    self.response["ok"] = 1
                else:
                    self.response["error"] = "bad var or value"
            else:
                self.response["error"] = "bad module name"
            
        self.fin()

        
    #----------------------------------------------------------------------------------------------
    # PersonServer просит прислать ему subcribe по всем существующим юзера (видимо, после рестарта)
    def onPersonServerSubscribeAll(self):
        info( "onPersonServerSubscribeAll: %d active users" % len(users) )
        for uid, acc in users.iteritems():
            self.I.WS.subscribeAccToPersonServer( acc, 0 )
        self.fin()

    def onReloadMultiConfig(self):
        if self.getParam('update', False):
            self.I.WS.updateMultiConfig()
            self.response['ok'] = 1
            self.fin()
        else:
            super(PwJsonHandler, self).onReloadMultiConfig()

    def onCalcTopBuild(self):
        #debug("onCalcTopBuild self.I.WS.get('TopBuildsData')=%r", bool(self.I.WS.get("TopBuildsData")))
        if not self.I.WS.get("TopBuildsData"):
            self.I.WS.calcTopBuildsData = True
            self.response['calcTopBuildsData'] = 0
        else:
            self.response['calcTopBuildsData'] = 1
            self.I.WS.calcTopBuildsData = False
        self.response['ok'] = 1
        self.fin()

    def onResendTopBuild(self):
        arg_servers_ids = self.getParam("servers_id")
        info("onResendTopBuild servers_ids: %r", arg_servers_ids)
        if arg_servers_ids and self.I.WS.get("TopBuildsData"):
            servers_ids = [long(x) for x in arg_servers_ids.split(",")]
            self.I.WS.sendTopBuildData(services=servers_ids)
        self.response['ok'] = 1
        self.fin()

## ----------------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------------


class SocialExchangeJsonHandler( WebJsonHandler ):
    """ принимает post аналогично get """
    def post(self):
        return self.get()
