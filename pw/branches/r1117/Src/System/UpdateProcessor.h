#ifndef _UPDATE_PROCESSOR_H_
#define _UPDATE_PROCESSOR_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Updater
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IUpdateProcessorFunc : public CObjectBase
{
	virtual void Process( CObjectBase *pRawData ) = 0;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename TObj, typename TUpdate>
class CUpdateProcessorFunc : public IUpdateProcessorFunc
{
	OBJECT_METHODS( 0x1E4A8B4A, CUpdateProcessorFunc );

	typedef void (TObj::*ProcessFunc)( const TUpdate &update );
	TObj *pObj;
	ProcessFunc pfnProcessFunc;
public:
	CUpdateProcessorFunc() : pObj( 0 ), pfnProcessFunc( 0 ) {}
	CUpdateProcessorFunc( ProcessFunc _pfnProcessFunc, TObj *_pObj ) : pfnProcessFunc( _pfnProcessFunc ), pObj( _pObj ) { }
  
	virtual void Process( CObjectBase *pRawUpdate )
	{
		TUpdate *pUpdate = pRawUpdate ? CastToUserObject( pRawUpdate, (TUpdate*)0 ) : 0;
		NI_VERIFY( pUpdate, "No data to process", return );
		(pObj->*pfnProcessFunc)( *pUpdate );
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CUpdateProcessor : public CObjectBase
{
	typedef hash_map<int, CPtr<IUpdateProcessorFunc> > TProcessorFuncs;
	TProcessorFuncs updateProcessorFuncs;
	ZDATA
  ZNOPARENT(CObjectBase)
	ZONSERIALIZE
public:
	ZEND int operator&( IBinSaver &f ) { OnSerialize( f ); return 0; }
private:
	void OnSerialize( IBinSaver &f );
protected:
	template<typename TObj, typename TUpdate>
	void Subscribe( void (TObj::*pfnProcessFunc)( const TUpdate &update ) )
	{
    const int nTypeID = TUpdate::typeId;
		updateProcessorFuncs[nTypeID] = new CUpdateProcessorFunc<TObj, TUpdate>( pfnProcessFunc, (TObj*)this );
	}

  virtual void SubscribeUpdates() = 0;
public:
	CUpdateProcessor() {}
	void Process( CObjectBase *pUpdate );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

