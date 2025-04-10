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

GARBAGE :=

VPATH = $(topsrcdir)

curdir := .
srcdir := $(topsrcdir)

COMPILE_CPPFLAGS = $(CPPFLAGS) $(APP_CPPFLAGS)
COMPILE_CXXFLAGS = $(CXXFLAGS) $(APP_CXXFLAGS)
COMPILE_CFLAGS = $(CFLAGS) $(APP_CFLAGS)

ifdef ENABLE_DEBUG
COMPILE_CPPFLAGS += $(DEBUG_CPPFLAGS)
COMPILE_CXXFLAGS += $(DEBUG_CXXFLAGS)
COMPILE_CFLAGS += $(DEBUG_CFLAGS)
LDFLAGS += $(DEBUG_LDFLAGS)
else
COMPILE_CPPFLAGS += $(OPT_CPPFLAGS)
COMPILE_CXXFLAGS += $(OPT_CXXFLAGS)
COMPILE_CFLAGS += $(OPT_CFLAGS)
endif

ifdef MACOSX_DEPLOYMENT_TARGET
export MACOSX_DEPLOYMENT_TARGET
endif

GLOBAL_DEPS := Makefile

all::

# Usage: from within RECURSE_DIRS
# Variables:
#   $(1) = $(curdir)
#   $(2) = subdirectory
# Note: positional parameters passed to $(call) are expanded "early". This is
# the magic that sets and revert $(curdir) and $(srcdir) properly.
define RECURSE_DIR
curdir := $(1)/$(2)
srcdir := $(topsrcdir)/$$(curdir)
include $(topsrcdir)/$$(curdir)/manifest.mk
curdir := $(1)
endef

# Usage: $(call REAL_RECURSE_DIRS,$(DIRS),$(curdir))
define REAL_RECURSE_DIRS
$(foreach dir,$(1),$(eval $(call RECURSE_DIR,$(2),$(dir))))
endef

# Usage: $(call RECURSE_DIRS,$(DIRS)))
define RECURSE_DIRS
$(call REAL_RECURSE_DIRS,$(1),$(curdir))
endef

# Usage: $(eval $(call THING_SRCS,$(thingname)))
define THING_SRCS
$(1)_CPPFLAGS ?= $(COMPILE_CPPFLAGS)
$(1)_CXXFLAGS ?= $(COMPILE_CXXFLAGS)
$(1)_CFLAGS ?= $(COMPILE_CFLAGS)
$(1)_CPPFLAGS += $($(1)_EXTRA_CPPFLAGS)
$(1)_CXXFLAGS += $($(1)_EXTRA_CXXFLAGS)
$(1)_CFLAGS += $($(1)_EXTRA_CFLAGS)
$(1)_INCLUDES += $(INCLUDES)
$(1)_DEFINES += $(DEFINES)

$(1)_CXXOBJS = $$($(1)_CXXSRCS:%.cpp=%.$(OBJ_SUFFIX))

$(1)_COBJS = $$($(1)_CSRCS:%.c=%.$(OBJ_SUFFIX))

$(1)_ASMOBJS = $$($(1)_ASMSRCS:%.armasm=%.$(OBJ_SUFFIX))

GARBAGE += \
  $$($(1)_CXXOBJS) \
  $$($(1)_COBJS) \
  $$($(1)_ASMOBJS) \
  $$($(1)_CXXOBJS:.$(OBJ_SUFFIX)=.$(II_SUFFIX)) \
  $$($(1)_CXXOBJS:.$(OBJ_SUFFIX)=.deps) \
  $$($(1)_COBJS:.$(OBJ_SUFFIX)=.$(II_SUFFIX)) \
  $$($(1)_COBJS:.$(OBJ_SUFFIX)=.deps) \
  $(NULL)

$$($(1)_CXXOBJS:.$(OBJ_SUFFIX)=.$(II_SUFFIX)): %.$(II_SUFFIX): %.cpp $$(GLOBAL_DEPS)
	@test -d $$(dir $$@) || mkdir -p $$(dir $$@)
	@echo "Compiling $$*"
	@$(CXX) -E $$($(1)_CPPFLAGS) $$($(1)_CXXFLAGS) $$($(1)_DEFINES) $$($(1)_INCLUDES) $$< > $$@
	@$(PYTHON) $(topsrcdir)/build/dependparser.py $$*.deps < $$@ > /dev/null

$$($(1)_CXXOBJS): %.$(OBJ_SUFFIX): %.$(II_SUFFIX) $$(GLOBAL_DEPS)
	@$(CXX) $(OUTOPTION)$$@ $$($(1)_CPPFLAGS) $$($(1)_CXXFLAGS) $$($(1)_DEFINES) $$($(1)_INCLUDES) -c $$<

$$($(1)_COBJS:.$(OBJ_SUFFIX)=.$(I_SUFFIX)): %.$(I_SUFFIX): %.c $$(GLOBAL_DEPS)
	@test -d $$(dir $$@) || mkdir -p $$(dir $$@)
	@echo "Compiling $$*"
	@$(CC) -E $$($(1)_CPPFLAGS) $$($(1)_CFLAGS) $$($(1)_DEFINES) $$($(1)_INCLUDES) $$< > $$@
	@$(PYTHON) $(topsrcdir)/build/dependparser.py $$*.deps < $$@ > /dev/null

$$($(1)_COBJS): %.$(OBJ_SUFFIX): %.$(I_SUFFIX) $$(GLOBAL_DEPS)
	@$(CC) $(OUTOPTION)$$@ $$($(1)_CPPFLAGS) $$($(1)_CFLAGS) $$($(1)_DEFINES) $$($(1)_INCLUDES) -c $$<

$$($(1)_ASMOBJS): %.$(OBJ_SUFFIX): %.armasm $$(GLOBAL_DEPS)
	$(ASM) -o $$@ $$($(1)_ASMFLAGS) $$<
	
$(1).thing.pp: FORCE
	@$(PYTHON) $(topsrcdir)/build/calcdepends.py $$@ $$($(1)_CXXOBJS:.$(OBJ_SUFFIX)=.$(II_SUFFIX)) $$($(1)_COBJS:.$(OBJ_SUFFIX)=.$(I_SUFFIX))

include $(1).thing.pp

endef # THINGS_SRCS

# Usage: $(eval $(call STATIC_LIBRARY_RULES,$(static_library_thingname)))
define STATIC_LIBRARY_RULES
  $(1)_BASENAME ?= $(1)
  $(1)_NAME = $(LIB_PREFIX)$$($(1)_BASENAME).$(LIB_SUFFIX)

$$($(1)_DIR)$$($(1)_NAME): $$($(1)_CXXOBJS) $$($(1)_COBJS) $$($(1)_ASMOBJS)
	@echo "Library $$*"
	$(call MKSTATICLIB,$$@) $$($(1)_CXXOBJS) $$($(1)_COBJS) $$($(1)_ASMOBJS)

GARBAGE += $$($(1)_DIR)$$($(1)_NAME)

ifdef $(1)_BUILD_ALL
all:: $$($(1)_DIR)$$($(1)_NAME)
endif

endef

# Usage: $(eval $(call DLL_RULES,$(dll_thingname)))
define DLL_RULES
  $(1)_BASENAME ?= $(1)
  $(1)_NAME = $(LIB_PREFIX)$$($(1)_BASENAME).$(DLL_SUFFIX)
  $(1)_DEPS = \
    $$($(1)_EXTRA_DEPS) \
    $$(foreach lib,$$($(1)_STATIC_LIBRARIES) $$($(1)_DLLS),$$($$(lib)_NAME)) \
    $$(GLOBAL_DEPS) \
    $(NULL)
  $(1)_LDFLAGS = \
    $$(LDFLAGS) \
    $$($(1)_EXTRA_LDFLAGS) \
    $$(foreach lib,$$(OS_LIBS),$(call EXPAND_LIBNAME,$$(lib))) \
    $$(OS_LDFLAGS) \
    $(NULL)

$$($(1)_DIR)$$($(1)_NAME): $$($(1)_CXXOBJS) $$($(1)_COBJS) $$($(1)_DEPS)
	$(call MKDLL,$$@) $$($(1)_CXXOBJS) $$($(1)_COBJS) \
	  $(LIBPATH). $$(foreach lib,$$($(1)_STATIC_LIBRARIES),$$(call EXPAND_LIBNAME,$$(lib))) \
	  $$(foreach lib,$$($(1)_DLLS),$$(call EXPAND_DLLNAME,$$(lib))) \
	  $$($(1)_LDFLAGS)

GARBAGE += $$($(1)_DIR)$$($(1)_NAME)

ifdef $(1)_BUILD_ALL
all:: $$($(1)_DIR)$$($(1)_NAME)
endif

endef

# Usage: $(eval $(call PROGRAM_RULES,$(program_thingnaame)))
define PROGRAM_RULES
  $(1)_BASENAME ?= $(1)
  $(1)_NAME ?= $$($(1)_BASENAME)$(PROGRAM_SUFFIX)
  $(1)_DEPS = \
    $$($(1)_EXTRA_DEPS) \
    $$(foreach lib,$$($(1)_STATIC_LIBRARIES) $$($(1)_DLLS),$$($$(lib)_NAME)) \
    $$(GLOBAL_DEPS) \
    $(NULL)
  $(1)_LDFLAGS = \
    $$(LDFLAGS) \
    $$($(1)_EXTRA_LDFLAGS) \
    $$(foreach lib,$$(OS_LIBS),$(call EXPAND_LIBNAME,$$(lib))) \
    $$(OS_LDFLAGS) \
    $(NULL)

$$($(1)_DIR)$$($(1)_NAME): $$($(1)_CXXOBJS) $$($(1)_DEPS)
	@echo "Link $$@"
	$(call MKPROGRAM,$$@) \
	  $$($(1)_CXXOBJS) \
	  $(LIBPATH). $$(foreach lib,$$($(1)_STATIC_LIBRARIES),$$(call EXPAND_LIBNAME,$$(lib))) \
	  $$(foreach lib,$$($(1)_DLLS),$$(call EXPAND_DLLNAME,$$(lib))) \
	  $$($(1)_LDFLAGS)

GARBAGE += $$($(1)_DIR)$$($(1)_NAME)

ifdef $(1)_BUILD_ALL
all:: $$($(1)_DIR)$$($(1)_NAME)
endif

endef

.PHONY: all FORCE