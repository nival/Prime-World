using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Data;
using System.Web.Configuration;
using ZzimaBilling.AdminUI.DAL;
using ZzimaBilling.AdminUI.BLL;

namespace ZzimaBilling.Additive
{
    public partial class MassReplenish : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                BindCheckBoxes();
            }
        }
        public void BindCheckBoxes()
        {
            List<ServiceBLL> result = null;
            using (BillingDataContext db = new BillingDataContext())
            {
                result = (from services in db.Services
                                           select new ServiceBLL
                                           {
                                               ServiceID = services.id,
                                               Name = services.name
                                           }).ToList<ServiceBLL>();
            }
            ddlFromServiceName.DataSource = result;
            ddlFromServiceName.DataValueField = "ServiceID";
            ddlFromServiceName.DataTextField = "Name";
            ddlFromServiceName.DataBind();
        }
        protected void btnReplenish_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(txtUserList.Text))
            {
                lblWarn.Text = "список юзеров пустой";
                return;
            }
            string[] separators = new string[] { "\r\n" };
            string[] inputUsers = txtUserList.Text.Split(separators, StringSplitOptions.RemoveEmptyEntries);
            int svcId = Convert.ToInt32(ddlFromServiceName.SelectedValue);
            string ps = ddlPaymentSystem.SelectedValue;
            int amount = Convert.ToInt32(txtAmount.Text);
            string reason = txtReason.Text;
            int? error = 0;
            List<string> errorUsers = new List<string>();
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                foreach (string user in inputUsers)
                {
                    db.sp_api_replenish(svcId, user, null, ps, amount, reason, ref error);
                    if (error != 0) errorUsers.Add(user + " errorCode : " + error.ToString()); 
                }
            }
            if (errorUsers.Count > 0)
            {
                lblWarn.Text = "Не удалось пополнить";
                gvResult.DataSource = errorUsers;
                gvResult.DataBind();
            }
            else
            {
                lblWarn.Text = "Все пополнения успешны";
                gvResult.DataSource = null;
                gvResult.DataBind();
            }
        }
    }
}