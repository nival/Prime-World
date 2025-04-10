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



# Since all is good, lets post the builds
ssh stage.mozilla.org "~/setupbuilds.sh $branch $change-$changeid"


# Release
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$platform/$shell_release $scp_mozilla/$branch/$change-${changeid}/$platform/$shell_release
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$platform/$shell_release $shell_release"

# Release-wordcode
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$platform/$shell_release_wordcode $scp_mozilla/$branch/$change-${changeid}/$platform/$shell_release_wordcode
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$platform/$shell_release_wordcode $shell_release_wordcode"

# Release_Debugger
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$platform/$shell_release_debugger $scp_mozilla/$branch/$change-${changeid}/$platform/$shell_release_debugger
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$platform/$shell_release_debugger $shell_release_debugger"

# Debug
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$platform/$shell_debug $scp_mozilla/$branch/$change-${changeid}/$platform/$shell_debug
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$platform/$shell_debug $shell_debug"

#Debug_Debugger
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$platform/$shell_debug_debugger $scp_mozilla/$branch/$change-${changeid}/$platform/$shell_debug_debugger
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$platform/$shell_debug_debugger $shell_debug_debugger"

# SelfTest
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$platform/$shell_selftest $scp_mozilla/$branch/$change-${changeid}/$platform/$shell_selftest
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$platform/$shell_selftest $shell_selftest"

# Release-vprof
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$platform/$shell_release_vprof $scp_mozilla/$branch/$change-${changeid}/$platform/$shell_release_vprof
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$platform/$shell_release_vprof $shell_release_vprof"

# builtin.abc
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$builtinABC $scp_mozilla/$branch/$change-${changeid}/$builtinABC
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$builtinABC $builtinABC"

# toplevel.abc
. ../all/util-upload-scp-mozilla.sh $buildsdir/$change-${changeid}/$shellABC $scp_mozilla/$branch/$change-${changeid}/$shellABC
echo "url: ftp://ftp.mozilla.org/pub/js/tamarin/builds/$branch/$change-${changeid}/$shellABC $shellABC"

