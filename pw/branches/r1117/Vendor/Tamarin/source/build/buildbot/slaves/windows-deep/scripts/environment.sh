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
# Set any variables that my be needed higher up the chain
##
export shell_extension=.exe

##
# Bring in the BRANCH environment variables
##
. ../all/environment.sh

export platform=windows
workdir=`pwd`
export basedir=`cygpath -m ${workdir}/../../../..`
export buildsdir=`cygpath -m ${basedir}/../builds`

export shell_release_cov=avmshell_cov.exe
export shell_release_debugger_cov=avmshell_s_cov.exe
export shell_debug_cov=avmshell_d_cov.exe
export shell_debug_debugger_cov=avmshell_sd_cov.exe
export shell_selftest_cov=avmshell_test_cov.exe

bullseyedir="/c/Progra~1/BullseyeCoverage/bin"


VS_HOME_PATH="/c/Program Files/Microsoft Visual Studio 9.0"
VS_HOME="c:\Program Files\Microsoft Visual Studio 9.0"

# ${PREPATH} if it exists will be the first thing in the path,
# this is needed for code coverage.
export PATH="${PREPATH}:$VS_HOME_PATH/Common7/IDE:$VS_HOME_PATH/VC/bin:$VS_HOME_PATH\Common7\Tools:$VS_HOME_PATH/VC/VCPackages:$PATH"
export INCLUDE="c:\Program Files\Microsoft SDKs\Windows\v6.0\Include;$VS_HOME\VC\atlmfc\include;$VS_HOME\VC\include;"
export LIB="c:\Program Files\Microsoft SDKs\Windows\v6.0\Lib;$VS_HOME\VC\atlmfc\lib;$VS_HOME\VC\lib"
export LIBPATH="c:\Program Files\Microsoft SDKs\Windows\v6.0\Lib;$VS_HOME\VC\atlmfc\lib;$VS_HOME\VC\lib;"

## Used by make in the build scripts
export make_opt="-j3"

