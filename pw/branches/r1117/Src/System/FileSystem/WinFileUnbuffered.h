#ifndef WINFILEUNBUFFERED_H_4175FD63_E274_4C
#define WINFILEUNBUFFERED_H_4175FD63_E274_4C

#include "FileSystem.h"
#include "System/Thread.h"

#if defined( NV_WIN_PLATFORM )

	class WinFileUnbuffered: public CObjectBase
	{
	private:

		typedef unsigned __int64 uint64;

		OBJECT_METHODS( 0x1E4A8BBB, WinFileUnbuffered );

		ZDATA
		ZNOPARENT(CObjectBase)

		HANDLE fileHandle;
		string filePath;
		uint64 expectedSize;
		DWORD  sectorSize;
		DWORD  pageSize;
		uint64 filePointer;

	public:

		ZEND int operator&( IBinSaver &f ) { f.Add(2,&( *( DWORD * )&fileHandle )); f.Add(3,&filePath); f.Add(4,&expectedSize); f.Add(5,&sectorSize); f.Add(6,&pageSize); f.Add(7,&filePointer); return 0; }

	private:

		WinFileUnbuffered(): fileHandle( INVALID_HANDLE_VALUE )
		{}

	public:

		struct WriteStruct {

			OVERLAPPED writeInfo;
			threading::Event completionEvent;

			WriteStruct()
			{
				Reset();
			}

			void Reset()
			{
				completionEvent.Reset();

				writeInfo.Internal = 0;
				writeInfo.InternalHigh = 0;
				writeInfo.Offset = 0;
				writeInfo.OffsetHigh = 0;
				writeInfo.hEvent = completionEvent.GetHandle();

			}

		};

		WinFileUnbuffered( char const *_filePath, int _expectedFileSize = 1024 * 1024 * 1024 );
		void Write( void const *pBuffer, size_t nSize, WriteStruct &writeStr );
		void Write( void const *pHeader, void const *pBuffer, size_t nSize, WriteStruct &writeStr );
		void Write( void const **pBuffer, size_t *bufferSizes,  size_t buffersNum, size_t sizeOfData, WriteStruct &writeStr );

		bool HasOperationCompleted( WriteStruct &writeStr, bool bWait ) const;
		~WinFileUnbuffered();

		static unsigned int GetPageSize();
		static unsigned int GetSectorSize( char const * rootDir );

		unsigned int GetSectorSize()
		{
			return sectorSize;
		}

	};

#elif defined( NV_LINUX_PLATFORM )

	#include <fstream>

	class WinFileUnbuffered: public CObjectBase
	{
	private:

		OBJECT_METHODS( 0x1E4A8BBB, WinFileUnbuffered );

    std::ofstream m_file;

    ZDATA
		ZNOPARENT(CObjectBase)

		string m_file_path;
		uint64 m_expected_size;
		uint m_sector_size;
		uint m_page_size;
		uint64 m_file_pointer;

	public:

		ZEND int operator&( IBinSaver &f ) { f.Add(2,&m_file_path); f.Add(3,&m_expected_size); f.Add(4,&m_sector_size); f.Add(5,&m_page_size); f.Add(6,&m_file_pointer); return 0; }

	private:

		WinFileUnbuffered() /*: fileHandle( INVALID_HANDLE_VALUE )*/
		{}

	public:

		struct WriteStruct {

			//OVERLAPPED writeInfo;
			//threading::Event completionEvent;

			WriteStruct()
			{
				Reset();
			}

			void Reset()
			{
				//completionEvent.Reset();

				//writeInfo.Internal = 0;
				//writeInfo.InternalHigh = 0;
				//writeInfo.Offset = 0;
				//writeInfo.OffsetHigh = 0;
				//writeInfo.hEvent = completionEvent.GetHandle();
			}

		};

		WinFileUnbuffered( char const *_filePath, int _expectedFileSize = 1024 * 1024 * 1024 );
		void Write( void const *pBuffer, size_t nSize, WriteStruct &writeStr );
		void Write( void const *pHeader, void const *pBuffer, size_t nSize, WriteStruct &writeStr );
		void Write( void const **pBuffer, size_t *bufferSizes,  size_t buffersNum, size_t sizeOfData, WriteStruct &writeStr );

		bool HasOperationCompleted( WriteStruct &writeStr, bool bWait ) const;
		~WinFileUnbuffered();

		static unsigned int GetPageSize();
		static unsigned int GetSectorSize( char const * rootDir );

		unsigned int GetSectorSize()
		{
			return m_sector_size;
		}

	};

#endif

#endif //#define WINFILEUNBUFFERED_H_4175FD63_E274_4C

