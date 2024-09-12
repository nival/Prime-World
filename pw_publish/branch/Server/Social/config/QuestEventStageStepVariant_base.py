# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.

class QuestEventStageStepVariant_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, db_dict):
        _dict = self.__dict__
        _dict['Message'] = db_dict.get('message', '')
        _dict['WinMessage'] = db_dict.get('winMessage', '')
        _dict['LoseMessage'] = db_dict.get('loseMessage', '')
        price = _dict['Price']
        price_dict = db_dict.get('price', {})
        price.load_from_db_dict(price_dict)
        _dict['WinRatioBase'] = db_dict.get('winRatioBase', 0)
        _dict['WinRatioGold'] = db_dict.get('winRatioGold', 0)
