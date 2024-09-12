# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *

from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing, separate_timing
from instr import * 

import base64

import imemcache

import MM
import EC
import CC

from pwaccount import UserAccount
import pwaccount

from login import BaseCheckVersionAction, LoginAction
from nickname import SetNicknameAction
from ext_pw import SetFractionAction
from sublogin import AgentSubloginAction

class CreateAccountAction( BaseCheckVersionAction ):
    action = "create_account"
    
    """ Cлужебный логический handler, поддерживает единственный 'action=login'. """
    @action_timing
    def onStart(self):
        log("CreateAccount.onStart")
        self.snid = self.getParam("snid")
        self.snuid = self.getParam("snuid")
        self.auid = self.getIntParam("auid",0)
        self.nickname = self.getParam("nickname","")
        self.fraction = self.getParam("fraction","N")
        self.login = self.snid+"#"+self.snuid
        self.boughtType = self.getIntParam("boughtType",0)
        pwd_hash = self.login[:32] # SQL ESCAPE?..
        if self.auid in cfg.TOURNAMENT_SPECTATOR_AUIDS:
            info( "Try CreateAccount by spectator auid=%r login=%r", self.auid, self.login )
            self.response["ok"] = 0
            self.fin()            

        info( "CreateAccount auid=%r login=%r", self.auid, self.login )
        self.I.SQL.addNewLogin( self.auid, self.login, pwd_hash, options.server_id, callback=self.onNewLoginAdded )
        self.response["ok"] = 1
        self.fin()            

    
    @action_timing  
    def onNewLoginAdded(self, sql_reply):
        info( "onNewLoginAdded: %r", sql_reply )
        self.I.AGG.getInfo( self.auid, None, include_secure_data=1, callback=self.onAgentFsnGetInfo )
    

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
                else:
                    fsn_snid = self.snid
                    fsn_snuid = self.snuid

                if fsn_snid and fsn_snuid:
                    self.login2 = str("%s#%s" % ( fsn_snid, fsn_snuid ))
                    if self.login != self.login2:
                        pwd_hash = self.login2[:32] # SQL ESCAPE?..
                        #FIXME duplicate addNewLogin call with the same id!
                        self.I.SQL.addNewLogin( self.auid, self.login2, pwd_hash, options.server_id, callback=self.onNewLoginAdded2 )
                    else:
                        self.onNewLoginAdded2( "Not need new sql user add" )
                    return
                else:
                    err( "Fail onAgentFsnGetInfo %r fsn_snid or fsn_snuid is None", agg_response )
            else:
                err( "Fail onAgentFsnGetInfo %r get_info=None", agg_response )
        # fail:
        err( "Fail onAgentFsnGetInfo %r", agg_response )


    @action_timing  
    def onNewLoginAdded2(self, sql_reply):
        info( "onNewLoginAdded2: %r", sql_reply )
        subParams = ClassDict( snid=[self.snid], snuid=[self.snuid], wait_persistent=[1] )
        accountAction = AgentSubloginAction( subParams, self.onSubLogin, I=self.I )
        accountAction.onStart()


    def onSubLogin( self, response ):
        info( "onSubLogin %r", response )
        if response:
            self.acc = self.I.WS.getUserAcc( self.login ) or self.I.WS.getUserAcc( self.login2 )
            subParams = ClassDict( nickname=[self.nickname] )
            accountAction = SetNicknameAction( subParams, self.onNickName, I=self.I, acc=self.acc, uid=self.acc.uid )
            accountAction.onStart()

            subParams = ClassDict( fraction=[self.fraction], force_new = [1], full_reset=[1] )
            resetAccountAction = SetFractionAction( subParams, self.onFraction, I=self.I, acc=self.acc, uid=self.acc.uid )
            resetAccountAction.onStart()
        else:
            err( "Fail login by %r", self.login )
            return None


    def onNickName( self, response ):
        info( "onNickName: %r", response )


    def onFraction( self, response ):
        info( "onFraction: %r", response )
        self.acc.model.TournamentInfo.createTicket( self.acc.db.auid, self.boughtType )
        self.acc.ka = 0 # и пусть юзера выкинет с сервера на следующем тике, чтобы данные сохранились

