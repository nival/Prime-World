# $Id: platform_tru64_pre.GNU 80826 2008-03-04 14:51:23Z wotte $

# Common definitions for all versions of Digital Unix.

ifndef ACE_DU_VERSION
  ACE_DU_VERSION := $(shell uname -r)
endif # ! ACE_DU_VERSION

ifndef ACE_DU_SUBVERSION
  ACE_DU_SUBVERSION := $(shell /usr/sbin/sizer -v)
endif # ! ACE_DU_SUBVERSION
