using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class AccountDetailBLL
    {
        public int UserID { get;set; }
        public string AccountID { get;set; }
        public string ServiceName { get;set; }
        public decimal Amount { get;set; }
    }
}
