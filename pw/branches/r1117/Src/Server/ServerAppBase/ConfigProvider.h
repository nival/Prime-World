#ifndef CONFIG_PROVIDER_H_INCLUDED
#define CONFIG_PROVIDER_H_INCLUDED

namespace Transport
{

template<class TConfigStruc>
class ConfigObject : public BaseObjectMT, public TConfigStruc
{
  NI_DECLARE_REFCOUNT_CLASS_1( ConfigObject, BaseObjectMT );

public:
  explicit ConfigObject( const TConfigStruc & _data ) :
  TConfigStruc( _data )
  {}
};



template<class TConfigStruc>
class IConfigProvider : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IConfigProvider, IBaseInterfaceMT );

public:
  typedef ConfigObject<TConfigStruc> TConfig;

  virtual StrongMT<TConfig> Cfg() = 0;
  virtual void ReloadConfig() = 0;
};



template<class TConfigStruc, class TNewConfigPolicy>
class ConfigProvider : public IConfigProvider<TConfigStruc>, public BaseObjectMT, public TNewConfigPolicy
{
  NI_DECLARE_REFCOUNT_CLASS_2( ConfigProvider, IConfigProvider<TConfigStruc>, BaseObjectMT );
  typedef typename IConfigProvider<TConfigStruc>::TConfig TConfig;

public:
  ConfigProvider() :
  config( TNewConfigPolicy::CreateNewConfig() )
  {}

  //IConfigProvider
  virtual StrongMT<TConfig> Cfg()
  {
    threading::MutexLock lock( configMutex );
    return config;
  }

  //IConfigProvider
  virtual void ReloadConfig()
  {
    StrongMT<TConfig> cfg = TNewConfigPolicy::CreateNewConfig();
    threading::MutexLock lock( configMutex );
    config = cfg;
  }

private:
  threading::Mutex configMutex;
  StrongMT<TConfig> config;
};

} //namespace Transport

#endif //CONFIG_PROVIDER_H_INCLUDED
