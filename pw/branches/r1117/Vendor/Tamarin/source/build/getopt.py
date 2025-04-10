# -*- Mode: Python; indent-tabs-mode: nil -*-
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
# The Original Code is [Open Source Virtual Machine].
#
# The Initial Developer of the Original Code is
# Adobe System Incorporated.
# Portions created by the Initial Developer are Copyright (C) 2005-2006
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

import sys
import re

_target = re.compile("^--target=(.*)$")
_host = re.compile("^--host=(.*)$")
_ignore = re.compile(r"^--(srcdir|cache-file)=")
_arg = re.compile(r"^--(enable|disable|with|without)-([\w-]+)(?:=(.*)|$)$")
_yes = re.compile("^(t|true|yes|y|1)$", re.I)
_no = re.compile("^(f|false|no|n|0)$", re.I)
_help = re.compile("^(-h|--help)$")


class Options:
    def __init__(self, argv = sys.argv):
        self._args = {}
        self.target = None
        self.host = None
        self.ignore_unknown_flags = False
        self.help = False
        self._allargs = {}


        unknown_args = []
        for arg in argv[1:]:
            m = _target.search(arg)
            if m:
                self.target = m.group(1)
                continue

            m = _host.search(arg)
            if m:
                self.host = m.group(1)
                continue

            if _ignore.search(arg) is not None:
                continue

            if arg == '--ignore-unknown-flags':
                self.ignore_unknown_flags = True
                continue

            if _help.search(arg) is not None:
                self.help = True
                continue

            m = _arg.search(arg)
            if not m:
                unknown_args.append(arg)
                continue

            (t, n, v) = m.groups()

            if type(v) == str:
                if _yes.search(v):
                    v = True
                if _no.search(v):
                    v = False

            if t == "enable" or t == "with":
                if v:
                    self._args[n] = v
                else:
                    self._args[n] = True

            elif t == "disable" or t == "without":
                if v:
                    raise Exception("--disable-" + n + " does not take a value.")

                self._args[n] = False

        if unknown_args and not self.ignore_unknown_flags:
            raise Exception("Unrecognized command line parameters: "
                            + ', '.join(unknown_args))


    def getBoolArg(self, name, default=None, remove=True):
        self._allargs[name] = default
        if not name in self._args:
            return default

        val = self._args[name]
        if remove:
            del self._args[name]

        if type(val) == bool:
            return val

        raise Exception("Unrecognized value for option '" + name + "'.")

    def getStringArg(self, name, default=None):
        self._allargs[name] = default
        if not name in self._args:
            return default

        val = self._args[name]
        del self._args[name]
        return val

    def peekBoolArg(self, name, default=None):
        return Options.getBoolArg(self,name,default,False)

    def peekStringArg(self, name, default=None):
        return Options.getStringArg(self,name,default,False)

    def getHelp(self):
        ret = ''
        for opt,default in self._allargs.iteritems():
            if default == True:
                ret += "%-35s [=enabled]\n" % ("--enable-%s" % opt)
            else:
                ret += "%-35s [=not enabled]\n" % ("--enable-%s" % opt)
        return ret



    def finish(self):
        if not self.ignore_unknown_flags:
            if len(self._args):
                raise Exception("Unrecognized command line parameters: " +
                                ", ".join(self._args.keys()))
