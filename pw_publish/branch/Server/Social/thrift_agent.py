# -*- coding: utf-8 -*-

# Thrift Agent web-server: принимает внешние запросы по thrift, мапит их на внутрикластерные http-запросы
# (C) Dan Vorobiev 2011, Nival Network

import sys
import os
import time

import logging
import functools

sys.path.append('tornado')
import tornado.options
from tornado.options import define, options
from pymongo import Connection
from base.helpers import *
from modeldata.persistent_data import PersistentDataManager

sys.path.append('cfg')
import coord_cfg
from thrift_cfg import BACKUP_MONGO_CONFIG

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

import pwaccount

from ext_main.chat import MessageAction


# базовые web request handlers
from handlers import *  # JsonHandler, SubAction, IfaceFactory
from thrift_handler import ThriftHandler, AsyncThriftException

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol


sys.path.append('thrift_pw/account_management/gen-py')
import AccountManagementAPI.AccountManagement
import AccountManagementAPI.ttypes

SN_LIST_KEEP_TIME = 30 * 60 # минимальный интервал между запросами на SA аз списком соцсетей
AUIDS_UPDATE_PER_TICK = 32 # скольки пользователям за 1 тик рассылать массовые операции
MASS_OPERATION_KEEP_TIME = 5*24*60*60  # сколько хранятся отчёты о массовых операциях на сервере

def AccountIsNull():
    warn("AccountIsNull!")
    resInfo = AccountManagementAPI.ttypes.RequestResult.SnUidNotExist
    accInfo = AccountManagementAPI.ttypes.AccountInfo(
        snid="Account is null", snuid="Account is null")
    return (
        AccountManagementAPI.ttypes.AccountInfoResponse(
            accountInfo=accInfo, result=resInfo)
    )

def BadAuidError(auid):
    error("Bad auid value: %r", auid)
    resInfo = AccountManagementAPI.ttypes.RequestResult.AuidNotExist
    accInfo = AccountManagementAPI.ttypes.AccountInfo(
        snid="Bad auid", snuid="Bad auid")
    return (
        AccountManagementAPI.ttypes.AccountInfoResponse(
            accountInfo=accInfo, result=resInfo)
    )


class AccountManagementAgentHandler( AccountManagementAPI.AccountManagement.Iface ):
    """ """
    def __init__( self, handler ):
        self.handler = handler
        self.service = handler.service
        self.I = handler.I

    @staticmethod
    def getProcessorClass():
        return AccountManagementAPI.AccountManagement.Processor

    def CallGuildFunction(self, funcname, auid, *args):
        if self.I.GS:
            gs_addr = self.I.GS.getPeer(auid)
            if gs_addr:
                transport = THttpClient.THttpClient(
                    'http://%s/thrift?service=account_management' % gs_addr)
                transport.setTimeout(10 * 1000)
                transport = TTransport.TBufferedTransport(transport)
                protocol = TBinaryProtocol.TBinaryProtocolAccelerated(
                    transport)
                client = AccountManagementAPI.AccountManagement.Client(
                    protocol)
                transport.open()
                info("CallGuildFunction: %s(%r)" % (funcname, args))

                func = getattr(client, funcname)
                result = func(*args)

                info("CallGuildFunction: done")
                transport.close()
                return result
            else:
                warn("CallGuildFunction: cannot get peer for auid %d" % auid)
        else:
            warn("CallGuildFunction: guild service disabled")

        return None

    def GetGuildByName(self, shortname, fullname):
        info("agent: GetGuildByName")
        result = self.CallGuildFunction(
            "GetGuildByName", 0, shortname, fullname)
        if result.result == AccountManagementAPI.ttypes.RequestResult.Success:
          auid = result.guild.guildid
          result = self.CallGuildFunction( "GetGuildById", auid, auid )
          return result
          
        return AccountManagementAPI.ttypes.GuildInfoResponse( result = AccountManagementAPI.ttypes.RequestResult.LoginNotExist, \
                                    guild = AccountManagementAPI.ttypes.GuildInfo() )
                                    
    def GetGuildById(self, auid):
        result = self.CallGuildFunction( "GetGuildById", auid, auid )
        return result

    def GetBruteForceAccount(self, email):
        result = self.CallSimpleFunction( "GetBruteForceAccount", email )
        return result

    def UnBanBruteForceAccount(self, email):
        result = self.CallSimpleFunction( "UnBanBruteForceAccount", email )
        return result

    def GetBannedIp(self, limit, skip):
        result = self.CallSimpleFunction( "GetBannedIp", limit, skip )
        return result

    def UnBanIp(self, ip):
        result = self.CallSimpleFunction( "UnBanIp", ip )
        return result

# region Wipe

    def FindPlayerByNickname(self, nickname):
        result = self.CallSimpleFunction("FindPlayerByNickname", nickname)
        return result

    def FindPlayerByEmail(self, email):
        result = self.CallSimpleFunction("FindPlayerByEmail", email)
        return result

    def PlayerChangeEmail(self, email, newEmail, newPass):
        result = self.CallSimpleFunction("PlayerChangeEmail", email, newEmail, newPass)
        return result

    def PlayerRemoveNickname(self, email, nickname):
        result = self.CallSimpleFunction("PlayerRemoveNickname", email, nickname)
        return result

# endregion

    def GetGuildMemberById(self, auid, memberid):
        result = self.CallGuildFunction( "GetGuildMemberById", auid, auid, memberid )
        return result
                                    
    def EditGuild(self, guildInfo, gmLogin):
        result = self.CallGuildFunction( "EditGuild", guildInfo.guildid, guildInfo, gmLogin )
        return result

    def ChangeGuildLeader(self, auid, leader, gmLogin):
        result = self.CallGuildFunction(
            "ChangeGuildLeader", auid, auid, leader, gmLogin)
        return result

    def EditGuildMember(self, auid, member, gmLogin):
        result = self.CallGuildFunction( "EditGuildMember", auid, auid, member, gmLogin )
        return result

    def RemoveGuildMembers(self, auid, members, gmLogin):
        result = self.CallGuildFunction(
            "RemoveGuildMembers", auid, auid, members, gmLogin)
        return result

    def SetGuildIcon(self, auid, image):
        result = self.CallGuildFunction("SetGuildIcon", auid, auid, image)
        return result

    def SwitchToNewGuildIcon(self, auid, gmLogin):
        result = self.CallGuildFunction("SwitchToNewGuildIcon", auid, auid, gmLogin)
        return result

    def TryToPayForGuildIconChange( self, leaderauid, changeiter ):
        return self.CallFunctionByAuid( "TryToPayForGuildIconChange", leaderauid, changeiter )

    def GetFreeGuildBankTalents(self, auid):
        result = self.CallGuildFunction( "GetFreeGuildBankTalents", auid, auid )
        return result

    def GetTakenGuildBankTalents(self, auid):
        result = self.CallGuildFunction( "GetTakenGuildBankTalents", auid, auid )
        return result

    def ReturnTalentToGuildBank(self, auid, talentid, gmLogin):
        result = self.CallGuildFunction( "ReturnTalentToGuildBank", auid, auid, talentid, gmLogin )
        return result

    def ReturnTalentToOwner(self, auid, talentid, gmLogin):
        result = self.CallGuildFunction( "ReturnTalentToOwner", auid, auid, talentid, gmLogin )
        return result

    def AcquireGuildLock(self, auid, gmLogin):
        result = self.CallGuildFunction("AcquireGuildLock", auid, auid, gmLogin)
        return result

    def ReleaseGuildLock(self, auid, gmLogin):
        result = self.CallGuildFunction("ReleaseGuildLock", auid, auid, gmLogin)
        return result

    def AddGuildSuzerain(self, auid, suzerainAuid, gmLogin):
        result = self.CallGuildFunction("AddGuildSuzerain", auid, auid, suzerainAuid, gmLogin)
        return result

    def RemoveGuildSuzerain(self, auid, gmLogin):
        result = self.CallGuildFunction("RemoveGuildSuzerain", auid, auid, gmLogin)
        return result

    def StopGuildSiege(self, targetguildid, gmLogin):
        result = self.CallGuildFunction("StopGuildSiege", targetguildid, targetguildid, gmLogin)
        return result

    def GetFullGuildDump(self, auid, zip):
        return self.CallGuildFunction("GetFullGuildDump", auid, auid, zip)

    #---------------------------------------------------------------------------
    # залогиним юзера на один из WS (если он уже активен на другом WS, нам так и скажут)
    # кстати, нужно ждать момента, когда WS загрузит persistent данные юзера, а то будет неприятно
    # - за это отвечает wait_persistent=1

    def loginMe(self, login):
        ws_res = None
        peers = self.I.WS.peers
        if peers:
            ws_id = pickRandom(peers.keys())
           # сначала пробуем subLogin на случайном WS (если юзер уже залоган на другом сервере, нам так и скажут)
            peer = peers[ws_id]
            ws_addr = peer["addr"]

            snid, snuid = login.split('#')
            ws_res = httpClientRequest(
                addr=ws_addr, server="x", params="action=sublogin_fsn&snid=%s&snuid=%s&wait_persistent=1&isGM=1" % (snid, snuid))
            info("ws sublogin result: %s" % str(ws_res))
        else:
            warn("no peers available")
            return None

        if ws_res:
            ws_change_name = ws_res.get("ws_name")
            if ws_change_name:
                info("user logged on different server: ws_name %s", ws_change_name)
                ws_addr = peers[ws_change_name]["addr"]
        return ws_addr

    def CallSimpleFunction(self, name, *args, **kwargs ):
        peers = self.I.WS.peers
        if peers:
            ws_id = pickRandom(peers.keys())
           # сначала пробуем subLogin на случайном WS (если юзер уже залоган на другом сервере, нам так и скажут)
            peer = peers[ws_id]
            url = 'http://{0}/thrift?service=account_management'.format(peer["addr"])
            transport = THttpClient.THttpClient(url)
            transport.setTimeout(10 * 1000)
            transport = TTransport.TBufferedTransport(transport)
            protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
            client = AccountManagementAPI.AccountManagement.Client(protocol)
            transport.open()

            func = getattr(client, name)
            result = func(*args)

            transport.close()
            return result

    def CallFunction(self, name, login, *args, **kwargs):
        info("CallFunction(name=%r, login=%r, args=%r, kwargs=%r)", name, login, args, kwargs)
        ws_addr = self.loginMe(login)
        if ws_addr:
            url = 'http://%s/thrift?service=account_management' % ws_addr
            transport = THttpClient.THttpClient(url)
            transport.setTimeout(10 * 1000)
            transport = TTransport.TBufferedTransport(transport)
            protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
            client = AccountManagementAPI.AccountManagement.Client(protocol)
            transport.open()

            func = getattr(client, name)
            use_login = kwargs.get("use_login", True)
            info( "-> THRIFT %s calling function %r(login=%s, args=%s, kwargs=%s), use_login=%s", url, func.__name__, login, str(args), str(kwargs), use_login)
            if "use_login" in kwargs:
                del kwargs["use_login"]
            if use_login:
                result = func(login, *args, **kwargs) if kwargs else func(login, *args)
            else:
                result = func(*args, **kwargs) if kwargs else func(*args)

            transport.close()
            return result

        else:
            err("%s fail" % name)
            return None

    def CallFunctionByAuid(self, name, auid, *args, **kwargs):
        snid, snuid, email = self.RetrieveUserInfoByAuid(auid)
        info("CallFunctionByAuid(auid=%r): snid=%r, snuid=%r", auid, snid, snuid)
        if snid and snuid:
            login = "%s#%s" % (snid, snuid)
            use_auid = kwargs.get("use_auid", True)
            use_login = kwargs.get("use_login", False)
            debug("CallFunctionByAuid(auid=%r): name=%r, login=%r args=%r use_login=%r kwargs=%r ", auid, name, login, args, use_login, kwargs)
            if use_auid:
                if "use_login" not in kwargs:
                    kwargs["use_login"] = use_login
                return (
                    (self.CallFunction(name, login, auid, *args, **kwargs))
                )
            else:
                if "use_auid" in kwargs:
                    del kwargs["use_auid"]
                return (
                    (self.CallFunction(name, login,   *args, **kwargs))
                )
        else:
            return AccountManagementAPI.ttypes.RequestResult.AuidNotExist

    # ------------------ AccountManagement.Iface ------------------
    def GetAccountBySNUid(self, snid, snuid):
        login = "%s#%s" % (snid, snuid)
        result = self.CallFunction( "GetAccountBySNUid", login, snid, snuid, use_login=False)
        if result and result.result != AccountManagementAPI.ttypes.RequestResult.SnUidNotExist:
            info('retrieving email for auid=%r', result.accountInfo.auid )
            snid, snuid, email = self.RetrieveUserInfoByAuid(result.accountInfo.auid)
            info(u'retrieved: snid=%r, snuid=%r, email=%r' % (snid, snuid, email))
            if email:
                result.accountInfo.email = utf8convert(email)
        info('GetAccountBySNUid(%s) result: %r' % (login, result))
        return result

    def RetrieveUserInfoByAuid(self, auid):
        if not auid:
            err(errStack("RetrieveUserInfoByAuid called with empty auid (%r)" % auid))
            return (None, None, '')
        # для начала попробуем взять кэшированные данные (на каком ws залоган юзер)
        social_data = self.I.WS.auid2social.get(auid)
        if social_data:
            now = time.time()
            if social_data.ts + ACCOUNT_EXPIRE_SECONDS < now:
                info("RetrieveUserInfoByAuid(%s): expire old social_data=%r, now=%.3f", auid, social_data, now)
                # старый логин; скорее всего, уже протух; удаляем
                social_data = None
                self.I.WS.auid2social.pop(auid)

        if social_data:
            info("RetrieveUserInfoByAuid(%s): using cached social_data=%s", auid, str(social_data))
            return (social_data.snid, social_data.snuid, social_data.email)

        _callback = functools.partial(self.onUserInfo, auid=auid)
        url = "%s/?action=get_info&auid=%d&version=%s&include_secure_data=%d" % (http_prefix(coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS), auid, SOCAGG_VERSION, 1)
        self.I.HTTP.fetch(url, _callback)
        raise AsyncThriftException("async aggregator get_info")


    def onUserInfo(self, result, auid=0):
        snid, snuid, email = self.parseUserInfoReply(result, auid)
        self.I.WS.auid2social[auid] = ClassDict(snid=snid, snuid=snuid, email=email, ts=time.time())

        # заново запускаем обработку евента (теперь в кэше auid2social будет инфа о нашем юзере)
        self.handler.process()

    def parseUserInfoReply(self, http_reply, auid=0):
        try:
            result = json_loads(http_reply.body)
        except:
            catch()
            err("parseUserInfoReply: error parsing aggregator reply body=%s",  http_reply.body)
            result = {}
        info("parseUserInfoReply(auid=%s) result: %r", auid, result)
        if not result or 'get_info' not in result:
            return (None, None, None)

        userInfo = result['get_info']
        agg_properties = userInfo.get('props') or {}
        return pwaccount.FindSocialNetworkInfo(userInfo, agg_properties.get('fsn', None))

    def GetAccountByAuid(self, auid):
        if auid is None:
            return BadAuidError(auid)
        snid, snuid, email = self.RetrieveUserInfoByAuid(auid)
        info("GetAccountByAuid(auid=%r): snid=%r, snuid=%r, email=%r", auid, snid, snuid, utf8convert(email))
        if snid and snuid:
            result = self.GetAccountBySNUid(snid, snuid)
            if email and result and result.result == AccountManagementAPI.ttypes.RequestResult.Success:
                result.accountInfo.email = utf8convert(email)
            return result
        else:
            return AccountIsNull()

    # Возвращает возможные даты пользовательских бекапов
    def GetBackups(self):
        result = AccountManagementAPI.ttypes.UserDumpsDataResponse(avaialbleBackups=[],
                 result=AccountManagementAPI.ttypes.RequestResult.BadResponseFromDatabase)
        if len(BACKUP_MONGO_CONFIG):
            try:
                connection = Connection(BACKUP_MONGO_CONFIG["mongo_addr"], BACKUP_MONGO_CONFIG["mongo_port"],
                                        network_timeout=BACKUP_MONGO_CONFIG["network_timeout"])
                for db in connection.database_names():
                    if re.search("_" + "\d\d\d\d-\d\d-\d\d", db):
                        result.avaialbleBackups.append(db)
                result.result = AccountManagementAPI.ttypes.RequestResult.Success
            except Exception:
                catch()
        return result

    def GetBrokenUserDump(self, login, dbname, zip):
        sqlResponse = getattr(self, "sqlResponse", None)
        if sqlResponse:
            return AccountManagementAPI.ttypes.StringDataResponse(data="", result=sqlResponse)
        if login in self.I.WS.login2uid:
            result = AccountManagementAPI.ttypes.StringDataResponse(data="",
                     result=AccountManagementAPI.ttypes.RequestResult.BadResponseFromDatabase)
            if len(BACKUP_MONGO_CONFIG):
                try:
                    uid = self.I.WS.login2uid[login]
                    connection = Connection(BACKUP_MONGO_CONFIG["mongo_addr"], BACKUP_MONGO_CONFIG["mongo_port"],
                                            network_timeout=BACKUP_MONGO_CONFIG["network_timeout"])
                    dump = connection[dbname].pers.find_one({"key": "data_" + str(uid)})
                    if dump:
                        user_data = dump.get("data", {})
                        acc = PersistentDataManager.newSimpleDataAcc(user_data)
                        result.data = json_dumps(PersistentDataManager.makeSaveDict(acc))
                        result.result = AccountManagementAPI.ttypes.RequestResult.Success
                    else:
                        warn("GetBrokenUserDump: dump for login: %r wasn't found", login)
                        result.result = AccountManagementAPI.ttypes.RequestResult.BadResponseFromDatabase
                except Exception:
                    catch()
            return result
        # login is not cached, we need to pick it up first
        _callback = functools.partial(self.onSqlReply, login=login)
        self.I.SQL.findUidByLogin(login, _callback)
        raise AsyncThriftException("async aggregator GetBrokenUserDump")

    def onSqlReply(self, sql_reply, login=""):
        try:
            # достаем uid
            result = sql_reply["r"][0]
            self.I.WS.login2uid[login] = result.id
        except Exception:
                self.sqlResponse = AccountManagementAPI.ttypes.RequestResult.LoginNotExist
        self.handler.process()

    def GetBrokenUserDumpByNickname(self, nickname, dbname, zip):
        sqlResponse = getattr(self, "sqlResponse", None)
        if sqlResponse:
            return AccountManagementAPI.ttypes.StringDataResponse(data="", result=sqlResponse)
        if nickname in self.I.WS.nick2uid:
            result = AccountManagementAPI.ttypes.StringDataResponse(data="",
                     result=AccountManagementAPI.ttypes.RequestResult.BadResponseFromDatabase)
            if len(BACKUP_MONGO_CONFIG):
                try:
                    uid = self.I.WS.nick2uid[nickname]
                    connection = Connection(BACKUP_MONGO_CONFIG["mongo_addr"], BACKUP_MONGO_CONFIG["mongo_port"],
                                            network_timeout=BACKUP_MONGO_CONFIG["network_timeout"])
                    dump = connection[dbname].pers.find_one({"key": "data_" + str(uid)})
                    user_data = dump.get("data", {})
                    acc = PersistentDataManager.newSimpleDataAcc(user_data)
                    result.data = json_dumps(PersistentDataManager.makeSaveDict(acc))
                    result.result = AccountManagementAPI.ttypes.RequestResult.Success
                except Exception:
                    catch()
            return result
        # login is not cached, we need to pick it up first
        _callback = functools.partial(self.onSqlByNickReply, nickname=nickname)
        self.I.SQL.findUidByNick(nickname, _callback)
        raise AsyncThriftException("async aggregator GetBrokenUserDump")

    def onSqlByNickReply(self, sql_reply, nickname=""):
        try:
            # достаем uid
            result = sql_reply["r"][0]
            self.I.WS.nick2uid[nickname] = result.id
        except Exception:
                self.sqlResponse = AccountManagementAPI.ttypes.RequestResult.NoUsersWithThatNickname
        self.handler.process()

    def FlushServerId(self, login, gmLogin):
        self.I.SQL.forceLogout(login, None)

    def FlushServerIdByAuid(self, auid, gmLogin, extra_comment="" ):
        snid, snuid, email = self.RetrieveUserInfoByAuid(auid)
        if snid and snuid:
            login = "%s#%s" % (snid, snuid)
            self.I.SQL.forceLogout(login, None)
            return AccountManagementAPI.ttypes.RequestResult.Success
        else:
            return AccountManagementAPI.ttypes.RequestResult.AuidNotExist

    def DisjointSN(self, auid, snid):
        warn("DisjointSN({0}, {1})".format(auid, snid))
        result = self.CallFunctionByAuid("DisjointSN", auid, snid)
        return result

    def ChangeFSN(self, auid, snid):
        warn("ChangeFSN({0}, {1})".format(auid, snid))
        result = self.CallFunctionByAuid("ChangeFSN", auid, snid)
        return result

    def DeleteSAAccount(self, auid):
        warn("DeleteSAAccount({0})".format(auid))
        result = self.CallSimpleFunction("DeleteSAAccount", auid)
        return result

    def UpdateGeoshowFlag(self, auid, isAllowed):
        return self.CallFunctionByAuid("UpdateGeoshowFlag", auid, isAllowed)

    def BindToGeolocation(self, auid, country, region, city, gmLogin):
        return self.CallFunctionByAuid("BindToGeolocation", auid, country, region, city, gmLogin)

    def ApplyDLC(self, auid, dlcid):
        return self.CallFunctionByAuid("ApplyDLC", auid, dlcid)

    #---------------------------------------------------------------------------
    #---------------------------------------------------------------------------
    
    def ResetUserAccount( self, login, gmLogin ):
        result = self.CallFunction( "ResetUserAccount", login, gmLogin )
        return result

    def GetAccountLibrary(self, login):
        result = self.CallFunction("GetAccountLibrary", login)
        return result

    def GetAccountHeroes(self, login):
        result = self.CallFunction("GetAccountHeroes", login)
        return result

    def GetHeroTalentSet(self, login, heroInstanceId):
        result = self.CallFunction("GetHeroTalentSet", login, heroInstanceId)
        return result

    def GetHeroSeasonsInfo(self, login, heroInstanceId):
        result = self.CallFunction("GetHeroSeasonsInfo", login, heroInstanceId)
        return result

    def MoveTalentFromTalentSetToLibrary(
            self, login, heroInstanceId, talentInstanceId, gmLogin):
        result = self.CallFunction(
            "MoveTalentFromTalentSetToLibrary", login, heroInstanceId, talentInstanceId, gmLogin)
        return result

    def RemoveTalentFromTalentSet(
            self, login, heroInstanceId, talentInstanceId, talentSetId, gmLogin):
        result = self.CallFunction(
            "RemoveTalentFromTalentSet", login, heroInstanceId, talentInstanceId, talentSetId, gmLogin)
        return result

    def MoveTalentFromLibraryToTalentSet(
            self, login, heroInstanceId, talentInstanceId, gmLogin):
        result = self.CallFunction(
            "MoveTalentFromLibraryToTalentSet", login, heroInstanceId, talentInstanceId, gmLogin)
        return result

    def GiveLamp(self, login, lampInfo, gmLogin, extra_comment=""):
        result = self.CallFunction("GiveLamp", login, lampInfo, gmLogin, extra_comment=extra_comment)
        return result

    def GiveLampByAuid(self, login, lampInfo, gmLogin, extra_comment=""):
        result = self.CallFunctionByAuid("GiveLamp", login, lampInfo, gmLogin, use_auid=False, use_login=True, extra_comment=extra_comment)
        return result

    def GetLampInfo(self, login):
        result = self.CallFunction("GetLampInfo", login)
        return result

    def GiveUpgradeHeroTalents(self, login, lampInfo, gmLogin, extra_comment=""):
        result = self.CallFunction("GiveUpgradeHeroTalents", login, lampInfo, gmLogin, extra_comment=extra_comment)
        return result

    def GetUpgradeHeroTalentsInfo(self, login):
        result = self.CallFunction("GetUpgradeHeroTalentsInfo", login)
        return result

    def GetAccountQuestsForTalentsByAuid(self, login):
        result = self.CallFunction("GetAccountQuestsForTalentsByAuid", login)
        return result

    def EditQuestForTalent(self, login, questForTalentEdit, gmLogin, extra_comment):
        result = self.CallFunction("EditQuestForTalent", login, questForTalentEdit, gmLogin, extra_comment=extra_comment)
        return result

    def EditHero(self, login, heroEdit, gmLogin):
        result = self.CallFunction("EditHero", login, heroEdit, gmLogin)
        return result

    def UnlockHero(self, login, heroClassId, gmLogin, extra_comment=""):
        result = self.CallFunction("UnlockHero", login, heroClassId, gmLogin, extra_comment=extra_comment)
        return result

    def UnlockHeroByAuid(self, auid, heroClassId, gmLogin, extra_comment=""):
        result = self.CallFunctionByAuid("UnlockHero", auid, heroClassId, gmLogin, use_auid=False, use_login=True, extra_comment=extra_comment)
        return result

    def LockHero(self, login, heroInstanceId, gmLogin, extra_comment=""):
        result = self.CallFunction("LockHero", login, heroInstanceId, gmLogin)
        return result

    def EditSeasonAwards(self, login, awardsEdit, gmLogin, extra_comment=""):
        result = self.CallFunction("EditSeasonAwards", login, awardsEdit, gmLogin)
        return result

    def EditSeasonInfo(self, login, heroInstanceId, seasonEdit, gmLogin, extra_comment=""):
        result = self.CallFunction("EditSeasonInfo", login, heroInstanceId, seasonEdit, gmLogin)
        return result

    def EditAccount(self, login, accountEdit, gmLogin, extra_comment=""):
        result = self.CallFunction("EditAccount", login, accountEdit, gmLogin, extra_comment=extra_comment)
        return result

    def EditAccountResources(self, login, accountEdit, gmLogin,  extra_comment=""):
        result = self.CallFunction("EditAccountResources", login, accountEdit, gmLogin,  extra_comment=extra_comment)
        return result

    def EditAccountResourcesByAuid(self, auid, accountEdit, gmLogin, extra_comment=""):
        result = self.CallFunctionByAuid("EditAccountResources", auid, accountEdit, gmLogin, use_auid=False, use_login=True, extra_comment=extra_comment)
        return result

    def EditTalent(self, login, talentEdit, gmLogin):
        result = self.CallFunction("EditTalent", login, talentEdit, gmLogin)
        return result

    def AddTalent(self, login, talentClassId, gmLogin, extra_comment=""):
        result = self.CallFunction("AddTalent", login, talentClassId, gmLogin, extra_comment=extra_comment)
        return result

    def AddTalentByAuid(self, auid, talentClassId, gmLogin,  extra_comment=""):
        result = self.CallFunctionByAuid("AddTalent", auid, talentClassId, gmLogin, use_auid=False, use_login=True , extra_comment=extra_comment)
        return result

    def AddTalents(self, login, talentIds, gmLogin, extra_comment=""):
        result = self.CallFunction("AddTalents", login, talentIds, gmLogin, extra_comment=extra_comment)
        return result

    def AddTalentsByAuid(self, auid, talentIds, gmLogin,  extra_comment=""):
        result = self.CallFunctionByAuid("AddTalents", auid, talentIds, gmLogin, use_auid=False, use_login=True, extra_comment=extra_comment)
        return result

    def DeleteTalent(self, login, talentInstanceId, gmLogin):
        result = self.CallFunction(
            "DeleteTalent", login, talentInstanceId, gmLogin)
        return result

    def UserOperation(self, auid, optype, minutes, reason, claims, gmLogin, claimAuids, points ):
        return self.CallFunctionByAuid( "UserOperation", auid, optype, minutes, reason, claims, gmLogin, claimAuids, points )

    def BanUser( self, login, auid, minutes, reason, gmLogin ):
        warn("Obsolete call %s.BanUser", type(self))
        result = self.CallFunction( "BanUser", login, auid, minutes, reason, gmLogin )
        return result

    def UnbanUser( self, login, auid, gmLogin ):
        warn("Obsolete call %s.UnbanUser", type(self))
        result = self.CallFunction( "UnbanUser", login, auid, gmLogin )
        return result
    
    def MuteUser( self, login, auid, minutes, reason, gmLogin ):
        warn("Obsolete call %s.MuteUser", type(self))
        result = self.CallFunction( "MuteUser", login, auid, minutes, reason, gmLogin )
        return result

    def UnmuteUser( self, login, auid, gmLogin ):
        warn("Obsolete call %s.UnmuteUser", type(self))
        result = self.CallFunction( "UnmuteUser", login, auid, gmLogin )
        return result

    def KickUser(self, login, gmLogin):
        result = self.CallFunction("KickUser", login, gmLogin)
        return result

    def FixAccount(self, login, gmLogin):
        result = self.CallFunction("FixAccount", login, gmLogin)
        return result

    def CheckAccountValidity(self, login):
        return self.CallFunction("CheckAccountValidity", login)

    def GetSocServerVersion(self):
        result = AccountManagementAPI.ttypes.SocServerVersionResponse(
            result=AccountManagementAPI.ttypes.RequestResult.Success,
            version=PWSOC_VERSION)
        return result

    def GetAccountBuildings(self, auid):
        result = self.CallFunctionByAuid("GetAccountBuildings", auid)
        return result

    def MoveBuildingToStorage(self, auid, buildingInstanceId, gmLogin):
        result = self.CallFunctionByAuid(
            "MoveBuildingToStorage", auid, buildingInstanceId, gmLogin)
        return result

    def AddBuilding(self, auid, buildingClassId, level, gmLogin, extra_comment=""):
        result = self.CallFunctionByAuid(
            "AddBuilding", auid, buildingClassId, level, gmLogin, extra_comment=extra_comment)
        return result

    def DeleteBuilding(self, auid, buildingInstanceId, gmLogin):
        result = self.CallFunctionByAuid(
            "DeleteBuilding", auid, buildingInstanceId, gmLogin)
        return result

    def GetAccountSkins(self, auid):
        result = self.CallFunctionByAuid("GetAccountSkins", auid)
        return result

    def AddSkin(self, auid, skinPersistentId, gmLogin, extra_comment=""):
        result = self.CallFunctionByAuid(
            "AddSkin", auid, skinPersistentId, gmLogin, extra_comment)
        return result

    def DeleteSkin(self, auid, skinPersistentId, gmLogin,  extra_comment=""):
        result = self.CallFunctionByAuid(
            "DeleteSkin", auid, skinPersistentId, gmLogin,  extra_comment)
        return result

    def GetAccountTalentUpgradeEntities(self, auid):
        result = self.CallFunctionByAuid("GetAccountTalentUpgradeEntities", auid)
        return result

    def DeleteTalentUpgradeEntity(self, auid, instanceId, gmLogin,  extra_comment=""):
        result = self.CallFunctionByAuid(
            "DeleteTalentUpgradeEntity", auid, instanceId, gmLogin,  extra_comment)
        return result

    def GetFullUserDump(self, login, zip):
        return self.CallFunction("GetFullUserDump", login, zip)

    def ApplyFullUserDump(self, login, dumpdata):
        return self.CallFunction("ApplyFullUserDump", login, dumpdata)

    def RemoveFakeAuid(self, login):
        return self.CallFunction("RemoveFakeAuid", login)

    def EditFreeChanges(self, login, gmLogin, nickChanges, fractionChanges):
        return self.CallFunction( "EditFreeChanges", login, gmLogin, nickChanges, fractionChanges)

    def EditNickname(self, login, gmLogin, nickname):
        return self.CallFunction("EditNickname", login, gmLogin, nickname)

    def PayEditNickname(self, login, nickname):
        return self.CallFunction("PayEditNickname", login, nickname)

    def PayChangeFraction(self, login, fraction):
        return self.CallFunction("PayChangeFraction", login, fraction)

    def PayService(self, login, servicetype, paramValue, gmLogin):
        return self.CallFunction("PayService", login, servicetype, paramValue, gmLogin)

    def PayServiceByAuid(self, auid, servicetype, paramValue, gmLogin, extra_comment=""):
        return self.CallFunctionByAuid("PayService", auid, servicetype, paramValue, gmLogin, use_auid=False, use_login=True, extra_comment=extra_comment)

    def GetPrices(self, login, servicetype):
        return self.CallFunction("GetPrices", login, servicetype)

    def BuyService(self, login, servicetype, paramValue):
        return self.CallFunction("BuyService", login, servicetype, paramValue)

    def EditAccountDbValue(self, login, gmLogin, key, value):
        return self.CallFunction( "EditAccountDbValue", login, gmLogin, key, value )

    def BuyTournamentTicket( self, login, pttype ):
        result = self.CallFunction( "BuyTournamentTicket", login, pttype )
        return result

    def GetLocaleInfoBySNUid(self, snid, snuid):
        return self.CallFunction("GetLocaleInfoBySNUid", "%s#%s" % (snid, snuid), snid, snuid, use_login=False)

    def GetLocaleInfoByAuid(self, auid):
        return self.CallFunctionByAuid("GetLocaleInfoByAuid", auid)

    def GetQuests(self, auid):
        return self.CallFunctionByAuid("GetQuests", auid)

    def ChangeQuest(self, auid, questId, questAction, login):
        return self.CallFunctionByAuid("ChangeQuest", auid, questId, questAction, login)

    def GetAccountFlags(self, login):
        return self.CallFunction("GetAccountFlags", login)

    def LockFlag(self, login, flagPersistentId, gmLogin, extra_comment=""):
        return self.CallFunction("LockFlag", login, flagPersistentId, gmLogin, extra_comment=extra_comment)

    def LockFlagByAuid(self, auid, flagPersistentId, gmLogin, extra_comment=""):
        return self.CallFunctionByAuid("LockFlag", auid, flagPersistentId, gmLogin, use_auid=False, use_login=True, extra_comment=extra_comment)

    def UnlockFlag(self, login, flagPersistentId, gmLogin, extra_comment=""):
        return self.CallFunction("UnlockFlag", login, flagPersistentId, gmLogin, extra_comment=extra_comment)

    def UnlockFlagByAuid(self, auid, flagPersistentId, gmLogin, extra_comment=""):
        return self.CallFunctionByAuid("UnlockFlag", auid, flagPersistentId, gmLogin, use_auid=False, use_login=True, extra_comment=extra_comment)

    def AddResources(self, auid, resourceType, amount):
        result = self.CallFunctionByAuid("AddResources", auid, resourceType, amount)
        return result

    def GetAccountFriends(self, auid):
        result = self.CallFunctionByAuid("GetAccountFriends", auid)
        return result

    def RemoveFriend(self, auid, friendAuid):
        result = self.CallFunctionByAuid("RemoveFriend", auid, friendAuid)
        return result

    #-----------------------------------------------------------------------------
    def SendMessageToUser(self, login, auid, messageTitle, messageText, gmLogin, extra_comment=""):
        return self.CallFunction("SendMessageToUser", login, auid, messageTitle, messageText, gmLogin, extra_comment=extra_comment)

    def SendMessageToUserByAuid(self, auid, messageTitle, messageText, gmLogin, extra_comment=""):
        return self.CallFunctionByAuid("SendMessageToUser", auid, messageTitle, messageText, gmLogin, use_auid=True, use_login=True, extra_comment=extra_comment)

    def callbackFn(self, response):
        if not response.get("ok"):
            err("Callback failed: response %s" % response)

    def RegisterPayment(self, auid, amount, source, txnid):
        result = self.CallFunctionByAuid( "RegisterPayment", auid, amount, source, txnid)
        if result is not None:
            if isinstance(result, int) and result == AccountManagementAPI.ttypes.RequestResult.AuidNotExist:
                return AccountManagementAPI.ttypes.RegisterPaymentResponse( AccountManagementAPI.ttypes.RequestResult.AuidNotExist, 0)
            return result
        else:
            return AccountManagementAPI.ttypes.RegisterPaymentResponse( AccountManagementAPI.ttypes.RequestResult.AuidNotExist, 0)

    def ReplenishUserGold(self, auid, amount, payment_system):
        return (self.CallFunctionByAuid( "ReplenishUserGold", auid, amount, payment_system))

    def UpdateUserGold(self, auid):
        return (self.CallFunctionByAuid( "UpdateUserGold", auid))

    def GetPaymentBonusActions(self, auid):
        result = self.CallFunctionByAuid("GetPaymentBonusActions", auid)
        if result is not None:
            if isinstance(result, int) and result == AccountManagementAPI.ttypes.RequestResult.AuidNotExist:
                return AccountManagementAPI.ttypes.GetPaymentBonusActionsResponse( AccountManagementAPI.ttypes.RequestResult.AuidNotExist, None)
            return result
        else:
            return AccountManagementAPI.ttypes.GetPaymentBonusActionsResponse( AccountManagementAPI.ttypes.RequestResult.AuidNotExist, None)

    # broadcast-запросы переправляем координатору
    def CallCoordinator(self, funcname, *args):
        url = 'http://%s/thrift?service=account_management' % options.coordinator
        transport = THttpClient.THttpClient(url)
        transport.setTimeout(10 * 1000)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagementAPI.AccountManagement.Client(protocol)
        transport.open()

        func = getattr(client, funcname)
        info("-> THRIFT %s calling function %r(%s)" %
             (url, func.__name__, str(args)))
        result = func(*args)

        transport.close()
        return result
        
    def CreateBroadcast( self, createInfo, gmLogin ):
        return self.CallCoordinator( "CreateBroadcast", createInfo, gmLogin )
    def EditBroadcast( self, editInfo, gmLogin ):
        return self.CallCoordinator( "EditBroadcast", editInfo, gmLogin )
    def DeleteBroadcast( self, msgId, gmLogin ):
        return self.CallCoordinator( "DeleteBroadcast", msgId, gmLogin )
    def GetBroadcastList( self, skipLines, takeLines ):
        return self.CallCoordinator( "GetBroadcastList", skipLines, takeLines )
    def GetBroadcastLocales( self ):
        return self.CallCoordinator( "GetBroadcastLocales" )
    def StartMessageRotation( self, msgId, gmLogin ):
        return self.CallCoordinator( "StartMessageRotation", msgId, gmLogin )
    def StopMessageRotation( self, msgId, gmLogin ):
        return self.CallCoordinator( "StopMessageRotation", msgId, gmLogin )        
    def AddUserRestriction( self, snid, snuid, cbtAccessKey ):
        info("AddUserRestriction")
        return (
            self.CallCoordinator(
                "AddUserRestriction",
                snid,
                snuid,
                cbtAccessKey)
        )

    def FindNicknameExact(self, nickName):
        return self.CallCoordinator("FindNicknameExact", nickName)

    def ActivateEmail(self, email, gmLogin):
        return self.CallCoordinator("ActivateEmail", email, gmLogin)

    def GetDynamicQuestInfo(self):
        return self.CallCoordinator("GetDynamicQuestInfo")

    def GetDynamicQuestById(self, persistentId):
        return self.CallCoordinator("GetDynamicQuestById", persistentId)

    def AddDynamicQuest(self, jsonQuestData, locale, gmLogin):
        return self.CallCoordinator("AddDynamicQuest", jsonQuestData, locale, gmLogin)

    def RemoveDynamicQuest(self, questId, locale):
        return self.CallCoordinator("RemoveDynamicQuest", questId, locale)

    def GetAccountAdminMessages(self, login):
        return self.CallCoordinator("GetAccountAdminMessages", login)

    def EditDynamicQuest(self, questId, locale, jsonQuestData):
        return self.CallCoordinator("EditDynamicQuest", questId, locale, jsonQuestData)

    def GetAuidsLists(self):
        return self.CallCoordinator("GetAuidsLists")

    def GetAuidsListById(self, index):
        return self.CallCoordinator("GetAuidsListById", index)

    def AddAuidsList( self, auidsList, gmLogin ):
        return self.CallCoordinator("AddAuidsList", auidsList, gmLogin)

    def EditAuidsList(self, auidsList, gmLogin ):
        return self.CallCoordinator("EditAuidsList", auidsList, gmLogin)

    def RemoveAuidsList(self, index):
        return self.CallCoordinator("RemoveAuidsList", index)

    def GetDynamicQuestPullsInfo(self):
        return self.CallCoordinator("GetDynamicQuestPullsInfo")

    def GetDynamicQuestPullById(self, pullId):
        return self.CallCoordinator("GetDynamicQuestPullById", pullId)

    def AddDynamicQuestPull(self, questPull, gmLogin):
        return self.CallCoordinator("AddDynamicQuestPull", questPull, gmLogin)

    def EditDynamicQuestPull(self, questPull, gmLogin):
        return self.CallCoordinator("EditDynamicQuestPull", questPull, gmLogin)

    def RemoveDynamicQuestPull(self, pullId, locale, gmLogin):
        return self.CallCoordinator("RemoveDynamicQuestPull", pullId, locale, gmLogin)

    def AddDynamicQuestsToPull(self, pullId, questId, locale, gmLogin):
        return self.CallCoordinator("AddDynamicQuestsToPull", pullId, questId, locale, gmLogin)

    def RemoveDynamicQuestsFromPull(self, pullId, questId, locale, gmLogin):
        return self.CallCoordinator("RemoveDynamicQuestsFromPull", pullId, questId, locale, gmLogin)

##---------------------------------------------------------------------------------------------------
##  Event tools API
##---------------------------------------------------------------------------------------------------
    def GetAvailableEvents(self):
        return self.CallCoordinator("GetAvailableEvents")

    def ChangeEventStateById(self, persistentId, state):
        return self.CallCoordinator("ChangeEventStateById", persistentId, state)

    def DeleteEventById(self, persistentId):
        return self.CallCoordinator("DeleteEventById", persistentId)

    def AddTalentPerPerlEvent(self, eventInfo):
        return self.CallCoordinator("AddTalentPerPerlEvent", eventInfo)

    def EditTalentPerPerlEvent(self, eventInfo):
        return self.CallCoordinator("EditTalentPerPerlEvent", eventInfo)

    def GetTransmutationTalentsPerPerlById(self, persistentId):
        return self.CallCoordinator("GetTransmutationTalentsPerPerlById", persistentId)

    def GetTransmutationTalentsPerPerl(self):
        return self.CallCoordinator("GetTransmutationTalentsPerPerl")

    def AddNewsBanner(self, bannerInfo):
        return self.CallCoordinator("AddNewsBanner", bannerInfo)

    def EditNewsBanner(self, bannerInfo):
        return self.CallCoordinator("EditNewsBanner", bannerInfo)

    def GetNewsBannerById(self, persistentId):
        return self.CallCoordinator("GetNewsBannerById", persistentId)

    def GetNewsBanners(self):
        return self.CallCoordinator("GetNewsBanners")

    def AddCustomEvent(self, customEvent):
        return self.CallCoordinator("AddCustomEvent", customEvent)

    def EditCustomEvent(self, customEvent):
        return self.CallCoordinator("EditCustomEvent", customEvent)

    def GetCustomEventById(self, persistentId):
        return self.CallCoordinator("GetCustomEventById", persistentId)

    def GetCustomEvents(self):
        return self.CallCoordinator("GetCustomEvents")

    def AddSkinPricesEvent(self, skinPrice):
        return self.CallCoordinator("AddSkinPricesEvent", skinPrice)

    def EditSkinPricesEvent(self, skinPrice):
        return self.CallCoordinator("EditSkinPricesEvent", skinPrice)

    def GetSkinPriceById(self, persistentId):
        return self.CallCoordinator("GetSkinPriceById", persistentId)

    def GetSkinPrices(self):
        return self.CallCoordinator("GetSkinPrices")

    def AddHeroPricesEvent(self, heroPrice):
        return self.CallCoordinator("AddHeroPricesEvent", heroPrice)

    def EditHeroPricesEvent(self, heroPrice):
        return self.CallCoordinator("EditHeroPricesEvent", heroPrice)

    def GetHeroPriceById(self, persistentId):
        return self.CallCoordinator("GetHeroPriceById", persistentId)

    def GetHeroPrices(self):
        return self.CallCoordinator("GetHeroPrices")

    def AddCustomMap(self, customMap):
        return self.CallCoordinator("AddCustomMap", customMap)

    def EditCustomMap(self, customMap):
        return self.CallCoordinator("EditCustomMap", customMap)

    def GetCustomMapById(self, persistentId):
        return self.CallCoordinator("GetCustomMapById", persistentId)

    def GetCustomMaps(self):
        return self.CallCoordinator("GetCustomMaps")

    def AddTalentDropRarities(self, dropRarities):
        return self.CallCoordinator("AddTalentDropRarities", dropRarities)

    def EditTalentDropRarities(self, dropRarities):
        return self.CallCoordinator("EditTalentDropRarities", dropRarities)

    def GetTalentDropRarityById(self, persistentId):
        return self.CallCoordinator("GetTalentDropRarityById", persistentId)

    def GetTalentDropRarities(self):
        return self.CallCoordinator("GetTalentDropRarities")

    def AddTechs(self, techs):
        return self.CallCoordinator("AddTechs", techs)

    def EditTechs(self, techs):
        return self.CallCoordinator("EditTechs", techs)

    def GetTechsInfoById(self, persistentId):
        return self.CallCoordinator("GetTechsInfoById", persistentId)

    def GetTechsInfos(self):
        return self.CallCoordinator("GetTechsInfos")

    def AddRerollShopSlotsEvent(self, eventInfo):
        return self.CallCoordinator("AddRerollShopSlotsEvent", eventInfo)

    def EditRerollShopSlotsEvent(self, eventInfo):
        return self.CallCoordinator("EditRerollShopSlotsEvent", eventInfo)

    def GetRerollShopSlotsById(self, persistentId):
        return self.CallCoordinator("GetRerollShopSlotsById", persistentId)

    def GetRerollShopSlots(self):
        return self.CallCoordinator("GetRerollShopSlots")

    def AddRerollShopPriceEvent(self, eventInfo):
        return self.CallCoordinator("AddRerollShopPriceEvent", eventInfo)

    def EditRerollShopPriceEvent(self, eventInfo):
        return self.CallCoordinator("EditRerollShopPriceEvent", eventInfo)

    def GetRerollShopPriceById(self, persistentId):
        return self.CallCoordinator("GetRerollShopPriceById", persistentId)

    def GetRerollShopPrices(self):
        return self.CallCoordinator("GetRerollShopPrices")

    def AddReforgeTalentPriceEvent(self, eventInfo):
        return self.CallCoordinator("AddReforgeTalentPriceEvent", eventInfo)

    def EditReforgeTalentPriceEvent(self, eventInfo):
        return self.CallCoordinator("EditReforgeTalentPriceEvent", eventInfo)

    def GetReforgeTalentPriceById(self, persistentId):
        return self.CallCoordinator("GetReforgeTalentPriceById", persistentId)

    def GetReforgeTalentPrice(self):
        return self.CallCoordinator("GetReforgeTalentPrice")

    def AddRerollShopGroupPricesEvent(self, groupPrice):
        return self.CallCoordinator("AddRerollShopGroupPricesEvent", groupPrice)

    def EditRerollShopGroupPricesEvent(self, groupPrice):
        return self.CallCoordinator("EditRerollShopGroupPricesEvent", groupPrice)

    def GetRerollShopGroupPriceById(self, persistentId):
        return self.CallCoordinator("GetRerollShopGroupPriceById", persistentId)

    def GetRerollShopGroupPrices(self):
        return self.CallCoordinator("GetRerollShopGroupPrices")

    def AddRerollShopSlotPricesEvent(self, slotPrice):
        return self.CallCoordinator("AddRerollShopSlotPricesEvent", slotPrice)

    def EditRerollShopSlotPricesEvent(self, slotPrice):
        return self.CallCoordinator("EditRerollShopSlotPricesEvent", slotPrice)

    def GetRerollShopSlotPriceById(self, persistentId):
        return self.CallCoordinator("GetRerollShopSlotPriceById", persistentId)

    def GetRerollShopSlotPrices(self):
        return self.CallCoordinator("GetRerollShopSlotPrices")

    def AddRerollShopSlotAmountsEvent(self, slotAmount):
        return self.CallCoordinator("AddRerollShopSlotAmountsEvent", slotAmount)

    def EditRerollShopSlotAmountsEvent(self, slotAmount):
        return self.CallCoordinator("EditRerollShopSlotAmountsEvent", slotAmount)

    def GetRerollShopSlotAmountById(self, persistentId):
        return self.CallCoordinator("GetRerollShopSlotAmountById", persistentId)

    def GetRerollShopSlotAmount(self):
        return self.CallCoordinator("GetRerollShopSlotAmount")

    def AddRerollShopGroupProbabilityEvent(self, groupProbabilities):
        return self.CallCoordinator("AddRerollShopGroupProbabilityEvent", groupProbabilities)

    def EditRerollShopGroupProbabilityEvent(self, groupProbabilities):
        return self.CallCoordinator("EditRerollShopGroupProbabilityEvent", groupProbabilities)

    def GetRerollShopGroupProbabilityById(self, persistentId):
        return self.CallCoordinator("GetRerollShopGroupProbabilityById", persistentId)

    def GetRerollShopGroupProbabilities(self):
        return self.CallCoordinator("GetRerollShopGroupProbabilities")

    def AddRerollShopGroupCurrenciesEvent(self, groupCurrencies):
        return self.CallCoordinator("AddRerollShopGroupCurrenciesEvent", groupCurrencies)

    def EditRerollShopGroupCurrenciesEvent(self, groupCurrencies):
        return self.CallCoordinator("EditRerollShopGroupCurrenciesEvent", groupCurrencies)

    def GetRerollShopGroupCurrenciesById(self, persistentId):
        return self.CallCoordinator("GetRerollShopGroupCurrenciesById", persistentId)

    def GetRerollShopGroupCurrencies(self):
        return self.CallCoordinator("GetRerollShopGroupCurrencies")

    def AddFirstBuyPricesEvent(self, firstBuyPrice):
        return self.CallCoordinator("AddFirstBuyPricesEvent", firstBuyPrice)

    def EditFirstBuyPricesEvent(self, firstBuyPrice):
        return self.CallCoordinator("EditFirstBuyPricesEvent", firstBuyPrice)

    def GetFirstBuyPriceById(self, persistentId):
        return self.CallCoordinator("GetFirstBuyPriceById", persistentId)

    def GetFirstBuyPrices(self):
        return self.CallCoordinator("GetFirstBuyPrices")

    def AddRerollShopPremiumNotInactiveEvent(self, firstBuyPrice):
        return self.CallCoordinator("AddRerollShopPremiumNotInactiveEvent", firstBuyPrice)

    def EditRerollShopPremiumNotInactiveEvent(self, firstBuyPrice):
        return self.CallCoordinator("EditRerollShopPremiumNotInactiveEvent", firstBuyPrice)

    def GetRerollShopPremiumNotInactiveById(self, persistentId):
        return self.CallCoordinator("GetRerollShopPremiumNotInactiveById", persistentId)

    def GetRerollShopPremiumNotInactive(self):
        return self.CallCoordinator("GetRerollShopPremiumNotInactive")

    def AddRerollShopGroupSlotsEvent(self, groupSlots):
        return self.CallCoordinator("AddRerollShopGroupSlotsEvent", groupSlots)

    def EditRerollShopGroupSlotsEvent(self, groupSlots):
        return self.CallCoordinator("EditRerollShopGroupSlotsEvent", groupSlots)

    def GetRerollShopGroupSlotsById(self, persistentId):
        return self.CallCoordinator("GetRerollShopGroupSlotsById", persistentId)

    def GetRerollShopGroupSlots(self):
        return self.CallCoordinator("GetRerollShopGroupSlots")

    def AddRerollShopBanner(self, bannerInfo):
        return self.CallCoordinator("AddRerollShopBanner", bannerInfo)

    def EditRerollShopBanner(self, bannerInfo):
        return self.CallCoordinator("EditRerollShopBanner", bannerInfo)

    def GetRerollShopBannerById(self, persistentId):
        return self.CallCoordinator("GetRerollShopBannerById", persistentId)

    def GetRerollShopBanners(self):
        return self.CallCoordinator("GetRerollShopBanners")

    def AddRerollShopTooltip(self, tooltipInfo):
        return self.CallCoordinator("AddRerollShopTooltip", tooltipInfo)

    def EditRerollShopTooltip(self, tooltipInfo):
        return self.CallCoordinator("EditRerollShopTooltip", tooltipInfo)

    def GetRerollShopTooltipById(self, persistentId):
        return self.CallCoordinator("GetRerollShopTooltipById", persistentId)

    def GetRerollShopTooltips(self):
        return self.CallCoordinator("GetRerollShopTooltips")

    def GetRollEvents(self):
        return self.CallCoordinator("GetRollEvents")

    def GetRollEventById(self, persistentId):
        return self.CallCoordinator("GetRollEventById", persistentId)

    def AddRollEvent(self, rollEvent):
        return self.CallCoordinator("AddRollEvent", rollEvent)

    def EditRollEvent(self, rollEvent):
        return self.CallCoordinator("EditRollEvent", rollEvent)

    def GetQuestEvents(self):
        return self.CallCoordinator("GetQuestEvents")

    def GetQuestEventById(self, persistentId):
        return self.CallCoordinator("GetQuestEventById", persistentId)

    def AddQuestEvent(self, questEvent):
        return self.CallCoordinator("AddQuestEvent", questEvent)

    def EditQuestEvent(self, questEvent):
        return self.CallCoordinator("EditQuestEvent", questEvent)

    def GetTradeEvents(self):
        return self.CallCoordinator("GetTradeEvents")

    def GetTradeEventById(self, persistentId):
        return self.CallCoordinator("GetTradeEventById", persistentId)

    def AddTradeEvent(self, tradeEvent):
        return self.CallCoordinator("AddTradeEvent", tradeEvent)

    def EditTradeEvent(self, tradeEvent):
        return self.CallCoordinator("EditTradeEvent", tradeEvent)

    def GetSeasonEvents(self):
        return self.CallCoordinator("GetSeasonEvents")

    def GetSeasonEventById(self, persistentId):
        return self.CallCoordinator("GetSeasonEventById", persistentId)

    def AddSeasonEvent(self, seasonEvent):
        return self.CallCoordinator("AddSeasonEvent", seasonEvent)

    def EditSeasonEvent(self, seasonEvent):
        return self.CallCoordinator("EditSeasonEvent", seasonEvent)

    def GetDonateEvents(self):
        return self.CallCoordinator("GetDonateEvents")

    def GetDonateEventById(self, persistentId):
        return self.CallCoordinator("GetDonateEventById", persistentId)

    def AddDonateEvent(self, donateEvent):
        return self.CallCoordinator("AddDonateEvent", donateEvent)

    def EditDonateEvent(self, donateEvent):
        return self.CallCoordinator("EditDonateEvent", donateEvent)

    def GetGWEvents(self):
        return self.CallCoordinator("GetGWEvents")

    def GetGWEventsModelById(self, persistentId):
        return self.CallCoordinator("GetGWEventsModelById", persistentId)

    def EditGWEvent(self, gwEvent, gmLogin):
        return self.CallCoordinator("EditGWEvent", gwEvent, gmLogin)


##---------------------------------------------------------------------------------------------------
    def GetAccountTournamentInfo( self, login ):
        result = self.CallFunction( "GetAccountTournamentInfo", login )
        return result

    def EditTournamentInfo( self, login, tournamentInfo, gmLogin ):
        result = self.CallFunction( "EditTournamentInfo", login, tournamentInfo, gmLogin )
        return result

    def GiveTournamentTicket( self, login ):
        result = self.CallFunction( "GiveTournamentTicket", login )
        return result

    def GetAccountTournamentGames( self, login ):
        result = self.CallFunction( "GetAccountTournamentGames", login )
        return result
##---------------------------------------------------------------------------------------------------

    def GetSocialNetworks(self):
        if self.I.WS.snList['error']:
            self.I.WS.snList['error'] = 0
            return AccountManagementAPI.ttypes.SocialNetworksResponse(
                result=AccountManagementAPI.ttypes.RequestResult.BadResult,
                socialnetworks=[])

        if self.I.WS.snList['tm'] < time.time():
            self.I.AGG.listSn(self.onListSn)
            raise AsyncThriftException("async aggregator get_info")

        return AccountManagementAPI.ttypes.SocialNetworksResponse(
            result = AccountManagementAPI.ttypes.RequestResult.Success,
            socialnetworks = self.I.WS.snList['data'])

    def onListSn(self, response):
        if response.get('error', 0):
            self.I.WS.snList['error'] = response['error']
        else:
            self.I.WS.snList['tm'] = time.time() + SN_LIST_KEEP_TIME
            self.I.WS.snList['data'] = response.get("snlist", [])
        self.handler.process()

##---------------------------------------------------------------------------------------------------

    def GetMassOperationsInfo(self):
        result = AccountManagementAPI.ttypes.MassOperationsResultResponse(
            result=AccountManagementAPI.ttypes.RequestResult.Success, massOperations=[])
        for operationId, operation in self.I.WS.massOperationsHistory.iteritems():
            result.massOperations.append(AccountManagementAPI.ttypes.MassOperationResult(
                startTime=operation["startTime"], type=operation["type"],
                endTime=operation["endTime"], finished=operation["finished"],
                failedAuids=','.join(operation["failed"]), operationId=operationId)
            )
        return result

    def DeleteMassOperationInfo(self, operationId):
        if operationId in self.I.WS.massOperationsHistory:
            del self.I.WS.massOperationsHistory[operationId]
        return AccountManagementAPI.ttypes.RequestResult.Success

    def AddMassOperation(self, operationInfo, gmLogin):
        args = []
        kwargs = {}
        massOperation = {"type": operationInfo.type, "auids": operationInfo.auids, "id": self.I.WS.nextMOId}
        self.I.WS.nextMOId += 1

        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.AddSkin:
            args = [operationInfo.skinId, gmLogin]
            massOperation["handlerFunc"] = "AddSkin"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.DeleteSkin:
            args = [operationInfo.skinId, gmLogin]
            massOperation["handlerFunc"] = "DeleteSkin"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.AddTalent:
            args = [operationInfo.talentId, gmLogin]
            massOperation["handlerFunc"] = "AddTalentByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.AddTalents:
            args = [operationInfo.talentIds, gmLogin]
            massOperation["handlerFunc"] = "AddTalentsByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.PremiumAccount:
            args = [1, operationInfo.days, gmLogin]
            massOperation["handlerFunc"] = "PayServiceByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.SendMessageToUser:
            args = ["", operationInfo.message, gmLogin]
            massOperation["handlerFunc"] = "SendMessageToUserByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.GiveLamp:
            args = [operationInfo.lampInfo, gmLogin]
            massOperation["handlerFunc"] = "GiveLampByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.UnlockFlag:
            args = [operationInfo.flagId, gmLogin]
            massOperation["handlerFunc"] = "UnlockFlagByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.LockFlag:
            args = [operationInfo.flagId, gmLogin]
            massOperation["handlerFunc"] = "LockFlagByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.UnlockHero:
            args = [operationInfo.heroId, gmLogin]
            massOperation["handlerFunc"] = "UnlockHeroByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.AddBuilding:
            args = [operationInfo.buildingId, 0, gmLogin]
            massOperation["handlerFunc"] = "AddBuilding"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.EditAccount:
            args = [operationInfo.accountEdit, gmLogin]
            massOperation["handlerFunc"] = "EditAccountResourcesByAuid"
        if operationInfo.type == AccountManagementAPI.ttypes.MassOperationType.FlushServerId:
            args = [gmLogin]
            massOperation["handlerFunc"] = "FlushServerIdByAuid"
        massOperation["args"] = args
        kwargs.update({"extra_comment": "MassOperation"})
        massOperation["kwargs"] = kwargs
        self.I.WS.massOperations.append(massOperation)
        self.I.WS.massOperationsHistory[massOperation["id"]] = {"startTime": int(time.time()), "endTime": int(time.time()),
                                                                "auidsLeft": len(operationInfo.auids), "failed": [],
                                                                "finished": False, "type": massOperation["type"]}
        self.result = 1
        return AccountManagementAPI.ttypes.RequestResult.Success
##---------------------------------------------------------------------------------------------------
    
class Forward2CooordinatorProcessor:

    """ переправляем внешний запрос AS IS в сторону координатора """

    def __init__(self, handler):
        self.handler = handler

    def process(self, iprot, oprot):
        # input protocol, output protocol -- это просто MemoryBuffer;
        # поэтому отправляем input как HTTP POST в сторону координатора, и засовываем в oprot то, что придет в http response
        transport = THttpClient.THttpClient('http://%s/thrift?service=%s' % (
            options.coordinator, self.handler.thrift_handler.service))
        transport.setTimeout(10 * 1000)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)

        transport.open()

        # переправляем туда все, что пришло во входящем буфере:
        transport.write(iprot.trans.getvalue())
        transport.flush()

        # забираем все, что там пришло в ответ:
        reply_bytes = transport.read(-1)
        info("transport: %s\n transport.read: %s" %
             (str(transport), str(reply_bytes)))

        transport.close()
        oprot.trans.write(reply_bytes)


class Forward2CooordinatorHandler:

    def __init__(self, thrift_handler):
        self.thrift_handler = thrift_handler

    @staticmethod
    def getProcessorClass():
        return Forward2CooordinatorProcessor


class ThriftAgentInternalHandler(JsonHandler):

    """ обрабатываем только служебные команды от координатора """
    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
        # --- служебное ----
        # base JsonHandler: умеем отвечать, что мы живы
        'check_alive': 'onCheckWebServerAlive',
        'peer': PeerServerStatusAction,
        # base JsonHandler: апдейтим статус peer WS-ок
    }


class ThriftAgentServer(ITornadoServer):

    """ Thrift Agent веб-сервер (принимает внешние запросы по thrift, мапит их на внутрикластерные http-запросы) """

    _SERVICES = {
        "account_management": AccountManagementAgentHandler,
        # этот сервис сначала исполняет кастомную кластерную логику (лезет в memcache/sql), а потом отправляет суб-запросы на WS
        "serverinfo": Forward2CooordinatorHandler,
        # этот сервис перенаправляет все свои запросы напрямую координатору
    }

    def __init__(self, **kwargs):
        super(ThriftAgentServer, self).__init__(**kwargs)
        self.ws_logins = {}  # login -> {server_name, ts}
        self.auid2social = {}  # auid -> {snid, snuid, nick, ts}
        self.login2uid = {}  # login -> uid
        self.nick2uid = {}  # nickname -> uid
        self.massOperations = []
        self.massOperationsHistory = {}
        self.nextMOId = 0
        self.snList = {'data': [], 'tm': 0, 'error': 0}

    # OVERRIDE
    def onGetPeerServer(self, peer, peer_name, peer_id, status):
        if status == PEER_DELETED:
            return
        if peer_id:
            self.peers[peer_name] = peer

    def initHandlers(self, application):
        info("ThriftAgentServer initHandlers: WS=%s, HTTP=%s"
             % (str(getattr(self, "WS", None)), str(getattr(self, "HTTP", None))))

        application.add_handlers(r"(.*)", [
            (r"/thrift", ThriftHandler, dict(I=self.I, SERVICES=ThriftAgentServer._SERVICES)),
            (r"/x", ThriftAgentInternalHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I)),
        ])

        self.getPeersFromCoordinator()

    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = THRIFT_AGENT_ID
            options.server_name = THRIFT_AGENT_NAME
            options.server_class = "thrift"
        else:
            options["server_id"].set(THRIFT_AGENT_ID)
            options["server_name"].set(THRIFT_AGENT_NAME)
            options["server_class"].set("thrift")


    @staticmethod
    def initInterfaces(classOf=None):
        iDict = ClassDict()

        # http-клиент, потенциально -- для запросов к facebook и zzima api
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient(
            max_clients=coord_cfg.COORDINATOR_HTTP_CURL_WORKERS)
        iDict.CHAT = IfaceFactory.makeIChatServerInterface(
            options.chat, coord_cfg.COORDINATOR_CHAT_SERVICES, HTTP=iDict.HTTP)

        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager()

        iDict.GS = IfaceFactory.makeGuildServiceInterface(
            options.guilds, coord_cfg.COORDINATOR_GUILD_SERVICES, HTTP=iDict.HTTP)

        iDict.AGG = IfaceFactory.makeSocAggInterface(options.soc_agg,
            http_prefix(coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS), SOCAGG_VERSION, HTTP=iDict.HTTP )

        iDict.SQL = IfaceFactory.makeSqlInterface(options.sql, coord_cfg.COORDINATOR_SQL_CONFIG,
            num_threads=coord_cfg.COORDINATOR_SQL_THREADS)

        return iDict

    # -----------------------------------------------
    def run_handler(self, args, kwargs, functionName, historyOperation):
        handler = AccountManagementAgentHandler(ClassDict(service=None, I=self.I))
        # если информации о пользователе нет на сервере, мы ищем его логин
        # и потом ещё раз вызываем функцию-обработчик через process
        handler.handler.process = lambda: self.run_result_handler(getattr(handler, functionName), historyOperation, args, kwargs)
        try:
            result = getattr(handler, functionName)(*args, **kwargs)
            historyOperation["auidsLeft"] -= 1
            if result != AccountManagementAPI.ttypes.RequestResult.Success:
                historyOperation["failed"].append(str(args[0]))
            if historyOperation["auidsLeft"] == 0:
                historyOperation["finished"] = True
                historyOperation["endTime"] = int(time.time())
                debug("historyOp = %r", self.massOperationsHistory)
        except AsyncThriftException:
            pass

    def run_result_handler(self, processorFunction, historyOperation, args, kwargs):
        if processorFunction(*args, **kwargs) != AccountManagementAPI.ttypes.RequestResult.Success:
            # Первым аргументом всегда является ауид пользователя
            historyOperation["failed"].append(str(args[0]))
        historyOperation["auidsLeft"] -= 1
        if historyOperation["auidsLeft"] == 0:
            historyOperation["finished"] = True
            historyOperation["endTime"] = int(time.time())
            debug("historyOp = %r", self.massOperationsHistory)

    def tick(self):
        #debug( "!thrift tick" )
        t0 = time.time()
        operationsToRemove = []
        usersToHandle = AUIDS_UPDATE_PER_TICK
        for massOperation in self.massOperations:
            for auid in massOperation["auids"][:]:
                args = [auid]
                args.extend(massOperation["args"])
                kwargs = massOperation.get("kwargs", {})
                debug("~thrift tick: run_handler(%r, %r, %r, %r) ", args, kwargs, massOperation["handlerFunc"], self.massOperationsHistory[massOperation["id"]])
                self.run_handler(args, kwargs, massOperation["handlerFunc"], self.massOperationsHistory[massOperation["id"]])
                massOperation["auids"].remove(auid)
                # чтобы не перегружать сервер, обрабатываем только часть аккаунтов за один tick
                usersToHandle -= 1
                if not usersToHandle:
                    return
            if not len(massOperation["auids"]):
                operationsToRemove.append(massOperation)
        for massOperation in operationsToRemove:
            self.massOperations.remove(massOperation)
        t1 = time.time()
        if t1-t0 > 0.001:
            debug( "~thrift tick: %.3f sec" % (t1-t0) )

def main():
    ITornadoServer.main(ThriftAgentServer)

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8706
    else:
        options["port"].set(8706)
    main()
