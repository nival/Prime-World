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

# import the utilities from cmdutils.py
import os
from cmdutils import *

def run():
    r=RunTestLib()
    r.run_test(name='memstats',
               command="%s -memstats testdata/memstats.abc" % r.avm,
               expectedout=[
                            'gross stats',
                            'managed overhead',
                            'gross stats end',
                            'sweep\\([0-9]+\\) reclaimed [0-9]+ whole pages'
                            ]
               )
    if os.name!='nt':
        print "pyspy     requires windows named pipes, does not work with cygwin python or non-windows operating systems"
    else:
        failed=False
        try:
            import win32event
            import win32pipe
            import win32file
        except:
            failed=True
            print "pyspy failed to load python win32 extension  FAILED"
        if failed==False:
            os.putenv('MMGC_PROFILE','1')
            proc=r.run_command_async(command="%s testdata/memstats.abc" % r.avm,sleep=2)
# pyspy source       
            e = "MMgc::MemoryProfiler::DumpFatties"
            h = None
            try:
                h = win32event.OpenEvent(win32event.EVENT_MODIFY_STATE, False, e)
            except Exception:
                print "Error: No registered event: %s FAILED!" % e
                sys.exit(1)

            win32event.SetEvent(h)

            pipe = "\\\\.\\pipe\MMgc_Spy" 
            readHandle = None
            while True:
                try:
                    readHandle = win32file.CreateFile(pipe, win32file.GENERIC_READ, 0, None, win32file.OPEN_EXISTING, 0, None)
                    win32pipe.WaitNamedPipe(pipe, 100)
                except Exception:
                    pass
                if readHandle:
                    break

                while True:
                    try:
                        data = win32file.ReadFile(readHandle, 128)
                        sys.stdout.write(data[1])
                    except:
                        break

# by specifying a main can run this test individually
if __name__ == '__main__':
    r=RunTestLib()
    r.compile("testdata/memstats.as",None,"-d")
    run()
