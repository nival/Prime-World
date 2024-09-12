# -*- coding: utf-8 -*-
import json 

class User:

    def __init__(self):
        self.auid = 0
        self.sex = 0
        self.photo = ""
        self.nick = "" 
        self.sn_nick = "" 
        self.fraction = None
        self.registration_date = 0
        self.snid = None
        self.snuid = None
        self.fsn = None
        self.remote_ip = None
        self.geolocation = None
        self.original_snid = None    
        self.original_snuid = None    
        self.restriction_ok = 0
        self.secret = None
        self.sn_count = 0
        self.sn_count_prev = 0
        self.sns = None
        self.sn_pairs = []
        self.pwc_snuid = None
        self.locale = None
        self.pwc_snuid = None
        self.pwconnect = 0
        self.registered  = 0
        self.email_md5 = None
        self.pwc_data = None
        self.muid = None
        self.ruid = None
        self.geo_info = ''

    def toJson(self):
        data = {
            'auid' : self.auid,
            'sex' : self.sex,
            'photo' : self.photo,
            'nick' : self.nick,
            'sn_nick' : self.sn_nick,
            'fraction' : self.fraction,
            'registration_date' : self.registration_date,
            'snid' : self.snid,
            'snuid' : self.snuid,
            'fsn' : self.fsn,
            'remote_ip' : self.remote_ip,
            'geolocation' : self.geolocation,
            'original_snid' : self.original_snid,
            'original_snuid' : self.original_snuid,
            'restriction_ok' : self.restriction_ok,
            'secret' : self.secret, 
            'sn_count' : self.sn_count,
            'sn_count_prev' : self.sn_count_prev,
            'sns' : self.sns,
            'sn_pairs' : self.sn_pairs,
            'pwc_snuid' : self.pwc_snuid,
            'registered' : self.registered,
            'locale' : self.locale,
            'pwconnect' : self.pwconnect,
            'email_md5' : self.email_md5,
            'pwc_data' : self.pwc_data,
            'muid' : self.muid,
            'ruid' : self.ruid,
            'geo_info' : self.geo_info,
        }
        return json.dumps(data)

    def fromJson(self, data):
        for name, value in data.items():
            self.__dict__[name] = value
        
