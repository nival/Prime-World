using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Web.Mvc;
using ControlCenter.Areas.GM.Controllers;
using ControlCenter.Areas.GM.Models;
using NUnit.Framework;

namespace ControlCenter.Tests.Models
{
  [TestFixture]
  class DynamicQuestsTest
  {
    [Test]
    public void TestDeserializationAcceptFilter()
    {
      const string json = "{\"MinLordLevel\":10,\"MaxLordLevel\":11,\"Faction\":\"B\",\"LastLoginTime\":50,"
                          + "\"NoHero\":\"aaa\",\"NoSkin\":\"bbb\",\"NoFlag\":\"rak\",\"NoBuilding\":\"rrr\",\"HeroesOfMinRating\":{\"Items\":\"ccc\",\"Value\":21},\"HeroesOfForce\""
                          + ":{\"Items\":\"ddd\",\"Value\":22},\"HeroesOfLevel\":{\"Items\":\"eee\",\"Value\":22},\"LastPaymentTime\""
                          + ":55,\"BuildingOfLevel\":{\"Items\":\"ggg\",\"Value\":23},\"InGuild\":\"True\",\"Donate\":\"False\","
                          + "\"HasPremium\":\"\",\"HasLamp\":\"\",\"Quests\":[]}";

      AcceptFilter temp;
      try
      {
        var serializer = new DataContractJsonSerializer(typeof(AcceptFilter));
        var stream = new MemoryStream(Encoding.UTF8.GetBytes(json)) { Position = 0 };
        temp = (AcceptFilter)serializer.ReadObject(stream);
      }
      catch (Exception)
      {
        temp = null;
      }

      Assert.AreNotEqual(temp, null);
    }

    [Test]
    public void TestDeserializationQuestData()
    {
      const string json = "{\"QuestCheckType\":3,\"ModelDataCondition\":{\"TypeToCollect\":0,\"PersistentId\":\"\",\"TotalValue\":6},\"Description\":\"ууууаа\",\"ButtonDescription\":\"ккк\"}";
      //const string json = "{\"ButtonDescription\":\"kkk\",\"Description\":\"yyyyaa\",\"ModelDataCondition\":{\"PersistentId\":\"\",\"TotalValue\":6,\"TypeToCollect\":0},\"QuestCheckType\":3}";

      QuestData temp;
      try
      {
        var serializer = new DataContractJsonSerializer(typeof(QuestData));
        var stream = new MemoryStream(Encoding.UTF8.GetBytes(json)) { Position = 0 };
        temp = (QuestData)serializer.ReadObject(stream);
      }
      catch (Exception)
      {
        temp = null;
      }

      Assert.AreNotEqual(temp, null);
    }

    [Test]
    public void TestSerializationQuestData()
    {
      var test = new QuestData
      {
        QuestCheckType = DynamicQuestCheckType.ModelData,
        ModelDataCondition = new ModelDataCondition {TypeToCollect = 0, PersistentId = "", TotalValue = 6},
        Description = "yyyyaa",
        ButtonDescription = "kkk"
      };
      const string json = "{\"ButtonDescription\":\"kkk\",\"Description\":\"yyyyaa\",\"ModelDataCondition\":{\"PersistentId\":\"\",\"TotalValue\":6,\"TypeToCollect\":0},\"QuestCheckType\":3}";

      string newJson;
      try
      {
        var serializer = new DataContractJsonSerializer(typeof(QuestData));
        var stream = new MemoryStream();
        serializer.WriteObject(stream, test);
        newJson = Encoding.Default.GetString(stream.ToArray());
      }
      catch (Exception)
      {
        newJson = "";
      }

      Assert.IsFalse(String.IsNullOrEmpty(newJson));
      Console.WriteLine(newJson);
      Console.WriteLine(json);
    }

    [Test]
    public void TestDeserializationAwards()
    {
      const string json = "{\"AwardType\":8,\"TextData\":\"excellent\",\"Value\":10}";

      DynamicQuestAward temp;
      try
      {
        var serializer = new DataContractJsonSerializer(typeof(DynamicQuestAward));
        var stream = new MemoryStream(Encoding.Default.GetBytes(json)) { Position = 0 };
        temp = (DynamicQuestAward)serializer.ReadObject(stream);
      }
      catch (Exception)
      {
        temp = null;
      }

      Assert.AreNotEqual(temp, null);
    }

    [Test]
    public void TestDeserealizationAll()
    {
      const string json = "{\"AcceptFilter\":{\"MinLordLevel\":0,\"MaxLordLevel\":40,\"Faction\":\"All\",\"LastLoginTime\":0,"
                          + "\"NoHero\":\"\",\"NoSkin\":\"\",\"NoFlag\":\"\",\"NoBuilding\":\"\",\"HeroesMinOfRating\":{\"Items\":\"\",\"Value\":0},\"HeroesOfForce\""
                          + ":{\"Items\":\"\",\"Value\":0},\"HeroesOfLevel\":{\"Items\":\"\",\"Value\":0},\"LastPaymentTime\""
                          + ":0,\"BuildingOfLevel\":{\"Items\":\"\",\"Value\":0},\"InGuild\":\"\",\"Donate\":\"\","
                          + "\"HasPremium\":\"\",\"HasLamp\":\"\",\"Quests\":[]},\"QuestData\":[{\"QuestCheckType\":3,"
                          + "\"ModelDataCondition\":{\"TypeToCollect\":0,\"PersistentId\":\"\",\"TotalValue\":6},\"Description\""
                          + ":\"ууууаа\",\"ButtonDescription\":\"ккк\"}],\"Awards\":[{\"AwardType\":8,\"TextData\":\"excellent\","
                          + "\"Value\":10}],\"NPCPortret\":\"http://ru.playpw.com/images/promo/flamefox_icon.png\",\"QuestName\":"
                          + "\"Логин_тест_получение_бонусов_ура_ура_ура\",\"QuestDescription\":\"ееее\",\"QuestStartTime\":"
                          + "1417453200,\"QuestEndTime\":1418922000,\"AutoAccept\":\"False\", \"CompletionText\":\"fdsfsd\",\"DescriptionImageUrl\":\"\"}";

      DynamicQuestDataModel temp;
      try
      {
        temp = DynamicQuestDataModel.Deserialize(json);
      }
      catch (Exception)
      {
        temp = null;
      }

      Assert.AreNotEqual(temp, null);
    }
  }
}
