using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class PaymentSystemAccountBLL
    {
        public int UserID { get; set; }
        public int PaymentSystemID { get; set; }
        public string PaymentSystemName { get; set; }
        public decimal Amount { get; set; }
    }
}
