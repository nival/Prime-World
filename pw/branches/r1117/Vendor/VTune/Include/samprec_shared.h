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

//
// File Name: samprec_shared.h
// Description: contains sample record meta-data information that is
//              shared between user mode and driver mode code.
//
//

#if !defined(__SAMPREC_SHARED_H__)
#define __SAMPREC_SHARED_H__

typedef enum {
    ST_NONE = 0,
    ST_LEGACY_SAMPLE_RECORD,
    ST_IP,
    ST_PID,
    ST_TID,
    ST_PROCESSOR_NUMBER,
    ST_PROCESSOR_STATUS,
    ST_TIME_STAMP,
    ST_POWER,
    ST_INTERRUPT_FAULT_ADDR,
    ST_IEAR,
    ST_DEAR,
    ST_BRANCH_TRACE,
    ST_INST_TRACE,
    ST_PMD,
    ST_IEAR_PHYSICAL,
    ST_DEAR_PHYSICAL,
    ST_BRANCH_TRACE_PHYSICAL,
    ST_INST_TRACE_PHYSICAL,
    ST_PMD_PHYSICAL,
    ST_PEBS_MACHINE_STATE,
    ST_UNCORE_TAG_NUMBER,
    ST_DEAR_INFO,
    ST_LEGACY_UNKNOWN, //unknown legacy type

    //
    // Extended sample record entries start here - these entries do
    // not physically reside in a sample record but can be computed 
    // based on data in a physical sample record
    //
    // I.E. (bit 14 and up == 0) &&  (bit 13 == 1) && (bit 12 == 0)
    // means extended sample record entries
    // (decimal 8192 through 12287) = 4096 values
    //
    ST_START_EXT_SAMPLE_REC_ENTRIES = 0x2000,
    ST_END_EXT_SAMPLE_REC_ENTRIES = 0x2FFF,

    ST_PROCESS = 0x2000,                 // process name
    ST_PROCESS_PATH,            // process path
    ST_PROCESS_IDX,

    ST_THREAD,                  // thread name
    ST_THREAD_IDX,
    
    ST_MODULE,                  // module name
    ST_MODULE_PATH,             // module path
    ST_MODULE_LOAD_ADDRESS,     // module load address
    ST_MODULE_IDX,

    ST_SEG_NAME,                // module segment name
    ST_SEG_NUM,                 // module segment number
    ST_SEG_OFFSET,
    ST_SEG_TYPE,
    
    ST_EVENT,                   // event name
    ST_EVENT_ID,                // event ID 
    ST_EVENT_IDX,

    ST_CORE,                    // core number 
    ST_HARDWARE_THREAD,         // hardware thread 
    ST_PACKAGE,                 // package number


    ST_FUNCTION,
    ST_FN_RVA,
    ST_FN_SIZE,
    ST_FUNCTION_FULL_NAME,
    ST_FN_SEG_OFFSET,
    ST_CLASS,
    ST_RVA,

    ST_FNID_SUM,			    // e.g. sum(some_column)
    ST_FNID_AVG,				// e.g. avg(some_column)
    ST_FNID_MIN,				// e.g. min(some_column)
    ST_FNID_MAX,				// e.g. max(some_column)

    ST_SAMPLES,
    ST_SAMPLE_IDX,
    ST_WALL_CLOCK,              // Wall clock.

    ST_EVENT_COUNTS,
    ST_PERCENTAGE_TOTAL,
    ST_PERCENTAGE_SEL,

    ST_ANNOTATION,              // Annotation text.

    ST_CS, // code-selector
    ST_MODE, // mode, i.e. MODE_{{64,32,16}BIT,V86}

    ST_POST_PROCESS_LAST,

    //
    // Available to users, vtune will ignore
    //
    // I.E. (bit 15 == 0) &&  (bit 14 == 1) means user-defined.
    // (decimal 16384 through 32767)
    //
    ST_START_USER_DEFINED = 0x4000,
    ST_END_USER_DEFINED = 0x7FFF,

    //
    // For future use...
    //
    // It is an error to use a type between
    // ST_RESERVED_START and ST_RESERVED_END, inclusive
    //
    ST_RESERVED_START = 0x8000,
    ST_RESERVED_END = 0xffff

} TBRW_DESC_TYPE;

typedef enum {
    SST_NONE = 0,

    //
    // Indicates a no data should be filled in by the driver,
    // but is left empty for someone else to use
    //
    SST_BLANK_SPACE,

    // Subtypes for time
    SST_TS_MILLISECONDS,
    SST_TS_CPU_CYCLES,
    SST_TS_FSB_CYCLES,
    SST_TS_OTHER,
    SST_TS_SAMPLE_COUNT,
    SST_TS_NANOSECONDS,

    // subtypes for BTB register
    SST_LBR_TOS,
    SST_LBR_FROM,
    SST_LBR_TO,
    SST_LBR_FROM_TO,
    SST_LBR_OTHER,

    SST_IEAR_CONFIG,
    SST_IEAR_INST_ADDR,
    SST_IEAR_LATENCY,

    SST_DEAR_CONFIG,
    SST_DEAR_INST_ADDR,
    SST_DEAR_LATENCY,
    SST_DEAR_DATA_ADDR,

    SST_BTB_CONFIG,
    SST_BTB_INDEX,
    SST_BTB_EXTENSION,
    SST_BTB_DATA,

    SST_IPEAR_CONFIG,
    SST_IPEAR_INDEX,
    SST_IPEAR_EXTENSION,
    SST_IPEAR_DATA,

    SST_IIP,
    SST_IPSR,
    SST_EIP,
    SST_EFLAGS,
    SST_TSC,
    SST_ITC,
    SST_RAW,
    SST_PSTATE,
    SST_IA32_PERF_STATUS,
    SST_THERMAL,             
    SST_IFA,

    SST_LBR_FROM_TO_0,
    SST_LBR_FROM_TO_1,
    SST_LBR_FROM_TO_2,
    SST_LBR_FROM_TO_3,

    SST_LBR_FROM_0,
    SST_LBR_FROM_1,
    SST_LBR_FROM_2,
    SST_LBR_FROM_3,
    SST_LBR_FROM_4,
    SST_LBR_FROM_5,
    SST_LBR_FROM_6,
    SST_LBR_FROM_7,
    SST_LBR_FROM_8,
    SST_LBR_FROM_9,
    SST_LBR_FROM_10,
    SST_LBR_FROM_11,
    SST_LBR_FROM_12,
    SST_LBR_FROM_13,
    SST_LBR_FROM_14,
    SST_LBR_FROM_15,

    SST_LBR_TO_0,
    SST_LBR_TO_1,
    SST_LBR_TO_2,
    SST_LBR_TO_3,
    SST_LBR_TO_4,
    SST_LBR_TO_5,
    SST_LBR_TO_6,
    SST_LBR_TO_7,
    SST_LBR_TO_8,
    SST_LBR_TO_9,
    SST_LBR_TO_10,
    SST_LBR_TO_11,
    SST_LBR_TO_12,
    SST_LBR_TO_13,
    SST_LBR_TO_14,
    SST_LBR_TO_15,

    SST_BTB_DATA_0,
    SST_BTB_DATA_1,
    SST_BTB_DATA_2,
    SST_BTB_DATA_3,
    SST_BTB_DATA_4,
    SST_BTB_DATA_5,
    SST_BTB_DATA_6,
    SST_BTB_DATA_7,
    SST_BTB_DATA_8,
    SST_BTB_DATA_9,
    SST_BTB_DATA_10,
    SST_BTB_DATA_11,
    SST_BTB_DATA_12,
    SST_BTB_DATA_13,
    SST_BTB_DATA_14,
    SST_BTB_DATA_15,

    SST_IPEAR_DATA_0,
    SST_IPEAR_DATA_1,
    SST_IPEAR_DATA_2,
    SST_IPEAR_DATA_3,
    SST_IPEAR_DATA_4,
    SST_IPEAR_DATA_5,
    SST_IPEAR_DATA_6,
    SST_IPEAR_DATA_7,
    SST_IPEAR_DATA_8,
    SST_IPEAR_DATA_9,
    SST_IPEAR_DATA_10,
    SST_IPEAR_DATA_11,
    SST_IPEAR_DATA_12,
    SST_IPEAR_DATA_13,
    SST_IPEAR_DATA_14,
    SST_IPEAR_DATA_15,

    SST_PEBS_EFLAGS,
    SST_PEBS_LINEARIP,
    SST_PEBS_RAX,
    SST_PEBS_RBX,
    SST_PEBS_RCX,
    SST_PEBS_RDX,
    SST_PEBS_RSI,
    SST_PEBS_RDI,
    SST_PEBS_RBP,
    SST_PEBS_RSP,
    SST_PEBS_R8,
    SST_PEBS_R9,
    SST_PEBS_R10,
    SST_PEBS_R11,
    SST_PEBS_R12,
    SST_PEBS_R13,
    SST_PEBS_R14,
    SST_PEBS_R15,
    
    SST_RESERVED_START = 0xc000,
    SST_RESERVED_END = 0xffff,

    SST_START_USER_DEFINED = 0x80000000,
    SST_END_USER_DEFINED   = 0x8FFFFFFF

} TBRW_DESC_SUBTYPE;

#endif  // __SAMPREC_SHARED_H__
