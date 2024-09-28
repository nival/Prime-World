#!/usr/bin/env python

#* ***** BEGIN LICENSE BLOCK *****
#* Version: MPL 1.1/GPL 2.0/LGPL 2.1
#*
#* The contents of this file are subject to the Mozilla Public License Version
#* 1.1 (the "License"); you may not use this file except in compliance with
#* the License. You may obtain a copy of the License at
#* http://www.mozilla.org/MPL/
#*
#* Software distributed under the License is distributed on an "AS IS" basis,
#* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
#* for the specific language governing rights and limitations under the
#* License.
#*
#* The Original Code is [Open Source Virtual Machine.].
#*
#* The Initial Developer of the Original Code is
#* Adobe System Incorporated.
#* Portions created by the Initial Developer are Copyright (C) 2009
#* the Initial Developer. All Rights Reserved.
#*
#* Contributor(s):
#*   Adobe AS3 Team
#*
#* Alternatively, the contents of this file may be used under the terms of
#* either the GNU General Public License Version 2 or later (the "GPL"), or
#* the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
#* in which case the provisions of the GPL or the LGPL are applicable instead
#* of those above. If you wish to allow use of your version of this file only
#* under the terms of either the GPL or the LGPL, and not to allow others to
#* use your version of this file under the terms of the MPL, indicate your
#* decision by deleting the provisions above and replace them with the notice
#* and other provisions required by the GPL or the LGPL. If you do not delete
#* the provisions above, a recipient may use your version of this file under
#* the terms of any one of the MPL, the GPL or the LGPL.
#*
#* ***** END LICENSE BLOCK ***** */
#

# template for testcase in cmdline testsuite
# the testsuite is for testing the avmshell or other executables, works by creating a python script containing:
#  - the executable and any arguments
#  - optionally any input text to be sent to the process
#  - optionally a list of string regexp pattern matched against the stdout
#  - optionally a list of string regexp pattern matched against the stdin
#  - optionally the exit code to verify
#  
# the cmdutils.py contains utilities

# below is a template

# import the utilities from cmdutils.py
from cmdutils import *

# define a run() function, this will be called by the runtests.py
def run():
    # instantiate the RunTestLib class, it will contain environment vars AVM,AVMRD,ASC,GLOBALABC,SHELLABC
    r=RunTestLib()
    # create any number of testcases
#    r.run_test(
#                name='testname',
#                command='the executable and any arguments',
#  optional              expectedcode=1,
#  optional              expectedout=['Error #1502']
#  optional              expectederr=[]
#  optional              cwd='testdata'
#               )

    r.run_test(name='shell usage',
               command=r.avm,
               expectedcode=1,
               expectedout=['.*\[-Ojit\].*use jit always.*',
                            '.*\[--\] application args'
                            ]
               )

# by specifying a main can run this test individually
if __name__ == '__main__':
    r=RunTestLib()
#   if any testdata/.as files need to be compiled to .abc use the .compile method
#    r.compile("testdata/sleep.as")
    run()
