# -*- coding: utf-8 -*-

import sys
sys.path.append('../common/py')

import Network.Web.sandbox
import System.logs

import time

System.logs.setup(None, 'debug')

se = Network.Web.sandbox.Caller('http://127.0.0.1:10003', 'action')

import hashlib
def md5(data):
    m = hashlib.md5()
    m.update(data)
    return m.hexdigest()

email = 'e_e_i@mail.ru'
new_email = 'redjack@inbox.com'
password = 'sunset' 
new_password = 'dawn'
new_password2 = None 

class Sign:

    def __init__(self, pwd_md5):
        self.pwd_md5 = pwd_md5

    def __call__(self, args):
        data = list(args.items())
        def ZeroItem(item):
            return item[0]
        data.sort(key=ZeroItem)
        s = ''
        for name, value in data:
            s += name+value
        s += self.pwd_md5
        print 'Sign', args, self.pwd_md5
        return ('sign', md5(s))

reg = se.pwc_register(email=email, pwd=md5(password), gender=1, birthdate=int(time.time()))
if reg.ec == 0:
    se.pwc_get_info(snuid=reg.pwc_snuid)

r = se.l_who(snid='pwe', snuid=md5(email), ver='1.2.3', __sign=Sign(md5(password)))
assert r.response.ec == 0

se.pwc_confirm(snuid=md5(email), confirm='bad_token')

res = se.pwc_resend_confirm(snuid=md5(email), __sign=Sign(md5(password)))

cf = se.pwc_confirm(snuid=md5(email), confirm=res.debug_confirm_token)
if cf.ec == 0:
    r = se.l_who(snid='pwe', snuid=md5(email), ver='1.2.3', __sign=Sign(md5(password)))
    assert r.response.ec == 0

    ce = se.pwc_change_email(snuid=md5(email), new_email=new_email, __sign=Sign(md5(password)))
    assert ce.ec == 0

    r = se.l_who(snid='pwe', snuid=md5(new_email), ver='1.2.3', __sign=Sign(md5(password)))
    assert r.response.ec == 0
    se.pwc_confirm(snuid=md5(new_email), confirm=ce.debug_confirm_token)

    se.pwc_change_pwd(snuid=md5(new_email), pwd=md5(new_password), __sign=Sign(md5(password+'fuck off')))
    se.pwc_change_pwd(snuid=md5(new_email), pwd=md5(new_password), __sign=Sign(md5(password)))

    rp = se.pwc_reset_pwd(snuid=md5(new_email))
    new_password2 = rp.debug_new_password

    cpl = se.pwc_reset_pwd_link(snuid=md5(new_email))

    cp = se.pwc_change_pwd(snuid=md5(new_email), pwd=md5('olala'), __sign=Sign(cpl.debug_link.token))
    assert cp.ec == 0
