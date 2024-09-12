/*
 * Gearman PHP Extension
 *
 * Copyright (C) 2008 James M. Luedke <contact@jamesluedke.com>,
 *                    Eric Day <eday@oddments.org>
 * All rights reserved.
 *
 * Use and distribution licensed under the PHP license.  See
 * the LICENSE file in this directory for full text.
 */

#ifndef __PHP_GEARMAN_H
#define __PHP_GEARMAN_H

/* module version */
#define PHP_GEARMAN_VERSION "0.7.0"

#ifdef ZTS
#include "TSRM.h"
#define GEARMAN_G(v) TSRMG(gearman_globals_id, zend_gearman_globals *, v)
#else
#define GEARMAN_G(v) (gearman_globals.v)
#endif

extern zend_module_entry gearman_module_entry;
#define phpext_gearman_ptr &gearman_module_entry

#endif  /* __PHP_GEARMAN_H */
