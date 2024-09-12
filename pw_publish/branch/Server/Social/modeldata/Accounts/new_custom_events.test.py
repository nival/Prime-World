# -*- coding: utf-8 -*-
# !/usr/bin/env python

import sys, os, time, logging, gc
from binascii import crc32

sys.path.append('../..')
sys.path.append('..')
sys.path.append('../../base')
sys.path.append('../../cfg')
#from modeldata.ModelData import *
#import jsonserialize
import unittest

from helpers import *
from datamanagerEnv import *
import glob


class MainTest(unittest.TestCase):

    def __load_event_data(self, file):
        with open(file, 'r') as json_file:
            event_json = json_file.read()
        event_data = json_loads(event_json)
        current_time = int(time.time())
        ws_event_record = dict(startTime=current_time-1000, endTime=current_time+1000, persistentId=event_data['_id'],
                               enabled=event_data['enabled'], type=event_data['type'],
                               newValue=event_data['customData'], defaultValue={},
                               description=event_data['description'])
        return ws_event_record

    def test_Main(self):
        self._test_profile("many_tables/many_tables_befor_tradeEvent.pwdump")
        self._test_profile("many_tables/pwc#3360047404943234 (1).pwdump")
        self._test_profile("many_tables/pwc#4862392605355083 (1).pwdump")
        self._test_profile("many_tables/st#76561197993463887 (4).pwdump")
        self._test_profile("many_tables/vk#274073343 (1).pwdump")

    def _test_profile(self, profile_file_name):
        env = DataManagerEnv()
        env.acc.model = None
        env.convertModelData(profile_file_name)

        model_data = env.acc.model

        # Prepare currencies
        currencies = model_data.Resources.Currencies  # type: SimpleDict
        currencies['CC_WC18_RU'] = 10
        currencies['CC_WC18_PE'] = 20
        currencies['CC_WC18_Ball'] = 20500
        # exp = 10 * 1 + 20 * 10 = 210 # захардкожена в sql mock
        # tal = 210 / 10 = 21
        # place = 1 # захардкожена в sql mock
        # lb = 15

        # Prepare events
        # cd
        env.I.WS.operatorEvents = {"finishedEvents": {}}
        # re
        event = self.__load_event_data("../../logic/testEnv/test_data/re_1.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/re_2.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/re_3.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/re_4.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        # qe
        event = self.__load_event_data("../../logic/testEnv/test_data/qe_1.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/qe_2.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/qe_3.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/qe_4.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        # tre
        event = self.__load_event_data("../../logic/testEnv/test_data/tre_1.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/tre_2.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/tre_3.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        event = self.__load_event_data("../../logic/testEnv/test_data/tre_4.json")
        env.I.WS.operatorEvents["finishedEvents"][event["persistentId"]] = event
        # md
        locale = model_data.getUserLocale(env.acc)
        tr_event = next(e for _, e in env.I.WS.operatorEvents["finishedEvents"].iteritems() if e['type'] == ConfigEventType.TradeEvent and e['newValue']['locale'].lower() == locale)
        progr = next((pr for pr in model_data.TradeEvents.values() if pr.PersistentId == tr_event['newValue']['guid']), None)
        if not progr:
            progr, _ = model_data.newTradeEventProgression()
            progr.PersistentId = tr_event['newValue']['guid']
            model_data.TradeEvents.add(tr_event['newValue']['guid'], progr)

        initial_inventory_len = len(model_data.UserInventory)
        initial_lootboxes_len = len(model_data.Lootboxes)

        model_data.applyCompletedOperatorEvents(env.acc, env.I.WS, env.I.STATS)
        # model_data.applyActiveTradeEvents(env.acc, env.I.Config)

        # assert event['newValue']['guid'] not in model_data.TradeEvents
        assert len(model_data.Lootboxes) == initial_lootboxes_len + 15
        assert len(model_data.UserInventory) == initial_inventory_len + 21
        #assert 'CC_Oscar' not in currencies
        #assert 'CC_Token' not in currencies
        assert 'CC_WC18_RU' not in currencies
        assert 'CC_WC18_SA' not in currencies
        assert 'CC_WC18_EG' not in currencies
        assert 'CC_WC18_UY' not in currencies
        assert 'CC_WC18_PT' not in currencies
        assert 'CC_WC18_ES' not in currencies
        assert 'CC_WC18_MA' not in currencies
        assert 'CC_WC18_IR' not in currencies
        assert 'CC_WC18_FR' not in currencies
        assert 'CC_WC18_AU' not in currencies
        assert 'CC_WC18_PE' not in currencies
        assert 'CC_WC18_DK' not in currencies
        assert 'CC_WC18_AR' not in currencies
        assert 'CC_WC18_IS' not in currencies
        assert 'CC_WC18_HR' not in currencies
        assert 'CC_WC18_NG' not in currencies
        assert 'CC_WC18_BR' not in currencies
        assert 'CC_WC18_CH' not in currencies
        assert 'CC_WC18_CR' not in currencies
        assert 'CC_WC18_RS' not in currencies
        assert 'CC_WC18_DE' not in currencies
        assert 'CC_WC18_MX' not in currencies
        assert 'CC_WC18_SE' not in currencies
        assert 'CC_WC18_KR' not in currencies
        assert 'CC_WC18_BE' not in currencies
        assert 'CC_WC18_PA' not in currencies
        assert 'CC_WC18_TN' not in currencies
        assert 'CC_WC18_EN' not in currencies
        assert 'CC_WC18_PL' not in currencies
        assert 'CC_WC18_SN' not in currencies
        assert 'CC_WC18_CO' not in currencies
        assert 'CC_WC18_JP' not in currencies
        assert 'CC_WC18_Ball' not in currencies


gc.disable()
unittest.main()
