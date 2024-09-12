import os
import sys
import templates
import string
from ComponentsSystem import utils
import uuid
import componentAnalyzer

class FileInfo:
    
    filterSeparator = '/'
    
    class SolutionAdapter:
        
        @staticmethod
        def amp( key ):
            #return key
            index = key.find( "&" )
            if index != -1:
                return string.replace( key, "&", "&amp;" )
            else:
                return key

    
    def __init__( self, file = '', filter = [], ignore = False, compilerKeys = {} ):
        self.file = file
        self.filter = map( FileInfo.SolutionAdapter.amp, filter )
        self.ignore = ignore
        self.compilerKeys = compilerKeys

    def __cmp__( self, other ):
        return cmp( string.lower( self.file ), string.lower( other.file ) )
        
    def __hash__( self ):
        totalHash = hash( 0 )
        for item in self.filter:
            totalHash ^= hash( item )
        for compilerKeys in self.compilerKeys.values():
            for key in compilerKeys:
                totalHash ^= hash( key )
        return hash( self.file ) ^ totalHash ^ hash( self.ignore )
        
    def __repr__( self ):
        return str( self )
    
    def __str__( self ):
        return utils.instance2string( self )
        
    def getCompilerKeys( self, configurationName ):
        return self.compilerKeys.get( configurationName, [] )
        
        
class Configuration:

    configurationNames = [
        'debug',
        'release',
    ]

    def __init__( self, type = "exe", output = None, compilerKeys = [], linkerKeys = [] ):
        
        self.files = set( [] )
        self.type = type
        self.output = output
        self.compilename = ''
        
        self.compilerKeys = set( compilerKeys )
        self.linkerKeys = set( linkerKeys )


class AdditionalBuildProject:
    def __init__( self, filename ):
        self.filename = filename
        ( self.name, self.uuid ) = utils.parseProj( filename )
        self.dependencies = set( [] )

    
    def addDependence( self, uuid ):
        self.dependencies.add( uuid )



class BuildProject:

    def __init__( self, data, platform, output, type, startup ):
        self.platform = platform
        self.files = set( [] )
        self.startup = startup
        self.configurations = {}        
        self.dependencies = set( [] )
        #self.evaluatedSources = set( [] )
        self.charset = ''
                
        self.output = self.evaluateOutput( output )        

        if isinstance( data, str ):
            '''symple string name'''
            self.filterName = ""
            self.compilename = ''
            self.setName( data )

            self.projType = 'other'
            
            for configurationName in Configuration.configurationNames:
                self.configurations[configurationName] = Configuration( output = self.output, type = type )
                
        elif isinstance( data, componentAnalyzer.Component ):
            '''initialize from component'''
            self.compilename = data.descriptor
            self.filterName = data.name
            self.setName( data.shortName )
            self.projType = data.projType
            
            self.addComponent( data )
            
    def evaluateOutput( self, output ):
        if not output: return ""
        else: return output
        
    @staticmethod
    def generateUUID( name ):
        return str( uuid.uuid3( uuid.NAMESPACE_DNS, name ) ).upper()
        
    def __eq__( self, other ):
        return self.projectName == other.projectName and self.platform == other.platform
    
    def __hash__( self ):
        return hash( self.uuid )
        
    def setName( self, name ):
        if not name: name = "empty"
        
        self.projectName = name
        self.uuid = BuildProject.generateUUID( name )
        
    def addFile( self, file, filter = [], ignore = False, compilerKeys = {} ):
        self.files.add( FileInfo( file, filter, ignore, compilerKeys = compilerKeys ) )

    # def detemineOutput( self, file, name ):
        # uniqueName = os.path.basename( file )
        # if uniqueName in self.evaluatedSources:
            # obj = "{0}.{1}.obj".format( string.replace( name, "/", "." ), uniqueName )
            # output = "/Fo&quot;$(IntDir)\{obj}&quot;".format( obj = obj )
            # return output
        # else:
            # self.evaluatedSources.add( uniqueName )
            # return None

    def addComponent( self, component ):
        projectDirectory = os.getcwd()
        for filter, infos in component.sources.iteritems():
            filters = filter.split( FileInfo.filterSeparator )
            for info in infos:
                if os.path.isabs( info.file ): path = info.file
                else: path = component.directory + "/" + info.file

                # output = self.detemineOutput( path, component.name )
                # if output:
                    # # print "CCC", os.path.basename( path ), output
                    # for configurationName in component.configurations.keys():
                        # if not info.HasCompileKey( configurationName, "/Fo" ):
                            # info.addKey( configurationName, output )

                info = FileInfo( path, filter = filters, compilerKeys = info.compilerKeys )
                self.files.add( info )
        
        for configurationName in Configuration.configurationNames:
            self.charset = component.getCharset( configurationName )
            type = component.getType( configurationName ) 
            compilerKeys = component.getCompilerKeys( configurationName )
            linkerKeys = component.getLinkerKeys( configurationName )
            features = component.getFeatures( configurationName )
            
            # print "AAA", component.name, configurationName
            # print compilerKeys
            # print "/AAA"
            
            configuration = self.getConfiguration( configurationName )
            if not configuration:
                configuration = Configuration( type, self.output, compilerKeys, linkerKeys )
                self.setConfiguration( configurationName, configuration )
            else:
                configuration.compilerKeys.update( compilerKeys )
                configuration.linkerKeys.update( linkerKeys )
            
            #print "ZZZ Add component ", configurationName, component.name
            if self.platform in features:
                feature = features[self.platform]                
                #print feature.pchs
                feature.Process( self )
            #print "---"
        
        for dependence in component.components:
            if dependence.project:
                ( projName, projUUID ) = utils.parseProj( dependence.project )
                self.addExternalDependence( projUUID )
            elif dependence.projType == 'cs':
                self.addReference( dependence.name )
            else:
                if dependence.getConfiguration('debug').projectType == '.net':
                    self.addDependence( dependence.shortName + '#CS#' )
                else:
                    self.addDependence( dependence.shortName )
        

    def addDependence( self, project ):
        raise Exception( "Incorrect type for dependence: {0}!".format( type( project ) ) )

    def addReference( self, project ):
        raise Exception( "Incorrect type for reference: {0}!".format( type( project ) ) )

    def addExternalDependence( self, projuuid ):
        self.dependencies.add( projuuid )
        
    def getConfiguration( self, configurationName ):
        configurationName = string.lower( configurationName ) 
        return self.configurations.get( configurationName )
        
    def setConfiguration( self, configurationName, configuration ):
        configurationName = string.lower( configurationName ) 
        self.configurations[configurationName] = configuration
        
    def getProjectName( self ):
        return self.projectName


class CSProject ( BuildProject ):

    def __init__( self, name = '', output = None, type = "exe", startup = False ):
        self.references = set( [] )
        BuildProject.__init__( self, data = name, platform = ".net", output = output, type = type, startup = startup )
        
    def evaluateOutput( self, output ):
        if not output or "" == output or "$(SolutionDir)$(ConfigurationName)" == output: return "$(Configuration)"
        else: return BuildProject.evaluateOutput( self, output )
        
    def addComponent( self, component ):
        if component.projType == 'cs':
            self.references.add( component.name )
        else:
            BuildProject.addComponent( self, component )
        
            for configurationName in Configuration.configurationNames:
                linkerKeys = component.getLinkerKeys( configurationName )
            
                configuration = self.getConfiguration( configurationName )
                # in linker keys we stored references, so get its
                for key in configuration.linkerKeys:
                    # remove &quot;                 
                    if key.find( "/LIBPATH" ) == -1:
                        key = key[len( "&quot;" ):-len( ";&quot" )]
                        self.references.add( key )
            
    def getFrameWorkVersion( self ):
        return "v2.0"
        
    def addDependence( self, project ):
        if isinstance( project, str ):
            self.dependencies.add( ( project, BuildProject.generateUUID( project.replace('#CS#','') ) ) )
        elif isinstance( project, BuildProject ):
            if project.projType == 'cs':
                self.addReference( project.getProjectName() )
            else:
                if project.platform == '.net':
                    self.dependencies.add( ( project.getProjectName()+'#CS#', project.uuid ) )
                else:
                    self.dependencies.add( ( project.getProjectName(), project.uuid ) )
        else:
            BuildProject.addDependence( self, project )

    def addReference( self, project ):
        if isinstance( project, str ):
            self.references.add( project )
        else:
            BuildProject.addDependence( self, project )


class VCProject ( BuildProject ):

    def __init__( self, name = '', output = None, type = "exe", startup = False ):
        self.isClr = False
        BuildProject.__init__( self, data = name, platform = "win32", output = output, type = type, startup = startup )
        
    def evaluateOutput( self, output ):
        if not output or "" == output or "$(Configuration)" == output: return "$(SolutionDir)$(ConfigurationName)"
        else: return BuildProject.evaluateOutput( self, output )
        
    def SetClr( self, val ):
        self.isClr = val
            
    def getCompilerKeys( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return '&#x0D;&#x0A;'.join( sorted( configuration.compilerKeys ) )
        else: return ""
                
    def getLinkerKeys( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return '&#x0D;&#x0A;'.join( sorted( configuration.linkerKeys ) )
        else: return ""
        
    def addDependence( self, project ):            
        if isinstance( project, str ):
            self.dependencies.add( BuildProject.generateUUID( project.replace('#CS#','') ) )
        elif isinstance( project, BuildProject ):
            self.dependencies.add( project.uuid )
        else:
            BuildProject.addDependence( self, project )



class CMakeProject ( BuildProject ):

    def __init__( self, name = '', output = None, type = "exe", startup = False ):
        self.isClr = False
        BuildProject.__init__( self, data = name, platform = "linux", output = output, type = type, startup = startup )
        
    def evaluateOutput( self, output ):
        if not output or "" == output or "$(Configuration)" == output: return "$(SolutionDir)$(ConfigurationName)"
        else: return BuildProject.evaluateOutput( self, output )
        
    def SetClr( self, val ):
        self.isClr = val
            
    def getCompilerKeys( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return '&#x0D;&#x0A;'.join( sorted( configuration.compilerKeys ) )
        else: return ""
                
    def getLinkerKeys( self, configurationName ):
        configuration = self.getConfiguration( configurationName )
        if configuration: return '&#x0D;&#x0A;'.join( sorted( configuration.linkerKeys ) )
        else: return ""
        
    def addDependence( self, project ):            
        if isinstance( project, str ):
            self.dependencies.add( BuildProject.generateUUID( project.replace('#CS#','') ) )
        elif isinstance( project, BuildProject ):
            self.dependencies.add( project.uuid )
        else:
            BuildProject.addDependence( self, project )
