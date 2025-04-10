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

import os
import sys
import build.process
import re

def writeFileIfChanged(path, contents):
    """Write some contents to a file. Avoids modifying the file timestamp if the file contents already match."""
    print "Generating " + path + "...",
    try:
        outf = open(path, "r")
        oldcontents = outf.read()
        outf.close()

        if oldcontents == contents:
            print "not changed"
            return
    except IOError:
        pass

    outf = open(path, "w")
    outf.write(contents)
    outf.close()
    print

# Figure out TARGET and CPU, a la config.guess
# Do cross-compilation in the future, which will require HOST_OS and perhaps
# other settings

def _configGuess():
    ostest = sys.platform
    cputest = build.process.run_for_output(['uname', '-m'])
    return _configSub(ostest, cputest)

def _configSub(ostest, cputest):
    if ostest.startswith('win') or ostest.startswith('cygwin'):
        os = 'windows'
    elif ostest.startswith('darwin') or ostest.startswith('apple-darwin'):
        os = 'darwin'
    elif ostest.startswith('linux') or ostest.startswith('pc-linux'):
        os = 'linux'
    elif ostest.startswith('sunos'):
        os = 'sunos'
    else:
        raise Exception('Unrecognized OS: ' + ostest)

    if re.search(r'^i(\d86|86pc|x86)$', cputest):
        cpu = 'i686'
    elif re.search('^(x86_64|amd64)$', cputest):
        cpu = 'x86_64'
    elif re.search('^(ppc64|powerpc64)$', cputest):
        cpu = 'ppc64'
    elif re.search('^(ppc|powerpc|Power Macintosh)$', cputest):
        cpu = 'powerpc'
    elif re.search('sun', cputest):
        cpu = 'sparc'
    elif re.search('arm', cputest):
        cpu = 'arm'
    elif re.search('mips', cputest):
        cpu = 'mips'
    else:
        raise Exception('Unrecognized CPU: ' + cputest)

    return (os, cpu)

class Configuration:
    def __init__(self, topsrcdir, options=None, sourcefile=None, objdir=None,
                 optimize=True, debug=False):
        self._topsrcdir = topsrcdir
        if objdir:
            self._objdir = objdir
        else:
            self._objdir = os.getcwd()

        self._optimize = optimize
        self._debug = debug
        self._host = _configGuess()
        self._target = self._host

        if sourcefile:
            srcfile = self._topsrcdir + "/" + sourcefile
            if not os.path.exists(srcfile):
                raise Exception("Source file " + srcfile + " doesn't exist.")

        objfile = self._objdir + "/" + sourcefile
        if os.path.exists(objfile):
            raise Exception("It appears you're trying to build in the source directory.  "
                            "(Source file " + objfile + " exists here.)  "
                            "You must use an object directory to build Tamarin.  "
                            "Create an empty directory, cd into it, and run this configure.py script from there.")


        if options:
            o = options.getStringArg("optimize")

            if o != None:
                self._optimize = o

            d = options.getStringArg("debug")
            if d != None:
                self._debug = d

            if options.host:
                hostcpu, hostos = options.host.split('-', 1)
                self._host = _configSub(hostos, hostcpu)

            if options.target:
                targetcpu, targetos = options.target.split('-', 1)
                self._target = _configSub(targetos, targetcpu)

        self._acvars = {
            'topsrcdir': self._topsrcdir,
            'HOST_OS': self._host[0],
            'TARGET_OS': self._target[0],
            'TARGET_CPU': self._target[1]
            }

        if self._host[0] == 'windows':
            self._acvars['topsrcdir'] = toMSYSPath(self._topsrcdir)

        if self._debug:
            self._acvars['ENABLE_DEBUG'] = 1


        self._compiler = 'GCC'
        self._acvars.update({
            'I_SUFFIX': 'i',
            'II_SUFFIX': 'ii',
            'OBJ_SUFFIX': 'o',
            'LIB_PREFIX': 'lib',
            'LIB_SUFFIX': 'a',
            'DLL_SUFFIX': 'so',
            'PROGRAM_SUFFIX': '',
            'USE_COMPILER_DEPS': 1,
            'EXPAND_LIBNAME' : '-l$(1)',
            'EXPAND_DLLNAME' : '-l$(1)',
            'OUTOPTION' : '-o ',
            'LIBPATH': '-L'
            })

        if self._target[0] == 'windows':
            self._compiler = 'VS'
            del self._acvars['USE_COMPILER_DEPS']
            
            static_crt = options.getBoolArg('static-crt')
            self._acvars.update({
                'OBJ_SUFFIX'   : 'obj',
                'LIB_PREFIX'   : '',
                'LIB_SUFFIX'   : 'lib',
                'DLL_SUFFIX'   : 'dll',
                'PROGRAM_SUFFIX': '.exe',
                'CPPFLAGS'     : (self._debug and '-MTd' or '-MT') or (self._debug and '-MDd' or '-MD'),
                'CXX'          : 'cl.exe -nologo',
                'CXXFLAGS'     : '-TP',
                'CC'           : 'cl.exe -nologo',
                'CFLAGS'       : '-TC',
                'DLL_CFLAGS'   : '',
                'AR'           : 'lib.exe -nologo',
                'LD'           : 'link.exe -nologo',
                'LDFLAGS'      : '',
                'MKSTATICLIB'  : '$(AR) -OUT:$(1)',
                'MKDLL'        : '$(LD) -DLL -OUT:$(1)',
                'MKPROGRAM'    : '$(LD) -OUT:$(1)',
                'EXPAND_LIBNAME' : '$(1).lib',
                'EXPAND_DLLNAME' : '$(1).lib',
                'OUTOPTION' : '-Fo',
                'LIBPATH'   : '-LIBPATH:'
                })
            if self._target[1] == "arm":
				self._acvars.update({'LDFLAGS' : '-NODEFAULTLIB:"oldnames.lib" -ENTRY:"mainWCRTStartup"'})
				
				if sys.platform.startswith('cygwin'):
					self._acvars.update({'ASM' : '$(topsrcdir)/build/cygwin-wrapper.sh armasm.exe -nologo -arch 5T'})
				else:
					self._acvars.update({'ASM' : 'armasm.exe -nologo -arch 5T'})
				
            if sys.platform.startswith('cygwin'):
                self._acvars.update({'CXX'          : '$(topsrcdir)/build/cygwin-wrapper.sh cl.exe -nologo'})
                self._acvars.update({'CC'           : '$(topsrcdir)/build/cygwin-wrapper.sh cl.exe -nologo'})

        # Hackery! Make assumptions that we want to build with GCC 3.3 on MacPPC
        # and GCC4 on MacIntel
        elif self._target[0] == 'darwin':
            self._acvars.update({
                'DLL_SUFFIX'   : 'dylib',
                'CPPFLAGS'     : '-pipe',
                'CXXFLAGS'     : '',
                'CFLAGS'       : '',
                'DLL_CFLAGS'   : '-fPIC',
                'LDFLAGS'      : '-framework CoreServices',
                'AR'           : 'ar',
                'MKSTATICLIB'  : '$(AR) cr $(1)',
                'MKDLL'        : '$(CXX) -dynamiclib -single_module -install_name @executable_path/$(1) -o $(1)',
                'MKPROGRAM'    : '$(CXX) -o $(1)'
                })

# -Wno-trigraphs -Wreturn-type -Wnon-virtual-dtor -Wmissing-braces -Wparentheses -Wunused-label  -Wunused-parameter -Wunused-variable -Wunused-value -Wuninitialized

            if 'CXX' in os.environ:
                self._acvars['CXX'] = os.environ['CXX']
            elif self._target[1] == 'i686':
                self._acvars['CXX'] = 'g++'
                self._acvars['CXXFLAGS'] += ' -arch i686 '
                self._acvars['LDFLAGS'] += ' -arch i686 '
            elif self._target[1] == 'x86_64':
                self._acvars['CXX'] = 'g++'
                self._acvars['CXXFLAGS'] += ' -arch x86_64 '
                self._acvars['LDFLAGS'] += ' -arch x86_64 '
            elif self._target[1] == 'powerpc':
                self._acvars['CXX'] = 'g++'
                self._acvars['CXXFLAGS'] += ' -arch ppc '
                self._acvars['LDFLAGS'] += ' -arch ppc '
            elif self._target[1] == 'ppc64':
                self._acvars['CXX'] = 'g++'
                self._acvars['CXXFLAGS'] += ' -arch ppc64 '
                self._acvars['LDFLAGS'] += ' -arch ppc64 '
            else:
                raise Exception("Unexpected Darwin processor.")
                
            if 'CC' in os.environ:
                self._acvars['CC'] = os.environ['CC']
            elif self._target[1] == 'i686':
                self._acvars['CC'] = 'gcc'
                self._acvars['CFLAGS'] += ' -arch i686 '
            elif self._target[1] == 'x86_64':
                self._acvars['CC'] = 'gcc'
                self._acvars['CFLAGS'] += ' -arch x86_64 '
            elif self._target[1] == 'powerpc':
                self._acvars['CC'] = 'gcc'
                self._acvars['CFLAGS'] += ' -arch ppc '
            elif self._target[1] == 'ppc64':
                self._acvars['CC'] = 'gcc'
                self._acvars['CFLAGS'] += ' -arch ppc64 '
            else:
                raise Exception("Unexpected Darwin processor.")

        elif self._target[0] == 'linux':
            self._acvars.update({
                'CPPFLAGS'     : os.environ.get('CPPFLAGS', ''),
                'CXX'          : os.environ.get('CXX', 'g++'),
                'CXXFLAGS'     : os.environ.get('CXXFLAGS', ''),
                'CC'           : os.environ.get('CC', 'gcc'),
                'CFLAGS'       : os.environ.get('CFLAGS', ''),
                'DLL_CFLAGS'   : '-fPIC',
                'LD'           : os.environ.get('LD', 'ar'),
                'LDFLAGS'      : os.environ.get('LDFLAGS', ''),
                'AR'           : os.environ.get('AR', 'ar'),
                'MKSTATICLIB'  : '$(AR) cr $(1)',
                'MKDLL'        : '$(CXX) -shared -o $(1)',
                'MKPROGRAM'    : '$(CXX) -o $(1)'
                })
            if self._target[1] == "mips":
                self._acvars.update({'CXXFLAGS' : '-EL -mips32r2 '})
                self._acvars.update({'LDFLAGS' : '-EL'})
                self._acvars.update({'zlib_EXTRA_CFLAGS' : '-EL'})
                
        elif self._target[0] == 'sunos':
	    if options.getBoolArg("gcc", False):
                self._acvars.update({
                'CPPFLAGS'     : os.environ.get('CPPFLAGS', '') + "-DBROKEN_OFFSETOF",
                'CXX'          : os.environ.get('CXX', 'g++'),
                'CXXFLAGS'     : os.environ.get('CXXFLAGS', ''),
                'CC'           : os.environ.get('CC', 'gcc'),
                'CFLAGS'       : os.environ.get('CFLAGS', ''),
                'DLL_CFLAGS'   : '-fPIC',
                'LD'           : 'ar',
                'LDFLAGS'      : '',
                'MKSTATICLIB'  : '$(AR) cr $(1)',
                'MKDLL'        : '$(CXX) -shared -o $(1)',
                'MKPROGRAM'    : '$(CXX) -o $(1)'
                })
 	    else:
                self._compiler = 'SunStudio'
                self._acvars.update({
                'I_SUFFIX': 'i',
                'II_SUFFIX': 'i',
                'CPPFLAGS'     : '',
                'CXX'          : 'CC',
                'CXXFLAGS'     : '',
                'CC'           : 'cc',
                'CFLAGS'       : '',
                'LD'           : 'ar',
                'LDFLAGS'      : '',
                'MKSTATICLIB'  : '$(AR) cr $(1)',
                'MKPROGRAM'    : '$(CXX) -o $(1)'
                })
        self._acvars['COMPILER'] = self._compiler

    def getObjDir(self):
        """Returns the build directory being configured."""
        return self._objdir

    def getHost(self):
        """Returns an (os, cpu) tuple of the host machine."""
        return self._host

    def getTarget(self):
        """Returns an (os, cpu) tuple of the target machine."""
        return self._target

    def getCompiler(self):
        """Returns the compiler in use, as a string.
Possible values are:
- 'GCC': the GNU Compiler Collection, including GCC and G++
- 'VS': Microsoft Visual Studio
- 'SunStudio': Sun Studio"""
        return self._compiler

    def getDebug(self):
        return self._debug

    def subst(self, name, value):
        self._acvars[name] = value

    _confvar = re.compile("@([^@]+)@")

    def generate(self, makefile):
        outpath = self._objdir + "/" + makefile

        contents = \
            "\n".join([k + "=" + str(v) \
                       for (k,v) in self._acvars.iteritems()]) + \
            "\n\ninclude $(topsrcdir)/build/config.mk\n" \
            "include $(topsrcdir)/manifest.mk\n" \
            "include $(topsrcdir)/build/rules.mk\n"

        writeFileIfChanged(outpath, contents)

def toMSYSPath(path):
    if sys.platform.startswith('cygwin'):
        return path
    elif path[1] != ':':
        raise ValueError("win32 path without drive letter! %s" % path)
    else:
        return '/%s%s' % (path[0], path[2:].replace('\\', '/'))
