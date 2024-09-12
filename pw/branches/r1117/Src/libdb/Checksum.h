#pragma once
#include "../System/MetaProg.h"
#include "System/DefaultTypes.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
DWORD GetDefaultCheckSum();
DWORD CalcCheckSum( const DWORD dwLastCheckSum, const BYTE *pBuf, const int nLen );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CCheckSum
{
	DWORD dwCheckSum;
	IBinSaver *pSaver;
	
	char CCDECL TestType(...) { return 0; }	
	int CCDECL TestType( string* ) { return 0; }
	int CCDECL TestType( wstring* ) { return 0; }
	template<class T1>
	int CCDECL TestType( vector<T1>* ) { return 0; }

	template<class T>
	void DataCheckSum( T *p, const int nLen )
	{
		dwCheckSum = CalcCheckSum( dwCheckSum, (const BYTE*)p, nLen );
	}

	template<class T>
	void CCDECL SeparateCheckSum( const T &data, Meta::Int2Type<1> *pp )
	{
		DataCheckSum( &data, sizeof( T ) );
	}

	template<class T>
	void CCDECL SeparateCheckSum( const T &data, Meta::Int2Type<4> *pp )
	{
		const DWORD dataCheckSum = data.CalcCheckSum();
		dwCheckSum = CalcCheckSum( dwCheckSum, (const BYTE*)&dataCheckSum, sizeof(DWORD) );
	}
public:
	CCheckSum() : dwCheckSum( GetDefaultCheckSum() ), pSaver( 0 ) { }

	template<class T>
	CCheckSum& operator<<( const T &data )
	{
		// this is a compile-time construction - no run-time calculations performed
		const int N_HAS_SERIALIZE_TEST = sizeof( *((T*)0) & (*pSaver) );
		Meta::Int2Type<N_HAS_SERIALIZE_TEST> separator;
		SeparateCheckSum( data, &separator );
		return *this;
	}
	
	template<class T>
	CCheckSum& operator<<( const vector<T> &vec )
	{
		const int nSize = vec.size();
		DataCheckSum( &nSize, sizeof( nSize ) );
		if ( nSize == 0 )
			return *this;
		//
		if ( sizeof( TestType((T*)0) ) == 1 && sizeof( *((T*)0) & (*pSaver) ) == 1 )
			DataCheckSum( &(vec[0]), vec.size() * sizeof(T) );
		else
		{
			for ( typename vector<T>::const_iterator iter = vec.begin(); iter != vec.end(); ++iter )
				(*this) << *iter;
		}

		return *this;
	}

	CCheckSum& operator<<( const string &sz )
	{
		const int nSize = sz.size();
		DataCheckSum( &nSize, sizeof(nSize) );
		if ( nSize != 0 )
			DataCheckSum( &(sz[0]), sz.size() * sizeof(sz[0]) );

		return *this;
	}

	CCheckSum& operator<<( const wstring &wsz ) 
	{
		const int nSize = wsz.size();
		DataCheckSum( &nSize, sizeof( nSize ) );
		if ( nSize != 0 )
			DataCheckSum( &(wsz[0]), wsz.size() * sizeof(wsz[0]) );

		return *this;
	}

	const DWORD GetCheckSum() const { return dwCheckSum; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

