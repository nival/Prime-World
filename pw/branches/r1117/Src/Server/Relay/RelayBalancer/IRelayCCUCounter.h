#pragma once

namespace Relay
{
  class ICCUCounter : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( ICCUCounter, IBaseInterfaceMT );

  public:
    ICCUCounter()
      :ccu_(0)
    {};

    ~ICCUCounter() {};

  public:
    uint ccu() const;
    void ccu(uint _ccu);
    uint inccu();
    uint deccu();

  private:
    uint ccu_;
  };

  inline
  uint ICCUCounter::ccu() const
  {
    return ccu_;
  }

  inline
  void ICCUCounter::ccu(uint _ccu)
  {
    ccu_ = _ccu;
  }

  inline
  uint ICCUCounter::inccu()
  {
    return ++ccu_;
  }

  inline
  uint ICCUCounter::deccu()
  {
    NI_ASSERT(ccu_ > 0, "");
    if (ccu_ > 0)
      --ccu_;

    return ccu_;
  }
}
