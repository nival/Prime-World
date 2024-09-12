# -*- coding: utf-8 -*-
import sys

sys.path.append('../common/py')
sys.path.append('../..')

import System.logs
import System.fsm
import System.config

import os.path
import tornado.escape
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.locale
import tornado.httpclient
import urllib
import urlparse
import json
import hashlib
import base64
import time
import random

import Network
import Network.HttpClient
from Network.SOA import Service

from logging import debug, info, error, warning

from recaptcha import RecaptchaMixin
from tornado.web import RequestHandler, asynchronous
from tornado import httpclient
from base.helpers import *


class SignupHandler(RequestHandler, RecaptchaMixin):
    def initialize(self, config):
        self.config = config

    def get(self):
        s = json.dumps({"xsrf": self.xsrf_form_html(), "url": self.recaptcha_render()})
        self.write(s)

    @asynchronous
    def post(self):
        challenge = self.get_argument('recaptcha_challenge_field', None)
        response = self.get_argument('recaptcha_response_field', None)
        _xcrf = self.get_argument('_xcrf', None)
        debug("Recaptcha fields challenge=%r : response=%r _xcrf=%r", challenge, response, _xcrf)
        self.recaptcha_validate(self._on_validate)

    def _on_validate(self, response):
        if response:
            self.write('success')
            self.finish()
            return
        self.write('failed')
        self.finish()


def gen_request_code():
    m = hashlib.md5()
    m.update(str(time.time()))
    m.update(str(random.random()))
    return m.hexdigest()


def xor_strings(value, key):
    result = ''
    for i in range(len(value)):
        result += chr(ord(value[i]) ^ ord(key[i % len(key)]))
    return result


def md5(data):
    return hashlib.md5(data).hexdigest()


def md5u(data):
    if isinstance(data, unicode):
        data = data.encode("utf8")
    return md5(data)


def EncodeToken(snuid, pwdmd5, secret, expire):
    token = str(snuid) + '%' + str(expire) + '%'
    token += md5(token + pwdmd5)
    token = xor_strings(token, secret)
    token = base64.urlsafe_b64encode(token)

    i = len(token) - 1
    while token[i] == '=' and i >= 0:
        i -= 1
    return token[:i + 1]


def DecodeToken(token, pwdmd5, secret):
    token = str(token)
    n = len(token) % 4
    if n > 0:
        token += '=' * (4 - n)
    token = base64.urlsafe_b64decode(token)
    token = xor_strings(token, secret)
    index = token.rfind('%')
    subtoken = token[:index]
    if token[index + 1:] == md5(token[:index + 1] + pwdmd5):
        _snuid, _expire = subtoken.split('%')
        try:
            snuid = int(_snuid)
        except ValueError:
            snuid = None
        try:
            expire = int(_expire)
        except ValueError:
            expire = None
            snuid = None
        return snuid, expire
    return (None, None)


def Sign(args, pwd_md5):
    data = list(args.items())

    def ZeroItem(item):
        return item[0]

    data.sort(key=ZeroItem)

    s = ''
    for name, value in data:
        s += name + str(value)
    s += pwd_md5
    return md5(s)

def ParseData(text, root=None):
    try:
        data = json.loads(text)
        debug(data)
        if not root:
            return data
        data = data.get(root, None)
        return data
    except:
        return None

class BaseHandler(tornado.web.RequestHandler):
    def initialize(self, config, http_client, cache):
        self.config = config
        self.http_client = http_client
        self.cache = cache

    def SFetch(self, url, callback):
        self.http_client.fetch(url, validate_cert=False, client_key=os.path.join(self.config.ssl_path, 'client01.key'),
                               client_cert=os.path.join(self.config.ssl_path, 'client01.crt'), callback=callback)

    def GetOAuthUrl(self):
        return self.config.pwcf_url_prefix + "/oauth"

    def _Error(self, etype, message):
        data = {
            "error": {
                "type": etype,
                "message": message,
            }
        }
        raise tornado.web.HTTPError(400, json.dumps(data, indent=4))

    def Error(self, message):
        self._Error("DataException", message)

    def OAuthError(self, message):
        self._Error("OAuthException", message)

    def get_current_user(self):
        user_json = self.get_secure_cookie("user")
        if not user_json: return None
        return tornado.escape.json_decode(user_json)

    def localize(self, s, locale):
        tmpl = None
        if isinstance(s, basestring):
            tmpl = s
        else:
            tmpl = s.get(locale, None)
            if tmpl is None:
                tmpl = s.get('<def>', None)
            if tmpl is None:
                tmpl = s
        if '%s' in tmpl:
            return tmpl % locale.lower()
        else:
            return tmpl

    def NormalizeLocale(self, locale):
        if locale and len(locale) >= 2:
            return locale[:2].upper()
        return 'EN'

    def getRequestLocale(self):
        locale = self.get_argument('locale', default="").lower()
        debug("argument locale=%r" % locale)
        if not locale:
            locale = self.get_cookie("pw_lang", default="").lower()
            debug("cookie locale=%r" % locale)

        allowed_locales = getattr(self.config, "allowed_pw_lang_dict", None) or {"ru": "ru", "en": "en", "tr": "tr",
                                                                                 "fr": "fr", "de": "de"}
        if locale and (locale in allowed_locales):
            locale = allowed_locales.get(locale)
            debug("table locale=%r" % locale)
        else:
            locale = "en"
            debug("default locale=%r" % locale)

        debug("translation self.locale.code=%r" % (self.locale.code))
        if locale != self.locale.code:
            self._locale = tornado.locale.get(locale)
            debug("switched translation self.locale.code to %r" % (self.locale.code))
        return locale

    def RedirectOnError(self, next, reason):
        params = urlparse.parse_qs(next)
        if 'redirect_uri' in params:
            redirect_uri = params['redirect_uri']
            if len(redirect_uri) > 0:
                next = redirect_uri[0]
                if next[-1] != '?':
                    next += '?'
                next += 'error_reason=' + reason
                state = params.get('state', [])
                if state:
                    next += '&state=' + state[0]
                self.redirect(next)
                return True
        return False

    def Redirect(self, uri, args):
        if uri[-1] != '?':
            uri += '?'
        uri += urllib.urlencode(args)
        self.redirect(uri)

    def Next(self, uri, args):
        index = uri.find('?')
        if index <= 0:
            uri += '?'
        if uri[-1] != '?':
            uri += '&'
        uri += urllib.urlencode(args)
        self.redirect(uri)

    def GetBool(self, name, default):
        value = self.get_argument(name, None)
        if not value:
            return default
        if value.lower() == 'true':
            return True
        if value.lower() == 'false':
            return False
        return default

    def Message(self, data, **kwargs):
        locale = self.getRequestLocale()
        logo = self.localize(self.config.links.logo, self.NormalizeLocale(locale))

        message = kwargs.get('message', None)
        message = self.locale.translate(message)
        if message and data and self.config.debug:
            kwargs['message'] = message + ' ' + str(data)
        else:
            kwargs['message'] = message
        kwargs['pwc_prefix'] = self.config.pwcf_url_prefix
        self.render('message.html', logo=logo, **kwargs)

    def Render(self, template, **kwargs):
        kwargs['pwcf_prefix'] = self.config.pwcf_url_prefix
        self.render(template, **kwargs)


    def CheckRecaptcha2(self):
        response_captcha = self.get_argument('g-recaptcha-pw', None)
        if not response_captcha:
            error("response_captcha is Null")
            return False

        str_google_post = "https://www.google.com/recaptcha/api/siteverify"
        x_real_ip = self.request.headers.get("X-Real-IP")
        remote_ip = x_real_ip or self.request.remote_ip
        post_args = {
            'secret': "6LdJNBYUAAAAAB__n_wtxMvMrg5zHlChUUQc5CPp",
            'remoteip': remote_ip,
            'response': response_captcha
        }
        http_client = httpclient.HTTPClient()
        response = http_client.fetch(str_google_post, method="POST", body=urllib.urlencode(post_args))
        debug("post to https://www.google.com/recaptcha/api/siteverify, remoteip = %s, response = %s" % (str(remote_ip), str(response_captcha)))
        if response.error:
            next = self.get_argument('next', self.GetOAuthUrl())
            reason = 'pwc_check_captcha_fail'
            if self.RedirectOnError(next, reason):
                return False
            error("check_captcha is fail: %s"%(str(response.error)))
            return False
        else:
            json_res = ParseData(response.body)
            if json_res["success"]:
                return True
            else:
                error("check_captcha is fail success != true, json_res: %s"%str(json_res))
                return False
        return False




class ChangeHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        try:
            error = self.get_argument('error')
            ec = self.get_argument('ec')
            self.Message(None, message=('password_changed_error'), next=self.GetOAuthUrl())
        except:
            pass
        locale = self.getRequestLocale()
        logo = self.localize(self.config.links.logo, self.NormalizeLocale(locale))
        debug("ChangeHandler snuid=%r token=%r logo=%r locale=%r", self.get_argument('snuid'),
              self.get_argument('token'), logo, locale)
        self.Render('changePwd.html', snuid=self.get_argument('snuid'), token=self.get_argument('token'), logo=logo,
                    locale=locale)


class DoChangeHandler(BaseHandler):
    @tornado.web.asynchronous
    def post(self):
        locale = self.getRequestLocale()
        # pwc_snuid, _ = DecodeToken(self.get_argument('token'), md5(self.get_argument('reg_passwd__')), self.config.pwc_token_secret )
        args = dict(
            action='pwc_change_pwd_link',
            snuid=self.get_argument('snuid'),
            token=self.get_argument('token'),
            pwd=md5(self.get_argument('reg_passwd__')),
            locale=self.NormalizeLocale(locale),
        )
        args['sign'] = Sign(args, self.get_argument("token"))

        url = self.config.pwc_url + "?" + urllib.urlencode(args)
        debug("DoChangeHandler url: " + url)
        self.SFetch(url, self._on_change)

    def _on_change(self, response):
        data = None
        if response and not response.error:
            data = ParseData(response.body, 'response')
            if data and data.get('ok', 0) == 1:
                self.pwd_md5 = md5(self.get_argument('reg_passwd__'))
                self.Message(None, message='password_changed_success', next=self.GetOAuthUrl())
                return
        self.Message(data, message=('password_changed_error'), next=self.GetOAuthUrl())


class DoChangePwdExtHandler(BaseHandler):
    @tornado.web.asynchronous
    def post(self):
        args = dict(
            action='pwc_change_pwd',
            snuid=self.get_argument('snuid__'),
            pwd=md5(self.get_argument('reg_passwd__')),  # TODO: remove md5
        )
        args['sign'] = Sign(args, self.get_argument("token__"))

        url = self.config.pwc_url + "?" + urllib.urlencode(args)
        debug(url)
        self.SFetch(url, self._on_change)

    def _on_change(self, response):
        data = None
        if response and not response.error:
            data = ParseData(response.body, 'response')
            if data and data.get('ok', 0) == 1:
                if self.current_user:
                    self.current_user['pwd_md5'] = md5(self.get_argument('reg_passwd__'))  # TODO: remove md5
                    self.set_secure_cookie("user", tornado.escape.json_encode(self.current_user))
                self.Message(None, message='password_changed_success', next=self.GetOAuthUrl())
                return
        self.Message(data, message='password_changed_error', next=self.GetOAuthUrl())


class ResetPwdLinkHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        if not self.current_user:
            email = ''
        else:
            email = self.current_user.get('email', '')
        next = self.get_argument('next', self.GetOAuthUrl())
        next = tornado.escape.url_unescape(next)
        locale = self.getRequestLocale()
        logo = self.localize(self.config.links.logo, self.NormalizeLocale(locale))

        self.Render('reset_pwd_link.html', logo=logo, email=email, next=next, locale=locale)


errors = {
    82: 'password_change_often',
    70: 'user_not_found',
}


class DoResetPwdLinkHandler(BaseHandler):
    @tornado.web.asynchronous
    def post(self):
        locale = self.getRequestLocale()
        args = dict(
            action='pwc_reset_pwd_link',
            snuid=md5(self.get_argument('reg_email__', '')),
            locale=self.NormalizeLocale(locale),
        )
        url = self.config.pwc_url + "?" + urllib.urlencode(args)
        debug(url)
        self.SFetch(url, self._on_change)

    def _on_change(self, response):
        data = None
        next = self.get_argument('next', self.GetOAuthUrl())
        if response and not response.error:
            data = ParseData(response.body, 'response')
            if data:
                if data.get('ok', 0) == 1:
                    self.Message(None, message='password_new_sent', next=next)  # Ссылка на смену пароля выслана
                    return
                else:
                    message = errors.get(data.get('ec', 0), None)
                    if message:
                        self.Message(None, message=message.decode('cp1251').encode('utf-8'), next=next)
                        return
        self.Message(data, message='password_changed_error', next=next)


class ChangeEmailHandler(BaseHandler):
    @tornado.web.authenticated
    @tornado.web.asynchronous
    def get(self):
        if not self.current_user:
            self.redirect(self.GetOAuthUrl())
            return
        self.Render('changeEmail.html')


class DoChangeEmailHandler(BaseHandler):
    @tornado.web.authenticated
    @tornado.web.asynchronous
    def post(self):
        if not self.current_user:
            self.redirect(self.GetOAuthUrl())
            return
        locale = self.getRequestLocale()
        args = dict(
            action='pwc_change_email',
            snuid=self.current_user['email_md5'],
            new_email=self.get_argument('reg_email__'),
            locale=self.NormalizeLocale(locale),
        )
        args['sign'] = Sign(args, md5(self.get_argument("reg_passwd__")))  # TODO: remove md5

        url = self.config.pwc_url + "?" + urllib.urlencode(args)
        debug(url)
        self.SFetch(url, self._on_change)

    def _on_change(self, response):
        data = None
        if response and not response.error:
            data = ParseData(response.body, 'response')
            if data and data.get('ok', 0) == 1:
                self.current_user['email'] = self.get_argument('reg_email__')
                self.current_user['email_md5'] = md5(self.current_user['email'])
                self.set_secure_cookie("user", tornado.escape.json_encode(self.current_user))
                self.Message(None, message='email_changed_success', next=self.GetOAuthUrl())
                return
        self.Message(data, message='email_changed_error', next=self.GetOAuthUrl())


class ResetHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        if not self.current_user:
            email = ''
        else:
            email = self.current_user.get('email', '')
        locale = self.getRequestLocale()
        self.Render('reset.html', email=email)


class DoResetHandler(BaseHandler):
    @tornado.web.asynchronous
    def post(self):
        args = dict(
            action='pwc_reset_pwd',
            snuid=md5(self.get_argument('reg_email__')),
        )
        url = self.config.pwc_url + "?" + urllib.urlencode(args)
        debug(url)
        self.SFetch(url, self._on_recover)

    def _on_recover(self, response):
        data = None
        if response and not response.error:
            data = ParseData(response.body, 'response')
            if data and data.get('ok', 0) == 1:
                self.Message(None, message='password_random_sent', next=self.GetOAuthUrl())
                return
        self.Message(data, message='password_random_error', next=self.GetOAuthUrl())


class RegisterHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        locale = self.getRequestLocale()
        eula = self.localize(self.config.links.eula, self.NormalizeLocale(locale))
        support = self.localize(self.config.links.support, self.NormalizeLocale(locale))
        logo = self.localize(self.config.links.logo, self.NormalizeLocale(locale))

        next = self.get_argument('next', self.GetOAuthUrl())
        next = tornado.escape.url_unescape(next)
        self.Render('register.html', logo=logo, next=next, eula=eula, support=support, locale=locale)


class GetUserInfoHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        access_token = self.get_argument('access_token', None)
        if access_token != None:
            pwc_snuid, expire = DecodeToken(access_token, self.config.pwc_token_password_md5,
                                            self.config.pwc_token_secret)
            if pwc_snuid:
                if expire == 0 or time.time() < expire:
                    args = dict(
                        action='pwc_get_info',
                        snuid=pwc_snuid,
                    )
                    url = self.config.pw_url + "?" + urllib.urlencode(args)
                    self.pwc_snuid = pwc_snuid
                    debug(url)
                    self.http_client.fetch(url, self._on_getuserinfo)
                else:
                    self.Error("Access token expired")
            else:
                self.Error("Invalid access token")
        else:
            self.Error("Access token not defined")

    def _on_getuserinfo(self, response):
        if response and not response.error:
            data = ParseData(response.body)
            if data and data.get('error', 1) == 0:
                result = {
                    'pwid': self.pwc_snuid,
                    'email': data['email'],
                    'gender': data['gender'],
                    'birthdate': data['birthdate'],
                }
                self.finish(json.dumps(result))
                return
        self.Error("User info retrieve failed")


class DoHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        action = self.get_argument('action', None)
        if action == 'pwc_confirm':
            snuid = self.get_argument('snuid', None)
            confirm = self.get_argument('confirm', None)
            if snuid or confirm:
                locale = self.getRequestLocale()
                args = dict(
                    action='pwc_confirm',
                    snuid=snuid,
                    confirm=confirm,
                    locale=self.NormalizeLocale(locale),
                )
                url = self.config.pwc_url + "?" + urllib.urlencode(args)
                debug(url)
                self.SFetch(url, self._on_confirm)
            else:
                self.Error("Wrong confirmation params")

        elif action == 'pwc_change_pwd':
            snuid = self.get_argument('snuid', None)
            pwc_snuid = self.get_argument('pwc_snuid', None)
            token = self.get_argument('token', None)
            if snuid != None and pwc_snuid != None and token != None:
                args = dict(
                    action='pwc_get_info',
                    snuid=pwc_snuid,
                )
                url = self.config.pw_url + "?" + urllib.urlencode(args)
                debug(url)
                self.http_client.fetch(url, self._on_getuserinfo)
            else:
                self.Error("Wrong params defined")
        elif action == 'getdata':
            data = {
                'cache': self.cache.GetData(),
            }
            self.write(json.dumps(data, indent=4))
            self.finish()
        else:
            self.Error("Unknown action")

    def _on_getuserinfo(self, response):
        if response and not response.error:
            data = ParseData(response.body)
            if data and data.get('error', 1) == 0:
                self.Render('changePwdExt.html', email=data['email'], token=self.get_argument('token'),
                            snuid=self.get_argument('snuid'))
                return
        self.Error("User info retrieve failed")

    def _on_confirm(self, response):
        if response and not response.error:
            data = ParseData(response.body, 'response')
            if data and data.get('ok', 0) == 1:
                self.Message(None, message='email_confirm_success', next=self.GetOAuthUrl())
                return
        self.Message(data, message='email_confirm_error', next=self.GetOAuthUrl())


class DoRegisterHandler(BaseHandler):
    @tornado.web.asynchronous
    def post(self):
        locale = self.getRequestLocale()
        if not self.CheckRecaptcha2():
            next = self.get_argument('next', self.GetOAuthUrl())
            self.Message(None, message='registration_error', next=next)
            return
        self.reg_email = self.get_argument('reg_email__').encode("utf8")
        args = dict(
            action='pwc_register',
            email=self.reg_email,
            pwd=self.get_argument('reg_passwd__'),
            gender=1,  # PF-85882 - don't ask gender during registration, set male by default
            birthdate=self.get_argument('birth_date'),
            locale=self.NormalizeLocale(locale),
        )
        muid = self.get_argument('muid', None)
        if muid is None:
            if self.config.tracking is not None and self.config.tracking.key_name is not None:
                muid = self.get_cookie(self.config.tracking.key_name, None)
        if muid is not None:
            args['muid'] = muid

        ruid = self.get_argument('ruid', None)
        if ruid is None:
            if self.config.tracking is not None and self.config.tracking.key_name is not None:
                ruid = self.get_cookie(self.config.tracking.key_name, None)

        if ruid is not None:
            args['ruid'] = ruid

        url = self.config.pwc_url + "?" + urllib.urlencode(args)
        debug(url)
        self.SFetch(url, self._on_register)

    def _on_register(self, response):
        data = None
        next = self.get_argument('next', self.GetOAuthUrl())
        reason = 'pwc_unreachable'
        if response and not response.error:
            data = ParseData(response.body, 'response')
            if data:
                if data.get('ok', 0) == 1:
                    token = EncodeToken(data['pwc_snuid'], self.config.pwc_token_password_md5,
                                        self.config.pwc_token_secret, 0)
                    code = gen_request_code()
                    self.cache.Add(code, (token, 0))
                    self.user = {
                        'auid': data['auid'],
                        'email': self.reg_email,
                        'email_md5': md5(self.reg_email),
                        'pwd_md5': self.get_argument('reg_passwd__'),
                        'token': token,
                        'snuid': data['pwc_snuid'],
                        'p': False,
                    }
                    self.set_secure_cookie("user", tornado.escape.json_encode(self.user))
                    self.Next(next, {'code': code, 'register': 1})
                    return
                else:
                    reason = '%s(ec=%s)' % (
                        data.get('error', 'unknown pwc error'), data.get('ec', 'unknown error code') )
            else:
                reason = 'pwc registration fail (bad pwc response)'
        if self.RedirectOnError(next, reason):
            return
        self.Message(data, message='registration_error', next=next)


# -----------------------------------------------------------------------------------

class JSONPRegisterHandler(DoRegisterHandler):
    """ В отличие от DoRegisterHandler, не делаем redirect, а отвечаем """

    @tornado.web.asynchronous
    def get(self):
        self.jsonp_callback = self.get_argument('callback', 'xxx')
        self.post()

    # ~ SUCCESS:
    #~  self.set_secure_cookie("user", tornado.escape.json_encode(self.user))
    #~  self.Next(next, { 'code' : code, 'register' : 1 })
    def Next(self, next_url, code_dict):
        self.fin(dict(register=1, auid=self.user['auid'], email=self.user['email']))

    #~ FAIL:
    #~  if self.RedirectOnError(next, reason):
    def RedirectOnError(self, next_url, reason):
        self.fin(dict(register=0, reason=reason))
        return True

    def fin(self, response):
        reply_string = self.jsonp_callback + "(" + json.dumps(response) + ")"
        self.finish(reply_string)


# -----------------------------------------------------------------------------------

class OAuthHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        response_type = self.get_argument('response_type', None)
        redirect_uri = self.get_argument('redirect_uri', None)
        is_register = self.get_argument('register', None)
        if response_type == 'token':
            if not self.current_user:
                self.redirect(self.config.pwcf_url_prefix + "/login")
                return
            else:
                if redirect_uri:
                    args = {'access_token': self.current_user['token'], 'expires_in': 0}
                    if is_register:
                        args['register'] = 1
                    self.Redirect(redirect_uri, args)
                    return
        elif response_type == 'code':
            state = self.get_argument('state', None)
            code = self.get_argument('code', None)
            if redirect_uri:
                if code:
                    args = {
                        'code': code
                    }
                    if state:
                        args['state'] = state
                    if is_register:
                        args['register'] = 1
                    self.Redirect(redirect_uri, args)
                else:
                    if self.current_user and self.current_user.get('p', False) and self.current_user.get('snuid', None):
                        token = EncodeToken(self.current_user['snuid'], self.config.pwc_token_password_md5,
                                            self.config.pwc_token_secret, 0)
                        code = gen_request_code()
                        self.cache.Add(code, (token, 0))
                        self.current_user['token'] = token
                        self.set_secure_cookie("user", tornado.escape.json_encode(self.current_user))
                        args = {
                            'code': code
                        }
                        if state:
                            args['state'] = state
                        if is_register:
                            args['register'] = 1
                        self.Redirect(redirect_uri, args)
                    else:
                        self.redirect(self.config.pwcf_url_prefix + "/login?next=" + tornado.escape.url_escape(
                            self.config.pwcf_url_prefix + self.request.uri))
            else:
                self.Error("Redirect uri not defined")
        elif not self.config.pwcf_disable_direct_mode:
            if not self.current_user:
                self.redirect(self.config.pwcf_url_prefix + "/login")
                return
            if self.config.debug:
                self.Render('root.html', user=json.dumps(self.current_user, indent=4),
                            email=self.current_user.get('email', 'unknown'))
            else:
                self.Message(None, message='welcome_to_prime_world', next=self.GetOAuthUrl())
        else:
            self.OAuthError('Direct mode is disabled')


class AccessTokenHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        redirect_uri = self.get_argument('redirect_uri', None)
        code = self.get_argument('code', None)
        data = self.cache.Retrieve(code)
        if data:
            token, expires = data
            args = {
                'access_token': token,
                'expires': expires,
            }
            self.write(urllib.urlencode(args))
            self.finish()
        else:
            self.OAuthError('Error validating verification code')


class LoginHandler(BaseHandler):
    @tornado.web.asynchronous
    def get(self):
        next = self.get_argument('next', tornado.escape.url_escape(self.GetOAuthUrl()))
        args = {
            'next': next,
        }
        locale = self.getRequestLocale()
        support = self.localize(self.config.links.support, self.NormalizeLocale(locale))
        logo = self.localize(self.config.links.logo, self.NormalizeLocale(locale))

        self.Render("login.html", next=tornado.escape.url_unescape(next), support=support, logo=logo,
                    params=urllib.urlencode(args), locale=locale)


class DoLoginHandler(BaseHandler):
    @tornado.web.asynchronous
    def post(self):
        locale = self.getRequestLocale()
        if not self.CheckRecaptcha2():
            next = self.get_argument('next', self.GetOAuthUrl())
            self.Message(None, message=('login_error'), next=next)
            return

        args = dict(
            action='l_who',
            snid='pwe',
            snuid=md5u(self.get_argument("email")),
            ver=self.config.pwc_version,
            locale=self.NormalizeLocale(locale),
            nocbt=1
        )
        args['sign'] = Sign(args, self.get_argument("pass"))

        url = self.config.pw_url + "?" + urllib.urlencode(args)
        debug(url)
        self.http_client.fetch(url, self._on_login)

    def _on_login(self, response):
        data = None
        persistent = self.GetBool('persistent', False)
        next = self.get_argument('next', self.GetOAuthUrl())
        reason = 'pwc_unreachable'
        if response and not response.error:
            data = ParseData(response.body, 'response')
            if data and data.get('ok', 0) == 1:
                info = data.get('info', {})
                sns = data.get('sns', {})
                token = data.get('token', None)
                snuid = data.get('pwc_snuid', '')
                if info.get('auid', None) and token and snuid:
                    token = EncodeToken(snuid, self.config.pwc_token_password_md5, self.config.pwc_token_secret, 0)
                    code = gen_request_code()
                    self.cache.Add(code, (token, 0))
                    user = {
                        'auid': info.get('auid'),
                        'email': self.get_argument("email"),
                        'email_md5': md5(self.get_argument("email")),
                        'pwd_md5': self.get_argument('pass'),
                        'token': token,
                        'snuid': snuid,
                        'p': persistent,
                    }
                    self.set_secure_cookie("user", tornado.escape.json_encode(user))
                    self.Next(next, {'code': code})
                    return
            else:
                reason = 'pwc_login_fail'

        if self.RedirectOnError(next, reason):
            return
        self.Message(data, message='login_error', next=self.GetOAuthUrl())


class DoLogoutHandler(BaseHandler):
    def get(self):
        self.clear_cookie("user")
        self.redirect(self.config.pwcf_url_prefix + "/login")


class TokenCache:
    def __init__(self):
        self.cache = {}

    def Add(self, code, token):
        self.cache[code] = token

    def Retrieve(self, code):
        token = self.cache.get(code, None)
        if token:
            del self.cache[code]
        return token

    def GetData(self):
        return {'active': len(self.cache)}


class PWConnectFrontendService(Service):
    def __init__(self, sid):
        super(PWConnectFrontendService, self).__init__(sid)
        self.cache = TokenCache()

    def Start(self, link, config):
        self.config = config
        self.link = link
        self.http_client = tornado.httpclient.AsyncHTTPClient()

        if config.translations_path:
            tornado.locale.load_translations(config.translations_path)
        handlers = [
            (r"/oauth", OAuthHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/oauth/access_token", AccessTokenHandler,
             dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/login", LoginHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/do/login", DoLoginHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/do/logout", DoLogoutHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/register", RegisterHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/do/register", DoRegisterHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/jsonp_register", JSONPRegisterHandler,
             dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/resetpwd", ResetHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/do/resetpwd", DoResetHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/changepwd", ChangeHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/do/changepwd", DoChangeHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/do/changepwdext", DoChangePwdExtHandler,
             dict(config=config, http_client=self.http_client, cache=self.cache)),
            (
                r"/resetpwdlink", ResetPwdLinkHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/do/resetpwdlink", DoResetPwdLinkHandler,
             dict(config=config, http_client=self.http_client, cache=self.cache)),
            # (r"/changeemail", ChangeEmailHandler, dict(config=config, http_client=self.http_client, cache = self.cache)),
            (r"/getuserinfo", GetUserInfoHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            #(r"/do/changeemail", DoChangeEmailHandler, dict(config=config, http_client=self.http_client, cache = self.cache)),
            (r"/do", DoHandler, dict(config=config, http_client=self.http_client, cache=self.cache)),
            (r"/signup", SignupHandler, dict(config=config)),
        ]
        if self.config.debug:
            handlers.extend([
                (r"/samples/(.*)", tornado.web.StaticFileHandler, {"path": './templates'}),
            ])
        if self.config.pwcf_serve_static_content:
            handlers.extend([
                (r"/static/(.*)", tornado.web.StaticFileHandler, {"path": './static'}),
                (r"/pwcf/static/(.*)", tornado.web.StaticFileHandler, {"path": './static'}),
            ])
        self.application = tornado.web.Application(
            handlers,
            cookie_secret=str(self.config.pwcf_cookie_secret),
            login_url=self.config.pwcf_url_prefix + "/login",
            static_url_prefix=config.pwcf_static_url_prefix,
            template_path=os.path.join(os.path.dirname(__file__), "templates"),
            static_path=os.path.join(os.path.dirname(__file__), "static"),
            debug=self.config.debug,
            autoescape=None)
        self.http_server = tornado.httpserver.HTTPServer(self.application)
        self.http_server.bind(self.config.port)
        self.http_server.start(self.config.nump)
        self.fsm.Move(Service.STARTED)

    def Update(self):
        ## warning('PWConnectFrontendService.Update') ##DEBUG
        self.HttpLoggerTick()

    def Stop(self, how):
        self.fsm.Move(Service.STOPPED)


def main(args, gate):
    if args.config:
        config = System.config.RawConfig(args.config)
    else:
        config = System.config.RawConfig(
            {
                'port': 10004,
                'nump': 1,
                'pwc_version': '0.12.0.12151.Trunk',
                'pwc_url': 'https://pw.nivalnetwork.com:888/pwc',
                'pw_url': 'http://pw.nivalnetwork.com:88',
                'pwc_token_secret': 'Nival forever',
                'pwc_token_password_md5': md5('sunset'),
                'pwcf_static_url_prefix': '/static/',
                'pwcf_url_prefix': '',
                'pwcf_serve_static_content': False,
                'pwcf_cookie_secret': "16o131312312312addasETASDASDzKXQAGaYdkL5gEmGeJJFuYh7EQnp2XdTP1o/Vo=",
                'pwcf_disable_direct_mode': False,
                'debug': True,
                'ssl_path': '../../tests/ssl_ca',
                'translations_path': './translations',
                'links': {
                    'support': {
                        '<def>': 'http://support.%s.playpw.com/',
                        'EN': 'mailto:support.en@playpw.com',
                    },
                    'eula': 'http://updates.playpw.com/eula-%s.rtf',
                    'logo': {
                        '<def>': 'http://playpw.com/',
                        'EN': 'http://en.playpw.com/',
                    },
                },
                'tracking': {
                    'key_name': 'nival_tracking_key',
                },
                "recaptcha": {
                    "recaptcha_key": "6LeZFwMTAAAAAIugtSu4MIB6MaVTdRQlzpKv1rXR",
                    "recaptcha_secret": "6LeZFwMTAAAAALnknqlyNje2u0CTKd3_Bg81zrIc",
                    "recaptcha_theme": "custom"
                }
            }
        )
    svn = PWConnectFrontendService(args.sid)
    gate.AddService(svn, config)
    svn.HttpLoggerInit(args, config)


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--config', default=None, help='Config path')
    parser.add_argument('--sid', default='PWConnectFrontend', help='Service class id')
    parser.add_argument('--pid', default='pwcf', help='Service process (instance) id')
    System.logs.setupParserArgs(parser)
    args = parser.parse_args()

    System.logs.setup(args.log, args.loglevel, args.logrotate)

    gate = Network.SOA.ServiceGate()

    main(args, gate)
    gate.Run()
