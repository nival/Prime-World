/*
    Copyright 2005-2009 Intel Corporation.  All Rights Reserved.

    The source code contained or described herein and all documents related
    to the source code ("Material") are owned by Intel Corporation or its
    suppliers or licensors.  Title to the Material remains with Intel
    Corporation or its suppliers and licensors.  The Material is protected
    by worldwide copyright laws and treaty provisions.  No part of the
    Material may be used, copied, reproduced, modified, published, uploaded,
    posted, transmitted, distributed, or disclosed in any way without
    Intel's prior express written permission.

    No license under any patent, copyright, trade secret or other
    intellectual property right is granted to or conferred upon you by
    disclosure or delivery of the Materials, either expressly, by
    implication, inducement, estoppel or otherwise.  Any license under such
    intellectual property rights must be express and approved by Intel in
    writing.
*/

#ifndef __TBB_profiling_H
#define __TBB_profiling_H

// Check if the tools support is enabled
#if (_WIN32||_WIN64||__linux__) && TBB_USE_THREADING_TOOLS

#if _WIN32||_WIN64
#include <stdlib.h>  /* mbstowcs_s */
#endif
#include "tbb_stddef.h"

namespace tbb {
    namespace internal {
#if _WIN32||_WIN64
        void __TBB_EXPORTED_FUNC itt_set_sync_name_v3( void *obj, const wchar_t* name ); 
        inline size_t multibyte_to_widechar( wchar_t* wcs, const char* mbs, size_t bufsize) {
#if _MSC_VER>=1400
            size_t len;
            mbstowcs_s( &len, wcs, bufsize, mbs, _TRUNCATE );
            return len;   // mbstowcs_s counts null terminator
#else
            size_t len = mbstowcs( wcs, mbs, bufsize );
            if(wcs && len!=size_t(-1) )
                wcs[len<bufsize-1? len: bufsize-1] = wchar_t('\0');
            return len+1; // mbstowcs does not count null terminator
#endif
        }
#else
        void __TBB_EXPORTED_FUNC itt_set_sync_name_v3( void *obj, const char* name ); 
#endif
    } // namespace internal
} // namespace tbb

//! Macro __TBB_DEFINE_PROFILING_SET_NAME(T) defines "set_name" methods for sync objects of type T
/** Should be used in the "tbb" namespace only. 
    Don't place semicolon after it to avoid compiler warnings. **/
#if _WIN32||_WIN64
    #define __TBB_DEFINE_PROFILING_SET_NAME(sync_object_type)    \
        namespace profiling {                                                       \
            inline void set_name( sync_object_type& obj, const wchar_t* name ) {    \
                tbb::internal::itt_set_sync_name_v3( &obj, name );                  \
            }                                                                       \
            inline void set_name( sync_object_type& obj, const char* name ) {       \
                size_t len = tbb::internal::multibyte_to_widechar(NULL, name, 0);   \
                wchar_t *wname = new wchar_t[len];                                  \
                tbb::internal::multibyte_to_widechar(wname, name, len);             \
                set_name( obj, wname );                                             \
                delete[] wname;                                                     \
            }                                                                       \
        }
#else /* !WIN */
    #define __TBB_DEFINE_PROFILING_SET_NAME(sync_object_type)    \
        namespace profiling {                                                       \
            inline void set_name( sync_object_type& obj, const char* name ) {       \
                tbb::internal::itt_set_sync_name_v3( &obj, name );                  \
            }                                                                       \
        }
#endif /* !WIN */

#else /* no tools support */

#if _WIN32||_WIN64
    #define __TBB_DEFINE_PROFILING_SET_NAME(sync_object_type)    \
        namespace profiling {                                               \
            inline void set_name( sync_object_type&, const wchar_t* ) {}    \
            inline void set_name( sync_object_type&, const char* ) {}       \
        }
#else /* !WIN */
    #define __TBB_DEFINE_PROFILING_SET_NAME(sync_object_type)    \
        namespace profiling {                                               \
            inline void set_name( sync_object_type&, const char* ) {}       \
        }
#endif /* !WIN */

#endif /* no tools support */

#endif /* __TBB_profiling_H */
