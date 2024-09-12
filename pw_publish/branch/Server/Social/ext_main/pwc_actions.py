# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Social Aggregator Login
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, base64
import functools

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

##import collections
## print type(_addPath), isinstance(_addPath, collections.Callable)

_addPath('..')
from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing
from instr import *
from base.helpers import makeSignedRequest, makeParamsSignature, checkParamsSignature, randomMD5

import coord_cfg
import cfg
import iaggregator

from login import BaseCheckVersionAction, LoginAction
from geo_cfg import DEFAULT_GEO_LOCATION
from subaction import SubAction, action_timing, separate_timing, parseGeoLocation

from LoginUser import User

import time
import json
import base64

import EC
import CC

def onSendMailCallback(smtp_reply):
    debug("onSendMailCallback: reply %s", smtp_reply)

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------
## дефолтный декоратор для обработчиков sql_reply
## прописывает, чтобы автоматические modelChange добавлялись в наш self.response[]
def sql_callback(method):
    @functools.wraps(method)
    def wrapper(self, sql_reply, *args, **kwargs):
        info( "%s: %s" % (method.__name__, sql_reply) )
        if sql_reply:
            if ( 'x' in sql_reply and isinstance(sql_reply.get('r'), (int,long) ) ) or sql_reply.get('r') :
                return method(self, sql_reply, *args, **kwargs)
            else:
                self.response["error"] = "bad sql %s reply" % method.__name__
                self.response["ec"] = EC.PWC_BAD_USER
                try:
                    if self.request.pretty:
                        self.response["sql_error"] = sql_reply.get("ex")
                except:
                    pass
                # fail:

                self.fin()
        else:
            self.response["error"] = "bad sql %s reply" % method.__name__
            self.response["ec"] = EC.PWC_BAD_USER
            self.fin()

    return wrapper

class PWCBase( SubAction ):
    """ common const/methods """
    EMAIL_ENCODINGS = ['utf8']
    EMAIL_LENGTH = xrange(5, 65) # от 5 до 64 символов включительно

    DEFAULT_MESSAGES = {
        'title': {
            'confirm': u"[Confirm registration]",
            'reset_pwd': u"[Reset Password]",
            'change_pwd_link': u"[Reset Password Link]",
            'bruteforce_msg' : u"[Attempt of cracking of the account]"
        },
        'body': {
            'confirm': u"Activation code %s\n \nClick this link to activate:\n%s",
            'reset_pwd': u"New password:\n%s",
            'change_pwd_link': u"Click this link to change password:\n%s",
            'bruteforce_msg' : u"Your account is tried to be hacked.\n Please change the password of your account on more difficult. If you are sure of your password then just ignore this letter."
        },
    }



    def fakeSocialInfo( self ):
        linfo = ClassDict( auid=str(self.token.auid), sex=self.token.gender, birthdate=self.token.birthdate ) # ланчеровский JavaScript не съест int64 auid, так что строкой
        self.response["info"] = linfo
        self.response["auid"] = str(self.token.auid) # ланчеровский JavaScript не съест int64, так что строкой
        self.response["pwc_snuid"] = str(self.token.pwc_snuid)
        self.response["sex"] = self.token.gender
    # -------------------------------------------------------------------------------------------------------
    def importLocaleMessagePart(self, msg_type, msg_part, locale=None):
        if not locale:
            locale = self.locale

        if not hasattr(self, "mail_path"):
            full_path = os.path.dirname(os.path.abspath(__file__))
            self.mail_path = full_path.replace(os.sep + "ext_main", "")

        filename = os.path.join(self.mail_path, "mail", "%s.%s.%s" % (locale, msg_type, msg_part))
        try:
            msg_file = open(filename, "rt")
            msg_unicode = unicode(msg_file.read(), "utf8")
            msg_unicode = msg_unicode.replace("@@@imagepath", getattr(coord_cfg, "COORDINATOR_PWC_STATIC_IMAGE_PATH", "."))
            msg_unicode = msg_unicode.replace("@@@webface", getattr(coord_cfg, "COORDINATOR_PWC_WEBFACE", "http://127.0.0.1:88/pwc"))
            msg_utf8 = msg_unicode.encode("utf8")
            return msg_utf8
        except:
            catch()
            warn("fail opening message template file %r",  filename)
            PARTS = self.DEFAULT_MESSAGES.get(msg_part, {})
            return PARTS.get(msg_type, "")

    # -------------------------------------------------------------------------------------------------------
    def generateConfirmToken(self, pwc, message_type="confirm"):
        pwc.confirm_token = randomMD5()
        # сохраняем confirm_token + auid в базу
        self.I.SQL.pwcPostRegister( pwc.email_md5, pwc.auid, pwc.confirm_token )
        if getattr(coord_cfg, 'COORDINATOR_PWC_CONFIRM', True):
            # отсылаем письмо
            self.sendConfirmEmail(pwc, message_type)

    # -------------------------------------------------------------------------------------------------------
    def convertToUtf8(self, text):
        if type(text) is not unicode:
            return unicode(text, 'utf8')
        return text

    # -------------------------------------------------------------------------------------------------------
    def sendConfirmEmail(self, pwc, message_type="confirm"):
        activation_params = "action=pwc_confirm_pretty&snuid=%s&confirm=%s&locale=%s" % (pwc.email_md5, pwc.confirm_token, self.locale)
        if not hasattr(self, 'pwc_snuid') and pwc.pwc_snuid:
            self.pwc_snuid = pwc.pwc_snuid

        if not hasattr(self, 'pwd') and pwc.secret:
            self.pwd = pwc.secret

        change_pwd_params = "action=pwc_change_pwd_link&snuid=%s&pwc_snuid=%s&token=%s&locale=%s" % (pwc.email_md5,
                                                                                                     self.pwc_snuid,
                                                                                                     self.pwd,
                                                                                                 self.locale)
        debug("sendConfirmEmail change_pwd_params %r", change_pwd_params)
        msg_template = self.importLocaleMessagePart(message_type, "body")
        msg_title = self.importLocaleMessagePart(message_type, "title")
        msg_plain = self.importLocaleMessagePart(message_type, "plain")

        # заменяем параметры
        debug("msg_template: %r\n msg_template class: %s", msg_template, msg_template.__class__)
        msg_body = self.convertToUtf8(msg_template)
        msg_body = msg_body.replace("@@@acc", pwc.email)
        msg_body = msg_body.replace("@@@params", activation_params)
        msg_body = msg_body.replace("@@@pass_params", change_pwd_params)

        msg_plain = self.convertToUtf8(msg_plain)
        msg_plain = msg_plain.replace("@@@acc", pwc.email)
        msg_plain = msg_plain.replace("@@@params", activation_params)
        msg_plain = msg_plain.replace("@@@pass_params", change_pwd_params)

        if message_type == "confirm":
            days = str(getattr(cfg, "PWC_ACTIVATION_DAYS", 2))
            msg_body = msg_body.replace("@@@activation_days", days)
            msg_plain = msg_plain.replace("@@@activation_days", days)

        msg_body_utf8 = msg_body.encode("utf8")
        msg_plain_utf8 = msg_plain.encode("utf8")

        try:
            msg_body = msg_body_utf8
        except:
            catch()
        # и отправляем юзеру по почте
        self.I.SMTP.sendMail( pwc.email, msg_title, msg_body, msg_plain_utf8, auid=pwc.auid, callback=onSendMailCallback )

    def sendMessageAboutBruteForce(self, pwc, message_type="bruteforce_msg"):
        if not hasattr(self, 'pwc_snuid') and pwc.pwc_snuid:
            self.pwc_snuid = pwc.pwc_snuid

        if not hasattr(self, 'pwd') and pwc.secret:
            self.pwd = pwc.secret

        msg_template = self.importLocaleMessagePart(message_type, "body")
        msg_title = self.importLocaleMessagePart(message_type, "title")
        msg_plain = self.importLocaleMessagePart(message_type, "plain")

        # заменяем параметры
        debug("msg_template: %r\n msg_template class: %s", msg_template, msg_template.__class__)
        msg_body = self.convertToUtf8(msg_template)
        #msg_body = msg_body.replace("@@@acc", pwc.email)
        #msg_body = msg_body.replace("@@@params", activation_params)
        #msg_body = msg_body.replace("@@@pass_params", change_pwd_params)

        msg_plain = self.convertToUtf8(msg_plain)
        #msg_plain = msg_plain.replace("@@@acc", pwc.email)
        #msg_plain = msg_plain.replace("@@@params", activation_params)
        #msg_plain = msg_plain.replace("@@@pass_params", change_pwd_params)

        msg_body_utf8 = msg_body.encode("utf8")
        msg_plain_utf8 = msg_plain.encode("utf8")

        try:
            msg_body = msg_body_utf8
        except:
            catch()
        # и отправляем юзеру по почте
        self.I.SMTP.sendMail( pwc.email, msg_title, msg_body, msg_plain_utf8, auid=pwc.auid, callback=onSendMailCallback )


    # --------------------------------------------------------------------------------------------------------
    def checkPwcGetReply(self, sql_reply):
        info("%s.onPwcGet sql reply: %s" % (self.action, sql_reply))
        try:
            # достаем данные аккаунта
            result = sql_reply["r"][0]
            self.pwc = ClassDict( email=result.email, secret=result.pwd_md5, auid=tolong(result.auid), gender=toint(result.gender), email_md5=self.snuid,
                pwc_snuid=result.pwc_snuid, ip=result.ip, birthdate=result.birthdate, confirm_token=result.confirm, ts_confirm=result.ts_confirm, active=result.active,
                ts_resend=result.ts_resend, ts_reset_pwd=result.ts_reset_pwd )

            # проверим подпись (запрос должен быть подписан старым pwd_md5)
            params = self.getParam('_params',{}) or self.getFlatParams()
            info("%s params: %s" % (self.action, params))
            if checkParamsSignature( params, secret=self.pwc.secret ):
                # все ок, подпись совпала
                return True
            else:
                self.response["error"] = "bad signature"
                self.response["ec"] = EC.PWC_BAD_SIGNATURE
        except:
            ##catch()
            warn("bad pwc sql reply: %s" % sql_reply)
            self.response["error"] = "no such pw connect user"
            self.response["ec"] = EC.PWC_BAD_USER
        # fail:
        self.fin()

## -------------------------------------------------------------------------------------------------------
## -------------------------------------------------------------------------------------------------------

class PWCRegisterAction( PWCBase ):
    """ pwc_register """
    @action_timing
    def onStart(self):
        if self.checkValidParam("email"):
            if self.checkValidParam("pwd"):
                # попробуем отконвертировать в unicode из разрешенных входных кодировок
                decoded = 0
                for encoding in self.EMAIL_ENCODINGS:
                    try:
                        self.email_unicode = unicode( self.email, encoding )
                        decoded = 1
                        self.email_encoding = encoding
                        break # видимо, получилось
                    except Exception:
                        pass

                if decoded:
                    self.email_unicode = self.email_unicode.lower()
                    if (self.email_unicode.find("@") > 0) and (self.email_unicode.find(".") > 0):
                        if len(self.email_unicode) in self.EMAIL_LENGTH:
                            if len(self.pwd) == CC.MD5_LENGTH:
                                if not re.search( CC.MD5_MASK, self.pwd ):
                                    # OK, проверки аргументов прошли
                                    self.remote_ip = ''
                                    try:
                                        # потенциальный облом, при каких-нибудь хитрых редиректах, где не будет правильных headers?
                                        self.remote_ip = self.request.request.headers.get("X-Real-IP", "")
                                    except:
                                        pass

                                    self.hostid = self.getParam('hostid', '')
                                    self.muid = self.getParam('muid', '')
                                    self.ruid = self.getParam('ruid', '')
                                    self.gender = toint( self.getParam('gender', 0) )
                                    self.birthdate = toint( self.getParam('birthdate', 0) )
                                    self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()

                                    # чтобы поддержать смену email, придется выдавать собственные snuid для PWC-юзеров
                                    self.pwc_snuid = self.I.WS.nextInt64GUID( "pwc_snuid" )
                                    self.response["pwc_snuid"] = str(self.pwc_snuid) # ланчеровский JavaScript не съест int64, так что строкой

                                    self.geolocation, self.geo_info = parseGeoLocation(self.I.GEO, self.pwc_snuid, self.remote_ip)

                                    self.I.SQL.pwcRegister( self.email_unicode, self.pwc_snuid, self.pwd, self.gender, self.remote_ip, \
                                        self.birthdate, callback=self.onSqlPwcRegisterReply )
                                    return
                                    #------

                                else:
                                    self.response["error"] = "bad pwd digest"
                                    self.response["ec"] = EC.PWC_BAD_PWD_DIGEST
                            else:
                                self.response["error"] = "bad pwd digest length %d" % len(self.pwd)
                                self.response["ec"] = EC.PWC_BAD_PWD_DIGEST
                        else:
                            self.response["error"] = "bad email length %d (should be in range %s)" % ( len(self.email_unicode), self.EMAIL_LENGTH )
                            self.response["ec"] = EC.PWC_BAD_EMAIL_LENGTH
                    else:
                        self.response["error"] = "doesn't look like email"
                        self.response["ec"] = EC.PWC_BAD_EMAIL
                else:
                    self.response["error"] = "can't decode email (bad encoding? accepting following encodings: %s)" % self.EMAIL_ENCODINGS
                    self.response["ec"] = EC.PWC_CANT_DECODE_EMAIL
        #fail--
        self.fin()

    #------------------------------------------------------------------------------------
    def getReferral(self):
        return '%s/%s' % (self.locale, self.geolocation)

    # -------------------------------------------------------------------------------------------------------
    def onSqlPwcRegisterReply(self, sql_reply):
        info("onSqlPwcRegisterReply: %s" % sql_reply)
        if sql_reply and sql_reply.get("r") and sql_reply.get("r")[0]:

            self.email_utf8 = self.email_unicode.encode("utf8")
            self.email_md5 = md5( self.email_utf8 )
            self.I.AGG.pwcAggRegister( self.pwc_snuid, callback=self.onAggregatorPwcRegisterReply, referral = self.getReferral(), ruid=self.ruid )
            return
            #------
        else:
            self.response["error"] = "bad sql register reply"
            self.response["ec"] = EC.PWC_BAD_SQL_REGISTER
            try:

                if self.request.pretty:
                    self.response["sql_error"] = sql_reply.get("ex") or "unknown sql error"
            except:
                pass
        #fail--
        self.fin()

    # -------------------------------------------------------------------------------------------------------
    def onAggregatorPwcRegisterReply(self, agg_reply):
        info("onAggregatorPwcRegisterReply: %s" % agg_reply)
        if agg_reply and agg_reply.get("error", -1) == 0:
            self.auid = tolong( agg_reply.get("auid", 0) )
            self.pwc = ClassDict( email=self.email_unicode, email_md5=self.email_md5, auid=self.auid)
            self.generateConfirmToken( self.pwc, message_type="confirm" )

            self.I.STATS.addSocialRegister( str(self.hostid), str(self.auid), CC.PWCONNECT_AGGREGATOR_SNID, str(self.pwc_snuid), str(self.muid), str(self.ruid) )

            self.I.AGG.setProperty( self.auid, 'reg', 1 ) # и отмечаем, что событие регистрации отправлено
            # для корректной работы веб-сервисов нужно, чтобы у свежесозданного pwc-аккаунта в аггрегаторе сразу было проставлено свойство fsn=pwc
            self.I.AGG.setProperty( self.auid, 'fsn', CC.PWCONNECT_AGGREGATOR_SNID, self.onAggregatorSave )
            return
        else:
            self.response["error"] = "bad aggregator register reply"
            self.response["ec"] = EC.PWC_BAD_SA_REGISTER
            self.response["agg_ec"] = agg_reply.get("error", -1)
            self.response["agg_message"] = agg_reply.get("message", "")

            # ---------------------------------------------------------------
            # TEST: на локале, где не работает соц.аггрегатор, выдаем фейковые auid-ы
            if getattr(cfg, "PWC_ALLOW_FAKE_AUIDS", 0):
                auid_64 = self.I.WS.nextInt64GUID( "pwc_auid" ) # пока выдаем тестовый auid в любом случае, даже если аггрегатор (предсказуемо) шлет нас на
                self.auid = self.I.WS.repackGUID64to20by12( auid_64 ) # выдаем фейковый 32-битный auid
                self.pwc = ClassDict( email=self.email_unicode, email_md5=self.email_md5, auid=self.auid )
                self.generateConfirmToken( self.pwc, message_type="confirm" )
                self.response["auid"] = str(self.auid) # ланчеровский JavaScript не съест int64, так что строкой
                self.response["ok"] = 1
                self.response.pop("ec", 0)
            # ---------------------------------------------------------------

        #fail--
        self.fin()

    def onAggregatorSave(self, agg_reply):
        self.response["auid"] = str(self.auid) # ланчеровский JavaScript не съест int64, так что строкой
        self.response["ok"] = 1
        self.fin()

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class PWResetPasswordLinkAction( PWCBase ):
    """ юзер приходит с email_md5, мы даем ему линк на смену пароля """
    def onStart(self):
        if self.checkValidParam("snuid"):
            if len(self.snuid) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.snuid)):
                self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()

                # достаем из mysql секретный ключ для данного аккаунта
                return self.I.SQL.pwcGet( self.snuid, callback=self.onPwcGet )

            else:
                self.response["error"] = "bad snuid mask"
                self.response["ec"] = EC.PWC_BAD_SNUID_MASK
        #fail:
        self.fin()

    #-------------------------------------------------------------------------------------
    def onPwcGet(self, sql_reply):
        info("PWResetPasswordLinkAction.onPwcGet sql reply: %s", sql_reply)
        try:
            # достаем данные аккаунта
            result = sql_reply["r"][0]
            self.pwc = ClassDict( email=result.email, secret=result.pwd_md5, pwc_snuid=result.pwc_snuid, auid=tolong(result.auid), gender=toint(result.gender), \
                ts_reset_pwd=result.ts_reset_pwd )

            now = toint( time.time() )
            next_reset_seconds = self.pwc.ts_reset_pwd + coord_cfg.COORDINATOR_PWC_RESET_PWD_PERIOD - now
            if next_reset_seconds < 0:
                # сохраняем в mysql новый timestamp
                self.I.SQL.pwcUpdateResetPwdTimestamp( self.snuid, callback=None )

                change_pwd_params = "action=pwc_change_pwd_link&snuid=%s&pwc_snuid=%s&token=%s&locale=%s" % (self.snuid,
                                                                                                             self.pwc.pwc_snuid,
                                                                                                             self.pwc.secret,
                                                                                                             self.locale
                                                                                                             )

                debug("onPwcGet change_pwd_params %r", change_pwd_params)
                ### отправляем юзеру по почте линк на смену пароля
                msg_template = self.importLocaleMessagePart("change_pwd_link", "body")
                msg_title = self.importLocaleMessagePart("change_pwd_link", "title")
                msg_plain = self.importLocaleMessagePart("change_pwd_link", "plain")

                # заменяем параметры
                msg_body = self.convertToUtf8(msg_template)
                msg_body = msg_body.replace("@@@acc", self.pwc.email)
                msg_body = msg_body.replace("@@@params", change_pwd_params)
                msg_body_utf8 = msg_body.encode("utf8")

                msg_plain = self.convertToUtf8(msg_plain)
                msg_plain = msg_plain.replace("@@@acc", self.pwc.email)
                msg_plain = msg_plain.replace("@@@params", change_pwd_params)
                msg_plain_utf8 = msg_plain.encode("utf8")

                try:
                    msg_body = msg_body_utf8
                except:
                    catch()
                self.I.SMTP.sendMail( self.pwc.email, msg_title, msg_body, msg_plain_utf8, auid=self.pwc.auid, callback=onSendMailCallback )

                self.response["ok"] = 1

            else:
                self.response["error"] = "already tried recently, next try in %s seconds" % next_reset_seconds
                self.response["ec"] = EC.PWC_RESEND_TOO_OFTEN

        except:
            ##catch()
            warn("bad pwc sql reply: %s" % sql_reply)
            self.response["error"] = "no such pw connect user"
            self.response["ec"] = EC.PWC_BAD_USER

        self.fin()

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class PWResetPasswordAction( PWCBase ):
    """ юзер приходит с email_md5, мы высылаем ему по почте новый пароль """
    def onStart(self):
        if self.checkValidParam("snuid"):
            if len(self.snuid) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.snuid)):
                self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()

                # достаем из mysql секретный ключ для данного аккаунта
                return self.I.SQL.pwcGet( self.snuid, callback=self.onPwcGet )

            else:
                self.response["error"] = "bad snuid mask"
                self.response["ec"] = EC.PWC_BAD_SNUID_MASK
        #fail:
        self.fin()

    #-------------------------------------------------------------------------------------
    def onPwcGet(self, sql_reply):
        info("PWResetPasswordAction.onPwcGet sql reply: %s" % sql_reply)
        try:
            # достаем данные аккаунта
            result = sql_reply["r"][0]
            self.pwc = ClassDict( email=result.email, secret=result.pwd_md5, pwc_snuid=result.pwc_snuid, auid=tolong(result.auid), gender=toint(result.gender), \
                ts_reset_pwd=result.ts_reset_pwd, confirm_token=result.confirm )

            now = toint( time.time() )
            next_reset_seconds = self.pwc.ts_reset_pwd + coord_cfg.COORDINATOR_PWC_RESET_PWD_PERIOD - now
            if next_reset_seconds < 0:
                # сохраняем в mysql новый timestamp
                self.I.SQL.pwcUpdateResetPwdTimestamp( self.snuid, callback=None )

                # делаем новый пароль
                self.new_pwd = randomMD5()[ :8 ] # первые 8 символов от случайного md5
                self.pwc.pwd_md5 = md5( self.new_pwd )

                info( "PWResetPasswordAction: new pass generated for email %s: pwd=%s (md5=%s)" % (self.pwc.email, self.new_pwd, self.pwc.pwd_md5) )

                ### сохраняем в mysql
                self.I.SQL.pwcUpdatePwd( self.snuid, self.pwc.pwd_md5, self.pwc.pwc_snuid, callback=self.onPwcUpdatePwd )
                return
            else:
                self.response["error"] = "already tried recently, next try in %s seconds" % next_reset_seconds
                self.response["ec"] = EC.PWC_RESEND_TOO_OFTEN

        except:
            ##catch()
            warn("bad pwc sql reply: %s" % sql_reply)
            self.response["error"] = "no such pw connect user"
            self.response["ec"] = EC.PWC_BAD_USER
            #fail
        self.fin()


    #-------------------------------------------------------------------------------------
    @sql_callback
    def onPwcUpdatePwd(self, sql_reply):
        # случай фейла (ответ sql_reply пустой) пусть обрабатывает декоратор, мы имеем дело только с валидным sql_reply["r"]
        ### отправляем новый пароль юзеру по почте
        msg_header = self.importLocaleMessagePart("all", "header")
        msg_footer = self.importLocaleMessagePart("all", "footer")
        msg_template = self.importLocaleMessagePart("reset_pwd", "body")
        msg_title = self.importLocaleMessagePart("reset_pwd", "title")
        msg_plain = self.importLocaleMessagePart("reset_pwd", "plain")

        # заменяем параметры
        msg_body = self.convertToUtf8(msg_template)
        msg_body = msg_body.replace("@@@acc", self.pwc.email)
        msg_body = msg_body.replace("@@@pwd", self.new_pwd)
        msg_body_utf8 = msg_body.encode("utf8")

        msg_plain = self.convertToUtf8(msg_plain)
        msg_plain = msg_plain.replace("@@@acc", self.pwc.email)
        msg_plain = msg_plain.replace("@@@pwd", self.new_pwd)
        msg_plain_utf8 = msg_plain.encode("utf8")

        try:
            msg_body = msg_header + msg_body_utf8 + msg_footer
        except:
            catch()
        self.I.SMTP.sendMail( self.pwc.email, msg_title, msg_body, msg_plain_utf8, auid=self.pwc.auid, callback=onSendMailCallback )

        self.response["ok"] = 1
        self.fin()

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class PWChangePasswordAction( PWCBase ):
    action = "pwc_change_pwd"
    """ юзер приходит с email_md5 и новым паролем; просто апдейтим пароль в mysql """
    def onStart(self):
        if self.checkValidParam("snuid"):
            if self.checkValidParam("pwd"):
                if len(self.snuid) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.snuid)):
                    if len(self.pwd) == CC.MD5_LENGTH:
                        if not re.search( CC.MD5_MASK, self.pwd ):
                            self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()
                            # достаем из mysql секретный ключ для данного аккаунта
                            return self.I.SQL.pwcGet( self.snuid, callback=self.onPwcGet )
                        else:
                            self.response["error"] = "bad pwd digest"
                            self.response["ec"] = EC.PWC_BAD_PWD_DIGEST
                    else:
                        self.response["error"] = "bad pwd digest length %d" % len(self.pwd)
                        self.response["ec"] = EC.PWC_BAD_PWD_DIGEST
                else:
                    self.response["error"] = "bad snuid mask"
                    self.response["ec"] = EC.PWC_BAD_SNUID_MASK
        #fail:
        self.fin()

    #-------------------------------------------------------------------------------------
    def onPwcGet(self, sql_reply):
        if self.checkPwcGetReply(sql_reply):
            # все ок, принимаем новый пароль и прописываем в mysql
            info( "PWChangePasswordAction: new pass accepted for email %s (new pwd md5=%s)" % (self.pwc.email, self.pwd) )

            ### сохраняем в mysql
            self.I.SQL.pwcUpdatePwd( self.snuid, self.pwd, self.pwc.pwc_snuid, callback=self.onPwcUpdatePwd )

    #-------------------------------------------------------------------------------------
    @sql_callback
    def onPwcUpdatePwd(self, sql_reply):
        # случай фейла (ответ sql_reply пустой) пусть обрабатывает декоратор, мы имеем дело только с валидным sql_reply["r"]
        self.response["ok"] = 1
        self.fin()

## ---------------------------------------------------------------------------------------------
## ----------------------------------------
class PWChangePasswordLinkAction( PWCBase ):
    action = "pwc_change_pwd_link"
    """ юзер приходит с email_md5, token и новым паролем; просто апдейтим пароль в mysql """
    def onStart(self):
        debug("PWChangePasswordLinkAction arguments: %r", self.arguments)
        if self.checkValidParam("snuid"):
            if self.checkValidParam("pwd"):
                if len(self.snuid) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.snuid)):
                    if len(self.pwd) == CC.MD5_LENGTH:
                        if not re.search( CC.MD5_MASK, self.pwd ):
                            self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()
                            # достаем из mysql секретный ключ для данного аккаунта
                            return self.I.SQL.pwcGet( self.snuid, callback=self.onPwcGet )
                        else:
                            self.response["error"] = "bad pwd digest"
                            self.response["ec"] = EC.PWC_BAD_PWD_DIGEST
                    else:
                        self.response["error"] = "bad pwd digest length %d" % len(self.pwd)
                        self.response["ec"] = EC.PWC_BAD_PWD_DIGEST
                else:
                    self.response["error"] = "bad snuid mask"
                    self.response["ec"] = EC.PWC_BAD_SNUID_MASK
        #fail:
        self.fin()

    #-------------------------------------------------------------------------------------
    def onPwcGet(self, sql_reply):
        debug("PWChangePasswordLinkAction.onPwcGet sql_reply %r", sql_reply)
        try:
            # достаем данные аккаунта
            result = sql_reply["r"][0]
            self.pwc = ClassDict( email=result.email, secret=result.pwd_md5, pwc_snuid=result.pwc_snuid )
            # проверим подпись (запрос должен быть подписан старым pwd_md5)
            params = self.getParam('_params',{}) or self.getFlatParams()
            info("pwc_change_pwd_link action - %s params: %s", self.action, params)
            if not checkParamsSignature( params, secret=self.pwc.secret ):
                self.response["error"] = "bad signature"
                self.response["ec"] = EC.PWC_BAD_SIGNATURE
                self.fin()
                return

            # все ок, принимаем новый пароль и прописываем в mysql
            info( "PWChangePasswordActionLink: new pass accepted for email %s (new pwd md5=%s)", self.pwc.email, self.pwc.secret)
            ### сохраняем в mysql
            self.I.SQL.pwcUpdatePwd( self.snuid, self.pwd, self.pwc.pwc_snuid, callback=self.onPwcUpdatePwd )
        except:
            catch()
            self.fin()

    #-------------------------------------------------------------------------------------
    @sql_callback
    def onPwcUpdatePwd(self, sql_reply):
        # случай фейла (ответ sql_reply пустой) пусть обрабатывает декоратор, мы имеем дело только с валидным sql_reply["r"]
        self.response["ok"] = 1
        self.fin()

## ---------------------------------------------------------------------------------------------

class PWRetryConfirmAction( PWCBase ):
    action = "pwc_resend_confirm"
    """ юзер просит прислать ему еще один confirm token (видимо, проипал) """
    def onStart(self):
        if self.checkValidParam("snuid"):
            if len(self.snuid) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.snuid)):
                self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()

                # достаем из mysql секретный ключ для данного аккаунта
                return self.I.SQL.pwcGet( self.snuid, callback=self.onPwcGet )
            else:
                self.response["error"] = "bad snuid mask"
                self.response["ec"] = EC.PWC_BAD_SNUID_MASK
        #fail:
        self.fin()

    #-------------------------------------------------------------------------------------
    def onPwcGet(self, sql_reply):
        if self.checkPwcGetReply(sql_reply):
            now = toint( time.time() )
            next_retry_seconds = self.pwc.ts_resend + coord_cfg.COORDINATOR_PWC_RETRY_CONFIRM_PERIOD - now
            if next_retry_seconds < 0:
                # все ок, высылаем токен заново:
                self.sendConfirmEmail( self.pwc, message_type="confirm" )
                info( "PWRetryConfirmAction: confirm token resent for email %s: confirm=%s" % (self.pwc.email, self.pwc.confirm_token) )
                # сохраняем в mysql новый timestamp
                self.I.SQL.pwcUpdateResendTimestamp( self.snuid, callback=None )
                self.response["ok"] = 1
            else:
                self.response["error"] = "already tried recently, next try in %s seconds" % next_retry_seconds
                self.response["ec"] = EC.PWC_RESEND_TOO_OFTEN
            self.fin()


## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

class PWCChangeEmailAction( PWCBase ):
    action = "pwc_change_email"
    debug = True
    """ pwc_change_email """
    def onStart(self):
        if self.checkValidParam("new_email"):
            # попробуем отконвертировать в unicode из разрешенных входных кодировок
            decoded = 0
            for encoding in self.EMAIL_ENCODINGS:
                try:
                    self.email_unicode = unicode( self.new_email, encoding )
                    decoded = 1
                    self.email_encoding = encoding
                    break # видимо, получилось
                except:
                    pass

            if decoded:
                self.email_unicode = self.email_unicode.lower()
                if (self.email_unicode.find("@") > 0) and (self.email_unicode.find(".") > 0):
                    if len(self.email_unicode) in self.EMAIL_LENGTH:
                        # ок, с email всё ок; пошли разбираться с реквизитами и подписью
                        if self.checkValidParam("snuid"):
                            if len(self.snuid) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.snuid)):
                                self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()

                                # достаем из mysql секретный ключ для данного аккаунта
                                return self.I.SQL.pwcGet( self.snuid, callback=self.onPwcGet )

                            else:
                                self.response["error"] = "bad snuid mask"
                                self.response["ec"] = EC.PWC_BAD_SNUID_MASK
                    else:
                        self.response["error"] = "bad email length %d (should be in range %s)" % len(self.email_unicode)
                        self.response["ec"] = EC.PWC_BAD_EMAIL_LENGTH
                else:
                    self.response["error"] = "doesn't look like email"
                    self.response["ec"] = EC.PWC_BAD_EMAIL
            else:
                self.response["error"] = "can't decode email (bad encoding? accepting following encodings: %s)" % self.EMAIL_ENCODINGS
                self.response["ec"] = EC.PWC_CANT_DECODE_EMAIL

        #fail--
        self.fin()

    def onPwcGet(self, sql_reply):
        if self.checkPwcGetReply(sql_reply):
            self.email_utf8 = self.email_unicode.encode("utf8")
            self.email_md5 = md5( self.email_utf8 )
            self.I.SQL.pwcChangeEmail( self.pwc.pwc_snuid, self.email_unicode, self.pwc.email_md5, self.email_md5, self.pwc, callback=self.onChangeEmail )

    @sql_callback
    # случай фейла (ответ sql_reply пустой) пусть обрабатывает декоратор, мы имеем дело только с валидным sql_reply["r"]
    def onChangeEmail(self, sql_reply):
        self.pwc.email = self.email_unicode
        self.pwc.email_md5 = self.email_md5
        self.generateConfirmToken( self.pwc, message_type="confirm" ) # нужно выслать новый confirm token на новый email
        self.response["ok"] = 1
        self.fin()


class PWCUser:

    def __init__(self):
        self.pwd_md5 = None
        self.auid = 0
        self.pwc_snuid = 0
        self.gender = 0
        self.active = False
        self.ts_confirm = time.time()
        self.ts_resend = time.time()
        self.birthdate = time.time()
        self.email = ''

    def toJson(self):
        data = {
            'pwd_md5' : self.pwd_md5,
            'auid' : self.auid,
            'pwc_snuid' : self.pwc_snuid,
            'gender' : self.gender,
            'active' : self.active,
            'ts_confirm' : self.ts_confirm,
            'ts_resend' : self.ts_resend,
            'ts_reset_pwd' : self.ts_reset_pwd,
            'birthdate' : self.birthdate,
            'email' : self.email,
        }
        return json.dumps(data)

    def fromJson(self, data):
        for name, value in data.items():
            self.__dict__[name] = value

class PWConnectLoadAction( SubAction ):

    """ достаем из mysql данные пользователя, шифруем, отправляем наружу"""
    @action_timing
    def onStart(self):

        if self.checkValidParam("email_md5"):
            # чтобы после смены пароля не обламывалось, давайте каждый раз брать свежие данные из mysql
            return self.I.SQL.pwcGet( self.email_md5, callback=self.onPwcGetFromSql )
        #fail:
        self.fin()

    @action_timing
    def onPwcGetFromSql(self, sql_reply):
        info("onPwcGetFromSql sql reply: %s" % sql_reply)
        try:
            results = sql_reply["r"]
            if results:
                self.processReply(results[0])
            else:
                warn("empty pwc sql reply for query %r" % sql_reply.get('s'))
                self.response["error"] = "no such pw connect user"
                self.response["ec"] = EC.PWC_BAD_USER
        except:
            catch()
            warn("bad pwc sql reply: %s" % sql_reply)
            self.response["error"] = "no such pw connect user"
            self.response["ec"] = EC.PWC_BAD_USER
        #fail
        self.fin()

    def processReply(self, result):
        user = PWCUser()
        user.pwd_md5 = result.pwd_md5
        user.auid = tolong(result.auid)
        user.pwc_snuid = tolong(result.pwc_snuid)
        user.gender = toint(result.gender)
        user.active = result.active
        user.ts_confirm = result.ts_confirm
        user.ts_resend = result.ts_resend
        user.ts_reset_pwd = result.ts_reset_pwd
        user.birthdate = result.birthdate
        user.email = result.email
        self.response["ok"] = 1
        self.response["data"] = base64.b64encode(user.toJson())

class PWConnectWhoAction( PWCBase ):
    """ достаем из mysql секретный ключ, отсылаем юзеру случайный challenge """

    @action_timing
    def onStart(self):
        info("PWConnectWhoAction.onStart request: %s",  self.request)
        if self.checkValidParam("email_md5"):
            self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()
            self.url = getattr(cfg, 'PWC_INFO_URL', None)
            info("PWConnectWhoAction.onStart (url=%r, email_md5=%s)", self.url, self.email_md5)
            self.checkIpAddress()
            return
        self.fin()

    def checkIpAddress(self):

        try:
            headers = self.request.headers
        except Exception:
            headers = self.request.request.headers
        self.remote_ip = headers.get("X-Real-IP", "")

        if self.I.Config.getMainConfig().BruteForceDefenderSettings.ENABLE:
            if self.I.Config.getMainConfig().BruteForceDefenderSettings.ENABLE_IP_CHECK and self.remote_ip:
                self.I.DATA.find(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {'remote_ip': self.remote_ip}, callback=self.onCheckIpAddress)
            else:
                self.checkBruteForcedAccount(self.email_md5, self.onStartAfterCheck)
        else:
            self.onStartAfterCheck()

    def onCheckIpAddress(self, response):
        debug("onCheckIpAddress res=%r", response)
        s = 0
        l = []
        if response and response.get("r"):
            l = response.get("r") or []
            s = sum([ x.get("count", 0) for x in l ])
            debug("onCheckIpAddress ip=%r try=%r count=%r", self.remote_ip, s, toint(l.count()) )

        _callback=functools.partial(self.onCheckBanIpAddress, s, l)
        self.I.DATA.find_one(CC.BANNED_BY_IP, CC.BANNED_BY_IP, {'_id': self.remote_ip}, callback=_callback)

    def onCheckBanIpAddress(self, s, l, response):
        debug("onCheckBanIpAddress res=%r", response)
        if response and response.get("r"):
            res = response.get("r") or []
            if res and res["timeout"] >= int(time.time()):
                self.I.DATA.find_one(CC.IP_WHITE_LIST, CC.IP_WHITE_LIST, {'_id': self.remote_ip}, callback=self.onCheckWhiteList)
                return
            elif res["timeout"] < int(time.time()):
                debug("onCheckBanIpAddress(remove record %r", self.remote_ip)
                self.I.DATA.remove(CC.BANNED_BY_IP, CC.BANNED_BY_IP, {"_id":self.remote_ip})
        else:
            lc = 0 if isinstance(l, list) else toint(l.count())
            if s >= self.I.Config.getMainConfig().BruteForceDefenderSettings.TRY_IP_COUNT or lc >= self.I.Config.getMainConfig().BruteForceDefenderSettings.TRY_IP_COUNT:
                self.I.DATA.update(CC.BANNED_BY_IP, CC.BANNED_BY_IP, {'_id': self.remote_ip},  {'accounts': toint(l.count()), 'try': s, "timeout": int(time.time()) + self.I.Config.getMainConfig().BruteForceDefenderSettings.TIME_IP_BAN },)


        self.checkBruteForcedAccount(self.email_md5, self.onStartAfterCheck)

    def onCheckWhiteList(self, response):
        debug("onCheckWhiteList res=%r", response)
        if response and response.get("r"):
            self.checkBruteForcedAccount(self.email_md5, self.onStartAfterCheck)
        else:
            self.response["error"] = "your ip was banned by server"
            self.response["ec"] = EC.PWC_ACCOUNT_BAN
            self.fin()

    def onStartAfterCheck(self, res=False):
        debug("onStartAfterCheck res=%r", res)
        if res:
            self.response["error"] = "you were banned by server"
            self.response["ec"] = EC.PWC_ACCOUNT_BAN
            self.fin()
            return

        if self.url is not None:
            return self.I.WSX.fetch(self.url, {'action' : 'pwc_load_info', 'email_md5' : self.email_md5 }, self.onPwcGetFromExternal, subrequest="", unwrap=True, timeout=20.0 )
        else:
            # чтобы после смены пароля не обламывалось, давайте каждый раз брать свежие данные из mysql
            return self.I.SQL.pwcGet( self.email_md5, callback=self.onPwcGetFromSql )
            #fail:
        #self.fin()

    @action_timing
    def onPwcGetFromExternal(self, response):
        try:
            if response:
                if response.get('ok', 0) and response.get('data', None):
                    text = base64.b64decode(response.get('data'))
                    json_data = json.loads(text)
                    user = PWCUser()
                    user.fromJson(json_data)
                    self.processReply(user)
                    return
                else:
                    warn("pwc external fetch error: %s" % response)
                    self.response["error"] = response.get('error', 'unknown error')
                    self.response["ec"] = response.get('ec', EC.PWC_BAD_USER)
            else:
                self.response["error"] = 'timeout'
                self.response["ec"] = response.get('ec', EC.PWC_BAD_USER)
        except:
            catch()
            self.response["error"] = "error parsing pwc reply"
            self.response["ec"] = EC.PWC_BAD_USER
        self.fin()

    @action_timing
    def onPwcGetFromSql(self, sql_reply):
        info("onPwcGetFromSql sql reply: %s" % sql_reply)
        try:
            results = sql_reply["r"]
            if results:
                self.processReply(results[0])
                return
            else:
                warn("empty pwc sql reply for query %r" % sql_reply.get('s'))
                self.response["error"] = "no such pw connect user"
                self.response["ec"] = EC.PWC_BAD_USER
        except:
            catch()
            warn("bad pwc sql reply: %s" % sql_reply)
            self.response["error"] = "no such pw connect user"
            self.response["ec"] = EC.PWC_BAD_USER
        self.fin()

    def processReply(self, result):
        self.token = ClassDict( secret=result.pwd_md5, auid=tolong(result.auid), pwc_snuid=tolong(result.pwc_snuid), gender=toint(result.gender), \
            active=result.active, ts_confirm=result.ts_confirm, ts_resend=result.ts_resend, ts_reset_pwd=result.ts_reset_pwd, birthdate=result.birthdate, \
            email=result.email )
        info("pwc token: %s", self.token)
        self.I.WS.pwc[ str(self.token.pwc_snuid) ] = self.token
        # проверим подпись запроса (т.е. есть ли у ланчера валидный password )
        params = self.getParam('_params',{}) or self.getFlatParams()
        info("pwc_who params: %s" % params)
        #info("self.I.WS.pwc: %s" % self.I.WS.pwc)
        if getattr(cfg, "PWC_SKIP_SIGNATURE_CHECK", 0) or checkParamsSignature( params, secret=self.token.secret ):
            now = toint(time.time())
            activation_term_left = self.token.ts_confirm + cfg.PWC_ACTIVATION_TERM - now
            self.I.DATA.remove(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {"_id":self.email_md5})
            info("processReply remove record %r after succes bruteforce checking", self.email_md5)
            if self.token.active or (activation_term_left > 0):
                if not self.token.active:
                    self.response["activation_term_left"] = activation_term_left # сколько секунд осталось до конца срока активации
                return self.reply(params)
            else:
                self.response["error"] = "pwc account activation required"
                self.response["ec"] = EC.PWC_ACTIVATION_EXPIRED
            self.fin()
        else:
            self.incBruteforcedAccCount(self.email_md5, self.onIncBruteforcedAccCount)
            return

    def checkBruteForcedAccount(self, email_md5, callback):
        if self.I.Config.getMainConfig().BruteForceDefenderSettings.ENABLE:
            _callback = functools.partial(self.onCheckBruteforcedAccount, callback)
            self.I.DATA.find_one(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {'_id': email_md5}, callback=_callback)
        else:
            callback(False)

    def onCheckBruteforcedAccount(self, callback, reply):
        debug("onCheckBruteforcedAccount %r", reply )
        if reply and reply.get("r"):
            bf_acc = reply.get("r")
            self.response["iscaptcha"] = bf_acc["count"] >= self.I.Config.getMainConfig().BruteForceDefenderSettings.FAILED_COUNT_FOR_CAPTCHA
            if bf_acc["count"] >= self.I.Config.getMainConfig().BruteForceDefenderSettings.TRY_LOGINS_COUNT and bf_acc["ban_timeout"] > time.time():
                callback(True)
                return
            elif bf_acc["ban_timeout"] <= time.time() and bf_acc["count"] >= self.I.Config.getMainConfig().BruteForceDefenderSettings.TRY_LOGINS_COUNT:
                #время истекло сбросим бан
                debug("onCheckBruteforcedAccount remove record %r", bf_acc )
                self.I.DATA.remove(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {"_id":bf_acc["_id"]})
        else:
            self.response["iscaptcha"] = False
        callback(False)
        return

    def incBruteforcedAccCount(self, email_md5, callback):
        _callback = functools.partial(self.onFindBruteforcedAccCount, email_md5, callback)
        self.I.DATA.find_one(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {'_id': email_md5}, callback=_callback)


    def onFindBruteforcedAccCount(self, email_md5, callback, reply):
        debug("onFindBruteforcedAccCount %r", reply )

        if reply and reply.get("r"):
            bf_acc = reply.get("r")
            if bf_acc["count"] + 1 >= self.I.Config.getMainConfig().BruteForceDefenderSettings.TRY_LOGINS_COUNT:
                bf_acc["ban_timeout"] = self.I.Config.getMainConfig().BruteForceDefenderSettings.LOGIN_BAN_TIME + int(time.time())
                if self.I.Config.getMainConfig().BruteForceDefenderSettings.ENABLE_SENDING_MAIL:
                    self.sendMessageAboutBruteForce(self.token)

            bf_acc["count"] += 1
            self.response["iscaptcha"] = bf_acc["count"] >= self.I.Config.getMainConfig().BruteForceDefenderSettings.FAILED_COUNT_FOR_CAPTCHA
            debug("onFindBruteforcedAccCount ban record %r", bf_acc )

            self.I.DATA.update(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {'_id': email_md5}, {'remote_ip': self.remote_ip, 'count': bf_acc["count"], 'ban_timeout': bf_acc["ban_timeout"]},  callback=callback)
        else:
            self.response["iscaptcha"] = False
            self.I.DATA.update(CC.BANNED_BY_BRUTEFORCE, CC.BANNED_BY_BRUTEFORCE, {'_id': email_md5}, {'remote_ip': self.remote_ip, 'count': 0, "ban_timeout": 0},  callback=callback)

    def onIncBruteforcedAccCount(self, response):
        info("onIncBruteforcedAccCount response: %r", response)
        if not response:
            err("Mongo call returns empty response!")
        elif 'e' in response:
            err("Mongo call returns error: %s", response)
        else:
            debug("Mongo call returns: %s", response)
        self.response["error"] = "bad signature"
        self.response["ec"] = EC.PWC_BAD_SIGNATURE
        self.fin()

    def reply(self, params):
        # нужно завести login token для sn_login
        user = User()
        user.pwconnect = 1
        user.email_md5 = self.email_md5
        user.pwc_snuid = str(self.token.pwc_snuid)
        user.auid = self.token.auid
        user.snid = CC.PWCONNECT_AGGREGATOR_SNID
        user.snuid = str(self.token.pwc_snuid)
        user.original_snid = user.snid
        user.original_snuid = user.snuid
        user.secret = self.token.secret
        user.sex = self.token.gender
        user.pwc_data = self.token
        user.muid = params.get('muid')
        user.ruid = params.get('ruid')

        # по новой моде, sn_nick для PWC должен быть первой частью email (до @)
        dog_pos = self.token.email.find("@")
        if dog_pos > 0:
            user.sn_nick = utf8convert( self.token.email[ :dog_pos ] )

        self.random_key = self.I.WS.registerLogin(str(self.token.auid), user, primary=self.getIntParam('primary', 0))
        if self.random_key is not None:
            self.token.challenge = self.random_key
            self.response["token"] = self.random_key
            self.fakeSocialInfo()
            self.response["ok"] = 1
        else:
            self.response["ec"] = EC.AUTH_REGISTER_LOGIN_FAILED
            self.response["error"] = "error registering login"
        self.fin()

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class PWConnectLoginAction( PWCBase ):
    """ проверяем, что нам пришел правильно подписанный запрос: отправленный нами ранее challenge, подписанный секретным ключом """
    @action_timing
    def onStart(self):
        if self.checkValidParam("snuid"):
            if (self.getParam("snid", "") == CC.PWCONNECT_LAUNCHER_SNID) and getattr(cfg, "PWC_SKIP_SIGNATURE_CHECK", 0):
                # специальная конфиг-опция, отключает проверку challenge и подписи
                warn("PWC_SKIP_SIGNATURE_CHECK: skipping challenge & sign checks for pwc login (snuid=%s), doing auto pwc login" % self.snuid)
                subaction = PWConnectWhoAction( dict(email_md5=[self.snuid]), self.onAutoPwcLogin, I=self.I, primary=self.getIntParam('primary', 0) )
                subaction.request = self.request
                return subaction.onStart()

            if self.checkValidParam("challenge"):
                params = self.getParam('_params',{}) or self.getFlatParams()
                info("pwc_login params: %s" % params)
                #info("self.I.WS.pwc: %s" % self.I.WS.pwc)
                info("self.snuid: %r" % self.snuid)
                self.token = self.I.WS.pwc.get( self.snuid )
                if self.token:
                    # секрет есть
                    if self.challenge == self.token.get("challenge", str(time.time())):
                        # challenge правильный
                        secret = self.token.get("secret", "")
                        if checkParamsSignature( params, secret=secret ):
                            ##self.token.pop("challenge", None) # сразу выпиливаем challenge, т.к. он одноразовый
                            return self.success()

                        else:
                            self.response["error"] = "bad signature"
                            self.response["ec"] = EC.PWC_BAD_SIGNATURE
                    else:
                        self.response["error"] = "bad challenge"
                        self.response["ec"] = EC.PWC_BAD_CHALLENGE
                else:
                    self.response["error"] = "no pw connect token"
                    self.response["ec"] = EC.PWC_NO_PWC_TOKEN
        #fail:
        self.fin()

    def onAutoPwcLogin(self, response):
        info("onAutoPwcLogin: snuid=%s, response=%s" % (self.snuid, response))
        if response and response.get("ok", 0):
            self.pwc_snuid = response.get("pwc_snuid", "")
            self.token = self.I.WS.pwc.get( self.pwc_snuid )
            return self.success()
        else:
            self.response.update( response )
            self.fin()

    def success(self):
        # подделываем "инфу из соц.сети" (благо сказать нам почти нечего: ника нет, фотки нет..)
        self.fakeSocialInfo()
        self.response["secret"] = self.token.get("secret", "")
        self.response["ok"] = 1
        self.fin()





##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class PWConfirmAction( PWCBase ):
    """ юзер приходит с confirm_token, мы активируем соотв. pwc-аккаунт """
    @action_timing
    def onStart(self):
        self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()
        if self.checkValidParam("snuid"):
            if self.checkValidParam("confirm"):
                if len(self.snuid) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.snuid)):
                    if len(self.confirm) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.confirm)):
                        # проверку на совпадение токена пусть делает mysql
                        return self.I.SQL.pwcActivate( self.snuid, self.confirm, callback=self.onSqlPwcActivate )
                    else:
                        self.response["error"] = "bad confirm mask"
                        self.response["ec"] = EC.PWC_BAD_CONFIRM_MASK
                else:
                    self.response["error"] = "bad snuid mask"
                    self.response["ec"] = EC.PWC_BAD_SNUID_MASK
        #fail:
        self.fin()

    @action_timing
    @sql_callback
    def onSqlPwcActivate(self, sql_reply):
        # случай фейла (ответ sql_reply пустой) пусть обрабатывает декоратор, мы имеем дело только с валидным sql_reply["r"]
        self.response["ok"] = 1
        self.fin()


##-------------------------------------------------------------------------------------
class PWConfirmRedirectAction( PWConfirmAction ):
    """ вместо обычного JSON-ответа делаем HTTP REDIRECT на один из указанных в конфиге адресов (ok/fail) """
    def fin(self):
        self.ok = self.response.get("ok")
        if self.ok:
            self.redirect_addr = coord_cfg.COORDINATOR_PWC_CONFIRM_OK + "?snuid=%s&locale=%s" % (self.snuid, self.locale)
        else:
            ec = self.response.get("ec", 0)
            error = self.response.get("error", "")
            self.redirect_addr = coord_cfg.COORDINATOR_PWC_CONFIRM_FAIL + "?snuid=%s&ec=%s&error=%s&locale=%s" % (self.snuid, ec, urlQuote(error), self.locale)

        # inherited
        info("PWConfirmRedirectAction: ok=%s, redirecting snuid=%s to %s" % (self.ok, self.snuid, self.redirect_addr))
        self.response["__redirect__"] = self.redirect_addr
        super(PWConfirmRedirectAction, self).fin()


##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class PWChangePasswordLinkActionExt( PWCBase ):
    """ юзер приходит с token, мы делаем HTTP REDIRECT на указанный в конфиге адрес для смены пароля """
    def fin(self):
        self.ok = self.response.get("ok")
        info("performing redirect")
        self.redirect_addr = ''
        if self.ok:
            self.redirect_addr = coord_cfg.COORDINATOR_PWC_CHANGE_PWD + "?snuid=%s&token=%s&locale=%s" % (self.snuid,
                                                                                                          self.token,
                                                                                                          self.locale)
        else:
            ec = self.response.get("ec", 0)
            error = self.response.get("error", "")
            self.redirect_addr = coord_cfg.COORDINATOR_PWC_CHANGE_PWD + "?ec=%s&error=%s&locale=%s" % (ec, urlQuote(error), self.locale)

        # inherited
        info("PWChangePasswordLinkAction: ok=%s, redirecting snuid=%s to %s", self.ok, self.snuid, self.redirect_addr)
        self.response["__redirect__"] = self.redirect_addr
        super(PWChangePasswordLinkActionExt, self).fin()

    @action_timing
    def onStart(self):
        debug("PWChangePasswordLinkActionExt.onStart arguments %r", self.arguments)
        self.locale = str(self.getParam('locale') or coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE).upper()
        if self.checkValidParam("snuid") and self.checkValidParam("pwc_snuid") and self.checkValidParam("token"):
            if len(self.snuid) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.snuid)):
                if len(self.token) == CC.MD5_LENGTH and (not re.search(CC.MD5_MASK, self.token)):
                    return self.I.SQL.pwcGet( self.snuid, callback=self.onPwcGet )
                else:
                    self.response["error"] = "bad token mask"
                    self.response["ec"] = EC.PWC_BAD_CHALLENGE
            else:
                self.response["error"] = "bad snuid mask"
                self.response["ec"] = EC.PWC_BAD_SNUID_MASK
        #fail:
        self.fin()

    @action_timing
    def onPwcGet(self, sql_reply):
        info("PWResetPasswordLinkActionExt.onPwcGet sql reply: %s", sql_reply)
        try:
            # достаем данные аккаунта
            result = sql_reply['r']
            if result:
                result = result[0]
            info("self.token: %s, result.pwd_md5: %s", self.token, result.pwd_md5)
            if self.token == result.pwd_md5:
                # все ок, подпись совпала
                self.response["ok"] = 1
            else:
                self.response["error"] = "bad signature"
                self.response["ec"] = EC.PWC_BAD_SIGNATURE
        except:
            #catch()
            warn("bad pwc sql reply: %s" % sql_reply)
            self.response["error"] = "no such pw connect user"
            self.response["ec"] = EC.PWC_BAD_USER

        self.fin()

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

SA_ERROR_GENERIC = -1
SA_ERROR_NO_SUCH_PWC_USER = 1001
SA_ERROR_BAD_SNUID_FORMAT = 1002

class PWGetInfoAction( PWCBase ):
    """ юзер приходит с pwc_snuid, мы ему отдаем email и gender (ну и на всякий случай auid)"""
    @action_timing
    def onStart(self):
        # id=<email_md5>
        self.ts_start = time.time()
        if self.checkValidParam("snuid"):
            if (not re.search(CC.MD5_MASK, self.snuid)):
                # достаем из mysql данные аккаунта
                return self.I.SQL.pwcGetByPwcSnuid( self.snuid, callback=self.onPwcGet )
            else:
                self.response["error"] = "bad snuid mask"
                self.response["ec"] = SA_ERROR_BAD_SNUID_FORMAT
        #fail:
        self.fin()

    @action_timing
    def onPwcGet(self, sql_reply):
        info("PWGetInfoAction.onPwcGet sql reply: %s" % sql_reply)
        try:
            # достаем данные аккаунта
            result = sql_reply["r"][0]

            self.response["email"] = result.email.encode("utf8") # из SQL приходит unicode
            self.response["gender"] = toint(result.gender)
            self.response["birthdate"] = toint(result.birthdate)

            self.response["ok"] = 1

        except Exception:
            ##catch()
            warn("bad pwc sql reply: %s" % sql_reply)
            self.response["error"] = "no such pw connect user"
            self.response["ec"] = SA_ERROR_NO_SUCH_PWC_USER
        #--
        self.fin()

    # -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    # конвертируем наши уютные статусы и ошибки ("ok":1, "error":STRING) в те, что положены по протоколу для Social Aggregator ("error":0/<error_code_INT>, "message":STRING)
    def fin(self):
        if self.response.get("ok"):
            self.response.pop("ok")
            self.response["error"] = 0
        else:
            error_message = self.response.get("error")
            if error_message:
                self.response["message"] = error_message
            ec = self.response.get("ec", SA_ERROR_GENERIC)
            self.response["error"] = ec

        # еще в протоколе SA есть время исполнения запроса (msec)
        self.ts_fin = time.time()
        self.response["tm"] = toint( (self.ts_fin - self.ts_start) * 1000 )

        # решительно забиваем на fin_callback; мы отвечаем не в стандартном формате сервера {"response":...}, а своим собственным JSON
        json_response = json_dumps( self.response )

        if not self.I.WS.TEST_MODE:
            # поручаем tornado IOLoop вызвать JsonHandler после того как мы вернем управление (и корректно отработают все декораторы)
            loop = tornado.ioloop.IOLoop.instance()
            _callback = functools.partial( self.request.finJsonResponse, json_response, self.response )
            loop.add_callback( _callback )
        else:
            # в тестовом режиме вызываем JsonHandler напрямую
            self.request.finJsonResponse( json_response, self.response )
