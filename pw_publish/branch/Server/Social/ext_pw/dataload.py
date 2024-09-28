# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging

from subaction import *
import pwconst
import chat_utils
from enums import *
from party_const import FRACTION, FRACTION_LIST
from functools import partial
import CC

## ---------------------------------------------------------------
## ---------------------------------------------------------------

class SetFractionAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "set_fraction" 
    
    ## юзер выбирает фракцию (КОСТЫЛЬ: также можно сохранить Model Data)
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        log("SetFractionAction.onStart")
        
        self.fraction = self.getParam("fraction")
        self.create_heroes = self.getIntParam("create_heroes", pwconst.CREATE_ALL_HEROES) # по умолчанию пусть создаются все герои, сколько есть
        self.force_new = self.getParam("force_new")
        self.full_reset = self.getParam("full_reset")
        isReset = False
        self.remote_ip = ""
        try:
            self.remote_ip = self.request.request.headers.get("X-Real-IP", "")
        except:
            pass
        
        if self.checkPossibleValue(self.fraction, FRACTION_LIST, error="bad fraction"):
            loaded = toint(self.acc.loaded)
            self.response["loaded"] = loaded
            
            if loaded or self.force_new:
                # запоминаем выбранную фракцию
                self.acc.db.fraction = self.fraction
                self.acc.db.reset_account_time = self.acc.db.get("reset_account_time", 0)
                if not self.acc.db.has_key("isRegularMMAllowed"):
                    self.acc.db.isRegularMMAllowed = True

                if ("castle_roll") not in self.acc.db:
                    self.acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {},
                                               CC.REROLL_DAILY_WEIGHTS: {}}
                
                if self.fraction == FRACTION.NONE : #if self.full_reset
                    debug( "fraction N, self.acc.db.reset_account_time = %r > int(time.time() = %r",  self.acc.db.reset_account_time, int(time.time()))
                    if self.acc.db.reset_account_time > int(time.time()):
                        warn("User %r cann't reset his account. User has reset his account less than %r sec ago", self.acc.auid, self.I.Config.getMainConfig().RESET_ACCOUNT_TIME)
                        self.fail("You cann't reset your account. You've reset your account less than %r sec ago" % self.I.Config.getMainConfig().RESET_ACCOUNT_TIME, EC.DEBUG_MESSAGE)
                        return

                    info( "fraction N, clearing nick (auid=%s)" % self.acc.auid )


                    # при полном ресете сбросим и никнейм
                    if self.acc.nick:
                        self.I.SQL.removeOldNick(self.acc.uid, self.acc.nick, "")
                    self.acc.db.nick = ""
                    self.acc.nick = ""
                    # и еще один тайный карман, где хранятся данные юзеров:
                    self.I.WS.setLoginNick(self.acc.auid, "")
                    # из гильдии валим
                    if self.acc.db.guildAuid:
                        self.I.GS.leaveGuild( self.acc, None )
                        #self.I.GS.unsubscribe( self.acc, options.server_id, None )
                        # и даже если leaveGuild упал, будем убивать гильдию!
                        self.acc.db.guildAuid = 0
                    # Сохраняем инфу о золотой руне PF-73099
                    self.acc.model.saveLampInfo( self.acc )
                    self.acc.db.reset_account_time = int(time.time()) + self.I.Config.getMainConfig().RESET_ACCOUNT_TIME
                    isReset = True

                # лочим аккаунт (на время асинхронного создания ModelData запрещаем прочие запросы)
                self.acc.locked = 1 

                # создаем новую модель данных

                debug("Calling self.I.SMODEL.newSerialModel. Current acc.model.LordInfo.TutorialState = %s", self.acc.model.LordInfo.TutorialState)

                if  not self.acc.model:
                    self.I.SMODEL.newSerialModel( self.acc.auid, self.fraction, self.acc.sex, self.acc.guest, ClassDict(self.acc.db), self.acc.model, \
                        self.acc.Config, self.acc.SD, self.acc.userlocale, self.acc.country_code, isReset, callback=partial(self.onNewModelReady, False) )
                else:

                    self.I.SMODEL.newSerialModel( self.acc.auid, self.fraction, self.acc.sex, self.acc.guest, ClassDict(self.acc.db), self.acc.model, \
                        self.acc.Config, self.acc.SD, self.acc.userlocale, self.acc.country_code, isReset, callback=partial(self.onNewModelReady, True))


                if self.fraction != FRACTION.NONE:
                    nick = self.acc.getNickname()
                    price = ClassDict( Gold=0, Silver=0, Perl=0, RedPerl=0, Population=0, Resource1=0, Resource2=0, Resource3=0 )
                    self.I.STATS.addFactionSelect( self.acc.auid, "N", self.fraction, price, price )


                return
            
        self.fin()


    @action_timing
    def onNewModelReady(self, isTutorial, serial_reply):
        t0 = time.time()
        
        if serial_reply:
            new_acc = serial_reply.get("r")
            if new_acc and new_acc.model:
                savedTS = new_acc.model.LordInfo.TutorialState
                if isTutorial:
                    savedTS = self.acc.model.LordInfo.TutorialState

                self.acc.model = new_acc.model
                
                self.I.PDM.applyModelDataDbChanges( self.acc, new_acc ) # нужно применить изменения new_acc.db, которые могли внести скрипты (конверсии, евенты и т.п.)
                
                ## зачищаем matchmaking и прочие "идущие игровые сессии"
                self.I.WS.resetUserSessions( self.acc )
                self.acc.pending_changes = []


                if self.fraction != FRACTION.NONE:
                    # при выборе новой фракции нужно насильно выдать бонусные таланты ("за присоединение соц.сетей")
                    info("onNewModelReady: reset sn_count_prev (was %s), give bonus talents" % self.acc.sn_count_prev)
                    self.acc.sn_count_prev = 0
                    self.I.WS.checkGiveBonusTalents( self.acc )

                if isTutorial and savedTS is not TutorialState.NotStarted:
                    debug("onNewModelReady: restore tutorial state to %s", enum2String(TutorialState, savedTS))
                    self.acc.model.LordInfo.TutorialState = savedTS
                    if self.acc.model.LordInfo.TutorialState == TutorialState.Skipped:
                        self.I.WS.onUserSkipTutorial( self.acc )

                # отсылаем на клиент Config
                self.response["config"] = self.acc.getConfigJson()
                
                # полное дерево Model Data в новом формате [op, path, json_changes]
                self.response["init"] = self.acc.model.generateJsonDict()

                self.response["nick"] = self.acc.getNickname()
                
                # причесываем докладываемый клиенту вид полной Model Data 
                self.I.WS.modelFullUpdateFix( self )

                # служебные данные, не входящие в Model Data, шлем как и прежде (data, db)
                self.response["data"] = self.acc.data
                self.response["db"] = self.acc.db
                
                # поменялась фракция -- извещаем PersonServer
                self.I.WS.updateGameDataToPersonServer( self.acc )
                self.I.WS.subscribeAccToGuildServer( self.acc ) 

                # отпускаем аккаунт; с асинхронным созданием ModelData разобрались, можно исполнять прочие запросы
                self.acc.locked = 0 
                self.generateTime = time.time()-t0

                self.response["ok"] = 1

                if self.acc.chat:
                    self.I.CHAT.removeUser(self.acc.chat['host'], self.acc.auid, self.onRemoveFromChat)
                    return 
                elif chat_utils.addToChat(self.I.CHAT, self.fraction, self.acc, options.server_id, self.onAddToChat):
                    return
                else:
                    return self.doFinish()
            else:
                self.response["error"] = "fail creating new ModelData: new acc failed (uid=%s)" % new_acc.uid
                self.acc.failed = 1 
        else:
            self.response["error"] = "bad serial reply: %s" % str(serial_reply)

        # ecли все плохо, тоже отпускаем    
        self.acc.locked = 0 
        self.fin()

    # --------------------------------------------------------------------------------------------------
    @action_timing
    def onRemoveFromChat(self, response):
        info( "onRemoveFromChat: response %s" % str(response) )
        if chat_utils.addToChat(self.I.CHAT, self.fraction, self.acc, options.server_id, self.onAddToChat):
            return
        self.doFinish()

    @action_timing
    def onAddToChat(self, response):
        if response and response.get("ok"):
            self.response['chat'] = { 'host' : self.acc.chat['host'], 'key' : self.acc.chat['key'] }
        else:
            warn( "onAddToChat: response %s" % str(response) )
        self.doFinish()

    def doFinish(self):
        t0 = time.time()
        self.fin()
        t1 = time.time()
        info( "set fraction times: fix %.3f, reply %.3f" % (self.generateTime, t1-t0) )
