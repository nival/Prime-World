/*
 * @file    DiMatrix.c
 * @memo    PC optimized matrix operations
 * @author  Vlad
 * @date    28.05.2001
 * @prefix  DiMatrix
 * @header  DiMatrix.h
 * @library Common.lib
 */

// *******************************************************************
// functions

#include "DiTypes.h"

///eugbelNSCENE///namespace NScene {


//#ifdef __GNUC__
//  #include "../../source/common/math/_diMatOld.h"
//#else
//  #include "../source/common/math/_diMatOld.h"
//#endif

// *******************************************************************
// defines

// *******************************************************************
// local data

// *******************************************************************
// functions

/**
 * This function is used to copy matrices
 *
 * @memo    Copy matrices
 * @return  none
 * @param   mpSrc source matrix [in]
 * @param   mpDst dest matrix [out]
 * @header  DiMatrix.h
 * @library Common.lib
 * @author  Vlad
 * @see     
 */

DiVoid DiMatrixCopy(const DiMatrix *mpSrc, DiMatrix *mpDst)
{
  DIFUNCTION("DiMatrixCopy");
  DIASSERT(mpSrc);
  DIASSERT(mpDst);

  // Alignment check
//  DIASSERT( !((DiUInt32)(mpSrc) & 15) );
  // Alignment check
  DIASSERT( !((DiUInt32)(mpDst) & 15) );
  
  // copy matrix
  *mpDst = *mpSrc;

  DIRETURNVOID();
} // end of DiMatrixCopy

/**
 * This function is used to multiply given matrices
 *
 * @memo    Multiply given matrices
 * @return  none
 * @param   mpA   matrix [in]
 * @param   mpB   matrix [in]
 * @param   mpOut matrix [out]
 * @header  DiMatrix.h
 * @library Common.lib
 * @author  Gandy
 * @see     
 */
DiVoid  DiMatrixMultiply(const DiMatrix *mpA, const DiMatrix *mpB, DiMatrix *mpOut)
{
  DiInt32     nI;
  const DiV4d *vpSrcVector;
  DiV4d       *vpDstVector;

  DIFUNCTION("DiMatrixMultiply");

  vpSrcVector = &(mpA->vRight);
  vpDstVector = &(mpOut->vRight);
  //test
  DiMatrixTestIntegrity(mpA);
  DiMatrixTestIntegrity(mpB);
  // Alignment check
  DIASSERT( !((DiUInt32)(mpOut) & 15) );


  for (nI = 0; nI < 4; nI++)
  {
    vpDstVector->x = vpSrcVector->x * mpB->vRight.x +
                     vpSrcVector->y * mpB->vUp.x +
                     vpSrcVector->z * mpB->vAt.x +
                     vpSrcVector->w * mpB->vPos.x;

    vpDstVector->y = vpSrcVector->x * mpB->vRight.y +
                     vpSrcVector->y * mpB->vUp.y +
                     vpSrcVector->z * mpB->vAt.y +
                     vpSrcVector->w * mpB->vPos.y;

    vpDstVector->z = vpSrcVector->x * mpB->vRight.z +
                     vpSrcVector->y * mpB->vUp.z +
                     vpSrcVector->z * mpB->vAt.z +
                     vpSrcVector->w * mpB->vPos.z;

    vpDstVector->w = vpSrcVector->x * mpB->vRight.w +
                     vpSrcVector->y * mpB->vUp.w +
                     vpSrcVector->z * mpB->vAt.w +
                     vpSrcVector->w * mpB->vPos.w;
    vpSrcVector++;
    vpDstVector++;
  }
  DIRETURNVOID();
} // end of DiMatrixMultiply

///eugbelNSCENE///} // end of namespace NScene


// END
