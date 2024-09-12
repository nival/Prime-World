using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Web.Routing;
using System.Web.Mvc;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Areas.MassOperations.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.MassOperations.Controllers
{
    [Authorize]
    public class MassOperationsController : Controller
    {
        //
        // GET: /MassOperations/MassOperations/
      public IAccountService AccountSvc { get; set; }

      protected override void Initialize( System.Web.Routing.RequestContext requestContext )
      {
        base.Initialize( requestContext );

        if ( AccountSvc == null )
          AccountSvc = new AccountService();
      }

      [AuthorizeWithPermission( Permission = "GM_MassOperations" )]
      public ActionResult Index()
      {
        var model = new MassOperationsModel();
        model.FillSelectLists(AccountSvc);
        return View(model);
      }

      [HttpPost]
      [AuthorizeWithPermission( Permission = "GM_MassOperations" )]
      public ActionResult Index( MassOperationsModel model )
      {
        List<long> auidsInt = null;
        var readFile = false;
        if ( Request.Files.Count > 0 )
        {
          var httpPostedFileBase = Request.Files[0];
          if ( httpPostedFileBase != null )
          {
            var fileName = Path.GetFileName( httpPostedFileBase.FileName );
            // store the file inside ~/App_Data folder
            if ( !String.IsNullOrEmpty( fileName ) )
            {
              readFile = true;
              var path = Path.Combine( Server.MapPath( "~/App_Data" ), fileName );
              httpPostedFileBase.SaveAs( path );
              var data = System.IO.File.ReadAllBytes( path );
              auidsInt = MassOperationsModel.GetAuids( Encoding.UTF8.GetString( data ) );
              System.IO.File.Delete( path );
            }
          }
        }
        if ( !readFile && model.Auids != null )
        {
          auidsInt = model.GetAuids();
        }

        if ( auidsInt == null )
        {
          ModelState.AddModelError( "Auids", "Error parsing auids data. Check for overflow and file content" );
          model.FillSelectLists( AccountSvc );
          return View( model );
        }

        var massOperationDetails = AccountSvc.ProcessMassOperation(model, auidsInt, User.Identity.Name);

        if (massOperationDetails.SuccessStatus)
            return RedirectToAction("Index");

        ModelState.AddModelError("Auids", "Error in processMassOperation: \n" + massOperationDetails.ErrorDetails);
        model.FillSelectLists(AccountSvc);
        return View(model);
      }

      [AuthorizeWithPermission( Permission = "GM_MassOperations" )]
      public ActionResult MassOperationsInfo()
      {
        var model = AccountSvc.GetMassOperationsInfo();
        return View( model );
      }

      [AuthorizeWithPermission( Permission = "GM_MassOperations" )]
      public ActionResult DeleteMassOperationInfo( int operationId )
      {
        var result = AccountSvc.DeleteMassOperationInfo(operationId);
        if (result != null)
        {
          return RedirectToAction( "ShowError", "Account", new { error = result } );
        }
        return RedirectToAction( "MassOperationsInfo" );
      }

      [AuthorizeWithPermission( Permission = "GM_MassOperations" )]
      public ActionResult GetFailedUsers(string auids, MassOperationType operationType, string date)
      {
        return File( Encoding.ASCII.GetBytes( auids ),
                 "text/plain", string.Format( "failed_{0}_{1}.txt", operationType.ToString(), date ) );
      }
    }
}
