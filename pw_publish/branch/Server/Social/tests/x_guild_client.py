# -*- coding: utf-8 -*-

import socket, ssl, pprint, time, sys, os
import unittest
import hashlib
import urllib2
import random
import logging

os.chdir('..')
sys.path.append('.')

from base.helpers import *

from friendsdata.FriendsData import FriendsData
from party.PartyData import PartyData
from modeldata.ModelData import ModelData
from guild.GuildData import GuildData

from modeldata.change_applicator import ModelChangeApplicator

import CC
import EC
import MM

from x_client_base import *

# ------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------
class Test_GuildService(unittest.TestCase):
    def test_guild_create_destroy(self):
        print "- test_guild_create_destroy"

        SNUID1 = '730742963'
        SNTOKEN1 = 'CAAB9M8ptmXMBAIzjqPEMGXXkGIZAtUv8YlebXOAkSyAyimaYtrhYW5vq8iTg9WpVrEFGY9XhAFC7XllVZAq2SXUxz7ajMJHKiLOkG4kZA1oRwBZAarNT0Cw1OxVS5CRftS93ZC7AaIBXc3KZB77JYhdF95RUZBAKX6lYY4XxcDF5bVgbUQldfsFlr9dyslvGEYZD'

        #~ SNUID2 = '100003297559974'
        #~ SNTOKEN2 = 'AAAB9M8ptmXMBAKLjZBe9ViZATa3j0miIp0BkIZA11325znpxQXQ9hdZAy1CnvZB3wgik1G2cqZCV9HzZBqiKJuZCqwUGZAZCD8LvYdZBRDWPBr2ZAgZDZD'

        acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 )

        time.sleep(2.0) # пусть пройдет апдейт

        AUID1 = acc1.auid

        try:
            reply = accGet( AUID1, "keepalive" )
            silver1 = acc1.model.Resources.Silver

            # logLevel( logging.INFO )

            #~ reply = accGet( AUID1, "give_fame", value=1234 )
            #~ reply = accGet( AUID2, "give_fame", value=2345 )

            GUILD_CREATE_PRICE = 150000
            reply = accGet( AUID1, "give_resource", resource="Silver", value=GUILD_CREATE_PRICE )

            reply = accGet( AUID1, "keepalive" )
            silver2 = acc1.model.Resources.Silver
            assert( silver2 == silver1 + GUILD_CREATE_PRICE)

            GUILD_FULLNAME = "DanTestGuild"
            GUILD_SHORTNAME = "DTG"

            reply = accGet( AUID1, "guild_create", fullname=GUILD_FULLNAME, shortname=GUILD_SHORTNAME )
            time.sleep(2.0) # пусть пройдут необх. апдейты

            reply = accGet( AUID1, "keepalive" )
            silver2 = acc1.model.Resources.Silver
            assert( silver2 == silver1 ) # снялись обратно монеты

            assert( acc1.guilddata )
            assert( acc1.guilddata.GuildAuid )
            assert( acc1.guilddata.GuildInfo.FullName == GUILD_FULLNAME )
            assert( acc1.guilddata.GuildInfo.ShortName == GUILD_SHORTNAME )
            assert( acc1.guilddata.Owner.Person == AUID1 )
            assert( acc1.guilddata.findMemberByAuid( AUID1 ) )
            assert( getFriend( acc1, AUID1 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в нашей персоне из FriendsData должна появиться аббревиатура гильдии
            print "-- guild after create: ok"

            # шлем гильдии письмо:
            msg_1_2 = json_dumps( [{"type":"test_g_awards", "text":"ONLINE MESSAGE"}] )
            reply = post( "send_nl", project=CC.SEX_PW_GUILD_PROJECT, recipient=acc1.guilddata.GuildAuid, sender="pw", body=msg_1_2, server=X_SERVER1 )
            assert( reply.get('ok', -1) == 1 )
            CLAN_POINT = 11
            msg_2_2 = json_dumps([{"awards":[{"count":CLAN_POINT,"id":0,"type":21}],"count":1,"roll_id":"6269234965189708624","tm_expire":86400,"type":"s_guild_awards"}])
            reply = post( "send_nl", project=CC.SEX_PW_GUILD_PROJECT, recipient=acc1.guilddata.GuildAuid, sender="pw_pvx", body=msg_2_2, server=X_SERVER1 )
            assert( reply.get('ok', -1) == 1 )
        except:
            catch()

        #~ time.sleep(30.0) # пусть успеют потикать отладочные sex.touch

        #--------------------------------------------------------
        logLevel()
        reply = accGet( AUID1, "logout" )

        time.sleep(10.0) # пусть пройдет logout и гильдия успеет отвалиться по неактивности

        # шлем гильдии письмо:
        msg_1_2 = json_dumps( [{"type":"MSGTYPE_OFFLINE", "text":"OFFLINE MESSAGE"}] )
        reply = post( "send_nl", project=CC.SEX_PW_GUILD_PROJECT, recipient=acc1.guilddata.GuildAuid, sender="pw", body=msg_1_2, server=X_SERVER1 )
        assert( reply.get('ok', -1) == 1 )
        msg_2_2 = json_dumps([{"awards":[{"count":CLAN_POINT,"id":0,"type":21}],"count":1,"roll_id":"6269234965189708624","tm_expire":86400,"type":"s_guild_awards"}])
        reply = post( "send_nl", project=CC.SEX_PW_GUILD_PROJECT, recipient=acc1.guilddata.GuildAuid, sender="pw_pvx", body=msg_2_2, server=X_SERVER1 )
        assert( reply.get('ok', -1) == 1 )

        #------------------------------------------------------------------------------------
        # при следующей загрузке должна прийти гильдия
        acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 )

        time.sleep(2.0)
        #------------------------------------------------------------------------------------
        try:
            reply = accGet( AUID1, "keepalive" )

            assert( acc1.guilddata )
            assert( acc1.guilddata.GuildAuid )
            assert( acc1.guilddata.GuildInfo.FullName == GUILD_FULLNAME )
            assert( acc1.guilddata.GuildInfo.ShortName == GUILD_SHORTNAME )
            assert( acc1.guilddata.Owner.Person == AUID1 )
            assert( acc1.guilddata.findMemberByAuid( AUID1 ) )
            assert( getFriend( acc1, AUID1 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в нашей персоне из FriendsData должна появиться аббревиатура гильдии
            assert( acc1.guilddata.GuildInfo.CWPoints_Clan == CLAN_POINT * 2 )
            print "-- guild after relogin: ok"

            #logLevel( logging.INFO )

            reply = accGet( AUID1, "guild_destroy" )
            time.sleep(2.0) # пусть пройдут необх. апдейты

            reply = accGet( AUID1, "keepalive" )
            assert( not acc1.guilddata.GuildAuid )
            assert( not acc1.guilddata.findMemberByAuid( AUID1 ) )
            assert( getFriend( acc1, AUID1 ).guildshortname == "" ) # кроме того, в нашей персоне из FriendsData должна зачиститься аббревиатура гильдии
            print "-- guild destroyed: ok"

        except:
            catch()

        #------------------------------------------------------------------------------------
        logLevel()
        reply = accGet( AUID1, "logout" )

    ## ------------------------------------------------------------------------------------
    ## ------------------------------------------------------------------------------------

    def test_guild_join(self):
        print "- test_guild_join"

        SNUID1 = '730742963'
        SNTOKEN1 = 'CAAB9M8ptmXMBAIzjqPEMGXXkGIZAtUv8YlebXOAkSyAyimaYtrhYW5vq8iTg9WpVrEFGY9XhAFC7XllVZAq2SXUxz7ajMJHKiLOkG4kZA1oRwBZAarNT0Cw1OxVS5CRftS93ZC7AaIBXc3KZB77JYhdF95RUZBAKX6lYY4XxcDF5bVgbUQldfsFlr9dyslvGEYZD'

        SNUID2 = '100006274567752'
        SNTOKEN2 = 'CAAB9M8ptmXMBACPUR6YuHXpG93jcSQFs2Uj80HcfzrIHYn6013okz2E2VsjGavVoiPOzjsmfZCF4ZA7U6rFIiH2bsZBggetTzU6FZAjSN7DsJUJWgy9ENA6ZAAJigqdirLYUdkFl13CDdFVgN8bSBEqTNtEyQq7AnJ4hndGH4WgZCZCSakCaZCFlQBh9N0m28mMZD'

        acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 )
        acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 )

        time.sleep(5.0) # пусть пройдут апдейты

        AUID1 = acc1.auid
        AUID2 = acc2.auid

        #~ reply = accGet( AUID1, "give_fame", value=100 )
        #~ reply = accGet( AUID2, "give_fame", value=123 )

        # ---------------------------------------------------------------
        # CREATE GUILD
        try:
            #~ reply = accGet( AUID1, "give_fame", value=1234 )
            #~ reply = accGet( AUID2, "give_fame", value=2345 )

            reply = accGet( AUID1, "keepalive" )
            silver1 = acc1.model.Resources.Silver

            logLevel( logging.INFO )

            GUILD_CREATE_PRICE = 150000
            reply = accGet( AUID1, "give_resource", resource="Silver", value=GUILD_CREATE_PRICE )

            reply = accGet( AUID1, "keepalive" )
            silver2 = acc1.model.Resources.Silver
            assert( silver2 == silver1 + GUILD_CREATE_PRICE)

            GUILD_FULLNAME = "DanTestGuild"
            GUILD_SHORTNAME = "DTG"

            reply = accGet( AUID1, "guild_create", fullname=GUILD_FULLNAME, shortname=GUILD_SHORTNAME )
            time.sleep(2.0) # пусть пройдут необх. апдейты

            reply = accGet( AUID1, "keepalive" )
            silver2 = acc1.model.Resources.Silver
            assert( silver2 == silver1 ) # снялись обратно монеты

            assert( acc1.guilddata )
            assert( acc1.guilddata.GuildAuid )
            assert( acc1.guilddata.GuildInfo.FullName == GUILD_FULLNAME )
            assert( acc1.guilddata.GuildInfo.ShortName == GUILD_SHORTNAME )
            assert( acc1.guilddata.Owner.Person == AUID1 )
            assert( acc1.guilddata.findMemberByAuid( AUID1 ) )
            assert( getFriend( acc1, AUID1 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в нашей персоне из FriendsData должна появиться аббревиатура гильдии
            print "-- guild after create: ok"

        except:
            catch()

        reply = accGet( AUID2, "keepalive" ) # список друзей и проч.

        ## logLevel( logging.INFO )

        #--------------------------------------------------------
        # INVITE AUID2 to guild
        try:
            reply = accGet( AUID1, "guild_invite", friend_name="BadName", friend_uid=AUID2 )
        except:
            catch()

        time.sleep(2.0)

        #--------------------------------------------------------
        # ACCEPT (JOIN AUID2 to guild)
        try:
            reply = accGet( AUID2, "keepalive" )

            invite, invite_id = acc2.model.findGuildInviteByPersonAuid( AUID1 )
            assert( invite )
            print "-- guild invite: ok"

            reply = accGet( AUID2, "guild_accept", guild_auid=invite.guildAuid )

            time.sleep(3.0)

            reply = accGet( AUID2, "keepalive" )
            assert( acc2.guilddata )
            assert( acc2.guilddata.GuildAuid )
            assert( acc2.guilddata.GuildInfo.FullName == GUILD_FULLNAME )
            assert( acc2.guilddata.GuildInfo.ShortName == GUILD_SHORTNAME )
            assert( acc2.guilddata.Owner.Person == AUID1 )
            assert( acc2.guilddata.findMemberByAuid( AUID1 ) )
            assert( acc2.guilddata.findMemberByAuid( AUID2 ) )
            assert( getFriend( acc2, AUID1 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в нашей персоне из FriendsData должна появиться аббревиатура гильдии
            assert( getFriend( acc2, AUID2 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в нашей персоне из FriendsData должна появиться аббревиатура гильдии
            print "-- guild after join: ok"

            print "acc1: fame1=%s, fame2=%s" % ( getFriend( acc1, AUID1 ).fame, getFriend( acc1, AUID2 ).fame )
            print "acc2: fame1=%s, fame2=%s" % ( getFriend( acc2, AUID1 ).fame, getFriend( acc2, AUID2 ).fame )

        except:
            catch()

        time.sleep(2.0)

        logLevel()

        #--------------------------------------------------------
        # LOGOUT
        logLevel()
        reply = accGet( AUID1, "logout" )
        reply = accGet( AUID2, "logout" )

        time.sleep(4.0) # пусть пройдет logout и гильдия успеет отвалиться по неактивности

        #------------------------------------------------------------------------------------
        # при следующей загрузке AUID1 должна прийти гильдия, c юзером AUID2 принадлежащим к гильдии
        acc2 = accLogin( snid="fb", snuid=SNUID2, server=ANY_WS, sntoken=SNTOKEN2 )
        time.sleep(2.0)

        try:
            acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 )
            time.sleep(1.0)

            reply = accGet( AUID2, "keepalive" )

            assert( acc2.guilddata )
            assert( acc2.guilddata.GuildAuid )
            assert( acc2.guilddata.GuildInfo.FullName == GUILD_FULLNAME )
            assert( acc2.guilddata.GuildInfo.ShortName == GUILD_SHORTNAME )
            assert( acc2.guilddata.Owner.Person == AUID1 )
            assert( acc2.guilddata.findMemberByAuid( AUID1 ) )
            assert( getFriend( acc2, AUID1 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в нашей персоне из FriendsData должна появиться аббревиатура гильдии

            assert( acc2.guilddata.findMemberByAuid( AUID2 ) )
            assert( getFriend( acc2, AUID2 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в персоне AUID2 из FriendsData должна появиться аббревиатура гильдии

            print "-- guild acc2 after relogin: ok"

            print "relogin acc2: fame1=%s, fame2=%s" % ( getFriend( acc2, AUID1 ).fame, getFriend( acc2, AUID2 ).fame )
        except:
            catch()

        reply = accGet( AUID2, "logout" )

        #------------------------------------------------------------------------------------
        # при следующей загрузке AUID1 должна прийти гильдия, c юзером AUID2 принадлежащим к гильдии
        ## acc1 = accLogin( snid="fb", snuid=SNUID1, server=ANY_WS, sntoken=SNTOKEN1 )
        time.sleep(2.0)

        try:
            reply = accGet( AUID1, "keepalive" )

            assert( acc1.guilddata )
            assert( acc1.guilddata.GuildAuid )
            assert( acc1.guilddata.GuildInfo.FullName == GUILD_FULLNAME )
            assert( acc1.guilddata.GuildInfo.ShortName == GUILD_SHORTNAME )
            assert( acc1.guilddata.Owner.Person == AUID1 )
            assert( acc1.guilddata.findMemberByAuid( AUID1 ) )
            assert( getFriend( acc1, AUID1 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в нашей персоне из FriendsData должна появиться аббревиатура гильдии

            assert( acc1.guilddata.findMemberByAuid( AUID2 ) )
            assert( getFriend( acc1, AUID2 ).guildshortname == GUILD_SHORTNAME ) # кроме того, в персоне AUID2 из FriendsData должна появиться аббревиатура гильдии

            print "-- guild acc1 after relogin: ok"
            print "relogin acc1: fame1=%s, fame2=%s" % ( getFriend( acc1, AUID1 ).fame, getFriend( acc1, AUID2 ).fame )
        except:
            catch()

        logLevel()

        #------------------------------------------------------------------------------------
        # DESTROY GUILD
        try:
            reply = accGet( AUID1, "guild_destroy" )
            time.sleep(2.0) # пусть пройдут необх. апдейты

            reply = accGet( AUID1, "keepalive" )
            assert( not acc1.guilddata.GuildAuid )
            assert( not acc1.guilddata.findMemberByAuid( AUID1 ) )
            assert( getFriend( acc1, AUID1 ).guildshortname == "" ) # кроме того, в нашей персоне из FriendsData должна зачиститься аббревиатура гильдии
            print "-- guild destroyed: ok"

        except:
            catch()

        #------------------------------------------------------------------------------------
        # LOGOUT
        logLevel()
        reply = accGet( AUID1, "logout" )

## ----------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------

## ----------------------------------------------------------------------------------

## test_party_set_fraction() ### для первого запуска на пустом деплое: нужно выбрать сторону 
## time.sleep(1.0)

#~ test_guild_create_destroy()
#~ time.sleep(1.0)

#test_guild_join()


if __name__ == "__main__":
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    unittest.main()
