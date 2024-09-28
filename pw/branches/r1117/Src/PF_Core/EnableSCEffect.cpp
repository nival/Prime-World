#include "stdafx.h"
#include "EnableSCEffect.h"

namespace PF_Core
{

void EnableSCEffect::Apply(CPtr<ClientObjectBase> const &pUnit_)
{
  NI_ASSERT(!IsValid(pUnit), "effect already applied");

  pUnit = pUnit_;

	if ( IsValid(pUnit) )
	{  
		NDb::EnableSCEffect const& dbEffect = GetDBEffect();
	  
		if ( !dbEffect.nameStart.empty() )
		{
			switch( dbEffect.mode )
			{
			case NDb::NABLESCEFFECTMODE_COMPONENTID:
				{
					if ( !dbEffect.nameStart.empty() )
					{
						pUnit->EnableById( dbEffect.nameStart, dbEffect.enable );
					}
				}
				break;
			case NDb::NABLESCEFFECTMODE_EVENTNAME:
				{
					pUnit->ProcessExternalEvent( dbEffect.nameStart.c_str() );
				}
				break;
			}
		}
	}
}

void EnableSCEffect::Die()
{
	if ( IsValid(pUnit) )
	{  
		NDb::EnableSCEffect const& dbEffect = GetDBEffect();

		if ( !dbEffect.nameStop.empty() )
		{
			switch( dbEffect.mode )
			{
			case NDb::NABLESCEFFECTMODE_COMPONENTID:
				{
					pUnit->EnableById( dbEffect.nameStop, !dbEffect.enable );
				}
				break;
			case NDb::NABLESCEFFECTMODE_EVENTNAME:
				{
					pUnit->ProcessExternalEvent( dbEffect.nameStop.c_str() );
				}
				break;
			}
		}
	}
  pUnit = 0;

  BasicEffect::Die();
}

void EnableSCEffect::DieImmediate()
{
  pUnit = 0;

  EffectBase::DieImmediate();
}

}
