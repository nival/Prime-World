/*************************************************************************
 *                         INTEL CONFIDENTIAL
 *
 * Copyright 2004-2009 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors.  Title to the Material remains with Intel
 * Corporation or its suppliers and licensors.  The Material contains
 * trade secrets and proprietary and confidential information of Intel
 * or its suppliers and licensors.  The Material is protected by worldwide
 * copyright and trade secret laws and treaty provisions.  No part of the
 * Material may be used, copied, reproduced, modified, published, uploaded,
 * posted, transmitted, distributed, or disclosed in any way without
 * Intel's prior express wrtten permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise.  Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 ************************************************************************/


#if !defined(__TBRW_TYPES_H__)
#define __TBRW_TYPES_H__


//
// Start off with none of the OS'es are defined
//
#undef TBRW_OS_WINDOWS
#undef TBRW_OS_LINUX
#undef TBRW_OS_DARWIN
#undef TBRW_32BIT
#undef TBRW_64BIT

//
// Make sure one (and only one) of the OS'es gets defined here
//
// Unfortunately entirex defines _WIN32 so we need to check for linux
// first. We don't want TBRW_OS_LINUX and TBRW_OS_WINDOWS defined for
// entirex. The definition of these flags is one and only one
// TBRW_OS_xxx is allowed to be defined.
//
#if defined(linux)
#define TBRW_OS_LINUX       1
#elif defined(_WIN32)
#define TBRW_OS_WINDOWS     1
#elif defined(__APPLE__)
#define TBRW_OS_APPLE       1
#else
#error "Compiling for an unknown OS"
#endif

//
// Make sure one (and only one) architecture is defined here
// as well as one (and only one) pointer size
//
#if defined(_M_IX86) || defined(__i386__)
#define TBRW_32BIT          1
#define TBRW_ARCH_PENTIUM   1
#elif defined(_M_IA64) || defined(__ia64__)
#define TBRW_ARCH_IA64      1
#define TBRW_64BIT          1
#elif defined(_M_AMD64) || defined(__x86_64__)
#define TBRW_ARCH_PENTIUM   1
#define TBRW_64BIT          1
#else
#error "Unknown architecture for compilation"
#endif


#if defined(TBRW_OS_WINDOWS)
#pragma once
#elif defined(TBRW_OS_LINUX) || defined(TBRW_OS_APPLE)
// Do they have a "#pragma once" equivilent?
#else
#error "unknown os"
#endif


//
// file permission flags
//
#define TBRW_FILE_READ          0x00000001
#define TBRW_FILE_WRITE         0x00000002
#define TBRW_FILE_CREATE_ALWAYS 0x00000004

//TODO Need to get to this later
#define NULL_OFFSET 0
#define CPU_ARCHITECTURE_NOT_SET 0  // cpu architecture not set
#define CPU_ARCHITECTURE_IA32   1   // X86 cpu
#define CPU_ARCHITECTURE_IA64   2   // IA64 cpu
//#define CPU_ARCHITECTURE_SA     3   // StrongARM
//#define CPU_ARCHITECTURE_XSC    4


//
// TBRW_VERIFY_SIZEOF let's you insert a compile-time check that the size of a data
// type (e.g. a struct) is what you think it should be.  Usually it is
// important to know what the actual size of your struct is, and to make sure
// it is the same across all platforms.  So this will prevent the code from
// compiling if something happens that you didn't expect, whether it's because
// you counted wring, or more often because the compiler inserted padding that
// you don't want.
//
// NOTE: 'elem' and 'size' must both be identifier safe, e.g. matching the
// regular expression /^[0-9a-zA-Z_]$/.
//
// Example:
//   typedef struct { void *ptr; int data; } mytype;
//   TBRW_VERIFY_SIZEOF(mytype, 8);
//                         ^-- this is correct on 32-bit platforms, but fails
//                             on 64-bit platforms, indicating a possible
//                             portability issue.
//
#define TBRW_VERIFY_SIZEOF(type, size) \
    enum { sizeof_ ## type ## _eq_ ## size = 1 / (int)(sizeof(type) == size) }



#if !defined INOUT
#define INOUT
#endif

#if !defined IN
#define IN
#endif

#if !defined OUT
#define OUT
#endif

#if !defined OPTIONAL
#define OPTIONAL
#endif



#if defined(TBRW_OS_WINDOWS)

// Allow nameless unions/structs in windows
#pragma warning(disable:4201)

#if defined TBRW_EXPORTS
#define TBRW_API __declspec(dllexport)
#else // TBRW_EXPORTS not defined
#define TBRW_API __declspec(dllimport)
#endif // endif TBRW_EXPORTS
//
// All DLL exports are (by convention) stdcall in windows
//
#define TBRW_APICALL __stdcall

#elif defined(TBRW_OS_LINUX) || defined(TBRW_OS_APPLE)
//
// linux and Mac OS don't care about all that dll complexity...
//
#define TBRW_API
#define TBRW_APICALL

#else
#error "Unknown OS"
#endif

#if !defined(_WCHAR_T_DEFINED)
#include <wchar.h>
#endif

//Define TBRW types which map to internal types
typedef     wchar_t             TBRW_CHAR;
typedef     unsigned char       TBRW_U8;
typedef     unsigned short      TBRW_U16;
typedef     unsigned int        TBRW_U32;
typedef     signed int          TBRW_S32;

#if defined(TBRW_OS_LINUX) || defined(TBRW_OS_APPLE)
typedef     signed long long    TBRW_S64;
typedef     unsigned long long  TBRW_U64;
#elif defined(TBRW_OS_WINDOWS)
typedef     signed __int64      TBRW_S64;
typedef     unsigned __int64    TBRW_U64;
#else
#error "Unexpected OS seen"
#endif

//
// And the pointer casts
// Designed to be of varying size so that pointers can be
// cast to this type, have math operations done, and then cast
// back into pointers without losing bits.
//
// The names come from:
// Signed Int Or Pointer (SIOP)
// Unsigned Int Or Pointer (UIOP)

#if defined(TBRW_32BIT)

typedef TBRW_S32                 TBRW_SIOP;
typedef TBRW_U32                 TBRW_UIOP;

#elif defined(TBRW_64BIT)

typedef TBRW_S64                 TBRW_SIOP;
typedef TBRW_U64                 TBRW_UIOP;

#else
#error "Unexpected bitsize seen"
#endif

#define TBRW_OSFAMILY_WIN32     1
#define TBRW_OSFAMILY_WIN64     2
#define TBRW_OSFAMILY_WINCE     3
#define TBRW_OSFAMILY_XOS       4
#define TBRW_OSFAMILY_LINUX32   5
#define TBRW_OSFAMILY_LINUX64   6

typedef struct _TBRW_FILETIME {
    TBRW_U32 dwLowDateTime;
    TBRW_U32 dwHighDateTime;
} TBRW_FILETIME, *PTBRW_FILETIME;
//END TODO

//
// TBRW_PTR
//

typedef void* TBRW_PTR;

//
// TBRW_SECTION_IDENTIFIER
//

typedef enum {
    TBRW_HARDWARE_SECTION,
    TBRW_SOFTWARE_SECTION,
    TBRW_PROCESS_THREAD_SECTION,
    TBRW_MODULE_SECTION,
    TBRW_USER_DEFINED_GLOBAL_SECTION,
    TBRW_VERSION_INFO_SECTION
} TBRW_SECTION_IDENTIFIER;

//
// TBRW_STREAM_SECTION_IDENTIFIER
//

typedef enum {
    TBRW_EVENT_DESCRIPTION_SECTION,
    TBRW_DATA_DESCRIPTION_SECTION,
    TBRW_DATA_SECTION,
    TBRW_USER_DEFINED_STREAM_SECTION,
    TBRW_STREAM_INFO_SECTION
} TBRW_STREAM_SECTION_IDENTIFIER;

//
// TBRW_STRING_OR_ID
//

typedef struct __string_or_id { // on writes, it is a string pointer
    union {
        TBRW_U64       soi_uniqueid;        // on reads, it is a unique id.
        TBRW_CHAR *soi_ptr;         // for debug/implementation can use
                                    // bit 63 to indicate whether it is an unique id or not
    };
//#if defined(VTSA_32BIT)
    //for alignment purposes
//    U32 dummy;
//#elif defined(VTSA_64BIT)
    //no padding needed
//#else
//#error "Unexpected bitsize"
//#endif

} TBRW_STRING_OR_ID;

TBRW_VERIFY_SIZEOF(TBRW_STRING_OR_ID, 8);

////////////////////////////////
// TBRW version info structure
// this structure applies to the whole tb5 file
////////////////////////////////
typedef struct __TBRW_version_info
{
    TBRW_U32 version_info_size;        //set to sizeof(TBRW_VERSION_INFO)
    TBRW_U32 sampling_driver_version;  //version of the sampling driver
    TBRW_U32 bind_version;             //version of the bind library used to analyze the tb5 file
    TBRW_U32 sample_file_version;      //version of the sample file format
} TBRW_VERSION_INFO;

TBRW_VERIFY_SIZEOF(TBRW_VERSION_INFO, 16);

////////////////////////////////
// TBRW stream info structure
// there is one of these kept per stream
////////////////////////////////
typedef struct __TBRW_stream_info
{
    TBRW_U32 stream_info_size;                  //set to sizeof(TBRW_STREAM_INFO)
    TBRW_U32 sampling_duration;                //duration of the sampling session (in milliseconds)
    TBRW_U32 stream_type;                      //refer to TBRW_STREAM_TYPE
    TBRW_U32 sampling_interval;                //in microseconds
    TBRW_FILETIME sampling_start_time;   //start time of the sampling session
    TBRW_FILETIME sampling_end_time;     //end time of the sampling session
    TBRW_STRING_OR_ID command_line;       //the command line used to generate this stream
    TBRW_STRING_OR_ID cpu_mask;           //even though the cpu mask info is also found in the command line,
                                          //we include it here too because TBRW does not know how to
                                          //parse the command line (could be sep command, vtl command, dcpi command, etc).
    TBRW_STRING_OR_ID comment;            //the comment describing this stream
} TBRW_STREAM_INFO;
TBRW_VERIFY_SIZEOF(TBRW_STREAM_INFO, 56);

////////////////////////////////
// TBRW Hardware Stuctures
////////////////////////////////
typedef struct __TBRW_node TBRW_NODE;
typedef struct __TBRW_cpu TBRW_CPU;
typedef struct __TBRW_cpu_arch TBRW_CPU_ARCH;
typedef struct __TBRW_cpuid TBRW_CPUID;
typedef struct __TBRW_event_detail TBRW_EVENT_DETAIL;
//
// TBRW_CPUID_IA32
//

typedef struct __TBRW_cpuid_ia32 {
    TBRW_U32 cpuid_eax_input;
    TBRW_U32 cpuid_eax;
    TBRW_U32 cpuid_ebx;
    TBRW_U32 cpuid_ecx;
    TBRW_U32 cpuid_edx;
    TBRW_U32 reserved;
} TBRW_CPUID_IA32;
TBRW_VERIFY_SIZEOF(TBRW_CPUID_IA32, 24);

//
// TBRW_CPUID_IA64
//

typedef struct __TBRW_cpuid_ia64 {
    TBRW_U64 cpuid_select;
    TBRW_U64 cpuid_val;
    TBRW_U64 reserved;
} TBRW_CPUID_IA64;
TBRW_VERIFY_SIZEOF(TBRW_CPUID_IA64, 24);

//
// TBRW_CPU_ARCH
//

struct __TBRW_cpu_arch {
    TBRW_U32 arch_size;                  //set to sizeof(TBRW_CPU_ARCH). Used for versioning
    TBRW_U16 arch_type;                  // enum of architecture (ia32, ia64, em64t, etc)
    TBRW_U16 arch_num_cpuid;             // number of cpuid structs available for this arch

    union {
        TBRW_CPUID_IA32 *cpuid_ia32_array;
        TBRW_CPUID_IA64 *cpuid_ia64_array;
    };

#if defined(TBRW_32BIT)
    //for alignment purposes
    TBRW_U32 dummy;
#elif defined(TBRW_64BIT)
    //no padding needed
#else
#error "Unexpected bitsize"
#endif

};
TBRW_VERIFY_SIZEOF(TBRW_CPU_ARCH, 16);

//
// TBRW_CPU
//

struct __TBRW_cpu {
    TBRW_U32 cpu_size;                   // set to sizeof(TBRW_CPU). Used for versioning
    TBRW_U32 cpu_number;                 // The logical cpu number (as seen from user perspective)
    TBRW_U32 cpu_native_arch_type;       // The native architecture for this processor
    TBRW_U32 cpu_intel_processor_number; // The intel processor number (if available)

    TBRW_U32 cpu_speed_mhz;             // cpu speed (in Mhz)
    TBRW_U32 cpu_fsb_mhz;               // cpu front side bus speed (in Mhz)

    TBRW_U32 cpu_cache_L2;              // Size of the L2 cache (in Kbytes)
    TBRW_U32 cpu_cache_L3;              // Size of the L3 cache (in Kbytes)

    TBRW_S64 cpu_tsc_offset;            // TSC offset from CPU 0 ie. (TSC CPU N - TSC CPU 0)

    TBRW_U16 cpu_package_num;           // package number for this cpu (if known)
    TBRW_U16 cpu_core_num;              // core number (if known)

    TBRW_U16 cpu_hardware_thread_num;    // hardware thread number inside core (if known)
    TBRW_U16 cpu_threads_per_core;       // total number of h/w threads per core (if known)

    TBRW_U32 num_cpu_arch_array;         //number of cpu architectures supported by this cpu
    TBRW_U32 dummy; //for alignment

    TBRW_CPU_ARCH *cpu_arch_array;        // pointer to an array of cpu
                                    // architectures supported by this cpu (for
                                    // example, ia64 processors that support execution
                                    // of ia32 binaries can have two elements in the
                                    // cpu_arch_array table). The native architectural
                                    // type must be represented in this array.
#if defined(TBRW_32BIT)
    TBRW_U32 dummy2;
#elif defined(TBRW_64BIT)
    //no padding needed
#else
#error "Unexpected bitsize"
#endif

};
TBRW_VERIFY_SIZEOF(TBRW_CPU, 64);

//
// TBRW_NODE
//

struct __TBRW_node {
    TBRW_U32 node_size;                 // set to sizeof(TBRW_NODE). Used for versioning
    TBRW_U32 node_type_from_shell;      //the shell platform
    TBRW_U32 node_id;                   // The node number/id (if known)
    TBRW_U32 node_num_available;        // total number of cpus on this node
    TBRW_U32 node_num_used;             // number of cpus used based on cpu-mask specified.
    TBRW_U32 reserved;                  // for alignment
    TBRW_U64 node_physical_memory;      // amount of physical memory on this node

#if defined(TBRW_32BIT)
    //for alignment purposes
    TBRW_U32 dummy;
#elif defined(TBRW_64BIT)
    //no padding needed
#else
#error "Unexpected bitsize"
#endif

    TBRW_CPU *cpu_array;           // pointer to an array of cpu's for this node
};
TBRW_VERIFY_SIZEOF(TBRW_NODE, 40);

//
// TBRW_SYSTEM
//

typedef struct __TBRW_system {
    TBRW_U32 system_size;              // set to sizeof(TBRW_SYSTEM). Used for versioning
    TBRW_U32 system_num_nodes;        // number of nodes in a system

#if defined(TBRW_32BIT)
    //for alignment purposes
    TBRW_U32 dummy;
#elif defined(TBRW_64BIT)
    //no padding needed
#else
#error "Unexpected bitsize"
#endif

    TBRW_NODE *node_array;        // pointer to an array of nodes for this system
} TBRW_SYSTEM;
TBRW_VERIFY_SIZEOF(TBRW_SYSTEM, 16);

////////////////////////////////
// TBRW Software Stuctures
////////////////////////////////

//
// TBRW_HOST_HOST
//

typedef struct __TBRW_host {
    TBRW_U32 host_size;          // set to sizeof(TBRW_HOST). Used for versioning
    TBRW_U32 reserved;           // for alignment purposes
    TBRW_STRING_OR_ID host_ip_address;    // IP address of the host
    TBRW_STRING_OR_ID host_name;        // human readable host name
} TBRW_HOST;
TBRW_VERIFY_SIZEOF(TBRW_HOST, 24);

//
// TBRW_OS
//

typedef struct __TBRW_os {
    TBRW_U32 os_size;            // set to sizeof(TBRW_OS). Used for versioning

    TBRW_U32 os_platform;        // OS indicator (linux, windows, etc)

    TBRW_U32 os_major;           // OS major version
    TBRW_U32 os_minor;          // OS minor version
    TBRW_U32 os_build;          // OS build number
    TBRW_U32 os_extra;           // OS release info, service packs, errata numbers, etc.

    TBRW_STRING_OR_ID os_name;          // human readable OS name
    TBRW_STRING_OR_ID os_name_extra;    // human readable OS arbitrary extra information (like
                                        // service packs, errata, the result of `uname -r`, etc)
} TBRW_OS;
TBRW_VERIFY_SIZEOF(TBRW_OS, 40);

//
// TBRW_APPLICATION
//

typedef struct __TBRW_application {
    TBRW_U32 app_size;           // set to sizeof(TBRW_APPLICATION). Used for versioning
    TBRW_U32 app_reserved;       // reserved, should be set to zero

    TBRW_U32 app_page_size;      // page size (as seen by application)
    TBRW_U32 app_alloc_granularity;  // granularity of vm (i.e. mmap() size/alignement)

    TBRW_U64 app_min_app_addr;   // lowest memory address accessible by an application
    TBRW_U64 app_max_app_addr;   // highest memory address accessible by an application

} TBRW_APPLICATION;
TBRW_VERIFY_SIZEOF(TBRW_APPLICATION, 32);

//////////////////////////////////////////
// TBRW Process/Thread/Module Structure.
//////////////////////////////////////////

//
// PID/TID flags
//

#define  TBRW_PIDTID_DESTROYED          0x00000001
#define  TBRW_PIDTID_CREATED            0x00000000
#define  TBRW_PIDTID_WHEN_TSC           0x00000010
#define  TBRW_PIDTID_WHEN_SAMP_COUNT    0x00000000

#define  TBRW_PIDTID_CREATION_MASK      0x00000001   // bit 1 is used
#define  TBRW_PIDTID_WHEN_MASK          0x00000110   // bits 2-3 are used.

//
// TBRW_PID
//

typedef struct __TBRW_pid {
    TBRW_U32 pid_size;           // set to sizeof(TBRW_PID). Used for versioning

    TBRW_U32 pid_id;             // process id (as provided by the OS). Needs
                            // to be comparable against the PID field in the
                            // sample record
    TBRW_U32 pid_flags;          // Flags desribed above.
                            // Currently used to indicate whether process was created
                            // or destroyed,and to store the when association

    TBRW_U32 reserved;           //alignment
    TBRW_U64 pid_event_when;     // An indication of when the pid event occured (i.e.
                            // could be a tsc value, could be a sample number, etc.)

    TBRW_U32 reserved_for_legacy; // for now this holds the pid index-- temporary only!
    TBRW_U32 reserved1;           // can be used for cpu # later on when we move to tsc's

    TBRW_STRING_OR_ID pid_path;       // path to the process executable (if create event)
    TBRW_STRING_OR_ID pid_name;       // name of the process (if create event)

} TBRW_PID;
TBRW_VERIFY_SIZEOF(TBRW_PID, 48);

//
// TBRW_TID
//

typedef struct __TBRW_tid {
    TBRW_U32 tid_size;          // set to sizeof(TBRW_TID). Used for versioning

    TBRW_U32 tid_associated_pid;    // process that this thread is a part of. Needs
                            // to be comparable against the PID field in the
                            // sample record and the TBRW_PID pid_id field

    TBRW_U32 tid_id;             // thread id (as provided by the OS). Needs
                            // to be comparable against the TID field in the
                            // sample record

    TBRW_U32 tid_flags;          // Flags desribed above.
                            // Currently used to indicate whether thread was created
                            // or destroyed,and to store the when association

    TBRW_U64 tid_event_when;     // An indication of when the tid event occured (i.e
                            // could be a tsc value, could be a sample number, etc)

    TBRW_U32 reserved_for_legacy;// for now this hold the tid index--temporary only!
    TBRW_U32 reserved;           // can be used for cpu # later on when we move to tsc's

    TBRW_STRING_OR_ID tid_name;       // name of the thread (if create event)

} TBRW_TID;
TBRW_VERIFY_SIZEOF(TBRW_TID, 40);

//
// Module Flags
//

#define  TBRW_MODULE_TSC_USED                  0x10000 // Is Tsc Used as for ordering?
#define  TBRW_MODULE_LOADED                    0x08000
#define  TBRW_MODULE_UNLOADED                  0x04000
#define  TBRW_MODULE_LOADED_MASK               0x02000
#define  TBRW_MODULE_IS_EXE                    0x01000 // is this module an exe?
#define  TBRW_MODULE_GLOBAL_LOAD               0x00800 // is this a kernel module?
#define  TBRW_MODULE_1ST_MODULE_REC_IN_PROCESS 0x00400 // is this the 1st module loaded for this process?
                                                      //   if so, then need to use this module's load count
                                                      //   as the load count for the pid generated by the next
                                                      //   exe module ordered in time

//
// TBRW_MODULE
//

typedef struct __TBRW_module {
    TBRW_U32 module_size;            // set to sizeof(TBRW_MODULE). Used for versioning
    TBRW_U32 module_reserved;        // reserved, should be zero
    TBRW_U32 module_associated_pid;  // The OS pid of the process which loaded/unloaded this module
    TBRW_U32 module_flags;           // addition information about this module (load
                                // vs. Unload, global,
                                // exe, segment type, event_when is tsc
                                // vs. Sample count, etc).

    TBRW_U64 module_event_when;     // An indication of when the event occured. Could be
                                // a timestamp or correspond to a particular sample
                                // (sample number)

    TBRW_U32 module_segment_number; // for java
    TBRW_U32 module_segment_type : 2;// see the MODE_ types defined in SampFile.h
    TBRW_U32                     :30;
    TBRW_U32 module_code_selector;  // for ia32
    TBRW_U32 reserved;               // for alignment

    TBRW_U64 module_length;          // size of the module (if load event)
    TBRW_U64 module_load_address;    // address where module was loaded (if load event)
    TBRW_U32 reserved_for_legacy;    // holds module unload sample count, please don't use
    TBRW_U32 reserved_for_legacy2;   // for now holds the pid index in the case of a bound tb5 file
                                // WARNING: temporary only!
    TBRW_U32 reserved_for_legacy_flags; // same as legacy ModuleRecord.flags field
    TBRW_U32 reserved1;              // can be used for cpu # later on when we move to tsc's
    //TBRW_U32 reserved2;
    TBRW_U64 module_unload_tsc;      // Saves the load tsc for tsc based data collection, module_event_when is used for old sample
                                // sample count based tb5 data
                                // Check the macro to get this field due to introduction of tsc
    //TBRW_U32 reserved3;

    TBRW_STRING_OR_ID module_path;        // path to the module (if load event)
    TBRW_STRING_OR_ID module_name;        // name of the module (if load event)
    TBRW_STRING_OR_ID module_segment_name;// name of the segment (if load event and segments in use)

} TBRW_MODULE;
TBRW_VERIFY_SIZEOF(TBRW_MODULE, 104);


//
// TBRW_STREAM_TYPE
//

typedef enum {
    TBRW_SAMPLING_STREAM = 1,
    TBRW_AGGREGATED_STREAM,
    TBRW_BOOKMARK_STREAM,
    TBRW_BIND_DATA_INFORMATION_STREAM,
    TBRW_BIND_MODULE_INFORMATION_STREAM,
    TBRW_BIND_PID_INFORMATION_STREAM,
    TBRW_BIND_TID_INFORMATION_STREAM,
    TBRW_CUSTOM_STREAM
    } TBRW_STREAM_TYPE;


//
// Event Flags
//

#define TBRW_EVENT_EBS          0x00000001
#define TBRW_EVENT_TBS          0x00000000

#define TBRW_EVENT_MODE_MASK    0x00000001

//
// TBRW_EVENT_DETAIL
//

typedef enum {
    TBRW_MSR = 0,
    TBRW_PMC,
    TBRW_PMD,
    TBRW_TBS_VTD,
    TBRW_TBS_RTC,
    TBRW_TBS_STATCARD,
    TBRW_OS_EVENT
} TBRW_ACCESS_METHOD;

struct __TBRW_event_detail {
    TBRW_U32 detail_size;       // set to sizeof(TBRW_EVENT_DETAIL). Used for versioning

    TBRW_U16 detail_access_size;    // size of the access (in bits) i.e. 8, 16, 32, 64
    TBRW_U8  detail_method;     // type of access - MSR, PCI, Memory, other, see TBRW_ACCESS_METHOD
    TBRW_U8  detail_access;     // read or write

    TBRW_U64 detail_address;        // address of read/write
    TBRW_U64 detail_value;      // value of read/write
    TBRW_U8  legacy_command;     // corresponds to legacy EventRegSetEx.command
                            // will become irrelevant as we move to new structures
                            // this field is useful when generating legacy Events info
    TBRW_U8  reserved1;
    TBRW_U16 reserved2;
    TBRW_U32 reserved3;

};
TBRW_VERIFY_SIZEOF(TBRW_EVENT_DETAIL, 32);

//
// TBRW_EVENT
//

typedef struct __TBRW_event {
    TBRW_U32 event_size;         // set to sizeof(TBRW_EVENT). Used for versioning

    TBRW_U32 event_id;           // event id. Must be comparable to the event id field
                            // in the sample record.

    TBRW_U32 event_num_details;  // number of event details supplied

    TBRW_U32 event_flags;       // event info (ie. Ebs vs. Tbs, units for the SAV, etc)
    TBRW_U64 event_sav;         // sample after value used for this event

    TBRW_STRING_OR_ID event_name;       // human readable name of the event
    TBRW_STRING_OR_ID event_arch_name;  //human readable name of cpu type, i.e. "Pentium M"

    TBRW_EVENT_DETAIL *event_detail_array; //details about programming this event
#if defined(TBRW_32BIT)
    //for alignment purposes
    TBRW_U32 dummy;
#elif defined(TBRW_64BIT)
    //no padding needed
#else
#error "Unexpected bitsize"
#endif
} TBRW_EVENT;
TBRW_VERIFY_SIZEOF(TBRW_EVENT, 48);

//
// TBRW_SAMPREC_DESC_ENTRY
//

typedef struct __tbrw_samprec_desc_entry {
    union {
        TBRW_U64 force_8_byte_aligned;
        struct {
            TBRW_U32 desc_size;    // set to sizeof(TBRW_SAMPREC_DESC_ENTRY).
                              // Used for versioning.
            TBRW_U32 desc_offset;  // offset from start of sample record in bytes
            TBRW_U16 desc_type;      // See ST_ types defined in samprec_shared.h
            TBRW_U16 desc_subtype;   // See SST_ types defined in samprec_shared.h
            TBRW_U32 desc_data_size; // in bytes
            TBRW_U64 desc_access_offset; // msr # or memory offset
            TBRW_U8  desc_access_type;   // read = 0, write = 1
            TBRW_U8  desc_access_method; // register = 0, memory = 1
            TBRW_U8  desc_sample_flag;   // internal driver sample flag
            TBRW_U8  reserved0;          // reserved
            TBRW_U32 reserved1;
            TBRW_STRING_OR_ID  desc_name; //human-readable name or comment
            TBRW_U8  padding[32]; //why do we need the padding-- it's already 8 byte aligned?????
        };
    };
} TBRW_SAMPREC_DESC_ENTRY;
TBRW_VERIFY_SIZEOF(TBRW_SAMPREC_DESC_ENTRY, 72);

typedef enum {
    TBRW_GST_UNK = 0,
    TBRW_GST_X86,
    TBRW_GST_ITANIUM,
    TBRW_GST_RESERVED1,
    TBRW_GST_RESERVED2,
    TBRW_GST_EM64T,
    TBRW_GST_RESERVED3
} TBRW_GEN_ENTRY_SUBTYPES;


/*
 * Start - TBRW sampling data structures used for VTune sampling data format
 */
typedef struct TBRW_CodeDescriptor_s {
    union {
        TBRW_U32 lowWord;            // low dword of descriptor
        struct {                  // low broken out by fields
            TBRW_U16 limitLow;              // segment limit 15:00
            TBRW_U16 baseLow;               // segment base 15:00
               };
          };
    union {
        TBRW_U32   highWord;      // high word of descriptor
        struct {                    // high broken out by bit fields
            TBRW_U32   baseMid : 8;        // base 23:16
            TBRW_U32   accessed : 1;       // accessed
            TBRW_U32   readable : 1;       // readable
            TBRW_U32   conforming : 1;     // conforming code segment
            TBRW_U32   oneOne : 2;         // always 11
            TBRW_U32   dpl : 2;            // Dpl
            TBRW_U32   pres : 1;           // present bit
            TBRW_U32   limitHi : 4;        // limit 19:16
            TBRW_U32   sys : 1;            // available for use by system
            TBRW_U32   reserved_0 : 1;     // reserved, always 0
            TBRW_U32   default_size : 1;   // default operation size (1=32bit, 0=16bit)
            TBRW_U32   granularity : 1;    // granularity (1=32 bit, 0=20 bit)
            TBRW_U32   baseHi : 8;         // base hi 31:24
               } ;
          } ;
} TBRW_CodeDescriptor;


typedef struct TBRW_SampleRecordPC_s {   // Program Counter section
    union {
        struct {
            TBRW_U64 iip;            // IA64 interrupt instruction pointer
            TBRW_U64 ipsr;           // IA64 interrupt processor status register
        };
        struct {
            TBRW_U32  eip;           // IA32 instruction pointer
            TBRW_U32  eflags;        // IA32 eflags
            TBRW_CodeDescriptor csd; // IA32 code seg descriptor (8 bytes)
        };
    };
    TBRW_U16    cs;                  // IA32 cs (0 for IA64)
    union {
        TBRW_U16 cpuAndOS;           // cpu and OS info as one word
        struct {                // cpu and OS info broken out
            TBRW_U16 cpuNum : 12;    // cpu number (0 - 4096)
            TBRW_U16 notVmid0 : 1;   // win95, vmid0 flag (1 means NOT vmid 0)
            TBRW_U16 codeMode : 2;   // processor mode, see MODE_ defines
            TBRW_U16          : 1;   // reserved
        };
    };
    TBRW_U32   tid;            // OS thread ID  (may get reused, see tidIsRaw)
    TBRW_U32   pidRecIndex;    // process ID rec index (index into start of pid
                          // record section) .. can validly be 0 if not raw
                          // (array index).  Use ReturnPid() to
                          // ..access this field .. (see pidRecIndexRaw)
    union {
        TBRW_U32 bitFields2;
        struct {
            TBRW_U32   mrIndex : 20;   // module record index (index into start of
                                  // module rec section) .. (see mrIndexNone)
            TBRW_U32   eventIndex : 8;     // index into the Events section
            TBRW_U32   tidIsRaw : 1;       // tid is raw OS tid
            TBRW_U32   IA64PC : 1;         // TRUE=this is a IA64 PC sample record
            TBRW_U32   pidRecIndexRaw : 1; // pidRecIndex is raw OS pid
            TBRW_U32   mrIndexNone : 1;    // no mrIndex (unknown module)
        };
    };
} TBRW_SampleRecordPC, *TBRW_PSampleRecordPC;


typedef struct TBRW_SampleRecordTSC_s {
    TBRW_U64 tsc;     // processor timestamp counter
} TBRW_SampleRecordTSC;
/*
 * End - VTune sampling data structure
 */





//The following are data structure used to hold bind information
//
// DATA_BIND_STRUCT
//
//Note: there is a 1:1 mapping between elements of this type
//and the sample record
typedef struct __data_bind_struct
{
    TBRW_U64 module_index; //index into the module array
    TBRW_U64 pid_index; //index into the pid array
    TBRW_U64 tid_index; //index into the tid array

} DATA_BIND_STRUCT;

TBRW_VERIFY_SIZEOF(DATA_BIND_STRUCT, 24);

//
// MODULE_BIND_STRUCT
//
//Note: there is a 1:1 mapping between elements of this type
//and the module record
typedef struct __module_bind_struct
{
    TBRW_U64 pid_index; //index into the pid array

} MODULE_BIND_STRUCT;

TBRW_VERIFY_SIZEOF(MODULE_BIND_STRUCT, 8);

//
// TID_BIND_STRUCT
//
//Note: there is a 1:1 mapping between elements of this type
//and the tid record
typedef struct __tid_bind_struct
{
    TBRW_U64 pid_index; //index into the pid array

} TID_BIND_STRUCT;

TBRW_VERIFY_SIZEOF(TID_BIND_STRUCT, 8);

//
// TBRW_DATA_CALLBACK
//
typedef TBRW_U32 (*TBRW_DATA_CALLBACK)(void *data, TBRW_U32 data_size, TBRW_U32 num_entries, void *user_ptr);

//
// TBRW_PID_CALLBACK
//
typedef TBRW_U32 (*TBRW_PID_CALLBACK)(TBRW_PID *pid, TBRW_U32 pid_data_size,
                                 TBRW_U32 num_entries, void *user_ptr);

//
// TBRW_TID_CALLBACK
//
typedef TBRW_U32 (*TBRW_TID_CALLBACK)(TBRW_TID *tid, TBRW_U32 tid_data_size,
                                 TBRW_U32 num_entries, void *user_ptr);

//
// TBRW_MODULE_CALLBACK
//
typedef TBRW_U32 (*TBRW_MODULE_CALLBACK)(TBRW_MODULE *module, TBRW_U32 module_data_size,
                                 TBRW_U32 num_entries, void *user_ptr);

//
// TBRW_EVENT_CALLBACK
//
typedef TBRW_U32 (*TBRW_EVENT_CALLBACK)(TBRW_EVENT *event, TBRW_U32 event_data_size,
                                 TBRW_U32 num_entries, void *user_ptr);

//
// TBRW_DATA_DESC_CALLBACK
//
typedef TBRW_U32 (*TBRW_DATA_DESC_CALLBACK)(TBRW_SAMPREC_DESC_ENTRY *data_desc, TBRW_U32 data_desc_size,
                                 TBRW_U32 num_entries, void *user_ptr);

//
// BIND_DATA_CALLBACK
//
typedef TBRW_U32 (*BIND_DATA_CALLBACK)(const void *data, TBRW_U32 sizeof_data_buffer, TBRW_U64 num_entries,
                                  const DATA_BIND_STRUCT *bind_table, TBRW_U32 sizeof_bind_buffer, void *user_ptr);

//
// BIND_MODULE_CALLBACK
//
typedef TBRW_U32 (*BIND_MODULE_CALLBACK)(const TBRW_MODULE *module, TBRW_U32 sizeof_module_buffer,
                                    TBRW_U64 num_entries, const MODULE_BIND_STRUCT *bind_table,
                                    TBRW_U32 sizeof_bind_buffer, void *user_ptr);
//
// BIND_TID_CALLBACK
//
typedef TBRW_U32 (*BIND_TID_CALLBACK)(const TBRW_TID *tid, TBRW_U32 sizeof_tid_buffer, TBRW_U64 num_entries,
                                 const TID_BIND_STRUCT *bind_table, TBRW_U32 sizeof_bind_buffer, void *user_ptr);


#endif  // __TBRW_TYPES_H__

