#pragma once

namespace NGameX
{
#pragma warning(push)
#pragma warning(disable:4201)

  union ClientVisibilityFlags
  {
    typedef unsigned StorageType;

    struct
    {
      bool enemy : 1;
      bool objectVisible : 1;
      bool placementVisible : 1;
      bool hasInvisibility : 1;
      bool hasIgnoreInvisibility : 1;
      bool sharedVision : 1;
    };

    StorageType bits;

    ClientVisibilityFlags()
      : bits(StorageType(0))
    {
    }

    ClientVisibilityFlags(const ClientVisibilityFlags& other)
      : bits(other.bits)
    {
    }

    ClientVisibilityFlags& operator=(const ClientVisibilityFlags& other)
    {
      bits = other.bits;
      return *this;
    }

    void Reset()
    {
      bits = StorageType(0);
    }
  };

#pragma warning(pop)

  inline bool operator==(const ClientVisibilityFlags& lhs, const ClientVisibilityFlags& rhs)
  {
    return lhs.bits == rhs.bits;
  }

  inline bool operator!=(const ClientVisibilityFlags& lhs, const ClientVisibilityFlags& rhs)
  {
    return lhs.bits == rhs.bits;
  }
}
