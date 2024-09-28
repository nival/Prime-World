#pragma once

#ifndef _SIMPLE_SIGNAL_ST_H_
#define _SIMPLE_SIGNAL_ST_H_

#include "Ring.h"

// Single-threaded simple, value based signal
template<class T, class Id>
class SimpleSignalST : public NonCopyable
{
  seDECLARE_RING_CLASS(SimpleSignalST, ringPart, Ring);
  typename Ring::Part ringPart;
  T value;

  static Ring& GetRing();
  static T&   GetValue();

public:
  typedef T ValueType;

  SimpleSignalST() : value( GetValue() )
  {
    GetRing().addLast(this);
  }

  ~SimpleSignalST()
  {
    Ring::remove(this);
  }

  void Set(T _value)
  {
    value = _value;
  }

  operator const T () const
  {
    return value;
  }

  T Get() // for use in templates
  {
    return value;
  }

  static void Signal(T _value)
  {
    GetValue() = _value;
    for(ring::Range<Ring> it( GetRing() ); it; ++it)
      it->Set(_value);
  }
};


template<class T>
class ProxySignalST: public NGlobal::IVariable, public CObjectBase
{
  OBJECT_BASIC_METHODS(ProxySignalST);
public:
  ProxySignalST(): pVar(0) {}
  ProxySignalST(T *_pVar): pVar(_pVar) {}
  virtual NGlobal::VariantValue Get() { NI_ASSERT(pVar != 0, ""); return NGlobal::VariantValue( pVar->Get() ); }
  virtual void Set(const NGlobal::VariantValue &val) { NI_ASSERT(pVar != 0, ""); T::Signal( val.Get<T::ValueType>() ); }
  virtual void Apply() {}

private:
  T *pVar;
};


template<class T> 
ProxySignalST<T>* MakeSignalProxy(T *_pVar, typename T::ValueType _defVal)
{
  ASSERT(_pVar);
  T::Signal(_defVal);
  return new ProxySignalST<T>(_pVar);
}


#define IMPLEMENT_SIMPLE_SIGNAL_ST(SSS) \
template<> SSS::Ring& SSS::GetRing()    \
{                                       \
  static Ring theRing;                  \
  return theRing;                       \
}                                       \
template<> SSS::ValueType& SSS::GetValue() \
{                                          \
  static ValueType value = ValueType();    \
  return value;                            \
}

#define _COMMA_ ,
#define IMPLEMENT_SIMPLE_SIGNAL_ST2(T, Id) IMPLEMENT_SIMPLE_SIGNAL_ST( SimpleSignalST< T _COMMA_ Id > )


#endif
