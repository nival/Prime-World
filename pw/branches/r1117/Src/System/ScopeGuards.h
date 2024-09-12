#pragma once

#if defined( NV_WIN_PLATFORM )
  #pragma warning(push)
  #pragma warning(disable: 4512)
#endif

//============= Value guard - restores variable' old value at scope exit ================
//========= It is quite efficient - it doesn't use virtual methods nor heap =============
//= Unfortunately, functions returning unwindable objects by value are never inlined by =
//======================= MSVC given that exceptions are enabled ========================
//============ This limitation can be overcome by means of BOOST_TYPEOF macro ===========

namespace ScopeGuards
{
  struct ValueScopeGuardBase
  {};

  template<typename T>
  class ValueScopeGuard : public ValueScopeGuardBase
  {
    const T oldVal;
    T& ref;

  public:
    ValueScopeGuard(T& _val, const T& _newVal) : oldVal(_val), ref(_val) { _val = _newVal; }
    ~ValueScopeGuard() { ref = oldVal; }
  };

  template<typename T, typename T1>
  inline const ValueScopeGuard<T> MakeValueScopeGuard(T& _val, const T1& _newVal)
  {
    return ValueScopeGuard<T>(_val, _newVal);
  }
}

#define CONCATENATE_DIRECT(A, B) A##B
#define CONCATENATE(A, B)        CONCATENATE_DIRECT(A, B)

// set var=val; restore old var value at scope exit
#define GUARD_VALUE(var, val) const ScopeGuards::ValueScopeGuardBase& CONCATENATE(valueScopeGuard_, __LINE__) = \
                                    ScopeGuards::MakeValueScopeGuard(var, val); CONCATENATE(valueScopeGuard_, __LINE__);

#if defined( NV_WIN_PLATFORM )
  #pragma warning(pop)
#endif
