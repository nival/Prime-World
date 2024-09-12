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
GUILD_RESOURCES_BONUS = 100000

guildLevels912 = [ 	0, 500000, 1100000, 1900000, 2900000, 4000000, 5300000, 6800000, 8500000, 10500000, 12600000, 14700000,
                    17000000, 19500000, 22100000, 24900000, 27800000, 30800000, 34000000, 37400000, 41300000, 45800000, 50800000,
                    56400000, 62500000, 69200000, 76400000, 84300000, 92700000, 101800000, 111000000, 120400000, 130000000,
                    139800000, 149700000, 159900000, 170200000, 180800000, 191500000, 202500000]
guildLevels913 = [ 	0, 4000000, 10000000, 17000000, 25000000, 34000000, 45000000, 58000000, 72000000, 89000000, 106000000, 125000000,
                    144000000, 165000000, 187000000, 211000000, 239000000, 269000000, 304000000, 342000000, 383000000, 427000000, 474000000,
                    524000000, 577000000, 634000000, 693000000, 756000000, 822000000, 891000000, 963000000, 1040000000, 1120000000,
                    1200000000, 1290000000, 1380000000, 1470000000, 1570000000, 1670000000, 1770000000]

guildLevels914 = []


def recalcGuildExperience(exp, oldGuildLevels, newGuildLevels):
  lvl = -1
  low = 0
  high = 0

  for requiredExp in oldGuildLevels:
    if exp >= requiredExp:
      lvl += 1
    else:
      break
  if lvl == -1:
    return 0
  try:
    low = oldGuildLevels[lvl]
    high = low # если следующего уровня нет, вернем [cap,cap]
    high = oldGuildLevels[lvl+1]
  except:
    pass
  if high == low:
    return newGuildLevels[lvl]
  currLevelExp = newGuildLevels[lvl]
  additionExp = (newGuildLevels[lvl+1] - currLevelExp) * (exp - low) / (high - low)
  return currLevelExp + additionExp

def makeListOfOldGuildExperience(oldExpFilename):
  startTime = time.time()
  guildExperience = {}
  curIdx = 0

  # База бэкапов, с которой мы работаем, должна быть второй по счёту в конфиге
  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 1:
    opt = ClassDict( coord_cfg.COORDINATOR_MONGO_CONFIG[1] )
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

        if len(guild_key) == 0:
            print( "ERROR bad mongo key %r\n" % guild_key )
            continue
        ####################################################

        # 2) Загружаем guilddata
        ####################################################
        guilddata = GuildData()
        guilddata.load( data_json )
        guilddata.init( changeWriter=None )
        ####################################################

        # 3) Запоминаем старый опыт
        ####################################################
        guildExperience[guilddata.GuildAuid] = guilddata.GuildLevelInfo.Experience

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

  endTime = time.time()
  # Заводим файл для гильдий
  ####################################################
  expFile = open(oldExpFilename, "w" )
  json.dump( guildExperience, expFile )
  expFile.close()

  print "Total time:", endTime-startTime

def convertOldGuilds(oldExpFilename):
  startTime = time.time()
  curIdx = 0
  guildConversionInfo = {}

  # Загружаем sa_copy.json
  ####################################################
  oldExpfile = open(oldExpFilename, "r" )
  oldExpMap = ujson.load( oldExpfile )
  oldExpfile.close()

  # Подгрузим StaticData, чтобы пересчитать уровени
  ####################################################
  SD = StaticData( "../../xdb/ExportedSocialData.xml", None )
  for it in SD.data['GuildLevels']['levels']['Item']:
    guildLevels914.append(it['requiredExp'])
    curIdx+= 1

  curIdx = 0
  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 1:
    opt_src = ClassDict( coord_cfg.COORDINATOR_MONGO_CONFIG[1] )
    opt_dst = ClassDict( coord_cfg.COORDINATOR_MONGO_CONFIG[0] )
    connection_src = pymongo.Connection( opt_src.mongo_addr, opt_src.mongo_port )
    connection_dst = pymongo.Connection( opt_dst.mongo_addr, opt_dst.mongo_port )
    mongo_db_src = getattr(connection_src, opt_src.mongo_base, None)
    mongo_db_dst = getattr(connection_src, opt_dst.mongo_base, None)
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

        # 3) Конвертируем опыт
        ####################################################
        # Проверим, старая это гильдия или новая
        if str(guilddata.GuildAuid) in oldExpMap:
          # Если уровни уже конвертировали, откатим изменения и пересчитаем ещё раз
          if guilddata.version.LevelsConverted:
            currExp = guilddata.GuildLevelInfo.Experience
            oldExpTo913 = recalcGuildExperience(oldExpMap[str(guilddata.GuildAuid)], guildLevels912, guildLevels913)
            deltaExp = currExp - oldExpTo913
            newExp = recalcGuildExperience(oldExpMap[str(guilddata.GuildAuid)], guildLevels912, guildLevels914) + deltaExp + GUILD_RESOURCES_BONUS
            guildConversionInfo[guilddata.GuildAuid] = { "9.12Exp" : oldExpMap[str(guilddata.GuildAuid)], "9.13Exp": currExp,
                                                         "wasConverted": True, "delta": deltaExp, "9.14Exp": newExp}
          else:
            # Если уровни не конвертировали, конвертируем с 9.12 сразу на 9.14
            newExp = recalcGuildExperience(guilddata.GuildLevelInfo.Experience, guildLevels912, guildLevels914)
            guildConversionInfo[guilddata.GuildAuid] = { "9.12Exp" : oldExpMap[str(guilddata.GuildAuid)],
                                                         "wasConverted": False, "9.14Exp": newExp}
          guilddata.GuildLevelInfo.Experience = newExp
        else:
          # Гильдия новая, надо просто сохранить её текущий статус
          guildConversionInfo[guilddata.GuildAuid] = { "wasConverted": False, "9.14Exp": guilddata.GuildLevelInfo.Experience}

        guilddata.version.LevelsConverted = True
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
  endTime = time.time()
  # Заводим файл для гильдий
  ####################################################
  expFile = open("guild_conversion_log.json", "w" )
  json.dump( guildConversionInfo, expFile )
  expFile.close()

  print "Total time:", endTime-startTime

#def makeListOfOldUSGuildExperience(oldExpFilename):
#  startTime = time.time()
#  guildExperience = {}
#  curIdx = 0

#  guildfile = open("guildauids.json", "r" )
#  guildsmap = ujson.load( guildfile )
#  guildfile.close()

#  if len(coord_cfg.COORDINATOR_MONGO_CONFIG) > 1:
#    opt = ClassDict( coord_cfg.COORDINATOR_MONGO_CONFIG[1] )
#    connection = pymongo.Connection( opt.mongo_addr, opt.mongo_port )
#    mongo_db = getattr(connection, opt.mongo_base, None)
#    if mongo_db:
#      coll = getattr( mongo_db, "guilds" )
#      func = getattr( coll, "find" )
#      reply = func( { "key" : { "$exists" : True } } )
#      total = reply.count()

#      print "Total guilds:", total
#      for guildInfo in reply:
#        # 1) Получаем служебную информацию о гильдии
#        ####################################################
#        data_json = guildInfo["data"]
#        guild_key = guildInfo["key"]

#        if len(guild_key) == 0:
#            print( "ERROR bad mongo key %r\n" % guild_key )
#            continue
#        ####################################################

#        # 2) Загружаем guilddata
#        ####################################################
#        guilddata = GuildData()
#        guilddata.load( data_json )
#        guilddata.init( changeWriter=None )
#        ####################################################

#        # 3) Запоминаем старый опыт
#        ####################################################
#        # Не нашли auid? значит, гильдию не перенесли..
#        if str(guilddata.GuildAuid) not in guildsmap["guildauids"]["US->RU"]:
#          continue
#        newAuid = guildsmap["guildauids"]["US->RU"][str(guilddata.GuildAuid)]
#        guildExperience[newAuid] = guilddata.GuildLevelInfo.Experience

#        # 4) Чистим память
#        ####################################################
#        curIdx += 1
#        if curIdx % FOREACH_GUILD_PER_GC_COLLECT == 0:
#          gc.collect()
#          sys.stdout.write("Guilds handled: %d/%d\r" % (curIdx+1, total))

#      print "Guilds handled: %d/%d\n" % (total, total)

#    else:
#      print "ERROR mongo_db is None"
#  else:
#    print "ERROR coord_cfg.COORDINATOR_MONGO_CONFIG doesn't contain configuration for RU backup database"

#  endTime = time.time()
#  # Заводим файл для гильдий
#  ####################################################
#  expFile = open(oldExpFilename, "w" )
#  json.dump( guildExperience, expFile )
#  expFile.close()

#  print "Total time:", endTime-startTime

def main():
  gc.disable()

  arglist = sys.argv[1:]
  print "arglist: ", arglist
  opts, args = getopt.getopt( arglist, "", ["make_old_experience_list=", "convert_all_guilds=",])
    #"make_old_us_experience_list=" ])

  for opt, arg in opts:
    if opt == "--make_old_experience_list":
      makeListOfOldGuildExperience(arg)
    elif opt == "--convert_all_guilds":
      convertOldGuilds(arg)
    #elif opt == "--make_old_us_experience_list":
    #  makeListOfOldUSGuildExperience(arg)

# --------------------------------------

if __name__ == "__main__":
    main()