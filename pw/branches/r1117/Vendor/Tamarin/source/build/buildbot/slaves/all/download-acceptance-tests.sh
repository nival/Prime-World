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

cd $basedir/test/acceptance
echo "Removing old *.abc files"
find ./ -name "*.abc" -exec rm {} \;

## download acceptance test abc zip
echo "Download acceptance-tests-abcs.zip"
$basedir/build/buildbot/slaves/all/util-download.sh $ftp_asteam/builds/$branch/$change-${changeid}/acceptance-tests-abcs.zip $basedir/test/acceptance/acceptance-tests-abcs.zip 
res=$?

if [ "$res" = "0" -a -f "$basedir/test/acceptance/acceptance-tests-abcs.zip" ]
then

echo "unzipping acceptance tests"
unzip -o -q acceptance-tests-abcs.zip

else

echo "download acceptance-tests-abcs.zip failed, rebuilding tests" 

##
# Download the latest asc.jar
##
echo "Download asc.jar"
$basedir/build/buildbot/slaves/all/util-download.sh $ascbuilds/asc.jar $basedir/utils/asc.jar
ret=$?
test "$ret" = "0" || {
    echo "Downloading of asc.jar failed"
    exit 1
}

echo ""
echo "Building ABC files using the following ASC version:"
echo "`java -jar $basedir/utils/asc.jar`"
echo ""


export ASC=$basedir/utils/asc.jar
export BUILTINABC=$basedir/core/$builtinABC
export SHELLABC=$basedir/shell/$shellABC

echo "Rebuilding ABC test media"

if [[ $AVM == *ceremoteshell* ]]
then
    python ./runtests.py --rebuildtests -c arm-winmobile-tvm-release-arm 
else
    python ./runtests.py --rebuildtests 
fi

fi # manually rebuild tests


# clean up
rm $basedir/test/acceptance/acceptance-tests-abcs.zip
rm $basedir/test/acceptance/download.log
echo "finished"

exit 0

