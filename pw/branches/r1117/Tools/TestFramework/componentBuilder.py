import os
import sys
import builder
import traceback
import componentAnalyzer
from ComponentsSystem import utils
import subprocess
import tempfile


class ComponentBuilder( builder.Builder ):

    def __init__( self, component, platform ):
        self.component = component
        
        if os.path.isfile( self.component ):
            self.component = os.path.normpath( os.path.abspath( self.component ) )
            scope = [os.path.dirname( self.component )]
            scope.extend( componentAnalyzer.getComponentsPaths() )
        else:
            scope = componentAnalyzer.getComponentsPaths()
            for path in scope:
                descriptor = path + "/" + self.component
                if os.path.isfile( descriptor ):
                    self.component = os.path.normpath( os.path.abspath( descriptor ) )
                    break
            scope.append( os.path.dirname( self.component ) )
                    
        self.analyzeSource( scope, platform )
        
    def version( self ):
        return 0;
        
    @staticmethod
    def evaluateComponent( component ):
        
        result = [ str( component ) ]
        
        # evaluate source file hash and libs
        for sources in component.sources.values():
            result.extend( map( lambda item: str( hash( item ) ), sorted( sources ) ) )
        
        # return hash calculation
        #result.extend( map( lambda item: utils.calculateHash( item ), component.libDependencies ) )
        # evaluate source file hash
        #result.extend( map( lambda builder: utils.calculateHash( builder.getSource() ), component.builders ) )
        
        return result

    def analyzeSource( self, scope, opts ):
        
        self.source = []
        
        # evaluate component graph hash
        # if os.path.isfile( self.component ):
            # name = os.path.splitext( os.path.basename( self.component ) )[0]
        # else:
            # name = self.component
        name = os.path.splitext( os.path.basename( self.component ) )[0]
        
        analyzer = componentAnalyzer.Analyzer( globalScope = scope, options = opts )
        root = analyzer.CreateComponent( name )
        
        components = componentAnalyzer.iterateComponents( root )        
        for item in components:
            self.source.append( ComponentBuilder.evaluateComponent( item ) )
        
        root.ProccessComponentsGraph()
        root.RemoveDummyDependencies()
        
        # TODO: implement search on all configurations
        configurationName = "debug"
        self.resultInfo = componentAnalyzer.collectResultInformation( root, configurationName )
    

    def getSource( self ):
        return [str( self )] + self.source + builder.Builder.getSource( self )
            
    def getResultInfo( self ):
        return self.resultInfo
        
    def correctResultInfo( self, output ):
        functor = lambda name: "{path}/{file}".format( path = output, file = name )
        self.resultInfo = map( functor, self.resultInfo )
        
    def collectResult( self ):
        result = self.getResultInfo()
        
        for file in result :
            assert os.path.isfile( file ), file
            
        builder.storeResultHash( self.getSource(), result )

    def __str__( self ):
        return r"Build( {0!s} )".format( self.component )
        
    def __call__( self, options ):
        self.correctResultInfo( options.output )
         
        if self.checkHash( options.verblevel ):
        
            assert options.output.find("$") == -1

            # run build script
            arguments = "{target} --buildcomponent --output={output} --verbose={verbose} --configuration={configuration}".format( target = self.component, output = options.output, verbose = options.verblevel, configuration = options.configuration )
            p = subprocess.Popen( 'run.cmd {0}'.format( arguments ), shell = True, stdin = subprocess.PIPE, stderr = subprocess.PIPE, stdout = subprocess.PIPE )
            textout = p.stdout.read()
            texterr = p.stderr.read()
            p.wait()
            
            if texterr: 
                sys.stderr.write( "Error in {builder}:".format( builder = self ) )
                sys.stderr.write( texterr )

            if options.verblevel >= 1 or p.returncode != 0: print textout
            if p.returncode == 0: self.collectResult()
            
        return None, self.getResultInfo()
