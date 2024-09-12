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
    public interface IGameSessionService
    {
        GameSessionShortInfoModel GetSessionShortInfoById(int gsid);
        List<GameReplayInfoModel> GetReplays(string host, string date, string sessionId, out string searchDirectory);
    }

    public class GameSessionService : IGameSessionService
    {
        private static ILog _log = LogManager.GetLogger(typeof(AccountService));

        private IAccountManagementService accountManagementService;

        public static string GmSessionService { get; set; }
        public static string GmReplaysService { get; set; }
        public static string GmReplaysUrlService { get; set; }

        public GameSessionService()
        {
            Uri gmAccounting_url;
            if (GmSessionService != null && Uri.TryCreate(GmSessionService, UriKind.Absolute, out gmAccounting_url))
            {
                accountManagementService = new AccountManagementService(gmAccounting_url);
            }
            else
            {
                _log.ErrorFormat("Invalid cluster address {0}", GmSessionService ?? "(null)");
                return;
            }
        }

        public GameSessionService(IAccountManagementService service)
        {
            this.accountManagementService = service;
        }

        public GameSessionShortInfoModel GetSessionShortInfoById(int gsid)
        {
            GameSessionShortInfoModel infoUi = new GameSessionShortInfoModel();
            GameSessionShortInfo info = accountManagementService.GetGameSession(gsid);
            if (info.Result != RequestResult.Success)
            {
                infoUi.ErrorIfExistToShow = Enum.GetName(typeof(RequestResult), info.Result);
                _log.ErrorFormat("{0}, was in {1}", infoUi.ErrorIfExistToShow, "GetSessionShortInfoById");
                return infoUi;
            }
            if (info.Teamadorni == null || info.Teamdocts == null)
            {
                infoUi.ErrorIfExistToShow = Enum.GetName(typeof(RequestResult), RequestResult.ServerReturnedNull);
                _log.ErrorFormat("{0}, was in {1}", infoUi.ErrorIfExistToShow, "GetSessionShortInfoById");
                return infoUi;
            }
            return new GameSessionShortInfoModel(info);
        }

        public List<GameReplayInfoModel> GetReplays(string host, string date, string sessionId, out string searchdirectory)
        {


            var replays = new List<GameReplayInfoModel>();
            searchdirectory = GmReplaysService;
            if (sessionId == "")
                return replays;

            List<String> files = new List<string>();

            try
            {
                HttpWebRequest req = (HttpWebRequest)HttpWebRequest.Create(GmReplaysUrlService + "/get_replays");
                req.Method = "POST";

                String body = String.Format("SessionId={0}&hostname={1}&date={2}", sessionId, host, date);
                UTF8Encoding encoding = new UTF8Encoding();
                req.ContentLength = encoding.GetByteCount(body);
                req.Credentials = CredentialCache.DefaultCredentials;
                req.Accept = "application/x-www-form-urlencoded";
                req.ContentType = "application/x-www-form-urlencoded";
                using (Stream requestStream = req.GetRequestStream())
                {
                    requestStream.Write(encoding.GetBytes(body), 0, encoding.GetByteCount(body));
                }
                HttpWebResponse response = req.GetResponse() as HttpWebResponse;
                string responseBody = "";
                using (Stream rspStm = response.GetResponseStream())
                {
                    using (StreamReader reader = new StreamReader(rspStm))
                    {
                        responseBody = reader.ReadToEnd();
                    }
                }
                //"Success: " + response.StatusCode.ToString();

                files = ParseJson(responseBody);
            }

            catch (System.Net.WebException ex)
            {
                StreamReader reader = new StreamReader(ex.Response.GetResponseStream());
                _log.ErrorFormat("Exception message: {0}\r\n; Status: {1};\r\n in {2}", ex.Message, ex.Status, "GetReplays");
            }

            foreach (var fileInfo in files)
            {
                var sfile = fileInfo.Replace("\\", "/");
                replays.Add(new GameReplayInfoModel() { Link = GmReplaysService + "/" + sfile, Name = GmReplaysService + "/" + sfile });
            }

            return replays;

        }

        public List<string> ParseJson(string str)
        {
            JavaScriptSerializer _jss = new JavaScriptSerializer();

            try
            {
                List<String> replays = new List<string>();
                var dict = _jss.Deserialize<Dictionary<string, List<string>>>(str);

                foreach (var pair in dict)
                    foreach (var url in pair.Value)
                        replays.Add(url);
                return replays;
            }
            catch (Exception ex)
            {
                _log.ErrorFormat("Invalid JSON '{0}'\nParsing error = {1}", str, ex);
                return null;
            }
        }

    }
}