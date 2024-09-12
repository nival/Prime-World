dnl Gearman PHP Extension
dnl
dnl Copyright (C) 2008 James M. Luedke <contact@jamesluedke.com>,
dnl                    Eric Day <eday@oddments.org>
dnl All rights reserved.
dnl
dnl Use and distribution licensed under the PHP license.  See
dnl the LICENSE file in this directory for full text.

CFLAGS="$CFLAGS -Wall"

PHP_ARG_WITH(gearman, whether to enable gearman support,
[[  --with-gearman[=PATH]   Include gearman support]])

if test "$PHP_GEARMAN" != "no"; then
  for i in $PHP_GEARMAN /usr/local /usr /opt/local; do
    if test -r $i/include/libgearman/gearman.h; then
      GEARMAN_LIB_DIR=$i/lib
      GEARMAN_INC_DIR=$i/include
      AC_MSG_RESULT([found in $i])
      break
    fi
  done

  if test -z "$GEARMAN_LIB_DIR" -o -z "$GEARMAN_INC_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please install libgearman])
  fi

  PHP_CHECK_LIBRARY(gearman, gearman_client_set_context,
  [
    PHP_ADD_LIBRARY_WITH_PATH(gearman, $GEARMAN_LIB_DIR, GEARMAN_SHARED_LIBADD)
    AC_DEFINE(HAVE_GEARMAN, 1, [Whether you have gearman])
  ],[
    AC_MSG_ERROR([libgearman version 0.10 or later required])
  ],[
    -L$GEARMAN_LIB_DIR -R$GEARMAN_LIB_DIR
  ])
  dnl
  PHP_SUBST(GEARMAN_SHARED_LIBADD)

  PHP_ADD_INCLUDE($GEARMAN_INC_DIR)
  PHP_NEW_EXTENSION(gearman, php_gearman.c, $ext_shared)
fi
