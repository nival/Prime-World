import sys
import os
from environment import *

configfilename = 'unittest.cfg'

class MD5Class:

    def Set( self, b, c ):
        pass


def getAllPath( startdir = '.' ):
    listpath = []
    mypath = os.path.normpath( os.path.abspath( startdir ) )
    listpath.insert( 0, mypath )
    while os.path.basename( mypath ) != '':
        mypath = os.path.normpath( os.path.dirname( mypath ) )
        listpath.insert( 0, mypath )

    mypath = os.path.abspath( sys.argv[0] )
    mypath = os.path.normpath( os.path.dirname( mypath ) )
    listpath.insert( 0, mypath )
    
    return listpath


def getConfigFilesList( startdir ):
    listfiles = []
    for dirname in getAllPath( startdir ):
        absconfigfile = os.path.join( dirname, configfilename )
        if (os.path.isfile( absconfigfile )):
            listfiles.append( absconfigfile )
    return listfiles


def setVars( root = "." ):
    for filename in getConfigFilesList( root ):
        path = ''
        if not os.path.isdir( filename ):
            path = os.path.dirname( filename )
        else:
            path = filename
        execfile( filename, { 'env' : Envo( path ), 'md5class' : MD5Class() } )

setVars()

if 'TestFrameworkPath' not in os.environ:
    print 'ERROR: There is no TestFrameworkPath variable in the environment'
else:
    sys.path.insert( 0, os.environ['TestFrameworkPath'] )
    print 'Working in:', os.environ['TestFrameworkPath']
    
    try:
        main = __import__('main', globals(),  locals())
        main.main( sys.argv[1:] )
    except Exception as exc:
        sys.stderr.write("Error: {0}".format(exc))
        sys.exit( 1 )
    finally:
        del sys.path[0]
