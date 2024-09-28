# -*- coding: utf-8 -*-
# Automatically generated template file. Remove this string if you modify this file.

class QuestEvent_base(object):
    def serializeToFile(self, file, name):
        pass

    def load_from_db_dict(self, config_data, persistent_id, end_time, db_dict):
        _dict = self.__dict__

        _dict['_modelChangeWriter'] = None
        _dict['_writeChanges'] = False

        _dict['Title'] = db_dict.get('title', '')
        _dict['Text'] = db_dict.get('text', '')
        _dict['PersistentId'] = persistent_id
        _dict['EndTimestamp'] = end_time
        _dict['Guid'] = db_dict.get('guid', -1)

        currency_ids = _dict['CurrencyIds']  # type: SimpleList
        for item_data in db_dict.get('currencyIds', []):  # type: str
            currency_ids.append(item_data)

        stages = _dict['Stages']
        stages_data = db_dict.get('stages', [])
        for item_data in enumerate(stages_data):
            item, _ = config_data.newQuestEventStage()
            item.load_from_db_dict(config_data, item_data[1])
            stages.add(item_data[0], item)

    def unwrap_index(self, index):
        if index < 0:
            return -1, -1
        step_index = index
        stages_len = len(self.Stages)
        for stage_index in range(stages_len):
            stage = self.Stages[stage_index]
            steps_len = len(stage.Steps)
            if step_index < steps_len:
                return stage_index, step_index
            step_index -= steps_len
        return -1, -1

    def wrap_index(self, stage_index, step_index):
        if stage_index < 0 or step_index < 0:
            return -1
        if stage_index == 0:
            return step_index
        result_index = 0
        for i in range(stage_index):
            stage = self.Stages[i]
            result_index += len(stage.Steps)
        result_index += step_index
        return result_index
