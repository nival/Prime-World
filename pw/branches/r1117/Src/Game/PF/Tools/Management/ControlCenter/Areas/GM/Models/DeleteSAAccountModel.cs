using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Web;

namespace ControlCenter.Areas.GM.Models
{
  public class DeleteSaAccountModel
  {
    public long Auid { get; set; }

    [DisplayName("Yes")]
    public bool Confirm1 { get; set; }
    [DisplayName("I")]
    public bool Confirm2 { get; set; }
    [DisplayName("Am")]
    public bool Confirm3 { get; set; }

    public string Result { get; set; }
    public bool Done { get; set; }

    public DeleteSaAccountModel()
    {
      Auid = 0;
      Confirm1 = false;
      Confirm2 = false;
      Confirm3 = false;

      Result = string.Empty;
      Done = false;
    }

    public bool Confirmed()
    {
      return Confirm1 && Confirm2 && Confirm3 && (Auid > 0);
    }
  }
}