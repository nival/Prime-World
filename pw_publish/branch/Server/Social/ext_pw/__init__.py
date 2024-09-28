# -*- coding: utf-8 -*-

""" Action handlers for WebServer.

    Каждый event handler должен представлять собой class: 
    1) унаследованный от SubAction
    2) имеющий поле action = <строка, которую клиент будет указывать в параметре '&action=xxx' своего http-запроса>
    3) имеющий метод onStart(self), с которого будет начинаться исполнение сервером команды action.

    Пример:
    
    class DummyAction ( SubAction ):
        action = "dummy"        
        def onStart(self):
            self.fin()
    
    Все такие event handler classes должны быть перечислены ниже, в списке __all__, и включены через import.
"""

version = "1.0" 

__all__ = [ 
    "SetFractionAction", # model data reset
    "MatchmakingAddAction", "MatchmakingPingAction", "MatchmakingCancelAction", "MatchmakingAcceptAction", # base matchmaking
    "MatchmakingReconnectAction", "MatchmakingLeaveAction", "MatchmakingSpectateAction", "MatchmakingTamburLeaveAction", "MatchmakingAlliesAction",  # new matchmaking
    "PingAction", "WakeAction", # отложенный пинг
    "CheckForSpectatorAction", # проверка, является ли пользователь спектатором
    #"PartyInviteAction", "PartyAcceptAction", "PartyDeclineAction", "PartyDisbandAction", "PartyKickAction", "PartyHeroAction", "PartyGoAction", "PartyStatusAction",
]

from .matchmake import MatchmakingAddAction, MatchmakingPingAction, MatchmakingCancelAction, MatchmakingAcceptAction, \
    MatchmakingReconnectAction, MatchmakingLeaveAction, MatchmakingTamburLeaveAction, MatchmakingSpectateAction, CheckForSpectatorAction, MatchmakingAlliesAction
from .dataload import SetFractionAction
from .ping import PingAction, WakeAction
#from .party import PartyInviteAction, PartyAcceptAction, PartyDeclineAction, PartyDisbandAction, PartyKickAction, PartyHeroAction, PartyGoAction, PartyStatusAction

    
