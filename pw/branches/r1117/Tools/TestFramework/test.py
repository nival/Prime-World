import sys
import os
import tempfile
import run
import unittest
import fnmatch
import sln
import uuid
import shutil
import componentAnalyzer
from ComponentsSystem import utils
import resultgen
import BuildProject

workdir = ''

def buildTestAssert( file, textout, texterr ):
    res = resultgen.generateTestResult( file, textout, texterr, 0 )
    if textout.find( 'fatal error' ) != -1 or textout.find( ': error' ) != -1:
        res = resultgen.generateBadBuildResult( file, textout, 0 )
    for r in res:
        if r.errorstr:
            assert 0, r.errorstr + '\nbuild failed'


def runDiffer( path1, path2 ):
    try:
        os.system( 'p4diff.exe %s %s' % ( path1, path2 ) )
    except:
        print "Can't find p4diff..."


def testCase( params, templatefile ):
    if os.path.isfile( 'unittest.cfg' ):
        os.remove( 'unittest.cfg' )
    mypath = os.path.abspath( workdir+'unittests/testCaseSelect' )
    mypath += '/'
    listfiles = os.listdir('.')
    listfiles_set = set( listfiles )
    textout, texterr = utils.runSubprocess( ['run.cmd', mypath+params ] )
    buildTestAssert( params[0], textout, texterr )
    
    dir = utils.changeScope()
    logPath = 'log.log' 
    logfile = open( logPath )
    logstr = logfile.read()
    logfile.close()
    del dir

    templatefile = open( mypath + templatefile )
    templatestr = templatefile.read()
    templatefile.close()

    for file in os.listdir('.'):
        if not file in listfiles_set:
            if os.path.isfile( file ):
                os.remove( file )
            if os.path.isdir( file ):
                shutil.rmtree( file )
    if os.path.isfile( 'log.log' ):
        os.remove( 'log.log' )

    if logstr != templatestr:
        #runDiffer( logPath, templatefile )
        assert 0, 'differ %s and %s' % ( logstr, templatestr )


def compareFiles( filename1, filename2 ):
    file1 = open( filename1 )
    file2 = open( filename2 )
    filestr1 = file1.read()
    filestr2 = file2.read()
    file1.close()
    file2.close()
    return filestr1 == filestr2


def compareAllFiles( dirname ):
    listfiles = os.listdir( dirname )
    for file in listfiles:
        if not fnmatch.fnmatch(file, '.svn') and not fnmatch.fnmatch(file, 'params'):
            res = compareFiles( './' + file, dirname + file )
            if not res:
                return False, './' + file, dirname + file
    return True, '', ''


def getTestName( testname ):
    mypath = os.path.abspath( testname )
    mypath = os.path.basename( mypath )
    return mypath


class pseudoOptions:
    def __init__( self ):
        self.verblevel = 0
        self.exceptions = False
        self.noSEH = True
        self.compiler = 'msvc9'
        self.devenvversion = "9.0.21022"

def runTest( testname, filename = None ):
    listfiles = os.listdir('.')
    run.setVars()
    paramsfile = open( testname + 'params' )
    params = paramsfile.read()
    paramsfile.close()
    exec(params)
    options = pseudoOptions()
    if filename:
        sln.createSLN( 'xxx', options, projects, filename )
    else:
        sln.createSLN( 'xxx', options, projects, )
    result, file1, file2 = compareAllFiles( testname )
    assert result, 'differ %s and %s' % ( file1, file2 )
    listfiles_set = set( listfiles )
    for file in os.listdir('.'):
        if not file in listfiles_set:
            os.remove( file )


class Test(unittest.TestCase):
    
    def setUp( self ):
        #os.system( 'run.cmd --cleanup' )
        pass

    def tearDown( self ):
        #os.system( 'run.cmd --cleanup' )
        pass


    def testDirHierarchy(self):
        self.dir1 = tempfile.mkdtemp()
        self.dir2 = tempfile.mkdtemp( dir = self.dir1 )
        self.dir3 = tempfile.mkdtemp( dir = self.dir2 )
        self.filename1 = self.dir1 + '/' + run.configfilename
        self.filename2 = self.dir3 + '/' + run.configfilename
        
        file = open( self.filename1, 'w' )
        file.write( '' )
        file.close()
        file = open( self.filename2, 'w' )
        file.write( '' )
        file.close()

        filelist = run.getConfigFilesList( self.dir3 )

        assert len( filelist ) == 2, filelist
        
        if os.path.normcase(os.path.normpath(self.filename1)) != os.path.normcase(os.path.normpath(filelist[0])):
            assert 0, 'differ %s and %s' % ( self.filename1, filelist[0] )
        
        if os.path.normcase(os.path.normpath(self.filename2)) != os.path.normcase(os.path.normpath(filelist[1])):
            assert 0, 'differ %s and %s' % ( self.filename2, filelist[1] )


    def testSet(self):
        env = run.Envo()

        env.Set('lofik', 'd:/te/test/test1;d:/te;')
        self.assertEquals('d:/te/test/test1;d:/te;', env['lofik'])

        env.Set('lofik', 'blabla')
        self.assertEquals('blabla', env['lofik'])


    def testAppend(self):
        env = run.Envo()

        env.Append('lofik', 'd:/lof')
        self.assertEquals('d:/lof;', env['lofik'])

        env.Set('lofik', 'd:/te/test/test1;d:/te;')
        env.Append('lofik', 'd:/lof')
        self.assertEquals('d:/te/test/test1;d:/te;d:/lof;', env['lofik'])

        env.Append('lofik', 'd:/gum')
        self.assertEquals('d:/te/test/test1;d:/te;d:/lof;d:/gum;', env['lofik'])


    def testPrepend( self ):
        env = run.Envo()

        env.Set('lofik', 'd:/te/test/test1;d:/te;')
        env.Prepend('lofik', 'd:/lof')
        self.assertEquals('d:/lof;d:/te/test/test1;d:/te;', env['lofik'])

        env.Prepend('lofik', 'd:/gum')
        self.assertEquals('d:/gum;d:/lof;d:/te/test/test1;d:/te;', env['lofik'])


    def testRemove( self ):
        env = run.Envo()

        env.Set('lofik', 'd:/te/test/test1;d:/te;')
        env.Remove('lofik', 'd:/t')
        self.assertEquals('d:/te/test/test1;d:/te;', env['lofik'])

        env.Remove('lofik', 'test1')
        self.assertEquals('d:/te/test/test1;d:/te;', env['lofik'])

        env.Remove('lofik', 'd:/tef')
        self.assertEquals('d:/te/test/test1;d:/te;', env['lofik'])

        env.Remove('lofik', 'd:/te/tes')
        self.assertEquals('d:/te/test/test1;d:/te;', env['lofik'])

        env.Remove('lofik', 'd:/te')
        self.assertEquals('d:/te/test/test1;', env['lofik'])

        env.Append('lofik', 'd:/lof')
        self.assertEquals('d:/te/test/test1;d:/lof;', env['lofik'])
        env.Remove('lofik', 'd:/lo')
        self.assertEquals('d:/te/test/test1;d:/lof;', env['lofik'])

        env.Prepend('lofik', 'd:/gum')
        self.assertEquals('d:/gum;d:/te/test/test1;d:/lof;', env['lofik'])
        env.Remove('lofik', 'd:/gu')
        self.assertEquals('d:/gum;d:/te/test/test1;d:/lof;', env['lofik'])

        env.Remove('lofik', 'd:/lof')
        self.assertEquals('d:/gum;d:/te/test/test1;', env['lofik'])
        env.Append('lofik', 'd:/lof')
        self.assertEquals('d:/gum;d:/te/test/test1;d:/lof;', env['lofik'])

        env.Remove('lofik', 'd:/gum')
        self.assertEquals('d:/te/test/test1;d:/lof;', env['lofik'])

        env.Prepend('lofik', 'd:/gum')
        self.assertEquals('d:/gum;d:/te/test/test1;d:/lof;', env['lofik'])
        env.Remove('lofik', 'd:/te/test/test1')
        self.assertEquals('d:/gum;d:/lof;', env['lofik'])

        env.Remove('lofik', '')
        self.assertEquals('d:/gum;d:/lof;', env['lofik'])

        env.Remove('lofik', 'd:/gum;d:/lof')
        self.assertEquals('', env['lofik'])


    def testVC( self ):
        pass
        #runTest( workdir+'unittests/testCreateSln/' )
        #testMD5Hash2

        #runTest( workdir+'unittests/testCreateVCProj/' )
        #testInlined

        #runTest( workdir+'unittests/testAddFile/' )
        #testComponentSources

        #runTest( workdir+'unittests/testAddFilter/' )
        #runTest( workdir+'unittests/testBadFilter/' )
        #runTest( workdir+'unittests/testBadFilter2/' )
        #testBadFilter3

        #runTest( workdir+'unittests/testVCProjDepend/' )
        #testComponentHash

        #runTest( workdir+'unittests/testPreBuildStep/', 'test.cpp' )
        #runTest( workdir+'unittests/testPreBuildNames/', 'test.cpp' )
        #testDllComponent


    def testCS( self ):
        runTest( workdir+'unittests/testCreateSlnCs/' )
        #runTest( workdir+'unittests/testCreateCSProj/' )
        #runTest( workdir+'unittests/testAddCSFile/' )
        #runTest( workdir+'unittests/testAssembly/' )
        #runTest( workdir+'unittests/testCSProjDepend/' )


    def testCaseSelect( self ):
        testCase( 'test.cpp', 'log1.txt' )
        testCase( 'test2.cpp', 'log2.txt' )
        testCase( 'test.cpp TestSuite1', 'log3.txt' )
        testCase( 'test.cpp TestSuite2', 'log4.txt' )
        testCase( 'test.cpp TestSuite1.testNumber3', 'log5.txt' )
        testCase( 'test.cpp TestSuite2.testNumber20', 'log6.txt' )
        testCase( 'test.cpp TestSuite1.testNumber3 TestSuite2.testNumber20', 'log7.txt' )


    def testMD5Hash( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testMD5Hash' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp', mypath+'test2.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        dir = utils.changeScope()
        templatefile = open( 'unittest.cfg' )
        templatestr = templatefile.read()
        templatefile.close()
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        assert templatestr.find('83b025a9bcc51864e68f35130b6a29ac') != -1, 'Bad md5 hash'
        assert templatestr.find('46d45b8b28094144db8b59e34fc25250') != -1, 'Bad md5 hash'


    def testMD5Hash2( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testMD5Hash2' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )

        testFileName = 'md52.test.cpp'
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+testFileName] )
        buildTestAssert( testFileName, textout, texterr )

        dir = utils.changeScope()
        solutionName = 'md52.test.sln'
        os.remove( solutionName )
        del dir

        utils.runSubprocess( ['run.cmd', mypath+testFileName] )
        isSlnError = True
        dir = utils.changeScope()
        if os.path.isfile( solutionName ):
            isSlnError = False
        os.remove( 'unittest.cfg' )
        del dir

        utils.runSubprocess( ['run.cmd', mypath+testFileName] )
        dir = utils.changeScope()
        statinfo = os.stat( solutionName )
        oldtime = statinfo.st_mtime
        del dir

        utils.runSubprocess( ['run.cmd', mypath+testFileName] )
        dir = utils.changeScope()
        statinfo2 = os.stat( solutionName )
        oldtime2 = statinfo2.st_mtime
        del dir

        srcfile = open( mypath+testFileName, 'r' )
        srcstr = srcfile.read()
        srcfile.close()
        srcstr += '\n'

        srcfile = open( mypath+testFileName, 'w' )
        srcfile.write( srcstr )
        srcfile.close()

        utils.runSubprocess( ['run.cmd', mypath+testFileName] )
        dir = utils.changeScope()
        statinfo3 = os.stat( solutionName )
        oldtime3 = statinfo3.st_mtime
        del dir

        srcfile = open( mypath+testFileName, 'r' )
        srcstr = srcfile.read()
        srcfile.close()
        srcstr = srcstr[:-1]

        srcfile = open( mypath+testFileName, 'w' )
        srcfile.write( srcstr )
        srcfile.close()
        
        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                if os.path.isdir( file ):
                    shutil.rmtree( file )

        assert oldtime == oldtime2, 'Time is differ!'

        assert oldtime == oldtime3, 'Time is differ!'

        assert not isSlnError, 'Error while solution creation!'
        
    def testAnalyzer( self ):
        analyzer = componentAnalyzer.Analyzer()

        assert analyzer.SearchComponentExpression( '//!Component("System/Math") : ddd' ) == 'System/Math'
        assert analyzer.SearchComponentExpression( '//!Component("Sys:tem\\Te|mp_-\\Math")ddd' ) == 'Sys:tem\\Te|mp_-\\Math'
        assert analyzer.SearchComponentExpression( '//dfd dd  //!Component("Math")' ) == 'Math'
        assert analyzer.SearchComponentExpression( '//!Component( '' )' ) == None
        assert analyzer.SearchComponentExpression( '//!Component( "Test" )' ) == 'Test'

    def testAnalyzerWithPackageName( self ):
        analyzer = componentAnalyzer.Analyzer()

        assert analyzer.SearchComponentExpression( '//!Package("System/Math") : ddd' ) == 'System/Math'
        assert analyzer.SearchComponentExpression( '//!Package("Sys:tem\\Te|mp_-\\Math")ddd' ) == 'Sys:tem\\Te|mp_-\\Math'
        assert analyzer.SearchComponentExpression( '//dfd dd  //!Package("Math")' ) == 'Math'
        assert analyzer.SearchComponentExpression( '//!Package( '' )' ) == None
        assert analyzer.SearchComponentExpression( '//!Package( "Test" )' ) == 'Test'

    def testRedundantPath( self ):

        assert utils.getRedundantPath( 'C:\\test\\1.txt', 'c:' ) == 'test/1.txt'
        assert utils.getRedundantPath( 'C:\\test\\1.txt', 'c:\\' ) == 'test/1.txt'
        assert utils.getRedundantPath( 'C:\\test/1.txt', 'c:/' ) == 'test/1.txt'
        assert utils.getRedundantPath( 'C:\\test\\1.txt', 'c:/test' ) == '1.txt'
        assert utils.getRedundantPath( 'C:\\test/1.txt', 'c:\\test/' ) == '1.txt'
        assert utils.getRedundantPath( 'C:\\test\\1.txt', 'c:/test/1.txt' ) == ''
        assert utils.getRedundantPath( 'C:\\test/', '' ) == 'c:/test/'
        assert utils.getRedundantPath( 'C:\\test\\', 'c:' ) == 'test/'
        assert utils.getRedundantPath( 'C:\\', 'c:/test/' ) == 'c:/'
        assert utils.getRedundantPath( 'C:\\test/1.txt', 'c:/test/2.txt' ) == 'c:/test/1.txt'


    def testRelPath( self ):

        assert utils.getRelPath( 'C:\\test', 'C:\\test\\1.txt' ) == '1.txt'
        assert utils.getRelPath( 'C:\\test2', 'C:\\test\\1.txt' ) == '../test/1.txt'
        assert utils.getRelPath( 'C:\\test\\test2\\test3', 'C:\\test\\1.txt' ) == '../../1.txt'
        assert utils.getRelPath( 'C:\\test2\\test2\\test3', 'C:\\test\\1.txt' ) == '../../../test/1.txt'
        assert utils.getRelPath( 'C:\\test2\\test\\test3', 'C:\\test\\1.txt' ) == '../../../test/1.txt'


    def testPathRegression( self ):

        assert utils.shortName( r'dsfs/fdsfdsf\\sdfs/dfs/sdfds.cccc' ) == 'sdfds.cccc'
        assert utils.shortName( r'dsfs/fdsfdsf\\sdfs/dfs/' ) == ''
        assert utils.shortName( 'cccc' ) == 'cccc'
        assert utils.shortName( r'cccc\sdfdsf' ) == 'sdfdsf'
        assert utils.shortName( r'' ) == ''
        
        assert utils.pathName( r'dsfs/fds\\fdsf\sdfs/dfs/sdfds.cccc' ) == r'dsfs/fds\\fdsf\sdfs/dfs/'
        assert utils.pathName( r'dsfs/fdsfdsf\\sdfs/dfs/' ) == r'dsfs/fdsfdsf\\sdfs/dfs/'
        assert utils.pathName( 'cccc' ) == ''
        assert utils.pathName( r'cccc\sdfdsf' ) == 'cccc\\'
        assert utils.pathName( r'' ) == ''


    def testBuilders( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testBuilders' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath + 'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isInstallBuilder = False
        isCopyBuilder = False

        dir = utils.changeScope()
        if os.path.isfile( 'fmod.dll' ):
            isCopyBuilder = True
        dir2 = utils.changeScope( 'Debug' )
        if os.path.isfile( 'bld.file' ):
            isInstallBuilder = True
        del dir2
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        assert isInstallBuilder
        assert isCopyBuilder


    def testDllComponent( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testDllComponent' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isLibFile = False
        isDefFile = False

        dir = utils.changeScope()
        if os.path.isfile( 'Debug/tdc.lib' ):
            isLibFile = True
        if os.path.isfile( 'Debug/tdc/tdc.def' ):
            isDefFile = True
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        assert isLibFile
        assert isDefFile


    def testComponentHash( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testComponentHash' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        config = '.auto/unittest.cfg'
        file1 = open( config )
        str1 = file1.read()
        file1.close()
        
        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        componentfile = open( mypath+'Dependence.component' )
        compstr = componentfile.read()
        componentfile.close()

        compstr = utils.replaceSubStr( compstr, 'main.cs', 'main2.cs' )

        componentfile = open( mypath+'Dependence.component', 'w' )
        componentfile.write( compstr )
        componentfile.close()

        utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )

        file2 = open( config )
        str2 = file2.read()
        file2.close()

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        componentfile = open( mypath+'Dependence.component' )
        compstr = componentfile.read()
        componentfile.close()

        compstr = utils.replaceSubStr( compstr, 'main2.cs', 'main.cs' )

        componentfile = open( mypath+'Dependence.component', 'w' )
        componentfile.write( compstr )
        componentfile.close()

        assert str1 != str2, 'Hash is same! {0}'.format( str1 )


    def testComponentSources( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testComponentSources' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )

        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        dir = utils.changeScope()
        file = open( 'test.vcproj' )
        teststr = file.read()
        file.close()
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        assert teststr.find( 'fileo1.cpp' ) != -1, 'vcproj is bad'
        assert teststr.find( 'fileo2.cpp' ) != -1, 'vcproj is bad'


    def testUniqProjects( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testUniqProjects' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        dir = utils.changeScope()
        file = open( 'test.sln' )
        teststr = file.read()
        file.close()
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        strtofind = 'Uniq.vcproj'

        idx1 = teststr.find( strtofind )
        assert idx1 != -1, 'vcproj is bad'
        assert teststr.find( strtofind, idx1 + len( strtofind ) ) == -1, 'vcproj is bad'


    def testCSReference( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testCSReference' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        dir = utils.changeScope()
        file = open( 'test1.csproj' )
        teststr = file.read()
        file.close()
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        strtofind = 'Reference Include=\"system.xml'

        idx1 = teststr.find( strtofind )
        if idx1 == -1:
            assert 0, 'csproj is bad'


    def testAddComponent( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testAddComponent' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        dir = utils.changeScope()
        file = open( 'DllComp.vcproj' )
        teststr = file.read()
        file.close()
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        strtofind = 'DllComp.component'

        idx1 = teststr.find( strtofind )
        if idx1 == -1:
            assert 0, 'Add component file to vcproj error'


    def testAddComponentCs( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testAddComponentCs' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isCsExeError = True

        dir = utils.changeScope()
        if os.path.isfile( r'Debug\DlComp.exe' ):
            isCsExeError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        if isCsExeError:
            assert 0, 'Add component file to csproj error'


    def testComponentBuild( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testComponentBuild' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'Second.component'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isCsExeError = True

        dir = utils.changeScope()
        if os.path.isfile( 'Second.csproj' ):
            isCsExeError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        if isCsExeError:
            assert 0, 'Build component error'


    def testApplicationBuild( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testApplication' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'Appl.application'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isExeError = True

        dir = utils.changeScope()
        if os.path.isfile( 'Appl.vcproj' ):
            isExeError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        if isExeError:
            assert 0, 'Build application error'


    def testComponentBuildEx( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testComponentBuildEx' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'BldEx.component'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isCppExeError = True
        isCppDllError = True

        dir = utils.changeScope()
        if os.path.isfile( 'BldEx.vcproj' ):
            isCppExeError = False
        if os.path.isfile( 'Mega.vcproj' ):
            isCppDllError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        if isCppExeError:
            assert 0, 'Build component error'
        if isCppDllError:
            assert 0, 'Build component error'


    def testApplicationBuildEx( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testApplicationEx' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'ApplBldEx.application'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isCppExeError = True
        isCppDllError = True

        dir = utils.changeScope()
        if os.path.isfile( 'ApplBldEx.vcproj' ):
            isCppExeError = False
        if os.path.isfile( 'MegaAppl.vcproj' ):
            isCppDllError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        if isCppExeError:
            assert 0, 'Build application error'
        if isCppDllError:
            assert 0, 'Build application error'

            
    def testInstanceToString( self ):
        assert "222" == utils.instance2string( 222 )
        assert "dfsdfs" == utils.instance2string( "dfsdfs" )
        assert "['aaaa', 'bbbbb', 22222]" == utils.instance2string( [ 'aaaa', 'bbbbb', 22222 ] )
        assert "[22222, 'aaaa', 'bbbbb']" == utils.instance2string( set( [ 'aaaa', 'bbbbb', 22222 ] ) )
        assert "{ 2222: ['222', 'aaa'], 'aaa': ['aaaa', 'bbbbb', 22222] }" == utils.instance2string( { 'aaa': ['aaaa', 'bbbbb', 22222], 2222: set( [ 'aaa', '222' ] ) } )
        
        class Mock:
            def __init__( self ):
                self.container = { 'aaa': ['aaaa', 'bbbbb', 22222], 2222: set( [ 'aaa', '222' ] ) }
                self.value = 4444
        assert "Instanse of __main__.Mock:\n container            = { 2222: ['222', 'aaa'], 'aaa': ['aaaa', 'bbbbb', 22222] }\n value                = 4444" == utils.instance2string( Mock() )


    def testFileFilterTree1( self ):
        files = []
        files.append( BuildProject.FileInfo( 'test.cpp', [] ) )
        ffs = ''
        ffs = utils.generateFileFilterTree( files )
        assert ffs.files[0].file == 'test.cpp'


    def testFileFilterTree2( self ):
        files = []
        files.append( BuildProject.FileInfo( 'test.cpp', [] ) )
        files.append( BuildProject.FileInfo( 'test2.cpp', ['test'] ) )
        ffs = ''
        ffs = utils.generateFileFilterTree( files )
        assert ffs.files[0].file == 'test.cpp'
        assert ffs.children[0].files[0].file == 'test2.cpp'
        assert ffs.children[0].filtername == 'test'


    def testFileFilterTree3( self ):
        files = []
        files.append( BuildProject.FileInfo( 'test.cpp', [] ) )
        files.append( BuildProject.FileInfo( 'lol.cpp', [] ) )
        files.append( BuildProject.FileInfo( 'test1.cpp', ['test1','test'] ) )
        files.append( BuildProject.FileInfo( 'test2.cpp', ['test2','test'] ) )
        ffs = ''
        ffs = utils.generateFileFilterTree( files )
        string = ''
        string = sln.generateFileFilterTreeText( string, ffs )
        assert ffs.files[0].file == 'test.cpp'
        assert ffs.files[1].file == 'lol.cpp'
        assert ffs.children[0].filtername == 'test1'
        assert ffs.children[1].filtername == 'test2'
        assert ffs.children[0].children[0].filtername == 'test'
        assert ffs.children[1].children[0].filtername == 'test'
        assert ffs.children[0].children[0].files[0].file == 'test1.cpp'
        assert ffs.children[1].children[0].files[0].file == 'test2.cpp'


    def testBadFilter3( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testBadFilter3' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        dir = utils.changeScope()
        file = open( 'test.vcproj' )
        teststr = file.read()
        file.close()
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        mainidx = teststr.find( '<Files>' )
        idx1 = teststr.find( 'test.cpp', mainidx )
        assert idx1 != -1

        idx2 = teststr.find( '\"test2\"', mainidx )
        idx3 = teststr.find( '\"test\"', idx2 )
        idx4 = teststr.find( 'test2.cpp', idx3 )
        assert idx2 > mainidx
        assert idx3 > idx2
        assert idx4 > idx3

        idx5 = teststr.find( '\"test1\"', mainidx )
        idx6 = teststr.find( '\"test\"', idx5 )
        idx7 = teststr.find( 'test1.cpp', idx6 )
        assert idx5 > mainidx
        assert idx6 > idx5
        assert idx7 > idx6


    def testDefines( self ):
        folder = tempfile.mkdtemp() + "\\"
        dir = utils.changeScope( folder )
        
        text = "env.Append( 'ComponentsPath', '.' )"

        f = open( 'unittest.cfg', 'wb')
        f.write( text )
        f.close()
        
        # main.cpp

        text = """//!Component("Components")
#include "cxxtest/TestSuite.h"

struct defineSuit : public CxxTest::TestSuite 
{
    void testDummy( void )
    {
    }
};
"""
        f = open( 'main.cpp', 'wb')
        f.write( text )
        f.close()
        
        # all.component
        
        os.mkdir( "Components" ) 
        
        text = """# include only defines
defines = [ 'TEST111', 'TEST111', 'TEST211' ]

components = [
    'Components/defc'
]
"""
        f = open( 'Components/all.component', 'wb')
        f.write( text )             
        f.close()
        
        # defc.component 
        
        text = """# include only defines
defines = "TEST111;TEST311"
"""
        f = open( 'Components/defc.component', 'wb')
        f.write( text )
        f.close()

        fullPath = folder + 'main.cpp'
        textout, texterr = utils.runSubprocess( ['run.cmd', fullPath] )
        buildTestAssert( fullPath, textout, texterr )
    
        dir2 = utils.changeScope()
        file = open( 'main.vcproj' )
        test = file.read()
        file.close()
        del dir2
        
        assert test.find( 'TEST111' ) != -1, 'Bad generated vcproj file.'
        assert test.find( 'TEST311' ) != -1, 'Bad generated vcproj file.'

        del dir
        shutil.rmtree( folder )


    def testComponentGraph( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testComponentGraph' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isGraphError = True
        cgfilename = "test.graph"

        dir = utils.changeScope()
        file = open( 'test.sln' )
        teststr = file.read()
        file.close()
        if os.path.isfile( cgfilename ):
            isGraphError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        if isGraphError:
            assert 0, 'Components graph file error'
        if teststr.find( cgfilename ) == -1:
            assert 0, 'Add to sln components graph file error'


    def testInlined( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testInlined' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'main.component'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        afilename = "a.vcproj"
        isAError = True
        bfilename = "b.vcproj"
        isBError = True

        dir = utils.changeScope()
        if os.path.isfile( afilename ):
            isAError = False
        if os.path.isfile( bfilename ):
            isBError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        if isAError:
            assert 0, 'Inline error: A.vcproj not found'
        if isBError:
            assert 0, 'Inline error: B.vcproj not found'


    def testCSProjInComponent( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testCSProjInComponent' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'main.component', '--build'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        filename = "Simple.exe"
        isFileError = True

        dir = utils.changeScope( mypath+'/Debug' )
        if os.path.isfile( filename ):
            isFileError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )


                    shutil.rmtree( mypath+'/Debug' )

        if isFileError:
            assert 0, 'CSProjInComponent error: Simple.exe not found'


    def testSpaceFolder(self):
        cwd = os.getcwd()
        folder = tempfile.mkdtemp( suffix = "f o l d e r", dir = cwd)
        os.chdir(folder)
        
        test_text = '''#include <cxxtest/TestSuite.h>

struct TestFirst : public CxxTest::TestSuite 
{

    void test_Simple()
    {
        TS_ASSERT(1 == 1);
    }
};'''        
        name = 'test.test.cpp'
        f = open(name, 'wb')
        f.write(test_text)
        f.close()
        result = os.system('run %s' % name)
        assert result == 0
        os.chdir(cwd)
        shutil.rmtree(folder)


    def testCSVCProjInComponent( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testCSVCProjInComponent' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath+'main.component', '--build'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        csfilename = "Simple.exe"
        isCSFileError = True
        vcfilename = "VCPorj.exe"
        isVCFileError = True

        dir = utils.changeScope( mypath+'/Debug' )
        if os.path.isfile( csfilename ):
            isCSFileError = False
        if os.path.isfile( vcfilename ):
            isVCFileError = False
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        shutil.rmtree( mypath+'/Debug' )

        if isCSFileError:
            assert 0, 'CSVCProjInComponent error: Simple.exe not found'
        if isVCFileError:
            assert 0, 'CSVCProjInComponent error: VCPorj.exe not found'


    def testOutput( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testOutput' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath + 'test.cpp', '--output=bin2'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        isInstallBuilder = False
        isExeFile = False

        dir = utils.changeScope()
        dir2 = utils.changeScope( 'bin2' )
        if os.path.isfile( 'outcomp.file' ):
            isInstallBuilder = True
        if os.path.isfile( 'test.exe' ):
            isExeFile = True
        del dir2
        del dir

        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )

        assert isInstallBuilder
        assert isExeFile
    
    def testFilter( self ):   
        folder = tempfile.mkdtemp() + "\\"
        dir = utils.changeScope( folder )
        
        text = """sources = {
    'Temp' : [ 'main.cpp' ],
    'D&G' : [ 'file1.cpp' ]
}\n"""
        f = open( 'filter.component', 'wb')
        f.write( text )             
        f.close()

        f = open( 'main.cpp', 'wb')
        f.write( "int main() { return 0xDEAD; }\n" )             
        f.close()

        f = open( 'file1.cpp', 'wb')
        f.write( "void foo() {}\n" )             
        f.close()
        
        textout, texterr = utils.runSubprocess( ['run.cmd', folder + 'filter.component', '--output=bin', '--b'] )
        buildTestAssert( 'filter.component', textout, texterr )

        dir2 = utils.changeScope()
        file = open( 'filter.vcproj' )
        content = file.read()
        file.close()
        
        assert content.find( "D&amp;G" ) != -1, "Wrong replacement!"
        
        del dir2
        del dir
        shutil.rmtree( folder )
        
    def testComponentDependence( self ):
        folder = tempfile.mkdtemp() + "\\"
        dir = utils.changeScope( folder )
        
        text = "env.Append( 'ComponentsPath', '.' )"

        f = open( 'unittest.cfg', 'wb')
        f.write( text )
        f.close()

        text = """//!Component("sam/sm2")
#include "cxxtest/TestSuite.h"

struct ComponentDependence : public CxxTest::TestSuite 
{
    void testAddition( void )
    {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
    }
};
"""

        f = open( 'test.cpp', 'wb')
        f.write( text )
        f.close()

        os.mkdir( "sam" ) 
        
        text = """sources = ['sm2.cpp']
inlined = False
components = [ 'test1' ]
type = 'dll'
"""

        f = open( 'sam/sm2.component', 'wb')
        f.write( text )             
        f.close()
        
        text = """int sm2dll()
{
  return 0;
}
"""
        f = open( 'sam/sm2.cpp', 'wb')
        f.write( text )
        f.close()

        os.mkdir( "test1" )

        text = """sources = ['test.cs']
#inlined = False
"""
        f = open( 'test1/all.component', 'wb')
        f.write( text )             
        f.close()
        
        text = """using System;
using System.Collections.Generic;
using System.Text;

namespace template_console
{
    class Program
    {
        static void Main(string[] args)
        {
            System.Console.WriteLine("Hello world!");
        }
    }
}
"""
        f = open( 'test1/test.cs', 'wb')
        f.write( text )             
        f.close()
        
        fulPath = folder + 'test.cpp'
        textout, texterr = utils.runSubprocess( ['run.cmd', fulPath] )
        buildTestAssert( fulPath, textout, texterr )
        
        del dir
        shutil.rmtree( folder )


    def testInstallBuilder( self ):
        if os.path.isfile( 'unittest.cfg' ):
            os.remove( 'unittest.cfg' )
        mypath = os.path.abspath( workdir+'unittests/testInstallBuilder' )
        mypath += '/'
        listfiles = os.listdir('.')
        listfiles_set = set( listfiles )
        textout, texterr = utils.runSubprocess( ['run.cmd', mypath + 'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        dir = utils.changeScope()
        dir2 = utils.changeScope( 'debug' )
        if os.path.isfile( 'test.txt' ):
            f = open( 'test.txt' )
            if f.read() != 'TestOriginal':
                assert 0, 'Bad original file'
            f.close()
        else:
            assert 0, 'Cannot find file test.txt'
        del dir2
        del dir


        f = open( mypath + 'test.txt', 'w' )
        f.write( 'TestTwo' )
        f.close()

        textout, texterr = utils.runSubprocess( ['run.cmd', mypath + 'test.cpp'] )
        buildTestAssert( 'test.cpp', textout, texterr )

        dir = utils.changeScope()
        dir2 = utils.changeScope( 'debug' )
        if os.path.isfile( 'test.txt' ):
            f = open( 'test.txt' )
            if f.read() != 'TestTwo':
                assert 0, 'InstallBuilder does not replace file test.txt'
            f.close()
        else:
            assert 0, 'Cannot find file test.txt'
        del dir2
        del dir

        f = open( mypath + 'test.txt', 'w' )
        f.write( 'TestOriginal' )
        f.close()


        for file in os.listdir('.'):
            if not file in listfiles_set:
                if os.path.isfile( file ):
                    os.remove( file )
                elif os.path.isdir( file ):
                    shutil.rmtree( file )


if __name__ == '__main__':
    workdir = os.path.dirname( os.path.realpath( __file__ ) )
    if workdir: 
        workdir += '/'
    else: 
        workdir = '../'
    dir = utils.changeScope()
    unittest.main()
    del dir
    
    #os.system( "run.cmd --cleanup" )
