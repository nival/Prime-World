/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/

// ============================================================================
//
// = AUTHOR
//    Alexander Libman <libman@terabit.com.au>
//
// ============================================================================

#ifndef _HTTPUTIL_H_
#define _HTTPUTIL_H_

#if _MSC_VER > 1000
# pragma once

//# pragma warning (disable : 4231)   // extern before template instantiation
//# pragma warning( disable : 4800 )  // forcing value to bool 'true' or 'false' 
//# pragma warning( disable : 4661) // no suitable definition provided ..
# pragma warning (disable : 4786)   //255 char debug symbols
 
#endif // _MSC_VER > 1000

#include <string>
#include <functional>
#include <map>

#include "ace/Message_Block.h"

enum
  {
    MAX_CHUNK_SIZE  = 0x10000,  // 64K
    MAX_LINE_SIZE   = 0x10000,  // 64K
    DEF_CHUNK_SIZE  = 16384,    // 16K 
    DEF_LINE_SIZE   = 16384     // 16K
  };


typedef  std::string  HString;
template struct std::less<HString>;
template class  std::map<HString,HString>;

class HMapItr;

class HMap : private std::map<HString,HString>
{
    friend class HMapItr ;
    typedef std::map<HString,HString> BaseClass;


public :
    HMap ();
    virtual ~HMap ();

    HString & operator[] ( const char * pStrKey );
    HString & operator[] ( const HString & rStrKey );

private:

    HMap (const HMap & other);
    HMap & operator = (const HMap & other);

};

class HMapItr 
{
public :
    HMapItr  (HMap & Map);
    HMapItr  (const HMapItr & MapItr);
    virtual ~HMapItr ();

    HMapItr & operator= (const HMapItr & MapItr );
    HMapItr & operator= ( const HString & Key );  // same as find
    HMapItr & find ( const HString & Key );

    bool      isValid () const;

    bool      operator== (const HMapItr & MapItr )const;
    bool      operator!= (const HMapItr & MapItr )const;


    HMapItr & begin ();
    HMapItr & end ();
    HMapItr & operator ++ ();
    HMapItr   operator ++ (int);

    const HString &  key  ()const;
    const HString &  value()const;

private:

    HMap &         map_;
    HMap::iterator itr_;
};
    

//class ACE_Message_Block;
class PConnection;


class HTTPReader  
{

public:
  enum ReadMode
    {
      MODE_CHUNK = 0x01,
      MODE_LINE  = 0x02
    };

  enum Status
    {
      READ_NONE    = 0x0000,  // Reader is free
      READ_OK      = 0x0001,  // Successful scan result
      READ_TOO_BIG = 0x0002,  // Scan OK, but line too big
      READ_MORE    = 0x0004,  // Reader waiting read completion
      READ_ERR_INT = 0x0010,  // Internal logic error
      READ_ERR_MEM = 0x0020,  // No memory available
      READ_ERR_IO  = 0x0040,  // I/O error
      READ_EOF     = 0x0080   // End of input stream
    };


	HTTPReader (PConnection * session);
	virtual ~HTTPReader();

  ReadMode  getMode  () { return mode_;}
  int       getStatus() { return status_;}
  size_t    getChunkSize() { return chunk_size_;}
  size_t    getMaxLineSize()  { return max_line_size_;}

  bool      setMode (ReadMode eMode, size_t Size );
  void      setChunkSize (size_t ChunkSize) ;
  void      setMaxLineSize  (size_t LineSize) ;


  Status    get      (HString & StrResult);
  Status    getLine  (HString & StrLine );
  Status    getChunk (HString & StrChunk);
  Status    getChunk (HString & StrChunk, size_t Size)
  {
      setChunkSize ( Size );
      return getChunk (StrChunk);
  }


  bool       init (void);  
  bool       on_read_finished(ACE_Message_Block & mb,
                              size_t bytes_read,
                              int error);


private:

  bool       read(void);

  PConnection * session_;
  Status     status_;
  ReadMode   mode_;

  size_t     chunk_size_;
  size_t     max_line_size_;
  
  HString    str_buf_;
};

class HTTPWriter
{
public:
	HTTPWriter (PConnection * session);

	virtual ~HTTPWriter();

  enum Status
    {
      WRITE_NONE    = 0x0000, 
      WRITE_OK      = 0x0001,  // 
      WRITE_WAIT    = 0x0004,  // Writer is waiting write completion
      WRITE_ERR     = 0x0008
    };
  
  Status write (const HString & Str );
  Status write (const char * pTxt , size_t Len);

  bool  init (void);  
  bool  on_write_finished(ACE_Message_Block & mb,
                          size_t bytes_written,
                          int error);


private:

  PConnection * session_;
};

class HTTPUtil
{
public:

    static bool addStringSafe (HString & StrTo,
                               const char * pFrom,
                               size_t LenFrom );

    static bool addStringSafe (HString & StrTo,
                               const HString & StrFrom);

    static bool skipSpaces (HString & Str, size_t& i1, size_t& i2 );

    static bool ToLower (HString & Str );
    static bool ToUpper (HString & Str );

};


#endif // !defined(_HTTPUTIL_)
//=====================End of File===========================================
