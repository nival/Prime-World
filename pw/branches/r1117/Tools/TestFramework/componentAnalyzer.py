import sys
import imp
import os
import re
import exceptions
from ComponentsSystem import utils
import traceback
import fnmatch
import string
import Vendors.SCons.Tool.msvc
import Vendors.SCons.Tool.msvs

from copy import deepcopy

from installBuilder import InstallBuilder
from copyBuilder import CopyBuilder
from componentBuilder import ComponentBuilder
from codegenBuilder import CodeGen
from RPCBuilder import RPCBuilder
from Thrift import Builder as ThriftBuilder

from string import Template
from platforms import supportedPlatforms
from platforms import Win32Features

from ComponentsSystem import getDefaultSources

# class ComponentGraphIterator:

    # def __init__( self ):
        # self.visited = set( [] )
        # self.current = None
        
    # def __call__( self, component ):
        # if component not in self.visited:
            # self.visited.add( component )
            # for child in component.components:
                # self( child )
        # else:
            # return 
def getRealComponentName( name ):
    dict = { 
        'libdb.animated' : 'libdb.NET/Animated',
        'libdb.db' : 'libdb.NET/DB',
        'libdb.undoredo' : 'libdb.NET/UndoRedo',
        'libdb.diagnostics' : 'libdb.NET/Diagnostics',
        'libdb.io' : 'libdb.NET/IO',
        'libdb.tests' : 'libdb.NET/Tests',
        'dbtypes' : 'Types.DBTypes',
        }

    for ( key, value ) in dict.iteritems():
        if name.lower() == key:
            return value

    return name


def getResultInformation( component, configurationName ):
    type2ext = {
        "exe" : "exe",
        "dll" : "dll",
        "lib" : "lib",
        "console" : "exe",
        "windows" : "exe",
        "library" : "dll",
    }
    type = component.getType( configurationName )
    if type in type2ext: return "{name}.{ext}".format( ext = type2ext[type], name = component.shortName )
    else: return None


def collectResultInformation( component, configurationName ):
    info = getResultInformation( component, configurationName )
    if info: result = [ info ]
    else: result = []
    for child in component.components:
        information = collectResultInformation( child, configurationName )
        for data in information: 
            if data not in result: result.append( data )
    return result

def ParseSources(sources):
    result = []
    for files_root_path, files in sources.items():
        for name in files:                                  
            result.append(os.path.join(files_root_path, name))
    return result            
    
def GetSources(rootPath=None, excludeFiles=[], patterns = ['*.cpp']):
    platform = globals().get( 'platform', None )
    start = os.path.abspath(globals().get( 'decriptorPath', '.' ))
    if rootPath:
        start = os.path.abspath(rootPath)
    sources = utils.collectFiles( start, patterns, recursive = False) 
    folders = []
    if platform:
        for name in os.listdir(start):
            path = os.path.join(start, name)
            if os.path.isdir(path) and platform in name:
                folders.append(path)
    for folder in folders:
        sources += utils.collectFiles(folder, patterns, recursive=False)
    result = []
    
    for name in sources:
        if not fnmatch.fnmatch(name.lower(), '*.test.cpp'):
            head, tail = os.path.split(name)
            if tail not in excludeFiles:
                result.append(name)
    return result
    
def GetLatestCompilerInstalled():
    v = sorted(Vendors.SCons.Tool.msvs.get_visualstudio_versions())
    if v:
        if v[-1] == '8.0':
            return 'msvc8'
        if v[-1] == '9.0':
            return 'msvc9'

def GetCompilerPaths():
    compiler = globals().get( 'compiler', None )
    version = '9.0'
    if compiler == 'msvc8':
        version = '8.0'
    includePaths, libPaths, exePaths = Vendors.SCons.Tool.msvc.get_msvc_paths({}, version)
    return includePaths.split(';'), libPaths.split(';')

def iterateComponents( root ):
    result = [root]
    for component in root.components:
        result.extend( iterateComponents( component ) )
    return result

def findLoopedComponent( root, alreadyChildren = [] ):
    alreadyChildren.append( root.name )
    for child in root.components:
        for alreadychild in alreadyChildren:
            if alreadychild == child.name:
                loopedh = ""
                for ac in alreadyChildren:
                    loopedh = loopedh + " " + ac
                loopedh = "Find loop:" + loopedh + " " + alreadychild
                raise Exception( loopedh )
        findLoopedComponent( child, alreadyChildren )
    alreadyChildren.pop()
    return None

def buildComponentsHierarchy( root ):
    result = {}
    children = set( [] )
    for child in root.components:
        children.add( child.name )
        result.update( buildComponentsHierarchy( child ) )
    result.update( { root.name : children } )
    return result
    
class SourceInfo:

    separator = '/'
    
    def __init__( self, file, componentDirectory ):
        self.componentDirectory = componentDirectory
        self.file = file
        self.compilerKeys = {}
        
    def __repr__( self ):
        return str( self )
        
    def __str__( self ):
        return utils.instance2string( self )
        
    def __cmp__( self, other ):
        return cmp( self.file, other.file )
        
    def __hash__( self ):
        result = hash( self.file )
        for key in sorted( self.compilerKeys.keys() ):
            hashs = map( lambda x: hash( x ), self.compilerKeys[key] )
            for value in hashs:
                result ^= value
        return result
        
    def addKey( self, configuration, key ):
        # TODO: support only cpp
        name, ext = os.path.splitext( self.file )
        #print "name, ext", name, ext
        if ext == ".cpp" or ext == ".c":
            keys = self.compilerKeys.setdefault( configuration, set( [] ) )
            if issubclass( type( key ), str ): keys.add( key )
            else: keys.update( key )
        
    def HasCompileKey( self, configuration, key ):
        keys = self.compilerKeys.setdefault( configuration, set( [] ) )
        for item in keys:
            if item.find( key ) != -1: 
                return True
        return False

class Configuration:
    '''
    All parameters:
        sources = {'':['']} || ['']
        includePaths = ['']
        libPaths = ['']
        libDependencies = [''] or libs = ['']
        components = ['']
        defines = '<define>;<define>' or list[''] 
        inlined = <boolean>
        projectType = 'win32' or '.net'
        type = 'exe' or 'dll' or 'lib' or 'utility'
        compilerKeys = ';' or list['']
        linkerKeys = ';' or list['']
        project = ''

        name
        descriptor
        directory
        shortName
    '''

    configurationNames = [
        'debug',
        'release',
    ]
    
    @staticmethod
    def analyzeOptions( options ):
        '''detemine options type and convert it to list'''
        if isinstance( options, str ):
            return [define for define in options.split( ";" ) if define]
        elif isinstance( options, list ):
            return options
        else:
            raise Exception( "Invalid parameter type: {0}, expected string or list".format( type( options ) ) )
    
    @staticmethod
    def determineType( sources ):
        projectType = 'win32'
        
        ext2type = {
            ".cs" : ".net",
            ".cpp" : "win32",
            ".c" : "win32",
            ".hpp" : "win32",
            ".h" : "win32"
        }
        
        files = sources
        if isinstance( sources, dict ):
            files = []
            for container in sources.values():
                files.extend( container )
        
        result = {}
        for source in files:
            ( name, ext ) = os.path.splitext( source )
            type = ext2type.get( ext )
            if type: 
                value = result.get( type, 0 )
                result[type] = value + 1
                
        oldValue = 0
        for type, value in result.iteritems():
            if value > oldValue:
                projectType = type
                value = oldValue
        
        return projectType, sources

    def __init__( self, name, platform, testRun, options, settings ):
        self.name = name
        self.platform = platform
        self.testRun = testRun
        self.type = 'exe'
        self.projectType = 'win32'
        
        self.compilerKeys = set( [] )
        self.sharedCompilerKeys = set( [] )
        self.globalCompilerKeys = set( [] )        
        self.linkerKeys = set( [] )
        self.builders = set( [] )
        self.defines = set( [] )
        self.charset = 'ansi'
        self.options = options
        self.settings = settings
        
        self.platformFeatures = {}
        
    def ProcessLibs(self, libs):        
        result = []
        for name in libs:
            if self.platform == 'win32' and '.lib' not in name.lower():
                result.append(name+'.lib')
            else:
                result.append(name)
        self.libDependencies.update( set( result ) )

    def GetPath( self, path ):
        if path.find("$(") != -1:
            return path
        return os.path.abspath( path )
        
    def __call__( self, componentPath ):
        componentRoot = os.path.dirname( componentPath )
        localVars = {}
        variables = {
            'descriptorPath' : componentRoot,
            'workingDirectory' : os.getcwd(),
            'configuration' : self.name,
            'platform' : self.platform,
            'testRun' : self.testRun,
            'compiler': self.options.compiler,
            'settings' : self.settings,
        }
        globalVariables = globals()
        globalVariables.update( variables )
        if self.options.verblevel >= 2:
            print "Loading component %r for configuration %r" % (componentPath, self.name)
        if self.options.projType == 'cs' and not os.path.isfile( componentPath ):
            pass
        else:
            savedDirectory = utils.Directory( componentRoot )
            execfile( componentPath, globalVariables, localVars )
        
        self.libDependencies = set()
        self.ProcessLibs( localVars.get( 'libDependencies', [] ) )
        self.ProcessLibs( localVars.get( 'libs', [] ) )

        tempComponents = localVars.get( 'components', [] )
        tempComponents = [ utils.fixBackslashes(c) for c in tempComponents]
        self.components = set( tempComponents )
        
        self.includePaths = set( localVars.get( 'includePaths', [] ) )
        self.libPaths = set( localVars.get( 'libPaths', [] ) )
        self.defines = set( Configuration.analyzeOptions( localVars.get( 'defines', [] ) ) )
        
        self.compilerKeys = set( Configuration.analyzeOptions( localVars.get( 'compilerKeys', [] ) ) )
        self.linkerKeys = set( Configuration.analyzeOptions( localVars.get( 'linkerKeys', [] ) ) )

        # local properties affected only on current component
        self.localIncludePaths = set( localVars.get( 'localIncludePaths', [] ) )
        self.localDefines = set( Configuration.analyzeOptions( localVars.get( 'localDefines', [] ) ) )
        self.localCompilerKeys = set( Configuration.analyzeOptions( localVars.get( 'localCompilerKeys', [] ) ) )
        self.globalCompilerKeys = set( Configuration.analyzeOptions( localVars.get( 'globalCompilerKeys', [] ) ) )
        
        self.platformFeatures = localVars.get( 'platformFeatures', {} )
    
        # normalize paths, make its absolute
        self.includePaths = set( map( self.GetPath, self.includePaths ) )
        self.libPaths = set( map( self.GetPath, self.libPaths ) )
        
        self.inlined = localVars.get( 'inlined', True )
                
        self.sources = localVars.get( 'sources', {} )
        self.projectType = localVars.get( 'projectType', None )
        if self.projectType == None:
            ( self.projectType, self.sources ) = Configuration.determineType( self.sources )

        self.project = localVars.get( 'project', '' )
        if self.project:
            self.project = os.path.abspath( utils.fixBackslashes(self.project) )
            self.inlined = False
        
        if len( self.sources ) == 0: 
            self.type = 'utility'
        else: 
            self.type = 'exe'
        self.type = localVars.get( 'type', self.type )
        
        self.builders = set( localVars.get( 'builders', [] ) )
        
        self.componentFilter = localVars.get( 'filter' )

        self.charset = localVars.get( 'charset', 'ansi' )
        
        # form list of compiler and linker keys
        self.ComposeKeys()
        
    def ComposeKeys( self ):
        self.addIncludePaths( self.includePaths )
        self.addDefines( self.defines )
        self.addLibPaths( self.libPaths )
        self.addLibs( self.libDependencies )
        self.sharedCompilerKeys = set( [] )
       
    def addDefines( self, defines ):
        if self.platform == 'win32':
            self.compilerKeys.update( map( lambda x: "/D&quot;{0}&quot;".format( x ), defines ) )
        elif self.platform == 'linux':
            self.compilerKeys.update( map( lambda x: "-D&quot;{0}&quot;".format( x ), defines ) )
        else:
            raise Exception( "Invalid platform type: {0}".format( self.platform ) )
        
    def addIncludePaths( self, includePaths ):
        if self.platform == 'win32':
            self.compilerKeys.update( map( lambda x: "/I&quot;{0}&quot;".format( x ), includePaths ) )
        elif self.platform == 'linux':
            self.compilerKeys.update( map( lambda x: "-I&quot;{0}&quot;".format( x ), includePaths ) )
        else:
            raise Exception( "Invalid platform type: {0}".format( self.platform ) )
        
    def addLibPaths( self, libPaths ):
        self.linkerKeys.update( map( lambda x: "/LIBPATH:&quot;{0}&quot;".format( x ), libPaths ) )
        
    def addLibs( self, libDependencies ):
        self.linkerKeys.update( map( lambda x: "&quot;{0}&quot;".format( x ), libDependencies ) )
        
    def Inline( self, configuration ):
        self.builders.update( configuration.builders )
        self.compilerKeys.update( configuration.compilerKeys )
        self.sharedCompilerKeys.update( configuration.sharedCompilerKeys )
        self.linkerKeys.update( configuration.linkerKeys )
        self.globalCompilerKeys.update( configuration.globalCompilerKeys )
        
        if self.type == 'utility':  
            self.type = configuration.type

class Settings:

    def get(self, name):            
        if name not in self.__dict__:
            return None
        return self.__dict__[name]
                    
class Component:
    
    EMPTY_DESCRIPTOR = "EMPTY_DESCRIPTOR"
    
    def __init__( self, name = "EMPTY_DESCRIPTOR", descriptor = None, options = None, testRun = False, settings = None):
        self.name = name
        self.shortName = utils.shortName( self.name )
        self.directory = ''
        self.options = options
        
        self.dummyDependenciesRemoved = False
        self.evaluatedCompilerKeys = False
        
        self.components = set( [] )
        self.inlined = False

        self.sources = {}
        self.configurations = {}
        
        self.componentFilter = self.name
        self.project = ""
        self.settings = settings

        if descriptor and self.options and self.options.projType == 'cs' and not os.path.isfile( descriptor ):
            self.projType = 'cs'
        else:
            self.projType = 'other'

        # run n calls where n - number of configurations
        if options: 
            platform = options.platform
        else: 
            platform = "win32"
        self.platform = platform
        
        for name in Configuration.configurationNames:
            configuration = Configuration( name, platform, testRun, options, self.settings )
            self.configurations[name] = configuration
        
        if descriptor:
            self.analyzeDescriptor( descriptor )
        else:
            self.descriptor = Component.EMPTY_DESCRIPTOR
        
    def analyzeDescriptor( self, descriptor ):

        if self.options and self.options.projType == 'cs' and not os.path.isfile( descriptor ):
            self.descriptor = descriptor
            self.directory = ''
        else:
            self.descriptor = os.path.normpath( descriptor )
            self.directory = os.path.dirname( self.descriptor )                        

        sources = {}
        for configuration in self.configurations.values():
            configuration( self.descriptor )
            
            if isinstance( configuration.sources, list ): sources.update( { "" : configuration.sources } )
            elif isinstance( sources, dict ): sources.update( configuration.sources )

            self.project = configuration.project
            self.components |= configuration.components
            self.inlined |= configuration.inlined
            self.componentFilter = configuration.componentFilter
            
            if not self.componentFilter:
                self.componentFilter = self.name
        
        for key, value in sources.iteritems():
            key = self.componentFilter + SourceInfo.separator + key
            for file in value:
                if self.options and self.options.projType == 'cs':
                    self.AddSource( self.directory + '\\' + file, key )
                else:
                    self.AddSource( file, key )
        
        if self.projType == 'cs':
            self.descriptor = self.descriptor.replace( '/', '.' )
            self.inlined = False
        else:
            self.AddSource( os.path.basename( self.descriptor ), utils.removeUnusedSeparator( self.componentFilter ) )
        self.ApplyLocalOptions()

    def getConfiguration( self, configurationName ):
        configurationName = string.lower( configurationName )
        return self.configurations.get( configurationName )
    
    def getCompilerKeys( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return configuration.sharedCompilerKeys | configuration.globalCompilerKeys
        else: return []
        
    def getLinkerKeys( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return configuration.linkerKeys
        else: return []
    
    def getProjectType( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return configuration.projectType
        else: return ""
    
    def getType( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return configuration.type
        else: return ""

    def getCharset( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return configuration.charset
        else: return ""
    
    def getBuilders( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return configuration.builders
        else: return []
        
    def getFeatures( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return configuration.platformFeatures
        else: return []
        
    def __repr__( self ):
        return str( self )
        
    def __str__( self ):
        return utils.instance2string( self )
        
    def AddSource( self, source, filter = None ):
        if not filter: 
            key = utils.removeUnusedSeparator( self.componentFilter )
        else: 
            key = utils.removeUnusedSeparator( filter )
        infos = self.sources.setdefault( key, set( [] ) )
        if os.path.isabs( source ): 
            value = source
        else: 
            value = os.path.normpath( self.directory + "\\" + source )
        info = SourceInfo( value, self.descriptor )
        infos.add( info )
        return info

    def generateUniqueOutputFileName( self, file ):
        uniqueName = os.path.basename( file )
        
        fileLwr = file.lower()
        fileLwr = utils.fixBackslashes( fileLwr )
        
        dirLwr = self.directory.lower()
        dirLwr = utils.fixBackslashes( dirLwr )
        
        result = uniqueName
        if fileLwr.find( dirLwr ) != -1:
            result = file[len(dirLwr):]
        else:
            result = file[fileLwr.find('/'):]
        if result[0] == '/' or result[0] == '\\':
            result = result[1:]
        result = result.replace( "/", "." ).replace( "\\", "." )
        return result

    def detemineOutput( self, file ):
        uniqueName = os.path.basename( file )
        uniqueNameLwr = uniqueName.lower()
        found = False
        for name in self.evaluatedSources:
            if name.lower() == uniqueNameLwr:
                found = True
                break
        if found and self.platform == 'win32':
            name = self.generateUniqueOutputFileName( file )
            obj = "{0}.obj".format( name )
            output = "/Fo&quot;$(IntDir)\{obj}&quot;".format( obj = obj )
            #print output
            return output
        else:
            self.evaluatedSources.add( uniqueName )
            return None
    
    #evaluatedSources = set( [] )
    def EvaluateSources( self ):
        testSameFiles = []
        testComponents = []
        
        self.evaluatedSources = set( [] )
        for keys, infos in self.sources.iteritems():
            for info in infos:
                
                fileLwr = info.file.lower()
                fileLwr = utils.fixBackslashes( fileLwr )
                for x in xrange(0,len(testSameFiles)):
                    if fileLwr == testSameFiles[x] and fileLwr.find(".pch.") == -1:
                        print info.componentDirectory+"(1) : error C666: double file: "+os.path.basename( info.file )
                        print testComponents[x]+"(1) : error C666: double file: "+os.path.basename( info.file )
                        exit(1)
                testSameFiles.append( fileLwr )
                testComponents.append( info.componentDirectory )
                
                output = self.detemineOutput( info.file )
                if output: 
                    for configurationName in self.configurations.keys():
                        info.addKey( configurationName, output )
        
        for component in self.components:
            component.EvaluateSources()
    
    def ApplyLocalOptions( self ):
        for infos in self.sources.values():
            for info in infos:
                for configurationName, configuration in self.configurations.iteritems():
                    info.addKey( configurationName, map( lambda x: "/I&quot;{0}&quot;".format( x ), configuration.localIncludePaths ) )
                    info.addKey( configurationName, map( lambda x: "/D&quot;{0}&quot;".format( x ), configuration.localDefines ) )
                    info.addKey( configurationName, configuration.localCompilerKeys )

    def ApplyPlatformFeatures( self ):
        for configurationName, configuration in self.configurations.iteritems():
            for pn in configuration.platformFeatures :
                if pn == self.platform :
                    platform = configuration.platformFeatures[ pn ]
                    #print "Apply", self.name, configurationName
                    platform.Apply( self, configurationName, configuration.compilerKeys )
                    #print "---"

    def addIncludePaths( self, includePaths ):
        for configuration in self.configurations.values():
            configuration.addIncludePaths( includePaths )

    def addLibPaths( self, libPaths ):
        for configuration in self.configurations.values():
            configuration.addLibPaths( libPaths )

    def ApplySpecificKeys( self, configurationName, compilerKeys ):
        #printed = []
        for sources in self.sources.values():
            for source in sources:
                # if source.file.find( "System.PerfLog.pch.cpp") != -1:
                    # printed.append( source )
                source.addKey( configurationName, compilerKeys )
                
        # for item in printed:
            # print "FFF", self.name, configurationName
            # print item.file, compilerKeys
            # print "---"

    def InlineComponent( self, component ):
        
        for configurationName, configuration in component.configurations.iteritems():
            if configurationName in self.configurations: self.configurations[configurationName].Inline( configuration )
            else: self.configurations[configurationName] = configuration
            
        for key, sources in component.sources.iteritems():
            for source in sources:
                files = self.sources.setdefault( key, set( [] ) )
                files.add( source )

        self.components.update( component.components )

    def InlinePlatformFeacture( self, component ):
        if component.inlined:
            
            # print "Inline PF:", self.name, component.name
            
            for configurationName in self.configurations.keys():
                assert configurationName in component.configurations                    
                remoteFeatures = component.configurations[configurationName].platformFeatures
                localFeatures = self.configurations[configurationName].platformFeatures
                for platform in supportedPlatforms:
                    if platform in remoteFeatures:
                        if platform in localFeatures: localFeatures[platform].Inline( remoteFeatures[platform] )
                        else: localFeatures[platform] = remoteFeatures[platform]
                        
                    # if platform in localFeatures:
                        # print "PCH", platform, configurationName, localFeatures[platform].pchs
                        
            # print "---"
                
    def InlinePlatformFeatures( self ):
        for component in self.components:
            self.InlinePlatformFeacture( component )

    def EvaluateSharedCompilerKeys( self ):
        sharedKeys = {}
        for configurationName, configuration in self.configurations.iteritems():
            sharedKeys[configurationName] = configuration.compilerKeys.copy() | configuration.sharedCompilerKeys.copy()
        
        for component in self.components:
            if component.inlined:
                keys = component.EvaluateSharedCompilerKeys()
                for key in keys.keys():
                    sharedKeys[key] &= keys[key]
       
        return sharedKeys
    
    def SetSharedCompilerKeys( self, sharedKeys ):
        for component in self.components:
            if component.inlined: component.SetSharedCompilerKeys( sharedKeys )
            
        for configurationName, configuration in self.configurations.iteritems():
            configuration.compilerKeys = ( configuration.compilerKeys | configuration.sharedCompilerKeys ) - sharedKeys[configurationName]
            configuration.sharedCompilerKeys = sharedKeys[configurationName]
        
    def CombineCompilerKeys( self ):
        # combine child compiler keys
        for component in self.components:
            if component.inlined:
                component.CombineCompilerKeys()
                
                for configurationName, configuration in component.configurations.iteritems():
                    keys = configuration.compilerKeys | configuration.sharedCompilerKeys
                    if configurationName in self.configurations: 
                        self.configurations[configurationName].compilerKeys |= keys
                    else: 
                        self.configurations[configurationName].compilerKeys = keys

    
    # def PrintKeys( self ):
        
        # for component in self.components:
            # component.PrintKeys()
        
        # print "@@@", self.name
        
        # for configurationName, configuration in self.configurations.iteritems():
            # print configurationName, "local:", configuration.compilerKeys
            # print configurationName, "shared:", configuration.sharedCompilerKeys
        
        # print "---"
        
    def ProccessComponentsGraph( self, root = True ):

        for component in self.components:
            component.ProccessComponentsGraph( not component.inlined )

        if root and not self.evaluatedCompilerKeys:
            
            self.CombineCompilerKeys()
            sharedKeys = self.EvaluateSharedCompilerKeys()
            self.SetSharedCompilerKeys( sharedKeys )
            
            self.evaluatedCompilerKeys = True
            
            # print "AAA", self.name
            # print sharedKeys
            # print "---"
    
    def RemoveDummyDependencies( self ): 

        if self.dummyDependenciesRemoved:
            return
        
        inlined = set( [] )
        for component in self.components:
            assert isinstance( component, Component ), self
            component.RemoveDummyDependencies()
            if component.inlined:
                inlined.add( component )
        
        self.InlinePlatformFeatures()
        self.ApplyPlatformFeatures()
        self.components -= inlined
        
        for configurationName, configuration in self.configurations.iteritems():
            self.ApplySpecificKeys( configurationName, configuration.compilerKeys )
        
        for component in inlined: self.InlineComponent( component )
    
        self.dummyDependenciesRemoved = True    
    
    def __lt__( self, other ):
        return self.descriptor < other.descriptor

    def __gt__( self, other ):
        return self.descriptor > other.descriptor

    def __eq__( self, other ):
        return self.descriptor == other.descriptor

    def __hash__( self ):
        return hash( self.descriptor )

class ComponentLoader:

    def __init__( self, globalScope, options, testRun):
        self.globalScope = map( lambda path: os.path.normpath( path ), globalScope )
        self.localPath = None
        self.locals = []
        self.options = options
        self.createdComponents = {}
        self.testRun = testRun
        self.settings = Settings()

    
    # look for total description then for concreat description
    descriptorTemplates = [ 
        Template( r'${path}/${name}.component' ),
        Template( r'${path}/${name}.application' ),
        Template( r'${path}/${name}/all.component' ),
    Template( r'${path}/${name}/${shortName}.component')
    ]
    
    def SearchComponentDescriptor( self, name ):
        # look for in current dirrectory at first and then in global scope
        scope = self.getScope()
        for path in scope:
            mapping = dict( path = path, name = name, shortName = utils.shortName( name ) )
            for template in ComponentLoader.descriptorTemplates:
                instanse = template.substitute( mapping )
                descriptor = os.path.normpath( instanse )
                if self.options.verblevel >= 2: 
                    print 'Looking for component in {0} ...'.format( descriptor ),
                if os.path.isfile( descriptor ):
                    if self.options.verblevel >= 2: 
                        print 'Found!'
                    return descriptor
                elif self.options.verblevel >= 2: print ''
        if self.options.projType == 'cs':
            name = name.replace( '.', '/' )
            for path in scope:
                mapping = dict( path = path, name = name, shortName = utils.shortName( name ) )
                for template in ComponentLoader.descriptorTemplates:
                    instanse = template.substitute( mapping )
                    descriptor = os.path.normpath( instanse )
                    if self.options.verblevel >= 2: 
                        print 'Looking for component in {0} ...'.format( descriptor ),
                    if os.path.isfile( descriptor ):
                        if self.options.verblevel >= 2: 
                            print 'Found!'
                        return descriptor
                    elif self.options.verblevel >= 2: 
                        print ''
            return name
        raise Exception( 'Can\'t find component "{0}" in scope: {1}'.format( name, scope ) )

    def getScope( self ):
        if self.localPath: 
            result = [self.localPath]        
        else: 
            result = []
        if self.locals: 
            result.extend( self.locals )
        for path in self.globalScope:
            if path not in result:
                result.append( path )
        return result
        
    def addLocals( self, locals = [] ):
        self.locals = locals    
    
    def addLocalPath( self, fileName = None ):
        # so we can find them in relativily from source file
        if os.path.isfile( fileName ):
            fileName = os.path.normpath( utils.pathName( fileName ) )
        self.localPath = fileName
        #self.createdComponents.clear()

    def CreateComponent(self, name, filterName=None):
        name = getRealComponentName( name )
        componentPath = self.SearchComponentDescriptor( name )

        if componentPath in self.createdComponents:
            return self.createdComponents[componentPath], False
        else:
            try:                
                if not filterName: 
                    filterName = name
                self.settings.testRun = self.testRun    
                component = Component( filterName, componentPath, self.options, self.testRun, self.settings )
            except Exception, instance:
                if self.options.showStack:
                    traceback.print_tb( sys.exc_traceback )
                raise
            self.createdComponents[componentPath] = component
            return component, True
                
class _Analyzer:

    maximumNestingLevel = 50
    
    def __init__( self, globalScope, verblevel, options, loader ):
        flags = re.I | re.U
        self.componentCppRE = [
            re.compile( r'//!Component\(\s*[\'\"]+(.+)[\'\"]+\s*\)', flags ),
            re.compile( r'//!Package\(\s*[\'\"]+(.+)[\'\"]+\s*\)', flags ),
        ]
        self.componentCsRE = [
            re.compile( 'using\s+((\w+\.*\w*)+);', flags ),
            re.compile( 'namespace\s+((\w+\.*\w*)+)', flags ),
        ]
        self.verblevel = verblevel
        self.nestingLevel = 0
        self.options = options
        self.loader = loader
    
    def Scan( self, fileName ):
        '''Return list of components graph'''
        self.addLocalPath( fileName )
        components = []
        if 'AdditionalComponent' in os.environ and self.options.projType == 'cpp':
            componentsNames = os.environ['AdditionalComponent'].split(';')
            for name in componentsNames:
                components.append( self.CreateComponent( name ) )

        file = open( fileName )
        while True:
            line = file.readline()
            if not line: 
                break
            if self.options and self.options.projType == 'cs':                
                components.extend( self.ScanLine( line, self.componentCsRE ) )
            else:    
                createdComponents = self.ScanLine( line, self.componentCppRE ) 
                if not createdComponents:
                    break
                components.extend(createdComponents)
        return components
        
    def ScanLine( self, line, patterns ):
        name = self._SearchComponentExpression( line, patterns )
        if name: 
            return [self.CreateComponent( name )]
        else: 
            return []
        
    def ProcessDependencies( self, component ):
        components = set( [] )
        for name in component.components:
            components.add( self.CreateComponent( name, resetCycleChecker = False ) )
            self.nestingLevel -= 1
        return components
    
    def CreateComponent( self, name, filterName = None, resetCycleChecker = True ):
        if resetCycleChecker: 
            self.nestingLevel = 0
        else: 
            self.nestingLevel += 1
            if self.nestingLevel > _Analyzer.maximumNestingLevel:
                raise Exception( "Maximum ({0}) nesting level reached while searching components!".format( _Analyzer.maximumNestingLevel ) )
        
        component, isNew = self.loader.CreateComponent(name, filterName)                
        if component and isNew:
            if component.getProjectType( "debug" ).lower() == '.net' or component.projType == 'cs':
                self.options.projType = 'cs'
            else:
                self.options.projType = 'cpp'
            component.addIncludePaths( self.loader.globalScope )
            component.addLibPaths( self.loader.globalScope )
            try:
                component.components = self.ProcessDependencies( component )
            except Exception, instance:
                if self.options.showStack:
                    traceback.print_tb( sys.exc_traceback )
                raise Exception( '{0}\nIn "{1}"'.format( instance, name ) )
                
            if self.options.useAutoIncludes:
                for c in component.components:
                    dir = [c.directory]
                    component.addIncludePaths( dir )
            if self.options.verblevel >= 3: 
                print 'Have found component {0}'.format( component )
        return component
                
    def _SearchComponentExpression( self, line, patterns ):
        for pattern in patterns:
            match = pattern.search( line )
            if match:
                return match.group( 1 )
        return None
        
    def SearchComponentExpression( self, line ):
        return self._SearchComponentExpression(line, self.componentCppRE)
        
    def addLocals( self, locals = [] ):
        self.loader.addLocals(locals)
    
    def addLocalPath( self, fileName = None ):
        self.loader.addLocalPath(fileName)
        
def Analyzer(globalScope = [], verblevel = 0, options = [], testRun = False ):
    loader = ComponentLoader(globalScope, options, testRun)
    return _Analyzer(globalScope, verblevel, options, loader)

class Applier:
    
    def __init__( self ):
        self.applied = set( [] )
        
    def __call__( self, component, functor ):
        if component not in self.applied:
            self.applied.add( component )
            functor( component )
            for child in component.components:
                self( child, functor )


def for_each( container, functor ):
    applier = Applier()
    for component in container:
        applier( component, functor )
        
if __name__ == '__main__':
    pass
