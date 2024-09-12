using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class RerollShopGroupProbabilityModel : INewPricesListModel<RerollShopGroupProbabilityInfoModel>
  {
    public int TimeZone { get; set; }
    public int Id { get; set; }

    [Required]
    public string Description { get; set; }

    public bool Enabled { get; set; }

    [Required]
    public DateTime StartTime { get; set; }

    [Required]
    public DateTime EndTime { get; set; }

    private readonly List<RerollShopGroupProbabilityInfoModel> newPrices = new List<RerollShopGroupProbabilityInfoModel>();
    public List<RerollShopGroupProbabilityInfoModel> NewPrices { get { return newPrices; } }

    public List<RerollShopGroupProbabilityInfoModel> DefaultPrices = new List<RerollShopGroupProbabilityInfoModel>();

    public RerollShopGroupProbabilityModel()
    {
    }

    public RerollShopGroupProbabilityModel( RerollShopGroupProbabilityEvent info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange( info.Groups.Select( p => new RerollShopGroupProbabilityInfoModel( p ) ) );
    }

    public override string ToString()
    {
      return
        String.Format(
          "RerollSlotPriceModel(NewPrices: [{0}], DefaultPrices: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join( ",", NewPrices.Select( p => p.ToString() ).ToArray() ),
          String.Join( ",", DefaultPrices.Select( p => p.ToString() ).ToArray() ),
          Id, Description, Enabled, StartTime, EndTime );
    }
  }

  public class RerollShopGroupProbabilityInfoModel
  {

    public string Group { get; set; }
    public int RerollTime { get; set; }
    public int Probability { get; set; }
    public int MinUpgradeLevel { get; set; }
    public int MaxUpgradeLevel { get; set; }

    public RerollShopGroupProbabilityInfoModel()
    {
    }


    public RerollShopGroupProbabilityInfoModel( RerollShopGroupProbability p )
    {
      Group = p.PersistentId;
      RerollTime = p.RerollTime;
      Probability = p.Probability;
      MinUpgradeLevel = p.MinUpgradeLevel;
      MaxUpgradeLevel = p.MaxUpgradeLevel;
    }


    public override string ToString()
    {
      return
        String.Format(
          "RerollShopGroupProbabilityInfoModel(Group: {0}, RerollTime: {1}, Probability: {2}, MinUpgradeLevel: {3}, MaxUpgradeLevel: {4})",
          Group, RerollTime, Probability, MinUpgradeLevel, MaxUpgradeLevel);
    }

  }
}