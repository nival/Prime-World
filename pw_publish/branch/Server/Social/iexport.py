# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *

import tornado.ioloop
import tornado.options
from tornado.options import define, options
from itertools import repeat

##---------------------------------------------------------------------------------------------
from cluster_base import crc_hash
from party_const import getPartyFraction
##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IDataExport:
    """ очередь запросов на зеркалирование данных
    """
    # ------------- техническое  -------------------
    def __init__(self, *args, **kwargs):
        pass
        
    def destroy(self):
        """ грубо закрываем лавочку (прибиваем thread pool, очередь запросов и т.п.) """
        pass

    def fadeout(self, syncWait=0 ):
        """ постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool) """
        pass
        
    def isDone(self):
        """ прикрыта ли лавочка? """ 
        return True # пустышку можно прибивать в любой момент
        
    # ------------- API -------------------
    def exportHeroData(self, *args, **kwargs): 
        pass

    def exportHeroTalentSet(self, *args, **kwargs):
        pass
        
    def exportBuildingData(self, *args, **kwargs): 
        pass
        
    def exportGuildRating(self, *args, **kwargs):
        pass
        
    def exportPersonalData(self, *args, **kwargs):
        pass

    def deleteHeroData(self, *args, **kwargs):
        pass

    def deleteHeroTalentSetData(self, *args, **kwargs):
        pass

    def deleteBuildingData(self, *args, **kwargs):
        pass

    def deleteStatisticsData(self, *args, **kwargs):
        pass

    def exportTicketData(self, *args, **kwargs):
        pass

    def exportStatisticsData(self, *args, **kwargs):
        pass

    def exportRecommendedVassalsData(self, *args, **kwargs):
        pass

    def updateLegendNickname(self, *args, **kwargs):
        pass
        
##---------------------------------------------------------------------------------------------
## Интерфейс для общения с реальной sql-базой через async thread-pool.
# NB: пока что реализуем и IData здесь же, просто через отдельную таблицу tbl_brick в MySQL БД
class AsyncSqlDataExport(IDataExport):
    def __init__(self):
        self.loop = tornado.ioloop.IOLoop.instance()
        
    def destroy(self):
        self.loop.export.destroy()

    def fadeout(self, syncWait=0 ):
        self.loop.export.fadeout( syncWait )
            
    def isDone(self):
        """ прикрыта ли лавочка? """ 
        if ( not self.loop.export.threadsDone() ) or len(self.loop.export.replies): # остались бегающие threads или неразобранные ответы
            return False
        return True
    
    # ------------------ API -------------------------
    def exportHeroData(self, auid, hero_id, hero_ts_id, hero_crc, hero_rating, hero_class, hero_skin, now, hero_force, hero_level, hero_last_played,
            hero_health, hero_mana, hero_strength, hero_intellect, hero_agility, hero_cunning, hero_fortitude,
            hero_will, hero_attack_type, callback=None):
        query = u"""INSERT INTO tbl_user_hero_stats_2
            (`auid`,`hero_id`,`hero_ts_id`,`hero_crc`,`hero_rating`,`hero_class`,`hero_skin`,`timestamp`,`hero_force`,`hero_level`,`hero_last_played`, `hero_health`,
            `hero_mana`, `hero_strength`, `hero_intellect`, `hero_agility`, `hero_cunning`, `hero_fortitude`, `hero_will`,`hero_attack_type`)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"""
        args = (auid, hero_id, hero_ts_id, hero_crc, hero_rating, hero_class, hero_skin, now, hero_force, hero_level, hero_last_played, hero_health, hero_mana,
            hero_strength, hero_intellect, hero_agility, hero_cunning, hero_fortitude, hero_will, hero_attack_type)
        info("- exportHeroData args: %r", args)
        self.loop.export.addExec( query, callback, params=(auid,hero_id), args=args, opname="exportHeroData" )

    def exportHeroTalentSet(self, auid, timestamp, hero_id, talents, tsId, callback=None):
        query = u"""INSERT INTO tbl_user_hero_talentset
            (`auid`, `hero_id`, `timestamp`,`talent1`,`talent2`,`talent3`,`talent4`,`talent5`,`talent6`,`talent7`,
            `talent8`,`talent9`,`talent10`,`talent11`,`talent12`,`talent13`,`talent14`,`talent15`,
            `talent16`,`talent17`,`talent18`,`talent19`,`talent20`,`talent21`,`talent22`,`talent23`,
            `talent24`,`talent25`,`talent26`,`talent27`,`talent28`,`talent29`,`talent30`,`talent31`,
            `talent32`,`talent33`,`talent34`,`talent35`,`talent36`, `talentset_id`)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"""
        args = (auid, hero_id, timestamp, talents[1], talents[2], talents[3], talents[4], talents[5], talents[6], talents[7], talents[8], talents[9],
            talents[10], talents[11], talents[12], talents[13], talents[14], talents[15], talents[16], talents[17], talents[18], talents[19],
            talents[20], talents[21], talents[22], talents[23], talents[24], talents[25], talents[26], talents[27], talents[28], talents[29],
            talents[30], talents[31], talents[32], talents[33], talents[34], talents[35], talents[36], tsId)
        info("- exportHeroTalentSet args: %r", args)
        self.loop.export.addExec( query, callback, params=(auid, hero_id), args=args, opname="exportHeroTalentSet" )
        
    def exportBuildingData(self, auid, building_id, crc, building_level, timestamp, in_pocket, callback=None):
        query = """INSERT INTO `tbl_user_build_stats` (`auid`,`build_id`,`build_crc`,`build_level`,`timestamp`,`in_pocket`) VALUES (%s,%s,%s,%s,%s,%s)"""
        args = (auid, building_id, crc, building_level, timestamp, in_pocket)
        info("- exportBuildingData args %r", args)
        self.loop.export.addExec(query, callback, params=(auid,building_id), args=args, opname="exportBuildingData")
        
    def exportGuildRating(self, guild_id, rating, prev_rating, prev_place, guild_name, guild_short_name, guild_fraction, guild_num_members,
                          guild_max_members, guild_exp, guildLevel, levelPercent, position, positionChange, maxPosition, iconRevision,
                          leadAuid, shopLevel, suzerainAuid, suzerain_name, suzerain_short_name, suzerain_rating, is_locked,
                          siege_end_time, current_event_id, callback=None):
        guild_fraction_int = getPartyFraction(guild_fraction)
        timestamp = int(time.time())
        debug("- exportGuildRating (guild_id %s, guild_name %r, guild_short_name %r)" % (guild_id, guild_name, guild_short_name))
        query = u"""INSERT INTO tbl_guild_rating (`guild_id`,
                        `rating`, `prev_rating`, `prev_place`, `guild_name`, `guild_short_name`,
                        `fraction`, `num_members`, `max_members`, `timestamp`, `date`,
                        `guild_exp`, `guild_level`, `level_percent`, `position`, `position_change`,
                        `max_position`, `icon_revision`, `lead_auid`, `shop_level`, `suzerain`,
                        `suzerain_name`, `suzerain_short_name`, `suzerain_rating`, `is_locked`, `siege_end_time`,
                        `current_event_id`)
                    VALUES (%s,
                        %s, %s, %s, %s, %s,
                        %s, %s, %s, %s, DATE(FROM_UNIXTIME(%s)),
                        %s, %s, %s, %s, %s,
                        %s, %s, %s, %s, %s,
                        %s, %s, %s, %s, %s,
                        %s)
                    ON DUPLICATE KEY UPDATE
                        `rating`=%s, `prev_rating`=%s, `prev_place`=%s, `guild_name`=%s, `guild_short_name`=%s,
                        `num_members`=%s, `max_members`=%s, `timestamp`=%s, `guild_exp`=%s, `guild_level`=%s,
                        `level_percent`=%s, `position`=%s, `position_change`=%s, `max_position`=%s, `icon_revision`=%s,
                        `lead_auid`=%s, `shop_level`=%s, `suzerain`=%s, `suzerain_name`=%s, `suzerain_short_name`=%s,
                        `suzerain_rating`=%s, `is_locked`=%s, `siege_end_time`=%s, `current_event_id`=%s"""
        args = (guild_id,  # INSERT VALUES
                rating, prev_rating, prev_place, uniConvert(guild_name), uniConvert(guild_short_name),
                guild_fraction_int, guild_num_members, guild_max_members, timestamp, timestamp,
                guild_exp, guildLevel, levelPercent, position, positionChange,
                maxPosition, iconRevision, leadAuid, shopLevel, suzerainAuid,
                uniConvert(suzerain_name), uniConvert(suzerain_short_name), suzerain_rating, is_locked, siege_end_time,
                current_event_id,
                rating, prev_rating, prev_place, uniConvert(guild_name), uniConvert(guild_short_name),  # UPDATE
                guild_num_members, guild_max_members, timestamp, guild_exp, guildLevel,
                levelPercent, position, positionChange, maxPosition, iconRevision,
                leadAuid, shopLevel, suzerainAuid, uniConvert(suzerain_name), uniConvert(suzerain_short_name),
                suzerain_rating, is_locked, siege_end_time, current_event_id)
        info("- exportGuildRating args: %r", args)
        self.loop.export.addExec(query, callback, params=guild_id, args=args, opname="exportGuildRating")
        
    def exportPersonalData(self, auid, snid, snuid, nick, locale, country, region, city, allow_geo_rating,
                           fraction, reliability, age, dt_register, dt_login, dt_logout,
                           gender, lord_level, timestamp, dt_birth, dt_pay, sessions, silver, gold, perl, red_perl, resource1, resource2,
                           resource3, shard, population, is_developer, is_spectator, is_leaver, leaver_points, bad_behaviour_reason, callback=None):
        query = u"""INSERT INTO tbl_user_profile (`auid`,`snid`,`snuid`,`nickname`,`locale`,
                `geo_country`, `geo_region`, `geo_city`, `geo_rating_enabled`,
                `fraction`,`reliability`,`age`,`dt_register`,
                `dt_login`,`dt_logout`,`timestamp`,`gender`,`lord_level`,`dt_birth`,`dt_pay`,`sessions`,
                `silver`,`gold`,`perl`,`red_perl`,`resource1`,`resource2`,`resource3`, `shard`, `population`,`is_developer`,`is_spectator`,
                `is_leaver`, `leaver_points`,`bad_behaviour_reason`)
                 VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)
                 ON DUPLICATE KEY UPDATE
                `snid`=%s,`snuid`=%s,`nickname`=%s,`locale`=%s,
                `geo_country`=%s, `geo_region`=%s, `geo_city`=%s, `geo_rating_enabled`=%s,
                `fraction`=%s,`reliability`=%s,`age`=%s,`dt_register`=%s,`dt_login`=%s,`dt_logout`=%s,`timestamp`=%s,
                `gender`=%s,`lord_level`=%s, `dt_birth`=%s,`dt_pay`=%s,`sessions`=%s,
                `silver`=%s,`gold`=%s,`perl`=%s,`red_perl`=%s,`resource1`=%s,`resource2`=%s,`resource3`=%s,`shard`=%s,`population`=%s,
                `is_developer`=%s,`is_spectator`=%s, `is_leaver`=%s, `leaver_points`=%s, `bad_behaviour_reason`=%s"""
        args = (auid,
                snid, snuid, uniConvert(nick), locale, country, region, city, allow_geo_rating,
                fraction, reliability, age, dt_register, dt_login, dt_logout, timestamp,
                gender, lord_level, dt_birth, dt_pay, sessions, silver, gold, perl, red_perl, resource1, resource2, resource3, shard,
                population, is_developer, is_spectator, is_leaver, leaver_points,bad_behaviour_reason,
                snid, snuid, uniConvert(nick), locale, country, region, city, allow_geo_rating,
                fraction, reliability, age, dt_register, dt_login, dt_logout, timestamp, gender, lord_level, dt_birth, dt_pay,
                sessions, silver, gold, perl, red_perl, resource1, resource2, resource3, shard, population, is_developer, is_spectator,
                is_leaver, leaver_points, bad_behaviour_reason)
        # info("template: %r, params: %r, len(params)=%s" % (templ, params, len(params)))
        #query = templ % params
        info( "- exportPersonalData args: %r", args)
        self.loop.export.addExec(query, callback, args=args, params=auid, opname="exportPersonalData")

    """ --------Many--------"""
    def exportManyHeroData(self, args, params, callback=None):
        query = u"""INSERT INTO tbl_user_hero_stats_2
            (`auid`,`hero_id`,`hero_ts_id`,`hero_crc`,`hero_rating`,`hero_class`,`hero_skin`,`timestamp`,`hero_force`,`hero_level`,`hero_last_played`, `hero_health`,
            `hero_mana`, `hero_strength`, `hero_intellect`, `hero_agility`, `hero_cunning`, `hero_fortitude`, `hero_will`,`hero_attack_type`)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"""
        debug("- exportManyHeroData args: %r", args)
        info("- exportManyHeroData args count: %r", len(args))
        self.loop.export.addExecMany( query, callback, params=params, args=args, opname="exportManyHeroData" )

    def exportManyHeroTalentSet(self, args, params, callback=None):
        query = u"""INSERT INTO tbl_user_hero_talentset
            (`auid`, `hero_id`, `timestamp`,`talent1`,`talent2`,`talent3`,`talent4`,`talent5`,`talent6`,`talent7`,
            `talent8`,`talent9`,`talent10`,`talent11`,`talent12`,`talent13`,`talent14`,`talent15`,
            `talent16`,`talent17`,`talent18`,`talent19`,`talent20`,`talent21`,`talent22`,`talent23`,
            `talent24`,`talent25`,`talent26`,`talent27`,`talent28`,`talent29`,`talent30`,`talent31`,
            `talent32`,`talent33`,`talent34`,`talent35`,`talent36`, `talentset_id`)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"""

        debug("- exportManyHeroTalentSet args : %r", args)
        info("- exportManyHeroTalentSet args count: %r", len(args))
        self.loop.export.addExecMany( query, callback, params=params, args=args, opname="exportManyHeroTalentSet" )

    def exportManyBuildingData(self, args, params, callback=None):
        query = """INSERT INTO `tbl_user_build_stats` (`auid`,`build_id`,`build_crc`,`build_level`,`timestamp`,`in_pocket`) VALUES (%s,%s,%s,%s,%s,%s)"""
        info("- exportManyBuildingData args count %r", len(args))
        self.loop.export.addExecMany(query, callback, params=params, args=args, opname="exportManyBuildingData")

    def exportManyGuildRating(self, args, params, callback=None):
        #guild_fraction_int = getPartyFraction(guild_fraction)
        #timestamp = int(time.time())
        query = u"""INSERT INTO tbl_guild_rating(`guild_id`,
                        `rating`, `prev_rating`, `prev_place`, `guild_name`, `guild_short_name`,
                        `fraction`, `num_members`, `max_members`, `timestamp`, `date`,
                        `guild_exp`, `guild_level`, `level_percent`, `position`, `position_change`,
                        `max_position`, `icon_revision`, `lead_auid`, `shop_level`, `suzerain`,
                        `suzerain_name`, `suzerain_short_name`, `suzerain_rating`, `is_locked`, `siege_end_time`,
                        `current_event_id`)
                    VALUES (%s,
                        %s, %s, %s, %s, %s,
                        %s, %s, %s, %s, DATE(FROM_UNIXTIME(%s)),
                        %s, %s, %s, %s, %s,
                        %s, %s, %s, %s, %s,
                        %s, %s, %s, %s, %s,
                        %s)
                    ON DUPLICATE KEY UPDATE
                        `rating`=%s, `prev_rating`=%s, `prev_place`=%s, `guild_name`=%s, `guild_short_name`=%s,
                        `num_members`=%s, `max_members`=%s, `timestamp`=%s, `guild_exp`=%s, `guild_level`=%s,
                        `level_percent`=%s, `position`=%s, `position_change`=%s, `max_position`=%s, `icon_revision`=%s,
                        `lead_auid`=%s, `shop_level`=%s, `suzerain`=%s, `suzerain_name`=%s, `suzerain_short_name`=%s,
                        `suzerain_rating`=%s, `is_locked`=%s, `siege_end_time`=%s, `current_event_id`=%s"""
        info("- exportManyGuildRating args: %r", args)
        self.loop.export.addExecMany(query, callback, params=params, args=args, opname="exportManyGuildRating")

    def exportManyPersonalData(self, args, params, callback=None):
        query = u"""INSERT INTO tbl_user_profile (`auid`,`snid`,`snuid`,`nickname`,`locale`,
                `geo_country`, `geo_region`, `geo_city`, `geo_rating_enabled`,
                `fraction`,`reliability`,`age`,`dt_register`,
                `dt_login`,`dt_logout`,`timestamp`,`gender`,`lord_level`,`dt_birth`,`dt_pay`,`sessions`,
                `silver`,`gold`,`perl`,`red_perl`,`resource1`,`resource2`,`resource3`,`population`,`is_developer`,`is_spectator`,
                `is_leaver`, `leaver_points`,`bad_behaviour_reason`)
                 VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)
                 ON DUPLICATE KEY UPDATE
                `snid`=%s,`snuid`=%s,`nickname`=%s,`locale`=%s,
                `geo_country`=%s, `geo_region`=%s, `geo_city`=%s, `geo_rating_enabled`=%s,
                `fraction`=%s,`reliability`=%s,`age`=%s,`dt_register`=%s,`dt_login`=%s,`dt_logout`=%s,`timestamp`=%s,
                `gender`=%s,`lord_level`=%s, `dt_birth`=%s,`dt_pay`=%s,`sessions`=%s,
                `silver`=%s,`gold`=%s,`perl`=%s,`red_perl`=%s,`resource1`=%s,`resource2`=%s,`resource3`=%s,`population`=%s,
                `is_developer`=%s,`is_spectator`=%s, `is_leaver`=%s, `leaver_points`=%s, `bad_behaviour_reason`=%s"""

        # info("template: %r, params: %r, len(params)=%s" % (templ, params, len(params)))
        #query = templ % params
        info( "- exportManyPersonalData args: %r", args)
        self.loop.export.addExecMany(query, callback, args=args, params=params, opname="exportManyPersonalData")
        """--------Many--------"""

    def deleteHeroData(self, auid, timestamp, callback=None):
        query = u"DELETE FROM tbl_user_hero_stats_2 WHERE `auid`=%s AND `timestamp`<%s"
        debug( "- deleteHeroData (auid=%s, timestamp=%s) query: %r", auid, timestamp, query)
        self.loop.export.addExec(query, callback, params=(auid), args=(auid, timestamp), opname="deleteHeroData")

    def deleteHeroTalentSetData(self, auid, timestamp, callback=None):
        query = u"DELETE FROM tbl_user_hero_talentset WHERE `auid`=%s AND `timestamp`<%s"
        debug( "- deleteHeroTalentSetData (auid=%s, timestamp=%s) query: %r", auid, timestamp, query)
        self.loop.export.addExec(query, callback, params=(auid), args=(auid, timestamp), opname="deleteHeroTalentSetData")

    def deleteBuildingData(self, auid, timestamp, callback=None):
        query = u"DELETE FROM tbl_user_build_stats WHERE `auid`=%s AND `timestamp`<%s"
        debug("- deleteBuildingData (auid=%s, timestamp=%s) query: %r", auid, timestamp, query)
        self.loop.export.addExec(query, callback, params=(auid), args=(auid, timestamp), opname="deleteBuildingData")

    def deleteStatisticsData(self, auid, timestamp, callback=None):
        query = u"DELETE FROM tbl_user_statistics WHERE `auid`=%s AND `timestamp`<%s"
        debug("- deleteStatisticsData (auid=%s, timestamp=%s) query: %r", auid, timestamp, query)
        self.loop.export.addExec(query, callback, params=(auid), args=(auid, timestamp), opname="deleteStatisticsData")

    def deleteGuildData(self, guild_id, timestamp, callback=None):
        query = u"DELETE FROM tbl_guild_rating WHERE `guild_id`=%s AND `timestamp`<%s"
        debug("- deleteGuildData (guild_id=%s, timestamp=%s) query: %r", guild_id, timestamp, query)
        self.loop.export.addExec(query, callback, params=(guild_id), args=(guild_id, timestamp), opname="deleteGuildData")

    def exportTicketData(self, auid, ticket, ts, boughtType, state, wins, losses, gold, maxDuration, callback=None):
        query = u"""INSERT INTO `tournaments` (`auid`, `ticket_id`, `timestamp`, `bought_type`, `state`, `wins`, `losses`, `gold`, `max_duration`)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s)
            ON DUPLICATE KEY UPDATE `timestamp`=%s, `bought_type`=%s, `state`=%s, `wins`=%s, `losses`=%s, `gold`=%s, `max_duration`=%s"""
        info("exportTicketData: auid=%s, ticket=%s, ts=%s, bt=%s, state=%s, wins=%s, losses=%s, gold=%s, maxDur=%s",
             auid, ticket, ts, boughtType, state, wins, losses, gold, maxDuration)
        self.loop.export.addExec(query, callback,
                                 args=(auid, ticket, ts, boughtType, state, wins, losses, gold, maxDuration,
                                                     ts, boughtType, state, wins, losses, gold, maxDuration),
                                 params=auid, opname="exportTicketData")


    def exportStatisticsData(self, auid, timestamp, kills, damageDealedTotal, neutralCreepsKilled, enemyCreepsKilled,
                    totalNumTowersKilled, totalNumQuartersDestroyed, numberOfWins, healedAmount, totalMedalsCountDone,
                    assists, score, money, flagsRaised, damageReceivedTotal, rareTalents, callback=None):
        query = """INSERT INTO tbl_user_statistics (`auid`,`timestamp`,`kills`,`damage_dealed_total`,`neutral_creeps_killed`,
            `enemy_creeps_killed`,`total_num_towers_killed`,`total_num_quarters_destroyed`,`main_buildings_destroyed`,
            `healed_amount`,`total_medals_done`,`assists`,`hero_score`,`money`,`flags_raised`,`damage_received`,
            `rare_talents`)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)"""
        args = (auid, timestamp, kills, damageDealedTotal, neutralCreepsKilled,
            enemyCreepsKilled, totalNumTowersKilled, totalNumQuartersDestroyed, numberOfWins, healedAmount, totalMedalsCountDone,
            assists, score, money, flagsRaised, damageReceivedTotal, rareTalents)
        info("- exportStatistics args %r", args)
        self.loop.export.addExec(query, callback, params=(auid), args=args, opname="exportStatistics")

    def getRecommendedGuildsInfo(self, auids, callback=None):
        query = """SELECT t.`guild_id`, t.`rating`, t.`guild_name`, t.`guild_short_name`, t.`position`, t.`guild_level`,
                   t.`position_change`, t.`icon_revision`, t.`shop_level`, t.`num_members`, r.`locale`, r.`message`
                   FROM tbl_guild_rating t
                   JOIN `tbl_guild_recruitment` r ON t.`guild_id` = r.`guild_id`
                   WHERE t.`guild_id` IN ({0}) AND t.`date` >=  CURRENT_DATE - INTERVAL 1 DAY""".format(','.join(repeat("%s", len(auids))))
        debug("- getGuildsInfo (auids %s) query %r", auids, query)
        self.loop.export.addQuery(query, callback, params=auids, args=auids, opname="getGuildsInfo")

    def getGuildsInfo(self, auids, callback=None):
        query = """SELECT t.`guild_id`, t.`rating`, t.`guild_name`, t.`guild_short_name`, t.`position`, t.`guild_level`,
                   t.`position_change`, t.`icon_revision`, t.`suzerain`, t.`shop_level`, t.`num_members`
                   FROM tbl_guild_rating t
                   WHERE t.`guild_id` IN ({0}) AND t.`date` >=  CURRENT_DATE - INTERVAL 1 DAY""".format(','.join(repeat("%s", len(auids))))
        debug("- getGuildsInfo (auids %s) query %r", auids, query)
        self.loop.export.addQuery(query, callback, params=auids, args=auids, opname="getGuildsInfo")

    def getExtendedGuildsInfo(self, auids, callback=None):
        query = """SELECT t.`guild_id`, t.`rating`, t.`guild_name`, t.`guild_short_name`, t.`position`, t.`position_change`,t. `icon_revision`,
                   t.`suzerain`, t.`suzerain_name`, t.`suzerain_short_name`, t.`suzerain_rating`, t.`is_locked`, t.`siege_end_time`
                   FROM tbl_guild_rating t
                   WHERE t.`guild_id` IN ({0}) AND t.`date` >=  CURRENT_DATE - INTERVAL 1 DAY""".format(','.join(repeat("%s", len(auids))))
        debug("- getExtendedGuildsInfo (auids %s) query %r", auids, query)
        self.loop.export.addQuery(query, callback, params=auids, args=auids, opname="getExtendedGuildsInfo")

    def exportRecommendedVassalsData(self, vauids, minR, maxR, limit, callback=None):
        mask = ""
        args = (minR, maxR, limit)
        if vauids:
            mask = " `guild_id` NOT IN (%s) AND " % ','.join(repeat("%s", len(vauids)))
            args = tuple(vauids) + args

        query = """SELECT t.`guild_id`, t.`guild_name`, t.`guild_short_name`, t.`guild_level`, t.`rating`, t.`position`, t.`position_change`,
                   t.`shop_level`, t.`num_members`, t.`icon_revision`,
                   t.`suzerain`, t.`suzerain_name`, t.`suzerain_short_name`, t.`suzerain_rating`, t.`is_locked`, t.`siege_end_time`, t.`timestamp`
                   FROM tbl_guild_rating t
                   WHERE {0} t.`date` >=  CURRENT_DATE - INTERVAL 1 DAY AND t.`rating` > %s AND IF(t.`suzerain`>0, t.`suzerain_rating`, t.`rating`) < %s
                   ORDER BY t.`rating` DESC LIMIT %s """.format(mask)
        info("- exportRecommendedVassalsData (args: %s, vauids: %s)..." , args, vauids)
        self.performQuery(query, args, callback )


    def performQuery(self, query, args, callback=None):
        debug("- performQuery (args %s) query %r", args, query)
        self.loop.export.addQuery(query, callback, params=args, args=args, opname="performQuery")


    def removeGuildInfoOnGuildDelete(self, guildAuid, callback = None):
        query1 = """DELETE FROM tbl_guild_rating WHERE `guild_id`=%s"""
        query2 = """DELETE FROM tbl_guild_recruitment WHERE `guild_id`=%s"""
        debug("- removeGuildInfoOnGuildDelete (guildAuid %s) query1 %r, query2 %r", guildAuid, query1, query2)
        self.loop.export.addExec(query1, callback, params=(guildAuid,), args=(guildAuid,), opname="removeGuildInfoOnGuildDelete")
        self.loop.export.addExec(query2, callback, params=(guildAuid,), args=(guildAuid,), opname="removeGuildInfoOnGuildDelete")

    def getHeroWithMaxRating(self, heroPersistentId, invalidAuids, callback=None):
        mask = ""
        args = (heroPersistentId, )
        if len(invalidAuids):
            mask = " h.`auid` NOT IN (%s) AND" % ','.join(repeat("%s", len(invalidAuids)))
            args = tuple (invalidAuids) + args
        query = """SELECT h.`auid`, h.`hero_crc`, h.`hero_id`, h.`hero_rating`, h.`hero_skin`, h.`hero_force`,
                   h.`hero_level`, h.`hero_health`, h.`hero_mana`, h.`hero_strength`, h.`hero_intellect`,
                   h.`hero_agility`, h.`hero_cunning`, h.`hero_fortitude`, h.`hero_will`, ts.*, pr.`nickname`
                   FROM tbl_user_hero_stats_2 h force index for join (Index_hero_crc,Index_merge)
                   JOIN tbl_user_hero_talentset AS ts
                   ON (h.`auid` = ts.`auid` and h.`hero_id` = ts.`hero_id` and h.`hero_ts_id` = ts.`talentset_id`)
                   JOIN tbl_user_profile AS pr
                   ON h.`auid` = pr.`auid`
                   WHERE {0} h.`hero_crc` = %s AND FROM_UNIXTIME(h.`hero_last_played`) >= DATE_SUB(CURRENT_DATE, INTERVAL 7 DAY)
                   ORDER BY h.`hero_rating` DESC, h.`hero_force` DESC, h.`hero_ts_id` ASC LIMIT 1
                   """.format(mask)
        debug("- getHeroWithMaxRating (invalidAuids %s) query %r", invalidAuids, query)
        self.loop.export.addQuery(query, callback, params=args, args=args, opname="getHeroWithMaxRating")

    def updateGuildRecruitmentParams(self, guildAuid, locale, message, minRating, callback=None):
        args = (locale, message, minRating, guildAuid)
        debug("- updateGuildRecruitmentParams %r", args)
        self.loop.export.addExec(
            """UPDATE tbl_guild_recruitment SET `locale`=%s, `message`=%s, `min_rating`=%s WHERE `guild_id`=%s""",
            callback, params=args, args=args, opname="updateGuildRecruitmentParams")

    def updateGuildRecruitmentLocale(self, guildAuid, locale, callback=None):
        args = (locale, guildAuid)
        debug("- updateGuildRecruitmentLocale %r", args)
        self.loop.export.addExec("""UPDATE tbl_guild_recruitment SET `locale`=%s WHERE `guild_id`=%s""",
                                 callback, params=args, args=args, opname="updateGuildRecruitmentLocale")

    def updateGuildRecruitmentMessage(self, guildAuid, message, callback=None):
        args = (message, guildAuid)
        debug("- updateGuildRecruitmentMessage %r", args)
        self.loop.export.addExec("""UPDATE tbl_guild_recruitment SET `message`=%s WHERE `guild_id`=%s""",
                                 callback, params=args, args=args, opname="updateGuildRecruitmentParams")

    def updateGuildRecruitmentMinRating(self, guildAuid, minRating, callback=None):
        args = (minRating, guildAuid)
        debug("- updateGuildRecruitmentMinRating %r", args)
        self.loop.export.addExec("""UPDATE tbl_guild_recruitment SET `min_rating`=%s WHERE `guild_id`=%s""",
                                 callback, params=args, args=args, opname="updateGuildRecruitmentParams")

    def setGuildRecruitmentParams(self, guildAuid, locale, callback=None):
        query = """INSERT INTO tbl_guild_recruitment (guild_id, message, locale, min_rating) VALUES (%s,'',%s,0)"""
        args = (guildAuid, locale)
        debug("- setGuildRecruitmentParams query %r", query)
        self.loop.export.addExec(query, callback, params=args, args=args, opname="setGuildRecruitmentParams")

    def updateLegendRatingInfo(self, auid, hero_id, rating, nickname, season_id, callback=None):
        args = (str(auid), str(hero_id), str(rating), uniConvert(nickname), str(season_id))
        query = """call `pw_stat`.`update_league_info`( %s, %s, %s, %s, %s )"""
        debug("- updateLegendRatingInfo query %s with args %r", query, args)
        self.loop.export.addExec(query, callback, params=args, args=args, opname="updateLegendRatingInfo")

    def getLegendRatingInfo(self, hero_id, auid, season_id, callback=None):
        query = """SELECT * from
                   ( SELECT  l.uid,
                    l.rating,
                    l.hero_id,
                    @curRow := @curRow + 1 AS league_place
                    FROM    tbl_seasons_league l
                    JOIN    (SELECT @curRow := 0) r
                    WHERE hero_id = {0} AND season = {1}
                    ORDER BY rating DESC ) as x
                    WHERE (x.`uid` = {2})""".format(hero_id, season_id, auid)
        debug("- getLegendRatingInfo (auids %s) query %r", auid, query)
        self.loop.export.addQuery(query, callback, opname="getLegendRatingInfo")

    def updateTradeEventExperience(self, auid, event_id, experience, callback=None):
        args = (str(auid), str(event_id), str(experience))
        query = """call `pw_stat`.`add_tradeevent_experience`( %s, %s, %s )"""
        debug("- updateTradeEventExperience query %s with args %r", query, args)
        self.loop.export.addExec(query, callback, params=args, args=args, opname="updateTradeEventExperience")

    def getTradeEventPlace(self, auid, event_id, limit, callback=None):
        args = (str(auid), str(event_id), str(limit))
        query = """call `pw_stat`.`get_tradeevent_place`( %s, %s, %s )"""
        debug("- getTradeEventTop query %s with args %r", query, args)
        self.loop.export.addQuery(query, callback, params=args, args=args, opname="getTradeEventTop")

    def updateSeasonEventProgress(self, auid, event_id, amount, callback=None):
        args = (str(auid), str(event_id), str(amount))
        query = """call `pw_stat`.`add_seasonevent_progress`( %s, %s, %s )"""
        debug("- updateSeasonEventProgress query %s with args %r", query, args)
        self.loop.export.addExec(query, callback, params=args, args=args, opname="updateSeasonEventProgress")

    def getSeasonEventPlace(self, auid, event_id, limit, callback=None):
        args = (str(auid), str(event_id), str(limit))
        query = """call `pw_stat`.`get_seasonevent_place`( %s, %s, %s )"""
        debug("- getSeasonEventPlace query %s with args %r", query, args)
        self.loop.export.addQuery(query, callback, params=args, args=args, opname="getSeasonEventPlace")

    def getLegendPlaces(self, hero_id, auid, start_place, count, season_id, callback=None):
        query = """SELECT rating, hero_id, @own_auid:={0} AS own_auid from
                   ( SELECT  l.uid,
                    l.rating,
                    l.hero_id,
                    @curRow := @curRow + 1 AS league_place
                    FROM    tbl_seasons_league l
                    JOIN    (SELECT @curRow := 0) r
                    WHERE hero_id = {1} AND season = {2}
                    ORDER BY rating DESC ) as x
                    LIMIT {3},{4}""".format(auid, hero_id, season_id, int(start_place), int(count))
        #query = ""
        debug("- getLegendPlace query %r", query)
        self.loop.export.addQuery(query, callback, opname="getLegendPlace")

    def updateLegendNickname(self, auid, nickname, callback=None):
        args = (uniConvert(nickname), str(auid))
        self.loop.export.addExec("""UPDATE tbl_seasons_league SET `nickname`=%s WHERE `uid`=%s""",
                                    callback, params=args, args=args, opname="updateLegendNickname")