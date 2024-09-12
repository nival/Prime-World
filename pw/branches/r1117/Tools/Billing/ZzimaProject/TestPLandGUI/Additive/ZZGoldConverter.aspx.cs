using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.DAL;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.API.DL.apidsTableAdapters;
using ZzimaBilling.API.PL;
using ZzimaBilling.API.BL;
using ZzimaBilling.AdminUI.Forms;

namespace ZzimaBilling.Additive
{
    public partial class ZZGoldConverter : BasePage
    {
        const int commonAcc = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                FillServices(ddlFromServiceName);
                FillServicesOnlyIndependent(ddlSrcServiceName);
                FillServicesOnlyIndependent(ddlDestServiceName);
            }
        }
        private void FillServices(DropDownList ddlServices)
        {
            ddlServices.Items.Clear();
            List<ServiceBLL> ls = new ServiceDAL().Select();
            foreach (ServiceBLL svc in ls)
            {
                ddlServices.Items.Add(new ListItem(svc.Name, svc.ServiceID.ToString()));
            }
        }
        private void FillServicesOnlyIndependent(DropDownList ddlServices)
        {
            ddlServices.Items.Clear();
            ddlServices.Items.Add(new ListItem("общий", commonAcc.ToString()));
            List<ServiceBLL> lsIndependents = ServiceDAL.IndependentSvcsListForBalance();
            foreach (ServiceBLL svc in lsIndependents)
            {
                ddlServices.Items.Add(new ListItem(svc.Name, svc.ServiceID.ToString()));
            }
        }

        protected void btnTransfer_Click(object sender, EventArgs e)
        {
            int fromSvcId = Convert.ToInt32(ddlFromServiceName.SelectedValue);
            int srcSvcId = Convert.ToInt32(ddlSrcServiceName.SelectedValue);
            int destSvcId = Convert.ToInt32(ddlDestServiceName.SelectedValue);
            bool srcAccCbt = srcSvcId == 0 ? false : new ServiceDAL().Select(srcSvcId).cbtMode;
            bool destAccCbt = destSvcId == 0 ? false : new ServiceDAL().Select(destSvcId).cbtMode;
            if (srcAccCbt != destAccCbt)
            {
                ShowMessage(true, "cbt режимы сервисов не совпадают", null);
                return;
            }
            int srcUserId = UserDAL.GetIdByUserName(txtSrcUsername.Text);
            if (srcUserId == 0)
            {
                ShowMessage(true, "юзер-источник не существует", null);
                return;
            }
            int destUserId = UserDAL.GetIdByUserName(txtDestUserName.Text);
            if (destUserId == 0)
            {
                ShowMessage(true, "юзер-получатель не существует", null);
                return;
            }
            string srcAccName = ServiceDAL.GetSvcGuidNameById(srcUserId, srcSvcId == commonAcc ? (int?)null : srcSvcId);
            string destAccName = ServiceDAL.GetSvcGuidNameById(destUserId, destSvcId == commonAcc ? (int?)null : destSvcId);
            
            APIQueriesAdapter ad = new APIQueriesAdapter();
            int? errorCode = 0;
            ad.sp_api_transfer(fromSvcId, txtSrcUsername.Text, srcAccName, txtDestUserName.Text, destAccName, Convert.ToInt32(txtAmount.Text), txtReason.Text, ref errorCode);
            if (errorCode != 0)
            {
                ShowMessage(true, "код ошибки : " + errorCode.ToString(), null);
            }
            else
            {
                ShowMessage(false, "средства успешно переведены", null);
            }
        }
    }
}