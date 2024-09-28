using System;
using System.Collections.Generic;
using ClusterLib;
using ControlCenter.Areas.Monitoring.Models;
using log4net;
using MonitoringService;
using MonitoringSummaryLib;

namespace ControlCenter.Areas.Cluster.Models
{
  public interface IClusterService
  {
    IEnumerable<ServiceInfoModel> GetAllServices();
    ServiceInfoModel GetServiceById(string serviceId);
    bool ExecuteCommand(string serviceId, ServiceCommand command);

    int GetGameCCU();
    int GetSocialCCU();
    int GetNumberOfMatchmakingUsers();

    MonitoringInfoModel GetFullMonitoringInfo();
  }

  public class ClusterService : IClusterService
  {
    private static ILog _log = LogManager.GetLogger(typeof (ClusterService));

    private readonly IClusterManagementService clusterManagementService;
    private readonly IMonitoringSummaryService monitoringSummaryService;

    public static string ClusterAddress { get; set; }
    public static string MonitoringSummaryAddress { get; set; }

    public ClusterService()
    {
      // initialization of cluster management service
      Uri cluster_url;
      if (!String.IsNullOrEmpty(ClusterAddress) && Uri.TryCreate(ClusterAddress, UriKind.Absolute, out cluster_url))
      {
        clusterManagementService = new ClusterManagementService(cluster_url);
      }
      else
      {
        _log.ErrorFormat("Invalid cluster address {0}", ClusterAddress ?? "(null)");
        return;
      }

      // initialization of monitoring summary service
      Uri url;
      if (!String.IsNullOrEmpty(MonitoringSummaryAddress) && (Uri.TryCreate(MonitoringSummaryAddress, UriKind.Absolute, out url)))
      {
        monitoringSummaryService = new MonitoringSummaryService(url);
      }
      else
        _log.ErrorFormat("Invalid monitoring summary address {0}", MonitoringSummaryAddress ?? "(null)");
    }

    public ClusterService(IClusterManagementService svc, IMonitoringSummaryService msvc)
    {
      clusterManagementService = svc;
      monitoringSummaryService = msvc;
    }

    public IEnumerable<ServiceInfoModel> GetAllServices()
    {
      if (clusterManagementService == null)
      {
        _log.Error("Attempt to use not initialized cluster management service");
        return null;
      }
      
      List<ServiceInfo> services = clusterManagementService.GetAllServices();
      if (services == null)
        return null;

      var result = new List<ServiceInfoModel>();
      services.ForEach(s => result.Add(new ServiceInfoModel(s)));
      
      return result;
    }

    public ServiceInfoModel GetServiceById(string serviceId)
    {
      if (serviceId == null)
        throw new ArgumentNullException("serviceId");

      if (clusterManagementService == null)
      {
        _log.Error("Attempt to use not initialized cluster management service");
        return null;
      }

      var service = clusterManagementService.GetServiceById(serviceId);
      if (service == null)
        return null;

      return new ServiceInfoModel(service);
    }

    public bool ExecuteCommand(string serviceId, ServiceCommand command)
    {
      if (clusterManagementService == null)
      {
        _log.Error("Attempt to use not initialized cluster management service");
        return false;
      }

      int retcode = clusterManagementService.ExecuteCommand(serviceId, (ClusterLib.ServiceCommand) command, null);
      return retcode >= 0;
    }

    public int GetGameCCU()
    {
      if (monitoringSummaryService != null)
        return monitoringSummaryService.GetGameClusterCCU();

      _log.Warn("Can't get Game CCU, because monitoring summary service was not initialized");
      return -1;
    }

    public int GetSocialCCU()
    {
      if (monitoringSummaryService != null)
        return monitoringSummaryService.GetSocialClusterCCU();

      _log.Warn("Can't get Social CCU, because monitoring summary service was not initialized");
      return -1;
    }

    public int GetNumberOfMatchmakingUsers()
    {
      if (monitoringSummaryService != null)
        return monitoringSummaryService.GetNumberOfMatchmakingUsers();

      _log.Warn("Can't get number of matchmaking users, because monitoring summary service was not initialized");
      return -1;
    }

    public MonitoringInfoModel GetFullMonitoringInfo()
    {
      if (monitoringSummaryService != null)
      {
        MonitoringInfo info = monitoringSummaryService.GetFullMonitoringInfo();
        var model = new MonitoringInfoModel
                      {
                        BldCCU = "No info",
                        DwdCCU = "No info",
                        GameCCU = "No info",
                        MMakingUsers = "No info",
                        NerCCU = "No info",
                        OpsCCU = "No info",
                        OthCCU = "No info",
                        TrnCCU = "No info",
                        TutCCU = "No info"
                      };
        if (info == null)
          return model;

        if (info.Bld_ccu != -1) model.BldCCU = info.Bld_ccu.ToString();
        if (info.Dwd_ccu != -1) model.DwdCCU = info.Dwd_ccu.ToString();
        if (info.Game_ccu != -1) model.GameCCU = info.Game_ccu.ToString();
        if (info.Mmakingusers != -1) model.MMakingUsers = info.Mmakingusers.ToString();
        if (info.Ner_ccu != -1) model.NerCCU = info.Ner_ccu.ToString();
        if (info.Ops_ccu != -1) model.OpsCCU = info.Ops_ccu.ToString();
        if (info.Oth_ccu != -1) model.OthCCU = info.Oth_ccu.ToString();
        if (info.Trn_ccu != -1) model.TrnCCU = info.Trn_ccu.ToString();
        if (info.Tut_ccu != -1) model.TutCCU = info.Tut_ccu.ToString();
        return model;
      }

      _log.Warn("Can't get monitoring info, because monitoring summary service was not initialized");
      return null;
    }
  }
}