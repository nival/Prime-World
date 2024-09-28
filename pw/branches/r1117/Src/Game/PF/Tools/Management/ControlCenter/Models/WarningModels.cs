using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace ControlCenter.Models
{
  public class WarningModel
  {
    public String Message { get; set; }
    public String Controller { get; set; }
    public String Action { get; set; }
    public RouteValueDictionary RedirectRoute { get; set; }
    public String RedirectUrl { get; set; }
  }
}
