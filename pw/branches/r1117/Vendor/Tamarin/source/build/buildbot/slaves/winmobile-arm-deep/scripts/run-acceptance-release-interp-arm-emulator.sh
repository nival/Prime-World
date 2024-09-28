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
# Calculate the change number and change id
##
. ../all/util-calculate-change.sh $1


##
# Download the AVMSHELL if it does not exist
##
echo "$buildsdir/$change-${changeid}/$platform/$shell_release_arm"
if [ ! -e "$buildsdir/$change-${changeid}/$platform/$shell_release_arm" ]; then
    echo "Download AVMSHELL"
    ../all/util-download.sh $vmbuilds/$branch/$change-${changeid}/$platform/$shell_release_arm $buildsdir/$change-${changeid}/$platform/$shell_release_arm
    ret=$?
    test "$ret" = "0" || {
        echo "Downloading of $shell_release_arm failed"
        rm -f $buildsdir/$change-${changeid}/$platform/$shell_release_arm
        exit 1
    }
    chmod +x $buildsdir/$change-${changeid}/$platform/$shell_release_arm
fi


##
# Download the latest asc.jar if it does not exist
##
if [ ! -e "$basedir/utils/asc.jar" ]; then
    echo "Download asc.jar"
    ../all/util-download.sh $ascbuilds/asc.jar $basedir/utils/asc.jar
    ret=$?
    test "$ret" = "0" || {
        echo "Downloading of asc.jar failed"
        rm -f $basedir/utils/asc.jar
        exit 1
    }
fi

echo ""
echo "Building ABC files using the following ASC version:"
echo "`java -jar $basedir/utils/asc.jar`"
echo ""

export CERUNNER=$basedir/build/buildbot/slaves/all/tools/wmrunner.exe
export AVM=$buildsdir/$change-${changeid}/$platform/$shell_release_arm
export ASC=$basedir/utils/asc.jar
export BUILTINABC=$basedir/core/$builtinABC
export SHELLABC=$basedir/shell/$shellABC

##
# Ensure that the system is clean and ready
##
cd $basedir/build/buildbot/slaves/scripts
../all/util-acceptance-clean.sh

cd $basedir/test/acceptance
# If available, use windows python (instead of cygwin python)
# Threading only works with windows python, $PYTHONWIN env variable must point to windows install
# $PYTHONWIN must be defined with forward slashes, e.g: c:/Python26/python.exe
if [ -z "$PYTHONWIN" ]
then
    py=python
else
    py=$PYTHONWIN
fi

echo "message: $py ./runtests.py  --vmargs=-Dinterp --config=arm-winmobile-emulator-tvm-release-Dinterp-deep --notimecheck"
$py ./runtests.py  --vmargs=-Dinterp --config=arm-winmobile-emulator-tvm-release-Dinterp-deep --notimecheck

##
# Ensure that the system is torn down and clean
##
cd $basedir/build/buildbot/slaves/scripts
../all/util-acceptance-teardown.sh

exit 0

