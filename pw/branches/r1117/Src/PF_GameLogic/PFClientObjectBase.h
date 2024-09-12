#pragma once 

#include "../PF_Core/ClientObject.h"

namespace NDb 
{
	struct AdvMapObject; 
}

namespace NScene 
{ 
	_interface IScene; 
}

namespace NWorld
{	
	class PFClientObjectBase : public PF_Core::ClientObjectBase
	{
	public:
		PFClientObjectBase() {}
		PFClientObjectBase(const CPtr<PF_Core::WorldObjectBase> &pWO) : PF_Core::ClientObjectBase(pWO) {}
	};
}