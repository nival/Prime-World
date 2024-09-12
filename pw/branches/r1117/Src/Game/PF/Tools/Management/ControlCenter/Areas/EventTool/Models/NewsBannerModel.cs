using System;
using System.ComponentModel.DataAnnotations;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Web.Mvc;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{

  [DataContract]
  public class NewsBannerModel
  {
    public int TimeZone { get; set; }
    public int Id { get; set; }

    [Required]
    public string Description { get; set; }

    [Required]
    public DateTime StartTime { get; set; }

    [Required]
    public DateTime EndTime { get; set; }

    public bool Enabled { get; set; }

    [Required]
    public string ButtonText { get; set; }

    [Required]
    public string WindowCaption { get; set; }

    [Required]
    public string ButtonUrl { get; set; }

    [Required]
    public string MainUrl { get; set; }

    [Required]
    public string Tooltip { get; set; }

    [Required]
    public string MainUrlB { get; set; }

    public string LoginNetworks { get; set; }

    [Required]
    public int MinLordLevel { get; set; }

    [Required]
    public bool HideIfViewed { get; set; }

    [Required]
    public string Locale { get; set; }

    #region ExtensionJSON

    public SelectList TypeExtensionsList;
    public SelectList DataExtensionsList;

    public enum ENewsType
    {
      None, Interface, Url, Json
    }

    public enum InteractionWindowType
    {
      FS_None,
      FS_Event,
      FS_Clan,
      FS_Collection,
      W_Guild,
      W_HeroAcademy,
      W_HeroTalents,
      W_HeroTalentsPanel,
      W_RerollShop,
      W_TalentProduction,
      W_Tavern,
      W_PlayerChangeFlag,
      W_PlayerChangeFaction,
    }


    [DataMember]
    public ENewsType Type { get; set; }

    [DataMember]
    public InteractionWindowType Screen { get; set; }

    [DataMember]
    public string InteractionButtonText { get; set; }

    [DataMember]
    public string InterfaceArgs { get; set; }

    public string ExtensionJson { get; set; }

    #endregion


    public NewsBannerModel()
    {
      InitSelectLists();
      AddEmptyData();
    }

    public NewsBannerModel(NewsBanner info)
    {
      InitSelectLists();
      Id = info.PersistentId;
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Enabled = info.Enabled;
      ButtonText = info.ButtonText;
      WindowCaption = info.WindowCaption;
      ButtonUrl = info.ButtonUrl;
      MainUrl = info.MainUrl;
      Tooltip = info.Tooltip;
      MainUrlB = info.MainUrlB;
      LoginNetworks = info.LoginNetworks;
      MinLordLevel = info.MinLordLevel;
      HideIfViewed = info.HideIfViewed;
      Locale = info.Locale;
      if (!string.IsNullOrEmpty(info.ExtensionJson))
        Deserialize(info.ExtensionJson);
      else
        AddEmptyData();
      
    }

    private void InitSelectLists()
    {
      TypeExtensionsList = new SelectList(Enum.GetValues(typeof(ENewsType)).Cast<Enum>()
        .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));

      DataExtensionsList = new SelectList(Enum.GetValues(typeof(InteractionWindowType)).Cast<Enum>()
        .Select(e => new SelectListItem { Text = e.ToString(), Value = e.ToString() }));
    }


    public void Deserialize(string json)
    {
      var serializer = new DataContractJsonSerializer(typeof(NewsBannerModel));
      var stream = new MemoryStream(Encoding.UTF8.GetBytes(json)) { Position = 0 };
      var partitionModel = (NewsBannerModel) serializer.ReadObject(stream);
      ExtensionJson = json;

      Type = partitionModel.Type;
      Screen = partitionModel.Screen;
      InteractionButtonText = partitionModel.InteractionButtonText;
      InterfaceArgs = partitionModel.InterfaceArgs;
    }

    public void AddEmptyData()
    {
      Type = ENewsType.None;
      Screen = InteractionWindowType.FS_None;
      InterfaceArgs = "";
      InteractionButtonText = "";
    }

    public void UpdateExtensionJSON()
    {
      var serializer = new DataContractJsonSerializer(typeof(NewsBannerModel));
      var stream = new MemoryStream();
      serializer.WriteObject(stream, this);
      ExtensionJson = Encoding.UTF8.GetString(stream.ToArray());
    }

  }

}