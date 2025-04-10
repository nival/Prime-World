/* /////////////////////////////////////////////////////////////////////////////
//
//                  INTEL CORPORATION PROPRIETARY INFORMATION
//     This software is supplied under the terms of a license agreement or
//     nondisclosure agreement with Intel Corporation and may not be copied
//     or disclosed except in accordance with the terms of that agreement.
//          Copyright(c) 2002-2004 Intel Corporation. All Rights Reserved.
//
//
*/

#if !defined(_VT_TIGGERS_)
#define VT_TRIGGERS_API _declspec(dllimport)
#else
#define VT_TRIGGERS_API _declspec(dllexport)
#endif

#define DEFAULTTIMEINTERVAL 1000

#ifdef __cplusplus
extern "C" {
VT_TRIGGERS_API DWORD VT_RegisterTrigger(LPTSTR pszTriggerName, DWORD dwIncrements, LPTSTR pszUnits, HANDLE* pHandle);
VT_TRIGGERS_API DWORD VT_UnregisterTrigger(HANDLE hTriggerID);
VT_TRIGGERS_API DWORD VT_SetTrigger(HANDLE hTriggerID);
}
#endif
