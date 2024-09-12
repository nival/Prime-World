# -*- coding: utf-8 -*-
from base.helpers import *
addModPath("thrift_pw/account_management/gen-py")
from AccountManagementAPI.ttypes import ConfigEventType

'''
удаляет кастомную валюту из профайла за первый TradeEvent
логика удаления валюты была добавлена после первого евента, поэтому для 1го евента завели этот скрипт
https://devjira.nivalnetwork.com/browse/PF-107368
'''

class RemoveCustomCurrenciesForFirstTradeEvent:

    FIRST_TRADE_EVENT_GUID = 1
    FIRST_TRADE_EVENT_CURRENCIES = [
        'CC_WC18_Ball',
        'CC_WC18_RU',
        'CC_WC18_SA',
        'CC_WC18_EG',
        'LB_WC18_A4',
        'CC_WC18_UY',
        'CC_WC18_PT',
        'CC_WC18_ES',
        'CC_WC18_MA',
        'CC_WC18_IR',
        'LB_WC18_C1',
        'CC_WC18_FR',
        'CC_WC18_AU',
        'CC_WC18_PE',
        'CC_WC18_DK',
        'CC_WC18_AR',
        'CC_WC18_IS',
        'CC_WC18_HR',
        'CC_WC18_NG',
        'CC_WC18_BR',
        'CC_WC18_CH',
        'CC_WC18_CR',
        'CC_WC18_RS',
        'CC_WC18_DE',
        'CC_WC18_MX',
        'CC_WC18_SE',
        'CC_WC18_KR',
        'CC_WC18_BE',
        'CC_WC18_PA',
        'CC_WC18_TN',
        'CC_WC18_EN',
        'CC_WC18_PL',
        'CC_WC18_SN',
        'CC_WC18_CO',
        'CC_WC18_JP']

    def convertModelData(self, env, acc, md, dict):
        is_progression_exist = self.FIRST_TRADE_EVENT_GUID in md.TradeEvents
        locale = md.getUserLocale(acc)
        def event_filter(e):
            return e['type'] == ConfigEventType.TradeEvent \
                   and e['newValue'].get('local', '').lower() == locale \
                   and e['newValue'].get('guid', -1) == self.FIRST_TRADE_EVENT_GUID
        is_event_data_exist = False
        if 'finishedEvents' in env.I.WS.operatorEvents:
            is_event_data_exist = any(e for _, e in env.I.WS.operatorEvents['finishedEvents'].iteritems() if event_filter(e))
        will_processed = is_progression_exist and is_event_data_exist
        if will_processed:
            # есть data, есть progression - сервер сможет нормально обработать завершение евента
            return md, acc.db

        currencies = acc.model.Resources.Currencies
        for cur in self.FIRST_TRADE_EVENT_CURRENCIES:
            if cur not in currencies:
                continue
            currencies.remove(cur)

        return md, acc.db
