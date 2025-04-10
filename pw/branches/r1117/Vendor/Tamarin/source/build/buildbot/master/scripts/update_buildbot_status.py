#!/usr/bin/env python
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

import os.path,sys,getopt

basedir=os.path.dirname(sys.argv[0])
publichtml=os.path.abspath(basedir+"/../public_html")
statushtml=publichtml+"/status.html"
usage="""
-m --message= new message
-s --style= style from buildbot.css [Successstatus,Failurestatus]
"""

color='Passstatus'
message='Tree is open'
options='m:s:'
longOptions=['message=','style=']
try:
    opts, args=getopt.getopt(sys.argv[1:],options,longOptions)
except:
    print('usage:\n%s'%usage)
    sys.exit(1)
for (o,v) in opts:
    if o in ('-m','--message'):
        message=v
    elif o in ('-s','--style'):
        color=v

contents='<link href="buildbot.css" rel="stylesheet" type="text/css">\n<center><div class="%s">%s<br></div>\n<Center>' % (color,message)

open(statushtml,"w").write(contents)


