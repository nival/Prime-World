/*
* FormulaExecutor.cpp
*
*  Created on: 19.01.2009
*      Author: earnol
*/

#include "stdafx.h"

#include "FormulaExecutor.h"
#include "System/Base64.h"
#include "stdafx.h"

FormulaExecutor::FormulaExecutor(char const *cpBase64String): DataExecutor(FORMULA_VERSION, cpBase64String)
{
}

FormulaExecutor::FormulaExecutor(unsigned char const *dataBuffer, unsigned int nBufferSize): DataExecutor(FORMULA_VERSION, dataBuffer, nBufferSize)
{
}


//REGISTER_SAVELOAD_CLASS( FormulaExecutor )
