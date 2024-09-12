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
// static variables

//******************************************************************************

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
diINLINE DiFloat DiFAbs(DiFloat rValue)
{
  DiSplitBits sbX;

  DIFUNCTION("DiFAbs");
  DI_SB_ASSIGN(sbX, rValue);
  sbX.nInt &= 0x7FFFFFFF;

  DIRETURN(sbX.rFloat);
} // end of DiFabs

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
diINLINE DiInt32 DiIAbs(DiInt32 nValue)
{
  DiInt32 nTmp;

  DIFUNCTION("DiIAbs");
  DIASSERT(nValue != 0x80000000);

  nTmp = nValue >> 31;
  nValue = (nTmp & (-nValue)) + ((~nTmp) & nValue);

  DIRETURN(nValue);
} // end of DiFabs

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
diINLINE DiFloat DiSqrt(DiFloat rValue)
{
  DIFUNCTION("DiSqrt");

  DIRETURN(DiD2F(sqrt(DiF2D(rValue))));
} // end of DiSqrt

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
diINLINE DiFloat DiSqr(DiFloat rValue)
{
  DIFUNCTION("DiSqr");
  

  DIRETURN(rValue * rValue);
} // end of DiSqr

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
diINLINE DiFloat DiSqrtR(DiFloat rValue)
{
  DIFUNCTION("DiSqrtR");
  

  DIRETURN(DiD2F((1.f/sqrt(DiF2D(rValue)))));
} // end of DiSqrtR

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
diINLINE DiFloat DiSin(DiFloat rValue)
{
  DIFUNCTION("DiSin");
  

  DIRETURN(DiD2F(sin(DiF2D(rValue))));
} // end of DiSin

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
diINLINE DiFloat DiCos(DiFloat rValue)
{
  DIFUNCTION("DiCos");
  

  DIRETURN(DiD2F(cos(DiF2D(rValue))));
} // end of DiCos

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
diINLINE DiFloat DiTan(DiFloat rValue)
{
  DIFUNCTION("DiTan");
  

  DIRETURN(DiD2F(tan(DiF2D(rValue))));
} // end of DiTan

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
diINLINE DiFloat DiASin(DiFloat rValue)
{
  DIFUNCTION("DiASin");
  

  DIRETURN(DiD2F(asin(DiF2D(rValue))));
} // end of DiASin

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
diINLINE DiFloat DiACos(DiFloat rValue)
{
  DIFUNCTION("DiACos");
  
  DIASSERT(DiFAbs(rValue) <= 1.0f);

  DIRETURN(DiD2F(acos(DiF2D(rValue))));
} // end of DiACos

diINLINE DiFloat DiATan(DiFloat rValue)
{
  DIFUNCTION("DiATan");
  

  DIRETURN(DiD2F(atan(DiF2D(rValue))));
} // end of DiACos


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
diINLINE DiBool DiSinCos(DiFloat rValue, DiFloat * rpSin, DiFloat * rpCos)
{
  DIFUNCTION("DiSinCos");
  
  DIASSERT(rpSin);
  DIASSERT(rpCos);

  // calc sin/cos
  *rpSin = DiSin(rValue);
  *rpCos = DiCos(rValue);

  DIRETURN(TRUE);
} // end of DiSinCos

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   rValue1
 * @param   rValue2
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiFloat DiFMin(DiFloat rValue1, DiFloat rValue2)
{
  DiSplitBits sbX, sbY, sbZ;
  DiFloat     rRet;

  DIFUNCTION("DiFMin");
  

  DI_SB_ASSIGN(sbX, rValue1);
  DI_SB_ASSIGN(sbY, rValue2);
  DI_SB_ASSIGN(sbZ, rValue1 - rValue2);
  sbZ.nInt >>= 31;
  sbX.nInt = (sbX.nInt & sbZ.nInt) + (sbY.nInt & (~sbZ.nInt));
  rRet = sbX.rFloat;

  DIRETURN(rRet);
} // end of DiFMin

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   rValue1
 * @param   rValue2
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiFloat DiFMax(DiFloat rValue1, DiFloat rValue2)
{
  DiSplitBits sbX, sbY, sbZ;
  DiFloat     rRet;

  DIFUNCTION("DiFMax");
  

  DI_SB_ASSIGN(sbX, rValue1);
  DI_SB_ASSIGN(sbY, rValue2);
  DI_SB_ASSIGN(sbZ, rValue1 - rValue2);
  sbZ.nInt >>= 31;
  sbX.nInt = (sbX.nInt & (~sbZ.nInt)) + (sbY.nInt & sbZ.nInt);
  rRet = sbX.rFloat;

  DIRETURN(rRet);
} // end of DiFMax

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  TRUE on success, FALSE otherwise
 * @param   rValue1
 * @param   rValue2
 * @param   rpMin
 * @param   rpMax
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiBool  DiFMinMax(DiFloat rValue1, DiFloat rValue2, DiFloat * rpMin, DiFloat * rpMax)
{
  DiSplitBits sbX, sbY, sbZ, sbW;

  DIFUNCTION("DiFMinMax");
  
  DIASSERT(rpMin);
  DIASSERT(rpMax);

  DI_SB_ASSIGN(sbX, rValue1);
  DI_SB_ASSIGN(sbY, rValue2);
  DI_SB_ASSIGN(sbZ, rValue1 - rValue2);
  sbZ.nInt >>= 31;
  sbW.nInt = (sbX.nInt & sbZ.nInt) + (sbY.nInt & (~sbZ.nInt));
  (*rpMin) = sbW.rFloat;
  sbX.nInt = (sbX.nInt & (~sbZ.nInt)) + (sbY.nInt & sbZ.nInt);
  (*rpMax) = sbX.rFloat;

  DIRETURN(TRUE);
} // end of DiFMinMax


// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   rValue
 * @param   rDown
 * @param   rUp
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiFloat DiFFitIn(DiFloat rValue, DiFloat rDown, DiFloat rUp)
{
  DiSplitBits sbX, sbLower, sbUpper, sbZLow, sbZUpr;
  DiFloat     rRet;

  DIFUNCTION("DiFFitIn");
  
  DIASSERT((rDown) <= (rUp));

  DI_SB_ASSIGN(sbX, rValue);
  DI_SB_ASSIGN(sbLower, rDown);
  DI_SB_ASSIGN(sbUpper, rUp);
  DI_SB_ASSIGN(sbZLow, rValue - rDown);
  DI_SB_ASSIGN(sbZUpr, rUp - rValue);
  sbZLow.nInt >>= 31;
  sbZUpr.nInt >>= 31;
  sbX.nInt = (sbLower.nInt & (sbZLow.nInt)) +
             (sbX.nInt & (~sbZLow.nInt) & (~sbZUpr.nInt)) +
             (sbUpper.nInt & (sbZUpr.nInt));
  rRet = sbX.rFloat;

  DIRETURN(rRet);
} // end of DiFFitIn

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   nValue1
 * @param   nValue2
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiInt32 DiIMin(DiInt32 nValue1, DiInt32 nValue2)
{
  DiInt32 nF, nRet;

  DIFUNCTION("DiIMin");
  

  nF = ((DiInt32)(nValue1 - nValue2)) >> 31;
  nRet = (nValue1 & nF) + (nValue2 & (~nF));

  DIRETURN(nRet);
} // end of DiIMin;

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   nValue1
 * @param   nValue2
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiInt32 DiIMax(DiInt32 nValue1, DiInt32 nValue2)
{
  DiInt32 nF, nRet;

  DIFUNCTION("DiIMax");
  

  nF = ((DiInt32)(nValue1 - nValue2)) >> 31;
  nRet = (nValue1 & (~nF)) + (nValue2 & nF);

  DIRETURN(nRet);
} // end of DiIMax

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   nValue
 * @param   nDown
 * @param   nUp
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiInt32 DiIFitIn(DiInt32 nValue, DiInt32 nDown, DiInt32 nUp)
{
  DiInt32 nLo = ((DiInt32)(nValue - nDown)) >> 31,
          nHi = ((DiInt32)(nUp - nValue)) >> 31,
          nRet;

  DIFUNCTION("DiIFitIn");
  
  DIASSERT((nDown) <= (nUp));

  nRet = (nDown & nLo) + (nValue & (~nLo) & (~nHi)) + (nUp & nHi);

  DIRETURN(nRet);
} // end of DiIFitIn

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  TRUE on success, FALSE otherwise
 * @param   rValue
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiBool DiIsFinite(DiFloat rValue)
{
  DIFUNCTION("DiIsFinite");
  

#ifdef __MWERKS__
  DIRETURN(isfinite(rValue));
#else
  DIRETURN(_finite(rValue));
#endif __MWERKS__

  DIRETURN(TRUE);
} // end of DiIsFinite

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
#define diFPU_ROUND_MODE_TRUNCATE   3<<10
diINLINE DiInt32 DiF2L(DiFloat rValue)
{
  DiInt16 nOldMode, nNewMode;
  DiInt32 nRet;

  DIFUNCTION("DiF2L");
  

  __asm
  {
    // flag setting
    fnstcw  WORD PTR nOldMode
    mov     AX, nOldMode
    and     AX, (~(3<<10))
    or      AX, WORD PTR diFPU_ROUND_MODE_TRUNCATE
    mov     nNewMode , AX
    fldcw   WORD PTR nNewMode

    // conversion
    fld    rValue
    fistp  nRet

    // back old flag
    fldcw   WORD PTR nOldMode
  }

  DIRETURN(nRet);
} // end of DiF2L

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   nValue
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiFloat DiL2F(DiInt32 nValue)
{
  DIFUNCTION("DiL2F");
  

  DIRETURN((DiFloat)nValue);
} // end of DiL2F

// *******************************************************************
/**
 * This function 
 *
 * @memo    
 * @return  
 * @param   nValue
 * @header  DiMFunc.h
 * @library Common.lib
 * @author  Max
 * @see     
 */
// *******************************************************************
diINLINE DiFloat DiUL2F(DiUInt32 nValue)
{
  DIFUNCTION("DiUL2F");
  

  DIRETURN((DiFloat)nValue);
} // end of DiUL2F

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
diINLINE DiDouble DiF2D(DiFloat rValue)
{
  DIFUNCTION("DiF2D");
  

  DIRETURN((DiDouble)rValue);
} // end of DiF2D

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
diINLINE DiFloat DiD2F(DiDouble rValue)
{
  DIFUNCTION("DiD2F");
  

  DIRETURN((DiFloat)rValue);
} // end of DiD2F

///eugbelNSCENE///} // end of namespace NScene


// end of dimath.inl
