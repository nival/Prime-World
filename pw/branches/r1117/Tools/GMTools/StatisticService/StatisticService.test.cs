using System;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;

namespace StatisticService.Test
{
  [TestFixture]
  public class StatisticServiceTest
  {
    [Test]
    public void Test()
    {
      var svc = new GameStatisticService();
    }
  }
}