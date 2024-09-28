#ifndef __L_GenTest_H__
#define __L_GenTest_H__

#include <RPC/RPC.h>
#include "GenTest.cpp"
namespace testnamespace
{
class LGenTest : public rpc::ILocalEntity, public CObjectBase
{
	OBJECT_BASIC_METHODS(LGenTest);
public:
	LGenTest() {}
	LGenTest(testnamespace::GenTest* _xxx, bool _isInstancePersistent)
	:	isInstancePersistent(_isInstancePersistent)
	,	xxx(_xxx) {}

	~LGenTest()
	{
		if (!isInstancePersistent)
		{
			delete xxx;
		}
	}
	virtual void vcall( byte method_id, va_list v, rpc::MethodCall& call );
	virtual void* getPtr( uint id ) { return ( id == xxx->ID ) ? xxx : 0; }
	virtual int getMemberIndex( const void* ) { return -1; }
private:
	testnamespace::GenTest* xxx;
	bool isInstancePersistent;

};
}
#endif // __L_GenTest_H__
