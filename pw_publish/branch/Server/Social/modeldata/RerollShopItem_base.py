# -*- coding: utf-8 -*-
import sys, time, math
from enums import ERerollShopResources
from base.helpers import *
from binascii import crc32

class RerollShopItem_base(object):
    def serializeToFile(self, file, name):
        pass

    def rollNewItem(self, groupId, SD, config):
        rollGroup = SD.getStaticRerollShopGroupById(groupId)
        if rollGroup:
            slotId = SD.getValueInRange(random.randint(0, len(rollGroup['slots']['Item'])-1), 0,
                                        len(rollGroup['slots']['Item'])-1)
            rerollSlot = rollGroup['slots']['Item'][slotId]
            self.PersistentId = crc32(rerollSlot['slot']['persistentId'])
            self.GroupId = groupId
            self.IsBought = False
            self.NumBought = 0
            self.RandomItemId = 0
            # если нет оверрайдов для валюты, найдем стандартную цену
            if rerollSlot['currencies'] == 0:
                priceTypes = self.getRerollPriceType(rollGroup['currencies'])
            # если есть, возьмём из описания слота
            else:
                priceTypes = self.getRerollPriceType(rerollSlot['currencies'])
            if len(priceTypes) > 0:
                priceTypeIdx = SD.getValueInRange(random.randint(0, len(priceTypes) - 1), 0, len(priceTypes) - 1)
                self.PriceResource = priceTypes[priceTypeIdx]
            else:
                self.PriceResource = ERerollShopResources.Perl
            # если нет оверрайдов для цен, найдем стандартную цену
            if rerollSlot['minPoints'] == 0:
                priceInPoints = SD.getValueInRange(random.randint(rollGroup['minPoints'], rollGroup['maxPoints']),
                                                   rollGroup['minPoints'], rollGroup['maxPoints'])
            # если есть, возьмём из описания слота
            else:
                priceInPoints = SD.getValueInRange(random.randint(rerollSlot['minPoints'], rerollSlot['maxPoints']),
                                                   rerollSlot['minPoints'], rerollSlot['maxPoints'])

            self.Price = self.getRoundedPrice(priceInPoints, self.PriceResource, SD)

            rerollToUpgradeLevels = config.EventToolsChangeFields.REROLL_SHOP_GROUP_UPGRADE_LEVELS.get(groupId)
            if rerollToUpgradeLevels:
                minLevel = max(1, min(rerollToUpgradeLevels.MinUpgradeLevel, 10))
                maxLevel = max(minLevel, min(rerollToUpgradeLevels.MaxUpgradeLevel, 10))
            self.TalentLevel = SD.getValueInRange(random.randint(minLevel, maxLevel), minLevel, maxLevel)

            if rerollSlot['slot']['classType'] == "TalentsListRerollSlot":
                self.RandomItemId = SD.getValueInRange(random.randint(0, len(rerollSlot['slot']['talents']['Item']) - 1), 0, len(rerollSlot['slot']['talents']['Item']) - 1)


        else:
            err("Reroll group with id %r not found", groupId)

    def getRerollPriceType(self, availableTypes):
        priceTypes = []
        if availableTypes & 1 != 0:
            priceTypes.append(ERerollShopResources.Resource1)
        if availableTypes & 2 != 0:
            priceTypes.append(ERerollShopResources.Resource2)
        if availableTypes & 4 != 0:
            priceTypes.append(ERerollShopResources.Resource3)
        if availableTypes & 8 != 0:
            priceTypes.append(ERerollShopResources.Perl)
        if availableTypes & 16 != 0:
            priceTypes.append(ERerollShopResources.RedPerl)
        if availableTypes & 32 != 0:
            priceTypes.append(ERerollShopResources.Silver)
        if availableTypes & 64 != 0:
            priceTypes.append(ERerollShopResources.Gold)
        return priceTypes

    def getRoundedPrice(self, priceInPoints, priceType, SD):
        priceConversion = SD.getResourcesToPointsConversionByPriceType(priceType)
        intPrice = math.ceil(priceInPoints / priceConversion['priceInPoints'])
        if intPrice % priceConversion['roundToDigits'] != 0:
            intPrice += priceConversion['roundToDigits'] - (intPrice % priceConversion['roundToDigits'])
        intPrice = max(1, intPrice)
        return intPrice