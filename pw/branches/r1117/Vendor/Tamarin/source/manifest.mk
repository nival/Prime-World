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

# shell must be included here because that's where avmshell-features.h lives,
# and in shell builds it is included from platform/VMPI.h.  That's how it
# is supposed to be.
INCLUDES += \
  -I$(topsrcdir) \
  -I$(topsrcdir)/MMgc \
  -I$(topsrcdir)/core \
  -I$(topsrcdir)/pcre \
  -I$(topsrcdir)/eval \
  -I$(topsrcdir)/platform \
  -I$(topsrcdir)/other-licenses/zlib \
  -I$(topsrcdir)/shell \
  -I$(topsrcdir)/VMPI \
  $(NULL)

$(call RECURSE_DIRS,other-licenses/zlib)
$(call RECURSE_DIRS,VMPI)
$(call RECURSE_DIRS,MMgc)

ifdef ENABLE_TAMARIN
$(call RECURSE_DIRS,core pcre vprof)
ifeq (sparc,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (i686,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (x86_64,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (arm,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (powerpc,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (ppc64,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (mips,$(TARGET_CPU))
$(call RECURSE_DIRS,nanojit)
endif
ifeq (darwin,$(TARGET_OS))
$(call RECURSE_DIRS,platform/mac)
endif
ifeq (windows,$(TARGET_OS))
$(call RECURSE_DIRS,platform/win32)
endif
ifeq (linux,$(TARGET_OS))
$(call RECURSE_DIRS,platform/unix)
endif
ifeq (sunos,$(TARGET_OS))
$(call RECURSE_DIRS,platform/unix)
endif
endif

$(call RECURSE_DIRS,eval)
$(call RECURSE_DIRS,shell)

echo:
	@echo avmplus_CXXFLAGS = $(avmplus_CXXFLAGS)
	@echo avmplus_CXXSRCS = $(avmplus_CXXSRCS)
	@echo avmplus_CXXOBJS = $(avmplus_CXXOBJS)
	@echo avmplus_OBJS = $(avmplus_OBJS)
	@echo avmplus_NAME = $(avmplus_NAME)
