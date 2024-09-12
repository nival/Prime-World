#pragma once

#include "DefaultScreenBase.h"

namespace NScene
{
  _interface IScene;
}

namespace NMainLoop 
{

class AdventureScreenBaseClient : public DefaultScreenBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( AdventureScreenBaseClient, DefaultScreenBase );

public:
  virtual NScene::IScene * GetScene() const = 0;
};

}  //namespace NMainLoop 