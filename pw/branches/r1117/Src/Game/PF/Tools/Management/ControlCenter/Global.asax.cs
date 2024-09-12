using System;
using System.Collections.Specialized;
using System.Configuration;
using System.Linq;
using System.Threading;
using System.Web;
using System.Web.Configuration;
using System.Web.Mvc;
using System.Web.Routing;
using System.Web.Security;
using AdminLib;
using AdminLib.Entities;
using AdminLib.Repositories;
using ControlCenter.Areas.Admin.Models;
using ControlCenter.Areas.Cluster.Models;
using ControlCenter.Areas.EventTool;
using ControlCenter.Areas.EventTool.Models;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;
using ControlCenter.Properties;
using DAL;
using log4net;
using log4net.Config;

namespace ControlCenter
{
  // Note: For instructions on enabling IIS6 or IIS7 classic mode, 
  // visit http://go.microsoft.com/?LinkId=9394801

  public class MvcApplication : HttpApplication
  {
    private static ILog _log = LogManager.GetLogger(typeof(MvcApplication));

    public static void RegisterRoutes(RouteCollection routes)
    {
      routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

      routes.MapRoute(
        "Default", // Route name
        "{controller}/{action}/{id}", // URL with parameters
        new { controller = "Home", action = "Index", id = UrlParameter.Optional } // Parameter defaults
        );
    }

    protected void Application_Start()
    {
      XmlConfigurator.Configure();
      _log.Info("Starting web application");
      AreaRegistration.RegisterAllAreas();

      RegisterRoutes(RouteTable.Routes);

      ModelBinders.Binders.Add(typeof(DateTime), new CustomDateTimeBinder());
      ModelBinders.Binders.Add(typeof(SkinPriceModel), new NewPricesModelBinder<SkinPriceModel, SkinPriceInfoModel>());
      ModelBinders.Binders.Add( typeof( HeroPriceModel ), new NewPricesModelBinder<HeroPriceModel, HeroPriceInfoModel>() );
      ModelBinders.Binders.Add( typeof( RerollShopSlotPriceModel ), new NewPricesModelBinder<RerollShopSlotPriceModel, RerollSlotPriceInfoModel>() );
      ModelBinders.Binders.Add( typeof( RerollShopSlotAmountModel ), new NewPricesModelBinder<RerollShopSlotAmountModel, RerollSlotAmountInfoModel>() );
      ModelBinders.Binders.Add( typeof( RerollShopGroupPriceModel ), new NewPricesModelBinder<RerollShopGroupPriceModel, RerollShopGroupPriceInfoModel>() );
      ModelBinders.Binders.Add( typeof( RerollShopGroupSlotsModel ), new NewPricesModelBinder<RerollShopGroupSlotsModel, RerollShopGroupSlotsInfoModel>() );
      ModelBinders.Binders.Add( typeof( RerollShopGroupCurrenciesModel ), new NewPricesModelBinder<RerollShopGroupCurrenciesModel, RerollShopGroupCurrenciesInfoModel>() );
      ModelBinders.Binders.Add( typeof( RerollShopGroupProbabilityModel ), new NewPricesModelBinder<RerollShopGroupProbabilityModel, RerollShopGroupProbabilityInfoModel>() );
      ModelBinders.Binders.Add( typeof( FirstBuyPriceModel ), new NewPricesModelBinder<FirstBuyPriceModel, FirstBuyPriceInfoModel>() );

      // AdminLib initialization
      string connectionString = WebConfigurationManager.ConnectionStrings["AdminDatabase"].ConnectionString;
      AdminLib.NHibernateHelper.Init(new DBContext(connectionString));

      // DAL initialization
      string managementString = WebConfigurationManager.ConnectionStrings["ManagementDatabase"].ConnectionString;
      DAL.NHibernateHelper.Init(new DALContext(managementString));

      // Ensure that Administrator account exists
      CheckAdministratorAccount();
      
      // Fill actual permissions values in database
      FillActualPermissions();

      // Set up the address of managed cluster
      var cluster = WebConfigurationManager.GetSection("cluster") as NameValueCollection;
      if (cluster == null)
        throw new ConfigurationErrorsException("Configuration block <cluster> was not found.");
      ClusterService.ClusterAddress = cluster["ClusterAddress"];
      ClusterService.MonitoringSummaryAddress = cluster["MonitoringSummaryAddress"];

      var gmAccounting = WebConfigurationManager.GetSection("gmAccounting") as NameValueCollection;
      if (gmAccounting == null)
        throw new ConfigurationErrorsException("Configuration block <gmAccounting> was not found.");
      AccountService.GmAccountingAddress = gmAccounting["gmAccountingAddress"];
      GuildService.GmAccountingAddress = gmAccounting["gmAccountingAddress"];
      DynamicQuestService.GmAccountingAddress = gmAccounting["gmAccountingAddress"];
      EventsService.GmAccountingAddress = gmAccounting["gmAccountingAddress"];
      //TODO нужен отдельный адрес?
      GameSessionService.GmSessionService = gmAccounting["gmAccountingAddress"];
      GameSessionService.GmReplaysService = gmAccounting["replaysServerAddress"];
      GameSessionService.GmReplaysUrlService = gmAccounting["replaysURLServerAddress"];

      GeolocationCache.Init(gmAccounting["geolocationDictionaryAddress"]);
      BruteForceDefenderService.GmAccountingAddress = gmAccounting["gmAccountingAddress"];
    }

    protected void Application_PostAuthenticateRequest(Object sender, EventArgs e)
    {
      // Get the authentication cookie
      string cookieName = FormsAuthentication.FormsCookieName;
      HttpCookie authCookie = Context.Request.Cookies[cookieName];

      if (authCookie == null) return;

      // Get the authentication ticket and rebuild the principal & identity
      FormsAuthenticationTicket authTicket = FormsAuthentication.Decrypt(authCookie.Value);
      var userdata = CustomUserData.Deserialize(authTicket.UserData);

      var userIdentity = new FormsIdentity(authTicket);
      var userPrincipal = new GMToolsPrincipal(userIdentity, userdata.superuser, userdata.roles, userdata.permissions, userdata.locales, userdata.muids);

      Context.User = userPrincipal;
      Thread.CurrentPrincipal = userPrincipal;
    }

    private const string SUPERUSER = "Administrator";
    private const string SUPERUSER_PASSWORD = "password";

    private void CheckAdministratorAccount()
    {
      using (var urepo = new GMUserRepository())
      {
        if (urepo.GetByUserName(SUPERUSER) == null)
        {
          _log.InfoFormat("Superuser {0} is not exists in database. Creating this one", SUPERUSER);
          using (var mrepo = new GMUserMembershipRepository())
          {
            mrepo.CreateUser(new GMUser { UserName = SUPERUSER, Superuser = true }, SUPERUSER_PASSWORD);
          }
        }
      }
    }

    private void FillActualPermissions()
    {
      var permissions = Settings.Default.Permissions.Cast<string>();

      using (var prepo = new GMPermissionRepository())
      {
        prepo.FillPermissions(permissions);
      }
    }
  }
}