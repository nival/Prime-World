using System.Collections.Generic;
using System.IO;
using ControlCenter.Areas.GM.Models;
using Moq;
using NUnit.Framework;
using log4net.Config;

namespace ControlCenter.Tests.Services.Geolocation
{

  [TestFixture]
  public class GeolocationCacheTests
  {
    [TestFixtureSetUp]
    public void FixtureSetUp()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    [Test]
    public void GetCountriesTest()
    {
      var mockrequester = new Mock<IGeolocationDictionaryRequester>();
      var mockparser = new Mock<IJsonParser>();

      mockrequester.Setup(m => m.GetCountries()).Returns("{countries}").AtMostOnce();
      mockparser.Setup(m => m.ParseCountries("{countries}")).Returns(new List<Country> { new Country { Code = "TC", Name = "Test Country" } }).AtMostOnce();

      var cache = new GeolocationCache(mockrequester.Object, mockparser.Object);

      var c1 = cache.GetCountries();
      Assert.IsNotNull(c1);
      Assert.AreEqual("TC", c1[0].Code);

      var c2 = cache.GetCountries();
      Assert.IsNotNull(c2);
      Assert.AreEqual("TC", c2[0].Code);

      mockrequester.VerifyAll();
      mockparser.VerifyAll();
    }

    [Test]
    public void GetRegionsTest()
    {
      var mockrequester = new Mock<IGeolocationDictionaryRequester>();
      var mockparser = new Mock<IJsonParser>();

      mockrequester.Setup(m => m.GetCountries()).Returns("{countries}").AtMostOnce();
      mockrequester.Setup(m => m.GetRegions("111")).Returns("{regions}").AtMostOnce();
      mockparser.Setup(m => m.ParseCountries("{countries}")).Returns(new List<Country> { new Country { Id= "111", Code = "TC", Name = "Test Country" } }).AtMostOnce();
      mockparser.Setup(m => m.ParseRegions("{regions}")).Returns(new List<Region> { new Region { Region_id = "01", Region_code = "101", Region_name_en = "Test Region"} }).AtMostOnce();

      var cache = new GeolocationCache(mockrequester.Object, mockparser.Object);

      var r1 = cache.GetRegions("111");
      Assert.IsNotNull(r1);
      Assert.AreEqual("01", r1[0].Region_id);
      Assert.AreEqual("101", r1[0].Region_code);
      Assert.AreEqual("Test Region", r1[0].Region_name_en);

      var r2 = cache.GetRegions("111");
      Assert.IsNotNull(r2);
      Assert.AreEqual("01", r2[0].Region_id);
      Assert.AreEqual("101", r2[0].Region_code);
      Assert.AreEqual("Test Region", r2[0].Region_name_en);

      mockrequester.VerifyAll();
      mockparser.VerifyAll();
    }

    [Test]
    public void GetRegionsByIncorrectCountryCodeTest()
    {
      var mockrequester = new Mock<IGeolocationDictionaryRequester>();
      var mockparser = new Mock<IJsonParser>();

      mockrequester.Setup(m => m.GetCountries()).Returns("{countries}").AtMostOnce();
      mockparser.Setup(m => m.ParseCountries("{countries}")).Returns(new List<Country> { new Country { Code = "TC", Name = "Test Country" } }).AtMostOnce();

      var cache = new GeolocationCache(mockrequester.Object, mockparser.Object);

      var r1 = cache.GetRegions("XB");
      Assert.IsNull(r1);

      mockrequester.Verify(m => m.GetRegions("XB"), Times.Never());
      mockrequester.VerifyAll();
      mockparser.VerifyAll();
    }

  }

}