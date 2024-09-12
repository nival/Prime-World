# -*- coding: utf-8 -*-
from base.helpers import *
import datetime
from modeldata.baseclasses import *
from guild.GuildWarsDataCustom import GuildWarsDataCustom

class SiegeDataCustom(BaseObject):

    def __init__(self):
        self.__dict__["_modelChangeWriter"] = None
        self.__dict__["_writeChanges"] = False
        self.__dict__["_comment"] = "auto"

    def save( self, save_data=None ):
        save_data = save_data or self.generateJsonDict()
        return json_dumps( save_data )


    def load( self, data ):
        if isinstance(data, basestring):
            data = json_loads( data )
        t0 = time.clock() # #############
        self._serializator.fromDict( data )
        t1 = time.clock() # #############
        info( "_serializator.fromDict time: %.3f" % (t1-t0) )


    def dump_file( self, filename ):
        f = open(filename, "wt")
        if f:
            save_dict = self.generateJsonDict()
            f.write( pretty(save_dict) )


    # IChangeWriter
    def modelChange( self, path, op, val ):
        if self._modelChangeWriter:
            self._modelChangeWriter.writeStringToResponse( self.__class__.__name__, self._comment, path, op, val )


    def canWrite( self ):
        return self._modelChangeWriter


    def setComment( self, name ):
        self._comment = str(name)


    # включаем авто-запись изменений в нашей ModelData (в указанный changeWriter)
    def write( self, changeWriter ):
        self._modelChangeWriter = changeWriter
        self._writeChanges = (changeWriter is not None)

    # дополнительные (server-side) сериализуемые поля
    def generateBaseDict(self):
        return dict(
            next_uid_ = self.next_uid_
        )

    def update(self, data_json):
        participants = []
        try:
            for siegeInfo in data_json:
                if len(siegeInfo["participants"]) >= 2:
                    s = self.getSiegeById( siegeInfo["_id"])
                    if not s:
                        siege, siegeId = self.newSiege()
                        siege.EndTime = siegeInfo["end_time"]
                        siege.Uid = siegeInfo["_id"]
                        for participant in siegeInfo["participants"]:
                            attacker, attackerId = self.newSiegeGuildInfo()
                            shortInfo, si_id = self.newGuildShortInfo()
                            attacker.ShortInfo = shortInfo
                            attacker.ShortInfo.GuildAuid = participant["id"]
                            participants.append(attacker.ShortInfo.GuildAuid)
                            attacker.SiegePoints = participant["score"]
                            siege.Participants.add(attacker)
                        siege.Target, targetId = self.newSiegeGuildInfo()
                        shortInfo, si_id = self.newGuildShortInfo()
                        siege.Target.ShortInfo = shortInfo
                        siege.Target.ShortInfo.GuildAuid = siegeInfo["target"]
                        siege.IsLocked = siegeInfo["status"] == "locked"
                        if siege.Target.ShortInfo.GuildAuid not in participants:
                            participants.append(siege.Target.ShortInfo.GuildAuid)

                        self.ActiveSieges.add(siege)
                    else:
                        #удалим старых участников
                        for guildInfoId, guildInfo in s.Participants.items():
                            self.deleteByID(guildInfo.ShortInfo.getID())
                            s.Participants.remove(guildInfo)
                        #добавим новых
                        for participant in siegeInfo["participants"]:
                            attacker, attackerId = self.newSiegeGuildInfo()
                            shortInfo, si_id = self.newGuildShortInfo()
                            attacker.ShortInfo = shortInfo
                            attacker.ShortInfo.GuildAuid = participant["id"]
                            participants.append(attacker.ShortInfo.GuildAuid)
                            attacker.SiegePoints = participant["score"]
                            s.Participants.add(attacker)

                else:
                    err("Bad siege data! Count of participants is %r " % len(siegeInfo["participants"]))
        except Exception():
            catch()
            return []
        return participants

    # Находим все гильдии, которые так или иначе относятся к текущим осадам
    def getAllParticipants(self):
        participants = []
        for siegeId, siege in self.SiegeGuildInfoKeeper.iteritems():
            if siege.GuildAuid not in participants:
                participants.append(siege.GuildAuid)
        return participants

    def updateGuildInfoFromSQL(self, guildInfoResponse):
        for guildInfoId, guildInfo in self.SiegeGuildInfoKeeper.iteritems():
            if guildInfo.ShortInfo.GuildAuid == guildInfoResponse.guild_id:
                guildInfo.ShortInfo.GuildShortName = guildInfoResponse.guild_short_name
                guildInfo.ShortInfo.GuildFullName = guildInfoResponse.guild_name

                guildInfo.ShortInfo.Level = guildInfoResponse.guild_level
                guildInfo.ShortInfo.Rating = guildInfoResponse.rating
                guildInfo.ShortInfo.Place = guildInfoResponse.position
                guildInfo.ShortInfo.RatingPositionChange = GuildWarsDataCustom.GetRatingPositionChange(guildInfoResponse.position_change)
                guildInfo.ShortInfo.ShopLevel = guildInfoResponse.shop_level

                guildInfo.ShortInfo.MembersCount = guildInfoResponse.num_members
                guildInfo.ShortInfo.IconChangesCount = guildInfoResponse.icon_revision

    def removeSiege(self, persistentId):
        for siegeId, siege in self.ActiveSieges.items():
            if siege.Uid == persistentId:
                self.ActiveSieges.remove(siege)
                return

    def addParticipant(self, persistentId, guildAuid):
        for siegeId, siege in self.ActiveSieges.iteritems():
            if siege.Uid == persistentId:
                attacker, attackerId = self.newSiegeGuildInfo()
                attacker.ShortInfo, si_id = self.newGuildShortInfo()
                attacker.ShortInfo.GuildAuid = guildAuid
                attacker.SiegePoints = 0
                siege.Participants.add(attacker)
                return


    def removeParticipant(self, persistentId, guildAuid):
        for siegeId, siege in self.ActiveSieges.iteritems():
            if siege.Uid == persistentId:
                for guildInfoId, guildInfo in siege.Participants.items():
                    if guildInfo.ShortInfo.GuildAuid == guildAuid:
                        self.deleteByID(guildInfo.ShortInfo.getID())
                        siege.Participants.remove(guildInfo)
                        return

    def updateScore(self, persistentId, guildAuid, score):
        for siegeId, siege in self.ActiveSieges.iteritems():
            if siege.Uid == persistentId:
                for guildInfoId, guildInfo in siege.Participants.iteritems():
                    if guildInfo.ShortInfo.GuildAuid == guildAuid:
                        guildInfo.SiegePoints = score
                        return

    def isTarget(self, targetAuid ):
        for siegeId, siege in self.ActiveSieges.iteritems():
            if siege.Target.ShortInfo.GuildAuid == targetAuid:
                return True

    def getPendingSiege(self, initiatedSieges):
        siegeIds = [siege.SiegeId for siegeId, siege in initiatedSieges.items()]
        for siegeId, siege in self.ActiveSieges.iteritems():
            # Проверим, что осада уже закончилась и что мы её инициировали
            if siege.IsLocked and siege.Uid in siegeIds:
                return siege
        return None

    def getSiegeById(self, persistentId):
        for siegeId, siege in self.ActiveSieges.iteritems():
            if siege.Uid == persistentId:
                return siege

    def getSiegeByTargetId(self, targetAuid):
        for siegeId, siege in self.ActiveSieges.iteritems():
            if siege.Target.ShortInfo.GuildAuid == targetAuid:
                return siege

    def lockSiegeByTargetId(self, targetAuid):
        for siegeId, siege in self.ActiveSieges.iteritems():
            if siege.Target.ShortInfo.GuildAuid == targetAuid:
                siege.IsLocked = True