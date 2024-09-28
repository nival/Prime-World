# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32
import CC
from modeldata import TalentSet, collects
import time
class AddPlayerRatings:

    def convertModelData( self, env, acc, md, dict ):
        md.initPlayerRatings(env.iDict.Config.getMainConfig())
        return md, acc.db