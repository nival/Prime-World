/**********************************************************************************************
 * INTEL CONFIDENTIAL
 * Copyright 2002-2009 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related to the source code
 * ("Material") are owned by Intel Corporation or its suppliers or licensors. Title to the
 * Material remains with Intel Corporation or its suppliers and licensors. The Material
 * contains trade secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright and trade secret
 * laws and treaty provisions. No part of the Material may be used, copied, reproduced,
 * modified, published, uploaded, posted, transmitted, distributed, or disclosed in any way
 * without Intel's prior express written permission.
 *
 * No license under any patent, copyright, trade secret or other intellectual property right
 * is granted to or conferred upon you by disclosure or delivery of the Materials, either
 * expressly, by implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in writing.
 */

#if !defined(__VT_ERRORS_H__)
#define __VT_ERRORS_H__

//
// THIS FILE IS DEPRECATED!
// THIS FILE IS DEPRECATED!
// THIS FILE IS DEPRECATED!
//
// Don't include it directly. Include
// #include "rise.h"
// going forward instead
//
// THIS FILE IS DEPRECATED!
// THIS FILE IS DEPRECATED!
// THIS FILE IS DEPRECATED!
//

//
// NOTE:
//
// 1) Before adding an error code, first make sure the error code doesn't
// already exist. If it does, use that, don't create a new one just because...
//
// 2) When adding an error code, add it to the end of the list. Don't insert
// error numbers in the middle of the list! For backwards compatibility,
// we don't want the numbers changing unless we really need them
// to for some reason (like we want to switch to negative error numbers)
//
// 3) Change the VT_LAST_ERROR_CODE macro to point to the (newly added)
// last error. This is done so SW can verify the number of error codes
// possible matches the number of error strings it has
//
// 4) Don't forget to update the error string table to include your
// error code (rise_class.cpp). Since the goal is something human readable
// you don't need to use abbreviations in there (ie. don't say "bad param",
// say "bad parameter" or "illegal parameter passed in")
//
// 5) Compile and run the test_rise app (in the test_rise directory) to
// verify things are still working
//
// 6) vt_errors.h is (unfortunately) duplicated for the sampling driver. So... you 
// need to update the sampling driver's mainline (vdk/src/include) with the new error
// codes. Keep in mind you can't just do a copy since the sampling driver has GPL headers
// and the public include version does not...
//
// And yes, someday we may want to make these enums instead to make accidental
// duplication of numbers less likely...
//

#define VT_SUCCESS                      0

/*************************************************************/
//VTStartSampling and VTStopSampling Error codes
//

#define VT_INVALID_MAX_SAMP                   1
#define VTAPI_INVALID_MAX_SAMP                VT_INVALID_MAX_SAMP

#define VT_INVALID_SAMP_PER_BUFF              2
#define VTAPI_INVALID_SAMP_PER_BUFF           VT_INVALID_SAMP_PER_BUFF

#define VT_INVALID_SAMP_INTERVAL              3
#define VTAPI_INVALID_SAMP_INTERVAL           VT_INVALID_SAMP_INTERVAL

#define VT_INVALID_PATH                       4
#define VTAPI_INVALID_PATH                    VT_INVALID_PATH
                         // invalid .tb5 filename
#define VT_TB5_IN_USE                         5
#define VTAPI_TB5_IN_USE                      VT_TB5_IN_USE

                         //If an .sdb file with the
                         //same name as that of the .tb5 file specified by
                         //the user exists in the specified directory and
                         //VTune(TM) analyzer is currently using that .sdb,
                         //then VTune(TM) analyzer
                         //should release access to it. This is because
                         //VTStartSampling deletes the previous .sdb (if any)
                         //so that the next time VTune(TM) analyzer is used
                         //to open the
                         //new .tb5, the previous .sdb is not used.

#define VT_INVALID_NUM_EVENTS                 6
#define VTAPI_INVALID_NUM_EVENTS              VT_INVALID_NUM_EVENTS

#define VT_INTERNAL_ERROR                     8
#define VTAPI_INTERNAL_ERROR                  VT_INTERNAL_ERROR
                       //An internal error occurred in VTStartSampling or
                       //VTStopSampling

#define VT_BAD_EVENT_NAME                     9
#define VTAPI_BAD_EVENT_NAME                  VT_BAD_EVENT_NAME
                       //The specified event doesn't exist.

#define VT_NO_SAMP_SESSION                   10
#define VTAPI_NO_SAMP_SESSION                VT_NO_SAMP_SESSION
                       //VTStopSampling was called without calling
                       //VTStartSampling first

#define VT_NO_EVENTS                         11
#define VTAPI_NO_EVENTS                      VT_NO_EVENTS
                       //No events were selected for Event Based Sampling
                       //and there are no default events

#define VT_MULTIPLE_RUNS                     12
#define VTAPI_MULTIPLE_RUNS                  VT_MULTIPLE_RUNS
                       //All of the selected events cannot be run together
                       //in a single run. Only the events that can run together
                       //in the first run are selected for sampling.
                       //
                       // NOTE :This is a NON-FATAL error returned by VtStartSampling()
                       // and the calling program must call VtStopSampling() before
                       // exiting when this error condition happens.

#define VT_NO_SAM_PARAMS                     13
#define VTAPI_NO_SAM_PARAMS                  VT_NO_SAM_PARAMS

#define VT_SDB_ALREADY_EXISTS                14
#define VTAPI_SDB_ALREADY_EXISTS                VT_SDB_ALREADY_EXISTS

#define VT_SAMPLING_ALREADY_STARTED          15
#define VTAPI_SAMPLING_ALREADY_STARTED       VT_SAMPLING_ALREADY_STARTED

#define VT_TBS_NOT_SUPPORTED                 16
#define VTAPI_TBS_NOT_SUPPORTED              VT_TBS_NOT_SUPPORTED
                       // This error is returned when time based sampling is requested
                       // on a system that does not support time based sampling.

#define VT_INVALID_SAMPARAMS_SIZE            17
#define VTAPI_INVALID_SAMPARAMS_SIZE         VT_INVALID_SAMPARAMS_SIZE
                       // The size specified in field sizeVtuneSamplingParams is incorrect

#define VT_INVALID_EVENT_SIZE                18
#define VTAPI_INVALID_EVENT_SIZE             VT_INVALID_EVENT_SIZE
                       // The size specified in field sizeVtuneEvent is incorrect

#define VT_ALREADY_PROCESSES                 19
#define VTAPI_ALREADY_PROCESSES                 VT_ALREADY_PROCESSES
                       // The file passed to VTBindSamplingResults was
                       // already processed

#define VT_INVALID_EVENTS_PATH               20
#define VTAPI_INVALID_EVENTS_PATH            VT_INVALID_EVENTS_PATH
                       // Specified path to events file is invalid.

#define VT_INVALID_LICENSE                   21
#define VTAPI_INVALID_LICENSE                VT_INVALID_LICENSE
                       // No valid VTune(TM) Performance Analyzer license found.

/******************************************************/
//Sep error codes

#define VT_SAM_ERROR                    22
#define VT_SAMPLE_FILE_ALREADY_MAPPED   23
#define VT_INVALID_SAMPLE_FILE          24
#define VT_UNKNOWN_SECTION_NUMBER       25
#define VT_NO_MEMORY                    26
#define VT_ENV_VAR_NOT_FOUND            27
#define VT_SAMPLE_FILE_NOT_MAPPED       28
#define VT_BUFFER_OVERFLOW              29
#define VT_USER_OP_COMPLETED            30
#define VT_BINARY_NOT_FOUND             31
#define VT_ISM_NOT_INITIALIZED          32
#define VT_NO_SYMBOLS                   33
#define VT_SAMPLE_FILE_MAPPING_ERROR    34
#define VT_BUFFER_NULL                  35
#define VT_UNEXPECTED_NULL_PTR          36
#define VT_BINARY_LOAD_FAILED           37 //use this if vt_dlopen failed
#define VT_FUNCTION_NOT_FOUND_IN_BINARY 38 //use this if vt_dlsym failed
#define VT_ENTRY_NOT_FOUND              39
#define VT_SEP_SYNTAX_ERROR             40 //use this for sep syntax error
#define VT_SEP_OPTIONS_ERROR            41 //use this for sep start options error
#define VT_BAD_EVENT_MODIFIER           42
#define VT_INCOMPATIBLE_PARAMS          43
#define VT_FILE_OPEN_FAILED             44
#define VT_EARLY_EXIT                   45 //early exit is requested
#define VT_TIMEOUT_RETURN               46 //timeout was reached and no early exit was requested
#define VT_NO_CHILD_PROCESS             47 //use for vt_wait_for_child_to_exit
#define VT_DRIVER_RUNNING               48 //used by early_exit
#define VT_DRIVER_STOPPED               49 //used by early_exit
#define VT_MULTIPLE_RUNS_NEEDED         50
#define VT_QUIT_IMMEDIATE               51
#define VT_DRIVER_INIT_FAILED           52
#define VT_NO_TB5_CREATED               53 //used to indicate no tb5 file was created (perhaps due to no samples collected)
#define VT_NO_WRITE_PERMISSION          54
#define VT_DSA_INIT_FAILED              55
#define VT_INVALID_CPU_MASK             56
#define VT_SAMP_IN_RUNNING_STATE        57 //used by run_handler to return state errors
#define VT_SAMP_IN_PAUSE_STATE          58 //used by run_handler to return state errors
#define VT_SAMP_IN_STOP_STATE           59 //used by run_handler to return state errors
#define VT_SAMP_NO_SESSION              60 //used by run_handler to return state errors
#define VT_NOT_CONFIGURED               61
#define VT_LAUNCH_BUILD64_FAILED        62 //used by config_n_control.DoStart()
#define VT_BAD_PARAMETER                63 //used by vtuneapi_entry.cpp for now

#define VT_ISM_INIT_FAILED              64 // used by symbols.cpp
#define VT_INVALID_STATE_TRANS          65 //used by CASI to indicate invalid state
#define VT_EARLY_EXIT_N_CANCEL          66 //indicates cancel a sampling session
#define VT_EVT_MGR_NOT_INIT             67
#define VT_ISM_SECTION_ENUM_FAILED      68 // used by symbols.cpp 
#define VT_VG_PARSER_ERROR              69
#define VT_MISSING_VALUE_FOR_TOKEN      70
#define VT_EMPTY_SAMPLE_FILE_NAME       71
#define VT_UNEXPECTED_VALUE             72
#define VT_NOT_IMPLEMENTED            	73
#define VT_MISSING_COL_DEPNDNCIES       74
#define VT_DEP_COL_NOT_LIB_DEFINED      75
#define VT_COL_NOT_REG_WITH_LIB         76
#define VT_SECTION_ALREADY_IN_USE       77 //used by tbrw
#define VT_SECTION_NOT_EXIST            78 //used by tbrw
#define VT_STREAM_NOT_EXIST             79 //used by tbrw
#define VT_INVALID_STREAM               80 //used by tbrw
#define VT_STREAM_ALREADY_IN_USE        81
#define VT_DATA_DESC_NOT_EXIST          82
#define VT_INVALID_ERROR_CODE           83
#define VT_INCOMPATIBLE_VERSION         84
#define VT_LEGACY_DATA_NOT_EXIST        85   
#define VT_INVALID_READ_START           86
#define VT_DRIVER_OPEN_FAILED           87
#define VT_DRIVER_IOCTL_FAILED          88
#define VT_SAMP_FILE_CREATE_FAILED      89
#define VT_MODULE_FILE_CREATE_FAILED    90
#define VT_INVALID_SAMPLE_FILE_NAME     91
#define VT_INVALID_MODULE_FILE_NAME     92
#define VT_FORK_CHILD_PROCESS_FAILED    93
#define VT_UNEXPECTED_MISMATCH_IN_STRING_TYPES    94
#define VT_INCOMPLETE_TB5_ENCOUNTERED   95
#define VT_ERR_CONVERSION_FROM_STRING_2_NUMBER 96
#define VT_INVALID_STRING               97
#define VT_UNSUPPORTED_DATA_SIZE        98
#define VT_TBRW_INIT_FAILED             99  
#define VT_PLUGIN_UNLOAD                100
#define VT_PLUGIN_ENTRY_NULL            101
#define VT_UNKNOWN_PLUGIN               102
#define VT_BUFFER_TOO_SMALL             103
#define VT_CANNOT_MODIFY_COLUMN         104
#define VT_MULT_FILTERS_NOT_ALLOWED     105
#define VT_ADDRESS_IN_USE               106
#define VT_NO_MORE_MMAPS                107
#define VT_MAX_PAGES_IN_DS_EXCEEDED     108
#define VT_INVALID_COL_TYPE_IN_GROUP_INFO 109
#define VT_AGG_FN_ON_VARCHAR_NOT_SUPP   110
#define VT_INVALID_ACCESS_PERMS         111
#define VT_NO_DATA_TO_DISPLAY           112
#define VT_TB5_IS_NOT_BOUND             113
#define VT_MISSING_GROUP_BY_COLUMN      114
#define VT_SMRK_MAX_STREAMS_EXCEEDED    115
#define VT_SMRK_STREAM_NOT_CREATED      116
#define VT_SMRK_NOT_IMPL                117
#define VT_SMRK_TYPE_NOT_IMPL           118
#define VT_SMRK_TYPE_ALREADY_SET        119
#define VT_SMRK_NO_STREAM               120
#define VT_SMRK_INVALID_STREAM_TYPE     121
#define VT_SMRK_STREAM_NOT_FOUND        122
#define VT_SMRK_FAIL                    123
#define VT_SECTION_NOT_READABLE         124
#define VT_SECTION_NOT_WRITEABLE        125
#define VT_GLOBAL_SECTION_NOT_CLOSED    126
#define VT_STREAM_SECTION_NOT_CLOSED    127
#define VT_STREAM_NOT_CLOSED            128
#define VT_STREAM_NOT_BOUND             129
#define VT_NO_COLS_SPECIFIED            130
#define VT_NOT_ALL_SECTIONS_CLOSED      131
#define VT_SMRK_INVALID_PTR             132
#define VT_UNEXPECTED_BIND_MISMATCH     133
#define VT_WIN_TIMER_ERROR              134
#define VT_ONLY_SNGL_DEPNDT_COL_ALLWD   135
#define VT_BAD_MODULE                   136
#define VT_INPUT_SOURCE_INFO_NOT_SET    137
#define VT_UNSUPPORTED_TIME_GRAN        138
#define VT_NO_SAMPLES_COLLECTED         139
#define VT_INVALID_CPU_TYPE_VERSION     140
#define VT_BIND_UNEXPECTED_1STMODREC    141
#define VT_BIND_MODULES_NOT_SORTED      142
#define VT_UNEXPECTED_NUM_CPUIDS        143
#define VT_UNSUPPORTED_ARCH_TYPE        144
#define VT_NO_DATA_TO_WRITE             145
#define VT_EM_TIME_SLICE_TOO_SMALL      146  //for event multiplexing
#define VT_EM_TOO_MANY_EVENT_GROUPS     147  //for event multiplexing
#define VT_EM_ZERO_GROUPS               148  //for event multiplexing
#define VT_EM_NOT_SUPPORTED             149  //for event multiplexing
#define VT_PMU_IN_USE                   150
#define VT_TOO_MANY_INTERRUPTS          151
#define VT_MAX_SAMPLES_REACHED          152
#define VT_MODULE_COLLECTION_FAILED     153
#define VT_INCOMPATIBLE_DRIVER          154
#define VT_UNABLE_LOCATE_TRIGGER_EVENT  155

//
// To make error checking easier, the special VT_LAST_ERROR_CODE
// should be set to whatever is the last error on the list above
//
#define VT_LAST_ERROR_CODE              VT_UNABLE_LOCATE_TRIGGER_EVENT

//
// Define a macro to determine success or failure. Users of this
// error header file should use the macros instead of direct
// checks so that we can change the error numbers in the future
// (such as making negative numbers be an error indication and positive
// numbers being a success with a value indication)
//
#define     VTSA_SUCCESS(x)     ((x) == VT_SUCCESS)
#define     VTSA_FAILED(x)      (!VTSA_SUCCESS(x))

//
// These should be deprecated, but we'll keep them here just in case
//
#define     SEP_IS_SUCCESS(x) VTSA_SUCCESS(x)
#define     SEP_IS_FAILED(x)  VTSA_FAILED(x)

//
// linuxsubs perfmon2 error codes
//
// Don't add anything here. These codes actually need to be removed/merged
// into the above list. DON'T CREATE SPECIALITY AREAS!
//
#define VT_PM2_CREATE_CONTEXT_FAILED    1000
#define VT_PM2_WRITE_PMCS_FAILED        1001
#define VT_PM2_WRITE_PMDS_FAILED        1002
#define VT_PM2_LOAD_CONTEXT_FAILED      1003
#define VT_PM2_START_FAILED             1004
#define VT_PM2_STOP_FAILED              1005
#define VT_INVALID_EVENTS               1006
#define VT_SMP_CALL_INIT_FAILED         1007

#endif
