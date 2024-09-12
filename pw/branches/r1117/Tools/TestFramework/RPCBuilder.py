import sys
import os
import builder
import traceback
from shutil import copy2
import hash
from ComponentsSystem import utils
import string

from hash import HashStorage

if 'TestFrameworkPath' in os.environ:
    sys.path.append( os.path.abspath( os.environ['TestFrameworkPath']+'/..' ) )

import CodeGenRPC

MAXPARAMS = 255
MAXFUNCS = 29

class RPCBuilder( builder.Builder ):

    def __init__( self, typename, filename, filter = '', includes = [] ):
        self.typename = typename
        self.filename = os.path.abspath(filename)
        self.includes = includes
        self.filter = filter
        self.dirname = os.path.dirname(self.filename)
        self.componentDir = os.path.abspath('./')

    def __str__( self ):
        file = open( self.filename, 'r' )
        filestr = file.read()
        file.close()
        srcfile = open( CodeGenRPC.getFileName().replace('pyc','py'), 'r' )
        srcfilestr = srcfile.read()
        srcfile.close()
        return 'RPC ' + filestr + ' ' + srcfilestr + ' ' + self.typename + ' ' + str(self.includes) + ' ' + self.filter

    def version( self ):
        return 0;

    def getSource( self ):
        return [ str( self ) ] + builder.Builder.getSource( self )

    def getResultInfo( self ):
        cache = HashStorage()
        return cache.get( "r" + utils.calculateHash( self.getSource() ), {} )

    def __call__( self, options ):
        if self.checkHash( options.verblevel ):
            try:
                parser = CodeGenRPC.Parser( self.filename, MAXPARAMS, MAXFUNCS )

                parser.parseNamespace()

                classes = parser.getAllClasses()

                addedfiles = []

                rcode_h = ""
                rcode_cpp = ""
                lcode_h = ""
                lcode_cpp = ""
                rcodecs = ""
                lcodecs = ""

                for c in classes:
                    parser.parseClass( c )
                    funcs = parser.getAllFuncs()
                    data = parser.getAllData()
#                   print funcs
                    for func in funcs:
                        parser.parseFunction( func )
                    parser.parseData( data )


                    codegen = CodeGenRPC.CodeGenRPC( parser )
                    if self.typename == 'Local':
                        lcode_h += codegen.generateLClassH()
                        lcode_cpp += codegen.generateLClassCpp()
                    elif self.typename == 'Remote':
                        rcode_h += codegen.generateRClassH()
                        rcode_cpp += codegen.generateRClassCpp()
                    elif self.typename == 'CSLocal':
                        lcodecs += codegen.generateLClassCS()
                    elif self.typename == 'CSRemote':
                        rcodecs += codegen.generateRClassCS()

                metacodegen = CodeGenRPC.MetaCodeGenRPC( self.dirname, parser.filename, rcode_h, rcode_cpp, lcode_h, lcode_cpp, rcodecs, lcodecs, self.includes )
        
                if self.typename == 'Local':
                    gfiles = metacodegen.generateLFiles()
                elif self.typename == 'Remote':
                    gfiles = metacodegen.generateRFiles()
                elif self.typename == 'CSLocal':
                    gfiles = metacodegen.generateLCSFiles()
                elif self.typename == 'CSRemote':
                    gfiles = metacodegen.generateRCSFiles()

                for f in gfiles:
                    addedfiles.append( utils.getRelPath(self.componentDir, f) )

                self.collectResultInformation( addedfiles )
            except Exception as instance:
                raise utils.MSVCInfoException( instance.args[0] )

        result = self.getResultInfo()
        return result, result.values()

    def collectResultInformation( self, info ):
        result = {}
        result = { self.filter : info }

        cache = HashStorage()
        cache["r" + utils.calculateHash( self.getSource() )] = result
        builder.storeResultHash( self.getSource(), result )

    def __hash__( self ):
        return int( utils.calcMD5( self.typename ), 16 ) ^ int( utils.calcMD5( str( self ) ), 16 )