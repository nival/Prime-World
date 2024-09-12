#ifndef _XML_SAVER_H_
#define _XML_SAVER_H_

#include "Placement.h"
#include "../System/nlist.h"
#include "../System/MetaProg.h"

namespace NFile
{
	class CFilePath;
}

namespace Render
{
	class HDRColor;
}

namespace NDb
{
  template <class T>  struct KnownEnum;
  class DbResource;
  class DBID;
  template<class TDbResource> class Ptr;
}

class CTextRef;

template <class T> class CArray2D;

#ifdef WIN32
  #define CCDECL    __cdecl
#else
#ifndef CCDECL
  #define CCDECL    __attribute__ ((cdecl))
#endif
#endif  

struct IXmlSaver;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct IResourceReader
{
  virtual ~IResourceReader() {};
  virtual NDb::Ptr<NDb::DbResource> Read( const NDb::DBID& dbid, IXmlSaver& saver ) = 0;
  virtual void Write( const NDb::DBID& dbid, const NDb::DbResource* pResource, IXmlSaver& saver ) = 0;
  virtual bool NeedPrecacheTexts() = 0;
  virtual bool LoadResources() = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XmlSaver
struct IXmlSaver : public CObjectBase
{
  enum EReadResult
  {
    RR_ADD,
    RR_SKIP,
    RR_DELETE,
  };

	typedef const char* chunk_id;
private:
	char CCDECL TestDataPath(...) { return 0; }
	template<class T1>
		int CCDECL TestDataPath( CArray2D<T1>* ) { return 0; }
	template<class T1>
		int CCDECL TestDataPath( basic_string<T1>* ) { return 0; }
	template<class T1>
		int CCDECL TestDataPath( vector<T1>* ) { return 0; }
	template<class T1>
		int CCDECL TestDataPath( list<T1>* ) { return 0; }
	template<class T1, class T2, class T3>
		int CCDECL TestDataPath( hash_map<T1, T2, T3>* ) { return 0; }

	// add boolean built-in type
	template <class TYPE>
		void AddBoolData( chunk_id idChunk, TYPE *pData, int nChunkNumber ) 
		{ 
			bool bData = *pData;
			const bool bRetVal = DataChunk( idChunk, &bData, nChunkNumber );
			if ( IsReading() && bRetVal ) 
				*pData = TYPE( bData );
		}
	// add integer built-in types
	template <class TYPE>
		void AddIntData( chunk_id idChunk, TYPE *pData, int nChunkNumber ) 
		{ 
			int nData = *pData;
			const bool bRetVal = DataChunk( idChunk, &nData, nChunkNumber );
			if ( IsReading() && bRetVal ) 
				*pData = TYPE( nData );
		}
	// add fp built-in types
	template <class TYPE>
		void AddFPData( chunk_id idChunk, TYPE *pData, int nChunkNumber ) 
		{ 
			float fData = *pData;
			const bool bRetVal = DataChunk( idChunk, &fData, nChunkNumber );
			if ( IsReading() && bRetVal ) 
				*pData = TYPE( fData );
		}
	//
	template<class T>
		void CCDECL CallObjectSerialize( const chunk_id idChunk, int nChunkNumber, T *p, ... )
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			p->operator&( *this );
			FinishChunk();
		}
	// enum or raw object?
	template<class T>
		void CCDECL CallRawObjectSerialize( const chunk_id idChunk, int nChunkNumber, T *p, Meta::Int2Type<1> *pp )
		{
			if ( StartChunk(idChunk, nChunkNumber) != false )
			{
				string szValue;
				if ( IsReading() )
				{
					DataChunkString( szValue );
					*p = NDb::KnownEnum<T>::ToEnum( szValue );
				}
				else
				{
					szValue = NDb::KnownEnum<T>::ToString( *p );
					DataChunkString( szValue );
				}
				FinishChunk();
			}
		}
	template<class T>
		void CCDECL CallRawObjectSerialize( const chunk_id idChunk, int nChunkNumber, T *p, Meta::Int2Type<0> *pp )
		{
			DataChunk( idChunk, p, sizeof(T), nChunkNumber );
		}
	template<class T>
		void CCDECL CallObjectSerialize( const chunk_id idChunk, int nChunkNumber, T *p, Meta::Int2Type<1> *pp )
		{
			const int N_KNOWN_ENUM = NDb::KnownEnum<T>::isKnown;
			Meta::Int2Type<N_KNOWN_ENUM> separator;
			CallRawObjectSerialize( idChunk, nChunkNumber, p, &separator );
		}
	//
	template<class T>
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, ... )
		{
			const int N_HAS_SERIALIZE_TEST = sizeof( (*p) & (*this) );
			Meta::Int2Type<N_HAS_SERIALIZE_TEST> separator;
			CallObjectSerialize( idChunk, nChunkNumber, p, &separator );
		}
	// file path reference (must be before string due to it is derived from it)
	template <class T> 
		void AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, CTextRef *pData ) 
		{
			if ( !StartChunk( idChunk, nChunkNumber ) )
				return;
			DataChunkTextRef( pData );
			FinishChunk();
		}
	template <class T> 
		void AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, NFile::CFilePath *pData ) 
		{
			if ( !StartChunk( idChunk, nChunkNumber ) )
				return;
			DataChunkFilePath( pData );
			FinishChunk();
		}
	template <class T, class T1>
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, basic_string<T1> *pStr ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			DataChunkString( *pStr );
			FinishChunk();
		}
	template<class T,class T1>
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, CArray2D<T1> *pArr ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			if ( sizeof( TestDataPath(&(*pArr)[0][0]) ) == 1 && sizeof( (*pArr)[0][0]&(*this) ) == 1 )
				Do2DArrayData( *pArr );
			else
				Do2DArray( *pArr );
			FinishChunk();
		}
	template <class T, class T1>
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, vector<T1> *pVec ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			/*
			if ( sizeof( TestDataPath(&(*pVec)[0]) ) == 1 && sizeof( (*pVec)[0]&(*this) ) == 1 )
				DoDataVector( *p );
			else
			*/
				DoVector( *p );
			FinishChunk();
		}
  // probably this specicialization is not required		
  #ifdef WIN32
	template <class T, class T1>
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, nstl::list<T1> *pList ) 
	{
		if ( !StartChunk(idChunk, nChunkNumber) )
			return;
		nstl::list<T1> &data = *pList;
		if ( IsReading() )
		{
			pList->clear();
			pList->insert( data.begin(), CountChunks(), T1() );
		}
		int i = 1;
		nstl::list<T1>::iterator it;
		for (it = data.begin(); it != data.end(); ++it, ++i )
			Add( "Item", &(*it), i );
		FinishChunk();
	}
	#endif
	
	template<class T,class T1, class T2, class T3>
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, hash_map<T1,T2,T3> *pHash ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			DoHashMap( *pHash );
			FinishChunk();
		}
	template <class T, class T1, class T2> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, pair<T1, T2> *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "First", &( pData->first ) );
			Add( "Second", &( pData->second ) );
			FinishChunk();
		}
	template <class T> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, CVec2 *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "x", &( pData->x ) );
			Add( "y", &( pData->y ) );
			FinishChunk();
		}
	template <class T> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, CVec3 *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "x", &( pData->x ) );
			Add( "y", &( pData->y ) );
			Add( "z", &( pData->z ) );
			FinishChunk();
		}
		template <class T> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, CVec4 *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "x", &( pData->x ) );
			Add( "y", &( pData->y ) );
			Add( "z", &( pData->z ) );
			Add( "w", &( pData->w ) );
			FinishChunk();
		}
		template <class T> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, Matrix43 *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "x1", &( pData->_11 ) );
			Add( "y1", &( pData->_12 ) );
			Add( "z1", &( pData->_13 ) );
			Add( "w1", &( pData->_14 ) );
			Add( "x2", &( pData->_21 ) );
			Add( "y2", &( pData->_22 ) );
			Add( "z2", &( pData->_23 ) );
			Add( "w2", &( pData->_24 ) );
			Add( "x3", &( pData->_31 ) );
			Add( "y3", &( pData->_32 ) );
			Add( "z3", &( pData->_33 ) );
			Add( "w3", &( pData->_34 ) );
			FinishChunk();
		}
		#ifdef WIN32
		template <class T> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, Render::HDRColor *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "R", &( pData->R ) );
			Add( "G", &( pData->G ) );
			Add( "B", &( pData->B ) );
			Add( "A", &( pData->A ) );
			FinishChunk();
		}
		#endif

	template <class T> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, CQuat *pData ) 
		{
			AddInternal( idChunk, nChunkNumber, p, const_cast<CVec4*>( &pData->GetInternalVector() ) );
		}
	template <class T> 
	void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, Render::Color *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "R", &( pData->R ) );
			Add( "G", &( pData->G ) );
			Add( "B", &( pData->B ) );
			Add( "A", &( pData->A ) );
			FinishChunk();
		}
	template <class T, class T1> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, CTRect<T1> *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "x1", &( pData->x1 ) );
			Add( "y1", &( pData->y1 ) );
			Add( "x2", &( pData->x2 ) );
			Add( "y2", &( pData->y2 ) );
			FinishChunk();
		}
	template <class T, class T1> 
		void CCDECL AddInternal( const chunk_id idChunk, int nChunkNumber, T *p, CTPoint<T1> *pData ) 
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			Add( "x", &( pData->x ) );
			Add( "y", &( pData->y ) );
			FinishChunk();
		}
	// vector
	template <class T> 
		void DoVector( vector<T> &data )
		{
			int i, nSize = 0;
			if ( IsReading() )
			{
        nSize = max( CountChunks(), data.size() );
				data.resize( nSize );
			}
			else
      {
				nSize = data.size();
      }
      int addIdx = 0;
      for ( i = 0; i < nSize; ++i, ++addIdx )
      {
        Add( "Item", &data[addIdx], i + 1 );
        if ( GetCurrentReadResult() == RR_DELETE )
        {
          data.erase( data.begin() + addIdx );
          addIdx--;
        }
      }
		}
	template <class T> 
		void DoDataVector( vector<T> &data )
		{
			int nSize = data.size();
			Add( "Size", &nSize );
			if ( IsReading() )
			{
				data.clear();
				data.resize( nSize );
			}
			if ( nSize > 0 )
				DataChunk( "Data", &data[0], sizeof(T) * nSize, 0 );
		}
  #ifdef WIN32		
	// hash_map
	template <class T1, class T2, class T3> 
		void DoHashMap( hash_map<T1, T2, T3> &data )
		{
			if ( IsReading() )
			{
				data.clear();
				const int nSize = CountChunks();
				vector<T1> indices;
				indices.resize( nSize );
				for ( int i = 0; i < nSize; ++i )
				{
					if ( StartChunk("Item", i + 1) ) 
					{
						Add( "Key", &indices[i] );
						Add( "Data", &data[ indices[i] ] );
						FinishChunk();
					}
				}
			}
			else
			{
				int i = 1;
				for ( hash_map<T1, T2, T3>::iterator pos = data.begin(); pos != data.end(); ++pos, ++i )
				{
					if ( StartChunk("Item", i) ) 
					{
						T1 idx = pos->first;
						Add( "Key", &idx );
						Add( "Data", &pos->second );
						FinishChunk();
					}
				}
			}
		}
  #endif
  		
	// 2D Array
	template <class T> 
		void Do2DArray( CArray2D<T> &a )
		{
			int nSizeX = a.GetSizeX(), nSizeY = a.GetSizeX();
			Add( "SizeX", &nSizeX );
			Add( "SizeY", &nSizeY );
			if ( StartChunk("Data", 0) )
			{
				if ( IsReading() )
					a.SetSizes( nSizeY, nSizeY );
				//
				for ( int i = 0; i < nSizeX * nSizeY; i++ )
					Add( "Item", &a[i/nSizeX][i%nSizeX], i + 1 );
				FinishChunk();
			}
		}
	template <class T> 
		void Do2DArrayData( CArray2D<T> &a )
		{
			int nSizeX = a.GetSizeX(), nSizeY = a.GetSizeX();
			Add( "SizeX", &nSizeX );
			Add( "SizeY", &nSizeY );
			if ( IsReading() )
				a.SetSizes( nSizeX, nSizeY );
			if ( nSizeX * nSizeY > 0 )
				DataChunk( "Data", &a[0][0], sizeof(T) * nSizeX * nSizeY, 0 );
		}

	virtual bool DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber ) = 0;
	virtual bool DataChunk( const chunk_id idChunk, int *pnData, int nChunkNumber ) = 0;
	virtual bool DataChunk( const chunk_id idChunk, float *pfData, int nChunkNumber ) = 0;
	virtual bool DataChunk( const chunk_id idChunk, bool *pData, int nChunkNumber ) = 0;
	#ifdef WIN32
	virtual bool DataChunk( const chunk_id idChunk, GUID *pgData, int nChunkNumber ) = 0;
  #endif	  
	virtual bool DataChunkFilePath( NFile::CFilePath *pFilePath ) = 0;
	virtual bool DataChunkTextRef( CTextRef *pTextRef ) = 0;
	virtual bool DataChunkString( string &data ) = 0;
	virtual bool DataChunkString( wstring &data ) = 0;
  //

  virtual EReadResult GetCurrentReadResult() const = 0;

public:
	// add raw data of specified size (in bytes)
	void AddRawData( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber = 0 ) { DataChunk( idChunk, pData, nSize, nChunkNumber ); }

  // main add function - add all structures/classes/datas through it
	template<class T>
	  void Add( const chunk_id idChunk, T *p, int nChunkNumber = 0 )
    {
      AddInternal( idChunk, nChunkNumber, p, p );
    }

  // adding typed super class - use it only for super class members serialization
	template <class T>
	  void AddTypedSuper( T *pData )
	  {
		  if ( !StartChunk(0, 0) )
			  return;
		  pData->T::operator&( *this );
		  FinishChunk();
	  }

  template <class T>
	  void AddPolymorphicBase( const chunk_id idChunk, T *pData, int nChunkNumber = 0 )
	  {
		  if ( !StartChunk( idChunk, nChunkNumber ) )
			  return;
		  if ( pData )
			  pData->operator&( *this );
		  FinishChunk();
	  }

  virtual bool IsReading() const = 0;
	//virtual const string& GetFileName() const = 0;

	virtual bool StartChunk( const chunk_id idChunk, int nChunkNumber ) = 0;
  virtual int CountChunks() = 0;
	virtual void FinishChunk() = 0;

	virtual void SetSourceFileName( const string & fileName ) = 0;
	virtual const string& GetSourceFileName() const = 0;
	virtual void SetSourceId( const string & id ) = 0;
	virtual const string& GetSourceId() const = 0;

  virtual void SetHrefIdAttributes( const string &href, const string &id ) = 0;

  virtual const string GetTypeOfNextElement() const = 0;

	virtual const bool IsComplexNextElement() const = 0;

	virtual const bool HasHRefAttr() const = 0;
	virtual const string GetHRefAttrValue() const = 0;

  virtual const bool HasIdAttr() const = 0;
	virtual const string GetIdAttrValue() const = 0;

  virtual const bool HasAnimatedAttr() const = 0;
  virtual const bool HasParentAttr() const = 0;
  virtual const string GetParentAttrValue() const = 0;

  virtual const string GetStateNameAttrValue() const = 0;
		
  virtual IResourceReader* GetResourceReader() const = 0;
};

// simple built-in data specialization
#ifdef WIN32
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<GUID>( const chunk_id idChunk, int nChunkNumber, GUID *pData, Meta::Int2Type<1> * )
{
  DataChunk( idChunk, pData, nChunkNumber );
}
#endif

template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<bool>( const chunk_id idChunk, int nChunkNumber, bool *pData, Meta::Int2Type<1> * )
{
  AddBoolData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<char>( const chunk_id idChunk, int nChunkNumber, char *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<signed char>( const chunk_id idChunk, int nChunkNumber, signed char *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<unsigned char>( const chunk_id idChunk, int nChunkNumber, unsigned char *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<short>( const chunk_id idChunk, int nChunkNumber, short *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<unsigned short>( const chunk_id idChunk, int nChunkNumber, unsigned short *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<long>( const chunk_id idChunk, int nChunkNumber, long *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<unsigned long>( const chunk_id idChunk, int nChunkNumber, unsigned long *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<int>( const chunk_id idChunk, int nChunkNumber, int *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<unsigned int>( const chunk_id idChunk, int nChunkNumber, unsigned int *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<float>( const chunk_id idChunk, int nChunkNumber, float *pData, Meta::Int2Type<1> * )
{
  AddFPData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IXmlSaver::CallObjectSerialize<double>( const chunk_id idChunk, int nChunkNumber, double *pData, Meta::Int2Type<1> * )
{
  AddFPData( idChunk, pData, nChunkNumber );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
inline char operator&( T &c, IXmlSaver &ss ) { return 0; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IXmlSaver *CreateXmlSaver( Stream *pStream, bool reading, IResourceReader* pResourceHandler = 0 );
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

