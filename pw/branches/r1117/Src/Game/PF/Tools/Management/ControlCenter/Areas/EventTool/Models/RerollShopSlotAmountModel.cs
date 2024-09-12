using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class RerollShopSlotAmountModel : INewPricesListModel<RerollSlotAmountInfoModel>
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

    private readonly List<RerollSlotAmountInfoModel> newPrices = new List<RerollSlotAmountInfoModel>();
    public List<RerollSlotAmountInfoModel> NewPrices { get { return newPrices; } }

    public List<RerollSlotAmountInfoModel> DefaultPrices = new List<RerollSlotAmountInfoModel>();

    public RerollShopSlotAmountModel()
    {
    }

    public RerollShopSlotAmountModel( RerollShopSlotAmountEvent info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange( info.Slots.Select( p => new RerollSlotAmountInfoModel( p ) ) );
    }

    public override string ToString()
    {
      return
        String.Format(
          "RerollSlotAmountModel(NewAmounts: [{0}], DefaultAmounts: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join( ",", NewPrices.Select( p => p.ToString() ).ToArray() ),
          String.Join( ",", DefaultPrices.Select( p => p.ToString() ).ToArray() ),
          Id, Description, Enabled, StartTime, EndTime );
    }
  }

  public class RerollSlotAmountInfoModel
  {

    public string Slot { get; set; }

    public string Group { get; set; }

    public int Amount { get; set; }

    public RerollSlotAmountInfoModel()
    {
    }


    public RerollSlotAmountInfoModel( RerollShopSlotAmount p )
    {
      Slot = p.PersistentId;
      Group = p.GroupId;
      Amount = p.Amount;
    }


    public override string ToString()
    {
      return String.Format( "RerollSlotAmountInfoModel(Slot: {0}, Group:{1}, Amount: {2})", Slot, Group, Amount );
    }

  }
}