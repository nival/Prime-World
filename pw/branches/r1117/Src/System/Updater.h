#ifndef _SYSTEM_UPDATER_H_
#define _SYSTEM_UPDATER_H_

#include "Functor.h"
#include "UpdateProcessor.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Updater
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Functor : public IUpdateProcessorFunc
{	
  OBJECT_METHODS(0xF4687380,Functor);
public:
  typedef void (*Handler)( const T& );

private:
  Handler handler;

public:
  Functor() : handler(0) {};
  explicit Functor( Handler _handler ) : handler( _handler ) {};

  void Process( CObjectBase* _data )
  {
    if(handler != 0)
    {
      T* data = _data ? CastToUserObject( _data, (T*)0 ) : 0;
      NI_VERIFY( data, "No data to process", return );
      handler( *data );
    }			
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
struct Validator
{
  bool operator () ( CPtr<Type>& processor ) const
  {
    //return !IsValid( processor );
    if(IsValid(processor))
      return false;
    else
      return true;
  }
};

class CUpdater : public CObjectBase
{
	OBJECT_METHODS( 0x1E4A8B4B, CUpdater );
	typedef list<CObj<CObjectBase> > TUpdates;
	typedef list<CPtr<CUpdateProcessor> > TProcessors;

	typedef list<CPtr<IUpdateProcessorFunc> > FunctorsVector;
	typedef hash_map<int, FunctorsVector> Functors;  // ???
	Functors functors;
	
	ZDATA
  ZNOPARENT(CObjectBase)
		TUpdates updates;
		TProcessors processors;		
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(2,&updates); f.Add(3,&processors); return 0; }
private:
	void ProcessUpdate( CObjectBase *pUpdate );
	void UnregisterCorpse();
public:
  ~CUpdater();

  void Register( int, IUpdateProcessorFunc *pFunctor);
	void Register( CUpdateProcessor *pProcessor );
	void Push( CObjectBase *pUpdate, const bool bDelayed );
	void Step();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

