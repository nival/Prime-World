import unittest
import sys, os, time, logging, json

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )

import pwaccount

class Test_PwAccount(unittest.TestCase):

    def test(self):
        data = { 'snuid' : '55555' }
        self.assertEquals('55555', pwaccount.ParseSnuid('fb', data))

    def testFbPhoto(self):
        data = {  }
        self.assertEquals(None, pwaccount.ParseSnuid('ok', data))
        data = { 'photo' : 'http://graph.facebook.com/5555/picture' }
        self.assertEquals('5555', pwaccount.ParseSnuid('fb', data))

if __name__ == '__main__':
    import logging
    logging.getLogger().setLevel(logging.ERROR)
    unittest.main()