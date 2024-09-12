using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.Forms;
using ZzimaBilling.AdminUI.Forms.ReportPages;
using ZzimaBilling.AdminUI.BLL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.DAL;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.Admin.ReportsPages
{
    public partial class Payments : ReportBasePage
    {
        #region Properties

        public DateTime FromDate
        {
            get
            {
                return dtTimePeriod.fromDate;
            }
        }

        public DateTime ToDate
        {
            get
            {
                return dtTimePeriod.toDate;
            }
        }

        public string UsernameMask
        {
            get
            {
                return tbxUsernameMask.Text;
            }
        }

        public List<PSystemBLL> PaymentSystems
        {
            get
            {
                if (chbxPaymentSystems != null && chbxPaymentSystems.Items.Count > 0)
                {
                    List<PSystemBLL> psystems = new List<PSystemBLL>();
                    foreach (ListItem listItem in chbxPaymentSystems.Items)
                    {
                        if (listItem.Selected)
                        {
                            PSystemBLL psystemBLL = new PSystemBLL();
                            psystemBLL.PSystemID = Convert.ToInt32(listItem.Value);
                            psystemBLL.Name = listItem.Text;
                            psystems.Add(psystemBLL);
                        }
                    }
                    if (psystems.Count == 0)
                    {
                        psystems = PaymentSystemDAL.SelectReal();
                    }
                    return psystems;
                }
                return null;
            }
            set
            {
                if (value != null)
                {
                    chbxPaymentSystems.DataSource = value;
                    chbxPaymentSystems.DataTextField = "Name";
                    chbxPaymentSystems.DataValueField = "PSystemID";
                    chbxPaymentSystems.DataBind();
                }
            }
        }

        public decimal FromTotalCount
        {
            get
            {
                return ncTotalCount.From;
            }
        }

        public decimal ToTotalCount
        {
            get
            {
                return ncTotalCount.To;
            }
        }

        public int FromTransactionCount
        {
            get
            {
                return Convert.ToInt32(ncTransactionCount.From);
            }
        }

        public int ToTransactionCount
        {
            get
            {
                return Convert.ToInt32(ncTransactionCount.To);
            }
        }

        public List<int> Groups
        {
            get
            {
                return gpGroups.Groups;
            }
        }

        public bool GroupsListIsEnable
        {
            get
            {
                return gpGroups.Enabled;
            }
            set
            {
                gpGroups.Enabled = value;
            }
        }

        public bool HideTransactionsIsChecked
        {
            get
            {
                return chbxHideTransactions.Checked;
            }
            set
            {
                chbxHideTransactions.Checked = value;
            }
        }

        public bool DevideIntoGroupsIsChecked
        {
            get
            {
                return chbxDevideIntoGroups.Checked;
            }
            set
            {
                chbxDevideIntoGroups.Checked = value;
                gpGroups.Enabled = value;
            }
        }

        #endregion

        #region Methods

        public override ReportParametersBLL LoadReportParameters()
        {
            try
            {
                ReportParametersBLL parameters = new ReportParametersBLL();

                parameters.AddParameter("fromDate", FromDate.ToString());
                parameters.AddParameter("toDate", ToDate.ToString());

                parameters.AddParameter("fromTotalAmount", FromTotalCount.ToString());
                parameters.AddParameter("toTotalAmount", ToTotalCount.ToString());


                parameters.AddParameter("fromTransactionCount", FromTransactionCount.ToString());
                parameters.AddParameter("toTransactionCount", ToTransactionCount.ToString());

                parameters.AddParameter("userMask", FormatUserMasks(UsernameMask));

                var PaymentsSystemsList=PaymentSystems.Select(ps => ps.PSystemID).ToList();

                parameters.AddParameter("systemIdList", JoinList(PaymentsSystemsList));

                parameters.AddParameter("hideTransactions", HideTransactionsIsChecked.ToString());

                parameters.AddParameter("withGroups", DevideIntoGroupsIsChecked.ToString());

                parameters.AddParameter("groupsList", JoinList(Groups));
                
                parameters.ReportName = RPT_Payment;
                parameters.ReportTitle = Translate("Reports.Menu.Payments");
                return parameters;
            }
            catch (Exception e)
            {
                ((IErrorHandler)Master).showMessage(true, Translate("Error.Reports"), e.Message);
            }
            return null;
        }

        protected void LoadDefaultSettings()
        {
            DevideIntoGroupsIsChecked = false;
            GroupsListIsEnable = false;
            HideTransactionsIsChecked = true;
        }

        #endregion

        #region Events

        protected override void Page_Load(object sender, EventArgs e)
        {
            base.lbtnReport = lbtnReport;
            base.Page_Load(sender, e);
            if (!IsPostBack)
            {
                PaymentSystems = PaymentSystemDAL.SelectReal();
                LoadDefaultSettings();
                CheckAll(chbxPaymentSystems);
            }
            GroupsListIsEnable = DevideIntoGroupsIsChecked;
        }

        protected void chbxDevideIntoGroups_CheckedChanged(object sender, EventArgs e)
        {
            GroupsListIsEnable = ((CheckBox)sender).Checked;
        }
        
        #endregion
    }
}
