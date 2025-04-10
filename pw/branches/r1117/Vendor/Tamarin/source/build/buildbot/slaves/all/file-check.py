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
# The Original Code is [Open Source Virtual Machine].
#
# The Initial Developer of the Original Code is
# Adobe System Incorporated.
# Portions created by the Initial Developer are Copyright (C) 2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#    Adobe AS3 Team
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



import os
import os.path
from os.path import *
import stat
import re
import sys



def usage():
    print "file-check.py <dir>"
    print "Must pass in a directory <dir>."
    exit(1)

try:
    base_dir = sys.argv[1]
    if not isdir(base_dir):
        usage()
except:
    usage()


MPL_string="Version: MPL 1\.1/GPL 2\.0/LGPL 2\.1"
MPL_excludes = open(os.getcwd() + '/../all/mpl_excluded.txt').read().splitlines()
mpl_files = []

LineEnding_excludes = open(os.getcwd() + '/../all/lineending_excluded.txt').read().splitlines()
ending_file = []



def walktree (top = ".", depthfirst = True):
    names = os.listdir(top)
    if not depthfirst:
       yield top, names
    for name in names:
         try:
             st = os.lstat(os.path.join(top, name))
         except os.error:
             continue
         if stat.S_ISDIR(st.st_mode):
             for (newtop, children) in walktree (os.path.join(top, name), depthfirst):
                 yield newtop, children
    if depthfirst:
        yield top, names





for (basepath, children) in walktree(base_dir, False):
    for child in children:
        mpl_excluded = 0
        lineending_excluded = 0
        filename = os.path.join(basepath, child)
        # Ignore directory names
        if isfile(filename):
            for line in MPL_excludes:
                if line.startswith('#') or len(line)==0: # Skip the line if blank or is comment
                    continue
                if re.search(line, filename)!=None:
                    mpl_excluded = 1
                    break
                    
            for line in LineEnding_excludes:
                if line.startswith('#') or len(line)==0: # Skip the line if blank or is comment
                    continue
                if re.search(line, filename)!=None:
                    lineending_excluded = 1
                    break
        else: # Exclude directory 
            mpl_excluded = 1
            lineending_excluded = 1
        
        
        ############
        # MPL Check
        ############
        # These files have not been mpl_excluded and need to be checked
        if mpl_excluded == 0:
            MPLfound = 0
            file = open(filename)
            
            # Search the file for the MPL string
            for line in file:
                if re.search(MPL_string, line)!=None:
                    MPLfound = 1
                    break

            # No MPL string was found
            if MPLfound != 1:
                mpl_files.append(filename)

        ####################
        # Line Ending Checks
        ####################
        # These files have not been lineending_excluded and need to be checked
        if lineending_excluded == 0:
            unix_lines = 1
            file = open(filename)
            
            # Search the file for the MPL string
            for line in file:
                if re.search("\r\n", line)!=None:
                    unix_lines = 0
                    break

            # None UNIX line endings foune
            if unix_lines != 1:
                ending_file.append(filename)



if (len(mpl_files) != 0) or (len(ending_file) != 0):
    print "buildbot_status: WARNINGS"

print ""
print ""
print "MPL Issues:"
print "==========="
for file in mpl_files:
    print file.replace(base_dir, '')


print ""
print ""
print "Line Ending Issues:"
print "==================="
for file in ending_file:
    print file.replace(base_dir, '')
