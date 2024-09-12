using System;
using System.Collections.Generic;
using System.ComponentModel;
using ClusterLib;

namespace ControlCenter.Areas.Cluster.Models
{
  public class ServiceInfoModel
  {
    [DisplayName("ID")]
    public string ServiceId { get; set; }

    [DisplayName("Type")]
    public string ServiceType { get; set; }

    [DisplayName("Machine")]
    public string Machine { get; set; }

    [DisplayName("Status")]
    public ServiceStatus Status { get; set; }

    [DisplayName("PID")]
    public int PID { get; set; }

    [DisplayName("Uptime")]
    public TimeSpan Uptime { get; set; }

    public List<ServiceParameter> Parameters { get; set; }

    public ServiceInfoModel()
    {
    }

    public ServiceInfoModel(ServiceInfo svc)
    {
      if (svc == null) throw new ArgumentNullException("svc");

      this.ServiceId = svc.Sid;
      this.ServiceType = svc.Stype;
      this.Machine = svc.Machine;
      this.Status = (ServiceStatus) svc.Status;
      this.PID = svc.Pid;
      this.Uptime = TimeSpan.FromSeconds(svc.Uptime);
    }

    public bool CanRunCommand(ServiceCommand command)
    {
      switch (Status)
      {
        case ServiceStatus.Running:
          return (int)(command & (ServiceCommand.Stop | ServiceCommand.Restart | ServiceCommand.SoftStop | ServiceCommand.SoftRestart)) > 0;

        case ServiceStatus.StartPending:
          return false;

        case ServiceStatus.Stopped:
          return (int)(command & (ServiceCommand.Start)) > 0;

        case ServiceStatus.StopPending:
          return false;

        case ServiceStatus.WaitingForStop:
          return false;

        case ServiceStatus.WaitingForRestart:
          return false;
      }

      return false;
    }
  }

  public enum ServiceStatus
  {
    Running = 1,
    Stopped = 2,
    StartPending = 3,
    StopPending = 4,
    WaitingForStop = 5,
    WaitingForRestart = 6
  }

  [Flags]
  public enum ServiceCommand
  {
    Start = 0x1,
    Stop = 0x2,
    Restart = 0x4,
    SoftStop = 0x8,
    SoftRestart = 0x10,
  }

  public struct ServiceParameter
  {
    public string Name { get; set; }
    public string Value { get; set; }
    public bool Changeable { get; set; }
    public bool NeedRestart { get; set; }
  }

  public enum GroupServicesBy
  {
    Machine,
    Type
  }
}