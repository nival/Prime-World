#pragma once

namespace NCore
{
	_interface IBaseFSMState;

	class CFSMBase : public CObjectBase
	{
		CObj<IBaseFSMState> pCurrentState;

	protected:
		virtual void SetState( IBaseFSMState *pNewState );

	public:
		CFSMBase();
		virtual void Step(float dt);
    IBaseFSMState *GetCurrentState() 
    {
      return pCurrentState;
    }
	};
}
