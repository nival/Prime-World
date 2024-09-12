import fnmatch
import re
import os
from ComponentsSystem import utils


class LogData:
    
    def __init__( self ):
        self.results = []
        self.components = set([])
        self.buildLog = ''
        self.rawText = ''
        self.memoryLeaks = ''


class TestResult:
    
    dirname = ""
    filename = ""
    testcase = ""
    errorstr = ""
    testline = "0"
    testtime = 0

    def __eq__( self, a ):
        if self.dirname == a.dirname and self.filename == a.filename and self.testcase == a.testcase and self.errorstr == a.errorstr:
            return True
        return False


def findLeft( string, substr, pos ):
    curpos = string.find( substr )
    lastpos = curpos

    while curpos != -1 and curpos <= pos:
        lastpos = curpos
        curpos = string.find( substr, curpos+1 )

    return lastpos

def parseBuildResult( textout, texterr, options ):
    curpos = 0

    isHaveError = True

    res = ''

    while isHaveError:
        isHaveError = False
        nextpos = textout.find( ': error ', curpos )
        if nextpos != -1:
            startpos = findLeft( textout, '\n', nextpos )
            endpos = textout.find( ': error ', nextpos+1 )
            if endpos != -1:
                endpos = findLeft( textout, '\n', endpos )
            else:
                endpos = textout.find( '\n', nextpos+1 )
            isHaveError = True
            curpos = nextpos + 1
            res += textout[startpos:endpos]
        else:
            nextpos = textout.find( ': fatal error ', curpos )
            if nextpos != -1:
                startpos = findLeft( textout, '\n', nextpos )
                endpos = textout.find( ': error ', nextpos+1 )
                if endpos != -1:
                    endpos = findLeft( textout, '\n', endpos )
                else:
                    endpos = textout.find( '\n', nextpos+1 )
                isHaveError = True
                curpos = nextpos + 1
                res += textout[startpos:endpos]

    if res:
        return False, res

    return True, ''


def generateBadBuildResult( sources, text, testtime ):
    reses = []

    path = ''

    if isinstance( sources, list ):
        for info in sources:

            path = os.path.normcase( os.path.dirname( info.filename ) )

            res = TestResult()
            res.dirname = path
            res.filename = info.filename
            res.testtime = testtime
            res.errorstr = 'Build Error'
            res.testcase = 'Build Error'
            reses.append( res )
    else:

        if sources:
            path = os.path.normcase( os.path.dirname( sources ) )

        res = TestResult()
        res.dirname = path
        res.filename = sources
        res.testtime = testtime
        res.errorstr = text
        res.testcase = 'Build Error'
        reses.append( res )

    return reses


def generateTestResult( sources, textout, texterr, testtime ):

    res = []

    path = ''

    if isinstance( sources, list ):
        for info in sources:

            path = os.path.normcase( os.path.dirname( info.filename ) )

            toaddres = []

            if fnmatch.fnmatch( info.filename, '*.cpp' ) or fnmatch.fnmatch( info.filename, '*.h' ):
                toaddres.extend( parseCppResult( path, info.filename, textout, texterr, testtime ) )
            elif fnmatch.fnmatch( info.filename, '*.py' ) or fnmatch.fnmatch( info.filename, '*.pyc' ):
                toaddres.extend( parsePyResult( path, info.filename, textout, texterr, testtime ) )
            elif fnmatch.fnmatch( info.filename, '*.java' ):
                toaddres.extend( parseJavaResult( path, info.filename, textout, texterr, testtime ) )

            for toadd in toaddres:
                isAlreadyIn = False
                for r in res:
                    if r == toadd:
                        isAlreadyIn = True
                        break
                if not isAlreadyIn:
                    res.append( toadd )

    else:

        path = os.path.normcase( os.path.dirname( sources ) )
        
        toaddres = []

        if fnmatch.fnmatch( sources, '*.cpp' ) or fnmatch.fnmatch( sources, '*.h' ):
            toaddres.extend( parseCppResult( path, sources, textout, texterr, testtime ) )
        elif fnmatch.fnmatch( sources, '*.py' ) or fnmatch.fnmatch( sources, '*.pyc' ):
            toaddres.extend( parsePyResult( path, sources, textout, texterr, testtime ) )
        elif fnmatch.fnmatch( sources, '*.java' ):
            toaddres.extend( parseJavaResult( path, sources, textout, texterr, testtime ) )

        for toadd in toaddres:
            isAlreadyIn = False
            for r in res:
                if r == toadd:
                    isAlreadyIn = True
                    break
            if not isAlreadyIn:
                res.append( toadd )

    return res


def getMemoryLeaksInfo( info ):
    startIdx = info.find('Memory leaks info START')
    endIdx = info.find('Memory leaks info END')
    if startIdx == -1 or endIdx == -1:
        return ''
    startIdx += len('Memory leaks info START')
    return info[startIdx:endIdx]


def findErrorText( casestr, textout ):
    res = ''
    
    idx = textout.find( casestr )
    if idx == -1:
        return 'Error1'
    idx2 = textout.find( ' Error: ', idx )

    if idx2 == -1:
        return 'Error2'

    idx3 = textout.find( '\n', idx2 )
    if idx3 == -1:
        return 'Error3'

    res += textout[idx2+8:idx3]

    #Find exception
    excidx = textout.find( ' Error: ', idx3 )
    if excidx != -1:
        excidx2 = textout.find( '\n', excidx )
        if excidx2 != -1:
            res += textout[excidx+8:excidx2]

    return res


def findErrorLine( casestr, textout ):
    idx = textout.find( casestr )
    if idx == -1:
        return '0'

    idx2 = textout.find( '(', idx )
    if idx2 == -1:
        return '0'

    idx3 = textout.find( ')', idx2+1 )
    if idx3 == -1:
        return '0'

    return textout[idx2+1:idx3]


def findErrorTextPy( casestr, textout ):
    idx = textout.find( casestr )
    if idx == -1:
        return 'Error1'
    idx2 = textout.find( '----------------------------------------------------------------------', idx )

    if idx2 == -1:
        return 'Error2'

    idx3 = textout.find( '----------------------------------------------------------------------', idx2+1 )
    idx4 = textout.find( '======================================================================', idx2+1 )

    if idx4 < idx3 and idx4 != -1:
        idx3 = idx4

    return textout[idx2+70:idx3]


def parseCppResult( path, filename, textout, texterr, testtime ):
    reses = []

    shortfilename = os.path.basename( filename )
  
    numtests = 1
    failedtests = []

    numtestRegression = re.compile( r'Running (?P<int>\d+) tests', re.I | re.U )
    match = numtestRegression.search( textout )
    if match:
        numtests = int( match.group( 'int' ) )

    failedRegression_Ivn = re.compile( r'[\s]?(?P<testcase>[\w0-9_\|!@\-]+(::[\w0-9_\|!@\-]+)+:)([^:]|$)', re.I | re.U )
    match = failedRegression_Ivn.findall( textout )
    if match:
        for m in match:
            failedtests.append( m[0] )

    filename_low = filename.lower()

    findIdx = textout.lower().find( '$_file_$ ' + filename_low )
    while findIdx != -1:
        findEnd = textout.lower().find( '\n', findIdx )
        if findEnd == -1:
            break
        res = TestResult()
        res.dirname = path
        res.filename = shortfilename
        res.testtime = testtime
  
        testLineStartIdx = textout.lower().find( ' $_line_$ ', findIdx ) + len(' $_line_$ ')
        testLineEndIdx = textout.lower().find( ' ', testLineStartIdx+1 )
        res.testline = textout[testLineStartIdx:testLineEndIdx]

        testCaseStartIdx = textout.lower().find( ' $_test_$ ', findIdx ) + len(' $_test_$ ')
        testCaseEndIdx = textout.lower().find( ' ', testCaseStartIdx+1 )
        res.testcase = textout[testCaseStartIdx:testCaseEndIdx]

        testErrorStartIdx = textout.lower().find( ' $_error_$ ', findIdx ) + len(' $_error_$ ')
        res.errorstr = textout[testErrorStartIdx:findEnd]
        reses.append( res )

        findIdx = textout.lower().find( '$_file_$ ' + filename_low, findEnd )


    findIdx = textout.lower().find( 'win32seh.h' )
    while findIdx != -1:
        findEnd = textout.lower().find( '\n', findIdx )
        if findEnd == -1:
            break
        res = TestResult()
        res.dirname = '.'
        res.filename = 'Exceptions'
        res.testtime = testtime
  
        testLineStartIdx = textout.lower().find( ' $_line_$ ', findIdx ) + len(' $_line_$ ')
        testLineEndIdx = textout.lower().find( ' ', testLineStartIdx+1 )
        res.testline = textout[testLineStartIdx:testLineEndIdx]

        testCaseStartIdx = textout.lower().find( ' $_test_$ ', findIdx ) + len(' $_test_$ ')
        testCaseEndIdx = textout.lower().find( ' ', testCaseStartIdx+1 )
        res.testcase = textout[testCaseStartIdx:testCaseEndIdx]

        testErrorStartIdx = textout.lower().find( ' $_error_$ ', findIdx ) + len(' $_error_$ ')
        res.errorstr = textout[testErrorStartIdx:findEnd]
        reses.append( res )

        findIdx = textout.lower().find( 'win32seh.h', findEnd )


    findIdx = textout.lower().find( 'runner.cpp' )
    while findIdx != -1:
        findEnd = textout.lower().find( '\n', findIdx )
        if findEnd == -1:
            break
        res = TestResult()
        res.dirname = '.'
        res.filename = 'TimeOuts'
        res.testtime = testtime
  
        testLineStartIdx = textout.lower().find( ' $_line_$ ', findIdx )
        testLineEndIdx = textout.lower().find( ' ', testLineStartIdx+1 )
        if testLineStartIdx != -1:
            testLineStartIdx += len(' $_line_$ ')
        if testLineStartIdx != -1 and testLineEndIdx != -1:
            res.testline = textout[testLineStartIdx:testLineEndIdx]
        else:
            res.testline = '0'

        testCaseStartIdx = textout.lower().find( ' $_test_$ ', findIdx )
        testCaseEndIdx = textout.lower().find( ' ', testCaseStartIdx+1 )
        if testCaseStartIdx != -1:
            testCaseStartIdx += len(' $_test_$ ')
        if testCaseStartIdx != -1 and testCaseEndIdx != -1:
            res.testcase = textout[testCaseStartIdx:testCaseEndIdx]
        else:
            res.testcase = 'None'

        testErrorStartIdx = textout.lower().find( ' $_error_$ ', findIdx )
        if testErrorStartIdx != -1:
            testErrorStartIdx += len(' $_error_$ ')
        if testErrorStartIdx != -1:
            res.errorstr = textout[testErrorStartIdx:findEnd]
        else:
            res.errorstr = 'None'

        if res.testcase != 'None' or res.errorstr != 'None' or res.testline != '0':
            reses.append( res )

        findIdx = textout.lower().find( 'runner.cpp', findEnd )

    idxb = 0
    idxe = 0
    for idx in xrange( 0, numtests - len(failedtests) ):
        idxb = textout.find( 'Runtest', idxe )
        if idxb == -1:
            return reses
        idxe = textout.find( 'Endtest', idxb )
        if idxe == -1:
            return reses

        stringa = textout[idxb:idxe]
        stringa_low = stringa.lower()

        if stringa_low.find( filename_low ) != -1:
            testCaseNames = stringa.split(' ')
            res = TestResult()
            res.dirname = path
            res.filename = shortfilename
            res.testline = "0"
            res.testtime = testtime
            res.testcase = testCaseNames[2]+'::'+testCaseNames[3]
            reses.append( res )

    return reses


def parsePyResult( path, filename, textout, texterr, testtime ):
    reses = []

    shortfilename = os.path.basename( filename )

    numtests = 1
    failedtests = []

    numtestRegression = re.compile( r'Ran (?P<int>\d+) test', re.I | re.U )
    match = numtestRegression.search( texterr )
    if match:
        numtests = int( match.group( 'int' ) )

    failedRegression = re.compile( r'FAIL: (?P<testcase>[\w0-9_\|!@\-]+)', re.I | re.U )
    match = failedRegression.findall( texterr )
    if match:
        failedtests = match

    for idx in xrange( 0, len(failedtests) ):
        res = TestResult()
        res.dirname = path
        res.filename = shortfilename
        res.testtime = testtime
        res.testcase = str( failedtests[idx] )
        res.testline = "0"
        res.errorstr = findErrorTextPy( res.testcase, texterr )
        reses.append( res )

    okstr = ' ... ok'
    flstr = ' ... FAIL'

    idxb = 0
    idxe = 0
    for idx in xrange( len(failedtests), numtests ):
        idxe = texterr.find( okstr, idxb )
        if idxe == -1:
            return reses
        stringa = texterr[idxb:idxe]
        idxf = stringa.rfind( flstr )
        if idxf != -1:
            stringa = stringa[idxf+len(flstr):]

        iden = stringa.find( '(' )
        if iden == -1:
            return reses

        stringa = stringa[:iden]

        res = TestResult()
        res.dirname = path
        res.filename = shortfilename
        res.testtime = testtime
        res.testcase = stringa
        res.testline = "0"
        reses.append( res )
        idxb = texterr.find( '\n', idxe )

    return reses


def parseJavaResult( path, filename, textout, texterr, testtime ):
    reses = []

    shortfilename = os.path.basename( filename )

    res = TestResult()
    res.dirname = path
    res.filename = shortfilename
    res.testtime = testtime
    res.testcase = ''
    res.testline = "0"
    res.errorstr = ''
    reses.append( res )

    return reses
