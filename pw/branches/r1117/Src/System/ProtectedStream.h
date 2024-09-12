#ifndef PROTECTEDTREAM_H__
#define PROTECTEDTREAM_H__

#include "MemoryStream.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ProtectedStream : public MemoryStream
{
public:

  enum  Protect
  {
    ACCESS_NO        = 0,
    ACCESS_WRITE     = 1,
    ACCESS_READ      = 2,
    ACCESS_READWRITE = 3,
  };
private:
  OBJECT_METHODS( 0x1E4A8B47, ProtectedStream );

  Protect protectStatus;

protected:
	int ReadInternal( void *pData, const int length );
	int WriteInternal( const void *pData, const int length );
  void SetSizeInternal( const int size );

  virtual char * AllocateBuffer(size_t nSize);
  virtual void   FreeBuffer    (char   *&pBuffer);

public:
	ProtectedStream();
	ProtectedStream( const int initialSize);

	ProtectedStream( const ProtectedStream& );
	ProtectedStream& operator = ( const ProtectedStream& );

	virtual bool operator == ( const ProtectedStream& ) const;
	
	virtual ~ProtectedStream() { Close(); }
 	virtual void Close();

  void    SetProtect(Protect prot);
  Protect GetProtect() const {return protectStatus;}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif   //PROTECTEDTREAM_H__

