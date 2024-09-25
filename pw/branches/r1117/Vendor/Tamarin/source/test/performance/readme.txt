# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Initial Developer of the Original Code is: 
# dschaffe@adobe.com
#
# Portions created by the Initial Developer are Copyright (C) 2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

Instructions for running performance tests

- sunspider is a collection of tests from Apple http://webkit.org/perf/sunspider-0.9/sunspider.html, the tests are from computer
    shootout, and other sources
- jsbench is the port of javagrande2 tests to javascript, work done by UC Irvine, these tests take about 50-60 minutes, not run by default

the tests are meant to be run against tamarin-central and/or tamarin-tracing

usage example:
$ export AVM=c:/dev/tamarin-central/platform/win32/obj_8/shell/Release/avmplus.exe
$ export AVM2=c:/dev/tamarin-tracing/platform/win32/obj_8/shell/Release/avmplus.exe
$ export ASC=c:/dev/asc/asc.jar
$ export BUILTINABC=c:/dev/tamarin-central/core/builtin.abc
$ ./runtests.py


to specify the tests to run
$ ./runtests.py sunspider/
or 
$ ./runtests.py sunspider/s3d-cube.as

to skip tests edit testconfig.txt

testconfig.txt contains configuration settings:

example output:
$ ./runtests.py --config=jsbench
$ ./runtests.py --config=all