# -*- coding: utf-8 -*-

import sys
sys.path.append('../')
sys.path.append('../..')
from logic.quest_event_choose import *
from logic.dbg_quest_event_choose import *
from logic.dbg_quest_event_clear import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC


class quest_event_choose_test:
    __EVENT_ID = 1234
    __EVENT_GUID = 1
    __SILVER_POOL = 1000000
    __PEARL_POOL = 1000000

    def __load_event_data(self, env):
        with open('test_data/quest_event.json', 'r') as json_file:
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

    def __cleanup(self, env):
        model_data = env.acc.model
        if self.__EVENT_GUID in model_data.QuestEvents:
            model_data.QuestEvents.remove(self.__EVENT_GUID)

    def init_record_test(self, env):
        self.__cleanup(env)
        self.__load_event_data(env)
        model_data = env.acc.model

        progr_id = model_data.addNewQuestEventProgression()
        progr = model_data.getQuestEventProgressionByID(progr_id)
        progr.PersistentId = 2
        model_data.QuestEvents.add(2, progr)
        progr_id = model_data.addNewQuestEventProgression()
        progr = model_data.getQuestEventProgressionByID(progr_id)
        progr.PersistentId = 3
        model_data.QuestEvents.add(3, progr)

        model_data.applyActiveQuestEvents(env.acc, env.I.Config)

        assert len(model_data.QuestEvents) == 1
        assert 2 not in model_data.QuestEvents
        assert 3 not in model_data.QuestEvents
        assert self.__EVENT_GUID in model_data.QuestEvents

    def choose_test_empty(self, env):
        self.__cleanup(env)
        self.__load_event_data(env)
        model_data = env.acc.model
        model_data.applyActiveQuestEvents(env.acc, env.I.Config)
        model_data.Resources.Perl = self.__PEARL_POOL
        model_data.Resources.Silver = self.__SILVER_POOL
        initial_lootboxes_len = len(model_data.Lootboxes)
        for i in range(100):
            choice_index = random.randint(0, 2)
            requests = [(Quest_event_choose,
                         QuestEventChooseRequest(model_data,
                                                 {'questEventId': [self.__EVENT_ID], 'choiceIndex': [choice_index]},
                                                 False))]
            env.execActions(requests)
            changes = env.getChangeList()
            changes_index = env.getChangeListIdx() - 1
            assert changes[changes_index]['ok'] == 1
        assert model_data.Resources.Perl < self.__PEARL_POOL
        assert model_data.Resources.Silver < self.__SILVER_POOL
        assert len(model_data.Lootboxes) == initial_lootboxes_len + 100

    def dbg_choose_test_win(self, env):
        self.__cleanup(env)
        self.__load_event_data(env)
        model_data = env.acc.model
        model_data.applyActiveQuestEvents(env.acc, env.I.Config)
        model_data.Resources.Perl = self.__PEARL_POOL
        model_data.Resources.Silver = self.__SILVER_POOL
        initial_lootboxes_len = len(model_data.Lootboxes)
        for i in range(20):
            choice_index = random.randint(0, 2)
            requests = [(Dbg_quest_event_choose,
                         DbgQuestEventChooseRequest(model_data,
                                                    {'questEventId': [self.__EVENT_ID], 'choiceIndex': [choice_index],
                                                     'win': [True]},
                                                    False))]
            env.execActions(requests)
            changes = env.getChangeList()
            changes_index = env.getChangeListIdx() - 1
            assert changes[changes_index]['ok'] == 1
        assert model_data.Resources.Perl < self.__PEARL_POOL
        assert model_data.Resources.Silver < self.__SILVER_POOL
        assert len(model_data.Lootboxes) == initial_lootboxes_len + 20

    def dbg_choose_test_lose(self, env):
        self.__cleanup(env)
        self.__load_event_data(env)
        model_data = env.acc.model
        model_data.applyActiveQuestEvents(env.acc, env.I.Config)
        model_data.Resources.Perl = self.__PEARL_POOL
        model_data.Resources.Silver = self.__SILVER_POOL
        initial_lootboxes_len = len(model_data.Lootboxes)
        for i in range(20):
            choice_index = random.randint(0, 2)
            requests = [(Dbg_quest_event_choose,
                         DbgQuestEventChooseRequest(model_data,
                                                    {'questEventId': [self.__EVENT_ID], 'choiceIndex': [choice_index],
                                                     'win': [False]},
                                                    False))]
            env.execActions(requests)
            changes = env.getChangeList()
            changes_index = env.getChangeListIdx() - 1
            assert changes[changes_index]['ok'] == 1
        assert model_data.Resources.Perl < self.__PEARL_POOL
        assert model_data.Resources.Silver == self.__SILVER_POOL
        assert len(model_data.Lootboxes) == initial_lootboxes_len + 20

    def dbg_quest_event_clear_test( self, env ):
        self.__cleanup(env)
        self.__load_event_data(env)
        model_data = env.acc.model

        progr_id = model_data.addNewQuestEventProgression()
        progr = model_data.getQuestEventProgressionByID(progr_id)
        progr.PersistentId = self.__EVENT_GUID
        for idx in (1, 2, 1):
            progr.Choices.append(idx)
        model_data.QuestEvents.add(self.__EVENT_GUID, progr)
        requests = [(Dbg_quest_event_clear,
                     DbgQuestEventClearRequest(model_data, {'questEventId': [self.__EVENT_ID]}, False))]
        env.execActions(requests)
        assert len(progr.Choices) == 0
