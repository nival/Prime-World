# -"- coding: utf8 -"-
# (C) Dmitry Kolb 2014, Nival Network 

__author__ = 'dmitry.kolb'

from subaction import SubAction, action_timing
from base.helpers import *
import CC
from functools import partial

class PseudoDeleteAccountAction( SubAction ):
    '''
    По задаче PF-90460
    Эмулируем удаление аккаунта. Размерживаем его и чистим информацию о логинах.
    !!!! Необходимо использовать только в режиме отладки !!!!
    Запрос оставляет в базах соц. аггр. информацию по старым аккаунтам. И соц. сервера.
    '''
    action = "pseudo_delete_account"
    debug = True

    """ Cлужебный логический handler, поддерживает единственный 'action=pseudo_delete_account'. """
    @action_timing
    def onStart(self):
        log("DeleteAccount.onStart")

        self.auid = self.getIntParam("auid", 0)

        info( "DeleteAccount auid=%r ", self.auid)

        self.acc = self.I.WS.getUserAccByAuid(self.auid)
        if self.acc:
            self.I.AGG.getInfo(self.auid, None, 1, callback=self.onGetInfo)
            self.response["ok"] = 1
        else:
            self.response["error"] = "auid is not found"
        self.fin()


    @action_timing
    def onRemoveLogin(self, sql_reply):
        info( "DeleteAccount.onRemoveLogin: %r", sql_reply )

    @action_timing
    def onGetInfo(self, agg_reply):
        info( "DeleteAccount.onGetInfo: %r", agg_reply)
        self.fsn = agg_reply['get_info']['props']['fsn']
        for snid in CC.AGG_SOCIAL_NETWORK_NAMES:
            if snid in agg_reply['get_info']:
                self.I.SQL.seFindLogin(str(snid + "#" + agg_reply['get_info'][snid]['snuid']), callback=partial(self.onSEFindLogin, self.auid, snid))

    @action_timing
    def onSEFindLogin(self, auid, sn, sql_reply):
        info( "DeleteAccount.onSEFindLogin auid: %r", auid)
        if self.fsn != sn:
            self.I.AGG.deleteSn(auid, sn, callback=self.onDeleteSn)

        if sql_reply and sql_reply.get('r'):
            result = sql_reply.get('r')
            info( "DeleteAccount.onSEFindLogin result : %r", result)
            self.I.SQL.removeLogin(result[0]['id'], self.acc.login, callback=self.onRemoveLogin)

    @action_timing
    def onDeleteSn(self, agg_reply):
        info( "DeleteAccount.onDeleteSn: %r", agg_reply)

