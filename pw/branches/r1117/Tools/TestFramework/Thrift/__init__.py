import sys
import os
import re
import builder
import tempfile
import traceback
import subprocess
from shutil import copy2
import hash
from ComponentsSystem import utils
import string
import platform

from hash import HashStorage

if 'TestFrameworkPath' in os.environ:
    sys.path.append( os.path.abspath( os.environ['TestFrameworkPath']+'/..' ) )

class Builder( builder.Builder ):

    def __init__( self, idlPath, genType, version='0.9.1', output='.'):
        self.idlPath = os.path.abspath(idlPath)
        self.genType = genType
        self.thriftVersion = version        
        self.output = output
        self.componentDir = os.path.abspath('./')

    def __str__( self ):
        file = open( self.idlPath, 'r' )
        filestr = file.read()
        file.close()
        return 'Thrift ' + filestr +  ' '

    def version( self ):
        return 0;

    def getSource( self ):
        return [ str( self ) ] + builder.Builder.getSource( self )

    def getResultInfo( self ):
        cache = HashStorage()
        return cache.get( "r" + utils.calculateHash( self.getSource() ), {} )

    def __call__( self, options ):
        if self.checkHash( options.verblevel, options.force ):
            try:    
                head, tail = os.path.split(self.idlPath)
                name, ext = os.path.splitext(tail)
                thriftCompilerPath = "thrift"
                if options.platform == 'win32' :
                    thriftCompilerPath = os.path.abspath(os.path.join(os.environ['TestFrameworkPath'], '../../Vendor/Thrift', 'thrift-'+self.thriftVersion+'.exe'))
                    if not os.path.isfile(thriftCompilerPath):
                        raise Exception('Thrift compiler not found: %r' % thriftCompilerPath)
                tempFile = tempfile.mkstemp()[1]
                generationPath = os.path.abspath(os.path.join(self.componentDir, self.output))
                if not os.path.isdir(generationPath):
                    os.makedirs(generationPath)
                args = [
                    thriftCompilerPath,
                    '-v',
                    '-r',
                    '-o',
                    generationPath,
                    '--gen',
                    self.genType,
                    self.idlPath
                ]
                if options.verblevel >= 1:
                    print ' '.join(args)
                
                '''result = os.system(' '.join(args))'''
                tf = open(tempFile, 'w')
                if options.platform == 'win32' :
                  result = subprocess.call(args, shell = True, stdout=tf,stderr=tf)
                else :
                  result = subprocess.call(args, stdout=tf,stderr=tf)
                '''print("Trift return: " + str(result))'''
                tf.close()
                
                if result != 0 or not os.path.isfile(tempFile):
                    if os.path.isfile(tempFile):
                        raise Exception('Thrift compiler failed: %r' % open(tempFile, 'rb').read())
                    else:
                        raise Exception('Thrift compiler failed: <no log>')
                        
                addedFiles = []
                f = open(tempFile, 'rb')
                programText = 'Program: '
                for line in f.readlines():
                    if line.startswith(programText):
                        programFile = line[len(programText):].strip()
                        head, tail = os.path.split(programFile)
                        name, ext = os.path.splitext(tail)
                        generatedPostFixes = [
                            '_types.h',
                            '_types.cpp',
                            '_constants.h',
                            '_constants.cpp',
                        ]
                        for postFix in generatedPostFixes:
                            genName = os.path.join(os.path.join(generationPath, 'gen-cpp'), name+postFix)
                            if os.path.isfile(genName):
                                addedFiles.append(utils.getRelPath(self.componentDir, genName))    

                        idlText = open(programFile, 'rb').read()
                        services = [service.strip() for service in re.findall('service(.+?)(?:extends(?:.+))?{', idlText)] 
                        for service in services:
                            genName = os.path.join(os.path.join(generationPath, 'gen-cpp'), service+'.cpp')
                            if os.path.isfile(genName):
                                addedFiles.append(utils.getRelPath(self.componentDir, genName))    
                            genName = os.path.join(os.path.join(generationPath, 'gen-cpp'), service+'.h')
                            if os.path.isfile(genName):
                                addedFiles.append(utils.getRelPath(self.componentDir, genName))    
                self.collectResultInformation( addedFiles )
            except Exception as instance:
                print("Exception: " + repr(instance))
                raise utils.MSVCInfoException( instance.args[0] )

        result = self.getResultInfo()
        return result, result.values()

    def collectResultInformation( self, info ):
        result = { self.genType : info }

        cache = HashStorage()
        cache["r" + utils.calculateHash( self.getSource() )] = result
        builder.storeResultHash( self.getSource(), result )

    def __hash__( self ):
        return int( utils.calcMD5( str( self ) ), 16 )