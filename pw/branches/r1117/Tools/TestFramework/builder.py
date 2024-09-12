from ComponentsSystem import utils
import traceback
from hash import HashStorage

def storeResultHash( command, result ):
  cache = HashStorage()
  cache[utils.calculateHash( command )] = utils.calculateHash( result )
  #print "S KEY: {0}".format( utils.calculateHash( command ) ), " VALUE: {0}".format( utils.calculateHash( result ) )
  
def restoreResultHash( command ):
  cache = HashStorage()
  resultHash = cache.get( utils.calculateHash( command ) )
  #print "R KEY:", utils.calculateHash( command ), " VALUE:", resultHash
  return resultHash

class Builder:
  '''Base class for builders. Rewrite all builders with new architecture.'''

  class Option:
    def __init__( self, output, configuration, verbose ):
      self.output = output
      self.configuration = configuration
      self.verbose = verbose
    
  def __call__( self, options ):
    """Return two items ( {}, [] ): added to component result, and all list of result"""
    return None, None
    
  def version( self ):
    return 0;
    
  def getResultInfo( self ):
    """Return result descriptor"""
    return None
    
  def getSource( self ):
    return [ "v.{0}".format( self.version() ) ]
    
  def isNeedRun( self, force=False ):
    if force:
        return True, 'Processing forced ...'
    try:
      resultHash = restoreResultHash( self.getSource() )
      if resultHash:
        urgentResultHash = utils.calculateHash( self.getResultInfo() )
        needRun = urgentResultHash != resultHash
        if needRun: message = "Result was changed {0}".format( self.getResultInfo() )
        else: message = "No relevant changes detected ... {0}".format( self )
        return needRun, message
      else:
        return True, "No result information for {0}".format( self )
    except:
      return True, traceback.format_exc()
      
  def checkHash( self, verbose, force=False):
    result, message = self.isNeedRun(force)
    #print message
    if verbose >= 2:
      if result: 
        print "Processing ... {0}".format( self )
      else: 
        print "Skiping ... {0}".format( self )
    return result

  def __str__( self ):
    return utils.instance2string( self )
    
  def __repr__( self ):
    return str( self )
    
  def __hash__( self ):
    return int( utils.calcMD5( str( self ) ), 16 )

  def __lt__( self, other ):
    return hash(self) < hash(other)

  def __gt__( self, other ):
    return hash(self) > hash(other)

  def __eq__( self, other ):
    return hash(self) == hash(other)
