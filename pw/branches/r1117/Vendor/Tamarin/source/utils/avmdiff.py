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
# The Original Code is [Open Source Virtual Machine].
#
# The Initial Developer of the Original Code is
# Adobe System Incorporated.
# Portions created by the Initial Developer are Copyright (C) 2007
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
# ***** END LICENSE BLOCK *****


# -*- Mode: Python; indent-tabs-mode: nil -*-
# vi: set ts=4 sw=4 expandtab:

# python modules
import random, os, time, signal, getopt, sys, subprocess, difflib, re, platform
from getopt import getopt
from sys import argv, exit, stderr
from os.path import basename, exists, join, dirname
from subprocess import Popen, PIPE
from difflib import unified_diff

topdir = ""

quiet = False
verbose = False
(avmr,avmrd,avmd,avmdd)=('','','','')

# read the list of vm's to use from filename
# todo: support wildcards
#
# buildfile syntax:
# [builds]
#   <list of exe paths>
#
# [options]
#   list of options, one group per line

def read_buildfile(filename):
    f = open(filename, 'r')
    try:
        builds = []
        options = []
        combined = []
        list = None
        for l in f.readlines():
            l = l.strip()
            if len(l) == 0 or l[0] == '#':
                continue
            elif l == '[builds]':
                list = builds
            elif l == '[options]':
                list = options
            elif l == '[combined]':
                list = combined
            else:
                if l == '-':
                    l = ''
                l=re.sub('{shell_release}',avmr,l)    
                l=re.sub('{shell_release_debugger}',avmrd,l)    
                l=re.sub('{shell_debug}',avmd,l)    
                l=re.sub('{shell_debug_debugger}',avmdd,l)    
                list.append(l)
        return builds, options, combined
    finally:
        f.close()

# make_vmlist: combine all the option choices with all the build choices
#    and return a list of len(builds) * len(options) command lines.
def make_vmlist(buildfile):
    builds, options, combined = read_buildfile(buildfile)
    missing = [p for p in builds if not exists(p)]
    if len(missing) > 0:
        for p in missing:
            print >> stderr, "no such file: ", p 
        exit(1)
    vms = []
    for build in builds:
        for o in options:
            vms.append('%s %s' % (build, o))
    vms = vms + combined
    verbose_print('created %d configurations' % len(vms))
    if verbose:
        for v in vms:
            print(v)
    
    return vms
try:
    signames = {
       # if you see a process die with SIG123, then add more entries below
       signal.SIGINT:  'SIGINT',
       signal.SIGILL:  'SIGILL',
       signal.SIGTERM: 'SIGTERM',
       signal.SIGABRT: 'SIGABRT',
       signal.SIGKILL: 'SIGKILL',
       signal.SIGBUS:  'SIGBUS',
    }
except:
    signames = {
       signal.SIGINT:  'SIGINT',
       signal.SIGILL:  'SIGILL',
       signal.SIGTERM: 'SIGTERM',
       signal.SIGABRT: 'SIGABRT',
    }

def signame(sig):
    if sig in signames:
        return signames[sig]
    else:
        return "SIG%d" % sig

def abcdump(filename):
	os.system('~/hg/tamarin-redux/objdir-release/shell/avmshell ~/hg/tamarin-redux/utils/abcdump.abc -- ' + filename)

def avm(vm, args):
    cmd = vm + ' ' + args + ' 2>&1'
    p = Popen(cmd, shell=True, stdout=PIPE)
    output = ()
    try:
        for line in p.stdout:
            line=scrub_errors(line)
            if len(line)>0:
                output = output + (line,)
    finally:
        p.stdout.close()
        stat = p.wait()
        if stat >= 128:
            stat = -(stat & ~128)
        return (stat, output)

def describe(e):
    stat, out = e
    s = ""
    #for l in out:
        #s += l
    if stat < 0:
        sig = -stat
        if s != "":
            s += '\n'
        s += "%s" % signame(sig)
    elif stat != 0:
        if s != "":
            s += '\n'
        s += "EXIT %d" % stat
    return s

def scrub_passfail(line):
# removed PASSED and FAILED messages interfering with runtests counting PASSES and FAILS tests
    line=re.sub('PASSED','P***ED',line)
    line=re.sub('FAILED','F***ED',line)
    line=re.sub('Assertion failed','A**ertion failed',line)
    return line
    
def scrub_errors(line):
# remove Error information only appearing in debugger builds
    match=re.search('[\w]+Error: Error #[0-9]+:',line)
    if match:
        end=match.end()-1
        newline=line[0:end]
        match2=line.find(') = Passed',end)
        if match2>-1:
            newline+=line[match2:]
        elif re.search('PASSED!',line):
            newline+=' PASSED!'
            newline+='\n'
        line=newline
# remove stack traces only appearing in debugger builds
    if re.search('at [\w]+()',line):
        line=''
# remove lines beginning with metric, variable data like timing should use this prefix
    if re.search('^metric ',line):
        line=''
    return line

def verbose_print(s):
    if verbose:
        print(s)

def compare(vmlist, args):
    results = {}
    if len(vmlist) < 2:
        print >> stderr, "too few vms were given"
        exit(1)
    for vm in vmlist:
        verbose_print('%s %s' % (vm,args))
        e = avm(vm, args)
        verbose_print(e)
        if e in results:
            results[e] += [vm]
        else:
            results[e] = [vm]
    return results

def printlines(seq):
    for l in seq:
        print scrub_passfail(l),

def pick_majoirty(results):
    # pick the result with the most examples
    e0 = ()
    maxlen = 0
    for e in results:
        if len(results[e]) > maxlen:
            e0 = (e,)
            maxlen = len(results[e])
        elif len(results[e]) == maxlen:
            e0 += (e,)
    if len(e0) == 1:
        return e0[0]
    # need a tiebreaker, prefer stat==0 over nonzero
    l = [(stat,out) for stat,out in e0 if stat == 0]
    if len(l) > 0:
        return l[0]
    # prefer stat > 0 (error) over stat < 0 (crash)
    l = [(stat,out) for stat,out in e0 if stat > 0]
    if len(l) > 0:
        return l[0]
    # just pick the first one
    return l[0]

def test(vmlist, args):
    results = compare(vmlist, args)
    e0 = pick_majoirty(results)
    stat0, out0 = e0
    if len(results) != 1:
        # results not all the same.  print the outliers as diffs against the majority
        print args, 'FAILED! diff'
        for e in results:
            if e != e0:
                out0 = out0 + (describe(e0)+'\n',)
                out = e[1] + (describe(e)+'\n',)
                printlines(unified_diff(out0, out, str(results[e0]), str(results[e])))
        return 1
    elif stat0 < 0:
        # everyone crashed the same way
        print args, 'FAILED!', describe(e0)
        prinlines(out0)
        return stat0
    if quiet:
        return 0
    # all agree, print output and return exit code
    printlines(out0)
    return stat0

def usage(stat):
    print 'usage: %s [hqf]' % basename(argv[0])
    print ' -h --help        print this message'
    print ' -f --buildfile   specify file with list of vms to compare, default is "Buildfile"'
    print ' -q --quiet       if vms agree, print "PASSED!" and return 0 instead of the vm output'     
    print ' -v --verbose     print extra info for diagnosing problems'     
    exit(stat)

if __name__ == '__main__':
    cwd = os.path.dirname(sys.argv[0])
    buildfile = cwd+'/avmdiff.cfg'
    try:
        opts, vmargs = getopt(argv[1:], 'hf:qv', ['help', 'buildfile=', 'quiet', 'verbose'])
    except:
        usage(2)

    for o, v in opts:
        if o in ('-h', '--help'):
            usage(0)
        elif o in ('-q', '--quiet'):
            quiet = True
        elif o in ('-f', '--buildfile'):
            buildfile = v
        elif o in ('-v', '--verbose'):
            verbose = True

    arglist = ""
    for a in vmargs:
        arglist += a + " "
    if os.path.isfile(buildfile)==False:
        print "ERROR: Buildfile does not exist: '%s'" % buildfile
        exit(1)

    exe=''
    if re.search('(CYGWIN_NT|Windows)',platform.system()):
        exe='.exe'
    avmr=cwd+'/../objdir-release/shell/avmshell'+exe
    avmrd=cwd+'/../objdir-releasedebugger/shell/avmshell'+exe
    avmd=cwd+'/../objdir-debug/shell/avmshell'+exe
    avmdd=cwd+'/../objdir-debugdebugger/shell/avmshell'+exe
    if os.environ.has_key('shell_release'):
        avmr=os.environ['shell_release']
    if os.environ.has_key('shell_release_debugger'):
        avmrd=os.environ['shell_release_debugger']
    if os.environ.has_key('shell_debug'):
        avmd=os.environ['shell_debug']
    if os.environ.has_key('shell_debug_debugger'):
        avmdd=os.environ['shell_debug_debugger']

    vmlist = make_vmlist(buildfile)
    stat = test(vmlist, arglist)
    if stat == 0:
        print 'PASSED! all configs match'
    exit(stat)
