using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Models
{
  public class BruteForceDefenderModel
  {
    [DisplayName("Email for PWC accounts")]
    public string Email { get; set; }
    public string ErrorIfExistToShow { get; set; }
    public BruteForceDefenderModel()
    {
    }

    public BruteForceDefenderModel(BruteForceDefenderModel info)
      : this()
    {
      if ( info == null )
        throw new ArgumentNullException( "info" );

      this.Email = info.Email;
    }
  }

  public class BruteForceAccountModel
  {
      public BruteForceAccountModel()
      {
          Visible = false;
      }
      public BruteForceAccountModel(BruteForceAccountShortInfo info)
      {
          BanTime = (DateTime?)info.BanTime.FromUnixTimestamp() ;
          Email = info.Email;
          Count = info.Count;
          Ip = info.Ip;
          Visible = true;
      }

    [Required]
    [DisplayName("Date format")]
    public DateTime? BanTime { get; set; }
    public string Email { get; set; }
    public int Count { get; set; }
    public string Ip { get; set; }
    public string ErrorIfExistToShow { get; set; }
    public bool Visible { get; set; }

  }
  public class BannedIpModel
  {
      public BannedIpModel()
      {
      }
      public BannedIpModel(BannedIpShortInfo info)
      {
          BanTime = (DateTime?)info.BanTime.FromUnixTimestamp();
          Accounts = info.Accounts;
          Tryes = info.Tryes;
          Ip = info.Ip;
      }

      [Required]
      [DisplayName("Date format")]
      public DateTime? BanTime { get; set; }
      public int Accounts { get; set; }
      public int Tryes { get; set; }
      public string Ip { get; set; }
      public string ErrorIfExistToShow { get; set; }

}

  public class BannedIpFullListModel
  {
        private const int PAGE_LIMIT = 30;
        public int Skip { get; set; }
        public int Limit { get; set; }
        
        public BannedIpFullListModel()
        {
            Limit = PAGE_LIMIT;
            Skip = 0;
        }

       public BannedIpFullListModel(BannedIpFullListInfo info)
       {
           IpList = new List<BannedIpModel>();
           IpList.AddRange(info.IpList.ConvertAll(new Converter<BannedIpShortInfo, BannedIpModel>( i => new BannedIpModel(i) )));
           Result = info.Result;
           Count = info.Count;
           Limit = PAGE_LIMIT;
           Skip = 0;
       }
        public List<BannedIpModel> IpList;
        public RequestResult Result;
        public string ErrorIfExistToShow { get; set; }
        public int Count { get; set; }
        
    }

}
