# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging

from subaction import SubAction, action_timing, separate_timing
from base.helpers import *
from enums import *
from handlers import *
from nickname import SetNicknameAction

from tornado.options import options

import EC # error codes
import chat_utils
import cfg
import party_const

## ---------------------------------------------------------------
## ---------------------------------------------------------------

class AuthAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "auth"
    
    ## клиент присылает правильно сгенерированную "цифровую подпись" (key), и заодно может получить в ответ persistent данные юзера (если уже загрузились)
    @separate_timing
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        log("AuthAction.onStart")
        
        loaded = toint(self.acc.loaded)
        self.response["loaded"] = loaded

        self.acc.userlocale = self.getParam("userlocale", cfg.MATCHMAKER_DEFAULT_LOCALE)

        if loaded:
            if self.checkRid(self.action):
                return self.errorResponse(EC.BAD_PARAM, "bad param rid")

            if cfg.TOURNAMENT_SERVER:
                if self.acc.model.TournamentInfo.TournamentTicket.UserAuid == self.acc.db.auid and self.acc.model.TournamentInfo.TournamentTicket.State == TicketState.InTournament and self.acc.model.TournamentInfo.TournamentState == TournamentState.InProgress:
                    if self.acc.getConfig().KICK_FROM_TOURNAMENT_BY_TIMEOUT:
                        # проверим, не пропустили ли мы слишком много дней
                        if self.acc.model.TournamentInfo.TournamentTicket.MissedGames >= self.acc.getConfig().TournamentSettings.MAX_GAMES_TO_MISS and (int(time.time()) - self.acc.model.TournamentInfo.TournamentTicket.LastGameTime) > self.acc.getConfig().TournamentSettings.HOURS_FOR_MISS*60*60:
                            self.acc.model.TournamentInfo.TournamentTicket.MissedGames += 1

                        # если мы уже пропускали игру или пропустили слишком много времени подряд
                        if (self.acc.model.TournamentInfo.TournamentTicket.MissedGames > self.acc.getConfig().TournamentSettings.MAX_GAMES_TO_MISS or
                           (int(time.time()) - self.acc.model.TournamentInfo.TournamentTicket.LastGameTime) > self.acc.getConfig().TournamentSettings.HOURS_FROM_LAST_PLAY*60*60):
                            self.acc.model.TournamentInfo.TournamentTicket.State = TicketState.TournamentLost
                            self.acc.model.TournamentInfo.sendTournamentTicket( self.acc, self.I.HTTP )


                if self.acc.model.TournamentInfo.TournamentTicket.State == TicketState.TournamentLost and self.acc.db.auid not in cfg.TOURNAMENT_SPECTATOR_AUIDS:
                    self.acc.model.TournamentInfo.sendTournamentTicket( self.acc, self.I.HTTP )
                    self.response["ec"] = EC.TOURNAMENT_IS_OVER
                    self.response["error"] = "Tournament is over"
                    self.fin()
                    return
            

            #self.response["data"] = self.acc.data -- клиенту наши внутренние данные неинтересны
            self.response["db"] = self.acc.db

            # поля, задаваемые по умолчанию, а потом переопределяемые из persistent, неплохо бы вынести отдельно
            self.response["nick"] = self.acc.getNickname()
            self.response["sex"] = self.acc.sex
            self.response["geolocation"] = self.acc.geolocation
            self.response["mmServerStatus"] = self.I.WS.mmServerStatus
            self.response["userlocale"] = self.acc.userlocale
        
            # отсылаем на клиент Config
            self.response["config"] = self.acc.getConfigJson()

            # полное дерево Model Data в новом формате [op, path, json_changes]                             
            self.response["init"] = self.acc.model.generateJsonDict()
            self.I.WS.subscribeAccToGuildServer( self.acc )

            # Добавляем информацию про топовый билд
            self.response["TopBuildsData"] = self.I.WS.getTopBuildsData()
            self.response["GuildWarEventData"] = self.I.WS.getGuildWarEventDataChanges()
            
            # список регулярок для проверки ников (если хотя бы по одной из них в нике не нашлось левых символов, значит ок)
            # первой идет регулярка для ограничения по спец. символам и пробелам, далее языки (см. выше)
            regexes = self.acc.getConfigValue("NICKNAME_REGEXES").keys()
            if not regexes:
                regexes = [SetNicknameAction.NICKNAME_SPECIAL_SYMBOLS_COMBO, SetNicknameAction.NICKNAME_NOT_ENGLISH, SetNicknameAction.NICKNAME_NOT_RUSSIAN]
            self.response["nickname_regex"] = regexes

            # причесываем докладываемый клиенту вид полной Model Data 
            self.I.WS.modelFullUpdateFix( self )

            self.remote_ip = ""
            try:
                l = self.acc.login.lower()
                if l in repeated_requests["sn_login"]:
                    repeated_requests["sn_login"].pop(l)
                self.remote_ip = self.request.request.headers.get("X-Real-IP", "")
            except:
                pass

            # необходимо получить chat context
            if chat_utils.addToChat(self.I.CHAT, self.acc.fraction, self.acc, options.server_id, self.onChatRegister):
                return
            else:
                self.response['ok'] = 1
                
        else:
            self.response["ec"] = EC.ACCOUNT_NOT_LOADED
        self.fin()

    @action_timing
    def onChatRegister(self, response):
        if response and response.get("ok"):
            self.response['chat'] = { 'host' : self.acc.chat['host'], 'key' : self.acc.chat['key'] }
        self.response['ok'] = 1
        self.fin()
