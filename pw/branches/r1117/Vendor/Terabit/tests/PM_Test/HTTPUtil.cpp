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
/**
 *  @file HTTPUtil.cpp
 *
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
// ============================================================================
#include "HTTPUtil.h"

using namespace std;
#include "ace/Message_Block.h"
#include "PConnection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HMap::HMap()
: std::map<HString,HString> ()
{
    ;
}

HMap::~HMap()
{
    ;
}

HString & HMap::operator[] (const char * pStrKey)
{
    HString Tmp (pStrKey);
    return  (*this)[Tmp];
}

HString & HMap::operator[] (const HString & rStrKey )
{
  return this->BaseClass::operator[](rStrKey);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


HMapItr::HMapItr  (HMap & Map)
: map_ (Map),
  itr_ (map_.begin ())
{
    ;
}

HMapItr::HMapItr  (const HMapItr & MapItr )
: map_ (MapItr.map_),
  itr_ (MapItr.itr_)
{
    ;
}

HMapItr::~HMapItr ()
{
    ;
}

HMapItr & HMapItr::operator= (const HMapItr & MapItr )
{
  if ( & MapItr.map_ == & map_ )
    {
        itr_ = MapItr.itr_;
    }
  return * this;
}

bool HMapItr::operator!= (const HMapItr & MapItr ) const
{
  return ! this->operator == ( MapItr );
}

bool HMapItr::operator== (const HMapItr & MapItr ) const
{
  return ( & MapItr.map_ == & map_ ) && ( MapItr.itr_ == itr_ );
}

HMapItr & HMapItr::begin ()
{
  itr_ = map_.begin ();
  return * this;
}

HMapItr & HMapItr::end ()
{
  itr_ = map_.end ();
  return * this;
}

HMapItr & HMapItr::operator ++ ()
{
  ++itr_;
  return * this;
}

HMapItr HMapItr::operator ++ (int)
{
  HMapItr tmp(*this);
  ++itr_;
  return tmp;;
}

const HString &  HMapItr::key  () const
{
  return (* itr_).first; 
}
const HString &  HMapItr::value() const
{
  return (* itr_).second;
}

HMapItr & HMapItr::operator = ( const HString & Key )
{
  return this->find ( Key );
}

HMapItr & HMapItr::find ( const HString & Key )
{
  itr_ = map_.find ( Key);
  return *this;
}

bool HMapItr::isValid () const 
{
  return itr_ != map_.end ();
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HTTPReader::HTTPReader(PConnection * session)
:   session_       (session),
    status_        (READ_NONE),
    mode_          (MODE_LINE),
    chunk_size_    (DEF_CHUNK_SIZE),
    max_line_size_ (DEF_LINE_SIZE)
{
    ;
}

HTTPReader::~HTTPReader()
{
    ;
}

bool 
HTTPReader::setMode (ReadMode eMode, size_t Size)
{
    switch ( eMode )
    {
    case MODE_LINE :  
      mode_ = MODE_LINE ;
      setMaxLineSize ( Size );
      return true ;

    case MODE_CHUNK :  
      mode_ = MODE_CHUNK ;
      setChunkSize ( Size );
      return true ;

    default :  break;
    }
    return false ;
}

void 
HTTPReader::setChunkSize (size_t ChunkSize) 
{
    chunk_size_ = ChunkSize;

    if ( chunk_size_ == 0 )
    {
        chunk_size_ = DEF_CHUNK_SIZE ;
    }
    else if ( chunk_size_  > MAX_CHUNK_SIZE )
    {
        chunk_size_  = MAX_CHUNK_SIZE ;
    }
}

void
HTTPReader::setMaxLineSize (size_t LineSize) 
{
    max_line_size_ = LineSize;

    if ( max_line_size_ == 0 )
    {
        max_line_size_ =  DEF_LINE_SIZE ;
    }
    else if ( max_line_size_  > MAX_LINE_SIZE )
    {
        max_line_size_ =  MAX_LINE_SIZE ;
    }
}

bool 
HTTPReader::init (void)
{
    status_ = READ_NONE;
    str_buf_.erase ();

    return this->read ();
}

HTTPReader::Status 
HTTPReader::get (HString & StrResult)
{
  switch ( mode_ )
  {
  case MODE_LINE :  
    return getLine ( StrResult ) ;

  case MODE_CHUNK : 
    return getChunk ( StrResult ) ;

  default :
    break;
  }

  status_ = READ_ERR_INT;
  return status_;
}

//---------------------------------------------------------------------
//  get Line
//---------------------------------------------------------------------
HTTPReader::Status
HTTPReader::getLine ( HString & StrLine)
{
  StrLine.erase ();

  switch (status_)
    {
    case READ_MORE    :
      return status_;

    case READ_ERR_INT :
    case READ_ERR_MEM :
    case READ_ERR_IO  : 
      return status_;

    case READ_EOF     : 
      break;

    case READ_NONE    :
    case READ_OK      :
    case READ_TOO_BIG :
      break;

    default           : 
      status_ = READ_ERR_INT; // internal logic error
      return status_;
    }


  Status rc       = READ_OK;

  size_t PosErase = str_buf_.size ();
  size_t PosNL    = str_buf_.find ( '\n' );
 
  if ( PosNL != HString::npos )  // Yes, NL found
    {
      PosErase = PosNL + 1 ;
    }
  else
    {
      PosNL = PosErase ;         // whole string  ;

      if (this->read () )        // try to read mode
        return status_;
    
      if ( PosNL == 0 )        // can not read and buf empty
       return status_ ;
    }

  if ( PosNL > max_line_size_ )
    rc = READ_TOO_BIG ;
  
  for (; PosNL != 0 ; --PosNL )
    {
      if ( str_buf_ [ PosNL - 1  ] != '\r' )
        break;
    }

  if (PosNL)
    {
      if (!HTTPUtil::addStringSafe (StrLine,
                                    str_buf_.c_str(),
                                    PosNL))
        {
          status_ = READ_ERR_MEM ;
          rc = status_;
        }
    }

  str_buf_.erase (0, PosErase );

  return rc ;
}

//---------------------------------------------------------------------
//  get Chunk
//---------------------------------------------------------------------

HTTPReader::Status
HTTPReader::getChunk ( HString & StrChunk)
{
  StrChunk.erase ();

  switch ( status_ )
    {
    case READ_MORE    :
      return status_;

    case READ_ERR_INT :
    case READ_ERR_MEM :
    case READ_ERR_IO  : 
      return status_;

    case READ_EOF     : 
      break;
    case READ_NONE    :
    case READ_OK      :
    case READ_TOO_BIG :
      break;

    default           : 
      status_ = READ_ERR_INT; // internal logic error
      return status_;
    }

  size_t LenPart = str_buf_.size ();

  if ( LenPart >= chunk_size_ )  // we have Chunk
    {
      LenPart = chunk_size_ ;
    }
  else 
    {
      if (this->read () )      // try to read mode
        return status_;

      if ( LenPart == 0 )   // can not read and buf empty
        return status_ ;
  }
  
  Status rc = READ_OK;

  if (!HTTPUtil::addStringSafe (StrChunk, 
                                str_buf_.c_str(),
                                LenPart))
  {
      status_ = READ_ERR_MEM ;
      rc = status_;
  }

  str_buf_.erase (0, LenPart );

  return rc ;
}

//---------------------------------------------------------------------
//  called only from processRead
//---------------------------------------------------------------------
bool
HTTPReader::on_read_finished(ACE_Message_Block & mb,
                             size_t bytes_read,
                             int error)
{
    if (status_ != READ_MORE )
      return false;
  
    
    if (error != 0 )
      {
        status_ = READ_ERR_IO;
        return true ;
      }

   
    if (bytes_read == 0 )
      {
        status_ = READ_EOF;
        return true ;
      }

    status_  = READ_NONE ;

    if (!HTTPUtil::addStringSafe (str_buf_, 
                                  mb.wr_ptr()-bytes_read,
                                  bytes_read))
      {
        status_ = READ_ERR_MEM ;
      }

    return true;
}

//---------------------------------------------------------------------
//
//---------------------------------------------------------------------

bool HTTPReader::read ()
{
  switch (status_)
    {
    case READ_MORE    :   
    case READ_ERR_MEM :
    case READ_ERR_IO  :
    case READ_ERR_INT :
    case READ_EOF     :  
      return false ;
    default           : 
      break ;
    }

  if (this->session_->initiate_read_stream() != 0 )
    {
        status_ = READ_ERR_INT;
        return false ;
    }

  status_ = READ_MORE ;
  return true ;
}

//----------------------------------------------------------------
//
//----------------------------------------------------------------
HTTPWriter::HTTPWriter(PConnection * session)
:   session_       (session)
{
    ;
}

HTTPWriter::~HTTPWriter()
{
    ;
}
bool 
HTTPWriter::init (void)
{
    return true;
}

HTTPWriter::Status
HTTPWriter::write ( const HString & Str )
{
    return write ( Str.c_str () , Str.length () );
}

HTTPWriter::Status
HTTPWriter::write ( const char * pTxt , size_t len )
{
    if ( !pTxt && !len )
      return WRITE_ERR;
    
    ACE_Message_Block * mb = 0;
    ACE_NEW_RETURN (mb,
                    ACE_Message_Block (pTxt, len),
                    WRITE_ERR);

    mb->rd_ptr (mb->base ());
    mb->wr_ptr (mb->base ());
    mb->wr_ptr (len);

    if (this->session_->initiate_write_stream(*mb) == 0)
      return WRITE_WAIT;
    
    return WRITE_ERR;
}

bool
HTTPWriter::on_write_finished(ACE_Message_Block & mb,
                             size_t bytes_written,
                             int error)
{
    if (error != 0  || bytes_written == 0)
      return false;

    return true ;
}

//------------------------------------------------------------------------
//  Static helpers
//------------------------------------------------------------------------
bool HTTPUtil::addStringSafe ( HString & StrTo, const HString & StrFrom )
{
  return addStringSafe ( StrTo, StrFrom.c_str(), StrFrom.length());
}

bool HTTPUtil::addStringSafe ( HString & StrTo, 
                               const char * pFrom, 
                               size_t LenFrom )
{
  if ( !pFrom || !LenFrom )
    return true ;
  
  size_t LenTo = StrTo.size ();

  if ( LenTo >= MAX_CHUNK_SIZE )  
    return false ;

#if defined (ACE_HAS_EXCEPTIONS)
  try
    {
#endif

      StrTo.append ( pFrom, LenFrom );

#if defined (ACE_HAS_EXCEPTIONS)
    }
  catch (...)
    {
      return false ;
    }
#endif

  LenTo += LenFrom;
    
  if ( LenTo != StrTo.size () )  // append: memory problems
    return false ;
 
  return true ;
}

bool HTTPUtil::skipSpaces ( HString & Str, size_t & i1, size_t & i2)
{ 
  size_t Len = Str.size () ;

  if ( i2 == HString::npos  || i2 > Len )
    i2 = Len ;

    
  for ( ; i1 < i2 && isspace ( Str[i1] ) ; i1++ ) 
    {
    }

  for ( ; i1 < i2 && isspace( Str[i1] ) ; i2-- )
    {
    }

  if ( i1 >= i2)
    return false ;

  return true ;
}

bool HTTPUtil::ToLower ( HString & Str )
{
  size_t Len = Str.size ();

  for ( size_t i=0; i < Len ; i++ )
    {
      Str[i] = ::tolower (Str[i]);
    }
  return true ;
}

bool HTTPUtil::ToUpper ( HString & Str )
{
  size_t Len = Str.size ();

  for ( size_t i=0; i < Len ; i++ )
    {
      Str[i] = ::toupper (Str[i]);
    }
  return true ;
}
//====================End of File ======================================


