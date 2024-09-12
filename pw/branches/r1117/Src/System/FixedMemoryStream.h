#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FixedMemoryStream : public Stream, public CObjectBase
{
	OBJECT_METHODS( 0x1E4A8B45, FixedMemoryStream );

	char *pBuffer;
	int offset;
	int realSize;
	int bufferSize;
	bool isOverflow;

private:
	// Not used.
	FixedMemoryStream( const FixedMemoryStream& );
	FixedMemoryStream& operator = ( const FixedMemoryStream& );

protected:
	FixedMemoryStream();

	void SeekInternal( const int offset );
	void SetSizeInternal( const int size );

	int ReadInternal( void *pData, const int length );
	int WriteInternal( const void *pData, const int length );

public:
	FixedMemoryStream( const void* buffer, const int size );
  virtual ~FixedMemoryStream() { Close(); }

  void SetBuffer( const void* buffer, const int size );

	bool IsOverflow() const { return isOverflow; }

	int GetSize() const { return realSize; }
	int GetPosition() const { return offset; }

	const char *GetBuffer() const { return pBuffer; }
	char *GetBuffer() { return pBuffer; }

	virtual void Close();
};
