#include "stdafx.h"

#include "WinFileSystem.h"
#include "FilePath.h"
#include "FileUtils.h"
#include "WinFileUnbuffered.h"


#if defined( NV_WIN_PLATFORM )


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WinFileUnbuffered::WinFileUnbuffered(char const *_filePath, int _expectedFileSize): 
  fileHandle (INVALID_HANDLE_VALUE), filePath(_filePath), expectedSize(_expectedFileSize), sectorSize(0), pageSize(0), filePointer(0)
{
  pageSize = GetPageSize();
  //create new file
  fileHandle = CreateFileA(filePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_WRITE_THROUGH, NULL);
  if(fileHandle != INVALID_HANDLE_VALUE)
  {
    string disk(_filePath);
    NI_ASSERT(disk.length() >= 3, "Full path should have drive.");
    disk = disk.substr(0, 3);
    DWORD dwBytesPerSect = GetSectorSize(disk.c_str());
    //align size
    unsigned __int64 addition = ~(dwBytesPerSect - 1);
    if((expectedSize & (dwBytesPerSect - 1)) != 0)
    {
      //alignment needed
       expectedSize = (expectedSize + (dwBytesPerSect - 1)) & addition;
    }
    sectorSize = dwBytesPerSect;
    BOOL result = SetFilePointerEx(fileHandle, *(LARGE_INTEGER *) &expectedSize, NULL, FILE_BEGIN);
    NI_ASSERT(result != FALSE, "Errorness.");
    result = SetEndOfFile(fileHandle);
    NI_ASSERT(result != FALSE, "Errorness. Possibly not enough space on media.");
    CloseHandle(fileHandle);
    //create for usage
    fileHandle = CreateFileA(filePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED | FILE_FLAG_SEQUENTIAL_SCAN | FILE_FLAG_WRITE_THROUGH, NULL);
    NI_ASSERT(fileHandle != INVALID_HANDLE_VALUE, "Errorness.");
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WinFileUnbuffered::Write(void const **pBuffer, size_t *bufferSizes,  size_t buffersNum, size_t sizeOfData, WriteStruct &writeStr)
{
  size_t currBuffer;
  NI_VERIFY((sizeOfData & (sectorSize - 1)) == 0, "Size should be aligned", return;);
  size_t nSum = 0;
  for(currBuffer = 0; currBuffer < buffersNum; currBuffer++)
  {
    //get address as int
    DWORD addr = (DWORD)pBuffer[currBuffer];
    NI_VERIFY((addr & (pageSize   - 1)) == 0, "Address should be aligned", return;);
    if(currBuffer < (buffersNum - 1))
    {
      NI_VERIFY((bufferSizes[currBuffer]& (pageSize   - 1)) == 0, "Size should be aligned", return;);
    }
    else
    {
      NI_VERIFY((bufferSizes[currBuffer]& (sectorSize   - 1)) == 0, "Size should be aligned", return;);
    }
    nSum += bufferSizes[currBuffer];
  }
  NI_VERIFY( nSum == sizeOfData, "Incorrect size", return;);
 
  //prepare event 
  writeStr.Reset();

  //fill-in overlapped
  writeStr.writeInfo.Offset     = filePointer & 0xFFFFFFFF;
  writeStr.writeInfo.OffsetHigh = ((filePointer & 0xFFFFFFFF00000000) >> 32) & 0xFFFFFFFF;
  filePointer += sizeOfData;
  DWORD nPages = sizeOfData / pageSize;
  if(sizeOfData % pageSize != 0)
  {
    nPages += 1;
  }
  //allocate data on stack
  FILE_SEGMENT_ELEMENT *pElems = (FILE_SEGMENT_ELEMENT*)alloca(sizeof(FILE_SEGMENT_ELEMENT) * (nPages + 1));
  pElems[nPages].Buffer = 0;
  size_t i;
  currBuffer = 0;
  size_t nBackShift = 0;
  for(i = 0; i < nPages;)
  {
    char const *pAddr = NULL;
    if(pageSize * (i - nBackShift) >= bufferSizes[currBuffer])
    {
      currBuffer++;
      nBackShift = i;
      continue;
    }
    pAddr = (char const *)pBuffer[currBuffer] + pageSize * (i - nBackShift);
    pElems[i].Buffer = const_cast<char *>(pAddr);
    i++;
  }
  BOOL rv = WriteFileGather(fileHandle, pElems, sizeOfData, NULL, &writeStr.writeInfo);
  NI_ASSERT(rv != 0 || GetLastError() == ERROR_IO_PENDING, "errorness");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WinFileUnbuffered::Write(void const *pBuffer, size_t size, WriteStruct &writeStr)
{
  Write(&pBuffer, &size, 1, size, writeStr);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WinFileUnbuffered::Write(void const *pHeader, void const *pBuffer, size_t nSize, WriteStruct &writeStr)
{
  void const  *buffers[2] = {pHeader, pBuffer};
  size_t       sizes  [2] = {pageSize, nSize};
  Write(buffers, sizes, 2, nSize + pageSize, writeStr);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WinFileUnbuffered::~WinFileUnbuffered()
{
  //just cancel it for now, since we do not care. Class should not be deleted until everything is completed.
  if(fileHandle != INVALID_HANDLE_VALUE)
  {
    CancelIo(fileHandle);
    CloseHandle(fileHandle);
    if(filePointer > 0)
    {
    //now open it properly & truncate
      fileHandle = CreateFileA(filePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      NI_ASSERT(fileHandle != INVALID_HANDLE_VALUE, "Errorness.");
      BOOL result = SetFilePointerEx(fileHandle, *(LARGE_INTEGER *) &filePointer, NULL, FILE_BEGIN);
    NI_ASSERT(result != FALSE, "Errorness.");
      SetEndOfFile(fileHandle);
      CloseHandle(fileHandle);
  }
    else
    {
      DeleteFileA(filePath.c_str());
    }
  }
}

bool WinFileUnbuffered::HasOperationCompleted(WriteStruct &writeStr, bool bWait) const
{
  DWORD numberOfBytesTransferred; 
  BOOL rv = GetOverlappedResult(fileHandle, &writeStr.writeInfo, &numberOfBytesTransferred , (bWait)?TRUE:FALSE);
  if(!bWait)
  {
    if(rv == 0 &&  (GetLastError() == ERROR_IO_INCOMPLETE || GetLastError() == ERROR_IO_PENDING))
    {
      return false;
    }
    else
    {
      NI_ASSERT(rv != 0, "erorr");
    }
  }
  else
  {
    NI_ASSERT(rv != 0, "erorr");
  }
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int WinFileUnbuffered::GetPageSize()
{
  SYSTEM_INFO sysInfo;
  GetSystemInfo(&sysInfo);
  return sysInfo.dwPageSize;
}
unsigned int WinFileUnbuffered::GetSectorSize(char const * rootDir)
{
  DWORD dwSectPerClust, dwBytesPerSect,  dwFreeClusters, dwTotalClusters;
  NI_VERIFY(strlen(rootDir) >= 3, "Incorrect path given.", return 0;);
  NI_VERIFY(rootDir[1] == ':' && (rootDir[2] == '\\' || rootDir[2] == '/'), "Incorrect path given.", return 0;);
  BOOL result = GetDiskFreeSpaceA(rootDir, &dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
  NI_ASSERT(result != FALSE, NI_STRFMT("Function GetDiskFreeSpace returned error %d.", GetLastError()));
  return dwBytesPerSect;
}


#elif defined( NV_LINUX_PLATFORM )


#include <sys/statfs.h>

unsigned int WinFileUnbuffered::GetPageSize()
{
  return sysconf( _SC_PAGESIZE );
}

unsigned int WinFileUnbuffered::GetSectorSize( char const * rootDir )
{
  assert( NULL != rootDir );

  struct statfs fs_info;
  NI_VERIFY( statfs( rootDir, &fs_info ), NStr::StrFmt( "Function statfs returned error %d.", errno ), return 0 );

  return fs_info.f_bsize;
}


WinFileUnbuffered::WinFileUnbuffered( char const *_filePath, int _expectedFileSize )
{
  // TODO: implement
}

void WinFileUnbuffered::Write( void const *pBuffer, size_t nSize, WinFileUnbuffered::WriteStruct &writeStr )
{
  // TODO: implement
}

void WinFileUnbuffered::Write( void const *pHeader, void const *pBuffer, size_t nSize, WinFileUnbuffered::WriteStruct &writeStr )
{
  // TODO: implement
}

void WinFileUnbuffered::Write( void const **pBuffer, size_t *bufferSizes,  size_t buffersNum, size_t sizeOfData, WinFileUnbuffered::WriteStruct &writeStr )
{
  // TODO: implement
}

bool WinFileUnbuffered::HasOperationCompleted( WinFileUnbuffered::WriteStruct &writeStr, bool bWait ) const
{
  // TODO: implement
  return false;
}

WinFileUnbuffered::~WinFileUnbuffered()
{
  // TODO: implement
}


#endif  // #elif defined( NV_LINUX_PLATFORM )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( WinFileUnbuffered );

