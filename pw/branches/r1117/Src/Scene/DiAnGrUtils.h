/*
 * @file    DiAnGrUtils.h
 * @memo    Macroses, special functions, stubs to like AnimGraph into Nival engine
 * @author  EugBel
 * @date    05.11.2008
 * @prefix  DiAn, DiAnGr

 */

#ifndef _DIANGRUTILS_H_
#define _DIANGRUTILS_H_

#include "../System/Asserts.h"
#include "../System/SystemLog.h"

///eugbelNSCENE///namespace NScene {

//////////////////////////////////////////////////////////////////////////
/// Some basic types
//////////////////////////////////////////////////////////////////////////
typedef char                      DiTChar;

typedef unsigned  char            DiByte;

typedef char                      DiInt8;
typedef short  int                DiInt16;
typedef long   int                DiInt32;
#if defined(_MSC_VER)
typedef __int64                  DiInt64;
#else
typedef long  int                DiInt64;
#endif

typedef unsigned char             DiUInt8;
typedef unsigned short  int       DiUInt16;
typedef unsigned long   int       DiUInt32;
#if defined (_MSC_VER)
typedef unsigned __int64          DiUInt64;
#else
typedef unsigned long int         DiUInt64;
#endif

typedef long  int                 DiBool;
typedef void                      DiVoid;

typedef float                     DiFloat;
typedef double                    DiDouble;

typedef CVec2                     DiVec2;

typedef unsigned long int         DiColor;

//////////////////////////////////////////////////////////////////////////
/// Some macroses from DiEngine
//////////////////////////////////////////////////////////////////////////
#include "..\System\Asserts.h"
#define diINLINE inline static

#define DI_NEW(type) new type

#define DIFUNCTION(c)
#define DIRETURN(x)   return x
#define DIRETURNVOID()  return

#define DIOBJMSG_STOP     0
#define DIOBJMSG_CONTINUE 1

#define DIASSERT(cond)            NI_ASSERT(cond, "Assert failed!")
#define DIASSERTMSG(cond, text)   NI_ASSERT(cond, text)
#define DIASSERT_ALOOF_CODE(msg)     NI_ALWAYS_ASSERT(NStr::StrFmt("Aloof code! %s", msg))
#define DIASSERTPTR(ptr)          DIASSERT(ptr != NULL)

#define DIFATAL_ERROR(cond, text, returnVal) \
{                                            \
  DIASSERTMSG(cond, text)                    \
  if (!cond)                                 \
  {                                          \
    return returnVal;                        \
  }                                          \
}

#define DiMemAllocate(size)                   new DiByte[size]
#define DiMemAllocateAligned(size, align)     DiMemAllocate(size)
#define DiMemAllocateTmp(size)                new DiByte[size]
#define DiMemAllocateTmpAligned(size, align)  DiMemAllocateTmp(size)

#define DiMemFree(ptr)                        delete [] ((DiByte *)ptr)
#define DiMemFreeAligned(ptr)                 DiMemFree(ptr)
#define DiMemFreeTmp(ptr)                     delete [] ((DiByte *)ptr)
#define DiMemFreeTmpAligned(ptr)              DiMemFreeTmp(ptr)

#define DiMemSet(ptr, val, size)              memset(ptr, val, size)

//////////////////////////////////////////////////////////////////////////
/// Some math staff
//////////////////////////////////////////////////////////////////////////

/**
* This enum contain return values of DiAlSphereCrossPoly
* @memo     return values of DiAlSphereCrossPoly
* @member   AL_NO_CROSS     no crossing
* @member   AL_PLANE_TOUCH  plane touch
* @member   AL_VERTEX_TOUCH vertex touch
* @member   AL_EDGE_TOUCH   edge touch
* @see      DiAlSphereCrossPoly
* @header   DiAlgbra.h
*/
typedef enum tagDiSolveEquationResult {
  AL_NO_ROOTS     = 0 ,
  AL_ONE_ROOTS,
  AL_TWO_ROOTS,
  AL_INFTY_ROOTS_FORCEDWORD = 0x7FFFFFFF
} DiSolveEquationResult;

typedef DiFloat (*DiAlParamEquation)(DiFloat rx, DiVoid *vp);

typedef struct tagDiAlSolveEquationParams
{
  DiFloat rY;    //value
  DiFloat rFrom; //lowest root
  DiFloat rTo;   //max root
  DiFloat rStep;   //initial step
  DiFloat rGuessRoot;
  DiFloat rAccuracy;
} DiAlSolveEquationParams;

extern  DiSolveEquationResult DiAlSolveSquareEquation(DiFloat rA, DiFloat rB, DiFloat rC, DiFloat *rpS1, DiFloat *rpS2);
DiFloat DiAlSolveEquationIntectionally(DiAlSolveEquationParams *sppPars, DiAlParamEquation fp, DiVoid *vp, const nstl::string& dbfilename);

/**
* This type represents bit fields for float calculation optimization.
* Volatile keyword is required for MSVC5.0 and 
* will perform immediate access to memory
*
* @memo     Bit fields for float calculation optimization
* @member   rFloat to access as DiFloat
* @member   nInt   to access as DiInt32
* @member   nUInt  to access as DiUInt32
* @header   DiTypes.h
*/
typedef union TagDiSplitBits
{
  DiFloat           rFloat;
  volatile DiInt32  nInt;
  volatile DiUInt32 nUInt;
} DiSplitBits;

//////////////////////////////////////////////////////////////////////////
/// Some defines from DiAnGrWr.h
//////////////////////////////////////////////////////////////////////////

#define DIANGRWR_NUM_COMMAS              11    // number of comms in csv-file. Change this if version of .csv changes

#define DIANGRWR_TEMP_BUF_SIZE           128  // size of internal buffer (used for forming lines)
// NOTE: it is the same for DiAnGrCsvLine and DiAnGrWriter
// so we don't check overflow in (DiTChar *) params

#define DIANGRWR_DELIMITER               ","  // delimiter in csv-file
#define DIANGRWR_KNOT_ID                 "KNOT"  // shows start of Node/Macronode

#define DIANGRWR_BORDER_SPACE            " "
#define DIANGRWR_EMPTY_LINE_LENGTH       70

// float parameters
#define DIANGRWR_SPEED_1                 7    // <=> "%4.2lf"
#define DIANGRWR_SPEED_2                 2    //

#define DIANGRWR_VPAR_1                  6   
#define DIANGRWR_VPAR_2                  4

#define DIANGRWR_SEQ_PARAM_1             5
#define DIANGRWR_SEQ_PARAM_2             3

#define DIANGRWR_GEN_FLOAT_1             4
#define DIANGRWR_GEN_FLOAT_2             2

#define DIANGRWR_PRIORITY_1             5
#define DIANGRWR_PRIORITY_2             2

#define DIANGRWR_INVALID_WIDTH           654321

// max length of "TRANSACTION" , "FLTRANSACTION"
#define DIANGRWR_MAX_TRANSS_ID           16 //(strlen(DIANGR_FLTRANSACTION_NAME) + 2)
// max length of "UNIFORM" , "3RECPARABOLIC", etc.
#define DIANGRWR_MAX_KIND_ID             14 //(strlen("3RECPARABOLIC") + 1)
// max assumed length of nodes name
#define DIANGRWR_MAX_NODE_NAME           23   
// max assumed length of sequence name
#define DIANGRWR_MAX_SEQ_NAME            23   
// max assumed length of "FIRST", "SECOND", "BOTH"
#define DIANGRWR_MAX_UPD_NAME            6 //(strlen("SECOND") + 1)

///eugbelNSCENE///} // end of namespace NScene

#include "dimath.h"


#endif _DIANGRUTILS_H_
