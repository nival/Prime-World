#pragma once

namespace gamechat
{
  struct ChatMessage;

  class IClient;
}

namespace NGameX
{
  class IChatMessageHook : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1(IChatMessageHook, IBaseInterfaceST)
  public:
    virtual bool MessageReceived(gamechat::ChatMessage& message) = 0;
  };
}
