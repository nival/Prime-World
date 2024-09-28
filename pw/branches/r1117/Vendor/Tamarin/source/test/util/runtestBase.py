#!/usr/bin/env python
#
# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is [Open Source Virtual Machine.].
#
# The Initial Developer of the Original Code is
# Adobe System Incorporated.
# Portions created by the Initial Developer are Copyright (C) 2005-2009
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   christine@netscape.com
#   Adobe AS3 Team
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK ***** */
#
#
# simple script that executes tamarin certification tests.  you have to build the
# stand-alone, avmplus executable.  
# see http://developer.mozilla.org/en/docs/Tamarin_Build_Documentation 
#
# this test looks for an executable avmplus shell in
# %MOZ_SRC/mozilla/js/tamarin/platform/,
#

import os, sys, getopt, datetime, pipes, glob, itertools, tempfile, string, re, platform, shutil
import subprocess, random
from os.path import abspath, basename, dirname, exists, isdir, isfile, split, splitext
from os import getcwd,environ
from datetime import datetime
from glob import glob
from sys import argv, exit
from getopt import getopt
from itertools import count
from time import time,sleep
import shutil
import which

import threadpool

# For Python 2.6 and above, use native subprocess.Popen
if sys.version_info[0] >= 3 or (sys.version_info[0] == 2 and sys.version_info[1] >= 6):
    from subprocess import Popen
else:
    from killableprocess import Popen


# runtestUtils must be imported after "from os.path import *" as walk is overridden
from runtestUtils import *


try:
    import pexpect
except ImportError:
    pexpect = False
    

class RuntestBase:
    abcasmExt = '.abs'
    abcasmRunner = 'bash ../../utils/abcasm/abcasm.sh'
    abcasmShell = 'abcasm/abs_helper'
    abcdump = '../../utils/abcdump'
    asc = ''
    ascargs = ''
    atsDir = 'ATS_SWFS'
    avm = ''
    avmce = ''
    builtinabc = ''
    config = ''
    escbin = ''
    includes = None
    java = 'java'
    js_output = ''
    js_output_f = None
    logFileType = 'html'
    options = ''
    osName = ''
    playerglobalabc = ''
    settings = None
    shellabc = ''
    sourceExt = '.as'
    testconfig = 'testconfig.txt'
    vmargs = ''
    vmtype = ''
    
    args = []
    ashErrors = []
    # ats template code 
    atstemplate = [
        'import flash.display.*;\n',
        'import flash.util.*;\n',
        'var fileName:String ="_";\n', # this line will get replaced with the actual filename
        'this[fileName] = new Array();\n',
        'this[fileName+"Str"] = new Array();\n',
        'this[fileName+"Ans"] = new Array();\n'
        ]
    currentPids = []
    exclude = []
    longOptions = []
    tests = []
    winceProcesses = []
    
    apiVersioning = False
    csv = False
    cygwin = False
    debug = False
    eval = False      # Run the source file (.as, .js) but, do not magically prepend included files
    forcerebuild = False
    genAtsSwfs = False
    htmlOutput = False
    quiet = False
    random = False
    rebuildtests = False
    runSource = False # Run the source file (.as, .js) instead of .abc, magically prepend included files
    show_time = False
    timestampcheck = True
    timestamps = True
    useShell = True
    verbose = False
    verify = False
    writeResultProperties = False   # used by the asc runtests.py to write to a result.properties file used by the asc ant scripts
    
    start_time = None
    testTimeOut = -1 #by default tests will NOT timeout
    threads = 1
    timeout = 0 # in seconds
    timeoutStartTime = 0
    
    lock = threadpool.threading.Lock()  # global lock used when threading
    
    def __init__(self):
        # Result Vars
        self.allpasses=0
        self.allfails=0
        self.allunpass=0
        self.allexpfails=0
        self.allexceptions=0
        self.allskips=0
        self.alltimeouts=0
        self.allasserts=0
        self.failmsgs=[]
        self.expfailmsgs=[]
        self.unpassmsgs=[]
        self.timeoutmsgs=[]
        self.assertmsgs=[]
        self.altsearchpath=None
        
        self.run()        

    def usage(self, c):
        print 'usage: %s [options] [tests]' % basename(argv[0])
        print ' -v --verbose       enable additional output'
        print ' -E --avm           avmplus command to use'
        print ' -a --asc           compiler to use'
        print ' -g --globalabc     DEPRECATED but still works - use builtin.abc (used to be location of global.abc)'
        print ' -b --builtinabc    location of builtin.abc'
        print ' -s --shellabc      location of shell_toplevel.abc'
        print ' -x --exclude       comma separated list of directories to skip'
        print ' -h --help          display help and exit'
        print ' -t --notime        do not generate timestamps (cleaner diffs)'
        print ' -f --forcerebuild  force rebuild all test files'
        print ' -c --config        sets the config string [default OS-tvm]'
        print ' -q --quiet         display minimum output during testrun'
        print '    --rebuildtests  rebuild the tests only - do not run against VM'
        print '    --showtimes     shows the time for each test'
        print '    --ascargs       args to pass to asc on rebuild of test files'
        print '    --vmargs        args to pass to vm'
        print '    --timeout       max time to run all tests'
        print '    --testtimeout   max time to let a test run, in sec (default -1 = never timeout)'
        print '    --html          also create an html output file'
        print '    --notimecheck   do not recompile .abc if timestamp is older than .as'
        print '    --java          location of java executable (default=java)'
        print '    --random        run tests in random order'
        
        

    def setOptions(self):
        '''set the valid command line options.
            When subclassing, call this method first, then append options to each list'''
        self.options = 'vE:a:g:b:s:x:htfc:dq'
        self.longOptions = ['verbose','avm=','asc=','globalabc=','builtinabc=','shellabc=',
                   'exclude=','help','notime','forcerebuild','config=','ascargs=','vmargs=',
                   'timeout=','testtimeout=', 'rebuildtests','quiet','notimecheck',
                   'showtimes','java=','html','random', 'playerglobalabc=', 'toplevelabc=']

    def parseOptions(self):
        try:
            opts, self.args = getopt(argv[1:], self.options, self.longOptions )
        except:
            self.usage(2)
        
        if not self.args:
            self.args = ['.']
        
        for o, v in opts:
            if o in ('-v', '--verbose'):
                self.verbose = True
            elif o in ('-h', '--help'):
                self.usage(0)
            elif o in ('-E', '--avm'):
                self.avm = v
            elif o in ('-a', '--asc'):
                self.asc = v
            elif o in ('-b', '--builtinabc', '-g', '--globalabc'):
                self.builtinabc = v
            elif o in ('-s', '--shellabc', '--toplevelabc'):
                self.shellabc = v
            elif o in ('--playerglobalabc',):
                self.playerglobalabc = v
            elif o in ('-x', '--exclude'):
                self.exclude += v.split(',')
                # remove any trailing /,\ and whitespace from exclude list
                self.exclude = map(lambda s: s.rstrip('\\/ '), self.exclude)
            elif o in ('-t', '--notime'):
                self.timestamps = False
            elif o in ('-f', '--forcerebuild'):
                self.forcerebuild = True
            elif o in ('-c', '--config'):
                self.config = v
            elif o in ('--ascargs',):
                self.ascargs = v
            elif o in ('--vmargs',):
                self.vmargs = v
            elif o in ('--ext',):
                self.sourceExt = v
            elif o in ('--timeout',):
                self.timeout = int(v)
                self.testTimeOut=int(v)
            elif o in ('--testtimeout',):
                self.testTimeOut=int(v)
            elif o in ('-d',):
                self.debug = True
            elif o in ('--rebuildtests',):
                self.rebuildtests = True
            elif o in ('-q', '--quiet'):
                self.quiet = True
            elif o in ('--html',):
                self.htmlOutput = True
            elif o in ('--notimecheck',):
                self.timestampcheck = False
            elif o in ('--showtimes',):
                self.show_time = True
            elif o in ('--java',):
                self.java = v
            elif o in ('--random',):
                self.random = True
            
        return opts
    
    
    ### Config and Settings ###

    def determineConfig(self):
        # ================================================
        # Determine the configruation if it has not been 
        # passed into the script:
        # {CPU_ARCH}-{OS}-{VM}-{VERSION}-{VMSWITCH}
        # ================================================
        
        try:
            # Try and determine CPU architecture of the AVM, if it fails drop back to platform.machine()
            cputype = ''
            (f,err,exitcode) = self.run_pipe('file "%s"' % (self.avm))
            f = ' '.join(f).replace(self.avm, '');
            self.verbose_print('determineConfig: %s' % f)
    
            if re.search('\(console\) 32-bit', f):
                cputype='arm'
                self.osName='winmobile-emulator'
            elif re.search('(Mach-O universal binary)', f):
                # multiple architectures
                machine = platform.machine()
                if re.search('(x86_64|ppc64)',f):
                    if machine == 'Power Macintosh':
                        cputype = 'ppc64'
                    elif machine == 'i386':
                        cputype = 'x64'
                elif re.search('(i386|ppc)',f):
                    if machine == 'Power Macintosh':
                        cputype = 'ppc'
                    elif machine == 'i386':
                        cputype = 'x86'
            # Need to do the SPARC check before the x86 check as the x86 check 
            # will find the "32-bit" string and think that it is x86.
            elif re.search('(SPARC)', f):
                cputype='sparc'
            elif re.search('(ppc64)', f):
                cputype='ppc64'
            elif re.search('(ppc)', f):
                cputype='ppc'
            elif re.search('(mips)', f.lower()):
                cputype='mips'
            elif re.search('(32-bit|80386|i386)', f):
                cputype='x86'
            elif re.search('(64-bit|x86-64|x86_64|Mono/\.Net)', f):
                cputype='x64'
                
            if cputype == '':
                raise Exception()
                
        except:
            try:
                cputype={'AMD64':'x86','x86':'x86','i386':'x86','i686':'x86','x86_64':'x64','i86pc':'x86','Power Macintosh':'ppc','sun4u':'x86','mips':'mips','':'x86'}[platform.machine()]
                if cputype == 'x86' and splitext(self.avm)[0][-2:] == '64':
                    cputype == 'x64'
            except:
                print("ERROR: cpu_arch '%s' is unknown, expected values are (x86,ppc), use runtests.py --config x86-win-tvm-release to manually set the configuration" % (platform.machine()))
                exit(1)
                
        self.vmtype = 'release'
        if self.osName=='winmobile-emulator':
            self.vmtype = 'release'
        elif not self.runSource and not self.rebuildtests:
            (f,err,exitcode) = self.run_pipe('%s' % self.avm)
            # determine avmshell type
            if re.search('debug-debugger',f[1]):
                self.vmtype = 'debugdebugger'
            elif re.search('release-debugger',f[1]):
                self.vmtype = 'releasedebugger'
            elif re.search('debug',f[1]):
                self.vmtype = 'debug'
            elif re.search('release',f[1]):
                self.vmtype = 'release'
            else:   # try to determine vmtype by filename
                vm = splitext(split(self.avm)[1])[0]
                if '_sd' in vm:
                    self.vmtype = 'debugdebugger'
                elif '_s' in vm:
                    self.vmtype = 'releasedebugger'
                elif '_d' in vm:
                    self.vmtype = 'debug'
                else:
                    self.vmtype = 'release'
                
            f = ' '.join(f)
            # determine if api versioning switch is available
            if re.search('(api)', f):
                self.apiVersioning = True
            
        wordcode = '-wordcode' if re.search('wordcode', self.avm) else ''
        
        self.config = cputype+'-'+self.osName+'-tvm-'+self.vmtype+wordcode+self.vmargs.replace(" ", "")
    
    def determineOS(self):
        _os = platform.system()
        ostype = ''
        # When running on a windows system we can either be running with cygwin python
        # or with a windows-native python.  Legacy code requires that ostype be kept
        # as win for the osName, but one can check for the python type by querying
        # the self.cygwin boolean:
        # self.osName='win' and not self.cygwin == windows python
        # self.cygwin = cygwin python
        
        if re.search('(CYGWIN_NT)', _os):
            ostype='win'
            self.cygwin = True
        if re.search('(Windows)', _os):
            ostype='win'
            self.useShell = False
        if re.search('(Darwin)', _os):
            ostype='mac'
        if re.search('(Linux)', _os):
            ostype='lnx'
        if re.search('(SunOS)', _os):
            ostype='sol'
            
        if ostype == '':
            print("ERROR: os %s is unknown, expected values are (win,mac,lnx,sol), use runtests.py --config x86-win-tvm-release to manually set the configuration" % (platform.system()))
            exit(1)
            
        self.osName = ostype

    def loadPropertiesFile(self):
        # yet another way to specify asc,avm,builtinabc ...from a file
        pf = 'runtests.properties'
        if exists(pf):
            self.verbose_print( 'reading properties from %s' % (pf) )
            fd = open(pf,'r')
            for l in fd:
                setting = l.strip().split('=')
                if l.startswith('#') or len(setting) < 2 or len(setting[1]) <= 0:
                    continue
                val = setting[1].strip()
                option = setting[0].split('.')  # see if we have x.y = z
                nm = option[0].strip()
                # check if nm is valid
                if nm in self.__class__.__dict__ and not callable(self.__class__.__dict__[nm]):
                    if len(option) > 1:
                        val = self.__class__.__dict__[nm] + ' ' + val  # concat
                    self.__class__.__dict__[nm] = val
            fd.close()
            
    def setEnvironVars(self):
        if 'ASC' in environ:
            self.asc = environ['ASC'].strip()
        if 'ASCARGS' in environ:
            self.ascargs = environ['ASCARGS'].strip()
        if 'AVM' in environ:
            self.avm = environ['AVM'].strip()
        if 'BUILTINABC' in environ:
            self.builtinabc = environ['BUILTINABC'].strip()
        if 'CONFIG' in environ:
            self.config = environ['CONFIG'].strip()
        if 'CVS' in environ:
            self.exclude = ['CVS'].strip()
        if 'GLOBALABC' in environ:  # deprecated var - users should use BUILTINABC
            self.builtinabc = environ['GLOBALABC'].strip()
        if 'PLAYERGLOBALABC' in environ:
            self.playerglobalabc = environ['PLAYERGLOBALABC'].strip()
        if 'SHELLABC' in environ:
            self.shellabc = environ['SHELLABC'].strip()
        if 'TOPLEVELABC' in environ:    # deprecated var - users should use SHELLABC
            self.shellabc = environ['TOPLEVELABC'].strip()
        if 'VMARGS' in environ:
            self.vmargs = environ['VMARGS'].strip()
        
    ### File and Directory functions ###

    def build_incfiles(self, as_file):
        files=[]
        (dir, file) = split(as_file)
        for p in self.parents(dir):
            shell = join(p,'shell'+self.sourceExt)
            if isfile(shell):
                files.append(shell)
        (testdir, ext) = splitext(as_file)
        if not self.eval:
            for util in glob(join(testdir,'*'+self.sourceExt)) + glob(join(dir,'*Util'+self.sourceExt)):
                files.append(string.replace(util, "$", "\$"))
        return files

    def checkExecutable(self,exe, msg):
        if exe:
            exe = exe.split()[0]    # only check first arg if there are more than one
        if not isfile(exe):
            # exe might be in path - check there
            try:
                if not which.which(exe):
                    exit('ERROR: cannot find %s, %s' % (exe, msg))
            except which.WhichError:
                exit('ERROR: cannot find %s, %s' % (exe, msg))
        if not os.access(exe, os.X_OK):
            # check in path
            try:
                if not os.access(which.which(exe)[0], os.X_OK):
                    try:
                        import stat
                        os.chmod(exe, stat.S_IXUSR)
                    except:
                        exit('ERROR: cannot execute %s, check the executable flag' % exe)
            except which.WhichError:
                exit('ERROR: cannot execute %s, check the executable flag' % exe)

    def checkPath(self,additionalVars=[]):
        '''Check to see if running using windows python and if so, convert any cygwin paths to win paths
            Takes additional variables to check as a list of strings
        '''
        self.determineOS()
        if self.osName == 'win':
            def convertFromCygwin(cygpath):
                if cygpath.find('\\') == -1:
                    try:
                        f = self.run_pipe('cygpath -m %s' % cygpath)
                        cygpath = ' '.join([i.strip() for i in f[0]])
                    except:
                        pass
                return cygpath
            
            selfVarsToCheck = ['avm','asc','builtinabc','shellabc','java']
            selfVarsToCheck.extend(additionalVars)
            for var in selfVarsToCheck:
                setattr(self, var, convertFromCygwin(getattr(self,var)).strip())
                
            newargs = []
            for t in self.args:
                newargs.append(convertFromCygwin(t).strip())
            self.args = newargs
        
        if not self.rebuildtests:
            self.checkExecutable(self.avm, 'AVM environment variable or --avm must be set to avmplus')

    def createOutputFile(self):
        # set the output file name.  let's base its name on the date and platform,
        # and give it a sequence number.
        now = datetime.today()
        for i in count(1):
            self.js_output = '%d-%s-%s.%d.%s' % (now.year, str(now.month).zfill(2), str(now.day).zfill(2), i, self.logFileType)
            if not isfile(self.js_output):
                break
        
        print 'Writing results to %s' % self.js_output
        self.js_output_f = open(self.js_output, 'w')
        
    def getTestsList(self, startDir):
        if self.altsearchpath!=None:
            newstartDir=[]
            for a in startDir:
                newstartDir.append(self.altsearchpath+a)
            startDir=startDir+newstartDir
        for i in range(len(startDir)):
            if startDir[i][-1] == '/':
                startDir[i] = startDir[i][:-1]
        tests = [a for a in startDir if isfile(a) and self.istest(a)]
        for a in [d for d in startDir if isdir(d) and not (basename(d) in self.exclude)]:
            for d, dirs, files in walk(a, followlinks=True):
                if d.startswith('./'):
                    d=d[2:]
                tests += [(d+'/'+f) for f in files if self.istest(f)]
                utils = [d for d in dirs if d+self.sourceExt in files]
                for x in [x for x in self.exclude+utils if x in dirs]:
                    dirs.remove(x)
        return tests

    def getLocalSettings(self, root):
        # get settings for this test - both from root dir testconfig.txt and
        # any testconfig.txt in the current dir
        settings = {}
        dir = os.path.split(root)[0]
        # when more than one filename regexp matches, we choose to use the longest:
        # e.g: given asc/.* and asc/testname - asc/testname will take precedence
        # since it has longer total length
        longestKeyMatch = 0 
        for k in self.settings.keys():
            if re.search('^'+k+'$', root):
                if len(k) > longestKeyMatch:
                    longestKeyMatch = len(k)
                    for k2 in self.settings[k].keys():
                        if k2 in settings:
                            settings[k2].update(self.settings[k][k2])
                        else:
                            settings[k2] = self.settings[k][k2].copy()
        
        if isfile(join(dir,self.testconfig)):
            localSettings, localIncludes = self.parseTestConfig(dir)
            # have a local testconfig, so we create a copy of the global settings to not overwrite
            includes = list(self.includes) #copy list - don't use reference
            includes.extend(localIncludes)
            if localSettings.has_key(root):
                settings.update(localSettings[root])
        return settings
    
    def istest(self,f):
        return f.endswith((self.sourceExt,self.abcasmExt)) and basename(f) != ('shell'+self.sourceExt) \
               and not f.endswith('Util'+self.sourceExt)
        
    def parents(self, d):
        while d != abspath(self.args[0]) and d != '':
            yield d
            d = dirname(d)
        yield d

    def parseTestConfig(self, dir):
        settings={}
        includes=[]
        names=None
        lines=[]
        
        if isfile(join(dir,self.testconfig)):
            if join(dir, '') == './':
                for line in open(join(dir,self.testconfig)).read().splitlines():
                    lines.append(line)
            else:
                # if this is not the root testconfig, append the path before the testname
                for line in open(join(dir,self.testconfig)).read().splitlines():
                    lines.append('%s/%s' %(dir,line))
            for line in lines:
                if line.startswith('#') or len(line)==0:
                    continue
                fields = line.split(',',3)
                for f in range(len(fields)):
                    fields[f]=fields[f].strip()
                while len(fields)<4:
                    fields.append('');
                names=fields[0].split(':')
                if len(names)==1:
                    names.append('.*')
                # remove any trailing extension if specified
                # TODO: add abs to here
                if names[0][-3:] == self.sourceExt:
                    names[0]=names[0][:-3]
                rs='^%s$' % names[0]
                # only add settings for current config
                if re.search('^%s$' % fields[1],self.config):
                    if re.search(fields[1],self.config) and fields[2]=='include':
                        includes.append(fields[0])
                    if not settings.has_key(names[0]):
                        settings[names[0]] = {}
                    if not settings[names[0]].has_key(names[1]):
                        settings[names[0]][names[1]] = {}
                    settings[names[0]][names[1]][fields[2]]=fields[3]
        return settings, includes
    
    ### Output / Printing functions ###
    
    def err_print(self, m):
        self.js_print(m, '<font color=#990000>', '</font><br/>')

    def fail(self, abc, msg, failmsgs):
        msg = msg.strip()
        self.err_print('   %s' % msg)
        failmsgs += ['%s : %s' % (abc, msg)]
        
    def js_print(self, m, start_tag='<p><tt>', end_tag='</tt></p>', overrideQuiet=False, csv=True, csvOut=True):
        # Print output
        # csv - if True and if outputting csv, convert line into csv (spaces and []: chars)
        # csvOut - if False and if outputing csv, do not print out this line
        if self.quiet and not overrideQuiet:
            sys.stdout.write('.')
        elif self.csv:
            if csvOut:
                if csv:
                    print convertToCsv(m)
                else:
                    if m.find(',') != -1:
                        m = '"%s"' % m
                    print m
        else:
            print m
            sys.stdout.flush()
        if self.js_output:
            if self.logFileType == 'html':
                self.js_output_f.write('%s %s %s\n' % (start_tag, m, end_tag))
            else:
                self.js_output_f.write('%s\n' % m)
            self.js_output_f.flush()

    def printOutput(self,request, outputCalls=None):
        #execute the outputCalls
        if outputCalls:
            for call in outputCalls:
                apply(call[0],call[1])
    
    def quiet_print(self, m, start=None, end=None):
        if self.quiet:
            sys.stdout.write('.')
        else:
            if not start and not end:
                self.js_print(m)
            else:
                self.js_print(m, start, end)
                
    def verbose_print(self, m, start='', end=''):
      if self.verbose:
        self.js_print(m, start, end)
    

    ### ASC / Compiling Functions ###
    
    def compile_test(self, as_file, extraArgs=[]):
        asc, builtinabc, shellabc, ascargs = self.asc, self.builtinabc, self.shellabc, self.ascargs
        # if there is a .build file available (which is an executable script) run that file instead
        # of compiling with asc
        as_base = as_file[0:as_file.rfind('.')]
        if isfile(as_base+'.build'):
            (dir,file)=split(as_base)
            self.verbose_print('    compiling %s running %s%s' % (file, as_base, '.build'))
            (f,err,exitcode) = self.run_pipe('%s%s' % (as_base, '.build'))
            for line in f:
                self.verbose_print(line.strip())
            for line in err:
                self.verbose_print(line.strip())
            return

        if not isfile(asc):
            exit('ERROR: cannot build %s, ASC environment variable or --asc must be set to asc.jar' % as_file)
           
        (dir, file) = split(as_file)
        self.verbose_print('   compiling %s' % file)
        
        if self.genAtsSwfs:
            # get settings as ats excluded files are defined there
            settings = self.getLocalSettings(as_file)
            if settings.has_key('.*') and settings['.*'].has_key('ats_skip'):
                self.js_print('ATS Skipping %s ... reason: %s' % (file,settings['.*']['ats_skip']))
                return
    
        # additional .as file compiler args
        if as_file.endswith(self.sourceExt):
            if not isfile(builtinabc):
                exit('ERROR: builtin.abc (formerly global.abc) %s does not exist, BUILTINABC environment variable or --builtinabc must be set to builtin.abc' % builtinabc)
        
            if asc.endswith('.jar'):
                cmd = '"%s" -jar %s' % (self.java,asc)
            else:
                cmd = asc
            
            arglist = parseArgStringToList(ascargs)
        
            # look for .asc_args files to specify dir / file level compile args, arglist is passed by ref
            arglist = self.loadAscArgs(arglist, dir, as_file)
            
            (testdir, ext) = splitext(as_file)
            
            if self.genAtsSwfs:
                arglist.extend(genAtsArgs(dir,file,self.atstemplate))
            
            for arg in extraArgs:
                cmd += ' %s' % arg
        
                                  
            cmd += ' -import %s' % builtinabc
            for arg in arglist:
                cmd += ' %s' % arg
            
            for p in self.parents(dir):
                if p=='':
                    p='.'
                shell = join(p,'shell'+self.sourceExt)
                if isfile(shell):
                    cmd += ' -in ' + shell
                    break
            
            deps = glob(join(testdir,'*'+self.sourceExt))
            deps.sort()
            for util in deps + glob(join(dir,'*Util'+self.sourceExt)):
                if self.osName == 'win' and not self.cygwin:
                    # don't escape $ when running windows python
                    cmd += ' -in %s' % util 
                else:
                    cmd += ' -in %s' % string.replace(util, '$', '\$')
                
        elif as_file.endswith(self.abcasmExt):
            cmd = '%s -j "%s" ' % (self.abcasmRunner,self.java)
            
        try:
            self.verbose_print('%s %s' % (cmd,as_file))
            (f,err,exitcode) = self.run_pipe('%s %s' % (cmd,as_file))
            for line in f:
                self.verbose_print(line.strip())
            for line in err:
                self.verbose_print(line.strip())
            
            if self.genAtsSwfs:
                moveAtsSwf(dir,file, self.atsDir)
            
            return f+err
        except:
            raise
    
    def compileWithAsh(self, tests):
        start_time = datetime.today()
        #print("starting compile of %d tests at %s" % (len(tests),start_time))
        total=len(tests)
        if not pexpect:
            if self.genAtsSwfs:
                print 'The pexpect module must be installed to generate ats swfs.'
                exit(1)
            for test in tests:
                self.js_print('%d\tcompiling %s' % (total,test))
                self.compile_test(test)
                (testdir, ext) = splitext(test)
                if exists(testdir+".abc")==False:
                    print("ERROR abc files %s.abc not created" % (testdir))
                    self.ashErrors.append("abc files %s.abc not created" % (testdir))
                total -= 1;
        else:  #pexpect available
            child = pexpect.spawn('"%s" -classpath %s macromedia.asc.embedding.Shell' % (self.java,self.asc))
            child.logfile = None
            child.expect("\(ash\)")
            child.expect("\(ash\)")
    
            for test in tests:
                if test.endswith(self.abcasmExt):
                    self.compile_test(test)
                else:
                    arglist = parseArgStringToList(self.ascargs)
                
                    (dir, file) = split(test)
                    (testdir, ext) = splitext(test)
                    
                    # look for .asc_args files to specify dir / file level compile args
                    arglist = self.loadAscArgs(arglist, dir, test)
                    
                    if self.genAtsSwfs:
                        # get settings as ats excluded files are defined there
                        settings = self.getLocalSettings(testdir)
                        if settings.has_key('.*') and settings['.*'].has_key('ats_skip'):
                            self.js_print('ATS Skipping %s ... reason: %s' % (test,settings['.*']['ats_skip']))
                            continue
                        arglist.extend(genAtsArgs(dir,file,self.atstemplate))
                    
                    cmd = "asc -import %s " % (self.builtinabc)
                    for arg in arglist:
                        cmd += ' %s' % arg
                    
                    for p in self.parents(dir):
                        if p=='':
                            p='.'
                        shell = join(p,"shell.as")
                        if isfile(shell):
                            cmd += " -in " + shell
                            break
                    
                    deps = glob(join(testdir,"*.as"))
                    deps.sort()
                    for util in deps + glob(join(dir,"*Util.as")):
                        cmd += " -in %s" % util #no need to prepend \ to $ when using ash
                    cmd += " %s" % test
                    
                    if self.debug:
                        self.js_print(cmd)
                    else:
                        self.js_print("Compiling %s" % test)
                    
                    if exists(testdir+".abc"):
                        os.unlink(testdir+".abc")
                    child.sendline(cmd)
                    child.expect("\(ash\)")
                    if not exists(testdir+".abc"):
                        print("ERROR: abc file %s.abc not created, cmd used to compile: %s" % (testdir,cmd))
                        self.ashErrors.append("abc file %s.abc not created, cmd used to compile: %s" % (testdir,cmd))
                    total -= 1;
                    
                    if self.genAtsSwfs:
                        moveAtsSwf(dir,file, self.atsDir)
                    
                    #print("%d remaining, %s" % (total,cmd))
        end_time = datetime.today() 
    
    def loadAscArgs(self, arglist,dir,file):
        # It is possible that file is actually a partial path rooted to acceptance,
        # so make sure that we are only dealing with the actual filename
        file = split(file)[1]
        
        # Loads an asc_args file and modifies arglist accordingly
        if isfile('./dir.asc_args'):  # load root dir.asc_args
            arglist = self.parseAscArgs(arglist, './dir.asc_args', './')
            
        if isfile(dir+'/dir.asc_args'):  # dir takes precedence over root
            arglist = self.parseAscArgs(arglist, dir+'/dir.asc_args', dir)

        if file and isfile('%s/%s.asc_args' % (dir, file)):  # file takes precendence over directory
            arglist = self.parseAscArgs(arglist, '%s/%s.asc_args' % (dir, file), dir)

        return arglist
    
    
    def parseAscArgs(self, currentArgList, ascArgFile, currentdir):
        # reads an .asc_args file and returns a tuple of the arg mode (override or merge) and a list of args
        f = open(ascArgFile,'r')
        while True: # skip comment lines
            ascargs = f.readline()
            if (ascargs[0] != '#'):
                break
        ascargs = ascargs.split('|')
        ascargs[0] = ascargs[0].strip()
        if (len(ascargs) == 1): #treat no keyword as a merge
            ascargs.insert(0,'merge')
        elif (ascargs[0] != 'override') or (ascargs[0] != 'merge'): # default to merge if mode not recognized
            ascargs[0] = 'merge'
        # replace the $DIR keyword with actual directory
        ascargs[1] = string.replace(ascargs[1], '$DIR', currentdir)
        if ascargs[1].find('$SHELLABC') != -1:  
            if not isfile(self.shellabc):   # TODO: not the best place to check for this
                exit('ERROR: shell.abc %s does not exist, SHELLABC environment variable or --shellabc must be set to shell_toplevel.abc' % self.shellabc)
            ascargs[1] = string.replace(ascargs[1], '$SHELLABC', self.shellabc)
        ascargs[1] = parseArgStringToList(ascargs[1])
        removeArgList = []
        argList = []
        for a in ascargs[1]:
            if a[0:3] == '-no':
                removeArgList.append(a[3:])
            else:
                argList.append(a)
        
        mode = ascargs[0]
        if mode == 'merge':
            currentArgList.extend(argList)
        elif mode == 'override':
            currentArgList = newArgList
        # remove any duplicate args
        currentArgList = list(set(currentArgList))
        if removeArgList:
            for removeArg in removeArgList:
                try:
                    currentArgList.remove(removeArg)
                except:
                    pass
                
        return currentArgList
    
    
    def rebuildTests(self):
        if self.genAtsSwfs:
            if not exists(self.atsDir):
                os.mkdir(self.atsDir)
    
        if self.threads == 1 or platform.system()[:6].upper() == 'CYGWIN':
            self.compileWithAsh(self.tests)
        else: # run using threads
            # split tests into number of threads
            testGroups = splitList(self.tests, self.threads)
            
            # generate threadpool
            requests = threadpool.makeRequests(self.compileWithAsh, testGroups, self.printOutput)
            main = threadpool.ThreadPool(self.threads)
            # que requests
            [main.putRequest(req) for req in requests]
            
            # ...and wait for the results to arrive in the result queue
            # wait() will return when results for all work requests have arrived
            
            try:
              main.wait()
            except (TimeOutException, KeyboardInterrupt):
                main.dismissWorkers(self.threads)
                self.killCurrentPids()
                self.lock.acquire()
                self.cleanup()
                exit(0)
            except SystemExit, e:
                main.dismissWorkers(self.threads)
                self.killCurrentPids()
                self.lock.acquire()
                print e
                exit(0)
        
        if self.genAtsSwfs:
            try:
                os.remove('./ats_temp.as')
            except:
                pass  
    
    
    
    ### Process Management ###  
    
    def killCurrentPids(self):
        # Kill all pids in the self.currentPids list
        self.lock.acquire()
        try:
            for p in self.currentPids:
                try:
                    p.kill()
                except:
                    pass
        finally:
            self.lock.release()
    
    def run_pipe(self, cmd):
        # run a command and return a tuple of (output, stdErr, exitCode) 
        if self.debug:
            print('cmd: %s' % cmd)
        self.verbose_print('executing: %s' % cmd)
        try:
            self.lock.acquire()
            try:
                p = Popen((cmd), shell=self.useShell, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                self.currentPids.append(p)
            finally:
                self.lock.release()
            
            starttime=time()
            (output, err) = p.communicate()
            output = output.split('\n') if output else []
            if output and output[-1].strip() == '': # strip empty line at end
                output = output[:-1]
            err = err.split('\n') if err else []
            if err and err[-1].strip() == '':
                err = err[:-1]
            if self.debug:
                print('output: %s' % output)
                print('err: %s' % err)
            exitCode = p.returncode
            
            if exitCode < 0 and self.testTimeOut>-1 and time()-starttime>self.testTimeOut:  # process timed out
                return ('', err, exitCode)

            self.lock.acquire()
            try:
                self.currentPids.remove(p)
            finally:
                self.lock.release()

            return (output,err,exitCode)
        except KeyboardInterrupt:
            self.killCurrentPids()
            
    ### Run Tests ###
    
    def preProcessTests(self):  # don't need AVM if rebuilding tests
        self.js_print('current configuration: %s' % self.config, overrideQuiet=True)
        self.js_print('Executing %d tests against vm: %s' % (len(self.tests), self.avm), overrideQuiet=True);


    def runTests(self, testList):
        testnum = len(testList)
        if self.random:
            random.shuffle(testList)
            
        if self.verify:
            if not re.search('debug', self.config):
                print 'Avm Debugger build must be used when running --verify'
                sys.exit(1)
            if not isfile(self.abcdump+'.abc'): # check that abcdump.abc is built
                self.run_pipe('"%s" -jar %s -import %s -import %s %s' % (self.java, self.asc, self.builtinabc, self.shellabc, self.abcdump+'.as'))
        
        if self.timeout:
            self.js_print("will run tests until timeout of %ds is exceeded" % self.timeout)
            self.timeoutStartTime = time()
        
        # threads on cygwin randomly lock up
        if self.threads == 1 or platform.system()[:6].upper() == 'CYGWIN':
            for t in testList:
                testnum -= 1
                o = self.runTestPrep((t, testnum))
                self.printOutput(None, o)
                if self.timeout and time()-self.timeoutStartTime > self.timeout:
                    break
        else: # run using threads
            #Assign test numbers
            testsTuples = []
            testsLen = len(testList)
            for i,t in enumerate(testList):
              testsTuples.append([t,testsLen-i])
            # generate threadpool
            requests = threadpool.makeRequests(self.runTestPrep, testsTuples, self.printOutput, self.handle_exception)
            main = threadpool.ThreadPool(self.threads)
            # que requests
            [main.putRequest(req) for req in requests]
            
            try:
                while True:
                    try:
                        sleep(1)
                        main.poll()
                        if self.timeout and time()-self.timeoutStartTime > self.timeout:
                            raise TimeOutException
                        #print "(active worker threads: %i)" % (threadpool.threading.activeCount()-1, )
                    except threadpool.NoResultsPending:
                        break
                if main.dismissedWorkers:
                    main.joinAllDismissedWorkers()
            except (TimeOutException, KeyboardInterrupt):
                main.dismissWorkers(self.threads)
                self.killCurrentPids()
                self.lock.acquire()
                self.cleanup()
                exit(0)
            except SystemExit, e:
                main.dismissWorkers(self.threads)
                self.killCurrentPids()
                self.lock.acquire()
                print e
                exit(0)
    
    #
    # cleanup
    #
    def cleanup(self):
        # Turn off quiet to display summary
        if self.quiet:
            self.quiet = False
        
        if self.failmsgs:
            self.js_print('\nFAILURES:', '', '<br/>')
            for m in self.failmsgs:
                self.js_print('  %s' % m, '', '<br/>')
        
        if self.expfailmsgs:
            self.js_print('\nEXPECTED FAILURES:', '', '<br/>')
            for m in self.expfailmsgs:
                self.js_print('  %s' % m, '', '<br/>')
        
        if self.unpassmsgs:
            self.js_print('\nUNEXPECTED PASSES:', '', '<br/>')
            for m in self.unpassmsgs:
                self.js_print('  %s' % m, '', '<br/>')
    
        if self.assertmsgs:
            self.js_print('\nASSERTIONS:', '', '<br/>')
            for m in self.assertmsgs:
                self.js_print('  %s' % m, '', '<br/>')
        
        if self.rebuildtests:
            if self.ashErrors:
                self.js_print('\ntest run FAILED!')
                self.js_print('')
                self.js_print('Compile Errors:')
                for msg in self.ashErrors:
                    self.js_print('\t'+msg)
                self.js_print('')
            else:
                self.js_print('\ntest run PASSED!')
        else:
            if not self.allfails and not self.allunpass:
                self.js_print('\ntest run PASSED!')
            else:
                self.js_print('\ntest run FAILED!')
        
        if self.timestamps:
            end_time = datetime.today()
            self.js_print('Tests complete at %s' % end_time, '<hr><tt>', '</tt>')
            self.js_print('Start Date: %s' % self.start_time, '<tt><br>', '')
            self.js_print('End Date  : %s' % end_time, '<br>', '')
            self.js_print('Test Time : %s' % (end_time-self.start_time), '<br>', '')
            
        if not self.rebuildtests:
            self.js_print('passes               : %d' % self.allpasses, '<br>', '')
            self.js_print('failures             : %d' % self.allfails, '<br>', '')
            if self.allunpass>0:
                self.js_print('unexpected passes    : %d' % self.allunpass, '<br>', '')
            if self.allexpfails>0:
                self.js_print('expected failures    : %d' % self.allexpfails, '<br>', '')
            if self.allskips>0:
                self.js_print('tests skipped        : %d' % self.allskips, '<br>', '')
            if self.allexceptions>0:
                self.js_print('test exceptions      : %d' % self.allexceptions, '<br>', '')
            if self.alltimeouts>0:
                self.js_print('test timeouts        : %d' % self.alltimeouts, '<br>', '')
            if self.allasserts>0:
                self.js_print('assertions           : %d' % self.allasserts, '<br>', '')
                
            if self.js_output:
                print 'Results were written to %s' % self.js_output

        if self.writeResultProperties:
            logfile = open('result.properties', 'w')
            if self.allfails>0:
              logfile.write("failures=%d" % self.allfails)
            else:
              logfile.write("no failures")  

        if self.ashErrors:
            exit(1)

    ### Misc Functions ###

    def compareAbcAsmOutput(self, file, output):
        # return diff
        try:
            f = open(file[:-4]+'.out', 'r')
            if self.config.find('debugger') != -1:
                if isfile(file[:-4]+'.out.debug'):
                    f.close()
                    f = open(file[:-4]+'.out.debug', 'r')
            if self.config.find('interp') != -1:
                if isfile(file[:-4]+'.out.interp'):
                    f.close()
                    f = open(file[:-4]+'.out.interp', 'r')
            flines = []
            for line in f.readlines():
                line = ''.join(line.split('\r'))
                if line != '\n':
                    flines.append(line)
            f.close()
        except IOError:
            flines = ['IOError Opening .out file']
        if len(output) != len(flines):
            return flines
        # compare lines
        for i in range(0,len(output)):
            line=output[i].strip()
            line=line.replace('\\','/')
            if line != flines[i].strip():
                return flines
        return

    # this will be called when an exception occurs within a thread
    def handle_exception(self, request, exc_info):
        raise exc_info[1]

    def setTimestamp(self):
        if self.timestamps:
            # get the start time
            self.start_time = datetime.today()
            self.js_print('Tamarin tests started: %s' % self.start_time, overrideQuiet=True, csv=False)


    def setupCEEmulators(self):
        # runs the windows mobile emulators
        # * for each threads (--numthreads=) start an emulator with emulator $EMULATOR and image $EMULATORIMAGE environment variables or use defaults below
        # * in emulator map shared directory to local machine, the shared directory gets mapped to /Storage Card on the device
        # * in shared directory /2755/autorun.exe will autorun when emulator is started
        # * copy the wmrunner.exe program as autorun.exe
        # * the wm tamarin shell is copied to /Storage Card/shell/avmshell_arm.exe
        # * the /Storage Card/nextvm.txt contains the parameters and abc file to compile
        # * /Storage Card/media is where .abc files are stored
        # * the wmrunner.exe runs in windows mobile looking for nextvm.txt, runs the avmplus_arm.exe with the arguments in the file
        # * when -log is a vm parameter the result of running the abc will be in a .log file
        # * the avm variable is replaced with the ../util/wmemulatorshell.py file, when called it copies the test abc to the wm /Storage Card/media
        #   directory and creates nextvm.txt, then waits for the wmrunner.exe to delete the nextvm.txt to signal the test is finished
        #
        
        emulator="c:/Program Files/Microsoft Device Emulator/1.0/DeviceEmulator.exe"
        emulator_image="c:/Program Files/Windows Mobile 6 SDK/PocketPC/DeviceemulationV650/0409/PPC_USA_GSM_VR.BIN"
        cwd=os.getcwd()
        # fixes for changing cygwin style paths into DOS
        if len(cwd)>9 and cwd[0:9]=='/cygdrive':
            cwd=cwd[9:]
        if cwd[0]=='/':
            cwd=cwd[1:]
        if cwd[1]!=':':
            cwd=cwd[0:1]+':'+cwd[1:]
        
        shared=cwd+"/../util/emulator_files"
        cerunner=cwd+"/../../utils/wmremote/wmrunner/Release/wmrunner.exe"
        emthreads=self.threads
        emulator_args="/memsize 128"

        if 'EMULATORTHREADS' in os.environ:
            try:
                emthreads=int(os.environ['EMULATORTHREADS'].strip())
            except:
                emthreads=self.threads
        if 'EMULATOR' in os.environ:
            emulator=os.environ['EMULATOR'].strip()
        if 'EMULATORIMAGE' in os.environ:
            emulator_image=os.environ['EMULATORIMAGE'].strip()
        if 'CERUNNER' in os.environ:
            cerunner=os.environ['CERUNNER'].strip()
        if 'EMULATORDIR' in os.environ:
            shared=os.environ['EMULATORDIR'].strip()
        if 'EMULATORARGS' in os.environ:
            emulator_args=os.environ['EMULATORARGS'].strip()

        if self.avm==None or os.path.isfile(self.avm)==False:
            print 'ERROR: AVM must be set and point to the avmshell_arm.exe shell'
            sys.exit(1)
        if os.path.isfile(emulator)==False:
            print "ERROR: device emulator does not exist '%s', set EMULATOR environment variable to the correct emulator" % emulator
            sys.exit(1)
        if os.path.isfile(emulator_image)==False:
            print "ERROR: device emulator image does not exist, '%s', set EMULATORIMAGE environment variable to the correct emulator image" % emulator_image
            sys.exit(1)
        if os.path.isfile(cerunner)==False:
            print "ERROR: cerunner tool does not exist '%s', set CERUNNER environment variable to the correct path to cerunner.exe" % cerunner
            sys.exit(1)
        if os.path.isdir(shared)==False:
            os.mkdir(shared)

        self.avmce=self.avm
        if os.environ.has_key('PYTHONWIN'):
            self.avm=os.environ['PYTHONWIN']+"  "+cwd+"/../util/wmemulatorshell.py"
        else:
            self.avm=cwd+"/../util/wmemulatorshell.py"
        # create and build version.as
        versionabc=cwd+"/version.abc"
        versionfile=open(cwd+"/version.as",'w')
        versionfile.write('import avmplus.*; print(System.getAvmplusVersion());\n')
        versionfile.close()
        self.compile_test(cwd+'/version.as')
        if os.path.isfile(versionabc)==False:
            print "ERROR: compiling %s/version.as" % cwd
            sys.exit(1)
        if os.path.isdir(shared)==False:
            os.mkdir(shared)
        if len(os.listdir(shared))>self.threads:
            print "ERROR: emulator directory '%s' must be removed before running tests" % shared
            sys.exit(1)

        for num in range(emthreads):
            sharedir="%s/share%d" %(shared,num)
            if os.path.isdir(sharedir)==False:
                os.mkdir(sharedir)
            if os.path.isfile(sharedir+'/lock'):
                print "WARNING: the emulator has an open lock file, removing it"
                os.unlink(sharedir+"/lock")
            if os.path.isfile(sharedir+'/running.txt'):
                print "detected emulator is already running, if not delete %s/running.txt" % sharedir 
            if os.path.isdir(sharedir+"/shell")==False:
                os.mkdir(sharedir+"/shell")
            if os.path.isdir(sharedir+"/media")==False:
                os.mkdir(sharedir+"/media")
            # 2577 is the windows mobile autorun directory
            if os.path.isdir(sharedir+"/2577")==False:
                os.mkdir(sharedir+"/2577")
                shutil.copy(cerunner,sharedir+"/2577/autorun.exe")
                shutil.copy(versionabc,sharedir+"/media/version.abc")
            shutil.copy(self.avmce,sharedir+"/shell/avmshell_arm.exe")
            file=open(sharedir+"/nextvm.txt","w")
            file.write(" -log \"\\Storage Card\\media\\version.abc\" ")
            file.close()
        
        winceProcesses=range(emthreads)
        for num in range(emthreads):
            if os.path.isfile("%s/share%d/running.txt" % (shared,num)):
                winceProcesses[num]="manual"
            else:
                args=[emulator]+emulator_args.split()+['/sharedfolder','%s/share%d' %(shared,num),emulator_image]
                winceProcesses[num]=subprocess.Popen(args)
        
        versions=range(emthreads)
        timestart=time()
        while len(versions)>0:
            for i in range(emthreads):
                versionfile="%s/share%d/media/version.log" % (shared,i)
                nextfile="%s/share%d/nextvm.txt" % (shared,i)
                if i in versions and os.path.isfile(nextfile)==False:
                    versions.remove(i)
                    try:
                        f=open(versionfile,"r")
                        data=f.read().strip()
                        f.close()
                    except:
                        data='unknown'
                    print " emulator %d shell version => %s" % (i,data)
            if time()-timestart>60*5:
                print "ERROR: emulators %s did not start after 5 minutes" % versions
                print "I'm guessing deleting the files '%s/share?/running.txt' will fix the problem" % (shared)
                sys.exit(1)
            sleep(.1)
        # cleanup version.as and version.abc
        try:
            if exists(cwd+"/version.as"):
                os.unlink(cwd+"/version.as")
            if exists(cwd+"/version.abc"):
                os.unlink(cwd+"/version.abc")
        except:
            print 'exception deleting %s/version.as or %s/version.abc' % (cwd,cwd)
            
