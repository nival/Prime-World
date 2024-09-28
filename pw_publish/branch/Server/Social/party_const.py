# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import ClassDict

# эти party-команды WS принимает с клиента (и форвардит на PS)
PARTY_COMMANDS = ['party_invite', 'party_accept', 'party_decline', 'party_disband', 'party_kick', 'party_status',
                  'party_dodge', 'party_go', 'party_hero', 'party_map', 'party_flag', 'party_inventory_is_full',
                  'party_choose_again']

WS_RECV_PARTY_COMMANDS = ['go', 'stop'] # WS обращает специальное внимание только на команды "начать матчмейкинг/остановить матчмейкинг"
WS_SEND_PARTY_COMMANDS = ['party_progress'] # WS умеет дополнительно извещать о статусе своей mm-сессии (party-систему интересует только смена 0 <--> !0)

PS_PARTY_COMMANDS = PARTY_COMMANDS[:]
PS_PARTY_COMMANDS.extend( WS_SEND_PARTY_COMMANDS )

MAX_PARTY_MEMBERS = 5

PARTY_INVITE_TIMEOUT = 30.0 # через столько секунд протухает party invite

PARTY_CANCEL_TIMEOUT = 5.0 # в течение стольких секунд после смены mm_progress=0 не разрешаем стартовать новый party.go

FRACTION = ClassDict(
    DOCT = "A",
    ADORN = "B",
    NONE = "N",
)

PARTY_FRACTION = ClassDict(
    DOCT = 0,
    ADORN = 1,
    NONE = 2,
)

PARTY_STRING_2_PARTY_FRACTION = ClassDict(
    A = 0,
    B = 1,
    N = 2,
)

FRACTION_LIST = ["A", "B", "N"]

def getPartyFraction(fraction_string):
    return PARTY_STRING_2_PARTY_FRACTION.get(fraction_string, PARTY_FRACTION.NONE)
    
    
#~ PARTY_ERROR = ClassDict(
    #~ BAD_MASTER_AUID = 501, # "bad master_auid specified",
    #~ BAD_PARTY = 502, # "no such party"
    #~ BAD_COMMAND = 503, # "no such command" 
    #~ USER_ALREADY_HAS_PARTY = 504, # "user already has a party"
    #~ USER_IN_GAME = 505, # "user in game" 
    #~ PARTY_FULL = 506, # "party is full"
    #~ NO_INVITE = 507,  # "no pending invite (maybe timed out)"
    #~ NOT_A_PARTY_MEMBER = 508, # "not a party member" 
    #~ CANT_KICK_SELF = 509, #  "cant kick self"
    #~ NOT_A_PARTY_MEMBER_OR_INVITE = 510, # "not a party member or invite" 
    #~ NO_CHOSEN_HEROES = 511, # "not all party members chosen heroes for pvp" 
    #~ NOT_READY_FOR_PVP = 512, #"not all party members ready for pvp" // у кого-то mm_progress != 0
#~ )

PARTY_ERROR = ClassDict(
    BAD_MASTER_AUID =     (501, "bad master_auid specified"),
    BAD_PARTY =         (502, "no such party"),
    BAD_COMMAND =         (503, "no such command" ),
    USER_ALREADY_HAS_PARTY = (504, "user already has a party"),
    USER_IN_GAME =         (505, "user in game" ),
    PARTY_FULL =         (506, "party is full"),
    NO_PENDING_INVITE = (507, "no pending invite (maybe timed out)"),
    NOT_A_PARTY_MEMBER =(508, "not a party member" ),
    CANT_KICK_SELF =     (509, "cant kick self"),
    NOT_A_PARTY_MEMBER_OR_INVITE = (510, "not a party member or invite" ),
    NO_CHOSEN_HEROES =     (511, "not all party members chosen heroes for pvp"), 
    NOT_READY_FOR_PVP = (512, "not all party members ready for pvp"), # у кого-то mm_progress != 0
    PARTY_MEMBER_CANT_INVITE = (513, "party member (not master) cannot invite"),
    USER_NOT_ONLINE =      (514, "user not online"),
    NOT_A_PARTY_MASTER =(515, "not a party master" ),
    CANT_INVITE_SELF =     (516, "cant invite self"),
    SIMILAR_HEROES =     (517, "too many similar heroes chosen"),
    TOO_BIG_PARTY =     (519, "party size exceeds map limits"),
    HAS_BAD_TS = (520, "some heroes has bad talent set"),
    ALREADY_MM_READY = (521, "already pressed mm_ready"),
    MIXED_GUARD_PARTY = (522, "mixed guards and non-guards heroes in party"),
    USER_IS_RETIRED = (523, "user is retired"),
    BAD_IS_FIXED_MATCH = (524, "bad is_fixed_match state"),
    BAD_FIXED_MATCH_SIDES = (525, "bad fixed_match sides"),
    CANT_CNANGE_MAP_MM = (526, "cant change map after mm start"),
    BOTS_FORBIDDEN = (527, "bots are not allowed for this map"),
    NOT_ENOUGH_FORCE = (528, "not all party members have enough force for map"),
    TOURNAMENT_ACCOUNT_IN_PARTY = (529, "one of party members has account with no MM allowed")
)