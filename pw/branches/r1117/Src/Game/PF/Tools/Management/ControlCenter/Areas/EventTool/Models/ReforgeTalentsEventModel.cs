using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AccountLib;
using ControlCenter.Helpers;
namespace ControlCenter.Areas.EventTool.Models
{


    public class ReforgeTalentPriceModel
    {
        [DisplayName("Rarity")]
        [Required]
        public ETalentRarity Rarity { get; set; }

        [Required]
        public int RerollPrice { get; set; }

        [Required]
        public int UpgradePrice { get; set; }

        [Required]
        public int TalentsToUpgrade { get; set; }

        public ReforgeTalentPriceModel(ReforgeTalentPrice info)
        {
            Rarity = info.Rarity;
            RerollPrice = info.RerollPrice;
            UpgradePrice = info.UpgradePrice;
            TalentsToUpgrade = info.TalentsToUpgrade;
        }

        public ReforgeTalentPriceModel(ETalentRarity r)
        {
            Rarity = r;
        }

        public ReforgeTalentPriceModel()
        {
        }

    }

    public class ReforgeTalentsEventModel
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
    public List<ReforgeTalentPriceModel> ListReforgeTalentPrices { get; set; }
    public List<ReforgeTalentPriceModel> DefaultListReforgeTalentPrices { get; set; }


   protected void InitPrices()
        {
            DefaultListReforgeTalentPrices = new List<ReforgeTalentPriceModel>();
            ListReforgeTalentPrices = new List<ReforgeTalentPriceModel>();
            for (ETalentRarity i = ETalentRarity.magnificent; i <= ETalentRarity.outstanding; i++)
            {
                ListReforgeTalentPrices.Add(new ReforgeTalentPriceModel(i));
            }            
        }

   public void ReInitRarity()
   {

       var i = ETalentRarity.excellent;
       foreach (var p in ListReforgeTalentPrices)
       {
           p.Rarity = i;
           i++;
       }  
   }

    public ReforgeTalentsEventModel()
    {
        InitPrices();
    }



    public ReforgeTalentsEventModel(ReforgeTalentPrices info)
    {
      Description = info.Description;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();
      Enabled = info.Enabled;

        if (info.ListReforgeTalentPrices.Count != 0)
        {
            ListReforgeTalentPrices = new List<ReforgeTalentPriceModel>();
            ListReforgeTalentPrices.AddRange(info.ListReforgeTalentPrices.Select(p => new ReforgeTalentPriceModel(p)));
        }
        else InitPrices();
    }

  }

}
