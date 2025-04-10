#!/usr/bin/env python
# -*- coding: UTF-8 -*-

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

import os, sys, getopt, datetime, pipes, glob, itertools, tempfile, string, re, platform, traceback
import subprocess
from math import sqrt
from os.path import *
from os import getcwd,environ,walk
from datetime import datetime
from glob import glob
from sys import argv, exit
from getopt import getopt
from itertools import count
from time import time
from socket import *

# add parent dir to python module search path
sys.path.append('..')

try:
    from util.runtestBase import RuntestBase
    from util.runtestUtils import *
except ImportError:
    print "Import error.  Please make sure that the test/acceptance/util directory has been deleted."
    print "   (directory has been moved to test/util)."
    
class PerformanceRuntest(RuntestBase):
    avm2 = ''
    avmname = 'avm'
    avm2name = 'avm2'
    iterations = 1
    vmname = 'unknown'
    memory = False
    vmversion = ''
    vmargs2 = ''
    optimize = True
    perfm = False
    tmpfile = None
    osName = ''
    logresults = False
    socketlogFile = None
    serverHost = '10.60.48.47'
    serverPort = 1188
    finalexitcode=0
    prettyprint = False
    
    def __init__(self):
        RuntestBase.__init__(self)
    
    def run(self):
        self.setEnvironVars()
        self.loadPropertiesFile()
        self.setOptions()
        self.parseOptions()
        self.altsearchpath='../../other-licenses/test/performance/'
        self.setTimestamp()
        self.checkPath(['avm2'])
        self.determineOS()
        self.getVersion()
        self.tests = self.getTestsList(self.args)
        # Load the root testconfig file
        self.settings, self.includes = self.parseTestConfig('.')
        self.preProcessTests()
        self.runTests(self.tests)
        #self.cleanup()
        
    def setEnvironVars(self):
        RuntestBase.setEnvironVars(self)
        if 'AVM2' in environ:
            self.avm2 = environ['AVM2'].strip()
        if 'VMARGS2' in environ:
            self.vmargs2 = environ['VMARGS2'].strip()
        

    def usage(self, c):
        RuntestBase.usage(self, c)
        print " -S --avm2          second avmplus command to use"
        print "    --avmname       nickname for avm to use as column header"
        print "    --avm2name      nickname for avm2 to use as column header"
        print " -i --iterations    number of times to repeat test"
        print " -l --log           logs results to a file"
        print " -k --socketlog     logs results to a socket server"
        print " -r --runtime       name of the runtime VM used, including switch info eg. TTVMi (tamarin-tracing interp)"
        print " -m --memory        logs the high water memory mark"
        print "    --vmversion     specify vmversion e.g. 502, use this if cannot be calculated from executable"
        print "    --vmargs2       args to pass to avm2, if not specified --vmargs will be used"
        print "    --nooptimize    do not optimize files when compiling"
        print "    --perfm         parse the perfm results from avm"
        print "    --csv           output in csv format"
        print " -p --prettyprint   enhanced terminal coloring"
        exit(c)
    
    def setOptions(self):
        RuntestBase.setOptions(self)
        self.options += 'S:i:lkr:mp'
        self.longOptions.extend(['avm2=','avmname=','avm2name=','iterations=','log','socketlog',
                                 'runtime=','memory','larger','vmversion=','vmargs2=','nooptimize',
                                 'perfm','csv','prettyprint'])
    
    def parseOptions(self):
        opts = RuntestBase.parseOptions(self)
        for o, v in opts:
            if o in ('-S', '--avm2'):
                self.avm2 = v
            elif o in ('--avmname',):
                self.avmname = v
            elif o in ('--avm2name',):
                self.avm2name = v
            elif o in ('-i', '--iterations'):
                self.iterations = int(v)
            elif o in ('-l','--log'):
                self.logFileType='log'
                self.createOutputFile()
            elif o in ('-k', '--socketlog'):
                self.logresults = True
            elif o in ('-r', '--runtime'):
                self.vmname = v
            elif o in ('-m', '--memory'):
                self.memory = True
            elif o in ('--vmversion',):
                self.vmversion = v
            elif o in ('--vmargs2',):
                self.vmargs2 = v
            elif o in ('--nooptimize',):
                self.optimize = False
            elif o in ('--perfm',):
                self.perfm = True
            elif o in ('--csv',):
                self.csv = True
            elif o in ('-p', '--prettyprint'):
                self.prettyprint = True
    
    
    def getVersion(self):
        # ================================================
        # Determine the version number associated with the 
        # VM, will be cyclone if not from build machine
        # ================================================
        if not self.vmversion:
            (f,err,exitcode) = self.run_pipe("%s" % self.avm)
            try:
                for line in f:
                    if re.search(" build ",line):
                        version = line.split()
                        version = version[len(version)-1]
                        if version.find(":") != -1:     # if this is an actual build we need to remove the hash
                            version = version.split(":")
                            version = version[0]
                        self.vmversion = version
                        break
            except:
                self.vmversion = 'unknown'
    
    def compile_test(self, as_file):
        if not isfile(self.shellabc):
            exit("ERROR: shell.abc %s does not exist, SHELLLABC environment variable or --shellabc must be set to shell.abc" % self.shellabc)
        args = []
        args.append('-import %s' % self.shellabc)
        if self.optimize:
            args.append('-optimize -AS3')
        RuntestBase.compile_test(self, as_file, args)
    
    def formatExceptionInfo(maxTBlevel=5):
        cla, exc, trbk = sys.exc_info()
        excName = cla.__name__
        try:
            excArgs = exc.__dict__["args"]
        except KeyError:
            excArgs = "<no args>"
        excTb = traceback.format_tb(trbk, maxTBlevel)
        return (excName, excArgs, excTb)
    

    def socketlog(self, msg):
        if self.logresults:
            if not self.socketlogFile:
                file="socketlog-%s.txt" % self.vmversion
                ctr=0
                while os.path.exists(file):
                    ctr += 1
                    file = "socketlog-%s-%s.txt" % (self.vmversion,ctr)
                self.socketlogFile=file
            open(self.socketlogFile,'a').write(msg)
            try:
                s = socket(AF_INET, SOCK_STREAM)    # create a TCP socket
                s.connect((self.serverHost, self.serverPort)) # connect to server on the port
                s.send("%s;exit\r\n" % msg)         # send the data
                data = s.recv(1024)
                #print('Sent: %s' % msg)
                #print('Received: %s \n\n' % data)
                #s.shutdown(SHUT_RDWR)
                s.close()
            except :
                print("Socket error occured:")
                print(sys.exc_info())
                print('buildbot_status: WARNINGS')

    def parsePerfm(self, line,dic):
        try:
            result = line.strip().split(' ')[-2]
            if 'verify & IR gen' in line:
                dic['verify'].append(int(result))
            elif 'code ' in line:
                dic['code'].append(int(result))
            elif 'compile ' in line:
                dic['compile'].append(int(result))
            elif ('IR-bytes' in line) or ('mir bytes' in line):
                dic['irbytes'].append(int(result))
            elif ('IR ' in line) or ('mir ' in line): #note trailing space
                dic['ir'].append(int(result))
                dic['count'].append(int(line.strip().split(' ')[-1]))
        except:
            pass


    def preProcessTests(self):
        self.checkExecutable(self.avm, 'AVM environment variable or --avm must be set to avmplus')
        if self.avm2:
            self.checkExecutable(self.avm2, '--avm2 must be set to avmplus')
            
        # Print run info and headers
        self.js_print('Executing %d test(s)' % len(self.tests), overrideQuiet=True, csv=False)
        self.js_print("%s: %s %s" % (self.avmname, self.avm, self.vmargs))
        if len(self.avm2)>0:
            if len(self.vmargs2)>0:
                self.js_print("%s: %s %s" % (self.avm2name, self.avm2, self.vmargs2))
            else:
                self.js_print("%s: %s" % (self.avm2name, self.avm2))
        self.js_print('iterations: %s' % self.iterations)
        if len(self.avm2)>0:
            if self.iterations == 1:
                self.js_print("\n%-50s %7s %7s %7s %7s\n" % ("test",self.avmname,self.avm2name, "%sp", "metric"))
            else:
                if self.memory:
                    self.js_print('Note that %diff is calculated using the largest memory value (not avg) from all runs', csv=False)
                else:
                    self.js_print('Note that %diff is calculated using the fastest value (not avg) of all runs', csv=False)
                self.js_print("\n%-50s %20s   %20s" % ('',self.avmname,self.avm2name))
                self.js_print('%-50s  %6s :%6s  %6s %6s    %6s :%6s  %6s %6s %7s %7s %8s' % ('test', 'min','max','avg','stdev','min','max','avg','stdev','%diff','sig  ','metric'))
                self.js_print('                                                   ------------------------------   ------------------------------   -----  -------  ------', csvOut=False)
        else:
            if (self.iterations>2):
                runFormatStr = ''
                if self.csv:
                    for i in range(1,self.iterations+1):
                        runFormatStr += '%7s' % 'run'+str(i)
                self.js_print(("\n\n%-50s %7s %12s %7s "+runFormatStr+"\n") % ("test",self.avmname,"95% conf", "metric"))
            else:
                self.js_print("\n\n%-50s %7s %7s\n" % ("test",self.avmname, "metric"))

    def runTests(self, testList):
        testnum = len(testList)
        for t in testList:
            testnum -= 1
            o = self.runTest((t, testnum))
    
    def parseMemHigh(self, line):
        memoryhigh = 0
        tokens=line.rsplit()
        if len(tokens)>4:
            _mem=tokens[3]
            if _mem.startswith('('):
                _mem=_mem[1:]
            if _mem.endswith(')'):
                _mem=_mem[:-1]
            if _mem.endswith('M'):
                val=float(_mem[:-1])*1024
            else:
                val=float(_mem[:-1])
            if val>memoryhigh:
                memoryhigh=val
        return memoryhigh
    
    def runTest(self, testAndNum):
        ast = testAndNum[0]
        testName = ast
        
        # strip off ./ as test is then treated differently in perf db
        if testName[:2] == './':
            testName = testName[2:]
        if self.altsearchpath!=None and ast.startswith(self.altsearchpath):
            testName = ast[len(self.altsearchpath):]
        testnum = testAndNum[1]
        
        if ast.startswith("./"):
            ast=ast[2:]
        dir =ast[0:ast.rfind('/')]
        root,ext = splitext(ast)
        tname = root[root.rfind('/')+1:]
        abc = "%s.abc" % root
        
        includes = self.includes #list
        settings = {}
        
        # get settings for this test (from main testconfig file loaded into self.settings)
        for k in self.settings.keys():
            if re.search('^'+k+'$', root):
                for k2 in self.settings[k].keys():
                    if k2 in settings:
                        settings[k2].update(self.settings[k][k2])
                    else:
                        settings[k2] = self.settings[k][k2].copy()

        
        if isfile(join(dir,self.testconfig)):
            localIncludes, localSettings = self.parseTestConfig(dir)
            # have a local testconfig, so we create a copy of the global settings to not overwrite
            includes = list(self.includes) #copy list - don't use reference
            includes.extend(localIncludes)
            if localSettings.has_key(root):
                settings.update(localSettings[root])
        
        #TODO: possibly handle includes by building test list?  This works for now...
        if includes and not list_match(includes,root):
            return
            
        if settings.has_key('.*') and settings['.*'].has_key('skip'):
            self.verbose_print('  skipping %s' % testName)
            self.allskips += 1
            return
        
        
        if settings.has_key('.*') and settings['.*'].has_key('largerValuesFaster'):
            largerIsFaster = 'largerValuesFaster'
        else:
            largerIsFaster = ''

        
        self.verbose_print("%d running %s" % (testnum, testName));
        if self.forcerebuild and isfile(abc):
            os.unlink(abc)
        if isfile(abc) and getmtime(ast)>getmtime(abc):
        	self.verbose_print("%s has been modified, recompiling" % ast)
        	os.unlink(abc)
        if not isfile(abc):
            self.compile_test(ast)
            if not isfile(abc):
                self.js_print("compile FAILED!, file not found " + abc)
                
        result1=9999999
        result2=9999999
        resultList=[]
        resultList2=[]
        out1=[]
        out2=[]
        if self.memory and self.vmargs.find("-memstats")==-1:
            self.vmargs="%s -memstats" % self.vmargs
        if self.memory and len(self.vmargs2)>0 and self.vmargs2.find("-memstats")==-1:
            self.vmargs2="%s -memstats" % self.vmargs2
    
        # setup dictionary for vprof (perfm) results
        if self.perfm:
            perfm1Dict = {'verify':[], 'code':[], 'compile':[], 'irbytes':[], 'ir':[], 'count':[] }
            perfm2Dict = {'verify':[], 'code':[], 'compile':[], 'irbytes':[], 'ir':[], 'count':[] }
      
        for i in range(self.iterations):
            memoryhigh = 0
            memoryhigh2 = 0
            (f1,err,exitcode) = self.run_pipe("%s %s %s" % (self.avm, self.vmargs, abc))
            out1.append(f1)
            if len(self.avm2)>0:
                if len(self.vmargs2)>0:
                    (f2,err2,exitcode2) = self.run_pipe("%s %s %s" % (self.avm2, self.vmargs2, abc))
                else:
                    (f2,err2,exitcode2) = self.run_pipe("%s %s %s" % (self.avm2, self.vmargs, abc))
                out2.append(f2)
            try:
                if exitcode!=0:
                    self.finalexitcode=1
                    memoryhigh=0
                else:
                    for line in f1:
                        if self.memory:
                            if "[mem]" in line and "private" in line:
                                memoryhigh = self.parseMemHigh(line)
                        elif "metric" in line:
                            rl=[]
                            rl=line.rsplit()
                            if len(rl)>2:
                                if "." in rl[2]:
                                    resultList.append(float(rl[2]))
                                else:
                                    resultList.append(int(rl[2]))
                                metric=rl[1]
                        elif self.perfm:
                            self.parsePerfm(line, perfm1Dict)
                if self.memory:
                    metric="memory"
                    resultList.append(memoryhigh)
                if len(self.avm2)>0:
                    if exitcode2!=0:
                        self.finalexitcode=1
                        memoryhigh2=0
                    else:
                        for line in f2:
                            if self.memory:
                                if "[mem]" in line and "private" in line:
                                    memoryhigh2 = self.parseMemHigh(line)
                            elif "metric" in line:
                                rl=[]
                                rl=line.rsplit()
                                if len(rl)>2:
                                    resultList2.append(int(rl[2]))
                            elif self.perfm:
                                self.parsePerfm(line, perfm2Dict)
                    if self.memory:
                        resultList2.append(memoryhigh2)
            except:
                print self.formatExceptionInfo()
                exit(-1)
        # end for i in range(iterations)
        # calculate best result
        if len(resultList)!=self.iterations:
            for f in out1:
                for line in f:
                    print(line.strip())
            result1=9999999
            result2=9999999
        else:
            if largerIsFaster:
                result1 = max(resultList)
                if resultList2:
                    result2 = max(resultList2)
            else:
                result1 = min(resultList)
                if resultList2:
                    result2 = min(resultList2)
            if self.memory:
                memoryhigh = max(resultList)
                if len(self.avm2)>0:
                    memoryhigh2 = max(resultList2)
                if memoryhigh<=0:
                    spdup = 9999
                else:
                    spdup = ((memoryhigh2-memoryhigh)/memoryhigh)*100.0
            elif len(self.avm2)>0:
                if len(resultList2)!=self.iterations:
                    for f in out2:
                        for line in f:
                            print(line.strip())
                if result1==0 or result2==0:
                    spdup = 9999
                else:
                    if largerIsFaster:
                        spdup = float(result2-result1)/result1*100.0
                    else:
                        spdup = float(result1-result2)/result1*100.0
        if self.memory:
            if len(self.avm2)>0:
                if self.iterations == 1:
                    self.js_print("%-50s %7s %7s %7.1f %7s %s" % (testName,formatMemory(memoryhigh),formatMemory(memoryhigh2),spdup, metric, largerIsFaster))
                else:
                    mem1_avg = formatMemory(sum(resultList)/float(len(resultList)))
                    mem2_avg = formatMemory(sum(resultList2)/float(len(resultList2)))
                    relStdDev1 = rel_std_dev(resultList)
                    relStdDev2 = rel_std_dev(resultList2)
                    try:
                        sig = spdup / (relStdDev1+relStdDev2)
                    except ZeroDivisionError:
                        sig = cmp(spdup,0) * (3.0 if abs(spdup) > 5.0 else 2.0 if abs(spdup) > 1.0 else 0.0)
                    sig_str = '--' if (sig < -2.0 and spdup < -5.0) else '- ' if sig < -1.0 \
                              else '++' if (sig > 2.0 and spdup > 5.0) else '+ ' if sig > 1.0 else '  '
                    bold = '\033[1m' if (abs(sig)>1.0 and self.prettyprint) else ''
                    endbold = '\033[0;0m' if bold else ''
                    self.js_print('%s%-50s [%6s :%6s] %6s ±%4.1f%%   [%6s :%6s] %6s ±%4.1f%% %6.1f%% %5.1f %2s %7s %s%s' %
                                  (bold,testName,formatMemory(min(resultList)),formatMemory(memoryhigh),mem1_avg,
                                    rel_std_dev(resultList), formatMemory(min(resultList2)),
                                    formatMemory(memoryhigh2),mem2_avg,rel_std_dev(resultList2),
                                    spdup, sig, sig_str, metric, largerIsFaster,endbold) )
            else:
                confidence=0
                meanRes=memoryhigh
                if self.iterations>2:
                    meanRes=mean(resultList)
                    if meanRes>0:
                        confidence = ((tDist(len(resultList)) * standard_error(resultList) / meanRes) * 100)
                    runResults = ''
                    for i in range(self.iterations):
                        runResults += '%8s' % formatMemory(resultList[i])
                    self.js_print(("%-50s %7s %10.1f%%  %7s "+runResults) % (testName,formatMemory(memoryhigh),confidence, "memory"))
                else:
                    self.js_print("%-50s %7s %7s" % (testName,formatMemory(memoryhigh), metric))
                config = "%s" % self.vmargs.replace(" ", "")
                config = config.replace("-memstats","")
                self.socketlog("addresult2::%s::%s::%s::%0.1f::%s::%s::%s::%s::%s::%s;" % (testName, metric, memoryhigh, confidence, meanRes, self.iterations, self.osName.upper(), config, self.vmversion, self.vmname))
        else:
            if len(self.avm2)>0:
                if self.iterations == 1:
                    self.js_print('%-50s %7s %7s %7.1f %7s %s' % (testName,result1,result2,spdup, metric, largerIsFaster))
                else:
                    try:
                        rl1_avg=sum(resultList)/float(len(resultList))
                        rl2_avg=sum(resultList2)/float(len(resultList2))
                        min1 = float(min(resultList))
                        min2 = float(min(resultList2))
                        max1 = float(max(resultList))
                        max2 = float(max(resultList2))
                        relStdDev1 = rel_std_dev(resultList)
                        relStdDev2 = rel_std_dev(resultList2)
                        try:
                            if largerIsFaster:
                                spdup = 100.0*(max2-max1)/max1
                            else:
                                spdup = 100.0*(min1-min2)/min1
                        except ZeroDivisionError:
                            spdup = 9999
                        try:
                            sig = spdup / (relStdDev1+relStdDev2)
                        except ZeroDivisionError:
                            # determine sig by %diff (spdup) only
                            sig = cmp(spdup,0) * (3.0 if abs(spdup) > 5.0 else 2.0 if abs(spdup) > 1.0 else 0.0)
                        sig_str = '--' if (sig < -2.0 and spdup < -5.0) else '- ' if sig < -1.0 \
                                  else '++' if (sig > 2.0 and spdup > 5.0) else '+ ' if sig > 1.0 else '  '
                        # only bold if abs > 1 and averages are > 3 ms apart
                        bold = '\033[1m' if (abs(sig)>1.0 and abs(rl1_avg-rl2_avg) > 3 and self.prettyprint) else ''
                        endbold = '\033[0;0m' if bold else ''
                        self.js_print('%s%-50s [%6s :%6s] %6.1f ±%4.1f%%   [%6s :%6s] %6.1f ±%4.1f%% %6.1f%% %5.1f %2s %7s %s%s' %
                                      (bold,testName, min1, max1, rl1_avg, relStdDev1,
                                       min2, max2, rl2_avg, relStdDev2,
                                       spdup, sig,sig_str, metric, largerIsFaster,endbold))
                    except:
                        print sys.exc_info
                        self.js_print('%-50s [%6s :%6s] %6.1f %6s   [%6s :%6s] %6.1f %6s %7.1f %7s %s' % (testName, '', '', result1,'', '', '', result2,'', spdup, metric, largerIsFaster))
                #TODO: clean up / reformat
                if self.perfm:
                    if perfm1Dict['verify']:    # only calc if data present
                        def calcPerfm(desc, key):
                        # calculate min, max, average and %diff of averages
                            try:
                                if self.iterations == 1:
                                    self.js_print( '     %-45s %7s %7s %7.1f' % (desc, perfm1Dict[key][0], perfm2Dict[key][0],
                                                ((perfm1Dict[key][0]-perfm2Dict[key][0])/float(perfm2Dict[key][0])*100.0)))
                                else:
                                    avg1 = sum(perfm1Dict[key])/len(perfm1Dict[key])
                                    avg2 = sum(perfm2Dict[key])/len(perfm2Dict[key])
                                    self.js_print('     %-45s [%6s :%6s] %6s   [%6s :%6s] %6s %7.1f' % (desc, min(perfm1Dict[key]), max(perfm1Dict[key]), avg1,
                                                                                 min(perfm2Dict[key]), max(perfm2Dict[key]), avg2,
                                                                                 ((avg1-avg2)/float(avg2))*100.0))
                            except:
                                pass
                
                        calcPerfm('verify & IR gen (time)','verify')
                        calcPerfm('compile (time)','compile')
                        calcPerfm('code size (bytes)','code')
                        calcPerfm('mir/lir bytes', 'irbytes')
                        calcPerfm('mir/lir (# of inst)', 'ir')
                        calcPerfm('count', 'count')
                        self.js_print('-------------------------------------------------------------------------------------------------------------')
            else: #only one avm tested
                if result1 < 9999999 and len(resultList)==self.iterations:
                    meanRes = mean(resultList)
                    if (self.iterations > 2):
                        confidence = conf95(resultList)
                        config = "%s" % self.vmargs.replace(" ", "")
                        config = "%s" % config.replace("\"", "")
                        if config.find("-memlimit")>-1:
                            config=config[0:config.find("-memlimit")]
                        if self.perfm:  #send vprof results to db   
                            if perfm1Dict['verify']:    # only calc if data present
                                #calc confidence and mean for each stat
                                def perfmSocketlog(metric,key):
                                  self.socketlog("addresult2::%s::%s::%s::%0.1f::%s::%s::%s::%s::%s::%s;" % 
                                           (testName, metric,min(perfm1Dict[key]), conf95(perfm1Dict[key]), mean(perfm1Dict[key]), self.iterations, self.osName.upper(), config, self.vmversion, self.vmname))
                                perfmSocketlog('vprof-compile-time','compile')
                                perfmSocketlog('vprof-code-size','code')
                                perfmSocketlog('vprof-verify-time','verify')
                                perfmSocketlog('vprof-ir-bytes','irbytes')
                                perfmSocketlog('vprof-ir-time','ir')
                                perfmSocketlog('vprof-count','count')
                        self.socketlog("addresult2::%s::%s::%s::%0.1f::%s::%s::%s::%s::%s::%s;" % (ast, metric, result1, confidence, meanRes, self.iterations, self.osName.upper(), config, self.vmversion, self.vmname))
                        runResults = ''
                        if self.csv:
                            for i in range(self.iterations):
                                runResults += '%8s' % resultList[i]
                        else:
                            runResults = str(resultList)
                        self.js_print(("%-50s %7s %10.1f%% %7s  "+runResults+" %s") % (ast,result1,confidence,metric, largerIsFaster)) 
                    else: #one iteration
                        self.js_print("%-50s %7s %7s %s" % (testName,result1,metric,largerIsFaster)) 
                else:
                        self.js_print("%-50s %7s %s" % (testName,'no test result - test output: ',f1))
                        self.finalexitcode=1

runtest = PerformanceRuntest()
exit(runtest.finalexitcode)
