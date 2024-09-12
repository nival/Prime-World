using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace ZzimaBilling.AdminUI.DAL
{
    public class RequestDAL
    {
        public int SelectProtocolPeriod()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                int period = (from protocolSettings in db.ProtocolSettings
                              where protocolSettings.name == "Reporting"
                              select protocolSettings.timeout.Value).SingleOrDefault<int>();
                return period;
            }
        }

        public int SelectProtocolLevel()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                int period = (from protocolSettings in db.ProtocolSettings
                              where protocolSettings.name == "Reporting"
                              select protocolSettings.loglevel).SingleOrDefault<int>();
                return period;
            }
        }
    }
}
