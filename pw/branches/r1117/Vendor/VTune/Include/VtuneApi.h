/*************************************************************************
 *
 *              INTEL CORPORATION PROPRIETARY INFORMATION
 *  This software is supplied under the terms of a license agreement or
 *  nondisclosure agreement with Intel Corporation and may not be copied
 *  or disclosed except in accordance with the terms of that agreement.
 *
 *    Copyright(c) 2002-2007 Intel Corporation. All Rights Reserved.
 *
 ************************************************************************/

/*
 * 
 * VtuneApi.h
 *
 *
 * This header file provides declarations and usage model for following APIs.
 * 
 *       VTStartSampling, VTStopSampling, VTBindSamplingResults
 *       VTPause, VTResume
 *       VTPauseSampling, VTResumeSampling
 *
 */

#ifndef _VTUNEAPI_H_
#define _VTUNEAPI_H_

#if !defined (__linux__) && !defined (_WIN32)
#error "Unsupported operating system detected"
#endif

#include "vt_errors.h"
#include "VtuneApiTypes.h"

#if defined(_WIN32)
#   if defined(_VTUNEAPI_EXPORT_)
#       define VTUNEAPI __declspec(dllexport)
#   else
#       define VTUNEAPI __declspec(dllimport)
#   endif
#   define VTUNEAPICALL __stdcall
#elif defined(__linux__)
#   define VTUNEAPI
#   define VTUNEAPICALL
#endif

/////////////////////////////////////////////////////////

#define VTAPI_EVENT_SAMPLED                   0x01

// The following bit-flags can be used to pass in the globalOptions field.
#define VTAPI_OPTIONS_ENABLE_LBR              0x01

/*************************************************************/
// VTUNE_EVENT

typedef struct __vtune_event {
	U64 sampleAfter;             // Sample After value for this event.
	U64 parameter;               // Reserved field - (MUST be set to 0).
	U32 options;                 // Reserved field - (MUST be set to 0).
	U32 status;                  // Field to return status by the VTStartSampling.
                                     // Used to indicate which events could be sampled
                                     // in a single run, if there are too many events.
	char *name;                  // event name.

} VTUNE_EVENT, *PVTUNE_EVENT;


/*************************************************************/
// VTUNE_SAMPLING_PARAMS

typedef struct __vtune_sampling_params {
  U32   sizeVtuneSamplingParams; // caller sets to sizeof(VTUNE_SAMPLING_PARAMS)
  U32   sizeVtuneEvent;         // caller sets to sizeof(VTUNE_EVENT)
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
  VTUNE_EVENT *pEvents;         // Pointer to event information array.
                                // Ignored, if TBS is selected.
  char  *tb5Filename;           // tb5 filename. Could be simple or path 
                                // qualified.
  UIOP  reservedField;          // Reserved field, must be set to 0.
  U32	count;                  // 1 indicates a counts file will be generated.
				// Default is 0. Counts file name is tb5Filename.txt.
  char  *cpu_mask;		// Provide a cpu mask to sample on specified cpu's.
				// eg: "0,1,2-15,34"

} VTUNE_SAMPLING_PARAMS, *PVTUNE_SAMPLING_PARAMS;

#if defined(__cplusplus)

extern "C" {

#endif   // __cplusplus

/* =================================================================
 * VTStartSampling, VTStopSampling and VTBindSamplingResults
 * =================================================================
 *
 * VTStartSampling enables users to configure and start local 
 * sampling from within their applications. The result is a .tb5 file that 
 * the users can open using VTune(TM) Performance Analyzer. The user can stop 
 * the collection by calling VTStopSampling. 
 *
 * VTStartSampling arguments
 *     VTUNE_SAMPLING_PARAMS *samParams : Sampling params structure that 
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
 *               Caller can check the 'status' field of VTUNE_EVENT entries
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
 * #include "VtuneApi.h"
 * int main ()
 * {
 *    VTUNE_EVENT events[] = {
 *        { 10000, 0, 0, 0, "Clockticks" },
 *        { 10000, 0, 0, 0, "Instructions Retired" },
 *    };
 *
 *    U32 numEvents = sizeof(events) / sizeof(VTUNE_EVENT);
 *    VTUNE_SAMPLING_PARAMS params = {
 *        sizeof(VTUNE_SAMPLING_PARAMS),
 *        sizeof(VTUNE_EVENT),
 *        0,
 *        0,
 *        0, 
 *        0, 
 *        1000, 
 *        40,    
 *        1, 
 *        numEvents, 
 *        events, 
 *        "results.tb5",
 *        0,
 *        0,
 *        ""
 *    };
 *
 *    U32 u32Return = VTStartSampling(&params);
 *
 *
 *    if (u32Return) { 
 *        // Handle error here...
 *        exit(0);
 *    }
 *
 *    // Some user code goes here...
 *    // ...
 *    // ...
 *
 *    u32Return = VTStopSampling(1);
 *    if (u32Return) {
 *        // handle error...
 *        exit(0);
 *    }
 *    
 *    // The rest of the code goes here...
 *    // ...
 *    // ...
 * } 
 *
 *
 *  LINK REQUIREMENTS :
 *
 *  The user program needs to link with VtuneApi.lib on Windows* and
 *  with libVtuneApi.so on Linux*. Also, some dependent VTune(TM) analyzer 
 *  libraries have to be in the path on Windows* and in the LD_LIBRARY_PATH
 *  on Linux*.
 *
 *  On Linux*, the user program also needs to link with libpthread.so.
 *
 */         
 
VTUNEAPI
U32 VTUNEAPICALL VTStartSampling(VTUNE_SAMPLING_PARAMS *samParams);

VTUNEAPI
U32 VTUNEAPICALL VTStopSampling(U32 bBindSamplingResults);

VTUNEAPI
U32 VTUNEAPICALL VTBindSamplingResults(char *tb5Filename);

/* =================================================================
 *		
 * VTPause and VTResume
 *
 * =================================================================
 *
 * VTPause and VTResume pause or resume data collection during a 
 * Sampling, Counter Monitor, or Callgraph activity.
 *
 * If VTPause is called while a  Sampling collection is active, a flag 
 * is set which suspends collection of PC samples on the current machine. 
 * Collection of PC samples can be resumed by calling VTResume which clears 
 * the flag. The overhead to set and clear the flag is very low, so the 
 * VTPause and VTResume can be called at a high frequency.
 *
 * If VTPause is called while a  Callgraph collection is active, 
 * Callgraph data collection is paused for the current process. Callgraph 
 * data collection for the current process can be resumed by calling 
 * VTResume.
 *
 * If VTPause is called while a  Counter Monitor collection is active, 
 * Counter Monitor data collection is paused. Counter Monitor data collection 
 * can be resumed by calling VTResume.
 *
 * VTPause and VTResume can be safely called when the Sampling, Counter 
 * Monitor, and Callgraph collectors are not active.In this case, the 
 * VTPause and VTResume do nothing.
 *
 * NOTE:
 *
 * Sampling, Counter Monitor, and Callgraph activities are typically 
 * started with the VTune(TM) Performance Analyzer application. 
 * The VTune(TM) Performance Analyzer GUI allows Sampling, 
 * Counter Monitor, and Callgraph activities to be started in "Pause" mode
 * which suspends data collection until a VTResume is called.
 * Data collection can also be paused and resumed by the Pause/Resume button 
 * in the VTune(TM) Performance Analyzer GUI.
 * See VTune(TM) Performance Analyzer onlilne help for more details.
 */

VTUNEAPI
void VTUNEAPICALL VTPause(void);

VTUNEAPI
void VTUNEAPICALL VTResume(void);

VTUNEAPI
void VTUNEAPICALL VTNameThread(const char *);

/* =================================================================
 *		
 * VTPauseSampling and VTResumeSampling
 *
 * =================================================================
 *
 * These APIs are provided for backward compatibility.
 *
 */

VTUNEAPI
void VTUNEAPICALL VTPauseSampling(void);

VTUNEAPI
void VTUNEAPICALL VTResumeSampling(void);

#if defined (_WIN32)
VTUNEAPI
void VTUNEAPICALL VTPauseCounterMonitor(void);

VTUNEAPI
void VTUNEAPICALL VTResumeCounterMonitor(void);
#endif


#if defined(__cplusplus)
}
#endif   // __cplusplus

#endif  // _VTUNEAPI_H_

/* vim: set ts=8 sw=4 sts=4 et : */
