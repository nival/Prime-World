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
# Run any slave specific code PRE performance
##
. ./run-performance-pre.sh


#specify special release  build
shell_release=$shell_release_vprof

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





export AVM=$buildsdir/$change-${changeid}/$platform/${shell_release}
export ASC=$basedir/utils/asc.jar
export BUILTINABC=$basedir/core/$builtinABC
export SHELLABC=$basedir/shell/$shellABC


echo ""
echo AVM=$AVM
echo "`$AVM`"
echo; echo "AVM built with the following options:"
echo "`$AVM -Dversion`"
echo ""


##
# Ensure that the system is clean and ready
##
cd $basedir/build/buildbot/slaves/scripts
../all/util-acceptance-clean.sh


cd $basedir/test/performance
find ./ -name "*.abc" -exec rm {} \;

result="0"
resultmessage=""

# If a second parameter (after revision is given) then only run those tests
if [ $2 ]
then
    echo ""
    echo "===========   Custom Run: $2   ==========="
    # determine what iter to apply based on testname
    if [[ $2 == jsbench* ]] ; then
        # skip js
        exit 0
    elif [[ $2 == sunspider* ]] ; then
        vmargs=""
        iter=3
    elif [[ $2 == v8* ]] ; then
        # skip v8
        exit 0
    else
        vmargs=""
        iter=3
    fi
    python ./runtests.py -r ${branch}-vprof --perfm -k -f -i $iter --vmargs="$vmargs" $2
    test "$?" = "0" || { 
        result="1"; 
        resultmessage="$2 time test run failed. " 
    }
else
    # standard performance run
    #echo ""
    #echo "===========   JSBench   ==========="
    #python ./runtests.py --vmargs=${jit} --config=jsbench --perfm -r ${branch}-vprof -k -f -i 3
    #test "$?" = "0" || { 
    #    result="1"; 
    #    resultmessage="$resultmessage \njsbench time test run failed. " 
    #}
    
    echo ""
    echo "===========   Misc   ==========="
    python ./runtests.py --vmargs=${jit} --config=misc --perfm -r ${branch}-vprof -k -f -i 3
    test "$?" = "0" || { 
        result="1"; 
        resultmessage="$resultmessage \nmisc time test run failed. " 
    }
    
    echo ""
    echo "===========   SunSpider   ==========="
    python ./runtests.py --vmargs=${jit} --config=sunspider --perfm -r ${branch}-vprof -k -f -i 3
    test "$?" = "0" || { 
        result="1"; 
        resultmessage="$resultmessage \nsunspider test run failed. " 
    }
fi

export time_url="http://tamarin-builds.mozilla.org/report/index.cfm?mode=time&ratio=true&baselinebuild=${baselineBuildTimeVprofJIT}&configbaseline=${baselineConfigTimeVprofJIT}&config1=${configVprofJIT}&config2=${configVprofJIT}&topBuild=${change}&hostip=${hostip}"

echo ""
echo ""
echo "url: ${time_url} time report"

test -f results.log && rm results.log
wget -O results.log -q ${time_url}
retry="0"
perfchg=""
while true
 do
  test -f results.log && {
    sleep 10
    perfchg=`cat results.log | grep -m1 "perfchange_ratio_time:" | awk -F"perfchange_ratio_time:" '{print $2}' | awk '{print $1}'`
    break
  }
  retry=`echo $retry | awk '{ print $1+1 }'`
  test "$retry" = "20" && break
  sleep 1
done
echo "perfchange: ${perfchg}%"

##
# Run any slave specific code POST performance
##
cd $basedir/build/buildbot/slaves/scripts/
. ./run-performance-post.sh

##
# Ensure that the system is torn down and clean
##
cd $basedir/build/buildbot/slaves/scripts
../all/util-acceptance-teardown.sh

test "$result" = "0" && resultmessage="performance tests passed"
echo -e "message: $resultmessage"
exit $result
