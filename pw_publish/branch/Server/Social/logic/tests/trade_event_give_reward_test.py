import sys

sys.path.append('../')
sys.path.append('../..')
from logic.trade_event_give_reward import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC
from logic.tests.trade_event_buy_test import trade_event_test_helper


class trade_event_give_reward_test:

    __EVENT_ID = 1234
    __EVENT_GUID = 1
    __EVENT_JSON_FILE_NAME = 'test_data/trade_event.json'

    def test1(self, env):
        helper = trade_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model
        model_data.applyActiveTradeEvents(env.acc, env.I.Config)

        # exp == 0
        model_data.Resources.Currencies['CC_Token'] = 0
        model_data.Resources.Currencies['CC_Oscar'] = 0
        requests = [(Trade_event_give_reward,
                     TradeEventGiveRewardRequest(model_data,
                                                 {'tradeEventId': [self.__EVENT_ID]},
                                                 False))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 0

    def test2(self, env):
        helper = trade_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model
        model_data.applyActiveTradeEvents(env.acc, env.I.Config)

        # exp == 1000
        model_data.Resources.Currencies['CC_Token'] = 0
        model_data.Resources.Currencies['CC_Oscar'] = 1000
        requests = [(Trade_event_give_reward,
                     TradeEventGiveRewardRequest(model_data,
                                                 {'tradeEventId': [self.__EVENT_ID]},
                                                 False))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 1
        assert crc32('LB_Crystal_Red3') in model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes

    def test3(self, env):
        helper = trade_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model
        model_data.applyActiveTradeEvents(env.acc, env.I.Config)

        # exp == 1000
        model_data.Resources.Currencies['CC_Token'] = 10
        model_data.Resources.Currencies['CC_Oscar'] = 900
        requests = [(Trade_event_give_reward,
                     TradeEventGiveRewardRequest(model_data,
                                                 {'tradeEventId': [self.__EVENT_ID]},
                                                 False))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 1
        assert crc32('LB_Crystal_Red3') in model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes

    def test4(self, env):
        helper = trade_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model
        model_data.applyActiveTradeEvents(env.acc, env.I.Config)

        # exp == 1000
        model_data.Resources.Currencies['CC_Token'] = 0
        model_data.Resources.Currencies['CC_Oscar'] = 1000
        requests = [(Trade_event_give_reward,
                     TradeEventGiveRewardRequest(model_data,
                                                 {'tradeEventId': [self.__EVENT_ID]},
                                                 True))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 1

        # exp == 2000
        model_data.Resources.Currencies['CC_Token'] = 0
        model_data.Resources.Currencies['CC_Oscar'] = 2000
        requests = [(Trade_event_give_reward,
                     TradeEventGiveRewardRequest(model_data,
                                                 {'tradeEventId': [self.__EVENT_ID]},
                                                 False))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 2

        # exp == 1000
        model_data.Resources.Currencies['CC_Token'] = 0
        model_data.Resources.Currencies['CC_Oscar'] = 1000
        requests = [(Trade_event_give_reward,
                     TradeEventGiveRewardRequest(model_data,
                                                 {'tradeEventId': [self.__EVENT_ID]},
                                                 True))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 2

        # exp == 2000
        model_data.Resources.Currencies['CC_Token'] = 0
        model_data.Resources.Currencies['CC_Oscar'] = 2000
        requests = [(Trade_event_give_reward,
                     TradeEventGiveRewardRequest(model_data,
                                                 {'tradeEventId': [self.__EVENT_ID]},
                                                 True))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 2
