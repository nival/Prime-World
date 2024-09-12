# -*- coding: utf-8 -*-
#!/usr/bin/env python
import sys, time, json

from modeldata.jsonserialize import JSONSerialization
from base.helpers import *
from modeldata.baseclasses import *

class GuildDataCustom( BaseObject ):
    def __init__(self):
        self.__dict__["_modelChangeWriter"] = None
        self.__dict__["_writeChanges"] = False

    def save( self, save_data=None ):
        self._serializator.setMode( False ) # For server side
        save_data = save_data or self.generateJsonDict()
        return json_dumps( save_data )

    def load( self, data ):
        if isinstance(data, basestring):
            data = json_loads( data )
        self._serializator.fromDict( data )

    # IChangeWriter
    def modelChange( self, path, op, val ):
        if self._modelChangeWriter:
            self._modelChangeWriter.writeStringToResponse( self.__class__.__name__, "auto", path, op, val )

    # включаем авто-запись изменений в нашей ModelData (в указанный changeWriter)
    def write( self, changeWriter ):
        self._modelChangeWriter = changeWriter
        self._writeChanges = (changeWriter is not None)

    # отключаем авто-запись изменений в нашей ModelData
    def stop( self ):
        self._modelChangeWriter = None
        self._writeChanges = False

    # эмулируем доступ к элементу как у словаря, чтобы работал поиск по абсолютным путям
    def get( self, key ):
        return self.__dict__.get(key)

    # находим по auid == Person.person_uid == Friend.person_uid
    def findMemberByAuid(self, auid):
        for member_id,member in self.GuildMemberKeeper.iteritems():
            if member.Person == auid:
                return member

    # дополнительные (server-side) сериализуемые поля
    def generateBaseDict(self):
        return dict(
            next_uid_ = self.next_uid_
        )


    def getTopMembersList(self, limit=20):
        # А теперь начнём сложный механизм фильтрации целей
        all_members = []
        result = []
        for member_id, member in self.GuildMemberKeeper.iteritems():
            all_members.append(member)

        # Отсортируем по весу
        all_members.sort(key=lambda memb: memb.EventRating, reverse=True)

        res_sum = 0
        for mem in all_members[:limit]:
            result.append(mem.Person)
            res_sum += mem.EventRating

        debug("getTopMembersList: sum=%s %r", res_sum, result)

        return res_sum, result

    def getAffectedMembersList(self, auid, onlineAuids, staticItem):
        # А теперь начнём сложный механизм фильтрации целей
        allMembers = []
        affectedMembers = []
        holdGuild  =False
        for member_id, member in self.GuildMemberKeeper.iteritems():
            allMembers.append(member)

        if 'Item' in staticItem['target']:
            # сие будем хранить в гильдии
            for target in staticItem['target']['Item']:
                if target['classType'] == "HoldGuild":
                    holdGuild = True
                    break

            # А вдруг, оно всеобщее?
            for target in staticItem['target']['Item']:
                if target['classType'] in ["AllGuildMembers", "HoldGuild"]:
                    for member in allMembers:
                      affectedMembers.append(member.Person)
                    return affectedMembers, holdGuild
            # Сначала выберем себя-любимого
            for target in staticItem['target']['Item']:
                if target['classType'] == "Buyer":
                    affectedMembers.append(auid)
            # Уберём тех, кто оффлайн
            for target in staticItem['target']['Item']:
                if target['classType'] == "OnlineGuildMembers":
                    allMembers = [member for member in allMembers if member.Person in onlineAuids]
            # Уберём людей, которые не проходят по рангу
            for target in staticItem['target']['Item']:
                if target['classType'] == "RankedGuildMembers":
                    allMembers = [member for member in allMembers if member.getBestHeroRating() >= target['minRating'] and  member.getBestHeroRating() <= target['maxRating']]

            if len(allMembers) <= int(staticItem['target']['Item'][0]['NumPlayers']):
                for member in allMembers:
                    affectedMembers.append(member.Person)
                return affectedMembers, holdGuild

            # Отсортируем по весу

            allMembers.sort(key=lambda memb: memb.DailyRating, reverse=True)
            debug("getAffectedMembersList: allMembers %r", [x.Person for x in allMembers])
            for target in staticItem['target']['Item']:
                numPlayers = int(target['NumPlayers'])
                if target['classType'] == "BestGuildInvesters":
                    allMembers = allMembers[:numPlayers]
                    for member in allMembers:
                        affectedMembers.append(member.Person)
                    return affectedMembers, holdGuild
                if target['classType'] == "WorstGuildInvesters":
                    allMembers = allMembers[-numPlayers:]
                    for member in allMembers:
                        affectedMembers.append(member.Person)
                    return affectedMembers, holdGuild

            return affectedMembers, holdGuild
        return affectedMembers, holdGuild

    def hasDiscountForSiege(self, guildAuid, siegeSettings):
        if str(guildAuid) in self.ExVassals:
            if (self.ExVassals[str(guildAuid)] + siegeSettings.TIMEOUT_FOR_EX_VASSAL_CAPTURE +
                  siegeSettings.SIEGE_DURATION) > int(time.time()):
                return True

        for vassalId, vassal in self.RecommendedForMapVassals.iteritems():
            if vassal.ShortInfo.GuildAuid == guildAuid:
                return True
        return False

    def getAllMembers(self):
        memberAuids = []
        for member_id, member in self.GuildMemberKeeper.iteritems():
            memberAuids.append(member.Person)
        return memberAuids

    def getShopOwnerRating(self):
        return self.RatingInfo.Rating

    def checkUltimateShop(self, SD):
        # PF-106814
        # # магазин выдаём только свободным и тем, у кого хватает рейтинга
        # if self.GuildSuzerain.ShortInfo.GuildAuid == 0 and self.RatingInfo.Rating >= SD.data["ClanWarsData"]["shopAncientRating"]:
        #     self.GuildInfo.HasUltimateShop = True
        # else:
        #     self.GuildInfo.HasUltimateShop = False
        self.GuildInfo.HasUltimateShop = True

    def getSiegeStartPrice(self, targetAuid, targetRating, siegeSettings):
        price = siegeSettings.MINIMAL_SIEGE_PARTICIPATION_PRICE + max(targetRating*siegeSettings.SIEGES_START_MULT_COEFF
                                                                      - siegeSettings.SIEGES_START_ADD_COEFF, 0)
        if self.hasDiscountForSiege(targetAuid, siegeSettings):
            price = price*siegeSettings.SIEGE_DISCOUNT

        if price % 10:
            price += 10 - price % 10

        return price

    def hasVassal(self, guildAuid):
        for vassalId, vassal in self.GuildVassals.iteritems():
            if vassal.ShortInfo.GuildAuid == guildAuid:
                return True
        return False

    def removeSiege(self, siegePersistentId):
        try:
            if siegePersistentId in self.ActiveSieges:
                self.ActiveSieges.remove(siegePersistentId)

        except ValueError:
            catchFull()
            err("Siege %s not found in self.ActiveSieges.", siegePersistentId)

        for siegeId, siege in self.InitiatedSieges.items():
            if siege.SiegeId == siegePersistentId:
                self.InitiatedSieges.remove(siege)
                return

    def removeVassal(self, vassal):
        _id = vassal.ShortInfo.getID()
        self.GuildVassals.remove(vassal)
        self.deleteByID(_id)

    def getRatingForRecommendedVassals(self):
        minRating = 0
        if len(self.GuildVassals):
            minRating = min(self.GuildVassals.iteritems(), key=lambda t: t[1].ShortInfo.Rating)
            minRating = minRating[1].ShortInfo.Rating
        return minRating

    def addActiveSiege(self, siegeId):
        if siegeId not in self.ActiveSieges:
            self.ActiveSieges.append(siegeId)