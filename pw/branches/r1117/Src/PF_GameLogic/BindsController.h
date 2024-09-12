#pragma once

namespace NGameX
{
  class BindsController : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( BindsController, BaseObjectST );
  public: 
    enum BindType
    {
      None = 0,
      Chat = 1,
      ReportWindow = 2,
      EscMenu = 4,
      Lua = 8
    }; 

    BindsController();
    ~BindsController(){};

    void SetEnabled(BindType type , bool enableBinds);
  private:
    bool IsFlagEnabled(BindType type);

    int currentEnabledFlags;
  };
}
