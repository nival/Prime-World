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

from iuserdata import IAbstractModelData
from modeldata.validator import *

class RecruitsDataCustom( BaseObject ):
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

    def addRecruit(self, recruitInfo, lifetime):
        recruit, _id = self.newGuildApplicantInfo()
        recruit.MaxRating = recruitInfo["max_rating"]
        recruit.Fame = recruitInfo["fame"]
        recruit.ExpireTime = recruitInfo["created"] + lifetime
        recruit.Auid = recruitInfo["pers_auid"]
        recruit.Nickname = recruitInfo["nickname"]
        for hero_id, rating in recruitInfo["heroes"]:
            recruit.MaxRatingHeroes[hero_id] = rating
        recruit.Message = recruitInfo["text"]
        self.GuildApplicants.add(recruit)
