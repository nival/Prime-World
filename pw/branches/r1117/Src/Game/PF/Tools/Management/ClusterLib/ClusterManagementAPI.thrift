namespace csharp ClusterLib
namespace cpp ClusterAdmin.Thrift

enum ServiceStatus {
  RUNNING = 1,               // Service is currently running
  STOPPED = 2,               // Service is not running
  START_PENDING = 3,         // Service has received the "START" command, but has not started yet
  STOP_PENDING = 4,          // Service has received the "STOP" command, but has not stopped yet
  WAITING_FOR_STOP = 5,      // Service is waiting for all users to disconnect before stopping
  WAITING_FOR_RESTART = 6    // Service is waiting for all users to disconnect before restarting
}

struct ServiceParameter {
  1: string name,
  2: string value,
  3: bool changeable,
  4: bool needrestart
}

struct ServiceInfo {
  1: string sid,             // service id
  2: string stype,           // service type
  3: string machine,         // machine name
  4: ServiceStatus status,   // current status
  5: i32 pid,                // PID of process
  6: i32 uptime,             // uptime in seconds
  7: string backendaddr,     // backend address
  8: string frontendaddr,    // frontend address
  9: list<ServiceParameter> parameters
}

enum ServiceCommand {
  START = 1,
  STOP = 2,
  RESTART = 4,
  SOFT_STOP = 8,
  SOFT_RESTART = 16,
  RELOAD_CONFIG = 32,
}

service ClusterManagement {
  list<ServiceInfo> GetServices(),
  list<ServiceInfo> GetServicesByMachine(1: string machine),
  list<ServiceInfo> GetServicesByType(1: string stype),
  ServiceInfo GetServiceById(1: string serviceid),
  i32 ExecuteCommand(1: string serviceid, 2: ServiceCommand command, 3: string arguments),
  i32 ChangeParameters(1: string serviceid, 2: list<ServiceParameter> parameters, 3: bool saveinconfig=0)
}
