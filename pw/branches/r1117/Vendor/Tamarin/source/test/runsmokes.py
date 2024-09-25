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
# Portions created by the Initial Developer are Copyright (C) 2009
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
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

import sys,os.path,os,getopt,time,subprocess,re

class RunSmokes():
    # shows detailed output for each test
    verbose=False

    # timeout in seconds
    timeout=120

    # test file
    testfile='./runsmokes.txt'

    # config, if None let runtests.py compute
    config=None

    allpasses=0
    allfails=0

    failed=False
    failures=''

    startTime=time.time()

    # list of actual env variables
    envsubs=[]

    def usage(self):
        print 'usage: %s [options]' % os.path.basename(sys.argv[0])
        print '-t --time       time in seconds to run,  tests will keep running until the time has been exceeded'
        print '-f --testfile   file containing commands to run'

    def setoptions(self):
        options = 't:f:hv'
        longoptions= ['time=','testfile=','help','verbose']
        try:
            opts,args = getopt.getopt(sys.argv[1:],options,longoptions)
        except:
            self.usage()
            sys.exit(1)
        for o,v in opts:
            if o in ('-t','--time'):
                self.timeout=int(v)
            if o in ('-f','--testfile'):
                self.testfile=v
            if o in ('-v','--verbose'):
                self.verbose=True
            if o in ('-h','--help'):
                self.usage()
                sys.exit(1)
        return opts

    def __init__(self):
        self.setoptions()

    def run(self):
        print "starting smoke tests"
        print "    test file is %s" % self.testfile
        if self.timeout > 0:
            print "    will run tests until timeout of %ds is exceeded" % self.timeout
        else:
            print "    will run tests until all tests are complete, no timeout"
        print
        try:
            infile=open(self.testfile,'r')
        except:
            print "ERROR reading file %s" % testfile
            sys.exit(1)
        for test in infile:
            test=test.strip()
            if len(test)==0 or test[0]=='#':
                continue
            if self.timeout > 0:
                if time.time()-self.startTime>self.timeout:
                    break
            self.runtest(test)
        if self.timeout > 0:
            if time.time()-self.startTime<self.timeout:
                print '\ntests finished after %d seconds, did not exceed timeout of %d seconds' % (time.time()-self.startTime,self.timeout)
            else:
                print '\nexceeded timeout of %d seconds, actual time %d seconds' % (self.timeout,time.time()-self.startTime)
        else:
            print '\ntests finished after %d seconds' % (time.time()-self.startTime)
        infile.close()

    def showstats(self):
        print "\nenvironment variables:"
        for env in self.envsubs:
            print "    %s = %s" % (env,os.environ[env])
        print "\npasses             : %d" % self.allpasses
        print "failures           : %d" % self.allfails
        if self.allfails>0:
            print "\nlist of test failures:\n%s" % self.failures

    def replaceEnv(self,line):
        envs=re.findall('\$\{[A-Za-z0-9_\-]+\}',line)    
        for env in envs:
            env=env[2:-1]
            if os.environ.has_key(env)==False:
                print "ERROR: environment variable '%s' is not defined, exiting" % env
                sys.exit(1)
            if (env in self.envsubs)==False:
                self.envsubs.append(env)
            val=os.environ[env]
            if val==None:
                continue
            line=re.sub('\$\{%s\}' % env, val, line)
        return line

    def scrub(self,out):
        out=re.sub('passes',' passes',out)
        out=re.sub('failures',' failures',out)
        out=re.sub('assertions',' assertions',out)
        out=re.sub('tests skipped',' tests skipped',out)
        return out

    def runtest(self,rawcommand):
        command=self.replaceEnv(rawcommand)
        if os.name=='nt':
            command=command.replace(';','&&')
        detail=""
        out=err=""
        try:
            process=subprocess.Popen(command,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
            (out,err)=process.communicate()
            exitcode=process.returncode
        except:
            detail="ERROR: running test"
            exitcode=1        
        tm=time.time()-self.startTime

        passes=0
        fails=0
        expectfail=0
        unpass=0
        asserts=0
        skips=0
        
        if exitcode!=0:
            detail+=" exitcode=%d" % exitcode
        if self.verbose:
            print "[OUTPUT %s]" % command
            out=self.scrub(out)
            print out
            print "[ENDOUTPUT %s]" % command
        for line in out.splitlines():
            line=line.strip()
            if re.search('time$',line):
                passes+=1
            if re.search('crash$',line):
                fails+=1
            if re.search("PASSED$",line):
                passes+=1
            if re.search("FAILED$",line):
                fails+=1
            if re.search("^passes",line):
                n=int(line.split()[2])
                if n>0 and passes==0:
                    passes+=1
            if re.search("^failures",line):
                n=int(line.split()[2])
                if n>0 and fails==0:
                    fails+=1
            if re.search("^expected failures",line):
                passes+=1
                expectfail=int(line.split()[3])
                detail+=" ef: %d" % expectfail
            if re.search("^unexpected passes",line):
                fails+=1
                unpass=int(line.split()[3])
                detail+=" up: %d" % unpass
            if re.search("^assertions",line):
                fails+=1
                asserts=int(line.split()[2])
                detail+=" as: %d" % asserts
            if re.search("^tests skipped",line):
                passes+=1
                skips=int(line.split()[3])
                detail+=" sk: %d" % skips
        detail="p:%d f:%d %s" % (passes,fails,detail)
        if passes==0 or fails>0 or exitcode!=0:
            if fails==0:
                fails+=1
            status="failed"
            self.failed=True
            out=self.scrub(out)
            self.failures+="%s\n%s\n[OUTPUT]\n%s%s\n[END OUTPUT]\n" % (rawcommand,command,out,err)
        else:
            status="passed"
        print "%s %ds %s %s" % (status,tm,rawcommand,detail)
        sys.stdout.flush()
        if fails>0:
            self.allfails+=1
        else:
            self.allpasses+=1

## main
r = RunSmokes()
r.run()
r.showstats()
if r.failed:
    sys.exit(1)
