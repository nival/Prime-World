#pragma once

#include "PFWorld.h"
#include "PFClientObjectBase.h"
#include "../PF_Core/WorldObject.h"

#define DebugTraceWithWorldStep(...) DebugTrace( ( "%s", NWorld::BuildFormattedStringWithStep( __VA_ARGS__ ) ) )

namespace NWorld
{
	class PFWorldObjectBase : public PF_Core::WorldObjectBase
	{
		WORLD_OBJECT_CLIENT(PFClientObjectBase)
	
	public:
		PFWorldObjectBase(PFWorld* pWorld, int realWObj, bool immediately = false) : PF_Core::WorldObjectBase(pWorld, realWObj, immediately)
		{
			if ( realWObj == 1 )
				NI_VERIFY(GetWorld(), "Invalid world object!", ; );
		}

    PFWorld*       GetWorld() {return static_cast<PFWorld*>(PF_Core::WorldObjectBase::GetWorld());}
    PFWorld const* GetWorld() const {return static_cast<PFWorld const*>(PF_Core::WorldObjectBase::GetWorld());}

    virtual void Hide(bool hide) {};
	
  protected:
		explicit PFWorldObjectBase() {}
		
    ZDATA_(PF_Core::WorldObjectBase)
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); return 0; }
	};

  const char* BuildFormattedStringWithStep( const PFWorldObjectBase* pWo, const char* format, ... );

} // namespace NWorld 
