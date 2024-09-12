#pragma once

#include "stdafx.h"
#include "PFClientBaseUnit.h"
#include "PFAuraEffect.h"

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAuraEffect::Apply(CPtr<PF_Core::ClientObjectBase> const &pObject)
{
	pUnit = dynamic_cast<PFClientBaseUnit*>(pObject.GetPtr());
	NI_DATA_VERIFY(pUnit,
								 NStr::StrFmt("Effect %s could be applied on base unit onlu", GetDBEffect().GetDBID().GetFileName().c_str()), 
								 return; );
	pUnit->AcknowledgeAuraChange(GetDBEffect().type == NDb::AURATYPE_ALLY, true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAuraEffect::Die()
{
	if ( IsValid( pUnit ) )
	{
		pUnit->AcknowledgeAuraChange(GetDBEffect().type == NDb::AURATYPE_ALLY, false);
	}

  BasicEffect::Die();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAuraEffect::DieImmediate()
{
  pUnit = 0;

  BasicEffect::DieImmediate();
}

}