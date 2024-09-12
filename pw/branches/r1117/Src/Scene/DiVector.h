/*
 * @file    DiVector.h
 * @memo    
 * @author  Gandy
 * @date    01.06.2001
 * @prefix  
 * @header  
 * @library 
 */

#ifndef _DIVECTOR_H_
#define _DIVECTOR_H_

///eugbelNSCENE///namespace NScene {

// *******************************************************************
// includes
#include "DiTypes.h"
//#include "DiPlatf.h"
//#include "DiMFunc.h"

// *******************************************************************
// defines

#define diDECLARE_V4D(var) diDECLARE(DiV4d, var, 16)

// *******************************************************************
// data types

/**
 * This structure represents two-dimension vector -
 * @memo     2D vector (XZ plane)
 * @member   x
 * @member   z
 * @header   DiVector.h
 */
typedef struct tagDiV2d
{
  DiFloat x;
  DiFloat z;
} DiV2d;

/**
 * This structure represents three-dimension vector with floating point components.
 * @memo     3D vector (DiFloat)
 * @member   x
 * @member   y
 * @member   z
 * @header   DiVector.h
 */
typedef struct tagDiV3d
{
  DiFloat x;
  DiFloat y;
  DiFloat z;
} DiV3d;

/**
 * This structure represents four-dimension vector
 * with floating point components. This is usually used
 * for homogemious coordinate system and
 * hardware-friendly transformations/calculations
 *
 * @memo     4D vector (DiFloat)
 * @member   x
 * @member   y
 * @member   z
 * @member   w
 * @header   DiV4d.h
 */
typedef struct tagDiV4d
{
  DiFloat x;
  DiFloat y;
  DiFloat z;
  DiFloat w;
} DiV4d;

/**
 * This structure represents two-dimension vector with DoFloat components.
 *  Use for texture coordinates.
 *
 * @memo     2D texture coordinates vector
 * @member   u first coordinate
 * @member   v second coordinate
 * @header   DiVector.h
 */
typedef struct tagDiUV
{
  DiFloat u;
  DiFloat v;
} DiUV;

/**
 * This structure represents three-dimension vector with DiInt8 components.
 *  Use for normals and other vectors in representation
 *  <B>x == (DiInt8)(rX * 255.0f)</B> where <B>rX</B> - floating point number.
 *  This structure can be used as DiColor.
 *
 * @memo     3D vector (DiInt8)
 * @member   x
 * @member   y
 * @member   z
 * @member   nPad
 * @header   DiVector.h
 */
typedef struct tagDiV3dInt
{
  DiInt8    x;
  DiInt8    y;
  DiInt8    z;
  DiUInt8   nPad;
} DiV3dInt;

/**
 * This structure represents common normal.
 *
 * @memo     Normal
 * @member   vNormal   normal with floating point components
 * @member   viNormal  normal with integer components
 * @header   DiVector.h
 */
typedef struct tagDiNormal
{
  DiV3d    vNormal;
  DiV3dInt viNormal;
} DiNormal;

// *******************************************************************
// functions as defines

// *******************************************************************
// prototypes

// *******************************************************************
// 2d vectors
diINLINE DiVoid DiV2dCopy(const DiV2d *vpIn, DiV2d *vpDst);
diINLINE DiFloat DiV2dNorma(const DiV2d *vpVect);
diINLINE DiVoid DiV2dZero(DiV2d *vpVect);
diINLINE DiBool DiV2dIsZero(const DiV2d *vpVect);
diINLINE DiVoid DiV2dAdd(const DiV2d *vpA, const DiV2d *vpB, DiV2d *vpC);
diINLINE DiVoid DiV2dSub(const DiV2d *vpA, const DiV2d *vpB, DiV2d *vpC);
diINLINE DiVoid DiV2dScale(const DiV2d *vpIn, DiFloat rScale, DiV2d *vpOut);
diINLINE DiVoid DiV2dNegate(const DiV2d *vpIn, DiV2d *vpOut);
diINLINE DiVoid DiV2dLineComb(const DiV2d *vpVect1, DiFloat rCoef1,
                              const DiV2d *vpVect2, DiFloat rCoef2,
                              DiV2d *vpOut);
diINLINE DiVoid DiV2dShiftComb(const DiV2d *vpVect1, const DiV2d *vpVect2, 
                               DiFloat rCoef, DiV2d *vpOut);
diINLINE DiVoid DiV2dAverage(const DiV2d *vpVect1, const DiV2d *vpVect2, DiV2d *vpOut);
diINLINE DiFloat DiV2dDotProduct(const DiV2d *vpVect1, const DiV2d *vpVect2);
diINLINE DiFloat DiV2dCrossProductY(const DiV2d *vpVect1, const DiV2d *vpVect2);
diINLINE DiFloat DiV2dNormalize(const DiV2d *vpIn, DiV2d *vpOut);
diINLINE DiFloat DiV2dLength(const DiV2d *vpVect);
diINLINE DiVoid DiV2dSetLength(const DiV2d *vpIn, DiFloat rLen, DiV2d *vpOut);
diINLINE DiFloat DiV2dPointDistance2(const DiV2d *vpP0, const DiV2d *vpP1);
// *******************************************************************
// 3d vectors
diINLINE DiVoid DiV3dCopy(const DiV3d *vpIn, DiV3d *vpDst);
diINLINE DiFloat DiV3dNorma(const DiV3d *vpVect);
diINLINE DiVoid DiV3dZero(DiV3d *vpVect);
diINLINE DiBool DiV3dIsZero(const DiV3d *vpVect);
diINLINE DiVoid DiV3dAdd(const DiV3d *vpA, const DiV3d *vpB, DiV3d *vpC);
diINLINE DiVoid DiV3dSub(const DiV3d *vpA, const DiV3d *vpB, DiV3d *vpC);
diINLINE DiVoid DiV3dScale(const DiV3d *vpIn, DiFloat rScale, DiV3d *vpOut);
diINLINE DiVoid DiV3dNegate(const DiV3d *vpIn, DiV3d *vpOut);
diINLINE DiVoid DiV3dLineComb(const DiV3d *vpVect1, DiFloat rCoef1,
                              const DiV3d *vpVect2, DiFloat rCoef2,
                              DiV3d *vpOut);
diINLINE DiVoid DiV3dShiftComb(const DiV3d *vpVect1, const DiV3d *vpVect2, 
                               DiFloat rCoef, DiV3d *vpOut);
diINLINE DiVoid DiV3dAverage(const DiV3d *vpVect1, const DiV3d *vpVect2, DiV3d *vpOut);
diINLINE DiFloat DiV3dDotProduct(const DiV3d *vpVect1, const DiV3d *vpVect2);
diINLINE DiFloat DiV3dDotProduct2D(const DiV3d *vpVect1, const DiV3d *vpVect2);
diINLINE DiVoid DiV3dCrossProduct(const DiV3d *vpVect1, const DiV3d *vpVect2, DiV3d *vpOut);
diINLINE DiFloat DiV3dNormalize(const DiV3d *vpIn, DiV3d *vpOut);
diINLINE DiFloat DiV3dLength(const DiV3d *vpVect);
diINLINE DiVoid DiV3dSetLength(const DiV3d *vpIn, DiFloat rLen, DiV3d *vpOut);
diINLINE DiFloat DiV3dPointDistance2(const DiV3d *vpP0, const DiV3d *vpP1);
diINLINE DiFloat DiV3dTripleScalarProduct(const DiV3d *vpVect1,
                                          const DiV3d *vpVect2,
                                          const DiV3d *vpVect3);
diINLINE DiVoid DiV3dAdd2D(const DiV3d *vpA, const DiV3d *vpB, DiV2d *vpC);
diINLINE DiVoid DiV3dSub2D(const DiV3d *vpA, const DiV3d *vpB, DiV2d *vpC);
diINLINE DiVoid DiV3dScale2D(const DiV3d *vpIn, DiFloat rScale, DiV2d *vpOut);
diINLINE DiFloat DiV3dNorma2D(const DiV3d *vpVect);
diINLINE DiFloat DiV3dLength2D(const DiV3d *vpVect);
diINLINE DiFloat DiV3dCrossProduct2D(const DiV3d *vpVect1, const DiV3d *vpVect2);
// *******************************************************************
// 4d vectors

diINLINE DiVoid DiV4dCopy(const DiV4d *vpIn, DiV4d *vpOut);
#define DiV4dNorma(vpVec)   DiV4dDotProduct((vpVec),(vpVec))
diINLINE DiFloat DiV4dNorma2d(const DiV4d *vpVect);
diINLINE DiVoid DiV4dZero(DiV4d *vpVect);
diINLINE DiBool DiV4dIsZero(const DiV4d *vpVect);
diINLINE DiVoid DiV4dAdd(const DiV4d *vpA, const DiV4d *vpB, DiV4d *vpC);
diINLINE DiVoid DiV4dSub(const DiV4d *vpA, const DiV4d *vpB, DiV4d *vpC);
diINLINE DiVoid DiV4dScale(const DiV4d *vpIn, DiFloat rScale, DiV4d *vpOut);
diINLINE DiVoid DiV4dShift(const DiV4d *vpIn, DiFloat rShift, DiV4d *vpOut);
diINLINE DiVoid DiV4dNegate(const DiV4d *vpIn, DiV4d *vpOut);
diINLINE DiVoid DiQuatNegate(const DiV4d *vpIn, DiV4d *vpOut);
diINLINE DiVoid DiV4dLineComb(const DiV4d *vpVect1, DiFloat rCoef1, 
                              const DiV4d *vpVect2, DiFloat rCoef2, 
                              DiV4d *vpOut);
diINLINE DiVoid DiQuatLineComb(const DiV4d *vpVect1, DiFloat rCoef1, 
                               const DiV4d *vpVect2, DiFloat rCoef2, 
                               DiV4d *vpOut);
diINLINE DiVoid DiV4dShiftComb(const DiV4d *vpVect1, const DiV4d *vpVect2,
                               DiFloat rCoef, DiV4d *vpOut);
diINLINE DiVoid DiV4dAverage(const DiV4d *vpVect1, const DiV4d *vpVect2, DiV4d *vpOut);
diINLINE DiFloat DiV4dDotProduct(const DiV4d *vpVect1, const DiV4d *vpVect2);
diINLINE DiFloat DiQuatDotProduct(const DiV4d *vpVect1, const DiV4d *vpVect2);
diINLINE DiFloat DiV4dDotProduct2d(const DiV4d *vpVect1, const DiV4d *vpVect2);
diINLINE DiVoid DiV4dCrossProduct(const DiV4d *vpVect1, const DiV4d *vpVect2, DiV4d *vpOut);
diINLINE DiFloat DiV4dCrossProduct2D(const DiV4d *vpVect1, const DiV4d *vpVect2);
diINLINE DiVoid DiV4dNormalize(const DiV4d *vpIn, DiV4d *vpOut);
diINLINE DiFloat DiV4dNormalizeExt(const DiV4d *vpIn, DiV4d *vpOut);
diINLINE DiFloat DiV4dLength(const DiV4d *vpVect);
diINLINE DiVoid  DiV4dMakeUnit(DiV4d *vpVect);
diINLINE DiVoid  DiV3dMakeUnit(DiV3d *vpVect);
diINLINE DiVoid DiV4dSetLength(const DiV4d *vpIn, const DiFloat rLen, DiV4d *vpOut);
diINLINE DiFloat DiV4dPointDistance2(const DiV4d *vpP0, const DiV4d *vpP1);
diINLINE DiFloat DiV4dLength2D(const DiV4d *vpVect) // todo optimize
{
  return DiV3dLength2D((const DiV3d *)vpVect);
}

// *******************************************************************
// inlines

///eugbelNSCENE///} // end of namespace NScene

#include "DiV2d.inl"
#include "DiV3d.inl"
#include "DiV4d.inl"

#endif /* DIVECTOR_H */
