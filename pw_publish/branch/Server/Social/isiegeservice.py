# -*- coding: utf-8 -*-
__author__ = 'danil.lavrentyuk'
"""
Модуль интерфейса к сервису осад (siege service).
Осады шардятся по guildAuid target'а (на одну цель может быть в один момент времени только одна осада).
"""

from base.helpers import *
import urllib
from binascii import crc32
from numbers import Integral
from functools import partial

import ihttp

class ISiegeService:
    def __init__(self, addresses=None, HTTP=None):
        pass

    def subscribe(self, *args):
        pass

    def unsubscribe(self, *args):
        pass

    def startSiege(self, *args):
        pass

    def leaveSiege(self, *args):
        pass

    def joinSiege(self, *args):
        pass

    def checkSiege(self, *args):
        pass

    def guildScore(self, *args):
        pass

    def getSieges(self, *args):
        pass

    def winnerChoice(self, *args):
        pass

    def setSiegeDuration(self, *args):
        pass

    def setSiegeScore(self, *args):
        pass

    def destroySiege(self, *args):
        pass


class SiegeDataCollector(AllResponseCollector):
    """Collects siege data responses from all siege_services
     and join them into a single list."""
    def addResponse(self, response, peer):
        self.data.extend(response["sieges"])


class ScoreResponseCollector(AllResponseCollector):
    def addResponse(self, response, peer):
        self.data.append({"ok": 1, "peer": peer})

    def addError(self, error, peer):
        self.data.append({"ok": 0, "peer": peer, "ec": error["ec"], "error": error["error"]})


class IHttpSiegeService( ISiegeService ):
    def __init__(self, addresses=None, HTTP=None, request_limit=1000):
        self.addresses = addresses
        self.address_count = len(addresses)
        self.HTTP = ihttp.ILimitedAsyncHttpFetcher(HTTP, request_limit)

    def getPeer(self, siege):
        if self.address_count:
            if isinstance(siege, Integral):
                return self.addresses[ siege % self.address_count ]
            else:
                return self.addresses[ siege.Target % self.address_count ]

    def do(self, siege, args, callback):
        peer_addr = self.getPeer(siege)
        self.HTTP.fetch(peer_addr, args, partial(self.onFetch, peer_addr=peer_addr, args=args, callback=callback))


    def onFetch(self, response, peer_addr="", args={}, callback=None):
        info("IHttpSiegeService.onFetch response (peer_addr=%s, args=%s):\n%s" % (peer_addr, args, str(response)[:128]))
        if callback:
            callback(response)


    def onFetchPeer(self, response, peer_addr, args, collector):
        info("IHttpSiegeService.onFetchPeer response (peer_addr=%s, args=%s):\n%s" % (peer_addr, args, str(response)[:128]))
        collector.onResponse(response, peer_addr)


    def doAll(self, args, collector, logMsg=""):
        for peer in self.addresses:
            if logMsg:
                info(logMsg, peer, args)
            self.HTTP.fetch(peer, args, partial(self.onFetchPeer, peer_addr=peer, args=args, collector=collector))


    def subscribe(self, guildAuid, callback):
        info("SIEGE: subscribe %s", guildAuid)
        args = dict(action="subscribe", guildAuid=guildAuid)
        self.doAll(args, SiegeDataCollector(self.address_count, callback), "Subscribe to SiegeService %s: args=%r")


    def unsubscribe(self, guildAuid):
        args = dict(action="unsubscribe", guildAuid=guildAuid)
        for peer in self.addresses:
            info("Unsubscribe from SiegeService %s: args=%r", peer, args )
            self.HTTP.fetch(peer, args, partial(self.onFetch, peer_addr=peer, args=args, callback=None))


    def startSiege(self, (inviderAuid, inviderRating), (targetAuid, targetRating), (targetSuzerain, suzerainRating), price, callback):
        "Initiate (or join) a siege"
        args = dict(action="start", price=int(price),
                    target=targetAuid, t_rating=targetRating,
                    invider=inviderAuid, i_rating=inviderRating,
                    suzerain=targetSuzerain, s_rating=suzerainRating)
        info("Start a siege: args=%r", args)
        self.do(targetAuid, args, callback)


    def joinSiege(self, inviderAuid, inviderRating, target, price, callback):
        "Join a siege"
        args = dict(action="join", target=target, invider=inviderAuid, i_rating=inviderRating, price=int(price))
        info("Join a siege: args=%r", args)
        self.do(target, args, callback)


    def leaveSiege(self, guildAuid, targetAuid, callback):
        """"Leave a siege
        Usage cases:
         1. If the guild isn't the siege target, it can leave:
           - if it's not the target's current suzerain
           - it it's a suzerain and this is the vassal liberating siege (i.e. the guild let him go away)
         2. If the guild is the target and there is only one another participant, i.e. there is no target's
         current suzerain - this is the case the target accepts this new suzerain without resist.
        ALL this checks should be done at the guild server, not here.
        """
        args = dict(action="leave", guild=guildAuid, target=targetAuid)
        info("Leave the siege: args=%r", args)
        self.do(targetAuid, args, callback)


    def checkSiege(self, targetAuid, siegerAuid=0, callback=None):
        """Check if the targetAuid guild is a target of any current siege.
        Also can check if the target is sieged by another specified guild."""
        info("Check for siege on guild %s, by %s", targetAuid, siegerAuid)
        self.do(targetAuid, dict(action="check", target=targetAuid, sieger=siegerAuid), callback)


    def guildScore(self, guildAuid, points, callback):
        """Add the amount of guild score points to all that guild's sieges.
        Pass to callback a list of dicts containing:
            "ok" - 1 or 0
            "peer" - siege service instance address
            "sieges" - if ok=True, a list of sieges updated by peer
             "ec" and "error" - if ok=False, an error code and message
        """
        args = dict(action="score", guild=guildAuid, points=points)
        self.doAll(args, ScoreResponseCollector(self.address_count, callback), "Send guild points to Siege Service %s: %r")
        #FIXME предусмотреть проверку результата, запоминание и перепосылку в случае сбоя отправки.


    def getSieges(self, guildAuid, callback):
        "Get all sieges for this guild. Same as for subscribed guild/"
        info("Getting sieges for guild %s", guildAuid)
        self.doAll(dict(action="get_sieges", guild=guildAuid), SiegeDataCollector(self.address_count, callback), "Get sieges from %s: args=%r")


    def winnerChoice(self, targetAuid, choice, callback):
        "Inform siege service about locket siege winner's choice: 'accept' or 'refuse' the conquered vassal."
        args = dict(action="choice", target=targetAuid, choice=choice)
        info("Winner's choice: %s", args)
        self.do(targetAuid, args, callback)


    def setSiegeDuration(self, targetAuid, duration, callback):
        "Debug action, sets the left time of the siege to `duration`"
        args = dict(action="set_duration", targetAuid=targetAuid, duration=duration)
        info("Set siege duration: %s", args)
        self.do(targetAuid, args, callback)


    def setSiegeScore(self, participantAuid, targetAuid, score, callback):
        "Debug action, sets the score of the siege participant to `score`"
        args = dict(action="set_score", participantAuid=participantAuid, targetAuid=targetAuid, score=score)
        info("Set siege score: %s", args)
        self.do(targetAuid, args, callback)


    def destroySiege(self, targetAuid, safe, callback):
        "Destroy possibly unfinished siege. With safe=1 never respond NO_SIEGE_FOR_TARGET error"
        args = dict(action="destroy", targetAuid=targetAuid, safe=safe)
        info("Destroy the siege: %s", args)
        self.do(targetAuid, args, callback)
