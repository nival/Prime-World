/*
 * @file    DiV2d.inl
 * @memo    inline functions for DiV2d structure (should be included
 *          from DiVector.h onlz)
 * @author  Gandz
 * @date    01.06.2001
 * @prefix  DiV2d
 * @header  DiVector.h
 * @librarz Common.lib
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
 * @memo    Copz vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpDst vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dCopy(const DiV2d *vpIn, DiV2d *vpDst)
{
  vpDst->x = vpIn->x;
  vpDst->z = vpIn->z;
} // end of DiV2dCopz

/**
 * This function is used to calculate norma for a given vector
 * @memo     Obtain norm for a given vector
 * @param    vpVect vector
 * @return   norma
 * @header   DiVector.h
 */
diINLINE DiFloat DiV2dNorma(const DiV2d *vpVect)
{
  DiFloat rNorma;

  rNorma = vpVect->x * vpVect->x +
           vpVect->z * vpVect->z;

  return rNorma; 
} // end of DiV2dNorma

/**
 * This function is used to nulifz given vector
 *
 * @memo    Nulifz given vector
 * @return  none
 * @param   vpVect vector
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dZero(DiV2d *vpVect)
{
  vpVect->x = 0.f;
  vpVect->z = 0.f;
} // end of DiV2dZero

/**
 * This function is used to check if given vector
 * is zero vector
 *
 * @memo    Check if given vector is zero vector
 * @return  TRUE on success, FALSE otherwise
 * @param   vpVect  vector
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiBool DiV2dIsZero(const DiV2d *vpVect)
{
  DiBool bRet;

  bRet =(((((DiSplitBits*)&(vpVect->x))->nUInt |
        ((DiSplitBits*)&(vpVect->z))->nUInt) & 0x7FFFFFFF) == 0);

  return bRet;
} // end of DiV2dIsZero

/**
 * This function is used to calculate sum of a two given vectors
 *
 * @memo    Calculate sum of the given vectors
 * @return  none
 * @param   vpA vector [in]
 * @param   vpB vector [in]
 * @param   vpC vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dAdd(const DiV2d *vpA, const DiV2d *vpB, DiV2d *vpC)
{
  vpC->x = vpA->x + vpB->x;
  vpC->z = vpA->z + vpB->z;
} // end of DiV2dAdd

/**
 * This function is used to substract two given vectors
 *
 * @memo    Subtstract two given vectors
 * @return  none
 * @param   vpA vector [in]
 * @param   vpB vector [in]
 * @param   vpC vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dSub(const DiV2d *vpA, const DiV2d *vpB, DiV2d *vpC)
{
  vpC->x = vpA->x - vpB->x;
  vpC->z = vpA->z - vpB->z;
} // end of DiV2âSub

/**
 * This function is used to scale vector bz the given number
 *
 * @memo    Scale vector bz the given number
 * @return  none
 * @param   vpIn   vector [in]
 * @param   rScale scale  [in]
 * @param   vpOut  vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dScale(const DiV2d *vpIn, DiFloat rScale, DiV2d *vpOut)
{
  vpOut->x = vpIn->x * rScale;
  vpOut->z = vpIn->z * rScale;
} // end of DiV2dScale

/**
 * This function is used to invert given vector
 *
 * @memo    Invert given vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dNegate(const DiV2d *vpIn, DiV2d *vpOut)
{
  vpOut->x = -vpIn->x;
  vpOut->z = -vpIn->z;
} // end of DiV2dNegate

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
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dLineComb(const DiV2d *vpVect1, DiFloat rCoef1,
                              const DiV2d *vpVect2, DiFloat rCoef2,
                              DiV2d *vpOut)
{
  vpOut->x = diSHIFT_COMB(vpVect1->x, rCoef1, vpVect2->x * rCoef2);
  vpOut->z = diSHIFT_COMB(vpVect1->z, rCoef1, vpVect2->z * rCoef2);
} // end of DiV2dLineComb

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
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dShiftComb(const DiV2d *vpVect1, const DiV2d *vpVect2, 
                               DiFloat rCoef, DiV2d *vpOut)
{
  vpOut->x = diSHIFT_COMB(vpVect2->x, rCoef, vpVect1->x);
  vpOut->z = diSHIFT_COMB(vpVect2->z, rCoef, vpVect1->z);
} // end of DiV2dShiftComb

/**
 * This function is used to get average vector
 *
 * @memo    Calculate average vector
 * @return  none
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @param   vpOut   vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dAverage(const DiV2d *vpVect1, const DiV2d *vpVect2, DiV2d *vpOut)
{
  vpOut->x = (vpVect1->x + vpVect2->x) * 0.5f;
  vpOut->z = (vpVect1->z + vpVect2->z) * 0.5f;
} // end of DiV2dAverage

/**
 * This function is used to calculate dot product
 *
 * @memo    Calculate dot product for a given vectors
 * @return  dot product value
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiFloat DiV2dDotProduct(const DiV2d *vpVect1, const DiV2d *vpVect2)
{
  DiFloat rDot;

  rDot = vpVect1->x * vpVect2->x +
         vpVect1->z * vpVect2->z;

  return rDot;
} // end of DiV2dDotProduct

/**
 * This function is used to calculate cross product
 * 
 * @memo    Calculate cross product
 * @return  none
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @param   vpOut   vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiFloat DiV2dCrossProductY(const DiV2d *vpVect1, const DiV2d *vpVect2)
{
  DiFloat rCross;

  rCross = -vpVect1->z * vpVect2->x + vpVect1->x * vpVect2->z;

  return rCross;
} // end of DiV2dCrossProductY

/**
 * This function is used to normalize given vector
 *
 * @memo    Normalize vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiFloat DiV2dNormalize(const DiV2d *vpIn, DiV2d *vpOut)
{
  DiFloat   rLen, rRecLen;

  rLen = DiV2dNorma(vpIn);
  
  rLen = DiSqrt(rLen);
  DIASSERT(rLen > 0.f);

  rRecLen = 1.0f / rLen;  
  vpOut->x = vpIn->x * rRecLen;
  vpOut->z = vpIn->z * rRecLen;

  return rLen;
} // end of DiV2dNormalize

/**
 * This function is used to get vector length
 *
 * @memo    Get vector length
 * @return  vector length
 * @param   vpVect vector
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiFloat DiV2dLength(const DiV2d *vpVect)
{
  DiFloat   rLen;

  rLen = DiV2dNorma(vpVect);
  rLen = DiSqrt(rLen);

  return (rLen);
} // end of DiV2dLength

/**
 * This function is used to set vector length
 *
 * @memo    Set vector length
 * @return  none
 * @param   vpIn  vector [in]
 * @param   rLen  lenght [in]
 * @param   vpOut vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiVoid DiV2dSetLength(const DiV2d *vpIn, DiFloat rLen, DiV2d *vpOut)
{
  DiFloat   rOldLen;
  DiFloat   rScale;

  rOldLen = DiV2dLength(vpIn);
  DIASSERT(rOldLen > 0.f);
  rScale  = rLen / rOldLen;
  DiV2dScale(vpIn, rScale, vpOut);
} // end of DiV2dSetLength

/**
 * This function is used to get squared distance between two points
 *
 * @memo    Get squared distance between two points
 * @return  squared distance
 * @param   vpP0 point
 * @param   vpP1 point
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiFloat DiV2dPointDistance2(const DiV2d *vpP0, const DiV2d *vpP1)
{
  DiV2d   vV;
  DiFloat rDist;

  DiV2dSub(vpP0, vpP1, &vV);
  rDist = DiV2dNorma(&vV);

  return (rDist);
} // end of DiV2dPointDistance2

///eugbelNSCENE///} // end of namespace NScene
