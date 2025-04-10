#!/usr/python
#  ***** BEGIN LICENSE BLOCK *****
#  Version: MPL 1.1/GPL 2.0/LGPL 2.1
# 
#  The contents of this file are subject to the Mozilla Public License Version
#  1.1 (the "License"); you may not use this file except in compliance with
#  the License. You may obtain a copy of the License at
#  http://www.mozilla.org/MPL/
# 
#  Software distributed under the License is distributed on an "AS IS" basis,
#  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
#  for the specific language governing rights and limitations under the
#  License.
# 
#  The Original Code is [Open Source Virtual Machine.].
# 
#  The Initial Developer of the Original Code is
#  Adobe System Incorporated.
#  Portions created by the Initial Developer are Copyright (C) 2009
#  the Initial Developer. All Rights Reserved.
# 
#  Contributor(s):
#    Adobe AS3 Team
# 
#  Alternatively, the contents of this file may be used under the terms of
#  either the GNU General Public License Version 2 or later (the "GPL"), or
#  the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
#  in which case the provisions of the GPL or the LGPL are applicable instead
#  of those above. If you wish to allow use of your version of this file only
#  under the terms of either the GPL or the LGPL, and not to allow others to
#  use your version of this file under the terms of the MPL, indicate your
#  decision by deleting the provisions above and replace them with the notice
#  and other provisions required by the GPL or the LGPL. If you do not delete
#  the provisions above, a recipient may use your version of this file under
#  the terms of any one of the MPL, the GPL or the LGPL.
# 
#  ***** END LICENSE BLOCK ****
# This script will regenerate performance data for the given build

import subprocess
import os
import shutil
from subprocess import check_call, CalledProcessError
from getopt import getopt
from sys import argv, exit


class RegenerateBaseLineData:
    options = ''
    vmbuilds = ''
    branch = ''
    longOptions = []
    args=[]
    build=''
    
    def __init__(self):
        self.setOptions()
        self.parseOptions()
        self.run()
        
    def vprint(self,msg):
        print msg
        
    def usage(self,c):
        print ''
        print 'usage: %s [options] [test/dir]' % os.path.basename(argv[0])
        print ' Default Usage: This script will regenerate performance data for the given revision'
        print ' and test(s) specified.  If no test/dir is specified, all performance tests will'
        print ' be run for the given revision.'
        #print ' Options that can have multiple values must be comma delimited (no spaces).'
        print ''
        print ' e.g: %s -r 703 -l http://10.60.48.47/builds -b tamarin-central jsbench' % os.path.basename(argv[0])
        print ''
        print ' -r specify revision (build) to regenerate data for (required)'
        print ' -b specify branch [tamarin-redux|tamarin-central|tamarin-flash] (replaces $branch)'
        #print ' -m specify milestone(s) [release|iteration|weekly|all]'
        #print ' -a specify different avmshell name (replaces $)'
        print ' -l specify builds location (replaces $vmbuilds)'
        print ' -h --help print this message'
        exit(c)
        
    def setOptions(self):
        '''set the valid command line options.'''
        self.options = 'r:b:m:a:l:h'
        self.longOptions = ['help']
                   
    def parseOptions(self):
        try:
            opts, self.args = getopt(argv[1:], self.options, self.longOptions )
            if not self.args:
                self.args = ['']
        except:
            self.usage(2)
        
        for o, v in opts:
            if o in ('-r'):
                self.build = v
            elif o in ('-h', '--help'):
                self.usage(0)
            elif o in ('-m'):
                self.milestones = v.split(',')
            elif o in ('-l'):
                self.vmbuilds = v
            elif o in ('-b'):
                self.branch = v
        
        if not self.build:
            self.vprint('Revision/Build must be specified')
            self.usage(1)

    def verifyOptions(self):
        pass
    
    def run(self):
        # determine where buildbot home is
        currentDir = os.getcwd()
        buildbotRootDir = currentDir[0:currentDir.find('performance/')+12]
        # verify that this is the root dir
        if not os.access(buildbotRootDir+'buildbot.tac', os.F_OK):
            self.vprint('Can not determine buildbot root directory')
            exit(1)
        
        os.chdir(buildbotRootDir)
        
        # is buildbot running
        if  os.access(buildbotRootDir+'twistd.pid', os.F_OK):
            restartBuildbot = True
            try:
                check_call(['buildbot', 'stop', '.'])
            except CalledProcessError:
                self.vprint('Problem stopping buildbot.')
            
        
        # lock machine for performance runs
        os.chdir(buildbotRootDir+'scripts')
        try:
            check_call(['../all/lock-acquire.sh',self.build])
        except CalledProcessError:
            self.vprint('Problem aquiring lock.')
        
        # resync qe scripts
        '''
        os.chdir('qe')
        try:
            check_call(['hg', 'pull', '-u'])
        except CalledProcessError:
            self.vprint('Problem syncing qe scripts.')
        '''
        # TODO: resync repo
        
        # override environment vars
        shutil.copyfile(buildbotRootDir+'scripts/environment.sh',buildbotRootDir+'scripts/environment.sh.orig')
        
        newEnvVar = []
        if self.vmbuilds:
            newEnvVar.append('vmbuilds=%s' % self.vmbuilds)
        if self.branch:
            newEnvVar.append('branch=%s' % self.branch)
        newEnvVar.append('change=%s' % self.build)
        envFile = open(buildbotRootDir+'scripts/environment.sh','a')
        envFile.write('\n'.join(newEnvVar))
        envFile.close()
        
        # run perf scripts
        os.chdir(buildbotRootDir+'scripts')
        try:
            check_call(['./prepare.sh',self.build])
        except CalledProcessError:
            self.vprint('Problem with prepare step.')
        
        perfCommands = [
            '../all/run-performance-release.sh',
            '../all/run-performance-release-interp.sh',
            '../all/run-performance-release-jit.sh',
            '../all/run-performance-release-vprof.sh',
            '../all/run-performance-release-mir.sh',
            '../all/run-performance-release-mir-vprof.sh'
            ]
        
        for cmd in perfCommands:
            try:
                check_call([cmd,self.build, self.args[0]])
            except CalledProcessError:
                pass
        
        # replace back to original env file
        os.remove(buildbotRootDir+'scripts/environment.sh')
        os.rename(buildbotRootDir+'scripts/environment.sh.orig', buildbotRootDir+'scripts/environment.sh')
        
        # release lock
        os.chdir(buildbotRootDir+'scripts')
        try:
            check_call(['../all/lock-release.sh',self.build])
        except CalledProcessError:
            self.vprint('Problem releasing lock.')
        
        # restart buildbot
        if restartBuildbot:
            os.chdir(buildbotRootDir)
            try:
                check_call(['buildbot', 'start', '.'])
            except CalledProcessError:
                self.vprint('Problem starting buildbot.')
        

regen = RegenerateBaseLineData()      
