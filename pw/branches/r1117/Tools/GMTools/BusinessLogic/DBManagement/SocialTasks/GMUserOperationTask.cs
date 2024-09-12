using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{
  public class GMUserOperationTask : BaseMultipleTask<GMUserOperationInfoBL>
  {
    private readonly IGMUserOperationRepository gmuseropRepository;
    private readonly IPlayerRepository playerRepository;
    private readonly IRepository<Claim> claimRepository;

    public GMUserOperationTask(IEnumerable<GMUserOperationInfoBL> infos)
      : this( infos, new GMUserOperationRepository(), new PlayerRepository(), new ClaimRepository() )
    {
    }

    public GMUserOperationTask(IEnumerable<GMUserOperationInfoBL> infos, IGMUserOperationRepository guoRepo, IPlayerRepository pRepo, IRepository<Claim> cRepo)
      : base(infos)
    {
      this.gmuseropRepository = guoRepo;
      this.playerRepository = pRepo;
      this.claimRepository = cRepo;
      repos = new List<IDisposable> {guoRepo, pRepo, cRepo};
    }

    protected override void Execute(GMUserOperationInfoBL info)
    {
      Player p = playerRepository.GetById(info.UserId);
      if (p == null)
        throw new Exception(String.Format("Player(id={0}) was not found", info.UserId));

      var claims = new List<Claim>();
      if (info.ClaimIds != null && info.ClaimIds.Count > 0)
      {
        foreach (int claimId in info.ClaimIds)
        {
          var c = claimRepository.GetById(claimId);
          if (c == null)
            throw new Exception(String.Format("Claim(id={0}) was not found", claimId));
          claims.Add(c);
        }
      }
        
      // При модераторском мьюте у нас нет информации о пользовательских жалобах
      // Попытаемся вытащить их из репозитория
      if ( (GMUserOperationType) info.Type == GMUserOperationType.ModeratorMute )
      {
        var claimRepo = claimRepository as ClaimRepository;
        if (claimRepo != null)
        {
          claims.AddRange( claimRepo.GetActiveClaimsByPlayerId( info.UserId, String.Empty ) );
        }
      }

      var guo = new GMUserOperation
                  {
                    Player = p,
                    GMLogin = info.GMLogin,
                    Type = (GMUserOperationType) info.Type,
                    Minutes = info.Minutes,
                    Points = info.Points,
                    Reason = info.Reason,
                    Timestamp = info.Timestamp
                  };
      gmuseropRepository.Add(guo);

      foreach (var claim in claims)
      {
        claim.GMUserOperation = guo;
        claimRepository.Update(claim);
      }
    }
  }
}