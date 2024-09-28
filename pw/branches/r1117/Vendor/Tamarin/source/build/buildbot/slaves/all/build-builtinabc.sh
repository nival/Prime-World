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

echo basedir=$basedir
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
echo "Building builtin.abc file using the following ASC version:"
echo "`java -jar $basedir/utils/asc.jar`"
echo ""



##
# Remove the old builtin.abc
##
cd $basedir/core
test -f ./$builtinABC && {
    rm $builtinABC
}

##
# Build the builtin.abc
##
echo "building builtin.abc"
export ASC=$basedir/utils/asc.jar
python ./builtin.py
ret=$?
test "$ret" = "0" || {
    echo "builtin.py failed"
    hg revert builtin*.cpp builtin*.h
    exit 1
}

cd $basedir
hg status

##
# Diff the builtin.cpp and builtin.h files
##

test -f $basedir/build/buildbot/slaves/scripts/builtin.diff && {
    rm $basedir/build/buildbot/slaves/scripts/builtin.diff
}
hg diff core/builtin.cpp
hg diff core/builtin.cpp > $basedir/build/buildbot/slaves/scripts/builtin.diff
cd $basedir/build/buildbot/slaves/scripts
../all/util-builtin-verify.py $basedir/build/buildbot/slaves/scripts/builtin.diff

cd $basedir
test -f $basedir/build/buildbot/slaves/scripts/builtin.diff && {
    rm $basedir/build/buildbot/slaves/scripts/builtin.diff
}
hg diff core/builtin.h
hg diff core/builtin.h > $basedir/build/buildbot/slaves/scripts/builtin.diff
cd $basedir/build/buildbot/slaves/scripts
../all/util-builtin-verify.py $basedir/build/buildbot/slaves/scripts/builtin.diff

cd $basedir
hg revert core/builtin.cpp core/builtin.h


mkdir -p $buildsdir/${change}-${changeid}
cp $basedir/core/$builtinABC $buildsdir/${change}-${changeid}/$builtinABC
chmod 777 $buildsdir/${change}-${changeid}/$builtinABC



##
# Remove the old shell_toplevel.abc
##
cd $basedir/shell
test -f ./$shellABC && {
    rm $shellABC
}

##
# Build the shell_toplevel.abc
##

echo "building shell_toplevel.abc"
export ASC=$basedir/utils/asc.jar
python ./shell_toplevel.py
ret=$?
test "$ret" = "0" || {
    echo "shell_toplevel failed"
    exit 1
}

cd $basedir
hg status

##
# Diff the shell_toplevel.cpp and shell_toplevel.h files
##
test -f $basedir/build/buildbot/slaves/scripts/builtin.diff && {
    rm $basedir/build/buildbot/slaves/scripts/builtin.diff
}
hg diff shell/shell_toplevel.cpp
hg diff shell/shell_toplevel.cpp > $basedir/build/buildbot/slaves/scripts/builtin.diff
cd $basedir/build/buildbot/slaves/scripts
../all/util-builtin-verify.py $basedir/build/buildbot/slaves/scripts/builtin.diff

cd $basedir
test -f $basedir/build/buildbot/slaves/scripts/builtin.diff && {
    rm $basedir/build/buildbot/slaves/scripts/builtin.diff
}
hg diff shell/shell_toplevel.h
hg diff shell/shell_toplevel.h > $basedir/build/buildbot/slaves/scripts/builtin.diff
cd $basedir/build/buildbot/slaves/scripts
../all/util-builtin-verify.py $basedir/build/buildbot/slaves/scripts/builtin.diff

cd $basedir
hg revert shell/shell_toplevel.cpp shell/shell_toplevel.h

mkdir -p $buildsdir/${change}-${changeid}
cp $basedir/shell/$shellABC $buildsdir/${change}-${changeid}/$shellABC
chmod 777 $buildsdir/${change}-${changeid}/$shellABC

hg status

exit 0

