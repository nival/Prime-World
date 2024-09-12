#include "stdafx.h"
#include "ProtectedStream.h"
#include "DumpingStream.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DumpingStream::DumpingStream(): ProtectedStream()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DumpingStream::DumpingStream( const int initialSize, CObj<WinFileUnbuffered> file) : ProtectedStream(initialSize )
{
  dumpFile = file;
  InitMembers();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DumpingStream::DumpingStream( const DumpingStream& other ): ProtectedStream(other)
{
  dumpFile = other.dumpFile;
  InitMembers();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DumpingStream& DumpingStream::operator = ( const DumpingStream& other )
{
  ProtectedStream::operator =(other);
  dumpFile = other.dumpFile;
  InitMembers();
  return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DumpingStream::InitMembers()
{
  pData = (StreamHeader *)VirtualAlloc( 0, WinFileUnbuffered::GetPageSize(), MEM_COMMIT, PAGE_READWRITE );                 
  isDumpingStarted = false;
  completionData.Reset(); 
  pData->nHeaderSize = WinFileUnbuffered::GetPageSize();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DumpingStream::operator == ( const DumpingStream& other ) const
{
	return ProtectedStream::operator ==(other) && other.dumpFile.GetBarePtr() == dumpFile.GetBarePtr();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DumpingStream::WaitDumpToFinish()
{
  if(isDumpingStarted) //we have pending I/O
  {
    bool bCompleted = dumpFile->HasOperationCompleted(completionData, true);
    if(bCompleted)
    {
      isDumpingStarted = false;
    }
    else
    {
      NI_ALWAYS_ASSERT("We waited and still not completed....");
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DumpingStream::SetSizeInternal( const int size )
{
  //it is allowed ONLY if dumping not in place. wait otherwise
  WaitDumpToFinish();
  ProtectedStream::SetSizeInternal(size);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DumpingStream::ReadInternal( void *pData, const int length )
{
  //just relay since we do not care
	return ProtectedStream::ReadInternal(pData, length);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DumpingStream::WriteInternal( const void *pData, const int length )
{
  //it is allowed ONLY if dumping not in place. wait otherwise
  WaitDumpToFinish();
	return ProtectedStream::WriteInternal(pData, length);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DumpingStream::Close()
{
  //it is allowed ONLY if dumping not in place. wait otherwise
  WaitDumpToFinish();
  ProtectedStream::Close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    DumpingStream::Dump(void const * pUserData, size_t userDataSize)
{
  WaitDumpToFinish();
  size_t writeSize = 0;
  if((GetPosition() & (pData->nHeaderSize - 1)) == 0)
  {
    writeSize = GetPosition();
  }
  else
  {
    writeSize = (GetPosition() + pData->nHeaderSize) & (~(pData->nHeaderSize - 1));
  }
  //fill in header
  pData->nDataSizeAligned = writeSize;
  pData->nDataSize        = GetPosition();
  NI_VERIFY(userDataSize <= pData->nHeaderSize - sizeof(StreamHeader), "Too Much data", return;);
  memcpy(pData + 1, pUserData, userDataSize);
  dumpFile->Write(pData, GetBuffer(), writeSize, completionData);
  isDumpingStarted = true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DumpingStream::~DumpingStream() 
{
  Close();
  if(pData != NULL)
  {
    VirtualFree(pData, 0, MEM_RELEASE);
    pData = NULL;
  }
}

        
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( DumpingStream );

