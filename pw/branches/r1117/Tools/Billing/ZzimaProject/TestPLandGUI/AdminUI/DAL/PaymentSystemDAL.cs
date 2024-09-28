using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using ZzimaBilling.AdminUI.BLL;

namespace ZzimaBilling.AdminUI.DAL
{
    public class PaymentSystemDAL
    {
        //Gets all payment systems
        public List<PSystemBLL> Select()
        { 
            using(BillingDataContext db=new BillingDataContext())
            {
                List<PSystemBLL> result = (from ps in db.PaymentSystems
                                           select new PSystemBLL
                                           {
                                               PSystemID = ps.id,
                                               Name = ps.name
                                          }).ToList<PSystemBLL>();
                return result;
            }
        }

        //Gets all payment systems except CBT and BONUSES
        public static List<PSystemBLL> SelectReal()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<PSystemBLL> result = (from ps in db.PaymentSystems
                                           where ps.id!=1 && ps.id!=2
                                           select new PSystemBLL
                                           {
                                               PSystemID = ps.id,
                                               Name = ps.name
                                           }).ToList<PSystemBLL>();
                return result;
            }
        }

        //Gets all payment systems except CBT
        public static List<PSystemBLL> SelectRealWithBonuses()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<PSystemBLL> result = (from ps in db.PaymentSystems
                                           where ps.id != 2
                                           select new PSystemBLL
                                           {
                                               PSystemID = ps.id,
                                               Name = ps.name
                                           }).ToList<PSystemBLL>();
                return result;
            }
        }

        public List<int> SelectProtocolSubscribed()
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                List<int> result = (from pps in db.vw_gui_protocolPaymentSystems
                                    where pps.protocol == 1
                                    select pps.id).ToList<int>();
                return result;
            }
        }

        public int SelectProtocolPeriod()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                int period = (from protocolSettings in db.ProtocolSettings
                              where protocolSettings.name == "PaymentSystems"
                              select protocolSettings.timeout.Value).SingleOrDefault<int>();
                return period;
            }
        }

        public int SelectProtocolLevel()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                int period = (from protocolSettings in db.ProtocolSettings
                              where protocolSettings.name == "PaymentSystems"
                              select protocolSettings.loglevel).SingleOrDefault<int>();
                return period;
            }
        }
    }
}
