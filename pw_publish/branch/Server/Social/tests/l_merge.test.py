import sys, os, time, logging, json

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )

import ext_main.l_merge
from ifactory import IfaceFactory
import cfg

import unittest

class DummyHttp:

    def __init__(self):
        self.requests = {}

    def fetch(self, request, callback):
        if type(request) == str:
            body = None
            url = request
        else:
            body = request.body
            url = request.url
        self.requests[url] = (body, callback)

    def push(self, url, result, error=None):
        data, callback = self.requests[url]
        class Response:
            def __init__(self, body, error):
                self.body = body
                self.error = error
        del self.requests[url] 
        callback(Response(result, error))

    def clear(self):
        self.requests.clear()


class Test_Merge(unittest.TestCase):

    def test(self):
        cfg.BILLING_MERGE_DISABLED_PS = ['102']
        arguments = {
            'auid0' : ['555'],
            'auid1' : ['777'],
#            'email_md5' : ['email_md5'],
#            'pwc_snuid' : ['pwc_snuid'],
        }
        def OnFinish(**args):
            print args

        class Interfaces:
            pass

        class STATS:
            def addSocialMerge(self, auid0, auid1):
                pass
        class WS:       
            TEST_MODE = False

            def deleteLoginToken(self, auid):
                pass

            def setSnBonusCount(self, auid, count, pcount, new_networks):
                pass

            def serverSubLogin(self, login, persistent_callback, auid):
                class Acc:
                    pass
                class Model:
                    def getSpentGold(self, I, acc):
                        return 100
                class Db:
                    guildAuid = None
                acc = Acc()
                acc.model = Model()
                acc.db = Db()
                persistent_callback(acc)

        I = Interfaces()    
        I.BILL = IfaceFactory.makeBillingInterface( "dummy", I )
        http = DummyHttp()
        I.AGG = IfaceFactory.makeSocAggInterface("http", 'http://url', '0.3.93', http )
        I.WS = WS()
        I.STATS = STATS()

        I.BILL.replenish(777, 3000, 'reason', payment_system='102')

        a = ext_main.l_merge.LauncherMergeInternalAction(arguments, OnFinish, None)
        a.I = I
        a.onStart()

        data = {
            'get_info' : {
                'props' : {
                    'fsn' : 'fb'
                },
                'fb' : {
                    'snuid' : '77777777',
                }
            }
        }
        http.push('http://url/?action=get_info&auid=777&version=0.3.93&include_secure_data=1', json.dumps(data))
        data = {
            'error' : 0
        }
        http.push('http://url/?action=merge&auid1=555&auid2=777&version=0.3.93', json.dumps(data))

        data = {
            'get_info' : {
                'props' : {
                    'fsn' : 'fb'
                },
                'fb' : {
                    'snuid' : '5555555',
                }
            }
        }
        http.push('http://url/?action=get_info&auid=555&version=0.3.93&include_secure_data=1', json.dumps(data))
        auid, helper = I.BILL.checkHelper('555')
        self.assertEquals(2100, helper.getBalance())
            


if __name__ == '__main__':
    import logging
    logging.getLogger().setLevel(logging.DEBUG)
    unittest.main()