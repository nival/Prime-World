/**********************************************************************************************
 * INTEL CONFIDENTIAL
 * Copyright 2002-2008 Intel Corporation All Rights Reserved.
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

/*
 *
 * sampling.h
 *
 *
 * This header file provides declarations and usage model for following APIs.
 *
 *       VTStartSampling, VTStopSampling, VTBindSamplingResults
 *       VTPauseSampling, VTResumeSampling
 *
 */

#ifndef _SAMPLING_H_
#define _SAMPLING_H_

#include "vtune_types.h"
#include "rise.h"          // sampling error codes

#if defined(VTSA_OS_WINDOWS)

// Removed the __declspec(dllexport) mechanism for now (for sampling.dll) since it is leading to issues due to
// name mangling (decorated names) of API for __stdcall convention (SCR#32003)
// Instead, defining the non-decorated names of exported API in the sampling.def file
// TODO - Eventually, need to switch back to __declspec(dllexport) mechanism and probably use __cdecl calling convention
#define VTUNEAPI
#define VTUNEAPICALL __stdcall

#elif defined(VTSA_OS_LINUX) || defined(VTSA_OS_DARWIN)
#define VTUNEAPI
#define VTUNEAPICALL
#else
#error "Unknown OS"
#endif

/////////////////////////////////////////////////////////

#define VTSA_EVENT_SAMPLED                   0x01

// The following bit-flags can be used to pass in the globalOptions field.
#define VTSA_OPTIONS_ENABLE_LBR              0x01
#define VTSA_OPTIONS_ENABLE_POWER_STATES     0x02
#define VTSA_OPTIONS_ENABLE_VTUNE_ML         0x04
#define VTSA_OPTIONS_ENABLE_EVENT_MULTIPLEXING 0x08 //indicates event multiplexing is wanted
#define VTSA_OPTIONS_DONT_HANDLE_DURATION    0x10   //when set this indicates sep will not
                                                    //stop sampling after the sampling duration has expired
                                                    //this means it's up to the caller to stop sampling.
#define VTSA_OPTIONS_ENABLE_RT_PROFILING     0x20   // enable RT profiling
#define VTSA_OPTIONS_ENABLE_LBR_FILTERING_MODE 0x40 //enable a particular way of LBR filtering mode
#define VTSA_OPTIONS_ENABLE_LBR_FLT_MODE_MASK 0x41

/*************************************************************/
// VTSA_EVENT

typedef struct __vtsa_event {
    U64 sampleAfter;             // Sample After value for this event.
    U64 parameter;               // Reserved field - (MUST be set to 0).
    U32 options;                 // Reserved field - (MUST be set to 0).
    U32 status;                  // Field to return status by the VTStartSampling.
                                     // Used to indicate which events could be sampled
                                     // in a single run, if there are too many events.
    char *name;                  // event name.

} VTSA_EVENT, *PVTSA_EVENT;


/*************************************************************/
// VTSA_SAMPLING_PARAMS

typedef struct __vtsa_sampling_params {
  U32   sizeVtsaSamplingParams; // caller sets to sizeof(VTSA_SAMPLING_PARAMS)
  U32   sizeVtsaEvent;          // caller sets to sizeof(VTSA_EVENT)
  U64   globalOptions;          // Used to pass sampling options. VTAPI_OPTIONS...
                                // specify the bit-flags (above).
                                // Should be set to 0 if no options need to be
                                // specified.
  U32   globalParameter;        // Reserved - (MUST be set to 0).
  U32   startInPauseMode;       // If 1, start sampling in pause mode
  U32   maxSamples;             // maximum number of samples to be collected.
                                // If this is 0, sampling continues until
                                // VTStopSampling is called.
  U32   samplesPerBuffer;       // number of samples per buffer.
  float fSamplingInterval;      // the sampling interval in miliseconds.
  U32   samplingType;           // 0 for time based sampling.
                                // non-zero for event based sampling.
  U32   nEvents;                // Number of events to be sampled.
  VTSA_EVENT *pEvents;          // Pointer to event information array.
                                // Ignored, if TBS is selected.
  char  *tb5Filename;           // tb5 filename. Could be simple or path
                                // qualified.
  UIOP  reservedField;          // Reserved field, must be set to 0.
  U32   count;                  // 1 indicates a counts file will be generated
                                //   default is 0. Counts file name is tb5Filename.txt
  char  *cpu_mask;              // provide a cpu mask to sample on specified cpus,
                                //   for example, "0,1,2-15,34"
  U32   experimentalOptions;    // Unsupported - should be set to zero
                                //   for non-zero values, the behavior is undefined
  void *cpiConfig;              // Configuration options for CPI, NULL if CPI is
                                //   not currently enabled.  CPI is not currently
                                //   supported for external API users!
  void *emConfig;               // Configuration options for event multiplexing.
                                //   NULL if event multiplexing is not enabled.
                                //   Event Multiplexing is not currently supported for
                                //   external API users!
  U32 emonCount;                // 1 indicates an EMON style counts file will be
                                //   generated. Default is 0. Counts file name
                                //   is tb5Filename.txt

} VTSA_SAMPLING_PARAMS, *PVTSA_SAMPLING_PARAMS;




#if defined(__cplusplus)
extern "C" {
#endif   // __cplusplus


/* =================================================================
 * VTStartSampling, VTStopSampling and VTBindSamplingResults
 * =================================================================
 *
 * VTStartSampling enables users to configure and start local
 * sampling from within their applications. The result is a .tb5 file that
 * the users can analyze using sfdump5 utility which is part of SEP product.
 * The tb5 file can also be opened and analyzed using VTune(TM) Performance Analyzer.
 *
 * The user can stop the collection by calling VTStopSampling.
 *
 * VTStartSampling arguments
 *     VTSA_SAMPLING_PARAMS *samParams : Sampling params structure that
 *                                        is used to configuring sampling.
 *
 * VTStopSampling arguments
 *     U32 bBindSamplingResults : A boolean flag to indicate whether
 *                                    the sampling results (.tb5) file
 *                                    will be processed or not.
 *
 * VTBindSamplingResults arguments
 *     char *tb5Filename            : Simple or absolute filename of a
 *                                    an unprocessed tb5 filename.
 *
 *
 *
 * RETURN Values :
 *        Both VTStartSampling and VTStopSampling return 0 on SUCCESS
 *        and a non-zero value if there is an error.
 *        The returned value can be used to check for errors.
 *        The error codes are defined above.
 *
 *        NOTE : VTAPI_MULTIPLE_RUNS is a non-fatal error returned by
 *               VTStartSampling when all the events specified cannot be
 *               collected in a single run. In this case, sampling is
 *               performed on a subset of events specified by the user.
 *               When this error is returned, the caller is expected to
 *               call VTStopSampling to stop sampling.
 *               Caller can check the 'status' field of VTSA_EVENT entries
 *               to find out which events were sampled.
 *               (status & VTAPI_EVENT_SAMPLED) will be non-zero for
 *               events that were sampled, and 0 otherwise.
 *
 * USAGE MODEL :
 *
 * The following example program shows the usage of these APIs.
 *
 * #include <stdio.h>
 * #include <windows.h>
 * #include "sampling.h"
 * int main ()
 * {
 *
 *
 *    VTSA_EVENT events[] = {
 *      { 1000, 0, 0, 0, "BRANCH_EVENT" },
 *       { 10000, 0, 0, 0, "Clockticks" },
 *     };
 *
 *    U32 numEvents = sizeof(events) / sizeof(VTSA_EVENT);
 *    VTSA_SAMPLING_PARAMS params = { sizeof(VTSA_SAMPLING_PARAMS),
 *                                      sizeof(VTSA_EVENT),
 *                                      0,
 *                                      0,
 *                                      0,
 *                                      0,
 *                                      1000,
 *                                      40,
 *                                      1,
 *                                      numEvents,
 *                                      events,
 *                                      "xyz.tb5" };
 *
 *    U32 u32Return = VTStartSampling(&params);
 *
 *
 *    if (u32Return)
 *    {
 *        // handle error ...
 *        exit(0);
 *    }
 *
 *    // user code
 *    ...
 *    ...
 *
 *    u32Return = VTStopSampling(true);
 *      if (u32Return)
 *    {
 *       // handle error...
 *         exit(0);
 *    }
 *    ...
 *    ...
 *  }
 *
 *
 *  LINK REQUIREMENTS :
 *
 *  The user program needs to link with sampling.lib on Windows* and
 *  with libsampling.so on Linux*. Also, some dependent VTune(TM) analyzer
 *  libraries have to be in the path on Windows* and in the LD_LIBRARY_PATH
 *  on Linux*.
 *
 *  On Linux*, the user program also needs to link with libpthread.so.
 *
 */

VTUNEAPI
U32 VTUNEAPICALL VTStartSampling(VTSA_SAMPLING_PARAMS *samParams);

VTUNEAPI
U32 VTUNEAPICALL VTStopSampling(U32 bBindSamplingResults);

VTUNEAPI
U32 VTUNEAPICALL VTBindSamplingResults(char *tb5Filename);

/* =================================================================
 *
 * VTPauseSampling and VTResumeSampling
 *
 * =================================================================
 *
 * VTPauseSampling and VTResumeSampling pauses or resumes sampling data
 * collection.
 *
 * If VTResumeSampling is called while a sampling collection is active, a flag
 * is set which suspends collection of PC samples on the current machine.
 * Collection of PC samples can be resumed by calling VTPauseSampling which clears
 * the flag. The overhead to set and clear the flag is very low, so the
 * VTPauseSampling and VTResumeSampling can be called at a high frequency.
 *
 * VTPauseSampling and VTResumeSampling can be safely called when the sampling
 * collector is not active. In this case, VTPauseSampling and VTResumeSampling
 * do nothing.
 *
 */

/* =================================================================
 *
 * VTPauseSampling and VTResumeSampling
 *
 * =================================================================
 *
 */

VTUNEAPI
void VTUNEAPICALL VTPauseSampling(void);

VTUNEAPI
void VTUNEAPICALL VTResumeSampling(void);

#if defined(__cplusplus)
}
#endif   // __cplusplus

#endif  // _SAMPLING_H_

