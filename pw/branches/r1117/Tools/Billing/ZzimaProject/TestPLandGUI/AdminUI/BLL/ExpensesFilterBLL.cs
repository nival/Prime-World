using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    [Serializable()]
    public class ExpensesFilterBLL
    {
        public DateTime DateFrom { get; set; }
        public DateTime DateTo { get; set; }
        public decimal AmountFrom { get; set; }
        public decimal AmountTo { get; set; }
        public List<int> Services { get; set; }
        public List<string> Subjects { get; set; }

        public ExpensesFilterBLL()
        {
            Services = new List<int>();
            Subjects = new List<string>();
            DateFrom = DateTime.MinValue;
            DateTo = DateTime.MaxValue;
            AmountFrom = 0;
            AmountTo = decimal.MaxValue;
        }
    }
}
