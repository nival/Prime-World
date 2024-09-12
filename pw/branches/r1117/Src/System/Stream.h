#ifndef  STREAM_H___
#define  STREAM_H___

#include "nstring.h"
#include "Basic.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum ESeekOrigin
{
	SEEKORIGIN_BEGIN,
	SEEKORIGIN_OFFSET,
	SEEKORIGIN_END
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Stream : public IObjectBase
{
private:
	enum EStreamFlags
	{
		STREAMFLAGS_BROKEN = 0,
		STREAMFLAGS_OK = 1,
		STREAMFLAGS_CAN_READ = 2,
		STREAMFLAGS_CAN_WRITE = 4,
		STREAMFLAGS_CAN_SEEK = 8
	};

	int flags;

protected:
	virtual void SeekInternal( const int offset ) = 0;
	virtual void SetSizeInternal( const int size ) = 0;

	virtual int ReadInternal( void *pData, const int length ) = 0;
	virtual int WriteInternal( const void *pData, const int length ) = 0;

	void SetCanRead( const bool canRead ) { if ( canRead ) flags |= STREAMFLAGS_CAN_READ; else flags &= (0xFF ^ STREAMFLAGS_CAN_READ); }
	void SetCanWrite( const bool canWrite ) { if ( canWrite ) flags |= STREAMFLAGS_CAN_WRITE; else flags &= (0xFF ^ STREAMFLAGS_CAN_WRITE);	}
	void SetCanSeek( const bool canSeek ) { if ( canSeek ) flags |= STREAMFLAGS_CAN_SEEK; else flags &= (0xFF ^ STREAMFLAGS_CAN_SEEK);	}
	void SetBroken( const bool broken )
	{
		if ( broken )
			flags = 0;
		else
			flags |= STREAMFLAGS_OK;
	}

	Stream() : flags( STREAMFLAGS_BROKEN ) {}

public:
	virtual ~Stream() {}

	int SetSize( const int size );
	int Seek( const int offset, ESeekOrigin seekOrigin );

	bool IsOk() const { return (flags & STREAMFLAGS_OK) == STREAMFLAGS_OK; }
	bool CanRead() const { return (flags & STREAMFLAGS_CAN_READ) == STREAMFLAGS_CAN_READ; }
	bool CanWrite() const { return (flags & STREAMFLAGS_CAN_WRITE) == STREAMFLAGS_CAN_WRITE; }
	bool CanSeek() const { return (flags & STREAMFLAGS_CAN_SEEK) == STREAMFLAGS_CAN_SEEK; }

	virtual int GetSize() const = 0;
	virtual int GetPosition() const = 0;

	int Read( void *pData, const int length );
	int Write( const void *pData, const int length );

	void CopyFrom( Stream *pStream );
	void CopyFrom( Stream *pStream, const int length );

	// some streams can provide direct access to its buffer. always check return value.
	virtual const char *GetBuffer() const = 0;
  template<class T> T const* ReadInPlaceAs();

	virtual void Close() = 0;

  virtual void Flush() {};
  virtual void FinishFlush() {};

	// стандартные операции ввода/вывода
  bool ReadString( nstl::string &res, int nMaxSize = -1 );
	void WriteString( const nstl::string &res ) { Write( res.c_str(), res.size() ); }
	template<class T> Stream& operator>>( T &res ) { Read( &res, sizeof(res) ); return *this; }
	template<class T> Stream& operator<<( const T &res ) { Write( &res, sizeof(res) ); return *this; }
};
template<> inline Stream& Stream::operator>> <nstl::string>( nstl::string &res ) { ReadString( res ); return *this; }
template<> inline Stream& Stream::operator<< <nstl::string>( const nstl::string &res ) { WriteString( res ); return *this; }

template<class T> inline T const* Stream::ReadInPlaceAs()
{
  const char* ptr = GetBuffer();
  if (!ptr)
    return 0; // direct access is not possible
  int pos = GetPosition();
  if (Seek(sizeof(T), SEEKORIGIN_OFFSET) != pos + (int)sizeof(T))
    return 0; // not enough data
  return reinterpret_cast<T const*>(ptr + pos);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
