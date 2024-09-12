using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using ZzimaBilling.AdminUI.BLL;

namespace ZzimaBilling.AdminUI.DAL
{
    public class ServiceDAL
    {
        public static List<ServiceBLL> IndependentSvcsListForBalance()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ServiceBLL> result = (from services in db.Services
                                           where services.independent == true && services.cbtMode == false
                                           select new ServiceBLL
                                           {
                                               ServiceID = services.id,
                                               Name = services.name
                                           }).ToList<ServiceBLL>();
                return result;
            }
        }
        public static string GetSvcGuidNameById(int userId, int? svcId)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                string accName = (from rec in db.vw_api_accountMaps
                               where rec.userid == userId && object.Equals(rec.serviceId , svcId)
                               select rec.accName).FirstOrDefault();
                return accName;
            }
        }

        public List<ServiceBLL> Select()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<ServiceBLL> result = (from services in db.Services
                                           select new ServiceBLL
                                           {
                                               ServiceID = services.id,
                                               Name = services.name
                                           }).ToList<ServiceBLL>();
                return result;
            }
        }

        public List<int> SelectProtocolSubscribed()
        {
            using(BillingSPDataContext db=new BillingSPDataContext())
            {
                List<int> result = (from services in db.vw_gui_protocolServices
                                           where services.protocol==1
                                           select services.id).ToList<int>();
                return result;
            }
        }

        public int SelectProtocolPeriod()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                int period = (from protocolSettings in db.ProtocolSettings
                              where protocolSettings.name == "Services"
                              select protocolSettings.timeout.Value).SingleOrDefault<int>();
                return period;
            }
        }

        public int SelectProtocolLevel()
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                int period = (from protocolSettings in db.ProtocolSettings
                              where protocolSettings.name == "Services"
                              select protocolSettings.loglevel).SingleOrDefault<int>();
                return period;
            }
        }



        public List<Service> Select(int[] serviceIDs)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                List<Service> serviceList=new List<Service>();
                for (int i = 0; i < serviceIDs.Length; i++)
                {
                    Service item = (from service in db.Services
                                    where service.id == serviceIDs[i]
                                    select service).SingleOrDefault();
                    serviceList.Add(item);
                }
                return serviceList;
            }
        }

        public List<Service> Select(List<int> serviceIDs)
        {
            if (serviceIDs.Count > 0)
            {
                using (BillingDataContext db = new BillingDataContext())
                {
                    List<Service> serviceList = new List<Service>();
                    foreach (var id in serviceIDs)
                    {
                        Service item = (from service in db.Services
                                        where service.id == id
                                        select service).SingleOrDefault();
                        serviceList.Add(item);
                    }
                    return serviceList;
                }
            }
            else
                return null;
        }

        public Service Select(int serviceID)
        {
            using (BillingDataContext db = new BillingDataContext())
            {
                Service result = (from services in db.Services
                                  where services.id == serviceID
                                  select services).SingleOrDefault();
                return result;
            }
        }
    }
}
