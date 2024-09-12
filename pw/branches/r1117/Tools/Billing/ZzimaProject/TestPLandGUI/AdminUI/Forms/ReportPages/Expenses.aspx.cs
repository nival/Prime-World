using System;
using System.Collections;
using System.Collections.Generic;
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
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.DAL;
using ZzimaBilling.AdminUI.Forms;
using ZzimaBilling.AdminUI.Forms.ReportPages;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.Admin.ReportsPages
{
    public partial class Expenses : ReportBasePage
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

        public List<string> Subjects
        {
            get
            {
                if (chbxSubjects != null && chbxSubjects.Items.Count > 0)
                {
                    List<string> subjects = new List<string>();
                    foreach (ListItem listItem in chbxSubjects.Items)
                    {
                        if (listItem.Selected)
                        {
                            subjects.Add(listItem.Text);
                        }
                    }
                    if (subjects.Count == 0)
                    { 
                        
                    }
                    return subjects;
                }
                return null;
            }
            set
            {
                if (value != null)
                {
                    chbxSubjects.DataSource = value;
                    chbxSubjects.DataBind();
                }
            }
        }

        public List<ServiceBLL> Games
        {
            get
            {
                if (chbxGames != null && chbxGames.Items.Count > 0)
                {
                    List<ServiceBLL> games = new List<ServiceBLL>();
                    foreach (ListItem listItem in chbxGames.Items)
                    {
                        if (listItem.Selected)
                        {
                            games.Add(new ServiceBLL { ServiceID = Convert.ToInt32(listItem.Value), Name = listItem.Text });
                        }
                    }
                    if (games.Count == 0)
                    {

                    }
                    return games;
                }
                return null;
            }
            set
            {
                if (value != null)
                {
                    chbxGames.DataSource = value;
                    chbxGames.DataTextField = "Name";
                    chbxGames.DataValueField = "ServiceID";
                    chbxGames.DataBind();
                }
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

        public bool DevideIntoGroupsIsChecked
        {
            get
            {
                return chbxDevideIntoGroups.Checked;
            }
            set
            {
                chbxDevideIntoGroups.Checked = value;
            }
        }

        #endregion

        #region Methods

        public override ReportParametersBLL LoadReportParameters()
        {
            ReportParametersBLL parameters = new ReportParametersBLL();

            try
            {
                parameters.AddParameter("fromDate", FromDate.ToString());
                parameters.AddParameter("toDate", ToDate.ToString());

                parameters.AddParameter("fromTotalAmount", FromTotalCount.ToString());
                parameters.AddParameter("toTotalAmount", ToTotalCount.ToString());


                parameters.AddParameter("fromTransactionCount", FromTransactionCount.ToString());
                parameters.AddParameter("toTransactionCount", ToTransactionCount.ToString());

                parameters.AddParameter("userMask", FormatUserMasks(UsernameMask));

                parameters.AddParameter("serviceIdList", JoinList(Games.Select(temp => temp.ServiceID).ToList()));
                
                parameters.AddParameter("subjectList", JoinList(Subjects, "|"));

                parameters.AddParameter("withGroups", DevideIntoGroupsIsChecked.ToString());

                parameters.AddParameter("groupsList", JoinList(Groups));

                parameters.ReportName = RPT_Expenses;
                parameters.ReportTitle = Translate("Reports.Menu.Expenses");
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
        }

        #endregion

        #region Events

        protected void chbxDevideIntoGroups_CheckedChanged(object sender, EventArgs e)
        {
            GroupsListIsEnable = ((CheckBox)sender).Checked;
        }


        protected override void Page_Load(object sender, EventArgs e)
        {
            base.Page_Load(sender, e);
            if (!IsPostBack)
            {
                LoadDefaultSettings();
                Subjects = EmployeeDAL.getAllSubjects();
                Games = EmployeeDAL.getServices();
                CheckAll(chbxSubjects);
                CheckAll(chbxGames);
            }
            GroupsListIsEnable = DevideIntoGroupsIsChecked;
        }

        #endregion
    }
}
