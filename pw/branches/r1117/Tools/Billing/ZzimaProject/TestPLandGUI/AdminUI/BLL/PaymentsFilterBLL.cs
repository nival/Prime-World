using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    [Serializable()]
    public class PaymentsFilterBLL
    {
        public DateTime? DateFrom { get; set; }
        public DateTime? DateTo { get; set; }
        public decimal? AmountFrom { get; set; }
        public decimal? AmountTo { get; set; }
        public int? PaymentSystemID { get; set; }
    }
}
