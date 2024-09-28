# -*- coding: utf-8 -*-

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
import time
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import GuildShortInfo

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from enums import RatingPositionChange


class GuildWarsDataCustom( BaseObject ):
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

    # дополнительные (server-side) сериализуемые поля
    def generateBaseDict(self):
        return dict(
            next_uid_ = self.next_uid_
        )

    #конвертация изменния позиции в направление
    @staticmethod
    def GetRatingPositionChange(positionChange):
        res = RatingPositionChange.Equal
        if positionChange < 0:
            res = RatingPositionChange.Decreased
        elif positionChange > 0:
            res = RatingPositionChange.Increased
        return res


    # заполняем GuildShortInfo по результату SQL запроса из tbl_guild_rating
    @staticmethod
    def FillGuildShortInfoFromSQL(guildInfo, sqlRequestResult):
        if "guild_id" in sqlRequestResult:
            guildInfo.ShortInfo.GuildAuid = sqlRequestResult.guild_id

        if "guild_short_name" in  sqlRequestResult:
            guildInfo.ShortInfo.GuildShortName = sqlRequestResult.guild_short_name

        if "guild_name" in sqlRequestResult:
            guildInfo.ShortInfo.GuildFullName = sqlRequestResult.guild_name

        if "siege_end_time" in sqlRequestResult:
            guildInfo.IsInSiege = (sqlRequestResult.siege_end_time > int(time.time()))
            guildInfo.SiegeEndTime = sqlRequestResult.siege_end_time

        if "is_locked" in sqlRequestResult:
            guildInfo.IsLocked = bool(sqlRequestResult.is_locked)

        if "guild_level" in sqlRequestResult:
            guildInfo.ShortInfo.Level = sqlRequestResult.guild_level

        if "suzerain" in sqlRequestResult:
            guildInfo.SuzerainGuildAuid = sqlRequestResult.suzerain

        if "suzerain_short_name" in sqlRequestResult:
            guildInfo.SuzerainGuildShortName = sqlRequestResult.suzerain_short_name

        if "suzerain_name" in sqlRequestResult:
            guildInfo.SuzerainGuildFullName = sqlRequestResult.suzerain_name

        if "suzerain_rating" in sqlRequestResult:
            guildInfo.SuzerainRating = sqlRequestResult.suzerain_rating

        if "icon_revision" in sqlRequestResult:
            guildInfo.ShortInfo.IconChangesCount = sqlRequestResult.icon_revision

        if "position_change" in sqlRequestResult:
            guildInfo.ShortInfo.RatingPositionChange = GuildWarsDataCustom.GetRatingPositionChange(sqlRequestResult.position_change)

        if "shop_level" in sqlRequestResult:
            guildInfo.ShortInfo.ShopLevel = sqlRequestResult.shop_level

        if "num_members" in sqlRequestResult:
            guildInfo.ShortInfo.MembersCount = sqlRequestResult.num_members

        if "rating" in sqlRequestResult:
            guildInfo.ShortInfo.Rating = sqlRequestResult.rating

        if "position" in sqlRequestResult:
            guildInfo.ShortInfo.Place = sqlRequestResult.position

        if "prev_rating" in sqlRequestResult:
            guildInfo.ShortInfo.PrevRating = sqlRequestResult.prev_rating

        if "prev_place" in sqlRequestResult:
            guildInfo.ShortInfo.PrevPlace = sqlRequestResult.prev_place

        if "current_event_id" in sqlRequestResult:
            guildInfo.ShortInfo.LastEventIndex = sqlRequestResult.current_event_id

    # заполняем GuildRecruitmentInfo по результату SQL запроса из tbl_guild_rating
    @staticmethod
    def FillGuildRecruitmentInfoFromSQL(guildInfo, sqlRequestResult):
        if "position" in sqlRequestResult:
            guildInfo.ShortInfo.Place = sqlRequestResult.position

        if "guild_id" in sqlRequestResult:
            guildInfo.ShortInfo.GuildAuid = sqlRequestResult.guild_id

        if "guild_short_name" in  sqlRequestResult:
            guildInfo.ShortInfo.GuildShortName = sqlRequestResult.guild_short_name

        if "guild_name" in sqlRequestResult:
            guildInfo.ShortInfo.GuildFullName = sqlRequestResult.guild_name

        if "rating" in sqlRequestResult:
            guildInfo.ShortInfo.Rating = sqlRequestResult.rating

        if "guild_level" in sqlRequestResult:
            guildInfo.ShortInfo.Level = sqlRequestResult.guild_level

        if "icon_revision" in sqlRequestResult:
            guildInfo.ShortInfo.IconChangesCount = sqlRequestResult.icon_revision

        if "position_change" in sqlRequestResult:
            guildInfo.ShortInfo.RatingPositionChange = GuildWarsDataCustom.GetRatingPositionChange(sqlRequestResult.position_change)

        if "shop_level" in sqlRequestResult:
            guildInfo.ShortInfo.ShopLevel = sqlRequestResult.shop_level

        if "num_members" in sqlRequestResult:
            guildInfo.ShortInfo.MembersCount = sqlRequestResult.num_members

        if "locale" in sqlRequestResult:
            guildInfo.ShortInfo.Locale = sqlRequestResult.locale

        if "message" in sqlRequestResult:
            guildInfo.Message = sqlRequestResult.message

        if "guild_level" in sqlRequestResult:
            guildInfo.Level = sqlRequestResult.guild_level
