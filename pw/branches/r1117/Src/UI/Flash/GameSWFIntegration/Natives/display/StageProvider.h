#pragma once

namespace flash
{

_interface IStageProvider : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IStageProvider, IBaseInterfaceST );

  virtual int GetStageWidth() const = 0;
  virtual int GetStageHeight() const = 0;

  virtual void Invalidate() = 0;
};

} // namespace flash