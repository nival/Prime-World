#pragma once

namespace NCore
{
	_interface IBaseFSMState
		: public IObjectBase
	{
		virtual void Init() = 0;
		virtual IBaseFSMState* Step(float dt) = 0;
		virtual const int GetTypeId() const = 0;
	};
}

template<> NCore::IBaseFSMState* GetInvalid();
