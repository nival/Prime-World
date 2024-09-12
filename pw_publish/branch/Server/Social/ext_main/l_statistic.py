# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Social Aggregator Login

import sys, os, time, logging, base64

from handlers import * 
from subaction import SubAction, action_timing

import EC
from base.helpers import toint32
import cfg

# ------------------------------------------------------------------------
class GeoSubAction( SubAction ):
    ## умеем вытаскивать remote IP и коротенькое строчное представление geolocation
    def getIpAndLocation(self):
        self.remote_ip = ""
        self.geolocation = ""
        try:
            self.remote_ip = self.request.request.headers.get("X-Real-IP", "127.0.0.1") # потенциальный облом, при каких-нибудь хитрых редиректах, где не будет правильных headers
            location, aux_info = self.I.GEO.getLocationInfoByIP( self.remote_ip )
            info( "l_start headers: %s" % str(self.request.request.headers) )
            info( "l_start remote_ip: %s, location: %s, aux_info: %s" % (self.remote_ip, location, aux_info) )
            if isinstance(aux_info, dict):
                country = aux_info.get("country_code", "")
                city = aux_info.get("city", "")
                if city:
                    self.geolocation = "%s,%s" % (country, city)
                else:
                    longitude = aux_info.get("longitude", "?")
                    latitude = aux_info.get("latitude", "?")
                    self.geolocation = "%s(%s:%s)" % (country, longitude, latitude)
                # из библиотеки geoip возвращается ascii, коды символов типа "\xff", нужно преобразовать к кошерному utf8
                self.geolocation = utf8convert( unicode(self.geolocation, "latin1") ) 
                info( "shorthand geolocation: %s" % self.geolocation )
        except:
            catch()
            info( "can't get location by IP (%s)" % self.remote_ip )
        

# ------------------------------------------------------------------------
class LauncherStartAction( GeoSubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "l_start"
    
    @action_timing
    def onStart(self):
        if self.checkValidParam("hostid"):
            if self.checkValidParam("version"):
                auid = toint( self.getParam("auid", 0) )
                locale = self.getParam("locale", cfg.MATCHMAKER_DEFAULT_LOCALE).upper()
                
                self.getIpAndLocation()
                
                self.I.STATS.addLauncherStart( str(self.hostid), str(self.version), auid, ip=self.remote_ip, location=self.geolocation, locale=locale )
                self.response['ok'] = 1
        self.fin()

# ------------------------------------------------------------------------
class LauncherEventsAction( SubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "l_events"
    
    # muid, auid, session_id, bitmask, timestamp
    @action_timing
    def onStart(self):
        muid = self.getParam("muid", "")
        ruid = self.getParam("ruid", "")
        auid = toint( self.getParam("auid", 0) )
        bitmask = toint( self.getParam("bitmask", 0) )
        timestamp = toint32( self.getParam("timestamp", 0), False )
        if timestamp == 0:
            timestamp = toint32(time.time())  # override with server timestamp
            
        locale = self.getParam("locale", cfg.MATCHMAKER_DEFAULT_LOCALE).upper()
        
        self.I.STATS.addLauncherEvents( str(ruid), str(muid), auid, bitmask, timestamp, locale )
        self.response['ok'] = 1
        
        self.fin()

# ------------------------------------------------------------------------
class LauncherDActions( GeoSubAction ):
    ## action, который будет обрабатывать данный класс:
    action = "l_stat"
    COMMANDS = ["dstart", "dcancel", "derror", "drepeat", "dpause", "dresume", "dprogress", "drepair", "dend"]
    #~ 1: string action
    #~ 2: string hostid
    #~ 3: string version
    #~ 4: string muid
    #~ 5: string auid
    #~ 6: double speed
    #~ 7: double avg_speed
    #~ 8: double min_speed
    #~ 9: i32 total_patches
    #~ 10: i32 applied_patches
    #~ 11: double total_download
    #~ 12: double downloaded
    #~ 13: string error
    #~ 14: i32 need_close
    #~ 15: i32 timestamp
    #~ 16: string geolocation
    #~ 17: i32 server_timestamp
    #~ 18: string locale

    # muid, auid, session_id, bitmask, timestamp
    @action_timing
    def onStart(self):
        cmd = self.getParam("cmd", "")
        if cmd in self.COMMANDS:
            hostid = self.getParam("hostid", "")
            muid = self.getParam("muid", "")
            ruid = self.getParam("ruid", "")
            auid = self.getParam("auid", "") # почему-то string? хм
            launcher_version = self.getParam("version", "")
            timestamp = toint32( self.getParam("time", 0) )
            
            speed = tofloat( self.getParam("speed", 0.0) )
            avg_speed = tofloat( self.getParam("avg_speed", 0.0) )
            min_speed = tofloat( self.getParam("min_speed", 0.0) )
            
            total_patches = toint32( self.getParam("total_patches", 0) )
            applied_patches = toint32( self.getParam("applied_patches", 0) )

            total_download  = tofloat( self.getParam("total_download", 0.0) )
            downloaded = tofloat( self.getParam("downloaded", 0.0) )
            
            string_error = self.getParam("error", "")
            need_close = toint( self.getParam("need_close", 0) )
            
            self.getIpAndLocation()
            now = toint32( time.time() )
            locale = self.getParam("locale", cfg.MATCHMAKER_DEFAULT_LOCALE).upper()
            
            self.I.STATS.addLauncherDActions( action=cmd, hostid=hostid, version=launcher_version, muid=muid,
                    auid=auid, speed=speed, avg_speed=avg_speed, min_speed=min_speed, total_patches=total_patches, applied_patches=applied_patches,
                total_download=total_download, downloaded=downloaded, error=string_error, need_close=need_close, timestamp=timestamp,
                server_timestamp=now, geolocation=self.geolocation, locale=locale )

            '''
            self.I.STATS.addLauncherDActions( action=cmd, hostid=hostid, version=launcher_version, muid=muid, """ruid=ruid,"""
                    auid=auid, speed=speed, avg_speed=avg_speed, min_speed=min_speed, total_patches=total_patches, applied_patches=applied_patches,
                total_download=total_download, downloaded=downloaded, error=string_error, need_close=need_close, timestamp=timestamp,
                server_timestamp=now, geolocation=self.geolocation, locale=locale )
            '''
            self.response['ok'] = 1
        else:
            self.fail( "unknown cmd: %r" % cmd, EC.BAD_PARAM )
        
        self.fin()

