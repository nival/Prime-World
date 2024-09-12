#ifndef __R_BenderTest_H__
#define __R_BenderTest_H__

#include <RPC/RPC.h>
namespace benderovec
{
class RBenderTest : public rpc::IRemoteEntity, public CObjectBase
{
    OBJECT_BASIC_METHODS(RBenderTest);
public:
    rpc::EntityHandler* handler;
    rpc::CallWait* xxx;

    RPC_ID();
    RBenderTest() : handler(0), xxx(0) {}
    RBenderTest( rpc::EntityHandler* _handler, rpc::CallWait* _xxx )
    :   handler(_handler)
    ,   xxx(_xxx) {}

    ~RBenderTest()
    {
        if( handler )
        {
            handler->OnDestruct();
        }
    }

    virtual rpc::RemoteEntityTypeInfo GetInfo() const { rpc::RemoteEntityTypeInfo info = { handler->GetId(), RBenderTest::ID }; return info; }

    template <typename T, typename P>
    void BenderGetServerDef( T* object, void (T::*func)(P result) );
    void BenderAddRoute( const Transport::Address& addr, const Network::NetAddress& netAddr );
    void BenderRemoveRoute( const Transport::Address& addr );
    void BenderInitialUpdateEnd();
    void BenderprocessVector(const nstl::vector<int>& value);
    template <typename T, typename P>
    void Benderprocess( T* object, void (T::*func)(P result) );
    void Bendersimple();
};
}
#endif // __R_BenderTest_H__
