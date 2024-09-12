using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.DAL
{
    public class PaymentsHistoryCMRecord : BaseChartableRecord
    {
        public string PaymentSystem { get; set; }
        public decimal Amount { get; set; }
        public decimal Percent { get; set; }
        public int Place { get; set; }
    }
}
