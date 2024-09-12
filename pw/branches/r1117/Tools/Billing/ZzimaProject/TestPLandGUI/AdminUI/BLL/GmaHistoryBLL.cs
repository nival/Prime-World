using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class GmaHistoryBLL
    {
        public DateTime Date { get; set; }
        public decimal Sum { get; set; }
        public string Login { get; set; }
        public string Comment { get; set; }
    }
}
