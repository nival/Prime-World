namespace SR
{

//REMOTE Protocol::SWStr nstl::wstring
//REMOTE Simple CObj<Slave>
//REMOTE SimpleType CObj<Hero>

REMOTE struct SimpleRabbit : rpc::IRemoteEntity
{
    RPC_ID(0xdd);
    nstl::Bool<false> is_processed;
    short short_creation_param0;
    int constructor_number_called;
    InitialSnapshot msg;
    InitialSnapshot msg0;
    InitialSnapshot msg1;
    nstl::Bool<false> isSnapshotRecieved;
    
    SimpleRabbit() {
        constructor_number_called = 1;
    }
    
    SimpleRabbit(short value):
    short_creation_param0(value)
    {
        constructor_number_called = 2;
    }    
    
    REMOTE virtual const ServerDef& GetServerDef() const = 0; 
    REMOTE virtual void AddRoute( Transport::Address const &addr, const Network::NetAddress& netAddr ) = 0;
    //megakom
    REMOTE virtual void RemoveRoute( const Transport::Address& addr ) = 0;
    REMOTE virtual void InitialUpdateEnd() = 0;
    REMOTE void processVector(const /*Komment*/ nstl::vector<int>& value)
    {
        vector_param0 = value;
    }
    REMOTE virtual const Protocol::IdGenRange& getInt32IdRange(int width) = 0;

    REMOTE nstl::vector<ssstruct> listtest(const nstl::vector<ssstruct>& value)
    {
        return value;
    }
    REMOTE virtual void AddClient( rpc::SimpleRabbit* _client ) = 0;


    REMOTE CQuat quat;
    REMOTE nstl::wstring namew;
    REMOTE CObj<Hero> iamhero;


    REMOTE Protocol::SWStr tstr;
    REMOTE nstl::vector<Protocol::SWStr> tvstr;
    REMOTE SimpleType tst;
    REMOTE Simple slaver;
};

}