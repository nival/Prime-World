#!/usr/bin/env python

from modeldata.collects import SimpleDict


class ResourceTable_base:
    def iteritems(self):
        for k in self._changeFields.keys():
            yield (k, self.__dict__.get(k))

    def load_from_db_dict(self, db_dict):
        """

        :param db_dict:
        :type db_dict: dict
        :return:
        """
        _dict = self.__dict__
        _dict["Resource1"] = db_dict.get("resource1", 0)
        _dict["Resource2"] = db_dict.get("resource2", 0)
        _dict["Resource3"] = db_dict.get("resource3", 0)
        _dict["Silver"] = db_dict.get("silver", 0)
        _dict["Gold"] = db_dict.get("gold", 0)
        _dict["Perl"] = db_dict.get("perl", 0)
        _dict["RedPerl"] = db_dict.get("redPerl", 0)
        currency_id = db_dict.get('currencyId', '')
        currency_value = db_dict.get('currency', 0)
        if currency_id != '' and currency_value != 0:
            currencies = _dict['Currencies']  # type: SimpleDict
            currencies.add(currency_id, currency_value)

    def load_from_sd_dict(self, sd_price):
        self.Gold = sd_price.Gold
        self.Perl = sd_price.Perl
        self.RedPerl = sd_price.RedPerl
        self.Resource1 = sd_price.Resource1
        self.Resource2 = sd_price.Resource2
        self.Resource3 = sd_price.Resource3
        self.Silver = sd_price.Silver
        self.Population = sd_price.Population
        self.Resource1_Rare = sd_price.Resource1_Rare
        self.Resource2_Rare = sd_price.Resource2_Rare
        self.Resource3_Rare = sd_price.Resource3_Rare
        self.CWPoints_Clan = sd_price.CWPoints_Clan
        self.CWPoints_Player = sd_price.CWPoints_Player
        self.Shard = sd_price.Shard
        for cc in sd_price.Currencies:
            self.Currencies[cc] = sd_price.Currencies[cc]
