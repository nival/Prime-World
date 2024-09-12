using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;

namespace ControlCenter.Areas.EventTool.Models
{
  public class ResourcesTableSmallModel
  {
    [Required]
    [DisplayName("First resource")]
    public int Resource1 { get; set; }

    [Required]
    [DisplayName("Second resource")]
    public int Resource2 { get; set; }

    [Required]
    [DisplayName("Third resource")]
    public int Resource3 { get; set; }

    [Required]
    [DisplayName("Silver")]
    public int Silver { get; set; }

    [Required]
    [DisplayName("Gold")]
    public int Gold { get; set; }

    [Required]
    [DisplayName("Crystals")]
    public int Perl { get; set; }

    [Required]
    [DisplayName("Red crystals")]
    public int RedPerl { get; set; }

    [DisplayName("Custom currency ID (default \"\")")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string CurrencyId { get; set; }

    [Required]
    [DisplayName("Custom currency")]
    public int Currency { get; set; }

    public ResourcesTableSmallModel()
    {
      CurrencyId = string.Empty;
    }

    public ResourcesTableSmallModel(ResourceTableSmall p)
    {
      Resource1 = p.Resource1;
      Resource2 = p.Resource2;
      Resource3 = p.Resource3;
      Silver = p.Silver;
      Gold = p.Gold;
      Perl = p.Perl;
      RedPerl = p.RedPerl;
      CurrencyId = p.CurrencyId;
      Currency = p.Currency;
    }

    public ResourceTableSmall ToResourceTableSmall()
    {
      var result = new ResourceTableSmall()
      {
        Resource1 = Resource1,
        Resource2 = Resource2,
        Resource3 = Resource3,
        Silver = Silver,
        Gold = Gold,
        Perl = Perl,
        RedPerl = RedPerl,
        CurrencyId = CurrencyId,
        Currency = Currency,
      };
      return result;
    }

    public ResourcesTableSmallModel Clone()
    {
      var model = new ResourcesTableSmallModel
      {
        Resource1 = Resource1,
        Resource2 = Resource2,
        Resource3 = Resource3,
        Silver = Silver,
        Gold = Gold,
        Perl = Perl,
        RedPerl = RedPerl,
        CurrencyId = CurrencyId,
        Currency = Currency
      };
      return model;
    }

    public override string ToString()
    {
      return string.Format("ResourceTableSmallModel(Resource1: {0}, Resource2: {1}, Resource3: {2}, Silver: {3}, Gold: {4}, Perl: {5}, RedPerl: {6})",
        Resource1, Resource2, Resource3, Silver, Gold, Perl, RedPerl);
    }
  }
}
