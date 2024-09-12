#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_

//#include "UpdateProcessor.h"

namespace Updater
{
  // Old functor implementation

	//_interface IFunctor
	//{
	//	virtual void operator() ( CObjectBase* ) = 0;
	//};

	//template<typename T>
	//class Functor : public public IFunctor
	//{	
	//public:
	//	typedef void (*Handler)( const T& );

	//private:
	//	Handler handler;

	//public:
 //   Functor( Handler _handler ) : handler( _handler ) {}

	//	virtual void operator() ( CObjectBase* _data )
	//	{
 //     if(handler != 0)
 //     {
 //       T* data = _data ? CastToUserObject( _data, (T*)0 ) : 0;
 //       NI_VERIFY( data, "No data to process", return );
 //       handler( *data );
 //     }			
	//	}
	//};
}

#endif


