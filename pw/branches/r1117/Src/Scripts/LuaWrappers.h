#pragma once

#include "LuaValues.h"

#ifndef  LUA_NATIVE
# define LUA_NATIVE
#endif

namespace Lua
{
  template<class RV> 
  struct Wrapper0
  {
    template<RV(*Address)()>
    static int Func(lua_State* L)
    {
      LUA_NATIVE
      return lua_values<RV>::put(L, Address());
    };
  };

  template<class RV, class ARG1>
  struct Wrapper1
  {
    template<RV(*Address)(ARG1)>
    static int Func(lua_State* L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      return lua_values<RV>::put(L, Address(val1));
    };
  };

  template<class RV, class ARG1, class ARG2>
  struct Wrapper2
  {
    template<RV(*Address)(ARG1, ARG2)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      return lua_values<RV>::put(L, Address(val1, val2));
    }
  };

  template<class RV, class ARG1, class ARG2, class ARG3>
  struct Wrapper3
  {
    template<RV(*Address)(ARG1, ARG2, ARG3)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      return lua_values<RV>::put(L, Address(val1, val2, val3));
    }
  };

  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4>
  struct Wrapper4
  {
    template< RV(*Address)(ARG1, ARG2, ARG3, ARG4)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      return lua_values<RV>::put(L, Address(val1, val2, val3, val4));
    }
  };

  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  struct Wrapper5
  {
    template< RV(*Address)(ARG1, ARG2, ARG3, ARG4, ARG5)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      return lua_values<RV>::put(L, Address(val1, val2, val3, val4, val5));
    }
  };

  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
  struct Wrapper6
  {
    template< RV(*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG6 val6 = lua_values<ARG6>::get(L, 6);
      return lua_values<RV>::put(L, Address(val1, val2, val3, val4, val5, val6));
    }
  };

  template<class RV, class T>
  struct MemberWrapper0
  {
    template<RV(T::*Address)(), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      return lua_values<RV>::put(L, (obj->*Address)());
    }
  };
  template<class RV, class T, class ARG1>
  struct MemberWrapper1
  {
    template<RV(T::*Address)(ARG1), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      return lua_values<RV>::put(L, (obj->*Address)(val1));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2>
  struct MemberWrapper2
  {
    template<RV(T::*Address)(ARG1, ARG2), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3>
  struct MemberWrapper3
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4>
  struct MemberWrapper4
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  struct MemberWrapper5
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4, val5));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
  struct MemberWrapper6
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0; // Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG6 val6 = lua_values<ARG6>::get(L, 6);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4, val5, val6));
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7>
  struct MemberWrapper7
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0; // Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG6 val6 = lua_values<ARG6>::get(L, 6);
      ARG7 val7 = lua_values<ARG7>::get(L, 7);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4, val5, val6, val7));
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7, class ARG8>
  struct MemberWrapper8
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0; // Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG6 val6 = lua_values<ARG6>::get(L, 6);
      ARG7 val7 = lua_values<ARG7>::get(L, 7);
      ARG7 val8 = lua_values<ARG7>::get(L, 8);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4, val5, val6, val7, val8));
    }
  };

  template<class RV, class T>
  struct MemberWrapper0_const
  {
    template<RV(T::*Address)() const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      return lua_values<RV>::put(L, (obj->*Address)());
    }
  };

  template<class RV, class T, class ARG1>
  struct MemberWrapper1_const
  {
    template<RV(T::*Address)(ARG1) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      return lua_values<RV>::put(L, (obj->*Address)(val1));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2>
  struct MemberWrapper2_const
  {
    template<RV(T::*Address)(ARG1, ARG2) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3>
  struct MemberWrapper3_const
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4>
  struct MemberWrapper4_const
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  struct MemberWrapper5_const
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4, val5));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
  struct MemberWrapper6_const
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG6 val6 = lua_values<ARG5>::get(L, 6);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4, val5, val6));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7>
  struct MemberWrapper7_const
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG6 val6 = lua_values<ARG5>::get(L, 6);
      ARG7 val7 = lua_values<ARG5>::get(L, 7);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4, val5, val6, val7));;
    }
  };

  template<class RV, class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7, class ARG8>
  struct MemberWrapper8_const
  {
    template<RV(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG6 val6 = lua_values<ARG5>::get(L, 6);
      ARG7 val7 = lua_values<ARG5>::get(L, 7);
      ARG8 val8 = lua_values<ARG5>::get(L, 8);
      return lua_values<RV>::put(L, (obj->*Address)(val1, val2, val3, val4, val5, val6, val7, val8));;
    }
  };

  template<>
  struct Wrapper0<void>
  {
    template<void(*Address)()>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      Address();
      return 0;
    }
  };

  template<class ARG1>
  struct Wrapper1<void, ARG1>
  {
    template<void(*Address)(ARG1)>
    static int Func(lua_State* L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      Address(val1);
      return 0;
    };
  };

  template<class ARG1, class ARG2>
  struct Wrapper2<void, ARG1, ARG2>
  {
    template<void(*Address)(ARG1, ARG2)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      Address(val1, val2);
      return 0;
    }
  };

  template<class ARG1, class ARG2, class ARG3>
  struct Wrapper3<void, ARG1, ARG2, ARG3>
  {
    template<void(*Address)(ARG1, ARG2, ARG3)>
    static int Func(lua_State *L){
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      Address(val1, val2, val3);
      return 0;
    }
  };

  template<class ARG1, class ARG2, class ARG3, class ARG4>
  struct Wrapper4<void, ARG1, ARG2, ARG3, ARG4>
  {
    template<void(*Address)(ARG1, ARG2, ARG3, ARG4)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      Address(val1, val2, val3, val4);
      return 0;
    }
  };

  template<class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  struct Wrapper5<void, ARG1, ARG2, ARG3, ARG4, ARG5>
  {
    template<void(*Address)(ARG1, ARG2, ARG3, ARG4, ARG5)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG4>::get(L, 5);
      Address(val1, val2, val3, val4, val5);
      return 0;
    }
  };

  template<class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
  struct Wrapper6<void, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6>
  {
    template<void(*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG6 val6 = lua_values<ARG6>::get(L, 6);
      Address(val1, val2, val3, val4, val5, val6);
      return 0;
    }
  };

  template<class T>
  struct MemberWrapper0<void, T>
  {
    template<void(T::*Address)(), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      (obj->*Address)();
      return 0;
    }
  };

  template<class T, class ARG1>
  struct MemberWrapper1<void, T, ARG1>
  {
    template<void(T::*Address)(ARG1), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      (obj->*Address)(val1);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2>
  struct MemberWrapper2<void, T, ARG1, ARG2>
  {
    template<void(T::*Address)(ARG1, ARG2), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      (obj->*Address)(val1, val2);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2, class ARG3>
  struct MemberWrapper3<void, T, ARG1, ARG2, ARG3>
  {
    template<void(T::*Address)(ARG1, ARG2, ARG3), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      (obj->*Address)(val1, val2, val3);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2, class ARG3, class ARG4>
  struct MemberWrapper4<void, T, ARG1, ARG2, ARG3, ARG4>
  {
    template<void(T::*Address)(ARG1, ARG2, ARG3, ARG4), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L){
      LUA_NATIVE
        T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      (obj->*Address)(val1, val2, val3, val4);
      return 0;
    }
  };
  
  template<class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  struct MemberWrapper5<void, T, ARG1, ARG2, ARG3, ARG4, ARG5>
  {
    template<void(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      (obj->*Address)(val1, val2, val3, val4, val5);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
  struct MemberWrapper6<void, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6>
  {
    template<void(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6), class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
        T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG5 val6 = lua_values<ARG5>::get(L, 6);
      (obj->*Address)(val1, val2, val3, val4, val5, val6);
      return 0;
    }
  };
  
  template<class T>
  struct MemberWrapper0_const<void, T>
  {
    template<void(T::*Address)() const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      (obj->*Address)();
      return 0;
    }
  };

  template<class T, class ARG1>
  struct MemberWrapper1_const<void, T, ARG1>
  {
    template<void(T::*Address)(ARG1) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      (obj->*Address)(val1);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2>
  struct MemberWrapper2_const<void, T, ARG1, ARG2>
  {
    template<void(T::*Address)(ARG1, ARG2) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      (obj->*Address)(val1, val2);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2, class ARG3>
  struct MemberWrapper3_const<void, T, ARG1, ARG2, ARG3>
  {
    template<void(T::*Address)(ARG1, ARG2, ARG3) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      (obj->*Address)(val1, val2, val3);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2, class ARG3, class ARG4>
  struct MemberWrapper4_const<void, T, ARG1, ARG2, ARG3, ARG4>
  {
    template<void(T::*Address)(ARG1, ARG2, ARG3, ARG4) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error
      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      (obj->*Address)(val1, val2, val3, val4);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  struct MemberWrapper5_const<void, T, ARG1, ARG2, ARG3, ARG4, ARG5>
  {
    template<void(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
      T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error

      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);

      (obj->*Address)(val1, val2, val3, val4, val5);
      return 0;
    }
  };

  template<class T, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
  struct MemberWrapper6_const<void, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6>
  {
    template<void(T::*Address)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const, class GetObjectPtrType, GetObjectPtrType GetObjectPtr>
    static int Func(lua_State *L)
    {
      LUA_NATIVE
        T* obj = static_cast<T*>(GetObjectPtr(L));
      if(!obj)
        return 0;// Type error

      ARG1 val1 = lua_values<ARG1>::get(L, 1);
      ARG2 val2 = lua_values<ARG2>::get(L, 2);
      ARG3 val3 = lua_values<ARG3>::get(L, 3);
      ARG4 val4 = lua_values<ARG4>::get(L, 4);
      ARG5 val5 = lua_values<ARG5>::get(L, 5);
      ARG5 val6 = lua_values<ARG5>::get(L, 6);

      (obj->*Address)(val1, val2, val3, val4, val5, val6);
      return 0;
    }
  };
  
  template<class RV>
  typename Wrapper0<RV> make_wrapper(RV(*)())
  {
    return Wrapper0<RV>();
  }

  template<class RV, class ARG1>
  typename Wrapper1<RV, ARG1> make_wrapper(RV(*)(ARG1))
  {
    return Wrapper1<RV, ARG1>();
  }

  template<class RV, class ARG1, class ARG2>
  typename Wrapper2<RV, ARG1, ARG2> make_wrapper(RV(*)(ARG1, ARG2))
  {
    return Wrapper2<RV, ARG1, ARG2>();
  }

  template<class RV, class ARG1, class ARG2, class ARG3>
  typename Wrapper3<RV, ARG1, ARG2, ARG3> make_wrapper(RV(*)(ARG1, ARG2, ARG3))
  {
    return Wrapper3<RV, ARG1, ARG2, ARG3>();
  }

  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4>
  typename Wrapper4<RV, ARG1, ARG2, ARG3, ARG4> make_wrapper(RV(*)(ARG1, ARG2, ARG3, ARG4))
  {
    return Wrapper4<RV, ARG1, ARG2, ARG3, ARG4>();
  }

  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  typename Wrapper5<RV, ARG1, ARG2, ARG3, ARG4, ARG5> make_wrapper(RV(*)(ARG1, ARG2, ARG3, ARG4, ARG5))
  {
    return Wrapper5<RV, ARG1, ARG2, ARG3, ARG4, ARG5>();
  }

  template<class T, class RV>
  typename MemberWrapper0<RV, T>  make_member_wrapper(RV(T::*)())
  {
    return MemberWrapper0<RV, T>();
  }

  template<class T, class RV, class ARG1>
  typename MemberWrapper1<RV, T, ARG1>  make_member_wrapper(RV(T::*)(ARG1))
  {
    return MemberWrapper1<RV, T, ARG1>();
  }

  template<class T, class RV, class ARG1, class ARG2>
  typename MemberWrapper2<RV, T, ARG1, ARG2>  make_member_wrapper(RV(T::*)(ARG1, ARG2))
  {
    return MemberWrapper2<RV, T, ARG1, ARG2>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3>
  typename MemberWrapper3<RV, T, ARG1, ARG2, ARG3>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3))
  {
    return MemberWrapper3<RV, T, ARG1, ARG2, ARG3>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4>
  typename MemberWrapper4<RV, T, ARG1, ARG2, ARG3, ARG4>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4))
  {
    return MemberWrapper4<RV, T, ARG1, ARG2, ARG3, ARG4>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  typename MemberWrapper5<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4, ARG5))
  {
    return MemberWrapper5<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
  typename MemberWrapper6<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6))
  {
    return MemberWrapper6<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7>
  typename MemberWrapper7<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7))
  {
    return MemberWrapper7<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7, class ARG8>
  typename MemberWrapper8<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8))
  {
    return MemberWrapper8<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8>();
  }
  
  template<class T, class RV>
  typename MemberWrapper0_const<RV, T>  make_member_wrapper(RV(T::*)() const)
  {
    return MemberWrapper0_const<RV, T>();
  }

  template<class T, class RV, class ARG1>
  typename MemberWrapper1_const<RV, T, ARG1>  make_member_wrapper(RV(T::*)(ARG1) const)
  {
    return MemberWrapper1_const<RV, T, ARG1>();
  }

  template<class T, class RV, class ARG1, class ARG2>
  typename MemberWrapper2_const<RV, T, ARG1, ARG2>  make_member_wrapper(RV(T::*)(ARG1, ARG2) const)
  {
    return MemberWrapper2_const<RV, T, ARG1, ARG2>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3>
  typename MemberWrapper3_const<RV, T, ARG1, ARG2, ARG3>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3) const)
  {
    return MemberWrapper3_const<RV, T, ARG1, ARG2, ARG3>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4>
  typename MemberWrapper4_const<RV, T, ARG1, ARG2, ARG3, ARG4>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4) const)
  {
    return MemberWrapper4_const<RV, T, ARG1, ARG2, ARG3, ARG4>();
  }

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  typename MemberWrapper5_const<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4, ARG5) const)
  {
    return MemberWrapper5_const<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5>();
  } 

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6>
  typename MemberWrapper6_const<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) const)
  {
    return MemberWrapper6_const<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6>();
  } 

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7>
  typename MemberWrapper7_const<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) const)
  {
    return MemberWrapper7_const<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7>();
  } 

  template<class T, class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5, class ARG6, class ARG7, class ARG8>
  typename MemberWrapper8_const<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8>  make_member_wrapper(RV(T::*)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8) const)
  {
    return MemberWrapper8_const<RV, T, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8>();
  } 
} // namespace Lua
