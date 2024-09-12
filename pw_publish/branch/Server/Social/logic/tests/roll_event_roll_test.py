import sys
sys.path.append('../')
sys.path.append('../..')
from logic.roll_event_roll import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC
addModPath("../thrift_pw/account_management/gen-py")
from AccountManagementAPI.ttypes import ConfigEventType
from enums.RollEventRuleType import RollEventRuleType
from enums.RollEventItemType import RollEventItemType

from modeldata.ModelData import ModelData


class roll_event_roll_test:
    __EVENT_ID = 12345
    __EVENT_GUID = 1

    def __load_event_data(self, env):
        with open('test_data/roll_event.json', 'r') as json_file:
            event_json = json_file.read()
        event_data = json_loads(event_json)
        current_time = int(time.time())
        ws_event_record = dict(startTime=current_time-1000, endTime=current_time+1000, persistentId=self.__EVENT_ID,
                               enabled=event_data['enabled'], type=event_data['type'],
                               newValue=event_data['customData'], defaultValue={},
                               description=event_data['description'])
        activeEvents = {self.__EVENT_ID: ws_event_record}
        env.I.WS.operatorEvents = {'activeEvents': activeEvents}
        env.I.Config.applyEvent(env.I.SD, ws_event_record)

    def __prepare_inventory_step1(self, model_data):
        """

        :param model_data:
        :type model_data: ModelData
        :return:
        """
        talent, talent_id = model_data.newTalent()
        talent.PersistentId = 'G322'
        talent.Points = 0
        talent, talent_id = model_data.newTalent()
        talent.PersistentId = 'G322'
        talent.Points = 200
        talent, talent_id = model_data.newTalent()
        talent.PersistentId = 'G322'
        talent.Points = 100
        # TODO: How to add soulbounded talents to test???

    def roll_event_roll_all_rules_test( self, env ):
        modeldata = env.acc.model

        self.__load_event_data(env)

        time.sleep(1.0)

        modeldata.Resources.Currencies['EUR'] = 200
        modeldata.Resources.Currencies['USD'] = 100
        # env.acc.getConfig().EventToolsChangeFields.HERO_SILVER_PRICES[static_hero['persistentId']] =0

        self.__prepare_inventory_step1(modeldata)

        availableEvents = env.acc.getConfigValue("RollEvents")
        eventData = availableEvents[self.__EVENT_ID]
        for i in range(0, 5):
            chl_idx = i*2
            rolls = sorted(eventData.Rolls.values(), key=lambda x: x.RuleType)
            for roll in rolls:
                if roll.RuleType == RollEventRuleType.Simple:
                    requests = [(Roll_event_roll, RollEventRoll(modeldata,
                                                                {
                                                                    "rid": [i],
                                                                    "rollEventId": [self.__EVENT_ID],
                                                                    "ruleId": [roll.getID()],
                                                                }, False))]
                    changes = env.execActions(requests)
                    assert 'error' not in changes[chl_idx]
                    assert changes[chl_idx]['ec'] == 0
                    assert 'roll_result' in changes[chl_idx]
                    assert changes[chl_idx]['roll_result']['event_id'] == self.__EVENT_ID
                    assert 'reward_id' in changes[chl_idx]['roll_result']
                    assert changes[chl_idx]['roll_result']['rule_id'] == roll.getID()

                elif roll.RuleType == RollEventRuleType.Reforge:
                    chl_idx = chl_idx + 1
                    requests = [(Roll_event_roll, RollEventRoll(modeldata, {"rid": [i],
                                                                            "rollEventId": [self.__EVENT_ID],
                                                                            "ruleId": [roll.getID()],
                                                                            "reforgeSourceId": [roll.ReforgeSources.values()[0].getID()]
                                                                            }, False))]
                    changes = env.execActions(requests)
                    assert 'error' not in changes[chl_idx]
                    assert changes[chl_idx]['ec'] == 0
                    assert 'roll_result' in changes[chl_idx]
                    assert changes[chl_idx]['roll_result']['event_id'] == self.__EVENT_ID
                    assert 'reward_id' in changes[chl_idx]['roll_result']
                    assert changes[chl_idx]['roll_result']['rule_id'] == roll.getID()

