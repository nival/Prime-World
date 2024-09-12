# -*- coding: utf-8 -*-

class SeasonEvent_base(object):
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

        _dict['ShopCurrencyId'] = db_dict.get('shopCurrencyId', '')
        _dict['RewardsCurrencyId'] = db_dict.get('rewardsCurrencyId', '')
        _dict['Guid'] = db_dict.get('guid', -1)
        _dict['CompletionTalentId'] = db_dict.get('completionTalentId', '')
        _dict['CompletionTalentRatio'] = db_dict.get('completionTalentRatio', -1)
        _dict['RewardsBlockTitle'] = db_dict.get('rewardsBlockTitle', '')

        _dict['BannerUrl'] = db_dict.get('bannerUrl', '')

        shopGroups = _dict['SeasonEventShopGroups']
        groupsData = db_dict.get('shopGroups', [])
        for item_data in enumerate(groupsData):
            item, _ = config_data.newSeasonEventShopGroup()
            item.load_from_db_dict(config_data, item_data[1])
            shopGroups.add(item_data[0], item)

        progressRelations = _dict['ProgressRewardRelations']
        progressRelationsData = db_dict.get('progressRewardRelations', [])
        for item_data in enumerate(progressRelationsData):
            item, _ = config_data.newSeasonProgressRewardRelation()
            item.load_from_db_dict(config_data, item_data[1])
            progressRelations.add(item_data[0], item)

        ratingRewardRelations = _dict['WorldRatingRewardRelations']
        ratingRewardRelationsData = db_dict.get('worldRatingRewardRelations', [])
        for item_data in enumerate(ratingRewardRelationsData):
            item, _ = config_data.newWorldRatingRewardRelation()
            item.load_from_db_dict(config_data, item_data[1])
            ratingRewardRelations.add(item_data[0], item)