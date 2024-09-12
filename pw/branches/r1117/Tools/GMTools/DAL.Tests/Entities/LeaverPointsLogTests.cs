using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;

namespace DAL.Tests.Entities
{

  public class LeaverPointsLogTests : BaseTestFixture
  {

    public override void Setup()
    {
      NHibernateHelper.SessionFactory.Evict(typeof(Player));
      NHibernateHelper.SessionFactory.Evict(typeof(LeaverPointsLog));
      TruncateTables("player", "leaverpointslog");
    }

    [Test]
    public void SimpleTest()
    {
      var obj = CreateLeaverPointsLog();
      using (var repo = new Repository<LeaverPointsLog>())
        repo.Add(obj);

      using (var repo = new Repository<LeaverPointsLog>())
      {
        var obj2 = repo.GetById(obj.Id);
        Assert.IsNotNull(obj2);
        Assert.AreNotSame(obj, obj2);
        Assert.AreEqual(obj.Player.Id, obj2.Player.Id);
        Assert.AreEqual(obj.PersistentId, obj2.PersistentId);
        Assert.AreEqual(obj.Type, obj2.Type);
        Assert.AreEqual(obj.LeaverPointsChange, obj2.LeaverPointsChange);
        Assert.AreEqual(obj.LeaverPointsTotal, obj2.LeaverPointsTotal);
        Assert.AreEqual(obj.IsLeaverChanged, obj2.IsLeaverChanged);
        Assert.AreEqual(obj.IsLeaver, obj2.IsLeaver);
        Assert.AreEqual(obj.IsBadBehaviour, obj2.IsBadBehaviour);
        Assert.AreEqual(obj.Timestamp, obj2.Timestamp);
      }
    }

  }

}