using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;

namespace DAL.Tests.Entities
{

  public class AfterPartyMembersTests : BaseTestFixture
  {

    public override void Setup()
    {
      NHibernateHelper.SessionFactory.Evict(typeof(Player));
      NHibernateHelper.SessionFactory.Evict(typeof(AfterParty));
      NHibernateHelper.SessionFactory.Evict(typeof(AfterPartyMember));
      TruncateTables("afterparty", "player");
    }

    [Test]
    public void SimpleTest()
    {
      var obj = CreateAfterPartyMember();
      using (var repo = new Repository<AfterPartyMember>())
        repo.Add(obj);

      using (var repo = new Repository<AfterPartyMember>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.PersistentId, obj2.PersistentId);
        Assert.AreEqual(obj.Player.Id, obj2.Player.Id);
        Assert.AreEqual(obj.AfterParty.Id, obj2.AfterParty.Id);
        Assert.AreEqual(obj.Kicked, obj2.Kicked);
        Assert.AreEqual(obj.Leaved, obj2.Leaved);
        Assert.AreEqual(obj.Timestamp, obj2.Timestamp);
      }
    }

  }

}