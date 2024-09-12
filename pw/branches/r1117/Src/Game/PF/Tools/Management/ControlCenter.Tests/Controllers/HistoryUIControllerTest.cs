using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NUnit.Framework;
using ControlCenter;
using ControlCenter.Controllers;
using System.Web.Mvc;
using ControlCenter.Areas.GM.Controllers;
using DAL.Repositories;
using DAL.Entities;
using ControlCenter.Areas.GM.Models;

namespace ControlCenter.Tests.Controllers
{
  [TestFixture]
  class HistoryUIControllerTests
  {
    Moq.Mock<IHistoryRecordsRepository> mockHistoryRepo;
    HistoryUIController controller;

    [TestFixtureSetUp]
    public void Init()
    {
      mockHistoryRepo = new Moq.Mock<IHistoryRecordsRepository>();
      IHistoryUIService histService = new HistoryUIService( mockHistoryRepo.Object, null, null, null, null, null, null, null);
      controller = new HistoryUIController();
      controller.HistorySvc = histService;
    }

/*
    [Test]
    public void Test_HeroesOpsHistory()
    {
      List<GmLockCharacter> lockHeroes = new List<GmLockCharacter>();
      lockHeroes.Add( new GmLockCharacter { operationdate = new DateTime( 2010, 11, 11 ) } );
      lockHeroes.Add( new GmLockCharacter { operationdate = new DateTime( 2012, 11, 11 ) } );
      List<GmUnlockCharacter> unlockHeroes = new List<GmUnlockCharacter>();
      unlockHeroes.Add( new GmUnlockCharacter { operationdate = new DateTime( 2011, 11, 11 ) } );

      mockHistoryRepo.Setup( x => x.GetGmLockCharactersByPlayerId( 1 ) ).Returns( lockHeroes.AsEnumerable() );
      mockHistoryRepo.Setup( x => x.GetGmUnlockCharactersByPlayerId( 1 ) ).Returns( unlockHeroes.AsEnumerable() );

      ViewResult result = controller.LockOpsHistory(1, "1", null) as ViewResult;
      ViewDataDictionary viewData = result.ViewData;
      List<GmLockOperationHistoryModel> modelList = (List<GmLockOperationHistoryModel>)viewData.Model;

      Assert.AreEqual( 3, modelList.Count );
      Assert.AreEqual( "unlock", modelList[1].operationType );
    }
    
    [Test]
    public void Test_TalentOpsHistory()
    {
      List<GmAddTalent> addTalents = new List<GmAddTalent>();
      addTalents.Add( new GmAddTalent { player = 10, talent = 10, operationdate = new DateTime( 2010, 11, 11 ) } );
      addTalents.Add( new GmAddTalent { player = 10, talent = 10, operationdate = new DateTime( 2012, 11, 11 ) } );
      List<GmDeleteTalent> deleteTalents = new List<GmDeleteTalent>();
      deleteTalents.Add( new GmDeleteTalent { player = 10, talent = 10, operationdate = new DateTime( 2011, 11, 11 ) } );
      
      mockHistoryRepo.Setup( x => x.GetGmAddTalentsByPlayerId( 1 ) ).Returns( addTalents.AsEnumerable() );
      mockHistoryRepo.Setup( x => x.GetGmDeleteTalentsByPlayerId( 1 ) ).Returns( deleteTalents.AsEnumerable() );

      ViewResult result = controller.TalentOpsHistory(1, "1", null) as ViewResult;
      ViewDataDictionary viewData = result.ViewData;
      List<GmTalentOperationHistoryModel> modelList = (List<GmTalentOperationHistoryModel>)viewData.Model;

      Assert.AreEqual( 3, modelList.Count );
      Assert.AreEqual( "delete talent", modelList[1].operationType );
    }*/
  }
}
