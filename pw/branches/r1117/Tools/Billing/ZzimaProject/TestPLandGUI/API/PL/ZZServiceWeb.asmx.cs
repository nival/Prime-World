using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.Xml.Linq;
using System.Globalization;
using ZzimaBilling.API.DL;
using ZzimaBilling.API.BL;
using ZzimaBilling.API.Common;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using System.Collections.Generic;

namespace ZzimaBilling.API.PL
{


    [WebService(Namespace = "http://zzima.com/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [ToolboxItem(false)]
    public class ZZServiceWeb : System.Web.Services.WebService
    {
        public class A_TestHash
        {
            public byte[] bt;
            public string bin;
        }

        [WebMethod(EnableSession = true)]
        public A_TestHash A_GenerateHash(string val)
        {
            A_TestHash att = new A_TestHash();
            byte[] bt = Encoding.UTF8.GetBytes(val);
            MD5 md5Hasher = MD5.Create();
            att.bt = md5Hasher.ComputeHash(bt, 0, bt.Length);

            att.bin = "";
            foreach (byte b in att.bt)
            {
                String ch = String.Format("{0:X2}", b);
                att.bin += ch;
            }
            return att;
        }

        [WebMethod]
        public string A_ToBase64(string val)
        {
            byte[] bt = Encoding.UTF8.GetBytes(val);
            MD5 md5Hasher = MD5.Create();
            return Convert.ToBase64String(bt);
        }

        [WebMethod]
        public string A_FromBase64(string val)
        {
            return System.Text.Encoding.UTF8.GetString(Convert.FromBase64String(val));
        }


        [WebMethod(EnableSession = true)]
        public RegisterUserResponse RegisterUser(RegisterUserReq req)
        {
            RegisterUserResponse resp = new RegisterUserResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User usr = ZzimaBilling.API.BL.User.create(req);
                resp.userId = usr.id;
                resp.accountName = usr.account;
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public AuthorizeUserResponse AuthorizeUser(AuthorizeUserReq req)
        {
            AuthorizeUserResponse resp = new AuthorizeUserResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User usr = ZzimaBilling.API.BL.User.authorize(svc, req);
                resp.userId = usr.id;

            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public AccountReplenishmentResponse AccountReplenish(AccountReplenishmentReq req)
        {
            AccountReplenishmentResponse resp = new AccountReplenishmentResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User.replenish(svc, req);

            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }
        
        [WebMethod(EnableSession = true)]
        public EnrollAccWithAwardResponse EnrollAccWithAward(EnrollAccWithAwardReq req)
        {
            EnrollAccWithAwardResponse resp = new EnrollAccWithAwardResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User.replenishWithAward(svc, req);

            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public ConfirmWriteOffResponse ConfirmWriteOff(ConfirmWriteOffReq req)
        {
            ConfirmWriteOffResponse resp = new ConfirmWriteOffResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User.confirmWriteOff(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public ReserveAmountResponse ReserveAmount(ReserveAmountReq req)
        {
            ReserveAmountResponse resp = new ReserveAmountResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.reserveId = ZzimaBilling.API.BL.User.reserveAmount(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public AccountWriteOffResponse AccountWriteOff(AccountWriteOffReq req)
        {
            AccountWriteOffResponse resp = new AccountWriteOffResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User.writeOff(svc, req);

            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public RemoveAmountWithRealResponse RemoveAmountWithReal ( AccountWriteOffReq req )
        {
            RemoveAmountWithRealResponse resp = new RemoveAmountWithRealResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.realAmount = ZzimaBilling.API.BL.User.removeAmountWithReal(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public MoneyTranseferResponse MoneyTransefer(MoneyTranseferReq req)
        {
            MoneyTranseferResponse resp = new MoneyTranseferResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User.transfer(svc, req);

            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public GetServicesListResponse GetServicesList(GetServicesListReq req)
        {
            GetServicesListResponse resp = new GetServicesListResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.services = svc.getServicesList(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public SubscribeServiceResponse SubscribeService(SubscribeServiceReq req)
        {
            SubscribeServiceResponse resp = new SubscribeServiceResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.accauntName = svc.subscribe(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;

        }

        [WebMethod(EnableSession = true)]
        public GetServiceGuidNameResponse GetServiceGuidName(GetServiceGuidNameReq req)
        {
            GetServiceGuidNameResponse resp = new GetServiceGuidNameResponse();
            try 
            {
                Service svc = Service.checkCRC(Context, req);
                resp.accauntName = svc.getServiceGuidName(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public UnsubscribeServiceResponse UnsubscribeService(UnsubscribeServiceReq req)
        {
            UnsubscribeServiceResponse resp = new UnsubscribeServiceResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                svc.unsubscribe(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public GetServiceSettingsResponse GetServiceSettings(GetServiceSettingsReq req)
        {
            GetServiceSettingsResponse resp = new GetServiceSettingsResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.serviceSettings = svc.getServiceSettings(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public SetServiceSettingsResponse SetServiceSettings(SetServiceSettingsReq req)
        {
            SetServiceSettingsResponse resp = new SetServiceSettingsResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                svc.setServiceSettings(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public BanUserResponse BanUser(BanUserReq req)
        {
            BanUserResponse resp = new BanUserResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                svc.ban(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public UnbanUserResponse UnbanUser(UnbanUserReq req)
        {
            UnbanUserResponse resp = new UnbanUserResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                svc.unban(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public GetUserProfileResponse GetUserProfile(GetUserProfileReq req)
        {
            GetUserProfileResponse resp = new GetUserProfileResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.info = ZzimaBilling.API.BL.User.getProfile(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public ByIdGetUserProfileResponse ByIdGetUserProfile(ByIdGetUserProfileReq req)
        {
            ByIdGetUserProfileResponse resp = new ByIdGetUserProfileResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.info = ZzimaBilling.API.BL.User.byIdGetUserProfile(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public SetUserProfileResponse SetUserProfile(SetUserProfileReq req)
        {
            SetUserProfileResponse resp = new SetUserProfileResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User.setProfile(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public SetUserPasswordResponse SetUserPassword(SetUserPasswordReq req)
        {
            SetUserPasswordResponse resp = new SetUserPasswordResponse();
            try
            {
                ZzimaBilling.API.BL.User.setPassword(req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public GetUserBalanceResponse GetUserBalance(GetUserBalanceReq req)
        {
            GetUserBalanceResponse resp = new GetUserBalanceResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.amount = ZzimaBilling.API.BL.User.getBalance(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public GetUserBalanceExResponse GetUserBalanceEx(GetUserBalanceExReq req)
        {
            GetUserBalanceExResponse response = new GetUserBalanceExResponse();
            try
            {
                var svc = Service.checkCRC(Context, req);
                response.detailedBalance = ZzimaBilling.API.BL.User.getBalanceEx(svc, req);
            }catch(ApiException ex)
            {
                response.code = ex.code;
                response.message = ex.description;
            }catch(Exception ex)
            {
                response.code = (int) ApiException.ErrorCode.E_UNEXPECTED;
                response.message = ex.ToString();
            }
            return response;
        }

        [WebMethod(EnableSession = true)]
        public WriteOffExResponse WriteOffEx(WriteOffExReq req)
        {
            WriteOffExResponse resp = new WriteOffExResponse();
            try
            {
                // writting off the amount of money and getting the operation id
                var svc = Service.checkCRC(Context, req);
                decimal? remainAmount = 0;
                resp.operationId = ZzimaBilling.API.BL.User.writeOffEx(svc, req, ref remainAmount);
            }catch(ApiException ex)
            {
                resp.code = ex.code;
                resp.message = ex.description;
            }
            catch (Exception ex)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = ex.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public GetOperationDetailsResponse GetOperationDetails(GetOperationDetailsReq req)
        {
            GetOperationDetailsResponse resp = new GetOperationDetailsResponse();
            try
            {
                var svc = Service.checkCRC(Context, req);
                resp.writeOffs = ZzimaBilling.API.BL.User.GetOperationDetails(svc, req);
            }
            catch (ApiException ex)
            {
                resp.code = ex.code;
                resp.message = ex.description;
            }
            catch (Exception ex)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = ex.ToString();
            }
            return resp;
        }


        [WebMethod(EnableSession = true)]
        public GetAwardAmountResponse GetAwardAmount(GetAwardAmountReq req)
        {
            GetAwardAmountResponse resp = new GetAwardAmountResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.amount = ZzimaBilling.API.BL.User.getAwardAmount(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public PromoActivateResponse PromoActivate(PromoActivateReq req)
        {
            PromoActivateResponse resp = new PromoActivateResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                ZzimaBilling.API.BL.User.promoActivate(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public GetUserPaymentsHistoryResponse GetUserPaymentsHistory(GetUserPaymentsHistoryReq req)
        {
            GetUserPaymentsHistoryResponse resp = new GetUserPaymentsHistoryResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.payments = ZzimaBilling.API.BL.User.getPaymentsHistory(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;

        }

        [WebMethod(EnableSession = true)]
        public GetUserExpensesHistoryResponse GetUserExpensesHistory(GetUserExpensesHistoryReq req)
        {
            GetUserExpensesHistoryResponse resp = new GetUserExpensesHistoryResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.expenses = ZzimaBilling.API.BL.User.getExpensesHistory(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public FindUserByEmailResponse FindUserByEmail(FindUserByEmailReq req)
        {
            FindUserByEmailResponse resp = new FindUserByEmailResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.userAndPartners = ZzimaBilling.API.BL.User.findUserByEmail(svc, req.email);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public ZeroAwardMoneyResponse ZeroAwardMoney(ZeroAwardMoneyReq req)
        {
            ZeroAwardMoneyResponse resp = new ZeroAwardMoneyResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.zeroedAmount = ZzimaBilling.API.BL.User.zeroAwardMoney(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }

        [WebMethod(EnableSession = true)]
        public GetValuePSDetailedResponse GetValuePSDetailed ( GetValuePSDetailedReq req )
        {
            GetValuePSDetailedResponse resp = new GetValuePSDetailedResponse();
            try
            {
                Service svc = Service.checkCRC(Context, req);
                resp.amount = ZzimaBilling.API.BL.User.getValuePSDetailed(svc, req);
            }
            catch (ApiException e)
            {
                resp.code = e.code;
                resp.message = e.description;
            }
            catch (Exception e)
            {
                resp.code = (int)ApiException.ErrorCode.E_UNEXPECTED;
                resp.message = e.ToString();
            }
            return resp;
        }
    }
}
