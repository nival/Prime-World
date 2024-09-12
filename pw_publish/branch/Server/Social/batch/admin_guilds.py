# -*- coding: utf-8 -*-

import sys, os
from guild.GuildData import GuildData

IGNORE_MULTIGUILD = False

# Проверяет, что для данной гильдии ( кирпичу ), найденной по { "key" : "gs_#auid#" }
# соответствует корректная shortinfo запись
def checkShortInfoByGSKey( reply, auid, coll ):

    # Нашли более одной записи shortinfo
    # Надо удалить все записи кроме первой валидной
    if reply.count() > 1:
        print "Too much shortinfo guilds records with auid", auid
        deleteAllShortInfoExceptOne( reply, auid, coll )
        return False

    # Не нашли ни одной записи shortinfo
    # Надо удалить кирпич по { "key" : "gs_#auid#" }
    if reply.count() == 0:
        print "Guild", auid, "not found. Erase..."
        deleteGuildData( auid, coll )
        deleteRatingData( auid, coll )
        return False

    # Нашли одну запись shortinfo
    guild = reply[0]
    # Проверяем, что там валидные ShortName и FullName
    # Если не валидные - удаляем и кирпич и shortinfo
    if not guild["ShortName"] or not guild["FullName"]:
        print "Not valid shortinfo for auid", auid, "Erase..."
        deleteShortInfo( auid, coll )
        deleteGuildData( auid, coll )
        deleteRatingData( auid, coll )
        return False

    return True



# Проверяет, что у данной гильдии ( кирпичу ), найденной по { "key" : "gs_#auid#" }
# все хорошо с данными
def checkGuildDataByGSKey( reply, auid, coll ):

    # Нашли более одной записи GuildData
    # Надо удалить все записи кроме той, в которую больше всего вложили ресурсов
    if reply.count() > 1:
        deleteAllGuildDataExceptOne( reply, auid, coll )
        print "Too much guilddata with auid", auid, "Erase"
        return False

    # Не нашли ни одной записи GuildData
    # Надо удалить и кирпич и shortinfo
    if reply.count() == 0:
        print "Guild with key gs_", auid, "not found. Erase..."
        deleteShortInfo( auid, coll )
        deleteGuildData( auid, coll )
        deleteRatingData( auid, coll )
        return False

    # Нашли одну запись GuildData
    # Загрузим ее для дальнейших проверок
    try:
        guild = reply[0]
        data_json = '{"GuildData":{}}'
        data_json = guild["data"] or '{"GuildData":{}}'
    except:
        print "Bad reply ", reply
        data_json = '{"GuildData":{}}'

    guildData = GuildData()
    try:
        guildData.load( data_json )
    except Exception:
        print "Bad GuildData: ", data_json, " .Erase.."
        deleteShortInfo( auid, coll )
        deleteGuildData( auid, coll )
        deleteRatingData( auid, coll )
        return False

    guildData.init( None )

    # Проверяем, что там валидные ShortName и FullName
    if not guildData.GuildInfo.FullName or not guildData.GuildInfo.ShortName:
        print "Guild with key gs_", auid, "has not valid name. Erase..."
        deleteShortInfo( auid, coll )
        deleteRatingData( auid, coll )
        deleteGuildData( auid, coll )
        return False

    # Проверяем, что есть члены в этой гильдии ( она не пустая )
    if len( guildData.GuildMemberKeeper ) == 0:
        print "Guild with key gs_", auid, "has not members. Erase..."
        deleteShortInfo( auid, coll )
        deleteRatingData( auid, coll )
        deleteGuildData( auid, coll )
        return False

    # Проверяем, что GuildAuid не равен 0
    if guildData.GuildAuid == 0:
        print "Guild with key gs_", auid, "has GuildAuid = 0 Erase..."
        deleteShortInfo( auid, coll )
        deleteRatingData( auid, coll )
        deleteGuildData( auid, coll )
        return False

    return True



# Проверяет, что у данной гильдии ( кирпичу ), найденной по shortinfo
# все хорошо с данными
def checkGuildDataByShortInfo( reply, auid, coll ):
    return checkGuildDataByGSKey( reply, auid, coll )



# Проверяет, что у данной shortinfo, найденной по shortinfo, корректная shortinfo запись
def checkShortInfoByShortInfo( reply, auid, coll ):
    return checkShortInfoByGSKey( reply, auid, coll )



# Удаляет все записи shortinfo кроме первой валидной
def deleteAllShortInfoExceptOne( reply, auid, coll ):
    needDelete = False
    for obj in reply:
        if needDelete:
            coll.remove( {"_id" : obj["_id"] } )
            continue
        if guild["ShortName"] and guild["FullName"] and guild["GuildAuid"] == auid:
            needDelete = True
            continue
        else:
            coll.remove( {"_id" : obj["_id"] } )
            continue



# Удаляет все записи GuildData ( кирпичи ) кроме той, в которой больше всего вложили ресурсов
def deleteAllGuildDataExceptOne( reply, auid, coll ):
    reachestGuildId = None
    reachestGuildResources = 0
    for obj in reply:
        guild = obj
        data_json = '{"GuildData":{}}'
        try:
            data_json = guild["data"] or '{"GuildData":{}}'
        except:
            data_json = '{"GuildData":{}}'

        guildData = GuildData()
        guildData.load( data_json )
        guildData.init( None )
        if guildData.GuildLevelInfo.Experience >= reachestGuildResources:
            reachestGuildResources = guildData.GuildLevelInfo.Experience
            reachestGuildId = obj["_id"]

    coll.remove( {"key" : "gs_"+str(auid), "_id":{"$ne":reachestGuildId} } )


# Удаляет shortinfo
def deleteShortInfo( auid, coll ):
    coll.remove( {"GuildAuid" : auid } )


# Удаляет кирпич GuildData
def deleteGuildData( auid, coll ):
    coll.remove( {"key" : "gs_"+str(auid) } )

def deleteRatingData( auid, coll ):
    coll.remove( {"key" : auid } )


def getGuildMembers(auid, data, all_members):
    if not data:
        return
    guildData = GuildData()
    guildData.load( data )
    guildData.init( None )
    for m in guildData.GuildMemberKeeper.itervalues():
        if m.Person in all_members and not IGNORE_MULTIGUILD:
            print "ERROR: duplicate guilds for person %s: %s and %s" % (m.Person, all_members[m.Person], auid)
            return False
        all_members[m.Person] = auid
    return True


def getDupGuildMembers(auid, data, all_members):
    if not data:
        return
    guildData = GuildData()
    guildData.load( data )
    guildData.init( None )
    for m in guildData.GuildMemberKeeper.itervalues():
        if m.Person in all_members:
            all_members[m.Person].append(auid)
        else:
            all_members[m.Person] = [auid]
