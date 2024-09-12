# -*- coding: utf-8 -*-
__author__ = 'danil.lavrentyuk'
"Helper functions for SQL queries."

from base.helpers import *
import time
from itertools import repeat

class GuildListQuery(object):
   # Used for multi-inheritance with SubAction's subclass, using it's self.acc and self.arguments
    _guildSortCriteriaMap = dict()

    #####
    # nameFilter - подстрока в полном или кратком имени клана
    # ratingFilter - интервал от [i] до [i+1] в списке ['GuildRatingRanges']['Item'] в acc.SD
    # statusFilter - 0 - Не в осаде, 1 - В бою, 2 - Бой закончился, принимаем решение
    # suzerenFilter - подстрока в полном или кратком имени клана сюзерена
    # suzerenRatingFilter - интервал рейтинга сюзерена
    # sortCriteria - критерий сортировки, число из GuildsListSortCriteria
    # order - сортировка DESC если любое True, ASC если False
    # position - "постраничность" запроса, результаты от position до position+GUILDS_IN_LIST_PER_REQUEST

    @classmethod
    def setSortCriteria(cls, criteria):
        if not cls._guildSortCriteriaMap:
            cls._guildSortCriteriaMap = {
                int(criteria.Place): 't.`position`',
                int(criteria.Name): 't.`guild_name`',
                int(criteria.Rating): 't.`rating`',
                int(criteria.Status): 't.`siege_end_time`',
                int(criteria.SuzerainName): 't.`suzerain_name`',
                int(criteria.SuzerainRating): 't.`suzerain_rating`',
                int(criteria.PrevRating): 't.`prev_rating`'
            }


    def createSQLQuery(self, guildAuids=()):
        arguments = self.arguments

        auid_filter = "`guild_id` IN ({0}) AND".format(','.join(repeat("%s", len(guildAuids)))) if guildAuids else ''

        query = """SELECT t.`guild_id`, t.`rating`, t.`guild_name`, t.`guild_short_name`, t.`position`,
                          t.`position_change`, t.`icon_revision`, t.`num_members`, t.`shop_level`, t.`guild_level`,
                          t.`suzerain`, t.`suzerain_name`, t.`suzerain_short_name`, t.`suzerain_rating`, t.`is_locked`,
                          t.`siege_end_time`, t.`current_event_id`, t.`prev_rating`, t.`prev_place`
                   FROM `tbl_guild_rating` t WHERE {0} t.`date` >=  CURRENT_DATE - INTERVAL 1 DAY""".format(auid_filter)

        args = list(guildAuids)
        conditions = []

        if arguments.nameFilter != "":
            args.append('%' + arguments.nameFilter + '%')
            args.append('%' + arguments.nameFilter + '%')
            conditions.append("""(t.`guild_short_name` LIKE %s OR t.`guild_name` LIKE %s)""")

        if arguments.ratingFilter != -1:
            botRate, topRate = self.acc.SD.getRatingFilterBorders(arguments.ratingFilter) # XXX!
            if topRate == 0:
                conditions.append("""t.`rating` > %s""" % botRate)
            else:
                conditions.append("""t.`rating` BETWEEN %s AND %s""" % (botRate, topRate))

        if arguments.statusFilter != -1:
            if arguments.statusFilter == 0:
                conditions.append("""t.`siege_end_time` = 0""")
            elif arguments.statusFilter == 1:
                conditions.append("""t.`siege_end_time` > %d""" % int(time.time()))
            elif arguments.statusFilter == 2:
                conditions.append("""(t.`is_locked` = 1 AND t.`siege_end_time` != 0)""")

        if arguments.suzerenFilter != "":
            args.append('%' + arguments.suzerenFilter + '%')
            args.append('%' + arguments.suzerenFilter + '%')
            conditions.append("""(t.`suzerain_short_name` LIKE %s OR t.`suzerain_name` LIKE %s)""")

        if arguments.suzerenRatingFilter != -1:
            botRate, topRate = self.acc.SD.getRatingFilterBorders(arguments.suzerenRatingFilter)
            if topRate == 0:
                conditions.append("""t.`suzerain_rating` > %s""" % botRate)
            else:
                conditions.append("""t.`suzerain_rating` BETWEEN %s AND %s""" % (botRate, topRate))

        if conditions:
            query += " AND " + (" AND ".join(conditions))

        if arguments.sortCriteria != -1:
            criteria = self._guildSortCriteriaMap.get(arguments.sortCriteria, "")
            if criteria:
                query += " ORDER BY %s" % criteria
                if arguments.order:
                    query += """ DESC"""
            else:
                warn("Get_guilds_list: unknown sortCriteria '%s', ignored", arguments.sortCriteria)

        query += """ LIMIT %d,%d""" % (
            arguments.position, arguments.position + self.acc.getConfig().GUILDS_IN_LIST_PER_REQUEST)
        return query, args


class RecommendedGuildListQuery(object):
   # Used for multi-inheritance with SubAction's subclass, using it's self.acc and self.arguments
    _guildSortCriteriaMap = dict()

    #####
    # nameFilter - подстрока в полном или кратком имени клана
    # ratingFilter - интервал от [i] до [i+1] в списке ['GuildRatingRanges']['Item'] в acc.SD
    # localeFilter - язык, на котором говорят в клане (в списке ['GuildRecruitment']['locales']['Item']
    # sortCriteria - критерий сортировки, число из GuildsListSortCriteria
    # order - сортировка DESC если любое True, ASC если False
    # position - "постраничность" запроса, результаты от position до position+GUILDS_IN_LIST_PER_REQUEST

    @classmethod
    def setSortCriteria(cls, criteria):
        if not cls._guildSortCriteriaMap:
            cls._guildSortCriteriaMap = {
                int(criteria.Position): 't.`position`',
                int(criteria.Name): 't.`guild_name`',
                int(criteria.Locale): 'r.`locale`',
                int(criteria.Rating): 't.`rating`',
                int(criteria.Level): 't.`guild_level`',
                int(criteria.PlayersCount): 't.`num_members`'
            }


    def createSQLQuery(self, maxRating, guildAuids=[]):
        arguments = self.arguments
        auid_filter = "t.`guild_id` NOT IN ({0}) AND".format(','.join(repeat("%s", len(guildAuids)))) if guildAuids else ''
        query = """SELECT
            t.`guild_id`, t.`rating`, t.`guild_name`, t.`guild_short_name`, t.`position`,
            t.`position_change`, t.`icon_revision`, t.`num_members`,t.`guild_level`, r.`locale`, r.`message`
            FROM `tbl_guild_rating` t
            JOIN `tbl_guild_recruitment` r ON t.`guild_id` = r.`guild_id`
            WHERE {0}
            t.`num_members` < t.`max_members` AND t.`date` >= CURRENT_DATE - INTERVAL 1 DAY AND r.`min_rating` <= {1}
        """.format(auid_filter, maxRating)

        args = list(guildAuids)
        conditions = []

        if arguments.nameFilter != "":
            args.append('%' + arguments.nameFilter + '%')
            args.append('%' + arguments.nameFilter + '%')
            conditions.append("""(t.`guild_short_name` LIKE %s OR t.`guild_name` LIKE %s)""")

        if arguments.ratingFilter != -1:
            botRate, topRate = self.acc.SD.getRatingFilterBorders(arguments.ratingFilter) # XXX!
            if topRate == 0:
                conditions.append("""t.`rating` > %s""" % botRate)
            else:
                conditions.append("""t.`rating` BETWEEN %s AND %s""" % (botRate, topRate))

        if arguments.localeFilter != "":
            conditions.append("""r.`locale` = %s""")
            args.append(arguments.localeFilter)

        if conditions:
            query += " AND " + (" AND ".join(conditions))

        if arguments.sortCriteria != -1:
            criteria = self._guildSortCriteriaMap.get(arguments.sortCriteria, "")
            if criteria:
                query += " ORDER BY %s" % criteria
                if arguments.order:
                    query += """ DESC"""
            else:
                warn("Get_recommended_guilds_list: unknown sortCriteria '%s', ignored", arguments.sortCriteria)

        query += """ LIMIT %d,%d""" % (
            arguments.position, self.acc.getConfig().GUILDS_IN_LIST_PER_REQUEST)
        return query, args

class LegendLeagueQuery(object):
   # Used for multi-inheritance with SubAction's subclass, using it's self.acc and self.arguments
    _legendLeagueSortCriteriaMap = dict()

    #####
    # nameFilter - подстрока в полном или кратком имени клана
    # ratingFilter - интервал от [i] до [i+1] в списке ['GuildRatingRanges']['Item'] в acc.SD
    # localeFilter - язык, на котором говорят в клане (в списке ['GuildRecruitment']['locales']['Item']
    # sortCriteria - критерий сортировки, число из GuildsListSortCriteria
    # order - сортировка DESC если любое True, ASC если False
    # position - "постраничность" запроса, результаты от position до position+GUILDS_IN_LIST_PER_REQUEST

    @classmethod
    def setSortCriteria(cls, criteria):
        if not cls._legendLeagueSortCriteriaMap:
            cls._legendLeagueSortCriteriaMap = {
                int(criteria.Place): 'league_place',
                int(criteria.Name): 'nickname',
            }

    def createSQLQuery(self):
        arguments = self.arguments
        query = """SELECT * from (
                    SELECT t.`uid`,
                    t.`rating`,
                    t.`hero_id`,
                    t.`nickname`,
                    t.`prev_league_place`,
                    @curRow := @curRow + 1 AS league_place
                    FROM `tbl_seasons_league` t
                    JOIN    (SELECT @curRow := 0) r
                    WHERE hero_id = {0} AND season = {1}
                    ORDER BY rating  DESC ) as x
                    """.format(arguments.heroidFilter, self.acc.SD.getCurrentSeasonId())

        conditions = []
        args = []

        if arguments.nameFilter != "":
            args.append('%' + arguments.nameFilter + '%')
            conditions.append("""(x.`nickname` LIKE %s)""")

        if arguments.auidFilter != -1:
            conditions.append("""x.uid = %s""" % self.arguments.auidFilter)

        if conditions:
            query += " WHERE " + (" AND ".join(conditions))

        sort_criteria = int(arguments.sortCriteria)
        if sort_criteria != -1:
            if sort_criteria == 1:
                query += " ORDER BY x.`nickname`"
            else:
                if sort_criteria == 0:
                    query += " ORDER BY x.`league_place`"
                else:
                    warn("Get_legendary_league: unknown sortCriteria %d, ignored", sort_criteria)

            if arguments.order:
                query += """ DESC"""

        if arguments.auidFilter == -1:
            query += """ LIMIT %d,%d""" % (
                arguments.position, self.acc.getConfig().GUILDS_IN_LIST_PER_REQUEST)

        debug("query for leagues = %s", query)
        return query, args
