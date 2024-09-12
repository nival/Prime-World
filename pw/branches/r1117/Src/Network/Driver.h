#ifndef DRIVER_H_F6E15FFF_496F_4266_97AF
#define DRIVER_H_F6E15FFF_496F_4266_97AF
#include "Network.h"
#include "ConnectionsContainer.h"
#include "../System/ThreadHelpers.h"
#include "DriverSettings.h"
#include "Connection.h"

namespace Network
{
  class Connection;
  class IncomingConnectionManager;

  class Driver : public INetworkDriver, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( Driver, INetworkDriver, BaseObjectMT )
  public:
    Driver(EDriverTrafficType::Enum tt = EDriverTrafficType::Light);
    ~Driver();
    int Process( volatile bool& isRunning );

    IConnectionsManager* CreateConnectionListener( const string& url, bool useCompression );
    StrongMT<IConnection> Connect( const string& url, bool useCompression );

    void SetTrafficType( EDriverTrafficType::Enum value );
    void SetStreamAllocator( IStreamAllocator* alloc ); 
    IStreamAllocator* GetStreamAllocator() const { return alloc; }

  private:

    typedef vector<StrongMT<IncomingConnectionManager> > LinksContainer;
    LinksContainer linkManagers;

    ConnectionsContainer container;

    ConnectionSettings settings;

    threading::Mutex mutex;
    threading::ProcessingThread<Driver>* driverThread;
    threading::Event threadStarted;

    StrongMT<IStreamAllocator> alloc;

    void Step();
  };
}
#endif //#define DRIVER_H_F6E15FFF_496F_4266_97AF
