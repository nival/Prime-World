import os
import sys
import templates
import string
from ComponentsSystem import utils
import uuid
import componentAnalyzer
import sln
import shutil
import stat
import BuildProject

from string import Template


class EclipseCompilerOptions:
    def __init__( self ):
        self.directories = []

DEFAULTCOMPILERKEYS = '-c -fmessage-length=0 -msse'


def generatePreBuildStepScript( scriptname, cppname, options, startup, runArguments = "" ):
    string = 'import os\nimport sys\nimport subprocess\n\n'

    string += """def runSubprocess( args ):
    a = subprocess.Popen(
        ' '.join(args),
        shell = True,
        stdin = subprocess.PIPE,
        stderr = subprocess.PIPE,
        stdout = subprocess.PIPE)
    textout = a.stdout.read()
    texterr = a.stderr.read()
    a.wait()
    retcode = a.returncode

    return retcode, textout, texterr"""

    filetobuild = cppname

    if options.exceptions: exception = "--he"
    else: exception = ''

    #string += 'print \"__D\", sys.argv[0]\n'
    string += '\n\nos.chdir( r"'+ os.path.normpath( os.path.abspath( '../..' ) ) +'" )\n'
    string += "verbose = {0}\n".format( options.verblevel )
    if options.platform == 'win32':
        string += 'retcode, textout, texterr = runSubprocess( [\'run.cmd\', \'--arguments={0}.arguments\', {1} ] )\n'.format( scriptname, "sys.argv[1]" )
    elif options.platform == 'linux':
        string += 'retcode, textout, texterr = runSubprocess( [\'run.sh\', \'--arguments={0}.arguments\', {1} ] )\n'.format( scriptname, "sys.argv[1]" )
    else:
        sys.stderr.write( "Bad platform type: " + options.platform + "\n" )

    string += "if texterr: sys.stderr.write( texterr )\n"
    string += "if verbose >= 1 or retcode != 0: print textout\n"
    string += 'sys.exit(retcode)'

    file = open( scriptname, 'w' )
    file.write( string )
    file.close()
    
    # make argument file
    if not startup: projectOnly = " --projectOnly"
    else: projectOnly = ""
    
    arguments = r"{0} {1} {2} --generateOnly --compiler=gcc --platform={6} --verbose={3} --output={4}{5}".format( filetobuild, runArguments, exception, options.verblevel, options.output, projectOnly, options.platform )
    f = open( "{script}.arguments".format( script = scriptname ), "w" )
    f.write( arguments )
    f.close()

    return os.path.normpath( os.path.abspath( '../' + scriptname ) )


def addPreBuildStep( projtemplate, scriptname, options ):
    if options.platform == 'win32':
        mapping = { 'py_prebuildscript' : 'python ' + scriptname + " --configuration=" }
    elif options.platform == 'linux':
        mapping = { 'py_prebuildscript' : 'python26 ' + scriptname + " --configuration=" }
    else:
        sys.stderr.write( "Bad platform type: " + options.platform + "\n" )

    projtemplate = Template( projtemplate ).safe_substitute( mapping )
    return projtemplate


def generateFilesList( projects, options ):
    res = ''
    for proj in projects:
        res += generateFilesText( proj.files )
    return res


def addFilesToProject( projtemplate, projects, options ):
    filelist = generateFilesList( projects, options )
    mapping = { 'py_filelist' : filelist }
    projtemplate = Template( projtemplate ).safe_substitute( mapping )
    return projtemplate


def rmgeneric(path, __func__):
    os.chmod(path, stat.S_IWRITE)
    __func__(path)

            
def removeall(path):
    if not os.path.isdir(path):
        return
    
    files=os.listdir(path)

    for x in files:
        fullpath=os.path.join(path, x)
        if os.path.isfile(fullpath):
            f=os.remove
            rmgeneric(fullpath, f)
        elif os.path.isdir(fullpath):
            removeall(fullpath)
            f=os.rmdir
            rmgeneric(fullpath, f)


def deleteSvn(arg, dirname, names):
    if dirname.find( '.svn' ) != -1:
        removeall( dirname )
        shutil.rmtree( dirname )


def createEclipseProject( slnname, options, projects = [], sources = None, solutionfiles = [], runArguments = "" ):
    if len(projects) == 0:
        sys.stderr.write( "Bad project list" + projects + "\n" )
        return

    if options.verblevel >= 2:
        print 'Create eclipse project: ', slnname

    workspacepath = None
    if 'TestFrameworkPath' in os.environ:
        if options.platform == 'win32':
            workspacepath = os.path.abspath( os.environ['TestFrameworkPath'] ) + '/workspace/' + options.configuration
        elif options.platform == 'linux':
            workspacepath = os.path.abspath( os.environ['TestFrameworkPath'] ) + '/workspace/linux/' + options.configuration
        else:
            sys.stderr.write( "Bad platform type: " + options.platform + "\n" )

    if not os.path.isdir( '../.metadata' ):
        utils.copytree( workspacepath, '..' )
    else:
        try:
            utils.copytree( workspacepath+'/Test', '../Test' )
        except:
            pass

    os.path.walk( os.path.abspath('..'), deleteSvn, None )

    projfilename = os.path.abspath( '../' + slnname + '/.project' )
    cprojfilename = os.path.abspath( '../' + slnname + '/.cproject' )

    proj = open( projfilename, "r" )
    projtemplate = proj.read()
    proj.close()
    cproj = open( cprojfilename, "r" )
    cprojtemplate = cproj.read()
    cproj.close()

    projtemplate = addFilesToProject( projtemplate, projects, options )
    cprojtemplate = setCompilerKeys( cprojtemplate, projects, options )

    scriptname = utils.fixBackslashes( os.path.abspath( '../' + slnname + '.py' ) )
    generatePreBuildStepScript( scriptname, sources, options, True, runArguments = runArguments )
    cprojtemplate = addPreBuildStep( cprojtemplate, scriptname, options )

    proj = open( projfilename, "w" )
    proj.write( projtemplate )
    proj.close()
    cproj = open( cprojfilename, "w" )
    cproj.write( cprojtemplate )
    cproj.close()



def getAbsFilePath( file ):
    res = ''
    if os.path.isabs( file ):
        res += file
    else:
        res += os.path.abspath( '../'+file )
    return utils.fixBackslashes( res )


def getFullFilterPath( file ):
    res = ''
    for filter in file.filter:
        res += filter+'/'
    res += os.path.split(getAbsFilePath( file.file ))[1]
    return res


def generateFilesText( files ):
    res = ''
    res += "    <linkedResources>\n"
    for file in files:
        res += "        <link>\n"
        if not file.ignore:
            res += "            <name>src/" + getFullFilterPath( file ) + "</name>\n"
        else:
            res += "            <name>" + os.path.split(getAbsFilePath( file.file ))[1] + "</name>\n"
        res += "            <type>1</type>\n"
        res += "            <location>"
        res += getAbsFilePath( file.file )
        res += "</location>\n"
        res += "        </link>\n"
    res += "    </linkedResources>\n"
    return res
                         

def generateIncludePathList( compilerOptions ):
    res = """<option id="gnu.cpp.compiler.option.include.paths.1292584339" superClass="gnu.cpp.compiler.option.include.paths" valueType="includePath">"""
    for dir in compilerOptions.directories:
        dir = utils.fixBackslashes( dir )
        dir = '\"' + dir + '\"'
        res += """<listOptionValue builtIn="false" value=""" + dir + """/>"""
    res += """</option>"""
    return res


def parseCompilerKeys( projtemplate, projects, configuration ):
    configuration = configuration.lower()
    compilerKeys = []
    compilerOptions = EclipseCompilerOptions()
    for proj in projects:
        compilerKeys.extend( proj.getCompilerKeys(configuration).split('&#x0D;&#x0A;') )

    removed = set( [] )
    for key in compilerKeys:
        if key.find( "-I" ) != -1:
            directory = key[len("-I"):]
            if not compilerOptions.directories: compilerOptions.directories = [ directory ]
            elif directory not in compilerOptions.directories: compilerOptions.directories.append( directory )
            removed.add( key )

    for key in removed: compilerKeys.remove( key )
    compilerKeys = ' '.join( sorted( compilerKeys ) )
    compilerKeys =  DEFAULTCOMPILERKEYS + ' ' + compilerKeys
            
    mapping = { 
    'py_includelist_'+configuration : generateIncludePathList( compilerOptions ), 
    'py_compilerkeys_'+configuration : compilerKeys,
    }

    projtemplate = Template( projtemplate ).safe_substitute( mapping )

    return projtemplate

def setCompilerKeys( projtemplate, projects, options ):
    if len(projects) > 0:
        for configurationName in BuildProject.Configuration.configurationNames:
            projtemplate = parseCompilerKeys( projtemplate, projects, configurationName )
 
    return projtemplate