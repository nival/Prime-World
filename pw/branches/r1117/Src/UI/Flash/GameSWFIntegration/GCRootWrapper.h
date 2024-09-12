#pragma once

namespace avmplus
{
  template <class T>
  class GCRootWrapper : public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( GCRootWrapper, BaseObjectST );

  private:
    GCRootWrapper() {}
    T * gcRoot;

  public:
    GCRootWrapper( T * _gcRoot ) : gcRoot( _gcRoot )
    {}

    ~GCRootWrapper()
    {
      if (gcRoot)
        delete gcRoot;

      gcRoot = 0;
    }

    T * Get() const { return gcRoot; }
  };
}