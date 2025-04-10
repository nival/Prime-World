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
# Make sure that there are no left over directories from previous compile
##
cd $basedir
test -d objdir-release && {
    echo Remove directory $basedir/objdir-release
    rm -rf $basedir/objdir-release
}

mkdir objdir-release

cd objdir-release

python ../configure.py --enable-shell --disable-eval

topsrcdir=`grep topsrcdir= Makefile | awk -F"=" '{print $2}'`
CXX=`grep CXX= Makefile | awk -F"=" '{print $2}'| sed 's/(/{/' | sed 's/)/}/' | sed 's/-nologo//'`
echo ""
echo compiler version: 
eval ${CXX} --version
echo ""
echo ""

make $make_opt clean
make $make_opt 
res=$?

test "$res" = "0" || {
    echo "build failed return value $res"
    exit $res
}
test -f "$basedir/objdir-release/shell/avmshell.map" || {
    echo "avmshell.map file was not created"
    exit 1
}

cd $basedir/utils
python ./sizereport.py --vmversion=$change --product=tamarin-redux --socketlog --prefix=message: --map=../objdir-release/shell/avmshell.map

echo url: "http://tamarin-builds.mozilla.org/report/index.cfm?mode=size&rollupname=sizereport&hostip=10.60.147.246&configbaseline=tamarin-redux&config1=tamarin-redux&config2=tamarin-redux&baselineBuild=1094&topBuild=${change}" size report

# We have had some problems in the past with deleting the objdir-release directory after running the 
# sizereport, give the script a couple of seconds to make sure that the python process completely
# shutsdown prior to trying to remove the directory
sleep 10

cd $basedir
test -d objdir-release && {
    echo Remove directory $basedir/objdir-release
    rm -rf $basedir/objdir-release
}
