import os
import sys
import traceback
from ComponentsSystem import utils

class HashStorage:

  __singleton = None
  
  def __init__( self, path = ".cache" ):
    if HashStorage.__singleton is None:
      HashStorage.__singleton = HashStorage.__Implementation( path )
    self.__dict__['_HashStorage__singleton'] = HashStorage.__singleton
    self.flush()
    
  def __del__( self ):
    self.flush()
      
  def flush( self ):
    self.__singleton.flush()
      
  def get( self, key, default = None ):
    return self.__singleton.get( key, default )
  
  def __str__( self ):
    return self.__singleton.__str__()
    
  def __getitem__( self, key ):
    return self.__singleton.__getitem__( key )
    
  def __setitem__( self, key, item ):
    return self.__singleton.__setitem__( key, item )
    
  def __contains__( self, key ):
    return self.__singleton.__contains__( key, item )
    
    

  class __Implementation:
    
    @staticmethod
    def getCache( path ):
      locals = {}
      if os.path.isfile( path ):
        execfile( path, locals )
      return locals.get( "cache", {} )
      
    def __init__( self, path = ".cache" ):
    
      self.storage = os.path.abspath( path )
      try:
        self.cache = self.getCache( self.storage )
      except:
        print "Failed hash storage initialization! Path = {0}".format( self.storage )
        raise

    def flush( self ):
      try:
        if self.reinit():
          file = open( self.storage, "w" )
          file.write( "cache = " )
          file.write( str( self.cache ) )
          file.close()
      except:
        print "Failed cache saving! Storage: {0}".format( self.storage )
        raise
        
    def get( self, key, default = None ):
      if key in self.cache: return self.__getitem__( key )
      else: return default
    
    def __str__( self ):
      return str( self.cache )
      
    def __getitem__( self, key ):
      #print "get - {0} : {1}".format( key, self.cache[key] )
      return self.cache[key]
      
    def __setitem__( self, key, item ):
      #print "store - {0} : {1}".format( key, item )
      self.cache[key] = item
      
    def __contains__( self, key ):
      return key in self.cache  
    
    def reinit( self ):
      cache = self.getCache( self.storage )
      if cache != self.cache:
        cache.update( self.cache )
        self.cache = cache
        return True
      else:
        return False
