//  **********************************************************
//  FILE NAME   DiMath.h
//  PURPOSE     standart math functions stubs
//  START       28 jan 2000
//  AUTHOR      Vlad
//  PREFIX      DiMath
//  NOTES
//  **********************************************************

#ifndef _DIMATH_H_
#define _DIMATH_H_

//  **********************************************************
//  Includes
//  **********************************************************

#include "DiTypes.h"

///eugbelNSCENE///namespace NScene {

// *****************************************************************************
// data types

// *****************************************************************************
// functions defines

// Number of values in table
#define diMATH_TRIG_NUM_ELEMENTS_IN_TABLE        512
#define diMATH_SQRTPRECISION                     11L
#define diMATH_SQRT_NUM_ELEMENTS_IN_TABLE        (1L << (diMATH_SQRTPRECISION + 1))


/*
 * This define represents square root from 2
 * @memo     Square root from 2
 * @header   DiMath.h
 */
#define di2ROOT  (1.4142135623730950488016887242097f)
#define di2ROOT2 (di2ROOT * 0.5f)

/*
 * This define represents square root from 3
 * @memo     Square root from 3
 * @header   DiMath.h
 */
#define di3ROOT  (1.2599210498948731647672106072779f)
#define di3ROOT2 (di3ROOT * 0.5f)

/*
 * This define represents float Pi number
 * @memo     Float Pi number
 * @header   DiVector.h
 */
#define diPI  (3.14159265358979323846f)

/*
 * This define represents float 2*Pi number
 * @memo     Float 2*Pi number
 * @header   DiVector.h
 */
#define di2PI (diPI * 2.0f)

/*
 * This define represents float Pi/2 number
 * @memo     Float Pi/2 number
 * @header   DiVector.h
 */
#define diPI2 (diPI * 0.5f)

/**
 * This macro makes combo-shift.
 * @memo     Make combo-shift.
 * @return   ((rA)*(rB)+(rC))
 * @param    rA first value
 * @param    rB first second
 * @param    rC third value
 * @header   DiVector.h
 */
#define diSHIFT_COMB(rA, rB, rC)      ((rA)*(rB)+(rC))

/**
 * This macro makes angle comparision: check a is in [b,c]
 * @memo     Make angle comparision: check a is in [b,c]
 * @return   TRUE if b smaller or equal to c and a is in [b,c]
 * @param    a interested value
 * @param    b lower boundary
 * @param    c upper boundary
 * @header   DiAlgbra.h
 */
#define DIAL_ANGLE_IS_IN(a,b,c) \
     ((b)<=(c) ? \
       ((b)<=(a) && (a)<=(c)) : \
       ((a)<=(c) || (b)<=(a)) \
    )

/**
 * This macro makes revolving increase in [0,modul] with joint in zero
 * @memo     Make revolving increase in [0,modul] with joint in zero
 * @param    a value need to increase
 * @param    modul upper boundary
 * @header   DiAlgbra.h
 */
#define DI_REVOLVING_INC(a,modul)     \
  {                                   \
    DIASSERT(0<=(a) && (a)<(modul)); \
    (a)++;                            \
    if ((a)>=(modul)) (a)=0;          \
  }

/**
 * This macro makes revolving decrease in [0,modul] with joint in zero
 * @memo     Make revolving decrease in [0,modul] with joint in zero
 * @param    a value need to decrease
 * @param    modul upper boundary
 * @header   DiAlgbra.h
 */
#define DI_REVOLVING_DEC(a,modul)     \
  {                                   \
    DIASSERT(0<=(a) && (a)<(modul)); \
    (a)--;                            \
    if ((a)<0) (a)=(modul)-1;         \
  }

/**
 * This macro makes revolving addition in [0,modul] with joint in zero
 * @memo     Make revolving addition in [0,modul] with joint in zero
 * @param    a first summand
 * @param    b second summand
 * @param    modul upper boundary
 * @param    c result, equal to (a+b) tiled to [0,modul]
 * @header   DiAlgbra.h
 */
#define DI_REVOLVING_ADD(a,b,modul,c) \
  {                                   \
    DIASSERT(0<=(a) && (a)<(modul)); \
    DIASSERT(0<=(b) && (b)<(modul)); \
    (c)=(a)+(b);                      \
    if ((c)>=(modul)) (c)-=(modul);   \
  }

/**
 * This macro makes revolving subtraction in [0,modul] with joint in zero
 * @memo     Make revolving subtraction in [0,modul] with joint in zero
 * @param    a first number
 * @param    b subtrahend
 * @param    modul upper boundary
 * @param    c result, equal to (a-b) tiled to [0,modul]
 * @header   DiAlgbra.h
 */
#define DI_REVOLVING_SUB(a,b,modul,c) \
  {                                   \
    DIASSERT(0<=(a) && (a)<(modul)); \
    DIASSERT(0<=(b) && (b)<(modul)); \
    (c)=(a)-(b);                      \
    if ((c)<0) (c)+=(modul);          \
  }

/**
 * This macro makes revolving increase in [0,modul] with any specific joint
 * @memo     Make revolving increase in [0,modul] with any specific joint
 * @param    a value need to increase
 * @param    modul upper boundary
 * @param    jnt joint, if a greather than modul, a = jnt
 * @header   DiAlgbra.h
 */
#define DI_REV_JNT_INC(a,modul,jnt)   \
  {                                   \
    DIASSERT(0<=(a) && (a)<(modul)); \
    (a)++;                            \
    if ((a)>=(modul)) (a)=(jnt);      \
  }

/**
 * This macro makes revolving derease in [0,modul] with any specific joint
 * @memo     Make revolving derease in [0,modul] with any specific joint
 * @param    a value need to decrease
 * @param    modul upper boundary
 * @param    jnt joint, <B>if a little than jnt, a += modul - jnt</B>
 * @header   DiAlgbra.h
 */
#define DI_REV_JNT_DEC(a,modul,jnt)   \
  {                                   \
    DIASSERT(0<=(a) && (a)<(modul)); \
    (a)--;                            \
    if ((a)<(jnt)) (a)+=(modul)-(jnt);\
  }

/**
 * This macro makes revolving addition in [0,modul] with any specific joint
 * @memo     Make revolving addition in [0,modul] with any specific joint
 * @param    a first summand
 * @param    b second summand
 * @param    modul upper boundary
 * @param    jnt joint, <B>if a little than jnt, c -= modul - jnt</B>
 * @param    c result, equal to (a+b) tiled to [0,modul] with specific joint
 * @header   DiAlgbra.h
 */
#define DI_REV_JNT_ADD(a,b,modul,jnt,c)     \
  {                                         \
    DIASSERT(0<=(a) && (a)<(modul));       \
    DIASSERT(0<=(b) && (b)<(modul));       \
    (c)=(a)+(b);                            \
    if ((c)>=(modul)) (c)-=(modul)-(jnt);   \
  }

/**
 * This macro makes revolving subtraction in [0,modul] with any specific joint
 * @memo     Make revolving subtraction in [0,modul] with any specific joint
 * @param    a first number
 * @param    b subtrahend
 * @param    modul upper boundary
 * @param    jnt joint, <B>if a little than jnt, c += modul - jnt</B>
 * @param    c result, equal to (a-b) tiled to [0,modul] with specific joint
 * @header   DiAlgbra.h
 */
#define DI_REV_JNT_SUB(a,b,modul,jnt,c)     \
  {                                         \
    DIASSERT(0<=(a) && (a)<(modul));       \
    DIASSERT(0<=(b) && (b)<(modul));       \
    (c)=(a)-(b);                            \
    if ((c)<(jnt)) (c)+=(modul)-(jnt);      \
  }

/**
 * This macro checks if the number power of 2
 * @memo     Check if the number power of 2
 * @return   TRUE if nA power of 2, FALSE otherwize
 * @param    nA interested value
 * @header   DiAlgbra.h
 */
#define DiAlIsPow2(nA)    (!((nA) & ((nA) - 1)))

/**
 * This macro converts angle from deg to radians
 * @memo     Convert angle from deg to radians
 * @param    x float value to convert
 * @return   converted value
 * @header   DiVector.h
 */
#define DI_DEG2RAD(x)   (diPI * (x) / 180.f)

// *****************************************************************************
// functions prototypes

// normal mathimatics
diINLINE DiInt32 DiIAbs(DiInt32 nValue);
diINLINE DiFloat DiFAbs(DiFloat rValue);
diINLINE DiFloat DiSqrt(DiFloat rValue);
diINLINE DiFloat DiSqr(DiFloat rValue);
diINLINE DiFloat DiSqrtR(DiFloat rValue);
diINLINE DiFloat DiSin(DiFloat rValue);
diINLINE DiFloat DiCos(DiFloat rValue);
diINLINE DiFloat DiTan(DiFloat rValue);
diINLINE DiFloat DiASin(DiFloat rValue);
diINLINE DiFloat DiACos(DiFloat rValue);
diINLINE DiFloat DiATan(DiFloat rValue);
diINLINE DiBool  DiSinCos(DiFloat rValue, DiFloat * rpSin, DiFloat * rpCos);
diINLINE DiBool  DiFDivMod(DiFloat rValue1, DiFloat rValue2, DiFloat * rpDiv, DiFloat * rpMod);
diINLINE DiFloat DiFDiv(DiFloat rValue1, DiFloat rValue2);
diINLINE DiFloat DiFMod(DiFloat rValue1, DiFloat rValue2);
#define DiExp(rValue)           DiD2F(exp(DiF2D((rValue))))
#define DiLog(rValue)           DiD2F(log(DiF2D((rValue))))
#define DiPow(rValue1, rValue2) DiD2F(pow(DiF2D((rValue1)), DiF2D((rValue2))))

// max/min
diINLINE DiFloat DiFMax(DiFloat rValue1, DiFloat rValue2);
diINLINE DiFloat DiFMin(DiFloat rValue1, DiFloat rValue2);
diINLINE DiFloat DiFFitIn(DiFloat rValue, DiFloat rDown, DiFloat rUp);
diINLINE DiBool  DiFMinMax(DiFloat rValue1, DiFloat rValue2, DiFloat * rpMin, DiFloat * rpMax);
diINLINE DiInt32 DiIMax(DiInt32 nValue1, DiInt32 nValue2);
diINLINE DiInt32 DiIMin(DiInt32 nValue1, DiInt32 nValue2);
diINLINE DiInt32 DiIFitIn(DiInt32 nValue, DiInt32 nDown, DiInt32 nUp);

// testing
diINLINE DiBool  DiIsFinite(DiFloat rValue);

// usual conversion
diINLINE DiInt32 DiF2L(DiFloat rValue);        // truncate float to int conversion
diINLINE DiFloat DiL2F(DiInt32 nValue);        // int to float
diINLINE DiFloat DiUL2F(DiUInt32 nValue);       // unsigned to float
diINLINE DiDouble DiF2D(DiFloat rValue);       // float to double
diINLINE DiFloat DiD2F(DiDouble rValue);       // double to float

// extention conversion
diINLINE DiInt32 DiF2LQuick(DiFloat rValue);   // must be only between DiFpuRoundBegin and DiFpuRoundEnd
diINLINE DiInt32 DiF2LClosest(DiFloat rValue); // closest conversion
diINLINE DiInt32 DiF2LNegInf(DiFloat rValue);  // negInf
diINLINE DiInt32 DiF2LPosInf(DiFloat rValue);  // posInf
#define DiF2LTruncate(rValue) DiF2L(rValue)    // truncate as DiF2L

diINLINE DiFloat DiDeg2Rad(DiFloat rDegrees);
diINLINE DiFloat DiRad2Deg(DiFloat rRadians);

// multiplication with conversion
diINLINE DiVoid DiMathMultiplyMixed(DiInt32 nMul1, DiFloat rMul2, DiInt32 *npResInt, DiFloat *rpResFrac);

// tablic mathematics
diINLINE DiFloat DiSqrtTabl(DiFloat rValue);
diINLINE DiFloat DiSinTabl(DiFloat rValue);
diINLINE DiFloat DiCosTabl(DiFloat rValue);
diINLINE DiBool DiSinCosTabl(DiFloat rValue, DiFloat * rpSin, DiFloat * rpCos);
diINLINE DiFloat DiASinTabl(DiFloat rValue);
diINLINE DiFloat DiACosTabl(DiFloat rValue);



/*
 * @memo    This function calculates the next power of two number. 
 *          Input number should be 16 bit.
 *          Example: 25 -> 32, 64 -> 64.
 * @return  the next power of two number
 * @param   nNumber    [in] number
 * @see     DiMathNextPowOf2Log
 */
diINLINE DiInt32 DiMathNextPowOf2(DiInt32 nNumber)
{
  DIASSERT(nNumber <= 0xFFFF);   // fails => add one more line
                                 // 0 1000 0000 0000 0001
  nNumber--;                     // 0 1000 0000 0000 0000
  nNumber |= nNumber >> 1;       // 0 1100 0000 0000 0000
  nNumber |= nNumber >> 2;       // 0 1111 0000 0000 0000
  nNumber |= nNumber >> 4;       // 0 1111 1111 0000 0000
  nNumber |= nNumber >> 8;       // 0 1111 1111 1111 1111

  return nNumber + 1;
}

/*
 * @memo    This function returns the log of the next power of two number
 *          Input number should be 16 bit.
 *          Example: 25 -> 5, 64 -> 6.
 * @return  the log of the next power of two number
 * @param   nNumber    [in] number
 * @see     DiMathNextPowOf2
 */
diINLINE DiInt32 DiMathNextPowOf2Log(DiInt32 nNumber)
{
  DiFloat rFloat;
  DiInt32 nExponent;

  DIASSERT(nNumber <= 0xFFFF);
                                 // 0 1000 0000 0000 0001
  nNumber--;                     // 0 1000 0000 0000 0000
  nNumber |= nNumber >> 1;       // 0 1100 0000 0000 0000
  nNumber |= nNumber >> 2;       // 0 1111 0000 0000 0000
  nNumber |= nNumber >> 4;       // 0 1111 1111 0000 0000
  nNumber |= nNumber >> 8;       // 0 1111 1111 1111 1111
  rFloat = (float)(nNumber + 1); // 1 0000 0000 0000 0000
  nExponent = (((*(int *)&rFloat) & 0x7F800000) >> 23) - 127;
  DIASSERT((1 << nExponent) == (nNumber + 1));

  return nExponent;
}

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

// system open/close
extern DiBool DiMathSystemOpen();
extern DiBool DiMathSystemClose();

// special function
extern DiInt32 DiMathGetLowestBitPosition(DiInt32 nVal);
extern DiInt32 DiMathGetHighestBitPosition(DiInt32 nVal);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


///eugbelNSCENE///} // end of namespace NScene
#include "DiMath.inl"
#include "DiMathOp.inl"
///eugbelNSCENE///namespace NScene {



// *****************************************************************************
// compatibility
#define diFABS(rValue)                     DiFAbs(rValue)
#define diSQRT(rValue)                     DiSqrt(rValue)
#define RSQRT(rValue)                      DiSqrt(rValue)
#define SQRT(rValue)                       DiSqrt(rValue)
#define diSQUARED(rValue)                  DiSqr(rValue)
#define diSQRTR(rValue)                    DiSqrtR(rValue)
#define diSIN(rValue, rpRes)               (*(rpRes) = DiSin(rValue))
#define SIN(rValue)                        DiSin(rValue)
#define RSIN(rValue)                       DiSin(rValue)
#define diCOS(rValue, rpRes)               (*(rpRes) = DiCos(rValue))
#define COS(rValue)                        DiCos(rValue)
#define RCOS(rValue)                       DiCos(rValue)
#define diISFINITE(rValue)                 DiIsFinite(rValue)
#define ASIN(rValue)                       DiAsin(rValue)
#define RASIN(rValue)                      DiAsin(rValue)
#define ACOS(rValue)                       DiAcos(rValue)
#define RACOS(rValue)                      DiAcos(rValue)
#define DiAsin(rValue)                     DiASin(rValue)
#define DiAcos(rValue)                     DiACos(rValue)
#define FMIN(rX, rY, rZ)                   ((rZ) = DiFMin((rX), (rY)))
#define FMAX(rX, rY, rZ)                   ((rZ) = DiFMax((rX), (rY)))
#define FMINMAX(rX, rY, rMin, rMax)        DiFMinMax((rX), (rY), &(rMin), &(rMax))
#define FFITIN(rX, rLower, rUpper, rOut)   ((rOut) = DiFFitIn((rX), (rLower), (rUpper)))
#define IMIN(nX, nY, nZ)                   ((nZ) = DiIMin((nX), (nY)))
#define IMAX(nX, nY, nZ)                   ((nZ) = DiIMax((nX), (nY)))
#define IFITIN(nX, nLower, nUpper, nOut)   ((nOut) = DiIFitIn((nX), (nLower), (nUpper)))
#define FL2L(rValue)                       DiF2L(rValue)
#define DiFpuFloat2Long(rValue)            DiF2L(rValue)
#define DiFpuFloat2LongClosest(rValue)     DiF2LClosest(rValue)
#define DiFpuFloat2LongNegInf(rValue)      DiF2LNegInf(rValue)
#define DiFpuFloat2LongPosInf(rValue)      DiF2LPosInf(rValue)
#define DiFpuFloat2LongTruncate(rValue)    DiF2LTruncate(rValue)

///eugbelNSCENE///} // end of namespace NScene


#endif // _DIMATH_H_
