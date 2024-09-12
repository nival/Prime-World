#ifndef SQLSTREAM_H__
#define SQLSTREAM_H__

#include "../Server/src/TypeProxy.h"
#include <typeinfo>
#include "../System/nvector.h"
#include "../System/Stream.h"
#include "../System/MemoryStream.h"
#include "../System/ScopedArray.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct BLOBField
{
  unsigned int               nSize;
  ScopedArray<unsigned char> pData;
  BLOBField()
  {
    init();
  }
  void init()
  {
    nSize = 0;
    Reset(pData );
  }
  void serialize(MemoryStream &str)
  {
    str << nSize;
    if(nSize > 0)
      str.Write(&pData[0], nSize);
  }
  void deserialize(MemoryStream &str)
  {
    str >> nSize       ;
    if(nSize > 0)
    {
      Reset(pData, new unsigned char[nSize]);
      str.Read(&pData[0], nSize);
    }
  }


};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class  SQLStream: public MemoryStream
{
	OBJECT_METHODS( 0x1E4A8B46, SQLStream);
public:
  enum SQLFieldType
  {
    FT_NA = -1,
    FT_NULL_VALUE,
    FT_BLOB,
    FT_CHAR,
    FT_BYTE,
    FT_UBYTE,
    FT_SHORT,
    FT_USHORT,
    FT_INT32,
    FT_UINT32,
    FT_INT64,
    FT_UINT64,
    FT_STRING,
    FT_WSTRING,
    FT_FLOAT,
    FT_DOUBLE,
    FT_BOOL
  };
  SQLStream(): MemoryStream() {}
  SQLStream(const int initialSize): MemoryStream(initialSize) {}

  SQLStream( const SQLStream& s): MemoryStream(s) {}
  SQLStream& operator = ( const SQLStream& s) {MemoryStream::operator =(s); 	return *this;}

  bool operator == ( const SQLStream& s) const {return MemoryStream::operator == (s);}
  bool operator != ( const SQLStream& s) const {return MemoryStream::operator != (s);}

  SQLStream& operator>>(BLOBField      &res);
  SQLStream& operator>>(         char  &res);
  SQLStream& operator>>(unsigned char  &res);
  SQLStream& operator>>(         short &res);
  SQLStream& operator>>(unsigned short &res);
  SQLStream& operator>>(         int   &res);
  SQLStream& operator>>(unsigned int   &res);
  SQLStream& operator>>(         long  &res);
  SQLStream& operator>>(unsigned long  &res);
  SQLStream& operator>>(         long long &res);
  SQLStream& operator>>(unsigned long long &res);
  SQLStream& operator>>(nstl::string &res);
  SQLStream& operator>>(nstl::wstring &res);
  SQLStream& operator>>(float         &res);
  SQLStream& operator>>(double        &res);
  SQLStream& operator>>(bool          &res);

	virtual ~SQLStream() {}
  void StoreSQLField(SQLFieldType type, const void *pVal, unsigned int nFieldLen) {StoreSQLField(type, (const char *)pVal, nFieldLen);}
  void StoreSQLField(SQLFieldType type, const char *pVal, unsigned int nFieldLen);
  //nede for header
  void StoreSQLField(unsigned int n);

  static int            ReadIntFromStream     (SQLStream &str) {return (int)ReadLongFromStream(str);}
  static long           ReadLongFromStream    (SQLStream &str);
  static unsigned long  ReadULongFromStream   (SQLStream &str);
  static long long      ReadLongLongFromStream(SQLStream &str);
  static double         ReadDoubleFromStream  (SQLStream &str);
  static bool           ReadBoolFromStream    (SQLStream &str);
  static unsigned long  ReadIPFromStream      (SQLStream &str);
  static nstl::wstring  ReadWStrFromStream    (SQLStream &str);

private:
  template<class T> Stream& operator<<( const T &res ) { Write( &res, sizeof(res) ); return *this; }
  int Read( void *a, const int b) {return MemoryStream::Read(a, b);}
  int Write( const void *a, const int b) {return MemoryStream::Write(a, b);}

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif   //SQLSTREAM_H__

