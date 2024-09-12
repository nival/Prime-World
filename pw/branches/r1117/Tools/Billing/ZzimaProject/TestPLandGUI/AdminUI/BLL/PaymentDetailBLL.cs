using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class PaymentDetailBLL
    {
        public int ProtocolID { get; set; }
        public int UserID {get;set;}
        public DateTime DateTime { get; set; }
        public int PaymentSystemID { get; set; }
        public string PaymentSystemName { get; set; }
        public decimal Amount { get; set; }
    }

    public class PaymentDetailByTransactionBLL
    {
        public int PaymentSystemID { get; set; }
        public string PaymentSystemName {get;set;}
        public int Count { get; set; }
        public int Portion { get; set; }
    }
}
