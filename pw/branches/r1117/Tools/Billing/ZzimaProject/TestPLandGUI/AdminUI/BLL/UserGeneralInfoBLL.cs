using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class UserGeneralInfoBLL
    {
        public int ID { get; set; }
        public string Username { get; set; }
        public string Email { get; set; }
        public string RefferalCode { get; set; }
        public DateTime RegisteredDate { get; set; }
        public bool? FinalBan { get; set; }
        public DateTime? TempBan { get; set; }
    } 
}
