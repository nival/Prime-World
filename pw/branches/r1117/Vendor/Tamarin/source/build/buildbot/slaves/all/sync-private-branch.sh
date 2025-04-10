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
# Calculate the change number and change id
##
. ../all/util-calculate-change.sh $1


mkdir -p $buildsdir/$change-${changeid}/

archive_file=$buildsdir/$change-${changeid}/tamarin-private.zip

test -f $archive_file || {
  wget --output-document=$archive_file http://10.60.48.47/hg/tamarin-redux-private/archive/tip.zip
}

## Clean up the old zip contents if it exists
cd $buildsdir/$change-${changeid}/
rm -rf tamarin-redux-private*

## The files will unzip into a tamarin-redux-private-HASH directory
## so just cd into tamarin-redux-private* since we don't know the hash
unzip -q $archive_file
cd tamarin-redux-private*

## Remove the .hg info file so that it is not copied into the main repo
rm .hg_archival.txt

## Copy the private repo onto the public repo
echo "===================="
echo ""
echo "Applying additional files to the repository"
echo ""
cp -Rv ./ $basedir
echo ""

## Return back to the scripts direcotry
cd $basedir/build/buildbot/slaves/scripts
