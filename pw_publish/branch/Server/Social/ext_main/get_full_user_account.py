# -*- coding: utf-8 -*-

# !/usr/bin/env python

from base.helpers import *
from handlers import *  # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing, separate_timing
from tornado.httpclient import HTTPRequest

class GetFullUserAccountAction(SubAction):
    action = "get_full_user_account"

    """ Cлужебный логический handler, выполняет поиск данных для аккаунта с <auid>. """

    @action_timing
    def onStart(self):
        info("GetFullUserAccountAction.onStart")
        self.target_auid = self.getIntParam("target_auid", 0)
        self.is_wsname = self.getIntParam("is_ws", False)
        if self.target_auid:
            target_user_acc = self.I.WS.getUserAccByAuid(self.target_auid)
            if target_user_acc:
                self.response["model"] = target_user_acc.model.generateJsonDict()
                self.response["db"] = target_user_acc.db
                self.response["ok"] = 1
                self.fin()
                return
            else:
                self.I.AGG.getInfo(self.target_auid, None, include_secure_data=1, callback=self.onAgentFsnGetInfo)
                return
        else:
            self.errorResponse("Bad parameter 'target_auid'")
            return

        self.response["ok"] = 0
        self.fin()


    @action_timing
    def onAgentFsnGetInfo(self, agg_response):
        if agg_response:
            self.agg_info = agg_response.get('get_info')
            if self.agg_info:
                agg_properties = self.agg_info.get('props') or {}
                fsn = agg_properties.get('fsn')
                if fsn:
                    sn_info = self.agg_info.get(fsn)
                    if sn_info:
                        fsn_snid = fsn
                        fsn_snuid = sn_info.get('snuid', '')
                        self.response["fsn_snid"] = fsn_snid
                        self.response["fsn_snuid"] = fsn_snuid
                        if fsn_snid and fsn_snuid:
                            self.login = str("%s#%s" % ( fsn_snid, fsn_snuid ))
                            self.loginToWS(self.login)
                            return
        # fail:
        self.errorResponse("Bad response from Aggregator")


    def loginToWS(self, login):
        ws_res = None
        peers = self.I.WS.peers
        if peers:
            ws_id = pickRandom(peers.keys())
            # сначала пробуем subLogin на случайном WS (если юзер уже залоган на другом сервере, нам так и скажут)
            peer = peers[ws_id]
            ws_addr = peer["addr"]
            # чтобы не слать запросов самому себе, залогиним человека ещё на каком-нибудь сервере
            selfPeer = self.I.WS.peers.get(options.server_id)
            self_ws_addr = selfPeer["addr"]

            # слать запросы самим себе - не комильфо
            if self_ws_addr == ws_addr:
                if len(self.I.WS.peers.keys()) > 1:
                    while self_ws_addr == ws_addr:
                        ws_id = pickRandom(peers.keys())
                        peer = peers[ws_id]
                        ws_addr = peer["addr"]
                else:
                    warn("no servers available")
                    self.onSubLogin(None, self_ws_addr)
                    return None

            snid, snuid = login.split('#')

            args = dict(action="sublogin_fsn", snid=snid, snuid=snuid, wait_persistent=1, isGM=1)
            _callback = functools.partial(self.onSubLogin, ws_addr=ws_addr)
            self.I.WSX.fetch(ws_addr, args, _callback, subrequest="x")
            return None
        else:
            warn("no peers available")


    def onSubLogin(self, response, ws_addr):
        info("onSubLogin: response(%r), ws_addr(%r)", response, ws_addr)
        self.ws_change_name = ""
        if response:
            self.ws_change_name = response.get("ws_name")
            if self.ws_change_name:
                ws_change = response.get("ws")
                info("user logged on different server: ws_name %s, ws %s", self.ws_change_name, ws_change)
                ws_addr = self.I.WS.peers[ws_change]["addr"]

            if not self.ws_change_name:
                self.ws_change_name = response.get("server")

        args = dict(action="get_account_data", auid=self.target_auid, login=self.login)
        req = HTTPRequest(url='http://' + ws_addr + '/?' + urllib.urlencode(args), method="GET", connect_timeout=20.0,
                          request_timeout=20.0)
        self.I.HTTP.fetch(req, self.onGetAccountData)
        return

    @action_timing
    def onGetAccountData(self, response):
        debug("onGetAccountData: %r", response)
        info("onGetAccountData")
        isOk = False
        if response and (not response.error) and len(response.body) > 0:
            result = jsonResult(response)
            if result.get("response", None) and result["response"].get("ok", None):
                isOk = result["response"].get("ok", False)
        if isOk:
            if self.is_wsname:
                self.response["ws_name"] = self.ws_change_name
            elif result["response"].get("model", None) and result["response"].get("db", None):
                self.response["model"] = result["response"].get("model")
                self.response["db"] = result["response"].get("db")

            self.response["ok"] = 1
            self.fin()
            return

        self.errorResponse("Failed to find account data for auid %d" % self.target_auid)


class GetAccountDataAction(SubAction):
    """action, который будет обрабатывать данный класс"""
    action = "get_account_data"

    def onStart(self):
        self.log()
        info("GetAccountDataAction.onStart")
        if self.checkValidIntParam("auid"):
            target_user_acc = self.I.WS.getUserAccByAuid(self.auid)
            if target_user_acc:
                self.response["model"] = target_user_acc.model.generateJsonDict()
                self.response["db"] = target_user_acc.db
                self.response["ok"] = 1
                self.fin()
                return
            else:
                self.errorResponse("Failed to find online account data for auid %d" % self.auid)
                return
        self.errorResponse("Bad parameter 'auid'")
