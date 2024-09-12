import os
import builder
import traceback
from shutil import copy2
import hash
from ComponentsSystem import utils
import string

class CopyBuilder( builder.Builder ):

    def __init__( self, source, destination ):
        self.source = os.path.normpath( os.path.abspath( source ) )
        self.evaluateDestination( os.path.normpath( os.path.abspath( destination ) ) )
        
    def evaluateDestination( self, directory ):
        ( path, file ) = os.path.split( self.source )
        self.__directory = directory                
        self.__destination = "{0}/{1}".format( self.__directory, file )
        
    def getSource( self ):
        return [ str( self ) ] + builder.Builder.getSource( self ) + [ utils.calculateHash(self.source) ]
            
    def getResultInfo( self ):
        return self.__destination
        
    def __str__( self ):
        return r"Copy( {0} -> {1} )".format( string.lower( self.source ), string.lower( self.__destination ) )

    def __call__( self, options ):
        if self.checkHash( options.verblevel ):
            try: os.makedirs( self.__directory )
            except: pass
                
            try: 
                copy2( self.source, self.__destination )
                builder.storeResultHash( self.getSource(), self.__destination )
            except: 
                print "Failed: {0}".format( self )
                print traceback.format_exc()
        
        return None, [ self.getResultInfo() ]
        
    def version( self ):
        return 0;
