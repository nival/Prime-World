// FILE     : DiString.h
// CONTENTS : Declaration of string management functions
// DATE     : 19.02.1998
// SPEC     : Sandy

#ifndef __DISTRING_H__
#define __DISTRING_H__

#include "DiTypes.h"
//#include "DiFile.h"

//  **********************************************************
//  Types
//  **********************************************************

/**
 * This enum contains string compare result
 * @memo     String compare result
 * @member   DI_STRING_LESS first string less than second
 * @member   DI_STRING_EQUAL strings are equal
 * @member   DI_STRING_MORE first string more than second
 * @header   DiString.h
 */
typedef enum tagDiStringCmpResult
{
  DI_STRING_LESS = -1,
  DI_STRING_EQUAL = 0,
  DI_STRING_MORE = 1,
  DI_STRING_FORCEDWORD = 0x7FFFFFFF
} DiStringCmpResult;

typedef DiStringCmpResult (*DiStringCmpFunction)(DiTChar *sStr1, DiTChar * sStr2);

//  **********************************************************
//  Functions prototype
//  **********************************************************

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

// extract something from string
extern DiVoid DiStringExtractDisk     (DiTChar *cpFullFileName, DiTChar *cpDisk);
extern DiVoid DiStringExtractPath     (DiTChar *cpFullFileName, DiTChar *cpPath);
DiVoid DiStringExtractFileName(DiTChar const *cpFullFileName, DiTChar *cpName, DiInt32 nLength);
extern DiVoid DiStringExtractFileExt  (DiTChar *cpFullFileName, DiTChar *cpExt, DiInt32 nLength);

// remove extension from string
extern DiVoid DiStringRemoveExt(DiTChar *cpFileName);

// check, if specified string is a mask
extern DiBool DiStringIsItAMask(DiTChar *cpMask);

// builds mask file name for image
extern DiBool DiStringBuildImageMaskFileName(DiTChar *cpName);

// delete sStub in the begining of sSrc and store it in sDst
extern DiBool DiStringDelStubPath(DiTChar * sSrc, DiTChar * sStub, DiTChar * sDst);

// delete slashes from the end of string
extern DiBool DiStringDelSlashes(DiTChar * sSrc, DiTChar * sDst);

// file name regular compare ("*a*.exe" and so)
extern DiBool DiStringPathMatchSpec(DiTChar * sFileName, DiTChar * sMaska);

extern DiTChar *DiStringCopyStringPrefix(DiTChar *cpOut, DiTChar const *cpIn, DiInt32 nOutSize);

extern DiBool DiStringGetInt32(DiTChar *cpIn, DiInt32 *npOut);
extern DiBool DiStringGetFloat(DiTChar *cpIn, DiFloat *rpOut);
extern DiBool DiStringGetBool(DiTChar *cpIn, DiBool *bpOut);

#ifdef __cplusplus
}
#endif __cplusplus

#undef extern

#endif  __DISTRING_H__
