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

import getopt, re, string
from sys import argv, exit
import os.path
from os.path import *


def usage():
    print "util-builint-verify.py <filepath>"
    print "Must pass in a path to a diff file <filepath>."
    exit(1)

try:
    diff_file = argv[1]
    if not isfile(diff_file):
        usage()
except:
    usage()
    
f = open(diff_file)
old=[]
new=[]
filename=""
for line in f.readlines():
    # Skip any of these lines:
    #    - where the diff is: @@ -189,20 +189,6 @@ ....
    #    - file1 of diff: --- a/....
    #    - file2 of diff: +++ a/....
    #    - abcdata chunk
    if not re.search('(\d{1,3},+[ \t])', line) \
       and not line.startswith("@@") \
       and not line.startswith("+++") \
       and not line.startswith("---"):
            
        if line.startswith("+"):
            new.append(line[1:])
        if line.startswith("-"):
            old.append(line[1:])

    if line.startswith("+++ b/"):
        filename = line[5:].split()[0]

new.sort()
old.sort()


diff=False
# Compare the changed lines to make sure the are the same
for index, item in enumerate(new):
    if item != old[index]:
        diff=True

print ""
print "Testing %s" % filename
if diff:
    print "Diff was found in the file."
    print "buildbot_status: WARNINGS"
else:
    print "No diff was found in the file."
print ""
