#ifndef OPENHASHSET_H_B504937F_6029_4921
#define OPENHASHSET_H_B504937F_6029_4921

#include "nhash_fun.h"

template<class TElement, class THashFunc = hash<TElement> > 
class OpenHashSet 
{
private:

  struct Entry
  {
    TElement key;
    bool valid;
    bool exists;
    Entry() : key(), valid(false), exists(false) {}
  };

  THashFunc _M_hash;
  vector<Entry> _M_cont;
  int _M_size;
  
  Entry& find( const TElement& __key )
  {
    static Entry _M_invalid_entry;
    int hv = _M_hash( __key ) % _M_cont.size();
    int inc = 2;
    int triesCount = 0;
    while ( _M_cont[hv].valid && _M_cont[hv].key != __key )
    {
      NI_VERIFY( ++triesCount < _M_size, "Hash table overflow", return _M_invalid_entry );

      hv = ( hv + inc ) % _M_cont.size();
      inc += 2;
    }
    return _M_cont[hv];
  }

public:

  explicit OpenHashSet( int size ) 
  {
    _M_size = 0;
    _M_cont.resize( size );
  }

  bool operator[]( const TElement& __key )  
  {
    Entry& ent = find( __key );
    if ( !ent.valid )
      return false;
    return ent.exists;
  }

  void insert( const TElement& __key ) 
  {
    NI_VERIFY( _M_size < ( _M_cont.size() * 9 ) / 10, "Hash table is full", return );

    Entry& ent = find( __key );
    if ( !ent.valid || !ent.exists )
    {
      ++_M_size;
    }
    ent.valid = true;
    ent.exists = true;
    ent.key = __key;
  }

  int size() const
  {
    return _M_size;
  }
  int capacity() const
  {
    return _M_cont.size();
  }

  void clear()
  {
    int sz = capacity();
    _M_cont.clear();
    _M_cont.resize( sz );
    _M_size = 0;
  }

};




#endif //#define OPENHASHSET_H_B504937F_6029_4921
