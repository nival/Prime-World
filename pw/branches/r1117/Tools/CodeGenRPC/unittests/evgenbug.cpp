REMOTE class RemoteApi : public rpc::ISharedEntity
{

nstl::Bool<false> isProcessed;
public:

REMOTE void callRemote()
{ isProcessed = true; }

REMOTE const test::Structure& finc()
{
  return test::Structure();
}

REMOTE const test::InitialSnapshot& GetServerDef() const
{
  return msg;
}
  REMOTE test::RBattleInstance* CreateNew();
};