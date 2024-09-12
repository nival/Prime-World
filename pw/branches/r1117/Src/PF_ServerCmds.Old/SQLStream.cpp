#include <math.h>
#include <stdlib.h>
#include "../Server/src/TypeProxy.h"
#include "SQLStream.h"
#include "LobbyCommand.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NI_PLATF_WIN
#pragma warning(push)
#pragma warning(disable: 4996)
#endif

#ifdef NI_PLATF_LINUX
  #define I64_PREFIX   "%ll"
#else
  #define I64_PREFIX   "%I64"
#endif

void SQLStream::StoreSQLField(unsigned int n)
{
  SQLFieldType type = FT_UINT32;
  Write(&type, sizeof(type));
  Write(&n, sizeof(n));
}

void SQLStream::StoreSQLField(SQLFieldType type, const char *pVal, unsigned int nFieldLen)
{
  switch(type)
  {
    case FT_NULL_VALUE:
    {
      Write(&type, sizeof(type));
      break;
    }
    case FT_BLOB:
    {
      Write(&type, sizeof(type));
      Write(&nFieldLen, sizeof(nFieldLen));
      Write(pVal, nFieldLen);
      break;
    }
    case FT_CHAR:
    {
      char c = *pVal;
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_BYTE:
    {
      NI_ALWAYS_ASSERT("Not supported yet.");
      char c;
      sscanf(pVal , "%hhd", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_UBYTE:
    {
      NI_ALWAYS_ASSERT("Not supported yet.");
      unsigned char c;
      sscanf(pVal , "%hhu", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_SHORT:
    {
      short c;
      sscanf(pVal , "%hd", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_USHORT:
    {
      unsigned short c;
      sscanf(pVal , "%hu", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_INT32:
    {
      int c;
      sscanf(pVal , "%d", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_UINT32:
    {
      unsigned int c;
      sscanf(pVal , "%u", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_INT64:
    {
      long long c;
      sscanf(pVal , I64_PREFIX"d", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_UINT64:
    {
      unsigned long long c;
      sscanf(pVal , I64_PREFIX"u", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_STRING:
    {
      NI_ALWAYS_ASSERT("Should never appear. And not supported.");
      break;
    }
    case FT_WSTRING:
    {
      Write(&type, sizeof(type));
      nstl::wstring s = LobbyCommand::Utf8ToUnc16(pVal);
      //write
      int nStrLen = s.length() * sizeof(*s.begin());
      Write(&nStrLen, sizeof(nStrLen));
      Write(s.c_str(), nStrLen);
      break;
    }
    case FT_FLOAT:
    {
      float c;
      sscanf(pVal , "%f", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_DOUBLE:
    {
      double c;
      sscanf(pVal , "%lf", &c);
      Write(&type, sizeof(type));
      Write(&c, sizeof(c));
      break;
    }
    case FT_BOOL:
    {
      unsigned char c;
      c = *(unsigned char *)pVal;
      bool b = (c == 1);
      Write(&type, sizeof(type));
      Write(&b, sizeof(b));
      break;
    }
    default:
    {
      NI_ALWAYS_ASSERT("Wrong type.")
    }
  }
}

SQLStream& SQLStream::operator>>(BLOBField &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
  {
    res.init();
    return *this;
  }
  NI_ASSERT(type == FT_BLOB, "type error");
  Read(&res.nSize, sizeof(res.nSize));
  if(res.nSize > 0)
  {
    Reset(res.pData, new unsigned char[res.nSize]);
    void *p = &res.pData[0];
    Read(p, res.nSize);
  }
  return *this;
}
SQLStream& SQLStream::operator>>(         char  &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_CHAR || type == FT_BYTE, "type error");
  Read(&res, sizeof(res));
  return *this;
}
SQLStream& SQLStream::operator>>(unsigned char  &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_UBYTE, "type error");
  Read(&res, sizeof(res));
  return *this;
}
SQLStream& SQLStream::operator>>(         short &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_SHORT, "type error");
  Read(&res, sizeof(res));
  return *this;
}
SQLStream& SQLStream::operator>>(unsigned short &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_USHORT, "type error");
  Read(&res, sizeof(res));
  return *this;
}
SQLStream& SQLStream::operator>>(         int   &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_INT32 || type == FT_INT64 , "type error");
  if(type == FT_INT64)
  {
    Seek(-int(sizeof(type)), SEEKORIGIN_OFFSET);
    long long tres;
    *this >> tres;
    NI_ASSERT(mabs(tres) <= 0x7FFFFFFF, "Value does not fit into desired type.");
    res = tres;
  }
  else
  {
    Read(&res, sizeof(res));
  }
  return *this;
}
SQLStream& SQLStream::operator>>(unsigned int   &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_UINT32 || type == FT_UINT64 , "type error");
  if(type == FT_UINT64)
  {
    Seek(-int(sizeof(type)), SEEKORIGIN_OFFSET);
    unsigned long long tres;
    *this >> tres;
    NI_ASSERT(tres <= 0xFFFFFFFF, "Value does not fit into desired type.");
    res = tres;
  }
  else
  {
    Read(&res, sizeof(res));
  }
  return *this;
}

SQLStream& SQLStream::operator>>(        long   &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_INT32, "type error");
  Read(&res, sizeof(res));
  return *this;
}

SQLStream& SQLStream::operator>>(unsigned long   &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_UINT32, "type error");
  Read(&res, sizeof(res));
  return *this;
}

SQLStream& SQLStream::operator>>(         long long &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_INT64, "type error");
  Read(&res, sizeof(res));
  return *this;
}
SQLStream& SQLStream::operator>>(unsigned long long &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_UINT64, "type error");
  Read(&res, sizeof(res));
  return *this;
}
SQLStream& SQLStream::operator>>(nstl::string &res)
{
  NI_ALWAYS_ASSERT("Not supported");
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_STRING, "type error");
  Read(&res, sizeof(res));
  return *this;
}
SQLStream& SQLStream::operator>>(nstl::wstring &res)
{
  nstl::wstring s;
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_WSTRING, "type error");
  unsigned int nSize;
  Read(&nSize, sizeof(nSize));
  if(nSize > 0)
  {
    s.resize(nSize / sizeof(*s.begin()), L'x');
    nstl::wstring::iterator it = s.begin();
    Read(&(*it), nSize);
    s.resize(nSize / sizeof(*s.begin()));
    res = s;
  }
  return *this;
}
SQLStream& SQLStream::operator>>(float         &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  if(type == FT_DOUBLE)
  {
    Seek(-int(sizeof(type)), SEEKORIGIN_OFFSET);
    double tres;
    *this >> tres;
    NI_ASSERT(fabs(tres) <= (float)(3.4e+38), "Value does not fit into desired type.");
    res = (float)tres;
  }
  else
  {
    NI_ASSERT(type == FT_FLOAT, "type error");
    Read(&res, sizeof(res));
  }
  return *this;
}
SQLStream& SQLStream::operator>>(double        &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_DOUBLE, "type error");
  Read(&res, sizeof(res));
  return *this;
}
SQLStream& SQLStream::operator>>(bool          &res)
{
  SQLFieldType type;
  Read(&type, sizeof(type));
  if(type == FT_NULL_VALUE)
    return *this;
  NI_ASSERT(type == FT_BOOL, "type error");
  Read(&res, sizeof(res));
  return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long long SQLStream::ReadLongLongFromStream(SQLStream &str)
{
  long long lval;
  str >> lval;
  return lval;
}

double SQLStream::ReadDoubleFromStream(SQLStream &str)
{
  double lval;
  str >> lval;
  return lval;
}

long  SQLStream::ReadLongFromStream(SQLStream &str)
{
  long lval;
  str >> lval;
  return lval;
}

unsigned long  SQLStream::ReadULongFromStream(SQLStream &str)
{
  unsigned long          lval = 0;
  str >> lval;
  return lval;
}
bool SQLStream::ReadBoolFromStream(SQLStream &str)
{
  bool lval;
  str >> lval;
  return lval;
}


nstl::wstring  SQLStream::ReadWStrFromStream(SQLStream &str)
{
  nstl::wstring s;
  str >> s;
  return s;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//REGISTER_SAVELOAD_CLASS(SQLStream);

#ifdef NI_PLATF_WIN
#pragma warning(pop)
#endif
