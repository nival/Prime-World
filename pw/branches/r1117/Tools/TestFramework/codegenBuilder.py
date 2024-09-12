import builder
import os
import subprocess
import sys

from string import lower
from shutil import copy
from fnmatch import fnmatch
from ComponentsSystem import utils
from hash import HashStorage

class CodeGen( builder.Builder ):
    def __init__( self, path, sources, target ):
        self.sourcePath = os.path.normpath( os.path.abspath( path ) )
        self.target = target
        self.componentDir = os.path.abspath('./')
        
        self.listsources = []
        for source in sources:
            self.listsources.append( os.path.join( self.sourcePath, source ) )
        
    def version( self ):
        return 0;
        
    def getResultInfo( self ):
        cache = HashStorage()
        return cache.get( "r" + utils.calculateHash( self.getSource() ), {} )
        
    def getSource( self ):
        return [ str( self ) ] + builder.Builder.getSource( self )
        
    def __str__( self ):
        return "Codegen( {0}, {1} )".format( lower( self.componentDir ), lower( self.target ) )
        
    def __call__( self, options ):
        if self.checkHash( options.verblevel ):
            codegen = CodeGen.getDBCodeGen( options )
            
            info = None
            if options.platform == 'win32' :
                if codegen:
                    arguments = '{0} {1} --custom={2} --target=cpp --out={3}'.format( codegen, " ".join(self.listsources), self.target, self.componentDir )
                    p = subprocess.Popen( arguments , shell = True, stdin = subprocess.PIPE, stderr = subprocess.STDOUT, stdout = subprocess.PIPE )
                    textout = p.stdout.read()
                    p.wait()
                
                    if textout.find("Error:") != -1: 
                        sys.stderr.write( "Error in {builder}:\n".format( builder = self ) )
                        sys.stderr.write( textout )
                        info = None
                        assert 0
                    else:
                        if options.verblevel >= 2 or p.returncode != 0:
                          print textout
                        if p.returncode == 0:
                            info = None
                        else:
                            info = None
                else:
                    info = None
                    assert 0

            if info != None:
                cache = HashStorage()
                cache["r" + utils.calculateHash( self.getSource() )] = { '' : [self.target + '.auto.h', self.target + '.auto.cpp'] }
                builder.storeResultHash( self.getSource(), result )
            
        result = { '' : [self.target + '.auto.h', self.target + '.auto.cpp'] }
        return result, result.values()

    @staticmethod
    def getDBCodeGen( options ):
        testFrameworkPath = os.path.abspath('.')
        if 'TestFrameworkPath' in os.environ:
            testFrameworkPath = os.path.abspath( os.environ['TestFrameworkPath'] )
        DBCodeGenPath = os.path.abspath( testFrameworkPath + '/../../Vendor/BuildUtils/DBCodeGen.exe' )
        return DBCodeGenPath
