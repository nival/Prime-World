#pragma once

namespace NMeta
{
  // Type list
  struct EmptyType{};
  class NullType {};

  template <class H, class T> struct TypeList { typedef H Head; typedef T Tail; };

  template <class T1 = NullType, class T2 = NullType, class T3 = NullType, class T4 = NullType, 
  class T5 = NullType, class T6 = NullType, class T7 = NullType, class T8 = NullType, 
  class T9 = NullType, class T10 = NullType>
  struct MakeTypeList
  {
  private:
    typedef typename MakeTypeList<T2 , T3 , T4, T5, T6, T7, T8, T9, T10>::Result TailResult;
  public:
    typedef TypeList<T1, TailResult> Result;
  };

  template <> struct MakeTypeList<> { typedef NullType Result; };

  template <class TList, unsigned int index, typename DefaultType = NullType> struct TypeAtNonStrict { typedef DefaultType Result; };
  template <class Head, class Tail, typename DefaultType> struct TypeAtNonStrict<TypeList<Head, Tail>, 0, DefaultType> { typedef Head Result; };
  template <class Head, class Tail, unsigned int i, typename DefaultType> struct TypeAtNonStrict<TypeList<Head, Tail>, i, DefaultType>
  {
    typedef typename TypeAtNonStrict<Tail, i - 1, DefaultType>::Result Result;
  };

}