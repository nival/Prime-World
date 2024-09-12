using System;
using System.Collections.Generic;
using Thrift.Protocol;
using Thrift.Transport;
using log4net;

namespace ClusterLib
{
  public interface IClusterManagementService
  {
    List<ServiceInfo> GetAllServices();
    ServiceInfo GetServiceById(string serviceid);

    int ExecuteCommand(string serviceid, ServiceCommand command, string arguments);
  }

  public class ClusterManagementService : IClusterManagementService
  {
    private static ILog _log = LogManager.GetLogger(typeof(ClusterManagementService));

    private ClusterManagement.Client client;

    public ClusterManagementService(Uri address)
    {
      if (address == null) throw new ArgumentNullException("address");

      // init thrift client
      TTransport transport = new THttpClient(address);
      TProtocol proto = new TBinaryProtocol(transport);
      this.client = new ClusterManagement.Client(proto);
    }

    public List<ServiceInfo> GetAllServices()
    {
      try
      {
        return client.GetServices();
      }
      catch (TTransportException ex)
      {
        _log.Error(ex);
        return null;
      }
    }

    public ServiceInfo GetServiceById(string serviceid)
    {
      try
      {
        return client.GetServiceById(serviceid);
      }
      catch (TTransportException ex)
      {
        _log.Error(ex);
        return null;
      }
    }

    public int ExecuteCommand(string serviceid, ServiceCommand command, string arguments)
    {
      try
      {
        return client.ExecuteCommand(serviceid, command, arguments);
      }
      catch (TTransportException ex)
      {
        _log.Error(ex);
        return -1;
      }
    }
  }
}