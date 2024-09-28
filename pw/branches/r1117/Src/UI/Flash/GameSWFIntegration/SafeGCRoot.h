#pragma once

namespace flash
{

#pragma warning( push )
#pragma warning( disable: 4355 ) //'this' : used in base member initializer list

  template <typename T>
  class SafeGCRoot : public MMgc::GCRoot
  {
  public:
    SafeGCRoot( MMgc::GC *gc ) : MMgc::GCRoot( gc, this, sizeof(T) ) {}
    ~SafeGCRoot() 
    { 
      Destroy();
    }
  };

#pragma warning( pop )

}