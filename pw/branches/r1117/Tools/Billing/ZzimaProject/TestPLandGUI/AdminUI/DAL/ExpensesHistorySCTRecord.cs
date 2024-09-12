using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.DAL
{
    public class ExpensesHistorySCTRecord : BaseChartableRecord
    {
        public int Place { get; set; }
        public int Count { get; set; }
        public string ServiceName { get; set; }
        public decimal Percent { get; set; }
    }
}
