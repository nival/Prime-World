#include "stdafx.h"
#include "BaseState.h"

using namespace NCore;
BASIC_REGISTER_CLASS( IBaseFSMState )

template<> NCore::IBaseFSMState* GetInvalid()
{
	class CEmptyObject 
		: public NCore::IBaseFSMState
		, public CObjectBase
	{
		OBJECT_METHODS( 0x104B4D00, CEmptyObject )

	public:
		virtual void Init() {}
		virtual NCore::IBaseFSMState *Step(float) { return 0; }
	};
	//
	static CEmptyObject emptyObj;
	return &emptyObj;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
