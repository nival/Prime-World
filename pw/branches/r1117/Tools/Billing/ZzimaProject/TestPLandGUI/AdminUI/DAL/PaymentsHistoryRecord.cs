using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.DAL
{
    public class PaymentsHistoryRecord
    {
        public DateTime Date { get; set; }
        public decimal Amount { get; set; }
        public string PaymentSystem { get; set; }
        public string Reason { get; set; }
    }

    public class PaymentsHistorySummary
    {
        public int TotalCount { get; set; }
        public decimal TotalAmount { get; set; }
        public int PaymentSystemsCount { get; set; }
    }

    public class TransferHistoryRecord
    {
        //AMOUNT, EXECUTEDAT, REASON, SRCACCID, DESTACCID
        public decimal AMOUNT { get; set; }
        public DateTime EXECUTEDAT { get; set; }
        public string REASON { get; set; }
        public int? SRCACCID { get; set; }
        public int? DESTACCID { get; set; }
    }
}
