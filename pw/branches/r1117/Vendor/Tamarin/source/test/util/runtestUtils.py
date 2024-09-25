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

import re
import pprint
import platform
import os
from os.path import join, isdir, islink, splitext, exists
from math import sqrt
import subprocess
import shutil

class TimeOutException(Exception):
    def __init__(self):
        pass

# functions that all can be used independently

def convertToCsv(line):
        # convert all whitespace and [ : ] chars to ,
        line = line.replace('\n', '')
        line = line.replace('[',' ')
        line = line.replace(']',' ')
        line = line.replace(':',' ')
        lineList = []
        
        for l in line.split():
            l = l.strip()
            if l.find(',') != -1:   #wrap with "" if there is a , in val
                l = '"%s"' % l
            lineList.append(l)
        
        return ','.join(lineList)

def detectCPUs():
    """
    Detects the number of CPUs on a system.
    """
    # Linux, Unix and MacOS:
    if hasattr(os, "sysconf"):
        if os.sysconf_names.has_key("SC_NPROCESSORS_ONLN"):
            # Linux & Unix:
            ncpus = os.sysconf("SC_NPROCESSORS_ONLN")
            if isinstance(ncpus, int) and ncpus > 0:
                return ncpus
        else: # OSX:
            p = subprocess.Popen("sysctl -n hw.ncpu", shell=True, close_fds=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
            return int(p.stdout.read())
    # Windows:
    if os.environ.has_key("NUMBER_OF_PROCESSORS"):
        ncpus = int(os.environ["NUMBER_OF_PROCESSORS"]);
        if ncpus > 0:
            return ncpus
    return 1 # Default  

def dict_match(dict,test,value):
    for k in dict.keys():
        if re.search(k,test):
            if dict[k].has_key(value):
                return dict[k][value]

def formatMemoryList(lst):
    out=""
    for mem in lst:
        out="%s%s, " %(out,formatMemory(mem))
    out=out[:-2]
    return out

def formatMemory(mem):
    if mem<1024:
        out="%dK" % mem
    else:
        out="%.1fM" % (mem/1024.0)
    return  out

def list_match(list,test):
    for k in list:
        if re.search(k,test):
            return True
    return False

def parseArgStringToList(argStr):
    # Convert an argument string to a list
    args = argStr.strip().split(' ')
    # recombine any args that have spaces in them
    argList = []
    for a in args:
        if a == '':
            pass
        elif a[0] == '-':
            argList.append(a)
        else:   # append the space and text to the last arg
            argList[len(argList)-1] += ' ' + a
    return argList

def pPrint(obj):
    pprint.pprint(obj)
    

def splitList(_list, _groups):
    groups = []
    groupSize = len(_list) / _groups
    startIndex = 0
    for i in range(1, _groups): 
        groups.append(_list[startIndex:i*groupSize])
        startIndex = i*groupSize
    # add the remaining elements
    groups.append(_list[startIndex:])
    return groups

### ATS Support Functions ###

def genAtsArgs(dir, file, atstemplate):
    args = []
    (name, ext) = splitext(file)
    # insert filename into template
    atstemplate[2] = 'var fileName:String = "%s_";\n' % name
    # write out the template file
    ats_inc = open('./ats_temp.as','w')
    ats_inc.writelines(atstemplate)
    ats_inc.close()
    if not 'ecma' in dir:
        args.append('-AS3')
    args.extend(['-swf 200,200','-in ./ats_temp.as'])
    return args
    
def moveAtsSwf(dir, file, atsDir):
    # move the swf to the swfs dir
    (name, ext) = splitext(file)
    try:
        atsOut = atsDir+'/'+dir 
        if not exists(atsOut):
            os.makedirs(atsOut)
    except:
        pass
        
    try:
        shutil.move('%s/%s.swf' % (dir,name),'%s/%s_.swf' % (atsOut,name))
    except IOError:
        print 'Error attempting to move %s/%s_.swf' % (dir,name)
    except:
        raise


### Statistical Functions ###

def conf95(list):
    if mean(list) == 0:
        return 0
    return ((tDist(len(list)) * standard_error(list) / mean(list)) * 100)
    
def mean(population):
    mean = 0.0
    for x in population:
        mean = mean + float(x)
    return mean / len(population)

def rel_std_dev(population):
    # Relative Standard Deviation = % standard deviation
    try:
        return (100*standard_deviation(population))/mean(population)
    except ZeroDivisionError:
        return 0.0

def standard_deviation(population):
    return sqrt(variance(population))

def standard_error(population):
    return standard_deviation(population) / sqrt(len(population))
    
def tDist(n):
    tDistribution = [ 999, 999, 12.71, 4.30, 3.18, 2.78, 2.57, 2.45, 2.36, 2.31, 2.26, 2.23, 2.20, 2.18, 2.16, 2.14, 2.13, 2.12, 2.11, 2.10, 2.09, 2.09, 2.08, 2.07, 2.07, 2.06, 2.06, 2.06, 2.05, 2.05, 2.05, 2.04, 2.04, 2.04, 2.03, 2.03, 2.03, 2.03, 2.03, 2.02, 2.02, 2.02, 2.02, 2.02, 2.02, 2.02, 2.01, 2.01, 2.01, 2.01, 2.01, 2.01, 2.01, 2.01, 2.01, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 2.00, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.99, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.98, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.97, 1.96]
    tMax = len(tDistribution)
    tLimit = 1.96
    if (n > tMax):
        return tLimit
    return tDistribution[n]

def variance(population):
    n = 0
    mean = 0.0
    s = 0.0
    for x in population:
        n = n + 1
        delta = int(x) - mean
        mean = mean + (delta / n)
        s = s + delta * (int(x) - mean)

    # if you want to calculate std deviation
    # of a sample change this to "s / (n-1)"
    return s / (n)


### os.path replacement functions ###

def join(a,b):
    return a+'/'+b

def walk(top, topdown=True, onerror=None, followlinks=False):
    '''Updated version of os.path.walk that will follow symbolic links'''
    try:
        names = os.listdir(top)
    except os.error, err:
        if onerror is not None:
            onerror(err)
        return

    dirs, nondirs = [], []
    for name in names:
        if isdir(join(top, name)):
            dirs.append(name)
        else:
            nondirs.append(name)

    if topdown:
        yield top, dirs, nondirs
    for name in dirs:
        path = join(top, name)
        if followlinks or not islink(path):
            for x in walk(path, topdown, onerror, followlinks):
                yield x
    if not topdown:
        yield top, dirs, nondirs
                