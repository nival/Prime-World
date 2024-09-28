#ifndef __BINARYBUFFER_H_INCLUDED__302310__
#define __BINARYBUFFER_H_INCLUDED__302310__

#include "Entity.h"
#include <vector>
#include <stdexcept>
#if defined( NV_LINUX_PLATFORM ) 
#include <string.h>
#endif

namespace nvl {

	class CBinaryBuffer
	{
	public:

		virtual size_t GetCapacity() const
		{ return m_Buffer.capacity(); }

		virtual void Reserve( size_t nSize )
		{ m_Buffer.reserve( nSize ); }

		virtual size_t GetSize() const
		{ return m_Buffer.size(); }

		virtual void Resize( size_t nSize )
		{ m_Buffer.resize( nSize ); }

		virtual str_t GetBuffer()
		{ return &m_Buffer[ 0 ]; }

		virtual cstr_t GetData() const
		{ return &m_Buffer[ 0 ]; }

		void Clear()
		{ Resize( 0 ); }

		virtual void Write( void const * pFrom, size_t nSize )
		{
			m_Buffer.insert(
				m_Buffer.end(),
				reinterpret_cast< cstr_t >( pFrom ),
				reinterpret_cast< cstr_t >( pFrom ) + nSize
			);
		}

		void Write( CBinaryBuffer const &Buffer )
		{ Write( Buffer.GetData(), Buffer.GetSize() ); }

		void Write( size_t nOffset, void const * pFrom, size_t nSize )
		{
			assert( GetSize() - nOffset >= nSize );
			memcpy( GetBuffer() + nOffset, pFrom, nSize );
		}

		CBinaryBuffer & operator << ( cstr_t csValue )
		{
			assert( NULL != csValue );

			uint32_t nLength = static_cast< uint32_t >( strlen( csValue ) );
			*this << nLength;

			Write( csValue, nLength );
			return *this;
		}

		CBinaryBuffer & operator << ( CBinaryBuffer const &Buffer )
		{
			Write( Buffer );
			return *this;
		}

		template< typename T > CBinaryBuffer & operator << ( T const &Value )
		{
			Write( &Value, sizeof( T ) );
			return *this;
		}

	private:

		std::vector< char > m_Buffer;

	};

	class CBinaryBufferReader
	{
	public:

		CBinaryBufferReader( cstr_t pData = NULL, size_t nDataSize = 0 ): m_pData( pData ), m_nDataSize( nDataSize )
		{}

		size_t GetDataSize() const
		{ return m_nDataSize; }

		void SetDataSize( size_t nDataSize )
		{ m_nDataSize = nDataSize; }

		cstr_t GetData() const
		{ return m_pData; }

		void SetData( cstr_t pData )
		{ m_pData = pData; }

		bool IsValid() const
		{ return NULL != m_pData; }

		void Clear()
		{
			m_nDataSize = 0;
			m_pData = NULL;
		}

		void Seek( size_t nSize )
		{
			assert( nSize <= GetDataSize() );
			m_nDataSize -= nSize;
		}

		bool operator == ( CBinaryBufferReader const &Reader ) const
		{ return GetData() == Reader.GetData() && GetDataSize() == Reader.GetDataSize(); }

		template< typename T > result_t Read( T &Value )
		{
			if ( GetDataSize() < sizeof( T ) )
				return result_fail;

			*this >> Value;

			return result_ok;
		}

		CBinaryBufferReader & operator >> ( std::string &sValue )
		{
			sValue.clear();

			uint32_t nLength;
			(*this) >> nLength;

			if ( nLength ) {

				if ( nLength > GetDataSize() )
					throw std::logic_error( "BinaryBuffer: Not enough data to read" );

				sValue.resize( nLength );
				memcpy( &sValue[ 0 ], m_pData, nLength );

				m_pData += nLength;
				m_nDataSize -= nLength;

			}

			return *this;
		}

		template< typename T > CBinaryBufferReader & operator >> ( T &Value )
		{
			if ( GetDataSize() < sizeof( T ) )
				throw std::logic_error( "BinaryBuffer: Not enough data to read" );

			memcpy( &Value, m_pData, sizeof( T ) );
			m_pData += sizeof( T );
			m_nDataSize -= sizeof( T );

			return *this;
		}

	private:

		cstr_t m_pData;
		size_t m_nDataSize;

	};

} // namespace nvl

#endif // __BINARYBUFFER_H_INCLUDED__302310__
