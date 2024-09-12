# -*- coding: utf-8 -*-
import CC

class RerollShop_base(object):
    def serializeToFile(self, file, name):
        pass

    def checkSize(self, md, ordinarySlots, premiumSlots):
        ordinaryItems = 0
        premiumItems = 0

        while len(self.ShopItems) < (ordinarySlots + premiumSlots):
            rerollShopItem ,_id = md.newRerollShopItem()
            self.ShopItems.add(rerollShopItem)
        while len(self.ShopItems) > (ordinarySlots + premiumSlots):
            for _id, item in self.ShopItems.items():
                self.ShopItems.remove(item)
                break

        for _id, item in self.ShopItems.iteritems():
            if item.IsPremium:
                premiumItems += 1
            else:
                ordinaryItems += 1

        # first of all, let's check if we have enough slots for ordinary and premium items
        while ordinarySlots > ordinaryItems:
            for _id, item in self.ShopItems.iteritems():
                if item.IsPremium:
                    item.IsPremium = False
                    premiumItems -= 1
                    ordinaryItems += 1
                    break
        while ordinarySlots < ordinaryItems:
            for item_id, item in self.ShopItems.items():
                if not item.IsPremium:
                    item.IsPremium = True
                    ordinaryItems -= 1
                    premiumItems += 1
                    break

        while premiumSlots > premiumItems:
            for _id, item in self.ShopItems.iteritems():
                if not item.IsPremium:
                    item.IsPremium = True
                    premiumItems += 1
                    break
        while premiumSlots < premiumItems:
            for item_id, item in self.ShopItems.items():
                if item.IsPremium:
                    item.IsPremium = False
                    premiumItems -= 1
                    break


    # def rerollItems(self, rollProbabilities, acc):
    #     for _id, item in self.ShopItems.iteritems():
    #         oldItemId = item.PersistentId
    #         oldItemPriceType = item.PriceResource
    #         oldItemPrice = item.Price
    #
    #         item.rollNewItem(rollProbabilities)
    #         if item.PersistentId == oldItemId and oldItemPriceType == item.PriceResource and oldItemPrice == item.Price:
    #             item.rollNewItem()
