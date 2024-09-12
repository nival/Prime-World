#include "StdAfx.h"
#include "ErrorMessageController.h"

#include "AdventureFlashInterface.h"
#include "DBStats.h"

namespace NGameX
{

ErrorMessageController::ErrorMessageController( AdventureFlashInterface * _flashInterface, NDb::Ptr<NDb::DBUIData> dbUIData )
: flashInterface(_flashInterface)
{
  NI_VERIFY(IsValid(dbUIData) && flashInterface, "invalid ui data", return);
  for (int i=0; i< dbUIData->errorMessageDescriptions.size(); i++)
  {
    const NDb::ErrorMessageDescription & desc = dbUIData->errorMessageDescriptions[i];
    flashInterface->SetErrorMessage((NDb::EErrorMessageType)i, desc.textMessage.GetText(), desc.shouldPlaySound, desc.lifeTime);
  }
}

}