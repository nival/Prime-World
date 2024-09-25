/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

The flashrunner tool converts an abc file to a swf. The script builds and runs
the swf from an abc file.  When the swf is run the output is sent over a socket
and printed to stdout.  

Setup:
Follow one-time setup instructions below.

test the setup by running the flashrunner.sh directly:

$ <tamarin>/test/utils/flashrunner/flashrunner.sh hello.abc
- expected output should be print statement output  e.g. 'hello'
- can edit flashrunner.sh set delay=3 (# seconds to pause the player before sending results over socket and closing)
   will see any print statements in the player player

set AVM to flashrunner.sh and call runtests on a set of tests.

$ export AVM=<tamarin>/test/util/flashrunner/flashrunner.sh
$ cd <tamarin>/test/acceptance
$ ./runtests.py as3/AbcDecoder

One time setup:

the following environment variables are required:
ASC - full path to asc.jar
PLAYERGLOBALABC - full path to playerglobal.abc
BUILTINABC - full path to global.abc 
    (e.g. export BUILTINABC=c:/hg/tamarin-redux/core/builtin.abc)
player -
    full path to standalone player executable
    or full path to browser
    or ff or firefox - default firefox path
    or ie or internetexplorer - default ie path
    or safari - default safari browser 

Windows only:
PYTHONWIN - set to full path for native windows python 
    (e.g. export PYTHONWIN=c:/python26/python.exe


to enable local networking set the tamarin directory to your FlashPlayerTrust
    windows: c:/Windows/system32/Macromed/Flash/FlashPlayerTrust
    mac: /Library/Application Support/Macromedia/FlashPlayerTrust
    linux: edit /etc/adobe/FlashPlayerTrust
    in the trust dir create a .cfg file with the path to your tamarin repository:
       test.cfg:
       c:/hg/tamarin-redux

For firefox to disable the Resume previous state warning
    type about:config in url
    set browser.sessionstore.resume_from_crash to false

