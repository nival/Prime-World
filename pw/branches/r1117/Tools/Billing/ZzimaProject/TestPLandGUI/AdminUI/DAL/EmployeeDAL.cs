using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Collections.Generic;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.DAL;
using System.Data.Linq;
using System.Security.Cryptography;
using System.Globalization;
using System.Text;
using ZzimaBilling.API.Common;
using System.Data.Linq.SqlClient;
using System.Linq.Expressions;

namespace ZzimaBilling.AdminUI.DAL
{
    public class EmployeeDAL
    {
        #region Constants : Protocol Settings

        private const int TYPE_SERVICES = 101;
        private const int TYPE_PSYSTEMS = 102;
        private const int TYPE_REQUESTS = 103;

        #endregion

        public static Employer Authorize(string name, string password)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                try
                {
                    sp_gui_AuthorizeAdministratorResult res = (from emps in db.sp_gui_AuthorizeAdministrator(name, Employer.generateHash(password))
                                                               select emps).SingleOrDefault<sp_gui_AuthorizeAdministratorResult>();
                    if (res.id == -1)
                        throw new Exception("Invalid username or password");

                    Employer adm = new Employer(res.id, res.groupid, name);
                    return adm;
                }
                catch (Exception ex)
                {
                    throw new Exception("Some problems with password or username (EmployeeDAL). <br/>", ex);
                }
            }
        }

        public static int GetGroup(string name)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                try
                {
                    Employee result = db.Employees.SingleOrDefault
                            (Employees => Employees.name == name);
                    if (result != null)
                        return result.groupid;
                }
                catch (Exception)
                {
                }
                return -1;
            }
        }

        public static void decreaseTemplatePriority(int id, int adminid)
        {

        }

        public static void deleteTemplate(int id, int adminid)
        {
            try
            {
                using (BillingSPDataContext db = new BillingSPDataContext())
                {
                    int? error = -1;
                    db.sp_gui_deleteTemplate(id, adminid, ref error);
                    if (error != 0)
                        throw new ApiException((int)error);
                    db.SubmitChanges();
                }
            }
            catch (Exception e)
            {

                throw new Exception("Ошибка в базе данных. Невозможно удалить шаблон: " + e.Message);
            }
        }

        public static List<Promocode> generatePromocodes(int count, double amount, string reason, int adminid)
        {
            List<Promocode> list = new List<Promocode>();
            return list;
        }

        public static List<vw_gui_Template> getTemplates()
        {
            try
            {
                using (BillingSPDataContext db = new BillingSPDataContext())
                {
                    List<vw_gui_Template> result = (from templates in db.vw_gui_Templates
                                                    orderby templates.Name ascending
                                                    select new vw_gui_Template
                                                    {
                                                        TemplateID = templates.TemplateID,
                                                        Name = templates.Name,
                                                        Mask = templates.Mask
                                                    }).ToList();
                    return result;
                }
            }
            catch (Exception e)
            {
                throw new Exception("Ошибка в базе данных при извлечении существующих шаблонов.", e);
            }
        }

        public Template getTemplate(int templateID)
        {
            try
            {
                using (BillingDataContext db = new BillingDataContext())
                {
                    Template result = db.Templates.SingleOrDefault
                        (template => template.id == templateID);
                    return result;
                }
            }
            catch (Exception)
            {

                throw new Exception("Ошибка в базе данных. Шаблона с таким ID не существует.");
            }
        }

        public static List<BalanceInfo> getUserBalanceInfo(int userid)
        {
            List<BalanceInfo> list = new List<BalanceInfo>();
            return list;
        }

        public static CbtInfo getUserCBTInfo(int userid)
        {
            CbtInfo info = new CbtInfo();
            return info;
        }

        #region Expenses History

        // --------------- Subjects----------------------------------------

        public static List<string> getOperationReasons(int userID)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<string> reasons = (from operations in db.Operations
                                        where operations.userid == userID &&
                                        operations.type == 201
                                        select operations.reason).Distinct().ToList<string>();
                return reasons;
            }
        }

        // --------------- Games -------------------------------------------

        public static List<ServiceBLL> getServices(int userID)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ServiceBLL> services = (from operations in db.Operations
                                             where operations.userid == userID &&
                                             operations.type == 201
                                             select new ServiceBLL
                                             {
                                                 ServiceID = operations.serviceid.Value,
                                                 Name = operations.Service.name
                                             }).Distinct().ToList<ServiceBLL>();
                return services;
            }
        }

        public static List<ServiceBLL> getServices()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ServiceBLL> services = (from operations in db.Operations
                                             where operations.type == 201
                                             select new ServiceBLL
                                             {
                                                 ServiceID = operations.serviceid.Value,
                                                 Name = operations.Service.name
                                             }).Distinct().ToList<ServiceBLL>();
                return services;
            }
        }

        // --------------- List of Details with Paging ----------------------

        private static List<ExpensesHistoryRecord> getUserExpensesHistory
            (int userid, int startIndex, int pageSize,
                ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            List<ExpensesHistoryRecord> result = new List<ExpensesHistoryRecord>();
            using (BillingDataContext db = new BillingDataContext())
            {
                //Filtering
                var query = db.Operations.Where(operation => operation.userid == userid && operation.type == 201 &&
                    operation.executedat >= filter.DateFrom && operation.executedat <= filter.DateTo &&
                    operation.amount >= filter.AmountFrom && operation.amount <= filter.AmountTo);
                //Filtering by games and subjects
                query = query.WhereIn(operation => (int)operation.serviceid, filter.Services);
                List<ExpensesHistoryRecord> records = query.WhereIn(operation => operation.reason, filter.Subjects).Select(operation =>
                    new ExpensesHistoryRecord 
                    {
                        Amount = operation.amount,
                        DateTime = operation.executedat,
                        Reason = operation.reason,
                        ServiceName = operation.Service.name
                    }).ToList<ExpensesHistoryRecord>();
                return Sort(records, sortExpression, asc).Skip(startIndex).Take(pageSize).ToList<ExpensesHistoryRecord>();
            }
        }

        // --------------- List of Details without Paging ----------------------

        private static List<ExpensesHistoryRecord> getUserExpensesHistory
            (int userid, ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            List<ExpensesHistoryRecord> result = new List<ExpensesHistoryRecord>();
            using (BillingDataContext db = new BillingDataContext())
            {
                //Filtering
                var query = (from operations in db.Operations
                             where operations.userid == userid &&
                             operations.type == 201 &&
                             operations.executedat >= filter.DateFrom && operations.executedat <= filter.DateTo &&
                             operations.amount >= filter.AmountFrom && operations.amount <= filter.AmountTo
                             select operations);

                List<ExpensesHistoryRecord> records = new List<ExpensesHistoryRecord>();

                records = (from temp in query
                           where temp.userid.Value == userid && temp.reason.Length > 0 && temp.serviceid != null
                           select new ExpensesHistoryRecord
                           {
                               Amount = temp.amount,
                               DateTime = temp.executedat,
                               Reason = temp.reason,
                               ServiceName = temp.Service.name,
                               ServiceID = temp.serviceid.Value
                           }).ToList<ExpensesHistoryRecord>();
                List<ExpensesHistoryRecord> targetRecords = new List<ExpensesHistoryRecord>();
                foreach (ExpensesHistoryRecord record in records)
                {
                    if (filter.Services.Contains(record.ServiceID) && filter.Subjects.Contains(record.Reason))
                        targetRecords.Add(record);
                }
                //Sorting

                return Sort(targetRecords, sortExpression, asc).ToList<ExpensesHistoryRecord>();
            }
        }

        // ---------------- Sort methods --------------------------------------

        protected static List<ExpensesHistoryRecord> Sort(List<ExpensesHistoryRecord> list, string sortExpression, bool asc)
        {
            if (list == null)
                return null;
            else
            {
                var preparedList = list as IEnumerable<ExpensesHistoryRecord>;
                switch (sortExpression)
                {
                    case "Amount":
                        preparedList = asc ? list.OrderBy(temp => temp.Amount) :
                            list.OrderByDescending(temp => temp.Amount);
                        break;
                    case "DateTime":
                        preparedList = asc ? list.OrderBy(temp => temp.DateTime) :
                            list.OrderByDescending(temp => temp.DateTime);
                        break;
                    case "Reason":
                        preparedList = asc ? list.OrderBy(temp => temp.Reason) :
                            list.OrderByDescending(temp => temp.Reason);
                        break;
                    case "ServiceName":
                        preparedList = asc ? list.OrderBy(temp => temp.ServiceName) :
                            list.OrderByDescending(temp => temp.ServiceName);
                        break;
                }
                return preparedList.ToList<ExpensesHistoryRecord>();
            }
        }

        protected static List<ExpensesHistorySCTRecord> Sort(List<ExpensesHistorySCTRecord> list, string sortExpression, bool asc)
        {
            if (list == null)
                return null;
            else
            {
                var preparedList = list as IEnumerable<ExpensesHistorySCTRecord>;
                switch (sortExpression)
                {
                    case "Place":
                        preparedList = asc ? list.OrderBy(temp => temp.Place) :
                            list.OrderByDescending(temp => temp.Place);
                        break;
                    case "Count":
                        preparedList = asc ? list.OrderBy(temp => temp.Count) :
                            list.OrderByDescending(temp => temp.Count);
                        break;
                    case "Percent":
                        preparedList = asc ? list.OrderBy(temp => temp.Percent) :
                            list.OrderByDescending(temp => temp.Percent);
                        break;
                    case "ServiceName":
                        preparedList = asc ? list.OrderBy(temp => temp.ServiceName) :
                            list.OrderByDescending(temp => temp.ServiceName);
                        break;
                }
                return preparedList.ToList<ExpensesHistorySCTRecord>();
            }
        }

        protected static List<ExpensesHistorySCMRecord> Sort(List<ExpensesHistorySCMRecord> list, string sortExpression, bool asc)
        {
            if (list == null)
                return null;
            else
            {
                var preparedList = list as IEnumerable<ExpensesHistorySCMRecord>;
                switch (sortExpression)
                {
                    case "Place":
                        preparedList = asc ? list.OrderBy(temp => temp.Place) :
                            list.OrderByDescending(temp => temp.Place);
                        break;
                    case "Amount":
                        preparedList = asc ? list.OrderBy(temp => temp.Amount) :
                            list.OrderByDescending(temp => temp.Amount);
                        break;
                    case "Percent":
                        preparedList = asc ? list.OrderBy(temp => temp.Percent) :
                            list.OrderByDescending(temp => temp.Percent);
                        break;
                    case "ServiceName":
                        preparedList = asc ? list.OrderBy(temp => temp.ServiceName) :
                            list.OrderByDescending(temp => temp.ServiceName);
                        break;
                }
                return preparedList.ToList<ExpensesHistorySCMRecord>();
            }
        }

        protected static List<ExpensesHistoryRCTRecord> Sort(List<ExpensesHistoryRCTRecord> list, string sortExpression, bool asc)
        {
            if (list == null)
                return null;
            else
            {
                var preparedList = list as IEnumerable<ExpensesHistoryRCTRecord>;
                switch (sortExpression)
                {
                    case "Place":
                        preparedList = asc ? list.OrderBy(temp => temp.Place) :
                            list.OrderByDescending(temp => temp.Place);
                        break;
                    case "Count":
                        preparedList = asc ? list.OrderBy(temp => temp.Count) :
                            list.OrderByDescending(temp => temp.Count);
                        break;
                    case "Percent":
                        preparedList = asc ? list.OrderBy(temp => temp.Percent) :
                            list.OrderByDescending(temp => temp.Percent);
                        break;
                    case "Reason":
                        preparedList = asc ? list.OrderBy(temp => temp.Reason) :
                            list.OrderByDescending(temp => temp.Reason);
                        break;
                }
                return preparedList.ToList<ExpensesHistoryRCTRecord>();
            }
        }

        protected static List<ExpensesHistoryRCMRecord> Sort(List<ExpensesHistoryRCMRecord> list, string sortExpression, bool asc)
        {
            if (list == null)
                return null;
            else
            {
                var preparedList = list as IEnumerable<ExpensesHistoryRCMRecord>;
                switch (sortExpression)
                {
                    case "Place":
                        preparedList = asc ? list.OrderBy(temp => temp.Place) :
                            list.OrderByDescending(temp => temp.Place);
                        break;
                    case "Count":
                        preparedList = asc ? list.OrderBy(temp => temp.Amount) :
                            list.OrderByDescending(temp => temp.Amount);
                        break;
                    case "Percent":
                        preparedList = asc ? list.OrderBy(temp => temp.Percent) :
                            list.OrderByDescending(temp => temp.Percent);
                        break;
                    case "Reason":
                        preparedList = asc ? list.OrderBy(temp => temp.Reason) :
                            list.OrderByDescending(temp => temp.Reason);
                        break;
                }
                return preparedList.ToList<ExpensesHistoryRCMRecord>();
            }
        }

        //---------------------------------------------------------------------

        private static List<ExpensesHistoryRecord> getUserExpensesHistory
            (int userid, ExpensesFilterBLL filter)
        {
            return getUserExpensesHistory(userid, filter, string.Empty, true);
        }

        // ---------------- Get summary ------------------------------------------

        public static void getUserExpensesSummary(int userid, ExpensesFilterBLL filter,
            ref int totalCount, ref decimal totalAmount,
            ref int gamesCount, ref int subjectsCount)
        {
            totalCount = 0;
            totalAmount = 0;
            gamesCount = 0;
            subjectsCount = 0;
            var list = getUserExpensesHistory(userid, filter);
            totalCount = list.Count;
            totalAmount = list.Sum(temp => temp.Amount);
            gamesCount = list.Select(temp => temp.ServiceName).Distinct().Count();
            subjectsCount = list.Select(temp => temp.Reason).Distinct().Count();
        }

        // ---------------- Get List Methods ------------------------------------------

        public static List<ExpensesHistorySCTRecord> getUserExpensesHistorySCT
            (int userid, ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ExpensesHistoryRecord> records = getUserExpensesHistory(userid, filter, sortExpression, asc);
                List<ExpensesHistorySCTRecord> recordsSCT = (from recs in records
                                                             group recs by recs.ServiceName into tempTable
                                                             select new ExpensesHistorySCTRecord
                                                             {
                                                                 ServiceName = tempTable.Key,
                                                                 Count = tempTable.Count()
                                                             }).ToList<ExpensesHistorySCTRecord>();
                int totalCount = recordsSCT.Sum(a => a.Count);
                recordsSCT = recordsSCT.OrderByDescending(temp => temp.Count).ToList<ExpensesHistorySCTRecord>();
                decimal totalPercent = 0;
                for (int i = 0; i < recordsSCT.Count; i++)
                {
                    recordsSCT[i].Percent = (decimal)recordsSCT[i].Count * 100 / totalCount;
                    totalPercent += recordsSCT[i].Percent;
                    recordsSCT[i].Place = i + 1;
                }

                return recordsSCT;
            }
        }

        public static List<ExpensesHistorySCMRecord> getUserExpensesHistorySCM
            (int userid, ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ExpensesHistoryRecord> records = getUserExpensesHistory(userid, filter, sortExpression, asc);
                List<ExpensesHistorySCMRecord> recordsSCM = (from recs in records
                                                             group recs by recs.ServiceName into tempTable
                                                             select new ExpensesHistorySCMRecord
                                                             {
                                                                 ServiceName = tempTable.Key,
                                                                 Amount = tempTable.Sum(a => a.Amount)
                                                             }).ToList<ExpensesHistorySCMRecord>();
                decimal totalAmount = recordsSCM.Sum(a => a.Amount);
                recordsSCM = recordsSCM.OrderByDescending(temp => temp.Amount).ToList<ExpensesHistorySCMRecord>();
                decimal totalPercent = 0;
                for (int i = 0; i < recordsSCM.Count; i++)
                {
                    recordsSCM[i].Percent = recordsSCM[i].Amount * 100 / totalAmount;
                    totalPercent += recordsSCM[i].Percent;
                    recordsSCM[i].Place = i + 1;
                }

                return recordsSCM;
            }
        }

        public static List<ExpensesHistoryRCTRecord> getUserExpensesHistoryRCT
            (int userid, ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ExpensesHistoryRecord> records = getUserExpensesHistory(userid, filter, sortExpression, asc);
                List<ExpensesHistoryRCTRecord> recordsRCT = (from recs in records
                                                             group recs by recs.Reason into tempTable
                                                             select new ExpensesHistoryRCTRecord
                                                             {
                                                                 Reason = tempTable.Key,
                                                                 Count = tempTable.Count()
                                                             }).ToList<ExpensesHistoryRCTRecord>();
                int totalCount = recordsRCT.Sum(a => a.Count);
                recordsRCT = recordsRCT.OrderByDescending(temp => temp.Count).ToList<ExpensesHistoryRCTRecord>();
                decimal totalPercent = 0;
                for (int i = 0; i < recordsRCT.Count; i++)
                {
                    recordsRCT[i].Percent = (decimal)recordsRCT[i].Count / totalCount * 100;
                    totalPercent += recordsRCT[i].Percent;
                    recordsRCT[i].Place = i + 1;
                }

                return recordsRCT;
            }
        }

        public static List<ExpensesHistoryRCMRecord> getUserExpensesHistoryRCM
            (int userid, ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ExpensesHistoryRecord> records = getUserExpensesHistory(userid, filter, sortExpression, asc);
                List<ExpensesHistoryRCMRecord> recordsRCM = (from recs in records
                                                             group recs by recs.Reason into tempTable
                                                             select new ExpensesHistoryRCMRecord
                                                             {
                                                                 Reason = tempTable.Key,
                                                                 Amount = tempTable.Sum(a => a.Amount)
                                                             }).ToList<ExpensesHistoryRCMRecord>();
                decimal totalAmount = recordsRCM.Sum(a => a.Amount);
                recordsRCM = recordsRCM.OrderByDescending(temp => temp.Amount).ToList<ExpensesHistoryRCMRecord>();
                decimal totalPercent = 0;
                for (int i = 0; i < recordsRCM.Count; i++)
                {
                    recordsRCM[i].Percent = recordsRCM[i].Amount * 100 / totalAmount;
                    totalPercent += recordsRCM[i].Percent;
                    recordsRCM[i].Place = i + 1;
                }

                return recordsRCM;
            }
        }


        // ---------------- Get Table Methods ------------------------------------------

        public static DataTable getUserExpensesHistoryTable
            (int userid, int startIndex, int pageSize,
                ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            return UserDAL.ToDataTable<ExpensesHistoryRecord>(getUserExpensesHistory(userid, startIndex, pageSize,
                filter, sortExpression, asc));
        }

        public static DataTable getUserExpensesHistorySCTTable(int userid, int startIndex, int pageSize,
                ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ExpensesHistoryRecord> records = getUserExpensesHistory(userid, filter, sortExpression, asc);
                List<ExpensesHistorySCTRecord> recordsSCT = (from recs in records
                                                             group recs by recs.ServiceName into tempTable
                                                             select new ExpensesHistorySCTRecord
                                                             {
                                                                 ServiceName = tempTable.Key,
                                                                 Count = tempTable.Count()
                                                             }).ToList<ExpensesHistorySCTRecord>();
                int totalCount = recordsSCT.Sum(a => a.Count);
                recordsSCT = recordsSCT.OrderByDescending(temp => temp.Count).ToList<ExpensesHistorySCTRecord>();

                decimal totalPercent = 0;
                for (int i = 0; i < recordsSCT.Count; i++)
                {
                    recordsSCT[i].Percent = (decimal)recordsSCT[i].Count * 100 / totalCount;
                    totalPercent += recordsSCT[i].Percent;
                    recordsSCT[i].Place = i + 1;
                }
                var sortedList = Sort(recordsSCT, sortExpression, asc);
                List<ExpensesHistorySCTRecord> page = (from p in sortedList
                                                       select p).Skip(startIndex).Take(pageSize)
                                                       .ToList<ExpensesHistorySCTRecord>();
                return UserDAL.ToDataTable<ExpensesHistorySCTRecord>(page);
            }
        }

        public static DataTable getUserExpensesHistorySCMTable(int userid, int startIndex, int pageSize,
                ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ExpensesHistoryRecord> records = getUserExpensesHistory(userid, filter, sortExpression, asc);
                List<ExpensesHistorySCMRecord> recordsSCM = (from recs in records
                                                             group recs by recs.ServiceName into tempTable
                                                             select new ExpensesHistorySCMRecord
                                                             {
                                                                 ServiceName = tempTable.Key,
                                                                 Amount = tempTable.Sum(a => a.Amount)
                                                             }).ToList<ExpensesHistorySCMRecord>();
                decimal totalAmount = recordsSCM.Sum(a => a.Amount);
                recordsSCM = recordsSCM.OrderByDescending(temp => temp.Amount).ToList<ExpensesHistorySCMRecord>();

                decimal totalPercent = 0;
                for (int i = 0; i < recordsSCM.Count; i++)
                {
                    recordsSCM[i].Percent = (decimal)recordsSCM[i].Amount * 100 / totalAmount;
                    totalPercent += recordsSCM[i].Percent;
                    recordsSCM[i].Place = i + 1;
                }
                var sortedList = Sort(recordsSCM, sortExpression, asc);
                var page = (from p in sortedList
                            select p).Skip(startIndex).Take(pageSize)
                            .ToList<ExpensesHistorySCMRecord>();
                return UserDAL.ToDataTable<ExpensesHistorySCMRecord>(page);
            }
        }

        public static DataTable getUserExpensesHistoryRCTTable(int userid, int startIndex, int pageSize,
                ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ExpensesHistoryRecord> records = getUserExpensesHistory(userid, filter, sortExpression, asc);
                List<ExpensesHistoryRCTRecord> recordsRCT = (from recs in records
                                                             group recs by recs.Reason into tempTable
                                                             select new ExpensesHistoryRCTRecord
                                                             {
                                                                 Reason = tempTable.Key,
                                                                 Count = tempTable.Count()
                                                             }).ToList<ExpensesHistoryRCTRecord>();
                int totalCount = recordsRCT.Sum(a => a.Count);
                recordsRCT = recordsRCT.OrderByDescending(temp => temp.Count).ToList<ExpensesHistoryRCTRecord>();

                decimal totalPercent = 0;
                for (int i = 0; i < recordsRCT.Count; i++)
                {
                    recordsRCT[i].Percent = (decimal)recordsRCT[i].Count * 100 / totalCount;
                    totalPercent += recordsRCT[i].Percent;
                    recordsRCT[i].Place = i + 1;
                }
                var sortedList = Sort(recordsRCT, sortExpression, asc);
                var page = (from p in sortedList
                            select p).Skip(startIndex).Take(pageSize)
                            .ToList<ExpensesHistoryRCTRecord>();
                return UserDAL.ToDataTable<ExpensesHistoryRCTRecord>(page);
            }
        }

        public static DataTable getUserExpensesHistoryRCMTable(int userid, int startIndex, int pageSize,
                ExpensesFilterBLL filter, string sortExpression, bool asc)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ExpensesHistoryRecord> records = getUserExpensesHistory(userid, filter, sortExpression, asc);
                List<ExpensesHistoryRCMRecord> recordsRCM = (from recs in records
                                                             group recs by recs.Reason into tempTable
                                                             select new ExpensesHistoryRCMRecord
                                                             {
                                                                 Reason = tempTable.Key,
                                                                 Amount = tempTable.Sum(a => a.Amount)
                                                             }).ToList<ExpensesHistoryRCMRecord>();
                decimal totalAmount = recordsRCM.Sum(a => a.Amount);
                recordsRCM = recordsRCM.OrderByDescending(temp => temp.Amount).ToList<ExpensesHistoryRCMRecord>();

                decimal totalPercent = 0;
                for (int i = 0; i < recordsRCM.Count; i++)
                {

                    recordsRCM[i].Percent = (decimal)recordsRCM[i].Amount * 100 / totalAmount;
                    totalPercent += recordsRCM[i].Percent;
                    recordsRCM[i].Place = i + 1;
                }
                var sortedList = Sort(recordsRCM, sortExpression, asc);
                var page = (from p in sortedList
                            select p).Skip(startIndex).Take(pageSize)
                           .ToList<ExpensesHistoryRCMRecord>();
                return UserDAL.ToDataTable<ExpensesHistoryRCMRecord>(page);
            }
        }

        // ----------------Get Count Methods------------------------------------------

        public static int getUserExpensesHistoryCount(int userid, ExpensesFilterBLL filter)
        {
            if (getUserExpensesHistory(userid, filter) == null)
                return 0;
            return getUserExpensesHistory(userid, filter).Count;
        }

        public static int getUserExpensesHistorySCTCount(int userid, ExpensesFilterBLL filter)
        {
            if (getUserExpensesHistory(userid, filter) == null)
                return 0;
            return (from history in getUserExpensesHistory(userid, filter)
                    select history.ServiceName).Distinct().Count();
        }

        public static int getUserExpensesHistorySCMCount(int userid, ExpensesFilterBLL filter)
        {
            if (getUserExpensesHistory(userid, filter) == null)
                return 0;
            return (from history in getUserExpensesHistory(userid, filter)
                    select history.ServiceName).Distinct().Count();
        }

        public static int getUserExpensesHistoryRCTCount(int userid, ExpensesFilterBLL filter)
        {
            if (getUserExpensesHistory(userid, filter) == null)
                return 0;
            return (from history in getUserExpensesHistory(userid, filter)
                    select history.Reason).Distinct().Count();
        }

        public static int getUserExpensesHistoryRCMCount(int userid, ExpensesFilterBLL filter)
        {
            if (getUserExpensesHistory(userid, filter) == null)
                return 0;
            return (from history in getUserExpensesHistory(userid, filter)
                    select history.Reason).Distinct().Count();
        }

        #endregion

        public static void getUserLastService(int userid)
        {

        }

        #region Payments History

        public static PaymentsHistorySummary getUserPaymentsSummary(int userid, Filter filter)
        {
            PaymentsHistorySummary summary = new PaymentsHistorySummary();
            List<PaymentsHistoryRecord> history = getUserPaymentsHistory(userid, filter);
            summary.TotalCount = history.Count;
            summary.TotalAmount = history.Sum(a => a.Amount);
            summary.PaymentSystemsCount = (from ps in history
                                           select ps.PaymentSystem).Distinct<string>().Count();
            return summary;
        }

        public static List<PaymentsHistoryRecord> getUserPaymentsHistory(int userid, Filter filter)
        {
            List<PaymentsHistoryRecord> result = new List<PaymentsHistoryRecord>();
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                int? error = 0;

                ISingleResult<sp_gui_getPaymentsHistoryResult> spResult =
                    db.sp_gui_getPaymentsHistory(userid, filter.DateFrom, filter.DateTo,
                    filter.AmountFrom, filter.AmountTo, filter.PaymentSystem, ref error);

                if (spResult != null)
                {
                    result = (from ps in spResult
                              select new PaymentsHistoryRecord
                              {
                                  PaymentSystem = ps.PAYMENTSYSTEM,
                                  Date = ps.EXECUTEDAT,
                                  Amount = ps.AMOUNT,
                                  Reason = ps.REASON
                              }).ToList<PaymentsHistoryRecord>();
                }
                return result;
            }
        }

        public static DataTable getUserPaymentsHistoryTable(int userid, Filter filter)
        {
            return UserDAL.ToDataTable<PaymentsHistoryRecord>(getUserPaymentsHistory(userid, filter));
        }

        public static int getUserPaymentsHistoryCount(int userid, Filter filter)
        {
            if (getUserPaymentsHistory(userid, filter) == null)
                return 0;
            return getUserPaymentsHistory(userid, filter).Count;
        }

        public static List<PaymentsHistoryCTRecord> getUserPaymentsHistoryCT(List<PaymentsHistoryRecord> list)
        {
            List<PaymentsHistoryCTRecord> result = new List<PaymentsHistoryCTRecord>();
            result = (from ctRecord in list
                      group ctRecord by ctRecord.PaymentSystem into ctTable
                      select new PaymentsHistoryCTRecord
                      {
                          PaymentSystem = ctTable.Key,
                          Count = ctTable.Count()
                      }).ToList<PaymentsHistoryCTRecord>();
            result = result.OrderByDescending(a => a.Count).ToList<PaymentsHistoryCTRecord>();
            int totalCount = result.Sum(a => a.Count);
            //Calculates Percent Field
            decimal totalPercent = 0;
            for (int i = 0; i < result.Count; i++)
            {
                if (i != result.Count - 1)
                {
                    result[i].Percent = ((decimal)result[i].Count * 100) / totalCount;
                    totalPercent += result[i].Percent;
                }
                else
                {
                    result[i].Percent = 100 - totalPercent;
                }
                result[i].Place = i + 1;
            }
            return result;
        }

        public static DataTable getUserPaymentsHistoryCTTable(int userid, Filter filter)
        {
            return UserDAL.ToDataTable<PaymentsHistoryCTRecord>(getUserPaymentsHistoryCT(getUserPaymentsHistory(userid, filter)));
        }

        public static int getUserPaymentsHistoryCTCount(int userid, Filter filter)
        {
            if (getUserPaymentsHistoryCT(getUserPaymentsHistory(userid, filter)) == null)
                return 0;
            return getUserPaymentsHistoryCT(getUserPaymentsHistory(userid, filter)).Count;
        }

        public static List<PaymentsHistoryCMRecord> getUserPaymentsHistoryCM(List<PaymentsHistoryRecord> list)
        {
            List<PaymentsHistoryCMRecord> result = new List<PaymentsHistoryCMRecord>();
            result = (from cmRecord in list
                      group cmRecord by cmRecord.PaymentSystem into cmTable
                      select new PaymentsHistoryCMRecord
                      {
                          PaymentSystem = cmTable.Key,
                          Amount = cmTable.Sum(a => a.Amount)
                      }).ToList<PaymentsHistoryCMRecord>();
            result = result.OrderByDescending(a => a.Amount).ToList<PaymentsHistoryCMRecord>();
            decimal totalAmount = result.Sum(a => a.Amount);
            //Calculates Percent Field
            decimal totalPercent = 0;
            for (int i = 0; i < result.Count; i++)
            {
                if (i != result.Count - 1)
                {
                    result[i].Percent = ((decimal)result[i].Amount * 100) / totalAmount;
                    totalPercent += result[i].Percent;
                }
                else
                {
                    result[i].Percent = 100 - totalPercent;
                }
                result[i].Place = i + 1;
            }
            return result;
        }

        public static DataTable getUserPaymentsHistoryCMTable(int userid, Filter filter)
        {
            return UserDAL.ToDataTable<PaymentsHistoryCMRecord>(getUserPaymentsHistoryCM(getUserPaymentsHistory(userid, filter)));
        }

        public static List<TransferHistoryRecord> getUserTransfersHistoryList(int userid, Filter filter)
        {
            List<TransferHistoryRecord> result = new List<TransferHistoryRecord>();

            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                int? error = 0;

                ISingleResult<sp_gui_getTransfersHistoryResult> spResult =
                    db.sp_gui_getTransfersHistory(userid, filter.DateFrom, filter.DateTo, filter.AmountFrom, filter.AmountTo, ref error);
                if (spResult != null)
                {
                    result = (from ps in spResult
                              select new TransferHistoryRecord
                              {
                                  EXECUTEDAT = ps.EXECUTEDAT,
                                  AMOUNT = ps.AMOUNT,
                                  REASON = ps.REASON,
                                  SRCACCID = ps.SRCACCID,
                                  DESTACCID = ps.DESTACCID
                              }).ToList<TransferHistoryRecord>();
                }
                return result;
            }
        }
        public static DataTable getUserTransfersHistoryTable(int userid, Filter filter)
        {
            return UserDAL.ToDataTable<TransferHistoryRecord>(getUserTransfersHistoryList(userid, filter));
        }

        public static int getUserPaymentsHistoryCMCount(int userid, Filter filter)
        {
            if (getUserPaymentsHistoryCM(getUserPaymentsHistory(userid, filter)) == null)
                return 0;
            return getUserPaymentsHistoryCM(getUserPaymentsHistory(userid, filter)).Count;
        }

        public static List<string> getAllSubjects()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                return (from subjects in db.Operations
                        where subjects.reason.ToString() != string.Empty
                        select subjects.reason.ToString()).Distinct().ToList<string>();
            }
        }

        #endregion

        #region Bonus History

        public static List<BonusHistoryBLL> getUserBonusesHistory(int userid, BonusFilter filter)
        {
            List<BonusHistoryBLL> result = new List<BonusHistoryBLL>();
            try
            {
                BillingSPDataContext db = new BillingSPDataContext();
                int? error = 0;
                string commentString = filter.Comment.Trim() == "" ? "%" : filter.Comment.ReplaceStarsAndQuestions();

                ISingleResult<sp_gui_getBonusesHistoryResult> results =
                    db.sp_gui_getBonusesHistory(userid, filter.DateFrom, filter.DateTo,
                    filter.AmountFrom, filter.AmountTo, commentString, ref error);

                if (error < 0)
                    throw new ApiException((int)error);

                foreach (sp_gui_getBonusesHistoryResult rec in results)
                {
                    result.Add(new BonusHistoryBLL
                    {
                        Date = rec.EXECUTEDAT,
                        Amount = rec.AMOUNT,
                        Reason = rec.REASON,
                    });
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Unable to get bonus history.", ex);
            }
            return result;
        }

        public static DataTable getUserBonusesHistoryTable(int userid, BonusFilter filter)
        {
            return UserDAL.ToDataTable<BonusHistoryBLL>(getUserBonusesHistory(userid, filter));
        }

        #endregion

        public static UserProfile getUserProfile(int userid)
        {
            UserProfile profile = new UserProfile();
            return profile;
        }

        public static List<UserProfile> getUsers()
        {
            List<UserProfile> list = new List<UserProfile>();
            return list;
        }

        public static void getUserUsedServices(int userid)
        {
        }

        public static void increaseTemplatePriority(int id, int adminid)
        {
        }

        /// <summary>
        /// Inserts new template
        /// </summary>
        public static void saveTemplate(int? id, Template template, int adminid)
        {
            try
            {
                using (BillingSPDataContext db = new BillingSPDataContext())
                {
                    int? error = -1;
                    db.sp_gui_saveTemplate(id, template.name, template.description,
                        template.mask, template.parameters, adminid, ref error);
                    if (error != 0)
                        throw new ApiException((int)error);
                    db.SubmitChanges();
                }
            }
            catch (Exception e)
            {
                throw new Exception("Ошибка в базе данных. Невозможно добавить новый шаблон: " + e.Message);
            }
        }
        /// <summary>
        /// Does administrative write-off
        /// </summary>
        public static void writeOff(int empId, byte[] password, int userId, int systemId, decimal amount, string reason)
        {
            try
            {
                using (BillingSPDataContext db = new BillingSPDataContext())
                {
                    int? err = 0;
                    db.sp_gui_adminWriteOff(empId, password, userId, null, systemId, amount, reason, ref err);
                    if (err != 0)
                        throw new ApiException((int)err);

                    return;
                }
            }
            catch (ApiException)
            {
                throw;
            }
            catch (Exception e)
            {
                throw new ApiException(ApiException.ErrorCode.E_UNEXPECTED, e.ToString());
            }
        }

        #region Protocol Settings
        public static ProtocolSettings getProtocolSettings()
        {
            ProtocolSettings settings = new ProtocolSettings();
            //1. Get all services
            settings.services = new ServiceDAL().Select();
            //2. Get all subscribed services
            settings.servicesSel = new ServiceDAL().SelectProtocolSubscribed();
            //3. Get all payment systems
            settings.paymentSystems = new PaymentSystemDAL().Select();
            //4. Get all subscribed payment systems
            settings.paymentSystemsSel = new PaymentSystemDAL().SelectProtocolSubscribed();
            //5. Get service protocol period
            settings.servicesPeriod = new ServiceDAL().SelectProtocolPeriod();
            //6. Get payment system protocol period
            settings.paymentSystemsPeriod = new PaymentSystemDAL().SelectProtocolPeriod();
            //7. Get service protocol level
            settings.servicesLevel = new ServiceDAL().SelectProtocolLevel();
            //8. Get payment system level
            settings.paymentSystemsLevel = new PaymentSystemDAL().SelectProtocolLevel();
            //9. Get requests level
            settings.requestsLevel = new RequestDAL().SelectProtocolLevel();
            //10. Get request period
            settings.requestsPeriod = new RequestDAL().SelectProtocolPeriod();

            return settings;
        }

        public static void saveProtocolSettings(ProtocolSettings settings)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                //1. Set protocol settings for services
                db.sp_gui_setProtocolSettings(TYPE_SERVICES, settings.servicesLevel, settings.servicesPeriod);
                //2. Set protocol settings for payment systems
                db.sp_gui_setProtocolSettings(TYPE_PSYSTEMS, settings.paymentSystemsLevel, settings.paymentSystemsPeriod);
                //3. Set protocol settings for requests
                db.sp_gui_setProtocolSettings(TYPE_REQUESTS, settings.requestsLevel, settings.requestsPeriod);
                //4. Set protocol node settings for services

                settings.services = new ServiceDAL().Select();
                settings.paymentSystems = new PaymentSystemDAL().Select();


                foreach (ServiceBLL service in settings.services)
                {
                    //subscribed services
                    if (settings.servicesSel.Contains(service.ServiceID))
                    {
                        db.sp_gui_setProtocolNodeSettings(TYPE_SERVICES, service.ServiceID, true);
                    }
                    //unsubscribed services
                    else
                    {
                        db.sp_gui_setProtocolNodeSettings(TYPE_SERVICES, service.ServiceID, false);
                    }
                }
                //5. Set protocol node settings for payment systems
                foreach (PSystemBLL psystem in settings.paymentSystems)
                {
                    //subscribed
                    if (settings.paymentSystemsSel.Contains(psystem.PSystemID))
                    {
                        db.sp_gui_setProtocolNodeSettings(TYPE_PSYSTEMS, psystem.PSystemID, true);
                    }
                    //unsubscribed
                    else
                    {
                        db.sp_gui_setProtocolNodeSettings(TYPE_PSYSTEMS, psystem.PSystemID, false);
                    }
                }
            }
        }
        #endregion
    }
    public static class SqlInExpression
    {
        public static IQueryable<TSource> WhereIn<TSource, V>(this IQueryable<TSource> source,
            Expression<Func<TSource, V>> valueSelector, IEnumerable<V> values)
        {
            if (source == null)
                throw new ArgumentNullException("source");

            if (values == null)
                return source;
            return source.Where(BuildInExpression(valueSelector, values));
        }
        /// Строит выражение для проверки значения на равенство одному из значений перечня. 
        /// Из X и {A, B, C , ...} получаем выражение вида (X==A or X==B or X==C ....)
        public static Expression<Func<TElement, bool>> BuildInExpression<TElement, TValue>(Expression<Func<TElement, TValue>> valueSelector, IEnumerable<TValue> values)
        {
            if (null == valueSelector)
                throw new ArgumentNullException("valueSelector");
            if (null == values)
                throw new ArgumentNullException("values");
            ParameterExpression p = valueSelector.Parameters.Single();
            if (!values.Any())
                return e => false;
            var equals = values.Select(value =>
            (Expression)Expression.Equal(valueSelector.Body,
            Expression.Constant(value, typeof(TValue))
            )
            );
            var body = equals.Aggregate<Expression>(
            (accumulate, equal) => Expression.OrElse(accumulate, equal)
            );

            return Expression.Lambda<Func<TElement, bool>>(body, p);
        }
    }
}
