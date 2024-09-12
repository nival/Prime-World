#ifndef __L_BenderTest_H__
#define __L_BenderTest_H__

#include <RPC/RPC.h>
#include "GenTest.cpp"
namespace benderovec
{
class LBenderTest : public rpc::ILocalEntity, public CObjectBase
{
	OBJECT_BASIC_METHODS(LBenderTest);
public:
	LBenderTest() {}
	LBenderTest(benderovec::BenderTest* _xxx, bool _isInstancePersistent)
	:	isInstancePersistent(_isInstancePersistent)
	,	xxx(_xxx) {}

	~LBenderTest()
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
	benderovec::BenderTest* xxx;
	bool isInstancePersistent;

};
}
#endif // __L_BenderTest_H__
