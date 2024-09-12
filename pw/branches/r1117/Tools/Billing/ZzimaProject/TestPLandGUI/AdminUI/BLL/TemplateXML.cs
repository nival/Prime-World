using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.DAL;

namespace ZzimaBilling.AdminUI.BLL
{
    public class TemplateXML
    {
        public XElement CreateParameters(decimal startmoney)
        {
            XElement element = new XElement("template");
            XElement amount = new XElement("amount", startmoney);
            element.Add(amount);
            return element;
        }

        public XElement AddServiceToTemplate(XElement template, int serviceID, string settings)
        { 
            //1. Create the service tag
            XElement newService = new XElement("service");
            XElement id = new XElement("id", serviceID);
            newService.Add(id);
            XElement settingsElement = new XElement("settings", settings);
            newService.Add(settingsElement);
            //2. Add the new service to current template
            template.Add(newService);
            return template;
        }

        public Template AddService(Template template, Service service)
        {
            XElement templateParameters =template.parameters;
            templateParameters = AddServiceToTemplate(templateParameters, service.id, string.Empty);
            template.parameters = templateParameters;
            return template;
        }

        public XElement AddServiceToTemplate(XElement template, Service service)
        {
            XElement newService = new XElement("service");
            XElement id = new XElement("id", service.id);
            XElement settingsElement = new XElement("settings", null);
            newService.Add(id);
            newService.Add(settingsElement);
            template.Add(newService);
            return template;
        }
    }
}
