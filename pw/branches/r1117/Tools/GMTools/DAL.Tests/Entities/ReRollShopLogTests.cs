using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;

namespace DAL.Tests.Entities
{

    public class ReRollAhopTests : BaseTestFixture
    {

        public override void Setup()
        {
            NHibernateHelper.SessionFactory.Evict(typeof(Player));
            NHibernateHelper.SessionFactory.Evict(typeof(ReRollShopLog));
            TruncateTables( "player", "rerollshoplog" );
        }

        [Test]
        public void SimpleTest()
        {
            var obj = CreatReRollShopLog();
            using (var repo = new Repository<ReRollShopLog>())
                repo.Add(obj);

            using (var repo = new Repository<ReRollShopLog>())
            {
                var obj2 = repo.GetById(obj.Id);
                Assert.IsNotNull(obj2);
                Assert.AreNotSame(obj, obj2);
                Assert.AreEqual(obj.Player.Id, obj2.Player.Id);
                Assert.AreEqual(obj.Auid, obj2.Auid);
                Assert.AreEqual(obj.ItemId, obj2.ItemId);
                Assert.AreEqual(obj.ItemGroup, obj2.ItemGroup);
                Assert.AreEqual(obj.ItemPrice, obj2.ItemPrice);
                Assert.AreEqual(obj.ItemPriceType, obj2.ItemPriceType);
                Assert.AreEqual(obj.RerollCount, obj2.RerollCount);
                Assert.AreEqual(obj.SlotType, obj2.SlotType);
                Assert.AreEqual(obj.Timestamp, obj2.Timestamp);
            }
        }

    }

}