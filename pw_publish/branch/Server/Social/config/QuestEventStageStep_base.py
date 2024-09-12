# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.

class QuestEventStageStep_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, db_dict):
        _dict = self.__dict__
        _dict['Title'] = db_dict.get('title', '')

        vars = _dict['Variants']
        vars_data = db_dict.get('variants', [])
        for item_data in enumerate(vars_data):
            item, _ = config_data.newQuestEventStageStepVariant()
            item.load_from_db_dict(item_data[1])
            vars.add(item_data[0], item)
