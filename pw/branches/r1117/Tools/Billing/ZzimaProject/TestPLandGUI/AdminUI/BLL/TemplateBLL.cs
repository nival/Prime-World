using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using ZzimaBilling.AdminUI.DAL;
using System.Xml.Linq;

namespace ZzimaBilling.AdminUI.BLL
{
    [Serializable()]
    public class TemplateBLL
    {
        public int ID { get; set; }
        public string Name { get; set; }
        public string Mask { get; set; }

        //Parameters
        public int Amount { get; set; }
        public List<ServiceBLL> Services;


        public bool UpdateServiceSettings(int serviceID, string settings)
        {
            ServiceBLL updatedService = (from us in Services
                                         where us.ServiceID == serviceID
                                         select us).SingleOrDefault<ServiceBLL>();
            if (updatedService != null)
            {
                updatedService.Settings = settings;
                return true;
            }
            return false;
        }

        public void AddService(ServiceBLL serviceBLL)
        {
            Services.Add(serviceBLL);
        }

        public void DeleteService(int serviceID)
        {
            foreach (ServiceBLL service in Services)
            {
                if (service.ServiceID == serviceID)
                    Services.Remove(service);
            }
        }

        public ServiceBLL GetServiceByID(int serviceID)
        {
            ServiceBLL service = (from s in Services
                                  where s.ServiceID == serviceID
                                  select s).SingleOrDefault<ServiceBLL>();
            if (service != null)
                return service;
            return null;
        }

        public TemplateBLL() {
            Services = new List<ServiceBLL>();
        }


        ///Mapping constructor
        public TemplateBLL(Template templateDAL)
        {
            ID = templateDAL.id;
            Name = templateDAL.name;
            Mask = templateDAL.mask;
            Services = GetServices(templateDAL.parameters);
        }

        public Template ToTemplate()
        {
            Template td = new Template();
            td.id = this.ID;
            td.name = this.Name;
            td.mask = this.Mask;
            //parameters
            XElement parameters = new XElement("template");

            XElement amount = new XElement("amount");
            amount.Value = this.Amount.ToString();

            parameters.Add(amount);
            if (Services.Count >= 0)
            {
                foreach (ServiceBLL sb in Services)
                    parameters.Add(sb.ToXElement());
            }
            td.parameters = parameters;
            return td;
        }


        //Helper Methods
        private List<ServiceBLL> GetServices(XElement parameters)
        {

            List<ServiceBLL> list = new List<ServiceBLL>();
            foreach (var par in parameters.Descendants("service"))
            {
                ServiceBLL item = new ServiceBLL();
                item.ServiceID = int.Parse(par.Element("id").Value);
                if (par.Element("settings")==null)
                    item.Settings = string.Empty;
                else
                    item.Settings = par.Element("settings").Value;
                list.Add(item);
            }
            return list;
        }

       
    }
}
