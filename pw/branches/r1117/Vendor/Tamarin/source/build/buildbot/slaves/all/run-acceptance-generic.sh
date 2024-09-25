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

showhelp ()
{
    echo ""
    echo "usage: run-acceptance-generic.sh <change> <filename> <vmargs> <config> <scriptargs>"
    echo "  <change>     build number of shell to test"
    echo "  <filename>   name of the shell, do not include file extenstion"
    echo "  <vmargs>     vmargs to be passed or empty quoted string"
    echo "  <config>     custom config string to be passed to runtests.py"
    echo "               or an empty string"
    echo "  <scriptargs> (optional) additional runtests.py args to be passed, can be"
    echo "               args and test/directories to run, value is appended to call"
    exit 1
}

if [ "$#" -lt 4 ]
then
    echo "not enough args passed"
    showhelp
fi

filename=$2
vmargs=$3
config=$4

# assign the remaining positional params to scriptargs
shift 4
scriptargs=$*


export shell=$filename$shell_extension


##
# Download the AVMSHELL if it does not exist
##
if [ ! -e "$buildsdir/$change-${changeid}/$platform/$shell" ]; then
    echo "Download AVMSHELL: ${shell}"
    ../all/util-download.sh $vmbuilds/$branch/$change-${changeid}/$platform/$shell $buildsdir/$change-${changeid}/$platform/$shell
    ret=$?
    test "$ret" = "0" || {
        echo "Downloading of $shell failed"
        rm -f $buildsdir/$change-${changeid}/$platform/$shell
        exit 1
    }
    chmod +x $buildsdir/$change-${changeid}/$platform/$shell
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
echo "Missing media will be compiled using the following ASC version:"
echo "`java -jar $basedir/utils/asc.jar`"
echo ""



export ASC=$basedir/utils/asc.jar
export BUILTINABC=$basedir/core/$builtinABC
export SHELLABC=$basedir/shell/$shellABC
export AVM=$buildsdir/$change-${changeid}/$platform/$shell

echo AVM=$AVM
echo "`$AVM`"
test -f $AVM || {
  echo "ERROR: $AVM not found"
  exit 1
}
echo; echo "AVM built with the following options:"
echo "`$AVM -Dversion`"


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

if [ "$config" != "" ]
then
    echo "message: $py ./runtests.py --vmargs=\"${vmargs}\" --config=${config} --notimecheck ${scriptargs}"
    $py ./runtests.py  --vmargs="${vmargs}" --config=${config} --notimecheck ${scriptargs}
else
    echo "message: $py ./runtests.py --vmargs=\"${vmargs}\" --notimecheck ${scriptargs}" 
    $py ./runtests.py  --vmargs="${vmargs}" --notimecheck ${scriptargs}
fi

##
# Ensure that the system is torn down and clean
##
cd $basedir/build/buildbot/slaves/scripts
../all/util-acceptance-teardown.sh

exit 0


