#ifndef __R_GenTest_H__
#define __R_GenTest_H__

#include <RPC/RPC.h>
namespace testnamespace
{
class RGenTest : public rpc::IRemoteEntity, public CObjectBase
{
    OBJECT_BASIC_METHODS(RGenTest);
public:
    rpc::EntityHandler* handler;
    rpc::CallWait* xxx;

    RPC_ID();
    RGenTest() : handler(0), xxx(0) {}
    RGenTest( rpc::EntityHandler* _handler, rpc::CallWait* _xxx )
    :   handler(_handler)
    ,   xxx(_xxx) {}

    ~RGenTest()
    {
        if( handler )
        {
            handler->OnDestruct();
        }
    }

    virtual rpc::RemoteEntityTypeInfo GetInfo() const { rpc::RemoteEntityTypeInfo info = { handler->GetId(), RGenTest::ID }; return info; }

    template <typename T, typename P>
    void GetServerDef( T* object, void (T::*func)(P result) );
    void AddRoute( const Transport::Address& addr, const Network::NetAddress& netAddr );
    void RemoveRoute( const Transport::Address& addr );
    void InitialUpdateEnd();
    void processVector(const nstl::vector<int>& value);
    template <typename T, typename P>
    void process( T* object, void (T::*func)(P result) );
    void simple();
};
}
#endif // __R_GenTest_H__
