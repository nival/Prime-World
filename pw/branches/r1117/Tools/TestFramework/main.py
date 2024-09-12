import sys
import os
from optparse import OptionParser
import sln
import uuid
import generator
from ComponentsSystem import utils
import fnmatch
import Vendors.SCons.Tool.msvs
import resultgen
import time
import xmlgenerator
import componentAnalyzer
import traceback
import shutil
import platforms
import tempfile
import subprocess
import hash
import eclproj
from copy import deepcopy
from environment import *
from builder import Builder
import BuildProject
import ComponentsSystem
import utils
import templates

Log = resultgen.LogData()
#retcode = 0

configfilename = 'unittest.cfg'

def getCompilerVersion( compiler ):
    try:
        import win32api
        pairs = win32api.GetFileVersionInfo(target, '\\VarFileInfo\\Translation')
        (lang, codepage) = pairs[0]
        path = u'\\StringFileInfo\\%04X%04X\\%%s' %(lang,codepage)
        prodName = win32api.GetFileVersionInfo(target, path%"ProductName")
        prodVersion = win32api.GetFileVersionInfo(target, path%"ProductVersion")
        prodVersionArray = prodVersion.split( '.' )
        prodVersionArray.pop()
        prodVersion = '.'.join(prodVersionArray)
        return prodVersion

    except Exception, e:
        return "9.0.21022"

def parseOptions( parser, argv ):
    ( options, args ) = parser.parse_args( argv )

    if options.arguments:
        file = open( options.arguments, "r" )
        args.extend( [name for name in file.read().split( "\n" ) if name] )
        ( options, args ) = parser.parse_args( args, options )
        file.close()

    data = [
        ( 'compiler', [ 'msvc9', 'msvc8', 'gcc', 'cmake' ] ),
        ( 'platform', [ 'win32', 'linux' ] ),
        ( 'frontend', [ 'console', 'xml', 'web' ] ),
        ( 'configuration', [ 'debug', 'release' ] ),
    ]

    for name, values in data:
        options = utils.parseOption( options, name, set( values ), parser.format_help() )

    if options.stdoutdumper:
        os.environ['AdditionalComponent']+=os.environ['StdOutDumper'];

    if options.output:
        if options.output.find('$') == -1:
            if not os.path.isabs(options.output):
                options.output = '.auto/' + options.output
            options.output = utils.fixBackslashes( os.path.abspath( options.output ) )
            if not os.path.isdir( options.output ):
                os.makedirs( options.output )

    if options.frontend != 'console':
        if options.verblevel == 0: 
            options.verblevel = 1
        options.exceptions = True

    options.devenvversion = getCompilerVersion(options.compiler)

    return ( options, args )


class FileLaunchInformation:

    def __init__( self, file, arguments = '' ):
        self.filename = file
        self.arguments = arguments

    def __repr__( self ):
        return str( self )
        
    def __str__( self ):
        return "{0} {1}".format( self.filename, '\n'.join(self.arguments) ).strip()

extentions = {
    '.h' : '.cpp',
    '.hpp': '.cpp'
}
def normalize( extention ):
    return extentions.get( extention, extention )

def collectFilesFromCommandLine( args ):
    files = {}
    argIdx = 0
    while argIdx < len( args ):
        if os.path.isfile( args[argIdx] ):
            name = args[argIdx]
            arguments = []
            while argIdx + 1 < len( args ):
                argument = args[argIdx + 1]
                if not os.path.isfile( argument ):
                    arguments.append( argument )
                    argIdx += 1
                else:
                    break
            argIdx += 1
            
            ( file, extention ) = os.path.splitext( name )
            extention = normalize( extention )
            info = FileLaunchInformation( os.path.abspath( name ), arguments )
            if extention in files: files[extention].append( info )
            else: files[extention] = [info]
        else:
            sys.stderr.write( "Bad argument: " + args[argIdx] + "\n" )
            argIdx += 1
    return files


def collectFilesFromFile( filename ):
    f = open( filename )
    fstr = f.read()
    f.close()
    
    fargs = fstr.split( ' ' )
    return collectFilesFromCommandLine( fargs )


def cleanUp():
    patterns = [
        '*.auto.*', '*.obj', '*.map', 'testcase_filter', '*.test_declaration', '*.testwrap.cpp', '*.suites',
        '*.testwrap.exe', '*.db.h', '*.pyc', '?', '??', '*.suo', '*.ncb', '*.pch', '*_Release*', '*_Debug*',
        'BuildLog.htm', 'UpgradeLog*.XML', 'UpgradeReport*.*', '*.componentc', '*.applicationc', '*.codegen.*' 
    ]
    files = utils.collectFiles( os.getcwd(), patterns, ignored=['*.svn*'] )
    dirs = utils.collectDirs( os.getcwd(), ['*.auto'], ignored=['*.svn*'] )
    for name in files:
        if os.path.exists(name):
            os.remove(name)
    folders = utils.getEmptyFolders(os.getcwd())     
    for path in folders:
        if '.svn' not in path:
            if os.path.exists(path):
                os.rmdir(path)

    for d in dirs:
        utils.delDirRecursive( os.path.split(d)[0], os.path.split(d)[1] )

def dissolveVcProj(args):
    if len(args) < 3:
        print 'Usage: <vcproj path> <components root path>'
        return 
    import VcProjDissolver        
    VcProjDissolver.main(args[1], args[2])
        
def startPythonHelp():
    PyDir = sys.prefix
    PyDir += '/Doc/'
    listfiles = os.listdir( PyDir )
    for f in listfiles:
        if fnmatch.fnmatch( f, '*.chm' ):
            os.startfile( '"{0}"'.format( PyDir + f ) )
            break


def parseCommandline( argv ):
    '''Analyze command line arguments'''
    parser = OptionParser("%prog [filenames]")
    parser.add_option( "--verbose", type="int", dest="verblevel", help="Set verbose level", default=0 )
    parser.add_option( "--generateOnly", action="store_true", dest="generateOnly", help="Generate projs only", default=False )
    parser.add_option( "--compiler", dest="compiler", type="string", help="Compiler ( msvc9, msvc8, gcc )", default=platforms.getDefaultCompiler() )
    parser.add_option( "--platform", dest="platform", type="string", help="Platform ( win32, linux )", default=platforms.getOS() )
    parser.add_option( "--frontend", dest="frontend", type="string", help="Frontend ( console, xml, web )", default="console" )
    parser.add_option( "--configuration", dest="configuration", type="string", help="Configuration ( debug, release )", default="debug" )
    parser.add_option( "--runner", dest="runner", type="string", default='runner', help="Runner class." )
    parser.add_option( "--cleanup", action="store_true", dest="cleanup", help="Clean up current dir", default=False )
    parser.add_option( "--nonrecursive", action="store_false", dest="recursive", help="Run recursive search test sources", default=True )
    parser.add_option( "--nostarthtml", action="store_false", dest="starthtml", help="Run html automaticly", default=True )
    parser.add_option( "--buildcomponent", action="store_true", dest="buildcomponent", help="Do build component", default=True )
    parser.add_option( "--runapplication", action="store_true", dest="runapplication", help="Run component after build", default=False )
    parser.add_option( "--output", dest="output", type="string", help="Output Dir", default="" )
    parser.add_option( "--filelist", dest="filelist", type="string", help="File with a list of tests", default="" )
    parser.add_option( "--he", dest="exceptions", action="store_true", help="Handle exceptions", default=False )
    parser.add_option( "--enable-SEH", action="store_false", dest="noSEH", help="Force to enable SEH processing.", default=True )
    parser.add_option( "--projectOnly", action="store_true", dest="projectOnly", help="Generate one project", default=False )
    parser.add_option( "--components-paths", type="string", dest="componentsPaths", help="Set component root directory.", default=None )
    parser.add_option( "--arguments", type="string", dest="arguments", help="Set file with arguments.", default=None )
    parser.add_option( "--time", action="store_true", dest="timeTest", help="Write performance times", default=False )
    parser.add_option( "--count", type="int", help="How many times each test should be runned", default=1 )
    parser.add_option( "--testRun", action="store_true", dest="testRun", help="Force testRun=true", default=False )
    parser.add_option( "--showStack", help="Show stack traceback on errors", default=False )
    parser.add_option( "--showTime", help="Show build time ", default=False )
    parser.add_option( "--prebuild", action="store_true", dest="prebuild", help="Internal use only", default=False )
    parser.add_option( "--impl", type="int", dest="impl", help="Which implementation will be used (1-old, 2-new)", default=1 )
    parser.add_option( "--stdoutdumper", action="store_true", dest="stdoutdumper", help="Attach StdOutDumper", default=False )
    parser.add_option( "--useAutoIncludes", action="store_true", dest="useAutoIncludes", help="Force add component path to includePaths", default=False )
    parser.add_option( "--force", action="store_true", dest="force", help="Force builders to run", default=False )
    parser.add_option( "--excludeExtension", action="append", type="string", dest="excludeExtensions", help="Extensions of files  which excluded from processing", default=[] )
    parser.add_option( "--failIfMemoryLeaks", action="store_true", dest="failIfMemoryLeaks", help="Fail tests if memory leacks detected", default=False )


    ( options, args ) = parseOptions( parser, argv )
    if options.timeTest:
        print 'Start RUN'

    retcode = 0
    if options.cleanup:
        cleanUp()
    else:
        if( len(args) > 0 ):
            print 'Platform:{1} Configuration:{0} Compiler:{2}'.format(options.configuration, options.platform, options.compiler)  
            starttime = time.time()

            if args[0] == 'tests':
                if len(args) > 1: dir = args[1]
                else: dir = os.getcwd()
                retcode = findAndRunAllTests( dir, options, options.recursive )
            elif args[0] == 'applications':
                if len(args) > 1: dir = args[1]
                else: dir = os.getcwd()
                retcode = findAndBuildAllApplications( dir, options, options.recursive )
            elif args[0] == 'pyhelp':
                startPythonHelp()
            elif args[0] == 'dissolve_vc':
                dissolveVcProj(args)
            else:
                ct = utils.TimeTest( 'Collect files:', options.timeTest )
                files = collectFilesFromCommandLine( args )
                if options.filelist:
                    files.update( collectFilesFromFile( options.filelist ) )
                del ct
                retcode = processFiles( files, options )
            endtime = time.time()

            if options.frontend == 'xml':
                xmlgenerator.createXmlDoc( 'log.xml', Log, endtime - starttime )
            elif options.frontend == 'web':
                xmlgenerator.createXmlDoc( 'report.xml', Log, endtime - starttime )
                if options.starthtml and Log.results:
                    report = os.path.abspath( '.auto/.xml/report.xml' )
                    os.startfile( report )
            else:
                if options.showTime:
                    print 'All time:', endtime - starttime

            for res in Log.results:
                if res.errorstr:
                    retcode = 1

        else:
            if options.filelist:
                files = {}
                files.update( collectFilesFromFile( options.filelist ) )
                retcode = processFiles( files, options )
            else:
                parser.print_help()

    if options.timeTest:
        print 'End RUN'
        
    return retcode


def pregenerateStep( components, options ):
    # TODO: implemet
    return components   


def generateBuildFiles( title, components, commandLine, options ):
    # TODO: implemet
    tempScope = utils.changeScope( '.temp' )
    
    slnName = '%s.sln' % title  
    if options.verblevel >= 2: print '\n--- Start generation: %s ---' % slnName
    
    # projects = list( generateProjects( sources, title, components, options, maincomponent ) )
    # runBuilders( projects, options )
    # solutionfiles = []#generateComponentsGraph( sources, options, maincomponent )

    # sln.createSLN( projectName, projects, commandLine, solutionfiles, options.verblevel )

    updatedFiles = checkToRealModifySLN( options )
    for f in updatedFiles:
        shutil.copy( f, '..' )
    
    return [slnName]


def build( buildFiles ):
    # TODO: implemet
    pass


def run( binaries ):
    # TODO: implemet
    pass


def generateBuildRun( sources, project, components, options, maincomponent = None, filetorun = None ):
    #pregenerate step

    # Because Eclipse workspace
    if options.compiler == 'gcc':
        project = 'Test'

    rbt = utils.TimeTest( 'Run builders:', options.timeTest )
    runBuilders( components, options )
    del rbt
    
    # generate components graph
    gcgt = utils.TimeTest( 'Generate components graph:', options.timeTest )

    if not options.projectOnly: ( graph, duplicates ) = generateComponentsGraph( project, components, options )
    else: ( graph, duplicates ) = None, None

    # make one root structure for tests
    if sources:
        root = componentAnalyzer.Component( options = options )
        root.inlined = True
        
        for component in components:
            if component != root:
                root.components.add( component ) 
        components = [ root ]

    #  optimize components graph
    for component in components:
        component.ProccessComponentsGraph()
        component.RemoveDummyDependencies()
        #component.PrintKeys()
        component.EvaluateSources()
    del gcgt

    # print "----------------"
    # print components
    # print "----------------"
    
    # TODO: refactor - extract method
    ut = utils.TimeTest( 'Test hash time:', options.timeTest )
    updated = False
    componentsWereUpdated = False
    if not os.path.isfile( configfilename ):
        if options.verblevel >= 2: 
            print 'md5hash file not found: ', configfilename
        updated = True
    else:
        ( numberOfUpdatedComponents, updatedComponents, presented ) = isComponentsUpdated( components, configfilename, options ) 
        ( sourcesWereUpdated, updatedSources ) = isFilesUpdated( sources, configfilename, options )
        if options.verblevel >= 2: 
            for component in updatedComponents:
                print 'component descriptor was updated:', component.descriptor
                # print "----------------"
                # print component
                # print "----------------"
            for file in updatedSources:
                print 'source was updated:', file
        updated = numberOfUpdatedComponents != 0 or sourcesWereUpdated
        updated |= areGenerationResultPresent( project, options )
        componentsWereUpdated = presented and numberOfUpdatedComponents != 0
    del ut

    st = utils.TimeTest( 'Stuff time:', options.timeTest )
        
    #generate build files
    if updated:
        if options.compiler == 'msvc9' or options.compiler == 'msvc8':
            updated = generateSln( sources, project, components, ( graph, duplicates ), options, maincomponent ) > 0
        elif options.compiler == 'gcc':
            updated = generateEclipseProject( sources, project, components, ( graph, duplicates ), options, maincomponent ) > 0
        elif options.compiler == 'cmake':
            updated = generateCMakeProject( sources, project, components, ( graph, duplicates ), options, maincomponent ) > 0
        map( lambda i: utils.setHashForFile( i.filename, configfilename ), sources )
        utils.storeComponentsHash( components, options, configfilename )

    planeList = set( [] )
    for component in components:
        planeList.update( componentAnalyzer.iterateComponents( component ) )
    utils.storeComponentsHash( planeList, options, configfilename )

    if options.generateOnly:
        if updated and options.prebuild:
            sys.stderr.write("Project changed!\n")
            sys.exit( 1 )
        else: return 0
        #return 0
        
    if not filetorun:
        filetorun = project
    del st

    brt = utils.TimeTest( 'Build/run time:', options.timeTest )
    #start build process
    retcode = 0
    if not maincomponent or options.buildcomponent:
        if options.compiler == 'msvc9' or options.compiler == 'msvc8':
            res, text = buildTest( project, options )
        elif options.compiler == 'cmake':
            res, text = buildCMakeTest( project, options )
        elif options.compiler == 'gcc':
            res, text = buildTestEclipse( project, options )
        if res:
            if not maincomponent or options.runapplication:
                if options.output:
                    outputpath = options.output+'/'
                elif options.compiler != 'gcc':
                    outputpath = utils.fixBackslashes( os.path.abspath( "." ) + '/%s/' % options.configuration )
                else:
                    outputpath = utils.fixBackslashes( os.path.abspath( "." ) + '/%s/%s/' % ( project, options.configuration ) )

                if options.platform == 'win32':
                    filetorun = '%s%s.exe' % ( outputpath, filetorun )
                    runTests( filetorun, options, '{0}/{1}'.format( os.getcwd(), project ), sources )
                elif options.platform == 'linux':
                    filetorun = 'ctest .'
                    runTests( filetorun, options, '', sources )
                else:
                    sys.stderr.write( "Bad platform type: " + options.platform + "\n" )

        else:
            #global retcode
            sys.stderr.write( "\nError building " + filetorun + "\n" )
            retcode = 1
            if options.frontend == 'xml' or  options.frontend == 'web':
                res = resultgen.generateBadBuildResult( sources, text, 0 )
                Log.results.extend( res )
    del brt

    return retcode


def determineComponents( sources, options, testRun = False ):
    '''Try to find components in iterable list'''
    if not isinstance( sources, list ):
        raise Exception( 'sources type is {0} but should be list of FileLaunchInformation!'.format( type( sources ) ) )

    analizer = createAnalyzer( options, testRun = testRun )
    components = set( [] )
    try:
        for info in sources:
            components.update( analizer.Scan( info.filename ) )
    except Exception, instance:
        if options.showStack:
            traceback.print_tb( sys.exc_traceback ) 
        raise Exception( '{0}\nCan\'t process file "{1}" while finding components...'.format( instance, info.filename ) )
    return components


def processCpp( sources, options ):
    '''Process *.h or *.cpp file'''
    retcode = 0

    options.projType = 'cpp'
    options.testRun = True

    try:        
        project = "runner.auto"
        dir = utils.changeScope()
        if len( sources ) == 1:
            project = os.path.splitext( os.path.basename(sources[0].filename) )[0]

        components = determineComponents( sources, options, options.testRun )
        #updated = generateBuildRun( sources, project, components, options )
        retcode = generateBuildRun( sources, project, components, options )
        #if updated and options.generateOnly:            
            #global retcode
            #retcode = 1

    except utils.MSVCInfoException as info:
        print info.value
        retcode = 1
    except Exception, instance:
        if options.showStack:
            traceback.print_tb( sys.exc_traceback ) 
        sys.stderr.write( '{0}\nCan\'t run cpp tests\n'.format( instance ) )        
        #global retcode
        retcode = 1
    except:
        traceback.print_exc() 
        raise
    
    return retcode


def processCs( sources, options ):
    '''Process *.cs'''
    retcode = 0

    options.projType = 'cs'
    
    try:
        dir = utils.changeScope()
        project = "runner.cs.auto"
        if len( sources ) == 1:
            project = os.path.splitext( os.path.basename(sources[0].filename) )[0]

        components = determineComponents( sources, options )
        updated = generateBuildRun( sources, project, components, options )
        if updated and options.generateOnly:
            #global retcode
            retcode = 1

    except Exception, instance:
        if options.showStack:
            traceback.print_tb( sys.exc_traceback ) 
        sys.stderr.write(  '{0}\nCan\'t run component.'.format( instance ) )
        #global retcode
        retcode = 1
    except:
        traceback.print_exc() 
        raise
        
    return retcode


def processPython( sources, options ):
    '''Process *.py file'''

    options.projType = 'py'
    
    if options.generateOnly:
        return 0
            
    for info in sources:
        starttime = time.time()
        name = utils.shortName( info.filename )
        runCommandList = [ info.filename ]
        runCommandList.extend( info.arguments )
        if options.verblevel >= 1:
            runCommandList.append( '-v' )
        textout, texterr = utils.runSubprocess( runCommandList )
        if options.frontend == 'console':
            print textout, texterr
        elif options.frontend == 'xml' or  options.frontend == 'web':
            endtime = time.time()
            res = resultgen.generateTestResult( info.filename, textout, texterr, endtime-starttime )
            Log.results.extend( res )
            Log.rawText += textout + texterr
            Log.memoryLeaks += resultgen.getMemoryLeaksInfo( textout+texterr )
            
    return 0

def processComponent( sources, options ):
    '''Process *.component and *.application file'''
    
    if options.impl == 2:
      ComponentsSystem.ProcessComponents(sources, options)
      return 0

    options.projType = 'component'
    
    retcode = 0
    try:
        ft = utils.TimeTest( 'Find comps:', options.timeTest )
        ( directory, file ) = os.path.split( sources[0].filename )
        ( name, extention ) = os.path.splitext( file )
        if options.prebuild and hasattr(options,"arguments"):
            dir = os.path.split(options.arguments)[0];
            dir = utils.changeScope( dir )
        else:
            dir = utils.changeScope( name + ".auto" )
                
        components = []
        try:
            analyzer = createAnalyzer( options, testRun = options.testRun )
            for info in sources:
                name = os.path.splitext( os.path.basename( info.filename ) )[0]
                directory = os.path.dirname( info.filename )
                if name == "all":                    
                    name = os.path.basename( directory )
                    directory = os.path.dirname( directory )
                analyzer.addLocalPath( directory )
                if len(info.arguments) > 0:
                    components.append( analyzer.CreateComponent( name, filterName = str(info.arguments[0]) ) )
                else:
                    components.append( analyzer.CreateComponent( name ) )

        except Exception, instance:
            if options.showStack:
                traceback.print_tb( sys.exc_traceback )
            raise Exception( '{0}\nCan\'t process file "{1}"\nwhile finding components...'.format( instance, info.filename ) )

        root = components[0]
        root.inlined = False
        del ft
        
        if len( sources ) == 1: title = os.path.basename( root.name )
        else: title = "runner.auto"
        
        retcode = generateBuildRun( [], title, set( components ), options, root, os.path.splitext(file)[0] )

    except Exception, instance:
        if options.showStack:
            traceback.print_tb( sys.exc_traceback ) 
        sys.stderr.write( '{0}\nCan\'t run component.\n'.format( instance ) )
        retcode = 1
    except:
        #traceback.print_exc() 
        retcode = 1
        sys.exit( retcode )

    return retcode


def processJava( sources, options ):
    '''Process *.java file'''

    options.projType = 'java'
    
    if options.generateOnly:
        return 0
            
    for info in sources:
        starttime = time.time()
        name = utils.shortName( info.filename )
        curpath = os.path.abspath('.')
        junitpath = None
        if 'TestFrameworkPath' in os.environ:
            junitpath = os.path.abspath( os.environ['TestFrameworkPath'] ) + '/Vendors/JUnit/JUnit.jar'
        runCommandList = [ 'javac', '-d '+ curpath, '-cp .;' + junitpath, info.filename, info.arguments ]
        utils.runSubprocess( runCommandList )
        classfilename = os.path.basename(info.filename)
        classfilename = utils.replaceSubStr( classfilename, '.java', '' )
        runCommandList = [ 'java', '-cp .;' + junitpath, 'org.junit.runner.JUnitCore', classfilename, info.arguments ]
        textout, texterr = utils.runSubprocess( runCommandList )
        if options.frontend == 'console':
            print textout, texterr
        elif options.frontend == 'xml' or  options.frontend == 'web':
            endtime = time.time()
            res = resultgen.generateTestResult( sources, textout, texterr, endtime-starttime )
            Log.results.extend( res )
            Log.rawText += textout + texterr
            Log.memoryLeaks += resultgen.getMemoryLeaksInfo( textout+texterr )

    return 0

processors = {
    '.cpp' : processCpp,
    '.py' : processPython,
    '.cs' : processCs,
    '.java' : processJava,
    '.component' : processComponent,
    '.application' : processComponent,
}


def processFiles( dic, options, badExts = set([]) ):
    retcode = 0
    for extention, sources in dic.iteritems():
        if extention in processors:
            if not extention in badExts:
                if processors[extention]( sources, options ) != 0: retcode = 1
        else:
            raise Exception( "Unsupported file type: {0}".format( extention ) )
    
    return retcode


def testFileContain( filename, listkeywors ):
    file = open( filename, 'r' )
    filestr = file.read()
    file.close()

    for keyword in listkeywors:
        if filestr.find( keyword ) != -1:
            return True

    return False


def testForContainTestsPy( filename ):
    return testFileContain( filename, [ 'unittest' + '.main()' ] )


def testForContainTestsCpp( filename ):
    return testFileContain( filename, [ 'CxxTest::TestSuite', 'CxxTest::TestCase', 'TestCase' ] )


def testForContainTestsCs( filename ):
    return testFileContain( filename, [ '[TestFixture]' ] )


testsAnalyzers = {
    '.cpp' : testForContainTestsCpp,
    '.py' : testForContainTestsPy,
    '.cs' : testForContainTestsCs,
}

def collectTests( files ):
    result = {}
    for file in files:
        ( name, extention ) = os.path.splitext( file )
        extention = normalize( extention )
        if extention in testsAnalyzers and testsAnalyzers[extention]( file ):
            info = FileLaunchInformation( file )
            if extention in result: result[extention].append( info )
            else: result[extention] = [info]
    return result


def collectApplications( file ):
    result = {}
    ( name, extention ) = os.path.splitext( file )
    extention = normalize( extention )
    info = FileLaunchInformation( file )
    if extention in result: result[extention].append( info )
    else: result[extention] = [info]
    return result

def filterExtentionsByExcludes(arrayExt, arrayExc):
  
  if not len(arrayExc):
    return arrayExt
    
  arrayResult = []
  isInclude=False
  
  for x in arrayExt:
    for y in arrayExc:
      if y in x:
        isExclude=True
    if not isExclude:
      arrayResult.append(x)
    isExclude=False
        
  return arrayResult

def findAndRunAllTests( dirname, options, recursive = True ):
    if options.verblevel >= 1:
      print 'findAndRunAllTests...'
      print '...excludeExtensions: {0}'.format(options.excludeExtensions)
    
    extensions = [ '*.py', '*.test.h', '*.test.cpp', '*.test.cs' ]
    extensions4Tests = filterExtentionsByExcludes(extensions, options.excludeExtensions)
    
    if options.verblevel >= 1:
      print '...extensions4Tests: {0}'.format(extensions4Tests)
    
    retcode = 0
    directory = os.path.abspath( dirname )
    files = collectTests( utils.collectFiles( directory, extensions4Tests, recursive = recursive ) )
    if len( files ) : retcode = processFiles( files, options, set(['.component','.application']) )
    else : sys.stderr.write( "No one tests were found!\n" )
    return retcode

def findAndBuildAllApplications( dirname, options, recursive = True ):
    directory = os.path.abspath( dirname )
    isAllOk = True
    for f in utils.collectFiles( directory, ['*.application'], recursive = recursive ):
        files = collectApplications( f )
        if len( files ): 
            ( name, extention ) = os.path.splitext( os.path.split( f )[1] )
            dir = utils.changeScope('.auto/'+name)
            #TODO
            args = ['run.cmd']
            args.append(str(f))
            for i in xrange(2,len(sys.argv)):
                args.append(sys.argv[i])
            if utils.runSubprocessInteractive( args ) != 0:
                isAllOk = False
                sys.stderr.write( "Build " + str(f) + " Failed!\n" )
            else:
                sys.stderr.write( "Build " + str(f) + " OK!\n" )
            del dir
        cleanUp()
    if not isAllOk:
        sys.exit( 1 )
        
    

def isFilesUpdated( files, storage, options ):
    updated = set([])
    for info in files:
        if utils.testHashForFile( os.path.abspath( info.filename ), storage, options ):
            updated.add( info.filename )
    return len( updated ), updated 

    
def isComponentsUpdated( components, storage, options ):
    updatedComponents = set([])
    presented = True
    for component in components:
        changed, presentInStrorage = utils.testHashForString( component.descriptor, str( component ), storage, options )
        presented &= presentInStrorage
        if changed: updatedComponents.add( component )
    return len( updatedComponents ), updatedComponents, presented


def areGenerationResultPresent( projectName, options ):

    slnName = "{0}.sln".format( projectName )
    
    if not options.projectOnly:
        if not os.path.isfile( slnName ):
            if options.verblevel >= 2: 
                print 'Solution not found: ', slnName
            return True
    
    if options.verblevel >= 2: 
        print 'No need to generate solution'
    return False

def runTests( runCommand, options, xml, sources ):
    starttime = time.time()

    if options.verblevel >= 2: 
        print '\n--- Start testing: ---'
        print 'Run command:', runCommand

    if options.platform == 'win32':
        runCommand = '\"' + runCommand + '\"'
    runCommandList = []
    runCommandList.append( runCommand )
    if options.frontend != 'console' or options.verblevel == 0:
        retcode, textout, texterr = utils.runSubprocess( runCommandList, True )
        if options.frontend == 'console':
            print textout, texterr
            memoryLeaks = resultgen.getMemoryLeaksInfo( textout+texterr )
            if len(memoryLeaks) > 0 and options.failIfMemoryLeaks:
              raise Exception("Memory leaks detected")
            if retcode != 0:
              raise Exception("Return code from runTests !=0 ")
        elif options.frontend == 'xml' or  options.frontend == 'web':
            endtime = time.time()
            res = resultgen.generateTestResult( sources, textout, texterr, endtime-starttime )
            Log.results.extend( res )
            Log.rawText += textout + texterr
            Log.memoryLeaks += resultgen.getMemoryLeaksInfo( textout+texterr )
    else:
        utils.runSubprocessInteractive( runCommandList )


def buildTest( file, options ):
    '''Build command file.'''
    compiler = getCompiler(options.compiler)
    if compiler == None:
        return False, '--- Build aborted! ---'
    else:
        buildCommand = [
            '%s' % compiler, 
            '%s.sln' % file,  
            '/build %s' % options.configuration,
        ]
        if options.verblevel >= 1: 
            print '\n--- Start building: %s.sln ---\nBuild command: %s ---' %  ( file, ' '.join( buildCommand ) )

        if options.frontend != 'console' or options.verblevel == 0:
            textout, texterr = utils.runSubprocess( buildCommand )
            res, text = resultgen.parseBuildResult( textout, texterr, options )
            sys.stderr.write( text )
            if options.verblevel >= 1:
                Log.buildLog = textout + texterr
                print textout           
            return res, text
        else:
            result = utils.runSubprocessInteractive( buildCommand )
            return result == 0, ''

        return True, ''
    
def buildCMakeTest( file, options ):
    os.chdir( file )
    buildCommand = [
        'cmake', 
        '.',
    ]
    if options.verblevel >= 1: 
        print '\n--- Start building: %s ---\nBuild command: %s ---' %  ( file, ' '.join( buildCommand ) )
    
    result = utils.runSubprocessInteractive( buildCommand )
    if result == 0 :
        result = utils.runSubprocessInteractive( [ 'make' ] )
    return result == 0, ''

def buildTestEclipse( file, options ):
    '''Build command file.'''

    #TODO
    if 'EclipsePath' in os.environ:
        if options.platform == 'win32':
            eclipsePath = os.environ['EclipsePath'] + '/eclipse.exe'
        elif options.platform == 'linux':
            eclipsePath = os.environ['EclipsePath'] + '/eclipse -vm /usr/java/jre1.6.0_11/bin/'
        else:
            sys.stderr.write( "Bad platform type: " + options.platform + "\n" )
    else:
        sys.stderr('Eclipse not found')
        sys.exit(1)

    workspacePath = os.path.abspath( '.' )

    buildCommand = ['%s' % eclipsePath, '-data %s' % workspacePath,  '-nosplash -application org.eclipse.jdt.apt.core.aptBuild -vmargs -Dorg.eclipse.cdt.core.console=org.eclipse.cdt.core.systemConsole' ]
    if options.verblevel >= 1: 
        print '\n--- Start building: %s.sln ---\nBuild command: %s ---' %  ( file, ' '.join( buildCommand ) )

    if options.frontend != 'console' or options.verblevel == 0:
        textout, texterr = utils.runSubprocess( buildCommand )
        res, text = resultgen.parseBuildResult( textout, texterr, options )
        sys.stderr.write( text )
        if options.verblevel >= 1:
            Log.buildLog = textout + texterr
            print textout           
        return res, text
    else:
        result = utils.runSubprocessInteractive( buildCommand )
        return result == 0, ''

    return True, ''


def getCompiler( compiler = 'msvc9' ):
    if compiler == 'msvc9':
        return getMSVC( '9.0' )
    elif compiler == 'msvc8':
        return getMSVC( '8.0' )


def getMSVC( version = '9.0' ):
    '''I banned early versions of msvc, all below 8.0.'''
    dirs = Vendors.SCons.Tool.msvs.get_msvs_install_dirs( version )
    if 'VSINSTALLDIR' in dirs:
        compiler = dirs['VSINSTALLDIR'] + 'Common7\IDE\devenv.com'
        return utils.fixBackslashes( '\"%s\"' % compiler )
    else:
        sys.stderr.write( 'Can\'t find MSVS %s!\n' % version )
        return None


def checkToRealModifySLN( options ):
    listfiles = os.listdir( '.' )
    new = []
    modified = []
    for f in listfiles:
        if os.path.isfile( '../' + f ):
            if utils.md5( f ) != utils.md5( '../' + f ):
                if options.verblevel >= 2: 
                    print 'File was changed:', f
                modified.append( f )
        else:
            if options.verblevel >= 2: 
                print 'Not found file:', f
            new.append( f )
    if not len( modified ) and options.verblevel >= 2: 
        print 'Solution was not modified'
    return modified + new


def generateSln( sources, projectName, components, componetsGraphFiles, options, maincomponent = None ):
    '''Check md5 hash of <testfile>. If it's differ from previose then regenerate solution and vcproj.'''

    if options.verblevel >= 2: print '\n--- Start generation %s ---' % projectName
    newsc = utils.changeScope( '.temp' )
    
    planeList = set( [] )
    for component in components:
        planeList.update( componentAnalyzer.iterateComponents( component ) )

    #for component in planeList:
    #    print "FFF", component.name
    #    for configurationName, configuartion in component.configurations.iteritems():
    #        print configurationName, configuartion.compilerKeys
    #        print configurationName, configuartion.sharedCompilerKeys
    #    print "---"

    additionalProjects = []
    removed = []
    for comp in planeList:
        if comp.project:
            addproject = BuildProject.AdditionalBuildProject( comp.project )
            for dep in comp.components:
                if dep.project:
                    temp = BuildProject.AdditionalBuildProject( dep.project )
                    addproject.addDependence( temp.uuid )
                else:
                    sys.stderr.write( "Dependence in project component not supported!" )
            additionalProjects.append( addproject )
            removed.append( comp )

    projects = list( generateProjects( sources, projectName, planeList, options, maincomponent, removed ) )
    
    files = ''
    if not maincomponent:
        files = '\n'.join( map( lambda x: str( x ), sources ) )
    else:
        files = maincomponent.descriptor

    # TODO: pass run command arguments
    # paths = options.componentsPaths
    # if not paths:
        # for source in sources:
            # ( directory, file ) = os.path.split( source.filename )
            # if not paths: paths = directory
            # else: paths += ";" + directory
            
    # construct arguments
    runArguments = []
    # if paths: runArguments = ["--components-paths=" + paths]

    if options.testRun:
        runArguments.append( "--testRun" )

    if not options.noSEH: runArguments.append( "--enable-SEH" )

    if options.projectOnly:
        sln.createProjects( options, projects, files, runArguments = runArguments )
    else:
        sln.createSLN( projectName, options, projects, files, componetsGraphFiles, runArguments = runArguments, additionalProjects = additionalProjects )
  
    updatedFiles = checkToRealModifySLN( options )
    if os.path.isdir( '../old' ):
        shutil.rmtree( '../old' )
    os.makedirs( '../old' )
    if os.path.isdir( '../new' ):
        shutil.rmtree( '../new' )
    os.makedirs( '../new' )
    for f in updatedFiles:
        if os.path.isfile( '../'+f ):
            shutil.copy( '../'+f, '../old' )
        shutil.copy( f, '../new' )
        shutil.copy( f, '..' )

    stopBuildFiles = [ '.vcproj', '.sln', '.csproj' ]

    for f in updatedFiles:
        for s in stopBuildFiles:
            if f.find( s ) != -1:
                return len( updatedFiles )
        
    return 0


def generateEclipseProject( sources, projectName, components, componetsGraphFiles, options, maincomponent = None ):
    '''Check md5 hash of <testfile>. If it's differ from previose then regenerate solution and vcproj.'''
    if options.verblevel >= 2: print '\n--- Start generation %s ---' % projectName
    newsc = utils.changeScope( '.temp' )
    
    planeList = set( [] )
    for component in components:
        planeList.update( componentAnalyzer.iterateComponents( component ) )
    projects = list( generateProjects( sources, projectName, planeList, options, maincomponent, [] ) )
    
    files = ''
    if not maincomponent:
        files = ' '.join( map( lambda x: str( x ), sources ) )
    else:
        files = maincomponent.descriptor

    # TODO: pass run command arguments
    # paths = options.componentsPaths
    # if not paths:
        # for source in sources:
            # ( directory, file ) = os.path.split( source.filename )
            # if not paths: paths = directory
            # else: paths += ";" + directory 
            
    # construct arguments
    # if paths: runArguments = ["--components-paths=" + paths]
    # else: runArguments = [""]
    
    runArguments = [""]    
    if not options.noSEH: runArguments.append( "--enable-SEH" )
    runArguments = " ".join( runArguments )
    
    if options.projectOnly:
        eclproj.createEclipseProject( projectName, options, projects, files, componetsGraphFiles, runArguments = runArguments )
    else:
        eclproj.createEclipseProject( projectName, options, projects, files, componetsGraphFiles, runArguments = runArguments )
  
    updatedFiles = checkToRealModifySLN( options )
    for f in updatedFiles:
        shutil.copy( f, '..' )
    
    return len( updatedFiles )


def getLibName( name ) :
    lib_name = name.replace( "/", "_" )
    lib_name = lib_name.replace( "\\", "_" )
    return lib_name

def shortenLibName( name, all_names ) :
    if len( name ) >= 25 :
        nn = name[ : 10 ] + "___" + name[ len( name ) - 10 : ]
        if nn not in set( all_names.values() ) : return nn
        i = 0
        while ( nn + str( i ) ) in set( all_names.values() ) :
            i += 1
        return nn + str( i )
    return name

def generateCMakeProject( sources, projectName, components, componetsGraphFiles, options, maincomponent = None ):

    if options.verblevel >= 2:
        print '\n--- Start generation %s ---' % projectName

    cmake_path = projectName
    if not os.path.isdir( cmake_path ) :
        os.makedirs( cmake_path )

    is_test = projectName.endswith( ".test" )

    cmake_file = open( cmake_path + '/CMakeLists.txt', 'w')
    cmake_file.write('CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )\n\n')
    cmake_file.write('PROJECT( ' + projectName + ' )\n\n')

    libs = {}
    lib_names = {}
    include_paths = set()
    defines = set()
    compiler_options = set()
    libPaths = set()
    libDeps = set()

    if components:       
        for c in components:
            cfg = c.getConfiguration( options.configuration )
            for kk in cfg.linkerKeys :
                key = kk.replace( "&quot;", "" ).strip()
                if key.startswith("/LIBPATH:") :
                    libPaths.add( key[ 9 : ] )
                else :
                    libDeps.add( key )
            
            for cc in c.getCompilerKeys( options.configuration ) :
                if cc.startswith( "-I" ) :
                    include_paths.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                elif cc.startswith( "-D" ) or cc.startswith( "/D" ) :
                    defines.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                else :
                    if cc.startswith( "-" ) or cc.startswith( "/" ) :
                        compiler_options.add( "-" + cc[ 1: ] )
            
            for (name, items) in c.sources.items():
                for item in items:
                    fname = item.file.replace("\\", "/")
                    if not fname.endswith( ".cpp" ) and not fname.endswith( ".c" ) :
                        continue
                    #include_paths.add( os.path.dirname( fname ) )
                    if name not in libs :
                        libs[ name ] = set([ item.file ])
                        lib_name = getLibName( name )
                        lib_names[ name ] = lib_name
                    else : libs[ name ].add( item.file )
                    if options.configuration in item.compilerKeys :
                        for cc in item.compilerKeys[ options.configuration ] :
                            if cc.startswith( "-I" ) :
                                include_paths.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                            elif cc.startswith( "-D" ) or cc.startswith( "/D" ) :
                                defines.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                            else :
                                if cc.startswith( "-" ) or cc.startswith( "/" ) :
                                    compiler_options.add( "-" + cc[ 1: ] )

    if maincomponent:
        cfg = maincomponent.getConfiguration( options.configuration )
        for kk in cfg.linkerKeys :
            key = kk.replace( "&quot;", "" ).strip()
            if key.startswith("/LIBPATH:") :
                libPaths.add( key[ 9 : ] )
            else :
                libDeps.add( key )

        for cc in maincomponent.getCompilerKeys( options.configuration ) :
            if cc.startswith( "-I" ) :
                include_paths.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
            elif cc.startswith( "-D" ) or cc.startswith( "/D" ) :
                defines.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
            else :
                if cc.startswith( "-" ) or cc.startswith( "/" ) :
                    compiler_options.add( "-" + cc[ 1: ] )
        
        for (name, items) in maincomponent.sources.items():
            for item in items:
                fname = item.file.replace("\\", "/")
                if not fname.endswith( ".cpp" ) and not fname.endswith( ".c" ) :
                    continue
                #include_paths.add( os.path.dirname( fname ) )
                if name not in libs :
                    libs[ name ] = set([ item.file ])
                    lib_name = getLibName( name )
                    lib_names[ name ] = lib_name
                else : libs[ name ].add( item.file )
                if options.configuration in item.compilerKeys :
                    for cc in item.compilerKeys[ options.configuration ] :
                        if cc.startswith( "-I" ) :
                            include_paths.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                        elif cc.startswith( "-D" ) or cc.startswith( "/D" ) :
                            defines.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                        else :
                            if cc.startswith( "-" ) or cc.startswith( "/" ) :
                                compiler_options.add( "-" + cc[ 1: ] )

        for c in maincomponent.components:
            cfg = c.getConfiguration( options.configuration )
            for kk in cfg.linkerKeys :
                key = kk.replace( "&quot;", "" ).strip()
                if key.startswith("/LIBPATH:") :
                    libPaths.add( key[ 9 : ] )
                else :
                    libDeps.add( key )
            
            for cc in c.getCompilerKeys( options.configuration ) :
                if cc.startswith( "-I" ) :
                    include_paths.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                elif cc.startswith( "-D" ) or cc.startswith( "/D" ) :
                    defines.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                else :
                    if cc.startswith( "-" ) or cc.startswith( "/" ) :
                        compiler_options.add( "-" + cc[ 1: ] )
            
            for (name, items) in c.sources.items():
                for item in items:
                    if not item.file.endswith( ".cpp" ) :
                        continue
                    if name not in libs :
                        libs[ name ] = set([ item.file ])
                        lib_name = getLibName( name )
                        lib_names[ name ] = lib_name
                    else : libs[ name ].add( item.file )
                    for cc in item.compilerKeys[ options.configuration ] :
                        if cc.startswith( "-I" ) :
                            include_paths.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                        elif cc.startswith( "-D" ) or cc.startswith( "/D" ) :
                            defines.add( cc[ 2: ].replace( "&quot;", "" ).strip() )
                        else :
                            if cc.startswith( "-" ) or cc.startswith( "/" ) :
                                compiler_options.add( "-" + cc[ 1: ] )

    if options.configuration == "debug" :
        compiler_options.add( "-g" )

    # print libDeps
    # print libPaths

    flags = " ".join( [ "-D" + d for d in defines ] )
    flags += " " + " ".join( [ co for co in compiler_options ] )
    if len( flags ) > 0 :
        cmake_file.write( 'SET(CMAKE_CXX_FLAGS "${CXX_FLAGS} ' + flags + '")\n\n' )

    for ipth in include_paths :
        cmake_file.write( "INCLUDE_DIRECTORIES( {0} )\n".format( ipth ) )
    cmake_file.write( "\n" )
    for ipth in libPaths :
        cmake_file.write( "LINK_DIRECTORIES( {0} )\n".format( ipth ) )

    cmake_file.write( "\n##################################################################\n" )
    cmake_file.write( "#\n" )
    cmake_file.write( "# Library names\n" )
    cmake_file.write( "#\n" )
    cmake_file.write( "##################################################################\n" )
    vrs = {}
    for ln in sorted( sorted( lib_names.keys() ) ) :
        lib_name = lib_names[ ln ]
        vrs[ lib_name ] = shortenLibName( lib_name, vrs )
        cmake_file.write( "SET( {0:<49} {1}-st )\n".format( lib_name.upper(), vrs[ lib_name ] ) )
    cmake_file.write( "\n" )

    cmake_file.write( "FIND_PACKAGE( CxxTest )\n" )
    cmake_file.write( "IF ( CXXTEST_FOUND )\n" )
    cmake_file.write( "  INCLUDE_DIRECTORIES( ${CXXTEST_INCLUDE_DIR} )\n" )
    cmake_file.write( "ELSE ( CXXTEST_FOUND )\n" )
    cmake_file.write( "  MESSAGE( FATAL_ERROR \"CxxTest not found!\" )\n" )
    cmake_file.write( "ENDIF ( CXXTEST_FOUND )\n\n" )

    for c in libs :
        lib_name_var = "${" + lib_names[ c ].upper() + "}"
        cmake_file.write( "##################################################################\n" )
        cmake_file.write( "#\n" )
        cmake_file.write( "# {0}\n".format( c ) )
        cmake_file.write( "#\n" )
        cmake_file.write( "##################################################################\n" )
        cmake_file.write( "ADD_LIBRARY( {0:<41} STATIC\n".format( lib_name_var ) )
        for src in sorted( libs[ c ] ):
            file_path = src.replace( "\\", "/" )
            cmake_file.write( "{0:>54} {1}\n".format( " ", file_path ) )
        cmake_file.write( "{0:>55})\n".format( " " ) )
        cmake_file.write( "SET_TARGET_PROPERTIES( {0:<31} PROPERTIES OUTPUT_NAME {0} )\n".format( lib_name_var ) )
        cmake_file.write( "SET_TARGET_PROPERTIES( {0:<31} PROPERTIES LINKER_LANGUAGE CXX )\n\n".format( lib_name_var ) )

    print "PROJECT:", projectName
    if is_test :
        test_name = sources[ 0 ]
        all_libs_var = "${ALL_LIBS}"
        gen_name = projectName.replace( ".", "" )

        cmake_file.write( "FIND_PACKAGE( CxxTest )\n" )
        cmake_file.write( "IF ( CXXTEST_FOUND )\n\n" )

        cmake_file.write( "  ENABLE_TESTING()\n\n" )

        for ln in lib_names :
            lib_name_var = "${" + lib_names[ ln ].upper() + "}"
            cmake_file.write( "  SET( ALL_LIBS {0}           {1} )\n".format( all_libs_var, lib_name_var ) )

        cmake_file.write( "\n" )
        cmake_file.write( "  CXXTEST_ADD_TEST( {0} {0}.cpp {1} )\n".format( gen_name, test_name ) )
        cmake_file.write( "  TARGET_LINK_LIBRARIES( {0} -Xlinker --start-group rt {1} -Xlinker --end-group )\n\n".format( gen_name, all_libs_var ) )

        cmake_file.write( "ENDIF ( CXXTEST_FOUND )\n\n" )
    elif projectName == 'runner.auto' :
        all_libs_var = "${ALL_LIBS}"
        gen_name = projectName.replace( ".", "" )

        cmake_file.write( "FIND_PACKAGE( CxxTest )\n" )
        cmake_file.write( "IF ( CXXTEST_FOUND )\n\n" )

        cmake_file.write( "  ENABLE_TESTING()\n\n" )

        for ln in lib_names :
            lib_name_var = "${" + lib_names[ ln ].upper() + "}"
            cmake_file.write( "  SET( ALL_LIBS {0}           {1} )\n".format( all_libs_var, lib_name_var ) )
        cmake_file.write( "\n" )
        for ln in libDeps :
            cmake_file.write( "SET( ALL_LIBS {0}           {1} )\n".format( all_libs_var, ln ) )

        cmake_file.write( "\n" )
        for test_name in sources :
            fname = test_name.filename.split("/")[-1]
            t_name = fname.replace( ".", "" )
            cmake_file.write( "  CXXTEST_ADD_TEST( {0} {0}.cpp {1} )\n".format( t_name, test_name ) )
            cmake_file.write( "  TARGET_LINK_LIBRARIES( {0} -Xlinker --start-group rt {1} -Xlinker --end-group )\n\n".format( t_name, all_libs_var ) )

        cmake_file.write( "ENDIF ( CXXTEST_FOUND )\n\n" )

    else :
        all_libs_var = "${ALL_LIBS}"
        gen_name = projectName.replace( ".", "" )

        cmake_file.write( "\n" )
        for ln in lib_names :
            lib_name_var = "${" + lib_names[ ln ].upper() + "}"
            cmake_file.write( "SET( ALL_LIBS {0}           {1} )\n".format( all_libs_var, lib_name_var ) )
        cmake_file.write( "\n" )
        for ln in libDeps :
            cmake_file.write( "SET( ALL_LIBS {0}           {1} )\n".format( all_libs_var, ln ) )

        app_name = maincomponent.name.upper() + "_APP"
        app_name_var = "${" + app_name + "}"
        cmake_file.write( "##################################################################\n" )
        cmake_file.write( "#\n" )
        cmake_file.write( "# {0}\n".format( maincomponent.name ) )
        cmake_file.write( "#\n" )
        cmake_file.write( "##################################################################\n" )
        cmake_file.write( "SET( {0:<49} {1} )\n".format( app_name, maincomponent.name ) )
        cmake_file.write( "ADD_EXECUTABLE( {0}\n".format( app_name_var ) )
        for src in sorted( maincomponent.sources[ maincomponent.name ] ):
            file_path = src.file.replace( "\\", "/" )
            if file_path.endswith( ".cpp" ) :
                cmake_file.write( "{0:>54} {1}\n".format( " ", file_path ) )
        cmake_file.write( "{0:>55})\n".format( " " ) )
        cmake_file.write( "SET_TARGET_PROPERTIES( {0:<31} PROPERTIES OUTPUT_NAME {0} )\n".format( app_name_var ) )
        cmake_file.write( "SET_TARGET_PROPERTIES( {0:<31} PROPERTIES LINKER_LANGUAGE CXX )\n".format( app_name_var ) )
        cmake_file.write( "TARGET_LINK_LIBRARIES( {0:<31} -Xlinker --start-group rt {1} -Xlinker --end-group )\n".format( app_name_var, all_libs_var ) )
        
        #cmake_file.write('add_executable(' + projectName + ' ${SOURCE_FILES})\n')

    cmake_file.close()
    return 1
    
def doBuilder( builder, options ):
    saveOptions = options.output

    if options.output and options.output.find( '$' ) == -1: 
        output = options.output
    else: 
        options.output = os.path.abspath( options.configuration )
    
    ( added, all ) = builder( options )
    if options.verblevel >= 2: 
        print "Builder total result: {0!s}".format( all )
        print "Builder modified component result: {0!s}".format( added )
    
    result = []
    if added:
        for filter, srcs in added.iteritems():
            result.extend( [BuildProject.FileInfo( source, [ filter ] ) for source in srcs] )
    options.output = saveOptions
    return result


class BuildersRunner:
    
    def __init__( self, options ):
        self.options = options
        self.cache = hash.HashStorage()
        
    def __call__( self, component ):
        builders = component.getBuilders( self.options.configuration )
        for builder in builders:
            added = doBuilder( builder, self.options )
            for info in added:
                if info.filter: 
                    key = "/".join( info.filter )
                else: 
                    key = utils.removeUnusedSeparator( component.name )
                component.AddSource( info.file, key )
                
    def __del__( self ):
        del self.cache


def runBuilders( components, options ):
    
    functor = BuildersRunner( options )
    componentAnalyzer.for_each( components, functor )
    
def createAnalyzer( options, testRun = False ):
    paths, locals = ComponentsSystem.getComponentsPaths( options )
    scope = [name for name in paths.split( ';' ) if name]
    analyzer = componentAnalyzer.Analyzer( globalScope = scope, verblevel = options.verblevel, options = options, testRun = testRun )
    #analyzer.addLocals( [name for name in locals.split( ';' ) if name] )
    return analyzer


def buildPlaneList( root, hierarchy ):
    result = set( [] )
    for node in hierarchy.get( root, set( [] ) ):
        result.add( node )
        result.update( buildPlaneList( node, hierarchy ) )
    return result

def detemineDublicates( root, hierarchy ):
    result = set( [] )
    nodes = hierarchy[root]
    for node1 in nodes:
        for node2 in nodes:
            if node1 != node2:
                children = buildPlaneList( node2, hierarchy )
                for child in children:
                    if child == node1:
                        warning = 'Warning: component {0} has duplicate component {1} in child component {2}'.format( root, node1, node2 )
                        result.add( warning )
    return result
    

def generateComponentsGraph( name, components, options ):

    outfilename = "{name}.graph".format( name = name )
    dublicatesfilename = "{name}.dublicates".format( name = name )

    hierarchy = {}
    duplicates = set( [] )
    for component in components:
        componentAnalyzer.findLoopedComponent( component )
        localHierarchy = componentAnalyzer.buildComponentsHierarchy( component )
        duplicates.update( detemineDublicates( component.name, localHierarchy ) )
        hierarchy.update( localHierarchy )


    componentnames = set([])
    res = 'digraph G {\n'
    for key, children in hierarchy.iteritems():
        res += '\t\"{0}\"\n'.format( key )
        componentnames.add( key )
        for child in children:
            res += '\t\"{0}\" -> \"{1}\";\n'.format( key, child )
            componentnames.add( child )
    res += '}\n'
    
    duplicates = list( duplicates )
    duplicates.sort()
    dublicatesstr = '\n'.join( duplicates )
    
    file = open( outfilename, 'w' )
    file.write( res )
    file.close()
    
    file = open( dublicatesfilename, 'w' )
    file.write( dublicatesstr )
    file.close()

    if options.verblevel >= 2:
        print dublicatesstr
        print 'Found ', len(componentnames), 'components: ', utils.instance2string( componentnames )
    
    if options.verblevel >= 1:
        Log.components = componentnames

    return ( outfilename, dublicatesfilename )
    

def generateCppRunner( project, sources, options, compilerKeys ):
    main = 'runner.cpp'
    
    addition = []
    if options.exceptions: addition = [ "--have-eh" ]
    if options.platform == 'win32' and not options.noSEH: addition.append( "--handle-seh" )
    if options.count > 1:
        addition.append('--count=%d' % options.count)
    
    #run script to generate test runner
    if options.verblevel >= 1: runner = 'VerbosePrinter'
    else: runner = 'ErrorPrinter'

    argsList = [ '--runner={0}'.format( runner ) ]
    argsList.append( '--output={0}'.format( main ) )
    argsList.extend( addition )
    for src in sources:
        argsList.append( str( src.filename ) )
        argsList.extend( src.arguments )
    files = ' '.join( map( lambda x: str( x ), sources ) )
    generator.generate( argsList, options.verblevel )

    for source in sources:
        project.addFile( source.filename, filter = [], ignore = True )
    project.addFile( main, filter = [], compilerKeys = compilerKeys )

    path = os.getcwd()
    if 'TestFrameworkPath' in os.environ:
        path = os.path.abspath( os.environ['TestFrameworkPath'] )
        
    for configurationName in BuildProject.Configuration.configurationNames:
        configuration = project.getConfiguration( configurationName )
        configuration.compilerKeys.add( "/I&quot;{0}&quot;".format( path ) );
        configuration.compilerKeys.add( "/I&quot;{0}/cxxtest&quot;".format( path ) );

    # paths, locals = getComponentsPaths( options )
    # scope = [name for name in paths.split( ';' ) if name]
    # for path in scope:
        # project.include.add( path )
    

def generateCsRunner( project, sources, options, compilerKeys ):
    main = 'runner.cs'

    for source in sources:
        project.addFile( source.filename, filter = [], ignore = True )

    if 'TestFrameworkPath' in os.environ:
        path = os.path.abspath( os.environ['TestFrameworkPath'] ) + '/NUnit/'
    else:
        path = ''

    shutil.copyfile( path + main, './' + main )
    project.addFile( 'runner.cs' )
    project.references.add( 'nunit.consolerunner' )


ProjectsFactory = {
    'win32' : { 
        'projectBuilder' : BuildProject.VCProject,        
        'runnerBuilder' : generateCppRunner
    },
    'linux' : { 
        'projectBuilder' : BuildProject.CMakeProject,        
        'runnerBuilder' : generateCppRunner
    },
    '.net' : {
        'projectBuilder' : BuildProject.CSProject,
        'runnerBuilder' : generateCsRunner
    }
}


def generateProjects( sources, root, components, options, maincomponent, removed = [] ):
    # detemine platform by the first item in the list

    if not sources:
        if not maincomponent: 
            raise Exception( "Can't find not inlined components" )
        root = maincomponent
        platform = root.getProjectType( options.configuration )
    else:
        platform = platforms.determinePlatform( sources[0].filename )

    # create projects from components
    isStartup = True
    if options.projectOnly:
        isStartup = False
    defaultProject = ProjectsFactory[platform]['projectBuilder']( root, output = options.output, startup = isStartup )
    projects = set( [defaultProject] )

    removed = set(removed)
    
    compilerKeys = {}
    #combinedComponent = None
    for component in components:
        if component != maincomponent:
            if component in removed:
                ( projName, projUUID ) = utils.parseProj( component.project )
                defaultProject.addExternalDependence( projUUID )
            else:
                if not component.inlined:
                    project = ProjectsFactory[component.getProjectType( options.configuration )]['projectBuilder']( component, output = options.output )
                    if project.projType != 'cs':
                        projects.add( project )
                    defaultProject.addDependence( project )
                else:
                    # if not combinedComponent: 
                        # combinedComponent = component
                    # else: 
                        # combinedComponent.InlinePlatformFeacture( component )
                        # combinedComponent.InlineComponent( component )
                    
                    defaultProject.addComponent( component )
                    
                    for configurationName, configuration in component.configurations.iteritems():
                        if configurationName in compilerKeys: compilerKeys[configurationName] |= configuration.compilerKeys
                        else: compilerKeys[configurationName] = configuration.compilerKeys

    # if combinedComponent:
        # defaultProject.addComponent( combinedComponent )
        # for configurationName, configuration in combinedComponent.configurations.iteritems():
            # # print configuration.compilerKeys
            # if configurationName in compilerKeys: compilerKeys[configurationName] |= configuration.compilerKeys
            # else: compilerKeys[configurationName] = configuration.compilerKeys


    if sources:
        # generate runner files 
        if 'runnerBuilder' in ProjectsFactory[platform] and ProjectsFactory[platform]['runnerBuilder']:            
            ProjectsFactory[platform]['runnerBuilder']( defaultProject, sources, options, compilerKeys )
        elif options.verblevel >= 1: 
            sys.stderr.write( "Can't generate runner for platform {0}\n".format( platform ) )
    
    return projects


def main( argv ):
    try:
        holder = InitializeEnvironment()
        result = parseCommandline( argv )
        sys.exit( result )
    except Exception as exc:
        sys.stderr.write("Error: {0}".format(exc))
        sys.stderr.write('\n')
        sys.stderr.write('-'*60)
        sys.stderr.write('\n')
        traceback.print_exc(file=sys.stderr)
        sys.stderr.write('-'*60)
        sys.exit( 1 )


if __name__ == '__main__':
    main( sys.argv[1:] )
