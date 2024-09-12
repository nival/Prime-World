/*
 * @file    DiV4d.inl
 * @memo    inline functions for DiV4d structure - (should be included
 *          from DiVector.h only)
 * @author  Gandy
 * @date    01.06.2001
 * @prefix  DiV3d
 * @header  DiVector.h
 * @library Common.lib
 */

// *******************************************************************
// includes
#include "DiTypes.h"

///eugbelNSCENE///namespace NScene {

// *******************************************************************
// functions

/**
 * This function is used to copy vector
 *
 * @memo    Copy vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dCopy(const DiV4d *vpIn, DiV4d *vpOut)
{
  // Alignment check
  DIASSERT(!((DiUInt32)(vpIn) & 15));
  DIASSERT(!((DiUInt32)(vpOut) & 15));

  vpOut->x = vpIn->x;
  vpOut->y = vpIn->y;
  vpOut->z = vpIn->z;
  vpOut->w = vpIn->w;
} // end of DiV4dCopy

/**
 * This function is used to calculate norma for a given vector using only flat components
 * @memo     Obtain norm for a given vector
 * @param    vpVect vector
 * @return   norma
 * @header   DiVector.h
 */
diINLINE DiFloat DiV4dNorma2d(const DiV4d *vpVect)
{
  DiFloat   rRet;

  rRet = vpVect->x * vpVect->x + 
         vpVect->z * vpVect->z ;

  return rRet;
} // end of DiV4dNorma2d

/**
 * This function is used to nulify given vector
 *
 * @memo    Nulify given vector
 * @return  none
 * @param   vpVect vector
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dZero(DiV4d *vpVect)
{
  vpVect->x = 0.0f;
  vpVect->y = 0.0f;
  vpVect->z = 0.0f;
  vpVect->w = 0.0f;
} // end of DiV4dZero

/**
 * This function is used to check if given vector
 * is zero vector
 *
 * @memo    Check if given vector is zero vector
 * @return  TRUE on success, FALSE otherwise
 * @param   vpVect  vector
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiBool DiV4dIsZero(const DiV4d *vpVect)
{
  DiBool  bRet;

  bRet =  (((((DiSplitBits*)&(vpVect->x))->nUInt |
          ((DiSplitBits*)&(vpVect->y))->nUInt    |         
          ((DiSplitBits*)&(vpVect->z))->nUInt) & 0x7FFFFFFF) == 0);

  return (bRet);
} // end of DiV4dIsZero

/**
 * This function is used to calculate sum of a two given vectors
 *
 * @memo    Calculate sum of the given vectors
 * @return  none
 * @param   vpA vector [in]
 * @param   vpB vector [in]
 * @param   vpC vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dAdd(const DiV4d *vpA, const DiV4d *vpB, DiV4d *vpC)
{
  vpC->x = vpA->x + vpB->x;
  vpC->y = vpA->y + vpB->y;
  vpC->z = vpA->z + vpB->z;
  vpC->w = 1.0f;
} // end of DiV4dAdd

/**
 * This function is used to substract two given vectors
 *
 * @memo    Subtstract two given vectors
 * @return  none
 * @param   vpA vector [in]
 * @param   vpB vector [in]
 * @param   vpC vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dSub(const DiV4d *vpA, const DiV4d *vpB, DiV4d *vpC)
{
  vpC->x = vpA->x - vpB->x;
  vpC->y = vpA->y - vpB->y;
  vpC->z = vpA->z - vpB->z;
  vpC->w = 1.0f;
} // end of DiV4dSub

/**
 * This function is used to scale vector by the given number
 *
 * @memo    Scale vector by the given number
 * @return  none
 * @param   vpIn   vector [in]
 * @param   rScale scale  [in]
 * @param   vpOut  vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dScale(const DiV4d *vpIn, DiFloat rScale, DiV4d *vpOut)
{
  vpOut->x = vpIn->x * rScale;
  vpOut->y = vpIn->y * rScale;
  vpOut->z = vpIn->z * rScale;
  vpOut->w = 1.0f;
}

/**
 * This function is used to shift vector by the given number
 *
 * @memo    Scale vector by the given number
 * @return  none
 * @param   vpIn   vector [in]
 * @param   rShift scale  [in]
 * @param   vpOut  vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Earnol
 * @see     
 */
diINLINE DiVoid DiV4dShift(const DiV4d *vpIn, DiFloat rShift, DiV4d *vpOut)
{
  vpOut->x = vpIn->x + rShift;
  vpOut->y = vpIn->y + rShift;
  vpOut->z = vpIn->z + rShift;
  vpOut->w = 1.0f;
}

/**
 * This function is used to invert given vector
 *
 * @memo    Invert given vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dNegate(const DiV4d *vpIn, DiV4d *vpOut)
{
  vpOut->x = -vpIn->x;
  vpOut->y = -vpIn->y;
  vpOut->z = -vpIn->z;
  vpOut->w = 1.0f;
}

/**
 * This function is used to invert given quaternion
 *
 * @memo    Invert given vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Miron
 * @see     
 */
diINLINE DiVoid DiQuatNegate(const DiV4d *vpIn, DiV4d *vpOut)
{
  vpOut->x = -vpIn->x;
  vpOut->y = -vpIn->y;
  vpOut->z = -vpIn->z;
  vpOut->w = -vpIn->w;
}

/**
 * This function is used to combine given vectors
 *
 * @memo    combines given vectors (v1 * scalar1 + v2 * scalar2)
 * @return  none
 * @param   vpVect1   vector      [in]
 * @param   rCoef1    coefficient [in]
 * @param   vpVect2   vector      [in]
 * @param   rCoef2    coefficient [in]
 * @param   vpOut     vector      [out] 
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dLineComb(const DiV4d     *vpVect1, 
                              DiFloat         rCoef1, 
                              const DiV4d     *vpVect2, 
                              DiFloat         rCoef2, 
                              DiV4d           *vpOut)
{
  vpOut->x = diSHIFT_COMB(vpVect1->x, rCoef1, vpVect2->x * rCoef2);
  vpOut->y = diSHIFT_COMB(vpVect1->y, rCoef1, vpVect2->y * rCoef2);
  vpOut->z = diSHIFT_COMB(vpVect1->z, rCoef1, vpVect2->z * rCoef2);
  vpOut->w = 1.0f;
} // end of DiV4dLineComb

/**
 * This function is used to combine given quaternions
 *
 * @memo    combines given vectors (v1 * scalar1 + v2 * scalar2)
 * @return  none
 * @param   vpVect1   vector      [in]
 * @param   rCoef1    coefficient [in]
 * @param   vpVect2   vector      [in]
 * @param   rCoef2    coefficient [in]
 * @param   vpOut     vector      [out] 
 * @header  DiVector.h
 * @library Common.lib
 * @author  Miron
 * @see     
 */
diINLINE DiVoid DiQuatLineComb(const DiV4d     *vpVect1, 
                               DiFloat         rCoef1, 
                               const DiV4d     *vpVect2, 
                               DiFloat         rCoef2, 
                               DiV4d           *vpOut)
{
  vpOut->x = diSHIFT_COMB(vpVect1->x, rCoef1, vpVect2->x * rCoef2);
  vpOut->y = diSHIFT_COMB(vpVect1->y, rCoef1, vpVect2->y * rCoef2);
  vpOut->z = diSHIFT_COMB(vpVect1->z, rCoef1, vpVect2->z * rCoef2);
  vpOut->w = diSHIFT_COMB(vpVect1->w, rCoef1, vpVect2->w * rCoef2);
} // end of DiQuatLineComb

/**
 * This function is used to combine given vectors
 *
 * @memo    Combine given vectors (v1 + v2 * scalar)
 * @return  none
 * @param   vpVect1  vector [in]
 * @param   vpVect2  vector [in]
 * @param   rCoef    coeff for second vector [in]
 * @param   vpOut    vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dShiftComb(const DiV4d   *vpVect1,
                               const DiV4d   *vpVect2,
                               DiFloat       rCoef, 
                               DiV4d         *vpOut)
{
  vpOut->x = diSHIFT_COMB(vpVect2->x, rCoef, vpVect1->x);
  vpOut->y = diSHIFT_COMB(vpVect2->y, rCoef, vpVect1->y);
  vpOut->z = diSHIFT_COMB(vpVect2->z, rCoef, vpVect1->z);
  vpOut->w = 1.0f;
} // end of DiV4dShiftComb

/**
 * This function is used to get average vector
 *
 * @memo    Calculate average vector
 * @return  none
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @param   vpOut   vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dAverage(const DiV4d *vpVect1, const DiV4d *vpVect2, DiV4d *vpOut)
{
  vpOut->x = (vpVect1->x + vpVect2->x) * 0.5f;
  vpOut->y = (vpVect1->y + vpVect2->y) * 0.5f;
  vpOut->z = (vpVect1->z + vpVect2->z) * 0.5f;
  vpOut->w = 1.0f;
} // end of DiV4dAverage

/**
 * This function is used to calculate dot product
 *
 * @memo    Calculate dot product for a given vectors
 * @return  dot product value
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiV4dDotProduct(const DiV4d *vpVect1, const DiV4d *vpVect2)
{
  DiFloat   rDot;

  rDot = vpVect1->x * vpVect2->x +
         vpVect1->y * vpVect2->y +
         vpVect1->z * vpVect2->z;

  return(rDot);
} // end of DiV4dDotProduct


/**
 * This function is used to calculate dot product of quaterions
 *
 * @memo    Calculate dot product for a given vectors
 * @return  dot product value
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Miron
 * @see     
 */
diINLINE DiFloat DiQuatDotProduct(const DiV4d *vpVect1, const DiV4d *vpVect2)
{
  DiFloat   rDot;

  rDot = vpVect1->x * vpVect2->x +
         vpVect1->y * vpVect2->y +
         vpVect1->z * vpVect2->z +
         vpVect1->w * vpVect2->w;

  return(rDot);
} // end of DiV4dDotProduct

/**
 * This function is used to calculate dot product
 *
 * @memo    Calculate dot product for a given vectors using omly flat components
 * @return  dot product value
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiV4dDotProduct2d(const DiV4d *vpVect1, const DiV4d *vpVect2)
{
  DiFloat   rDot;

  rDot = vpVect1->x * vpVect2->x +
         vpVect1->z * vpVect2->z;

  return(rDot);
} // end of DiV4dDotProduct2d

/**
 * This function is used to calculate cross product
 * 
 * @memo    Calculate cross product
 * @return  none
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @param   vpOut   vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dCrossProduct(const DiV4d *vpVect1, const DiV4d *vpVect2, DiV4d *vpOut)
{
  vpOut->x = vpVect1->y * vpVect2->z - vpVect1->z * vpVect2->y;
  vpOut->y = vpVect1->z * vpVect2->x - vpVect1->x * vpVect2->z;
  vpOut->z = vpVect1->x * vpVect2->y - vpVect1->y * vpVect2->x;
  vpOut->w = 0.0f;
}

/**
 * This function is used to normalize given vector
 *
 * @memo    Normalize vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dNormalize(const DiV4d *vpIn, DiV4d *vpOut)
{
  DiFloat   rLen, rRecLen;

  rLen = DiV4dNorma(vpIn);
  
  rLen = DiSqrt(rLen);
  DIASSERT(rLen > 0.f);

  rRecLen = 1.0f / rLen;  
  vpOut->x = vpIn->x * rRecLen;
  vpOut->y = vpIn->y * rRecLen;
  vpOut->z = vpIn->z * rRecLen;
  vpOut->w = 0.0f;

  return ;
} // end of DiV4dNormalize

/**
 * This function is used to normalize given vector
 *
 * @memo    Normalize vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiV4dNormalizeExt(const DiV4d *vpIn, DiV4d *vpOut)
{
  DiFloat   rLen, rRecLen;

  rLen = DiV4dNorma(vpIn);
  
  rLen = DiSqrt(rLen);
  DIASSERT(rLen > 0.f);

  rRecLen = 1.0f / rLen;  
  vpOut->x = vpIn->x * rRecLen;
  vpOut->y = vpIn->y * rRecLen;
  vpOut->z = vpIn->z * rRecLen;
  vpOut->w = 0.0f;

  return rLen;
} // end of DiV4dNormalize

/**
 * This function is used to get vector length
 *
 * @memo    Get vector length
 * @return  vector length
 * @param   vpVect vector
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiV4dLength(const DiV4d *vpVect)
{
  DiFloat   rLen;

  rLen = DiV4dNorma(vpVect);
#if (defined(_MSC_VER) && defined (_M_IX86))
  DIASSERT(_finite(rLen));
#endif
  rLen = DiSqrt(rLen);
#if (defined(_MSC_VER) && defined (_M_IX86))
  DIASSERT(_finite(rLen));
#endif

  return (rLen);
} // end of DiV4dLength


/**
 * This function is used to normalize given vector
 *
 * @memo    Normalize vector
 * @return  none
 * @param   vpVect [in/out] vector 
 * @header  DiVector.h
 * @library Common.lib
 * @author  Paul
 * @see     
 */
diINLINE DiVoid DiV4dMakeUnit(DiV4d *vpVect)
{
  DiFloat   rLen, rRecLen;

  rLen = DiV4dNorma(vpVect);
  DIASSERT(rLen > 0.f);

  rRecLen = DiSqrtR(rLen);
  vpVect->x = vpVect->x * rRecLen;
  vpVect->y = vpVect->y * rRecLen;
  vpVect->z = vpVect->z * rRecLen;
  vpVect->w = 0.0f;
}


/**
 * This function is used to set vector length
 *
 * @memo    Set vector length
 * @return  none
 * @param   vpIn  vector [in]
 * @param   rLen  lenght [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV4dSetLength(const DiV4d *vpIn, const DiFloat rLen, DiV4d *vpOut)
{
  DiFloat   rOldLen;
  DiFloat   rScale;

  rOldLen = DiV4dLength(vpIn);
  DIASSERT(rOldLen > 0.f);
  rScale  = rLen / rOldLen;
  DiV4dScale(vpIn, rScale, vpOut);
} // end of DiV4dSetLength

///eugbelNSCENE///} // end of namespace NScene
