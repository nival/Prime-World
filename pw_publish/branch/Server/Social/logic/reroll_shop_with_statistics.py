# -*- coding: utf-8 -*-
import sys
from subaction import *
import subprocess
from logic.requests.RerollShopWithStatisticsRequest import *
import CC
from RerollHelper import RerollHelper
import csv
import sys

class Reroll_shop_with_statistics( SubAction, RerollShopWithStatisticsRequest ):
    action = "reroll_shop_with_statistics"
    debug = True
    fieldnames = ['group',  'item id', 'slot id', 'amount', 'min res1', 'max res1', 'min res2', 'max res2', 'min res3',
                  'max res3', 'min silver', 'max silver', 'min gold', 'max gold', 'min perl', 'max perl', 'min redperl',
                  'max redperl']
    groupFieldnames = ['group', 'items']

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        if self.arguments.dumpConfig:
            rerollsPath = os.path.join( os.path.dirname(os.path.realpath(__file__)), "testEnv","Rerolls.txt")
            info("Reroll_shop_with_statistics.onStart rerolls path = %r", rerollsPath)
            logFile = open(rerollsPath, "w")
            logFile.write(str(self.arguments.totalRerolls))
            logFile.close()
            flePath = os.path.join( os.path.dirname(os.path.realpath(__file__)), "testEnv","all_test.py")
            info("Reroll_shop_with_statistics.onStart flePath = %r", flePath)
            fileDir = os.path.join( os.path.dirname(os.path.realpath(__file__)), "testEnv")
            info("Reroll_shop_with_statistics.onStart fileDir = %r", fileDir)
            testprocess = subprocess.Popen([sys.executable, flePath,
                              "reroll_shop_with_statistics_test:reroll_shop_with_statistics_subprocess_test"],
                             stdout=subprocess.PIPE, cwd=fileDir)
            self.response["ok"] = 1
            self.fin()
            return

        t1 = int(time.time())
        self.acc.model.RerollShopInfo.RerollsToday = 0
        self.acc.model.RerollShopInfo.checkSize(self.acc.model, self.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS,
                                                self.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS)
        rerollHelper = RerollHelper(self.acc.SD)
        rolledItems = {}
        rolledGroups = {}
        if self.arguments.totalRerolls == 0:
            rerollHelper.resetProbabilities(self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES],
                                            self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                            self.acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES], 0, self.acc.getConfig())

            count = -1
            totalItems = 0
            for groupId in self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS].keys():
                rolledItems[int(groupId)] = {}
                rolledGroups[int(groupId)] = 0
                totalItems += self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS][groupId]
            while totalItems:
                for _id, item in self.acc.model.RerollShopInfo.ShopItems.iteritems():
                    if rerollHelper.needRerollProbabilities(self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES],
                                                            self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                                            self.acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES],
                                                            self.acc.getConfig()):
                        rerollHelper.resetProbabilities(self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES],
                                                        self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                                        self.acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES],
                                                        0, self.acc.getConfig())
                    groupId = rerollHelper.getNewGroup(self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES], self.acc)
                    item.rollNewItem(groupId, self.acc.SD, self.acc.getConfig())
                    staticItem = self.acc.SD.getStaticRerollShopItemById(item.PersistentId)
                    staticGroup = self.acc.SD.getStaticRerollShopGroupById(groupId)
                    price = self.acc.model.getRerollShopItemPrice(item.PriceResource, item.Price)
                    if staticItem['classType'] in ["ResourceRerollSlot", "PremiumRerollSlot"]:
                        if staticItem['persistentId'] not in rolledItems[groupId]:
                            rolledItems[groupId][staticItem['persistentId']] = {"slot id": "",
                                        "group": staticGroup['persistentId'], "item id": staticItem['persistentId']}
                            self.updateNewItem(rolledItems[groupId][staticItem['persistentId']], price)
                        else:
                            self.updateExistingItem(rolledItems[groupId][staticItem['persistentId']], price)
                    if staticItem['classType'] == "TalentsListRerollSlot":
                        staticTalent = staticItem['talents']['Item'][item.RandomItemId]
                        if staticTalent['persistentId'] not in rolledItems[groupId]:
                            rolledItems[groupId][staticTalent['persistentId']] = {"slot id": staticItem['persistentId'],
                                        "group": staticGroup['persistentId'], "item id": staticTalent['persistentId']}
                            self.updateNewItem(rolledItems[groupId][staticTalent['persistentId']], price)
                        else:
                            self.updateExistingItem(rolledItems[groupId][staticTalent['persistentId']], price)
                    rolledGroups[groupId] += 1
                    totalItems -= 1
                    if not totalItems:
                        break
                count += 1
            info("TotalRerolls: %d", count)
            filename = 'reroll_fullBasket.csv'
            groupsFilename = 'reroll_groups_fullBasket.csv'
        else:
            for groupId in self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS].keys():
                rolledItems[int(groupId)] = {}
                rolledGroups[int(groupId)] = 0
            for i in xrange(0, self.arguments.totalRerolls):
                for _id, item in self.acc.model.RerollShopInfo.ShopItems.iteritems():
                    if rerollHelper.needRerollProbabilities(self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES],
                                                            self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                                            self.acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES],
                                                            self.acc.getConfig()):
                        rerollHelper.resetProbabilities(self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES],
                                                        self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                                        self.acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES],
                                                        0, self.acc.getConfig())
                    groupId = rerollHelper.getNewGroup(self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES], self.acc)
                    item.rollNewItem(groupId, self.acc.SD, self.acc.getConfig())
                    staticItem = self.acc.SD.getStaticRerollShopItemById(item.PersistentId)
                    staticGroup = self.acc.SD.getStaticRerollShopGroupById(groupId)
                    price = self.acc.model.getRerollShopItemPrice(item.PriceResource, item.Price)
                    if staticItem['classType'] in ["ResourceRerollSlot", "PremiumRerollSlot"]:
                        if staticItem['persistentId'] not in rolledItems[groupId]:
                            rolledItems[groupId][staticItem['persistentId']] = {"slot id": "",
                                        "group": staticGroup['persistentId'], "item id": staticItem['persistentId']}
                            self.updateNewItem(rolledItems[groupId][staticItem['persistentId']], price)
                        else:
                            self.updateExistingItem(rolledItems[groupId][staticItem['persistentId']], price)
                    if staticItem['classType'] == "TalentsListRerollSlot":
                        staticTalent = staticItem['talents']['Item'][item.RandomItemId]
                        if staticTalent['persistentId'] not in rolledItems[groupId]:
                            rolledItems[groupId][staticTalent['persistentId']] = {"slot id": staticItem['persistentId'],
                                        "group": staticGroup['persistentId'], "item id": staticTalent['persistentId']}
                            self.updateNewItem(rolledItems[groupId][staticTalent['persistentId']], price, item.TalentLevel)
                        else:
                            self.updateExistingItem(rolledItems[groupId][staticTalent['persistentId']], price, item.TalentLevel)
                    rolledGroups[groupId] += 1
            filename = 'reroll_%d_times.csv' % self.arguments.totalRerolls
            groupsFilename = 'reroll_groups_%d_times.csv' % self.arguments.totalRerolls
        try:
            with open(filename, 'w') as csvfile:
                writer = csv.DictWriter(csvfile, fieldnames=self.fieldnames)
                writer.writeheader()
                for groupId in rolledItems:
                    for itemId in rolledItems[groupId]:
                        writer.writerow(rolledItems[groupId][itemId])
            with open(groupsFilename, 'w') as csvfile:
                writer = csv.DictWriter(csvfile, fieldnames=self.groupFieldnames)
                writer.writeheader()
                for groupId in rolledGroups:
                    staticGroup = self.acc.SD.getStaticRerollShopGroupById(groupId)
                    writer.writerow({"group": staticGroup['persistentId'], "items": rolledGroups[groupId]})
            with open(filename + "_time.txt", 'w') as timeFile:
                t2 = int(time.time()) - t1
                timeFile.write(str(t2))
        except IOError as (errno, strerror):
                print("I/O error({0}): {1}".format(errno, strerror))
        self.response["ok"] = 1
        self.fin()

    def updateNewItem(self, dictValue, price, level):
        dictValue.update({"amount": 1, "min res1": price.Resource1, "max res1": price.Resource1,
                          "min res2": price.Resource2, "max res2": price.Resource2, "min res3": price.Resource3,
                          "max res3": price.Resource3, "min silver": price.Silver, "max silver": price.Silver,
                          "min perl": price.Perl, "max perl": price.Perl, "min redperl": price.RedPerl,
                          "max redperl": price.RedPerl, "min gold": price.Gold, "max gold": price.Gold, "level": level})

    def updateExistingItem(self, dictValue, price, level):
        dictValue["amount"] += 1
        dictValue["level"] = level
        if (price.Resource1 < dictValue["min res1"] and price.Resource1 > 0) or dictValue["min res1"] == 0:
            dictValue["min res1"] = price.Resource1
        if price.Resource1 > dictValue["max res1"] and price.Resource1 > 0:
            dictValue["max res1"] = price.Resource1
        if price.Resource2 < dictValue["min res2"] and price.Resource2 > 0 or dictValue["min res2"] == 0:
            dictValue["min res2"] = price.Resource2
        if price.Resource2 > dictValue["max res2"] and price.Resource2 > 0:
            dictValue["max res2"] = price.Resource2
        if price.Resource3 < dictValue["min res3"] and price.Resource3 > 0 or dictValue["min res3"] == 0:
            dictValue["min res3"] = price.Resource3
        if price.Resource3 > dictValue["max res3"] and price.Resource3 > 0:
            dictValue["max res3"] = price.Resource3
        if price.Silver < dictValue["min silver"] and price.Silver > 0 or dictValue["min silver"] == 0:
            dictValue["min silver"] = price.Silver
        if price.Silver > dictValue["max silver"] and price.Silver > 0:
            dictValue["max silver"] = price.Silver
        if price.Perl < dictValue["min perl"] and price.Perl > 0 or dictValue["min perl"] == 0:
            dictValue["min perl"] = price.Perl
        if price.Perl > dictValue["max perl"] and price.Perl > 0:
            dictValue["max perl"] = price.Perl
        if price.RedPerl < dictValue["min redperl"] and price.RedPerl > 0 or dictValue["min redperl"] == 0:
            dictValue["min redperl"] = price.RedPerl
        if price.RedPerl > dictValue["max redperl"] and price.RedPerl > 0:
            dictValue["max redperl"] = price.RedPerl
        if price.Gold < dictValue["min gold"] and price.Gold > 0 or dictValue["min gold"] == 0:
            dictValue["min gold"] = price.Gold
        if price.Gold > dictValue["max gold"] and price.Gold > 0:
            dictValue["max gold"] = price.Gold