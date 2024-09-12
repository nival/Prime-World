# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import ClassDict


CREATE_ALL_HEROES = -1
TALENT_SLOTS_PER_ROW = 6
MAX_TALENT_SLOTS = 40

_MAX_TALENTS_PER_ROW = 6
_MAX_ROWS = 6

_GIVF_COMMON_TALENTS_LIST =    [ "G001","G002","G003","G004","G005","G006","G009","G011","G012","G013","G016","G019","G020","G021","G022","G023","G024","G025","G026","G027","G028","G029","G030","G032","G036","G037","G038","G039","G040","G042","G043","G044","G049","G051","G053","G054","G056","G057","G058","G059","G060","G061","G062","G063","G064","G065","G066","G067","G068","G069","G070","G071","G072","G073","G074","G075","G076","G077","G078","G079","G080","G081","G082","G083","G084","G085","G086","G087","G088","G089","G090","G091","G092","G093","G094","G095","G096" ]

KEEPALIVE_TIMINGS = ClassDict(
    updateBuildingsProduction = 1,
    updateGold = 1,
    updateEventMap = 10,
    updateFameToPersonServer = 1,
    updatePartyInfo = 1,
    updateFirstDayWin = 20,
    updateGoldLamp = 2,
    setTime = 1,
    sendPendingMessages = 1,
    sendPendingEvents = 1,
    updateDodgesStatus = 5,
    updateGuildBonuses = 1,
    updateDynQuests = 1,
    updateRerollShop = 20,
    updateGuildWarEvent=1,
	)
