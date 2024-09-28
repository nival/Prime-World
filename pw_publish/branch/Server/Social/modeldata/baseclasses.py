# -*- coding: utf-8 -*-

#
# (C) Vadim Petrov 2011
#
# base classes for modeldata

from base.helpers import err

def generateEmptyDict(*args):
    return {}

class BaseObject(object):    
    def get( self, key ):
        return self.__dict__.get(key) 
  
class RefCounted(object):
    def __init__( self ):
        self.__dict__["refCounter"] = 0
    def addRef( self ):
        self.__dict__["refCounter"] += 1
    def decRef( self ):
        self.__dict__["refCounter"] -= 1
    def canDel( self ):
        return self.__dict__["refCounter"] == 0

class Identified(object):
    def __init__( self, id ):
        self.__dict__["id"] = id
    def getID( self ):
        return self.__dict__["id"]
