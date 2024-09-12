#ifndef DUMPINGSTREAM_H__
#define DUMPINGSTREAM_H__

#include "ProtectedStream.h"
#include "FileSystem/WinFileUnbuffered.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This stream can dump it's data to WinFileUnbuffered file. All requirements for maximum efficiency will be fullfilled
class  DumpingStream: public ProtectedStream
{
public:
  struct StreamHeader
  {
    unsigned int nHeaderSize; // header that is written to before stream content; ussially VRAM page size
    unsigned int nDataSize;   // data size unaligned
    unsigned int nDataSizeAligned;   // real data size with padding written into file
    // user data used in dump argument will be written here
  };
private:
  OBJECT_METHODS( 0x1E4A8BB7, DumpingStream);

  CObj<WinFileUnbuffered>        dumpFile;
  WinFileUnbuffered::WriteStruct completionData;
  bool                           isDumpingStarted;   
  StreamHeader                  *pData;
  void WaitDumpToFinish();
  void InitMembers();
protected:
	int ReadInternal( void *pData, const int length );
	int WriteInternal( const void *pData, const int length );
  void SetSizeInternal( const int size );
public:
	DumpingStream();
	DumpingStream( const int initialSize, CObj<WinFileUnbuffered> file);

	DumpingStream( const DumpingStream& );
	DumpingStream& operator = ( const DumpingStream& );

	virtual bool operator == ( const DumpingStream& ) const;
	
	virtual ~DumpingStream();
 	virtual void Close();

  void    Dump(void const *pUserData, size_t userDataSize);

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif   //DUMPINGSTREAM_H__

