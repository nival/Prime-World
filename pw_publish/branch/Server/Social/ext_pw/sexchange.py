# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Social Exchange handlers
# (C) Dan Vorobiev 2012, Nival Network

import sys, os, time, logging, re

from subaction import * 
from intaction import InternalAction
from base.helpers import *
from tornado.options import options
#from handlers import users
from intaction import InternalMailAction
from enums import *
import EC
import CC
import MM
from base.exceptions import RecruitmentError
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation

## ------------------------------------------------------------------------------------------------------------------------------
## ------------------------------------------------------------------------------------------------------------------------------

def getMongoKeyAuid(guildAuid):
    return "gs_%d" % guildAuid

class ExchangeSendAction( SubAction ):
    """ нам присылают список сообщений игровой почты, из Social EXchange """
    action = "sex_send"
    
    @action_timing
    def onStart(self):
        """ стартовый метод для обработки action """
        info("ExchangeSendAction.onStart")
        if self.checkValidParam("project"):
            if self.checkValidIntParam("auid"):
                #
                #TODO: find user acc
                #
                try:
                    json_body = json_loads( self.request.request.body )
                    info( "ExchangeSendAction: project=%s, auid=%s, json messages=%s", self.project, self.auid, json_body)
                    if self.project == CC.SEX_PW_PROJECT:
                        self.acc = self.I.WS.getUserAccByAuid( self.auid )
                        if self.acc:
                            if self.acc.model:
                                if (not self.acc.locked) and (not self.acc.failed) and (not self.acc.db.banned):
                                    if json_body and isinstance(json_body, dict):
                                        messages = json_body.get("messages", {})
                                        if messages and isinstance(messages, dict):
                                            self.purge_msg_ids = self.I.WS.handleSocialExchangeMessages( messages, self.acc )
                                        
                                            if self.purge_msg_ids:
                                                info("ExchangeSendAction done: project=%s, auid=%s, purge msg_id list=%s" % (self.project, self.auid, self.purge_msg_ids))
                                                self.response["purge_ids"] = self.purge_msg_ids
                                            self.response["ok"] = 1
                            
                                        else:
                                            return self.fail( "bad or empty message dict", EC.XS_NO_MESSAGES )
                                    else:
                                        return self.fail( "can't parse message body", EC.XS_BAD_SEND_MESSAGE_BODY )
                                else:
                                    return self.fail( "dest account not ready", EC.XS_DEST_NOT_READY )
                            else:
                                return self.fail( "no dest modeldata", EC.XS_DEST_NOT_READY )
                        else:
                            return self.fail( "no account for auid", EC.XS_BAD_DEST_AUID )
                    else:
                        return self.fail( "bad mail project", EC.XS_BAD_DEST_PROJECT )
                except:
                    catch()
                    return self.fail( "can't parse message body", EC.XS_BAD_SEND_MESSAGE_BODY )
        
        self.fin()
        
        
## ------------------------------------------------------------------------------------------------------------------------------
## ------------------------------------------------------------------------------------------------------------------------------
        

class DefaultMailAction( InternalMailAction ):
    """ по умолчанию просто добавляем сообщение в acc.pending_messages """
    action = "default_mail"
    
    @action_timing
    def onStart(self):
        if self.acc.model:
            ## просто кладем копию сообщения в pending (пусть забирают по keepalive)
            self.acc.pending_changes.append( {"message":{ self.msg_id : self.msg }} )
            self.response["ok"] = 1
            
        self.fin()

    def collectPendingChanges(self):
        # приходится выгребать уже готовые changes из response, и перекладывать в pending
        model_changes_generated = self.response.get("ModelData")
        if model_changes_generated:
            if isinstance(model_changes_generated, ResponseObject):
                model_changes_generated = model_changes_generated.makeDict()
            info("generated model changes: %s", model_changes_generated)
            for change in model_changes_generated:
                self.acc.pending_changes.append({"ModelData": change})
    

## ------------------------------------------------------------------------------------------------------------------------------
## ------------------------------------------------------------------------------------------------------------------------------
    
class AsyncMailAction( InternalMailAction ):
    """ по умолчанию добавляем сообщение в acc.pending_messages, и выполняем лишний 'тренировочный' асинхронный вызов к аггрегатору """
    action = "async_mail_test"
    
    @action_timing
    def onStart(self):
        if self.acc.model:
            ## просто кладем копию сообщения в pending (пусть забирают по keepalive)
            self.acc.pending_changes.append( {"message":{ self.msg_id : self.msg }} )
            self.response["ok"] = 1
            
            ## для отладки: пробуем асинхронный вызов
            return self.I.AGG.getInfo(self.acc.auid, None, 1, self.onAggregator)
            
        self.fin()

    @action_timing
    def onAggregator(self, response):
        info("AsyncMailAction.onAggregator: response %s" % response)
        self.response["ok"] = 1
        self.fin()
    
    
## ------------------------------------------------------------------------------------------------------------------------------
## ------------------------------------------------------------------------------------------------------------------------------
class SessionAwardsMailAction( DefaultMailAction ):
    """ получаем по почте список наград от roll-сервера """
    action = "session_awards"

    @action_timing
    def onStart(self):
        info("SessionAwardsMailAction.onStart %r", self.arguments)
        if self.acc.model:
            game_id = self.msg.get("roll_id", 0) or self.msg.get("gameid", 0) # поддерживаем и старый формат передачи наград, чтобы не ломать транки-бранчи
            game_type = str(self.msg.get("game_type", ""))

            ## info("SessionAwardsMailAction(msg_id=%s, auid=%s): game_id=%s, awards=%s, session_roll=%r, game_type=%r, playerWin=%r, playerLeaver=%r" \
            ##    % (self.msg_id, self.acc.auid, game_id, awards, session_roll, game_type, playerWin, playerLeaver))

            if game_id:
                # давайте все же проконтролируем, что награды не приходят 2 раза для одного game_id
                self.I.WS.unpackGameAwards(self.acc, self.msg, self.msg_id, self.msg_type)
                self.response["ok"] = 1
            else:
                warn("BAD SessionAwardsMailAction params (msg_id=%s, auid=%s), awards skipped" % (self.msg_id, self.acc.auid))
        else:
            warn("BAD acc.model (msg_id=%s, auid=%s), awards skipped" % (self.msg_id, self.acc.auid))
            
        self.fin()

## ------------------------------------------------------------------------------------------------------------------------------
## ------------------------------------------------------------------------------------------------------------------------------
class ForgeRollMailAction( DefaultMailAction ):
    """ получаем по почте список наролленных талантов от roll-сервера """
    action = "forge_roll"

    @action_timing
    def onStart(self):
        if self.acc.model:
            roll_id = self.msg.get("roll_id", 0)
            awards = self.msg.get("awards", {})
            session_roll = self.msg.get("session_roll", "")

            info("ForgeRollMailAction(msg_id=%s, auid=%s): roll_id=%s, awards=%s" \
                % (self.msg_id, self.acc.auid, roll_id, awards))
                
            if roll_id and awards:
                # проконтролируем, что награды не приходят 2 раза для одного roll_id
                self.acc.db.roll_ids = self.acc.db.roll_ids or {}
                str_roll_id  = str(roll_id )
                prev_ts = self.acc.db.roll_ids.get( str_roll_id )
                if not prev_ts:
                    self.acc.db.roll_ids[ str_roll_id ] = toint( time.time() )
                    
                    self.I.WS.applyForgeRoll(self.acc, roll_id, awards, session_roll)
                    
                    # раз уж чего-то новое получили, давайте заодно повыкинем протухшие "ярлыки о получении наград"
                    self.I.WS.weedTimestamps(self.acc.db.roll_ids, "roll_ids", self.acc.auid, expire_period=24*60*60)
                    
                    ## для отладки -- кладем копию ключевых полей сообщения в pending (пусть забирают по keepalive)
                    self.acc.pending_changes.append( {"message":{ self.msg_id: dict(type=self.msg_type, roll_id=roll_id) }} )
                    self.response["ok"] = 1
                
                else:
                    warn("ForgeRollMailAction (msg_id=%s, auid=%s): awards already received for roll_id=%s (prev_ts %s), awards skipped" \
                        % (self.msg_id, self.acc.auid, roll_id, prev_ts))
            else:
                warn("BAD ForgeRollMailAction params (msg_id=%s, auid=%s), awards skipped" % (self.msg_id, self.acc.auid))
        else:
            warn("BAD acc.model (msg_id=%s, auid=%s), awards skipped" % (self.msg_id, self.acc.auid))
            
        self.fin()

## ------------------------------------------------------------------------------------------------------------------------------
## ------------------------------------------------------------------------------------------------------------------------------

class InviteFriendMailAction( DefaultMailAction ):
    action = "invite_friend"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            person_uid = self.msg.get("person_uid", 0)
            nickName = self.msg.get("nickName", "")
            photoUrl = self.msg.get("photoUrl", "")
            guildshortname = self.msg.get("guildshortname", "")

            isFind = False
            for friendId in self.acc.model.Friends.IncomingInvites.keys():
                friend = self.acc.model.getSimpleFriendByID( friendId )
                if friend.person_uid == person_uid:
                    isFind = True
                    break
            if not isFind:
                if self.acc.friendsdata:
                    friend = self.acc.friendsdata.findPersonByUid(person_uid)
                    if friend and not self.acc.friendsdata.hasRecentAlly(person_uid):
                        isFind = True

            if not isFind: 
                friend = self.acc.model.newSimpleFriend()[0]
                friend.person_uid = person_uid
                friend.nickName = nickName
                friend.photoUrl = photoUrl
                friend.guildshortname = guildshortname
                self.acc.model.Friends.IncomingInvites.add(friend.id)
                self.collectPendingChanges()
            info( "InviteFriendMailAction: person_uid=%r, nickName=%r, photoUrl=%r" % ( person_uid, nickName, photoUrl ) )
        else:
            warn( "BAD acc.model (msg_id=%s, auid=%s), invite friend skipped" % (self.msg_id, self.acc.auid) )
            
        self.fin()



class InviteGuildMailAction( DefaultMailAction ):
    action = "invite_guild"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            person_uid = self.msg.get("person_uid", 0)
            nickName = self.msg.get("nickName", "")
            photoUrl = self.msg.get("photoUrl", "")
            guildAuid = self.msg.get("guildAuid", 0)
            guildName = self.msg.get("guildName", "")

            isFind = False
            for giId in self.acc.model.IncomingGuildInvites.keys():
                guildInvite = self.acc.model.getGuildInviteByID( giId )
                if guildInvite.guildAuid == guildAuid:
                    isFind = True
                    break
                    
            info("InviteGuildMailAction: invite guildAuid=%s, isFind=%s, self.acc.db.guildAuid=%s" % (guildAuid, isFind, self.acc.db.guildAuid))

            if not isFind and not self.acc.db.guildAuid: 
                guildInvite = self.acc.model.newGuildInvite()[0]
                guildInvite.guildAuid = guildAuid
                guildInvite.guildName = guildName
                guildInvite.person_uid = person_uid
                guildInvite.nickName = nickName
                guildInvite.photoUrl = photoUrl
                guildInvite.timeToAutoDecline = toint( time.time() ) + self.acc.getConfigValue("GUILD_INVITE_TIMEOUT")
                self.acc.model.IncomingGuildInvites.add( guildInvite )
                self.collectPendingChanges()

            info( "InviteGuildMailAction: guildAuid=%r, guildName=%r, person_uid=%r, nickName=%r, photoUrl=%r" % ( guildAuid, guildName, person_uid, nickName, photoUrl ) )
        else:
            warn( "BAD acc.model (msg_id=%s, auid=%s), invite friend skipped" % (self.msg_id, self.acc.auid) )
            
        self.fin()

## ------------------------------------------------------------------------------------------------------------------------------

class DeleteAllGuildTalentsMailAction( DefaultMailAction ):
    action = "del_all_gltals"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            info("DeleteAllGuildTalentsMailAction: self.acc.auid=%s", self.acc.auid)
            for talentId in self.acc.model.ItemsKeeper.keys():
                talent = self.acc.model.getTalentByID(talentId)
                if talent.GuildBankInfo.get() and talent.GuildBankInfo.OwnerId != self.acc.auid:
                    if talent.Owner and talent.Owner.get():
                        hero = talent.Owner.get()
                        hero.moveTalentFromTalentSetToLibrary(talent, talentId)
                        for tsId, ts in hero.TalentSets.iteritems():
                           hero.CalcForce(self.acc.model, self.I.WS, self.acc, tsId, skipStatisticEvent=True)

                    talent.GuildBankInfo = None

                    self.acc.model.UserInventory.remove(talent)

                    self.I.STATS.addTalentChange(self.acc.db.auid,
                                                 TalentInfo(talent.PersistentId, talentId, getBoundHeroClassId(talent)),
                                                 TalentChangeOperation.ReturnToBankOnLeave)
            self.collectPendingChanges()
        else:
            warn("BAD acc.model (msg_id=%s, auid=%s), delete all talents skipped" % (self.msg_id, self.acc.auid))
            
        self.fin()

class DestroyGuildMailAction( DefaultMailAction ):
    action = "destr_guild"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            info( "DestroyGuildMailAction: self.acc.auid=%s", self.acc.auid )
            self.acc.model.LordInfo.GuildStatus = GuildStatus.Disbanded
            self.collectPendingChanges()
        else:
            warn( "BAD acc.GuildData (msg_id=%s, auid=%s), destroy guild skipped" % (self.msg_id, self.acc.auid) )

        self.fin()


class AddGuildTalentMailAction( DefaultMailAction ):
    action = "add_gltal"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            persistentId = self.msg.get("persistentId", 0)
            heroClassId = self.msg.get("heroClassId", 0)
            points = self.msg.get("points", 0)
            info( "AddGuildTalentMailAction: self.acc.auid=%s, persistentId=%s, points=%s", self.acc.auid, persistentId, points )

            staticTalent = self.acc.SD.getStaticTalentByTalentId( persistentId )
            if staticTalent and staticTalent['rarity'] != "Class":
                talent = self.acc.model.addTalent(persistentId)
                talent.Points = points

                # Проверим, не потеряем ли мы привязку гильдийского таланта
                soulboundFixed = True
                if heroClassId:
                    soulboundFixed = False
                    for heroId in self.acc.model.Heroes:
                        hero = self.acc.model.getHeroByID (heroId)
                        if hero.PersistentId == heroClassId:
                            talent.Soulbound = hero
                            soulboundFixed = True
                            break
                # Своего героя нет, придётся заводить GuildBankInfo
                if not soulboundFixed:
                    gbi, gbi_id = self.acc.model.newGuildBankInfo()
                    gbi.GuildAuid = self.acc.db.guildAuid
                    gbi.GuildTalentId = IGuidGenerator.InvalidUID
                    gbi.OwnerId = self.acc.db.auid
                    gbi.HeroClassId = heroClassId
                    talent.GuildBankInfo = gbi_id

                self.collectPendingChanges()
        else:
            warn( "BAD acc.model (msg_id=%s, auid=%s), add guild talent skipped" % (self.msg_id, self.acc.auid) )
        self.fin()
    

class DeleteGuildTalentMailAction( DefaultMailAction ):
    action = "del_gltal"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            guildTalId = self.msg.get("guildTalId", 0)
            info( "DeleteGuildTalentMailAction: self.acc.auid=%s guildTalId=%s", self.acc.auid, guildTalId )

            for talentId in self.acc.model.ItemsKeeper.keys():
                talent = self.acc.model.getTalentByID(talentId)
                if talent.GuildBankInfo.get() and talent.GuildBankInfo.GuildTalentId == guildTalId:
                    # выкинем героя из ММ, если у него гильдийские таланты в talentSet'e
                    if self.acc.data and self.acc.data.mm:
                        info("User in MM")
                        session = self.acc.data.mm
                        info("session.progress=%r", session.progress)
                        if session.progress in [MM.STATUS_INLINE]:

                            hero = self.acc.model.getHeroByID( session.hero_id )
                            if hero:
                                for tsId in hero.TalentSets.keys():
                                    if hero and hero.isTalentInTalentSet(talent.getID(), tsId):
                                        info( "canceling mm sessions on deleting guild talents (uid=%s)", self.acc.uid )
                                        self.I.WS.doMatchmakingCmd( "cancel", self.acc, MM.CANCEL_ALL )
                                        self.acc.pending_events.append( {"callback": { "callback_ec": [EC.GUILD_BANK_TALENT_REMOVED_FROM_TALENTSET], "callback": ["guild_accept"] }} )

                    talent.GuildBankInfo = None
                    talent.Soulbound = None
                    if talent.Owner and talent.Owner.get():
                        hero = talent.Owner.get()
                        for tsId in talent.ParentTalentSets.keys():
                            hero.removeTalentFromTalentSet(tsId, talent, talentId)
                            hero.CalcForce(self.acc.model, self.I.WS, self.acc, tsId, skipStatisticEvent=True)

                    self.acc.model.UserInventory.remove(talent)
                    self.I.STATS.addTalentChange(self.acc.db.auid,
                                                 TalentInfo(talent.PersistentId, talentId, getBoundHeroClassId(talent)),
                                                 TalentChangeOperation.ReturnToBank)

            self.collectPendingChanges()
        else:
            warn( "BAD acc.model (msg_id=%s, auid=%s), delete guild talent skipped", self.msg_id, self.acc.auid)
        self.fin()

## ------------------------------------------------------------------------------------------------------------------------------

class FindNickAuidAction( InternalAction ):
    """ временный метод, довольно зубодробительно вытаскивающий соответствие nick->auid по данным, которые есть на стороне соц.сервера (без аггрегатора i5) """
    action = "find_nick_auid"

    @action_timing
    def onStart(self):
        self.nick_utf8 = utf8convert( self.getParam("nick", "") )
        if self.nick_utf8:
            return self.I.SQL.findUidByNick( self.nick_utf8, self.onSqlUid )
        else:
            return self.fail("bad nick", EC.BAD_PARAM)
            
    @action_timing
    def onSqlUid(self, sql_reply):
        info("FindNickAuidAction: onSqlUid sql_reply: %s" % sql_reply)
        try:
            # достаем uid
            result = sql_reply["r"][0]
            self.uid = result.id
            if self.uid:
                # придется залезть во все шарды SQL, и у каждого спросить -- нет ли там логина для данного uid
                self.fail_count = 0
                return self.I.SQL.findLoginByUid( self.uid, self.onSqlLogin )
            else:
                return self.fail("can't find uid", EC.FIND_NICK_NO_UID)
        except:
            return self.fail("can't find uid", EC.FIND_NICK_NO_UID)
        
    @action_timing
    def onSqlLogin(self, sql_reply):
        # будет вызвано N раз, по количеству шардов mysql; в т.ч. N-1 с фейлом!
        info("FindNickAuidAction: onSqlLogin sql_reply: %s" % sql_reply)
        try:
            # достаем login
            result = sql_reply["r"][0]
            self.login_name = result.login
            if self.login_name:
                # ура, нашлось
                try:
                    self.snid, self.snuid = self.login_name.split("#")
                    self.response["snid"] = self.snid
                    self.response["snuid"] = self.snuid
                    self.response["server_id"] = result.server_id
                    return self.findAuid()
                except:
                    return self.fail("bad login", EC.FIND_NICK_BAD_LOGIN)
        except:
            self.fail_count += 1 # фейлы игнорируем ("не в этом шарде")
            if self.fail_count >= len(self.I.SQL.loop.sql):
                return self.fail("can't find login", EC.FIND_NICK_NO_LOGIN)
            
    # OVERRIDABLE (in case we don't want to use aggregator)
    def findAuid(self):
        self.I.AGG.findUser( self.snid, self.snuid, callback=self.onAggregatorAuid )
                
    @action_timing
    def onAggregatorAuid(self, agg_response):
        info("FindNickAuidAction: onAggregatorAuid response: %s", agg_response)
        if agg_response:
            self.auid = agg_response.get("auid", 0)
            if self.auid:
                self.response["ok"] = 1
                self.response["auid"] = self.auid
                self.fin()
            else:
                return self.fail("no auid in aggregator reply", EC.FIND_NICK_NO_AUID)
        else:
            return self.fail("bad aggregator reply", EC.FIND_NICK_NO_AUID)
    
## ------------------------------------------------------------------------------------------------------------------------------

class FindNickSnidAction( FindNickAuidAction ):
    """ ограничиваемся найденными реквизитами snid/snuid """
    action = "find_nick_snid"
    # OVERRIDABLE (we don't want to use aggregator, return with snid/snuid)
    def findAuid(self):
        self.response["login"] = self.login_name
        self.response["ok"] = 1
        self.fin()
        

class TicketInfoMailAction( DefaultMailAction ):
    action = "ticket_info"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            self.acc.model.TournamentInfo.TournamentTicket.State = toint(self.msg.get("State", 0))
            self.acc.model.TournamentInfo.TournamentTicket.TicketId = str(self.msg.get("TicketId", ""))
            self.acc.model.TournamentInfo.TournamentTicket.LastGameTime = toint(self.msg.get("LastGameTime", 0))
            self.acc.model.TournamentInfo.TournamentTicket.Wins = toint(self.msg.get("Wins", 0))
            self.acc.model.TournamentInfo.TournamentTicket.Losses = toint(self.msg.get("Losses", 0))
            self.acc.model.TournamentInfo.TournamentTicket.UserAuid = toint(self.msg.get("UserAuid", 0))
            self.acc.model.TournamentInfo.TournamentTicket.TicketBoughtType = toint(self.msg.get("TicketBoughtType", 0))
            gameDurations = self.msg.get("GameDurations", [])
            for duration in gameDurations:
                self.acc.model.TournamentInfo.TournamentTicket.GameDurations.append(duration)
            sessionInfos = self.msg.get("SessionInfo", [])
            for sesion in sessionInfos:
                self.acc.model.TournamentInfo.TournamentTicket.SessionInfo.append(sesion)
            info( "TicketInfoMailAction: self.acc.auid=%s, State=%s, TicketId=%s, LastGameTime=%s, Wins=%s, Losses=%s, UserAuid=%s, TicketBoughtType=%s",
                   self.acc.auid, self.acc.model.TournamentInfo.TournamentTicket.State, 
                   self.acc.model.TournamentInfo.TournamentTicket.TicketId, self.acc.model.TournamentInfo.TournamentTicket.LastGameTime,
                   self.acc.model.TournamentInfo.TournamentTicket.Wins, self.acc.model.TournamentInfo.TournamentTicket.Losses,
                   self.acc.model.TournamentInfo.TournamentTicket.UserAuid, self.acc.model.TournamentInfo.TournamentTicket.TicketBoughtType )

            self.collectPendingChanges()
        else:
            warn( "BAD acc.model (msg_id=%s, auid=%s), add guild talent skipped" % (self.msg_id, self.acc.auid) )
        self.fin()

class AddGuildBufMailAction(DefaultMailAction):
    action = "add_glbuf"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            persistentId = self.msg.get("persistentId", 0)
            expireTime = self.msg.get("expireTime", 0)
            info("AddGuildBufMailAction: self.acc.auid=%s, persistentId=%s, expireTime=%d", self.acc.auid, persistentId, expireTime)

            staticShopItem = self.acc.SD.getGuildShopItemById(persistentId)
            if staticShopItem:
                if staticShopItem['classType'] == "OneTimeGuildShopItem":
                    if staticShopItem['guildBuff']['duration'] != 0 and expireTime <= int(time.time()):
                        # Поздновато пришёл..
                        self.fin()
                        return

                    self.acc.model.AddOneTimeGuildShopItem(self.acc, self.acc.SD, expireTime, staticShopItem)

                self.collectPendingChanges()
        else:
            warn( "BAD acc.model (msg_id=%s, auid=%s), add guild buf skipped" % (self.msg_id, self.acc.auid) )
        self.fin()


class DeleteAllGuildBufsMailAction(DefaultMailAction):
    action = "del_all_glbufs"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            info("DeleteAllGuildBufsMailAction: self.acc.auid=%s", self.acc.auid)
            for bufId in self.acc.model.GuildBufs.keys():
                buf = self.acc.model.getGuildBufByID(bufId)
                if buf.GuildOnly:
                    self.acc.model.GuildBufs.remove(bufId)
            self.acc.model.deactivateAllWeakerBonuses(self.acc.SD)
            self.collectPendingChanges()
        else:
            warn("BAD acc.model (msg_id=%s, auid=%s), delete all bufs skipped" % (self.msg_id, self.acc.auid))

        self.fin()

class RemoveGuildApplicationMailAction(DefaultMailAction):
    action = "recruit_guild_gone"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            guildAuid = self.msg.get("guildAuid", 0)
            if guildAuid:
                info("RemoveGuildApplicationMailAction: self.acc.auid=%s, guildAuid=%s", self.acc.auid, guildAuid)
                try:
                    self.acc.model.removeGuildApplication(guildAuid, any_state=True)
                    model_changes_generated = self.response.get("ModelData")
                    if model_changes_generated:
                        if isinstance(model_changes_generated, ResponseObject):
                            model_changes_generated = model_changes_generated.makeDict()
                        debug("generated recruit_guild_gone model changes: %s" % model_changes_generated)
                        for change in model_changes_generated:
                            self.acc.pending_changes.append({"ModelData": change})
                except RecruitmentError:
                    pass
            else:
                error("RemoveGuildApplicationMailAction: self.acc.auid=%s: Empty guildAuid!", self.acc.auid)
        else:
            warn("BAD acc.model (msg_id=%s, auid=%s), delete all bufs skipped" % (self.msg_id, self.acc.auid))
        self.fin()

class RecruitApplicationRejectedMailAction(DefaultMailAction):
    action = "recruit_rejected"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.model:
            guildAuid = self.msg.get("guildAuid", 0)
            if guildAuid:
                info("RecruitApplicationRejectedMailAction: self.acc.auid=%s, guildAuid=%s", self.acc.auid, guildAuid)
                for app_id in self.acc.model.GuildApplications:
                    app = self.acc.model.getGuildApplicationByID(app_id)
                    if app.GuildAuid == guildAuid:
                        app.Rejected = True

                self.collectPendingChanges()
            else:
                error("RecruitApplicationRejectedMailAction: self.acc.auid=%s: Empty guildAuid!", self.acc.auid)
        else:
            warn("BAD acc.model (msg_id=%s, auid=%s), delete all bufs skipped" % (self.msg_id, self.acc.auid))
        self.fin()

class AddMuteAction(DefaultMailAction):
    action = "add_mute"

    @action_timing
    @model_callback
    def onStart(self):
        if self.acc.db:
            muteTime = self.msg.get("muteTime", None)
            info("AddMuteAction: self.acc.auid=%s, muteTime=%d",
                 self.acc.auid, muteTime)

            # PF-98178
            # if muteTime and (muteTime > int(time.time()) or muteTime == 0):
            if (muteTime is not None) and (muteTime > int(time.time()) or muteTime == 0):
                self.acc.db.muted = 1
                if muteTime == 0:
                    self.acc.db.mutetime = 0
                else:
                    self.acc.db.mutetime = muteTime
                self.I.PS.mute(self.acc.auid, 1)
                if self.acc.chat:
                    self.I.CHAT.muteUser(self.acc.chat['host'], self.acc.auid, 1, self.acc.db.mutetime, None)
                else:
                    warn("MuteUser: no acc.chat for auid=%s", self.acc.auid)

                self.collectPendingChanges()
        else:
            warn( "BAD acc.model (msg_id=%s, auid=%s), add mute skipped" % (self.msg_id, self.acc.auid) )
        self.fin()
