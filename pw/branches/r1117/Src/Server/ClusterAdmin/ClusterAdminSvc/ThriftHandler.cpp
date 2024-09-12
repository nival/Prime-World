#include "ThriftHandler.h"
#include "ClusterAdminImpl.h"

namespace ClusterAdmin
{
  ThriftHandler::ThriftHandler(StrongMT<ClusterAdminImpl> const & _impl)
    :impl(_impl)
  {
  }

  ThriftHandler::~ThriftHandler()
  {
  }

  void ThriftHandler::GetServices(std::vector<Thrift::ServiceInfo> & _return)
  {
    impl->GetServices(_return);
  }

  void ThriftHandler::GetServicesByMachine(std::vector<Thrift::ServiceInfo> & _return, const std::string& machine)
  {
    impl->GetServicesByMachine(_return, machine);
  }

  void ThriftHandler::GetServicesByType(std::vector<Thrift::ServiceInfo> & _return, const std::string& stype)
  {
    impl->GetServicesByType(_return, stype);
  }

  void ThriftHandler::GetServiceById(Thrift::ServiceInfo& _return, const std::string& serviceid)
  {
    impl->GetServiceById(_return, serviceid);
  }

  int32_t ThriftHandler::ExecuteCommand(const std::string& serviceid, const Thrift::ServiceCommand::type command, const std::string& arguments)
  {
    return impl->ExecuteCommand(serviceid, command, arguments);
  }

  int32_t ThriftHandler::ChangeParameters(const std::string& serviceid, const std::vector<Thrift::ServiceParameter> & parameters, const bool saveinconfig)
  {
    return impl->ChangeParameters(serviceid, parameters, saveinconfig);
  }
}
