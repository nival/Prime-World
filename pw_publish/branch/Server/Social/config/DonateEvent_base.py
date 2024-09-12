# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.

class DonateEvent_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, persistent_id, end_time, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__  # type: dict

        _dict['PersistentId'] = persistent_id
        _dict['EndTimestamp'] = end_time

        ranges = _dict['Ranges']  # type: Set

        for item_data in db_dict.get('ranges', []):
            item, _ = config_data.newDonateEventRange()
            item.load_from_db_dict(config_data, item_data)
            ranges.add(item)
