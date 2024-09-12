/******************************************************************************
 * FILE NAME  DITYPES.H
 * PURPOSE    Engine types definitions
 *
 * SPEC       10.11.1997 S.K.
 * UPDATED    15.02.2001 Gandy
 * NOTES
 *******************************************************************************/

#ifndef __DITYPES_H__
#define __DITYPES_H__

#include "../System/DefaultTypes.h"

#include <stddef.h>

#ifdef WIN32
  #include "../System/Asserts.h"
  #include "../System/Logger.h"
#endif


///eugbelNSCENE///namespace NScene {

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef _MAX_PATH
 #define  _MAX_PATH                260
#endif  //_MAX_PATH

#ifdef MAX_FLOAT
  #undef MAX_FLOAT
#endif
#define  MAX_FLOAT                (float)(3.4e+38)
#define  MIN_FLOAT                (float)(-3.4e+38)

#ifdef _diAElem
#error MF
#endif
#define _diAElem(aArray, nIndex, nStride, type)  ((type*)((DiByte*)(aArray) + (nIndex) * (nStride)))

//  these defines are used now not only in matrix operations -
//  so they are moved from dimatrix.h here
typedef enum tagDiOpCombainType
{
  diREPLACE,
  diPRECONCAT,
  diPOSTCONCAT,
  di_OP_FORCEDWORD = 0x7FFFFFFF
} DiOpCombainType;

/**
 * This macro aligns nDword at 4 bytes
 * @memo     Align nDword at 4 bytes
 * @param    nDword number to aline
 * @return   aligned value
 * @header   DiTypes.h
 */
#define diALIGN4BYTES(nDword) (((nDword) + 3) & (~3L))
#define diALIGN16BYTES(nDword) (((nDword) + 15) & (~15L))

#define DI_SB_ASSIGN(sbValue, r)          ((sbValue).rFloat = (r))
#define DI_SB_IS_POSITIVE(sbValue)        ((sbValue).nInt > 0)
#define DI_SB_IS_GE_ZERO(sbValue)         ((sbValue).nUInt <= 0x80000000)
#define DI_SB_IS_NEGATIVE(sbValue)        ((sbValue).nUInt > 0x80000000)
#define DI_SB_IS_LE_ZERO(sbValue)         ((sbValue).nUInt-1 >= 0x7fffffff)
#define DI_SB_IS_ZERO(sbValue)            (!((sbValue).nUInt & 0x7fffffff))
#define DI_SB_OF_DIFFERENT_SIGN(sbA, sbB) (((sbA).nInt ^ (sbB).nInt) & 0x80000000)
#define DI_SB_OF_SAME_SIGN(sbA, sbB)      (!(((sbA).nInt ^ (sbB).nInt) & 0x80000000))
#define DI_SB_GET_SIGN(sbA)               ((sbA).nInt & 0x80000000)
#define DI_SB_ABS_OF_FLOAT(rpF, sbA)      ((sbA).nUInt = ((*(DiUInt32 *)(rpF)) & 0x7fffffff))
#define DI_SB_ABS_OF_SB(sbSrc, sbDst)     ((sbDst).nUInt = ((sbSrc).nUInt & 0x7fffffff))
#define DI_SB_SET_SIGN(sbA, nSign)        ((sbA).nInt &= 0x7fffffff, (sbA).nInt |= nSign)


/**
 * This enum represents standart callback return values.
 * <br><B>NOTE:</B> Each callback that will be passed
 *  to any DiXXXForAll function MUST be defined as
 *  DiCallbackReturnValue DiCallbackFunction(DiXXX *, DiVoid *vpParamA, DiVoid *vpParamB);
 *  where DiXXX is a type of callback data (e.g. DiLight, DiClump, etc.)
 *
 * @memo     standart callback return value
 * @member   diFORALL_NA         -
 * @member   diFORALL_STOP       -
 * @member   diFORALL_CONTINUE   -
 * @member   diFORALL_ERROR      -
 * @member   diFORALL_ENUM       -
 * @header   DiTypes.h
 */
typedef enum tagDiCalbackReturnValue
{
  diFORALL_NA       = 0,
  diFORALL_STOP     = 1,
  diFORALL_CONTINUE = 2,
  diFORALL_ERROR    = 3,
  diFORALL_ENUM,
  diFORALL_FORCEDWORD = 0x7FFFFFFF
} DiCallbackReturnValue;

#ifndef NULL
 #ifdef __cplusplus
  #define NULL    0
 #else  __cplusplus
  #define NULL    ((void *)0)
 #endif __cplusplus
#endif

#ifdef FALSE
  #undef FALSE
#endif
#define FALSE 0

#ifdef TRUE
  #undef TRUE
#endif
#define TRUE   (!FALSE)

/**
 * This macro obtains size (<B>number of elements</B>) of specified array.
 * @memo     Obtain size of specified array
 * @param    a    interested array
 * @return   size of array (number of elements)
 * @header   DiTypes.h
 */

#ifndef DIM
  #define DIM(a) (sizeof((a)) / sizeof(*(a)))
#endif  //DIM

/**
 * This macro uses parameter x.
 *    It defined like <br><B>#define diUSE_PARAM(x) ((x)=(x))</B>
 *
 * @memo     Use parameter x
 * @param    x    parameter to use
 * @return   parametr value
 * @header   DiTypes.h
 */
#define diUSE_PARAM(x)      ((void)(x))

// make 4 bytes signature for memory integrity checks
// for example
// #define diSOME_SYSTEM_SIGN diMAKE_SIGN('s','o','m','e')
/*
 * This macro is used to make 4 bytes signature for memory integrity checks
 * for example #define diSOME_SYSTEM_SIGN diMAKE_SIGN('s','o','m','e')*
 * @memo
 * @param    a    parameter
 * @param    b    parameter
 * @param    c    parameter
 * @param    d    parameter
 * @return
 * @header   DiTypes.h
 */
#define diMAKE_SIGN(a,b,c,d)  (                      \
                                ((DiUInt32)(a))|      \
                                ((DiUInt32)(b)<<8)|   \
                                ((DiUInt32)(c)<<16)|  \
                                ((DiUInt32)(d)<<24)   \
                             )

/**
 * This type represents abstract type structure
 *
 * @memo     Abstract type structure
 * @member   cType          type
 * @member   cSubType       subtype
 * @member   cFlags         flags
 * @member   cPrivateFlags  private flags
 * @header   DiTypes.h
 */
typedef struct tagDiType
{
  unsigned char cType;
  unsigned char cSubType;
  unsigned char cFlags;
  unsigned char cPrivateFlags;
} DiType;

/**
 * This macro gets type for t
 *
 * @memo     Get type for t
 * @param    t  pointer to the DiType structure
 * @return   requested member
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeGetType(t) (((DiType *)(t))->cType)

/**
 * This macro sets type for t
 *
 * @memo     Set type for t
 * @param    t [out] pointer to the DiType structure
 * @param    v [in]  type to set (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeSetType(t, v) (((DiType *)(t))->cType) = (unsigned char)(v)

/**
 * This macro gets sub type for t
 *
 * @memo     Get sub type for t
 * @param    t pointer to the DiType structure
 * @return   requested member
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeGetSubType(t) (((DiType *)(t))->cSubType)
/**
 * This macro sets sub type for t
 *
 * @memo     Set sub type for t
 * @param    t [out] pointer to the DiType structure
 * @param    v [in]  type to set (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeSetSubType(t, v) (((DiType *)(t))->cSubType) = (unsigned char)(v)

/**
 * This macro gets flags for t
 *
 * @memo     Get flags for t
 * @param    t pointer to the DiType structure
 * @return   requested member
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeGetFlags(t) (((DiType *)(t))->cFlags)
/**
 * This macro sets flags for t
 *
 * @memo     Set flags for t
 * @param    t [out] pointer to the DiType structure
 * @param    v [in]  flags to set (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeSetFlags(t, v) (((DiType *)(t))->cFlags) = (unsigned char)(v);

/**
 * This macro adds flags for t
 *
 * @memo     Add flags for t
 * @param    t [out] pointer to the DiType structure
 * @param    v [in]  flags to add (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeAddFlags(t, v) (((DiType *)(t))->cFlags) |= (v)
/**
 * This macro removes flags for t
 *
 * @memo     Remove flags for t
 * @param    t [out] pointer to the DiType structure
 * @param    v [in]  flags to remove (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeRemoveFlags(t, v) (((DiType *)(t))->cFlags) &= (~(v))

/**
 * This macro gets private flags for t
 *
 * @memo     Get private flags for t
 * @param    t pointer to the DiType structure
 * @return   requested member
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeGetPrivateFlags(t) (((DiType *)(t))->cPrivateFlags)
/**
 * This macro sets private flags for t
 *
 * @memo     Set private flags for t
 * @param    t [out] pointer to the DiType structure
 * @param    v [in]  flags to set (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeSetPrivateFlags(t, v) (((DiType *)(t))->cPrivateFlags) = (unsigned char)(v)

/**
 * This macro adds private flags for t
 *
 * @memo     Add private flags for t
 * @param    t [out] pointer to the DiType structure
 * @param    v [in]  flags to add (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeAddPrivateFlags(t, v) (((DiType *)(t))->cPrivateFlags) |= (v)
/**
 * This macro removes private flags for t
 *
 * @memo     Remove private flags for t
 * @param    t [out] pointer to the DiType structure
 * @param    v [in]  flags to remove (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeRemovePrivateFlags(t, v) (((DiType *)(t))->cPrivateFlags) &= (~(v))

/**
 * This macro initializes type t by given parameters.
 * Flags and private flags init to 0.
 *
 * @memo     Initialize type t by given parameters
 * @param    t [out] pointer to the DiType structure
 * @param    type [in]  flags to remove (unigned char)
 * @param    subtype [in]  flags to remove (unigned char)
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeInitialize(t, type, subtype)                 \
   {                                                       \
    ((DiType *)(t))->cType = (unsigned char)(type);        \
    ((DiType *)(t))->cSubType = (unsigned char)(subtype);  \
    ((DiType *)(t))->cFlags = 0;                           \
    ((DiType *)(t))->cPrivateFlags = 0;                    \
   }

/**
 * This macro copyes type
 *
 * @memo     Copy type
 * @param    d [out] pointer to the DiType structure
 * @param    s [in]  pointer to the DiType structure
 * @header   DiTypes.h
 * @see      DiType structure
 */
#define DiTypeCopy(d, s) (*((DiType *)(d))) = (*((DiType *)(s)))

#define DiDwordReadUnaligned(ptr) (*(DiUInt32*)(ptr))

#define diTOS_EXT(expr) #expr
#define diTOS(expr) diTOS_EXT(expr)

#ifdef __cplusplus
}
#endif  /* __cplusplus */

///eugbelNSCENE///} // end of namespace NScene


#endif  //__DITYPES_H__
