# -*- coding: utf-8 -*-

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
import time
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")


import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from enums import RatingPositionChange

class LegendLeagueDataCustom( BaseObject ):
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

    # заполняем GuildRecruitmentInfo по результату SQL запроса из tbl_guild_rating
    @staticmethod
    def FillInfoInfoFromSQL(legendInfo, sqlRequestResult):
        if "uid" in sqlRequestResult:
            legendInfo.Uid = sqlRequestResult.uid

        if "hero_id" in sqlRequestResult:
            legendInfo.HeroId = sqlRequestResult.hero_id

        if "league_place" in sqlRequestResult:
            legendInfo.Place = sqlRequestResult.league_place

        if "nickname" in sqlRequestResult:
            legendInfo.Nickname = sqlRequestResult.nickname

        if "prev_league_place" in sqlRequestResult:
            if sqlRequestResult.prev_league_place < 0:
                legendInfo.RatingPositionChange = RatingPositionChange.Increased
            else:
                legendInfo.RatingPositionChange = LegendLeagueDataCustom.GetRatingPositionChange(sqlRequestResult.prev_league_place - sqlRequestResult.league_place)
        else:
            legendInfo.RatingPositionChange = 0
