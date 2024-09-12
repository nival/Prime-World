using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{

    public class ReRollShopTask : BaseMultipleTask<ReRollShopInfoBL>
    {
        private readonly IPlayerRepository playerRepository;
        private readonly IRepository<ReRollShopLog> reRollshopLogRepository;

        public ReRollShopTask(IEnumerable<ReRollShopInfoBL> infos)
            : this(infos, new PlayerRepository(), new Repository<ReRollShopLog>())
        {
        }

        public ReRollShopTask(IEnumerable<ReRollShopInfoBL> infos, IPlayerRepository prepo, IRepository<ReRollShopLog> lplrepo)
            : base(infos)
        {
            playerRepository = prepo;
            reRollshopLogRepository = lplrepo;
        }


        protected override void Execute(ReRollShopInfoBL info)
        {
            var p = playerRepository.CheckAndGetById(info.Auid);
            var obj = new ReRollShopLog
            {
                Player = p,
                Auid = info.Auid,
                ItemId = info.ItemId,
                ItemGroup = info.ItemGroup,
                ItemPrice = info.ItemPrice,
                ItemPriceType = info.ItemPriceType,
                RerollCount = info.RerollCount,
                SlotType = info.SlotType,
                Timestamp = info.Timestamp
            };
            reRollshopLogRepository.Add(obj);
            playerRepository.Update(p);
        }

    }

}