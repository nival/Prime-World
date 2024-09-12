#ifndef __TEXTYBUFFER_H_INCLUDED__961524__
#define __TEXTYBUFFER_H_INCLUDED__961524__

#include "stdafx.h"
#include "BinaryBuffer.h"
#include "StrUtils.h"
#include <vector>

namespace nvl {

	class CTextBuffer
	{
	public:

		size_t GetCapacity() const
		{ return m_Buffer.GetCapacity(); }

		void Reserve( size_t nSize )
		{ m_Buffer.Reserve( nSize ); }

		size_t GetSize() const
		{ return m_Buffer.GetSize(); }

		void Resize( size_t nSize )
		{ m_Buffer.Resize( nSize ); }

		void Clear()
		{ Resize( 0 ); }

		CTextBuffer & operator << ( cstr_t csString )
		{
			m_Buffer.Write( csString, strlen( csString ) );
			return *this;
		}

		CTextBuffer & operator << ( std::string const &csString )
		{
			m_Buffer.Write( csString.c_str(), csString.length() );
			return *this;
		}

		CTextBuffer & operator << ( CTextBuffer const &Buffer )
		{
			m_Buffer.Write( Buffer.GetData(), Buffer.GetSize() );
			return *this;
		}

		template< typename T > CTextBuffer & operator << ( T const &Value )
		{ return Write( Value ); }

		str_t GetBuffer()
		{ return m_Buffer.GetBuffer(); }

		cstr_t GetData() const
		{ return m_Buffer.GetData(); }

		CTextBuffer & Write( char const nValue )
		{
			m_Buffer << nValue;
			return *this;
		}

		CTextBuffer & Write( int const nValue )
		{
			Write( int64_t( nValue ) );
			return *this;
		}

		CTextBuffer & Write( int64_t const nValue )
		{
			char Buffer[ 24 ];
      NStr::Printf( Buffer, sizeof( Buffer ), "%I64i", nValue );
			m_Buffer.Write( Buffer, NStr::Len( Buffer ) );

			return *this;
		}

	private:

		CBinaryBuffer m_Buffer;

	};

} // namespace nvl

#endif // __TEXTYBUFFER_H_INCLUDED__961524__
