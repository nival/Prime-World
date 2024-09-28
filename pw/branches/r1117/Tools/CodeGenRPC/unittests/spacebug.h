namespace testnamespace
{

REMOTE class GenTest
{
public:
    RPC_ID(0xdd);
  
    REMOTE virtual const ServerDef& GetServerDef0() const = 0; 
    REMOTE virtual const ServerDef & GetServerDef1() const = 0; 
    REMOTE virtual const ServerDef &GetServerDef2() const = 0; 
    REMOTE void RemoveRoute0( const Transport::Address* addr ) = 0;
    REMOTE void RemoveRoute1( const Transport::Address *addr ) = 0;
    REMOTE void RemoveRoute2( const Transport::Address * addr ) = 0;
    REMOTE void processVector0(const nstl::vector<int>& value);
    REMOTE void processVector1(const nstl::vector<int> & value);
    REMOTE void processVector2(const nstl::vector<int> &value);
};

}