#pragma once


namespace flash
{
  _interface IStageFocusHandler: public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1( IStageFocusHandler, IBaseInterfaceST )

    virtual void OnStageFocusGain() = 0;
  };
}


