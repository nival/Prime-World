using System;
using DAL.Entities;
using DAL.Repositories;
using log4net;
using Npgsql;
using NUnit.Framework;

namespace DAL.Tests.Entities
{

  public class AfterPartyTests : BaseTestFixture
  {

    public override void Setup()
    {
      NHibernateHelper.SessionFactory.Evict(typeof(AfterParty));
      TruncateTables("afterparty");
    }

    [Test]
    public void SimpleTest()
    {
      var obj = CreateAfterParty();
      using (var repo = new Repository<AfterParty>())
        repo.Add(obj);

      using (var repo = new Repository<AfterParty>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.PersistentId, obj2.PersistentId);
        Assert.AreEqual(obj.MMStarted, obj2.MMStarted);
        Assert.AreEqual(obj.Timestamp, obj2.Timestamp);
      }
    }

  }

}