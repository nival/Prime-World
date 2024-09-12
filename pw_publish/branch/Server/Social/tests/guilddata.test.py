import unittest
import sys, os, time, logging, json
import ujson

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )
from guild.GuildData import *

class Test_GuildData(unittest.TestCase):

    def test(self):
        guilddatafile = open(os.path.join("tests/GuildDumps/guilddata.json"), "r")
        guilddatajson = ujson.load(guilddatafile)
        guilddatafile.close()
        guilddata = None
        try:
            guilddata = GuildData()
            guilddata.load(guilddatajson)
            guilddata.init(changeWriter=None)
        except Exception:
            catch()
            assert()
        summaryRating = 0
        for memberId, member in guilddata.Members.iteritems():
            summaryRating += member.DailyRating
        self.assertEqual(summaryRating, guilddata.RatingInfo.DailyRating, "ratings are not equal: members: %f, guild total: %f" % (summaryRating, guilddata.RatingInfo.DailyRating))

    #def testFbPhoto(self):
    #    data = {  }
    #    self.assertEquals(None, pwaccount.ParseSnuid('ok', data))
    #    data = { 'photo' : 'http://graph.facebook.com/5555/picture' }
    #    self.assertEquals('5555', pwaccount.ParseSnuid('fb', data))

if __name__ == '__main__':
    import logging
    logging.getLogger().setLevel(logging.ERROR)
    unittest.main()