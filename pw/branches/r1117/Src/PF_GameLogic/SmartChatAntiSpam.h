#pragma once

namespace NGameX
{
  _interface ISmartChatAntiSpam : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1(ISmartChatAntiSpam, IBaseInterfaceST);

    virtual bool UseSmartChat() = 0;
  };
}
