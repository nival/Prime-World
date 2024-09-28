import sys

sys.path.append('../')
sys.path.append('../..')
from logic.season_event_buy_item import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class season_event_buy_item_test:

    __EVENT_ID = 1234
    __EVENT_GUID = 1
    __EVENT_JSON_FILE_NAME = 'test_data/season_event.json'

    def season_event_init_test(self, env):
        helper = season_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model

        model_data.applyActiveSeasonEvents(env.acc, env.I.Config)
        model_data.applyActiveSeasonEvents(env.acc, env.I.Config)
        model_data.applyActiveSeasonEvents(env.acc, env.I.Config)

        assert len(model_data.SeasonEvents) == 1
        assert 2 not in model_data.SeasonEvents
        assert 3 not in model_data.SeasonEvents
        assert self.__EVENT_GUID in model_data.SeasonEvents
        assert model_data.SeasonEvents[self.__EVENT_GUID].PersistentId == self.__EVENT_GUID
        assert len(model_data.SeasonEvents[self.__EVENT_GUID].CollectedLootboxes) == 0

    def season_event_buy_test(self, env):
        helper = season_event_test_helper()
        helper.cleanup(env, self.__EVENT_ID)
        helper.load_event_data(env, self.__EVENT_JSON_FILE_NAME, self.__EVENT_ID)
        model_data = env.acc.model

        model_data.Resources.Currencies['CC_Oscar'] = 1000

        model_data.applyActiveSeasonEvents(env.acc, env.I.Config)

        requests = [(Season_event_buy_item,
                     SeasonEventBuyItemRequest(model_data,
                                             {'seasonEventId': [self.__EVENT_ID], 'groupIndex': [0], 'itemIndex': [0]},
                                             False))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        #debug(pprint.PrettyPrinter(indent=1).pprint(changes))
        assert changes[changes_index]['ok'] == 1
        assert model_data.Resources.Currencies['CC_Oscar'] == 960
        assert len(model_data.Lootboxes) == 1
        assert len(model_data.SeasonEvents[self.__EVENT_GUID].BoughtItems) == 1
        assert model_data.SeasonEvents[self.__EVENT_GUID].BoughtItems['0'] == 1
        assert model_data.Lootboxes.values()[0].PersistentId == crc32("LB_Crystal_Red2")
        assert not model_data.Lootboxes.values()[0].Reward.IsApplied

        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        #debug(pprint.PrettyPrinter(indent=1).pprint(changes))
        assert changes[changes_index]['ok'] == 0

class season_event_test_helper:

    def cleanup(self, env, event_persistent_id):
        model_data = env.acc.model
        if event_persistent_id in model_data.SeasonEvents:
            model_data.SeasonEvents.remove(event_persistent_id)

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
