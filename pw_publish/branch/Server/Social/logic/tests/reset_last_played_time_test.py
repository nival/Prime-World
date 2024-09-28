import sys
sys.path.append('../')
sys.path.append('../..')
from logic.reset_last_played_time import *
from binascii import crc32
from base.helpers import *

class reset_last_played_time_test:

    def reset_last_played_time_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.LastRankedGameTime = int(time.time()) - 60*60*24*100
        decreaseLevel = env.acc.SD.getRatingToLooseLevel(modeldata.LordInfo.LastRankedGameTime)

        if not decreaseLevel: # PF-104481
            return

        oldTime = modeldata.LordInfo.LastRankedGameTime
        hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
        hero.Rating = 1500

        requests = [(Reset_last_played_time, ResetLastPlayedTimeRequest(modeldata, {"decreaseRating": ["true"]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.LordInfo.LastRankedGameTime > oldTime
        assert hero.Rating == 1500 - decreaseLevel['ratingToLoose']

    def reset_last_played_time_decrease_to_minimum_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.LastRankedGameTime = int(time.time()) - 60*60*24*100
        decreaseLevel = env.acc.SD.getRatingToLooseLevel(modeldata.LordInfo.LastRankedGameTime)
        oldTime = modeldata.LordInfo.LastRankedGameTime
        hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
        hero.Rating = env.acc.SD.data['RatingDecreaseByTime']['minRatingToLoose']

        requests = [(Reset_last_played_time, ResetLastPlayedTimeRequest(modeldata, {"decreaseRating": ["true"]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.LordInfo.LastRankedGameTime > oldTime
        assert hero.Rating == env.acc.SD.data['RatingDecreaseByTime']['minRatingToLoose']

    def reset_last_played_time_dont_decrease_rating_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.LastRankedGameTime = int(time.time()) - 60*60*24*100
        decreaseLevel = env.acc.SD.getRatingToLooseLevel(modeldata.LordInfo.LastRankedGameTime)
        oldTime = modeldata.LordInfo.LastRankedGameTime
        hero = modeldata.hireHero( crc32("mowgly"), env.acc.sex, env.I.WS, env.acc, env.I )
        hero.Rating = 1500

        requests = [(Reset_last_played_time, ResetLastPlayedTimeRequest(modeldata, {"decreaseRating": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.LordInfo.LastRankedGameTime > oldTime
        assert hero.Rating == 1500