using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml;
using System.IO;
using System.Xml.Linq;
using System.Text;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.API.Common;
using ZzimaBilling.API.DL;
using ZzimaBilling.API.DL.apidsTableAdapters;
using ZzimaBilling.API.PL;
using System.Security.Cryptography;
namespace ZzimaBilling.API.BL
{
    public class Service
    {
        private int _id = -1;
        private string _name = null;
        private bool _cbtMode = false;

        public int id {get { return _id; }}
        public string name { get { return _name; } }
        public bool cbtMode { get { return _cbtMode; } }

        /**
         * Private constructor
         */
        private Service()
        {
        }
        private void recordWrongCrc(System.Web.HttpContext ctx, string svcname)
        {
            APIQueriesAdapter adp = new APIQueriesAdapter();
            ctx.Request.InputStream.Position = 0;
            byte[] bin = ctx.Request.BinaryRead(ctx.Request.TotalBytes);
            string content = Encoding.ASCII.GetString(bin, 0, bin.Length);

            Nullable<int> errorCode = 0;
            adp.sp_api_recordWrongCrc(null, svcname, content, ref errorCode);
        }

        private void logRequest(System.Web.HttpContext ctx, string svcname)
        {
            // log content of request =========================================
            APIQueriesAdapter adp = new APIQueriesAdapter();
            ctx.Request.InputStream.Position = 0;
            byte[] bin = ctx.Request.BinaryRead(ctx.Request.TotalBytes);
            string content = Encoding.ASCII.GetString(bin, 0, bin.Length);
            
            Nullable<int> errorCode = 0;
            adp.sp_api_protocolRequest(null, svcname, content, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        private void logLegacyRequest(System.Web.HttpContext ctx, int serviceId)
        {
            // log content of request =========================================
            APIQueriesAdapter adp = new APIQueriesAdapter();
            ctx.Request.InputStream.Position = 0;
            byte[] bin = ctx.Request.BinaryRead(ctx.Request.TotalBytes);
            string content = Encoding.ASCII.GetString(bin, 0, bin.Length);

            Nullable<int> errorCode = 0;
            adp.sp_legacy_protocolRequest(serviceId, null, content, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        /**
         * Implements check-CRC functionality
         */
        public static Service checkCRC(System.Web.HttpContext ctx, ServiceRequest req)
        {
            Service svc = new Service();
            // validate request
            req.validate();
            
            // try to find service
            sp_api_getServicePasswordTableAdapter ad = new sp_api_getServicePasswordTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_getServicePasswordDataTable table = ad.GetData(req.fromServiceName, ref errorCode);
            if (errorCode!=0)
                throw new ApiException((int)errorCode, "");
            
            // try to authorize and check CRC
            byte[] crc2 = req.getCrc(ctx, table[0].PASSWORD);
            StringBuilder sBuilderMD5 = new StringBuilder();
            for (int i = 0; i < crc2.Length; i++)
            {
                sBuilderMD5.Append(crc2[i].ToString("x2"));
            }
            string str = sBuilderMD5.ToString();
            
            //=============================================================
            //@todo - uncomment !!!!!
            bool checkCRC = Convert.ToBoolean(System.Configuration.ConfigurationSettings.AppSettings.Get("checkCRC"));
            string privet = str;
            if (checkCRC)
            {
                if (req.crc != null)
                {
                    if (!req.crc.SequenceEqual(crc2))
                        //throw new ApiException(ApiException.ErrorCode.E_CRC, "");
                        //temporarily only log wrongCrc cases instead error throwing
                        svc.recordWrongCrc(ctx, req.fromServiceName);
                }
                else
                    svc.recordWrongCrc(ctx, req.fromServiceName);
            }

            //=============================================================

            // creates new instance of object
            svc._id = table[0].ID;
            svc._name = req.fromServiceName;
            svc.logRequest(ctx, req.fromServiceName);
            return svc;
        }

        /**
         * Implements legacy check-CRC functionality
         */
        public static Service legacyCheckCRC(System.Web.HttpContext ctx, String legacyId, String crc, String request)
        {

            // try to find service
            sp_legacy_getServicePasswordTableAdapter ad = new sp_legacy_getServicePasswordTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_legacy_getServicePasswordDataTable table = ad.GetData(legacyId, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            request += table[0].PASSWORD;

            MD5 md5Hasher = MD5.Create();

            byte[] content = System.Text.Encoding.UTF8.GetBytes(request);
            byte[] hash = md5Hasher.ComputeHash(content, 0, content.Length);

            string crcCalc = "";
            foreach (byte b in hash)
                crcCalc +=  String.Format("{0:x2}", b);
            
            //=============================================================
            //@todo - uncomment !!!!!
            bool checkLegacyCRC = Convert.ToBoolean(System.Configuration.ConfigurationSettings.AppSettings.Get("checkLegacyCRC"));
            if (checkLegacyCRC)
                if (crc.ToLower() != crcCalc)
                    throw new ApiException(ApiException.ErrorCode.E_CRC, "Invalid CRC");
            //=============================================================

            Service svc = new Service();
            svc._id = table[0].ID;
            svc._name = table[0].NAME;
            svc.logLegacyRequest(ctx, svc._id);

            return svc;
        }

        
        public static Service getService(string name)
        {
            Service res = new Service();
            return res;
        }

        public string subscribe(SubscribeServiceReq req)
        {
            // try to find service
            sp_api_subscribeUserTableAdapter ad = new sp_api_subscribeUserTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_subscribeUserDataTable table = ad.GetData(req.userName, req.serviceName, Employer.getMd5HashPassword(req.userName, req.servicePassword), ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            return table[0].ACCOUNT;
        }

        public string getServiceGuidName(GetServiceGuidNameReq req)
        {
            sp_api_getServiceGuidNameTableAdapter ad = new sp_api_getServiceGuidNameTableAdapter();
            int? errorCode = 0;
            apids.sp_api_getServiceGuidNameDataTable table = ad.GetData(req.userid, req.serviceName, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
            return table[0].SERVICENAME;
        }
        
        public void unsubscribe(UnsubscribeServiceReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_unsubscribeUser(req.userName, req.serviceName, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public void ban(BanUserReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_banUser(req.userName, req.fromServiceName, req.reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

        }

        public void unban(UnbanUserReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_unbanUser(req.userName, req.fromServiceName, req.reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public ServiceShortInfo[] getServicesList(GetServicesListReq req)
        {
            // try to find service
            sp_api_getServicesListTableAdapter ad = new sp_api_getServicesListTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_getServicesListDataTable table = ad.GetData(req.userName, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");


            ServiceShortInfo[] res = new ServiceShortInfo[table.Rows.Count];
            
            for(int i=0;i<res.Length;i++)
            {
                res[i] = new ServiceShortInfo(); 
                res[i].serviceName = table[i].SERVICENAME;
                res[i].subscribed = table[i].SUBSCR!=0;
            }
            return res;
        }
        
        public string getServiceSettings(GetServiceSettingsReq req)
        {
            // try to find service
            sp_api_getServiceSettingsTableAdapter ad = new sp_api_getServiceSettingsTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_getServiceSettingsDataTable table = ad.GetData(req.userName, req.serviceName, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");


            ServiceShortInfo[] res = new ServiceShortInfo[table.Rows.Count];
            return table[0].PROPERTIES;
        }
    

        public void setServiceSettings(SetServiceSettingsReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_setServiceSettings(req.userName, req.serviceName, Employer.getMd5HashPassword(req.userName, req.servicePassword), req.serviceSettings, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

        }


    }
}
