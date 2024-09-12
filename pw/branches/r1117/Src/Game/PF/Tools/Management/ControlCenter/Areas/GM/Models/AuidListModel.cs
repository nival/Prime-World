using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;

namespace ControlCenter.Areas.GM.Models
{
  public class AuidListModel
  {
    public List<AuidListMemberModel> Lists = new List<AuidListMemberModel>();
  }

  public class AuidListMemberModel
  {
    public int Index { get; set; }

    [DisplayName("Name")]
    public string Description { get; set; }

    [RegularExpression(@"((\d)+(\s)*(,)(\s)*)*(\d)+")]
    public string Auids { get; set; }

    public int Links { get; set; }

    public AuidListMemberModel()
    {
      Description = "";
      Index = -1;
      Auids = "";
    }

    public List<long> GetAuids()
    {
      return GetAuids(Auids);
    }

    public static List<long> GetAuids(string auidsString)
    {
      List<long> auidsInt;

      try
      {
        var auids = auidsString.Split(',');
        auidsInt =
          (from auid in auids where !String.IsNullOrEmpty(auid.Trim()) select Convert.ToInt64(auid.Trim())).ToList();
      }
      catch (OverflowException)
      {
        return null;
      }
      catch (FormatException)
      {
        return null;
      }

      return auidsInt;
    }
  }
}