#!/bin/bash
#  ***** BEGIN LICENSE BLOCK *****
#  Version: MPL 1.1/GPL 2.0/LGPL 2.1
# 
#  The contents of this file are subject to the Mozilla Public License Version
#  1.1 (the "License"); you may not use this file except in compliance with
#  the License. You may obtain a copy of the License at
#  http://www.mozilla.org/MPL/
# 
#  Software distributed under the License is distributed on an "AS IS" basis,
#  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
#  for the specific language governing rights and limitations under the
#  License.
# 
#  The Original Code is [Open Source Virtual Machine.].
# 
#  The Initial Developer of the Original Code is
#  Adobe System Incorporated.
#  Portions created by the Initial Developer are Copyright (C) 2009
#  the Initial Developer. All Rights Reserved.
# 
#  Contributor(s):
#    Adobe AS3 Team
# 
#  Alternatively, the contents of this file may be used under the terms of
#  either the GNU General Public License Version 2 or later (the "GPL"), or
#  the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
#  in which case the provisions of the GPL or the LGPL are applicable instead
#  of those above. If you wish to allow use of your version of this file only
#  under the terms of either the GPL or the LGPL, and not to allow others to
#  use your version of this file under the terms of the MPL, indicate your
#  decision by deleting the provisions above and replace them with the notice
#  and other provisions required by the GPL or the LGPL. If you do not delete
#  the provisions above, a recipient may use your version of this file under
#  the terms of any one of the MPL, the GPL or the LGPL.
# 
#  ***** END LICENSE BLOCK ****
(set -o igncr) 2>/dev/null && set -o igncr; # comment is needed

cwd=`pwd`
cd $basedir
if [ -d .hg ];
then
    withhash=`echo $1 | grep :`
    # nothing passed in
    if [ "$1" == "" ]; then
        change=`hg identify -n | awk -F+ '{print $1}'`
        echo "change number not passed using tip: $change"
        changeid=`hg log -r $change | head -n 1 | awk -F: '{print $3}'`
        
    # only revision passed in
    elif [ "$withhash" == ""  ]; then
        change=$1
        echo "change number passed: $change"
        changeid=`hg log -r $change | head -n 1 | awk -F: '{print $3}'`
    
    # revision and changeid passed in
    else
        change=${1%:*}
        changeid=${1#*:}
        echo "change and changeid number passed: $change $changeid"
    fi
    
    echo "running $platform build for change: $change changeid: $changeid"


else
    change=$1
    test "$change" = "" && {
        change=`p4 changes -m 1 //depot/main/FlashRuntime/Main/code/third_party/avmplus/... | grep Change | awk '{print $2}'`
        echo "change number no passed using tip: $change"
    }
    change=`echo $change | awk -F: '{print $1}'`
    changeid=

fi

# Move back into the default location
cd $cwd
