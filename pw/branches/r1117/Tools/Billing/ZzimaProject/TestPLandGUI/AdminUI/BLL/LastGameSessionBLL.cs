using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.BLL
{
    public class LastGameSessionBLL
    {
        public int ID { get; set; }
        public string Name { get; set; }
        public DateTime LastSession { get; set; }

        //Properties for format input in GridView
        public DateTime LastSessionDate
        {
            get
            {
                if (LastSession == null)
                    return DateTime.MinValue;
                return LastSession;
            }
        }

        public string LastSessionTime
        {
            get
            {
                if (LastSession == null)
                    return string.Empty;
                return LastSession.ToShortTimeString();
            }
        }
    }
}
