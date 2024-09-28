#ifndef FIXEDSTRING_H_060BBEE0_D99B_47CC
#define FIXEDSTRING_H_060BBEE0_D99B_47CC


class _BaseFixedString
{
public:
  _BaseFixedString() {}
};

template< unsigned int _capacity, typename TChar = char >
class FixedString : public _BaseFixedString
{
public:
  FixedString() { clear(); }
  FixedString( const TChar * str ) { Assign( str ); }

  //Operators
  FixedString & operator = ( const TChar * str ) { Assign( str ); return *this; }
  FixedString & operator += ( const TChar * str ) { Append( str ); return *this; }
  FixedString & operator += ( const TChar c ) { Append( c ); return *this; }
  bool operator == ( const TChar * str ) const { return Compare( str ) == 0; }
  bool operator != ( const TChar * str ) const { return Compare( str ) != 0; }
  bool operator < ( const TChar * str ) const { return Compare( str ) < 0; }
  bool operator > ( const TChar * str ) const { return Compare( str ) > 0; }

  template< size_t OTHER_SIZE>
  bool operator == ( const FixedString<OTHER_SIZE, TChar> & other ) const { return Compare( other.buffer ) == 0; }

  template< size_t OTHER_SIZE>
  bool operator != ( const FixedString<OTHER_SIZE, TChar> & other ) const { return Compare( other.buffer ) != 0; }

  template< size_t OTHER_SIZE>
  bool operator < ( const FixedString<OTHER_SIZE, TChar> & other ) const { return Compare( other.buffer ) < 0; }

  template< size_t OTHER_SIZE>
  bool operator > ( const FixedString<OTHER_SIZE, TChar> & other ) const { return Compare( other.buffer ) > 0; }

  //STL stuff
  typedef const TChar* const_iterator;
  typedef TChar* iterator;
  typedef const TChar& const_reference;
  typedef TChar& reference;

  const_reference operator[]( unsigned int index ) const	{	/*ASSERT(index<_size); FIXME */ return At( index ); }
  reference operator[]( unsigned int index ) { /*ASSERT(index<_size); FIXME */ return At( index );	}

  const_iterator begin() const { return &buffer[0];	}
  iterator begin() { return &buffer[0];	}

  const_iterator end() const { return &buffer[ size() ]; }
  iterator end() { return &buffer[ size() ]; }

  static size_t capacity() { return _capacity; }
  size_t size() const
  {
    for ( size_t i = 0; i < _capacity; ++i )
      if ( !buffer[i] )
        return i;
    return _capacity;
  }

  bool empty() const { return buffer[0] == 0; }
  void clear() { buffer[0] = 0; }

  const TChar* c_str() const { return buffer; }

  //Functions
  void Assign( const TChar * str )
  {
    size_t i = 0;
    for ( ; ( i < _capacity - 1 ) && *str ; ++i, ++str )
      buffer[i] = *str;
    buffer[i] = 0;
  }
  void AssignN( const TChar * str, size_t charsToCopy )
  {
    size_t i = 0;
    for ( ; ( i < _capacity - 1 ) && *str && charsToCopy > 0 ; ++i, ++str, --charsToCopy )
      buffer[i] = *str;
    buffer[i] = 0;
  }

  void Append( const TChar * str )
  {
    size_t i = 0;
    for ( ; i < _capacity - 1; ++i )
      if ( !buffer[i] )
        break;
    for ( ; ( i < _capacity - 1 ) && *str; ++i, ++str )
      buffer[i] = *str;
    buffer[i] = 0;
  }

  void Append( TChar c )
  {
    size_t i = 0;
    for ( ; i < _capacity - 1; ++i )
      if ( !buffer[i] )
        break;
    if ( i < _capacity - 1 )
    {
      buffer[i] = c;
      buffer[i + 1] = 0;
    }
  }

  bool IsValid() const
  {
    for ( size_t i = 0; i < _capacity; ++i )
      if ( !buffer[i] )
        return true;
    return false;
  }

  const TChar At( size_t index ) const
  {
    NI_ASSERT( index < _capacity, "index out of range" );
    return buffer[index];
  }

  TChar & At( size_t index )
  {
    NI_ASSERT( index < _capacity, "index out of range" );
    return buffer[index];
  }

  const TChar * Ptr() const { return buffer; }

  TChar * Ptr() { return buffer; }

  int Compare( const TChar * str ) const
  {
    for ( size_t i = 0; i < _capacity; ++i, ++str )
      if ( !buffer[i] && !*str )
        return 0;
      else if ( buffer[i] < *str )
        return -1;
      else if ( buffer[i] > *str )
        return +1;
      return -1;
  }

  void Printf(const char *sFormat, ...)
  {
    va_list vlArgs;
    va_start(vlArgs, sFormat);
    NStr::VPrintf(buffer, _capacity, sFormat, vlArgs);
    va_end(vlArgs);           
  }

private:
  TChar buffer[_capacity];
};


#endif //#define FIXEDSTRING_H_060BBEE0_D99B_47CC
