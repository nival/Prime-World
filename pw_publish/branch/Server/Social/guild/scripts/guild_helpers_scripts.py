#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, time, datetime
import getopt
import pymongo
import urllib, urllib2
import gc
from threading import Thread
import math
import os.path
import codecs

sys.path.append('../../cfg')
import coord_cfg
sys.path.append('../../libs/memcache')
import memcache


sys.path.append('../..')
from base.helpers import *
from guild.GuildData import GuildData
from handlers import *

FOREACH_GUILD_PER_GC_COLLECT = 100

# Обрабатывает базу данных гильдий из coord_cfg.COORDINATOR_MONGO_CONFIG[1]
# Записывает результат в базу coord_cfg.COORDINATOR_MONGO_CONFIG[0]
# Лучше, если перед началом работы скрипта базы в [0] и [1] будут одинаковые
def processGuilds2Databases(processFunction, logFileName, *kwargs):
  startTime = time.time()
  curIdx = 0
  logDict = {}

  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 1:
    opt_src = ClassDict( coord_cfg.COORDINATOR_MONGO_CONFIG[1] )
    opt_dst = ClassDict( coord_cfg.COORDINATOR_MONGO_CONFIG[0] )
    connection_src = pymongo.Connection( opt_src.mongo_addr, opt_src.mongo_port )
    connection_dst = pymongo.Connection( opt_dst.mongo_addr, opt_dst.mongo_port )
    mongo_db_src = getattr(connection_src, opt_src.mongo_base, None)
    mongo_db_dst = getattr(connection_dst, opt_dst.mongo_base, None)
    if mongo_db_src:
      coll_src = getattr( mongo_db_src, "guilds" )
      coll_dst = getattr( mongo_db_dst, "guilds" )
      func_find = getattr( coll_src, "find" )
      func_update = getattr(coll_dst, "update")
      reply = func_find( { "key" : { "$exists" : True } } )
      total = reply.count()

      print "Total guilds:", total
      for guildInfo in reply:
        # 1) Получаем служебную информацию о гильдии
        ####################################################
        data_json = guildInfo["data"]
        guild_key = guildInfo["key"]

        if isinstance(guild_key, int) or (not isinstance(guild_key, long) and len(guild_key) == 0):
            print( "ERROR bad mongo key %r\n" % guild_key )
            continue
        ####################################################

        # 2) Загружаем guilddata
        ####################################################
        guilddata = GuildData()
        guilddata.load( data_json )
        guilddata.init( changeWriter=None )
        ####################################################

        # 3) Обрабатываем данные гильдиии заданной функцией
        ####################################################
        guilddata = processFunction(guilddata, logDict, kwargs)

        # 4) Сохраняем guilddata в json и пишем кирпич в монго
        ####################################################
        new_data_json = guilddata.save()
        mongo_reply = func_update( {"key": "gs_"+str(guilddata.GuildAuid)}, {"$set": {"data":new_data_json}}, upsert=True, new=True )
        if not mongo_reply.get( "ok", None ):
            print ( "ERROR save to mongo: %r\n" % mongo_reply )

        # 5) Чистим память
        ####################################################
        curIdx += 1
        if curIdx % FOREACH_GUILD_PER_GC_COLLECT == 0:
          gc.collect()
          sys.stdout.write("Guilds converted: %d/%d\r" % (curIdx, total))

      print "Guilds converted: %d/%d\n" % (total, total)

  # Заводим файл для дампа
  ###################################################
  logFile = open(logFileName, "w")
  json.dump(logDict, logFile)
  logFile.close()
  endTime = time.time()
  print "Total time:", endTime-startTime

def removeGuildMemberById(guildData, dupMemberID, mainMemberID):
    dupMember = guildData.getGuildMemberByID(dupMemberID)
    mainMember = guildData.getGuildMemberByID(mainMemberID)

    if not dupMember:
      warn("removeGuildMemberById failed: cannot find member %d in guild %d" % (dupMemberID, guildData.GuildAuid))
      return False

    if guildData.Owner == dupMember:
      # главу гильдии ни в коем случае не трогаем!
      warn("removeGuildMemberById failed: cannot remove Guild Owner")
      return

    # Меняем индексы талантов, которые принадлежали дубликату игроку
    for gTalId in guildData.GuildTalentKeeper:
      talent = guildData.getGuildTalentByID(gTalId)
      if talent.Holder == dupMember:
        info("Guild with auid %d has bank!", guildData.GuildAuid)
        talent.Holder = mainMember
      if talent.Owner == dupMember:
        info("Guild with auid %d has bank!", guildData.GuildAuid)
        talent.Owner = mainMember

    #пшел вон
    guildData.Members.remove(dupMember)
    guildData.GuildMemberKeeper.remove(dupMemberID)

def getDuplicatedMembers(guilddata, duplicatedUsers):
  auids = []
  for memberId in guilddata.GuildMemberKeeper:
    member = guilddata.getGuildMemberByID( memberId )
    if not member.Person in auids:
      auids.append(member.Person)
    else:
      if duplicatedUsers.get(guilddata.GuildAuid, None):
        duplicatedUsers[guilddata.GuildAuid].append(member.Person)
      else:
        duplicatedUsers[guilddata.GuildAuid] = [member.Person]

def removeDuplicatedMembers(guilddata, duplicatedUsers, *kwargs):
  getDuplicatedMembers(guilddata, duplicatedUsers)
  if guilddata.GuildAuid in duplicatedUsers:
    for auid in duplicatedUsers[guilddata.GuildAuid]:
      mainId = 0
      dupId = 0
      # Определим, кто из аккаунтов у нас главный
      for memberId in guilddata.GuildMemberKeeper:
        member = guilddata.getGuildMemberByID(memberId)
        if member.Person == auid:
          if member.getID() == guilddata.Owner.getID():
            mainId = memberId
          else:
            if not dupId:
              dupId = memberId
            else:
              mainId = memberId
      removeGuildMemberById(guilddata, dupId, mainId)
  return guilddata

def findDuplicatedGuildMembers(outFilename):
  startTime = time.time()
  curIdx = 0
  duplicatedUsers = {}

  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 0:
    opt = ClassDict( coord_cfg.COORDINATOR_MONGO_CONFIG[0] )
    connection = pymongo.Connection( opt.mongo_addr, opt.mongo_port )
    mongo_db = getattr(connection, opt.mongo_base, None)
    if mongo_db:
      coll = getattr( mongo_db, "guilds" )
      func = getattr( coll, "find" )
      reply = func( { "key" : { "$exists" : True } } )
      total = reply.count()

      print "Total guilds:", total
      for guildInfo in reply:
        # 1) Получаем служебную информацию о гильдии
        ####################################################
        data_json = guildInfo["data"]
        guild_key = guildInfo["key"]

        if isinstance(guild_key, int) or ((not isinstance(guild_key, long) and len(guild_key) == 0)):
            print( "ERROR bad mongo key %r\n" % guild_key )
            continue
        ####################################################

        # 2) Загружаем guilddata
        ####################################################
        guilddata = GuildData()
        try:
            guilddata.load( data_json )
        except AssertionError:
            print >>sys.stderr, "Error loading data for info: %s" % guildInfo
        guilddata.init( changeWriter=None )
        ####################################################

        # 3) Ищем дублируемых товарищей
        ####################################################
        auids = []
        for memberId in guilddata.GuildMemberKeeper:
          member = guilddata.getGuildMemberByID( memberId )
          if not member.Person in auids:
            auids.append(member.Person)
          else:
            if duplicatedUsers.get(guilddata.GuildAuid, None):
              duplicatedUsers[guilddata.GuildAuid].append(member.Person)
            else:
              duplicatedUsers[guilddata.GuildAuid] = [member.Person]

        # 4) Чистим память
        ####################################################
        curIdx += 1
        if curIdx % FOREACH_GUILD_PER_GC_COLLECT == 0:
          gc.collect()
          sys.stdout.write("Guilds handled: %d/%d\r" % (curIdx+1, total))

      print "Guilds handled: %d/%d\n" % (total, total)

    else:
      print "ERROR mongo_db is None"
  else:
    print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG doesn't contain configuration for RU backup database"

  # Заводим файл для дампа
  ###################################################
  duplicatedUsersFile = open(outFilename, "w")
  json.dump(duplicatedUsers, duplicatedUsersFile)
  duplicatedUsersFile.close()

  endTime = time.time()
  print "Total time:", endTime-startTime


def main():
  gc.disable()

  arglist = sys.argv[1:]
  print "arglist: ", arglist
  opts, args = getopt.getopt( arglist, "", ["find_duplicated_members=", "remove_duplicated_members="])

  for opt, arg in opts:
    if opt == "--find_duplicated_members":
      findDuplicatedGuildMembers(arg)
    if opt == "--remove_duplicated_members":
      processGuilds2Databases(removeDuplicatedMembers, arg)

# --------------------------------------

if __name__ == "__main__":
    main()
