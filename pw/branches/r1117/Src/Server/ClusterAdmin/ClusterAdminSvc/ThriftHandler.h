#pragma once

#include "gen-cpp/ClusterManagement.h"
#include "Pointers/Strong.h"

namespace ClusterAdmin
{
  class ClusterAdminImpl;

  class ThriftHandler : public Thrift::ClusterManagementIf
  {
  public:
    ThriftHandler(StrongMT<ClusterAdminImpl> const & _impl);
    ~ThriftHandler();

  public:

    //  ClusterManagementIf
    virtual void GetServices(std::vector<Thrift::ServiceInfo> & _return);
    virtual void GetServicesByMachine(std::vector<Thrift::ServiceInfo> & _return, const std::string& machine);
    virtual void GetServicesByType(std::vector<Thrift::ServiceInfo> & _return, const std::string& stype);
    virtual void GetServiceById(Thrift::ServiceInfo& _return, const std::string& serviceid);
    virtual int32_t ExecuteCommand(const std::string& serviceid, const Thrift::ServiceCommand::type command, const std::string& arguments);
    virtual int32_t ChangeParameters(const std::string& serviceid, const std::vector<Thrift::ServiceParameter> & parameters, const bool saveinconfig);

  private:
    StrongMT<ClusterAdminImpl> impl;
  };
}
