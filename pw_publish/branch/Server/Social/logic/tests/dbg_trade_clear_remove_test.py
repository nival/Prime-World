import sys

sys.path.append('../')
sys.path.append('../..')
from logic.dbg_trade_clear_remove import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC
from logic.tests.trade_event_buy_test import trade_event_test_helper


class dbg_trade_clear_remove_test:

    __EVENT_ID = 1234
    __EVENT_GUID = 1
    __EVENT_JSON_FILE_NAME = 'test_data/trade_event.json'

    def dbg_trade_clear_remove_test(self, env):
        helper = trade_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model

        model_data.applyActiveTradeEvents(env.acc, env.I.Config)

        # add progression
        model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes.append(1234)
        model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes.append(1235)
        model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes.append(1236)
        model_data.Resources.Currencies['CC_Token'] = 1
        model_data.Resources.Currencies['CC_Oscar'] = 1

        requests = [(Dbg_trade_clear_remove,
                     DbgTradeEventClearRequest(model_data,
                                          {'tradeEventId': [self.__EVENT_ID], 'groupIndex': [0], 'memberIndex': [0],
                                           'isFirstChoice': ["true"]},
                                          False))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        #print pprint.PrettyPrinter(indent=1).pprint(changes)
        assert changes[changes_index]['ok'] == 1
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 0
        assert model_data.Resources.Currencies['CC_Token'] == 0
        assert model_data.Resources.Currencies['CC_Oscar'] == 0
