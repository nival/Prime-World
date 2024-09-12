#ifndef BINSAVER_H_437085EA_F184_4ED3_B0
#define BINSAVER_H_437085EA_F184_4ED3_B0

#include <System/DefaultTypes.h>
#include "MetaProg.h"
#include "System/Pointers/Pointers.h"
#include "BinSaverStatsCollector.h"
#include "System/Ring.h"
#include "StarForce/HiddenVars.h"
#include "System/nfixed_string.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DONOT_REGISTER_SAVELOAD_CLASS

#define REGISTER_SAVELOAD_CLASS( name )				                             \
	BASIC_REGISTER_CLASS( name )								                             \
	STATIC_CTOR_BEGIN() {                                                    \
		REGISTER_CLASS( name::typeId, name );			                             \
	 } STATIC_CTOR_END() 


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_SAVELOAD_CLASS_NM( name, nmspace )					                \
	BASIC_REGISTER_CLASS( nmspace::name )	                                    \
	STATIC_CTOR_BEGIN() {                                                     \
    REGISTER_CLASS_NM( nmspace::name::typeId, name, nmspace )               \
  } STATIC_CTOR_END()  


#define ZDATA_(a)
#define ZDATA
#define ZSTRUCT
#define ZPARENT(a)
#define ZNOPARENT(a)
#define ZEND
#define ZSKIP
#define ZONSERIALIZE
#define ZNOCRC
#define ZNOCRCEND
#define ZNOMAPOBJECT
#define ZNOMAPOBJECTEND


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CONTAINER_SIZE_VERIFY( size, doOnErr )                               \
{ if (!CheckContainerSize( size ))                                           \
  { SetError(BINSAVER_ERR_CONTAINER_SIZE_LIMIT); { doOnErr; } } }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE_VERIFY( size, doOnErr )                               \
{ totalSize += size;                                               \
  if (!CheckSize())                                          \
  { SetError(BINSAVER_ERR_SIZE_LIMIT); { doOnErr; } } }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class CArray2D;

#if !defined(_SHIPPING) && 0
  #define BIN_SAVER_USE_PROFILER
#endif

class Stream;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: This is not an interface! Should be renamed to BaseBinSaver
struct IBinSaver : public CObjectBase
{
public:
	typedef unsigned char chunk_id;

	enum ChunkType
	{
		CHUNK_DATA, //0
		CHUNK_SERIALIZABLE_OBJECT, //1
		CHUNK_PTR, //2
		CHUNK_STRING,
		CHUNK_WSTRING,
		CHUNK_MEMORYSTREAM,
		CHUNK_MEMORYSTREAM_DATA,
		CHUNK_VECTOR,
		CHUNK_HASHMAP,
		CHUNK_RING,
		CHUNK_MAP,
		CHUNK_STATICARRAYY,
		CHUNK_HASHSET,
		CHUNK_SET, //13
		CHUNK_ARRAY2D, //14
		CHUNK_LIST, //15
		CHUNK_PAIR, //16
		CHUNK_COBJECTBASE, //17
		CHUNK_FORCESTR, //18
		CHUNK_FIXED_STRING, // 19
		CHUNK_FIXED_WSTRING, // 20
	};

  enum ErrorType
  {
    BINSAVER_ERR_OK           = 0,
    BINSAVER_ERR_READ_FAILED  = 1,
    BINSAVER_ERR_CONTAINER_SIZE_LIMIT   = 2,
    BINSAVER_ERR_SIZE_LIMIT = 3,
  };

  IBinSaver() : totalSizeLimit(0), totalSize(0), containerSizeLimit(0), error(BINSAVER_ERR_OK) {}
  IBinSaver(const uint _containerSizeLimit) : containerSizeLimit(_containerSizeLimit), totalSizeLimit(0), totalSize(0), error(BINSAVER_ERR_OK) {}
  IBinSaver(const uint _containerSizeLimit, const uint _totalSizeLimit) : 
      containerSizeLimit(_containerSizeLimit), totalSizeLimit(_totalSizeLimit), totalSize(0), error(BINSAVER_ERR_OK) {}

private:
	template<bool isObjectBase, typename T>
	struct ObjectTypeId
	{
		enum { typeId = T::typeId };
	};

	template<typename T>
	struct ObjectTypeId<false, T>
	{
		enum { typeId = CHUNK_SERIALIZABLE_OBJECT };
	};

	template<class T>
	void CCDECL CallObjectSerialize( const chunk_id idChunk, int nChunkNumber, T *p, Meta::Int2Type<1> )
	{
		if ( !StartChunk( idChunk, nChunkNumber, ObjectTypeId<Meta::SuperSubclass<CObjectBase, T>::value, T>::typeId ) )
			return;
		p->T::operator&( *this );

    FinishChunk();
	}

	template<class T>
	void CCDECL CallObjectSerialize( const chunk_id idChunk, int nChunkNumber, T *p, Meta::Int2Type<0> )
	{
		DataChunkImplKnownSize<sizeof(T)>( idChunk, p, nChunkNumber );
	}

	template <class T> 
	void DoVector( vector<T> &data )
	{
#if defined( NV_WIN_PLATFORM )
		int i, nSize;
#elif defined( NV_LINUX_PLATFORM )
        int i;
        nival::int32_t nSize;
#endif
		if ( IsReading() )
		{
		  vector<T> oldData;
			swap( oldData, data );
			Add( 2, &nSize );
      CONTAINER_SIZE_VERIFY( nSize, return; );
			data.resize( nSize );
		}
		else
		{
			nSize = data.size();
			Add( 2, &nSize );
		}
		for ( i = 0; i < nSize; i++ )
			Add( 1, &data[i], i + 1 );
	}

	template <class T> 
	void DoDataVector( vector<T> &data )
	{
#if defined( NV_WIN_PLATFORM )
		int nSize = data.size();
#elif defined( NV_LINUX_PLATFORM )
        nival::int32_t nSize = data.size();
#endif
		Add( 1, &nSize );
		if ( IsReading() )
		{
      CONTAINER_SIZE_VERIFY( nSize, return; );
			data.clear();
			data.resize( nSize );
		}
		if ( nSize > 0 )
			DataChunkImpl( 2, &data[0], sizeof(T) * nSize, 1 );
	}

	// Serializer by data
	template <int N> 
	struct RingSerializer
	{
		template <class T, class C, class R>
		static int Write(IBinSaver *pSaver, ::ring::Ring<T, C, R> &data)
		{
			int nI = 1;
			T * pElemLast = data.last();
			for (T *pRingElem = data.first(); pRingElem != pElemLast;)
			{
				pSaver->Add( 2, pRingElem, nI );
				pRingElem = data.next(pRingElem);
				nI++;
			}
			
			return nI;
		}

		template <class T, class C, class R>
		static void Read(IBinSaver *pSaver, ::ring::Ring<T, C, R> &data, int nCount)
		{
			for(int nI = 1; nI <= nCount; nI++)
			{
				T *pRingElem = new T;
				pSaver->Add( 2, pRingElem, nI );
				data.addLast(pRingElem);
			}
		}
	};

  template<class T, class C, class R>
  void DoRing(::ring::Ring<T, C, R> &data )
  {
    T * pRingElem = NULL; 
    
    if( IsChecksum() )
    {
      //Читерская оптимизация позволяющая отказаться от вычисления nCount
      int nCount = RingSerializer<R::SerializeByPointer>::Write(this, data);
      Add(3, &nCount);
    }
    else if(!IsReading())
    {
      T * pElemLast = data.last();
      int nCount = 0;
      for (pRingElem = data.first(); pRingElem != pElemLast;)
      {
        pRingElem = data.next(pRingElem);
        nCount++;
      }
      Add(1, &nCount);
			RingSerializer<R::SerializeByPointer>::Write(this, data);
    }
    else
    {
      Clear(data);
      int nCount = 0;
      Add(1, &nCount);
      CONTAINER_SIZE_VERIFY( nCount, return; );
			RingSerializer<R::SerializeByPointer>::Read(this, data, nCount);
    }
  }

	template <typename T, unsigned int _capacity>
	void DoStaticArray( StaticArray<T, _capacity> &arr )
	{
		for (int i = 0; i < _capacity; i++)
			Add(i + 1, &arr[i]);
	}

  template <class Key, class T> 
  void DoMap( map<Key, T> &data )
  {     
    if ( IsReading() )  //deserialization
    {
      //clear the passed variable
      data.clear();

      int nSize = 0;

      //read the size of map
      Add( 1, &nSize );
      CONTAINER_SIZE_VERIFY( nSize, return; );

      //read key:value
      for(int idx = 0; idx < nSize * 2; )
      {        
        Key key;

        Add(2, &key, ++idx );
        typename map<Key, T>::iterator it = data.insert( key );
        Add(2, &(it->second), ++idx ); 
      }
    }
    else  //serialization
    {      
      int num( data.size() );

      //write the size of map
      Add( 1, &num );

      //write key:value
      if ( num > 0 )
      {      
        int idx = 0;
        for(typename map<Key, T>::iterator it = data.begin(); it != data.end(); ++it)
        {
          // Add requires non-const reference, but in write mode it is actually const
          Key& key = const_cast<Key&>((*it).first);
          T& elementValue = (*it).second;

          Add(2, &key, ++idx );
          Add(2, &elementValue, ++idx );        
        }
        NI_ASSERT( idx == num * 2, "Internal error writing map" );
      }
    }
  }

	template <class T1,class T2,class T3> 
	void DoHashMap( hash_map<T1,T2,T3> &data )
	{
		if( IsChecksum() )
		{
		  //Конечно, можно было оптимизировать чтение и запись, но hash_map 
		  //грузится из ресурсов, а влезать в редактор не хотелось
      int nSize = data.size(), nBuckets = data.bucket_count();
      Add( 3, &nSize );
      Add( 4, &nBuckets );

      int idx = 1;
      for ( typename hash_map<T1,T2,T3>::iterator pos = data.begin(); pos != data.end(); ++pos, ++idx )
      {
        Add( 1, const_cast<T1 *>(&pos->first), idx );
        Add( 2, &pos->second, idx );
      }
		}
		else if ( IsReading() )
		{
			hash_map<T1,T2,T3> oldData;
			swap( oldData, data );

			int nSize, i;
			Add( 3, &nSize );
      CONTAINER_SIZE_VERIFY( nSize, return; );

			int nBuckets;
			Add( 4, &nBuckets );
      CONTAINER_SIZE_VERIFY( nBuckets, return; );
			data.set_bucket_count( nBuckets );

			vector<T1> indices;
			indices.resize( nSize );
			for ( i = 0; i < nSize; ++i )
				Add( 1, &indices[i], i + 1 );
			for ( i = 0; i < nSize; ++i )
				Add( 2, &data[ indices[i] ], i + 1 );
		}
		else
		{
			int nSize = data.size(), nBuckets = data.bucket_count();
			Add( 3, &nSize );
			Add( 4, &nBuckets );

			vector<T1> indices;
			indices.resize( nSize );
			int i = 1;
			for ( typename hash_map<T1,T2,T3>::iterator pos = data.begin(); pos != data.end(); ++pos, ++i )
				indices[ nSize - i ] = pos->first;
			for ( i = 0; i < nSize; ++i )
				Add( 1, &indices[i], i + 1 );
			for ( i = 0; i < nSize; ++i )
				Add( 2, &data[ indices[i] ], i + 1 );
		}
	}

	template <class T1,class T2> 
	void DoSet( set<T1,T2> &data )
	{
		if ( IsReading() )
		{
			vector<T1> vectorData;
			Add( 1, &vectorData );

			data.clear();
			data.insert( vectorData.begin(), vectorData.end() );
		}
		else
		{
			vector<T1> vectorData( data.begin(), data.end() );
			Add( 1, &vectorData );
		}
	}

	template<class T> 
	void Do2DArray( CArray2D<T> &a )
	{
		int nXSize = a.GetSizeX(), nYSize = a.GetSizeY();
		Add( 1, &nXSize );
    CONTAINER_SIZE_VERIFY( nXSize, return; );
		Add( 2, &nYSize );
    CONTAINER_SIZE_VERIFY( nYSize, return; );
		if ( IsReading() )
			a.SetSizes( nXSize, nYSize );
		for ( int i = 0; i < nXSize * nYSize; i++ )
			Add( 3, &a[i/nXSize][i%nXSize], i + 1 );
	}

	template<class T> 
	void Do2DArrayData( CArray2D<T> &a )
	{
		int nXSize = a.GetSizeX(), nYSize = a.GetSizeY();
		Add( 1, &nXSize );
    CONTAINER_SIZE_VERIFY( nXSize, return; );
		Add( 2, &nYSize );
    CONTAINER_SIZE_VERIFY( nYSize, return; );
		if ( IsReading() )
			a.SetSizes( nXSize, nYSize );
		if ( nXSize * nYSize > 0 )
			DataChunkImpl( 3, &a[0][0], sizeof(T) * nXSize * nYSize, 1 );
	}

  virtual void DataChunkString( string &data ) = 0;
  virtual void DataChunkString( wstring &data ) = 0;

  virtual void DataChunkString( nstl::fixed_string_base<char> &data ) = 0;
  virtual void DataChunkString( nstl::fixed_string_base<wchar_t> &data ) = 0;
public:
  virtual void Reset( Stream* data, bool isReading ) {} // not implemented by default
  virtual Stream* GetStream() = 0;

	virtual bool StartChunk( const chunk_id idChunk, int nChunkNumber, int chunkType ) = 0;
	virtual void FinishChunk() = 0;
	virtual void DataChunk( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber ) = 0;
	
	virtual void DataChunk_1( const chunk_id idChunk, void *pData, int nChunkNumber )
	{
	  DataChunk( idChunk, pData, 1, nChunkNumber );
	}
	
	virtual void DataChunk_4( const chunk_id idChunk, void *pData, int nChunkNumber )
	{
	  DataChunk( idChunk, pData, 4, nChunkNumber );
	}
	
	virtual int CountChunks( const chunk_id idChunk ) = 0;
	
  // storing/loading pointers to objects
	virtual void StoreObject( CObjectBase *pObject ) = 0;
	virtual void StoreObject( const chunk_id idChunk, CObjectBase *pObject ) { NI_ALWAYS_ASSERT("Must been called only in CRC"); }
	virtual CObjectBase* LoadObject() = 0;

  //New pointers version
  //FIXME: get rid of ST/MT copypast
  virtual void StoreObjectST( BaseObjectST * pObject ) = 0;
	virtual BaseObjectST * LoadObjectST() = 0;
  virtual void StoreObjectMT( BaseObjectMT * pObject ) = 0;
	virtual BaseObjectMT * LoadObjectMT() = 0;

	//
	virtual bool IsReading() = 0;
	virtual bool IsChecksum() { return false; }
	//
	void AddRawData( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber = 1 )
	{ 
		DataChunkImpl( idChunk, pData, nSize, nChunkNumber ); 
	}
	//
	template<class T>
	void AddImpl( const chunk_id idChunk, T *p, int nChunkNumber = 1 ) 
	{
		const int N_HAS_SERIALIZE_TEST = sizeof( (*p) & (*this) ) != sizeof(char);
		CallObjectSerialize( idChunk, nChunkNumber, p, Meta::Int2Type<N_HAS_SERIALIZE_TEST>() );
	}

	void AddImpl( const chunk_id idChunk, bool *pBool, int nChunkNumber = 1 );

	void AddImpl( const chunk_id idChunk, string *pStr, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_STRING ) )
			return;
		DataChunkStringImpl( *pStr );
		FinishChunk();
	}

	void AddImpl( const chunk_id idChunk, wstring *pStr, int nChunkNumber = 1 )
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_WSTRING ) )
			return;
		DataChunkStringImpl( *pStr );
		FinishChunk();
	}

	template <size_t N>
	void AddImpl( const chunk_id idChunk, fixed_string<char, N> *pStr, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_FIXED_STRING ) )
			return;
		DataChunkStringImpl( *pStr );
		FinishChunk();
	}

	template <size_t N>
	void AddImpl( const chunk_id idChunk, fixed_string<wchar_t, N> *pStr, int nChunkNumber = 1 )
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_FIXED_WSTRING ) )
			return;
		DataChunkStringImpl( *pStr );
		FinishChunk();
	}

	void AddImpl( const chunk_id idChunk, MemoryStream *pStr, int nChunkNumber = 1 )
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_MEMORYSTREAM ) )
			return;
		int nSize = pStr->GetSize();
		Add( 1, &nSize );
		if ( !StartChunk( 2, 1, CHUNK_MEMORYSTREAM_DATA ) )
		{
			FinishChunk();
			return;
		}
		if ( IsReading() )
			pStr->SetSize( nSize );
		DataChunkImpl( 1, pStr->GetBuffer(), nSize, 1 );
		FinishChunk();
		FinishChunk();
	}

#ifdef WIN32
  #pragma warning( push )
  #pragma warning( disable: 4127 ) //warning C4127: conditional expression is constant
#endif
	template<class T1>
		void AddImpl( const chunk_id idChunk, vector<T1> *pVec, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_VECTOR ) )
			return;
		if ( sizeof( (*pVec)[0] & (*this) ) == sizeof(char) )
			DoDataVector( *pVec );
		else
			DoVector( *pVec );
		FinishChunk();
	}
#ifdef WIN32
  #pragma warning( pop )
#endif

	template<class T1, class T2, class T3>
	void AddImpl( const chunk_id idChunk, hash_map<T1,T2,T3> *pHash, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_HASHMAP ) )
			return;
		DoHashMap( *pHash );
		FinishChunk();
	}

  template<class T, class C, class R>
  void AddImpl( const chunk_id idChunk, ::ring::Ring<T, C, R>* pRing, int nChunkNumber = 1 ) 
  {
    if ( !StartChunk( idChunk, nChunkNumber, CHUNK_RING ) )
      return;
    DoRing<T, C, R>( *pRing);
    FinishChunk();
  }

  template<class Key, class T>
  void AddImpl( const chunk_id idChunk, ::map<Key, T>* pMap, int nChunkNumber = 1 ) 
  {
    if ( !StartChunk( idChunk, nChunkNumber, CHUNK_MAP ) )
      return;
    DoMap<Key, T>( *pMap);
    FinishChunk();
  }

	template<typename T, unsigned int _capacity>
	void AddImpl( const chunk_id idChunk, StaticArray<T, _capacity>* pArr, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_STATICARRAYY ) )
			return;
		DoStaticArray<T, _capacity>(*pArr);
		FinishChunk();
	}

	template<class T1, class T2>
	void AddImpl( const chunk_id idChunk, hash_set<T1,T2> *pHash, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_HASHSET ) )
			return;
		DoHashMap( *pHash );
		FinishChunk();
	}

	template<class T1, class T2>
	void AddImpl( const chunk_id idChunk, set<T1,T2> *pSet, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_SET ) )
			return;
		DoSet( *pSet );
		FinishChunk();
	}

	template<class T1>
	void AddImpl( const chunk_id idChunk, CArray2D<T1> *pArr, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_ARRAY2D ) )
			return;
		if ( sizeof( (*pArr)[0][0] & (*this) ) == sizeof(char) )
			Do2DArrayData( *pArr );
		else
			Do2DArray( *pArr );
		FinishChunk();
	}

	template<class T1>
	void AddImpl( const chunk_id idChunk, list<T1> *pList, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_LIST ) )
			return;
		list<T1> &data = *pList;
		if ( IsReading() )
		{
			int nSize;
			Add( 2, &nSize );
			data.clear();
			data.insert( data.begin(), nSize, T1() );
		}
		else
		{
			int nSize = data.size();
			Add( 2, &nSize );
		}
		int i = 1;
		for ( typename list<T1>::iterator k = data.begin(); k != data.end(); ++k, ++i )
			Add( 1, &(*k), i );
		FinishChunk();
	}

	template <class T1, class T2> 
	void AddImpl( const chunk_id idChunk, pair<T1, T2> *pData, int nChunkNumber = 1 ) 
	{
		if ( !StartChunk( idChunk, nChunkNumber, CHUNK_PAIR ) )
			return;
		Add( 1, &( pData->first ) );
		Add( 2, &( pData->second ) );
		FinishChunk();
	}

	void AddPolymorphicBase( chunk_id idChunk, CObjectBase *pObject, int nChunkNumber = 1 ) 
	{
	  statsCollector.StartTypePoly(*pObject);
	    
		if ( StartChunk( idChunk, nChunkNumber, CHUNK_COBJECTBASE ) )
		{
		  (*pObject)&(*this);
		  FinishChunk();
		}
		
		statsCollector.FinishTypePoly(*pObject);
	}
	
  void AddPolymorphicBaseWithoutChunks( CObjectBase *pObject ) 
  {
    statsCollector.StartTypePoly(*pObject);
    (*pObject)&(*this);
    statsCollector.FinishTypePoly(*pObject);
  }

  template< class TUserObj, class TRef>
  void AddImpl( const chunk_id idChunk, CPtrBase<TUserObj, TRef> *pPtr, int nChunkNumber )
  {
    if( IsChecksum() )
    {
      //Оптимизация позволяет не создавать чанк на каждый указатель
      //Не хотелось менять другие классы, поэтому используется только для
      //контрольной суммы
      StoreObject( idChunk, pPtr->GetBarePtr() );
      return;
    }
    
    typedef CPtrBase<TUserObj, TRef> TPtr;

    if ( !StartChunk( idChunk, nChunkNumber, ObjectTypeId<Meta::SuperSubclass<CObjectBase, TPtr>::value, TPtr>::typeId ) )
      return;

    else if ( IsReading() ) 
      pPtr->SetPtr( CastToUserObject( LoadObject(), (TUserObj*)0 ) ); 
    else 
      StoreObject( pPtr->GetBarePtr() );

    FinishChunk();
  }
  
  template<class T>
  void AddImpl( const chunk_id idChunk, CPtr<T> *pPtr, int nChunkNumber )
  {
    AddImpl( idChunk, static_cast<typename CPtr<T>::TBase *>(pPtr), nChunkNumber );
  }
  
  template<class T>
  void AddImpl( const chunk_id idChunk, CObj<T> *pPtr, int nChunkNumber )
  {
    AddImpl( idChunk, static_cast<typename CObj<T>::TBase *>(pPtr), nChunkNumber );
  }

  template<class T>
  void AddImpl( const chunk_id idChunk, ConstPtr<T> *pPtr, int nChunkNumber )
  {
    AddImpl( idChunk, static_cast<typename ConstPtr<T>::TBase *>(pPtr), nChunkNumber );
  }
  
  template< class HiddenVarT >
  void AddImplHiddenVar( const chunk_id idChunk, HiddenVarT *pHiddenVar, int nChunkNumber )
  {
    if( IsReading() )
    {
      typename HiddenVarT::TOrigin tmp;
      AddImpl( idChunk, &tmp, nChunkNumber );
      *pHiddenVar = tmp;
    }
    else
    {   
      typename HiddenVarT::TOrigin tmp(*pHiddenVar);
      AddImpl( idChunk, &tmp, nChunkNumber ); 
    }
  }

  template< class OriginT, class StorageT, int UniqNum >
  void AddImpl( 
    const chunk_id idChunk, 
    Protection::Detail::HiddenVarImpl<OriginT, StorageT, UniqNum> *pHiddenVar, 
    int nChunkNumber 
  )
  {
    AddImplHiddenVar( idChunk, pHiddenVar, nChunkNumber );
  }
   
  template< int UniqNum >
  void AddImpl( 
    const chunk_id idChunk, 
    Protection::Detail::Vec2<UniqNum> *pHiddenVar, 
    int nChunkNumber 
  )
  {
    AddImplHiddenVar( idChunk, pHiddenVar, nChunkNumber );
  } 
  
  template< int UniqNum >
  void AddImpl( 
    const chunk_id idChunk, 
    Protection::Detail::Vec3<UniqNum> *pHiddenVar, 
    int nChunkNumber 
  )
  {
    AddImplHiddenVar( idChunk, pHiddenVar, nChunkNumber );
  } 
   
  template <class T> 
  void DoStrong( Strong<T> * ptr ) 
  {
    if ( IsReading() ) 
    {
      IBaseInterfaceST * iobj = LoadObjectST();
      ptr->Set( nival_cast<T>( iobj ) );
    }
    else
      StoreObjectST( ptr->GetBaseObject() );
  }

  template <class T> 
  void DoStrong( StrongMT<T> * ptr ) 
  {
    if ( IsReading() ) 
    {
      IBaseInterfaceMT * iobj = LoadObjectMT();
      ptr->Set( nival_cast<T>( iobj ) );
    }
    else
      StoreObjectMT( ptr->GetBaseObject() );
  }

  template <class T> 
  void DoWeak( Weak<T> * ptr ) 
  {
    if ( IsReading() )
    {
      IBaseInterfaceST * iobj = LoadObjectST();
      ptr->Set( nival_cast<T>( iobj ) );
    }
    else
      StoreObjectST( ptr->GetBaseObject() );
  }

  //We DO NOT serialize WeakMT<> at all

  template<class T>
  void Add( const chunk_id idChunk, T *p, int nChunkNumber = 1 )
  {
    if (error == BINSAVER_ERR_OK)
    {
      statsCollector.StartType( *p );
    
      AddImpl( idChunk, p, nChunkNumber );
      
      statsCollector.FinishType( *p );
    }
  } 
  
public:
  void DumpStatistics()
  {
    statsCollector.DumpData();
  }
  
  void StatisticReset()
  {
    statsCollector.Reset();
  }
  
  void StartStatisticsGathering()
  {
    statsCollector.StartDataGathering();
  }

  void SetSizeLimit( uint size )
  {
    totalSizeLimit = size;
  }
    

  virtual ErrorType GetError() const { return error; };

private:
  template <typename CharType>
  void DataChunkStringImpl( nstl::basic_string<CharType> &data )
  {
    SIZE_VERIFY( data.length() * sizeof(CharType), return; );
    DataChunkString( data );
    statsCollector.DataWrited( data.length() * sizeof(CharType) );
  }

  template <typename CharType, size_t N>
  void DataChunkStringImpl( nstl::fixed_string<CharType, N> &data )
  {
    SIZE_VERIFY( data.storage_size(), return; );
    DataChunkString( data );
    statsCollector.DataWrited( data.storage_size() );
  }

  void DataChunkImpl( const chunk_id idChunk, void *pData, int nSize, int nChunkNumber )
  {
    SIZE_VERIFY(nSize, return; );
    DataChunk(idChunk, pData, nSize, nChunkNumber);
    statsCollector.DataWrited( nSize );
  }
  
  template<int size>
  void DataChunkImplKnownSize( const chunk_id idChunk, void *pData, int nChunkNumber )
  {
    SIZE_VERIFY(size, return; );
    DataChunk(idChunk, pData, size, nChunkNumber);
    statsCollector.DataWrited( size ); 
  }
  
protected:
  void SetError(ErrorType _error) { error = _error; }

  bool CheckContainerSize(int size) const
  {
    if (size < 0 || containerSizeLimit > 0 && (uint)size > containerSizeLimit)
      return false;
    return true;
  }

  bool CheckSize() const
  {
    if (totalSizeLimit == 0)
      return true;
    if (totalSize > totalSizeLimit)
      return false;

    return true;
  }

  uint totalSizeLimit;
  uint totalSize;

private:
	// Compile time error detection
	template <class T1, class T2, class T3, class T4, class T5>
	void Add( const chunk_id idChunk, _Ht_it<T1, T2, T3, T4, T5> *pData, int nChunkNumber = 1 ) 
	{
		NI_ALWAYS_ASSERT(	"Hash table iterator can't be serialized" );
	}
	template <class T>
	void Add( const chunk_id idChunk, T **pData, int nChunkNumber = 1 ) 
	{
		NI_ALWAYS_ASSERT(	"Pointer or vector iterator can't be serialized" );
	}

	template<class T1, class T2>//, class _Traits>
	void Add( const chunk_id idChunk, _List_it<T1, T2> *pData, int nChunkNumber = 1 ) 
	{
		NI_ALWAYS_ASSERT(	"List iterator can't be serialized" );
	}


  uint containerSizeLimit;
  ErrorType error;

private:
#ifdef BIN_SAVER_USE_PROFILER
  BinSaverStatsCollector statsCollector;
#else  
  BinSaverDummyStatsCollector statsCollector;
#endif
};

// Serializer by pointer
template <>
struct IBinSaver::RingSerializer<1>
{
	template <class T, class C, class R>
	static int Write(IBinSaver *pSaver, ::ring::Ring<T, C, R> &data)
	{
		int nI = 1;
		T * pElemLast = data.last();
		for (T *pRingElem = data.first(); pRingElem != pElemLast;)
		{
			typename R::Pointer point(pRingElem);
			pSaver->Add( 2, &point, nI );
			pRingElem = data.next(pRingElem);
			nI++;
		}
		
		return nI;
	}

	template <class T, class C, class R>
	static void Read(IBinSaver *pSaver, ::ring::Ring<T, C, R> &data, int nCount)
	{
		for(int nI = 1; nI <= nCount; nI++)
		{
			typename R::Pointer pRingElem;        
			pSaver->Add( 2, &pRingElem, nI );
			if ( pRingElem )
			{
				data.safeRemove(pRingElem);
				data.addLast(pRingElem);
			}
			else
			{
				NI_ALWAYS_ASSERT_TRACE("Ring element is empty");
			}
		}
	}
};

template<>
inline void IBinSaver::DataChunkImplKnownSize< 1 >( const chunk_id idChunk, void *pData, int nChunkNumber )
{
  SIZE_VERIFY(1, return; );
	DataChunk_1(idChunk, pData, nChunkNumber);
	statsCollector.DataWrited( 1 ); 
}

template<>
inline void IBinSaver::DataChunkImplKnownSize< 4 >( const chunk_id idChunk, void *pData, int nChunkNumber )
{
  SIZE_VERIFY(4, return; );
	DataChunk_4(idChunk, pData, nChunkNumber);
	statsCollector.DataWrited( 4 ); 
}

inline void IBinSaver::AddImpl( const chunk_id idChunk, bool *pBool, int nChunkNumber)
{
	NI_STATIC_ASSERT( sizeof(bool) == 1, write_only_1_byte );
	DataChunkImplKnownSize< sizeof(bool) >(idChunk, pBool, nChunkNumber);
	//NI_ASSERT(*(unsigned char *)pBool == 0 || *(unsigned char *)pBool == 1, "Strange value in boolean field"); //Visual Studio dependent code. Check under GCC.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
char operator&( T &, IBinSaver & );

//Перечисление всех типов, которые нельзя сериализовать как POD (нельзя копировать при помощи memcpy).
//Такой-же оператор можно объявить и как метод соответствующего класса.
//Если компоновщик ругается на отсутствие определения одной из этих функций, значит нужно написать 
//специализацию для IBinSaver::AddImpl. 
int operator&( string &, IBinSaver & );

int operator&( wstring &, IBinSaver & );

int operator&( MemoryStream &, IBinSaver & );

//template<typename T, unsigned int _capacity>
//int operator&( StaticArray<T, _capacity> &, IBinSaver & );

template<class T1>
int operator&( CArray2D<T1> &, IBinSaver & );

template<class T1>
int operator&( vector<T1> &, IBinSaver & );

template<class T1>
int operator&( list<T1> &, IBinSaver & );

template<class T1, class T2>
int operator&( map<T1,T2> &, IBinSaver & );

template<class T1, class T2, class T3>
int operator&( hash_map<T1,T2,T3> &, IBinSaver & );

template<class T1, class T2, class T3>
int operator&( ring::Ring<T1,T2,T3> &, IBinSaver & );

template<class T1, class T2>
int operator&( hash_set<T1,T2> &, IBinSaver & );

template<class T1, class T2>
int operator&( set<T1,T2> &, IBinSaver & );

template<class T1, class T2>
int operator&( pair<T1,T2> &, IBinSaver & );

// realisation of forward declared serialisation operator

#if 0
template< class TUserObj, class TRef>
int CPtrBase<TUserObj, TRef>::operator&( IBinSaver &f )
{
	f.DoPtr( this );
	return 0;
}
#endif

template< class T>
int Strong<T>::operator & ( IBinSaver & f )
{
  f.DoStrong( this );
	return 0;
}

template< class T>
int StrongMT<T>::operator & ( IBinSaver & f )
{
  f.DoStrong( this );
	return 0;
}

template< class T>
int Weak<T>::operator & ( IBinSaver & f )
{
  f.DoWeak( this );
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //#define BINSAVER_H_437085EA_F184_4ED3_B0
