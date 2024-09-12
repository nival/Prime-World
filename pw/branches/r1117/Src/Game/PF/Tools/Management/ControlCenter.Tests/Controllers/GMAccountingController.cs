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
  class GMAccountingControllerTests
  {
    Moq.Mock<IAccountService> gmAccServiceMock;
    AccountController controller;

    [TestFixtureSetUp]
    public void Init()
    {
      gmAccServiceMock = new Moq.Mock<IAccountService>();
      controller = new AccountController();
      controller.AccountSvc = gmAccServiceMock.Object;
    }

    [Test, Ignore("Устаревший тест, починить")]
    public void Test_DetailsAction_Parameters()
    {
      AccountInfoModel accInfo = new AccountInfoModel { Login = "fb#user345", Auid = 1, NickName = "nickOfUser345", SNid = null, SNUid = null };
      gmAccServiceMock.Setup( x => x.GetAccountByAuid( 1 ) ).Returns( accInfo );
      gmAccServiceMock.Setup( x => x.GetAccountBySNUid( "fb", "user345" ) ).Returns( accInfo );
      GetAccountsResp nickResponse = new GetAccountsResp{accountsList = new List<AccountInfoModel>() };
      nickResponse.accountsList.Add(accInfo);
      gmAccServiceMock.Setup( x => x.GetAccountsByNickName( "nickOfUser345" ) ).Returns( nickResponse );

      ActionResult result = controller.Details( null, null, null, null) as ActionResult;
      Assert.AreEqual( "ShowError",
        ((RedirectToRouteResult)result).RouteValues["action"]);

      result = controller.Details( null, null, null, 1) as ActionResult;
      Assert.AreEqual( 1, ( (AccountInfoModel)( (ViewResult)result ).ViewData.Model ).Auid );

      result = controller.Details( null, null, "fb#user345", null) as ActionResult;
      Assert.AreEqual( "fb#user345", ( (AccountInfoModel)( (ViewResult)result ).ViewData.Model ).Login );

      result = controller.Details( "fb", "user345", null, null) as ActionResult;
      Assert.AreEqual( "user345", ( (AccountInfoModel)( (ViewResult)result ).ViewData.Model ).SNUid );
    }
  }
}