/*
 *@file    DiMatrix.h
 *@memo    matrix functions
 *@author  BVS + (Miron)
 *@date    25.11.97 
 *@prefix  DiMatrix
 *@header  DiMatrix.h
 *@library Common.lib
 */

#ifndef _DIMATRIX_H_
#define _DIMATRIX_H_

// *******************************************************************
// includes

#include "DiTypes.h"
#include "DiVector.h"

///eugbelNSCENE///namespace NScene {


// *******************************************************************
// defines

#define diMATRIX_DEFAULTNUMMATRICES 16

#ifdef DIDEBUG
  #define diMATRIX_NEW_MODE_TEST
#endif

#define diDECLARE_MATRIX(var) diDECLARE(DiMatrix, var, 16)

// *******************************************************************
// types

// Structure for matrix
typedef struct tagDiMatrix
{
  DiV4d     vRight;
  DiV4d     vUp;
  DiV4d     vAt;
  DiV4d     vPos;
} DiMatrix;

typedef DiV4d DiQuaternion;

// Matrix interpolation
typedef struct tagDiMatrixInterpolationData
{
  // Matrices
  DiQuaternion  qtCurQuat;
  DiQuaternion  qtPrevQuat;
  // Linear
  DiV4d         vPosDelta;
  DiV4d         vPrevPos;
} DiMatrixInterpolationData;

/**
 *This struct is used to pass open params
 *to the matrix subsystem
 *
 *@memo    Matrix subsystem params
 *@member  nMaxNumMatrices maximal matrices count available (through DiMatrixCreate)
 *@header  DiMatrix.h
 *@author  Gandy
*/
typedef struct tagDiMatrixOpenParams
{
  // maximal number of matrices created 
  // through the DiMatrixCreate
  DiInt32   nMaxNumMatrices;
} DiMatrixOpenParams;

// *******************************************************************
// defines one more
/**
 *This macro initalizes matrix.
 *@memo     Initalize matrix
 *@param    m      matrix
 *@param    t      init type
 *@header   DiMatrix.h
 */
#define DiMatrixInitialize(m)       \
{                                   \
  DiMemSet(m, 0, sizeof(DiMatrix)); \
}

 /**
 *This macro access one element of the matrix: vRight 'x' component
 *@memo     Access x component of vRight
 *@return   x component of vRight
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetRightX(mpMat)    ((mpMat)->vRight.x)
/**
 *This macro access one element of the matrix: vRight 'y' component
 *@memo     Access y component of vRight
 *@return   y component of vRight
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetRightY(mpMat)    ((mpMat)->vRight.y)
/**
 *This macro access one element of the matrix: vRight 'z' component
 *@memo     Access z component of vRight
 *@return   z component of vRight
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetRightZ(mpMat)    ((mpMat)->vRight.z)

/**
 *This macro access one element of the matrix: vUp 'x' component
 *@memo     Access x component of vUp
 *@return   x component of vUp
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetUpX(mpMat)       ((mpMat)->vUp.x)
/**
 *This macro access one element of the matrix: vUp 'y' component
 *@memo     Access y component of vUp
 *@return   y component of vUp
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetUpY(mpMat)       ((mpMat)->vUp.y)
/**
 *This macro access one element of the matrix: vUp 'z' component
 *@memo     Access z component of vUp
 *@return   z component of vUp
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetUpZ(mpMat)       ((mpMat)->vUp.z)

/**
 *This macro access one element of the matrix: vAt 'x' component
 *@memo     Access x component of vAt
 *@return   x component of vAt
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetAtX(mpMat)       ((mpMat)->vAt.x)
/**
 *This macro access one element of the matrix: vAt 'y' component
 *@memo     Access y component of vAt
 *@return   y component of vAt
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetAtY(mpMat)       ((mpMat)->vAt.y)
/**
 *This macro access one element of the matrix: vAt 'z' component
 *@memo     Access z component of vAt
 *@return   z component of vAt
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetAtZ(mpMat)       ((mpMat)->vAt.z)

/**
 *This macro access one element of the matrix: vPos 'x' component
 *@memo     Access x component of vPos
 *@return   x component of vPos
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetPosX(mpMat)      ((mpMat)->vPos.x)
/**
 *This macro access one element of the matrix: vPos 'y' component
 *@memo     Access y component of vPos
 *@return   y component of vPos
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetPosY(mpMat)      ((mpMat)->vPos.y)
/**
 *This macro access one element of the matrix: vPos 'z' component
 *@memo     Access z component of vPos
 *@return   z component of vPos
 *@param    mpMat      matrix
 *@header   DiMatrix.h
 */
#define     DiMatrixGetPosZ(mpMat)      ((mpMat)->vPos.z)

/**
 *This macro access one element of the matrix: set 'x' component of vRight
 *@memo     Set x component of vRight
 *@return   new x component of vRight
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetRightX(mpMat,v)  ((mpMat)->vRight.x=(v))
/**
 *This macro access one element of the matrix: set 'y' component of vRight
 *@memo     Set y component of vRight
 *@return   new y component of vRight
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetRightY(mpMat,v)  ((mpMat)->vRight.y=(v))
/**
 *This macro access one element of the matrix: set 'z' component of vRight
 *@memo     Set z component of vRight
 *@return   new z component of vRight
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetRightZ(mpMat,v)  ((mpMat)->vRight.z=(v))

/**
 *This macro access one element of the matrix: set 'x' component of vUp
 *@memo     Set x component of vUp
 *@return   new x component of vUp
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetUpX(mpMat,v)     ((mpMat)->vUp.x=(v))
/**
 *This macro access one element of the matrix: set 'y' component of vUp
 *@memo     Set y component of vUp
 *@return   new y component of vUp
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetUpY(mpMat,v)     ((mpMat)->vUp.y=(v))
/**
 *This macro access one element of the matrix: set 'z' component of vUp
 *@memo     Set z component of vUp
 *@return   new z component of vUp
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetUpZ(mpMat,v)     ((mpMat)->vUp.z=(v))

/**
 *This macro access one element of the matrix: set 'x' component of vAt
 *@memo     Set x component of vAt
 *@return   new x component of vAt
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetAtX(mpMat,v)     ((mpMat)->vAt.x=(v))
/**
 *This macro access one element of the matrix: set 'y' component of vAt
 *@memo     Set y component of vAt
 *@return   new y component of vAt
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetAtY(mpMat,v)     ((mpMat)->vAt.y=(v))
/**
 *This macro access one element of the matrix: set 'z' component of vAt
 *@memo     Set z component of vAt
 *@return   new z component of vAt
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetAtZ(mpMat,v)     ((mpMat)->vAt.z=(v))

/**
 *This macro access one element of the matrix: set 'x' component of vPos
 *@memo     Set x component of vPos
 *@return   new x component of vPos
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetPosX(mpMat,v)    ((mpMat)->vPos.x=(v))
/**
 *This macro access one element of the matrix: set 'y' component of vPos
 *@memo     Set y component of vPos
 *@return   new y component of vPos
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetPosY(mpMat,v)    ((mpMat)->vPos.y=(v))
/**
 *This macro access one element of the matrix: set 'z' component of vPos
 *@memo     Set z component of vPos
 *@return   new z component of vPos
 *@param    mpMat     [in/out] matrix
 *@param    v         [in] new component value
 *@header   DiMatrix.h
 */
#define     DiMatrixSetPosZ(mpMat,v)    ((mpMat)->vPos.z=(v))

/**
 *This macro gets vector vUp from mpMat
 *@memo     Get vector vUp from mpMat
 *@param    mpMat     [in] matrix
 *@param    v         [out] output vector
 *@header   DiMatrix.h
 */
#define DiMatrixGetUp(mpMat,v) \
   (v)->x = (mpMat)->vUp.x;   \
   (v)->y = (mpMat)->vUp.y;   \
   (v)->z = (mpMat)->vUp.z

/**
 *This macro gets vector vAt from mpMat
 *@memo     Get vector vAt from mpMat
 *@param    mpMat     [in] matrix
 *@param    v         [out] output vector
 *@header   DiMatrix.h
 */
#define DiMatrixGetAt(mpMat,v) \
   (v)->x = (mpMat)->vAt.x;    \
   (v)->y = (mpMat)->vAt.y;    \
   (v)->z = (mpMat)->vAt.z

/**
 *This macro gets vector vRight from mpMat
 *@memo     Get vector vRight from mpMat
 *@param    mpMat     [in] matrix
 *@param    v         [out] output vector
 *@header   DiMatrix.h
 */
#define DiMatrixGetRight(mpMat,v) \
   (v)->x = (mpMat)->vRight.x;    \
   (v)->y = (mpMat)->vRight.y;    \
   (v)->z = (mpMat)->vRight.z

/**
 *This macro gets vector vPos from mpMat
 *@memo     Get vector vPos from mpMat
 *@param    mpMat     [in] matrix
 *@param    v         [out] output vector
 *@header   DiMatrix.h
 */
#define DiMatrixGetPos(mpMat,v) \
   (v)->x = (mpMat)->vPos.x;    \
   (v)->y = (mpMat)->vPos.y;    \
   (v)->z = (mpMat)->vPos.z

/**
 *This macro sets vector vUp in mpMat and sets 'dirty' and 'not rotate identity' flags
 *@memo     Set vector vUp from mpMat
 *@param    mpMat     [out] matrix
 *@param    v         [in] vector to set as vUp
 *@header   DiMatrix.h
 */
#define DiMatrixSetUpOnly(mpMat,v) \
   (mpMat)->vUp.x = (v)->x;    \
   (mpMat)->vUp.y = (v)->y;    \
   (mpMat)->vUp.z = (v)->z;    \

/**
 *This macro sets vector vAt in mpMat and sets 'dirty' and 'not rotate identity' flags
 *@memo     Set vector vAt from mpMat
 *@param    mpMat     [out] matrix
 *@param    v         [in] vector to set as vAt
 *@header   DiMatrix.h
 */
#define DiMatrixSetAtOnly(mpMat,v) \
   (mpMat)->vAt.x = (v)->x;    \
   (mpMat)->vAt.y = (v)->y;    \
   (mpMat)->vAt.z = (v)->z;    \

/**
 *This macro sets vector vRight in mpMat and sets 'dirty' and 'not rotate identity' flags
 *@memo     Set vector vRight from mpMat
 *@param    mpMat     [out] matrix
 *@param    v         [in] vector to set as vRight
 *@header   DiMatrix.h
 */
#define DiMatrixSetRightOnly(mpMat,v) \
   (mpMat)->vRight.x = (v)->x;    \
   (mpMat)->vRight.y = (v)->y;    \
   (mpMat)->vRight.z = (v)->z;    \

/**
 *This macro sets vector vPos in mpMat and sets 'dirty' and 'not rotate identity' flags
 *@memo     Set vector vPos from mpMat
 *@param    mpMat     [out] matrix
 *@param    v         [in] vector to set as vPos
 *@header   DiMatrix.h
 */
#define DiMatrixSetPos(mpMat,v) \
   (mpMat)->vPos.x = (v)->x;    \
   (mpMat)->vPos.y = (v)->y;    \
   (mpMat)->vPos.z = (v)->z;    \

// *******************************************************************
// functions prototypes
diINLINE DiVoid DiMatrixCopy(const DiMatrix *mpSrc, DiMatrix *mpDst);
diINLINE DiVoid DiMatrixMultiply(const DiMatrix *mpA, const DiMatrix *mpB, DiMatrix *mpOut);

#ifdef __cplusplus
extern "C" {
#endif  /*__cplusplus */

extern  DiMatrix   *DiMatrixCreate(DiVoid);
extern  DiBool     DiMatrixDestroy(DiMatrix **mppMat);

extern  DiVoid     DiMatrixIdentity(DiMatrix *mpM);
extern  DiVoid     DiMatrixRotateIdentity(DiMatrix *mpM);

extern  DiVoid     DiMatrixAdd(const DiMatrix *mpSrc1, const DiMatrix *mpSrc2, DiMatrix *mpDst);
extern  DiVoid     DiMatrixSubtract(const DiMatrix *mpSrc1, const DiMatrix *mpSrc2, DiMatrix *mpDst);
extern  DiVoid     DiMatrixScale(DiMatrix *mpMat, DiV4d *vpScale, DiOpCombainType nOperation);
extern  DiVoid     DiMatrixTranslate(DiMatrix *mpMat, DiV4d *vpTran, DiOpCombainType nOperation);

extern  DiVoid     DiMatrixRotateAt(DiMatrix *mpMat, DiFloat rAngle, DiOpCombainType nOperation);
extern  DiVoid     DiMatrixRotateAtSinCosLeft(DiMatrix *mpMat, DiFloat rSin, DiFloat rCos, DiOpCombainType nOperation);
extern  DiVoid     DiMatrixRotateRight(DiMatrix *mpMat, DiFloat rAngle, DiOpCombainType nOperation);
extern  DiVoid     DiMatrixRotateRightSinCos(DiMatrix *mpMat,DiFloat rSin, DiFloat rCos, DiOpCombainType nOperation);
extern  DiVoid     DiMatrixRotateUp(DiMatrix *mpMat, DiFloat rAngle, DiOpCombainType nOperation);
extern  DiVoid     DiMatrixRotateUpSinCosLeft(DiMatrix *mpMat,DiFloat rSin, DiFloat rCos, DiOpCombainType nOperation);

#define            DiMatrixRotateUpSinCosRight(a, b, c, d)  DiMatrixRotateUpSinCosLeft((a), -(b), (c), (d))
#define            DiMatrixRotateUpSinCos(a, b, c, d)  DiMatrixRotateUpSinCosLeft((a), (b), (c), (d))
#define            DiMatrixRotateAtSinCosRight(a, b, c, d)  DiMatrixRotateAtSinCosLeft((a), -(b), (c), (d))
#define            DiMatrixRotateAtSinCos(a, b, c, d)  DiMatrixRotateAtSinCosLeft((a), (b), (c), (d))

extern  DiVoid     DiMatrixInitWithAt(DiMatrix *mpMat, const DiV4d *vpAt);
extern  DiVoid     DiMatrixInitWithRight(DiMatrix *mpMat, const DiV4d *vpRight);
extern  DiVoid     DiMatrixInitWithUp(DiMatrix *mpMat, const DiV4d *vpUp);

extern  DiVoid     DiMatrixOrtoNormalizeVectSys(DiV4d  *vpMain,
                                                DiV4d  *vpSub1,
                                                DiV4d  *vpSub2,
                                                DiBool bLeftRight);

extern  DiVoid     DiMatrixSetAt(DiMatrix *mpMat, DiV4d const *vpAt);
extern  DiVoid     DiMatrixSetRight(DiMatrix *mpMat, DiV4d const *vpRight);
extern  DiVoid     DiMatrixSetUp(DiMatrix *mpMat, DiV4d const *vpUp);

extern  DiBool     DiMatrixInvert(const DiMatrix *mpIn, DiMatrix *mpOut);
extern  DiBool     DiMatrixTransform(DiMatrix *mpDst, DiMatrix *mpSrc, DiInt32 op);
extern  DiVoid     DiMatrixBuildRotation(DiV4d *vpRotAbout, DiFloat rA, DiMatrix *mpDest);
extern  DiVoid     DiMatrixRotate(DiMatrix *mpSrc, DiV4d const *vpRotAbout, DiFloat rA, DiOpCombainType op);
extern  DiVoid     DiMatrixTransposeRotationalSubmatrix(const DiMatrix *mpMatSrc, DiMatrix *mpMatDst);

extern  DiBool      DiMatrixEulerDecomposeXYZ(
                                                DiMatrix  *matrix,
                                                DiFloat   *angleX,
                                                DiFloat   *angleY,
                                                DiFloat   *angleZ
                                             );


extern  DiVoid     DiMatrixBuildInterpolationData(DiMatrix *mpCurMatrix, DiMatrix *mpPrevMatrix,
                                                  DiMatrixInterpolationData *midpData);
extern  DiVoid     DiMatrixBuildInterpolated(DiMatrixInterpolationData *midpData, DiFloat rT,
                                             DiMatrix *mpNewMatrix);

extern  DiBool     DiMatrixIsMatrixOrtoNormalized(DiMatrix *mpMat);

diINLINE DiVoid DiMatrixOrtonormalize(DiMatrix *mpMat)
{
  DiV4dMakeUnit(&mpMat->vAt);
  DiV4dCrossProduct(&mpMat->vAt, &mpMat->vRight, &mpMat->vUp);
  DiV4dMakeUnit(&mpMat->vUp);
  DiV4dCrossProduct(&mpMat->vUp, &mpMat->vAt, &mpMat->vRight);
}

extern  DiBool     DiMatrixSystemOpen(DiMatrixOpenParams *mpParams);
extern  DiBool     DiMatrixSystemClose(DiVoid);

#ifdef DIDEBUG
/**
 *This macro checks matrix integrity
 *<br><B>NOTE:</B> Works only in DEBUG compilation, otherwize do nothing
 *@memo     Check matrix integrity
 *@return   TRUE if matrix pos identity, FALSE otherwize
 *@param    mpM      matrix
 *@header   DiMatrix.h
 *@see      DiMatrixIntergrityTest
 *@see      DIDEBUG define
 */
  extern DiVoid DiMatrixTestIntegrity(const DiMatrix *mpMatrix);
#else
  #define DiMatrixTestIntegrity(mpM)
#endif DIDEBUG

#ifdef __cplusplus
}
#endif // ifdef __cplusplus

// *******************************************************************
// inlines
///eugbelNSCENE///} // end of namespace NScene


#include "DiM4d.inl"

#endif // ifndef _DIMATRIX_H_
