#ifndef BASIC_H__
#define BASIC_H__

#include <typeinfo>

#include "Asserts.h"
#include "DefaultTypes.h"
#include "ScopedPtr.h"
#include "interlocked.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// single thread version
//
//	 Есть разные шаблоны указателей - простые указатели - CPtr с добавлением ссылки и
// указатели, обладающие правом собственности - CObj. После уничтожения CObj объект,
// на который он ссылался очищается и помечается как невалидный.
//
//	 Ограничения:
// * иногда может потребоваться в .cpp файле использовать BASIC_REGISTER_CLASS(), при
// использовании указателей на forward declared classes
// * нельзя переопределять operator new, так как удалятся объекты будут с помощью
// стандартного operator`a delete (из-за delete this)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef NI_PLATF_LINUX
#pragma warning(disable:4250)
#else
class type_info {
public:
   virtual ~type_info();
   int operator==(const type_info& rhs) const;
   int operator!=(const type_info& rhs) const;
   int before(const type_info& rhs) const;
   const char* name() const;
   const char* raw_name() const;
private:
};
#endif
_interface IBinSaver;
class CObjectBase;

////////////////////////////////////////////////////////////////////////////////////////////////////
// \def TRACK_COBJECTS
// Если включить этот макрос и вызвать PrintObjectsStatistics(), то в Output будет выведена
// статистика для всех типов объектов, производных от CObjectBase, существующих в текущий момент.
// Функция PrintObjectsStatistics() вызывается по нажатию клавиш Ctrl+Shift+M (бинд print_object_statistics)
//#define TRACK_COBJECTS
// Если включить этот макрос со включенным предыдущим, то в консоли можно будет использовать 
// cobj_track_references <hex address> [<depth=0..5>]
// См. статью на confluence "Использование CObj & CPtr в логике".
//#define TRACK_COBJECTS_POINTERS
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef TRACK_COBJECTS
void PrintObjectsStatistics( bool toFile );
#else
inline void PrintObjectsStatistics( bool ) {}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ring
{
	struct CObjectBasePolicy;
	struct CPtrBasePolicy;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This funny crap is needed for bypassing operator & problems when building with gcc on linux
template< class T >
T* GetAddress(T& arg) 
{
  return reinterpret_cast<T*>(
             &const_cast<char&>(
                reinterpret_cast<const volatile char&>(arg)));
}

///////////////////////////////////////////////////////////////////////////////////////////////
/// struct IObjectBase
/// Базовый интерфейс для других интерфейсов.
///
/// IObjectBase является базовым интерфейсом, от него наследуются остальные интерфейсы. 
/// В нём объявлены абстрактные методы с базовой функциональностью.
/// 
/// Эти методы затем имплементируются в финальных классах. Такое наследование интерфейсов 
/// требуется для использования механизма смарт-пойнтеров указателями на интерфейсы.
/// 
/// См. также класс CObjectBase.
_interface IObjectBase
{
	virtual void DestroyContents() = 0;
	virtual void DeleteThis() = 0;

  /// Находится ли объект в невалидном состоянии
	virtual const int IsInvalidRef() const = 0;

	virtual CObjectBase *CastToObjectBase() = 0;
	virtual const CObjectBase *CastToObjectBase() const = 0;

	virtual const int GetTypeId() const = 0;
	virtual const char *GetObjectTypeName() const = 0;

  /// Деструктор
  virtual ~IObjectBase() {};

  /// Оператор сериализации
  virtual int operator&( IBinSaver &f ) { ((void)(&f)); return 0; }
};

class CObjectBase;
namespace NCore
{
  class CRCCalculator;
};
class BinChunkSaver;

///////////////////////////////////////////////////////////////////////////////
/// Предоставляет функционал смарт-пойнтеров.
///
/// От этого класса должны наследоваться все классы, на которые затем будут делаться
/// смарт-пойнтеры: CObj<>, CPtr<>.
///
/// Внутри класса хранятся два счётчика - сильных и слабых указателей. Один для CObj<> -
/// владеющих указателей на данный объект, второй для CPtr<>, указывающих на него.
/// 
/// В объявлении финального класса надо указать макрос OBJECT_BASIC_METHODS( <classname> ), 
/// либо OBJECT_METHODS( <TypeID>, <className> ): в них реализованы абстрактные методы, 
/// объявленные в IObjectBase.
class CObjectBase : public IObjectBase
{
	// delete this object
	void ReleaseComplete();
	// recreate content if this object, mark it invalid but not delete it
	void ReleaseInvalid();

private:
  void AddRef();
	void AddObj() { nival::interlocked_increment( nObjCount ); }
	void DecRef() { nival::interlocked_decrement( nRefCount ); }
	void DecObj() { nival::interlocked_decrement( nObjCount ); }
	void ReleaseRef();
	void ReleaseObj();
protected:
	enum { INVALID_REF_MASK = 0x80000000 };

	const int IsInvalidRefInternal() const { return nObjCount & INVALID_REF_MASK; }

	virtual void OnDestroyContents() {}

	volatile int nRefCount;
	volatile int nObjCount;
  int nCRCMark; //this mark serves for marking object purposed in CRC traversal

// Objects tracking block
protected:
#ifdef TRACK_COBJECTS
	void RegisterInObjectsSet();
	void UnRegisterInObjectsSet();

#ifdef TRACK_COBJECTS_POINTERS
	struct CObjectPointerInfo
	{
		bool isStrong;
	};
	typedef nstl::hash_map<void*, CObjectPointerInfo> TPointersHash;
	TPointersHash *pPointers;
	void TrackRef( void *pPtr, bool inc, bool isStrong );
public:
	void DumpRefs(int depth, int maxDepth);
#endif
#endif

public:
  /// Конструктор без параметров
	CObjectBase() : nRefCount( 0 ), nObjCount( 0 ), nCRCMark(0)
	{
#ifdef TRACK_COBJECTS_POINTERS
		pPointers = 0;
#endif
#ifdef TRACK_COBJECTS
		RegisterInObjectsSet();
#endif
	}

  /// 
	CObjectBase( const CObjectBase& ) : nRefCount( 0 ), nObjCount( 0 ), nCRCMark(0) 
	{
#ifdef TRACK_COBJECTS_POINTERS
		pPointers = 0;
#endif
	}
	CObjectBase& operator = ( const CObjectBase& other ) { ((void)(other)); return *this; }

  /// Деструктор
	virtual ~CObjectBase()
	{
#ifdef TRACK_COBJECTS
		UnRegisterInObjectsSet();
#endif
	}

  /// Размер объекта
  /// <returns>Размер объекта в байтах</returns>
	virtual int GetSizeOf() const = 0;

  /// Оператор сериализации
	virtual int operator&( IBinSaver &f ) { ((void)(&f)); return 0; }

  /// Кол-во слабых указателей
  int GetRefCount() const { return nRefCount; }

  /// Кол-во владеющих указателей
  int GetObjCount() const { return nObjCount; }

  /// CRC
	int GetCRCMark() const { return nCRCMark; }
  void SetCrcMark( int mark ) { nCRCMark = mark; }

	friend struct ring::CObjectBasePolicy;
	friend struct ring::CPtrBasePolicy;

	struct SRefCounter
	{
		static void AddRef( CObjectBase *pObject ) { pObject->AddRef(); }
		static void DecRef( CObjectBase *pObject ) { pObject->DecRef(); }
		static void ReleaseRef( CObjectBase *pObject ) { pObject->ReleaseRef(); }
#ifdef TRACK_COBJECTS_POINTERS
		static void TrackRef( CObjectBase *pObject, void *pPtr, bool inc ) { pObject->TrackRef(pPtr, inc, false); }
#endif
	};

	struct SObjCounter
	{
		static void AddRef( CObjectBase *pObject ) { pObject->AddObj(); }
		static void DecRef( CObjectBase *pObject ) { pObject->DecObj(); }
		static void ReleaseRef( CObjectBase *pObject ) { pObject->ReleaseObj(); }
#ifdef TRACK_COBJECTS_POINTERS
		static void TrackRef( CObjectBase *pObject, void *pPtr, bool inc )  { pObject->TrackRef(pPtr, inc, true); }
#endif
	};
};

#ifdef TRACK_COBJECTS_POINTERS
#define TRACK_ADDOBJ(obj, p) obj->TrackRef(p, true, true)
#define TRACK_DECOBJ(obj, p) obj->TrackRef(p, false, true)
#define TRACK_ADDPTR(obj, p) obj->TrackRef(p, true, false)
#define TRACK_DECPTR(obj, p) obj->TrackRef(p, false, false)
#else
#define TRACK_ADDOBJ(obj, p) 
#define TRACK_DECOBJ(obj, p) 
#define TRACK_ADDPTR(obj, p) 
#define TRACK_DECPTR(obj, p) 
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// General function for getting "invalid" object (for an _interface)
template<typename T>
T* GetInvalid() { return 0; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> CObjectBase *CastToObjectBaseImpl( T *p, void* );
template<class T> const CObjectBase *CastToObjectBaseImpl( const T *p, const void* );
template<class T> inline CObjectBase *CastToObjectBaseImpl( T *p, CObjectBase * ) { return p; }
template<class T> inline CObjectBase* CastToObjectBaseImpl( T* p, IObjectBase* ) { return p ? p->CastToObjectBase() : 0; }
template<class T> T *CastToUserObjectImpl( CObjectBase *p, T*, void * );
template<class T> inline T *CastToUserObjectImpl( CObjectBase *p, T*, CObjectBase * ) { return dynamic_cast<T*>( p ); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> inline CObjectBase *CastToObjectBase( T *p ) { return CastToObjectBaseImpl( p, p ); }
template<class T> inline const CObjectBase *CastToObjectBase( const T *p ) { return CastToObjectBaseImpl( p, p ); }
template<class T> inline T *CastToUserObject( CObjectBase *p, T *pu ) { return CastToUserObjectImpl( p, pu, pu ); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FIXME: Removing ability to use IsValid() on forward declared pointers for NUM_TASK/NUM_TASK
//template<class T> inline bool IsValid( T *p ) { return p != 0 && p != GetInvalid<T>() && !CastToObjectBase( p )->IsInvalidRef(); }
inline bool IsValid( IObjectBase *p ) { return p != 0 && !CastToObjectBase( p )->IsInvalidRef(); }
inline bool IsValid( const IObjectBase *p ) { return p != 0 && !CastToObjectBase( p )->IsInvalidRef(); }
inline bool IsValid( CObjectBase *p ) { return p != 0 && !p->IsInvalidRef(); }
inline bool IsValid( const CObjectBase *p ) { return p != 0 && !p->IsInvalidRef(); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Базовый класс-шаблон для смарт-пойнтеров.
/// 
/// Реализует операции: создание, присвоение, возвращение обычного указателя, удаление,
/// извлечение объекта (Extract). 
template<class T, class TRefCounter>
class CPtrBase
{
	T *pObject;

	void AddRef( T *p ) 
	{ 
		CObjectBase *_p = CastToObjectBase( p ); 
		if ( _p != 0 ) 
		{ 
#ifdef TRACK_COBJECTS_POINTERS
			TRefCounter::TrackRef( _p, this, true );
#endif
			TRefCounter::AddRef( _p ); 
		} 
	}

	void DecRef( T *p ) 
	{ 
		CObjectBase *_p = CastToObjectBase( p ); 
		if ( _p != 0 ) 
		{ 
#ifdef TRACK_COBJECTS_POINTERS
			TRefCounter::TrackRef( _p, this, false );
#endif
			TRefCounter::DecRef( _p ); 
		} 
	}

	void ReleaseRef( T *p ) 
	{ 
		CObjectBase *_p = CastToObjectBase( p ); 
		if ( _p != 0 && p != GetInvalid<T>() ) 
		{ 
#ifdef TRACK_COBJECTS_POINTERS
			TRefCounter::TrackRef( _p, this, false );
#endif
			TRefCounter::ReleaseRef( _p ); 
		} 
	}
public:
  /// Конструктор
	CPtrBase(): pObject( 0 ) {}

  /// Конструктор: сохраняет обычный указатель
	CPtrBase( T *p ): pObject( p )
  {
#if defined( NV_WIN_PLATFORM )
    NI_ASSERT( (unsigned int)p == 0 || (unsigned int)p > 0x00001000, "Possibly bad pointer" );
#endif // defined( NV_WIN_PLATFORM )
    AddRef( pObject );
  }

  /// Конструктор: копирует указатель из другого смарт-пойнтера
	CPtrBase( const CPtrBase &ptrBase ): pObject( ptrBase.pObject ) { AddRef( pObject ); }

  /// Деструктор.
  /// Вызывает ReleaseRef() объекта, на который ссылается указатель.
	~CPtrBase() { ReleaseRef( pObject ); }

  /// Оператор присвоения обычного указателя
	CPtrBase& operator=( T *p ) { SetPtr( p ); return *this; }

  /// Оператор присвоения другого смарт-пойнтера
  CPtrBase& operator=( const CPtrBase &ptrBase ) { SetPtr( ptrBase.pObject ); return *this; }

  /// Возвращает обычный указатель
  T* operator->() const { return GetPtr(); }

  /// Возвращает обычный указатель
  operator T*() const { return GetPtr(); }

  /// Присвоение обычного указателя.
  /// 
  /// Если смарт-пойнтер до присвоения указывал на другой объект, то ему делается ReleaseRef(). 
  /// На новый объект вызывается AddRef().
  void SetPtr( T *p ) 
	{ 
#if defined( NV_WIN_PLATFORM )
		NI_ASSERT( (unsigned int)p == 0 || (unsigned int)p > 0x00001000, "Possibly bad pointer" ); 
#endif // defined( NV_WIN_PLATFORM )
		T *pOldObject = pObject; 
		pObject = (p == GetInvalid<T>() ? 0 : p); 
#ifdef TRACK_COBJECTS_POINTERS
		if (pObject != pOldObject)
		{
			AddRef( pObject ); 
			ReleaseRef( pOldObject ); 
		}
#else
		AddRef( pObject ); 
		ReleaseRef( pOldObject ); 
#endif
	}

  /// Возвращает обычный указатель
  T* GetPtr() const { if ( pObject == 0 ) return GetInvalid<T>(); else return pObject; }
  T* GetValidPtr() const { return (GetPtr() != GetInvalid<T>() && !GetBarePtr()->IsInvalidRef())?pObject:0; }

  /// Возвращает указатель, приведённый к CObjectBase*
	CObjectBase* GetBarePtr() const { return CastToObjectBase( pObject ); }

  /// Извлечение объекта.
  /// 
  /// Указатель "вынимается" из смарт-пойнтера без вызова деструктора, счётчик ссылок уменьшается на 1. 
  /// После вызова смарт-пойнтер перестаёт как-либо быть связанным с объектом, 
  /// в нём больше не хранится указатель на объект.
	T* Extract() { T *pResult = GetPtr(); DecRef( pObject ); pObject = 0; return pResult; }

  /// Оператор сериализации
	int operator&( IBinSaver &f );
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_SMART_PTR( smartPtrName, TRefCounter )																																				\
template<class T>																																																							\
class smartPtrName: public CPtrBase<T, TRefCounter>																																						\
{																																																															\
public:                                                                                                                       \
	typedef CPtrBase<T, TRefCounter> TBase;																																											\
public:																																																												\
	smartPtrName() {}																																																						\
	smartPtrName( T *_pObject ): TBase( _pObject ) {}																																						\
	smartPtrName( const smartPtrName &smartPtr ): TBase( smartPtr ) {}																													\
	smartPtrName& operator=( T *_pObject ) { this->SetPtr( _pObject ); return *this; }																								\
	smartPtrName& operator=( const smartPtrName &smartPtr ) { this->SetPtr( smartPtr.GetPtr() ); return *this; }											\
																																																															\
	int operator&( IBinSaver &f );																														                                  \
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// Weak-pointer 
DECLARE_SMART_PTR( CPtr, CObjectBase::SRefCounter );

/// Strong-pointer - владеющий указатель
DECLARE_SMART_PTR( CObj, CObjectBase::SObjCounter );
#undef DECLARE_SMART_PTR

/// Weak pointer, emulating point-to-constant raw pointer
//NOTE: It can still call destructors etc.!
template<class T>
class ConstPtr : public CPtrBase<T, CObjectBase::SRefCounter>
{
public:
  typedef CPtrBase<T, CObjectBase::SRefCounter> TBase;
public:
  ConstPtr() {}

  //We can construct from const raw pointers
  ConstPtr( const T * _pObject ) : TBase( const_cast<T *>( _pObject ) ) {}
  ConstPtr( const ConstPtr & smartPtr ) : TBase( const_cast<T *>( smartPtr.GetPtr() ) ) {}
  ConstPtr & operator = ( const T *_pObject ) { SetPtr( const_cast<T *>( _pObject ) ); return *this; }
  ConstPtr & operator = ( const ConstPtr & smartPtr ) { SetPtr( const_cast<T *>( smartPtr.GetPtr() ) ); return *this; }

  //We'll mask non-constant access methods and operators
  const T * GetPtr() const { return TBase::GetPtr(); }

  const T * operator->() const { return GetPtr(); }
  operator const T * () const { return GetPtr(); }

  const T * Extract() { return TBase::Extract(); }

  int operator&( IBinSaver &f );
};

#include "CreateHelper.h"



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define OBJECT_ABSTRACT_METHODS( className )																																									\
	public:																																																											\
		enum { typeId = 0 };																																																			\
		const int GetTypeId() const { return typeId; }																																						\
		const int IsInvalidRef() const { return IsInvalidRefInternal(); }																													\
		void DeleteThis() { delete this; }																																												\
		CObjectBase *CastToObjectBase() { return (CObjectBase*)this; }																														\
		const CObjectBase *CastToObjectBase() const { return (CObjectBase*)this; }																								\
		const char *GetObjectTypeName() const { return #className; }																															\
		static const char *GetTypeName() { return #className; }																																		\
		int GetSizeOf() const { return sizeof(className); }																																				\
	private:

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define OBJECT_BASIC_METHODS( className )																																											\
	public:																																																											\
		enum { typeId = 0 };																																																			\
		const int GetTypeId() const { return typeId; }																																						\
		const int IsInvalidRef() const { return IsInvalidRefInternal(); }																													\
		void DeleteThis() { delete this; }																																												\
		CObjectBase *CastToObjectBase() { return (CObjectBase*)this; }																														\
		const CObjectBase *CastToObjectBase() const { return (CObjectBase*)this; }																								\
		const char *GetObjectTypeName() const { return #className; }																															\
		static const char *GetTypeName() { return #className; }																																		\
		int GetSizeOf() const { return sizeof(className); }																																				\
	public:																																																											\
		void DestroyContents()																																																		\
		{																																																													\
			this->~className();																																																			\
			int nHoldRef = nRefCount;																																																\
			int nHoldObj = nObjCount;																																																\
      ::new(this) className();																																																\
			nRefCount += nHoldRef;																																																	\
			nObjCount += nHoldObj;																																																	\
		}																																																													\
    static CObjectBase* New##className() { return ::Create<className>(); }																		                \
	private:                                                                                                                    \
  friend struct CreateHelpersHelper<className>;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define OBJECT_METHODS( N, className )																																												\
	public:																																																											\
		enum { typeId = N };																																																			\
		const int GetTypeId() const { return typeId; }																																						\
		const int IsInvalidRef() const { return IsInvalidRefInternal(); }																													\
		void DeleteThis() { delete this; }																																												\
		CObjectBase *CastToObjectBase() { return (CObjectBase*)this; }																														\
		const CObjectBase *CastToObjectBase() const { return (CObjectBase*)this; }																								\
		const char *GetObjectTypeName() const { return #className; }																															\
		static const char *GetTypeName() { return #className; }																																		\
		int GetSizeOf() const { return sizeof(className); }																																				\
	public:																																																											\
		void DestroyContents()																																																		\
		{																																																													\
			this->~className();																																																			\
			int nHoldRef = nRefCount;																																																\
			int nHoldObj = nObjCount;																																																\
      ::new(this) className();																																																\
			nRefCount += nHoldRef;																																																	\
			nObjCount += nHoldObj;																																																	\
		}																																																													\
    static CObjectBase* New##className() { return ::Create<className>(); }																		     	          \
  private:                                                                                                                    \
    friend struct CreateHelpersHelper<className>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BASIC_REGISTER_CLASS( className )																																											\
template<> className *CastToUserObjectImpl<className >( CObjectBase *p, className*, void* ) { return dynamic_cast<className*>( p ); }	\
template<> const CObjectBase *CastToObjectBaseImpl<className>( const className *p, const void* ) { if ( p ) return p->CastToObjectBase(); else return 0; } \
template<> CObjectBase *CastToObjectBaseImpl<className>( className *p, void* ) { if ( p ) return p->CastToObjectBase(); else return 0; }

template<class T, class TRef> inline bool IsValid( const CPtrBase<T, TRef> &p ) { return p.GetPtr() != GetInvalid<T>() && !p.GetBarePtr()->IsInvalidRef(); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// assumes base class is IObjectBase
template<class T>
class CDynamicCast
{
	T *pObject;
public:
	template<class TOther>
		CDynamicCast( TOther *_pObject ) { pObject = dynamic_cast<T*>( CastToObjectBase( _pObject ) ); }
	template<class TOther>
		CDynamicCast( const TOther *_pObject ) { pObject = dynamic_cast<T*>( CastToObjectBase( const_cast<TOther*>( _pObject ) ) ); }
	template<class TOther, class TRef>
		CDynamicCast( const CPtrBase<TOther, TRef> &ptr ) { pObject = dynamic_cast<T*>( ptr.GetBarePtr() ); }

	operator T*() const { return pObject; }
	T* operator->() const { return pObject; }
	T* GetPtr() const { return pObject; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
inline bool IsValid( const CDynamicCast<T> &p ) { return IsValid( p.GetPtr() ); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// walks container of pointers and erases references on invalid entries
template<class TContainer>
inline bool EraseInvalidRefs( TContainer *pData )
{
	bool bRes = false;
	for ( typename TContainer::iterator it = pData->begin(); it != pData->end(); )
	{
		if ( IsValid( *it ) )
			++it;
		else
		{
			it = pData->erase( it );
			bRes = true;
		}
	}
	return bRes;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// object factory
namespace NObjectFactory
{
	typedef CObjectBase* (*ObjectFactoryNewFunc)();
	// create new object by typeID
	CObjectBase *MakeObject( int nTypeID );
	// register type for further creation
	void RegisterType( int nObjectTypeID, ObjectFactoryNewFunc pfnNewFunc, const std::type_info *pTypeInfo );
	void RegisterType( int nObjectTypeID, ObjectFactoryNewFunc pfnNewFunc, const std::type_info *pTypeInfo, const char* name );
	void UnRegisterType( int nObjectTypeID, const std::type_info *pTypeInfo );
	// get object's typeID (for save/load system)
	int GetObjectTypeID( const CObjectBase *pObj );
	// check, is type registered
	bool IsRegistered( int nObjectTypeID );
	// start register type
	void StartRegister();
	//
	template <class T>
	void RegisterTypeName( int nTypeID, ObjectFactoryNewFunc func, T* ) { NObjectFactory::RegisterType( nTypeID, func, &typeid(T) ); }
	template <class T>
	void RegisterTypeName( int nTypeID, ObjectFactoryNewFunc func, T*, const char* name ) { NObjectFactory::RegisterType( nTypeID, func, (const std::type_info *)&typeid(T), name ); }
	template <class T>
	void UnRegisterTypeName( int nTypeID, T* ) { NObjectFactory::UnRegisterType( nTypeID, &typeid(T) ); }

	void CheckTypes();
}; // namespace NObjectFactory


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// macroses for registring classes in objects factory
#define REGISTER_CLASS( N, name ) { NObjectFactory::StartRegister(); NObjectFactory::RegisterTypeName( N, name ::New##name, (name*)0, #name ); }
#define UNREGISTER_CLASS( N, name ) NObjectFactory::UnRegisterTypeName( N, (name*)0 );

#define REGISTER_CLASS_NM( N, name, nmspace ) { NObjectFactory::StartRegister(); NObjectFactory::RegisterTypeName( N, nmspace::name::New##name, (nmspace::name*)0, #name ); }
#define UNREGISTER_CLASS_NM( N, name, nmspace ) NObjectFactory::UnRegisterTypeName( N, (nmspace::name*)0 );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct PtrHash
{
	template <class T,class TRef>
	size_t operator()( const CPtrBase<T, TRef> &p ) const { return (size_t)p.GetBarePtr(); }
	template <class T>
	size_t operator()( const T *p ) const { return (size_t)p; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//namespace nstl
//{
//	template<class T,class TRef>
//	struct hash<CPtrBase<T, TRef>>
//	{
//		size_t operator()( const CPtrBase<T, TRef> &p ) const { return (int)p.GetBarePtr(); }
//	};
//}//namespace nstl;
#endif //BASIC_H__
