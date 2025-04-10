#!/usr/bin/env python
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

import os, sys, getopt, datetime, pipes, glob, itertools, tempfile, string, re, platform
from os.path import *
from os import getcwd,environ,walk
from datetime import datetime
from glob import glob
from sys import argv, exit
from getopt import getopt
from itertools import count
from time import time

# add parent dir to python module search path
sys.path.append('..')

try:
    from util.runtestBase import RuntestBase
    # runtestUtils must be imported after "from os.path import *" as walk is overridden
    from util.runtestUtils import *
except ImportError:
    print "Import error.  Please make sure that the test/acceptance/util directory has been deleted."
    print "   (directory has been moved to test/util)."

class AcceptanceRuntest(RuntestBase):
    runESC = False
    escbin = '../../esc/bin/'
    

    def __init__(self):
        # Set threads to # of available cpus/cores
        self.threads = detectCPUs()
        RuntestBase.__init__(self)

    def setEnvironVars(self):
        RuntestBase.setEnvironVars(self)
        if 'ESCBIN' in environ:
            self.escbin = environ['ESCBIN'].strip()
        
    def usage(self, c):
        RuntestBase.usage(self, c)
        print '    --esc           run esc instead of avm'
        print '    --escbin        location of esc/bin directory - defaults to ../../esc/bin'
        print '    --eval          use run-time compiler'
        print '    --ext           set the testfile extension (defaults to .as)'
        print '    --ats           generate ats swfs instead of running tests'
        print '    --atsdir        base output directory for ats swfs - defaults to ATS_SWFS'
        print '    --threads       number of threads to run (default=# of cpu/cores), set to 1 to have tests finish sequentially'
        print '    --verify        run a verify pass instead of running abcs'
        exit(c)
    
    def setOptions(self):
        RuntestBase.setOptions(self)
        self.longOptions.extend(['ext=','esc','escbin=','eval','threads=','ats','atsdir=','verify'])
    
    def parseOptions(self):
        opts = RuntestBase.parseOptions(self)
        for o, v in opts:
            if o in ('--ext',):
                self.sourceExt = v
            elif o in ('--esc',):
                self.runESC = True
            elif o in ('--escbin',):
                self.escbin = v
            elif o in ('--eval',):
                self.eval = True
            elif o in ('--threads',):
                self.threads=int(v)
            elif o in ('--ats',):
                self.genAtsSwfs = True
                self.rebuildtests = True
            elif o in ('--atsdir',):
                self.atsDir = v
            elif o in ('--verify',):
                self.verify = True
                self.vmargs = '-Dverifyall -Dverbose=verify'
                
    def run(self):
        self.setEnvironVars()
        self.loadPropertiesFile()
        self.setOptions()
        self.parseOptions()
        self.setTimestamp()
        self.checkPath()
        if not self.config:
            self.determineConfig()
        if self.rebuildtests==False and (re.search('arm-winmobile-emulator',self.config)!=None or self.osName=='winmobile'):
            if re.search('^arm-winmobile-emulator',self.config)==None:
                print 'ERROR: to use windows mobile build set --config arm-winmobile-emulator-tvm-release or install cygwin utility /usr/bin/file.exe'
                sys.exit(1)
            self.setupCEEmulators()
        if self.htmlOutput and not self.rebuildtests:
            self.createOutputFile()
        self.tests = self.getTestsList(self.args)
        # Load the root testconfig file
        self.settings, self.includes = self.parseTestConfig('.')
        self.preProcessTests()
        if self.rebuildtests:
            self.rebuildTests()
        else:
            self.runTests(self.tests)
        self.cleanup()

    def preProcessTests(self):
        RuntestBase.preProcessTests(self)
        # Are we running esc - depends on a valid avm
        if self.runESC:
            self.runSource = True
            # generate the executable cmd for esc
            #escAbcs = [f for f in os.listdir(self.escbin) if f.endswith('.abc')] #not all abcs are used for esc
            escAbcs = ['debug','util','bytes-tamarin','util-tamarin','lex-char','lex-token',
                       'lex-scan','ast','ast-decode','parse','asm','abc','emit','cogen',
                       'cogen-stmt','cogen-expr','esc-core','eval-support','esc-env','main']
            if not self.escbin.endswith('/'):
                self.escbin += '/'
            for f in escAbcs:
                self.avm += ' %s%s.es.abc' % (self.escbin, f)
            self.avm += ' -- '
            self.avm += ' %s../test/spidermonkey-prefix.es' % self.escbin  #needed to run shell harness

    def runTestPrep(self, testAndNum):
        ast = testAndNum[0]
        testnum = testAndNum[1]
        outputCalls = [] #queue all output calls so that output is written in a block
        lpass = 0
        lfail = 0
        lexpfail = 0
        lunpass = 0
        ltimeout = 0
        lassert = 0
        extraVmArgs = ''
        abcargs = ''
        
        dir = os.path.split(ast)[0]
        root,ext = splitext(ast)
        if self.runSource or self.eval:
            testName = ast
        else:
            testName = root + '.abc'
            
        includes = self.includes #list
        
        settings = self.getLocalSettings(root)
        
        #TODO: possibly handle includes by building test list?  This works for now...
        if includes and not list_match(includes,root):
            return
        
        # skip tests that can't be verified
        if self.verify and settings.has_key('.*') and settings['.*'].has_key('verify_skip'):
            outputCalls.append((self.js_print,('%d running %s' % (testnum, ast), '<b>', '</b><br/>')));
            outputCalls.append((self.js_print,('  skipping... reason: %s' % settings['.*']['verify_skip'],)))
            self.allskips += 1
            return outputCalls
        
        # skip entire test if specified
        if settings.has_key('.*') and settings['.*'].has_key('skip'):
            outputCalls.append((self.js_print,('  skipping... reason: %s' % settings['.*']['skip'],)))
            self.allskips += 1
            outputCalls.insert(0,(self.js_print,('%d running %s' % (testnum, ast), '<b>', '</b><br/>')));
            return outputCalls
        
        # skip apiversioning tests if api versioning not enabled
        if not self.apiVersioning and settings.has_key('.*') and settings['.*'].has_key('apiversioning'):
            outputCalls.append((self.js_print,('  skipping... reason: apiversioning not enabled',)))
            self.allskips += 1
            outputCalls.insert(0,(self.js_print,('%d running %s' % (testnum, ast), '<b>', '</b><br/>')));
            return outputCalls
        
        # delete abc if forcerebuild
        if self.forcerebuild and isfile(testName):
            os.unlink(testName)
        if isfile(testName) and getmtime(ast)>getmtime(testName) and self.timestampcheck:
            self.verbose_print("%s has been modified, recompiling" % ast)
            os.unlink(testName)
        if not isfile(testName):
            compileOutput = self.compile_test(ast)
            if not isfile(testName):
                if ast.endswith(self.abcasmExt):
                    # file didn't compile, compare compile output
                    flines = self.compareAbcAsmOutput(ast, compileOutput)
                    if flines:
                        lfail += 1
                        outputCalls.append((self.fail,(testName, 'FAILED! :\nExpected:\n'+''.join(flines)+'\nGOT:\n'+''.join(compileOutput), self.failmsgs)))
                        outputCalls.append((self.js_print, ('   FAILED passes:%d fails:%d unexpected passes: %d expected failures: %d' % (lpass,lfail,lunpass,lexpfail), '', '<br/>')))
                    else:
                        lpass += 1
                        outputCalls.append((self.verbose_print, ('   PASSED passes:%d fails:%d unexpected passes: %d expected failures: %d' % (lpass,lfail,lunpass,lexpfail), '', '<br/>')))
                    outputCalls.insert(0,(self.js_print,('%d running %s' % (testnum, ast), '<b>', '</b><br/>')));
                    self.allfails += lfail
                    self.allpasses += lpass
                    return outputCalls
                else:
                    lfail += 1
                    outputCalls.append((self.fail,(testName, 'FAILED! file not found ' + testName, self.failmsgs)))
        
        self.allfails += lfail
        self.allpasses += lpass
        
        if self.runSource or self.eval:
            incfiles=self.build_incfiles(testName)
            incfiles.append("shell" + self.sourceExt)
            for incfile in incfiles:
                testName=incfile+" "+testName
        
        # read any extra avm arguments, each line will execute the avm with those args
        if isfile('%s.avm_args' % ast):
            avm_args_file = open('%s.avm_args' % ast,'r')
            index = 0
            for line in avm_args_file:
                line = line.strip()
                if line.startswith('#'):
                    continue
                index += 1
                line = string.replace(line, "$DIR", dir)
                if line.find('--') != -1:
                    (extraVmArgs, abcargs) = line.split('--')
                else:
                    extraVmArgs = line
                outputCalls.extend(self.runTest(ast, root, testName, '%s.%s' % (testnum, index), settings, extraVmArgs, abcargs))
        else:
            outputCalls.extend(self.runTest(ast, root, testName, testnum, settings))
        
        return outputCalls
        
    def runTest(self, ast, root, testName, testnum, settings, extraVmArgs='', abcargs=''):
        outputCalls = []
        lpass = 0
        lfail = 0
        lexpfail = 0
        lunpass = 0
        ltimeout = 0
        lassert = 0
        starttime=time()
        
        if ast.endswith(self.abcasmExt):
            # make sure util file has been compiled
            if not exists(self.abcasmShell+'.abc'):  # compile abcasmShell with no additional args
                self.run_pipe('"%s" -jar %s %s' % (self.java, self.asc, self.abcasmShell+'.as'))
            (f,err,exitcode) = self.run_pipe('%s %s %s %s %s' % (self.avm, self.vmargs, extraVmArgs, self.abcasmShell+'.abc', testName))
        elif self.verify:
            # get the abcdump for the file
            (f,err,exitcode) = self.run_pipe('%s %s -- %s' % (self.avm, self.abcdump+'.abc', testName))
            abcdumpFunctions = [line.strip() for line in f if line.startswith('var function')]
            if self.verbose:
                outputCalls.append((self.js_print,(abcdumpFunctions,)))
            # get -Dverifyall -Dverbose=verify output
            (f,err,exitcode) = self.run_pipe('%s %s %s' % (self.avm, self.vmargs, testName))
            verifyFunctions = [line.strip() for line in f if line.startswith('verify Function/')]
            if self.verbose:
                outputCalls.append((self.js_print,(verifyFunctions,)))
                
            # we can't compare actual function names since abcdump treats function names and var names the same
            # we instead just compare that the # of functions verified == the # of functions listed out by abcdump
            if len(abcdumpFunctions) != len(verifyFunctions):
                lfail += 1
                outputCalls.append((self.fail,(testName, 'FAILED! :\nExpected (from abcdump): %s functions verified\nGOT (-Dverifyall -Dverbose=verify): %s functions verified' %
                                               (len(abcdumpFunctions),len(verifyFunctions)), self.failmsgs)))
            else:
                lpass += 1
        else:
            if abcargs:
                (f,err,exitcode) = self.run_pipe('%s %s %s %s -- %s' % (self.avm, self.vmargs, extraVmArgs, testName, abcargs))
            else:
                (f,err,exitcode) = self.run_pipe('%s %s %s %s' % (self.avm, self.vmargs, extraVmArgs, testName))
            
        if f and not self.verify:
            try:
                outputLines = []
                for line in f+err:
                    outputLines.append(line)
                    outputCalls.append((self.verbose_print,(line.strip(),)))
                    if 'Assertion failed:' in line:
                        lassert += 1
                        outputCalls.append((self.fail,(testName+extraVmArgs, line, self.assertmsgs)))
                    testcase=''
                    if len(line)>9:
                        testcase=line.strip()
                    skipTestDesc = dict_match(settings,testcase,'skip')
                    if skipTestDesc:
                        outputCalls.append((self.js_print,('  skipping "%s" ... reason: %s' % (line.strip(),skipTestDesc),)))
                        self.allskips+=1
                        continue
                    if 'PASSED!' in line:
                        res=dict_match(settings,testcase,'expectedfail')
                        if res:
                            outputCalls.append((self.fail,(testName, 'unexpected pass: ' + line.strip() + ' reason: '+res, self.unpassmsgs)))
                            lunpass += 1
                        else:
                            lpass += 1
                    if 'FAILED!' in line:
                        res=dict_match(settings,testcase,'expectedfail')
                        if res:
                            outputCalls.append((self.fail,(testName, 'expected failure: ' + line.strip() + ' reason: '+res, self.expfailmsgs)))
                            lexpfail += 1
                        else:
                            lfail += 1
                            outputCalls.append((self.fail,(testName+extraVmArgs, line, self.failmsgs)))
            except:
                print 'exception running avm'
                raise
            exitcodeExp=0
            if isfile(root+".exitcode"):
                try:
                    exitcodeExp=int(open(root+".exitcode").read())
                except:
                    print("ERROR: reading exit code file '%s' should contain an integer")
            res=dict_match(settings,'exitcode','expectedfail')
            if exitcode!=exitcodeExp:
                res2=dict_match(settings,'exitcode','skip')
                if res2==None and res:
                    outputCalls.append((self.js_print,(testName, 'expected failure: exitcode reason: %s'%res,self.expfailmsgs)))
                    lexpfail += 1
                elif res2==None:
                    outputCalls.append((self.fail,(testName, 'unexpected exit code expected:%d actual:%d FAILED!' % (exitcodeExp,exitcode), self.failmsgs)))
                    outputCalls.append((self.fail,(testName, 'captured output: %s' % string.join([l.strip() for l in outputLines], ' | '), self.failmsgs)))
                    lfail+= 1
            elif err!=[]:
                outputCalls.append((self.fail,(testName, "unexpected stderr expected:'%s' actual:'%s'" % ('',err), self.failmsgs)))
            elif lpass == 0 and lfail == 0 and lunpass==0 and lexpfail==0:
                res=dict_match(settings,'*','expectedfail')
                if res:
                    outputCalls.append((self.fail,(testName, 'expected failure: FAILED contained no testcase messages reason: %s' % res,self.expfailmsgs)))
                    lexpfail += 1
                else:
                    lfail = 1
                    outputCalls.append((self.fail,(testName, '   FAILED contained no testcase messages - reason: %s' % string.join([l.strip() for l in outputLines], ' | '), self.failmsgs)))
                 
        self.allfails += lfail
        self.allpasses += lpass
        self.allexpfails += lexpfail
        self.allunpass += lunpass
        self.alltimeouts += ltimeout
        self.allasserts += lassert
        if lfail or lunpass:
            outputCalls.append((self.js_print, ('   FAILED passes:%d fails:%d unexpected passes: %d expected failures: %d' % (lpass,lfail,lunpass,lexpfail), '', '<br/>')))
        else:
            outputCalls.append((self.verbose_print, ('   PASSED passes:%d fails:%d unexpected passes: %d expected failures: %d' % (lpass,lfail,lunpass,lexpfail), '', '<br/>')))
        if self.show_time:
            outputCalls.insert(0,(self.js_print,('%s running %s %s %s time %.1f' % (testnum, ast, extraVmArgs, abcargs, time()-starttime), '<b>', '</b><br/>')));
        else:
            outputCalls.insert(0,(self.js_print,('%s running %s %s %s' % (testnum, ast, extraVmArgs, abcargs), '<b>', '</b><br/>')));
        

        return outputCalls
    
runtest = AcceptanceRuntest()