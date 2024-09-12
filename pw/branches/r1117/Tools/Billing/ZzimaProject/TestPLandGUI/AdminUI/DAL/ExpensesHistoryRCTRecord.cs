using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.DAL
{
    public class ExpensesHistoryRCTRecord : BaseChartableRecord
    {
        public int Place { get; set; }
        public int Count { get; set; }
        public string Reason { get; set; }
        public decimal Percent { get; set; }
    }
}
