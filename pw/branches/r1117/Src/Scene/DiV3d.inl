/*
 * @file    DiV3d.inl
 * @memo    inline functions for DiV3d structure (should be included
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

diINLINE DiVoid DiV3dMakeUnit(DiV3d *vpVect)
{
  DiFloat   rLen, rRecLen;

  rLen = DiV3dNorma(vpVect);
  DIASSERT(rLen > 0.f);

  rRecLen = DiSqrtR(rLen);
  vpVect->x = vpVect->x * rRecLen;
  vpVect->y = vpVect->y * rRecLen;
  vpVect->z = vpVect->z * rRecLen;
}


/**
 * This function is used to copy vector
 *
 * @memo    Copy vector
 * @return  none
 * @param   vpIn  vector [in]
 * @param   vpDst vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV3dCopy(const DiV3d *vpIn, DiV3d *vpDst)
{
  vpDst->x = vpIn->x;
  vpDst->y = vpIn->y;
  vpDst->z = vpIn->z;
} // end of DiV3dCopy

/**
 * This function is used to calculate norma for a given vector
 * @memo     Obtain norm for a given vector
 * @param    vpVect vector
 * @return   norma
 * @header   DiVector.h
 */
diINLINE DiFloat DiV3dNorma(const DiV3d *vpVect)
{
  DiFloat rNorma;

  rNorma = vpVect->x * vpVect->x +
           vpVect->y * vpVect->y +
           vpVect->z * vpVect->z;

  return rNorma;
} // end of DiV3dNorma

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
diINLINE DiVoid DiV3dZero(DiV3d *vpVect)
{
  vpVect->x = 0.f;
  vpVect->y = 0.f;
  vpVect->z = 0.f;
} // end of DiV3dZero

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
diINLINE DiBool DiV3dIsZero(const DiV3d *vpVect)
{
  DiBool bRet;

  bRet =(((((DiSplitBits*)&(vpVect->x))->nUInt |
         ((DiSplitBits*)&(vpVect->y))->nUInt   |
         ((DiSplitBits*)&(vpVect->z))->nUInt) & 0x7FFFFFFF) == 0);

  return bRet;
} // end of DiV3dIsZero

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
diINLINE DiVoid DiV3dAdd(const DiV3d *vpA, const DiV3d *vpB, DiV3d *vpC)
{
  vpC->x = vpA->x + vpB->x;
  vpC->y = vpA->y + vpB->y;
  vpC->z = vpA->z + vpB->z;
} // end of DiV3dAdd

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
diINLINE DiVoid DiV3dSub(const DiV3d *vpA, const DiV3d *vpB, DiV3d *vpC)
{
  vpC->x = vpA->x - vpB->x;
  vpC->y = vpA->y - vpB->y;
  vpC->z = vpA->z - vpB->z;
} // end of DiV3dSub

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
diINLINE DiVoid DiV3dScale(const DiV3d *vpIn, DiFloat rScale, DiV3d *vpOut)
{
  vpOut->x = vpIn->x * rScale;
  vpOut->y = vpIn->y * rScale;
  vpOut->z = vpIn->z * rScale;
} // end of DiV3dScale

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
diINLINE DiVoid DiV3dNegate(const DiV3d *vpIn, DiV3d *vpOut)
{
  vpOut->x = -vpIn->x;
  vpOut->y = -vpIn->y;
  vpOut->z = -vpIn->z;
} // end of DiV3dNegate

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
diINLINE DiVoid DiV3dLineComb(const DiV3d *vpVect1, DiFloat rCoef1,
                              const DiV3d *vpVect2, DiFloat rCoef2,
                              DiV3d *vpOut)
{
  vpOut->x = diSHIFT_COMB(vpVect1->x, rCoef1, vpVect2->x * rCoef2);
  vpOut->y = diSHIFT_COMB(vpVect1->y, rCoef1, vpVect2->y * rCoef2);
  vpOut->z = diSHIFT_COMB(vpVect1->z, rCoef1, vpVect2->z * rCoef2);
} // end of DiV3dLineComb

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
diINLINE DiVoid DiV3dShiftComb(const DiV3d *vpVect1, const DiV3d *vpVect2, 
                               DiFloat rCoef, DiV3d *vpOut)
{
  vpOut->x = diSHIFT_COMB(vpVect2->x, rCoef, vpVect1->x);
  vpOut->y = diSHIFT_COMB(vpVect2->y, rCoef, vpVect1->y);
  vpOut->z = diSHIFT_COMB(vpVect2->z, rCoef, vpVect1->z);
} // end of DiV3dShiftComb

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
diINLINE DiVoid DiV3dAverage(const DiV3d *vpVect1, const DiV3d *vpVect2, DiV3d *vpOut)
{
  vpOut->x = (vpVect1->x + vpVect2->x) * 0.5f;
  vpOut->y = (vpVect1->y + vpVect2->y) * 0.5f;
  vpOut->z = (vpVect1->z + vpVect2->z) * 0.5f;
} // end of DiV3dAverage

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
diINLINE DiFloat DiV3dDotProduct(const DiV3d *vpVect1, const DiV3d *vpVect2)
{
  DiFloat rDot;

  rDot = vpVect1->x * vpVect2->x +
         vpVect1->y * vpVect2->y +
         vpVect1->z * vpVect2->z;

  return rDot;
} // end of DiV3dDotProduct


/**
 * This function is used to calculate dot product
 *
 * @memo    Calculate flat dot product for a given vectors
 * @return  dot product value
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiV3dDotProduct2D(const DiV3d *vpVect1, const DiV3d *vpVect2)
{
  DiFloat rDot;

  rDot = vpVect1->x * vpVect2->x +
         vpVect1->z * vpVect2->z;

  return rDot;
} // end of DiV3dDotProduct

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
diINLINE DiVoid DiV3dCrossProduct(const DiV3d *vpVect1, const DiV3d *vpVect2, DiV3d *vpOut)
{
  DIASSERT(vpVect1 != vpOut);
  DIASSERT(vpVect2 != vpOut);

  vpOut->x = vpVect1->y * vpVect2->z - vpVect1->z * vpVect2->y;   \
  vpOut->y = vpVect1->z * vpVect2->x - vpVect1->x * vpVect2->z;   \
  vpOut->z = vpVect1->x * vpVect2->y - vpVect1->y * vpVect2->x;   \
} // end of DiV3dCrossProduct

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
diINLINE DiFloat DiV3dNormalize(const DiV3d *vpIn, DiV3d *vpOut)
{
  DiFloat   rLen, rRecLen;

  rLen = DiV3dNorma(vpIn);
  
  rLen = DiSqrt(rLen);
  DIASSERT(rLen > 0.f);

  rRecLen = 1.0f / rLen;  
  vpOut->x = vpIn->x * rRecLen;
  vpOut->y = vpIn->y * rRecLen;
  vpOut->z = vpIn->z * rRecLen;

  return (rLen);
} // end of DiV3dNormalize

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
diINLINE DiFloat DiV3dLength(const DiV3d *vpVect)
{
  DiFloat   rLen;

  rLen = DiV3dNorma(vpVect);
  rLen = DiSqrt(rLen);

  return (rLen);
} // end of DiV3dLength

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
diINLINE DiVoid DiV3dSetLength(const DiV3d *vpIn, DiFloat rLen, DiV3d *vpOut)
{
  DiFloat   rOldLen;
  DiFloat   rScale;

  rOldLen = DiV3dLength(vpIn);
  DIASSERT(rOldLen > 0.f);
  rScale  = rLen / rOldLen;
  DiV3dScale(vpIn, rScale, vpOut);
} // end of DiV3dSetLength

/**
 * This function is used to get squared distance between two points
 *
 * @memo    Get squared distance between two points
 * @return  distance
 * @param   vpP0 point
 * @param   vpP1 point
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiV3dPointDistance2(const DiV3d *vpP0, const DiV3d *vpP1)
{
  DiV3d   vV;
  DiFloat rDist;

  DiV3dSub(vpP0, vpP1, &vV);
  rDist = DiV3dNorma(&vV);
  
  return (rDist);
} // end of DiV3dPointDistance2

/**
 * This function is used to calculate triple scalar product
 * for a given vectors
 *
 * @memo    Calculate triple scalar product for a given vectors
 * @return  triple scalar product (a * (b x c))
 * @param   vpVect1 vector
 * @param   vpVect2 vector
 * @param   vpVect3 vector
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiV3dTripleScalarProduct(const DiV3d *vpVect1,
                                          const DiV3d *vpVect2,
                                          const DiV3d *vpVect3)
{
  DiFloat rRes;

  rRes = vpVect1->x * (vpVect2->y * (vpVect3)->z - vpVect2->z * vpVect3->y) +
         vpVect1->y * (vpVect2->z * vpVect3->x - vpVect2->x * vpVect3->z)   +
         vpVect1->z * (vpVect2->x * vpVect3->y - vpVect2->y * vpVect3->x);

  return rRes;
} // end of DiV3dTripleScalarProduct

/**
 * This function is used to add x & z components of
 * the given vectors
 *
 * @memo    Add x & z commponents for a given vectors
 * @return  none
 * @param   vpA vector [in]
 * @param   vpB vector [in]
 * @param   vpC vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV3dAdd2D(const DiV3d *vpA, const DiV3d *vpB, DiV2d *vpC)
{
  vpC->x = vpA->x + vpB->x;
  vpC->z = vpA->z + vpB->z;
} // end of DiV3dAdd2D

/**
 * This function is used to substract x & z components
 * of the given vectors
 *
 * @memo    Substract x & z components of the given vectors
 * @return  none
 * @param   vpA vector [in]
 * @param   vpB vector [in]
 * @param   vpC vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV3dSub2D(const DiV3d *vpA, const DiV3d *vpB, DiV2d *vpC)
{
  vpC->x = vpA->x - vpB->x;
  vpC->z = vpA->z - vpB->z;
} // end of DiV3dSub2D

/**
 * This function is used to scale x & z components of 
 * the given vector
 *
 * @memo    Scale x & z components of a given vector
 * @return  none
 * @param   vpIn   vector [in]
 * @param   rScale scale  [in]
 * @param   vpOut  vector [out]
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiVoid DiV3dScale2D(const DiV3d *vpIn, DiFloat rScale, DiV2d *vpOut)
{
  vpOut->x = vpIn->x * rScale;
  vpOut->z = vpIn->z * rScale;
} // end of DiV3dScale2D

/**
 * This function is used to calculate norma for a given vector
 * @memo     Obtain norm for a given vector (uses only x & z components)
 * @param    vpVect vector
 * @return   norma
 * @header   DiVector.h
 */
diINLINE DiFloat DiV3dNorma2D(const DiV3d *vpVect)
{
  DiFloat rNorma;

  rNorma = vpVect->x * vpVect->x +
           vpVect->z * vpVect->z;

  return rNorma;
} // end of DiV3dNorma2D

/**
 * This function is used to get vector length
 *
 * @memo    Get vector length (use only x & z components)
 * @return  vector length
 * @param   vpVect vector
 * @header  DiVector.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
diINLINE DiFloat DiV3dLength2D(const DiV3d *vpVect)
{
  DiFloat   rLen;

  rLen = DiV3dNorma2D(vpVect);
  rLen = DiSqrt(rLen);

  return (rLen);
} // end of DiV3dLength2D

/**
 * This function is used to calculate cross product
 * 
 * @memo    Calculate cross product (using x & z components only)
 * @return  none
 * @param   vpVect1 vector [in]
 * @param   vpVect2 vector [in]
 * @param   vpOut   vector [out]
 * @header  DiVector.h
 * @librarz Common.lib
 * @author  Gandz
 * @see     
 */
diINLINE DiFloat DiV3dCrossProduct2D(const DiV3d *vpVect1, const DiV3d *vpVect2)
{
  DiFloat rCross;

  rCross = -vpVect1->z * vpVect2->x + vpVect1->x * vpVect2->z;

  return rCross;
} // end of DiV3dCrossProduct2D

///eugbelNSCENE///} // end of namespace NScene
