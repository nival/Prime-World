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
# Adobe System Incorporated..
# Portions created by the Initial Developer are Copyright (C) 2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Adobe AS3 Team

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
# ***** END LICENSE BLOCK *****

import os, xmlrpclib, time, shutil, subprocess, getopt
from buildbot.scripts import runner
from sys import argv, exit
from getopt import getopt
from StringIO import StringIO


MASTER = "10.171.22.12:9750" #localhost:9850
SERVER_URL = "http://10.171.22.12:8750/xmlrpc" #http://localhost:8850/xmlrpc
INTERVAL_TIMER = 120
MASTER_ROOT = 'e:/AVMTeam/buildbot/master-tamarin-redux'
PENDING_BUILDS = MASTER_ROOT+'/changes/pending'
PROCESSED_BUILDS = MASTER_ROOT+'/changes/processed'
LOG = MASTER_ROOT+'/changes/trigger.log'
BUILDBOT_SCRIPT = 'buildbot'


def usage(c):
    print "usage: %s [options] " % argv[0]
    print " -m --master=           ip:port to the buildbot master [required]"
    print " -u --url=              URL to the xmlrpc buildbot status [required]"
    print " -i --interval=         number of seconds to sleep betwwn build checks [default=60]"
    exit(c)
    
try:
    opts, args = getopt(argv[1:], "m:u:i", ["master=","url="])
except:
    usage(2)

if not args:
    args = ["."]
for o, v in opts:
    if o in ("-m", "--master"):
        MASTER = v;
    elif o in ("-u", "--url"):
        SERVER_URL = v
    elif o in ("-i"):
        INTERVAL_TIMER = int(v)

if MASTER == "":
    print "MASTER"
    usage(2)
if SERVER_URL == "":
    print "server"
    usage(2)

def log(msg):
    print(msg)
    logfile = open(LOG, "a")
    logfile.write("%s\n" % msg)
    logfile.close()

def triggerBuild(build, branch='tamarin-redux'):
    
    s = open(PROCESSED_BUILDS +"/" + build)
    comments=''
    username=''
    revision=''
    files=''
    user='unknown'
    files = ['']

    while True:
        line = s.readline()
        if not line:
            break
        if line.startswith("user:"):
            user = line[line.find(":")+1:].strip()
        elif line.startswith("changeset:"):
            revision = line[line.find(":")+1:].strip()
            if revision.find(':') != -1:
                revision = revision[:revision.find(":")].strip()
        elif line.startswith("files:"):
            files = line[line.find(":")+1:].strip()
        elif line.startswith("description:"):
            comments = "".join(s.readlines())
            if comments[-1] == "\n":
                # this removes the additional newline that hg emits
                comments = comments[:-1]
            break

    s.close()
    args = BUILDBOT_SCRIPT
    args += " sendchange "
    args += " --master=%s " % MASTER
    args += " --username='%s' " % user
    args += " --revision=%s " % revision
    args += " --branch=%s " % branch
    args += " --comments=\"%s\"" % comments
    args += " %s " % files
    subprocess.call([args],shell=True) 
    
    time.sleep(1)

def getPriorityRequests(files):
    requests = []
    for file in files:
        if file.find('change-') != -1:
            requests.append(file)
    return requests

def getSandboxRequests(files):
    requests = []
    for file in files:
        if file.find('change-') == -1:
            requests.append(file)
    return requests


server = xmlrpclib.Server(SERVER_URL)
while True:
    log(time.ctime(time.time()))
    if os.path.exists(PENDING_BUILDS +"/halt"):
        log("HALTING, %s/halt exists" % PENDING_BUILDS)
        break
    try:
        # Is there an active buildset?
        active = server.isBuildSetActive(['compile','smoke','test','compile-sandbox','smoke-sandbox','test-sandbox'])

        log("active: %s" % active)

        if not active:
            log("Look for pending builds")

            files = os.listdir(PENDING_BUILDS)
            if len(files) > 0:
                files.sort() # files are in arbitary order be default
                log("found the following: %s" % files)

                ## First look for 'change-XXXX' files, these are tamarin-redux builds and
                ## have the highest priority.
                priorityRequests = getPriorityRequests(files)
                if len(priorityRequests) > 0:
                    #log("PRIORITY: %s" % priorityRequests)
                    for change in priorityRequests:
                        log("going to build: %s" % change)
                        # TODO: Should catch any errors in triggereing the build and
                        # then move the file back into PENDING_BUILDS
                        shutil.move("%s/%s" % (PENDING_BUILDS, change), PROCESSED_BUILDS)
                        triggerBuild(change)
                    log("No more pending changes")
                else: # there must be sandbox builds
                    sandboxRequests = getSandboxRequests(files)
                    #log("SANDBOX: %s" % sandboxRequests)
                    change = sandboxRequests[0]
                    log("going to build: %s" % change)
                    # TODO: Should catch any errors in triggereing the build and
                    # then move the file back into PENDING_BUILDS
                    shutil.move("%s/%s" % (PENDING_BUILDS, change), PROCESSED_BUILDS)
                    triggerBuild(change, 'sandbox')
            else:
                log("There are no pending builds.")

    except:
        log("server is offline: %s" % SERVER_URL)
    time.sleep(INTERVAL_TIMER)
    
