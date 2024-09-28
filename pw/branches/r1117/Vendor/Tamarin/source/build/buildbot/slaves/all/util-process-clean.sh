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


##
# Bring in the environment variables
##
. ./environment.sh


##
# Make sure that there are no processes running that should not be
##

for process in ${proc_names}
do
    prevPID=-0
    while [ 1 ]
    do
        if [[ `uname` == *-WOW64* ]]; then
            # If running on win64 make sure to install plist from 
            # http://technet.microsoft.com/en-us/sysinternals/bb896682.aspx
            PID=`pslist ${process} | tail -1 | awk '{print $2}'`
        elif [[ `uname` == *CYGWIN* ]]; then
            PID=`ps -aW | grep "${process}" | grep -v grep | grep -v ps |\
                 tail -1 | awk '{print $1}'`
        else
            PID=`ps -Ac | grep "${process}" | grep -v grep | grep -v ps |\
                 tail -1 | awk '{print $1}'`
        fi

        if [ "$prevPID" == "$PID" ]; then
            echo 
            echo "Unable to kill zombie ${process} process with pid $PID"
            echo "buildbot_status: WARNINGS"
            echo
            break
        fi
        if [ "" != "$PID" ]; then
            echo
            echo "There is a zombie ${process} [pid $PID] still running."
            echo "Attempting to kill process $PID"
            echo "message: zombie ${process} process found"
            echo "buildbot_status: WARNINGS"
            echo

            if [[ `uname` == *-WOW64* ]]; then
                echo "`pslist $PID`"
                # bash: kill: (####) - No such process" error using kill 
                # command in Cygwin
                # http://www-01.ibm.com/support/docview.wss?uid=swg21205470
                /bin/kill -f $PID
            elif [[ `uname` == *CYGWIN* ]]; then
                echo "`ps -W -p $PID`"
                # bash: kill: (####) - No such process" error using kill 
                # command in Cygwin
                # http://www-01.ibm.com/support/docview.wss?uid=swg21205470
                /bin/kill -f $PID
            else
                echo "`ps -p $PID`"
                kill -9 $PID
            fi
            
            prevPID=$PID
            sleep 10
        else
            break
        fi
    done
done

