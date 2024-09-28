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
  public enum ERerollShopResourceType
  {
    Resource1 = 1,
    Resource2 = 2,
    Resource3 = 4,
    Perl = 8,
    RedPerl = 16,
    Silver = 32,
    Gold = 64,
    All = 127,
  }

  public class RerollShopGroupCurrenciesModel : INewPricesListModel<RerollShopGroupCurrenciesInfoModel>
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

    private readonly List<RerollShopGroupCurrenciesInfoModel> newPrices = new List<RerollShopGroupCurrenciesInfoModel>();
    public List<RerollShopGroupCurrenciesInfoModel> NewPrices { get { return newPrices; } }

    public List<RerollShopGroupCurrenciesInfoModel> DefaultPrices = new List<RerollShopGroupCurrenciesInfoModel>();

    public SelectList CurrenciesEnum;

    public RerollShopGroupCurrenciesModel()
    {
      FillSelectListValues();
    }

    public RerollShopGroupCurrenciesModel( RerollShopGroupCurrenciesEvent info )
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      NewPrices.AddRange( info.Groups.Select( p => new RerollShopGroupCurrenciesInfoModel( p ) ) );
      FillSelectListValues();
    }

    private void FillSelectListValues()
    {
      CurrenciesEnum = new SelectList( new List<SelectListItem>
      {
        new SelectListItem {Text = "Resource1", Value = "Resource1"},
        new SelectListItem {Text = "Resource2", Value = "Resource2"},
        new SelectListItem {Text = "Resource3", Value = "Resource3"},
        new SelectListItem {Text = "Perl", Value = "Perl"},
        new SelectListItem {Text = "RedPerl", Value = "RedPerl"},
        new SelectListItem {Text = "Silver", Value = "Silver"},
        new SelectListItem {Text = "Gold", Value = "Gold"},
      } );
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
          "RerollShopGroupCurrenciesModel(NewPrices: [{0}], DefaultPrices: [{1}], Id: {2}, Description: {3}, Enabled: {4}, StartTime: {5}, EndTime: {6})",
          String.Join( ",", NewPrices.Select( p => p.ToString() ).ToArray() ),
          String.Join( ",", DefaultPrices.Select( p => p.ToString() ).ToArray() ),
          Id, Description, Enabled, StartTime, EndTime );
    }
  }

  public class RerollShopGroupCurrenciesInfoModel
  {
    public string Group { get; set; }

    public string Currencies { get; set; }

    private static readonly string[] _currenciesArray = {"Resource1", "Resource2", "Resource3", "Perl", "RedPerl", "Silver", "Gold"};

    public RerollShopGroupCurrenciesInfoModel()
    {
    }

    public RerollShopGroupCurrenciesInfoModel( RerollShopGroupCurrencies p )
    {
      Group = p.PersistentId;

      Currencies = "";
      for (var i = 0; i < _currenciesArray.Length; i++)
      {
        if ((p.Currencies & (1 << i)) != 0)
        {
          Currencies += _currenciesArray[i] + ",";
        }
      }

      if (Currencies.Length > 0)
        Currencies = Currencies.Remove( Currencies.Length - 1 );
    }

    public int GetIntCurrencies()
    {
      var parts = Currencies.Split(new[] {','});
      int value = 0;

      foreach (var part in parts)
      {
        var currency = part.Trim();
        for (var i = 0; i < _currenciesArray.Length; i++)
        {
          if (currency == _currenciesArray[i])
          {
            value |= 1 << i;
            break;
          }
        }
      }

      return value;
    }


    public override string ToString()
    {
      return String.Format( "RerollShopGroupCurrenciesInfoModel(Group: {0}, Currencies: {1}", Group, Currencies );
    }

  }
}