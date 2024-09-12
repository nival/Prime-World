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

namespace ZzimaBilling.AdminUI.DAL
{
    public class PromoCodesDAL
    {
        public static List<PromoCodesBLL> GeneratePromoCodes(int empid, int count, decimal amount, string comment)
        {
            try
            {
                List<PromoCodesBLL> lst = new List<PromoCodesBLL>();
                using (BillingSPDataContext db = new BillingSPDataContext())
                {
                    int? error = -1;
                    ISingleResult<sp_gui_generatePromocodesResult> results = db.sp_gui_generatePromocodes(empid, count, amount, comment, ref error);
                    if (error != 0)
                        throw new ApiException((int)error);
                    foreach (sp_gui_generatePromocodesResult promoDetail in results)
                    {
                        lst.Add(new PromoCodesBLL
                        {
                            Code = promoDetail.code,
                            Amount = promoDetail.amount,
                            GeneratedAt = promoDetail.generatedat
                        });
                    }
                }
                return lst;
            }
            catch (Exception e)
            {
                throw new Exception("Ошибка в базе данных. Невозможно удалить шаблон: " + e.Message);
            }
        }
    }
}