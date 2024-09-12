#ifndef RANDOMINTERFACEIMPL_H_INCLUDED
#define RANDOMINTERFACEIMPL_H_INCLUDED

#include "RandomInterface.h"


namespace ni_rnd
{

class Factory : public IFactory, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( Factory, IFactory, BaseObjectST );

public:
  explicit Factory( bool _threadsafe = false ) :
  threadsafe( _threadsafe )
  {}

  virtual IGenerator * Produce( unsigned _seed );
  virtual IGenerator * Produce();

private:
  bool threadsafe;
};

} //namespace ni_rnd

#endif //RANDOMINTERFACEIMPL_H_INCLUDED
