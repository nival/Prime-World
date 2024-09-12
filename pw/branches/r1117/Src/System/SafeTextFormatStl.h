#ifndef SAFETEXTFORMATSTL_H_INCLUDED
#define SAFETEXTFORMATSTL_H_INCLUDED

#include "SafeTextFormat.h"
#include "SafeTextFormatBuffers.h"
#include <string>
#include <vector>
#include <map>
#include <set>

namespace text
{

template<>
struct TArg<std::string> : public BasicStringArg<char> {
  TArg( const std::string & _v ) : BasicStringArg<char>( _v.c_str() ) {}
};

template<>
struct TArg<std::wstring> : public BasicStringArg<wchar_t> {
  TArg( const std::wstring & _v ) : BasicStringArg<wchar_t>( _v.c_str() ) {}
};


typedef TStlBuffer<std::string> StlBuffer;



template<class T>
struct TArg<std::vector<T> > : public TContainerArg< std::vector<T>, ContainerBracesPolicy_Brackets, TContainerValuePolicy_Single<typename std::vector<T>::const_iterator, T> >
{
  TArg( const std::vector<T> & _v ) : TContainerArg< std::vector<T>, ContainerBracesPolicy_Brackets, TContainerValuePolicy_Single<typename std::vector<T>::const_iterator, T> >( _v ) {}
};


template<class TKey, class TValue>
struct TArg<std::map<TKey, TValue> > : public TContainerArg< std::map<TKey, TValue>, ContainerBracesPolicy_Curly, TContainerValuePolicy_Pair<typename std::map<TKey, TValue>::const_iterator, TKey, TValue> >
{
  TArg( const std::map<TKey, TValue> & _v ) : TContainerArg< std::map<TKey, TValue>, ContainerBracesPolicy_Curly, TContainerValuePolicy_Pair<typename std::map<TKey, TValue>::const_iterator, TKey, TValue> >( _v ) {}
};


template<class T>
struct TArg<std::set<T> > : public TContainerArg< std::set<T>, ContainerBracesPolicy_Curly, TContainerValuePolicy_Single<typename std::set<T>::const_iterator, T> >
{
  TArg( const std::set<T> & _v ) : TContainerArg< std::set<T>, ContainerBracesPolicy_Curly, TContainerValuePolicy_Single<typename std::set<T>::const_iterator, T> >( _v ) {}
};

} //namespace text

#endif //SAFETEXTFORMATSTL_H_INCLUDED
