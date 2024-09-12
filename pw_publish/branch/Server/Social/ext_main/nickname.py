# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *

from subaction import SubAction, action_timing
from tornado.options import options
import chat_utils
import CC
from ext_main.guild_app_loader import GuildApplicationsLoader

from intaction import InternalAction

import EC # error codes

## ---------------------------------------------------------------

class CheckNicknameAction(SubAction):
    ## action, который будет обрабатывать данный класс:
    action = "check_nickname"
    debug = True

    @action_timing
    def onStart(self):
        info( "CheckNickname.onStart" )
        nickname = self.getParam("nickname", "")
        forbidden = self.acc.getConfigValue("ADMIN_NICKS").keys()

        (r, nickname_unicode, encoding) = SetNicknameAction.checkNickname(nickname,
            self.acc.getConfigValue("NICKNAME_REGEXES").keys(), forbidden)

        if r == SetNicknameAction.CHECK_OK:
            # ник прошел проверку, смотрим в базе уникален ли он            
            nickname_utf8 = nickname_unicode.encode( 'utf8' )
            self.I.SQL.findUidByNick( nickname_utf8, self.onSQLResponse )
            return

        info( "check result = %r" % r )
        self.response["error"] = "nickname is invalid"
        self.response["ec"] = EC.NICK_BAD_PARAMS
        self.fin()

    def onSQLResponse(self, sql_reply):
        try:
            info( "CheckNickname.onSQLResponse reply: %s" % sql_reply )
            uid = sql_reply.get("p")
            result = sql_reply.get("r")
            
            if not result:
                info("CheckNickname.onSQLResponse: nickname is free")
                self.response["ok"] = 1
            else:
                self.response["error"] = "failed to set new nick: must be duplicate"
                self.response["ec"] = EC.NICKNAME_NOT_UNIQUE
        except:
            catch()
            warn("onSetNick failed sql reply: %s" % sql_reply)
            self.response["error"] = "failed sql operation"
            self.response["ec"] = EC.NICKNAME_OPERATION_FAILED
            
        self.fin()

## ---------------------------------------------------------------

class SetNicknameAction(SubAction, GuildApplicationsLoader):
    ## action, который будет обрабатывать данный класс:
    action = "set_nickname"
    debug = True
    
    NICKNAME_ENCODINGS = ['utf8']
    MIN_NICKNAME_LENGTH = 3
    MAX_NICKNAME_LENGTH = 32
    
    NICKNAME_SPECIAL_SYMBOLS_COMBO = u'^\s|[\s_\-]{2,}|\s$'

    # пока включаем в "английский" вариант и турецкие символы
    NICKNAME_NOT_ENGLISH = u'[^abcçdefgğhıijklmnoöpqrsştuüwvxyzABCÇDEFGĞHIİJKLMNOÖPQRSŞTUÜWVXYZ0-9 _\-]'
    NICKNAME_NOT_RUSSIAN = u'[^ЙЦУКЕЁНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮйцукеёнгшщзхъфывапролджэячсмитьбю0-9 _\-]'
    
    DEFAULT_FORBIDDEN_NICKS = [u'administrator', u'admin', u'админ', u'администратор']
    
    CHECK_OK = 0
    CHECK_INVALID_LENGTH = 1
    CHECK_INVALID_CHAR = 2
    CHECK_INVALID_DOUBLE_SPECIAL = 3
    CHECK_FORBIDDEN = 4
    CHECK_INVALID_ENCODING = 5
    
    @staticmethod
    def checkNickname(nickname, regexes, forbidden, min=MIN_NICKNAME_LENGTH, max=MAX_NICKNAME_LENGTH):
      nickname_unicode = nickname
      nickname_encoding = None
      decoded = 0
      for encoding in SetNicknameAction.NICKNAME_ENCODINGS:
        try:
            nickname_unicode = unicode( nickname, encoding )
            nickname_encoding = encoding
            decoded = 1
            break # видимо, получилось
        except:
            pass

      if decoded == 0:
        info( "can't decode nickname \"%r\"" % nickname )
        return ( SetNicknameAction.CHECK_INVALID_ENCODING, None, None )

      if not len( nickname_unicode ) in xrange( min, max+1 ):
        return ( SetNicknameAction.CHECK_INVALID_LENGTH, None, None )
        
      if not regexes:
          regs = [SetNicknameAction.NICKNAME_SPECIAL_SYMBOLS_COMBO, SetNicknameAction.NICKNAME_NOT_ENGLISH, SetNicknameAction.NICKNAME_NOT_RUSSIAN]
      else:
          regs = regexes

      if re.search( regs[0], nickname_unicode ):
        return ( SetNicknameAction.CHECK_INVALID_DOUBLE_SPECIAL, None, None )
        
      for regex in regs[1:]:
        if not re.search( regex, nickname_unicode ):
          break
      else:
        return ( SetNicknameAction.CHECK_INVALID_CHAR, None, None )
        
      forbidden_nicks = forbidden or SetNicknameAction.DEFAULT_FORBIDDEN_NICKS
      if nickname_unicode.lower() in forbidden_nicks:
        return ( SetNicknameAction.CHECK_FORBIDDEN, None, None )
        
      return ( SetNicknameAction.CHECK_OK, nickname_unicode, nickname_encoding )
    
    
    ## Получаем и проверяем ник. Отправляем запрос в SQL для установки ника 
    ## и проверки на уникальность. Управление перейдет в onSetNick по 
    ## ответу из базы
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        info("SetNickname.onStart for auid %s", self.acc.db.auid)
        self.nickname_encoded = self.getParam("nickname", "")
        if not self.nickname_encoded:
            self.errorResponse( EC.NICK_BAD_PARAMS, "no nickname" )
            return
                
        r, self.nickname_unicode, self.nickname_encoding = SetNicknameAction.checkNickname(self.nickname_encoded,
            self.acc.getConfigValue("NICKNAME_REGEXES").keys(), self.acc.getConfigValue("ADMIN_NICKS").keys())
        
        if r == SetNicknameAction.CHECK_INVALID_ENCODING:
            self.errorResponse( EC.NICK_BAD_PARAMS, "can't decode nickname" )
            return
            
        if r == SetNicknameAction.CHECK_INVALID_LENGTH:
            self.errorResponse( EC.NICK_BAD_PARAMS, "bad nickname length, should be in %d..%d" % ( SetNicknameAction.MIN_NICKNAME_LENGTH, SetNicknameAction.MAX_NICKNAME_LENGTH ) )
            return
        
        if r == SetNicknameAction.CHECK_INVALID_DOUBLE_SPECIAL:
            self.errorResponse( EC.NICK_BAD_PARAMS, "two or more special symbols in a row or leading spaces" )
            return
        
        if r == SetNicknameAction.CHECK_INVALID_CHAR:
            self.errorResponse( EC.NICK_BAD_PARAMS, "bad characters in nickname" )
            return
        
        if r == SetNicknameAction.CHECK_FORBIDDEN:
            self.errorResponse( EC.NICK_BAD_PARAMS, "nickname is forbidden" )
            return
                
        loaded = toint(self.acc.loaded)
        self.response["loaded"] = loaded
        if not loaded:
            self.errorResponse( EC.NICK_BAD_PARAMS, "persistent data not loaded, please wait" )
            return
            
        self.nickname_utf8 = self.nickname_unicode.encode( 'utf8' )
        self.I.SQL.setNick( self.acc.uid, self.nickname_utf8, self.onSetNick )
        self.I.EXPORT.updateLegendNickname(self.acc.auid, self.nickname_utf8)
        
    # --------------------------------------------------------------------------------------------------
    @action_timing
    def onSetNick(self, sql_reply):
        try:
            info("onSetNick reply: %s", sql_reply)
            result = sql_reply.get("r")
            
            if result and len(result):
                id_ok = result[0].idok
                if id_ok:
                    # все старые инстансы ника для данного юзера надо удалить (по идее, там не более 1, но в каком sql-шарде, узнать проблематично) 
                    if self.acc.nick:
                        self.I.SQL.removeOldNick(self.acc.uid, self.acc.nick, self.nickname_utf8)
                    
                    self.acc.nick = self.nickname_utf8
                    self.acc.db.nick = self.nickname_unicode # в mongo будем хранить в unicode
                    self.acc.db.nick_encoding = self.nickname_encoding # но на всякий случай запомним, в какой кодировке было изначально
                    # и еще один тайный карман, где хранятся данные юзеров:
                    self.I.WS.setLoginNick(self.acc.auid, self.nickname_utf8)
                    
                    info( "user nick: unicode '%s'" % repr(self.nickname_unicode) )
                    
                    ########### DEBUG: сливаем все ники в файлик
                    #if id_ok > 0:
                    #    file = open("logs/wsX.%d.nicknames" % options.server_id, "at")
                    #    file.write( self.nickname_encoded )
                    #   file.write( ':' )
                    #    file.write( self.nickname_encoding )
                    #    file.write( '\n' )
                    #    file.close()
                    ########### 
                    
                    # поменялся ник -- извещаем PersonServer
                    self.I.WS.updateGameDataToPersonServer(self.acc)
                    self.callWithGuildApplications(self.passToGuildApplications)
                   
                    self.response["db"] = self.acc.db
                    self.response["ok"] = 1

                    if self.acc.chat:
                        self.I.CHAT.removeUser(self.acc.chat['host'], self.acc.auid, self.onRemoveFromChat)
                        return 
                    elif chat_utils.addToChat(self.I.CHAT, self.acc.fraction, self.acc, options.server_id, self.onAddToChat):
                        return 
                else:
                    self.response["error"] = "failed to set new nick: must be duplicate"
                    self.response["ec"] = EC.NICKNAME_NOT_UNIQUE
            else:
                self.response["error"] = "failed sql operation"
                self.response["ec"] = EC.NICKNAME_OPERATION_FAILED
                
        except:
            catch()
            warn("onSetNick failed sql reply: %s" % sql_reply)
            self.response["error"] = "failed sql operation"
            self.response["ec"] = EC.NICKNAME_OPERATION_FAILED
            
        self.fin()

    # --------------------------------------------------------------------------------------------------
    @action_timing
    def onRemoveFromChat(self, response):
        info( "onRemoveFromChat: response %s" % str(response) )
        if chat_utils.addToChat(self.I.CHAT, self.acc.fraction, self.acc, options.server_id, self.onAddToChat):
            return
        self.fin()

    # --------------------------------------------------------------------------------------------------
    @action_timing
    def onAddToChat(self, response):
        if response and response.get("ok"):
            self.response['chat'] = { 'host' : self.acc.chat['host'], 'key' : self.acc.chat['key'] }
        else:
            warn( "onAddToChat: response %s" % str(response) )
        self.fin()
            

    def passToGuildApplications(self):
        "Pass new nickname to recruit applications if any."
        info("passToGuildApplications: applications found: %s", len(self.acc.model.GuildApplications))
        # if self.acc.model.LordInfo.UpdateGuildApplications:
        if len(self.acc.model.GuildApplications):
            self.I.DATA.multi_update(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA, {"pers_auid": self.acc.auid},
                {"nickname": self.acc.nick}, callback=self.onMongoGuildRequestsUpdated)


    def onMongoGuildRequestsUpdated(self, response):
        if not (response and response.get("r")):
            err("SetNicknameAction.onMongoGuildRequestsUpdated: Error updating guild recruit requets: %s", response.get("ex"))
            return
        info("SetNicknameAction.onMongoGuildRequestsUpdated")
        for app in self.acc.model.GuildApplications.itervalues():
            if not app.Rejected:
                self.I.GS.renameRecruitNotification(self.acc.auid, self.acc.nick, app.GuildAuid)

# ---------------------------------------

class NicknameRemoveSquareBrackets( InternalAction ):
    """  """
    action = "nickname_remove_square_brackets"
    
    @action_timing
    def onStart(self):
        if self.acc:
            self.converted_nick = self.acc.nick.replace("[", "")
            self.converted_nick = self.converted_nick.replace("]", "")
            if self.converted_nick != self.acc.nick:
                info("NicknameRemoveSquareBrackets.onStart (auid=%s) self.acc.nick=%r, converted_nick=%r, nickChanged=%s" \
                    % (self.acc.auid, self.acc.nick, self.converted_nick, self.acc.db.nickChanged))
                subParams = ClassDict( nickname=[self.converted_nick] )
                self.nickAction = SetNicknameAction( subParams, self.onChangeNickname1, self )
                return self.nickAction.onStart()
            else:
                self.response["ok"] = 1
        self.fin()
        
    def onChangeNickname1(self, response):
        if response.get("ok", 0):
            return self.success()
        else:
            # фейл; попробуем еще раз, подставив к нику auid для уникальности
            str_auid = str(self.acc.auid)
            len_auid = len(str_auid)
            cut_length = SetNicknameAction.MAX_NICKNAME_LENGTH - len_auid
            self.converted_nick = self.converted_nick[ :cut_length ] + str_auid
            info("NicknameRemoveSquareBrackets.onChangeNickname1 (auid=%s) self.acc.nick=%r, converted_nick=%r" % (self.acc.auid, self.acc.nick, self.converted_nick))
            subParams = ClassDict( nickname=[self.converted_nick] )
            self.nickAction = SetNicknameAction( subParams, self.onChangeNickname2, self )
            return self.nickAction.onStart()
        
    def onChangeNickname2(self, response):
        if response.get("ok", 0):
            return self.success()
        else:
            # последняя попытка: вместо ника ставим timestamp+auid (должно быть уникально с вероятностью близкой к 1)
            self.converted_nick = "%d_%d" % ( toint(time.time()), self.acc.auid )
            # фейл; попробуем еще раз, подставив к нику auid для уникальности
            info("NicknameRemoveSquareBrackets.onChangeNickname2 (auid=%s) self.acc.nick=%r, converted_nick=%r" % (self.acc.auid, self.acc.nick, self.converted_nick))
            subParams = ClassDict( nickname=[self.converted_nick] )
            self.nickAction = SetNicknameAction( subParams, self.onChangeNickname3, self )
            return self.nickAction.onStart()

    def onChangeNickname3(self, response):
        if response.get("ok", 0):
            return self.success()
        self.fin()
        
    def success(self):
        # в случае успешного авто-переименования - выдаем +1 бесплатное пользовательское переименование
        config_free_changes = self.acc.getConfigValue("FREE_NICK_CHANGES")
        self.acc.db.nickChanged = min( self.acc.db.nickChanged-1, config_free_changes-1 )
        info("NicknameRemoveSquareBrackets.success (auid=%s), new nickChanged=%s [config_free_changes=%s]" \
            % (self.acc.auid, self.acc.db.nickChanged, config_free_changes))
        self.response["ok"] = 1
        self.fin()
        
