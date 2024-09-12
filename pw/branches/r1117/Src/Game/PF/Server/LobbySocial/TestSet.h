#pragma once

#include <set>
#include <vector>

template <class T, class TCont, class TPolicy>
class TTestSet : public TCont, public TPolicy
{
public:
  TTestSet() {}

  TTestSet( const T & i0 )
  { Add( i0 ); }

  TTestSet( const T & i0, const T & i1 )
  { Add( i0 ); Add( i1 ); }

  TTestSet( const T & i0, const T & i1, const T & i2 )
  { Add( i0 ); Add( i1 ); Add( i2 ); }

  TTestSet( const T & i0, const T & i1, const T & i2, const T & i3 )
  { Add( i0 ); Add( i1 ); Add( i2 ); Add( i3 ); }

  TTestSet( const T & i0, const T & i1, const T & i2, const T & i3, const T & i4 )
  { Add( i0 ); Add( i1 ); Add( i2 ); Add( i3 ); Add( i4 ); }

  TTestSet( const T & i0, const T & i1, const T & i2, const T & i3, const T & i4, const T & i5 )
  { Add( i0 ); Add( i1 ); Add( i2 ); Add( i3 ); Add( i4 ); Add( i5 ); }

  TTestSet( const T & i0, const T & i1, const T & i2, const T & i3, const T & i4, const T & i5, const T & i6 )
  { Add( i0 ); Add( i1 ); Add( i2 ); Add( i3 ); Add( i4 ); Add( i5 ); Add( i6 ); }

  TTestSet( const T & i0, const T & i1, const T & i2, const T & i3, const T & i4, const T & i5, const T & i6, const T & i7 )
  { Add( i0 ); Add( i1 ); Add( i2 ); Add( i3 ); Add( i4 ); Add( i5 ); Add( i6 ); Add( i7 ); }

  TTestSet( const T & i0, const T & i1, const T & i2, const T & i3, const T & i4, const T & i5, const T & i6, const T & i7, const T & i8 )
  { Add( i0 ); Add( i1 ); Add( i2 ); Add( i3 ); Add( i4 ); Add( i5 ); Add( i6 ); Add( i7 ); Add( i8 ); }

  TTestSet( const T & i0, const T & i1, const T & i2, const T & i3, const T & i4, const T & i5, const T & i6, const T & i7, const T & i8, const T & i9 )
  { Add( i0 ); Add( i1 ); Add( i2 ); Add( i3 ); Add( i4 ); Add( i5 ); Add( i6 ); Add( i7 ); Add( i8 ); Add( i9 ); }

  void Add( const T & i ) { TPolicy::Add( this, i ); }
  void Remove( const T & i ) { TPolicy::Remove( this, i ); }

  TTestSet & operator << ( const T & i ) { Add( i ); return *this; }
  TTestSet & operator >> ( const T & i ) { Remove( i ); return *this; }

  TTestSet operator / ( const TTestSet & substr ) {
    TTestSet result = *this;
    for ( TCont::const_iterator it = substr.begin(); it != substr.end(); ++it )
      result.Remove( *it );
    return result;
  }

  TTestSet operator + ( const TTestSet & rhp ) {
    TTestSet result = *this;
    result.insert( result.end(), rhp.begin(), rhp.end() );
    return result;
  }

  TTestSet & operator += ( const TTestSet & add ) {
    insert( end(), add.begin(), add.end() );
    return *this;
  }
};


namespace ni_detail {

template<class T>
class TestSetPolicy {
public:
  static void Add( std::set<T> * This, const T & i ) { This->insert( i ); }
  static void Remove( std::set<T> * This, const T & i ) { This->erase( i ); }
};

template<class T>
class TestVectorPolicy {
public:
  static void Add( std::vector<T> * This, const T & i ) { This->push_back( i ); }
  static void Remove( std::vector<T> * This, const T & i ) {
    std::vector<T>::iterator it = std::find( This->begin(), This->end(), i );
    if ( it != This->end() )
      This->erase( it );
  }
};

} //namespace ni_detail


typedef TTestSet<int, std::set<int>, ni_detail::TestSetPolicy<int>> TestIntSet;

typedef TTestSet<int, std::vector<int>, ni_detail::TestVectorPolicy<int>> TestIntVec;
