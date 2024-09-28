#!/usr/bin/env python
# -*- coding: utf-8 -*-

import gc
from threading import Thread
import math
import codecs
import getopt

import pymongo

from admin_users import addNewSqlUserDB, addNewSqlUserNicknameDB, deleteSqlUser, deleteSqlUserNickname
from modeldata.persistent_data import PersistentDataManager
from modeldata.ModelData import *
from modeldata.StaticData import StaticData
from guild.GuildData import GuildData
from handlers import *
from cluster_sql import syncSqlQuery, syncSqlCommand, SyncSqlManager
import admin_guilds


sys.path.append('../cfg')
import coord_cfg
# Выходная папка для скриптов переноса баз в US на RU
OUT_JSON_PATH = os.path.join('.', 'rusmerge')
SQL_CONFIG = coord_cfg.COORDINATOR_SQL_CONFIG
MONGO_CONFIG = coord_cfg.COORDINATOR_MONGO_CONFIG

FOREACH_USERS_PER_GC_COLLECT = 10  # по умолчанию при переборе базы через foreach -- раз в 10 юзеров делаем garbage collect

# размер строки под полное и сокращённое имена гильдий
MAX_SHORTNAME_SIZE = 5
MAX_FULLNAME_SIZE = 32


def fixAccDbFunc(cursor, final_db, auidsmap, uidsmap, guildsmap, delusmap, total, threadId):
  curIdx = 0
  coll2 = getattr(final_db, "pers")
  func2 = getattr(coll2, "update")
  logFileName = "fix_acc_db" + str(threadId) + ".log"
  logFile = open(os.path.join(OUT_JSON_PATH, logFileName), "w")
  for obj in cursor:

    # 1) Получаем служебную информацию об акке
    # ###################################################
    if not obj.get("data", None):
      logFile.write("Data for account %r was not found\n" % str(obj))
      continue
    data_json = obj["data"]
    pers_key = obj["key"]

    curIdx += 1

    if curIdx % 100 == 0:
      sys.stdout.write("Thread: %r convert: %r/%r\n" % (threadId, curIdx, total))

    # Увеличим кол-во аккаунтов, после которого будем собирать мусор (+скорость)
    FOREACH_USERS_PER_GC_COLLECT = 100
    if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
      gc.collect()

    FOREACH_USERS_PER_GC_COLLECT = 10

    key_coll = pers_key.split("_")
    if len(key_coll) == 2:
      prefix = key_coll[0]
      uid = long(key_coll[1])
    else:
      sys.stdout.write("ERROR bad key %r\n" % pers_key)
      logFile.write("Bad uid key: \n" % str(pers_key))
      continue
    # ###################################################

    if uid in delusmap["fsn_uids"]:
      continue

    # 2) Загружаем acc
    # ###################################################
    acc = PersistentDataManager.newSimpleDataAcc(data_json)
    MD = ModelData()
    MD.load(acc.model)
    MD.init(changeWriter=None)
    # ###################################################

    # 3) Конвертируем acc
    # ###################################################
    usauid = acc.db.auid
    ruauid = getRusAuid(auidsmap, "auids", usauid)
    if not ruauid:
      logFile.write("User with auid %r was not found in new_auids.json\n" % str(usauid))
      continue
    usuid = uid
    ruuid = getRusAuid(uidsmap, "uids", usuid)
    if not ruuid:
      logFile.write("User with uid %r was not found in new_uids.json\n" % str(usuid))
      continue
    rupers_key = makePersKey(ruuid)

    acc.db.auid = ruauid
    acc.db.load_auid = ruauid
    acc.db.IsUSAacc = True
    acc.db.original_uid = getRusAuid(uidsmap, "uids", acc.db.original_uid)
    # Если не нашли, печально, но поставим ему туда просто uid.
    if not acc.db.original_uid:
      logFile.write(
        "User with original_uid %r was not found in new_uids.json, original_uid will be set as uid.\n" % str(
          acc.db.original_uid))
    if acc.db.guildAuid:
      usGuildAuid = acc.db.guildAuid
      ruGuildAuid = getRusAuid(guildsmap, "guildauids", acc.db.guildAuid)
      if not acc.db.guildAuid:
        logFile.write("User with us auid %r lost his guild (old guild auid=%r).\n" % (str(usauid), acc.db.guildAuid))
        acc.db.guildAuid = 0
      else:
        acc.db.guildAuid = ruGuildAuid
    ####################################################

    # 4) Конвертируем modeldata
    ####################################################
    for constructionId in MD.ConstructionsKeeper:
      construction = MD.getConstructionByID(constructionId)

      newFrList = []
      for fr in construction.FriendsInBuilding:
        ruauid = getRusAuid(auidsmap, "auids", fr)
        if not ruauid:
          logFile.write("User with us auid %r lost his friend in building (old friend auid=%r).\n" % (str(usauid), fr))
          continue
        newFrList.append(ruauid)
      for fr in xrange(0, len(construction.FriendsInBuilding)):
        construction.FriendsInBuilding.pop()
      for fr in newFrList:
        construction.FriendsInBuilding.append(fr)

    lostFriends = []
    for friendId in MD.FriendsKeeper:
      friend = MD.getSimpleFriendByID(friendId)
      ru_fr_auid = getRusAuid(auidsmap, "auids", friend.person_uid)
      if not ru_fr_auid:
        logFile.write("User with us auid %r lost his friend invite (old friend invite auid=%r).\n" % (
          str(usauid), friend.person_uid))
        lostFriends.append(friend)
        continue
      friend.person_uid = ru_fr_auid
    for friend in lostFriends:
      MD.Friends.IncomingInvites.remove(friend)

    newFrList = []
    for fr in MD.Friends.Favorites:
      ruauid = getRusAuid(auidsmap, "auids", fr)
      if not ruauid:
        logFile.write(
          "User with us auid %r lost his favourite friend (old favourite friend auid=%r).\n" % (str(usauid), fr))
      else:
        newFrList.append(ruauid)
    for fr in xrange(0, len(MD.Friends.Favorites)):
      MD.Friends.Favorites.pop()
    for fr in newFrList:
      MD.Friends.Favorites.append(fr)

    lostGuildInvites = []
    for guildInviteId in MD.GuildInvitesKeeper:
      guildInvite = MD.getGuildInviteByID(guildInviteId)
      guildInvite.person_uid = getRusAuid(auidsmap, "auids", guildInvite.person_uid)
      guildInvite.guildAuid = getRusAuid(guildsmap, "guildauids", guildInvite.guildAuid)
      if not guildInvite.person_uid or not guildInvite.guildAuid:
        logFile.write("User with us auid %r lost invite to guild.\n" % str(usauid))
        lostGuildInvites.append(guildInvite)
    for guildInvite in lostGuildInvites:
      MD.IncomingGuildInvites.remove(guildInvite)
    ####################################################

    # 5) Сохраняем acc в json и zip'ем
    ####################################################
    new_data_json = PersistentDataManager.saveData(acc, True)
    ####################################################

    # 6) Пишем кирпич в монго
    ####################################################
    mongo_reply = func2({"key": rupers_key}, {"$set": {"data": new_data_json}}, upsert=True, safe=True)
    if not mongo_reply.get("ok", None):
      sys.stdout.write("ERROR save to mongo: %r\n" % mongo_reply)
      logFile.write("ERROR save to mongo: %r\n" % mongo_reply)
      ####################################################
  logFile.close()


def fixAccDb(maxThreads=10):
  startTime = time.time()

  # Загружаем auids.json и uids.json
  # ###################################################
  print "Convert all acc.db from database amerika"
  print "Num threads:", maxThreads
  print "Load auids.json and uids.json and guildauids.json and del_us.json"

  # auidsmap = {"auids" : {"US->RU" : {}, "RU->US" : {}}}
  auidsfile = open(os.path.join(OUT_JSON_PATH, "new_auids.json"), "r")
  auidsmap = ujson.load(auidsfile)
  auidsfile.close()

  # uidsmap = {"uids" : {"US->RU" : {}, "RU->US" : {}}}
  uidsfile = open(os.path.join(OUT_JSON_PATH, "new_uids.json"), "r")
  uidsmap = ujson.load(uidsfile)
  uidsfile.close()

  # guildsmap = {"guildauids" : {"US->RU" : {}, "RU->US" : {}}}
  guildfile = open(os.path.join(OUT_JSON_PATH, "guildauids.json"), "r")
  guildsmap = ujson.load(guildfile)
  guildfile.close()

  # delusmap = {"fsn_uids": []}
  delusfile = open(os.path.join(OUT_JSON_PATH, "del_us.json"), "r")
  delusmap = ujson.load(delusfile)
  delusfile.close()

  print "Load auids.json and uids.json and guildauids.json and del_us.json OK"
  ####################################################

  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
    opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
    connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
    mongo_db = getattr(connection, "amerika", None)
    final_db = getattr(connection, opt.mongo_base, None)
    if mongo_db and final_db:
      coll = getattr(mongo_db, "pers")
      func = getattr(coll, "find")
      reply = func({"key": {"$exists": True}})
      total = reply.count()
      curIdx = 0

      coll2 = getattr(final_db, "pers")
      func2 = getattr(coll2, "update")

      print "Total acc:", total
      threads = []
      for x in range(0, maxThreads):
        cel = int(math.ceil(float(total) / maxThreads))
        start = 0 if x == 0 else cel * x + 1
        end = cel * (x + 1) + 1
        if end > total:
          end = total + 1
        slice = reply.clone()[start:end]
        thread = Thread(target=fixAccDbFunc,
                        args=(slice, final_db, auidsmap, uidsmap, guildsmap, delusmap, end - start, x))
        thread.start()
        threads.append(thread)
      for thread in threads:
        thread.join()

    else:
      print "ERROR mongo_db is None"
      exit(1)
  else:
    print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"
    exit(1)

  # Объединяем полученные логи
  ####################################################
  logText = ""
  for x in range(0, maxThreads):
    f = open(os.path.join(OUT_JSON_PATH, "fix_acc_db" + str(x) + ".log"), "r")
    logText += f.read()
    f.close()
    os.remove(os.path.join(OUT_JSON_PATH, "fix_acc_db" + str(x) + ".log"))
  logFile = open(os.path.join(OUT_JSON_PATH, "fix_acc_db.log"), "w")
  logFile.write(logText)
  logFile.close()

  endTime = time.time()
  print "Total time:", endTime - startTime
  #print "Timings:", timings


class FakeGuidGenarator(object):
  """ Заглушка, умеет только выдавать GUID-ы. """

  def __init__(self, server_id=0):
    # inc-словарик, по которому будем выдавать GUID-ы
    self.guids = IncDict()
    self.server_id = server_id

  def reset(self):
    self.guids = IncDict()

  # --------------- выдача GUID-ов -----------------
  # основываемся на том, что server_id всегда глобально уникальный
  def nextUid(self, key):
    return self.guids.inc(key)

  def nextInt64GUID(self, key):
    uid = self.nextUid(key)
    guid = (long(self.server_id) << 32) | long(uid)
    return guid


def getRusAuid(auidsmap, key, usAuid):
  if str(usAuid) not in auidsmap[key]["US->RU"]:
    return None
  return auidsmap[key]["US->RU"][str(usAuid)]


def fixRuUsGuildDataFunc(cursor, guilds_coll, final_db, auidsmap, total, logFile):
  curIdx = 0
  coll2 = getattr(final_db, "guilds")
  func2 = getattr(coll2, "update")
  guildauidsmap = {"guildauids": {"US->RU": {}, "RU->US": {}}}

  # Подменим номер следующего WS сервера, чтобы правильным образом сгенерировать guid's
  sql_options = ClassDict(SQL_CONFIG[0])
  sql_autoinc = 'SHOW TABLE STATUS LIKE "tbl_servers"'
  sql_reply = syncSqlQuery(sql_autoinc, sql_options)
  auto_inc_old = int(sql_reply[0].__getattr__("Auto_increment"))
  syncSqlCommand("INSERT INTO tbl_servers (id, name) VALUES (%d, 'test_ws')" % auto_inc_old, sql_options)
  sql_reply = syncSqlQuery(sql_autoinc, sql_options)
  auto_inc = int(sql_reply[0].__getattr__("Auto_increment"))
  syncSqlCommand("DELETE FROM tbl_servers WHERE id=%d" % auto_inc_old, sql_options)

  guids = FakeGuidGenarator()
  guids.__init__(auto_inc)
  usGuildShortInfo = {}
  for obj in cursor:

    # 1) Получаем служебную информацию о гильдии
    # ###################################################
    data_json = obj["data"]
    guild_key = obj["key"]

    if len(guild_key) == 0:
      print("ERROR bad mongo key %r\n" % guild_key)
      logFile.write("ERROR bad mongo key %r\n" % guild_key)
      continue
    # ###################################################

    # 2) Загружаем guilddata
    # ###################################################
    guilddata = GuildData()
    guilddata.load(data_json)
    guilddata.init(changeWriter=None)
    # ###################################################

    # 3) Конвертируем все auid's
    # ###################################################
    membersToRemove = []
    for memberId in guilddata.GuildMemberKeeper:
      member = guilddata.getGuildMemberByID(memberId)

      usMemberAuid = member.Person
      ruMemberAuid = getRusAuid(auidsmap, "auids", usMemberAuid)
      if ruMemberAuid:
        member.Person = ruMemberAuid
      else:
        logFile.write("User with auid %d was not found in transferring accounts and was removed from guild %r\n" % (
          usMemberAuid, guilddata.GuildAuid))
        membersToRemove.append(usMemberAuid)
    ####################################################
    for auid in membersToRemove:
      guilddata = removeGuildMember(guilddata, auid, guilds_coll, logFile)

    if not guilddata:
      continue

    investmentsToRemove = []
    for investEventId in guilddata.InvestStatisticsKeeper:
      investEvent = guilddata.getGuildInvestEventByID(investEventId)

      usMemberAuid = investEvent.auid
      ruMemberAuid = getRusAuid(auidsmap, "auids", usMemberAuid)
      if ruMemberAuid:
        investEvent.auid = member.Person = ruMemberAuid
      else:
        logFile.write(
          "User with auid %d was not found in transferring accounts and was removed from guild %r InvestStatistics\n" % (
            usMemberAuid, guilddata.GuildAuid))
        investmentsToRemove.append(investEvent)
    for investEvent in investmentsToRemove:
      guilddata.InvestStatistics.remove(investEvent)

    # 4) Конвертируем GuildAuid
    ####################################################
    usGuildAuid = guilddata.GuildAuid
    ruGuildAuid = guids.nextInt64GUID("guild_service")
    guildauidsmap["guildauids"]["US->RU"][str(usGuildAuid)] = ruGuildAuid
    guildauidsmap["guildauids"]["RU->US"][str(ruGuildAuid)] = usGuildAuid
    guilddata.GuildAuid = ruGuildAuid
    ####################################################

    # 5) Сохраняем guilddata в json
    ####################################################
    new_data_json = guilddata.save()
    ####################################################

    # 6) Пишем кирпич в монго
    ####################################################
    mongo_reply = func2({"key": "gs_" + str(ruGuildAuid)}, {"$set": {"data": new_data_json}}, upsert=True, new=True)
    if not mongo_reply.get("ok", None):
      print ("ERROR save to mongo: %r\n" % mongo_reply)
      logFile.write("ERROR save to mongo: %r\n" % mongo_reply)
    usGuildShortInfo[ruGuildAuid] = {"FullName": guilddata.GuildInfo.FullName,
                                     "ShortName": guilddata.GuildInfo.ShortName,
                                     "CreationDate": guilddata.GuildCreateTime, "GuildAuid": guilddata.GuildAuid}
    ####################################################

    curIdx += 1
    if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
      gc.collect()
    sys.stdout.write("Guilds converted: %d/%d\r" % (curIdx + 1, total))

  print "Guilds converted: %d/%d\n" % (total, total)
  # 7) Сохраняем соответствия OldGuildAuid->NewGuildAuid
  # ###################################################
  f = open(os.path.join(OUT_JSON_PATH, "guildauids.json"), "w")
  json.dump(guildauidsmap, f)
  f.close()
  # ###################################################

  return usGuildShortInfo


def fixRuUsGuildData():
  startTime = time.time()

  # Загружаем auids.json
  # ###################################################
  print "Convert all guilddata member auids from database amerika"
  print "Load copied_auids.json"
  auidsfile = open(os.path.join(OUT_JSON_PATH, "copied_auids.json"), "r")
  auidsmap = ujson.load(auidsfile)
  auidsfile.close()

  print "Load copied_auids.json OK"
  # ###################################################
  logFile = open(os.path.join(OUT_JSON_PATH, "fix_us_ru_guilds.log"), "w")

  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
    opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
    connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
    mongo_db = getattr(connection, "amerika", None)
    final_db = getattr(connection, opt.mongo_base, None)
    if mongo_db and final_db:
      coll = getattr(mongo_db, "guilds")
      func = getattr(coll, "find")
      reply = func({"key": {"$exists": True}})
      total = reply.count()

      print "Total guilds:", total
      usGuildShortInfo = fixRuUsGuildDataFunc(reply, coll, final_db, auidsmap, total, logFile)
      fixRuUsGuildNames(usGuildShortInfo, logFile)
    else:
      print "ERROR mongo_db is None"
  else:
    print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"

  logFile.close()
  endTime = time.time()
  print "Total time:", endTime - startTime
  # print "Timings:", timings


def checkForDup(allGuilds, guilddata, renamedGuilds):
  shortDup = {"isDup": False, "CreationDate": 0, "GuildAuid": 0}
  fullDup = {"isDup": False, "CreationDate": 0, "GuildAuid": 0}
  for item in allGuilds.values():
    if guilddata.GuildInfo.FullName.lower() == item["FullNameNew"].lower():
      if guilddata.GuildAuid != item["GuildAuid"] and not guilddata.GuildAuid in renamedGuilds:
        fullDup["isDup"] = True
        fullDup["CreationDate"] = item.get("CreationDate") or None
        fullDup["GuildAuid"] = item["GuildAuid"]

    if guilddata.GuildInfo.ShortName.lower() == item["ShortNameNew"].lower():
      if guilddata.GuildAuid != item["GuildAuid"] and not guilddata.GuildAuid in renamedGuilds:
        shortDup["isDup"] = True
        shortDup["CreationDate"] = item.get("CreationDate") or None
        shortDup["GuildAuid"] = item["GuildAuid"]

    if fullDup["isDup"] and shortDup["isDup"]:
      break

  return shortDup, fullDup


def getNextFullName(oldName, allGuilds):
  curIdx = 1
  isDuplicated = True
  newName = ""
  oldNameUnicode = unicode(oldName, 'utf8')
  while isDuplicated:
    isDuplicated = False
    if len(oldNameUnicode) + len(str(curIdx)) > MAX_FULLNAME_SIZE:
      newName = (oldNameUnicode[:MAX_FULLNAME_SIZE - len(str(curIdx))] + unicode(curIdx)).encode('utf8')
    else:
      newName = (oldNameUnicode + unicode(curIdx)).encode('utf8')

    for item in allGuilds.values():
      if newName.lower() == item["FullNameNew"].lower():
        isDuplicated = True
        curIdx += 1
        break
  return newName


def getNextShortName(oldName, allGuilds):
  curIdx = 1
  isDuplicated = True
  newName = ""
  oldNameUnicode = unicode(oldName, 'utf8')
  while isDuplicated:
    isDuplicated = False
    if len(oldNameUnicode) + len(str(curIdx)) > MAX_SHORTNAME_SIZE:
      newName = oldNameUnicode[:MAX_SHORTNAME_SIZE - len(str(curIdx))].encode('utf8') + str(curIdx)
    else:
      newName = oldNameUnicode.encode('utf8') + str(curIdx)

    for item in allGuilds.values():
      if newName.lower() == item["ShortNameNew"].lower():
        isDuplicated = True
        curIdx += 1
        break
  return newName


def updateGuildShortNameInfo(coll, allGuilds, guilddata, updateAuidsList):
  allGuilds[guilddata.GuildAuid].update({"ShortNameOld": guilddata.GuildInfo.ShortName,
                                         "ShortNameNew": getNextShortName(guilddata.GuildInfo.ShortName, allGuilds)})
  args = {"FullName": guilddata.GuildInfo.FullName, "ShortName": guilddata.GuildInfo.ShortName,
          "GuildAuid": guilddata.GuildAuid}
  coll.remove(args)
  guilddata.GuildInfo.ShortName = allGuilds[guilddata.GuildAuid]["ShortNameNew"]
  for memberId in guilddata.GuildMemberKeeper:
    member = guilddata.getGuildMemberByID(memberId)
    updateAuidsList[str(member.Person)] = guilddata.GuildInfo.ShortName
  args["ShortName"] = guilddata.GuildInfo.ShortName
  coll.insert(args)
  return guilddata, updateAuidsList


# Принимает один пустой параметр, чтобы не плодить кода в функциях по вызову updateGuild...Info.
def updateGuildFullNameInfo(coll, allGuilds, guilddata, uselessParamForSimilarity):
  allGuilds[guilddata.GuildAuid].update({"FullNameOld": guilddata.GuildInfo.FullName,
                                         "FullNameNew": getNextFullName(guilddata.GuildInfo.FullName, allGuilds)})
  args = {"FullName": guilddata.GuildInfo.FullName, "ShortName": guilddata.GuildInfo.ShortName,
          "GuildAuid": guilddata.GuildAuid}
  coll.remove(args)
  guilddata.GuildInfo.FullName = allGuilds[guilddata.GuildAuid]["FullNameNew"]
  args["FullName"] = guilddata.GuildInfo.FullName
  coll.insert(args)
  return guilddata, uselessParamForSimilarity


def rewriteDuplicatedInfo(dupRecord, guilddata, allGuilds, renamedGuilds, updateAuidsList, func_update, func_find_one,
                          updateFunc, coll, logFile):
  if not dupRecord["CreationDate"]:
    guildInfo_reply = func_find_one({"key": "gs_" + str(dupRecord["GuildAuid"])})
    if guildInfo_reply:
      # Загрузим данные о гильдии, поскольку она нам ещё не попадалась в спике
      data_json = guildInfo_reply["data"]
      guild_key = guildInfo_reply["key"]

      if guild_key == 0:
        sys.stdout.write("ERROR bad key %r\n" % guild_key)
        return
      newGuilddata = GuildData()
      newGuilddata.load(data_json)
      newGuilddata.init(changeWriter=None)
      dupRecord["CreationDate"] = newGuilddata.GuildCreateTime
    else:
      logFile.write("No GuildData found for guild with auid %r\n" % dupRecord["GuildAuid"])
      dupRecord["CreationDate"] = time.time()
  if dupRecord["CreationDate"] < guilddata.GuildCreateTime:
    # Переименовываем американскую гильдию, т.к. американские гильдии в конце списка и guilddata - американская
    guilddata, updateAuidsList = updateFunc(coll, allGuilds, guilddata, updateAuidsList)
    renamedGuilds[guilddata.GuildAuid] = allGuilds[guilddata.GuildAuid]
  else:
    # Переименовываем русскую гильдию, меняем флаг "isDup", чтобы потом отдельно сохранить данные об американской гильдии
    dupRecord["isDup"] = False
    gd_reply = func_find_one({"key": "gs_" + str(dupRecord["GuildAuid"])})
    ru_gd_json = gd_reply["data"]
    ru_guilddata = GuildData()
    ru_guilddata.load(ru_gd_json)
    ru_guilddata.init(changeWriter=None)
    ru_guilddata, updateAuidsList = updateFunc(coll, allGuilds, ru_guilddata, updateAuidsList)
    renamedGuilds[ru_guilddata.GuildAuid] = allGuilds[ru_guilddata.GuildAuid]
    new_ru_data_json = ru_guilddata.save()
    # Перезаписываем изменённую информацию о русской гильдии
    mongo_reply = func_update({"key": "gs_" + str(ru_guilddata.GuildAuid)}, {"$set": {"data": new_ru_data_json}},
                              upsert=False, multi=False)
    if mongo_reply:
      if not mongo_reply.get("ok", None):
        sys.stdout.write("ERROR save to mongo: %r\n" % mongo_reply)
  return dupRecord


def fixRuUsGuildNames(usGuildShortInfo, logFile):
  startTime = time.time()
  curIdx = 0
  # ###################################################
  print "Convert all guilddata short and fill names from database amerika"
  # ###################################################

  allGuilds = {}
  # Список переименованных гильдий дл GM'ов
  renamedGuilds = {}
  # Список auid'ов, которым надо будет поменять guildShortName в SA
  updateAuidsList = {}

  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
    opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
    connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
    guilds_db = getattr(connection, opt.mongo_base, None)
    if guilds_db:
      coll = getattr(guilds_db, "guilds")
      func_find = getattr(coll, "find")
      func_update = getattr(coll, "update")
      func_find_one = getattr(coll, "find_one")

      # Заведём список имён всех гильдий
      short_names_reply = func_find({"ShortName": {"$exists": True}})
      for guildShortInfo in short_names_reply:
        allGuilds[guildShortInfo["GuildAuid"]] = {"ShortNameOld": guildShortInfo["ShortName"],
                                                  "ShortNameNew": guildShortInfo["ShortName"],
                                                  "FullNameOld": guildShortInfo["FullName"],
                                                  "FullNameNew": guildShortInfo["FullName"],
                                                  "GuildAuid": guildShortInfo["GuildAuid"]}

      for guildShortInfo in usGuildShortInfo.values():
        allGuilds[guildShortInfo["GuildAuid"]] = {"ShortNameOld": guildShortInfo["ShortName"],
                                                  "ShortNameNew": guildShortInfo["ShortName"],
                                                  "FullNameOld": guildShortInfo["FullName"],
                                                  "FullNameNew": guildShortInfo["FullName"],
                                                  "GuildAuid": guildShortInfo["GuildAuid"],
                                                  "CreationDate": guildShortInfo["CreationDate"]}
      reply = func_find({"key": {"$exists": True}})
      total = reply.count()

      print "Total guilds:", total
      for guild in reply:
        # 1) Получаем служебную информацию о гильдии
        # ###################################################
        data_json = guild["data"]
        guild_key = guild["key"]

        if guild_key == 0:
          sys.stdout.write("ERROR bad key %r\n" % guild_key)
          continue
        # ###################################################

        # 2) Загружаем guilddata
        # ###################################################
        guilddata = GuildData()
        guilddata.load(data_json)
        guilddata.init(changeWriter=None)
        ####################################################

        shortDup, fullDup = checkForDup(allGuilds, guilddata, renamedGuilds)

        # 3) Проверяем дубликаты
        ####################################################
        if shortDup["isDup"]:
          shortDup = rewriteDuplicatedInfo(shortDup, guilddata, allGuilds, renamedGuilds, updateAuidsList, func_update,
                                           func_find_one, updateGuildShortNameInfo, coll, logFile)
        if fullDup["isDup"]:
          fullDup = rewriteDuplicatedInfo(fullDup, guilddata, allGuilds, renamedGuilds, updateAuidsList, func_update,
                                          func_find_one, updateGuildFullNameInfo, coll, logFile)
        ####################################################

        # 5) Сохраняем guilddata в json
        ####################################################
        if shortDup["isDup"] or fullDup["isDup"]:
          new_data_json = guilddata.save()

          mongo_reply = func_update({"key": "gs_" + str(guilddata.GuildAuid)}, {"$set": {"data": new_data_json}},
                                    upsert=False, multi=False)
          if mongo_reply:
            if not mongo_reply.get("ok", None):
              sys.stdout.write("ERROR save to mongo: %r\n" % mongo_reply)


        # Параллельно заполним краткую информацию о гильдиях в монго
        short_name_reply = func_find_one({"GuildAuid": guilddata.GuildAuid})
        if short_name_reply:
          coll.remove(short_name_reply)
        args = {"FullName": allGuilds[guilddata.GuildAuid]["FullNameNew"],
                "ShortName": allGuilds[guilddata.GuildAuid]["ShortNameNew"],
                "GuildAuid": allGuilds[guilddata.GuildAuid]["GuildAuid"]}
        coll.insert(args)

        curIdx += 1
        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
          gc.collect()
        sys.stdout.write("Fix guildnames for: %r/%r\r" % (curIdx, total))

      print "Fix guildnames for: %r/%r\n" % (total, total)
      # 6) Сохраняем соответствия OldGuildAuid->NewGuildAuid
      # ###################################################
      f = open(os.path.join(OUT_JSON_PATH, "renamedGuilds.json"), "w")
      json.dump(renamedGuilds, f)
      f.close()

      f = open(os.path.join(OUT_JSON_PATH, "new_gsn.json"), "w")
      json.dump(updateAuidsList, f)
      f.close()
      # ###################################################
    else:
      print "ERROR mongo_db is None"
  else:
    print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"

  endTime = time.time()
  print "Total time:", endTime - startTime


def getTotalGoldAmount(billingDict, auid):
  for billingInfo in billingDict:
    if str(auid) in billingInfo.keys():
      return billingInfo[str(auid)]
  return 0


def parseDuplicatedAuids():
  startTime = time.time()

  # Загружаем sa_dups.json
  # ###################################################
  print "Sort all duplicated auids from database amerika"
  print "Load sa_dups.json"
  auidsfile = open(os.path.join(OUT_JSON_PATH, "sa_dups.json"), "r")
  duplicatesMap = ujson.load(auidsfile)
  auidsfile.close()
  # Загружаем sa_copy.json
  # ###################################################
  copyAuidsfile = open(os.path.join(OUT_JSON_PATH, "sa_copy.json"), "r")
  copyMap = ujson.load(copyAuidsfile)
  copyAuidsfile.close()
  # Заведём файл логов
  # ###################################################
  logFile = open(os.path.join(OUT_JSON_PATH, "find_duplicated_accs.log"), "w")
  # Загружаем ru_billing.json (информация о золоте русских дублируемых акков)
  # ###################################################
  ru_billing_file = open(os.path.join(OUT_JSON_PATH, "ru_billing.json"), "r")
  ru_goldInfo = ujson.load(ru_billing_file)
  ru_billing_file.close()
  # Загружаем us_billing_file.json (информация о золоте амеркианских дублируемых акков)
  # ###################################################
  us_billing_file = open(os.path.join(OUT_JSON_PATH, "us_billing.json"), "r")
  us_goldInfo = ujson.load(us_billing_file)
  us_billing_file.close()
  # Отсортируем дублируемые аккаунты
  ruDeleteList = {"fsn_uids": []}
  usDeleteList = {"fsn_uids": []}
  copyList = {}
  goldList = []
  resolvedDups = []

  print "Load sa_dups.json, ru_billing.json, us_billing.json OK"
  ####################################################
  ru_sql_db = SyncSqlManager(ClassDict(SQL_CONFIG[0]))
  ru_sql_db.openConnection()
  us_sql_db = SyncSqlManager(ClassDict(SQL_CONFIG[1]))
  us_sql_db.openConnection()

  # Подгрузим StaticData, чтобы подсчитать уровень замка
  ####################################################
  SD = StaticData("../xdb/ExportedSocialData.xml", None)

  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
    opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
    try:
      connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
    except:
      print "Can't connect to Mongo database"
      exit(1)

    us_db = getattr(connection, "amerika", None)
    ru_db = getattr(connection, opt.mongo_base, None)
    if us_db and ru_db:
      ru_coll_ = getattr(ru_db, "pers")
      ru_find_one = getattr(ru_coll_, "find_one")
      us_coll = getattr(us_db, "pers")
      us_find_one = getattr(us_coll, "find_one")
      curIdx = 0
      # Начинаем сортировать дубликаты акков
      for duplicateAcc in duplicatesMap:
        maxFameAcc = {"auid": 0, "uid": 0, "login": "", "level": 0, "location": "", "accCreationTime": 0}
        # Если вдруг мы не нашли каких-то данны, поменяем флаг и пропустим этот аккаунт.
        skipAcc = False
        for accInfo in duplicateAcc:
          if accInfo["locale"] == "RU":
            uid_reply = ru_sql_db.syncSqlQuery("SELECT id FROM tbl_login WHERE login='%s'" % accInfo["login"])
            mongoRequest = ru_find_one
          else:
            uid_reply = us_sql_db.syncSqlQuery("SELECT id FROM tbl_login WHERE login='%s'" % accInfo["login"])
            mongoRequest = us_find_one
          if uid_reply:
            accInfo["uid"] = uid_reply[0]["id"]
            reply = mongoRequest({"key": "data_" + str(accInfo["uid"])})
          else:
            # Не нашли этого человека в SQL. Скорее всего, он просто не заходил в игру, но успел зарегистрироваться.
            if accInfo["ghost"]:
              logLevel = "INFO "
            else:
              logLevel = "WARNING "
            logFile.write(
              logLevel + "tbl_login SQL row was not found for account with login %r, locale=%r, total number of duplicated accs for user=%r\n" % \
              (accInfo["login"], accInfo["locale"], len(duplicateAcc)))
            continue

          if reply and reply.get("data", None):
            acc = PersistentDataManager.newSimpleDataAcc(reply["data"])
            MD = ModelData()
            MD.load(acc.model)
            MD.init(changeWriter=None)
            castleLvl = SD.getFameLevel(MD.LordInfo.Fame)
            if castleLvl > maxFameAcc["level"] or (
                    castleLvl == maxFameAcc["level"] and acc.db.registration_date < maxFameAcc["accCreationTime"]):
              maxFameAcc["uid"] = uid_reply[0]["id"]
              maxFameAcc["auid"] = accInfo["auid"]
              maxFameAcc["login"] = accInfo["login"]
              maxFameAcc["level"] = castleLvl
              maxFameAcc["location"] = accInfo["locale"]
              maxFameAcc["accCreationTime"] = acc.db.registration_date
          else:
            logFile.write("ModelData was not found for uid %r, login %r\n" % (uid_reply[0], accInfo["login"]))
            continue
        # Проверим, жив ли хоть 1 аккаунт
        if not maxFameAcc["auid"]:
          # Если нет, считаем, что главный - первый русский.
          for accInfo in duplicateAcc:
            if accInfo["locale"] == "RU":
              maxFameAcc["auid"] = accInfo["auid"]
              maxFameAcc["login"] = accInfo["login"]
              maxFameAcc["location"] = accInfo["locale"]
              continue
          logFile.write("WARNING, SQL information was not found for all duplicates from %r\n" % duplicateAcc)
        # Нашли акк с наибольшим уровнем замка
        totalGoldToAdd = 0
        dupAccs = []
        for accInfo in duplicateAcc:
          # Все остальные акки-дубликаты в список для удаления
          if accInfo["auid"] != maxFameAcc["auid"]:
            dupAccs.append({"auid": accInfo["auid"], "login": accInfo["login"], "location": accInfo["locale"]})
            # Русские аккаунты потом надо удалить с основного сервера
            if accInfo["locale"] == "RU":
              if "uid" in accInfo:
                ruDeleteList["fsn_uids"].append(accInfo["uid"])
              totalGoldToAdd += getTotalGoldAmount(ru_goldInfo, accInfo["auid"])
            else:
              if "uid" in accInfo:
                usDeleteList["fsn_uids"].append(accInfo["uid"])
              totalGoldToAdd += getTotalGoldAmount(us_goldInfo, accInfo["auid"])
          else:
            # Если у американского акка уровень замка больше, то занесём его в список для копирования
            if accInfo["locale"] == "US":
              copyList[md5(accInfo["login"])] = accInfo["auid"]
        goldList.append({"auid": maxFameAcc["auid"], "gold": totalGoldToAdd, "locale": maxFameAcc["location"]})
        resolvedDups.append(
          {"main": {"auid": maxFameAcc["auid"], "login": maxFameAcc["login"], "location": maxFameAcc["location"]},
           "dups": dupAccs})

        # Почистим память
        curIdx += 1
        if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
          gc.collect()
    else:
      print "ERROR mongo_db is None"
  else:
    print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"

  # Добавим логины и auid'ы из sa_copy.json в ss_copy, чтобы переносить их в п.7
  for accInfo in copyMap:
    copyList[md5(accInfo[1])] = accInfo[0]
  # Сохраняем полученную информацию по дубликатам
  ####################################################
  f = open(os.path.join(OUT_JSON_PATH, "del_ru.json"), "w")
  json.dump(ruDeleteList, f)
  f.close()
  f = open(os.path.join(OUT_JSON_PATH, "del_us.json"), "w")
  json.dump(usDeleteList, f)
  f.close()
  f = open(os.path.join(OUT_JSON_PATH, "add_gold.json"), "w")
  json.dump(goldList, f)
  f.close()
  f = open(os.path.join(OUT_JSON_PATH, "ss_copy.json"), "w")
  json.dump(copyList, f)
  f.close()
  f = open(os.path.join(OUT_JSON_PATH, "dup_resolve_sa.json"), "w")
  json.dump(resolvedDups, f)
  f.close()
  ####################################################
  logFile.close()
  endTime = time.time()
  print "Total time:", endTime - startTime
  #print "Timings:", timings


def checkMissedSQLUsers(slice, us_find_one, usAuids, total_sql, threadId):
  curIdx = 0
  inSQLNotInSA = []
  inSQLNotInMongo = []
  id = 0
  login = ""
  # sys.stdout.write ("slice size=%d, usAuids size=%d\n" % (len(slice), len(usAuids)))
  for accInfo in slice:
    id = accInfo.get("id")
    login = accInfo.get("login")
    if id and login:
      if not usAuids.has_key(md5(login)):
        inSQLNotInSA.append({str(id): login})
      mongo_reply = us_find_one({"key": "data_" + str(id)})
      if not mongo_reply:
        inSQLNotInMongo.append({str(id): login})
    curIdx += 1
    if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
      sys.stdout.write("SQL accs in Mongo and SA checking: %d percents complete\r" % toint(curIdx * 100 / total_sql))
      # gc.collect()

  # Сохраняем полученную информацию по Mongo потеряшкам
  # ###################################################
  f = open(os.path.join(OUT_JSON_PATH, "inSQLNotInSA" + str(threadId) + ".json"), "w")
  json.dump(inSQLNotInSA, f)
  f.close()

  # Сохраняем полученную информацию по Mongo потеряшкам
  # ###################################################
  f = open(os.path.join(OUT_JSON_PATH, "inSQLNotInMongo" + str(threadId) + ".json"), "w")
  json.dump(inSQLNotInMongo, f)
  f.close()


def createTotalList(auidsPath):
  lostAuidsFile = open(auidsPath, "r")
  lostAuids = ujson.load(lostAuidsFile)
  lostAuidsFile.close()
  os.remove(auidsPath)
  return lostAuids


def checkAllSAAuids(maxThreads):
  startTime = time.time()
  print maxThreads
  # Загружаем sa_copy.json
  # ###################################################
  print "Check all auids from US Social aggregator"
  print "Load sa_copy.json"
  auidsfile = open(os.path.join(OUT_JSON_PATH, "sa_copy.json"), "r")
  auidsList = ujson.load(auidsfile)
  auidsfile.close()
  # Заведём файл логов
  # ###################################################
  logFile = open(os.path.join(OUT_JSON_PATH, "check_all_sa_auids.log"), "w")
  # Загружаем sa_dups.json (информация о дублируемых аккаунтах)
  # ###################################################
  dupAuidsfile = open(os.path.join(OUT_JSON_PATH, "sa_dups.json"), "r")
  dupAuidsList = ujson.load(dupAuidsfile)
  dupAuidsfile.close()

  us_sql_db = SyncSqlManager(ClassDict(SQL_CONFIG[1]))
  us_sql_db.openConnection()

  sqlLosts = []
  usAuids = {}

  # Проверим, кто из пользователей отсутствует в SQL
  curIdx = 0
  for accInfo in auidsList:
    usAuids[md5(accInfo[1])] = accInfo[0]
    uid_reply = us_sql_db.syncSqlQuery("SELECT id FROM tbl_login WHERE login='%s'" % accInfo[1])
    if not uid_reply:
      sqlLosts.append(accInfo)
      # print "SQL data for auid %r, login %r was not found" % (accInfo[0], accInfo[1])
      logFile.write("SQL data for auid %r, login %r was not found\n" % (accInfo[0], accInfo[1]))
    curIdx += 1
    if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
      sys.stdout.write("Single SA accs in SQL checking: %d percents complete\r" % toint(curIdx * 100 / len(auidsList)))
  curIdx = 0
  print ("Single SA accs in SQL checking: 100 percents complete\n")
  for duplicateAcc in dupAuidsList:
    for accInfo in duplicateAcc:
      if accInfo["locale"] == "US":
        usAuids[md5(accInfo["login"])] = accInfo["auid"]
        uid_reply = us_sql_db.syncSqlQuery("SELECT id FROM tbl_login WHERE login='%s'" % accInfo["login"])
        if not uid_reply:
          sqlLosts.append(accInfo)
          # print "SQL data for auid %r, login %r was not found" % (accInfo["auid"], accInfo["login"])
          logFile.write("SQL data for auid %r, login %r was not found\n" % (accInfo["auid"], accInfo["login"]))
    curIdx += 1
    if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
      sys.stdout.write(
        "Duplicated SA accs in SQL checking: %d percents complete\r" % toint(curIdx * 100 / len(dupAuidsList)))
  print ("Duplicated SA accs in SQL checking: 100 percents complete\n")
  # Сохраняем полученную информацию по SQL потеряшкам
  # ###################################################
  f = open(os.path.join(OUT_JSON_PATH, "inSANotInSQL.json"), "w")
  json.dump(sqlLosts, f)
  f.close()

  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
    opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
    try:
      connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
    except:
      print "Can't connect to Mongo database"
      exit(1)

  us_db = getattr(connection, "amerika", None)
  if us_db:
    us_coll = getattr(us_db, "pers")
    us_find_one = getattr(us_coll, "find_one")
    us_find = getattr(us_coll, "find")
  else:
    print "Can't connect to Mongo database\n"
    exit(1)
  curIdx = 0

  #
  uid_reply = us_sql_db.syncSqlQuery("SELECT id, login FROM tbl_login")
  total_sql = len(uid_reply)
  print "Total amount of accounts in SQL %r\n" % total_sql

  threads = []
  for x in range(0, maxThreads):
    cel = int(math.ceil(float(total_sql) / maxThreads))
    start = 0 if x == 0 else cel * x + 1
    end = cel * (x + 1) + 1
    if end > total_sql:
      end = total_sql + 1
    slice = uid_reply[start:end]
    thread = Thread(target=checkMissedSQLUsers, args=(slice, us_find_one, usAuids, end - start, x))
    thread.start()
    threads.append(thread)
  for thread in threads:
    thread.join()

  print ("SQL accs in Mongo and SA checking: 100 percents complete\n")
  # Объединяем полученную информацию по потеряшкам
  # ###################################################
  inSQLNotInMongo = []
  inSQLNotInSA = []
  for x in range(0, maxThreads):
    inSQLNotInSA.append(createTotalList(os.path.join(OUT_JSON_PATH, "inSQLNotInSA" + str(x) + ".json"), ))
    inSQLNotInMongo.append(createTotalList(os.path.join(OUT_JSON_PATH, "inSQLNotInMongo" + str(x) + ".json"), ))


  # Если надо проверить, кто из Mongo отсутствует в SA
  #reply = us_find({"key" : {"$exists" : True}})
  #total = reply.count()
  #print "Total amount of accounts in Mongo %r\n" % total
  #saLosts = []
  ## Проверим, кто из пользователей отсутствует в mongo
  #for obj in reply:
  #    # 1) Получаем служебную информацию об акке
  #    ####################################################
  #    data_json = obj["data"]
  #    pers_key = obj["key"]

  #    key_coll = pers_key.split("_")
  #    if len(key_coll) == 2:
  #        prefix = key_coll[0]
  #        uid = long(key_coll[1])
  #    else:
  #        sys.stdout.write("ERROR bad key %r\n" % pers_key)
  #        continue
  #    ####################################################

  #   # 2) Загружаем acc
  #    ####################################################
  #    acc = PersistentDataManager.newSimpleDataAcc(data_json)
  #    MD = ModelData()
  #    MD.load(acc.model)
  #    MD.init(changeWriter=None)
  #    ####################################################
  #    if not str(acc.db.auid) in usAuids.keys():
  #        saLosts.append(accInfo)
  #        login = str(acc.db.snid) + '#' + str(acc.db.snuid)
  #        #print "SA data for auid %r, login %r was not found" % (acc.db.auid, login)
  #        logFile.write("SA data for auid %r, login %r was not found\n" % (acc.db.auid, login))
  #    else:
  #        del usAuids[str(acc.db.auid)]
  #    # Почистим память
  #    curIdx += 1
  #    if curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
  #        sys.stdout.write ("Mongo checking: %d percents complete\r" % toint(curIdx*100/total))
  #        gc.collect()
  #print "Mongo checking: 100% percents complete"
  #if len(usAuids):
  #    # Сохраняем полученную информацию по Mongo потеряшкам
  #    ####################################################
  #    f = open(os.path.join(OUT_JSON_PATH, "lost_US_mongo_users.json"), "w")
  #    json.dump(usAuids, f)
  #    f.close()

  if len(inSQLNotInSA):
    # Сохраняем полученную информацию по Mongo потеряшкам
    ####################################################
    f = open(os.path.join(OUT_JSON_PATH, "inSQLNotInSA.json"), "w")
    json.dump(inSQLNotInSA, f)
    f.close()

  if len(inSQLNotInMongo):
    # Сохраняем полученную информацию по Mongo потеряшкам
    ####################################################
    f = open(os.path.join(OUT_JSON_PATH, "inSQLNotInMongo.json"), "w")
    json.dump(inSQLNotInMongo, f)
    f.close()

  logFile.close()
  endTime = time.time()
  print "Total time:", endTime - startTime

# ########## uniqueNicks

_latin = u'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
_latlower = dict((ord(c), ord(c.lower())) for c in _latin)


def _find_dup_nicks(db, logFile):
  allNicks = {}
  for row in db.syncSqlQuery("SELECT id, nick FROM tbl_nick"):
    key = row['nick'].translate(_latlower)
    r = {'uid': row['id'], 'nick': row['nick']}  # make clear dict, to be free from any row type magic
    if key in allNicks:
      allNicks[key].append(r)
    else:
      allNicks[key] = [r]
  logFile.write("%d duplicated nicks are found\n" % len([v for v in allNicks.itervalues() if len(v) > 1]))
  return allNicks


def _load_acc_data(pers, user, logFile):
  user['key'] = 'data_%d' % user['uid']
  mongo_reply = pers.find_one({'key': user['key']})
  errmsg = ''
  if not mongo_reply:
    errmsg = "ERROR: account with uid %s not found in mongo\n" % user['uid']
  elif (type(mongo_reply) != dict) or ('data' not in mongo_reply):
    errmsg = "ERROR: no 'data' in a mongo reply for account with uid %s\nReply: %r" % (user['uid'], mongo_reply)
  else:
    user['acc'] = PersistentDataManager.newSimpleDataAcc(mongo_reply['data'])
    user['reg'] = user['acc'].db.registration_date
    return
  logFile.write(errmsg)
  user['acc'] = None
  user['reg'] = 0x7fffffff


def _rename_in_mongo(pers, key, acc, newnick, config_free_changes, logFile):
  acc.db.nick = newnick
  acc.db.nickChanged = min(acc.db.nickChanged - 1, config_free_changes - 1)
  new_data_json = PersistentDataManager.saveData(acc, True)
  mongo_reply = pers.update({"key": key}, {"$set": {"data": new_data_json}}, safe=True)
  if not mongo_reply.get("ok", None):
    logFile.write("ERROR save to mongo: %r\n" % mongo_reply)
    logFile.close()
    exit(1)


def _rename_in_sql(db, uid, nick, logFile):
  try:
    db.db.execute("UPDATE tbl_nick SET nick = %s WHERE id = %s", nick, uid)
  except Exception:
    logFile.write("Error renaming user in tbl_nick:\n")
    exstr = printException(sys.exc_info())
    logFile.write(exstr)
    err(exstr)
    logFile.close()
    exit(1)


def uniqueNicks():
  ru_sql_db = SyncSqlManager(ClassDict(SQL_CONFIG[0]))
  ru_sql_db.openConnection()
  opt = ClassDict(MONGO_CONFIG[0])
  try:
    connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
  except:
    print "Can't connect to Mongo database"
    exit(1)
  ru_db = getattr(connection, opt.mongo_base, None)
  if ru_db is None:
    print "No mongo databse %s found" % opt.mongo_base
    exit(1)
  config_free_changes = MultiConfig().getMainConfig().FREE_NICK_CHANGES
  logFile = codecs.open(os.path.join(OUT_JSON_PATH, "uniqie_nicks.log"), "w", encoding='utf8')
  pers = ru_db.pers
  allNicks = _find_dup_nicks(ru_sql_db, logFile)
  dups = dict((k, v) for k, v in allNicks.iteritems() if len(v) > 1)
  # have to make dups a separate var since we need to change allNicks during the loop
  NN = 1
  renames = dict()
  for users in dups.itervalues():
    # user is dict of 'uid' and 'nick'
    for user in users:
      _load_acc_data(pers, user, logFile)
    skip = True
    for user in sorted(users, key=lambda d: d['reg']):
      if skip:
        skip = False
        continue
      while True:
        num = str(NN)
        NN += 1
        newnick = user['nick'][0:(32 - len(num))] + num
        newnick_key = newnick.translate(_latlower)
        if newnick_key not in allNicks:
          allNicks[newnick_key] = None  # need no value, just key existance
          break
      logFile.write("Renaming user '%s' (auid %s) to '%s'\n" % (
        user['nick'], user['acc'].db.auid if user['acc'] else '<UNKNOWN>', newnick))
      if user['acc']:
        _rename_in_mongo(pers, user['key'], user['acc'], newnick, config_free_changes, logFile)
        renames[user['acc'].db.auid] = newnick
      _rename_in_sql(ru_sql_db, user['uid'], newnick, logFile)
    users[:] = []
  f = open(os.path.join(OUT_JSON_PATH, "new_nick.json"), "w")
  json.dump(renames, f)
  f.close()
  logFile.close()


# ########## uniqueNicks end

# ########## fixPwcAuids

def fixPwcAuids():
  ru_sql_db = SyncSqlManager(ClassDict(SQL_CONFIG[0]))
  ru_sql_db.openConnection()

  with open(os.path.join(OUT_JSON_PATH, 'pwc_auids_update.json'), "r") as newAuidsFile:
    newAuids = ujson.load(newAuidsFile)

  with open(os.path.join(OUT_JSON_PATH, "fix_pwc_auids.log"), "w") as logFile:
    logFile.write("%d auid updates found\n" % len(newAuids))
    for snuid, auid in newAuids.iteritems():
      rows = ru_sql_db.syncSqlQuery("SELECT auid FROM tbl_pwconnect WHERE pwc_snuid = %s LIMIT 1", snuid)
      if not rows:
        logFile.write("ERROR: PWC account with snuid %s not found!\n" % snuid)
        continue
      logFile.write("Updating auid %s -> %s for pwc_snuid %s\n" % (rows[0]['auid'], auid, snuid))
      if rows[0]['auid'] == auid:
        logFile.write("WARNING: the new auid %s for snuid %s is equal to the old one!\n" % (auid, snuid))
        continue
      upadted = 0
      try:
        updated = ru_sql_db.db.execute_rowcount("UPDATE tbl_pwconnect SET auid = %s WHERE pwc_snuid = %s", auid, snuid)
      except Exception:
        exstr = printException(sys.exc_info())
        logFile.write(exstr)
        err(exstr)
        logFile.close()
        exit(1)
      if not updated:
        logFile.write("ERROR: no rows updated!\n")
      elif updated > 1:
        logFile.write("WARNING: Too many rows (%s) updated!\n" % (updated,))


# ########## fixPwcAuids end


def removeGuildMember(guildData, member_auid, coll, logFile, highLeveledGuilds=None):
  member = guildData.findMemberByAuid(member_auid)
  if not member:
    # print("removeGuildMember failed: cannot find member %d in guild %d" % (member_auid, guildData.GuildAuid))
    logFile.write("removeGuildMember failed: cannot find member %d in guild %d\n" % (member_auid, guildData.GuildAuid))
    return None

  # пшел вон
  memberID = member.getID()
  guildData.Members.remove(member)
  guildAuid = guildData.GuildAuid
  guildData.GuildMemberKeeper.remove(memberID)
  print "highLeveledGuilds %r" % highLeveledGuilds
  if highLeveledGuilds != None:
    # Проверим, какого уровня наш клан
    iDict = ClassDict()
    iDict.Config = MultiConfig()
    iDict.SD = StaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig())
    level = iDict.SD.getGuildLevel(guildData.GuildLevelInfo.Experience)
    if level >= 19:
      highLeveledGuilds[guildData.GuildInfo.FullName] = guildData.GuildAuid
  # Уберём удаляемый акк из статистики
  for investEventId in guildData.InvestStatisticsKeeper:
    investEvent = guildData.getGuildInvestEventByID(investEventId)
    if investEvent.auid == member_auid:
      guildData.InvestStatisticsKeeper.remove(investEventId)
  # Найдём нового владельца, если мы удаляем хозяина гильдии
  if guildData.Owner.Person == member_auid:
    #не командир ты нам больше
    guildData.Owner = None
    newOwner = None
    maxRating = 0.0
    #вакансия открыта, ищем нового повелителя
    for gmId in guildData.Members.keys():
      mem = guildData.getGuildMemberByID(gmId)

      avrRating = sum(mem.Ratings) / float(len(mem.Ratings))

      if not newOwner or (mem.IsOfficer and not newOwner.IsOfficer) or (
              mem.IsOfficer == newOwner.IsOfficer and maxRating < avrRating):
        newOwner = mem
        maxRating = avrRating

    if newOwner:
      #да здравствует новый король
      newOwner.IsOfficer = True
      guildData.Owner = newOwner
    else:
      #если, уходя, вы оказались последним, гасите свет
      admin_guilds.deleteShortInfo(guildAuid, coll)
      admin_guilds.deleteGuildData(guildAuid, coll)
      print "Guild with auid %d was removed\n" % guildData.GuildAuid
      logFile.write("Guild with auid %d was removed\n" % guildData.GuildAuid)
      return None

  # Если хоть кто-то в гильдии остался жив, сохраним информацию об этом
  func_update = getattr(coll, "update")
  save_reply = func_update({"key": "gs_" + str(guildData.GuildAuid)}, {"$set": {"data": guildData.save()}},
                           upsert=False, multi=False)
  if save_reply:
    if not save_reply.get("ok", None):
      sys.stdout.write("ERROR save to mongo: %r\n" % save_reply)
  return guildData


def deleteMongoAccounts(duplicatesMap, opt, db_name, highLevelGuilds, logFile):
  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
    connection = pymongo.Connection(opt.mongo_addr, opt.mongo_port)
    mongo_db = getattr(connection, db_name, None)
    if mongo_db:
      collPers = getattr(mongo_db, "pers")
      collGuilds = getattr(mongo_db, "guilds")
      func_find_one_guild = getattr(collGuilds, "find_one")
      func_find_one_pers = getattr(collPers, "find_one")
      # Удалим все лишние аккаунты с us базы данных (только mongo)
      for usAccUid in duplicatesMap["fsn_uids"]:
        reply = func_find_one_pers({"key": "data_" + str(usAccUid)})
        if reply:
          acc = PersistentDataManager.newSimpleDataAcc(reply["data"])
          # Если мы были в гильдии, надо исключить аккаунт из Member'ов
          if acc.db.guildAuid:
            gs_reply = func_find_one_guild({"key": "gs_" + str(acc.db.guildAuid)})
            if gs_reply:
              GD = GuildData()
              GD.load(gs_reply["data"])
              GD.init(changeWriter=None)
              removeGuildMember(GD, acc.db.auid, collGuilds, logFile, highLeveledGuilds=highLevelGuilds)
            else:
              print "Guild data with auid %d was not found in Mongo" % acc.db.guildAuid
              logFile.write("Guild data wit auid %d was not found in Mongo\n" % acc.db.guildAuid)
        else:
          print "User data for auid %d was not found in Mongo" % usAccUid
          logFile.write("User data for auid %d was not found in Mongo\n" % usAccUid)
          continue
        res = collPers.remove({"key": "data_" + str(usAccUid)})
        print "REMOVE duplicate (id=%d) result: %s" % (usAccUid, res)
    else:
      print "ERROR mongo_db is None"
  else:
    print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG is empty"


def deleteDuplicatedRuAccounts():
  startTime = time.time()

  # Загружаем del_ru.json
  # ###################################################
  duplicatesFile = open(os.path.join(OUT_JSON_PATH, "del_ru.json"), "r")
  duplicatesMap = ujson.load(duplicatesFile)
  duplicatesFile.close()
  ####################################################
  # Заведём файл для логов
  logFile = open(os.path.join(OUT_JSON_PATH, "delete_duplicated_ru_accs.log"), "w")
  print "Clear duplicated uids and Nicknames from russian SQL and Mongo bases"

  sql_options = ClassDict(SQL_CONFIG[0])
  highLevelGuilds = {}
  # Удалим все лишние аккаунты с ru базы данных (как mongo, так и SQL)
  for ruAccUid in duplicatesMap["fsn_uids"]:
    deleteSqlUser(ruAccUid, sql_options)
    deleteSqlUserNickname(ruAccUid, sql_options)

  opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
  deleteMongoAccounts(duplicatesMap, opt, opt.mongo_base, highLevelGuilds, logFile)

  print "Duplicated users were removed from database"
  ####################################################
  # Сохраняем полученную информацию по гильдиям с банком
  ####################################################
  f = open(os.path.join(OUT_JSON_PATH, "guilds_above_20.json"), "w")
  json.dump(highLevelGuilds, f)
  f.close()

  logFile.close()
  endTime = time.time()
  print "Total time:", endTime - startTime


def deleteDuplicatedUsAccounts():
  startTime = time.time()

  # Загружаем del_us.json
  # ###################################################
  duplicatesFile = open(os.path.join(OUT_JSON_PATH, "del_us.json"), "r")
  duplicatesMap = ujson.load(duplicatesFile)
  duplicatesFile.close()
  ####################################################
  # Заведём файл для логов
  logFile = open(os.path.join(OUT_JSON_PATH, "delete_duplicated_us_accs.log"), "w")
  print "Clear duplicated uids and Nicknames from us Mongo base"

  opt = ClassDict(coord_cfg.COORDINATOR_MONGO_CONFIG[0])
  deleteMongoAccounts(duplicatesMap, opt, "amerika", logFile)

  print "Duplicated users were removed from database"
  ####################################################
  logFile.close()
  endTime = time.time()
  print "Total time:", endTime - startTime


def importTblLoginsForMergedAccounts():
  startTime = time.time()

  # Загружаем ss_copy.json и del_us.json
  # ###################################################
  copyAccsFile = open(os.path.join(OUT_JSON_PATH, "ss_copy.json"), "r")
  copyAccs = ujson.load(copyAccsFile)
  copyAccsFile.close()
  auidsMapFile = open(os.path.join(OUT_JSON_PATH, "new_auids.json"), "r")
  auidsMap = ujson.load(auidsMapFile)
  auidsMapFile.close()
  deletedAccFiles = open(os.path.join(OUT_JSON_PATH, "del_us.json"), "r")
  deletedAccs = ujson.load(deletedAccFiles)
  deletedAccFiles.close()
  ####################################################
  # Заводим файл логов
  logFile = open(os.path.join(OUT_JSON_PATH, "import_us_tbl_login.log"), "w")
  ru_sql_options = ClassDict(SQL_CONFIG[0])
  us_sql_options = ClassDict(SQL_CONFIG[1])

  ru_db = SyncSqlManager(ru_sql_options)
  ru_db.openConnection()
  us_db = SyncSqlManager(us_sql_options)
  us_db.openConnection()

  newUids = {"uids": {"US->RU": {}, "RU->US": {}}}
  # Сдвигаем индексы в таблице серверов, чтобы честно получить новые uid'ы
  sql_autoinc = 'SHOW TABLE STATUS LIKE "tbl_servers"'
  sql_reply = ru_db.syncSqlQuery(sql_autoinc)
  auto_inc_old = int(sql_reply[0].__getattr__("Auto_increment"))
  ru_db.syncSqlCommand("INSERT INTO tbl_servers (id, name) VALUES (%d, 'test_ws')" % auto_inc_old)
  sql_reply = ru_db.syncSqlQuery(sql_autoinc)
  auto_inc = int(sql_reply[0].__getattr__("Auto_increment"))
  ru_db.syncSqlCommand("DELETE FROM tbl_servers WHERE id=%d" % auto_inc_old)

  guids = FakeGuidGenarator()
  guids.__init__(auto_inc)
  curIdx = 0
  newId = 0
  newAuid = 0
  usAuid = 0
  # Здесь храним перенесённые auid'ы
  copiedAuids = {"auids": {"US->RU": {}, "RU->US": {}}}
  # Переносим таблицу логинов
  us_logins_reply = us_db.syncSqlQuery("SELECT * FROM tbl_login")
  total_logins = len(us_logins_reply)
  print "Total logins in us databese: %d" % total_logins
  for sql_login in us_logins_reply:
    # Если этот акк не попал в список удалённых, переносим его данные в ru sql таблицу
    if md5(sql_login["login"]) in copyAccs:
      usAuid = copyAccs[md5(sql_login["login"])]
      newAuid = getRusAuid(auidsMap, "auids", usAuid)
      if newAuid:
        copiedAuids["auids"]["RU->US"][str(newAuid)] = usAuid
        copiedAuids["auids"]["US->RU"][str(usAuid)] = newAuid
      newId = guids.nextInt64GUID("sql_uid")
      newUids["uids"]["RU->US"][str(newId)] = sql_login["id"]
      newUids["uids"]["US->RU"][str(sql_login["id"])] = newId
      reply = addNewSqlUserDB(ru_db, newId, str(sql_login["login"]), str(sql_login["pwd_md5"]))
      if reply == None:
        #print "user with login %r was not added" % sql_login["login"]
        logFile.write("user with login %r was not added\n" % sql_login["login"])
    else:
      logFile.write("WARNING user with login %r was not found in ss_copy.json\n" % sql_login["login"])
    curIdx += 1
    if curIdx % 100 == 0:
      sys.stdout.write("Transferring 'tbl_login', %d percents complete\r" % toint(curIdx * 100 / total_logins))
  print "Transferring 'tbl_login', 100 percents complete\n"

  # Переносим таблицу ников
  curIdx = 0
  us_nicknames_reply = us_db.syncSqlQuery("SELECT * FROM tbl_nick")
  total_nicks = len(us_nicknames_reply)
  for sql_nick in us_nicknames_reply:
    # Если этот акк не попал в список удалённых, переносим его данные в ru sql таблицу
    if str(sql_nick["id"]) in newUids["uids"]["US->RU"]:
      newId = newUids["uids"]["US->RU"][str(sql_nick["id"])]
      nick_unicode = utf8convert(unicode(sql_nick["nick"]))
      reply = addNewSqlUserNicknameDB(ru_db, newId, nick_unicode)
      if reply == None:
        #print "Nickname %r was not added" % nick_unicode
        logFile.write("Nickname %r was not added\n" % nick_unicode)
    else:
      logFile.write("WARNING Nickname %r was not found in uids map\n" % sql_nick["nick"])
    curIdx += 1
    if curIdx % 100 == 0:
      sys.stdout.write("Transferring 'tbl_nick, %d percents complete\r" % toint(curIdx * 100 / total_nicks))
  print "Transferring 'tbl_nick', 100 percents complete\n"

  # Сбросим таблицу серверов, чтобы все юзеры смогли залогиниться в следующий раз
  ####################################################
  ru_db.syncSqlCommand("UPDATE tbl_login SET server_id=0")

  # Сохраняем полученную информацию по соответствию uid'ов
  ####################################################
  f = open(os.path.join(OUT_JSON_PATH, "new_uids.json"), "w")
  json.dump(newUids, f)
  f.close()
  # Сохраняем полученную информацию по перенесённым auid'ам
  ####################################################
  f = open(os.path.join(OUT_JSON_PATH, "copied_auids.json"), "w")
  json.dump(copiedAuids, f)
  f.close()

  # Обнулим временную таблицу tbl_login в se1
  ####################################################
  import x_coord_cfg

  seSqlConfig = ClassDict(x_coord_cfg.COORDINATOR_SQL_CONFIG[0])
  reply = syncSqlCommand("DELETE FROM tbl_login", seSqlConfig)
  logFile.close()
  ####################################################
  endTime = time.time()
  print "Total time:", endTime - startTime


def importPwcSQLlogins():
  startTime = time.time()

  ru_db = SyncSqlManager(ClassDict(SQL_CONFIG[0]))
  ru_db.openConnection()
  us_db = SyncSqlManager(ClassDict(SQL_CONFIG[1]))
  us_db.openConnection()

  if not os.path.exists(OUT_JSON_PATH):
    os.makedirs(OUT_JSON_PATH)

  logFile = open(os.path.join(OUT_JSON_PATH, "import_pwc_sql_logins.log"), "w")
  newUids = {"map": {}, "dup": []}
  # Сдвигаем индексы в таблице серверов, чтобы честно получить новые uid'ы
  sql_autoinc = 'SHOW TABLE STATUS LIKE "tbl_servers"'
  sql_reply = ru_db.syncSqlQuery(sql_autoinc)
  auto_inc_old = int(sql_reply[0].__getattr__("Auto_increment"))
  ru_db.syncSqlCommand("INSERT INTO tbl_servers (id, name) VALUES (%d, 'test_ws')" % auto_inc_old)
  sql_reply = ru_db.syncSqlQuery(sql_autoinc)
  auto_inc = int(sql_reply[0].__getattr__("Auto_increment"))
  ru_db.syncSqlCommand("DELETE FROM tbl_servers WHERE id=%d" % auto_inc_old)
  guids = FakeGuidGenarator()
  guids.__init__(auto_inc)

  ru_pwc_emails_reply = ru_db.syncSqlQuery("SELECT email FROM tbl_pwconnect")
  ru_emails = {}
  new_snuid = 0
  for mail in ru_pwc_emails_reply:
    ru_emails[md5(utf8convert(unicode(mail["email"])))] = 0
  total_ru = len(ru_emails)
  us_pwc_logins_reply = us_db.syncSqlQuery("SELECT * FROM tbl_pwconnect")
  total_us = len(us_pwc_logins_reply)
  curIdx = 0
  duplicated_emails = 0
  for pwc_login in us_pwc_logins_reply:
    # Если такой e-mail уже зарегистрирован
    if ru_emails.has_key(md5(utf8convert(unicode(pwc_login.email)))):
      newUids["dup"].append(pwc_login.pwc_snuid)
      ru_acc = ru_db.syncSqlQuery("SELECT * FROM tbl_pwconnect WHERE email='%s'" % pwc_login.email)
      if ru_acc:
        # Русский акк подтверждён (или не подтверждены оба или оба подтверждены, но русский акк старше)
        duplicated_emails += 1
        newUids["map"][str(pwc_login.pwc_snuid)] = ru_acc[0].pwc_snuid
        # переносим русский логин в таблицу tbl_login us сервера
        reply = us_db.syncSqlCommand(u"UPDATE tbl_login SET login='%s' WHERE login='%s'" % (
          "pwc#" + str(ru_acc[0].pwc_snuid), "pwc#" + str(pwc_login.pwc_snuid)))
        if reply == None:
          print "Transferring duplicated pwc login %r from russian to us sql database failed" % ru_acc[0].pwc_snuid
          logFile.write(
            "Transferring duplicated pwc login %r from russian to us sql database failed\n" % ru_acc[0].pwc_snuid)
        if not (
                (ru_acc[0].active != 0 and pwc_login.active == 0) or (
                      ru_acc[0].active == 0 and pwc_login.active == 0) or \
                (ru_acc[0].active != 0 and pwc_login.active != 0 and ru_acc[0].ts_create < pwc_login.ts_create)):
          # Подтверждём американский, или подтверждены оба, но старше американский переносим его данные в русскую базу.
          reply = ru_db.syncSqlCommand(u"UPDATE tbl_pwconnect SET pwd_md5='%s', gender=%d, birthdate=%d,\
                                            ip='%s', ts_create=%d, confirm='%s', ts_confirm=%d, active=%d, ts_active=%d, ts_resend=%d,ts_reset_pwd=%d \
                                            WHERE email='%s'" % (pwc_login.pwd_md5, pwc_login.gender, \
                                                                 pwc_login.birthdate, pwc_login.ip, pwc_login.ts_create,
                                                                 pwc_login.confirm, pwc_login.ts_confirm, \
                                                                 pwc_login.active, pwc_login.ts_active,
                                                                 pwc_login.ts_resend, pwc_login.ts_reset_pwd,
                                                                 pwc_login.email))
          if reply == None:
            print "Transferring duplicated pwc login %r from us to russian sql database failed" % pwc_login.pwc_snuid
            logFile.write(
              "Transferring duplicated pwc login %r from us to russian sql database failed\n" % pwc_login.pwc_snuid)
      else:
        print "Login with email %r was not found in russian SQL base" % pwc_login.email
        logFile.write("Login with email %r was not found in russian SQL base\n" % pwc_login.email)
    else:
      # e-mail не зарегистрирован, просто перенесём данные из одной таблицы в другую
      new_snuid = guids.nextInt64GUID("pwc_snuid")
      newUids["map"][str(pwc_login.pwc_snuid)] = new_snuid
      reply = ru_db.syncSqlCommand(u"INSERT INTO tbl_pwconnect (email,email_md5,pwc_snuid,pwd_md5,ip,gender,birthdate,ts_create,confirm,ts_confirm,active,ts_active,ts_resend,ts_reset_pwd)\
             VALUES ('%s','%s',%d,'%s','%s',%d,%d,%d,'%s',%d,%d,%d,%d,%d)" \
                                   % ((pwc_login.email, pwc_login.email_md5, new_snuid, pwc_login.pwd_md5, pwc_login.ip,
                                       toint(pwc_login.gender), toint(pwc_login.birthdate), \
                                       toint(pwc_login.ts_create), pwc_login.confirm, toint(pwc_login.ts_confirm),
                                       toint(pwc_login.active), toint(pwc_login.ts_active), toint(pwc_login.ts_resend),
                                       toint(pwc_login.ts_reset_pwd))))
      if not reply:
        print "Transferring us pwc login %d to russian sql database failed" % pwc_login.pwc_snuid
        logFile.write("Transferring us pwc login %d to russian sql database failed\n" % pwc_login.pwc_snuid)
      login_reply = us_db.syncSqlCommand(u"UPDATE tbl_login SET login='%s' WHERE login='%s'" % (
        "pwc#" + str(new_snuid), "pwc#" + str(pwc_login.pwc_snuid)))
      if login_reply == None:
        print "Updating pwc login %r in us tbl_login failed" % pwc_login.pwc_snuid
        logFile.write("Updating pwc login %r in us tbl_login failed\n" % pwc_login.pwc_snuid)
    curIdx += 1
    if curIdx % 100 == 0:
      sys.stdout.write("Transferring PWC accounts: %r percents complete\r" % (curIdx * 100 / total_us))

  print "Transferring PWC accounts: 100 percents complete, number of duplicated emails %d\n" % duplicated_emails
  # Сохраняем полученную информацию по соответствию uid'ов
  # ###################################################
  f = open(os.path.join(OUT_JSON_PATH, "pwc_fix.json"), "w")
  json.dump(newUids, f)
  f.close()
  logFile.close()

  ####################################################
  endTime = time.time()
  print "Total time:", endTime - startTime


def returnGold():
  startTime = time.time()

  # Загружаем ss_copy.json и del_us.json
  # ###################################################
  bonusGoldFile = open(os.path.join(OUT_JSON_PATH, "add_gold.json"), "r")
  bonusGold = ujson.load(bonusGoldFile)
  bonusGoldFile.close()
  currentGoldFile = open(os.path.join(OUT_JSON_PATH, "us_current_billing.json"), "r")
  currentGold = ujson.load(currentGoldFile)
  currentGoldFile.close()
  auidsMapFile = open(os.path.join(OUT_JSON_PATH, "new_auids.json"), "r")
  auidsMap = ujson.load(auidsMapFile)
  auidsMapFile.close()
  ####################################################
  # Заведём файл с логами
  logFile = open(os.path.join(OUT_JSON_PATH, "return_gold.log"), "w")

  # Заведём файл с данными о биллинге
  replenishFile = open(os.path.join(OUT_JSON_PATH, "replenish.txt"), "w")

  # вернём денег всем, у кого были удалены аккаунты
  for accInfo in bonusGold:
    # Если добавляем денег на русский акк (американский удалён), то auid у него не менялся
    if accInfo["locale"] == "RU":
      replenishAuid = accInfo["auid"]
    # Если добавляем денег на американский акк (русский удалён), найдём его новый auid
    else:
      replenishAuid = auidsMap["auids"]["US->RU"].get(str(accInfo["auid"]))

    replenishFile.write(str(replenishAuid) + "," + str(accInfo["gold"]) + "\n")

  # восстановим текущий баланс для перенесённых амеркианцев
  for accAuid in currentGold["billing"].keys():
    # Для всех перенесённых аккаунтов надо достать голду и зачислить на счёт
    if auidsMap["auids"]["US->RU"].has_key(str(accAuid)):
      replenishAuid = auidsMap["auids"]["US->RU"][accAuid]
      replenishAmount = currentGold["billing"][accAuid]
      replenishFile.write(str(replenishAuid) + "," + str(replenishAmount) + "\n")
    else:
      logFile.write("ERROR: no billing info found for acc with auid %r\n" % accAuid)

  ####################################################
  logFile.close()
  replenishFile.close()
  endTime = time.time()
  print "Total time:", endTime - startTime


def main():
  gc.disable()

  arglist = sys.argv[1:]
  print "arglist: ", arglist
  # TODO Навести порярядок
  # 1. Разбить опции на группы
  # 2. Прокомментировать команды и дополнительные опции
  opts, args = getopt.getopt(arglist, "", [ "fix_acc_db=", "fix_us_ru_guilds", "find_duplicated_accs", "delete_duplicated_ru_accs",
                                           "delete_duplicated_us_accs", "import_us_tbl_login", "import_pwc_sql_logins",
                                           "return_gold", "check_all_sa_auids=", "unique_nicks", "fix_pwc_auids",
  ])

  for opt, arg in opts:
      if opt == "--fix_acc_db":
          fixAccDb(toint(arg))

      elif opt == "--fix_us_ru_guilds":
          fixRuUsGuildData()

      elif opt == "--find_duplicated_accs":
          parseDuplicatedAuids()

      elif opt == "--delete_duplicated_ru_accs":
          deleteDuplicatedRuAccounts()

      elif opt == "--delete_duplicated_us_accs":
          deleteDuplicatedUsAccounts()

      elif opt == "--import_us_tbl_login":
          importTblLoginsForMergedAccounts()

      elif opt == "--import_pwc_sql_logins":
          importPwcSQLlogins()

      elif opt == "--return_gold":
          returnGold()

      elif opt == "--check_all_sa_auids":
          checkAllSAAuids(toint(arg))

      elif opt == "--unique_nicks":
          uniqueNicks()

      elif opt == "--fix_pwc_auids":
          fixPwcAuids()
# --------------------------------------

if __name__ == "__main__":
  main()
