#ifndef SAFETEXTFORMATNSTL_H_INCLUDED
#define SAFETEXTFORMATNSTL_H_INCLUDED

#include "SafeTextFormat.h"
#include "SafeTextFormatBuffers.h"
#include "Asserts.h" //Required by nstring.h, but not included
#include "nstring.h"
#include "nvector.h"
#include "nmap.h"
#include "nset.h"
#include "nfixed_string.h"

namespace text
{

template<>
struct TArg<nstl::string> : public BasicStringArg<char> {
  TArg( const nstl::string & _v ) : BasicStringArg<char>( _v.c_str() ) {}
};

template<>
struct TArg<nstl::wstring> : public BasicStringArg<wchar_t> {
  TArg( const nstl::wstring & _v ) : BasicStringArg<wchar_t>( _v.c_str() ) {}
};

template <typename CharType, size_t N>
struct TArg< nstl::fixed_string<CharType, N> >
  : public BasicStringArg<CharType>
{
  TArg( const nstl::fixed_string<CharType, N> & _v )
    : BasicStringArg<CharType>( _v.c_str() )
  {
  }
};


typedef TStlBuffer<nstl::string> NstlBuffer;



template<class T>
struct TArg<nstl::vector<T> > : public TContainerArg< nstl::vector<T>, ContainerBracesPolicy_Brackets, TContainerValuePolicy_Single<typename nstl::vector<T>::const_iterator, T> >
{
  TArg( const nstl::vector<T> & _v ) : TContainerArg< nstl::vector<T>, ContainerBracesPolicy_Brackets, TContainerValuePolicy_Single<typename nstl::vector<T>::const_iterator, T> >( _v ) {}
};


template<class TKey, class TValue>
struct TArg<nstl::map<TKey, TValue> > : public TContainerArg< nstl::map<TKey, TValue>, ContainerBracesPolicy_Curly, TContainerValuePolicy_Pair<typename nstl::map<TKey, TValue>::const_iterator, TKey, TValue> >
{
  TArg( const nstl::map<TKey, TValue> & _v ) : TContainerArg< nstl::map<TKey, TValue>, ContainerBracesPolicy_Curly, TContainerValuePolicy_Pair<typename nstl::map<TKey, TValue>::const_iterator, TKey, TValue> >( _v ) {}
};


template<class T>
struct TArg<nstl::set<T> > : public TContainerArg< nstl::set<T>, ContainerBracesPolicy_Curly, TContainerValuePolicy_Single<typename nstl::set<T>::const_iterator, T> >
{
  TArg( const nstl::set<T> & _v ) : TContainerArg< nstl::set<T>, ContainerBracesPolicy_Curly, TContainerValuePolicy_Single<typename nstl::set<T>::const_iterator, T> >( _v ) {}
};

} //namespace text

#endif //SAFETEXTFORMATNSTL_H_INCLUDED
