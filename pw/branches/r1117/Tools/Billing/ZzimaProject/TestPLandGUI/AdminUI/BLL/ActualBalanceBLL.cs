using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class ActualBalanceBLL
    {
        public int UserID { get; set; }
        public decimal TotalBalance { get; set; }
        public decimal BonusBalance { get; set; }
        public List<PaymentSystemAccountBLL> PaymentSystemAccounts { get; set; }


        public ActualBalanceBLL()
        {
            PaymentSystemAccounts = new List<PaymentSystemAccountBLL>();
        }
    }
}
