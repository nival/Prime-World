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

#
# This script automates the import of changes from
# nanojit-central to tamarin. 
#
# It works by noting revisions from nanojit-central, starting with the
# rev number in the file nanojit-import-rev, and then pulling those
# changes into the current repo.
#
# The last step updates the rev number file and checks it in.
#
# Note that the scripts will clobber the contents of the nanojit/
# directory so it is important that changes move in a single
# direction; i.e. from nanojit-central --> tamarin.
#
# You also need to ensure that nothing nasty happened during this
# import, and that you're the only person using the script when you
# push your changes.
#
# I would also recommend only running the script once per 'checkin',
# and not try to revert or otherwise manipulate the repo after the
# script has run.
#
# If nanojit-import-rev (which identifies a node in nanojit-central)
# gets corrupted (it really should never happen) you need to manually
# set it to the correct rev, not doing so will cause subsequent
# executions of this script to do very nasty things.
#
# I found the following command quite handy in displaying
# rev information: hg log --template "{rev} {node|short} {node}
# {author}\n", since the long form of the node is used in the file. 
# 
# If you see the error "mercurial.error.RepoError: unknown revision xxx", then
# the NJ repo you're attempting to pull from does not have the rev identified
# in the file nanojit-import-rev
# 
set -x
set -e

if [ $# -lt 1 ]
then
    echo "usage: $0 -f"
    echo "Pulls and commits the latest nanojit-central changes to this repo"
    exit 1
fi
if [ $1 != '-f' ]; then exit 1; fi

# random part of names
RAND="$RANDOM$RANDOM"

SRCDIR=$(hg root)
SCRIPTDIR=$SRCDIR/utils/nanojit-import
TMPDIR=/tmp/nj-$RAND

NANOJIT_CENTRAL_REV=$(cat $SCRIPTDIR/nanojit-import-rev)
NANOJIT_CENTRAL_REPO=http://hg.mozilla.org/projects/nanojit-central
NANOJIT_CENTRAL_LOCAL=$TMPDIR/nanojit-central

if [ $# -eq 2 ]
then
	# undocumented option ... be mighty careful when using could result in big problems
	NANOJIT_CENTRAL_REPO=$2
fi

mkdir $TMPDIR
rm -Rf $NANOJIT_CENTRAL_LOCAL $TMPDIR/import-splicemap $TMPDIR/import-revmap

hg clone $NANOJIT_CENTRAL_REPO $NANOJIT_CENTRAL_LOCAL

python $SCRIPTDIR/find-child.py \
    --src=$NANOJIT_CENTRAL_LOCAL \
    --dst=$SRCDIR \
    --start=$NANOJIT_CENTRAL_REV \
    --filemap=$SCRIPTDIR/nanojit-import-filemap \
    >$TMPDIR/import-splicemap

hg convert --config convert.hg.saverev=True \
    --config convert.hg.startrev=$(cut -d ' ' -f 1 $TMPDIR/import-splicemap) \
    --filemap=$SCRIPTDIR/nanojit-import-filemap \
    --splicemap=$TMPDIR/import-splicemap \
    $NANOJIT_CENTRAL_LOCAL \
    $SRCDIR \
    $TMPDIR/import-revmap

(cd $SRCDIR && \
    hg up)

(cd $NANOJIT_CENTRAL_LOCAL && \
    hg log -r tip --template "{node}\n") >$SCRIPTDIR/nanojit-import-rev

(cd $SRCDIR && \
    hg commit --message="Update nanojit-import-rev stamp." $SCRIPTDIR/nanojit-import-rev)

set +x
echo "This repo is now ready to push changes...ensure there is only a single head first"
echo "You may also want to clean-up the tmp directory at " $TMPDIR
