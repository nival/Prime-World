using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;

namespace ZzimaBilling.AdminUI.BLL
{
    [Serializable()]
    public class ServiceBLL
    {
        public int ServiceID { get; set; }
        public string Name { get; set; }
        public string Settings { get; set; }

        public XElement ToXElement()
        {
            XElement service = new XElement("service");
            XElement id = new XElement("id");
            id.Value = this.ServiceID.ToString();
            XElement settings = new XElement("settings");
            if (this.Settings == null || this.Settings == string.Empty)
                settings.Value = string.Empty;
            else
                settings.Value = this.Settings;
            service.Add(id);
            service.Add(settings);
            return service;
        }


    }
}
