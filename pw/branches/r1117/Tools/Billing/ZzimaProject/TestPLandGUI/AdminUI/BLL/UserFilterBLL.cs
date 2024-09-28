using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class UserFilterBLL
    {
        public string UsernameMask { get; set; }
        public string UserIDMask { get; set; }
        public string EmailMask { get; set; }
        public decimal TotalFrom { get; set; }
        public decimal TotalTo { get; set; }
        public decimal RealFrom { get; set; }
        public decimal RealTo { get; set; }
        public decimal BonusFrom { get; set; }
        public decimal BonusTo { get; set; }
        public string PartnerProgramName { get; set; }
    }
}
