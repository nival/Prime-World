using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.DAL
{
    public class ExpensesHistoryRecord
    {
        public DateTime DateTime { get; set; }
        public decimal Amount { get; set; }
        public int ServiceID { get; set; }
        public string ServiceName { get; set; }
        public string Reason { get; set; }
    }
}
