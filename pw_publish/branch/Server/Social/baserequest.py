#!/usr/bin/env python
# -*- coding: utf-8 -*-
# (C) Vadim Petrov 2011, Nival

from base.helpers import *
#from binascii import crc32
import cfg
#from modeldata.changes import IGuidGenerator
import EC

class BaseRequest( object ):
    UnindexedRequestIndex = -1


    def __init__( self, obfuscator ):
        self.obfuscator = obfuscator
        self.response = {}
        self.arguments = {}

    # поведение нормального dictionary (arguments)
    def __setitem__(self, name, value):
        self.arguments[name] = value

    def __getitem__(self, name):
        return self.arguments.get(name)

    def __iter__( self ):
        return self.arguments.__iter__()

    def iteritems( self ):
        return self.arguments.iteritems()

    def keys( self ):
        return self.arguments.keys()

    def __len__( self ):
        return self.arguments.__len__()


    def get( self, name, default=None):
        strParam = self.getStringParam( name, None )
        if strParam is not None:
            return [strParam]
            # FIXME - если strParam is None, то и следующие две попытки будут безуспешными, ещё и код ошибки запишут!
        intParam = self.getIntParam( name, None )
        if intParam is not None:
            return [intParam]
        floatParam = self.getFloatParam( name, None )
        if floatParam is not None:
            return [floatParam]
        return default


    def getArrayParam( self, name, default=None):
        strParam = self.getStringParam( name, default )
        if strParam:
            numbers_str = string.split( string.strip(strParam), ',' )
            numbers = []
            for str in numbers_str:
                numbers.append( int(str) )
            return numbers
        return default


    def getStringParam(self, name, default=None):
        param_list = self.arguments.get(name)
        if param_list:
            return param_list[0]
        return default


    def getIntParam(self, name, default=None):
        param_list = self.arguments.get(name)
        if param_list:
            value = param_list[0]
            if digit(value):
                return int(value)
            else:
                self.response["error"] = "Not int param: " + str(name)
        return default


    def getBoolParam(self, name, default=None):
        param_list = self.arguments.get(name)
        if param_list:
            value = param_list[0]
            if str(value).lower() in ["false", "true"]:
                return str2bool(str(value))
            else:
                self.response["error"] = "Not bool param: " + str(name)
        return default


    def getFloatParam(self, name, default=None):
        param_list = self.arguments.get(name)
        if param_list:
            value = param_list[0]
            if testfloat(value):
                return float(value)
            else:
                self.response["error"] = "Not float param: " + str(name)
        return default


    def getJsonParam(self, name, default=None, error="bad json data: "):
        param_list = self.arguments.get(name)
        if param_list and len(param_list) and param_list[0]:
            json_data = param_list[0] #tornado.escape.xhtml_escape(param_list[0])
            try:
                data = json_loads( json_data )
                return data
            except:
                self.response["error"] = error + "%s=%s" % (str(name), str(json_data))
                self.response["error_json"] = printException( sys.exc_info() )
        return default


    def getKeeperObjectIDParam( self, name, modeldata ):
        id = self.getIntParam( name )
        #TODO:LOFIK:ENCIPHER_TRAFFIC
        #if self.obfuscator and cfg.ENCIPHER_TRAFFIC:
        #  rid = BaseRequest.UnindexedRequestIndex
        #  if self.rid != None and self.rid != BaseRequest.UnindexedRequestIndex:
        #    rid = self.rid
        #  key = self.getStringParam("key")
        #  uid = self.getIntParam("uid")
        #  hash1 = uid^rid
        #  hash2 = crc32(key)
        #
        #  id = id ^ hash1
        #  id = id ^ -53
        #  id = id - hash2
        return id
