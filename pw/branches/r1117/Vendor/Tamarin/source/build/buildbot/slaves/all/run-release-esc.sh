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



export scriptsdir=`pwd`
echo scriptsdir: $scriptsdir

##
# Download the AVMSHELL if it does not exist
##
if [ ! -e "$buildsdir/$change-${changeid}/$platform/$shell_release" ]; then
    echo "Download AVMSHELL"
    ../all/util-download.sh $vmbuilds/$branch/$change-${changeid}/$platform/$shell_release $buildsdir/$change-${changeid}/$platform/$shell_release
    ret=$?
    test "$ret" = "0" || {
        echo "Downloading of $shell_release failed"
        rm -f $buildsdir/$change-${changeid}/$platform/$shell_release
        exit 1
    }
    chmod +x $buildsdir/$change-${changeid}/$platform/$shell_release
fi

chmod +x $buildsdir/$change-${changeid}/$platform/$shell_release

echo ""
cp $buildsdir/$change-${changeid}/$platform/$shell_release $basedir/esc/bin/shell${shell_extension}
export AVM=$basedir/esc/bin/shell${shell_extension}
chmod +x $AVM

cd $basedir/esc/build
make clean

##
# First compilation of ESC
##
echo; echo "First compilation of ESC"; echo
make
ret=$?
test "$ret" = "0" || {
  echo "esc initial build failed..."
  exit 1
}
make clean




##
# Second compilation of ESC
##
echo; echo "Second compilation of ESC"; echo
make
ret=$?
test "$ret" = "0" || {
  echo "esc 2nd build failed..."
  exit 1
}
make clean



##
# Third compilation of ESC
##
echo; echo "Third compilation of ESC"; echo
make
ret=$?
test "$ret" = "0" || {
  echo "esc 3rd build failed..."
  exit 1
}
make clean



##
# Fourth compilation of ESC
##
echo; echo "Fourth compilation of ESC"; echo
make
ret=$?
test "$ret" = "0" || {
  echo "esc 4th build failed..."
  exit 1
}
make clean

