using System;
using System.Data;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.DAL;

namespace ZzimaBilling.AdminUI.BLL
{
    public class ProtocolSettings
    {
        public Int32 servicesLevel { get; set; }
        public List<ServiceBLL> services { get; set; }
        public List<Int32> servicesSel { get; set; }
        public Int32 servicesPeriod { get; set; }
        public Int32 paymentSystemsLevel { get; set; }
        public List<PSystemBLL> paymentSystems { get; set; }
        public List<Int32> paymentSystemsSel { get; set; }
        public Int32 paymentSystemsPeriod { get; set; }
        public Int32 requestsLevel { get; set; }
        public Int32 requestsPeriod { get; set; }

        public ProtocolSettings()
        {
            services = new List<ServiceBLL>();
            servicesSel = new List<Int32>();
            paymentSystems = new List<PSystemBLL>();
            paymentSystemsSel = new List<Int32>();
        }

        public void get()
        {

        }

        public void save()
        {
        }
    }
}
