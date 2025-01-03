#pragma once

namespace GameBalancer
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
  uint ICCUCounter::inccu()
  {
    return ++ccu_;
  }

  inline
  uint ICCUCounter::deccu()
  {
    NI_ASSERT(ccu_ > 0, "");
    return --ccu_;
  }
}
