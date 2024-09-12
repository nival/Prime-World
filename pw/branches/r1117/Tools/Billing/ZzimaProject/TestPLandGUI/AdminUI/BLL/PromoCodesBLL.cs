using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class PromoCodesBLL
    {
        public static string SESSION_KEY_PROMOCODES = "promoCodesKey";

        public string Code { get; set; }
        public decimal Amount { get; set; }
        public DateTime GeneratedAt { get; set; }
    }
}
