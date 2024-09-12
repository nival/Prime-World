#ifndef SYSTEM_CYCLICBUFFER_H_INCLUDED
#define SYSTEM_CYCLICBUFFER_H_INCLUDED

#include <vector>


template <class T>
class CyclicBufferCleanCopy
{
public:
  static inline void Copy( typename std::vector<T>::iterator _srcBegin, typename std::vector<T>::iterator _srcEnd, typename std::vector<T>::iterator _dest )
  {
    if ( _srcEnd > _srcBegin )
      NI_ASSERT( _srcEnd + 1 != _dest, "" );

    while ( _srcBegin != _srcEnd )
    {
      *_dest = *_srcBegin;
      *_srcBegin = T();
      ++_srcBegin;
      ++_dest;
    }
  }
};



template <class T>
class CyclicBufferStdCopy
{
public:
  static inline void Copy( typename std::vector<T>::iterator _srcBegin, typename std::vector<T>::iterator _srcEnd, typename std::vector<T>::iterator _dest )
  {
    std::copy( _srcBegin, _srcEnd, _dest );
  }
};


template <class T, class CopyPolicy = CyclicBufferCleanCopy<T> >
class CyclicBuffer : public CopyPolicy
{
public:
  explicit CyclicBuffer( size_t _capacity = 0 ) :
  buffer( _capacity ),
  empty( true ),
  tail( 0 ),
  head( 0 )
  {}

  ~CyclicBuffer()
  {}


  bool Empty() const
  {
    return empty;
  }


  bool Full() const
  {
    if ( empty )
      return false;

    return ( tail == head ) ? true : false;
  }


  size_t Size() const
  {
    if ( empty )
      return 0;

    if ( head > tail )
      return head - tail;

    return ( buffer.size() - tail ) + head;
  }


  size_t Capacity() const
  {
    return buffer.size();
  }


  void Enlarge( size_t _newSize )
  {
    size_t oldSize = buffer.size();

    NI_VERIFY( _newSize > oldSize, "", return );

    buffer.resize( _newSize );

    if ( empty )
      return;

    if ( head > tail )
      return;

    size_t delta = _newSize - oldSize;
    if ( head <= delta )
    {
      CopyPolicy::Copy( buffer.begin(), buffer.begin() + head, buffer.begin() + oldSize );
      head = oldSize + head;
    }
    else
    {
      CopyPolicy::Copy( buffer.begin(), buffer.begin() + delta, buffer.begin() + oldSize );
      CopyPolicy::Copy( buffer.begin() + delta, buffer.begin() + head, buffer.begin() ); //!!!!!!!
      head -= delta;
    }
  }


  void PushAtHead( const T & _v )
  {
    EnsureRightSize();

    NI_VERIFY( !buffer.empty(), "", return );

    buffer[head] = _v;
    head = ( head + 1 ) % buffer.size();

    empty = false;
  }


  void PushAtTail( const T & _v )
  {
    EnsureRightSize();

    NI_VERIFY( !buffer.empty(), "", return );

    tail = ( tail + buffer.size() - 1 ) % buffer.size();
    buffer[tail] = _v;

    empty = false;
  }


  void PopHead()
  {
    NI_VERIFY( !empty, "", return );
    NI_VERIFY( !buffer.empty(), "", return );

    head = ( head + buffer.size() - 1 ) % buffer.size();
    buffer[head] = T();

    empty = ( head == tail ) ? true : false;
  }


  T PopHeadValue()
  {
    NI_VERIFY( !empty, "", return T() );
    NI_VERIFY( !buffer.empty(), "", return T() );

    head = ( head + buffer.size() - 1 ) % buffer.size();
    T _v = buffer[head];
    buffer[head] = T();

    empty = ( head == tail ) ? true : false;

    return _v;
  }


  void PopTail()
  {
    NI_VERIFY( !empty, "", return );
    NI_VERIFY( !buffer.empty(), "", return );

    buffer[tail] = T();
    tail = ( tail + 1 ) % buffer.size();

    empty = ( head == tail ) ? true : false;
  }


  T PopTailValue()
  {
    NI_VERIFY( !empty, "", return T() );
    NI_VERIFY( !buffer.empty(), "", return T() );

    T _v = buffer[tail];
    buffer[tail] = T();
    tail = ( tail + 1 ) % buffer.size();

    empty = ( head == tail ) ? true : false;
    return _v;
  }


  T & AtHead( size_t _offset = 0 )
  {
    NI_ASSERT( !empty, "" );

    if ( tail < head )
    {
      NI_ASSERT( _offset < head - tail, "" );
      return buffer[head - 1 - _offset];
    }

    if ( _offset < head )
      return buffer[head - 1 - _offset];

    size_t offs = _offset - head;
    NI_ASSERT( offs < buffer.size() - tail, "" );
    return buffer[buffer.size() - 1 - offs];
  }


  T & AtTail( size_t _offset = 0 )
  {
    NI_ASSERT( !empty, "" );

    if ( tail < head )
    {
      NI_ASSERT( _offset < head - tail, "" );
      return buffer[tail + _offset];
    }

    if ( tail + _offset < buffer.size() )
      return buffer[tail + _offset];

    size_t offs = _offset - ( buffer.size() - tail );
    NI_ASSERT( offs < head, "" );
    return buffer[offs];
  }


  const T & AtHead( size_t _offset = 0 ) const
  {
    return const_cast<CyclicBuffer *>( this )->AtHead( _offset );
  }


  const T & AtTail( size_t _offset = 0 ) const
  {
    return const_cast<CyclicBuffer *>( this )->AtTail( _offset );
  }

private:
  std::vector<T>  buffer;
  bool            empty;
  size_t          tail, head;

  void EnsureRightSize()
  {
    size_t initSize = Size();
    if ( initSize >= buffer.size() )
    {
      size_t newSize = initSize * 2;
      if ( !newSize )
        newSize = 16;
      Enlarge( newSize );
    }
  }
};


#endif //SYSTEM_CYCLICBUFFER_H_INCLUDED
