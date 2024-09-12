using System.IO;
using System.Linq;
using ControlCenter.Areas.GM.Models;
using NUnit.Framework;
using log4net.Config;

namespace ControlCenter.Tests.Services.Geolocation
{

  public class JsonParserTests
  {

    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }


    [Test]
    public void ParseCountriesTest()
    {
      var str = "{\"53\":{\"code\":\"AF\",\"name\":\"Afghanistan\"},\"143\":{\"code\":\"AX\",\"name\":\"Aland Islands\"},\"128\":{\"code\":\"AL\",\"name\":\"Albania\"}}";

      var json = new JsonParser();
      var countries = json.ParseCountries(str);

      Assert.AreEqual(3, countries.Count); 
      // ordered by code
      Assert.AreEqual("53", countries[0].Id);
      Assert.AreEqual("AF", countries[0].Code); 
      Assert.AreEqual("Afghanistan", countries[0].Name);
      Assert.AreEqual("143", countries[1].Id);
      Assert.AreEqual("AX", countries[1].Code);
      Assert.AreEqual("Aland Islands", countries[1].Name);
      Assert.AreEqual("128", countries[2].Id);
      Assert.AreEqual("AL", countries[2].Code);
      Assert.AreEqual("Albania", countries[2].Name);
    }


    [Test]
    public void ParseInvalidJsonTest()
    {
      var str = "\"53\":{\"code\":\"AF\",\"name\":\"Afghanistan\"}}";

      var json = new JsonParser();
      var countries = json.ParseCountries(str);

      Assert.IsNull(countries);
    }


    [Test]
    public void ParseExcessingAttributeJsonObjectTest()
    {
      var str = "{\"53\":{\"code\":\"AF\",\"name\":\"Afghanistan\",\"language\":\"Pashto\"}}";

      var json = new JsonParser();
      var countries = json.ParseCountries(str);

      Assert.AreEqual(1, countries.Count);
      Assert.AreEqual("53", countries[0].Id);
      Assert.AreEqual("AF", countries[0].Code);
      Assert.AreEqual("Afghanistan", countries[0].Name);
    }


    [Test]
    public void ParseRegionsTest()
    {
      var str = "[{\"region_code\":\"01\",\"region_id\":\"3221\",\"region_name_en\":\"Adygeya, Republic of\",\"cities\":[\"Maykop\",\"Enem\",\"Dagestanskaya\",\"Litvinov\"]},{\"region_code\":\"03\",\"region_id\":\"3223\",\"region_name_en\":\"Gorno-Altay\",\"cities\":[\"Gorno-altaysk\",\"Ust-koksa\"]}]";

      var json = new JsonParser();
      var regions = json.ParseRegions(str);

      Assert.AreEqual(2, regions.Count);

      Assert.AreEqual("01", regions[0].Region_code);
      Assert.AreEqual("3221", regions[0].Region_id);
      Assert.AreEqual("Adygeya, Republic of", regions[0].Region_name_en);
      Assert.AreEqual(4, regions[0].Cities.Count);

      Assert.AreEqual("03", regions[1].Region_code);
      Assert.AreEqual("3223", regions[1].Region_id);
      Assert.AreEqual("Gorno-Altay", regions[1].Region_name_en);
      Assert.AreEqual(2, regions[1].Cities.Count);
    }

  }

}