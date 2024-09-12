#pragma once


namespace NDb
{
  struct DBUIData;
}

namespace NGameX
{
  class AdventureFlashInterface;

  class ErrorMessageController : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( ErrorMessageController, BaseObjectST );

  public:
    ErrorMessageController(AdventureFlashInterface * _flashInterface, NDb::Ptr<NDb::DBUIData> dbUIData);
    
    void SetErrorMessage(NDb::EErrorMessageType msgType);

  private:
    Weak<AdventureFlashInterface> flashInterface;
  };

} //namespace NGameX
