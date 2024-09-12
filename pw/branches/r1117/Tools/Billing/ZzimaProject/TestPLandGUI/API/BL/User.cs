using System;
using System.Data;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using System.Text;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.API.Common;
using ZzimaBilling.API.PL;
using ZzimaBilling.API.DL;
using ZzimaBilling.API.DL.apidsTableAdapters;
using System.Data.SqlClient;
using System.Collections.Generic;

namespace ZzimaBilling.API.BL
{
    public class User
    {
        private string _account;
        private int _id;
        public int id { get { return _id; } }
        public string account { get { return _account; } }

        private static void logLegacyRequest(System.Web.HttpContext ctx, string name)
        {
            // log content of request =========================================
            APIQueriesAdapter adp = new APIQueriesAdapter();
            ctx.Request.InputStream.Position = 0;
            byte[] bin = ctx.Request.BinaryRead(ctx.Request.TotalBytes);
            string content = Encoding.ASCII.GetString(bin, 0, bin.Length);

            Nullable<int> errorCode = 0;
            adp.sp_legacy_protocolRequest(null, name, content, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static User create(RegisterUserReq req)
        {
            // try to find service
            sp_api_createUserTableAdapter ad = new sp_api_createUserTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_createUserDataTable table =
                    ad.GetData(req.userName, req.userEmail.ToLower(), Employer.getMd5HashPassword(req.userName, req.userPassword), req.userReferal, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            User usr = new User();
            usr._id = table[0].ID;
            usr._account = table[0].ACCOUNT;
            return usr;
        }

        public static User authorize(Service svc, AuthorizeUserReq req)
        {

            // try to find service
            sp_api_authorizeUserTableAdapter ad = new sp_api_authorizeUserTableAdapter();
            Nullable<int> errorCode = 0;
            ad.Connection.FireInfoMessageEventOnUserErrors = true;

            SqlMsgHandler hdl = new SqlMsgHandler();
            SqlInfoMessageEventHandler hd = new SqlInfoMessageEventHandler(hdl.conn_InfoMessage);
            ad.Connection.InfoMessage += hd;

            try
            {
                apids.sp_api_authorizeUserDataTable table = ad.GetData(svc.id, req.userName, Employer.getMd5HashPassword(req.userName, req.userPassword), ref errorCode);

                if (errorCode != 0)
                {
                    throw new ApiException((int)errorCode, hdl.msg);
                }

                User usr = new User();
                usr._id = table[0].id;

                if (table[0].authorized == 0)
                {
                    if (! ExtAuthHelper.authorize(table[0].authorizationclass, req.userName, Convert.ToBase64String(req.userPassword),table[0].email))
                        throw new ApiException(ApiException.ErrorCode.E_INVALID_PASSWORD, "");
                }
                return usr;

            }
            finally
            {
                ad.Connection.FireInfoMessageEventOnUserErrors = false;
                ad.Connection.InfoMessage -= hd;
            }
        }

        public static decimal getBalance(Service svc, GetUserBalanceReq req)
        {
            // try to find service
            sp_api_getBalanceTableAdapter ad = new sp_api_getBalanceTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_getBalanceDataTable table =
                    ad.GetData(req.userName, svc.id, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
            return table[0].IsAMOUNTNull() ? 0 : table[0].AMOUNT;
        }

        public static decimal getBalanceExceptSys(Service svc, GetUserBalanceExceptSysReq req)
        {
            var ad = new sp_api_getBalanceExceptSysTableAdapter();
            int? errorCode = 0;
            apids.sp_api_getBalanceExceptSysDataTable table = ad.GetData(req.userName, svc.id,
                                                                         string.Join(";", req.Systems.ToArray()),
                                                                         ref errorCode);
            if(errorCode != 0)
                throw  new ApiException((int)errorCode, "");
            return table[0].IsAMOUNTNull() ? 0 : table[0].AMOUNT;
        }

        public static List<OperationWriteOff> getBalanceEx(Service svc, GetUserBalanceExReq req)
        {
            sp_api_getBalanceExTableAdapter ad = new sp_api_getBalanceExTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_getBalanceExDataTable table = ad.GetData(req.userName, svc.id, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int) errorCode, "");

            var res = new List<OperationWriteOff>();

            for (int i = 0; i < table.Rows.Count; i++)
            {
                res.Add(new OperationWriteOff()
                            {
                                amount=table[i].amount,
                                paymentSystemId = table[i].psid
                            });
            }
            return res;
        }

        public static decimal legacyGetBalance(System.Web.HttpContext ctx, string userName)
        {
            logLegacyRequest(ctx, userName);
            // try to find service
            sp_legacy_getBalanceTableAdapter ad = new sp_legacy_getBalanceTableAdapter();
            Nullable<int> errorCode = 0;

            apids.sp_legacy_getBalanceDataTable table =
                    ad.GetData(userName, ctx.Request.UserHostAddress, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            return table[0].IsAMOUNTNull() ? 0 : table[0].AMOUNT;
        }

        public static User legacyAuthorize(System.Web.HttpContext ctx, string user, byte[] password, string serviceIp)
        {
            logLegacyRequest(ctx, user);
            // try to find service
            sp_legacy_accountLoginTableAdapter ad = new sp_legacy_accountLoginTableAdapter();
            Nullable<int> errorCode = 0;

            apids.sp_legacy_accountLoginDataTable table = ad.GetData(user, Employer.getMd5HashPassword(user, password), serviceIp, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            User usr = new User();
            usr._id = table[0].id;

            if (table[0].authorized == 0)
            {
                if (!ExtAuthHelper.authorize(table[0].authorizationclass, user, Convert.ToBase64String(password), table[0].email))
                    throw new ApiException(ApiException.ErrorCode.E_INVALID_PASSWORD, "");
            }
            return usr;

        }

        public static void replenish(Service svc, AccountReplenishmentReq req)
        {

            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_replenish(svc.id, req.userName, req.account, req.paymentSystem, req.amount, null, req.reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }
        public static void replenishWithAward(Service svc, EnrollAccWithAwardReq req)
        {

            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_replenish(svc.id, req.userName, req.account, req.paymentSystem, req.amount, req.award, req.reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static void legacyReplenish(Service svc, string userName, decimal amount, string reason)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_legacy_replenish(svc.id, userName, amount, reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static void transfer(Service svc, MoneyTranseferReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_transfer(svc.id, req.srcUserName, req.srcAccount, req.dstUserName, req.dstAccount, req.amount, req.reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static void legacyTransfer(Service svc, string fromName, string toName, decimal amount, string reason)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_legacy_transfer(svc.id, fromName, toName, amount, reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static void writeOff(Service svc, AccountWriteOffReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_writeOff(svc.id, req.userName, req.account, req.amount, req.reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static void WriteOffExceptSys(Service svc, WriteOffExceptSysReq req)
        {
            var ad = new APIQueriesAdapter();
            int? errorCode = 0;
            ad.sp_api_writeOffExceptSys(svc.id, req.userName, req.accountName, req.amount, req.reason,
                                        string.Join(";", req.Systems.ToArray()), ref errorCode);
            if(errorCode !=0)
            {
                throw new ApiException((int)errorCode, "");
            }
        }

        public static int writeOffEx(Service svc, WriteOffExReq req, ref decimal? remainAmount)
        {
            sp_api_writeOffWithBalanceExTableAdapter ad = new sp_api_writeOffWithBalanceExTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_writeOffWithBalanceExDataTable table = ad.GetData(svc.id, req.userName, req.accountName,
                                                                           req.amount, req.reason, ref remainAmount,
                                                                           ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int) errorCode, "");

            return table[0].IsOperationIdNull() ? 0 : table[0].OperationId;
        }

        public static List<OperationWriteOff> GetOperationDetails(Service svc, GetOperationDetailsReq req)
        {
            sp_api_getOperationDetailsTableAdapter ad = new sp_api_getOperationDetailsTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_getOperationDetailsDataTable table = ad.GetData(req.userName, req.operationId, ref errorCode);
            if (errorCode != 0)
            {
                throw new ApiException((int) errorCode, "");
            }
            var res = new List<OperationWriteOff>();
            for (int i = 0; i < table.Rows.Count; i++)
            {
                res.Add(new OperationWriteOff()
                            {
                                amount = table[i].amount,
                                paymentSystemId = table[i].paymentSystemId
                            });
            }

            return res;
        }

        public static decimal removeAmountWithReal(Service svc, AccountWriteOffReq req)
        {
            sp_api_removeAmountWithRealTableAdapter ad = new sp_api_removeAmountWithRealTableAdapter();
            int? errorCode = 0;
            decimal? realAmount = 0;
            apids.sp_api_removeAmountWithRealDataTable table =
                ad.GetData(svc.id, req.userName, req.account, req.amount, req.reason, ref realAmount, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
            return realAmount.HasValue ? realAmount.Value : 0;
        }

        public static decimal reserveAmount(Service svc, ReserveAmountReq req)
        {
            sp_api_reserveAmountTableAdapter ad = new sp_api_reserveAmountTableAdapter();
            int? errorCode = 0;
            apids.sp_api_reserveAmountDataTable table =
                ad.GetData(req.userName, svc.id, req.amount, req.reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
            return table[0].reserveId;
        }

        public static void confirmWriteOff(Service svc, ConfirmWriteOffReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            int? errorCode = 0;
            ad.sp_api_confirmWriteOff(req.reserveId, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static void legacyWriteOff(Service svc, string userName, decimal amount, string reason)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_writeOff(svc.id, userName, null, amount, reason, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static ProfileInfo getProfile(GetUserProfileReq req)
        {
            return getProfile(req.userName);
        }
        public static ByIdProfileInfo byIdGetUserProfile(ByIdGetUserProfileReq req)
        {
            sp_api_byIdGetUserProfileTableAdapter ad = new sp_api_byIdGetUserProfileTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_byIdGetUserProfileDataTable table =
                    ad.GetData(req.userid, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            ByIdProfileInfo pi = new ByIdProfileInfo();
            pi.creationDate = table[0].CREATEDAT;
            pi.userName = table[0].name;
            if (!table[0].IsEMAILNull())
                pi.email = table[0].EMAIL;
            if (!table[0].IsREFERALCODENull())
                pi.referalCode = table[0].REFERALCODE;
            if (!table[0].IsDISPLAYNAMENull())
                pi.displayName = table[0].DISPLAYNAME;
            if (!table[0].IsPARTNERNull())
                pi.partner = table[0].PARTNER;
            if (!table[0].IsBANNull())
                pi.banSn = table[0].BAN;
            pi.agreementAccepted = table[0].AGREEMENT;

            return pi;
        }

        public static ProfileInfo getProfile(string userName)
        {
            // try to find service
            sp_api_getUserProfileTableAdapter ad = new sp_api_getUserProfileTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_getUserProfileDataTable table =
                    ad.GetData(userName, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            ProfileInfo pi = new ProfileInfo();
            pi.userid = table[0].USERID;
            pi.creationDate = table[0].CREATEDAT;
            if (!table[0].IsEMAILNull())
                pi.email = table[0].EMAIL;
            if (!table[0].IsREFERALCODENull())
                pi.referalCode = table[0].REFERALCODE;
            if (!table[0].IsDISPLAYNAMENull())
                pi.displayName = table[0].DISPLAYNAME;
            if (!table[0].IsPARTNERNull())
                pi.partner = table[0].PARTNER;
            if (!table[0].IsBANNull())
                pi.banSn = table[0].BAN;
            pi.agreementAccepted = table[0].AGREEMENT;

            return pi;
        }

        public static void setProfile(Service svc, SetUserProfileReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_setUserProfile(svc.id, req.userName, req.displayName, req.email, req.agreementAccepted, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static void setPassword(SetUserPasswordReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_setUserPassword(req.userName, Employer.getMd5HashPassword(req.userName, req.userPassword), ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static void promoActivate(Service svc, PromoActivateReq req)
        {
            APIQueriesAdapter ad = new APIQueriesAdapter();
            Nullable<int> errorCode = 0;
            ad.sp_api_promoActivate(svc.id, req.userName, req.account, req.promoCode, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
        }

        public static decimal zeroAwardMoney(Service svc, ZeroAwardMoneyReq req)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(@"<?xml version = ""1.0""?>");
            foreach (string s in req.users)
            {
                sb.Append("<user>" + s + "</user>");
            }
            sp_api_zeroAwardMoneyTableAdapter ad = new sp_api_zeroAwardMoneyTableAdapter();
            Nullable<int> errorCode = 0;
            apids.sp_api_zeroAwardMoneyDataTable table =
                    ad.GetData(svc.id, sb.ToString(), req.zeroAll, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
            return table[0].IszeroedAmountNull() ? 0 : table[0].zeroedAmount;
            
            //user[] users = new user[2];
            //user u = new user();
            //u.name = "fedor";
            //u.errorCode = 1001;
            //users[0] = u;
            //u.name = "petya";
            //u.errorCode = 1002;
            //users[1] = u;
            //return users;
        }

        public static UserPaymentsHistoryRecord[] getPaymentsHistory(Service svc, GetUserPaymentsHistoryReq req)
        {
            // try to find service
            sp_api_getPaymentsHistoryTableAdapter ad = new sp_api_getPaymentsHistoryTableAdapter();
            Nullable<int> errorCode = 0;

            Nullable<DateTime> nFrom = null;
            if (req.from.ToOADate() != 0)
                nFrom = req.from;
            Nullable<DateTime> nTo = null;
            if (req.to.ToOADate() != 0)
                nTo = req.to;


            apids.sp_api_getPaymentsHistoryDataTable table = ad.GetData(req.userName, nFrom, nTo, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            UserPaymentsHistoryRecord[] res = new UserPaymentsHistoryRecord[table.Rows.Count];
            for (int i = 0; i < table.Rows.Count; i++)
            {
                res[i] = new UserPaymentsHistoryRecord();
                res[i].date = table[i].EXECUTEDAT;
                res[i].amount = table[i].AMOUNT;
                res[i].paymentSystem = table[i].PAYMENTSYSTEM;

            }
            return res;
        }

        public static UserExpensesHistoryRecord[] getExpensesHistory(Service svc, GetUserExpensesHistoryReq req)
        {
            // try to find service
            sp_api_getExpensesHistoryTableAdapter ad = new sp_api_getExpensesHistoryTableAdapter();
            Nullable<int> errorCode = 0;

            Nullable<DateTime> nFrom = null;
            if (req.from.ToOADate() != 0)
                nFrom = req.from;
            Nullable<DateTime> nTo = null;
            if (req.to.ToOADate() != 0)
                nTo = req.to;


            apids.sp_api_getExpensesHistoryDataTable table = ad.GetData(req.userName, nFrom, nTo, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            UserExpensesHistoryRecord[] res = new UserExpensesHistoryRecord[table.Rows.Count];
            for (int i = 0; i < table.Rows.Count; i++)
            {
                res[i] = new UserExpensesHistoryRecord();
                res[i].date = table[i].EXECUTEDAT;
                res[i].amount = table[i].AMOUNT;
                res[i].serviceName = table[i].SERVICENAME;
                res[i].reason = table[i].REASON;
            }
            return res;
        }

        public static UsernameAndPartnerRecord[] findUserByEmail(Service svc, string email)
        {
            sp_api_findUserByEmailTableAdapter ad = new sp_api_findUserByEmailTableAdapter();
            int? errorCode = 0;

            apids.sp_api_findUserByEmailDataTable table = ad.GetData(email, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");

            UsernameAndPartnerRecord[] res = new UsernameAndPartnerRecord[table.Rows.Count];
            for (int i = 0; i < table.Rows.Count; i++)
            {
                res[i] = new UsernameAndPartnerRecord();
                res[i].userName = table[i].USERNAME;
                if (!table[i].IsPARTNERNAMENull()) res[i].partnerName = table[i].PARTNERNAME;
            }
            return res;
        }

        public static decimal getAwardAmount(Service svc, GetAwardAmountReq req)
        {
            sp_api_getAwardAmountTableAdapter ad = new sp_api_getAwardAmountTableAdapter();
            int? errorCode = 0;
            apids.sp_api_getAwardAmountDataTable table =
                    ad.GetData(req.userName, svc.id, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
            return table[0].IsAwardAmountNull() ? 0 : table[0].AwardAmount;

        }

        public static decimal getValuePSDetailed(Service svc, GetValuePSDetailedReq req)
        {
            sp_api_getValuePSDetailedTableAdapter ad = new sp_api_getValuePSDetailedTableAdapter();
            int? errorCode = 0;
            apids.sp_api_getValuePSDetailedDataTable table =
                ad.GetData(svc.id, req.userName, req.ps, ref errorCode);
            if (errorCode != 0)
                throw new ApiException((int)errorCode, "");
            return table[0].IsamountPSNull() ? 0 : table[0].amountPS;
        }
    }
}
