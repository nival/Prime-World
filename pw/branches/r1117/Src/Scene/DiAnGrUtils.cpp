/*
* @file    DiAnGrUtils.h
* @memo    Macroses, special functions, stubs to like AnimGraph into Nival engine
* @author  EugBel
* @date    05.11.2008
* @prefix  DiAn, DiAnGr

*/

// *******************************************************************
// includes
#include "stdafx.h"

#include "DiAnGrUtils.h"

///eugbelNSCENE///namespace NScene {

#define diALSIDE_NA    3
#define diALSIDE_LEFT  2
#define diALSIDE_RIGHT 1


/*
* @memo    Solve equation
* @return  Root like number
* @param   sppPars - solver parameters
* @param   fp - user function
* @param   vp - user parametr to pass
* @author  Earnol
* @see     Nothing
*/
DiFloat DiAlSolveEquationIntectionally(DiAlSolveEquationParams *sppPars, DiAlParamEquation fp, DiVoid *vp, const nstl::string& dbfilename)
{
  DiFloat rRootVal;
  DiInt32 nMaxTrys;
  DiFloat rTry(0.0f);
  DiFloat rTryVal(0.0f);
  DiBool  nSide = diALSIDE_NA;
  DiFloat rRootFrom(0.0f), rRootTo(0.0f);
  DiFloat rCurStep;
  DiInt32 nI;
  DiFloat rLeftVal(0.0f), rRightVal(0.0f);

  DIFUNCTION("DiAlSolveEquationIntectionally");

#ifndef Sb
#define Sb(f)             (*((DiSplitBits*)(&(f))))
#endif

  nMaxTrys = DiF2L((sppPars->rTo - sppPars->rFrom) / sppPars->rStep);
  DIASSERT(nMaxTrys > 0);

  rRootVal = fp(sppPars->rGuessRoot, vp) - sppPars->rY;
  if(DiFAbs(rRootVal) < sppPars->rAccuracy)
  {
    DIRETURN(sppPars->rGuessRoot);
  }
  //find where the root is loacated
  for(nI = 1; nI <= nMaxTrys; nI++)
  {
    //try right step
    rTry = sppPars->rGuessRoot + nI * sppPars->rStep;
    rTry = DiFMin(sppPars->rTo, rTry);
    rTryVal = fp(rTry, vp) - sppPars->rY;
    if(rTryVal == 0.0f)
    {
      DIRETURN(rTry);
    }
    if(DI_SB_OF_DIFFERENT_SIGN(Sb(rRootVal), Sb(rTryVal)))
    {
      nSide = diALSIDE_RIGHT;
      break;
    }
    //try left step
    rTry = sppPars->rGuessRoot - nI * sppPars->rStep;
    rTry = DiFMax(sppPars->rFrom, rTry);
    rTryVal = fp(rTry, vp) - sppPars->rY;
    if(rTryVal == 0.0f)
    {
      DIRETURN(rTry);
    }
    if(DI_SB_OF_DIFFERENT_SIGN(Sb(rRootVal), Sb(rTryVal)))
    {
      nSide = diALSIDE_LEFT;
      break;
    }
  }

  if(nSide == diALSIDE_RIGHT)
  {
    rRootFrom = DiFMin(sppPars->rTo, sppPars->rGuessRoot + (nI - 1) * sppPars->rStep);
    rRootTo   = rTry;
    rLeftVal  = fp(rRootFrom, vp) - sppPars->rY;
    rRightVal = rTryVal;
  }
  else if(nSide == diALSIDE_LEFT)
  {
    rRootFrom = rTry;
    rRootTo   = DiFMax(sppPars->rFrom, sppPars->rGuessRoot - (nI - 1) * sppPars->rStep);
    rLeftVal  = rTryVal;
    rRightVal = fp(rRootTo, vp) - sppPars->rY;
  }
  else
  {
    DIASSERT_ALOOF_CODE(dbfilename);
  }
  //no we know that root somewhere in [rRootFro; rRootTo]

  do
  {
    rCurStep = (rRootTo - rRootFrom) * 0.5f;
    rTry = rCurStep + rRootFrom;
    rTryVal = fp(rTry, vp) - sppPars->rY;
    if(rTryVal == 0.0f)
    {
      DIRETURN(rTry);
    }
    if(DI_SB_OF_DIFFERENT_SIGN(Sb(rLeftVal), Sb(rTryVal)))
    {
      rRightVal = rTryVal;
      rRootTo   = rTry;
    }
    else
    {
      rLeftVal   = rTryVal;
      rRootFrom  = rTry;
    }
  } while(rCurStep > sppPars->rAccuracy);

  DIRETURN((rRootFrom + rRootTo) * 0.5f);
} // end of DiAlSolveEquationIntectionally

///eugbelNSCENE///} // end of namespace NScene