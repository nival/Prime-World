# -*- coding: utf-8 -*-

# обработка account-management запросов на координаторе (почему-то именно в account management API вошли команды, управляющие глобальными бродкастами)
# (C) Dan Vorobiev 2012, Nival Network

from base.helpers import *
import functools
import json
from binascii import crc32
from enums import ETalentRarity
from modeldata import DynamicQuest
from bson import ObjectId
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------
addRelPath('gen-py')

import AccountManagementAPI.AccountManagement
import AccountManagementAPI.ttypes

from base.http_dumb import httpClientRequest
import coord_cfg
import CC

from AccountManagementAPI.AccountManagement import RequestResult, BroadcastListResponse, BroadcastCreateResponse, BroadcastLocalesResponse, BroadcastMessage
from AccountManagementAPI.ttypes import RequestResult, ConfigEventType
from thrift_handler import AsyncThriftException
from ext_pw.sexchange import FindNickSnidAction

# --------------------------------------------------------------------------------------

class BroadcastMessageData( object ):
    def __init__(self, Id=0, message=None, tLastSent=0):
        self.Id = Id
        self.message = message
        self.tLastSent = tLastSent

    def toJson(self):
        data = {}
        for msg in self.message.Messages:
            data[msg.Locale] = utf8convert(msg.Text)
        return json.dumps(data, ensure_ascii=False)
        
    def fromJson(self, content):
        # Оставила так, чтобы можно было цеплять бродкасты старого формата. PF-84192.
        try:
            data = json.loads(content)
            if not isinstance(data, dict):
                data = {"RU": str(data)}
        except Exception:
            data = {"RU": content}
        messages = []
        for locale, text in data.items():
            loc = BroadcastMessage(Locale=locale, Text=utf8convert(text))
            messages.append(loc)
        self.message.Messages = messages

# --------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------


class BroadcastHandler( AccountManagementAPI.AccountManagement.Iface ):
    """ """
    def __init__( self, handler ):
        self.handler = handler
        self.I = handler.I
        self.service = handler.service
        
    @staticmethod
    def getProcessorClass():
        return AccountManagementAPI.AccountManagement.Processor

    # RequestResult CreateBroadcastMessage(1: BroadcastMessage createMessage, 2: string gmLogin),
    def CreateBroadcast( self, createInfo, gmLogin ):
        info( "CreateBroadcast: createInfo %s, gmLogin %s" % (createInfo, gmLogin) )
        try:
            if createInfo and len(createInfo.Messages) > 0:
                msgData = self.I.WS.addBroadcast(createInfo)
                response = BroadcastCreateResponse( result=RequestResult.Success, id=msgData.Id )
                return response
            else:
                response = BroadcastCreateResponse( result=RequestResult.BadResult, id=0 )
                warn("CreateBroadcast: bad message (or MessageText)")
                return response
        except:
            catch()
            return BroadcastCreateResponse( result=RequestResult.BadResult, msgId=0 )
        
    # RequestResult EditBroadcastMessage(1: BroadcastMessage editInfo, 2: string gmLogin),
    def EditBroadcast( self, editInfo, gmLogin ):
        info( "EditBroadcast: editInfo %s, gmLogin %s" % (editInfo, gmLogin) )
        try:
            if editInfo and editInfo.Id and len(editInfo.Messages):
                if self.I.WS.editBroadcast(editInfo):
                    return RequestResult.Success
                else:
                    warn("EditBroadcast: no such msgId (%s)" % editInfo.Id)
                    return RequestResult.BadResult
            else:
                warn("EditBroadcast: bad editInfo (or Id/Text)")
                return RequestResult.BadResult
        except:
            catch()
            return RequestResult.BadResult
            
        
    # RequestResult DeleteBroadcastMessage(1: i32 mesId, 2: string gmLogin),
    def DeleteBroadcast( self, msgId, gmLogin ):
        info( "DeleteBroadcast: msgId %s, gmLogin %s" % (msgId, gmLogin) )
        try:
            if self.I.WS.deleteBroadcast(msgId):
                return RequestResult.Success
            else:
                warn("DeleteBroadcast: bad or non-existing msgId (%s)" % msgId)
                return RequestResult.BadResult
        except:
            catch()
            return RequestResult.BadResult
        
    # BroadcastListResponse GetBroadcastList(1: i32 skipLines, 2: i32 takeLines),
    def GetBroadcastList( self, skipLines, takeLines ):
        info( "GetBroadcastList: skipLines %s, takeLines %s" % (skipLines, takeLines) )
        response = BroadcastListResponse( result=RequestResult.Success, broadcastList=[] )
        
        try:
            # сортируем сообщения по msgId и возвращаем требуемую выборку
            keys = sorted( self.I.WS.broadcasts.keys() )
            
            fromIndex = skipLines
            if (not fromIndex) or (fromIndex < 0):
                fromIndex = 0
            if (not takeLines) or (takeLines < 0):
                takeLines = len(keys)
            toIndex = fromIndex + takeLines
            
            info( "GetBroadcastList: keys len %s, corrected range: [%s:%s]" % (len(keys), fromIndex, toIndex ))
            picked_keys = keys[ fromIndex:toIndex ]
                
            for msgId in picked_keys:
                msgData = self.I.WS.broadcasts.get(msgId)
                response.broadcastList.append( msgData.message )
        except:
            catch()
            response.result = RequestResult.BadResult
        
        return response

    # BroadcastListResponse GetBroadcastList(1: i32 skipLines, 2: i32 takeLines),
    def GetBroadcastLocales( self ):
        locales = ['RU', 'EN', 'TR', 'DE', 'ES', 'FR', 'LT']
        return BroadcastLocalesResponse( result=RequestResult.Success, locales=locales )

    # RequestResult StartMessageRotation(1: i32 mesId, 2: string gmLogin),
    def StartMessageRotation( self, msgId, gmLogin ):
        info( "StartMessageRotation: msgId %s, gmLogin %s" % (msgId, gmLogin) )
        try:
            if msgId in self.I.WS.broadcasts:
                msgData = self.I.WS.broadcasts[ msgId ]
                msgData.message.EnabledNow = True
                
                # ################## 
                # TEST
                # пока что просто сразу отправим бродкаст, однократно
                #~ params = dict( action="broadcast", message=msgData.message.MessageText )
                #~ response = httpClientRequest( addr=coord_cfg.COORDINATOR_BALANCER_INTERNAL, server="x", params=urllib.urlencode(params) )
                #~ info( "broadcast response: %s" % response )
                # ################## 
                
                return RequestResult.Success
            else:
                warn("StartMessageRotation: bad or non-existing msgId (%s)" % msgId)
                return RequestResult.BadResult
        except:
            catch()
            return RequestResult.BadResult
        
    # RequestResult StopMessageRotation(1: i32 mesId, 2: string gmLogin),
    def StopMessageRotation( self, msgId, gmLogin ):
        info( "StopMessageRotation: msgId %s, gmLogin %s" % (msgId, gmLogin) )
        try:
            if msgId in self.I.WS.broadcasts:
                msgData = self.I.WS.broadcasts[ msgId ]
                msgData.message.EnabledNow = False
                return RequestResult.Success
            else:
                warn("StopMessageRotation: bad or non-existing msgId (%s)" % msgId)
                return RequestResult.BadResult
        except:
            catch()
            return RequestResult.BadResult

    def AddUserRestriction( self, snid, snuid, cbtAccessKey ):
        result = getattr(self, "result", None)
        info( "AddUserRestriction: snid=%r, snuid=%r, cbtAccessKey=%r, self.result=%r" % (snid, snuid, cbtAccessKey, result) )
        if result is None:
            try:
                login = "%s:%s" % (snid, snuid)
                self.I.SQL.cbtAddRestrictedUser( login, toint(time.time()), cbtAccessKey, self.onSqlAddRestrictedUser )
            except:
                catch()
                return RequestResult.BadResult
                
            # срубаем thrift-обработчик на время исполнения запроса к mysql
            raise AsyncThriftException("async cbtAddRestrictedUser call") 
        else:
            return result
            
    def onSqlAddRestrictedUser( self, sql_reply ):
        try:
            info("onSqlAddRestrictedUser: sql_reply=%s" % sql_reply)
            if sql_reply["r"]:
                self.result = RequestResult.Success
            else:
                self.result = RequestResult.BadResult
        except:
            self.result = RequestResult.BadResult
        # после асинхронного ответа заново вызываем thrift-обработчик
        self.handler.process()
        
        
        
    # ------------------------------------------------------------------------

    def FindNicknameExact(self, nickName):
        result = getattr(self.handler, "findNicknameResult", None)
        if not result:
            callback = functools.partial( self.onFindNickSnidAction, nick=nickName )
            action = FindNickSnidAction( nick=nickName, I=self.I, fin_callback=callback )
            action.onStart()
            raise AsyncThriftException("async FindNickSnidAction call")
        else:
            return result
            
    def onFindNickSnidAction(self, response, nick=""):
        info("onFindNickSnidAction(nick=%r): response %r" % (nick, response))
        if response.get("ok"):
            snid = response.get("snid", "")
            snuid = response.get("snuid", "")
            login = response.get("login", "")
            foundAccount = AccountManagementAPI.ttypes.AccountShortInfo(snid=snid, snuid=snuid, login=login, nickname=nick)
            self.handler.findNicknameResult = AccountManagementAPI.ttypes.NickSnidResponse(result=RequestResult.Success, foundAccount=foundAccount)
        else:
            self.handler.findNicknameResult = AccountManagementAPI.ttypes.NickSnidResponse(result=RequestResult.LoginNotExist)
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def ActivateEmail(self, email, gmLogin):
        result = getattr(self.handler, "result", None)
        if result is None:
            callback = functools.partial( self.onActivateEmail, email=email )
            self.I.SQL.pwcGetByEmail(email, callback)
            raise AsyncThriftException("async ActivateEmail call")
        else:
            return result

    def onActivateEmail(self, sql_reply, email=""):
        info("onActivateEmail(email=%r): sql_reply %r" % (email, sql_reply))
        if "r" in sql_reply and len (sql_reply["r"]) > 0:
            result = sql_reply["r"][0]
            if result.active == 1:
                self.handler.result = RequestResult.EmailAlreadyActivated
            else:
                self.I.SQL.pwcForceActivate(email)
                self.handler.result = RequestResult.Success
        else:
            self.handler.result = RequestResult.EmailNotExist
        self.handler.process() # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetDynamicQuestInfo(self):
        result = getattr(self.handler, "findDynamicQuestsResult", None)
        info("GetDynamicQuestInfo.onStart")
        if not result:
            self.I.DATA.find(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                             {"key": {"$exists": True}},
                             params=None, callback=self.onGetDynamicQuestList)
            raise AsyncThriftException("async GetDynamicQuestInfo call")
        else:
            return result

    def onGetDynamicQuestList(self, response):
        self.handler.findDynamicQuestsResult = AccountManagementAPI.ttypes.DynamicQuestInfoResponse(
            result=RequestResult.BadServiceType, quests=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    # Если квест не активен, не показываем его в GMTools.
                    if "removed" in obj and obj["removed"]:
                        continue
                    pullId = None
                    if "pullId" in obj:
                        pullId = obj["pullId"]

                    questInfo = None
                    try:
                        questInfo = AccountManagementAPI.ttypes.DynamicQuestInfo(QuestText=utf8convert(obj["data"]), Locale=obj["locale"],
                                                                             Index=obj["key"], PullId=pullId)
                    except Exception:
                        err("Bad quest Data: %r", obj)
                        catch()
                        continue
                    else:
                        self.handler.findDynamicQuestsResult.quests.append(questInfo)

                self.handler.findDynamicQuestsResult.result = RequestResult.Success
            except:
                catch()
                self.handler.findDynamicQuestsResult.result = RequestResult.BadResult

        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetDynamicQuestById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetDynamicQuestById.onStart")
        if not result:
            self.I.DATA.find_one(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                             {"key": persistentId},
                             params=None, callback=self.onGetDynamicQuestById)
            raise AsyncThriftException("async GetDynamicQuestById call")
        else:
            return result

    def onGetDynamicQuestById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.DynamicQuestByIdResponse(
            result=RequestResult.BadServiceType, quest=None)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                # Если квест не активен, не показываем его в GMTools.
                if "removed" in obj and obj["removed"]:
                    self.handler.process()
                    return
                pullId = None
                if "pullId" in obj:
                    pullId = obj["pullId"]
                self.handler.result.quest = AccountManagementAPI.ttypes.DynamicQuestInfo(
                                                QuestText=utf8convert(obj["data"]), Locale=obj["locale"],
                                                Index=obj["key"], PullId=pullId)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult

        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)


    def AddDynamicQuest(self, jsonQuestData, locale, gmLogin):
        result = getattr(self.handler, "result", None)
        info("AddDynamicQuest.onStart, result = %r", result)
        if result is None:
            self.questData = jsonQuestData
            self.locale = locale
            try:
                self.questDict = json.loads(self.questData)
            except Exception:
                catch()
                warn("AddDynamicQuest: can't parse json string %r" % self.questData)
                return AccountManagementAPI.ttypes.AddDynamicQuestResponse(
                    result=RequestResult.DynamicQuestHasIllegalSynthaxis, questId=0, details="can't parse json string")

            validateDetails = DynamicQuest.DynamicQuest.validateJsonQuest(self.questDict)
            if validateDetails[0]:
                self.I.DATA.find_and_modify(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                            {"last_id": {"$exists": True}}, update={"$inc": {"last_id": 1}}, new=True,
                                            params=None, callback=self.onUpdateNextQuestIndex)
                raise AsyncThriftException("async AddDynamicQuest call")
            else:
                return AccountManagementAPI.ttypes.AddDynamicQuestResponse(
                    result=RequestResult.DynamicQuestHasIllegalSynthaxis, questId=0, details=validateDetails[1])
        else:
            return result

    def onUpdateNextQuestIndex(self, response):
        if response and response["r"] is not None:
            self.questId = response["r"]["last_id"]
            self.I.DATA.insert(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                               {"key": self.questId, "data": self.questData, "locale": self.locale, "version": 0},
                               params=None, callback=self.onAddDynamicQuest)
        else:
            self.handler.result = RequestResult.BadResponseFromDatabase
            self.handler.process()

    def onAddDynamicQuest(self, response):
        self.handler.result = AccountManagementAPI.ttypes.AddDynamicQuestResponse(
          result=RequestResult.BadResponseFromDatabase, questId=0)
        info("onAddDynamicQuest.response = %r", response)
        if response:
            if "AuidList" in self.questDict["AcceptFilter"] and int(self.questDict["AcceptFilter"]["AuidList"]) != 0:
                self.I.DATA.find_one(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                     {"auidsKey": int(self.questDict["AcceptFilter"]["AuidList"])},
                                     params=None, callback=functools.partial(self.onGetAuidsListForQuest,
                                                                             action='add_new_dynamic_quest'))
                return
            self.notifyOnDynamicQuestChange('add_new_dynamic_quest')
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def notifyOnDynamicQuestChange(self, action):
        # разослать всем рабочим серверам
        args = {
            'action': action,
            'jsonQuestData': self.questData,  # urlQuote больше не нужен, XHTTP.fetch и так делает
            'persistentId': self.questId,
            'locale': self.locale,
        }

        self.I.WS.updateAllWebServers(args)

        if action != "edit_dynamic_quest":
            self.handler.result.result = RequestResult.Success
            self.handler.result.questId = self.questId
        else:
            self.handler.result = RequestResult.Success

    def onGetAuidsListForQuest(self, response, action=''):
        if response:
            info("Response = %r", response)
            try:
                self.questDict["AcceptFilter"]["ForAuids"] = response["r"]["auids"]
                self.questData = json_dumps(self.questDict)
                self.notifyOnDynamicQuestChange(action)
            except:
                catch()
                # Если списка не нашлось, надо бы удалить квест
                self.handler.result.result = RequestResult.BadResult
                self.I.DATA.remove(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                   {"key": self.questId}, params=None, callback=None)
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def RemoveDynamicQuest(self, questId, locale):
        result = getattr(self.handler, "result", None)
        info("RemoveDynamicQuest.onStart, result = %r", result)
        if result is None:
            self.questId = questId
            self.locale = locale
            self.I.DATA.update(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                               {"key": questId}, {"removed": True},
                               params=None, callback=self.onRemoveDynamicQuest)
            raise AsyncThriftException("async RemoveDynamicQuest call")
        else:
            return result

    def onRemoveDynamicQuest(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onRemoveDynamicQuest.response = %r", response)
        if response:
            args = {
                    'action': 'remove_dynamic_quest',
                    'locale': self.locale,
                    'questId': self.questId,
                }
            self.I.WS.updateAllWebServers(args)
            self.handler.result = RequestResult.Success
        else:
            warn("onRemoveDynamicQuest: failed to remove quest %r" % self.questId)
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def EditDynamicQuest(self, questId, locale, jsonQuestData):
        result = getattr(self.handler, "result", None)
        info("EditDynamicQuest.onStart, result = %r", result)
        if result is None:
            self.questId = questId
            self.locale = locale
            self.questData = jsonQuestData
            try:
                self.questDict = json.loads(self.questData)
            except Exception:
                catch()
                warn("EditDynamicQuest: can't parse json string %r" % self.questData)
                return RequestResult.DynamicQuestHasIllegalSynthaxis
            if DynamicQuest.DynamicQuest.validateJsonQuest(self.questDict)[0]:
                self.I.DATA.update(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                   {"key": questId}, {"data": jsonQuestData},
                                   params=None, callback=self.onEditDynamicQuest)
                raise AsyncThriftException("async EditDynamicQuest call")
            else:
                return RequestResult.DynamicQuestHasIllegalSynthaxis
        else:
            return result

    def onEditDynamicQuest(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onEditDynamicQuest.response = %r", response)
        self.I.DATA.increment(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                              {"key": self.questId}, {"version": 1},
                              params=None, callback=None)
        if response:
            if "AuidList" in self.questDict["AcceptFilter"] and int(self.questDict["AcceptFilter"]["AuidList"]) != 0:
                self.I.DATA.find_one(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                     {"auidsKey": int(self.questDict["AcceptFilter"]["AuidList"])},
                                     params=None, callback=functools.partial(self.onGetAuidsListForQuest,
                                                                         action='edit_dynamic_quest'))
                return
            self.notifyOnDynamicQuestChange('edit_dynamic_quest')

        else:
            warn("onEditDynamicQuest: failed to remove quest %r" % self.questId)
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetAccountAdminMessages(self, login):
        result = getattr(self.handler, "findAccountAdminMessages", None)
        info("GetAccountAdminMessages.onStart, result = %r", result)
        if result is None:
            self.I.SQL.getAccountAdminMessages(login, self.onGetAccountMessages)
            raise AsyncThriftException("async GetAccountAdminMessages call")
        else:
            return result

    def onGetAccountMessages(self, sql_reply):
        self.handler.findAccountAdminMessages = AccountManagementAPI.ttypes.AdminMessagesResponse(
            result=RequestResult.BadResponseFromDatabase, adminMessages=[])
        if sql_reply and sql_reply.get("r"):
            messages = sql_reply["r"]
            try:
                for msg in messages:
                    if msg:
                        messageInfo = AccountManagementAPI.ttypes.AdminMessage(
                            messageTitle=utf8convert(msg.title),
                            messageText=utf8convert(msg.message),
                            gmLogin=utf8convert(msg.gmlogin),
                            timestamp=msg.timestamp)
                        self.handler.findAccountAdminMessages.adminMessages.append(messageInfo)
                    else:
                        err("onGetAccountMessages: bad sql reply")
            except Exception:
                catch()
                self.handler.findAccountAdminMessages.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetAuidsLists(self):
        result = getattr(self.handler, "result", None)
        info("GetAuidsLists.onStart")
        if not result:
            self.I.DATA.find(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                             {"auidsKey": {"$exists": True}},
                             params=None, callback=self.onGetAuidsLists)
            raise AsyncThriftException("async GetAuidsLists call")
        else:
            return result

    def onGetAuidsLists(self, response):
        self.handler.result = AccountManagementAPI.ttypes.AuidsListResponse(
            result=RequestResult.BadServiceType, auidsLists=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    auidsList = AccountManagementAPI.ttypes.AuidsList(index=obj["auidsKey"],
                                                                      description=utf8convert(obj["description"]),
                                                                      auids=[])
                    self.handler.result.auidsLists.append(auidsList)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult

        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetAuidsListById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetAuidsListById.onStart")
        if not result:
            self.I.DATA.find_one(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                 {"auidsKey": persistentId},
                                 params=None, callback=self.onGetAuidsListById)
            raise AsyncThriftException("async GetAuidsListById call")
        else:
            return result

    def onGetAuidsListById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.AuidsListByIdResponse(
            result=RequestResult.BadServiceType, auidsLists=None)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                if obj:
                    self.handler.result.auidsLists = AccountManagementAPI.ttypes.AuidsList(index=obj["auidsKey"],
                                                                                      description=utf8convert(obj["description"]),
                                                                                      auids=obj["auids"])
                    self.handler.result.result = RequestResult.Success
                else:
                    warn("onGetAuidsListById: bad response ")
                    self.handler.result.result = RequestResult.BadResult
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult

        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddAuidsList(self, listInfo, gmLogin):
        result = getattr(self.handler, "result", None)
        info("AddAuidsList.onStart, result = %r", result)
        if result is None:
            self.listInfo = listInfo
            self.handler.result = RequestResult.BadResponseFromDatabase
            self.I.DATA.find_and_modify(CC.HELPER_VARIABLES_DATA, CC.HELPER_VARIABLES_DATA,
                                        {"_id": "last_auids_list_id"}, update={"$inc": {"val": 1}}, new=True,
                                        params=None, callback=self.onAuidsListKeyFind)

            raise AsyncThriftException("async AddAuidsList call")
        else:
            return result

    def onAuidsListKeyFind(self, response):
        debug("onAuidsListKeyFind response=%r", response)
        if response and response["r"] is not None:
            try:
                lastAuidsListId = int(response["r"]["val"])
                self.I.DATA.insert(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                   {"auidsKey": lastAuidsListId, "description": self.listInfo.description,
                                    "auids": self.listInfo.auids}, params=None, callback=self.onAddAuidsList)
                return
            except:
                pass
        self.handler.process()

    def onAddAuidsList(self, response):
        debug("onAddAuidsList response=%r", response)
        if response and response["r"] is not None:
            self.handler.result = RequestResult.Success
        self.handler.process()

    def EditAuidsList(self, listInfo, gmLogin):
        result = getattr(self.handler, "result", None)
        debug("listInfo = %r", listInfo)
        info("EditAuidsList.onStart, result = %r", result)
        if result is None:
            self.listInfo = listInfo
            self.handler.result = RequestResult.BadResponseFromDatabase
            self.I.DATA.update(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA, {"auidsKey": self.listInfo.index},
                               {"auidsKey": self.listInfo.index, "description": self.listInfo.description,
                                "auids": self.listInfo.auids}, params=None, callback=self.onEditAuidsList)
            raise AsyncThriftException("async AddAuidsList call")
        else:
            return result

    def onEditAuidsList(self, response):
        debug("onAuidsListKeyFind response=%r", response)
        if response and response["r"] is not None:
            # разослать всем рабочим серверам
            args = {
                'action': 'edit_auids_list',
                'listId': self.listInfo.index,
                'auids': json_dumps(self.listInfo.auids),
            }
            self.I.WS.updateAllWebServers(args)
            self.handler.result = RequestResult.Success
        self.handler.process()

    def RemoveAuidsList(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("RemoveAuidsList.onStart, result = %r", result)
        if result is None:
            self.persistentId = persistentId
            self.handler.result = RequestResult.BadResponseFromDatabase
            self.I.DATA.find(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                             {"key": {"$exists": True}},
                             params=None, callback=self.onGetDynamicQuestsForCheck)
            raise AsyncThriftException("async RemoveAuidsList call")
        else:
            return result

    def onGetDynamicQuestsForCheck(self, response):
        debug("onGetDynamicQuestsForCheck response=%r", response)
        if response and response["r"] is not None:
            for obj in response["r"]:
                if "removed" in obj and obj["removed"]:
                    continue
                questDict = json_loads(obj["data"])
                if "ForAuids" in questDict["AcceptFilter"] and questDict["AcceptFilter"] == self.persistentId:
                    self.handler.result = RequestResult.AuidsListInUsedInQuest
                    self.handler.process()
                    return
                else:
                    self.I.DATA.remove(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                       {"auidsKey": self.persistentId},
                                       params=None, callback=None)
        self.handler.result = RequestResult.Success
        self.handler.process()

    def GetDynamicQuestPullsInfo(self):
        result = getattr(self.handler, "findDynamicQuestPullsResult", None)
        info("GetDynamicQuestPullsInfo.onStart")
        if not result:
            self.I.DATA.find(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                             {"pullKey": {"$exists": True}},
                             params=None, callback=self.onGetDynamicQuestPullsInfo)
            raise AsyncThriftException("async GetDynamicQuestPullsInfo call")
        else:
            return result

    def onGetDynamicQuestPullsInfo(self, response):
        self.handler.findDynamicQuestPullsResult = AccountManagementAPI.ttypes.DynamicQuestPullsInfoResponse(
            result=RequestResult.BadServiceType, questPulls=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    questPullInfo = \
                        AccountManagementAPI.ttypes.DynamicQuestPull(locale=obj['pullData']['locale'],
                                                                     startTime=obj['pullData']['startTime'],
                                                                     endTime=obj['pullData']['endTime'],
                                                                     persistentId=obj['pullKey'],
                                                                     quests=obj['quests'],
                                                                     hasRotation=obj['pullData']['hasRotation'],
                                                                     isActive=obj['pullData']['isActive'])
                    self.handler.findDynamicQuestPullsResult.questPulls.append(questPullInfo)
                self.handler.findDynamicQuestPullsResult.result = RequestResult.Success
            except:
                catch()
                self.handler.findDynamicQuestPullsResult.result = RequestResult.BadResult

        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetDynamicQuestPullById(self, pullId):
        result = getattr(self.handler, "result", None)
        info("GetDynamicQuestPullById.onStart")
        if not result:
            self.I.DATA.find_one(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                             {"pullKey": pullId},
                             params=None, callback=self.onGetDynamicQuestPullById)
            raise AsyncThriftException("async GetDynamicQuestPullById call")
        else:
            return result

    def onGetDynamicQuestPullById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.DynamicQuestPullByIdResponse(
            result=RequestResult.BadServiceType, questPull=None)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                self.handler.result.questPull = AccountManagementAPI.ttypes.DynamicQuestPull(
                                                                     locale=obj['pullData']['locale'],
                                                                     startTime=obj['pullData']['startTime'],
                                                                     endTime=obj['pullData']['endTime'],
                                                                     persistentId=obj['pullKey'],
                                                                     quests=obj['quests'],
                                                                     hasRotation=obj['pullData']['hasRotation'],
                                                                     isActive=obj['pullData']['isActive'])
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult

        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddDynamicQuestPull(self, pullInfo, gmLogin):
        result = getattr(self.handler, "result", None)
        info("AddDynamicQuestPull.onStart, result = %r", result)
        if result is None:
            self.pullInfo = pullInfo
            self.I.DATA.find_one(CC.HELPER_VARIABLES_DATA, CC.HELPER_VARIABLES_DATA,
                                 {"_id": "last_pull_id"},
                                 params=None, callback=self.onPullKeyFind)
            raise AsyncThriftException("async AddDynamicQuestPull call")
        else:
            return result

    def onPullKeyFind(self, response):
        debug("onPullKeyFind response=%r", response)
        if response and response["r"] is not None:
            try:
                self.lastPullId = int(response["r"]["val"]) + 1
                self.I.DATA.increment(CC.HELPER_VARIABLES_DATA, CC.HELPER_VARIABLES_DATA,
                                      {"_id": "last_pull_id"}, {"val": 1},
                                      params=None, callback=self.onUpdateNextQuestPullIndex)

                return
            except:
                pass
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def onUpdateNextQuestPullIndex(self, response):
        debug("onUpdateNextQuestPullIndex response=%r", response)
        if response and response["r"] is not None:
            self.I.DATA.insert(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                               {"pullKey": self.lastPullId, "pullData": {"locale": self.pullInfo.locale,
                                "startTime": self.pullInfo.startTime, "endTime": self.pullInfo.endTime,
                                "hasRotation": self.pullInfo.hasRotation, "isActive": self.pullInfo.isActive},
                                "quests": []},
                               params=None, callback=self.onAddDynamicQuestPull)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def onAddDynamicQuestPull(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onAddDynamicQuestPull.response = %r", response)
        if response:
            # разослать всем рабочим серверам
            args = {
                'action': 'add_new_dynamic_quest_pull',
                'persistentId': self.lastPullId,
                'locale': self.pullInfo.locale,
                'startTime': self.pullInfo.startTime,
                'endTime': self.pullInfo.endTime,
                'hasRotation': self.pullInfo.hasRotation,
                'active': self.pullInfo.isActive,
            }
            self.I.WS.updateAllWebServers(args)
            self.handler.result = RequestResult.Success
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def EditDynamicQuestPull(self, pullInfo, gmLogin):
        result = getattr(self.handler, "result", None)
        info("EditDynamicQuestPull.onStart, result = %r", result)
        if result is None:
            self.pullInfo = pullInfo
            self.I.DATA.update(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                               {"pullKey": pullInfo.persistentId}, {"pullData": {"locale": pullInfo.locale,
                                "startTime": pullInfo.startTime, "endTime": pullInfo.endTime,
                                "persistentId": pullInfo.persistentId, "hasRotation": pullInfo.hasRotation,
                                "isActive": pullInfo.isActive}},
                                params=None, callback=self.onEditDynamicQuestPull)
            raise AsyncThriftException("async EditDynamicQuestPull call")
        else:
            return result

    def onEditDynamicQuestPull(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onEditDynamicQuestPull.response = %r", response)
        if response:
            # разослать всем рабочим серверам
            args = {
                'action': 'edit_dynamic_quest_pull',
                'persistentId': self.pullInfo.persistentId,
                'locale': self.pullInfo.locale,
                'startTime': self.pullInfo.startTime,
                'endTime': self.pullInfo.endTime,
                'hasRotation': self.pullInfo.hasRotation,
                'active': self.pullInfo.isActive,
            }
            self.I.WS.updateAllWebServers(args)
            self.handler.result = RequestResult.Success
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def RemoveDynamicQuestPull(self, pullId, locale, gmLogin):
        result = getattr(self.handler, "result", None)
        info("RemoveDynamicQuestPull.onStart, result = %r", result)
        if result is None:
            self.pullId = pullId
            self.locale = locale
            self.I.DATA.find_one(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                 {"pullKey": pullId},
                                 params=None, callback=self.onGetRemovingPullInfo)
            raise AsyncThriftException("async RemoveDynamicQuestPull call")
        else:
            return result

    def onGetRemovingPullInfo(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        if response and "r" in response:
            self.questIds = response["r"]["quests"]
            self.I.DATA.multi_update(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                     {"key": {"$in": self.questIds}}, {"removed": True},
                                     params=None, callback=self.onMultiRemoveDynamicQuests)
            self.I.DATA.remove(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                               {"pullKey": self.pullId},
                               params=None, callback=self.onRemoveDynamicQuestPull)
            return
        self.handler.process()

    def onMultiRemoveDynamicQuests(self, response):
        if not response:
            err("Dynamic quests %r from pull %r were not removed correctly", self.questIds, self.pullId)

    def onRemoveDynamicQuestPull(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onRemoveDynamicQuestPull.response = %r", response)
        if response:
            # разослать всем рабочим серверам
            args = {
                'action': 'remove_dynamic_quest_pull',
                'persistentId': self.pullId,
                'locale': self.locale,
            }
            self.I.WS.updateAllWebServers(args)
            self.handler.result = RequestResult.Success
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddDynamicQuestsToPull(self, pullId, questIds, locale, gmLogin):
        result = getattr(self.handler, "result", None)
        info("AddDynamicQuestsToPull.onStart, result = %r", result)
        if result is None:
            self.pullId = pullId
            self.questIds = questIds
            self.locale = locale
            self.I.DATA.pushAll(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                {"pullKey": pullId}, {"quests": questIds},
                                params=None, callback=self.onAddDynamicQuestToPull)
            raise AsyncThriftException("async AddDynamicQuestsToPull call")
        else:
            return result

    def onAddDynamicQuestToPull(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onAddDynamicQuestsToPull.response = %r", response)
        if response:
            self.I.DATA.multi_update(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                     {"key": {"$in": self.questIds}}, {"pullId": self.pullId},
                                     params=None, callback=self.onAddedQuestPullIdsUpdated)
        else:
            self.handler.process()

    def onAddedQuestPullIdsUpdated(self, response):
        info("onAddedQuestPullIdsUpdated.response = %r", response)
        if response:
            args = {
                    'action': 'add_quests_to_pull',
                    'locale': self.locale,
                    'pullId': self.pullId,
                    'questId': self.questIds,
                }
            self.I.WS.updateAllWebServers(args)
            self.handler.result = RequestResult.Success
        else:
            warn("onAddDynamicQuestToPull: failed to add quest %r to pull %r", self.questId, self.pullId)
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def RemoveDynamicQuestsFromPull(self, pullId, questIds, locale, gmLogin):
        result = getattr(self.handler, "result", None)
        info("RemoveDynamicQuestFromPull.onStart, result = %r", result)
        if result is None:
            self.pullId = pullId
            self.questIds = questIds
            self.locale = locale
            self.I.DATA.pullAll(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                {"pullKey": pullId}, {"quests": questIds},
                                params=None, callback=self.onRemoveDynamicQuestFromPull)
            raise AsyncThriftException("async RemoveDynamicQuestFromPull call")
        else:
            return result

    def onRemoveDynamicQuestFromPull(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onRemoveDynamicQuestFromPull.response = %r", response)
        if response:
            self.I.DATA.multi_update(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                     {"key": {"$in": self.questIds}}, {"pullId": 0},
                                     params=None, callback=self.onRemovedQuestPullIdsUpdated)
        else:
            self.handler.process()

    def onRemovedQuestPullIdsUpdated(self, response):
        info("onRemovedQuestPullIdsUpdated.response = %r", response)
        if response:
            args = {
                    'action': 'remove_quest_from_pull',
                    'locale': self.locale,
                    'pullId': self.pullId,
                    'questId': self.questIds,
                }
            self.I.WS.updateAllWebServers(args)
            self.handler.result = RequestResult.Success
        else:
            warn("onRemovedQuestPullIdsUpdated: failed to add quest %r to pull %r", self.questId, self.pullId)
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddEvent(self, handlerFunc, args):
        result = getattr(self.handler, "result", None)
        info("AddEvent.onStart, result = %r", result)
        if result is None:
            self.args = args
            self.func = handlerFunc
            self.I.DATA.find_one(CC.HELPER_VARIABLES_DATA, CC.HELPER_VARIABLES_DATA,
                                 {"_id": "last_event_id"},
                                 params=None, callback=self.onEventKeyFind)
            raise AsyncThriftException("async AddEvent call")
        else:
            return result

    # Увеличивает счётчик для коллекции ивентов, вызывает обработчик для конкретного ивента
    def onEventKeyFind(self, response):
        debug("onEventKeyFind response=%r", response)
        if response and response["r"] is not None:
            try:
                self.lastEventId = int(response["r"]["val"]) + 1
                self.I.DATA.increment(CC.HELPER_VARIABLES_DATA, CC.HELPER_VARIABLES_DATA,
                                      {"_id": "last_event_id"}, {"val": 1},
                                      params=None, callback=self.func)

                return
            except:
                pass
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    # задать аргументы в зависимости от типа ивента и разослать их на вс-ки
    def onAddEvent(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onAddEvent.response = %r", response)
        if response:
            # разослать всем рабочим серверам
            self.I.WS.updateAllWebServers(self.args)
            self.handler.result = RequestResult.Success
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetAvailableEvents(self):
        result = getattr(self.handler, "result", None)
        debug("GetAvailableEvents.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": {"$exists": True}},
                             params=None, callback=self.onGetAvailableEvents)
            raise AsyncThriftException("async GetAvailableEvents call")
        else:
            return result

    def onGetAvailableEvents(self, response):
        self.handler.result = AccountManagementAPI.ttypes.CommonEventsListResponse(
            result=RequestResult.BadServiceType, availableEvents=[])
        if response:
            debug("onGetAvailableEvents.Response = %r", response)
            try:
                for obj in response["r"]:
                     event = AccountManagementAPI.ttypes.CommonEventInfo(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     type=obj['type'],
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                     self.handler.result.availableEvents.append(event)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def DeleteEventById(self, persistentId):
        result = getattr(self.handler, "result", None)
        debug("DeleteEventById.onStart, result = %r", result)
        if result is None:
            self.persistentId = persistentId
            self.I.DATA.remove(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onDeleteEventById)
            raise AsyncThriftException("async DeleteEventById call")
        else:
            return result

    def onDeleteEventById(self, response):
        self.handler.result = RequestResult.BadServiceType
        if response:
            debug("onDeleteEventById.Response = %r", response)
            # разослать всем рабочим серверам
            self.I.WS.updateAllWebServers({"action": "delete_event_by_id",
                                           "persistentId": self.persistentId})
            self.handler.result = RequestResult.Success
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def ChangeEventStateById(self, persistentId, state):
        result = getattr(self.handler, "result", None)
        debug("ChangeEventStateById.onStart, result = %r", result)
        if result is None:
            self.persistentId = persistentId
            self.state = state
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": persistentId}, {"enabled": state},
                               params=None, callback=self.onChangeEventStateById)
            raise AsyncThriftException("async ChangeEventStateById call")
        else:
            return result

    def onChangeEventStateById(self, response):
        self.handler.result = RequestResult.BadServiceType
        if response:
            debug("onChangeEventStateById.Response = %r", response)
            # разослать всем рабочим серверам
            self.I.WS.updateAllWebServers({"action": "chane_event_state_by_id",
                                           "persistentId": self.persistentId,
                                           "enable": self.state})
            self.handler.result = RequestResult.Success
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetTransmutationTalentsPerPerl(self):
        result = getattr(self.handler, "findTransmutationTalentEventResult", None)
        info("GetTransmutationTalentsPerPerl.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.TransmutationTalentsPerPerl},
                             params=None, callback=self.onGetTransmutationTalentsPerPerl)
            raise AsyncThriftException("async GetTransmutationTalentsPerPerl call")
        else:
            return result

    def onGetTransmutationTalentsPerPerl(self, response):
        self.handler.findTransmutationTalentEventResult = AccountManagementAPI.ttypes.TransmutationTalentsPerPerlResponse(
            result=RequestResult.BadServiceType, talentsPerPerlEvents=[], talentsDefault=0)
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                     talentsPerPerlEvent = AccountManagementAPI.ttypes.TransmutationTalentsPerPerl(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     talents=obj['customData']['talents'],
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                     self.handler.findTransmutationTalentEventResult.talentsPerPerlEvents.append(talentsPerPerlEvent)
                self.handler.findTransmutationTalentEventResult.talentsDefault = \
                  self.I.Config.getMainConfig().EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL
                self.handler.findTransmutationTalentEventResult.result = RequestResult.Success
            except:
                catch()
                self.handler.findTransmutationTalentEventResult.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetTransmutationTalentsPerPerlById(self, persistentId):
        result = getattr(self.handler, "findTransmutationTalentEventResult", None)
        info("GetTransmutationTalentsPerPerlById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetTransmutationTalentsPerPerlById)
            raise AsyncThriftException("async GetTransmutationTalentsPerPerlById call")
        else:
            return result

    def onGetTransmutationTalentsPerPerlById(self, response):
        self.handler.findTransmutationTalentEventResult = AccountManagementAPI.ttypes.TransmutationTalentsPerPerlByIdResponse(
            result=RequestResult.BadServiceType, talentsPerPerl=0, talentsDefault=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                self.handler.findTransmutationTalentEventResult.talentsPerPerl = \
                    AccountManagementAPI.ttypes.TransmutationTalentsPerPerl(
                                                                 startTime=obj['startTime'],
                                                                 endTime=obj['endTime'],
                                                                 persistentId=obj['_id'],
                                                                 talents=obj['customData']['talents'],
                                                                 enabled=obj['enabled'],
                                                                 description=utf8convert(obj['description']))
                self.handler.findTransmutationTalentEventResult.talentsDefault = \
                  self.I.Config.getMainConfig().EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL
                self.handler.findTransmutationTalentEventResult.result = RequestResult.Success
            except:
                catch()
                self.handler.findTransmutationTalentEventResult.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddTalentPerPerlEvent(self, eventInfo):
        args = {"endTime": eventInfo.endTime, "startTime": eventInfo.startTime,
                "enabled": eventInfo.enabled, "description": eventInfo.description,
                "type": ConfigEventType.TransmutationTalentsPerPerl, "talents": eventInfo.talents,
                "action": "add_talent_per_perl_event"}
        return self.AddEvent(self.onAddTalentPerPerlEvent, args)

    def EditTalentPerPerlEvent(self, eventInfo):
        result = getattr(self.handler, "result", None)
        info("EditTalentPerPerlEvent.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": eventInfo.endTime, "startTime": eventInfo.startTime,
                    "enabled": eventInfo.enabled, "description": eventInfo.description,
                    "type": ConfigEventType.TransmutationTalentsPerPerl, "talents": eventInfo.talents,
                    "action": "add_talent_per_perl_event"}
            self.lastEventId = eventInfo.persistentId
            self.onAddTalentPerPerlEvent({"r": 1})
            raise AsyncThriftException("async EditTalentPerPerlEvent call")
        else:
            return result

    def onAddTalentPerPerlEvent(self, response):
        debug("AddTalentPerPerlEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"talents": self.args["talents"]}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetNewsBanners(self):
        result = getattr(self.handler, "result", None)
        info("GetNewsBanners.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.NewsBanner},
                             params=None, callback=self.onGetNewsBanners)
            raise AsyncThriftException("async GetNewsBanners call")
        else:
            return result

    def onGetNewsBanners(self, response):
        self.handler.result = AccountManagementAPI.ttypes.NewsBannersResponse(
            result=RequestResult.BadServiceType, newsBanners=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                     extensionJson = obj['customData']['extensionJson'].encode("utf8") if 'extensionJson' in obj['customData'] else ""
                     newsBannerEvent = AccountManagementAPI.ttypes.NewsBanner(locale=obj['customData']['locale'],
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     buttonText=obj['customData']['buttonText'].encode("utf8"),
                                                                     windowCaption=obj['customData']['windowCaption'].encode("utf8"),
                                                                     buttonUrl=obj['customData']['buttonUrl'].encode("utf8"),
                                                                     mainUrl=obj['customData']['mainUrl'].encode("utf8"),
                                                                     tooltip=obj['customData']['tooltip'].encode("utf8"),
                                                                     mainUrlB=obj['customData']['mainUrlB'].encode("utf8"),
                                                                     LoginNetworks=obj['customData']['LoginNetworks'].encode("utf8"),
                                                                     minLordLevel=obj['customData']['minLordLevel'],
                                                                     hideIfViewed=obj['customData']['hideIfViewed'],
                                                                     extensionJson=extensionJson,
                                                                     enabled=obj['enabled'],
                                                                     description=obj['description'].encode("utf8"))
                     self.handler.result.newsBanners.append(newsBannerEvent)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetNewsBannerById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetNewsBannerById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetNewsBannerById)
            raise AsyncThriftException("async GetNewsBannerById call")
        else:
            return result

    def onGetNewsBannerById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.NewsBannerByIdResponse(
            result=RequestResult.BadServiceType, newsBanner=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                extensionJson = obj['customData']['extensionJson'].encode("utf8") if 'extensionJson' in obj['customData'] else ""
                self.handler.result.newsBanner = \
                    AccountManagementAPI.ttypes.NewsBanner(locale=obj['customData']['locale'],
                                                           startTime=obj['startTime'],
                                                           endTime=obj['endTime'],
                                                           persistentId=obj['_id'],
                                                           buttonText=obj['customData']['buttonText'].encode("utf8"),
                                                           windowCaption=obj['customData']['windowCaption'].encode("utf8"),
                                                           buttonUrl=obj['customData']['buttonUrl'].encode("utf8"),
                                                           mainUrl=obj['customData']['mainUrl'].encode("utf8"),
                                                           tooltip=obj['customData']['tooltip'].encode("utf8"),
                                                           mainUrlB=obj['customData']['mainUrlB'].encode("utf8"),
                                                           LoginNetworks=obj['customData']['LoginNetworks'].encode("utf8"),
                                                           minLordLevel=obj['customData']['minLordLevel'],
                                                           extensionJson=extensionJson,
                                                           hideIfViewed=obj['customData']['hideIfViewed'],
                                                           enabled=obj['enabled'],
                                                           description=obj['description'].encode("utf8"))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddNewsBanner(self, bannerInfo):
        args = {"endTime": bannerInfo.endTime, "startTime": bannerInfo.startTime, "locale": bannerInfo.locale,
                "enabled": bannerInfo.enabled, "description": bannerInfo.description,
                "type": ConfigEventType.NewsBanner, "buttonText": bannerInfo.buttonText,
                "windowCaption": bannerInfo.windowCaption, "buttonUrl": bannerInfo.buttonUrl,
                "mainUrl": bannerInfo.mainUrl, "tooltip": bannerInfo.tooltip,
                "mainUrlB": bannerInfo.mainUrlB, "LoginNetworks": bannerInfo.LoginNetworks or "",
                "minLordLevel": bannerInfo.minLordLevel, "hideIfViewed": bannerInfo.hideIfViewed, "extensionJson": bannerInfo.extensionJson,
                "action": "add_news_banner_event"}
        return self.AddEvent(self.onAddNewsBanner, args)

    def EditNewsBanner(self, bannerInfo):
        result = getattr(self.handler, "result", None)
        info("EditNewsBanner.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": bannerInfo.endTime, "startTime": bannerInfo.startTime, "locale": bannerInfo.locale,
                         "enabled": bannerInfo.enabled, "description": bannerInfo.description,
                         "type": ConfigEventType.NewsBanner, "buttonText": bannerInfo.buttonText,
                         "windowCaption": bannerInfo.windowCaption, "buttonUrl": bannerInfo.buttonUrl,
                         "mainUrl": bannerInfo.mainUrl, "tooltip": bannerInfo.tooltip,
                         "mainUrlB": bannerInfo.mainUrlB, "LoginNetworks": bannerInfo.LoginNetworks or "",
                         "minLordLevel": bannerInfo.minLordLevel, "hideIfViewed": bannerInfo.hideIfViewed, "extensionJson": bannerInfo.extensionJson,
                         "action": "add_news_banner_event"}
            self.lastEventId = bannerInfo.persistentId
            self.onAddNewsBanner({"r": 1})
            raise AsyncThriftException("async EditNewsBanner call")
        else:
            return result

    def onAddNewsBanner(self, response):
        debug("onAddNewsBanner response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"buttonText": self.args["buttonText"],
                                "windowCaption": self.args["windowCaption"], "buttonUrl": self.args["buttonUrl"],
                                "mainUrl": self.args["mainUrl"], "tooltip": self.args["tooltip"], "locale": self.args["locale"],
                                "mainUrlB": self.args["mainUrlB"], "LoginNetworks": self.args["LoginNetworks"],
                                "minLordLevel": self.args["minLordLevel"], "hideIfViewed": self.args["hideIfViewed"], "extensionJson": self.args["extensionJson"]}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetCustomEvents(self):
        result = getattr(self.handler, "result", None)
        info("GetCustomEvents.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.CustomEvent},
                             params=None, callback=self.onGetCustomEvents)
            raise AsyncThriftException("async GetCustomEvents call")
        else:
            return result

    def onGetCustomEvents(self, response):
        self.handler.result = AccountManagementAPI.ttypes.CustomEventsResponse(
            result=RequestResult.BadServiceType, customEvents=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    customEvent = AccountManagementAPI.ttypes.CustomEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     type=obj['customData']['eventDescription'],
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.customEvents.append(customEvent)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetCustomEventById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetCustomEventById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetCustomEventById)
            raise AsyncThriftException("async GetCustomEventById call")
        else:
            return result

    def onGetCustomEventById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.CustomEventByIdResponse(
            result=RequestResult.BadServiceType, customEvent=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                self.handler.result.customEvent = \
                    AccountManagementAPI.ttypes.CustomEvent(
                                                           startTime=obj['startTime'],
                                                           endTime=obj['endTime'],
                                                           persistentId=obj['_id'],
                                                           type=obj['customData']['eventDescription'],
                                                           enabled=obj['enabled'],
                                                           description=utf8convert(obj['description']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddCustomEvent(self, customEvent):
        args = {"endTime": customEvent.endTime, "startTime": customEvent.startTime,
                "enabled": customEvent.enabled, "description": customEvent.description,
                "type": ConfigEventType.CustomEvent, "eventDescription": customEvent.type,
                "action": "add_custom_event"}
        return self.AddEvent(self.onAddCustomEvent, args)

    def EditCustomEvent(self, customEvent):
        result = getattr(self.handler, "result", None)
        info("EditCustomEvent.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": customEvent.endTime, "startTime": customEvent.startTime,
                         "enabled": customEvent.enabled, "description": customEvent.description,
                         "type": ConfigEventType.CustomEvent, "eventDescription": customEvent.type,
                         "action": "add_custom_event"}
            self.lastEventId = customEvent.persistentId
            self.onAddCustomEvent({"r": 1})
            raise AsyncThriftException("async EditCustomEvent call")
        else:
            return result

    def onAddCustomEvent(self, response):
        debug("onAddCustomEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"eventDescription": self.args["eventDescription"]}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetSkinPrices(self):
        result = getattr(self.handler, "result", None)
        info("GetSkinPrices.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.SkinGoldPrice},
                             params=None, callback=self.onGetSkinPrices)
            raise AsyncThriftException("async GetSkinPrices call")
        else:
            return result

    def onGetSkinPrices(self, response):
        self.handler.result = AccountManagementAPI.ttypes.SkinGoldPricesResponse(
            result=RequestResult.BadServiceType, skinEvents=[], defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventSkins = []
                    for skin in obj['customData']['skins']:
                        customSkinPrice = AccountManagementAPI.ttypes.SkinGoldPrice(persistentId=skin['persistentId'],
                                                                                    heroClassId=skin['heroClassId'],
                                                                                    price=skin['price'])
                        eventSkins.append(customSkinPrice)
                    customEvent = AccountManagementAPI.ttypes.SkinGoldPriceEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     skins=eventSkins,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.skinEvents.append(customEvent)
                for skinId in self.I.SD.getMainSD().data['Skins'].keys():
                    skinSD = self.I.SD.getMainSD().data['Skins'][skinId]
                    self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.SkinGoldPrice(
                                                             persistentId=skinSD['persistentId'],
                                                             heroClassId=crc32(skinSD['heroClassId']),
                                                             price=int(skinSD['cost'])))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetSkinPriceById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetSkinPriceById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetSkinPriceById)
            raise AsyncThriftException("async GetSkinPriceById call")
        else:
            return result

    def onGetSkinPriceById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.SkinGoldPriceByIdResponse(
            result=RequestResult.BadServiceType, skinEvent=0, defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventSkins = []
                for skin in obj['customData']['skins']:
                    customSkinPrice = AccountManagementAPI.ttypes.SkinGoldPrice(persistentId=skin['persistentId'],
                                                                                heroClassId=skin['heroClassId'],
                                                                                price=skin['price'])
                    eventSkins.append(customSkinPrice)
                self.handler.result.skinEvent = AccountManagementAPI.ttypes.SkinGoldPriceEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     skins=eventSkins,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                for skinId in self.I.SD.getMainSD().data['Skins'].keys():
                    skinSD = self.I.SD.getMainSD().data['Skins'][skinId]
                    self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.SkinGoldPrice(
                                                             persistentId=skinSD['persistentId'],
                                                             heroClassId=crc32(skinSD['heroClassId']),
                                                             price=int(skinSD['cost'])))

                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddSkinPricesEvent(self, skinPrice):
        skins = []
        for skin in skinPrice.skins:
            skins.append({"persistentId": skin.persistentId, "heroClassId": skin.heroClassId, "price": skin.price})
        args = {"endTime": skinPrice.endTime, "startTime": skinPrice.startTime,
                "enabled": skinPrice.enabled, "description": skinPrice.description,
                "type": ConfigEventType.SkinGoldPrice, "skins": json_dumps(skins),
                "action": "add_skins_price_event"}
        return self.AddEvent(self.onAddSkinPricesEvent, args)

    def EditSkinPricesEvent(self, skinPrice):
        result = getattr(self.handler, "result", None)
        info("EditSkinPricesEvent.onStart, result = %r", result)
        if result is None:
            skins = []
            for skin in skinPrice.skins:
                skins.append({"persistentId": skin.persistentId, "heroClassId": skin.heroClassId, "price": skin.price})
            self.args = {"endTime": skinPrice.endTime, "startTime": skinPrice.startTime,
                    "enabled": skinPrice.enabled, "description": skinPrice.description,
                    "type": ConfigEventType.SkinGoldPrice, "skins": json_dumps(skins),
                    "action": "add_skins_price_event"}
            self.lastEventId = skinPrice.persistentId
            self.onAddSkinPricesEvent({"r": 1})
            raise AsyncThriftException("async EditSkinPricesEvent call")
        else:
            return result

    def onAddSkinPricesEvent(self, response):
        debug("onAddCustomEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"skins": json_loads(self.args["skins"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetHeroPrices(self):
        result = getattr(self.handler, "result", None)
        info("GetHeroPrices.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.HeroPrice},
                             params=None, callback=self.onGetHeroPrices)
            raise AsyncThriftException("async GetHeroPrices call")
        else:
            return result

    def onGetHeroPrices(self, response):
        self.handler.result = AccountManagementAPI.ttypes.HeroPricesResponse(
            result=RequestResult.BadServiceType, heroEvents=[], defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventHeroes = []
                    for hero in obj['customData']['heroes']:
                        customHeroPrice = AccountManagementAPI.ttypes.HeroPrice(persistentId=hero['persistentId'],
                                                                                silverPrice=hero['silverPrice'],
                                                                                goldPrice=hero['goldPrice'])
                        eventHeroes.append(customHeroPrice)
                    customEvent = AccountManagementAPI.ttypes.HeroPriceEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     heroes=eventHeroes,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.heroEvents.append(customEvent)
                for heroId in self.I.SD.getMainSD().data['Heroes'].keys():
                    heroSD = self.I.SD.getMainSD().data['Heroes'][heroId]
                    silverCost = heroSD['lobbyData']['CostMale']['Silver']
                    goldCost = -1
                    if heroSD['lobbyData']['LevelRequireMale'] >= self.I.Config.getMainConfig().BuyGoldHeroInfo.MIN_LORD_LVL_REQUIRED:
                        goldCost = (silverCost / self.I.Config.getMainConfig().BuyGoldHeroInfo.DISCOUNT_COEFFICIENT) - 1
                    self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.HeroPrice(
                                                             persistentId=heroSD['persistentId'],
                                                             silverPrice=silverCost,
                                                             goldPrice=goldCost))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetHeroPriceById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetHeroPriceById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetHeroPriceById)
            raise AsyncThriftException("async GetHeroPriceById call")
        else:
            return result

    def onGetHeroPriceById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.HeroPriceByIdResponse(
            result=RequestResult.BadServiceType, heroEvent=0, defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventHeroes = []
                for hero in obj['customData']['heroes']:
                    customHeroPrice = AccountManagementAPI.ttypes.HeroPrice(persistentId=hero['persistentId'],
                                                                            silverPrice=hero['silverPrice'],
                                                                            goldPrice=hero['goldPrice'])
                    eventHeroes.append(customHeroPrice)
                self.handler.result.heroEvent = AccountManagementAPI.ttypes.HeroPriceEvent(
                                                                 startTime=obj['startTime'],
                                                                 endTime=obj['endTime'],
                                                                 persistentId=obj['_id'],
                                                                 heroes=eventHeroes,
                                                                 enabled=obj['enabled'],
                                                                 description=utf8convert(obj['description']))
                for heroId in self.I.SD.getMainSD().data['Heroes'].keys():
                    heroSD = self.I.SD.getMainSD().data['Heroes'][heroId]
                    silverCost = heroSD['lobbyData']['CostMale']['Silver']
                    goldCost = -1
                    if heroSD['lobbyData']['LevelRequireMale'] >= self.I.Config.getMainConfig().BuyGoldHeroInfo.MIN_LORD_LVL_REQUIRED:
                        goldCost = (silverCost / self.I.Config.getMainConfig().BuyGoldHeroInfo.DISCOUNT_COEFFICIENT) - 1
                    self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.HeroPrice(
                                                             persistentId=heroSD['persistentId'],
                                                             silverPrice=silverCost,
                                                             goldPrice=goldCost))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddHeroPricesEvent(self, heroPrice):
        heroes = []
        for hero in heroPrice.heroes:
            heroes.append({"persistentId": hero.persistentId,
                           "silverPrice": hero.silverPrice, "goldPrice": hero.goldPrice})
        args = {"endTime": heroPrice.endTime, "startTime": heroPrice.startTime,
                "enabled": heroPrice.enabled, "description": heroPrice.description,
                "type": ConfigEventType.HeroPrice, "heroes": json_dumps(heroes),
                "action": "add_heroes_price_event"}
        return self.AddEvent(self.onAddHeroPricesEvent, args)

    def EditHeroPricesEvent(self, heroPrice):
        result = getattr(self.handler, "result", None)
        info("EditHeroPricesEvent.onStart, result = %r", result)
        if result is None:
            heroes = []
            for hero in heroPrice.heroes:
                heroes.append({"persistentId": hero.persistentId,
                               "silverPrice": hero.silverPrice, "goldPrice": hero.goldPrice})
            self.args = {"endTime": heroPrice.endTime, "startTime": heroPrice.startTime,
                    "enabled": heroPrice.enabled, "description": heroPrice.description,
                    "type": ConfigEventType.HeroPrice, "heroes": json_dumps(heroes),
                    "action": "add_heroes_price_event"}
            self.lastEventId = heroPrice.persistentId
            self.onAddHeroPricesEvent({"r": 1})
            raise AsyncThriftException("async EditHeroPricesEvent call")
        else:
            return result

    def onAddHeroPricesEvent(self, response):
        debug("onAddHeroPricesEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"heroes": json_loads(self.args["heroes"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetCustomMaps(self):
        result = getattr(self.handler, "result", None)
        info("GetCustomMaps.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.EventMap},
                             params=None, callback=self.onGetCustomMaps)
            raise AsyncThriftException("async GetCustomMaps call")
        else:
            return result

    def onGetCustomMaps(self, response):
        self.handler.result = AccountManagementAPI.ttypes.CustomMapsResponse(
            result=RequestResult.BadServiceType, customMaps=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    customMap = AccountManagementAPI.ttypes.CustomMap(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     day=obj['customData']['day'],
                                                                     startHour=obj['customData']['startHour'],
                                                                     endHour=obj['customData']['endHour'],
                                                                     mapDbid=utf8convert(obj['customData']['mapDbid']),
                                                                     mapType=utf8convert(obj['customData']['mapType']),
                                                                     mapEnabled=obj['customData']['mapEnabled'],
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.customMaps.append(customMap)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetCustomMapById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetCustomMapById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetCustomMapById)
            raise AsyncThriftException("async GetCustomMapById call")
        else:
            return result

    def onGetCustomMapById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.CustomMapByIdResponse(
            result=RequestResult.BadServiceType, customMap=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                self.handler.result.customMap = \
                    AccountManagementAPI.ttypes.CustomMap(
                                                          startTime=obj['startTime'],
                                                          endTime=obj['endTime'],
                                                          persistentId=obj['_id'],
                                                          day=obj['customData']['day'],
                                                          startHour=obj['customData']['startHour'],
                                                          endHour=obj['customData']['endHour'],
                                                          mapDbid=utf8convert(obj['customData']['mapDbid']),
                                                          mapType=utf8convert(obj['customData']['mapType']),
                                                          mapEnabled=obj['customData']['mapEnabled'],
                                                          enabled=obj['enabled'],
                                                          description=utf8convert(obj['description']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddCustomMap(self, customMap):
        args = {"endTime": customMap.endTime, "startTime": customMap.startTime,
                "enabled": customMap.enabled, "description": customMap.description,
                "type": ConfigEventType.EventMap, "startHour": customMap.startHour,
                "endHour": customMap.endHour, "mapType": customMap.mapType,
                "mapDbid": customMap.mapDbid, "day": customMap.day,
                "mapEnabled": customMap.mapEnabled, "action": "add_custom_map_event"}
        return self.AddEvent(self.onAddCustomMap, args)

    def EditCustomMap(self, customMap):
        result = getattr(self.handler, "result", None)
        info("EditCustomMap.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": customMap.endTime, "startTime": customMap.startTime,
                         "enabled": customMap.enabled, "description": customMap.description,
                         "type": ConfigEventType.EventMap, "startHour": customMap.startHour,
                         "endHour": customMap.endHour, "mapType": customMap.mapType,
                         "mapDbid": customMap.mapDbid, "day": customMap.day,
                         "mapEnabled": customMap.mapEnabled, "action": "add_custom_map_event"}
            self.lastEventId = customMap.persistentId
            self.onAddCustomMap({"r": 1})
            raise AsyncThriftException("async EditCustomMap call")
        else:
            return result

    def onAddCustomMap(self, response):
        debug("onAddCustomMap response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"day": self.args["day"],
                                "startHour": self.args["startHour"], "endHour": self.args["endHour"],
                                "mapType": self.args["mapType"], "mapDbid": self.args["mapDbid"],
                                "mapEnabled": self.args["mapEnabled"]}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetTalentDropRarities(self):
        result = getattr(self.handler, "result", None)
        info("GetTalentDropRarities.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.TalentDropRarity},
                             params=None, callback=self.onGetTalentDropRarities)
            raise AsyncThriftException("async GetTalentDropRarities call")
        else:
            return result

    def onGetTalentDropRarities(self, response):
        self.handler.result = AccountManagementAPI.ttypes.TalentDropRaritiesResponse(
            result=RequestResult.BadServiceType, talentDropEvents=[], ordinaryDefault=None, premiumDefault=None)
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    talentDrop = AccountManagementAPI.ttypes.TalentDropRarity(classRar=obj['customData']['Class'],
                                                                              ordinary=obj['customData']['ordinary'],
                                                                              good=obj['customData']['good'],
                                                                              excellent=obj['customData']['excellent'],
                                                                              magnificent=obj['customData']['magnificent'],
                                                                              exclusive=obj['customData']['exclusive'])
                    talentDropEvent = AccountManagementAPI.ttypes.TalentDropRarityEvent(startTime=obj['startTime'],
                                                                                        endTime=obj['endTime'],
                                                                                        persistentId=obj['_id'],
                                                                                        dropRarity = talentDrop,
                                                                                        enabled=obj['enabled'],
                                                                                        premium=obj['customData']['premium'],
                                                                                        description=utf8convert(obj['description']))
                    self.handler.result.talentDropEvents.append(talentDropEvent)
                configField = self.I.Config.getMainConfig().EventToolsChangeFields
                self.handler.result.ordinaryDefault = AccountManagementAPI.ttypes.TalentDropRarity(
                    classRar=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.Class],
                    ordinary=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.ordinary],
                    good=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.good],
                    excellent=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.excellent],
                    magnificent=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.magnificent],
                    exclusive=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.exclusive])
                self.handler.result.premiumDefault = AccountManagementAPI.ttypes.TalentDropRarity(
                    classRar=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.Class],
                    ordinary=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.ordinary],
                    good=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.good],
                    excellent=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.excellent],
                    magnificent=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.magnificent],
                    exclusive=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.exclusive])
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetTalentDropRarityById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetTalentDropRarityById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetTalentDropRarityById)
            raise AsyncThriftException("async GetTalentDropRarityById call")
        else:
            return result

    def onGetTalentDropRarityById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.TalentDropRarityByIdResponse(
            result=RequestResult.BadServiceType, talentDropEvent=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                talentDrop = AccountManagementAPI.ttypes.TalentDropRarity(classRar=obj['customData']['Class'],
                                                                          ordinary=obj['customData']['ordinary'],
                                                                          good=obj['customData']['good'],
                                                                          excellent=obj['customData']['excellent'],
                                                                          magnificent=obj['customData']['magnificent'],
                                                                          exclusive=obj['customData']['exclusive'])
                self.handler.result.talentDropEvent = \
                    AccountManagementAPI.ttypes.TalentDropRarityEvent(startTime=obj['startTime'],
                                                                      endTime=obj['endTime'],
                                                                      persistentId=obj['_id'],
                                                                      dropRarity=talentDrop,
                                                                      enabled=obj['enabled'],
                                                                      premium=obj['customData']['premium'],
                                                                      description=utf8convert(obj['description']))
                configField = self.I.Config.getMainConfig().EventToolsChangeFields
                self.handler.result.ordinaryDefault = AccountManagementAPI.ttypes.TalentDropRarity(
                    classRar=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.Class],
                    ordinary=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.ordinary],
                    good=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.good],
                    excellent=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.excellent],
                    magnificent=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.magnificent],
                    exclusive=configField.ORDINARY_TALENTS_DROP_RARITIES[ETalentRarity.exclusive])
                self.handler.result.premiumDefault = AccountManagementAPI.ttypes.TalentDropRarity(
                    classRar=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.Class],
                    ordinary=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.ordinary],
                    good=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.good],
                    excellent=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.excellent],
                    magnificent=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.magnificent],
                    exclusive=configField.PREMIUM_TALENTS_DROP_RARITIES[ETalentRarity.exclusive])
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddTalentDropRarities(self, dropRarities):
        args = {"endTime": dropRarities.endTime, "startTime": dropRarities.startTime, "premium": dropRarities.premium,
                "enabled": dropRarities.enabled, "description": dropRarities.description,
                "type": ConfigEventType.TalentDropRarity, "Class": dropRarities.dropRarity.classRar or 0,
                "ordinary": dropRarities.dropRarity.ordinary or 0, "good": dropRarities.dropRarity.good or 0,
                "excellent": dropRarities.dropRarity.excellent or 0, "magnificent": dropRarities.dropRarity.magnificent or 0,
                "exclusive": dropRarities.dropRarity.exclusive or 0, "action": "add_talent_drop_rar_event"}
        return self.AddEvent(self.onAddTalentDropRarities, args)

    def EditTalentDropRarities(self, dropRarities):
        result = getattr(self.handler, "result", None)
        info("EditTalentDropRarities.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": dropRarities.endTime, "startTime": dropRarities.startTime,
                "enabled": dropRarities.enabled, "description": dropRarities.description, "premium": dropRarities.premium,
                "type": ConfigEventType.TalentDropRarity, "Class": dropRarities.dropRarity.classRar or 0,
                "ordinary": dropRarities.dropRarity.ordinary or 0, "good": dropRarities.dropRarity.good or 0,
                "excellent": dropRarities.dropRarity.excellent or 0, "magnificent": dropRarities.dropRarity.magnificent or 0,
                "exclusive": dropRarities.dropRarity.exclusive or 0, "action": "add_talent_drop_rar_event"}
            self.lastEventId = dropRarities.persistentId
            self.onAddTalentDropRarities({"r": 1})
            raise AsyncThriftException("async EditTalentDropRarities call")
        else:
            return result

    def onAddTalentDropRarities(self, response):
        debug("onAddTalentDropRarities response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"Class": self.args["Class"],
                                "ordinary": self.args["ordinary"], "good": self.args["good"],
                                "excellent": self.args["excellent"], "magnificent": self.args["magnificent"],
                                "exclusive": self.args["exclusive"], "premium": self.args["premium"]}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def AddReforgeTalentPriceEvent(self, val):
        self.rawListReforgeTalentPrices =[dict(rarity=x.rarity, rerollPrice=x.rerollPrice, upgradePrice=x.upgradePrice, talentsToUpgrade=x.talentsToUpgrade  ) for x in val.listReforgeTalentPrices]
        args = {"endTime": val.endTime, "startTime": val.startTime,
                "enabled": val.enabled, "description": val.description, "type": ConfigEventType.ReforgeTalentPrice,
                "listReforgeTalentPrices": json_dumps(self.rawListReforgeTalentPrices),
                "action": "add_reforge_talents_prices_event"}
        return self.AddEvent(self.onAddReforgeTalentsPrices, args)

    def EditReforgeTalentPriceEvent(self, val):
        result = getattr(self.handler, "result", None)
        info("EditReforgeTalentsPrices.onStart, result = %r", result)
        if result is None:
            self.rawListReforgeTalentPrices =[dict(rarity=x.rarity, rerollPrice=x.rerollPrice, upgradePrice=x.upgradePrice, talentsToUpgrade=x.talentsToUpgrade  ) for x in val.listReforgeTalentPrices]
            self.args = {"endTime": val.endTime, "startTime": val.startTime,
                "enabled": val.enabled, "description": val.description, "type": ConfigEventType.ReforgeTalentPrice,
                "listReforgeTalentPrices": json_dumps(self.rawListReforgeTalentPrices),
                "action": "add_reforge_talents_prices_event"}
            self.lastEventId = val.persistentId
            self.onAddReforgeTalentsPrices({"r": 1})
            raise AsyncThriftException("async EditReforgeTalentsPrices call")
        else:
            return result

    def onAddReforgeTalentsPrices(self, response):
        debug("onAddReforgeTalentsPrices response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId },
                { "endTime": self.args["endTime"], "startTime": self.args["startTime"],
                "enabled": self.args["enabled"], "description": self.args["description"],
                "type": self.args["type"], "customData": {"listReforgeTalentPrices": self.rawListReforgeTalentPrices} },
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetReforgeTalentPrice(self):
        result = getattr(self.handler, "result", None)
        info("GetReforgeTalentsPrice.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.ReforgeTalentPrice},
                             params=None, callback=self.onGetReforgeTalentsPrice)
            raise AsyncThriftException("async GetTalentDropRarities call")
        else:
            return result

    def onGetReforgeTalentsPrice(self, response):
        self.handler.result = AccountManagementAPI.ttypes.ReforgeTalentPriceResponse(
            result=RequestResult.BadServiceType, reforgeTalentPricesEvents=[], defaultReforgeTalentPrices=None)
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    lt = []
                    for x in obj["customData"]["listReforgeTalentPrices"]:
                        lt.append(AccountManagementAPI.ttypes.ReforgeTalentPrice(
                            talentsToUpgrade=x['talentsToUpgrade'],
                            rerollPrice=x['rerollPrice'],
                            upgradePrice=x['upgradePrice'],
                            rarity=x['rarity']
                        ))

                    reforgeTalentPricesEvent = AccountManagementAPI.ttypes.ReforgeTalentPrices(
                                                                                        startTime=obj['startTime'],
                                                                                        endTime=obj['endTime'],
                                                                                        persistentId=obj['_id'],
                                                                                        enabled=obj['enabled'],
                                                                                        listReforgeTalentPrices=lt,
                                                                                        description=utf8convert(obj['description']))
                    self.handler.result.reforgeTalentPricesEvents.append(reforgeTalentPricesEvent)
                configField = self.I.Config.getMainConfig().EventToolsChangeFields
                l = []
                for _id, item in configField.ReforgePrices.iteritems():
                    l.append(AccountManagementAPI.ttypes.ReforgeTalentPrice(
                        rarity=item.Rarity,
                        rerollPrice=item.RerollPrice,
                        upgradePrice=item.UpgradePrice,
                        talentsToUpgrade=item.TalentsToUpgrade,
                    ))

                self.handler.result.defaultReforgeTalentPrices = AccountManagementAPI.ttypes.ReforgeTalentPrices(listReforgeTalentPrices=l)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetReforgeTalentPriceById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetReforgeTalentPriceById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onReforgeTalentPriceById)
            raise AsyncThriftException("async GetReforgeTalentPriceById call")
        else:
            return result

    def onReforgeTalentPriceById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.ReforgeTalentPriceByIdResponse(
            result=RequestResult.BadServiceType, defaultReforgeTalentPrices=None, reforgeTalentPrices=None)
        if response:
            info("Response = %r", response)
            try:
                if response["r"]:
                    obj = response['r']
                    lt = []
                    for x in obj["customData"]["listReforgeTalentPrices"]:
                        lt.append(AccountManagementAPI.ttypes.ReforgeTalentPrice(
                            talentsToUpgrade = x['talentsToUpgrade'],
                            rerollPrice = x['rerollPrice'],
                            upgradePrice = x['upgradePrice'],
                            rarity = x['rarity']
                        ))

                    self.handler.result.reforgeTalentPrices = AccountManagementAPI.ttypes.ReforgeTalentPrices(
                                                                                        startTime=obj['startTime'],
                                                                                        endTime=obj['endTime'],
                                                                                        persistentId=obj['_id'],
                                                                                        enabled=obj['enabled'],
                                                                                        listReforgeTalentPrices=lt,
                                                                                        description=utf8convert(obj['description']))
                configField = self.I.Config.getMainConfig().EventToolsChangeFields
                l = []
                for _id, item in configField.ReforgePrices.iteritems():
                    l.append(AccountManagementAPI.ttypes.ReforgeTalentPrice(
                        rarity = item.Rarity,
                        rerollPrice = item.RerollPrice,
                        upgradePrice = item.UpgradePrice,
                        talentsToUpgrade = item.TalentsToUpgrade,
                    ))

                self.handler.result.defaultReforgeTalentPrices = AccountManagementAPI.ttypes.ReforgeTalentPrices(listReforgeTalentPrices=l)
                self.handler.result.result = RequestResult.Success

            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)




    def GetTechsInfos(self):
        result = getattr(self.handler, "result", None)
        info("GetTechsInfos.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.Techs},
                             params=None, callback=self.onGetTechsInfos)
            raise AsyncThriftException("async GetTechsInfos call")
        else:
            return result

    def onGetTechsInfos(self, response):
        self.handler.result = AccountManagementAPI.ttypes.TechsInfosResponse(
            result=RequestResult.BadServiceType, techInfos=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    techs = AccountManagementAPI.ttypes.TechsInfo(endTime=obj['endTime'],
                                                                  startTime=obj['startTime'],
                                                                  persistentId=obj['_id'],
                                                                  type=utf8convert(obj['customData']['techType']),
                                                                  time=obj['customData']['compensation'],
                                                                  description=utf8convert(obj['description']))
                    self.handler.result.techInfos.append(techs)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetTechsInfoById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetTechsInfoById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetTechsInfoById)
            raise AsyncThriftException("async GetTechsInfoById call")
        else:
            return result

    def onGetTechsInfoById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.TechsInfoByIdResponse(
            result=RequestResult.BadServiceType, techInfo=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                self.handler.result.techInfo = AccountManagementAPI.ttypes.TechsInfo(
                                                          endTime=obj['endTime'],
                                                          startTime=obj['startTime'],
                                                          persistentId=obj['_id'],
                                                          type=utf8convert(obj['customData']['techType']),
                                                          time=obj['customData']['compensation'],
                                                          description=utf8convert(obj['description']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddTechs(self, techs):
        args = {"endTime": techs.endTime, "startTime": techs.startTime,
                "enabled": True, "description": techs.description,
                "type": ConfigEventType.Techs, "techType": techs.type,
                "compensation": techs.time, "action": "add_techs"}
        return self.AddEvent(self.onAddAddTechs, args)

    def EditTechs(self, techs):
        result = getattr(self.handler, "result", None)
        info("EditCustomEvent.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": techs.endTime, "startTime": techs.startTime,
                         "enabled": True, "description": techs.description,
                         "type": ConfigEventType.Techs, "techType": techs.type,
                         "compensation": techs.time, "action": "add_techs"}
            self.lastEventId = techs.persistentId
            self.onAddAddTechs({"r": 1})
            raise AsyncThriftException("async EditTechs call")
        else:
            return result

    def onAddAddTechs(self, response):
        debug("onAddAddTechs response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"techType": self.args["techType"],
                                                                          "compensation": self.args["compensation"]}},
                               params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopSlots(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopSlots.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopSlots},
                             params=None, callback=self.onGetRerollShopSlots)
            raise AsyncThriftException("async GetRerollShopSlots call")
        else:
            return result

    def onGetRerollShopSlots(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopSlotsResponse(
            result=RequestResult.BadServiceType, rerollShopSlotsEvents=[], defaultUsualSlots=0, defaultPremiumSlots=0,
            defaultMaxActiveUsualSlots=0, defaultMaxActivePremiumSlots=0)
        if response:
            info("Response = %r", response)
            config = self.I.Config.getMainConfig().EventToolsChangeFields
            try:
                for obj in response["r"]:
                     rerollSlotsEvent = AccountManagementAPI.ttypes.RerollShopSlots(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     usualSlots=obj['customData']['usualSlots'],
                                                                     premiumSlots=obj['customData']['premiumSlots'],
                                                                     maxActiveUsualSlots=obj['customData']['maxActiveUsualSlots'],
                                                                     maxActivePremiumSlots=obj['customData']['maxActivePremiumSlots'],
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                     self.handler.result.rerollShopSlotsEvents.append(rerollSlotsEvent)
                self.handler.result.defaultUsualSlots = config.REROLL_SHOP_ORDINARY_SLOTS
                self.handler.result.defaultPremiumSlots = config.REROLL_SHOP_PREMIUM_SLOTS
                self.handler.result.defaultMaxActiveUsualSlots = config.INACTIVE_REROLL_SHOP_ORDINARY_SLOTS
                self.handler.result.defaultMaxActivePremiumSlots = config.INACTIVE_REROLL_SHOP_PREMIUM_SLOTS
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopSlotsById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopSlotsById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA, {"_id": persistentId},
                                 params=None, callback=self.onGetRerollShopSlotsById)
            raise AsyncThriftException("async GetRerollShopSlotsById call")
        else:
            return result

    def onGetRerollShopSlotsById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopSlotsByIdResponse(
            result=RequestResult.BadServiceType, rerollShopSlots=0, defaultUsualSlots=0, defaultPremiumSlots=0,
            defaultMaxActiveUsualSlots=0, defaultMaxActivePremiumSlots=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                config = self.I.Config.getMainConfig().EventToolsChangeFields
                self.handler.result.rerollShopSlots = AccountManagementAPI.ttypes.RerollShopSlots(
                                                     startTime=obj['startTime'],
                                                     endTime=obj['endTime'],
                                                     persistentId=obj['_id'],
                                                     usualSlots=obj['customData']['usualSlots'],
                                                     premiumSlots=obj['customData']['premiumSlots'],
                                                     maxActiveUsualSlots=obj['customData']['maxActiveUsualSlots'],
                                                     maxActivePremiumSlots=obj['customData']['maxActivePremiumSlots'],
                                                     enabled=obj['enabled'],
                                                     description=utf8convert(obj['description']))
                self.handler.result.defaultUsualSlots = config.REROLL_SHOP_ORDINARY_SLOTS
                self.handler.result.defaultPremiumSlots = config.REROLL_SHOP_PREMIUM_SLOTS
                self.handler.result.defaultMaxActiveUsualSlots = config.INACTIVE_REROLL_SHOP_ORDINARY_SLOTS
                self.handler.result.defaultMaxActivePremiumSlots = config.INACTIVE_REROLL_SHOP_PREMIUM_SLOTS
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopSlotsEvent(self, eventInfo):
        args = {"endTime": eventInfo.endTime, "startTime": eventInfo.startTime,
                "enabled": eventInfo.enabled, "description": eventInfo.description,
                "type": ConfigEventType.RerollShopSlots, "usualSlots": eventInfo.usualSlots,
                "premiumSlots": eventInfo.premiumSlots, "maxActiveUsualSlots": eventInfo.maxActiveUsualSlots,
                "maxActivePremiumSlots": eventInfo.maxActivePremiumSlots,
                "action": "add_reroll_shop_slots_event"}
        return self.AddEvent(self.onAddRerollShopSlotsEvent, args)

    def EditRerollShopSlotsEvent(self, eventInfo):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopSlotsEvent.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": eventInfo.endTime, "startTime": eventInfo.startTime,
                    "enabled": eventInfo.enabled, "description": eventInfo.description,
                    "type": ConfigEventType.RerollShopSlots, "usualSlots": eventInfo.usualSlots,
                    "premiumSlots": eventInfo.premiumSlots, "maxActiveUsualSlots": eventInfo.maxActiveUsualSlots,
                    "maxActivePremiumSlots": eventInfo.maxActivePremiumSlots,
                    "action": "add_reroll_shop_slots_event"}
            self.lastEventId = eventInfo.persistentId
            self.onAddRerollShopSlotsEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopSlotsEvent call")
        else:
            return result

    def onAddRerollShopSlotsEvent(self, response):
        debug("onAddRerollShopSlotsEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"usualSlots": self.args["usualSlots"],
                                "premiumSlots": self.args["premiumSlots"], "maxActiveUsualSlots": self.args["maxActiveUsualSlots"],
                                "maxActivePremiumSlots": self.args["maxActivePremiumSlots"]}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopPrices(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopPrices.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopPrice},
                             params=None, callback=self.onGetRerollShopPrices)
            raise AsyncThriftException("async GetRerollShopPrices call")
        else:
            return result

    def onGetRerollShopPrices(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopPricesResponse(
            result=RequestResult.BadServiceType, rerollShopPriceEvents=[], defaultRerollShopPrice=0)
        if response:
            info("Response = %r", response)
            config = self.I.Config.getMainConfig().EventToolsChangeFields
            try:
                for obj in response["r"]:
                    price = AccountManagementAPI.ttypes.ResourceTableSmall(
                                                                     resource1=obj['customData']['resource1'],
                                                                     resource2=obj['customData']['resource2'],
                                                                     resource3=obj['customData']['resource3'],
                                                                     silver=obj['customData']['silver'],
                                                                     gold=obj['customData']['gold'],
                                                                     perl=obj['customData']['perl'],
                                                                     redPerl=obj['customData']['redPerl'])
                    rerollPriceEvent = AccountManagementAPI.ttypes.RerollShopPrice(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     price=price,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.rerollShopPriceEvents.append(rerollPriceEvent)
                self.handler.result.defaultRerollShopPrice = AccountManagementAPI.ttypes.ResourceTableSmall(
                                                                                          resource1=config.REROLL_SHOP_PRICE.Resource1,
                                                                                          resource2=config.REROLL_SHOP_PRICE.Resource2,
                                                                                          resource3=config.REROLL_SHOP_PRICE.Resource3,
                                                                                          silver=config.REROLL_SHOP_PRICE.Silver,
                                                                                          gold=config.REROLL_SHOP_PRICE.Gold,
                                                                                          perl=config.REROLL_SHOP_PRICE.Perl,
                                                                                          redPerl=config.REROLL_SHOP_PRICE.RedPerl)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopPriceById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopPriceById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA, {"_id": persistentId},
                                 params=None, callback=self.onGetRerollShopPriceById)
            raise AsyncThriftException("async GetRerollShopPriceById call")
        else:
            return result

    def onGetRerollShopPriceById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopPriceByIdResponse(
            result=RequestResult.BadServiceType, rerollShopPrice=0, defaultRerollShopPrice=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                config = self.I.Config.getMainConfig().EventToolsChangeFields
                price = AccountManagementAPI.ttypes.ResourceTableSmall(
                                                                     resource1=obj['customData']['resource1'],
                                                                     resource2=obj['customData']['resource2'],
                                                                     resource3=obj['customData']['resource3'],
                                                                     silver=obj['customData']['silver'],
                                                                     gold=obj['customData']['gold'],
                                                                     perl=obj['customData']['perl'],
                                                                     redPerl=obj['customData']['redPerl'])
                self.handler.result.rerollShopPrice = AccountManagementAPI.ttypes.RerollShopPrice(
                                                     startTime=obj['startTime'],
                                                     endTime=obj['endTime'],
                                                     persistentId=obj['_id'],
                                                     price=price,
                                                     enabled=obj['enabled'],
                                                     description=utf8convert(obj['description']))
                self.handler.result.defaultRerollShopPrice = AccountManagementAPI.ttypes.ResourceTableSmall(
                                                             resource1=config.REROLL_SHOP_PRICE.Resource1,
                                                             resource2=config.REROLL_SHOP_PRICE.Resource2,
                                                             resource3=config.REROLL_SHOP_PRICE.Resource3,
                                                             silver=config.REROLL_SHOP_PRICE.Silver,
                                                             gold=config.REROLL_SHOP_PRICE.Gold,
                                                             perl=config.REROLL_SHOP_PRICE.Perl,
                                                             redPerl=config.REROLL_SHOP_PRICE.RedPerl)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopPriceEvent(self, eventInfo):
        args = {"endTime": eventInfo.endTime, "startTime": eventInfo.startTime,
                "enabled": eventInfo.enabled, "description": eventInfo.description,
                "type": ConfigEventType.RerollShopPrice, "resource1": eventInfo.price.resource1,
                "resource2": eventInfo.price.resource2, "resource3": eventInfo.price.resource3,
                "silver": eventInfo.price.silver, "gold": eventInfo.price.gold,
                "perl": eventInfo.price.perl, "redPerl": eventInfo.price.redPerl,
                "action": "add_reroll_shop_price_event"}
        return self.AddEvent(self.onAddRerollShopPriceEvent, args)

    def EditRerollShopPriceEvent(self, eventInfo):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopPriceEvent.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": eventInfo.endTime, "startTime": eventInfo.startTime,
                    "enabled": eventInfo.enabled, "description": eventInfo.description,
                    "type": ConfigEventType.RerollShopPrice, "resource1": eventInfo.price.resource1,
                    "resource2": eventInfo.price.resource2, "resource3": eventInfo.price.resource3,
                    "silver": eventInfo.price.silver, "gold": eventInfo.price.gold,
                    "perl": eventInfo.price.perl, "redPerl": eventInfo.price.redPerl,
                    "action": "add_reroll_shop_price_event"}
            self.lastEventId = eventInfo.persistentId
            self.onAddRerollShopPriceEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopPriceEvent call")
        else:
            return result

    def onAddRerollShopPriceEvent(self, response):
        debug("onAddRerollShopPriceEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"resource1": self.args["resource1"],
                                "resource2": self.args["resource2"], "resource3": self.args["resource3"],
                                "silver": self.args["silver"], "gold": self.args["gold"],
                                "perl": self.args["perl"], "redPerl": self.args["redPerl"]}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopGroupPrices(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopGroupPrices.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopGroupPrice},
                             params=None, callback=self.onGetRerollShopGroupPrices)
            raise AsyncThriftException("async GetRerollShopGroupPrices call")
        else:
            return result

    def onGetRerollShopGroupPrices(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopGroupPricesResponse(
            result=RequestResult.BadServiceType, groupEvents=[], defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventGroups = []
                    for group in obj['customData']['groups']:
                        customGroupPrice = AccountManagementAPI.ttypes.RerollShopGroupPrice(persistentId=group['persistentId'],
                                                                                minPrice=group['minPrice'],
                                                                                maxPrice=group['maxPrice'])
                        eventGroups.append(customGroupPrice)
                    customEvent = AccountManagementAPI.ttypes.RerollShopGroupPriceEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     groups=eventGroups,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.groupEvents.append(customEvent)
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.RerollShopGroupPrice(
                                                             persistentId=group['persistentId'],
                                                             minPrice=group['minPoints'],
                                                             maxPrice=group['maxPoints']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopGroupPriceById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopGroupPriceById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetRerollShopGroupPriceById)
            raise AsyncThriftException("async GetRerollShopGroupPriceById call")
        else:
            return result

    def onGetRerollShopGroupPriceById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopGroupPriceByIdResponse(
            result=RequestResult.BadServiceType, groupEvent=0, defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventGroups = []
                for group in obj['customData']['groups']:
                    customGroupPrice = AccountManagementAPI.ttypes.RerollShopGroupPrice(persistentId=group['persistentId'],
                                                                            minPrice=group['minPrice'],
                                                                            maxPrice=group['maxPrice'])
                    eventGroups.append(customGroupPrice)
                self.handler.result.groupEvent = AccountManagementAPI.ttypes.RerollShopGroupPriceEvent(
                                                                 startTime=obj['startTime'],
                                                                 endTime=obj['endTime'],
                                                                 persistentId=obj['_id'],
                                                                 groups=eventGroups,
                                                                 enabled=obj['enabled'],
                                                                 description=utf8convert(obj['description']))
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.RerollShopGroupPrice(
                                                             persistentId=group['persistentId'],
                                                             minPrice=group['minPoints'],
                                                             maxPrice=group['maxPoints']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopGroupPricesEvent(self, groupPrice):
        groups = []
        for group in groupPrice.groups:
            groups.append({"persistentId": group.persistentId,
                           "minPrice": group.minPrice, "maxPrice": group.maxPrice})
        args = {"endTime": groupPrice.endTime, "startTime": groupPrice.startTime,
                "enabled": groupPrice.enabled, "description": groupPrice.description,
                "type": ConfigEventType.RerollShopGroupPrice, "groups": json_dumps(groups),
                "action": "add_reroll_shop_groups_price_event"}
        return self.AddEvent(self.onAddRerollShopGroupPricesEvent, args)

    def EditRerollShopGroupPricesEvent(self, groupPrice):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopGroupPricesEvent.onStart, result = %r", result)
        if result is None:
            groups = []
            for group in groupPrice.groups:
                groups.append({"persistentId": group.persistentId,
                               "minPrice": group.minPrice, "maxPrice": group.maxPrice})
            self.args = {"endTime": groupPrice.endTime, "startTime": groupPrice.startTime,
                    "enabled": groupPrice.enabled, "description": groupPrice.description,
                    "type": ConfigEventType.RerollShopGroupPrice, "groups": json_dumps(groups),
                    "action": "add_reroll_shop_groups_price_event"}
            self.lastEventId = groupPrice.persistentId
            self.onAddRerollShopGroupPricesEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopGroupPricesEvent call")
        else:
            return result

    def onAddRerollShopGroupPricesEvent(self, response):
        debug("onAddRerollShopGroupPricesEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"groups": json_loads(self.args["groups"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopGroupProbabilities(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopGroupProbabilities.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopGroupProbability},
                             params=None, callback=self.onGetRerollShopGroupProbabilities)
            raise AsyncThriftException("async GetRerollShopGroupProbabilities call")
        else:
            return result

    def onGetRerollShopGroupProbabilities(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopGroupProbabilitiesResponse(
            result=RequestResult.BadServiceType, groupEvents=[], defaultProbability=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventGroups = []
                    for group in obj['customData']['groups']:
                        customGroupProbability = AccountManagementAPI.ttypes.RerollShopGroupProbability(
                            persistentId=group['persistentId'],
                            rerollTime=group['rerollTime'],
                            probability=group['probability'],
                            minUpgradeLevel=group.get('minUpgradeLevel', 0),
                            maxUpgradeLevel=group.get('maxUpgradeLevel', 0)
                        )
                        eventGroups.append(customGroupProbability)
                    customEvent = AccountManagementAPI.ttypes.RerollShopGroupProbabilityEvent(
                        startTime=obj['startTime'],
                        endTime=obj['endTime'],
                        persistentId=obj['_id'],
                        groups=eventGroups,
                        enabled=obj['enabled'],
                        description=utf8convert(obj['description']))
                    self.handler.result.groupEvents.append(customEvent)
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    self.handler.result.defaultProbability.append(AccountManagementAPI.ttypes.RerollShopGroupProbability(
                        persistentId=group['persistentId'],
                        rerollTime=group['rerollTimesToDropProbabilties']['Item'][0]['rerollTime'],
                        probability=group['rerollTimesToDropProbabilties']['Item'][0]['newProbability'],
                        minUpgradeLevel=group.get('minUpgradeLevel', 0),
                        maxUpgradeLevel=group.get('maxUpgradeLevel', 0)
                    ))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopGroupProbabilityById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopGroupProbabilityById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetRerollShopGroupProbabilityById)
            raise AsyncThriftException("async GetRerollShopGroupProbabilityById call")
        else:
            return result

    def onGetRerollShopGroupProbabilityById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopGroupProbabilityByIdResponse(
            result=RequestResult.BadServiceType, groupEvent=0, defaultProbability=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventGroups = []
                for group in obj['customData']['groups']:
                    customGroupProbability = AccountManagementAPI.ttypes.RerollShopGroupProbability(
                        persistentId=group['persistentId'],
                        rerollTime=group['rerollTime'],
                        probability=group['probability'],
                        minUpgradeLevel=group.get('minUpgradeLevel', 0),
                        maxUpgradeLevel=group.get('maxUpgradeLevel', 0)
                    )
                    eventGroups.append(customGroupProbability)
                self.handler.result.groupEvent = AccountManagementAPI.ttypes.RerollShopGroupProbabilityEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     groups=eventGroups,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    self.handler.result.defaultProbability.append(AccountManagementAPI.ttypes.RerollShopGroupProbability(
                        persistentId=group['persistentId'],
                        rerollTime=group['rerollTimesToDropProbabilties']['Item'][0]['rerollTime'],
                        probability=group['rerollTimesToDropProbabilties']['Item'][0]['newProbability'],
                        minUpgradeLevel=group.get('minUpgradeLevel', 0),
                        maxUpgradeLevel=group.get('maxUpgradeLevel', 0)
                    ))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopGroupProbabilityEvent(self, groupProbability):
        groups = []
        for group in groupProbability.groups:
            groups.append({"persistentId": group.persistentId,
                           "rerollTime": group.rerollTime, "probability": group.probability,
                           "minUpgradeLevel": group.minUpgradeLevel, "maxUpgradeLevel": group.maxUpgradeLevel})
        args = {"endTime": groupProbability.endTime, "startTime": groupProbability.startTime,
                "enabled": groupProbability.enabled, "description": groupProbability.description,
                "type": ConfigEventType.RerollShopGroupProbability, "groups": json_dumps(groups),
                "action": "add_reroll_shop_groups_probability_event"}
        return self.AddEvent(self.onAddRerollShopGroupProbabilityEvent, args)

    def EditRerollShopGroupProbabilityEvent(self, groupProbability):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopGroupProbabilityEvent.onStart, result = %r", result)
        if result is None:
            groups = []
            for group in groupProbability.groups:
                groups.append({"persistentId": group.persistentId,
                               "rerollTime": group.rerollTime, "probability": group.probability,
                           "minUpgradeLevel": group.minUpgradeLevel, "maxUpgradeLevel": group.maxUpgradeLevel})
            self.args = {"endTime": groupProbability.endTime, "startTime": groupProbability.startTime,
                    "enabled": groupProbability.enabled, "description": groupProbability.description,
                    "type": ConfigEventType.RerollShopGroupProbability, "groups": json_dumps(groups),
                    "action": "add_reroll_shop_groups_probability_event"}
            self.lastEventId = groupProbability.persistentId
            self.onAddRerollShopGroupProbabilityEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopGroupProbabilityEvent call")
        else:
            return result

    def onAddRerollShopGroupProbabilityEvent(self, response):
        debug("onAddRerollShopGroupProbabilityEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"groups": json_loads(self.args["groups"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopGroupCurrencies(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopGroupCurrencies.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopGroupCurrencies},
                             params=None, callback=self.onGetRerollShopGroupCurrencies)
            raise AsyncThriftException("async GetRerollShopGroupCurrencies call")
        else:
            return result

    def onGetRerollShopGroupCurrencies(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopGroupCurrenciesResponse(
            result=RequestResult.BadServiceType, groupEvents=[], defaultCurrencies=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventGroups = []
                    for group in obj['customData']['groups']:
                        customGroupCurrencies = AccountManagementAPI.ttypes.RerollShopGroupCurrencies(
                                                                                persistentId=group['persistentId'],
                                                                                currencies=group['currencies'])
                        eventGroups.append(customGroupCurrencies)
                    customEvent = AccountManagementAPI.ttypes.RerollShopGroupCurrenciesEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     groups=eventGroups,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.groupEvents.append(customEvent)
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    self.handler.result.defaultCurrencies.append(AccountManagementAPI.ttypes.RerollShopGroupCurrencies(
                                      persistentId=group['persistentId'],
                                      currencies=group['currencies']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopGroupCurrenciesById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopGroupCurrenciesById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetRerollShopGroupCurrenciesById)
            raise AsyncThriftException("async GetRerollShopGroupCurrenciesById call")
        else:
            return result

    def onGetRerollShopGroupCurrenciesById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopGroupCurrenciesByIdResponse(
            result=RequestResult.BadServiceType, groupEvent=0, defaultCurrencies=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventGroups = []
                for group in obj['customData']['groups']:
                    customGroupCurrencies = AccountManagementAPI.ttypes.RerollShopGroupCurrencies(
                                                                                persistentId=group['persistentId'],
                                                                                currencies=group['currencies'])
                    eventGroups.append(customGroupCurrencies)
                self.handler.result.groupEvent = AccountManagementAPI.ttypes.RerollShopGroupCurrenciesEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     groups=eventGroups,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    self.handler.result.defaultCurrencies.append(AccountManagementAPI.ttypes.RerollShopGroupCurrencies(
                                      persistentId=group['persistentId'],
                                      currencies=group['currencies']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopGroupCurrenciesEvent(self, groupCurrencies):
        groups = []
        for group in groupCurrencies.groups:
            groups.append({"persistentId": group.persistentId, "currencies": group.currencies})
        args = {"endTime": groupCurrencies.endTime, "startTime": groupCurrencies.startTime,
                "enabled": groupCurrencies.enabled, "description": groupCurrencies.description,
                "type": ConfigEventType.RerollShopGroupCurrencies, "groups": json_dumps(groups),
                "action": "add_reroll_shop_groups_currencies_event"}
        return self.AddEvent(self.onAddRerollShopGroupCurrenciesEvent, args)

    def EditRerollShopGroupCurrenciesEvent(self, groupCurrencies):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopGroupCurrenciesEvent.onStart, result = %r", result)
        if result is None:
            groups = []
            for group in groupCurrencies.groups:
                groups.append({"persistentId": group.persistentId, "currencies": group.currencies})
            self.args = {"endTime": groupCurrencies.endTime, "startTime": groupCurrencies.startTime,
                    "enabled": groupCurrencies.enabled, "description": groupCurrencies.description,
                    "type": ConfigEventType.RerollShopGroupCurrencies, "groups": json_dumps(groups),
                    "action": "add_reroll_shop_groups_currencies_event"}
            self.lastEventId = groupCurrencies.persistentId
            self.onAddRerollShopGroupProbabilityEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopGroupCurrenciesEvent call")
        else:
            return result

    def onAddRerollShopGroupCurrenciesEvent(self, response):
        debug("onAddRerollShopGroupCurrenciesEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"groups": json_loads(self.args["groups"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopSlotPrices(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopSlotPrices.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopSlotPrice},
                             params=None, callback=self.onGetRerollShopSlotPrices)
            raise AsyncThriftException("async GetRerollShopSlotPrices call")
        else:
            return result

    def onGetRerollShopSlotPrices(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopSlotPricesResponse(
            result=RequestResult.BadServiceType, slotEvents=[], defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventSlots = []
                    for slot in obj['customData']['slots']:
                        customSlotPrice = AccountManagementAPI.ttypes.RerollShopSlotPrice(persistentId=slot['persistentId'],
                                                                                groupId=slot['groupId'],
                                                                                minPrice=slot['minPrice'],
                                                                                maxPrice=slot['maxPrice'])
                        eventSlots.append(customSlotPrice)
                    customEvent = AccountManagementAPI.ttypes.RerollShopSlotPriceEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     slots=eventSlots,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.slotEvents.append(customEvent)
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    for slot in group['slots']['Item']:
                        self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.RerollShopSlotPrice(
                                                             persistentId=slot['slot']['persistentId'],
                                                             groupId=group['persistentId'],
                                                             minPrice=slot['minPoints'],
                                                             maxPrice=slot['maxPoints']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopSlotPriceById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopSlotPriceById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetRerollShopSlotPriceById)
            raise AsyncThriftException("async GetRerollShopSlotPriceById call")
        else:
            return result

    def onGetRerollShopSlotPriceById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopSlotPriceByIdResponse(
            result=RequestResult.BadServiceType, slotEvent=0, defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventSlots = []
                for slot in obj['customData']['slots']:
                    customSlotPrice = AccountManagementAPI.ttypes.RerollShopSlotPrice(persistentId=slot['persistentId'],
                                                                            groupId=slot['groupId'],
                                                                            minPrice=slot['minPrice'],
                                                                            maxPrice=slot['maxPrice'])
                    eventSlots.append(customSlotPrice)
                self.handler.result.slotEvent = AccountManagementAPI.ttypes.RerollShopSlotPriceEvent(
                                                                 startTime=obj['startTime'],
                                                                 endTime=obj['endTime'],
                                                                 persistentId=obj['_id'],
                                                                 slots=eventSlots,
                                                                 enabled=obj['enabled'],
                                                                 description=utf8convert(obj['description']))
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    for slot in group['slots']['Item']:
                        self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.RerollShopSlotPrice(
                                                             persistentId=slot['slot']['persistentId'],
                                                             groupId=group['persistentId'],
                                                             minPrice=slot['minPoints'],
                                                             maxPrice=slot['maxPoints']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopSlotPricesEvent(self, slotPrice):
        slots = []
        for slot in slotPrice.slots:
            slots.append({"persistentId": slot.persistentId, "groupId": slot.groupId,
                           "minPrice": slot.minPrice, "maxPrice": slot.maxPrice})
        args = {"endTime": slotPrice.endTime, "startTime": slotPrice.startTime,
                "enabled": slotPrice.enabled, "description": slotPrice.description,
                "type": ConfigEventType.RerollShopSlotPrice, "slots": json_dumps(slots),
                "action": "add_reroll_shop_slots_price_event"}
        return self.AddEvent(self.onAddRerollShopSlotPricesEvent, args)

    def EditRerollShopSlotPricesEvent(self, slotPrice):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopGroupPricesEvent.onStart, result = %r", result)
        if result is None:
            slots = []
            for slot in slotPrice.slots:
                slots.append({"persistentId": slot.persistentId, "groupId": slot.groupId,
                               "minPrice": slot.minPrice, "maxPrice": slot.maxPrice})
            self.args = {"endTime": slotPrice.endTime, "startTime": slotPrice.startTime,
                    "enabled": slotPrice.enabled, "description": slotPrice.description,
                    "type": ConfigEventType.RerollShopSlotPrice, "slots": json_dumps(slots),
                    "action": "add_reroll_shop_slots_price_event"}
            self.lastEventId = slotPrice.persistentId
            self.onAddRerollShopSlotPricesEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopSlotPricesEvent call")
        else:
            return result

    def onAddRerollShopSlotPricesEvent(self, response):
        debug("onAddRerollShopSlotPricesEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"slots": json_loads(self.args["slots"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopSlotAmount(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopSlotAmount.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopSlotAmount},
                             params=None, callback=self.onGetRerollShopSlotAmounts)
            raise AsyncThriftException("async GetRerollShopSlotAmounts call")
        else:
            return result

    def onGetRerollShopSlotAmounts(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopSlotAmountsResponse(
            result=RequestResult.BadServiceType, slotEvents=[], defaultAmounts=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventSlots = []
                    for slot in obj['customData']['slots']:
                        customSlotAmount = AccountManagementAPI.ttypes.RerollShopSlotAmount(persistentId=slot['persistentId'],
                                                                                groupId=slot['groupId'],
                                                                                amount=slot['amount'])
                        eventSlots.append(customSlotAmount)
                    customEvent = AccountManagementAPI.ttypes.RerollShopSlotAmountEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     slots=eventSlots,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.slotEvents.append(customEvent)
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    for slot in group['slots']['Item']:
                        if slot['slot']['classType'] == "ResourceRerollSlot":
                            self.handler.result.defaultAmounts.append(AccountManagementAPI.ttypes.RerollShopSlotAmount(
                                                             persistentId=slot['slot']['persistentId'],
                                                             groupId=group['persistentId'],
                                                             amount=int(slot['slot']['amount'])))
                        if slot['slot']['classType'] == "PremiumRerollSlot":
                            self.handler.result.defaultAmounts.append(AccountManagementAPI.ttypes.RerollShopSlotAmount(
                                                             persistentId=slot['slot']['persistentId'],
                                                             groupId=group['persistentId'],
                                                             amount=int(slot['slot']['days'])))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopSlotAmountById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopSlotAmountById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetRerollShopSlotAmountById)
            raise AsyncThriftException("async GetRerollShopSlotAmountById call")
        else:
            return result

    def onGetRerollShopSlotAmountById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopSlotAmountByIdResponse(
            result=RequestResult.BadServiceType, slotEvent=0, defaultAmounts=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventSlots = []
                for slot in obj['customData']['slots']:
                    customSlotAmount = AccountManagementAPI.ttypes.RerollShopSlotAmount(persistentId=slot['persistentId'],
                                                                            groupId=slot['groupId'],
                                                                            amount=slot['amount'])
                    eventSlots.append(customSlotAmount)
                self.handler.result.slotEvent = AccountManagementAPI.ttypes.RerollShopSlotAmountEvent(
                                                                 startTime=obj['startTime'],
                                                                 endTime=obj['endTime'],
                                                                 persistentId=obj['_id'],
                                                                 slots=eventSlots,
                                                                 enabled=obj['enabled'],
                                                                 description=utf8convert(obj['description']))
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    for slot in group['slots']['Item']:
                        if slot['slot']['classType'] == "ResourceRerollSlot":
                            self.handler.result.defaultAmounts.append(AccountManagementAPI.ttypes.RerollShopSlotAmount(
                                                             persistentId=slot['slot']['persistentId'],
                                                             groupId=group['persistentId'],
                                                             amount=int(slot['slot']['amount'])))
                        if slot['slot']['classType'] == "PremiumRerollSlot":
                            self.handler.result.defaultAmounts.append(AccountManagementAPI.ttypes.RerollShopSlotAmount(
                                                             persistentId=slot['slot']['persistentId'],
                                                             groupId=group['persistentId'],
                                                             amount=int(slot['slot']['days'])))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopSlotAmountsEvent(self, slotAmount):
        slots = []
        for slot in slotAmount.slots:
            slots.append({"persistentId": slot.persistentId, "groupId": slot.groupId,
                           "amount": slot.amount})
        args = {"endTime": slotAmount.endTime, "startTime": slotAmount.startTime,
                "enabled": slotAmount.enabled, "description": slotAmount.description,
                "type": ConfigEventType.RerollShopSlotAmount, "slots": json_dumps(slots),
                "action": "add_reroll_shop_slots_amount_event"}
        return self.AddEvent(self.onAddRerollShopSlotAmountsEvent, args)

    def EditRerollShopSlotAmountsEvent(self, slotAmount):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopGroupAmountsEvent.onStart, result = %r", result)
        if result is None:
            slots = []
            for slot in slotAmount.slots:
                slots.append({"persistentId": slot.persistentId, "groupId": slot.groupId,
                               "amount": slot.amount})
            self.args = {"endTime": slotAmount.endTime, "startTime": slotAmount.startTime,
                    "enabled": slotAmount.enabled, "description": slotAmount.description,
                    "type": ConfigEventType.RerollShopSlotAmount, "slots": json_dumps(slots),
                    "action": "add_reroll_shop_slots_amount_event"}
            self.lastEventId = slotAmount.persistentId
            self.onAddRerollShopSlotAmountsEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopSlotAmountsEvent call")
        else:
            return result

    def onAddRerollShopSlotAmountsEvent(self, response):
        debug("onAddRerollShopSlotAmountsEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"slots": json_loads(self.args["slots"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopSlotProbabilities(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopSlotProbabilities.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopSlotProbability},
                             params=None, callback=self.onGetRerollShopSlotProbabilities)
            raise AsyncThriftException("async GetRerollShopSlotProbabilities call")
        else:
            return result

    def GetFirstBuyPrices(self):
        result = getattr(self.handler, "result", None)
        info("GetFirstBuyPrices.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.FirstBuyPrice},
                             params=None, callback=self.onGetFirstBuyPrices)
            raise AsyncThriftException("async GetFirstBuyPrices call")
        else:
            return result

    def onGetFirstBuyPrices(self, response):
        self.handler.result = AccountManagementAPI.ttypes.FirstBuyGoldPricesResponse(
            result=RequestResult.BadServiceType, firstBuyEvents=[], defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventPrices = []
                    for firstBuy in obj['customData']['firstBuys']:
                        customFirstBuyPrice = AccountManagementAPI.ttypes.FirstBuyGoldPrice(persistentId=firstBuy['persistentId'],
                                                                                            price=firstBuy['price'])
                        eventPrices.append(customFirstBuyPrice)
                    customEvent = AccountManagementAPI.ttypes.FirstBuyGoldPriceEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     firstBuys=eventPrices,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.firstBuyEvents.append(customEvent)
                for constructionId in self.I.SD.getMainSD().data['Constructions'].keys():
                    staticConstruction = self.I.SD.getMainSD().data['Constructions'][constructionId]
                    if staticConstruction['classType'] == "FirstBuyBuilding":
                        self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.FirstBuyGoldPrice(
                                                                 persistentId=staticConstruction['persistentId'],
                                                                 price=int(staticConstruction['Levels']['Item'][0]['price']['Gold'])))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetFirstBuyPriceById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetFirstBuyPriceById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetFirstBuyPriceById)
            raise AsyncThriftException("async GetFirstBuyPriceById call")
        else:
            return result

    def onGetFirstBuyPriceById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.FirstBuyGoldPriceByIdResponse(
            result=RequestResult.BadServiceType, firstBuyEvent=0, defaultPrices=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventFirstBuys = []
                for firstBuy in obj['customData']['firstBuys']:
                    customSkinPrice = AccountManagementAPI.ttypes.FirstBuyGoldPrice(persistentId=firstBuy['persistentId'],
                                                                                    price=firstBuy['price'])
                    eventFirstBuys.append(customSkinPrice)
                self.handler.result.firstBuyEvent = AccountManagementAPI.ttypes.FirstBuyGoldPriceEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     firstBuys=eventFirstBuys,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                for constructionId in self.I.SD.getMainSD().data['Constructions'].keys():
                    staticConstruction = self.I.SD.getMainSD().data['Constructions'][constructionId]
                    if staticConstruction['classType'] == "FirstBuyBuilding":
                        self.handler.result.defaultPrices.append(AccountManagementAPI.ttypes.FirstBuyGoldPrice(
                                                                 persistentId=staticConstruction['persistentId'],
                                                                 price=int(staticConstruction['Levels']['Item'][0]['price']['Gold'])))

                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddFirstBuyPricesEvent(self, firstBuyPrice):
        firstBuys = []
        for firstBuy in firstBuyPrice.firstBuys:
            firstBuys.append({"persistentId": firstBuy.persistentId, "price": firstBuy.price})
        args = {"endTime": firstBuyPrice.endTime, "startTime": firstBuyPrice.startTime,
                "enabled": firstBuyPrice.enabled, "description": firstBuyPrice.description,
                "type": ConfigEventType.FirstBuyPrice, "firstBuys": json_dumps(firstBuys),
                "action": "add_first_buy_price_event"}
        return self.AddEvent(self.onAddFirstBuyPricesEvent, args)

    def EditFirstBuyPricesEvent(self, firstBuyPrice):
        result = getattr(self.handler, "result", None)
        info("EditFirstBuyPricesEvent.onStart, result = %r", result)
        if result is None:
            firstBuys = []
            for firstBuy in firstBuyPrice.firstBuys:
                firstBuys.append({"persistentId": firstBuy.persistentId, "price": firstBuy.price})
            self.args = {"endTime": firstBuyPrice.endTime, "startTime": firstBuyPrice.startTime,
                    "enabled": firstBuyPrice.enabled, "description": firstBuyPrice.description,
                    "type": ConfigEventType.FirstBuyPrice, "firstBuys": json_dumps(firstBuys),
                    "action": "add_first_buy_price_event"}
            self.lastEventId = firstBuyPrice.persistentId
            self.onAddFirstBuyPricesEvent({"r": 1})
            raise AsyncThriftException("async EditFirstBuyPricesEvent call")
        else:
            return result

    def onAddFirstBuyPricesEvent(self, response):
        debug("onAddFirstBuyPricesEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"firstBuys": json_loads(self.args["firstBuys"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopPremiumNotInactive(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopPremiumNotInactive.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.PremiumNotInactive},
                             params=None, callback=self.onGetRerollShopPremiumNotInactive)
            raise AsyncThriftException("async GetRerollShopPremiumNotInactive call")
        else:
            return result

    def onGetRerollShopPremiumNotInactive(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopPremiumNotInactiveResponse(
            result=RequestResult.BadServiceType, rerollShopPremiumNotInactiveEvents=[], rerollShopPremiumNotInactiveDefault=0)
        if response:
            info("Response = %r", response)
            config = self.I.Config.getMainConfig().EventToolsChangeFields
            try:
                for obj in response["r"]:
                    rerollPriceEvent = AccountManagementAPI.ttypes.RerollShopPremiumNotInactiveEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     isInactive=obj["customData"],
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.rerollShopPremiumNotInactiveEvents.append(rerollPriceEvent)
                self.handler.result.rerollShopPremiumNotInactiveDefault = config.PREMIUM_SLOTS_ARE_NOT_INACTIVE
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopPremiumNotInactiveById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopPremiumNotInactiveById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA, {"_id": persistentId},
                                 params=None, callback=self.onGetRerollShopPremiumNotInactiveById)
            raise AsyncThriftException("async GetRerollShopPremiumNotInactiveById call")
        else:
            return result

    def onGetRerollShopPremiumNotInactiveById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopPremiumNotInactiveByIdResponse(
            result=RequestResult.BadServiceType, rerollShopPremiumNotInactive=0, rerollShopPremiumNotInactiveDefault=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                config = self.I.Config.getMainConfig().EventToolsChangeFields
                self.handler.result.rerollShopPremiumNotInactive = AccountManagementAPI.ttypes.RerollShopPremiumNotInactiveEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     isInactive=obj["customData"],
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                self.handler.result.rerollShopPremiumNotInactiveDefault = config.PREMIUM_SLOTS_ARE_NOT_INACTIVE
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopPremiumNotInactiveEvent(self, eventInfo):
        args = {"endTime": eventInfo.endTime, "startTime": eventInfo.startTime,
                "enabled": eventInfo.enabled, "description": eventInfo.description,
                "type": ConfigEventType.PremiumNotInactive, "isInactive": eventInfo.isInactive,
                "action": "add_premium_not_inactive_event"}
        return self.AddEvent(self.onAddRerollShopPremiumNotInactiveEvent, args)

    def EditRerollShopPremiumNotInactiveEvent(self, eventInfo):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopPremiumNotInactiveEvent.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": eventInfo.endTime, "startTime": eventInfo.startTime,
                    "enabled": eventInfo.enabled, "description": eventInfo.description,
                    "type": ConfigEventType.PremiumNotInactive, "isInactive": eventInfo.isInactive,
                    "action": "add_premium_not_inactive_event"}
            self.lastEventId = eventInfo.persistentId
            self.onAddRerollShopPremiumNotInactiveEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopPremiumNotInactiveEvent call")
        else:
            return result

    def onAddRerollShopPremiumNotInactiveEvent(self, response):
        debug("onAddRerollShopPremiumNotInactiveEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": self.args["isInactive"]},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopGroupSlots(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopGroupSlots.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopGroupSlots},
                             params=None, callback=self.onGetRerollShopGroupSlots)
            raise AsyncThriftException("async GetRerollShopGroupSlots call")
        else:
            return result

    def onGetRerollShopGroupSlots(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopGroupSlotsResponse(
            result=RequestResult.BadServiceType, slotEvents=[], defaultSlots=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                    eventGroups = []
                    for group in obj['customData']['groups']:
                        customGroupSlots = AccountManagementAPI.ttypes.RerollShopGroupSlots(persistentIds=group['persistentIds'],
                                                                                groupId=group['groupId'])
                        eventGroups.append(customGroupSlots)
                    customEvent = AccountManagementAPI.ttypes.RerollShopGroupSlotsEvent(
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     groups=eventGroups,
                                                                     enabled=obj['enabled'],
                                                                     description=utf8convert(obj['description']))
                    self.handler.result.slotEvents.append(customEvent)
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    defaultSlots = []
                    for slot in group['slots']['Item']:
                        defaultSlots.append(slot['slot']['persistentId'])
                    self.handler.result.defaultSlots.append(AccountManagementAPI.ttypes.RerollShopGroupSlots(
                                                             persistentIds=defaultSlots,
                                                             groupId=group['persistentId']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopGroupSlotsById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopGroupSlotsById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetRerollShopGroupSlotsById)
            raise AsyncThriftException("async GetRerollShopGroupSlotsById call")
        else:
            return result

    def onGetRerollShopGroupSlotsById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopGroupSlotsByIdResponse(
            result=RequestResult.BadServiceType, slotEvent=0, defaultSlots=[])
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                eventGroups = []
                for group in obj['customData']['groups']:
                    customGroupSlots = AccountManagementAPI.ttypes.RerollShopGroupSlots(persistentIds=group['persistentIds'],
                                                                                groupId=group['groupId'])
                    eventGroups.append(customGroupSlots)
                self.handler.result.slotEvent = AccountManagementAPI.ttypes.RerollShopGroupSlotsEvent(
                                                                 startTime=obj['startTime'],
                                                                 endTime=obj['endTime'],
                                                                 persistentId=obj['_id'],
                                                                 groups=eventGroups,
                                                                 enabled=obj['enabled'],
                                                                 description=utf8convert(obj['description']))
                for group in self.I.SD.getMainSD().data['RerollShop']['groups']['Item']:
                    defaultSlots = []
                    for slot in group['slots']['Item']:
                        defaultSlots.append(slot['slot']['persistentId'])
                    self.handler.result.defaultSlots.append(AccountManagementAPI.ttypes.RerollShopGroupSlots(
                                                             persistentIds=defaultSlots,
                                                             groupId=group['persistentId']))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopGroupSlotsEvent(self, groupSlots):
        groups = []
        for group in groupSlots.groups:
            groups.append({"persistentIds": group.persistentIds, "groupId": group.groupId})
        args = {"endTime": groupSlots.endTime, "startTime": groupSlots.startTime,
                "enabled": groupSlots.enabled, "description": groupSlots.description,
                "type": ConfigEventType.RerollShopGroupSlots, "groups": json_dumps(groups),
                "action": "add_reroll_shop_groups_slots_event"}
        return self.AddEvent(self.onAddRerollShopGroupSlotsEvent, args)

    def EditRerollShopGroupSlotsEvent(self, groupSlots):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopGroupSlotsEvent.onStart, result = %r", result)
        if result is None:
            groups = []
            for group in groupSlots.groups:
                groups.append({"persistentIds": group.persistentIds, "groupId": group.groupId})
            self.args = {"endTime": groupSlots.endTime, "startTime": groupSlots.startTime,
                    "enabled": groupSlots.enabled, "description": groupSlots.description,
                    "type": ConfigEventType.RerollShopGroupSlots, "groups": json_dumps(groups),
                    "action": "add_reroll_shop_groups_slots_event"}
            self.lastEventId = groupSlots.persistentId
            self.onAddRerollShopGroupSlotsEvent({"r": 1})
            raise AsyncThriftException("async EditRerollShopGroupSlotsEvent call")
        else:
            return result

    def onAddRerollShopGroupSlotsEvent(self, response):
        debug("onAddRerollShopGroupSlotsEvent response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"groups": json_loads(self.args["groups"])}},
                                params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopBanners(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopBanners.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopBanner},
                             params=None, callback=self.onGetRerollShopBanners)
            raise AsyncThriftException("async GetRerollShopBanners call")
        else:
            return result

    def onGetRerollShopBanners(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopBannersResponse(
            result=RequestResult.BadServiceType, rerollShopBanners=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                     rerollShopBannerEvent = AccountManagementAPI.ttypes.RerollShopBanner(locale=obj['customData']['locale'],
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     mainUrl=obj['customData']['mainUrl'].encode("utf8"),
                                                                     enabled=obj['enabled'],
                                                                     description=obj['description'].encode("utf8"))
                     self.handler.result.rerollShopBanners.append(rerollShopBannerEvent)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopBannerById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopBannerById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetRerollShopBannerById)
            raise AsyncThriftException("async GetRerollShopBannerById call")
        else:
            return result

    def onGetRerollShopBannerById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopBannerByIdResponse(
            result=RequestResult.BadServiceType, rerollShopBanner=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                self.handler.result.rerollShopBanner = \
                    AccountManagementAPI.ttypes.RerollShopBanner(locale=obj['customData']['locale'],
                                                           startTime=obj['startTime'],
                                                           endTime=obj['endTime'],
                                                           persistentId=obj['_id'],
                                                           mainUrl=obj['customData']['mainUrl'].encode("utf8"),
                                                           enabled=obj['enabled'],
                                                           description=obj['description'].encode("utf8"))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopBanner(self, bannerInfo):
        args = {"endTime": bannerInfo.endTime, "startTime": bannerInfo.startTime, "locale": bannerInfo.locale,
                "enabled": bannerInfo.enabled, "description": bannerInfo.description,
                "type": ConfigEventType.RerollShopBanner, "mainUrl": bannerInfo.mainUrl,
                "action": "add_reroll_shop_banner_event"}
        return self.AddEvent(self.onAddRerollShopBanner, args)

    def EditRerollShopBanner(self, bannerInfo):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopBanner.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": bannerInfo.endTime, "startTime": bannerInfo.startTime, "locale": bannerInfo.locale,
                         "enabled": bannerInfo.enabled, "description": bannerInfo.description,
                         "type": ConfigEventType.RerollShopBanner, "mainUrl": bannerInfo.mainUrl,
                         "action": "add_reroll_shop_banner_event"}
            self.lastEventId = bannerInfo.persistentId
            self.onAddRerollShopBanner({"r": 1})
            raise AsyncThriftException("async EditRerollShopBanner call")
        else:
            return result

    def onAddRerollShopBanner(self, response):
        debug("onAddRerollShopBanner response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"mainUrl": self.args["mainUrl"],
                                "locale": self.args["locale"]}},
                               params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    def GetRerollShopTooltips(self):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopTooltips.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"type": ConfigEventType.RerollShopTooltip},
                             params=None, callback=self.onGetRerollShopTooltips)
            raise AsyncThriftException("async GetRerollShopTooltips call")
        else:
            return result

    def onGetRerollShopTooltips(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopTooltipsResponse(
            result=RequestResult.BadServiceType, rerollShopTooltips=[])
        if response:
            info("Response = %r", response)
            try:
                for obj in response["r"]:
                     rerollShopTooltipEvent = AccountManagementAPI.ttypes.RerollShopTooltip(locale=obj['customData']['locale'],
                                                                     startTime=obj['startTime'],
                                                                     endTime=obj['endTime'],
                                                                     persistentId=obj['_id'],
                                                                     tooltip=obj['customData']['tooltip'].encode("utf8"),
                                                                     enabled=obj['enabled'],
                                                                     description=obj['description'].encode("utf8"))
                     self.handler.result.rerollShopTooltips.append(rerollShopTooltipEvent)
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def GetRerollShopTooltipById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRerollShopTooltipById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {"_id": persistentId},
                             params=None, callback=self.onGetRerollShopTooltipById)
            raise AsyncThriftException("async GetRerollShopTooltipById call")
        else:
            return result

    def onGetRerollShopTooltipById(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RerollShopTooltipByIdResponse(
            result=RequestResult.BadServiceType, rerollShopTooltip=0)
        if response:
            info("Response = %r", response)
            try:
                obj = response["r"]
                self.handler.result.rerollShopTooltip = \
                    AccountManagementAPI.ttypes.RerollShopTooltip(locale=obj['customData']['locale'],
                                                           startTime=obj['startTime'],
                                                           endTime=obj['endTime'],
                                                           persistentId=obj['_id'],
                                                           tooltip=obj['customData']['tooltip'].encode("utf8"),
                                                           enabled=obj['enabled'],
                                                           description=obj['description'].encode("utf8"))
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()  # вызываем повторную обработку евента (теперь должно вернуть ответ)

    def AddRerollShopTooltip(self, tooltipInfo):
        args = {"endTime": tooltipInfo.endTime, "startTime": tooltipInfo.startTime, "locale": tooltipInfo.locale,
                "enabled": tooltipInfo.enabled, "description": tooltipInfo.description,
                "type": ConfigEventType.RerollShopTooltip, "tooltip": tooltipInfo.tooltip,
                "action": "add_reroll_shop_tooltip_event"}
        return self.AddEvent(self.onAddRerollShopTooltip, args)

    def EditRerollShopTooltip(self, tooltipInfo):
        result = getattr(self.handler, "result", None)
        info("EditRerollShopTooltip.onStart, result = %r", result)
        if result is None:
            self.args = {"endTime": tooltipInfo.endTime, "startTime": tooltipInfo.startTime, "locale": tooltipInfo.locale,
                         "enabled": tooltipInfo.enabled, "description": tooltipInfo.description,
                         "type": ConfigEventType.RerollShopTooltip, "tooltip": tooltipInfo.tooltip,
                         "action": "add_reroll_shop_tooltip_event"}
            self.lastEventId = tooltipInfo.persistentId
            self.onAddRerollShopTooltip({"r": 1})
            raise AsyncThriftException("async EditRerollShopTooltip call")
        else:
            return result

    def onAddRerollShopTooltip(self, response):
        debug("onAddRerollShopTooltip response=%r", response)
        if response and response["r"] is not None:
            self.args["persistentId"] = self.lastEventId
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {"_id": self.lastEventId},
                               {"endTime": self.args["endTime"],
                                "startTime": self.args["startTime"],
                                "enabled": self.args["enabled"], "description": self.args["description"],
                                "type": self.args["type"], "customData": {"tooltip": self.args["tooltip"],
                                "locale": self.args["locale"]}},
                               params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    # region Roll events
    # ==================

    @staticmethod
    def convert_dict_to_resource_table_small(record):
        """

        :param record:
        :type record: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.ResourceTableSmall
        """
        resource1 = record.get('resource1', 0)
        resource2 = record.get('resource2', 0)
        resource3 = record.get('resource3', 0)
        silver = record.get('silver', 0)
        gold = record.get('gold', 0)
        pearl = record.get('perl', 0)
        red_pearl = record.get('redPerl')
        currency_id = record.get('currencyId', '')
        currency = record.get('currency', 0)
        result = AccountManagementAPI.ttypes.ResourceTableSmall(resource1=resource1, resource2=resource2,
                                                                resource3=resource3, silver=silver, gold=gold,
                                                                perl=pearl, redPerl=red_pearl, currencyId=currency_id,
                                                                currency=currency)
        return result

    @staticmethod
    def convert_resource_table_small_to_dict(resource_table_small):
        """

        :param resource_table_small:
        :type resource_table_small: AccountManagementAPI.ttypes.ResourceTableSmall
        :return:
        :rtype: dict
        """
        result = dict(resource1=resource_table_small.resource1, resource2=resource_table_small.resource2,
                      resource3=resource_table_small.resource3, silver=resource_table_small.silver,
                      gold=resource_table_small.gold, pearl=resource_table_small.perl,
                      redPearl=resource_table_small.redPerl, currencyId=resource_table_small.currencyId,
                      currency=resource_table_small.currency)
        return result

    @staticmethod
    def convert_record_to_roll_event_item(record):
        """

        :param record:
        :type record: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.RollEventItem
        """
        item_type = record.get('itemType', 0)
        persistent_id = record.get('persistentId', '')
        resource = BroadcastHandler.convert_dict_to_resource_table_small(record.get('resource', {}))
        ratio = record.get('ratio', 0.0)
        result = AccountManagementAPI.ttypes.RollEventItem(itemType=item_type, persistentId=persistent_id,
                                                           resource=resource, ratio=ratio)
        return result

    @staticmethod
    def convert_roll_event_item_to_dict(roll_event_item):
        """

        :param roll_event_item:
        :type roll_event_item: AccountManagementAPI.ttypes.RollEventItem
        :return:
        :rtype: dict
        """
        resource = BroadcastHandler.convert_resource_table_small_to_dict(roll_event_item.resource)
        result = dict(itemType=roll_event_item.itemType, persistentId=roll_event_item.persistentId,
                      resource=resource, ratio=roll_event_item.ratio)
        return result

    @staticmethod
    def convert_dict_to_roll_event_rule(record):
        """

        :param record:
        :type record: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.RollEventRule
        """
        rule_type = record.get('ruleType', 0)
        description = record.get('description', '').encode('utf8')
        title = record.get('title', '').encode('utf8')
        text = record.get('text', '').encode('utf8')
        price = BroadcastHandler.convert_dict_to_resource_table_small(record.get('price', {}))
        rewards = [BroadcastHandler.convert_record_to_roll_event_item(r) for r in record.get('rewards', [])]
        reforge_sources = [BroadcastHandler.convert_record_to_roll_event_item(r)
                           for r in record.get('reforgeSource', [])]
        result = AccountManagementAPI.ttypes.RollEventRule(ruleType=rule_type, description=description,
                                                           titleLocalized=title, textLocalized=text, price=price,
                                                           rewards=rewards, reforgeSource=reforge_sources)
        return result

    @staticmethod
    def convert_roll_event_rule_to_dict(roll_event_rule):
        """

        :param roll_event_rule:
        :type roll_event_rule: AccountManagementAPI.ttypes.RollEventRule
        :return:
        :rtype: dict
        """
        price = BroadcastHandler.convert_resource_table_small_to_dict(roll_event_rule.price)
        rewards = [BroadcastHandler.convert_roll_event_item_to_dict(r) for r in roll_event_rule.rewards]
        reforge_source = [BroadcastHandler.convert_roll_event_item_to_dict(r) for r in roll_event_rule.reforgeSource]
        result = dict(ruleType=roll_event_rule.ruleType, description=roll_event_rule.description,
                      title=roll_event_rule.titleLocalized, text=roll_event_rule.textLocalized, price=price,
                      rewards=rewards, reforgeSource=reforge_source)
        return result

    @staticmethod
    def convert_dict_to_roll_event(record):
        """

        :param record:
        :type record: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.RollEvent
        """
        persistent_id = record['_id']
        start_time = record['startTime']
        end_time = record['endTime']
        enabled = record['enabled']
        description = record['description'].encode('utf8')
        custom_data = record.get('customData', {})
        locale = custom_data.get('locale', 'ru')
        title = custom_data.get('title', '').encode('utf8')
        image = custom_data.get('image', '')
        text = custom_data.get('text', '').encode('utf8')
        currency_ids = [r.encode('utf8') for r in custom_data.get('currencyIds', [])]
        rolls = [BroadcastHandler.convert_dict_to_roll_event_rule(r) for r in custom_data.get('rolls', [])]
        completion_talent_id = custom_data.get('completionTalentId', '')
        completion_talent_ratio = custom_data.get('completionTalentRatio', 1)
        guid = custom_data.get('guid', -1)
        result = AccountManagementAPI.ttypes.RollEvent(persistentId=persistent_id, startTime=start_time,
                                                       endTime=end_time, locale=locale, enabled=enabled,
                                                       description=description, title=title, image=image, text=text,
                                                       currencyIds=currency_ids, rolls=rolls,
                                                       completionTalentId=completion_talent_id,
                                                       completionTalentRatio=completion_talent_ratio, guid=guid)
        return result

    @staticmethod
    def convert_roll_event_to_dict(obj):
        """

        :param obj:
        :type obj: AccountManagementAPI.ttypes.RollEvent
        :return:
        :rtype: dict
        """
        rolls = [BroadcastHandler.convert_roll_event_rule_to_dict(r) for r in obj.rolls]
        custom_data = dict(locale=obj.locale, title=obj.title, image=obj.image, text=obj.text,
                           currencyIds=obj.currencyIds, rolls=rolls, completionTalentId=obj.completionTalentId,
                           completionTalentRatio=obj.completionTalentRatio, guid=obj.guid)
        result = dict(type=ConfigEventType.RollEvent, startTime=obj.startTime, endTime=obj.endTime,
                      enabled=obj.enabled, description=obj.description, customData=custom_data)
        return result

    @staticmethod
    def convert_roll_event_dict_to_args(dct):
        """

        :param dct:
        :type dct: dict
        :return:
        :rtype: dict
        """
        custom_data = json_dumps(dct['customData'])
        result = dict(action='add_roll_event', type=dct['type'], startTime=dct['startTime'], endTime=dct['endTime'],
                      enabled=dct['enabled'], description=dct['description'], customData=custom_data)
        return result

    @staticmethod
    def convert_roll_event_args_to_dict(args):
        """

        :param args:
        :type args: dict
        :return:
        :rtype: dict
        """
        custom_data = json_loads(args['customData'])
        result = dict(type=args['type'], startTime=args['startTime'], endTime=args['endTime'], enabled=args['enabled'],
                      description=args['description'], customData=custom_data)
        return result

    def GetRollEvents(self):
        result = getattr(self.handler, "result", None)
        info("GetRollEvents.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {'type': ConfigEventType.RollEvent},
                             params=None, callback=self.on_get_roll_events)
            raise AsyncThriftException("async GetRollEvents call")
        else:
            return result

    def on_get_roll_events(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RollEventsResponse(result=RequestResult.BadServiceType,
                                                                             rollEvents=[])
        if response:
            info("Response = %r", response)
            try:
                roll_events = [BroadcastHandler.convert_dict_to_roll_event(r) for r in response['r']]
                self.handler.result.rollEvents += roll_events
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def GetRollEventById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetRollEventById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                                 {'_id': persistentId, 'type': ConfigEventType.RollEvent},
                                 params=None, callback=self.on_get_roll_event_by_id)
            raise AsyncThriftException("async GetRollEventById call")
        else:
            return result

    def on_get_roll_event_by_id(self, response):
        self.handler.result = AccountManagementAPI.ttypes.RollEventByIdResponse(result=RequestResult.BadServiceType,
                                                                                rollEvent=0)
        if response:
            info("Response = %r", response)
            try:
                roll_event = BroadcastHandler.convert_dict_to_roll_event(response['r'])
                self.handler.result.rollEvent = roll_event
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def AddRollEvent(self, rollEvent):
        """

        :param rollEvent:
        :type rollEvent: AccountManagementAPI.ttypes.RollEvent
        :return:
        """
        roll_event_dict = BroadcastHandler.convert_roll_event_to_dict(rollEvent)
        args = BroadcastHandler.convert_roll_event_dict_to_args(roll_event_dict)
        return self.AddEvent(self.on_add_roll_event, args)

    def EditRollEvent(self, rollEvent):
        """

        :param rollEvent:
        :type rollEvent: AccountManagementAPI.ttypes.RollEvent
        :return:
        """
        result = getattr(self.handler, "result", None)
        info("EditRollEvent.onStart, result = %r", result)
        if result is None:
            roll_event_dict = BroadcastHandler.convert_roll_event_to_dict(rollEvent)
            self.args = BroadcastHandler.convert_roll_event_dict_to_args(roll_event_dict)
            self.args['action'] = 'add_roll_event'
            self.lastEventId = rollEvent.persistentId
            self.on_add_roll_event({'r': 1})
            raise AsyncThriftException("async EditRollEvent call")
        else:
            return result

    def on_add_roll_event(self, response):
        debug("on_add_roll_event response = %r", response)
        if response and response['r'] is not None:
            self.args['persistentId'] = self.lastEventId
            roll_event_dict = BroadcastHandler.convert_roll_event_args_to_dict(self.args)
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {'_id': self.lastEventId},
                               roll_event_dict, params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    # endregion

    # region Quest events
    # ===================

    @staticmethod
    def convert_dict_to_quest_event_stage_step_variant(dct):
        """

        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.QuestEventStageStepVariant
        """
        message = dct.get('message', '').encode('utf8')
        winMessage = dct.get('winMessage', '').encode('utf8')
        loseMessage = dct.get('loseMessage', '').encode('utf8')
        winRatioBase = dct.get('winRatioBase', 0.9)
        winRatioGold = dct.get('winRatioGold', 0.95)
        price = BroadcastHandler.convert_dict_to_resource_table_small(dct.get('price', {}))
        obj = AccountManagementAPI.ttypes.QuestEventStageStepVariant(message=message, winMessage=winMessage,
                                                                     loseMessage=loseMessage, winRatioBase=winRatioBase,
                                                                     winRatioGold=winRatioGold, price=price)
        return obj

    @staticmethod
    def convert_quest_event_stage_step_variant_to_dict(obj):
        """

        :param obj:
        :type obj: AccountManagementAPI.ttypes.QuestEventStageStepVariant
        :return:
        :rtype: dict
        """
        price = BroadcastHandler.convert_resource_table_small_to_dict(obj.price)
        dct = dict(message=obj.message, winMessage=obj.winMessage, loseMessage=obj.loseMessage,
                   winRatioBase=obj.winRatioBase, winRatioGold=obj.winRatioGold, price=price)
        return dct

    @staticmethod
    def convert_dict_to_quest_event_stage_step(dct):
        """

        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.QuestEventStageStep
        """
        title = dct.get('title', '').encode('utf8')
        variants = [BroadcastHandler.convert_dict_to_quest_event_stage_step_variant(r) for r in dct.get('variants', [])]
        obj = AccountManagementAPI.ttypes.QuestEventStageStep(title=title, variants=variants)
        return obj

    @staticmethod
    def convert_quest_event_stage_step_to_dict(obj):
        """

        :param obj:
        :type obj: AccountManagementAPI.ttypes.QuestEventStageStep
        :return:
        :rtype: dict
        """
        variants = [BroadcastHandler.convert_quest_event_stage_step_variant_to_dict(r) for r in obj.variants]
        dct = dict(title=obj.title, variants=variants)
        return dct

    @staticmethod
    def convert_dict_to_quest_event_stage(dct):
        """

        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.QuestEventStage
        """
        title = dct.get('title', '').encode('utf8')
        text = dct.get('text', '').encode('utf8')
        image = dct.get('image', '')
        reward = BroadcastHandler.convert_record_to_roll_event_item(dct.get('reward', {}))
        steps = [BroadcastHandler.convert_dict_to_quest_event_stage_step(r) for r in dct.get('steps', [])]
        loseReward = BroadcastHandler.convert_record_to_roll_event_item(dct.get('loseReward', {}))
        obj = AccountManagementAPI.ttypes.QuestEventStage(title=title, text=text, image=image, reward=reward,
                                                          steps=steps, loseReward=loseReward)
        return obj

    @staticmethod
    def convert_quest_event_stage_to_dict(obj):
        """

        :param obj:
        :type obj: AccountManagementAPI.ttypes.QuestEventStage
        :return:
        :rtype: dict
        """
        reward = BroadcastHandler.convert_roll_event_item_to_dict(obj.reward)
        steps = [BroadcastHandler.convert_quest_event_stage_step_to_dict(r) for r in obj.steps]
        loseReward = BroadcastHandler.convert_roll_event_item_to_dict(obj.loseReward)
        dct = dict(title=obj.title, text=obj.text, image=obj.image, reward=reward, steps=steps,loseReward=loseReward)
        return dct

    @staticmethod
    def convert_dict_to_quest_event(dct):
        """
        Create QuestEvent object from MongoDB collection item
        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.QuestEvent
        """
        persistent_id = dct['_id']
        start_time = dct['startTime']
        end_time = dct['endTime']
        enabled = dct['enabled']
        description = dct['description'].encode('utf8')
        custom_data = dct['customData']
        locale = custom_data.get('locale', 'ru')
        title = custom_data.get('title', '').encode('utf8')
        text = custom_data.get('text', '').encode('utf8')
        completion_talent_id = custom_data.get('completionTalentId', '')
        completion_talent_ratio = custom_data.get('completionTalentRatio', 1)
        currency_ids = [r.encode('utf8') for r in custom_data.get('currencyIds', [])]
        stages = [BroadcastHandler.convert_dict_to_quest_event_stage(r) for r in custom_data.get('stages', [])]
        guid = custom_data.get('guid', -1)
        result = AccountManagementAPI.ttypes.QuestEvent(persistentId=persistent_id, startTime=start_time,
                                                        endTime=end_time, locale=locale, enabled=enabled,
                                                        description=description, title=title, text=text,
                                                        currencyIds=currency_ids, stages=stages,
                                                        completionTalentId=completion_talent_id,
                                                        completionTalentRatio=completion_talent_ratio, guid=guid)
        return result

    @staticmethod
    def convert_quest_event_to_dict(obj):
        """
        Create MongoDB collection item from QuestEvent object
        :param obj:
        :type obj: AccountManagementAPI.ttypes.QuestEvent
        :return:
        :rtype: dict
        """
        stages = [BroadcastHandler.convert_quest_event_stage_to_dict(r) for r in obj.stages]
        custom_data = dict(locale=obj.locale, title=obj.title, text=obj.text, currencyIds=obj.currencyIds,
                           stages=stages, completionTalentId=obj.completionTalentId,
                           completionTalentRatio=obj.completionTalentRatio, guid=obj.guid)
        dct = dict(type=ConfigEventType.QuestEvent, startTime=obj.startTime, endTime=obj.endTime, enabled=obj.enabled,
                   description=obj.description, customData=custom_data)
        return dct

    @staticmethod
    def convert_quest_event_dict_to_args(dct):
        args = dict(dct)
        args['action'] = 'add_quest_event'
        args['customData'] = json_dumps(dct['customData'])
        return args

    @staticmethod
    def convert_quest_event_args_to_dict(args):
        dct = dict(args)
        dct['customData'] = json_loads(args['customData'])
        if 'action' in dct:
            del dct['action']
        return dct

    def GetQuestEvents(self):
        result = getattr(self.handler, "result", None)
        info("GetQuestEvents.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {'type': ConfigEventType.QuestEvent},
                             params=None, callback=self.on_get_quest_events)
            raise AsyncThriftException("async GetQuestEvents call")
        else:
            return result

    def on_get_quest_events(self, response):
        self.handler.result = AccountManagementAPI.ttypes.QuestEventsResponse(result=RequestResult.BadServiceType,
                                                                              questEvents=[])
        if response:
            info("Response = %r", response)
            try:
                quest_events = [BroadcastHandler.convert_dict_to_quest_event(r) for r in response['r']]
                self.handler.result.questEvents += quest_events
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def GetQuestEventById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetQuestEventById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                                 {'_id': persistentId, 'type': ConfigEventType.QuestEvent},
                                 params=None, callback=self.on_get_quest_event_by_id)
            raise AsyncThriftException("async GetQuestEventById call")
        else:
            return result

    def on_get_quest_event_by_id(self, response):
        self.handler.result = AccountManagementAPI.ttypes.QuestEventByIdResponse(result=RequestResult.BadServiceType,
                                                                                 questEvent=0)
        if response:
            info("Response = %r", response)
            try:
                quest_event = BroadcastHandler.convert_dict_to_quest_event(response['r'])
                self.handler.result.questEvent = quest_event
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def AddQuestEvent(self, questEvent):
        quest_event_dict = BroadcastHandler.convert_quest_event_to_dict(questEvent)
        args = BroadcastHandler.convert_quest_event_dict_to_args(quest_event_dict)
        return self.AddEvent(self.on_add_quest_event, args)

    def EditQuestEvent(self, questEvent):
        result = getattr(self.handler, "result", None)
        info("EditQuestEvent.onStart, result = %r", result)
        if result is None:
            quest_event_dict = BroadcastHandler.convert_quest_event_to_dict(questEvent)
            self.args = BroadcastHandler.convert_quest_event_dict_to_args(quest_event_dict)
            self.lastEventId = questEvent.persistentId
            self.on_add_quest_event({'r': 1})
            raise AsyncThriftException("async EditQuestEvent call")
        else:
            return result

    def on_add_quest_event(self, response):
        debug("on_add_quest_event response = %r", response)
        if response and response['r'] is not None:
            self.args['persistentId'] = self.lastEventId
            quest_event_dict = BroadcastHandler.convert_quest_event_args_to_dict(self.args)
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {'_id': self.lastEventId},
                               quest_event_dict, params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    # endregion

    # region TradeEvent

    def AddTradeEvent(self, tradeEvent):
        trade_event_dict = BroadcastHandler.convert_trade_event_to_dict(tradeEvent)
        args = BroadcastHandler.convert_trade_event_dict_to_args(trade_event_dict)
        return self.AddEvent(self.on_add_trade_event, args)


    def EditTradeEvent(self, tradeEvent):
        """

        :param tradeEvent:
        :type tradeEvent: AccountManagementAPI.ttypes.TradeEvent
        :return:
        """
        result = getattr(self.handler, "result", None)
        info("EditTradeEvent.onStart, result = %r", result)
        if result is None:
            trade_event_dict = BroadcastHandler.convert_trade_event_to_dict(tradeEvent)
            self.args = BroadcastHandler.convert_trade_event_dict_to_args(trade_event_dict)
            self.args['action'] = 'add_trade_event'
            self.lastEventId = tradeEvent.persistentId
            self.on_add_trade_event({'r': 1})
            raise AsyncThriftException("async EditRollEvent call")
        else:
            return result


    def on_add_trade_event(self, response):
        debug("on_add_trade_event response = %r", response)
        if response and response['r'] is not None:
            self.args['persistentId'] = self.lastEventId
            trade_event_dict = BroadcastHandler.convert_trade_event_args_to_dict(self.args)
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA,
                               {'_id': self.lastEventId},
                               trade_event_dict, params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()


    @staticmethod
    def convert_trade_event_to_dict(obj):
        """
        Create MongoDB collection item from TradeEvent object
        :param obj:
        :type obj: AccountManagementAPI.ttypes.TradeEventModel
        :return:
        :rtype: dict
        """
        tradeEventGroups = [BroadcastHandler.convert_trade_event_group_to_dict(r) for r in obj.tradeEventGroups]
        worldRatingRewardRelations = [BroadcastHandler.convert_world_rating_reward_to_dict(r) for r in obj.worldRatingRewardRelations]
        experienceRewardRelations = [BroadcastHandler.convert_experience_reward_to_dict(r) for r in obj.experienceRewardRelations]
        custom_data = dict(locale=obj.locale,
                           guid=obj.guid,
                           experienceCurrencyName=obj.experienceCurrencyName,
                           completionTalentId=obj.completionTalentId,
                           title=obj.title,
                           text=obj.text,
                           bannerUrl=obj.bannerUrl,
                           completionTalentRatio=obj.completionTalentRatio,
                           rewardsBlockTitle=obj.rewardsBlockTitle,
                           tradeEventGroups=tradeEventGroups,
                           worldRatingRewardRelations=worldRatingRewardRelations,
                           experienceRewardRelations=experienceRewardRelations)
        dct = dict(type=ConfigEventType.TradeEvent, startTime=obj.startTime, endTime=obj.endTime, enabled=obj.enabled,
                   description=obj.description, customData=custom_data)
        return dct

    @staticmethod
    def convert_experience_reward_to_dict(obj):

        reward = BroadcastHandler.convert_roll_event_item_to_dict(obj.reward)
        dct = dict(rewardCount=obj.rewardCount, experience=obj.experience, reward=reward, isMinor=obj.isMinor)
        return dct

    @staticmethod
    def convert_world_rating_reward_to_dict(obj):

        reward = BroadcastHandler.convert_roll_event_item_to_dict(obj.reward)
        dct = dict(rewardCount=obj.rewardCount, worldPosition=obj.worldPosition, reward=reward)
        return dct

    @staticmethod
    def convert_trade_event_group_to_dict(obj):

        tradeGroupMembers = [BroadcastHandler.convert_trade_event_group_members_to_dict(r) for r in obj.tradeGroupMembers]
        dct = dict(name=obj.name, tradeGroupMembers=tradeGroupMembers)
        return dct

    @staticmethod
    def convert_trade_event_group_members_to_dict(obj):

        rewardA = BroadcastHandler.convert_roll_event_item_to_dict(obj.rewardA)
        rewardB = BroadcastHandler.convert_roll_event_item_to_dict(obj.rewardB)

        dct = dict(name=obj.name, image=obj.image, currencyName=obj.currencyName, currencyCostPerExp=obj.currencyCostPerExp,
                   rewardA=rewardA, rewardACost=obj.rewardACost, rewardB=rewardB, rewardBCost=obj.rewardBCost)
        return dct

    @staticmethod
    def convert_trade_event_dict_to_args(dct):
        args = dict(dct)
        args['action'] = 'add_trade_event'
        args['customData'] = json_dumps(dct['customData'])
        return args

    @staticmethod
    def convert_trade_event_args_to_dict(args):
        dct = dict(args)
        dct['customData'] = json_loads(args['customData'])
        if 'action' in dct:
            del dct['action']
        return dct

    def GetTradeEvents(self):
        result = getattr(self.handler, "result", None)
        info("GetTradeEvents.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA,
                             {'type': ConfigEventType.TradeEvent},
                             params=None, callback=self.on_get_trade_events)
            raise AsyncThriftException("async GetTradeEvents call")
        else:
            return result

    def on_get_trade_events(self, response):
        self.handler.result = AccountManagementAPI.ttypes.TradeEventsResponse(result=RequestResult.BadServiceType,
                                                                              tradeEvents=[])
        if response:
            info("Response = %r", response)
            try:
                trade_events = [BroadcastHandler.convert_dict_to_trade_event(r) for r in response['r']]
                self.handler.result.tradeEvents += trade_events
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def GetTradeEventById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetTradeEventById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                                 {'_id': persistentId, 'type': ConfigEventType.TradeEvent},
                                 params=None, callback=self.on_get_trade_event_by_id)
            raise AsyncThriftException("async GetTradeEventById call")
        else:
            return result

    def on_get_trade_event_by_id(self, response):
        self.handler.result = AccountManagementAPI.ttypes.TradeEventByIdResponse(result=RequestResult.BadServiceType,
                                                                                 tradeEvent=0)
        if response:
            info("Response = %r", response)
            try:
                trade_event = BroadcastHandler.convert_dict_to_trade_event(response['r'])
                self.handler.result.tradeEvent = trade_event
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    @staticmethod
    def convert_dict_to_trade_event(dct):
        """
        Create TradeEvent object from MongoDB collection item
        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.TradeEvent
        """
        persistent_id = dct['_id']
        start_time = dct['startTime']
        end_time = dct['endTime']
        enabled = dct['enabled']
        description = dct['description'].encode('utf8')

        custom_data = dct['customData']
        locale = custom_data.get('locale', 'ru')
        bannerUrl = custom_data.get('bannerUrl', '').encode('utf8')
        title = custom_data.get('title', '').encode('utf8')
        text = custom_data.get('text', '').encode('utf8')
        guid = custom_data.get('guid', -1)
        rewardsBlockTitle = custom_data.get('rewardsBlockTitle', '').encode('utf8')

        completion_talent_id = custom_data.get('completionTalentId', '').encode('utf8')
        completion_talent_ratio = custom_data.get('completionTalentRatio', 1)
        experienceCurrencyName = custom_data.get('experienceCurrencyName', '').encode('utf8')
        tradeEventGroups = [BroadcastHandler.convert_dict_to_trade_event_group(r) for r in custom_data.get('tradeEventGroups', [])]
        worldRatingRewardRelations = [BroadcastHandler.convert_dict_to_world_rating_reward(r) for r in custom_data.get('worldRatingRewardRelations', [])]
        experienceRewardRelations = [BroadcastHandler.convert_dict_to_experience_reward(r) for r in custom_data.get('experienceRewardRelations', [])]
        return AccountManagementAPI.ttypes.TradeEventModel(persistentId=persistent_id, startTime=start_time,
                                                        endTime=end_time, locale=locale, enabled=enabled,
                                                        description=description,
                                                        bannerUrl=bannerUrl,
                                                        title=title,
                                                        text=text,
                                                        guid=guid,
                                                        rewardsBlockTitle=rewardsBlockTitle,
                                                        completionTalentId=completion_talent_id,
                                                        completionTalentRatio=completion_talent_ratio,
                                                        experienceCurrencyName=experienceCurrencyName,
                                                        tradeEventGroups=tradeEventGroups,
                                                        worldRatingRewardRelations=worldRatingRewardRelations,
                                                        experienceRewardRelations=experienceRewardRelations)

    @staticmethod
    def convert_dict_to_trade_event_group(dct):
        """

        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.TradeEventGroupModel
        """
        tradeGroupMembers = []
        for group in dct.get('tradeGroupMembers', []):
            tradeGroupMembers.append(AccountManagementAPI.ttypes.TradeGroupMemberModel(
                name=group.get('name', '').encode('utf8'), image=group.get('image', '').encode('utf8'),
                currencyName=group.get('currencyName', '').encode('utf8'),
                currencyCostPerExp=group.get('currencyCostPerExp', -1.0),
                rewardA=BroadcastHandler.convert_record_to_roll_event_item(group.get('rewardA', '')),
                rewardACost=group.get('rewardACost', -1),
                rewardB=BroadcastHandler.convert_record_to_roll_event_item(group.get('rewardB', '')),
                rewardBCost=group.get('rewardBCost', -1),
            ))

        obj = AccountManagementAPI.ttypes.TradeEventGroupModel(name=dct['name'].encode('utf8'), tradeGroupMembers=tradeGroupMembers)
        return obj

    @staticmethod
    def convert_dict_to_world_rating_reward(dct):
        return AccountManagementAPI.ttypes.WorldRatingRewardRelation(
            reward=BroadcastHandler.convert_record_to_roll_event_item(dct.get('reward', '')),
            rewardCount=dct.get('rewardCount', ''),
            worldPosition=dct.get('worldPosition', ''),
        )

    @staticmethod
    def convert_dict_to_experience_reward(dct):
        return AccountManagementAPI.ttypes.ExperienceRewardRelation(
            reward=BroadcastHandler.convert_record_to_roll_event_item(dct.get('reward', '')),
            rewardCount=dct.get('rewardCount', ''),
            isMinor=dct.get('isMinor', True),
            experience=dct.get('experience', ''),
        )
    # endregion

    # region SeasonEvent

    def AddSeasonEvent(self, event):
        event_dict = BroadcastHandler.convert_season_event_to_dict(event)
        args = BroadcastHandler.convert_season_event_dict_to_args(event_dict)
        return self.AddEvent(self.on_add_season_event, args)

    def EditSeasonEvent(self, event):
        """

        :param event:
        :type event: AccountManagementAPI.ttypes.SeasonEvent
        :return:
        """
        result = getattr(self.handler, "result", None)
        info("EditSeasonEvent.onStart, result = %r", result)
        if result is None:
            event_dict = BroadcastHandler.convert_season_event_to_dict(event)
            self.args = BroadcastHandler.convert_season_event_dict_to_args(event_dict)
            self.args['action'] = 'add_season_event'
            self.lastEventId = event.persistentId
            self.on_add_season_event({'r': 1})
            raise AsyncThriftException("async EditSeasonEvent call")
        else:
            return result

    def on_add_season_event(self, response):
        debug("on_add_season_event response = %r", response)
        if response and response['r'] is not None:
            self.args['persistentId'] = self.lastEventId
            event_dict = BroadcastHandler.convert_season_event_args_to_dict(self.args)
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA, {'_id': self.lastEventId}, event_dict,
                               params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    @staticmethod
    def convert_season_event_to_dict(obj):
        """
        Create MongoDB collection item from SeasonEvent object
        :param obj:
        :type obj: AccountManagementAPI.ttypes.SeasonEvent
        :return:
        :rtype: dict
        """
        seasonEventGroups = [BroadcastHandler.convert_season_event_shop_group_to_dict(r) for r in obj.shopGroups]
        worldRatingRewardRelations = [BroadcastHandler.convert_world_rating_reward_to_dict(r) for r in
                                      obj.worldRatingRewardRelations]
        progressRewardRelations = [BroadcastHandler.convert_season_progress_reward_to_dict(r) for r in
                                     obj.progressRewardRelations]
        custom_data = dict(locale=obj.locale, guid=obj.guid, shopCurrencyId=obj.shopCurrencyId,
                           rewardsCurrencyId=obj.rewardsCurrencyId,
                           completionTalentId=obj.completionTalentId, title=obj.title, text=obj.text,
                           bannerUrl=obj.bannerUrl, completionTalentRatio=obj.completionTalentRatio,
                           rewardsBlockTitle=obj.rewardsBlockTitle, shopGroups=seasonEventGroups,
                           worldRatingRewardRelations=worldRatingRewardRelations,
                           progressRewardRelations=progressRewardRelations)
        dct = dict(type=ConfigEventType.SeasonEvent, startTime=obj.startTime, endTime=obj.endTime,
                   enabled=obj.enabled, description=obj.description, customData=custom_data)
        return dct

    @staticmethod
    def convert_season_progress_reward_to_dict(obj):
        reward = BroadcastHandler.convert_roll_event_item_to_dict(obj.reward)
        dct = dict(rewardCount=obj.rewardCount, requiredProgress=obj.requiredProgress, reward=reward)
        return dct

#    @staticmethod
#    def convert_world_rating_reward_to_dict(obj):
#
#        reward = BroadcastHandler.convert_roll_event_item_to_dict(obj.reward)
#        dct = dict(rewardCount=obj.rewardCount, worldPosition=obj.worldPosition, reward=reward)
#        return dct

    @staticmethod
    def convert_season_event_shop_group_to_dict(obj):
        items = [BroadcastHandler.convert_season_event_shop_item_to_dict(r) for r in obj.items]
        dct = dict(name=obj.name, items=items)
        return dct

    @staticmethod
    def convert_season_event_shop_item_to_dict(obj):
        #reward = BroadcastHandler.convert_roll_event_item_to_dict(obj.reward)
        dct = dict(name=obj.name, image=obj.image, lootboxId=obj.lootboxId, cost=obj.cost, limit=obj.limit)
        return dct

    @staticmethod
    def convert_season_event_dict_to_args(dct):
        args = dict(dct)
        args['action'] = 'add_season_event'
        args['customData'] = json_dumps(dct['customData'])
        return args

    @staticmethod
    def convert_season_event_args_to_dict(args):
        dct = dict(args)
        dct['customData'] = json_loads(args['customData'])
        if 'action' in dct:
            del dct['action']
        return dct

    def GetSeasonEvents(self):
        result = getattr(self.handler, "result", None)
        info("GetSeasonEvents.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA, {'type': ConfigEventType.SeasonEvent}, params=None,
                             callback=self.on_get_season_events)
            raise AsyncThriftException("async GetSeasonEvents call")
        else:
            return result

    def on_get_season_events(self, response):
        self.handler.result = AccountManagementAPI.ttypes.SeasonEventsResponse(result=RequestResult.BadServiceType,
                                                                              seasonEvents=[])
        if response:
            info("Response = %r", response)
            try:
                season_events = [BroadcastHandler.convert_dict_to_season_event(r) for r in response['r']]
                self.handler.result.seasonEvents += season_events
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def GetSeasonEventById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetSeasonEventById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                                 {'_id': persistentId, 'type': ConfigEventType.SeasonEvent}, params=None,
                                 callback=self.on_get_season_event_by_id)
            raise AsyncThriftException("async GetSeasonEventById call")
        else:
            return result

    def on_get_season_event_by_id(self, response):
        self.handler.result = AccountManagementAPI.ttypes.SeasonEventByIdResponse(
            result=RequestResult.BadServiceType, seasonEvent=0)
        if response:
            info("Response = %r", response)
            try:
                season_event = BroadcastHandler.convert_dict_to_season_event(response['r'])
                self.handler.result.seasonEvent = season_event
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    @staticmethod
    def convert_dict_to_season_event(dct):
        """
        Create SeasonEvent object from MongoDB collection item
        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.SeasonEvent
        """
        persistent_id = dct['_id']
        start_time = dct['startTime']
        end_time = dct['endTime']
        enabled = dct['enabled']
        description = dct['description'].encode('utf8')

        custom_data = dct['customData']
        locale = custom_data.get('locale', 'ru')
        bannerUrl = custom_data.get('bannerUrl', '').encode('utf8')
        title = custom_data.get('title', '').encode('utf8')
        text = custom_data.get('text', '').encode('utf8')
        guid = custom_data.get('guid', -1)
        rewardsBlockTitle = custom_data.get('rewardsBlockTitle', '').encode('utf8')

        completion_talent_id = custom_data.get('completionTalentId', '').encode('utf8')
        completion_talent_ratio = custom_data.get('completionTalentRatio', 1)
        shopCurrencyId = custom_data.get('shopCurrencyId', '').encode('utf8')
        rewardsCurrencyId = custom_data.get('rewardsCurrencyId', '').encode('utf8')
        shopGroups = [BroadcastHandler.convert_dict_to_season_event_shop_group(r) for r in
                      custom_data.get('shopGroups', [])]
        worldRatingRewardRelations = [BroadcastHandler.convert_dict_to_world_rating_reward(r) for r in
                                      custom_data.get('worldRatingRewardRelations', [])]
        progressRewardRelations = [BroadcastHandler.convert_dict_to_progress_reward(r) for r in
                                     custom_data.get('progressRewardRelations', [])]
        return AccountManagementAPI.ttypes.SeasonEvent(persistentId=persistent_id, startTime=start_time,
                                                           endTime=end_time, locale=locale, enabled=enabled,
                                                           description=description, bannerUrl=bannerUrl,
                                                           title=title, text=text, guid=guid,
                                                           rewardsBlockTitle=rewardsBlockTitle,
                                                           completionTalentId=completion_talent_id,
                                                           completionTalentRatio=completion_talent_ratio,
                                                           shopCurrencyId=shopCurrencyId,
                                                           rewardsCurrencyId=rewardsCurrencyId,
                                                           shopGroups=shopGroups,
                                                           worldRatingRewardRelations=worldRatingRewardRelations,
                                                           progressRewardRelations=progressRewardRelations)

    @staticmethod
    def convert_dict_to_season_event_shop_group(dct):
        """
        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.SeasonEventShopGroup
        """
        items = []
        for group in dct.get('items', []):
            items.append(
                AccountManagementAPI.ttypes.SeasonEventShopItem(name=group.get('name', '').encode('utf8'),
                    image=group.get('image', '').encode('utf8'),
                    lootboxId=group.get('lootboxId', ''),
                    limit=group.get('limit',-1),
                    cost=group.get('cost', -1)))

        obj = AccountManagementAPI.ttypes.SeasonEventShopGroup(name=dct['name'].encode('utf8'),
                                                               items=items)
        return obj

#    @staticmethod
#    def convert_dict_to_world_rating_reward(dct):
#        return AccountManagementAPI.ttypes.WorldRatingRewardRelation(
#            reward=BroadcastHandler.convert_record_to_roll_event_item(dct.get('reward', '')),
#            rewardCount=dct.get('rewardCount', ''), worldPosition=dct.get('worldPosition', ''), )

    @staticmethod
    def convert_dict_to_progress_reward(dct):
        return AccountManagementAPI.ttypes.SeasonProgressRewardRelation(
            reward=BroadcastHandler.convert_record_to_roll_event_item(dct.get('reward', '')),
            rewardCount=dct.get('rewardCount', ''),
            requiredProgress=dct.get('requiredProgress', ''), )
    # endregion

    # region DonateEvent

    def AddDonateEvent(self, event):
        event_dict = BroadcastHandler.convert_donate_event_to_dict(event)
        args = BroadcastHandler.convert_donate_event_dict_to_args(event_dict)
        return self.AddEvent(self.on_add_donate_event, args)

    def EditDonateEvent(self, event):
        """

        :param event:
        :type event: AccountManagementAPI.ttypes.DonateEvent
        :return:
        """
        result = getattr(self.handler, "result", None)
        info("EditDonateEvent.onStart, result = %r", result)
        if result is None:
            event_dict = BroadcastHandler.convert_donate_event_to_dict(event)
            self.args = BroadcastHandler.convert_donate_event_dict_to_args(event_dict)
            self.args['action'] = 'add_donate_event'
            self.lastEventId = event.persistentId
            self.on_add_donate_event({'r': 1})
            raise AsyncThriftException("async EditDonateEvent call")
        else:
            return result

    def on_add_donate_event(self, response):
        debug("on_add_donate_event response = %r", response)
        if response and response['r'] is not None:
            self.args['persistentId'] = self.lastEventId
            event_dict = BroadcastHandler.convert_donate_event_args_to_dict(self.args)
            self.I.DATA.update(CC.EVENTS_DATA, CC.EVENTS_DATA, {'_id': self.lastEventId}, event_dict,
                               params=None, callback=self.onAddEvent)
            return
        self.handler.result = RequestResult.BadResponseFromDatabase
        self.handler.process()

    @staticmethod
    def convert_donate_event_to_dict(obj):
        """
        Create MongoDB collection item from DonateEvent object
        :param obj:
        :type obj: AccountManagementAPI.ttypes.DonateEvent
        :return:
        :rtype: dict
        """
        donateEventRanges = [BroadcastHandler.convert_donate_event_range_to_dict(r) for r in obj.ranges]
        custom_data = dict(ranges=donateEventRanges)
        dct = dict(type=ConfigEventType.DonateEvent, startTime=obj.startTime, endTime=obj.endTime,
                   enabled=obj.enabled, description=obj.description, customData=custom_data)
        return dct


    @staticmethod
    def convert_donate_event_range_to_dict(obj):
        rewards = [BroadcastHandler.convert_donate_event_range_reward_to_dict(r) for r in obj.rewards]
        dct = dict(amountFrom=obj.amountFrom, amountTo=obj.amountTo, rewards=rewards)
        return dct

    @staticmethod
    def convert_donate_event_range_reward_to_dict(obj):
        # reward = BroadcastHandler.convert_roll_event_item_to_dict(obj.reward)
        dct = dict(lootboxes=obj.lootboxes)
        return dct

    @staticmethod
    def convert_donate_event_dict_to_args(dct):
        args = dict(dct)
        args['action'] = 'add_donate_event'
        args['customData'] = json_dumps(dct['customData'])
        return args

    @staticmethod
    def convert_donate_event_args_to_dict(args):
        dct = dict(args)
        dct['customData'] = json_loads(args['customData'])
        if 'action' in dct:
            del dct['action']
        return dct

    def GetDonateEvents(self):
        result = getattr(self.handler, "result", None)
        info("GetDonateEvents.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA, {'type': ConfigEventType.DonateEvent}, params=None,
                             callback=self.on_get_donate_events)
            raise AsyncThriftException("async GetDonateEvents call")
        else:
            return result

    def on_get_donate_events(self, response):
        self.handler.result = AccountManagementAPI.ttypes.DonateEventsResponse(result=RequestResult.BadServiceType,
                                                                               donateEvents=[])
        if response:
            info("Response = %r", response)
            try:
                donate_events = [BroadcastHandler.convert_dict_to_donate_event(r) for r in response['r']]
                self.handler.result.donateEvents += donate_events
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def GetDonateEventById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetDonateEventById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.EVENTS_DATA, CC.EVENTS_DATA,
                                 {'_id': persistentId, 'type': ConfigEventType.DonateEvent}, params=None,
                                 callback=self.on_get_donate_event_by_id)
            raise AsyncThriftException("async GetDonateEventById call")
        else:
            return result

    def on_get_donate_event_by_id(self, response):
        self.handler.result = AccountManagementAPI.ttypes.DonateEventByIdResponse(
            result=RequestResult.BadServiceType, donateEvent=0)
        if response:
            info("Response = %r", response)
            try:
                donate_event = BroadcastHandler.convert_dict_to_donate_event(response['r'])
                self.handler.result.donateEvent = donate_event
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    @staticmethod
    def convert_dict_to_donate_event(dct):
        """
        Create DonateEvent object from MongoDB collection item
        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.DonateEvent
        """
        persistent_id = dct['_id']
        start_time = dct['startTime']
        end_time = dct['endTime']
        enabled = dct['enabled']
        description = dct['description'].encode('utf8')

        custom_data = dct['customData']
        ranges = [BroadcastHandler.convert_dict_to_donate_event_range(r) for r in
                      custom_data.get('ranges', [])]

        return AccountManagementAPI.ttypes.DonateEvent(persistentId=persistent_id, startTime=start_time,
                                                       endTime=end_time, enabled=enabled,
                                                       description=description,
                                                       ranges=ranges,
                                                       )

    @staticmethod
    def convert_dict_to_donate_event_range(dct):
        """
        :param dct:
        :type dct: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.DonateRange
        """
        rewards = []
        for group in dct.get('rewards', []):
            rewards.append(AccountManagementAPI.ttypes.DonateReward(lootboxes=group.get('lootboxes', [])))

        obj = AccountManagementAPI.ttypes.DonateRange(amountFrom=dct.get('amountFrom', -1),
                                                               amountTo=dct.get('amountTo', -1),
                                                               rewards=rewards)
        return obj


    # region Guild war events
    # =======================

    def GetGWEvents(self):
        result = getattr(self.handler, "result", None)
        info("GetRollEvents.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find(CC.GUILDWAR_EVENTS_DATA, CC.GUILDWAR_EVENTS_DATA,
                             {},
                             params=None, callback=self.on_get_gw_events)
            raise AsyncThriftException("async GetRollEvents call")
        else:
            return result

    def on_get_gw_events(self, response):
        self.handler.result = AccountManagementAPI.ttypes.GWEventsModelResponse(result=RequestResult.BadServiceType,
                                                                                gwEvents=[])
        if response:
            info("Response = %r", response)
            try:
                gw_events = []
                for r in response['r']:
                    try:
                        gw_events.append(BroadcastHandler.convert_dict_to_gw_event(self.I.Config.getMainConfig(), r))
                    except Exception:
                        warn("Bad event = %r", r)
                self.handler.result.gwEvents += gw_events
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def GetGWEventsModelById(self, persistentId):
        result = getattr(self.handler, "result", None)
        info("GetGWEventById.onStart, result = %r", result)
        if result is None:
            self.I.DATA.find_one(CC.GUILDWAR_EVENTS_DATA, CC.GUILDWAR_EVENTS_DATA,
                                 {'_id': persistentId},
                                 params=None, callback=self.on_get_gw_event_by_id)
            raise AsyncThriftException("async GetGwEventById call")
        else:
            return result

    def on_get_gw_event_by_id(self, response):
        self.handler.result = AccountManagementAPI.ttypes.GWEventsModelByIdResponse(result=RequestResult.BadServiceType,
                                                                                    gwEvent=0)
        if response:
            info("Response = %r", response)
            try:
                gw_event = BroadcastHandler.convert_dict_to_gw_event(self.I.Config.getMainConfig(), response['r'])
                self.handler.result.gwEvent = gw_event
                self.handler.result.result = RequestResult.Success
            except:
                catch()
                self.handler.result.result = RequestResult.BadResult
        self.handler.process()

    def EditGWEvent(self, gwEvent, gmLogin):
        """

        :param gwEvent:
        :type gwEvent: AccountManagementAPI.ttypes.GwEvent
        :return:
        """
        result = getattr(self.handler, "result", None)
        info("EditGwEvent.onStart, result = %r", result)
        info("EditGwEvent.gmLogin = %r", gmLogin)
        if result is None:
            partial_gw_event_dict = BroadcastHandler.partialconvert_gw_event_to_dict(gwEvent)
            self.I.DATA.increment(CC.GUILDWAR_EVENTS_DATA, CC.GUILDWAR_EVENTS_DATA,
                                {'_id': ObjectId(gwEvent.persistentId)},
                                {"points": long(gwEvent.points)}, params=None, upsert=False, callback=None) # warn: if query will fall - GM not will did know
            self.I.DATA.update(CC.GUILDWAR_EVENTS_DATA, CC.GUILDWAR_EVENTS_DATA,
                               {'_id': ObjectId(gwEvent.persistentId)},
                               partial_gw_event_dict, params=None, callback=self.on_edit_gw_event)

            # send editaction to stats
            args = {
                'action': 'send_gweventedit_to_stats',
                'persistentId': str(gwEvent.persistentId),
                'event_index': int(gwEvent.event_index),
                'enabled': int(gwEvent.enabled),
                'points': int(gwEvent.points),
                'endTime': int(gwEvent.endTime),
                'limit': int(gwEvent.limit),
            }
            self.I.WS.updateOneWebServer(args)
            # ----------------

            raise AsyncThriftException("async EditGwEvent call")
        else:
            return result

    def on_edit_gw_event(self, response):
        self.handler.result = RequestResult.BadResponseFromDatabase
        info("onEditGWEvent.response = %r", response)
        if response:
            self.handler.result = RequestResult.Success

        self.handler.process()

    @staticmethod
    def convert_dict_to_gw_event(config, record):
        """
        Attributes:
           - persistentId
           - enabled
           - pointsToAddLimit
           - endTime
           - locale
           - locale
           - pointsToAdd
           - limit

        :param record:
        :type record: dict
        :return:
        :rtype: AccountManagementAPI.ttypes.GWEventModel
        """
        persistent_id = str(record['_id'])
        enabled = False if int(record['enabled']) == 0 else True
        pointsToAddLimit = config.GWPOINTSTOADDLIMIT if hasattr(config, 'GWPOINTSTOADDLIMIT') else 100
        endTime = int(record['end_time'])
        points = int(record['points'])
        limit = int(record['limit'])
        event_index = int(record['event_index'])

        result = AccountManagementAPI.ttypes.GWEventModel(persistentId=persistent_id,
                                                          enabled=enabled,
                                                          pointsToAddLimit=pointsToAddLimit,
                                                          endTime=endTime,
                                                          points=points,
                                                          limit=limit,
                                                          event_index=event_index)
        return result

    @staticmethod
    def partialconvert_gw_event_to_dict(gw_event):
        """

        """
        result = dict(end_time=gw_event.endTime,
                      limit=long(gw_event.limit))
        return result

    # endregion
