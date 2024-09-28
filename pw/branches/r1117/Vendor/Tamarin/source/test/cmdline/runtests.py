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

from cmdutils import *
from os import listdir
import testAvmShell,testDebugger,testShellSystem
class RunTests (RunTestLib):
    def compileAll(self):
        print "compile all"
        # for testShellSystem.py
        r.compile("testdata/exec.as")
        r.compile("testdata/exit.as")
        r.compile("testdata/readline.as")
        r.compile("testdata/trace1.as")
        r.compile("testdata/write.as")
        r.compile("testdata/argv.as")
        # for testAvmShell.py
        r.compile("testdata/sleep.as")
        # for testDebuggerShell.py
        r.compile("testdata/debug.as",None,"-d")
        # for testMemstats.py
        r.compile("testdata/memstats.as",None)
        # for testLanguage.py
        r.compile("testdata/rt_error.as",None)

    def runAll(self):
        list=os.listdir(".")
        for f in list:
            if re.match("test.*\.py$",f):
                if self.testconfig.has_key(f):
                    (type,notes)=self.testconfig[f]
                    if type=='skip':
                        print "%-30s SKIPPED, %s" % (f,notes)
                        continue
                cl=f[0:f.rindex('.')]
                exec "import " + cl
                print "%s.run()" % cl
                exec cl + ".run()"

if __name__ == "__main__":
    r=RunTests()
    r.compileAll()
    r.runAll()
