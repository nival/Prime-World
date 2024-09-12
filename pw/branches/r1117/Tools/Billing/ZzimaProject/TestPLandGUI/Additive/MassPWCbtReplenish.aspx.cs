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
using System.Configuration;
using ZzimaBilling.API.PL;
using ZzimaBilling.API.DL;
using ZzimaBilling.API.DL.apidsTableAdapters;


namespace ZzimaBilling.Additive
{
    public partial class MassPWCbtReplenish : System.Web.UI.Page
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
            string serviceName = ConfigurationManager.AppSettings["pwTestName"];
            using (BillingDataContext db = new BillingDataContext())
            {
                result = db.Services.Where(serv => serv.name == serviceName)
                .Select(serv => new ServiceBLL
                {
                    ServiceID = serv.id,
                    Name = serv.name
                }).ToList<ServiceBLL>();
            }
            ddlFromServiceName.DataSource = result;
            ddlFromServiceName.DataValueField = "ServiceID";
            ddlFromServiceName.DataTextField = "Name";
            ddlFromServiceName.DataBind();
        }
        protected void btnReplenish_Click(object sender, EventArgs e)
        {
            string[] separators = new string[] { "\r\n" };
            string[] inputUsers = txtUserList.Text.Split(separators, StringSplitOptions.RemoveEmptyEntries);
            if (inputUsers.Length == 0)
            {
                lblWarn.Text = "список юзеров пустой";
                return;
            }
            int svcId = Convert.ToInt32(ddlFromServiceName.SelectedValue);
            string ps = ddlPaymentSystem.SelectedValue;
            int amount = Convert.ToInt32(txtAmount.Text);
            string reason = txtReason.Text;
            int? error = 0;
            List<string> errorUsers = new List<string>();

            if (ddlReplenishRegime.SelectedValue == "align")//выровнять на значение
            {
                foreach (string user in inputUsers)
                {
                    string us = user.Trim();
                    sp_api_getBalanceTableAdapter ad = new sp_api_getBalanceTableAdapter();
                    Nullable<int> errorCode = 0;
                    apids.sp_api_getBalanceDataTable table = ad.GetData(us, svcId, ref errorCode);
                    if (errorCode != 0)
                    {
                        errorUsers.Add(us + " errorCode : " + errorCode.ToString());
                        continue;
                    }
                    errorCode = 0;
                    int balance = (int)(table[0].IsAMOUNTNull() ? 0 : table[0].AMOUNT);
                    int delta = Math.Abs(amount - balance);
                    if (balance < amount)
                    {
                        using (BillingSPDataContext db = new BillingSPDataContext())
                        {
                            db.sp_api_replenish(svcId, us, null, ps, delta, reason, ref errorCode);
                            if (errorCode != 0)
                            {
                                errorUsers.Add(us + " errorCode : " + errorCode.ToString());
                            }
                        }
                    }
                    if (balance > amount)
                    {
                        APIQueriesAdapter aq = new APIQueriesAdapter();
                        errorCode = 0;
                        aq.sp_api_writeOff(svcId, us, null, delta, reason, ref errorCode);
                        if (errorCode != 0)
                        {
                            errorUsers.Add(us + " errorCode : " + errorCode.ToString());
                        }
                    }
                }
                if (errorUsers.Count > 0)
                {
                    lblWarn.Text = "Не удалось привести";
                    gvResult.DataSource = errorUsers;
                    gvResult.DataBind();
                }
                else
                {
                    lblWarn.Text = "Все операции успешны";
                    gvResult.DataSource = null;
                    gvResult.DataBind();
                }
            }
            else //пополнить на значение
            {
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
}