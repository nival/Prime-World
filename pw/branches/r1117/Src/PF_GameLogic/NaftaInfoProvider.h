#pragma once

namespace NGameX
{
  _interface INaftaInfoProvider: public IObjectBase
  {
    virtual int GetNaftaAmount() = 0;
  };
}