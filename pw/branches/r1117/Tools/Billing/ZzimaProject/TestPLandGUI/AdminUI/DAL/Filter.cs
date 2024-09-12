using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

namespace ZzimaBilling.AdminUI.DAL
{
    [Serializable()]
    public class Filter
    {
        public DateTime? DateFrom { get; set; }
        public DateTime? DateTo { get; set; }
        public decimal? AmountFrom { get; set; }
        public decimal? AmountTo { get; set; }
        public string PaymentSystem { get; set; }
    }

    [Serializable]
    public class GmaHistoryFilter
    {
        public DateTime? DateFrom { get; set; }
        public DateTime? DateTo { get; set; }
        public decimal? AmountFrom { get; set; }
        public decimal? AmountTo { get; set; }
        public string GmaLogin { get; set; }
        public string Comment { get; set; }
        
        public GmaHistoryFilter()
        {
            DateFrom = new DateTime(1900, 01, 01);
            DateTo = new DateTime(2100, 01, 01);
            AmountFrom = 0;
            AmountTo = int.MaxValue;
            GmaLogin = "";
            Comment = "";
        }

        public void Validate()
        {
            if (DateTo==null)
                DateTo = new DateTime(2100, 01, 01);
            if (DateFrom == null)
                DateFrom = new DateTime(1900, 01, 01);

            if (DateTo < DateFrom || DateFrom < new DateTime(1900, 01, 01))
                throw new Exception("Invalid From date field");
            if (DateTo > new DateTime(2100, 01, 01))
                throw new Exception("Invalid To date field");

            if (AmountFrom == null)
                AmountFrom = 0;
            if (AmountTo == null)
                AmountTo = int.MaxValue;

            if (AmountTo < AmountFrom || AmountFrom < 0)
                throw new Exception("Invalid From amount field");

            if (AmountTo > decimal.MaxValue)
                throw new Exception("Invalid To amount field");

        }
    }

    [Serializable]
    public class BonusFilter
    {
        public DateTime? DateFrom { get; set; }
        public DateTime? DateTo { get; set; }
        public decimal? AmountFrom { get; set; }
        public decimal? AmountTo { get; set; }
        public string Comment { get; set; }
    }
}
