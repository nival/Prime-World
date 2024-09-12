import unittest

import main

import base64

def EncodeBadToken(snuid, pwdmd5, secret, expire):
    token = str(snuid)+'%'+'AAAAA'+'%'
    token += main.md5(token+pwdmd5)
    token = main.xor_strings(token, secret)
    token = base64.urlsafe_b64encode(token)
    i = len(token)-1
    while token[i] == '=' and i >= 0:
        i -= 1
    return token[:i+1]

class Test_AccessToken(unittest.TestCase):

    def test_Simple(self):
        a = main.EncodeToken(12345, 'pwdmd5', 'secret', 0)
        assert a
        snuid, expire = main.DecodeToken(a, 'pwdmd5', 'secret')
        self.assertEquals(12345, snuid)
        self.assertEquals(0, expire)

    def test_CrossSimple(self):
        a = main.EncodeToken(123456, 'pwdmd50', 'secret0', 1)
        assert a
        snuid, expire = main.DecodeToken(a, 'pwdmd50', 'secret0')
        self.assertEquals(123456, snuid)
        self.assertEquals(1, expire)

    def test_BadToken(self):
        snuid, expire = main.DecodeToken('fuckoff', 'pwdmd5', 'secret')
        self.assertEquals(None, snuid)
        self.assertEquals(None, expire)

    def test_BadToken2(self):
        a = EncodeBadToken(123456, 'pwdmd5', 'secret', 0)
        snuid, expire = main.DecodeToken(a, 'pwdmd5', 'secret')
        self.assertEquals(None, snuid)
        self.assertEquals(None, expire)

    def test_RealLife(self):
        token = main.EncodeToken(1, u'88eb60614bb67782bd8c18afb4438329', u'Nival forever', 0)
        snuid, expire = main.DecodeToken(token, '88eb60614bb67782bd8c18afb4438329', 'Nival forever')
        self.assertEquals(1, snuid)
        self.assertEquals(0, expire)

    def test_RealLife2(self):
        token = main.EncodeToken(u'898743381524481', u'88eb60614bb67782bd8c18afb4438329', u'98eb60614bb67782bd8c18afb832a966b60614bb23523482bd8c18afb44d4bb97782bd8c18afb4538329', 0)
        snuid, expire = main.DecodeToken(token, u'88eb60614bb67782bd8c18afb4438329', u'98eb60614bb67782bd8c18afb832a966b60614bb23523482bd8c18afb44d4bb97782bd8c18afb4538329')
        self.assertEquals(898743381524481, snuid)
        self.assertEquals(0, expire)

    def test_Xor(self):
        secret = u'98eb60614bb67782bd8c18afb832a966b60614bb23523482bd8c18afb44d4bb97782bd8c18afb4538329'
        r = main.xor_strings('test', secret)
        r = main.xor_strings(r, secret)
        self.assertEquals('test', r)

    def test_Xor2(self):
        secret = u'98'
        r = main.xor_strings('test', secret)
        r = main.xor_strings(r, secret)
        self.assertEquals('test', r)

if __name__ == '__main__':  
    unittest.main()