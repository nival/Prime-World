import sys
sys.path.append('../')
sys.path.append('../..')
from logic.season_event_give_reward import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

from logic.tests.season_event_buy_item_test import season_event_test_helper

class season_event_give_reward_test:


    __EVENT_ID = 1234
    __EVENT_GUID = 1
    __EVENT_JSON_FILE_NAME = 'test_data/season_event.json'

    def test1(self, env):
        helper = season_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model
        model_data.applyActiveSeasonEvents(env.acc, env.I.Config)

        model_data.SeasonEvents[self.__EVENT_GUID].PlayerProgress = 800
        # exp == 0
        model_data.Resources.Currencies['CC_Token'] = 1000
        #model_data.Resources.Currencies['CC_Oscar'] = 0
        for retry in range(2):
            requests = [(Season_event_give_reward,
                         SeasonEventGiveRewardRequest(model_data,
                                                     {'rid': [retry*100], 'seasonEventId': [self.__EVENT_ID]},
                                                     False))]
            env.execActions(requests)

        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.SeasonEvents[self.__EVENT_GUID].CollectedLootboxes) == 1

    def test_give_reward_fail(self, env):
        helper = season_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model
        model_data.applyActiveSeasonEvents(env.acc, env.I.Config)

        model_data.SeasonEvents[self.__EVENT_GUID].PlayerProgress = 5000
        # exp == 0
        model_data.Resources.Currencies['CC_Token'] = 1000
        #model_data.Resources.Currencies['CC_Oscar'] = 0
        for retry in range(2):
            requests = [(Season_event_give_reward,
                         SeasonEventGiveRewardRequest(model_data,
                                                     {'rid': [retry*100], 'seasonEventId': [self.__EVENT_ID]},
                                                     False))]
            env.execActions(requests)

        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.SeasonEvents[self.__EVENT_GUID].CollectedLootboxes) == 0