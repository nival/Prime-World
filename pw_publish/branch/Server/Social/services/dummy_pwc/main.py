# -*- coding: utf-8 -*-

import sys
sys.path.append('../common/py')

import System.logs
import System.fsm
import System.config
import Network
from Network.SOA import Service
import argparse
import os
import EC
import hashlib
import time


from logging import debug, info, error, warning

import tornado.web
import tornado.httpserver

import json
import hashlib

MANIFEST_VERSION = 1

def md5(data):
    m = hashlib.md5()
    m.update(data)
    return m.hexdigest()

class User:

    def __init__(self, auid, email, pwd, gender, birthdate, pwc_snuid):
        self.email = email
        self.pwd = pwd
        self.gender = gender
        self.birthdate = birthdate
        self.auid = auid
        self.confirm_deadline = time.time()+60*60*24*2
        self.generated_password = None
        self.pwc_snuid = pwc_snuid
        self.ResetConfirm()

    def ResetPassword(self):
        self.generated_password = str(time.time())
        self.pwd = md5(self.generated_password)

    def Confirm(self, token):
        if token == self.confirm_token:
            self.confirmed = True
            return True
        else:
            return False

    def ResetConfirm(self):
        self.confirmed = False
        self.confirm_token = md5(str(time.time())+str(id(self)))

class PWConnect:

    def __init__(self, config):
        self.config = config
        self.pwc_snuid = 1
        self.auid = 5000
        self.users = {}
        self.email_users = {}

    def Sign(self, request, pwd_md5):
        data = []
        for name, values in request.request.request.arguments.items():
            assert len(values) == 1
            if name != 'sign':
                data.append( (name, values[0]) )
        def ZeroItem(item):
            return item[0]
        data.sort(key=ZeroItem)
        s = ''
        for name, value in data:
            s += name+value
        s += pwd_md5
        print 'Sign', data, pwd_md5
        return md5(s)
        
    def Register(self, request, email, pwd, gender, birthdate):
        email_md5 = md5(email)
        if email_md5 not in self.email_users:
            pwc_snuid = self.pwc_snuid
            self.pwc_snuid += 1
            auid = self.auid
            self.auid += 1
            user = User(auid, email, pwd, gender, birthdate, pwc_snuid)
            self.users[str(pwc_snuid)] = user
            self.email_users[email_md5] = user

            request.Finish(
                {
                    'ok': 1,
                    'pwc_snuid'  : pwc_snuid,
                    'auid'  : auid,
                    'debug_confirm_token' : user.confirm_token,
                })
        else:
            request.Fail(5, 'email already taken') 

    def Who(self, request, snid, snuid, version, sign):
        assert snid == 'pwe'
        token = md5(str(time.time()))

        user = self.email_users.get(snuid, None)
        if user: 
            if sign == self.Sign(request, user.pwd):
                data = {'token' : token, "auid"  : user.auid, 'ok' : 1, 'info' : {'pwc_snuid' : user.pwc_snuid, 'gender' : user.gender, 'birthdate' : user.birthdate }}
                if not user.confirmed:
                    data['activation_term_left'] = user.confirm_deadline-time.time()
                request.Finish(data)
            else:
                request.Fail(71, 'bad signature')
        else:
            request.Fail(3, "user not found") 

    def GetInfo(self, request, snuid):
        user = self.users.get(snuid, None)
        if user:
            request.Finish({'email' : user.email, 'gender' : user.gender, 'birthdate' : user.birthdate, 'ok' : 1})
        else:
            request.Fail(2, "user not found")

    def Confirm(self, request, snuid, confirm):
        user = self.email_users.get(snuid, None)
        if user:
            if user.Confirm(confirm):
                request.Finish( {'ok' : 1} )
            else:
                request.Fail(3, 'wrong token')
        else:
            request.Fail(2, "user not found")

    def ResendConfirm(self, request, snuid, sign):
        user = self.email_users.get(snuid, None)
        if user:
            if sign == self.Sign(request, user.pwd):
                user.ResetConfirm()
                data = {
                    'debug_confirm_token' : user.confirm_token,
                    'ok' : 1,
                }
                request.Finish(data)
            else:
                request.Fail(55, 'bad sign')
        else:
            request.Fail(2)

    def ChangeEmail(self, request, snuid, new_email, sign):
        user = self.email_users.get(snuid, None)
        if user:
            if sign != self.Sign(request, user.pwd):
                request.Fail(55, 'bad sign')
                return
            email_md5 = md5(new_email)
            if email_md5 not in self.email_users:
                user.email = new_email
                del self.email_users[snuid]
                user.ResetConfirm()
                self.email_users[email_md5] = user
                data = {
                    'debug_confirm_token' : user.confirm_token,
                    'ok' : 1,
                }
                request.Finish(data)
            else:
                request.Fail(44, "email already taken")
        else:
            request.Fail(2, "user not found")

    def ChangePassword(self, request, snuid, pwd, sign):
        user = self.email_users.get(snuid, None)
        if user:
            if sign != self.Sign(request, user.pwd):
                request.Fail(55, 'bad sign')
                return
            user.pwd = pwd
            request.Finish({'ok' : 1})
        else:
            request.Fail(2, "user not found")

    def ResetPassword(self, request, snuid):
        user = self.email_users.get(snuid, None)
        if user:
            user.ResetPassword()
            data = {
                'debug_new_password' : user.generated_password,
                'debug_new_password_md5' : user.pwd,
                'ok' : 1,
            }
            request.Finish(data)
        else:
            request.Fail(2, "user not found")

    def ResetPasswordLink(self, request, snuid):
        user = self.email_users.get(snuid, None)
        if user:
            args = {
                'action' : 'pwc_change_pwd',
                'snuid' : snuid,
                'pwc_snuid' : user.pwc_snuid,
                'token' : user.pwd,
            }
            data = {
                'debug_link' : args,
                'ok' : 1,
            }
            request.Finish(data)
        else:
            request.Fail(2, "user not found")

class PWConnectHandler(tornado.web.RequestHandler):

    def initialize(self, entity):
        self.entity = entity

    @tornado.web.asynchronous
    def post(self):
        method = self.get_argument('method')
        pretty = int(self.get_argument('pretty', '0'))
        request = Network.Web.Request(self, method, pretty)
        request.Fail(EC.UNSUPPORTED_METHOD, 'Unsupported method %r' % method)

    @tornado.web.asynchronous
    def get(self):
        method = self.get_argument('action')
        pretty = int(self.get_argument('pretty', '0'))
        request = Network.Web.Request(self, method, pretty, False)
        if method == 'pwc_register':
            email = self.get_argument('email')
            pwd = self.get_argument('pwd')
            gender = int(self.get_argument('gender'))
            birthdate=int(self.get_argument('birthdate'))
            self.entity.Register(request, email, pwd, gender, birthdate)
        elif method == 'pwc_confirm':
            snuid = self.get_argument('snuid')
            confirm = self.get_argument('confirm')
            self.entity.Confirm(request, snuid, confirm)
        elif method == 'pwc_resend_confirm':
            snuid = self.get_argument('snuid')
            sign = self.get_argument('sign')
            self.entity.ResendConfirm(request, snuid, sign)
        elif method == 'pwc_change_email':
            snuid = self.get_argument('snuid')
            sign = self.get_argument('sign')
            new_email = self.get_argument('new_email')
            self.entity.ChangeEmail(request, snuid, new_email, sign)
        elif method == 'pwc_change_pwd':
            snuid = self.get_argument('snuid')
            sign = self.get_argument('sign')
            pwd = self.get_argument('pwd')
            self.entity.ChangePassword(request, snuid, pwd, sign)
        elif method == 'pwc_reset_pwd':
            snuid = self.get_argument('snuid')
            self.entity.ResetPassword(request, snuid)
        elif method == 'pwc_reset_pwd_link':
            snuid = self.get_argument('snuid')
            self.entity.ResetPasswordLink(request, snuid)
        elif method == 'l_who':
            request.method = 'response'
            request.useMethod = True
            snid = self.get_argument('snid')
            snuid = self.get_argument('snuid')  
            version = self.get_argument('ver')
            sign = self.get_argument('sign')
            self.entity.Who(request, snid, snuid, version, sign)
        elif method == 'pwc_get_info':
            request.method = 'response'
            request.useMethod = True
            snuid = self.get_argument('snuid')
            self.entity.GetInfo(request, snuid)
        else:
            request.Fail(EC.UNSUPPORTED_METHOD, 'Unsupported method %r' % method)

class PWConnectService(Service):

    def __init__(self, sid):
        super(PWConnectService, self).__init__(sid)
        self.entity = None
    
    def Start(self, link, config):
        self.config = config
        self.link = link
        self.fsm.Move(Service.STARTING)
        self.entity = PWConnect(config)
        self.application = tornado.web.Application( [
            (r"/", PWConnectHandler, dict(entity=self.entity)),
        ], debug=True )   
        self.http_server = tornado.httpserver.HTTPServer(self.application)
        self.http_server.listen(self.config.port)
        self.fsm.Move(Service.STARTED)
    
    def Update(self):
        pass
    
    def Stop(self, how):
        if self.fsm.state == Service.STARTED:   
            self.fsm.Move(Service.STOPPING)
            self.fsm.Move(Service.STOPPED)

def main(args, gate):
    if args.config:
        config = System.config.RawConfig(args.config)
    else:
        config = System.config.RawConfig({'port' : 10003}) 

    svn = PWConnectService(args.sid)
    gate.AddService(svn, config)
            
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', default=None, help='Config path')
    parser.add_argument('--sid', default='PWConnect', help='Service id')
    parser.add_argument('--log', default=None, help='Log file name')
    parser.add_argument('--loglevel', choices=['debug', 'info','warning','error', 'critical'], default='info', help='Logging severity level')
    args = parser.parse_args()

    System.logs.setup(args.log, args.loglevel)
    gate = Network.SOA.ServiceGate()

    main(args, gate)
    gate.Run()
