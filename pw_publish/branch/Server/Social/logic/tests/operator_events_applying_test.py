import sys
from modeldata.SharedTypes.ResourceTable import ResourceTable
from modeldata.collects import SimpleDict
sys.path.append('../')
sys.path.append('../../')


class operator_events_applying_test:

    def __init__(self):
        pass

    def __generate_event(self, **kwargs):
        custom_data = dict(locale=kwargs['locale'],
                           currencyIds=kwargs['currencies'],
                           completionTalentId=kwargs.get('talent', ''),
                           completionTalentRatio=kwargs.get('ratio', 1))
        result = dict(persistentId=kwargs['pid'],
                      endTime=kwargs['time'],
                      type=kwargs['type'],
                      newValue=custom_data)
        return result

    def validate_finish_roll_events(self, env):
        model_data = env.acc.model

        # Prepare currencies
        currencies = model_data.Resources.Currencies  # type: SimpleDict
        currencies['BTC'] = 10
        currencies['JPY'] = 15
        currencies['USD'] = 30

        # Prepare events
        webservice = env.I.WS
        webservice.operatorEvents = {"finishedEvents": {}}
        events = webservice.operatorEvents["finishedEvents"]
        event = self.__generate_event(pid=1, time=100, type=21, currencies=['BTC'], talent='G322', locale='RU')
        events[event["persistentId"]] = event
        event = self.__generate_event(pid=5, time=1400, type=21, currencies=['BTC'], locale='RU')
        events[event["persistentId"]] = event
        event = self.__generate_event(pid=10, time=1500, type=21, currencies=['BTC'], talent='G323', locale='RU')
        events[event["persistentId"]] = event
        event = self.__generate_event(pid=15, time=1600, type=21, currencies=['BTC'], talent='G324', locale='EN')
        events[event["persistentId"]] = event
        event = self.__generate_event(pid=17, time=1900, type=20, currencies=['BTC'], talent='G325', locale='RU')
        events[event["persistentId"]] = event
        event = self.__generate_event(pid=18, time=1950, type=21, currencies=['JPY'], locale='RU')
        events[event["persistentId"]] = event
        event = self.__generate_event(pid=19, time=1900, type=22, currencies=['USD'], ratio=6, talent='G326', locale='RU')
        events[event['persistentId']] = event

        initial_inventory_len = len(model_data.UserInventory)

        assert len(model_data.Resources.Currencies) == 3
        model_data.applyCompletedOperatorEvents(env.acc, env.I.WS, env.I.STATS)
        assert len(model_data.Resources.Currencies) == 1
        assert model_data.Resources.Currencies['JPY'] == 15
        assert len(model_data.UserInventory) == initial_inventory_len + 15
