import copyBuilder
import os

class InstallBuilder( copyBuilder.CopyBuilder ):

    def __init__( self, source, dest = "" ):
        self.dest = dest
        copyBuilder.CopyBuilder.__init__( self, source, "" )
        
    def __call__( self, options ):
        if self.dest:
            self.evaluateDestination( os.path.join(options.output, self.dest) )
        else:    
            self.evaluateDestination( options.output )
        return copyBuilder.CopyBuilder.__call__( self, options )
        
    def __str__( self ):
        return r"Install( {0} )".format( self.source )
        
    def version( self ):
        return 0 + copyBuilder.CopyBuilder.version( self );
