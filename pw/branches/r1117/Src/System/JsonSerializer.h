#ifndef _JSON_SAVER_H_
#define _JSON_SAVER_H_

#include "../System/nlist.h"
#include "../System/MetaProg.h"


#define JDATA
#define JDATA_(a)
#define JEND
#define JSKIP


namespace Render
{
	class HDRColor;
}

template <class T> class CArray2D;

#ifdef WIN32
  #define CCDECL    __cdecl
#else
#ifndef CCDECL
  #define CCDECL    __attribute__ ((cdecl))
#endif
#endif  

//struct IJsonSerializer;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PointersHolder : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( PointersHolder, BaseObjectMT );

  typedef nstl::hash_map<int, CObj<CObjectBase>> TCObjMap;
  typedef nstl::hash_map<int, StrongMT<BaseObjectMT>> TStrongMTMap;
  typedef nstl::hash_map<int, Strong<BaseObjectST>> TStrongSTMap;

  template<class T> 
  void clear( T& container )
  {
    for ( T::iterator it = container.begin(); it != container.end(); it++ )
    {
      it->second = 0;
    }
    container.clear();
  }
public:
  
  TCObjMap cobjs;
  TStrongMTMap mtobjs;
  TStrongSTMap stobjs;
  


  PointersHolder() {}
  ~PointersHolder()
  {
    clear(cobjs);
    clear(mtobjs);
    clear(stobjs);
  }

  void Add( CObjectBase* obj, int id )
  {
    cobjs[id] = obj;
  }

  void Add( BaseObjectMT* obj, int id )
  {
    mtobjs[id] = obj;
  }

  void Add( BaseObjectST* obj, int id )
  {
    stobjs[id] = obj;
  }

  virtual int GetObjectID( CObjectBase *pObject )
  {
    for ( TCObjMap::iterator it = cobjs.begin(); it != cobjs.end(); it++ )
    {
      if ( it->second.GetPtr() == pObject )
      {
        return it->first;
      }
    }
    return -1;
  }

  virtual CObjectBase* GetObject ( int nID )
  {
    if( -1 == nID )
      return NULL;

    TCObjMap::iterator object = cobjs.find(nID);
    return cobjs.end() == object ? NULL : object->second;
  }

  int GetObjectIdST( BaseObjectST* pObject )
  {
    for ( TStrongSTMap::iterator it = stobjs.begin(); it != stobjs.end(); it++ )
    {
      if ( it->second.Get() == pObject )
      {
        return it->first;
      }
    }
    return -1;
  }

  BaseObjectST* GetObjectST( int id )
  {
    if( -1 == id )
      return NULL;

    TStrongSTMap::iterator object = stobjs.find(id);
    return stobjs.end() == object ? NULL : object->second;
  }

  int GetObjectIdMT( BaseObjectMT* pObject )
  {
    for ( TStrongMTMap::iterator it = mtobjs.begin(); it != mtobjs.end(); it++ )
    {
      if ( it->second.Get() == pObject )
      {
        return it->first;
      }
    }
    return -1;
  }

  BaseObjectMT* GetObjectMT( int id )
  {
    if( -1 == id )
      return NULL;

    TStrongMTMap::iterator object = mtobjs.find(id);
    return mtobjs.end() == object ? NULL : object->second;
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JsonSaver
class IJsonSerializerBase : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IJsonSerializerBase, IBaseInterfaceMT );

private:
	// add boolean built-in type
	template <class TYPE>
		void AddBoolData( const string& idChunk, TYPE *pData, int nChunkNumber ) 
		{ 
			bool bData = *pData;
			const bool bRetVal = DataChunk( idChunk, &bData, nChunkNumber );
			if ( IsReading() && bRetVal ) 
				*pData = TYPE( bData );
		}
	// add integer built-in types
	template <class TYPE>
		void AddIntData( const string& idChunk, TYPE *pData, int nChunkNumber ) 
		{ 
			int nData = *pData;
			const bool bRetVal = DataChunk( idChunk, &nData, nChunkNumber );
			if ( IsReading() && bRetVal ) 
				*pData = TYPE( nData );
		}
	// add fp built-in types
	template <class TYPE>
		void AddFPData( const string& idChunk, TYPE *pData, int nChunkNumber ) 
		{ 
			float fData = *pData;
			const bool bRetVal = DataChunk( idChunk, &fData, nChunkNumber );
			if ( IsReading() && bRetVal ) 
				*pData = TYPE( fData );
		}
	//
	template<class T>
		void CCDECL CallObjectSerialize( const string& idChunk, int nChunkNumber, T *p, ... )
		{
			if ( !StartChunk(idChunk, nChunkNumber) )
				return;
			p->operator&( *this );
			FinishChunk();
		}

	template<class T>
		void CCDECL CallRawObjectSerialize( const string& idChunk, int nChunkNumber, T *p, Meta::Int2Type<0> *pp )
		{
			DataChunk( idChunk, p, sizeof(T), nChunkNumber );
		}

	template<class T>
		void CCDECL CallObjectSerialize( const string& idChunk, int nChunkNumber, T *p, Meta::Int2Type<1> *pp )
		{
			const int N_KNOWN_ENUM = 0;
			Meta::Int2Type<N_KNOWN_ENUM> separator;
			CallRawObjectSerialize( idChunk, nChunkNumber, p, &separator );
		}


  //////////////////////////////////////////////////////////////////////////
  // CObjectBase serialization
  template< class TUserObj, class TRef>
    void AddInternal( const string& idChunk, CPtrBase<TUserObj, TRef> *pPtr, int nChunkNumber )
    {
      if ( !StartChunk( idChunk, nChunkNumber ) )
        return;

      int objectId = 0;

      TUserObj* userTypePtr = 0;
      if (!IsReading() && IsValid(*pPtr))
      {
        userTypePtr = static_cast<TUserObj*>(pPtr->GetPtr());
        objectId = (int)userTypePtr;
        Add("id", &objectId);

        CObjectBase* storedObj = objHolder->GetObject(objectId);
        if (!storedObj)
          objHolder->Add(userTypePtr, objectId);
        else
          userTypePtr = 0;
      }
      else
      {
        Add("id",&objectId);

        CObjectBase* storedObj = objHolder->GetObject(objectId);
        if (storedObj)
        {
          pPtr->SetPtr(dynamic_cast<TUserObj*>(storedObj));
        }
        else
        {
          userTypePtr = new TUserObj();
          objHolder->Add(userTypePtr, objectId);
          pPtr->SetPtr(userTypePtr);
        }

      }

      if (userTypePtr)
        userTypePtr->operator& ( *this );  

      FinishChunk();
    }

    template<class T, class T1>
    void AddInternal( const string& idChunk, int nChunkNumber, T* p, CPtr<T1> *pPtr )
    {
      AddInternal( idChunk, static_cast<typename CPtr<T1>::TBase *>(pPtr), nChunkNumber );
    }

    template<class T, class T1>
    void AddInternal( const string& idChunk, int nChunkNumber, T* p, CObj<T1> *pPtr )
    {
      AddInternal( idChunk, static_cast<typename CObj<T1>::TBase *>(pPtr), nChunkNumber );
    }

    template<class T, class T1>
    void AddInternal( const string& idChunk, int nChunkNumber, T* p, ConstPtr<T1> *pPtr )
    {
      AddInternal( idChunk, static_cast<typename ConstPtr<T1>::TBase *>(pPtr), nChunkNumber );
    }

    //////////////////////////////////////////////////////////////////////////
    // BaseObjectMT serialization
    template<class T, class TUserObj>
    void AddInternal( const string& idChunk, int nChunkNumber, T* p, StrongMT<TUserObj> *pPtr )
    {
      if ( !StartChunk( idChunk, nChunkNumber ) )
        return;

      int objectId = 0;

      TUserObj* userTypePtr = 0;
      if (!IsReading() && pPtr->Valid())
      {
        userTypePtr = static_cast<TUserObj*>(pPtr->Get());
        objectId = (int)userTypePtr;
        Add("id", &objectId);

        BaseObjectMT* storedObj = objHolder->GetObjectMT(objectId);
        if (!storedObj)
          objHolder->Add(static_cast<BaseObjectMT*>(pPtr->Get()), objectId);
        else
          userTypePtr = 0;
      }
      else
      {
        Add("id",&objectId);

        BaseObjectMT* storedObj = objHolder->GetObjectMT(objectId);
        if (storedObj)
          pPtr->Set(dynamic_cast<TUserObj*>(storedObj));
        else
        {
          StrongMT<TUserObj> newObj = new TUserObj();
          userTypePtr = newObj.Get();
          objHolder->Add(newObj, objectId);
          pPtr->Set(userTypePtr);
        }
      }

      if (userTypePtr)
        userTypePtr->operator& ( *this );  

      FinishChunk();
    }

    template<class T, class T1>
    void AddInternal( const string& idChunk, int nChunkNumber, T* p, WeakMT<T1> *pPtr )
    {
      StrongMT<T1> pStrong = pPtr->Lock();
      AddInternal( idChunk, nChunkNumber, &pStrong, &pStrong );

      if (IsReading())
        *pPtr = pStrong;
    }

  //////////////////////////////////////////////////////////////////////////
  // BaseObjectST
    template<class T, class TUserObj>
    void AddInternal( const string& idChunk, int nChunkNumber, T* p, Strong<TUserObj> *pPtr )
    {
      if ( !StartChunk( idChunk, nChunkNumber ) )
        return;

      int objectId = 0;

      TUserObj* userTypePtr = 0;
      if (!IsReading() && pPtr->Valid())
      {
        userTypePtr = static_cast<TUserObj*>(pPtr->Get());
        objectId = (int)userTypePtr;
        Add("id", &objectId);

        BaseObjectST* storedObj = objHolder->GetObjectST(objectId);
        if (!storedObj)
          objHolder->Add(static_cast<BaseObjectST*>(pPtr->Get()), objectId);
        else
          userTypePtr = 0;
      }
      else
      {
        Add("id",&objectId);

        BaseObjectST* storedObj = objHolder->GetObjectST(objectId);
        if (storedObj)
          pPtr->Set(dynamic_cast<TUserObj*>(storedObj));
        else
        {
          Strong<TUserObj> newObj = new TUserObj();
          userTypePtr = newObj.Get();
          objHolder->Add(newObj, objectId);
          pPtr->Set(userTypePtr);
        }
      }

      if (userTypePtr)
        userTypePtr->operator& ( *this );  

      FinishChunk();
    }

    template<class T, class T1>
    void AddInternal( const string& idChunk, int nChunkNumber, T* p, Weak<T1> *pPtr )
    {
      Strong<T1> pStrong = pPtr->Get();
      AddInternal( idChunk, nChunkNumber, &pStrong, &pStrong );

      if (IsReading())
        *pPtr = pStrong;
    }

	//
	template<class T>
		void CCDECL AddInternal( const string& idChunk, int nChunkNumber, T *p, ... )
		{
			const int N_HAS_SERIALIZE_TEST = sizeof( (*p) & (*this) );
			Meta::Int2Type<N_HAS_SERIALIZE_TEST> separator;
			CallObjectSerialize( idChunk, nChunkNumber, p, &separator );
		}

	template <class T, class T1>
		void CCDECL AddInternal( const string& idChunk, int nChunkNumber, T *p, basic_string<T1> *pStr ) 
		{
			DataChunkString( idChunk, *pStr, nChunkNumber );
		}

	template <class T, class T1>
		void CCDECL AddInternal( const string& idChunk, int nChunkNumber, T *p, vector<T1> *pVec ) 
		{
			if ( !StartChunk(idChunk, 0) )
				return;
		
			DoVector( *p );
			FinishChunk();
		}

    
  // probably this specicialization is not required		
  #ifdef WIN32
	template <class T, class T1>
		void CCDECL AddInternal( const string& idChunk, int nChunkNumber, T *p, nstl::list<T1> *pList ) 
	{
		if ( !StartChunk(idChunk, nChunkNumber) )
			return;

		nstl::list<T1> &data = *pList;
		if ( IsReading() )
		{
			pList->clear();
			pList->insert( data.begin(), CurrentContainerSize(), T1() );
		}
		int i = 0;
		nstl::list<T1>::iterator it;
		for (it = data.begin(); it != data.end(); ++it, ++i )
			Add( string(), &(*it), i );
		
    FinishChunk();
	}
	#endif

	// vector
	template <class T> 
		void DoVector( vector<T> &data )
		{
			int i, nSize = 0;
			if ( IsReading() )
			{
        nSize = max( CurrentContainerSize(), data.size() );
				data.resize( nSize );
			}
			else
				nSize = data.size();

      for ( i = 0; i < nSize; ++i )
        Add( string(), &data[i], i );
		}
    
	virtual bool DataChunk( const string& idChunk, void *pData, int nSize, int nChunkNumber ) = 0;
	virtual bool DataChunk( const string& idChunk, int *pnData, int nChunkNumber ) = 0;
	virtual bool DataChunk( const string& idChunk, float *pfData, int nChunkNumber ) = 0;
	virtual bool DataChunk( const string& idChunk, bool *pData, int nChunkNumber ) = 0;
	#ifdef WIN32
	virtual bool DataChunk( const string& idChunk, GUID *pgData, int nChunkNumber ) = 0;
  #endif	  
	virtual bool DataChunkString( const string& idChunk, string &data, int nChunkNumber ) = 0;
	virtual bool DataChunkString( const string& idChunk, wstring &data, int nChunkNumber ) = 0;
  //
  virtual int CurrentContainerSize() const = 0;

  StrongMT<PointersHolder> objHolder;
public:
  IJsonSerializerBase() 
  {
    objHolder = new PointersHolder();
  }

	// add raw data of specified size (in bytes)
	void AddRawData( const string& idChunk, void *pData, int nSize, int nChunkNumber = 0 ) 
  { 
    DataChunk( idChunk, pData, nSize, nChunkNumber ); 
  }

  template<class T>
  void Add(T *p)
  {
     Add("__root__", p);
  }
  // main add function - add all structures/classes/datas through it
	template<class T>
  void Add( const string& idChunk, T *p, int nChunkNumber = 0 )
  {
    AddInternal( idChunk, nChunkNumber, p, p );
  }

  virtual bool IsReading() const = 0;

	virtual bool StartChunk( const string& idChunk, int nChunkNumber ) = 0;
	virtual void FinishChunk() = 0;
};

// simple built-in data specialization
#ifdef WIN32
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<GUID>( const string& idChunk, int nChunkNumber, GUID *pData, Meta::Int2Type<1> * )
{
  DataChunk( idChunk, pData, nChunkNumber );
}
#endif

template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<bool>( const string& idChunk, int nChunkNumber, bool *pData, Meta::Int2Type<1> * )
{
  AddBoolData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<char>( const string& idChunk, int nChunkNumber, char *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<signed char>( const string& idChunk, int nChunkNumber, signed char *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<unsigned char>( const string& idChunk, int nChunkNumber, unsigned char *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<short>( const string& idChunk, int nChunkNumber, short *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<unsigned short>( const string& idChunk, int nChunkNumber, unsigned short *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<long>( const string& idChunk, int nChunkNumber, long *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<unsigned long>( const string& idChunk, int nChunkNumber, unsigned long *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<int>( const string& idChunk, int nChunkNumber, int *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<unsigned int>( const string& idChunk, int nChunkNumber, unsigned int *pData, Meta::Int2Type<1> * )
{
  AddIntData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<float>( const string& idChunk, int nChunkNumber, float *pData, Meta::Int2Type<1> * )
{
  AddFPData( idChunk, pData, nChunkNumber );
}
template <> inline
void CCDECL IJsonSerializerBase::CallObjectSerialize<double>( const string& idChunk, int nChunkNumber, double *pData, Meta::Int2Type<1> * )
{
  AddFPData( idChunk, pData, nChunkNumber );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
inline char operator&( T &c, IJsonSerializerBase &ss ) { return 0; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IJsonSerializerBase *CreateJsonLoader( const string& jsonString);
IJsonSerializerBase *CreateJsonWriter( string& jsonString);


class JsonSerializer : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( JsonSerializer, BaseObjectMT );
public:
  template <class T>
  void SerializeFromFile(const char* fileName, T* p) 
  {
    CObj<FileStream> pStream = new FileStream( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);

    if ( !pStream->IsOk() )
    {
      DevTrace( NStr::StrFmt("can't serialize from json: can't read file %s", fileName) );
      return;
    }

    SerializeFromStr(pStream->GetBuffer(), p);
  };

  template <class T>
  void SerializeFromStr(const char* str, T* p)
  {
    StrongMT<IJsonSerializerBase> pLoader = CreateJsonLoader(str);
    pLoader->Add(p);
  }

  template <class T>
  void SerializeToFile(const char* fileName, T* p) 
  {
    string result;
    SerializeToStr(result, p);

    CObj<FileStream> pStream = new FileStream( fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);

    if ( !pStream->IsOk() )
    {
      DevTrace( NStr::StrFmt("can't serialize to json: can't write file %s", fileName) );
      return;
    }

    pStream->WriteString(result);
    pStream->Close();
    
  };

  template <class T>
  void SerializeToStr(string& str, T* p)
  {
    StrongMT<IJsonSerializerBase> pWriter = CreateJsonWriter(str);
    pWriter->Add(p);
  }
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

