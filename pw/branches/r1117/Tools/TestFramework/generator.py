'''Usage: generate [OPTIONS] <input file(s)>
Generate test source file for CxxTest.
'''

import re
import sys
import os
import string
import optparse
from ComponentsSystem import utils
import fnmatch
import exceptions

# Global variables
suites = []
suite = None
inBlock = 0
launchedSuites = []
launchedTests = []

outputFileName = None
runner = None
root = None
part = None
noStaticInit = None
templateFileName = None
headers = []
handleSEH = False
runCount = 1

haveExceptionHandling = 0
haveStandardLibrary = 0
abortOnFail = 0
factor = 0
longlong = 0

wrotePreamble = 0
wroteWorld = 0
lastIncluded = ''


def generate( arguments, verbose ):
    '''Genetation of cxxtest code.'''
    if verbose >= 2: print '... started cxxtest generator, arguments:', arguments
    resetEvironment()
    files = parseArguments( arguments )
    scanInputFiles( files )
    writeOutput()


def resetEvironment():
    global suites, suite, inBlock
    global outputFileName, runner, root, part, noStaticInit, templateFileName, headers
    global  haveExceptionHandling, haveStandardLibrary, abortOnFail, factor, longlong, wrotePreamble, wroteWorld, lastIncluded
    
    suites = []
    suite = None
    inBlock = 0

    outputFileName = None
    runner = None
    root = None
    part = None
    noStaticInit = None
    templateFileName = None
    headers = []

    haveExceptionHandling = 0
    haveStandardLibrary = 0
    abortOnFail = 0
    factor = 0
    longlong = 0
    
    wrotePreamble = 0
    wroteWorld = 0
    lastIncluded = ''
    
def parseArguments( arguments ):
    '''Analyze arguments of call'''
    try:
        usage = '%prog [options] arg'
        parser = optparse.OptionParser( usage )

        parser.add_option( "-o", "--output", dest="outputFileName", help="UnitTest file NAME" )
        parser.add_option( "-r", "--runner", dest="runner", help="Create a main() function that runs CxxTest::CLASS" )
        parser.add_option( "--abort-on-fail", dest="abortOnFail", action="store_true", help="Abort tests on failed asserts (like xUnit)", default=False )
        parser.add_option( "--have-std", dest="std", action="store_true", help="Use standard library (even if not found in tests)" )
        parser.add_option( "--no-std", dest="std", action="store_false", help="Don\'t use standard library (even if found in tests)" )
        parser.add_option( "--have-eh", dest="exeption", action="store_true", help="Use exception handling (even if not found in tests)" )
        parser.add_option( "--no-eh", dest="exeption", action="store_false", help="Don\'t use exception handling (even if found in tests)" )
        parser.add_option( "--longlong", dest="longType", help="Use TYPE (default: long long) as long long" )
        parser.add_option( "--template", dest="templateFileName", help="Use TEMPLATE file to generate the test runner" )
        parser.add_option( "--include", dest="include", help="Include HEADER in test runner before other headers" )
        parser.add_option( "--root", dest="root", action="store_true", help="Write CxxTest globals" )
        parser.add_option( "--part", dest="part", action="store_true", help="Don\'t write CxxTest globals" )
        parser.add_option( "--no-static-init", dest="noStaticInit", action="store_false", help="Don\'t rely on static initialization" )
        parser.add_option( "--handle-seh", dest="handleSEH", action="store_true", help="Catch win32 SEH", default=False )
        parser.add_option( "--count", type="int", dest="count", help="How many times each test should be runned", default=1 )
        
        ( options, patterns ) = parser.parse_args( arguments )
                
    except optparse.OptionError, problem:
        raise Exception( problem )
    
    setOptions( options )
    return setFiles( patterns )

def setOptions( options ):
    '''Set options specified on command line'''
    global outputFileName, templateFileName, runner, haveStandardLibrary, factor, longlong
    global haveExceptionHandling, abortOnFail, headers, root, part, noStaticInit, handleSEH, runCount
    
    if options.outputFileName:
        outputFileName = options.outputFileName
    if options.runner:
        runner = options.runner
    if options.abortOnFail:
        abortOnFail = 1
    if options.std:
        haveStandardLibrary = options.std
    if options.exeption:
        haveExceptionHandling = options.exeption
    if options.longType:
        longlong = 'long long'
    if options.templateFileName:
        templateFileName = options.templateFileName
    if options.include:
        if not re.match( r'^["<].*[>"]$', options.include ):
            options.include = ( '"%s"' % options.include )
        headers.append( options.include )
    if options.root:
        root = 1
    if options.part:
        part = 1
    if options.noStaticInit:
        noStaticInit = 1
    runCount = options.count        
        
    handleSEH = options.handleSEH

    if noStaticInit and (root or part):
        abort( '--no-static-init cannot be used with --root/--part' )
        
def abort( problem ):
    '''Print error message and exit'''
    raise Exception( problem )

def setFiles( patterns ):
    '''Set input files specified on command line'''
    #scan for suit and test
    files = []
    arguments = []
    templates = [ '*.h', '*.cpp' ]
    for item in patterns:
        isFile = False
        for template in templates:
            if fnmatch.fnmatch( item, template ):
                files.append( os.path.normpath( item ) )
                isFile = True
        if not isFile: arguments.append( item )

    processArguments( arguments )
    return files

def processArguments( arguments ):
    for argument in arguments:
        index = argument.find( '.' )
        if index == -1:
            launchedSuites.append( argument )
        else:
            launchedSuites.append( argument[:index] )
            launchedTests.append( argument[index + 1:] )
    
    if len( launchedSuites ) == 0: launchedSuites.append( '*' )
    if len( launchedTests ) == 0: launchedTests.append( '*' )


def scanInputFiles(files):
    '''Scan all input files for test suites'''
    for file in files:
        scanInputFile( file )
    global suites
    if len( suites ) is 0 and not root:
        abort( 'No tests defined' )

def scanInputFile(fileName):
    '''Scan single input file for test suites'''
    file = open(fileName)
    lineNo = 0
    while 1:
        line = file.readline()
        if not line:
            break
        lineNo = lineNo + 1

        scanInputLine( fileName, lineNo, line )
    closeSuite()
    file.close()

def scanInputLine( fileName, lineNo, line ):
    '''Scan single input line for interesting stuff'''
    scanLineForExceptionHandling( line )
    scanLineForStandardLibrary( line )

    scanLineForSuiteStart( fileName, lineNo, line )

    global suite
    if suite:
        scanLineInsideSuite( suite, lineNo, line )

def scanLineInsideSuite( suite, lineNo, line ):
    '''Analyze line which is part of a suite'''
    global inBlock
    if lineBelongsToSuite( suite, lineNo, line ):
        scanLineForTest( suite, lineNo, line )
        scanLineForCreate( suite, lineNo, line )
        scanLineForDestroy( suite, lineNo, line )

def lineBelongsToSuite( suite, lineNo, line ):
    '''Returns whether current line is part of the current suite.
    This can be false when we are in a generated suite outside of CXXTEST_CODE() blocks
    If the suite is generated, adds the line to the list of lines'''
    if not suite['generated']:
        return 1

    global inBlock
    if not inBlock:
        inBlock = lineStartsBlock( line )
    if inBlock:
        inBlock = addLineToBlock( suite, lineNo, line )
    return inBlock


std_re = re.compile( r"\b(std\s*::|CXXTEST_STD|using\s+namespace\s+std\b|^\s*\#\s*include\s+<[a-z0-9]+>)" )
def scanLineForStandardLibrary( line ):
    '''Check if current line uses standard library'''
    global haveStandardLibrary
    if not haveStandardLibrary and std_re.search(line):
        haveStandardLibrary = 1

exception_re = re.compile( r"\b(throw|try|catch|TSM?_ASSERT_THROWS[A-Z_]*)\b" )
def scanLineForExceptionHandling( line ):
    '''Check if current line uses exception handling'''
    global haveExceptionHandling
    if not haveExceptionHandling and exception_re.search(line):
        haveExceptionHandling = 1

suitePatterns = [
    re.compile( r'\bclass\s+(\w+)\s*:\s*public\s+((::)?\s*CxxTest\s*::\s*)?TestSuite\b' ),
    re.compile( r'\bstruct\s+(\w+)\s*:\s*public\s+((::)?\s*CxxTest\s*::\s*)?TestSuite\b' ),
    re.compile( r'\bstruct\s+(\w+)\s*:\s*public\s+\s*?TestCase\b' ),
    re.compile( r'\bstruct\s+(\w+)\s*:\s*?TestCase\b' ),
]
generatedSuite_re = re.compile( r'\bCXXTEST_SUITE\s*\(\s*(\w*)\s*\)' )
def scanLineForSuiteStart( fileName, lineNo, line ):
    '''Check if current line starts a new test suite'''
    for pattern in suitePatterns:
        m = pattern.search( line )
        if m:
            startSuite( m.group(1), fileName, lineNo, 0 )
            break
    m = generatedSuite_re.search( line )
    if m:
        sys.stdout.write( "%s:%s: Warning: Inline test suites are deprecated.\n" % (fileName, lineNo) )
        startSuite( m.group(1), fileName, lineNo, 1 )

def startSuite( name, file, line, generated ):
    '''Start scanning a new suite'''
    global suite
    closeSuite()
    
    for suit in launchedSuites:
        if fnmatch.fnmatch( name, suit ):
            suite = {
                'name'         : name,
                'file'         : file,
                'cfile'        : cstr(file),
                'line'         : line,
                'generated'    : generated,
                'object'       : 'suite_%s' % name,
                'dobject'      : 'suiteDescription_%s' % name,
                'tlist'        : 'Tests_%s' % name,
                'tests'        : [],
                'lines'        : []
            }; break
            
def lineStartsBlock( line ):
    '''Check if current line starts a new CXXTEST_CODE() block'''
    return re.search( r'\bCXXTEST_CODE\s*\(', line ) is not None

test_re = re.compile( r'^([^/]|/[^/])*\bvoid\s+([Tt]est\w+)\s*\(\s*(void)?\s*\)' )
def scanLineForTest( suite, lineNo, line ):
    '''Check if current line starts a test'''
    m = test_re.search( line )
    if m:
        addTest( suite, m.group(2), lineNo )

def addTest( suite, name, line ):
    '''Add a test function to the current suite'''
    for item in launchedTests:
        if fnmatch.fnmatch( name, item ):
            test = {
                'name'   : name,
                'suite'  : suite,
                'class'  : 'TestDescription_%s_%s' % (suite['name'], name),
                'object' : 'testDescription_%s_%s' % (suite['name'], name),
                'line'   : line,
            }
            suite['tests'].append( test )
            break

def addLineToBlock( suite, lineNo, line ):
    '''Append the line to the current CXXTEST_CODE() block'''
    line = fixBlockLine( suite, lineNo, line )
    line = re.sub( r'^.*\{\{', '', line )
    
    e = re.search( r'\}\}', line )
    if e:
        line = line[:e.start()]
    suite['lines'].append( line )
    return e is None

def fixBlockLine( suite, lineNo, line):
    '''Change all [E]TS_ macros used in a line to _[E]TS_ macros with the correct file/line'''
    return re.sub( r'\b(E?TSM?_(ASSERT[A-Z_]*|FAIL))\s*\(',
                   r'_\1(%s,%s,' % (suite['cfile'], lineNo),
                   line, 0 )

create_re = re.compile( r'\bstatic\s+\w+\s*\*\s*createSuite\s*\(\s*(void)?\s*\)' )
def scanLineForCreate( suite, lineNo, line ):
    '''Check if current line defines a createSuite() function'''
    if create_re.search( line ):
        addSuiteCreateDestroy( suite, 'create', lineNo )

destroy_re = re.compile( r'\bstatic\s+void\s+destroySuite\s*\(\s*\w+\s*\*\s*\w*\s*\)' )
def scanLineForDestroy( suite, lineNo, line ):
    '''Check if current line defines a destroySuite() function'''
    if destroy_re.search( line ):
        addSuiteCreateDestroy( suite, 'destroy', lineNo )

def cstr( str ):
    '''Convert a string to its C representation'''
    return '"' + string.replace( str, '\\', '\\\\' ) + '"'


def addSuiteCreateDestroy( suite, which, line ):
    '''Add createSuite()/destroySuite() to current suite'''
    if suite.has_key(which):
        abort( '%s:%s: %sSuite() already declared' % ( suite['file'], str(line), which ) )
    suite[which] = line

def closeSuite():
    '''Close current suite and add it to the list if valid'''
    global suite
    if suite is not None:
        if len(suite['tests']) is not 0:
            verifySuite(suite)
            rememberSuite(suite)
        suite = None

def verifySuite(suite):
    '''Verify current suite is legal'''
    if suite.has_key('create') and not suite.has_key('destroy'):
        abort( '%s:%s: Suite %s has createSuite() but no destroySuite()' %
               (suite['file'], suite['create'], suite['name']) )
    if suite.has_key('destroy') and not suite.has_key('create'):
        abort( '%s:%s: Suite %s has destroySuite() but no createSuite()' %
               (suite['file'], suite['destroy'], suite['name']) )

def rememberSuite(suite):
    '''Add current suite to list'''
    global suites
    suites.append( suite )

def writeOutput():
    '''Create output file'''
    if templateFileName:
        writeTemplateOutput()
    else:
        writeSimpleOutput()

def writeSimpleOutput():
    '''Create output not based on template'''
    output = startOutputFile()
    writePreamble( output )
    writeWorld( output )
    writeMain( output )
    output.close()

include_re = re.compile( r"\s*\#\s*include\s+<cxxtest/" )
preamble_re = re.compile( r"^\s*<CxxTest\s+preamble>\s*$" )
world_re = re.compile( r"^\s*<CxxTest\s+world>\s*$" )
def writeTemplateOutput():
    '''Create output based on template file'''
    template = open(templateFileName)
    output = startOutputFile()
    while 1:
        line = template.readline()
        if not line:
            break;
        if include_re.search( line ):
            writePreamble( output )
            output.write( line )
        elif preamble_re.search( line ):
            writePreamble( output )
        elif world_re.search( line ):
            writeWorld( output )
        else:
            output.write( line )
    template.close()
    output.close()

def startOutputFile():
    '''Create output file and write header'''
    if outputFileName is not None:
        output = open( outputFileName, 'w' )
    else:
        output = sys.stdout
    output.write( "/* Generated file, do not edit */\n\n" )
    return output

def writePreamble( output ):
    '''Write the CxxTest header (#includes and #defines)'''
    global wrotePreamble, headers, longlong
    if wrotePreamble: return
    lines = [
        "#ifndef CXXTEST_RUNNING",
        "#define CXXTEST_RUNNING", 
        "#endif",
        "",
    ]
    if haveStandardLibrary:
        lines.append( "#define _CXXTEST_HAVE_STD" )
    if haveExceptionHandling:
        lines.append( "#define _CXXTEST_HAVE_EH" )
    if abortOnFail:
        lines.append( "#define _CXXTEST_ABORT_TEST_ON_FAIL" )
    if longlong:
        lines.append( "#define _CXXTEST_LONGLONG %s" % longlong )
    if factor:
        lines.append( "#define _CXXTEST_FACTOR" )
    for header in headers:
        lines.append( "#include %s" % header )
    for suite in suites:
        baseDir = os.path.dirname( suite['file'] )
        lines.append( '#include "' + baseDir + '\stdafx.h"' ) #+ suite['file'] + '"' )
        break
    lines.extend([        
        "#ifndef WIN32_LEAN_AND_MEAN",
        "#define WIN32_LEAN_AND_MEAN",
        "#endif",
        "#include <windows.h>",
        "#include <tlhelp32.h>",
        "#include <vector>",
        "#include <algorithm>",
        "#include <string>",
        "#include <cxxtest/TestListener.h>",
        "#include <cxxtest/TestTracker.h>",
        "#include <cxxtest/TestRunner.h>",
        "#include <cxxtest/RealDescriptions.h>",
        "#define CXX_REGISTER_TEST_SUITE( suite_class ) void dummy##suite_class()",
        "#define CXX_REGISTER_TEST_FUNCTION( func_name ) ",
        "#define PW_UNIT_TEST",
    ])        
    if runner:
        lines.append( "#include <cxxtest/%s.h>" % runner )
    if handleSEH:
        lines.append( "#include <cxxtest/Win32SEH.h>" )
    lines.append('')        
    lines.append( "static const int gMaxTestRunTimeLength = 3000000;" )
    lines.append('')        
        
    output.write('\n'.join(lines))
    wrotePreamble = 1

def writeMain( output ):
    '''Write the main() function for the test runner'''
    if runner:
        if handleSEH:
            output.write( '\nwin32::SEHHandler sehHandler;\n\n' )

        output.write( 'int main(int argc, char* argv[])\n{\n' )
        if noStaticInit:
            output.write( '  CxxTest::initialize();\n' )
        output.write( "  std::vector<std::string> params;\n" )
        output.write( "  for ( int i = 1; i < argc; i++ )\n  {\n    params.push_back( argv[i] );\n  }\n" )

        output.write( '  return CxxTest::%s().run( params, %d );\n' % (runner, runCount) )
        output.write( '}\n' )

def writeWorld( output ):
    '''Write the world definitions'''
    global wroteWorld, part
    if wroteWorld: return
    writePreamble( output )
    writeSuites( output )
    if root or not part:
        writeRoot( output )
    if noStaticInit:
        writeInitialize( output )
    wroteWorld = 1

def writeSuites(output):
    '''Write all TestDescriptions and SuiteDescriptions'''
    for suite in suites:
        writeInclude( output, suite['file'] )
        if isGenerated(suite):
            generateSuite( output, suite )
        if isDynamic(suite):
            writeSuitePointer( output, suite )
        else:
            writeSuiteObject( output, suite )
        writeTestList( output, suite )
        writeSuiteDescription( output, suite )
        writeTestDescriptions( output, suite )

def isGenerated(suite):
    '''Checks whether a suite class should be created'''
    return suite['generated']

def isDynamic(suite):
    '''Checks whether a suite is dynamic'''
    return suite.has_key('create')

def writeInclude(output, file):
    '''Add #include "file" statement'''
    global lastIncluded
    if file == lastIncluded: return
    output.writelines( [ '#include "', file, '"\n\n' ] )
    lastIncluded = file

def generateSuite( output, suite ):
    '''Write a suite declared with CXXTEST_SUITE()'''
    output.write( 'class %s : public CxxTest::TestSuite {\n' % suite['name'] )
    output.write( 'public:\n' )
    for line in suite['lines']:
        output.write(line)
    output.write( '};\n\n' )

def writeSuitePointer( output, suite ):
    '''Create static suite pointer object for dynamic suites'''
    if noStaticInit:
        output.write( 'static %s *%s;\n\n' % (suite['name'], suite['object']) )
    else:
        output.write( 'static %s *%s = 0;\n\n' % (suite['name'], suite['object']) )

def writeSuiteObject( output, suite ):
    '''Create static suite object for non-dynamic suites'''
    output.writelines( [ "static ", suite['name'], " ", suite['object'], ";\n\n" ] )

def writeTestList( output, suite ):
    '''Write the head of the test linked list for a suite'''
    if noStaticInit:
        output.write( 'static CxxTest::List %s;\n' % suite['tlist'] )
    else:
        output.write( 'static CxxTest::List %s = { 0, 0 };\n' % suite['tlist'] )

def writeTestDescriptions( output, suite ):
    '''Write all test descriptions for a suite'''
    for test in suite['tests']:
        writeTestDescription( output, suite, test )

def writeTestDescription( output, suite, test ):
    '''Write test description object'''
    output.write( 'DWORD WINAPI %s_Func( LPVOID lpParam )\n' % test['class'] )
    output.write( '{\n' )
    output.write( '\t%s *suiteTest = (%s*)lpParam;\n' % (suite['name'], suite['name']) )
    output.write( '\tsuiteTest->%s();\n' % test['name'] )
    output.write( '\treturn 0;\n' )
    output.write( '}\n\n' )


    output.write( 'static class %s : public CxxTest::RealTestDescription {\n' % test['class'] )
    output.write( 'public:\n' )
    if not noStaticInit:
        output.write( '\t%s() : CxxTest::RealTestDescription( %s, %s, %s, "%s" ) {}\n' %
                      (test['class'], suite['tlist'], suite['dobject'], test['line'], test['name']) )
    output.write( '\tvoid runTest()' )
    output.write( '\t{\n' )

    output.write( '\t\tDWORD id;\n' )
    output.write( '\t\tHANDLE hThread = CreateThread(\n' )
    output.write( '\t\t\tNULL, 0,\n' )
    output.write( '\t\t\t%s_Func,\n' % test['class'] )
    output.write( '\t\t\t&%s, 0, &id);\n\n' % suite['object'] )

    output.write( '\t\tDWORD result = WaitForSingleObject( hThread, CxxTest::isDebuggerPresent() ? INFINITE : gMaxTestRunTimeLength );\n' )
    
    output.write( '\t\tif ( result == WAIT_OBJECT_0 )\n' )
    output.write( '\t\t{\n' )
    output.write( '\t\t\treturn;\n' )
    output.write( '\t\t}\n' )
    output.write( '\t\telse\n' )
    output.write( '\t\t{\n' )
    output.write( '\t\t\tTS_FAIL("TimeOut: %s.%s");\n' % (suite['name'], test['name']) )
    output.write( '\t\t}\n' )

    output.write( '\t}\n' )
     
    output.write( '} %s;\n\n' % test['object'] )

def runBody( suite, test ):
    '''Body of TestDescription::run()'''
    if isDynamic(suite): return dynamicRun( suite, test )
    else: return staticRun( suite, test )

def dynamicRun( suite, test ):
    '''Body of TestDescription::run() for test in a dynamic suite'''
    return 'if ( ' + suite['object'] + ' ) ' + suite['object'] + '->' + test['name'] + '();'
    
def staticRun( suite, test ):
    '''Body of TestDescription::run() for test in a non-dynamic suite'''
    return suite['object'] + '.' + test['name'] + '();'
    
def writeSuiteDescription( output, suite ):
    '''Write SuiteDescription object'''
    if isDynamic( suite ):
        writeDynamicDescription( output, suite )
    else:
        writeStaticDescription( output, suite )

def writeDynamicDescription( output, suite ):
    '''Write SuiteDescription for a dynamic suite'''
    output.write( 'CxxTest::DynamicSuiteDescription<%s> %s' % (suite['name'], suite['dobject']) )
    if not noStaticInit:
        output.write( '( %s, %s, "%s", %s, %s, %s, %s )' %
                      (suite['cfile'], suite['line'], suite['name'], suite['tlist'],
                       suite['object'], suite['create'], suite['destroy']) )
    output.write( ';\n\n' )

def writeStaticDescription( output, suite ):
    '''Write SuiteDescription for a static suite'''
    output.write( 'CxxTest::StaticSuiteDescription %s' % suite['dobject'] )
    if not noStaticInit:
        output.write( '( %s, %s, "%s", %s, %s )' %
                      (suite['cfile'], suite['line'], suite['name'], suite['object'], suite['tlist']) )
    output.write( ';\n\n' )

def writeRoot(output):
    '''Write static members of CxxTest classes'''
    output.write( '#include <cxxtest/Root.cpp>\n' )

def writeInitialize(output):
    '''Write CxxTest::initialize(), which replaces static initialization'''
    output.write( 'namespace CxxTest {\n' )
    output.write( ' void initialize()\n' )
    output.write( ' {\n' )
    for suite in suites:
        output.write( '  %s.initialize();\n' % suite['tlist'] )
        if isDynamic(suite):
            output.write( '  %s = 0;\n' % suite['object'] )
            output.write( '  %s.initialize( %s, %s, "%s", %s, %s, %s, %s );\n' %
                          (suite['dobject'], suite['cfile'], suite['line'], suite['name'],
                           suite['tlist'], suite['object'], suite['create'], suite['destroy']) )
        else:
            output.write( '  %s.initialize( %s, %s, "%s", %s, %s );\n' %
                          (suite['dobject'], suite['cfile'], suite['line'], suite['name'],
                           suite['object'], suite['tlist']) )

        for test in suite['tests']:
            output.write( '  %s.initialize( %s, %s, %s, "%s" );\n' %
                          (test['object'], suite['tlist'], suite['dobject'], test['line'], test['name']) )

    output.write( ' }\n' )
    output.write( '}\n' )
    
if __name__ == '__main__':
    # testsFile = 'test2.cpp'
    # runner = 'ErrorPrinter'
    # output = 'test2.cpp.auto.cpp' 
    # arguments = '--runner=%s --output=%s %s' % ( runner, output, testsFile )  
    # generate( arguments, True )
    pass