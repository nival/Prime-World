using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Linq;
using System.Data;
using System.Reflection;
using System.Data.Linq.SqlClient;
using ZzimaBilling.AdminUI.BLL;
using System.Linq.Expressions;
using ZzimaBilling.API.Common;
using System.Data.SqlClient;
using System.Web.Configuration;
namespace ZzimaBilling.AdminUI.DAL
{
    public class UserDAL
    {
        #region For Users.aspx

        private static IQueryable<vw_gui_User> GetUsersFilteredQuery(BillingSPDataContext ctx, UserFilterBLL filter)
        {
            var query = (from users in ctx.vw_gui_Users
                         select users);
            //Process if there are mask simbols
            if (!string.IsNullOrEmpty(filter.UsernameMask))
            {
                string sqlMask = filter.UsernameMask.ReplaceStarsAndQuestions();
                query = from users in query
                        where SqlMethods.Like(users.Username, sqlMask)
                        select users;
            }

            if (!string.IsNullOrEmpty(filter.UserIDMask))
            {
                int sqlVal = Convert.ToInt32(filter.UserIDMask.ReplaceStarsAndQuestions());
                query = from users in query
                        where SqlMethods.Equals(users.id, sqlVal)
                        select users;
            }

            if (!string.IsNullOrEmpty(filter.EmailMask))
            {
                string sqlMask = filter.EmailMask.ReplaceStarsAndQuestions();
                query = from users in query
                        where SqlMethods.Like(users.email, sqlMask)
                        select users;
            }
            //
            if (!string.IsNullOrEmpty(filter.PartnerProgramName))
            {
                query = query.Where(users => users.PartnerProgram == filter.PartnerProgramName);
            }
            if (filter.TotalFrom > 0 || filter.TotalTo < int.MaxValue)
            {
                query = query.Where(users => users.Total.Value >= filter.TotalFrom &&
                                        users.Total.Value <= filter.TotalTo);
            }

            if (filter.RealFrom > 0 || filter.RealTo < int.MaxValue)
            {
                query = query.Where(users => users.RealBalance.Value >= filter.RealFrom &&
                                        users.RealBalance.Value <= filter.RealTo);
            }

            if (filter.BonusFrom > 0 || filter.BonusTo < int.MaxValue)
            {
                query = query.Where(users => users.BonusMoney.Value >= filter.BonusFrom &&
                                        users.BonusMoney.Value <= filter.BonusTo);
            }
            return query;
        }

        private static IQueryable<vw_gui_User> GetUsersOrderedQuery(IQueryable<vw_gui_User> query, string sortExpression, bool asc)
        {
            switch (sortExpression)
            {
                case "Username":
                    {
                        query = asc ? query.OrderBy(users => users.Username) :
                            query.OrderByDescending(users => users.Username);
                        break;
                    }
                case "id":
                    {
                        query = asc ? query.OrderBy(users => users.id) :
                            query.OrderByDescending(users => users.id);
                        break;
                    }

                case "email":
                    {
                        query = asc ? query.OrderBy(users => users.email) :
                            query.OrderByDescending(users => users.email);
                        break;
                    }

                case "Total":
                    {
                        query = asc ? query.OrderBy(users => users.Total) :
                            query.OrderByDescending(users => users.Total);
                        break;
                    }

                case "RealBalance":
                    {
                        query = asc ? query.OrderBy(users => users.RealBalance) :
                            query.OrderByDescending(users => users.RealBalance);
                        break;
                    }

                case "BonusMoney":
                    {
                        query = asc ? query.OrderBy(users => users.BonusMoney) :
                            query.OrderByDescending(users => users.BonusMoney);
                        break;
                    }

                case "PartnerProgram":
                    {
                        query = asc ? query.OrderBy(users => users.PartnerProgram) :
                            query.OrderByDescending(users => users.PartnerProgram);
                        break;
                    }
                case null:
                default:
                    sortExpression = null;
                    break;
            }


            if (sortExpression != null)
            {
                var ordered = ((IOrderedQueryable<vw_gui_User>)query);
                query = ordered.ThenBy(users => users.id);
            }
            else
                query = query.OrderBy(users => users.id);

            return query;
        }

        public static DataTable GetUsers(
            int startIndex, int pageSize, UserFilterBLL filter, string sortExpression, bool asc)
        {
            BillingSPDataContext ctx = new BillingSPDataContext();
            var query = GetUsersFilteredQuery(ctx, filter);
            query = GetUsersOrderedQuery(query, sortExpression, asc);
            query = query.Skip(startIndex).Take(pageSize);
            return ToDataTable(query);
        }

        public static DataTable GetAllUsersTable(UserFilterBLL filter, string sortExpression, bool asc)
        {
            BillingSPDataContext ctx = new BillingSPDataContext();
            var query = GetUsersFilteredQuery(ctx, filter);
            query = GetUsersOrderedQuery(query, sortExpression, asc);
            return ToDataTable(query);
        }

        public static int SelectCount(UserFilterBLL filter)
        {
            BillingSPDataContext ctx = new BillingSPDataContext();
            return GetUsersFilteredQuery(ctx, filter).Count();
        } 

        #endregion

        #region For GeneralInfo.aspx

        public static UserGeneralInfoBLL GetUserGeneralInfo(int userID)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                UserGeneralInfoBLL userInfo;
                try
                {
                    userInfo = (from ui in db.Users
                                where ui.id == userID
                                select new UserGeneralInfoBLL
                                {
                                    ID = ui.id,
                                    Username = ui.name,
                                    Email = ui.Profile.email,
                                    RefferalCode = ui.Profile.referalCode,
                                    RegisteredDate = ui.Profile.createdat,
                                    FinalBan = ui.finalBan,
                                    TempBan = ui.tempBan
                                }).SingleOrDefault<UserGeneralInfoBLL>();
                }
                catch (Exception ex)
                {
                    throw new Exception("There is no user with such ID.", ex);
                }
                return userInfo;
            }
        } 

        #endregion

        #region For ActualBalanse.aspx

        public static ActualBalanceBLL GetActualBalance(int userID, string serviceId)
        {
            if (String.IsNullOrEmpty(serviceId) || serviceId == "0") serviceId = "1";
            ActualBalanceBLL actualBalance = new ActualBalanceBLL();
            string userName;
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                userName = (from tb in db.vw_gui_Users
                                              where tb.id == userID
                                              select tb.Username).Single<string>();
                
                int? error = 0;
                int serviceID = Convert.ToInt32(serviceId);
                ISingleResult<sp_api_getBalanceResult> result = db.sp_api_getBalance(userName, serviceID, ref error);
                if (result != null)
                {
                    actualBalance.TotalBalance = (from rec in result
                                                   select rec.AMOUNT.Value).SingleOrDefault<decimal>() ;
                }
                ///////non-filter version
                //actualBalance.TotalBalance = (from tb in db.vw_gui_Users
                //                              where tb.id == userID
                //                              select tb.Total.Value).Single<Decimal>();

                //actualBalance.BonusBalance = (from tb in db.vw_gui_Users
                //                              where tb.id == userID
                //                              select tb.BonusMoney.Value).Single<Decimal>();
            }
            return actualBalance;
        }

        public static List<PSystemBLL> GetRealPaymentSystems(int userID)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                ISingleResult<sp_gui_getRealPaymentSystemsResult> result = db.sp_gui_getRealPaymentSystems(userID);
                if (result == null)
                    return new List<PSystemBLL>();
                var data = (from ps in result
                            select new PSystemBLL
                            {
                                PSystemID = ps.systemid.Value,
                                Name = ps.name
                            }).ToList<PSystemBLL>();
                return data;
            }
        }

        

        public static List<PaymentSystemAccountBLL> GetPaymentSystemReplenishments(int userID)
        {
            List<PSystemBLL> paymentSystems = PaymentSystemDAL.SelectReal();
            List<PaymentSystemAccountBLL> ps = new List<PaymentSystemAccountBLL>();
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                foreach (PSystemBLL psystem in paymentSystems)
                {
                    decimal amount = (from psAccounts in db.vw_UserBalances
                                      where psAccounts.systemid == psystem.PSystemID &&
                                            psAccounts.id == userID
                                      select psAccounts.amount.Value).SingleOrDefault<Decimal>();
                    if (psystem.PSystemID != 2 && psystem.PSystemID != 1 && amount > 0)
                    {
                        ps.Add(new PaymentSystemAccountBLL
                        {
                            UserID = userID,
                            PaymentSystemID = psystem.PSystemID,
                            PaymentSystemName = psystem.Name,
                            Amount = amount
                        });
                    }
                }
                return ps;
            }
        }
        public static DataTable GetPaymentSystemsTableFiltered(int userID, string serviceID)
        {
            List<PaymentSystemAccountBLL> psList = null;
            if (String.IsNullOrEmpty(serviceID)) serviceID = "0";
            
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                ISingleResult<sp_gui_getActualBalanceFilteredResult> result = db.sp_gui_getActualBalanceFiltered(userID, Convert.ToInt32(serviceID));

                psList = (from ps in result
                            select new PaymentSystemAccountBLL
                            {
                                PaymentSystemID = ps.PaymentSystemID.Value,
                                Amount = ps.Amount,
                                PaymentSystemName = ps.PaymentSystemName,
                                UserID = userID
                            }).ToList<PaymentSystemAccountBLL>();

            }
            DataTable table = ToDataTable<PaymentSystemAccountBLL>(psList);
            if (table.Rows.Count == 0)
                table.Rows.Add();
            return table;
        }
        
        public static DataTable GetPaymentSystemReplenishmentsTable(int userID)
        {
            DataTable table = ToDataTable<PaymentSystemAccountBLL>(GetPaymentSystemReplenishments(userID));
            if (table.Rows.Count == 0)
                table.Rows.Add();
            return table;//ToDataTable<PaymentSystemAccountBLL>(GetPaymentSystemReplenishments(userID));
        } 

        #endregion

        #region For AccountCBT.aspx

        public static List<AccountDetailBLL> GetAccountDetails(int userID)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                ISingleResult<sp_gui_getAccountCBTDetailsResult> results = db.sp_gui_getAccountCBTDetails(userID);
                List<AccountDetailBLL> accountDetails = new List<AccountDetailBLL>();

                foreach (sp_gui_getAccountCBTDetailsResult accountDetail in results)
                {
                    accountDetails.Add(new AccountDetailBLL
                    {
                        ServiceName = accountDetail.name,
                        Amount = accountDetail.amount
                    });
                }

                return accountDetails;
            }
        }

        //For sorting in ODS

        public static DataTable GetAccountDetailsTable(int userID)
        {
            return ToDataTable<AccountDetailBLL>(GetAccountDetails(userID));
        }

        public static decimal GetCBTAmount(int userID)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                ISingleResult<sp_gui_getAccountCBTDetailsResult> results = db.sp_gui_getAccountCBTDetails(userID);
                Decimal amount = 0;
                foreach (sp_gui_getAccountCBTDetailsResult accountDetail in results)
                {
                    amount += accountDetail.amount;
                }

                return amount;
            }
        } 
        #endregion

        #region For Games.aspx
        //For Games.aspx

        private static List<ServiceBLL> GetIndependentServices(int userID)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                ISingleResult<sp_gui_getSubscribedIndepndentServicesResult> services = db.sp_gui_getSubscribedIndepndentServices(userID);
                List<ServiceBLL> servicesBLL = new List<ServiceBLL>();
                foreach (sp_gui_getSubscribedIndepndentServicesResult service in services)
                {
                    servicesBLL.Add(new ServiceBLL
                    {
                        ServiceID = service.id,
                        Name = service.name
                    });
                }
                return servicesBLL;
            }
        }

        private static List<ServiceBLL> GetServices(int userID)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                ISingleResult<sp_gui_getSubscribedServicesResult> services = db.sp_gui_getSubscribedServices(userID);
                List<ServiceBLL> servicesBLL = new List<ServiceBLL>();
                foreach (sp_gui_getSubscribedServicesResult service in services)
                {
                    servicesBLL.Add(new ServiceBLL
                    {
                        ServiceID = service.id,
                        Name = service.name
                    });
                }
                return servicesBLL;
            }
        }

        public static int GetIdByUserName(string userName)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                int userid = (from user in db.Users
                              where user.name == userName
                              select user.id).FirstOrDefault();
                return userid;
            }
        }

        public static List<LastGameSessionBLL> GetLastSessions(int userID)
        {
            List<LastGameSessionBLL> lastSessionsBLL = new List<LastGameSessionBLL>();
            //List<ServiceBLL> independentServices = UserDAL.GetIndependentServices(userID);
            List<ServiceBLL> userServices = GetServices(userID);
            if (userServices.Count > 0)
            {
                using (BillingSPDataContext db = new BillingSPDataContext())
                {
                    foreach (ServiceBLL service in userServices)
                    {
                        ISingleResult<sp_gui_getLastSessionResult> lastSession = db.sp_gui_getLastSession(userID, service.ServiceID);
                        if (lastSession != null || lastSession.Count() > 0)
                        {
                            LastGameSessionBLL lastGameSessionBLL = new LastGameSessionBLL();
                            var ls = lastSession.FirstOrDefault<sp_gui_getLastSessionResult>();
                            if (ls != null)
                            {
                                lastGameSessionBLL.ID = service.ServiceID;
                                lastGameSessionBLL.Name = ls.name;
                                lastGameSessionBLL.LastSession = ls.occurredat;
                                lastSessionsBLL.Add(lastGameSessionBLL);
                            }
                        }
                    }
                }
            }
            return lastSessionsBLL;
        }

        //For sorting in ODS
        public static DataTable GetLastSessionsTable(int userID)
        {
            return ToDataTable<LastGameSessionBLL>(GetLastSessions(userID));
        }

        public static List<GmaHistoryBLL> GetGmaHistory(int userID, GmaHistoryFilter filter)
        {
            List<GmaHistoryBLL> gmaHistoryListBLL = new List<GmaHistoryBLL>();
            try
            {
                BillingSPDataContext db = new BillingSPDataContext();
                int? error = 0;

                string loginString = filter.GmaLogin.Trim() == "" ? "%" : filter.GmaLogin.ReplaceStarsAndQuestions();
                string commentString = filter.Comment.Trim() == "" ? "%" : filter.Comment.ReplaceStarsAndQuestions();

                ISingleResult<sp_gui_adminWriteOffHistoryResult> results =
                    db.sp_gui_adminWriteOffHistory(userID,
                                                    filter.DateFrom,
                                                    filter.DateTo,
                                                    filter.AmountFrom,
                                                    filter.AmountTo,
                                                    loginString,
                                                    commentString,
                                                    ref error);
                if (error < 0)
                    throw new ApiException((int)error);

                foreach (sp_gui_adminWriteOffHistoryResult rec in results)
                {
                    gmaHistoryListBLL.Add(new GmaHistoryBLL
                    {
                        Date = rec.executedat,
                        Sum = rec.amount,
                        Comment = rec.reason,
                        Login = rec.gmaLogin
                    });
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Unable to get writeoff history.", ex);
            }
            return gmaHistoryListBLL;
        }

        //For sorting in ODS

        public static DataTable GetGmaHistoryTable(int userID, GmaHistoryFilter filter)
        {
            return ToDataTable<GmaHistoryBLL>(GetGmaHistory(userID, filter));
        }

        //For Payments History 
        public static void UnTotalBanUser(int userID)
        {

        }
        
        #endregion
        
        #region HelperMethods

        public static DataTable GetUsers()
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                var query = from users in db.vw_gui_Users
                            select users;
                return ToDataTable<vw_gui_User>(query);

            }
        }

        /// <summary>
        /// Helper method for converting List<T> to DataTable of T entities
        /// </summary>
        public static DataTable ToDataTable<T>(List<T> items)
        {
            var tb = new DataTable(typeof(T).Name);
            PropertyInfo[] props = typeof(T).GetProperties(BindingFlags.Public | BindingFlags.Instance);
            foreach (PropertyInfo prop in props)
            {
                Type t = GetCoreType(prop.PropertyType);
                tb.Columns.Add(prop.Name, t);
            }
            if (items!=null && items.Count > 0)
            {
                foreach (T item in items)
                {
                    var values = new object[props.Length];
                    for (int i = 0; i < props.Length; i++)
                    {
                        values[i] = props[i].GetValue(item, null);
                    }
                    tb.Rows.Add(values);
                }
            }
            return tb;
        }

        /// <summary>
        /// Helper method for converting IQueryable<T> to DataTable of T entities
        /// </summary>
        public static DataTable ToDataTable<T>(IQueryable<T> items)
        {
            var tb = new DataTable(typeof(T).Name);
            PropertyInfo[] props = typeof(T).GetProperties(BindingFlags.Public | BindingFlags.Instance);
            foreach (PropertyInfo prop in props)
            {
                Type t = GetCoreType(prop.PropertyType);
                tb.Columns.Add(prop.Name, t);
            }
            foreach (T item in items)
            {
                var values = new object[props.Length];
                for (int i = 0; i < props.Length; i++)
                {
                    values[i] = props[i].GetValue(item, null);
                }
                tb.Rows.Add(values);
            }
            //if tb has now rows then add one empty row
            if (tb.Rows.Count == 0)
            {
                DataRow emptyRow = tb.NewRow();
                tb.Rows.Add(emptyRow);
            }
            return tb;
        }

        public static Type GetCoreType(Type t)
        {
            if (t != null && IsNullable(t))
            {
                if (!t.IsValueType)
                {
                    return t;
                }
                else
                {
                    return Nullable.GetUnderlyingType(t);
                }
            }
            else
            {
                return t;
            }
        }

        public static bool IsNullable(Type t)
        {
            return !t.IsValueType || (t.IsGenericType && t.GetGenericTypeDefinition() == typeof(Nullable<>));
        }

        private static List<vw_gui_User> ToUserList(IQueryable<vw_gui_User> list)
        {
            List<vw_gui_User> newlist = new List<vw_gui_User>();
            int count = list.Count();
            foreach (var item in list)
            {
                vw_gui_User newitem = new vw_gui_User
                {
                    Username = item.Username,
                    email = item.email,
                    RealBalance = item.RealBalance.GetValueOrDefault(0),
                    Total = item.Total.GetValueOrDefault(0),
                    BonusMoney = item.BonusMoney.GetValueOrDefault(0),
                    PartnerProgram = item.PartnerProgram
                };
                newlist.Add(newitem);
            }
            return newlist;
        }

        #endregion
    }

    #region Extension Methods
    public static class ExtensionMethods
    {
        public static String ReplaceStarsAndQuestions(this string mask)
        {
            return mask.Replace('*', '%').Replace('?', '_');
        }

        /*public static bool HasStarsAndQuestions(this string mask)
        {
            return mask.Contains('*') || mask.Contains('?');
        } */
    } 
    #endregion
}
