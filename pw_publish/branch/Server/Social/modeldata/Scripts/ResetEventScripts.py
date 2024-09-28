# -*- coding: utf-8 -*-

from base.helpers import *


class ResetEventScripts:
    def convertModelData( self, env, acc, md, dict ):
        while len(md.version.events):
            md.version.events.pop()
        md.LordInfo.LastTechPremium = 0
        md.LordInfo.LastTechGuildBuffs = 0
        md.MarketingEventsInfo.LampEventInfo.LastTechLamp = 0

        return md, acc.db