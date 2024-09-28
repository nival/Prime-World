#pragma once

#pragma warning(disable: 4505) //Unreferenced local function has been removed

template<class T>
struct CreateHelpersHelper
{
  static T* _New() { return new T(); }
  template<class T1>
  static T* _New(T1 *_arg) { return new T(_arg); }
  template<class T1>
  static T* _New(const T1& _arg) { return new T(_arg); }
  template<class T1, class T2>
  static T* _New(T1 *_arg1, T2 *_arg2) { return new T(_arg1, _arg2); }
  template<class T1, class T2>
  static T* _New(T1* _arg1, const T2& _arg2) { return new T(_arg1, _arg2); }
  template<class T1, class T2>
  static T* _New(const T1& _arg1, T2 *_arg2) { return new T(_arg1, _arg2); }
  template<class T1, class T2>
  static T* _New(const T1& _arg1, const T2& _arg2) { return new T(_arg1, _arg2); }
};

template<int s, class T> struct CreateHelper : CreateHelpersHelper<T> {};


char ClassSelectorFunction( ... );


#define CUSTOM_NEW  CreateHelper<sizeof(ClassSelectorFunction((T*)0)), T>::_New

template<class T>
T* Create() { return CUSTOM_NEW(); }
template<class T, class T1>
T* Create(T1 *_arg) { return CUSTOM_NEW(_arg); }
template<class T, class T1>
T* Create(const T1& _arg) { return CUSTOM_NEW(_arg); }
template<class T, class T1, class T2>
T* Create(T1 *_arg1, T2 *_arg2) { return CUSTOM_NEW(_arg1, _arg2); }
template<class T, class T1, class T2>
T* Create(T1* _arg1, const T2& _arg2) { return CUSTOM_NEW(_arg1, _arg2); }
template<class T, class T1, class T2>
T* Create(const T1& _arg1, T2 *_arg2) { return CUSTOM_NEW(_arg1, _arg2); }
template<class T, class T1, class T2>
T* Create(const T1& _arg1, const T2& _arg2) { return CUSTOM_NEW(_arg1, _arg2); }

#undef CUSTOM_NEW
