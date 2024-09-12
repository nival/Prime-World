/******************************************************************************
 * FILE NAME  DIMATH.inl
 * PURPOSE    engine advance mathematics system
 *
 * SPEC       27.12.2000 Max
 * NOTES      
 *******************************************************************************/
#include <math.h>
#include <float.h>

#include "DiTypes.h"

///eugbelNSCENE///namespace NScene {


//******************************************************************************

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

extern DiFloat  _raSinTable[diMATH_TRIG_NUM_ELEMENTS_IN_TABLE + 3];
extern DiFloat  _raCosTable[diMATH_TRIG_NUM_ELEMENTS_IN_TABLE + 3];
extern DiFloat  _raAsinTable[diMATH_TRIG_NUM_ELEMENTS_IN_TABLE + 3]; 
extern DiFloat  _raAcosTable[diMATH_TRIG_NUM_ELEMENTS_IN_TABLE + 3];
extern DiUInt32 _naSqrtTab1to2[diMATH_SQRT_NUM_ELEMENTS_IN_TABLE];
extern DiUInt32 *_npSqrtTab2to4;


#ifdef __cplusplus
}
#endif  /* __cplusplus */

//******************************************************************************
// functions
/**
 * This function calculates square root of the given number rNum and returns the result.
 *
 * @memo    Calculate square root
 * @return  square root of rNum
 * @param   rNum given number to caluculate the square root from.
 */
/**
 * This function is used to calculate square root got a given number
 *
 * @memo    Calculate square root
 * @return  sqaure root
 * @param   rNum  number
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiSqrtTabl(DiFloat rNum)
{
  DiFloat   *rpNum = &rNum;
  register  DiUInt32 nMantissa;
  register  DiUInt32 nExponent;
  DiFloat   rX;
  DiUInt32  *npX = (DiUInt32 *)&rX;

  DIFUNCTION("_diRSqrt");

  /* Assumes IEEE floating point layout:
    3         2         1          0
    10987654321098765432109876543210
    SEEEEEEEEMMMMMMMMMMMMMMMMMMMMMMM
    |   |               |
    |   |               23 bits of mantissa
    |   8 bits of exponent
    1 bit of sign
  */

  nExponent = *(DiUInt32 *)rpNum;

  if (nExponent)
  {
    // correction factor
    nExponent += (1L << (22 - diMATH_SQRTPRECISION));

    // extract mantissa
    nMantissa = (nExponent & 0x007fffffUL) >>
            (23 - diMATH_SQRTPRECISION);
    // extract exponent
    nExponent &= 0x7f800000UL;

    // Odd or even exponent ?
    nMantissa = (nExponent & 0x00800000UL) ?
            _naSqrtTab1to2[nMantissa] : _npSqrtTab2to4[nMantissa];

    *npX = (nExponent >> 1) + nMantissa;
  }
  else
  {
    rX = 0.0f ;
  }
  
  DIRETURN(rX);
} // end of DiSqrt

/**
 *  This function calculates sine.
 *
 * @memo    Calculate sine
 * @return  sin(rAngleInRadians)
 * @param   rAngleInRadians angle value in radians
 * @author  Vlad
 */
diINLINE DiFloat DiSinTabl(DiFloat rAngleInRadians)
{
  DiFloat   rRes;
  DiFloat   rIndex;
  DiFloat   rT;
  DiInt32   nIndex;

  DIFUNCTION("DiSin") ;

  if (rAngleInRadians > 0.0f)
  {
    rIndex = rAngleInRadians * ((diMATH_TRIG_NUM_ELEMENTS_IN_TABLE) / di2PI);
    nIndex = DiF2L(rIndex);
    rT     = rIndex - DiL2F(nIndex);
    nIndex &= (diMATH_TRIG_NUM_ELEMENTS_IN_TABLE - 1);
    rRes = _raSinTable[nIndex] * (1.0f-rT) + _raSinTable[nIndex + 1] * rT;
  }
  else
  {
    rAngleInRadians = -rAngleInRadians ;
    rIndex = rAngleInRadians * ((diMATH_TRIG_NUM_ELEMENTS_IN_TABLE) / di2PI);
    nIndex = DiF2L(rIndex);
    rT     = rIndex - DiL2F(nIndex);
    nIndex &= (diMATH_TRIG_NUM_ELEMENTS_IN_TABLE-1) ;
    rRes = _raSinTable[nIndex] * (1.0f - rT) + _raSinTable[nIndex + 1] * rT;
    rRes = -rRes;
  }

  DIRETURN(rRes);
}

/**
 *  This function calculates cosine.
 *
 * @memo    Calculate cos
 * @return  cos(rAngleInRadians)
 * @param   rAngleInRadians angle value in radians
 * @author  Vlad
 */
diINLINE DiFloat DiCosTabl(DiFloat rAngleInRadians)
{
  DiFloat   rRes;
  DiFloat   rIndex;
  DiFloat   rT;
  DiInt32   nIndex;

  DIFUNCTION("DiCos") ;

  rAngleInRadians = DiFMax(rAngleInRadians, -rAngleInRadians);

  rIndex = rAngleInRadians*((diMATH_TRIG_NUM_ELEMENTS_IN_TABLE)/di2PI);
  nIndex  = DiF2L(rIndex);
  rT      = rIndex - DiL2F(nIndex);
  nIndex &= (diMATH_TRIG_NUM_ELEMENTS_IN_TABLE-1);
  nIndex ++;
  rRes = _raCosTable[nIndex] * (1.0f - rT) + _raCosTable[nIndex + 1] * rT;

  DIRETURN(rRes);
}

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   rValue
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiBool DiSinCosTabl(DiFloat rAngleInRadians, DiFloat * rpSin, DiFloat * rpCos)
{
  DiFloat   rAngle;
  DiFloat   rIndex;
  DiFloat   rT, rInvT;
  DiInt32   nIndex;

  DIFUNCTION("DiSinCosTabl");
  DIASSERT(rpSin);
  DIASSERT(rpCos);

  rAngle = DiFMax(rAngleInRadians, -rAngleInRadians);

  rIndex = rAngle * ((diMATH_TRIG_NUM_ELEMENTS_IN_TABLE)/di2PI);
  nIndex  = DiF2L(rIndex);
  rT      = rIndex - DiL2F(nIndex);
  nIndex &= (diMATH_TRIG_NUM_ELEMENTS_IN_TABLE-1);
  nIndex ++;
  rInvT = (1.0f - rT);

  *(rpCos) = _raCosTable[nIndex] * rInvT + _raCosTable[nIndex + 1] * rT;
  if (rAngleInRadians > 0.0f)
  {
    *(rpSin) = _raSinTable[nIndex] * rInvT + _raSinTable[nIndex + 1] * rT;
  }else
  {
    *(rpSin) = -(_raSinTable[nIndex] * rInvT + _raSinTable[nIndex + 1] * rT);
  }

  DIRETURN(TRUE);
} // end of DiSinCosTabl

/**
 *  This function calculates arc sine.
 *
 * @memo    Calculate arc sine
 * @return  arcsin(rArg)
 * @param   rArg argument
 * @author  Vlad
 */
diINLINE DiFloat DiASinTabl(DiFloat rArg)
{
  DiFloat   rRes;
  DiFloat   rIndex;
  DiFloat   rT;
  DiInt32   nIndex;

  DIFUNCTION("DiAsin") ;

  rIndex  = (rArg + 1.0f) * (0.5f * diMATH_TRIG_NUM_ELEMENTS_IN_TABLE);
  nIndex  = DiF2L(rIndex);
  rT      = rIndex - DiL2F(nIndex);
  DIASSERT(nIndex >= 0 && nIndex <= diMATH_TRIG_NUM_ELEMENTS_IN_TABLE);
  rRes = _raAsinTable[nIndex] * (1.0f - rT) + _raAsinTable[nIndex+1] * rT;
  
  DIRETURN(rRes);
}

/**
 *  This function calculates arc cosine.
 *
 * @memo    Calculate arc cosine
 * @return  arccos(rArg)
 * @param   rArg argument
 * @author  Vlad
 */
diINLINE DiFloat DiACosTabl(DiFloat rArg)
{
  DiFloat   rRes;
  DiFloat   rIndex;
  DiFloat   rT;
  DiInt32   nIndex;

  DIFUNCTION("DiAcos") ;


  rIndex  = (rArg + 1.0f) * (0.5f * diMATH_TRIG_NUM_ELEMENTS_IN_TABLE);
  nIndex  = DiF2L(rIndex);
  rT      = rIndex - DiL2F(nIndex);
  DIASSERT(nIndex >= 0 && nIndex <= diMATH_TRIG_NUM_ELEMENTS_IN_TABLE);
  rRes = _raAcosTable[nIndex] * (1.0f - rT) + _raAcosTable[nIndex + 1] * rT;
  
  DIRETURN(rRes);
}

/**
 * MultiplyMixed - Muliply integer by floating point and give
 *                 the result in integer and fractional part separately
 *
 * @returns None
 * @param   nMul1      - [in]
 * @param   rMul2      - [in]
 * @param   npResInt   - [out] (DiInt32)(nMul1 * rMul2)
 * @param   rpResFrac  - [out] fraction of nMul1 * rMul2
 * @author  Miron
 */
diINLINE DiVoid DiMathMultiplyMixed(DiInt32 nMul1    , DiFloat rMul2, 
                                    DiInt32 *npResInt, DiFloat *rpResFrac)
{
  DiFloat rBig;

  DIFUNCTION("DiMathMultiplyMixed");

  DIASSERT(npResInt!=NULL && rpResFrac!=NULL);

  // multiply
  rBig = DiL2F(nMul1) * rMul2;

  // get parts
  *npResInt  = DiF2L(rBig);
  *rpResFrac = rBig - DiL2F(*npResInt);

  DIRETURNVOID();
}

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  TRUE on success, FALSE otherwise
 * @param   rValue1
 * @param   rValue2
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiBool DiFDivMod(DiFloat rValue1, DiFloat rValue2, DiFloat * rpDiv, DiFloat * rpMod)
{
  DIFUNCTION("DiFDivMod");

  DIASSERT(rpDiv);
  DIASSERT(rpMod);

  (*rpDiv) = DiL2F(DiF2L(rValue1 / rValue2));
  (*rpMod) = rValue1 - rValue2 * (*rpDiv);

  DIRETURN(TRUE);
} // end of DiFDivMod

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  TRUE on success, FALSE otherwise
 * @param   rValue
 * @param   rpSin
 * @param   rpCos
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiFloat DiFMod(DiFloat rValue1, DiFloat rValue2)
{
  DIFUNCTION("DiFMod");


  DIRETURN(rValue1 - rValue2 * DiL2F(DiF2L(rValue1 / rValue2)));
} // end of DiFMod

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  TRUE on success, FALSE otherwise
 * @param   rValue1
 * @param   rValue2
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiFloat DiFDiv(DiFloat rValue1, DiFloat rValue2)
{
  DIFUNCTION("DiFDiv");


  DIRETURN(DiL2F(DiF2L(rValue1 / rValue2)));
} // end of DiFDiv

/**
 * This function converts degrees to radians
 *
 * @memo    convert degrees to radians
 * @return  corresponding value in radians
 * @param   rDegrees [in] value in degrees
 * @header  DiMath.h
 * @library common.lib
 * @author  dim0n
 * @see     DiRad2Deg
 */
diINLINE DiFloat DiDeg2Rad(DiFloat rDegrees)
{
  return rDegrees * diPI / 180.0f;
}

/**
 * This function converts radians to degrees
 *
 * @memo    convert radians to degrees
 * @return  corresponding value in degrees
 * @param   rRadians [in] value in radians
 * @header  DiMath.h
 * @library common.lib
 * @author  dim0n
 * @see     DiRad2Deg
 */
diINLINE DiFloat DiRad2Deg(DiFloat rRadians)
{
  return rRadians * 180.0f / diPI;
}

///eugbelNSCENE///} // end of namespace NScene


// end of dimath.inl
