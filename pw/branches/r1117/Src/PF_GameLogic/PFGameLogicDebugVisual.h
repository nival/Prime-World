#pragma once

#include "PFBaseUnit.h"

namespace NWorld
{

void InitLogicDebugManager();
void DeinitLogicDebugManager();

void DebugShowScreamEffect( const CPtr<PFBaseUnit>& pSender, const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st );
void DebugShowAttackEffect( const CPtr<PFBaseUnit>& pUnit, const CPtr<PFBaseUnit>& pTarget, float revisionTimeOffset );

}//namespace NWorld