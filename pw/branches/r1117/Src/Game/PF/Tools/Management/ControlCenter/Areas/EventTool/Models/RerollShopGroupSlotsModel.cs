using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class RerollShopGroupSlotsModel : INewPricesListModel<RerollShopGroupSlotsInfoModel>
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

    public SelectList Slots { get; set; }

    private readonly List<RerollShopGroupSlotsInfoModel> newPrices = new List<RerollShopGroupSlotsInfoModel>();
    public List<RerollShopGroupSlotsInfoModel> NewPrices { get { return newPrices; } }

    public List<RerollShopGroupSlotsInfoModel> DefaultPrices = new List<RerollShopGroupSlotsInfoModel>();

    public RerollShopGroupSlotsModel()
    {
    }

    public RerollShopGroupSlotsModel( RerollShopGroupSlotsEvent info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange( info.Groups.Select( p => new RerollShopGroupSlotsInfoModel( p ) ) );
    }

    public static string GetAllTexts( SelectList list )
    {
      return String.Join( "\", \"",
        list.Items.OfType<SelectListItem>().ToList().Count == 0
          ? list.Select( x => x.Text ).ToArray()
          : list.Items.OfType<SelectListItem>().ToList().Select( x => x.Text ).ToArray() );
    }

    public static string GetAllValues( SelectList list )
    {
      return String.Join( "\", \"", list.Items.OfType<SelectListItem>().ToList().Select( x => x.Value ).ToArray() );
    }

    public override string ToString()
    {
      return
        String.Format(
          "RerollShopGroupSlotsModel(NewPrices: [{0}], DefaultPrices: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join( ",", NewPrices.Select( p => p.ToString() ).ToArray() ),
          String.Join( ",", DefaultPrices.Select( p => p.ToString() ).ToArray() ),
          Id, Description, Enabled, StartTime, EndTime );
    }
  }

  public class RerollShopGroupSlotsInfoModel
  {

    public string Group { get; set; }

    public string Slots { get; set; }



    public RerollShopGroupSlotsInfoModel()
    {
      Slots = "";
    }


    public RerollShopGroupSlotsInfoModel( RerollShopGroupSlots p )
    {
      Group = p.GroupId;
      Slots = "";
      foreach ( var slot in p.PersistentIds )
      {
        Slots += slot + ",";
      }
      if (Slots != "") Slots = Slots.Remove( Slots.Length - 1 );
    }


    public override string ToString()
    {
      return String.Format( "RerollShopGroupSlotsInfoModel(Group: {0}, Slots: {1})", Group, Slots );
    }

  }
}