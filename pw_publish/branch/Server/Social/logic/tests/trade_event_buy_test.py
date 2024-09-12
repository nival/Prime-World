import sys

sys.path.append('../')
sys.path.append('../..')
from logic.trade_event_buy import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC


class trade_event_buy_test:

    __EVENT_ID = 1234
    __EVENT_GUID = 1
    __EVENT_JSON_FILE_NAME = 'test_data/trade_event.json'

    def trade_event_init(self, env):
        helper = trade_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model

        progr, _ = model_data.newTradeEventProgression()
        progr.PersistentId = 2
        model_data.TradeEvents.add(2, progr)

        progr, _ = model_data.newTradeEventProgression()
        progr.PersistentId = 3
        model_data.TradeEvents.add(3, progr)

        # print 'Before'
        # print 'configData TradeEvents {}'.format([e.Guid for _, e in env.I.Config.getConfig('ru').TradeEvents.iteritems()])
        # print 'md TradeEvents {}'.format([event_id for event_id in model_data.TradeEvents])

        model_data.applyActiveTradeEvents(env.acc, env.I.Config)

        # print 'After'
        # print 'configData TradeEvents {}'.format([e.Guid for _, e in env.I.Config.getConfig('ru').TradeEvents.iteritems()])
        # print 'md TradeEvents {}'.format([event_id for event_id in model_data.TradeEvents])

        assert len(model_data.TradeEvents) == 1
        assert 2 not in model_data.TradeEvents
        assert 3 not in model_data.TradeEvents
        assert self.__EVENT_GUID in model_data.TradeEvents
        assert model_data.TradeEvents[self.__EVENT_GUID].PersistentId == self.__EVENT_GUID
        assert len(model_data.TradeEvents[self.__EVENT_GUID].CollectedLootboxes) == 0

    def trade_event_buy_test(self, env):
        helper = trade_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model

        model_data.Resources.Currencies['CC_Token'] = 1000

        model_data.applyActiveTradeEvents(env.acc, env.I.Config)

        requests = [(Trade_event_buy,
                     TradeEventBuyRequest(model_data,
                                             {'tradeEventId': [self.__EVENT_ID], 'groupIndex': [0], 'memberIndex': [0], 'isFirstChoice': ["true"]},
                                             False))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        #print pprint.PrettyPrinter(indent=1).pprint(changes)
        assert changes[changes_index]['ok'] == 1
        assert model_data.Resources.Currencies['CC_Token'] == 970
        assert len(model_data.Lootboxes) == 1
        assert model_data.Lootboxes.values()[0].PersistentId == crc32("LB_Crystal_Red2")
        assert not model_data.Lootboxes.values()[0].Reward.IsApplied


class trade_event_test_helper:

    def cleanup(self, env, event_persistent_id):
        model_data = env.acc.model
        if event_persistent_id in model_data.TradeEvents:
            model_data.TradeEvents.remove(event_persistent_id)

    def load_event_data(self, env, json_file_name, event_persistent_id):
        with open(json_file_name, 'r') as json_file:
            event_json = json_file.read()
        event_data = json_loads(event_json)
        current_time = int(time.time())
        ws_event_record = dict(startTime=current_time-1000, endTime=current_time+1000, persistentId=event_persistent_id,
                               enabled=event_data['enabled'], type=event_data['type'],
                               newValue=event_data['customData'], defaultValue={},
                               description=event_data['description'])
        activeEvents = {event_persistent_id: ws_event_record}
        env.I.WS.operatorEvents = {'activeEvents': activeEvents}
        env.I.Config.applyEvent(env.I.SD, ws_event_record)
