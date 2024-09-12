using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Web.Script.Serialization;
using AccountLib;
using log4net;

namespace ControlCenter.Areas.GM.Models
{
    public interface IBruteForceDefenderService
    {
        BruteForceAccountModel GetBruteForceAccount(string email);
        BruteForceAccountModel UnBanBruteForceAccount(string email);
        BannedIpFullListModel GetBannedIp(int limit, int skip);
        BannedIpFullListModel UnBanIp(string ip);

    }

    public class BruteForceDefenderService : IBruteForceDefenderService
    {
        private static ILog _log = LogManager.GetLogger(typeof(AccountService));

        private IAccountManagementService accountManagementService;
        public static string GmAccountingAddress { get; set; }
        
        public BruteForceDefenderService()
        {
            Uri gmAccountingUrl;
            if (GmAccountingAddress != null && Uri.TryCreate(GmAccountingAddress, UriKind.Absolute, out gmAccountingUrl))
            {
                accountManagementService = new AccountManagementService(gmAccountingUrl);
            }
            else
            {
                _log.ErrorFormat("Invalid cluster address {0}", GmAccountingAddress ?? "(null)");
            }
        }

        public BruteForceDefenderService(IAccountManagementService service)
        {
            this.accountManagementService = service;
        }
        public static string GetVerboseErrorMessage(RequestResult result)
        {
            if (result == RequestResult.TransportException)
                return "Transport exception during server request";
            if (result == RequestResult.BadResult)
                return "Unknown server problem";
            if (result == RequestResult.EmailNotExist)
                return "Email doesn't exist in the collection of brutefoce ";
            return Enum.GetName(typeof(RequestResult), result);
        }
        public BruteForceAccountModel GetBruteForceAccount(string email)
        {
            BruteForceAccountShortInfo info = accountManagementService.GetBruteForceAccount(email);
            BruteForceAccountModel infoUi = new BruteForceAccountModel();
            if (info.Result != RequestResult.Success )
            {
                infoUi.ErrorIfExistToShow = GetVerboseErrorMessage(info.Result);
                _log.ErrorFormat("{0}, was in {1}", infoUi.ErrorIfExistToShow, "GetBruteForceAccount");
                return infoUi;
            }

            return new BruteForceAccountModel(info);
        }

        public BruteForceAccountModel UnBanBruteForceAccount(string email)
        {
            RequestResult result = accountManagementService.UnBanBruteForceAccount(email);
            BruteForceAccountModel infoUi = new BruteForceAccountModel();
            if (result != RequestResult.Success)
            {
                infoUi.ErrorIfExistToShow = GetVerboseErrorMessage(result);
                _log.ErrorFormat("{0}, was in {1}", infoUi.ErrorIfExistToShow, "GetBruteForceAccount");
                return infoUi;
            }
            infoUi.ErrorIfExistToShow = "UnBaning was done";
            return infoUi;
        }

        public BannedIpFullListModel GetBannedIp(int limit, int skip)
        {
            BannedIpFullListInfo info = accountManagementService.GetBannedIp(limit, skip);
            BannedIpFullListModel infoUi = new BannedIpFullListModel();
            if (info.Result != RequestResult.Success)
            {
                infoUi.ErrorIfExistToShow = GetVerboseErrorMessage(info.Result);
                _log.ErrorFormat("{0}, was in {1}", infoUi.ErrorIfExistToShow, "GetBannedIp");
                return infoUi;
            }
            return new BannedIpFullListModel(info);            
        }

        public BannedIpFullListModel UnBanIp(string ip)
        {
            RequestResult result = accountManagementService.UnBanIp(ip);
            BannedIpFullListModel infoUi = new BannedIpFullListModel();
            if (result != RequestResult.Success)
            {
                infoUi.ErrorIfExistToShow = GetVerboseErrorMessage(result);
                _log.ErrorFormat("{0}, was in {1}", infoUi.ErrorIfExistToShow, "UnBanIp");
                return infoUi;
            }
            infoUi.ErrorIfExistToShow = "UnBaning was done";
            return infoUi;            
        }


    }
}