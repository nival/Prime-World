#pragma once

#include "PFWorldObjectBase.h"

namespace NWorld
{
  using NCore::ProtectionResult;

  class PFWorldProtection
    : public PFWorldObjectBase
    , public NonCopyable
  {
    DONOT_REGISTER_SAVELOAD_CLASS
    OBJECT_METHODS(0x15C5DC00, PFWorldProtection)
  public:
    STARFORCE_EXPORT static CObj<PFWorldProtection> Create(PFWorld* const world);

    virtual ~PFWorldProtection() {}

    virtual void Update() {}
    virtual bool IsOK() const { return true; }

    virtual bool PopResult(ProtectionResult& result) { return false; }
    virtual void SetUpdateFrequency(const int offset, const int frequency) {}
  protected:
    explicit PFWorldProtection(PFWorld* const world)
      : PFWorldObjectBase(world, 0)
    {
    }

    PFWorldProtection() {}
  private:
    ZDATA_(PFWorldObjectBase)
    ZNOPARENT(NonCopyable)
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); return 0; }
  };
}
