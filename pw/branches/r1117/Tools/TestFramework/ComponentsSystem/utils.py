import glob
import re
from optparse import OptionParser
import os
import fnmatch
import shutil
import hashlib
import subprocess
import inspect
import time
import xdrlib
import sys


class MSVCInfoException(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class FileFilterTree:
    
    def __init__( self, filtername = '', files = [], children = [] ):
        self.filtername = filtername
        self.files = files
        self.children = children

    def __hash__( self ):
        return hash( str( self ) )

    def __repr__( self ):
        return str( self )
        
    def __str__( self ):
        return utils.instance2string( self )

def getChildrenForDepth( root, dep ):
    depth = dep
    current_nodes = [root]

    while depth:
        current_res = []
        for node in current_nodes:
            for child in node.children:
                current_res.append( child )
        current_nodes = current_res
        depth = depth - 1

    return current_nodes


def isFilterInTree( root, filtername, dep ):
    for child in getChildrenForDepth( root, dep ):
        if child.filtername == filtername:
            return True, child

    return False, None


def addFilterToTree( child, filtername ):
    child.children.append( FileFilterTree( filtername, [], [] ) )
    return child.children[-1]


def addFileToTree( root, file ):
    res = False
    child = root
    for fidx in xrange( 0, len(file.filter) ):
        res, tempchild = isFilterInTree( child, file.filter[fidx], 1 )
        if not res:
            child = addFilterToTree( child, file.filter[fidx] )
        else:
            child = tempchild

    child.files.append( file )


def generateFileFilterTree( files ):
    root = FileFilterTree( '', [], [] )

    for file in files:
        if len(file.filter):
            addFileToTree( root, file )
        else:
            root.files.append( file )

    return root


def instance2string( instance, useQuote = False, format = True ):
    try:
        simpleType = not hasattr( instance, "__dict__" )
    except TypeError:
        simpleType = True
    
    result = ""
    if not simpleType:
        result += "Instanse of {0}:\n".format( instance.__class__ )
        lastIndex = len( instance.__dict__ ) - 1
        for index, attribute in enumerate( instance.__dict__ ):
            attributeName = instance2string( attribute, format = False )
            if attributeName == "options" or attributeName == "sharedCompilerKeys":
                continue
            if attributeName[0] != "_":
                value = getattr( instance, attribute )
                result += " {0:20} = {1}".format( attributeName, instance2string( value, format = False ) )
                if index < lastIndex and format: 
                    result += "\n"
    else:
        if issubclass( type( instance ), dict ):
            keys = instance.keys()
            keys.sort()
            result += "{"
            lastIndex = len( keys ) - 1
            for index, key in enumerate( keys ): 
                result += " {0}: {1}".format( instance2string( key, format = False, useQuote = True ), instance2string( instance[key], format = False, useQuote = True ) )
                if index < lastIndex: 
                    result += ","
                else: 
                    result += " "
            result += "}"
        elif issubclass( type( instance ), set ):
            container = list( instance )
            container.sort()
            result += "{0}".format( instance2string( container ) )
        elif issubclass( type( instance ), list ):
            result += "["
            lastIndex = len( instance ) - 1
            for index, value in enumerate( instance ): 
                result += "{0}".format( instance2string( value, format = False, useQuote = True ) )
                if index < lastIndex: 
                    result += ", "
            result += "]"
        elif issubclass( type( instance ), str ):
            if useQuote: 
                result += "'{0}'".format( instance )
            else: 
                result += "{0}".format( instance )
        else: 
            result += "{0}".format( instance )
    
    return result


def replaceSubStr( fullstr, toreplace, replacestr ):
    '''Replace all substrings in string'''
    idx = fullstr.find( toreplace )
    while idx != -1:
        fullstr = fullstr[:idx] + replacestr + fullstr[idx+len(toreplace):]
        idx = fullstr.find( toreplace )
    return fullstr


def fixBackslashes( fileName ):
    '''Convert backslashes to slashes in file name'''
    return re.sub( r'\\', '/', fileName, 0 )


def parseOption( options, name, possiblevals, usage ):
    '''Parse and validate options.'''
    if getattr( options, name ):
        optvalue = getattr( options, name ).lower()
        if not optvalue in possiblevals:
            sys.stderr.write( 'Bad ' + name + ' option value ' + getattr( options, name ) + '\n' )
            sys.stderr.write( usage + '\n' )
            exit( -1 )
        else:
            setattr( options, name, optvalue )
    return options


def _getEmptyFolders(path, result):
    deleted_all = True
    for name in os.listdir(path):
        if (name != '.') and (name != '..'):
            cur_dir = os.path.join(path, name)
            if os.path.isdir(cur_dir):
                if _getEmptyFolders(cur_dir, result):
                    result.append(cur_dir)
                else:
                    deleted_all = False
            else:
                deleted_all = False
    return deleted_all
    

def getEmptyFolders(path):
    result = []
    _getEmptyFolders(path, result)
    return result

  
def removeEmptyFolders(path):
    result = getEmptyFolders(path)
    for path in result:
        os.rmdir(path)


def matchPatterns(name, patterns, ignored = []):
    for mask in ignored:
        #TODO
        #print "MASK", mask, fnmatch.translate( mask ), name
        if re.match( fnmatch.translate( mask ), name ):
            return None
        if name.find( mask ) != -1:
            return None
    for pattern in patterns:        
        if re.match( fnmatch.translate( pattern ), name ):
            return pattern        
    return None        

 
def collectFiles(path, patterns, ignored = [], recursive=True, add_root=True):
    result = []
    for root, dirs, files in os.walk(path):
        for name in files:
            relativePath = os.path.join( root, name )[len(path)+1:]
            if matchPatterns(relativePath, patterns, ignored):
                value = os.path.join(root, name)
                if not add_root:
                    value = value[len(path)+1:]    
                result.append(value)
        if not recursive:
            break                    
    return result


def delDirRecursive( dirname, todel ):
    olddir = os.path.abspath( '.' )
    os.chdir( os.path.abspath( dirname ) )
    listfiles = os.listdir( '.' )
    for item in listfiles:
        if os.path.isdir( item ):
            delDirRecursive( item, todel )

    if os.path.isdir( todel ):
        shutil.rmtree( todel )

    os.chdir( olddir )
    
def copytree(src, dst, symlinks=False, ignore=None):
    names = os.listdir(src)
    if ignore is not None:
        ignored_names = ignore(src, names)
    else:
        ignored_names = set()

    try: os.makedirs(dst)
    except: pass
    
    errors = []
    for name in names:
        if name in ignored_names:
            continue
        srcname = os.path.join(src, name)
        dstname = os.path.join(dst, name)
        try:
            if symlinks and os.path.islink(srcname):
                linkto = os.readlink(srcname)
                os.symlink(linkto, dstname)
            elif os.path.isdir(srcname):
                copytree(srcname, dstname, symlinks, ignore)
            else:
                shutil.copy2(srcname, dstname)
            # XXX What about devices, sockets etc.?
        except (IOError, os.error), why:
            errors.append((srcname, dstname, str(why)))
        # catch the Error from the recursive copytree so that we can
        # continue with other files
        except Error, err:
            errors.extend(err.args[0])
    try:
        shutil.copystat(src, dst)
    except WindowsError:
        # can't copy file access times on Windows
        pass
    except OSError, why:
        errors.extend((src, dst, str(why)))
    if errors:
        raise Error, errors


def pathsplit( p, rest=[] ):
    ( h, t ) = os.path.split( p )
    if len( h ) < 1: 
        return [t] + rest
    if len( t ) < 1: 
        return [h] + rest
    return pathsplit( h, [t] + rest )


def commonpath( l1, l2, common=[] ):
    if len( l1 ) < 1: 
        return ( common, l1, l2 )
    if len( l2 ) < 1: 
        return ( common, l1, l2 )
    if l1[0].lower() != l2[0].lower(): 
        return ( common, l1, l2 )
    return commonpath( l1[1:], l2[1:], common+[l1[0]] )


def getRelPath( p1, p2 ):
    p1 = fixBackslashes( removeUnusedSeparator( p1 ) )
    p2 = fixBackslashes( p2 )
    ( common, l1, l2 ) = commonpath( pathsplit( p1 ), pathsplit( p2 ) )
    p = []
    if len( l1 ) > 0:
        p = [ '../' * len( l1 ) ]
    p = p + l2
    if len( p ) is 0:
        return '.'
    path = os.path.join( *p )
    return fixBackslashes( os.path.normpath( path ) )


def getRedundantPath( abspath, root ):
    path = fixBackslashes( abspath ).lower()
    rootpath = fixBackslashes( root ).lower()
    iskillslash = False

    if len( rootpath ) == 0:
        return path

    if rootpath[-1] != '/':
        rootpath += '/'

    if path[-1] != '/':
        iskillslash = True
        path += '/'

    if path.find( rootpath ) == 0:
        path = path[len(rootpath):]

    if iskillslash:
        path = path[:-1]

    return path


def md5( fileName, excludeLine="", includeLine="" ):
    """Compute md5 hash of the specified file"""
    try:
        fd = open( fileName, "rb" )
        content = fd.readlines()
        fd.close()
        m = hashlib.md5()
        for eachLine in content:
            if excludeLine and eachLine.startswith( excludeLine ):
                continue
            m.update( eachLine )
            m.update( includeLine )
        return m.hexdigest()
    except IOError:
        sys.stderr.write( "Unable to open the file in readmode: " + filename + "\n" )
        return None

def calculateMD5ForFile( fileName ):
    file = open( fileName )
    string = file.read()
    file.close()
    return calcMD5( string )


def calcMD5( strtocalc ):
    m = hashlib.md5()
    m.update( strtocalc )
    return m.hexdigest()
    
def calculateHash( result, evaluateFiles = True ):
    if issubclass( type( result ), list ):
        hash = 0
        for item in result:
            hash ^= int( calculateHash( item, evaluateFiles ), 16 )
        return str( hash )
    elif issubclass( type( result ), set ):
        result = list( result )
        result.sort()
        return calculateHash( result, evaluateFiles )
    elif issubclass( type( result ), dict ):
        keys = result.keys()
        keys.sort()
        hash = 0
        for key in keys:
            hash ^= int( calculateHash( key, evaluateFiles ), 16 )
            hash ^= int( calculateHash( result[key], evaluateFiles ), 16 )
        return str( hash )
    elif issubclass( type( result ), str ):
        if os.path.isfile( result ) and evaluateFiles: return str( calculateMD5ForFile( result ) )
        else: return str( calcMD5( result ) )
    else:
        return str( calcMD5( result ) )

def testHashForFile( file, md5hash_filename, options ):
    hashstr = getHashForFile( file, md5hash_filename )

    if not hashstr:
        if options.verblevel >= 2: 
            print 'hash not found: ', file
        return True

    if hashstr != calculateMD5ForFile( file ):
        if options.verblevel >= 2: 
            print 'hash:', hashstr, 'real file:', calculateMD5ForFile( file )
        return True

    return False


def testDeepHash( key, string, md5hash_filename, options ):
    hashstr = getHashForKey( key, md5hash_filename )

    if not hashstr:
        if options.verblevel >= 2: 
            print 'hash not found: ', key
        return True

    calculatedHash = calcMD5( string )
    if hashstr != calculatedHash:
        if options.verblevel >= 2: 
            print 'stored hash:', hashstr, 'calculated hash:', calculatedHash, 'key:', key
        return True

    return False


def setDeepHash( key, string, md5hash_filename ):
    hashstr = ''

    if os.path.isfile( md5hash_filename ):
        hashfile = open( md5hash_filename, 'r' )
        hashstr = hashfile.read()
        hashfile.close()

    if hashstr.find( calcMD5( string ) ) != -1:
        return

    idx = hashstr.find( key )
    if idx == -1:

        if len(hashstr) and ( hashstr[-1] == '\n' or hashstr[-1] == '\r' ):
            hashstr += 'md5class.Set( \'' + key + '\', \'' + calcMD5( string ) + '\' )\n'
        elif len(hashstr):
            hashstr += '\nmd5class.Set( \'' + key + '\', \'' + calcMD5( string ) + '\' )\n'
        else:
            hashstr += 'md5class.Set( \'' + key + '\', \'' + calcMD5( string ) + '\' )\n'

        hashfile = open( md5hash_filename, 'w' )
        hashfile.write( hashstr )
        hashfile.close()
    else:
        idx2 = idx-15
        if idx2 != -1:
            idx3 = hashstr.find( '\n', idx2 )
            if idx3 != -1:
                hashstr = hashstr[:idx2] + 'md5class.Set( \'' + key + '\', \'' + calcMD5( string ) + '\' )' + hashstr[idx3:]
                hashfile = open( md5hash_filename, 'w' )
                hashfile.write( hashstr )
                hashfile.close()
            else:
                sys.stderr.write( "Find error 1\n" )
        else:
            sys.stderr.write( "Find error 2\n" )


def getHashForKey( key, md5hash_filename ):
    if not os.path.isfile( md5hash_filename ):
        return None

    hashfile = open( md5hash_filename, 'r' )
    hashstr = hashfile.read()
    hashfile.close()
    idx = hashstr.find( key )
    if idx == -1:
        return None

    resstr = hashstr[ idx + len(key) + 4 : idx + len(key) + 4 + len( calcMD5( key ) ) ]
    return resstr


def testHashForString( file, string, md5hash_filename, options ):
    '''return <Ubdated> <Present in storage>'''
    hashstr = getHashForFile( file, md5hash_filename )

    if not hashstr:
        if options.verblevel >= 2: 
            print 'hash not found: ', file
        return True, False

    calculatedHash = calcMD5( string )
    if hashstr != calculatedHash:
        if options.verblevel >= 2: 
            print 'stored hash:', hashstr, 'calculated hash:', calculatedHash, 'file:', file
        return True, True

    return False, True


def getHashForFile( file, md5hash_filename ):
    abspath = fixBackslashes( os.path.normcase( os.path.abspath( '.' ) ) )
    file = getRelPath( abspath, fixBackslashes( os.path.normcase( file ) ) )
    
    if not os.path.isfile( md5hash_filename ):
        return None

    hashfile = open( md5hash_filename, 'r' )
    hashstr = hashfile.read()
    hashfile.close()
    idx = hashstr.find( file )
    if idx == -1:
        return None
    
    if not os.path.isfile( file ):
        return None

    srcfile = open( file )
    srcstr = srcfile.read()
    srcfile.close()
    resstr = hashstr[ idx + len(file) + 4 : idx + len(file) + 4 + len( calcMD5( srcstr ) ) ]
    return resstr


def setHashForFile( file, md5hash_filename ):
    hashstr = ''

    abspath = fixBackslashes( os.path.normcase( os.path.abspath( '.' ) ) )
    file = getRelPath( abspath, fixBackslashes( os.path.normcase( file ) ) )

    srcfile = open( file )
    srcstr = srcfile.read()
    srcfile.close()

    if os.path.isfile( md5hash_filename ):
        hashfile = open( md5hash_filename, 'r' )
        hashstr = hashfile.read()
        hashfile.close()

    if hashstr.find( calcMD5( srcstr ) ) != -1:
        return

    idx = hashstr.find( file )
    if idx == -1:

        if len(hashstr) and ( hashstr[-1] == '\n' or hashstr[-1] == '\r' ):
            hashstr += 'md5class.Set( \'' + file + '\', \'' + calcMD5( srcstr ) + '\' )\n'
        elif len(hashstr):
            hashstr += '\nmd5class.Set( \'' + file + '\', \'' + calcMD5( srcstr ) + '\' )\n'
        else:
            hashstr += 'md5class.Set( \'' + file + '\', \'' + calcMD5( srcstr ) + '\' )\n'

        hashfile = open( md5hash_filename, 'w' )
        hashfile.write( hashstr )
        hashfile.close()
    else:
        idx2 = idx-15
        if idx2 != -1:
            idx3 = hashstr.find( '\n', idx2 )
            if idx3 != -1:
                hashstr = hashstr[:idx2] + 'md5class.Set( \'' + file + '\', \'' + calcMD5( srcstr ) + '\' )' + hashstr[idx3:]
                hashfile = open( md5hash_filename, 'w' )
                hashfile.write( hashstr )
                hashfile.close()
            else:
                sys.stderr.write( "Find error 1\n" )
        else:
            sys.stderr.write( "Find error 2\n" )


def setHashForString( file, string, md5hash_filename ):
    hashstr = ''

    abspath = fixBackslashes( os.path.normcase( os.path.abspath( '.' ) ) )
    file = getRelPath( abspath, fixBackslashes( os.path.normcase( file ) ) )

    if os.path.isfile( md5hash_filename ):
        hashfile = open( md5hash_filename, 'r' )
        hashstr = hashfile.read()
        hashfile.close()

    if hashstr.find( calcMD5( string ) ) != -1:
        return

    idx = hashstr.find( file )
    if idx == -1:

        if len(hashstr) and ( hashstr[-1] == '\n' or hashstr[-1] == '\r' ):
            hashstr += 'md5class.Set( \'' + file + '\', \'' + calcMD5( string ) + '\' )\n'
        elif len(hashstr):
            hashstr += '\nmd5class.Set( \'' + file + '\', \'' + calcMD5( string ) + '\' )\n'
        else:
            hashstr += 'md5class.Set( \'' + file + '\', \'' + calcMD5( string ) + '\' )\n'

        hashfile = open( md5hash_filename, 'w' )
        hashfile.write( hashstr )
        hashfile.close()
    else:
        idx2 = idx-15
        if idx2 != -1:
            idx3 = hashstr.find( '\n', idx2 )
            if idx3 != -1:
                hashstr = hashstr[:idx2] + 'md5class.Set( \'' + file + '\', \'' + calcMD5( string ) + '\' )' + hashstr[idx3:]
                hashfile = open( md5hash_filename, 'w' )
                hashfile.write( hashstr )
                hashfile.close()
            else:
                sys.stderr.write( "Find error 1\n" )
        else:
            sys.stderr.write( "Find error 2\n" )


def storeComponentsHash( components, options, configfilename ):
    #print "\n----------------"
    for comp in components:
        #print comp
        setHashForString( comp.descriptor, str(comp), configfilename )
    #print "----------------\n"
    

pathRegression = re.compile( r'(?P<path>(?:.*[\\/]+)|(?:))(?P<shortName>.*)', re.I | re.U )
def shortName( name ):
    match = pathRegression.search( name )
    if match: 
        return match.group( 'shortName' )
    else: 
        return name
    
def pathName( name ):
    match = pathRegression.search( name )
    if match: return match.group( 'path' )
    else: return name

def removeUnusedSeparator( string, separators = ['/', '\\'] ):
    for separator in separators:
        if len(string) > 0 and string[len(string) - 1] == separator: 
            return string[:-1]
    return string

def runSubprocess( args ):
    a = subprocess.Popen(
        ' '.join(args),
        shell = True,
        stdin = subprocess.PIPE,
        stderr = subprocess.PIPE,
        stdout = subprocess.PIPE)
    textout = a.stdout.read()
    texterr = a.stderr.read()
    a.wait()
    p = a.returncode
    if p != 0:
        textout += ": error Unknown error."

    return textout, texterr


def runSubprocessInteractive( args ):
    sys.stdout.flush()
    sys.stderr.flush()
    a = subprocess.Popen(
        ' '.join(args),
        shell = True,
        stdout = sys.stdout,
        stderr = sys.stderr)
    a.wait()
    return a.returncode


class Directory:
    
    def __init__( self, directory ):
        self.previousDirectory = os.getcwd()
        os.chdir( directory )
    
    def __del__( self ):
        os.chdir( self.previousDirectory )
        

class dir_holder:

    def __init__( self, directory ):
        self.directory = directory
        
    def __del__( self ):
        shutil.rmtree( self.directory )        


class TimeTest:

    def __init__( self, msg, isprint = False ):
        self.msg = msg
        self.starttime = time.time()
        self.isprint = isprint

    def __del__( self ):
        if self.isprint:
            print self.msg, time.time()-self.starttime


def getClassesInModule( module ):
    classes = []

    for name in dir( module ):
        obj = getattr( module, name )
        if inspect.isclass( obj ):
            classes.append( obj )

    return classes


def getHtmlTemplate( templatename ):
    templatefile = ""
    if 'TestFrameworkPath' in os.environ:
        templatefile = open( os.path.abspath( os.environ['TestFrameworkPath'] ) + '/Vendors/html_template/' + templatename, 'r' )
    else:
        templatefile = open( templatename, 'r' )
    template = templatefile.read()
    templatefile.close()
    return template


def getUniqFileName( dirname, filename = '', suffix = '' ):
    m = hashlib.md5()
    m.update( dirname + filename )
    return m.hexdigest() + suffix + '.html'


def changeScope( path = '.auto' ):
    #change path to temp dir    
    if not os.path.isdir( path ): 
        os.makedirs( path )
    return Directory( path )
    

def getPlatformCmd( cmd, platform = 'win32' ):
    if platform == 'win32':
        if cmd == 'createProj':
            return 'createVCProj'
        elif cmd == 'addProjectToSLN':
            return 'addVCProjectToSLN'
        elif cmd == 'generateProjects':
            return 'generateVCProjects'
    elif platform == '.net':
        if cmd == 'createProj':
            return 'createCSProj'
        elif cmd == 'addProjectToSLN':
            return 'addCSProjectToSLN'
        elif cmd == 'generateProjects':
            return 'generateCSProjects'
    assert 0, 'Can\'t find cmd ' + cmd + ' for platform ' + platform


def parseVCProj( projfilename ):
    ( projName, extention ) = os.path.splitext( os.path.split( projfilename )[1] )
    uuid = None
    file = open( projfilename )
    filestr = file.read()
    file.close()
    startstr = 'ProjectGUID=\"{'
    endstr = '}\"'
    startidx = filestr.find( startstr )
    if startidx != -1:
        endidx = filestr.find( endstr, startidx+1 )
        if endidx != -1:
            uuid = filestr[startidx+len(startstr):endidx]

    if not uuid:
        raise Exception( 'Can not find UUID for project ' + projName )
    return ( projName, uuid )


def parseCSProj( projfilename ):
    ( projName, extention ) = os.path.splitext( os.path.split( projfilename )[1] )
    uuid = None
    file = open( projfilename )
    filestr = file.read()
    file.close()
    startstr = '<ProjectGuid>{'
    endstr = '}</ProjectGuid>'
    startidx = filestr.find( startstr )
    if startidx != -1:
        endidx = filestr.find( endstr, startidx+1 )
        if endidx != -1:
            uuid = filestr[startidx+len(startstr):endidx]

    if not uuid:
        raise Exception( 'Can not find UUID for project ' + projName )
    return ( projName, uuid )


additionalParseProjTypes = {
    '*.csproj' : parseCSProj,
    '*.vcproj' : parseVCProj,
}


def parseProj( projname ):
    for extention, cmd in additionalParseProjTypes.iteritems():
        if fnmatch.fnmatch( projname, extention ):
            return cmd( projname )
    return ( None, None )


if __name__ == '__main__':
    pass
