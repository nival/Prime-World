# -*- coding: utf-8 -*-
__author__ = 'danil.lavrentyuk'
"""Siege Service request handlers classes"""

# WARNING! DO NOT OVERRIDE onStart()
# Derive action class from SiegeServiceAction and override perfrom()

from base.helpers import *
from subaction import *
from base.wstools import *
# from siege.SiegeData import SiegeData

__all__ = [
    'SubscribeAction',
    'UnsubscribeAction',
    "StartSiegeAction",
    "JoinSiegeAction",
    "LeaveSiegeAction",
    "ScoreAction",
    "GetSieges",
    "WinnerChoiceAction",
    "DestroySiegeAction",
    "CheckSiegeAction",
#
    "SetDurationAction",
    "SetScoreAction",
]


class SiegeServiceAction(SubAction):
    check_enabled = True  # is I.WS.enabled check required?
    wait_cached = True    # is I.WS.chaced check required?

    def onStart(self):
        if self.check_enabled and not self.I.WS.enabled:
            info("%s: Sieges isn't enabled. Do nothing.", self.__class__.__name__)
            self.disabled_response()
            self.fin()
        elif self.wait_cached and not self.I.WS.cached:
            info("%s: Sieges aren't cached. Suspended.", self.__class__.__name__)
            AddLoopCallback(self.onStart, timeout_seconds = 1.9)
        else:
            try:
                self.perform()
            except Exception, e:
                catch()
                self.errorResponse(EC.INTERNAL_SERVER_ERROR, "%s: %s" % (sys.exc_info()[:2]))

    @action_timing
    def perform(self):
        err("%s.perform method NOT IMPLEMENTED", self.__class__.__name__)

    def response_ok(self):
        self.response["ok"] = 1

    def response_no_ok(self):
        self.response["ok"] = 0

    def response_sieges(self):
        self.response["sieges"] = []
        self.response["ok"] = 1

    disabled_response = response_ok


class SubscribeAction(SiegeServiceAction):
    action = "subscribe"
    disabled_response = SiegeServiceAction.response_sieges

    @action_timing
    def perform(self):
        if not self.I.WS.enabled:
            return self.onSubscribed([])
        info("SiegeService: SubscribeAction %s", self.arguments)
        if self.checkValidIntParam("guildAuid"):
            self.I.WS.subscribeAction(self.guildAuid, self.onSubscribed)
        else:
            self.fin()

    def onSubscribed(self, sieges):
        self.response["sieges"] = sieges
        self.response["ok"] = 1
        self.fin()



class UnsubscribeAction(SiegeServiceAction):
    action = "unsubscribe"
    wait_cached = False

    @action_timing
    def perform(self):
        info("SiegeService: UnsubscribeAction %s", self.arguments)
        if self.checkValidIntParam("guildAuid"):
            self.I.WS.unsubscribeAction(self.guildAuid)
            self.response["ok"] = 1
        self.fin()


class StartJoinBaseAction(SiegeServiceAction):
    "The base class for start ans join actions."
    def _reverseFoundResponce(self):
        warn("Reverse-siege attempt from guild %s on guild %s", self.invider, self.target)
        self.errorResponse(EC.SIEGE_BACK_FORBIDDEN, "Can't siege a guild who already sieges you!")

    def checkReverseAndGo(self):
        if self.I.WS.checkReverseSiege(self.invider, self.target, self.onReverseChecked):
            self._reverseFoundResponce()
        # else it uses the callback

    def onReverseChecked(self, Ok):
        if Ok is None:
            self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Internal server error, check siege service logs for details")
        elif Ok:
            self.proceed()
        else:
            self._reverseFoundResponce()

    def proceed(self):
        err_trace("StartJoinBaseAction: abstract method `proceed` has to be overriden")
        self.errorResponse(EC.INTERNAL_SERVER_ERROR, "abstract method `proceed` has to be overriden")


class StartSiegeAction(StartJoinBaseAction):
    action = "start"
    intParams = ('target', 'invider', 'suzerain', 'price')
    floatParams = ('t_rating', 'i_rating', 's_rating')
    disabled_response = SiegeServiceAction.response_no_ok

    @action_timing
    def perform(self):
        info("SiegeService: StartSiegeAction %s", self.arguments)
        if self.checkIntParams() and self.checkFloatParams():
            self.checkReverseAndGo()
        else:
            self.fin()

    def proceed(self):
        self.I.WS.startSiegeAction((self.target, self.t_rating), (self.invider, self.i_rating), (self.suzerain, self.s_rating), self.price, self.onSiegeStarted)

    def onSiegeStarted(self, result):
        if result.get("ok"):
            self.response["siege"] = result['siege']
            self.response["ok"] = 1
        else:
            self.response["ec"] = result["ec"]
            self.response["error"] = result["error"]
            if "response" in result:
                self.response["response"] = result["response"]
        self.fin()


class JoinSiegeAction(StartJoinBaseAction):
    action = "join"
    intParams = ('target', 'invider', 'price')
    disabled_response = SiegeServiceAction.response_no_ok

    @action_timing
    def perform(self):
        info("SiegeService: JoinSiegeAction %s", self.arguments)
        if self.checkIntParams() and self.checkValidFloatParam("i_rating"):
            self.checkReverseAndGo()
        else:
            self.fin()

    def proceed(self):
        self.I.WS.joinSiegeAction(self.target, self.invider, self.i_rating, self.price, self.onSiegeJoined)

    def onSiegeJoined(self, result):
        if result.get("ok"):
            self.response["siege"] = result['siege']
            self.response["ok"] = 1
        else:
            self.response["ec"] = result["ec"]
            self.response["error"] = result["error"]
            if "response" in result:
                self.response["response"] = result["response"]
        self.fin()


class LeaveSiegeAction(SiegeServiceAction):
    action = "leave"
    intParams = ("target", "guild")
    disabled_response = SiegeServiceAction.response_ok

    @action_timing
    def perform(self):
        info("SiegeService: LeaveSiegeAction %s", self.arguments)
        if self.checkIntParams():
            self.I.WS.leaveSiegeAction(self.target, self.guild, self.onSiegeLeft)
        else:
            self.fin()

    def onSiegeLeft(self, result):
        if result.get("ok"):
            self.response["siege"] = result['siege']
            self.response["ok"] = 1
        else:
            self.response["ec"] = result["ec"]
            self.response["error"] = result["error"]
            if "response" in result:
                self.response["response"] = result["response"]
        self.fin()


class ScoreAction(SiegeServiceAction):
    action = "score"

    @action_timing
    def perform(self):
        info("SiegeService: ScoreAction %s", self.arguments)
        if self.checkValidIntParam("guild") and self.checkValidFloatParam("points"):
            self.I.WS.scoreAction(self.guild, self.points, self.onScored)
        else:
            self.fin()

    def onScored(self, result=None):
        self.response["ok"] = 1
        self.fin()


class GetSieges(SiegeServiceAction):
    action = "get_sieges"
    wait_cached = False
    disabled_response = SiegeServiceAction.response_sieges

    @action_timing
    def perform(self):
        info("SiegeService: GetSieges %s", self.arguments)
        if self.checkValidIntParam("guild"):
            self.response["sieges"] = self.I.WS.findGuildSieges(self.guild)
            self.response["ok"] = 1
        self.fin()


class WinnerChoiceAction(SiegeServiceAction):
    action = "choice"
    disabled_response = SiegeServiceAction.response_ok

    @action_timing
    def perform(self):
        info("SiegeService: WinnerChoiceAction %s", self.arguments)
        if self.checkValidIntParam("target") and self.checkValidParam("choice"):
            self.I.WS.winnerChoice(self.target, self.choice, self.onChoiceProcessed)
        else:
            self.fin()

    def onChoiceProcessed(self, result):
        if result.get("ok"):
            self.response["ok"] = 1
        else:
            self.response["ec"] = result["ec"]
            self.response["error"] = result["error"]
        self.fin()


class SetDurationAction(SiegeServiceAction):
    action = "set_duration"
    disabled_response = SiegeServiceAction.response_ok
    debug = True

    @action_timing
    def perform(self):
        info("SiegeService: SetDurationAction %s", self.arguments)
        if self.checkValidIntParam("targetAuid") and self.checkValidIntParam("duration"):
            siege = self.I.WS.getByTarget(self.targetAuid)
            if siege and siege['status'] == 'active':
                self.I.WS.siegeEndTimeUpdate(siege, int(time.time()) + self.duration)
                self.I.DATA.update("sieges", "sieges", {"_id": siege["_id"]}, {"end_time": siege["end_time"]},
                                   callback=partial(self.onDurationChangedProcessed, siege=siege))
                return
            else:
                errDict = self.I.WS.popError()
                if errDict:
                    self.errorResponse(errDict["ec"], errDict["error"])
                else:
                    self.errorResponse(EC.SIEGE_FINISHED, "The siege is not active already!")
        else:
            self.fin()

    def onDurationChangedProcessed(self, response, siege=None):
        if not response or response.get("r") is None:
            self.response["error"] = "onSiegeSave: error saving/updating siege: %s" % siege["_id"]
        else:
            for part in siege["participants"]:
                debug("active = %r", self.I.WS.activeGuilds)
                if part["id"] in self.I.WS.activeGuilds:
                    args = {}
                    self.I.GUILD.debugUpdateSiege(part["id"], siegeInfo=[{"cmd": "duration", "end_time": siege["end_time"],
                                                                          "_id": siege["_id"]}], callback=self.onDummyCallback)
            self.response["ok"] = 1
        self.fin()

    def onDummyCallback(self, response):
        if not response.get("ok"):
            err("SetDurationAction failed to notify one of participants")


class SetScoreAction(SiegeServiceAction):
    action = "set_score"
    disabled_response = SiegeServiceAction.response_ok
    debug = True

    @action_timing
    def perform(self):
        info("SiegeService: SetScoreAction %s", self.arguments)
        if self.checkValidIntParam("targetAuid") and self.checkValidIntParam("score") and self.checkValidIntParam("participantAuid"):
            siege = self.I.WS.getByTarget(self.targetAuid)
            if siege and siege['status'] in ('active', 'gap'):
                for part in siege["participants"]:
                    if part["id"] == self.participantAuid:
                        part["score"] = self.score
                        self.I.DATA.update("sieges", "sieges", {"_id": siege["_id"]}, {"participants": siege["participants"]},
                                       callback=partial(self.onScoreSavedProcessed, guild=self.participantAuid, score=part["score"], siege=siege))
                        return
                self.response["error"] = "Participant %d was not found in siege for guild %d" % (self.participantAuid, self.targetAuid)
            else:
                errDict = self.I.WS.popError()
                if errDict:
                    self.errorResponse(errDict["ec"], errDict["error"])
                else:
                    self.errorResponse(EC.SIEGE_FINISHED, "The siege is already finished!")
        else:
            self.fin()

    def onScoreSavedProcessed(self, response, siege=None, guild=None, score=0):
        if not response or response.get("r") is None:
            self.response["error"] = "onSiegeSave: error saving/updating siege: %s" % siege["_id"]
        else:
            self.response["ok"] = 1
        self.I.WS.notifyParticipants(siege, {'cmd': 'score', 'guildAuid': guild, 'score': score, '_id': siege['_id']})
        #for part in siege["participants"]:
        #    info("active = %r", self.I.WS.activeGuilds)
        #    if ("leave" not in part) and (part["id"] in self.I.WS.activeGuilds):
        #        self.I.GUILD.debugUpdateSiege(part["id"], siegeInfo=[{"cmd": "score", "guildAuid": guild, "score": score,
        #                                                              "_id": siege["_id"]}], callback=self.onDummyCallback)
        self.fin()

    def onDummyCallback(self, response):
        if not response.get("ok"):
            err("SetScoreAction failed to notify one of participants")


class DestroySiegeAction(SiegeServiceAction):
    action = "destroy"
    disabled_response = SiegeServiceAction.response_ok

    @action_timing
    def perform(self):
        info("SiegeService: DestroySiegeAction %s", self.arguments)
        if self.checkValidIntParam("targetAuid") and self.checkValidBoolParam("safe"):
            self.response["ok"] = 1
            siege = self.I.WS.getByTarget(self.targetAuid)
            if siege:
                self.I.WS.performDestroy(siege)
            else:
                if not self.safe:
                    errDict = self.I.WS.popError()
                    self.errorResponse(errDict["ec"], errDict["error"])
                    return
        self.fin()


class CheckSiegeAction(SiegeServiceAction):
    action = "check"
    disabled_response = SiegeServiceAction.response_no_ok

    def perform(self):
        info("SiegeService: CheckSiegeAction %s", self.arguments)
        if self.checkValidIntParam("target") and self.checkValidIntParam("sieger"):
            try:
                self.response["ok"] = 1
                self.response["found"] = 1 if (
                    self.I.WS.getByTarget(self.target) if self.sieger == 0 else
                    self.I.WS.checkTargetAndSieger(self.target, self.sieger)
                ) else 0
            except Exception:
                catch()
                self.response["ok"] = 0
        self.fin()

