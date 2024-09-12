#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Mock Social Aggregator web-server
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import functools

import tornado.options
from tornado.options import define, options

addModPath('cfg')
import cfg

from config.MultiConfig import *

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

from handlers import * # JsonHandler, IfaceFactory
from subaction import SubAction, action_timing, separate_timing, ResponseObject

from party_const import *
import MM
import CC
from MM import FriendStatus, GameType2FriendStatus

## ---------------------------------------------------------------------------------------------

from modeldata.changes import PendingChangeWriter, GroupPendingChangeWriter, MakeModelChangeString

from friendsdata.FriendsData import FriendsData
from modeldata.SharedTypes.Friend import Friend

from party.PartyData import PartyData # нужно для создания PartyError

from modeldata.datamanager import PwNewModelManager # от него, вообще-то, нужен только .toJson
from modeldata.MultiStaticData import MultiStaticData
from modeldata.SharedTypes.FriendMMInfo import FriendMMInfo

import ifriendservice
import ipartyservice

# для генерации msg_id нам требуется таймер с хорошим разрешением. под виндой это time.clock (=QueryPerformanceCounter), под Unix это time.time
# тип системы (win/unix) будем определять с помощью грубой подпорки (наличие в ядре getitimer)
if hasattr(signal, "getitimer"):
    good_timer_function = time.time
else:
    good_timer_function = time.clock

## ---------------------------------------------------------------------------------------------

def preview_pending_response( acc, uid, isPretty=1 ):
    response = {}
    SubAction.wrapPendingMessages( acc, uid, response )
    if isPretty:
        return pretty(response)
    else:
        return response
## ---------------------------------------------------------------------------------------------
    
            
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class PersonServerSubAction( SubAction ):
    """ сюда выносим базовые для PersonServer helper-методы """
    def nextMsgID(self):
        return self.I.WS.nextMsgID()
        
    def replyPartyCmd(self, cmd, message, **kwargs):
        self.response["party_events"] = [ 
            dict( to_uid=self.uid,  action="server_party", cmd=cmd, party_id=self.party_id, message=message, msg_id=self.nextMsgID(), **kwargs ) 
        ]

    # поскольку party error должен возвращать и friend_service, отказываемся от идеи писать ошибки в настоящую пользовательскую PartyData,
    # будем использовать специальный fake instance, а id ошибки генерить уникальный, по nextUid (включая id сервиса).
    # шанс что автогенерированный error_id (на 100500 цифр) случайно совпадет с валидным modeldate obj id, практически нулевой.
    def replyPartyError(self, failed_cmd, error_tuple, error_auid=0, ec=EC.GENERIC_PARTY_ERROR, model_tag="PartyData", **kwargs):
        error_code, error_text = error_tuple
        
        party_model_changes = []
        userPartyData, userErrorAcc = self.I.WS.getErrorPartyData()
        userPartyData.next_uid_ = self.I.WS.nextInt64GUID( "party_error" )

        # добавляем ошибку 
        userPartyData.write( userErrorAcc.pending )
        _error, _error_id = userPartyData.newFriendError()
        _error.errorCode = error_code
        _error.errorMessage = urlQuote(error_text)
        _error.auid = error_auid
        userPartyData.errors.add( _error )
        userPartyData.stop()
            
        # изменения (model changes) не надо паковать в JSON, там прозрачный формат
        party_model_changes = self.I.WS.pickPendingPartyChanges( userErrorAcc, to_json=0 )
        kwargs[model_tag] = party_model_changes
        self.replyPartyCmd( "error", error_text, error_code=error_code, error_auid=error_auid, failed_cmd=failed_cmd, **kwargs)
        self.response["ec"] = ec

    def replyInviteError(self, failed_cmd, error_tuple):
        self.replyPartyError( failed_cmd, error_tuple, error_auid=self.invite_auid, invite_auid=self.invite_auid, ec=EC.GENERIC_INVITE_ERROR )
        
    def addPartyError(self, partyData, ec, error_text, auid):
        _error, _error_id = partyData.newFriendError()
        _error.errorCode = ec
        _error.errorMessage = urlQuote(error_text)
        _error.auid = auid
        partyData.errors.add( _error )
        
    def setUserUid(self):
        ws_acc = self.I.WS.ws_accs.get( self.auid )
        if ws_acc:
            self.uid = ws_acc.uid
            self.response["uid"] = self.uid # продублируем в ответ, чтобы WS, если получит авто-отлуп, разобрался, к какому юзеру-команде-партии он относится

        
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class SubscribePersonAction(PersonServerSubAction):
    """ подписка юзеров на PS (фактически - извещение о том что игрок онлайн; 
        заодно WS отдает все равно уже вытащенное из аггрегатора social info, а PS вытаскивает и отдает на WS список френдов """
    action = "subscribe"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info( "SubscribePersonAction" )
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("uid"):
                if self.checkValidIntParam("server"):
                    if self.checkValidParam("snid"):
                        if self.checkValidParam("snuid"):
                            self.nick = self.getParam("nick", "")
                            self.photo = self.getParam("photo", "")
                            self.fame = self.getIntParam("fame", 0)
                            self.fraction = self.getIntParam("fraction", PARTY_FRACTION.NONE)
                            self.locale = self.getParam("locale", "")
                            if self.checkValidParam("sex"):
                                self.sex = toint( self.sex )
                                self.fraction = toint( self.fraction )
                                ## photo = urllib.unquote(self.photo) 
                                ## info( "nick: %r, nick type: %s" % (self.nick, type(self.nick)) )

                                self.acc = self.I.WS.subscribeUserAccount( self.auid, self.snid, self.snuid, self.uid, self.nick, self.photo, \
                                    self.fame, self.fraction, self.sex, self.server, self.locale )

                                self.acc.friendsLoaded = False

                                self.I.AGG.getFriendsInfo(self.auid, 0, 0, 0, self.onGetFriendsInfo)
                                #
                                # сейчас мы заставляем WS ждать, пока аггрегатор не отдаст нам список френдов.
                                #TODO: сделать асинхронную схему, когда апдейты френдов будут доставляться на WS отдельным направленным send-ом из PS
                                #
                                return 
                
        self.fin()
                        
    @action_timing
    def onGetFriendsInfo(self, res): # reply теперь приходит сразу распарсенный до dict-содержимого
        try:
            info( "onGetFriendsInfo(auid=%s): %s", self.auid, str(res)[:128])
            #debug( "onGetFriendsInfo(auid=%s): %s", self.auid, str(res))

            friends = res.get("get_friends_info_all") or {}

            self.response["get_friends"] = friends
            self.response["uid"] = self.uid
            self.response["msg_id"] = self.nextMsgID()
            self.response["ok"] = 1

            #~ # 1) разослать инфу о нашем появлении на сервере всем, у кого мы есть во френдах:
            #~ friends_model_changes = self.I.WS.pickPendingFriendsChanges( self.acc )
            #~ self.I.WS.sendFriendsBroadcast( self.acc, friends.keys(), "change", friend_auid=self.auid, json_FriendsData=friends_model_changes )
            
            #~ info("OUR online-coming info: %s" % friends_model_changes)
            
            # model changes, которые нагенерируются для нашего acc.FriendsData, игнорируем (т.к. все равно будем отсылать полный FriendsData init)
            self.acc.FriendsData.stop()
        
            # нам добавить (и отослать в виде FriendsData init) всю инфу по френдам, какую вернул соц.аггрегатор
            try:
                self.I.WS.addUserFriends( self.auid, self.acc, friends )
            except:
                catch()
                self.response["error"] = "addUserFriends failed for auid=%r (friends=%r)" % (self.auid, friends)
            
            friends_model_init = [ MakeModelChangeString("init_friends", "/", "init", self.acc.FriendsData.generateJsonDict()) ]
            self.response["FriendsData"] = friends_model_init
            
            _callback = functools.partial( self.I.WS.onUpdatePeerFriends, auid=self.auid )
            self.I.FRIENDS.updateFriendList( self.auid, self.acc.FriendsData.myFriends.keys(), _callback )

            ## info("online-coming(auid=%s) FRIENDS info: %s" % (self.auid, self.response.get("FriendsData")))
            
            # на старте клиенту нужен апдейт PartyData
            if self.acc.party_id:
                self.I.PARTY.partyRelogin( self.acc.party_id, self.acc.auid ) # init существующей PartyData придет юзеру направленным send-ом с PartyService
            else:
                # можем сами отослать пустой party init
                party_model_init = [ MakeModelChangeString("init_party", "/", "init", {}) ]
                self.response["PartyData"] = party_model_init
            
            # включаем генерацию model changes обратно
            self.acc.FriendsData.write( self.acc.pending ) 

            friend = self.acc.FriendsData.findPersonByUid( self.auid )
            if friend:
                self.I.WS.updatePersonInfo( friend, self.acc, forceUpdate=True )

            # --- разослать инфу об изменениях user game data всем, у кого мы есть во френдах:
            if self.acc.pending_changes:
                friends_model_changes = self.I.WS.pickPendingFriendsChanges( self.acc )
                ## info("online-coming(auid=%s) broadcast friends_model_changes: %s" % (self.auid, friends_model_changes))
                self.I.WS.sendFriendsBroadcast( self.acc, self.acc.FriendsData.myFriends.keys(), "change", friend_auid=self.auid,  json_FriendsData=friends_model_changes )

                #! если чувак в партии, те же изменения надо донести в party person
                if self.acc.party_id:
                    self.I.PARTY.updateGameData( self.acc.auid, self.acc.party_id, friends_model_changes )

            self.acc.friendsLoaded = True
            # А теперь асинхронно подгрузим недавних соратников
            self.I.DATA.find_one(CC.RECENT_ALLIES_DATA, CC.RECENT_ALLIES_DATA, {"key": self.auid}, self.onRecentAlliesDataFound)
        except:
            catch()
            self.response["error"] = res.get("error")

        self.fin()

    def onRecentAlliesDataFound(self, response):
        if response and "r" in response:
            try:
                self.recent_allies = response["r"]["data"] or []
            except Exception:
                warn("Failed to load recent allies, mongo response: %r", response)
                self.recent_allies = []
            if self.recent_allies:
                new_allies_str = ','.join(ally for ally in self.recent_allies)
                self.I.AGG.getInfos(new_allies_str, None, self.onAggGetRecentAlliesInfo)
        else:
            err("SubscribePersonAction.onRecentAlliesDataFound: failed to get recent allies list")

    def onAggGetRecentAlliesInfo(self, response):
        debug("onAggGetRecentAlliesInfo: %r", response)
        if response:
            ec = toint(response.get("error"))
            pers_infos = response.get("get_infos", {})
            if (ec == 0) and pers_infos:
                acc = self.I.WS.users.get(self.auid)
                if acc:
                    acc.FriendsData.write(acc.pending)
                    self.I.WS.fillRecentAlliesInfoFromAgg(acc, pers_infos, self.recent_allies)
                    friends_model_changes = self.I.WS.pickPendingFriendsChanges(acc)
                    if friends_model_changes:
                        info("fillRecentAlliesInfoFromAgg (auid=%s): friends_model_changes=%s", acc.auid, friends_model_changes)
                        self.I.WS.sendFriendsBroadcast(acc, [acc.auid], "change", friend_auid=self.auid, json_FriendsData=friends_model_changes)
                else:
                    warn("onAggGetRecentAlliesInfo: no such acc (auid=%s)", self.auid)
            else:
                warn("onAggGetRecentAlliesInfo: bad ec(%s) or pers_info(%s) for auid=%s", ec, pers_infos, self.auid)
        else:
            warn("onAggGetRecentAlliesInfo: bad res for auid=%s", self.auid)

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class UpdateGameDataAction( PersonServerSubAction ):
    """ подписка юзеров на PS (фактически - извещение о том что игрок онлайн; 
        заодно WS отдает все равно уже вытащенное из аггрегатора social info, а PS вытаскивает и отдает на WS список френдов """
    action = "update_game_data"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        info( "UpdateGameDataAction" )
        if self.checkValidIntParam("auid"):
            if self.checkValidParam("nick"):
                self.nick = urllib.unquote( self.nick )
                self.fame = self.getIntParam("fame", 0)
                self.fraction = self.getIntParam("fraction", PARTY_FRACTION.NONE)
                self.locale = self.getParam("locale", "")
                self.sex = self.getIntParam("sex", 0)

                acc = self.I.WS.subscribeUserAccount( self.auid, nick=self.nick, fame=self.fame, fraction=self.fraction, locale=self.locale, sex=self.sex )
                if acc:
                  if acc.friendsLoaded:
                    # --- разослать инфу об изменениях user game data всем, у кого мы есть во френдах:
                    friends_model_changes = []
                    if acc.pending_changes:
                        friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                        self.I.WS.sendFriendsBroadcast( acc, acc.FriendsData.myFriends.keys(), "change", friend_auid=self.auid, \
                            json_FriendsData=friends_model_changes )

                    if acc.party_id:
                        self.hero_id = self.getIntParam("hero_id", 0)
                        self.hero_lvl = self.getIntParam("hero_lvl", 0)
                        self.hero_force = self.getFloatParam("hero_force", 0.0)
                        self.hero_rating = self.getFloatParam("hero_rating", 0.0)
                        self.I.PARTY.updateGameData( acc.auid, acc.party_id, friends_model_changes, \
                            hero_id=self.hero_id, hero_lvl=self.hero_lvl, hero_force=self.hero_force, hero_rating=self.hero_rating, sex=self.sex )
                    
                    self.response["ok"] = 1
                  else:
                    warn("Cancel UpdateGameDataAction, acc(auid=%s) still waiting for a friends", self.auid)
                    warn("       acc.friendsLoaded = %s", acc.friendsLoaded)
                else:
                    warn("Out of order UpdateGameDataAction, no acc for auid=%s" % self.auid)
                        
        self.fin()

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class UnsubscribePersonAction( PersonServerSubAction ):
    """ подписка юзеров на PS (фактически - извещение о том что игрок онлайн; 
        заодно WS отдает все равно уже вытащенное из аггрегатора social info, а PS вытаскивает и отдает на WS список френдов """
    action = "unsubscribe"    
    # -----------------------------------------
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("auid"):
            # можно больше не апдейтить список френдов данного юзера
            self.I.WS.unsubscribeUserAccount( self.auid )
            self.response["ok"] = 1            
        self.fin()
    
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class AddFriendAction( PersonServerSubAction ):
    """ добавляем друга в список друзей в аггрегаторе """
    action = "add_friend"    
    # -----------------------------------------
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("auid") and self.checkValidIntParam("friend_auid"):
            if self.auid != self.friend_auid:
                info("AddFriendAction arguments %r" % self.arguments)
                snid = self.getParam("snid")
                aggregator_up = self.getParam("no_aggregator_up") is None
                if snid and aggregator_up:
                    info("AddFriendAction: auid=%s, friend_auid=%s, snid=%s" % (self.auid, self.friend_auid, snid))
                    self.I.AGG.addSnFriend(self.auid, self.friend_auid, snid, callback=self.onAggregatorAddFriend)
                elif aggregator_up:
                    info("AddFriendAction: auid=%s, friend_auid=%s" % (self.auid, self.friend_auid))
                    self.I.AGG.addFriend(self.auid, self.friend_auid, callback=self.onAggregatorAddFriend)
                else:
                    info("AddFriendAction: no update Aggregator for auid=%s, friend_auid=%s" % (self.auid, self.friend_auid))
                    self.onAggregatorAddFriend(True)
                self.response["ok"] = 1
            else:
                warn("trying to add self as friend, skipped (auid=%s, friend_auid=%s)" % (self.auid, self.friend_auid))
            self.fin()

    @separate_timing
    def onAggregatorAddFriend(self, res):
        #info("AddFriendAction: onAggregatorAddFriend: %r" % res)
        if res:
            acc = self.I.WS.getUserAcc( self.auid )
            #info("AddFriendAction: onAggregatorAddFriend acc: %r self.auid:[%r]" % (acc,self.auid))
            if acc:
                # посмотрим по индексу ws_accs -- есть ли friend_auid сейчас онлайн
                ws_acc = self.I.WS.ws_accs.get( self.friend_auid )
                if ws_acc and ws_acc.server:
                    # друг онлайн; отсылаем ему наши персональные данные, и просим в ответ прислать его перс.данные
                    self.I.FRIENDS.updateAddFriend( self.friend_auid, self.auid, acc, send_personal_info=1 )
                else:
                    # друга нет онлайн; запросим персональные данные из аггрегатора
                    self.I.AGG.getInfo( self.friend_auid, None, False, callback=self.onGetFriendInfo )
            else:
                warn("AddFriendAction: onAggregatorAddFriend: no such acc (auid=%s)" % (self.auid))

    @separate_timing
    def onGetFriendInfo(self, res):
        info("onGetFriendInfo: %r" % res)
        if res:
            ec = toint(res.get("error"))
            pers_info = res.get("get_info", {})
            props = pers_info.get("props", {})
            if (ec == 0) and pers_info and props:
                acc = self.I.WS.getUserAcc(self.auid)
                if acc:
                    fsn = props.get("fsn", "")
                    fsn_info = pers_info.get(fsn, {})

                    acc.FriendsData.write(acc.pending)
                    self.I.WS.setPersonAUID(self.friend_auid)  # пусть FriendsData выдаст friend_id == self.friend_auid
                    friend, friend_id = acc.FriendsData.newFriend()
                    assert( friend_id == self.friend_auid)
                    friend.person_uid = self.friend_auid
                    self.I.WS.fillFriendsData(friend, pers_info, props, fsn_info)
                    acc.FriendsData.myFriends.add(self.friend_auid)

                    if acc.FriendsData.removeRecentAlly(self.friend_auid):
                        self.I.WS.saveRecentAllies(self.auid, acc.FriendsData.RecentAllies)
                    friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                    info("onGetFriendInfo (auid=%s): friends_model_changes=%s", acc.auid, friends_model_changes)
                    if friends_model_changes:
                        self.I.WS.sendFriendsBroadcast(acc, [acc.auid], "change", friend_auid=self.friend_auid,
                                                       json_FriendsData=friends_model_changes)
                else:
                    warn("onGetFriendInfo: bad acc for auid=%s", self.auid)
            else:
                warn("onGetFriendInfo: bad ec(%s) pers_info(%s) or props(%s) for friend_auid=%s (auid=%s)",
                     ec, pers_info, props, self.friend_auid, self.auid)
        else:
            warn("onGetFriendInfo: bad res for friend_auid=%s (auid=%s)", self.friend_auid, self.auid)

class RefreshFriendAction( PersonServerSubAction ):
    """ обновление списока друзей в WS """
    action = "refresh_friend"
    # -----------------------------------------
    @action_timing
    def onStart(self):
        self.checkValidIntParam("auid")
        self.I.AGG.getFriendsInfo(self.auid, include_secure_data=0,skip=0,limit=0, callback=self.onGetFriendInfo)
        #info("FS_INFO: onStart %r " % self.auid)

    @separate_timing
    def onGetFriendInfo(self, res):
        #info("FS_INFO: res %r " % res)
        if res:
            user_info = {}
            #info("FS_INFO_JSON: refresh_friend %r " % res)
            all_friends_list = res.get('get_friends_info_all', None)
            if self.auid and all_friends_list:
                acc = self.I.WS.getUserAcc(self.auid)
                #info("onGetFriendInfo: refresh_friend %r, self.auid[%r] " % (acc, self.auid))
                if acc:
                    user_info = acc.FriendsData.myFriends.keys()
                #info("onGetFriendInfo: refresh_friend %r " % user_info)
                for friend_auid in all_friends_list:
                    if friend_auid not in user_info:
                        #info("onGetFriendInfo: friend_auid [%r] " % friend_auid)
                        # дружим обоих
                        self.I.FRIENDS.addFriend(self.auid, friend_auid, None, no_aggregator_up=True)
                        self.I.FRIENDS.addFriend(friend_auid, self.auid, None, no_aggregator_up=True)
                        info("RefreshFriendAction [addFriend]: auid [%r] for friend_auid[%r] " % (self.auid, friend_auid,))
                        self.response["ok"] = 1
            else:
                warn("trying to add self as friend, skipped (auid=%s) OR Valid Error" % (self.auid))
        else:
            warn("No friends founds OR Valid Error")
        self.fin()

# -----------------------------------------

class UpdateGuildShortNameAction( AddFriendAction ):
    """ добавляем друга в список друзей в аггрегаторе """
    action = "update_guildshortname"    
    
    # -----------------------------------------
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc( self.auid )
            if acc:
                guildshortname = self.getParam("guildshortname", "")
                if guildshortname == "-":
                    guildshortname = ""
                acc.guildshortname = guildshortname

                you = acc.FriendsData.findPersonByUid(acc.auid)
                if you:
                    acc.FriendsData.write( acc.pending ) 
                    you.guildshortname = acc.guildshortname
                    friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                    if friends_model_changes:
                        self.I.WS.sendFriendsBroadcast( acc, acc.FriendsData.myFriends.keys(), "change", friend_auid=acc.auid, json_FriendsData=friends_model_changes )
            else:
                warn("UpdateAddFriendAction: no such acc(auid=%s)",  self.auid)
                
        self.fin()


class UpdateAddFriendAction( AddFriendAction ):
    """ добавляем друга в список друзей в аггрегаторе """
    action = "fs_update_add_friend"    
    
    # -----------------------------------------
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("friend_auid"):
                send_my_info = self.getIntParam("send_personal_info", 0)
                friend_acc_on = self.getIntParam("friend_acc_on", 0)
                info("UpdateAddFriendAction: %s -> %s" % (self.auid, self.friend_auid))
                if friend_acc_on:
                    acc = self.I.WS.getUserAcc( self.auid )
                    if acc:
                        # Добавляем себе в друзья
                        acc.FriendsData.write( acc.pending ) 
                        self.I.WS.setPersonAUID( self.friend_auid ) # пусть FriendsData выдаст friend_id == self.friend_auid
                        friend, friend_id = acc.FriendsData.newFriend()
                        assert( friend_id == self.friend_auid)
                        friend.person_uid = self.friend_auid

                        friend.guildshortname = self.getParam("guildshortname", "")
                        if friend.guildshortname == "-":
                            friend.guildshortname = ""
                        friend.nickName = utf8convert( urllib.unquote( self.getParam("nickName", "") ) )
                        friend.gender = self.getIntParam("gender", 0)
                        friend.fraction = self.getIntParam("fraction", 0)
                        friend.photoUrl = utf8convert( urllib.unquote( self.getParam("photoUrl", "") ) )
                        friend.fame = self.getIntParam("fame", 0)
                        friend.online = self.getBoolParam("online")
                        friend.InMatchmaking = False # КОСТЫЛЬ; трудновато доставать прогресс-статус?..
                        friend.mmStartTime = 0 # КОСТЫЛЬ; трудновато доставать прогресс-статус?..
                        friend.Status = self.getIntParam("Status", 0)
                        friend.lastLoginTime = self.getIntParam("lastLoginTime", 0)
                        friend.lastLogoutTime = self.getIntParam("lastLogoutTime", 0)
                        friend.IsMuted = bool(self.getIntParam("isMuted", 0))
                        
                        acc.FriendsData.myFriends.add(friend_id)

                        friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                        if friends_model_changes:
                            self.I.WS.sendFriendsBroadcast( acc, [acc.auid], "change", friend_auid=self.friend_auid, json_FriendsData=friends_model_changes )

                        acc.FriendsData.write(acc.pending)
                        # Отдельным пакетом удалим друга из недавних друзей, чтобы клиентская FriendsData не запуталась
                        if acc.FriendsData.removeRecentAlly(self.friend_auid):
                            self.I.WS.saveRecentAllies(self.auid, acc.FriendsData.RecentAllies)
                            friends_model_changes = self.I.WS.pickPendingFriendsChanges(acc)
                            if friends_model_changes:
                                self.I.WS.sendFriendsBroadcast(acc, [acc.auid], "change", friend_auid=self.friend_auid, json_FriendsData=friends_model_changes)
                    else:
                        warn("UpdateAddFriendAction: no such acc(auid=%s)", self.auid)
                        
                    if send_my_info:
                        info("send_my_info: %s -> %s", self.friend_auid, self.auid)
                        self.I.FRIENDS.updateAddFriend( self.friend_auid, self.auid, acc )
                else:
                    # все-таки друга нет онлайн; запросим его персональные данные из аггрегатора
                    self.I.AGG.getInfo( self.friend_auid, None, False, callback=self.onGetFriendInfo )
                    
        self.fin()
    
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class DeleteFriendAction( PersonServerSubAction ):
    """ убираем друга из списка друзей в аггрегаторе """
    action = "delete_friend"    
    # -----------------------------------------
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("friend_auid"):
                if self.auid != self.friend_auid:
                    info("DeleteFriendAction: auid=%s, friend_auid=%s" % (self.auid, self.friend_auid))
                    self.I.AGG.deleteFriend(self.auid, self.friend_auid, callback=self.onAggregatorDeleteFriend)
                    self.response["ok"] = 1
            else:
                snid = self.getParam("snid")
                if snid:
                    info("DeleteFriendAction: auid=%s, snid=%s" % (self.auid, snid))
                    self.I.AGG.deleteSnFriends(self.auid, snid, callback=self.onAggregatorDeleteSnFriends)
                    self.response["ok"] = 1
        self.fin()
        
    @action_timing
    def onAggregatorDeleteFriend(self, res):
        #info("onAggregatorDeleteFriend: %r" % res)
        if res:
            self.I.FRIENDS.updateDeleteFriend( self.auid, self.friend_auid ) # удаляем друга у себя
            self.I.FRIENDS.updateDeleteFriend( self.friend_auid, self.auid ) # удаляем себя у друга
            
    @action_timing
    def onAggregatorDeleteSnFriends(self, res):
        #info("onAggregatorDeleteSnFriends: %r" % res)
        if res and not res['error']:
            for pair in res['pairs']:
            # res['pairs'] is a list of deleted friendship links [auid, friendAuid],
            # containing 2 elements for each pair: [a1, a2] and [a2, a1]
                self.I.FRIENDS.updateDeleteFriend( pair[0], pair[1] )

##---------------------------------------------------------------------------------------------------

class UpdateDeleteFriendAction(PersonServerSubAction):
    """ апдейт model changes по случаю удаления друга """
    action = "fs_update_delete_friend"    
    # -----------------------------------------
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("auid"):
            if self.checkValidIntParam("friend_auid"):  
                acc = self.I.WS.getUserAcc( self.auid )
                if acc:
                    # Удаляем у себя друга
                    acc.FriendsData.write( acc.pending ) 
                    friend = acc.FriendsData.findPersonByUid( self.friend_auid )
                    if friend:
                        acc.FriendsData.myFriends.remove( friend )
                        friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                        if friends_model_changes:
                            self.I.WS.sendFriendsBroadcast( acc, [acc.auid], "change", friend_auid=self.friend_auid, json_FriendsData=friends_model_changes )
                        self.response["ok"] = 1
                else:
                    warn("UpdateDeleteFriendAction: no such acc (auid=%s)" % self.auid)
        self.fin()
        
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class InCastlePersonAction( PersonServerSubAction ):
    """ WS извещает нас, что у юзера [не]живой замок ([не] присылает keepalive) """
    @action_timing
    def onStart(self):
        self.auid = self.getIntParam("auid", 0)
        self.on = self.getIntParam("on", 0)
        self.acc = self.I.WS.users.get( self.auid )
        if self.acc:
            self.acc.in_castle = self.on
            info( "change auid=%s in_castle status: %s" % (self.auid, self.on))
            if self.acc.friend_status in [FriendStatus.INCASTLE, FriendStatus.LOADING, FriendStatus.AFK]:
                self.I.WS.setFriendStatus(self.acc, FriendStatus.INCASTLE, friend_update=True, party_update=True)
        self.response["ok"] = 1
        self.fin()


##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class AFKPersonAction( PersonServerSubAction ):
    """ WS извещает нас, что юзер отошёл """
    @action_timing
    def onStart(self):
        self.auid = self.getIntParam("auid", 0)
        self.acc = self.I.WS.users.get( self.auid )
        if self.acc:
            info( "set auid=%s afk status", self.auid)
            if self.acc.friend_status in [FriendStatus.INCASTLE]:
                self.I.WS.setFriendStatus(self.acc, FriendStatus.AFK, friend_update=True, party_update=False)
        self.response["ok"] = 1
        self.fin()

class MutePersonAction( PersonServerSubAction ):
    """ WS извещает нас, что юзер отошёл """
    @action_timing
    def onStart(self):
        self.auid = self.getIntParam("auid", 0)
        self.isMuted = self.getIntParam("isMuted", 0)
        self.acc = self.I.WS.users.get( self.auid )
        if self.acc:
            info( "set auid=%s muted status %s", self.auid, self.isMuted)
            self.I.WS.setFriendMutedStatus(self.acc, self.isMuted, friend_update=True, party_update=False)
        self.response["ok"] = 1
        self.fin()
    
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class RemovePartyInviteAction( PersonServerSubAction ):
    """ PartyS извещает нас, что у юзера удаляется pending invite """
    @action_timing
    def onStart(self):
        self.auid = self.getIntParam("auid", 0)
        self.master_auid = self.getIntParam("master_auid", 0)
        self.party_id = self.getIntParam("party_id", 0)
        self.reason = self.getParam("reason")
        acc = self.I.WS.users.get( self.auid )
        if acc:
            info( "RemovePartyInviteAction (auid=%s) acc.FriendsData.invites=%s, acc.online=%s" % (self.auid, acc.FriendsData.invites.keys(), acc.online))
            acc.FriendsData.invites.deleteByID( self.master_auid )
            
            if acc.online:
                # если online -- нужно отослать model changes
                friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )                         
                self.I.WS.sendFriendsDataMessage( acc, "invite_removed", message=self.reason, party_id=self.party_id, master_auid=self.master_auid, \
                    invite_auid=acc.auid, json_FriendsData=friends_model_changes )
            
            self.response["ok"] = 1
        else:
            warn( "RemovePartyInviteAction: no acc for auid=%s" % self.auid )
            
        self.fin()

## ---------------------------------------------------------------------------------------------

class RemovePartyIdAction( PersonServerSubAction ):
    """ PartyS извещает нас, что юзер покинул партию (надо почистить party_id) """
    @action_timing
    def onStart(self):
        self.auid = self.getIntParam("auid", 0)
        self.master_auid = self.getIntParam("master_auid", 0)
        self.party_id = self.getIntParam("party_id", 0)
        acc = self.I.WS.users.get( self.auid )
        if acc:
            info( "RemovePartyIdAction auid=%s, party_id=%s, acc.party_id=%s" % (self.auid, self.party_id, acc.party_id) )
            
            if self.party_id == acc.party_id:
                acc.party_id = 0
            
            self.response["ok"] = 1
        else:
            warn( "RemovePartyIdAction: no acc for auid=%s" % self.auid )
            
        self.fin() 
        
## ---------------------------------------------------------------------------------------------

class UpdateWsAccAction( PersonServerSubAction ):
    """ FS извещает, что юзер теперь онлайн/оффлайн на таком-то рабочем сервере """
    @action_timing
    def onStart(self):
        self.auid = self.getIntParam("auid", 0)
        self.server = self.getIntParam("server", 0)
        self.uid = self.getIntParam("uid", 0)
        info("UpdateWsAccAction: auid=%s, uid=%s, ws server=%s" % (self.auid, self.uid, self.server))
        
        self.I.WS.updateWsAcc( self.auid, self.uid, self.server, retranslate=False )
        self.response["ok"] = 1
        self.fin()


## ---------------------------------------------------------------------------------------------

class UpdateFriendListAction( PersonServerSubAction ):
    """ peer FS извещает, что юзер получил список друзей от аггрегатора, и теперь желает апдейта person_info по всем френдам, которые онлайн на нашем FS """
    @action_timing
    def onStart(self):
        self.auid = self.getIntParam("auid", 0)
        self.friend_auids = json_loads( self.getParam("friend_auids", "") )
        if isinstance(self.friend_auids, list):
            reply_persons = {}
            for friend_auid in self.friend_auids:    
                acc = self.I.WS.users.get( friend_auid )
                if acc:
                    friend_person = acc.FriendsData.findPersonByUid( friend_auid )
                    if friend_person:
                        reply_persons[ friend_auid ] = friend_person.generateJsonDict().get("Friend",{})
                    else:
                        warn("UpdateFriendListAction(auid=%s): bad self person for friend_auid=%s" % (self.auid, friend_auid))
                    
            self.response["persons"] = reply_persons
            self.response["ok"] = 1
        else:
            warn("UpdateFriendListAction: empty friend_auids for auid=%s" % self.auid)
        self.fin()

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class TamburAddPersonAction( PersonServerSubAction ):
    action = 'fs_tambur_add'
    """ """
    def onStart(self):
        if self.checkValidIntParam("auid"):
            self.setUserUid()
            if self.checkValidIntParam("game_id"):
                if self.checkValidParam("allies_key"):
                    self.acc = self.I.WS.getUserAcc( self.auid )
                    if self.acc:
                        self.acc.game_id = self.game_id
                        args = self.getFlatParams( except_list=['auid', 'game_id', 'action'] )
                        
                        person = self.acc.FriendsData.findPersonByUid( self.auid )
                        if person:
                            json_person = json_dumps( person.generateJsonDict().get("Friend",{}) )
                            return self.I.PARTY.tamburAddPerson( self.game_id, self.auid, self.onTamburAdd, json_person=json_person, **args ) 
                        else:
                            return self.fail( EC.GENERIC_PARTY_ERROR, "no person (auid=%s)" % self.auid )
                    else:
                        return self.fail( EC.FRIENDS_NO_ACC, "no such acc(auid=%s)" % self.auid )
        self.fin()
    
    def onTamburAdd(self, response):
        if response and response.get("ok"):
            # копируем ответ WS-ке
            subDictUpdateListsAppend( self.response, response )
            # прикапываем у себя все реквизиты тамбура (потом понадобятся для маппинга тамбур-команд)
            self.acc.tambur_id = toint( response.get("tambur_id", 0) )
            self.acc.game_id = self.game_id
            self.acc.allies_key = self.allies_key
            info("onTamburAdd: (auid=%s) stored tambur_id=%s, game_id=%s, allies_key=%s" % (self.auid, self.acc.tambur_id, self.acc.game_id, self.acc.allies_key))
        self.fin()

## ---------------------------------------------------------------------------------------------

class RemoveTamburIdAction( PersonServerSubAction ):
    action = 'fs_remove_tambur_id'
    """ """
    def onStart(self):
        if self.checkValidIntParam("tambur_id"):
            if self.checkValidParam("json_auids"):
                self.auids = json_loads( self.json_auids )
                for auid in self.auids:
                    acc = self.I.WS.getUserAcc( auid )
                    if acc:
                        info("RemoveTamburIdAction: acc auid=%s, acc.tambur_id=%s, action tambur_id=%s" % (auid, acc.tambur_id, self.tambur_id))
                        if acc.tambur_id == self.tambur_id:
                            acc.tambur_id = None
                            acc.game_id = 0
        self.fin()
    

## ---------------------------------------------------------------------------------------------

class PartyInviteAction( PersonServerSubAction ):
    action = 'fs_party_invite'
    """ """
    def onStart(self):
        if self.checkValidIntParam("auid"):
            self.setUserUid()
            if self.checkValidIntParam("invite_auid"):
                if self.checkValidIntParam("party_id"):
                    if self.checkValidParam("game_type"):
                        self.is_temp_party_id = self.getIntParam("is_temp_party_id")
                        self.acc = self.I.WS.getUserAcc( self.auid )
                        if self.acc:
                            if self.auid != self.invite_auid:
                                if not self.acc.mm_progress:
                                    if not self.acc.party_id:
                                        self.acc.party_id = self.party_id
                                        
                                    self.as_enemy = self.getIntParam("as_enemy", 0) # 0/1, приглашаем как противника (на договорной матч)
                                    self.with_bots = self.getIntParam("with_bots", 0) # 0/1, приглашаем на бой с ботами
                                    self.flagType = self.getIntParam("flagType")
                                    self.flagPersistentId = self.getParam("flagPersistentId")
                                    self.isMMAllowed = self.getBoolParam("isMMAllowed")
                                    self.isInventoryFull = self.getBoolParam("isInventoryFull")
                                    self.isLeaver = self.getBoolParam("isLeaver")
                                    self.banEndTime = self.getIntParam("banEndTime")
                                    self.tournamentDynQuestId = self.getIntParam("tournamentDynQuestId",-1)
                                    self.dependedTournamentQuests =  self.getParam("dependedTournamentQuests","-1")

                                    # ок, местные проверки прошли; добавляем person info и пересылаем на FS[invite_auid]
                                    master_person = self.acc.FriendsData.findPersonByUid( self.auid )
                                    if master_person:
                                        json_master_person = json_dumps( master_person.generateJsonDict().get("Friend",{}) )
                                        
                                        return self.I.FRIENDS.partyInviteFromMaster( self.invite_auid, self.onInviteFromMaster,
                                            auid=self.auid, party_id=self.party_id, json_master_person=json_master_person,
                                            master_fraction=master_person.fraction, as_enemy=self.as_enemy, game_type=self.game_type,
                                            with_bots=self.with_bots, flagType=self.flagType, flagPersistentId=self.flagPersistentId,
                                            isMMAllowed=self.isMMAllowed, isInventoryFull=self.isInventoryFull,isLeaver=self.isLeaver,banEndTime=self.banEndTime,
                                            tournamentDynQuestId=self.tournamentDynQuestId, dependedTournamentQuests= self.dependedTournamentQuests )
                                    else:
                                        self.response["error"] = "no master person (auid=%s)" % (self.auid)
                                        self.replyInviteError( "invite", PARTY_ERROR.BAD_MASTER_AUID )
                                                                    
                                else:
                                    self.response["error"] = "master user %s in game/matchmaking, mm_progress %s" % (self.auid, self.acc.mm_progress)
                                    self.replyInviteError( "invite", PARTY_ERROR.USER_IN_GAME )
                            else:
                                self.response["error"] = "cant invite self (invite_auid %d, self auid %d)" % (self.invite_auid, self.auid)
                                self.replyInviteError( "invite", PARTY_ERROR.CANT_INVITE_SELF )
                        else:
                            self.response["error"] = "no such acc(auid=%s)" % self.auid
                            self.replyInviteError( "invite", PARTY_ERROR.USER_NOT_ONLINE )
                            #return self.fail( EC.FRIENDS_NO_ACC, "no such acc(auid=%s)" % self.auid )
        self.fin()

    def onInviteFromMaster(self, response):
        # если запрос пофейлился, а выданный party_id был временный, нужно его зачистить
        if (not response) or (not response.get("ok", 0)):
            if self.is_temp_party_id:
                self.acc = self.I.WS.getUserAcc( self.auid )
                if self.acc and self.acc.party_id and (self.acc.party_id == self.party_id):
                    info("onInviteFromMaster: clearing temp party_id=%s for auid=%s" % (self.party_id, self.auid))
                    self.acc.party_id = 0
                            
        # просто перекидываем финальный ответ от FS[invite_auid] обратно на WS
        subDictUpdateListsAppend( self.response, response )
        self.fin()
        
##---------------------------------------------------------------------------------------------------
    
class PartyInviteFromMasterAction( PersonServerSubAction ):
    action = 'fs_party_invite_from_master'
    """ """
    def onStart(self):
        if self.checkValidIntParam("auid"):
            self.setUserUid()
            if self.checkValidIntParam("invite_auid"):
                if self.checkValidIntParam("party_id"):
                    if self.checkValidParam("game_type"):
                        self.invite_acc = self.I.WS.getUserAcc( self.invite_auid )
                        if self.invite_acc:
                            if self.invite_acc.uid is None:
                                warn( "invite_acc %r", self.invite_acc)
                            if self.invite_acc.online:
                                self.master_fraction = self.getIntParam("master_fraction")
                                json_master_person = self.getParam("json_master_person")
                                self.as_enemy = self.getIntParam("as_enemy", 0)
                                self.with_bots = self.getIntParam("with_bots", 0)
                                self.flagType = self.getIntParam("flagType")
                                self.flagPersistentId = self.getParam("flagPersistentId")
                                self.isMMAllowed = self.getBoolParam("isMMAllowed")
                                self.isInventoryFull = self.getBoolParam("isInventoryFull")
                                self.isLeaver = self.getBoolParam("isLeaver")
                                self.banEndTime = self.getIntParam("banEndTime")
                                self.tournamentDynQuestId = self.getIntParam("tournamentDynQuestId",-1)
                                self.dependedTournamentQuests = self.getParam("dependedTournamentQuests","-1")

                                self.master_person_dict = json_loads( json_master_person )
                                if not self.invite_acc.party_id:
                                    if not self.invite_acc.mm_progress:
                                        #------------------------------------------------------------------------------------------
                                        # ок, местные проверки прошли; добавляем person info и пересылаем на FS[invite_auid]
                                        invited_person = self.invite_acc.FriendsData.findPersonByUid( self.invite_auid )
                                        if invited_person:
                                            json_invited_person = json_dumps( invited_person.generateJsonDict().get("Friend",{}) )

                                            info("json_master_person=%r" % json_master_person)
                                            info("json_invited_person=%r" % json_invited_person)

                                            return self.I.PARTY.partyInvite( self.party_id, self.auid, self.invite_auid,
                                                json_master_person=json_master_person, json_invited_person=json_invited_person, as_enemy=self.as_enemy,
                                                game_type = self.game_type, with_bots = self.with_bots, callback=self.onPartyInvite, flagType=self.flagType,
                                                flagPersistentId=self.flagPersistentId, isMMAllowed = self.isMMAllowed, isInventoryFull=self.isInventoryFull,
                                                isLeaver=self.isLeaver, tournamentDynQuestId=self.tournamentDynQuestId, dependedTournamentQuests=self.dependedTournamentQuests,banEndTime=self.banEndTime )

                                    else:
                                        self.response["error"] = "invited user %s in game/matchmaking, mm_progress %s" \
                                            % (self.invite_auid, self.invite_acc.mm_progress)
                                        self.replyInviteError( "invite", PARTY_ERROR.USER_IN_GAME )
                                else:
                                    self.response["error"] = "invited user %d already has a party (%d)" % (self.invite_auid, self.invite_acc.party_id)
                                    self.replyInviteError( "invite", PARTY_ERROR.USER_ALREADY_HAS_PARTY )
                            else:
                                self.response["error"] = "no acc for user %s" % self.invite_auid
                                self.replyInviteError( "invite", PARTY_ERROR.USER_NOT_ONLINE )
                        else:
                            self.response["error"] = "no such acc(auid=%s)" % self.auid
                            self.replyInviteError( "invite", PARTY_ERROR.USER_NOT_ONLINE )
                            #return self.fail( EC.FRIENDS_NO_ACC, "no such acc(auid=%s)" % self.invite_auid )
                        
        self.fin()
        
    def onPartyInvite(self, response):
        # перекидываем финальный ответ от PS[party_id] обратно на FS/WS
        info( "onPartyInvite: self.response=%s, PTS response=%s" % (self.response, response))
        subDictUpdateListsAppend( self.response, response )
        info( "onPartyInvite: resulting self.response=%s" % (self.response))
        if response.get("ok", 0):
            #TODO: добавляем приглашенному invite, отправляем FriendsData model change
            # 2) добавляем в персональную FriendsData приглашаемого юзера сведения о новом инвайте (== персона мастера)
            self.I.WS.addInviterPerson( self.invite_acc, self.auid, self.master_person_dict, self.party_id )
    
            # заворачиваем для приглашенного FriendsData changes
            friends_model_changes = self.I.WS.pickPendingFriendsChanges( self.invite_acc )
            from_nick = self.master_person_dict.get("nickName", "")
            post_body = json_dumps( dict(json_FriendsData=friends_model_changes, from_nick=from_nick) )

            #достаем uid с WSки потому что в self.invite_acc его почему то нет (будем разбираться отдельной задачей)
            #if self.invite_acc.uid is None:
            #    ws_acc = self.I.WS.ws_accs.get(self.invite_auid)
            #    self.invite_acc.uid=ws_acc.uid
            ws_acc = self.I.WS.ws_accs.get( self.invite_auid )
            #info("--- onPartyInvite: auid=%r, ws_acc=%r" % (self.invite_auid, ws_acc))

            # на какой там WS-ке наш приглашенный?
            peer_addr = self.I.WS.getUserWsAddr( self.invite_auid )
            info("onPartyInvite (auid=%s): peer_addr=%s" % (self.invite_auid, peer_addr))
            if peer_addr:
                self.I.WSX.post( 
                    peer_addr, 
                    dict(
                        action='server_party',
                        cmd='invite',
                        #to_uids=str(self.invite_acc.uid),
                        to_uids=str(ws_acc.uid),
                        party_id=self.party_id,
                        msg_id=self.nextMsgID(),
                        master_auid=self.auid,
                        as_enemy=self.as_enemy,
                    ), 
                    post_body,
                    self.I.WS.onDummyResponseCallback 
                )
            
        self.fin()
        
   
##---------------------------------------------------------------------------------------------------

class PartyAcceptAction( PersonServerSubAction ):
    action = 'fs_party_accept'
    """ """
    def onStart(self):
        if self.checkValidIntParam("auid"):
            self.setUserUid()
            if self.checkValidIntParam("master_auid"):
                self.banEndTime = self.getIntParam("banEndTime")
                self.flagType = self.getIntParam("flagType")
                self.flagPersistentId = self.getParam("flagPersistentId")
                self.isMMAllowed = self.getParam("isMMAllowed")
                self.isInventoryFull = self.getParam("isInventoryFull")
                self.isLeaver = self.getParam("isLeaver")
                self.tournamentDynQuestId= self.getParam("tournamentDynQuestId",-1)
                self.dependedTournamentQuests = self.getParam("dependedTournamentQuests", "-1")
                info( "PartyAcceptAction: auid=%s, master_auid=%s, banEndTime=%s, flagType=%s, flagPersistentId=%s, isInventoryFull=%s isLeaver=%s tournamentDynQuestId=%s dependedTournamentQuests=%s",
                      self.auid, self.master_auid, self.banEndTime, self.flagType, self.flagPersistentId, self.isInventoryFull, self.isLeaver,
                      self.tournamentDynQuestId, self.dependedTournamentQuests)
                self.acc = self.I.WS.getUserAcc( self.auid )
                if self.acc:
                    master_person = self.acc.FriendsData.findPersonByUid( self.master_auid )
                    self.party_id = getattr(master_person, "party_id", 0)
                    if self.party_id:
                        if self.acc.online:
                            if not self.acc.party_id:
                                if not self.acc.mm_progress:
                                    #--------------------------------------------------------------------------------------------------------
                                    # ок, местные проверки прошли; прибиваем искомый инвайт в нашем FriendsData и пересылаем на PTS[party_id]
                                    person = self.acc.FriendsData.invites.deleteByID( self.master_auid )
                                    friends_model_changes = self.I.WS.pickPendingFriendsChanges( self.acc )
                                    
                                    self.replyPartyCmd("accept_invite", "removing invite", json_FriendsData=friends_model_changes) 
                                                                        
                                    self.I.PARTY.updatePersonStatus( self.acc.auid, self.party_id, FriendStatus.INCASTLE )
                                    return self.I.PARTY.partyAccept( self.party_id, self.auid, self.banEndTime, self.flagType,
                                                                     self.flagPersistentId, self.isMMAllowed, self.isInventoryFull, self.isLeaver,
                                                                     self.tournamentDynQuestId, self.dependedTournamentQuests, callback=self.onPartyAccept )
                                    #--------------------------------------------------------------------------------------------------------
                                else:
                                    self.response["error"] = "accepting user %s in game/matchmaking, mm_progress %s" % (self.auid, self.acc.mm_progress)
                                    self.replyPartyError( "accept", PARTY_ERROR.USER_IN_GAME, self.auid )
                            else:
                                self.response["error"] = "accepting user %d already has a party (%d)" % (self.auid, self.acc.party_id)
                                self.replyPartyError( "accept", PARTY_ERROR.USER_ALREADY_HAS_PARTY, self.auid )
                        else:
                            self.response["error"] = "no acc for user %s" % self.auid
                            self.replyPartyError( "accept", PARTY_ERROR.USER_NOT_ONLINE, self.auid )
                    else:
                        self.response["error"] = "(auid=%s) unknown party_id for master_auid %s" % (self.auid, self.master_auid)
                        self.replyPartyError( "accept", PARTY_ERROR.BAD_MASTER_AUID, self.auid )
                else:
                    return self.fail( EC.FRIENDS_NO_ACC, "no such acc(auid=%s)" % self.auid )
                    
        self.fin()
    
    def onPartyAccept(self, response):
        # перекидываем финальный ответ от PTS[party_id] обратно на WS
        ## info( "onPartyAccept: self.response=%s, PTS response=%s" % (self.response, response))
        subDictUpdateListsAppend( self.response, response )
        ## info( "onPartyAccept: resulting self.response=%s" % (self.response))
        if self.response.get("ok"):
            self.acc.party_id = self.party_id
        self.fin()

##---------------------------------------------------------------------------------------------------
    
class PartyDeclineAction( PersonServerSubAction ):
    action = 'fs_party_decline'
    """ """
    def onStart(self):
        if self.checkValidIntParam("auid"):
            self.setUserUid()
            if self.checkValidIntParam("master_auid"):
                info( "PartyDeclineAction: auid=%s, master_auid=%s" % (self.auid, self.master_auid))
                self.acc = self.I.WS.getUserAcc( self.auid )
                if self.acc:
                    master_person = self.acc.FriendsData.findPersonByUid( self.master_auid )
                    self.party_id = getattr(master_person, "party_id", 0)
                    if self.party_id:
                        if self.acc.online:
                            #--------------------------------------------------------------------------------------------------------
                            # ок, местные проверки прошли; прибиваем искомый инвайт в нашем FriendsData и пересылаем на PTS[party_id]
                            person = self.acc.FriendsData.invites.deleteByID( self.master_auid )
                            friends_model_changes = self.I.WS.pickPendingFriendsChanges( self.acc )
                            
                            self.replyPartyCmd("decline_invite", "removing invite", json_FriendsData=friends_model_changes) 
                                                                
                            return self.I.PARTY.partyDecline( self.party_id, self.auid, callback=self.onPartyDecline ) 
                            #--------------------------------------------------------------------------------------------------------
                        else:
                            self.response["error"] = "no acc for user %s" % self.auid
                            self.replyPartyError( "decline", PARTY_ERROR.USER_NOT_ONLINE, self.auid )
                    else:
                        self.response["error"] = "(auid=%s) unknown party_id for master_auid %s" % (self.auid, self.master_auid)
                        self.replyPartyError( "decline", PARTY_ERROR.BAD_MASTER_AUID, self.auid )
                else:
                    self.response["error"] = "no acc for user %s" % self.auid
                    self.replyPartyError( "decline", PARTY_ERROR.USER_NOT_ONLINE, self.auid )
                    
        self.fin()
    
    def onPartyDecline(self, response):
        # перекидываем финальный ответ от PTS[party_id] обратно на WS
        subDictUpdateListsAppend( self.response, response )
        self.fin()
        

class MatchmakingProgressAction(PersonServerSubAction):
    action = 'fs_party_progress'
    """ """
    def onStart(self):
        if self.checkValidIntParam("auid"):
            self.setUserUid()
            
            self.progress = self.getIntParam( "progress", 0 )
            self.game_type = self.getParam( "game_type", "" )
            self.ec = toint(self.getParam("ec", 0))
            info( "MatchmakingProgressAction: auid=%s, progress=%s, game_type=%s, ec=%s" % (self.auid, self.progress, self.game_type, self.ec))
            
            self.acc = self.I.WS.getUserAcc( self.auid )
            if self.acc:
                # меняем текущий прогресс MM у данного юзера:
                self.acc.mm_progress = self.progress         
        
                # разберемся с Friend.status
                if self.progress:
                    # если пошли в матчмейкинг -- статус должен стать одним из вариантов InBattle
                    if self.progress == MM.STATUS_NEW:
                        friend_status = FriendStatus.INMATCHMAKING
                    else:
                        friend_status = FriendStatus.INBATTLE
                    self.mmStartTime = self.getIntParam( "mm_start_time", 0 )
                    self.heroId = self.getIntParam( "hero_id", 0 )
                    self.I.WS.setFriendStatus(self.acc, friend_status, mm_start_time=self.mmStartTime, hero_id=self.heroId, friend_update=True, party_update=False)
                else:
                    # если вышли из матчмейкинга -- статус InCastle (если юзер online; если offline -- то по-любому NotInGame)
                    self.I.WS.setFriendStatus(self.acc, FriendStatus.INCASTLE, friend_update=True, party_update=False)
                    
                if self.acc.party_id:
                    # у нас была партия
                    self.I.PARTY.updateProgress( self.acc.party_id, self.auid, self.progress, self.acc.friend_status, self.ec )

                if self.acc.tambur_id:
                    # был гвардейский тамбур
                    self.I.PARTY.sendTamburCmd( self.auid, "tambur_delete", game_id=self.acc.game_id, allies_key=self.acc.allies_key )

            else:
                return self.fail( EC.FRIENDS_NO_ACC, "no such acc(auid=%s)" % self.auid )
                    
        self.fin()

class AddRecentAlliesAction(PersonServerSubAction):
    """ обновляем список тех, с кем недавно играли """
    action = "add_recent_allies"

    # -----------------------------------------
    @action_timing
    def onStart(self):
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                allies_auids_str = self.getParam("allies_auids", "")
                if allies_auids_str != "":
                    self.new_allies = []
                    new_allies_str = allies_auids_str.strip("][")
                    allies_auids = new_allies_str.split(",")
                    for auid in allies_auids:
                        # Если это наш друг, пропускаем
                        if acc.FriendsData.hasFriend(int(auid)):
                            continue
                        self.new_allies.append(int(auid))
                    new_allies_str = ','.join(str(auid) for auid in self.new_allies)

                    if new_allies_str:
                        self.I.AGG.getInfos(new_allies_str, None, self.onAggGetInfo)
                    return
            else:
                warn("UpdateRecentAlliesAction: no such acc(auid=%s)" % self.auid)

        self.fin()

    def onAggGetInfo(self, response):
        debug("onAggGetInfo: %r", response)
        if response:
            ec = toint(response.get("error"))
            pers_infos = response.get("get_infos", {})
            if (ec == 0) and pers_infos:
                acc = self.I.WS.getUserAcc(self.auid)
                if acc:
                    acc.FriendsData.write(acc.pending)
                    for pers_auid in pers_infos:
                        int_pers_auid = toint(pers_auid)
                        # Если мы недавно играли с этим человеком, удалим его и добавим заново, чтобы поправить позицию в списке
                        acc.FriendsData.removeRecentAlly(int_pers_auid) #FIXME почему нельзя в этом случае просто переместить его на другой индекс? D.L.
                        props = pers_infos[pers_auid].get("props", {})
                        fsn = props.get("fsn", "")
                        fsn_info = pers_infos[pers_auid].get(fsn, {})
                        if props and fsn_info:
                            self.I.WS.setPersonAUID(int_pers_auid)  # пусть FriendsData выдаст friend_id == self.friend_auid
                            friend, friend_id = acc.FriendsData.newFriend()
                            assert(friend_id == int_pers_auid)
                            friend.person_uid = int_pers_auid
                            self.I.WS.fillFriendsData(friend, pers_infos[pers_auid], props, fsn_info)
                            ws_acc = self.I.WS.ws_accs.get(friend.person_uid)
                            if ws_acc and ws_acc.server:
                                friend.online = True
                                _callback = functools.partial(self.I.WS.onFriendInfoFound,
                                                              auid=self.auid, friend_auid=friend.person_uid)
                                self.I.FRIENDS.updateRecentAllyInfo(friend.person_uid, _callback)
                            else:
                                friend.online = False
                            timestamp = int(time.time())
                            if timestamp in acc.FriendsData.RecentAllies:
                                while timestamp in acc.FriendsData.RecentAllies:
                                    timestamp += 1
                            acc.FriendsData.RecentAllies.add(timestamp, int_pers_auid)

                        else:
                            warn("UpdateRecentAlliesAction.onAggGetInfo: ec(%r) bad pers_info(%s) or props(%s) for friend_auid=%s (auid=%s)",
                                ec, pers_infos[pers_auid], props, pers_auid, self.auid)

                    sortedTimes = sorted(acc.FriendsData.RecentAllies.keys())
                    while len(acc.FriendsData.RecentAllies) > self.I.Config.getMainConfig().RECENT_ALLIES_IN_LIST:
                        acc.FriendsData.RecentAllies.remove(sortedTimes[0])
                        sortedTimes.pop(0)

                    self.I.WS.saveRecentAllies(self.auid, acc.FriendsData.RecentAllies)

                    friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                    info( "onAggGetInfo (auid=%s): friends_model_changes=%s", acc.auid, friends_model_changes)
                    if friends_model_changes:
                        self.I.WS.sendFriendsBroadcast( acc, [acc.auid], "change", friend_auid=self.auid,
                                                        json_FriendsData=friends_model_changes )
                else:
                    warn("UpdateRecentAlliesAction.onAggGetInfo: bad acc for auid=%s", self.auid)
            else:
                warn("UpdateRecentAlliesAction.onAggGetInfo: bad ec(%s) or pers_info(%s) for auids=%s (auid=%s)",
                     ec, pers_infos, self.new_allies, self.auid)
        else:
            warn("UpdateRecentAlliesAction.onAggGetInfo: bad res for auids=%s (auid=%s)", self.new_allies, self.auid)
        self.fin()

class RemoveRecentAllyAction(PersonServerSubAction):
    """ удаляем человека из списка тех, с кем недавно играли """
    action = "remove_recent_ally"

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("RemoveRecentAllyAction.onStart: %s", self.arguments)
        if self.checkValidIntParam("auid") and self.checkValidIntParam("ally_auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                # Удаляем у себя друга

                if acc.FriendsData.hasRecentAlly(self.ally_auid):
                    acc.FriendsData.write(acc.pending)
                    friend = acc.FriendsData.findPersonByUid(self.ally_auid)
                    if friend:
                        acc.FriendsData.RecentAllies.remove(friend)
                        self.I.WS.saveRecentAllies(self.auid, acc.FriendsData.RecentAllies)
                        friends_model_changes = self.I.WS.pickPendingFriendsChanges(acc)
                        if friends_model_changes:
                            self.I.WS.sendFriendsBroadcast(acc, [acc.auid], "change", friend_auid=self.ally_auid,
                                                           json_FriendsData=friends_model_changes)
                        self.response["ok"] = 1
                else:
                    warn("RemoveRecentAllyAction: no such recent_ally (ally_auid=%s)", self.ally_auid)
                    self.response["ok"] = 0

            else:
                warn("RemoveRecentAllyAction: no such acc (auid=%s)", self.auid)
                self.response["ok"] = 0

        self.fin()

class UpdateRecentAllyInfoAction(PersonServerSubAction):
    """ Получаем онлайновые параметры друга """
    action = "update_recent_ally_info"

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("UpdateRecentAllyInfoAction.onStart")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                self.response["status"] = acc.friend_status
                self.response["ok"] = 1
            else:
                warn("RemoveRecentAllyAction: no such acc (auid=%s)" % self.auid)

        self.fin()

class UpdateRecentAlliesAction(PersonServerSubAction):
    """ Обновляем информацию обо всех бывших союзниках """
    action = "update_recent_allies"

    # -----------------------------------------
    @action_timing
    def onStart(self):
        info("UpdateRecentAllyInfoAction.onStart")
        if self.checkValidIntParam("auid"):
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                new_allies_str = ','.join(str(fr.person_uid) for _id, fr in acc.FriendsData.RecentAllies.iteritems())
                if new_allies_str:
                    self.I.AGG.getInfos(new_allies_str, None, self.onAggGetRecentAlliesInfo)
                    return
            else:
                warn("RemoveRecentAllyAction: no such acc (auid=%s)" % self.auid)

        self.fin()

    def onAggGetRecentAlliesInfo(self, response):
        debug("onAggGetRecentAlliesInfo: %r", response)
        if response:
            ec = toint(response.get("error"))
            pers_infos = response.get("get_infos", {})
            if (ec == 0) and pers_infos:
                acc = self.I.WS.users.get(self.auid)
                if acc:
                    acc.FriendsData.write(acc.pending)
                    for pers_auid in pers_infos:
                        self.I.WS.updateRecentAllyInfoFromAgg(acc, pers_infos[pers_auid], int(pers_auid))
                    friends_model_changes = self.I.WS.pickPendingFriendsChanges(acc, to_json=0)
                    if friends_model_changes:
                        SubAction.convertResponseObjects(friends_model_changes)
                        info("fillRecentAlliesInfoFromAgg (auid=%s): friends_model_changes=%s", acc.auid, friends_model_changes)
                        self.response["FriendsData"] = friends_model_changes
                        self.response["ok"] = 1
                else:
                    warn("onAggGetRecentAlliesInfo: no such acc (auid=%s)", self.auid)
            else:
                warn("onAggGetRecentAlliesInfo: bad ec(%s) or pers_info(%s) for auid=%s", ec, pers_infos, self.auid)
        else:
            warn("onAggGetRecentAlliesInfo: bad res for auid=%s", self.auid)
        self.fin()


## ---------------------------------------------------------------------------------------------

class PartyChooseAgainAction( PersonServerSubAction ):
    action = 'fs_party_choose_again'
    intParams = ("auid", "party_id", "session_id")

    """ Вытаскиваем данные игрока, чтобы заполнить вновь собираемую PartyData """
    def onStart(self):
        info("PartyChooseAgainAction.onStart %r", self.arguments)
        if self.checkIntParams():
            self.setUserUid()
            if self.checkValidParam("game_type"):
                self.is_temp_party_id = self.getIntParam("is_temp_party_id")
                self.agreed = self.getIntParam("agreed")
                self.acc = self.I.WS.getUserAcc(self.auid)
                if self.acc:
                    if not self.acc.party_id and self.agreed:
                        self.acc.party_id = self.party_id

                    with_bots = self.getIntParam("with_bots", 0) # 0/1, приглашаем на бой с ботами
                    flagType = self.getIntParam("flagType")
                    flagPersistentId = self.getParam("flagPersistentId")
                    isMMAllowed = self.getBoolParam("isMMAllowed")
                    isInventoryFull = self.getBoolParam("isInventoryFull")
                    is_leader = self.getIntParam("is_leader")
                    allies_keys = self.getParam("allies_keys")
                    lock_end_time = self.getIntParam("lock_end_time")
                    old_party_id = self.getIntParam("old_party_id")
                    leaver = self.getBoolParam("isLeaver")
                    tournamentDynQuestId = self.getIntParam("tournamentDynQuestId",-1)
                    dependedTournamentQuests = self.getParam("dependedTournamentQuests", "-1")
                    old_party = self.getParam("old_party")
                    # ок, местные проверки прошли; добавляем person info и пересылаем на PARTY
                    master_person = self.acc.FriendsData.findPersonByUid(self.auid)
                    if master_person:
                        person_dict = json_dumps(master_person.generateJsonDict().get("Friend", {}))
                        if not self.acc.mm_progress or \
                            (self.acc.mm_progress and self.acc.mm_progress > MM.PROGRESS_ACCEPTED):
                            return self.I.PARTY.choosePartyAgain(self.party_id, self.auid, self.session_id, allies_keys,
                                self.agreed, self.onPartyCreate, person_dict=person_dict, game_type=self.game_type,
                                with_bots=with_bots, flagType=flagType, flagPersistentId=flagPersistentId,
                                isMMAllowed=isMMAllowed, is_leader=is_leader, isInventoryFull=isInventoryFull,
                                lock_end_time=lock_end_time, old_party_id=old_party_id,  old_party=old_party,
                                isLeaver=leaver, tournamentDynQuestId=tournamentDynQuestId, dependedTournamentQuests=dependedTournamentQuests)
                        else:
                            err("user %s in matchmaking, mm_progress %s", self.auid, self.acc.mm_progress)
                            return self.I.PARTY.choosePartyAgain(self.party_id, self.auid, self.session_id, allies_keys,
                                0, self.onPartyCreate, person_dict=person_dict, game_type=self.game_type,
                                with_bots=with_bots, flagType=flagType, flagPersistentId=flagPersistentId,
                                isMMAllowed=isMMAllowed, is_leader=is_leader, isInventoryFull=isInventoryFull,
                                lock_end_time=lock_end_time, old_party_id=old_party_id, old_party=old_party, isLeaver=leaver,
                                tournamentDynQuestId=tournamentDynQuestId, dependedTournamentQuests=dependedTournamentQuests)
                    else:
                        err("no master person (auid=%s)", self.auid)
                else:
                    err("no such acc(auid=%s)", self.auid)
        else:
            err("PartyChooseAgainAction: Bad action params")
        self.fin()

    def onPartyCreate(self, response):
        # если запрос пофейлился, а выданный party_id был временный, нужно его зачистить
        if (not response) or (not response.get("ok", 0)):
            if self.is_temp_party_id:
                self.acc = self.I.WS.getUserAcc(self.auid)
                if self.acc and self.acc.party_id and (self.acc.party_id == self.party_id):
                    info("PartyChooseAgainAction.onPartyCreate: clearing temp party_id=%s for auid=%s",
                         self.party_id, self.auid)
                    self.acc.party_id = 0
        else:
            if self.agreed:
                self.acc.party_id = response.get("party_id", 0)

        # просто перекидываем финальный ответ от FS[invite_auid] обратно на WS
        subDictUpdateListsAppend(self.response, response)
        self.fin()

class PartySetId(PersonServerSubAction):
    action = 'fs_party_set_id'
    intParams = ("auid", "party_id")

    """ Ставим новый party_id игроку, если он изменился на party_service """
    def onStart(self):
        if self.checkIntParams():
            info("PartySetId, auid %d, party_id %d", self.auid, self.party_id)
            acc = self.I.WS.getUserAcc(self.auid)
            if acc:
                acc.party_id = self.party_id
        self.fin()

class GetFriendInfoAction(PersonServerSubAction):
    """ Вытаскиваем данные игрока, чтобы заполнить вновь собираемую PartyData """
    action = 'fs_get_friend_info'

    def onStart(self):
        info("GetFriendInfoAction")
        if self.checkValidIntParam("auid"):
            self.acc = self.I.WS.getUserAcc(self.auid)
            if self.acc:
                # ок, местные проверки прошли; добавляем person info и пересылаем на PARTY
                person = self.acc.FriendsData.findPersonByUid(self.auid)
                if person:
                    person_dict = json_dumps(person.generateJsonDict().get("Friend", {}))
                    self.response["person_dict"] = person_dict
                    self.response["ok"] = 1
                else:
                    err("no person (auid=%s)", self.auid)
            else:
                err("no such acc(auid=%s)", self.auid)
        else:
            err("GetFriendInfoAction: Bad action param auid")
        self.fin()

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class FriendServiceHandler( JsonHandler ):
    """ обрабатываем только внутренние запросы от рабочих серверов """
    
    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
        # --- служебное ----
        'check_alive': 'onCheckWebServerAlive', # base JsonHandler: умеем отвечать, что мы живы
        'get_stat':  'onGetStat',
        'reload_multi_config': 'onReloadMultiConfigWithMainSD', # base JsonHandler: умеем перегружать logic_cfg+StaticData со всеми внутренностями
        'peer': PeerServerStatusAction, # base JsonHandler: апдейтим статус peer WS-ок
        'clear_addr_info': 'onClearAddrInfoCache', # base JsonHandler: умеем чистить кэш addrinfo (чтобы заново резолвить адреса после перестройки DNS)        
        
        # --- user actions --- 
        'subscribe': SubscribePersonAction,
        'unsubscribe': UnsubscribePersonAction,
        'update_game_data': UpdateGameDataAction,
        'add_friend': AddFriendAction,
        'delete_friend': DeleteFriendAction,
        'in_castle': InCastlePersonAction,
        'afk': AFKPersonAction,
        'mute': MutePersonAction,
        'update_guildshortname': UpdateGuildShortNameAction,
        'refresh_friend' : RefreshFriendAction,
        'add_recent_allies': AddRecentAlliesAction,
        'update_recent_allies': UpdateRecentAlliesAction,
        'remove_recent_ally': RemoveRecentAllyAction,
        'update_recent_ally_info': UpdateRecentAllyInfoAction,

        # --- ifriendservice --- (mapping party->friends messages)
        'fs_update_ws_acc': UpdateWsAccAction,
        'fs_remove_party_invite': RemovePartyInviteAction,
        'fs_remove_party_id': RemovePartyIdAction,
        'fs_update_delete_friend': UpdateDeleteFriendAction,
        'fs_update_add_friend': UpdateAddFriendAction,
        'fs_update_friend_list': UpdateFriendListAction,
        'fs_get_friend_info': GetFriendInfoAction,

        'fs_party_invite': PartyInviteAction, # 1-я серия, на FS[master_auid]
        'fs_party_invite_from_master': PartyInviteFromMasterAction, # 2-я серия, на FS[invited_auid]
        'fs_party_accept': PartyAcceptAction,
        'fs_party_decline': PartyDeclineAction,
        'fs_party_progress': MatchmakingProgressAction,
        'fs_party_choose_again': PartyChooseAgainAction,
        'fs_party_set_id': PartySetId,

        'fs_tambur_add': TamburAddPersonAction, # добавим person info
        'fs_remove_tambur_id': RemoveTamburIdAction,
    }

    # ############################################################
    # DEBUG OVERRIDE -- для тестов с "подвисанием" == очень долгим отвечанием на запросы
    #~ def onCheckWebServerAlive(self):
        #~ """ всем кому угодно умеем отвечать, что живы """ 
        #~ time.sleep(15.0) # ЗЛОБНО ЗАСИРАЕМ ОЧЕРЕДЬ HTTP неответами по 15 сек ######################################
        #~ self.response['ok'] = 1
        #~ self.response['sid'] = options.server_id
        #~ self.fin()        
    # ############################################################
    def onGetStat(self):
        self.response["ok"] = 1
        self.response["usersCount"] = len(self.I.WS.users)
        self.response["afterpartiesCount"] = len(self.I.WS.afterparties)
        self.response["fail_requests"] = self.I.WS.fail_requests
        self.fin()

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class FakePartyData:
    """ общий для friend_service/party_service механизм фейкового PartyData для рассылки party errors """
    def __init__(self):
        info("FakePartyData __init__")
        self.fakeErrorPartyData = PartyData()
        self.fakeErrorPartyData.init( None )
        acc = ClassDict()
        acc.pending_changes = []
        acc.pending = GroupPendingChangeWriter( acc )
        self.fakeErrorUserAcc = acc
        
    def getErrorPartyData(self):
        return self.fakeErrorPartyData, self.fakeErrorUserAcc


##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class BasePersonService:
    _SPECIFIC_CONFIG_PARAMS = {
        "friends_svc": "FRIEND_SERVICES",
        "party_svc": "PARTY_SERVICES",
        "chat_serv": "CHAT_SERVICES",
        "stats_agent": "STATS_AGENT_URL",
        "balancer_int": "BALANCER_INTERNAL",
        "curl_wrk": "HTTP_CURL_WORKERS", 
        "req_limit": "HTTP_REQUEST_LIMIT",
        "soc_agg": "SOCIAL_AGGREGATOR_ADDRESS",
        "events": "EVENT_SERVICES",
        "tournament_server": "TOURNAMENT_SERVER",
        "mongo_cfg": "MONGO_CONFIG"
    }
        
    """ helper-методы, общие для friend_service, party_service и проч. """
    # вынимаем с указанного user acc (key="FriendsData") или party (key="PartyData") все pending_changes    
    def pick_pending_response(self, acc, uid, key, to_json=1 ):
        response = {}
        SubAction.wrapPendingMessages( acc, uid, response )
        acc.pending_changes = []
        if to_json:
            return self.I.MD.toJson( response.get(key) or [] )
        else:
            return response.get(key) or []
        
    # ПОБОЧНЫЙ ЭФФЕКТ: пропадут и все накопленные Party model changes (т.к. делаем acc_pending_changes=[])
    def pickPendingFriendsChanges(self, acc, to_json=1):
        return self.pick_pending_response( acc, acc.uid, "FriendsData", to_json )
        
    # ПОБОЧНЫЙ ЭФФЕКТ: пропадут и все накопленные Friend model changes (т.к. делаем acc_pending_changes=[])
    def pickPendingPartyChanges(self, party, to_json=1):
        return self.pick_pending_response( party, party.party_id, "PartyData", to_json )

    def WriteModelChangeString(self, comment, path, op, params):
        return self.I.MD.toJson( [ MakeModelChangeString(comment, path, op, params) ] )
        
    def nextMsgID(self):
        return long( good_timer_function() * 10000000 )
        
    def updatePersonFromDict(self, person, person_dict, forceUpdate=False):
        photoUrl = utf8convert( person_dict.get("photoUrl", "") )
        gender = person_dict.get("gender", MM.ESex.NONE)
        fame = person_dict.get("fame", 0)
        fraction = person_dict.get("fraction")
        if (fraction is None) or (fraction < 0):
            fraction = PARTY_FRACTION.NONE
        nickName = utf8convert( person_dict.get("nickName", "") )
        if nickName == CC.NICK_EMPTY:
            nickName = ""
        lastLoginTime = person_dict.get("lastLoginTime", 0)
        lastLogoutTime = person_dict.get("lastLogoutTime", 0)
        online = person_dict.get("online", False)
        Status = person_dict.get("Status", 0)
        isMuted = bool(person_dict.get("IsMuted", 0))
        guildshortname = person_dict.get("guildshortname", "")
        if guildshortname == "-":
            guildshortname = ""

        info("updatePersonFromDict: person_dict %s, online=%r" % (person_dict, online))

        if person.gender != gender or forceUpdate:
            person.gender = gender
        if person.photoUrl != photoUrl or forceUpdate:
            person.photoUrl = urlQuote(photoUrl) # пусть всегда хранится в квотированном виде, т.к. у одноклассников например это url, который может включать ? и &
        if person.nickName != nickName or forceUpdate:
            person.nickName = urlQuote(nickName) # пусть всегда хранится в квотированном виде
        if person.fame != fame or forceUpdate:
            person.fame = fame
        if person.fraction != fraction or forceUpdate:
            person.fraction = fraction
        if person.lastLoginTime != lastLoginTime or forceUpdate:
            person.lastLoginTime = lastLoginTime
        if person.lastLogoutTime != lastLogoutTime or forceUpdate:
            person.lastLogoutTime = lastLogoutTime
        if person.online != online or forceUpdate:
            person.online = online
        if person.Status != Status or forceUpdate:
            person.Status = Status
        if person.guildshortname != guildshortname or forceUpdate:
            person.guildshortname = guildshortname
        if person.IsMuted != isMuted or forceUpdate:
            person.IsMuted = isMuted



    # ---------------------------------------------------------------------------------------------
    def updateWsAcc(self, auid, uid, server, retranslate=True):
        self.ws_accs[ toint(auid) ] = ClassDict( uid=uid, server=server )
        ## info("updateWsAcc(auid=%s, uid=%s, server=%s), ws_accs now: %s" % (auid, uid, server, self.ws_accs))
        if retranslate:
            self.I.FRIENDS.updateWsAcc(auid, uid, server) # всем кроме себя
            self.I.PARTY.updateWsAcc(auid, uid, server) # всем
            
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class FriendService( BasePersonService, ICSVActionTimingWriter, ITornadoServer, FakePartyData ):
    """ Добываем из социального аггрегатора пользовательские данные (ник, фото и т.п.) и предоставляем их рабочим серверам """
    server_type_name = "fs"
    
    _aggregatorProperties = { 
        "nick": utf8convert,
        "fame": int,
        "fraction": int,
        "guildshortname": utf8convert,
    }
    
    # данные от какие соц.сетей может возвращать аггрегатор (сейчас перебираем по списку только при поиске "какой-нибудь фотки")
    _socialNetworks = [
        "fb", 
        "ok",
    ]
    
    TAMBUR_DELETE_PERIOD = 60.0 

    def __init__(self, **kwargs):
        super(FriendService, self).__init__( **kwargs )
        FakePartyData.__init__( self )
        
        self.users = {} # здесь будем хранить записи юзеров (со списками френдов) [auid] -> user info
        self.logins = {} # здесь будем хранить соответствие login ["<snid>#<snuid>"] -> auid 
        self.aggregatorProperties = {} # [auid] -> aggregatorProperties acc
        self.ws_accs = {} # [auid] -> {server, uid}
        self.afterparties = {}  # [session_id] -> [auid] для трансфера запросов choose_party_again на правильные сервера
        self.fail_requests = ClassDict()
        
    # -----------------------------------------------
    def tick(self):
        try:
            SEC = toint(time.time())
            if SEC % 60 == 0:
                self.updateInstrumentedActions()
        except:
            catch()
        self.gcTick()

    # OVERRIDE
    def onGetPeerServer(self, peer, peer_name, peer_id, status):
        if status == PEER_DELETED:
            return
        if peer["on"] and peer_id:
            # просим каждый online WS выслать нам полный список юзеров для подписки (а то мы тут только что перезапустились)
            self.peers[ toint(peer_id) ] = peer
            if status == PEER_ADDED:
                res = httpClientRequest( addr=peer["addr"], server="x", params="action=ps_resubscribe&name=%s" % options.server_name )
            
    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers( r"(.*)", [ 
            ( r"/x", FriendServiceHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
        ] )
        
        # готовы слушать; рапортуем координатору (и получаем в ответ список WS peers)
        self.getPeersFromCoordinator()
            
        
    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # проверяем, не слушает ли на нашем порту кто-то еще (защита от повторного запуска координатора)
        self_addr = "127.0.0.1:"+str(options.port)
        res = httpClientRequest( addr=self_addr, server="x", params="action=check_alive&name=_friend_server_" )
        if res and res.get("ok") != None:
            fatal( "DUPLICATE FRIEND SERVER: already listening on " + self_addr + "\n(reply was %s)" % str(res) )
            return True # обламываемся, уже запущена копия веб-сервера на этом порту
            
        print( "check startup environment: ok, port free (" + self_addr + ")" )
        
        
    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = PERSON_SERVER_ID
            options.server_name = PERSON_SERVER_NAME
            options.server_class = "friends"
        else:
            options["server_id"].set(PERSON_SERVER_ID)
            options["server_name"].set(PERSON_SERVER_NAME)
            options["server_class"].set("friends")


    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        # --- для начала надо связаться с координатором и получить от него актуальные кластерные настройки для cfg
        classOf.getCoordinatorConfig( classOf )
            
        iDict = ClassDict()

        # http-клиент, потенциально -- для запросов к facebook и zzima api
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=cfg.HTTP_CURL_WORKERS ) 
        iDict.WS = IWebServer() # чисто для генерации GUID-ов

        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager() 
        info( "MD interface: " + str(iDict.MD) )
        
        #~ # нам зачем-то нужен полновесный ModelData manager? хм..
        #~ iDict.MD = PwNewModelManager( ifaceDict=iDict ) 
        #~ info( "MD interface: " + str(iDict.MD) )

        iDict.Config = MultiConfig()
        iDict.DATA = IfaceFactory.makeIDataInterfaceSimple(options.data, cfg.MONGO_CONFIG, None)

        iDict.MSD = MultiStaticData("xdb/ExportedSocialData.xml", iDict.Config.getMainConfig(), loadLocales=False)
        iDict.SD = iDict.MSD.getMainSD()
        iDict.AGG = IfaceFactory.makeSocAggInterface( options.soc_agg, \
            cfg.SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, HTTP=iDict.HTTP )
                
        request_limit = getattr(cfg, "HTTP_REQUEST_LIMIT", 1000)
        info("using http request_limit=%s" % request_limit)
        iDict.WSX = IfaceFactory.makeIPeerWebServerInterface( options.wsx, HTTP=iDict.HTTP, request_limit=request_limit)
        iDict.CHAT = IfaceFactory.makeIChatServerInterface( options.chat, cfg.CHAT_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit)
        
        iDict.FRIENDS = ifriendservice.IHttpFriendService( addresses=cfg.FRIEND_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit )
        iDict.PARTY = ipartyservice.IHttpPartyService( addresses=cfg.PARTY_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit )
       
        return iDict

    # добавляем в users аккаунт соотв. юзера, со списком френдов
    def addUserFriends(self, auid, acc, friends):
        ## info( "addUserFriends: auid=%r, friends=%r" % (auid, friends) )
        if not (auid and acc and isinstance(friends, dict)):
            warn( "addUserFriends: bad auid=%r, acc=%r, friends=%r", auid, acc, friends)
            return

        for pers_auid_string, pers_info in friends.iteritems():
            pers_auid = tolong( pers_auid_string )
            if pers_auid and isinstance(pers_info, dict):
                new_info = ClassDict( pers_info )
                person_properties = pers_info.get("props") or {}

                friend_acc = self.users.get(pers_auid) or ClassDict() # если записи персоны нет на сервере, поля fame/fraction/nickName/online будут None

                fsn = person_properties.get("fsn") # ключ "fsn" тоже переехал в "props"
                photoUrl = ""
                snid_list = self._socialNetworks[:]
                if fsn: # "first social network", эта соц.сеть считается главной соц.сетью аккаунта; если в ней есть фотка, значит, оттуда и берем (проверяем первой)
                    snid_list.insert(0, fsn)
                # если в fsn нет фотки, то будем искать дальше, во всех данных от соц.сетей; надо найти хоть какую-нибудь фотку (FB, OK - все равно)
                for snid in snid_list:
                    photoUrl = subFind(new_info, (snid, "photo"))
                    if photoUrl:
                        #info("picked photo: snid=%s of %s" % (snid, snid_list))
                        break
                friend_acc.photoUrl = photoUrl
                friend_acc.lastlogin = pers_info.get("dt_login", 0)
                friend_acc.lastlogout = pers_info.get("dt_logout", 0)
                if friend_acc.lastlogout > friend_acc.lastlogin:
                    friend_acc.lastlogin = friend_acc.lastlogout

                for property_name,property_type in self._aggregatorProperties.iteritems():
                    property_value = person_properties.get(property_name)
                    ## info("found property: %r = %s (type %s), should be type %s" % (property_name, property_value, type(property_value), property_type) )
                    if property_value:
                        # типы приводим автоматически
                        setattr(friend_acc, property_name, property_type(property_value))

                if friend_acc.guildshortname == "-":
                    friend_acc.guildshortname = ""

                friend = acc.FriendsData.findPersonByUid( pers_auid )
                if friend:
                    ## info( "found existing friend [%r] pers.info dict=%r, REPLACE with new info=%r" % (pers_auid, friend.generateJsonDict(), new_info) )

                    # 1) внести изменения в acc.FriendData
                    # 2) аккуратно проапдейтить поля (там где старое значение совпадает с новым, не должно быть model change)
                    #if friend:
                    self.updatePersonInfo(friend, friend_acc)
                        ## info( "[auid %d] updated pers_auid=%d, FriendsData acc.pending: %s" % (auid, pers_auid, preview_pending_response(acc, acc.auid)) )

                else:
                    ## info( "new friend [%r] pers_info=%r" % (pers_auid, new_info) )

                    # внести новые данные в acc.FriendData
                    self.I.WS.setPersonAUID( pers_auid ) # пусть FriendsData выдаст person_id == pers_auid
                    friend, friend_id = acc.FriendsData.newFriend()
                    assert( friend_id == pers_auid)
                    friend.person_uid = pers_auid
                    friend.Status = FriendStatus.NOTINGAME
                    self.updatePersonInfo(friend, friend_acc)

                    acc.FriendsData.myFriends.add(friend_id)

                    ## info( "[auid %d] added pers_auid=%d, FriendsData acc.pending: %s" % (auid, pers_auid, preview_pending_response(acc, acc.auid)) )

            else:
                warn( "addUserFriends: bad friend auid=%r (info=%r)", pers_auid, pers_info )

        ## info( "users keys now: %r" % self.users.keys() )


    def resetPendingChanges(self, acc):
        acc.pending_changes = []
        acc.pending = GroupPendingChangeWriter( acc )

    def getUserInfo(self, auid):
        #info("getUserInfo: auid=%r " % (auid))
        #info("getUserInfo: self.users=[%r]" % (self.users))
        #self.aggregatorProperties = {} # [auid] -> aggregatorProperties acc
        #self.ws_accs = {} # [auid] -> {server, uid}
        #info("getUserInfo: self.ws_accs=[%r]" % (self.ws_accs))
        #info("getUserInfo: self.aggregatorProperties=[%r]" % (self.aggregatorProperties))
        if auid:
            acc = self.users.get(auid)
            #info( "getUserInfo: acc=[%r], self.users=[%r]" % (acc, self.users))
            if acc:
                #info( "getUserInfo: FriendsData=[%r]" % acc.FriendsData.getFriendByID(auid))
                return acc.FriendsData.getFriendByID(auid)

    def fillPersonData(self, auid, person):
        if auid:
            acc = self.users.get(auid)
            if acc:
                self.updatePersonInfo( person, acc )

    def updatePersonInfo(self, person, acc, forceUpdate=False):
        photoUrl = utf8convert( acc.photoUrl or "" )
        sex = acc.sex or MM.ESex.NONE
        fame = acc.fame or 0
        fraction = acc.fraction
        if (fraction is None) or (fraction < 0):
            fraction = PARTY_FRACTION.NONE
        nick = utf8convert( acc.nick or "" )
        if nick == CC.NICK_EMPTY:
            nick = ""
        lastlogin = acc.lastlogin or 0
        lastlogout = acc.lastlogout or 0
        online = acc.online or False
        status = acc.friend_status or FriendStatus.NOTINGAME
        guildshortname = acc.guildshortname or ""
        if guildshortname == "-":
            guildshortname = ""
            
        ## info( "auid=%s fame: %d/%d, fraction: %s/%s, acc.friend_status=%s, status=%s" \
            ## % (acc.auid, person.fame, fame, person.fraction, fraction, acc.friend_status, status) )
        
        if person.gender != sex or forceUpdate:
            person.gender = sex
        if person.photoUrl != photoUrl or forceUpdate:
            ##person.photoUrl = photoUrl ##
            person.photoUrl = urlQuote(photoUrl) # пусть всегда хранится в квотированном виде, т.к. у одноклассников например это url, который может включать ? и &
        if person.nickName != nick or forceUpdate:
            person.nickName = urlQuote(nick) # пусть всегда хранится в квотированном виде
        if person.fame != fame or forceUpdate:
            person.fame = fame
        if person.fraction != fraction or forceUpdate:
            person.fraction = fraction
        if person.lastLoginTime != lastlogin or forceUpdate:
            person.lastLoginTime = lastlogin
        if person.lastLogoutTime != lastlogout or forceUpdate:
            person.lastLogoutTime = lastlogout
        if person.online != online or forceUpdate:
            person.online = online
        if person.Status != status or forceUpdate:
            person.Status = status
        if person.guildshortname != guildshortname or forceUpdate:
            person.guildshortname = guildshortname

    
    # FriendsData придется сбрасывать при каждом логине
    def newFriendsData(self, acc):
        # ---- FriendData --------------------
        self.resetPendingChanges( acc )
        acc.FriendsData = FriendsData()
        acc.FriendsData.init( None ) # создание новой fake-записи в keeper-е не должно уходить на клиент (он не переживет добавления дубликатов в keeper)
        acc.FriendsData.nextGUID = self.I.WS.getPersonAUID # грязно хакаем механизм выдачи следующих GUID-ов, гарантируем что Friend-ам всегда выдается id == auid

        # заводим fake-запись "собственного юзера" у себя во FriendsData
        self.I.WS.setPersonAUID( acc.auid ) # пусть FriendsData выдаст person_id == pers_auid
        friend, friend_id = acc.FriendsData.newFriend()
        assert( friend_id == acc.auid )
        acc.FriendsData.myFriends.add( friend )
        
        # только с момента апдейта полей включаем механизм накопления model changes
        acc.FriendsData.write( acc.pending )
        friend.person_uid = acc.auid # чтобы апдейты полей не приходили без апдейта person_uid (иначе клиент не отличит самого себя от друга/раба)
        self.updatePersonInfo(friend, acc)

    def fillFriendsData(self, friend, pers_info, props, fsn_info, update_status=True):
        friend.guildshortname = props.get("guildshortname", "")
        if friend.guildshortname == "-":
            friend.guildshortname = ""
        friend.nickName = utf8convert(props.get("nick", ""))
        friend.gender = toint(fsn_info.get("gender"))
        friend.fraction = toint(props.get("fraction"))
        photoUrl = pathFind(pers_info, "fb/photo") or pathFind(pers_info, "ok/photo") or ""
        friend.photoUrl = utf8convert(photoUrl)
        friend.fame = toint(props.get("fame"))
        if update_status:
            friend.Status = FriendStatus.NOTINGAME
        friend.InMatchmaking = False
        friend.mmStartTime = 0
        friend.lastLoginTime = toint(pers_info.get("dt_login", 0))
        friend.lastLogoutTime = toint(pers_info.get("dt_logout", 0))

    def onFriendInfoFound(self, response, auid=0, friend_auid=0):
        if response and response.get("ok") and response.get("status"):
            acc = self.users.get(auid)
            if acc:
                friend = acc.FriendsData.findPersonByUid(friend_auid)
                if friend:
                    acc.FriendsData.write(acc.pending)
                    friend.Status = response.get("status")
                    IsMuted = response.get("IsMuted")
                    friend.IsMuted = bool(IsMuted if IsMuted else 0)
                    friends_model_changes = self.I.WS.pickPendingFriendsChanges(acc)
                    info("onFriendInfoFound (auid=%s): friends_model_changes=%s", acc.auid, friends_model_changes)
                    if friends_model_changes:
                        self.I.WS.sendFriendsBroadcast(acc, [acc.auid], "change", friend_auid=auid, json_FriendsData=friends_model_changes)
            else:
                warn("FriendService.onFriendInfoFound: no acc for auid %d", friend_auid)
        else:
            warn("FriendService.onFriendInfoFound: no info for auid %d", friend_auid)
    
    def setFriendStatus(self, acc, friend_status=FriendStatus.NONE,  mm_start_time=0, hero_id=0, friend_update=False, party_update=False):
        info( "setFriendStatus: auid %s, friend_status=%s" % (acc.auid, friend_status) )
        
        if not acc.online:
            friend_status = FriendStatus.NOTINGAME
            info( "setFriendStatus: auid %s offline, changed friend_status to %s" % (acc.auid, friend_status) )
        elif (friend_status == FriendStatus.INCASTLE) and (not acc.in_castle):
            friend_status = FriendStatus.LOADING
            info( "setFriendStatus: auid %s not in_castle, changed friend_status to %s" % (acc.auid, friend_status) )
            
        friend = acc.FriendsData.getFriendByID( acc.auid )
        if friend and friend.Status != friend_status:
            info( "setFriendStatus: auid %s, set Status=%s (mm_start_time:%d, hero_id:%d, friend_update:%s, party_update:%s)" % (acc.auid, friend_status, mm_start_time, hero_id, friend_update, party_update) )
            friend.Status = friend_status
            acc.friend_status = friend_status

            friend.mmInfo.mmStartTime = mm_start_time
            friend.mmInfo.heroId = hero_id

            # когда уходим выставляем logout время правильное PF-61171
            if friend_status == FriendStatus.NOTINGAME:
                dt_logout = int(time.time())
                friend.lastLogoutTime = dt_logout
                acc.lastlogout = dt_logout

            if friend_update:
                # апдейтим всем друзьям результат изменения:
                friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                self.I.WS.sendFriendsBroadcast( acc, acc.FriendsData.myFriends.keys(), "status_change", friend_auid=acc.auid, json_FriendsData=friends_model_changes )
            
            if party_update:
                if acc.party_id:
                    self.I.PARTY.updatePersonStatus( acc.auid, acc.party_id, friend_status )

    def setFriendMutedStatus(self, acc, isMuted, friend_update=False, party_update=False):
        info( "setFriendMuteStatus: auid %s, isMute=%s" % (acc.auid, isMuted) )

        friend = acc.FriendsData.getFriendByID( acc.auid )
        if friend:
            info( "setFriendMuteStatus: auid %s, set isMute=%r (friend_update:%s, party_update:%s)", acc.auid, isMuted, friend_update, party_update )
            friend.IsMuted = bool(isMuted)
            if friend_update:
                # апдейтим всем друзьям результат изменения:
                friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                self.I.WS.sendFriendsBroadcast( acc, acc.FriendsData.myFriends.keys(), "change", friend_auid=acc.auid, json_FriendsData=friends_model_changes )

            if party_update:
                if acc.party_id:
                    self.I.PARTY.updatePersonMutedStatus( acc.auid, acc.party_id, isMuted )

    
    def setAccProperty(self, acc, aggAcc, name, value):
        # при первом заходе юзера на person_server будем в любом случае апдейтить опции аггрегатору (благо делается это только по subscribe == логин)
        if getattr(acc, name, None) != value: 
            setattr(acc, name, value)
        if getattr(aggAcc, name, None) != value: 
            setattr(aggAcc, name, value)
            if isinstance(value, basestring):
                value = urlQuote(value)
            debug("AGG.setProperty( %s, %s, %s )", acc.auid, name, value)
            self.I.AGG.setProperty(acc.auid, name, value, callback=self.onDummyAggCallback)


    def updateAggregatorProperties(self, acc, nick, fraction, fame, locale):
        if acc.auid:
            info( "subscribe nick: %r (type %s)" % (nick, type(nick)) )
            aggAcc = self.aggregatorProperties.get( acc.auid )
            if not aggAcc:
                aggAcc = ClassDict( nick="", fraction=2, fame=0 )
                self.aggregatorProperties[ acc.auid ] = aggAcc
            if nick:
                self.setAccProperty(acc, aggAcc, "nick", nick)

            debug("setAggProperty fame: old %s, new %s", getattr(aggAcc, "fame", "None"), fame)
            self.setAccProperty(acc, aggAcc, "fame", fame)

            debug("setAggProperty fraction: old %s, new %s", getattr(aggAcc, "fraction", "None"), fraction)
            if fraction != PARTY_FRACTION.NONE:
                self.setAccProperty(acc, aggAcc, "fraction", fraction)
            self.setAccProperty(acc, aggAcc, "locale", locale)
            
    
    # заводим аккаунт юзера и помечаем как активный 
    def subscribeUserAccount(self, auid, snid=None, snuid=None, uid=None, nick="", photo=None,
                             fame=0, fraction=-1, sex=MM.ESex.NONE, server=None, locale=""):
        if auid:
            acc = self.users.get( auid ) 
            if (not acc): 
                if (snid and snuid and uid and server):
                    login = "%s#%s" % (snid, snuid)
                        
                    acc = ClassDict( auid=auid, snid=snid, snuid=snuid, uid=uid, login=login, server=server, nick=nick,
                        photo=photo, fame=fame, fraction=fraction, sex=sex, friends={}, online=True,
                        friend_status=FriendStatus.NONE, locale=locale, guildshortname="", friendsLoaded=False)

                    acc.photoUrl = photo
                    acc.lastlogin = toint( time.time() )

                    self.newFriendsData(acc)
                    self.I.WS.setFriendStatus( acc, FriendStatus.INCASTLE )

                    debug("subscribeUserAccount (new acc): fraction=%s", fraction)
                    if fraction != -1:
                        self.updateAggregatorProperties(acc, nick, fraction, fame, locale)
                        
                    # оповещаем peer friend services, что юзер теперь живет на такой вот WS-ке
                    self.updateWsAcc( auid, uid, server )
                    
                else:
                    warn( "subscribeUserAccount: bad params (auid=%r, uid=%r, snid=%r, snuid=%r, server=%r)", auid, uid, snid, snuid, server )
                    return
            else:
                acc.online = True
                acc.sex = sex
                if id: # время логина проставляем только при стартовом subscribe
                    acc.lastlogin = toint( time.time() )
                    acc.uid = uid
                
                if server:
                    if acc.server != server:
                        # оповещаем peer friend services, что юзер теперь живет на такой вот WS-ке
                        self.updateWsAcc( auid, uid, server )

                    acc.server = server
                    
                    # если у нас новый сервер, значит и клиент новый; придется ресетнуть FriendsData, чтобы доставить клиенту model changes
                    self.newFriendsData(acc)

                debug("subscribeUserAccount: fraction=%s", fraction)
                if fraction != -1:
                    # подпираем неприятный случай, когда WS присылает subscribe(fraction=NONE) после логина, т.к. еще не разобрало ModelData и не знает реальную фракцию игрока
                    new_fraction = fraction
                    debug("subscribeUserAccount: fraction=%s vs acc.fraction=%s", fraction, acc.fraction)
                    if acc.fraction and acc.fraction != PARTY_FRACTION.NONE and fraction == PARTY_FRACTION.NONE:
                        new_fraction = acc.fraction
                    
                    # обновим игровую инфу
                    self.updateAggregatorProperties(acc, nick, new_fraction, fame, locale)
                    
                    # self FriendData --------------------
                    friend = acc.FriendsData.getFriendByID( auid )
                    # если аккаунт у нас активен и юзер в бою, то по resubscribe не перещелкиваем статус на "в замке", скорее всего реконнектимся в pvx
                    if friend.Status not in [FriendStatus.INBATTLE, FriendStatus.INTRAINING, FriendStatus.ONDRAGONRIDE]: 
                        self.I.WS.setFriendStatus( acc, FriendStatus.INCASTLE )
                    self.updatePersonInfo(friend, acc)
                    
            info( "[auid %d] acc.pending: %s", auid, preview_pending_response(acc, auid) )
            
            self.logins[ acc.login.lower() ] = auid
            self.users[ auid ] = acc
            return acc
        else:
            warn( "subscribeUserAccount: bad auid=%r", auid )
        
    # ---------------------------------------------------------------------------------------------
    # помечаем аккаунт юзера как неактивный (возможно, подчищаем какую-то ненужную в оффлайне инфу)
    def unsubscribeUserAccount(self, auid):
        if auid:
            acc = self.users.get( auid )
            if acc:
                acc.online = False
                acc.in_castle = False
                self.logins.pop( acc.login.lower(), None ) # из логинов давайте сразу выкинем
                
                friend = acc.FriendsData.getFriendByID( auid )
                if friend:
                    friend.online = False
                    self.I.WS.setFriendStatus( acc, FriendStatus.NOTINGAME, friend_update=True, party_update=False ) # партия все равно развалится
                
                if acc.party_id:
                    self.I.PARTY.unsubscribe( acc.auid, acc.party_id )

                # оповещаем peer friend services, что юзер теперь не живет ни на какой WS-ке
                acc.server = 0
                self.updateWsAcc( auid, acc.uid, 0 )

                # убиваем с концами
                self.users.pop( auid )
                
            info( "unsubscribeUserAccount: auid=%r, acc is not None: %s" , auid, acc is not None )
        else:
            warn( "unsubscribeUserAccount: bad auid=%r", auid )
            
        
    # ---------------------------------------------------------------------------------------------
    def addInviterPerson(self, invite_acc, master_auid, master_person_dict, party_id):
        fd = invite_acc.FriendsData
        person = fd.findPersonByUid( master_auid )
        if not person:
            self.I.WS.setPersonAUID( master_auid ) # пусть FriendsData выдаст person_id == master_auid
            person, person_id = fd.newFriend()
            assert( person_id == master_auid )
            person.person_uid = master_auid
            
            self.I.WS.updatePersonFromDict( person, master_person_dict )
            
        person.party_id = party_id # запоминаем party_id, т.к. клиент будет знать только master_auid, и accept/decline будет выполнять именно по auid
                
        if person.id not in fd.invites:
            fd.invites.add( person.id )
                
        info( "[auid %d] ---------- INVITED acc.pending: %s", invite_acc.auid, preview_pending_response(invite_acc, invite_acc.auid) )
            
    # ---------------------------------------------------------------------------------------------
    def onUpdatePeerFriends(self, response, auid=0):
        # peer FS присылает нам список персон (из числа наших друзей), которые нашлись онлайн на этом peer FS
        info("onUpdatePeerFriends(auid=%s): %s", auid, response)
        if response.get("ok"):
            persons = response.get("persons")
            if isinstance(persons, dict):
                acc = self.users.get(auid)
                if acc:
                    fd = acc.FriendsData
                    for friend_auid, person_dict in persons.iteritems():
                        person = fd.findPersonByUid( friend_auid )
                        if person:
                            self.I.WS.updatePersonFromDict( person, person_dict )
                        else:
                            warn("onUpdatePeerFriends: person with friend_auid=%s not found for auid=%s",friend_auid, auid)
                    
                    # и отошлем все полученные person changes юзеру на его WS
                    friends_model_changes = self.I.WS.pickPendingFriendsChanges( acc )
                    self.I.WS.sendFriendsBroadcast( acc, [auid], "peer_friends_init", json_FriendsData=friends_model_changes )
                    
                else:
                    warn("onUpdatePeerFriends: no acc for auid=%s" % (auid))
        
    # ---------------------------------------------------------------------------------------------
    def sendFriendsDataMessage(self, acc, cmd, **kwargs):
        # отправляем одному себе, изменения своей собственной FriendsData
        self.sendFriendsBroadcast(acc, [acc.auid], cmd, **kwargs)
        
    # ---------------------------------------------------------------------------------------------
    def sendFriendsBroadcast(self, my_acc, friend_auids, cmd, **kwargs):
        # отсортируем список членов группы по peer-серверам, на которых они находятся (каждому peer-серверу можно отослать одно http-сообщение, со списком to_uids)
        #  заодно достаем родные кластерные uid вместо вражеских auid
        info( "sendFriendsBroadcast: friend_auids=%s, cmd=%s, kwargs=%s", friend_auids, cmd, kwargs )
        
        server_uid_groups = {}
        for auid_string in friend_auids:
            auid = toint(auid_string)
            ws_acc = self.ws_accs.get( auid )
            ## info("- sendFriendsBroadcast: auid=%r, ws_acc=%r" % (auid, ws_acc))
            if ws_acc and ws_acc.server:
                group = server_uid_groups.get( ws_acc.server ) or []
                group.append( ws_acc.uid )
                server_uid_groups[ ws_acc.server ] = group
            
        info("/ sendFriendsBroadcast: server_uid_groups=%r", server_uid_groups)
        if server_uid_groups:
            post_body = json_dumps( kwargs )
            for server_id, uid_list in server_uid_groups.iteritems():
                peer = self.peers.get( server_id )
                if peer:
                    Callback = functools.partial(self.checkFailCallback, peer.get("name", ""))
                    self.I.WSX.post( 
                        peer["addr"],
                        dict(
                            action='server_friends',
                            cmd=cmd,
                            to_uids=strList(uid_list),
                            msg_id=self.nextMsgID(),
                        ), 
                        post_body,
                        Callback
                    )
        else:
            info( "empty server_uid_groups for sendFriendsBroadcast: auid %d, friend_auids %s", my_acc.auid, friend_auids )

    def checkFailCallback(self, sname, data_reply):
        if not data_reply:
            self.fail_requests[sname] = self.fail_requests.get(sname, 0) + 1
            warn("checkFailCallback fail_requests stats %r", self.fail_requests)
        else:
            if not self.fail_requests.get(sname, 0):
                self.fail_requests[sname] = 0

    def saveRecentAllies(self, auid, recentAllies):
        recent_allies_list = {}
        for timestamp, fr in recentAllies.iteritems():
            recent_allies_list[str(fr.person_uid)] = timestamp
        self.I.DATA.update_data(CC.RECENT_ALLIES_DATA, CC.RECENT_ALLIES_DATA, auid, recent_allies_list,
                                self.onDummyResponseCallback, params=None)

    def fillRecentAlliesInfoFromAgg(self, acc, pers_infos, recent_allies):
        for pers_auid in pers_infos:
            friend = self.updateRecentAllyInfoFromAgg(acc, pers_infos[pers_auid], int(pers_auid))
            if friend and not acc.FriendsData.hasRecentAlly(int(pers_auid)):
                acc.FriendsData.RecentAllies.add(recent_allies[str(pers_auid)], friend)


    def updateRecentAllyInfoFromAgg(self, acc, pers_info, pers_auid):
        int_pers_auid = toint(pers_auid)
        props = pers_info.get("props", {})
        fsn = props.get("fsn", "")
        fsn_info = pers_info.get(fsn, {})
        if props and fsn_info:
            friend = acc.FriendsData.findPersonByUid(int_pers_auid)
            if not friend:
                self.I.WS.setPersonAUID(int_pers_auid)  # пусть FriendsData выдаст friend_id == self.friend_auid
                friend, friend_id = acc.FriendsData.newFriend()
                assert(friend_id == int_pers_auid)
                friend.person_uid = int_pers_auid
            self.fillFriendsData(friend, pers_info, props, fsn_info, update_status=False)
            ws_acc = self.ws_accs.get(friend.person_uid)
            if ws_acc and ws_acc.server:
                friend.online = True
                _callback = functools.partial(self.onFriendInfoFound, auid=acc.auid, friend_auid=friend.person_uid)
                self.I.FRIENDS.updateRecentAllyInfo(friend.person_uid, _callback)
            else:
                friend.online = False
                friend.Status = FriendStatus.NOTINGAME
        else:
            warn("updateRecentAllyInfoFromAgg: bad pers_info(%s) or props(%s) for friend_auid=%s (auid=%s)",
                pers_info, props, pers_auid, acc.auid)
            return None
        return friend

                
    # ---------------------------------------------------------------------------------------------
    def onDummyHttpCallback(self, http_reply):
        pass
        
    def onDummyAggCallback(self, result_dict):
        info( "onDummyAggCallback: result %s", result_dict )
        
    def onDummyResponseCallback(self, response):
        info( "PS onDummyResponseCallback: response %r", response )
    
    # ---------------------------------------------------------------------------------------------
    def setPersonAUID(self, auid):
        self._personAUID = auid
        
    def getPersonAUID(self):
        return self._personAUID
        
    def getUserAcc(self, auid):
        return self.users.get( auid )
        
    def getPartyByAcc(self, acc):
        return acc.party_id or 0
            
    # ---------------------------------------------------------------------------------------------
    # CHAT callbacks
    # ---------------------------------------------------------------------------------------------
    def onChatRegister(self, response):
        ##response = self.parseResponse(http_reply)
        if response and response.get('ok'):
            ##info( "onChatRegister response: %s" % pretty(response) )
            pass

    def onChatUnregister(self, response):
        if response and response.get('ok'):
            ##info( "onChatUnregister response: %s" % pretty(response) )
            pass

    def onChatGroupRegister(self, response):
        if response and response.get('ok'):
            ##info( "onChatGroupRegister response: %s" % pretty(response) )
            pass

    def onChatGroupUnregister(self, response):
        if response and response.get('ok'):
            ##info( "onChatGroupUnregister response: %s" % pretty(response) )
            pass

    def getUserWsAddr(self, auid):
        ws_acc = self.ws_accs.get( auid )
        if ws_acc and ws_acc.server:
            peer = self.peers.get( ws_acc.server )
            if peer:
                return peer["addr"]
            else:
                warn("no peer for server_id=%s (auid=%s)" ,ws_acc.server, auid)
        else:
            warn("no ws_acc for auid=%s" , auid)
            
## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

def main():
    ITornadoServer.main( FriendService )

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8714
    else:
        options["port"].set(8714)
    main()
