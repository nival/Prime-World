using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using AccountLib;

namespace ControlCenter.Areas.EventTool.Models
{
  public enum RollEventItemTypeEnum
  {
    Resource = 0,
    Talent = 1,
    Skin = 2,
    Hero = 3,
    Lootbox = 4,
  }

  public class RollEventItemModel
  {
    #region Data fields

    [Required(ErrorMessage = "Item type required")]
    [DisplayName("Item type")]
    public RollEventItemTypeEnum ItemType { get; set; }

    [DisplayName("PersistentID")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string PersistentId { get; set; }

    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("ResourceTableSmallModel")]
    public ResourcesTableSmallModel Resource { get; set; }

    [Required(ErrorMessage = "Drop ratio must be defined as positive floating point value")]
    [DisplayName("Drop Ratio")]
    [Range(0.001d, 10000.0d, ErrorMessage = "Out of supported range")]
    public double Ratio { get; set; }

    #endregion

    #region Helper fields

    public bool IsRatioRequired { get; set; }

    #endregion

    public RollEventItemModel() : this(RollEventItemTypeEnum.Resource, true) { }

    public RollEventItemModel(RollEventItemTypeEnum defaultType, bool isRatioRequired = true)
    {
      ItemType = defaultType;
      PersistentId = string.Empty;
      Resource = new ResourcesTableSmallModel();
      Ratio = 1.0d;

      IsRatioRequired = isRatioRequired;
    }

    public RollEventItemModel(RollEventItem rollEventItem, bool isRatioRequired = true)
    {
      ItemType = (RollEventItemTypeEnum)rollEventItem.ItemType;
      PersistentId = rollEventItem.PersistentId;
      Resource = new ResourcesTableSmallModel(rollEventItem.Resource);
      Ratio = rollEventItem.Ratio;

      IsRatioRequired = isRatioRequired;
    }

    public RollEventItem ToRollEventItem()
    {
      RollEventItem rollEventItem = new RollEventItem()
      {
        ItemType = (RollEventItemType)ItemType,
        PersistentId = PersistentId,
        Resource = Resource.ToResourceTableSmall(),
        Ratio = Ratio
      };
      return rollEventItem;
    }

    public RollEventItemModel Clone()
    {
      var model = new RollEventItemModel(ItemType, IsRatioRequired)
      {
        PersistentId = PersistentId,
        Resource = Resource.Clone(),
        Ratio = Ratio
      };
      return model;
    }
  }
}