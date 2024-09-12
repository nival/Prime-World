import sys
sys.path.append('../')
sys.path.append('../..')
from logic.give_decrease_rating_quest import *
from base.helpers import *

class give_decrease_rating_quest_test:

    def give_decrease_rating_quest_test( self, env ):
        modeldata = env.acc.model

        oldTime = modeldata.LordInfo.LastRankedGameTime

        requests = [(Give_decrease_rating_quest, GiveDecreaseRatingQuestRequest(modeldata, {"daysAway": ["100"]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.LordInfo.LastRankedGameTime < oldTime