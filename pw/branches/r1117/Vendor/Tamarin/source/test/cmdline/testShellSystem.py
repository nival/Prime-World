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
import os

def run():
    r=RunTestLib()
    r.run_test('trace','%s testdata/trace1.abc'  % r.avm,expectedout=['single line','array line1,array line2','arg1 arg2 arg3','null'])
    r.run_test('write','%s testdata/write.abc' %r.avm,expectedout=['part1part2'])
    r.run_test('exit','%s testdata/exit.abc' %r.avm,expectedcode=5)
    r.run_test('readline','%s testdata/readline.abc' %r.avm,input='test input\n',expectedout=['line=test input'])
    r.run_test('exec','%s testdata/exec.abc' %r.avm,expectedout=['result=0'])
    r.run_test('argv 0','%s testdata/argv.abc --' %r.avm,expectedout=['argv.length=0'])
    r.run_test('argv n','%s testdata/argv.abc -- zero one two"' %r.avm,expectedout=['argv.length=3','argv\[0\]=zero','argv\[1\]=one','argv\[2\]=two'])

if __name__ == '__main__':
    r=RunTestLib()
    r.compile("testdata/exec.as")
    r.compile("testdata/exit.as")
    r.compile("testdata/readline.as")
    r.compile("testdata/trace1.as")
    r.compile("testdata/write.as")
    r.compile("testdata/argv.as")
    run()
