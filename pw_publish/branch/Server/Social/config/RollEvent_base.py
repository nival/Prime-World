# -*- coding: utf-8 -*-

from modeldata.collects import SimpleList, Set
from RollEventRule import RollEventRule


class RollEvent_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, persistent_id, end_time, db_dict):
        """

        :param persistent_id:
        :type persistent_id: int
        :param end_time:
        :type end_time: int
        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict

        _dict['_modelChangeWriter'] = None
        _dict['_writeChanges'] = False

        _dict['PersistentId'] = persistent_id
        _dict['EndTimestamp'] = end_time
        _dict['CompletionTalentPersistentId'] = db_dict.get('completionTalentId', '')
        _dict['Text'] = db_dict.get('text', '')
        _dict['Title'] = db_dict.get('title', '')
        _dict['Image'] = db_dict.get('image', '')
        _dict['Guid'] = db_dict.get('guid', -1)

        currency_ids = _dict['CurrencyIds']  # type: SimpleList
        for item_data in db_dict.get('currencyIds'):  # type: str
            currency_ids.append(item_data)

        rolls = _dict['Rolls']  # type: Set
        for item_data in db_dict.get('rolls'):  # type: dict
            item, _ = config_data.newRollEventRule()
            item.load_from_db_dict(config_data, item_data)
            rolls.add(item)
