//!Component('GenTest.Local')
//!Component('GenTest.Remote')

namespace testnamespace
{

REMOTE class GenTest
{
public:
    RPC_ID(0xdd);
  
    REMOTE virtual const ServerDef& GetServerDef() const = 0; 
    REMOTE virtual void AddRoute( const Transport::Address& addr, const Network::NetAddress& netAddr ) = 0;
    REMOTE void RemoveRoute( const Transport::Address& addr ) = 0;
    REMOTE virtual void InitialUpdateEnd() = 0;
    REMOTE void processVector(const nstl::vector<int>& value)
    {
        vector_param0 = value;
    }
    REMOTE short process()
    {
     	return 1;
    }
    REMOTE void simple();
};

}

namespace benderovec
{

REMOTE class BenderTest
{
public:
    RPC_ID(0xdd);
  
    REMOTE virtual const ServerDef& BenderGetServerDef() const = 0; 
    REMOTE virtual void BenderAddRoute( const Transport::Address& addr, const Network::NetAddress& netAddr ) = 0;
    REMOTE void BenderRemoveRoute( const Transport::Address& addr ) = 0;
    REMOTE virtual void BenderInitialUpdateEnd() = 0;
    REMOTE void BenderprocessVector(const nstl::vector<int>& value)
    {
        vector_param0 = value;
    }
    REMOTE short Benderprocess()
    {
     	return 1;
    }
    REMOTE void Bendersimple();
};

}